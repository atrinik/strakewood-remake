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
* the Free Software Foundation; either version 3 of the License, or     *
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

/* zutil.c -- target dependent utility functions for the compression library
 * Copyright (C) 1995-2003 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h */

#include "zutil.h"

#ifndef NO_DUMMY_DECL
/* for buggy compilers */
struct internal_state {int dummy;};
#endif

#ifndef STDC
extern void exit OF((int));
#endif

const char * const z_errmsg[10] = {
	/* Z_NEED_DICT       2  */
	"need dictionary",
	/* Z_STREAM_END      1  */
	"stream end",
	/* Z_OK              0  */
	"",
	/* Z_ERRNO         (-1) */
	"file error",
	/* Z_STREAM_ERROR  (-2) */
	"stream error",
	/* Z_DATA_ERROR    (-3) */
	"data error",
	/* Z_MEM_ERROR     (-4) */
	"insufficient memory",
	/* Z_BUF_ERROR     (-5) */
	"buffer error",
	/* Z_VERSION_ERROR (-6) */
	"incompatible version",
	""
};

const char *ZEXPORT zlibVersion()
{
    return ZLIB_VERSION;
}

uLong ZEXPORT zlibCompileFlags()
{
    uLong flags;

    flags = 0;
    switch (sizeof(uInt))
	{
		case 2:
			break;

		case 4:
			flags += 1;
			break;

		case 8:
			flags += 2;
			break;

		default:
			flags += 3;
    }

    switch (sizeof(uLong))
	{
		case 2:
			break;

		case 4:
			flags += 1 << 2;
			break;

		case 8:
			flags += 2 << 2;
			break;

		default:
			flags += 3 << 2;
    }

    switch (sizeof(voidpf))
	{
		case 2:
			break;

		case 4:
			flags += 1 << 4;
			break;

		case 8:
			flags += 2 << 4;
			break;

		default:
		flags += 3 << 4;
    }

    switch (sizeof(z_off_t))
	{
		case 2:
			break;

		case 4:
			flags += 1 << 6;
			break;

		case 8:
			flags += 2 << 6;
			break;

		default:
			flags += 3 << 6;
    }

#ifdef DEBUG_ZLIB
    flags += 1 << 8;
#endif

#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif

#ifdef ZLIB_WINAPI
    flags += 1 << 10;
#endif

#ifdef BUILDFIXED
    flags += 1 << 12;
#endif

#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif

#ifdef NO_GZCOMPRESS
    flags += 1 << 16;
#endif

#ifdef NO_GZIP
    flags += 1 << 17;
#endif

#ifdef PKZIP_BUG_WORKAROUND
    flags += 1 << 20;
#endif

#ifdef FASTEST
    flags += 1 << 21;
#endif

#ifdef STDC
#  ifdef NO_vsnprintf
        flags += 1 << 25;
#    ifdef HAS_vsprintf_void
        flags += 1 << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
        flags += 1 << 26;
#    endif
#  endif
#else
        flags += 1 << 24;
#  ifdef NO_snprintf
        flags += 1 << 25;
#    ifdef HAS_sprintf_void
        flags += 1 << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
        flags += 1 << 26;
#    endif
#  endif
#endif

    return flags;
}

#ifdef DEBUG_ZLIB

#  ifndef verbose
#    define verbose 0
#  endif
int z_verbose = verbose;

void z_error(char *m)
{
    fprintf(stderr, "%s\n", m);
    exit(1);
}
#endif

/* exported to allow conversion of error code to string for compress() and
 * uncompress() */
const char * ZEXPORT zError(int err)
{
    return ERR_MSG(err);
}

#if defined(_WIN32_WCE)
    /* does not exist on WCE */
    int errno = 0;
#endif

#ifndef HAVE_MEMCPY

void zmemcpy(Bytef *dest, const Bytef *source, uInt len)
{
    if (len == 0)
		return;

    do
	{
		/* ??? to be unrolled */
        *dest++ = *source++;
    } while (--len != 0);
}

int zmemcmp(const Bytef *s1, const Bytef *s2, uInt len)
{
    uInt j;

    for (j = 0; j < len; j++)
	{
        if (s1[j] != s2[j])
			return 2 * (s1[j] > s2[j]) - 1;
    }
    return 0;
}

