/*----------------------------------------------------------------------------*\
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
	0.1.4
Changelog:
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
		Command_Add - Adds a command to the array for processing.
		Command_Remove - Removes a command.
		Command_Name - Gets the name of a command in a property.
	Core:
		Command_Process - Called from OnPlayerCommandText to process entered commands.
		Command_Parse - Sorts added commands into a binary tree.
		Command_Hash - Hashes a word for command hashing.
		Command_ProcRem - Processes a help command in the master script.
	Stock:
		Command_SetDisconnectReturn - Sets the return value for unconnected players.
		Command_UseShortCuts - Toggles use of per-player command shortcuts.
		Command_SetDeniedReturn - Sets the return value for denied use commands.
		Command_UseDeniedMessage - Toggles the use of an error message for denied.
		Command_SetIllegalReturn - Sets the return value for illegal characters.
		Command_UseAltNames - Toggles the use of ini defined alternate names.
		Command_UsePrefix - Toggles the use of a global prefix.
		Command_UseSpace - Toggles the use of a space between prefix and command.
		Command_SetAltName - Sets the alternate name of a function.
		Command_SetPrefix - Sets the pfexix to be typed.
		Comamnd_SetPlayerUse - Sets wether or not a player can use a command.
		Comamnd_SetPlayerUseByID - Sets wether or not a player can use a command.
		Command_FindByName - Finds a command in a possibly sorted list.
	Static:
		Command_FindFast - Finds a function by binary search of function name.
		Command_FindAlt - Finds a function by binary search of alternate name.
		Command_SetSorted - Marks the binary tree as sorted.
		Command_FindSlow - Finds a function by linear search of function name.
		Command_Find - Finds a function from entered text.
		Command_Prefix - Checks the entered prefix.
		Command_ReturnName - Returns the name of a function.
		Command_GetPlayerCount - Gets the number of commands a player can use.
	Inline:
		Command_Command - Not used, constructor.
		Command_IsCleared - Checks a player is cleared to use a command.
		Command_DisconnectReturn - Gets the return value for disconnected players.
		Command_UsingShortCuts - Checks if short cuts are being used.
		Command_DeniedReturn - Gets the return value for prohibited commands.
		Command_IllegalReturn - Gets the return value for invalid characters.
		Command_DeniedMessage - Checks if a level error message should be sent.
		Command_IsSorted - Checks if the binary tree has been initialised.
		Command_UsingAltNames - Checks if alt names are being used.
		Command_UsingPrefix - Checks if the prefix is being used.
		Command_UsingSpace - Checks if the space option is being used.
		Command_CallFunction - Calls the required function.
		ycmd - Adds a command to the system.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_COMMAND_LENGTH - The maximum length of a command string.
	COMMAND_NOT_FOUND - Indicates that a searched for string is not a function.
Enums:
	e_COMM_FLAG - Bit mappings for command options.
	E_COMMANDS - Structure of the array holding the string data.
Macros:
	Command_(%1) - Forwards and declares a standard command for calling.
	ycmd(%1) - Adds a command to the array (wrapper for Command_Add).
Tags:
	e_COMM_FLAG - Flag type.
Variables:
	Global:
		-
	Static:
		YSI_g_sCommands - Holds all the textual data of the commands.
		YSI_g_sSearchTree - Tree of hashes for function names.
		YSI_g_sAltTree - Tree of hashes for alternate names.
		YSI_g_sPrefix - The command prefix.
		YSI_g_sPrefixLength - Length of the prefix.
		YSI_g_sCommandIndex - Pointer to the next free index in the function array.
		YSI_g_sAltCount - The number of commands with altnames.
		YSI_g_sCommandFlags - Bit array of command options.
Commands:
	commands - Lists all commands available to you.
Compile options:
	COMMAND_SENSITIVE - Make commands case sensitive.
	COMMAND_ACCURATE - Can use '@' in command names.
	MAX_COMMANDS - The maximum number of commands which can be used.
\*----------------------------------------------------------------------------*/

#if defined _INC_y_text
	#error y_commands must be included before y_text
#endif

#include "internal\y_version"

#if !defined MAX_COMMANDS
	#define MAX_COMMANDS                (1024)
#endif

#define _GROUP_MAKE_NAME_CMD<%0...%1>   %0Command%1
#define _GROUP_MAKE_LIMIT_CMD           MAX_COMMANDS

#define YSIM_U_DISABLE
#include "y_master"
#include "y_groups"

#include "y_debug"
#include "y_hooks"

#include "y_bintree"
#include "y_amx"
#include "y_playerarray"
#include "y_utils"

#include "internal\y_natives"

// Define the CMD: macro.  This uses the prefix "@yC_" as it's 32 bits so allows
// for fast command string searching in the publics table and makes the commands
// public without the need for the public keyword.
/*#if YSIM_HAS_MASTER
	#if _YSIM_IS_CLIENT
		#define YCMD:%1(%2) static stock @_yC%1(%2)
	#else
		#if _YSIM_IS_SERVER
			#define YCMD:%1(%2) @yC_%1(a,b[],c);@yC_%1(a,b[],c)U@(8,YSIM_RETURN,@_yC%1(a,b,c));static @_yC%1(%2)
		#else
			#define YCMD:%1(%2) @yC_%1(a,b[],c);@yC_%1(a,b[],c)<>{}@yC_%1(a,b[],c)<_YCM:y>U@(8,YSIM_RETURN,@_yC%1(a,b,c));static @_yC%1(%2)
		#endif
	#endif
#else
	#define YCMD:%1(%2) @yC_%1(%2);@yC_%1(%2)
#endif*/

//#define YCMD:%0(%1) RC:%0(%1)

#define _YCMD_0:_YCMD_1:_YCMD_2:%0(%1[]%2) RC:%0(%1[]%2)
#define _YCMD_1:_YCMD_2:%0, Command_GetID(#%0),
#define _YCMD_2:%0)  Command_GetID(#%0))
#define @YCMD:%0;  Command_TouchNamed(#%0);

#define YCMD: _YCMD_0:_YCMD_1:_YCMD_2:

// ZCMD compatibility.
#define CMD:%0(%1) RC:%0(%1,__help)if(__help)return 0;else
#define COMMAND CMD

// This is opposite AMX_FastString as that's in C, not packed, order.
#define Command_FastString(%1,%2,%3,%4) \
	(((%1)<<24)|((%2)<<16)|((%3)<<8)|((%4)<<0))

#define MAX_COMMAND_LENGTH              (32)

#define COMMAND_NOT_FOUND               (-1)

#if defined COMMAND_SENSITIVE
	#define TOLOWER(%0) (%0)
	#define COMMAND_END_CMP (0)
#else
	//#if defined COMMAND_ACCURATE
	//	#define TOLOWER(%0) ((%0) | 0x20)
	//	#define COMMAND_END_CMP (0x20)
	//#else
		#define TOLOWER(%0) tolower(%0)
		#define COMMAND_END_CMP (0)
	//#endif
#endif

// Don't forget the AMX_FastString below if you change this.
#define COMMAND_FUNCTION_PREFIX         (Command_FastString('@', 'y', 'C', '_'))

// Reset both of these when you remove a command.
#define _Command_IsValid(%0) ((Command_GetPointer(%0)==(%0))||(YSI_g_sCommands[(%0)][E_COMMANDS_MASTERS]==-1))
#define Command_IsValid(%0) ((0<=(%0)<MAX_COMMANDS)&&_Command_IsValid(%0))

enum e_COMM_FLAG (<<= 1)
{
	e_COMM_FLAG_PROVIDER = 0x000000FF,
	e_COMM_FLAG_SORTED = 0x00000100,
	e_COMM_FLAG_PERMISSION_WARN,
	e_COMM_FLAG_USE_ALTNAMES,
	e_COMM_FLAG_PERMISSION_RET,
	e_COMM_FLAG_USE_PREFIX,
	e_COMM_FLAG_USE_SPACE,
	e_COMM_FLAG_USE_SHORTCUTS,
	e_COMM_FLAG_DISCONNECT,
	e_COMM_FLAG_ILLEGAL,
	e_COMM_FLAG_COLLISION,
	e_COMM_FLAG_UNKNOWN,
	e_COMM_FLAG_MULPRO,
	// Can't easilly add more flags now...
	e_COMM_FLAG_OPCP = 0x07C00000, // 0b00000111110..0
	e_COMM_FLAG_OPCP_ADD = 0x00400000, // Low bit of above flag.
	e_COMM_FLAG_OPCR = 0xF8000000, // 0b11111000000..0
	e_COMM_FLAG_OPCR_ADD = 0x08000000  // Low bit of above flag.
}

enum E_COMMANDS
{
	E_COMMANDS_FUNCTION[MAX_COMMAND_LENGTH char],
	PlayerArray:E_COMMANDS_PLAYERS<MAX_PLAYERS>,
	#if YSIM_HAS_MASTER
		E_COMMANDS_MASTERS,
	#endif
	E_COMMANDS_FUNC_POINTER
	//E_COMMANDS_AMX_ADDRESS,
}

static stock
	#if YSIM_HAS_MASTER
		YSI_g_sPlayerProvider[MAX_PLAYERS char] = {-1, ...},
	#endif
	YSI_g_sCommands[MAX_COMMANDS][E_COMMANDS],
	BinaryTree:YSI_g_sSearchTree<MAX_COMMANDS>,
	e_COMM_FLAG:YSI_g_sCommandFlags = e_COMM_FLAG:0xFF,
	YSI_g_sCommandIndex,
	YSI_g_sCommandCount;

