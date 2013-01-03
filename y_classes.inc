/*----------------------------------------------------------------------------*\
					======================================
					 y_classes - Advanced class selection 
					======================================
Description:
	Allows greater control over classes so not everyone has every class.  Uses
	a form of compression for locations.
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
	
	The Original Code is the YSI classes include.
	
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
	0.1
Changelog:
	14/04/12:
		Readded OnRequestSpawn logic.
		Fixed Class_AddWithGroupSet.
		Improved GM/FS interaction.
	02/01/08:
		First '08 edit - Fixed minus numbers in spawn points.
	18/11/07:
		Improved location compression to allow larger areas.
		Moved position code to Class_OnPlayerSpawn to reduce overhead.
	10/10/07:
		Fixed spawn data problem.
	31/08/07:
		Added cheap master system - YSI_SLAVE_CLASSs can't be master.
	05/08/07:
		Fixed a few bugs with repeated selection.
	04/08/07:
		First version.
Functions:
	Public:
		Class_AddRemote - Adds a class to the remote master.
		Class_Remote - Updates settings remotely.
	Core:
		Class_Class - Sets up the system.
		Class_OnPlayerRequestSpawn - Called when a player requests a spawn.
		Class_OnPlayerRequestClass - Called when a player requests a class.
		Class_OnPlayerConnect - Called when a player connects.
	Stock:
		Class_Delete - Removes a class.
		Class_SetPlayer - Sets whether or not a player can use a class.
		Class_Disable - Disables a class.
		Class_Enable - Enables a disabled class.
		Class_AddForGroup - Adds a class to the system for only one group.
		Class_Add - Adds a class to the system.
		Class_AddEx - Adds a class to the system with group selection and setting.
		Class_AddWithGroupSet - Adds a class and sets their group on selection.
		Class_AllowReselection - Allows or disallows people to return to reselect a class.
		Class_RequireSpawnLogin - Require people to login before spawning.
		Class_RequireSelectionLogin - Require people to login before selecting.
		Class_RequireSelectionReg - Require people to register before selecting.
		Class_RequireSpawnReg - Require people to register before spawning.
	Static:
		Class_AddClass - Adds a class, wrapped by API and remote functions.
	Inline:
		Class_IsActive - Checks a class is active.
		Class_Enabled - Checks a class is enabled.
		Class_IsValid - Checks a class is valid.
		Class_X - Gets a classes x position.
		Class_Y - Gets a classes y position.
		Class_Z - Gets a classes z position.
		Class_A - Gets a classes angle.
		Class_Skin - Gets a classes skin.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_CLASSES - Maximum number of classes storeable by the system.
	CLASS_LEFT - Flag for last internal class viewed.
	CLASS_MIDDLE - Flag for last internal class viewed.
	CLASS_RIGHT - Flag for last internal class viewed.
Enums:
	e_CLASS_FLAGS - Small data for individual classes.
	E_CLASS - Class data structure.
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		YSI_g_sClasses - Data for classes.
		YSI_g_sPlayerClass - Player's current classes.
		YSI_g_sLeft - Handle for the first internal class.
		YSI_g_sMiddle - Handle for the second internal class.
		YSI_g_sRight - Handle for the third internal class.
		YSI_g_sClassCount - Number of classes stored.
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_bit"
#include "y_debug"

#define YSIM_U_DISABLE
#include "y_master"

#include "y_iterate"

#include "y_hooks"

#include "internal\y_natives"

#if !defined MAX_CLASSES
	#define MAX_CLASSES                 (256)
#endif

#if !defined MAX_CLASS_SPAWN_WEAPONS
	#define MAX_CLASS_SPAWN_WEAPONS     (13)
#endif

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR               (100)
#endif

//#define OnPlayerRequestClassEx(%0) OnPlayerRequestClassEx_(%0)if(!YSI_gOPRCE)return 0;else
//#define OnPlayerRequestSpawnEx(%0) OnPlayerRequestSpawnEx_(%0)if(!YSI_gOPRCE)return 0;else

//forward OnPlayerRequestClassEx_(playerid, classid);
//forward OnPlayerRequestSpawnEx_(playerid, classid);
forward _Class_OnPlayerRequestClass(playerid, classid);
forward _Class_OnPlayerRequestSpawn(playerid);
forward _Class_OtherRequestClass(playerid, classid);
forward _Class_OtherRequestSpawn(playerid);

#define INFINATE_ARMOUR                 (0x00800000)

#define _CLASS_WEAPON_CODE if((n-w)&0x01)while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)P:E(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}else while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(getarg(w++)<<8);else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}

#define _GROUP_MAKE_NAME_CLASSES<%0...%1>   %0Class%1
#define _GROUP_MAKE_LIMIT_CLASSES           MAX_CLASSES

forward Class_ResolveGroups(class, Group:forgroup, bool:cp);

#include "y_groups"
#include "y_playerarray"

#include "y_iterate"

enum e_CLASS_FLAGS (<<= 1)
{
	e_CLASS_FLAGS_SKIN    = 0x0000FFFF,
	e_CLASS_FLAGS_ENABLED = 0x00010000,
	e_CLASS_FLAGS_ACTIVE
}

enum E_CLASS
{
	e_CLASS_FLAGS:E_CLASS_FLAGS,
	Float:E_CLASS_X,
	Float:E_CLASS_Y,
	Float:E_CLASS_Z,
	Float:E_CLASS_A,
	E_CLASS_WEAPONS[MAX_CLASS_SPAWN_WEAPONS + 1],
	Group:E_CLASS_GROUP,
	PlayerArray:E_CLASS_PLAYERS<MAX_PLAYERS>
}

enum e_PLAYER_CLASS (<<= 1)
{
	e_PLAYER_CLASS_NONE  = 0,
	e_PLAYER_CLASS_SKIN  = 0x000FFFFF,
	e_PLAYER_CLASS_PRESS = 0x00700000,
	e_PLAYER_CLASS_RIGHT = 0x00100000,
	e_PLAYER_CLASS_MIDDLE,
	e_PLAYER_CLASS_LEFT,
	// Control flags.
	e_PLAYER_CLASS_RETURNED,   // Back in class selection.
	e_PLAYER_CLASS_SPAWNSINCE, // Spawned after class selection.
	e_PLAYER_CLASS_DISABLED,   // Class selection disabled.
	e_PLAYER_CLASS_HADFIRST,   // Spawned ever.
	e_PLAYER_CLASS_INSTANT,    // Sent straight to class selection.
	e_PLAYER_CLASS_INSELECT,   // In class selection.
	e_PLAYER_CLASS_IGNORE_ONCE
}

enum e_CLASS_SETTINGS (<<= 1)
{
	e_CLASS_SETTING_NORE = 1,
	e_CLASS_SETTING_OPRCE,
	e_CLASS_SETTING_OPRSE
}

#define CLASS_MOVE_LEFT                 (-1)
#define CLASS_MOVE_RIGHT                (1)
#define CLASS_MOVE_NONE                 (0)

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	e_PLAYER_CLASS:YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sTimer[MAX_PLAYERS],
	YSI_g_sLeft,
	YSI_g_sMiddle,
	YSI_g_sRight,
	e_CLASS_SETTINGS:YSI_g_sSettings,
	YSI_g_sClassCount,
	YSI_g_sHookC,
	YSI_g_sHookS,
	YSI_g_sLastRefuse[MAX_PLAYERS];

stock
	bool:YSI_gOPRCE = true;

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <YSI_has_groups : n>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<n>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
	//else if (forgroup) {}
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
}

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
	//else if (forgroup) {}
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_IsValid
Params:
	classid - Class to check if valid.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_IsValid(%1) (0<=(%1)<MAX_CLASSES&&Class_IsActive(%1))

/*----------------------------------------------------------------------------*\
Function:
	Class_IsValid
Params:
	classid - Class to check if active.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_IsActive(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS]&e_CLASS_FLAGS_ACTIVE)

/*----------------------------------------------------------------------------*\
Function:
	Class_Enabled
Params:
	classid - Class to check.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Enabled(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS]&e_CLASS_FLAGS_ENABLED)

/*----------------------------------------------------------------------------*\
Function:
	Class_X
Params:
	classid - Class to get X location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_X(%1) YSI_g_sClasses[(%1)][E_CLASS_X]

/*----------------------------------------------------------------------------*\
Function:
	Class_Y
Params:
	classid - Class to get Y location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Y(%1) YSI_g_sClasses[(%1)][E_CLASS_Y]

/*----------------------------------------------------------------------------*\
Function:
	Class_Z
Params:
	classid - Class to get Z location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Z(%1) YSI_g_sClasses[(%1)][E_CLASS_Z]

/*----------------------------------------------------------------------------*\
Function:
	Class_A
Params:
	classid - Class to get angle for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_A(%1) YSI_g_sClasses[(%1)][E_CLASS_A]

/*----------------------------------------------------------------------------*\
Function:
	Class_Skin
Params:
	classid - Class to get skin for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Skin(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS]&e_CLASS_FLAGS_SKIN)

/*----------------------------------------------------------------------------*\
Function:
	Class_Class
Params:
	-
Return:
	-
Notes:
	Creates three real player classes so you can scroll correctly with the
	direction being detected.
\*----------------------------------------------------------------------------*/

