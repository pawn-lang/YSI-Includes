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
4
6
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



