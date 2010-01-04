/************************************************************************
*            Atrinik, a Multiplayer Online Role Playing Game            *
*                                                                       *
*    Copyright (C) 2009-2010 Alex Tokar and Atrinik Development Team    *
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
 * This file deals with things like flags, object types, and a lot
 * more.
 *
 * @todo
 * This file is really too large. With all the .h files
 * around, this file should be better split between them - things
 * that deal with objects should be in objects.h, things dealing
 * with players in player.h, etc. As it is, everything just seems
 * to be dumped in here. */

#ifndef DEFINE_H
#define DEFINE_H

/* Crossfire requires ANSI-C, but some compilers "forget" to define it.
 * Thus the prototypes made by cextract don't get included correctly. */
#if !defined(__STDC__)
#error "Your ANSI C compiler should be defining __STDC__";
#endif

#ifndef WIN32
#include <autoconf.h>
#endif

/* Decstations have trouble with fabs()... */
#define FABS(x) ((x) < 0 ? -(x) : (x))
#define abs(x) ((x) < 0 ? -(x) : (x))

#ifdef __NetBSD__
#include <sys/param.h>
#endif
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif
#ifndef SGN
#define SGN(x) ((x) > 0 ? 1 : ((x) < 0 ? - 1 : 0))
#endif

#ifndef NAME_MAX
#define NAME_MAX 255
#endif

/** The maximum legal value of any stat */
#define MAX_STAT        30
/** The minimum legal value of any stat */
#define MIN_STAT        1

/** Used for all kinds of things */
#define MAX_BUF             256
#define VERY_BIG_BUF        1024
/** Used for messages - some can be quite long */
#define HUGE_BUF            4096
/** Max length a packet could be */
#define SOCKET_BUFLEN       4096
/** Maximum size of player name */
#define MAX_NAME            16
#define BIG_NAME            32
#define MAX_EXT_TITLE       98

#define MAX_ANIMATIONS      256

/**
 * @defgroup identify_modes Identify modes
 * Modes for cast_identify().
 *@{*/
/** Normal identification. */
#define IDENTIFY_MODE_NORMAL    0
/** Identify everything. */
#define IDENTIFY_MODE_ALL       1
/** Identify only marked item. */
#define IDENTIFY_MODE_MARKED    2
/*@}*/

/**
 * @defgroup spelllist_modes Spell list modes
 * Spell list commands for client spell list
 *@{*/
/** Add a spell to the spell list */
#define SPLIST_MODE_ADD		0
/** Remove a spell from the spell list */
#define SPLIST_MODE_REMOVE	1
/** Update a spell in the spell list */
#define SPLIST_MODE_UPDATE	2
/*@}*/

/**
 * @defgroup golem_control_modes Golem control modes
 * For golem control function sent to client
 *@{*/
/** Release a golem */
#define GOLEM_CTR_RELEASE   0
/** Get control over a golem */
#define GOLEM_CTR_ADD       1
/*@}*/

/** Marks no skill used */
#define CHOSEN_SKILL_NO (99999)

/** Town portal destination name */
#define PORTAL_DESTINATION_NAME "Town portal destination"
#define PORTAL_ACTIVE_NAME "Existing town portal"

/**
 * @defgroup los_blocked_modes LoS blocked modes
 * Line of Sight (los.c) defines
 *@{*/
/** It's visible */
#define BLOCKED_LOS_VISIBLE     0x00
/** Ignore this tile for blocksview/visible changes */
#define BLOCKED_LOS_IGNORE      0x01
/** Visible but will block all behind */
#define BLOCKED_LOS_BLOCKSVIEW  0x02
/** Sight is blocked */
#define BLOCKED_LOS_BLOCKED     0x04
/** Tile is not visible because it is not part of legal map */
#define BLOCKED_LOS_OUT_OF_MAP  0x08
/*@}*/

/**
 * @defgroup type_defines Type defines
 * <h1>Type Defines</h1>
 * Only add new values to this list if somewhere in the program code,
 * it is actually needed.  Just because you add a new monster does not
 * mean it has to have a type defined here.  That only needs to happen
 * if in some .c file, it needs to do certain special actions based on
 * the monster type, that can not be handled by any of the numerous
 * flags.
 *
 * Also, if you add new entries, try and fill up the holes in this list.
 *
 * Type 0 will be undefined and show a non valid type information.
 *@{*/

/** The object is a player object. */
#define PLAYER		            1
#define BULLET		            2
#define ROD		                3
#define TREASURE	            4
#define POTION		            5
#define FOOD		            6
#define POISON		            7
#define BOOK		            8
#define CLOCK		            9
#define FBULLET		            10
#define FBALL		            11
#define LIGHTNING	            12
#define ARROW		            13
#define BOW		                14
#define WEAPON		            15
#define ARMOUR		            16
#define PEDESTAL	            17
#define ALTAR		            18
#define CONFUSION	            19
#define LOCKED_DOOR	            20
#define SPECIAL_KEY	            21
#define MAP		                22
#define DOOR		            23
#define KEY		                24
#define MMISSILE	            25
#define TIMED_GATE	            26
#define TRIGGER		            27
#define GRIMREAPER	            28
#define MAGIC_EAR	            29
#define TRIGGER_BUTTON	        30
#define TRIGGER_ALTAR	        31
#define TRIGGER_PEDESTAL        32
#define SHIELD		            33
#define HELMET		            34
#define HORN		            35
#define MONEY		            36
/** Object for applying character class modifications to someone */
#define CLASS                   37
#define GRAVESTONE	            38
#define AMULET		            39
#define PLAYERMOVER	            40
#define TELEPORTER	            41
#define CREATOR		            42
/**
 * Skills are similar to abilites, but
 * not related to spells.
 * @author njw@cs.city.ac.u */
#define SKILL		            43
/**
 * An experience 'object'. Needed for multi-exp/skills
 * hack.
 * @author b.t. thomas@astro.psu.edu */
#define EXPERIENCE	            44
#define EARTHWALL	            45
#define GOLEM		            46
#define BOMB		            47
#define THROWN_OBJ	            48
#define BLINDNESS	            49
#define GOD		                50

/**
 * Detector is an object which notices the presense of
 * another object and is triggered like buttons.
 * @author peterm */
#define DETECTOR	            51
#define SPEEDBALL	            52
#define DEAD_OBJECT	            53
#define DRINK		            54
/**
 * Inserts an invisible, weightless
 * force into a player with a specified string. */
#define MARKER                  55
#define HOLY_ALTAR	            56
#define PLAYER_CHANGER          57