hook OnScriptInit()
{
	#if !_YSIM_IS_CLIENT
		if (!YSI_FILTERSCRIPT)
		{
			// This code placement is not generic.
			YSI_g_sLeft = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sMiddle = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sRight = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			//printf("==========================");
			//printf("%d %d %d", YSI_g_sLeft, YSI_g_sMiddle, YSI_g_sRight);
			//printf("==========================");
			YSI_g_sSettings = ((funcidx("OnPlayerRequestClassEx_") == -1) ? (e_CLASS_SETTINGS:0) : (e_CLASS_SETTING_OPRCE)) | ((funcidx("OnPlayerRequestSpawnEx_") == -1) ? (e_CLASS_SETTINGS:0) : (e_CLASS_SETTING_OPRSE));
			#if !defined YSI_NO_MASTER
				// Steal the master system.
				_Master_Get(#_YCM, true);
				#if _YSIM_IS_CLOUD
					// Set to uninitialised.
					state _YCM:u;
					//_YCM = _YCM@u;
					_YCM@ = _E_YCM@u;
				#endif
				CallRemoteFunction(#_YCM, "");
				#if _YSIM_IS_CLOUD
					// Fully master.
					state _YCM:y;
					//_YCM = _YCM@y;
					_YCM@ = _E_YCM@y;
				#endif
			#endif
		}
	#endif
	//Hooks_RedirectPublic("OnPlayerRequestClass", "_Class_OnPlayerRequestClass");
	//Hooks_RedirectPublic("OnPlayerRequestSpawn", "_Class_OnPlayerRequestSpawn");
	YSI_g_sHookC = Hooks_RedirectPublic("OnPlayerRequestClass", "_Class_OnPlayerRequestClass");
	YSI_g_sHookS = Hooks_RedirectPublic("OnPlayerRequestSpawn", "_Class_OnPlayerRequestSpawn");
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerRequestClass
Params:
	playerid - Player who requested a class.
	class - Class they requested.
Return:
	-
Notes:
	The input is one of the three real classes used to detect selected
	direction of alteration.  Scans for a class the player is allowed to use
	and hot swaps it out.  Uses SetPlayerSkin AND SetSpawnInfo to combat bugs
	with calling this from OnPlayerRequestSpawn (e.g. the example team script).
	Calls OnPlayerRequestClassEx with the current internal class not the real
	one.
\*----------------------------------------------------------------------------*/

static stock Class_FindNew(playerid, playerclass, dir)
{
	P:4("Class_FindNew called: %i, %i, %i", playerid, playerclass, dir);
	// Handles the special case where "dir" = 0 very nicely with no extra code
	// slowing down the common case (as it should be)!  This is simply because
	// "playerclass != old" will fail on the first loop with "+ 0";
	new
		old = playerclass % YSI_g_sClassCount;
	do
	{
		playerclass = (playerclass + dir) % YSI_g_sClassCount;
		P:4("Class_FindNew: %d %d", playerclass, playerid);
	}
	while (playerclass != old && (!Class_Enabled(playerclass) || !PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	return playerclass;
}

public _Class_OtherRequestClass(playerid, classid)
{
	if (YSI_g_sHookC)
	{
		#emit PUSH.S     classid
		#emit PUSH.S     playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sHookC
		#emit SCTRL      6
		#emit RETN
	}
}

#if !defined YSI_NO_MASTER && _YSIM_IS_CLIENT
	public _Class_OnPlayerRequestClass(playerid, classid)
	{
		return 1;
	}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestClass(playerid, classid) <>
		{
			return 1;
		}
		
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestClass(playerid, classid) <_YCM:y>
		{
	#else
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestClass(playerid, classid)
		{
	#endif
			if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_IGNORE_ONCE))
			{
				SetTimerEx("_Class_SpawnPlayer3", 10, 0, "i", playerid);
				return 1;
			}
			P:1("_Class_OnPlayerRequestClass called: %d %d", playerid, classid);
			Class_TK(playerid);
			new
				dir = CLASS_MOVE_RIGHT;
			// Spawned from returning to class selection but not meant to.
			//P:5("Class_OnPlayerRequestClass(): Spawn check %d %d", playerclass, playerclass); //(playerclass & e_PLAYER_CLASS_SPAWN_CHECK), e_PLAYER_CLASS_SPAWN_CHECK);
			// Find which direction they pressed.
			switch (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_PRESS)
			{
				case e_PLAYER_CLASS_RIGHT:
				{
					if (classid == YSI_g_sMiddle)
					{
						// Went from the right to the middle - that's a move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sLeft)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
				case e_PLAYER_CLASS_MIDDLE:
				{
					if (classid == YSI_g_sLeft)
					{
						// Went from the middle to the left - that's a move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sRight)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
				default:
				{
					if (classid == YSI_g_sRight)
					{
						// Went from the left to the right - that's a wrap move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sMiddle)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
			}
			// Store which class they are now on.
			//printf("%d %d %d %d", classid, YSI_g_sMiddle, YSI_g_sLeft, YSI_g_sRight);
			if (classid == YSI_g_sMiddle)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_MIDDLE | e_PLAYER_CLASS_INSELECT;
			}
			else if (classid == YSI_g_sLeft)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_LEFT | e_PLAYER_CLASS_INSELECT;
			}
			else if (classid == YSI_g_sRight)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_RIGHT | e_PLAYER_CLASS_INSELECT;
			}
			P:C(else {P:E("y_classes unidentified classid.");YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_INSELECT;});
			classid = (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN);
			if (YSI_g_sClassCount)
			{
				// Find the next available skin for this player.  I'm still not sure how
				// this handles the case where you can't use any skin.  I'll have to
				// look in to that.
				// Don't want to get stuck constantly adding "0".
				classid = Class_FindNew(playerid, classid, dir);
				P:5("Class_OnPlayerRequestClass() selected: %d", classid);
				Class_Goto(playerid, _:classid);
			}
			else
			{
				SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
				SetPlayerSkin(playerid, 0);
				P:E("No YSI classes found");
				classid = -1;
			}
			// Now sort out if they actually should be spawned.
			/*if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_IGNORE_ONCE))
			{
				YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_IGNORE_ONCE);
				return 1;
			}
			else*/
			if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE) == (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE))
			{
				YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE);
				Class_Spectate(playerid);
				//SpawnPlayer(playerid);
				//printf("0");
				SetTimerEx("_Class_SpawnPlayer2", 10, 0, "i", playerid);
				YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer4", 50, 0, "i", playerid);
				/*if (YSI_g_sHookC)
				{
					#emit PUSH.C     0xFFFFFFFF
					#emit PUSH.S     playerid
					#emit PUSH.C     8
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.pri   YSI_g_sHookC
					#emit SCTRL      6
					//#emit RETN
				}*/
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, -1);
			}
			else if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_DISABLED | e_PLAYER_CLASS_HADFIRST) == (e_PLAYER_CLASS_DISABLED | e_PLAYER_CLASS_HADFIRST))
			{
				// If class selection is disabled for this player, they have already selected
				// a class and we haven't manually sent them back to the menu.
				//YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE);
				Class_Spectate(playerid);
				//SpawnPlayer(playerid);
				//printf("1");
				SetTimerEx("_Class_SpawnPlayer1", 10, 0, "i", playerid);
				/*if (YSI_g_sHookC)
				{
					#emit PUSH.C     0xFFFFFFFF
					#emit PUSH.S     playerid
					#emit PUSH.C     8
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.pri   YSI_g_sHookC
					#emit SCTRL      6
					//#emit RETN
				}*/
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, -1);
			}
			else
			{
				/*if (YSI_g_sHookC)
				{
					#emit PUSH.S     classid
					#emit PUSH.S     playerid
					#emit PUSH.C     8
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.pri   YSI_g_sHookC
					#emit SCTRL      6
					//#emit RETN
				}*/
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, classid);
			}
			return 1;
		}
