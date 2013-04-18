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
</remarks>
\**--------------------------------------------------------------------------**/

#include "internal\y_version"
#include "y_debug"
#include "internal\y_funcinc"
#include "internal\y_amx"
#include "y_utils"

#tryinclude "..\amx\opcode"
#include "amx\opcode"
//#tryinclude "..\amx\amx"
//#include "amx\amx"
//#tryinclude "..\amx\stack_dump"
//#include "amx\stack_dump"

#define MALLOC_KB_TO_CELL ((1024 * 8) / cellbits)

#define NO_ALLOC (Alloc:0)

#if !defined MALLOC_MEMORY
	#if defined MALLOC_MEMORY_KB
		#define MALLOC_MEMORY ((MALLOC_MEMORY_KB) * MALLOC_KB_TO_CELL)
	#else
		#if defined MALLOC_MEMORY_MB
			#define MALLOC_MEMORY ((MALLOC_MEMORY_MB) * 1024 * MALLOC_KB_TO_CELL)
		#else
			#if defined MALLOC_MEMORY_B
				#define MALLOC_MEMORY (((MALLOC_MEMORY_B) * 8) / cellbits)
			#else
				#define MALLOC_MEMORY (16 * 1024 * MALLOC_KB_TO_CELL)
			#endif
		#endif
	#endif
#endif

// Allocate extra memory for the normal stack and heap (64k, 16 times the size
// of the default stack)!
#pragma dynamic MALLOC_MEMORY * 4 + 65536

static
	YSI_g_sHeapStart = 0,
	YSI_g_sUnusedStart = MALLOC_MEMORY * 4;

#if defined YSI_MALLOC_SECURE
	#error YSI_MALLOC_SECURE has been removed.
//	static
//#else
//	new
#endif

//new
//	YSI_gMallocMemory[MALLOC_MEMORY] = {MALLOC_MEMORY - 1, 0};

new
	YSI_gMallocMemory[1];

forward Alloc:Malloc_Allocate(size);
forward Alloc:calloc(size);

#if defined YSI_MALLOC_SECURE
	forward Alloc:malloc(size);
#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Finds all "BOUNDS 0" OpCodes in the AMX and rewrites them to "NOP NOP".  The
	byte pattern for this code is "OP_BOUNDS 0", which (AFAIK) can not appear
	anywhere else in the DAT segment.  You can have "OP_BOUNDS" as a parameter
	to something, but it would then be followed by an OpCode of "0", which is
	never valid (OP_NONE).
</remarks>
\**--------------------------------------------------------------------------**/

public OnScriptInit()
{
	new
		Opcode:bounds = RelocateOpcode(OP_BOUNDS),
		nop = _:RelocateOpcode(OP_NOP);
	for (new i = AMX_HEADER_COD, end = AMX_HEADER_DAT - 4; i < end; i += 4)
	{
		// Make sure this isn't just something that LOOKS like "bounds 0",
		// although I don't think there can be because "0" is nota valid
		// opcode.
		if (AMX_Read(i) == _:bounds && AMX_Read(i + 4) == 0)
		{
			// Found a bounds code.
			AMX_Write(i, nop);
			AMX_Write(i += 4, nop);
		}
	}
	// Allocate a ton of space on the heap.
	#emit LCTRL         2
	#emit STOR.pri      YSI_g_sHeapStart
	#emit LOAD.alt      YSI_g_sUnusedStart
	#emit ADD
	#emit SCTRL         2
	// Now there's only the normal bit of the stack and heap left.
	if (YSI_g_sHeapStart != AMX_HEADER_HEA) P:F("y_malloc: Not the first HEAP allocation!");
	P:2("Malloc_OnScriptInit: %d %d %d", YSI_g_sHeapStart, YSI_g_sUnusedStart, AMX_HEADER_HEA); // + AMX_BASE_ADDRESS);
	#emit CONST.alt     YSI_gMallocMemory
	#emit LOAD.pri      YSI_g_sHeapStart
	#emit SUB
	#emit SHR.C.pri     2 // Divide by 4 to get cells.
	#emit STOR.pri      YSI_g_sHeapStart
	YSI_gMallocMemory[YSI_g_sHeapStart] = MALLOC_MEMORY - 1;
	YSI_g_sUnusedStart = YSI_g_sHeapStart + 1;
	// Blank the whole memory.  Not required - the heap is already empty.
	//memset(YSI_gMallocMemory[1], 0, MALLOC_MEMORY - 1);
	#if _DEBUG > 3
		#emit CONST.alt     YSI_gMallocMemory
		#emit STOR.S.alt    nop
		printf("Malloc_OnScriptInit: AMX_HEADER_HEA = %d, YSI_gMallocMemory = %d, YSI_g_sHeapStart = %d", _:AMX_HEADER_HEA, _:nop, YSI_g_sHeapStart);
		printf("Malloc_OnScriptInit: YSI_gMallocMemory + 4 * YSI_g_sHeapStart = %d", nop + 4 * YSI_g_sHeapStart);
	#endif
	// This is never read, but we now have a spare cell because we HAD to
	// allocate an array of some size.
	YSI_gMallocMemory[0] = MALLOC_MEMORY;
	#if defined Malloc_OnScriptInit
		Malloc_OnScriptInit();
	#endif
	return 1;
}