#define PEARL                   59
#define GEM		                60
#define FIRECHEST	            61
#define FIREWALL	            62
#define ANVIL                   63

/**
 * @author b.t. thomas@nomad.astro.psu.edu */
#define CHECK_INV	            64

/**
 * Values of last_sp set how to change:
 * <ul>
 * <li>0 = furious, all monsters become aggressive</li>
 * <li>1 = angry, all but friendly become aggressive</li>
 * <li>2 = calm, all aggressive monsters calm down</li>
 * <li>3 = sleep, all monsters fall asleep</li>
 * <li>4 = charm, monsters become pets</li>
 * </ul>
 * @author b.t. thomas@nomad.astro.psu.edu */
#define MOOD_FLOOR	            65
#define EXIT		            66

/** This object is an age force */
#define TYPE_AGE_FORCE			67
#define SHOP_FLOOR	            68
#define SHOP_MAT	            69
#define RING		            70

/** This is a floor tile -> native layer 0 */
#define FLOOR                   71

/**
 * Animal 'body parts'
 * @author b.t. thomas@nomad.astro.psu.edu */
#define FLESH		            72

/** Metals and minerals */
#define INORGANIC	            73

/** New light source for player */
#define TYPE_LIGHT_APPLY        74

#define LIGHTER		            75

#define TRAP_PART	            76

/** This is a wall. Put it always in layer 1 if not set is_floor */
#define WALL                    77

/** This is now light source on a map (invisible lights) */
#define LIGHT_SOURCE            78

/**
 * Miscellaneous objects are for objects without a function
 * in the engine. Like statues, clocks, chairs, etc.
 *
 * If perhaps we create a function where we can sit
 * on chairs, we create a new type and remove all
 * chairs from here. */
#define MISC_OBJECT             79

/** A real living creature */
#define MONSTER                 80

/** A spawn point or monster generator object */
#define SPAWN_POINT             81

/** Refilling item for TYPE_LIGHT_APPLY */
#define TYPE_LIGHT_REFILL       82

/**
 * Inactive default mob inside spawn point inv.
 * This object is somewhat special because it's generated.
 * It's only a copy and not a real monster nor an active object. */
#define SPAWN_POINT_MOB			83

/**
 * This is put inside a mob, created from a spawn point.
 * It is used to track back the mob to the spawn point. */
#define SPAWN_POINT_INFO		84
#define SPELLBOOK	            85

/** Body parts which can't be eaten - dragon scales for example */
#define ORGANIC					86

#define CLOAK		            87
#define CONE		            88

/** aura spell object */
#define AURA                    89

#define SPINNER		            90
#define GATE		            91
#define BUTTON		            92
#define CF_HANDLE		        93
#define PIT		                94
#define TRAPDOOR	            95
#define WORD_OF_RECALL	        96
#define PARAIMAGE	            97
#define SIGN		            98
#define BOOTS		            99
#define GLOVES		            100

/** This object holds the real base stats of mobs or other active objects */
#define TYPE_BASE_INFO			101

/**
 * Only used for spawn point monsters:
 *
 * If found inside the monster, there is a random chance based on the
 * object's weight limit to drop the object's inventory into the
 * monster. */
#define TYPE_RANDOM_DROP		102

#define CONVERTER	            103
#define BRACERS		            104

/**
 * That's the poison force... If a player applies for example
 * a POISON object (poison food), this force is inserted in
 * the player and does the poison effect until it wears out
 * or gets removed */
#define POISONING	            105
#define SAVEBED		            106
#define POISONCLOUD	            107
#define FIREHOLES	            108
#define WAND		            109
#define ABILITY		            110
#define SCROLL		            111
#define DIRECTOR	            112
#define GIRDLE		            113
#define FORCE		            114
/** A force, holding the effect of a potion */
#define POTION_EFFECT           115

/** To make it different from GEM - that's needed to have a better */
#define TYPE_JEWEL				116

/** Use from the artifacts file */
#define TYPE_NUGGET				117

/** Event/script object */
#define TYPE_EVENT_OBJECT		118

/** Waypoint object */
#define TYPE_WAYPOINT_OBJECT	119

/** Ised to store quest infos in players */
#define TYPE_QUEST_CONTAINER	120

/** Id for close_container archetype. */
#define CLOSE_CON	            121
#define CONTAINER	            122
#define ARMOUR_IMPROVER         123
#define WEAPON_IMPROVER         124

/**
 * This is a "raw" (abstract) wealth object. When generated
 * it's tranformed into real money depending on the enviroment
 * where it's generated. (most of the time by treasure list and
 * transformed to money by using level of mob or map to generating
 * a fitting amount of money basing on the base setting). */
#define TYPE_WEALTH				125

/** A beacon. */
#define BEACON                  126

/* unused: 127 - 129 */

/**
 * Can add a skill to player's inventory
 * @author b.t. thomas@nomad.astro.psu.edu */
#define SKILLSCROLL	            130

#define DEEP_SWAMP	            138
#define IDENTIFY_ALTAR	        139
#define CANCELLATION	        141

/**
 * Shop inventories
 * @author Mark Wedel (mark@pyramid.com) */
#define MENU		            150

/**
 * Ball lightning and color spray
 * @author peterm */
#define BALL_LIGHTNING          151
#define SWARM_SPELL             153
#define RUNE                    154

#define POWER_CRYSTAL           156
#define CORPSE                  157

#define DISEASE                 158
#define SYMPTOM                 159

/** Pure internal system object */
#define TYPE_VOID_CONTAINER		255
/*@}*/

/**
 * @defgroup sub_type_defines Sub type defines
 * <h1>Sub Type Defines</h1>
 * These are very special sub_types - used by different types.
 * The reason is, that different items can be missiles - amuns and throw items.
 * First, we have the amun types - arrows for bows, or bolts for crossbows.
 * They need a firing weapon and get fired indirect.
 *
 * For throwing we have some more types.
 *
 * Second, we have the 'real' throw weapons - like darts or shurikens.
 *
 * Third, there are weapons which can be used as hand weapons but
 * also as throw weapons. A hammer like mjoellnir or a simple spear, for example.
 *
 * Fourth, there are special throw items. ATM, we have:
 *
 * Potions - like firestorm
 *
 * Dust - like dust of blinding... etc.
 * Dusts are also from 'type POTION' but use a different base arch.
 *
 * These special items will handled different - we allow the player to throw
 * ANY dust or potion. But only when the potion/dust is from sub_type _missile_xx
 * we include the skill id and only these items will do a range effect.
 *
 * Every potion/dust will have a level (like a spell or rod). If this level is
 * 40% higher than our throw skill (and more than 5 level higher), then throwing
 * will fail, like we try to use a too high item device.
 *
 * If we apply a throw potion/dust, the effect will triggered (a firestorm potion
 * will explode) but no skill id will be inserted in the firestorm objects.
 * So, the player and perhaps some mobs will take damage - but it will not give
 * any exp when this will happen. MNT-11-2002
 *
 * @todo
 * Have not included this 40% throw thing - perhaps later. MT-2003
 *@{*/

