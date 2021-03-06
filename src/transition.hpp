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

#ifndef LIBMARL_TARNSITION_HPP
#define LIBMARL_TARNSITION_HPP


namespace marl {

class state;

class transition {
public:
    transition();
    transition(marl::state* target,
               float probability,
               float reward);
    ~transition() = default;
    marl::state* to() const;
    void set_target(marl::state* target);
    float probability() const;
    void set_probability(float p);
    float reward() const;
    void set_reward(float r);
private:
    marl::state* m_target;
    float m_probability;
    float m_reward;
};
}

#endif // LIBMARL_TARNSITION_HPP
