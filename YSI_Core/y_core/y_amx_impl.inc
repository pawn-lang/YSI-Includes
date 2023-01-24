#if defined _INC_y_amx
	#endinput
#endif
#define _INC_y_amx

/**
 * <library
 *   name="y_amx"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Allows a script access to information about itself, such as function names."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This can be used for a range of things, including automatic callback
 *     hooking and testing.
 *   </remarks>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
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

// I debated porting this over to use ZeeX's advanced AMX system, but there's no
// point - this is stable and works well.  Doing so would mean testing that all
// the code that uses this file still operates corectly given how differently
// the two systems do things.  I fully admit that his is FAR more general but
// there are legacy libraries to consider.
//
// Update: I'm using both in parallel because they do different things well.
// That has a more complete API for most things, but this is way better for
// looping over functions.

#define AMX_FastString(%1,%2,%3,%4) \
	(((%1) << 0) | ((%2) << 8) | ((%3) << 16) | ((%4) << 24))

#define AMX_MEMORY_TRACE_0 0xAABBCCDD
#define AMX_MEMORY_TRACE_1 0xDDCCBBAA
#define AMX_MEMORY_TRACE_2 0x12345678
#define AMX_MEMORY_TRACE_3 0x87654321

stock
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_SIZE = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_MAGIC = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_FILE_VERSION = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_AMX_VERSION = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_FLAGS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_DEFSIZE = 0,
	/**
	 * <library>y_amx</library>
	 */
	// These are not as they appear in the AMX - they are relative to the dat
	// pointer so that they can be directly manipulated.
	AMX_HEADER_COD = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_DAT = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_HEA = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_STP = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_CIP = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_PUBLICS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_NATIVES = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_LIBRARIES = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_PUBVARS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_TAGS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_HEADER_NAMETABLE = 0,
	/**
	 * <library>y_amx</library>
	 */
	//E_AMX_HEADER_OVERLAYS,
	AMX_REAL_ADDRESS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_BASE_ADDRESS = 0,
	/**
	 * <library>y_amx</library>
	 */
	AMX_REAL_DATA = 0;

/// <p/>

/**
 * <library>y_amx</library>
 */
enum E_AMX_TABLE
{
	AMX_TABLE_PUBLICS,
	AMX_TABLE_NATIVES,
	AMX_TABLE_LIBRARIES,
	AMX_TABLE_PUBVARS,
	AMX_TABLE_TAGS
}
static stock E_AMX_TABLE:_@E_AMX_TABLE() { return E_AMX_TABLE; }

#if cellbits == 64
	#define __32(%0) ((%0)&0xFFFFFFFF)
