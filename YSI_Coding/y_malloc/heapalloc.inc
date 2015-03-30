/**--------------------------------------------------------------------------**\
					===================================
					Y Sever Includes - Malloc Functions
					===================================
Description:
	Functions for using malloc/calloc/free type functions in PAWN.
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
	
	The Original Code is the YSI malloc include.
	
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
	0.1
Changelog:
	02/12/11:
		Added variable argument functions.
	22/12/08:
		First version.
Functions:
	Public
		-
	Core:
		-
	Stock:
		malloc - Allocate a block of memory (may be inline).
		calloc - Allocate a block of memory and blank.
		free - Free an allocated block of memory (may be inline).
		Malloc_Set - Set a value in an allocated array (may be inline).
		Malloc_Get - Get a value in an allocated array (may be inline).
		Malloc_SetS - Set a string in an allocated array.
		Malloc_GetS - Get a string in an allocated array.
		Malloc_Allocate - Do the memory allocation (may be static).
		Malloc_Free - Do the memory freeing (may be static).
		Malloc_SlotSize - Get the size of an allocated block (may be inline).
		Malloc_NewS - Allocate for and store a given string.
	Static:
		Malloc_Allocate - Do the memory allocation (may be stock).
		Malloc_Free - Do the memory freeing (may be stock).
	Inline:
		mget - Get data from an allocation unit.
		mset - Set data in an allocation unit.
		mgets - Get a string from an allocation unit.
		msets - Set a string in an allocation unit.
		malloc - Allocate a block of memory (may be stock).
		free - Free an allocated block of memory (may be stock).
		Malloc_Set - Set a value in an allocated array (may be stock).
		Malloc_Get - Get a value in an allocated array (may be stock).
		Malloc_NextSlot - Get the next free data block.
		Malloc_GetSlotSize - Get the size of a slot.
		Malloc_SetSlotSize - Set the size of a block.
		Malloc_GetData - Direct data access getter.
		Malloc_SetData - Direct data access setter.
		Malloc_SlotSize - Get the size of an allocated block (may be stock).
	API:
		-
Callbacks:
	-
Definitions:
	MALLOC_KB_TO_CELL - Multiplication value to convert kb to cells.
	NO_ALLOC - A failed allocation (NULL, but YSI already has NULL).
Enums:
	-
Macros:
	-
Tags:
	Alloc - An allocated block handle variable.
Variables:
	Global:
		YSI_gMallocMemory - Stores the data (may be static).
	Static:
		YSI_gMallocMemory - Stores the data (may be global).
		YSI_g_sUnusedStart - Start of free memory.
Commands:
	-
Compile options:
	MALLOC_MEMORY - Number of cells to reserve.
	MALLOC_MEMORY_KB - Number of killobytes to reserve.
	MALLOC_MEMORY_B - Number of bytes to reserve.
	MALLOC_MEMORY_MB - Number of megabytes to reserve.
	YSI_MALLOC_SECURE - Use enhanced bounds checking.
	YSI_MALLOC_NO_SHORT - Avoid conflicts with mget/mset.
Operators:
	-
\**--------------------------------------------------------------------------**/

main()
{
	P:1("Malloc_main called");
	Malloc_TrySetup();
	#if defined Malloc_main
		Malloc_main();
	#endif
	return 1;
	//return MALLOC_SOLIDIFYHEAP(3);
}

#if defined _ALS_main
	#undef main
#else
	#define _ALS_main
#endif
#define main() forward Malloc_main();public Malloc_main()


/**--------------------------------------------------------------------------**\
<summary>Malloc_FindStackTop</summary>
<returns>
	-
</returns>
<remarks>
	Loop back up through the stack and find the start of the current stack.  If
	it doesn't equal the top of the true stack then we've been called via
	"CallLocalFunction" at some point and thus MAY get some memory corruption.
	
	Based on ZeeX's GetStackTrace, but gets frames instead of returns.
</remarks>
\**--------------------------------------------------------------------------**/

static Malloc_FindStackTop()
{
	new
		frm_addr;
	#emit LCTRL       5
	#emit STOR.S.pri  frm_addr
	// Loop until we hit a return address of 0.
	while (GetFrameReturn(frm_addr))
	{
		#emit LREF.S.pri  frm_addr
		#emit STOR.S.pri  frm_addr
	}
	// We can't accurately get the number or parameters because of y_hooks :(.
	return frm_addr + 12;
}

