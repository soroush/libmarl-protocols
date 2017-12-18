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

#ifndef LIBMARL_NAMED_OBJECT_HPP
#define LIBMARL_NAMED_OBJECT_HPP

#include <string>
#include <cstdint>

namespace marl {
class named_object {
public:
    named_object();
    named_object(const std::string& name, uint32_t id);
    ~named_object() = default;
    std::string name() const;
    void set_name(const std::string& name);
    uint32_t id() const;
    void set_id(uint32_t);
protected:
    std::string m_name;
    uint32_t m_id;
};
}

#endif // LIBMARL_NAMED_OBJECT_HPP
