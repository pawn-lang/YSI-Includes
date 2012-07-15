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

#include "y_bit"
#include "y_debug"

#include "y_master"

#include "y_hooks"
#include "y_playerarray"

#include "y_iterate"

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

enum e_CLASS_FLAGS (<<= 1)
{
	e_CLASS_FLAGS_SKIN   = 0x0000FFFF,
	e_CLASS_FLAGS_ACTIVE = 0x01000000,
	e_CLASS_FLAGS_ENABLED,
	e_CLASS_FLAGS_DEFAULT
}

enum E_CLASS
{
	e_CLASS_FLAGS:E_CLASS_FLAGS,
	Float:E_CLASS_X,
	Float:E_CLASS_Y,
	Float:E_CLASS_Z,
	Float:E_CLASS_A,
	E_CLASS_WEAPONS[MAX_CLASS_SPAWN_WEAPONS + 1],
	//#if defined _YSI_SYSTEM_GROUPS
	Group:E_CLASS_GROUP,
	//#endif
	PlayerArray:E_CLASS_PLAYERS<MAX_PLAYERS>
	//Bit:E_CLASS_PLAYERS[PLAYER_BIT_ARRAY]
}

enum e_CLASS_OPTION (<<= 1)
{
	e_CLASS_OPTION_PAUSED = 0x0000FFFF,
	e_CLASS_OPTION_NORE = 0x00010000,
	e_CLASS_OPTION_LOGIN_SELECT,
	e_CLASS_OPTION_LOGIN_SPAWN,
	e_CLASS_OPTION_REG_SELECT,
	e_CLASS_OPTION_REG_SPAWN,
	e_CLASS_OPTION_HAS_RC_CALLBACK,
	e_CLASS_OPTION_HAS_RS_CALLBACK,
	e_CLASS_OPTION_REFRESH_PAUSE
}

enum e_PLAYER_CLASS (<<= 1)
{
	e_PLAYER_CLASS_SKIN  = 0x000FFFFF,
	e_PLAYER_CLASS_PRESS = 0x00E00000,
	e_PLAYER_CLASS_RIGHT = 0x00200000,
	e_PLAYER_CLASS_MIDDLE,
	e_PLAYER_CLASS_LEFT,
	e_PLAYER_CLASS_EVER, // Has this player EVER spawned?
	e_PLAYER_CLASS_DENY, // Is this player not allowed to see class selection?
	e_PLAYER_CLASS_SPAWNED, // Should this player NOT be allowed to reselect?
	e_PLAYER_CLASS_SELECT,
	e_PLAYER_CLASS_RETURN, // Player is returning to class selection.
	e_PLAYER_CLASS_AFTER_RETURN, // Prevent the double class selection screen.
	e_PLAYER_CLASS_TEMP_SPAWN // Player has spawned once, respawn them.
}

#define e_PLAYER_CLASS_SPAWN_CHECK      (e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_TEMP_SPAWN)

#define CLASS_MOVE_LEFT                 (e_PLAYER_CLASS:-1)
#define CLASS_MOVE_RIGHT                (e_PLAYER_CLASS:1)

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	e_PLAYER_CLASS:YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sLeft,
	YSI_g_sMiddle,
	YSI_g_sRight,
	YSI_g_sClassCount,
	e_CLASS_OPTION:YSI_g_sClassOptions,
	YSI_g_sLastRefuse[MAX_PLAYERS];

static
	bool:YSI_g_sIsFirst = false;

stock
	bool:YSI_gOPRCE = true,
	bool:YSI_gOPRSE = true;

/*----------------------------------------------------------------------------*\
Function:
	Class_IsActive
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a class is currently in use.
\*----------------------------------------------------------------------------*/

#define Class_IsActive(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ACTIVE)

/*----------------------------------------------------------------------------*\
Function:
	Class_Enabled
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a class is currently available for viewing.
\*----------------------------------------------------------------------------*/

#define Class_Enabled(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ENABLED)

/*----------------------------------------------------------------------------*\
Function:
	Class_IsValid
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a number is a valid classid and active.
\*----------------------------------------------------------------------------*/

#define Class_IsValid(%1) \
	((%1) >= 0 && (%1) < MAX_CLASSES && Class_IsActive((%1)))

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

#define Class_X(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_X]
	//(float(YSI_g_sClasses[(%1)][E_CLASS_XY] >> 16) / 10.0)

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

#define Class_Y(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_Y]
	//(float((YSI_g_sClasses[(%1)][E_CLASS_XY] & 0x7FFF) | ((YSI_g_sClasses[(%1)][E_CLASS_XY] & 0x8000) ? (0xFFFF8000) : (0))) / 10.0)

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

