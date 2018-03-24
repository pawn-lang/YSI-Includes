/*----------------------------------------------------------------------------*-
					===================================
					Y Sever Includes - Malloc Functions
					===================================
Description:
	Functions for using malloc/calloc/free type functions in PAWN.
Legal:
	Copyright (C) 2008 Alex "Y_Less" Cole

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA 02110-1301, USA.
Version:
	0.1
Changelog:
	22/12/08:
		First version.
Functions:
	Public
		-
	Core:
		-
	Stock:
		malloc - Allocate a block of memory (may be inline).
		calloc - Allocate a block of memory and blank.
		free - Free an allocated block of memory (may be inline).
		Malloc_Set - Set a value in an allocated array (may be inline).
		Malloc_Get - Get a value in an allocated array (may be inline).
		Malloc_SetS - Set a string in an allocated array.
		Malloc_GetS - Get a string in an allocated array.
		Malloc_Allocate - Do the memory allocation (may be static).
		Malloc_Free - Do the memory freeing (may be static).
		Malloc_SlotSize - Get the size of an allocated block (may be inline).
	Static:
		Malloc_Allocate - Do the memory allocation (may be stock).
		Malloc_Free - Do the memory freeing (may be stock).
	Inline:
		mget - Get data from an allocation unit.
		mset - Set data in an allocation unit.
		mgets - Get a string from an allocation unit.
		msets - Set a string in an allocation unit.
		malloc - Allocate a block of memory (may be stock).
		free - Free an allocated block of memory (may be stock).
		Malloc_Set - Set a value in an allocated array (may be stock).
		Malloc_Get - Get a value in an allocated array (may be stock).
		Malloc_NextSlot - Get the next free data block.
		Malloc_GetSlotSize - Get the size of a slot.
		Malloc_SetSlotSize - Set the size of a block.
		Malloc_GetData - Direct data access getter.
		Malloc_SetData - Direct data access setter.
		Malloc_SlotSize - Get the size of an allocated block (may be stock).
	API:
		-
Callbacks:
	-
Definitions:
	MALLOC_KB_TO_CELL - Multiplication value to convert kb to cells.
	NO_ALLOC - A failed allocation (NULL, but YSI already has NULL).
Enums:
	-
Macros:
	-
Tags:
	Alloc - An allocated block handle variable.
Variables:
	Global:
		YSI_gMallocMemory - Stores the data (may be static).
	Static:
		YSI_gMallocMemory - Stores the data (may be global).
		YSI_g_sUnusedStart - Start of free memory.
Commands:
	-
Compile options:
	MALLOC_MEMORY - Number of cells to reserve.
	MALLOC_MEMORY_KB - Number of killobytes to reserve.
	MALLOC_MEMORY_B - Number of bytes to reserve.
	MALLOC_MEMORY_MB - Number of megabytes to reserve.
	YSI_MALLOC_SECURE - Use enhanced bounds checking.
	YSI_MALLOC_NO_SHORT - Avoid conflicts with mget/mset.
Operators:
	-
-*----------------------------------------------------------------------------*/

#define MALLOC_KB_TO_CELL ((1024 * 8) / cellbits)

#define NO_ALLOC (Alloc:0)

#if !defined MALLOC_MEMORY
	#if defined MALLOC_MEMORY_KB
		#define MALLOC_MEMORY ((MALLOC_MEMORY_KB) * MALLOC_KB_TO_CELL)
	#else
		#if defined MALLOC_MEMORY_MB
			#define MALLOC_MEMORY ((MALLOC_MEMORY_MB) * 1024 * MALLOC_KB_TO_CELL)
		#else
			#if defined MALLOC_MEMORY_B
				#define MALLOC_MEMORY (((MALLOC_MEMORY_B) * 8) / cellbits)
			#else
				#define MALLOC_MEMORY (1 * 1024 * MALLOC_KB_TO_CELL)
			#endif
		#endif
	#endif
#endif

static
	YSI_g_sUnusedStart = 1;

#if defined YSI_MALLOC_SECURE
	static
#else
	new
#endif
		YSI_gMallocMemory[MALLOC_MEMORY] = {MALLOC_MEMORY - 1, 0};

forward Alloc:Malloc_Allocate(size);
forward Alloc:calloc(size);

#if defined YSI_MALLOC_SECURE
	forward Alloc:malloc(size);
#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_GetSlotSize
Params:
	slot - Allocation unit to get the size of.
Return:
	The size.
Notes:
	-
-*----------------------------------------------------------------------------*/

#define Malloc_GetSlotSize(%1) \
	(YSI_gMallocMemory[(%1) - 1])

/*----------------------------------------------------------------------------*-
Function:
	Malloc_SlotSize
Params:
	slot - Allocation unit to get the size of.
Return:
	The size.
Notes:
	-
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE

	stock Malloc_SlotSize(slot)
	{
		return Malloc_GetSlotSize(slot);
	}

#else

	#define Malloc_SlotSize(%1) \
		Malloc_GetSlotSize(%1)

#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_SetSlotSize
Params:
	slot - The allocation unit to set the size of.
	size - The size to set it to.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

#define Malloc_SetSlotSize(%1,%2) \
	YSI_gMallocMemory[(%1) - 1] = (%2)

/*----------------------------------------------------------------------------*-
Function:
	Malloc_GetData
Params:
	slot - The allocation unit to get data from.
	index - The location in the unit to get.
Return:
	The data
Notes:
	Basically like Malloc_Get but used internally.
-*----------------------------------------------------------------------------*/

