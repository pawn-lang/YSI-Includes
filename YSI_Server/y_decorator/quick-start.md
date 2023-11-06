## Introduction

This library makes one aspect of writing ["decorators" (aka "annotations")](https://github.com/pawn-lang/YSI-Includes/blob/5.x/annotations.md) simpler.  This gives compile-time analysis of function parameter types and provides them to your decorator automatically.  For more advanced analysis you should use [code-parse.inc](https://github.com/Y-Less/code-parse.inc), which this library uses underneath.

### Example 1

To write an `@example()` decorator that just lists all the functions with this decorator on server start, plus their parameter types.

First we define our `@example` decorator as an alias for `@decorator__(DECORATOR_EXAMPLE)`:

```pawn
#define @example @decorator__(DECORATOR_EXAMPLE)
```

`DECORATOR_EXAMPLE` is where we will actually do our code generation once the code analysis completes.  The parameters given to `DECORATOR_EXAMPLE` are:

* `%0` - Anything given to `@example(params)` directly (i.e. the decorator's parameters).
* `%1` - The function's return tag (including `:`).
* `%2` - The function name.
* `%3` - The function's parameters.
* `%4` - The specifier, i.e. the `"sif"`-like string you'd need to call this function with `CallRemoteFunction`.
* `%5` - The function parameters again, but stripped of syntax; for calling the function.
* `%8` - Internal details.  Make sure you keep this!

A call of:

```pawn
@example(4, 6) MyFunc(Float:f, const string:s[], d)
```

Becomes:

```pawn
DECORATOR_EXAMPLE:%8$(4, 6)(MyFunc)(Float:f, const string:s[], d)(fsi)(f, s, d)
```

These are the most common data needed for writing custom decorators.  If you need to do some more custom tag-based processing of things you can do it safely before `%8$`:

```pawn
#define DECORATOR_EXAMPLE:%8$(%0)(%1)(%2)(%3)(%4)(%5) EXAMPLE_NO_PARAMS:EXAMPLE_W_PARAMS:%8$(%0)(%1)(%2)(%3)(%4)(%5)
#define EXAMPLE_NO_PARAMS:%8$()(%1)(%2)(%3)(%4)(%5) %8$ /* whatever - don't forget `%8$`! */
#define EXAMPLE_W_PARAMS:%8$(%0)(%1)(%2)(%3)(%4)(%5) %8$ /* whatever - don't forget `%8$`! */
```

Now we need to actually do something with all this data.  To run some code at server start we invoke another decorator (`@init`), which is perfectly safe.  Remember to always start the output with `%8$`, just for implementation reasons (see the code-parse.inc documentation for reasons why):

```pawn
#define DECORATOR_EXAMPLE:%8$(%0)(%1)(%2)(%3)(%4)(%5) %8$@init %2() printf("Function %s, with parameters %s, decorated", __nameof(%2), #%4); %1%2(%3)
```

### Example 2

We can make a function called remotely with:

```pawn
#define @remote @decorator__(DECORATOR_REMOTE)

#define DECORATOR_REMOTE:%8$(%0)(%1)(%2)(%3)(%4)(%5) %8$forward @@%2(%3); %1%2(%3) CallRemoteFunction(__nameof(@@%2), _:#%4, %5); public @@%2(%3)
```

Used as:

```pawn
@remote() Func(a, const string:b[])
{
}

main()
{
	Func(5, "hi");
}
```

`@@` can be used as a prefix for public functions that will consume excess space to make valid symbols.  `_:#%4,` is a trick to remove the trailing comma in the case of no parameters.  `__nameof` is not really needed here since we are generating the code automatically, but unlike `#@@%1` to convert the function name in to a string, `__nameof` will give an error if the function being stringised doesn't exist.

