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

// An array of `[1][1]` would still have a second dimension offset of `4`, never `0`.  The offset to
// the data in the second dimension is relative to the current index.

stock bool:Circular_IsFull_(s1, s2, ...)
{
	// Get the address of the final slot.
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   20
	#emit ADD
	#emit ADD.C        0xFFFFFFFC
	// Load the data there.
	#emit STOR.S.pri   s2
	#emit LREF.S.pri   s2
	// Test if it is `> 0`.  If so the circular buffer is full.
	#emit ZERO.alt
	#emit SGRTR
	#emit RETN
	return false; //__COMPILER_NAKED
}

stock Circular_GetCount_(s1, s2, ...)
{
	// Get the address of the final slot.
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   20
	#emit ADD
	#emit ADD.C        0xFFFFFFFC
	// Load the data there.
	#emit STOR.S.pri   s2
	#emit LREF.S.pri   s2
	#emit STOR.S.pri   s2
	if (s2 > 0)
	{
		// Full.  Return the size (adjusted to cells).
		#emit LOAD.S.pri   s1
		#emit SHR.C.pri    2
		#emit RETN
	}
	{}
	// Subtract the offset from the original size.
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   s2
	#emit ADD
	#emit SHR.C.pri    2
	#emit RETN
	return 0; //__COMPILER_NAKED
}

#define Circular_Rotate(%0) Circular_Rotate_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0))
#define Circular_Full(%0) Circular_IsFull_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0))
#define Circular_Count(%0) Circular_GetCount_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0))
#define Circular_Push(%0,%1) Circular_Push_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0), (%1))
#define Circular_Rotate(%0) Circular_Rotate_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0))
#define Circular_Init(%0) Circular_Init_(sizeof (%0) * cellbytes, sizeof (%0[]), (%0))
#define Circular_Capacity(%0) (sizeof (%0))

stock void:Circular_Init_(s1, s2, ...)
{
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   20
	#emit ADD
	#emit ADD.C        0xFFFFFFFC
	#emit STOR.S.pri   s2
	#emit ZERO.pri
	#emit SUB
	#emit SREF.S.pri   s2
}

stock Circular_Push_(s1, s2, ...)
{
	new
		count = 0;
	// Get the address of the final slot.
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   20
	#emit ADD
	#emit ADD.C        0xFFFFFFFC
	// Load the data there.
	#emit STOR.S.pri   count
	#emit LREF.S.pri   count
	#emit STOR.S.pri   count
	// Test if it is `> 0`.  If so the circular buffer is full.
	if (count > 0)
	{
		// Just rotate.
		// Simple copy to the first slot
		#emit LREF.S.alt   20 // NOT s1
		#emit LOAD.S.pri   20
		#emit ADD
		#emit LOAD.S.alt   s2
		#emit PUSH.alt
		#emit SHL.C.alt    2
		#emit PUSH.alt
		#emit PUSH.C       0
		#emit PUSH.S       24
		#emit PUSH.pri
		#emit PUSH.C       20
		#emit SYSREQ.C     memcpy
		#emit STACK        24
		// And rotate the numbers.
		// Get the start end end pointers.
		#emit LOAD.S.pri   s1
		#emit LOAD.S.alt   20
		#emit ADD
		#emit ADD.C        0xFFFFFFFC
		#emit STOR.S.pri   count
		#emit STOR.S.alt   s2
		// Load the first value, adjusted for its new slot.
		#emit LREF.S.pri   count
		#emit ADD.C        4
		// 24 (`src`) is clobbered from this point on.  But it saves a stack allocation.
		#emit STOR.S.pri   24
		while (count != s2)
		{
			// Move to the next slot.
			count -= 4;
			// `start` is actually a pointer to an array header index.
			// Load the offset here.  Swap slots through the registers.
			#emit LREF.S.pri   count
			#emit LOAD.S.alt   24
			#emit SREF.S.alt   count
			#emit ADD.C        4
			#emit STOR.S.pri   24
		}
		{}
		// `count` now contains the value from slot 0, ready to be moved to the end of the array.
		// We overwrote slot 0 earlier, when writing the new data, so NOW we move it to the end.
		#emit LOAD.S.pri   s1
		#emit LOAD.S.alt   20
		#emit ADD.C        0xFFFFFFFC
		#emit ADD
		#emit STOR.S.pri   count
		#emit LOAD.S.alt   s1
		#emit LOAD.S.pri   24
		#emit SUB
		#emit SREF.S.pri   count
		#emit POP.pri
		// Return the final slot.
		#emit MOVE.pri
		#emit SHR.C.pri    2
		#emit DEC.pri
		#emit RETN
	}
	else
	{
		// Just append.  `-count` is the slot to write to.
		#emit LOAD.S.alt   s1
		#emit LOAD.S.pri   count
		#emit ADD
		// `pri` is now the offset of the slot to write to in the header.
		#emit LOAD.S.alt   s2
		#emit SMUL
		// `pri` is now an offset in the main data.
		#emit LOAD.S.alt   20
		#emit ADD
		#emit LOAD.S.alt   s1
		#emit ADD
		// `pri` is now the full address of the destination.  Copy it.
		#emit LOAD.S.alt   s2
		#emit PUSH.alt
		#emit SHL.C.alt    2
		#emit PUSH.alt
		#emit PUSH.C       0
		#emit PUSH.S       24
		#emit PUSH.pri
		#emit PUSH.C       20
		#emit SYSREQ.C     memcpy
		#emit STACK        24
		// Adjust the final count.
		count += 4;
		if (count == 0)
		{
			// The array is full.  Reset the final slot pointer.
			#emit LOAD.S.pri   s1
			#emit LOAD.S.alt   20
			#emit ADD.C        0xFFFFFFFC
			#emit XCHG
			#emit ADD
			#emit STOR.S.pri   count
			#emit LOAD.S.pri   s2
			#emit SMUL
			#emit ADD.C        4
			#emit SREF.S.pri   count
			#emit POP.pri
			// Return the final slot ID.
			#emit MOVE.pri
			#emit SHR.C.pri    2
			#emit RETN
		}
		else
		{
			// Store the new count in the final slot.
			#emit LOAD.S.alt   s1
			#emit LOAD.S.pri   20
			#emit ADD
			#emit ADD.C        0xFFFFFFFC
			#emit LOAD.S.alt   count
			#emit STOR.S.pri   count
			#emit SREF.S.alt   count
			#emit POP.pri
			#emit LOAD.S.pri   s1
			#emit ADD
			#emit SHR.C.pri    2
			#emit DEC.pri
			#emit RETN
		}
	}
	return 0;
}

