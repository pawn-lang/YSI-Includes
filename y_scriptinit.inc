/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include <a_samp>

#include "internal\y_natives"

#if !defined _ALS_
	forward public _ALS_();
	
	_ALS_()<_ALS_:unhooked>
	{
	}
	
	_ALS_()<_ALS_:hooked>
	{
	}
	
	_ALS_()<>
	{
	}
#endif

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
		state _ALS_:hooked;
		ScriptInit_OnScriptInit();
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
		return ScriptInit_OnFilterScriptInit();
		//ScriptInit_OnScriptInitLate();
		//CallLocalFunction("Text_Special_OnScriptInit", "");
	}
	
	forward ScriptInit_OnFilterScriptInit();public ScriptInit_OnFilterScriptInit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnFilterScriptInit()<>{return 1;}
	
	//public ScriptInit_OnFilterScriptInit() <_ALS_:unhooked> return 1;
	//public ScriptInit_OnFilterScriptInit() <> return 1;
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit(%0) ScriptInit_OnFilterScriptInit(%0) <_ALS_:hooked>
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
		state _ALS_:hooked;
		ScriptInit_OnScriptInit();
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
		return ScriptInit_OnFilterScriptInit();
		//ScriptInit_OnScriptInitLate();
	}
	
	public OnGameModeInit()
	{
		if (YSI_FILTERSCRIPT)
		{
			state _script_init_fix_state : true;
			return ScriptInit_OnGameModeInit();
		}
		else
		{
			state _script_init_fix_state : false;
			//CallLocalFunction("__YSI_SpecialInit", "");
			state _ALS_:hooked;
			printf("OnScriptInit 1");
			ScriptInit_OnScriptInit();
			printf("OnScriptInit 2");
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
			printf("OnScriptInit 3");
			ScriptInit_OnGameModeInit();
			printf("OnScriptInit 4");
			return 222;
//			return ScriptInit_OnGameModeInit();
			//ScriptInit_OnScriptLate();
			//CallLocalFunction("Text_SpecialInit", "");
		}
	}
	
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit(%0) ScriptInit_OnGameModeInit(%0) <_ALS_:hooked>
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit(%0) ScriptInit_OnFilterScriptInit(%0) <_ALS_:hooked>
	
	forward ScriptInit_OnFilterScriptInit();public ScriptInit_OnFilterScriptInit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnFilterScriptInit()<>{return 1;}
	forward ScriptInit_OnGameModeInit();public ScriptInit_OnGameModeInit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnGameModeInit()<>{return 1;}
#endif

#if defined FILTERSCRIPT
	public OnFilterScriptExit()
	{
		ScriptInit_OnScriptExit();
		//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
		new
			ret = ScriptInit_OnFilterScriptExit();
		//ScriptInit_OnScriptExitLate();
		//CallLocalFunction("__YSI_SpecialExit", "");
		__YSI_SpecialExit();
		return ret;
	}
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit(%0) ScriptInit_OnFilterScriptExit(%0) <_ALS_:hooked>
	
	forward ScriptInit_OnFilterScriptExit();public ScriptInit_OnFilterScriptExit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnFilterScriptExit()<>{return 1;}
#else
	public OnFilterScriptExit()
	{
		if (YSI_FILTERSCRIPT)
		{
			ScriptInit_OnScriptExit();
			//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
			new
				ret = ScriptInit_OnFilterScriptExit();
			//ScriptInit_OnScriptExitLate();
			//CallLocalFunction("__YSI_SpecialExit", "");
			__YSI_SpecialExit();
			return ret;
		}
		return 1;
	}
	
	public OnGameModeExit()
	{
		//printf("ScriptInit_OnGameModeExit");
		if (YSI_FILTERSCRIPT)
		{
			return ScriptInit_OnGameModeExit();
		}
		else
		{
			//printf("NF 0");
			ScriptInit_OnScriptExit();
			//printf("NF 1");
			//CallRemoteFunction("ScriptInit_OnAnyScriptExit", "");
			new
				ret = ScriptInit_OnGameModeExit();
			//printf("NF 2");
			//ScriptInit_OnScriptExitLate();
			//CallLocalFunction("__YSI_SpecialExit", "");
			__YSI_SpecialExit();
			return ret;
		}
	}
	
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit(%0) ScriptInit_OnGameModeExit(%0) <_ALS_:hooked>
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit(%0) ScriptInit_OnFilterScriptExit(%0) <_ALS_:hooked>
	
	forward ScriptInit_OnFilterScriptExit();public ScriptInit_OnFilterScriptExit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnFilterScriptExit()<>{return 1;}
	forward ScriptInit_OnGameModeExit();public ScriptInit_OnGameModeExit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnGameModeExit()<>{return 1;}
#endif

#define OnScriptInit(%0) ScriptInit_OnScriptInit(%0) <_ALS_:hooked>
#define _ALS_OnScriptInit
forward ScriptInit_OnScriptInit();public ScriptInit_OnScriptInit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnScriptInit()<>{return 1;}

#define OnScriptExit(%0) ScriptInit_OnScriptExit(%0) <_ALS_:hooked>
#define _ALS_OnScriptExit
forward ScriptInit_OnScriptExit();public ScriptInit_OnScriptExit()<_ALS_:unhooked>{return 1;}public ScriptInit_OnScriptExit()<>{return 1;}

//#define _YSI_SpecialInit __YSI_SpecialInit
//#define _ALS__YSI_SpecialInit
//forward _YSI_SpecialInit();

#define _YSI_SpecialExit(%0) __YSI_SpecialExit(%0) <_ALS_:hooked>
#define _ALS__YSI_SpecialExit
//forward _YSI_SpecialExit();
forward __YSI_SpecialExit();public __YSI_SpecialExit()<_ALS_:unhooked>{return 1;}public __YSI_SpecialExit()<>{return 1;}

/*#define OnScriptInitLate(%0) ScriptInit_OnScriptInitLate(%0) <_ALS_:hooked>
forward OnScriptInitLate();public OnScriptInitLate()<_ALS_:unhooked>{return 1;}public OnScriptInitLate()<>{return 1;}

#define OnScriptExitLate(%0) ScriptInit_OnScriptExitLate(%0) <_ALS_:hooked>
forward OnScriptExitLate();public OnScriptExitLate()<_ALS_:unhooked>{return 1;}public OnScriptExitLate()<>{return 1;}

#define OnAnyScriptInit(%0) ScriptInit_OnAnyScriptInit(%0) <_ALS_:hooked>
forward OnAnyScriptInit();public OnAnyScriptInit()<_ALS_:unhooked>{return 1;}public OnAnyScriptInit()<>{return 1;}

#define OnAnyScriptExit(%0) ScriptInit_OnAnyScriptExit(%0) <_ALS_:hooked>
forward OnAnyScriptExit();public OnAnyScriptExit()<_ALS_:unhooked>{return 1;}public OnAnyScriptExit()<>{return 1;}*/

// I'm not quite sure what causes it, but there seems to be a bug in the
// compiler somewhere which messes up the "ysi_debug" automaton and the
// "YSI_FILTERSCRIPT" variable :(.
public _ScriptInit_FixState() <_script_init_fix_state : true>
{
}

public _ScriptInit_FixState() <_script_init_fix_state : false>
{
}
