#if !defined MAX_NESTED_ITERATORS
	#define MAX_NESTED_ITERATORS (4)
#endif

#define yield%0\32;%1; yield%0%1;
#define yieldreturn%0; Iter_YieldReturn(%0);
#define yieldbreak%0; return;

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
	YSI_g_sStackPtr;

stock
	YSI_gIteratorDepth = -1;

static
	YSI_g_sPtr;
#pragma unused YSI_g_sPtr

/**
 * <remarks>
 * </remarks>
 */

hook public OnScriptInit()
{
	#emit CONST.pri    YSI_g_sStack
	#emit STOR.pri     YSI_g_sStackPtr
}

/**
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
		P:E("Too many nested `foreach` yield loops.  Increase `MAX_NESTED_ITERATORS`.");
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
	#emit FILL         44
	// Save the stack size after this function ends.
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_START] = GetAmxStackBottom() + 12;
	#emit LCTRL        4
	#emit ADD.C        12
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        12  // Move on to `E_ITER_YIELD_HEAP_START`.
	#emit XCHG
	// Save the heap size.
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_START]  = GetAmxHeapTop();
	#emit LCTRL        2
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        24 // Move on to `E_ITER_YIELD_FRAME`.
	#emit XCHG
	// Load of data already blanked.
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_END]   = 0;
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_END]    = 0;
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_ALLOC]  = ResolvedAlloc:0;
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_ALLOC] = ResolvedAlloc:0;
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_FIRST]       = 0;
	// Store the previous function's frame pointer.
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_FRAME]       = GetCurrentFramePreviousFrame();
	#emit LOAD.S.pri   0
	#emit STOR.I
	#emit XCHG
	#emit ADD.C        4  // Move on to `E_ITER_YIELD_RETURN`.
	#emit XCHG
	// Store the return address (next instruction to execute).
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_RETURN]      = GetCurrentFrameReturn();
	#emit LOAD.S.pri   4
	#emit STOR.I
	return false;
}

/**
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

static stock
	size_l,
	src_l;

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
		#emit ADD.C        8
		#emit STOR.pri     YSI_g_sPtr
		#emit MOVE.alt
//		++YSI_gIteratorDepth;
		// Restore the heap.
		#emit CONST.pri    3
		#emit LIDX
		#emit STOR.pri     size_l
		#emit CONST.pri    1
		#emit LIDX
		#emit STOR.pri     src_l
		#emit CONST.pri    2
		#emit LIDX
		#emit SCTRL        2
		YSI_g_sStackPtr -= size_l,
		rawMemcpy(src_l, YSI_g_sStackPtr, size_l);
//		++YSI_gIteratorDepth;
		// Restore the stack.
		#emit LOAD.alt     YSI_g_sPtr
		#emit ZERO.pri
		#emit LIDX
		#emit STOR.pri     size_l
		#emit ZERO.pri
		#emit STOR.I
		#emit CONST.pri    0xFFFFFFFF // -1
		#emit LIDX
		#emit STOR.pri     src_l
		#emit SCTRL        4
		YSI_g_sStackPtr -= size_l,
		rawMemcpy(src_l, YSI_g_sStackPtr, size_l);
		//free(Malloc_Reconcile(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_ALLOC]));
//		YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_SIZE] = 0;
		// Jump back in to our earlier function.
		#emit LOAD.alt     YSI_g_sPtr
//		SetAmxFrame(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_FRM]);
		#emit CONST.pri    5
		#emit LIDX
		#emit SCTRL        5
//		SetAmxNextInstructionPointer(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_CIP]);
		#emit CONST.pri    6
		#emit LIDX
		#emit SCTRL        6
		// Technically, we never return from here, but the compiler can't know!
	}
	return true;
}

stock Iter_YieldReturn(value)
{
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
	#emit ADD.C        4
	#emit MOVE.alt
	#emit LCTRL        4
	#emit ADD.C        16
	#emit STOR.pri     src_l
	#emit STOR.I
//	size_l =
//		YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_START] -
//		(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_END] = size_l + 16);
	#emit LREF.alt     YSI_g_sPtr
	#emit SUB.alt
	#emit STOR.pri     size_l
	#emit MOVE.alt
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        8
	#emit XCHG
	#emit STOR.I
	rawMemcpy(YSI_g_sStackPtr, src_l, size_l);
	YSI_g_sStackPtr += size_l;
//	if (size_l)
//	{
//		dest_l = _:Malloc_Resolve(malloc(size_l / cellbytes)),
//		rawMemcpy(dest_l, src_l, size_l);
//		#emit LOAD.pri     YSI_g_sPtr
//		#emit ADD.C        8
//		#emit MOVE.alt
//		#emit LOAD.pri     dest_l
//		#emit STOR.I
////		YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_ALLOC] = Malloc_Resolve(malloc(size_l / cellbytes));
////		rawMemcpy(
////			_:YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_ALLOC],
////			YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_START],
////			size_l);
//	}
//	{}
//	size_l = GetAmxStackBottom();
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        12
	#emit STOR.pri     YSI_g_sPtr
	// Heap.
	#emit ADD.C        4
	#emit MOVE.alt
	#emit LCTRL        2
	#emit STOR.I
	// Using `LCTRL 2` is faster than saving and restoring the value.
//	#emit STOR.pri     size_l
//	size_l =
//		(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_END] = GetAmxHeapTop())
//		- YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_START];
	#emit LREF.alt     YSI_g_sPtr
	#emit STOR.alt     src_l
	#emit SUB
	#emit STOR.pri     size_l
	#emit MOVE.alt
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        8
	#emit XCHG
	#emit STOR.I
	rawMemcpy(YSI_g_sStackPtr, src_l, size_l);
	YSI_g_sStackPtr += size_l;
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_ALLOC] = Malloc_Resolve(malloc(size_l / cellbytes));
//	rawMemcpy(
//		_:YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_ALLOC],
//		YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_END],
//		size_l);
//	dest_l = _:Malloc_Resolve(malloc(size_l / cellbytes)),
//	rawMemcpy(dest_l, src_l, size_l);
	// Store the data to jump straight back to the caller.
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_FRM] = GetCurrentFramePreviousFrame();
	#emit LOAD.pri     YSI_g_sPtr
	#emit ADD.C        16
	#emit MOVE.alt
	#emit LOAD.S.pri   0
	#emit STOR.I
//	YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_CIP] = GetCurrentFrameReturn();
	#emit MOVE.pri
	#emit ADD.C        4
	#emit MOVE.alt
	#emit LOAD.S.pri   4
	#emit STOR.I
	// Go to the caller.  From this point on, we can't use any stack-local
	// storage, because we just destroyed the stack!
//	SetAmxFrame(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_FRAME]);
	#emit CONST.pri    1
	#emit LIDX
	#emit SCTRL        5
//	SetAmxStackBottom(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_STACK_START]);
	#emit CONST.pri    0xFFFFFFF8 // -8
	#emit LIDX
	#emit SCTRL        4
//	SetAmxHeapTop(YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_HEAP_START]);
	#emit CONST.pri    0xFFFFFFFB // -5
	#emit LIDX
	#emit SCTRL        2
//	size_l = YSI_g_sIteratorStack[YSI_gIteratorDepth][E_ITER_YIELD_RETURN];
	// No longer in this iterator.
//	--YSI_gIteratorDepth;
	#emit DEC          YSI_gIteratorDepth
//	SetAmxNextInstructionPointer(size_l);
	#emit CONST.pri    2
	#emit LIDX
	#emit SCTRL        6
}

