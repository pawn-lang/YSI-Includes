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

	
