/*----------------------------------------------------------------------------*\
					===============================
					 y_scripting - Access amx data
					===============================
Description:
	Allows a script access to information about itself, such as function names.
	This can be used for a range of things, including automatic callback hooking
	and testing.
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
	
	The Original Code is the YSI AMX include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	1.0
Changelog:
	06/08/10:
		First version
\*----------------------------------------------------------------------------*/

#include "internal\y_version"

#include "y_scriptinit"
//#include "internal\y_funcinc"
#include "y_debug"
#include "internal\y_natives"

#define AMX_FastString(%1,%2,%3,%4) \
	(((%1) << 0) | ((%2) << 8) | ((%3) << 16) | ((%4) << 24))

#define AMX_MEMORY_TRACE_0 0xAABBCCDD
#define AMX_MEMORY_TRACE_1 0xDDCCBBAA
#define AMX_MEMORY_TRACE_2 0x12345678
#define AMX_MEMORY_TRACE_3 0x87654321

stock
	AMX_HEADER_SIZE,
	AMX_HEADER_MAGIC,
	AMX_HEADER_FILE_VERSION,
	AMX_HEADER_AMX_VERSION,
	AMX_HEADER_FLAGS,
	AMX_HEADER_DEFSIZE,
	// These are not as they appear in the AMX - they are relative to the dat
	// pointer so that they can be directly manipulated.
	AMX_HEADER_COD,
	AMX_HEADER_DAT,
	AMX_HEADER_HEA,
	AMX_HEADER_STP,
	AMX_HEADER_CIP,
	AMX_HEADER_PUBLICS,
	AMX_HEADER_NATIVES,
	AMX_HEADER_LIBRARIES,
	AMX_HEADER_PUBVARS,
	AMX_HEADER_TAGS,
	AMX_HEADER_NAMETABLE,
	//E_AMX_HEADER_OVERLAYS,
	AMX_REAL_ADDRESS,
	AMX_BASE_ADDRESS,
	AMX_REAL_DATA;

enum E_AMX_TABLE
{
	AMX_TABLE_PUBLICS,
	AMX_TABLE_NATIVES,
	AMX_TABLE_LIBRARIES,
	AMX_TABLE_PUBVARS,
	AMX_TABLE_TAGS
}

// This is based on the AMX version used in SA:MP - it DOES NOT match the code
// found in the PAWN documentation as that's for a later version.
#define AMX_NOP                         000
#define AMX_LOAD_PRI                    001
#define AMX_LOAD_ALT                    002
#define AMX_PUSH_C                      039
#define AMX_CALL                        049
#define AMX_STACK                       044
#define AMX_PUSH_PRI                    036
#define AMX_CONST_PRI                   011

forward _@_y_amx_inc_@_();
public _@_y_amx_inc_@_()
{
	// This function call is VERY important - it exists but it never used, so
	// can be found in memory, and it also appears in code before the constant
	// offset is ever used in #emit code.
	AMX_TraceFunc(AMX_MEMORY_TRACE_0, AMX_MEMORY_TRACE_1, AMX_MEMORY_TRACE_2, AMX_MEMORY_TRACE_3);
}

static stock AMX_TraceFunc(b0, b1, b2, b3)
{
	// This function is only called to anchor the AMX in memory.
	#pragma unused b0, b1, b2, b3
	return 0;
}

