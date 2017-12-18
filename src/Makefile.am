# Copyright 2017 - Roya Ghasemzade <roya@ametisco.ir>
# Copyright 2017 - Soroush Rabiei <soroush@ametisco.ir>
#
# This file is part of libmarl_protocols.
#
# libmarl_protocols is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libmarl_protocols is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libmarl_protocols.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

AM_CXXFLAGS = --pedantic -Wall -Werror -DBUILD_LIBMARL_PROTOCOLS

lib_LTLIBRARIES = libmarl_protocols.la

libmarl_protocols_la_CPPFLAGS = \
    $(XERCES_CFLAGS)

libmarl_protocols_la_LDFLAGS = -version-info $(LIBMARL_SO_VERSION)
libmarl_protocols_la_LDFLAGS += -fvisibility=hidden

libmarl_protocols_includedir = $(includedir)/libmarl-protocols
nobase_libmarl_protocols_include_HEADERS =  \
    libmarl-exports.hpp \
    details/named-object.hpp \
    parser/environment-parser.hpp \
    parser/from-pskel.hpp \
    parser/title-pskel.hpp \
    parser/to-pskel.hpp \
    parser/environment-pskel.hpp \
    parser/probability-pskel.hpp \
    parser/state_type-pskel.hpp \
    parser/transition_type-pskel.hpp \
    parser/states_type-pskel.hpp \
    parser/actions_type-pskel.hpp \
    parser/environment_type-pskel.hpp \
    parser/action_type-pskel.hpp \
    semaphore.hpp \
    message-base.hpp \
    client-base.hpp \
    request-base.hpp \
    action-select-request.hpp \
    action-select-response.hpp \
    update-table-request.hpp \
    update-table-response.hpp \
    response-base.hpp \
    state.hpp \
    transition.hpp \
    action.hpp \
    environment.hpp

nobase_libmarl_protocols_include_HEADERS +=  \
    parser/state-parser.hpp \
    parser/states-parser.hpp \
    parser/action-parser.hpp \
    parser/actions-parser.hpp \
    parser/probability-parser.hpp \
    parser/state-pointer-helper.hpp \
    parser/from-parser.hpp \
    parser/transition-parser.hpp

libmarl_protocols_la_SOURCES = \
    $(libmarl_protocols_include_HEADERS) \
    details/named-object.cpp \
    parser/environment-parser.cpp \
    parser/to-pskel.cpp \
    parser/environment-pskel.cpp \
    parser/probability-pskel.cpp \
    parser/from-pskel.cpp \
    parser/title-pskel.cpp \
    parser/state_type-pskel.cpp \
    parser/transition_type-pskel.cpp \
    parser/states_type-pskel.cpp \
    parser/actions_type-pskel.cpp \
    parser/action_type-pskel.cpp \
    parser/environment_type-pskel.cpp \
    semaphore.cpp \
    message-base.cpp \
    message-base-impl.hpp \
    client-base.cpp \
    request-base.cpp \
    request-base-impl.hpp \
    action-select-request.cpp \
    action-select-request-impl.hpp \
    action-select-response.cpp \
    action-select-response-impl.hpp \
    update-table-request.cpp \
    update-table-request-impl.hpp \
    update-table-response.cpp \
    update-table-response-impl.hpp \
    response-base.cpp \
    response-base-impl.hpp \
    state.cpp \
    transition.cpp \
    action.cpp \
    environment.cpp

libmarl_protocols_la_SOURCES += \
    parser/state-parser.cpp \
    parser/states-parser.cpp \
    parser/action-parser.cpp \
    parser/actions-parser.cpp \
    parser/probability-parser.cpp \
    parser/state-pointer-helper.cpp \
    parser/to-parser.cpp \
    parser/from-parser.cpp \
    parser/transition-parser.cpp

libmarl_protocols_la_LIBADD = \
    $(XERCES_LIBS)
