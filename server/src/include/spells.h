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

#ifndef SPELLS_H
#define SPELLS_H

extern int turn_bonus[]; /* chance array for stat values */
extern int fear_bonus[];
extern int cleric_chance[];

#define SPELL_USE_INTERN 0x00 /* special spells - don't list them as avaible spell */
#define SPELL_USE_CAST   0x01 /* spell can be casted normal */
#define SPELL_USE_BALM   0x02
#define SPELL_USE_DUST   0x04
#define SPELL_USE_SCROLL 0x08
#define SPELL_USE_HORN   0x10
#define SPELL_USE_WAND   0x20
#define SPELL_USE_ROD    0x40
#define SPELL_USE_POTION 0x80
#define SPELL_USE_BOOK   0x100 /* well, normally we don't use spellbooks as random stuff
* except some special "quest" spells for quest monster
*/

#define SPELL_TYPE_NATURAL 0 /* special case: this is use like a spell but natural ability - effect is non magical */
#define SPELL_TYPE_WIZARD  1 /* base mage spell: using mana */
#define SPELL_TYPE_PRIEST  2 /* base cleric spell: using grace */
#define SPELL_TYPE_NROF	   2 /* This should be highest number of SPELL_TYPES */

#define SPELL_DESC_TOWN			0x01	/* Spell is safe to cast in as TOWN marked maps */
#define SPELL_DESC_DIRECTION	0x02	/* Spell is fired in a direction (bullets, bolts, ... ) */
/* stack the next flags to define whats possible with this spell */
#define SPELL_DESC_SELF			0x04	/* Spell can be cast on self (with target system) */
#define SPELL_DESC_FRIENDLY		0x08	/* Spell can be cast on friendly (with target system) */
#define SPELL_DESC_ENEMY		0x10	/* Spell can be cast on enemy (with target system) */
#define SPELL_DESC_GROUP		0x20	/* Spell can be cast on group members  */
/* end stack flags */
#define SPELL_DESC_SUMMON		0x40	/* Spell summons something */
#define SPELL_DESC_PARALYZED	0x80	/* Spell can be casted even when paralyzed (TODO) */

#define SPELL_DESC_WIS			0x100   /* special flag - if set, this is a "prayer" using WIS
* when not set it use INT as is a spell
*/
#define SPELL_ACTIVE 1
#define SPELL_DEACTIVE 0

typedef struct spell_struct
{
	/* name of this spell */
	char name[BIG_NAME];

		/* Type of spell: wizard, priest, ... */
		int type;

		/* Level required to cast this spell */
		int level;

		/* Spellpoint-cost to cast it */
		int sp;

		/* How many ticks it takes to cast the spell */
		float time;

		/* thats from 1 to <scrolls> nrof we will generate for potions/scrolls... */
		int scrolls;

		/* If it can be used in wands, max # of charges */
		int charges;

		/* if target spell, this is max range to target */
		int range;

		/* used when we have a item of tihs spell kind.
		 * a magic potion has vaule x. We do: (x * value_mul)*level */
		float value_mul;

		/* bdam: base damage or hp of spell or summoned monster
		 * bdur: base duration of spell or base range
		 * ldam: levels you need over the min for the spell to gain one dam
		 * ldur: levels you need over the min for the spell to gain one dur
		 * spl: number of levels beyond minimum for spell point cost to
		 *		increase by amount equal to base cost.  i.e. if base cost
		 * 		is 10 at level 2 and spl is 5, cost will increase by 2 per
		 * 		level.  if base cost is 5 and spl is 10, cost increases by
		 *		1 every 2 levels. */

		/*  base damage  */
		int bdam;

		/*  base duration  */
		int bdur;

		/*  damage adjustment for level  */
		int ldam;

		/*  duration adjustment for level  */
		int ldur;

		int spl;

		/* number of sound id for this sound */
		int sound;

		/* Define to what items this spell can be bound (potion, rod,,, ) */
		int spell_use;

		/* Used for SPELL_DESC_xx flags */
		uint32 flags;

		/* Path this spell belongs to */
		uint32 path;

		/* Pointer to archetype used by spell */
		char *archname;

		/* if 0 then spell is disabled and can't be cast or used */
		int is_active;
	} spell;

extern spell spells[NROFREALSPELLS];

/* When adding new spells, don't insert into the middle of the list -
 * add to the end of the list.  Some archetypes and treasures require
 * the spell numbers to be as they are. */