public OnScriptInit()
{
	new
		addr,
		data,
		dat;
	#emit LCTRL                     1
	#emit STOR.S.pri                addr
	// Invert to get the prefix offset relative to the data.
	// Get all the script data.
	addr = -addr;
	// Now read in all the data.
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_SIZE         = data;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_MAGIC        = data & 0xFFFF;
	AMX_HEADER_FILE_VERSION = data >>> 16 & 0xFF;
	AMX_HEADER_AMX_VERSION  = data >>> 24;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_FLAGS        = data & 0xFFFF;
	AMX_HEADER_DEFSIZE      = data >>> 16;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_COD          = data;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	dat = data;
	AMX_HEADER_DAT          = 0;
	AMX_BASE_ADDRESS = -dat;
	AMX_HEADER_COD -= dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_HEA          = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_STP          = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_CIP          = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_PUBLICS      = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_NATIVES      = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_LIBRARIES    = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_PUBVARS      = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_TAGS         = data - dat;
	addr += 4;
	#emit LREF.S.pri                addr
	#emit STOR.S.pri                data
	AMX_HEADER_NAMETABLE    = data - dat;
	// Now find the AMX's base address in global memory.  This is VERY handy to
	// have for more advanced functionality (none of which actually exists yet).
	/*addr = 0;
	data = 0;
	new
		func;
	static
		sSearch[] =
			{
				AMX_PUSH_C, AMX_MEMORY_TRACE_3,
				AMX_PUSH_C, AMX_MEMORY_TRACE_2,
				AMX_PUSH_C, AMX_MEMORY_TRACE_1,
				AMX_PUSH_C, AMX_MEMORY_TRACE_0,
				AMX_PUSH_C, 0x10,
				AMX_CALL
			};
	#emit CONST.pri           AMX_TraceFunc
	#emit STOR.S.pri          func
	if (AMX_TraceCode(sSearch, addr, data))
	{
		AMX_REAL_ADDRESS = data - func - (AMX_HEADER_COD - AMX_BASE_ADDRESS);
		addr += 4;
		if (AMX_TraceCode(sSearch, addr, data))
		{
			P:E("Multiple y_amx tracers found!");
		}
	}
	else
	{
		P:E("y_amx tracer not found!");
	}*/
	AMX_REAL_ADDRESS = AMX_GetGlobal();
	AMX_REAL_DATA = AMX_REAL_ADDRESS - AMX_BASE_ADDRESS;
	// Call next ALS callback.
	#if defined YSI_LOCK_MODE
		GetServerVarAsString(YSI_gLockData, YSI_gLockData[5], sizeof (YSI_gLockData) - 5);
	#endif
	return AMX_OnScriptInit();
}

#undef OnScriptInit
#define OnScriptInit(%0) AMX_OnScriptInit(%0) <_ALS_:hooked>
forward AMX_OnScriptInit();public AMX_OnScriptInit()<_ALS_:unhooked>{return 1;}public AMX_OnScriptInit()<>{return 1;}

stock AMX_GetGlobalAddress(...)
{
	new
		addr;
	// addr = numargs();
	#emit LOAD.S.pri 8
	#emit STOR.S.pri addr
	if (addr >= 4)
	{
		// getargptr(0);
		#emit LOAD.S.pri 12
		#emit LOAD.alt   AMX_REAL_DATA
		#emit ADD
		#emit STACK 4
		#emit RETN
	}
	return 0;
}

stock AMX_GetRelativeAddress(...)
{
	new
		addr;
	// addr = numargs();
	#emit LOAD.S.pri 8
	#emit STOR.S.pri addr
	if (addr >= 4)
	{
		// getargptr(0);
		#emit LOAD.S.pri 12
		#emit STACK 4
		#emit RETN
	}
	return 0;
}

static AMX_GetGlobal()
{
	new
		addr = -1;
	// Get the return address.
	#emit LOAD.S.pri 4
	#emit ADD.C      0xFFFFFFFC
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri addr
	// Get the data 4 bytes before the return address.
	#emit LREF.S.alt addr
	#emit CONST.pri  AMX_GetGlobal
	#emit SUB.alt
	#emit LOAD.alt   AMX_HEADER_COD
	#emit SUB
	#emit LOAD.alt   AMX_BASE_ADDRESS
	#emit ADD
	// Return
	#emit STACK 4
	#emit RETN
	// Find base address, not cod address (both operands relative to DAT.
	return 0;
}

