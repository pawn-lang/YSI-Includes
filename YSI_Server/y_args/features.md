# Features

## Getting Argument Values

### Bools

Boolean arguments can be parameterless, which defaults to `true`, or provide an argument.  The return value is *not* the argument value, but whether the argument was passed:

```pawn
new bool:help;
// Look for `-h` or `--help` (or `/h` or `/help`).
if (Arg_GetBool('h', "help", help))
{
	// The argument was given.
	if (help)
	{
		// The argument is true.
		printf("Your mode help goes here");
	}
}
```

The first argument (`'h'`) is the short-form argument name (i.e. `-h`).  The second argument is the long-form name (i.e. `--help`).  Either may be omitted by passing `_`.

Examples:

```
-h --yes=1 /param false -ctl -l+
```

### Integers And Floats

These arguments must provide a value:

```pawn
new i;
// Look for `-i` or `/i`.
if (Arg_GetInt('i', _, i))
{
	// The argument was given.
	printf("-i = %d", i);
}

new Float:f;
// Look for `--float` or `/float`.
if (Arg_GetBool(_, "float", f))
{
	// The argument was given.
	printf("--float = %.2f", f);
}
```

Examples:

```
-i=7 -j:9 --money 42 /count 3 --float 6.6
```

If the same argument is given multiple times, only the last one is returned:

```
-i=7 -i=9
```

Will return `i = 9`, except for when retrieving arrays.

### Strings

String arguments may be enclosed in quotes on the command line to include spaces.

```pawn
new name[32];
// Look for `/owner`.
if (Arg_GetString(_, "owner", name))
{
	// The argument was given.
	printf("The owner is \"%s\"", name);
}
```

Examples:

```
--owner "your name here" -s=bob "--favourite-arg=--help or --count"
```

### Arrays

All the previous types of arguments may also be retrieved as an array.  In these cases the return value is the number of elements *passed* - if the given array size is insufficient to hold all the values this return value will be larger than the array size, to indicate that values were skipped.  If there are no matching arguments the return value is `0`.  Arrays can be passed as arguments either via a comma-separated list, or as multiple arguments with the same name.  String arrays *must* be the latter, and thus the strings may contain commas.

```pawn
// Explicit array size passed.
new bool:boolArray[6];
new boolCount = Arg_GetBoolArray('b', "bools", boolArray, sizeof (boolArray));

// Default argument (`sizeof (array)`) explicitly used.
new intArray[10];
new intCount = Arg_GetIntArray('i', "ints", intArray, _);

// Default argument (`sizeof (array)`) implicitly used.
new floatArray[10];
new floatCount = Arg_GetFloatArray('f', "floats", floatArray);

// Second default argument (`sizeof (array[])`) implicitly used.
new stringArray[10][32];
new stringCount = Arg_GetStringArray('s', "strings", stringArray, 5);
```

Examples:

```
-b=true -b- /b+ --bools true --bools 0 /bools
```

```
--ints=6,7,8,9,10
```

```
-f=6.6 -f=7.7 -f=8.8 -f=9.9
```

```
"-s=Hello world!" "/s:This may contain `,`s" --strings "...see?"
```

## Meta-data

* `Args_UniqueCount()` returns the number of *unique* arguments passed to the script.  So `-o -o -o` will return `1`.  *rest* and positional arguments both count.
* `Args_TrueCount()` returns the number any arguments passed to the script.  So `-o -o -o` will return `3`.  *rest* and positional arguments both count.  `-ab` will return `2`.
* `Args_PositionalCount()` returns the number of positional arguments passed.
* `bool:Args_HasRest()` Was there ` -- `?
* `bool:Args_GetRest(output[], size = sizeof (output))` returns the *rest* data (everything after ` -- `).
* `bool:Args_GetPositionalBool(index, &bool:output)` tries to get an boolean from the given positional argument index.
* `bool:Args_GetPositionalInt(index, &output)` tries to get an integer from the given positional argument index.
* `bool:Args_GetPositionalFloat(index, &Float:output)` tries to get an float from the given positional argument index.
* `bool:Args_GetPositionalString(index, output[], size = sizeof (output))` tries to get a string from the given positional argument index.

## Accepted Argument Forms

### Positional arguments

These are arguments that are only data - no name.  For example simply:

```
Hello
```

Would be a string positional argument at positional index 0.

What is and isn't a positional argument can be a little tricky to determine.  `--` arguments may have a parameter, so anything after them is assumed to be their parameter:

```
--help start
```

Here `start` is *not* a positional argument because it can be attributed to `--help`.

```
--help= start
```

Here `start` *is* a positional argument because `--help` has an explicit empty parameter via `=`.

Any non-argument after a short-form argument is always positional:

```
-a we are always positional
```

Because short-form arguments don't have parameters separated by spaces (unless you wrap the whole thing in quotes, but that's not an ambiguous situation).

And if there is only one datum passed, or the first datum has no `-` or `/` it must be positional:

```
first
```

Note that while this:

```
--help start
```

Assumes that `start` is a parameter to `--help`, this:

```
--help --start
```

Assumes that `--help` and `--start` are separate arguments, because `-` and `/` override parameters (see below for how to have a parameter with those special characters in).

### Collated short-form.

```
-akgd
```

Is equivalent to:

```
-a -k -g -d
```

### Implicit `true`/`false`.

```
-y
```

Is equivalent to:

```
-y=true
```

Or:

```
-y=1
```

### pawncc style `-`/`+`.

```
-x+
```

Is equivalent to:

```
-x=true
```

```
-x-
```

Is equivalent to:

```
-x=false
```

(Useful when the default is `true`, but can be ommitted entirely when the default is `false`).

### pawncc style `:`.

As well as `=`, short-form arguments can be separated from their parameter with `:`:

```
-z:7
```

### windows style '/'.

As well as `-`, arguments can be started with `/`.  However, this has very different semantics to `-`.  Because there is no `--` equivalent the argument name is never collated, so this:

```
/k
```

Is equivalent to:

```
-k
```

However, this:

```
/klm
```

Is equivalent to:

```
--klm
```

And *not*:

```
-k -l -m
```

### Long- and short-form pairs.

```
-h
```

Can be configured to be the same as:

```
--help
```

### Long-form separated arguments.

Long-form arguments can be separated from their parameters by a space:

```
--players 7
```

### Double-quotes enclosing long parameters

```
--motd "Hello and welcome to my server!"
```

### Only use the last argument.

```
-c=7 -c=6 -c=9
```

Will just return `-c` = `9`.

Unless...

### Array parameters.

If configured as an array, this:

```
-c=7 -c=6 -c=9
```

Will return `-c` = `{7, 6, 9}`.

### Comma-separation of arrays.

If configured as an array, this:

```
-c=7,6,9
```

Will, as above, return `-c` = `{7, 6, 9}`.

### Rest

A `--` parameter with no name separates the initial parameters from the *rest* parameters.  The *rest* parameters are always returned as a single large string:

```
--foo --bar -- Hello world!
```

Will have "Hello world!" as a single parameter.  Absolutely everything after the lone `--` is this parameter, it can't be ended again.

### Parameters starting with `-`.

If you want a parameter to start with `-` (or `/`), which are usually used to denote a new argument, they MUST be separated by `=` or `:`, not a space:

```
-e=--i
```

For almost exclusively this corner-case (it is not usually recommended) the entire argument and parameter may be enclosed in double quotes or use `=`:

```
--decrement=--i
```

```
"--decrement --i with space"
```

