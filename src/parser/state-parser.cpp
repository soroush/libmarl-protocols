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

#include "state-parser.hpp"

void marl::state_parser::id(unsigned long long i) {
    this->m_id = static_cast<uint32_t>(i);
}

void marl::state_parser::title(std::string n) {
    this->m_name = n;
}

marl::state *marl::state_parser::post_state_type() {
    return new marl::state(m_name, m_id);
}
