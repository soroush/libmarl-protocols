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

#ifndef LIBMARL_ENVIORNMENT_PARSER_HPP
#define LIBMARL_ENVIORNMENT_PARSER_HPP

#include "environment-pskel.hpp"
#include "states-parser.hpp"
#include "actions-parser.hpp"

namespace marl {

class environment_parser: public environment_pskel {
public:
    environment_parser();
    void title(const std::string&) override;
    void description(const std::string&) override;
    void states(const std::vector<::marl::state*>&) override;
    void actions(const std::vector<::marl::action*>&) override;
    environment post_environment() override;
private:
    xml_schema::string_pimpl m_string_parser;
    marl::states_parser m_states_parser;
    marl::actions_parser m_actions_parser;
    marl::environment m_env;
};

}

#endif // LIBMARL_ENVIORNMENT_PARSER_HPP
