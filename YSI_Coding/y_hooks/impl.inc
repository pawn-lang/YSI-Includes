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
	26/12/13:
		Added sections.
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

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           
    
*/

#define hook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2);UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define rehook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define Hook:%0_%1(%2) @yH_%1@%0(%2);@yH_%1@%0(%2)
// Strip out extra spaces (nicely recursive)
#define @yH_%0\32;%1(%2) @yH_%1(%2)

// DO NOT hook the Init functions or we will get stuck in an infinite loop!
//#define @yH_OnGameModeInit @yH_GameModeInit
//#define @yH_OnFilterScriptInit @yH_FilterScriptInit
//#define @yH_OnScriptInit @yH_ScriptInit

_Y_HOOKS_STATIC stock
	YSI_g_sOnGameModeInit,
	YSI_g_sOnFilterScriptInit,
	YSI_g_sOnScriptInit;

static stock const
	// Multiple of 4 characters with NULL.
	YSI_gscOnPlayerEnterRaceCP     [32 char] = !"OnPlayerEnterRaceCheckpoint\0\0\0\0",
	// Multiple of 4 characters with NULL.
	YSI_gscOnPlayerLeaveRaceCP     [32 char] = !"OnPlayerLeaveRaceCheckpoint\0\0\0\0",
	YSI_gscOnVehicleDamageStatusUpd[32 char] = !"OnVehicleDamageStatusUpdate",
	YSI_gscOnUnoccupiedVehicleUpd  [32 char] = !"OnUnoccupiedVehicleUpdate",
	YSI_gscOnPlayerClickPlayerTD   [32 char] = !"OnPlayerClickPlayerTextDraw",
	YSI_gscOnPlayerEditAttachedObj [32 char] = !"OnPlayerEditAttachedObject",
	// YSI callbacks.
	YSI_gscOnPlayerCmdPerformed    [32 char] = !"OnPlayerCommandPerformed",
	// YSI_gscOnPlayerCommandReceived    [32 char] = !"OnPlayerCommandReceived",
	YSI_gscOnMasterSystemClose    [32 char] = !"Master_OnScriptClose",
	// Streamer plugin long callbacks.
	YSI_gscOnPlayerEditDynObject  [32 char] = !"OnPlayerEditDynamicObject",
	YSI_gscOnPlayerSelectDynObject[32 char] = !"OnPlayerSelectDynamicObject",
	YSI_gscOnPlayerPickUpDynPickup[32 char] = !"OnPlayerPickUpDynamicPickup",
	YSI_gscOnPlayerEnterDynRaceCP [32 char] = !"OnPlayerEnterDynamicRaceCP",
	YSI_gscOnPlayerLeaveDynRaceCP [32 char] = !"OnPlayerLeaveDynamicRaceCP",
	YSI_gscOnPlayerEnterDynArea   [32 char] = !"OnPlayerEnterDynamicArea",
	YSI_gscOnPlayerLeaveDynArea   [32 char] = !"OnPlayerLeaveDynamicArea",
	// Multiple of 4 characters with NULL.
	YSI_gscOnScriptExit           [32 char] = !"ScriptInit_OnScriptExit";

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
	P:F("Someone called \"_@_y_hooks_@_0\" and somehow it didn't crash yet!");
	assert(FALSE); // Always fails.
	Hooks_DoForceReverse("");
	//memcpy("", "", 0, 0, 0);
	// Reserve a huge area of "COD" for our own use!
	static
		STE[] = "";
	#define _CODE_1 SetTimerEx(STE,0,0,STE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	#define _CODE_2 _CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1
	// This reserves about 5kb of space in "COD"
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	// Uncomment this block if more hook function space is required.
	/*
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	*/
	#undef _CODE_2
	#undef _CODE_1
}

forward _@_y_hooks_@_1();

public _@_y_hooks_@_1()
{
	// This function SHOULD come straight after "_@_y_hooks_@_0" in both the
	// public functions table and code segment if the compiler is true to form.
}

/*

    88        88         88 88            
    88        88   ,d    "" 88            
    88        88   88       88            
    88        88 MM88MMM 88 88 ,adPPYba,  
    88        88   88    88 88 I8[    ""  
    88        88   88    88 88  `"Y8ba,   
    Y8a.    .a8P   88,   88 88 aa    ]8I  
     `"Y8888Y"'    "Y888 88 88 `"YbbdP"'  

*/

