/**--------------------------------------------------------------------------**\
					=======================================
					 y_scriptinit - Two useful callbacks.
					=======================================
Description:
	This file provides "OnScriptInit" and "OnScriptExit" which are called at the
	start and end of the current script, regardless of what the type of the
	script is (note: doesn't support NPC modes).  It also provides
	"YSI_FILTERSCRIPT" as a (partial) replacement for "FILTERSCRIPT" which
	detects what the mode is at runtime for a more reliable system (but it is a
	run-time variable, not a compile-time constant).
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
	
	The Original Code is the YSI scriptinit include.
	
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
	1.0
Changelog:
	30/04/11:
		First version
</remarks>
\**--------------------------------------------------------------------------**/

#include <a_samp>

#include "internal\y_natives"

forward _ScriptInit_FixState();

#if defined FILTERSCRIPT
	#if !defined YSI_FILTERSCRIPT
		stock
			bool:YSI_FILTERSCRIPT = true;
	#endif
	
	public OnFilterScriptInit()
	{
		state _script_init_fix_state : true;
		//CallLocalFunction("__YSI_SpecialInit", "");
		//state _ALS_:hooked;
		#if defined ScriptInit_OnScriptInit
			ScriptInit_OnScriptInit();
		#endif
		#if defined YSI_LOCK_MODE
			if (strlen(YSI_gLockData[5]) !=
				floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil) + 1 +
				floatround(floatlog(_LOCK_LEN_1 + 1), floatround_ceil) + 1 +
				floatround(floatlog(_LOCK_LEN_2 + 1), floatround_ceil) + 1 +
				floatround(floatlog(_LOCK_LEN_3 + 1), floatround_ceil))
			{
				y_lock 6;
			}
		#endif
		//CallRemoteFunction("ScriptInit_OnAnyScriptInit", "");
		//ScriptInit_OnFilterScriptInit();
		#if defined ScriptInit_OnFilterScriptInit
			return ScriptInit_OnFilterScriptInit();
		#else
			return ALS_R_FilterScriptInit;
		#endif
		//ScriptInit_OnScriptInitLate();
		//CallLocalFunction("Text_Special_OnScriptInit", "");
	}
	
	#if defined ScriptInit_OnFilterScriptInit
		forward ScriptInit_OnFilterScriptInit();
	#endif
	
	//public ScriptInit_OnFilterScriptInit() <_ALS_:unhooked> return 1;
	//public ScriptInit_OnFilterScriptInit() <> return 1;
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit ScriptInit_OnFilterScriptInit
#else
	// People can't be trusted to use "FILTERSCRIPT"...
	#if !defined YSI_FILTERSCRIPT
		new
			bool:YSI_FILTERSCRIPT = false;
	#endif
	
	public OnFilterScriptInit()
	{
		state _script_init_fix_state : true;
		//printf("OFSI");
		YSI_FILTERSCRIPT = true;
		//CallLocalFunction("__YSI_SpecialInit", "");
		//state _ALS_:hooked;
		#if defined ScriptInit_OnScriptInit
			ScriptInit_OnScriptInit();
		#endif
		#if defined YSI_LOCK_MODE
			new
				str[16];
			format(str, sizeof (str), "%c%c%c%c%c%c%c%c%c%c%c", '%', 'd', '.', '%', 'd', '.', '%', 'd', '.', '%', 'd');
			format(str, sizeof (str), str, _LOCK_IP_0, _LOCK_IP_1, _LOCK_IP_2, _LOCK_IP_3);
			if (strlen(YSI_gLockData[5]) != strlen(str))
			{
				y_lock 7;
			}
		#endif
		//CallRemoteFunction("ScriptInit_OnAnyScriptInit", "");
		#if defined ScriptInit_OnFilterScriptInit
			return ScriptInit_OnFilterScriptInit();
		#else
			return 1;
		#endif
		//ScriptInit_OnScriptInitLate();
	}
	
	public OnGameModeInit()
	{
		if (YSI_FILTERSCRIPT)
		{
			state _script_init_fix_state : true;
			#if defined ScriptInit_OnGameModeInit
				return ScriptInit_OnGameModeInit();
			#else
				return 1;
			#endif
		}
		else
		{
			state _script_init_fix_state : false;
			//CallLocalFunction("__YSI_SpecialInit", "");
			//state _ALS_:hooked;
			//printf("OnScriptInit 1");
			#if defined ScriptInit_OnScriptInit
				ScriptInit_OnScriptInit();
			#endif
			//printf("OnScriptInit 2");
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
			//CallRemoteFunction("ScriptInit_OnAnyScriptInit", "");
			//printf("OnScriptInit 3");
			//ScriptInit_OnGameModeInit();
			//printf("OnScriptInit 4");
			//return 222;
			#if defined ScriptInit_OnGameModeInit
				return ScriptInit_OnGameModeInit();
			#else
				return 1;
			#endif
			//ScriptInit_OnScriptLate();
			//CallLocalFunction("Text_SpecialInit", "");
		}
	}
	
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit ScriptInit_OnGameModeInit
	#if defined ScriptInit_OnGameModeInit
		forward ScriptInit_OnGameModeInit();
	#endif
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit ScriptInit_OnFilterScriptInit
	#if defined ScriptInit_OnFilterScriptInit
		forward ScriptInit_OnFilterScriptInit();
	#endif
