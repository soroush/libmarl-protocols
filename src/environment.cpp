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

#include "environment.hpp"
#include "state.hpp"
#include "action.hpp"

void marl::environment::set_title(const std::string& title) {
    m_title = title;
}

void marl::environment::set_description(const std::string& description) {
    m_description = description;
}

void marl::environment::set_states(const std::vector<marl::state*>& states) {
    m_states = states;
}

void marl::environment::set_actions(const std::vector<marl::action*>& actions) {
    m_actions = actions;
}

std::string marl::environment::title() const {
    return m_title;
}

std::string marl::environment::description() const {
    return m_description;
}

std::vector<marl::state*> marl::environment::states() const {
    return m_states;
}

std::vector<marl::action*> marl::environment::actions() const {
    return m_actions;
}
