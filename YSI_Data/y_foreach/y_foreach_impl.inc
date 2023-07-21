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

/*

           db        88888888ba  88      ,ad8888ba,                       88             
          d88b       88      "8b 88     d8"'    `"8b                      88             
         d8'`8b      88      ,8P 88    d8'                                88             
        d8'  `8b     88aaaaaa8P' 88    88             ,adPPYba,   ,adPPYb,88  ,adPPYba,  
       d8YaaaaY8b    88""""""'   88    88            a8"     "8a a8"    `Y88 a8P_____88  
      d8""""""""8b   88          88    Y8,           8b       d8 8b       88 8PP"""""""  
     d8'        `8b  88          88     Y8a.    .a8P "8a,   ,a8" "8a,   ,d88 "8b,   ,aa  
    d8'          `8b 88          88      `"Y8888Y"'   `"YbbdP"'   `"8bbdP"Y8  `"Ybbd8"'  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="num">Number of extra parameters hidden on the stack.</param>
 * <remarks>
 *   Returns a random value from an iterator.
 *  
 *   If additional parameters are given they are excluded from consideration.
 *   This allows you to chain calls to get multiple random values so follows:
 *  
 *      new president     = Iter_Random(Player);
 *      new vicePresident = Iter_Random(Player, president);
 *      new primeMinister = Iter_Random(Player, president, vicePresident);
 *      new minister      = Iter_Random(Player, president, vicePresident, primeMinister);
 *  
 *   None of those values can be the same, and this saves horrible random-
 *   dependent loops.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Iter_Random_Impl(count, const array[], start, num)
{
	new
		first = 0,
		last = 0;
	#emit LOAD.S.pri   num
	#emit SHL.C.pri    __cell_shift
	#emit ADDR.alt     __param4_offset
	#emit STOR.S.alt   first
	#emit ADD
	#emit STOR.S.pri   last
	// Short-circuit the common-case where there are no exclusions.
	if (num)
	{
		// Count how many unique values there are.
		for (new value = 0, ptr = first; ptr != last; ptr += cellbytes)
		{
			#emit LREF.S.pri   ptr
			#emit STOR.S.pri   value
			// First, check if this is valid and IN the array.
			if (0 <= value < start && array[value] > value)
			{
				// Is this unique?
				for (new i2 = first, v2 = 0; i2 != ptr; i2 += cellbytes)
				{
					#emit LREF.S.pri   i2
					#emit STOR.S.pri   v2
					if (value == v2)
					{
						// Only the first instance of any number is counted.
						--num;
						break;
					}
				}
			}
			else
			{
				--num;
			}
		}
	}
	if (count <= num)
	{
		return INVALID_ITERATOR_SLOT;
	}
	// There are enough elements to search from after exclusions.
	count = random(count - num);
	if (num)
	{
		do
		{
Iter_Random_Impl_loop:
			// Check if this is an excluded value.
			start = array[start];
			for (num = first; num != last; num += cellbytes)
			{
				#emit LREF.S.pri   num
				#emit LOAD.S.alt   start
				#emit JEQ          Iter_Random_Impl_loop
			}
			// The loop ended, all is good.
		}
		while (count--);
		return start;
	}
	// No exclutions, use the old code.
	do
	{
		start = array[start];
	}
	while (count--);
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="">Excluded elements.</param>
 * <remarks>
 *   Returns a random value from an iterator.
 *  
 *   If additional parameters are given they are excluded from consideration.
 *   This allows you to chain calls to get multiple random values so follows:
 *  
 *      new president     = Iter_Random(Player);
 *      new vicePresident = Iter_Random(Player, president);
 *      new primeMinister = Iter_Random(Player, president, vicePresident);
 *      new minister      = Iter_Random(Player, president, vicePresident, primeMinister);
 *  
 *   None of those values can be the same, and this saves horrible random-
 *   dependent loops.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Random_Internal(count, const array[], start, ...)
{
	new
		n = numargs() - 3,
		s,
		e;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param3_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_Random_Impl(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return s;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <remarks>
 *   Adds a random value to an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomAdd_InternalC(&count, array[], start, ...)
{
	new
		n = numargs() - 3;
	if (n == 0)
	{
		return Iter_Add_InternalC(count, array, start, Iter_RandomFree_Single(count, array, start));
	}
	new
		e,
		s;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param3_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_RandomFree_Multi(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return Iter_Add_InternalC(count, array, start, s);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="counts">Number of items in each iterator part.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <param name="start"></param>
 * <param name="slot">Multi-iterator slot to add to.</param>
 * <remarks>
 *   Adds a random value to an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomAdd_InternalD(counts[], array[], size, slots, start, slot, ...)
{
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	new
		count = 0;
	while (slots--)
		count += counts[slots];
	new
		n = numargs() - 6;
	if (n == 0)
	{
		return Iter_Add_InternalD(counts[slot], array, start, size, Iter_RandomFree_Single(count, array, size));
	}
	new
		e,
		s;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param6_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_RandomFree_Multi(count, array, size, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return Iter_Add_InternalD(counts[slot], array, start, size, s);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <remarks>
 *   Removes a random value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomRemove_InternalC(&count, array[], start, ...)
{
	new
		n = numargs() - 3,
		s,
		e;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param3_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_Random_Impl(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return Iter_Remove_InternalC(count, array, start, s);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *   Removes a random value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomRemove_InternalD(&count, array[], size, start, ...)
{
	new
		n = numargs() - 4,
		s,
		e;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param4_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_Random_Impl(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	return Iter_Remove_InternalD(count, array, start, size, s);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <remarks>
 *   Returns a random unused value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomFree_InternalC(count, const array[], start, ...)
{
	new
		n = numargs() - 3;
	if (n == 0)
	{
		return Iter_RandomFree_Single(count, array, start);
	}
	new
		e,
		s;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param3_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_RandomFree_Multi(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return s;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <remarks>
 *   Returns a random unused value from an iterator.  Takes a load of hidden
 *   extra parameters on the stack, which are values to not return.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Iter_RandomFree_Multi(count, const array[], start, num)
{
	count = start - count;
	new
		first = 0,
		last = 0;
	#emit LOAD.S.pri   num
	#emit SHL.C.pri    __cell_shift
	#emit ADDR.alt     __param4_offset
	#emit STOR.S.alt   first
	#emit ADD
	#emit STOR.S.pri   last
	// Count how many unique values there are.
	for (new value = 0, ptr = first; ptr != last; ptr += cellbytes)
	{
		#emit LREF.S.pri   ptr
		#emit STOR.S.pri   value
		// First, check if this is valid and OUT the array.
		if (0 <= value < start && array[value] <= value)
		{
			// Is this unique?
			for (new i2 = first, v2 = 0; i2 != ptr; i2 += cellbytes)
			{
				#emit LREF.S.pri   i2
				#emit STOR.S.pri   v2
				if (value == v2)
				{
					// Only the first instance of any number is counted.
					--num;
					break;
				}
			}
		}
		else
		{
			--num;
		}
	}
	if (count <= num)
	{
		return INVALID_ITERATOR_SLOT;
	}
	// There are enough elements to search from after exclusions.
	count = random(count - num);
	for ( ; ; )
	{
Iter_RandomFree_Internal_loop:
		--start;
		// Check if this is an excluded value.
		if (array[start] > start)
		{
			continue;
		}
		for (num = first; num != last; num += cellbytes)
		{
			#emit LREF.S.pri   num
			#emit LOAD.S.alt   start
			#emit JEQ          Iter_RandomFree_Internal_loop
		}
		// Don't use `do {} while ();` or this decrement will be run when
		// the `continue;` above is hit.
		if (count == 0)
		{
			break;
		}
		--count;
	}
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <remarks>
 *   Returns a random unused value from an iterator.  No exclusions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Iter_RandomFree_Single(count, const array[], start)
{
	// Get the unused count, not the used count.
	count = start - count;
	if (count <= 0)
	{
		return INVALID_ITERATOR_SLOT;
	}
	// There are enough elements to search from after exclusions.
	count = random(count);
	// No exclutions, use the old code.
	for ( ; ; )
	{
		--start;
		// Check if this value is not included in any iterator.  If it isn't
		// then decrement the count until we have run out of values to test.
		if (array[start] <= start)
		{
			if (count == 0)
			{
				break;
			}
			--count;
		}
	}
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="counts">Number of items in each iterator part.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *   Returns a random unused value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomFree_InternalD(const counts[], const array[], start, slots, ...)
{
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	new
		count = 0;
	while (slots--)
		count += counts[slots];
	new
		n = numargs() - 4;
	if (n == 0)
	{
		return Iter_RandomFree_Single(count, array, start);
	}
	new
		e,
		s;
	// Get the range of the dynamic parameters.
	#emit ADDR.pri             __param4_offset
	#emit STOR.S.pri           s
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit STOR.S.pri           e
	while (s != e)
	{
		#emit LREF.S.pri           s
		#emit LOAD.I
		#emit PUSH.pri
		s += cellbytes;
	}
	s = Iter_RandomFree_Multi(count, array, start, n);
	// Pop the extra parameters.
	#emit LCTRL                __stk
	#emit LOAD.S.alt           n
	#emit SHL.C.alt            __cell_shift
	#emit ADD
	#emit SCTRL                __stk
	return s;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Array start index.</param>
 * <remarks>
 *   Finds the first free slot in the iterator and add it.  Excepting requested
 *   values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Alloc_InternalC(&count, array[], size, ...)
{
	for (new value = 0; value != size; ++value)
	{
		if (array[value] <= value)
		{
			new
				last = size++,
				next = array[last];
			while (next < value)
			{
				last = next,
				next = array[last];
			}
			return
				++count,
				array[(value - 1) % size] = (last + 1) % size,
				array[next - 1] = (value + 1) % size,
				array[value] = next,
				array[last] = value;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

stock Iter_Alloc_InternalD(&count, array[], start, size, ...)
{
	if (start >= size)
	{
		for (new value = 0; value != size; ++value)
		{
			if (array[value] <= value)
			{
				new
					last = start,
					next = array[last];
				while (next < value)
				{
					last = next,
					next = array[last];
				}
				return
					++count,
					array[value] = next,
					array[last] = value;
			}
		}
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <remarks>
 *   Finds the first free slot in the iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Free_Internal(const array[], size)
{
	// I tried to rewrite this to use the internal structure of a linked list to
	// find a free slot.  The logic being that if the next used slot in the list
	// is not the same as the next theoretical slot, the theoretical slot must
	// be available.  Bascially something like:
	//   
	//   if (array[i] != i + 1)
	//       return i + 1;
	//   
	// However, that doesn't work with multi-iterators, since the next slot
	// consecutively may not be in the same iterator, but will still be in use.
	// I wrote all the code and had to back it out again.  This comment is in
	// case I ever have the same "clever" idea again - DON'T DO IT.  Fortunately
	// the existing tests caught the problem and saved me everything but time.
	for (new i = 0; i != size; ++i)
	{
		if (array[i] <= i)
		{
			return i;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">multi-iterator data.</param>
 * <param name="trueSize">Size of the multi-iterator.</param>
 * <param name="start">End [?, since start points are backwards] of the multi-iterator.</param>
 * <remarks>
 *   Finds the first free multi index in the multi-iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_FreeMulti_Internal(const array[], trueSize, start)
{
    for (new i = 0; trueSize-- > start; ++i)
    {
        if (array[trueSize] >= start)
            return i;
    }
    return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Array start index.</param>
 * <param name="value">Item to add.</param>
 * <remarks>
 *   Adds a value to a given iterator set.  Now detects when you try and add the
 *   last item multiple times, as well as all the other items.  Now simplified
 *   even further with the new internal representation.  The modulo code is for
 *   iterator reversal.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Add_InternalC(&count, array[], size, value)
{
	//Iter_Debug_InternalC("Iter_Add_InternalC", array, size, count);
	Debug_Print3("Iter_Add called: %d, %d, %d", count, size, value);
	if (0 <= value < size && array[value] <= value)
	{
		Debug_Print5("Iter_Add: In iterator");
		new
			next = array[size],
			last;
		// We use many heuristics to try and find where in the list to insert
		// this new value as fast as possible.
		//
		// Version 0:
		//
		//   The value is being added to the very start of the list.  Only comes
		//   before the end insertion case because of a bug getting `prev` in
		//   empty lists.
		//
		if (next > value)
		{
			last = size;
		}
		//
		// Version 1:
		//
		//   It is being inserted at the end.  By far the most common case when
		//   initialising some list of items.
		//
		else if (value > (last = Iter_Prev_InternalD(array, size + 1, size)))
		{
			next = size;
		}
		//
		// Version 2:
		//
		//   If the array is densely filled then just looping linearly from the
		//   value until we hit something in the array will be faster than
		//   iterating through the list.  For that we need the average number of
		//   steps required, which is `count / 2`.  So if
		//   `(last - first) / count / 2` is smaller than that number then the
		//   density is sufficient to justify a linear scan.
		//
		//   Simplify:
		//
		//     d = last - next + 1
		//     c = count
		//   
		//     d / c / 2 < c / 2
		//     d / c     < c
		//     d         < c^2
		//
		else if ((last - next + 1) < count * count)
		{
			next = value + 1;
			while (array[next] <= next)
			{
				++next;
			}
			last = Iter_Prev_InternalD(array, size + 1, next);
		}
		//
		// Version 3:
		//
		//   Base case.  Loop through the list forwards.
		//
		else
		{
			last = size;
			while (next < value)
			{
				Debug_Print6("Iter_Add: Finding prev %d, %d", next, last);
				last = next,
				next = array[last];
			}
		}
		// Increase `size` so we modulo over the whole array, not just the
		// valid values subset.
		Debug_Print5("Iter_Add: Adding %d, %d, %d, %d, %d, %d", last, value, size, next, next - 1, (value - 1) % (size + 1));
		
		return
			++size,
			++count,
			array[(value - 1) % size] = (last + 1) % size,
			array[next - 1] = value + 1,
			array[value] = next,
			array[last] = value;
	}
	return INVALID_ITERATOR_SLOT;
}

stock Iter_Add_InternalD(&count, array[], start, size, value)
{
	if (0 <= value < size && start >= size && array[value] <= value)
	{
		new
			last = start,
			next = array[last];
		while (next < value)
		{
			last = next,
			next = array[last];
		}
		return
			++count,
			array[value] = next,
			array[last] = value;
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Array start index.</param>
 * <param name="size">Array size.</param>
 * <param name="index">Index to find Nth value.</param>
 * <param name="wrap">Keep going around until a value is found?</param>
 * <remarks>
 *   Allows you to find the Nth value in the iterator.  DO NOT call this in a
 *   loop to get all values - that totally defeats the purpose of "foreach", just
 *   use a normal "foreach" loop with an index counter for that case.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Index_Internal(count, const array[], start, size, index, bool:wrap = false)
{
	// If there are no elements in the iterator, we can't ever return the Nth
	// item.  Also if the parameters are invalid.
	if (index < 0 || start < size || array[start] >= size)
		return INVALID_ITERATOR_SLOT;
	// We could wrap around in the loop (it would work), but it is better to set
	// the limit first.
	if (wrap)
		index %= count;
	else if (index >= count)
		return INVALID_ITERATOR_SLOT;
	start = array[start];
	while (index--)
		start = array[start];
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Number of iterator elements.</param>
 * <param name="value">Item to remove.</param>
 * <remarks>
 *   Removes a value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Remove_InternalC(&count, array[], size, value)
{
	Debug_Print3("Iter_Remove called: %d, %d, %d", count, size, value);
	if (0 <= value < size++ && array[value] > value)
	{
		// This version has reverse iterators, which need maintaining, and can
		// be used in place of a loop to jump backwards in the list.
		--count;
		new
			next,
			last = value;
		do
		{
			--last,
			next = array[last % size];
		}
		while (next < 0);
		Debug_Print5("Iter_Remove: found %d, %d, %d, %d", min(next, last), array[value], min(next - 1, last) % size, array[value] - 1);
		return
			last = min(next - 1, last) % size,
			next = array[value],
			
			// These next four lines are done in a very specific order because
			// it is possible for two of the indexes to be the same when two
			// iterator entries are adjacent.  Thus we set the reverse pointers
			// first, then the next pointers, as the latter are more important.
			
			// Set the pointers for `last`.
			array[(value - 1) % size] = (last + 1) % size,
			array[next - 1] = (last + 1) % size,
			
			// Set the pointers for `next`.
			array[last] = next,
			array[value] = next | cellmin;
	}
	else
	{
		return INVALID_ITERATOR_SLOT;
	}
}

stock Iter_Remove_InternalD(&count, array[], start, size, value)
{
	new last = start;
	if (0 <= value < size && start >= size && count && array[value] > value)
	{
		// This version doesn't have reverse iterators, so we need to
		// manually loop through the list.
		while ((start = array[last]) < size)
		{
			if (start == value)
			{
				return
					--count,
					array[last] = array[value],
					array[value] |= cellmin;
			}
			last = start;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">Iterator data.</param>
 * <param name="size">Number of iterator elements.</param>
 * <param name="value">Item to remove.</param>
 * <param name="last">Pointer in which to store the last pointer.</param>
 * <remarks>
 *   Removes a value from an iterator safely.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated You can now use `Iter_Remove()` in loops.
stock Iter_SafeRemove_1(&count, array[], size, value, &last)
{
	if (0 <= value < size++ && array[value] > value)
	{
		// This version has reverse iterators, which need maintaining, and can
		// be used in place of a loop to jump backwards in the list.
		--count,
		last = Iter_Prev_InternalD(array, size, value);
		array[last] = array[value];
		if (array[last] == value + 1)
		{
			// We are going one step later, which means that the removed value
			// needs to point both forwards and backwards at the same time.
			return
				array[value] = (array[value] - size) + (-size * last);
		}
		else
		{
			return
				// For being out the iterator, but still usable in `foreach`.
				array[value] = array[value] - size,
				// Set the reverse pointer.
				array[(array[last] - 1) % size] = -size * last;
		}
	}
	else
	{
		return
			last = size,
			INVALID_ITERATOR_SLOT;
	}
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated You can now use `Iter_Remove()` in loops.
stock Iter_SafeRemove_2(&count, array[], start, size, value, &last)
{
	last = start;
	if (0 <= value < size && start >= size && count && array[value] > value)
	{
		// This version doesn't have reverse iterators, so we need to
		// manually loop through the list.
		while ((start = array[last]) < size)
		{
			if (start == value)
			{
				return
					--count,
					array[last] = array[value],
					array[value] |= -65536;
			}
			last = start;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="value">Item to check.</param>
 * <param name="size">Size of the iterator.</param>
 * <remarks>
 *   Checks if this item is in the iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Contains_InternalC(const array[], size, value)
{
	// Only need to know that this element is in ANY list, because there is only
	// one list it can be in.
	return 0 <= value < size && array[value] > value;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="counts">Number of items in each iterator part.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *   Return the total number of elements in all slots together.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Count_InternalC(const counts[], slots = sizeof (counts))
{
	new
		count = 0;
	while (slots--)
		count += counts[slots];
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="value">Item to check.</param>
 * <param name="size">Size of the iterator.</param>
 * <remarks>
 *   Checks if this item is in the iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Contains_InternalD(count, const array[], size, start, value)
{
	// Check the count first, and that this element is in ANY list.  There is no
	// point searching an empty list for this element, hence the count check.
	if (0 <= value < size && start >= size && count && array[value] > value)
	{
		// Then loop over that list to check if this element is in it.
		size = start;
		while ((size = array[size]) != start)
		{
			if (size == value)
			{
				return 1;
			}
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">multi-iterator data.</param>
 * <param name="trueSize">Size of the multi-iterator per index.</param>
 * <param name="size">Size of the multi-iterator.</param>
 * <param name="value">Item to check.</param>
 * <returns>
 *   INVALID_ITERATOR_SLOT on failure.
 *   Index of the multi-iterator the value is contained.
 * </returns>
 * <remarks>
 *   Checks if this item is in the multi-iterator at all, and if it is returns which index it is in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_GetMulti_Internal(const array[], trueSize, size, value)
{
    if (0 <= value < size && array[value] > value)
    {
        // Find the end of this list.
        while ((value = array[value]) < size) {}
        // Start points are actually backwards.
        return trueSize - value - 1;
    }
    return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of information.</param>
 * <param name="entries">Size of the count data.</param>
 * <param name="">Optional single multi-iterator to clear.</param>
 * <remarks>
 *   Resets an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Clear_InternalC(array[], size, entries, ...)
{
	//if (entries == 1)
	//{
	//	// Common case.
	//	new tmp = size;
	//	do
	//	{
	//		// Just a swap.
	//		entries = array[tmp],
	//		array[tmp] = tmp,
	//		tmp = entries;
	//	}
	//	while (tmp != size);
	//	{}
	//	#emit ZERO.pri
	//	#emit SREF.S.pri __param3_offset
	//}
	//else
	//{
	//	// Clear an entire iterator.
	//	for (size += entries; size--; )
	//	{
	//		array[size] = size;
	//	}
	//	while (entries--)
	//	{
	//		setarg(4, entries, 0);
	//	}
	//}
	while (size--)
		array[size] = size;
	while (entries--)
		setarg(3, entries, 0);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of base array.</param>
 * <param name="entries">Size of the count data.</param>
 * <param name="counts">Number of items in the iterator.</param>
 * <param name="elems">Number of iterator elements.</param>
 * <param name="start">Optional single multi-iterator to clear.</param>
 * <remarks>
 *   Resets an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Clear_InternalD(array[], size, entries, elems, counts[], start)
{
	// Clear just one part of a multi-iterator.
	if (0 <= start < entries)
	{
		counts[start] = 0,
		start = size - 1 - start,
		entries = array[start],
		array[start] = start;
		while (entries < elems)
		{
			start = array[entries],
			array[entries] = entries,
			entries = start;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">Iterator array to initialise.</param>
 * <param name="first">First iterator slot.</param>
 * <param name="s0">Size of first dimension.</param>
 * <param name="s1">Size of second dimension.</param>
 * <param name="entries">Number of start points.</param>
 * <remarks>
 *   Multi-dimensional arrays can't be initialised at compile time, so need to be
 *   done at run time, which is slightly annoying.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Init_Internal(array[][], first[], s0, s1, entries)
{
	new
		elems = s1 - entries,
		i = s1;
	entries *= elems;
	while (i--)
	{
		first[i] = entries,
		entries -= elems;
	}
	while (++i != s0)
	{
		memcpy(array[i], first, 0, s1 * cellbytes, s1);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="elems">Number of elements in the iterator.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="slot">The current slot.</param>
 * <remarks>
 *   Gets the element in an iterator that points to the current element.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Prev_InternalC(const array[], elems, size, slot)
{
	if ((slot < elems) ?
		(0 <= slot < array[slot]) :
		(slot < size && array[slot] < elems))
	{
		for (new last = slot; last--; )
		{
			if (array[last] == slot)
			{
				return last;
			}
		}
	}
	return elems;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="slot">The current slot.</param>
 * <remarks>
 *   Gets the element in an iterator that points to the current element.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Prev_InternalD(const array[], size, slot)
{
	if (array[slot] == slot)
	{
		// Special initial case for empty iterators.  When they aren't properly
		// initialised the reverse code doesn't work yet, until at least one
		// thing has been added.
		return slot;
	}
	new
		ptr;
	do
	{
		--slot,
		ptr = array[slot % size];
	}
	while (ptr < 0);
	return min(ptr - 1, slot) % size;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="name">iterator name.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="count">The number of elements added.</param>
 * <remarks>
 *   Print the contents of an iterator for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Debug_InternalC(const name[], const array[], size, count)
{
	printf("Iterator:%s<%d>:", name, size);
	printf("    Count   : %d", count);
	printf("    Free    : %d", size - count);
	printf("    Initial : %d", array[size]);
	printf("    Contents:");
	size -= 8;
	for (count = 0; count <= size; count += 8)
	{
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5],
			array[count + 6] < 0 ? -(array[count + 6] & cellmax) : array[count + 6],
			array[count + 7] < 0 ? -(array[count + 7] & cellmax) : array[count + 7]
		);
	}
	switch (count - size)
	{
	case 1:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5],
			array[count + 6] < 0 ? -(array[count + 6] & cellmax) : array[count + 6]
		);
	case 2:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5]
		);
	case 3:
		printf("        %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4]
		);
	case 4:
		printf("        %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3]
		);
	case 5:
		printf("        %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2]
		);
	case 6:
		printf("        %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1]
		);
	case 7:
		printf("        %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0]
		);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="name">iterator name.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="counts">The number of elements added.</param>
 * <param name="slots">The number of start points.</param>
 * <remarks>
 *   Print the contents of an iterator for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Debug_InternalD(const name[], const array[], size, const counts[], slots)
{
	printf("Iterator:%s<%d, %d>:", name, slots, size);
	new total = 0;
	new count = 0;
	for (count = 0; count != slots; ++count)
	{
		total += counts[count];
	}
	slots -= 8;
	printf("    Counts  :");
	for (count = 0; count <= slots; count += 8)
	{
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2],
			counts[count + 3],
			counts[count + 4],
			counts[count + 5],
			counts[count + 6],
			counts[count + 7]
		);
	}
	switch (count - slots)
	{
	case 1:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2],
			counts[count + 3],
			counts[count + 4],
			counts[count + 5],
			counts[count + 6]
		);
	case 2:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2],
			counts[count + 3],
			counts[count + 4],
			counts[count + 5]
		);
	case 3:
		printf("        %8d, %8d, %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2],
			counts[count + 3],
			counts[count + 4]
		);
	case 4:
		printf("        %8d, %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2],
			counts[count + 3]
		);
	case 5:
		printf("        %8d, %8d, %8d,",
			counts[count + 0],
			counts[count + 1],
			counts[count + 2]
		);
	case 6:
		printf("        %8d, %8d,",
			counts[count + 0],
			counts[count + 1]
		);
	case 7:
		printf("        %8d,",
			counts[count + 0]
		);
	}
	printf("    Total   : %d", total);
	printf("    Free    : %d", size - total);
	printf("    Initials:");
	for (count = 0; count <= slots; count += 8)
	{
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2],
			array[size + count + 3],
			array[size + count + 4],
			array[size + count + 5],
			array[size + count + 6],
			array[size + count + 7]
		);
	}
	switch (count - slots)
	{
	case 1:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2],
			array[size + count + 3],
			array[size + count + 4],
			array[size + count + 5],
			array[size + count + 6]
		);
	case 2:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2],
			array[size + count + 3],
			array[size + count + 4],
			array[size + count + 5]
		);
	case 3:
		printf("        %8d, %8d, %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2],
			array[size + count + 3],
			array[size + count + 4]
		);
	case 4:
		printf("        %8d, %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2],
			array[size + count + 3]
		);
	case 5:
		printf("        %8d, %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1],
			array[size + count + 2]
		);
	case 6:
		printf("        %8d, %8d,",
			array[size + count + 0],
			array[size + count + 1]
		);
	case 7:
		printf("        %8d,",
			array[size + count + 0]
		);
	}
	printf("    Contents:");
	size -= 8;
	for (count = 0; count <= size; count += 8)
	{
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5],
			array[count + 6] < 0 ? -(array[count + 6] & cellmax) : array[count + 6],
			array[count + 7] < 0 ? -(array[count + 7] & cellmax) : array[count + 7]
		);
	}
	switch (count - size)
	{
	case 1:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5],
			array[count + 6] < 0 ? -(array[count + 6] & cellmax) : array[count + 6]
		);
	case 2:
		printf("        %8d, %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4],
			array[count + 5] < 0 ? -(array[count + 5] & cellmax) : array[count + 5]
		);
	case 3:
		printf("        %8d, %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3],
			array[count + 4] < 0 ? -(array[count + 4] & cellmax) : array[count + 4]
		);
	case 4:
		printf("        %8d, %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2],
			array[count + 3] < 0 ? -(array[count + 3] & cellmax) : array[count + 3]
		);
	case 5:
		printf("        %8d, %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1],
			array[count + 2] < 0 ? -(array[count + 2] & cellmax) : array[count + 2]
		);
	case 6:
		printf("        %8d, %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0],
			array[count + 1] < 0 ? -(array[count + 1] & cellmax) : array[count + 1]
		);
	case 7:
		printf("        %8d,",
			array[count + 0] < 0 ? -(array[count + 0] & cellmax) : array[count + 0]
		);
	}
}

