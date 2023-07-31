## Special Iterators

Standard iterators are the array-like ones declared and used thus:

```pawn
// Declare the iterator:
new
	Iterator:MyIter<55>;
// Add any value between 0 and 54 to the iterator:
Iter_Add(MyIter, 0);
Iter_Add(MyIter, 42);
Iter_Add(MyIter, 54);
// Use the iterator:
foreach (new i : MyIter)
{
	print("%d", i);
}
```

Output:

```
0
42
54
```

This is how the `Player` iterator is defined and runs, as are many others.
However, there is another set of iterators, used indistinguishably from this
first set, but defined in a very different way - these are called "special
iterators".  These are defined by functions instead, called each iteration to give the next value:

### Example 1

Lets say you want to write an iterator to loop through all positive even
numbers. You could try do this:

```pawn
#define IsOdd(%0)  ((%0) & 1)
#define IsEven(%0) (!IsOdd(%0))

new
	Iterator:EvenInt<cellmax>;
for (new i = 0; i != cellmax; ++i)
{
	if (IsEven(i))
	{
		Iter_Add(EvenInt, i);
	}
}
foreach (new j : EvenInt)
{
	printf("%d", j);
}
```

Output:

```
0
2
4
...
```

At first glance that seems OK. We loop through every integer and add only the
even ones. But there are two issues Firstly the `Iterator:` macro adds on an
extra cell, so we end up with `EvenInt@YSII_Ag[cellmax + 1]`. `cellmax` is the
highest possible integer value, so adding 1 to it is an invalid operation and
won't compile. But assuming that it is possible to do that, we would still end
up with an array consisting of 2147483648 4-byte cells - that's exactly 8Gb of
data in your compiled mode! Again, this won't compile.

Fortunately there is another way in the form of a special iterator function:

```pawn
iterfunc stock EvenInt(cur)
{
	switch (cur)
	{
		case -1: return 0;
		case cellmax - 1: return -1;
	}
	return cur + 2;
}
```

As before we can now do:

```pawn
foreach (new j : EvenInt())
{
	printf("%d", j);
}
```

Output:

```
0
2
4
...
```

The important difference is that this will compile and run, and won't be vast!

### Explanation

```pawn
iterfunc stock EvenInt(cur)
```

