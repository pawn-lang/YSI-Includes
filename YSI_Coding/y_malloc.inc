#if defined _INC_y_malloc
	#endinput
#endif
#define _INC_y_malloc

/**
 * <library name="y_malloc">
 * <section>
 *  Description
 * </section>
 *  Functions for using malloc/calloc/free type functions in PAWN.
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="malloc">Allocate a block of memory (may be inline).</symbol>
 *  <symbol name="calloc">Allocate a block of memory and blank.</symbol>
 *  <symbol name="free">Free an allocated block of memory (may be inline).</symbol>
 *  <symbol name="Malloc_Set">Set a value in an allocated array (may be inline).</symbol>
 *  <symbol name="Malloc_Get">Get a value in an allocated array (may be inline).</symbol>
 *  <symbol name="Malloc_SetS">Set a string in an allocated array.</symbol>
 *  <symbol name="Malloc_GetS">Get a string in an allocated array.</symbol>
 *  <symbol name="Malloc_Allocate">Do the memory allocation (may be static).</symbol>
 *  <symbol name="Malloc_Free">Do the memory freeing (may be static).</symbol>
 *  <symbol name="Malloc_SlotSize">Get the size of an allocated block (may be inline).</symbol>
 *  <symbol name="Malloc_NewS">Allocate for and store a given string.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Malloc_Allocate">Do the memory allocation (may be stock).</symbol>
 *  <symbol name="Malloc_Free">Do the memory freeing (may be stock).</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="mget">Get data from an allocation unit.</symbol>
 *  <symbol name="mset">Set data in an allocation unit.</symbol>
 *  <symbol name="mgets">Get a string from an allocation unit.</symbol>
 *  <symbol name="msets">Set a string in an allocation unit.</symbol>
 *  <symbol name="malloc">Allocate a block of memory (may be stock).</symbol>
 *  <symbol name="free">Free an allocated block of memory (may be stock).</symbol>
 *  <symbol name="Malloc_Set">Set a value in an allocated array (may be stock).</symbol>
 *  <symbol name="Malloc_Get">Get a value in an allocated array (may be stock).</symbol>
 *  <symbol name="Malloc_NextSlot">Get the next free data block.</symbol>
 *  <symbol name="Malloc_GetSlotSize">Get the size of a slot.</symbol>
 *  <symbol name="Malloc_SetSlotSize">Set the size of a block.</symbol>
 *  <symbol name="Malloc_GetData">Direct data access getter.</symbol>
 *  <symbol name="Malloc_SetData">Direct data access setter.</symbol>
 *  <symbol name="Malloc_SlotSize">Get the size of an allocated block (may be stock).</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MALLOC_KB_TO_CELL">Multiplication value to convert kb to cells.</symbol>
 *  <symbol name="NO_ALLOC">A failed allocation (NULL, but YSI already has NULL).</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="Alloc">An allocated block handle variable.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Global
 * </subsection><ul>
 *  <symbol name="YSI_gMallocMemory">Stores the data (may be static).</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_gMallocMemory">Stores the data (may be global).</symbol>
 *  <symbol name="_YSI_g_sUnusedStart">Start of free memory.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="MALLOC_MEMORY">Number of cells to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_KB">Number of killobytes to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_B">Number of bytes to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_MB">Number of megabytes to reserve.</symbol>
 *  <symbol name="YSI_MALLOC_SECURE">Use enhanced bounds checking.</symbol>
 *  <symbol name="YSI_MALLOC_NO_SHORT">Avoid conflicts with mget/mset.</symbol>
 * </ul>
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
	Portions created by the Initial Developer are Copyright C 2011
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

#include "..\YSI_Internal\y_compilerdata"

#if defined YSI_MALLOC_SECURE
	#error YSI_MALLOC_SECURE has been removed.
#endif

#include "..\YSI_Internal\y_version"
#include "..\YSI_Internal\y_funcinc"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Core\y_als"
#include "..\YSI_Core\y_utils"

#include "..\YSI_Internal\y_thirdpartyinclude"

#define GB_TO_MB(%0) ((%0) * 1024)

#define MB_TO_KB(%0) ((%0) * 1024)
#define GB_TO_KB(%0) ((%0) * 1024 * 1024)

#define KB_TO_BYTE(%0) ((%0) * 1024)
#define MB_TO_BYTE(%0) ((%0) * 1024 * 1024)
#define GB_TO_BYTE(%0) ((%0) * 1024 * 1024 * 1024)

#define BYTE_TO_CELL(%0) ((%0) * 8 / cellbits)
#define KB_TO_CELL(%0)   BYTE_TO_CELL(KB_TO_BYTE(%0))
#define MB_TO_CELL(%0)   BYTE_TO_CELL(MB_TO_BYTE(%0))
#define GB_TO_CELL(%0)   BYTE_TO_CELL(GB_TO_BYTE(%0))

#define NO_ALLOC (Alloc:0)

#if !defined MALLOC_MEMORY
	#if defined MALLOC_MEMORY_GB
		#define MALLOC_MEMORY GB_TO_CELL(MALLOC_MEMORY_GB)
	#elseif defined MALLOC_MEMORY_MB
		#define MALLOC_MEMORY MB_TO_CELL(MALLOC_MEMORY_MB)
	#elseif defined MALLOC_MEMORY_KB
		#define MALLOC_MEMORY KB_TO_CELL(MALLOC_MEMORY_KB)
	#elseif defined MALLOC_MEMORY_B
		#define MALLOC_MEMORY BYTE_TO_CELL(MALLOC_MEMORY_B)
	#else
		#define MALLOC_MEMORY MB_TO_CELL(16)
	#endif
#endif

#if defined YSI_NO_HEAP_MALLOC
	#if defined DYNAMIC_MEMORY
		#pragma dynamic DYNAMIC_MEMORY
		#define dynamic dynamic_is_now_DYNAMIC_MEMORY_ // See below...
	#endif
#else
	// Allocate extra memory for the normal stack and heap (64k, 16 times the
	// size of the default stack)!
	#if !defined DYNAMIC_MEMORY
		#define DYNAMIC_MEMORY (65536)
	#endif
	#pragma dynamic MALLOC_MEMORY + DYNAMIC_MEMORY
	
	// ====================================================================== //
	//                                                                        //
	//                                 IMPORTANT!                             //
	//                                                                        //
	// ====================================================================== //
	#define dynamic dynamic_is_now_DYNAMIC_MEMORY_                            //
	// ====================================================================== //
	//                                                                        //
	// dynamic_is_now_DYNAMIC_MEMORY_                                         //
	//                                                                        //
	// If you get a warning or error about "dynamic_is_now_DYNAMIC_MEMORY_",  //
	// hopefully (though doubtfully) you searched for something related to it //
	// and found this.  If you are slightly confused, just remember that any  //
	// reference to that variable is actually a reference to a variable       //
	// called "dynamic", and so the error/warning refers to that.             //
	//                                                                        //
	// _is_now_DYNAMIC_MEMORY_                                                //
	//                                                                        //
	// If you get an error or warning about "_is_now_DYNAMIC_MEMORY_", it is  //
	// because you have tried to use "#pragma dynamic <number>" after         //
	// including "y_malloc" (or another library that eventually includes      //
	// "y_malloc").  Because that library allocates memory from the heap, it  //
	// needs control over how much memory is in the heap to begin with.  You  //
	// do this with "#pragma dynamic <number>", which that library does.      //
	// Because using that a second time somewhere in your mode will break     //
	// "y_malloc", it disables the pragma, and instead outputs that error.    //
	// If you need to increase your stack or heap size (due to a stack/heap   //
	// collision), add this to the very top of your mode:                     //
	//                                                                        //
	//   #define DYNAMIC_MEMORY <number>                                      //
	//                                                                        //
	// ====================================================================== //
#endif

// Sort of "module local" variables.
stock
	__YSI_g_sHeapStart = 0,
	__YSI_g_sUnusedStart = 0;

#define YSI_g_sHeapStart __YSI_g_sHeapStart
#define YSI_g_sUnusedStart __YSI_g_sUnusedStart

forward Alloc:Malloc_Allocate(size, const bool:clear = true);
forward Alloc:calloc(size);

#if defined YSI_NO_HEAP_MALLOC
	new
		YSI_gMallocMemory[MALLOC_MEMORY];
	
	public OnScriptInit()
	{
		YSI_g_sHeapStart = 0;
		YSI_gMallocMemory[0] = MALLOC_MEMORY - 1;
		YSI_g_sUnusedStart = 1;
		memset(YSI_gMallocMemory[1], 0, MALLOC_MEMORY - 1);
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
#else
	new
		YSI_gMallocMemory[1];
	
	// Allocate space on the heap permanently.
	#include "y_malloc/heapalloc"
#endif

// Functions to access the data on the heap.
#include "y_malloc/funcs"
#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_malloc/tests"
#endif

#undef YSI_g_sHeapStart
#undef YSI_g_sUnusedStart

