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

#if !defined MAX_NESTED_ITERATORS
	#define MAX_NESTED_ITERATORS (4)
#endif

#define YIELD__%0\32;%1; YIELD__%0%1;
#define YIELD__return%0; Iter_YieldReturn(%0);
#define YIELD__break%0; return;

#if YSI_KEYWORD(yield)
	#define yield YIELD__
#endif

#define iteryield%9;_:(%9=Iter%9@%0$[_:%2]%9; F@o)&&(I@=-1,Iter_YieldEnter())))?I@:_:F@u:F@l:(F@C:Iter_Func@%0$(),--YSI_gIteratorDepth)?1:2;Iter_YieldLoop();
#define F@C:%0(,%1) %0(%1)

#if !defined MAX_YIELD_MEMORY
	#define MAX_YIELD_MEMORY (512)
#endif

enum E_ITER_YIELD
{
	E_ITER_YIELD_STACK_START, // Where the pointer was before the loop.
	E_ITER_YIELD_STACK_END,   // Where the pointer was at `yield`.
	E_ITER_YIELD_STACK_SIZE,  // `malloc`ed memory.
	E_ITER_YIELD_HEAP_START,  // Where the pointer was before the loop.
	E_ITER_YIELD_HEAP_END,    // Where the pointer was at `yield`.
	E_ITER_YIELD_HEAP_SIZE,   // `malloc`ed memory.
	E_ITER_YIELD_FIRST,       // First call of a pair to `Iter_YieldLoop`.
	E_ITER_YIELD_FRM,         // The iterator function context.
	E_ITER_YIELD_CIP,         // The iterator function continuation.
	E_ITER_YIELD_FRAME,       // The return frame from `yield`.
	E_ITER_YIELD_RETURN       // The return address from `yield`.
}

static stock
	YSI_g_sIteratorStack[MAX_NESTED_ITERATORS][E_ITER_YIELD],
	YSI_g_sStack[MAX_YIELD_MEMORY],
	YSI_g_sStackPtr = 0;

stock
	YSI_gIteratorDepth = -1;

static
	YSI_g_sPtr = 0;
#pragma unused YSI_g_sPtr

/**
 * <remarks>
 * </remarks>
 */

