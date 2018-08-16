/*
 * Copyright 2018 - Roya Ghasemzade <roya@ametisco.ir>
 * Copyright 2018 - Soroush Rabiei <soroush@ametisco.ir>
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

#ifndef LIBMARL_TERMINATE_RESPONSE_HPP
#define LIBMARL_TERMINATE_RESPONSE_HPP

#include <cstdint>
#include "message-base.hpp"
#include "libmarl-exports.hpp"

namespace marl {

struct LIBMARL_API terminate_response : public message_base {
    terminate_response() = default;
    terminate_response(const terminate_response&) = default;
    ~terminate_response() = default;
    uint8_t type() const override;
    message_base* clone() const override;
};
}

#endif // LIBMARL_TERMINATE_RESPONSE_HPP
