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

* `.id` - Return value that holds the ID of the command:

```pawn
static gCommandID;

@cmd(.id = gCommandID) say(playerid, params[], help)
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

## Repeat Commands

You can now create multiple commands with the same name, and permissions will be used to determine which one to call, along with priority.  Base commands are the lowest priority, alt commands next, then inline commands (see [Inline Commands](#inline-commands)); at least usually, it depends on creation order.  One example of this could be a `/pm` command, disabled for people who are in gaol:

```pawn
// The normal `/pm` command, uncluttered by worries about who is in gaol:
@cmd() pm(playerid, params[], help)
{
	new targetid, msg[144];
	if (help || sscanf(params, "us[*]", targetid, sizeof (msg), msg))
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "Usage: /pm <target> <message>");
		return 1;
	}
	SendClientMessage(playerid, COLOUR_GREETING, "Sent");
	SendClientMessage(targetid, COLOUR_GREETING, "Message from %s:", ReturnPlayerName(playerid));
	SendClientMessage(targetid, COLOUR_GREETING, msg);
	return 1;
}

// The y_goups documentation has an example of a `/gaol` command to put people in gaol, but it just
// outright disables all commands for them.  We can have a more refined solution:
@cmd(.name = "pm", .group = gGaoled) pm_gaoled__(playerid, params[], help)
{
	SendClientMessage(playerid, COLOUR_FAILURE, "You cannot send PMs while in gaol.");
	return 1;
}
```

An explanation of this example:

* `pm` is the canonical name for the first version of this command and it is a base command.  This means it has the lowest priority and so will only be called if no other command matches the string `/pm` for the current player.
* `pm_gaoled__` is the canonical name of the second version of the command, so is the name used to refer to this command in code.  For example to set its prefix you would use `Command_SetPrefix(YCMD:pm_gaoled__, '!')` (but doing so would create two separate commands in `!pm` and `/pm`, giving gaoled players access to both, so don't - it was just an example).  You would also use `Command_ReProcess(playerid, "pm_gaoled__", true)` to invoke this command variant directly.
* The canonical names are `pm` and `pm_gaoled__`, and must be unique, otherwise the compiler will complain (functions defined twice).  You could make the two canonical names `pm_free__` and `pm_gaoled__` and use `.name = "pm"` for both, but then the priority would depend on the order in which they were added, which in this case would be correct as the addition is done in alphabetical order, and new versions are added to the front of the list, with `pm_g` comeing after `pm_f` in insertion order, so before in priority.
* `.name = "pm"` creates an alt-name for the command and completely hides the canonical version so there is no way for a player to list or call `/pm_gaoled__` directly.  Because this is an alt-name it has slightly higher priority than the base-name version and so anyone allowed to use this command (i.e. anyone in the `gGaoled` group) will always invoke this version.
* `.group = gGaoled` sets who can use this version of the command.
* `Gaol` is the correct spelling of `jail`, in case you were wondering:

```pawn
@cmd(.group = gGroupPolice) jail(playerid, params[], help)
{
	SendClientMessage(playerid, COLOUR_FAILURE, "Did you mean /gaol?");
	return 1;
}

@cmd(.group = gGroupPolice) gaol(playerid, params[], help)
{
	return 1;
}
```

This system makes your code even more modular as you can now split up commands by usage and context.  Put the gaoled version of `/pm` in the police module and leave the majority of the code elsewhere.  If you decide to then create a specialised admin version (`pm_admin__`) you don't need to worry about touching multiple other seemingly irrelevant code locations.

While we spoke a lot about precedence when one player can use multiple variations of the command, the normal way to set this up would be with groups for each variation:

```pawn
@cmd(.group = gGroupAttackers, .name = "respawn") respawn_attackers__(playerid, params[], help)
{
	SetPlayerPos(playerid, 10.5, 103.2, 21.2); // I don't know.  Some base location.
	return 1;
}

@cmd(.group = gGroupDefenders, .name = "respawn") respawn_defenders__(playerid, params[], help)
{
	SetPlayerPos(playerid, 93.2, 8.7, 10.1); // I don't know.  Some other location.
	return 1;
}
```

## Inline Commands

More specifically, these are per-player commands, or dynamic commands.  They allow you to add and remove commands for a single player at any time based on any conditions you like; and, more importantly, you can use inline functions!  Let's expand the earlier `/pm` command with a `/r` command to quickly reply to the last PM sent:

```pawn
// The normal `/pm` command, uncluttered by worries about who is in gaol:
@cmd() pm(playerid, params[], help)
{
	new targetid, msg[144];
	if (help || sscanf(params, "us[*]", targetid, sizeof (msg), msg))
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "Usage: /pm <target> <message>");
		return 1;
	}
	SendClientMessage(playerid, COLOUR_GREETING, "Sent");
	SendClientMessage(targetid, COLOUR_GREETING, "Message from %s:", ReturnPlayerName(playerid));
	SendClientMessage(targetid, COLOUR_GREETING, msg);
	
	// Set up a reply command.
	inline const SendReply(string:reply[])
	{
		SendClientMessage(targetid, COLOUR_GREETING, "Sent");
		SendClientMessage(playerid, COLOUR_GREETING, "Message from %s:", ReturnPlayerName(targetid));
		SendClientMessage(playerid, COLOUR_GREETING, reply);
		@return 1;
	}
	Command_AddCallback("r", tagetid, using inline SendReply);
	
	return 1;
}
```

This implementation is fully compatible with the `pm_gaoled__` version earlier, again showing how edits in one part of your code can be done without touching other areas at all.

One problem with this version is that it will slowly run out of memory, because a new version of `/r` is created every time the target gets a PM, we can solve this in several ways:

1.  Just remove old versions before creating the new command:

```pawn
	// Just in case, remove any old versions of `/r`:
	Command_RemoveCallback("r", tagetid);
