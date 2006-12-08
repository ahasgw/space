#! /usr/bin/perl -w
########################################################################
## $Id$
##
## space
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
########################################################################

use IO::Socket;

print scalar(@ARGV), "\n";
print $#ARGV, "\n";
print $ARGV[$#ARGV], "\n";

if (@ARGV < 2) {
    print "usage: $ARGV[0] host port\n";
    exit(1);
}

my $remote_host = $ARGV[0];
my $remote_port = $ARGV[1];

my $socket = IO::Socket::INET->new(
	PeerAddr => $remote_host,
	PeerPort => $remote_port,
	Proto => "tcp",
	Type => SOCK_STREAM
    )
    or die "Could not connect to $remote_host:$remote_port: $@\n";

print $socket "list\nquit\n";
while (<$socket>) {
    print $_;
}
close($socket);

print "<<end>>\n";