#endif

foreign void:Class_Goto(playerid, playerclass);

global void:Class_Goto(playerid, playerclass)
{
	P:2("Class_Goto called: %i, %i", playerid, playerclass);
	// This now sets the REAL spawn information, including spawn location.
	SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~(e_PLAYER_CLASS_SKIN)) | (e_PLAYER_CLASS:playerclass);
	// Save the last viewed class so that we know which direction the person
	// went next time OnPlayerRequestClass is called.
	P:2("Class_Goto() end %08h %08h %d", YSI_g_sSettings, _:e_CLASS_SETTING_OPRCE, playerclass);
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerRequestSpawn
Params:
	playerid - Player who selected a spawn.
Return:
	-
Notes:
	Has inbuilt protection for a bug where selections aren't correctly
	debounced so you can press shift twice at once which can mess up some
	scripts (e.g. the example team selection script).  Calls
	OnPlayerRequestSpawnEx with an additional class parameter.
\*----------------------------------------------------------------------------*/

public _Class_OtherRequestSpawn(playerid)
{
	if (YSI_g_sHookS)
	{
		#emit PUSH.S     playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sHookC
		#emit SCTRL      6
		#emit RETN
	}
}

//mhook OnPlayerRequestSpawn(playerid)

#if !defined YSI_NO_MASTER && (_YSIM_IS_CLIENT || _YSIM_IS_STUB)
	public _Class_OnPlayerRequestSpawn(playerid)
	{
		return 1;
	}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid) <>
		{
			return 1;
		}
		
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid) <_YCM:y>
		{
	#else
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid)
		{
	#endif
			P:2("hook Class_OnPlayerRequestSpawn called: %d", playerid);
			new
				time = GetTickCount();
			if ((time - YSI_g_sLastRefuse[playerid]) >= 1000)
			{
				//YSI_gOPRSE = false;
				//new
				//	ret = 1;
				//if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RS_CALLBACK)
				//{
				//	YSI_gOPRSE = true;
				//	ret = CallLocalFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
				//}
				new
					ret = CallRemoteFunction("_Class_OtherRequestSpawn", "i", playerid);
				P:4("Class_OnPlayerRequestSpawn() return: %d", ret);
				if (ret)
				{
					//#if defined _YSI_SYSTEM_GROUPS
					new
						Group:newgroup = YSI_g_sClasses[(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN)][E_CLASS_GROUP];
					P:4("Class_OnPlayerRequestSpawn() newgroup: %d", _:newgroup);
					if (newgroup != Group:-1) Class_ResolveGroups(playerid, newgroup, true); //Group_AddPlayer(newgroup, playerid);
					//#endif
					if (ret == -1)
					{
						YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_SKIN;
						// The order is VERY important here - this will actually
						// call the function further down (directly below in fact).
						//OnPlayerRequestClass(playerid, YSI_g_sLeft);
						//Class_DoOnPlayerRequestClass(playerid, YSI_g_sLeft);
						switch (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_PRESS)
						{
							case e_PLAYER_CLASS_RIGHT:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sLeft);
							}
							case e_PLAYER_CLASS_MIDDLE:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sRight);
							}
							case e_PLAYER_CLASS_LEFT:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sMiddle);
							}
						}
					}
					else
					{
						return 1;
					}
				}
			}
			YSI_g_sLastRefuse[playerid] = time;
			//Class_ResumeRefresh(playerid);
			P:5("Class_OnPlayerRequestSpawn: Return 0");
			return 0;
		}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerSpawn
