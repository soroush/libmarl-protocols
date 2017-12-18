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

#include "named-object.hpp"

marl::named_object::named_object() : m_name("<unnamed>"), m_id(0) {
}

marl::named_object::named_object(const std::string& name, uint32_t id) :
    m_name(name),
    m_id(id) {
}

std::string marl::named_object::name() const {
    return this->m_name;
}

void marl::named_object::set_name(const std::string& name) {
    this->m_name = name;
}

uint32_t marl::named_object::id() const {
    return m_id;
}

void marl::named_object::set_id(uint32_t i) {
    m_id = i;
}
