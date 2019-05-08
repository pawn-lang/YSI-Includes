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

static
	bool:YSI_g_sCrashdetect = false,
	bool:YSI_g_sCodeJITed = false,
	bool:YSI_g_sCodeJITing = false;

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
		#define DEBUG_MAYBE_DUMP(%0) DisasmDump(%0)
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
	return YSI_g_sCodeJITing;
}

stock bool:Server_JITComplete()
{
	return YSI_g_sCodeJITed;
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
	return YSI_g_sCrashdetect;
}

static ScriptInit_CallOnCodeInit(bool:jit)
{
	#if defined ScriptInit_OnCodeInit
		YSIPrint(" ");
		YSIPrint(" ======================================= ");
		YSIPrint(" |                                     | ");
		YSIPrint(" |    Optimising code, this may take   | ");
		YSIPrint(" |        a little bit of time.        | ");
		YSIPrint(" |                                     | ");
		YSIPrint(" |            Please wait...           | ");
		YSIPrint(" |                                     | ");
		if (!jit)
		{
			YSIPrint(" |=====================================| ");
			YSIPrint(" |                                     | ");
			YSIPrint(" | Note that these optimisations are   | ");
			YSIPrint(" | designed to improve performance     | ");
			YSIPrint(" | with the JIT plugin, which you are  | ");
			YSIPrint(" | not currently using.  Get it here:  | ");
			YSIPrint(" |                                     | ");
			YSIPrint(" |      https://git.io/jit-plugin      | ");
			YSIPrint(" |                                     | ");
		}
		YSIPrint(" ======================================= ");
		YSIPrint(" ");
		ScriptInit_OnCodeInit();
	#endif
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
	if (YSI_g_sCodeJITing)
		return 0;
	DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
	YSI_g_sCodeJITing = true;
	ScriptInit_CallOnCodeInit(true);
	new ret = ScriptInit_OnJITCompile();
	if (ret)
		YSI_g_sCodeJITed = true;
	else
		Debug_Print0("\7*** YSI Warning: JIT disabled");
	DEBUG_MAYBE_DUMP("YSI_POST_INIT.asm");
	return ret;
}

#if !defined _ALS_OnRuntimeError
	forward OnRuntimeError(code, &bool:suppress);
#endif

public OnRuntimeError(code, &bool:suppress)
{
	if (code == 0x00495359)
	{
		YSI_g_sCrashdetect = true;
		suppress = true;
		return 1;
	}
	return ScriptInit_OnRuntimeError(code, suppress);
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

#define INIT_STRIP_TAGS__:%3:%0(%1);INIT_THE_TAG__<%2>%9(%9) %2%0(%1);%2%0(%1)
#define INIT_STRIP_TAGS_2__:@yI_%3:%0(%1);INIT_STRIP_TAGS_2__:%9(%9){_YSI_ConstMod(%4,(%5));} @yI_%0(%1);@yI_%0(%1){_YSI_ConstMod(_:%4,_:(%3:I@=(%5)));}
#define INIT_THE_TAG__<%0> INIT_STRIP_TAGS__:%0

#define PREINIT__%0(%1) INIT_STRIP_TAGS__:@yI_%0(%1);INIT_THE_TAG__<@yI_>%0(%1)
#define POSTINIT__%0(%1) INIT_STRIP_TAGS__:@_yI%0(%1);INIT_THE_TAG__<@_yI>%0(%1)

#define PREEXIT__%0(%1) INIT_STRIP_TAGS__:@Iy_%0(%1);INIT_THE_TAG__<@Iy_>%0(%1)
#define POSTEXIT__%0(%1) INIT_STRIP_TAGS__:@_Iy%0(%1);INIT_THE_TAG__<@_Iy>%0(%1)

#define FINAL__%0=%1; stock const %0;INIT_STRIP_TAGS_2__:@yI_%0();INIT_STRIP_TAGS_2__:@yI_%0(){_YSI_ConstMod(%0,(%1));}

#if YSI_KEYWORD(final)
	#define final FINAL__
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
	if (!YSI_g_sCodeJITing)
	{
		DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
		ScriptInit_CallOnCodeInit(false);
	}
	ScriptInit_PreInitFuncs_();
	#if defined ScriptInit_OnScriptInit
		ScriptInit_OnScriptInit();
	#endif
	ScriptInit_PostInitFuncs_();
	if (!YSI_g_sCodeJITing)
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
	#emit HALT 0x00495359 // "YSI".
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
		if (!YSI_g_sCodeJITing)
		{
			DEBUG_MAYBE_DUMP("YSI_PRE_INIT.asm");
			ScriptInit_CallOnCodeInit(false);
		}
		ScriptInit_PreInitFuncs_();
		#if defined ScriptInit_OnScriptInit
			ScriptInit_OnScriptInit();
		#endif
		ScriptInit_PostInitFuncs_();
		if (!YSI_g_sCodeJITing)
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
	if (!YSI_FILTERSCRIPT)
	{
		#emit HALT 0x00495359 // "YSI".
	}
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
#if defined _ALS_OnCodeInit || defined OnCodeInit
	#error OnCodeInit defined
#endif
#define OnCodeInit ScriptInit_OnCodeInit
#if defined ScriptInit_OnCodeInit
	forward ScriptInit_OnCodeInit();
#endif

CHAIN_FORWARD:ScriptInit_OnScriptInit() = 1;
#if defined _ALS_OnScriptInit || defined OnScriptInit
	#error defined OnScriptInit
#endif
#define _ALS_OnScriptInit
#define OnScriptInit(%0) CHAIN_PUBLIC:ScriptInit_OnScriptInit(%0)

CHAIN_FORWARD:ScriptInit_OnRuntimeError(code, &bool:suppress) = 1;
#if defined _ALS_OnRuntimeError
	#undef OnRuntimeError
#else
	#define _ALS_OnRuntimeError
#endif
#define OnRuntimeError(%0) CHAIN_PUBLIC:ScriptInit_OnRuntimeError(%0)

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