#define Malloc_GetData(%1,%2) \
	(YSI_gMallocMemory[(%1) + (%2)])

/*----------------------------------------------------------------------------*-
Function:
	Malloc_SetData
Params:
	slot - The allocation unit to set in.
	index - Where in the unit to set.
	value - The value to save.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

#define Malloc_SetData(%1,%2,%3) \
	YSI_gMallocMemory[(%1) + (%2)] = (%3)

/*----------------------------------------------------------------------------*-
Function:
	mget
Params:
	slot - The allocation unit to get data from.
	index - The location in the unit to get.
Return:
	The data
Notes:
	Shorthand for Malloc_Get.
-*----------------------------------------------------------------------------*/

#if !defined YSI_MALLOC_NO_SHORT
	#define mget(%1,%2) \
		Malloc_Get(%1, %2)
#endif

/*----------------------------------------------------------------------------*-
Function:
	mset
Params:
	slot - The allocation unit to set in.
	index - Where in the unit to set.
	value - The value to save.
Return:
	-
Notes:
	Shorthand for Malloc_Set.
-*----------------------------------------------------------------------------*/

#if !defined YSI_MALLOC_NO_SHORT
	#define mset(%1,%2,%3) \
		Malloc_Set(%1, %2, %3)
#endif

/*----------------------------------------------------------------------------*-
Function:
	mgets
Params:
	target[] - Target for the string.
	len - Length of the target.
	array - Data unit to put information in.
	index - Index in the unit.
Return:
	The data
Notes:
	Shorthand for Malloc_GetS.
-*----------------------------------------------------------------------------*/

#if !defined YSI_MALLOC_NO_SHORT
	#define mgets(%1,%2,%3,%4) \
		Malloc_GetS(%1, %2, %3, %4)
#endif

/*----------------------------------------------------------------------------*-
Function:
	msets
Params:
	array - Data unit to put information in.
	index - Index in the unit.
	str[] - String to insert
Return:
	-
Notes:
	Shorthand for Malloc_SetS.
-*----------------------------------------------------------------------------*/

#if !defined YSI_MALLOC_NO_SHORT
	#define msets(%1,%2,%3) \
		Malloc_SetS(%1, %2, %3)
#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_NextSlot
Params:
	slot - The unit to get the one after of.
Return:
	-
Notes:
	Gets the next free block of memory after the current one.
-*----------------------------------------------------------------------------*/

#define Malloc_NextSlot(%1) \
	(YSI_gMallocMemory[(%1)])

/*----------------------------------------------------------------------------*-
Function:
	Malloc_Get
Params:
	array - Data unit to get information from.
	index - Index in the unit.
Return:
	Data.
Notes:
	Displays errors in secure mode.
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Get(Alloc:array, index)
	{
		return (index >= 0 && index < Malloc_GetSlotSize(_:array)) ? (Malloc_GetData(_:array, index)) : (DBGP1("Array read index out of bounds: %d[%d]", _:array, index));
	}

#else

	#define Malloc_Get(%1,%2) \
		Malloc_GetData(%1, %2)

#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_Set
Params:
	array - Data unit to put information in.
	index - Index in the unit.
	value - Value to insert
Return:
	-
Notes:
	Displays errors in secure mode.
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE

	stock Malloc_Set(Alloc:array, index, value)
	{
		return (index >= 0 && index < Malloc_GetSlotSize(_:array)) ? (Malloc_SetData(_:array, index, value)) : (DBGP1("Array write index out of bounds: %d[%d]", _:array, index));
	}

#else

	#define Malloc_Set(%1,%2,%3) \
		Malloc_SetData(%1, %2, %3)

#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_GetS
Params:
	target[] - Target for the string.
	len - Length of the target.
	array - Data unit to put information in.
	index - Index in the unit.
Return:
	-
Notes:
	Displays errors in secure mode.  Gets a string.
-*----------------------------------------------------------------------------*/