This line actually starts ths special iterator function. `stock` is simply
because you don't know if your iterator will be used or not and you don't want a
warning (unless you have it in your mode and know you will use it, in which case
don't use "stock"). The next part is the function name.

```pawn
	case -1: return 0;
```

Standard iterators compile to something similar to:

```pawn
for (new i = SIZE_MINUS_1; (i = ITER[i]) != SIZE_MINUS_1; )
```

For special iterators, there is no size, so there is no start or end point using
this scheme. Instead, `-1` is used:

```pawn
for (new i = -1; (i = FUNC(i)) != -1; )
```

As a side note, this won't work for regular iterators because `-1` is not a
valid array index, so can't be used as the start value without a significant
loss in efficiency.

Anyway, `-1` is passed to the special iterator function at the start of the loop
to get the first value. Here the first value is the first positive even
integer, i.e. 0, so we return that.

```pawn
	case cellmax - 1: return -1;
```

As with `-1` as an input being the start of a special iterator, `-1` as a return
value marks the end of the special iterator. Note that this does mean that no
special iterators can ever have `-1` as a valid return unfortunately... In this
case, we need to return `-1` when we run out of positive even integers. The
last number available in signed 32bit integers is `2147483647` - defined in PAWN
as `cellmax`, but this is odd so the last positive integer must be 1 less than
that, i.e. `2147483646`, which can be written out in full or calculated as
`cellmax - 1`. Therefore, when the input to the special iterator is the last
possible positive even integer there can be no further valid returns and instead
`-1` is returned to mark the end of the loop.

```pawn
	return cur + 2;
```

This is very simple. For all other input numbers, return the next even number
after that - defined as `cur + 2`.

### Example 2

An odd numbers iterator would be almost identical, just with different start and
end values:

```pawn
iterfunc stock OddInt(cur)
{
	switch (cur)
	{
		case -1: return 1;
		case cellmax: return -1;
	}
	return cur + 2;
}
```

You could actually have another function also called `OddInt`, the `iterfunc` macro (aka `ITERFUNC__`) mangles the name to something unique only usable from within `foreach`:

```pawn
foreach (new c : OddInt())
{
}
```

You could also mangle the name manually:

```pawn
#define Iterator@OddInt iterstart(-1)

stock Iter_Func@OddInt(cur)
{
	switch (cur)
	{
		case -1: return 1;
		case cellmax: return -1;
	}
	return cur + 2;
}
```

This would mean that you could define the function without including `y_iterate`, so you can have a library declare special iterators without adding a YSI dependency.  Should someone use your library without YSI, this is just a normal unused function with no special macros, so no errors.  If they do use YSI as well, suddenly they get a load of additional enhancements.  The `iterfunc` macro simply adds the `Iter_Func@` prefix for you and defines the start values (default `-1`).

### Example 3

We've seen basic iterator functions, but we can extend them with more state and parameters, leading to very complex behaviours.  One pre-defined special iterator is `Random(n, min, max)`, which returns `n` random numbers in the range `min <= x < max`:

```pawn
iterfunc stock Random(&iterstate, cur, count, min = cellmax, max = 0)
{
	// Return a given count of random numbers:
	//   
	//   foreach (new i : Random(5))
	//   {
	//       // 5 random numbers.
	//   }
	//   
	//   foreach (new i : Random(12, 10))
	//   {
	//       // 12 random numbers between 0 and 10 (0 to 9 inclusive).
	//   }
	//   
	//   foreach (new i : Random(100, -10, 10))
	//   {
	//       // 100 random numbers between -10 and 10 (-10 to 9 inclusive).
	//   }
	//   
	// Note that this function has internal state, so you cannot call this in a
	// nested manner.  This will probably fail:
	//   
	//   foreach (new i : Random(10, 70))
	//   {
	//       foreach (new j : Random(10, 80))
	//       {
	//           // Will NOT get 100 randoms 0 to 80, plus 10 randoms 0 to 70.
	//       }
	//   }
	//   
	if (cur == cellmin)
	{
		iterstate = 0;
	}
	if (++iterstate > count)
	{
		return cellmin;
	}
	if (min >= max)
	{
		return random(min);
	}
	else
	{
		return random(max - min) + min;
	}
}

#define iterstart@Random iterstate(cellmin, 0)
```

This is the first iterator we've seen with an explicit `iterstart` declaration:

```pawn
#define iterstart@Random iterstate(cellmin, 0)
```

This declares `Random()` as an iterator function with state - it needs to track how many random numbers have been returned.  This wasn't needed on `IsEven`, because you could determine the current loop iteration from the current value.  With a random number generator, you can't.  This:

```pawn
iterstate(start, ...vars)
```

Compiles basically as:

```pawn
for (new i = start, ...vars; (i = Random(i, ...vars)) != start; )
{
}
```

The first parameter to `iterstate` is the iterator sentinel - i.e. the invalid value that represents the start and end of the loop.  The rest are just pre-loop state.  The per-loop is important, because it means you could have nested special iterator loops if you wanted without them interferring with each other:

```pawn
foreach (new i : Random(10))
{
	// Generate 10 random numbers, by default `0 <= x < cellmax`.
	foreach (new j : Random(10, 5, 100))
	{
		// Generate 10 random numbers, `5 <= x < 100`.
	}
}
```

The `iterfunc` takes the state, the current value, and all the extra parameters given (for example `(10, 5, 100)`):

```pawn
iterfunc stock Random(&iterstate, cur, count, min = cellmax, max = 0)
```

`&iterstate` will be passed by-reference if there is only one, or as an array for multiple values.
`cur` is, as before, the current iterator value (ignored in `Random` except to determine start of loop).
`count` is the first explicit parameter, and always required.
`min` and `max` are both optional, and if only `min` is given it is instead treated as `max`, with `min` becoming `0`.

### Example 4

Lets say you want to write an iterator to loop through all currently connected
RCON admins. Resulting in the equivalent of:

```pawn
foreach (new playerid : Player) if (IsPlayerAdmin(playerid))
{
}
```

A first attempt might try to use standard iterators and hook
`OnRconLoginAttempt`. This is possible, but not as easy as it would first
appear due to `OnRconLoginAttempt` not giving a playerid and the chance that
multiple players may share an IP:

```pawn
new
	Iterator:Admin<MAX_PLAYERS>;

hook OnRconLoginAttempt(ip[], password[], success)
{
	// We can't just access the logged in player directly.
	if (success)
	{
		// Rebuild the iterator.
		foreach (new playerid : Player)
		{
			if (IsPlayerAdmin(playerid) && !Iter_Contains(Admin, playerid))
			{
				// Add this admin not already in the array.
				Iter_Add(Admin, playerid);
			}
		}
	}
}

hook OnPlayerDisconnect(playerid, reason)
{
	if (Iter_Contains(Admin, playerid))
	{
		Iter_Remove(Admin, playerid);
	}
}
```

We can now do:

```pawn
foreach (new admin : Admin)
{
	// Loop over all the RCON admins.
}
```

Indeed, this is an acceptable solution (and it turns out this is actually the
BEST solution in terms of speed). However, there is an alternative route that
can be taken which is much simpler to write and avoids hooking callbacks:

```pawn
iterfunc stock Admin(cur)
{
	// Loop over all remaining players AFTER the current player.
	while (++cur != MAX_PLAYERS)
	{
		// Test if they are an admin (includes an `IsPlayerConnected` check).
		if (IsPlayerAdmin(cur))
		{
			return cur;
		}
	}
	// Generic `foreach` failure is `-1` by default.
	return -1;
}
```

The first thing to note is that the initial `-1` input is never explicitly mentioned (passed when the loop starts).
Instead it is handled generically by `++cur`, which makes `cur == 0` to begin with, and that is the correct initial value for looping over players.

The syntax to use this new special iterator version is identical to the syntax
for the original iterator version. The benefit to this being that the
implementation can be swapped out in your library without users having to
adjust their code at all:

```pawn
foreach (new admin : Admin())
{
	// Loop over all the RCON admins, using the special iterator.
}
```

Note that `RconAdmin` already exists as a built-in iterator for exactly this usage.

### Invisible Special Iterators

A normal iterator loop is:

```pawn
foreach (new i : Player)
{
}
```

A special iterator loop is:

```pawn
foreach (new i : Admin())
{
}
```

The extra brackets give the game away - users know HOW the iterator is implemented, and you can't swap it out later.  Fortunately, you can hide them with one little line:

```pawn
#define Iterator@Admin iterstart(-1)
```

This is exactly the same code as is used to declare an iterator function without using the `iterfunc` macro, thus it serves two purposes.  With that macro, the final loop in Example 4 returns to the original loop:

```pawn
foreach (new admin : Admin)
{
	// Loop over all the RCON admins, using an invisible special iterator.
}
```

## More Advanced Special Iterators

We can combine every feature so far - no y_iterate dependency, state, and more, in to one iterator:

```pawn
// Using `iterstate` not `iterstart` - either are acceptable here.
#define Iterator@Admin iterstate(MAX_PLAYERS, 0)

// The initial value of `cur` (i.e. the loop start value) is `0`.
// The initial state (`i`) is 0, because we've not displayed any admins yet.

stock Iter_Func@Admin(&i, cur, max = MAX_PLAYERS)
{
	// When `i == max` we've had enough admins listed.
	if (i++ == max)
	{
		// Custom start/end value.
		return MAX_PLAYERS;
	}

	// Loop over admins, but using an Iterator here as well.
	while (Iter_Next(Player, cur) != Iter_End(Player))
	{
		if (IsPlayerAdmin(cur))
		{
			return cur;
		}
	}

	// Out of players.
	return MAX_PLAYERS;
}
```

This code will list all the admins (note the lack of parameters):

```pawn
foreach (new i : Admin)
{
}
```

This code will list just five admins (we now have parameters):

```pawn
foreach (new i : Admin(5))
{
}
```

There is one tiny limitataion with special iterators.  If they have state (i.e. use `iterstate` not `iterstart` or no definition), this won't work:

```pawn
foreach (i : Admin(5))
{
}
```

Stateful special iterators MUST use `new`.  But there's a solution for this as well - move the state in to the function, and use `yield`...

## `yield`

`yield` (aka `YIELD__`) is a new keyword that can return control flow to an earlier point, then resume again later.  It is a form of context switching long built in to y_iterate.  Our `Admin` example would thus become:

```pawn
#define Iterator@Admin iteryield

iterfunc stock Admin()
{
	foreach (new i : Player)
	{
		if (IsPlayerAdmin(i))
		{
			yield return i;
		}
	}
}
```

This is again a silent special iterator; but instead of `iterstart` or `iterstate`, uses `iteryield`; and MUST be declared with `#define`, unlike earlier ones.  There are a few interesting things to note about this function:

* There is no `return` at the end.  This isn't a mistake, and isn't a warning.  When the function ends without using `yield`, it signals the end of the iterator.

* Because there is no end value (sentinel value) you can return every possible number from a `yield` iterator and still end the loop.  This is the only way to make a loop over every integer without needing to reserve one for the start and end conditions:

```pawn
#define Iterator@EveryInteger iteryield

iterfunc stock EveryInteger()
{
	new i = cellmin;
	do
	{
		yield return i;
	}
	while (++i != cellmin);
}
```

* There is no state passed in, nor is there a `cur` variable.  All your state is stored locally in the function, using a closure.

* You can return early, without using `yield` to end the loop:

```pawn
#define Iterator@RandomAmountOf100s iteryield

iterfunc stock RandomAmountOf100s()
{
	for ( ; ; )
	{
		if (random(100) == 0)
		{
			return;
		}
		yield return 100;
	}
}
```

* You can have as many `yield`s in your function as you like:

```pawn
#define Iterator@ManyYields iteryield

iterfunc stock ManyYields()
{
	for (new i = 0; i != 3; ++i)
	{
		yield return i;
	}
	yield return 10;
	yield return 20;
	for (new i = 501; i != 505; ++i)
	{
		yield return i;
	}
}
```

* `yield` iterators can call other `yield` iterators.  Indeed, because these iterators can be invisible special functions, you may again not know that the function called is an `iteryield` function:

```pawn

iterfunc stock Iter1(num, mul)
{
	while (num--)
	{
		yield return (num * mul);
	}
}
#define Iterator@Iter1 iteryield

iterfunc stock Iter2(end = -1)
{
	FOREACH__ (new i : Iter1(3, 10))
	{
		yield return i + 1;
		yield return i + 2;
		yield return i + 3;
		yield return i + 4;
		yield return i + 5;
	}
	
	yield return end;
}
#define Iterator@Iter2 iteryield

MyCode()
{
	foreach (new i : Iter2)
	{
		printf("%d", i);
	}
}
```

That code will print:

```
21
22
23
24
25
11
12
13
14
15
1
2
3
4
5
-1
```

## Special Array Iterators

An example of owned vehicles could look like:

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

Like the `Admin` example this code works fine, but uses a lot of memory. For
500 players and 2000 vehicles the main array takes up `500 * (2000 + 1)` cells,
which is just over 3Mb. That's not a vast amount of memory on modern computers,
but it might still be worth reducing. For some examples a reduction may not be
possible, but in this case a vehicle can only have one owner so there's no point
storing every vehicle for every player. A better storage option would be:

```pawn
new
	gVehicleOwner[MAX_VEHICLES];
```

Here `gVehicleOwner` stores the player ID of the owning player for each vehicle.
To print all the vehicles belonging to one player now looks like:

```pawn
for (new vehicleid = 0; vehicleid != MAX_VEHICLES; ++vehicleid)
{
	if (gVehicleOwner[vehicleid] == playerid)
	{
		printf("Player %d owns vehicle %d", playerid, vehicleid).
	}
}
```

This is a significant reduction in memory, but we had to re-write the code to
accommodate it.  We know we can write special iterators that are
functions, but look like normal iterators, can we also write a function to hide this
representation as well, from an array of iterators? Yes - quite easily in fact. The original loop was:

```pawn
foreach (new vehicleid : OwnedVehicle[playerid])
{
	printf("Player %d owns vehicle %d", playerid, vehicleid).
}
```

This is yet another use of `#define Iterator@` - allowing us to hide the fact that not only are varibles now functions, but also so are arrays:


```pawn
#define Iterator@OwnedVehicle iterstart(-1)

iterfunc stock OwnedVehicle(cur, ownerid)
{
	do
	{
		// The initial value is "-1", increment it to 0, and always increment
		// after that.
		if (++cur == MAX_VEHICLES) return -1;
		// Stay in this function until we find a vehicle this player owns, or
		// we run out of vehicles to test.
	}
	while (gVehicleOwner[cur] != ownerid);
	return cur;
}

foreach (new vehicleid : OwnedVehicle[playerid])
{
	printf("Player %d owns vehicle %d", playerid, vehicleid).
}
```

An additional benefit is that you can't modify special iterators directly. If
we use the first version of "OwnedVehicle" user code can include:

```pawn
Iter_Add(OwnedVehicle[playerid], 42);
```

If you use the special iterator version and try call that function it will
generate a compile-time error. This makes it essentially a read-only iterator
unless you have access to the underlying data store. If this iterator comes
from a vehicle ownership library you may have a function such as:

```pawn
Vehicle_SetOwner(vehicleid, playerid);
```

Which will add that owner to the `gVehicleOwner` array, while checking that the
vehicle isn't already owned and doing anything else. This way you can keep
`gVehicleOwner` as `static` to your library so that no-one can access private
data except through your well-defined API.

## Multi-Dimensional Iterators

The owned vehicles example above is such a common use-case that it has been integrated directly in to the library.  A vehicle can only have one owner, so an array of iterators is very inefficient:

```pawn
new
	Iterator:OwnedVehicle[MAX_PLAYERS]<MAX_VEHICLES>;
```

Not only does this waste a lot of space, but there's nothign preventing this:

```pawn
Iter_Add(OwnedVehicle[4], 10);
Iter_Add(OwnedVehicle[6], 10);
```

This will make both players 4 and 6 owner of vehicle 10.  The alternative is to make multiple intertwined iterators, so that each element can be a member of only one at once:

```pawn
new
	Iterator:OwnedVehicle<MAX_PLAYERS, MAX_VEHICLES>;
Iter_Add(OwnedVehicle<4>, 10); // Fine.
Iter_Add(OwnedVehicle<6>, 10); // Will fail.
```

Several functions can take either a specific start, e.g. `<playerid>`, or operate over the whole set together with `<>`:

```pawn
Iter_Contains(OwnedVehicle<4>, 10); // true.
Iter_Contains(OwnedVehicle<6>, 10); // false.
Iter_Contains(OwnedVehicle<>, 10); // true.
```

Looping also takes a start point (you can't loop over `<>`):

```pawn
foreach (new vehicleid : OwnedVehicle<playerid>)
{
	printf("Player %d owns vehicle %d", playerid, vehicleid).
}
```

## Existing Special Iterators

### `Bits`

"y_bit" provides the "Bits" iterator, which takes a bit array and loops over all
the bits set within it:

```pawn
new
	BitArray:arr<100>;
Bit_Set(arr, 42, true);
Bit_Set(arr, 82, true);
Bit_Set(arr, 11, true);
Bit_Set(arr, 99, true);
Bit_Set(arr, 7, true);
foreach (new c : Bits(arr))
{
	printf("%d", c);
}
```

Output:

```
7
11
42
82
99
```

### `Blanks`

Like `Bits`, but returns all the `0` slots instead.


```pawn
new
	BitArray:arr<100>;
Bit_SetAll(arr, true);
Bit_Set(arr, 18, false);
Bit_Set(arr, 9, false);
Bit_Set(arr, 5, false);
Bit_Set(arr, 80, false);
Bit_Set(arr, 88, false);
foreach (new c : Blanks(arr))
{
	printf("%d", c);
}
```

Output:

```
5
9
18
80
88
```

### `Range`

```pawn
foreach (new i : Range(min, max))
```

Equivalent to:

```pawn
for (new i = min; i != max; ++i)
```

```pawn
foreach (new i : Range(min, max, step))
```

Equivalent to:

```pawn
for (new i = min; i < max; i += step)
```

### `N`

Loops *n* times:

```pawn
foreach (new i : N(10))
```

### `Powers`

```pawn
// Loop through the powers of 2 (1, 2, 4, 8, etc.)
foreach (new i : Powers(2))
```

### `Fib`

```pawn
// Loop through the Fibbonacci sequence (1, 1, 2, 3, 5, 8, etc).
foreach (new i : Fib())
```

### `Random`

Generate a number of random numbers.  Uses:

```pawn
// Loop 5 times with any random number.
foreach (new i : Random(5))
```

```pawn
// Loop 5 times with any random number 0 <= n < 100
foreach (new i : Random(5, 100))
```

```pawn
// Loop 5 times with any random number 100 <= n < 1000
foreach (new i : Random(5, 100, 1000))
```

### `Null`

```pawn
// Return every index of the array that contains `0`.
foreach (new i : Null(arr))
```

### `NonNull`

```pawn
// Return every index of the array that doesn't contain `0`.
foreach (new i : NonNull(arr))
```

### `Until`

```pawn
new arr[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
}

// Return every index until one equals the given value.
foreach (new i : Until(6, arr))
```

Output:

```
0
1
2
3
4
```

Index `5` contains `6`, so the loop then ends.

### `Filter`

```pawn
new arr[] = {
	1, 6, 7, 8, 6, 2, 9, 6
}

// Return every index that contains the given value.
foreach (new i : Filter(6, arr))
```

Output:

```
1
4
7
```

## Iterator Manipulators

These special iterators themselves take an iterator.

### `None`

Return all values NOT in the given iterator:

```pawn
new Iterator:x<5>
Iter_Add(x, 3);
foreach (new i : None(x))
```

Output:

```
0
1
2
4
```

Called `None` because it also works for multi-dimensional iterators:

```pawn
new Iterator:x<5, 5>
foreach (new i : None(x<>))
```

### `All`

This doesn't work:

```pawn
new Iterator:x<5, 5>
foreach (new i : x<>)
```

That will not loop over every value in every slot of the multi-dimensional iterator.  However, this will:

```pawn
new Iterator:x<5, 5>
foreach (new i : All(x<>))
```

### `Reverse`

Goes through an iterator backwards:

```pawn
foreach (new i : Reverse(Player))
```

## Main Iterators

### `Player`

Loop over all players (excludes NPCs):

```pawn
foreach (new i : Player)
```

### `StreamedPlayer`

Loop over all players streamed in for another player (excludes NPCs):

```pawn
foreach (new i : StreamedPlayer[playerid])
```

### `Bot`/`NPC`

Loop over all bots (NPCs):

```pawn
foreach (new i : Bot)
```

### `StreamedBot`

Loop over all bots streamed in for a player:

```pawn
foreach (new i : StreamedBot[playerid])
```

### `Character`

Loop over all bots and players:

```pawn
foreach (new i : Character)
```

### `StreamedCharacter`

Loop over all bots and players streamed in for another player

```pawn
foreach (new i : StreamedCharacter[playerid])
```

### `Actor`

Loop over all actors:

```pawn
foreach (new i : Actor)
```

### `StreamedActor`

Loop over all actors streamed in for a player:

```pawn
foreach (new i : StreamedActor[playerid])
```

### `Vehicle`

Loop over all vehicles:

```pawn
foreach (new i : Vehicle)
```

### `LocalVehicle`

Loop over all vehicles created in the current mode:

```pawn
foreach (new i : LocalVehicle)
```

### `StreamedVehicle`

Loop over all vehicles streamed in for a player:

```pawn
foreach (new i : StreamedVehicle[playerid])
```

### `VehicleOccupant`

Loop over all players (driver and passengers) in any vehicle:

```pawn
foreach (new i : VehicleOccupant)
```

Or loop over all players in a single vehicle:

```pawn
foreach (new i : VehicleOccupant[vehicleid])
```

### `VehicleDriver`

Loop over all players driving a vehicle:

```pawn
foreach (new i : VehicleDriver[vehicleid])
```

Loop over all players driving any vehicle:

```pawn
foreach (new i : VehicleDriver)
```

### `VehiclePassenger`

Loop over all passengers in a vehicle:

```pawn
foreach (new i : VehiclePassenger[vehicleid])
```

Loop over all passengers in any vehicle:

```pawn
foreach (new i : VehiclePassenger)
```

### `Command`

Loop over all y_commands command IDs:

```pawn
foreach (new i : Command)
```

### `PlayerCommand`

Loop over all y_commands command IDs that the given player can use:

```pawn
foreach (new i : PlayerCommand[playerid])
```

### `Group`

Loop over all y_groups groups:

```pawn
foreach (new Group:g : Group)
```

### `PlayerGroups`

Loop over all y_groups groups a single player is in:

```pawn
foreach (new Group:g : PlayerGroups[playerid]) // [sic]
```

### `GroupMember`

Loop over everyone in a y_groups group:

```pawn
foreach (new i : GroupMember[groupid]) // [sic]
```

### `Group_...`

For every library that uses y_groups for permissions, there is an iterator to loop over items from
that library in a group.  For example, to loop over all the commands enabled in a group:

```pawn
foreach (new i : Group_Command[groupid])
```

### `RCON`

Every player logged in as an RCON admin:

```pawn
foreach (new i : RconAdmin)
```

## You don't need n-dimensional arrays.

### Introduction

To prove this, I'm going to take a common example - warrants: 

* Police can issue warrants for players' arrest.
* Each player can have several warrants out on them.
* A warrant has a time, issuing officer, and a message.

The naïve coder will put all of this information in their monolithic `PlayerInfo` array:

```pawn
#define MAX_WARRANTS (5)
#define MAX_WARRANT_MESSAGE (32)

enum E_PLAYER_INFO
{
	// ...
	E_WARRANT_TIME[MAX_WARRANTS],
	E_WARRANT_ISSUER[MAX_WARRANTS],
	E_WARRANT_MESSAGE[MAX_WARRANTS][MAX_WARRANT_MESSAGE]
	// ...
}

new PlayerInfo[MAX_PLAYERS][E_PLAYER_INFO];
```

The slightly less stupid coder will know not to put everything in one huge array and will try keep things isolated:

```pawn
#define MAX_WARRANTS (5)
#define MAX_WARRANT_MESSAGE (32)

enum E_PLAYER_WARRANTS
{
	E_WARRANT_TIME[MAX_WARRANTS],
	E_WARRANT_ISSUER[MAX_WARRANTS],
	E_WARRANT_MESSAGE[MAX_WARRANTS][MAX_WARRANT_MESSAGE]
}

static gPlayerWarrants[MAX_PLAYERS][E_PLAYER_WARRANTS];
```

But there are already several obvious, and not so obvious, problems with this:

1. That's a 2d array inside an enum (`E_WARRANT_MESSAGE`) - pawn can't do that (and this is a GOOD thing).
2. There's a hard limit on warrants per-player.  What happens if someone gets a sixth?
3. This is incredibly space inefficient.  You need to cater for the worst-case scenario, even though 90% of your players may never get a warrant.

You end up wasting massive amounts of space, with hundreds of warrant slots never used, while still being very limited in how many warrants a single player could have.  If only there was a way to combine all players' warrants together so there was a single huge global limit, instead of a tiny per-player limit.  There is, and I'm going to show you how:

```pawn
#define MAX_WARRANTS (500)
#define MAX_WARRANT_MESSAGE (32)

enum E_PLAYER_WARRANT
{
	E_WARRANT_TIME,
	E_WARRANT_ISSUER,
	E_WARRANT_MESSAGE[MAX_WARRANT_MESSAGE]
	E_WARRANT_NEXT,
}

static gWarrants[MAX_WARRANTS][E_PLAYER_WARRANTS];
static gPlayerWarrants[MAX_PLAYERS];
static gUnusedWarrants;
```

Assuming `MAX_PLAYERS` is 500, the old code used about 340kb of data for a maximum of 5 warrants per player.  This new version uses around 72kb and has a maximum number of warrants for one single player of 500.  If you wanted, you could assign every single warrant to one extremely bad player.  So work out how many TOTAL warrants you'll have an any one time and set the limit to exactly that number.  Now it might become a little clearer what we're going to do if you mentally replace `E_WARRANT_NEXT` with `E_WARRANT_PLAYER` - each slot knows which player it is assigned to, so you can loop through all the warrants to find just the ones for that player.  However, that would be very inefficient in time, and we can do one better.  This is where the fundamental idea of lists comes in.

### Lists

A list (more specifically a linked list) is a data structure where each element tells you where the next one is.  In our example `gPlayerWarrants` stores the index of the FIRST warrant for every player (`-1` if they don't have a warrant).  You go to that index in `gWarrants` and read the information.  Then, from that slot, you read `E_WARRANT_NEXT` and it tells you the index of the next warrant for that player (or `-1` if you've finished the list).  They may have warrants in slots `3`, `66`, and `209`, but you don't need to loop through the entire array to discover this fact.  You just follow the stored indexes.  `gUnusedWarrants` stores the index of the first free slot - that is, the first data available for storing a newly issued warrant; and that too is chained through the whole array.  Initialisation is simple:

```pawn
hook OnScriptInit()
{
	for (new i = 0; i != MAX_WARRANTS - 1; ++i)
	{
		// Construct the chain.
		gWarrants[i][E_WARRANT_NEXT] = i + 1;
	}
	// Start of the list.
	gUnusedWarrants = 0;
	
	// End of the list.
	gWarrants[MAX_WARRANTS][E_WARRANT_NEXT - 1] = -1;
}
```

To add a new warrant to a player, you remove it from the unused list (by changing the pointer of the first unused slot) and add it to that player's list (at the start is simplest):

```pawn
GetNewWarrant(playerid)
{
	// Get a free slot.
	new idx = gUnusedWarrants;
	if (idx == -1)
	{
		return -1;
	}
	
	// Move the unused warrants pointer.
	gUnusedWarrants = gWarrants[idx][E_WARRANT_NEXT];
	
	// Add this to the player's list.
	gWarrants[idx][E_WARRANT_NEXT] = gPlayerWarrants[playerid];
	gPlayerWarrants[playerid] = idx;
	
	// Return it, so we can write the data to `gWarrants[idx]`.
	return idx;
}
```

Some of you might even notice that this assignment code is actually simpler than it would be in the first enum version, where you have to loop over the whole set of per-player warrants and check if any one is empty.

To loop over a player's warrants is simply traversing the list.  Incidentally, this is EXACTLY how y_iterate/foreach works:

```pawn
for (new idx = gPlayerWarrants[playerid]; idx != -1; idx = gWarrants[idx][E_WARRANT_NEXT])
{
	// `idx` is a valid index in to `gWarrants` pointing to a warrant for that player.
}
```

Removing an item from a list is the most complex operation, especially when it is in the middle of the list.  You have to update the previous item (or initial pointer) to point to the following item, but even this isn't that complex:

```pawn
ReleaseWarrant(playerid, idx)
{
	// Is this the first one?
	if (gPlayerWarrants[playerid] == idx)
	{
		// Yes, remove it.
		gPlayerWarrants[playerid] = gWarrants[idx][E_WARRANT_NEXT];
	}
	else
	{
		// No, we need to loop.
		new prev = gPlayerWarrants[playerid];
		while (prev != -1)
		{
			// Check if the NEXT item is the one we want to remove.
			new cur = gWarrants[prev][E_WARRANT_NEXT];
			if (cur == idx)
			{
				// Found it in the list.
				break;
			}
			// Not found it yet, move on.
			prev = cur;
		}

		if (prev == -1)
		{
			// Not in this player's list.
			return;
		}
		
		// We've now found the item in the list BEFORE `idx`.
		gWarrants[prev][E_WARRANT_NEXT] = gWarrants[idx][E_WARRANT_NEXT];
	}

	// And add it to the free list.
	gWarrants[idx][E_WARRANT_NEXT] = gUnusedWarrants;
	gUnusedWarrants = idx;
}
```

### y_iterate

Lets look at the previous example using the new y_iterate extension:

```pawn
enum E_PLAYER_WARRANT
{
	E_WARRANT_TIME,
	E_WARRANT_ISSUER,
	E_WARRANT_MESSAGE[MAX_WARRANT_MESSAGE]
}

static LIST__ gWarrants<MAX_WARRANTS, MAX_PLAYERS>[E_PLAYER_WARRANT];
```

Then you get all of y_iterate for free:

```pawn
new idx = Itter_Alloc(gWarrants<playerid>);
```

```pawn
Iter_Remove(gWarrants<player>, idx);
```

```pawn
foreach (new idx : gWarrants<player>)
{
	printf("Warrant issued at %d by %d", gWarrants[idx][E_WARRANT_TIME], gWarrants[idx][E_WARRANT_ISSUER]);
}
```

For reference, this is just a wrapper around:


```pawn
enum E_PLAYER_WARRANT
{
	E_WARRANT_TIME,
	E_WARRANT_ISSUER,
	E_WARRANT_MESSAGE[MAX_WARRANT_MESSAGE]
}

static gWarrants[MAX_WARRANTS][E_PLAYER_WARRANT];
static Iterator:gWarrants<MAX_WARRANTS, MAX_PLAYERS>;
```

Which works thanks to the fact that `Iterator:` mangles some names internally, allowing you to seemingly have to variables with the same name - the iterator and the data array.  This made the implementation of this feature exactly one line long:

```pawn
#define LIST__%0<%1,%2> Iterator:%0<%1,%2>,%0[%1]
```

