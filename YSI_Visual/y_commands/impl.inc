/**--------------------------------------------------------------------------**\
					================================
					Y Sever Includes - Commands Core
					================================
Description:
	Runs commands registered with the system and calls the required functions.
	Also handles alternate names and prefixes.  Based very loosely on dcmd.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI commands include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	2.0
Changelog:
	23/06/13:
		Rewritten from scratch for MORE speed.
		Punycode support.
		More failure messages.
		Cleaner code.
	20/10/10:
		Fixed a bug with insensitive commands - my fault for not testing.
	06/01/08:
		Improved master and /help support.
	04/01/08:
		Fixed bad element in Command_SetDeniedReturn.
	12/08/07:
		Added master support.
	24/06/07:
		Modifed a few functions to use Bit_GetBit for speed.
	04/05/07:
		Completed command use support.
		Added invalid character protection.
	02/05/07:
		Added YSI_ prefix to all globals.
	14/04/07:
		Updated header documentation with more than changelog/functions.
		Added function name requesting.
	13/04/07:
		Added function documentation.
		Added wrapped functions for e_COMM_FLAG values missing them.
		Added header function list.
	12/04/07:
		Added command removal.
	11/04/07:
		Changed system slightly to handle names and alt names separately.  Still
		need a better way of ignoring names when alt names are used.
	10/04/07:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
\**--------------------------------------------------------------------------**/

enum E_COMMAND
{
	HASH_MAP_DATA<MAX_COMMAND_LENGTH char>,
	
	// Share a memory location with the hashmap stored name.
	E_COMMAND_NAME[MAX_COMMAND_LENGTH char] = 0,
	
	// IGNORE THESE, THEY COVER HASH MAP DATA.
	_E_COMMAND_PAD_0, _E_COMMAND_PAD_1,
	
	// Who can use this command?
	PlayerArray:E_COMMAND_USERS<MAX_PLAYERS>,
	// Function pointer.
	E_COMMAND_POINTER
}

enum e_COMMAND_ERRORS
{
	COMMAND_ZERO_RET,  // The command returned 0.
	COMMAND_OK,        // Called corectly.
	COMMAND_UNDEFINED, // Command doesn't exist.
	COMMAND_DENIED,    // Can't use the command.
	COMMAND_HIDDEN,    // Can't use the command, don't let them know it exists.
	COMMAND_NO_PLAYER, // Used by a player who shouldn't exist.
	COMMAND_DISABLED   // All commands are disabled for this player.
}

enum e_COMMAND_FLAGS (<<= 1)
{
	e_COMMAND_FLAGS_ZERO_RET = 1, // The command returned 0.
	e_COMMAND_FLAGS_OK,        // Called corectly.
	e_COMMAND_FLAGS_NOT_FOUND, // Command doesn't exist.
	e_COMMAND_FLAGS_DENIED,    // Can't use the command.
	e_COMMAND_FLAGS_HIDDEN,    // Can't use the command, don't let them know it exists.
	e_COMMAND_FLAGS_NO_PLAYER, // Used by a player who shouldn't exist.
	e_COMMAND_FLAGS_DISABLED,  // All commands are disabled for this player.
	// Save counts for callbacks.
	e_COMM_FLAG_OPCP     = 0x00FF0000,
	e_COMM_FLAG_OPCP_ADD = 0x00010000,
	e_COMM_FLAG_OPCR     = 0xFF000000,
	e_COMM_FLAG_OPCR_ADD = 0x01000000
}

// Store which script(s) own which commands.
MASTER_DATA<MAX_COMMANDS>

// Information for returning error messages.
static stock __declspec(dist_tagged) e_COMMAND_FLAGS:YSI_g_sCommandFlags;
static stock __declspec(distributed) YSI_g_sErrorMessages[e_COMMAND_ERRORS][144];
// Who has had ALL their commands disabled?
static stock __declspec(dist_special) PlayerArray:YSI_g_sDisabledPlayers<MAX_PLAYERS>;

