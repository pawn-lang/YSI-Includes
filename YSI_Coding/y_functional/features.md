## Lambdas

A "lambda" is a function declared inline, that is, inside a call to another function.  In javascript they look like this:

```javascript
array.map((idx) => idx + 1)
```

Here this is a function:

```javascript
(idx) => idx + 1
```

It is (almost\*) the same as:

```javascript
function (idx) {
  return idx + 1;
}
```

*y_functional* also introduces basic lambdas, though with slightly different syntax.  Instead of specifying the parameters, they are automatically named `_0`, `_1`, etc.  A function like `Map` takes a function that only needs a single parameter, so a passed lambda only has `_0`:

```pawn
Map({ _0 + 1 }, array);
```

Thanks to the underlying use of *y_inline* (or, more strictly, *indirection.inc*) these are all equivalent:

```pawn
public AddOne(n)
{
	return n + 1;
}

Map(using public AddOne, array);
```

```pawn
static stock AddOne(n)
{
	return n + 1;
}

Map(&AddOne, array);
```

```pawn
inline AddOne(n)
{
	return n + 1;
}

Map(using inline AddOne, array);
```

And, ultimately, these are all just a loop (but, especially with the lambda, way simpler):

```pawn
for (new i = 0; i != sizeof (array); ++i)
{
	array[i] + 1;
}
```

Now, the keen-eyed amongst you may have noticed something there - `array[i] + 1` doesn't actually do anything.  It adds `1` to an array, then, what?  The result doesn't go anywhere (and indeed, this would be a compiler warning).  You need to save the result:

```pawn
for (new i = 0; i != sizeof (array); ++i)
{
	dest[i] = array[i] + 1;
}
```

Which in `Map` terms translates to\*\*:

```pawn
Map({ _0 + 1 }, array, dest);
```

## Functions

As well as lambdas, this library provides several functions for quickly manipulating arrays.  They are common in functional programming circles, but PAWN isn't functional programming.  Often they are just odd names for common structures (I'm not going to explain WHY things have these names, there are reasons though).

### `Map`

A `map` is when you do the same thing to every element of an array: for example increase them all by 1, or print them all.  In SA:MP this is usually done as a loop, the example below will "map `+7` over `array`":

```pawn
new
	array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	dest[sizeof (array)];
for (new i = 0; i != sizeof (array); ++i)
{
	dest[i] = array[i] + 7;
}
```

Using *y_functional*, instead you pass an expression to run for every element of the array, an array to run the code on, and an array to store the results in:

```pawn
Map({_0 + 7}, array, dest);
```

The syntax is not too difficult to understand, but still not entirely obvious.  The code between the braces is what is run for every element of the array.  The variable called `_0` is the contents of the current array index.  Think of it like this:

```pawn
for (new i = 0; i != sizeof (array); ++i)
{
	new
		_0 = array[i],
		result = (_0 + 7); // This is the part you specify.
	dest[i] = result;
}
```

What if you want to modify the input array, instead of writing the results to a different array?  This is simple - just give the same array as the input and output:

```pawn
Map({_0 + 7}, array, array);
```

What if you don't actually want to store the results?  Say if you want to print every element of the array, but do no processing?  This again is simple:

```pawn
Map_({printf("%d", _0)}, array);
```

The `_` suffix means that there is nothing to return.

What if you want to know the current index, as well as the current value?  For this there are the `MapIdx` functions:

```pawn
MapIdx_({printf("array[%d] = %d", _0, _1)}, array); // Note that the index is `_0`.
MaxIdx({_1 / _0}, array, dest);
```

### `Fold`

A `fold` converts an array to a single value in some way, for example by adding up all the values.  A `fold` uses all the elements of the array to get the final value, and again is normally done via a loop with an extra variable.  The total (sum) example would be:

```pawn
new
	array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	total = 0;
for (new i = 0; i != sizeof (array); ++i)
{
	total = total + array[i];
}
```

This becomes:

```pawn
new
	total = FoldL({_0 + _1}, 0, array);
```

Unlike `Map` there is no destination array since we are only storing one value.  `_0` is the running total, `_1` is the current array cell.  The second function parameter, `0`, is the initial value of the loop.  For the product (what you get when you multiply every value up), the initial value must be `1` since `0 * x = 0` always:

```pawn
new
	total = FoldL({_0 * _1}, 1, array);
```

### `FoldL and FoldR`

Both of the examples above used `FoldL` - the `L` stands for `Left`, but the `Right` version would have worked two, so what is the difference?

Consider this example:

```pawn
new
	array[] = {5, 10, 4};
	total = FoldL({_0 / _1}, 1000, array);
```

This evaluates as:

```pawn
new
	total = (((1000 / 5) / 10) / 4); // = 5
```

Because `/` is not commutative, this is a different sum:

```pawn
new
	total = (1000 / (5 / (10 / 4))); // = 500
```

They are the same numbers in the same written order, but give different results according to the evaluation order.

### `Scan`

A `scan` is like a `fold`, but keeps all the intermediate results as well.  To demonstrate this I'll use a more complete `sum` example:

```pawn
new
	array[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	scan[sizeof (array) + 1]. // + 1.
	total = 0;
for (new i = 0; i != sizeof (array); ++i)
{
	scan[i] = total;
	total = total + array[i];
}
scan[sizeof (array)] = total;
```

After this code `total` is 10 (equal to adding up 10 1s), the array `scan` becomes:

```
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
```

Another example:

Input:

```
array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
```

Output:

```
scan = { 0, 0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
```

Just to demonstrate how this came about:

```
scan = {
	0,
	0 + 0,
	0 + 0 + 1,
	0 + 0 + 1 + 2,
	0 + 0 + 1 + 2 + 3,
	0 + 0 + 1 + 2 + 3 + 4,
	0 + 0 + 1 + 2 + 3 + 4 + 5,
	0 + 0 + 1 + 2 + 3 + 4 + 5 + 6,
	0 + 0 + 1 + 2 + 3 + 4 + 5 + 6 + 7,
	0 + 0 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8,
	0 + 0 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9
};
```

Note that `0` appears twice in the output because that is both the initial value of `total` AND the first value in the input array.  If you know that your input always has at least one value (which, to be fair, arrays in pawn always should) you can use `Scan1`, which doesn't take an initial value\*\*\*.

### `Filter`

A `filter` finds all arrays elements that meet some value.  For example, to get all the positive values in an array:

```pawn
new
	array[10] = {1, -2, 4, -8, 16, -32, 64, -126, 256, -512},
	dest[sizeof (array)],
	count;
for (new i = 0; i != sizeof (array); ++i)
{
	if (array[i] > 0)
	{
		dest[count++] = array[i];
	}
}
```

To check which array elements are connected players:

```pawn
new
	array[10] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90},
	dest[sizeof (array)],
	count;
for (new i = 0; i != sizeof (array); ++i)
{
	if (IsPlayerConnected(array[i]))
	{
		dest[count++] = array[i];
	}
}
```

Here `count` returns the number of elements found, and `dest` includes them all.

### `Zip`

A `zip` combines two or more arrays in to one.  This example simply adds them:

```pawn
new
	array1[10] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90},
	array2[10] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9},
	dest[sizeof (array1)],
	count;
for (new i = 0; i != sizeof (array); ++i)
{
	dest[i] = array1[i] + array2[i];
}
```

## Combinations

These functions can be quite quickly built up to do complex code.  You could use a `zip` and a `fold` to find the distance between two points.  The normal code for this is:

```pawn
DistanceBetweenPoints(Float:p0[3], Float:p1[3])
{
	// Get the difference in each dimension.
	p0[0] -= p1[0];
	p0[1] -= p1[1];
	p0[2] -= p1[2];
	// Square it.
	p0[0] *= p0[0];
	p0[1] *= p0[1];
	p0[2] *= p0[2];
	// Add them.
	new
		Float:sq = p0[0] + p0[1] + p0[2];
	// Square root.
	return floatsqroot(sq);
}
```

With *y_functional*:

```pawn
DistanceBetweenPoints(Float:p0[3], Float:p1[3])
{
	// Get the difference in each dimension.
	ZipWith({_0 - _1}, p0, p1, p0);
	// Square it.
	Map({_0 * _0}, p0, p0);
	// Add them.
	new
		Float:sq = Sum(p0);
	// Square root.
	return floatsqroot(sq);
}
```

Or combining several steps:

```pawn
DistanceBetweenPoints(Float:p0[3], Float:p1[3])
{
	// Get the difference in each dimension.
	ZipWith({_0 - _1}, p0, p1, p0);
	// Square it and add them.
	new
		Float:sq = FoldL({_0 + _1 * _1}, 0, p0);
	// Square root.
	return floatsqroot(sq);
}
```

## Creating Your Own Functions

You can write a function that takes a lambda in much the same way as a normal function that takes an inline, but sadly you need an extra define to recognise the `{}` syntax (this define gives you `&` syntax too for free):

```pawn
Filter(Func:f<i>, const input[], output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	new len = min(inputSize, outputSize), count = 0;
	for (new i = 0; i != len; ++i)
	{
		if (@.cb(input[i]))
		{
			output[count++] = input[i];
		}
	}
	return count;
}

// `@lambda` is the lambda-making decorator.  If your function returns anything other than `_:` you
// also need to specify this:
//
//   #define Filter(%9) Float:@lambda(0, "i") Filter(%9)
//
// `0` is the index of the parameter that will take a function.  Here it is the first parameter, so
// index 0.  This uses some internal magic to allow you to have the function at up to position 31.
//
// `"i"` is the type of the function to accept (in this case, taking just one parameter).
//
// `%9` is just "the rest of the parameters".  You technically don't need this and can do:
//
//   #define Filter( @lambda(0, "i") Filter(
//
// Although this macro looks recursive, because you replace `Filter(...)` with `Filter(...)` the
// `@lambda` macro does some magic to ensure it isn't (it uses `PP_DEFER`).  But this means the lone
// `(` in the second example is VERY important!
#define Filter(%9) @lambda(0, "i") Filter(%9)
```

You can now call this function as:

```pawn
new arr[] = {6, 7, 1, 5, 7, 2};
new res[sizeof (arr)];
Filter({ _0 > 3 }, arr, res);
```

And it will return `4` directly, and this in `res`:

```
{ 6, 7, 5, 7 }
```

\* I'm not going to go in to the pros and cons of auto-`this`-binding here.

\*\* I'm considering adopting Slice's *md-sort* syntax for array outputs, but haven't yet:

```pawn
Map({ _0 + 1 }, array) -> dest;
```

\*\*\* Because `0` doesn't affect `+` at all you can chain as many of them together as you like with no side-effects.  The same applies to `1` and `*`, making `(0, +)` and `(1, *)` special pairs of value and operator.  These pairs are called "monoids", which is the first important part of the meme definition of "monads" being "a monoid in the category of endofunctors".  So while `(0, +)` and `(1, *)` are monoids in the category of real numbers, a monad is then a pair of operator and value that doesn't change the result, but operating on (certain special types of) functions instead.  You do not need to know any of this!