/*----------------------------------------------------------------------------*\
Function:
	Command_Name
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the name of a function from the array.
\*----------------------------------------------------------------------------*/

#define Command_Name(%1) \
	(YSI_g_sCommands[(%1)][E_COMMANDS_FUNCTION][1])

/*----------------------------------------------------------------------------*\
Function:
	Command_GetFuncName
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the full function name for a slot - note that this may not be the right
	function if this slot points to another one.
\*----------------------------------------------------------------------------*/

#define Command_GetFuncName(%1) \
	(YSI_g_sCommands[(%1)][E_COMMANDS_FUNCTION])

/*----------------------------------------------------------------------------*\
Function:
	Command_GetPointer
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the pointer for a function from the array.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	#define Command_GetPointer(%1) \
		(YSI_g_sCommands[(%1)][E_COMMANDS_FUNC_POINTER]&0x00FFFFFF)
#else
	#define Command_GetPointer(%1) \
		(YSI_g_sCommands[(%1)][E_COMMANDS_FUNC_POINTER])
#endif
/*----------------------------------------------------------------------------*\
Function:
	Command_GetProvider
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the unique script in which this version of the command is.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	#define Command_Provider(%1) \
		(YSI_g_sCommands[(%1)][E_COMMANDS_FUNC_POINTER]>>>24)
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_GetProvider
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the unique script in which this version of the command is.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	#define Command_DefaultProvider() \
		(YSI_g_sCommandFlags & e_COMM_FLAG_PROVIDER)
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_GetFunction
Params:
	index - Index of the command to operate on.
Return:
	-
Notes:
	Gets the real function for this slot.
\*----------------------------------------------------------------------------*/

#define Command_GetFunction(%1) \
	(Command_GetFuncName(Command_GetPointer((%1))))

/*----------------------------------------------------------------------------*\
Function:
	Command_CheckPlayer
Params:
	index - Index of the command to operate on.
	playerid - The player to check for.
Return:
	-
Notes:
	Gets wether a player can use a command.
\*----------------------------------------------------------------------------*/

#define Command_CheckPlayer(%1,%2) \
	(YSI_g_sCommands[(%1)][E_COMMANDS_PLAYERS][Bit_Slot(%2)+1]&Bit_Mask(%2))
	//(PA=([E_COMMANDS_PLAYERS], (%2)))
	//(Bit_Get(YSI_g_sCommands[(%1)][E_COMMANDS_PLAYERS], (%2)))

/*----------------------------------------------------------------------------*\
Function:
	Command_DeniedReturn
Params:
	-
Return:
	e_COMM_FLAG_PERMISSION_RET
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_DeniedReturn() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_PERMISSION_RET)

/*----------------------------------------------------------------------------*\
Function:
	Command_SetDeniedReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_SetDeniedReturn(bool:set);

global void:Command_SetDeniedReturn(bool:set)
{
	P:2("Command_SetDeniedReturn called: %i", bool:set);
	if (set)
	{
		YSI_g_sCommandFlags |= e_COMM_FLAG_PERMISSION_RET;
	}
	else
	{
		YSI_g_sCommandFlags &= ~e_COMM_FLAG_PERMISSION_RET;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_SetProvider
Params:
	p - Script.
Return:
	-
Notes:
	Set the current provider to use for all commands being added.  Basically
	allows us to have the same command name in different scripts and have them
	do different things, with different players targetting different ones.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	foreign void:Command_SetProvider(p);
	
	global void:Command_SetProvider(p)
	{
		P:2("Command_SetProvider called: %i", p);
		YSI_g_sCommandFlags = (YSI_g_sCommandFlags & ~e_COMM_FLAG_PROVIDER) | (e_COMM_FLAG:p & e_COMM_FLAG_PROVIDER) | e_COMM_FLAG_MULPRO;
		//return 1;
	}
	
	foreign Command_GetProvider();
	
	global Command_GetProvider()
	{
		P:2("Command_GetProvider called");
		/*YSI_g_sCommandFlags = (YSI_g_sCommandFlags & ~e_COMM_FLAG_PROVIDER) | (e_COMM_FLAG:p & e_COMM_FLAG_PROVIDER) 
		if (YSI_g_sCommandFlags & e_COMM_FLAG_MULPRO)
		{
			return _:(YSI_g_sCommandFlags & (YSI_g_sCommandFlags & ~e_COMM_FLAG_PROVIDER));
		}
		else
		{
		}*/
		// Poorely named, gets the current provider.
		return _:Command_DefaultProvider();
	}
	
	foreign void:Command_SetPlayerProvider(playerid,p);
	
	global void:Command_SetPlayerProvider(playerid,p)
	{
		P:2("Command_SetPlayerProvider called: %i, %i", playerid, p);
		if (0 <= playerid < MAX_PLAYERS)
		{
			YSI_g_sPlayerProvider{playerid} = p & 0xFF;
		}
		//return 1;
	}
	
	foreign Command_GetPlayerProvider(playerid);
	
	global Command_GetPlayerProvider(playerid)
	{
		P:2("Command_GetPlayerProvider called: %i", playerid);
		return YSI_g_sPlayerProvider{playerid};
	}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_GetDeniedReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Command_GetDeniedReturn();

global bool:Command_GetDeniedReturn()
{
	P:2("bool:Command_GetDeniedReturn called");
	return bool:Command_DeniedReturn();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_HasCollisions
Params:
	-
Return:
	e_COMM_FLAG_COLLISION
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_HasCollisions() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_COLLISION)

/*----------------------------------------------------------------------------*\
Function:
	Command_HasCollisions
Params:
	-
Return:
	e_COMM_FLAG_MULPRO
Notes:
	-
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	#define Command_HasMultipleProviders() \
		(YSI_g_sCommandFlags & e_COMM_FLAG_MULPRO)
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_SetCollisions
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_SetCollisions() \
	YSI_g_sCommandFlags |= e_COMM_FLAG_COLLISION

/*----------------------------------------------------------------------------*\
Function:
	Command_IllegalReturn
Params:
	-
Return:
	e_COMM_FLAG_ILLEGAL
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_IllegalReturn() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_ILLEGAL)

/*----------------------------------------------------------------------------*\
Function:
	Command_SetIllegalReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_SetIllegalReturn(bool:set);

global void:Command_SetIllegalReturn(bool:set)
{
	P:2("Command_SetIllegalReturn called: %i", bool:set);
	if (set)
	{
		YSI_g_sCommandFlags |= e_COMM_FLAG_ILLEGAL;
	}
	else
	{
		YSI_g_sCommandFlags &= ~e_COMM_FLAG_ILLEGAL;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetIllegalReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Command_GetIllegalReturn();

global bool:Command_GetIllegalReturn()
{
	P:2("bool:Command_GetIllegalReturn called");
	return bool:Command_IllegalReturn();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_IllegalReturn
Params:
	-
Return:
	e_COMM_FLAG_ILLEGAL
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_UnknownReturn() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_UNKNOWN)

/*----------------------------------------------------------------------------*\
Function:
	Command_SetIllegalReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_SetUnknownReturn(bool:set);

global void:Command_SetUnknownReturn(bool:set)
{
	P:2("Command_SetUnknownReturn called: %i", bool:set);
	if (set)
	{
		YSI_g_sCommandFlags |= e_COMM_FLAG_UNKNOWN;
	}
	else
	{
		YSI_g_sCommandFlags &= ~e_COMM_FLAG_UNKNOWN;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetIllegalReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Command_GetUnknownReturn();

global bool:Command_GetUnknownReturn()
{
	P:2("bool:Command_GetUnknownReturn called");
	return bool:Command_UnknownReturn();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_DisconnectReturn
Params:
	-
Return:
	e_COMM_FLAG_DISCONNECT
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_DisconnectReturn() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_DISCONNECT)

/*----------------------------------------------------------------------------*\
Function:
	Command_SetDisconnectReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_SetDisconnectReturn(bool:set);

global void:Command_SetDisconnectReturn(bool:set)
{
	P:2("Command_SetDisconnectReturn called: %i", bool:set);
	if (set)
	{
		YSI_g_sCommandFlags |= e_COMM_FLAG_DISCONNECT;
	}
	else
	{
		YSI_g_sCommandFlags &= ~e_COMM_FLAG_DISCONNECT;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetDisconnectReturn
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Command_GetDisconnectReturn();

global bool:Command_GetDisconnectReturn()
{
	P:2("bool:Command_GetDisconnectReturn called");
	return bool:Command_DisconnectReturn();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_DeniedDisplay
Params:
	-
Return:
	e_COMM_FLAG_PERMISSION_WARN
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_DeniedDisplay() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_PERMISSION_WARN)

/*----------------------------------------------------------------------------*\
Function:
	Command_SetDeniedDisplay
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_SetDeniedDisplay(bool:set);

global void:Command_SetDeniedDisplay(bool:set)
{
	P:2("Command_SetDeniedDisplay called: %i", bool:set);
	if (set)
	{
		YSI_g_sCommandFlags |= e_COMM_FLAG_PERMISSION_WARN;
	}
	else
	{
		YSI_g_sCommandFlags &= ~e_COMM_FLAG_PERMISSION_WARN;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetDeniedDisplay
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Command_GetDeniedDisplay();

global bool:Command_GetDeniedDisplay()
{
	P:2("bool:Command_GetDeniedDisplay called");
	return bool:Command_DeniedDisplay();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetNameInt
Params:
	f - Command to get the name of.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

/*RF:Command_GetNameInt[i](f)
{
	P:2("Command_GetNameInt called: %i", f);
	if (f >= 0 && f < YSI_g_sCommandIndex)
	{
		setproperty(8, "", YSIM_STRING, Command_Name(f));
		return 1;
	}
	return 0;
}*/

