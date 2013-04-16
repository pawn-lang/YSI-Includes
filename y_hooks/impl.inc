/**--------------------------------------------------------------------------**\
					==============================
					 y_hooks - Hook any callback!
					==============================
Description:
	Automatically hooks any callbacks with a very simple syntax.
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
	
	The Original Code is the SA:MP callback hooks include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		Peter, Cam - Support.
		ZeeX, g_aSlice/Slice, Popz, others - Very productive conversations.
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
	2.0
Changelog:
	15/04/13:
		Changed the assembly to be shorter by actually using the stack.
		Now slightly handles return values.
	14/04/13:
		Entirely new version - simpler, faster, and more generic.
	02/01/13:
		Rewrote the system to do away with ALS.
		Removed overflow checks in every callback.
		Streamlined code.
	14/04/12:
		Added crash fix from Slice, now returning correct values.
		Fixed ALS detection of mode callbacks.
	25/02/12:
		Extracted most of the code to a separate file.
	17/03/11:
		Second complete re-write using another new technique.  Now VERY fast!
		Updated OnPlayerUpdate code using Google63's SCTRL jump code.
	06/08/10:
		First version
\**--------------------------------------------------------------------------**/

#include "internal\y_unique"
#include "y_cell"
#include "y_utils"
#include "y_amx"
#include "y_als"

#tryinclude "..\amx\asm"
#include "amx\asm"

#define hook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2);UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define rehook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define Hook:%0_%1(%2) @yH_%1@%0(%2);@yH_%1@%0(%2)
// Strip out extra spaces (nicely recursive)
#define @yH_%0\32;%1(%2) @yH_%1(%2)

_Y_HOOKS_STATIC stock
	YSI_g_sCodeSpace,
	YSI_g_sCodeEnd;

/**--------------------------------------------------------------------------**\
<summary>_@_y_hooks_@_</summary>
<returns>
	-
</returns>
<remarks>
	Just makes space in the main code assembly area (so "RETN" will work without
	thinking that it is leaving valid code space).  This short function stores
	about 5k of memory.
</remarks>
\**--------------------------------------------------------------------------**/

forward _@_y_hooks_@_0();

public _@_y_hooks_@_0()
{
	//memcpy("", "", 0, 0, 0);
	// Reserve a huge area of "COD" for our own use!
	static
		STE[] = "";
	#define _CODE_1 SetTimerEx(STE,0,0,STE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	#define _CODE_2 _CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;
	// This reserves about 5kb of space in "COD"
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	/*
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	_CODE_2
	*/
	#undef _CODE_1
	#undef _CODE_2
}

forward _@_y_hooks_@_1();