#define Class_Z(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_Z]
	//(float(YSI_g_sClasses[(%1)][E_CLASS_ZA] >> 16) / 10.0)

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

#define Class_A(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_A]
	//(float((YSI_g_sClasses[(%1)][E_CLASS_ZA] & 0x7FFF) | (YSI_g_sClasses[(%1)][E_CLASS_ZA] & 0x8000) ? (0xFFFF8000) : (0)) / 10.0)

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

#define Class_Skin(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_SKIN)

//mhook OnScriptInit()
hook OnScriptInit()
{
	// This code placement is not generic.
	YSI_g_sLeft = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
	YSI_g_sMiddle = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
	YSI_g_sRight = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
	return 1;
}

mhook OnPlayerRequestSpawn(playerid)
{
	P:2("hook Class_OnPlayerRequestSpawn called: %d", playerid);
	//P:2("Class_OnPlayerRequestSpawn called");
	if (YSI_g_sClassCount)
	{
		P:5("Class_OnPlayerRequestSpawn: Has class count");
		new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		if (!(Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)))
		{
		//	Class_ResumeRefresh(playerid);
			return 1;
		}
		P:5("Class_OnPlayerRequestSpawn: Can spawn");
		// Don't need this line anymore - it's all done in OnPlayerRequestClass
		// OnPlayerSpawn.
		//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(playerclass), Class_X(playerclass), Class_Y(playerclass), Class_Z(playerclass), Class_A(playerclass), 0, 0, 0, 0, 0, 0);
		new
			time = GetTickCount();
		if ((time - YSI_g_sLastRefuse[playerid]) >= 1000)
		{
			YSI_gOPRSE = false;
			CallRemoteFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
			new
				ret = 1;
			if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RS_CALLBACK)
			{
				YSI_gOPRSE = true;
				ret = CallLocalFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
			}
			P:4("Class_OnPlayerRequestSpawn() return: %d", ret);
			if (ret)
			{
				//#if defined _YSI_SYSTEM_GROUPS
				new
					Group:newgroup = YSI_g_sClasses[playerclass][E_CLASS_GROUP];
				P:4("Class_OnPlayerRequestSpawn() newgroup: %d", _:newgroup);
			//	if (newgroup != Group:-1) Class_ResolveGroups(playerid, newgroup, true); //Group_AddPlayer(newgroup, playerid);
				//#endif
				if (ret == 1)
				{
					//ALS_CALL<PlayerRequestSpawn>
				//	Class_ResumeRefresh(playerid);
					return 1;
				}
				else if(ret == -1)
				{
					YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_SKIN;
					// The order is VERY important here - this will actually
					// call the function further down (directly below in fact).
					//OnPlayerRequestClass(playerid, YSI_g_sLeft);
				//	Class_DoOnPlayerRequestClass(playerid, YSI_g_sLeft);
				}
			}
		}
		YSI_g_sLastRefuse[playerid] = time;
	//	Class_ResumeRefresh(playerid);
		P:5("Class_OnPlayerRequestSpawn: Return 0");
		return 0;
	}
	//ALS_CALL<PlayerRequestSpawn>
//	Class_ResumeRefresh(playerid);
	P:5("Class_OnPlayerRequestSpawn: Return 1");
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
		e_PLAYER_CLASS:old = playerclass;
	//do
	{
		playerclass = (playerclass + dir) % e_PLAYER_CLASS:YSI_g_sClassCount;
		//P:4("Class_OnPlayerRequestClass() playerclass: %d", playerclass);
		/*if (playerclass < e_PLAYER_CLASS:0)
		{
			playerclass = e_PLAYER_CLASS:(YSI_g_sClassCount - 1);
		}
		else if (playerclass >= e_PLAYER_CLASS:YSI_g_sClassCount)
		{
			playerclass = e_PLAYER_CLASS:0;
		}*/
		P:4("Class_FindNew: %d %d", playerclass, playerid);
	}
	//while (playerclass != old && !(Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	return playerclass;
}

