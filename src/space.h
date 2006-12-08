/***********************************************************************
 * $Id: msg.h,v 1.3 2005/07/05 07:33:28 aki Exp $
 *
 * Header file for space
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

#ifndef SPACE_H
#define SPACE_H 1
#define SPACE_H_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

/*======================================================================
 * macro definitions
 *======================================================================*/

#ifndef DATABASEDIR_ENVNAME
# define DATABASEDIR_ENVNAME	"SPACEDBDIR"
#endif
#ifndef DATABASEFILE
# define DATABASEFILE		"space.db"
#endif
#if 0
#ifndef TOOLDIR_ENVNAME
# define TOOLDIR_ENVNAME	"SPACETOOLDIR"
#endif
#else
# define TOOLPROG_MATCH_ENVNAME	"SPACEMATCHPROG"
#endif
#ifndef TOOLPROG_MATCH
# define TOOLPROG_MATCH		"sfxasrch"
#endif
#ifndef TOOLPROG_NSMATCH
# define TOOLPROG_NSMATCH	"nsps"
#endif
#ifndef TOOLPROG_PSMATCH
# define TOOLPROG_PSMATCH	"psps"
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SPACE_H */
