#define LIST__%0<%1,%2>[%3]%4; \
	%0[%1][%3+%3:1]%4,List@%0,y@L_%0[%2]; \
	PRE_INIT__ %0(){List_Init_(List@%0,y@L_%0,(_:%1)-1,_:(%3),_:(%2),YSI_gFakeList,_:%0);}

#define y@L_%0\32; y@L_
#define List@%0\32; List@

#define LIST_NONE (cellmin)

stock
	YSI_gFakeList[1][1];

stock List_Init_(&unused, entries[], slotCountMinus1, next, entryCount, slots[][], ...)
{
	// Get the real array in to an easy-to-use location.
	#emit LOAD.S.pri 36
	#emit STOR.S.pri 32

	// Easy, and probably pointless.
	unused = 0;
	
	// Set up the "unused" array.
	for (new i = 0; i != slotCountMinus1; ++i)
	{
		slots[i][next] = i + 1;
	}
	
	// Sentinel value.
	slots[slotCountMinus1][next] = LIST_NONE;
	
	// Blank all list start points.
	for (new i = 0; i != entryCount; ++i)
	{
		entries[i] = LIST_NONE;
	}
}

stock List_Add_(entry, &unused, entries[], next, entryCount, slots[][], ...)
{
	// Get the real array in to an easy-to-use location.
	#emit LOAD.S.pri 36
	#emit STOR.S.pri 32
	
	new idx = unused;
	
	if (idx == LIST_NONE)
	{
		// No more slots available.
		return LIST_NONE;
	}
	
	if (entry < 0 || entryCount <= entry)
	{
		// Invalid entry point.
		return LIST_NONE;
	}
	
	return
		// Move the unused pointer.
		unused = slots[idx][next],
		
		// Add this to the entry's list.
		slots[idx][next] = entries[entry],
		entries[entry] = idx,
		
		// Return the found index.
		idx;
}

stock bool:List_Remove_(entry, idx, &unused, entries[], slotCountMinus1, next, entryCount, slots[][], ...)
{
	// Get the real array in to an easy-to-use location.
	#emit LOAD.S.pri 44
	#emit STOR.S.pri 40
	
	if (idx < 0 || slotCountMinus1 < idx)
	{
		return false;
	}
	
	if (entry < 0 || entryCount <= entry)
	{
		// Invalid entry point.
		return false;
	}

	#define previousSlot slotCountMinus1
	previousSlot = entries[entry];
	
	// Is this the first one?
	if (previousSlot == idx)
	{
		// Yes, remove it.
		entries[entry] = slots[idx][next];
	}
	else
	{
		// No, we need to loop.
		while (previousSlot != -1)
		{
			// Check if the NEXT item is the one we want to remove.
			new cur = slots[previousSlot][next];
			if (cur == idx)
			{
				// Found it in the list.
				break;
			}
			// Not found it yet, move on.
			previousSlot = cur;
		}

		if (previousSlot == -1)
		{
			// Not in this player's list.
			return false;
		}
		
		// We've now found the item in the list BEFORE `idx`.
		slots[previousSlot][next] = slots[idx][next];
	}
	#undef previousSlot

	// And add it to the free list.
	return
		slots[idx][next] = unused,
		unused = idx,
		true;
}

#define List_Init(%0) List_Init_(List@%0,y@L_%0,sizeof(%0)-1,sizeof(%0[])-1,sizeof(y@L_%0),YSI_gFakeList,_:%0)
#define List_Add(%0,%1) List_Add_((%1),List@%0,y@L_%0,sizeof(%0[])-1,sizeof(y@L_%0),YSI_gFakeList,_:%0)
#define List_Remove(%0,%1,%2) List_Remove_((%1),(%2),List@%0,y@L_%0,sizeof(%0)-1,sizeof(%0[])-1,sizeof(y@L_%0),YSI_gFakeList,_:%0)

