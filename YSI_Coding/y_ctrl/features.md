## `@lctrl` decorator

Declare a function to be called when a custom `LCTRL n` register is read:

```pawn
@lctrl(500) Handler(pri, alt)
{
	return 42;
}
```

The decorator parameter must be a bare number.  The function name doesn't matter.  The values of
`pri` and `alt` are the values of those registers when `LCTRL` is invoked.  This function must
return a value, which is set to `pri`.

## `@sctrl` decorator

Declare a function to be called when a custom `SCTRL n` register is read:

```pawn
@sctrl(500) Handler(pri, alt)
{
	printf("sctrl 500 called");
}
```

The decorator parameter must be a bare number.  The function name doesn't matter.  The values of
`pri` and `alt` are the values of those registers when `SCTRL` is invoked.

## Call Handlers

Calling the handlers is done via `LCTRL` and `SCTRL` in assembly:

```pawn
#emit SCTRL            500
#emit LCTRL            500
```

## Not Clobbering

If you want to not clobber `pri` and `alt` in the handlers this must be done manually:

```pawn
@lctrl(500) Handler(pri, const alt)
{
	{
	}
	#emit LOAD.S.alt alt
	return 42;
}

@sctrl(500) Handler(const pri, const alt)
{
	{
		printf("sctrl 500 called");
	}
	#emit LOAD.S.pri pri
	#emit LOAD.S.alt alt
}
```

The weird braces are so that cleanup code doesn't also clobber `alt` (all locals must be within
those braces if you don't want to do more work).  `lctrl` shouldn't restore `pri` as that holds the
return value afterwards.  Note that `pri` and `alt` are actually always `const`, the specifier isn't
needed.

