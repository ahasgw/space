/***********************************************************************
 * $Id: msg.c,v 1.2 2005/07/05 05:12:57 aki Exp $
 *
 * seqlist
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
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <getndelim2.h>
#include <pathname.h>

#include "seqlist.h"
#include <token.h>

/*======================================================================
 * macro definitions
 *======================================================================*/

#ifndef LINEBUFFER_SIZE
# define LINEBUFFER_SIZE    (GETNLINE_NO_LIMIT)
#endif

#ifndef SYSCONFDIR
# define SYSCONFDIR	    "/etc"
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

typedef struct seqtype_str_type {
    const char	*token;		/* written in space.db */
    const char	*name;		/* display name */
} seqtype_str_t;

/*======================================================================
 * local variables
 *======================================================================*/

static seqtype_str_t seqtype_str[] = {
    {"NONE",	    "none"},
    {"TEXT",	    "text"},
    {"AMINO_ACID",  "amino acid"},
    {"LINEAR_DNA",  "linear DNA"},
    {"CIRCULAR_DNA","circular DNA"},
    {"DNA",	    "DNA"},
    {"RNA",	    "RNA"},
    {NULL,	    NULL}
};

/*======================================================================
 * local function declaration
 *======================================================================*/

static int seqtype_search(const char *t);

/*======================================================================
 * function definitions
 *======================================================================*/

int seqlist_setup(seqlist_t *sl, const char *envname, const char *fname)
{
    const char *dirs;
    char *dbpath = NULL;
    int nseq = 0;

    assert(sl != NULL);
    assert(envname != NULL);
    assert(*envname != '\0');
    assert(fname != NULL);
    assert(*fname != '\0');

    seqlist_init(sl);

    if ((dirs = getenv(envname)) == NULL) {
	/* environment variable envname is not set
	 * read from system configuration
	 */
	if ((dbpath = concatenated_pathname(SYSCONFDIR, fname, "")) == NULL
		|| (nseq = seqlist_append_file(sl, dbpath)) < 0)
	{	/* error */
#if 0
fprintf(stderr, "ignoring: [%s]\n", dbpath);
	} else {
fprintf(stderr, "read: [%s]\n", dbpath);
#endif
	}
	free(dbpath), dbpath = NULL;
    } else {
	char *work = strdup(dirs);
	char *cp, *cp2;
	if (work == NULL) {	/* error */
	    return -1;
	}
	for (cp = work; cp != NULL; cp = ((cp2 == NULL) ? NULL : cp2 + 1)) {
	    if ((cp2 = strchr(cp, ':')) != NULL)
		*cp2 = '\0';
	    if ((dbpath = concatenated_pathname(cp, fname, "")) == NULL
		|| (nseq = seqlist_append_file(sl, dbpath)) < 0)
	    {	/* error */
#if 0
fprintf(stderr, "ignoring: [%s]\n", dbpath);
	    } else {
fprintf(stderr, "read: [%s]\n", dbpath);
#endif
	    }
	    free(dbpath), dbpath = NULL;
	}
    }
    return nseq;
}

int seqlist_append_file(seqlist_t *sl, const char *listpath)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(listpath, "r")) == NULL)
	return -1;

    while ((read = getndelim2(&line, &len, 0, LINEBUFFER_SIZE, '\n', '\r', fp)) != -1) {
	seqitem_t si;
	char *cp, *cp2;

	if (line[read - 1] == '\n' || line[read - 1] == '\r')
	    line[--read] = '\0';

	for (cp = line; *cp != '\0' && !isgraph(*cp); ++cp)
	    ;			/* skip invisible chars */
	if (*cp == '#' || !token_pick(&cp, &cp2))
	    continue;		/* continue if EOL or '#' */

	si.seqtype = seqtype_search(cp);

	cp = cp2;
	if (*cp == '#' || !token_pick(&cp, &cp2))
	    continue;		/* continue if EOL or '#' */

	si.select = SEQSEL_NONE;
	if ((si.sqxpath = strdup(cp)) == NULL
		|| seqlist_append(sl, &si) == 0)
	{
	    if (line)
		free(line);
	    fclose(fp);
	    return -1;
	}
    }
    if (line)
	free(line);
    fclose(fp);
    return (int)seqlist_count(sl);
}

int seqlist_show(seqlist_t *sl)
{
    seqitem_t *si = seqlist_ptr(sl);
    int i, cnt = seqlist_count(sl);
    printf("# No.: Selected [Type] /Path/to/sqx/file\n");
    for (i = 0; i < cnt; ++i, ++si) {
	printf("%d: %d [%s] %s\n",
		i, si->select, seqtype_str[si->seqtype].name, si->sqxpath);
    }
    return cnt;
}

void seqlist_select(seqlist_t *sl, int n, seqsel_t sel)
{
    seqitem_t *si = seqlist_ptr(sl);
    int cnt = seqlist_count(sl);
    if (n >= 0 && n < cnt) {
	si[n].select = sel;
    }
}

/*----------------------------------------------------------------------
 * local function definitions
 *----------------------------------------------------------------------*/

static int seqtype_search(const char *t)
{
    const seqtype_str_t *p = &seqtype_str[0];
    for (; p->token != NULL; ++p) {
	if (strcasecmp(p->token, t) == 0)
	    return p - &seqtype_str[0];
    }
    return SEQTYPE_END;
}
