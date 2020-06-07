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

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Allocation unit to get the size of.</param>
 * <returns>
 *  The size.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(Malloc_GetSlotSize(Alloc:slot));
#define Malloc_GetSlotSize(%1) \
	(YSI_gMallocMemory[_:(%1) - 1])

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Allocation unit to get the size of.</param>
 * <returns>
 *  The size.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_SlotSize(Alloc:slot)
	{
		return Malloc_GetSlotSize(slot);
	}

#else

	P:D(Malloc_SlotSize(Alloc:slot));
	#define Malloc_SlotSize(%1) \
		Malloc_GetSlotSize(%1)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="string">The string to store.</param>
 * <param name="pack">Whether or not the string will be packed.</param>
 * <returns>
 *  0 on fail or a data handle on sucess.
 * </returns>
 * <remarks>
 *  Allocates a new piece of memory with enough space to store the given string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Alloc:Malloc_NewS(const string[], bool:pack = false) {
	new
		size = pack ? ((strlen(string) + 1) char) : (strlen(string) + 1),
		Alloc:alloc = Malloc_Allocate(size, false);
	if (alloc)
	{
		if (pack)
			strpack(YSI_gMallocMemory[_:alloc], string, size);
		else
			strunpack(YSI_gMallocMemory[_:alloc], string, size);
	}
	return alloc;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to set the size of.</param>
 * <param name="size">The size to set it to.</param>
 *//*------------------------------------------------------------------------**/

P:D(Malloc_SetSlotSize(slot,size));
#define Malloc_SetSlotSize(%1,%2) \
	YSI_gMallocMemory[_:(%1) - 1] = (%2)

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to get data from.</param>
 * <param name="index">The location in the unit to get.</param>
 * <returns>
 *  The data
 * </returns>
 * <remarks>
 *  Basically like <symbolref name="Malloc_Get" /> but used internally.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Malloc_GetData(Alloc:slot,index));
#define Malloc_GetData(%1,%2) \
	(YSI_gMallocMemory[_:((%1)+Alloc:(%2))])

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to set in.</param>
 * <param name="index">Where in the unit to set.</param>
 * <param name="value">The value to save.</param>
 *//*------------------------------------------------------------------------**/

P:D(Malloc_SetData(Alloc:slot,index,value));
#define Malloc_SetData(%1,%2,%3) \
	YSI_gMallocMemory[_:((%1)+Alloc:(%2))]=(%3)

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to get data from.</param>
 * <param name="index">The location in the unit to get.</param>
 * <returns>
 *  The data
 * </returns>
 * <remarks>
 *  Shorthand for <symbolref name="Malloc_Get" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(mget(Alloc:slot, index));
