#if !defined MAX_NESTED_ITERATORS
	#define MAX_NESTED_ITERATORS (4)
#endif

enum E_ITER_YIELD
{
	E_ITER_YIELD_STACK,
	E_ITER_YIELD_HEAP,
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
 * <param name="addr">The address of the true iterator function to call.  This
 *     is derived at mode start time, by <em>code-scan.inc</em>.</param>
 * <param name="">If there is another parameter (determined by <c>numargs</c>),
 *     it means there was a <c>new</c> declaration.  This means that by
 *     subtracting a constant from the stack position, we can get the stack
 *     position after the function ends, accounting for the fact that the
 *     variable will be instantly pushed.</param>
 */

stock Iter_YieldEnter(addr, ...)
{
	static
		tmp;
	// DO NOT ALLOCATE ANYTHING ON THE STACK HERE.
	if (++YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
	{
		P:E("Too many nested `foreach` yield loops.  Increase `MAX_NESTED_ITERATORS`.");
		return;
	}
	// Allocate everything.
	// Save the stack depth at this point.  First check if the return from this
	// function is pushed, indicating `new`.
	#emit LCTRL      4
	#emit STOR.pri   tmp
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_STACK] = tmp;
	#emit LCTRL      2
	#emit STOR.pri   tmp
	YSI_g_sIteratorStack[YSI_g_sIteratorDepth][E_ITER_YIELD_HEAP] = tmp;
	// After we return, every time "Iter_YieldReturn" is called, we store
	// everything from between the (then) current stack pointer and the value we
	// just saved.  Also for the heap.  Then when we re-enter it, we can restore
	// all of that data and resume as if nothing happened.  Also `CIP`.
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
	// There are too many loops inside each other.  Ignore some.
	if (YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return false;
	// Resume the function from the last point.
}

stock Iter_YieldEnd()
{
	if (--YSI_g_sIteratorDepth >= MAX_NESTED_ITERATORS)
		return;
	// Free everything.
}