/*----------------------------------------------------------------------------*\
Function:
	Command_GetName
Params:
	funcid - Command to get the name of.
Return:
	-
Notes:

native Command_GetName(funcid);

\*----------------------------------------------------------------------------*/

/*stock Command_GetName(funcid)
{
	P:3("Command_GetName called: %i", funcid);
	new
		buffer[32] = "";
	if (Command_GetNameInt(funcid))
	{
		getproperty(8, "", YSIM_STRING, buffer);
		strunpack(buffer, buffer);
	}
	return buffer;
}*/

/*----------------------------------------------------------------------------*\
Function:
	Command_IsSorted
Params:
	-
Return:
	e_COMM_FLAG_SORTED
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_IsSorted() \
	(YSI_g_sCommandFlags & e_COMM_FLAG_SORTED)

/*----------------------------------------------------------------------------*\
Function:
	Command_Generate
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Command_Generate();

global void:Command_Generate()
{
	P:2("Command_Generate called");
	P:2("Command_Generate called");
	if (!Command_IsSorted())
	{
		P:2("Command_Generate: Count = %d", YSI_g_sCommandCount);
		new
			data[MAX_COMMANDS][E_BINTREE_INPUT];
		// This is only called once, so we know YSI_g_sCommandCount will be
		// accurate WRT the locations of commands.
		for (new i = 0; i != YSI_g_sCommandCount; ++i)
		{
			data[i][E_BINTREE_INPUT_POINTER] = i;
			new
				hash = Command_PackHash(Command_Name(i));
			// Check for an existing command with this hash.
			if (!Command_HasCollisions())
			{
				for (new j = 0; j != i; ++j)
				{
					if (hash == data[j][E_BINTREE_INPUT_VALUE])
					{
						Command_SetCollisions();
						break;
					}
				}
			}
			C:3(else printf("Command_Generate: Hash = %d", hash););
			P:2("Command_Generate: Hash = %d", hash);
			data[i][E_BINTREE_INPUT_VALUE] = hash;
		}
		// WHY THE HECK did I change "Bintree_Generate" to "Bintree_Fill"?  That
		// skips the whole sorting code before adding things to the binary tree!
		if (YSI_g_sCommandCount)
		{
			//Bintree_Fill(YSI_g_sSearchTree, data, YSI_g_sCommandCount);
			Bintree_Generate(YSI_g_sSearchTree, data, YSI_g_sCommandCount);
			//Bintree_Fill(YSI_g_sSearchTree, data, YSI_g_sCommandCount);
		}
		P:4("Command_Generate: %d %d %d %d %d", YSI_g_sSearchTree[0][E_BINTREE_TREE_VALUE], YSI_g_sSearchTree[0][E_BINTREE_TREE_LEFT], YSI_g_sSearchTree[0][E_BINTREE_TREE_RIGHT], YSI_g_sSearchTree[0][E_BINTREE_TREE_PARENT], YSI_g_sSearchTree[0][E_BINTREE_TREE_POINTER]);
		// Set sorted to true.
		YSI_g_sCommandFlags |= e_COMM_FLAG_SORTED;
	}
	//return 1;
}

foreign void:Command_IncOPCR();

global void:Command_IncOPCR()
{
	P:2("Command_IncOPCR called");
	YSI_g_sCommandFlags += e_COMM_FLAG_OPCR_ADD;
	//return 1;
}

foreign void:Command_DecOPCR();

global void:Command_DecOPCR()
{
	P:2("Command_DecOPCR called");
	YSI_g_sCommandFlags -= e_COMM_FLAG_OPCR_ADD;
	//return 1;
}

foreign void:Command_IncOPCP();

global void:Command_IncOPCP()
{
	P:2("Command_IncOPCP called");
	YSI_g_sCommandFlags += e_COMM_FLAG_OPCP_ADD;
	//return 1;
}

foreign void:Command_DecOPCP();

global void:Command_DecOPCP()
{
	P:2("Command_DecOPCP called");
	YSI_g_sCommandFlags -= e_COMM_FLAG_OPCP_ADD;
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	OnScriptInit
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

hook OnScriptInit()
{
	// Set the default provider as any script.
	//YSI_g_sCommandFlags = 0xFF;
	P:1("Command_OnScriptInit called");
	// Initialise the tree.
	#if YSIM_NOT_CLIENT
		Bintree_Reset(YSI_g_sSearchTree);
		//YSI_g_sMaster23 = getproperty(8, "x@");
	#endif
	// Make a list of unused commands.
	for (new i = 0; i != MAX_COMMANDS - 1; ++i)
	{
		YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER] = i + 1;
	}
	YSI_g_sCommands[MAX_COMMANDS - 1][E_COMMANDS_FUNC_POINTER] = -1;
	// Loop through all the possible commands.  Note that this may need to add
	// commands to the remote command system if this is not the master system.
	// The way the master system is designed means that we will know if we are
	// master or not by the time this function is called.
	new
		buffer[32],
		idx;
	// This is the only place where AMX_FastString is used instead of
	// Commands_FastString as the strings in the AMX are not the same as packed
	// strings - they are in different memory orders.
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, _A<@yC_>)))
	{
		Command_Add(buffer, _@);
		//Command_Add(unpack(buffer), _@);
		//Command_Add(unpack(buffer), _@);
		P:2("Command_OnScriptInit: Adding %s", unpack(buffer));
	}
	Command_Generate();
	// Now that all commands have been added to the array, sort it.
	// Now call the next constructor.
	if (funcidx("OnPlayerCommandPerformed") != -1)
	{
		Command_IncOPCP();
	}
	if (funcidx("OnPlayerCommandReceived") != -1)
	{
		Command_IncOPCR();
	}
}

// Forwards for initial command callbacks.
forward OnPlayerCommandReceived(playerid, cmdtext[]); 
forward OnPlayerCommandPerformed(playerid, cmdtext[], success); 

hook OnScriptExit()
{
	P:1("Commands_OnScriptExit called");
	if (funcidx("OnPlayerCommandPerformed") != -1)
	{
		Command_DecOPCP();
	}
	if (funcidx("OnPlayerCommandReceived") != -1)
	{
		Command_DecOPCR();
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	OnScriptClose
Params:
	script - ID of the closing script.
Return:
	-
Notes:
	Called when a script under the control of the master system ends.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER && YSIM_NOT_CLIENT
	#if _YSIM_IS_CLOUD
		public OnScriptClose(script) <>
		{
			CallLocalFunction("Command_OnScriptClose", "i", script);
		}
		
		public OnScriptClose(script) <_YCM:y>
	#elseif _YSIM_IS_STUB
		#error y_commands called with _YSIM_IS_STUB.
	#else
		public OnScriptClose(script)
	#endif
	{
		new
			mask = ~(1 << script);
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (Command_GetPointer(i) == i && (YSI_g_sCommands[i][E_COMMANDS_MASTERS] &= mask) == 0)
			{
				for (new j = 0; j != MAX_COMMANDS; ++j)
				{
					// Remove all alternate names.
					if (Command_GetPointer(j) == i)
					{
						YSI_g_sCommands[j][E_COMMANDS_FUNC_POINTER] = YSI_g_sCommandIndex;
						YSI_g_sCommandIndex = j;
						YSI_g_sCommands[j][E_COMMANDS_MASTERS] = 0;
						//Bintree_Delete(YSI_g_sSearchTree, j, YSI_g_sCommandCount);
						Command_RemoveFromBintree(j);
						--YSI_g_sCommandCount;
						//Bintree_Add(YSI_g_sSearchTree, YSI_g_sCommandIndex, hash, YSI_g_sCommandIndex);
					}
				}
			}
			/*new
				p = i;
			while (YSI_g_sCommands[p][E_COMMANDS_MASTERS] == -1)
			{
				p = Command_GetPointer(p);
			}
			if (YSI_g_sCommands[p][E_COMMANDS_FUNC_POINTER] == p && (YSI_g_sCommands[p][E_COMMANDS_MASTERS] &= mask) == 0)
			{
				// Remove all alternate versions of commands - done backwards by
				// an alternate command checking its parent.  Can also handle
				// alternate versions of alternate commands (note this is the
				// only code that can currently).
				YSI_g_sCommands[i][E_COMMANDS_MASTERS] = 0;
				YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER] = YSI_g_sCommandIndex;
				YSI_g_sCommandIndex = i;
				// Mark it as invalid in this instance.
				YSI_g_sCommands[i][E_COMMANDS_MASTERS] = 0;
				// Reduce the number of commands.
				--YSI_g_sCommandCount;
			}*/
		}
		//YSI_g_sMaster23 = getproperty(8, "x@");
		// I can add better removal code later.  Done ^
		CallLocalFunction("Command_OnScriptClose", "i", script);
	}
	
	// Don't need ALS here as we did it supporting it at the start.
	#undef OnScriptClose
	//#define OnScriptClose(%0) Command_OnScriptClose(%0) <_ALS_:hooked>
	//forward Command_OnScriptClose(script);public Command_OnScriptClose(script)<_ALS_:unhooked>{return 1;}public Command_OnScriptClose(script)<>{return 1;}
	#define OnScriptClose Command_OnScriptClose
	forward Command_OnScriptClose(script);
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_TouchNamed
Params:
	string:command[] - Command to "touch".
