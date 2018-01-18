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
    $(CPNET_CFLAGS) \
    $(FLOG_CFLAGS) \
    $(XERCES_CFLAGS)

libmarl_protocols_la_LIBADD = \
    $(CPNET_LIBS) \
    $(FLOG_LIBS) \
    $(XERCES_LIBS)

libmarl_protocols_la_LDFLAGS = -version-info $(LIBMARL_SO_VERSION)
libmarl_protocols_la_LDFLAGS += -fvisibility=hidden

libmarl_protocols_includedir = $(includedir)/libmarl-protocols
nobase_libmarl_protocols_include_HEADERS =  \
    libmarl-exports.hpp \
    details/named-object.hpp \
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

libmarl_protocols_la_SOURCES = \
    details/named-object.cpp \
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

# Parser implementation

nobase_libmarl_protocols_include_HEADERS +=  \
    parser/mdp-pskel.hpp \
    parser/environment-pskel.hpp \
    parser/environment-parser.hpp \
    parser/state-pskel.hpp \
    parser/state-parser.hpp \
    parser/states-pskel.hpp \
    parser/states-parser.hpp \
    parser/state_pointer_type-pskel.hpp \
    parser/probability-parser.hpp \
    parser/probability_type-pskel.hpp \
    parser/state-pointer-parser.hpp \
    parser/state-pointer-helper.hpp \
    parser/transition-parser.hpp \
    parser/transition-pskel.hpp \
    parser/title-parser.hpp \
    parser/title_type-pskel.hpp \
    parser/id-parser.hpp \
    parser/action-parser.hpp \
    parser/action-pskel.hpp \
    parser/actions-parser.hpp \
    parser/actions-pskel.hpp


libmarl_protocols_la_SOURCES += \
    parser/mdp-pskel.cpp \
    parser/environment-pskel.cpp \
    parser/environment-parser.cpp \
    parser/state-pskel.cpp \
    parser/state-parser.cpp \
    parser/states-pskel.cpp \
    parser/states-parser.cpp \
    parser/state_pointer_type-pskel.cpp \
    parser/probability-parser.cpp \
    parser/probability_type-pskel.cpp \
    parser/state-pointer-parser.cpp \
    parser/state-pointer-helper.cpp \
    parser/transition-parser.cpp \
    parser/transition-pskel.cpp \
    parser/title-parser.cpp \
    parser/title_type-pskel.cpp \
    parser/id-parser.cpp \
    parser/action-parser.cpp \
    parser/action-pskel.cpp \
    parser/actions-parser.cpp \
    parser/actions-pskel.cpp
