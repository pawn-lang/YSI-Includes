# Quick Start

Creating an inline timer that is called once after five seconds.  Note that the y_inline_timers API
takes time and number of calls (0 for unlimited), not time and forever/once boolean.

```pawn
#include <a_samp>

// Include for `inline`.
#include <YSI_Coding\y_inline>

// Include for `Timer_CreateCallback`.
#include <YSI_Extra\y_inline_timers>

// Store the timer handles.
static gTimers[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
	// This is in the "closure", so it can be used and updated in the inline.
	// Every `using inline` creates a new closure, so `minutes` is per-player.
	new minutes = 0;

	// `inline` is like `stock`, but declares a function inside another
	// function.
	inline OneMinute()
	{
		// Modify `minutes` from the outer function.
		++minutes;

		// Send a message to the `playerid` from the outer function.
		va_SendClientMessage(playerid, COLOUR_MSG, "You have been connected for %d minutes", minutes);

		// When the inline function ends the value of `minutes` is saved for the
		// next call.  If you DON'T want this saving, use `inline const`.
	}

	// Create a timer that calls an inline function with `Timer_CreateCallback`:
	//
	//    `using inline OneMinute` - specify the function and store the closure.
	//    60000 - One minute in milliseconds.
	//    0 - No call count, repeat forever.
	//
	gTimers[playerid] = Timer_CreateCallback(using inline OneMinute, 60000, 0);

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	// Stop the timer (also frees the memory used for the closure).
	Timer_KillCallback(gTimers[playerid]);
}
```