Params:
	playerid - Player who spawned.
Return:
	-
Notes:
	Sets a player's position based on skin.
\*----------------------------------------------------------------------------*/

mhook OnPlayerSpawn(playerid)
{
	P:2("Class_OnPlayerSpawn called: %d", playerid);
	Class_TK(playerid);
	new
		playerclass = _:(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN),
		weapon;
	//YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~(e_PLAYER_CLASS_NOT_FIRST | e_PLAYER_CLASS_ALLOW_ONE)) | e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_IS_SPAWNED;
	for (new i = 0; i != MAX_CLASS_SPAWN_WEAPONS; ++i)
	{
		weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][i];
		//if (weapon == WEAPON_ARMOUR) SetPlayerArmour(playerid, 100.0);
		if (weapon)
		{
			GivePlayerWeapon(playerid, weapon & 0xFF, weapon >>> 8);
		}
		else
		{
			break;
		}
	}
	weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][MAX_CLASS_SPAWN_WEAPONS];
	P:5("Class_OnPlayerSpawn: Armour %d %d %d", weapon, weapon & 0xFF, WEAPON_ARMOUR);
	if ((weapon & 0xFF) == WEAPON_ARMOUR)
	{
		weapon >>>= 8;
		if (weapon == 0x00800000)
		{
			// INFINITY
			SetPlayerArmour(playerid, Float:0x7F800000);
		}
		else
		{
			SetPlayerArmour(playerid, weapon);
		}
	}
	// Now update reselection variables.
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~(e_PLAYER_CLASS_INSELECT | e_PLAYER_CLASS_IGNORE_ONCE)) | (e_PLAYER_CLASS_HADFIRST);
	if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_RETURNED))
	{
		if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_INSTANT))
		{
			YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_SPAWNSINCE);
		}
		else
		{
			YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_RETURNED);
		}
	}
	//if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_DISABLED))
	//{
		// I know it may seem odd to force class selection when it is explicitly
		// disabled, but this will disable the "F4" message too.
		//ForceClassSelection(playerid);
	//}
	return 1;
}

