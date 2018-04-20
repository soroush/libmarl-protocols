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

#ifndef LIBMARL_ENVIRONMENT_HPP
#define LIBMARL_ENVIRONMENT_HPP

#include <string>
#include <vector>

namespace marl {

class state;
class action;

class environment {
public:
    environment() = default;
    environment(const environment&) = default;
    void set_title(const std::string& title);
    void set_description(const std::string& description);
    void set_states(const std::vector<marl::state*>&);
    void set_actions(const std::vector<marl::action*>&);
    std::string title() const;
    std::string description() const;
    std::vector<marl::state*> states() const;
    std::vector<marl::action*> actions() const;
protected:
    std::string m_title;
    std::string m_description;
    std::vector<marl::state*> m_states;
    std::vector<marl::action*> m_actions;
};

}

#endif // LIBMARL_ENVIRONMENT_HPP