public OnCodeInit()
{
	#emit CONST.pri    YSI_g_sStack
	#emit STOR.pri     YSI_g_sStackPtr
	
	#if defined Yield_OnCodeInit
		Yield_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Yield_OnCodeInit
#if defined Yield_OnCodeInit
	forward Yield_OnCodeInit();
#endif

/**
 * <library>y_iterate</library>
 * <remarks>
 * </remarks>
 */

stock bool:Iter_YieldEnter()
{
	// This is called as:
	//   
	//   iter_var = (I@ = -1, Iter_YieldEnter() ? I@ : (iter_func(), --YSI_gIteratorDepth));
	//   
	// (More-or-less, there's an extra conditional to avoid a compiler bug).
	// 
	// This means we can skip ever entering the iterator in error cases.  Better
	// yet, we can use the default iterator value for the fail case!  It is
	// important that the `true` case is the fail case, as the return value may
	// often be a non-zero jump address (i.e. the return address).
	if (++YSI_gIteratorDepth >= MAX_NESTED_ITERATORS)
	{
		Debug_Error("Too many nested `foreach` yield loops.  Increase `MAX_NESTED_ITERATORS`.");
		return true;
	}
	{}
	// Load a pointer to the first address.  We know we are in range, so there's
	// no `BOUNDS` check here.
	#emit CONST.alt    YSI_g_sIteratorStack
	#emit LOAD.pri     YSI_gIteratorDepth
	#emit IDXADDR
	#emit MOVE.alt
	#emit LOAD.I
	#emit ADD
	#emit MOVE.alt
	// Blank a load of data.
	#emit ZERO.pri
	#emit FILL         __11_cells
	// Save the stack size after this function ends.
	#emit LCTRL        __stk
	#emit ADD.C        __3_cells
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        __3_cells  // Move on to `E_ITER_YIELD_HEAP_START`.
	#emit XCHG
	// Save the heap size.
	#emit LCTRL        __hea
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        __6_cells // Move on to `E_ITER_YIELD_FRAME`.
	#emit XCHG
	// Load of data already blanked.
	// Store the previous function's frame pointer.
	#emit LOAD.S.pri   __frame_offset
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        __1_cell  // Move on to `E_ITER_YIELD_RETURN`.
	#emit XCHG
	// Store the return address (next instruction to execute).
	#emit LOAD.S.pri   __return_offset
	#emit STOR.I
	return false;
}

static stock
	size_l = 0,
	src_l = 0;

/**
 * <library>y_iterate</library>
 * <remarks>
 * <p>Because of the strange way we manipulate the stack, this function actually
 * gets called twice as often as you would expect.  Essentially, for this
 * (psudo-)loop:</p>
 *   
 *   <code>
 *   for (new i = iter_func(); Iter_YieldLoop(); )                              <br />
 *   {                                                                          <br />
 *   }
 *   </code>
 *   
 * <p>The loop is entered and <c>iter_func()</c> is called.  This indirectly
 * calls <c>yield</c>, which returns to the call point of that function.  The
 * loop check is then entered and <c>Iter_YieldLoop()</c> is called.  Depending
 * on if <c>yield</c> was actually used, the main loop body is entered.  At the
 * end of that iteration, the loop check is run again and so
 * <c>Iter_YieldLoop()</c> is called again.</p>
 * 
 * <p>This is where it gets wierd!</p>
 * 
 * <p><c>Iter_YieldLoop()</c> does a stack copy and a jump in to the earlier
 * call to <c>iter_func</c>, whose return address is earlier in the code.  When
 * a <c>yield</c> is done again, that return is to the first part of the
 * <c>for</c> loop, which then instantly enters the loop check section and calls
 * <c>Iter_YieldLoop()</c> again (as a side-effect, saving the iterator value in
 * the loop variable).</p>
 * 
 * <p>So for <c>N</c> iterations of the loop, <c>Iter_YieldLoop()</c> is called
 * <c>2N + 1</c> times, and should be made aware of which phase of its calls it
 * is in.</p>
 * 
 * <p>This is, of course, made more complicated by nested loops, but that just
 * means we need to store the state on our own stack.</p>
 * </remarks>
 */

stock bool:Iter_YieldLoop()
{
	if ((YSI_g_sIteratorStack[YSI_gIteratorDepth + 1][E_ITER_YIELD_FIRST] ^= 1))
	{
		// If there is nothing allocated here, we fell out of the iterator
		// function and so the loop is over.
		if (!YSI_g_sIteratorStack[YSI_gIteratorDepth + 1][E_ITER_YIELD_STACK_SIZE])
		{
			// Release our stack.
			return false;
		}
		// Otherwise, the iterator continued, so the loop should as well.
	}
	else
	{
		#emit INC          YSI_gIteratorDepth
		#emit CONST.alt    YSI_g_sIteratorStack
		#emit LOAD.pri     YSI_gIteratorDepth
		#emit IDXADDR
		#emit MOVE.alt
		#emit LOAD.I
		#emit ADD
		#emit ADD.C        __2_cells
		#emit STOR.pri     YSI_g_sPtr
		#emit MOVE.alt
		// Restore the heap.
		#emit CONST.pri    3
		#emit LIDX
		#emit PUSH.pri
		#emit PUSH.pri
		#emit PUSH.C       0
		#emit LOAD.alt     YSI_g_sStackPtr
		#emit SUB.alt
		#emit PUSH.pri
		#emit STOR.pri     YSI_g_sStackPtr
		#emit LOAD.alt     YSI_g_sPtr
		#emit CONST.pri    1
		#emit LIDX
		#emit PUSH.pri
		#emit CONST.pri    2
		#emit LIDX
		#emit SCTRL        __hea
		#emit PUSH.C       __5_cells
		#emit SYSREQ.C     memcpy
		// Restore the stack.
		#emit LOAD.alt     YSI_g_sPtr
		#emit CONST.pri    __minus1
		#emit LIDX
		#emit SCTRL        __stk
		#emit LREF.pri     YSI_g_sPtr // Or ZERO.pri, LIDX
		#emit PUSH.pri
		#emit PUSH.pri
		#emit LOAD.alt     YSI_g_sStackPtr
		#emit SUB.alt
		#emit ZERO.alt
		#emit PUSH.alt
		#emit SREF.alt     YSI_g_sPtr
		#emit PUSH.pri
		#emit STOR.pri     YSI_g_sStackPtr
		#emit LCTRL        __stk
		#emit ADD.C        __4_cells
		#emit PUSH.pri
		#emit PUSH.C       __5_cells
		#emit SYSREQ.C     memcpy
		#emit STACK        __6_cells
		// Jump back in to our earlier function.
		#emit LOAD.alt     YSI_g_sPtr
		#emit CONST.pri    5
		#emit LIDX
		#emit SCTRL        __frm
		#emit CONST.pri    6
		#emit LIDX
		#emit SCTRL        __jit_jump
		#emit SCTRL        __cip
		// Technically, we never return from here, but the compiler can't know!
	}
	return true;
}

/**
 * <library>y_iterate</library>
 * <remarks>
 * </remarks>
 */

stock Iter_YieldReturn(value)
{
	const minus5 = -5;
	const minus8 = -8;
	// This does the return through the global scope.
	I@ = value;
	// Load a pointer to the first address.  We know we are in range, so there's
	// no `BOUNDS` check here.
	#emit CONST.alt    YSI_g_sIteratorStack
	#emit LOAD.pri     YSI_gIteratorDepth
	#emit IDXADDR
	#emit MOVE.alt
	#emit LOAD.I
	#emit ADD
	#emit STOR.pri     YSI_g_sPtr
	// Stack (excluding this function and intermediate results).
	#emit ADD.C        __1_cell
	#emit MOVE.alt
	#emit LCTRL        __stk
	#emit ADD.C        __4_cells
	#emit STOR.I
	#emit LREF.alt     YSI_g_sPtr
	#emit SUB.alt
	#emit MOVE.alt
	#emit PUSH.pri
	#emit PUSH.pri
	#emit PUSH.C       0
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        __2_cells
	#emit XCHG
	#emit STOR.I
	#emit LCTRL        __stk
	#emit ADD.C        __7_cells
	#emit PUSH.pri
	#emit LOAD.alt     YSI_g_sStackPtr
	#emit PUSH.alt
	#emit PUSH.C       __5_cells
	#emit SYSREQ.C     memcpy
	#emit LOAD.pri     YSI_g_sStackPtr
	#emit STACK        __5_cells
	#emit POP.alt
	#emit ADD
	#emit STOR.pri     YSI_g_sStackPtr
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        __3_cells
	#emit STOR.pri     YSI_g_sPtr
	// Heap.
	#emit ADD.C        __1_cell
	#emit MOVE.alt
	#emit LCTRL        __hea
	#emit STOR.I
	// Using `LCTRL 2` is faster than saving and restoring the value.
	#emit LREF.alt     YSI_g_sPtr
	#emit SUB
	#emit MOVE.alt
	#emit PUSH.pri
	#emit PUSH.pri
	#emit PUSH.C       0
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        __2_cells
	#emit XCHG
	#emit STOR.I
	#emit LCTRL        __hea
	#emit PUSH.pri
	#emit LOAD.alt     YSI_g_sStackPtr
	#emit PUSH.alt
	#emit PUSH.C       __5_cells
	#emit SYSREQ.C     memcpy
	#emit LOAD.pri     YSI_g_sStackPtr
	#emit STACK        __5_cells
	#emit POP.alt
	#emit ADD
	#emit STOR.pri     YSI_g_sStackPtr
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        __4_cells
	#emit MOVE.alt
	#emit LOAD.S.pri   __frame_offset
	#emit STOR.I
	// Frame.
	#emit MOVE.pri
	#emit ADD.C        __1_cell
	#emit MOVE.alt
	#emit LOAD.S.pri   __return_offset
	#emit STOR.I
	// Go to the caller.  From this point on, we can't use any stack-local
	// storage, because we just destroyed the stack!
	#emit CONST.pri    1
	#emit LIDX
	#emit SCTRL        __frm
	#emit CONST.pri    minus8
	#emit LIDX
	#emit SCTRL        __stk
	#emit CONST.pri    minus5
	#emit LIDX
	#emit SCTRL        __hea
	// No longer in this iterator.
	#emit DEC          YSI_gIteratorDepth
	#emit CONST.pri    2
	#emit LIDX
	#emit SCTRL        __jit_jump
	#emit SCTRL        __cip
}

/**
 * <library>y_iterate</library>
 * <remarks>
 * </remarks>
 */

stock Iter_NewYield()
{
	
}

