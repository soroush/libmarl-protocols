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

#include "state-pointer-helper.hpp"
#include "../state.hpp"
#include <algorithm>

marl::state* marl::details::state_pointer_helper::find(const std::string& name) const {
    auto predicate = [&name](marl::state * s)->bool { return s->name() == name; };
    auto iterator = std::find_if(m_states.begin(), m_states.end(), predicate);
    if(iterator == m_states.end()) {
        return nullptr;
    } else {
        return *iterator;
    }
}

marl::state* marl::details::state_pointer_helper::find(uint32_t id) const {
    auto predicate = [&id](marl::state * s)->bool { return s->id() == id; };
    auto iterator = std::find_if(m_states.begin(), m_states.end(), predicate);
    if(iterator == m_states.end()) {
        return nullptr;
    } else {
        return *iterator;
    }
}

void marl::details::state_pointer_helper::set_states(const std::vector<marl::state*>& states) {
    m_states = states;
}
