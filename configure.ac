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

AC_PREREQ([2.69])
AC_INIT([libmarl-protocols], [0.1], [https://github.com/RoyaGh/libmarl-protocols/issues])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_CONFIG_MACRO_DIRS([m4])
LT_INIT([static shared pic-only])

# Configure automake
AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

# Check for C++11 compiler
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AX_PKG_CHECK_MODULES([CPNET],[],[libcpnet >= 1.0])
AX_PKG_CHECK_MODULES([FLOG],[libflog >= 1.0],[])
AX_PKG_CHECK_MODULES([XERCES],[],[xerces-c >= 3.1])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile
                 libmarl_protocols.pc])

AC_SUBST([LIBMARL_SO_VERSION], [1:0:0])
AC_SUBST([LIBMARL_API_VERSION], [1.0.0])

AC_OUTPUT
