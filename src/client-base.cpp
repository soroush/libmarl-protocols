/*
 * Copyright 2017 - Roya Ghasemzade <roya@ametisco.ir>
 * Copyright 2017 - Soroush Rabiei <soroush@ametisco.ir>
 *
 * This file is part of libmarl_protocols.
 *
 * libmarl_protocols is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmarl_protocols is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmarl_protocols.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "client-base.hpp"
#include <flog/flog.hpp>
#include <chrono>
#include <sstream>
#include <cereal/archives/binary.hpp>
#include "update-table-request-impl.hpp"
#include "update-table-response-impl.hpp"
#include "action-select-request-impl.hpp"
#include "action-select-response-impl.hpp"
#include "parser/environment-parser.hpp"

#define DBUFSIZE 8192
#define HEADSIZE (sizeof(uint32_t))

using level = flog::level_t;

marl::client_base::client_base() {
    cpnet_init();
}

marl::client_base::~client_base() {
    stop();
}

bool marl::client_base::connect(const std::string& address, uint16_t port) {
    flog::logger* l = flog::logger::instance();
    m_socket = cpnet_socket(SOCK_STREAM);
    if(m_socket <= 0) {
        l->log(flog::level_t::ERROR_, "Unable to create socket!");
        return false;
    }
    if(cpnet_connect(m_socket, address.c_str(), port) != 0) {
        l->log(flog::level_t::ERROR_, "Unable to connect to `%s':%d", address.c_str(), port);
        return false;
    }
    return true;
}

void marl::client_base::send_message(const marl::message_base* const msg) {
    flog::logger* l = flog::logger::instance();

    std::stringstream str_out;
    cereal::BinaryOutputArchive ar_out(str_out);
    ar_out(*msg);
    std::string buffer = str_out.str();
    size_t new_size = buffer.size() + HEADSIZE;
    char* raw_buffer = new char[new_size];
    uint32_t size = htonl(static_cast<uint32_t>(buffer.size()));
    memcpy(raw_buffer, &size, HEADSIZE);
    memcpy(raw_buffer + HEADSIZE, buffer.data(), buffer.size());
    l->log(flog::level_t::TRACE, "Sending message...");
    l->logc(flog::level_t::TRACE, "Data size   : %z", buffer.size());
    l->logc(flog::level_t::TRACE, "Packet size : %d", buffer.size());
    if(cpnet_write(m_socket, raw_buffer, new_size) <= 0) {
        l->log(level::ERROR_, "Unable to write data on socket!");
        l->log(level::ERROR_, "Network backend returned error: %s",
               cpnet_last_error());
    }
    delete[] raw_buffer;
}

void marl::client_base::start() {
    m_is_running.store(true);
    m_sender = std::thread{&client_base::response_worker, this};
    m_receiver = std::thread{&client_base::receiver_worker, this};
}

void marl::client_base::wait() {
    m_sender.join();
    m_receiver.join();
}

void marl::client_base::stop() {
    m_is_running.store(false);
    wait();
}

void marl::client_base::set_id(uint32_t id) {
    m_id = id;
}

uint32_t marl::client_base::id() const {
    return m_id;
}

bool marl::client_base::initialize(const std::string& path, uint32_t start) {
    flog::logger* l = flog::logger::instance();
    l->log(level::INFO, "Reading problem instance from `%s'...", path.c_str());

    marl::environment_parser mdp_parser;
    xml_schema::document doc_p(mdp_parser, "environment",
                               xml_schema::flags::dont_validate);
    mdp_parser.pre();
    doc_p.parse(path.c_str());
    m_env = mdp_parser.post_environment();
    l->log(level::INFO, "Parsing problem done.");
    l->logc(level::INFO, "Title: `%s'.", m_env.title().c_str());
    l->logc(level::INFO, "Desc.: `%s'.", m_env.description().c_str());
    l->logc(level::INFO, "Number of states: %d.", m_env.states().size());
    l->logc(level::INFO, "Number of actions: %d.", m_env.actions().size());
    l->logc(level::INFO, "Initial state: %d.", start);
    return true;
    // TODO: How do we check errors?
}

/**
 * @brief marl::client_base::response_worker
 * Takes a request from queue, processes the request, sends the response to
 * server. Sending response is a blocking call. It will be replaced with a queue
 * mechanism in the next releases.
 */
void marl::client_base::response_worker() {
    while(m_is_running.load()) {
        if(!m_requests_sem.wait_for(std::chrono::milliseconds{100})) {
            continue;
        }
        std::unique_lock<std::mutex> req_lck{m_request_lock};
        request_base* req = m_requests.front();
        m_requests.pop_front();
        req_lck.unlock();
        response_base* rsp = process_request(req);
        send_message(rsp);
        delete req;
        delete rsp;
    }
}

/**
 * @brief marl::client_base::receiver_worker
 * Listens on the socket, puts every incomming message into the requests or
 * responses queue.
 */
void marl::client_base::receiver_worker() {
    flog::logger* l = flog::logger::instance();
    char data_buffer[DBUFSIZE];
    char header_buffer[HEADSIZE];
    l->log(level::INFO, "Starting message reader...");
    while(m_is_running) {
        ssize_t read_size = cpnet_read2(m_socket, header_buffer,
                                        HEADSIZE, MSG_WAITALL);
        if(read_size != HEADSIZE) {
            l->log(level::ERROR_,
                   "Unable to read header from incomming connection. Error: %s",
                   cpnet_last_error());
            continue;
        }
        uint32_t expected_size = 0;
        memcpy(&expected_size, header_buffer, HEADSIZE);
        expected_size = ntohl(expected_size);
        size_t total_read = 0;
        std::stringstream istr;
        while(total_read < expected_size) {
            read_size = cpnet_read(m_socket, data_buffer, DBUFSIZE);
            if(read_size < 0) {
                l->log(level::ERROR_,
                       "Unable to read data from incomming connection. Error: %s",
                       cpnet_last_error());
                break;
            }
            total_read += read_size;
            istr.write(data_buffer, read_size);
        }
        if(expected_size != total_read) {
            l->log(level::ERROR_,
                   "Expected incomming buffer size was %z, bytes only %z received.",
                   expected_size, total_read);
            continue;
        }
        l->log(level::TRACE, "Incomming message...");
        // Process incomming message: construct buffers
        std::unique_ptr<message_base> msg;
        try {
            cereal::BinaryInputArchive archiver(istr);
            archiver(msg);
        } catch(cereal::Exception& e) {
            l->log(level::ERROR_,
                   "Unable to deserialize buffer into `message_base' object. "
                   "Error: %s", e.what());
        }
        if(!msg) {
            l->log(level::ERROR_,
                   "Received message object is not valid.");
            continue;
        }
        // Read message, according to its type, put it in a queue
        switch(msg->type()) {
            case MARL_ACTION_SELECT_REQ:
            case MARL_UPDATE_TABLE_REQ: {
                l->log(level::TRACE, "Message type is : request.");
                std::unique_lock<std::mutex> lck{m_request_lock};
                m_requests.push_back(dynamic_cast<request_base*>(msg->clone()));
                lck.unlock();
                m_requests_sem.notify();
            }
            break;
            case MARL_ACTION_SELECT_RSP:
            case MARL_UPDATE_TABLE_RSP: {
                l->log(level::TRACE, "Message type is : response.");
                std::unique_lock<std::mutex> lck{m_response_lock};
                m_responses.push_back(dynamic_cast<response_base*>(msg->clone()));
                lck.unlock();
                m_responses_sem.notify();
            }
            break;
            default:
                break;
        }
    }
}
