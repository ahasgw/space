## $Id: Makefile.am,v 1.8 2005/10/31 03:03:44 aki Exp $
##
## Makefile for the doc directory
## Copyright (C) 2005 RIKEN. All rights reserved.
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

DISTCLEANFILES = space.info
MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = $(man_MANS)

info_TEXINFOS = 
man_MANS = 

info_TEXINFOS += space.texi

HELP2MANFLAGS = -p space

man_MANS += space.1
space.1 : $(top_builddir)/src/space
	if test "x$(HELP2MAN)" != x; \
	then $(HELP2MAN) $(HELP2MANFLAGS) $< > $@; fi

clean-local :
	if test "x$(HELP2MAN)" != x; \
	then rm -f $(man_MANS); fi
