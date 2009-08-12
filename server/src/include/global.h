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

#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef EXTERN
#define EXTERN extern
#endif

#include "includes.h"


/* Type defines for specific signed/unsigned variables of a certain number
 * of bits.  Not really used anyplace, but if a certain number of bits
 * is required, these type defines should then be used.  This will make
 * porting to systems that have different sized data types easier.
 *
 * Note: The type defines should just mean that the data type has at
 * least that many bits.  if a uint16 is actually 32 bits, no big deal,
 * it is just a waste of space.
 *
 * Note2:  When using something that is normally stored in a character
 * (ie strings), don't use the uint8/sint8 typdefs, use 'char' instead.
 * The signedness for char is probably not universal, and using char
 * will probably be more portable than sint8/unit8 */

typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short Fontindex;
typedef unsigned int tag_t;

#if SIZEOF_LONG == 8

typedef unsigned long			uint64;
typedef signed long				sint64;
#define FMT64					"ld"
#define FMT64U					"lu"

#elif SIZEOF_LONG_LONG == 8
typedef unsigned long long		uint64;
typedef signed long long		sint64;
#define FMT64					"lld"
#define FMT64U					"llu"

#else
#error Do not know how to get a 64 bit value on this system.
#error Correct and send email to the Atrinik Team on how to do this.
#endif

typedef struct _money_block {
	/* 0, 1, or -1: see get_money_from_string() */
	int mode;

	long mithril;

	long gold;

	long silver;

	long copper;
}_money_block;

#define MONEYSTRING_NOTHING 0
#define MONEYSTRING_AMOUNT 1
#define MONEYSTRING_ALL -1

#define POW2(x) ((x) * (x))

/* map distance values for draw_info_map functions
 * This value is in tiles */
#define MAP_INFO_NORMAL 12
#define MAP_INFO_ALL 9999

/* use this macros *only* to access the global hash table!
 * Note: there is a 2nd hash table for the arch list - thats a static
 * list BUT the arch names are inserted in the global hash to - so every
 * archlist name has 2 entries! */
#define FREE_AND_COPY_HASH(_sv_,_nv_) { if (_sv_) free_string_shared(_sv_); _sv_=add_string(_nv_); }
#define FREE_AND_ADD_REF_HASH(_sv_,_nv_) { if (_sv_) free_string_shared(_sv_); _sv_=add_refcount(_nv_); }
#define FREE_AND_CLEAR_HASH(_nv_) {if(_nv_){free_string_shared(_nv_);_nv_ =NULL;}}
#define FREE_ONLY_HASH(_nv_) if(_nv_)free_string_shared(_nv_);

#define ADD_REF_NOT_NULL_HASH(_nv_) if(_nv_!=NULL)add_refcount(_nv_);

/* special macro with no {} ! if() FREE_AND_CLEAR_HASH2 will FAIL! */
#define FREE_AND_CLEAR_HASH2(_nv_) if(_nv_){free_string_shared(_nv_);_nv_ =NULL;}

#define SPAWN_RANDOM_RANGE 10000
#define RANDOM_DROP_RAND_RANGE 1000000

/* for creating treasures (treasure.c) */
#define T_STYLE_UNSET (-2)
#define ART_CHANCE_UNSET (-1)

/* mob defines */
#define MIN_MON_RADIUS 2  /* minimum monster detection radius */
#define MAX_AGGRO_RANGE 9 /* if target of mob is out of this range (or stats.Wis if higher)*/
#define MAX_AGGRO_TIME 12 /* until this time - then it skip target */

/* return values for esrv_send_face() in image.c */
#define SEND_FACE_OK 0
#define SEND_FACE_OUT_OF_BOUNDS 1
#define SEND_FACE_NO_DATA 2

/* number of connected maps from a tiled map */
#define TILED_MAPS 8

/* global stuff used by new skill/experience system -b.t.
 * Needed before player.h */
/* This should be => # of exp obj in the game
 * remember to include the "NULL" exp object
 * EXP_NONE as part of the overall tally. */
#define MAX_EXP_CAT 7

