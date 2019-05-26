# y_flooding

Provides a number of ways of dealing with multiple connections from the same IP, including banning the IP, rejecting too many connections, and more.

## YSI

For general YSI information, see the following links:

* [Installation](../installation.md)
* [Troubleshooting](../troubleshooting.md)

## Documentation

Limit the number of connections on an IP:

```pawn
#include <YSI_Server\y_flooding>

public OnScriptInit()
{
	// Allow unlimited connections per IP.
	SetMaxConnections(); // -1, default.

	// Only allow two connections per IP.
	SetMaxConnections(2);
}
```

The possible actions for too many players are;

* `e_FLOOD_ACTION_NOTHING` - Do nothing, basically disable the system.
* `e_FLOOD_ACTION_BLOCK` - Kick the latest player on this IP (default).
* `e_FLOOD_ACTION_KICK` - Kick all players on this IP.
* `e_FLOOD_ACTION_BAN` - Ban the IP and have players time out.
* `e_FLOOD_ACTION_FBAN` - Ban the IP and kick all the players instantly.
* `e_FLOOD_ACTION_GHOST` - Silently force all players on the IP to reconnect.
* `e_FLOOD_ACTION_OTHER` - Call a callback (`OnFloodLimitExceeded(ip[], count)`).

To specify an action, pass an extra parameter:

```pawn
#include <YSI_Server\y_flooding>

public OnScriptInit()
{
	// Only allow one connection per IP, and ban the IP when there are 2+.
	SetMaxConnections(1, e_FLOOD_ACTION_FBAN);
}
```

To perform a custom action when there are too many connections, use
`OnFloodLimitExceeded`, which also has access to the `FloodingPlayer` iterator
to loop over the IDs of all the players with the current IP:

```pawn
#include <YSI_Server\y_flooding>
#include <YSI_Data\y_iterate>

public OnScriptInit()
{
	// Set to 1, but do a custom action.
	SetMaxConnections(1, e_FLOOD_ACTION_OTHER);
}

public OnFloodLimitExceeded(ip[], count)
{
	// Not called for `count == 1`, because the limit hasn't been exceeded yet.
	if (count == 2)
	{
		foreach (new i : FloodingPlayer)
		{
			SendClientMessage(i, COLOUR_WARN, "There are two of you on this IP, one more and you will be banned.");
		}
	}
	else
	{
		foreach (new i : FloodingPlayer)
		{
			BanEx(i, "There are three+ of you on this IP, I warned you you would be banned.");
		}
	}
}
```

Note that the `FloodingPlayer` iterator is only valid within the scope of
`OnFloodLimitExceeded`.

You can get the current count and action with:

```pawn
Flooding_GetMaxConnections();
e_FLOOD_ACTION:Flooding_GetConnectionAction();
```

## External Links

These are links to external documentation and tutorials; both first- and third-party.  Note that these may be incomplete, obsolete, or otherwise inaccurate.