/**--------------------------------------------------------------------------**\
<summary>Hooks_DoForceReverse</summary>
<param name="str">The string to convert.</param>
<returns>
	-
</returns>
<remarks>
	Does the actual reversing once "Hooks_ForceReverse" has stripped off the
	"const" modifier.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_DoForceReverse(str[])
{
	for (new i = 0; i != 32 char; ++i)
	{
		str[i] = Cell_ReverseBytes(str[i]);
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_ForceReverse</summary>
<param name="str">The string to convert.</param>
<returns>
	-
</returns>
<remarks>
	Converts a constant packed string to a C string.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_ForceReverse(/* mutable */ const str[32 char])
{
	P:C(if (strlen(str) & 3 != 3) P:W("%s must be padded for \"Hooks_ForceReverse\"", unpack(str)););
	// Modifies constant strings - naughty but meh.
	#emit PUSH.S     str
	#emit PUSH.C     4
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit CONST.pri  Hooks_DoForceReverse
	#emit SCTRL      6
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

/*

     ad88888ba                                 88                          
    d8"     "8b                          ,d    ""                          
    Y8,                                  88                                
    `Y8aaaaa,    ,adPPYba,  8b,dPPYba, MM88MMM 88 8b,dPPYba,   ,adPPYb,d8  
      `"""""8b, a8"     "8a 88P'   "Y8   88    88 88P'   `"8a a8"    `Y88  
            `8b 8b       d8 88           88    88 88       88 8b       88  
    Y8a     a8P "8a,   ,a8" 88           88,   88 88       88 "8a,   ,d88  
     "Y88888P"   `"YbbdP"'  88           "Y888 88 88       88  `"YbbdP"Y8  
                                                               aa,    ,88  
                                                                "Y8bbdP"   

*/

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
	else if (!(s0 & 0x000000FF)) s0 &= 0xFFFFFF00;
	if (!(s1 & 0xFF000000)) s1 = 0;
	else if (!(s1 & 0x00FF0000)) s1 &= 0xFF000000;
	else if (!(s1 & 0x0000FF00)) s1 &= 0xFFFF0000;
	else if (!(s1 & 0x000000FF)) s1 &= 0xFFFFFF00;
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
		// I'd love to be able to update ZeeX's code as well, but I can't.
		// Issue pull request for this.
		ResetStaticAmxHeader();
	}
	// TODO: Inform the fixes2 plugin of the change.  That stores indexes, not
	// addresses so it needs to update itself (somehow - I don't actually know
	// HOW it will do this...)  Probably inform it first, store the addresses,
	// then inform it again to track down and replace those addresses.
}

/*

           db        88b           d88 8b        d8    88               ad88             
          d88b       888b         d888  Y8,    ,8P     88              d8"               
         d8'`8b      88`8b       d8'88   `8b  d8'      88              88                
        d8'  `8b     88 `8b     d8' 88     Y88P        88 8b,dPPYba, MM88MMM ,adPPYba,   
       d8YaaaaY8b    88  `8b   d8'  88     d88b        88 88P'   `"8a  88   a8"     "8a  
      d8""""""""8b   88   `8b d8'   88   ,8P  Y8,      88 88       88  88   8b       d8  
     d8'        `8b  88    `888'    88  d8'    `8b     88 88       88  88   "8a,   ,a8"  
    d8'          `8b 88     `8'     88 8P        Y8    88 88       88  88    `"YbbdP"'   

*/

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

