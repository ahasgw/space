/***********************************************************************
 * $Id: msg.c,v 1.2 2005/07/05 05:12:57 aki Exp $
 *
 * commands
 * Copyright (C) 2005, 2006 RIKEN. All rights reserved.
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
#include <errno.h>
#include <string.h>

#include "command.h"
#include "state.h"
#include <token.h>

#include <findprog.h>
#include <stpcpy.h>
#include <sh-quote.h>

#include "space.h"

/*======================================================================
 * prototypes
 *======================================================================*/

static int cmd_quit_f(char *line);
static int cmd_help_f(char *line);
static int cmd_match_f(char *line);
static int cmd_nsmatch_f(char *line);
static int cmd_psmatch_f(char *line);
static int cmd_status_f(char *line);
static int cmd_list_f(char *line);
static int cmd_select_f(char *line);
static int cmd_deselect_f(char *line);

static char *build_match_cmdline(const char *cmdpath, const char *sqxpath, const char *line);
static size_t cmd_table_size(void);
static int cmd_compare(const void *c1, const void *c2);

/*======================================================================
 * local variables
 *======================================================================*/

static cmd_t cmd_table[] = {
    /* these entries must be sorted by cmd member (1st element) */
    {"?",	cmd_help_f,	"",	    "show help message"},
    {"deselect",cmd_deselect_f,	"[n ...]",  "deselect sequence item"},
    {"help",	cmd_help_f,	"",	    "show help message"},
    {"list",	cmd_list_f,	"",	    "list database"},
    {"match",	cmd_match_f,	"[pat ...]","execute pattern matching"},
    {"nsmatch",	cmd_nsmatch_f,	"[pat ...]","execute DNA pattern matching"},
    {"psmatch",	cmd_psmatch_f,	"[pat ...]","execute PROSITE pattern matching"},
    {"quit",	cmd_quit_f,	"",	    "close connection and quit"},
    {"select",	cmd_select_f,	"[n ...]",  "select sequence item"},
    {"status",	cmd_status_f,	"",	    "show current status"},
};

/*======================================================================
 * command function definitions
 *======================================================================*/

static int cmd_quit_f(char *line)
{
//    fprintf(stdout, "[[quit]]\n");
    return 1;
}

static int cmd_help_f(char *line)
{
    cmd_t *cmdp;
    int i;
//    fprintf(stdout, "[[help]]\n");
    for (cmdp = cmd_table, i = 0; i < cmd_table_size(); ++i, ++cmdp) {
	printf("%s%s%s  --  %s\n",
		cmdp->cmd, ((*cmdp->help_opt == '\0') ? "" : " "),
		cmdp->help_opt, cmdp->help);
    }
    return 0;
}

static int cmd_match_f(char *line)
{
    const char *srchcmd = TOOLPROG_MATCH;
    const char *cmdpath = NULL;
    seqitem_t *si_beg, *si_end, *si;

//    fprintf(stdout, "[[match]]\n");

    if ((cmdpath = getenv(TOOLPROG_MATCH_ENVNAME)) == NULL) {
	/* environ variable of TOOLDIR_ENVNAME is not set,
	 * so, the PATH environment variable is used
	 */
#if 1
	putenv("PATH=/usr/bin:~/bin:/home/aki/works/suffix/sfxatools/src:/home/aki/works/suffix/sfxatools/bio");
#endif
	cmdpath = find_in_path(srchcmd);
    }
//fprintf(stderr, "cmdpath: [%s]\n", cmdpath);

    si_beg = seqlist_ptr(&g_state.seqlist);
    si_end = si_beg + seqlist_count(&g_state.seqlist);
    for (si = si_beg; si < si_end; ++si) {
	if (si->select == SEQSEL_SELECTED) {
	    char *cmdstr = build_match_cmdline(cmdpath, si->sqxpath, line);
	    if (cmdstr != NULL) {
		FILE *fp;
#if 1
		fflush(NULL);
		if ((fp = popen(cmdstr, "w")) == NULL) {    /* popen */
		    /* error */
		    fprintf(stderr, "popen failed: %s\n", strerror(errno));
		}
		pclose(fp);
		fflush(NULL);
#else
		fprintf(stderr, "[[%s]]\n", cmdstr);
#endif
		free(cmdstr);
	    } else {
		fprintf(stderr, "cannot process command\n");
	    }
	}
    }

    if (cmdpath != srchcmd)
	free((void*)cmdpath);

    return 0;
}

static int cmd_nsmatch_f(char *line)
{
    const char *srchcmd = TOOLPROG_NSMATCH;
    const char *cmdpath = NULL;
    seqitem_t *si_beg, *si_end, *si;

//    fprintf(stdout, "[[nsmatch]]\n");

    if ((cmdpath = getenv(TOOLPROG_MATCH_ENVNAME)) == NULL) {
	/* environ variable of TOOLDIR_ENVNAME is not set,
	 * so, the PATH environment variable is used
	 */
#if 1
	putenv("PATH=/usr/bin:~/bin:/home/aki/works/suffix/sfxatools/src:/home/aki/works/suffix/sfxatools/bio");
#endif
	cmdpath = find_in_path(srchcmd);
    }
fprintf(stderr, "cmdpath: [%s]\n", cmdpath);

    si_beg = seqlist_ptr(&g_state.seqlist);
    si_end = si_beg + seqlist_count(&g_state.seqlist);
    for (si = si_beg; si < si_end; ++si) {
	if (si->select == SEQSEL_SELECTED) {
	    char *cmdstr = build_match_cmdline(cmdpath, si->sqxpath, line);
	    if (cmdstr != NULL) {
		FILE *fp;
#if 1
		fflush(NULL);
		if ((fp = popen(cmdstr, "w")) == NULL) {    /* popen */
		    /* error */
		    fprintf(stderr, "popen failed: %s\n", strerror(errno));
		}
		pclose(fp);
		fflush(NULL);
#else
		fprintf(stderr, "[[%s]]\n", cmdstr);
#endif
		free(cmdstr);
	    } else {
		fprintf(stderr, "cannot process command\n");
	    }
	}
    }

    if (cmdpath != srchcmd)
	free((void*)cmdpath);

    return 0;
}

