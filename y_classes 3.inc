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

#if !defined MAX_CLASSES
	#define MAX_CLASSES                 (256)
#endif

#if !defined MAX_CLASS_SPAWN_WEAPONS
	#define MAX_CLASS_SPAWN_WEAPONS     (13)
#endif

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR               (100)
#endif

#define OnPlayerRequestClassEx(%0) OnPlayerRequestClassEx_(%0)if(!YSI_gOPRCE)return 0;else
#define OnPlayerRequestSpawnEx(%0) OnPlayerRequestSpawnEx_(%0)if(!YSI_gOPRSE)return 0;else

#define INFINATE_ARMOUR                 (0x00800000)

#define _CLASS_WEAPON_CODE if((n-w)&0x01)while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)P:E(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}else while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(getarg(w++)<<8);else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}

#define _GROUP_MAKE_NAME_CLASSES<%0...%1>   %0Class%1
#define _GROUP_MAKE_LIMIT_CLASSES           MAX_CLASSES

//forward Class_ResolveGroups(class, Group:forgroup, bool:cp);

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
	e_PLAYER_CLASS_SKIN  = 0x000FFFFF,
	e_PLAYER_CLASS_PRESS = 0x00E00000,
	e_PLAYER_CLASS_RIGHT = 0x00200000,
	e_PLAYER_CLASS_MIDDLE,
	e_PLAYER_CLASS_LEFT,
	e_PLAYER_CLASS_NO_RESEL, // Can't reselect a class.
	e_PLAYER_CLASS_IS_SPAWNED,
	e_PLAYER_CLASS_DENIED, // Can't spawn just yet.
	//e_PLAYER_CLASS_FIRST_DEATH,
	e_PLAYER_CLASS_NOT_FIRST, // Already seen one class this time.
	e_PLAYER_CLASS_ALLOW_ONE, // Allowed to reselect once.
	e_PLAYER_CLASS_HAS_EVER_SPAWNED // Has ever spawned.
}

enum e_CLASS_SETTINGS (<<= 1)
{
	e_CLASS_SETTING_NORE
}

