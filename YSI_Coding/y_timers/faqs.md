# Issues

## ``error 047: array sizes do not match, or destination array is too small``

This is caused when you redefin `MAX_PLAYERS` and use `ptask`:

```pawn
#include <a_samp>
#include <YSI_Coding\y_timers>

#undef MAX_PLAYERS
#define MAX_PLAYERS 100

ptask Ping[1000](playerid)
{
	SendClientMessage(playerid, COLOUR_PING, "ping");
}
```

The problem is that the define is after `y_timers` was included.  To fix this, just move the definition:

```pawn
#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 100

#include <YSI_Coding\y_timers>

ptask Ping[1000](playerid)
{
	SendClientMessage(playerid, COLOUR_PING, "ping");
}
```

