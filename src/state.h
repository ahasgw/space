/***********************************************************************
 * $Id: msg.h,v 1.3 2005/07/05 07:33:28 aki Exp $
 *
 * Header file for state
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

#ifndef STATE_H
#define STATE_H 1
#define STATE_H_INCLUDED 1

#include "seqlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

typedef struct state_type {
    seqlist_t	seqlist;
} state_t;

/*======================================================================
 * global variables
 *======================================================================*/

extern state_t g_state;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* STATE_H */