/* "NULL" exp. object. This is the last
 * experience obj always.*/
#define EXP_NONE (MAX_EXP_CAT - 1)

#define MAXLEVEL 110
extern uint32 new_levels[MAXLEVEL + 2];
extern float lev_exp[MAXLEVEL + 1];

/* our global map_tag value for the server (map.c)*/
extern uint32 global_map_tag;

/* So far only used when dealing with artifacts.
 * (now used by alchemy and other code too. Nov 95 b.t). */
typedef struct linked_char {
  	const char *name;

  	struct linked_char *next;
} linked_char;

#include "face.h"
/* needs to be before material.h */
#include "attack.h"
#include "material.h"
#include "living.h"
#include "object.h"
#include "arch.h"
#include "map.h"
#include "tod.h"
#include "pathfinder.h"

/* Pull in the socket structure - used in the player structure */
#include "newserver.h"

/* add skills.h global */
#include "skills.h"

/* Pull in the player structure */
#include "player.h"

/* pull in treasure structure */
#include "treasure.h"

#include "commands.h"

/* Pull in artifacts */
#include "artifact.h"

/* Now for gods */
#include "god.h"

/* Now for races */
#include "race.h"

#include "sounds.h"

/* Now for recipe/alchemy */
#include "recipe.h"

/* Now for spells */
#include "spells.h"

/* pointer for the glue.c interface between crosslib and server */
#include "funcpoint.h"

/*****************************************************************************
 * GLOBAL VARIABLES:							     						 *
 *****************************************************************************/
/* Special potions are now identifed by the last_eat value.
 * last_eat == 0 is no special potion - means they are used
 * as spell effect carrier. */
#define special_potion(__op_sp) (__op_sp)->last_eat

/* arch.c - sysinfo for lowlevel */

/* How many strcmp's */
extern int arch_cmp;
/* How many searches */
extern int arch_search;

#define move_object(__op, __dir) move_ob(__op,__dir,__op)

#define is_magical(__op_) QUERY_FLAG(__op_,FLAG_IS_MAGICAL)

#define NUM_COLORS 13

extern char *colorname[NUM_COLORS];

extern New_Face *new_faces;

/* These are the beginnings of linked lists: */
EXTERN player *first_player;
EXTERN mapstruct *first_map;
EXTERN treasurelist *first_treasurelist;
EXTERN artifactlist *first_artifactlist;
/* Objects monsters will go after */
EXTERN objectlink *first_friendly_object;
EXTERN godlink *first_god;
EXTERN racelink *first_race;

#define NROF_COMPRESS_METHODS 4
EXTERN char *uncomp[NROF_COMPRESS_METHODS][3];

/* Variables set by different flags (see init.c): */
/* Ignores signals until init_done is true */
EXTERN long init_done;
/* True when emergency_save() is reached */
EXTERN long trying_emergency_save;
/* If it exceeds MAX_ERRORS, call fatal() */
EXTERN long nroferrors;

/* used by various function to determine
 * how often to save the character */
extern long pticks;

/* Misc global variables: */

/* Used by server/daemon.c */
EXTERN FILE *logfile;
/* True if the game is about to exit */
EXTERN int exiting;
/* Only used in malloc_info() */
EXTERN long nroftreasures;
/* Only used in malloc_info() */
EXTERN long nrofartifacts;
/* Only used in malloc_info() */
EXTERN long nrofallowedstr;

/* Current number of experience categories in the game */
EXTERN short nrofexpcat;
/* Array of experience objects in the game */
EXTERN object *exp_cat[MAX_EXP_CAT];
/* Container for objects without env or map (e.g. exp_cat[i])*/
extern object void_container;

/* The start-level */
EXTERN char first_map_path[MAX_BUF];

EXTERN char errmsg[HUGE_BUF];
EXTERN long ob_count;

/* global round ticker ! this is real a global */
EXTERN uint32 global_round_tag;
#define ROUND_TAG global_round_tag /* put this here because the DIFF */

/* global race counter */
EXTERN int global_race_counter;

/* Used for main loop timing */
EXTERN struct timeval last_time;

