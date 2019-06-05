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

