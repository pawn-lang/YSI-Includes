# Converting 4.x -> 5.x

## End-Users

y_inline changed significantly for YSI 5.x.  Most old code still works, but will throw up many many warnings.  The simple reason for this is that the new code is well typed.  If a function expects an inline function (or any type of function pointer) the old code would accept anything - any pointer would do.  The new code adds specifiers, so for example `Dialog_ShowCallback` expects a function pointer with the shape `<iiiis>` (i.e. the parameter types for `OnDialogResponse`).  Before, this code would compile with no problem:

```pawn
inline Response(string:input[])
{
	printf("You typed: %s", input);
}
Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_MSGBOX, "Input", "Type something:", "OK", "Cancel");
```

This is clearly wrong, and would probably crash at run-time for no apparent reason.  This is the sort of thing that the compiler should warn you about, and now it does!  That code above will now generate the following warning:

``warning 213: tag mismatch: expected tag "F@_@iiiis", but found "F@_@s"``

If you are on an older compiler, the warning is just `warning 213: tag mismatch`, but the newer warnings give you much more information.  Ignoring the `F@_@` part, which is an implementation detail, the warning clearly states that it expected `iiiis` but got `s` - the function parameters are wrong.

If you are using a library that provides functions that expect inlines, and you are already passing the correct types, you should not need to update anything at all - the old code is correct.

### Breaking Changes

There are (AFAIK) only two breaking changes, and they are both in quite obscure syntax that it wasn't possible (or desirable) to keep:

* If you used plain strings as:

```pawn
MyFunc(callback_tag:"func");
```

This has been entirely removed and must be:

```pawn
MyFunc(using func);
```

Note the lack of `inline` or `callback`.  This was the syntax for plain string searches, but plain strings were also possible.  Now they are not.

* If you used an inline that was not in scope as:

```pawn
{
	inline Func() {}
}
{
	Other(using Func);
}
```

You now can't do that - it won't work.  The old code was not fully aware of scopes and would attempt to find the nearest potential function.  The new code is fully scope aware and will correctly deal with it.

## Library Writers

While end-user inline code hasn't changed at all (which is a good thing), supporting the new tagged specifiers required major changes to how inlines are used.  As well as tags, there are other changes, but fortunately these make using inlines much simpler.  Again, legacy code (except that using y_inline internal details) will still work, but with a lot of warnings - mostly tag mismatches and deprecation warnings.

### Tags

Previously a function that recieved a function pointer looked like:

```pawn
Func(callback:cb)
{
	// Other code.
}
```

This should now be `Func:cb<specifier>`:

```pawn
Func(Func:cb<isf>)
{
	// Other code.
}
```

The full list of specifiers is:

