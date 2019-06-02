# Quick Start

There are three types of hooks: original, callback, and function.

## Original

Originals are still the fastest (faster even than a normal function call) and simplest, but can only hook publics:

```pawn
#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Welcome!");
}
```

The system will call each hook of a public in the order they are declared.  When one ends the next starts.  There is a way to stop the chain entirely, such that no more hooks are called, but this is all the control given.  These can hook callbacks that don't even exist, you don't need `public OnPlayerConnect` anywhere in code for this example to work.

## Function

A function hook hooks a function - i.e. something called within the script.  This includes pawn functions and natives:

```pawn
#include <YSI_Coding\y_hooks>

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	return continue(playerid, x, y, z + 0.1);
}
```

Every time `SetPlayerPos` is used in the script, this hook will be called first.  `continue` is an explicit call to the next function in the chain - this may be another hook or the original code (a native in this case).

## Callback

A callback hook combines the hooking of callbacks from original hooks with the explicit chaining of function hooks:

```pawn
#include <YSI_Coding\y_hooks>

hook callback OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Welcome!");
	return continue(playerid);
}
```

Note that I haven't ACTUALLY written these yet.

