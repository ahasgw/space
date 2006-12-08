# $Id: configure.ac,v 1.13 2005/10/31 03:03:43 aki Exp $
# vi: set tabstop=8 shiftwidth=8 noexpandtab:
#
# Makefile for the toplevel directory
# Copyright (C) 2005 RIKEN. All rights reserved.
# Written by Aki Hasegawa <aki@gsc.riken.jp>.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

AC_PREREQ(2.59)
AC_INIT([SPACE], [0.0.1], [aki@gsc.riken.jp], [space])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_TESTDIR(tests)
gl_EARLY
AM_INIT_AUTOMAKE([1.9])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(ac_aux_dir)
AC_SUBST(AR, [${AR:-ar}])
AC_SUBST(LD, [${LD:-ld}])

# Checks for compiler.

# Checks for programs.
AC_PROG_LN_S
AC_PROG_RANLIB
#AC_PATH_PROG([INETD], [inetd], [/usr/libexec/inetd],
#             [$PATH:/usr/libexec:/usr/sbin:/usr/etc:etc])
AC_PATH_PROG(HELP2MAN, help2man)
AM_MISSING_PROG(AUTOM4TE, autom4te)

# Checks for system services.
AC_SYS_LARGEFILE

# Checks for libraries.
gl_SOURCE_BASE(libgnu)
gl_M4_BASE(libgnu/m4)
gl_LIB(libgnu)
gl_MODULES([c-bs-a assert dummy exit atexit strtod strtol strtoul memchr
 memcmp memcpy memmove memset strcspn strpbrk strstr strerror mktime calloc
 free malloc realloc restrict stdbool stdint ullong_max strtoll strtoull
 strtoimax strtoumax snprintf vsnprintf getsubopt dirname getopt xalloc
 xalloc-die getline error exitfail gettext progname ftruncate getsubopt])
gl_INIT
AC_CHECK_LIB(pthread,pthread_create,,
    AC_MSG_FAILURE([pthread_create is not available]))

# Checks for header files.
AC_CHECK_HEADERS(sys/file.h)
AC_CHECK_HEADERS(sys/param.h)
AC_CHECK_HEADERS(sys/mman.h,,AC_MSG_ERROR([sys/mman.h is not available]))
AC_CHECK_HEADER(pthread.h,,AC_MSG_ERROR([pthread.h is not available]))

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF(off_t)
AC_CHECK_SIZEOF(size_t)

#AM_CONDITIONAL(IS_SIZEOF_OFF_T_EQ_8, test "${ac_cv_sizeof_off_t}" = "8")
#AC_SUBST(IS_SIZEOF_OFF_T_EQ_8)

# Checks for library functions.
AC_CHECK_FUNC(strdup,,AC_MSG_ERROR([strdup is not available]))
AC_CHECK_FUNC(mmap,,AC_MSG_ERROR([mmap is not available]))
AC_CHECK_FUNC(munmap,,AC_MSG_ERROR([munmap is not available]))
AC_CHECK_FUNC(msync,,AC_MSG_ERROR([msync is not available]))

# Output
AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(libgnu/Makefile)
AC_CONFIG_FILES(util/Makefile)
AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(scripts/Makefile)
AC_CONFIG_FILES(tests/Makefile)
AC_CONFIG_FILES(tests/space, [chmod +x tests/space])
AC_CONFIG_FILES(doc/Makefile)
AC_CONFIG_FILES(space.spec)

AC_OUTPUT
