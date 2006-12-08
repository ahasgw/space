/***********************************************************************
 * $Id: msg.h,v 1.3 2005/07/05 07:33:28 aki Exp $
 *
 * Header file for commands
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

#ifndef COMMAND_H
#define COMMAND_H 1
#define COMMAND_H_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

/*======================================================================
 * type definitions
 *======================================================================*/

typedef struct cmd_type {
    const char      *cmd;
    int             (*func)(char *line);
    const char	    *help_opt;
    const char	    *help;
} cmd_t;

cmd_t *cmd_get_func(const char *token);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COMMAND_H */
