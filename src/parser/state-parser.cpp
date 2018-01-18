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

marl::state_parser::state_parser():
    state_pskel(),
    m_id{0},
    m_name{""} {
    id_parser(m_id_parser);
    title_parser(m_title_parser);
}

void marl::state_parser::id(uint32_t i) {
    this->m_id = i;
}

void marl::state_parser::title(std::string n) {
    this->m_name = n;
}

marl::state* marl::state_parser::post_state() {
    return new marl::state(m_name, m_id);
}
