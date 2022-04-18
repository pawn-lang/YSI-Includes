/*
	
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

forward _ScriptInit_FixState();

CHAIN_HOOK(ScriptInit)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(ScriptInit)

stock
	#if _YSI_SAFE_STARTUP
		bool:YSI_GAMEMODE = false,
		bool:YSI_OPEN_MP = false,
	#endif
		bool:YSI_FILTERSCRIPT = false;

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

static
	E_SCRIPTINIT_STATE:YSI_g_sScriptInitState = E_SCRIPTINIT_STATE_NONE;

#define Debug_PrintE(%1); \
	Debug_Print0("\7\7\7*** YSI Error: " #%1);

#if defined _DEBUG
	#if _DEBUG > 0
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
	#endif
#endif
#if !defined DEBUG_MAYBE_DUMP
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

stock bool:Server_JITExists()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING) != E_SCRIPTINIT_STATE_NONE;
}

#pragma deprecated Use `Script_JITComplete`.
stock bool:Server_JITComplete()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITED) != E_SCRIPTINIT_STATE_NONE;
}

stock bool:Script_JITComplete()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITED) != E_SCRIPTINIT_STATE_NONE;
}

#pragma deprecated Use `Script_CacheLoaded`.
stock bool:Server_CacheLoaded()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD) != E_SCRIPTINIT_STATE_NONE;
}

stock bool:Script_CacheLoaded()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD) != E_SCRIPTINIT_STATE_NONE;
}

#pragma deprecated Use `Script_CacheSaved`.
stock bool:Server_CacheSaved()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_DUMPED) != E_SCRIPTINIT_STATE_NONE;
}

stock bool:Script_CacheSaved()
{
	return (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_DUMPED) != E_SCRIPTINIT_STATE_NONE;
}

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

#if _YSI_SAFE_STARTUP
	#define Script_IsFilterscript() (YSI_FILTERSCRIPT)
#elseif defined FILTERSCRIPT
	#define Script_IsFilterscript() (TRUE)
#else
	#define Script_IsFilterscript() (FALSE)
#endif

stock bool:Server_IsLinuxHost()
{
	// Taken from fixes.inc.
	new
		val = 0;
	// The code at address 0 is always `HALT`.
	#emit LCTRL                0
	#emit MOVE.alt
	#emit LCTRL                1
	#emit SUB.alt
	#emit STOR.S.pri           val
	#emit LREF.S.alt           val
	#emit STOR.S.alt           val
	return val != 120;
}

stock bool:Server_IsWindowsHost()
{
	// Taken from fixes.inc.
	new
		val = 0;
	// The code at address 0 is always `HALT`.
	#emit LCTRL                0
	#emit MOVE.alt
	#emit LCTRL                1
	#emit SUB.alt
	#emit STOR.S.pri           val
	#emit LREF.S.alt           val
	#emit STOR.S.alt           val
	return val == 120;
}

#pragma deprecated Use `Script_IsLinuxCompiler`.
stock bool:Server_IsLinuxCompiler()
{
	#if __COMPILER_OS == __COMPILER_LINUX
		return true;
	#else
		return false;
	#endif
}

stock bool:Script_IsLinuxCompiler()
{
	#if __COMPILER_OS == __COMPILER_LINUX
		return true;
	#else
		return false;
	#endif
}

#pragma deprecated Use `Script_IsWindowsCompiler`.
stock bool:Server_IsWindowsCompiler()
{
	#if __COMPILER_OS == __COMPILER_WINDOWS
		return true;
	#else
		return false;
	#endif
}

stock bool:Script_IsWindowsCompiler()
{
	#if __COMPILER_OS == __COMPILER_WINDOWS
		return true;
	#else
		return false;
	#endif
}

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

#if _YSI_SAFE_STARTUP
	#define Script_IsGameMode() (YSI_GAMEMODE)
#elseif defined FILTERSCRIPT
	#define Script_IsGameMode() (FALSE)
#else
	#define Script_IsGameMode() (TRUE)
#endif

stock bool:Server_IsOpenMP()
{
#if _YSI_SAFE_STARTUP
	return YSI_OPEN_MP;
#else
	return false;
#endif
}

static stock const
	YSI_gscHeader[] = " ========================================== ",
	YSI_gscSpacer[] = " |                                        | ",
	YSI_gscInitMsgA[] = "    Dumping \"pre-init.asm\", this",
	YSI_gscInitMsgB[] = "    Dumping \"post-init.asm\", this",
	YSI_gscInitMsgC[] = "   may take a little bit of time.",
	YSI_gscInitMsgD[] = "            Please wait...",
	YSI_gscDone[] =     "                Done!",
	YSI_gscFailed[] =   "               Failed!",
	YSI_gscPreInitFile[] = "pre-init",
	YSI_gscPostInitFile[] = "post-init";

static stock
	YSI_gsStartTime,
	bool:YSI_gsObnoxiousHeader = true,
	bool:YSI_gsFirstHeader = true,
	bool:YSI_gsNewPart = true,
	YSI_gsPurgeTimer = 0;

native YSI_VAPrintF(const fmt[], addr) = printf;
forward bool:fautocleanup(const name[], maxAge);

static stock ScriptInit_Dump(const filename[], const message[])
{
		new file[48];
		format(file, sizeof (file), "%s%s.%d.asm", GetYSIScriptfilesDir(E_YSI_DIR_DEBUG), filename, YSI_gsStartTime);
	#if _YSI_SAFE_STARTUP
		Server_PrintIntroPart(message, YSI_gscInitMsgC, YSI_SPACE, YSI_gscInitMsgD),
		Server_DisableLongCall();
	#endif
		if (DisasmWrite(file))
		{
			// 1 week.
			fautocleanup(file, 60 * 60 * 24 * 7);
		}
	#if _YSI_SAFE_STARTUP
		Server_EnableLongCall(),
		Server_PrintIntroPart(YSI_SPACE, YSI_gscDone),
		Server_FinishIntroPart();
	#endif
}

static stock Server_PrintYSIHeader()
{
	YSI_Print("         ==============================================================");
	YSI_Print("         |                                                            |");
	YSI_Print("         |                                                            |");
	YSI_Print("         |    YYYYYYY       YYYYYYY    SSSSSSSSSSSSSSS  IIIIIIIIII    |");
	YSI_Print("         |    Y:::::Y       Y:::::Y  SS:::::::::::::::S I::::::::I    |");
	YSI_Print("         |    Y:::::Y       Y:::::Y S:::::SSSSSS::::::S I::::::::I    |");
	YSI_Print("         |    Y::::::Y     Y::::::Y S:::::S     SSSSSSS II::::::II    |");
	YSI_Print("         |    YYY:::::Y   Y:::::YYY S:::::S               I::::I      |");
	YSI_Print("         |       Y:::::Y Y:::::Y    S:::::S               I::::I      |");
	YSI_Print("         |        Y:::::Y:::::Y      S::::SSSS            I::::I      |");
	YSI_Print("         |         Y:::::::::Y        SS::::::SSSSS       I::::I      |");
	YSI_Print("         |          Y:::::::Y           SSS::::::::SS     I::::I      |");
	YSI_Print("         |           Y:::::Y               SSSSSS::::S    I::::I      |");
	YSI_Print("         |           Y:::::Y                    S:::::S   I::::I      |");
	YSI_Print("         |           Y:::::Y                    S:::::S   I::::I      |");
	YSI_Print("         |           Y:::::Y        SSSSSSS     S:::::S II::::::II    |");
	YSI_Print("         |        YYYY:::::YYYY     S::::::SSSSSS:::::S I::::::::I    |");
	YSI_Print("         |        Y:::::::::::Y     S:::::::::::::::SS  I::::::::I    |");
	YSI_Print("         |        YYYYYYYYYYYYY      SSSSSSSSSSSSSSS    IIIIIIIIII    |");
	YSI_Print("         |                                                            |");
	YSI_Print("         |                                                            |");
	YSI_Print("         |                      (c) 2021 MPL v1.1                     |");
	YSI_Print("         |            Alex \"Y_Less\" Cole and contributors.            |");
	YSI_Print("         |                                                            |");
	YSI_Print("         |                                                            |");
	YSI_Print("         ==============================================================");
}

stock Server_PrintIntroMessage(...)
{
	#if _YSI_SAFE_STARTUP
		if (YSI_gsObnoxiousHeader)
		{
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_SPACE),
			Server_PrintYSIHeader(),
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_gscHeader),
			YSI_gsObnoxiousHeader = false,
			YSI_gsFirstHeader = false;
		}
		else
	#endif
		if (YSI_gsFirstHeader)
		{
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_gscHeader),
			YSI_gsFirstHeader = false;
		}
		// Header.
		YSI_Print(YSI_gscSpacer);
		// Body.
		for (new i = 3 * cellbytes, j = (numargs() << __COMPILER_CELL_SHIFT) + (3 * cellbytes), a = 0; i != j; i += cellbytes)
		{
			#emit LCTRL          5
			#emit LOAD.S.alt     i
			#emit ADD
			#emit LOAD.I
			#emit STOR.S.pri     a
			YSI_VAPrintF(" | %38s | ", a);
		}
		// Footer.
		YSI_Print(YSI_gscSpacer);
		YSI_Print(YSI_gscHeader);
}

stock Server_PrintIntroPart(...)
{
	#if _YSI_SAFE_STARTUP
		if (YSI_gsObnoxiousHeader)
		{
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_SPACE),
			Server_PrintYSIHeader(),
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_gscHeader),
			YSI_gsObnoxiousHeader = false,
			YSI_gsFirstHeader = false;
		}
		else
	#endif
		if (YSI_gsFirstHeader)
		{
			YSI_Print(YSI_SPACE),
			YSI_Print(YSI_gscHeader),
			YSI_gsFirstHeader = false;
		}
		// Header.
		if (YSI_gsNewPart)
		{
			YSI_gsNewPart = false;
			YSI_Print(YSI_gscSpacer);
		}
		// Body.
		for (new i = 3 * cellbytes, j = 3 * cellbytes + (numargs() << __COMPILER_CELL_SHIFT), a = 0; i != j; i += cellbytes)
		{
			#emit LCTRL          5
			#emit LOAD.S.alt     i
			#emit ADD
			#emit LOAD.I
			#emit STOR.S.pri     a
			YSI_VAPrintF(" | %38s | ", a);
		}
}

stock Server_FinishIntroPart()
{
	// Footer.
	YSI_Print(YSI_gscSpacer);
	YSI_Print(YSI_gscHeader);
	YSI_gsNewPart = true;
}

stock Server_FinishIntroMessage()
{
	YSI_Print(YSI_SPACE),
	YSI_gsFirstHeader = true;
}

stock Server_SetLongCallTime(usTime)
{
	// Setting this to `0` doesn't change the internal time, merely disables the check.
	#emit LOAD.S.pri    usTime
	#emit SCTRL         0xFE
}

stock Server_DisableLongCall()
{
	#emit CONST.pri     0
	#emit SCTRL         0xFE
}

stock Server_EnableLongCall()
{
	#emit CONST.pri     2
	#emit SCTRL         0xFF
}

stock Server_ResetLongCallTime()
{
	#emit CONST.pri     4
	#emit SCTRL         0xFF
}

stock Server_RestartLongCall()
{
	#emit CONST.pri     8
	#emit SCTRL         0xFF
}

stock bool:Server_IsLongCallEnabled()
{
	#emit ZERO.pri
	#emit LCTRL         0xFF
	#emit CONST.alt     1
	#emit AND
	#emit RETN
	return false;
}

stock Server_GetLongCallTime()
{
	#emit ZERO.pri
	#emit LCTRL         0xFE
	#emit SHR.C.pri     1
	#emit RETN
	return 0;
}

stock Server_DisableDetectAddr0() {
	#emit CONST.pri     0
	#emit SCTRL         0xFD
}

stock Server_EnableDetectAddr0() {
	#emit CONST.pri     1
	#emit SCTRL         0xFD
}

stock bool:Server_IsDetectAddr0Enabled() {
	// Is the check enabled?  0 if off or doesn't exist.
	#emit CONST.pri     0
	#emit LCTRL 0xFD
	#emit CONST.alt     1
	#emit AND
	#emit RETN
	return false;
}

stock bool:Server_HasDetectAddr0() {
	// Is the check possible?
	#emit CONST.pri     0xFFFFFFFF // -1
	#emit LCTRL 0xFD               // 0, 1, or -2
	#emit CONST.alt     0
	#emit SGEQ                     // >= 0
	#emit RETN
	return false;
}

stock Server_GetStartTime()
{
	return YSI_gsStartTime;
}

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

// `GetCrashDetectDefaultLongCallTime` is too long.
stock Server_GetLongCallDefault()
{
	// Store the current value.
	#emit ZERO.pri
	#emit LCTRL         0xFE
	#emit MOVE.alt
	// Reset to and read the default.
	#emit CONST.pri     4
	#emit SCTRL         0xFF
	#emit ZERO.pri
	#emit LCTRL         0xFE
	// Put the current value back.
	#emit XCHG
	#emit SCTRL         0xFE
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

#if !defined _ALS_OnCachedInit
	forward OnCachedInit();
#endif

static bool:ScriptInit_CallOnCodeInit(bool:jit, bool:fs)
{
	#if !_YSI_SAFE_STARTUP
		printf("Unsafe YSI signed by: %s", YSI_gcUnsafeStartupContract);
	#endif
	if (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD)
	{
		// Loaded from a file.
		#if _YSI_SAFE_STARTUP
			Server_PrintIntroMessage("   File loaded from YSI code cache.");
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
						P:W("Could not auto-load YSI cache - script type (GM/FS) cannot be determined with JIT.");
						strcat(name, ".amx");
					}
					else if (fs)
					{
						P:W("Could not auto-load YSI cache - current filterscript cannot be unloaded.");
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
		#else
			#pragma unused jit
		#endif
		#if defined ScriptInit_OnCodeInit
			ScriptInit_OnCodeInit();
		#endif
		#if _YSI_SAFE_STARTUP
			Server_PrintIntroPart(YSI_SPACE, YSI_gscDone);
			Server_FinishIntroPart();
		#endif
		#if !defined YSI_NO_MODE_CACHE
			E_SCRIPTINIT_STATE
				tmp = YSI_g_sScriptInitState & (E_SCRIPTINIT_STATE_JITING | E_SCRIPTINIT_STATE_JITED);
			// Set the variable to something unique for next load.  This will be
			// written out, thus loaded in next time.
			YSI_g_sScriptInitState = E_SCRIPTINIT_STATE_RELOAD;
			#if _YSI_SAFE_STARTUP
				Server_PrintIntroPart(
					" Dumping \"YSI_CACHE.amx\", this may",
					"     take a little bit of time.",
					YSI_SPACE,
					YSI_gscInitMsgD
				);
			#endif
			if (DumpAMX_Write(name))
			{
				#if _YSI_SAFE_STARTUP
					Server_PrintIntroPart(YSI_SPACE, YSI_gscDone);
					Server_FinishIntroPart();
				#endif
					// Clear this flag after dumping.  This is so we can tell
					// when a mode is cached.
					YSI_g_sScriptInitState = tmp | E_SCRIPTINIT_STATE_DUMPED;
				#if _YSI_SAFE_STARTUP
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
			}
			else
			{
				#if _YSI_SAFE_STARTUP
					Server_PrintIntroPart(YSI_SPACE, YSI_gscFailed);
					Server_FinishIntroPart();
				#endif
					YSI_g_sScriptInitState = tmp;
					P:E("YSI code cache write failed");
			}
		#endif
			Server_EnableLongCall();
	}
	return true;
}

#if !defined _ALS_OnJITCompile
	forward OnJITCompile();
#endif

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
	YSI_gsStartTime = gettime();
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
		Debug_Print0("\7*** YSI Warning: JIT disabled");
	}
	DEBUG_MAYBE_DUMP(YSI_gscPostInitFile, YSI_gscInitMsgB);
	#if _YSI_SAFE_STARTUP
		Server_FinishIntroMessage();
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
#define @Iy_%0\32; @Iy_
#define @_Iy%0\32; @_Iy

#define y_@I%0\32; y_@I

#define __script_init_u@_1
// Can't `#undef` this because it declares a `forward` with the same name.
#define u@$ 1]);

// Detect tags.
#define _@Iy:%8$%3:%0(%1)<_> %8$%0(%1)<%3>

// Detect arrays, on `final` only.
#define _@yI:_I@y:%8$%0[%4]%9(%1)<%3> %8$@yI_%0();@yI_%0(){new %3:y__[sizeof(%0)];y_@I%0(y__);_YSI_ConstCpy(_:%0,_:y__,0,sizeof y__*4,sizeof y__);}static y_@I%0(%3:y__[sizeof(%0)])y__=

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
//		YSI_OPEN_MP = true;
//		state _script_init_fix_state : false;
//		// Dump the final assembly of this script so we can inspect it.
//		if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
//		{
//			YSI_gsStartTime = gettime();
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
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
			state _ALS : _ALS_go;
		#if _YSI_SAFE_STARTUP
			YSI_FILTERSCRIPT = true;
			if (!YSI_OPEN_MP)
		#endif
			{
				state _script_init_fix_state : true;
				// Dump the final assembly of this script so we can inspect it.
				if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
				{
					YSI_gsStartTime = gettime();
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
				#if defined ScriptInit_OnYSIInit
					ScriptInit_OnYSIInit();
				#endif
				ScriptInit_PreInitFuncs_();
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
				CallLocalFunction("OnScriptInit@C", YSI_EMPTY);
			}
			return 1;
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  Check which temporary files need deleting.
 * </returns>
 *//*------------------------------------------------------------------------**/

