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

#ifndef LIBMARL_ACTION_PARSER_HPP
#define LIBMARL_ACTION_PARSER_HPP

#include "action-pskel.hpp"
#include "transition-parser.hpp"
#include "state-pointer-parser.hpp"
#include "id-parser.hpp"
#include "title-parser.hpp"
#include <vector>

namespace marl {
class action_parser : public action_pskel {
public:
	action_parser();
    void transition(marl::transition*) override;
    void id(uint32_t) override;
    void from(marl::state*) override;
    void title(std::string) override;
    marl::action* post_action() override;
    void set_states(const std::vector<marl::state*>& states);
    void pre() override;
private:
    marl::state_pointer_parser m_fparser;
    marl::transition_parser m_tparser;
    marl::title_parser m_title_parser;
    marl::id_parser m_id_parser;
    std::vector<marl::transition*> m_transitions;
    uint32_t i;
    marl::state* f;
    std::string t;
};
}

#endif // LIBMARL_ACTION_PARSER_HPP
