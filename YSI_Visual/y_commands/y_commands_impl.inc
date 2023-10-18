/*
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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           

*/

enum e_COMMAND_FLAGS
{
	e_COMMAND_FLAG_PREFIX = 0xFF,
	// Inherit user permissions.
	e_COMMAND_FLAG_INHERIT = 0x01000000,
	// Can't be listed.
	e_COMMAND_FLAG_HIDDEN = 0x02000000,
	// Can't be used by default.
	e_COMMAND_FLAG_DISABLED = 0x04000000,
	// Is a primary.
	e_COMMAND_FLAG_PRI = 0x00000000,
	// Is an alternative.
	e_COMMAND_FLAG_ALT = 0x10000000,
	// Is an inline, or more strictly it is a per-player defined function called
	// via `indirection.inc`.  In this case the use of the permissions changes
	// to represent whether the player had a personal command with this name.
	// However, this data may become stale when you're using `EBC` as the
	// command may have stopped exsting another way in the interim.  To check
	// this we always need to iterate through the list of inlines to find the
	// one for this player, then check it is valid.
	e_COMMAND_FLAG_INLINE = 0x20000000,
	// A reference to the original command with this name.
	e_COMMAND_FLAG_PARENT = 0x0FFFFF,
	// Breakdown of the type specialisations.
	e_COMMAND_FLAG_ARGS_ISI = 0x000000,
	e_COMMAND_FLAG_ARGS_IS = 0x100000,
	e_COMMAND_FLAG_ARGS_S = 0x200000,
	e_COMMAND_FLAG_TYPE_INL = 0xC00000,
	e_COMMAND_FLAG_TYPE_PTR = 0x800000,
	e_COMMAND_FLAG_TYPE_STR = 0x400000,
	e_COMMAND_FLAG_TYPE_NRM = 0x000000,
	
	// If this is set this is a function that only takes a single string
	// parameter, and is an inline in the current script.  We do this so that we
	// can call that code way more directly, or at least slightly more directly,
	// since we still need to go through the inline handler.  And actually,
	// since we still need to go through the handler anyway to set up the stack
	// and frame we can short-circuit a few other calls as well - no need to
	// check if this is a pointer and no need to do any tag-based parameter
	// resolution.  Now expanded to special-case all the variants.
	e_COMMAND_FLAG_INL_ISI = e_COMMAND_FLAG_TYPE_INL | e_COMMAND_FLAG_ARGS_ISI,
	e_COMMAND_FLAG_INL_IS  = e_COMMAND_FLAG_TYPE_INL | e_COMMAND_FLAG_ARGS_IS,
	e_COMMAND_FLAG_INL_S   = e_COMMAND_FLAG_TYPE_INL | e_COMMAND_FLAG_ARGS_S,
	// Normal function pointer.
	e_COMMAND_FLAG_PTR_ISI = e_COMMAND_FLAG_TYPE_PTR | e_COMMAND_FLAG_ARGS_ISI,
	e_COMMAND_FLAG_PTR_IS  = e_COMMAND_FLAG_TYPE_PTR | e_COMMAND_FLAG_ARGS_IS,
	e_COMMAND_FLAG_PTR_S   = e_COMMAND_FLAG_TYPE_PTR | e_COMMAND_FLAG_ARGS_S,
	// String name.
	e_COMMAND_FLAG_STR_ISI = e_COMMAND_FLAG_TYPE_STR | e_COMMAND_FLAG_ARGS_ISI,
	e_COMMAND_FLAG_STR_IS  = e_COMMAND_FLAG_TYPE_STR | e_COMMAND_FLAG_ARGS_IS,
	e_COMMAND_FLAG_STR_S   = e_COMMAND_FLAG_TYPE_STR | e_COMMAND_FLAG_ARGS_S,
	// A normal command (actually works out as `0`).
	e_COMMAND_FLAG_NRM_ISI = e_COMMAND_FLAG_TYPE_NRM | e_COMMAND_FLAG_ARGS_ISI,
	// Mask for switches.
	e_COMMAND_FLAG_ARGS = 0x300000,
	e_COMMAND_FLAG_DEST = 0xC00000,
	e_COMMAND_FLAG_TYPE = e_COMMAND_FLAG_ARGS | e_COMMAND_FLAG_DEST
}

enum E_COMMAND
{
	// HASH_MAP_DATA<MAX_COMMAND_LENGTH char>,
	
	// Share a memory location with the hashmap stored name.
	E_COMMAND_NAME[MAX_COMMAND_LENGTH char] = 0,
	
	// IGNORE THESE, THEY COVER HASH MAP DATA.
	E_COMMAND_HASH_MAP[HASH_MAP_DATA],
	// _E_COMMAND_PAD_0, _E_COMMAND_PAD_1,
	
	// Who can use this command?  For inlines, the players currently with one.
	PlayerArray:E_COMMAND_USERS<MAX_PLAYERS>,
	// Meta-data.
	e_COMMAND_FLAGS:E_COMMAND_FLAGS,
	// Function pointer, or for inlines the index of the first entry to search.
	E_COMMAND_POINTER,
	// The base case for altnames.
	E_COMMAND_PARENT,
	// Circular linked list of the same name commands.
	E_COMMAND_NEXT
}

enum E_COMMAND_INLINE
{
	// The pointer.
	E_COMMAND_INLINE_POINTER,
	// The script that this callback is in.
	Bit:E_COMMAND_INLINE_MASTER,
	// Any special flags for this call.  We can use this to slightly optimise
	// the most common case of call.
	e_COMMAND_FLAGS:E_COMMAND_INLINE_FLAGS
}

enum e_COMMAND_ERRORS
{
	// The majority of these are even - odd numbers return "1" not "0".
	COMMAND_ZERO_RET      = 0 , // The command returned 0.
	COMMAND_OK            = 1 , // Called corectly.
	COMMAND_UNDEFINED     = 2 , // Command doesn't exist.
	COMMAND_DENIED        = 3 , // Can't use the command.
	COMMAND_HIDDEN        = 4 , // Can't use the command don't let them know it exists.
	COMMAND_NO_PLAYER     = 6 , // Used by a player who shouldn't exist.
	COMMAND_DISABLED      = 7 , // All commands are disabled for this player.
	COMMAND_BAD_PREFIX    = 8 , // Used "/" instead of "#", or something similar.
	COMMAND_INVALID_INPUT = 10, // Didn't type "/something".
	COMMAND_SILENT        = 11  // Just end.  Don't call the command or print anything.
}

enum e_SYSTEM_SETTINGS:
{
	// Space reserved for `e_COMMAND_ERRORS` return values.
	e_COMM_FLAG_RETURNS_ = 0x00000FFF,
	// Mark the script as having a punycode command.
	e_COMM_FLAG_PUNYCODE = 0x00008000,
	// Save counts for callbacks.
	e_COMM_FLAG_OPCP     = 0x00FF0000,
	e_COMM_FLAG_OPCP_ADD = 0x00010000,
	e_COMM_FLAG_OPCR     = 0xFF000000,
	e_COMM_FLAG_OPCR_ADD = 0x01000000
}

// Store which script(s) own which commands.
MASTER_DATA<MAX_COMMANDS>

// Information for returning error messages.
static stock __declspec(dist_tagged) e_SYSTEM_SETTINGS:YSI_g_sSystemSettings;
static stock __declspec(distributed) YSI_g_sErrorMessages[e_COMMAND_ERRORS][144];
// Who has had ALL their commands disabled?
static stock __declspec(dist_special) PlayerArray:YSI_g_sDisabledPlayers<MAX_PLAYERS>;

static stock
	YSI_g_sCodSize = 0,
	YSI_g_sCurrentID = COMMAND_NOT_FOUND,
	BitArray:YSI_g_sPrefixes<128>,
	YSI_g_sHighestID = 0,
	YSI_g_sReturnBuffer[YSI_MAX_STRING],
	// Quickly reference and store commands by name.
	HashMap:YSI_g_sCommandMap<>,
	// These two MUST be adjacent in memory.
	YSI_g_sCommandPrefix[4] = { '@', 'y', 'C', '_' },
	YSI_g_sCommandName[60],
	Iterator:YSI_g_sPlayerCmd<MAX_PLAYERS, MAX_COMMANDS>;

static stock __declspec(dist_master) YSI_g_sCommands[MAX_COMMANDS][E_COMMAND];
static stock __declspec(dist_master) YSI_g_sInlineCommands[MAX_COMMANDS][E_COMMAND_INLINE];

static stock const
	YSI_gscOPCR[] = "OnPlayerCommandReceived",
	YSI_gscOPCP[] = "OnPlayerCommandPerformed",
	YSI_gscCommand_FastCallS[] = "Command_FastCallS",
	YSI_gscCommand_FastCallIS[] = "Command_FastCallIS",
	YSI_gscCommand_FastCallISI[] = "Command_FastCallISI";

// Why are these parameters in a seemingly random order?  To reduce duplication
// in the number of specifier strings that we need.
forward Command_FastCallS(Func:func<s>, string:params[], master);
forward Command_FastCallIS(playerid, string:params[], master, Func:func<is>);
forward Command_FastCallISI(playerid, string:params[], help, master, Func:func<isi>);


/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   <c>funcidx</c> by pointer not name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native Command_FuncIDX(func) = funcidx;

// "YCMD:" macros.  The true core is "YSIM_COMMAND", which is in "y_master".
#define _YCMD_0:(_:_YCMD_1:_YCMD_2:_YCMD_3:%0(%1[]%2) YSIM_COMMAND %0(%1[]%2)
#define _YCMD_1:_YCMD_2:_YCMD_3:%0, Command_GetID(#%0)),
#define _YCMD_2:_YCMD_3:%0)  Command_GetID(#%0)))
#define _YCMD_3:%0;  Command_GetID(#%0));
#define @YCMD:%0;  Command_TouchNamed(#%0);

#define COMMAND__ YSIM_COMMAND
#if YSI_KEYWORD(YCMD)
	#define YCMD: _YCMD_0:(_:_YCMD_1:_YCMD_2:_YCMD_3:
#else
	// If we don't want the keyword, we still want the ID tag.
	#define YCMD: (_:_YCMD_1:_YCMD_2:_YCMD_3:
#endif

// ZCMD compatibility.
#define CMD:%0(%1) YSIM_COMMAND %0(%1,__help)if(__help)return 0;else
#define COMMAND CMD

// Alt commands:
#define _YCMD_4:_F<@yC_>%0(%9);%9(%9)%9;%9(%9);%9(%1)=%2; POSTINIT__%0(){Command_AddAltNamed(#%2,#%0);}
#define _YCMD_5:_F<@yC_>%0(%9);%9(%9)=%2; POSTINIT__%0(){Command_AddAltNamed(#%2,#%0);}

#define @_yC%0\32; @_yC
#define @y_C%0\32; @y_C
#define @yC_%0\32; @yC_
#define _@yC%0\32; _@yC
#define @C_y%0\32; @C_y

#define @_yC0000%0\32; @_yC0000
#define @y_C0000%0\32; @y_C0000
#define @yC_0000%0\32; @yC_0000
#define _@yC0000%0\32; _@yC0000
#define @C_y0000%0\32; @C_y0000

// Forwards for optional command callbacks.
forward e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success); 
forward e_COMMAND_ERRORS:OnPlayerCommandPerformed(playerid, cmdtext[], e_COMMAND_ERRORS:success); 

/*

    88b           d88                                                         
    888b         d888                                                         
    88`8b       d8'88                                                         
    88 `8b     d8' 88 ,adPPYYba,  ,adPPYba, 8b,dPPYba,  ,adPPYba,  ,adPPYba,  
    88  `8b   d8'  88 ""     `Y8 a8"     "" 88P'   "Y8 a8"     "8a I8[    ""  
    88   `8b d8'   88 ,adPPPPP88 8b         88         8b       d8  `"Y8ba,   
    88    `888'    88 88,    ,88 "8a,   ,aa 88         "8a,   ,a8" aa    ]8I  
    88     `8'     88 `"8bbdP"Y8  `"Ybbd8"' 88          `"YbbdP"'  `"YbbdP"'  

*/

//#define _Command_GetPlayer(%0,%1) (PA_Get(YSI_g_sCommands[(%0)][E_COMMAND_USERS], (%1)))

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="idx">Command to test.</param>
 * <remarks>
 *   Tests if the given slot is empty.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Command_IsEmptySlot(idx));
#define _Command_IsEmptySlot(%0) (!YSI_g_sCommands[(%0)][E_COMMAND_NAME])

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="idx">Command to test.</param>
 * <remarks>
 *   Tests if the given slot is an alternate command.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Command_IsAlt(idx));
#define _Command_IsAlt(%0) (YSI_g_sCommands[(%0)][E_COMMAND_POINTER] & cellmin)

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="error">Which error to show.</param>
 * <param name="playerid">Player who typed the command.</param>
 * <param name="cmdtext">What they typed.</param>
 * <remarks>
 *   Call OnPlayerCommandReceived once the system knows how the player can use
 *   this command (if they can).  The order of the parameters is such that the
 *   error comes first.  This is because it is compile-time concatenated to make
 *   the error enum value, and putting that parameter first means that we don't
 *   need to ommit the space after any comma.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Command_ErrorRet(%2) (YSI_g_sSystemSettings&e_SYSTEM_SETTINGS:(1<<_:(%2)-1))
#if defined COMMAND_USE_ERRORS
	
	#define Command_ErrorMsg(%2) YSI_g_sErrorMessages[%2]
	
	#if defined _Text_Send
		#define Command_Error(%0,%2) (Command_ErrorMsg(%2)[0]?(Text_Send((%0),Command_ErrorMsg(%2)),Command_ErrorRet(%2)):Command_ErrorRet(%2))
	#else
		#define Command_Error(%0,%2) (Command_ErrorMsg(%2)[0]?(SendClientMessage((%0),0xFF0000AA,Command_ErrorMsg(%2)),Command_ErrorRet(%2)):Command_ErrorRet(%2))
	#endif
