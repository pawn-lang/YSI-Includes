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
	E_ITER_YIELD_STACK_ALLOC  // `malloc`ed memory.
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
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK_START] = tmp + 12;
	#emit LCTRL      2
	#emit STOR.pri   tmp
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP_START] = tmp;
	// After we return, every time "Iter_YieldReturn" is called, we store
	// everything from between the (then) current stack pointer and the value we
	// just saved.  Also for the heap.  Then when we re-enter it, we can restore
	// all of that data and resume as if nothing happened.  Also `CIP`.
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP_ALLOC] =
		YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK_ALLOC] = NO_ALLOC;
}

/**
 * <param name=""></param>
 * <remarks>
 *     Although it might not look like it from general code, this function is
 *     called, by replacing calls to an underlying iterator function with calls
 *     to this function instead.  In that way, we can restore the stack each
 *     time.
 * </remarks>
 */

stock bool:Iter_YieldLoop(...)
{
	// Because of the strange way we manipulate the stack, this function
	// actually gets called twice as often as you would expect.  Essentially,
	// for this (psudo-)loop:
	//   
	//   for (new i = iter_func(); Iter_YieldLoop(); )
	//   {
	//   }
	//   
	// The loop is entered and `iter_func()` is called.  This indirectly calls
	// `yield`, which returns to the call point of that function.  The loop
	// check is then entered and `Iter_YieldLoop()` is called.  Depending on if
	// `yield` was actually used, the main loop body is entered.  At the end of
	// that iteration, the loop check is run again and so `Iter_YieldLoop()` is
	// called again.
	// 
	// This is where it gets wierd!
	// 
	// `Iter_YieldLoop()` does a stack copy and a jump in to the earlier call to
	// `iter_func`, whose return address is earlier in the code.  When a `yield`
	// is done again, that return is to the first part of the `for` loop, which
	// then instantly enters the loop check section and calls `Iter_YieldLoop()`
	// again (as a side-effect, saving the iterator value in the loop variable).
	// 
	// So for `N` iterations of the loop, `Iter_YieldLoop()` is called `2N + 1`
	// times, and should be made aware of which phase of its calls it is in.
	// 
	// This is, of course, made more complicated by nested loops, but that just
	// means we need to store the state on our own stack.
	// 
	// There are too many loops inside each other.  Ignore some.
	if (YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return false;
	// If there is nothing allocated here, we fell out of the iterator function
	// and so the loop is over.
	new
		bool:ret = false;
	// Resume the function from the last point.
	return false;
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

