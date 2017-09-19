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
	E_ITER_YIELD_FIRST        // First call of a pair to `Iter_YieldLoop`.
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

stock bool:Iter_YieldEnter()
{
	// This is called as:
	//   
	//   iter_var = Iter_YieldEnter() ? -1 : iter_func();
	//   
	// This means we can skip ever entering the iterator in error cases.  Better
	// yet, we can use the default iterator value for the fail case!
	static
		tmp;
	if (++YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
	{
		P:E("Too many nested `foreach` yield loops.  Increase `MAX_NESTED_ITERATORS`.");
		return true;
	}
	{}
	// Save the stack depth at this function's return point.
	#emit LCTRL      4
	#emit STOR.pri   tmp
	iter[E_ITER_YIELD_STACK_START] = tmp + 12;
	#emit LCTRL      2
	#emit STOR.pri   tmp
	iter[E_ITER_YIELD_HEAP_START] = tmp;
	iter[E_ITER_YIELD_FIRST] = 0;
	// After we return, every time "Iter_YieldReturn" is called, we store
	// everything from between the (then) current stack pointer and the value we
	// just saved.  Also for the heap.  Then when we re-enter it, we can restore
	// all of that data and resume as if nothing happened.  Also `CIP`.
	iter[E_ITER_YIELD_HEAP_ALLOC] =
		iter[E_ITER_YIELD_STACK_ALLOC] = NO_ALLOC;
}

static stock bool:_Iter_YieldLoop(iter[E_ITER_YIELD])
{
	static
		end,
		src,
		dst,
		frm,
		cip;
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
	}
	else
	{
		// Copy the heap.
		if ((cip = iter[E_ITER_YIELD_HEAP_ALLOC]))
		{
			dst = iter[E_ITER_YIELD_HEAP_START],
			end = iter[E_ITER_YIELD_HEAP_END];
			#emit LOAD.pri   end
			#emit SCTRL      2
			rawMemcpy(dst, cip, end - dst);
			// TODO: Adjust this from raw memory to an allocation offset.
			free(cip);
		}
		// Copy the stack.
		frm = iter[E_ITER_YIELD_FRM],
		cip = iter[E_ITER_YIELD_CIP],
		src = iter[E_ITER_YIELD_STACK_ALLOC],
		end = iter[E_ITER_YIELD_STACK_START],
		dst = iter[E_ITER_YIELD_STACK_END];
		#emit LOAD.pri   dst
		#emit SCTRL      4
		rawMemcpy(dst, src, end - dst),
		free(src);
		// Copy the frame.
		#emit LOAD.pri   frm
		#emit SCTRL      5
		// Jump back in to our earlier function.
		#emit LOAD.pri   cip
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
	return _Iter_YieldLoop(iter);
}

stock Iter_YieldEnd()
{
	if (--YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return;
	// Free everything.
}

stock Iter_YieldReturn(value)
{
	// First, store the stack and heap.
	// Next, jump to a random point - the point 
	// Finally, clear the stored stack.
}

