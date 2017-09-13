#if defined _INC_y_commands
	#endinput
#endif
#define _INC_y_commands

/**
<file>
					y_commands
</file>
<section>
	Description
</section>
	Runs commands registered with the system and calls the required functions.
	Also handles alternate names and prefixes.  Based very loosely on dcmd.
<section>
	Version
</section>
	0.1.4
<section>
	Changelog
</section><ul>
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
</ul><section>
	Functions
</section><ul>
<li><subsection>
Public
</subsection><ul>
	<entry name="Command_Add">Adds a command to the array for processing.</entry>
	<entry name="Command_Remove">Removes a command.</entry>
	<entry name="Command_Name">Gets the name of a command in a property.</entry>
</ul></li><li><subsection>
Core
</subsection><ul>
	<entry name="Command_Process">Called from OnPlayerCommandText to process entered commands.</entry>
	<entry name="Command_Parse">Sorts added commands into a binary tree.</entry>
	<entry name="Command_Hash">Hashes a word for command hashing.</entry>
	<entry name="Command_ProcRem">Processes a help command in the master script.</entry>
</ul></li><li><subsection>
Stock
</subsection><ul>
	<entry name="Command_SetDisconnectReturn">Sets the return value for unconnected players.</entry>
	<entry name="Command_UseShortCuts">Toggles use of per-player command shortcuts.</entry>
	<entry name="Command_SetDeniedReturn">Sets the return value for denied use commands.</entry>
	<entry name="Command_UseDeniedMessage">Toggles the use of an error message for denied.</entry>
	<entry name="Command_SetIllegalReturn">Sets the return value for illegal characters.</entry>
	<entry name="Command_UseAltNames">Toggles the use of ini defined alternate names.</entry>
	<entry name="Command_UsePrefix">Toggles the use of a global prefix.</entry>
	<entry name="Command_UseSpace">Toggles the use of a space between prefix and command.</entry>
	<entry name="Command_SetAltName">Sets the alternate name of a function.</entry>
	<entry name="Command_SetPrefix">Sets the pfexix to be typed.</entry>
	<entry name="Comamnd_SetPlayerUse">Sets wether or not a player can use a command.</entry>
	<entry name="Comamnd_SetPlayerUseByID">Sets wether or not a player can use a command.</entry>
	<entry name="Command_FindByName">Finds a command in a possibly sorted list.</entry>
</ul></li></ul><section>
	Definitions
</section><ul>
	<entry name="MAX_COMMAND_LENGTH">The maximum length of a command string.</entry>
	<entry name="COMMAND_NOT_FOUND">Indicates that a searched for string is not a function.</entry>
</ul><section>
	Enums
</section><ul>
	<entry name="e_COMM_FLAG">Bit mappings for command options.</entry>
	<entry name="E_COMMANDS">Structure of the array holding the string data.</entry>
</ul><section>
	Macros
</section><ul>
	<entry name="Command_(%1)">Forwards and declares a standard command for calling.</entry>
	<entry name="ycmd(%1)">Adds a command to the array (wrapper for Command_Add).</entry>
</ul><section>
	Tags
</section><ul>
	<entry name="e_COMM_FLAG">Flag type.</entry>
</ul><section>
	Variables
</section><ul>
<li><subsection>
Static
</subsection><ul>
	<entry name="YSI_g_sCommands">Holds all the textual data of the commands.</entry>
	<entry name="YSI_g_sSearchTree">Tree of hashes for function names.</entry>
	<entry name="YSI_g_sAltTree">Tree of hashes for alternate names.</entry>
	<entry name="YSI_g_sPrefix">The command prefix.</entry>
	<entry name="YSI_g_sPrefixLength">Length of the prefix.</entry>
	<entry name="YSI_g_sCommandIndex">Pointer to the next free index in the function array.</entry>
	<entry name="YSI_g_sAltCount">The number of commands with altnames.</entry>
	<entry name="YSI_g_sCommandFlags">Bit array of command options.</entry>
</ul></li></ul><section>
	Commands
</section><ul>
	<entry name="commands">Lists all commands available to you.</entry>
</ul><section>Compile options</section><ul>
	<entry name="COMMAND_SENSITIVE">Make commands case sensitive.</entry>
	<entry name="COMMAND_ACCURATE">Can use '@' in command names.</entry>
	<entry name="MAX_COMMANDS">The maximum number of commands which can be used.</entry>
</ul>
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

