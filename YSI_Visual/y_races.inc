/**--------------------------------------------------------------------------**\
					==============================
					 y_hooks - Hook any callback!
					==============================
Description:
	Automatically hooks any callbacks with a very simple syntax.
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
	
	The Original Code is the SA:MP callback hooks include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		Peter, Cam - Support.
		ZeeX, g_aSlice/Slice, Popz, others - Very productive conversations.
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
	2.0
Changelog:
	25/02/12:
		Extracted most of the code to a separate file.
	17/03/11:
		Second complete re-write using another new technique.  Now VERY fast!
		Updated OnPlayerUpdate code using Google63's SCTRL jump code.
	06/08/10:
		First version
\**--------------------------------------------------------------------------**/

#if defined _INC_y_races
	#endinput
#endif
#define _INC_y_races

#if !defined YSI_NO_RACE_POSITION && !defined RACE_POSITION
	#define RACE_POSITION
#endif

#if defined YSI_TESTS
	#define _Y_RACES_STATIC
#else
	#define _Y_RACES_STATIC static
#endif

#include "..\YSI_Players\y_text"
#include "..\YSI_Data\y_bit"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Data\y_playerarray"
#if defined RACE_POSITION
	#include "..\YSI_Coding\y_timers"
#endif

#if !defined MAX_RACES
	#define MAX_RACES 16
#endif

#define YSIM_U_DISABLE
#define MASTER 53
#include "..\YSI_Core\y_master"

#define _GROUP_MAKE_NAME<%0...%1> %0Race%1
#define _GROUP_MAKE_LIMIT         MAX_RACES
#include "..\YSI_Players\y_groups\_funcs"

#include "..\YSI_Coding\y_hooks"

stock _YSI_HAS_y_races(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_races!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

forward Race_Create(laps = 0, entry = 0, countdown = 3, bool:arial = false, bool:fixedPrize = true, exitTime = 0, interior = 0, world = 0, bool:restart = false);
forward Race_Destroy(slot, bool:refund = false);
foreign Race_AddCheckpoint(raceid, Float:x, Float:y, Float:z);
foreign Race_AddStart(raceid, Float:x, Float:y, Float:z, Float:a);
foreign void:Race_SetFixedWin(raceid, set);
foreign void:Race_SetRestart(raceid, set);
foreign void:Race_SetArial(raceid, set);
foreign void:Race_SetCountdown(raceid, countdown);
foreign void:Race_SetInterior(raceid, interior);
foreign void:Race_SetWorld(raceid, world);
foreign void:Race_SetPrize(raceid, position, amount);
foreign void:Race_SetExitTime(raceid, time);
foreign Race_IsActive(raceid);
foreign void:Race_SetLaps(raceid, laps);
foreign void:Race_SetEntry(raceid, cost);
foreign Race_GetPlayerExitedTime(playerid);
foreign Race_PlayerJoin(playerid, race);
forward Race_PlayerLeave(playerid, bool:refund = false);
foreign Race_Start(race);
foreign Race_GetPlayerPosition(playerid);
foreign Race_GetPlayerRaceTime(playerid);
foreign Race_GetPlayerRace(playerid);
foreign Race_SetPlayer(race, playerid, bool:set);

#include "y_races/impl"
#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_races/tests"
	// Get some new IDs.
#endif

#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME

#include "..\YSI_Core\y_master"

