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

#ifndef MARL_UPDATE_RESPONSE_HPP
#define MARL_UPDATE_RESPONSE_HPP

#include <cstdint>
#include "response-base.hpp"

namespace marl {

struct LIBMARL_API update_table_rsp : public response_base {
    update_table_rsp() = default;
    ~update_table_rsp() = default;
    float max_q;
    uint8_t type() const override;
};

}

#endif // MARL_UPDATE_RESPONSE_HPP
