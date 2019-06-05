# Features

## Pass Extra Parameters.

There is no reason that `___` is the only given parameter.

```pawn
PrintMore(const str[], ...)
{
	printf(str, 5, 6, ___(1), 7, 8);
}
```

## Skip Parameters.

There's also no reason why all the variable arguments must be passed on.

```pawn
PrintLess(...)
{
	if (numargs() < 5)
	{
		return;
	}
	printf("%d %d %d", ___(2));
}
```

## Reference Parameters.

`___` always passes things on by reference.  This will not work:

```pawn
NormalArg(a, b)
{
	printf("%d", ___(0));
}
```

But because both `...` and `&` are pass-by-reference, this will work:

```pawn
RefArg(&a, &b)
{
	printf("%d", ___(0));
}
```

## `va_args<>` and `va_start<>`

For backwards-compatibility with older versions of y_va (designed to look like C vararg functions), these are aliases for `...` and `___`:

```pawn
SendFormattedMessage1(playerid, colour, const msg[], ...)
{
	new str[128]
	format(str, sizeof (str), msg, ___(3));
}

SendFormattedMessage2(playerid, colour, const msg[], va_args<>)
{
	new str[128]
	va_format(str, sizeof (str), msg, va_start<3>);
}

```

Those two pieces of code are entirely equivalent - `va_format` is also a alias to `format` for compatibility reasons; with one exception...

## `GLOBAL_TAG_TYPES`

Technically, `va_args<>` is not `...`, but `GLOBAL_TAG_TYPES:...`.  The difference being that the latter accepts many tags, not just one.  The common way of writing this is `{Float, _}:...`, but this only accepts two tags - `Float` and `_` (integer, no tag).  `GLOBAL_TAG_TYPES` is defined as `{_,Language,Bit,Text,Menu,Style,XML,Bintree,Group,Timer,File,Float,Text3D,CUSTOM_TAG_TYPES}`, i.e. a lot of common tags.

## `CUSTOM_TAG_TYPES`

If you want to add more accepted tags to functions - especially internal YSI functions, simply define them in `CUSTOM_TAG_TYPES`:

```pawn
#define CUSTOM_TAG_TYPES Int,Hex
#include <YSI_Coding\y_va>
```

Make sure the define is before any YSI library.

