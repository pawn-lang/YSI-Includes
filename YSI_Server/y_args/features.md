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

## Accepted Argument Forms

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

