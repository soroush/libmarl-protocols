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

#include "action.hpp"
#include "state.hpp"
#include <memory>

marl::action::action() :
    marl::named_object(),
    m_initial_state{nullptr} {
}

marl::action::action(const std::string& name,
                     uint32_t id, marl::state* state):
    marl::named_object(name, id),
    m_initial_state{state} {
    if(state) {
        m_initial_state->m_actions.push_back(this);
    }
}

marl::state* marl::action::from() const {
    return this->m_initial_state;
}


void marl::action::add_transition(marl::transition* t) {
    m_transitions.push_back(t);
}

void marl::action::set_transitions(std::vector<marl::transition*>&& t) {
    m_transitions = t;
    m_initial_state->m_actions.push_back(this);
}

std::vector<marl::transition*> marl::action::transitions() const {
    return m_transitions;
}