```

2.  A new extension to EBC which adds a lightweight timer as the owner (`TBC` = Timer Based Callback, sadly I couldn't fit it to my other brother's initials):

```pawn
	// Expire this command after one minute.
	Command_AddCallback("r", tagetid, TBC(60000, using inline SendReply));
```

In which case you may want a fallback for after that callback expires:

```pawn
@cmd() r(playerid, string:params[], help)
{
	SendClientMessage(playerid, COLOUR_FAILURE, "No recent message to reply to.");
	return 1;
}
```

3. Manually track and remove the old versions.  But this is more effort.

Notes:

* You may have noticed that the command only has `params`.  This is a new feature - you can create the callback with `params[]`, `playerid, params[]`, or `playerid, params[], help` and all variants will be correctly called.
* `@return` is used instead of `return`.  This is exactly the same, but bypasses some limitations with using `return` inside `inline`.
* Because `TBC` will remove the command eventually, and the latest added version of an inline callback always take precedence (you can remove the new version and the old version will be used again until it too is removed, so you can create a stack of commands), we can create a full chat system very simply:

```pawn
@cmd() r(playerid, string:params[], help)
{
	SendClientMessage(playerid, COLOUR_FAILURE, "No recent message to reply to.");
	return 1;
}

static SendPM(from, to, string:msg[])
{
	// We don't need to copy `msg` to a local variable because it isn't use inside the inline.
	
	SendClientMessage(from, COLOUR_GREETING, "Sent");
	SendClientMessage(to, COLOUR_GREETING, "Message from %s:", ReturnPlayerName(from));
	SendClientMessage(to, COLOUR_GREETING, msg);
	
	// Set up a reply command.
	inline const SendReply(string:reply[])
	{
		SendPM(to, from, reply);
		@return 1;
	}
	Command_AddCallback("r", to, TBC(60000, using inline SendReply));
	
	// This shows why `@return` is required - there's no `return`, and a compiler limitation would
	// otherwise give a warning in this case.
}

@cmd() pm(playerid, params[], help)
{
	new targetid, msg[144];
	if (help || sscanf(params, "us[*]", targetid, sizeof (msg), msg))
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "Usage: /pm <target> <message>");
		return 1;
	}
	
	SendPM(playerid, targetid, msg);
	return 1;
}
```

## Enhanced `/buy` Command.

One motivating example for this system was a context-aware `/buy` command:

First a tiny piece of boilerplate required just once regardless of the number and type of inline commands used in areas.  We also need a hook to destoy ECB functions when their owning areas are destroyed, but that is included by default:

```pawn
// Streamer tags are required for `EBC`.
public OnPlayerLeaveDynamicArea(playerid, DynamicArea:areaid)
{
	// Destroy all commands for this player in this area.  `EBC()` without a `using` expression will
	// just return the encoded owner to be compared against.  
	Command_RemoveCallback("", playerid, EBC(areaid));
	return 1;
}
```

Create an area around a house that you can buy:

```pawn
DynamicArea:CreateBuyableHouse(Float:x, Float:y, Float:z, price)
{
	inline const OnEnter(playerid, DynamicArea:areaid)
	{
		inline const BuyHouse(params[])
		{
			if (GetPlayerMoney(playerid) > price)
			{
				GetPlayerMoney(playerid) -= price;
				SendClientMessage(playerid, COLOUR_GREETING, "You bought the house.");
			}
			else
			{
				SendClientMessage(playerid, COLOUR_FAILURE, "Not enough money.");
			}
			@return 1;
		}
		
		Command_AddCallback("buy", playerid, EBC(areaid, using inline BuyHouse));
		
		@return 1;
	}
	
	return Streamer_CreateSphereCallback(using inline OnEnter, x, y, z, 30.0);
}
```

Create a totally different `/buy` command in an ammunation:

```pawn
CreateAmmunation(Float:x1, Float:y1, Float:x2, Float:y2)
{
	inline const OnEnter(playerid, DynamicArea:areaid)
	{
		inline const BuyWeapons(params[])
		{
			new weapon, ammo, alt;
			if (sscanf(params, "'weapon'k<weapon>i|'armour'|'ammo'i", alt, weapon, ammo, ammo))
			{
				ShowAmmunationMenu(playerid);
			}
			else switch (alt)
			{
			case 1:
				GivePlayerWeapon(playerid, weapon, ammo);
			case 2:
				SetPlayerArmour(playerid, 100.0);
			case 3:
				GivePlayerAmmo(playerid, GetPlayerWeapon(playerid), ammo);
			}
			@return 1;
		}
		
		Command_AddCallback("buy", playerid, EBC(areaid, using inline BuyWeapons));
		
		@return 1;
	}
	
	Streamer_CreateRectCallback(using inline OnEnter, x1, y1, x2, y2);
}
```

Finally a fallback command (which is also used to provide `/help buy` if no other existent variation takes a `help` parameter):

```pawn
@cmd() buy(playerid, params[], help)
{
	if (help)
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "Buy a thing you are stood near.");
	}
	else
	{
		SendClientMessage(playerid, COLOUR_FAILURE, "There is nothing here to buy.");
	}
	return 1;
}
```

