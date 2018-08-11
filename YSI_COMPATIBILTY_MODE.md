# YSI_COMPATIBILITY_MODE

This is a special build mode, enabled with the `YSI_COMPATIBILITY_MODE` flag:

```pawn
// At the VERY top of your script.
#define YSI_COMPATIBILITY_MODE

// All other includes and defines below.
```

Or `YSI_COMPATIBILITY_MODE=1` on the command-line.

It disables all of YSI's custom syntax and keywords, replacing them with upper-case, double-underscore-suffixed versions:

```pawn
TIMER__ SayHi[1000](playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi!");
}

HOOK__ OnPlayerConnect(playerid)
{
	DEFER__ SayHi(playerid);
}
```

This is to vastly reduce the chances of any of the symbols colliding with another include or library.  For example both YSI and pawn-plus have a `yield` keyword, and there are several different `foreach` implementations.

In this mode you can still use the normal keywords by explicitly enabling them:

```pawn
#define YSI_COMPATIBILITY_MODE
#define YSI_KEYWORD_hook

#include <a_samp>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

TIMER__ SayHi[1000](playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi!");
}

hook OnPlayerConnect(playerid)
{
	DEFER__ SayHi(playerid);
}
```

Alternatively, if you want all but one keyword, you can leave compatibility mode off and just disable a single keyword:

```pawn
#define YSI_NO_KEYWORD_hook

#include <a_samp>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

timer SayHi[1000](playerid)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi!");
}

HOOK__ OnPlayerConnect(playerid)
{
	defer SayHi(playerid);
}
```

