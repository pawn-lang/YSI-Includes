# Errors

## `warning 234: function is deprecated (symbol "CallStoredFunction") Use \`@.func(params);\`.`

Old code:

```pawn
new Function:f = GetLocalFunction("Function", "iis");

CallStoredFunction(f, 42, 43, "Hello World");
```

New code:

```pawn
new Func:f<iis> = GetLocalFunction(&Function<iis>);

@.f(42, 43, "Hello World");
```

## `warning 234: function is deprecated (symbol "Callback_Call") Use \`@.func(params);\`.`

Old code:

```pawn
Callback_Call(f, 42, 43, "Hello World");
```

New code:

```pawn
@.f(42, 43, "Hello World");
```

## `warning 234: function is deprecated (symbol "Callback_Array") Use \`Indirect_Array(_:func, tagof (func), params);\`.`

This is not quite as simple - there's no neat `@` wrapper for when you want to give the parameters all in a single array instead of as multiple real parameters.  But there is still a way:

```pawn
Callback_Array(f, args);
```

New code:

```pawn
Indirect_Array(f, tagof (f), args);
```

Note that with `y_va` and closures this is likely rarely needed:

```pawn
@.f(___(0));
```

## `warning 234: function is deprecated (symbol "Callback_Get_") Remove or use \`Indirect_Claim(func);\`.`

Old code:

```pawn
Callee(callback:c)
{
	ret[E_CALLBACK_DATA]
	Callback_Get(c, ret);
	Callback_Call(ret);
	Callback_Release(ret);
}
```

New code:  The whole resolving system has been removed, there's now no need to call `Callback_Get` at all:

```pawn
Callee(Func:c<>)
{
	@.c();
}
```

The exception being if you are storing the function for use in the future:

```pawn
new Func:g_c<>;
Callee(Func:c<>)
{
	Indirect_Claim(c);
	g_c = c;
}
```

This isn't quite the same, but performs the same job in some cases.

## `warning 234: function is deprecated (symbol "Callback_Release") Remove or use \`Indirect_Release(func);\`.`

Old code:

```pawn
Callee(callback:c)
{
	ret[E_CALLBACK_DATA]
	Callback_Get(c, ret);
	Callback_Call(ret);
	Callback_Release(ret);
}
```

New code:  As with `Callback_Get`, if you aren't storing the pointer for use in the future, there's no code required:

```pawn
Callee(Func:c<>)
{
	@.c();
}
```

And if you do, once you're done with it, release it with:

```pawn
Indirect_Release(g_c);
```

## `warning 213: tag mismatch: expected tag none ("_"), but found "F@_@<something>"`

This usually happens when you pass a function pointer to a normal function (such as as an optional parameter to `SetTimerEx`):

To fix, simply add a tag override:

```pawn
Caller(Func:callback<ii>)
{
	SetTimerEx("PublicWithInline", 1000, 0, "iii", _:callback, 42, 43);
}
```

Bear in mind that even in this case, the called public functions can have tags on their parameters - the specifier and function have no interaction:

```pawn
forward PublicWithInline(Func:callback<ii>, a, b);

public PublicWithInline(Func:callback<ii>, a, b)
{
	@.callback(a, b);
}
```

It is also worth noting that "y_timers" and "y_remote" do not have this problem.  Both provide type-safe (tag-safe) wrappers for `SetTimerEx`, `CallLocalFunction`, and `CallRemoteFunction`:

```pawn
timer PublicWithInline[1000](Func:callback<ii>, a, b)
{
	@.callback(a, b);
}

Caller(Func:callback<ii>)
{
	defer PublicWithInline(callback, 42, 43);
}
```

## `warning 213: tag mismatch: expected tag "F@_@", but found "F@_@<something>"`

This indicates that you are passing an inline to an old-style function, one such as:

```pawn
MyFunction(callback:c)
{
}
```

The function signature needs updating to indicate the parameters the passed inline is expected to have:

```pawn
MyFunction(Func:c<iiai>)
{
}
```

