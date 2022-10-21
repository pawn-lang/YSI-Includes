# Annotations

## AKA Decorators

## Problem

Annotations solve multiple long-standing problems, best illustrated below:

```pawn
hook OnPlayerConnect(playerid)
{
}

hook native IsPlayerConnected(playerid)
{
}

TEST__ HasANumber()
{
}

YCMD:givecash(playerid, params[], help)
{
}

timer OneSecond[1000]()
{
}

foreign RemoteFunction();

global RemoteFunction()
{
}

PROFILE__ AlgorithmA()
{
}

PROFILE__ AlgorithmB[5000]()
{
}
```

There are *eight* different ways to declare functions there, all custom, which leads to many many issues:

1. I hope no-one has a variable called `timer` anywhere, which would conflict with the macro.  This was partially solved by adding compatibility mode and `TIMER__`, but...
2. There are multiple ways to do the same thing - `timer` and `TIMER__`, or `Test:` and `TEST__`, declare the same functions.  Some code may mix them, some includes may use one or the other, and that may make the include incompatible with code using different settings.
3. `YCMD:` is a tag.  It looks like a tag, in pawn syntax it *is* a tag, but it is used to declare a special function type, a special function that might have to return, or an untagged return.  That's just misleading and overloading syntax.
4. `timer` has a parameter to configure the declaration itself, which is in square brackets.  Why is it there?  What other code uses *square* brackets for parameters?  `PROFILE__` also has a parameter, but it is optional - by hiding the brackets entirely!?
5. All these different syntaxes require documentation so people know what they do.

Annotations solve almost all of these problems; notably not point two - there are now *three* ways to do some things, or point five - but that's what this file is for.

## Solution

The problems above with constantly adding new syntax boil down to them being ad-hoc (thus inconsistent) and liable to cause conflicts with existing code.  We need a method that allows adding new syntax in a consistent way, without causing conflicts, and gives people an idea of where to look for what they do.  Fortunately this problem has already been solved in other languages in the form of *annotations*.  In Java:

```csharp
class Container
{
	@JsonIgnore()
	public int Var;
}
```

In short, annotations add "meta-data" to a function.  They declare a normal function, but with attached information that can be queried at run-time to do different things.  For example a function could be called automatcially when a player logs in, or have added entry/exit logging.

So we stole the idea for pawn:

```pawn
@hook() OnPlayerConnect(playerid)
{
}

@hook(.native = "IsPlayerConnected") AnyName(playerid)
{
}

@test() HasANumber()
{
}

@ycmd() givecash(playerid, params[], help)
{
}

@timer(1000) OneSecond()
{
}

@foreign() RemoteFunction();

@global() RemoteFunction()
{
}

@profile() AlgorithmA()
{
}

@profile(5000) AlgorithmB()
{
}
```

A few notable differences:

1. You can only have one annotation per function.  Actually, this might not be true, but more become vastly harder due to the underlying macros).
2. They must be on the same line as the function name (again, potentially solvable with macros).
3. If you know C# it uses `[name()]` instead of `@name()`, but we can't replicate that so may as well copy syntax we can.

But they offer some vast improvements over the ad-hoc syntax examples above:

1. They are clearly different to other syntax, so there's no chance of being confused.
2. They use `@` as a prefix to differentiate them from other potential code and reduce conflicts (this is actually valid, but basically unused within SA:MP/open.mp).
3. They look like functions, and follow function syntax.  You can have required parmeters, optional parameters, named parameters, etc and people already know what those mean and how they work.

Hopefully when people see `@name() Func()` they will know it is an annotation.  They might not know what it does yet, but it is a start.

## Examples

### `@test()`

Declare a y_testing test, with or without a player required, and to be run automatcially when `RUN_TESTS` is defined:

```pawn
new gVar = 5;

@test() GreaterThanFive()
{
	ASSERT_GT(gVar, 5);
}
```

Optional named parameters:

* `string:group` - Connect several tests together by name, for improved output and easier test selection.
* `bool:run` - Should the test be run at all?
* `bool:slow` - Is this a slow test, skipped by default?

### `@hook()`

*Hook* another function, to be called at the same time as it:

```pawn
@hook(.fallback = true) OnPlayerDisconnect(playerid, reason)
{
	if (reason == 4)
	{
		printf("Mode ending");
	}
	return 1;
}
```

Optional named parameters:

* `bool:fallback` - Replicate the old `hook` behaviour, rather than the newer `continue()` behaviour.
* `string:native` - Hook a native, not a public.
* `string:function` - Hook a function, not a public.
* `order` - What position in the call chain does this hook appear?  Duplicates are resolved in include order.

### `@timer()`

Declare a function that can be called after a given delay:

```pawn
@timer(5000, .initial = 1000) RepeatMessage(playerid, colour, style, const string:message[])
{
	if (style == -1)
	{
		SendClientMessage(playerid, colour, message);
	}
	else
	{
		GameTextForPlayer(playerid, style, 5000, message);
	}
}
```

Required parameters:

* `delay` - How long between invocations of the timer.

Optional named parameters:

* `initial` - How long before the first call, if it is different to the normal call delay time.
* `repeat` - Number of times to repeat, `0` for default (forever when called with `repeat` and once when called with `defer`).

### `@remote()`

A function maybe called in another script, like `CallRemoteFunction`, but without the need to manage specifier strings, and thus with compile-time checking of parameters.

Call a function in another script:

```pawn
@remote() NonLocalFunction(number, Float:real, const string:message[]);

main()
{
	NonLocalFunction(5, 6.7, "hi");
}
```

Declare a function for another script:


```pawn
@remote() NonLocalFunction(number, Float:real, const string:message[])
{
}
```

No parameters.

### `@init()`

Call a function when the mode starts.  This is similar to `@hook() OnScriptInit()`, but lighter weight.  This is related to the underlying implementation of `final` (which is not yet `@final()`, and maybe never will be):

```pawn
// Run before `OnScriptInit`.
@init() ObjectModule()
{
	CreateObject(1337, 4.0, 5.0, 6.0);
}
```

