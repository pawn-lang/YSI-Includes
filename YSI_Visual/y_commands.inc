#if defined _INC_y_commands
	#endinput
#endif
#define _INC_y_commands

/**
 * <library name="y_commands">
 * <section>
 *  Description
 * </section>
 *  Runs commands registered with the system and calls the required functions.
 *  Also handles alternate names and prefixes.  Based very loosely on dcmd.
 * <section>
 *  Version
 * </section>
 *  0.1.4
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="Command_Add">Adds a command to the array for processing.</symbol>
 *  <symbol name="Command_Remove">Removes a command.</symbol>
 *  <symbol name="Command_Name">Gets the name of a command in a property.</symbol>
 * </ul><subsection>
 * Core
 * </subsection><ul>
 *  <symbol name="Command_Process">Called from OnPlayerCommandText to process entered commands.</symbol>
 *  <symbol name="Command_Parse">Sorts added commands into a binary tree.</symbol>
 *  <symbol name="Command_Hash">Hashes a word for command hashing.</symbol>
 *  <symbol name="Command_ProcRem">Processes a help command in the master script.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Command_SetDisconnectReturn">Sets the return value for unconnected players.</symbol>
 *  <symbol name="Command_UseShortCuts">Toggles use of per-player command shortcuts.</symbol>
 *  <symbol name="Command_SetDeniedReturn">Sets the return value for denied use commands.</symbol>
 *  <symbol name="Command_UseDeniedMessage">Toggles the use of an error message for denied.</symbol>
 *  <symbol name="Command_SetIllegalReturn">Sets the return value for illegal characters.</symbol>
 *  <symbol name="Command_UseAltNames">Toggles the use of ini defined alternate names.</symbol>
 *  <symbol name="Command_UsePrefix">Toggles the use of a global prefix.</symbol>
 *  <symbol name="Command_UseSpace">Toggles the use of a space between prefix and command.</symbol>
 *  <symbol name="Command_SetAltName">Sets the alternate name of a function.</symbol>
 *  <symbol name="Command_SetPrefix">Sets the pfexix to be typed.</symbol>
 *  <symbol name="Comamnd_SetPlayerUse">Sets wether or not a player can use a command.</symbol>
 *  <symbol name="Comamnd_SetPlayerUseByID">Sets wether or not a player can use a command.</symbol>
 *  <symbol name="Command_FindByName">Finds a command in a possibly sorted list.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MAX_COMMAND_LENGTH">The maximum length of a command string.</symbol>
 *  <symbol name="COMMAND_NOT_FOUND">Indicates that a searched for string is not a function.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  <symbol name="e_COMM_FLAG">Bit mappings for command options.</symbol>
 *  <symbol name="E_COMMANDS">Structure of the array holding the string data.</symbol>
 * </ul><section>
 *  Macros
 * </section><ul>
 *  <symbol name="Command_(%1)">Forwards and declares a standard command for calling.</symbol>
 *  <symbol name="ycmd(%1)">Adds a command to the array (wrapper for Command_Add).</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="e_COMM_FLAG">Flag type.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_sCommands">Holds all the textual data of the commands.</symbol>
 *  <symbol name="YSI_g_sSearchTree">Tree of hashes for function names.</symbol>
 *  <symbol name="YSI_g_sAltTree">Tree of hashes for alternate names.</symbol>
 *  <symbol name="YSI_g_sPrefix">The command prefix.</symbol>
 *  <symbol name="YSI_g_sPrefixLength">Length of the prefix.</symbol>
 *  <symbol name="YSI_g_sCommandIndex">Pointer to the next free index in the function array.</symbol>
 *  <symbol name="YSI_g_sAltCount">The number of commands with altnames.</symbol>
 *  <symbol name="YSI_g_sCommandFlags">Bit array of command options.</symbol>
 * </ul><section>
 *  Commands
 * </section><ul>
 *  <symbol name="commands">Lists all commands available to you.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="COMMAND_SENSITIVE">Make commands case sensitive.</symbol>
 *  <symbol name="COMMAND_ACCURATE">Can use '@' in command names.</symbol>
 *  <symbol name="MAX_COMMANDS">The maximum number of commands which can be used.</symbol>
 * </ul>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#include "..\YSI_Internal\y_compilerdata"
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
#include "..\YSI_Data\y_hashmap"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Coding\y_hooks"
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