static int cmd_psmatch_f(char *line)
{
    const char *srchcmd = TOOLPROG_PSMATCH;
    const char *cmdpath = NULL;
    seqitem_t *si_beg, *si_end, *si;

//    fprintf(stdout, "[[psmatch]]\n");

    if ((cmdpath = getenv(TOOLPROG_MATCH_ENVNAME)) == NULL) {
	/* environ variable of TOOLDIR_ENVNAME is not set,
	 * so, the PATH environment variable is used
	 */
#if 1
	putenv("PATH=/usr/bin:~/bin:/home/aki/works/suffix/sfxatools/src:/home/aki/works/suffix/sfxatools/bio");
#endif
	cmdpath = find_in_path(srchcmd);
    }
fprintf(stderr, "cmdpath: [%s]\n", cmdpath);

    si_beg = seqlist_ptr(&g_state.seqlist);
    si_end = si_beg + seqlist_count(&g_state.seqlist);
    for (si = si_beg; si < si_end; ++si) {
	if (si->select == SEQSEL_SELECTED) {
	    char *cmdstr = build_match_cmdline(cmdpath, si->sqxpath, line);
	    if (cmdstr != NULL) {
		FILE *fp;
#if 1
		fflush(NULL);
		if ((fp = popen(cmdstr, "w")) == NULL) {    /* popen */
		    /* error */
		    fprintf(stderr, "popen failed: %s\n", strerror(errno));
		}
		pclose(fp);
		fflush(NULL);
#else
		fprintf(stderr, "[[%s]]\n", cmdstr);
#endif
		free(cmdstr);
	    } else {
		fprintf(stderr, "cannot process command\n");
	    }
	}
    }

    if (cmdpath != srchcmd)
	free((void*)cmdpath);

    return 0;
}

static char *build_match_cmdline(const char *cmdpath, const char *sqxpath, const char *line)
{
    char *cmdline = NULL;
    size_t sz = strlen(cmdpath) + (2 * (strlen(sqxpath))) + strlen(line) + 4;

    /* alloc */
    if ((cmdline = (char*)malloc(sz)) == NULL) {
	/* error */
	return NULL;
    }
    /* copy */
    cmdline[0] = '\0';
    {
	char *cp = cmdline;
	cp = stpcpy(cp, cmdpath);
	cp = stpcpy(cp, " ");
	cp = stpcpy(cp, sqxpath), cp -= 4, cp = stpcpy(cp, ".seq");
	cp = stpcpy(cp, " ");
	cp = stpcpy(cp, sqxpath);
	cp = stpcpy(cp, " ");
	cp = stpcpy(cp, line);
    }
    return cmdline;
}

static int cmd_status_f(char *line)
{
//    fprintf(stdout, "[[status]]\n");
    return 0;
}

static int cmd_list_f(char *line)
{
//    fprintf(stdout, "[[list]]\n");
    seqlist_show(&g_state.seqlist);
    return 0;
}

static int cmd_select_f(char *line)
{
    char *cp2;
//    fprintf(stdout, "[[select]]\n");
    for (; *line != '#' && token_pick(&line, &cp2); line = cp2) {
	char *endp;
	long n;
	n = strtol(line, &endp, 10);
//fprintf(stdout, "[[%ld]]\n", n);
	if (line != endp && n >= 0 && n <= INT_MAX)
	    seqlist_select(&g_state.seqlist, (int)n, SEQSEL_SELECTED);
    }
    return 0;
}

static int cmd_deselect_f(char *line)
{
    char *cp2;
//    fprintf(stdout, "[[deselect]]\n");
    for (; *line != '#' && token_pick(&line, &cp2); line = cp2) {
	char *endp;
	long n;
	n = strtol(line, &endp, 10);
//fprintf(stdout, "[[%ld]]\n", n);
	if (line != endp && n >= 0 && n <= INT_MAX)
	    seqlist_select(&g_state.seqlist, (int)n, SEQSEL_NONE);
    }
    return 0;
}

/*----------------------------------------------------------------------
 * function definitions
 *----------------------------------------------------------------------*/

static size_t cmd_table_size(void)
{
    return (sizeof cmd_table / sizeof(cmd_t));
}

static int cmd_compare(const void *c1, const void *c2)
{
    return strcasecmp(((cmd_t*)c1)->cmd, ((cmd_t*)c2)->cmd);
}

cmd_t *cmd_get_func(const char *token)
{
    size_t ctsz = cmd_table_size();
    cmd_t key;
    key.cmd = token;
    return bsearch(&key, cmd_table, ctsz, sizeof(cmd_t), cmd_compare);
}
