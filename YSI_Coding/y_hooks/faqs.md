# FAQ

## What order are different hooks called in?



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

