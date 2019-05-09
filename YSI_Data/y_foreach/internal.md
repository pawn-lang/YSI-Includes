# Internal Details

## Macros

The "Iterator:" macro generates two variables - one to store the main iterator
data (the array) and the other to store the number of items in the iterator (the
count):

```pawn
new
	Iterator:MyIter<7>;
```

Becomes:

```pawn
new
	// Number of items currently in the iterator.
	Iter_Single@MyIter,
	// The data in the iterator, plus internal data (all slots invalidated).
	Iterator@MyIter[7 + 1] = {14, 13, ...};
```

The names are designed to give vaguely meaningful errors - `Undefined symbol "Iterator@MyIter"` might give you some hint that an iterator is missing.  `Iter_Single` denotes a standard iterator, `Iter_Multi` denotes a multi-iterator both are the number of items currently
added to the iterator, and not the total size of the iterator.  "Iterator@MyIter"
is the values currently stored in the iterator.

Iterators are "linked lists", which means that each element points to the next
valid element. Before adding anything to the array it is declared using:

```pawn
Iterator@MyIter[7 + 1] = {7 * 2, 7 * 2 - 1, ...};
```

This declares the array as 7 cells big to store all the valid data, with an
extra cell to store the start point of the list. The initialisation data is
carefully crafted to be invalid. The use of "- 1" for the second value means
that the compiler attempts to infer a pattern to the array declaration using the
first two values (and determines that the pattern is that each slot is one less
than the previous slot). This means that the array starts off looking like:

```
14, 13, 12, 11, 10,  9,  8,  7
```

Most of those values are greater than 7, so they are invalid. Our extra slot
(the last one) has a value of "7" which is ALMOST valid. The code is designed
so that the last slot ALWAYS contains its own index, which equals the declared
size of the iterator. This is important for the linked list as will be shown
later.

After adding the values "0", "4", and "6" the array will look like:

```
 4, 13, 12, 11,  6,  9,  7,  0
``` 
 
FOUR slots have changed value - 0, 4, and 6 (the values we added to the
iterator), and slot 7 (our extra slot added by the "Iterator:" macro). Slots
1, 2, 3, and 5 have not been touched so are all still invalid (as shown by the
fact that they are all greater than the maximum valid slot value).

## Linked Lists

That's interesting, but why is it like that; and why is slot 0 "4", slot 4 "6"
etc? Each valid slot has a value LESS THAN OR EQUAL TO the iterator size. So
slot 0 is valid and has a value "<= 7" to prove it, as do slots 4, 6, and 7.
But wait, slot 7 CAN'T be valid because it is too big - only slots 0 to 6 are
within the declared range of the iterator, so why does it have a valid value
stored in it? More to the point, why is that last slot initially declared as
"7", when it shouldn't be valid?

Each valid slot's value is the index of the next valid slot. If we start at
slot 0 we get the value "4", jumping to slot 4 gives us the value "6", and slot
6 is the last item we initially added to the iterator:

```pawn
Iter_Add(MyIter, 0);
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 6);
```

Already it should be clear how "foreach" can loop over only values that exist,
unlike "for" which must loop over every possible value. From the information
above we can write:

