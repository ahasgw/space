## $Id: Makefile.am,v 1.5 2005/08/17 10:11:43 aki Exp $
##
## Makefile for the src directory
## Copyright (C) 2004 RIKEN. All rights reserved.
## Written by Aki Hasegawa <aki@gsc.riken.jp>.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES = Makefile.in

dist_sysconf_DATA = space.db.sample
dist_pkgdata_DATA = cmd.example

bin_PROGRAMS = 

AM_CPPFLAGS = -I$(top_srcdir)/libgnu -I$(top_srcdir)/util
AM_CFLAGS = -DNDEBUG

## space
bin_PROGRAMS += space
space_CFLAGS = -DNDEBUG -D_REENTRANT
space_CFLAGS += -DSYSCONFDIR="\"@sysconfdir@\""
space_SOURCES = space.c command.c command.h seqlist.c seqlist.h state.h space.h
space_LDADD = 
space_LDADD += $(top_builddir)/util/libutil.a
space_LDADD += $(top_builddir)/libgnu/libgnu.a
space_LDADD += -lpthread