stock Circular_Rotate_(s1, s2, ...)
{
	new
		count = 0;
	// Get the address of the final slot.
	#emit LOAD.S.alt   s1
	#emit LOAD.S.pri   20
	#emit ADD
	#emit ADD.C        0xFFFFFFFC
	// Load the data there.
	#emit STOR.S.pri   count
	#emit LREF.S.pri   count
	#emit STOR.S.pri   count
	// Test if it is `> 0`.  If so the circular buffer is full.
	if (count > 0)
	{
		new data = 0;
		// Just rotate the numbers.
		// Get the start end end pointers.
		#emit LOAD.S.pri   s1
		#emit LOAD.S.alt   20
		#emit ADD
		#emit ADD.C        0xFFFFFFFC
		#emit STOR.S.pri   count
		#emit STOR.S.alt   s2
		// Load the first value, adjusted for its new slot.
		#emit LREF.S.pri   count
		#emit ADD.C        4
		#emit STOR.S.pri   data
		while (count != s2)
		{
			// Move to the next slot.
			count -= 4;
			// `start` is actually a pointer to an array header index.
			// Load the offset here.  Swap slots through the registers.
			#emit LREF.S.pri   count
			#emit LOAD.S.alt   data
			#emit SREF.S.alt   count
			#emit ADD.C        4
			#emit STOR.S.pri   data
		}
		{}
		// `count` now contains the value from slot 0, ready to be moved to the end of the array.
		// We overwrote slot 0 earlier, when writing the new data, so NOW we move it to the end.
		#emit LOAD.S.pri   s1
		#emit LOAD.S.alt   20
		#emit ADD.C        0xFFFFFFFC
		#emit ADD
		#emit STOR.S.pri   count
		#emit LOAD.S.alt   s1
		#emit LOAD.S.pri   data
		#emit SUB
		#emit SREF.S.pri   count
		#emit POP.pri
		// Return the final slot.
		#emit POP.pri
		#emit MOVE.pri
		#emit SHR.C.pri    2
		#emit DEC.pri
		#emit RETN
	}
	else
	{
		// Just adjust the final count.
		count += 4;
		if (count == 0)
		{
			// The array is full.  Reset the final slot pointer.
			#emit LOAD.S.pri   s1
			#emit LOAD.S.alt   20
			#emit ADD.C        0xFFFFFFFC
			#emit XCHG
			#emit ADD
			#emit STOR.S.pri   count
			#emit LOAD.S.pri   s2
			#emit SMUL
			#emit ADD.C        4
			#emit SREF.S.pri   count
			#emit POP.pri
			// Return the final slot ID.
			#emit MOVE.pri
			#emit SHR.C.pri    2
			#emit RETN
		}
		else
		{
			// Store the new count in the final slot.
			#emit LOAD.S.alt   s1
			#emit LOAD.S.pri   20
			#emit ADD
			#emit ADD.C        0xFFFFFFFC
			#emit LOAD.S.alt   count
			#emit STOR.S.pri   count
			#emit SREF.S.alt   count
			#emit POP.pri
			#emit LOAD.S.pri   s1
			#emit ADD
			#emit SHR.C.pri    2
			#emit DEC.pri
			#emit RETN
		}
	}
	return 0;
}