_Y_HOOKS_STATIC stock Hooks_GetAddr(entry)
{
	return AMX_Read(entry);
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

/*

      ,ad8888ba,                       88                                                
     d8"'    `"8b                      88                                                
    d8'                                88                                                
    88             ,adPPYba,   ,adPPYb,88  ,adPPYba,  ,adPPYb,d8  ,adPPYba, 8b,dPPYba,   
    88            a8"     "8a a8"    `Y88 a8P_____88 a8"    `Y88 a8P_____88 88P'   `"8a  
    Y8,           8b       d8 8b       88 8PP""""""" 8b       88 8PP""""""" 88       88  
     Y8a.    .a8P "8a,   ,a8" "8a,   ,d88 "8b,   ,aa "8a,   ,d88 "8b,   ,aa 88       88  
      `"Y8888Y"'   `"YbbdP"'   `"8bbdP"Y8  `"Ybbd8"'  `"YbbdP"Y8  `"Ybbd8"' 88       88  
                                                      aa,    ,88                         
                                                       "Y8bbdP"                          

*/

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

_Y_HOOKS_STATIC Hooks_WriteFunction(const pointers[], const size, const ret = 1, const skipable = true)
{
	new
		bool:multiple = size != 1,
		base = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS,
		ctx[AsmContext];
	// Make sure the underlying system doesn't change without us.  Now supported
	// natively.
	CGen_UseCodeSpace(ctx);
	
	// Start of the function.
	@emit PROC              // 1
	
	// Allocate space for our "ret" variable at "frm - 4".
	if (multiple) @emit PUSH.C        ret // 3
	
	// Copy the stack to itself (MOVS).
	// Allocate space.
	@emit LOAD.S.alt    8   // 5
	@emit LCTRL         4   // 7
	@emit SUB               // 8
	@emit SCTRL         4   // 10
	@emit XCHG              // 11
	
	// The "MOVS" OpCode only takes a constant, not a variable, so we need to
	// generate self-modifying code (just to be UBER meta)!  This code is
	// generated AFTER the file is loaded so we bypass the data segment checks
	// and can freely write wherever we want.
	@emit STOR.pri      (CGen_GetCodeSpace() + (18 * 4) - (multiple ? 0 : 8)) // 13
	
	// Do the copying.  "alt" is already "STK", load the "FRM" offset.
	@emit LCTRL         5   // 15
	@emit ADD.C         12  // 17
	// This is the instruction we want to modify...
	@emit MOVS          0   // 19 (- 1)
	
	// Push the (fake) number of parameters.
	@emit PUSH.C        -4
	// Now loop over all our functions and insert "CALL" opcodes for them.
	if (multiple)
	{
		for (new i = 0; ; )
		{
			// Get the absolute offset from here.
			// #emit CALL pointers[i]
			@emit CALL          (pointers[i] + base) // 2
			if (skipable)
			{
				// =====================================
				//  THIS SECTION IS CURRENTLY 10 CELLS. 
				// =====================================
				// Note: Including the original call...
				//  
				//  if (func() < 0) break;
				//  else ret = ret & func();
				//  
				@emit ZERO.alt      // 3
				@emit JSLESS.rel    ((size - i) * (10 * 4) - (5 * 4)) // 5
				// =========================
				//  JUMP OVER THIS SECTION. 
				// =========================
			}
			@emit LOAD.S.alt    -4   // 7
			if (ret) @emit AND       // 8
			else @emit OR            // 8
			if (++i == size) break;
			else @emit STOR.S.pri -4 // 10
		}
		if (skipable)
		{
			@emit JUMP.rel      4    // 10
			// This is the point the large "JSLESS" above goes to.
			// -1 = 0, -2 = 1
			@emit INVERT
		}
	}
	else if (skipable)
	{
		// Still need this code as they may hook a function that doesn't exist,
		// but we still need to correctly process -1 or -2.
		@emit CALL          (pointers[0] + base)
		@emit ZERO.alt
		@emit JSGEQ.rel     4
		@emit INVERT
	}
	else
	{
		// Just replace the original (turns out, this takes no code).  Basically
		// just discard everything we've written so far (reclaims the memory).
		return 0;
	}
	
	// This is the point the small "JUMP" above goes to.
	@emit MOVE.alt
	// Remove the whole stack then get the return value.
	@emit LCTRL         5
	@emit SCTRL         4
	//@emit LOAD.S.pri    -4
	@emit MOVE.pri
	
	// Return.
	@emit RETN
	
	// Return the number of bytes written.
	return ctx[AsmContext_buffer_offset];
}

/*

    88888888888                                        88                            88               ad88             
    88                                           ,d    ""                            88              d8"               
    88                                           88                                  88              88                
    88aaaaa 88       88 8b,dPPYba,   ,adPPYba, MM88MMM 88  ,adPPYba,  8b,dPPYba,     88 8b,dPPYba, MM88MMM ,adPPYba,   
    88""""" 88       88 88P'   `"8a a8"     ""   88    88 a8"     "8a 88P'   `"8a    88 88P'   `"8a  88   a8"     "8a  
    88      88       88 88       88 8b           88    88 8b       d8 88       88    88 88       88  88   8b       d8  
    88      "8a,   ,a88 88       88 "8a,   ,aa   88,   88 "8a,   ,a8" 88       88    88 88       88  88   "8a,   ,a8"  
    88       `"YbbdP'Y8 88       88  `"Ybbd8"'   "Y888 88  `"YbbdP"'  88       88    88 88       88  88    `"YbbdP"'   

*/

/**--------------------------------------------------------------------------**\
<summary>Hooks_SpecialCases</summary>
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
	static
		ret[32 char];
	ret[0] = '\0';
	// The comments after are the number of saved characters.  If this is
	// greater than 6, then we need to specially handle the rewriting as that
	// means there isn't enough space in the hook's name for the original.
	if      (!strcmp(ref, YSI_gscOnPlayerEnterRaceCP))      ret = !"OnPlayerEnterRaceCP";      // 8
	else if (!strcmp(ref, YSI_gscOnPlayerLeaveRaceCP))      ret = !"OnPlayerLeaveRaceCP";      // 8
	else if (!strcmp(ref, YSI_gscOnVehicleDamageStatusUpd)) ret = !"OnVehicleDamageStatusUpd"; // 3
	else if (!strcmp(ref, YSI_gscOnUnoccupiedVehicleUpd))   ret = !"OnUnoccupiedVehicleUpd";   // 3
	else if (!strcmp(ref, YSI_gscOnPlayerClickPlayerTD))    ret = !"OnPlayerClickPlayerTD";    // 6
	else if (!strcmp(ref, YSI_gscOnPlayerEditAttachedObj))  ret = !"OnPlayerEditAttachedObj";  // 3
	else if (!strcmp(ref, !"OnPlayerEnterRaceCP"))      ret = YSI_gscOnPlayerEnterRaceCP;
	else if (!strcmp(ref, !"OnPlayerLeaveRaceCP"))      ret = YSI_gscOnPlayerLeaveRaceCP;
	else if (!strcmp(ref, !"OnVehicleDamageStatusUpd")) ret = YSI_gscOnVehicleDamageStatusUpd;
	else if (!strcmp(ref, !"OnUnoccupiedVehicleUpd"))   ret = YSI_gscOnUnoccupiedVehicleUpd;
	else if (!strcmp(ref, !"OnPlayerClickPlayerTD"))    ret = YSI_gscOnPlayerClickPlayerTD;
	else if (!strcmp(ref, !"OnPlayerEditAttachedObj"))  ret = YSI_gscOnPlayerEditAttachedObj;
	// YSI.
	else if (!strcmp(ref, YSI_gscOnPlayerCmdPerformed)) ret = !"OnPlayerCmdPerformed";         
	else if (!strcmp(ref, !"OnPlayerCmdPerformed"))     ret = YSI_gscOnPlayerCmdPerformed;
	// else if (!strcmp(ref, YSI_gscOnPlayerCommandReceived)) ret = !"OnPlayerCommandReceived";         
	// else if (!strcmp(ref, !"OnPlayerCommandReceived"))     ret = YSI_gscOnPlayerCommandReceived;
	else if (!strcmp(ref, YSI_gscOnMasterSystemClose)) ret = !"OnMasterSystemClose";         
	else if (!strcmp(ref, !"OnMasterSystemClose"))     ret = YSI_gscOnMasterSystemClose;
	// Streamer ("CP" is already shorter for the streamer).
	else if (!strcmp(ref, YSI_gscOnPlayerEditDynObject))   ret = !"OnPlayerEditDynObject";     // 4
	else if (!strcmp(ref, YSI_gscOnPlayerSelectDynObject)) ret = !"OnPlayerSelectDynObject";   // 4
	else if (!strcmp(ref, YSI_gscOnPlayerPickUpDynPickup)) ret = !"OnPlayerPickUpDynPickup";   // 4
	else if (!strcmp(ref, YSI_gscOnPlayerEnterDynRaceCP))  ret = !"OnPlayerEnterDynRaceCP";    // 4
	else if (!strcmp(ref, YSI_gscOnPlayerLeaveDynRaceCP))  ret = !"OnPlayerLeaveDynRaceCP";    // 4
	else if (!strcmp(ref, YSI_gscOnPlayerEnterDynArea))    ret = !"OnPlayerEnterDynArea";      // 4
	else if (!strcmp(ref, YSI_gscOnPlayerLeaveDynArea))    ret = !"OnPlayerLeaveDynArea";      // 4
	else if (!strcmp(ref, !"OnPlayerEditDynObject"))   ret = YSI_gscOnPlayerEditDynObject;
	else if (!strcmp(ref, !"OnPlayerSelectDynObject")) ret = YSI_gscOnPlayerSelectDynObject;
	else if (!strcmp(ref, !"OnPlayerPickUpDynPickup")) ret = YSI_gscOnPlayerPickUpDynPickup;
	else if (!strcmp(ref, !"OnPlayerEnterDynRaceCP"))  ret = YSI_gscOnPlayerEnterDynRaceCP;
	else if (!strcmp(ref, !"OnPlayerLeaveDynRaceCP"))  ret = YSI_gscOnPlayerLeaveDynRaceCP;
	else if (!strcmp(ref, !"OnPlayerEnterDynArea"))    ret = YSI_gscOnPlayerEnterDynArea;
	else if (!strcmp(ref, !"OnPlayerLeaveDynArea"))    ret = YSI_gscOnPlayerLeaveDynArea;
	// Start points.
	else if (!strcmp(ref, !"OnGameModeInit"))     ret = !"S@@_OnGameModeInit";     // N/A
	else if (!strcmp(ref, !"OnFilterScriptInit")) ret = !"S@@_OnFilterScriptInit"; // N/A
	else if (!strcmp(ref, !"OnScriptInit"))       ret = !"S@@_OnScriptInit";       // N/A
	// Specially named exit point.
	else if (!strcmp(ref, !"OnScriptExit"))       ret = YSI_gscOnScriptExit;       // 11
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_SpecialReturns</summary>
<param name="ref">The PACKED function that's hooking something.</param>
<returns>
	The default return value for this function.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_SpecialReturns(const string:ref[])
{
	if (!strcmp(ref, !"OnPlayerCommandText")) return 0;
	else if (!strcmp(ref, !"OnPlayerCommandPerformed")) return 0;
	else if (!strcmp(ref, !"OnPlayerCmdPerformed")) return 0;
	return 1;
}

/*

      ,ad8888ba,              88 88                    88                          
     d8"'    `"8b             88 88              ,d    ""                          
    d8'                       88 88              88                                
    88             ,adPPYba,  88 88 ,adPPYYba, MM88MMM 88  ,adPPYba,  8b,dPPYba,   
    88            a8"     "8a 88 88 ""     `Y8   88    88 a8"     "8a 88P'   `"8a  
    Y8,           8b       d8 88 88 ,adPPPPP88   88    88 8b       d8 88       88  
     Y8a.    .a8P "8a,   ,a8" 88 88 88,    ,88   88,   88 "8a,   ,a8" 88       88  
      `"Y8888Y"'   `"YbbdP"'  88 88 `"8bbdP"Y8   "Y888 88  `"YbbdP"'  88       88  

*/

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

_Y_HOOKS_STATIC Hooks_GetSame(const string:ref[], const original, const string:ref2[])
{
	new
		// Uugh, special cases!
		init = (_:!strcmp(ref, !"OnScriptExit") << 3) | (_:!strcmp(ref, !"OnGameModeInit") << 2) | (_:!strcmp(ref, !"OnFilterScriptInit") << 1) | (_:!strcmp(ref, !"OnScriptInit")),
		same[32],
		sameCount = 3,
		entry,
		pure,
		idx;
	static
		name[32];
	P:4("Hooks_GetSame called: \"%s\" = %d, %d, \"%s\" = %d", unpack(ref), strlen(ref), original, unpack(ref2), strlen(ref2));
	// Reserve space for ALS hooked callbacks first.
	same[2] = AMX_Read(original),
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
			Hooks_IsolateName(name),
			pure = 0;
		}
		else if (init) continue; // Don't hook the originals "Init" functions.
		else pure = 1;
		// Not sufficiently identical.
		if (strcmp(name, ref)) continue;
		// Get just the useful part of the name.
		if (!strcmp(name, ref))
		{
			Hooks_InvalidateName(entry);
			if (pure) same[1] = AMX_Read(entry);
			else
			{
				same[sameCount] = AMX_Read(entry);
				if (++sameCount == sizeof (same))
				{
					P:E("sameCount == sizeof (same) in y_hooks.");
					break;
				}
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
				Hooks_IsolateName(name),
				pure = 0;
			}
			else pure = 1;
			// Not sufficiently identical.
			if (strcmp(name, ref2)) continue;
			// Get just the useful part of the name.
			if (!strcmp(name, ref2))
			{
				Hooks_InvalidateName(entry);
				if (pure)
				{
					if (same[1]) same[0] = AMX_Read(entry);
					else same[1] = AMX_Read(entry);
				}
				else
				{
					same[sameCount] = AMX_Read(entry);
					if (++sameCount == sizeof (same))
					{
						P:E("sameCount == sizeof (same) in y_hooks.");
						break;
					}
				}
			}
		}
	}
	// Now start writing our entirely new version.
	// First, the (longest) function name as that is always the "base" name.
	entry = strlen(ref),
	idx = strlen(ref2);
	P:6("Hooks_GetSame: Lengths = %d (ref), %d (ref2)", entry, idx);
	#if _DEBUG >= 5
		AMX_Write(AMX_BASE_ADDRESS + AMX_Read(original + 4), _A<@yH_>);
		AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(original + 4), Q@);
		AMX_Write(AMX_BASE_ADDRESS + AMX_Read(original + 4), 0);
		printf("Hooks_GetSame: exist = %s", unpack(Q@));
		printf("Hooks_GetSame: ref = %s", unpack(ref));
		AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(original + 4), ref, entry);
		AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(original + 4), Q@);
		printf("Hooks_GetSame: new = %s", unpack(Q@));
	#endif
	if (idx <= entry) AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(original + 4), ref, entry);
	else
	{
		// There's a chance this won't be long enough at all!
		if (!strcmp(ref2, YSI_gscOnPlayerEnterRaceCP))
		{
			Hooks_ForceReverse(YSI_gscOnPlayerEnterRaceCP);
			P:5("Hooks_GetSame: REVERSED: %s", unpack(YSI_gscOnPlayerEnterRaceCP));
			// VERY special case.  The space used to hold the hook name is not
			// long enough to hold the original callback's full name!  In this
			// case we point the function header at somewhere deep inside the
			// DAT segment, not in the nametable, after first generating our new
			// function name in C order not packed PAWN order.
			#emit CONST.pri  YSI_gscOnPlayerEnterRaceCP
			#emit STOR.S.pri idx
			idx -= AMX_BASE_ADDRESS,
			AMX_Write(original + 4, idx);
		}
		else if (!strcmp(ref2, YSI_gscOnPlayerLeaveRaceCP))
		{
			Hooks_ForceReverse(YSI_gscOnPlayerLeaveRaceCP);
			#emit CONST.pri  YSI_gscOnPlayerLeaveRaceCP
			#emit STOR.S.pri idx
			idx -= AMX_BASE_ADDRESS,
			AMX_Write(original + 4, idx);
		}
		else if (!strcmp(ref2, YSI_gscOnScriptExit))
		{
			Hooks_ForceReverse(YSI_gscOnScriptExit);
			#emit CONST.pri  YSI_gscOnScriptExit
			#emit STOR.S.pri idx
			idx -= AMX_BASE_ADDRESS,
			AMX_Write(original + 4, idx);
		}
		else
		{
			P:5("Hooks_GetSame: WRITE: %08x %08x: %s (%d)", AMX_Read(original + 4), AMX_Read(AMX_BASE_ADDRESS + AMX_Read(original + 4)), unpack(ref2), idx);
			AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(original + 4), ref2, idx);
		}
	}
	// Work out what the FIRST used slot is.
	pure = same[0] ? 0 : (same[1] ? 1 : 2);
	// Write our new function (HARD).
	entry = Hooks_WriteFunction(same[pure], sameCount - pure, Hooks_SpecialReturns(ref));
	if (entry)
	{
		// Point "original"'s function pointer to the new function.
		idx = CGen_GetCodeSpace() - AMX_HEADER_COD,
		AMX_Write(original, idx);
		// Save the address for hooks later.  These three can't be done normally
		// because they have already been started by this point.  I did use
		// "CallLocalFunction" but that caused issues with "y_malloc".
		switch (init)
		{
			case 0b0001: YSI_g_sOnScriptInit = idx;
			case 0b0010: YSI_g_sOnFilterScriptInit = idx;
			case 0b0100: YSI_g_sOnGameModeInit = idx;
		}
		CGen_AddCodeSpace(entry);
	}
	else
	{
		idx = AMX_Read(original);
		switch (init)
		{
			case 0b0001: YSI_g_sOnScriptInit = idx;
			case 0b0010: YSI_g_sOnFilterScriptInit = idx;
			case 0b0100: YSI_g_sOnGameModeInit = idx;
		}
	}
}

