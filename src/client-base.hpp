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
#include "request-base.hpp"
#include "response-base.hpp"
#include "action-select-request.hpp"
#include "action-select-response.hpp"
#include "libmarl-exports.hpp"

namespace marl {

enum class operation_mode_t {
    single,
    multi,
};

enum class learning_mode_t {
    learn,
    exploit,
};

class LIBMARL_API client_base {
public:
    client_base();
    virtual ~client_base();
    bool connect(const std::string& address, uint16_t port);
    void send_message(const action_select_req&);
    void send_message(const action_select_rsp&);
    response_base* get_response(uint32_t request_id);
    void start();
    void wait();
    void stop();
    void set_id(uint32_t id);
    uint32_t id() const;
    void initialize(operation_mode_t, learning_mode_t);
    bool initialize(const std::string& path, uint32_t start = 0, uint32_t id = 0);
    uint32_t iterations() const;
    void set_iterations(uint32_t);
protected:
    virtual void run() = 0;
    virtual action_select_rsp process_request(const action_select_req&) = 0;
    uint32_t m_id;
    // Module
    std::atomic_bool m_is_running;
    // Envirinment
    environment m_env;
    // Settings
    uint32_t m_start_index;
    operation_mode_t m_operation_mode;
    learning_mode_t m_learning_mode;
    uint32_t m_iterations;
    bool join();
private:
    void response_worker();
    void receiver_worker();
    tidm::semaphore m_requests_sem;
    tidm::semaphore m_responses_sem;
    std::mutex m_request_lock;
    std::mutex m_response_lock;
    std::thread m_sender;
    std::thread m_receiver;
    std::thread m_main_loop;
    socket_t m_socket;
    // Incomming message queues
    std::list<request_base*> m_requests;
    std::list<response_base*> m_responses;
};

}

#endif // LIBMARL_CLIENTBASE_HPP