/**
 * @defgroup missile_sub_types Missile sub types
 * All the possible missile sub type defines.
 *@{*/
/** Ammunition for bows = arrows */
#define ST1_MISSILE_BOW     1
/** Ammunition for crossbows = bolts */
#define ST1_MISSILE_CBOW    2
/** Ammunition for slings = sling stones */
#define ST1_MISSILE_SSTONE  3
/** Throwing missile */
#define ST1_MISSILE_THROW   128
/*@}*/

/**
 * @defgroup throwing_missile_sub_types Throwing missile sub types
 * Different kinds of throwing missiles, like impact
 * and slash, etc.
 *@{*/
/** Impact throwing missile */
#define ST1_MISSILE_IMPACT  (ST1_MISSILE_THROW | 0)
/** Slash throwing missile */
#define ST1_MISSILE_SLASH   (ST1_MISSILE_THROW | 1)
/** Pierce throwing missile */
#define ST1_MISSILE_PIERCE  (ST1_MISSILE_THROW | 2)
/** Cleave throwing missile */
#define ST1_MISSILE_CLEAVE  (ST1_MISSILE_THROW | 3)
/** Special boulder-like throwing missile (impact damage too) */
#define ST1_MISSILE_BOULDER (ST1_MISSILE_THROW | 4)
/*@}*/

/**
 * @defgroup one_handed_weapon_sub_types One handed weapon sub types
 * One handed weapons - allows shield in second hand.
 *@{*/
/** Impact damage: clubs, maces, hammers, etc. */
#define WEAP_1H_IMPACT  0
/** Slash: swords, scimitars */
#define WEAP_1H_SLASH   1
/** Pierce: daggers, rapiers */
#define WEAP_1H_PIERCE  2
/** Cleave: axes */
#define WEAP_1H_CLEAVE  3
/*@}*/

/**
 * @defgroup two_handed_weapon_sub_types Two handed weapon sub types
 * Two handed weapons need base one handed skill and two handed mastery
 * to use. Experience goes always in one handed skill - mastery skills
 * are indirect skills.
 * @{*/
/** Impact damage: clubs, maces, hammers, etc. */
#define WEAP_2H_IMPACT  4
/** Slash: swords, scimitars */
#define WEAP_2H_SLASH   5
/** Pierce: daggers, rapiers */
#define WEAP_2H_PIERCE  6
/** Cleave: axes */
#define WEAP_2H_CLEAVE  7
/*@}*/

/**
 * @defgroup polearm_weapon_sub_types Polearm weapon sub types
 * Same like two handed weapons but for polearms.
 *@{*/
/** Impact damage: clubs, maces, hammers, etc. */
#define WEAP_POLE_IMPACT    8
/** Slash: swords, scimitars */
#define WEAP_POLE_SLASH     9
/** Pierce: daggers, rapiers */
#define WEAP_POLE_PIERCE    10
/** Cleave: axes */
#define WEAP_POLE_CLEAVE    11
/*@}*/

/**
 * @defgroup range_weapon_sub_types Range weapon sub types
 * Range weapons sub types
 *@{*/
/** Bows */
#define RANGE_WEAP_BOW      0
/** Crossbows */
#define RANGE_WEAP_XBOWS    1
/** Slings */
#define RANGE_WEAP_SLINGS   2
/** Firearms */
#define RANGE_WEAP_FIREARMS 3
/*@}*/

/**
 * @defgroup skill_type_sub_types Skill type sub types
 * Some skills are auto used, some should not be
 * able to use with fire xxx (use_skill)
 *@{*/
/** Normal skill but not direct usable with use_skill() */
#define ST1_SKILL_NORMAL    0
/** Skill can be used with fire and use_skill() */
#define ST1_SKILL_USE       1
/** Skill is used indirect by server */
#define ST1_SKILL_INDIRECT  2
/*@}*/

/**
 * @defgroup spell_book_sub_types Spell book sub types
 * Spell books can be different types: mage, cleric, and so on.
 *@{*/
/** Cleric spell book */
#define ST1_SPELLBOOK_CLERIC 1
/** Mage spell book */
#define ST1_SPELLBOOK_MAGE   2
/*@}*/

/**
 * @defgroup container_sub_types Container sub types
 * Containers can be different items: normal containers, mob corpse
 * or player corpse.
 *
 * All containers with sub_type higher or equal to 64 are personalized.
 * Personalized containers have name of the owner in their slaying
 * field and only the owner can open it.
 *
 * All containers with sub_type higher or equal to 128 are party
 * containers and have the party ID stored in the slaying field. Only
 * the party members can open it.
 *@{*/
/** Normal container */
#define ST1_CONTAINER_NORMAL           0
/** Corpse container */
#define ST1_CONTAINER_CORPSE           1
/** Player container */
#define ST1_CONTAINER_DEAD_PL          2

/** Personalized normal container */
#define ST1_CONTAINER_NORMAL_player    64
/** Personalized corpse container */
#define ST1_CONTAINER_CORPSE_player    65

/** Party normal container */
#define ST1_CONTAINER_NORMAL_party     128
/** Party corpse container */
#define ST1_CONTAINER_CORPSE_party     129
/*@}*/

/**
 * @defgroup exit_sub_types Exit sub types
 * Sub types for EXIT objects. If set, a teleport sound is played.
 *@{*/
#define ST1_EXIT_SOUND_NO       0
#define ST1_EXIT_SOUND          1
/*@}*/

/**
 * @defgroup door_sub_types Door sub types
 * Sub types for DOOR objects.
 *@{*/
/** Normal door */
#define ST1_DOOR_NORMAL     0
/** Different sound */
#define ST1_DOOR_CURTAIN    1
/*@}*/
/*@}*/

/**
 * @defgroup size_of_free_defines Size of free defines
 * Instead of using arbitrary constants for indexing the
 * freearr, add these values.  <= SIZEOFFREE1 will get you
 * within 1 space.  <= SIZEOFFREE2 wll get you withing
 * 2 spaces, and the entire array (<= SIZEOFFREE) is
 * three spaces.
 *@{*/
#define SIZEOFFREE1     8
#define SIZEOFFREE2     24
#define SIZEOFFREE      49
/*@}*/

