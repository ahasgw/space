/***********************************************************************
 * $Id: msg.h,v 1.3 2005/07/05 07:33:28 aki Exp $
 *
 * Header file for seqlist
 * Copyright (C) 2004 RIKEN. All rights reserved.
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

#ifndef SEQLIST_H
#define SEQLIST_H 1
#define SEQLIST_H_INCLUDED 1

#include <limits.h>

#include "xarray.h"

#ifdef __cplusplus
extern "C" {
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

typedef enum seqtype_type {
    SEQTYPE_END = -1,
    SEQTYPE_NONE = 0,
    SEQTYPE_TEXT,
    SEQTYPE_AMINO_ACID,
    SEQTYPE_LINEAR_DNA,
    SEQTYPE_CIRCULAR_DNA,
    SEQTYPE_DNA,
    SEQTYPE_RNA
} seqtype_t;

typedef enum seqsel_type {
    SEQSEL_NONE = 0,
    SEQSEL_SELECTED,
    SEQSEL_PROCESSING,
    SEQSEL_DONE
} seqsel_t;

typedef struct seqitem_type {
    char	*sqxpath;
    seqtype_t	seqtype;
    seqsel_t	select;
} seqitem_t;

typedef xarray_t    seqlist_t;

/*======================================================================
 * prototypes
 *======================================================================*/

inline static seqlist_t *seqlist_new(void);
inline static void seqlist_init(seqlist_t *sl);
inline static void seqlist_free(seqlist_t *sl);
inline static void seqlist_delete(seqlist_t *sl);
inline static seqitem_t *seqlist_ptr(seqlist_t *sl);
inline static seqitem_t *seqlist_at(seqlist_t *sl, int num);
inline static int seqlist_count(seqlist_t *sl);
inline static int seqlist_append(seqlist_t *sl, seqitem_t *item);
inline static int seqlist_shrink(seqlist_t *sl);

int seqlist_setup(seqlist_t *sl, const char *envname, const char *fname);
int seqlist_append_file(seqlist_t *sl, const char *listpath);

int seqlist_show(seqlist_t *sl);
void seqlist_select(seqlist_t *sl, int n, seqsel_t sel);

/*======================================================================
 * inline function definitions
 *======================================================================*/

inline static seqlist_t *seqlist_new(void)
{
    return xarray_new(sizeof(seqitem_t), 1, 2);
}

inline static void seqlist_init(seqlist_t *sl)
{
    xarray_init(sl, sizeof(seqitem_t), 1, 2);
}

inline static void seqlist_free(seqlist_t *sl)
{
    size_t i = xarray_count(sl);
    seqitem_t *si = (seqitem_t*)xarray_ptr(sl) + i;
    for (--si; i > 0; --i) {
	free(si->sqxpath); si->sqxpath = NULL;
    }
    xarray_free(sl);
}

inline static void seqlist_delete(seqlist_t *sl)
{
    xarray_delete(sl);
}

inline static seqitem_t *seqlist_ptr(seqlist_t *sl)
{
    return (seqitem_t*)xarray_ptr(sl);
}

inline static seqitem_t *seqlist_at(seqlist_t *sl, int num)
{
    return (num >= xarray_count(sl))
	? NULL
	: ((seqitem_t*)xarray_ptr(sl)) + num;
}

inline static int seqlist_count(seqlist_t *sl)
{
    return (int)xarray_count(sl);
}

inline static int seqlist_append(seqlist_t *sl, seqitem_t *item)
{
    return ((xarray_count(sl) <= INT_MAX) ? (int)xarray_append(sl, item) : 0);
}

inline static int seqlist_shrink(seqlist_t *sl)
{
    return xarray_shrink(sl, xarray_count(sl));
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SEQLIST_H */