static stock
	YSI_g_sReturnBuffer[YSI_MAX_STRING],
	// Quickly reference and store commands by name.
	HashMap:YSI_g_sCommandMap<MAX_COMMANDS>;

static stock __declspec(dist_master) YSI_g_sCommands[MAX_COMMANDS][E_COMMAND];

static stock const
	YSI_gscOPCR[] = "OnPlayerCommandReceived",
	YSI_gscOPCP[] = "OnPlayerCommandPerformed",
	YSI_gscISI[] = "isi",
	YSI_gscISII[] = "isii";

// "YCMD:" macros.  The true core is "RC:", which is in "y_master".
#define _YCMD_0:_YCMD_1:_YCMD_2:%0(%1[]%2) RC:%0(%1[]%2)
#define _YCMD_1:_YCMD_2:%0, Command_GetID(#%0),
#define _YCMD_2:%0)  Command_GetID(#%0))
#define @YCMD:%0;  Command_TouchNamed(#%0);

#define YCMD: _YCMD_0:_YCMD_1:_YCMD_2:

// ZCMD compatibility.
#define CMD:%0(%1) RC:%0(%1,__help)if(__help)return 0;else
#define COMMAND CMD

// Forwards for optional command callbacks.
forward e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success); 
forward e_COMMAND_ERRORS:OnPlayerCommandPerformed(playerid, cmdtext[], e_COMMAND_ERRORS:success); 

/**--------------------------------------------------------------------------**\
<summary>_Command_IsEmptySlot</summary>
<param name="idx">Command to test.</param>
<returns>
	-
</returns>
<remarks>
	Tests if the given slot is empty.
</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_IsEmptySlot(%0) (!YSI_g_sCommands[(%0)][E_COMMAND_NAME])

/**--------------------------------------------------------------------------**\
<summary>_Command_IsAlt</summary>
<param name="idx">Command to test.</param>
<returns>
	-
</returns>
<remarks>
	Tests if the given slot is an alternate command.
</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_IsAlt(%0) (YSI_g_sCommands[(%0)][E_COMMAND_POINTER] & cellmin)

/**--------------------------------------------------------------------------**\
<summary>_Command_GetReal</summary>
<param name="ptr">AMX function pointer.</param>
<param name="idx">Index of the parent command data.</param>
<param name="name">Destination for the parent function name.</param>
<returns>
	-
</returns>
<remarks>
	Finds the original version of an alt command.
</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_GetReal(%0,%1,%2); \
	%0=YSI_g_sCommands[(%1)][E_COMMAND_POINTER];				\
	if((%0)&cellmin){											\
		do{														\
			%1=(%0)&~cellmin,									\
			%0=YSI_g_sCommands[(%1)][E_COMMAND_POINTER];}		\
		while((%0)&cellmin);									\
		strunpack(%2,YSI_g_sCommands[(%1)][E_COMMAND_NAME]);}

/**--------------------------------------------------------------------------**\
<summary>Command_Find</summary>
<param name="cmd[]">The command name to find.</param>
<returns>
	The array slot of this command, or -1.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Command_Find(%0) HashMap_Get(YSI_g_sCommandMap, (%0))

/**--------------------------------------------------------------------------**\
<summary>Command_OnReceived</summary>
<param name="error">Which error to show.</param>
<param name="playerid">Player who typed the command.</param>
<param name="cmdtext">What they typed.</param>
<returns>
	-
</returns>
<remarks>
	Call OnPlayerCommandReceived once the system knows how the player can use
	this command (if they can).  The order of the parameters is such that the
	error comes first.  This is because it is compile-time concatenated to make
	the error enum value, and putting that parameter first means that we don't
	need to ommit the space after any comma.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined COMMAND_USE_ERRORS
	#define Command_ErrorRet(%2) (YSI_g_sCommandFlags&e_COMMAND_FLAGS:(1<<_:(%2)))
	
	#define Command_ErrorMsg(%2) YSI_g_sErrorMessages[%2]
	
	#if defined _Text_Send
		#define Command_Error(%0,%2) (Command_ErrorMsg(%2)[0]?(Text_Send((%0),Command_ErrorMsg(%2)),Command_ErrorRet(%2)):Command_ErrorRet(%2))
	#else
		#define Command_Error(%0,%2) (Command_ErrorMsg(%2)[0]?(SendClientMessage((%0),0xFF0000AA,Command_ErrorMsg(%2)),Command_ErrorRet(%2)):Command_ErrorRet(%2))
	#endif
#else
	#define Command_Error(%0,%2) ((%2) == COMMAND_OK)
#endif

#define Command_OnReceived(%2,%0,%1) ((sErr=(YSI_g_sCommandFlags&e_COMM_FLAG_OPCR)?(e_COMMAND_ERRORS:W@(YSI_gscOPCR,YSI_gscISI,(%0),(%1),(_:COMMAND_%2))):(COMMAND_%2)),Command_Error(%0,sErr))

/**--------------------------------------------------------------------------**\
<summary>Command_IsValid</summary>
<param name="command">Command to get for.</param>
<returns>
	Is this command ID valid?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_IsActive(%0) (YSI_g_sCommands[(%0)][E_COMMAND_NAME])
#define _Command_IsValid(%0) ((0 <= (%0) < MAX_COMMANDS) && _Command_IsActive(%0))

foreign bool:Command_IsValid(cmd);

global bool:Command_IsValid(cmd)
{
	return _Command_IsValid(cmd);
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetName</summary>
<param name="f">Command to get the name of.</param>
<returns>
	-
</returns>
<remarks>

native Command_GetName(funcid);

</remarks>
\**--------------------------------------------------------------------------**/

