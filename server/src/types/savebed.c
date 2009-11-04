/************************************************************************
*            Atrinik, a Multiplayer Online Role Playing Game            *
*                                                                       *
*                     Copyright (C) 2009 Alex Tokar                     *
*                                                                       *
* Fork from Daimonin (Massive Multiplayer Online Role Playing Game)     *
* and Crossfire (Multiplayer game for X-windows).                       *
*                                                                       *
* This program is free software; you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation; either version 2 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program; if not, write to the Free Software           *
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
*                                                                       *
* The author can be reached at admin@atrinik.org                        *
************************************************************************/

/**
 * @file
 * Handles code used for @ref SAVEBED "savebeds". */

#include <global.h>

/**
 * Apply a savebed.
 * @param op The player applying the savebed. */
void apply_savebed(object *op)
{
	if (!CONTR(op)->name_changed || !op->stats.exp)
	{
		new_draw_info(NDI_UNIQUE, 0, op, "You don't deserve to save your character yet.");
		return;
	}

	/* update respawn position */
	strcpy(CONTR(op)->savebed_map, op->map->path);
	CONTR(op)->bed_x = op->x;
	CONTR(op)->bed_y = op->y;

	new_draw_info(NDI_UNIQUE, 0, op, "You save and leave the game. Bye!\nLeaving...");
	CONTR(op)->socket.status = Ns_Dead;
}