#else
	#define Command_Error(%0,%2) Command_ErrorRet(%2)
#endif

#define Command_OnReceived(%2,%0,%1) ((YSI_g_sSystemSettings&e_COMM_FLAG_OPCR)?(e_COMMAND_ERRORS:W@(YSI_gscOPCR,YSI_gcISI,(%0),(%1),_:(%2))):(%2))

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to get for.</param>
 * <returns>
 *   Is this command ID active?
 * </returns>
 * <remarks>
 *   Doesn't do any bounds checks - use "_Command_IsValid" for that.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Command_IsActive(command));
#define _Command_IsActive(%0) (YSI_g_sCommands[(%0)][E_COMMAND_NAME])

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to get for.</param>
 * <returns>
 *   Is this command ID valid?
 * </returns>
 * <remarks>
 *   Internal direct-access check.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Command_IsValid(command));
#define _Command_IsValid(%0) (IS_IN_RANGE((%0), 0, MAX_COMMANDS) && _Command_IsActive(%0))

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to get for.</param>
 * <returns>
 *   Is this command ID a special inline representation?
 * </returns>
 * <remarks>
 *   Internal direct-access check.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Command_IsInline(command));
#define _Command_IsInline(%0) (YSI_g_sCommands[(%0)][E_COMMAND_FLAGS] & e_COMMAND_FLAG_INLINE)

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="idx">Command to test.</param>
 * <remarks>
 *   Checks to see if a character is a possible prefix character.  May use an
 *   unsigned comparison.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	#define _Command_IsPrefix(%0) (IS_IN_RANGE((%0), 0, 128) && Bit_Get(YSI_g_sPrefixes, (%0)))
#else
	#define _Command_IsPrefix(%0) ((%0) == '/')
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">Command to get.</param>
 * <returns>
 *   The prefix for this command.
 * </returns>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(_Command_GetPrefix(c));
#define _Command_GetPrefix(%0) (_:(YSI_g_sCommands[(%0)][E_COMMAND_FLAGS]&e_COMMAND_FLAG_PREFIX))

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="f">Command to get the name of.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Command_Name(f));
#define Command_Name(%0) (YSI_g_sCommands[(%0)][E_COMMAND_NAME])

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="function">Function name to find.</param>
 * <returns>
 *   The ID of the passed function.
 * </returns>
 * <remarks>
 *   -
 *
 * native Command_GetID(function[])
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_GetID(const string:function[]);