/**--------------------------------------------------------------------------**\
<summary>OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Finds all "BOUNDS 0" OpCodes in the AMX and rewrites them to "NOP NOP".  The
	byte pattern for this code is "OP_BOUNDS 0", which (AFAIK) can not appear
	anywhere else in the DAT segment.  You can have "OP_BOUNDS" as a parameter
	to something, but it would then be followed by an OpCode of "0", which is
	never valid (OP_NONE).
	
	I've tried to make this as resiliant as possible to being called via
	"CallLocalFunction" as not the first callback in the script but there may
	still be a few problems - we won't see till people start testing I guess...
</remarks>
\**--------------------------------------------------------------------------**/

public OnScriptInit()
{
	P:1("Malloc_OnScriptInit called");
	// First ever LEGITIMATE call to "heapspace"!
	if (heapspace() < MALLOC_MEMORY + 4 * 1024)
	{
		P:E("heapspace too low for y_malloc: Did you use \"#pragma dynamic\"?");
	}
	new
		Opcode:bounds = RelocateOpcode(OP_BOUNDS),
		nop = _:RelocateOpcode(OP_NOP);
	for (new i = AMX_HEADER_COD, end = AMX_HEADER_DAT - 4; i < end; i += 4)
	{
		// Make sure this isn't just something that LOOKS like "bounds 0",
		// although I don't think there can be because "0" is not a valid
		// opcode.
		if (AMX_Read(i) == _:bounds && AMX_Read(i + 4) == 0)
		{
			// Found a bounds code.
			AMX_Write(i, nop);
			AMX_Write(i += 4, nop);
		}
	}
	Malloc_TrySetup();
	#if defined Malloc_OnScriptInit
		Malloc_OnScriptInit();
	#endif
	SetTimer("Malloc_SolidifyTimer", 0, 0);
	SetTimer("Malloc_SolidifyTimer", 0, 0);
	return 1;
}

#undef OnScriptInit
#define OnScriptInit Malloc_OnScriptInit
#if defined Malloc_OnScriptInit
	forward Malloc_OnScriptInit();
#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_TrySetup</summary>
<returns>
	-
</returns>
<remarks>
	Move the heap pointer up a load.  This is called multiple times at the start
	of the mode because we need to beat protections added in by the virtual
	machine to steal away its heap area.
</remarks>
\**--------------------------------------------------------------------------**/

static Malloc_TrySetup()
{
	P:1("Malloc_TrySetup called");
	new
		temp;
	#emit LCTRL       3
	#emit STOR.S.pri  temp
	if (temp > Malloc_FindStackTop() + 4)
	{
		P:W("y_malloc set up via \"CallLocalFunction\", memory corruption is a remote possibility");
	}
	temp = MALLOC_MEMORY * 4;
	// Allocate a ton of space on the heap.
	#emit LCTRL         2
	#emit LOAD.S.alt    temp
	#emit ADD
	#emit STOR.S.pri    temp
	// Now there's only the normal bit of the stack and heap left.
	if (temp == AMX_HEADER_HEA + MALLOC_MEMORY * 4 * 2)
	{
		// Already allocated and now trying to double allocate.
		return;
	}
	if (temp != AMX_HEADER_HEA + MALLOC_MEMORY * 4)
	{
		P:F("y_malloc: Not the first HEAP allocation!");
		return;
	}
	else
	{
		#emit LOAD.S.pri    temp
		#emit SCTRL         2
		if (YSI_g_sHeapStart) return;
	}
	YSI_g_sHeapStart = temp - MALLOC_MEMORY * 4;
	P:2("Malloc_OnScriptInit: %d %d %d", YSI_g_sHeapStart, MALLOC_MEMORY * 4, AMX_HEADER_HEA);
	#emit CONST.alt     YSI_gMallocMemory
	#emit LOAD.pri      __YSI_g_sHeapStart
	#emit SUB
	#emit SHR.C.pri     2 // Divide by 4 to get cells.
	#emit STOR.pri      __YSI_g_sHeapStart
	YSI_gMallocMemory[YSI_g_sHeapStart] = MALLOC_MEMORY - 1;
	YSI_g_sUnusedStart = YSI_g_sHeapStart + 1;
	// Blank the whole memory.  Maybe required if the heap has been used
	// already (better to be safe than sorry).
	memset(YSI_gMallocMemory[YSI_g_sHeapStart + 1], 0, MALLOC_MEMORY - 1);
	#if _DEBUG > 3
		// The "#if" is actually ignored by these "#emit" codes, as always.
		#emit CONST.alt     YSI_gMallocMemory
		#emit STOR.S.alt    temp
		printf("Malloc_OnScriptInit: AMX_HEADER_HEA = %d, YSI_gMallocMemory = %d, YSI_g_sHeapStart = %d", _:AMX_HEADER_HEA, temp, YSI_g_sHeapStart);
		printf("Malloc_OnScriptInit: YSI_gMallocMemory + 4 * YSI_g_sHeapStart = %d", temp + 4 * YSI_g_sHeapStart);
	#endif
	// This is never read, but we now have a spare cell because we HAD to
	// allocate an array of some size.
	YSI_gMallocMemory[0] = MALLOC_MEMORY;
}

