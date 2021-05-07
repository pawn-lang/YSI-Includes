# API

* `Iter_Add(Iterator, value);` - Add an in-range value from an iterator:

```pawn
// Assume "4, 9, 11" already added:
foreach (new i : MyIter)
{
	printf("%d", i);
}
printf("Adding 16...");
Iter_Add(MyIter, 16);
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Output:

```
4
9
11
Adding 16...
4
9
11
16
```

* `Iter_Remove(Iterator, value);` - Remove an in-range value from an
iterator:

```pawn
// Assume "4, 9, 11" already added:
foreach (new i : MyIter)
{
	printf("%d", i);
}
printf("Removing 9...");
Iter_Remove(MyIter, 9);
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Output:

```
4
9
11
Removing 9...
4
11
```

* `Iter_Contains(Iterator, value);` - Check if the given value is in the
given iterator:

```pawn
// Assume "4, 9, 11" already added:
printf("%d", Iter_Contains(MyIter, 6));
Iter_Add(MyIter, 6);
printf("%d", Iter_Contains(MyIter, 6));
```

Output:

```
0
1
```

* `Iter_Free(Iterator);` - Get the first INVALID value in the iterator.
Useful for finding empty slots. Returns "-1" on failure (i.e. when there are
no free slots).

```pawn
// Assume "0, 1, 3" already added:
printf("%d", Iter_Free(MyIter));
Iter_Add(MyIter, 2);
printf("%d", Iter_Free(MyIter));
```

Output:

```
2
4
```

* `Iter_FreeMulti(Iterator);` - Deprecated.

* `Iter_Count(Iterator);` - Get the number of UNIQUE elements already
added to the iterator:

```pawn
new
	Iterator:MyIter<12>;
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 5);
Iter_Add(MyIter, 9);
Iter_Add(MyIter, 9);
printf("%d", Iter_Count(MyIter));
```

Output:

```
3
```

* `Iter_Clear(Iterator);` - Reset the iterator entirely:

```pawn
// Assume "7, 10, 15" already added:
foreach (new i : MyIter)
{
	printf("%d", i);
}
printf("Resetting...");
Iter_Clear(MyIter);
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Output:

```
7
10
15
Resetting...
```

* `Iter_Random(Iterator, ...);` - Select a random added element from the
iterator. This is vastly more efficient than most other implementations:

```pawn
// Assume "0, 1, 3, 4, 6, 7, 8" already added:
printf("Random: %d", Iter_Random(MyIter));
```

POSSIBLE Output:

```
4
```

POSSIBLE Output:

```
8
```

Etc...

The extended parameters (`...`) are exclusions - values that will not be selected, allowing you to generate multiple unique random numbers.  For example:

```pawn
// Any random player.
new president = Iter_Random(Player);

// Any player except the president.
new primeMinister = Iter_Random(Player, president);

// Any player except one with an existing job.
new sheriff = Iter_Random(Player, president, primeMinister);
```

* `Iter_RandomFree(Iterator, ...);` - The opposite of `Iter_Random`, will return a random value NOT in the iterator.  Has exclusion parameters.

* `Iter_RandomAdd(Iterator, ...);` - Add a random value to the iterator and return it.  More akin to `Iter_RandomAlloc`.  Has exclusion parameters.

* `Iter_RandomRemove(Iterator, ...);` - Remove a random value from the iterator.  Has exclusion parameters.

* `Iter_Init(MDIterator);` - Normal iterators set themselves up with the
"{2 * s, 2 * s - 1, ...}" code shown above. However, you can't use that syntax
with multi-dimensional iterators, so they need explicitly initiating:

```pawn
new
	Iterator:MyIters[4]<11>;
