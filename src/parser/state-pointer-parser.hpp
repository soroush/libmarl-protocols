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

#ifndef LIBMARL_STATE_POINTER_PARSER_HPP
#define LIBMARL_STATE_POINTER_PARSER_HPP

#include "state_pointer_type-pskel.hpp"
#include "state-pointer-helper.hpp"

namespace marl {

class state_pointer_parser :
    public state_pointer_type_pskel,
    public details::state_pointer_helper,
    public xml_schema::string_pimpl {
public:
    marl::state* post_state_pointer_type() override;
};
}

#endif // LIBMARL_STATE_POINTER_PARSER_HPP
