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

marl::client_base::client_base() {
//    cpnet_init();
}

bool marl::client_base::connect(const std::string& address, uint16_t port) {
//    m_socket = cpnet_socket(SOCK_STREAM);
//    if(m_socket <= 0) {
//        // TODO: log
//        return false;
//    }
//    if(cpnet_connect(m_socket, address.c_str(), port) != 0 ) {
//        // TODO: log
//        return false;
//    }
    return true;
}
