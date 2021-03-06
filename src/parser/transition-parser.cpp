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

#include "transition-parser.hpp"
#include <iostream>

marl::transition_parser::transition_parser() : transition_pskel(),
    p{0}, r{0}, s{nullptr} {
    to_parser(m_tparser);
    probability_parser(m_pparser);
    reward_parser(m_decimal_parser);
}

void marl::transition_parser::probability(float _p) {
    p = _p;
}

void marl::transition_parser::reward(double _r) {
    r = static_cast<float>(_r);
}

void marl::transition_parser::to(marl::state* _s) {
    s = _s;
}

marl::transition* marl::transition_parser::post_transition() {
    return new transition(s, p, r);
}

void marl::transition_parser::set_states(const std::vector<marl::state*>& states) {
    m_tparser.set_states(states);
}
