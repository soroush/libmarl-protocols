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

#include "action-parser.hpp"

marl::action_parser::action_parser() :
		action_pskel(), i{0}, f(nullptr) {
	this->from_parser(m_fparser);
	this->transition_parser(m_tparser);
	this->title_parser(m_title_parser);
	this->id_parser(m_id_parser);
}

void marl::action_parser::transition(marl::transition* t) {
	this->m_transitions.push_back(t);
}

void marl::action_parser::id(uint32_t _i) {
	this->i = _i;

}

void marl::action_parser::from(marl::state* s) {
	this->f = s;
}

void marl::action_parser::title(std::string n) {
	this->t = n;
}

marl::action* marl::action_parser::post_action() {
	marl::action* a = new marl::action(t, i, f);
	a->set_transitions(std::move(m_transitions));
	return a;
}

void marl::action_parser::set_states(const std::vector<marl::state*>& states) {
	m_fparser.set_states(states);
	m_tparser.set_states(states);
}

void marl::action_parser::pre() {
	m_transitions.clear();
}
