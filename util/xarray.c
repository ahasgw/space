/***********************************************************************
 * $Id: xarray.c,v 1.3 2004/07/12 09:45:45 aki Exp $
 *
 * Extendable array utility
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

#include <string.h>

#include "xarray.h"
//#include "clp2.h"

/*======================================================================
 * macros
 *======================================================================*/

#define XARRAY_DEFAULT_INIT	(1)
#define XARRAY_DEFAULT_GROW	(2)

/*======================================================================
 * extendable array functions
 *======================================================================*/

xarray_t *xarray_new(size_t memb_sz, size_t init, size_t grow)
{
    xarray_t *ap = (xarray_t*)malloc(sizeof(xarray_t));
    if (ap == NULL)
	return NULL;
    xarray_init(ap, memb_sz, init, grow);
    return ap;
}

void xarray_init(xarray_t *ap, size_t memb_sz, size_t init, size_t grow)
{
    ap->init = (init == 0) ? XARRAY_DEFAULT_INIT : init;
    ap->grow = (grow == 0) ? XARRAY_DEFAULT_GROW : grow;
    ap->siz = memb_sz;
    ap->max = 0;
    ap->num = 0;
    ap->ptr = NULL;
}

void xarray_free(xarray_t *ap)
{
    free(ap->ptr), ap->ptr = NULL;
}

void xarray_delete(xarray_t *ap)
{
    xarray_free(ap);
    free(ap);
}

void xarray_clear(xarray_t *ap)
{
    ap->num = 0;
}

void *xarray_ptr(xarray_t *ap)
{
    return ap->ptr;
}

size_t xarray_count(xarray_t *ap)
{
    return ap->num;
}

size_t xarray_append(xarray_t *ap, void *elem)
{
    if (ap->ptr == NULL) {
	ap->ptr = malloc(ap->init * ap->siz);
	if (ap->ptr == NULL)
	    return 0;
	ap->max = ap->init;
	ap->num = 0;
    } else if (ap->num >= ap->max) {
	void *newptr = (void*)realloc(ap->ptr, (ap->grow * ap->max * ap->siz));
	if (newptr == NULL)
	    return 0;
	ap->ptr = newptr;
	ap->max *= ap->grow;
    }
    memmove(ap->ptr + (ap->num * ap->siz), elem, ap->siz);
    return ++ap->num;
}

size_t xarray_append_n(xarray_t *ap, void *elem, size_t n)
{
    size_t new = ap->num + n;
    if (ap->ptr == NULL) {
	new = (new > ap->init) ? new : ap->init;
	ap->ptr = (void*)malloc(new * ap->siz);
	if (ap->ptr == NULL)
	    return 0;
	ap->max = new;
	ap->num = 0;
    } else if (new >= ap->max) {
	void *newptr = (void*)realloc(ap->ptr, (new * ap->siz));
	if (newptr == NULL)
	    return 0;
	ap->ptr = newptr;
	ap->max = new;
    }
    memmove(ap->ptr + (ap->num * ap->siz), elem, n * ap->siz);
    ap->num += n;
    return ap->num;

}

size_t xarray_shrink(xarray_t *ap, size_t num)
{
    void *newptr = NULL;

    if (num > ap->num)
	return 0;
    newptr = (void*)realloc(ap->ptr, (num * ap->siz));
    if (newptr == NULL)
	return 0;
    ap->ptr = newptr;
    ap->max = num;
    ap->num = num;
    return ap->num;
}
