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

static stock
	// Quickly reference and store commands by name.
	HashMap:YSI_g_sCommandMap<MAX_COMMANDS>,
	YSI_g_sCommands[MAX_COMMANDS][E_COMMAND];

// Store which script(s) own which commands.
MASTER_DATA<MAX_COMMANDS>

// "YCMD:" macros.  The true core is "RC:", which is in "y_master".
#define _YCMD_0:_YCMD_1:_YCMD_2:%0(%1[]%2) RC:%0(%1[]%2)
#define _YCMD_1:_YCMD_2:%0, Command_GetID(#%0),
#define _YCMD_2:%0)  Command_GetID(#%0))
#define @YCMD:%0;  Command_TouchNamed(#%0);

#define YCMD: _YCMD_0:_YCMD_1:_YCMD_2:

// ZCMD compatibility.
#define CMD:%0(%1) RC:%0(%1,__help)if(__help)return 0;else
#define COMMAND CMD

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

#define _Command_IsValid(%0) ((0 <= (%0) < MAX_COMMANDS) && YSI_g_sCommands[(%0)][E_COMMAND_NAME][0])

foreign Command_IsValid(cmd);

global Command_IsValid(cmd)
{
	return _Command_IsValid(cmd);
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

hook OnScriptInit()
{
	P:1("Command_OnScriptInit called");
	#if YSIM_NOT_CLIENT
		HashMap_Init(YSI_g_sCommandMap, YSI_g_sCommands);
	#endif
	new
		entry,
		buffer[32 char],
		idx;
	P:5("Command_OnScriptInit: Pre-loop");
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yC_>)))
	{
		// Add the command name and pointer, but skip the leading "@yC_".
		P:6("Command_OnScriptInit: Adding %d", entry);
		AMX_ReadString(AMX_BASE_ADDRESS + AMX_Read(entry + 4), buffer);
		P:6("Command_OnScriptInit: Name %s", unpack(buffer[1]));
		Command_Add(buffer[1], AMX_Read(entry));
	}
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
		if (!YSI_g_sCommands[i][E_COMMAND_NAME]) return i;
	}
	return COMMAND_NOT_FOUND;
}

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
		YSI_g_sCommands[id][E_COMMAND_POINTER] = ptr;
		// Add all players, or defer to y_groups.
		PA_FastInit(YSI_g_sCommands[id][E_COMMAND_USERS]);
		NO_GROUPS(id)
		{
			PA_Init(YSI_g_sCommands[id][E_COMMAND_USERS], true);
		}
		// Add this command to the hash map (does the name too).
		HashMap_Add(YSI_g_sCommandMap, cmd, id);
		// Add the calling script as having this command.
		if (Master_Caller() == Master_ID()) MASTER_RESET<id>
		else MASTER_SET<id>
	}
	else
	{
		// Add this script to the list of providers.
		if (MASTER_GET<id>) MASTER_ADD<id>
		else YSI_g_sMasterData[_:id] = Bit:((1 << Master_Caller()) | (1 << Master_ID()));
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
		YSI_g_sCommands[id][E_COMMAND_POINTER] = YSI_g_sCommands[oidx][E_COMMAND_POINTER];
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
<summary>Command_GetPlayer</summary>
<param name="command">Command to get for.</param>
<param name="playerid">Player to get.</param>
<returns>
	Can this player use this command?
</returns>
<remarks>
	-

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

//#define _Command_GetPlayer(%0,%1) (PA_Get(YSI_g_sCommands[(%0)][E_COMMAND_USERS]. (%1)))
#define _Command_GetPlayer(%0,%1) (PA_Get(YSI_g_sCommands[(%0)][E_COMMAND_USERS], (%1)))

foreign bool:Command_GetPlayer(cmd, pid);

global bool:Command_GetPlayer(cmd, pid)
{
	if (_Command_IsValid(cmd) && IsPlayerConnected(pid)) return _Command_GetPlayer(cmd, pid);
	return false;
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
	-

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_SetPlayer(c, p, bool:s);

global void:Command_SetPlayer(c, p, bool:s)
{
	P:2("Command_SetPlayer called: %i, %i, %i", c, p, s);
	if (0 <= c < MAX_COMMANDS)
	{
		PA_Set(YSI_g_sCommands[c][E_COMMAND_USERS], p, s);
	}
}

mhook OnPlayerCommandText(playerid, cmdtext[])
{
	P:1("Commands_OnPlayerCommandText called: %d %s", playerid, cmdtext);
	CallRemoteFunction("OnPlayerCommandReceived", "is", playerid, cmdtext);
	static
		sCmd[64] = "@yC_",
		sPos,
		sIdx,
		sHash;
	// Get the hashed version of the decoded string.
	sPos = Puny_EncodeHash(sCmd[4], cmdtext[1], sHash, .delimiter = '@') + 1;
	while (cmdtext[sPos] == ' ') ++sPos;
	// Find the command in the array.
	sIdx = HashMap_GetWithHash(YSI_g_sCommandMap, sCmd[4], sHash);
	P:5("Commands_OnPlayerCommandText: %s, %d, %d, %d", sCmd[4], sPos, sHash, sIdx);
	if (sIdx == COMMAND_NOT_FOUND) return 0;
	// Can the player use this command?
	if (_Command_GetPlayer(sIdx, playerid))
	{
		static
			sMasters;
		sMasters = _:MASTER_GET<sIdx>;
		// This is in another script.
		if (sMasters)
		{
			// Call the command in another script.  If no particular script is
			// set up as the "master", call it in the first one found...
			if (cmdtext[sPos]) sIdx = CallRemoteFunction(sCmd, "isii", playerid, cmdtext[sPos], 0, Cell_GetLowestBit(sMasters));
			else sIdx = CallRemoteFunction(sCmd, "isii", playerid, NULL, 0, Cell_GetLowestBit(sMasters));
			CallRemoteFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, sIdx);
		}
		else
		{
			// In this script.
			sIdx = YSI_g_sCommands[sIdx][E_COMMAND_POINTER];
			#emit PUSH.C      0
			#emit LOAD.pri    sPos
			#emit LOAD.S.alt  cmdtext
			#emit IDXADDR
			#emit PUSH.pri
			#emit PUSH.S      playerid
			#emit PUSH.C      12
			#emit LCTRL       6
			#emit ADD.C       28
			#emit PUSH.pri
			#emit LOAD.pri    sIdx
			#emit SCTRL       6
			#emit STOR.pri    sIdx
			CallRemoteFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, sIdx);
		}
	}
	return 0;
}