#define Command_Name(%0) (YSI_g_sCommands[(%0)][E_COMMAND_NAME])

foreign string:Command_GetName(f);

global string:Command_GetName(f)
{
	YSI_g_sReturnBuffer[0] = '\0';
	if (_Command_IsValid(f)) strunpack(YSI_g_sReturnBuffer, Command_Name(f));
	return YSI_g_sReturnBuffer;
}

/**--------------------------------------------------------------------------**\
<summary>OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Add all local commands in to the system.
</remarks>
\**--------------------------------------------------------------------------**/

forward _Command_DoInit();

hook OnScriptInit()
{
	P:1("Command_OnScriptInit called");
	#if YSIM_NOT_CLIENT
		HashMap_Init(YSI_g_sCommandMap, YSI_g_sCommands);
		for (new func = 0; func != MAX_COMMANDS; ++func)
		{
			YSI_g_sCommands[func][E_COMMAND_POINTER] = -1;
		}
	#endif
/*	_Command_DoInit();
}

#if (_YSIM_IS_SERVER || _YSIM_IS_CLOUD)
	public _Command_DoInit() <_YCM:p>
	{
		//Bescause they get removed again.
		if (funcidx(YSI_gscOPCR) != -1) Command_IncOPCR();
		if (funcidx(YSI_gscOPCP) != -1) Command_IncOPCP();
	}
	
	public _Command_DoInit() <>
#else
	public _Command_DoInit()
#endif
	{*/
		P:2("_Command_DoInit <> called");
		new
			entry,
			buffer[32 char],
			idx,
			id2;
		P:5("Command_OnScriptInit: Pre-loop");
		while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yC_>)))
		{
			// Add the command name and pointer, but skip the leading "@yC_".
			P:6("Command_OnScriptInit: Adding %d", entry);
			AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(entry + 4), buffer),
			buffer[0] = ('@' << 24) | ('_' << 16) | ('y' << 08) | ('C' << 00),
			id2 = funcidx(buffer);
			if (id2 != -1) entry = AMX_HEADER_PUBLICS + id2 * 8;
			// Check that the function name is all lower-case.
			for (id2 = 4; buffer{id2}; ++id2)
			{
				if (buffer{id2} != tolower(buffer{id2})) P:E("Commands must be in lower-case in your source code.");
			}
			// Add the command regardless.
			Command_Add(buffer[1], AMX_Read(entry));
			P:6("Command_OnScriptInit: Name %s", unpack(buffer[1]));
		}
		if (funcidx(YSI_gscOPCR) != -1) Command_IncOPCR();
		if (funcidx(YSI_gscOPCP) != -1) Command_IncOPCP();
	}

