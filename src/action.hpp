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

#ifndef LIBMARL_ACTION_HPP
#define LIBMARL_ACTION_HPP

#include "transition.hpp"
#include "details/named-object.hpp"
#include <vector>
#include <cstdint>

namespace marl {

class state;
class transition;

class action : public named_object {
public:
    action();
    action(const std::string& name, uint32_t id, marl::state* initial);
    ~action() = default;
    marl::state* from() const;
    void add_transition(marl::transition*);
    void set_transitions(std::vector<marl::transition*>&&);
    std::vector<marl::transition*> transitions() const;
private:
    std::vector<marl::transition*> m_transitions;
    marl::state* m_initial_state;
};
}

#endif // LIBMARL_ACTION_HPP
