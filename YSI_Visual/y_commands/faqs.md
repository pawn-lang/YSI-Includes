# Questions

## Why can't I call commands directly?

With ZCMD you can do:

```pawn
CMD:MyCommand(playerid, params[])
{
	return cmd_MyOtherCommand(playerid, params);
}

CMD:MyOtherCommand(playerid, params[])
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi");
	return 1;
}
```

This is an error in y_commands.  y_commands has native support for alternate command names, so the correct way to do this is:

```pawn
hook OnScriptInit()
{
	Command_AddAlt(YCMD:MyOtherCommand, "MyCommand");
}

YCMD:MyOtherCommand(playerid, params[])
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi");
	return 1;
}
```

Or (in YSI 5.x):

```pawn
YCMD:MyCommand(playerid, params[], help) = MyOtherCommand;

YCMD:MyOtherCommand(playerid, params[], help)
{
	SendClientMessage(playerid, COLOUR_GREETING, "Hi");
	return 1;
}
```

## But how do I call them from something other than another command?

You don't!

## Why?

This is objectively bad coding practice.  There are well defined ways of calling code from other code already - they're called functions!  Commands are an interface to the outside world (i.e. players), once you're in code you don't need them.  Parameters are passed to commands via strings, which are hard to deal with (hence `sscanf` and other tools), but parameters in real code are easy to deal with.

Code to do the same thing in both a command with ZCMD and by clicking a player might look like:

```pawn
CMD:arrest(playerid, params[])
{
	if (!IsPlayerCop(playerid))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You are not a cop!");
	new targetid;
	if (sscanf(params, "u", targetid) || targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOUR_FAILURE, "Could not find the target!");
	// Put them in gaol.
	SetPlayerPos(targetid, 1084.3, 2250.6, 503.4);
	SendClientMessage(playerid, COLOUR_GREETING, "Player arrested!");
	SendClientMessage(targetid, COLOUR_GREETING, "You were arrested!");
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	new params[16];
	format(params, sizeof (params), "%d", clickedplayerid);
	return cmd_arrest(playerid, params);
}
```

There are several problems with this code:

1. You convert a number to a string, to pass it to the command, to convert it back to a number.  This is just a waste of effort, it also bypasses the compiler's type checking.
2. It assumes the permissions for both are the same.  If only detectives can click names to arrest, this becomes:

```pawn
static bool:gCalledFromClick = false;

CMD:arrest(playerid, params[])
{
	if (!gCalledFromClick && !IsPlayerCop(playerid))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You are not a cop!");
	new targetid;
	if (sscanf(params, "u", targetid) || targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOUR_FAILURE, "Could not find the target!");
	// Put them in gaol.
	SetPlayerPos(targetid, 1084.3, 2250.6, 503.4);
	SendClientMessage(playerid, COLOUR_GREETING, "Player arrested!");
	SendClientMessage(targetid, COLOUR_GREETING, "You were arrested!");
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if (!IsPlayerDetective(playerid))
		return SendClientMessage(playerid, COLOUR_FAILURE, "You are not a detective!");
	new params[16];
	format(params, sizeof (params), "%d", clickedplayerid);
	gCalledFromClick = true;
	new ret = cmd_arrest(playerid, params);
	gCalledFromClick = false;
	return ret;
}
```

You need to add in a lot of extra code to do the permissions, and the command becomes bloated because it needs to know that it can be called from a click, and that if it is called from a click, to not do the permissions checks.

The code gets even more complex with y_commands and y_groups, because the permissions checks aren't done in the command itself:

```pawn
static Group:gGroupBypass;
static Group:gGroupCop;
static Group:gGroupDetective;

YCMD:arrest(playerid, params[], help)
{
	new targetid;
	if (sscanf(params, "u", targetid) || targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOUR_FAILURE, "Could not find the target!");
	// Put them in gaol.
	SetPlayerPos(targetid, 1084.3, 2250.6, 503.4);
	SendClientMessage(playerid, COLOUR_GREETING, "Player arrested!");
	SendClientMessage(targetid, COLOUR_GREETING, "You were arrested!");
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if (gGroupDetective < playerid)
		return SendClientMessage(playerid, COLOUR_FAILURE, "You are not a detective!");
	new cmdtext[16];
	format(cmdtext, sizeof (cmdtext), "/arrest %d", clickedplayerid);
	gGroupBypass += playerid;
	new ret = Command_ReProcess(playerid, cmdtext);
	gGroupBypass -= playerid;
	return ret;
}

public OnScriptInit()
{
	// Create the groups.
	gGroupBypass = Group_Create();
	gGroupCop = Group_Create("Cops");
	gGroupDetective = Group_Create("Detectives");
	
	// Disable the command for normal players.
	Group_SetCommandDefault(YCMD:arrest, false);
	
	// Enable the command for cops, and people using the click bypass.
	Group_SetCommand(gGroupCop, YCMD:arrest, true);
	Group_SetCommand(gGroupBypass, YCMD:arrest, true);
}
```

## So what is the solution?

The correct way to handle this, with y_commands, ZCMD, or just any other code at all, is to use a third function.  This function will do the actual arresting logic, and the callbacks and commands will just provide an external interface to this function:

```pawn
DoArrest(playerid, targetid)
{
	// Put them in gaol.
	SetPlayerPos(targetid, 1084.3, 2250.6, 503.4);
	SendClientMessage(playerid, COLOUR_GREETING, "Player arrested!");
	SendClientMessage(targetid, COLOUR_GREETING, "You were arrested!");
}

YCMD:arrest(playerid, params[], help)
{
	new targetid;
	if (sscanf(params, "u", targetid) || targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOUR_FAILURE, "Could not find the target!");
	DoArrest(playerid, targetid);
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if (gGroupDetective < playerid)
		return SendClientMessage(playerid, COLOUR_FAILURE, "You are not a detective!");
	DoArrest(playerid, clickedplayerid);
	return true;
}
```

Now you are fully leveraging the power of the compiler - this is faster because it uses real parameters instead of strings, and it can check that all the parameters are correct.

## Why is `Command_ReProcess` not `const`-correct?

There are two reasons:

1. People don't make their commands `const`-correct:

```pawn
YCMD:mycommand(playerid, params[], help)
{
}
```

Here, `params` isn't `const`, and very very frequently isn't.  Making `Command_ReProcess`, which calls the commands, `const`-correct would either mean slowing the function down slightly to copy data, or making every single command everywhere `const`-correct.  Other command processors can get away with this because they use a slower call method, which copies things, already.

2. It encourages bad practices:

As explained above, you can't call commands directly in y_commands, and you shouldn't be able to.  Making `Command_ReProcess` `const`-correct would make this code possible:

```pawn
Command_ReProcess("/mycommand");
```

This is doing the wrong thing, and we want to make doing the wrong thing as hard as possible.  See [*So what is the solution*](#so-what-is-the-solution) for what to do instead.

## Isn't `other command processor` faster than this?

Maybe.  So?  y_commands is as-fast, or slightly faster, than most other command processors (if you believe their graphs, but they all have an agenda), but with way more features.

### How to make a slightly faster command processor:

1. Remove checks:

> ZCMD has loads of checks I don't understand, they must be pointless.

2. Remove features:

> No-one wants to check if a player can use this command, I'll just delete that.

3. Actually work on the algorithms involved.

Only y_commands bothers with this one.

### What is being timed?

Most command processors, when they claim they are faster, only time how long it takes to CALL the command.  Once code execution reaches the command, that's it.  But what happens inside the command?  For most people, the first thing they do is check if a player can use the command.  This permssion check isn't included in the command processor time because it is deemed part of the command itself.  y_commands, however, does these checks for you, and includes the time taken to do these checks in its reports.  Despite this overhead, it is still faster than many command processors.  So you can have a slightly faster processor and much slower commands, or a slighty slower command processor and much faster commands (because the processor does the hard work for you).

But again, they won't tell you this.

