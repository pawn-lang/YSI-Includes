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
	foreach (new playerid : Admin)
	{
		ShowTextToPlayer(playerid, text);
	}
}
```

Or in terms of an additional internal function:

```pawn
static ShowTextToPlayerSet(const bool:players[MAX_PLAYERS], const text[])
{
	foreach (new playerid : Player)
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
	foreach (new playerid : Admin)
	{
		players[playerid] = true;
	}
	ShowTextToPlayerSet(players, text);
}
```

But you still end up with multiple just slightly incompatible functions.  YSI already has a lot of code for dealing with sets of players: y_groups (for pre-defined named groups), and y_playerarray (for bit arrays of players).  y_playerset abstracts over these further to allow you to write a single function that can take a single player id, an array of players, or a groups.  You do need to tell the compiler this, through a simple decorator `#define` (Note the use of `(` and no space in the define):

```pawn
// Sadly `@PSF()SendText()` here doesn't yet work.
SentText(@PlayerSet:players, const text[])
{
	foreach (new playerid : PS(players))
	{
		// Real message code.
	}
}

// `PSF` stands for `PlayerSetFunction`.
#define SentText( @PSF()SentText(
```

Using `@PlayerSet` you can now call this function in a wide range of manners:

```pawn
SendText(player, "Hi one player.");
```

```pawn
new Group:admins = Group_Create("admins");
SendText(admins, "Hi admins.");
```

Passing arrays needs `@` prefix:

```pawn
new PlayerArray:jailed<MAX_PLAYERS>;
SendText(@jailed, "Hi jailed.");
```

```pawn
new list[MAX_PLAYERS];
list[0] = player0;
list[1] = player5;
list[2] = player88;
list[3] = INVALID_PLAYER_ID;
SendText(list, "Hi random three players.");
```

```pawn
new bool:flags[MAX_PLAYERS];
flags[player0] = true;
flags[player5] = true;
flags[player88] = true;
SendText(list, "Hi same random three players.");
```

```pawn
enum E_PLAYER_DATA
{
	E_PLAYER_DATA_SOMETHING,
	bool:E_PLAYER_DATA_ADMIN,
	E_PLAYER_DATA_OTHER,
}

new gPlayerData[MAX_PLAYERS][E_PLAYER_DATA];

gPlayerData[player0][E_PLAYER_DATA_ADMIN] = true;
gPlayerData[player5][E_PLAYER_DATA_ADMIN] = true;
gPlayerData[player88][E_PLAYER_DATA_ADMIN] = true;
SendText(gPlayerData<E_PLAYER_DATA_ADMIN>, "Hi same random three players.");
```

