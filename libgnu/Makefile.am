## Process this file with automake to produce Makefile.in.
# Copyright (C) 2004 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Automake, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
# Reproduce by: gnulib-tool --import --dir=.. --lib=libgnu --source-base=libgnu --m4-base=libgnu/m4 --aux-dir=config --macro-prefix=gl assert atexit c-bs-a calloc dirname dummy error exit exitfail findprog free ftruncate getdelim getline getndelim2 getnline getopt getsubopt gettext gettimeofday linebuffer malloc memchr memcmp memcpy memmove memset mktime pathname progname realloc restrict safe-read safe-write sh-quote snprintf ssize_t stdbool stdint strcspn strerror strpbrk strstr strtod strtoimax strtol strtoll strtoul strtoull strtoumax ullong_max vsnprintf xalloc xalloc-die

AUTOMAKE_OPTIONS = 1.5 gnits no-dependencies

noinst_LIBRARIES = libgnu.a

libgnu_a_SOURCES =
libgnu_a_LIBADD = @LIBOBJS@
EXTRA_DIST =
BUILT_SOURCES =
SUFFIXES =
MOSTLYCLEANFILES =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES =

## begin gnulib module alloca-opt

BUILT_SOURCES += $(ALLOCA_H)
EXTRA_DIST += alloca_.h

# We need the following in order to create <alloca.h> when the system
# doesn't have one that works with the given compiler.
alloca.h: alloca_.h
	cp $(srcdir)/alloca_.h $@-t
	mv $@-t $@
MOSTLYCLEANFILES += alloca.h alloca.h-t

## end   gnulib module alloca-opt

## begin gnulib module dirname

libgnu_a_SOURCES += basename.c stripslash.c

## end   gnulib module dirname

## begin gnulib module dummy

libgnu_a_SOURCES += dummy.c

## end   gnulib module dummy

## begin gnulib module exit

libgnu_a_SOURCES += exit.h

## end   gnulib module exit

## begin gnulib module findprog

libgnu_a_SOURCES += findprog.h findprog.c

## end   gnulib module findprog

## begin gnulib module getndelim2

EXTRA_DIST += getndelim2.h getndelim2.c

## end   gnulib module getndelim2

## begin gnulib module getnline

libgnu_a_SOURCES += getnline.h getnline.c

## end   gnulib module getnline

## begin gnulib module getopt

BUILT_SOURCES += $(GETOPT_H)
EXTRA_DIST += getopt_.h getopt_int.h

# We need the following in order to create <getopt.h> when the system
# doesn't have one that works with the given compiler.
getopt.h: getopt_.h
	cp $(srcdir)/getopt_.h $@-t
	mv $@-t $@
MOSTLYCLEANFILES += getopt.h getopt.h-t

## end   gnulib module getopt

## begin gnulib module getsubopt

libgnu_a_SOURCES += getsubopt.h

## end   gnulib module getsubopt

## begin gnulib module gettext-h

libgnu_a_SOURCES += gettext.h

## end   gnulib module gettext-h

## begin gnulib module linebuffer

libgnu_a_SOURCES += linebuffer.h linebuffer.c

## end   gnulib module linebuffer

## begin gnulib module mbchar

libgnu_a_SOURCES += mbchar.h

## end   gnulib module mbchar

## begin gnulib module mbuiter

libgnu_a_SOURCES += mbuiter.h

## end   gnulib module mbuiter

## begin gnulib module minmax

libgnu_a_SOURCES += minmax.h

## end   gnulib module minmax

## begin gnulib module pathname

libgnu_a_SOURCES += pathname.h concatpath.c

## end   gnulib module pathname

## begin gnulib module progname

libgnu_a_SOURCES += progname.h progname.c

## end   gnulib module progname

## begin gnulib module sh-quote

libgnu_a_SOURCES += sh-quote.h sh-quote.c

## end   gnulib module sh-quote

## begin gnulib module size_max

libgnu_a_SOURCES += size_max.h

## end   gnulib module size_max

## begin gnulib module snprintf

libgnu_a_SOURCES += snprintf.h

## end   gnulib module snprintf

## begin gnulib module stdbool

BUILT_SOURCES += $(STDBOOL_H)
EXTRA_DIST += stdbool_.h

# We need the following in order to create <stdbool.h> when the system
# doesn't have one that works.
stdbool.h: stdbool_.h
	sed -e 's/@''HAVE__BOOL''@/$(HAVE__BOOL)/g' < $(srcdir)/stdbool_.h > $@-t
	mv $@-t $@
MOSTLYCLEANFILES += stdbool.h stdbool.h-t

## end   gnulib module stdbool

## begin gnulib module stdint

BUILT_SOURCES += $(STDINT_H)
EXTRA_DIST += stdint_.h

# We need the following in order to create <stdint.h> when the system
# doesn't have one that works with the given compiler.
stdint.h: stdint_.h
	sed -e 's/@''HAVE_LONG_64BIT''@/$(HAVE_LONG_64BIT)/g;s/@''HAVE_LONG_LONG_64BIT@/$(HAVE_LONG_LONG_64BIT)/g' < $(srcdir)/stdint_.h > $@-t
	mv $@-t $@
MOSTLYCLEANFILES += stdint.h stdint.h-t

## end   gnulib module stdint

## begin gnulib module stpcpy

libgnu_a_SOURCES += stpcpy.h

## end   gnulib module stpcpy

## begin gnulib module strchrnul

libgnu_a_SOURCES += strchrnul.h

## end   gnulib module strchrnul

## begin gnulib module strnlen1

libgnu_a_SOURCES += strnlen1.h strnlen1.c

## end   gnulib module strnlen1

## begin gnulib module strpbrk

libgnu_a_SOURCES += strpbrk.h

## end   gnulib module strpbrk

## begin gnulib module strstr

libgnu_a_SOURCES += strstr.h

## end   gnulib module strstr

## begin gnulib module strtod

LIBS += $(POW_LIB)

## end   gnulib module strtod

## begin gnulib module time_r

libgnu_a_SOURCES += time_r.h

## end   gnulib module time_r

## begin gnulib module vasnprintf

libgnu_a_SOURCES += printf-args.h printf-parse.h vasnprintf.h

## end   gnulib module vasnprintf

## begin gnulib module verify

libgnu_a_SOURCES += verify.h

## end   gnulib module verify

## begin gnulib module vsnprintf

libgnu_a_SOURCES += vsnprintf.h

## end   gnulib module vsnprintf

## begin gnulib module xalloc-die

libgnu_a_SOURCES += xalloc-die.c

## end   gnulib module xalloc-die

## begin gnulib module xsize

libgnu_a_SOURCES += xsize.h

## end   gnulib module xsize


# Makefile.am ends here
