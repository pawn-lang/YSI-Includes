#if defined _INC_y_sortedarray
	#endinput
#endif
#define _INC_y_sortedarray

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

#include "..\..\YSI_Core\y_utils"

#define SortedArray:%0<%1> SortedData_%0[%1],SortedSize_%0

#define SortedData_%0\32; SortedData_
#define SortedSize_%0\32; SortedSize_

#define SORTED_FUNC_0<%8>(%0) _%8(SortedData_%0,SortedSize_%0)
#define SORTED_FUNC_N<%8>(%0,%2) _%8(SortedData_%0,SortedSize_%0,%2)

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The sorted array.</param>
 * <param name="last">The number of elements in the sorted array.</param>
 * <param name="value">The value to find.</param>
 * <returns>
 *  Does the array contain this value?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:_Sorted_Contains(arr[], last, value)
{
	new
		first = 0,
		mid = 0;
	while (first < last)
	{
		mid = (first + last - 1) / 2;
		if (arr[mid] < value)
		{
			first = mid + 1;
		}
		else if (arr[mid] > value)
		{
			last = mid;
		}
		else
		{
			return true;
		}
	}
	return false;
}
#define Sorted_Contains SORTED_FUNC_N<Sorted_Contains>

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The sorted array.</param>
 * <param name="last">The number of elements in the sorted array.</param>
 * <param name="value">The value to find.</param>
 * <returns>
 *  The index at which the new value should be inserted.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock _Sorted_FindInsert(arr[], last, value)
{
	new
		first = 0,
		mid = 0;
	while (first < last)
	{
		mid = (first + last - 1) / 2;
		if (arr[mid] < value)
		{
			first = mid + 1;
		}
		else if (arr[mid] > value)
		{
			last = mid;
		}
		else
		{
			return mid;
		}
	}
	return last;
}
#define Sorted_FindInsert SORTED_FUNC_N<Sorted_FindInsert>

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The sorted array.</param>
 * <param name="last">The number of elements in the sorted array.</param>
 * <param name="value">The value to find.</param>
 * <returns>
 *  The index of the value, or <c>-1</c> if it doesn't exist.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock _Sorted_Find(arr[], last, value)
{
	new
		first = 0,
		mid = 0;
	while (first < last)
	{
		mid = (first + last - 1) / 2;
		if (arr[mid] < value)
		{
			first = mid + 1;
		}
		else if (arr[mid] > value)
		{
			last = mid;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
#define _Sorted_Find SORTED_FUNC_N<_Sorted_Find>

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The sorted array.</param>
 * <param name="size">The number of elements in the sorted array.</param>
 * <param name="value">The value to add.</param>
 * <param name="max">The total size of the array.</param>
 * <remarks>
 *  Adds a value to the sorted array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Sorted_Add(arr[], &size, value, max = sizeof (arr))
{
	if (size >= max)
		return false;
	if (size == 0)
	{
		// Only value.
		arr[0] = value;
	}
	else if (arr[size - 1] <= value)
	{
		// New largest value.
		arr[size] = value;
	}
	else if (arr[0] >= value)
	{
		// New smallest value.
		memcpy(arr[1], arr[0], 0, size << __COMPILER_CELL_SHIFT, max - 1);
		arr[0] = value;
	}
	else
	{
		new idx = _Sorted_FindInsert(arr, size, value);
		memcpy(arr[idx + 1], arr[idx], 0, (size - idx) << __COMPILER_CELL_SHIFT, max - idx - 1);
		arr[idx] = value;
	}
	++size;
	return true;
}
#define Sorted_Add SORTED_FUNC_N<Sorted_Add>

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The sorted array.</param>
 * <param name="size">The number of elements in the sorted array.</param>
 * <param name="value">The value to add.</param>
 * <remarks>
 *  Removes a value from the sorted array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Sorted_Remove(arr[], &size, value)
{
	if (size == 0)
		return false;
	new
		idx = _Sorted_Find(arr, size, value);
	if (idx == -1)
	{
		return false;
	}
	--size;
	if (arr[size] == value)
	{
		return true;
	}
	// We are shrinking the array, so the destination size doesn't matter.
	memcpy(arr[idx], arr[idx + 1], 0, (size - idx) << __COMPILER_CELL_SHIFT, cellmax);
	return true;
}
#define Sorted_Remove SORTED_FUNC_N<Sorted_Remove>

#if defined YSI_TESTS
	#include "y_sortedarray_tests"
#endif

