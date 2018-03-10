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

void marl::client_base::start() {
    m_is_running.store(true);
    m_responser = std::thread{&client_base::responser_worker, this};
    m_receiver = std::thread{&client_base::receiver_worker, this};
}

void marl::client_base::stop() {
    m_is_running.store(false);
    m_responser.join();
    m_receiver.join();
}

void marl::client_base::responser_worker() {
    while(m_is_running.load()) {
        if(!m_request_sem.wait_for(std::chrono::milliseconds{100})) {
            continue;
        }
        std::unique_lock<std::mutex> req_lck{m_request_lock};
        request_base* req = m_requests.front();
        m_requests.pop_front();
        req_lck.unlock();
        response_base* rsp = process_request(req);
        std::unique_lock<std::mutex> rsp_lck{m_response_lock};
        m_responses.push_back(rsp);
        rsp_lck.unlock();
        m_request_sem.notify();
        delete req;
    }
}
