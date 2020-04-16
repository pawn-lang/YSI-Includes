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
		#define DEBUG_MAYBE_DUMP(%0) DisasmWrite(%0)
	#endif
#endif
#if !defined DEBUG_MAYBE_DUMP
	#define DEBUG_MAYBE_DUMP(%0);
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
	return !!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING);
}

stock bool:Server_JITComplete()
{
	return !!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITED);
}

stock bool:Server_CacheLoaded()
{
	return !!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD);
}

stock bool:Server_CacheSaved()
{
	return !!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_DUMPED);
}

stock bool:Server_IsFilterscript()
{
	return YSI_FILTERSCRIPT;
}

stock bool:Server_IsGameMode()
{
	return !YSI_FILTERSCRIPT;
}

stock bool:Server_CrashDetectExists()
{
	// 0xFF is roughly flags, but some are mutually exclusive:
	//
	//   1 - Present (read only, write always 0).
	//   2 - long_call_time checks enabled (write ignored when `server.cfg` has `long_call_time 0`).
	//   4 - long_call_time reset to default time (write only, read always 0).
	//   8 - long_call_time restart check from now (write only, read always 0).
	//
	#emit ZERO.pri
	#emit LCTRL         0xFF
	#emit NOT
	#emit NOT
	#emit RETN
	return false;
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
	#emit SHR.C.pri     1
	#emit RETN
	return false;
}

stock Server_GetLongCallTime()
{
	#emit ZERO.pri
	#emit LCTRL         0xFE
	#emit RETN
	return 0;
}

// `GetCrashDetectDefaultLongCallTime` is too long.
stock Server_GetLongCallDefault()
{
	// store the current value
	#emit ZERO.pri
	#emit LCTRL         0xFE
	#emit MOVE.alt
	// reset to and read the default
	#emit CONST.pri     4
	#emit SCTRL         0xFF
	#emit ZERO.pri
	#emit LCTRL         0xFE
	// put the current value back
	#emit XCHG
	#emit SCTRL         0xFE
	#emit MOVE.pri
	#emit RETN
	return 0;
}

#if !defined YSI_NO_MODE_CACHE
	#if !defined DumpAMX_Included_ && !defined YSI_YES_MODE_CACHE && __COMPILER_2ND_PASS
		#define YSI_NO_MODE_CACHE
		#define YSI_NO_CACHE_MESSAGE
		#define YSI_NO_OPTIMISATION_MESSAGE
	#endif
#endif

forward bool:DumpAMX_Write(const filename[]);

forward OnCachedInit();