Return:
	-
Notes:
	Used within "GROUP_ADD" to quickly assign a load of commands to just one
	group.
\*----------------------------------------------------------------------------*/

foreign void:Command_TouchNamed(string:command[]);

global void:Command_TouchNamed(string:command[])
{
	new
		id = Command_Find(command);
	if (id != COMMAND_NOT_FOUND)
	{
		NO_GROUPS(id)
		{
			return; //0;
		}
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Touch
Params:
	string:command[] - Command to "touch".
Return:
	-
Notes:
	Used within "GROUP_ADD" to quickly assign a load of commands to just one
	group.
\*----------------------------------------------------------------------------*/

foreign void:Command_Touch(command);

global void:Command_Touch(command)
{
	if (Command_IsValid(command))
	{
		NO_GROUPS(command)
		{
			return; //0;
		}
		//return 1;
	}
	//return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	OnPlayerConnect
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

// TODO: Rewrite!
//RA:Command_OnPlayerConnect(playerid)

#if YSIM_NOT_CLIENT
	mhook OnPlayerConnect(playerid)
	{
		//#if YSIM_NOT_CLIENT
		//YSI_g_sCommandDialog[playerid] = -1;
		#if YSIM_HAS_MASTER
			YSI_g_sPlayerProvider{playerid} = 0xFF;
		#endif
		NO_GROUPS()
		{
			new
				slot = Bit_Slot(playerid) + 1,
				Bit:mask = Bit_Mask(playerid); //Bit:(1 << (playerid & (cellbits - 1)));
			for (new i = 0; i != MAX_COMMANDS; ++i)
			{
				YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] |= mask;
				//PA+(YSI_g_sCommands[i][E_COMMANDS_PLAYERS], mask);
			}
		}
		//#endif
		// Groups will ALWAYS be called after this function - so this can reset
		// player permissions however it likes with the group system then being
		// able to override anything set in here.
		return 1;
		//ALS_CALL<PlayerConnect, i>(playerid)
	}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_
Params:
	command - Command to declare.
Return:
	-
Notes:
	Deprecated!
\*----------------------------------------------------------------------------*/

#define Command_(%1) \
	CMD:%1(playerid,params[],help)

/*----------------------------------------------------------------------------*\
Function:
	ycmd
Params:
	command[] - Command to register.
Return:
	-
Notes:
	Deprecated!
\*----------------------------------------------------------------------------*/

#define ycmd(%1);

/*----------------------------------------------------------------------------*\
Function:
	Command_FindFast
Params:
	data[] - Function name to find.
	value - Hash of function name.
Return:
	Position in functions array or COMMAND_NOT_FOUND.
Notes:
	-
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	static stock Command_FindFast(data[], value, provider = 0xFF)
#else
	static stock Command_FindFast(data[], value)
#endif
{
	new
		leaf,
		pointer;
	#if YSIM_HAS_MASTER
		P:4("Command_FindFast called: \"%s\", %i, %i", data, value, provider);
		provider <<= 24;
		P:5("Command_FindFast: Searching for %s", data);
		if (Command_HasMultipleProviders())
		{
			/*if (provider == 0xFF)
			{
				while ((pointer = Bintree_FindValue(YSI_g_sSearchTree, value, leaf)) != BINTREE_NOT_FOUND)
				{
					//new
					//	p = YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] & 0xFF000000;
					//P:7("Command_FindFast: providers %d %d %d", Command_HasMultipleProviders(), (p & 0xFF000000 != 0xFF000000), (p >>> 24 != provider));
					// Any script will do.
					//if ((YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] & 0xFF000000) != 0xFF000000) continue;
					//if (p != 0xFF000000 && p != provider) continue;
					// Don't do an strcmp if there are no collisions.
					P:7("Command_FindFast: collisions %d", !Command_HasCollisions());
					if (!Command_HasCollisions()) return pointer;
					//if (!strcmp(YSI_g_sCommands[i][E_COMMANDS_FUNCTION][1], funcname) &&
					P:7("Command_FindFast: strcmp %d", !strcmp(Command_Name(pointer), data));
					if (!strcmp(Command_Name(pointer), data)) return pointer;
					//if (!strcmp(Command_Name(pointer), data) && (Command_GetProvider(pointer) == 0xFF || Command_GetProvider(pointer) == provider)) return pointer;
				}
			}
			else
			{*/
				while ((pointer = Bintree_FindValue(YSI_g_sSearchTree, value, leaf)) != BINTREE_NOT_FOUND)
				{
					//new
					//	p = YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] & 0xFF000000;
					//P:7("Command_FindFast: providers %d %d %d", Command_HasMultipleProviders(), (p & 0xFF000000 != 0xFF000000), (p >>> 24 != provider));
					//if (p != provider && p != 0xFF000000) continue;
					// Only one provider will do.
					if ((YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] & 0xFF000000) != provider) continue;
					// Don't do an strcmp if there are no collisions.
					P:7("Command_FindFast: collisions %d", Command_HasCollisions());
					if (!Command_HasCollisions()) return pointer;
					//if (!strcmp(YSI_g_sCommands[i][E_COMMANDS_FUNCTION][1], funcname) &&
					P:7("Command_FindFast: strcmp %d", !strcmp(Command_Name(pointer), data));
					if (!strcmp(Command_Name(pointer), data)) return pointer;
					//if (!strcmp(Command_Name(pointer), data) && (Command_GetProvider(pointer) == 0xFF || Command_GetProvider(pointer) == provider)) return pointer;
				}
			//}
		}
		else
		{
	#endif
			while ((pointer = Bintree_FindValue(YSI_g_sSearchTree, value, leaf)) != BINTREE_NOT_FOUND)
			{
				//new
				//	p = YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] & 0xFF000000;
				//P:7("Command_FindFast: providers %d %d %d", Command_HasMultipleProviders(), (p & 0xFF000000 != 0xFF000000), (p >>> 24 != provider));
				//if (Command_HasMultipleProviders() && (p != 0xFF000000) && (p != provider)) continue;
				// Don't do an strcmp if there are no collisions.
				P:7("Command_FindFast: collisions %d", Command_HasCollisions());
				if (!Command_HasCollisions()) return pointer;
				//if (!strcmp(YSI_g_sCommands[i][E_COMMANDS_FUNCTION][1], funcname) &&
				P:7("Command_FindFast: strcmp %d", !strcmp(Command_Name(pointer), data));
				if (!strcmp(Command_Name(pointer), data)) return pointer;
				//if (!strcmp(Command_Name(pointer), data) && (Command_GetProvider(pointer) == 0xFF || Command_GetProvider(pointer) == provider)) return pointer;
			}
	#if YSIM_HAS_MASTER
		}
	#endif
	P:5("Command_FindFast: Not found");
	return COMMAND_NOT_FOUND;
}

static stock Command_FindFastStrict(data[], value, provider)
{
	#if YSIM_HAS_MASTER
		P:4("Command_FindFastStrict called: \"%s\", %i, %i", data, value, provider);
	#else
		#pragma unused provider
	#endif
	new
		leaf,
		pointer;
	P:5("Command_FindFast: Searching for %s", data);
	while ((pointer = Bintree_FindValue(YSI_g_sSearchTree, value, leaf)) != BINTREE_NOT_FOUND)
	{
		#if YSIM_HAS_MASTER
			if (Command_HasMultipleProviders() && (YSI_g_sCommands[pointer][E_COMMANDS_FUNC_POINTER] >>> 24 != provider)) continue;
		#endif
		// Don't do an strcmp if there are no collisions.
		if (!Command_HasCollisions()) return pointer;
		if (!strcmp(Command_Name(pointer), data)) return pointer;
	}
	P:5("Command_FindFast: Not found");
	return COMMAND_NOT_FOUND;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_FindSlow
Params:
	funcname[] - Function to find.
Return:
	-
Notes:
	Searches through the array for function linearly - used to set altnames
	before the data has been sorted.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	static stock Command_FindSlow(funcname[], provider = 0xFF)
#else
	static stock Command_FindSlow(funcname[])
#endif
{
	#if YSIM_HAS_MASTER
		P:4("Command_FindSlow called: \"%s\", %i", funcname, provider);
	#endif
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		#if YSIM_HAS_MASTER
			new
				p = YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER];
			if (((p & 0x00FFFFFF == i) || (YSI_g_sCommands[i][E_COMMANDS_MASTERS] == -1)) &&
				(!Command_HasMultipleProviders() || (p & 0xFF000000 == 0xFF000000) || (p >>> 24 == provider)) &&
				!strcmp(Command_Name(i), funcname))
		#else
			if (YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER] == i && !strcmp(Command_Name(i), funcname))
		#endif
			{
				return i;
			}
	}
	return COMMAND_NOT_FOUND;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_FindSlowStrict
Params:
	funcname[] - Function to find.
Return:
	-
Notes:
	Searches through the array for function linearly - used to set altnames
	before the data has been sorted.
\*----------------------------------------------------------------------------*/