#else
	#define __32(%0) (%0)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <summary>
 *   Swap two pointers in the header.  Pointers are always 32-bit, regardless of
 *   cell size, so this may require some bit manipulation.
 * </summary>
 * <remarks>
 *   Shamelessly ripped from amx_assembly (but I wrote the original, so...)
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock AMX_HeaderTableSwap(addr0, addr1)
{
	#if cellbits == 64
		new
			v0,
			v1,
			v3;
		// Swap the pointers.
		v0 = AMX_Read(addr0),
		v1 = AMX_Read(addr1),
		AMX_Write(addr1, v0),
		AMX_Write(addr0, v1),
		// Move on.
		addr0 += cellbytes,
		addr1 += cellbytes,
		// Swap the names.  These pointers are always 32-bit, at least in
		// the AMX versions we deal with.  Thus we mask the upper bits.
		v0 = AMX_Read(addr0),
		v1 = AMX_Read(addr1),
		AMX_Write(addr1, (v0 & 0x00000000FFFFFFFF) | (v1 & 0xFFFFFFFF00000000)),
		AMX_Write(addr0, (v1 & 0x00000000FFFFFFFF) | (v0 & 0xFFFFFFFF00000000));
	#else
		new
			v0,
			v1;
		// Swap the pointers.
		v0 = AMX_Read(addr0),
		v1 = AMX_Read(addr1),
		AMX_Write(addr1, v0),
		AMX_Write(addr0, v1),
		// Move on.
		addr0 += cellbytes,
		addr1 += cellbytes,
		// Swap the names.
		v0 = AMX_Read(addr0),
		v1 = AMX_Read(addr1),
		AMX_Write(addr1, v0),
		AMX_Write(addr0, v1);
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <summary>
 *   The partition operation for a quicksort.
 * </summary>
 * <remarks>
 *   Shamelessly ripped from amx_assembly (but I wrote the original, so...)
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock AMX_HeaderTablePartition(low, high, dat, defsize)
{
	new
		pivot = __32(AMX_Read(high + cellbytes)) - dat,
		j = low;
	for (low -= defsize; j != high; j += defsize)
	{
		if (AMX_CompareHeaderStrings(__32(AMX_Read(j + cellbytes)) - dat, pivot) < 0)
		{
			// Swap.
			low += defsize,
			AMX_HeaderTableSwap(low, j);
		}
	}
	low += defsize,
	AMX_HeaderTableSwap(low, high);
	return low;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <summary>
 *   Sort a list of names in the AMX header.
 * </summary>
 * <remarks>
 *   Shamelessly ripped from amx_assembly (but I wrote the original, so...)
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock AMX_HeaderTableQuickSort(low, high, dat, defsize)
{
	if (low < high)
	{
		new
			partition = AMX_HeaderTablePartition(low - dat, high - dat, dat, defsize) + dat;
		AMX_HeaderTableQuickSort(low, partition - defsize, dat, defsize);
		AMX_HeaderTableQuickSort(partition + defsize, high, dat, defsize);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <summary>
 *   Compares a string stored in the name table starting at "s1" (packed) with
 *   another string in the name table starting at "s2" (packed).
 * </summary>
 * <remarks>
 *   Shamelessly ripped from amx_assembly (but I wrote the original, so...)
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock AMX_CompareHeaderStrings(s1, s2)
{
	new c1 = 0, c2 = 0;
	new diff = 0;

	do
	{
		c1 = AMX_Read(s1) & 0xFF;
		++s1;
		c2 = AMX_Read(s2) & 0xFF;
		++s2;
		diff = c1 - c2;
		if (diff != 0)
		{
			break;
		}
	}
	while ((c1 & c2));

	return diff;
}

// This is based on the AMX version used in SA:MP - it DOES NOT match the code
// found in the PAWN documentation as that's for a later version.
public OnCodeInit()
{
	#if defined ResetStaticAmxHeader
		// Call this function to sort the header.
		ResetStaticAmxHeader();
	#endif
	new
		addr = 0,
		data = 0;
	#emit LCTRL                     __dat
	#emit STOR.S.pri                addr
	// Invert to get the prefix offset relative to the data.
	// Get all the script data.
	addr = -addr;
	// Now read in all the data.
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_SIZE = __32(data);
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_MAGIC        = data & 0xFFFF;
	AMX_HEADER_FILE_VERSION = data >>> 16 & 0xFF;
	AMX_HEADER_AMX_VERSION  = __32(data) >>> 24;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_FLAGS        = data & 0xFFFF;
	AMX_HEADER_DEFSIZE      = __32(data) >>> 16;
	assert(AMX_HEADER_DEFSIZE == __defsize_cells);
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_COD          = __32(data);
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	//dat = data;
	AMX_HEADER_DAT          = 0;
	AMX_BASE_ADDRESS = -__32(data);
	AMX_HEADER_COD += AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_HEA          = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_STP          = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_CIP          = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_PUBLICS      = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_NATIVES      = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_LIBRARIES    = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_PUBVARS      = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_TAGS         = __32(data) + AMX_BASE_ADDRESS;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_NAMETABLE    = __32(data) + AMX_BASE_ADDRESS;
	// Now find the AMX's base address in global memory.  This is VERY handy to
	// have for more advanced functionality (none of which actually exists yet).
	AMX_REAL_ADDRESS = AMX_GetGlobal();
	AMX_REAL_DATA = AMX_REAL_ADDRESS - AMX_BASE_ADDRESS;
	// Since this code was copied from amx_assembly there are some weird `-`s in
	// it.  All amx_assembly code is written relative to the AMX base address,
	// which has the advantage that all header data is used exactly as it is in
	// the header.  All y_amx code is written relative to DAT, which has the
	// advantage that most reads and writes need no offset manipulations.
	// However, this does mean that when porting code from one place to the
	// other a lot of adjustments are required.
	AMX_HeaderTableQuickSort(AMX_HEADER_TAGS - AMX_BASE_ADDRESS, AMX_HEADER_NAMETABLE - __defsize_cells - AMX_BASE_ADDRESS, -AMX_BASE_ADDRESS, __defsize_cells);
	AMX_HeaderTableQuickSort(AMX_HEADER_LIBRARIES - AMX_BASE_ADDRESS, AMX_HEADER_PUBVARS - __defsize_cells - AMX_BASE_ADDRESS, -AMX_BASE_ADDRESS, __defsize_cells);
	// Call next ALS callback.
	#if defined YSI_LOCK_MODE
		GetServerVarAsString(YSI_gLockData, YSI_gLockData[5], sizeof (YSI_gLockData) - 5);
	#endif
	#if defined AMX_OnCodeInit
		AMX_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit AMX_OnCodeInit
#if defined AMX_OnCodeInit
	forward AMX_OnCodeInit();
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   Check that we can use direct offsets to native names.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:AMX_NativeNamePointers();

#if __COMPILER___EMIT_U
	#define AMX_NativeNamePointers() (bool:(__emit(ZERO.pri, LCTRL __flg, CONST.alt 512, AND, EQ.C.pri 0)))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The passed address, in the server not the AMX.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetGlobalAddress(...)
{
	assert(numargs() == 1);
	new
		addr = 0;
	// addr = numargs();
	#emit LOAD.S.pri   __args_offset
	#emit STOR.S.pri   addr
	if (addr > 0)
	{
		// getargptr(0);
		#emit LOAD.S.pri   __param0_offset
		#emit LOAD.alt     AMX_REAL_DATA
		#emit ADD
		#emit POP.alt
		#emit RETN
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The passed address in the AMX.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetRelativeAddress(...)
{
	assert(numargs() == 1);
	new
		addr = 0;
	// addr = numargs();
	#emit LOAD.S.pri   __args_offset
	#emit STOR.S.pri   addr
	if (addr > 0)
	{
		// getargptr(0);
		#emit LOAD.S.pri   __param0_offset
		#emit POP.alt
		#emit RETN
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <remarks>
 *   A dummy function used to get the address of.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static AMX_DoNothing()
{
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The address of the AMX in the server.
 * </returns>
 *//*------------------------------------------------------------------------**/

static AMX_GetGlobal()
{
	new
		addr = -1;
	// Call dummy function and read its (absolute) address from code.
	AMX_DoNothing();
	#emit LCTRL        __cip
	#emit ADD.C        __m3_cells
	#emit LOAD.alt     AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri   addr
	#emit LREF.S.pri   addr
	// Get difference between absolute and relative addresses.
	#emit SUB
	#emit CONST.alt    AMX_DoNothing
	#emit SUB
	#emit MOVE.alt
	#emit LCTRL        __dat
	#emit XCHG
	#emit SUB
	// Return
	#emit POP.alt
	#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="pattern">The pattern to scan for in code.</param>
 * <param name="addrRet">The return for the address.</param>
 * <param name="dataRet">The return for the parameter.</param>
 * <param name="size">The size of the pattern.</param>
 * <remarks>
 *   An extremely poor-mans version of codescan.  Just takes a pure array of
 *   opcodes and searches for it in memory.  No data wildcards, no stack
 *   tracing, no opcode value lookup, etc.  Returns the next cell after the end
 *   of a found pattern as if it were an opcode parameter.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_TraceCode(pattern[], &addrRet, &dataRet, size = sizeof (pattern))
{
	new
		addr = AMX_HEADER_COD + addrRet,
		i = 0;
	while (addr < AMX_HEADER_DAT)
	{
		if (AMX_Read(addr) == pattern[i])
		{
			++i;
			addr += cellbytes;
			if (i == size)
			{
				addrRet = addr - i * cellbytes - AMX_HEADER_COD;
				dataRet = AMX_Read(addr);
				return 1;
			}
		}
		else if (i)
		{
			addr -= i * cellbytes - cellbytes;
			i = 0;
		}
		else
		{
			addr += cellbytes;
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="pattern">The pattern to scan for in data.</param>
 * <param name="addrRet">The return for the address.</param>
 * <param name="dataRet">The return for the parameter.</param>
 * <param name="size">The size of the pattern.</param>
 * <remarks>
 *   Search for the given pattern in the data segment.  Return the address of
 *   the match and the data immediately following the match.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_TraceMemory(pattern[], &addrRet, &dataRet, size = sizeof (pattern))
{
	new
		addr = AMX_HEADER_DAT + addrRet,
		i = 0;
	while (addr < AMX_HEADER_HEA)
	{
		if (AMX_Read(addr) == pattern[i])
		{
			++i;
			addr += cellbytes;
			if (i == size)
			{
				addrRet = addr - i * cellbytes - AMX_HEADER_DAT;
				dataRet = AMX_Read(addr);
				return 1;
			}
		}
		else if (i)
		{
			addr -= i * cellbytes - cellbytes;
			i = 0;
		}
		else
		{
			addr += cellbytes;
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">The table in the header (publics, tags, etc).</param>
 * <param name="base">Return for the start pointer.</param>
 * <param name="count">Return for the count.</param>
 * <remarks>
 *   Get information about one of the tables in the AMX header.  These are
 *   lists of address/name pairs.  The address is one cell long, and points to
 *   where in code/data/vm the corresponding symbol is located.  The name is
 *   <c>defsize - cellbytes</c> long, which may not be exactly one cell (all of
 *   y_amx assumes that this value is known at compile-time, but amx_assembly
 *   more correctly reads it from the header), and points to the start of the
 *   name as a C string in the AMX header's nametable.  This function just gets
 *   where in memory (relative to DAT) the table starts, and how many items
 *   there are in the table.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetBaseCount(E_AMX_TABLE:table, &base, &count)
{
	Debug_Print7("AMX_GetBaseCount called: %i, %i, %i", _:table, base, count);
	switch (table)
	{
		case AMX_TABLE_PUBLICS:
		{
			base = AMX_HEADER_PUBLICS;
			count = (AMX_HEADER_NATIVES - AMX_HEADER_PUBLICS) / __defsize_cells;
		}
		case AMX_TABLE_NATIVES:
		{
			base = AMX_HEADER_NATIVES;
			count = (AMX_HEADER_LIBRARIES - AMX_HEADER_NATIVES) / __defsize_cells;
		}
		case AMX_TABLE_LIBRARIES:
		{
			base = AMX_HEADER_LIBRARIES;
			count = (AMX_HEADER_PUBVARS - AMX_HEADER_LIBRARIES) / __defsize_cells;
		}
		case AMX_TABLE_PUBVARS:
		{
			base = AMX_HEADER_PUBVARS;
			count = (AMX_HEADER_TAGS - AMX_HEADER_PUBVARS) / __defsize_cells;
		}
		case AMX_TABLE_TAGS:
		{
			base = AMX_HEADER_TAGS;
			count = (AMX_HEADER_NAMETABLE - AMX_HEADER_TAGS) / __defsize_cells;
		}
		default:
		{
			base = 0;
			count = 0;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">An optional name to look for.</param>
 * <param name="exact">When true find the pattern exactly, otherwise just include it.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the public variables table to find one matching the
 *   given name pattern, or just the next one when no pattern is given.  Loop
 *   over all public variables with:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer;                            <br />
 *    while ((idx = AMX_GetPubvarEntry(idx, buffer))) <br />
 *    {                                               <br />
 *    }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarEntry`
stock AMX_GetPubvarEntry(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetEntry(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicEntry( AMX_GetEntry(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryEntry( AMX_GetEntry(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntry( AMX_GetEntry(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntry( AMX_GetEntry(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">An optional name to look for.</param>
 * <param name="exact">When true find the pattern exactly, otherwise just include it.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one matching the given
 *   name pattern, or just the next one when no pattern is given.  Loop over all
 *   public functions with:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer;                            <br />
 *    while ((idx = AMX_GetPublicEntry(idx, buffer))) <br />
 *    {                                               <br />
 *    }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.  You should not use this function directly,
 *   but one of the macro wrappers defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicEntry</c>
 *   <c>AMX_GetPubVarEntry</c>
 *   <c>AMX_GetLibraryEntry</c>
 *   <c>AMX_GetTagEntry</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntry(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetEntryBinary called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		base = 0,
		count = 0;
	AMX_GetBaseCount(table, base, count);
	if (exact)
	{
		if (idx)
		{
			return 0;
		}
		// Binary search.
		#if cellbits == 32
			new quick = (pattern[3]) | (pattern[2] << 8) | (pattern[1] << 16) | (pattern[0] << 24);
		#elseif cellbits == 64
			new quick = (pattern[7]) | (pattern[6] << 8) | (pattern[5] << 16) | (pattern[4] << 24) | (pattern[3] << 32) | (pattern[2] << 40) | (pattern[1] << 48) | (pattern[0] << 56);
		#else
			#error Unsupported `cellbits`.
		#endif
			new
				addr = 0,
				str[FUNCTION_LENGTH],
				mid,
				pos;
			while (idx < count)
			{
				mid = (idx + count) / 2;
				pos = mid * __defsize_cells + base + cellbytes;
				for ( ; ; )
				{
					Debug_Print7("Looking for: %s, %d, %d, %d", pattern, idx, mid, count);
					addr = __32(AMX_Read(pos)) + AMX_BASE_ADDRESS;
					Debug_Code7{AMX_ReadPackedString(addr, str);}
					Debug_Print7("    %d, %d, %s", pos, addr, Unpack(str));
					Debug_Print7("    %08x, %08x, %d", quick, Cell_ReverseBytes(AMX_Read(addr)), Cell_ReverseBytes(AMX_Read(addr)) - quick);
					if (addr == AMX_BASE_ADDRESS)
					{
						if (++mid == count)
						{
							// Tested this entire half.
							count = (idx + count) / 2;
							break;
						}
						pos += __defsize_cells;
						continue;
					}
					// Bad reuse of a variable, but I ran out...
					table = E_AMX_TABLE:Cell_ReverseBytes(AMX_Read(addr));
					if (_:table < quick)
					{
						idx = mid + 1;
						break;
					}
					else if (_:table > quick)
					{
						count = mid;
						break;
					}
					AMX_ReadPackedString(addr, str);
					addr = strcmp(str, pattern);
					if (addr < 0)
					{
						idx = mid + 1;
					}
					else if (addr > 0)
					{
						count = mid;
					}
					else
					{
						buffer = pos - cellbytes;
						return cellmax;
					}
					break;
				}
			}
	}
	else
	{
		new
			addr = 0,
			pos = idx * __defsize_cells + base + cellbytes,
			str[FUNCTION_LENGTH];
		while (idx++ < count)
		{
			addr = __32(AMX_Read(pos)) + AMX_BASE_ADDRESS;
			if (addr != AMX_BASE_ADDRESS)
			{
				if (pattern[0] == '\0')
				{
					buffer = pos - cellbytes;
					return idx;
				}
				AMX_ReadPackedString(addr, str);
				if (strfind(str, pattern) != -1)
				{
					buffer = pos - cellbytes;
					return idx;
				}
			}
			pos += __defsize_cells;
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">An optional name to look for.</param>
 * <param name="exact">When true find the pattern exactly, otherwise just include it.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the native table to find one matching the given name
 *   pattern, or just the next one when no pattern is given.  Loop over all
 *   natives with:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer;                            <br />
 *    while ((idx = AMX_GetNativeEntry(idx, buffer))) <br />
 *    {                                               <br />
 *    }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeEntry(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetNativeEntry called: %i, %i, \"%s\", %i", idx, buffer, pattern, exact);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos = 0,
		str[FUNCTION_LENGTH];
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
	}
	pos = idx * __defsize_cells + base + cellbytes;
	while (idx++ < count)
	{
		if (pattern[0] == '\0')
		{
			buffer = pos - cellbytes;
			return idx;
		}
		if (slowNeeded)
		{
			AMX_ReadPackedString(addr, str),
			addr = addr + strlen(str) + 1;
		}
		else
		{
			addr = __32(AMX_Read(pos)) + AMX_BASE_ADDRESS;
			if (addr == AMX_BASE_ADDRESS)
			{
				pos += __defsize_cells;
				continue;
			}
			AMX_ReadPackedString(addr, str);
		}
		if (exact)
		{
			if (strcmp(str, pattern) == 0)
			{
				buffer = pos - cellbytes;
				return idx;
			}
		}
		else
		{
			if (strfind(str, pattern) != -1)
			{
				buffer = pos - cellbytes;
				return idx;
			}
		}
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the public variables table to find one whose name starts
 *   with the given prefix.  Prefixes are four bytes built from the first four
 *   characters in a name.  Prefixes are used extensively for looping over
 *   special function types as they require no string decoding and so can be
 *   compared very quickly.  The <c>_A</c> macro can be used to convert four
 *   characters in to the special format used by <c>pattern</c> (which is really
 *   just the C string as a 32-bit number).
 *   <p/>
 *   To loop over all public variables that start with <c>"var_"</c>:
 *   <p/>
 *   <code>
 *     new idx = 0, buffer;                                                      <br />
 *     while ((idx = AMX_GetPubvarEntryPrefix(idx, buffer, _A&lt;var_&gt;)))     <br />
 *     {                                                                         <br />
 *     }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarEntryPrefix`
stock AMX_GetPubvarEntryPrefix(idx, &buffer, pattern)
{
	return AMX_GetEntryPrefix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicEntryPrefix( AMX_GetEntryPrefix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryEntryPrefix( AMX_GetEntryPrefix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntryPrefix( AMX_GetEntryPrefix(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntryPrefix( AMX_GetEntryPrefix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one whose name starts
 *   with the given prefix.  Prefixes are four bytes built from the first four
 *   characters in a name.  Prefixes are used extensively for looping over
 *   special function types as they require no string decoding and so can be
 *   compared very quickly.  The <c>_A</c> macro can be used to convert four
 *   characters in to the special format used by <c>pattern</c> (which is really
 *   just the C string as a 32-bit number).
 *   <p/>
 *   <em>y_hooks</em> uses this function to find all of its special hook
 *   functions, which start with the magic four character sequence
 *   <c>"@yH_"</c> (both a prefix for this function, and a public function
 *   declaration as it starts with <c>@</c>), like so:
 *   <p/>
 *   <code>
 *     new idx = 0, buffer;                                                      <br />
 *     while ((idx = AMX_GetPublicEntryPrefix(idx, buffer, _A&lt;@yH_&gt;)))     <br />
 *     {                                                                         <br />
 *     }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.  You should not use this function directly,
 *   but one of the macro wrappers defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicEntryPrefix</c>
 *   <c>AMX_GetPubVarEntryPrefix</c>
 *   <c>AMX_GetLibraryEntryPrefix</c>
 *   <c>AMX_GetTagEntryPrefix</c>
 *   <p/>
 *   <p/>
 *   Prefixes are widely used in YSI as the names are sorted and so can be
 *   binary searched, the entries point to the start of the names, and once a
 *   prefix is passed there can be no more later (thanks to sorting).  Thus
 *   binary prefix searches are extremely efficient.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntryPrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetEntryPrefixBinary called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base = 0,
		count = 0,
		addr = 0,
		pos;
	AMX_GetBaseCount(table, base, count);
	if (idx == 0)
	{
		// Binary search for the start of the prefixes.
		new p2 = Cell_ReverseBytes(pattern); // Little-endian for comparisons.
		new
			upper = count,
			mid;
		while (idx < upper)
		{
			mid = (idx + upper) / 2;
			pos = mid * __defsize_cells + base + cellbytes;
			for ( ; ; )
			{
				#emit LREF.S.pri                pos
				#emit CONST.alt                 0xFFFFFFFF
				#emit AND
				#emit LOAD.alt                  AMX_BASE_ADDRESS
				#emit ADD
				#emit STOR.S.pri                addr
				if (addr == AMX_BASE_ADDRESS)
				{
					if (++mid == upper)
					{
						// Tested this entire half.
						upper = (idx + upper) / 2;
						break;
					}
					pos += __defsize_cells;
					continue;
				}
				if (Cell_ReverseBytes(AMX_Read(addr)) - p2 < 0)
				{
					idx = mid + 1;
					break;
				}
				else
				{
					// >=, because we want the very start.
					upper = mid;
					break;
				}
			}
		}
    
		// Now we re-check the value at `idx`.
	}
	// Get the address of the string.
	pos = idx * __defsize_cells + base + cellbytes;
	while (idx++ < count)
	{
		#emit LREF.S.pri                pos
		#emit CONST.alt                 0xFFFFFFFF
		#emit AND
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                addr
		//addr = __32(addr);
		if (addr != AMX_BASE_ADDRESS && AMX_Read(addr) == pattern)
		{
			buffer = pos - cellbytes;
			return idx;
		}
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find one whose name starts
 *   with the given prefix.  Prefixes are four bytes built from the first four
 *   characters in a name.  Prefixes are used extensively for looping over
 *   special function types as they require no string decoding and so can be
 *   compared very quickly.  The <c>_A</c> macro can be used to convert four
 *   characters in to the special format used by <c>pattern</c> (which is really
 *   just the C string as a 32-bit number).
 *   <p/>
 *   All the special <c>Func:</c> tags which encode parameter types could be
 *   looped over like so:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer;                                         <br />
 *    while ((idx = AMX_GetTagEntryPrefix(idx, buffer, _A&lt;F@_@&gt;))) <br />
 *    {                                                            <br />
 *    }
 *   </code>
 *   <p/>
 *   The <em>entry</em> is a pointer in to the table itself, i.e. address/name
 *   pair relative to <c>DAT</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeEntryPrefix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativeEntryPrefix called: %i, %i, %i", idx, buffer, pattern);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos;
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	// Get the address of the string.
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
	}
	pos = idx * __defsize_cells + base + cellbytes;
	while (idx++ < count)
	{
		if (slowNeeded)
		{
			if (AMX_Read(addr) == pattern)
			{
				buffer = pos - cellbytes;
				return idx;
			}
			addr = addr + AMX_ReadLength(addr) + 1;
		}
		else
		{
			#emit LREF.S.pri                pos
			#emit CONST.alt                 0xFFFFFFFF
			#emit AND
			#emit LOAD.alt                  AMX_BASE_ADDRESS
			#emit ADD
			#emit STOR.S.pri                addr
			//addr = __32(addr);
			if (addr != AMX_BASE_ADDRESS && AMX_Read(addr) == pattern)
			{
				buffer = pos - cellbytes;
				return idx;
			}
		}
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <em>AMX_GetEntrySuffix</em>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarEntrySuffix`
stock AMX_GetPubvarEntrySuffix(idx, &buffer, pattern)
{
	return AMX_GetEntrySuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns the table entry.  You should
 *   not use this function directly, but one of the macro wrappers defined for
 *   sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicEntrySuffix</c>
 *   <c>AMX_GetPubVarEntrySuffix</c>
 *   <c>AMX_GetLibraryEntrySuffix</c>
 *   <c>AMX_GetTagEntrySuffix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntrySuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetEntrySuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base = 0,
		count = 0,
		addr = 0,
		pos = 0;
	#if cellbits == 64
		// Suffixes are always 32-bit.
		pattern = pattern & 0xFFFFFFFF;
	#endif
	AMX_GetBaseCount(table, base, count);
	pos = idx * __defsize_cells + base + cellbytes;
	// Get the address of the string.
	#emit LREF.S.pri                pos
	#emit CONST.alt                 0xFFFFFFFF
	#emit AND
	#emit LOAD.alt                  AMX_BASE_ADDRESS
	#emit ADD
	#emit STOR.S.pri                addr
	while (idx++ < count)
	{
		addr = addr + AMX_ReadLength(addr) - 4;
		if (__32(AMX_Read(addr)) == pattern)
		{
			buffer = pos - cellbytes;
			return idx;
		}
		// Skip the rest of the string.
		addr += 5,
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The return value, with a pointer to a table entry.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns the table entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeEntrySuffix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativeEntrySuffix called: %i, %i, %i", idx, buffer, pattern);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos = 0;
	#if cellbits == 64
		// Suffixes are always 32-bit.
		pattern = pattern & 0xFFFFFFFF;
	#endif
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
		pos = idx * __defsize_cells + base + cellbytes;
	}
	else
	{
		pos = idx * __defsize_cells + base + cellbytes;
		// Get the address of the string.
		#emit LREF.S.pri                pos
		#emit CONST.alt                 0xFFFFFFFF
		#emit AND
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                addr
	}
	while (idx++ < count)
	{
		// Because we need the end of the string, thus the length, to use the
		// suffix there's no point separating this code for the fast and slow
		// search methods.  We always just read the last four bytes.
		addr = addr + AMX_ReadLength(addr) - 4;
		if (__32(AMX_Read(addr)) == pattern)
		{
			buffer = pos - cellbytes;
			return idx;
		}
		// Skip the rest of the string.
		addr += 5,
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed sring.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <em>AMX_GetName</em>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarName`
stock AMX_GetPubvarName(idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	return AMX_GetName(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicName( AMX_GetName(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryName( AMX_GetName(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarName( AMX_GetName(AMX_TABLE_PUBVARS,
#define AMX_GetTagName( AMX_GetName(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed sring.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one whose name contains
 *   the given pattern, or all of them when there is no pattern.  Loop over all
 *   the defined player callbacks like so:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer[FUNCTION_LENGTH];                             <br />
 *    while ((idx = AMX_GetPublicName(idx, buffer, "OnPlayer", false))) <br />
 *    {                                                                 <br />
 *    }
 *   </code>
 *   <p/>
 *   You should not use this function directly, but one of the macro wrappers
 *   defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicName</c>
 *   <c>AMX_GetPubVarName</c>
 *   <c>AMX_GetLibraryName</c>
 *   <c>AMX_GetTagName</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetName(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetNameBinary called: %i, %i, \"%s\", \"%s\"", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntry(table, idx, pointer, pattern, exact);
	if (idx)
	{
		AMX_ReadPackedString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed sring.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find one whose name contains
 *   the given pattern, or all of them when there is no pattern.  Loop over all
 *   the defined player callbacks like so:
 *   <p/>
 *   <code>
 *    new idx = 0, buffer[FUNCTION_LENGTH];                             <br />
 *    while ((idx = AMX_GetPublicName(idx, buffer, "OnPlayer", false))) <br />
 *    {                                                                 <br />
 *    }
 *   </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeName(idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetNativeName called: %i, \"%s\", \"%s\"", idx, buffer, pattern);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos = 0;
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
	}
	pos = idx * __defsize_cells + base + cellbytes;
	while (idx++ < count)
	{
		if (pattern[0] == '\0')
		{
			buffer = pos - cellbytes;
			return idx;
		}
		if (slowNeeded)
		{
			AMX_ReadPackedString(addr, buffer),
			addr = addr + strlen(buffer) + 1;
		}
		else
		{
			addr = __32(AMX_Read(pos)) + AMX_BASE_ADDRESS;
			if (addr == AMX_BASE_ADDRESS)
			{
				pos += __defsize_cells;
				continue;
			}
			AMX_ReadPackedString(addr, buffer);
		}
		if (exact)
		{
			if (strcmp(buffer, pattern) == 0)
			{
				return idx;
			}
		}
		else
		{
			if (strfind(buffer, pattern) != -1)
			{
				return idx;
			}
		}
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed string.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <c>AMX_GetNamePrefix</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarNamePrefix`
stock AMX_GetPubvarNamePrefix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	return AMX_GetNamePrefix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicNamePrefix( AMX_GetNamePrefix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryNamePrefix( AMX_GetNamePrefix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarNamePrefix( AMX_GetNamePrefix(AMX_TABLE_PUBVARS,
#define AMX_GetTagNamePrefix( AMX_GetNamePrefix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed string.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find the next entry matching
 *   the given prefix, and returns the full name of the entry.  You should not
 *   use this function directly, but one of the macro wrappers defined for
 *   sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicNamePrefix</c>
 *   <c>AMX_GetPubVarNamePrefix</c>
 *   <c>AMX_GetLibraryNamePrefix</c>
 *   <c>AMX_GetTagNamePrefix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNamePrefix(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNamePrefixBinary called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefix(table, idx, pointer, pattern);
	if (idx)
	{
		AMX_ReadPackedString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed string.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find the next entry matching
 *   the given prefix, and returns the full name of the entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeNamePrefix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNativeNamePrefix called: %i, \"%s\", %i", idx, buffer, pattern);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos;
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	// Get the address of the string.
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
	}
	pos = idx * __defsize_cells + base + cellbytes;
	while (idx++ < count)
	{
		if (slowNeeded)
		{
			if (AMX_Read(addr) == pattern)
			{
				AMX_ReadPackedString(addr, buffer);
				return idx;
			}
			addr = addr + AMX_ReadLength(addr) + 1;
		}
		else
		{
			#emit LREF.S.pri                pos
			#emit CONST.alt                 0xFFFFFFFF
			#emit AND
			#emit LOAD.alt                  AMX_BASE_ADDRESS
			#emit ADD
			#emit STOR.S.pri                addr
			//addr = __32(addr);
			if (addr != AMX_BASE_ADDRESS && AMX_Read(addr) == pattern)
			{
				AMX_ReadPackedString(addr, buffer);
				return idx;
			}
		}
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed sring.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <em>AMX_GetNameSuffix</em>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarNameSuffix`
stock AMX_GetPubvarNameSuffix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	return AMX_GetNameSuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicNameSuffix( AMX_GetNameSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryNameSuffix( AMX_GetNameSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarNameSuffix( AMX_GetNameSuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagNameSuffix( AMX_GetNameSuffix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The name return value, as a packed sring.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns the full name.  You should
 *   not use this function directly, but one of the macro wrappers defined for
 *   sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicNameSuffix</c>
 *   <c>AMX_GetPubVarNameSuffix</c>
 *   <c>AMX_GetLibraryNameSuffix</c>
 *   <c>AMX_GetTagNameSuffix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeNameSuffix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNativeNameSuffix called: %i, \"%s\", %i", idx, buffer, pattern);
	new
		bool:slowNeeded = !AMX_NativeNamePointers(),
		base = 0,
		count = 0,
		addr = 0,
		pos = 0;
	#if cellbits == 64
		// Suffixes are always 32-bit.
		pattern = pattern & 0xFFFFFFFF;
	#endif
	AMX_GetBaseCount(AMX_TABLE_NATIVES, base, count);
	if (slowNeeded)
	{
		addr = AMX_GetFirstNativeString();
		while (pos < idx)
		{
			// Skip earlier names.
			addr = addr + AMX_ReadLength(addr) + 1,
			++pos;
		}
		pos = idx * __defsize_cells + base + cellbytes;
	}
	else
	{
		pos = idx * __defsize_cells + base + cellbytes;
		// Get the address of the string.
		#emit LREF.S.pri                pos
		#emit CONST.alt                 0xFFFFFFFF
		#emit AND
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                addr
	}
	while (idx++ < count)
	{
		// Because we need the end of the string, thus the length, to use the
		// suffix there's no point separating this code for the fast and slow
		// search methods.  We always just read the last four bytes.
		base = addr + AMX_ReadLength(addr) - 4;
		if (__32(AMX_Read(base)) == pattern)
		{
			buffer = pos - cellbytes;
			AMX_ReadPackedString(addr, buffer);
			return idx;
		}
		// Skip the rest of the string.
		addr = base + 5,
		pos += __defsize_cells;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which unsorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <c>AMX_GetPointer</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarPointer`
stock AMX_GetPubvarPointer(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetPointer(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicPointer( AMX_GetPointer(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryPointer( AMX_GetPointer(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointer( AMX_GetPointer(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointer( AMX_GetPointer(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one whose name includes
 *   or exactly matches the given pattern.  The return value is the pointer from
 *   in the entry, not the entry itself, nor the data the pointer references
 *   (e.g. a funcion).  You should not use this function directly, but one of
 *   the macro wrappers defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicPointer</c>
 *   <c>AMX_GetPubVarPointer</c>
 *   <c>AMX_GetLibraryPointer</c>
 *   <c>AMX_GetTagPointer</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPointer(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetPointerBinary called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetEntry(table, idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find one whose name includes
 *   or exactly matches the given pattern.  The return value is the pointer from
 *   in the entry, not the entry itself, nor the data the pointer references
 *   (e.g. a funcion).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativePointer(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetNativePointer called: %i, %i, \"%s\", %i", idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetNativeEntry(idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which unsorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <c>AMX_GetPointerPrefix</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarPointerPrefix`
stock AMX_GetPubvarPointerPrefix(idx, &buffer, pattern)
{
	return AMX_GetPointerPrefix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicPointerPrefix( AMX_GetPointerPrefix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryPointerPrefix( AMX_GetPointerPrefix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointerPrefix( AMX_GetPointerPrefix(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointerPrefix( AMX_GetPointerPrefix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find the next entry matching
 *   the given prefix, and returns a pointer to the data.  You should not use
 *   this function directly, but one of the macro wrappers defined for sorted
 *   tables:
 *   <p/>
 *   <c>AMX_GetPublicPointerPrefix</c>
 *   <c>AMX_GetPubVarPointerPrefix</c>
 *   <c>AMX_GetLibraryPointerPrefix</c>
 *   <c>AMX_GetTagPointerPrefix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPointerPrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPointerPrefixBinary called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The pointer return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find the next entry matching
 *   the given prefix, and returns a pointer to the data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativePointerPrefix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativePointerPrefix called: %i, %i, %i", idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetNativeEntryPrefix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data pointer return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <em>AMX_GetPointerSuffix</em>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarPointerSuffix`
stock AMX_GetPubvarPointerSuffix(idx, &buffer, pattern)
{
	return AMX_GetPointerSuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data pointer return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns the data pointer.  You should
 *   not use this function directly, but one of the macro wrappers defined for
 *   sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicPointerSuffix</c>
 *   <c>AMX_GetPubVarPointerSuffix</c>
 *   <c>AMX_GetLibraryPointerSuffix</c>
 *   <c>AMX_GetTagPointerSuffix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPointerSuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPointerSuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntrySuffix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data pointer return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns the data pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativePointerSuffix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativePointerSuffix called: %i, %i, %i", idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetNativeEntrySuffix(idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of entries in this table.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarCount`
stock AMX_GetPubvarCount()
{
	return AMX_GetCount(AMX_TABLE_PUBVARS);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicCount( AMX_GetCount(AMX_TABLE_PUBLICS
#define AMX_GetNativeCount( AMX_GetCount(AMX_TABLE_NATIVES
#define AMX_GetLibraryCount( AMX_GetCount(AMX_TABLE_LIBRARIES
#define AMX_GetPubVarCount( AMX_GetCount(AMX_TABLE_PUBVARS
#define AMX_GetTagCount( AMX_GetCount(AMX_TABLE_TAGS

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to get the size of.</param>
 * <returns>
 *   The number of entries in this table.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetCount(E_AMX_TABLE:table)
{
	Debug_Print7("AMX_GetCount called: %i", _:table);
	AMX_GetBaseCount(table, _:table, _:table);
	return _:table;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <c>AMX_GetValue</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarValue`
stock AMX_GetPubvarValue(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetPubVarValue(idx, buffer, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicValue( AMX_GetValue(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryValue( AMX_GetValue(AMX_TABLE_LIBRARIES,
#define AMX_GetTagValue( AMX_GetValue(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one whose name includes
 *   or exactly matches the given pattern.  The return value is the data pointed
 *   to by the entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPubVarValue(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetPubVarValue called: %i, %i, \"%s\", %i", idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetPointerBinary(AMX_TABLE_PUBVARS, idx, pointer, pattern, exact);
	if (idx)
	{
		// This is the only one that makes sense, so the only one that returns a
		// valid value.
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find one whose name includes
 *   or exactly matches the given pattern.  The return value is the data pointed
 *   to by the entry.  You should not use this function directly, but one of the
 *   macro wrappers defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicValue</c>
 *   <c>AMX_GetLibraryValue</c>
 *   <c>AMX_GetTagValue</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetValue(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetValue called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetEntry(table, idx, idx, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to look for.</param>
 * <param name="exact">True to match the pattern exactly, false for contains.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find one whose name includes
 *   or exactly matches the given pattern.  The return value is the data pointed
 *   to by the entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetNativeValue(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetNativeValue called: %i, %i, \"%s\", %i", idx, buffer, pattern, exact);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetNativeEntry(idx, idx, pattern, exact);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <c>AMX_GetValuePrefix</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarValuePrefix`
stock AMX_GetPubvarValuePrefix(idx, &buffer, pattern)
{
	return AMX_GetPubVarValuePrefix(idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicValuePrefix( AMX_GetValuePrefix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryValuePrefix( AMX_GetValuePrefix(AMX_TABLE_LIBRARIES,
#define AMX_GetTagValuePrefix( AMX_GetValuePrefix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find the next entry matching
 *   the given prefix, and returns the data pointed to by that entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPubVarValuePrefix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPubVarValuePrefix called: %i, %i, %i", idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetPointerPrefixBinary(AMX_TABLE_PUBVARS, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which sorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given sorted table to find the next entry matching
 *   the given prefix, and returns the data pointed to by that entry.  You
 *   should not use this function directly, but one of the macro wrappers
 *   defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicValuePrefix</c>
 *   <c>AMX_GetLibraryValuePrefix</c>
 *   <c>AMX_GetTagValuePrefix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetValuePrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetValuePrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetEntryPrefix(table, idx, idx, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which unsorted table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A prefix to scan for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through the given unsorted table to find the next entry matching
 *   the given prefix, and returns the data pointed to by that entry.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetNativeValuePrefix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativeValuePrefix called: %i, %i, %i", idx, buffer, pattern);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetNativeEntryPrefix(idx, idx, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   See <em>AMX_GetPubVarValueSuffix</em>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_GetPubVarValueSuffix`
stock AMX_GetPubvarValueSuffix(idx, &buffer, pattern)
{
	return AMX_GetPubVarValueSuffix(idx, buffer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define AMX_GetPublicValueSuffix( AMX_GetValueSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetLibraryValueSuffix( AMX_GetValueSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetTagValueSuffix( AMX_GetValueSuffix(AMX_TABLE_TAGS,

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns data from the data pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPubVarValueSuffix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPubVarValueSuffix called: %i, %i, %i", idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetPointerSuffix(AMX_TABLE_PUBVARS, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns data from the data pointer.
 *   You should not use this function directly, but one of the macro wrappers
 *   defined for sorted tables:
 *   <p/>
 *   <c>AMX_GetPublicValueSuffix</c>
 *   <c>AMX_GetLibraryValueSuffix</c>
 *   <c>AMX_GetTagValueSuffix</c>
 *   <p/>
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetValueSuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetValueSuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetEntrySuffix(table, idx, pointer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which table to scan through.</param>
 * <param name="idx">When iterating, the offset to start at.</param>
 * <param name="buffer">The data return value.</param>
 * <param name="pattern">A suffix to look for.</param>
 * <returns>
 *   The next index (<c>idx</c>) to continue scanning from, or <c>0</c>.
 * </returns>
 * <remarks>
 *   This scans through any table to look for names ending with the given four
 *   byte suffix.  These suffixes are defined in the same way as the prefixes
 *   used by <c>AMX_GetPublicEntryPrefix</c> et. al, but the scanning is much
 *   harder because the full names must all be read.  Unlike prefix scanning,
 *   suffix scanning is very inefficient.  Returns data from the data pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Getting these values are meaningless.
stock AMX_GetNativeValueSuffix(idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetNativeValueSuffix called: %i, %i, %i", idx, buffer, pattern);
	buffer = 0;
	// Don't even need to look up a pointer, just advance `idx`.
	return AMX_GetNativeEntrySuffix(idx, pointer, pattern);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tableEntry">The table entry in the AMX header to use.</param>
 * <returns>
 *   The data pointer in this table (the first cell in the struct).
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntryPointer(tableEntry)
{
	#emit LREF.S.pri tableEntry
	#emit RETN
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="index">The position in the native functions table.</param>
 * <returns>
 *   A pointer to this table entry.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntryFromNativeIndex(index)
{
	return index * __defsize_cells + AMX_HEADER_NATIVES;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="index">The position in the public functions table.</param>
 * <returns>
 *   A pointer to this table entry.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetEntryFromPublicIndex(index)
{
	// An index is an offset in to their own table.
	return index * __defsize_cells + AMX_HEADER_PUBLICS;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tableEntry">The AMX header native function entry to use.</param>
 * <returns>
 *   The index (i.e the position in the table) of this native function entry.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeIndexFromEntry(tableEntry) 
{
	return (tableEntry - AMX_HEADER_NATIVES) / __defsize_cells;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tableEntry">The AMX header public function entry to use.</param>
 * <returns>
 *   The index (i.e the position in the table) of this public function entry.
 * </returns>
 * <remarks>
 *   The value returned corresponds to the return value of <c>funcidx</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPublicIndexFromEntry(tableEntry)
{
	return (tableEntry - AMX_HEADER_PUBLICS) / __defsize_cells;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tableEntry">The AMX header table entry to use.</param>
 * <returns>
 *   The length of the name of this entry.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetLengthFromEntry(tableEntry)
{
	tableEntry += cellbytes;
	#emit LREF.S.pri                tableEntry
	#emit CONST.alt                 0xFFFFFFFF
	#emit AND
	#emit LOAD.alt                  AMX_BASE_ADDRESS
	#emit ADD
	#emit STOR.S.pri                tableEntry
	return AMX_ReadLength(tableEntry);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Pointer to a C string.</param>
 * <returns>
 *   The length of the string.
 * </returns>
 * <remarks>
 *   Operates on C strings, as found in the header, not pawn packed strings,
 *   which have their bytes reversed in a cell.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_ReadLength(addr)
{
	new
		buffer = 0,
		len = 0;
	for ( ; ; )
	{
		// Read 4 bytes.
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                buffer
		
		// https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/
		if (Cell_HasZeroByte(buffer))
		{
			if (buffer & 0x000000FF)
			{
				++len;
				if (buffer & 0x0000FF00)
				{
					++len;
					if (buffer & 0x00FF0000)
					{
							++len;
						#if cellbits == 64
							if (buffer & 0x00000000FF000000)
							{
								++len;
								if (buffer & 0x000000FF00000000)
								{
									++len;
									if (buffer & 0x0000FF0000000000)
									{
										++len;
										if (buffer & 0x00FF000000000000)
										{
											++len;
						#endif
											// No point checking the last byte, one of them must be
											// `0`, and it wasn't any of the other three.
						#if cellbits == 64
										}
									}
								}
							}
						#endif
					}
				}
			}
			break;
		}
		addr += cellbytes;
		len += cellbytes;
	}
	return len;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tableEntry">The header entry that has a name pointer.</param>
 * <param name="str">The destination array.</param>
 * <param name="size">The size of the destination array.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a C string in AMX memory out to a packed string.  The pointer does
 *   not point straight to the string, but instead points to a header
 *   <em>entry</em>, i.e. part of a table with a data pointer and a name
 *   pointer.  This thus abstracts the weirdness of the size of the name
 *   pointer, which may not be a whole cell.  There is no unpacked equivalent.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetStringFromEntry(tableEntry, str[], size = sizeof (str))
{
	AMX_ReadPackedString(__32(AMX_Read(tableEntry + cellbytes)) + AMX_BASE_ADDRESS, str, size);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to read the string from.</param>
 * <param name="str">The destination array.</param>
 * <param name="len">The size of the destination array.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a C string in AMX memory out to a packed string.  Mainly used to
 *   read function names from the header, as they are not in pawn order.  Uses a
 *   clever trick to detect <c>NULL</c> in four bytes at once.  Deprecated name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_ReadPackedString`
stock AMX_ReadString(addr, str[], len = sizeof (str))
{
	AMX_ReadPackedString(addr, str, len);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to read the string from.</param>
 * <param name="str">The destination array.</param>
 * <param name="len">The size of the destination array.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a C string in AMX memory out to a packed string.  Mainly used to
 *   read function names from the header, as they are not in pawn order.  Uses a
 *   clever trick to detect <c>NULL</c> in four bytes at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_ReadPackedString(addr, str[], len = sizeof (str))
{
	new
		buffer = 0,
		idx = 0;
	do
	{
		// Read 4 bytes.
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                buffer
		str[idx] = swapchars(buffer);
		
		// https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/
		if (Cell_HasZeroByte(buffer))
		{
			return;
		}
		addr += cellbytes;
	}
	while (++idx < len);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to read the string from.</param>
 * <param name="str">The destination array.</param>
 * <param name="len">The size of the destination array.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a C string in AMX memory out to an unpacked string.  Mainly used to
 *   read function names from the header, as they are not in pawn order.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_ReadUnpackedString(addr, str[], len = sizeof (str))
{
		new
			buffer = 0,
			idx = 0;
		len -= cellbytes - 1;
		while (idx < len)
		{
				// Read 4/8 bytes.
				#emit LREF.S.pri                addr
				#emit STOR.S.pri                buffer
				if (
					((str[idx++] = (buffer       ) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 8 ) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 16) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 24) & 0xFF) == 0))
				{
					return;
				}
			#if cellbits == 64
				if (
					((str[idx++] = (buffer >>> 32) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 40) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 48) & 0xFF) == 0) ||
					((str[idx++] = (buffer >>> 56) & 0xFF) == 0))
				{
					return;
				}
			#endif
				addr += cellbytes;
		}
		len += cellbytes - 1;
		// Read 4 bytes.
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                buffer
		if (!(str[idx++] = (buffer       ) & 0xFF) || (idx == len))
		{
			return;
		}
		if (!(str[idx++] = (buffer >>> 8 ) & 0xFF) || (idx == len))
		{
			return;
		}
		if (!(str[idx++] = (buffer >>> 16) & 0xFF) || (idx == len))
		{
			return;
		}
	#if cellbits == 64
		if (!(str[idx++] = (buffer >>> 24) & 0xFF) || (idx == len))
		{
			return;
		}
		if (!(str[idx++] = (buffer >>> 32) & 0xFF) || (idx == len))
		{
			return;
		}
		if (!(str[idx++] = (buffer >>> 40) & 0xFF) || (idx == len))
		{
			return;
		}
		if (!(str[idx++] = (buffer >>> 48) & 0xFF) || (idx == len))
		{
			return;
		}
		//if (!(str[idx++] = (buffer >>> 56) & 0xFF) || (idx == len))
		//{
		//	return;
		//}
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to write the string to.</param>
 * <param name="str">The packed string to write.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a packed string in to AMX memory, as a C string.  Mainly used to
 *   write function names in to the header, as they are not in pawn order.  Old
 *   attempt at efficiently detecting the end of the string and short-circuiting
 *   the common case, but turned out to be way slower.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `AMX_WritePackedString`
stock AMX_WriteString(addr, const str[], len = sizeof (str))
{
	#pragma unused len
	new
		buffer = 0,
		idx = 0;
	// These have to go up here because for some reason older compilers give
	// weird warnings when they're more tightly scoped and have the same names.
	const mask0 = -1 << 8;
	const mask1 = -1 << 16;
	const mask2 = 0x000000FF;
	const mask3 = -1 << 24;
	const mask4 = 0x0000FFFF;
	for ( ; ; ++idx)
	{
			buffer = str[idx];
			Debug_Print7("AMX_WriteString: Writing %04x%04x", buffer >>> 16, buffer & 0xFFFF);
			buffer = swapchars(buffer);
			if      (!(buffer & 0x000000FF))
			{
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask0
				#emit AND
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0x0000FF00))
			{
				// This:
				//            '\0', '1'.
				// Becomes:
				//  '1', '\0', ???, ???.
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask1
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask2
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0x00FF0000))
			{
				// This:
				//       '\0', '2', '1'.
				// Becomes:
				//  '1', '2', '\0', ???.
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask3
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask4
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
		/*#if cellbits == 64
			else if (!(buffer & 0x00000000FF000000))
			{
				const mask0 = -1 << 32;
				const mask1 = 0x0000000000FFFFFF;
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask0
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask1
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0x000000FF00000000))
			{
				const mask0 = -1 << 40;
				const mask1 = 0x00000000FFFFFFFF;
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask0
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask1
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0x0000FF0000000000))
			{
				const mask0 = -1 << 48;
				const mask1 = 0x000000FFFFFFFFFF;
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask0
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask1
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0x00FF000000000000))
			{
				const mask0 = -1 << 56;
				const mask1 = 0x0000FFFFFFFFFFFF;
				#emit LREF.S.pri                addr
				#emit CONST.alt                 mask0
				#emit AND
				#emit PUSH.pri
				#emit LOAD.S.pri                buffer
				#emit CONST.alt                 mask1
				#emit AND
				#emit POP.alt
				#emit OR
				#emit SREF.S.pri                addr
				return;
			}
			else if (!(buffer & 0xFF00000000000000))
			{
				// The code seems to skip a step in `0x00FFFFFFFFFFFFFF`, but
				// that would normally mask out the null byte and add nothing of
				// the original contents.  But masking out a null byte is
				// pointless in that case.
				#emit LOAD.S.pri                buffer
				#emit SREF.S.pri                addr
				return;
			}
		#else*/
			else if (!(buffer & 0xFF000000))
			{
				// This:
				//  '\0', '3', '2', '1'.
				// Becomes:
				//  '1', '2', '3', '\0'.
				// Write 3 bytes.
				#emit LOAD.S.pri                buffer
				#emit SREF.S.pri                addr
				return;
			}
		//#endif
			else
			{
				// Write 4 bytes.
				#emit LOAD.S.pri                buffer
				#emit SREF.S.pri                addr
				addr += cellbytes;
			}
	}
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to write the string to.</param>
 * <param name="str">The packed string to write.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies a packed string in to AMX memory, as a C string.  Mainly used to
 *   write function names in to the header, as they are not in pawn order.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_WritePackedString(addr, const str[])
{
	new
		buffer = 0,
		idx = -1,
		c;
	do
	{
		buffer = AMX_Read(addr),
		c = str{++idx},
		buffer = (buffer & ~0xFF) | (c & 0xFF),
		AMX_Write(addr, buffer),
		++addr;
	}
	while (c);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where in DAT to write the string to.</param>
 * <param name="str">The unpacked string to write.</param>
 * <returns>
 * </returns>
 * <remarks>
 *   Copies an unpacked string in to AMX memory, as a C string.  Mainly used to
 *   write function names in to the header, as they are not in pawn order.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_WriteUnpackedString(addr, const str[])
{
	new
		buffer = 0,
		idx = -1,
		c;
	do
	{
		buffer = AMX_Read(addr),
		c = str[++idx],
		buffer = (buffer & ~0xFF) | (c & 0xFF),
		AMX_Write(addr, buffer),
		++addr;
	}
	while (c);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Data source address.</param>
 * <param name="dest">Where to copy the data to.</param>
 * <param name="len">Amount of data to copy.</param>
 * <remarks>
 *   Read data out of a memory location, which may be outside the bounds of DAT.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_ReadArray(addr, dest[], len = sizeof (dest))
{
	// I tried to use memcpy, I couldn't get it to work, even when exactly
	// replicating compiler generated code...
	//
	// Given how old this code is, the reason for the above could well have been
	// the `SYSREQ.C memcpy` bug, which is long-since fixed.  So I should look
	// at this again.  However, could also just be that we're operating outside
	// `DAT` and `memcpy` tries to prevent that.
	while (len--)
	{
		// Load the address possibly outside "dat".  Can't be done using only
		// "pri"/"alt" as it relies on "LREF.S" explicitly.
		#emit LREF.S.pri                addr
		#emit SREF.S.pri                dest
		#emit LOAD.S.pri                addr
		#emit ADD.C                     __1_cell
		#emit STOR.S.pri                addr
		#emit LOAD.S.pri                dest
		#emit ADD.C                     __1_cell
		#emit STOR.S.pri                dest
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where to copy the data to.</param>
 * <param name="src">Data source.</param>
 * <param name="len">Amount of data to copy.</param>
 * <remarks>
 *   Write data to a memory location, which may be outside the bounds of DAT.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_WriteArray(addr, const src[], len = sizeof (src))
{
	while (len--)
	{
		#emit DEC.pri
		// Read the data.
		#emit LREF.S.pri                dest
		#emit SREF.S.pri                addr
		#emit LOAD.S.pri                addr
		#emit ADD.C                     __1_cell
		#emit STOR.S.pri                addr
		#emit LOAD.S.pri                dest
		#emit ADD.C                     __1_cell
		#emit STOR.S.pri                dest
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">A DAT pointer.</param>
 * <returns>
 *   An array whose data is at <c>addr</c>.  Converts a pointer to a pawn usable
 *   array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_Deref(addr)
{
	Debug_Print7("AMX_Deref called: %i", addr);
	#emit LOAD.S.pri                    addr
	#emit STOR.S.pri                    __param1_offset
	#emit RETN
	new ret[2];
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="tag">The tag value to look up (e.g. from <c>tagof</c>).</param>
 * <param name="name">The destination for the name.</param>
 * <param name="len">The destination size.</param>
 * <remarks>
 *   Get the original string (code) name of a tag from its ID.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_GetTagByValue(tag, name[], len = sizeof (name))
{
	new
		idx,
		buffer,
		value;
	while ((idx = AMX_GetEntry(AMX_TABLE_TAGS, idx, buffer)))
	{
		#emit LREF.S.pri buffer
		#emit STOR.S.pri value
		// Ignore the top two bits - they're flags we don't need.
		if (value & 0x3FFFFFFF == tag & 0x3FFFFFFF)
		{
			// Found the tag, get the name.
			AMX_ReadPackedString(__32(AMX_Read(buffer + cellbytes)) + AMX_BASE_ADDRESS, name, len);
			strunpack(name, name, len);
		}
	}
}

#define AMX_GetFirstPublicString( AMX_GetFirstString(AMX_TABLE_PUBLICS
#define AMX_GetFirstLibraryString( AMX_GetFirstString(AMX_TABLE_LIBRARIES
#define AMX_GetFirstPubVarString( AMX_GetFirstString(AMX_TABLE_PUBVARS
#define AMX_GetFirstTagString( AMX_GetFirstString(AMX_TABLE_TAGS

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="table">Which header table to report on.</param>
 * <returns>
 *   The address in the nametable of the first string name referenced by this
 *   table.  Should be called via the table-specific wrappers:
 *   <p/>
 *   <c>AMX_GetFirstPublicString</c>
 *   <c>AMX_GetFirstLibraryString</c>
 *   <c>AMX_GetFirstPubVarString</c>
 *   <c>AMX_GetFirstTagString</c>
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock AMX_GetFirstString(E_AMX_TABLE:table)
{
	// Get the first item in this table and resolve the name.
	table += E_AMX_TABLE:cellbytes;
	#emit LREF.S.pri                table
	#emit CONST.alt                 0xFFFFFFFF
	#emit AND
	#emit LOAD.alt                  AMX_BASE_ADDRESS
	#emit ADD
	#emit RETN
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The address in the nametable of the first string name referenced by this
 *   table.  Same as <c>AMX_GetFirstString</c>, but specialised for natives as
 *   their pointers may be clobbered in some VM versions.
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock AMX_GetFirstNativeString()
{
	// This can't use simple pointers because some VM versions clobber the
	// native name pointers.  Instead get the last public function and go beyond
	// it.
	new
		base = 0,
		count = 0;
	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base, count);
	if (count)
	{
		base = AMX_GetEntryFromPublicIndex(count - 1);
		base += cellbytes;
		#emit LREF.S.pri                base
		#emit CONST.alt                 0xFFFFFFFF
		#emit AND
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                base
		return base + AMX_ReadLength(base) + 1;
	}
	else
	{
		// If there are no public functions then the first things in the
		// nametable are the natives; so just return that offset.  I had a long
		// comment about this, and an assert to ensure that there was always at
		// least one public.  Then I realised the correct implementation was so
		// trivial I may as well do it.
		return AMX_HEADER_NAMETABLE;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of bytes used by all public function names in the nametable.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPublicStringSpace()
{
	// How many bytes in the header do the public strings take up?
	return AMX_GetFirstNativeString() - AMX_GetFirstPublicString();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of bytes used by all native function names in the nametable.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetNativeStringSpace()
{
	// How many bytes in the header do the native strings take up?
	return AMX_GetFirstLibraryString() - AMX_GetFirstNativeString();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of bytes used by all library names in the nametable.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetLibraryStringSpace()
{
	// How many bytes in the header do the library strings take up?
	return AMX_GetFirstPubVarString() - AMX_GetFirstLibraryString();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of bytes used by all public variable names in the nametable.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetPubVarStringSpace()
{
	// How many bytes in the header do the pub var strings take up?
	return AMX_GetFirstTagString() - AMX_GetFirstPubVarString();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   The number of bytes used by all tag names in the nametable.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock AMX_GetTagStringSpace()
{
	// How many bytes in the header do the tag strings take up?  Everything up
	// to the start of code.
	return (AMX_HEADER_COD - AMX_BASE_ADDRESS) - AMX_GetFirstTagString();
}

//stock AMX_CodToDat(ptr)
//{
//	// Convert a pointer in to the code segment in to a data offset.
//	return ptr + AMX_HEADER_COD;
//}

#define AMX_CodToDat(%0) ((%0) + AMX_HEADER_COD)
#define AMX_DatToCod(%0) ((%0) - AMX_HEADER_COD)

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <remarks>
 *   Print all the names of all the public functions from the AMX header.  There
 *   is now a more complete version of this function in amx_assembly called
 *   <c>PrintAmxHeader</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_DumpHeader()
{
	new
		idx = 0,
		buffer[FUNCTION_LENGTH];
	print("================================");
	while ((idx = AMX_GetPublicName(idx, buffer)))
	{
		strunpack(buffer, buffer);
		printf(buffer);
	}
	print("================================");
}

#if cellbits == 64
	// Extend the prefix to 8 bytes as simply as possible.
	#define _F<%0> %00000
#elseif cellbits == 32
	#define _F<%0> %0
#else
	#error Unsupported `cellbits`.
#endif

#define _A<%0> (_:H_Re(%0,))

// Do the next character test as this one failed.
#define H_Se(%0,%1,%3) H_Ne%1(%0,%3)
// End of string test failed.
#define H_Ee(%0,%3)    @E_:H_Se(%0,_,%3)
// Do the single addition.
#define H_De(%0,%1,%3) (_:H_Re(%0,%31))<<8|%1
// Recurse through the string.
#define H_Re(%0,%3)    he:H_Ee(%0,%3)
// Test for the end of a string (4 characters only).
#if cellbits == 64
	#define he:H_Ee(%0,1111)   808464432 // '0000' in decimal, to be short.
#elseif cellbits == 32
	#define he:H_Ee(%0,1111)   0
#else
	#error Unsupported `cellbits`.
#endif

// Test for the current character.

#define @E_:H_Se(_%0,%1,%3) H_De(%0,95,%3)
#define @E@:H_Se(@%0,%1,%3) H_De(%0,64,%3)
#define @Ey:H_Se(y%0,%1,%3) H_De(%0,121,%3)

#define @Ea:H_Se(a%0,%1,%3) H_De(%0,97,%3)
#define @Eb:H_Se(b%0,%1,%3) H_De(%0,98,%3)
#define @Ec:H_Se(c%0,%1,%3) H_De(%0,99,%3)
#define @Ed:H_Se(d%0,%1,%3) H_De(%0,100,%3)
#define @Ee:H_Se(e%0,%1,%3) H_De(%0,101,%3)
#define @Ef:H_Se(f%0,%1,%3) H_De(%0,102,%3)
#define @Eg:H_Se(g%0,%1,%3) H_De(%0,103,%3)
#define @Eh:H_Se(h%0,%1,%3) H_De(%0,104,%3)
#define @Ei:H_Se(i%0,%1,%3) H_De(%0,105,%3)
#define @Ej:H_Se(j%0,%1,%3) H_De(%0,106,%3)
#define @Ek:H_Se(k%0,%1,%3) H_De(%0,107,%3)
#define @El:H_Se(l%0,%1,%3) H_De(%0,108,%3)
#define @Em:H_Se(m%0,%1,%3) H_De(%0,109,%3)
#define @En:H_Se(n%0,%1,%3) H_De(%0,110,%3)
#define @Eo:H_Se(o%0,%1,%3) H_De(%0,111,%3)
#define @Ep:H_Se(p%0,%1,%3) H_De(%0,112,%3)
#define @Eq:H_Se(q%0,%1,%3) H_De(%0,113,%3)
#define @Er:H_Se(r%0,%1,%3) H_De(%0,114,%3)
#define @Es:H_Se(s%0,%1,%3) H_De(%0,115,%3)
#define @Et:H_Se(t%0,%1,%3) H_De(%0,116,%3)
#define @Eu:H_Se(u%0,%1,%3) H_De(%0,117,%3)
#define @Ev:H_Se(v%0,%1,%3) H_De(%0,118,%3)
#define @Ew:H_Se(w%0,%1,%3) H_De(%0,119,%3)
#define @Ex:H_Se(x%0,%1,%3) H_De(%0,120,%3)
#define @Ez:H_Se(z%0,%1,%3) H_De(%0,122,%3)

#define @EA:H_Se(A%0,%1,%3) H_De(%0,65,%3)
#define @EB:H_Se(B%0,%1,%3) H_De(%0,66,%3)
#define @EC:H_Se(C%0,%1,%3) H_De(%0,67,%3)
#define @ED:H_Se(D%0,%1,%3) H_De(%0,68,%3)
#define @EE:H_Se(E%0,%1,%3) H_De(%0,69,%3)
#define @EF:H_Se(F%0,%1,%3) H_De(%0,70,%3)
#define @EG:H_Se(G%0,%1,%3) H_De(%0,71,%3)
#define @EH:H_Se(H%0,%1,%3) H_De(%0,72,%3)
#define @EI:H_Se(I%0,%1,%3) H_De(%0,73,%3)
#define @EJ:H_Se(J%0,%1,%3) H_De(%0,74,%3)
#define @EK:H_Se(K%0,%1,%3) H_De(%0,75,%3)
#define @EL:H_Se(L%0,%1,%3) H_De(%0,76,%3)
#define @EM:H_Se(M%0,%1,%3) H_De(%0,77,%3)
#define @EN:H_Se(N%0,%1,%3) H_De(%0,78,%3)
#define @EO:H_Se(O%0,%1,%3) H_De(%0,79,%3)
#define @EP:H_Se(P%0,%1,%3) H_De(%0,80,%3)
#define @EQ:H_Se(Q%0,%1,%3) H_De(%0,81,%3)
#define @ER:H_Se(R%0,%1,%3) H_De(%0,82,%3)
#define @ES:H_Se(S%0,%1,%3) H_De(%0,83,%3)
#define @ET:H_Se(T%0,%1,%3) H_De(%0,84,%3)
#define @EU:H_Se(U%0,%1,%3) H_De(%0,85,%3)
#define @EV:H_Se(V%0,%1,%3) H_De(%0,86,%3)
#define @EW:H_Se(W%0,%1,%3) H_De(%0,87,%3)
#define @EX:H_Se(X%0,%1,%3) H_De(%0,88,%3)
#define @EY:H_Se(Y%0,%1,%3) H_De(%0,89,%3)
#define @EZ:H_Se(Z%0,%1,%3) H_De(%0,90,%3)

#define @E0:H_Se(0%0,%1,%3) H_De(%0,48,%3)
#define @E1:H_Se(1%0,%1,%3) H_De(%0,49,%3)
#define @E2:H_Se(2%0,%1,%3) H_De(%0,50,%3)
#define @E3:H_Se(3%0,%1,%3) H_De(%0,51,%3)
#define @E4:H_Se(4%0,%1,%3) H_De(%0,52,%3)
#define @E5:H_Se(5%0,%1,%3) H_De(%0,53,%3)
#define @E6:H_Se(6%0,%1,%3) H_De(%0,54,%3)
#define @E7:H_Se(7%0,%1,%3) H_De(%0,55,%3)
#define @E8:H_Se(8%0,%1,%3) H_De(%0,56,%3)
#define @E9:H_Se(9%0,%1,%3) H_De(%0,57,%3)

// Find the next character to test.  This tests `@`, `_`, and `y` first because
// those three are all used in the vast majority of `_A` uses, which tend to
// look something like `_A<@_yX>` - so these three and one more.  That's also
// usually a capital letter, so those are done next.
#define H_Ne_(%0,%3) @E@:H_Se(%0,@,%3)
#define H_Ne@(%0,%3) @Ey:H_Se(%0,y,%3)
#define H_Ney(%0,%3) @EA:H_Se(%0,A,%3)

#define H_NeA(%0,%3) @EB:H_Se(%0,B,%3)
#define H_NeB(%0,%3) @EC:H_Se(%0,C,%3)
#define H_NeC(%0,%3) @ED:H_Se(%0,D,%3)
#define H_NeD(%0,%3) @EE:H_Se(%0,E,%3)
#define H_NeE(%0,%3) @EF:H_Se(%0,F,%3)
#define H_NeF(%0,%3) @EG:H_Se(%0,G,%3)
#define H_NeG(%0,%3) @EH:H_Se(%0,H,%3)
#define H_NeH(%0,%3) @EI:H_Se(%0,I,%3)
#define H_NeI(%0,%3) @EJ:H_Se(%0,J,%3)
#define H_NeJ(%0,%3) @EK:H_Se(%0,K,%3)
#define H_NeK(%0,%3) @EL:H_Se(%0,L,%3)
#define H_NeL(%0,%3) @EM:H_Se(%0,M,%3)
#define H_NeM(%0,%3) @EN:H_Se(%0,N,%3)
#define H_NeN(%0,%3) @EO:H_Se(%0,O,%3)
#define H_NeO(%0,%3) @EP:H_Se(%0,P,%3)
#define H_NeP(%0,%3) @EQ:H_Se(%0,Q,%3)
#define H_NeQ(%0,%3) @ER:H_Se(%0,R,%3)
#define H_NeR(%0,%3) @ES:H_Se(%0,S,%3)
#define H_NeS(%0,%3) @ET:H_Se(%0,T,%3)
#define H_NeT(%0,%3) @EU:H_Se(%0,U,%3)
#define H_NeU(%0,%3) @EV:H_Se(%0,V,%3)
#define H_NeV(%0,%3) @EW:H_Se(%0,W,%3)
#define H_NeW(%0,%3) @EX:H_Se(%0,X,%3)
#define H_NeX(%0,%3) @EY:H_Se(%0,Y,%3)
#define H_NeY(%0,%3) @EZ:H_Se(%0,Z,%3)
#define H_NeZ(%0,%3) @Ea:H_Se(%0,a,%3)

#define H_Nea(%0,%3) @Eb:H_Se(%0,b,%3)
#define H_Neb(%0,%3) @Ec:H_Se(%0,c,%3)
#define H_Nec(%0,%3) @Ed:H_Se(%0,d,%3)
#define H_Ned(%0,%3) @Ee:H_Se(%0,e,%3)
#define H_Nee(%0,%3) @Ef:H_Se(%0,f,%3)
#define H_Nef(%0,%3) @Eg:H_Se(%0,g,%3)
#define H_Neg(%0,%3) @Eh:H_Se(%0,h,%3)
#define H_Neh(%0,%3) @Ei:H_Se(%0,i,%3)
#define H_Nei(%0,%3) @Ej:H_Se(%0,j,%3)
#define H_Nej(%0,%3) @Ek:H_Se(%0,k,%3)
#define H_Nek(%0,%3) @El:H_Se(%0,l,%3)
#define H_Nel(%0,%3) @Em:H_Se(%0,m,%3)
#define H_Nem(%0,%3) @En:H_Se(%0,n,%3)
#define H_Nen(%0,%3) @Eo:H_Se(%0,o,%3)
#define H_Neo(%0,%3) @Ep:H_Se(%0,p,%3)
#define H_Nep(%0,%3) @Eq:H_Se(%0,q,%3)
#define H_Neq(%0,%3) @Er:H_Se(%0,r,%3)
#define H_Ner(%0,%3) @Es:H_Se(%0,s,%3)
#define H_Nes(%0,%3) @Et:H_Se(%0,t,%3)
#define H_Net(%0,%3) @Eu:H_Se(%0,u,%3)
#define H_Neu(%0,%3) @Ev:H_Se(%0,v,%3)
#define H_Nev(%0,%3) @Ew:H_Se(%0,w,%3)
#define H_New(%0,%3) @Ex:H_Se(%0,x,%3)
#define H_Nex(%0,%3) @Ez:H_Se(%0,z,%3)
#define H_Nez(%0,%3) @E0:H_Se(%0,0,%3)

#define H_Ne0(%0,%3) @E1:H_Se(%0,1,%3)
#define H_Ne1(%0,%3) @E2:H_Se(%0,2,%3)
#define H_Ne2(%0,%3) @E3:H_Se(%0,3,%3)
#define H_Ne3(%0,%3) @E4:H_Se(%0,4,%3)
#define H_Ne4(%0,%3) @E5:H_Se(%0,5,%3)
#define H_Ne5(%0,%3) @E6:H_Se(%0,6,%3)
#define H_Ne6(%0,%3) @E7:H_Se(%0,7,%3)
#define H_Ne7(%0,%3) @E8:H_Se(%0,8,%3)
#define H_Ne8(%0,%3) @E9:H_Se(%0,9,%3)
#define H_Ne9(%0,%3) ()

#if cellbits == 64
	#define _C<%0> (_:H_Rc(%0,56))
	// Test for the end of a string (4 characters only).
	#define hc:H_Ec(%0,56-8-8-8-8)   808464432
#elseif cellbits == 32
	#define _C<%0> (_:H_Rc(%0,24))
	// Test for the end of a string (4 characters only).
	#define hc:H_Ec(%0,24-8-8-8-8)   0
#else
	#error Unsupported `cellbits`.
#endif

// Do the next character test as this one failed.
#define H_Sc(%0,%1,%3) H_Nc%1(%0,%3)
// End of string test failed.
#define H_Ec(%0,%3)    @C_:H_Sc(%0,_,%3)
// Do the single addition.
#define H_Dc(%0,%1,%3) (_:H_Rc(%0,%3-8))|%1<<%3
// Recurse through the string.
#define H_Rc(%0,%3)    hc:H_Ec(%0,%3)

// Test for the current character.

#define @C_:H_Sc(_%0,%1,%3) H_Dc(%0,95,%3)
#define @C@:H_Sc(@%0,%1,%3) H_Dc(%0,64,%3)
#define @Cy:H_Sc(y%0,%1,%3) H_Dc(%0,121,%3)

#define @Ca:H_Sc(a%0,%1,%3) H_Dc(%0,97,%3)
#define @Cb:H_Sc(b%0,%1,%3) H_Dc(%0,98,%3)
#define @Cc:H_Sc(c%0,%1,%3) H_Dc(%0,99,%3)
#define @Cd:H_Sc(d%0,%1,%3) H_Dc(%0,100,%3)
#define @Ce:H_Sc(e%0,%1,%3) H_Dc(%0,101,%3)
#define @Cf:H_Sc(f%0,%1,%3) H_Dc(%0,102,%3)
#define @Cg:H_Sc(g%0,%1,%3) H_Dc(%0,103,%3)
#define @Ch:H_Sc(h%0,%1,%3) H_Dc(%0,104,%3)
#define @Ci:H_Sc(i%0,%1,%3) H_Dc(%0,105,%3)
#define @Cj:H_Sc(j%0,%1,%3) H_Dc(%0,106,%3)
#define @Ck:H_Sc(k%0,%1,%3) H_Dc(%0,107,%3)
#define @Cl:H_Sc(l%0,%1,%3) H_Dc(%0,108,%3)
#define @Cm:H_Sc(m%0,%1,%3) H_Dc(%0,109,%3)
#define @Cn:H_Sc(n%0,%1,%3) H_Dc(%0,110,%3)
#define @Co:H_Sc(o%0,%1,%3) H_Dc(%0,111,%3)
#define @Cp:H_Sc(p%0,%1,%3) H_Dc(%0,112,%3)
#define @Cq:H_Sc(q%0,%1,%3) H_Dc(%0,113,%3)
#define @Cr:H_Sc(r%0,%1,%3) H_Dc(%0,114,%3)
#define @Cs:H_Sc(s%0,%1,%3) H_Dc(%0,115,%3)
#define @Ct:H_Sc(t%0,%1,%3) H_Dc(%0,116,%3)
#define @Cu:H_Sc(u%0,%1,%3) H_Dc(%0,117,%3)
#define @Cv:H_Sc(v%0,%1,%3) H_Dc(%0,118,%3)
#define @Cw:H_Sc(w%0,%1,%3) H_Dc(%0,119,%3)
#define @Cx:H_Sc(x%0,%1,%3) H_Dc(%0,120,%3)
#define @Cz:H_Sc(z%0,%1,%3) H_Dc(%0,122,%3)

#define @CA:H_Sc(A%0,%1,%3) H_Dc(%0,65,%3)
#define @CB:H_Sc(B%0,%1,%3) H_Dc(%0,66,%3)
#define @CC:H_Sc(C%0,%1,%3) H_Dc(%0,67,%3)
#define @CD:H_Sc(D%0,%1,%3) H_Dc(%0,68,%3)
#define @CE:H_Sc(E%0,%1,%3) H_Dc(%0,69,%3)
#define @CF:H_Sc(F%0,%1,%3) H_Dc(%0,70,%3)
#define @CG:H_Sc(G%0,%1,%3) H_Dc(%0,71,%3)
#define @CH:H_Sc(H%0,%1,%3) H_Dc(%0,72,%3)
#define @CI:H_Sc(I%0,%1,%3) H_Dc(%0,73,%3)
#define @CJ:H_Sc(J%0,%1,%3) H_Dc(%0,74,%3)
#define @CK:H_Sc(K%0,%1,%3) H_Dc(%0,75,%3)
#define @CL:H_Sc(L%0,%1,%3) H_Dc(%0,76,%3)
#define @CM:H_Sc(M%0,%1,%3) H_Dc(%0,77,%3)
#define @CN:H_Sc(N%0,%1,%3) H_Dc(%0,78,%3)
#define @CO:H_Sc(O%0,%1,%3) H_Dc(%0,79,%3)
#define @CP:H_Sc(P%0,%1,%3) H_Dc(%0,80,%3)
#define @CQ:H_Sc(Q%0,%1,%3) H_Dc(%0,81,%3)
#define @CR:H_Sc(R%0,%1,%3) H_Dc(%0,82,%3)
#define @CS:H_Sc(S%0,%1,%3) H_Dc(%0,83,%3)
#define @CT:H_Sc(T%0,%1,%3) H_Dc(%0,84,%3)
#define @CU:H_Sc(U%0,%1,%3) H_Dc(%0,85,%3)
#define @CV:H_Sc(V%0,%1,%3) H_Dc(%0,86,%3)
#define @CW:H_Sc(W%0,%1,%3) H_Dc(%0,87,%3)
#define @CX:H_Sc(X%0,%1,%3) H_Dc(%0,88,%3)
#define @CY:H_Sc(Y%0,%1,%3) H_Dc(%0,89,%3)
#define @CZ:H_Sc(Z%0,%1,%3) H_Dc(%0,90,%3)

#define @C0:H_Sc(0%0,%1,%3) H_Dc(%0,48,%3)
#define @C1:H_Sc(1%0,%1,%3) H_Dc(%0,49,%3)
#define @C2:H_Sc(2%0,%1,%3) H_Dc(%0,50,%3)
#define @C3:H_Sc(3%0,%1,%3) H_Dc(%0,51,%3)
#define @C4:H_Sc(4%0,%1,%3) H_Dc(%0,52,%3)
#define @C5:H_Sc(5%0,%1,%3) H_Dc(%0,53,%3)
#define @C6:H_Sc(6%0,%1,%3) H_Dc(%0,54,%3)
#define @C7:H_Sc(7%0,%1,%3) H_Dc(%0,55,%3)
#define @C8:H_Sc(8%0,%1,%3) H_Dc(%0,56,%3)
#define @C9:H_Sc(9%0,%1,%3) H_Dc(%0,57,%3)

// Find the next character to test.
#define H_Nc_(%0,%3) @C@:H_Sc(%0,@,%3)
#define H_Nc@(%0,%3) @Cy:H_Sc(%0,y,%3)
#define H_Ncy(%0,%3) @Ca:H_Sc(%0,a,%3)

#define H_Nca(%0,%3) @Cb:H_Sc(%0,b,%3)
#define H_Ncb(%0,%3) @Cc:H_Sc(%0,c,%3)
#define H_Ncc(%0,%3) @Cd:H_Sc(%0,d,%3)
#define H_Ncd(%0,%3) @Ce:H_Sc(%0,e,%3)
#define H_Nce(%0,%3) @Cf:H_Sc(%0,f,%3)
#define H_Ncf(%0,%3) @Cg:H_Sc(%0,g,%3)
#define H_Ncg(%0,%3) @Ch:H_Sc(%0,h,%3)
#define H_Nch(%0,%3) @Ci:H_Sc(%0,i,%3)
#define H_Nci(%0,%3) @Cj:H_Sc(%0,j,%3)
#define H_Ncj(%0,%3) @Ck:H_Sc(%0,k,%3)
#define H_Nck(%0,%3) @Cl:H_Sc(%0,l,%3)
#define H_Ncl(%0,%3) @Cm:H_Sc(%0,m,%3)
#define H_Ncm(%0,%3) @Cn:H_Sc(%0,n,%3)
#define H_Ncn(%0,%3) @Co:H_Sc(%0,o,%3)
#define H_Nco(%0,%3) @Cp:H_Sc(%0,p,%3)
#define H_Ncp(%0,%3) @Cq:H_Sc(%0,q,%3)
#define H_Ncq(%0,%3) @Cr:H_Sc(%0,r,%3)
#define H_Ncr(%0,%3) @Cs:H_Sc(%0,s,%3)
#define H_Ncs(%0,%3) @Ct:H_Sc(%0,t,%3)
#define H_Nct(%0,%3) @Cu:H_Sc(%0,u,%3)
#define H_Ncu(%0,%3) @Cv:H_Sc(%0,v,%3)
#define H_Ncv(%0,%3) @Cw:H_Sc(%0,w,%3)
#define H_Ncw(%0,%3) @Cx:H_Sc(%0,x,%3)
#define H_Ncx(%0,%3) @Cz:H_Sc(%0,z,%3)
#define H_Ncz(%0,%3) @CA:H_Sc(%0,A,%3)

#define H_NcA(%0,%3) @CB:H_Sc(%0,B,%3)
#define H_NcB(%0,%3) @CC:H_Sc(%0,C,%3)
#define H_NcC(%0,%3) @CD:H_Sc(%0,D,%3)
#define H_NcD(%0,%3) @CE:H_Sc(%0,E,%3)
#define H_NcE(%0,%3) @CF:H_Sc(%0,F,%3)
#define H_NcF(%0,%3) @CG:H_Sc(%0,G,%3)
#define H_NcG(%0,%3) @CH:H_Sc(%0,H,%3)
#define H_NcH(%0,%3) @CI:H_Sc(%0,I,%3)
#define H_NcI(%0,%3) @CJ:H_Sc(%0,J,%3)
#define H_NcJ(%0,%3) @CK:H_Sc(%0,K,%3)
#define H_NcK(%0,%3) @CL:H_Sc(%0,L,%3)
#define H_NcL(%0,%3) @CM:H_Sc(%0,M,%3)
#define H_NcM(%0,%3) @CN:H_Sc(%0,N,%3)
#define H_NcN(%0,%3) @CO:H_Sc(%0,O,%3)
#define H_NcO(%0,%3) @CP:H_Sc(%0,P,%3)
#define H_NcP(%0,%3) @CQ:H_Sc(%0,Q,%3)
#define H_NcQ(%0,%3) @CR:H_Sc(%0,R,%3)
#define H_NcR(%0,%3) @CS:H_Sc(%0,S,%3)
#define H_NcS(%0,%3) @CT:H_Sc(%0,T,%3)
#define H_NcT(%0,%3) @CU:H_Sc(%0,U,%3)
#define H_NcU(%0,%3) @CV:H_Sc(%0,V,%3)
#define H_NcV(%0,%3) @CW:H_Sc(%0,W,%3)
#define H_NcW(%0,%3) @CX:H_Sc(%0,X,%3)
#define H_NcX(%0,%3) @CY:H_Sc(%0,Y,%3)
#define H_NcY(%0,%3) @CZ:H_Sc(%0,Z,%3)
#define H_NcZ(%0,%3) @C0:H_Sc(%0,0,%3)

#define H_Nc0(%0,%3) @C1:H_Sc(%0,1,%3)
#define H_Nc1(%0,%3) @C2:H_Sc(%0,2,%3)
#define H_Nc2(%0,%3) @C3:H_Sc(%0,3,%3)
#define H_Nc3(%0,%3) @C4:H_Sc(%0,4,%3)
#define H_Nc4(%0,%3) @C5:H_Sc(%0,5,%3)
#define H_Nc5(%0,%3) @C6:H_Sc(%0,6,%3)
#define H_Nc6(%0,%3) @C7:H_Sc(%0,7,%3)
#define H_Nc7(%0,%3) @C8:H_Sc(%0,8,%3)
#define H_Nc8(%0,%3) @C9:H_Sc(%0,9,%3)
#define H_Nc9(%0,%3) ()

#if __COMPILER___EMIT_U
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where to write the data (relative to DAT).</param>
 * <param name="value">What to write.</param>
 * <remarks>
 *   Writes some data to any arbitrary location in the AMX, bypassing the
 *   DAT-only restriction.  This is the old function version in case the
 *   compiler being used doesn't have inline assembly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// Function call versions of `AMX_Read` and `AMX_Write`.
stock AMX_Write(addr, value)
{
	Debug_Print7("AMX_Write called: %i, %i", addr, value);
	#emit LOAD.S.pri                    value
	#emit SREF.S.pri                    addr
}

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">Where to read the data from (relative to DAT).</param>
 * <returns>
 *   The data at this address.
 * </returns>
 * <remarks>
 *   Read some data from any arbitrary location in the AMX, bypassing the
 *   DAT-only restriction.  
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_Read(addr)
{
	Debug_Print7("AMX_Read called: %i", addr);
	#emit LREF.S.pri                    addr
	#emit RETN
	__pragma("naked");
}

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 238
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <param name="addr">A variable that you want to get the address of.</param>
 * <returns>
 *   The address of the given parameter.
 * </returns>
 * <remarks>
 *   This is the old function version in case the compiler being used doesn't
 *   have inline assembly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock AMX_Ref(const &addr)
{
	Debug_Print7("AMX_Ref called: %i", addr);
	#emit LOAD.S.pri                    addr
	#emit RETN
	__pragma("naked");
}

#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_amx</library>
 * <returns>
 *   Check that we can use direct offsets to native names.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:AMX_NativeNamePointers()
{
	#emit ZERO.pri
	#emit LCTRL                         __flg
	#emit CONST.alt                     512
	#emit AND
	#emit EQ.C.pri                      0
	#emit RETN

	return true;
}