#undef OnScriptInit
#define OnScriptInit Malloc_OnScriptInit
#if defined Malloc_OnScriptInit
	forward Malloc_OnScriptInit();
#endif

static
	//YSI_g_sSolidifyHeap,
	bool:YSI_g_sFILTERSCRIPT = false;

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
		"    | If you use \"crashdetect\", ignore this \"error 12\" message:                |\n" \
		"    |                                                                          |\n" \
		"    |  [debug] Run time error 12: \"(sleep mode)\"                               |\n" \
		"    |  [debug] AMX backtrace:                                                  |",
		//"    |  [debug] #0 <SOME ADDRESS> in %s () from <FILE>%s|\n"
	YSI_g_scErrorMessage3[] = 
		"    |  [debug] #0 <SOME NUMBER> in Malloc_SolidifyHeap () from <YOUR FILE>     |\n" \
		"    |                                                                          |\n" \
		"    | For more information, see the YSI.tl release topic.                      |\n" \
		"    |                                                                          |\n" \
		"    ============================================================================\n" \
		" \n";

/*
static Malloc_GetName0(ss)
{
	new
		ret[27];
	switch (ss)
	{
		case 0: ret = "public OnGameModeInit";
		case 1: ret = "public OnFilterScript";
		case 2: ret = "public Malloc_SolidifyHeap";
		case 3: ret = "main";
	}
	return ret;
}

static Malloc_GetName1(ss)
{
	new
		ret[] = "                        ";
	switch (ss)
	{
		case 2:  ret[2] = '\0';
		case 3:  return ret;
		default: ret[7] = '\0';
	}
	return ret;
}
*/

#define MALLOC_SOLIDIFYHEAP(%0) Malloc_SolidifyHeap() //while(TRUE){print(YSI_g_scErrorMessage1),print(YSI_g_scErrorMessage2),printf(YSI_g_scErrorMessage3,Malloc_GetName0(%0),Malloc_GetName1(%0));sleep cellmax;}
//forward Malloc_SolidifyHeap(ss);
//
static Malloc_SolidifyHeap() //ss)
{
	// This code calls "sleep" a second time.  When "sleep" is called "amx_Exec"
	// sets "amx->reset_hea" to the original value of the heap, so that when the
	// function is resumed and then ends, it can be fully reset.  However, if
	// "amx_Exec" is called a second time before the "sleep" function is resumed
	// then the process will be repeated and "amx->reset_hea" will be replaced
	// by our modified "hea", entirely destroying the original value.  The only
	// place where "sleep" can be resumed is in "main", so we need to make sure
	// that we have fully solidified our new heap value first.  Unfortunately,
	// this function looses us about 20 cells of the stack, but our stack is far
	// more vast than the original anyway.  Now it doesn't.
	print(YSI_g_scErrorMessage1),
	print(YSI_g_scErrorMessage2),
	print(YSI_g_scErrorMessage3);
	//printf(YSI_g_scErrorMessage3, Malloc_GetName0(ss), Malloc_GetName1(ss));
	new
		ss = MALLOC_MEMORY * 4;
	#emit LOAD.pri   AMX_HEADER_HEA
	#emit LOAD.S.alt ss
	#emit ADD
	#emit SCTRL      2 // Set the new heap pointer.
	#emit LOAD.pri   AMX_HEADER_STP
	//#emit POP.alt
	//#emit SUB        // Adjust the stack to keep the return address for "CONT".
	#emit SCTRL      4 // Set the original stack pointer.
	#emit SCTRL      5 // Set the frame pointer.
	// Sleep for about 25 days!
	while (TRUE)
	{
		sleep cellmax;
	}
	//MALLOC_SOLIDIFYHEAP(ss)
	return 0;
}

