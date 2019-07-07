#if defined _INC_y_malloc
	#endinput
#endif
#define _INC_y_malloc

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

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Core\y_core\y_thirdpartyinclude"

#if defined YSI_MALLOC_SECURE
	#error YSI_MALLOC_SECURE has been removed.
#endif

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

CHAIN_HOOK(Malloc)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Malloc)

#define MALLOC_FORWARD:%0(%1); \
	forward Malloc_%0(%1); \
	public Malloc_%0(%1) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return 1; } \
	public Malloc_%0(%1) <> { return 1; }

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

forward Alloc:Malloc_Allocate(size, const bool:clear = false);
forward Alloc:calloc(size);

#if defined YSI_NO_HEAP_MALLOC
	new
		YSI_gMallocMemory[MALLOC_MEMORY];
	
	public OnCodeInit()
	{
		YSI_g_sHeapStart = 0;
		YSI_gMallocMemory[0] = MALLOC_MEMORY - 1;
		YSI_g_sUnusedStart = 1;
		#if defined Malloc_OnCodeInit
			Malloc_OnCodeInit();
		#endif
		return 1;
	}
	
	#undef OnCodeInit
	#define OnCodeInit Malloc_OnCodeInit
	#if defined Malloc_OnCodeInit
		forward Malloc_OnCodeInit();
	#endif
#else
	new
		YSI_gMallocMemory[1];
	
	#if !defined _ALS_OnJITCompile
		forward OnJITCompile();
	#endif
	
	public OnJITCompile()
	{
		P:E("y_malloc with JIT requires \"#define YSI_NO_HEAP_MALLOC\"");
		// Disable the JIT.
		Malloc_OnJITCompile();
		return 0;
	}
	
	CHAIN_FORWARD:Malloc_OnJITCompile() = 1;
	#if defined _ALS_OnJITCompile
		#undef OnJITCompile
	#else
		#define _ALS_OnJITCompile
	#endif
	#define OnJITCompile(%0) CHAIN_PUBLIC:Malloc_OnJITCompile(%0)
	
	// Allocate space on the heap permanently.
	#include "y_malloc_warning"
	#include "y_malloc_heapalloc"
#endif

// Functions to access the data on the heap.
#include "y_malloc_funcs"
#if defined YSI_TESTS
	#include "y_malloc_tests"
#endif

#undef YSI_g_sHeapStart
#undef YSI_g_sUnusedStart

