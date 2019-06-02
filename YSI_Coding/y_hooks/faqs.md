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

# Errors

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