/** Number of different spells */
#define NROFREALSPELLS  42
/** Number of spell paths. */
#define NRSPELLPATHS    20

/**
 * @defgroup terrain_type_flags Terrain type flags
 * Terrain type flags
 * These values are used from terrain_typ and terrain_flag
 * Arches without terrain flags become AIRBREATH as default.
 * These values also define the enviroment of the map tile position
 *@{*/
#define TERRAIN_NOTHING         0
/* That's default - walk on earth */
#define TERRAIN_AIRBREATH       1
/* Walk on water - deep water too */
#define TERRAIN_WATERWALK       2
/* You can move underwater and on land */
#define TERRAIN_WATERBREATH     4
/* Walk over lava or fire */
#define TERRAIN_FIREWALK        8
/* You can move in fire environment (fire elemental dimension, hell, ...) */
#define TERRAIN_FIREBREATH      16
/* Move "on clouds" in the air - not flying. Similar to the story of the magic bean */
#define TERRAIN_CLOUDWALK       32
/*@}*/

/**
 * @defgroup flags_structure Flags Structure
 * Flag structure now changed.
 * Each flag is now a bit offset, starting at zero.  The macros
 * will update/read the appropriate flag element in the object
 * structure.
 *
 * Hopefully, since these offsets are integer constants set at run time,
 * the compiler will reduce the macros something as simple as the
 * old system was.
 *
 * Flags now have FLAG as the prefix.  This to be clearer, and also
 * to make sure F_ names are not still being used anyplace.
 *
 * The macros below assume that the flag size for each element is 32
 * bits.  IF it is smaller, bad things will happen.  See structs.h
 * for more info.
 *
 * All functions should use the macros below.  In process of converting
 * to the new system, I find several files that did not use the previous
 * macros.
 *
 * If any FLAG's are added, be sure to add them to the flag_links structure
 * in common/loader.c, if necessary.
 *
 * flags[0] is 0 to 31
 * flags[1] is 32 to 63
 * flags[2] is 64 to 95
 * flags[3] is 96 to 127
 *@{*/

/**
 * @defgroup object_flag_macros Object flag macros
 * Basic macros to do the above.
 *@{*/

/**
 * Set flag of of an object.
 * @param xyz The object
 * @param p The flag to set */
#define SET_FLAG(xyz, p) \
	((xyz)->flags[p / 32] |= (1U << (p % 32)))

/**
 * Clear flag of an object.
 * @param xyz The object
 * @param p The flag to clear */
#define CLEAR_FLAG(xyz, p) \
	((xyz)->flags[p / 32] &= ~(1U << (p % 32)))

/**
 * Query flag of an object.
 * @param xyz The object
 * @param p The flag to query */
#define QUERY_FLAG(xyz, p) \
	((xyz)->flags[p / 32] & (1U << (p % 32)))
/*@}*/

/**
 * @defgroup object_multiflag_macros Object multiflag macros
 * This is rarely used but needed for some flags, which are
 * used for intern handling like INVISIBLE or WALK_OFF. Because
 * some core functions like remove_ob() use this, it will be better
 * we set this ONE time outside instead of every time in remove_ob():
 * we skip the call for the head in this way.
 *@{*/
#define SET_MULTI_FLAG(xyz, p)                          \
{                                                       \
	object *_tos_;                                      \
                                                        \
	for (_tos_ = xyz; _tos_; _tos_ = _tos_->more)       \
	{                                                   \
		((_tos_)->flags[p / 32] |= (1U << (p % 32)));   \
	}                                                   \
}

#define CLEAR_MULTI_FLAG(xyz, p)                        \
{                                                       \
	object *_tos_;                                      \
                                                        \
	for (_tos_ = xyz; _tos_; _tos_ = _tos_->more)       \
	{                                                   \
		((_tos_)->flags[p / 32] &= ~(1U << (p % 32)));  \
	}                                                   \
}
/*@}*/

/**
 * @defgroup item_types Item types
 * Convenience macros to determine what kind of things we are dealing with
 *@{*/
#define IS_WEAPON(op) \
	(op->type == ARROW || op->type == BOW || op->type == WEAPON)

#define IS_ARMOR(op) \
	(op->type == ARMOUR || op->type == SHIELD || op->type == HELMET || \
	 op->type == CLOAK || op->type == BOOTS || op->type == GLOVES || \
	 op->type == BRACERS || op->type == GIRDLE)

#define IS_LIVE(__op__) ( (__op__)->type == PLAYER || QUERY_FLAG((__op__),FLAG_MONSTER) || \
						 (QUERY_FLAG((__op__), FLAG_ALIVE) && !QUERY_FLAG((__op__), FLAG_GENERATOR)))

#define IS_ARROW(op) \
	(op->type == ARROW || op->type == MMISSILE || op->type == BULLET)
/*@}*/

/** Used in blocked() when we only want know about blocked by something */
#define TERRAIN_ALL 0xffff


/**
 * @defgroup flag_defines Flag defines
 * The flags.
 *
 * @note
 * You MUST set the FLAG_xx to V_xxx array in loader.l too when
 * you change something here! Search for NUM_FLAGS in loader.l for more.
 *
 * @warning
 * The first 8 bit are used from the map2 cmd as direct mapped data.
 * The order must stay as it is here!
 * @{*/
/** NPC is sleeping */
#define FLAG_SLEEP			0
/** confused... random dir when moving and problems to do actions */
#define FLAG_CONFUSED		1
/** Object is paralyzed */
#define FLAG_PARALYZED      2
/** Monster is scared (for players: this is feared) */
#define FLAG_SCARED			3
/** If set, object cannot see (the map) with eyes */
#define FLAG_BLIND			4
/** only THIS invisible can be seen with seen_invisible */
#define FLAG_IS_INVISIBLE	5
/** object is etheral  - means transparent and special protected */
#define FLAG_IS_ETHEREAL	6
/** NOT USED from map2. alignment flag */
#define FLAG_IS_GOOD		7

/** Object can't be picked up */
#define FLAG_NO_PICK	 	8
/** Applied when it's walked upon */
#define FLAG_WALK_ON	 	9
/** Nothing can pass (wall() is true) */
#define FLAG_NO_PASS		10
/** The object looks at archetype for faces */
#define FLAG_ANIMATE		11
/**
 * Uses the stats.exp/1000 to slow down
 * I use this flag now in 2 ways: for objects like floors
 * it force objects to move slow. For monsters with speed,
 * it force monsters to move slow! (slow spell or snared!) */