static stock Command_FindSlowStrict(funcname[], provider)
{
	#if YSIM_HAS_MASTER
		P:4("Command_FindSlowStrict called: \"%s\", %i", funcname, provider);
	#else
		#pragma unused provider
	#endif
	P:2("Command_FindSlowStrict: Searching for %s", unpack(funcname));
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		#if YSIM_HAS_MASTER
			new
				p = YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER];
			P:6("Command_FindSlowStrict: %s %08x %d %d", unpack(funcname), Command_Name(i), p & 0xFFFFFF, i);
			// This needs additional checks that the item is valid.
			if (((p & 0x00FFFFFF == i) || (YSI_g_sCommands[i][E_COMMANDS_MASTERS] == -1)) &&
				(!Command_HasMultipleProviders() || (p >>> 24 == provider)) &&
				!strcmp(Command_Name(i), funcname))
		#else
			if (YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER] == i && !strcmp(Command_Name(i), funcname))
		#endif
			{
				return i;
			}
	}
	return COMMAND_NOT_FOUND;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_AddHash
Params:
	command[] - Command text to hash.
	dest[] - Array to copy to.
	idx - Point to start copying from.
Return:
	hash value.
Notes:
	Hashes a string and copies it to a destination at the same time.
\*----------------------------------------------------------------------------*/

static stock Command_AddHash(command[], dest[], idx)
{
	P:4("Command_AddHash called: \"%s\", %i, %i", command, dest, idx);
	// Skip the function name prefix.
	new
		hash = -1,
		ch,
		dx = 1,
		end = idx + 28;
	// Copy and hash at the same time.
	do
	{
		/*ch = TOLOWER(command[idx++]);
		// Always NULL terminate.
		if ((dest[dx] = ch << 24) == COMMAND_END_CMP << 24)
		{
			// Fixes a bug with commands multiples of 4 chars long.
			dest[dx] = 0;
			break;
		}*/
		ch = TOLOWER(command[idx++]);
		if (ch == COMMAND_END_CMP) break;
		dest[dx] = ch << 24;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command[idx++]);
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 16;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command[idx++]);
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 8;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command[idx++]);
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 0;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		++dx;
	}
	while (idx < end);
	return hash;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_AddHashPacked
Params:
	command[] - Packed command text to hash.
	dest[] - Array to copy to.
	idx - Point to start copying from.
Return:
	hash value.
Notes:
	Hashes a string and copies it to a destination at the same time.
\*----------------------------------------------------------------------------*/

static stock Command_AddHashPacked(command[], dest[], idx)
{
	P:4("Command_AddHashPacked called: \"%s\", %i, %i", command, dest, idx);
	// Skip the function name prefix.
	new
		hash = -1,
		ch,
		dx = 1,
		end = idx + 28;
	// Copy and hash at the same time.
	do
	{
		/*ch = TOLOWER(command[idx++]);
		// Always NULL terminate.
		if ((dest[dx] = ch << 24) == COMMAND_END_CMP << 24)
		{
			// Fixes a bug with commands multiples of 4 chars long.
			dest[dx] = 0;
			break;
		}*/
		ch = TOLOWER(command{idx++});
		if (ch == COMMAND_END_CMP) break;
		dest[dx] = ch << 24;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command{idx++});
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 16;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command{idx++});
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 8;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		ch = TOLOWER(command{idx++});
		if (ch == COMMAND_END_CMP) break;
		dest[dx] |= ch << 0;
		hash = hash * 33 + ch; //Command_ToUpper(ch);
		++dx;
	}
	while (idx < end);
	return hash;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_FastHash
Params:
	command[] - Command text to hash.
Return:
	hash value.
Notes:
	Just hashes the passed string.
\*----------------------------------------------------------------------------*/

