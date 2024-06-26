/***********************************************************************
 * $Id: token.h,v 1.3 2005/07/05 07:33:28 aki Exp $
 *
 * tokenizer
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

#include <ctype.h>

#include "token.h"

/*======================================================================
 * function definition
 *======================================================================*/

int token_pick(char **beg, char **end)
{
    if (**beg == '\0')
	return 0;               /* continue if EOL or '#' */
    for (*end = *beg; **end != '\0' && isgraph(**end); ++*end)
	;                       /* find end of token */
    if (**end != '\0') {
	**end = '\0';           /* make sure zero terminated */
	for (++*end; **end != '\0' && !isgraph(**end); ++*end)
	    ;                   /* skip trailing invisible chars */
    }
    return 1;
}