static
	//YSI_g_sSolidifyHeap,
	YSI_g_sHeapSetup = 0;

static const
	// Split in to three because of line length limits.
	YSI_g_scErrorMessage1[] = 
		" \n" \
		" \n" \
		"    ============================================================================\n" \
		"    |                                                                          |\n" \
		"    |                            ******************                            |\n" \
		"    |                            * VERY IMPORTANT *                            |\n" \
		"    |                            ******************                            |",
	YSI_g_scErrorMessage2[] = 
		"    |                                                                          |\n" \
		"    | Your \"crashdetect\" plugin is out of date, ignore the \"error 12\" above!   |\n" \
		"    |                                                                          |\n" \
		"    |  [debug] Run time error 12: \"(sleep mode)\"                               |\n" \
		"    |  [debug] AMX backtrace:                                                  |",
		//"    |  [debug] #0 <SOME ADDRESS> in %s () from <FILE>%s|\n"
	YSI_g_scErrorMessage3[] = 
		"    |  [debug] #0 <HEX NUMBER> in public Malloc_SolidifyTimer ()               |\n" \
		"    |                                                                          |\n" \
		"    | For more information, see the YSI.tl release topic.                      |\n" \
		"    |                                                                          |\n" \
		"    ============================================================================\n" \
		" \n";

forward OnRuntimeError(code, &bool:suppress);

public OnRuntimeError(code, &bool:suppress)
{
	// This is called if the "crashdetect" plugin is installed.
	if (code == 12)
	{
		P:0(YSI_g_scErrorMessage1);
		P:0(YSI_g_scErrorMessage2);
		P:0(YSI_g_scErrorMessage3);
	}
	#if defined Malloc_OnRuntimeError
		Malloc_OnRuntimeError(code);
	#endif
	if (code == 12)
	{
		// Make sure our heap is correctly set still...
		return Malloc_SolidifyHeap();
	}
	else return 0;
}
#if defined _ALS_OnRuntimeError
	#undef OnRuntimeError
#else
	#define _ALS_OnRuntimeError
#endif
#define OnRuntimeError Malloc_OnRuntimeError
#if defined Malloc_OnRuntimeError
	forward Malloc_OnRuntimeError(code, &bool:suppress);
#endif

forward Malloc_SolidifyTimer();

public Malloc_SolidifyTimer()
{
	P:1("Malloc_SolidifyTimer called");
	Malloc_TrySetup();
	Malloc_SolidifyHeap();
}

static Malloc_SolidifyHeap()
{
	if (YSI_g_sHeapSetup == 2) return 1;
	++YSI_g_sHeapSetup;
	#emit LCTRL      3
	#emit MOVE.alt
	#emit SCTRL      5
	#emit SCTRL      4 // Set the original stack pointer.
	// Call to save "stk" and "frm", since they aren't in early builds.
	#emit PUSH.C      0
	#emit SYSREQ.C    heapspace // The pre-processor can't touch this.
	#emit STACK       4
	// Unfortunately, "heapspace" has a parameter pushed first so it saves the
	// wrong stack value (the value 4 below where it should be).  The only other
	// opcode that reliably saves "stk" in "amx->stk" without trying to call a
	// native function is "OP_RETN", so let's BADLY invoke it!  Note that we
	// still need the "heapspace" call (or any function call) to save "hea" and
	// "frm", which are NOT saved by "OP_RETN" but are by "OP_SYSREQ_C".
	#emit PUSH.C      0 // No parameters
	#emit LCTRL       6 // Return to the next instruction...
	#emit ADD.C       20
	#emit PUSH.pri
	#emit PUSH.alt      // Same frame.
	#emit RETN
	// "return" to here...
	#emit HALT        12
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_OnPlayerConnect</summary>
<param name="playerid">Player that just connected.</param>
<returns>
	-
</returns>
<remarks>
	This is the only callback that can be called before our timers when the mode
	starts.  Make sure the heap is set up correctly.
</remarks>
\**--------------------------------------------------------------------------**/

forward Malloc_DoPlayerConnect(playerid);

public Malloc_DoPlayerConnect(playerid)
{
	if (YSI_g_sHeapSetup != 2) Malloc_TrySetup();
	// Ensure we only call the originsl.
	return call OnPlayerConnect(playerid);
}
