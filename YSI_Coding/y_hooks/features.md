# Features

## Chain Order

Think of hooks as sitting between your code and the server:

```
SERVER
HOOK 1
HOOK 2
CODE
```

A callback comes from the server, through the hooks, in to your code.  Thus the earliest hooks are called first (the ones declared first in source code).

A function call goes from your code, through the hooks, in to the server.  Thus the latest hooks are called first (the ones declared last in source code).

Of course, with explicit chaining you can slightly control WHEN things are called, but not do anything about hooks that were called before the current hook.

## Original Hooks

### Use A Callback Multiple Times

```pawn
#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "   Welcome");
}

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "to my server!");
}
```

### States

```pawn
#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) <current_city : current_city_lv>
{
	SendClientMessage(playerid, COLOUR_GREETING, "Welcome to Las Venturas!");
}

hook OnPlayerConnect(playerid) <current_city : current_city_ls>
{
	SendClientMessage(playerid, COLOUR_GREETING, "Welcome to Los Santos!");
}
```

### Custom Default Returns

The default return from a callback is normally `1`.  You can change this with `DEFINE_HOOK_RETURN__`.  Note that this macro goes OUTSIDE all functions.

```pawn
DEFINE_HOOK_RETURN__(OnMyCustomEvent, 0);

main()
{
}
```

The existing non-standard returns are:

```pawn
DEFINE_HOOK_RETURN__(OnPlayerCommandText, 0);
DEFINE_HOOK_RETURN__(OnRconCommand, 0);
```

### Short Form Names

Sometimes a hooked function name becomes too long and gives a warning.  In that case you can replace some of the words with shorter version.

```pawn
DEFINE_HOOK_REPLACEMENT__(Inventory, Inv);

hook OnPlayerInvOpened(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "OnPlayerInventoryOpened");
}
```

Note that this replacement is CamelCase-aware.  The above replacement will NOT match the following callback:

```pawn
hook OnPlayerInvolvedInFight(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "to my server!");
}
```

The `Inv` here will not be expanded to `Inventory`, because it isn't followed by a capital letter or the end of the function name.

The pre-defined short forms replacements are:

```pawn
DEFINE_HOOK_REPLACEMENT__(Checkpoint, CP );
DEFINE_HOOK_REPLACEMENT__(Container , Cnt);
DEFINE_HOOK_REPLACEMENT__(Inventory , Inv);
DEFINE_HOOK_REPLACEMENT__(Dynamic   , Dyn);
DEFINE_HOOK_REPLACEMENT__(TextDraw  , TD );
DEFINE_HOOK_REPLACEMENT__(Update    , Upd);
DEFINE_HOOK_REPLACEMENT__(Object    , Obj);
DEFINE_HOOK_REPLACEMENT__(Command   , Cmd);
DEFINE_HOOK_REPLACEMENT__(DynamicCP , DynamicCP);
```

That last one isn't pointless, it tricks the system in to NOT replacing the `CP` there with `Checkpoint` from the earlier defined replacement.  This is because `DynamicCP` is the correct full name in the streamer plugin.

### Return Values

While none of the examples above had returns, this was merely a simplification for those examples.  As with normal callbacks, hooks can return either `0` or `1`.  The exact meaning of the return depends on the callback in question.  For most callbacks the default return is 1, for `OnPlayerCommandText` and other text callbacks it is `0`.  The final value returned from an overall callback is the return from the final hook or public in the chain.

This can, however, be overridden.  If a hook returns `~0` or `~1` instead, the chain is instantly ended and the corresponding value returned with no further hooks being called.  So `~0` is "halt processing and return 0 immediately", `~1` is "halt processing and return 1 immediately".  There are also very long macro names for these returns, but they are hard to remember, hard to type, and so now pointless (they used to be useful, until it was realised that `~0` and `~1` were far clearer).

## Function Hooks

### Recursive Calls

DO NOT call the original function directly or you will get stuck in a loop:

```pawn
#include <YSI_Coding\y_hooks>

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	return SetPlayerPos(playerid, x, y, z + 0.1);
}
```

Here the hook will be called from within itself, only `continue` bypasses the recursive call.

### Explicit Chaining

Because the next function in the chain is called via `continue`, you can decide exactly when (and if) it will happen:

```pawn
#include <YSI_Coding\y_hooks>

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	if (0.0 <= z < 100.0)
	{
		return SetPlayerPos(playerid, x, y, z);
	}
	else
	{
		return 0;
	}
}
```

This is far more flexible than the original method, which gave very little control over ordering, and is far more akin to ALS hooks.

### Any Return Values

Original hooks can only return 0 or 1.  These hooks have the full range of any return value.  Returning strings is currently not possible because of the return type of `continue`, but that's being considered.

### Pre- and Post-Processing

Also a result of the explicit chaining, hooks can utilise the results of further calls:

```pawn
hook function random(max)
{
	new ret;
	if (max < 0)
	{
		ret = -continue(-max * 10);
	}
	else
	{
		ret = continue(max * 10);
	}
	return ret / 10;
}
```

Also, as shown there, call the original potentially many times.

### Abstract `continue`

`continue` doesn't need to be called from within the hook directly, it can be in another function and will still work.  It will even call a different function based on the current hook executing.

```pawn
ZeroParamContinue()
{
	return continue();
}

hook function numargs()
{
	// Note that a `numargs` hook will not work in practice - it returns the
	// number of parameters passed to the function that called it, but a hook
	// changes that source.
	return ZeroParamContinue();
}

hook function heapspace()
{
	return ZeroParamContinue();
}
```

### Use With `y_va`

```pawn
hook function printf(const str[], GLOBAL_TAG_TYPES:...)
{
	// Not `printf` - we don't want a recursive call.
	print("The string is:");
	print(str);
	return continue(str, ___(1));
}

Also, variable arguments.

## Callback Hooks

### The Original Need Not Exist

The only difference between `hook callback` and `hook function` (aside from the reversed call order) is that `hook function` confirms that the function being hooked really exists, while `hook callback` doesn't.  `hook function MyFunc()` will give an error if `MyFunc()` doesn't exist, `hook callback OnPlayerSpawn(playerid)` won't if there's no `public OnPlayerSpawn(playerid)`.

