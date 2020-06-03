# Introduction

A lot of scripts end up with very similar functions all doing the same thing for different sets of players.  For example:

```pawn
ShowTextToPlayer(playerid, const text[])
{
}

ShowTextToAdmins(const text[])
{
}

ShowTextToAll(const text[])
{
}

ShowTextToTeam(teamid, const text[])
{
}
```

These are most easilly defined in terms of each other:

```pawn
ShowTextToPlayer(playerid, const text[])
{
	// Real message code.
}

ShowTextToAdmins(const text[])
{
	foeach (new playerid : Admin)
	{
		ShowTextToPlayer(playerid, text);
	}
}
```

Or in terms of an additional internal function:

```pawn
static ShowTextToPlayerSet(const bool:players[MAX_PLAYERS], const text[])
{
	foeach (new playerid : Player)
	{
		if (players[playerid])
		{
			// Real message code.
		}
	}
}

ShowTextToAdmins(const text[])
{
	new
		bool:players[MAX_PLAYERS];
	foeach (new playerid : Admin)
	{
		players[playerid] = true;
	}
	ShowTextToPlayerSet(players, text);
}
```

But you still end up with multiple just slightly incompatible functions.  YSI already has a lot of code for dealing with sets of players: y_groups (for pre-defined named groups), and y_playerarray (for bit arrays of players).  y_playerset abstracts over these further to allow you to write a single function that can take a single player id, an array of players, or a groups:

```pawn
SentText(@PlayerSet:players, const text[])
{
	foeach (new playerid : PS(players))
	{
		// Real message code.
	}
}
```

Using `@PlayerSet` you can now call this function in a wide range of manners:

```pawn
SendText