#if !defined YSI_MALLOC_NO_SHORT
	#define mget(%1) \
		Malloc_Get(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to get float data from.</param>
 * <param name="index">The location in the unit to get.</param>
 * <returns>
 *  The data
 * </returns>
 * <remarks>
 *  Shorthand for <symbolref name="Malloc_GetFloat" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/
P:D(mgetf(Alloc:slot, index));
#if !defined YSI_MALLOC_NO_SHORT
	#define mgetf(%1) \
		Malloc_GetFloat(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to set in.</param>
 * <param name="index">Where in the unit to set.</param>
 * <param name="value">The value to save.</param>
 * <remarks>
 *  Shorthand for <symbolref name="Malloc_Set" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(mset(Alloc:slot, index, value));
#if !defined YSI_MALLOC_NO_SHORT
	#define mset(%1) \
		Malloc_Set(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The allocation unit to set in.</param>
 * <param name="index">Where in the unit to set.</param>
 * <param name="value">The float value to save.</param>
 * <remarks>
 *  Shorthand for <symbolref name="Malloc_SetFloat" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(msetf(Alloc:slot, index, value));
#if !defined YSI_MALLOC_NO_SHORT
	#define msetf(%1) \
		Malloc_SetFloat(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="target">Target for the string.</param>
 * <param name="length">Length of the target.</param>
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="pack">Return the string packed?</param>
 * <returns>
 *  The data
 * </returns>
 * <remarks>
 *  Displays errors in secure mode.  Gets a string.
 *  Shorthand for <symbolref name="Malloc_GetS" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(mgets(target[], length, Alloc:array, const index, const bool:pack = false));
#if !defined YSI_MALLOC_NO_SHORT
	#define mgets(%1) \
		Malloc_GetS(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="target">Target for the string.</param>
 * <param name="length">Length of the target.</param>
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <returns>
 *  The data
 * </returns>
 * <remarks>
 *  Displays errors in secure mode.  Gets an array.
 *  Shorthand for <symbolref name="Malloc_GetA" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(mgeta(target[], length, Alloc:array, index));
#if !defined YSI_MALLOC_NO_SHORT
	#define mgeta(%1) \
		Malloc_GetA(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="str">String to insert</param>
 * <param name="pack">Should the string be packed in?</param>
 * <remarks>
 *  Displays errors in secure mode.  Inserts a string.
 *  Shorthand for <symbolref name="Malloc_SetS" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(msets(Alloc:array, const index, const str[], const bool:pack = false));
#if !defined YSI_MALLOC_NO_SHORT
	#define msets(%1) \
		Malloc_SetS(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="str">Array to insert.</param>
 * <param name="len">Length of the array.</param>
 * <remarks>
 *  Displays errors in secure mode.  Inserts an array.
 *  Shorthand for <symbolref name="Malloc_SetA" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(mseta(Alloc:array, index, const str[], len));
#if !defined YSI_MALLOC_NO_SHORT
	#define mseta(%1) \
		Malloc_SetA(%1)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="slot">The unit to get the one after of.</param>
 * <remarks>
 *  Gets the next free block of memory after the current one.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Malloc_NextSlot(slot));
#define Malloc_NextSlot(%1) \
	(YSI_gMallocMemory[(%1)])

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to get information from.</param>
 * <param name="index">Index in the unit.</param>
 * <returns>
 *  Data.
 * </returns>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Get(Alloc:array, index)
	{
		if (index >= 0 && index < Malloc_GetSlotSize(_:array))
		{
			return Malloc_GetData(_:array, index);
		}
		P:C(else P:E("Array read index out of bounds: %d[%d]", _:array, index););
		return 0;
	}

#else

	P:D(Malloc_Get(Alloc:array, index));
	#define Malloc_Get(%1,%2) \
		Malloc_GetData(%1, %2)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="value">Value to insert</param>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Set(Alloc:array, index, value)
	{
		if (index >= 0 && index < Malloc_GetSlotSize(_:array))
		{
			return Malloc_SetData(_:array, index, value);
		}
		P:C(else P:E("Array write index out of bounds: %d[%d]", _:array, index););
		return 0;
	}

#else

	P:D(Malloc_Set(Alloc:array,index,value));
	#define Malloc_Set(%1,%2,%3) \
		Malloc_SetData(%1, %2, %3)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="value">Float value to insert</param>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	Float:Malloc_GetFloat(Alloc:array, index) {
		P:3("Malloc_GetFloat: array = %d, index = %d.", _:array, index);
		return Float:Malloc_Get(_:array, index);
	}
    
#else 

	P:D(Float:Malloc_GetFloat(Alloc:array, index));
	#define Malloc_GetFloat(%1,%2) \
		Float:Malloc_Get(%1,%2)

#endif


/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="value">Float value to insert</param>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/


#if defined YSI_MALLOC_SECURE

	Malloc_SetFloat(Alloc:array, index, Float:value) {
		P:3("Malloc_SetFloat called: %d, %d, %f", _:array, index, _:value);
        Malloc_Set(_:array, index, _:value);
        return 1;
	}

#else 

	P:D(Malloc_SetFloat(Alloc:array, index, Float:value));
	#define Malloc_SetFloat(%1,%2,%3) \
		Malloc_Set(%1,%2,%3)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="target">Target for the string.</param>
 * <param name="length">Length of the target.</param>
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="pack">Return the string packed?</param>
 * <remarks>
 *  Displays errors in secure mode.  Gets a string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_GetS(target[], length, Alloc:array, const index, const bool:pack = false)
{
	P:3("Malloc_GetS: array = %d, index = %d.", _:array, index);
	if (0 <= index < Malloc_GetSlotSize(_:array))
	{
		if (pack)
		{
			strpack(target, Malloc_GetData(array, index), length);
		}
		else
		{
			strunpack(target, Malloc_GetData(array, index), length);
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="str">String to insert</param>
 * <param name="pack">Should the string be packed in?</param>
 * <remarks>
 *  Displays errors in secure mode.  Inserts a string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_SetS(Alloc:array, const index, const str[], const bool:pack = false)
{
	P:3("Malloc_SetS called: %d, %d, %s", _:array, index, str);
	new
		len = strlen(str) + 1;
	if (0 <= index && index + len <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetS: In check.");
		if (pack)
		{
			strpack(Malloc_GetData(array, index), str, cellmax);
			return (len char);
		}
		else
		{
			strunpack(Malloc_GetData(array, index), str, cellmax);
			return (len);
		}
	}
	else
	{
		#if defined YSI_MALLOC_SECURE
			P:E("String copy failed (%s)", str);
		#endif
		return 0;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="arg">Offset in the stack of the string to store.</param>
 * <remarks>
 *  Inserts a string by stack offset for use in vararg functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_SetVAS(Alloc:array, index, arg)
{
	P:3("Malloc_SetVAS called: %d, %d, %d", _:array, index, arg);
	new
		len = 0;
	#emit LOAD.S.pri arg
	#emit SMUL.C     4
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADD.C      12
	#emit LOAD.I
	// For later reuse.
	#emit STOR.S.pri arg
	#emit PUSH.pri
	#emit PUSH.C     4
	#emit SYSREQ.C   strlen
	#emit STACK      8
	#emit STOR.S.pri len
	if (index >= 0 && index + (++len) <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetVAS: In check.");
		index += _:array;
		YSI_gMallocMemory[index] = 0;
		// Blank and copy the string.
		//#emit LOAD.S.pri arg
		//#emit SMUL.C     4
		//#emit LOAD.S.alt 0
		//#emit ADD
		//#emit ADD.C      12
		//#emit LOAD.I
		// Skip the code above the second time now (store the true source
		// address in "arg" the first time).
		#emit PUSH.S     len
		#emit PUSH.S     arg
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri index
		#emit IDXADDR
		#emit MOVE.alt
		#emit CONST.pri  0
		#emit STOR.I
		#emit PUSH.alt
		#emit PUSH.C     12
		#emit SYSREQ.C   strcat
		#emit STACK      16
		//strcat(YSI_gMallocMemory[index], str, cellmax);
	}
	#if defined YSI_MALLOC_SECURE
		P:C(else P:E("String copy failed (%s)", str););
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="dest">Target for the array.</param>
 * <param name="length">Length of the target.</param>
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <remarks>
 *  Displays errors in secure mode.  Gets an array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_GetA(dest[], length, Alloc:array, index)
{
	P:3("Malloc_GetA called: array = %d, index = %d, length = %d.", _:array, index, length);
	if (index >= 0)
	{
		new
			size = Malloc_GetSlotSize(_:array);
		P:5("Malloc_GetA: size = %d, %d.", size, size - index);
		memcpy(dest, YSI_gMallocMemory[index + _:array], 0, min(size - index, length) * 4, length);
		#if defined YSI_MALLOC_SECURE
			P:C(if(length > size)P:E("Out of buffer space."););
		#endif
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="source">Array to insert.</param>
 * <param name="length">Length of the array.</param>
 * <remarks>
 *  Displays errors in secure mode.  Inserts an array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_SetA(Alloc:array, index, const source[], length)
{
	P:3("Malloc_SetA: array = %d, index = %d.", _:array, index);
	if (index >= 0)
	{
		new
			size = Malloc_GetSlotSize(_:array);
		P:5("Malloc_SetA: size = %d.", size);
		memcpy(YSI_gMallocMemory[index + _:array], source, 0, min(size - index, length) * 4, size - index);
		#if defined YSI_MALLOC_SECURE
			P:C(if(length > size - index)P:E("Out of buffer space."););
		#endif
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Data unit to put information in.</param>
 * <param name="index">Index in the unit.</param>
 * <param name="arg">Offset in the stack of the array to store.</param>
 * <remarks>
 *  Inserts an array by stack offset for use in vararg functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Malloc_SetVAA(Alloc:array, index, arg)
{
	P:3("Malloc_SetVAA called: %d, %d, %d", _:array, index, arg);
	new
		len = 0;
	#emit LOAD.S.pri arg
	#emit ADD.C      1
	#emit SMUL.C     4
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADD.C      12
	#emit LOAD.I
	#emit LOAD.I
	// For later reuse.
	#emit STOR.S.pri len
	if (index >= 0 && index + len <= Malloc_GetSlotSize(_:array))
	{
		P:5("Malloc_SetVAA In check.");
		index += _:array;
		// Skip the code above the second time now (store the true source
		// address in "arg" the first time).
		#emit LOAD.S.pri len
		#emit PUSH.pri
		#emit SMUL.C     4
		#emit PUSH.pri
		#emit PUSH.C     0
		// Source.
		#emit LOAD.S.pri arg
		#emit SMUL.C     4
		#emit LOAD.S.alt 0
		#emit ADD
		#emit ADD.C      12
		#emit LOAD.I
		#emit PUSH.pri
		// Destination.
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri index
		#emit IDXADDR
		#emit MOVE.alt
		#emit CONST.pri  0
		#emit STOR.I
		#emit PUSH.alt
		// GO!
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
	}
	#if defined YSI_MALLOC_SECURE
		P:C(else P:E("Array copy out of memory."););
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="size">Size of memory to allocate.</param>
 * <returns>
 *  0 on fail or a data handle on sucess.
 * </returns>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock Alloc:malloc(size)
	{
		new
			Alloc:slot = Malloc_Allocate(size, false);
		P:C(if(!slot)P:E("Allocation failed (%d)", size););
		return slot;
	}

#else

	P:D(Alloc:malloc(size));
	#define malloc(%1) \
		Malloc_Allocate(%1)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="size">Size of memory to allocate.</param>
 * <returns>
 *  0 on fail or a data handle on sucess.
 * </returns>
 * <remarks>
 *  Displays errors in secure mode.  Blanks allocated mmeory.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Alloc:calloc(size)
{
	new
		Alloc:slot = Malloc_Allocate(size, true);
	//if (slot)
	//{
	//	new
	//		temp = _:slot;
	//	while (size--)
	//	{
	//		YSI_gMallocMemory[temp++] = 0;
	//	}
	//}
	//#if defined YSI_MALLOC_SECURE
	P:C(if(!slot)P:E("Allocation failed (%d)", size););
	//#endif
	return slot;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Slot of memory to free up.</param>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE

	stock free(Alloc:slot)
	{
		if (!slot || !Malloc_GetSlotSize(_:slot))
		{
			P:1("Free failed (%d)", _:slot);
			return 0;
		}
		return Malloc_Free(slot);
	}

#else

	P:D(free(Alloc:slot));
	#define free(%1) \
		Malloc_Free(%1)

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Slot to resize.</param>
 * <param name="size">New size of the memory.</param>
 * <param name="clear">Should we erase the memory first?</param>
 * <remarks>
 *  Displays errors in secure mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Alloc:realloc(Alloc:slot, size, const bool:clear = false)
{
	if (!size || !slot || !Malloc_GetSlotSize(_:slot))
	{
		P:1("Realloc failed (%d)", _:slot);
		return NO_ALLOC;
	}
	new
		Alloc:ret = Malloc_Allocate(size, clear);
	if (!ret)
	{
		P:1("Realloc failed (%d)", _:slot);
		return NO_ALLOC;
	}
	memcpy(YSI_gMallocMemory[_:ret], YSI_gMallocMemory[_:slot], 0, Malloc_GetSlotSize(slot) * cellbytes, size);
	Malloc_Free(slot);
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="size">Ammount of memory to allocate IN CELLS.</param>
 * <param name="cleat">Blank the memory?</param>
 * <returns>
 *  Memory identifier.
 * </returns>
 * <remarks>
 *  The size check should never fail, if there's only 1 cell
 *  extra somewhere just sneak it onto the end of an array,
 *  if the user does proper bounds checking it shouldn't
 *  matter.
 *
 *  Implementation code for <symbolref name="malloc" />.
 *
 *  This code will find an area in memory with sufficient
 *  space to store the given data and 
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Alloc:Malloc_Allocate(size, const bool:clear = false)
		{
			P:2("Malloc_Allocate called: %d, %d, %d, %d", size, YSI_g_sUnusedStart, YSI_g_sHeapStart, Malloc_GetSlotSize(YSI_g_sUnusedStart));
			// We allocate `size + 1` cells - the extra cell comes before the
			// returned allocation, and is used to store the size of the
			// allocation (for when we are freeing data).  To make allocations
			// and de-allocations easier, we allocate memory in blocks of 16
			// cells, INCLUDING the size.  Thus `size + 1` should be a multiple
			// of 16.  Round up.
			//size = ceildiv(size + 1, 16) * 16 - 1;
			size = (size & ~15) + 15;
			new
				slot = YSI_g_sUnusedStart,
				p = YSI_g_sHeapStart, // Was "0", now an offset to the heap.
				cs,
				nextSlot = 0;
			#if _DEBUG > 4
				// I think this is always generated, because `#emit` is not
				// affected by `#if`.  The print isn't though, and it is just
				// two extra instructions - not a huge burden!
				#emit LCTRL         2
				#emit STOR.S.alt    cs
				printf("Malloc_Allocate: heap = %d", cs);
			#endif
			while (slot)
			{
				cs = Malloc_GetSlotSize(slot);
				if (!cs)
				{
					return NO_ALLOC;
				}
				if (cs >= size)
				{
					break;
				}
				p = slot;
				slot = Malloc_NextSlot(slot);
			}
			if (slot)
			{
				nextSlot = Malloc_NextSlot(slot);
				if (clear)
				{
					memset(Malloc_GetData(Alloc:slot, 0), 0, size);
				}
				if (cs == size)
				{
					if (p == YSI_g_sHeapStart)
					{
						YSI_g_sUnusedStart = nextSlot;
					}
					else
					{
						Malloc_SetData(Alloc:p, 0, nextSlot);
					}
				}
				else
				{
					Malloc_SetSlotSize(slot, size);
					size++;
					cs -= size;
					size += slot;
					if (p == YSI_g_sHeapStart)
					{
						YSI_g_sUnusedStart = size;
					}
					else
					{
						Malloc_SetData(Alloc:p, 0, size);
					}
					Malloc_SetData(Alloc:size, 0, nextSlot);
					Malloc_SetSlotSize(size, cs);
				}
				return Alloc:slot;
			}
			return NO_ALLOC;
		}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Memory allocation unit to release</param>
 * <remarks>
 *  Implementation code for <symbolref name="free" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Malloc_Free(Alloc:slot)
		{
			if (slot == NO_ALLOC) return 0;
			P:4("Malloc_Free called: %d", _:slot);
			new
				size = Malloc_GetSlotSize(_:slot),
				p = YSI_g_sUnusedStart,
				l = YSI_g_sHeapStart; // Was "0", now an offset to the heap.
			P:5("Malloc_Free: size = %d", size);
			if (p)
			{
				while (p && p < _:slot)
				{
					l = p;
					p = Malloc_NextSlot(p);
				}
				if (p)
				{
					if (l == YSI_g_sHeapStart)
					{
						YSI_g_sUnusedStart = _:slot;
					}
					else
					{
						new
							tmp = Malloc_GetSlotSize(l);
						if (l + tmp + 1 == _:slot)
						{
							size += tmp + 1;
							Malloc_SetSlotSize(l, size);
							slot = Alloc:l;
						}
						else
						{
							Malloc_SetData(slot, 0, p);
							Malloc_SetData(Alloc:l, 0, _:slot);
						}
					}
					if (_:slot + size + 1 == p)
					{
						Malloc_SetSlotSize(_:slot, Malloc_GetSlotSize(p) + size + 1);
						Malloc_SetData(slot, 0, Malloc_NextSlot(p));
					}
					else
					{
						Malloc_SetData(slot, 0, p);
					}
				}
				else
				{
					p = Malloc_GetSlotSize(l) + 1;
					if (l + p == _:slot)
					{
						Malloc_SetSlotSize(l, size + p);
					}
					else
					{
						Malloc_SetData(slot, 0, 0);
						Malloc_SetData(Alloc:l, 0, _:slot);
					}
				}
			}
			else
			{
				YSI_g_sUnusedStart = _:slot;
				Malloc_SetData(slot, 0, 0);
			}
			return 1;
		}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Memory allocation unit to find</param>
 * <remarks>
 *   Transforms a memory slot in to a memory address.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ResolvedAlloc:Malloc_Resolve(Alloc:slot)
{
	#emit CONST.alt     YSI_gMallocMemory
	#emit LOAD.S.pri    slot
	#emit IDXADDR
	#emit RETN
	return ResolvedAlloc:0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="addr">Memory address to find</param>
 * <remarks>
 *   Transforms a memory address in to a memory slot.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Alloc:Malloc_Reconcile(ResolvedAlloc:addr)
{
	#emit CONST.alt     YSI_gMallocMemory
	#emit LOAD.S.pri    addr
	#emit SUB
	#emit SHR.C.pri     2
	#emit RETN
	return Alloc:0;
}

