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

#include "../src/parser/environment-parser.hpp"
#include <iostream>

int main() {
    try {
        marl::environment_parser mdp_parser;
        xml_schema::document doc_p(mdp_parser, "environment",
                                   xml_schema::flags::dont_validate);
        mdp_parser.pre();
        const std::string path{"sample.xml"};
        doc_p.parse(path);
        marl::environment e = mdp_parser.post_environment();
        std::cout << "States (Count=" << e.states().size() << ")\n";
        for(const auto& s : e.states()) {
            std::cout << s->id()
                      << ": '" << s->name() << "'\n";
        }
        std::cout << "Actions (Count=" << e.actions().size() << ")\n";
        for(const auto& a : e.actions()) {
            std::cout << a->id() << " : '" << a->name() << "' ,Size: " <<
                      a->transitions().size() << "\n";
            for(const auto& t : a->transitions()) {
                std::cout << a->from()->name()
                          << " => " << t->to()->name()
                          << " (" << t->probability() * 100.0 << "%, "
                          << t->reward() << ")\n";
            }
        }
    } catch(const xml_schema::exception& e) {
        std::cout << e << ::std::endl;
        return 1;
    }
    return 0;
}

