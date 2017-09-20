#if !defined MAX_NESTED_ITERATORS
	#define MAX_NESTED_ITERATORS (4)
#endif

enum E_ITER_YIELD
{
	E_ITER_YIELD_STACK_START, // Where the pointer was before the loop.
	E_ITER_YIELD_HEAP_START,  // Where the pointer was before the loop.
	E_ITER_YIELD_STACK_END,   // Where the pointer was at `yield`.
	E_ITER_YIELD_HEAP_END,    // Where the pointer was at `yield`.
	E_ITER_YIELD_HEAP_ALLOC,  // `malloc`ed memory.
	E_ITER_YIELD_STACK_ALLOC, // `malloc`ed memory.
	E_ITER_YIELD_FIRST,       // First call of a pair to `Iter_YieldLoop`.
	E_ITER_YIELD_RETURN,      // The return address from `yield`.
	E_ITER_YIELD_FRAME        // The return frame from `yield`.
}

static stock
	YSI_g_sIteratorStack[MAX_NESTED_ITERATORS][E_ITER_YIELD],
	YSI_g_sIteratorDepth = -1;

/**
 * <remarks>
 * </remarks>
 */

stock Iter_YieldReturn(iterstate[], ...)
{
	// "iterstate" contains the 
}

/**
 */
static stock
	YSI_g_sC,
	YSI_g_sB,
	YSI_g_sE,
	YSI_g_sA,
	YSI_g_sD;

stock bool:Iter_YieldEnter()
{
	// This is called as:
	//   
	//   iter_var = (I@ = -1, Iter_YieldEnter() ? I@ : iter_func());
	//   
	// This means we can skip ever entering the iterator in error cases.  Better
	// yet, we can use the default iterator value for the fail case!  It is
	// important that the `true` case is the fail case, as the return value may
	// often be a non-zero jump address (i.e. the return address).
	if (++YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
	{
		P:E("Too many nested `foreach` yield loops.  Increase `MAX_NESTED_ITERATORS`.");
		return true;
	}
	{}
	// Save the stack depth at this function's return point.
	#emit LCTRL      4
	#emit STOR.pri   YSI_g_sC
	iter[E_ITER_YIELD_STACK_START] = YSI_g_sC + 12;
	#emit LCTRL      2
	#emit STOR.pri   YSI_g_sC
	iter[E_ITER_YIELD_HEAP_START] = YSI_g_sC;
	iter[E_ITER_YIELD_FIRST] = 0;
	// After we return, every time "Iter_YieldReturn" is called, we store
	// everything from between the (then) current stack pointer and the value we
	// just saved.  Also for the heap.  Then when we re-enter it, we can restore
	// all of that data and resume as if nothing happened.  Also `CIP`.
	iter[E_ITER_YIELD_HEAP_ALLOC] =
		iter[E_ITER_YIELD_STACK_ALLOC] = NO_ALLOC;
	return false;
}

static stock bool:_Iter_YieldLoop(iter[E_ITER_YIELD])
{
	if ((iter[E_ITER_YIELD_FIRST] ^= 1))
	{
		// If there is nothing allocated here, we fell out of the iterator
		// function and so the loop is over.
		if (!iter[E_ITER_YIELD_STACK_ALLOC])
		{
			// Release our stack.
			--YSI_g_sIteratorDepth;
			return false;
		}
		// Otherwise, the iterator continued, so the loop should as well.
	}
	else
	{
		// Restore the heap.
		if ((YSI_g_sB = iter[E_ITER_YIELD_HEAP_ALLOC]))
		{
			iter[E_ITER_YIELD_HEAP_ALLOC] = NO_ALLOC,
			YSI_g_sE = iter[E_ITER_YIELD_HEAP_START],
			YSI_g_sC = iter[E_ITER_YIELD_HEAP_END];
			#emit LOAD.pri   YSI_g_sC
			#emit SCTRL      2
			rawMemcpy(YSI_g_sE, YSI_g_sB, YSI_g_sC - YSI_g_sE),
			// TODO: Adjust this from raw memory to an allocation offset.
			free(Malloc_Reconcile(YSI_g_sB));
		}
		YSI_g_sA = iter[E_ITER_YIELD_FRM],
		YSI_g_sD = iter[E_ITER_YIELD_CIP],
		YSI_g_sB = iter[E_ITER_YIELD_STACK_ALLOC],
		YSI_g_sC = iter[E_ITER_YIELD_STACK_START], // Correct (grows down).
		YSI_g_sE = iter[E_ITER_YIELD_STACK_END],   // Correct (grows down).
		iter[E_ITER_YIELD_STACK_ALLOC] = NO_ALLOC;
		// Restore the stack.
		#emit LOAD.pri   YSI_g_sE
		#emit SCTRL      4
		// Restore the frame.
		#emit LOAD.pri   YSI_g_sA
		#emit SCTRL      5
		// Copy the stack.
		rawMemcpy(YSI_g_sE, YSI_g_sB, YSI_g_sC - YSI_g_sE),
		free(Malloc_Reconcile(YSI_g_sB));
		// Jump back in to our earlier function.
		#emit LOAD.pri   YSI_g_sD
		#emit SCTRL      6
		// Technically, we never return from here, but the compiler can't know!
	}
	return true;
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

stock bool:Iter_YieldLoop()
{
	// There are too many loops inside each other.  Ignore some.
	if (YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return false;
	return _Iter_YieldLoop(YSI_g_sIteratorStack[YSI_g_sIteratorDepth]);
}

stock Iter_YieldEnd()
{
	if (--YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return;
	// Free everything.
}

stock Iter_YieldReturn(value)
{
	// Store the heap.
	#emit LCTRL      2
	#emit STOR.pri   YSI_g_sB
	YSI_g_sE = YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP_START],
	YSI_g_sD = YSI_g_sB - YSI_g_sE;
	if (YSI_g_sD)
	{
		YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP_END] = YSI_g_sB,
		YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP_ALLOC] = YSI_g_sA = Malloc_Resolve(malloc(YSI_g_sD / cellbytes)),
		rawMemcpy(YSI_g_sA, YSI_g_sE, YSI_g_sD);
	}
	{}
	// Store the stack.
	#emit LCTRL      4
	#emit STOR.pri   YSI_g_sB
	YSI_g_sD = YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK_START],
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK_END] = YSI_g_sB,
	YSI_g_sC = YSI_g_sD - YSI_g_sB,
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK_ALLOC] = YSI_g_sA = Malloc_Resolve(malloc(YSI_g_sC / cellbytes)),
	rawMemcpy(YSI_g_sA, YSI_g_sB, YSI_g_sC);
	// Store the frame.
	#emit LCTRL      5
	#emit STOR.pri   YSI_g_sB
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_FRM] = YSI_g_sB;
	// Store the return value in `I@` so we can access it.
	I@ = value;
	// Wipe out the stack (YSI_g_sD).
	#emit LOAD.pri   YSI_g_sD
	#emit SCTRL      4
	// Wipe out the heap (YSI_g_sE).
	#emit LOAD.pri   YSI_g_sE
	#emit SCTRL      2
	// Reset the frame.
	YSI_g_sA = YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_FRAME];
	#emit LOAD.pri   YSI_g_sA
	#emit SCTRL      5
	// Jump to the return location.
	YSI_g_sA = YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_RETURN];
	#emit LOAD.pri   YSI_g_sA
	#emit SCTRL      6
}