/**--------------------------------------------------------------------------**\
<summary>_Command_SetPerms</summary>
<param name="f">Function to adjust.</param>
<param name="pa">Player permissions array.</param>
<param name="s">Size of the array.</param>
<param name="x">eXtra data (flags).</param>
<returns>
	-
</returns>
<remarks>
	Passes additional commands data to the new master.
</remarks>
\**--------------------------------------------------------------------------**/

foreign void:_Command_SetPerms(string:f[],pa[],s,x);

global void:_Command_SetPerms(string:f[],pa[],s,x)
{
	#pragma unused x
	new
		id = Command_Find(f);
	if (id != -1)
	{
		memcpy(_:YSI_g_sCommands[id][E_COMMAND_USERS], pa, (bits<MAX_PLAYERS> + 1) * 4, s);
	}
}

/**--------------------------------------------------------------------------**\
<summary>HANDOFF</summary>
<returns>
	-
</returns>
<remarks>
	Passes additional commands data to the new master.
</remarks>
\**--------------------------------------------------------------------------**/

foreign void:_Command_Rebuild();

global void:_Command_Rebuild()
{
	HashMap_Init(YSI_g_sCommandMap, YSI_g_sCommands);
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		if (_Command_IsActive(i))
		{
			HashMap_Add(YSI_g_sCommandMap, Command_Name(i), i);
		}
	}
}

HANDOFF()
{
	P:1("Commands_OnScriptExit <_YCM:p> called");
	// Copy settings.
	DISTRIBUTE(YSI_g_sCommandFlags);
	DISTRIBUTE(YSI_g_sErrorMessages);
	DISTRIBUTE(YSI_g_sDisabledPlayers);
	// This accounts for master IDs.
	DISTRIBUTE(YSI_g_sCommands);
	// Now we've sent over the remaining valid commands, build the hash map.
	_Command_Rebuild();
}

/**--------------------------------------------------------------------------**\
<summary>OnScriptExit</summary>
<returns>
	-
</returns>
<remarks>
	When a script ends, update the status of any new callback hooks.
</remarks>
\**--------------------------------------------------------------------------**/