mhook OnPlayerRequestClass(playerid, classid)
{
	P:1("Class_OnPlayerRequestClass called: %d, %d", playerid, classid);
	new
		e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid],
		e_PLAYER_CLASS:dir = CLASS_MOVE_RIGHT;
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
	if (classid == YSI_g_sMiddle) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_MIDDLE;
	else if (classid == YSI_g_sLeft) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_LEFT;
	else if (classid == YSI_g_sRight) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_RIGHT;
	playerclass &= e_PLAYER_CLASS_SKIN;
	if (!YSI_g_sClassCount)
	{
		SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
		SetPlayerSkin(playerid, 0);
		P:E("No YSI classes found");
	}
	else
	{
		// Find the next available skin for this player.  I'm still not sure how
		// this handles the case where you can't use any skin.  I'll have to
		// look in to that.
		playerclass = Class_FindNew(playerid, playerclass, dir);
		P:5("Class_OnPlayerRequestClass() selected: %d", playerclass);
	}
	//Class_ResumeRefresh(playerid);
	return Class_Goto(playerid, _:playerclass);
	//ALS_CALL_EX<PlayerRequestClass, ret>
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
	YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS:playerclass;
	// Save the last viewed class so that we know which direction the person
	// went next time OnPlayerRequestClass is called.
	P:2("Class_Goto() end");
	// Call the OnPlayerRequestClassEx functions.
	YSI_gOPRCE = false;
	CallRemoteFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RC_CALLBACK)
	{
		YSI_gOPRCE = true;
		return CallLocalFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerConnect
Params:
	playerid - Player who joined.
Return:
	-
Notes:
	Resets the player's current class.
\*----------------------------------------------------------------------------*/

mhook OnPlayerConnect(playerid)
{
	P:2("Class_OnPlayerConnect called: %d", playerid);
	//P:2("Class_OnPlayerConnect called");
	YSI_g_sPlayerClass[playerid] = 0;
}

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
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], false, bits<MAX_PLAYERS>);
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	//Class_ResolveGroups(i, f, false);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	//YSI_g_sClasses[i][E_CLASS_WEAPONS][MAX_CLASS_SPAWN_WEAPONS] = w[MAX_CLASS_SPAWN_WEAPONS];
	YSI_g_sClassCount++;
	//setproperty(0, "LReqClass", i);
	//#if !defined YSI_CLASS_INVERT
	//	Bit_SetAll(YSI_g_sClasses[i][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
	//#endif
	return i;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerDeath
Params:
	playerid - Player who dies.
	reason - The reason they died.
Return:
	-1 on fake deaths.
Notes:
	Catches and hides fake deaths caused by the spawn system.  Called first.
\*----------------------------------------------------------------------------*/

// We need this definition as we are using "mhook" instead of "hook", which
// can't handle the extra number used to force a call order.
//#define ALS_R_PlayerDeath0 ALS_R_PlayerDeath
hook OnPlayerDeath0(playerid, killerid, reason)
{
	// For consistency all scripts return -1 if the class system thinks this is
	// a fake death caused by the weird respawn selection system.
	if (YSI_g_sIsFirst)
	{
		new
			ret = Class_DoPlayerDeath(playerid, killerid, reason);
		setproperty(8, YSIM_OPDRET, ret);
		return ret;
	}
	return getproperty(8, YSIM_OPDRET);
}

foreign Class_DoPlayerDeath(playerid, killerid, reason);

global Class_DoPlayerDeath(playerid, killerid, reason)
{
	P:2("Class_OnPlayerDeath called: %d, %d, %d", playerid, killerid, reason);
	#pragma unused killerid, reason
	P:2("Class_OnPlayerDeath called");
	//new
	//	time = GetTickCount();
	//new
	//	e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
	//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	//return -1;
	//if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SPAWN_CHECK) == e_PLAYER_CLASS_SPAWN_CHECK)// || (time - YSI_g_sLastRefuse[playerid]) < 200)
	if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN) == e_PLAYER_CLASS_AFTER_RETURN)// || (time - YSI_g_sLastRefuse[playerid]) < 200)
	{
		P:2("Class_OnPlayerDeath: Inner");
		new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		// Fake death to get the ForceClassSelection out the system.
		//SetTimerEx("_Class_DoRespawn", 0, 0, "i", playerid);
		//SetPlayerHealth(playerid, 100.0);
		if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_TEMP_SPAWN) == e_PLAYER_CLASS_TEMP_SPAWN)
		{
			SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_TEMP_SPAWN);
		}
		//YSI_g_sLastRefuse[playerid] = time;
		// Cancel all other callbacks.
		return -1;
	}
	//TogglePlayerControllable(playerid, false);
	if (YSI_g_sClassOptions & e_CLASS_OPTION_NORE)
	{
		/*new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
		SetPlayerHealth(playerid, 100.0);*/
		SetTimerEx("_Class_DoRespawn", 2500, 0, "i", playerid);
		//ForceClassSelection(playerid);
	}
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
	if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN)
	{
		// Fake spawn.
		//SetPlayer
		YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_TEMP_SPAWN;
		return -1;
	}
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_SPAWNED | e_PLAYER_CLASS_EVER) & ~e_PLAYER_CLASS_SELECT;
	new
		playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN,
		weapon;
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
	/*if (YSI_g_sClassOptions & e_CLASS_OPTION_NORE)
	{
		// Yes, if they're NOT allowed to change class, send them back to class
		// selection!  This is so the message doesn't appear.
		ForceClassSelection(playerid);
	}*/
	return 1;
}