#define FLAG_SLOW_MOVE		12
/** Not affected by WALK_ON or SLOW_MOVE) */
#define FLAG_FLYING			13
/**
 * A object with this flag is used like a object with
 * type == MONSTER. SO, we can use type GOLEMS objects
 * for example in attack functions like MONSTER without
 * checking all possible different type defines. */
#define FLAG_MONSTER		14
/** Will help players */
#define FLAG_FRIENDLY		15

/*
 * REMOVED and BEEN_APPLIED are direct used from CAN_MERGE - change it too when
 * you move this flag! */

/** Object is not in any map or invenory */
#define FLAG_REMOVED	 	16
/** The object has been applied */
#define FLAG_BEEN_APPLIED	17
/** Will be applied when created */
#define FLAG_AUTO_APPLY		18
/** Will generate treasure when applied */
#define FLAG_TREASURE		19
/** alignment of this object: we need the explicit neutral setting for items */
#define FLAG_IS_NEUTRAL		20
/** Will see invisible player */
#define FLAG_SEE_INVISIBLE 	21
/** Object can be rolled */
#define FLAG_CAN_ROLL		22
/** Will generate type ob->stats.food */
#define FLAG_GENERATOR		23

/** Object can change face with direction */
#define FLAG_IS_TURNABLE 	24
/** Object is applied when left */
#define FLAG_WALK_OFF		25
/** As WALK_ON, but only with FLAG_FLYING */
#define FLAG_FLY_ON			26
/** As WALK_OFF, but only with FLAG_FLYING */
#define FLAG_FLY_OFF		27
/** When (--food<0) the object will exit */
#define FLAG_IS_USED_UP		28
/** Not implemented yet */
#define FLAG_IDENTIFIED		29
/** Object reflects from walls (lightning) */
#define FLAG_REFLECTING		30
/** Changes to other_arch when anim is done*/
#define FLAG_CHANGING		31

/* Start of values in flags[1] */

/** Object splits into stats.food other objs */
#define FLAG_SPLITTING		32
/** Object will hit back when hit */
#define FLAG_HITBACK		33
/** Object was given to player at start */
#define FLAG_STARTEQUIP		34
/** Object blocks view */
#define FLAG_BLOCKSVIEW		35
/** Monster is undead */
#define FLAG_UNDEAD			36
/** The object can stack */
#define FLAG_CAN_STACK      37
/** Monster doesn't attack players */
#define FLAG_UNAGGRESSIVE	38
/** object will give missile reflection */
#define FLAG_REFL_MISSILE	39

/** object will give spell reflection */
#define FLAG_REFL_SPELL		40
/** Spells (some) can't pass this object */
#define FLAG_NO_MAGIC		41
/** fix_player() won't be called */
#define FLAG_NO_FIX_PLAYER	42
/** alignment flags */
#define FLAG_IS_EVIL		43
/** at->faces[hp*animations/maxhp] at hit */
#define FLAG_TEAR_DOWN		44
/**
 * Object runs away from nearest player
 * but can still attack at a distance */
#define FLAG_RUN_AWAY		45
/**
 * Objects with can_pass_thru can pass
 * thru this object as if it wasn't there */
#define FLAG_PASS_THRU		46
/** Can pass thru... */
#define FLAG_CAN_PASS_THRU	47

/** Can pick up */
#define FLAG_PICK_UP		48
/** Item is really unique (UNIQUE_ITEMS) */
#define FLAG_UNIQUE			49
/** Object can't be dropped */
#define FLAG_NO_DROP		50
/** every item with quality use up. if this is set, it don't use up by physical forces */
#define FLAG_INDESTRUCTIBLE	51
/** (Monster) can learn and cast spells */
#define FLAG_CAST_SPELL		52
/** (Monster) can read scroll */
#define FLAG_USE_SCROLL		53
/** (Monster) can apply and use range items */
#define FLAG_USE_RANGE		54
/** (Monster) can apply and fire bows */
#define FLAG_USE_BOW		55

/** (Monster) can wear armour/shield/helmet */
#define FLAG_USE_ARMOUR		56
/** (Monster) can wield weapons */
#define FLAG_USE_WEAPON		57
/** (Monster) can use rings, boots, gauntlets, etc */
#define FLAG_USE_RING		58
/** (Monster) has a range item readied... 8) */
#define FLAG_READY_RANGE	59
/** not implemented yet */
#define FLAG_READY_BOW		60
/** X-ray vision */
#define FLAG_XRAYS			61
/** Avoids step_on/fly_on to this object */
#define FLAG_NO_APPLY		62
/** Can't see what's underneath this object */
#define FLAG_IS_FLOOR		63

/* Start of values in flags[2] */

/** Saves a players' life once, then destr. */
#define FLAG_LIFESAVE		64
/**
 * item is magic - intern used.
 * player use FLAG_KNOWN_MAGICAL */
#define FLAG_IS_MAGICAL     65
/** Object can fight (or be fought) */
#define FLAG_ALIVE	 		66
/** NPC will not (ever) move */
#define FLAG_STAND_STILL	67
/** NPC will move randomly */
#define FLAG_RANDOM_MOVE	68
/** NPC will evaporate if there is no enemy */
#define FLAG_ONLY_ATTACK	69
/** Object has special privilegies */
#define FLAG_WIZ	 		70
/** Will wake monsters with less range */
#define FLAG_STEALTH		71

/** The wizard can go through walls */
#define FLAG_WIZPASS		72
/** The object is linked with other objects */
#define FLAG_IS_LINKED		73
/** The object is cursed */
#define FLAG_CURSED			74
/** The object is _very_ cursed */
#define FLAG_DAMNED			75
/** The object will be visible behind walls (disabled MT2003 - read los.c) */
#define FLAG_SEE_ANYWHERE	76
/** The object is known to be magical */
#define FLAG_KNOWN_MAGICAL	77
/** The object is known to be cursed */
#define FLAG_KNOWN_CURSED	78
/** The monster can use skills */
#define FLAG_CAN_USE_SKILL	79

/** Object is designed to be thrown. */
#define FLAG_IS_THROWN		80
#define FLAG_VUL_SPHERE		81
#define FLAG_PROOF_SPHERE	82
#define FLAG_IS_MALE		83
#define FLAG_IS_FEMALE		84
/** Object is ready for use by living */
#define FLAG_APPLIED	 	85
/** Item will not be dropped from inventory */
#define FLAG_INV_LOCKED		86
/** Item is wooded terrain */
#define FLAG_IS_WOODED		87

