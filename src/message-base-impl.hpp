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

#ifndef MARL_MESSAGE_BASE_IMPL_HPP
#define MARL_MESSAGE_BASE_IMPL_HPP

#include "message-base.hpp"
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/common.hpp>

namespace cereal {
template<class Archive>
void serialize(Archive& archive, marl::message_base& m) {
    archive(m.agent_id, m.confidence, m.request_number);
}
}
CEREAL_REGISTER_TYPE(marl::message_base)

#endif // MARL_MESSAGE_BASE_IMPL_HPP