#define CLASS_MOVE_LEFT                 (e_PLAYER_CLASS:-1)
#define CLASS_MOVE_RIGHT                (e_PLAYER_CLASS:1)

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	e_PLAYER_CLASS:YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sLeft,
	YSI_g_sMiddle,
	YSI_g_sRight,
	e_CLASS_SETTINGS:YSI_g_sSettings,
	YSI_g_sClassCount;

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
			//YSI_g_sClassOptions = ((funcidx("OnPlayerRequestClassEx_") == -1) ? (e_CLASS_OPTION:0) : (e_CLASS_OPTION_HAS_RC_CALLBACK)) | ((funcidx("OnPlayerRequestSpawnEx_") == -1) ? (e_CLASS_OPTION:0) : (e_CLASS_OPTION_HAS_RS_CALLBACK));
			#if !defined YSI_NO_MASTER
				// Steal the master system.
				_Master_Get(#_YCM, true);
				#if _YSIM_IS_CLOUD
					// Set to uninitialised.
					state _YCM:u;
				#endif
				CallRemoteFunction(#_YCM, "");
				#if _YSIM_IS_CLOUD
					// Fully master.
					state _YCM:y;
				#endif
			#endif
		}
	#endif
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

static stock e_PLAYER_CLASS:Class_FindNew(playerid, e_PLAYER_CLASS:playerclass, e_PLAYER_CLASS:dir)
{
	P:4("e_PLAYER_CLASS:Class_FindNew called: %i, %i, %i", playerid, _:playerclass, _:dir);
	if (playerclass >= e_PLAYER_CLASS:YSI_g_sClassCount)
	{
		playerclass = -dir;
	}
	new
		e_PLAYER_CLASS:old = playerclass % e_PLAYER_CLASS:YSI_g_sClassCount;
	do
	{
		playerclass = (playerclass + dir) % e_PLAYER_CLASS:YSI_g_sClassCount;
		P:4("Class_FindNew: %d %d", playerclass, playerid);
	}
	while (playerclass != old && !(Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	return playerclass;
}

forward _Class_DoSpawn(playerid);

public _Class_DoSpawn(playerid)
{
	// So that they don't briefly see the class selection screen.
	TogglePlayerSpectating(playerid, false);
	SpawnPlayer(playerid);
	printf("3) Hi");
}

mhook OnPlayerRequestClass(playerid, classid)
{
	SetPlayerHealth(playerid, 100.0);
	SetPlayerSpecialAction(playerid, 0);
	P:2("hook OnPlayerRequestClass called: %d, %d", playerid, classid);
	new
		e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid];
	// Default to previous settings always.
	printf("1) %d %d %d", YSI_g_sPlayerClass[playerid], (e_PLAYER_CLASS_ALLOW_ONE | e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL), (e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL));
	if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_ALLOW_ONE | e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL) == (e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL))
	{
		printf("2) %d %d %d", YSI_g_sPlayerClass[playerid], (e_PLAYER_CLASS_ALLOW_ONE | e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL), (e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL));
		playerclass &= e_PLAYER_CLASS_SKIN;
		SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
		SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
		//printf("hmm...");
		//TogglePlayerSpectating(playerid, true);
		SetTimerEx("_Class_DoSpawn", 5, 0, "i", playerid);
		//SpawnPlayer(playerid);
		//SetPlayerHealth(playerid, 0.0);
		TogglePlayerSpectating(playerid, true);
		return -1;
	}
	new
		e_PLAYER_CLASS:dir = CLASS_MOVE_RIGHT;
	// Spawned from returning to class selection but not meant to.
	P:5("Class_OnPlayerRequestClass(): Spawn check %d %d", (playerclass & e_PLAYER_CLASS_SPAWN_CHECK), e_PLAYER_CLASS_SPAWN_CHECK);
	switch (playerclass & e_PLAYER_CLASS_PRESS)
	{
		case e_PLAYER_CLASS_RIGHT:
		{
			if (classid == YSI_g_sMiddle)
			{
				// Went from the right to the middle - that's a move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
		case e_PLAYER_CLASS_MIDDLE:
		{
			if (classid == YSI_g_sLeft)
			{
				// Went from the middle to the left - that's a move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
		default:
		{
			if (classid == YSI_g_sRight)
			{
				// Went from the left to the right - that's a wrap move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
	}
	if (classid == YSI_g_sMiddle)
	{
		YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_MIDDLE | e_PLAYER_CLASS_NOT_FIRST; // | playerclass;
	}
	else if (classid == YSI_g_sLeft)
	{
		YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_LEFT | e_PLAYER_CLASS_NOT_FIRST; // | playerclass;
	}
	else if (classid == YSI_g_sRight)
	{
		YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_RIGHT | e_PLAYER_CLASS_NOT_FIRST; // | playerclass;
	}
	if (playerclass & e_PLAYER_CLASS_NOT_FIRST)
	{
		playerclass &= e_PLAYER_CLASS_SKIN;
		// Is the first time the spawn has been re-called.
	}
	else
	{
		// So that we get the same skin to begin with when returning.
		playerclass = (playerclass & e_PLAYER_CLASS_SKIN) - dir;
	}
	if (YSI_g_sClassCount)
	{
		// Find the next available skin for this player.  I'm still not sure how
		// this handles the case where you can't use any skin.  I'll have to
		// look in to that.
		playerclass = Class_FindNew(playerid, playerclass, dir);
		P:5("Class_OnPlayerRequestClass() selected: %d", playerclass);
		return Class_Goto(playerid, _:playerclass);
	}
	//Class_ResumeRefresh(playerid);
	//YSI_g_sClassOptions &= ~(e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION_PAUSED);
	//ALS_CALL_EX<PlayerRequestClass, ret>
	SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, 0);
	P:E("No YSI classes found");
	return 1;
}

foreign Class_Goto(playerid, playerclass);

global Class_Goto(playerid, playerclass)
{
	P:2("Class_Goto called: %i, %i", playerid, playerclass);
	// This now sets the REAL spawn information, including spawn location.
	// 0.2 code
	//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), weapon1 & 0xFF, weapon1 >>> 8, weapon2 & 0xFF, weapon2 >>> 8, weapon3 & 0xFF, weapon3 >>> 8);
	// 0.3 code
	SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_SKIN) | e_PLAYER_CLASS:playerclass;
	// Save the last viewed class so that we know which direction the person
	// went next time OnPlayerRequestClass is called.
	P:2("Class_Goto() end");
	// Call the OnPlayerRequestClassEx functions.
	/*YSI_gOPRCE = false;
	CallRemoteFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RC_CALLBACK)
	{
		YSI_gOPRCE = true;
		CallLocalFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	}*/
	return 1;
}

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
	//P:2("Class_OnPlayerSpawn called: %d %d", YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN, e_PLAYER_CLASS_AFTER_RETURN);
	new
		playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN,
		weapon;
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~(e_PLAYER_CLASS_NOT_FIRST | e_PLAYER_CLASS_ALLOW_ONE)) | e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_IS_SPAWNED;
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
	return 1;
}

mhook OnPlayerConnect(playerid)
{
	P:2("Classes_OnPlayerConnect called");
	YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS:0;
	TogglePlayerSpectating(playerid, false);
	return 1;
}

mhook OnPlayerDeath(playerid, killerid, reason)
{
	P:2("Classes_OnPlayerDeath called");
	// TogglePlayerSpectating(playerid, false);
	// if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL | e_PLAYER_CLASS_FIRST_DEATH) == (e_PLAYER_CLASS_HAS_EVER_SPAWNED | e_PLAYER_CLASS_NO_RESEL))
	// {
		// //YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_FIRST_DEATH;
		// SpawnPlayer(playerid);
		// //SetTimerEx("_Class_DoSpawn", 2500, 0, "i", playerid);
		// SetPlayerHealth(playerid, 100.0);
		// return -1;
	// }
	YSI_g_sPlayerClass[playerid] &= ~e_PLAYER_CLASS_IS_SPAWNED;
	return 1;
}

mhook OnPlayerRequestSpawn(playerid)
{
	P:2("Classes_OnPlayerRequestSpawn called");
	return 1; //!(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_DENIED);
}

mhook OnPlayerDisconnect(playerid, reason)
{
	P:2("Classes_OnPlayerDisconnect called");
	TogglePlayerSpectating(playerid, true);
	return 1; //!(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_DENIED);
}

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
	P:3("Class_Add called: %i, %i, %i, %i, %i, %i (+%i)", skin, x, y, z, a, numargs() - 5);
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
	P:2("Class_AddClass called: %i, %f, %f, %f, %f, %a, %i, %i, %i", s, x, y, z, a, w, c, _:f, _:g);
	new
		i;
	while (i < MAX_CLASSES)
	{
		if (!Class_IsActive(i)) break;
		i++;
	}
	if (i == MAX_CLASSES) return -1;
	YSI_g_sClasses[i][E_CLASS_FLAGS] = 	e_CLASS_FLAGS_ACTIVE | e_CLASS_FLAGS_ENABLED | e_CLASS_FLAGS:s;
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
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	//Class_ResolveGroups(i, f, false);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	YSI_g_sClassCount++;
	return i;
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

foreign Class_Delete(classid);

global Class_Delete(classid)
{
	// P:2("Class_Delete called: %i", classid);
	// if (Class_IsValid(classid))
	// {
		// YSI_g_sClasses[classid][E_CLASS_FLAGS] = e_CLASS_FLAGS:0;
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
	// }
	return 1;
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

foreign Class_SetPlayer(cl, pid, bool:s);

global Class_SetPlayer(cl, pid, bool:s)
{
	return PA_Set(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid, s);
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
	Class_Remote
Params:
	allow - Wether or not to allow changing class.
Return:
	-
Notes:
	Sets wether or not people can change class after first spawning.
\*----------------------------------------------------------------------------*/

stock Class_AllowReselection(allow, playerid = INVALID_PLAYER_ID)
{
	return _Class_AllowReselection(allow, playerid);
}

foreign _Class_AllowReselection(allow, playerid);

global _Class_AllowReselection(allow, playerid)
{
	P:2("Class_AllowReselection called: %i, %i", allow, playerid);
	if (allow)
	{
		if (playerid == INVALID_PLAYER_ID)
		{
			YSI_g_sSettings &= ~e_CLASS_SETTING_NORE;
			foreach (new i : Player)
			{
				YSI_g_sPlayerClass[i] &= ~e_PLAYER_CLASS_NO_RESEL;
			}
		}
		else
		{
			YSI_g_sPlayerClass[playerid] &= ~e_PLAYER_CLASS_NO_RESEL;
		}
		return 1;
	}
	else
	{
		if (playerid == INVALID_PLAYER_ID)
		{
			YSI_g_sSettings |= e_CLASS_SETTING_NORE;
			foreach (new i : Player)
			{
				YSI_g_sPlayerClass[i] |= e_PLAYER_CLASS_NO_RESEL;
			}
		}
		else
		{
			YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_NO_RESEL;
		}
		// ForceClassSelection(playerid);
		return 0;
	}
}

//#pragma deprecate Class_DenySelection
foreign Class_DenySelection(playerid);

global Class_DenySelection(playerid)
{
	TogglePlayerSpectating(playerid, true);
	//return Class_
	if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_IS_SPAWNED)
	{
		YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_IS_SPAWNED) | e_PLAYER_CLASS_DENIED;
	}
	else
	{
		YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_DENIED;
	}
	TogglePlayerControllable(playerid, false);
	SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

foreign Class_ReturnToSelection(playerid);

global Class_ReturnToSelection(playerid)
{
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_DENIED) | e_PLAYER_CLASS_ALLOW_ONE;
	if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_IS_SPAWNED)
	{
		ForceClassSelection(playerid);
	}//
	SetPlayerHealth(playerid, 0.0);
	TogglePlayerSpectating(playerid, true);
	TogglePlayerSpectating(playerid, false);
	// else
	// {
		// //ForceClassSelection(playerid);
		// //SetPlayerHealth(playerid, 0.0);
		// TogglePlayerSpectating(playerid, false);
		// //TogglePlayerControllable(playerid, false);
	// }
	return 1;
}

foreign Class_DisableSelection();

global Class_DisableSelection()
{
	return 1;
}

//#define YSI_SET_LAST_GROUP 22	
#include "internal\y_grouprevert"
