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
	YSI_g_sCodeEnd;//,
	//YSI_g_sParamsStack[128],
	//YSI_g_sReturnStack[128],
	//YSI_g_sReturnPtr;

// If you have a (hooked) call stack deeper than this there's something wrong
// with you!

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
	memcpy("", "", 0, 0, 0);
	// This code is here for handy "-a" reference.
	//YSI_g_sParamsStack[YSI_g_sReturnPtr++] = 0;
	//YSI_g_sReturnStack[YSI_g_sReturnPtr++] = 0;
	//YSI_g_sReturnPtr = 0;
	// Reserve a huge area of "COD" for our own use!
	static
		STE[] = "";
	#define _CODE_1 SetTimerEx(STE,0,0,STE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	#define _CODE_2 _CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;
	// This reserves about 20kb of space in the 
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
	//s0 = Cell_ReverseBytes(s0);
	//s1 = Cell_ReverseBytes(s1);
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
			//case 0:
			case 1:
			{
				// Already in order - good.
				return;
			}
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
		//newCount = oldCount + diff;
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
	//static
	//	str[32];
	//AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(idx * 8 + base + 4), str);
	AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(entry + 4), name);
	//return str;
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
<returns>
	The number of bytes written to memory.
</returns>
<remarks>
	Generate some new code, very nicely :D.
</remarks>
\**--------------------------------------------------------------------------**/

/*_Y_HOOKS_STATIC Hooks_JumpAddress(ctx, base, offset)
{
	// We aren't in the data section, so the "Rel" functions don't work.
	//new next_offset = 2 * 4; // offset to the next instruction
	return base + ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + 2 * 4 + offset;
}*/

//#define Hooks_JumpAddress(%0,%2) ((%0[AsmContext_buffer]) + (%0[AsmContext_buffer_offset]) + (2 * 4) + (%2) + AMX_REAL_DATA)

