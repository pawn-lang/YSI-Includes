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
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="">Excluded elements.</param>
 * <remarks>
 *  Returns a random value from an iterator.
 *  
 *  If additional parameters are given they are excluded from consideration.
 *  This allows you to chain calls to get multiple random values so follows:
 *  
 *      new president     = Iter_Random(Player);
 *      new vicePresident = Iter_Random(Player, president);
 *      new primeMinister = Iter_Random(Player, president, vicePresident);
 *      new minister      = Iter_Random(Player, president, vicePresident, primeMinister);
 *  
 *  None of those values can be the same, and this saves horrible random-
 *  dependent loops.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Random_Internal(count, array[], start, ...)
{
	new
		numArgs = (numargs() - 3);
	if (numArgs)
	{
		// Get the number of VALID exclusions.
		new
			end,
			excluded;
		// Get the end of the variable arguments.
		#emit ADDR.alt     24
		#emit STOR.S.alt   excluded
		#emit LOAD.S.pri   numArgs
		#emit SHL.C.pri    2
		#emit ADD
		#emit STOR.S.pri   end
		for (new rewrite = excluded, value; excluded != end; excluded += 4)
		{
			#emit LREF.S.pri   excluded
			#emit LOAD.I
			#emit STOR.S.pri   value
			// First, check if this is valid.
			if (0 <= value < start && array[value] > value)
			{
				// It does.  Optimise for the inner loop.  Do this by
				// compressing valid values to the start of the list and storing
				// the dereferenced versions instead of the addresses.
				#emit LOAD.S.pri   value
				#emit SREF.S.pri   rewrite
				rewrite += 4;
			}
			else
			{
				// It does not.  Remove from the check.
				--numArgs;
			}
		}
		if (numArgs)
		{
			if (count <= numArgs)
				return INVALID_ITERATOR_SLOT;
			// There are enough elements to search from after exclusions.
			count = random(count - numArgs);
			#emit ADDR.alt     24
			#emit LOAD.S.pri   numArgs
			#emit SHL.C.pri    2
			#emit ADD
			#emit STOR.S.pri   end
			do
			{
Iter_Random_Internal_next_loop:
				// Load the start address.
				#emit ADDR.pri     24
				#emit STOR.S.pri   excluded
				// Check if this is an excluded value.
				start = array[start];
				for ( ; excluded != end; excluded += 4)
				{
					#emit LREF.S.pri   excluded
					#emit LOAD.S.alt   start
					#emit JEQ          Iter_Random_Internal_next_loop
					//#emit STOR.S.pri   value
					//if (check == start)
					//	goto Iter_Random_Internal_next_loop;
				}
				// The loop ended, all is good.
			}
			while (count--);
			return start;
		}
		// After removing invalid exclusions, there are none left.  Fall through
		// to the default implementation.
	}
	if (count)
	{
		// No exclutions, use the old code.
		count = random(count);
		do
		{
			start = array[start];
		}
		while (count--);
		return start;
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *  Returns a random unused value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomAdd_InternalC(&count, array[], start)
{
	return Iter_Add_InternalC(count, array, start, Iter_RandomFree_InternalC(count, array, start));
}

stock Iter_RandomAdd_InternalD(counts[], array[], size, slots, start, slot)
{
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	return Iter_Add_InternalD(counts[slot], array, start, size, Iter_RandomFree_InternalD(counts, array, size, slots));
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *  Returns a random unused value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomRemove_InternalC(&count, array[], start)
{
	return Iter_Remove_InternalC(count, array, start, Iter_Random_Internal(count, array, start));
}

stock Iter_RandomRemove_InternalD(&count, array[], size, start)
{
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	return Iter_Remove_InternalD(count, array, start, size, Iter_Random_Internal(count, array, start));
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Size of the iterator.</param>
 * <param name="slots">Number of multi-iterator values.</param>
 * <remarks>
 *  Returns a random unused value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_RandomFree_InternalC(count, array[], start)
{
	count = start - count;
	if (count)
	{
		count = random(count);
		while (start--)
		{
			// Check if this value is not included in any iterator.  If it isn't
			// then decrement the count until we have run out of values to test.
			if (array[start] <= start && !count--)
				return start;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

stock Iter_RandomFree_InternalD(counts[], array[], start, slots)
{
	// This is subtly different to the "C" version - it operates on multi
	// iterators, which have many counts, and thus we need to sum those first.
	new
		count = 0;
	while (slots--)
		count += counts[slots];
	return Iter_RandomFree_InternalC(count, array, start);
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Array start index.</param>
 * <remarks>
 *  Finds the first free slot in the iterator and add it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Alloc_InternalC(&count, array[], size)
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
				array[next - 1] = value + 1,
				array[value] = next,
				array[last] = value;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

stock Iter_Alloc_InternalD(&count, array[], start, size)
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
 * <param name="array">iterator data.</param>
 * <param name="size">Size of the iterator.</param>
 * <remarks>
 *  Finds the first free slot in the iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Free_Internal(array[], size)
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
 * <param name="array">multi-iterator data.</param>
 * <param name="trueSize">Size of the multi-iterator.</param>
 * <param name="start">End [?, since start points are backwards] of the multi-iterator.</param>
 * <remarks>
 *  Finds the first free multi index in the multi-iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_FreeMulti_Internal(array[], trueSize, start)
{
    for (new i = 0; trueSize-- > start; ++i)
    {
        if (array[trueSize] >= start)
            return i;
    }
    return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Array start index.</param>
 * <param name="value">Item to add.</param>
 * <remarks>
 *  Adds a value to a given iterator set.  Now detects when you try and add the
 *  last item multiple times, as well as all the other items.  Now simplified
 *  even further with the new internal representation.  The modulo code is for
 *  iterator reversal.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Add_InternalC(&count, array[], size, value)
{
	if (0 <= value < size && array[value] <= value)
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
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="start">Array start index.</param>
 * <param name="size">Array size.</param>
 * <param name="index">Index to find Nth value.</param>
 * <param name="wrap">Keep going around until a value is found?</param>
 * <remarks>
 *  Allows you to find the Nth value in the iterator.  DO NOT call this in a
 *  loop to get all values - that totally defeats the purpose of "foreach", just
 *  use a normal "foreach" loop with an index counter for that case.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Index_Internal(count, array[], start, size, index, bool:wrap = false)
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
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">iterator data.</param>
 * <param name="size">Number of iterator elements.</param>
 * <param name="value">Item to remove.</param>
 * <remarks>
 *  Removes a value from an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Remove_InternalC(&count, array[], size, value)
{
	new
		last;
	return Iter_SafeRemove_InternalC(count, array, size, value, last);
}

stock Iter_Remove_InternalD(&count, array[], start, size, value)
{
	new
		last;
	return Iter_SafeRemove_InternalD(count, array, start, size, value, last);
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of items in the iterator.</param>
 * <param name="array">Iterator data.</param>
 * <param name="size">Number of iterator elements.</param>
 * <param name="value">Item to remove.</param>
 * <param name="last">Pointer in which to store the last pointer.</param>
 * <remarks>
 *  Removes a value from an iterator safely.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_SafeRemove_InternalC(&count, array[], size, value, &last)
{
	if (0 <= value < size++ && array[value] > value)
	{
		// This version has reverse iterators, which need maintaining, and can
		// be used in place of a loop to jump backwards in the list.
		return
			--count,
			last = (array[(value - 1) % size] - 1) % size,
			array[last] = array[value],
			array[value] = value,
			array[(array[last] - 1) % size] = (last + 1) % size;
	}
	return INVALID_ITERATOR_SLOT;
}

stock Iter_SafeRemove_InternalD(&count, array[], start, size, value, &last)
{
	if (0 <= value < size && start >= size && count && array[value] > value)
	{
		// This version doesn't have reverse iterators, so we need to
		// manually loop through the list.
		last = start;
		while ((start = array[last]) < size)
		{
			if (start == value)
			{
				return
					--count,
					array[last] = array[value],
					array[value] = value;
			}
			last = start;
		}
	}
	return INVALID_ITERATOR_SLOT;
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">iterator data.</param>
 * <param name="value">Item to check.</param>
 * <param name="size">Size of the iterator.</param>
 * <remarks>
 *  Checks if this item is in the iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Contains_InternalC(array[], size, value)
{
	// Only need to know that this element is in ANY list, because there is only
	// one list it can be in.
	return 0 <= value < size && array[value] > value;
}

stock Iter_Contains_InternalD(count, array[], size, start, value)
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
 * <param name="array">multi-iterator data.</param>
 * <param name="trueSize">Size of the multi-iterator per index.</param>
 * <param name="size">Size of the multi-iterator.</param>
 * <param name="value">Item to check.</param>
 * <returns>
 *  INVALID_ITERATOR_SLOT on failure.
 *  Index of the multi-iterator the value is contained.
 * </returns>
 * <remarks>
 *  Checks if this item is in the multi-iterator at all, and if it is returns which index it is in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_GetMulti_Internal(array[], trueSize, size, value)
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
 * <param name="array">iterator data.</param>
 * <param name="size">Size of base array.</param>
 * <param name="entries">Size of the count data.</param>
 * <param name="count">Number of items in the iterator.</param>
 * <param name="elems">Number of iterator elements.</param>
 * <param name="lst">Last valid index in the iterator array.</param>
 * <param name="start">Optional single multi-iterator to clear.</param>
 * <remarks>
 *  Resets an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Iter_Clear_InternalC(array[], size, entries, lst, ...)
{
	// Clear an entire iterator.
	while (size--)
	{
		array[size] = size;
	}
	array[lst] = 0;
	while (entries--)
	{
		setarg(4, entries, 0);
	}
}

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
			array[entries] = 0,
			entries = start;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Iterator array to initialise.</param>
 * <param name="first">First iterator slot.</param>
 * <param name="s0">Size of first dimension.</param>
 * <param name="s1">Size of second dimension.</param>
 * <param name="entries">Number of start points.</param>
 * <remarks>
 *  Multi-dimensional arrays can't be initialised at compile time, so need to be
 *  done at run time, which is slightly annoying.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Init_Internal(arr[][], first[], s0, s1, entries)
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
		memcpy(arr[i], first, 0, s1 * 4, s1);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">iterator data.</param>
 * <param name="elems">Number of elements in the iterator.</param>
 * <param name="size">Size of the iterator.</param>
 * <param name="slot">The current slot.</param>
 * <remarks>
 *  Gets the element in an iterator that points to the current element.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock
	Iter_Prev_Internal(array[], elems, size, slot)
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

