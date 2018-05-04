/*
 * Copyright 2017, 2018 - Roya Ghasemzade <roya@ametisco.ir>
 * Copyright 2017, 2018 - Soroush Rabiei <soroush@ametisco.ir>
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

#include "../src/client-base.hpp"
#include "../src/request-base.hpp"
#include "../src/response-base.hpp"
#include "../src/action-select-response.hpp"
#include <iostream>

namespace marl {
class test_client : public client_base {
protected:
    response_base* process_request(const request_base* const req) override {
        if(!req) {
            return nullptr;
        }
        switch(req->type()) {
            case MARL_ACTION_SELECT_REQ:
                action_select_rsp* result = new action_select_rsp;
                result->agent_id = req->agent_id + 1;
                result->confidence = req->confidence * 2.0;
                result->request_number = req->request_number;
                break;
        }
    }

};
}

int main() {

    return 0;
}

