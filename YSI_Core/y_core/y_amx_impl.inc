/*
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

/// <library>y_amx</library>
/// <summary>
///   -1, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_1 = -1;

/// <library>y_amx</library>
/// <summary>
///   -4, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_4 = -4;

/// <library>y_amx</library>
/// <summary>
///   -8, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_8 = -8;

/// <library>y_amx</library>
/// <summary>
///   -12, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_12 = -12;

/// <library>y_amx</library>
/// <summary>
///   -16, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_16 = -16;

/// <library>y_amx</library>
/// <summary>
///   -20, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_20 = -20;

/// <library>y_amx</library>
/// <summary>
///   -24, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_24 = -24;

/// <library>y_amx</library>
/// <summary>
///   -28, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_28 = -28;

/// <library>y_amx</library>
/// <summary>
///   -32, for use in <c>#emit</c> which fails with <c>-</c>.
/// </summary>
const EMIT_MINUS_32 = -32;

stock
	AMX_HEADER_SIZE = 0,
	AMX_HEADER_MAGIC = 0,
	AMX_HEADER_FILE_VERSION = 0,
	AMX_HEADER_AMX_VERSION = 0,
	AMX_HEADER_FLAGS = 0,
	AMX_HEADER_DEFSIZE = 0,
	// These are not as they appear in the AMX - they are relative to the dat
	// pointer so that they can be directly manipulated.
	AMX_HEADER_COD = 0,
	AMX_HEADER_DAT = 0,
	AMX_HEADER_HEA = 0,
	AMX_HEADER_STP = 0,
	AMX_HEADER_CIP = 0,
	AMX_HEADER_PUBLICS = 0,
	AMX_HEADER_NATIVES = 0,
	AMX_HEADER_LIBRARIES = 0,
	AMX_HEADER_PUBVARS = 0,
	AMX_HEADER_TAGS = 0,
	AMX_HEADER_NAMETABLE = 0,
	//E_AMX_HEADER_OVERLAYS,
	AMX_REAL_ADDRESS = 0,
	AMX_BASE_ADDRESS = 0,
	AMX_REAL_DATA = 0;

enum E_AMX_TABLE
{
	AMX_TABLE_PUBLICS,
	AMX_TABLE_NATIVES,
	AMX_TABLE_LIBRARIES,
	AMX_TABLE_PUBVARS,
	AMX_TABLE_TAGS
}

#if cellbits == 64
	#define __32(%0) ((%0)&0xFFFFFFFF)
#else
	#define __32(%0) (%0)
#endif

// This is based on the AMX version used in SA:MP - it DOES NOT match the code
// found in the PAWN documentation as that's for a later version.
public OnCodeInit()
{
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

static AMX_DoNothing()
{
	return 0;
}

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

#define AMX_GetPublicEntry( AMX_GetEntryBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeEntry( AMX_GetEntryLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryEntry( AMX_GetEntryLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntry( AMX_GetEntryBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntry( AMX_GetEntryLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarEntry`
stock AMX_GetPubvarEntry(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetEntryBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

stock AMX_GetEntryBinary(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetEntry called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
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
					Debug_Code7{AMX_ReadString(addr, str);}
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
					AMX_ReadString(addr, str);
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
				AMX_ReadString(addr, str);
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

stock AMX_GetEntryLinear(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetEntry called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		base = 0,
		count = 0;
	AMX_GetBaseCount(table, base, count);
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
			AMX_ReadString(addr, str);
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

#define AMX_GetPublicEntryPrefix( AMX_GetEntryPrefixBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeEntryPrefix( AMX_GetEntryPrefixLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryEntryPrefix( AMX_GetEntryPrefixLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntryPrefix( AMX_GetEntryPrefixBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntryPrefix( AMX_GetEntryPrefixLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarEntryPrefix`
stock AMX_GetPubvarEntryPrefix(idx, &buffer, pattern)
{
	return AMX_GetEntryPrefixBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetEntryPrefixBinary(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetEntryPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
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

stock AMX_GetEntryPrefixLinear(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetEntryPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base = 0,
		count = 0,
		addr = 0,
		pos;
	AMX_GetBaseCount(table, base, count);
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

#define AMX_GetPublicEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_PUBLICS,
#define AMX_GetNativeEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_NATIVES,
#define AMX_GetLibraryEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagEntrySuffix( AMX_GetEntrySuffix(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarEntrySuffix`
stock AMX_GetPubvarEntrySuffix(idx, &buffer, pattern)
{
	return AMX_GetEntrySuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetEntrySuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetEntrySuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base = 0,
		count = 0,
		addr = 0,
		ch = 0;
	AMX_GetBaseCount(table, base, count);
	for (new pos = idx * __defsize_cells + base + cellbytes; idx < count; pos += __defsize_cells)
	{
		++idx;
		// Get the address of the string.
		#emit LREF.S.pri                pos
		#emit CONST.alt                 0xFFFFFFFF
		#emit AND
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                addr
		//addr = __32(addr);
		if (addr == AMX_BASE_ADDRESS)
		{
			continue;
		}
		for ( ; ; )
		{
			// Find the end of the string.
			ch = AMX_Read(addr);
			if (ch & 0x000000FF)
			{
				if (ch & 0x0000FF00)
				{
					if (ch & 0x00FF0000)
					{
						if (ch & 0xFF000000)
						{
							addr += 4;
							continue;
						}
						else addr -= 1;
					}
					else addr -= 2;
				}
				else addr -= 3;
			}
			else addr -= 4;
			break;
		}
		if (AMX_Read(addr) == pattern)
		{
			buffer = pos - cellbytes;
			return idx;
		}
	}
	return 0;
}

#define AMX_GetPublicName( AMX_GetNameBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeName( AMX_GetNameLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryName( AMX_GetNameLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarName( AMX_GetNameBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagName( AMX_GetNameLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarName`
stock AMX_GetPubvarName(idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	return AMX_GetNameBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

stock AMX_GetNameBinary(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetName called: %i, %i, \"%s\", \"%s\"", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryBinary(table, idx, pointer, pattern, exact);
	if (idx)
	{
		AMX_ReadString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

stock AMX_GetNameLinear(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetName called: %i, %i, \"%s\", \"%s\"", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryLinear(table, idx, pointer, pattern, exact);
	if (idx)
	{
		AMX_ReadString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

#define AMX_GetPublicNamePrefix( AMX_GetNamePrefixBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeNamePrefix( AMX_GetNamePrefixLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryNamePrefix( AMX_GetNamePrefixLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarNamePrefix( AMX_GetNamePrefixBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagNamePrefix( AMX_GetNamePrefixLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarNamePrefix`
stock AMX_GetPubvarNamePrefix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	return AMX_GetNamePrefixBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetNamePrefixBinary(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNamePrefix called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefixBinary(table, idx, pointer, pattern);
	if (idx)
	{
		AMX_ReadString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

stock AMX_GetNamePrefixLinear(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNamePrefix called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefixLinear(table, idx, pointer, pattern);
	if (idx)
	{
		AMX_ReadString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

#define AMX_GetPublicNameSuffix( AMX_GetNameSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetNativeNameSuffix( AMX_GetNameSuffix(AMX_TABLE_NATIVES,
#define AMX_GetLibraryNameSuffix( AMX_GetNameSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarNameSuffix( AMX_GetNameSuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagNameSuffix( AMX_GetNameSuffix(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarNameSuffix`
stock AMX_GetPubvarNameSuffix(idx, buffer[FUNCTION_LENGTH], pattern)
{
	return AMX_GetNameSuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetNameSuffix(E_AMX_TABLE:table, idx, buffer[FUNCTION_LENGTH], pattern)
{
	Debug_Print7("AMX_GetNameSuffix called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntrySuffix(table, idx, pointer, pattern);
	if (idx)
	{
		AMX_ReadString(__32(AMX_Read(pointer + cellbytes)) + AMX_BASE_ADDRESS, buffer);
	}
	return idx;
}

#define AMX_GetPublicPointer( AMX_GetPointerBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativePointer( AMX_GetPointerLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryPointer( AMX_GetPointerLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointer( AMX_GetPointerBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointer( AMX_GetPointerLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarPointer`
stock AMX_GetPubvarPointer(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetPointerBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

stock AMX_GetPointerBinary(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetPointer called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetEntryBinary(table, idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_GetPointerLinear(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetPointer called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetEntryLinear(table, idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicPointerPrefix( AMX_GetPointerPrefixBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativePointerPrefix( AMX_GetPointerPrefixLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryPointerPrefix( AMX_GetPointerPrefixLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointerPrefix( AMX_GetPointerPrefixBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointerPrefix( AMX_GetPointerPrefixLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarPointerPrefix`
stock AMX_GetPubvarPointerPrefix(idx, &buffer, pattern)
{
	return AMX_GetPointerPrefixBinary(E_AMX_TABLE:table, idx, buffer, pattern);
}

stock AMX_GetPointerPrefixBinary(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPointerPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefixBinary(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_GetPointerPrefixLinear(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetPointerPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetEntryPrefixLinear(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetNativePointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_NATIVES,
#define AMX_GetLibraryPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagPointerSuffix( AMX_GetPointerSuffix(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarPointerSuffix`
stock AMX_GetPubvarPointerSuffix(idx, &buffer, pattern)
{
	return AMX_GetPointerSuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

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

#define AMX_GetPublicValue( AMX_GetValueBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeValue( AMX_GetValueLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryValue( AMX_GetValueLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarValue( AMX_GetValueBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagValue( AMX_GetValueLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarValue`
stock AMX_GetPubvarValue(idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	return AMX_GetValueBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern, exact);
}

stock AMX_GetValueBinary(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetValue called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetPointerBinary(table, idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_GetValueLinear(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "", const bool:exact = false)
{
	Debug_Print7("AMX_GetValue called: %i, %i, %i, \"%s\", %i", _:table, idx, buffer, pattern, exact);
	new
		pointer = 0;
	idx = AMX_GetPointerLinear(table, idx, pointer, pattern, exact);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicValuePrefix( AMX_GetValuePrefixBinary(AMX_TABLE_PUBLICS,
#define AMX_GetNativeValuePrefix( AMX_GetValuePrefixLinear(AMX_TABLE_NATIVES,
#define AMX_GetLibraryValuePrefix( AMX_GetValuePrefixLinear(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarValuePrefix( AMX_GetValuePrefixBinary(AMX_TABLE_PUBVARS,
#define AMX_GetTagValuePrefix( AMX_GetValuePrefixLinear(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarValuePrefix`
stock AMX_GetPubvarValuePrefix(idx, &buffer, pattern)
{
	return AMX_GetValuePrefixBinary(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetValuePrefixBinary(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetValuePrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetPointerPrefixBinary(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_GetValuePrefixLinear(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetValuePrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetPointerPrefixLinear(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicValueSuffix( AMX_GetValueSuffix(AMX_TABLE_PUBLICS,
#define AMX_GetNativeValueSuffix( AMX_GetValueSuffix(AMX_TABLE_NATIVES,
#define AMX_GetLibraryValueSuffix( AMX_GetValueSuffix(AMX_TABLE_LIBRARIES,
#define AMX_GetPubVarValueSuffix( AMX_GetValueSuffix(AMX_TABLE_PUBVARS,
#define AMX_GetTagValueSuffix( AMX_GetValueSuffix(AMX_TABLE_TAGS,

#pragma deprecated Use `AMX_GetPubVarValueSuffix`
stock AMX_GetPubvarValueSuffix(idx, &buffer, pattern)
{
	return AMX_GetValueSuffix(AMX_TABLE_PUBVARS, idx, buffer, pattern);
}

stock AMX_GetValueSuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	Debug_Print7("AMX_GetValueSuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer = 0;
	idx = AMX_GetPointerSuffix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_GetEntryPointer(tableEntry)
{
	#emit LREF.S.pri tableEntry
	#emit RETN
	__pragma("naked");
}

stock AMX_GetEntryFromNativeIndex(index)
{
	return index * __defsize_cells + AMX_HEADER_NATIVES;
}

stock AMX_GetEntryFromPublicIndex(index)
{
	// An index is an offset in to their own table.
	return index * __defsize_cells + AMX_HEADER_PUBLICS;
}

stock AMX_GetNativeIndexFromEntry(tableEntry) 
{
	return (tableEntry - AMX_HEADER_NATIVES) / __defsize_cells;
}

stock AMX_GetPublicIndexFromEntry(tableEntry)
{
	return (tableEntry - AMX_HEADER_PUBLICS) / __defsize_cells;
}

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

stock AMX_GetStringFromEntry(tableEntry, str[], size = sizeof (str))
{
	AMX_ReadString(__32(AMX_Read(tableEntry + cellbytes)) + AMX_BASE_ADDRESS, str, size);
}

stock AMX_ReadString(addr, str[], len = sizeof (str))
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

stock AMX_ReadUnpackedString(addr, str[], len = sizeof (str))
{
	new
		buffer = 1;
	while (buffer && len--);
	{
		// Read 4 bytes.
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                buffer
		#emit SREF.S.pri                str
		#emit LOAD.S.pri                str
		#emit ADD.C                     __1_cell
		#emit STOR.S.pri                str
		addr += cellbytes;
	}
}

stock AMX_WriteString(addr, const str[], len = sizeof (str))
{
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
	do
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
	while (++idx < len);
}

stock AMX_ReadArray(addr, dest[], len = sizeof (dest))
{
	// I tried to use memcpy, I couldn't get it to work, even when exactly
	// replicating compiler generated code...
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

stock AMX_Deref(addr)
{
	Debug_Print7("AMX_Deref called: %i", addr);
	#emit LOAD.S.pri                    addr
	#emit STOR.S.pri                    __4_cells
	#emit RETN
	new ret[2];
	return ret;
}

stock AMX_GetTagByValue(tag, name[], len = sizeof (name))
{
	new
		idx,
		buffer,
		value;
	while ((idx = AMX_GetEntryLinear(AMX_TABLE_TAGS, idx, buffer)))
	{
		#emit LREF.S.pri buffer
		#emit STOR.S.pri value
		// Ignore the top two bits - they're flags we don't need.
		if (value & 0x3FFFFFFF == tag & 0x3FFFFFFF)
		{
			// Found the tag, get the name.
			AMX_ReadString(__32(AMX_Read(buffer + cellbytes)) + AMX_BASE_ADDRESS, name, len);
			strunpack(name, name, len);
		}
	}
}

//stock AMX_CodToDat(ptr)
//{
//	// Convert a pointer in to the code segment in to a data offset.
//	return ptr + AMX_HEADER_COD;
//}

#define AMX_CodToDat(%0) ((%0) + AMX_HEADER_COD)
#define AMX_DatToCod(%0) ((%0) - AMX_HEADER_COD)

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

// Function call versions of `AMX_Read` and `AMX_Write`.
stock AMX_Write(addr, value)
{
	Debug_Print7("AMX_Write called: %i, %i", addr, value);
	#emit LOAD.S.pri                    value
	#emit SREF.S.pri                    addr
}

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