forward ScriptInit_PurgeTemporaries();

forward File:ftemporary_(name[], const ext[] = "tmp", const path[] = "", len = sizeof (name));

public ScriptInit_PurgeTemporaries()
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
	YSI_gsPurgeTimer = YSI_SetTimer("ScriptInit_PurgeTemporaries", 1000 * 60 * 60, false);
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="_script_init_fix_state : false"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	public OnGameModeInit()
	{
			state _ALS : _ALS_go;
			// Kill an existing purge if one exists in this script.
		#if _YSI_SAFE_STARTUP
			if (!YSI_FILTERSCRIPT && !YSI_OPEN_MP && !(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		#else
			if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		#endif
			{
				YSI_gsStartTime = gettime();
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
				if (!YSI_OPEN_MP)
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
					#if defined ScriptInit_OnYSIInit
						ScriptInit_OnYSIInit();
					#endif
					ScriptInit_PreInitFuncs_();
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
			if (!YSI_OPEN_MP)
		#endif
			{
				CallLocalFunction("OnScriptInit@E", YSI_EMPTY);
			}
			return 1;
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

#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	public OnFilterScriptExit()
	{
		ScriptInit_OnFilterScriptExit();
#if _YSI_SAFE_STARTUP
		if (YSI_FILTERSCRIPT && !YSI_OPEN_MP)
#endif
		{
			ScriptInit_PreExitFuncs_();
			ScriptInit_OnScriptExit();
			ScriptInit_PostExitFuncs_();
			ScriptInit_OnYSIExit();
		}
		return 1;
	}
#endif

#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	public OnGameModeExit()
	{
		ScriptInit_OnGameModeExit();
#if _YSI_SAFE_STARTUP
		if (YSI_GAMEMODE && !YSI_OPEN_MP)
#endif
		{
			ScriptInit_PreExitFuncs_();
			ScriptInit_OnScriptExit();
			ScriptInit_PostExitFuncs_();
			ScriptInit_OnYSIExit();
		}
		return 1;
	}
#endif

#if _YSI_SAFE_STARTUP
	forward OnScriptExit(id);

	public OnScriptExit(id)
	{
		if (YSI_OPEN_MP)
		{
			ScriptInit_PreExitFuncs_();
			ScriptInit_OnScriptExit();
			ScriptInit_PostExitFuncs_();
			ScriptInit_OnYSIExit();
		}
		return 1;
	}
#endif

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

// I'm not quite sure what causes it, but there seems to be a bug in the
// compiler somewhere which messes up the "ysi_debug" automaton and the
// "YSI_FILTERSCRIPT" variable :(.
//
// I eventually figured this one out:
//
//     https://github.com/pawn-lang/compiler/issues/666
//
// So this fix is probably no longer needed.
public _ScriptInit_FixState() <_script_init_fix_state : true>
{
}

public _ScriptInit_FixState() <_script_init_fix_state : false>
{
}

