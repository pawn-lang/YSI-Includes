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

Side-note:  In default pawn there is a function called `settimer`, different to SA:MP/open.mp's `SetTimer`, which only takes a delay time, not a target function.  This can only call a single function, and that function is called `@timer()`.  Here `@` is used in its role as an alternative to `public` (the `@` remains part of the name, so `@timer()` is the same as `public @timer()` and all functions starting with `@` are always `public`).  In open.mp and any other uses of YSI `settimer` is not used, and neither is the `@` prefix for publics (with the notable exception of YSI internals, hence *y_hooks* for example currently using the function name prefix of `@yH_`).  Even if you wanted to write a function called `@timer()` the `@timer` annotation would most likely not conflict because of the double `()()` detected by the declaration `#define @timer(%3)%0(%1)`.

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
// Run during `OnCodeInit`.
@init(.order = init_code) PickupsModule()
{
}

// Run during `OnScriptInit`.
@init() ObjectModule()
{
	CreateObject(1337, 4.0, 5.0, 6.0);
}

// Run during `OnScriptInit`.
@init(init_script) GangZonesModule()
{
}

// Run during `OnGameModeInit`/`OnFilterScriptInit`.
@init(.order = init_mode) TextDrawsModule()
{
}

// Run during `main`.
@init(init_main) CheckpointModule()
{
}
```

### `@exit()`

Call a function when the mode ends.  This is similar to `@hook() OnScriptExit()`, but lighter weight.

```pawn
// Run during `OnGameModeExit`/`OnFilterScriptExit`.
@exit(.order = exit_mode) TextDrawsModule()
{
}

// Run during `OnScriptExit`.
@exit() ObjectModule()
{
}

// Run during `OnScriptExit`.
@exit(exit_script) GangZonesModule()
{
}
```

## Writing Your Own

As an example of writing an annotation we will demonstrate a basic `@task()` equivalent, that is automatcially called at the given interval.  All annotations are actually macros and there is no single way to write one, this is just a simple first step.  The final use will look something like:

```pawn
@task(.interval = 1000) OneSecond()
{
	static seconds = 0;
	++seconds;
	printf("%d seconds", seconds);
}
```

We start with the macro, which almost always has the same pattern.  Bear in mind that `%0` in the code below is the function name, but will probably start with a space.  By convention `%1` is all the parameters to the main function and `%2` is all the annotation configuration:

```pawn
#define @task(%2)%0(%1)
```

To make a timer we need two things - a timer function and a way to call the timer function.  The former is just a public function, the latter is some code that must be run when the mode starts.  There are many ways to get code to run at mode start, but the simplest is actually another annotation - `@init()`.  So we write a function with an `@init()` annotation to start the timer, and a second function with a normal `public` declaration as the code itself.  Note that because of the way `@init()` works we can actually give these two functions the same name, but that isn't always the case.  In short, we want the code above to become:

```pawn
forward OneSecond();

@init() OneSecond()
{
	SetTimer(#OneSecond, 1000, true);
}

public OneSecond()
{
	// Code goes here.
}
```

To use the `.interval` syntax with this structure we can create a helper function that takes all the same parameters as we want to make available to users of the annotation, with all the correct names, and do everything in there instead:

```pawn
@task__(const func__[], interval = 1000, bool:repeat = true, copies = 1)
{
	while (copies--)
	{
		SetTimer(func__, interval, repeat);
	}
}

@init() OneSecond()
{
	@task__(#OneSecond, .interval = 1000);
}
```

Again as a semi convention I'm using `__` suffixes for internal details that end-users shouldn't touch, but which must sadly be visible to them by virtue of how the code is called from anywhere.

We can now put the macro together:

```pawn
#define @task(%2)%0(%1) \
	forward %0(%1);                     \
	@init() %0()                        \
	{                                   \
		@task__(_:__nameof(%0),%2); \
	}                                   \
	public %0(%1)
```

There's two more tiny tricks in the final macro:

* The `_:` seems pointless since the string already has the `_:` tag, but it is another macro in YSI that can detect and remove trailing `,`s.  The annotation options are passed in `(_:#%0,%2)` but if none are given, e.g. `@task()` then `%2` will be empty and the call will be `@task__(#OneSecond,);`, which is invalid code.  The `_:` detects this case and deals with it.

* Using `__nameof(%0)` instead of `#%0`.  In this specific case there's no advantage since everything is generated so we can't get the name wrong, but it is a useful introduction to a new compiler feature (back-ported by YSI and invented by Pawn Plus).  `__nameof` will only convert the parameter to a string if the symbol exists, otherwise it will give an error.  This can be useful in code like `SetTimer`, to ensure that the function really exists and you didn't make a typo: `SetTimer("MyTomer", 1000, false);` - compiles but doesn't work; `SetTimer(#MyTomer, 1000, false);` - same problem; `SetTimer(__nameof(MyTomer), 1000, false);` - compile-time error.

Because `@task__` has three named parameters the annotation does too:

```pawn
@task(.interval = 1000, .copies = 5, .repeat = false) FiveTimes()
{
	printf("This is printed five times");
}
```

Some annotations in YSI use a slightly more complex method for achieving this effect.  I'd like to pretend that some of this is because they're secretly doing more advanced things behind the scenes, but a lot of it is just because I hadn't come up with the helper/`@init()` method yet.

To simplify another aspect of writing a decorator, i.e. analysing the function's parameters, there is now the [y_decorator library](https://github.com/pawn-lang/YSI-Includes/blob/5.x/YSI_Server/y_decorator/quick-start.md) which provides some basic code analysis for you.  For more advanced options you can use [code-parse.inc](https://github.com/Y-Less/code-parse.inc).

