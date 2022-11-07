## Prefixes

Prefixes are one of the most important *y_amx* concepts used throughout YSI for very efficient filtering and finding of functions.  For example, the core of y_hooks looks like:

```pawn
#define hook%0(%1) @yH_%0(%1)

while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yH_>)))
{
	// Do something with the found hook.

```

The define adds `@yH_` to the start of every hook function, and the loop then looks for all functions starting with those four bytes.  The *four* part is important because that's the size of a cell, and in pawn `@` first makes the function public, so this prefix serves double duty.  The macros are also optimised for prefixes with `@` and `_` in for better support of the old compiler.  Further, to support 64-bit cells the prefixes are extended as minimally as possible to eight bytes, which requires declaring the functions slightly differently:

```pawn
#define hook%0(%1) _F<@yH_>%0(%1)
```

`_F<>` will either return the prefix exactly, or with padding bytes for larger cell sizes.

`_A<>` converts the input to a number representing those four characters in C string order, which is not the same as pawn packed string order:

```pawn
new prefx = _A<code>;
```

Becomes:

```pawn
new prefix = ('c') | ('o'  << 8) | ('d' << 16) | ('e' << 24);
```

There is also `_C<>` if you want the pawn equivalent:

```pawn
new prefx = _C<code>;
```

Becomes:

```pawn
new prefix = ('c' << 24) | ('o'  << 16) | ('d' << 8) | ('e');
```