stock Malloc_GetS(target[], length, Alloc:array, index)
{
	new
		size = Malloc_GetSlotSize(_:array);
	if (index >= 0)
	{
		new
			i = 0;
		index += _:array;
		while (i < length && index < size)
		{
			if (!(target[i++] = YSI_gMallocMemory[index++]))
			{
				return 1;
			}
		}
		#if defined YSI_MALLOC_SECURE
			if (index == size)
			{
				DBGP1("Out of data (%d, %d)", _:array, index);
			}
			if (i == length)
			{
				DBGP1("Out of buffer space");
			}
		#endif
	}
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Malloc_SetS
Params:
	array - Data unit to put information in.
	index - Index in the unit.
	str[] - String to insert
Return:
	-
Notes:
	Displays errors in secure mode.  Inserts a string.
-*----------------------------------------------------------------------------*/

stock Malloc_SetS(Alloc:array, index, const str[])
{
	if (index >= 0 && index + strlen(str) < Malloc_GetSlotSize(_:array))
	{
		new
			i = 0;
		index += _:array;
		while ((YSI_gMallocMemory[index++] = str[i++])) {}
	}
	#if defined YSI_MALLOC_SECURE
		else
		{
			DBGP1("String copy failed (%s)", str);
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	malloc
Params:
	size - Size of memory to allocate.
Return:
	0 on fail or a data handle on sucess.
Notes:
	Displays errors in secure mode.
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE

	stock Alloc:malloc(size)
	{
		new
			Alloc:slot = Malloc_Allocate(size);
		if (!slot)
		{
			DBGP1("Allocation failed (%d)", size);
		}
		return slot;
	}

#else

	#define malloc(%1) \
		Malloc_Allocate(%1)

#endif

/*----------------------------------------------------------------------------*-
Function:
	calloc
Params:
	size - Size of memory to allocate.
Return:
	0 on fail or a data handle on sucess.
Notes:
	Displays errors in secure mode.  Blanks allocated mmeory.
-*----------------------------------------------------------------------------*/


stock Alloc:calloc(size)
{
	new
		Alloc:slot = Malloc_Allocate(size);
	if (slot)
	{
		new
			temp = _:slot;
		while (size--)
		{
			YSI_gMallocMemory[temp++] = 0;
		}
	}
	#if defined YSI_MALLOC_SECURE
		else
		{
			DBGP1("Allocation failed (%d)", size);
		}
	#endif
	return slot;
}

/*----------------------------------------------------------------------------*-
Function:
	free
Params:
	slot - Slot of memory to free up.
Return:
	-
Notes:
	Displays errors in secure mode.
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE

	stock free(Alloc:slot)
	{
		if (!slot || !Malloc_GetSlotSize(_:slot))
		{
			DBGP1("Free failed (%d)", _:slot);
			return 0;
		}
		return Malloc_Free(slot);
	}

#else

	#define free(%1) \
		Malloc_Free(%1)

#endif

/*----------------------------------------------------------------------------*-
Function:
	Malloc_Allocate
Params:
	size - Ammount of memory to allocate.
Return:
	Memory identifier.
Notes:
	The size check should never fail, if there's only 1 cell
	extra somewhere just sneak it onto the end of an array,
	if the user does proper bounds checking it shouldn't
	matter.
	
	Implementation code for malloc().
	
	This code will find an area in memory with sufficient
	space to store the given data and 
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Alloc:Malloc_Allocate(size)
		{
			new
				slot = YSI_g_sUnusedStart,
				p = 0,
				cs;
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
				if (cs == size + 1)
				{
					size++;
				}
				if (cs == size)
				{
					if (p)
					{
						Malloc_SetData(p, 0, Malloc_NextSlot(slot));
					}
					else
					{
						YSI_g_sUnusedStart = Malloc_NextSlot(slot);
					}
				}
				else
				{
					Malloc_SetSlotSize(slot, size);
					size++;
					cs -= size;
					size += slot;
					if (p)
					{
						Malloc_SetData(p, 0, size);
					}
					else
					{
						YSI_g_sUnusedStart = size;
					}
					Malloc_SetData(size, 0, Malloc_NextSlot(slot));
					Malloc_SetSlotSize(size, cs);
				}
				return Alloc:slot;
			}
			return NO_ALLOC;
		}

/*----------------------------------------------------------------------------*-
Function:
	Malloc_Free
Params:
	slot - Memory allocation unit to release
Return:
	-
Notes:
	Implementation code for free().
-*----------------------------------------------------------------------------*/

#if defined YSI_MALLOC_SECURE
	static
#endif
		stock Malloc_Free(Alloc:slot)
		{
			new
				size = Malloc_GetSlotSize(_:slot),
				p = YSI_g_sUnusedStart,
				l = 0;
			if (p)
			{
				while (p && p < _:slot)
				{
					l = p;
					p = Malloc_NextSlot(p);
				}
				if (p)
				{
					if (l)
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
							Malloc_SetData(_:slot, 0, p);
							Malloc_SetData(l, 0, _:slot);
						}
					}
					else
					{
						YSI_g_sUnusedStart = _:slot;
					}
					if (_:slot + size + 1 == p)
					{
						Malloc_SetSlotSize(_:slot, Malloc_GetSlotSize(p) + size + 1);
						Malloc_SetData(_:slot, 0, Malloc_NextSlot(p));
					}
					else
					{
						Malloc_SetData(_:slot, 0, p);
					}
				}
				else
				{
					new
						tmp = Malloc_GetSlotSize(l);
					if (l + tmp + 1 == _:slot)
					{
						Malloc_SetSlotSize(l, size + tmp + 1);
					}
					else
					{
						Malloc_SetData(_:slot, 0, 0);
						Malloc_SetData(l, 0, _:slot);
					}
				}
			}
			else
			{
				YSI_g_sUnusedStart = _:slot;
				Malloc_SetData(_:slot, 0, 0);
			}
			return 1;
		}