Iter_Init(MyIters);
```

* `Iter_SafeRemove(Iterator, value, next);` - You can't use "Iter_Remove"
inside a loop that uses that iterator or it may crash:

```pawn
foreach (new i : MyIter)
{
	if (i == 5)
	{
		Iter_Remove(MyIter, i);
	}
}
```

The reason that won't work is that the loop needs to use the current slot to get
the next slot, but we just removed the current slot so it is no longer valid for
getting the next slot. Instead, we use "Iter_SafeRemove", which takes an
additional parameter to store the next slot in BEFORE the current slot is
removed:

```pawn
foreach (new i : MyIter)
{
	new
		cur = i;
	if (cur == 5)
	{
		Iter_SafeRemove(MyIter, cur, i);
	}
}
```

This is equivalent to doing:

```pawn
new i = Iter_First(MyIter);
while (i != Iter_End(MyIter))
{
	new
		cur = i,
		nxt = Iter_Next(MyIter, cur);
	if (cur == 5)
	{
		Iter_Remove(MyIter, cur);
	}
	i = nxt;
}
```

* `Iter_Size(Iterator);` - Returns the declared size of the iterator:

```pawn
new
	Iterator:MyIter<101>;
printf("%d", Iter_Size(MyIter));
```

Output:

```
101
```


* `Iter_Count(Iterator);` - Returns the number of elements added to the iterator (<= the size).


* `Iter_Alloc(Iterator);` - Convenience function for `new val = Iter_Add(Iterator, Iter_Free(Iterator));`.  Basically, add the next value to the iterator and return it.

* `Iter_Begin(Iterator);` - A technically invalid slot that comes before
the first valid slot of an iterator. Doing "Iter_Next" on this value will give
the first valid slot (if there is one at all).


* `Iter_End(Iterator);` - A value that comes after the last valid slot, to
check for having reached the end of an array.


* `Iter_Next(Iterator, cur);` - Get the iterator value after the current
one. Will return "Iter_End" when called on the very last valid value.


* `Iter_Prev`(Iterator, cur); - Get the iterator value before the current
one. Will return "Iter_Begin" when called on the very first valid value.


* `Iter_First(Iterator);` - Returns the first VALID value of the iterator,
unlike "Iter_Begin" which returns a value BEFORE the first valid value.


* `Iter_Last(Iterator);` - Returns the last valid value of the iterator,
unlike "Iter_End" which returns a value AFTER the last valid value.



* `Iter_InternalSize(Iterator);` - Returns the internal size of the
iterator. This includes the additional slot at the end of the array added on by
the "Iterator:" macro:

```pawn
new
	Iterator:MyIter<101>;