public _@_y_hooks_@_1()
{
	// This function SHOULD come straight after "_@_y_hooks_@_0" in both the
	// public functions table and code segment if the compiler is true to form.
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_CountInvalidPublics</summary>
<returns>
	-
</returns>
<remarks>
	Counts the number of public functions that have had their names erased.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CountInvalidPublics()
{
	new
		idx,
		buf,
		count;
	// Search for functions whose names start with nothing.
	while ((idx = AMX_GetPublicEntryPrefix(idx, buf, 0)))
	{
		++count;
	}
	return count;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_CompareNextCell</summary>
<param name="addr0">The 1st address to read.</param>
<param name="addr1">The 2nd address to read.</param>
<returns>
	-1 - The first address is bigger.
	0  - The addresses are the same
	1  - The second address is bigger.
</returns>
<remarks>
	Reads two addresses, converts them to big endian, and compares them as four
	characters of a string at once.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CompareNextCell(addr0, addr1)
{
	new
		s0 = Cell_ReverseBytes(AMX_Read(addr0)),
		s1 = Cell_ReverseBytes(AMX_Read(addr1));
	// Propogate NULLs.
	if (!(s0 & 0xFF000000)) s0 = 0;
	else if (!(s0 & 0x00FF0000)) s0 &= 0xFF000000;
	else if (!(s0 & 0x0000FF00)) s0 &= 0xFFFF0000;
	if (!(s1 & 0xFF000000)) s1 = 0;
	else if (!(s1 & 0x00FF0000)) s1 &= 0xFF000000;
	else if (!(s1 & 0x0000FF00)) s1 &= 0xFFFF0000;
	// We need the numbers to be compared as big-endian.  Now any trailing NULLs
	// don't matter at all.
	if (s1 > s0) return 1;
	else if (s1 < s0) return -1;
	else return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_ComparePublics</summary>
<param name="idx0">The index of the 1st public.</param>
<param name="idx1">The index of the 2nd public.</param>
<returns>
	-
</returns>
<remarks>
	Compares two public function entries, and if need-be, swaps them over.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_ComparePublics(idx0, idx1)
{
	idx0 = idx0 * 8 + AMX_HEADER_PUBLICS;
	idx1 = idx1 * 8 + AMX_HEADER_PUBLICS;
	new
		addr0 = AMX_BASE_ADDRESS + AMX_Read(idx0 + 4),
		addr1 = AMX_BASE_ADDRESS + AMX_Read(idx1 + 4);
	for ( ; ; )
	{
		switch (Hooks_CompareNextCell(addr0, addr1))
		{
			case -1:
			{
				// Swap them over.
				new
					tmpFunc = AMX_Read(idx0),
					tmpName = AMX_Read(idx0 + 4);
				AMX_Write(idx0, AMX_Read(idx1));
				AMX_Write(idx0 + 4, AMX_Read(idx1 + 4));
				AMX_Write(idx1, tmpFunc);
				AMX_Write(idx1 + 4, tmpName);
				return;
			}
			case 1:
			{
				// Already in order - good.
				return;
			}
			// case 0: // Loop.
		}
		addr0 += 4;
		addr1 += 4;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_SortPublics</summary>
<returns>
	-
</returns>
<remarks>
	Goes through the whole of the public functions table and sorts them all in
	to alphabetical order.  This is done as we move and rename some so we need
	to fix the virtual machine's binary search.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_SortPublics()
{
	// Count the number of still active functions.
	new
		diff = Hooks_CountInvalidPublics() * 8,
		oldCount = (AMX_HEADER_NATIVES - AMX_HEADER_PUBLICS) / 8;
	// Now I need to SORT the functions, and I have honestly no idea how to do
	// that.  Fortunately I don't actually need to move the strings themselves
	// around as they just sit nicely in the nametable; I only need to sort the
	// pointers.
	for (new i = 0; i != oldCount; ++i)
	{
		for (new j = i + 1; j != oldCount; ++j)
		{
			// This neatly moves all the functions with blanked names to the
			// start of the public functions table (which will soon be moved).
			Hooks_ComparePublics(i, j);
		}
	}
	// Move the start address UP to reduce the VM's search space.
	if (diff)
	{
		// Update stored values in y_amx so they reflect the new structure.
		AMX_Write(AMX_BASE_ADDRESS + 32, AMX_Read(AMX_BASE_ADDRESS + 32) + diff);
		AMX_HEADER_PUBLICS += diff;
		#if defined ResetStaticAmxHeader
			// I'd love to be able to update ZeeX's code as well, but I can't.
			// Issue pull request for this.
			ResetStaticAmxHeader();
		#endif
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_IsolateName</summary>
<param name="name">The string to get the hooked function name from.</param>
<returns>
	The input string without y_hooks name decorations.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_IsolateName(string:name[])
{
	new
		pos = strfind(name, "@", false, 4);
	// Make "pos" a legal value inside the error message.
	if (pos == -1) P:E("Invalid hook name: %s", unpack(name), ++pos);
	name{pos} = '\0';
	strdel(name, 0, 4);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetName</summary>
<param name="entry">The public entry to get the name of.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_GetName(entry, name[32])
{
	AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(entry + 4), name);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetAddr</summary>
<param name="idx">The public function index to get the address of.</param>
<param name="base">The start of the public functions header.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetAddr(idx, base)
{
	new
		str[32];
	return AMX_Read(idx * 8 + base);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_InvalidateName</summary>
<param name="entry">The public function slot to destroy.</param>
<returns>
	-
</returns>
<remarks>
	Basically, once we know a function has been included, wipe it from the AMX
	header.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_InvalidateName(entry)
{
	AMX_Write(AMX_BASE_ADDRESS + AMX_Read(entry + 4), 0);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_WriteFunction</summary>
<param name="pointers">The hooks to link together.</param>
<param name="size">The number of hooks.</param>
<param name="ret">The default return.</param>
<param name="skipable">Can future hooks be ignored on -1?</param>
<returns>
	The number of bytes written to memory.
</returns>
<remarks>
	Generate some new code, very nicely :D.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_WriteFunction(const pointers[], const size, const ret = 1, const skipable = false)
{
	new
		base = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS,
		ctx[AsmContext];
	// Make sure the underlying system doesn't change without us.  Now supported
	// natively.
	AsmInitPtr(ctx, YSI_g_sCodeSpace, YSI_g_sCodeEnd - YSI_g_sCodeSpace);
	
	// Start of the function.
	@emit PROC
	
	// Allocate space for our "ret" variable at "frm - 4".
	@emit PUSH.C        ret
	
	// Copy the stack to itself (MOVS).
	// Allocate space.
	@emit LOAD.S.alt    8
	@emit LCTRL         4
	@emit SUB
	@emit SCTRL         4
	@emit XCHG
	
	// The "MOVS" OpCode only takes a constant, not a variable, so we need to
	// generate self-modifying code (just to be UBER meta)!  This code is
	// generated AFTER the file is loaded so we bypass the data segment checks
	// and can freely write wherever we want.
	@emit STOR.pri      (ctx[AsmContext_buffer] + 18 * 4)
	
	// Do the copying.  "alt" is already "STK", load the "FRM" offset.
	@emit LCTRL         5 // 4
	@emit ADD.C         12 // 6
	// This is the instruction we want to modify...
	@emit MOVS          0 // 8 - 1
	
	// Push the (fake) number of parameters.
	@emit PUSH.C        -4
	
	// Now loop over all our functions and insert "CALL" opcodes for them.
	for (new i = 0; ; )
	//for (new i = 0; i != size; ++i)
	{
		// Get the absolute offset from here.
		// #emit CALL pointers[i]
		@emit CALL          (pointers[i] + base) // 2
		if (skipable)
		{
			if (ret)
			{
				// =====================================
				//  THIS SECTION IS CURRENTLY 19 BYTES. 
				// =====================================
				// Note: Including the original call...
				// ret = func() & (ret | cellmin);
				@emit PUSH.pri                 // 3
				@emit LOAD.S.alt    -4         // 5
				// That bit for odd numbers.
				@emit CONST.pri     0x80000000 // 7
				@emit OR                       // 8
				@emit POP.alt                  // 9
				@emit AND                      // 10
				@emit STOR.S.pri    -4         // 12
				
				// if (ret < 0) return 0;
				@emit ZERO.alt         // 13
				
				// =========================
				//  JUMP OVER THIS SECTION. 
				// =========================
				if (++i == size)
				{
					// The "Rel" functions work relative to "DAT", but despite
					// the fact that we are writing in "COD", this still works
					// because we are doing that writing relative to "DAT".
					@emit JSGEQ.rel     8  // 15
					@emit ZERO.S        -4 // 17
					// Subtract 8 below for the jump that isn't here.
					break;
				}
				else
				{
					// I spent AGES reading this code to figure out why it was
					// failing - turns out I used "JGEQ" instead of "JSGEQ".
					// Also, I can't count and did "JSGEQ 8" instead of "16"...
					@emit JSGEQ.rel     16 // 15
					@emit ZERO.S        -4 // 17
					// Huge jump (maybe)!
					@emit JUMP.rel      ((size - i) * 19 * 4 - 8) // 19
					// ===============================================
					//  IF THE CODE CHANGES, UPDATE BYTE COUNT ABOVE. 
					// ===============================================
				}
			}
			else
			{
				@emit LOAD.S.alt    -4 // 4
				@emit OR               // 5
				@emit STOR.S.pri    -4 // 7
				@emit ZERO.alt         // 8
				if (++i == size)
				{
					@emit JSGEQ.rel      8 // 10
					@emit ZERO.S        -4 // 12
					break;
				}
				else
				{
					@emit JSGEQ.rel     16 // 10
					@emit ZERO.S        -4 // 12
					// The "- 8" is because the last call doesn't have the last
					// jump so we don't need to skip it.  Ironically, the
					// "JumpRel" functions actually add on 8 to account for this
					// instruction itself so the two cancel each other out.
					@emit JUMP.rel      ((size - i) * 14 * 4 - 8) // 14
				}
			}
		}
		else
		{
			if (ret)
			{
				@emit LOAD.S.alt    -4
				@emit AND
				@emit STOR.S.pri    -4
			}
			else
			{
				@emit LOAD.S.alt    -4
				@emit OR
				@emit STOR.S.pri    -4
			}
			if (++i == size) break;
		}
	}
	// This is the point the large "Jump" above goes to.
	
	// Remove the whole stack then get the return value.
	@emit LCTRL         5
	@emit SCTRL         4
	@emit LOAD.S.pri    -4
	
	// Return.
	@emit RETN
	
	// Return the number of bytes written.
	return ctx[AsmContext_buffer_offset];
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetSame</summary>
<param name="ref">The PACKED function that's hooking something.</param>
<returns>
	-
</returns>
<remarks>
	Some functions are normally too long, here we detect special shortened
	cases.  These are just hard-coded in.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_SpecialCases(const string:ref[])
{
	new
		ret[32 char];
	if (!strcmp(ref, !"OnPlayerEnterRaceCheckpoint")) ret = !"OnPlayerEnterRaceCP";
	else if (!strcmp(ref, !"OnPlayerEnterRaceCP")) ret = !"OnPlayerEnterRaceCheckpoint";
	else if (!strcmp(ref, !"OnPlayerLeaveRaceCheckpoint")) ret = !"OnPlayerLeaveRaceCP";
	else if (!strcmp(ref, !"OnPlayerLeaveRaceCP")) ret = !"OnPlayerLeaveRaceCheckpoint";
	else if (!strcmp(ref, !"OnVehicleDamageStatusUpdate")) ret = !"OnVehicleDamageStatusUpd";
	else if (!strcmp(ref, !"OnVehicleDamageStatusUpd")) ret = !"OnVehicleDamageStatusUpdate";
	else if (!strcmp(ref, !"OnUnoccupiedVehicleUpdate")) ret = !"OnUnoccupiedVehicleUpd";
	else if (!strcmp(ref, !"OnUnoccupiedVehicleUpd")) ret = !"OnUnoccupiedVehicleUpdate";
	else if (!strcmp(ref, !"OnPlayerClickPlayerTextDraw")) ret = !"OnPlayerClickPlayerTD";
	else if (!strcmp(ref, !"OnPlayerClickPlayerTD")) ret = !"OnPlayerClickPlayerTextDraw";
	else if (!strcmp(ref, !"OnPlayerEditAttachedObject")) ret = !"OnPlayerEditAttachedObj";
	else if (!strcmp(ref, !"OnPlayerEditAttachedObj")) ret = !"OnPlayerEditAttachedObject";
	// YSI.
	else if (!strcmp(ref, !"OnPlayerCommandPerformed")) ret = !"OnPlayerCmdPerformed";
	else if (!strcmp(ref, !"OnPlayerCmdPerformed")) ret = !"OnPlayerCommandPerformed";
	// Streamer.
	else if (!strcmp(ref, !"OnPlayerEditDynamicObject")) ret = !"OnPlayerEditDynObject";
	else if (!strcmp(ref, !"OnPlayerSelectDynamicObject")) ret = !"OnPlayerSelectDynObject";
	else if (!strcmp(ref, !"OnPlayerPickUpDynamicPickup")) ret = !"OnPlayerPickUpDynPickup";
	else if (!strcmp(ref, !"OnPlayerEnterDynamicRaceCP")) ret = !"OnPlayerEnterDynRaceCP";
	else if (!strcmp(ref, !"OnPlayerLeaveDynamicRaceCP")) ret = !"OnPlayerLeaveDynRaceCP";
	else if (!strcmp(ref, !"OnPlayerEnterDynamicArea")) ret = !"OnPlayerEnterDynArea";
	else if (!strcmp(ref, !"OnPlayerLeaveDynamicArea")) ret = !"OnPlayerLeaveDynArea";
	else if (!strcmp(ref, !"OnPlayerEditDynObject")) ret = !"OnPlayerEditDynamicObject";
	else if (!strcmp(ref, !"OnPlayerSelectDynObject")) ret = !"OnPlayerSelectDynamicObject";
	else if (!strcmp(ref, !"OnPlayerPickUpDynPickup")) ret = !"OnPlayerPickUpDynamicPickup";
	else if (!strcmp(ref, !"OnPlayerEnterDynRaceCP")) ret = !"OnPlayerEnterDynamicRaceCP";
	else if (!strcmp(ref, !"OnPlayerLeaveDynRaceCP")) ret = !"OnPlayerLeaveDynamicRaceCP";
	else if (!strcmp(ref, !"OnPlayerEnterDynArea")) ret = !"OnPlayerEnterDynamicArea";
	else if (!strcmp(ref, !"OnPlayerLeaveDynArea")) ret = !"OnPlayerLeaveDynamicArea";
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetSame</summary>
<param name="ref">The PACKED function that's hooking something.</param>
<param name="original">The hook function's address.</param>
<param name="ref2">In some cases there are standard short versions.</param>
<returns>
	-
</returns>
<remarks>
	Find all functions with the same name fragment as the one given.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_GetSame(const string:ref[], const original, const string:ref2[] = "")
{
	new
		same[32],
		sameCount = 1,
		entry,
		idx;
	static
		name[32];
	same[0] = AMX_Read(original);
	// Wipe out the current hook.
	Hooks_InvalidateName(original);
	// Loop through all remaining functions to find ones that hook the same
	// data.
	while ((idx = AMX_GetPublicEntry(idx, entry, ref)))
	{
		// Get the function name and compare it to the current one.
		Hooks_GetName(entry, name);
		if (name[0] == (('@' << 24) | ('y' << 16) | ('H' << 8) | ('_'))) // "@yH_"
		{
			// A hook, not an original.
			Hooks_IsolateName(name);
		}
		// Not sufficiently identical.
		if (strcmp(name, ref)) continue;
		// Get just the useful part of the name.
		if (!strcmp(name, ref))
		{
			same[sameCount] = AMX_Read(entry);
			Hooks_InvalidateName(entry);
			if (++sameCount == sizeof (same))
			{
				P:E("sameCount == sizeof (same) in y_hooks.");
				break;
			}
		}
	}
	if (ref2[0])
	{
		idx = 0;
		while ((idx = AMX_GetPublicEntry(idx, entry, ref2)))
		{
			// Get the function name and compare it to the current one.
			Hooks_GetName(entry, name);
			if (name[0] == (('@' << 24) | ('y' << 16) | ('H' << 8) | ('_'))) // "@yH_"
			{
				// A hook, not an original.
				Hooks_IsolateName(name);
			}
			// Not sufficiently identical.
			if (strcmp(name, ref2)) continue;
			// Get just the useful part of the name.
			if (!strcmp(name, ref2))
			{
				same[sameCount] = AMX_Read(entry);
				Hooks_InvalidateName(entry);
				if (++sameCount == sizeof (same))
				{
					P:E("sameCount == sizeof (same) in y_hooks.");
					break;
				}
			}
		}
	}
	// Now start writing our entirely new version.
	// First, the (longest) function name as that is always the "base" name.
	entry = strlen(ref);
	idx = strlen(ref2);
	if (idx > entry) AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(original + 4), ref2, idx);
	else AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(original + 4), ref, entry);
	// I don't know if this will work as they won't be in alphabetical
	// order any more...
	if (sameCount == 1)
	{
		// Only one hook, just call it directly (the pointer is already
		// right so we are done)!
		return;
	}
	// Point "original"'s function pointer to the new function.
	// Write our new function (HARD).
	entry = Hooks_WriteFunction(same, sameCount);
	if (entry)
	{
		AMX_Write(original, YSI_g_sCodeSpace - AMX_HEADER_COD);
		YSI_g_sCodeSpace += entry;
	}
}

public OnScriptInit()
{
	P:2("Hooks_OnScriptInit called");
	new
		func[32],
		entry,
		idx;
	// Get our code space relative to "DAT".
	entry = AMX_HEADER_PUBLICS + funcidx("_@_y_hooks_@_0") * 8;
	YSI_g_sCodeSpace = AMX_HEADER_COD + AMX_Read(entry);
	Hooks_InvalidateName(entry);
	// Determine EXACTLY how much space we have to play with.
	entry = AMX_HEADER_PUBLICS + funcidx("_@_y_hooks_@_1") * 8;
	// Scrounge an extra 8 bytes from the following function too.
	YSI_g_sCodeEnd = AMX_HEADER_COD + AMX_Read(entry) + 8;
	Hooks_InvalidateName(entry);
	// Find all hook functions in order (at least find the first one in a set).
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yH_>)))
	{
		Hooks_GetName(entry, func);
		P:2("Hooks_OnScriptInit: %s", unpack(func));
		Hooks_IsolateName(func);
		// Get all ones the same (and the original).
		Hooks_GetSame(func, entry, Hooks_SpecialCases(func));
	}
	// Finally, put all our new mashed up publics back in order!
	Hooks_SortPublics();
	#if defined S@@_OnScriptInit
		S@@_OnScriptInit();
	#endif
	// Do the main code here.
	#if defined YSI_LOCK_MODE
		YSI_gLockData[1] = floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil);
		YSI_gLockData[0] = 5 + YSI_gLockData[1];
		YSI_gLockData[2] = YSI_gLockData[0] - 5;
		if (~strval(YSI_gLockData[5]) != ~_LOCK_IP_0)
		{
			y_lock 2;
		}
		YSI_gLockData[2] -= YSI_gLockData[1];
		YSI_gLockData[YSI_gLockData[2] + 1] -= YSI_gLockData[0];
		YSI_gLockData[1] += '.' + 5;
	#endif
	return ALS_R_ScriptInit;
}
#if defined _ALS_OnScriptInit
	#undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit S@@_OnScriptInit
#if defined S@@_OnScriptInit
	forward S@@_OnScriptInit();
#endif
