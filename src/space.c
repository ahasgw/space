/***********************************************************************
 * $Id$
 *
 * space
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

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>

#include <dirname.h>
#include <getndelim2.h>
#include <getopt.h>
#include <progname.h>
#include <xalloc.h>
#include <safe-read.h>
#include <safe-write.h>

#include <syslog.h>
//#include "msg.h"

#include "state.h"
#include "command.h"
#include <token.h>

#include "space.h"

/*======================================================================
 * macro definitions
 *======================================================================*/

#define SYSLOG_OPTION	    (LOG_CONS|LOG_PERROR|LOG_PID)
#define SYSLOG_FACILITY	    (LOG_DAEMON)
#define SYSLOG_PRIORITY	    (LOG_USER|LOG_DEBUG)

#ifndef LINEBUFFER_SIZE
# define LINEBUFFER_SIZE    (GETNLINE_NO_LIMIT)
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

typedef struct opts_type {
    int		    opt_v;	/* v: verbose level */
    bool	    opt_h: 1;	/* h: help flag */
    bool	    opt_V: 1;	/* V: version flag */
} opts_t;

/*======================================================================
 * prototypes
 *======================================================================*/

static int eval(char *line);
static int read_eval_print(void);
static void show_banner(void);
static void show_version(void);
static void show_help(void);

/*======================================================================
 * global variables
 *======================================================================*/

static opts_t opts = {
    /* numerals */
    0,				/* v: verbose level */
    /* binary flags */
    false,			/* h: help flag */
    false			/* V: version flag */
};

state_t g_state;

/*======================================================================
 * function definitions
 *======================================================================*/

/* eval */
static int eval(char *line)
{
    int ret = 0;
    char *cp, *cp2;
    for (cp = line; *cp != '\0' && !isgraph(*cp); ++cp)
	;                   /* skip invisible chars */
    if (*cp != '#' && token_pick(&cp, &cp2)) {
	cmd_t *cmdp = cmd_get_func(cp);
	if (cmdp == NULL) {
	    fprintf(stdout, "unknown command: [%s]\n", cp);
	} else {
	    if (cmdp->func)
		ret = cmdp->func(cp2);
	}
    }
    return ret;
}

/* input from files */
static int read_eval_print(void)
{
#if LINEBUFFER_SIZE == GETNLINE_NO_LIMIT
    char *line = NULL;
#else
    char line[LINEBUFFER_SIZE + 1];
#endif
    size_t len = 0;
    ssize_t read;

//    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    show_banner();
    printf("> ");
    while ((read = getndelim2(&line, &len, 0, LINEBUFFER_SIZE, '\n', '\r', stdin)) != -1) {
	if (line[read - 1] == '\n' || line[read - 1] == '\r')
	    --read;
	line[read] = '\0';
#if 0
	printf("(%s)\n", line);
#endif
	if (read > 0) {
	    if (eval(line) != 0)
		break;
	} else {
	    fputc('\n', stdout);
	}
	printf("> ");
    }
    if (line)
	free(line);

    fflush(NULL);

    return EXIT_SUCCESS;
}

/* show banner */
static void show_banner(void)
{
    show_version();
    fputc('\n', stdout);    /* skip one line */
}

/* show version number */
static void show_version(void)
{
    static char fmt[] =
	"space (%s) %s\n"
	"Copyright (C) 2005, 2006 RIKEN. All rights reserved.\n"
	"This program comes with ABSOLUTELY NO WARRANTY.\n"
	"You may redistribute copies of this program under the terms of the\n"
	"GNU General Public License.\n"
	"For more information about these matters, see the file named COPYING.\n"
	;
    fprintf(stdout, fmt, PACKAGE, VERSION);
}

/* show help */
static void show_help(void)
{
    static char fmt[] =
	"This is space, the sequence pattern capture engine.\n"
	"Usage: %s [options]\n"
	"Options:\n"
	"  -h, --help           display this message\n"
	"  -V, --version        print version number, and exit\n"
	"  -v, --verbose        verbose output\n"
	"Report bugs to <%s>.\n"
	;
    fprintf(stdout, fmt, base_name(program_name), PACKAGE_BUGREPORT);
}

/* parse options */
static void parse_options(int argc, char *argv[], opts_t *opts)
{
    for (;;) {
	int opt, opt_index = 0;
	static struct option long_opts[] = {
	    {"help",	    no_argument,	NULL, 'h'},
	    {"version",	    no_argument,	NULL, 'V'},
	    {"verbose",	    no_argument,	NULL, 'v'},
	    {0, 0, 0, 0}
	};

	opt = getopt_long(argc, argv, "hVv", long_opts, &opt_index);
	if (opt == -1)
	    break;

	switch (opt) {
	    case 'h': opts->opt_h = 1; break;
	    case 'V': opts->opt_V = 1; break;
	    case 'v': ++opts->opt_v; break;
	    default: show_help(); exit(EXIT_FAILURE);
	}
    }
}

/* main */
int main(int argc, char *argv[])
{
    int ret = EXIT_SUCCESS;
    set_program_name(argv[0]);
    parse_options(argc, argv, &opts);

    if (opts.opt_V) { show_version(); exit(ret); }
    if (opts.opt_h) { show_help(); exit(ret); }

    openlog(base_name(program_name), SYSLOG_OPTION, SYSLOG_FACILITY);
    syslog(SYSLOG_PRIORITY, "started");
    {
	int nseq = seqlist_setup(&g_state.seqlist,
		DATABASEDIR_ENVNAME, DATABASEFILE);
	if (nseq > 0) {
	    syslog(SYSLOG_PRIORITY, "read %d seqitem(s)", nseq);
	    ret = read_eval_print();
	} else {
	    syslog(SYSLOG_PRIORITY, "failed to read seqlist");
	}
	seqlist_free(&g_state.seqlist);
    }
    syslog(SYSLOG_PRIORITY, "terminated");
    closelog();

    exit(ret);
}