GLOBAL__ Command_GetID(const string:function[])
{
	Debug_Print2("Command_GetID called: \"%s\"", function);
	return Command_Find(function);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="oidx">The function this is an alternate to.</param>
 * <param name="cmd">The new name.</param>
 * <param name="inherit">Does the new command use the parent's permissions?</param>
 * <returns>
 *   The command's ID.  You can't do this:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("h", "ajuda");
 *   </code>
 *   
 *   The chaining won't work, only the top-level command will be used as a point
 *   of reference.  This code will run as if it were:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("help", "ajuda");
 *   </code>
 *   
 *   Previously this was done silently behind the scenes because it didn't
 *   matter - the externally observable effects were always the same.  However,
 *   it does matter now with permission inheritance, because these two things
 *   are different:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("h", "ajuda", true);
 *   </code>
 *   
 *   Vs:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("help", "ajuda", true);
 *   </code>
 *   
 *   In the first version you'd expect <c>/ajuda</c> to inherit the permissions
 *   of <c>/h</c>, which may be different to the permissions of <c>/help</c>.
 *   However, in the second (accurate) version <c>/ajuda</c> will inherit from
 *   <c>/help</c>, which may still be different to <c>/h</c>, thus not what you
 *   want.  Allowing the chaining of permissions is very simple code-wise, but
 *   until I see a demand for it, it isn't implemented.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_AddAlt__(oidx, const string:cmd[], bool:inherit);

GLOBAL__ Command_AddAlt__(oidx, const string:cmd[], bool:inherit)
{
	Debug_Print2("Command_AddAlt called: %d, %s, %d", oidx, cmd, inherit);
	if (!_Command_IsValid(oidx) || _Command_IsInline(oidx))
	{
		return COMMAND_NOT_FOUND;
	}
	// Check the pointer is valid.
	new
		hash,
		id = YSI_g_sCommands[oidx][E_COMMAND_POINTER];
	// The command we are pointing to is already an alternate for a third
	// command - point this new command at the parent.
	if (id & cellmin)
	{
		oidx = id & ~cellmin;
		if (_Command_IsInline(oidx))
		{
			return COMMAND_NOT_FOUND;
		}
		Debug_Warning("Command_AddAlt: Using grandparent for alternate `/%s`", cmd);
	}
	
	if ((id = Command_GetEmptySlot()) == COMMAND_NOT_FOUND)
	{
		Debug_Error("Could not add alt command to array.");
		return COMMAND_NOT_FOUND;
	}
	// Copy the master script information.  Note that this won't be kept up
	// to date with new scripts unfortunately.
	MASTER_COPY<id, oidx>
	// Save the command's pointer.
	oidx |= cellmin,
	YSI_g_sCommands[id][E_COMMAND_POINTER] = oidx;
	
	//if (strfind(cmd, "@") == -1)
	//{
	//	strpack(YSI_g_sCommandName, cmd, cellmax),
	//	hash = BernsteinHash(cmd);
	//}
	//else
	Puny_EncodeHash(YSI_g_sCommandName, cmd, hash, .delimiter = '@'),
	strpack(YSI_g_sCommandName, YSI_g_sCommandName, cellmax);
	Debug_Print5("Command_AddAlt: packed %s, %s", YSI_g_sCommandName, cmd);
	Debug_Print5("Command_AddAlt: unpacked %s, %s", Unpack(YSI_g_sCommandName), Unpack(cmd));
	if (strcmp(YSI_g_sCommandName, cmd))
	{
		// There is any punycode command.
		YSI_g_sSystemSettings |= e_COMM_FLAG_PUNYCODE;
	}

	// Add all players, or defer to y_groups.
	if (inherit)
	{
		YSI_g_sCommands[id][E_COMMAND_FLAGS] |= e_COMMAND_FLAG_INHERIT;
	}
	else
	{
		PA_FastInit(YSI_g_sCommands[id][E_COMMAND_USERS]);
		NO_GROUPS<Command>(id)
		{
			PA_Init(YSI_g_sCommands[id][E_COMMAND_USERS], true);
		}
	}

	// Now point this new command at the real (software) command.
	inherit = bool:HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash),
	YSI_g_sCommands[id][E_COMMAND_NEXT] = _:inherit;
	if (_:inherit != COMMAND_NOT_FOUND)
	{
		// There's another command with this name already.  Is it an existing
		// alt command pointing to exactly the same destination?
		do
		{
			if ((YSI_g_sCommands[_:inherit][E_COMMAND_FLAGS] & e_COMMAND_FLAG_ALT) && (YSI_g_sCommands[_:inherit][E_COMMAND_POINTER] == oidx))
			{
				// Yes - this is a special case of adding the same alt twice.
				// Do nothing except return the old ID.  By this point the new
				// slot has not been "committed", so we can just return and our
				// changes will not be persisted.
				return _:inherit;
			}
		}
		while ((_:inherit = YSI_g_sCommands[_:inherit][E_COMMAND_NEXT]) != COMMAND_NOT_FOUND);
		// Otherwise add us to the linked list of lookups for the name.
		HashMap_RemoveKeyWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash);
	}

	// This is the point at which the slot is marked as in use.  Returning
	// before this will not remove it from the available list.
	HashMap_AddWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash, id),
	// This sets the prefix even when that feature is disabled, because
	// there's literally no overhead in doing so.
	YSI_g_sCommands[id][E_COMMAND_FLAGS] = e_COMMAND_FLAG_ALT | (e_COMMAND_FLAGS:'/') | e_COMMAND_FLAG_NRM_ISI,
	// Save the new highest ID for loops later.
	YSI_g_sHighestID = max(YSI_g_sHighestID, id + 1);

	return id;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="oidx">The function this is an alternate to.</param>
 * <param name="cmd">The new name.</param>
 * <param name="inherit">Does the new command use the parent's permissions?</param>
 * <remarks>
 *   Add an alternate command for an existing command.  Switched to a wrapper
 *   so we can add a third optional parameter.  You can't do this:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("h", "ajuda");
 *   </code>
 *   
 *   The chaining won't work, only the top-level command will be used as a point
 *   of reference.  This code will run as if it were:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("help", "ajuda");
 *   </code>
 *   
 *   Previously this was done silently behind the scenes because it didn't
 *   matter - the externally observable effects were always the same.  However,
 *   it does matter now with permission inheritance, because these two things
 *   are different:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("h", "ajuda", true);
 *   </code>
 *   
 *   Vs:
 *   
 *   <code>
 *     Command_Add("help");
 *     Command_AddAlt("help", "h");
 *     Command_AddAlt("help", "ajuda", true);
 *   </code>
 *   
 *   In the first version you'd expect <c>/ajuda</c> to inherit the permissions
 *   of <c>/h</c>, which may be different to the permissions of <c>/help</c>.
 *   However, in the second (accurate) version <c>/ajuda</c> will inherit from
 *   <c>/help</c>, which may still be different to <c>/h</c>, thus not what you
 *   want.  Allowing the chaining of permissions is very simple code-wise, but
 *   until I see a demand for it, it isn't implemented.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Command_AddAlt(oidx, const string:cmd[], bool:inherit = false)
{
	return Command_AddAlt__(oidx, cmd, inherit);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="owner">The owning entity for EBC callbacks.</param>
 * <param name="ptr">The inline itself.</param>
 * <returns>
 *   -
 * </returns>
 * <remarks>
 *   This handles the remote cleanup.  An owner of <c>cellmin</c> means "always"
 *   while an owner of <c>-1</c> means "if invalid".
 * </remarks>
 *//*------------------------------------------------------------------------**/

REMOTE_FUNC__ bool:Command_TryRelease__(owner, ptr)
{
	switch (owner)
	{
	case cellmin:
		{}
	case -1:
		if (Indirect_IsValid(ptr)) return false;
	default:
		if (Indirect_GetOwner(ptr) != owner) return false;
	}
	Indirect_Release(owner);
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="p">(playerid) - Player who entered the command.</param>
 * <param name="c">(cmdtext) - Text entered.</param>
 * <param name="h">
 *   1 - Called from the help commmand or OnPlayerCommandText.
 *   2 - Bypass permissions checks.
 * </param>
 * <returns>
 *   true - success or hidden fail.
 *   false - fail.
 * </returns>
 * <remarks>
 *   Does all the command and error handling.  The macro version takes four
 *   parameters:
 *
 *   <code>Command_ReProcess(playerid,cmdtext,help,force);</code>
 *
 *   <c>help</c> and <c>force</c> are combined together in to a bitmap.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock e_COMMAND_ERRORS:Command_ReProcess__(playerid, const string:cmdtext[], help)
{
	Debug_Print1("Commands_OnPlayerCommandText called: %d %s", playerid, cmdtext);
	// Check for a valid player.
	#if !defined Y_COMMANDS_NO_IPC
		if (!IsPlayerConnected(playerid))
		{
			return Command_OnReceived(COMMAND_NO_PLAYER, playerid, cmdtext);
		}
	#endif
	const
		Func:tagS<s> = Func:0<s>,
		Func:tagIS<is> = Func:0<is>,
		Func:tagISI<isi> = Func:0<isi>;
	// Apparently being using in `tagof` doesn't mark them as used (which is
	// somewhat understandable, that's usually a mistake).
	#pragma unused tagS, tagIS, tagISI
	static
		sPos = 0,
		e_COMMAND_ERRORS:sRet = COMMAND_OK,
		sHash = 0,
		e_COMMAND_FLAGS:sFlags = e_COMMAND_FLAGS:0;
	// Skip whitespace.
	new
		prefix = cmdtext[0];
	if (!(sRet = e_COMMAND_ERRORS:_Command_IsPrefix(prefix)))
	{
		prefix = '\0';
	}
	while (cmdtext[sRet] == ' ') ++sRet;
	if (0 <= cmdtext[sRet] <= 1)
	{
		return Command_OnReceived(COMMAND_INVALID_INPUT, playerid, cmdtext);
	}
	if (PA_Get(YSI_g_sDisabledPlayers, playerid))
	{
		if ((sRet = Command_OnReceived(COMMAND_DISABLED, playerid, cmdtext)) != COMMAND_OK)
			return sRet;
	}
	// Get the hashed version of the decoded string, skipping the possible  "/".
	if (YSI_g_sSystemSettings & e_COMM_FLAG_PUNYCODE)
	{
		sPos = Puny_EncodeHash(YSI_g_sCommandName, cmdtext[_:sRet], sHash, sizeof (YSI_g_sCommandName), '@') + _:sRet;
	}
	else
	{
		sPos = sRet,
		sHash = 5381;
		while ((_:sFlags = cmdtext[sPos]) > ' ')
		{
			YSI_g_sCommandName[sPos - _:sRet] = _:sFlags,
			sHash = sHash * 33 ^ _:sFlags,
			++sPos;
		}
	}
	// Skip whitespace.
	while (cmdtext[sPos] == ' ') ++sPos; // Better/slower: ('\0' < cmdtext[sPos] <= ' ').
	// Find the command in the array.
	YSI_g_sCurrentID = HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, sHash);
	Debug_Print5("Commands_OnPlayerCommandText: %s, %d, %d, %d", YSI_g_sCommandName, sPos, sHash, YSI_g_sCurrentID);
	if (YSI_g_sCurrentID == COMMAND_NOT_FOUND)
	{
		return Command_OnReceived(COMMAND_UNDEFINED, playerid, cmdtext);
	}
	// Loop through all the commands with this name and find the first one that
	// this player can use.
	for ( ; ; )
	{
		#if defined Y_COMMANDS_USE_CHARS
			// Have a prefix, but not the right one.  Calling this function
			// directly always works for all possible command prefixes.
			if (prefix && _Command_GetPrefix(YSI_g_sCurrentID) != prefix)
			{
				if ((YSI_g_sCurrentID = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_NEXT]) == COMMAND_NOT_FOUND)
					return Command_OnReceived(COMMAND_BAD_PREFIX, playerid, cmdtext);
			}
		#endif
		//Debug_Print5("Commands_OnPlayerCommandText: Use %d", _Command_GetPlayer(YSI_g_sCurrentID, playerid));
		// Can the player use this command?
		sHash = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_POINTER],
		sFlags = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_FLAGS];
		switch (sFlags & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
		{
		case e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_INHERIT:
		{
			// Disabled primary commands.
			if ((sRet = Command_OnReceived((help & 2) ? COMMAND_OK : COMMAND_DENIED, playerid, cmdtext)) == COMMAND_OK)
				break;
		}
		case e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// Disabled alternate commands.  We still get the primary as the call
			// to `Command_OnReceived` may result in it being called.
			if ((sRet = Command_OnReceived((help & 2) ? COMMAND_OK : COMMAND_DENIED, playerid, cmdtext)) == COMMAND_OK)
			{
				YSI_g_sCurrentID = sHash & ~cellmin,
				sHash = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_POINTER];
				break;
			}
		}
		case e_COMMAND_FLAG_ALT:
		{
			// Alternate command with its own permissions.
			sRet = (help & 2) || PA_Get(YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_USERS], playerid) ? COMMAND_OK : COMMAND_DENIED;
			if ((sRet = Command_OnReceived(sRet, playerid, cmdtext)) == COMMAND_OK)
			{
				YSI_g_sCurrentID = sHash & ~cellmin,
				sHash = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_POINTER];
				break;
			}
		}
		case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// Alternate command with inherited permissions.
			sRet = (help & 2) || PA_Get(YSI_g_sCommands[sHash & ~cellmin][E_COMMAND_USERS], playerid) ? COMMAND_OK : COMMAND_DENIED;
			if ((sRet = Command_OnReceived(sRet, playerid, cmdtext)) == COMMAND_OK)
			{
				YSI_g_sCurrentID = sHash & ~cellmin,
				sHash = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_POINTER];
				break;
			}
		}
		case e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_INHERIT:
		{
			// Technically `e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_INHERIT` is an
			// invalid combination, but don't worry about that here.
			sRet = (help & 2) || PA_Get(YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_USERS], playerid) ? COMMAND_OK : COMMAND_DENIED;
			if ((sRet = Command_OnReceived(sRet, playerid, cmdtext)) == COMMAND_OK)
				break;
		}
		default:
		{
			// This is an indirect function, defined for a single player.  The
			// `help & 2` above will override normal permissions to allow you to
			// call any command for any player, but these commands don't have
			// permissions, they literally don't exist for other players.
			sRet = COMMAND_UNDEFINED;
			FOREACH__ (sHash : YSI_g_sPlayerCmd<playerid>)
			{
				sFlags = YSI_g_sInlineCommands[sHash][E_COMMAND_INLINE_FLAGS];
				if (_:(sFlags & e_COMMAND_FLAG_PARENT) == YSI_g_sCurrentID)
				{
						sRet = e_COMMAND_ERRORS:YSI_g_sInlineCommands[sHash][E_COMMAND_INLINE_POINTER];
						// Found it.
					#if YSIM_HAS_MASTER
						// Fake the master data so that the correct script is used.
						YSI_g_sMasterData[YSI_g_sCurrentID] = YSI_g_sInlineCommands[sHash][E_COMMAND_INLINE_MASTER];
						if (MASTER_EXCLUSIVE<YSI_g_sCurrentID>)
					#endif
						{
							if (Indirect_IsValid(_:sRet))
							{
								sHash = _:sRet,
								sRet = COMMAND_OK;
								break;
							}
							else
							{
								// Release any dangling pointers.
								Indirect_Release(_:sRet),
								Iter_Remove(YSI_g_sPlayerCmd<playerid>, sHash),
								sRet = COMMAND_DENIED;
							}
						}
					#if YSIM_HAS_MASTER
						else
						{
							if (TARGET_FUNC__ Command_TryRelease__<_:YSI_g_sMasterData[YSI_g_sCurrentID]>(-1, _:sRet))
							{
								// Release any dangling pointers.
								Iter_Remove(YSI_g_sPlayerCmd<playerid>, sHash),
								sRet = COMMAND_DENIED;
							}
							else
							{
								sHash = _:sRet,
								sRet = COMMAND_OK;
								break;
							}
						}
					#endif
				}
			}
			// We must confirm that the command was actually found first.
			if (sRet == COMMAND_DENIED)
			{
				// A command was removed, and no alternative was found.
				PA_Set(YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_USERS], playerid, false),
				sRet = COMMAND_UNDEFINED;
			}
			else if (sRet == COMMAND_OK && (sRet = Command_OnReceived(COMMAND_OK, playerid, cmdtext)) == COMMAND_OK)
				break;
		}
		}
		if ((YSI_g_sCurrentID = YSI_g_sCommands[YSI_g_sCurrentID][E_COMMAND_NEXT]) == COMMAND_NOT_FOUND)
			return sRet;
	}
	Debug_Print5("Commands_OnPlayerCommandText: Read %d", YSI_g_sCurrentID);
	Debug_Print5("Commands_OnPlayerCommandText: Master %d %d", Master_ID(), _:MASTER_GET<YSI_g_sCurrentID>);
	#if YSIM_HAS_MASTER
		if (MASTER_EXCLUSIVE<YSI_g_sCurrentID>)
	#endif
		{
			Debug_Print5("Commands_OnPlayerCommandText: Local %08x %08x (%d, \"%s\", %d)", sFlags, sHash, playerid, cmdtext[sPos], help & 1);
			// In this script.  More to the point, in ONLY this script, so
			// we can't have another script as the master.  I tried updating
			// this code but then realised that the update would ignore the
			// case where a command was in both the current script and
			// another script, but the other script was the master script.
			static
				sParams[144];
			sParams[0] = '\0',
			strcat(sParams, cmdtext[sPos]),
			// Strip out all other flags.
			help &= 1;
			//sRet = Command_FastCall(sFlags, sHash, playerid, sParams, bool:(help & 1), true);
			//Debug_Print4("Command_FastCall called: %08x, %08x, %d, \"%s\", %d, %d", _:flags, func, playerid, params, help, unique);
			//#pragma unused params
			// `params` is NOT `const` here.  This is NOT a mistake.  I mean...
			// ultimately it IS a mistake, since it is done that way to account
			// for commands themselves not having `const` parameters.  But
			// beyond that, no.
			// Only call this in the correct script.
			switch (sFlags & e_COMMAND_FLAG_TYPE)
			{
			case e_COMMAND_FLAG_INL_ISI:
			{
				Debug_Print5("Command_FastCall: Type INL_ISI %08x %08x", sHash, AMX_Read(sHash - YSI_g_sCodSize + E_INDIRECTION_HANDER__));
				INDIRECTION_DATA = sHash - YSI_g_sCodSize,
				//INDIRECTION_TAG = tagof(tagISI),
				sHash = AMX_Read(INDIRECTION_DATA + E_INDIRECTION_HANDER__);
				#emit PUSH.ADR     help
				#emit PUSH.C       sParams
				#emit PUSH.ADR     playerid
				#emit PUSH.C       __3_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_INL_IS:
			{
				Debug_Print5("Command_FastCall: Type INL_IS %08x %08x", sHash, AMX_Read(sHash - YSI_g_sCodSize + E_INDIRECTION_HANDER__));
				INDIRECTION_DATA = sHash - YSI_g_sCodSize,
				//INDIRECTION_TAG = tagof(tagIS),
				sHash = AMX_Read(INDIRECTION_DATA + E_INDIRECTION_HANDER__);
				#emit PUSH.C       sParams
				#emit PUSH.ADR     playerid
				#emit PUSH.C       __2_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_INL_S:
			{
				Debug_Print5("Command_FastCall: Type INL_S %08x %08x", sHash, AMX_Read(sHash - YSI_g_sCodSize + E_INDIRECTION_HANDER__));
				INDIRECTION_DATA = sHash - YSI_g_sCodSize,
				//INDIRECTION_TAG = tagof(tagS),
				sHash = AMX_Read(INDIRECTION_DATA + E_INDIRECTION_HANDER__);
				#emit PUSH.C       sParams
				#emit PUSH.C       __1_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_PTR_ISI:
			{
				Debug_Print5("Command_FastCall: Type PTR_ISI");
				#emit PUSH.S       help
				#emit PUSH.C       sParams
				#emit PUSH.S       playerid
				#emit PUSH.C       __3_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_PTR_IS:
			{
				Debug_Print5("Command_FastCall: Type PTR_IS");
				#emit PUSH.C       sParams
				#emit PUSH.S       playerid
				#emit PUSH.C       __2_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_PTR_S:
			{
				Debug_Print5("Command_FastCall: Type PTR_S");
				#emit PUSH.C       sParams
				#emit PUSH.C       __1_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_STR_ISI:
			{
				Debug_Print5("Command_FastCall: Type STR_ISI");
				if ((sHash = Command_FuncIDX(sHash - YSI_g_sCodSize)) == -1)
				{
					return COMMAND_UNDEFINED;
				}
				sHash = AMX_Read(sHash * __defsize_cells + AMX_HEADER_PUBLICS);
				#emit PUSH.S       help
				#emit PUSH.C       sParams
				#emit PUSH.S       playerid
				#emit PUSH.C       __3_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_STR_IS:
			{
				Debug_Print5("Command_FastCall: Type STR_IS");
				if ((sHash = Command_FuncIDX(sHash - YSI_g_sCodSize)) == -1)
				{
					return COMMAND_UNDEFINED;
				}
				sHash = AMX_Read(sHash * __defsize_cells + AMX_HEADER_PUBLICS);
				#emit PUSH.C       sParams
				#emit PUSH.S       playerid
				#emit PUSH.C       __2_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_STR_S:
			{
				Debug_Print5("Command_FastCall: Type STR_S");
				if ((sHash = Command_FuncIDX(sHash - YSI_g_sCodSize)) == -1)
				{
					return COMMAND_UNDEFINED;
				}
				#emit PUSH.C       sParams
				#emit PUSH.C       __1_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			case e_COMMAND_FLAG_NRM_ISI:
			{
				Debug_Print5("Command_FastCall: Type NRM_ISI");
				#emit PUSH.S       help
				#emit PUSH.C       sParams
				#emit PUSH.S       playerid
				#emit PUSH.C       __3_cells
				#emit LCTRL        __cip
				#emit ADD.C        __11_cells
				#emit LCTRL        __jit_jump
				#emit PUSH.pri
				#emit LOAD.pri     sHash
				#emit SCTRL        __jit_jump
				#emit SCTRL        __cip
				#emit STOR.pri     sRet
			}
			// Does nothing
			default:
			{
				return COMMAND_UNDEFINED;
			}
			}
		}
	#if YSIM_HAS_MASTER
		else if (sFlags & e_COMMAND_FLAG_DEST == e_COMMAND_FLAG_TYPE_NRM)
		{
			Debug_Print5("Commands_OnPlayerCommandText: Normal %08x %08x (%d, \"%s\", %d)", sFlags, sHash, playerid, cmdtext[sPos], help & 1);
			// This is in another script, or multiple scripts.
			// Call the command in another script.  If no particular script
			// is set up as the "master", call it in the first one found...
			// Using `YSI_g_sCommandPrefix` here has a buffer overflow in to
			// `YSI_g_sCommandName`, which is what we want.
			if (cmdtext[sPos])
				YSI_CallRemoteFunction__(YSI_g_sCommandPrefix, YSI_gcISII, playerid, cmdtext[sPos], help & 1, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>));
			else
				YSI_CallRemoteFunction__(YSI_g_sCommandPrefix, YSI_gcISII, playerid, NULL, help & 1, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>));
			sRet = e_COMMAND_ERRORS:getproperty(8, YSIM_RETURN);
		}
		else switch (sFlags & e_COMMAND_FLAG_ARGS)
		{
		case e_COMMAND_FLAG_ARGS_IS:
		{
			Debug_Print5("Commands_OnPlayerCommandText: Inline IS %08x %08x (%d, \"%s\", %d)", sFlags, sHash, playerid, cmdtext[sPos], help & 1);
			if (cmdtext[sPos])
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallIS, YSI_gcISII, playerid, cmdtext[sPos], Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>), sHash);
			else
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallIS, YSI_gcISII, playerid, NULL, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>), sHash);
			sRet = e_COMMAND_ERRORS:getproperty(8, YSIM_RETURN);
		}
		case e_COMMAND_FLAG_ARGS_S:
		{
			Debug_Print5("Commands_OnPlayerCommandText: Inline S %08x %08x (%d, \"%s\", %d)", sFlags, sHash, playerid, cmdtext[sPos], help & 1);
			if (cmdtext[sPos])
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallS, YSI_gcISI, sHash, cmdtext[sPos], Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>));
			else
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallS, YSI_gcISI, sHash, NULL, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>));
			sRet = e_COMMAND_ERRORS:getproperty(8, YSIM_RETURN);
		}
		case e_COMMAND_FLAG_ARGS_ISI:
		{
			Debug_Print5("Commands_OnPlayerCommandText: Inline ISI %08x %08x (%d, \"%s\", %d)", sFlags, sHash, playerid, cmdtext[sPos], help & 1);
			if (cmdtext[sPos])
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallISI, YSI_gcISIII, playerid, cmdtext[sPos], help & 1, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>), sHash);
			else
				YSI_CallRemoteFunction__(YSI_gscCommand_FastCallISI, YSI_gcISIII, playerid, NULL, help & 1, Cell_GetLowestBit(_:MASTER_GET<YSI_g_sCurrentID>), sHash);
			sRet = e_COMMAND_ERRORS:getproperty(8, YSIM_RETURN);
		}
		default:
		{
			return COMMAND_UNDEFINED;
		}
		}
	#endif
	Debug_Print5("Command_ReProces: Result = %d %d %d", _:sRet, Command_ErrorRet(sRet), _:COMMAND_OK);
	if (YSI_g_sSystemSettings & e_COMM_FLAG_OPCP)
		sRet = e_COMMAND_ERRORS:YSI_CallRemoteFunction__(YSI_gscOPCP, YSI_gcISI, playerid, cmdtext, _:sRet);
	Debug_Print5("Command_ReProces: Return = %d %d %d", playerid, _:sRet, Command_ErrorRet(sRet));
	return sRet;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">The player to run the script for.</param>
 * <param name="cmdtext">The script.</param>
 * <returns>
 *   true - success or hidden fail.
 *   false - fail.
 * </returns>
 * <remarks>
 *   Run a series of commands separated by <c>;</c>s.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_RunScript(playerid, const string:cmdtext[]);