forward _Class_SpawnPlayer1(playerid);

public _Class_SpawnPlayer1(playerid)
{
	P:1("_Class_SpawnPlayer1 called: %d", playerid);
	//SpawnPlayer(playerid);
	YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_IGNORE_ONCE);
	TogglePlayerSpectating(playerid, false);
	//SpawnPlayer(playerid);
	//YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer3", 20, 0, "i", playerid);
	//Class_TK(playerid);
}

forward _Class_SpawnPlayer2(playerid);

public _Class_SpawnPlayer2(playerid)
{
	P:1("_Class_SpawnPlayer2 called: %d", playerid);
	//SpawnPlayer(playerid);
	//YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_IGNORE_ONCE);
	TogglePlayerSpectating(playerid, false);
	//Class_TK(playerid);
}

forward _Class_SpawnPlayer3(playerid);

public _Class_SpawnPlayer3(playerid)
{
	P:1("_Class_SpawnPlayer3 called: %d", playerid);
	SpawnPlayer(playerid);
	//Class_TK(playerid);
	//YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_IGNORE_ONCE);
	//TogglePlayerSpectating(playerid, false);
	//Class_TK(playerid);
}

forward _Class_SpawnPlayer4(playerid);

public _Class_SpawnPlayer4(playerid)
{
	P:1("_Class_SpawnPlayer4 called: %d", playerid);
	//SpawnPlayer(playerid);
	Class_Spectate(playerid);
	if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_DISABLED))
	{
		YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer1", 10, 0, "i", playerid);
	}
	else
	{
		YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer2", 10, 0, "i", playerid);
	}
	//Class_TK(playerid);
	//YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_IGNORE_ONCE);
	//TogglePlayerSpectating(playerid, false);
	//Class_TK(playerid);
}

