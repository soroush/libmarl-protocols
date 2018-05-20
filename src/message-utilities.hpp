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

#ifndef MESSAGE_UTILITIES_HPP
#define MESSAGE_UTILITIES_HPP

#include <flog/flog.hpp>
#include <sstream>
#include <string.h>
#include <cereal/archives/binary.hpp>
#include <cpnet/cpnet-network.h>
#include "message-base.hpp"

namespace marl {

#define DBUFSIZE 8192
#define HEADSIZE (sizeof(uint32_t))

std::unique_ptr<marl::message_base> receive_message(socket_t socket);

template<typename message>
bool send_message_helper(const message& msg, socket_t& socket) {
    flog::logger* l = flog::logger::instance();
    std::stringstream str_out;
    cereal::BinaryOutputArchive ar_out(str_out);
    std::unique_ptr<marl::message_base> msg_ptr{msg.clone()};
    ar_out(msg_ptr);
    std::string buffer = str_out.str();
    size_t new_size = buffer.size() + HEADSIZE;
    char* raw_buffer = new char[new_size];
    uint32_t size = htonl(static_cast<uint32_t>(buffer.size()));
    memcpy(raw_buffer, &size, HEADSIZE);
    memcpy(raw_buffer + HEADSIZE, buffer.data(), buffer.size());
    /*
    l->log(flog::level_t::TRACE, "Sending message...");
    l->logc(flog::level_t::TRACE, "Data size   : %d", buffer.size());
    l->logc(flog::level_t::TRACE, "Packet size : %d", buffer.size());
    */
    if(cpnet_write(socket, raw_buffer, new_size) <= 0) {
        l->log(flog::level_t::ERROR_, "Unable to write data on socket!");
        l->log(flog::level_t::ERROR_, "Network backend returned error: %s",
               cpnet_last_error());
        delete[] raw_buffer;
        return false;
    }
    delete[] raw_buffer;
    return true;
}

template<typename message>
bool receive_message_helper(message& msg, socket_t& socket) {
    flog::logger* l = flog::logger::instance();
    std::unique_ptr<marl::message_base> msg_ptr = receive_message(socket);
    if(!msg_ptr) {
        l->log(flog::level_t::ERROR_,
               "Deserialized `message_base' pointer is null.");
        return false;
    }
    message* typed_ptr = dynamic_cast<message*>(msg_ptr.get());
    if(!typed_ptr) {
        l->log(flog::level_t::ERROR_,
               "Unable to cast pointer of `message_base' type to requested object.");
        return false;
    } else {
        msg = *typed_ptr;
    }
    return true;
}

}

#endif // MESSAGE_UTILITIES_HPP