/*

    88        88                         88                   
    88        88                         88                   
    88        88                         88                   
    88aaaaaaaa88  ,adPPYba,   ,adPPYba,  88   ,d8  ,adPPYba,  
    88""""""""88 a8"     "8a a8"     "8a 88 ,a8"   I8[    ""  
    88        88 8b       d8 8b       d8 8888[      `"Y8ba,   
    88        88 "8a,   ,a8" "8a,   ,a8" 88`"Yba,  aa    ]8I  
    88        88  `"YbbdP"'   `"YbbdP"'  88   `Y8a `"YbbdP"'  

*/

public OnScriptInit()
{
	P:2("Hooks_OnScriptInit called");
	new
		func[32],
		entry,
		idx;
	P:C(for (idx = 0; ((idx = AMX_GetPublicEntry(idx, entry))); ) { Hooks_GetName(entry, func); P:5("Hooks_OnScriptInit: %03d) %s (%08x) = %08x", idx - 1, unpack(func), Hooks_GetAddr(entry + 4), Hooks_GetAddr(entry)); });
	// Find all hook functions in order (at least find the first one in a set).
	P:C(idx=0;);
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
	P:C(for (idx = 0; ((idx = AMX_GetPublicEntry(idx, entry))); ) { Hooks_GetName(entry, func); P:5("Hooks_OnScriptInit: %03d) %s (%08x) = %08x", idx - 1, unpack(func), Hooks_GetAddr(entry + 4), Hooks_GetAddr(entry)); });
	// Detect when there are no hooks for the init functions.
	if (!YSI_g_sOnFilterScriptInit) AMX_GetPublicPointer(0, YSI_g_sOnFilterScriptInit, "S@@_OnFilterScriptInit", true);
	if (!YSI_g_sOnGameModeInit) AMX_GetPublicPointer(0, YSI_g_sOnGameModeInit, "S@@_OnGameModeInit", true);
	if (!YSI_g_sOnScriptInit) AMX_GetPublicPointer(0, YSI_g_sOnScriptInit, "S@@_OnScriptInit", true);
	// Old method so we can hook it!
	if (YSI_g_sOnScriptInit)
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sOnScriptInit
		#emit SCTRL      6
	}
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
	P:1("Hooks_OnScriptInit end");
	return ALS_R_ScriptInit;
}

#if defined _ALS_OnScriptInit
	#undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit S@@_OnScriptInit

forward S@@_OnScriptInit();

/**--------------------------------------------------------------------------**\
<summary>OnFilterScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	This is here PURELY to be hooked.
</remarks>
\**--------------------------------------------------------------------------**/

public OnFilterScriptInit()
{
	if (YSI_g_sOnFilterScriptInit)
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sOnFilterScriptInit
		#emit SCTRL      6
		#emit RETN
	}
	return ALS_R_FilterScriptInit;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit S@@_OnFilterScriptInit
forward S@@_OnFilterScriptInit();

/**--------------------------------------------------------------------------**\
<summary>OnGameModeInit</summary>
<returns>
	-
</returns>
<remarks>
	This is here PURELY to be hooked.
</remarks>
\**--------------------------------------------------------------------------**/

public OnGameModeInit()
{
	if (YSI_g_sOnGameModeInit)
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sOnGameModeInit
		#emit SCTRL      6
		#emit RETN
	}
	return ALS_R_GameModeInit;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit S@@_OnGameModeInit

forward S@@_OnGameModeInit();

