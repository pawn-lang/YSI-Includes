# Quick Start

Creating a per-player timer using y_ebc, y_inline, and y_inline_timers

```pawn
#include <a_samp>

// Include for `inline`.
#include <YSI_Coding\y_inline>

// Include for `Timer_CreateCallback`.
#include <YSI_Extra\y_inline_timers>

// Include for `EBC`.
#include <YSI_Coding\y_ebc>

public OnPlayerConnect(playerid)
{
	// This is ONLY called if `playerid` doesn't disconnect in the interim.
	inline HasLoggedIn()
	{
		if (!IsLoggedIn(playerid)
		{
			SendClientMessage(playerid, COLOUR_ERROR, "You didn't log in within five minutes.");
			printf("Kicking %d because they didn't log in", playerid);
			Kick(playerid);
		}
	}

	// Ensure that the player has logged in within five minutes.
	Timer_CreateCallback(EBC(playerid, using inline HasLoggedIn), 5 * 60 * 1000, 1);

	return 1;
}
```

`EBC` sets the owner of the *callback*, not the thing *using* the callback (here a timer).  It works by simply wrapping the callback and not calling it when needed if the owner no longer exists.  It will not, for example, kill the timer, because this generic library cannot possibly know about how the callback is used.  You should thus be aware that a repeating timer will NOT be killed when the player disconnects.

By default the code assumes that the owner is a player.  If it isn't a player you can use a tag to indicate this:

```pawn
Timer_CreateCallback(EBC(Vehicle:vehicle, using inline StopVehicle), 5 * 60 * 1000, 1);
```

The default tags are `Player:`, `Vehicle:` and `Object:`, but adding handlers for more is fairly trivial.

