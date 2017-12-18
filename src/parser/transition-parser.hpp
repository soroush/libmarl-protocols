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

#include "transition_type-pskel.hpp"

#ifndef LIBMARL_TRANSITION_PARSER_HPP
#define LIBMARL_TRANSITION_PARSER_HPP

namespace marl {

class transition_parser : public transition_type_pskel {
public:
    void probability(float) override;
    void reward(double) override;
    void to(marl::state*) override;
    marl::transition *post_transition_type() override;
private:
    float p;
    float r;
    marl::state* s;
};

}

#endif