static ScriptInit_CallOnCodeInit(bool:jit)
{
	Server_DisableLongCall();
	if (YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_RELOAD)
	{
		// Loaded from a file.
		#if !defined YSI_NO_CACHE_MESSAGE
			YSI_Print(" ");
			YSI_Print(" ========================================== ");
			YSI_Print(" |                                        | ");
			YSI_Print(" |  File loaded from YSI code cache.      | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" | You can disable this message with:     | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" |   #define YSI_NO_CACHE_MESSAGE         | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" ========================================== ");
			YSI_Print(" ");
		#endif
		R@("OnCachedInit", "");
	}
	else
	{
		#if defined YSI_NO_OPTIMISATION_MESSAGE
			#pragma unused jit
		#else
			YSI_Print(" ");
			YSI_Print(" ========================================== ");
			YSI_Print(" |                                        | ");
			YSI_Print(" |    Generating code, this may take a    | ");
			YSI_Print(" |           little bit of time.          | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" |             Please wait...             | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" | You can disable this message with:     | ");
			YSI_Print(" |                                        | ");
			YSI_Print(" |   #define YSI_NO_OPTIMISATION_MESSAGE  | ");
			YSI_Print(" |                                        | ");
			if (!jit)
			{
				YSI_Print(" ========================================== ");
				YSI_Print(" |                                        | ");
				YSI_Print(" | Note that this code generation works   | ");
				YSI_Print(" | best with the JIT plugin, which you    | ");
				YSI_Print(" | are not currently using.  Get it here: | ");
				YSI_Print(" |                                        | ");
				YSI_Print(" |        https://git.io/jit-plugin       | ");
				YSI_Print(" |                                        | ");
			}
			YSI_Print(" ========================================== ");
			YSI_Print(" ");
		#endif
		#if defined ScriptInit_OnCodeInit
			ScriptInit_OnCodeInit();
		#endif
		#if !defined YSI_NO_MODE_CACHE
			new
				E_SCRIPTINIT_STATE:tmp = YSI_g_sScriptInitState & (E_SCRIPTINIT_STATE_JITING | E_SCRIPTINIT_STATE_JITED);
			// Set the variable to something unique for next load.  This will be written out, thus
			// loaded in next time.
			YSI_g_sScriptInitState = E_SCRIPTINIT_STATE_RELOAD;
			if (DumpAMX_Write("YSI_CACHE.amx"))
			{
				// Clear this flag after dumping.  This is so we can tell when a mode is cached.
				YSI_g_sScriptInitState = tmp | E_SCRIPTINIT_STATE_DUMPED;
				#if !defined YSI_NO_CACHE_MESSAGE
					YSI_Print(" ");
					YSI_Print(" ========================================== ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |   File dumped to YSI code cache:       | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |      scriptfiles/YSI_CACHE.amx         | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" | Load this file instead to skip this    | ");
					YSI_Print(" | code optimisation step in the future.  | ");
					YSI_Print(" | Note that if you have multiple scripts | ");
					YSI_Print(" | loading at once (i.e. gamemodes,       | ");
					YSI_Print(" | filterscripts, and modules) you may    | ");
					YSI_Print(" | need to load and cache them            | ");
					YSI_Print(" | individually so that they don't        | ");
					YSI_Print(" | clobber each other.  If you don't, in  | ");
					YSI_Print(" | \"server.cfg\", the following works:     | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |   gamemode0 ../scriptfiles/YSI_CACHE 1 | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" | You can disable this message with:     | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |   #define YSI_NO_CACHE_MESSAGE         | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" | You can disable this caching with:     | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |   #define YSI_NO_MODE_CACHE            | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" | You can explicitly enable it with:     | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" |   #define YSI_YES_MODE_CACHE           | ");
					YSI_Print(" |                                        | ");
					YSI_Print(" ========================================== ");
					YSI_Print(" ");
				#endif
			}
			else
			{
				YSI_g_sScriptInitState = tmp;
				P:E("YSI code cache write failed");
			}
		#endif
	}
	Server_EnableLongCall();
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
	DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
	YSI_g_sScriptInitState |= E_SCRIPTINIT_STATE_JITING;
	ScriptInit_CallOnCodeInit(true);
	new ret = ScriptInit_OnJITCompile();
	if (ret)
	{
		YSI_g_sScriptInitState |= E_SCRIPTINIT_STATE_JITED;
	}
	else
	{
		Debug_Print0("\7*** YSI Warning: JIT disabled");
	}
	DEBUG_MAYBE_DUMP("YSI_POST_INIT.asm");
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

#define u@$ 0]);

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

#if defined Script_GetID
	forward OnScriptInit(id);
	public OnScriptInit(id)
	{
		if (id != Script_GetID())
		{
			return 0;
		}
		#if !defined FILTERSCRIPT
			if (funcidx("OnFilterScriptInit") != -1)
		#endif
			{
				// This is a legacy filterscript.
				printf("*** This script has been detected as a legacy filterscript.");
				R@("OnFilterScriptInit", "");
			}
		#if !defined FILTERSCRIPT
			else
			{
				printf("*** This script has been detected as a legacy gamemode.");
				W@("OnGameModeInit", "");
			}
		#endif
		return 0;
	}
#elseif defined _ALS_OnScriptInit || (__COMPILER_1ST_PASS && defined OnScriptInit)
	#error OnScriptInit defined
#endif

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="_script_init_fix_state : true"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

public OnFilterScriptInit()
{
	YSI_FILTERSCRIPT = true;
	state _script_init_fix_state : true;
	state _ALS : _ALS_go;
	// Dump the final assembly of this script so we can inspect it.
	if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
	{
		DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
		ScriptInit_CallOnCodeInit(false);
	}
	ScriptInit_PreInitFuncs_();
	#if defined ScriptInit_OnScriptInit
		ScriptInit_OnScriptInit();
	#endif
	ScriptInit_PostInitFuncs_();
	if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
	{
		// Dump the final assembly of this script so we can inspect it.
		DEBUG_MAYBE_DUMP("YSI_POST_INIT.asm");
	}
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
	ScriptInit_OnFilterScriptInit();
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="_script_init_fix_state : false"/>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

public OnGameModeInit()
{
	state _ALS : _ALS_go;
	if (!YSI_FILTERSCRIPT)
	{
		state _script_init_fix_state : false;
		// Dump the final assembly of this script so we can inspect it.
		if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		{
			DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
			ScriptInit_CallOnCodeInit(false);
		}
		ScriptInit_PreInitFuncs_();
		#if defined ScriptInit_OnScriptInit
			ScriptInit_OnScriptInit();
		#endif
		ScriptInit_PostInitFuncs_();
		if (!(YSI_g_sScriptInitState & E_SCRIPTINIT_STATE_JITING))
		{
			// Dump the final assembly of this script so we can inspect it.
			DEBUG_MAYBE_DUMP("YSI_POST_INIT.asm");
		}
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
	ScriptInit_OnGameModeInit();
	return 1;
}

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

public OnFilterScriptExit()
{
	ScriptInit_OnFilterScriptExit();
	if (YSI_FILTERSCRIPT)
	{
		ScriptInit_PreExitFuncs_();
		ScriptInit_OnScriptExit();
		ScriptInit_PostExitFuncs_();
	}
	return 1;
}

public OnGameModeExit()
{
	ScriptInit_OnGameModeExit();
	if (!YSI_FILTERSCRIPT)
	{
		ScriptInit_PreExitFuncs_();
		ScriptInit_OnScriptExit();
		ScriptInit_PostExitFuncs_();
	}
	return 1;
}

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

//#undef OnCodeInit
#define OnCodeInit ScriptInit_OnCodeInit
#if defined ScriptInit_OnCodeInit
	forward ScriptInit_OnCodeInit();
#endif

CHAIN_FORWARD:ScriptInit_OnScriptInit() = 1;

#define _ALS_OnScriptInit
#define OnScriptInit(%0) CHAIN_PUBLIC:ScriptInit_OnScriptInit(%0)

CHAIN_FORWARD:ScriptInit_OnJITCompile() = 1;
#if defined _ALS_OnJITCompile
	#undef OnJITCompile
#else
	#define _ALS_OnJITCompile
#endif
#define OnJITCompile(%0) CHAIN_PUBLIC:ScriptInit_OnJITCompile(%0)

CHAIN_FORWARD:ScriptInit_OnFilterScriptInit() = 1;
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit(%0) CHAIN_PUBLIC:ScriptInit_OnFilterScriptInit(%0)

CHAIN_FORWARD:ScriptInit_OnGameModeInit() = 1;
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit(%0) CHAIN_PUBLIC:ScriptInit_OnGameModeInit(%0)

CHAIN_FORWARD:ScriptInit_OnFilterScriptExit() = 1;
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit(%0) CHAIN_PUBLIC:ScriptInit_OnFilterScriptExit(%0)

CHAIN_FORWARD:ScriptInit_OnGameModeExit() = 1;
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit(%0) CHAIN_PUBLIC:ScriptInit_OnGameModeExit(%0)

CHAIN_FORWARD:ScriptInit_OnScriptExit() = 1;
#if defined _ALS_OnScriptExit
	#undef OnScriptExit
#else
	#define _ALS_OnScriptExit
#endif
#define OnScriptExit(%0) CHAIN_PUBLIC:ScriptInit_OnScriptExit(%0)

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
public _ScriptInit_FixState() <_script_init_fix_state : true>
{
}

public _ScriptInit_FixState() <_script_init_fix_state : false>
{
}