forward _Class_Return(playerid);

public _Class_Return(playerid)
{
	P:1("_Class_Return called: %d", playerid);
	Class_ReturnToSelection(playerid);
	//Class_TK(playerid);
	//YSI_g_sTimer[playerid] = SetTimerEx("_Class_NotSpawned", 500, 0, "i", playerid);
}

forward _Class_NotSpawned(playerid);

public _Class_NotSpawned(playerid)
{
	P:1("_Class_NotSpawned called: %d", playerid);
	// Called if they don't connect properly.
	Class_DisableSelection(playerid);
	//SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	//SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	SetTimerEx("_Class_Return", 10, 0, "i", playerid);
	YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_INSTANT);
}

static stock Class_TK(playerid)
{
	// "Timer Kill".
	if (YSI_g_sTimer[playerid])
	{
		KillTimer(YSI_g_sTimer[playerid]);
		YSI_g_sTimer[playerid] = 0;
	}
}

mhook OnPlayerConnect(playerid)
{
	//printf("OnPlayerConnect %d", playerid);
	YSI_g_sPlayerClass[playerid] = (e_PLAYER_CLASS_NONE);
	YSI_g_sTimer[playerid] = SetTimerEx("_Class_NotSpawned", 500, 0, "i", playerid);
	NO_GROUPS()
	{
		new
			slot = Bit_Slot(playerid) + 1,
			Bit:mask = Bit_Mask(playerid); //Bit:(1 << (playerid & (cellbits - 1)));
		for (new i = 0; i != MAX_CLASSES; ++i)
		{
			YSI_g_sClasses[i][E_CLASS_PLAYERS][slot] |= mask;
		}
	}
	return 1;
}