```pawn
for (new i = Iterator@MyIter[0]; ; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

That will loop forever and output:

```
0
4
6
7
0
4
6
7
...
```

We need an end condition for the loop - which is exactly what we have the extra
slot at the end for. Slot 6 has the value "7", which is a value we have already
determined should be invalid, and indeed it is. So we can modify our loop to:

```pawn
for (new i = Iterator@MyIter[0]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

New output:

```
0
4
6
```

## Start Point

Excellent. The linked list works and ends correctly - but does it START
correctly? In this example yes, but in the more general case NO! What happens
if we never added slot 0 to the iterator?

```pawn
new
	Iterator:MyIter<7>;
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 6);
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

The output SHOULD BE:

```
4
6
```

But if we use our loop above we get:

```
14
<crash>
```

The problem is here:

```pawn
new i = Iterator@MyIter[0];
```

After adding only the values "4" and "6", the array looks like:

```
14, 13, 12, 11,  6,  9,  7,  4
```

But we start at index 0, which has the value "14". We print that value, then
try use that value as an index in to the array. The array has size "7 + 1", so
accessing slot "14" is an out-of-bounds error and won't work (or will crash or
do any other unpredictable things). So instead we need:

```pawn
for (new i = Iterator@MyIter[4]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

And if we never add ANY values to the array we still have the original:

```
14, 13, 12, 11, 10,  9,  8,  7
```

And the resulting required code is below (note that this will end instantly
because the value of slot 7 is "7", so the condition will fail immediately):

```pawn
for (new i = Iterator@MyIter[7]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

In each case, the "new i" value must be initialised to the value stored in the
first valid slot - so we need to determine WHICH is the first valid slot. That
just so happens to be stored in the last slot of the array:

```pawn
for (new first = Iterator@MyIter[7], i = Iterator@MyIter[first]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

This is, in essence, how "foreach" works, and that loop will now correctly
print all the added values (if any) in all cases.

## Improvements

Now we have a basic understanding of how "foreach" works under the hood, lets
look at how the macro itself works and generates significantly better code than
that presented above. The simplest way to present this is to show it:

Doing:

```pawn
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Gives:

```pawn
for (new i = 7; (i = Iterator@MyIter[i]) != 7; )
{
	printf("%d", i);
}
```

This is significantly simplified from the original version, but still
equivalent. The only possibly confusing part is the assignment within the
condition, but this is equivalent to:

```pawn
i = Iterator@MyIter[i];
if (i != 7)
{
	printf("%d", i);
}
else break;
```

The first action in the loop is to get the NEXT item, then use that item. Thus
we have to start with an item that is invalid or else the very first element
would always get skipped because we would have the first item and instantly get
the second item.

## Generic Loop Functions

It might help to think of the loop like this:

```pawn
for (new i = MyIter[7]; i != 7; i = MyIter[i])
{
}
```

Or more generically:

```pawn
for (new i = MyIter[START_SLOT]; i != END_VALUE; i = MyIter[i])
{
}
```

But slightly more efficient. It just so happens that "START_SLOT" and
"END_VALUE" are always the same, and always equal to the declared size of the
iterator). We can define and use the generic values:

```pawn
#define START_SLOT(%0) (sizeof (%0) - 1)
#define END_VALUE(%0)  (sizeof (%0) - 1)

for (new i = START_SLOT(Iterator@MyIter); (i = Iterator@MyIter[i]) != END_VALUE(Iterator@MyIter); )
{
	printf("%d", i);
}
```

These macros already exist in y_iterate so you don't even need the "YSII_Ag"
suffixes:

```pawn
for (new i = Iter_Begin(MyIter); (i = Iter_Next(MyIter, i)) != Iter_End(MyIter); )
{
}
```

That code is EXACTLY equivalent to the default "foreach" use, plus it gives you
more control over the looping should you so desire:

```pawn
stock PrintFivePlayers()
{
	new
		printed = 0;
	foreach (new i : Player)
	{
		printf("%d", i);
		// Limit the display.
		++printed;
		if (printed == 5) break;
	}
}
```

Using the alternate form:

```pawn
stock PrintFivePlayers()
{
	for (new i = Iter_Begin(Player), printed = 0; printed != 5 && (i = Iter_Next(MyIter, i)) != Iter_End(MyIter); ++printed)
	{
		printf("%d", i);
	}
}
```

Granted in this case the second version may be less appealing to look at, but it
does avoid the use of "break" and keeps all the loop end conditions in one
place. It also combines the efficiency of "foreach" with more code.

You may be tempted to "optimise" the loop by calling "Iter_End" just once with:

```pawn
stock PrintFivePlayers()
{
	for (new i = Iter_Begin(Player), printed = 0, end = Iter_End(MyIter); printed != 5 && (i = Iter_Next(MyIter, i)) != end; ++printed)
	{
		printf("%d", i);
	}
}
```

You can, and that will run, but "Iter_End" is actually a macro not a function
call and doing it this way is a rare case in which that will end up being LESS
efficient unfortunately.

## Reverse Iteration

Using similar methods to those above you can also go BACKWARDS through an
iterator:

```pawn
stock PrintPlayersBackwards()
{
	for (new i = Iter_End(Player); (i = Iter_Prev(MyIter, i)) != Iter_Begin(MyIter); )
	{
		printf("%d", i);
	}
}
```

However, while this was added to "y_iterate" for completeness sake, it is
INCREDIBLY inefficient and you are MUCH better off using this where possible:

```pawn
stock PrintPlayersBackwards()
{
	for (new i = MAX_PLAYERS; i--; )
	{
		if (IsPlayerConnected)
		{
			printf("%d", i);
		}
	}
}
```

This is because iterators are one-way (and very good at doing things one way),
but when you try and go backwards they can still only go forwards so must go all
theway through the whole loop until they hit the current value and know where
they came from for EVERY iteration. Tracing the loop would give something like:

```
7, 0, 4, 6, 7 - Print 6
7, 0, 4, 6 - Print 4
7, 0, 4 - Print 0
7, 0 - End
```
I did add efficient reverse iterators to the code once, but they doubled the
memory usage and were rarely (if ever) used so were basically worthless.
