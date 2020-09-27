## Introduction

`yield` is a new keyword that basically means "return some data, but later come back to EXACTLY this spot in the code".  This is appearing in more and more languages, and now PAWN has it as well.  As a very brief example, this is invalid code.  The compiler will give a warning, since the second `print` can never be run:

```pawn
Func()
{
	print("a");
	return 42;
	print("b");
}
```

On the other hand, this code is valid, because after doing the `return`, code execution actually comes back in to the middle of the function:

```pawn
Func()
{
	print("a");
	yield return 42;
	print("b");
}
```

## Interators

Currently the only place this actually works is in special iterators.  If you are not familiar with basic special iterators, read this: http://forum.sa-mp.com/showthread.php?t=570937

A regular special iterator may look like this:

```pawn
iterfunc stock Powers(&iterstate, cur, base)
{
	if (cur)
	{
		return
			iterstate = base * cur,
			_:(iterstate > cur) * iterstate;
	}
	return 1;
}

#define iterstart@Powers iterstate(0, 0)
```

And called with:

```pawn
foreach (new i : Powers(2))
{
	// 1, 2, 4, 8, 16, ...
}
```

`foreach` calls that function once every loop, each time passing in the current value of `i` and any other required state for the function.  This gets a bit confusing, so we can replace this all with `yield`, and keep all the iterator state purely within the function:

```pawn
iterfunc stock Powers(base)
{
	for (new cur = 1; cur > 0; cur *= base)
		yield return cur;
}

#define iterstart@Powers iteryield
```

A few things to notice:

1. We declare a local variable (`cur`) and keep using it, despite repeatedly leaving the function.  This variable lives within the function's closure.  You could call this function twice in nested loops with no problems.

2. There is no return at the end of the function.  You could have one, and that value would be part of the `foreach` loop, but one isn't required (this would be a compiler warning with regular returns).  If the function ends without a `yield`, the loop instantly ends.

3. Because loop ends are determined purely by the iterator function ending, not by a special value as in other iterators, `yield` iterators can use EVERY number.

4. You can end a `yield` function early by using `return` alone as normal, or by using `yield break;`.

5. The define has changed to `iteryield` - this just tells `foreach` which type of code to use for this iterator.

6. This specific loop ends when the number overflows, but that's not special to this code.

### Example

The example for using this code is identical to the old version:

```pawn
foreach (new i : Powers(2))
{
	// 1, 2, 4, 8, 16, ...
}
```

So for each iteration of that loop, just a little bit of the iterator function is run.

### Every Value

Standard special iterator functions end when they return a certain value - by default this is `cellmin`, but it can be changed.  However, this means that there is always at least one value that can't be part of the loop ever.  Maybe that's not a problem, but `yield` iterators don't have that problem:

```pawn
iterfunc stock Number()
{
	new x = cellmin;
	do
	{
		yield return x;
		++x;
	}
	while (x != cellmin);
}

#define iterstart@Number iteryield

foreach (new i : Number())
{
	printf("%d", i);
}
```

That code will print every valid 32-bit number (so I suggest you don't actually run it).

## Variants

`yield` iterators can contain any code, as with normal function, and can "yield" as many things as desired.

Looping over this will get every number three times in a row:

```pawn
iterfunc stock NumberThrice()
{
	new x = cellmin;
	do
	{
		yield return x;
		yield return x;
		yield return x;
		++x;
	}
	while (x != cellmin);
}

#define iterstart@NumberThrice iteryield
```

A `Range` function (y_iterate actually already has one of these, not written like this as it is an old-style standard special iterator, but this is a good example anyway):

```pawn
iterfunc stock Range(start, end, step = 1)
{
	if (step < 0)
	{
		while (end < start)
		{
			yield return start;
			start += step;
		}
	}
	else
	{
		while (start < end)
		{
			yield return start;
			start += step;
		}
	}
}

#define iterstart@Range iteryield
```

Return the numbers from 0-20.  This example is not at all the easiest way of doing this, but shows a number of other techniques:

```pawn
iterfunc stock XToY(x, y)
{
	while (x != y)
		yield return x++;
}

#define iterstart@XToY iteryield

iterfunc stock ZeroToTwenty()
{
	yield return 0;
	foreach (new i : XToY(1, 10))
		yield return i;
	yield return 10;
	yield return 11;
	yield return 12;
	yield return 13;
	for (new i = 0; i != 3; ++i)
		yield return i + 14;
	yield return 17;
	for (new i = 0; i != 100; ++i)
	{
		if (i == 3)
			yield break;
		else
			yield return i + 18;
	}
	yield return 101;
}

#define iterstart@ZeroToTwenty iteryield
```

Notes:

1. Because of `yield break;`, the higher numbers will never be passed to `foreach`.

2. This has a call to another `yield` iterator.  Any valid code can be used in these functions (even recursion).

3. Some returns are in loops, some aren't.  It doesn't matter.

4. The inner `yield` function uses post-increment on the `yield return` line.  This will also work correctly and pass the old value to the loop.