_Y_HOOKS_STATIC Hooks_WriteFunction(pointers[], size, ret = 1)
{
	new
		//start = YSI_g_sCodeSpace - AMX_HEADER_COD,
		base = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS,
		//base = AMX_HEADER_COD + AMX_REAL_DATA,
		ctx[AsmContext];
	// Make sure the underlying system doesn't change without us.
	#assert _:AsmContext_buffer == 0
	#assert _:AsmContext_buffer_size == 1
	#assert _:AsmContext_buffer_offset == 2
	#assert _:AsmContext_error_handler == 3
	#assert _:AsmContext == 4
	// Don't call "AsmInit" because we need custom functionality.
	ctx[AsmContext_buffer] = YSI_g_sCodeSpace;
	ctx[AsmContext_buffer_size] = YSI_g_sCodeEnd - YSI_g_sCodeSpace;
	ctx[AsmContext_buffer_offset] = 0;
	ctx[AsmContext_error_handler] = 0;
	#define _ASM_NO:ctx,) ctx)
	#define _ASM:%0(%1); if((AsmEmit%0(_:_ASM_NO:ctx,%1))!=ASM_ERROR_NONE){P:E("Hooks_WriteFunction");return 0;}
	
	// Start of the function.
	// #emit PROC
	_ASM:Proc();
	
	// Allocate space for our "ret" variable at "frm - 4".
	_ASM:PushC(ret);
	
	// Copy the stack to itself (memcpy).
	// Allocate space.
	// #emit LOAD.S.alt    8
	_ASM:LoadSAlt(8);
	// #emit LCTRL         4
	_ASM:Lctrl(4);
	// #emit SUB
	_ASM:Sub();
	// #emit SCTRL         4
	_ASM:Sctrl(4);
	// #emit MOVE.alt
	_ASM:MoveAlt();
	
	// memcpy(stack, frm[3], 0, *(frm + 8), 64);
	// #emit PUSH.C        64
	_ASM:PushC(64);
	// #emit PUSH.S        8
	_ASM:PushS(8);
	// #emit PUSH.C        0
	_ASM:PushC(0);
	// #emit LCTRL         5
	_ASM:Lctrl(5);
	// #emit ADD.C         12
	_ASM:AddC(12);
	// #emit PUSH.pri
	_ASM:PushPri();
	// Stored (higher) stack point.
	// #emit PUSH.alt
	_ASM:PushAlt();
	// #emit PUSH.C        20
	_ASM:PushC(20);
	// #emit SYSREQ.C      memcpy
	_ASM:CallNative("memcpy");
	// #emit STACK         24
	_ASM:Stack(24);
	
	// Push the (fake) number of parameters.
	// #emit PUSH.C        0xFFFFFFFC
	_ASM:PushC(-4);
	
	// Now loop over all our functions and insert "CALL" opcodes for them.
	for (new i = 0; ; )
	{
		// =====================================
		//  THIS SECTION IS CURRENTLY 22 BYTES. 
		// =====================================
		// #emit CALL pointers[i]
		// Get the absolute offset from here.
		_ASM:Call(pointers[i] + base); // 2
		// TODO: Handle "0" and "-1" returns as before.
		// #emit MOVE.alt
		_ASM:MoveAlt(); // 3
		// #emit CONST.pri  0xFFFFFFFE
		_ASM:ConstPri(~1); // 5
		// #emit AND
		_ASM:And(); // 6
		// #emit PUSH.pri
		_ASM:PushPri(); // 7
		// #emit LOAD.S.pri ret
		_ASM:LoadSPri(-4); // 9
		// #emit AND
		_ASM:And(); // 10
		// #emit POP.alt
		_ASM:PopAlt(); // 11
		// #emit OR
		_ASM:Or(); // 12
		// #emit STOR.S.pri ret
		_ASM:StorSPri(-4); // 14
		
		// if (ret < 0) return ret + 1;
		_ASM:ConstAlt(0); // 16
		// =========================
		//  JUMP OVER THIS SECTION. 
		// =========================
		if (++i == size)
		{
			// We aren't IN the data section, so "JgeqRel" doesn't work.
			_ASM:JgeqRel(4); // 18
			//_ASM:Jgeq(Hooks_JumpAddress(ctx, 4)); // 18
			//_ASM:IncS(-4); // 20
			_ASM:ZeroS(-4);
			// Subtract 8 below to not jump over the jump that isn't here.
			break;
		}
		else
		{
			_ASM:JgeqRel(8); // 18
			//_ASM:Jgeq(Hooks_JumpAddress(ctx, 8)); // 18
			//_ASM:IncS(-4); // 20
			_ASM:ZeroS(-4);
			// Huge jump (maybe)!
			_ASM:JumpRel((size - i) * 22 * 4 - 8); // 22
			//_ASM:Jump(Hooks_JumpAddress(ctx, (size - i) * 22 * 4 - 8)); // 22
			// ===============================================
			//  IF THE CODE CHANGES, UPDATE BYTE COUNT ABOVE. 
			// ===============================================
		}
	}
	// This is the point the large jump above goes to.
	
	// Remove our fake count.
	// #emit POP.alt
	_ASM:PopAlt();
	
	// Remove our parameters.
	// #emit LOAD.S.alt    8
	_ASM:LoadSAlt(8);
	// #emit LCTRL         4
	_ASM:Lctrl(4);
	// #emit ADD
	_ASM:Add();
	// #emit SCTRL         4
	_ASM:Sctrl(4);
	// #emit MOVE.alt
	_ASM:MoveAlt();
	
	// Get the return value.
	// #emit POP.pri
	_ASM:PopPri();
	
	// Return.
	// #emit RETN
	_ASM:Retn();
	
	/*
	// We don't call "PROC" because there's no need to save the stack - we don't
	// do anything relative to it so keep the stack slightly invalid!
	
	// Store the current return.
	// #emit CONST.alt YSI_g_sReturnStack
	_ASM:ConstAlt(AMX_GetRelativeAddress(YSI_g_sReturnStack));
	// #emit LOAD.pri YSI_g_sReturnPtr
	_ASM:LoadPri(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	// #emit IDXADDR
	_ASM:Idxaddr();
	
	// Extract and store the return address.
	// #emit POP.alt
	_ASM:PopAlt();
	// #emit XCHG
	_ASM:Xchg();
	// #emit STOR.I
	_ASM:StorI();
	
	// Store the current parameters.
	// #emit CONST.alt YSI_g_sParamsStack
	_ASM:ConstAlt(AMX_GetRelativeAddress(YSI_g_sParamsStack));
	// #emit LOAD.pri  YSI_g_sReturnPtr
	_ASM:LoadPri(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	// #emit IDXADDR
	_ASM:Idxaddr();
	
	// Extract and store the parameter count.
	// #emit POP.alt
	_ASM:PopAlt();
	// #emit XCHG
	_ASM:Xchg();
	// #emit STOR.I
	_ASM:StorI();
	
	// Increment the pointer.
	// #emit INC       YSI_g_sReturnPtr
	_ASM:Inc(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	
	// Mangle the parameters count so "RETN" ADDS ON parameters, or more
	// specifically so it doesn't remove any at all.  We do this instead of just
	// pushing all the parameters over and over again because we don't know how
	// many there are in advance so we would need a loop in that case.
	// #emit PUSH.C 0xFFFFFFFC
	_ASM:PushC(-4);
	
	// Now loop over all our functions and insert "CALL" opcodes for them.
	for (new i = 0; i != size; ++i)
	{
		// #emit CALL pointers[i]
		// Get the absolute offset from here.
		_ASM:Call(pointers[i] + base);
		// TODO: Handle "0" and "-1" returns as before.
	}
	
	// Pop our mini stack.
	// #emit DEC       YSI_g_sReturnPtr
	_ASM:Dec(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	
	// Pop our fake argument count.
	// #emit POP.alt
	_ASM:PopAlt();
	
	// Get the parameter count.
	// #emit CONST.alt YSI_g_sParamsStack
	_ASM:ConstAlt(AMX_GetRelativeAddress(YSI_g_sParamsStack));
	// #emit LOAD.pri  YSI_g_sReturnPtr
	_ASM:LoadPri(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	// #emit LIDX
	_ASM:Lidx();
	// #emit MOVE.alt
	_ASM:MoveAlt();
	
	// Reduce the stack.
	// #emit LCTRL 4
	_ASM:Lctrl(4);
	// #emit ADD
	_ASM:Add();
	// #emit SCTRL 4
	_ASM:Sctrl(4);
	
	// Get the return.
	// #emit CONST.alt YSI_g_sReturnStack
	_ASM:ConstAlt(AMX_GetRelativeAddress(YSI_g_sReturnStack));
	// #emit LOAD.pri  YSI_g_sReturnPtr
	_ASM:LoadPri(AMX_GetRelativeAddress(YSI_g_sReturnPtr));
	// #emit LIDX
	_ASM:Lidx();
	
	// Don't use "RETN" as we didn't use "PROC".
	// #emit SCTRL 6
	_ASM:Sctrl(6);
	*/
	
	#undef _ASM_NO
	#undef _ASM
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
	//printf("ref: %s", unpack(ref));
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
	//printf("ret: %s", unpack(ret));
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
	//YSI_g_sReturn = 0;
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
	YSI_g_sCodeEnd = AMX_HEADER_COD + AMX_Read(entry);
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

/**
Basic custom function layout

// We don't call "PROC" because there's no need to save the stack - we don't do
// anything relative to it so keep the stack slightly invalid!

// Store the current return.
#emit CONST.alt YSI_g_sReturnStack
#emit LOAD.pri  YSI_g_sReturnPtr
#emit IDXADDR

// Extract and store the return address.
#emit POP.alt
#emit XCHG
#emit STOR.I

// Store the current parameters.
#emit CONST.alt YSI_g_sParamsStack
#emit LOAD.pri  YSI_g_sReturnPtr
#emit IDXADDR

// Extract and store the parameter count.
#emit POP.alt
#emit XCHG
#emit STOR.I

// Increment the pointer.
#emit INC       YSI_g_sReturnPtr

// Mangle the parameters count so "RETN" ADDS ON parameters, or more
// specifically so it doesn't remove any at all.  We do this instead of just
// pushing all the parameters over and over again because we don't know how many
// there are in advance so we would need a loop in that case.
#emit PUSH.C 0xFFFFFFFC

// Now loop over all our functions and insert "CALL" opcodes for them.
for ( ; ; )
{
	#emit CALL <wherever - here>
}

// Pop our mini stack.
#emit DEC       YSI_g_sReturnPtr

// Pop our fake argument count.
#emit POP.alt

// Get the parameter count.
#emit CONST.alt YSI_g_sParamsStack
#emit LOAD.pri  YSI_g_sReturnPtr
#emit LIDX
#emit MOVE.alt

// Reduce the stack.
#emit LCTRL 4
#emit ADD
#emit SCTRL 4

// Get the return.
#emit CONST.alt YSI_g_sReturnStack
#emit LOAD.pri  YSI_g_sReturnPtr
#emit LIDX

// Don't use "RETN" as we didn't use "PROC".
#emit SCTRL 6
**/

/**
Second custom function layout

#emit PROC

// Copy the stack to itself (memcpy).
// Allocate space.
#emit LOAD.S.alt    8
#emit LCTRL         4
#emit SUB
#emit SCTRL         4
#emit MOVE.alt

// memcpy(stack, frm[3], 0, *(frm + 8), 64);
#emit PUSH.C        64
#emit PUSH.S        8
#emit PUSH.C        0
#emit LCTRL         5
#emit ADD.C         12
#emit PUSH.pri
// Stored (higher) stack point.
#emit PUSH.alt
#emit PUSH.C        20
#emit SYSREQ.C      memcpy
#emit STACK         24

// Push the (fake) number of parameters.
#emit PUSH.C        0xFFFFFFFC

// Now loop over all our functions and insert "CALL" opcodes for them.
for ( ; ; )
{
	#emit CALL <wherever - here>
}

// Remove our fake count.
#emit POP.alt

// Remove our parameters.
#emit LOAD.S.alt    8
#emit LCTRL         4
#emit ADD
#emit SCTRL         4
#emit MOVE.alt

// Return.
#emit RETN

**/
