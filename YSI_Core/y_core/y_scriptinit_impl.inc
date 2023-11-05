#if defined _INC_y_scriptinit
	#endinput
#endif

/**
 * <library
 *   name="y_scriptinit"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="OnScriptInit, OnCodeInit, and equivalent exit functions."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//**
 * <library
 *   name="y_scriptdata"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Utility functions for information about how and when the script was built."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//**
 * <library
 *   name="y_serverdata"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Utility functions for information about plugin and server options."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//** *//*
	
	Now also provides OnCodeInit, which comes before OnScriptInit and should
	mostly be used for @emit code generation and other assembly related stuff
	(since it is called by the JIT if that exists).
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

/// <p/>

forward _ScriptInit_FixState();

CHAIN_HOOK(ScriptInit)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(ScriptInit)

/**
 * <library>y_serverdata</library>
 * <remarks>
 *   <c>true</c> if the current script is running as a gamemode.
 * </remarks>
 */
#if _YSI_SAFE_STARTUP
	stock
		bool:YSI_GAMEMODE = false;
#else
	static stock
		bool:YSI_GAMEMODE__ = false;
#endif

/**
 * <library>y_serverdata</library>
 * <remarks>
 *   <c>true</c> if the current script is running as a filterscript.
 * </remarks>
 */
stock
	bool:YSI_FILTERSCRIPT = false;

/// <p/>

/**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Where in initialisation the script currently is.  Handles multiple ways of
 *   starting the script, including cache loads and JIT.
 * </remarks>
 */

enum E_SCRIPTINIT_STATE (<<= 1)
{
	E_SCRIPTINIT_STATE_NONE,
	E_SCRIPTINIT_STATE_JITING = 1,
	E_SCRIPTINIT_STATE_JITED,
	// No longer used, but kept for caching bit locations.
	E_SCRIPTINIT_STATE_CRASHDETECT_,
	E_SCRIPTINIT_STATE_RELOAD,
	E_SCRIPTINIT_STATE_DUMPED,
}

static stock E_SCRIPTINIT_STATE:_@E_SCRIPTINIT_STATE() { return E_SCRIPTINIT_STATE; }

/**
 * <library>y_scriptinit</library>
 * <remarks>
 *   How the script was set up - JIT, cache, or other.
 * </remarks>
 */
static
	E_SCRIPTINIT_STATE:YSI_g_sScriptInitState = E_SCRIPTINIT_STATE_NONE;

#if defined DEBUG_DUMP
	#tryinclude "..\..\amx\disasm"
	#tryinclude <amx_assembly\disasm>
	#tryinclude "..\..\amx_assembly\disasm"
	#tryinclude "..\..\..\amx_assembly\disasm"
	#tryinclude "disasm"
	#tryinclude <disasm>

	#if !defined DISASM_INC
		#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
	#endif

	// Dump the final assembly of this script so we can inspect it.
	#define DEBUG_MAYBE_DUMP(%0,%2); ScriptInit_Dump(%0,%2);
#else
	#define DEBUG_MAYBE_DUMP(%0,%1);
#endif

#if !defined _ALS_OnFilterScriptInit
	forward OnFilterScriptInit();
#endif

#if !defined _ALS_OnGameModeInit
	forward OnGameModeInit();
#endif

#if !defined _ALS_OnFilterScriptExit
	forward OnFilterScriptExit();
#endif