hook OnScriptExit()
{
	P:1("Commands_OnScriptExit <> called");
	if (funcidx(YSI_gscOPCR) != -1) Command_DecOPCR();
	if (funcidx(YSI_gscOPCP) != -1) Command_DecOPCP();
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Command_IncOPCR</summary>
<returns>
	-
</returns>
<remarks>
	This function, and the three other related ones, increment and decrement the
	number of callbacks known to exist on the server.  If they are 0, there's no
	point trying to call them on errors etc.
</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_IncOPCR();

global void:Command_IncOPCR()
{
	P:2("Command_IncOPCR called");
	YSI_g_sCommandFlags += e_COMM_FLAG_OPCR_ADD;
}

foreign void:Command_DecOPCR();

global void:Command_DecOPCR()
{
	P:2("Command_DecOPCR called");
	YSI_g_sCommandFlags -= e_COMM_FLAG_OPCR_ADD;
}

foreign void:Command_IncOPCP();

global void:Command_IncOPCP()
{
	P:2("Command_IncOPCP called");
	YSI_g_sCommandFlags += e_COMM_FLAG_OPCP_ADD;
}

foreign void:Command_DecOPCP();

global void:Command_DecOPCP()
{
	P:2("Command_DecOPCP called");
	YSI_g_sCommandFlags -= e_COMM_FLAG_OPCP_ADD;
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetEmptySlot</summary>
<returns>
	The first available slot in "YSI_g_sCommands".
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

static stock Command_GetEmptySlot()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		// No name for the command, can't exist.
		if (_Command_IsEmptySlot(i)) return i;
	}
	return COMMAND_NOT_FOUND;
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetID</summary>
<param name="function[]">Function name to find.</param>
<returns>
	The ID of the passed function.
</returns>
<remarks>
	-

native Command_GetID(function[])

</remarks>
\**--------------------------------------------------------------------------**/

foreign Command_GetID(string:function[]);

global Command_GetID(string:function[])
{
	P:2("Command_GetID called: \"%s\"", function);
	return Command_Find(function);
}

/**--------------------------------------------------------------------------**\
<summary>Command_Add</summary>
<param name="cmd[]">The command name to add.</param>
<param name="ptr">The command's pointer.</param>
<param name="id">Where to store the command (default -1 = find).</param>
<returns>
	The command's ID.
</returns>
<remarks>

native Command_Add(funcname[], script);

</remarks>
\**--------------------------------------------------------------------------**/

@foreign Command_Add(string:cmd[], ptr);

@global Command_Add(string:cmd[], ptr)
{
	// The commands all need to be stored packed.
	strpack(cmd, cmd, cellmax);
	P:2("Command_Add: %s, %d", unpack(cmd), ptr);
	new
		id = Command_Find(cmd);
	P:5("Command_Add: found %d", id);
	if (id == COMMAND_NOT_FOUND)
	{
		// Command doesn't already exist, add it.
		id = Command_GetEmptySlot();
		if (id == COMMAND_NOT_FOUND)
		{
			P:E("Could not add command to array.");
			return COMMAND_NOT_FOUND;
		}
		// Save the command's pointer.
		YSI_g_sCommands[id][E_COMMAND_POINTER] = ptr,
		// Add this command to the hash map (does the name too).
		HashMap_Add(YSI_g_sCommandMap, cmd, id),
		// Add all players, or defer to y_groups.
		PA_FastInit(YSI_g_sCommands[id][E_COMMAND_USERS]);
		NO_GROUPS(id)
		{
			PA_Init(YSI_g_sCommands[id][E_COMMAND_USERS], true);
		}
		// Add the calling script as having this command.
		MASTER_SET<id>
	}
	else
	{
		// Add this script to the list of providers.
		MASTER_ADD<id>
	}
	return id;
}

/**--------------------------------------------------------------------------**\
<summary>Command_AddAlt</summary>
<param name="oidx">The function this is an alternate to.</param>
<param name="cmd[]">The new name.</param>
<returns>
	The command's ID.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign Command_AddAlt(oidx, string:cmd[]);

global Command_AddAlt(oidx, string:cmd[])
{
	if (!_Command_IsValid(oidx)) return COMMAND_NOT_FOUND;
	strpack(cmd, cmd, cellmax);
	new
		id = Command_Find(cmd);
	if (id == COMMAND_NOT_FOUND)
	{
		// Command doesn't already exist, add it.
		id = Command_GetEmptySlot();
		if (id == COMMAND_NOT_FOUND)
		{
			P:E("Could not add alt command to array.");
			return COMMAND_NOT_FOUND;
		}
		// Save the command's pointer.
		YSI_g_sCommands[id][E_COMMAND_POINTER] = cellmin | oidx;
		// Add all players, or defer to y_groups.
		PA_FastInit(YSI_g_sCommands[id][E_COMMAND_USERS]);
		NO_GROUPS(id)
		{
			PA_Init(YSI_g_sCommands[id][E_COMMAND_USERS], true);
		}
		// Add this command to the hash map (does the name too).
		HashMap_Add(YSI_g_sCommandMap, cmd, id);
		// Copy the master script information.  Note that this won't be kept up
		// to date with new scripts unfortunately.
		MASTER_COPY<id, oidx>
	}
	return id;
}

/**--------------------------------------------------------------------------**\
<summary>Command_AddAltNamed</summary>
<param name="function[]">The function this is an alternate to.</param>
<param name="altname[]">The new name.</param>
<returns>
	-
</returns>
<remarks>
	Add an alternate command for an existing command.

native Command_AddAltNamed(function[], altname[]);

</remarks>
\**--------------------------------------------------------------------------**/

foreign Command_AddAltNamed(string:function[], string:altname[]);

global Command_AddAltNamed(string:function[], string:altname[])
{
	return Command_AddAlt(Command_Find(function), altname);
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetPlayer</summary>
<param name="command">Command to get for.</param>
<param name="playerid">Player to get.</param>
<returns>
	Can this player use this command?
</returns>
<remarks>

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_GetPlayer(%0,%1) (PA_Get(YSI_g_sCommands[(%0)][E_COMMAND_USERS], (%1)))

foreign bool:Command_GetPlayer(cmd, pid);

global bool:Command_GetPlayer(cmd, pid)
{
	if (_Command_IsValid(cmd) && 0 <= pid < MAX_PLAYERS) return _Command_GetPlayer(cmd, pid);
	return false;
}
/**--------------------------------------------------------------------------**\
<summary>Command_GetPlayerNamed</summary>
<param name="funcname[]">Command to get for.</param>
<param name="playerid">Player to get.</param>
<returns>
	-
</returns>
<remarks>
	Like Command_GetPlayer but for a function name.

native bool:Command_GetPlayerNamed(funcname[], playerid);

</remarks>
\**--------------------------------------------------------------------------**/

foreign bool:Command_GetPlayerNamed(string:func[], playerid);

global bool:Command_GetPlayerNamed(string:func[], playerid)
{
	return Command_GetPlayer(Command_Find(func), playerid);
}

/**--------------------------------------------------------------------------**\
<summary>Command_SetPlayer</summary>
<param name="command">Command to set for.</param>
<param name="playerid">Player to set.</param>
<param name="bool:set">Wether or not this player can use this command.</param>
<returns>
	-
</returns>
<remarks>

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_SetPlayer(c, p, bool:s);

global void:Command_SetPlayer(c, p, bool:s)
{
	P:2("Command_SetPlayer called: %i, %i, %i", c, p, s);
	if (_Command_IsValid(c) && 0 <= p < MAX_PLAYERS) PA_Set(YSI_g_sCommands[c][E_COMMAND_USERS], p, s);
}

/**--------------------------------------------------------------------------**\
<summary>Command_SetPlayerNamed</summary>
<param name="funcname[]">Command to set for.</param>
<param name="playerid">Player to set.</param>
<param name="set">Wether or not this player can use this command.</param>
<returns>
	-
</returns>
<remarks>
	Like Command_SetPlayer but for a function name.

native bool:Command_SetPlayerNamed(funcname[], playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_SetPlayerNamed(string:f[],p,bool:s);

global void:Command_SetPlayerNamed(string:f[],p,bool:s)
{
	Command_SetPlayer(Command_Find(f), p, s);
}

/**--------------------------------------------------------------------------**\
<summary>Command_Remove</summary>
<param name="func">The slot of the command to remove.</param>
<returns>
	-
</returns>
<remarks>

native Command_Remove(func);

</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_Remove(func);

global void:Command_Remove(func)
{
	// Annoyingly, this is actually better with "HashMap_RemoveKey", but then we
	// don't have the ID for later use.
	if (HashMap_RemoveValue(YSI_g_sCommandMap, func))
	{
		YSI_g_sCommands[func][E_COMMAND_POINTER] = -1;
	}
}

foreign void:Command_RemoveNamed(string:func[]);

global void:Command_RemoveNamed(string:func[])
{
	Command_Remove(Command_Find(func));
}

/**--------------------------------------------------------------------------**\
<summary>Command_OnPlayerCommandText</summary>
<param name="playerid">Player who typed a command.</param>
<param name="cmdtext[]">What they typed.</param>
<returns>
	0 - Could not process the command.
	1 - Called the command.
</returns>
<remarks>
	The core of the command processor.  Now vsatly simplified.
	
	This function first finds the command in our hash map.  If it exists, it
	checks if the player can use it.  If they can, it checks if it is only in
	the current script.  If it is it calls it directly, if it isn't it calls it
	using "CallRemoteFunction", which takes in to account master states in
	multiple scripts and the special master 23, which calls it in only one
	other script.
</remarks>
\**--------------------------------------------------------------------------**/

mhook OnPlayerCommandText(playerid, cmdtext[])
{
	return Command_ReProcess(playerid, cmdtext, 0);
}

/**--------------------------------------------------------------------------**\
<summary>Command_ReProcess</summary>
<param name="playerid">Player who entered the command.</param>
<param name="cmdtext[]">Text entered.</param>
<param name="help">Called from the help commmand or OnPlayerCommandText.</param>
<returns>
	true - success or hidden fail.
	false - fail.
</returns>
<remarks>
	This is a complete copy of "OnPlayerCommandText" for speed.
</remarks>
\**--------------------------------------------------------------------------**/

foreign Command_ReProcess(p,string:c[],h);

global Command_ReProcess(p,string:c[],h)
{
	static
		e_COMMAND_ERRORS:sErr;
	#if !defined Y_COMMANDS_NO_IPC
		if (!IsPlayerConnected(p)) return Command_OnReceived(NO_PLAYER, p, c);
	#endif
	if (PA_Get(YSI_g_sDisabledPlayers, p)) return Command_OnReceived(DISABLED, p, c);
	P:1("Commands_OnPlayerCommandText called: %d %s", p, c);
	static
		sCmd[64] = "@yC_",
		sPos,
		sIdx,
		sHash;
	// Get the hashed version of the decoded string.
	sPos = Puny_EncodeHash(sCmd[4], c[1], sHash, .delimiter = '@') + 1;
	while (c[sPos] == ' ') ++sPos;
	// Find the command in the array.
	sIdx = HashMap_GetWithHash(YSI_g_sCommandMap, sCmd[4], sHash);
	P:5("Commands_OnPlayerCommandText: %s, %d, %d, %d", sCmd[4], sPos, sHash, sIdx);
	if (sIdx == COMMAND_NOT_FOUND) return Command_OnReceived(UNDEFINED, p, c);
	// Can the player use this command?
	if (_Command_GetPlayer(sIdx, p))
	{
		if (!Command_OnReceived(OK, p, c)) return 0;
		// Find the true version of the command (alts etc).
		_Command_GetReal(sHash, sIdx, sCmd[4]);
		#if YSIM_HAS_MASTER
			if (MASTER_EXCLUSIVE<sIdx>)
		#endif
			{
				// In this script.
				//sIdx = YSI_g_sCommands[sIdx][E_COMMAND_POINTER];
				#emit PUSH.S      h
				#emit LOAD.pri    sPos
				#emit LOAD.S.alt  c
				#emit IDXADDR
				#emit PUSH.pri
				#emit PUSH.S      p
				#emit PUSH.C      12
				#emit LCTRL       6
				#emit ADD.C       28
				#emit PUSH.pri
				#emit LOAD.pri    sHash
				#emit SCTRL       6
				#emit STOR.pri    sIdx
				P:5("Command_ReProces: Result = %d %d %d", sIdx, Command_Error(p, e_COMMAND_ERRORS:sIdx), _:COMMAND_OK);
			}
		#if YSIM_HAS_MASTER
			else
			{
				// This is in another script, or multiple scripts.
				// Call the command in another script.  If no particular script
				// is set up as the "master", call it in the first one found...
				if (c[sPos]) CallRemoteFunction(sCmd, YSI_gscISII, p, c[sPos], h, Cell_GetLowestBit(_:MASTER_GET<sIdx>));
				else CallRemoteFunction(sCmd, YSI_gscISII, p, NULL, h, Cell_GetLowestBit(_:MASTER_GET<sIdx>));
				sIdx = getproperty(8, YSIM_RETURN);
			}
		#endif
		if (YSI_g_sCommandFlags & e_COMM_FLAG_OPCP) sIdx = CallRemoteFunction(YSI_gscOPCP, YSI_gscISI, p, c, sIdx);
		return Command_Error(p, e_COMMAND_ERRORS:sIdx);
	}
	return Command_OnReceived(DENIED, p, c);
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetDisplay</summary>
<param name="f">Command to get the real name of.</param>
<param name="p">Player to get the name for.</param>
<returns>
	The name of a command for a single player.
</returns>
<remarks>
	-

native Command_GetDisplay(funcid, playerid);

</remarks>
\**--------------------------------------------------------------------------**/

foreign string:Command_GetDisplay(funcid, playerid);

global string:Command_GetDisplay(funcid, playerid)
{
	YSI_g_sReturnBuffer[0] = '\0';
	if (_Command_IsValid(funcid) && 0 <= playerid < MAX_PLAYERS)
	{
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		// Check if they can use the original version.
		if (YSI_g_sCommands[funcid][E_COMMAND_USERS][slot] & mask)
		{
			strunpack(YSI_g_sReturnBuffer, Command_Name(funcid));
			return YSI_g_sReturnBuffer;
		}
		funcid = YSI_g_sCommands[funcid][E_COMMAND_POINTER];
		// Search for a command pointing to that command which the player can use.
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (YSI_g_sCommands[i][E_COMMAND_POINTER] == funcid && (YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask))
			{
				strunpack(YSI_g_sReturnBuffer, Command_Name(i));
				return YSI_g_sReturnBuffer;
			}
		}
	}
	return YSI_g_sReturnBuffer;
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetDisplayNamed</summary>
<param name="f[]">Command to get the real name of.</param>
<param name="p">Player to get the name for.</param>
<returns>
	The name of a named function for one player.
</returns>
<remarks>
	Remote function call for Command_GetDisplayNameNamed - avoids needing to
	expose users to the master system's odd way of returning strings.  This is
	the only part I've not yet fixed up to be nice and hidden.

native string:Command_GetDisplayNamed(string:funcid[], playerid);

</remarks>
\**--------------------------------------------------------------------------**/

foreign string:Command_GetDisplayNamed(string:func[], playerid);

global string:Command_GetDisplayNamed(string:func[], playerid)
{
	return Command_GetDisplay(Command_Find(func), playerid);
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetPlayerCommandCount</summary>
<param name="playerid">Player to count for.</param>
<returns>
	-
</returns>
<remarks>
	Gets the number of comamnds this player can use.

native Command_GetPlayerCommandCount(playerid);

</remarks>
\**--------------------------------------------------------------------------**/

foreign Command_GetPlayerCommandCount(playerid);

global Command_GetPlayerCommandCount(playerid)
{
	P:2("Command_GetPlayerCommandCount called: %i", playerid);
	new
		slot = PA_Slot(playerid),
		Bit:mask = PA_Mask(playerid),
		count = 0;
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		if (YSI_g_sCommands[i][E_COMMAND_NAME][0] && YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask)
		{
			++count;
		}
	}
	return count;
}

/**--------------------------------------------------------------------------**\
<summary>Command_GetNext</summary>
<param name="index">Index of the next command for this player.</param>
<param name="playerid">Player to get the name for.</param>
<returns>
	The name of a command for a single player.
</returns>
<remarks>
	-

native Command_GetNext(index, playerid);

</remarks>
\**--------------------------------------------------------------------------**/

foreign string:Command_GetNext(index, playerid);

global string:Command_GetNext(index, playerid)
{
	P:2("Command_GetNext called: %i, %i", index, playerid);
	YSI_g_sReturnBuffer[0] = '\0';
	if (0 <= index < MAX_COMMANDS)
	{
		// Don't recalculate this every loop.
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (YSI_g_sCommands[i][E_COMMAND_NAME][0] && YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask)
			{
				// Skip already displayed ones.
				if (index)
				{
					--index;
				}
				else
				{
					strunpack(YSI_g_sReturnBuffer, Command_Name(i));
					return YSI_g_sReturnBuffer;
				}
			}
		}
	}
	return YSI_g_sReturnBuffer;
}