printf("%d", Iter_Size(MyIter));
```

Output:

```
102
```

﻿#### foreach
>* **Parameters:**
>	* `data`: data_INFO
>	* `as`: as_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Not exactly the same as PHP foreach, just iterates through a list and
>	returns the value of the current slot but uses that slot as the next index
>	too.  Variables must be in the form @YSII_<gname>S for the start index and
>	@YSII_<gname>A for the data array where <name> is what's entered in data.
 
***

#### iterfunc
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Used to declare a special iterator function.
 
***

#### @iterfunc
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Converts an array-like iterator to a special iterator.
 
***

#### iterstart
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Used to declare the default special iterator value.
 
***

#### Reverse
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Run an iterator backwards.
 
***

#### Iter_Init
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_Init_Internal.  When "NESTED_ELLIPSIS" is set, this isn't
>	needed because multi-dimensional iterators can be initialised with the new
>	"{{0, 1, ...), ...}" feature.  In that case "I@ = 0" is called as a "void"
>	function that does nothing but ends in a semi-colon ("I@" is used a lot in
>	YSI as a "do nothing" enabler).
>	native Iter_Init(IteratorArray:Name[]<>);
 
***

#### Iter_Add
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_AddInternal.
>	native Iter_Add(Iterator:Name<>, value);
 
***

#### Iter_Remove
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_RemoveInternal.
>	native Iter_Remove(Iterator:Name<>, value);
 
***

#### Iter_Free
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_Free_Internal.  Returns a slot NOT in the current
>	iterator.
>	native Iter_Free(Iterator:Name<>);
 
***

#### Iter_FreeMulti
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_FreeMulti_Internal.  Returns a slot NOT in the current
>	multi-iterator.
>	native Iter_FreeMulti(Iterator:Name<>);
 
***

#### Iter_Contains
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if the given value is in the given iterator.
>	native Iter_Contains(Iterator:Name<>, value);
 
***

#### Iter_GetMulti
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* Index in which the value is contained in the multi-iterator.
>* **Remarks:**
>	Checks if the given value is in the given iterator, and if it is return which index it is contained.
>	native Iter_GetMulti(Iterator:Name<>, value);
 
***

#### Iter_SafeRemove
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `value`: value_INFO
>	* `next`: next_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_SafeRemoveInternal.  Common use:
>	Iter_SafeRemove(iter, i, i);
>	native Iter_SafeRemove(Iterator:Name<>, value, &next);
 
***

#### Iter_Random
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_RandomInternal.
>	native Iter_Random(Iterator:Name<>);
 
***

#### Iter_Count
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Returns the number of items in this iterator.
>	native Iter_Count(Iterator:Name<>);
 
***

#### Iter_Clear
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Iter_Clear_Internal.
>	Although it doesn't fit my normal strict spacing, the end of "B" is correct,
>	namely: "_:F@s(%0),%2)".  This uses the "_:%0,)" macro to consume
>	a trailing comma when nothing is given in "%2", so I can't have a leading
>	space sadly.
>	"- 2" in place of the normal "- 1" is CORRECT!
>	native Iter_Clear(IteratorArray:Name[]<>);
 
***

#### Iter_Alloc
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds an empty slot in an iterator, adds that slot to the iterator, and
>	returns the now added slot.
>	native Iter_Alloc(Iterator:Name<>);
 
***

#### Iter_FastClear
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Uses a static array copy to blank the iterator instead of a loop.
>	BROKEN!
>	native Iter_FastClear(IteratorArray:Name[]<>);
 
***

#### Iter_Begin
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a point BEFORE the start of the iterator (the theoretical beginning).
 
***

#### Iter_End
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").
 
***

#### Iter_First
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the first element in an iterator.
 
***

#### Iter_Last
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the last element in an iterator.  Works by getting the previous item
>	from the one BEFORE the first element (i.e. the one before the sentinel).
 
***

#### Iter_Next
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `cur`: cur_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an iterator after the current one.
 
***

#### Iter_Prev
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `cur`: cur_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an iterator before the current one.  Slow.
 
***

#### Iter_TrueArray
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal array of an iterator.
 
***

#### Iter_TrueCount
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal count of an iterator.
 
***

#### Iter_TrueMulti
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal count of a multi-iterator.
 
***

#### Iter_TrueSize
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal size of an iterator.
 
***

#### Iter_Starts
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the number of starts in a multi-iterator.
 
***

#### Iter_Size
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the size of an iterator.
 
***

#### Iter_RandomInternal
>* **Parameters:**
>	* `count`: count_INFO
>	* `array[]`: array[]_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Returns a random value from an iterator.
 
***

#### Iter_Free_Internal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the first free slot in the iterator.
 
***

#### Iter_FreeMulti_Internal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `trueSize`: trueSize_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the first free multi index in the multi-iterator.
 
***

#### Iter_AddInternal
>* **Parameters:**
>	* `&start`: &start_INFO
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a value to a given iterator set.  Now detects when you try and add the
>	last item multiple times, as well as all the other items.  Now simplified
>	even further with the new internal representation.  The modulo code is for
>	iterator reversal.
 
***

#### Iter_RemoveInternal
>* **Parameters:**
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a value from an iterator.
 
***

#### Iter_SafeRemoveInternal
>* **Parameters:**
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>	* `value`: value_INFO
>	* `&last`: &last_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a value from an iterator safely.
 
***

#### Iter_ContainsInternal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `value`: value_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if this item is in the iterator.
 
***

#### Iter_GetMulti_Internal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `trueSize`: trueSize_INFO
>	* `size`: size_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -1 on failure.
>	* Index of the multi-iterator the value is contained.
>* **Remarks:**
>	Checks if this item is in the multi-iterator at all, and if it is returns which index it is in.
 
***

#### Iter_Clear_Internal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>	* `entries`: entries_INFO
>	* `&count`: &count_INFO
>	* `elems`: elems_INFO
>	* `lst`: lst_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Resets an iterator.
 
***

#### Iter_InitInternal
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `first[]`: first[]_INFO
>	* `s0`: s0_INFO
>	* `s1`: s1_INFO
>	* `entries`: entries_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Multi-dimensional arrays can't be initialised at compile time, so need to be
>	done at run time, which is slightly annoying.
 
***

#### Iter_PrevInternal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `elems`: elems_INFO
>	* `size`: size_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an iterator that points to the current element.
 
***

#### Iter_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a player to the loop data.  Now sorts the list too.  Note that I found
>	the most bizzare bug ever (I *think* it may be a compiler but, but it
>	requires further investigation), basically it seems that multiple variables
>	were being treated as the same variable (namely @YSII_EgotS and
>	@YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
>	same).  Adding print statements which reference these variables seem to fix
>	the problem, and I've tried to make sure that the values will never actually
>	get printed.
 
***

#### Iter_OnPlayerDisconnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a player from the loop data.  No longer uses "hook" to ENSURE
>	that this is always last.  Previously I think that the order of
>	evaluation in y_hooks meant that this got called before the user
>	"OnPlayerDisconnect".
 
***

#### Iter_OPDCInternal
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Called AFTER "OnPlayerDisconnect" so that using "Kick" inside a
>	"foreach" loop doesn't crash the server due to an OOB error.
 
***

#### foreach
>* **Parameters:**
>	* `data`: data_INFO
>	* `as`: as_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Not exactly the same as PHP foreach, just itterates through a list and
>	returns the value of the current slot but uses that slot as the next index
>	too.  Variables must be in the form @YSII_<gname>S for the start index and
>	@YSII_<gname>A for the data array where <name> is what's entered in data.
 
***

#### Itter_Init2
>* **Parameters:**
>	* `itter`: itter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_InitInternal.
>	native Iter_Init(IteratorArray:Name[]<>);
 
***

#### Itter_Add
>* **Parameters:**
>	* `itter`: itter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_AddInternal.
>	native Iter_Add(Iterator:Name<>, value);
 
***

#### Itter_Remove
>* **Parameters:**
>	* `itter`: itter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_RemoveInternal.
>	native Iter_Remove(Iterator:Name<>, value);
 
***

#### Itter_Free
>* **Parameters:**
>	* `itter`: itter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_FreeInternal.
>	native Iter_Free(Iterator:Name<>);
 
***

#### Itter_Contains
>* **Parameters:**
>	* `itter`: itter_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if the given value is in the given iterator.
>	native Iter_Remove(Iterator:Name<>, value);
 
***

#### Itter_SafeRemove
>* **Parameters:**
>	* `itter`: itter_INFO
>	* `value`: value_INFO
>	* `next`: next_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_SafeRemoveInternal.  Common use:
>	Iter_SafeRemove(iter, i, i);
>	native Iter_SafeRemove(Iterator:Name<>, value, &next);
 
***

#### Itter_Random
>* **Parameters:**
>	* `itter`: itter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_RandomInternal.
>	native Iter_Random(Iterator:Name<>);
 
***

#### Itter_Count
>* **Parameters:**
>	* `itter`: itter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Returns the number of items in this iterator.
>	native Iter_Count(Iterator:Name<>);
 
***

#### Itter_Clear
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Itter_ClearInternal.
>	native Iter_Clear(IteratorArray:Name[]<>);
 
***

#### Itter_FastClear
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Uses a static array copy to blank the iterator instead of a loop.
>	native Iter_FastClear(IteratorArray:Name[]<>);
 
***

#### Iter_Begin
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a point BEFORE the start of the iterator (the theoretical beginning).
 
***

#### Iter_End
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").
 
***

#### Iter_First
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the first element in an iterator.
 
***

#### Iter_Last
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the last element in an iterator.  Works by getting the previous item
>	from the one BEFORE the first element (i.e. the one before the sentinel).
 
***

#### Iter_Next
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `cur`: cur_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an interator after the current one.
 
***

#### Iter_Prev
>* **Parameters:**
>	* `iter`: iter_INFO
>	* `cur`: cur_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an iterator before the current one.  Slow.
 
***

#### Iter_InternalArray
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal array of an iterator.
 
***

#### Iter_InternalSize
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal size of an iterator.
 
***

#### Iter_Size
>* **Parameters:**
>	* `iter`: iter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Accesses the internal size of an iterator.
 
***

#### Itter_Create2
>* **Parameters:**
>	* `name`: name_INFO
>	* `size0`: size0_INFO
>	* `size1`: size1_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Creates a new array of iterator start/array pair.
 
***

#### foreachex
>* **Parameters:**
>	* `data`: data_INFO
>	* `as`: as_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Similar to foreach but doesn't declare a new variable for the iterator.
 
***

#### Itter_OPDCInternal
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Called AFTER "OnPlayerDisconnect" so that using "Kick" inside a "foreach"
>	loop doesn't crash the server due to an OOB error.
 
***

#### Itter_OnFilterScriptInit
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Fixes a bug where callbacks are not detected when "loadfs" is used after the
>	GM has already started.  If this is a GM this is just never used called.
 
***

#### Itter_OnGameModeInit
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	There are WIERD bugs in this script, seemingly caused by the compiler, so
>	this hopefully fixes them.  The OnFilterScriptInit code is written to be
>	very fast by utilising the internal array structure instead of the regular
>	Add functions.
 
***

#### Itter_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a player to the loop data.  Now sorts the list too.  Note that I found
>	the most bizzare bug ever (I *think* it may be a compiler but, but it
>	requires further investigation), basically it seems that multiple variables
>	were being treated as the same variable (namely @YSII_EgotS and
>	@YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
>	same).  Adding print statements which reference these variables seem to fix
>	the problem, and I've tried to make sure that the values will never actually
>	get printed.
 
***

#### Itter_OnPlayerDisconnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a player from the loop data.  No longer uses "hook" to ENSURE that
>	this is always last.  Previously I think that the order of evaluation in
>	y_hooks meant that this got called before the user "OnPlayerDisconnect".
 
***

#### Itter_RandomInternal
>* **Parameters:**
>	* `count`: count_INFO
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Returns a random value from an iterator.
 
***

#### Itter_FreeInternal
>* **Parameters:**
>	* `count`: count_INFO
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the first free slot in the iterator.  iterators now HAVE to be
>	sorted for this function to work correctly as it uses that fact to decide
>	wether a slot is unused or the last one.  If you want to use the slot
>	straight after finding it the iterator will need to re-find it to add in
>	the data.
 
***

#### Itter_AddInternal
>* **Parameters:**
>	* `&start`: &start_INFO
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a value to a given iterator set.  Now detects when you try and add the
>	last item multiple times, as well as all the other items.  Now simplified even
>	further with the new internal representation.
 
***

#### Itter_RemoveInternal
>* **Parameters:**
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a value from an iterator.
 
***

#### Itter_SafeRemoveInternal
>* **Parameters:**
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `back[]`: back[]_INFO
>	* `value`: value_INFO
>	* `&last`: &last_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a value from an iterator safely.
 
***

#### Itter_ContainsInternal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `value`: value_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if this item is in the iterator.
 
***

#### Itter_ClearInternal
>* **Parameters:**
>	* `&count`: &count_INFO
>	* `array[]`: array[]_INFO
>	* `back[]`: back[]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Resets an iterator.
 
***

#### Itter_InitInternal
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `s0`: s0_INFO
>	* `s1`: s1_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Multi-dimensional arrays can't be initialised at compile time, so need to be
>	done at run time, which is slightly annoying.
 
***

#### Itter_PrevInternal
>* **Parameters:**
>	* `array[]`: array[]_INFO
>	* `size`: size_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the element in an iterator that points to the current element.
 
***

