# Features

## Declaring Commands

```pawn
YCMD:me(playerid, params[], help)
{
	if (IsNull(params))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
	new str[144];
	format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
	SendClientMessageToAll(COLOUR_GREETING, str);
	return 1;
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
	if (IsNull(params))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
	new str[144];
	format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
	SendClientMessageToAll(COLOUR_GREETING, str);
	return 1;
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

## Help

Every command comes with a `help` parameter, which should be used to display information about the command, rather than run the command.  This helps keep everything relating to one command - information and execution, in one place:

```pawn
YCMD:me(playerid, params[], help)
{
	if (help)
	{
		SendClientMessage(playerid, COLOUR_GREETING, "Role-play an action.  Example: '/me jumps'");
		return 1;
	}
	else if (IsNull(params))
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
		return 1;
	}
	else
	{
		new str[144];
		format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
		SendClientMessageToAll(COLOUR_GREETING, str);
		return 1;
	}
}
```

This `help` parameter is triggered by special `/help` commands, for example to type `/help me` and get the above information add the following command to your mode:

```pawn

YCMD:help(playerid, params[], help)
{
	if (help)
	{
		SendClientMessage(playerid, COLOUR_GREETING, "Use `/help <command>` to get information about the command.");
	}
	else if (IsNull(params))
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "Please enter a command.");
	}
	else
	{
		Command_ReProcess(playerid, params, true);
	}
	return 1;
}
```

This is the most basic version, but can be expanded of course.