| Specifier | Description                                               |
| --------- | --------------------------------------------------------- |
| a         | Array (must have the size specified in the inline)        |
| s         | String                                                    |
| i, d      | Integer (decimal)                                         |
| c         | Character                                                 |
| f         | Float                                                     |
| r         | Reference                                                 |
| t         | Tagged varaible                                           |
| x         | Varargs (can't be used currently, and ends the specifier) |

### `Callback_Get`

Previously, the second thing you did, in the first function passed an inline, was resolve that and store the closure, using some nasty code that involved internal arrays:

```pawn
Func(callback:cb)
{
	new resolved[E_CALLBACK_DATA];
	Callback_Get(cb, resolved);
	// Other code.
}
```

This is now just gone - `cb` IS the resolved call, complete with closure data (if you are interested, the closure resolution is now done by the `using inline` expression):

```pawn
Func(Func:cb<isf>)
{
	// Other code.
}
```

### `Callback_Release`

This cleaned up from `Callback_Get`, if we don't have the former, we don't need the latter:

```pawn
Func(callback:cb)
{
	new resolved[E_CALLBACK_DATA];
	Callback_Get(cb, resolved);
	// Other code.
	Callback_Release(resolved);
}
```

Becomes:

```pawn
Func(Func:cb<isf>)
{
	// Other code.
}
```

### `Callback_Call`

The actual calling of a function has now been passed off to [indirection.inc](https://github.com/Y-Less/indirection) (see that repository for more documentation).  This means `Callback_Call` has been replaced with the indirection operator `@`:

```pawn
Func(callback:cb)
{
	new resolved[E_CALLBACK_DATA];
	Callback_Get(cb, resolved);
	Callback_Call(resolved, 42, "Hello World", 9.9);
	Callback_Release(resolved);
}
```

Becomes:

```pawn
Func(Func:cb<isf>)
{
	@.cb(42, "Hello World", 9.9);
}
```

The indirection operator handles far more than y_inline - it can take raw function pointers, string function names, and custom indirection handlers.  y_inline is implemented as the latter, and you can write your own too, all with a common syntax.

### Claim/Release Exception.

We just removed `Callback_Get` and `Callback_Release`, but there is one case where they are still needed - when you will call the inline in the future (i.e. after the current function ends).  This is most likely caused by it being called in a callback or timer:

```pawn
forward Timer(resolved[E_CALLBACK_DATA], size, num);

public Timer(resolved[E_CALLBACK_DATA], size, num)
{
	Callback_Call(resolved, num, "Hello World", 9.9);
	Callback_Release(resolved);
}

Func(callback:cb)
{
	new resolved[E_CALLBACK_DATA];
	Callback_Get(cb, resolved);
	SetTimerEx("Timer", 1000, false, "aii", resolved, _:E_CALLBACK_DATA, 42);
}
```

However, because this is now a feature of indirection.inc, the function names have changed:

```pawn
forward Timer(Func:cb<isf>, num);

public Timer(Func:cb<isf>, num)
{
	@.cb(num, "Hello World", 9.9);
	Indirect_Release(cb);
}

Func(Func:cb<isf>)
{
	Indirect_Claim(cb);
	SetTimerEx("Timer", 1000, false, "ii", _:cb, 42);
}
```

You do need to pass the pointer as `_:cb`, but this is a limitation of `SetTimerEx` not accepting all tags, not a problem with y_inline/indirection.inc themselves - functions with proper tags (for example y_timers timers) would not need this workaround.

This shows another important feature of the new syntax - function pointers are just plain integers.  They can be stored and manipulated exactly like normal numbers (don't try adding/multiplying/etc. them, but you can store/copy them).

### Scope

Previously, this could be done:

```pawn
Container()
{
	{
		inline Func() {}
	}
	{
		Other(using Func);
	}
}
```

That would trigger `Callback_Get` to search for the inline by name instead of by direct reference.  The `using` syntax to pass by name still works, but this example will no longer work because `Func` is not in scope at the time of the call to `Other`.  `Callback_Get` is deprecated, but `Callback_Find` has not changed - it still searches for an inline by name, but will also not find this callback.  However it WILL find inlines further up the call stack:

```pawn
Outer()
{
	inline Func() {}
	Container();
}

Container()
{
	Other(using Func);
}
```

This WILL work, because `Func` is technically in scope when dealing with the whole call stack.  This highlights a second important change - inlines are no longer restricted to the immediate parent of the function that calls `Callback_Get`.

# Issues

## ``warning 234: function is deprecated (symbol "CallStoredFunction") Use `@.func(params);`.``

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

## ``warning 234: function is deprecated (symbol "Callback_Call") Use `@.func(params);`.``

Old code:

```pawn
Callback_Call(f, 42, 43, "Hello World");
```

New code:

```pawn
@.f(42, 43, "Hello World");
```

## ``warning 234: function is deprecated (symbol "Callback_Array") Use `Indirect_Array(_:func, tagof (func), params);`.``

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

## ``warning 234: function is deprecated (symbol "Callback_Get_") Remove or use `Indirect_Claim(func);`.``

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

## ``warning 234: function is deprecated (symbol "Callback_Release") Remove or use `Indirect_Release(func);`.``

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

## ``warning 213: tag mismatch: expected tag none ("_"), but found "F@_@<something>"``

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

## ``warning 213: tag mismatch: expected tag "F@_@", but found "F@_@<something>"``

There are two possible causes to this:

1. Wrong function type:

`Dialog_ShowCallback` takes a callback, this callback expects five parameters:

```pawn
inline Response(playerid, dialogid, response, listitem, string:inputtext[])
{
}
Dialog_ShowCallback(pid, using inline Response, ...);
```

That code is correct.  The following code is not:

```pawn
inline Response(playerid, dialogid, string:inputtext[])
{
}
Dialog_ShowCallback(pid, using inline Response, ...);
```

Here, `Response` is missing two parameters.  This will trigger the warning ``warning 213: tag mismatch: expected tag "F@_@iiiis", but found "F@_@iis"``  The warning itself gives you some information - `iis` are the parameters that exist (number, number, string), `iiiis` are the ones that are expected.  So you're missing two.  The warning might also be the opposite, so you're missing some, even just `F@_@`, which means no parameters given/wanted.

2. Legacy code:

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

