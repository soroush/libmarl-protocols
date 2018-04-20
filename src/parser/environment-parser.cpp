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

#include "environment-parser.hpp"

marl::environment_parser::environment_parser() :
    environment_pskel() {
    title_parser(m_string_parser);
    description_parser(m_string_parser);
    states_parser(m_states_parser);
    actions_parser(m_actions_parser);
}

void marl::environment_parser::title(const std::string& name) {
    m_env.set_title(name);
}

void marl::environment_parser::description(const std::string& name) {
    m_env.set_description(name);
}

void marl::environment_parser::states(const ::std::vector<::marl::state*>& states) {
    m_env.set_states(states);
    m_actions_parser.set_states(states);
}

void marl::environment_parser::actions(const std::vector<marl::action*>& actions) {
    m_env.set_actions(actions);
}

marl::environment marl::environment_parser::post_environment() {
    return m_env;
}
