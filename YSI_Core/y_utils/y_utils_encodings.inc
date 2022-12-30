/**
 * <library
 *   name="y_utils - encodings"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - encodings</library>
 * <param name="string">the string to hash.</param>
 * <returns>
 *   The bernstein hash of the input string
 * </returns>
 * <remarks>
 *   This is a 32bit hash system so is not very secure, however we're only using
 *   this as a string enumerator to uniquely identify strings easilly and allow
 *   for a binary search of strings based on the hash of their name.
 *   <em>crc32</em>, then <em>jenkins</em> were originally used however this is
 *   far faster, if a little collision prone, but we're checking the strings
 *   manually anyway.  This doesn't matter as it would be done regardless of
 *   hash method, so this doesn't need to be accounted for.  Speed is all that
 *   matters with at least least a bit of non collision (the number of strings
 *   we're dealing with, this should have none-to-few collisions).
 *   <p/>
 *   I modified it slightly from the original code pasted by aru, to code closer
 *   to <a href="http://www.burtleburtle.net/bob/hash/doobs.html">the code</a>
 *   and to work with PAWN (and shaved 0.2us off the time for one call :D).
 *   <p/>
 *   Uber reduced version (just for fun):
 *   <code>
 *   b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
 *   </code>
 *   <p/>
 *   Update: Contrary to what I said above this is also used to identify colour
 *   strings for the updated text system involving file based styling and this
 *   is not checked for collisions as it's unimportant.  But this doesn't affect
 *   the function at all, I just mentioned it here for "interest".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock BernsteinHash(const string:str[] /* 12 */)
{
	new h = 5381, i = 0, j = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while ((j = str{i++}))
			h = h * 33 ^ j;
	}
	else
	{
		while ((j = str[i++]))
			h = h * 33 ^ j;
	}
	#if cellbits == 64
		return h & 0xFFFFFFFF;
	#else
		return h;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - encodings</library>
 * <param name="string">the string to hash.</param>
 * <returns>
 *   The bernstein hash of the input string
 * </returns>
 * <remarks>
 *   This is a 32bit hash system so is not very secure, however we're only using
 *   this as a string enumerator to uniquely identify strings easilly and allow
 *   for a binary search of strings based on the hash of their name.
 *   <em>crc32</em>, then <em>jenkins</em> were originally used however this is
 *   far faster, if a little collision prone, but we're checking the strings
 *   manually anyway.  This doesn't matter as it would be done regardless of
 *   hash method, so this doesn't need to be accounted for.  Speed is all that
 *   matters with at least least a bit of non collision (the number of strings
 *   we're dealing with, this should have none-to-few collisions).
 *   <p/>
 *   I modified it slightly from the original code pasted by aru, to code closer
 *   to <a href="http://www.burtleburtle.net/bob/hash/doobs.html">the code</a>
 *   and to work with PAWN (and shaved 0.2us off the time for one call :D).
 *   <p/>
 *   Uber reduced version (just for fun):
 *   <code>
 *   b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
 *   </code>
 *   <p/>
 *   Update: Contrary to what I said above this is also used to identify colour
 *   strings for the updated text system involving file based styling and this
 *   is not checked for collisions as it's unimportant.  But this doesn't affect
 *   the function at all, I just mentioned it here for "interest".
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `BernsteinHash` (i.e. use proper capitalisation).
stock bernstein(const string:str[] /* 12 */)
{
	new h = 5381, i = 0, j = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while ((j = str{i++}))
			h = h * 33 ^ j;
	}
	else
	{
		while ((j = str[i++]))
			h = h * 33 ^ j;
	}
	#if cellbits == 64
		return h & 0xFFFFFFFF;
	#else
		return h;
	#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - encodings</library>
 * <param name="str">the string to hash.</param>
 * <returns>
 *   the Jenkins hash of the input string
 * </returns>
 * <remarks>
 *   This is a 32bit hash system so is not very secure, however we're only using
 *   this as a string enumerator to uniquely identify strings easilly and allow
 *   for a binary search of strings based on the hash of their name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock JenkinsHash(const string:str[] /* 12 */)
{
	if (YSI_IsLocalVarPackedString__(str))
	{
		new h = 0, i = 0, j = 0;
		while ((j = str{i++}))
			h += j, h += h << 10, h ^= h >> 6;
		return
			h += h << 3,
			h ^= h >> 1,
			h + (h << 15);
	}
	else
	{
		new h = 0, i = 0, j = 0;
		while ((j = str[i++]))
			h += j, h += h << 10, h ^= h >> 6;
		return
			h += h << 3,
			h ^= h >> 1,
			h + (h << 15);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - encodings</library>
 * <summary>
 *   Base64Encode
 * </summary>
 * <remarks>
 *   Encodes data using proper base64.  This code is complicated by the fact
 *   that PAWN packed strings are backwards by cells in memory, so we need to do
 *   the writes in what seems like a strange order.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Base64Encode(string:dest[], const src[], num = sizeof (src), len = sizeof (dest), offset = 0)
{
	static
		// This is what the encoding should look like.  We mangle it to make the
		// representation in memory look like a C string, not a PAWN packed
		// string.
		//sEncoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		sEncoding[65 char] = __COMPILER_PACK"DCBAHGFELKJIPONMTSRQXWVUbaZYfedcjihgnmlkrqpovutszyxw32107654/+98",
		//tmp,
		ret = 0;
	num = num << __cell_shift;
	if (len <= ceildiv(num, 3))
	{
		// How many complete chunks can we fit in?
		num = (len - 1) * 3;
	}
	len = num % 3;
	num /= 3;
	// Set up the array for preincrement.
	const minus3 = -3;
	#emit LOAD.S.pri   src
	#emit ADD.C        minus3
	#emit LOAD.S.alt   offset
	#emit ADD
	#emit PUSH.pri
	#emit LOAD.S.pri   dest
	#emit STOR.pri     ret
	// Loop for the whole chunks.
	while (num--)
	{
		// Using a post-increment just refuses to work, and I have no idea why.
		#emit POP.pri
		#emit ADD.C        3
		#emit PUSH.pri
		#emit LOAD.I       // `LODB.I 3` doesn't work.
		#emit PUSH.pri
		
		#emit SHL.C.pri    10 // (pri >> 16) & 0x3F
		#emit SHR.C.pri    26 // 
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit LOAD.S.pri   __local1_offset
		#emit MOVE.alt
		#emit SHL.C.pri     8 // (pri >> 22) & 0x03
		#emit SHR.C.pri    30 // Would be just `SHR.C.pri` with `LODB.I 3`...
		#emit XCHG
		#emit SHL.C.pri    20 // (alt >> 6) & 0x3C
		#emit SHR.C.pri    28 //
		#emit SHL.C.pri    2  //
		#emit OR
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit LOAD.S.pri   __local1_offset
		#emit MOVE.alt
		#emit SHL.C.pri    30 // (pri << 4) & 0x30
		#emit SHR.C.pri    26 //
		#emit XCHG
		#emit SHL.C.pri    16 // (alt >> 12) & 0x0F
		#emit SHR.C.pri    28 //
		#emit OR
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit POP.pri
		#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
		#emit SHR.C.pri    26 //
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
	}
	{}
	switch (len)
	{
		case 0:
		{
			#emit POP.pri
			#emit LOAD.S.alt   dest
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
		case 1:
		{
			#emit LOAD.S.alt   dest
			#emit CONST.pri    '='
			#emit STRB.I       1
			#emit INC.alt
			#emit STRB.I       1
			#emit INC.alt
			#emit POP.pri
			#emit ADD.C        3
			#emit LODB.I       1
			#emit PUSH.pri
			
			#emit SHL.C.pri    30 // (pri << 4) & 0x30
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			
			#emit POP.pri
			#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
		case 2:
		{
			// Write out remaining `=` signs.
			#emit LOAD.S.alt   dest
			#emit CONST.pri    '='
			#emit STRB.I       1
			#emit INC.alt
			#emit POP.pri
			#emit ADD.C        3
			#emit LODB.I       2
			#emit PUSH.pri
			
			#emit SHL.C.pri    20 // (alt >> 6) & 0x3C
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			
			#emit LOAD.S.pri   __local0_offset
			#emit MOVE.alt
			#emit SHL.C.pri    30 // (pri << 4) & 0x30
			#emit SHR.C.pri    26 //
			#emit XCHG
			#emit SHL.C.pri    16 // (alt >> 12) & 0x0F
			#emit SHR.C.pri    28 //
			#emit OR
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit LOAD.S.alt   dest
			#emit INC.alt
			#emit INC.alt
			#emit STRB.I       1
			#emit INC.alt
			
			#emit POP.pri
			#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
	}
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - encodings</library>
 * <summary>
 *   Base64Decode
 * </summary>
 * <remarks>
 *   Decodes data using proper base64.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Base64Decode(dest[], const string:src[], len = sizeof (dest), offset = 0)
{
	static
		// Again, the encoding looks slightly mangled as we want the bytes in
		// order, while cells are little-endian.
		sDecoding[128 char] = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x00000000, 0x3E000000, 0x3F000000, 0x37363534, 0x3B3A3938, 0x00003D3C, 0x00000000,
			0x02010000, 0x06050403, 0x0A090807, 0x0E0D0C0B, 0x1211100F, 0x16151413, 0x00191817, 0x00000000,
			0x1C1B1A00, 0x201F1E1D, 0x24232221, 0x28272625, 0x2C2B2A29, 0x302F2E2D, 0x00333231, 0x00000000
		},
		blocks = 0,
		num = 0;
	// Work out the final length.  Subtract some for incomplete bytes and
	// insufficient destination data.
	num = strlen(src),
	len = len << __cell_shift,
	blocks = num >>> __cell_shift;
	if (src{num - 1}  == '=')
	{
		--blocks;
		if (src{num - 2}  == '=')
			num = 1;
		else
			num = 2;
	}
	else
		num = 0;
	blocks = min(blocks, len / 3);
	num = min(num, len - blocks * 3);
	len = blocks * 3 + num;
	// Do complete blocks of 4 (one cell).
	{}
	// x - 1 - 3
	#emit LOAD.S.pri   dest
	#emit ADD.C        __m1_cells
	#emit LOAD.S.alt   offset
	#emit ADD
	#emit STOR.S.pri   dest
	#emit LOAD.S.pri   src
	#emit ADD.C        __m1_cells
	#emit STOR.S.pri   src
	while (blocks--)
	{
		#emit LOAD.S.pri   src
		#emit ADD.C        4
		#emit STOR.S.pri   src
		#emit LOAD.I
		#emit MOVE.alt
		
		// The data has now been loaded.  The data MSB comes from the string's
		// LSB (which for PAWN is the last character).
		#emit SHL.C.pri    24 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit SHL.C.pri    24 // (pri << 24)
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHL.C.pri    16 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit PUSH.pri
		#emit SHL.C.pri    30 // (pri << 30)
		#emit SWAP.pri
		#emit SHR.C.pri     2 // (pri >> 2 << 16)
		#emit SHL.C.pri    16
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHL.C.pri     8 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit PUSH.pri
		#emit SHR.C.pri     4 // (pri >> 4 << 8)
		#emit SHL.C.pri     8
		#emit SWAP.pri
		#emit SHL.C.pri    28 // (pri << 28 >> 8)
		#emit SHR.C.pri     8
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHR.C.pri    24 // (pri & 0xFF)
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit SHL.C.pri    10 // (pri << 10)
		#emit MOVE.alt
		
		// Get the byte before the one we want to write loaded as the LSB then
		// shift the other bytes in to this one.
		#emit LOAD.S.pri   dest
		#emit ADD.C        3
		#emit STOR.S.pri   dest
		#emit LODB.I       1
		
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		
		#emit SREF.S.pri   dest
	}
	switch (num)
	{
		case 1:
		{
			// Need to store just one byte (the LSB).
			#emit LOAD.S.pri   src
			#emit ADD.C        4
			#emit LOAD.I
			#emit MOVE.alt
			
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHL.C.pri     2 // (pri << 2)
			#emit XCHG
			#emit SHL.C.pri     8
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHR.C.pri     4 // (pri >> 4)
			#emit OR
			#emit MOVE.alt
			
			#emit LOAD.S.pri   dest
			#emit ADD.C        4
			#emit XCHG
			#emit STRB.I       1
		}
		case 2:
		{
			// Need to store two bytes (the LSBs).
			#emit LOAD.S.pri   src
			#emit ADD.C        4
			#emit LOAD.I
			#emit MOVE.alt
			#emit PUSH.pri
			
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHL.C.pri     2 // (pri << 2)
			#emit XCHG
			#emit SHL.C.pri     8
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit PUSH.pri
			#emit SHR.C.pri     4 // (pri >> 4)
			#emit OR
			#emit MOVE.alt
			
			// This has extra bits left in, but they are cut off by `STRB.I 2`.
			#emit POP.pri
			#emit SHL.C.pri    12 // (pri << 12)
			#emit OR
			#emit POP.alt
			#emit XCHG
			#emit SHL.C.pri    16
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHR.C.pri     2 // (pri >> 2 << 8)
			#emit SHL.C.pri     8
			#emit OR
			#emit MOVE.alt
			
			#emit LOAD.S.pri   dest
			#emit ADD.C        4
			#emit XCHG
			#emit STRB.I       2
		}
	}
	return len;
}

