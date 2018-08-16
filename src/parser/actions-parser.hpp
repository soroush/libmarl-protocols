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

#ifndef LIBMARL_ACTIONS_PARSER_HPP
#define LIBMARL_ACTIONS_PARSER_HPP

#include "actions-pskel.hpp"
#include "action-parser.hpp"
#include <vector>

namespace marl {
class actions_parser : public actions_pskel {
public:
    actions_parser();
    void action(::marl::action*) override;
    std::vector<marl::action*> post_actions() override;
    void set_states(const std::vector<marl::state*>& states);
private:
    std::vector<marl::action*> m_actions;
    marl::action_parser m_aparser;
};
}

#endif // LIBMARL_ACTION_PARSER_HPP
