/*
 * bitops.c --- Bitmap frobbing code.  See bitops.h for the inlined
 * 	routines.
 * 
 * Copyright (C) 1993, 1994 Theodore Ts'o.  This file may be
 * redistributed under the terms of the GNU Public License.
 * 
 * Taken from <asm/bitops.h>, Copyright 1992, Linus Torvalds.
 */

#include <stdio.h>
#include <sys/types.h>

#include <linux/ext2_fs.h>

#include "ext2fs.h"

#ifndef _EXT2_HAVE_ASM_BITOPS_

/*
 * For the benefit of those who are trying to port Linux to another
 * architecture, here are some C-language equivalents.  You should
 * recode these in the native assmebly language, if at all possible.
 *
 * C language equivalents written by Theodore Ts'o, 9/26/92.
 * Modified by Pete A. Zaitcev 7/14/95 to be portable to big endian
 * systems, as well as non-32 bit systems.
 */

int set_bit(int nr,void * addr)
{
	int		mask, retval;
	unsigned char	*ADDR = (unsigned char *) addr;

	ADDR += nr >> 3;
	mask = 1 << (nr & 0x07);
	retval = (mask & *ADDR) != 0;
	*ADDR |= mask;
	return retval;
}

int clear_bit(int nr, void * addr)
{
	int		mask, retval;
	unsigned char	*ADDR = (unsigned char *) addr;

	ADDR += nr >> 3;
	mask = 1 << (nr & 0x07);
	retval = (mask & *ADDR) != 0;
	*ADDR &= ~mask;
	return retval;
}

int test_bit(int nr, const void * addr)
{
	int			mask;
	const unsigned char	*ADDR = (const unsigned char *) addr;

	ADDR += nr >> 3;
	mask = 1 << (nr & 0x07);
	return ((mask & *ADDR) != 0);
}

#endif	/* !_EXT2_HAVE_ASM_BITOPS_ */

void ext2fs_warn_bitmap(errcode_t errcode, unsigned long arg,
			const char *description)
{
	if (description)
		com_err(0, errcode, "#%u for %s", arg, description);
	else
		com_err(0, errcode, "#%u", arg);
}

