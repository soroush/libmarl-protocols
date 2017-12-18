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

#include "transition.hpp"
#include "state.hpp"

marl::transition::transition() :
    m_target(nullptr),
    m_probability(0.0),
    m_reward(0.0) {
}

marl::transition::transition(marl::state* target,
                             float probability,
                             float reward) :
    m_target(target),
    m_probability(probability),
    m_reward(reward) {
}

const marl::state* marl::transition::to() const {
    return this->m_target;
}

void marl::transition::set_target(marl::state* target) {
    m_target = target;
}

float marl::transition::probability() const {
    return this->m_probability;
}

void marl::transition::set_probability(float p) {
    this->m_probability = p;
}

float marl::transition::reward() const {
    return this->m_reward;
}

void marl::transition::set_reward(float r) {
    this->m_reward = r;
}
