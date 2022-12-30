/**
 * <library
 *   name="y_utils - arrays"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="dest">Destination address.</param>
 * <param name="src">Source data.</param>
 * <param name="numbytes">Number of bytes to copy.</param>
 * <remarks>
 *   Like memcpy, but takes addresses instead of arrays.  Also far less secure
 *   because it doesn't check the destination size - it just assumes it is large
 *   enough.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native RawMemCpy_(dest, src, index, numbytes, maxlength) = memcpy;
#define RawMemCpy(%0,%1,%2) RawMemCpy_((%0),(%1),0,(%2),(cellmax>>>2))

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="dest">Destination address.</param>
 * <param name="src">Source data.</param>
 * <param name="numbytes">Number of bytes to copy.</param>
 * <remarks>
 *   Like memcpy, but takes addresses instead of arrays.  Also far less secure
 *   because it doesn't check the destination size - it just assumes it is large
 *   enough.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `RawMemCpy` (i.e. use proper capitalisation).
stock rawMemcpy(dest, src, numbytes)
{
	return RawMemCpy(dest, src, numbytes);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of cells to fill.</param>
 * <remarks>
 *   Based on <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781">
 *   code by Slice</a>, modified to use binary flags instead of a loop.
 *
 *   "MemSet" takes an array, the size of the array, and a value to fill it with
 *   and sets the whole array to that value.
 *
 *   "rawmemset" is similar, but takes an AMX data segment address instead and
 *   the size is in bytes, not cells.  However, the size must still be a
 *   multiple of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock MemSet(arr[], value = 0, size = sizeof (arr))
{
	new
		addr = 0;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return RawMemSet(addr, value, size * cellbytes);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of cells to fill.</param>
 * <remarks>
 *   Based on <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781">
 *   code by Slice</a>, modified to use binary flags instead of a loop.
 *
 *   "MemSet" takes an array, the size of the array, and a value to fill it with
 *   and sets the whole array to that value.
 *
 *   "rawmemset" is similar, but takes an AMX data segment address instead and
 *   the size is in bytes, not cells.  However, the size must still be a
 *   multiple of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `MemSet` (i.e. use proper capitalisation).
stock memset(arr[], val = 0, size = sizeof (arr))
{
	new
		addr = 0;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return RawMemSet(addr, val, size * cellbytes);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="address">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of bytes to fill.</param>
 * <remarks>
 *   Based on code by Slice:
 *
 *   <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781" />
 *
 *   Modified to use binary flags instead of a loop.
 *
 *   "MemSet" takes an array, the size of the array, and a value to fill it with
 *   and sets the whole array to that value.
 *
 *   "RawMemSet" is similar, but takes an AMX data segment address instead and
 *   the size is in bytes, not cells.  However, the size must still be a multiple
 *   of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RawMemSet(address /* 12 */, value /* 16 */, size /* 20 */)
{
	if (size < cellbytes)
		return 0;
	if (address < 0)
	{
		// Somewhere in COD, not DAT.  Can't use FILL because it checks the
		// address.  Unless we are running in the JIT, which doesn't have
		// checks, but we shouldn't be writing to COD after the JIT has started
		// anyway.
		do
		{
			#emit LOAD.S.pri value
			#emit SREF.S.pri address
			address += cellbytes;
		}
		while ((size -= cellbytes) > 0);
		return 1;
	}
	else //if (Server_JITComplete())
	{
		while (size >= 4096)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       4096
			address += 4096;
			size -= 4096;
		}
		if (size & 2048)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       2048
			address += 2048;
		}
		if (size & 1024)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       1024
			address += 1024;
		}
		if (size & 512)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       512
			address += 512;
		}
		if (size & 256)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       256
			address += 256;
		}
		if (size & 128)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       128
			address += 128;
		}
		if (size & 64)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       64
			address += 64;
		}
		if (size & 32)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       32
			address += 32;
		}
		if (size & 16)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       16
			address += 16;
		}
		// Might be `0` or `8`.
		if (size & (8 / cellbytes / 2 * 8))
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       8
			address += 8;
		}
		if (size & cellbytes)
		{
			#emit LOAD.S.pri value
			#emit SREF.S.pri address
		}
		return 1;
	}
//	else
//	{
//		// JIT not started/non-existant.  We can use code rewriting.
//		return 1;
//	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="address">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of bytes to fill.</param>
 * <remarks>
 *   Based on code by Slice:
 *
 *   <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781" />
 *
 *   Modified to use binary flags instead of a loop.
 *
 *   "MemSet" takes an array, the size of the array, and a value to fill it with
 *   and sets the whole array to that value.
 *
 *   "RawMemSet" is similar, but takes an AMX data segment address instead and
 *   the size is in bytes, not cells.  However, the size must still be a multiple
 *   of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `RawMemSet` (i.e. use proper capitalisation).
stock rawMemset(address /* 12 */, value /* 16 */, size /* 20 */)
{
	return RawMemSet(address, value, size);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr1">First array to compare.</param>
 * <param name="arr2">Second array to compare.</param>
 * <param name="count">How many cells to compare.</param>
 * <returns>
 *   The difference (0 if the same).
 * </returns>
 * <remarks>
 *   Returns the first found difference between two arrays.  If they are the same
 *   the return value is <c>0</c>, otherwise it is <c>arr1[i] - arr2[i]</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock MemCmp(arr1[], arr2[], count)
{
	for (new diff = 0, i = 0; i != count; ++i)
	{
		if ((diff = arr1[i] - arr2[i]))
			return diff;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr1">First array to compare.</param>
 * <param name="arr2">Second array to compare.</param>
 * <param name="count">How many cells to compare.</param>
 * <returns>
 *   The difference (0 if the same).
 * </returns>
 * <remarks>
 *   Returns the first found difference between two arrays.  If they are the same
 *   the return value is <c>0</c>, otherwise it is <c>arr1[i] - arr2[i]</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `MemCmp` (i.e. use proper capitalisation).
stock memcmp(arr1[], arr2[], count)
{
	return MemCmp(arr1, arr2, count);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr">The array to sort.</param>
 * <param name="low">The lowest index to sort.</param>
 * <param name="high">The highest index (inclusive) to sort.</param>
 * <remarks>
 *   Internal recursive call for quicksorting.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Utils_QuickSort(arr[], low, high)
{
	Debug_Print6("Utils_QuickSort: %d, %d", low, high);
	if (low < high)
	{
		new
			partition = (low + high) / 2,
			pivot = arr[partition];
		arr[partition] = arr[high],
		arr[high] = pivot,
		partition = low - 1;
		for (new j = low, tmp; j != high; ++j)
		{
			Debug_Print7("Utils_QuickSort: Test %d, %d, %d", j, arr[j], pivot);
			if ((tmp = arr[j]) < pivot)
			{
				Debug_Print7("Utils_QuickSort: Swap [%d] = %d, [%d] = %d", j, arr[j], partition + 1, arr[partition + 1]);
				// Swap.
				arr[j] = arr[++partition],
				arr[partition] = tmp;
			}
		}
		arr[high] = arr[++partition],
		arr[partition] = pivot,
		Utils_QuickSort(arr, low, partition - 1),
		Utils_QuickSort(arr, partition + 1, high);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - arrays</library>
 * <param name="arr">The array to sort.</param>
 * <param name="num">The size of the array.</param>
 * <remarks>
 *   Sorts the array in place.  Uses quick sort because it is relatively simple
 *   and pretty "quick".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock QuickSort(arr[], num = sizeof (arr))
{
	Debug_Print5("QuickSort called: %d", num);
	Utils_QuickSort(arr, 0, num - 1);
}

