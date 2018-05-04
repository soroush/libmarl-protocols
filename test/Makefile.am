# Copyright 2017, 2018 - Roya Ghasemzade <roya@ametisco.ir>
# Copyright 2017, 2018 - Soroush Rabiei <soroush@ametisco.ir>
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

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = \
    -I$(srcdir)/.. \
    $(CPNET_CFLAGS) \
    $(XERCES_CFLAGS)

AM_CXXFLAGS = --pedantic -Wall -Werror

check_PROGRAMS = \
    tst_serialize \
    tst_parser \
    tst_agent

tst_serialize_SOURCES = \
    tst-serialize.cpp

tst_parser_SOURCES = \
    tst-parser.cpp

tst_server_SOURCES = \
    tst-server.cpp

tst_agent_SOURCES = \
    tst-agent.cpp

LDADD = \
    ../src/libmarl_protocols.la \
    $(CPNET_LIBS) \
    $(XERCES_LIBS)

TESTS = $(check_PROGRAMS)