/*mhook OnPlayerDeath(playerid, killerid, reason)
{
}

mhook OnPlayerRequestSpawn(playerid)
{
}

mhook OnPlayerDisconnect(playerid, reason)
{
}*/

/*----------------------------------------------------------------------------*\
Function:
	Class_Add
Params:
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons and ammo (weapon then ammo)
Return:
	-
Notes:
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.  This is one of
	the few API functions which is not entirely remote.  This is because it has
	variable parameters which is need to collect in to a single array to pass to
	the remote function.
\*----------------------------------------------------------------------------*/

stock Class_Add(skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	//printf("Class_Add called: %i, %f, %f, %f, %f, (+%i)", skin, x, y, z, a, numargs() - 5);
	P:3("Class_Add called: %i, %f, %f, %f, %f, (+%i)", skin, x, y, z, a, numargs() - 5);
	new
		n = numargs(),
		w = 5,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, Group:-1);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddEx
Params:
	forgroup - Group that can use the skin.
	setgroup - Group to add the player to on selection.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons and ammo (weapon then ammo)
Return:
	-
Notes:
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.
\*----------------------------------------------------------------------------*/

stock Class_AddEx(Group:forgroup, Group:setgroup, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_AddEx called: %i, %i, %i, %f, %f, %f, %f (+%i)", _:forgroup, _:setgroup, skin, x, y, z, a, numargs() - 7);
	new
		n = numargs(),
		w = 7,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, forgroup, setgroup);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddForGroup
Params:
	group - Group to allow to use the class.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Weapon data.
Return:
	-
Notes:
	Adds a class only people in the specified group can use.
\*----------------------------------------------------------------------------*/

stock Class_AddForGroup(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_AddForGroup called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
	new
		n = numargs(),
		w = 6,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, group, Group:-1);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddWithGroupSet
Params:
	group - Group to make players who use this group.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons.
Return:
	-
Notes:
	Adds a class which puts you in the specified group when selected.
\*----------------------------------------------------------------------------*/

stock Class_AddWithGroupSet(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_AddWithGroupSet called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
	new
		n = numargs(),
		w = 6,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, group);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddClass
Params:
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	weapons[] - Array of spawn weapon data.
	count - Number of weapons added.
	forgroup - Group that can use the class.
	asgroup - Group to assign people to with this class.
Return:
	-
Notes:
	Does the hard work.  This took a long time to get working correctly with the
	new master system, infact getting just this one function to compile took a
	major re-working of the macros to reduce the length of intermediate stages.
\*----------------------------------------------------------------------------*/

foreign Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g);

global Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g)
{
	//printf("Class_AddClass called: %i, %f, %f, %f, %f, %s, %i, %i, %i", s, x, y, z, a, Debug_PrintArray(w, c), c, _:f, _:g);
	P:2("Class_AddClass called: %i, %f, %f, %f, %f, %s, %i, %i, %i", s, x, y, z, a, Debug_PrintArray(w, c), c, _:f, _:g);
	new
		i;
	while (i < MAX_CLASSES)
	{
		if (!Class_IsActive(i)) break;
		i++;
	}
	if (i == MAX_CLASSES) return -1;
	YSI_g_sClasses[i][E_CLASS_FLAGS] = e_CLASS_FLAGS_ACTIVE | e_CLASS_FLAGS_ENABLED | e_CLASS_FLAGS:s;
	YSI_g_sClasses[i][E_CLASS_X] = x;
	YSI_g_sClasses[i][E_CLASS_Y] = y;
	YSI_g_sClasses[i][E_CLASS_Z] = z;
	YSI_g_sClasses[i][E_CLASS_A] = a;
	new
		j;
	// This may be better with a memcpy.
	while (j < c)
	{
		P:5("Class_AddClass: weapon %d %d %d", j, c, w[j]);
		YSI_g_sClasses[i][E_CLASS_WEAPONS][j] = w[j];
		++j;
	}
	//printf("Class_AddClass: weapon %d %d %d", j, c, i);
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	//printf("Class_AddClass: weapon %d %d %d", j, c, f);
	Class_ResolveGroups(i, f, false);
	//printf("Class_AddClass: weapon %d %d %d", j, c, g);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	YSI_g_sClassCount++;
	//printf("Class_AddClass: weapon %d %d %d", j, c, YSI_g_sClassCount);
	return i;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_HasGroup
Params:
	classid - The class to test.
	Group:group - The group to test setting of.
Return:
	Does this class add players to the given group on spawn?
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Class_HasGroup(classid, Group:group);

global Class_HasGroup(classid, Group:group)
{
	return YSI_g_sClasses[classid][E_CLASS_GROUP] == group;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Enable
Params:
	-
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Class_Enable(classid, bool:toggle);

global Class_Enable(classid, bool:toggle)
{
	if (Class_IsValid(classid))
	{
		if (toggle)
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] |= e_CLASS_FLAGS_ENABLED;
		}
		else
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] &= ~e_CLASS_FLAGS_ENABLED;
			// TODO!  Hide the class for anyone currently viewing it.
			// foreach (new playerid : Player)
			// {
				// new
					// e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[playerid];
				// P:4("Class_Delete: %d %d %d", playerid, curclass, e_PLAYER_CLASS_SELECT);
				// if (curclass & e_PLAYER_CLASS_SELECT)
				// {
					// if (e_PLAYER_CLASS:classid == curclass & e_PLAYER_CLASS_SKIN) Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS:classid, CLASS_MOVE_RIGHT));
				// }
			// }
		}
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Delete
Params:
	classid - Class to delete.
