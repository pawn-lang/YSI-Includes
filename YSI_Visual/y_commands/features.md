# Features

## Declaring Commands

```pawn
YCMD:me(playerid, params[], help)
{
	if (isnull(params))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
	new str[144];
	format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
	return SendClientMessageToAll(COLOUR_GREETING, str);
}
```

## Declaring Alternate Command Names

```pawn
YCMD:i(playerid, params[], help) = me;
```

## Help Information

```pawn
YCMD:me(playerid, params[], help)
{
	if (help)
		return SendClientMessage(playerid, COLOUR_GREETING, "Role-play an action.  Example: '/me jumps'");
	if (isnull(params))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
	new str[144];
	format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
	return SendClientMessageToAll(COLOUR_GREETING, str);
}
```

## Permissions

```pawn
new Group:gGroupLoggedIn;

public OnScriptInit()
{
	// Create a group for people logged in.
	gGroupLoggedIn = Group_Create();

	// Disable all commands by default.
	Group_SetGlobalCommandDefault(false);

	// Enable the command only for people in this group.
	Group_SetCommand(gGroupLoggedIn, YCMD:me, false);
}

public OnPlayerLogIn(playerid)
{
	// Add the player to the group - they can now use `/me`.
	gGroupLoggedIn += playerid;
}
```

