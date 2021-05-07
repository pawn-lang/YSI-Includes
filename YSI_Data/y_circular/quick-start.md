# Quick Start

Here we will look at how y_iterate (aka "foreach") works. To begin with,
lets review declaring and using a standard simple iterator. This will be the
example used throughout this tutorial:

```pawn
// Declare the iterator:
new
	Iterator:MyIter<7>;
// Add any value between 0 and 6 to the iterator:
Iter_Add(MyIter, 0);
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 6);
// Use the iterator:
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Output:

```
0
4
6
```

You can add any value less than the iterator limit to the iterator, so for this
example "7" cannot be added because it is not LESS THAN 7. We also can't add
negative numbers, so the following lines will not work (they will compile, but
do nothing):

```pawn
Iter_Add(MyIter, -11);
Iter_Add(MyIter, 7);
Iter_Add(MyIter, 100);
```

## Standard Iterators

The most common use of y_iterate is just using the in-built iterators, ones already defined by the library.  The most common of these is `Player`:

```pawn
foreach (new i : Player)
{
	SendClientMessage(i, COLOR_WELCOME, "Hi");
}
```

That will loop over all connected players (so no need for `IsPlayerConnected`) and send them all a message.  It is `Player` not `Players` because of how the code is read - the sentence in English would be `for each player, do this`.
	
## Multi-Dimensional Iterators

From the original release topic it should be known that you can have arrays of
iterators (multi-dimensional, or MD, iterators):

```pawn
new
	Iterator:OwnedVehicle[MAX_PLAYERS]<MAX_VEHICLES>;
Iter_Init(OwnedVehicle);
// Add vehicles to players here...
Iter_Add(OwnedVehicle[playerid], 42);
Iter_Add(OwnedVehicle[playerid], 43);
Iter_Add(OwnedVehicle[playerid], 44);
// Other code...
foreach (new vehicleid : OwnedVehicle[playerid])
{
	printf("Player %d owns vehicle %d", playerid, vehicleid).
}
```

Originally this used "IteratorArray:" instead of "Iterator:", but that has since
been changed so you can always use either (generally using just "Iterator:").
As a result, the only important difference is the use of "Iter_Init", the
reasons for which are addressed later. Everywhere you would normally use an
iterator you can instead use a selected dimension of a multi-dimensional
iterator (in exactly the same way as you can normally use a variable or array
slot in the same places).

As a side note. Currently everything but "Iter_Init" supports 3-dimensional
iterator arrays - this function must be called for all multi-dimensional
iterators, but can't be easily if there are more than two dimensions. You can
do:

```pawn
new
	Iterator:Iter2[5]<10>;
Iter_Init(Iter2);
Iter_Add(Iter2[3], 7);
```

You can also do:

```pawn
new
	Iterator:Iter3[5][8]<10>;
//Iter_Init(Iter3);
Iter_Add(Iter3[3][6], 7);
```

But you can't currently call "Iter_Init" directly on 3d iterator arrays, despite
the fact that you need to. Instead, you have to do:

```pawn
new
	Iterator:Iter3[5][8]<10>;
for (new i = 0; i != Iter_InternalSize(Iter3); ++i)
{
	Iter_Init(Iter3[i]);
}
Iter_Add(Iter3[3][6], 7);
```

A possibly clearer way is:

```pawn
#define SIZE 5
new
	Iterator:Iter3[SIZE][8]<10>;
for (new i = 0; i != SIZE; ++i)
{
	Iter_Init(Iter3[i]);
}
Iter_Add(Iter3[3][6], 7);
```

Note that you can only do even this as of very recently. If you have a slightly
older version the code becomes:

```pawn
for (new i = 0; i != Iter_InternalSize(Iter3); ++i)
{
	Iter_InitInternal(Iter_InternalArray(Iter3[i]), Iter_InternalSize(Iter3[]), Iter_InternalSize(Iter3[][]) - 1);
}
```