/* Used in treasure.c */
/* Used in hit_player() in main.c */
EXTERN const char *undead_name;

EXTERN Animations *animations;
EXTERN int num_animations, animations_allocated, bmaps_checksum;

/* to access strings from objects, maps, arches or other system objects,
 * for printf() or others use only this macros to avoid NULL pointer exceptions.
 * Some standard c libaries don't check for NULL in that functions - most times
 * the retail versions. */
#define STRING_SAFE(__string__) (__string__?__string__:">NULL<")

#define STRING_ARCH_NAME(__arch__) ((__arch__)->name?(__arch__)->name:">NULL<")

#define STRING_OBJ_NAME(__ob__) ((__ob__) && (__ob__)->name?(__ob__)->name:">NULL<")
#define STRING_OBJ_ARCH_NAME(__ob__) ((__ob__)->arch?((__ob__)->arch->name?(__ob__)->arch->name:">NULL<"):">NULL<")
#define STRING_OBJ_TITLE(__ob__) ((__ob__)->title?(__ob__)->title:">NULL<")
#define STRING_OBJ_RACE(__ob__) ((__ob__)->race?(__ob__)->race:">NULL<")
#define STRING_OBJ_SLAYING(__ob__) ((__ob__)->slaying?(__ob__)->slaying:">NULL<")
#define STRING_OBJ_MSG(__ob__) ((__ob__)->msg?(__ob__)->msg:">NULL<")

#define STRING_MAP_PATH(__map__) ((__map__)->path?(__map__)->path:">NULL<")
#define STRING_MAP_TILE_PATH(__map__, __id__) ((__map__)->tile_path[__id__]?(__map__)->tile_path[__id__]:">NULL<")
#define STRING_MAP_NAME(__map__) ((__map__)->name?(__map__)->name:">NULL<")
#define STRING_MAP_TMPNAME(__map__) ((__map__)->tmpname?(__map__)->tmpname:">NULL<")
#define STRING_MAP_MSG(__map__) ((__map__)->msg?(__map__)->msg:">NULL<")

/* Rotate right from bsd sum. This is used in various places for checksumming */
#define ROTATE_RIGHT(c) if ((c) & 01) (c) = ((c) >>1) + 0x80000000; else (c) >>= 1;

#define SET_ANIMATION(ob,newanim) ob->face=&new_faces[animations[ob->animation_id].faces[newanim]]
#define GET_ANIMATION(ob,anim) (animations[ob->animation_id].faces[anim])
#define GET_ANIM_ID(ob) (ob->animation_id)

#define SET_INV_ANIMATION(ob,newanim) ob->face=&new_faces[animations[ob->inv_animation_id].faces[newanim]]
#define GET_INV_ANIMATION(ob,anim) (animations[ob->inv_animation_id].faces[anim])
#define GET_INV_ANIM_ID(ob) (ob->inv_animation_id)
/* NUM_ANIMATIONS returns the number of animations allocated.  The last
 * usuable animation will be NUM_ANIMATIONS-1 (for example, if an object
 * has 8 animations, NUM_ANIMATIONS will return 8, but the values will
 * range from 0 through 7. */
#define NUM_ANIMATIONS(ob) (animations[ob->animation_id].num_animations)
#define NUM_FACINGS(ob) (animations[ob->animation_id].facings)

extern int freearr_x[SIZEOFFREE], freearr_y[SIZEOFFREE];
extern int maxfree[SIZEOFFREE], freedir[SIZEOFFREE];

/* DM active list */
typedef struct active_DMs_struct
{
	object *op;
	struct active_DMs_struct *next;
} active_DMs;

extern active_DMs *dm_list;

extern New_Face *blank_face, *next_item_face, *prev_item_face;
extern MapLook blank_look;

/* loop time */
extern long max_time;
extern NewSocket *init_sockets;

/* time of the day tick counter */
extern unsigned long todtick;
/* daylight value. 0= totally dark. 7= daylight */
extern int world_darkness;