/** Item is hilly/mountain terrain */
#define FLAG_IS_HILLY		88
/** (Monster or Player) has a skill readied */
#define FLAG_READY_SKILL	89
/** (Monster or Player) has a weapon readied */
#define FLAG_READY_WEAPON	90
/** If set, item cannot be identified w/ a skill */
#define FLAG_NO_SKILL_IDENT	91
/** Player was once a wiz */
#define FLAG_WAS_WIZ	 	92
/** if set ob not effected by darkness */
#define FLAG_SEE_IN_DARK	93
/** container can make alchemical stuff */
#define FLAG_IS_CAULDRON	94
/** item is a 'powder', effects throwing */
#define FLAG_DUST			95

/* Start of values in flags[3] */

/** Item can't be stolen */
#define FLAG_NO_STEAL			96
/**
 * Monster can only hit once before going
 * away (replaces ghosthit) */
#define FLAG_ONE_HIT			97
/**
 * THIS IS A DEBUG FLAG ONLY.  We use it to
 * detect cases were the server is trying
 * to send an upditem when we have not
 * actually sent the item. */
#define FLAG_CLIENT_SENT		98
/** monster will attack closest living object */
#define FLAG_BERSERK            99
/** object will not attack */
#define FLAG_NO_ATTACK          100
/** monster can't be damaged */
#define FLAG_INVULNERABLE       101

/** this is a special quest object */
#define FLAG_QUEST_ITEM			102

/**
 * object is trapped - most common a container with
 * a known trap inside. This info so useful for client
 * below and inventory look. */
#define FLAG_IS_TRAPPED			103

/**
 * Thats the item damage flags. Every flag determinate
 * that a worn or wielded item can be damaged from this
 * effect. If the effect for a item is set, then he can
 * be "proofed" against it. It the proof flag is set, the
 * item don't get damage from this effect anymore */
#define FLAG_VUL_ELEMENTAL		104
#define FLAG_PROOF_ELEMENTAL	105
#define FLAG_VUL_MAGIC			106
#define FLAG_PROOF_MAGIC		107
#define FLAG_VUL_PHYSICAL		108
#define FLAG_PROOF_PHYSICAL		109
/** thats old invisible - now sys_object (which are invisible) */
#define FLAG_SYS_OBJECT			110
/** when putting a object on map - do it exactly on position */
#define FLAG_USE_FIX_POS		111

/** Object hasn't been paid for yet */
#define FLAG_UNPAID	 			112
/** if set, object falls under heavy ageing effects */
#define FLAG_IS_AGED			113
/** if a applyable item has this set, he makes the wearer invisible */
#define FLAG_MAKE_INVISIBLE		114
/** same as make_invisibile but for ethereal */
#define FLAG_MAKE_ETHEREAL		115
/** object "is player". */
#define FLAG_IS_PLAYER			116
/**
 * object name is "unique"- for artifacts like Stormbringer.
 * Unique object normally don't have a race or material
 * (no "elven iron Stormbringer") */
#define FLAG_IS_NAMED			117
/**
 * monster with this flag are created by spawn point
 * and have a spawn info object inside inventory */
#define FLAG_SPAWN_MOB			118
/**
 * objects with this flags will not be teleported
 * from teleporters. Except, they are in a inventory
 * of a teleporter object. */
#define FLAG_NO_TELEPORT		119
/**
 * if set, this object (usally mob) will drop corpse using race name->
 * all item of the mob will put in the corpse and/or if slaying of corpse
 * is set only the player which killed the mob can access the corpse until
 * it decayed - then items drop on ground and all can grap it */
#define FLAG_CORPSE				120
/**
 * normally, corpses will only be placed when the mob has some items to drop.
 * this flag will drop a corpse even the corpse is empty */
#define FLAG_CORPSE_FORCED		121
/**
 * if a item with this flag is placed in a tile, this tile can't be entered
 * from anything ecept a player */
#define FLAG_PLAYER_ONLY		122
#define FLAG_NO_CLERIC			123
/**
 * if this flag is set, the item marked with it will flaged
 * start equipment when a player gets it (item is inserted
 * in player inventory and/or touched by a player) */
#define FLAG_ONE_DROP			124
/**
 * object will set to cursed when monster or player applies it.
 * remove curse will remove cursed 1 but not this flag. */
#define FLAG_PERM_CURSED		125
/** same as perm_cursed but for damned */
#define FLAG_PERM_DAMNED		126

/**
 * this object works like a closed door. Main function
 * is to trigger the right map flags, so a moving objects
 * know that spot is blocked by a door and he must open it first-> */
#define FLAG_DOOR_CLOSED		127
/** object was reflected (arrow, throw object...) */
#define FLAG_WAS_REFLECTED		128
/** object is used as missile (arrow, potion, magic bullet, ...) */
#define FLAG_IS_MISSILE			129
/** Arrows WILL reflect from object (most times) */
#define FLAG_CAN_REFL_MISSILE	130
/** Spells WILL reflect from object (most times) */
#define FLAG_CAN_REFL_SPELL		131

/** If a attacking force and slaying is set, this is 3 times damage */
#define FLAG_IS_ASSASSINATION	132
/** internal used from remove_ob() und insert_xx() */
#define FLAG_OBJECT_WAS_MOVED	133
/** don't save this object - remove it before we save */
#define FLAG_NO_SAVE			134

/**
 * The object has player shop open and cannot do move actions (checked
 * for in move_player(), as this is for players only). */
#define FLAG_PLAYER_SHOP		135
/*@}*/

/* flag 37 is still free (old FREED flag). Let it free for secure reason for some time */

/** Should always be equal to the last defined flag */
#define NUM_FLAGS       135
/** the number of uint32 we need to store all flags */
#define NUM_FLAGS_32    5
/*@}*/

/* Macros for invisible test. The first tests only system objects */
#define IS_SYS_INVISIBLE(__ob_) \
	QUERY_FLAG(__ob_, FLAG_SYS_OBJECT)
#define IS_INVISIBLE(__ob_,__player_) \
	(QUERY_FLAG(__ob_, FLAG_SYS_OBJECT) || (QUERY_FLAG(__ob_, FLAG_IS_INVISIBLE) && !QUERY_FLAG(__player_, FLAG_SEE_INVISIBLE)))

/* Values can go up to 127 before the size of the flags array in the
 * object structure needs to be enlarged. */
#define NROFNEWOBJS(xyz) ((xyz)->stats.food)

#define SLOW_PENALTY(xyz) ((xyz)->stats.exp) / 1000.0
#define SET_SLOW_PENALTY(xyz, fl) (xyz)->stats.exp = (sint32) ((fl) * 1000.0)

#define EXIT_PATH(xyz) (xyz)->slaying
#define EXIT_LEVEL(xyz) (xyz)->stats.food
#define EXIT_X(xyz) (xyz)->stats.hp
#define EXIT_Y(xyz) (xyz)->stats.sp

