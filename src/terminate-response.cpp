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

#include "response-base.hpp"
#include "terminate-response.hpp"

uint8_t marl::terminate_response::type() const
{
    return MARL_TERMINATE_RSP;
}

marl::message_base* marl::terminate_response::clone() const {
    return new terminate_response(*this);
}