GLOBAL__ bool:Command_RunScript(playerid, const string:cmdtext[])
{
	for (new end = -1, start = cellmax; start; )
	{
		end = strfind(cmdtext, ";", false, (start = end + 1));
		// `Command_ReProcess__` doesn't expect leading spaces, and shouldn't
		// really.  So deal with them here.
		while ('\0' < cmdtext[start] <= ' ')
		{
			++start;
		}
		if (end == -1)
		{
			return Command_ReProcess__(playerid, cmdtext[start], 0) == COMMAND_OK;
		}
		else
		{
			_YSI_ConstMod(cmdtext[end], '\0'),
			start = Command_ReProcess__(playerid, cmdtext[start], 0) == COMMAND_OK,
			_YSI_ConstMod(cmdtext[end], ';');
		}
	}
	
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="p">(playerid) - Player who entered the command.</param>
 * <param name="c">(cmdtext) - Text entered.</param>
 * <param name="h">
 *   1 - Called from the help commmand or OnPlayerCommandText.
 *   2 - Bypass permissions checks.
 * </param>
 * <returns>
 *   true - success or hidden fail.
 *   false - fail.
 * </returns>
 * <remarks>
 *   Does all the command and error handling.  The macro version takes four
 *   parameters:
 *
 *   <code>Command_ReProcess(playerid,cmdtext,help,force);</code>
 *
 *   <c>help</c> and <c>force</c> are combined together in to a bitmap.
 * </remarks>
 *//*------------------------------------------------------------------------**/

//FUNC_PAWNDOC(Command_ReProcess(playerid,cmdtext,help,force));
#define Command_ReProcess(%0,%1,%2,%3) Command_ReProcess(%0,%1, _:(%2)|(_:(%3)<<1))

FOREIGN__ Command_ReProcess(p,const string:c[],h);

GLOBAL__ Command_ReProcess(p,const string:c[],h)
{
	new
		e_COMMAND_ERRORS:sErr = Command_ReProcess__(p, c, h);
	return Command_Error(playerid, sErr);
}

/*

    88888888ba                                          88                     88                                    
    88      "8b                                         ""                     ""                                    
    88      ,8P                                                                                                      
    88aaaaaa8P' ,adPPYba, 8b,dPPYba, 88,dPYba,,adPYba,  88 ,adPPYba, ,adPPYba, 88  ,adPPYba,  8b,dPPYba,  ,adPPYba,  
    88""""""'  a8P_____88 88P'   "Y8 88P'   "88"    "8a 88 I8[    "" I8[    "" 88 a8"     "8a 88P'   `"8a I8[    ""  
    88         8PP""""""" 88         88      88      88 88  `"Y8ba,   `"Y8ba,  88 8b       d8 88       88  `"Y8ba,   
    88         "8b,   ,aa 88         88      88      88 88 aa    ]8I aa    ]8I 88 "8a,   ,a8" 88       88 aa    ]8I  
    88          `"Ybbd8"' 88         88      88      88 88 `"YbbdP"' `"YbbdP"' 88  `"YbbdP"'  88       88 `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The ID of the command to disable.</param>
 * <param name="e">Should it be disabled?.</param>
 * <remarks>
 *   Enable or disable the command.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetDisabled(c, bool:e);

GLOBAL__ void:Command_SetDisabled(c, bool:e)
{
	if (_Command_IsValid(c))
	{
		if (e)
			YSI_g_sCommands[c][E_COMMAND_FLAGS] |= e_COMMAND_FLAG_DISABLED;
		else
			YSI_g_sCommands[c][E_COMMAND_FLAGS] &= ~e_COMMAND_FLAG_DISABLED;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The ID of the command to look up.</param>
 * <returns>Is the command disabled?</returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetDisabled(c);

GLOBAL__ bool:Command_GetDisabled(c)
{
	return _Command_IsValid(c) && YSI_g_sCommands[c][E_COMMAND_FLAGS] & e_COMMAND_FLAG_DISABLED;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The ID of the command to hide.</param>
 * <param name="e">Should it be hidden?.</param>
 * <remarks>
 *   Hide or unhide the command.  Meaning it can be used, but not listed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetHidden(c, bool:e);

GLOBAL__ void:Command_SetHidden(c, bool:e)
{
	if (_Command_IsValid(c))
	{
		if (e)
			YSI_g_sCommands[c][E_COMMAND_FLAGS] |= e_COMMAND_FLAG_HIDDEN;
		else
			YSI_g_sCommands[c][E_COMMAND_FLAGS] &= ~e_COMMAND_FLAG_HIDDEN;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The ID of the command to look up.</param>
 * <returns>Is the command hidden?</returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetHidden(c);

GLOBAL__ bool:Command_GetHidden(c)
{
	return _Command_IsValid(c) && YSI_g_sCommands[c][E_COMMAND_FLAGS] & e_COMMAND_FLAG_HIDDEN;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">Player to set.</param>
 * <param name="set">Can they use any commands at all.</param>
 * <remarks>
 *   Enables or disables using commands for this player.  Enabling commands does
 *   not enable ALL commands, just allows them to use the ones for which they
 *   have otherwise set permissions.  Disabling prevents them from using ANY
 *   commands at all (though this can be overridden by returning
 *   <c>COMMAND_OK</c> in <c>OnPlayerCommandReceived</c>).
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetPlayerDisabled(playerid, bool:set);

GLOBAL__ void:Command_SetPlayerDisabled(playerid, bool:set)
{
	PA_Set(YSI_g_sDisabledPlayers, playerid, set);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">Player to get.</param>
 * <returns>
 *   Can this player use any commands?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetPlayerDisabled(playerid);

GLOBAL__ bool:Command_GetPlayerDisabled(playerid)
{
	return PA_Get(YSI_g_sDisabledPlayers, playerid);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to get for.</param>
 * <param name="playerid">Player to get.</param>
 * <returns>
 *   Can this player use this command?
 * </returns>
 * <remarks>
 *   Returns <c>true</c> if a player can use a command, but the command is
 *   hidden.  Meanwhile, the inbuilt loops will not return the command.  This
 *   gives a way to truly see the underlying information.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetPlayer(cmd, pid);

GLOBAL__ bool:Command_GetPlayer(cmd, pid)
{
	Debug_Print2("Command_GetPlayer called: %i, %i", cmd, pid);
	if (_Command_IsValid(cmd) && VALID_PLAYERID(pid))
	{
		Debug_Print5("Command_GetPlayer: valid");
		switch (YSI_g_sCommands[cmd][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
		{
		case e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_INLINE:
		{
			// Primary command that isn't indirect or disabled.
			// Alternate command that isn't inherited or disabled.
			return PA_Get(YSI_g_sCommands[cmd][E_COMMAND_USERS], pid);
		}
		case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// Alternate command that is inherited.  Use the parent.
			return PA_Get(YSI_g_sCommands[YSI_g_sCommands[cmd][E_COMMAND_POINTER] & ~cellmin][E_COMMAND_USERS], pid);
		}
		default:
		{
			return false;
		}
		}
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="funcname">Command to get for.</param>
 * <param name="playerid">Player to get.</param>
 * <remarks>
 *   Like Command_GetPlayer but for a function name.
 *
 * native bool:Command_GetPlayerNamed(funcname[], playerid);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetPlayerNamed(const string:func[], playerid);

GLOBAL__ bool:Command_GetPlayerNamed(const string:func[], playerid)
{
	return Command_GetPlayer(Command_Find(func), playerid);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to set for.</param>
 * <param name="playerid">Player to set.</param>
 * <param name="set">Wether or not this player can use this command.</param>
 * <remarks>
 *
 * native bool:Command_SetPlayer(command, playerid, bool:set);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetPlayer(c, p, bool:s);

GLOBAL__ void:Command_SetPlayer(c, p, bool:s)
{
	Debug_Print2("Command_SetPlayer called: %i, %i, %i", c, p, s);
	if (_Command_IsValid(c) && !_Command_IsInline(c) && VALID_PLAYERID(p))
	{
		Debug_Print5("Command_SetPlayer: valid");
		PA_Set(YSI_g_sCommands[c][E_COMMAND_USERS], p, s);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="funcname">Command to set for.</param>
 * <param name="playerid">Player to set.</param>
 * <param name="set">Wether or not this player can use this command.</param>
 * <remarks>
 *   Like Command_SetPlayer but for a function name.
 *
 * native bool:Command_SetPlayerNamed(funcname[], playerid, bool:set);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetPlayerNamed(const string:f[],p,bool:s);

GLOBAL__ void:Command_SetPlayerNamed(const string:f[],p,bool:s)
{
	Debug_Print2("Command_SetPlayerNamed called: %s, %i, %i", f, p, s);
	Command_SetPlayer(Command_Find(f), p, s);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="cmd">The command name to find.</param>
 * <param name="playerid">Whose permissions to check or <c>INVALID_PLAYER_ID</c>.</param>
 * <returns>
 *   The ID, or <c>ID | cellmin</c> for inline commands, or
 *   <c>COMMAND_NOT_FOUND</c> if there isn't one.  Returns "true" commands if
 *   possible, i.e. not alts if both exist.
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock Command_Find__(const string:cmd[], playerid)
{
	new
		id,
		candidate = COMMAND_NOT_FOUND;
	if (YSI_g_sSystemSettings & e_COMM_FLAG_PUNYCODE)
	{
		new
			encoded[64],
			hash;
		Puny_EncodeHash(encoded, cmd, hash, sizeof (encoded), '@'),
		id = HashMap_GetWithHash(YSI_g_sCommandMap, encoded, hash);
	}
	else
	{
		id = HashMap_Get(YSI_g_sCommandMap, cmd);
	}
	Debug_Print4("Command_Find__ called: %s, %d, %d, %d", cmd, playerid, alts, id);
	if (id == COMMAND_NOT_FOUND)
	{
		return COMMAND_NOT_FOUND;
	}
	// Loop through all the commands with this name and find the first one that
	// this player can use.
	do
	{
		switch (YSI_g_sCommands[id][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
		{
		case e_COMMAND_FLAG_DISABLED, e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INHERIT:
		{
			// These are only disabled for players, not if we test globally.
			// `e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INHERIT` should be
			// invalid, but don't fail this code just in case.
			if (playerid == INVALID_PLAYER_ID)
				candidate = id;
		}
		case e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// These are only disabled for players, not if we test globally.
			if (candidate == COMMAND_NOT_FOUND && playerid == INVALID_PLAYER_ID)
				candidate = id;
		}
		case e_COMMAND_FLAG_ALT:
		{
			// Alternate command with its own permissions.
			if (candidate == COMMAND_NOT_FOUND && (playerid == INVALID_PLAYER_ID || PA_Get(YSI_g_sCommands[id][E_COMMAND_USERS], playerid)))
				candidate = id;
		}
		case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// Alternate command with inherited permissions.
			if (candidate == COMMAND_NOT_FOUND && (playerid == INVALID_PLAYER_ID || PA_Get(YSI_g_sCommands[YSI_g_sCommands[id][E_COMMAND_POINTER] & ~cellmin][E_COMMAND_USERS], playerid))
				candidate = id;
		}
		case e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_INHERIT, e_COMMAND_FLAG_PRI:
		{
			// No flags (or only `e_COMMAND_FLAG_INHERIT` on a base command).
			if (playerid == INVALID_PLAYER_ID || PA_Get(YSI_g_sCommands[id][E_COMMAND_USERS], playerid))
				candidate = id;
		}
		default:
		{
			// Anything inline.  Only matters for players.
			if (candidate == COMMAND_NOT_FOUND && VALID_PLAYERID(playerid) && PA_Get(YSI_g_sCommands[id][E_COMMAND_USERS], playerid))
			{
				// This player has an inline in the list so find it.  Also there
				// isn't a better option already.  We loop through all the per-
				// player commands for this player and check if any of the point
				// to the current ID as their parent.
				FOREACH__ (candidate : YSI_g_sPlayerCmd<playerid>)
				{
					if (_:(YSI_g_sInlineCommands[candidate][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == id)
					{
						// Found it.
						candidate = id;
						break;
					}
				}
			}
		}
		}
	}
	while ((id = YSI_g_sCommands[id][E_COMMAND_NEXT]) != COMMAND_NOT_FOUND);
	return candidate;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="cmd">The command name to find.</param>
 * <returns>
 *   The array slot of this command, or -1.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_Find(const string:cmd[]);

GLOBAL__ Command_Find(const string:cmd[])
{
	Debug_Print2("Command_Find called: %s", cmd);
	static
		sHash = 0;

	Puny_EncodeHash(YSI_g_sCommandName, cmd, sHash, .delimiter = '@');
	Debug_Print5("Command_Find: hash %s, %d, %d", YSI_g_sCommandName, sHash, BernsteinHash(cmd));
	//printf("Command_Find: hash 1, %d", BernsteinHash(cmd));
	//printf("Command_Find: hash 2, %d", sHash);

	Debug_Print5("Command_Find: return %d", HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, sHash));
	return HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, sHash);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to "touch".</param>
 * <remarks>
 *   Used within "GROUP_ADD" to quickly assign a load of commands to just one
 *   group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_TouchNamed(const string:command[]);

GLOBAL__ void:Command_TouchNamed(const string:command[])
{
	new
		id = Command_Find(command);
	if (id != COMMAND_NOT_FOUND)
	{
		NO_GROUPS<Command>(id)
		{
			return;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to "touch".</param>
 * <remarks>
 *   Used within "GROUP_ADD" to quickly assign a load of commands to just one
 *   group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_Touch(command);

GLOBAL__ void:Command_Touch(command)
{
	if (_Command_IsValid(command) && !_Command_IsInline(command))
	{
		NO_GROUPS<Command>(command)
		{
			return;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetDeniedReturn(bool:set);

GLOBAL__ void:Command_SetDeniedReturn(bool:set)
{
	if (set)
		YSI_g_sSystemSettings |= e_SYSTEM_SETTINGS:(1 << _:COMMAND_DENIED - 1);
	else
		YSI_g_sSystemSettings &= ~e_SYSTEM_SETTINGS:(1 << _:COMMAND_DENIED - 1);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetDeniedReturn();

GLOBAL__ bool:Command_GetDeniedReturn()
{
	return bool:(YSI_g_sSystemSettings & e_SYSTEM_SETTINGS:(1 << _:COMMAND_DENIED - 1));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetIllegalReturn(bool:set);

GLOBAL__ void:Command_SetIllegalReturn(bool:set)
{
	if (set)
		YSI_g_sSystemSettings |= e_SYSTEM_SETTINGS:(1 << _:COMMAND_INVALID_INPUT - 1);
	else
		YSI_g_sSystemSettings &= ~e_SYSTEM_SETTINGS:(1 << _:COMMAND_INVALID_INPUT - 1);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetIllegalReturn();

GLOBAL__ bool:Command_GetIllegalReturn()
{
	return bool:(YSI_g_sSystemSettings & e_SYSTEM_SETTINGS:(1 << _:COMMAND_INVALID_INPUT - 1));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetUnknownReturn(bool:set);

GLOBAL__ void:Command_SetUnknownReturn(bool:set)
{
	if (set)
		YSI_g_sSystemSettings |= e_SYSTEM_SETTINGS:(1 << _:COMMAND_UNDEFINED - 1);
	else
		YSI_g_sSystemSettings &= ~e_SYSTEM_SETTINGS:(1 << _:COMMAND_UNDEFINED - 1);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetUnknownReturn();

GLOBAL__ bool:Command_GetUnknownReturn()
{
	return bool:(YSI_g_sSystemSettings & e_SYSTEM_SETTINGS:(1 << _:COMMAND_UNDEFINED - 1));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetDisconnectReturn(bool:set);

GLOBAL__ void:Command_SetDisconnectReturn(bool:set)
{
	if (set)
		YSI_g_sSystemSettings |= e_SYSTEM_SETTINGS:(1 << _:COMMAND_NO_PLAYER - 1);
	else
		YSI_g_sSystemSettings &= ~e_SYSTEM_SETTINGS:(1 << _:COMMAND_NO_PLAYER - 1);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetDisconnectReturn();

GLOBAL__ bool:Command_GetDisconnectReturn()
{
	return bool:(YSI_g_sSystemSettings & e_SYSTEM_SETTINGS:(1 << _:COMMAND_NO_PLAYER - 1));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_SetSilentReturn(bool:set);

GLOBAL__ void:Command_SetSilentReturn(bool:set)
{
	if (set)
		YSI_g_sSystemSettings |= e_SYSTEM_SETTINGS:(1 << _:COMMAND_SILENT - 1);
	else
		YSI_g_sSystemSettings &= ~e_SYSTEM_SETTINGS:(1 << _:COMMAND_SILENT - 1);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_GetSilentReturn();

GLOBAL__ bool:Command_GetSilentReturn()
{
	return bool:(YSI_g_sSystemSettings & e_SYSTEM_SETTINGS:(1 << _:COMMAND_SILENT - 1));
}

/*

    88888888888                                                     db        88888888ba  88  
    88                        ,d                                   d88b       88      "8b 88  
    88                        88                                  d8'`8b      88      ,8P 88  
    88aaaaa     8b,     ,d8 MM88MMM 8b,dPPYba, ,adPPYYba,        d8'  `8b     88aaaaaa8P' 88  
    88"""""      `Y8, ,8P'    88    88P'   "Y8 ""     `Y8       d8YaaaaY8b    88""""""'   88  
    88             )888(      88    88         ,adPPPPP88      d8""""""""8b   88          88  
    88           ,d8" "8b,    88,   88         88,    ,88     d8'        `8b  88          88  
    88888888888 8P'     `Y8   "Y888 88         `"8bbdP"Y8    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="function">The function this is an alternate to.</param>
 * <param name="altname">The new name.</param>
 * <param name="inherit">Does the new command use the parent's permissions?</param>
 * <remarks>
 *   Add an alternate command for an existing command.
 *
 * native Command_AddAltNamed(function[], altname[]);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_AddAltNamed__(const string:function[], const string:altname[], bool:inherit);

GLOBAL__ Command_AddAltNamed__(const string:function[], const string:altname[], bool:inherit)
{
	return Command_AddAlt__(Command_Find(function), altname, inherit);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="function">The function this is an alternate to.</param>
 * <param name="altname">The new name.</param>
 * <param name="inherit">Does the new command use the parent's permissions?</param>
 * <remarks>
 *   Add an alternate command for an existing command.
 *
 * native Command_AddAltNamed(function[], altname[]);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Command_AddAltNamed(const string:function[], const string:altname[], bool:inherit = false)
{
	return Command_AddAltNamed__(function, altname, inherit);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="func">The slot of the command to remove.</param>
 * <remarks>
 *
 * native Command_Remove(func);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_Remove(func);

GLOBAL__ void:Command_Remove(func)
{
	if (!_Command_IsValid(func) || _Command_IsInline(func))
	{
		return;
	}
	// Step one: Get the name as well.  We need both now.
	new
		name[64];
	strcat(name, YSI_g_sCommands[func][E_COMMAND_NAME]);
	new
		hash = BernsteinHash(name),
		start = HashMap_GetWithHash(YSI_g_sCommandMap, name, hash);
	if (start == func)
	{
		// We have found the first one.
		HashMap_RemoveKeyWithHash(YSI_g_sCommandMap, name, hash),
		start = YSI_g_sCommands[func][E_COMMAND_NEXT];
		if (start != COMMAND_NOT_FOUND)
		{
			// There are more.  We need to replace the pointer.
			HashMap_AddWithHash(YSI_g_sCommandMap, name, hash, start);
		}
	}
	else
	{
		while (start != COMMAND_NOT_FOUND && (hash = YSI_g_sCommands[start][E_COMMAND_NEXT]) != func)
		{
			start = hash;
		}
		if (start != COMMAND_NOT_FOUND)
		{
			YSI_g_sCommands[start][E_COMMAND_NEXT] = YSI_g_sCommands[func][E_COMMAND_NEXT];
		}
	}
	#if defined Y_COMMANDS_USE_CHARS
		Command_FlushPrefixes(_Command_GetPrefix(func)),
	#endif
	YSI_g_sCommands[func][E_COMMAND_POINTER] = -1,
	YSI_g_sCommands[func][E_COMMAND_NAME] = '\0';
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="func">The name of the command to remove.</param>
 * <remarks>
 *
 * native Command_RemoveNamed(string:func[]);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_RemoveNamed(const string:name[]);

GLOBAL__ void:Command_RemoveNamed(const string:name[])
{
	new
		func = Command_Find(name);
	Command_Remove(func);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="command">Command to get for.</param>
 * <returns>
 *   Is this command ID valid?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Command_IsValid(cmd);

GLOBAL__ bool:Command_IsValid(cmd)
{
	return _Command_IsValid(cmd);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <returns>
 *   The command currently being processed, or "COMMAND_NOT_FOUND".
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_GetCurrent();

GLOBAL__ Command_GetCurrent()
{
	return YSI_g_sCurrentID;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">Player to count for.</param>
 * <remarks>
 *   Gets the number of comamnds this player can use.
 *
 * native Command_GetPlayerCommandCount(playerid);
 *
 *   Has an internal name and an external name, because macros.  Ignores hidden
 *   commands, because they're hidden!
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ YCMD_GetPlayerCommandCount(playerid);

GLOBAL__ YCMD_GetPlayerCommandCount(playerid)
{
	Debug_Print2("Command_GetPlayerCommandCount called: %i", playerid);
	new
		slot = PA_Slot(playerid),
		Bit:mask = PA_Mask(playerid),
		count = 0;
	for (new i = 0; i != YSI_g_sHighestID; ++i)
	{
		if (_Command_IsActive(i))
		{
			switch (YSI_g_sCommands[i][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
			{
			case e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_INLINE:
			{
				// Primary command that isn't indirect, hidden, or disabled.
				// Alternate command that isn't inherited, hidden, or disabled.
				if (YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask)
				{
					++count;
				}
			}
			case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
			{
				// Alternate command that is inherited.  Use the parent.
				if (YSI_g_sCommands[YSI_g_sCommands[i][E_COMMAND_POINTER] & ~cellmin][E_COMMAND_USERS][slot] & mask)
				{
					++count;
				}
			}
			default:
			{
				// Any other combination is skipped.
			}
			}
		}
	}
	return count;
}

#define Command_GetPlayerCommandCount YCMD_GetPlayerCommandCount

/*

    888b      88                                                     
    8888b     88                                                     
    88 `8b    88                                                     
    88  `8b   88 ,adPPYYba, 88,dPYba,,adPYba,   ,adPPYba, ,adPPYba,  
    88   `8b  88 ""     `Y8 88P'   "88"    "8a a8P_____88 I8[    ""  
    88    `8b 88 ,adPPPPP88 88      88      88 8PP"""""""  `"Y8ba,   
    88     `8888 88,    ,88 88      88      88 "8b,   ,aa aa    ]8I  
    88      `888 `"8bbdP"Y8 88      88      88  `"Ybbd8"' `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="f">Command to get the name of.</param>
 * <remarks>
 *
 * native Command_GetName(funcid);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ string:Command_GetName(f);

GLOBAL__ string:Command_GetName(f)
{
	YSI_g_sReturnBuffer[0] = '\0';
	if (_Command_IsValid(f)) strunpack(YSI_g_sReturnBuffer, Command_Name(f));
	return YSI_g_sReturnBuffer;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="f">Command to get the real name of.</param>
 * <param name="p">Player to get the name for.</param>
 * <returns>
 *   The name of a command for a single player.
 * </returns>
 * <remarks>
 *   Abstracted because there's a crash when chain returning a string from a
 *   foreign function (see "Command_GetDisplayNamed").
 *
 * native Command_GetDisplay(funcid, playerid);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ string:Command_GetDisplay(funcid, playerid);

GLOBAL__ string:Command_GetDisplay(funcid, playerid)
{
	return
		_Command_GetDisplay(funcid, playerid),
		YSI_g_sReturnBuffer;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="f">Command to get the real name of.</param>
 * <param name="p">Player to get the name for.</param>
 * <returns>
 *   The name of a named function for one player.
 * </returns>
 * <remarks>
 *   Remote function call for Command_GetDisplayNameNamed - avoids needing to
 *   expose users to the master system's odd way of returning strings.  This is
 *   the only part I've not yet fixed up to be nice and hidden.
 *
 * native string:Command_GetDisplayNamed(string:funcid[], playerid);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ string:Command_GetDisplayNamed(const string:func[], playerid);

GLOBAL__ string:Command_GetDisplayNamed(const string:func[], playerid)
{
	return
		_Command_GetDisplay(Command_Find(func), playerid),
		YSI_g_sReturnBuffer;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="index">Index of the next command for this player.</param>
 * <param name="playerid">Player to get the name for.</param>
 * <returns>
 *   The name of a command for a single player.
 * </returns>
 * <remarks>
 *   -
 *
 * native Command_GetNext(index, playerid);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ string:Command_GetNext(index, playerid);

GLOBAL__ string:Command_GetNext(index, playerid)
{
	Debug_Print2("Command_GetNext called: %i, %i", index, playerid);
	YSI_g_sReturnBuffer[0] = '\0';
	if (0 <= index < YSI_g_sHighestID)
	{
		// Don't recalculate this every loop.
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		for (new i = 0; i != YSI_g_sHighestID; ++i)
		{
			if (_Command_IsActive(i))
			{
				switch (YSI_g_sCommands[i][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
				{
				case e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_INLINE:
				{
					// Primary command that isn't indirect, hidden, or disabled.
					// Alternate command that isn't inherited, hidden, or disabled.
					if (!(YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask))
					{
						continue;
					}
				}
				case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
				{
					// Alternate command that is inherited.  Use the parent.
					if (!(YSI_g_sCommands[YSI_g_sCommands[i][E_COMMAND_POINTER] & ~cellmin][E_COMMAND_USERS][slot] & mask))
					{
						continue;
					}
				}
				default:
				{
					// Any other combination is skipped.
					continue;
				}
				}
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

/*

    88                                                                                  
    88   ,d                                      ,d                                     
    88   88                                      88                                     
    88 MM88MMM ,adPPYba, 8b,dPPYba, ,adPPYYba, MM88MMM ,adPPYba,  8b,dPPYba, ,adPPYba,  
    88   88   a8P_____88 88P'   "Y8 ""     `Y8   88   a8"     "8a 88P'   "Y8 I8[    ""  
    88   88   8PP""""""" 88         ,adPPPPP88   88   8b       d8 88          `"Y8ba,   
    88   88,  "8b,   ,aa 88         88,    ,88   88,  "8a,   ,a8" 88         aa    ]8I  
    88   "Y888 `"Ybbd8"' 88         `"8bbdP"Y8   "Y888 `"YbbdP"'  88         `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="start">Last value.</param>
 * <returns>
 *   The next command.
 * </returns>
 * <remarks>
 *   Internal implementation of the "Command()" iterator for "foreach".  Returns
 *   all the commands that exist.  Normally iterator functions take two
 *   parameters, but this needs only one.  Really quite simple, but probably
 *   faster this way as it has access to internal information.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Iter_Func@Command(start);

GLOBAL__ Iter_Func@Command(start)
{
	for (new i = start + 1; i < YSI_g_sHighestID; ++i)
	{
		if (_Command_IsActive(i)) return i;
	}
	return COMMAND_NOT_FOUND;
}

#define Iterator@Command iterstart(-1)

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="pid">Player to check for.</param>
 * <param name="start">Last value.</param>
 * <returns>
 *   The next command.
 * </returns>
 * <remarks>
 *   Internal implementation of the "PlayerCommand()" iterator for "foreach".
 *   Returns all the commands this player can use.
 *
 *   This is similar to "Command_GetNext", but returns an ID not a string - I
 *   actually think this way is slightly better.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Iter_Func@PlayerCommand(start, pid);

GLOBAL__ Iter_Func@PlayerCommand(start, pid)
{
	new
		slot = PA_Slot(pid),
		Bit:mask = PA_Mask(pid);
	for (new i = start + 1; i < YSI_g_sHighestID; ++i)
	{
		if (_Command_IsActive(i))
		{
			switch (YSI_g_sCommands[i][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
			{
			case e_COMMAND_FLAG_PRI, e_COMMAND_FLAG_ALT, e_COMMAND_FLAG_INLINE:
			{
				// Primary command that isn't indirect, hidden, or disabled.
				// Alternate command that isn't inherited, hidden, or disabled.
				if (YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask)
				{
					return i;
				}
			}
			case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
			{
				// Alternate command that is inherited.  Use the parent.
				if (YSI_g_sCommands[YSI_g_sCommands[i][E_COMMAND_POINTER] & ~cellmin][E_COMMAND_USERS][slot] & mask)
				{
					return i;
				}
			}
			default:
			{
				// Any other combination is skipped.
				continue;
			}
			}
		}
	}
	return COMMAND_NOT_FOUND;
}

#define Iterator@PlayerCommand iterstart(-1)

/*
  
    88888888ba                           ad88 88                                  
    88      "8b                         d8"   ""                                  
    88      ,8P                         88                                        
    88aaaaaa8P' 8b,dPPYba,  ,adPPYba, MM88MMM 88 8b,     ,d8 ,adPPYba, ,adPPYba,  
    88""""""'   88P'   "Y8 a8P_____88   88    88  `Y8, ,8P' a8P_____88 I8[    ""  
    88          88         8PP"""""""   88    88    )888(   8PP"""""""  `"Y8ba,   
    88          88         "8b,   ,aa   88    88  ,d8" "8b, "8b,   ,aa aa    ]8I  
    88          88          `"Ybbd8"'   88    88 8P'     `Y8 `"Ybbd8"' `"YbbdP"'  
  
*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">Command to get.</param>
 * <returns>
 *   The prefix for this command ('/' by default).
 * </returns>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	FOREIGN__ Command_GetPrefix(c);
	
	GLOBAL__ Command_GetPrefix(c)
	{
		if (_Command_IsValid(c) && !_Command_IsInline(c)) return _Command_GetPrefix(c);
		return '/';
	}
	
	FOREIGN__ Command_GetPrefixNamed(const string:c[]);
	
	GLOBAL__ Command_GetPrefixNamed(const string:c[])
	{
		return Command_GetPrefix(Command_Find(c));
	}
	// Don't compile at all if it is disabled.
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="prefix">Possible prefix character.</param>
 * <returns>
 *   Is this a valid character for a prefix?
 * </returns>
 * <remarks>
 *   This is the ONLY place the list of valid prefixes is defined!  They are
 *   symbols, not an alphanumerics, and under 128.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	stock bool:Command_IsValidPrefix(prefix)
	{
		return (
			'!' <= prefix <= '/' ||
			':' <= prefix <= '@' ||
			'[' <= prefix <= '`' ||
			'{' <= prefix <= '~');
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="prefix">Possible prefix character.</param>
 * <returns>
 *   Is this a prefix used for any command?
 * </returns>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	FOREIGN__ bool:Command_IsPrefixUsed(prefix);
	
	GLOBAL__ bool:Command_IsPrefixUsed(prefix)
	{
		return Command_IsValidPrefix(prefix) && Bit_Get(YSI_g_sPrefixes, prefix);
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="prefix">Prefix to maybe remove.</param>
 * <remarks>
 *   If one command uses a prefix, then STOPS using said prefix, the global list
 *   of valid prefixes will need to be updated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	static stock Command_FlushPrefixes(prefix)
	{
		if (prefix == '/') return 1;
		for (new i = 0; i != YSI_g_sHighestID; ++i)
		{
			if (_Command_IsActive(i) && _Command_GetPrefix(i) == prefix) return 1;
		}
		Bit_Vet(YSI_g_sPrefixes, prefix);
		return 0;
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">Command to set.</param>
 * <param name="prefix">First character of the command.</param>
 * <remarks>
 *   Change what command to type "/x" vs "#x" for example.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	FOREIGN__ bool:Command_SetPrefix(c, prefix);
	
	GLOBAL__ bool:Command_SetPrefix(c, prefix)
	{
		if (Command_IsValidPrefix(prefix))
		{
			if (_Command_IsValid(c) && !_Command_IsInline(c))
			{
				// Set this command's prefix, and add the prefix to the list.
				new
					tmp = _Command_GetPrefix(c);
				return
					Bit_Let(YSI_g_sPrefixes, prefix),
					YSI_g_sCommands[c][E_COMMAND_FLAGS] = (YSI_g_sCommands[c][E_COMMAND_FLAGS] & ~e_COMMAND_FLAG_PREFIX) | (e_COMMAND_FLAGS:prefix),
					Command_FlushPrefixes(tmp),
					true;
			}
		}
		return false;
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">Named command to set.</param>
 * <param name="prefix">First character of the command.</param>
 * <remarks>
 *   Change what command to type "/x" vs "#x" for example.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	FOREIGN__ bool:Command_SetPrefixNamed(const string:c[], prefix);
	
	GLOBAL__ bool:Command_SetPrefixNamed(const string:c[], prefix)
	{
		return Command_SetPrefix(Command_Find(c), prefix);
	}
#endif

/*

    88        88                         88                   
    88        88                         88                   
    88        88                         88                   
    88aaaaaaaa88  ,adPPYba,   ,adPPYba,  88   ,d8  ,adPPYba,  
    88""""""""88 a8"     "8a a8"     "8a 88 ,a8"   I8[    ""  
    88        88 8b       d8 8b       d8 8888[      `"Y8ba,   
    88        88 "8a,   ,a8" "8a,   ,a8" 88`"Yba,  aa    ]8I  
    88        88  `"YbbdP"'   `"YbbdP"'  88   `Y8a `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">Player who typed something.</param>
 * <param name="text">What they typed.</param>
 * <returns>
 *   0 - Could not process the command.
 *   1 - Called the command.
 * </returns>
 * <remarks>
 *   Used to implement alternate command prefixes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerText(playerid, text[])
{
	// Is this prefix used anywhere?
	if (_Command_IsPrefix(text[0]))
	{
		// The default return for OnPlayerText is opposite OnPlayerCommandText.
		new
			e_COMMAND_ERRORS:sErr = Command_ReProcess__(playerid, text, 0);
		return !Command_Error(playerid, sErr);
	}
	// Default return, do nothing.
	return 1;
}

MASTER_REHOOK__ OnPlayerText(playerid, text[])
{
	#pragma unused playerid, text
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="playerid">Player who typed a command.</param>
 * <param name="cmdtext">What they typed.</param>
 * <returns>
 *   0 - Could not process the command.
 *   1 - Called the command.
 * </returns>
 * <remarks>
 *   The core of the command processor.  Now vsatly simplified.
 *
 *   This function first finds the command in our hash map.  If it exists, it
 *   checks if the player can use it.  If they can, it checks if it is only in
 *   the current script.  If it is it calls it directly, if it isn't it calls it
 *   using "CallRemoteFunction", which takes in to account master states in
 *   multiple scripts and the special master 23, which calls it in only one
 *   other script.
 * </remarks>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerCommandText(playerid, cmdtext[])
{
	// An interesting side-effect of this code is that, in theory, hacks that
	// submit commands without the "/" will still work.  Or you could hook
	// "OnPlayerText" to call "Command_ReProcess" and still work as well.
	new
		e_COMMAND_ERRORS:sErr = Command_ReProcess__(playerid, cmdtext, 0);
	return Command_Error(playerid, sErr);
}

MASTER_REHOOK__ OnPlayerCommandText(playerid, cmdtext[])
{
	#pragma unused playerid, cmdtext
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Add all local commands in to the system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnYSIInit()
{
	Debug_Print1("Command_OnYSIInit called");
	// Cache the pointer for faster checks later.
	YSI_g_sSystemSettings = e_SYSTEM_SETTINGS:((1 << _:COMMAND_OK - 1) | (1 << _:COMMAND_SILENT - 1));
	#if YSIM_NOT_CLIENT
		#if defined Y_COMMANDS_USE_CHARS
			Bit_SetAll(YSI_g_sPrefixes, false),
			Bit_Let(YSI_g_sPrefixes, '/'),
		#endif
		HashMap_Init(YSI_g_sCommandMap, YSI_g_sCommands, E_COMMAND_HASH_MAP);
		for (new func = 0; func != MAX_COMMANDS; ++func)
		{
			YSI_g_sCommands[func][E_COMMAND_POINTER] = -1;
		}
	#endif
	Debug_Print2("_Command_DoInit <> called");
	new
		entryPublic = 0,
		buffer[FUNCTION_LENGTH char],
		idx = 0,
		id2 = 0;
	Debug_Print5("Command_OnYSIInit: Pre-loop");
	while ((idx = AMX_GetPublicEntryPrefix(idx, entryPublic, _A<@yC_>)))
	{
		// Add the command name and pointer, but skip the leading "@yC_".
		Debug_Print6("Command_OnYSIInit: Adding %d", entryPublic);
		AMX_GetStringFromEntry(entryPublic, buffer),
		// buffer[0] = ('@' << 24) | ('_' << 16) | ('y' << 08) | ('C' << 00),
		buffer[0] = _C<@_yC>,
		id2 = funcidx(buffer);
		if (id2 != -1) entryPublic = AMX_HEADER_PUBLICS + id2 * 8;
		// Check that the function name is all lower-case.
		for (id2 = 4; buffer{id2}; ++id2)
		{
			if (buffer{id2} != tolower(buffer{id2})) Debug_Error("Commands must be in lower-case in your source code.");
		}
		// Add the command regardless.
		Command_Add__(buffer[1], ResolveJITAddress(AMX_Read(entryPublic)));
		Debug_Print6("Command_OnYSIInit: Name %s", Unpack(buffer[1]));
	}
	if (funcidx(YSI_gscOPCR) != -1) Command_IncOPCR();
	if (funcidx(YSI_gscOPCP) != -1) Command_IncOPCP();
	if (!YSI_g_sCodSize)
	{
		AddressofResolve();
		new
			amxhdr[AMX_HDR];
		GetAmxHeader(amxhdr);
		YSI_g_sCodSize = amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Passes additional commands data to the new master.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HANDOFF()
{
	Debug_Print1("Commands_OnScriptExit <_YCM:p> called");
	// Copy settings.
	DISTRIBUTE(YSI_g_sSystemSettings);
	DISTRIBUTE(YSI_g_sErrorMessages);
	DISTRIBUTE(YSI_g_sDisabledPlayers);
	// This accounts for master IDs.
	DISTRIBUTE(YSI_g_sCommands);
	// Now we've sent over the remaining valid commands, build the hash map.
	_Command_Rebuild();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   When a script ends, update the status of any new callback hooks.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnScriptExit()
{
	Debug_Print1("Commands_OnScriptExit <> called");
	if (funcidx(YSI_gscOPCR) != -1) Command_DecOPCR();
	if (funcidx(YSI_gscOPCP) != -1) Command_DecOPCP();
}

#if YSIM_HAS_MASTER
	MASTER_HOOK__ OnMasterSystemClose(id)
	{
		new
			cmdname[FUNCTION_LENGTH char] = {_C<@_yC>, 0, 0, ...},
			Bit:cur = Bit:Master_ID(),
			Bit:bit = Bit:(1 << id),
			Bit:rem = ~bit;
		for (new i = 0; i != MAX_COMMANDS; ++i)
		{
			if (_Command_IsActive(i))
			{
				if (YSI_g_sMasterData[i] == bit)
				{
					// Only existed in one (other) script.  Remove it.
					Command_Remove(i);
				}
				if ((YSI_g_sMasterData[i] &= rem) == cur)
				{
                    if(YSI_g_sCommands[i][E_COMMAND_POINTER] & cellmin) continue;
					// Existed in multiple, now only one.
					strpack(cmdname[1], Command_Name(i), 31);
					new
						id2 = funcidx(cmdname);
					if (id2 == -1)
					{
						Debug_Warning("Command marked EXCLUSIVE, but doesn't exist");
						Command_Remove(i);
						continue;
					}
					// Store the new pointer.
					YSI_g_sCommands[i][E_COMMAND_POINTER] = ResolveJITAddress(AMX_Read(AMX_HEADER_PUBLICS + id2 * 8));
				}
			}
		}
		return 1;
	}

	MASTER_REHOOK__ OnMasterSystemClose(id)
	{
		#pragma unused id
		return 1;
	}
#endif

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Call an inline command remotely, with a known type.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Command_FastCallS(Func:func<s>, string:params[], master)
{
	if (Master_ID() == master)
	{
		setproperty(8, YSIM_RETURN, @.func(params));
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Call an inline command remotely, with a known type.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Command_FastCallIS(playerid, string:params[], master, Func:func<is>)
{
	if (Master_ID() == master)
	{
		setproperty(8, YSIM_RETURN, @.func(playerid, params));
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Call an inline command remotely, with a known type.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Command_FastCallISI(playerid, string:params[], help, master, Func:func<isi>)
{
	if (Master_ID() == master)
	{
		setproperty(8, YSIM_RETURN, @.func(playerid, params, help));
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   Rebuilds the hashmap of command pointers after a master script hands off.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:_Command_Rebuild();

GLOBAL__ void:_Command_Rebuild()
{
	new
		cmdname[FUNCTION_LENGTH char] = {('@' << 24) | ('_' << 16) | ('y' << 08) | ('C' << 00), 0, 0, ...};
	HashMap_Init(YSI_g_sCommandMap, YSI_g_sCommands, E_COMMAND_HASH_MAP);
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		#if defined Y_COMMANDS_USE_CHARS
			Bit_SetAll(YSI_g_sPrefixes, false),
			Bit_Let(YSI_g_sPrefixes, '/');
		#endif
		if (_Command_IsActive(i))
		{
			#if defined Y_COMMANDS_USE_CHARS
				Bit_Let(YSI_g_sPrefixes, _Command_GetPrefix(i)),
			#endif
			strpack(cmdname[1], Command_Name(i), 31),
			HashMap_Add(YSI_g_sCommandMap, cmdname[1], i),
			YSI_g_sHighestID = i + 1;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   This function, and the three other related ones, increment and decrement the
 *   number of callbacks known to exist on the server.  If they are 0, there's no
 *   point trying to call them on errors etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_IncOPCR();

GLOBAL__ void:Command_IncOPCR()
{
	Debug_Print2("Command_IncOPCR called");
	YSI_g_sSystemSettings += e_COMM_FLAG_OPCR_ADD;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   This function, and the three other related ones, increment and decrement the
 *   number of callbacks known to exist on the server.  If they are 0, there's no
 *   point trying to call them on errors etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_DecOPCR();

GLOBAL__ void:Command_DecOPCR()
{
	Debug_Print2("Command_DecOPCR called");
	YSI_g_sSystemSettings -= e_COMM_FLAG_OPCR_ADD;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   This function, and the three other related ones, increment and decrement the
 *   number of callbacks known to exist on the server.  If they are 0, there's no
 *   point trying to call them on errors etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_IncOPCP();

GLOBAL__ void:Command_IncOPCP()
{
	Debug_Print2("Command_IncOPCP called");
	YSI_g_sSystemSettings += e_COMM_FLAG_OPCP_ADD;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <remarks>
 *   This function, and the three other related ones, increment and decrement the
 *   number of callbacks known to exist on the server.  If they are 0, there's no
 *   point trying to call them on errors etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_DecOPCP();

GLOBAL__ void:Command_DecOPCP()
{
	Debug_Print2("Command_DecOPCP called");
	YSI_g_sSystemSettings -= e_COMM_FLAG_OPCP_ADD;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <returns>
 *   The first available slot in "YSI_g_sCommands".
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock Command_GetEmptySlot()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		// No name for the command, can't exist.
		if (_Command_IsEmptySlot(i)) return i;
	}
	return COMMAND_NOT_FOUND;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The command name to add.</param>
 * <param name="p">The player this command is for.</param>
 * <param name="i">The command's implementation.</param>
 * <param name="f">Flags.</param>
 * <returns>
 *   The command's ID.
 * </returns>
 * <remarks>
 *   Multiple commands for different players with the same name may return the
 *   same ID.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_AddCallback__(const string:c[],p,i,f);

GLOBAL__ Command_AddCallback__(const string:c[],p,i,f)
{
	Debug_Print2("Command_AddCallback called: %s, %d, %08x, %d", c, p, i, f);
	new
		hash,
		id = Iter_Alloc(YSI_g_sPlayerCmd<p>);
	if (id == INVALID_ITERATOR_SLOT)
	{
		Debug_Error("Could not add inline command to array.");
		return COMMAND_NOT_FOUND;
	}
	
	Puny_EncodeHash(YSI_g_sCommandName, c, hash, .delimiter = '@'),
	strpack(YSI_g_sCommandName, YSI_g_sCommandName, cellmax);
	Debug_Print5("Command_AddCallback: packed %s, %s", YSI_g_sCommandName, c);
	Debug_Print5("Command_AddCallback: unpacked %s, %s", Unpack(YSI_g_sCommandName), Unpack(c));
	
	// Check if there is already an inline entry point for this command.
	new
		parent = HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash),
		tmp = parent;
	while (parent != COMMAND_NOT_FOUND)
	{
		if (YSI_g_sCommands[parent][E_COMMAND_FLAGS] & e_COMMAND_FLAG_INLINE)
		{
			break;
		}
		parent = YSI_g_sCommands[parent][E_COMMAND_NEXT];
	}
	if (parent == COMMAND_NOT_FOUND)
	{
		Debug_Print5("Command_AddCallback: New command name");
		if ((parent = Command_GetEmptySlot()) == COMMAND_NOT_FOUND)
		{
			Debug_Error("Could not add inline command to array.");
			return COMMAND_NOT_FOUND;
		}
		if ((YSI_g_sCommands[parent][E_COMMAND_NEXT] = tmp) != COMMAND_NOT_FOUND)
		{
			HashMap_RemoveKeyWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash);
		}
		if (strcmp(YSI_g_sCommandName, c))
		{
			// There is any punycode command.
			YSI_g_sSystemSettings |= e_COMM_FLAG_PUNYCODE;
		}
		HashMap_AddWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, hash, parent),
		// This sets the prefix even when that feature is disabled, because
		// there's literally no overhead in doing so.
		YSI_g_sCommands[parent][E_COMMAND_FLAGS] = e_COMMAND_FLAG_INLINE | (e_COMMAND_FLAGS:'/'),
		// Save the new highest ID for loops later.
		YSI_g_sHighestID = max(YSI_g_sHighestID, parent + 1),
		PA_FastInit(YSI_g_sCommands[parent][E_COMMAND_USERS]);
		NO_GROUPS<Command>(parent)
		{
			PA_Init(YSI_g_sCommands[parent][E_COMMAND_USERS], false);
		}
	}
	
	// Check if they already have an inline command with this name.
	if (PA_Get(YSI_g_sCommands[parent][E_COMMAND_USERS], p))
	{
		Debug_Print5("Command_AddCallback: Has existing command");
		FOREACH__ (tmp : YSI_g_sPlayerCmd<p>)
		{
			if ((YSI_g_sInlineCommands[tmp][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == (e_COMMAND_FLAGS:parent))
			{
				if (tmp != id)
				{
					// This is a different inline with the same parent, but comes
					// before our new one.  Swap everything.  We haven't actually
					// set the new command's data yet, so only need to move.
					YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER] = YSI_g_sInlineCommands[tmp][E_COMMAND_INLINE_POINTER],
					YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER] = YSI_g_sInlineCommands[tmp][E_COMMAND_INLINE_MASTER],
					YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] = YSI_g_sInlineCommands[tmp][E_COMMAND_INLINE_FLAGS],
					id = tmp;
				}
				break;
			}
		}
	}
	
	Debug_Print5("Command_AddCallback: return %d, %d, %d, %d", parent, id, _:Master_Caller(), _:(f | parent));
	return
		PA_Set(YSI_g_sCommands[parent][E_COMMAND_USERS], p, true),
		YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER] = i,
		YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER] = Bit:Master_Caller(),
		YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] = e_COMMAND_FLAGS:(f | parent),
		parent;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="cmd">The command name to add.</param>
 * <param name="playerid">The player this command is for.</param>
 * <param name="ptr">The command's implementation.</param>
 * <param name="tag">The type of command call to use.</param>
 * <returns>
 *   The command's ID.
 * </returns>
 * <remarks>
 *   Multiple commands for different players with the same name may return the
 *   same ID.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Command_AddCallback(const string:cmd[], playerid, {F@_@s, F@_@is, F@_@isi}:ptr, tag = tagof (ptr))
{
	// This code is done locally because the inline may always reside in local
	// assigned memory.
	const
		Func:tagS<s> = Func:0<s>,
		Func:tagIS<is> = Func:0<is>,
		Func:tagISI<isi> = Func:0<isi>;
	// Apparently being using in `tagof` doesn't mark them as used (which is
	// somewhat understandable, that's usually a mistake).
	#pragma unused tagS, tagIS, tagISI
	const
		tagofS = tagof (tagS),
		tagofIS = tagof (tagIS),
		tagofISI = tagof (tagISI);
	new
		e_COMMAND_FLAGS:flags = e_COMMAND_FLAG_INLINE;
	// The compiler really doesn't like `tagof` in `case`.
	switch (tag)
	{
	case tagofS:
		flags |= e_COMMAND_FLAG_ARGS_S;
	case tagofIS:
		flags |= e_COMMAND_FLAG_ARGS_IS;
	case tagofISI:
		flags |= e_COMMAND_FLAG_ARGS_ISI;
	}
	switch (Indirect_GetType(ptr))
	{
	case 1:
		flags |= e_COMMAND_FLAG_TYPE_INL;
	case 2:
		flags |= e_COMMAND_FLAG_TYPE_STR;
	case 3:
		flags |= e_COMMAND_FLAG_TYPE_PTR;
	}
	if (Command_AddCallback__(cmd, playerid, _:ptr, _:flags) != COMMAND_NOT_FOUND)
	{
		Indirect_Claim(ptr);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="c">The command name to remove.</param>
 * <param name="p">The player this command is for.</param>
 * <param name="o">The owning entity for EBC callbacks.</param>
 * <param name="i">The inline itself.</param>
 * <returns>
 *   -
 * </returns>
 * <remarks>
 *   We need to call in to the owning script for each candidate because the
 *   allocated memory is there.  They will return whether this should be
 *   removed and do the local memory deallocation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Command_RemoveCallback__(const string:c[],p,o,i);

GLOBAL__ void:Command_RemoveCallback__(const string:c[],p,o,i)
{
	Debug_Print2("Command_RemoveCallback called: %s, %d, %d, %08x", c, p, o, i);
	// TODO: I need to 
	if (i != 0)
	{
		Debug_Print5("Command_RemoveCallback: Exact pointer");
		// Given an exact pointer.  Don't worry about anything else, just
		// remove exactly this one.
		#if YSIM_HAS_MASTER
			new
				m = Master_Caller();
		#endif
			o = COMMAND_NOT_FOUND; // Unknown.
			FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
			{
				if (YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER] == i)
				{
						// Remove it.
					#if YSIM_HAS_MASTER
						// We need to check the origin script as well.  It
						// is possible that two different ones give the same
						// pointer in their own memory spaces.
						if (YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER] == Bit:m)
						{
					#endif
							o = YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT,
							Iter_Remove(YSI_g_sPlayerCmd<p>, id);
					#if YSIM_HAS_MASTER
							TARGET_FUNC__ Command_TryRelease__<m>(cellmin, i);
						}
					#else
							Indirect_Release(i);
					#endif
				}
			}
			if (o != COMMAND_NOT_FOUND)
			{
				FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
				{
					if ((YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == e_COMMAND_FLAGS:o)
					{
						// Another command has the same parent.  Don't
						// remove this player from the list.
						return;
					}
				}
				PA_Set(YSI_g_sCommands[o][E_COMMAND_USERS], p, false);
			}
	}
	else if (IsNull(c))
	{
		Debug_Print5("Command_RemoveCallback: All for player");
		// No command specified.  Remove everything for this player.
		FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
		{
			// Remove it.
			#if YSIM_HAS_MASTER
				TARGET_FUNC__ Command_TryRelease__<_:YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER]>(cellmin, YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]);
			#else
				Indirect_Release(YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]);
			#endif
				PA_Set(YSI_g_sCommands[YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT][E_COMMAND_USERS], p, false),
				Iter_Remove(YSI_g_sPlayerCmd<p>, id);
		}
	}
	else if (o == cellmin)
	{
		Debug_Print5("Command_RemoveCallback: All for command");
		// No owner specified.  Remove all instances of this command.
		Puny_EncodeHash(YSI_g_sCommandName, c, i, .delimiter = '@'),
		i = HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, i);
		while (i != COMMAND_NOT_FOUND)
		{
			if (YSI_g_sCommands[i][E_COMMAND_FLAGS] & e_COMMAND_FLAG_INLINE)
			{
				break;
			}
			i = YSI_g_sCommands[i][E_COMMAND_NEXT];
		}
		if (i != COMMAND_NOT_FOUND && PA_Get(YSI_g_sCommands[i][E_COMMAND_USERS], p))
		{
			FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
			{
				if ((YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == e_COMMAND_FLAGS:i)
				{
					// Remove it.
					#if YSIM_HAS_MASTER
						TARGET_FUNC__ Command_TryRelease__<_:YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER]>(cellmin, YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]);
					#else
						Indirect_Release(YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]);
					#endif
						Iter_Remove(YSI_g_sPlayerCmd<p>, id);
				}
			}
			PA_Set(YSI_g_sCommands[i][E_COMMAND_USERS], p, false);
		}
	}
	else
	{
		Debug_Print5("Command_RemoveCallback: Owned for command");
		#if YSIM_HAS_MASTER
			new
				m = Master_Caller();
		#endif
			Puny_EncodeHash(YSI_g_sCommandName, c, i, .delimiter = '@'),
			i = HashMap_GetWithHash(YSI_g_sCommandMap, YSI_g_sCommandName, i);
			while (i != COMMAND_NOT_FOUND)
			{
				if (YSI_g_sCommands[i][E_COMMAND_FLAGS] & e_COMMAND_FLAG_INLINE)
				{
					break;
				}
				i = YSI_g_sCommands[i][E_COMMAND_NEXT];
			}
			if (i != COMMAND_NOT_FOUND && PA_Get(YSI_g_sCommands[i][E_COMMAND_USERS], p))
			{
				FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
				{
					#if YSIM_HAS_MASTER
						// Only the originating script can remove a callback
						// with a specified owner.
						if ((YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == e_COMMAND_FLAGS:i && YSI_g_sInlineCommands[id][E_COMMAND_INLINE_MASTER] == Bit:m && TARGET_FUNC__ Command_TryRelease__<m>(o, YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]))
						{
							Iter_Remove(YSI_g_sPlayerCmd<p>, id);
						}
					#else
						if ((YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == e_COMMAND_FLAGS:i && Indirect_GetOwner(YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]) == o)
						{
							Indirect_Release(YSI_g_sInlineCommands[id][E_COMMAND_INLINE_POINTER]),
							Iter_Remove(YSI_g_sPlayerCmd<p>, id);
						}
					#endif
				}
				FOREACH__ (new id : YSI_g_sPlayerCmd<p>)
				{
					if ((YSI_g_sInlineCommands[id][E_COMMAND_INLINE_FLAGS] & e_COMMAND_FLAG_PARENT) == e_COMMAND_FLAGS:i)
					{
						// Another command has the same parent.  Don't
						// remove this player from the list.
						return;
					}
				}
				PA_Set(YSI_g_sCommands[i][E_COMMAND_USERS], p, false);
			}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="cmd">The command name to remove.</param>
 * <param name="playerid">The player this command is for.</param>
 * <param name="owner">The owning entity for EBC callbacks.</param>
 * <returns>
 *   -
 * </returns>
 * <remarks>
 *   We need to call in to the owning script for each candidate because the
 *   allocated memory is there.  They will return whether this should be
 *   removed and do the local memory deallocation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Command_RemoveCallback(const string:cmd[], playerid, {_, F@_@s, F@_@is, F@_@isi}:owner = cellmin, tag = tagof (owner))
{
	if (tag == tagof (tag)) // tagof (_:)
	{
		// A specified owner, not a function.
		// A pointer of `0` should in theory be a valid inline function, but
		// points to the start of COD where the public return code is, so we
		// assume it isn't a valid pointer.  Plus `owner` isn't `cellmin`.
		Command_RemoveCallback__(cmd, playerid, owner, 0);
	}
	else
	{
		// Much simpler - we only need to find an exact matching function.  We
		// use `cellmin` because that bit can never be set by an owner - it is
		// reserved by `indirection.inc`.
		Command_RemoveCallback__(cmd, playerid, cellmin, owner);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="cmd">The command name to add.</param>
 * <param name="ptr">The command's pointer.</param>
 * <returns>
 *   The command's ID.
 * </returns>
 * <remarks>
 *   This was an external API function, but there is no reason for it to be as it
 *   is called for all found commands at mode start.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Command_Add__(const string:cmd[], ptr);

GLOBAL__ Command_Add__(const string:cmd[], ptr)
{
	new
		packed[64] = "",
		hash = 0,
		id;
	// The commands all need to be stored packed.
	Debug_Print2("Command_Add: %s, %d", Unpack(cmd), ptr);
	if (strfind(cmd, "@") == -1)
	{
		// There is any punycode command.
		YSI_g_sSystemSettings |= e_COMM_FLAG_PUNYCODE;
	}
	// We don't need to use `Puny_EncodeHash` here since the input is already
	// correctly encoded.
	hash = BernsteinHash(cmd),
	id = HashMap_GetWithHash(YSI_g_sCommandMap, cmd, hash);
	Debug_Print5("Command_Add: found %d", id);
	if (id == COMMAND_NOT_FOUND)
	{
		// Command doesn't already exist, add it.
		if ((id = Command_GetEmptySlot()) == COMMAND_NOT_FOUND)
		{
			Debug_Error("Could not add command to array.");
			return COMMAND_NOT_FOUND;
		}
		// This sets the prefix even when that feature is disabled, because
		// there's literally no overhead in doing so.
		YSI_g_sCommands[id][E_COMMAND_FLAGS] = e_COMMAND_FLAG_PRI | (e_COMMAND_FLAGS:'/') | e_COMMAND_FLAG_NRM_ISI,
		YSI_g_sHighestID = max(YSI_g_sHighestID, id + 1),
		// Save the command's pointer.
		YSI_g_sCommands[id][E_COMMAND_POINTER] = ptr,
		// This should always be the first command of this name.
		YSI_g_sCommands[id][E_COMMAND_NEXT] = COMMAND_NOT_FOUND,
		// Add this command to the hash map (does the name too).
		strpack(packed, cmd, cellmax),
		HashMap_AddWithHash(YSI_g_sCommandMap, packed, hash, id),
		// Add all players, or defer to y_groups.
		PA_FastInit(YSI_g_sCommands[id][E_COMMAND_USERS]);
		NO_GROUPS<Command>(id)
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

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="func">Command to get the real name of.</param>
 * <param name="playerid">Player to get the name for.</param>
 * <returns>
 *   The name of a command for a single player.
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock _Command_GetDisplay(funcid, playerid)
{
	Debug_Print4("_Command_GetDisplay called: %d %d", funcid, playerid);
	YSI_g_sReturnBuffer[0] = '\0';
	if (_Command_IsValid(funcid) && VALID_PLAYERID(playerid))
	{
		Debug_Print5("_Command_GetDisplay: valid");
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
_Command_GetDisplay_retry:
		// Check if they can use the original version.
		switch (YSI_g_sCommands[funcid][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
		{
		case e_COMMAND_FLAG_ALT:
		{
			// Allowed alternate.
			if (YSI_g_sCommands[funcid][E_COMMAND_USERS][slot] & mask)
			{
				return strunpack(YSI_g_sReturnBuffer, Command_Name(funcid));
			}
			funcid = YSI_g_sCommands[funcid][E_COMMAND_POINTER] & ~cellmin;
			goto _Command_GetDisplay_retry;
		}
		case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
		{
			// BAD REUSE OF THE "playerid" VARIABLE.
			if (YSI_g_sCommands[(playerid = YSI_g_sCommands[funcid][E_COMMAND_POINTER] & ~cellmin)][E_COMMAND_USERS][slot] & mask)
			{
				return strunpack(YSI_g_sReturnBuffer, Command_Name(funcid));
			}
			funcid = playerid;
			goto _Command_GetDisplay_retry;
		}
		case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_HIDDEN                                                   ,
		     e_COMMAND_FLAG_ALT                         | e_COMMAND_FLAG_DISABLED                         ,
		     e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED                         ,
		     e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_HIDDEN                           | e_COMMAND_FLAG_INHERIT,
		     e_COMMAND_FLAG_ALT                         | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INHERIT,
		     e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INHERIT:
		{
			// All the variations of disabled alternates.
			funcid = YSI_g_sCommands[funcid][E_COMMAND_POINTER] & ~cellmin;
			goto _Command_GetDisplay_retry;
		}
		case e_COMMAND_FLAG_PRI:
		{
			// Allowed primary.
			if (YSI_g_sCommands[funcid][E_COMMAND_USERS][slot] & mask)
			{
				return strunpack(YSI_g_sReturnBuffer, Command_Name(funcid));
			}
		}
		case e_COMMAND_FLAG_INLINE:
		{
			// Allowed inline.
			if (YSI_g_sCommands[funcid][E_COMMAND_USERS][slot] & mask)
			{
				return strunpack(YSI_g_sReturnBuffer, Command_Name(funcid));
			}
			return 0;
		}
		//case e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_HIDDEN                                                    ,
		//     e_COMMAND_FLAG_PRI                         | e_COMMAND_FLAG_DISABLED                          ,
		//     e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED                          :
		default:
		{
			// All the variations of disabled primaries.
		}
		}
		// Now we have a root command, check all alternates to this one.
		playerid = funcid | cellmin;
		for (new i = 0; i != YSI_g_sHighestID; ++i)
		{
			if (_Command_IsActive(i) && YSI_g_sCommands[i][E_COMMAND_POINTER] == playerid)
			{
				switch (YSI_g_sCommands[i][E_COMMAND_FLAGS] & (e_COMMAND_FLAG_PRI | e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT | e_COMMAND_FLAG_HIDDEN | e_COMMAND_FLAG_DISABLED | e_COMMAND_FLAG_INLINE))
				{
				case e_COMMAND_FLAG_ALT:
				{
					// Allowed alternate.
					if (YSI_g_sCommands[i][E_COMMAND_USERS][slot] & mask)
					{
						return strunpack(YSI_g_sReturnBuffer, Command_Name(i));
					}
				}
				case e_COMMAND_FLAG_ALT | e_COMMAND_FLAG_INHERIT:
				{
					// BAD REUSE OF THE "playerid" VARIABLE.
					if (YSI_g_sCommands[funcid][E_COMMAND_USERS][slot] & mask)
					{
						return strunpack(YSI_g_sReturnBuffer, Command_Name(i));
					}
				}
				default:
				{
					// Do nothing, try the next alternative.
				}
				}
			}
		}
	}
	return 0;
}

static stock y_commands_y_groups() <y_groups : y_groups_exists>
{
}

static stock y_commands_y_groups() <y_groups : y_groups_none>
{
}

stock Command_DecoratorGroup__(cmd, Group:g) <y_groups : y_groups_none>
{
	#pragma unused cmd, g
}

stock Command_DecoratorGroup__(cmd, Group:g) <>
{
	#pragma unused cmd, g
}

native Command_Strcat_(dest[], src, len) = strcat;

/*-------------------------------------------------------------------------*//**
 * <library>y_commands</library>
 * <param name="func__">The name of the implementing function.  Also the command if <c>name</c> isn't given.</param>
 * <param name="name">The command to type, if not just the function name.</param>
 * <param name="altcount">The number of entries in the alternate name array.</param>
 * <param name="alts">A pointer to the array of alternate names.</param>
 * <param name="prefix">Which character to start the command with.</param>
 * <param name="group">An optional group that has exclusive use of this command.</param>
 * <param name="disabled">Not usable by default.</param>
 * <param name="hidden">Not listed in command loops.</param>
 * <param name="id">Variable to return the ID in.</param>
 * <library>y_commands</library>
 * <returns>
 *   The name of a command for a single player.
 * </returns>
 * <remarks>
 *   No combination of this works:
 *   
 *   <code>
 *     Command_Decorator__(alts[][] = {})
 *   </code>
 *   
 *   Hence we need to use:
 *   
 *   <code>
 *     Command_Decorator__(.alts = ref(alts));
 *   </code>
 *   
 *   I.e. use a pointer to an array.  Not nice, but meh.  We must ensure that
 *   the decorator macro allows:
 *   
 *   <code>
 *     @cmd(.alts = { "h", "help", "ajuda" });
 *   </code>
 *   
 *   And translates this to:
 *   
 *   <code>
 *     const alts = { "h", "help", "ajuda" };                                   <br />
 *     Command_Decorator__(.altcount = sizeof (alts), .altpointer = ref(alts));
 *   </code>
 *   
 *   For now this is the only parameter that needs special handling.  Example:
 *   
 *   <code>
 *     @cmd(.group = gAdmins, .prefix = '!') ban(playerid, params[], help)      <br />
 *     {                                                                        <br />
 *     }
 *   </code>
 *   
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined Y_COMMANDS_USE_CHARS
	stock Command_Decorator__(const __COMPILER_NAMED.string:func__[], const __COMPILER_NAMED.string:name[] = "", __COMPILER_NAMED.altcnt__ = 0, __COMPILER_NAMED.altptr__ = 0, __COMPILER_NAMED.prefix = '/', __COMPILER_NAMED.Group:group = Group:0, __COMPILER_NAMED.bool:disabled = false, __COMPILER_NAMED.bool:hidden = false, __COMPILER_NAMED.&id = 0)
#else
	stock Command_Decorator__(const __COMPILER_NAMED.string:func__[], const __COMPILER_NAMED.string:name[] = "", __COMPILER_NAMED.altcnt__ = 0, __COMPILER_NAMED.altptr__ = 0, __COMPILER_NAMED.Group:group = Group:0, __COMPILER_NAMED.bool:disabled = false, __COMPILER_NAMED.bool:hidden = false, __COMPILER_NAMED.&id = 0)
#endif
{
	state y_groups : y_groups_exists;
	id = Command_GetID(func__);
	new str[FUNCTION_LENGTH];
	while (altcnt__--)
	{
		// Add alternate versions of this command.
		// Get an offset in to the 2D array.
		str[0] = '\0',
		Command_Strcat_(str, altptr__ + AMX_Read(altptr__), FUNCTION_LENGTH),
		altptr__ += cellbytes;
		new aid = Command_AddAlt(id, str);
		// A simple `Command_SetDisabled(aid, disabled);` would seem to make more
		// sense in these following lines, and be more readable, but this way is
		// much faster in the enabled case.
		if (disabled) Command_SetDisabled(aid, true);
		if (hidden) Command_SetHidden(aid, true);
		if (group) Command_DecoratorGroup__(aid, group);
	}
	if (!IsNull(name))
	{
		// Remove all players.
		// TODO: Set the group default.
		Command_SetDisabled(id, true),
		Command_SetHidden(id, true);
		// `func__` remains the canonical internal name, but isn't what the
		// user types.  This is simply implemented as another alternate name
		// with the original name completely disabled for all players.
		id = Command_AddAlt(id, name, true);
	}
	// There's a group given, as the only users of this command.
	if (group) Command_DecoratorGroup__(id, group);
	// Disable this command initially.
	if (disabled) Command_SetDisabled(id, true);
	// TODO:  We don't actually currently have a way to mark a command as
	// hidden.  Things like `foreach (new c : Command(playerid))` will loop
	// through all the commands the player can use, regardless of anything.
	if (hidden) Command_SetHidden(id, true);
	#if defined Y_COMMANDS_USE_CHARS
		Command_SetPrefix(id, prefix);
	#endif
}

// Un-inline the alt commands array.
#define Command_Decorator__(%0{%1}%2) static const altnames__[][]={%1};Command_Decorator__(%0$%2)
#define alts=$ altptr__=ref(altnames__),.altcnt__=sizeof (altnames__)
#define func__=#%1,) func__=#%1)

#define @cmd(%0)%1(%2) POSTINIT__ %1(){Command_Decorator__(.func__=#%1,%0);}YSIM_COMMAND %1(%2)
#define @command @cmd

