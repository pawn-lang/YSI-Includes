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
		-
	Inline:
		-
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
\**--------------------------------------------------------------------------**/

#if defined _INC_y_commands
	#endinput
#endif
#define _INC_y_commands

#include "..\YSI_Internal\y_version"

#define MAX_COMMAND_LENGTH              (32)

#define COMMAND_NOT_FOUND               (-1)

#if !defined MAX_COMMANDS
	#define MAX_COMMANDS                (512)
#endif

// Set commands as master 25.
#define MASTER 63
#define YSIM_U_DISABLE
#include "..\YSI_Core\y_master"

// Misc includes.
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Coding\y_hooks"
#include "..\YSI_Data\y_hashmap"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Data\y_playerarray"
#include "..\YSI_Server\y_punycode"
#include "..\YSI_Internal\y_distribute"

// Include the group functions (maybe).
#define _GROUP_MAKE_NAME<%0...%1> %0Command%1
#define _GROUP_MAKE_LIMIT         MAX_COMMANDS
#include "..\YSI_Players\y_groups\_funcs"

#if defined YSI_TESTS
	#if !defined Y_COMMANDS_NO_IPC
		#define Y_COMMANDS_NO_IPC
	#endif
#endif

// Include the main implementation.
#include "y_commands/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_commands/tests"
#endif

// Restore previous settings.
#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME

#include "..\YSI_Core\y_master"