public OnFilterScriptInit()
{
	#if defined Malloc_OnFilterScriptInit
		Malloc_OnFilterScriptInit();
	#endif
	YSI_g_sFILTERSCRIPT = true;
	//DumpStack();
	//YSI_g_sSolidifyHeap = SetTimerEx("Malloc_SolidifyHeap", 1000, 0, "i", 2);
	return MALLOC_SOLIDIFYHEAP(1);
	//return 0;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Malloc_OnFilterScriptInit
#if defined Malloc_OnFilterScriptInit
	forward Malloc_OnFilterScriptInit();
#endif

public OnGameModeInit()
{
	#if defined Malloc_OnGameModeInit
		Malloc_OnGameModeInit();
	#endif
	if (!YSI_g_sFILTERSCRIPT)
	{
		//YSI_g_sSolidifyHeap = SetTimerEx("Malloc_SolidifyHeap", 1000, 0, "i", 2);
		return MALLOC_SOLIDIFYHEAP(0);
		//return 0;
	}
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Malloc_OnGameModeInit
#if defined Malloc_OnGameModeInit
	forward Malloc_OnGameModeInit();
#endif

main()
{
	//KillTimer(YSI_g_sSolidifyHeap);
	#if defined Malloc_main
		Malloc_main();
	#endif
	//CallLocalFunction("Malloc_main", "");
	//sleep(0);
	return MALLOC_SOLIDIFYHEAP(3);
	//return 0;
	//Malloc_SolidifyHeap(0);
}

#if defined _ALS_main
	#undef main
#else
	#define _ALS_main
#endif
#define main() forward Malloc_main();public Malloc_main()
//#if defined Malloc_main
//	forward Malloc_main();
//#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_GetSlotSize</summary>
<param name="slot">Allocation unit to get the size of.</param>
<returns>
	The size.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Malloc_GetSlotSize(%1) \
	(YSI_gMallocMemory[_:(%1) - 1])

/**--------------------------------------------------------------------------**\
<summary>Malloc_SlotSize</summary>
<param name="slot">Allocation unit to get the size of.</param>
<returns>
	The size.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_SlotSize(slot)
	{
		return Malloc_GetSlotSize(slot);
	}

#else

	#define Malloc_SlotSize(%1) \
		Malloc_GetSlotSize(%1)

#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_NewS</summary>
<param name="string[]">The string to store.</param>
<param name="pack">Whether or not the string will be packed.</param>
<returns>
	0 on fail or a data handle on sucess.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock Alloc:Malloc_NewS(const string[], bool:pack = false) {
	new
		      size = pack ? ((strlen(string) + 1) char) : (strlen(string) + 1),
		Alloc:alloc = Malloc_Allocate(size)
	;
	
	if (alloc) {
		if (pack)
			strpack(YSI_gMallocMemory[_:alloc], string, size);
		else
			strunpack(YSI_gMallocMemory[_:alloc], string, size);
	}
	
	return alloc;
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetSlotSize</summary>
<param name="slot">The allocation unit to set the size of.</param>
<param name="size">The size to set it to.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Malloc_SetSlotSize(%1,%2) \
	YSI_gMallocMemory[_:(%1) - 1] = (%2)

/**--------------------------------------------------------------------------**\
<summary>Malloc_GetData</summary>
<param name="slot">The allocation unit to get data from.</param>
<param name="index">The location in the unit to get.</param>
<returns>
	The data
</returns>
<remarks>
	Basically like Malloc_Get but used internally.
</remarks>
\**--------------------------------------------------------------------------**/

#define Malloc_GetData(%1,%2) \
	(YSI_gMallocMemory[_:((%1)+Alloc:(%2))])

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetData</summary>
<param name="slot">The allocation unit to set in.</param>
<param name="index">Where in the unit to set.</param>
<param name="value">The value to save.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Malloc_SetData(%1,%2,%3) \
	YSI_gMallocMemory[_:((%1)+Alloc:(%2))]=(%3)

/**--------------------------------------------------------------------------**\
<summary>mget</summary>
<param name="slot">The allocation unit to get data from.</param>
<param name="index">The location in the unit to get.</param>
<returns>
	The data
</returns>
<remarks>
	Shorthand for Malloc_Get.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined YSI_MALLOC_NO_SHORT
	#define mget(%1) \
		Malloc_Get(%1)
#endif

/**--------------------------------------------------------------------------**\
<summary>mset</summary>
<param name="slot">The allocation unit to set in.</param>
<param name="index">Where in the unit to set.</param>
<param name="value">The value to save.</param>
<returns>
	-
</returns>
<remarks>
	Shorthand for Malloc_Set.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined YSI_MALLOC_NO_SHORT
	#define mset(%1) \
		Malloc_Set(%1)
#endif

/**--------------------------------------------------------------------------**\
<summary>mgets</summary>
<param name="target[]">Target for the string.</param>
<param name="len">Length of the target.</param>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<returns>
	The data
</returns>
<remarks>
	Shorthand for Malloc_GetS.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined YSI_MALLOC_NO_SHORT
	#define mgets(%1) \
		Malloc_GetS(%1)
	
	#define mgeta(%1) \
		Malloc_GetA(%1)
#endif

/**--------------------------------------------------------------------------**\
<summary>msets</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="str[]">String to insert</param>
<returns>
	-
</returns>
<remarks>
	Shorthand for Malloc_SetS.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined YSI_MALLOC_NO_SHORT
	#define msets(%1) \
		Malloc_SetS(%1)
	
	#define mseta(%1) \
		Malloc_SetA(%1)
#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_NextSlot</summary>
<param name="slot">The unit to get the one after of.</param>
<returns>
	-
</returns>
<remarks>
	Gets the next free block of memory after the current one.
</remarks>
\**--------------------------------------------------------------------------**/

#define Malloc_NextSlot(%1) \
	(YSI_gMallocMemory[(%1)])

/**--------------------------------------------------------------------------**\
<summary>Malloc_Get</summary>
<param name="array">Data unit to get information from.</param>
<param name="index">Index in the unit.</param>
<returns>
	Data.
</returns>
<remarks>
	Displays errors in secure mode.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Get(Alloc:array, index)
	{
		if (index >= 0 && index < Malloc_GetSlotSize(_:array))
		{
			return Malloc_GetData(_:array, index);
		}
		P:C(else P:E("Array read index out of bounds: %d[%d]", _:array, index););
		return 0;
	}

#else

	#define Malloc_Get(%1,%2) \
		Malloc_GetData(%1, %2)

#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_Set</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="value">Value to insert</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Set(Alloc:array, index, value)
	{
		if (index >= 0 && index < Malloc_GetSlotSize(_:array))
		{
			return Malloc_SetData(_:array, index, value);
		}
		P:C(else P:E("Array write index out of bounds: %d[%d]", _:array, index););
		return 0;
	}

#else

	#define Malloc_Set(%1,%2,%3) \
		Malloc_SetData(%1, %2, %3)

#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_GetS</summary>
<param name="target[]">Target for the string.</param>
<param name="len">Length of the target.</param>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.  Gets a string.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_GetS(target[], length, Alloc:array, index)
{
	P:3("Malloc_GetS: array = %d, index = %d.", _:array, index);
	if (index >= 0)
	{
		new
			size = Malloc_GetSlotSize(_:array);
		P:5("Malloc_GetS: size = %d.", size);
		new
			i = 0;
		index += _:array;
		size += _:array;
		while (i < length && index < size)
		{
			P:6("Malloc_GetS: i = %d.", i);
			if (!(target[i++] = YSI_gMallocMemory[index++]))
			{
				return 1;
			}
		}
		#if defined YSI_MALLOC_SECURE
			P:C(if(index == size)P:E("Out of data (%d, %d)", _:array, index););
			P:C(if(i == length)P:E("Out of buffer space"););
		#endif
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetS</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="str[]">String to insert</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.  Inserts a string.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_SetS(Alloc:array, index, const str[])
{
	P:3("Malloc_SetS called: %d, %d, %s", _:array, index, str);
	if (index >= 0 && index + strlen(str) + 1 <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetS: In check.");
		index += _:array;
		YSI_gMallocMemory[index] = 0;
		strcat(YSI_gMallocMemory[index], str, cellmax);
		//while ((YSI_gMallocMemory[index++] = str[i++])) {}
	}
	#if defined YSI_MALLOC_SECURE
		P:C(else P:E("String copy failed (%s)", str););
	#endif
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetVAS</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="arg">Offset in the stack of the string to store.</param>
<returns>
	-
</returns>
<remarks>
	Inserts a string by stack offset for use in vararg functions.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_SetVAS(Alloc:array, index, arg)
{
	P:3("Malloc_SetVAS called: %d, %d, %d", _:array, index, arg);
	new
		len;
	#emit LOAD.S.pri arg
	#emit SMUL.C     4
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADD.C      12
	#emit LOAD.I
	// For later reuse.
	#emit STOR.S.pri arg
	#emit PUSH.pri
	#emit PUSH.C     4
	#emit SYSREQ.C   strlen
	#emit STACK      8
	#emit STOR.S.pri len
	if (index >= 0 && index + (++len) <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetVAS: In check.");
		index += _:array;
		YSI_gMallocMemory[index] = 0;
		// Blank and copy the string.
		//#emit LOAD.S.pri arg
		//#emit SMUL.C     4
		//#emit LOAD.S.alt 0
		//#emit ADD
		//#emit ADD.C      12
		//#emit LOAD.I
		// Skip the code above the second time now (store the true source
		// address in "arg" the first time).
		#emit PUSH.S     len
		#emit PUSH.S     arg
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri index
		#emit IDXADDR
		#emit MOVE.alt
		#emit CONST.pri  0
		#emit STOR.I
		#emit PUSH.alt
		#emit PUSH.C     12
		#emit SYSREQ.C   strcat
		#emit STACK      16
		//strcat(YSI_gMallocMemory[index], str, cellmax);
	}
	#if defined YSI_MALLOC_SECURE
		P:C(else P:E("String copy failed (%s)", str););
	#endif
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_GetA</summary>
<param name="target[]">Target for the array.</param>
<param name="len">Length of the target.</param>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.  Gets an array.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_GetA(target[], length, Alloc:array, index)
{
	P:3("Malloc_GetA called: array = %d, index = %d.", _:array, index);
	if (index >= 0)
	{
		new
			size = Malloc_GetSlotSize(_:array);
		P:5("Malloc_GetA: size = %d.", size);
		memcpy(target, YSI_gMallocMemory, index + _:array, size * 4, length);
		#if defined YSI_MALLOC_SECURE
			P:C(if(length > size)P:E("Out of buffer space."););
		#endif
		return 1;
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetA</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="str[]">Array to insert.</param>
<param name="len">Length of the array.</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.  Inserts an array.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_SetA(Alloc:array, index, const str[], len)
{
	P:3("Malloc_SetA: array = %d, index = %d.", _:array, index);
	if (index >= 0)
	{
		new
			size = Malloc_GetSlotSize(_:array);
		P:5("Malloc_SetA: size = %d.", size);
		memcpy(YSI_gMallocMemory[index + _:array], str, 0, len * 4, size - index);
		#if defined YSI_MALLOC_SECURE
			P:C(if(len > size - index)P:E("Out of buffer space."););
		#endif
	}
}

/**--------------------------------------------------------------------------**\
<summary>Malloc_SetVAA</summary>
<param name="array">Data unit to put information in.</param>
<param name="index">Index in the unit.</param>
<param name="arg">Offset in the stack of the array to store.</param>
<returns>
	-
</returns>
<remarks>
	Inserts an array by stack offset for use in vararg functions.
</remarks>
\**--------------------------------------------------------------------------**/

stock Malloc_SetVAA(Alloc:array, index, arg)
{
	P:3("Malloc_SetVAA called: %d, %d, %d", _:array, index, arg);
	new
		len;
	#emit LOAD.S.pri arg
	#emit ADD.C      1
	#emit SMUL.C     4
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADD.C      12
	#emit LOAD.I
	#emit LOAD.I
	// For later reuse.
	#emit STOR.S.pri len
	printf("%d", len);
	if (index >= 0 && index + len <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetVAA In check.");
		index += _:array;
		// Skip the code above the second time now (store the true source
		// address in "arg" the first time).
		#emit LOAD.S.pri len
		#emit PUSH.pri
		#emit SMUL.C     4
		#emit PUSH.pri
		#emit PUSH.C     0
		// Source.
		#emit LOAD.S.pri arg
		#emit SMUL.C     4
		#emit LOAD.S.alt 0
		#emit ADD
		#emit ADD.C      12
		#emit LOAD.I
		#emit PUSH.pri
		// Destination.
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri index
		#emit IDXADDR
		#emit MOVE.alt
		#emit CONST.pri  0
		#emit STOR.I
		#emit PUSH.alt
		// GO!
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
		//strcat(YSI_gMallocMemory[index], str, cellmax);
	}
	#if defined YSI_MALLOC_SECURE
		P:C(else P:E("Array copy out of memory."););
	#endif
}

/**--------------------------------------------------------------------------**\
<summary>malloc</summary>
<param name="size">Size of memory to allocate.</param>
<returns>
	0 on fail or a data handle on sucess.
</returns>
<remarks>
	Displays errors in secure mode.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Alloc:malloc(size)
	{
		new
			Alloc:slot = Malloc_Allocate(size);
		P:C(if(!slot)P:E("Allocation failed (%d)", size););
		return slot;
	}

#else

	#define malloc(%1) \
		Malloc_Allocate(%1)

#endif

/**--------------------------------------------------------------------------**\
<summary>calloc</summary>
<param name="size">Size of memory to allocate.</param>
<returns>
	0 on fail or a data handle on sucess.
</returns>
<remarks>
	Displays errors in secure mode.  Blanks allocated mmeory.
</remarks>
\**--------------------------------------------------------------------------**/


stock Alloc:calloc(size)
{
	new
		Alloc:slot = Malloc_Allocate(size);
	if (slot)
	{
		new
			temp = _:slot;
		while (size--)
		{
			YSI_gMallocMemory[temp++] = 0;
		}
	}
	#if defined YSI_MALLOC_SECURE
		P:C(if(!slot)P:E("Allocation failed (%d)", size););
	#endif
	return slot;
}

/**--------------------------------------------------------------------------**\
<summary>free</summary>
<param name="slot">Slot of memory to free up.</param>
<returns>
	-
</returns>
<remarks>
	Displays errors in secure mode.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock free(Alloc:slot)
	{
		if (!slot || !Malloc_GetSlotSize(_:slot))
		{
			P:1("Free failed (%d)", _:slot);
			return 0;
		}
		return Malloc_Free(slot);
	}

#else

	#define free(%1) \
		Malloc_Free(%1)

#endif

/**--------------------------------------------------------------------------**\
<summary>Malloc_Allocate</summary>
<param name="size">Ammount of memory to allocate IN CELLS.</param>
<returns>
	Memory identifier.
</returns>
<remarks>
	The size check should never fail, if there's only 1 cell
	extra somewhere just sneak it onto the end of an array,
	if the user does proper bounds checking it shouldn't
	matter.
	
	Implementation code for malloc().
	
	This code will find an area in memory with sufficient
	space to store the given data and 
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Alloc:Malloc_Allocate(size)
		{
			P:2("Malloc_Allocate called: %d, %d, %d, %d", size, YSI_g_sUnusedStart, YSI_g_sHeapStart, Malloc_GetSlotSize(YSI_g_sUnusedStart));
			new
				slot = YSI_g_sUnusedStart,
				p = YSI_g_sHeapStart, // Was "0", now an offset to the heap.
				cs;
			while (slot)
			{
				cs = Malloc_GetSlotSize(slot);
				if (!cs)
				{
					return NO_ALLOC;
				}
				if (cs >= size)
				{
					break;
				}
				p = slot;
				slot = Malloc_NextSlot(slot);
			}
			if (slot)
			{
				if (cs == size + 1)
				{
					size++;
				}
				if (cs == size)
				{
					if (p != YSI_g_sHeapStart)
					{
						Malloc_SetData(Alloc:p, 0, Malloc_NextSlot(slot));
					}
					else
					{
						YSI_g_sUnusedStart = Malloc_NextSlot(slot);
					}
				}
				else
				{
					Malloc_SetSlotSize(slot, size);
					size++;
					cs -= size;
					size += slot;
					if (p != YSI_g_sHeapStart)
					{
						Malloc_SetData(Alloc:p, 0, size);
					}
					else
					{
						YSI_g_sUnusedStart = size;
					}
					Malloc_SetData(Alloc:size, 0, Malloc_NextSlot(slot));
					Malloc_SetSlotSize(size, cs);
				}
				return Alloc:slot;
			}
			return NO_ALLOC;
		}

/**--------------------------------------------------------------------------**\
<summary>Malloc_Free</summary>
<param name="slot">Memory allocation unit to release</param>
<returns>
	-
</returns>
<remarks>
	Implementation code for free().
</remarks>
\**--------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Malloc_Free(Alloc:slot)
		{
			P:4("Malloc_Free called: %d", _:slot);
			new
				size = Malloc_GetSlotSize(_:slot),
				p = YSI_g_sUnusedStart,
				l = YSI_g_sHeapStart; // Was "0", now an offset to the heap.
			P:5("Malloc_Free: size = %d", size);
			if (p)
			{
				while (p && p < _:slot)
				{
					l = p;
					p = Malloc_NextSlot(p);
				}
				if (p)
				{
					if (l == YSI_g_sHeapStart)
					{
						YSI_g_sUnusedStart = _:slot;
					}
					else
					{
						new
							tmp = Malloc_GetSlotSize(l);
						if (l + tmp + 1 == _:slot)
						{
							size += tmp + 1;
							Malloc_SetSlotSize(l, size);
							slot = Alloc:l;
						}
						else
						{
							Malloc_SetData(slot, 0, p);
							Malloc_SetData(Alloc:l, 0, _:slot);
						}
					}
					if (_:slot + size + 1 == p)
					{
						Malloc_SetSlotSize(_:slot, Malloc_GetSlotSize(p) + size + 1);
						Malloc_SetData(slot, 0, Malloc_NextSlot(p));
					}
					else
					{
						Malloc_SetData(slot, 0, p);
					}
				}
				else
				{
					new
						tmp = Malloc_GetSlotSize(l);
					if (l + tmp + 1 == _:slot)
					{
						Malloc_SetSlotSize(l, size + tmp + 1);
					}
					else
					{
						Malloc_SetData(slot, 0, 0);
						Malloc_SetData(Alloc:l, 0, _:slot);
					}
				}
			}
			else
			{
				YSI_g_sUnusedStart = _:slot;
				Malloc_SetData(slot, 0, 0);
			}
			return 1;
		}
