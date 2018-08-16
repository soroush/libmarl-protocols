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

#include "message-utilities.hpp"
#include "message-base-impl.hpp"

std::unique_ptr<marl::message_base> marl::receive_message(socket_t socket) {
    flog::logger* l = flog::logger::instance();
    char data_buffer[DBUFSIZE];
    char header_buffer[HEADSIZE];
    ssize_t read_size = cpnet_read(socket, header_buffer, HEADSIZE);
    if(read_size != HEADSIZE) {
        l->log(flog::level_t::ERROR_,
               "Unable to read header from incomming connection.");
        l->logc(flog::level_t::ERROR_, "Read header size: %zu", read_size);
        return nullptr;
    }
    uint32_t expected_size = 0;
    memcpy(&expected_size, header_buffer, HEADSIZE);
    expected_size = ntohl(expected_size);
    uint32_t total_read = 0;
    std::stringstream istr;
    while(total_read < expected_size) {
        read_size = cpnet_read(socket, data_buffer, expected_size - total_read);
        if(read_size < 0) {
            l->log(flog::level_t::ERROR_,
                   "Unable to read data from incomming connection. Error: %s",
                   cpnet_last_error());
            return nullptr;
        }
        total_read += read_size;
        istr.write(data_buffer, read_size);
    }
    if(expected_size != total_read) {
        l->log(flog::level_t::ERROR_,
               "Expected incomming buffer size was %d, bit %d received.",
               expected_size, total_read);
        return nullptr;
    }
    // Process incomming message: construct buffers
    std::unique_ptr<message_base> msg;
    try {
        cereal::BinaryInputArchive archiver(istr);
        archiver(msg);
    } catch(cereal::Exception& e) {
        l->log(flog::level_t::ERROR_, "Unable to deserialize buffer into `message_base' object.");
        l->logc(flog::level_t::ERROR_, "Serialization error: %s", e.what());
        return nullptr;
    }
    return msg;
}
