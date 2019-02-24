# Features

## Use A Callback Multiple Times

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

## States

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

## Custom Default Returns

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

## Short Form Names

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

## Return Values

While none of the examples above had returns, this was merely a simplification for those examples.  As with normal callbacks, hooks can return either `0` or `1`.  The exact meaning of the return depends on the callback in question.  For most callbacks the default return is 1, for `OnPlayerCommandText` and other text callbacks it is `0`.  The final value returned from an overall callback is the return from the final hook or public in the chain.

This can, however, be overridden.  If a hook returns `~0` or `~1` instead, the chain is instantly ended and the corresponding value returned with no further hooks being called.  So `~0` is "halt processing and return 0 immediately", `~1` is "halt processing and return 1 immediately".  There are also very long macro names for these returns, but they are hard to remember, hard to type, and so now pointless (they used to be useful, until it was realised that `~0` and `~1` were far clearer).