/* Nice to have fast access to it */
EXTERN archetype *wp_archetype;
/* Nice to have fast access to it */
EXTERN archetype *empty_archetype;
/* Nice to have fast access to it */
EXTERN archetype *base_info_archetype;
EXTERN archetype *map_archeytpe;
/* a global animation arch we use it in 2 modules, so not static */
EXTERN archetype *level_up_arch;

#define decrease_ob(xyz) decrease_ob_nr(xyz,1)

#define FREE_AND_NULL_PTR(_xyz_) {if(_xyz_){free(_xyz_); _xyz_=NULL; }}

#ifdef CALLOC
#undef CALLOC
#endif

#ifdef USE_CALLOC
# define CALLOC(x,y)	calloc(x,y)
# define CFREE(x)	free(x)
#else
# define CALLOC(x,y)	malloc(x*y)
# define CFREE(x)	free(x)
#endif

/** Settings structure */
typedef struct Settings {
	/* logfile to use */
    char    *logfilename;

	/* port for new client/server */
    uint16  csport;

	/* Default debugging level */
    LogLevel debug;

	/* Set to dump various values/tables */
    uint8 dumpvalues;

	/* additional argument for some dump functions */
    char *dumparg;

	/* If true, detach and become daemon */
    uint8 daemonmode;

	/* parameters that were passed to the program */
    int argc;

	/* Only used by xio.c, so will go away at some time */
    char **argv;

	/* read only data files */
    char *datadir;

	/* read/write data files */
    char *localdir;

	/* Where the map files are */
    char *mapdir;

	/* name of the archetypes file - libdir is prepended */
    char *archetypes;

	/* location of the treasures file. */
    char *treasures;

	/* directory for the unique items */
    char *uniquedir;

	/* Directory to use for temporary files */
    char *tmpdir;

	/* If true, chars lose a random stat when they die */
    uint8 stat_loss_on_death;

	/* If true, players can gain perm exp */
    uint8 use_permanent_experience;

	/* If true, Death stat depletion based on level etc */
    uint8 balanced_stat_loss;

	/* Number of seconds to put player back at home */
    int	reset_loc_time;

    /* The meta_ is information for the metaserver.  These are set in
     * the lib/settings file. */

	/* True if we should send updates */
    unsigned int   meta_on:1;

	/* Hostname/ip addr of the metaserver */
    char    meta_server[MAX_BUF];

	/* Hostname of this host */
    char    meta_host[MAX_BUF];

	/* Port number to use for updates */
    uint16  meta_port;

	/* Comment we send to the metaserver */
    char    meta_comment[MAX_BUF];

	/* starting x tile for the worldmap */
    uint32  worldmapstartx;

	/* starting y tile for the worldmap */
    uint32  worldmapstarty;

	/* number of tiles wide the worldmap is */
    uint32  worldmaptilesx;

	/* number of tiles high the worldmap is */
    uint32  worldmaptilesy;

	/* number of squares wide in a wm tile */
    uint32  worldmaptilesizex;

	/* number of squares high in a wm tile */
    uint32  worldmaptilesizey;

	/* how dynamic is the world? */
    uint16  dynamiclevel;
} Settings;

extern Settings settings;

/* 0.94.1 - change to GETTIMEOFDAY macro - SNI systems only one one option.
 * rather than have complex #ifdefs throughout the file, lets just figure
 * it out once, here at the top.
 * Have no idea if that is the right symbol to check on for NetBSD,
 * but NetBSD does use 2 params.
 * Move this to global.h from time.c since its also used in arch.c */

#ifdef GETTIMEOFDAY_TWO_ARGS
#define GETTIMEOFDAY(last_time) gettimeofday(last_time, (struct timezone *) NULL);
#else
#define GETTIMEOFDAY(last_time) gettimeofday(last_time);
#endif

/* GROS: Those are used by plugin events (argument fixthem) */
#define SCRIPT_FIX_ACTIVATOR 2
#define SCRIPT_FIX_ALL 1
#define SCRIPT_FIX_NOTHING 0

/* include some global project headers */
#ifndef __CEXTRACT__
#include "libproto.h"
#include "sockproto.h"
#endif

#include "plugin.h"

#endif