#endif

#if defined FILTERSCRIPT
	public OnFilterScriptExit()
	{
		#if defined ScriptInit_OnScriptExit
			ScriptInit_OnScriptExit();
		#endif
		//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
		#if defined ScriptInit_OnFilterScriptExit
			new
				ret = ScriptInit_OnFilterScriptExit();
		#endif
		//ScriptInit_OnScriptExitLate();
		//CallLocalFunction("__YSI_SpecialExit", "");
		#if defined __YSI_SpecialExit
			__YSI_SpecialExit();
		#endif
		#if defined ScriptInit_OnFilterScriptExit
			return ret;
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit ScriptInit_OnFilterScriptExit
	
	#if defined ScriptInit_OnFilterScriptExit
		forward ScriptInit_OnFilterScriptExit();
	#endif
#else
	public OnFilterScriptExit()
	{
		if (YSI_FILTERSCRIPT)
		{
			#if defined ScriptInit_OnScriptExit
				ScriptInit_OnScriptExit();
			#endif
			//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
			#if defined ScriptInit_OnFilterScriptExit
				new
					ret = ScriptInit_OnFilterScriptExit();
			#endif
			//ScriptInit_OnScriptExitLate();
			//CallLocalFunction("__YSI_SpecialExit", "");
			#if defined __YSI_SpecialExit
				__YSI_SpecialExit();
			#endif
			#if defined ScriptInit_OnFilterScriptExit
				return ret;
			#else
				return 1;
			#endif
		}
		return 1;
	}
	
	public OnGameModeExit()
	{
		//printf("ScriptInit_OnGameModeExit");
		if (YSI_FILTERSCRIPT)
		{
			#if defined ScriptInit_OnGameModeExit
				return ScriptInit_OnGameModeExit();
			#else
				return 1;
			#endif
		}
		else
		{
			printf("NF 0");
			#if defined ScriptInit_OnScriptExit
				ScriptInit_OnScriptExit();
			#endif
			printf("NF 1");
			//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
			#if defined ScriptInit_OnGameModeExit
				new
					ret = ScriptInit_OnGameModeExit();
			#endif
			printf("NF 2");
			//ScriptInit_OnScriptExitLate();
			//CallLocalFunction("__YSI_SpecialExit", "");
			#if defined __YSI_SpecialExit
				__YSI_SpecialExit();
			#endif
			printf("NF 3");
			#if defined ScriptInit_OnGameModeExit
				printf("NF 4");
				return ret;
			#else
				return 1;
			#endif
		}
	}
	
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit ScriptInit_OnGameModeExit
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit ScriptInit_OnFilterScriptExit
	
	#if defined ScriptInit_OnFilterScriptExit
		forward ScriptInit_OnFilterScriptExit();
	#endif
	#if defined ScriptInit_OnGameModeExit
		forward ScriptInit_OnGameModeExit();
	#endif
#endif

#define OnScriptInit ScriptInit_OnScriptInit
#define _ALS_OnScriptInit
#if defined ScriptInit_OnScriptInit
	forward ScriptInit_OnScriptInit();
#endif

#define OnScriptExit ScriptInit_OnScriptExit
#define _ALS_OnScriptExit
#if defined ScriptInit_OnScriptExit
	forward ScriptInit_OnScriptExit();
#endif

#define _YSI_SpecialExit __YSI_SpecialExit
#define _ALS__YSI_SpecialExit
#if defined __YSI_SpecialExit
	forward __YSI_SpecialExit();
#endif

// I'm not quite sure what causes it, but there seems to be a bug in the
// compiler somewhere which messes up the "ysi_debug" automaton and the
// "YSI_FILTERSCRIPT" variable :(.
public _ScriptInit_FixState() <_script_init_fix_state : true>
{
}

public _ScriptInit_FixState() <_script_init_fix_state : false>
{
}