static stock Command_FastHash(command[])
{
	P:4("Command_FastHash called: \"%s\"", command);
	new
		index = 0,
		hash = -1,
		ch;
	while ((ch = command[index++])) hash = hash * 33 + TOLOWER(ch);
	return hash;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_PackHash
Params:
	command[] - Command text to hash.
Return:
	hash value.
Notes:
	Hashes packed strings.
\*----------------------------------------------------------------------------*/

static stock Command_PackHash(command[])
{
	P:4("Command_PackHash called: \"%s\"", command);
	new
		index = 0,
		hash = -1,
		ch;
	while ((ch = command[index++]))
	{
		P:4("Commands_PackHash: ch = 0x%04x%04x", ch >>> 16, ch & 0xFFFF);
		if (ch & 0xFF000000)
		{
			hash = hash * 33 + TOLOWER(ch >>> 24);
			P:5("Command_PackHash: Hash1 = %d", hash);
		}
		else
		{
			break;
		}
		if (ch & 0x00FF0000)
		{
			hash = hash * 33 + TOLOWER(ch >> 16 & 0xFF);
			P:5("Command_PackHash: Hash2 = %d", hash);
		}
		else
		{
			break;
		}
		if (ch & 0x0000FF00)
		{
			hash = hash * 33 + TOLOWER(ch >> 8 & 0xFF);
			P:5("Command_PackHash: Hash3 = %d", hash);
		}
		else
		{
			break;
		}
		if (ch & 0x000000FF)
		{
			hash = hash * 33 + TOLOWER(ch & 0xFF);
			P:5("Command_PackHash: Hash4 = %d", hash);
		}
		else
		{
			break;
		}
	}
	return hash;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Hash
Params:
	command[] - Command text to hash.
	&index - Start point and variable to store end point to.
	&length - Length of the hashed word.
Return:
	hash value.
Notes:
	Hashes a string using space delimiters and returns information such as the
	length of the string hased and the start point of the next word.
\*----------------------------------------------------------------------------*/

static stock Command_Hash(command[], &index, &length)
{
	P:4("Command_Hash called: \"%s\", %i, %i", command, index, length);
	new
		hash = -1,
		ch;
	length = index;
	while ((ch = command[index++]) > ' ') hash = hash * 33 + TOLOWER(ch);
	length = index - length - 1;
	while (ch)
	{
		if (ch > ' ')
		{
			break;
		}
		ch = command[index++];
	}
	--index;
	return hash;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Find
Params:
	function[] - Function name to find.
Return:
	Position in functions array or COMMAND_NOT_FOUND.
Notes:
	Used by API functions to avoid repeated sorting checks.
\*----------------------------------------------------------------------------*/

#if YSIM_HAS_MASTER
	static stock Command_Find(function[], provider = -1)
#else
	static stock Command_Find(function[])
#endif
{
	#if YSIM_HAS_MASTER
		P:4("Command_Find called: \"%s\", %i", function, provider);
		if (provider == -1)
		{
			provider = _:Command_DefaultProvider();
			// Find the ID of the command.
			if (Command_IsSorted())
			{
				return Command_FindFast(function, Command_FastHash(function), provider);
			}
			else
			{
				return Command_FindSlow(function, provider);
			}
		}
		else
		{
			provider &= 0xFF;
			// Find the ID of the command.
			if (Command_IsSorted())
			{
				return Command_FindFastStrict(function, Command_FastHash(function), provider);
			}
			else
			{
				return Command_FindSlowStrict(function, provider);
			}
		}
	#else
		if (Command_IsSorted())
		{
			return Command_FindFast(function, Command_FastHash(function));
		}
		else
		{
			return Command_FindSlow(function);
		}
	#endif
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetID
Params:
	function[] - Function name to find.
Return:
	The ID of the passed function.
Notes:
	-

native Command_GetID(function[])

\*----------------------------------------------------------------------------*/

foreign Command_GetID(string:function[]);

global Command_GetID(string:function[])
{
	P:2("Command_GetID called: \"%s\"", function);
	return Command_Find(function);
}

/*----------------------------------------------------------------------------*\
Function:
	Command_SetPlayer
Params:
	command - Command to set for.
	playerid - Player to set.
	bool:set - Wether or not this player can use this command.
Return:
	-
Notes:
	-

native bool:Command_SetPlayer(command, playerid, bool:set);

\*----------------------------------------------------------------------------*/

foreign void:Command_SetPlayer(c,p,bool:s);

global void:Command_SetPlayer(c,p,bool:s)
{
	P:2("Command_SetPlayer called: %i, %i, %i", c, p, s);
//	if (c < 0 || c >= YSI_g_sCommandIndex)
	if (0 <= c < MAX_COMMANDS)
	{
		//Bit_Set(YSI_g_sCommands[c][E_COMMANDS_PLAYERS], p, s, bits<MAX_PLAYERS>);
		//if (s) PA+(YSI_g_sCommands[c][E_COMMANDS_PLAYERS], p);
		//else PA-(YSI_g_sCommands[c][E_COMMANDS_PLAYERS], p);
		PA_Set(YSI_g_sCommands[c][E_COMMANDS_PLAYERS], p, s);
		// Not in range,
//		return false;
	}
	//return 1;
//	return s;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_SetPlayerNamed
Params:
	funcname[] - Command to set for.
	playerid - Player to set.
	set - Wether or not this player can use this command.
Return:
	-
Notes:
	Like Command_SetPlayer but for a function name.

native bool:Command_SetPlayerNamed(funcname[], playerid, bool:set);

\*----------------------------------------------------------------------------*/

foreign void:Command_SetPlayerNamed(string:f[],p,bool:s);

global void:Command_SetPlayerNamed(string:f[],p,bool:s)
{
	P:2("Command_SetPlayerNamed called: \"%s\", %i, %i", f, p, s);
	Command_SetPlayer(Command_Find(f), p, s);
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetPlayer
Params:
	command - Command to get for.
	playerid - Player to get.
Return:
	Wether this player can use this command.
Notes:
	-

native bool:Command_GetPlayer(command, playerid);

\*----------------------------------------------------------------------------*/

foreign bool:Command_GetPlayer(command, playerid);

global bool:Command_GetPlayer(command, playerid)
{
	P:2("bool:Command_GetPlayer called: %i, %i", command, playerid);
	if (0 <= command < MAX_COMMANDS)
	{
		return bool:Command_CheckPlayer(command, playerid);
	}
	// Not in range,
	return false;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetPlayerNamed
Params:
	funcname[] - Command to get for.
	playerid - Player to get.
Return:
	-
Notes:
	Like Command_GetPlayer but for a function name.

native bool:Command_GetPlayerNamed(funcname[], playerid);

\*----------------------------------------------------------------------------*/

foreign bool:Command_GetPlayerNamed(string:func[], playerid);

global bool:Command_GetPlayerNamed(string:func[], playerid)
{
	P:2("bool:Command_GetPlayerNamed called: \"%s\", %i", func, playerid);
	return Command_GetPlayer(Command_Find(func), playerid);
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Remove
Params:
	func - The slot of the command to remove.
Return:
	-
Notes:

native Command_Remove(func);

\*----------------------------------------------------------------------------*/

static stock Command_RemoveFromBintree(func)
{
	P:4("Command_RemoveFromBintree called: %i", func);
	if (!Command_IsSorted()) return;
	// This function has to find the right index in the binary tree, as that's
	// not in the same order at all.
	new
		leaf,
		hash = Command_PackHash(Command_Name(func));
	// Find where in the binary tree this is referenced from.
	while (Bintree_FindValue(YSI_g_sSearchTree, hash, _, leaf) != BINTREE_NOT_FOUND)
	{
		if (YSI_g_sSearchTree[leaf][E_BINTREE_TREE_POINTER] == func)
		{
			P:2("Command_RemoveFromBintree: Delete branch");
			Bintree_Delete(YSI_g_sSearchTree, leaf, YSI_g_sCommandCount);
			return;
		}
	}
}

foreign void:Command_Remove(func);

global void:Command_Remove(func)
{
	P:2("Command_Remove called: %i", func);
	if (0 <= func < MAX_COMMANDS)
	{
		if (Command_GetPointer(func) == func)
		{
			for (new i = 0; i != MAX_COMMANDS; ++i)
			{
				// Remove all alternate names.
				if (Command_GetPointer(i) == func)
				{
					// Add this to the list of unused functions.
					YSI_g_sCommands[i][E_COMMANDS_FUNC_POINTER] = YSI_g_sCommandIndex;
					YSI_g_sCommandIndex = i;
					// Mark it as invalid in this instance.
					#if YSIM_HAS_MASTER
						YSI_g_sCommands[i][E_COMMANDS_MASTERS] = 0;
					#endif
					// Reduce the number of commands.
					//Bintree_Delete(YSI_g_sSearchTree, i, YSI_g_sCommandCount);
					Command_RemoveFromBintree(i);
					--YSI_g_sCommandCount;
				}
			}
		}
		// Remove a single alternate name.
		YSI_g_sCommands[func][E_COMMANDS_FUNC_POINTER] = YSI_g_sCommandIndex;
		YSI_g_sCommandIndex = func;
		#if YSIM_HAS_MASTER
			YSI_g_sCommands[func][E_COMMANDS_MASTERS] = 0;
		#endif
		//Bintree_Delete(YSI_g_sSearchTree, func, YSI_g_sCommandCount);
		Command_RemoveFromBintree(func);
		--YSI_g_sCommandCount;
		//return 1;
	}
	//return 0;
}

foreign void:Command_RemoveNamed(string:func[]);

global void:Command_RemoveNamed(string:func[])
{
	P:2("Command_RemoveNamed called: \"%s\"", func);
	Command_Remove(Command_Find(func));
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Add
Params:
	funcname[] - The function to add to the array.
	script - The script ID with the function.
Return:
	-
Notes:
	If the list of commands have already been sorted into the binary tree the
	new commands will be appended, otherwise they will just be added to the
	array.

native Command_Add(funcname[], script);

\*----------------------------------------------------------------------------*/

foreign void:Command_Add(string:f[],s);

global void:Command_Add(string:f[],s)
{
	#if !YSIM_HAS_MASTER
		#pragma unused s
	#endif
	P:2("Command_Add called: \"%s\", %i", f, s);
	if (YSI_g_sCommandCount < MAX_COMMANDS && YSI_g_sCommandIndex != -1)
	{
		#if !YSIM_HAS_MASTER
			static
				provider = -1;
		#endif
		new
			#if YSIM_HAS_MASTER
				provider = _:Command_DefaultProvider(),
			#endif
			//hash = Command_AddHashPacked(f, YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION], 4),
			// Because of the way the master system works, packed strings are
			// unpacked when they are passed remotely, but not when they are
			// passed locally.  The unpacking is done by "CallRemoteFunction",
			// not anything we outselves do...
			offset = f[0] == '@' ? 4 : 1,
			hash = f[0] == '@' ?
				Command_AddHash(f, YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION], 4) :
				Command_AddHashPacked(f, YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION], 4);
		//printf("%s", unpack(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][1]));
		if (Command_IsSorted())
		{
			new
				idx = Command_FindFastStrict(f[offset], hash, provider);
			if (idx != COMMAND_NOT_FOUND)
			{
				P:4("Command_Add: Command exists");
				#if YSIM_HAS_MASTER
					YSI_g_sCommands[idx][E_COMMANDS_MASTERS] |= 1 << s;
				#endif
				return; //0;
			}
			if (!Command_HasCollisions())
			{
				// Check for an existing command with this hash.
				if (Bintree_FindValue(YSI_g_sSearchTree, hash) != BINTREE_NOT_FOUND)
				{
					Command_SetCollisions();
				}
			}
			// Command doesn't exist already - good!
			Bintree_Add(YSI_g_sSearchTree, YSI_g_sCommandIndex, hash, YSI_g_sCommandIndex);
		}
		else
		{
			new
				idx = Command_FindSlowStrict(f[offset], provider);
			if (idx != COMMAND_NOT_FOUND)
			{
				P:4("Command_Add: Command exists");
				#if YSIM_HAS_MASTER
					YSI_g_sCommands[idx][E_COMMANDS_MASTERS] |= 1 << s;
				#endif
				return; //0;
			}
		}
		YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][0] = COMMAND_FUNCTION_PREFIX;
		//Bit_SetAll(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS], true, bits<MAX_PLAYERS>);
		//Command_InitialiseFromGroups(YSI_g_sCommandIndex);
		PA_FastInit(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS]);
		NO_GROUPS(YSI_g_sCommandIndex)
		{
			PA_Init(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS], true);
		}
		// Swap these.
		#if YSIM_HAS_MASTER
			YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_MASTERS] = 1 << s;
		#endif
		P:2("Command_Add: Command added in %d (%d)", YSI_g_sCommandIndex, hash);
		hash = YSI_g_sCommandIndex;
		// Set this command as usable in any script.
		P:4("Command_Add: %08x%08x%08x%08x", YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][0], YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][1], YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][2], YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][3]);
		YSI_g_sCommandIndex = YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER];
		#if YSIM_HAS_MASTER
			YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER] = hash | (provider << 24);
		#else
			YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER] = hash;
		#endif
		/*#if YSIM_HAS_MASTER
			if (s == _@)
		#endif
			{
				new
					addr = funcidx(f) * 8 + AMX_HEADER_PUBLICS;
				#emit LREF.S.pri addr
				#emit STOR.S.pri addr
				YSI_g_sCommands[hash][E_COMMANDS_AMX_ADDRESS] = addr;
			}
		#pragma tabsize 4*/
		// Now some complex debug rubbish.
		C:4(new str[32];strpack(str, f);printf("Command_Add: %08x%08x%08x%08x", str[0], str[1], str[2], str[3]););
		++YSI_g_sCommandCount;
	}
	//return 1;
	/*else
	{
		// Not all hope is lost - check if this command name already exists.
		if (Command_IsSorted())
		{
			new
				pos = Command_FindFast(funcname[4], Command_FastHash(funcname[4]));
			if (pos != COMMAND_NOT_FOUND)
			{
				// Found it already in the array.
				return pos;
			}
		}
		else
		{
			new
				pos = Command_FindSlow(funcname[4]);
			if (pos != COMMAND_NOT_FOUND)
			{
				// Command already exists.
				return pos;
			}
		}
	}
	return COMMAND_NOT_FOUND;*/
}

/*----------------------------------------------------------------------------*\
Function:
	Command_AddAlt
Params:
	funcidx - The function this is an alternate to.
	altname[] - The new name.
Return:
	-
Notes:
	If the list of commands have already been sorted into the binary tree the
	new commands will be appended, otherwise they will just be added to the
	array.

native Command_AddAlt(funcidx, altname[]);

\*----------------------------------------------------------------------------*/

foreign Command_AddAlt(oidx, string:altname[]);

