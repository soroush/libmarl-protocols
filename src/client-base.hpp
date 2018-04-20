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


#ifndef LIBMARL_CLIENTBASE_HPP
#define LIBMARL_CLIENTBASE_HPP

#include <string>
#include <cstdint>
#include <list>
#include <mutex>
#include <thread>
#include <atomic>
#include <cpnet/cpnet-network.h>
#include "environment.hpp"
#include "semaphore.hpp"
#include "message-base.hpp"
#include "request-base.hpp"
#include "response-base.hpp"
#include "libmarl-exports.hpp"

namespace marl {

class LIBMARL_API client_base {
public:
    client_base();
    virtual ~client_base();
    bool connect(const std::string& address, uint16_t port);
    void send_message(const message_base* const);
    response_base* get_response(uint32_t request_id);
    void start();
    void wait();
    void stop();
    void set_id(uint32_t id);
    uint32_t id() const;
    // Environment
    bool initialize(const std::string& path, uint32_t start = 0);
protected:
    virtual response_base* process_request(const request_base* const) = 0;
    uint32_t m_id;
private:
    void response_worker();
    void receiver_worker();
    tidm::semaphore m_requests_sem;
    tidm::semaphore m_responses_sem;
    std::mutex m_request_lock;
    std::mutex m_response_lock;
    std::thread m_sender;
    std::thread m_receiver;
    // Module
    std::atomic_bool m_is_running;
    socket_t m_socket;
    // Incomming message queues
    std::list<request_base*> m_requests;
    std::list<response_base*> m_responses;
    // Envirinment
    environment m_env;
};

}

#endif // LIBMARL_CLIENTBASE_HPP
