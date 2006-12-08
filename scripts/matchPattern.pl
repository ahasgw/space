#! /usr/bin/perl -w
########################################################################
## $Id$
##
## sample client
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

if (@ARGV < 3) {
    print "usage: $ARGV[0] host port pattern ...\n";
    exit(1);
}

my $remote_host = shift(@ARGV);
my $remote_port = shift(@ARGV);
my @query_patterns = @ARGV;

my $socket = IO::Socket::INET->new(
	PeerAddr => $remote_host,
	PeerPort => $remote_port,
	Proto => "tcp",
	Type => SOCK_STREAM
    )
    or die "Could not connect to $remote_host:$remote_port: $@\n";

print $socket "list\n";
while (<$socket>) {
    print $_;
    last if ($_ eq "\n");
}

print $socket "select 0\n";
print $socket "match " . join(" ", @query_patterns) . "\n";
print $socket "quit\n";
while (<$socket>) {
    print $_;
    last if ($_ eq "\n");
}


close($socket);
print "<<end>>\n";