#define F_BUY 0
#define F_SELL 1
/* True value of item, unadjusted */
#define F_TRUE 2

#define DIRX(xyz) freearr_x[(xyz)->direction]
#define DIRY(xyz) freearr_y[(xyz)->direction]

#define ARMOUR_SPEED(xyz) (xyz)->last_sp
#define ARMOUR_SPELLS(xyz) (xyz)->last_heal

/**
 * @defgroup monster_movements Monster movements
 * The following definitions are for the attack_movement variable in monsters
 * if the attack_variable movement is left out of the monster archetype, or is
 * set to zero
 * the standard mode of movement from previous versions of crossfire will be
 * used. the upper four bits of movement data are not in effect when the monst
 * er has an enemy. these should only be used for non agressive monsters.
 * to program a monsters movement add the attack movement numbers to the movem
 * ment numbers example a monster that moves in a circle until attacked and
 * then attacks from a distance:
 *                                                      CIRCLE1 = 32
 *                                              +       DISTATT = 1
 *                                      -------------------
 *                      attack_movement = 33
 * @author kholland@sunlab.cit.cornell.edu
 *@{*/
/**
 * Move toward a player if far, but mantain some space,
 * attack from a distance - good for missile users only */
#define DISTATT  1
/** Run but attack if player catches up to object */
#define RUNATT   2
/** Run to then hit player then run away cyclicly */
#define HITRUN   3
/** Wait for player to approach then hit, move if hit */
#define WAITATT  4
/** Rush toward player blindly, similiar to dumb monster */
#define RUSH     5
/** Always run never attack good for sim. of weak player */
#define ALLRUN   6
/** Attack from a distance if hit as recommended by Frank */
#define DISTHIT  7
/** Monster does not try to move towards player if far */
#define WAIT2    8

/**
 * if the upper four bits of move_type / attack_movement
 * are set to this number, the monster follows a player
 * until the owner calls it back or off
 * player followed denoted by 0b->owner
 * the monster will try to attack whatever the player is
 * attacking, and will continue to do so until the owner
 * calls off the monster - a key command will be
 * inserted to do so */
#define PETMOVE 16

/**
 * if the upper four bits of move_type / attack_movement
 * are set to this number, the monster will move in a
 * circle until it is attacked, or the enemy field is
 * set, this is good for non-aggressive monsters and NPC */
#define CIRCLE1 32

/** Same as above but a larger circle is used */
#define CIRCLE2 48

/**
 * The Monster will pace back and forth until attacked
 * this is HORIZONTAL movement */
#define PACEH   64

/**
 * the monster will pace as above but the length of the
 * pace area is longer and the monster stops before
 * changing directions
 * this is HORIZONTAL movement */
#define PACEH2  80

/**
 * the monster will go in a random direction until
 * it is stopped by an obstacle, then it chooses another
 * direction. */
#define RANDO   96

/** constantly move in a different random direction */
#define RANDO2 112

/**
 * The Monster will pace back and forth until attacked
 * this is VERTICAL movement */
#define PACEV  128

/**
 * the monster will pace as above but the length of the
 * pace area is longer and the monster stops before
 * changing directions
 * this is VERTICAL movement */
#define PACEV2 144

/** The monster uses waypoints (if it has any) */
#define WPOINT 176

/* bitmasks for upper and lower 4 bits from 8 bit fields */
#define LO4    15
#define HI4    240
/*@}*/

/**
 * @defgroup st_defines Player states
 * Use of the state-variable in player objects.
 *@{*/

/** Usual state. */
#define ST_PLAYING              0
/** New character, rolling stats. */
#define ST_ROLL_STAT            1
/** New character, choosing class. */
#define ST_CHANGE_CLASS         2
/** Player just connected. */
#define ST_GET_NAME             3
/** Name entered, now for password. */
#define ST_GET_PASSWORD         4
/** New character, confirm password. */
#define ST_CONFIRM_PASSWORD     5
/*@}*/

#define BLANK_FACE_NAME "blank.111"
#define NEXT_ITEM_FACE_NAME "next_item.101"
#define PREVIOUS_ITEM_FACE_NAME "prev_item.101"

/* Defines for the luck/random functions to make things more readable */
#define PREFER_HIGH	1
#define PREFER_LOW	0

/* Socket defines */
#define SockList_AddChar(_sl_, _c_) (_sl_)->buf[(_sl_)->len++] = (_c_)
#define SockList_AddShort(_sl_, _data_)                  \
	(_sl_)->buf[(_sl_)->len++] = ((_data_) >> 8) & 0xff; \
	(_sl_)->buf[(_sl_)->len++] = (_data_) & 0xff

#define SockList_AddInt(_sl_, _data_)                     \
	(_sl_)->buf[(_sl_)->len++] = ((_data_) >> 24) & 0xff; \
	(_sl_)->buf[(_sl_)->len++] = ((_data_) >> 16) & 0xff; \
	(_sl_)->buf[(_sl_)->len++] = ((_data_) >> 8) & 0xff;  \
	(_sl_)->buf[(_sl_)->len++] = (_data_) & 0xff

/* Basically does the reverse of SockList_AddInt, but on
 * strings instead.  Same for the GetShort, but for 16 bits. */
#define GetInt_String(_data_)                                                      \
	(((_data_)[0] << 24) + ((_data_)[1] << 16) + ((_data_)[2] << 8) + (_data_)[3])
#define GetShort_String(_data_)        \
	(((_data_)[0] << 8) + (_data_)[1])

/**
 * Simple function we use below to keep adding to the same string
 * but also make sure we don't overwrite that string.
 * @param dest String to append to.
 * @param orig String to append.
 * @param curlen Current length of dest. Will be updated by this function.
 * @param maxlen Maximum length of dest buffer. */
static inline void safe_strcat(char *dest, const char *orig, int *curlen, int maxlen)
{
	if (*curlen == (maxlen - 1))
	{
		return;
	}

	strncpy(dest + *curlen, orig, maxlen - *curlen - 1);
	dest[maxlen - 1] = 0;
	*curlen += strlen(orig);

	if (*curlen > (maxlen - 1))
	{
		*curlen = maxlen - 1;
	}
}

