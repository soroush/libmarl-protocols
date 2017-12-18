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

#ifndef MARL_RESPONSE_BASE_IMPL_HPP
#define MARL_RESPONSE_BASE_IMPL_HPP

#include <cereal/types/common.hpp>
#include <cereal/types/polymorphic.hpp>
#include "message-base-impl.hpp"
#include "response-base.hpp"

namespace cereal {
template<class Archive>
void serialize(Archive& archive, marl::response_base& m) {
    archive(cereal::base_class<marl::message_base>(&m));
}
}

CEREAL_REGISTER_TYPE(marl::response_base)
CEREAL_REGISTER_POLYMORPHIC_RELATION(marl::message_base, marl::response_base)

#endif // MARL_RESPONSE_BASE_IMPL_HPP