stock AMX_TraceCode(pattern[], &addrRet, &dataRet, size = sizeof (pattern))
{
	new
		addr = AMX_HEADER_COD + addrRet,
		data,
		i;
	while (addr < AMX_HEADER_DAT)
	{
		#emit LREF.S.pri      addr
		#emit STOR.S.pri      data
		if (data == pattern[i])
		{
			++i;
			addr += 4;
			if (i == size)
			{
				addrRet = addr - i * 4 - AMX_HEADER_COD;
				#emit LREF.S.pri      addr
				#emit STOR.S.pri      data
				dataRet = data;
				return 1;
			}
		}
		else if (i)
		{
			addr -= i * 4 - 4;
			i = 0;
		}
		else
		{
			addr += 4;
		}
	}
	return 0;
}

stock AMX_TraceMemory(pattern[], &addrRet, &dataRet, size = sizeof (pattern))
{
	new
		addr = AMX_HEADER_DAT + addrRet,
		data,
		i;
	while (addr < AMX_HEADER_HEA)
	{
		#emit LREF.S.pri      addr
		#emit STOR.S.pri      data
		if (data == pattern[i])
		{
			++i;
			addr += 4;
			if (i == size)
			{
				addrRet = addr - i * 4 - AMX_HEADER_DAT;
				#emit LREF.S.pri      addr
				#emit STOR.S.pri      data
				dataRet = data;
				return 1;
			}
		}
		else if (i)
		{
			addr -= i * 4 - 4;
			i = 0;
		}
		else
		{
			addr += 4;
		}
	}
	return 0;
}

stock AMX_GetBaseCount(E_AMX_TABLE:table, &base, &count)
{
	P:5("AMX_GetBaseCount called: %i, %i, %i", _:table, base, count);
	switch (table)
	{
		case AMX_TABLE_PUBLICS:
		{
			base = AMX_HEADER_PUBLICS;
			count = (AMX_HEADER_NATIVES - base) / 8;
		}
		case AMX_TABLE_NATIVES:
		{
			base = AMX_HEADER_NATIVES;
			count = (AMX_HEADER_LIBRARIES - base) / 8;
		}
		case AMX_TABLE_LIBRARIES:
		{
			base = AMX_HEADER_LIBRARIES;
			count = (AMX_HEADER_PUBVARS - base) / 8;
		}
		case AMX_TABLE_PUBVARS:
		{
			base = AMX_HEADER_PUBVARS;
			count = (AMX_HEADER_TAGS - base) / 8;
		}
		case AMX_TABLE_TAGS:
		{
			base = AMX_HEADER_TAGS;
			count = (AMX_HEADER_NAMETABLE - base) / 8;
		}
		default:
		{
			base = 0;
			count = 0;
		}
	}
}

#define AMX_GetPublicEntry(%0) AMX_GetEntry(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeEntry(%0) AMX_GetEntry(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryEntry(%0) AMX_GetEntry(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarEntry(%0) AMX_GetEntry(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagEntry(%0) AMX_GetEntry(AMX_TABLE_TAGS,%0)

stock AMX_GetEntry(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "")
{
	P:5("AMX_GetEntry called: %i, %i, %i, \"%s\"", _:table, idx, buffer, pattern);
	new
		base,
		count;
	if (table == AMX_TABLE_PUBLICS && idx == 0)
	{
		// Special case where we can use native functions.
		idx = funcidx(pattern);
		if (idx == -1)
		{
			idx = 0;
		}
		else
		{
			buffer = idx * 8 + AMX_HEADER_PUBLICS;
			return idx + 1;
		}
	}
	AMX_GetBaseCount(table, base, count);
	if (idx < count)
	{
		if (pattern[0] == '\0')
		{
			buffer = idx * 8 + base;
			return idx + 1;
		}
		else
		{
			new
				addr,
				pos = idx * 8 + base + 4,
				str[32];
			do
			{
				#emit LREF.S.pri pos
				#emit STOR.S.pri addr
				AMX_ReadString(AMX_BASE_ADDRESS + addr, str);
				++idx;
				if (strfind(str, pattern) != -1)
				{
					buffer = pos - 4;
					return idx;
				}
				pos += 8;
			}
			while (idx < count);
		}
	}
	return 0;
}

