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

#ifndef LIBMARL_RESPONSE_BASE_HPP
#define LIBMARL_RESPONSE_BASE_HPP

#include <cstdint>
#include "message-base.hpp"
#include "libmarl-exports.hpp"

namespace marl {

const uint8_t MARL_ACTION_SELECT_RSP = 1;
const uint8_t MARL_UPDATE_TABLE_RSP = 3;

struct LIBMARL_API response_base : public message_base {
    response_base() = default;
    response_base(const response_base&) = default;
    virtual ~response_base() = default;
};

}
#endif // LIBMARL_RESPONSE_BASE_HPP