global Command_AddAlt(oidx, string:altname[])
{
	P:2("Command_AddAlt called: %i, \"%s\"", oidx, altname);
	if (!Command_IsValid(oidx))
	{
		return COMMAND_NOT_FOUND;
	}
	#if YSIM_HAS_MASTER
		new
			provider = _:Command_DefaultProvider();
	#else
		static
			provider = -1;
	#endif
	if (YSI_g_sCommandCount < MAX_COMMANDS && YSI_g_sCommandIndex != -1)
	{
		new
			hash = Command_AddHash(altname, YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION], 0);
		if (Command_IsSorted())
		{
			// Find the function this mirrors.
			//oidx = Command_FindFast(function, Command_FastHash(function));
			new
				pos = Command_FindFastStrict(altname, hash, provider);
			if (pos != COMMAND_NOT_FOUND)
			{
				if (Command_GetPointer(pos) != oidx)
				{
					// Same altname, different function.
					return COMMAND_NOT_FOUND;
				}
				return pos;
			}
			if (!Command_HasCollisions())
			{
				// Check for an existing command with this hash.
				//if (Bintree_FindValue(YSI_g_sSearchTree, hash) != BINTREE_NOT_FOUND)
				//{
				//	Command_SetCollisions();
				//}
				new
					leaf;
				while ((pos = Bintree_FindValue(YSI_g_sSearchTree, hash, leaf)) != BINTREE_NOT_FOUND)
				{
					// Don't have collisions if the providers are different.
					if ((YSI_g_sCommands[pos][E_COMMANDS_FUNC_POINTER] >>> 24) != provider) continue;
					Command_SetCollisions();
				}
			}
			// Command doesn't exist already - good!
			Bintree_Add(YSI_g_sSearchTree, YSI_g_sCommandIndex, hash, YSI_g_sCommandIndex);
		}
		else
		{
			new
				pos = Command_FindSlowStrict(altname, provider);
			if (pos != COMMAND_NOT_FOUND)
			{
				if (Command_GetPointer(pos) != oidx)
				{
					// Same altname, different function.
					return COMMAND_NOT_FOUND;
				}
				// Command already exists.
				return pos;
			}
		}
		YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_FUNCTION][0] = COMMAND_FUNCTION_PREFIX;
		//Bit_SetAll(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS], true, bits<MAX_PLAYERS>);
		//Command_InitialiseFromGroups(YSI_g_sCommandIndex);
		PA_FastInit(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS]);
		NO_GROUPS(YSI_g_sCommandIndex)
		{
			PA_Init(YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_PLAYERS], true);
		}
		++YSI_g_sCommandCount;
		#if YSIM_HAS_MASTER
			// This doesn't have real masters.
			YSI_g_sCommands[YSI_g_sCommandIndex][E_COMMANDS_MASTERS] = -1;
		#endif
		P:2("Command_AddAlt: Command added in %d as %d", YSI_g_sCommandIndex, oidx);
		hash = YSI_g_sCommandIndex;
		YSI_g_sCommandIndex = YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER];
		#if YSIM_HAS_MASTER
			YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER] = oidx | (provider << 24);
		#else
			YSI_g_sCommands[hash][E_COMMANDS_FUNC_POINTER] = oidx;
		#endif
		return hash;
	}
	else
	{
		// Not all hope is lost - check if this command name already exists.
		new
			pos;
		if (Command_IsSorted())
		{
			pos = Command_FindFastStrict(altname, Command_FastHash(altname), provider);
		}
		else
		{
			pos = Command_FindSlowStrict(altname, provider);
		}
		if (pos != COMMAND_NOT_FOUND)
		{
			// Found it already in the array.  Check if the element it points to
			// has the correct name so we know this is the correct pair, not
			// just the correct single element.  I.e. check that this is the
			// correct original/altname combo, not the right altname on a
			// different original name.
			if (oidx == Command_GetPointer(pos))
			{
				return pos;
			}
		}
	}
	return COMMAND_NOT_FOUND;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_AddAltNamed
Params:
	function[] - The function this is an alternate to.
	altname[] - The new name.
Return:
	-
Notes:
	Add an alternate command for an existing command.

native Command_AddAltNamed(function[], altname[]);

\*----------------------------------------------------------------------------*/

foreign Command_AddAltNamed(string:function[], string:altname[]);

global Command_AddAltNamed(string:function[], string:altname[])
{
	P:2("Command_AddAltNamed called: \"%s\", \"%s\"", function, altname);
	return Command_AddAlt(Command_Find(function), altname);
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Debug
Params:
	-
Return:
	-
Notes:
	Print some random information about commands if _DEBUG is set.
\*----------------------------------------------------------------------------*/

stock Command_Debug()
{
	P:3("Command_Debug called: %i");
	#if _DEBUG > 0
		printf("Command_Debug: Start");
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (Command_IsValid(i))
			{
				printf("Command_Debug: Loop start %d", i);
				new buffer[MAX_COMMAND_LENGTH];
				strunpack(buffer, Command_Name(i));
				printf("%08x%08x%08x", YSI_g_sCommands[i][E_COMMANDS_FUNCTION][0], YSI_g_sCommands[i][E_COMMANDS_FUNCTION][1], YSI_g_sCommands[i][E_COMMANDS_FUNCTION][2]);
				new pointer = Command_GetPointer(i);
				printf("Command %d:", i);
				printf("\t%s", buffer);
				printf("\t%d", pointer);
				printf("\t%d %d %d", YSI_g_sSearchTree[i][E_BINTREE_TREE_LEFT], YSI_g_sSearchTree[i][E_BINTREE_TREE_RIGHT], YSI_g_sSearchTree[i][E_BINTREE_TREE_VALUE]);
				CallLocalFunction(Command_GetFunction(Command_GetPointer(i)), "isi", 0, "hi", 0);
				printf("Command_Debug: Loop end");
			}
		}
		printf("Command_Debug: End");
	#endif
}

/*----------------------------------------------------------------------------*\
Function:
	OnPlayerCommandText
Params:
	playerid - Player who entered the command.
	cmdtext[] - Text entered.
Return:
	true - success or hidden fail, false - fail.
Notes:
	Calls the Command_Process function if this is not a client.
\*----------------------------------------------------------------------------*/

#if YSIM_NOT_CLIENT
	mhook OnPlayerCommandText(playerid, cmdtext[])
	{
		P:1("Commands_OnPlayerCommandText");
		if (isnull(cmdtext)) return Command_UnknownReturn();
		if (YSI_g_sCommandFlags & e_COMM_FLAG_OPCR)
		{
			switch (CallRemoteFunction("OnPlayerCommandReceived", "is", playerid, cmdtext))
			{
				case 0:
					// Handle normally, as in ZCMD.
					return 1;
				case -1:
					// Allow them to stop processing but return 0.
					return 0;
				// Do nothing on 1.
			}
		}
		if (YSI_g_sCommandFlags & e_COMM_FLAG_OPCP)
		{
			new
				ret = Command_Process(playerid, cmdtext, 0);
			switch (CallRemoteFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, ret))
			{
				case 0:
					return 0;
				case 1:
					return 1;
				//default:
					// Return the original return on -1.
			}
			return ret;
		}
		else
		{
			/*switch (Command_Process(playerid, cmdtext, 0))
			{
				case 1:
					// Found the command, processed.
					return 1;
				case -1:
					// Found the command, but want to return 0 anyway.
					return 0;
				// Do nothing on 0.
			}*/
			return Command_Process(playerid, cmdtext, 0);
		}
		// This can never actually be reached!
		//return 0;
	}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Command_ReProcess
Params:
	playerid - Player who entered the command.
	cmdtext[] - Text entered.
	help - Called from the help commmand or OnPlayerCommandText.
Return:
	true - success or hidden fail, false - fail.
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Command_ReProcess(p,string:c[],h);

global Command_ReProcess(p,string:c[],h)
{
	P:2("Command_ReProcess called: %i, \"%s\", %i", p, c, h);
	return Command_Process(p,c,h);
}

