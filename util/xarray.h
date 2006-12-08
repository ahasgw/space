/***********************************************************************
 * $Id: xarray.h,v 1.2 2005/08/17 10:11:45 aki Exp $
 *
 * Header file for xarray
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

#ifndef XARRAY_H
#define XARRAY_H 1
#define XARRAY_H_INCLUDED 1

#ifndef CONFIG_H_INCLUDED
# define CONFIG_H_INCLUDED 1
# include <config.h>
#endif

#include <stdlib.h>
#include <errno.h>

#ifndef STDINT_H_INCLUDED
# define STDINT_H_INCLUDED 1
# include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

/* extendable array */
typedef struct xarray {
    size_t  init;	/* initial number of element */
    size_t  grow;	/* growing factor */
    size_t  siz;	/* size of an element */
    size_t  max;	/* maximum number of element */
    size_t  num;	/* number of element */
    void    *ptr;	/* pointer to data */
} xarray_t;

/*======================================================================
 * function declarations
 *======================================================================*/

xarray_t *xarray_new(size_t memb_sz, size_t init, size_t grow);
void xarray_init(xarray_t *ap, size_t memb_sz, size_t init, size_t grow);
void xarray_free(xarray_t *ap);
void xarray_delete(xarray_t *ap);
void xarray_clear(xarray_t *ap);
void *xarray_ptr(xarray_t *ap);
size_t xarray_count(xarray_t *ap);
size_t xarray_append(xarray_t *ap, void *elem);
size_t xarray_append_n(xarray_t *ap, void *elem, size_t num);
size_t xarray_shrink(xarray_t *ap, size_t num);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* XARRAY_H */
