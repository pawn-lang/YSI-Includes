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
	static
		sFailRet[_:_E_COMMAND_PAD_0 - _:E_COMMAND_NAME];
	if (_Command_IsValid(f)) return Command_Name(f);
	return sFailRet;
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
		for (new func = 0; func != MAX_COMMANDS; ++func)
		{
			YSI_g_sCommands[func][E_COMMAND_POINTER] = -1;
		}
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
	-

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

#define _Command_GetPlayer(%0,%1) (PA_Get(YSI_g_sCommands[(%0)][E_COMMAND_USERS], (%1)))

foreign bool:Command_GetPlayer(cmd, pid);

global bool:Command_GetPlayer(cmd, pid)
{
	if (_Command_IsValid(cmd) && IsPlayerConnected(pid)) return _Command_GetPlayer(cmd, pid);
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
	-

native bool:Command_SetPlayer(command, playerid, bool:set);

</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Command_SetPlayer(c, p, bool:s);

global void:Command_SetPlayer(c, p, bool:s)
{
	P:2("Command_SetPlayer called: %i, %i, %i", c, p, s);
	if (_Command_IsValid(c) && IsPlayerConnected(p)) PA_Set(YSI_g_sCommands[c][E_COMMAND_USERS], p, s);
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
	Command_SetPlayer(Command_Find(func), p, s);
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
	Command_Remove(Command_Find(func), func);
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
	P:1("Commands_OnPlayerCommandText called: %d %s", playerid, cmdtext);
	CallRemoteFunction("OnPlayerCommandReceived", "isi", playerid, cmdtext, 0);
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
		#if YSIM_HAS_MASTER
			static
				sMasters;
			sMasters = _:MASTER_GET<sIdx>;
			// This is in another script, or multiple scripts.
			if (sMasters)
			{
				// Call the command in another script.  If no particular script
				// is set up as the "master", call it in the first one found...
				if (cmdtext[sPos]) sIdx = CallRemoteFunction(sCmd, "isii", playerid, cmdtext[sPos], 0, Cell_GetLowestBit(sMasters));
				else sIdx = CallRemoteFunction(sCmd, "isii", playerid, NULL, 0, Cell_GetLowestBit(sMasters));
				CallRemoteFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, sIdx);
				return sIdx;
			}
		#endif
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
			CallRemoteFunction("OnPlayerCommandPerformed", "isii", playerid, cmdtext, sIdx, 0);
			return sIdx;
	}
	return 0;
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
	P:1("Commands_OnPlayerCommandText called: %d %s", p, c);
	CallRemoteFunction("OnPlayerCommandReceived", "isi", p, c, h);
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
	if (sIdx == COMMAND_NOT_FOUND) return 0;
	// Can the player use this command?
	if (_Command_GetPlayer(sIdx, p))
	{
		#if YSIM_HAS_MASTER
			static
				sMasters;
			sMasters = _:MASTER_GET<sIdx>;
			// This is in another script, or multiple scripts.
			if (sMasters)
			{
				// Call the command in another script.  If no particular script
				// is set up as the "master", call it in the first one found...
				if (c[sPos]) sIdx = CallRemoteFunction(sCmd, "isii", p, c[sPos], h, Cell_GetLowestBit(sMasters));
				else sIdx = CallRemoteFunction(sCmd, "isii", p, NULL, h, Cell_GetLowestBit(sMasters));
				CallRemoteFunction("OnPlayerCommandPerformed", "isi", p, c, sIdx);
				return sIdx;
			}
		#endif
			// In this script.
			sIdx = YSI_g_sCommands[sIdx][E_COMMAND_POINTER];
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
			#emit LOAD.pri    sIdx
			#emit SCTRL       6
			#emit STOR.pri    sIdx
			CallRemoteFunction("OnPlayerCommandPerformed", "isii", p, c, sIdx, h);
			return sIdx;
	}
	return 0;
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
	new
		buffer[YSI_MAX_STRING] = "";
	if (_Command_IsValid(funcid) && IsPlayerConnected(playerid))
	{
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		// Check if they can use the original version.
		if (YSI_g_sCommands[funcid][E_COMMANDS_PLAYERS][slot] & mask)
		{
			strunpack(buffer, Command_Name(funcid));
			return buffer;
		}
		funcid = YSI_g_sCommands[funcid][E_COMMAND_POINTER];
		// Search for a command pointing to that command which the player can use.
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (Command_GetPointer(i) == funcid && (YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask))
			{
				strunpack(buffer, Command_Name(i));
				return buffer;
			}
		}
	}
	return buffer;
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
		if (YSI_g_sCommands[i][E_COMMAND_NAME][0] && YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask)
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
	new
		buffer[YSI_MAX_STRING] = "";
	if (0 <= index < MAX_COMMANDS)
	{
		// Don't recalculate this every loop.
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (YSI_g_sCommands[i][E_COMMAND_NAME][0] && YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask)
			{
				// Skip already displayed ones.
				if (index)
				{
					--index;
				}
				else
				{
					strunpack(buffer, Command_Name(i));
					return buffer;
				}
			}
		}
	}
	return buffer;
}