/*----------------------------------------------------------------------------*\
Function:
	Command_Process
Params:
	playerid - Player who entered the command.
	cmdtext[] - Text entered.
	help - Called from the help commmand or OnPlayerCommandText.
Return:
	true - success or hidden fail, false - fail.
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Command_CallR(%1,%2) \
	CallRemoteFunction(Command_GetFuncName((%1)), "isii", playerid, %2, help, script)

#define Command_CallL(%1,%2) \
	CallLocalFunction(Command_GetFuncName((%1)), "isi", playerid, %2, help)

static stock Command_Process(playerid, cmdtext[], help)
{
	P:4("Command_Process FS called: %i, \"%s\", %i", playerid, cmdtext, help);
	// Support for very old problems!
	// TODO: Add back.
	P:2("Command_Process called: %d %s", playerid, cmdtext);
	/*#if !_DEBUG && !defined _YSI_SPECIAL_DEBUG
		// For testing purposes.
		if (!IsPlayerConnected(playerid))
		{
			return Command_DisconnectReturn();
		}
	#endif*/
	P:4("Command_Process: Connected");
	new
		idx,
		prelen = help ? 0 : 1,
		index = prelen;
	/*// Shortcuts.
	if (cmdtext[2] <= ' ')
	{
		// Get a player's shortcut information for this letter.
	}
	else*/
	{
		// No more faffing about with random alternate code - it's all done in
		// one nice function instead of having to handle both separately.
		new
			length,
			hash = Command_Hash(cmdtext, index, length);
		P:2("Command_Process: Hash = %d, Length = %d", hash, length);
		// NOTE: No prefix support here.
		cmdtext[length + prelen] = '\0';
		#if YSIM_HAS_MASTER
			length = YSI_g_sPlayerProvider{playerid};
			P:2("Command_Process: Provider: %d", length);
			idx = Command_FindFast(cmdtext[prelen], hash, length);
			if (idx == COMMAND_NOT_FOUND && length != 0xFF)
			{
				// Check default commands if no specialised commands were found.
				idx = Command_FindFast(cmdtext[prelen], hash);
			}
		#else
			idx = Command_FindFast(cmdtext[prelen], hash);
		#endif
		// TODO: Replace!
		//idx = Command_FindSlow(cmdtext[prelen]);//, hash);
	}
	P:2("Command_Process: Index = %d", idx);
	if (idx != COMMAND_NOT_FOUND)
	{
		// Get the master data for the underlying command, not the possibly
		// changed name.
		new
			pointer = Command_GetPointer(idx);
		P:4("Command_Process: Found %d, %d", idx, pointer);
		// Found a command with this name - check the permissions.
		//if (Bit_Get(YSI_g_sCommands[idx][E_COMMANDS_PLAYERS], playerid))
		if (Command_CheckPlayer(idx, playerid))
		{
			P:4("Command_Process: Allowed");
			// Allowed to use the command, get the real function.  Note that
			// this may well be the same as "idx", but we loose no time.
			#if YSIM_HAS_MASTER
				P:4("Command_Process: %08x%08x%08x%08x", YSI_g_sCommands[idx][E_COMMANDS_FUNCTION][0], YSI_g_sCommands[idx][E_COMMANDS_FUNCTION][1], YSI_g_sCommands[idx][E_COMMANDS_FUNCTION][2], YSI_g_sCommands[idx][E_COMMANDS_FUNCTION][3]);
				//if (master & 1 << YSI_g_sMaster23)
				//{
				//	master = YSI_g_sMaster23;
				//}
				//else
				//{
				new
					script = Command_Provider(idx);
				if (script == 0xFF)
				{
					script = YSI_g_sCommands[pointer][E_COMMANDS_MASTERS];
					if (!script)
					{
						// No scripts can serve the code.
						return Command_UnknownReturn();
					}
					// Find the lowest set bit.  We use this to broadcastfunc the
					// command.  If it uses MASTER 23, this will select only
					// one script to use.  If it doesn't use MASTER 23, this is
					// ignored as a parameter and _YCM is used instead.
					static const
						scDeBruijn[] =
							{
								0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8, 
								31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
							};
					// http://supertech.csail.mit.edu/papers/debruijn.pdf
					script = scDeBruijn[((script & -script) * 0x077CB531) >>> 27];
				}
				//}
				P:2("Command_Process: script = %d", script);
				//if (master == _@)
				//{
			/*#endif
					// This script has it!
					addr = YSI_g_sCommands[pointer][E_COMMANDS_AMX_ADDRESS];
					P:4("Command_Process: %04x%04x", addr >>> 16, addr & 0xFFFF);
					// Make sure all the "#emits" are together as they don't
					// seem to be affected by pre-processor directives.
					#emit PUSH.S     master
					#emit PUSH.S     help
					#emit LOAD.S.alt cmdtext
					#emit LOAD.S.pri index
					#emit SMUL.C     4
					#emit ADD
					#emit PUSH.pri
					#emit PUSH.S     playerid
					#emit PUSH.C     16
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.S.pri addr
					#emit SCTRL      6
					#emit STOR.S.pri addr
			#if YSIM_HAS_MASTER*/
				//}
				//else
				//{
					#pragma tabsize 4
					P:2("Command_Process: call %s (%d, %d)", unpack(Command_GetFuncName(pointer)), pointer, script);
					if (cmdtext[index])
					{
						// Call it!
						Command_CallR(pointer, cmdtext[index]);
					}
					else
					{
						Command_CallR(pointer, NULL);
					}
					#pragma tabsize 4
				//}
				// Get the real return.
				P:1("Command_Process: return: %d", getproperty(8, YSIM_RETURN));
				return getproperty(8, YSIM_RETURN);
			#else
				if (cmdtext[index])
				{
					// Call it!
					return Command_CallL(pointer, cmdtext[index]);
				}
				else
				{
					return Command_CallL(pointer, NULL);
				}
				//return addr;
			#endif
		}
		else
		{
			return Command_DeniedReturn();
		}
	}
	P:5("Command_Process: Not found");
	return Command_UnknownReturn();
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetName
Params:
	funcid - Command to get the name of.
Return:
	-
Notes:

native Command_GetName(funcid);

\*----------------------------------------------------------------------------*/

foreign string:Command_GetName(funcid);

global string:Command_GetName(funcid)
{
	P:2("Command_GetName called: %i", funcid);
	new
		buffer[YSI_MAX_STRING] = "";
	if (Command_IsValid(funcid))
	{
		strunpack(buffer, Command_Name(funcid));
	}
	return buffer;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetDisplay
Params:
	f - Command to get the real name of.
	p - Player to get the name for.
Return:
	The name of a command for a single player.
Notes:
	-

native Command_GetDisplay(funcid, playerid);

\*----------------------------------------------------------------------------*/

foreign string:Command_GetDisplay(funcid, playerid);

global string:Command_GetDisplay(funcid, playerid)
{
	P:2("Command_GetDisplay called: %i, %i", funcid, playerid);
	new
		buffer[YSI_MAX_STRING] = "";
	if (Command_IsValid(funcid))
	{
		// Don't recalculate this every loop.
		new
			slot = Bit_Slot(playerid) + 1,
			Bit:mask = Bit_Mask(playerid);
		// Check if they can use the original version.
		if (YSI_g_sCommands[funcid][E_COMMANDS_PLAYERS][slot] & mask)
		{
			//setproperty(8, "", YSIM_STRING, Command_Name(f));
			strunpack(buffer, Command_Name(funcid));
			return buffer;
			//return 1;
		}
		// Search for a command pointing to that command which the player can use.
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (Command_GetPointer(i) == funcid && (YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask))
			{
				//setproperty(8, "", YSIM_STRING, Command_Name(i));
				strunpack(buffer, Command_Name(i));
				return buffer;
			}
		}
	}
	return buffer;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetDisplayNamed
Params:
	f[] - Command to get the real name of.
	p - Player to get the name for.
Return:
	The name of a named function for one player.
Notes:
	Remote function call for Command_GetDisplayNameNamed - avoids needing to
	expose users to the master system's odd way of returning strings.  This is
	the only part I've not yet fixed up to be nice and hidden.

native string:Command_GetDisplayNamed(string:funcid[], playerid);

\*----------------------------------------------------------------------------*/

foreign string:Command_GetDisplayNamed(string:func[], playerid);

global string:Command_GetDisplayNamed(string:func[], playerid)
{
	P:1("Command_GetDisplayNamed called: \"%s\", %i", func, playerid);
	new
		pointer = Command_Find(func),
		buffer[YSI_MAX_STRING] = "";
	if (pointer != COMMAND_NOT_FOUND)
	{
		// Don't recalculate this every loop.
		new
			slot = Bit_Slot(playerid) + 1, //playerid >>> CELLSHIFT) + 1,
			Bit:mask = Bit_Mask(playerid); //Bit:(1 << (playerid & (cellbits - 1)));
		// Check if they can use the original version.
		if (YSI_g_sCommands[pointer][E_COMMANDS_PLAYERS][slot] & mask)
		{
			//setproperty(8, "", YSIM_STRING, Command_Name(pointer));
			strunpack(buffer, Command_Name(pointer));
			return buffer;
		}
		// Search for a command pointing to that command which the player can use.
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (Command_GetPointer(i) == pointer && (YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask))
			{
				//setproperty(8, "", YSIM_STRING, Command_Name(i));
				strunpack(buffer, Command_Name(i));
				return buffer;
			}
		}
	}
	return buffer;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetPlayerCommandCount
Params:
	playerid - Player to count for.
Return:
	-
Notes:
	Gets the number of comamnds this player can use.

native Command_GetPlayerCommandCount(playerid);

\*----------------------------------------------------------------------------*/

foreign Command_GetPlayerCommandCount(playerid);

global Command_GetPlayerCommandCount(playerid)
{
	P:2("Command_GetPlayerCommandCount called: %i", playerid);
	new
		slot = Bit_Slot(playerid) + 1,
		Bit:mask = Bit_Mask(playerid),
		count = 0;
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		if (_Command_IsValid(i) && YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask)
		{
			++count;
		}
	}
	return count;
}

/*----------------------------------------------------------------------------*\
Function:
	Command_GetNext
Params:
	index - Index of the next command for this player.
	playerid - Player to get the name for.
Return:
	The name of a command for a single player.
Notes:
	-

native Command_GetNext(index, playerid);

\*----------------------------------------------------------------------------*/

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
			slot = Bit_Slot(playerid) + 1,
			Bit:mask = Bit_Mask(playerid);
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (_Command_IsValid(i) && YSI_g_sCommands[i][E_COMMANDS_PLAYERS][slot] & mask)
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

//#tryinclude <YSI\y_groups>

//#undef _YCM

// This is to allow callback chaining.  When the user includes y_groups and
// other libraries, the function names will be reset to their custom ones after
// every inclusion, however if you then include another YSI library you need to
// revert to the previous library names to get the chaining to work.  However I
// think this is completely pointless now thanks to "y_hooks".

//#define YSI_SET_LAST_GROUP 25
#include "internal\y_grouprevert"

// So we can use custom syntax on these two functions and allow command names to
// be sort of used...
//#define Group_SetCommand(%0,YCMD:%2,%3) Group_SetCommand(%0,Command_GetID(#%2),%3)
//#define Group_SetGlobalCommand(YCMD:%2,%3) Group_SetGlobalCommand(Command_GetID(#%2),%3)