#define SP_NO_SPELL -1

enum spellnrs
{
	/* Here starts the Atrinik list */
	SP_FIRESTORM,
	SP_ICESTORM,
	SP_MINOR_HEAL,
	SP_CURE_POISON,
	SP_CURE_DISEASE,
	SP_STRENGTH,
	SP_IDENTIFY,
	SP_DETECT_MAGIC,
	SP_DETECT_CURSE,
	SP_REMOVE_CURSE,
	SP_REMOVE_DAMNATION,
	SP_CAUSE_LIGHT,
	SP_CONFUSION,
	SP_BULLET,
	SP_GOLEM,
	SP_REMOVE_DEPLETION,
	SP_PROBE,
	SP_TOWN_PORTAL,
	SP_CREATE_FOOD,
	SP_WOR,

	/* All down here are from Crossfire */
	SP_S_FIREBALL,
	SP_M_FIREBALL,
	SP_L_FIREBALL,
	SP_S_LIGHTNING,
	SP_L_LIGHTNING,
	SP_M_MISSILE,
	SP_BOMB,
	SP_FIRE_ELEM,
	SP_EARTH_ELEM,
	SP_WATER_ELEM,
	SP_AIR_ELEM,
	SP_D_DOOR,
	SP_EARTH_WALL,
	SP_PARALYZE,
	SP_MAGIC_MAPPING,
	SP_TURN_UNDEAD,
	SP_FEAR,
	SP_POISON_CLOUD,
	SP_WOW,
	SP_DESTRUCTION,
	SP_PERCEIVE,
	SP_CREATE_MISSILE,
	SP_INVIS,
	SP_INVIS_UNDEAD,
	SP_LARGE_BULLET,
	SP_IMPROVED_INVIS,
	SP_HOLY_WORD,
	SP_MED_HEAL,
	SP_MAJOR_HEAL,
	SP_HEAL,
	SP_EARTH_DUST,
	SP_ARMOUR,
	SP_DEXTERITY,
	SP_CONSTITUTION,
	SP_CHARISMA,
	SP_FIRE_WALL,
	SP_FROST_WALL,
	SP_PROT_COLD,
	SP_PROT_ELEC,
	SP_PROT_FIRE,
	SP_PROT_POISON,
	SP_PROT_SLOW,
	SP_PROT_PARALYZE,
	SP_PROT_DRAIN,
	SP_PROT_MAGIC,
	SP_PROT_ATTACK,
	SP_LEVITATE,
	SP_SMALL_SPEEDBALL,
	SP_LARGE_SPEEDBALL,
	SP_HELLFIRE,
	SP_FIREBREATH,
	SP_LARGE_ICESTORM,
	SP_CHARGING,
	SP_POLYMORPH,
	SP_CANCELLATION,
	SP_MASS_CONFUSION,
	SP_PET,
	SP_SLOW,
	SP_REGENERATE_SPELLPOINTS,
	SP_PROT_CONFUSE,
	SP_PROT_CANCEL,
	SP_PROT_DEPLETE,
	SP_ALCHEMY,
	SP_DETECT_MONSTER,
	SP_DETECT_EVIL,
	SP_HEROISM,
	SP_AGGRAVATION,
	SP_FIREBOLT,
	SP_FROSTBOLT,
	SP_SHOCKWAVE,
	SP_COLOR_SPRAY,
	SP_HASTE,
	SP_FACE_OF_DEATH,
	SP_BALL_LIGHTNING,
	SP_METEOR_SWARM,
	SP_METEOR,
	SP_MYSTIC_FIST,
	SP_RAISE_DEAD,
	SP_RESURRECTION,
	SP_REINCARNATION,
	SP_IMMUNE_COLD,
	SP_IMMUNE_ELEC,
	SP_IMMUNE_FIRE,
	SP_IMMUNE_POISON,
	SP_IMMUNE_SLOW,
	SP_IMMUNE_PARALYZE,
	SP_IMMUNE_DRAIN,
	SP_IMMUNE_MAGIC,
	SP_IMMUNE_ATTACK,
	SP_INVULNERABILITY,
	SP_PROTECTION,
	SP_RUNE_FIRE,
	SP_RUNE_FROST,
	SP_RUNE_SHOCK,
	SP_RUNE_BLAST,
	SP_RUNE_DEATH,
	SP_RUNE_MARK,
	SP_BUILD_DIRECTOR,
	SP_CHAOS_POOL,
	SP_BUILD_BWALL,
	SP_BUILD_LWALL,
	SP_BUILD_FWALL,
	SP_RUNE_MAGIC,
	SP_RUNE_DRAINSP,
	SP_RUNE_ANTIMAGIC,
	SP_RUNE_TRANSFER,
	SP_TRANSFER,
	SP_MAGIC_DRAIN,
	SP_COUNTER_SPELL,
	SP_DISPEL_RUNE,
	SP_CURE_CONFUSION,
	SP_RESTORATION,
	SP_SUMMON_EVIL_MONST,
	SP_COUNTERWALL,
	SP_CAUSE_MEDIUM,
	SP_CAUSE_HEAVY,
	SP_CHARM,
	SP_BANISHMENT,
	SP_SHOW_INVIS,
	SP_XRAY,
	SP_PACIFY,
	SP_SUMMON_FOG,
	SP_STEAMBOLT,
	SP_COMMAND_UNDEAD,
	SP_HOLY_ORB,
	SP_SUMMON_AVATAR,
	SP_HOLY_POSSESSION,
	SP_BLESS,
	SP_CURSE,
	SP_REGENERATION,
	SP_CONSECRATE,
	SP_SUMMON_CULT,
	SP_CAUSE_CRITICAL,
	SP_HOLY_WRATH,
	SP_RETRIBUTION,
	SP_FINGER_DEATH,
	SP_INSECT_PLAGUE,
	SP_HOLY_SERVANT,
	SP_WALL_OF_THORNS,
	SP_STAFF_TO_SNAKE,
	SP_LIGHT,
	SP_DARKNESS,
	SP_NIGHTFALL,
	SP_DAYLIGHT,
	SP_SUNSPEAR,
	SP_FAERY_FIRE,
	SP_CURE_BLINDNESS,
	SP_DARK_VISION,
	SP_BULLET_SWARM,
	SP_BULLET_STORM,
	SP_CAUSE_MANY,
	SP_S_SNOWSTORM,
	SP_M_SNOWSTORM,
	SP_L_SNOWSTORM,
	SP_CAUSE_EBOLA,
	SP_CAUSE_FLU,
	SP_CAUSE_PLAGUE,
	SP_CAUSE_LEPROSY,
	SP_CAUSE_SMALLPOX,
	SP_CAUSE_PNEUMONIC_PLAGUE,
	SP_CAUSE_ANTHRAX,
	SP_CAUSE_TYPHOID,
	SP_MANA_BLAST,
	SP_S_MANABALL,
	SP_M_MANABALL,
	SP_L_MANABALL,
	SP_MANA_BOLT,
	SP_DANCING_SWORD,
	SP_ANIMATE_WEAPON,
	SP_CAUSE_COLD,
	SP_DIVINE_SHOCK,
	SP_WINDSTORM,
	SP_SANCTUARY,
	SP_PEACE,
	SP_SPIDERWEB,
	SP_CONFLICT,
	SP_RAGE,
	SP_FORKED_LIGHTNING,
	SP_POISON_FOG,
	SP_FLAME_AURA,
	SP_VITRIOL,
	SP_VITRIOL_SPLASH,
	SP_IRONWOOD_SKIN,
	SP_WRATHFUL_EYE,
	SP_MISSILE_SWARM,
	SP_CAUSE_RABIES
};

#define IS_SUMMON_SPELL(spell) (spells[type].flags&SPELL_DESC_SUMMON)

#define PATH_SP_MULT(op,spell) (((op->path_attuned & s->path) ? 0.8 : 1) * \
				((op->path_repelled & s->path) ? 1.25 : 1))
#define PATH_TIME_MULT(op,spell) (((op->path_attuned & s->path) ? 0.8 : 1) * \
				((op->path_repelled & s->path) ? 1.25 : 1))

extern char *spellpathnames[NRSPELLPATHS];
extern archetype *spellarch[NROFREALSPELLS];

/* i added spellNPC here as special... its used for example to force scripted npc
 * action which is normally ingame not legal - like shopkeepers who casts self only
 * spells like identify over players. */
typedef enum SpellTypeFrom
{
	spellNormal,
	spellWand,
	spellRod,
	spellHorn,
	spellScroll,
	spellPotion,
	spellNPC
} SpellTypeFrom;


#endif