#define AMX_GetPublicEntryPrefix(%0) AMX_GetEntryPrefix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeEntryPrefix(%0) AMX_GetEntryPrefix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryEntryPrefix(%0) AMX_GetEntryPrefix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarEntryPrefix(%0) AMX_GetEntryPrefix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagEntryPrefix(%0) AMX_GetEntryPrefix(AMX_TABLE_TAGS,%0)

stock AMX_GetEntryPrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetEntryPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base,
		count;
	AMX_GetBaseCount(table, base, count);
	if (idx < count)
	{
		new
			addr,
			pos = idx * 8 + base + 4;
		do
		{
			// Get the address of the string.
			#emit LREF.S.pri                pos
			#emit STOR.S.pri                addr
			// Get the 4 bytes 5 bytes before this position.
			addr += AMX_BASE_ADDRESS;
			#emit LREF.S.pri                addr
			#emit STOR.S.pri                addr
			++idx;
			if (addr == pattern)
			{
				buffer = pos - 4;
				return idx;
			}
			pos += 8;
		}
		while (idx < count);
	}
	return 0;
}

#define AMX_GetPublicEntrySuffix(%0) AMX_GetEntrySuffix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeEntrySuffix(%0) AMX_GetEntrySuffix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryEntrySuffix(%0) AMX_GetEntrySuffix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarEntrySuffix(%0) AMX_GetEntrySuffix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagEntrySuffix(%0) AMX_GetEntrySuffix(AMX_TABLE_TAGS,%0)

stock AMX_GetEntrySuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetEntrySuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		base,
		count;
	AMX_GetBaseCount(table, base, count);
	if (idx < --count)
	{
		new
			addr,
			pos = idx * 8 + base + 12;
		do
		{
			// Get the address of the string.
			#emit LREF.S.pri                pos
			#emit STOR.S.pri                addr
			// Get the 4 bytes 5 bytes before this position.
			addr += AMX_BASE_ADDRESS - 5;
			#emit LREF.S.pri                addr
			#emit STOR.S.pri                addr
			++idx;
			if (addr == pattern)
			{
				buffer = pos - 12;
				return idx;
			}
			pos += 8;
		}
		while (idx < count);
	}
	if (idx == count)
	{
		// Do the final one, this is more of an issue!
		new
			addr,
			ch,
			pos = idx * 8 + base + 4;
		// Get the address of the string.
		#emit LREF.S.pri                pos
		#emit STOR.S.pri                addr
		addr += AMX_BASE_ADDRESS;
		for ( ; ; )
		{
			// Find the end of the string.
			#emit LREF.S.pri            addr
			#emit STOR.S.pri            ch
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
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                ch
		++idx;
		if (ch == pattern)
		{
			buffer = pos - 4;
			return idx;
		}
	}
	return 0;
}

#define AMX_GetPublicName(%0) AMX_GetName(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeName(%0) AMX_GetName(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryName(%0) AMX_GetName(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarName(%0) AMX_GetName(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagName(%0) AMX_GetName(AMX_TABLE_TAGS,%0)

stock AMX_GetName(E_AMX_TABLE:table, idx, buffer[32], const pattern[] = "")
{
	P:5("AMX_GetName called: %i, %i, \"%s\", \"%s\"", _:table, idx, buffer, pattern);
	new
		base,
		count;
	AMX_GetBaseCount(table, base, count);
	if (idx < count)
	{
		if (pattern[0] == '\0')
		{
			new
				addr,
				pos = idx * 8 + base + 4;
			#emit LREF.S.pri pos
			#emit STOR.S.pri addr
			AMX_ReadString(AMX_BASE_ADDRESS + addr, buffer);
			++idx;
			//buffer = idx * 8 + base;
			return idx;
		}
		else
		{
			new
				addr,
				pos = idx * 8 + base + 4;
			do
			{
				#emit LREF.S.pri pos
				#emit STOR.S.pri addr
				AMX_ReadString(AMX_BASE_ADDRESS + addr, buffer);
				++idx;
				if (strfind(buffer, pattern) != -1)
				{
					//buffer = idx * 8 + base;
					return idx;
				}
				pos += 8;
			}
			while (idx < count);
		}
	}
	return 0;
}

