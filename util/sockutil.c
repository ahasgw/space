/***********************************************************************
 * $Id: msg.c,v 1.2 2005/07/05 05:12:57 aki Exp $
 *
 * socket utilities
 * Copyright (C) 2005 RIKEN. All rights reserved.
 * Written by Aki Hasegawa <aki@gsc.riken.jp>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 ***********************************************************************/

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include <config.h>
#endif

//#include <stdio.h>
#include <stdlib.h>
//#include <stddef.h>
//#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SYSLOG_OPTION	    (LOG_CONS|LOG_PERROR|LOG_PID)
#define SYSLOG_FACILITY	    (LOG_DAEMON)
#define SYSLOG_PRIORITY	    (LOG_USER|LOG_DEBUG)

/*======================================================================
 * messaging function
 *======================================================================*/

int setup_server_socket(const char *host_name, const char *port_number)
{
    int so = -1;
    struct sockaddr_in my;

    /* initialize sockaddr_in */
    memset(&my, 0, sizeof my);
    my.sin_family = AF_INET;

    /* host address */
    if (host_name == NULL) {
	my.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
	if ((my.sin_addr.s_addr = inet_addr(host_name)) == -1) {
	    struct hostent *he;
	    if ((he = gethostbyname(host_name)) == NULL) {
		syslog(SYSLOG_PRIORITY, "gethostbyname():%m\n");
		return -1;
	    }
	    memcpy(&my.sin_addr, *he->h_addr_list, sizeof(struct in_addr));
	}
    }

    /* port number */
    if (port_number == NULL) {
	syslog(SYSLOG_PRIORITY, "port number is not specified\n");
	return -1;
    } else {
	if (isdigit(port_number[0])) {
	    int portno;
	    if ((portno = atoi(port_number)) <= 0) {
		syslog(SYSLOG_PRIORITY, "illegal port number\n");
		return -1;
	    }
	    my.sin_port = htons(portno);
	} else {
	    struct servent *se;
	    if ((se = getservbyname(port_number, "tcp")) == NULL) {
		syslog(SYSLOG_PRIORITY, "getservbyname():%m\n");
		return -1;
	    }
	    my.sin_port = se->s_port;
	}
    }

    /* create socket */
    if ((so = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
	syslog(SYSLOG_PRIORITY, "socket():%m\n");
	return -1;
    }

    /* set socket option */
    {
	int opt = 1;
	if (setsockopt(so, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) != 0) {
	    syslog(SYSLOG_PRIORITY, "setsockopt():%m\n");
	    close(so);
	    return -1;
	}
    }

    /* bind address */
    if (bind(so, (struct sockaddr*)&my, sizeof my) != 0) {
	syslog(SYSLOG_PRIORITY, "bind():%m\n");
	close(so);
	return -1;
    }

    /* listen */
    if (listen(so, SOMAXCONN) != 0) {
	syslog(SYSLOG_PRIORITY, "listen():%m\n");
	close(so);
	return -1;
    }

    return so;
}

/* accept loop with file locking */
int accept_loop_with_lock(int so, int lockfd, int (*func)(int ac))
{
    for (;;) {
	int ac;
	struct sockaddr_in from;
	socklen_t len = sizeof from;

	lockf(lockfd, F_LOCK, 0);	/* block to lock */
	if ((ac = accept(so, (struct sockaddr*)&from, &len)) < 0) {
	    if (errno != EINTR)
		break;
	    lockf(lockfd, F_ULOCK, 0);	/* unlock */
	} else {
	    lockf(lockfd, F_ULOCK, 0);	/* unlock */
	    (*func)(ac);
	    close(ac);
	}
    }

    return errno;
}