#define DESCRIBE_PATH(retbuf, variable, name)                        \
    if (variable)                                                    \
	{                                                                \
        int i, j = 0;                                                \
        strcat(retbuf, "(" name ": ");                               \
                                                                     \
        for (i = 0; i < NRSPELLPATHS; i++)                           \
		{                                                            \
            if (variable & (1 << i))                                 \
			{                                                        \
                if (j)                                               \
                    strcat(retbuf, ", ");                            \
                else                                                 \
                    j = 1;                                           \
                                                                     \
                strcat(retbuf, spellpathnames[i]);                   \
            }                                                        \
		}                                                            \
                                                                     \
        strcat(retbuf, ")");                                         \
    }

#define DESCRIBE_PATH_SAFE(retbuf, variable, name, len, maxlen)      \
    if (variable)                                                    \
	{                                                                \
        int i, j = 0;                                                \
        safe_strcat(retbuf, "(" name ": ", len, maxlen);             \
                                                                     \
        for (i = 0; i < NRSPELLPATHS; i++)                           \
		{                                                            \
            if (variable & (1 << i))                                 \
			{                                                        \
                if (j)                                               \
                    safe_strcat(retbuf, ", ", len, maxlen);          \
                else                                                 \
                    j = 1;                                           \
                                                                     \
                safe_strcat(retbuf, spellpathnames[i], len, maxlen); \
            }                                                        \
		}                                                            \
                                                                     \
        safe_strcat(retbuf, ")", len, maxlen);                       \
    }

/**
 * Flags for apply_special().
 *
 * @anchor AP_xxx */
enum apply_flag
{
	/* Basic flags, always use one of these */
	AP_NULL = 0,
	AP_APPLY = 1,
	AP_UNAPPLY = 2,
	AP_BASIC_FLAGS = 15,
	/* Optional flags, for bitwise or with a basic flag */
	AP_NO_MERGE = 16,
	AP_IGNORE_CURSE = 32
};

/** Cut off point of when an object is put on the active list or not */
#define MIN_ACTIVE_SPEED 0.00001f

/**
 * @defgroup bresenham_algorithm Bresenham algorithm
 * Bresenham line drawing algorithm. Implemented as macros for
 * flexibility and speed.
 *@{*/

/**
 * Bresenham init.
 * dx & dy are input only and will not be changed.
 * All other parameters are the outputs which will be initialized */
#define BRESENHAM_INIT(dx, dy, fraction, stepx, stepy, dx2, dy2)      \
    {                                                                 \
        (dx2) = (dx) << 1;                                            \
        (dy2) = (dy) << 1;                                            \
                                                                      \
        if ((dy) < 0)                                                 \
		{                                                             \
			(dy2) = -(dy2);                                           \
			(stepy) = -1;                                             \
		}                                                             \
		else                                                          \
		{                                                             \
			(stepy) = 1;                                              \
		}                                                             \
                                                                      \
        if ((dx) < 0)                                                 \
		{                                                             \
			(dx2) = -(dx2);                                           \
			(stepx) = -1;                                             \
		}                                                             \
		else                                                          \
		{                                                             \
			(stepx) = 1;                                              \
		}                                                             \
                                                                      \
        if ((dx2) > (dy2))                                            \
			(fraction) = (dy2) - (dx) * (stepx);                      \
		else                                                          \
			(fraction) = (dx2) - (dy) * (stepy);                      \
    }

/**
 * Bresenham line stepping macro.
 * x, y are input-output and will be always be changed
 * fraction is also input-output, but should be initialized with
 * BRESENHAM_INIT.
 * stepx, stepy, dx2 and dy2 are input only and should also
 * be initialized by BRESENHAM_INIT */
#define BRESENHAM_STEP(x, y, fraction, stepx, stepy, dx2, dy2)        \
    if ((dx2) > (dy2))                                                \
	{                                                                 \
        if ((fraction) >= 0)                                          \
		{                                                             \
            (y) += (stepy);                                           \
            (fraction) -= (dx2);                                      \
        }                                                             \
                                                                      \
        (x) += (stepx);                                               \
        (fraction) += (dy2);                                          \
    }                                                                 \
	else                                                              \
	{                                                                 \
        if ((fraction) >= 0)                                          \
		{                                                             \
            (x) += (stepx);                                           \
            (fraction) -= (dy2);                                      \
        }                                                             \
                                                                      \
        (y) += (stepy);                                               \
        (fraction) += (dx2);                                          \
    }
/*@}*/

#ifdef HAVE_SRANDOM
#define RANDOM() random()
#define SRANDOM(xyz) srandom(xyz)
#else
#  ifdef HAVE_SRAND48
#  define RANDOM() lrand48()
#  define SRANDOM(xyz) srand48(xyz)
#  else
#    ifdef HAVE_SRAND
#      define RANDOM() rand()
#      define SRANDOM(xyz) srand(xyz)
#    else
#      error "Could not find a usable random routine"
#    endif
#  endif
#endif

#define PLUGINS

/**
 * @defgroup dump_values Dump values
 * Dump values, used for various information dumping.
 *@{*/

/** Dump information about monsters. */
#define DUMP_VALUE_MONSTERS          1
/** Dump information about monsters' abilities. */
#define DUMP_VALUE_ABILITIES         2
/** Dump artifacts information. */
#define DUMP_VALUE_ARTIFACTS         3
/** Dump spells. */
#define DUMP_VALUE_SPELLS            4
/** Dump skills and experience categories. */
#define DUMP_VALUE_SKILLS            5
/** Dump races. */
#define DUMP_VALUE_RACES             6
/** Dump alchemical formulas. */
#define DUMP_VALUE_ALCHEMY           7
/** Dump information about gods. */
#define DUMP_VALUE_GODS              8
/** Dump alchemy costs. */
#define DUMP_VALUE_ALCHEMY_COSTS     9
/** Dump all archetypes. */
#define DUMP_VALUE_ARCHETYPES        10
/** Dump treasure list of a monster. */
#define DUMP_VALUE_MONSTER_TREASURE  11
/** Dump level colors table. */
#define DUMP_VALUE_LEVEL_COLORS      12
/*@}*/

/** Name of the quest container archetype. */
#define QUEST_CONTAINER_ARCHETYPE "quest_container"

/**
 * @defgroup quest_statuses Quest statuses
 * Quest statuses. Stored in object::magic.
 *@{*/

/** The quest has been started. */
#define QUEST_STATUS_STARTED 0
/** The quest has been completed. */
#define QUEST_STATUS_COMPLETED 1
/*@}*/

/**
 * @defgroup quest_types Quest types
 * All the possible quest types.
 *@{*/

/** The quest is a one drop type. */
#define QUEST_TYPE_ITEM 0
/** The quest requires you to kill X monsters. */
#define QUEST_TYPE_KILL 1
/** The quest requires you to get item X from monster Y. */
#define QUEST_TYPE_KILL_ITEM 2
/*@}*/

#endif
