# Internal Details.

## `PREINIT__`/`POSTINIT__` Implementation.


## `FINAL__` Implementation.

Thanks to `PREINIT__`, this is actually incredibly simple:

```pawn
#define FINAL__%0=%1; stock const %0;PREINIT__%0(){ScriptInit_ForceFinal_(_:%0,_:(%1));}

stock ScriptInit_ForceFinal_(const &var, const val)
{
	#emit LOAD.S.pri val
	#emit SREF.S.pri var
}
```

The variable is defined as `stock const`, not just `const`.  This is an important difference as it means it is actually allocated memory, whereas `const` is replaced at compile-time.  Were there no memory, the value could not be forcibly replaced at run-time, but the use of `const` means that any normal attempt to change the value is a compile-time error.  This would not work:

```pawn
stock ScriptInit_ForceFinal_(...)
{
	setarg(0, 0, getarg(1, 0));
}
```

Because passing a `const`, even a `stock const` to a varargs function will actually allocate heap space and copy the value.  This makes this a very rare case where `const &` is required and thus the new warning I explicitly asked for must be disabled:

```pawn
#pragma warning disable 238
```

Very simple assembly is used to write to the `const` without the compiler noticing, but `setarg` could also be used:

```pawn
#pragma unused var
setarg(0, 0, val);
```