#if !defined _ALS_OnGameModeExit
	forward OnGameModeExit();
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if the JIT plugin exists.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_JITExists()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING) != E_SCRIPTINIT_STATE_NONE;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if the JIT plugin has completed compilation.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_JITComplete`.
stock bool:Server_JITComplete()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITED) != E_SCRIPTINIT_STATE_NONE;
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if the JIT plugin has completed compilation.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Script_JITComplete()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITED) != E_SCRIPTINIT_STATE_NONE;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script was loaded from <c>YSI_CACHE</c>.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_CacheLoaded`.
stock bool:Server_CacheLoaded()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD) != E_SCRIPTINIT_STATE_NONE;
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script was loaded from <c>YSI_CACHE</c>.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Script_CacheLoaded()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD) != E_SCRIPTINIT_STATE_NONE;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script was written to <c>YSI_CACHE</c>.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_CacheSaved`.
stock bool:Server_CacheSaved()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_DUMPED) != E_SCRIPTINIT_STATE_NONE;
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script was written to <c>YSI_CACHE</c>.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Script_CacheSaved()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_DUMPED) != E_SCRIPTINIT_STATE_NONE;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script is determined to be a filterscript at runtime.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_IsFilterscript`.
stock bool:Server_IsFilterscript()
{
#if _YSI_SAFE_STARTUP
	return YSI_FILTERSCRIPT;
#elseif defined FILTERSCRIPT
	return true;
#else
	return false;
#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script is determined to be a filterscript at runtime.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Script_IsFilterscript();

#if _YSI_SAFE_STARTUP
	#define Script_IsFilterscript() (YSI_FILTERSCRIPT)
#elseif defined FILTERSCRIPT
	#define Script_IsFilterscript() (TRUE)
#else
	#define Script_IsFilterscript() (FALSE)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script is determined to be a gamemode at runtime.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_IsGameMode`.
stock bool:Server_IsGameMode()
{
#if _YSI_SAFE_STARTUP
	return YSI_GAMEMODE;
#elseif defined FILTERSCRIPT
	return false;
#else
	return true;
#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script is determined to be a gamemode at runtime.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Script_IsGameMode();

#if _YSI_SAFE_STARTUP
	#define Script_IsGameMode() (YSI_GAMEMODE)
#elseif defined FILTERSCRIPT
	#define Script_IsGameMode() (FALSE)
#else
	#define Script_IsGameMode() (TRUE)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script is running on a Linux server currently.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_IsLinuxHost()
{
	// Taken from fixes.inc.
	new
		val = 0;
	// The code at address 0 is always `HALT`.
	#emit LCTRL                __cod
	#emit MOVE.alt
	#emit LCTRL                __dat
	#emit SUB.alt
	#emit STOR.S.pri           val
	#emit LREF.S.alt           val
	#emit STOR.S.alt           val
	return val != 120;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script is running on a Windows server currently.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_IsWindowsHost()
{
	// Taken from fixes.inc.
	new
		val = 0;
	// The code at address 0 is always `HALT`.
	#emit LCTRL                __cod
	#emit MOVE.alt
	#emit LCTRL                __dat
	#emit SUB.alt
	#emit STOR.S.pri           val
	#emit LREF.S.alt           val
	#emit STOR.S.alt           val
	return val == 120;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script is running on an open.mp server currently.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Server_IsOpenMP();

// Spell `open.mp` correctly in the function name (because why not).
#define Server_Isopen.mp Server_IsOpenMP
#define Server_Is_open.mp Server_IsOpenMP

#define Server_IsOpenMP() (__OPEN_MP_VERSION != 0)

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script is running on a SA:MP server currently.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Server_IsSAMP();

#define Server_IsSAMP() (__OPEN_MP_VERSION == 0)

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script was compiled with a Linux compiler.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_IsLinuxCompiler`.
stock bool:Server_IsLinuxCompiler()
{
	#if __COMPILER_OS == __COMPILER_UNIX
		return true;
	#else
		return false;
	#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script was compiled with a Linux compiler.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Script_IsLinuxCompiler();

#if __COMPILER_OS == __COMPILER_UNIX
	#define Script_IsLinuxCompiler() (TRUE)
#else
	#define Script_IsLinuxCompiler() (FALSE)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if this script was compiled with a Windows compiler.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_IsWindowsCompiler`.
stock bool:Server_IsWindowsCompiler()
{
	#if __COMPILER_OS == __COMPILER_WINDOWS
		return true;
	#else
		return false;
	#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   <c>true</c> if this script was compiled with a Windows compiler.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Script_IsWindowsCompiler();

#if __COMPILER_OS == __COMPILER_WINDOWS
	#define Script_IsWindowsCompiler() (TRUE)
#else
	#define Script_IsWindowsCompiler() (FALSE)
#endif

static stock const
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscHeader[] = " ========================================== ",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscSpacer[] = " |                                        | ",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscInitMsgA[] = "    Dumping \"pre-init.asm\", this",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscInitMsgB[] = "    Dumping \"post-init.asm\", this",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscInitMsgC[] = "   may take a little bit of time.",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscInitMsgD[] = "            Please wait...",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscDone[] =     "                Done!",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscFailed[] =   "               Failed!",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gsc38[] =   " | %38s | ",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscPreInitFile[] = "pre-init",
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gscPostInitFile[] = "post-init";

native ScriptInit_PrintF__(const fmat[], arg) = printf;

static stock
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gsStartTime,
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gsStartHMS,
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gsStartDMY,
	/**
	 * <library>y_scriptinit</library>
	 */
	bool:YSI_gsObnoxiousHeader = true,
	/**
	 * <library>y_scriptinit</library>
	 */
	bool:YSI_gsFirstHeader = true,
	/**
	 * <library>y_scriptinit</library>
	 */
	bool:YSI_gsNewPart = true,
	/**
	 * <library>y_scriptinit</library>
	 */
	YSI_gsPurgeTimer = 0;

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Store the earliest time of this script starting that we can.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock ScriptInit_GetStartTime()
{
	new h, m, s, d, y;
	YSI_gsStartTime = gettime(),
	gettime(h, m, s),
	YSI_gsStartHMS = (h << 16) | (m << 8) | s,
	getdate(y, m, d),
	YSI_gsStartDMY = (y << 16) | (m << 8) | d;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <param name="usTime">The time in microseconds.</param>
 * <remarks>
 *   Set the time that crashdetect will use when detecting slow functions.
 *   Anything executing for longer than this time will trigger a warning.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_SetLongCallTime(usTime);

#if __COMPILER___EMIT_U
	#define Server_SetLongCallTime(%0) (__emit(LOAD.U.pri %0, SCTRL __crash_time))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Disable the detection of slow functions, if crashdetect exists.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_DisableLongCall();

#if __COMPILER___EMIT_U
	#define Server_DisableLongCall() (__emit(CONST.pri 32, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Enable the detection of slow functions, if crashdetect exists.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_EnableLongCall();

#if __COMPILER___EMIT_U
	#define Server_EnableLongCall() (__emit(CONST.pri 34, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Set the slow code threshold back to the default value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_ResetLongCallTime();

#if __COMPILER___EMIT_U
	#define Server_ResetLongCallTime() (__emit(CONST.pri 36, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Restart the current function's long call timer, if crashdetect exists.  So
 *   the detection of slow code will only account for execution time after this
 *   point.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_RestartLongCall();

#if __COMPILER___EMIT_U
	#define Server_RestartLongCall() (__emit(CONST.pri 40, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if long call (slow code) detection is active.
 * </returns>
 * <remarks>
 *   Check if the crashdetect plugin exists, and long call detection is enabled.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward bool:Server_IsLongCallEnabled();

#if __COMPILER___EMIT_U
	#define Server_IsLongCallEnabled() (bool:(__emit(ZERO.pri, LCTRL __crash_flag, SHR.C.pri 1, CONST.alt 1, AND)))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The current setting (in microseconds) for the slow code warning threshold.
 *   Or <c>0</c> if there is none.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward Server_GetLongCallTime();

#if __COMPILER___EMIT_U
	#define Server_GetLongCallTime() (__emit(ZERO.pri, LCTRL __crash_time))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Disable crashdetect's ability to detect possibly unintended writes to
 *   address naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_DisableDetectAddr0();

#if __COMPILER___EMIT_U
	#define Server_DisableDetectAddr0() (__emit(CONST.pri 64, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Enable crashdetect's ability to detect possibly unintended writes to address
 *   naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_EnableDetectAddr0();

#if __COMPILER___EMIT_U
	#define Server_EnableDetectAddr0() (__emit(CONST.pri 192, SCTRL __crash_flag))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if crashdetect will warn for writes to address naught.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Server_IsDetectAddr0Enabled();

#if __COMPILER___EMIT_U
	#define Server_IsDetectAddr0Enabled() (bool:(__emit(ZERO.pri, LCTRL __crash_flag, SHR.C.pri 7, CONST.alt 1, AND)))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   <c>true</c> if crashdetect is able to warn for writes to address naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward bool:Server_HasDetectAddr0();

#if __COMPILER___EMIT_U
	#define Server_HasDetectAddr0() (bool:(__emit(ZERO.pri, LCTRL __crash_flag, SHR.C.pri 6, CONST.alt 1, AND)))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if crashdetect exists.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward bool:Server_CrashDetectExists();

#if __COMPILER___EMIT_U
	// Could also do `ZERO.alt, NEQ`, but that's the same number of instructions
	// and clobbers `alt`.
	#define Server_CrashDetectExists() (bool:(__emit(ZERO.pri, LCTRL __crash_flag, NOT, NOT)))
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <param name="reason">The halt type.</param>
 * <remarks>
 *   Halt the server, or at least the current public, instantly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_Abort(reason);

#if __COMPILER___EMIT_U
	#define Server_Abort(%0) (__emit(LOAD.U.pri %0, HALT 0))
#endif

forward bool:fautocleanup(const name[], maxAge);

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <param name="filename">Name of the file to write the dump to.</param>
 * <param name="message">Message to show in the console.</param>
 * <remarks>
 *   Write a disassembled version of the current state of the script to a file.
 *   This is by far the most powerful debugging technique I've ever had while
 *   developing YSI.  It is generally called twice - once before
 *   <c>OnCodeInit</c> is run, and once after.  That callback does all of the
 *   assembly-level transformations used to implement many of the advanced YSI
 *   features.  Thus the two resulting dump files can be used to examine and
 *   compare the results of every code rewrite done, and see where things have
 *   gone wrong.  Plus, if anyone has a complex bug I can ask for those two files
 *   and get a very complete view of what their script is trying to do, without
 *   needing any of their source.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock ScriptInit_Dump(const filename[], const message[])
{
		PrintAmxHeader();
		new file[48];
		format(file, sizeof (file), "%s%s.%d.asm", GetYSIScriptfilesDir(E_YSI_DIR_DEBUG), filename, YSI_gsStartTime);
	#if _YSI_SAFE_STARTUP
		#if __debug > 0
			Server_PrintIntroPart(message, YSI_gscInitMsgC, YSI_SPACE, YSI_gscInitMsgD),
		#else
			#pragma unused message
		#endif
		Server_DisableLongCall();
	#else
		#pragma unused message
	#endif
		if (DisasmWrite(file))
		{
			// 1 week.
			fautocleanup(file, 60 * 60 * 24 * 7);
		}
	#if _YSI_SAFE_STARTUP
		Server_EnableLongCall();
		#if __debug > 0
			Server_PrintIntroPart(YSI_SPACE, YSI_gscDone),
			Server_FinishIntroPart();
		#endif
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Print the awesome header that everyone loves in the console.  You're
 *   welcomes everyone!
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Server_PrintYSIHeader()
{
	YSI_Print__("         ==============================================================");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         |    YYYYYYY       YYYYYYY    SSSSSSSSSSSSSSS  IIIIIIIIII    |");
	YSI_Print__("         |    Y:::::Y       Y:::::Y  SS:::::::::::::::S I::::::::I    |");
	YSI_Print__("         |    Y:::::Y       Y:::::Y S:::::SSSSSS::::::S I::::::::I    |");
	YSI_Print__("         |    Y::::::Y     Y::::::Y S:::::S     SSSSSSS II::::::II    |");
	YSI_Print__("         |    YYY:::::Y   Y:::::YYY S:::::S               I::::I      |");
	YSI_Print__("         |       Y:::::Y Y:::::Y    S:::::S               I::::I      |");
	YSI_Print__("         |        Y:::::Y:::::Y      S::::SSSS            I::::I      |");
	YSI_Print__("         |         Y:::::::::Y        SS::::::SSSSS       I::::I      |");
	YSI_Print__("         |          Y:::::::Y           SSS::::::::SS     I::::I      |");
	YSI_Print__("         |           Y:::::Y               SSSSSS::::S    I::::I      |");
	YSI_Print__("         |           Y:::::Y                    S:::::S   I::::I      |");
	YSI_Print__("         |           Y:::::Y                    S:::::S   I::::I      |");
	YSI_Print__("         |           Y:::::Y        SSSSSSS     S:::::S II::::::II    |");
	YSI_Print__("         |        YYYY:::::YYYY     S::::::SSSSSS:::::S I::::::::I    |");
	YSI_Print__("         |        Y:::::::::::Y     S:::::::::::::::SS  I::::::::I    |");
	YSI_Print__("         |        YYYYYYYYYYYYY      SSSSSSSSSSSSSSS    IIIIIIIIII    |");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         |                      (c) 2021 MPL v1.1                     |");
	YSI_Print__("         |            Alex \"Y_Less\" Cole and contributors.            |");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         |                                                            |");
	YSI_Print__("         ==============================================================");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Every parameter to this function is a string, and they are all shown in
 *   order in the console, in a nice box.  If this is the first call it also
 *   shows the amazing beautiful YSI header first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_PrintIntroMessage(...)
{
	#if _YSI_SAFE_STARTUP
		if (YSI_gsObnoxiousHeader)
		{
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_SPACE),
			Server_PrintYSIHeader(),
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_gscHeader),
			YSI_gsObnoxiousHeader = false,
			YSI_gsFirstHeader = false;
		}
		else
	#endif
		if (YSI_gsFirstHeader)
		{
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_gscHeader),
			YSI_gsFirstHeader = false;
		}
		// Header.
		YSI_Print__(YSI_gscSpacer);
		// Body.
		for (new i = 3 * cellbytes, j = (numargs() << __cell_shift) + (3 * cellbytes), a = 0; i != j; i += cellbytes)
		{
			#emit LCTRL          __frm
			#emit LOAD.S.alt     i
			#emit ADD
			#emit LOAD.I
			#emit STOR.S.pri     a
			ScriptInit_PrintF__(YSI_gsc38, a);
		}
		// Footer.
		YSI_Print__(YSI_gscSpacer);
		YSI_Print__(YSI_gscHeader);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Every parameter to this function is a string, and they are all shown in
 *   order in the console, in a nice box.  Unlike <c>Server_PrintIntroMessage</c>
 *   this doesn't close the box, nor does it start a new one if one is already
 *   being written in to.  Thus this one can append messages within a nice box in
 *   the console.  If this is the first call it also shows the loved and adored
 *   YSI header first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_PrintIntroPart(...)
{
	#if _YSI_SAFE_STARTUP
		if (YSI_gsObnoxiousHeader)
		{
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_SPACE),
			Server_PrintYSIHeader(),
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_gscHeader),
			YSI_gsObnoxiousHeader = false,
			YSI_gsFirstHeader = false;
		}
		else
	#endif
		if (YSI_gsFirstHeader)
		{
			YSI_Print__(YSI_SPACE),
			YSI_Print__(YSI_gscHeader),
			YSI_gsFirstHeader = false;
		}
		// Header.
		if (YSI_gsNewPart)
		{
			YSI_gsNewPart = false;
			YSI_Print__(YSI_gscSpacer);
		}
		// Body.
		for (new i = 3 * cellbytes, j = 3 * cellbytes + (numargs() << __cell_shift), a = 0; i != j; i += cellbytes)
		{
			#emit LCTRL          __frm
			#emit LOAD.S.alt     i
			#emit ADD
			#emit LOAD.I
			#emit STOR.S.pri     a
			ScriptInit_PrintF__(YSI_gsc38, a);
		}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   If a box was previously partially written in to with
 *   <c>Server_PrintIntroPart</c> this closes the box off at the bottom.  It
 *   basically just prints a line in the console.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_FinishIntroPart()
{
	// Footer.
	YSI_Print__(YSI_gscSpacer);
	YSI_Print__(YSI_gscHeader);
	YSI_gsNewPart = true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   This is called after all the intro messages have been completed to add
 *   padding.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_FinishIntroMessage()
{
	YSI_Print__(YSI_SPACE),
	YSI_gsFirstHeader = true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Get the start time of the script, previously determined by
 *   <c>ScriptInit_GetStartTime</c>, as a unix timestamp.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_GetStartTime()
{
	return YSI_gsStartTime;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Get the start time of the script, previously determined by
 *   <c>ScriptInit_GetStartTime</c>, as a set of six components for time and
 *   date.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_GetStartDateTime(&year, &month, &day, &hour, &minute, &second)
{
	hour = YSI_gsStartHMS >>> 16,
	minute = YSI_gsStartHMS >>> 8 & 0xFF,
	second = YSI_gsStartHMS & 0xFF,
	year = YSI_gsStartDMY >>> 16,
	month = YSI_gsStartDMY >>> 8 & 0xFF,
	day = YSI_gsStartDMY & 0xFF;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Is a version of the crashdetect plugin loaded that we can control long call
 *   detection in via registers.  There were several releases where this just
 *   didn't work properly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Server_HasLongCallControl()
{
	// This code detects if the `0xFE` long call control register works.  If it
	// doesn't this could be an old version of crashdetect, one with
	// `long_call_time 0` in `server.cfg`, or a bugged Linux version.  See
	//
	//   https://github.com/Zeex/samp-plugin-crashdetect/commit/4146ae379ebad8a0a4eb38a7e0af3bcfe7a89bd5
	//
	// Unfortunately there's no way to distinguish these three cases (I tried).
	// Even attempting to enable things won't work for any of those cases.
	if (Server_IsLongCallEnabled())
		return true;
	Server_EnableLongCall();
	if (Server_IsLongCallEnabled())
	{
		Server_DisableLongCall();
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Get the default long call time for crashdetect.  May not be the current
 *   setting.  Simply stores the current value, resets it, restores the current
 *   and returns the old version.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// `GetCrashDetectDefaultLongCallTime` is too long.
stock Server_GetLongCallDefault()
{
	// Store the current value.
	#emit ZERO.pri
	#emit LCTRL         __crash_time
	#emit MOVE.alt
	// Reset to and read the default.
	#emit CONST.pri     36
	#emit SCTRL         __crash_flag
	#emit ZERO.pri
	#emit LCTRL         __crash_time
	// Put the current value back.
	#emit XCHG
	#emit SCTRL         __crash_time
	#emit MOVE.pri
	#emit RETN
	return 0;
}

#if !defined YSI_YES_MODE_CACHE
	#define YSI_NO_MODE_CACHE
	#define YSI_NO_CACHE_MESSAGE
#endif

#if !defined YSI_NO_MODE_CACHE
	#if !defined DumpAMX_Included_ && !defined YSI_YES_MODE_CACHE && !__COMPILER_1ST_PASS
		#define YSI_NO_MODE_CACHE
		#define YSI_NO_CACHE_MESSAGE
	#endif
#endif

forward bool:Debug_Enable();

#if !defined _ALS_OnCachedInit
	forward OnCachedInit();
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <param name="jit">We are calling the callback from the JIT plugin.</param>
 * <param name="fs">We are calling the callback in a filterscript.</param>
 * <remarks>
 *   This is seemingly a lot of code just to call a callback, but it does more
 *   than that.  Really this is <c>OnScriptInit</c> for this file - it calls
 *   other callbacks, dumps debug information, profiles the startup, and caches
 *   compilation results.  These steps are all done regardless of which callback
 *   gets triggered first, hence why the code is abstracted.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static bool:ScriptInit_CallOnCodeInit(bool:jit, bool:fs)
{
	Debug_Enable();
	#if defined _DEBUG
		#if _DEBUG > 0
			new preHeap, postHeap;
			preHeap = heapspace();
		#endif
	#endif
	{
		#if _YSI_SAFE_STARTUP
			#if __debug <= 0
				Debug_Info("Version: %02d.%02d.%04d", YSI_VERSION_MAJOR, YSI_VERSION_MINOR, YSI_VERSION_BUILD);
			#endif
		#else
			YSI_PrintF__("Unsafe YSI signed by: %s", YSI_gcUnsafeStartupContract);
		#endif
		if (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD)
		{
			// Loaded from a file.
			#if _YSI_SAFE_STARTUP
				#if __debug > 0
					Server_PrintIntroMessage("   File loaded from YSI code cache.");
				#endif
			#endif
				R@("OnCachedInit", YSI_EMPTY);
		}
		else
		{
			#if defined YSI_NO_MODE_CACHE
				#pragma unused fs
			#else
				#if defined __date && defined __time && defined YSI_AUTO_LOAD_CACHE
					new name[64];
					format(name, sizeof (name), "YSI_CACHE.%s.%s", __date, __time);
					if (fexist(name))
					{
						if (jit)
						{
							Debug_Warning("Could not auto-load YSI cache - script type (GM/FS) cannot be determined with JIT.");
							strcat(name, ".amx");
						}
						else if (fs)
						{
							Debug_Warning("Could not auto-load YSI cache - current filterscript cannot be unloaded.");
							strcat(name, ".amx");
						}
						else
						{
							Server_EnableLongCall();
							format(name, sizeof (name), "changemode ../scriptfiles/%s", name);
							SendRconCommand(name)
							return false;
						}
					}
					else
					{
						strcat(name, ".amx");
					}
				#else
					#pragma unused fs
					static const name[] = "YSI_CACHE.amx";
				#endif
			#endif
				Server_DisableLongCall();
			#if _YSI_SAFE_STARTUP
				#if __debug > 0
					if (jit)
					{
						Server_PrintIntroPart(
							"  Generating code, this may take a",
							"         little bit of time.",
							YSI_SPACE,
							YSI_gscInitMsgD
						);
					}
					else
					{
						Server_PrintIntroPart(
							"  Generating code, this may take a",
							" little bit of time.  Note that this",
							" code generation works best with the",
							"    JIT plugin, which you are not",
							"    currently using.  Get it here:",
							YSI_SPACE,
							"      https://git.io/jit-plugin",
							YSI_SPACE,
							YSI_gscInitMsgD
						);
					}
					new t0, t1;
					t0 = GetTickCount();
				#endif
				#pragma unused jit
			#else
				#pragma unused jit
			#endif
				ScriptInit_CodeInitFuncs_();
			#if defined ScriptInit_OnCodeInit
				ScriptInit_OnCodeInit();
			#endif
			#if _YSI_SAFE_STARTUP
				#if __debug > 0
					t1 = GetTickCount();
					new str[32];
					format(str, sizeof (str), "            Done in %dms!", t1 - t0);
					Server_PrintIntroPart(YSI_SPACE, str);
					Server_FinishIntroPart();
				#endif
			#endif
			#if defined ScriptInit_OnYSIInit
				ScriptInit_OnYSIInit();
			#endif
			#if !defined YSI_NO_MODE_CACHE
				new
					E_SCRIPTINIT_STATE:tmp = YSI_g_sScriptInitState & (E_SCRIPTINIT_STATE_JITING | E_SCRIPTINIT_STATE_JITED);
				// Set the variable to something unique for next load.  This will be
				// written out, thus loaded in next time.
				YSI_g_sScriptInitState = E_SCRIPTINIT_STATE_RELOAD;
				#if _YSI_SAFE_STARTUP
					#if __debug > 0
						Server_PrintIntroPart(
							" Dumping \"YSI_CACHE.amx\", this may",
							"     take a little bit of time.",
							YSI_SPACE,
							YSI_gscInitMsgD
						);
					#endif
				#endif
				if (DumpAMX_Write(name))
				{
					#if _YSI_SAFE_STARTUP
						#if __debug > 0
							Server_PrintIntroPart(YSI_SPACE, YSI_gscDone);
							Server_FinishIntroPart();
						#endif
					#endif
						// Clear this flag after dumping.  This is so we can tell
						// when a mode is cached.
						YSI_g_sScriptInitState = tmp | E_SCRIPTINIT_STATE_DUMPED;
					#if _YSI_SAFE_STARTUP
						#if __debug > 0
							Server_PrintIntroMessage(
								"    File dumped to YSI code cache:",
								YSI_SPACE,
								"       scriptfiles/YSI_CACHE.amx",
								YSI_SPACE,
								"Load this file instead to skip this",
								"code optimisation step in the future.",
								"Note that if you have multiple scripts",
								"loading at once (i.e. gamemodes,",
								"filterscripts, and modules) you may",
								"need to load and cache them",
								"individually so that they don't",
								"clobber each other.  If you don't, in",
								"\"server.cfg\", the following works:",
								YSI_SPACE,
								"  gamemode0 ../scriptfiles/YSI_CACHE 1"
							);
						#endif
					#endif
				}
				else
				{
					#if _YSI_SAFE_STARTUP
						#if __debug > 0
							Server_PrintIntroPart(YSI_SPACE, YSI_gscFailed);
							Server_FinishIntroPart();
						#endif
					#endif
						YSI_g_sScriptInitState = tmp;
						Debug_Error("YSI code cache write failed");
				}
			#endif
				Server_RestartLongCall();
				Server_EnableLongCall();
		}
	}
	#if defined _DEBUG
		#if _DEBUG > 0
			postHeap = heapspace();
			if (preHeap != postHeap)
			{
				Debug_Warning("Heapspace leak in `OnCodeInit`.");
			}
		#endif
	#endif
	return true;
}

#if !defined _ALS_OnJITCompile
	forward OnJITCompile();
#endif

/**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Called when the JIT plugin starts.  Used to determine that the plugin
 *   exists (and remember that fact for later), and to compile YSI (and other)
 *   code before JIT compilation.  Thus calls <c>OnCodeInit</c>.
 * </remarks>
 */

public OnJITCompile()
{
	state _ALS : _ALS_go;
	state _script_init_fix_state : false;
	// Got it being called twice for some reason.  I think it was a file glitch,
	// but just make sure.
	if (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING)
	{
		return 0;
	}
	ScriptInit_GetStartTime();
	#if _YSI_SAFE_STARTUP
		ResolveYSIScriptfileDirs();
	#endif
	DEBUG_MAYBE_DUMP(YSI_gscPreInitFile, YSI_gscInitMsgA);
	YSI_g_sScriptInitState |= E_SCRIPTINIT_STATE_JITING;
	if (!ScriptInit_CallOnCodeInit(true, false))
		return 0;
	new ret = ScriptInit_OnJITCompile();
	if (ret)
	{
		YSI_g_sScriptInitState |= E_SCRIPTINIT_STATE_JITED;
	}
	else
	{
		Debug_Warning("JIT disabled");
	}
	DEBUG_MAYBE_DUMP(YSI_gscPostInitFile, YSI_gscInitMsgB);
	#if _YSI_SAFE_STARTUP
		#if __debug > 0
			Server_FinishIntroMessage();
		#endif
	#endif
	return ret;
}

/*

    88             88          
    88             ""   ,d     
    88                  88     
    88 8b,dPPYba,  88 MM88MMM  
    88 88P'   `"8a 88   88     
    88 88       88 88   88     
    88 88       88 88   88,    
    88 88       88 88   "Y888  

*/

#define @yI_%0\32; @yI_
#define @_yI%0\32; @_yI
#define @y_I%0\32; @y_I
#define @I_y%0\32; @I_y
#define @Iy_%0\32; @Iy_
#define @_Iy%0\32; @_Iy

#define y_@I%0\32; y_@I

#define __script_init_u@_1
// Can't `#undef` this because it declares a `forward` with the same name.
#define u@$ 1]);

// Detect tags.
#define _@Iy:%8$%3:%0(%1)<_> %8$%0(%1)<%3>

// Detect arrays, on `final` only.
#define _@yI:_I@y:%8$%0[%4]%9(%1)<%3> %8$@yI_%0();@yI_%0(){new %3:y__[sizeof(%0)];y_@I%0(y__);_YSI_ConstCpy__(_:%0,_:y__,0,sizeof y__*4,sizeof y__);}static y_@I%0(%3:y__[sizeof(%0)])y__=

// Finish inits.
#define _y@I:%8$%0(%1)<%3>(%2) %8$%3:%2%0(%1);%3:%2%0(%1)


// Finish final.
#define _I@y:%8$%0(%1)<%3> %8$@yI_%0();@yI_%0(){new %3:y__;y_@I%0(y__);_YSI_ConstMod(_:%0,_:y__);}static y_@I%0(&%3:y__)y__=

// The assignment to `I@` is so any custom assignment operators are called and to check the tag is
// correct, or give a mismatch warning.

#define DO_YSI_INIT__%0(%1)<%2> u@(u[_:_@Iy:_y@I:u@$%0(%1)<_>(%2)

#define PREINIT__%0(%1) DO_YSI_INIT__%0(%1)<@yI_>
#define POSTINIT__%0(%1) DO_YSI_INIT__%0(%1)<@_yI>

#define PREEXIT__%0(%1) DO_YSI_INIT__%0(%1)<@Iy_>
#define POSTEXIT__%0(%1) DO_YSI_INIT__%0(%1)<@_Iy>

// New decorator:
//
//   @init(init_code) B()           // OnCodeInit
//   @init() A()                    // OnScriptInit
//   @init(init_script) F()         // OnScriptInit
//   @init(.order = init_mode) C()  // OnGameModeInit
//   @init(init_mode) D()           // OnFilterScriptInit
//   @init(.order = init_main) E()  // main
//
#define @init(%2)%0(%1) u@(u[_:Iy_@:y_I@%2:u@$@yI_%0(%1);@yI_%0(%1)
#define @exit(%2)%0(%1) u@(u[_:Iy_@:yI_@%2:u@$@Iy_%0(%1);@Iy_%0(%1)

/// <p/>

/**
 * <library>y_scriptinit</library>
 * <remarks>
 *   When to call an <c>@init()</c> function.
 * </remarks>
 */

enum init_order
{
	init_code,   // OnCodeInit
	init_script, // OnScriptInit
	init_mode,   // OnGameModeInit/OnFilterScriptInit
	init_main    // main
}

static stock init_order:_@init_order() { return init_order; }

/// <p/>

/**
 * <library>y_scriptinit</library>
 * <remarks>
 *   When to call an <c>@exit()</c> function.
 * </remarks>
 */

enum exit_order
{
	exit_mode,   // OnGameModeExit/OnFilterScriptExit
	exit_script  // OnScriptExit
}

static stock exit_order:_@exit_order() { return exit_order; }

// Strip all spaces within the parameters first.
#define Iy_@:%0\32;%1$ Iy_@:%0%1$

// Detect the parameters, with or without names.
#define y_I@.%4=%5: y_I@%4=%5:
#define y_I@order=%5: y_I@%5:
#define y_I@init_code:%8$@yI_%0(%1);@yI_%0(%1) %8$@y_I%0(%1);@y_I%0(%1)
#define y_I@init_script:%8$@yI_%0(%1);@yI_%0(%1) %8$@yI_%0(%1);@yI_%0(%1)
#define y_I@init_mode:%8$@yI_%0(%1);@yI_%0(%1) %8$@_yI%0(%1);@_yI%0(%1)
#define y_I@init_main:%8$@yI_%0(%1);@yI_%0(%1) %8$@I_y%0(%1);@I_y%0(%1)

// And do the same for `exit`, but with fewer options.
#define yI_@.%4=%5: yI_@%4=%5:
#define yI_@order=%5: yI_@%5:
#define yI_@exit_script:%8$@Iy_%0(%1);@Iy_%0(%1) %8$@Iy_%0(%1);@Iy_%0(%1)
#define yI_@exit_mode:%8$@Iy_%0(%1);@Iy_%0(%1) %8$@_Iy%0(%1);@_Iy%0(%1)

// Alternative spellings.
#define PRE_INIT__ PREINIT__
#define POST_INIT__ POSTINIT__
#define PRE_EXIT__ PREEXIT__
#define POST_EXIT__ POSTEXIT__

#define FINAL__%0= stock const %0;u@(u[_:_@Iy:_@yI:_I@y:u@$%0()<_>

#if YSI_KEYWORD(final)
	#define final FINAL__
#endif

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

 #if defined _ALS_OnCodeInit || defined OnCodeInit
	#error OnCodeInit defined
#endif

//#if _YSI_SAFE_STARTUP
//	// open.mp
//	forward OnScriptInit(id);
//
//	public OnScriptInit(id)
//	{
//		state _ALS : _ALS_go;
//		state _script_init_fix_state : false;
//		// Dump the final assembly of this script so we can inspect it.
//		if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
//		{
//			ScriptInit_GetStartTime();
//			ResolveYSIScriptfileDirs();
//			DEBUG_MAYBE_DUMP(YSI_gscPreInitFile, YSI_gscInitMsgA);
//			if (!ScriptInit_CallOnCodeInit(false, true))
//				return 0;
//		}
//		YVers_StartCheck();
//		Server_FinishIntroMessage();
//		#if defined ScriptInit_OnYSIInit
//			ScriptInit_OnYSIInit();
//		#endif
//		ScriptInit_PreInitFuncs_();
//		CallLocalFunction("OnScriptInit@A", YSI_EMPTY);
//		ScriptInit_PostInitFuncs_();
//		if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
//		{
//			// Dump the final assembly of this script so we can inspect it.
//			DEBUG_MAYBE_DUMP(YSI_gscPostInitFile, YSI_gscInitMsgB);
//		}
//		Server_FinishIntroMessage();
//		CallLocalFunction("OnScriptInit@C", YSI_EMPTY);
//		CallLocalFunction("OnScriptInit@E", YSI_EMPTY);
//		return 1;
//	}
//#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 * <remarks>
 *   Call <c>OnScriptInit</c> in filterscripts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
			state _ALS : _ALS_go;
		#if _YSI_SAFE_STARTUP
			YSI_FILTERSCRIPT = true;
			//if (Server_IsSAMP())
		#endif
			{
				state _script_init_fix_state : true;
				// Dump the final assembly of this script so we can inspect it.
				if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
				{
					ScriptInit_GetStartTime();
					#if _YSI_SAFE_STARTUP
						ResolveYSIScriptfileDirs();
					#endif
					DEBUG_MAYBE_DUMP(YSI_gscPreInitFile, YSI_gscInitMsgA);
					if (!ScriptInit_CallOnCodeInit(false, true))
						return 0;
				}
				YVers_StartCheck();
				#if _YSI_SAFE_STARTUP
					Server_FinishIntroMessage();
				#endif
				ScriptInit_PreInitFuncs_();
				Server_RestartLongCall();
				CallLocalFunction("OnScriptInit", YSI_EMPTY);
				ScriptInit_PostInitFuncs_();
				if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
				{
					// Dump the final assembly of this script so we can inspect it.
					DEBUG_MAYBE_DUMP(YSI_gscPostInitFile, YSI_gscInitMsgB);
				}
				#if _YSI_SAFE_STARTUP
					Server_FinishIntroMessage();
				#endif
				#if defined YSI_LOCK_MODE
					#if defined FILTERSCRIPT
						if (strlen(YSI_gLockData[5]) !=
							floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_1 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_2 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_3 + 1), floatround_ceil))
						{
							y_lock 6;
						}
					#else
						new
							str[16];
						format(str, sizeof (str), "%c%c%c%c%c%c%c%c%c%c%c", '%', 'd', '.', '%', 'd', '.', '%', 'd', '.', '%', 'd');
						format(str, sizeof (str), str, _LOCK_IP_0, _LOCK_IP_1, _LOCK_IP_2, _LOCK_IP_3);
						if (strlen(YSI_gLockData[5]) != strlen(str))
						{
							y_lock 7;
						}
					#endif
				#endif
				Server_RestartLongCall();
				CallLocalFunction("OnScriptInit@C", YSI_EMPTY);
			}
			return 1;
	}
#else
	static stock ScriptInit_OnFilterScriptInit__()
	{
	}
#endif

forward File:ftemporary_(name[], const ext[] = "tmp", const path[] = "", len = sizeof (name));

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Delete temporary files that have reached their maximum age.  Related to
 *   <c>ftemporary</c>, which only stores files for a limited period.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock ScriptInit_PurgeTemporaries()
{
	if (!fexist(YSI_TEMP_FILE_NAME))
	{
		goto ScriptInit_Purge_retry;
	}
	new
		File:in = fopen(YSI_TEMP_FILE_NAME, io_read),
		bool:change = false,
		tmp[32],
		File:out = ftemporary_(tmp, "ysi"),
		line[YSI_TEMP_FILE_LENGTH + 64],
		now = gettime(),
		then = 0;
	if (!in)
	{
		if (out)
			goto ScriptInit_Purge_clean;
		goto ScriptInit_Purge_retry;
	}
	else if (!out)
	{
		fclose(in);
		goto ScriptInit_Purge_retry;
	}
	// Read the whole file, looking for expired files.
	while (fread(in, line))
	{
		then = strval(line);
		if (then && then < now)
		{
			then = strlen(line);
			if (line[then - 1] <= ' ')
				line[then - 1] = '\0';
			if (line[then - 2] <= ' ')
				line[then - 2] = '\0';
			change = true;
			// Release this file.
			fremove(line[strfind(line, YSI_SPACE) + 1]);
		}
		else
		{
			fwrite(out, line);
		}
	}
	if (change)
	{
		fclose(in);
		in = fopen(YSI_TEMP_FILE_NAME, io_write);
		if (!in)
			goto ScriptInit_Purge_clean;
		// Copy the data back, without now deleted lines.
		fseek(out, 0, seek_start);
		while (fread(out, line))
		{
			fwrite(in, line);
		}
	}
	fclose(in);
ScriptInit_Purge_clean:
	fclose(out);
	fremove(tmp);
	// Recheck once an hour.
ScriptInit_Purge_retry:
	YSI_gsPurgeTimer = SetTimer(&ScriptInit_PurgeTemporaries<>, 1000 * 60 * 60, false);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 * <remarks>
 *   Call <c>OnScriptInit</c> in gamemodes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	public OnGameModeInit()
	{
			state _ALS : _ALS_go;
			// Kill an existing purge if one exists in this script.
		#if _YSI_SAFE_STARTUP
			if (!YSI_FILTERSCRIPT && /*Server_IsSAMP() &&*/ !(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		#else
			if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		#endif
			{
				ScriptInit_GetStartTime();
				#if _YSI_SAFE_STARTUP
					ResolveYSIScriptfileDirs();
				#endif
			}
			if (YSI_gsPurgeTimer)
			{
				KillTimer(YSI_gsPurgeTimer);
				YSI_gsPurgeTimer = 0;
			}
			// Start a new purge if this is the first script called.
			if (!existproperty(8, "Purge"))
			{
				setproperty(8, "Purge", 1);
				ScriptInit_PurgeTemporaries();
			}
		#if _YSI_SAFE_STARTUP
			if (!Script_IsFilterscript())
		#endif
			{
		#if _YSI_SAFE_STARTUP
				YSI_GAMEMODE = true;
				//if (Server_IsSAMP())
		#endif
				{
					state _script_init_fix_state : false;
					// Dump the final assembly of this script so we can inspect it.
					if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
					{
						DEBUG_MAYBE_DUMP(YSI_gscPreInitFile, YSI_gscInitMsgA);
						if (!ScriptInit_CallOnCodeInit(false, false))
							return 0;
					}
					YVers_StartCheck();
					#if _YSI_SAFE_STARTUP
						Server_FinishIntroMessage();
					#endif
					ScriptInit_PreInitFuncs_();
					Server_RestartLongCall();
					CallLocalFunction("OnScriptInit", YSI_EMPTY);
					ScriptInit_PostInitFuncs_();
					if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
					{
						// Dump the final assembly of this script so we can inspect it.
						DEBUG_MAYBE_DUMP(YSI_gscPostInitFile, YSI_gscInitMsgB);
					}
					#if _YSI_SAFE_STARTUP
						Server_FinishIntroMessage();
					#endif
					#if defined YSI_LOCK_MODE
						if (YSI_gLockData[
							floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_1 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_2 + 1), floatround_ceil) +
							floatround(floatlog(_LOCK_LEN_3 + 1), floatround_ceil)] == '\0'
						 || YSI_gLockData[
							floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_1 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_2 + 1), floatround_ceil) + 1 +
							floatround(floatlog(_LOCK_LEN_3 + 1), floatround_ceil) + 1] == '\0')
						{
							y_lock 8;
						}
					#endif
				}
			}
		#if _YSI_SAFE_STARTUP
			//if (Server_IsSAMP())
		#endif
			{
				Server_RestartLongCall();
				CallLocalFunction("OnScriptInit@E", YSI_EMPTY);
			}
			return 1;
	}
#else
	static stock ScriptInit_OnGameModeInit__()
	{
	}
#endif

/*

    88888888888             88          
    88                      ""   ,d     
    88                           88     
    88aaaaa     8b,     ,d8 88 MM88MMM  
    88"""""      `Y8, ,8P'  88   88     
    88             )888(    88   88     
    88           ,d8" "8b,  88   88,    
    88888888888 8P'     `Y8 88   "Y888  

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 * <remarks>
 *   Call <c>OnScriptExit</c> in filterscripts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	public OnFilterScriptExit()
	{
		ScriptInit_OnFilterScriptExit();
#if _YSI_SAFE_STARTUP
		if (YSI_FILTERSCRIPT /*&& Server_IsSAMP()*/)
#endif
		{
			ScriptInit_PreExitFuncs_();
			ScriptInit_OnScriptExit();
			ScriptInit_PostExitFuncs_();
			ScriptInit_OnYSIExit();
		}
		return 1;
	}
#else
	static stock ScriptInit_OnFilterScriptExit__()
	{
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 * <remarks>
 *   Call <c>OnScriptExit</c> in gamemodes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	public OnGameModeExit()
	{
		ScriptInit_OnGameModeExit();
#if _YSI_SAFE_STARTUP
		if (YSI_GAMEMODE /*&& Server_IsSAMP()*/)
#endif
		{
			ScriptInit_PreExitFuncs_();
			ScriptInit_OnScriptExit();
			ScriptInit_PostExitFuncs_();
			ScriptInit_OnYSIExit();
		}
		return 1;
	}
#else
	static stock ScriptInit_OnGameModeExit__()
	{
	}
#endif

//#if _YSI_SAFE_STARTUP
//	forward OnScriptExit(id);
//
//	public OnScriptExit(id)
//	{
//		if (YSI_OPEN_MP)
//		{
//			ScriptInit_PreExitFuncs_();
//			ScriptInit_OnScriptExit();
//			ScriptInit_PostExitFuncs_();
//			ScriptInit_OnYSIExit();
//		}
//		return 1;
//	}
//#endif

/*

    88888888888                                                                      88            
    88                                                                               88            
    88                                                                               88            
    88aaaaa  ,adPPYba,  8b,dPPYba, 8b      db      d8 ,adPPYYba, 8b,dPPYba,  ,adPPYb,88 ,adPPYba,  
    88""""" a8"     "8a 88P'   "Y8 `8b    d88b    d8' ""     `Y8 88P'   "Y8 a8"    `Y88 I8[    ""  
    88      8b       d8 88          `8b  d8'`8b  d8'  ,adPPPPP88 88         8b       88  `"Y8ba,   
    88      "8a,   ,a8" 88           `8bd8'  `8bd8'   88,    ,88 88         "8a,   ,d88 aa    ]8I  
    88       `"YbbdP"'  88             YP      YP     `"8bbdP"Y8 88          `"8bbdP"Y8 `"YbbdP"'  

*/

#define _ALS_OnCodeInit
#define OnCodeInit ScriptInit_OnCodeInit
#if defined ScriptInit_OnCodeInit
	forward ScriptInit_OnCodeInit();
#endif

//#define _ALS_OnScriptInit
//#define OnScriptInit(%0) OnScriptInit@A(%0)
forward OnScriptInit PP_LEFT_BRACKET<>PP_RIGHT_BRACKET<>;

CHAIN_FORWARD:ScriptInit_OnJITCompile() = 1;
#if defined _ALS_OnJITCompile
	#undef OnJITCompile
#else
	#define _ALS_OnJITCompile
#endif
#define OnJITCompile(%0) CHAIN_PUBLIC:ScriptInit_OnJITCompile(%0)

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit( OnScriptInit@C(
	#if defined OnScriptInit@C
		forward OnScriptInit@C();
	#endif
#endif

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit( OnScriptInit@E(
	#if defined OnScriptInit@E
		forward OnScriptInit@E();
	#endif
#endif

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	CHAIN_FORWARD:ScriptInit_OnFilterScriptExit() = 1;
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit(%0) CHAIN_PUBLIC:ScriptInit_OnFilterScriptExit(%0)
#endif

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	CHAIN_FORWARD:ScriptInit_OnGameModeExit() = 1;
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit(%0) CHAIN_PUBLIC:ScriptInit_OnGameModeExit(%0)
#endif

CHAIN_FORWARD:ScriptInit_OnScriptExit() = 1;
#if defined _ALS_OnScriptExit
	#undef OnScriptExit
#else
	#define _ALS_OnScriptExit
#endif
#define OnScriptExit(%0) CHAIN_PUBLIC:ScriptInit_OnScriptExit(%0)

CHAIN_FORWARD:ScriptInit_OnYSIInit() = 1;
#if defined _ALS_OnYSIInit
	#undef OnYSIInit
#else
	#define _ALS_OnYSIInit
#endif
#define OnYSIInit(%0) CHAIN_PUBLIC:ScriptInit_OnYSIInit(%0)

CHAIN_FORWARD:ScriptInit_OnYSIExit() = 1;
#if defined _ALS_OnYSIExit
	#undef OnYSIExit
#else
	#define _ALS_OnYSIExit
#endif
#define OnYSIExit(%0) CHAIN_PUBLIC:ScriptInit_OnYSIExit(%0)

#if !defined _ALS_OnRuntimeError
	forward OnRuntimeError(code, &bool:suppress);
#endif

/*

     ad88888ba  88                                      88                                             
    d8"     "8b 88                        ,d            88                                             
    Y8,         88                        88            88                                             
    `Y8aaaaa,   88,dPPYba,  88       88 MM88MMM ,adPPYb,88  ,adPPYba,  8b      db      d8 8b,dPPYba,   
      `"""""8b, 88P'    "8a 88       88   88   a8"    `Y88 a8"     "8a `8b    d88b    d8' 88P'   `"8a  
            `8b 88       88 88       88   88   8b       88 8b       d8  `8b  d8'`8b  d8'  88       88  
    Y8a     a8P 88       88 "8a,   ,a88   88,  "8a,   ,d88 "8a,   ,a8"   `8bd8'  `8bd8'   88       88  
     "Y88888P"  88       88  `"YbbdP'Y8   "Y888 `"8bbdP"Y8  `"YbbdP"'      YP      YP     88       88 

*/

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 * <remarks>
 *   I'm not quite sure what causes it, but there seems to be a bug in the
 *   compiler somewhere which messes up the <c>ysi_debug</c> automaton and the
 *   <c>YSI_FILTERSCRIPT</c> variable :(.
 *   <p />
 *   I eventually figured this one out:
 *   <p />
 *       https://github.com/pawn-lang/compiler/issues/666
 *   <p />
 *   So this fix is probably no longer needed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public _ScriptInit_FixState() <_script_init_fix_state : true>
{
}

public _ScriptInit_FixState() <_script_init_fix_state : false>
{
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if crashdetect needs updating.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_UpgradeCrashDetect()
{
	// Test `LCTRL(255) & 0x11 == 0x01`.  If that's true we have an older
	// version of crashdetect.
	#emit ZERO.pri
	#emit LCTRL         __crash_flag
	#emit CONST.alt     33
	#emit AND
	#emit CONST.alt     1
	#emit EQ
	#emit RETN
	return false;
}

// Don't let anyone else call this function.
#define ScriptInit_PrintF__ ScriptInit_PrintF

#if __COMPILER___EMIT_U
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <param name="usTime">The time in microseconds.</param>
 * <remarks>
 *   Set the time that crashdetect will use when detecting slow functions.
 *   Anything executing for longer than this time will trigger a warning.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_SetLongCallTime(usTime)
{
	#emit LOAD.S.pri    usTime
	#emit SCTRL         __crash_time
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Disable the detection of slow functions, if crashdetect exists.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_DisableLongCall()
{
	#emit CONST.pri     32
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Enable the detection of slow functions, if crashdetect exists.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_EnableLongCall()
{
	#emit CONST.pri     34
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Set the slow code threshold back to the default value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_ResetLongCallTime()
{
	#emit CONST.pri     36
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Restart the current function's long call timer, if crashdetect exists.  So
 *   the detection of slow code will only account for execution time after this
 *   point.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_RestartLongCall()
{
	#emit CONST.pri     40
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if long call (slow code) detection is active.
 * </returns>
 * <remarks>
 *   Check if the crashdetect plugin exists, and long call detection is enabled.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Server_IsLongCallEnabled()
{
	#emit ZERO.pri
	#emit LCTRL         __crash_flag
	#emit SHR.C.pri     1
	#emit CONST.alt     1
	#emit AND
	#emit RETN
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The current setting (in microseconds) for the slow code warning threshold.
 *   Or <c>0</c> if there is none.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Server_GetLongCallTime()
{
	#emit ZERO.pri
	#emit LCTRL         __crash_time
	#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Disable crashdetect's ability to detect possibly unintended writes to
 *   address naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_DisableDetectAddr0()
{
	#emit CONST.pri     64
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Enable crashdetect's ability to detect possibly unintended writes to address
 *   naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_EnableDetectAddr0()
{
	#emit CONST.pri     192
	#emit SCTRL         __crash_flag
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if crashdetect will warn for writes to address naught.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_IsDetectAddr0Enabled()
{
	// Is the check enabled?  0 if off or doesn't exist.
	#emit ZERO.pri
	#emit LCTRL         __crash_flag
	#emit SHR.C.pri     7
	#emit CONST.alt     1
	#emit AND
	#emit RETN
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   <c>true</c> if crashdetect is able to warn for writes to address naught.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Server_HasDetectAddr0()
{
	// Is the check possible?
	#emit ZERO.pri
	#emit LCTRL         __crash_flag
	#emit SHR.C.pri     6
	#emit CONST.alt     1
	#emit AND
	#emit RETN
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   <c>true</c> if crashdetect exists.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Server_CrashDetectExists()
{
	// 0xFF is roughly flags, but some are mutually exclusive:
	//
	//   1 - Present (read only, write always 0).
	//   2 - long_call_time checks enabled (write ignored when `server.cfg` has `long_call_time 0`).
	//   4 - long_call_time reset to default time (write only, read always 0).
	//   8 - long_call_time restart check from now (write only, read always 0).
	//
	// `!!pri` is the same number of instructions as `pri != 0`, but doesn't
	// clobber `alt`.  This doesn't matter in this function, but might in the
	// inline version.
	#emit ZERO.pri
	#emit LCTRL         __crash_flag
	#emit NOT
	#emit NOT
	#emit RETN
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <param name="reason">The halt type.</param>
 * <remarks>
 *   Halt the server, or at least the current public, instantly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock void:Server_Abort(reason)
{
	#emit LOAD.S.pri    reason
	#emit HALT          0
}

