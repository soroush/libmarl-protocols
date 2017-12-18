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

#ifndef MARL_REQUEST_BASE_IMPL_HPP
#define MARL_REQUEST_BASE_IMPL_HPP

#include <cereal/types/common.hpp>
#include <cereal/types/polymorphic.hpp>
#include "message-base-impl.hpp"
#include "request-base.hpp"

namespace cereal {
template<class Archive>
void serialize(Archive& archive, marl::request_base& m) {
    archive(cereal::base_class<marl::message_base>(&m),
            m.state_id);
}
}

CEREAL_REGISTER_TYPE(marl::request_base)
CEREAL_REGISTER_POLYMORPHIC_RELATION(marl::message_base, marl::request_base)

#endif // MARL_REQUEST_BASE_IMPL_HPP
