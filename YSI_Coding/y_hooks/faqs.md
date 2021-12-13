# FAQ

## What order are callback hooks called in?

1. Pre-Hooks.  These are a special type of hook used in some libraries to ensure that their callbacks pre-empt even y_hooks.

2. y_hooks.  Normal `hook` hooks.

3. ALS and callback hooks (i.e. `hook callback`).  These are called intertwined with each other, i.e. at the same priority defined only by code order.

4. `public`.  The original callback.

## What order are function hooks called in?

Since there are only two types of function hook, this is much simpler to answer:

1. ALS and function hooks (i.e. `hook function`).  These are called intertwined with each other, i.e. at the same priority defined only by code order in reverse.

2. Original function (i.e. the native or function).

## How many hooks can you have?

The easy answer is "1000 per function", but it usually isn't quite that many.  The reason is complicated and not important if you are nowhere near that limit.

Every time you re-include **y_hooks** (which transitively re-includes **y_unique**) you get a new ID generated.  This can be done 1000 times, but that doesn't always translate to 1000 instances of every callback.  If you include it once and `hook OnPlayerConnect`, you've still "lost" an ID so you can now only `hook OnPlayerDisconnect` 999 times, even though you've not hooked it once yet.  So the best you can do is include **y_hooks** 1000 times and hook every callback each time.  This will give you the maximum possible number of hooked functions.  The worst you can do is include it 1000 times and hook a completely different function every time.

# Errors

## `YSI Fatal Error: Could not write function name in "Hooks_MakePublicPointer".`

This is an unusual corner-case.  It happens when you have a single hook of a long function name, with many replacements, and no `public`:

```pawn
hook OnDynTDUpd()
{
	// Expands to `OnDynamicTextDrawUpdate`.
}
```

The solutions are to either use a longer version of the name, add some dummy hooks, or add the original public:

```pawn
hook OnDynamicTDUpdate()
{
}
```

```pawn
hook OnDynTDUpd()
{
}

hook OnDynTDUpd@0(){}
hook OnDynTDUpd@1(){}
```

```pawn
public OnDynamicTextDrawUpdate()
{
}
```

It technically happens when the full name of the callback is more than 8 characters longer than the shor version.  In that case there is not enough space to write the long version back in te header.  This is only a problem with a single hook - when there are multiple hooks of the same callback, there is 2+ times as much space to write to.  Also, if there is a `public` version of he callback as well, there's no need to write the full name in the header.

## `error 021: symbol already defined: "@yH_OnGamemodeInit@003"`

This applies to any `symbol already defined` error on a hook:

```pawn
hook OnGameModeInit()
{
}
```

Every time you include y_hooks it generates a new unique suffix, this is the number (`003` in the example above) at the end of a hook used to ensure that no two functions have the same name (which is obviously not allowed by the compiler).  The main requirement of this is including y_hooks multiple times.  Generally this means once per source file, but there are some exceptions and addenda:

* The inclusion of y_hooks should always be the last include in the file.  The reason for this is simple - if one of the other files included after y_hooks also includes y_hooks, the unique symbol will get overridden:

Bad:

```pawn
#include <YSI_Coding\y_hooks>
#include "house-system"
#include "race-system"
```

Good:

```pawn
#include "house-system"
#include "race-system"
#include <YSI_Coding\y_hooks>
```

* If you hook the same callback multiple times in one file, you must also include y_hooks multiple times (between the multiple callback copies so the second one gets a new symbol):

Bad:

```pawn
#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
}

hook OnGameModeInit()
{
}
```

Bad:

```pawn
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
}

hook OnGameModeInit()
{
}
```

Good:

```pawn
#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
}

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
}
```

