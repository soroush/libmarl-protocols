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

#ifndef MARL_ACTION_SELECT_RESPONSE_HPP
#define MARL_ACTION_SELECT_RESPONSE_HPP

#include <cstdint>
#include <vector>
#include "response-base.hpp"
#include "libmarl-exports.hpp"

namespace marl {

struct LIBMARL_API action_info {
    uint32_t action;
    uint32_t state;
    float q_value;
    float confidence;
};

struct LIBMARL_API action_select_rsp : public response_base {
    std::vector<action_info> info;
    uint8_t type() const;
};

}

#endif // MARL_ACTION_SELECT_RESPONSE_HPP
