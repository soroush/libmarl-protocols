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

#include "../src/update-table-request.hpp"
#include "../src/update-table-request-impl.hpp"
#include "../src/update-table-response.hpp"
#include "../src/update-table-response-impl.hpp"
#include "../src/action-select-request.hpp"
#include "../src/action-select-request-impl.hpp"
#include "../src/action-select-response.hpp"
#include "../src/action-select-response-impl.hpp"
#include "../src/start-request.hpp"
#include "../src/start-request-impl.hpp"
#include <cereal/archives/binary.hpp>
#include <sstream>
#include <random>
#include <limits>
#include <cassert>
#include <iostream>

int main() {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<uint32_t> uniform_dist(
        std::numeric_limits<uint32_t>::min(),
        std::numeric_limits<uint32_t>::max());
    std::uniform_real_distribution<float> uniform_rdist(
        std::numeric_limits<float>::min(),
        std::numeric_limits<float>::max());
    const size_t test_size = 1.0e+02;
    for(size_t i = 0; i < test_size; ++i) {
        std::stringstream str_out;
        cereal::BinaryOutputArchive ar_out(str_out);
        std::stringstream str_in;
        cereal::BinaryInputArchive ar_in(str_in);
        marl::update_table_req req1;
        req1.agent_id = uniform_dist(e1);
        req1.confidence = uniform_rdist(e1);
        req1.request_number = uniform_dist(e1);
        req1.state_id = uniform_dist(e1);
        ar_out(req1);
        str_in.str(str_out.str());
        marl::update_table_req req2;
        ar_in(req2);
        assert(req1.state_id == req2.state_id &&
               req1.agent_id == req2.agent_id &&
               req1.confidence == req2.confidence &&
               req1.request_number == req2.request_number);
    }
    for(size_t i = 0; i < test_size; ++i) {
        std::stringstream str_out;
        cereal::BinaryOutputArchive ar_out(str_out);
        std::stringstream str_in;
        cereal::BinaryInputArchive ar_in(str_in);
        marl::update_table_rsp rsp1;
        rsp1.agent_id = uniform_dist(e1);
        rsp1.confidence = uniform_rdist(e1);
        rsp1.request_number = uniform_dist(e1);
        rsp1.max_q = uniform_rdist(e1);
        ar_out(rsp1);
        str_in.str(str_out.str());
        marl::update_table_rsp rsp2;
        ar_in(rsp2);
        assert(rsp1.max_q == rsp2.max_q &&
               rsp1.agent_id == rsp2.agent_id &&
               rsp1.confidence == rsp2.confidence &&
               rsp1.request_number == rsp2.request_number);
    }

    for(size_t i = 0; i < test_size; ++i) {
        std::stringstream str_out;
        cereal::BinaryOutputArchive ar_out(str_out);
        std::stringstream str_in;
        cereal::BinaryInputArchive ar_in(str_in);
        marl::action_select_req req1;
        req1.agent_id = uniform_dist(e1);
        req1.confidence = uniform_rdist(e1);
        req1.request_number = uniform_dist(e1);
        req1.state_id = uniform_dist(e1);
        ar_out(req1);
        str_in.str(str_out.str());
        marl::action_select_req req2;
        ar_in(req2);
        assert(req1.state_id == req2.state_id &&
               req1.agent_id == req2.agent_id &&
               req1.confidence == req2.confidence &&
               req1.request_number == req2.request_number);
    }
    for(size_t i = 0; i < test_size; ++i) {
        std::stringstream str_out;
        cereal::BinaryOutputArchive ar_out(str_out);
        std::stringstream str_in;
        cereal::BinaryInputArchive ar_in(str_in);
        marl::action_select_rsp rsp1;
        rsp1.agent_id = uniform_dist(e1);
        rsp1.confidence = uniform_rdist(e1);
        rsp1.request_number = uniform_dist(e1);
        uint32_t vector_size = uniform_dist(e1) % 1000;
        for(uint32_t i = 0; i < vector_size; ++i) {
            marl::action_info info;
            info.action = uniform_dist(e1);
            info.state = uniform_dist(e1);
            info.q_value = uniform_rdist(e1);
            info.confidence = uniform_rdist(e1);
            rsp1.info.push_back(info);
        }
        ar_out(rsp1);
        str_in.str(str_out.str());
        marl::action_select_rsp rsp2;
        ar_in(rsp2);
        assert(rsp1.agent_id == rsp2.agent_id &&
               rsp1.confidence == rsp2.confidence &&
               rsp1.request_number == rsp2.request_number);
        assert(rsp1.info.size() == rsp2.info.size());
        for(size_t i = 0; i < rsp1.info.size(); ++i) {
            assert(rsp1.info.at(i).action == rsp2.info.at(i).action &&
                   rsp1.info.at(i).state == rsp2.info.at(i).state &&
                   rsp1.info.at(i).q_value == rsp2.info.at(i).q_value &&
                   rsp1.info.at(i).confidence == rsp2.info.at(i).confidence);
        }
    }
    // Start Request
    for(size_t i = 0; i < test_size; ++i) {
        std::stringstream str_out;
        cereal::BinaryOutputArchive ar_out(str_out);
        std::stringstream str_in;
        cereal::BinaryInputArchive ar_in(str_in);
        marl::start_req req1;
        req1.agent_id = uniform_dist(e1);
        req1.agent_count = uniform_dist(e1);
        req1.confidence = uniform_rdist(e1);
        req1.request_number = uniform_dist(e1);
        req1.state_id = uniform_dist(e1);
        ar_out(req1);
        std::string x = str_out.str();
        std::cerr << x.size() << std::endl;
        str_in.str(x);
        marl::start_req req2;
        ar_in(req2);
        assert(req1.state_id == req2.state_id &&
               req1.agent_count == req2.agent_count &&
               req1.agent_id == req2.agent_id &&
               req1.confidence == req2.confidence &&
               req1.request_number == req2.request_number);
    }
    return 0;
}