void zmemzero(Bytef *dest, uInt len)
{
    if (len == 0)
		return;

    do
	{
		/* ??? to be unrolled */
        *dest++ = 0;
    } while (--len != 0);
}
#endif


#ifdef SYS16BIT

#ifdef __TURBOC__
/* Turbo C in 16-bit mode */

#  define MY_ZCALLOC

/* Turbo C malloc() does not allow dynamic allocation of 64K bytes
 * and farmalloc(64K) returns a pointer with an offset of 8, so we
 * must fix the pointer. Warning: the pointer must be put back to its
 * original form in order to free it, use zcfree(). */

#define MAX_PTR 10
/* 10*64K = 640K */

local int next_ptr = 0;

typedef struct ptr_table_s {
    voidpf org_ptr;
    voidpf new_ptr;
} ptr_table;

local ptr_table table[MAX_PTR];
/* This table is used to remember the original form of pointers
 * to large buffers (64K). Such pointers are normalized with a zero offset.
 * Since MSDOS is not a preemptive multitasking OS, this table is not
 * protected from concurrent access. This hack doesn't work anyway on
 * a protected system like OS/2. Use Microsoft C instead. */
voidpf zcalloc (voidpf opaque, unsigned items, unsigned size)
{
	/* just to make some compilers happy */
    voidpf buf = opaque;
    ulg bsize = (ulg)items * size;

    /* If we allocate less than 65520 bytes, we assume that farmalloc
     * will return a usable pointer which doesn't have to be normalized. */
    if (bsize < 65520L)
	{
        buf = farmalloc(bsize);
        if (*(ush*)&buf != 0)
			return buf;
    }
	else
	{
        buf = farmalloc(bsize + 16L);
    }

    if (buf == NULL || next_ptr >= MAX_PTR)
		return NULL;

    table[next_ptr].org_ptr = buf;

    /* Normalize the pointer to seg:0 */
    *((ush*)&buf + 1) += ((ush)((uch*)buf - 0) + 15) >> 4;
    *(ush*)&buf = 0;
    table[next_ptr++].new_ptr = buf;
    return buf;
}

void zcfree(voidpf opaque, voidpf ptr)
{
    int n;
	/* object < 64K */
    if (*(ush*)&ptr != 0)
	{
        farfree(ptr);
        return;
    }

    /* Find the original pointer */
    for (n = 0; n < next_ptr; n++)
	{
        if (ptr != table[n].new_ptr)
			continue;

        farfree(table[n].org_ptr);
        while (++n < next_ptr)
		{
            table[n - 1] = table[n];
        }
        next_ptr--;
        return;
    }

	/* just to make some compilers happy */
    ptr = opaque;
    Assert(0, "zcfree: ptr not found");
}

#endif


#ifdef M_I86
/* Microsoft C in 16-bit mode */

#  define MY_ZCALLOC

#if (!defined(_MSC_VER) || (_MSC_VER <= 600))
#  define _halloc  halloc
#  define _hfree   hfree
#endif

voidpf zcalloc(voidpf opaque, unsigned items, unsigned size)
{
	/* to make compiler happy */
    if (opaque)
		opaque = 0;

    return _halloc((long)items, size);
}

void zcfree(voidpf opaque, voidpf ptr)
{
	/* to make compiler happy */
    if (opaque)
		opaque = 0;

    _hfree(ptr);
}

#endif

#endif

/* Any system without a special alloc function */
#ifndef MY_ZCALLOC

#ifndef STDC
extern voidp malloc OF((uInt size));
extern voidp calloc OF((uInt items, uInt size));
extern void  free OF((voidpf ptr));
#endif

voidpf zcalloc(voidpf opaque, unsigned items, unsigned size)
{
	/* make compiler happy */
    if (opaque)
		items += size - size;

    return sizeof(uInt) > 2 ? (voidpf)malloc(items * size) : (voidpf)calloc(items, size);
}

void zcfree(voidpf opaque, voidpf ptr)
{
    free(ptr);

	/* make compiler happy */
    if (opaque)
		return;
}

#endif
