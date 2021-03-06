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
#include <chrono>
#include <sstream>
#include <cereal/archives/binary.hpp>
#include <flog/flog.hpp>
#include "update-table-request-impl.hpp"
#include "update-table-response-impl.hpp"
#include "action-select-request-impl.hpp"
#include "action-select-response-impl.hpp"
#include "start-request-impl.hpp"
#include "join-request-impl.hpp"
#include "join-response-impl.hpp"
#include "terminate-request.hpp"
#include "terminate-response.hpp"
#include "terminate-request-impl.hpp"
#include "terminate-response-impl.hpp"
#include "parser/environment-parser.hpp"
#include "message-utilities.hpp"

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

void marl::client_base::send_message(const marl::action_select_req& req) {
    marl::send_message_helper<marl::action_select_req>(req, m_socket);
}

void marl::client_base::send_message(const marl::action_select_rsp& rsp) {
    marl::send_message_helper<marl::action_select_rsp>(rsp, m_socket);
}

void marl::client_base::start() {
    m_is_running.store(true);
    flog::logger* l = flog::logger::instance();
    if(m_operation_mode == operation_mode_t::multi) {
        if(!join()) {
            l->log(level::ERROR_, "Unable to join to server. "
                   "Terminating...");
            stop();
            return;
        }
        l->log(level::INFO, "Waiting for all agents to come online...");
        marl::start_req msg;
        if(!receive_message_helper<marl::start_req>(msg, m_socket)) {
            l->log(level::ERROR_, "Unable to get start command from server. "
                   "Terminating...");
            stop();
            return;
        }
        l->log(level::INFO, "Received start command from server.");
        l->logc(level::INFO, "Reported agent count is : %d", msg.agent_count);
        m_sender = std::thread{&client_base::response_worker, this};
        m_receiver = std::thread{&client_base::receiver_worker, this};
        m_main_loop = std::thread{&client_base::run, this};
    } else if(m_operation_mode == operation_mode_t::single) {
        // Just run single agent mode
        m_main_loop = std::thread{&client_base::run, this};
    }
}

void marl::client_base::wait() {
    if(m_main_loop.joinable()) {
        m_main_loop.join();
    }
    if(m_sender.joinable()) {
        m_sender.join();
    }
    if(m_receiver.joinable()) {
        m_receiver.join();
    }
}

void marl::client_base::stop() {
    m_is_running.store(false);
}

void marl::client_base::set_id(uint32_t id) {
    m_id = id;
}

uint32_t marl::client_base::id() const {
    return m_id;
}

void marl::client_base::initialize(marl::operation_mode_t ot,
                                   marl::learning_mode_t lt) {
    m_operation_mode = ot;
    m_learning_mode = lt;
    if(m_operation_mode == operation_mode_t::multi &&
            m_learning_mode == learning_mode_t::exploit) {
        flog::logger* l = flog::logger::instance();
        l->log(level::ERROR_, "Exploit mode in Multi-Agent environment does not "
               "make sense. Falling back so single-agent mode.");
        m_operation_mode = operation_mode_t::single;
    }
}

bool marl::client_base::initialize(const std::string& path, uint32_t start, uint32_t id) {
    flog::logger* l = flog::logger::instance();
    l->log(level::INFO, "Reading problem instance from `%s'...", path.c_str());

    marl::environment_parser mdp_parser;
    xml_schema::document doc_p(mdp_parser, "environment",
                               xml_schema::flags::dont_validate);
    mdp_parser.pre();
    doc_p.parse(path.c_str());
    m_env = mdp_parser.post_environment();
    m_start_index = start;
    m_id = id;
    l->log(level::INFO, "Parsing problem done.");
    l->logc(level::INFO, "Title: `%s'.", m_env.title().c_str());
    l->logc(level::INFO, "Desc.: `%s'.", m_env.description().c_str());
    l->logc(level::INFO, "Number of states: %d.", m_env.states().size());
    l->logc(level::INFO, "Number of actions: %d.", m_env.actions().size());
    l->logc(level::INFO, "Agent ID: %d.", id);
    l->logc(level::INFO, "Initial state: %d.", start);
    return true;
    // TODO: How do we check errors?
}

uint32_t marl::client_base::iterations() const {
    return m_iterations;
}

void marl::client_base::set_iterations(uint32_t i) {
    m_iterations = i;
}

void marl::client_base::terminate() {
    flog::logger* l = flog::logger::instance();
    l->log(level::INFO, "Requesting terminate for %d...", m_id);
    marl::terminate_request req;
    req.agent_id = m_id;
    marl::send_message_helper<marl::terminate_request>(req, m_socket);
}

bool marl::client_base::join() {
    flog::logger* l = flog::logger::instance();

    if(m_operation_mode == operation_mode_t::single) {
        l->log(level::WARN, "Trying to join to server in single agent mode!");
        l->logc(level::WARN, "Callback will be silently ignored.");
        return false;
    }

    l->log(level::INFO, "Trying to join to server...");
    join_req req;
    req.agent_id = m_id;
    req.problem_name = m_env.title();
    if(!send_message_helper<join_req>(req, m_socket)) {
        l->log(level::FATAL, "Unable to send joining request over socket...");
        return false;
    } else {
        l->log(level::INFO, "Joining request has been sent. Waiting for response...");
    }
    join_rsp rsp;
    if(!receive_message_helper<join_rsp>(rsp, m_socket)) {
        l->log(level::FATAL, "Unable to receive joining response from socket...");
        return false;
    }
    if(rsp.success) {
        l->log(level::INFO, "Joining was successful.");
        return true;
    } else {
        l->log(level::ERROR_, "Unable to join to server.");
        l->logc(level::ERROR_, "Server returned error:");
        l->logc(level::ERROR_, rsp.error_message.c_str());
        return false;
    }
}

