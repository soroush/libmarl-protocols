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

#ifndef LIBMARL_STATE_POINTER_HELPER_HPP
#define LIBMARL_STATE_POINTER_HELPER_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace marl {

class state;

namespace details {
class state_pointer_helper {
public:
    state_pointer_helper() = default;
    virtual ~state_pointer_helper() = default;
    void set_states(const std::vector<marl::state*>& states);
protected:
    marl::state* find(const std::string& name) const;
    marl::state* find(uint32_t id) const;
    std::vector<marl::state*> m_states;
};
}
}

#endif // LIBMARL_STATE_POINTER_HELPER_HPP
