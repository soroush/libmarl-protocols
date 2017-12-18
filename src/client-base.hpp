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
#include <cpnet/cpnet-network.h>
#include "semaphore.hpp"
#include "message-base.hpp"
#include "request-base.hpp"
#include "response-base.hpp"
#include "libmarl-exports.hpp"

namespace marl {

class LIBMARL_API client_base {
public:
    client_base();
    virtual ~client_base() = default;
    bool connect(const std::string& address, uint16_t port);
    void send_message(const message_base* const);
    response_base* get_response(uint32_t request_id);
protected:
    virtual void process_request(const request_base* const) = 0;
private:
    void receive_messages();
    void request_broaker();
    tidm::semaphore request_sem;
    tidm::semaphore response_sem;
    std::mutex request_lock;
    std::mutex response_lock;
    std::mutex transmit_lock;
    std::list<request_base*> m_requests;
    std::list<response_base*> m_responses;
    socket_t m_socket;
};

}

#endif // LIBMARL_CLIENTBASE_HPP