void marl::client_base::set_rendezvous(uint32_t request_id) {
    flog::logger* l = flog::logger::instance();
    l->log(level::TRACE, "Setting rendezvous for request %d...", request_id);
    std::lock_guard<std::mutex> lck{m_request_history_lck};
    if(!m_request_history.insert(std::make_pair(request_id, std::make_unique<request_track>())).second) {
        l->log(level::TRACE, "A rendezvous is already set for request %d...", request_id);
    } else {
        l->logc(level::TRACE, "Rendezvous for request %d is set. Rendezvous map size is: %d",
                request_id, m_request_history.size());
    }
}

std::unique_ptr<marl::response_base> marl::client_base::get_response(uint32_t request_id) {
    flog::logger* l = flog::logger::instance();
        l->log(level::TRACE, "Waiting for history lock...");
    std::unique_lock<std::mutex> lck{m_request_history_lck};
        l->logc(level::TRACE, "history lock released.");
    auto found = m_request_history.find(request_id);
    if(found == m_request_history.end()) {
        l->log(level::FATAL,
               "Unable to find original requets to wait for. Req number is: %d. Map size is: %d",
               request_id, m_request_history.size());
        return nullptr;
    }
    std::unique_ptr<request_track>& ptr = found->second;
    lck.unlock();
    std::unique_lock<std::mutex> lk{ptr->lock};
    l->logc(level::TRACE, "condition_var lock released.");
    l->log(level::TRACE, "Waiting on condition to be released. Req number is: %d", request_id);
    // TODO: Wait for some time
    ptr->waiter.wait(lk, [&ptr] {return ptr->ready;});
    l->logc(level::TRACE, "Condition is released");
    return std::move(ptr->response);
}

/**
 * @brief marl::client_base::response_worker
 * Takes a request from queue, processes the request, sends the response to
 * server. Sending response is a blocking call. It will be replaced with a queue
 * mechanism in the next releases.
 */
void marl::client_base::response_worker() {
    flog::logger* l = flog::logger::instance();
    l->log(level::INFO, "Starting response worker...");
    while(m_is_running.load()) {
        if(!m_requests_sem.wait_for(std::chrono::milliseconds{100})) {
            continue;
        }
        std::unique_lock<std::mutex> req_lck{m_request_lock};
        request_base* req = m_requests.front();
        m_requests.pop_front();
        req_lck.unlock();
        action_select_req* asrp = dynamic_cast<action_select_req*>(req);
        action_select_rsp rsp = process_request(*asrp);
        send_message(rsp);
        delete req;
    }
    l->log(level::INFO, "Stopping response worker...");
}

/**
 * @brief marl::client_base::receiver_worker
 * Listens on the socket, puts every incomming message into the requests or
 * responses queue.
 */
void marl::client_base::receiver_worker() {
    flog::logger* l = flog::logger::instance();
    l->log(level::INFO, "Starting message reader...");
    while(m_is_running.load()) {
        std::unique_ptr<message_base> msg = receive_message(m_socket);
        switch(msg->type()) {
            case MARL_ACTION_SELECT_REQ:
            case MARL_UPDATE_TABLE_REQ: {
                l->log(level::TRACE, "Incomming message type is : request.");
                std::unique_lock<std::mutex> lck{m_request_lock};
                m_requests.push_back(dynamic_cast<request_base*>(msg->clone()));
                lck.unlock();
                m_requests_sem.notify();
            }
            break;
            case MARL_ACTION_SELECT_RSP:
            case MARL_UPDATE_TABLE_RSP: {
                l->log(level::TRACE, "Incomming message type is : response.");
                std::lock_guard<std::mutex> lck{m_request_history_lck};
                // Note: Ownership of this pointer will be taken away
                marl::response_base* rsp = dynamic_cast<response_base*>(msg->clone());
                if(!rsp) {
                    l->log(level::FATAL, "Unable to cast received response to `marl::response_base*`...");
                    delete rsp;
                    continue;
                }
                auto found = m_request_history.find(rsp->request_number);
                if(found == m_request_history.end()) {
                    l->log(level::FATAL, "Unable to find original request for received response: %d, Map size is: %d",
                           rsp->request_number, m_request_history.size());
                } else {
                    {
                        l->log(level::TRACE, "Waiting on condition_var lock to notify...");
                        std::lock_guard<std::mutex> lk(found->second->lock);
                        l->logc(level::TRACE, "condition_var lock for notify is released.");
                        found->second->response = std::unique_ptr<marl::response_base>(rsp);
                        found->second->ready = true;
                    }
                    l->logc(level::TRACE, "notifying the cond_var...");
                    found->second->waiter.notify_one();
                }
            }
            break;
            case MARL_TERMINATE_RSP: {
                l->log(level::TRACE, "Incomming message type is : terminate.");
                l->log(level::TRACE, "Terminating...");
                stop();
                cpnet_close(m_socket);
            }
            break;
            default:
                break;
        }
    }
    l->log(level::INFO, "Stopping message reader...");
    // l->flush(std::chrono::seconds{10});
}