#define AMX_GetPublicNamePrefix(%0) AMX_GetNamePrefix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeNamePrefix(%0) AMX_GetNamePrefix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryNamePrefix(%0) AMX_GetNamePrefix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarNamePrefix(%0) AMX_GetNamePrefix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagNamePrefix(%0) AMX_GetNamePrefix(AMX_TABLE_TAGS,%0)

stock AMX_GetNamePrefix(E_AMX_TABLE:table, idx, buffer[32], pattern)
{
	P:5("AMX_GetNamePrefix called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		base,
		count;
	AMX_GetBaseCount(table, base, count);
	if (idx < count)
	{
		new
			addr,
			pos = idx * 8 + base + 4;
		do
		{
			// Get the address of the string.
			#emit LREF.S.pri                pos
			#emit STOR.S.pri                addr
			// Get the 4 bytes 5 bytes before this position.
			addr += AMX_BASE_ADDRESS;
			#emit LREF.S.pri                addr
			#emit STOR.S.pri                addr
			++idx;
			if (addr == pattern)
			{
				#emit LREF.S.pri            pos
				#emit STOR.S.pri            addr
				AMX_ReadString(AMX_BASE_ADDRESS + addr, buffer);
				return idx;
			}
			pos += 8;
		}
		while (idx < count);
	}
	return 0;
}

#define AMX_GetPublicNameSuffix(%0) AMX_GetNameSuffix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeNameSuffix(%0) AMX_GetNameSuffix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryNameSuffix(%0) AMX_GetNameSuffix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarNameSuffix(%0) AMX_GetNameSuffix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagNameSuffix(%0) AMX_GetNameSuffix(AMX_TABLE_TAGS,%0)

stock AMX_GetNameSuffix(E_AMX_TABLE:table, idx, buffer[32], pattern)
{
	P:5("AMX_GetNameSuffix called: %i, %i, \"%s\", %i", _:table, idx, buffer, pattern);
	new
		base,
		count;
	AMX_GetBaseCount(table, base, count);
	if (idx < --count)
	{
		new
			addr,
			pos = idx * 8 + base + 12;
		do
		{
			// Get the address of the string.
			#emit LREF.S.pri                pos
			#emit STOR.S.pri                addr
			// Get the 4 bytes 5 bytes before this position.
			addr += AMX_BASE_ADDRESS - 5;
			#emit LREF.S.pri                addr
			#emit STOR.S.pri                addr
			++idx;
			if (addr == pattern)
			{
				//buffer = pos - 12;
				pos -= 8;
				#emit LREF.S.pri            pos
				#emit STOR.S.pri            addr
				//addr += AMX_BASE_ADDRESS;
				AMX_ReadString(AMX_BASE_ADDRESS + addr, buffer);
				return idx;
			}
			pos += 8;
		}
		while (idx < count);
	}
	if (idx == count)
	{
		// Do the final one, this is more of an issue!
		new
			addr,
			ch,
			pos = idx * 8 + base + 4;
		// Get the address of the string.
		#emit LREF.S.pri                pos
		#emit STOR.S.pri                addr
		addr += AMX_BASE_ADDRESS;
		for ( ; ; )
		{
			// Find the end of the string.
			#emit LREF.S.pri            addr
			#emit STOR.S.pri            ch
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
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                ch
		++idx;
		if (ch == pattern)
		{
			#emit LREF.S.pri            pos
			#emit STOR.S.pri            addr
			AMX_ReadString(AMX_BASE_ADDRESS + addr, buffer);
			return idx;
		}
	}
	return 0;
}

#define AMX_GetPublicPointer(%0) AMX_GetPointer(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativePointer(%0) AMX_GetPointer(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryPointer(%0) AMX_GetPointer(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarPointer(%0) AMX_GetPointer(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagPointer(%0) AMX_GetPointer(AMX_TABLE_TAGS,%0)

stock AMX_GetPointer(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "")
{
	P:5("AMX_GetPointer called: %i, %i, %i, \"%s\"", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetEntry(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicPointerPrefix(%0) AMX_GetPointerPrefix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativePointerPrefix(%0) AMX_GetPointerPrefix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryPointerPrefix(%0) AMX_GetPointerPrefix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarPointerPrefix(%0) AMX_GetPointerPrefix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagPointerPrefix(%0) AMX_GetPointerPrefix(AMX_TABLE_TAGS,%0)

stock AMX_GetPointerPrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetPointerPrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetEntryPrefix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicPointerSuffix(%0) AMX_GetPointerSuffix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativePointerSuffix(%0) AMX_GetPointerSuffix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryPointerSuffix(%0) AMX_GetPointerSuffix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarPointerSuffix(%0) AMX_GetPointerSuffix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagPointerSuffix(%0) AMX_GetPointerSuffix(AMX_TABLE_TAGS,%0)

stock AMX_GetPointerSuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetPointerSuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetEntrySuffix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicValue(%0) AMX_GetValue(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeValue(%0) AMX_GetValue(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryValue(%0) AMX_GetValue(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarValue(%0) AMX_GetValue(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagValue(%0) AMX_GetValue(AMX_TABLE_TAGS,%0)

stock AMX_GetValue(E_AMX_TABLE:table, idx, &buffer, const pattern[] = "")
{
	P:5("AMX_GetValue called: %i, %i, %i, \"%s\"", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetPointer(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicValuePrefix(%0) AMX_GetValuePrefix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeValuePrefix(%0) AMX_GetValuePrefix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryValuePrefix(%0) AMX_GetValuePrefix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarValuePrefix(%0) AMX_GetValuePrefix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagValuePrefix(%0) AMX_GetValuePrefix(AMX_TABLE_TAGS,%0)

stock AMX_GetValuePrefix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetValuePrefix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetPointerPrefix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

#define AMX_GetPublicValueSuffix(%0) AMX_GetValueSuffix(AMX_TABLE_PUBLICS,%0)
#define AMX_GetNativeValueSuffix(%0) AMX_GetValueSuffix(AMX_TABLE_NATIVES,%0)
#define AMX_GetLibraryValueSuffix(%0) AMX_GetValueSuffix(AMX_TABLE_LIBRARIES,%0)
#define AMX_GetPubvarValueSuffix(%0) AMX_GetValueSuffix(AMX_TABLE_PUBVARS,%0)
#define AMX_GetTagValueSuffix(%0) AMX_GetValueSuffix(AMX_TABLE_TAGS,%0)

stock AMX_GetValueSuffix(E_AMX_TABLE:table, idx, &buffer, pattern)
{
	P:5("AMX_GetValueSuffix called: %i, %i, %i, %i", _:table, idx, buffer, pattern);
	new
		pointer;
	idx = AMX_GetPointerSuffix(table, idx, pointer, pattern);
	if (idx)
	{
		#emit LREF.S.pri pointer
		#emit SREF.S.pri buffer
	}
	return idx;
}

stock AMX_ReadString(addr, str[], len = sizeof (str))
{
	new
		buffer,
		idx;
	do
	{
		// Read 4 bytes.
		#emit LREF.S.pri                addr
		#emit STOR.S.pri                buffer
		// Write PACKED strings.
		buffer = (buffer >>> 24) | (buffer >> 8 & 0x0000FF00) | (buffer << 8 & 0x00FF0000) | (buffer << 24);
		str[idx] = buffer;
		if (!(buffer & 0x000000FF && buffer & 0x0000FF00 && buffer & 0x00FF0000 && buffer & 0xFF000000))
		{
			return;
		}
		addr += 4;
	}
	while (++idx < len);
}

stock AMX_WriteString(addr, const str[], len = sizeof (str))
{
	new
		buffer,
		idx;
	do
	{
		// Write PACKED strings.
		buffer = str[idx];
		buffer = (buffer >>> 24) | (buffer >> 8 & 0x0000FF00) | (buffer << 8 & 0x00FF0000) | (buffer << 24);
		// Write 4 bytes.
		#emit LOAD.S.pri                buffer
		#emit SREF.S.pri                addr
		if (!(buffer & 0x000000FF && buffer & 0x0000FF00 && buffer & 0x00FF0000 && buffer & 0xFF000000))
		{
			return;
		}
		addr += 4;
	}
	while (++idx < len);
}

stock AMX_Read(addr)
{
	P:5("AMX_Read called: %i", addr);
	/*new
		ret;
	#emit LREF.S.pri                    addr
	#emit STOR.S.pri                    ret
	return ret;*/
	#emit LREF.S.pri                    addr
	#emit RETN
	return 0;
	// It's a shame about the compiler here - this should be a 1 line function:
	//  
	//  #emit LREF.S.pri addr
	//  
	// pri is the return value of a function so the data will already be in the
	// correct place, but the compiler will detect the lack of a return call.
	// Now fixed!
}

stock AMX_Write(addr, value)
{
	P:5("AMX_Write called: %i, %i", addr, value);
	#emit LOAD.S.pri                    value
	#emit SREF.S.pri                    addr
}

stock AMX_ReadArray(addr, dest[], len = sizeof (dest))
{
	// I tried to use memcpy, I couldn't get it to work, even when exactly
	// replicating compiler generated code...
	//while (len--)
	#emit LOAD.S.pri                    len
	#emit JZER                          AMX_ReadArray_done
	// if (len)
AMX_ReadArray_loop:
	{
		// --len
		#emit DEC.pri
		// Load the address possibly outside "dat".  Can't be done using only
		// "pri"/"alt" as it relies on "LREF.S" explicitly.
		#emit LREF.S.alt                addr
		#emit SREF.S.alt                dest
		#emit LOAD.S.alt                addr
		#emit ADD.C                     4
		#emit STOR.S.alt                addr
		#emit LOAD.S.alt                dest
		#emit ADD.C                     4
		#emit STOR.S.alt                dest
		// while (len != 0)
		#emit JNZ                       AMX_ReadArray_loop
	}
AMX_ReadArray_done:
	//	ret;
	/*while (len--)
	{
		#emit LREF.S.pri                    addr
		#emit SREF.S.pri                    dest
		#emit LOAD.S.pri                    addr
		#emit ADD.C                         4
		#emit STOR.S.pri                    addr
		#emit LOAD.S.pri                    dest
		#emit ADD.C                         4
		#emit STOR.S.pri                    dest
	}*/
	//	ret;
	//#emit LREF.S.pri                    addr
	//#emit STOR.S.pri                    ret
	//return ret;
	/*#emit push.adr len
	#emit push.adr dest
	#emit push.adr addr
	#emit push.c 0x175c
	#emit push.c 10
	#emit sysreq.c printf
	#emit stack 14
	//printf("1 %d %d %d", addr, dest, len);
	new src[32];

	printf("1 %d %d %d", addr, dest, len);
	#emit BREAK
	#emit PUSH.S                        len
	#emit LOAD.S.pri                    len
	#emit SMUL.C                        4
	#emit PUSH.pri
	#emit PUSH.C                        0
	#emit PUSH.adr                      src
	#emit PUSH.S                        dest
	#emit PUSH.C                        20
	#emit SYSREQ.C                      memcpy
	#emit STACK                         24*/
	//#emit LOAD.S.pri addr
	//#emit LOAD.S.alt dest
	//#emit
	// It's a shame about the compiler here - this should be a 1 line function:
	//  
	//  #emit LREF.S.pri addr
	//  
	// pri is the return value of a function so the data will already be in the
	// correct place, but the compiler will detect the lack of a return call.
	return;
}

stock AMX_WriteArray(addr, const src[], len = sizeof (src))
{
	#emit LOAD.S.pri                    len
	#emit JZER                          AMX_WriteArray_done
	// if (len)
AMX_WriteArray_loop:
	{
		// --len
		#emit DEC.pri
		// Read the data.
		#emit LREF.S.alt                dest
		#emit SREF.S.alt                addr
		#emit LOAD.S.alt                addr
		#emit ADD.C                     4
		#emit STOR.S.alt                addr
		#emit LOAD.S.alt                dest
		#emit ADD.C                     4
		#emit STOR.S.alt                dest
		// while (len != 0)
		#emit JNZ                       AMX_WriteArray_loop
	}
AMX_WriteArray_done:
	return;
}

/*#endinput

#define AMX_GetPublicsCount() ((AMX_HEADER_NATIVES-AMX_HEADER_PUBLICS)/8)

#define AMX_GetNativesCount() ((AMX_HEADER_NATIVES-AMX_HEADER_PUBLICS)/8)

#define AMX_GetPublicFast(%0) AMX_GetNamePrefix(AMX_PUBLICS,%0)

#define AMX_GetPublicSuffix(%0) AMX_GetNameSuffix(AMX_PUBLICS,%0)

#define AMX_GetPubvarSuffix(%0) AMX_GetNameSuffix(AMX_PUBVARS,%0)

#define AMX_GetNativeFast(%0) AMX_GetNamePrefix(AMX_NATIVES,%0)

#define AMX_GetPublic(%0) AMX_GetName(AMX_PUBLICS,%0)

#define AMX_GetNative(%0) AMX_GetName(AMX_NATIVES,%0)

stock AMX_GetPublicPointer(name[])
{
	P:5("AMX_GetPublicPointer called: \"%s\"", name);
	new
		p;
	AMX_GetPointer(AMX_PUBLICS, 0, p, name);
	return p;
}

//#define AMX_GetPointerSuffix(idx, &func, search)

#define AMX_RedirectPublic(name[], pointer)

#define AMX_GetPublicVariable(name[])

#define AMX_SetPublicVariable(name[], value)*/

//#define _A<%0> (_:H_Xe:H_Ye:H_Ze(%0))
#define _A<%0> (_:H_Re(%0,0))

//#define H_Xe:H_Ye:H_Ze(@y%0) (31040|(_:H_Re(%0,0+8+8)))
//#define H_Ye:H_Ze(_y%0) (31071|(_:H_Re(%0,0+8+8)))
//#define H_Ze(%0) H_Re(%0,0)

// Do the next character test as this one failed.
#define H_Se(%0,%1,%3) H_Ne%1(%0,%3)
// End of string test failed.
#define H_Ee(%0,%3)    @E_:H_Se(%0,_,%3)
// Do the single addition.
#define H_De(%0,%1,%3) (_:H_Re(%0,%3+8))|%1<<%3
// Recurse through the string.
#define H_Re(%0,%3)    he:H_Ee(%0,%3)
// Test for the end of a string (4 characters only).
#define he:H_Ee(%0,0+8+8+8+8)   0
// Find the length of a string at compile time.
//#define LEN(%0,%3) _:(H_R(%0,%3),%3)

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

// Find the next character to test.
#define H_Ne_(%0,%3) @E@:H_Se(%0,@,%3)
#define H_Ne@(%0,%3) @Ey:H_Se(%0,y,%3)
#define H_Ney(%0,%3) @Ea:H_Se(%0,a,%3)

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
#define H_Nez(%0,%3) @EA:H_Se(%0,A,%3)

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
#define H_NeZ(%0,%3) @E0:H_Se(%0,0,%3)

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
