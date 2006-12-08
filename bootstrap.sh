#! /bin/sh
#
# $Id: bootstrap.sh,v 1.2 2005/10/31 03:03:43 aki Exp $
#
# Bootstrapping
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

set -x
if test ! -d ./config; then
	mkdir config
fi
aclocal -I config -I libgnu/m4
autoheader
automake --add-missing --copy
autoconf
