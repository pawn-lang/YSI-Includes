# Features

## Declaring Commands

```pawn
@cmd() me(playerid, params[], help)
{
	if (IsNull(params))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You must enter an action");
	new str[144];
	format(str, sizeof (str), "** %s %s **", ReturnPlayerName(playerid), params);
	SendClientMessageToAll(COLOUR_GREETING, str);
	return 1;
}
```

## Old Syntax

The preferred way to declare commands is with the `@cmd()` decorator, but the old methods still work:

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

```pawn
CMD:me(playerid, params[])
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

## `@cmd()`

`YCMD:` looks like a tag, which has a meaning in pawn and shouldn't be used to declare special function types.  Thus YSI is moving towards decorators, which are function-like prefixes to function names starting with `@`.  You can always identify a decoarated function as `@decorator() function()`, as opposed to `Tag:function()` which is ambiguous.  To declare a basic command use `@cmd()` (or `@command()`, they're synonyms):

```pawn
@cmd() jump(playerid, params[], help)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerPos(playerid, x, y, z + 2.0);
	return 1;
}
```

The `@cmd()` decorator can take many named parameters to configure the command behaviour:

* `.disable` - Makes the command unusable by default, until you enable it again with `Command_SetDisabled(id, false);`:

```pawn
@cmd(.disable = true) unusable(playerid, params[], help)
{
	return 1;
}
```

* `.hidden` - The command is usable, but won't be listed in functions like `Command_GetNext` which list a player's commands:

```pawn
@cmd(.hidden = true) usable(playerid, params[], help)
{
	return 1;
}
```

* `.name` - Use this parameter to set a name for the command if the name is not a valid pawn function name.  Useful for non-English commands:

```pawn
@cmd(.name = "машина") vehicle(playerid, params[], help)
{
	return 1;
}
```

The function name remains the internal canonical name, since many references need to be valid pawn identifiers:

```pawn
Command_SetPlayer(YCMD:vehicle, playerid, true);
```

* `.alts` - An array of alternate names that this command can also be used as:

```pawn
@cmd(.alts = { "cmd2", "cmd3" }) cmd1(playerid, params[], help)
{
	return 1;
}
```

* `.group` - Not yet implemented, but the default group that can use this command:

```pawn
final Group:gAdmins = Group_Create("admins");

@cmd(.group = gAdmins) ban(playerid, params[], help)
{
	return 1;
}
```

You can of course mix up the parameters as needed.

## Help Information

```pawn
@cmd() me(playerid, params[], help)
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
@cmd() me(playerid, params[], help)
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
@cmd() help(playerid, params[], help)
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