Return:
	-
Notes:
	Completely removes a class from the system.
\*----------------------------------------------------------------------------*/

foreign void:Class_Delete(classid);

global void:Class_Delete(classid)
{
	P:2("Class_Delete called: %i", classid);
	if (Class_Enable(classid, false))
	{
		YSI_g_sClasses[classid][E_CLASS_FLAGS] = e_CLASS_FLAGS:0;
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_SetPlayer
Params:
	classid - Class to set permissions for.
	playerid - Player to set for.
	set - Whether or not they can use this class.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign void:Class_SetPlayer(cl, pid, bool:s);

global void:Class_SetPlayer(cl, pid, bool:s)
{
	//printf("CLASS SET PLAYER: %d %d %d", cl, pid, s);
	PA_Set(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid, s);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_GetPlayer
Params:
	classid - Class to set permissions for.
	playerid - Player to set for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Class_GetPlayer(cl,pid);

global bool:Class_GetPlayer(cl,pid)
{
	return PA_Get(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Get
Params:
	playerid - Player to get the current class of.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Class_Get(playerid);

global Class_Get(playerid)
{
	if (0 <= playerid < MAX_PLAYERS)
	{
		return _:(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN);
	}
	return -1;
}

foreign void:Class_DisableSelection(playerid);

global void:Class_DisableSelection(playerid)
{
	if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_INSELECT)
	{
		Class_Spectate(playerid);
		Class_TK(playerid);
	}
	//return 1;
}

foreign void:Class_DisableReselection(playerid);

global void:Class_DisableReselection(playerid)
{
	YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_DISABLED);
	// Disable "F4".
	//ForceClassSelection(playerid);
	//return 1;
}

foreign void:Class_EnableReselection(playerid);

global void:Class_EnableReselection(playerid)
{
	YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_DISABLED);
	//return 1;
}

foreign void:Class_ForceReselection(playerid);

global void:Class_ForceReselection(playerid)
{
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_RETURNED) & ~(e_PLAYER_CLASS_SPAWNSINCE);
	ForceClassSelection(playerid);
	//return 1;
}

foreign void:Class_ReturnToSelection(playerid);

global void:Class_ReturnToSelection(playerid)
{
	YSI_g_sPlayerClass[playerid] |= (e_PLAYER_CLASS_INSTANT);
	Class_ForceReselection(playerid);
	TogglePlayerSpectating(playerid, false);
	//return 1;
}

static stock Class_Spectate(playerid)
{
	new
		Float:x1,
		Float:y1,
		Float:z1;
	GetPlayerCameraPos(playerid, x1, y1, z1);
	new
		Float:x2,
		Float:y2,
		Float:z2;
	GetPlayerCameraFrontVector(playerid, x2, y2, z2);
	TogglePlayerSpectating(playerid, true);
	SetPlayerCameraPos(playerid, x1, y1, z1);
	SetPlayerCameraLookAt(playerid, x2, y2, z2);
	PlayerSpectatePlayer(playerid, playerid, SPECTATE_MODE_FIXED);
}

#if defined _ALS_AddPlayerClass
	#undef AddPlayerClass
#else
	#define _ALS_AddPlayerClass
#endif
#define AddPlayerClass Class_Add

//#define YSI_SET_LAST_GROUP 22	
#include "internal\y_grouprevert"
