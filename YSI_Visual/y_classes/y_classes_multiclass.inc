/*
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

forward Class_ResolveGroups(class, Group:forgroup, bool:cp);

enum e_CLASS_FLAGS:(<<= 1)
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

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sInternalClass[MAX_PLAYERS],
	YSI_g_sClassCount = 0,
	YSI_g_sLastRefuse[MAX_PLAYERS];

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <YSI_has_groups : n>
{
	#pragma unused forgroup
	Debug_Print2("Class_ResolveGroups<n>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
}

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <>
{
	#pragma unused forgroup
	Debug_Print2("Class_ResolveGroups<>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
}

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to check if active.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Class_IsActive(classid));
#define _Class_IsActive(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ACTIVE)

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to check if valid.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Class_IsValid(classid));
#define _Class_IsValid(%1) (IS_IN_RANGE((%1), 0, MAX_CLASSES) && _Class_IsActive(%1))

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to check.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:_Class_Enabled(classid));
#define _Class_Enabled(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ENABLED)

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to get X location for.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Float:Class_X(classid));
#define Class_X(%1) YSI_g_sClasses[(%1)][E_CLASS_X]

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to get Y location for.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Float:Class_Y(classid));
#define Class_Y(%1) YSI_g_sClasses[(%1)][E_CLASS_Y]

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to get Z location for.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Float:Class_Z(classid));
#define Class_Z(%1) YSI_g_sClasses[(%1)][E_CLASS_Z]

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to get angle for.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Float:Class_A(classid));
#define Class_A(%1) YSI_g_sClasses[(%1)][E_CLASS_A]

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to get skin for.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Class_Skin(classid));
#define Class_Skin(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_SKIN)

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Creates three real player classes so you can scroll correctly with the
 *   direction being detected.
 * </remarks>
 * <transition keep="true" target="_YCM : u"/>
 * <transition keep="true" target="_YCM : y"/>
 *//*------------------------------------------------------------------------**/

HOOK__ OnYSIInit()
{
	#if !_YSIM_IS_CLIENT
		if (!Script_IsFilterscript())
		{
			// This code placement is not generic.
			new
				classLeft = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0),
				classMiddle = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0),
				classRight = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
			if (classLeft != 0 || classMiddle != 1 || classRight != 2)
			{
				Debug_Error("y_classes assumptions failed.  Do you have \"AddPlayerClass\" in your modes?");
			}
			//print("==========================");
			Debug_Print4("Class_OnYSIInit: classes = %d %d %d", classLeft, classMiddle, classRight);
			//print("==========================");
			#if !defined YSI_NO_MASTER
				switch (_Master_Get(#_YCM, true))
				{
					case e_YSIM_GET_TYPE_NO_CONTEST:
					{
						// Nothing changed, or we took it without force.
						Debug_Print2("Got master " #_YCM);
						state _YCM:y;
						_YCM@ = _E_YCM@y;
					}
					case e_YSIM_GET_TYPE_STOLE:
					{
						// Something changed, tell other scripts.
						state _YCM:u;
						_YCM@ = _E_YCM@u;
						// Determine the next unique name.
						CallRemoteFunction(#_YCM, YSI_EMPTY);
						// There is a note in y_master about this being safe
						// because servers always get the data.  This is the server
						// code, but may be in use by cloud systems.  This, however,
						// is still not a problem because we never fully pass off.
					}
					case e_YSIM_GET_TYPE_NOT_GOT:
					{
						Debug_Error("`E_YSIM_GET_TYPE_NOT_GOT` with `force = true`");
					}
				}
			#endif
		}
	#endif
	return 1;
}

static stock Class_FindNew(playerid, playerclass, dir)
{
	Debug_Print4("Class_FindNew called: %i, %i, %i", playerid, playerclass, dir);
	if (dir == 0)
	{
		// No change, check the current skin is still valid.  There are plenty
		// of reasons for this: Removed skin, returned -1, disabled, returned to
		// class selection.  This used to not be handled explicitly, but now it
		// is.
		if (_Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)) return playerclass;
		++dir;
	}
	new
		old = playerclass % YSI_g_sClassCount;
	do
	{
		playerclass = (playerclass + dir) % YSI_g_sClassCount;
		Debug_Print4("Class_FindNew: %d %d", playerclass, playerid);
	}
	while (playerclass != old && (!_Class_Enabled(playerclass) || !PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	// (!(playerclass == old || (_Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid))))
	return playerclass;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is changing class.</param>
 * <param name="playerclass">The internal class they are switching to.</param>
 * <remarks>
 *   Does the visual faking through "SetPlayerSkin", and also calls
 *   "SetSpawnInfo" to avoid any lag from "SetPlayerPos" under "OnPlayerSpawn".
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Class_Goto(playerid, playerclass);

GLOBAL__ void:Class_Goto(playerid, playerclass)
{
	Debug_Print2("Class_Goto called: %i, %i", playerid, playerclass);
	// This now sets the REAL spawn information, including spawn location.
	SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
	SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
	YSI_g_sPlayerClass[playerid] = playerclass; //(YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_SKIN) | (e_PLAYER_CLASS:playerclass);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who selected a spawn.</param>
 * <remarks>
 *   Has inbuilt protection for a bug where selections aren't correctly
 *   debounced so you can press shift twice at once which can mess up some
 *   scripts (e.g. the example team selection script).  Calls
 *   OnPlayerRequestSpawnEx with an additional class parameter.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined YSI_NO_MASTER && (_YSIM_IS_CLIENT || _YSIM_IS_STUB)
	public OnPlayerRequestSpawn(playerid)
	{
		return 1;
	}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		public OnPlayerRequestSpawn(playerid) <>
		{
			return 1;
		}
		
		public OnPlayerRequestSpawn(playerid) <_YCM:y>
	#else
		public OnPlayerRequestSpawn(playerid)
	#endif
		{
			Debug_Print1("Class_OnPlayerRequestSpawn called: %d", playerid);
			new
				time = GetTickCount();
			if ((time - YSI_g_sLastRefuse[playerid]) >= 500)
			{
				new
					ret = CallRemoteFunction("Class_OnPlayerRequestSpawn", YSI_gcI, playerid);
				Debug_Print4("Class_OnPlayerRequestSpawn() return: %d", ret);
				if (ret)
				{
					new
						Group:newgroup = YSI_g_sClasses[YSI_g_sPlayerClass[playerid]][E_CLASS_GROUP];
					Debug_Print4("Class_OnPlayerRequestSpawn() newgroup: %d", _:newgroup);
					if (newgroup != Group:-1) Class_ResolveGroups(playerid, newgroup, true);
					if (ret == -1)
					{
						// Send the player back to class selection.
						_Class_OnPlayerRequestClass(playerid, YSI_g_sInternalClass[playerid]);
					}
					else
					{
						return 1;
					}
				}
			}
			Debug_Print5("Class_OnPlayerRequestSpawn: Return 0");
			return
				YSI_g_sLastRefuse[playerid] = time,
				0;
		}
#endif

CHAIN_FORWARD:Class_OnPlayerRequestSpawn(playerid) = 1;
#if defined _ALS_OnPlayerRequestSpawn
	#undef OnPlayerRequestSpawn
#else
	#define _ALS_OnPlayerRequestSpawn
#endif
#define OnPlayerRequestSpawn(%0) CHAIN_PUBLIC:Class_OnPlayerRequestSpawn(%0)

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who spawned.</param>
 * <remarks>
 *   Sets a player's position based on skin.
 * </remarks>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerSpawn(playerid)
{
	Debug_Print2("Class_OnPlayerSpawn called: %d", playerid);
	new
		playerclass = YSI_g_sPlayerClass[playerid],
		weapon = 0;
	for (new i = 0; i != MAX_CLASS_SPAWN_WEAPONS; ++i)
	{
		weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][i];
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
	Debug_Print5("Class_OnPlayerSpawn: Armour %d %d %d", weapon, weapon & 0xFF, WEAPON_ARMOUR);
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

MASTER_REHOOK__ OnPlayerSpawn(playerid)
{
	#pragma unused playerid
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who joined the server.</param>
 * <remarks>
 *   Reset all the data on this player's current classes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerConnect(playerid)
{
	YSI_g_sPlayerClass[playerid] = -1,
	YSI_g_sInternalClass[playerid] = -1;
	NO_GROUPS<Class>()
	{
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		for (new i = 0; i != MAX_CLASSES; ++i)
		{
			YSI_g_sClasses[i][E_CLASS_PLAYERS][slot] |= mask;
		}
	}
	return 1;
}

MASTER_REHOOK__ OnPlayerConnect(playerid)
{
	#pragma unused playerid
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Converts the variable arguments to an array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define _CLASS_WEAPON_CODE \
	{if((n-w+1)/2>MAX_CLASS_SPAWN_WEAPONS) Debug_Error("Excessive class weapon data."); \
	if((n-w)&0x01){while(w!=n)if((cw=getarg(w++))==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)Debug_Error(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);} \
	else{while(w!=n)weapons[((cw=getarg(w++))==WEAPON_ARMOUR)?MAX_CLASS_SPAWN_WEAPONS:(s++)]=(cw&0xFF)|(getarg(w++)<<8);}}

/*-------------------------------------------------------------------------*//**
 * <param name="skin">Skin of the class.</param>
 * <param name="x">X spawn location.</param>
 * <param name="y">Y spawn location.</param>
 * <param name="z">Z spawn location.</param>
 * <param name="a">A spawn location.</param>
 * <param name="">Spawn weapons and ammo (weapon then ammo)</param>
 * <remarks>
 *   Pretty much AddPlayerClass but allows greater control over the classes.
 *   Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.  This is one of
 *   the few API functions which is not entirely remote.  This is because it has
 *   variable parameters which is need to collect in to a single array to pass to
 *   the remote function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Class_Add(skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	Debug_Print3("Class_Add called: %i, %f, %f, %f, %f, (+%i)", skin, x, y, z, a, numargs() - 5);
	new
		n = numargs(),
		w = 5,
		s = 0,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw = 0;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, Group:-1);
}

/*-------------------------------------------------------------------------*//**
 * <param name="forgroup">Group that can use the skin.</param>
 * <param name="setgroup">Group to add the player to on selection.</param>
 * <param name="skin">Skin of the class.</param>
 * <param name="x">X spawn location.</param>
 * <param name="y">Y spawn location.</param>
 * <param name="z">Z spawn location.</param>
 * <param name="a">A spawn location.</param>
 * <param name="">Spawn weapons and ammo (weapon then ammo)</param>
 * <remarks>
 *   Pretty much AddPlayerClass but allows greater control over the classes.
 *   Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Class_AddEx(Group:forgroup, Group:setgroup, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	Debug_Print3("Class_AddEx called: %i, %i, %i, %f, %f, %f, %f (+%i)", _:forgroup, _:setgroup, skin, x, y, z, a, numargs() - 7);
	new
		n = numargs(),
		w = 7,
		s = 0,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw = 0;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, forgroup, setgroup);
}

/*-------------------------------------------------------------------------*//**
 * <param name="group">Group to allow to use the class.</param>
 * <param name="skin">Skin of the class.</param>
 * <param name="x">X spawn location.</param>
 * <param name="y">Y spawn location.</param>
 * <param name="z">Z spawn location.</param>
 * <param name="a">A spawn location.</param>
 * <param name="">Weapon data.</param>
 * <remarks>
 *   Adds a class only people in the specified group can use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Class_AddForGroup(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	Debug_Print3("Class_AddForGroup called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
	new
		n = numargs(),
		w = 6,
		s = 0,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw = 0;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, group, Group:-1);
}

/*-------------------------------------------------------------------------*//**
 * <param name="group">Group to make players who use this group.</param>
 * <param name="skin">Skin of the class.</param>
 * <param name="x">X spawn location.</param>
 * <param name="y">Y spawn location.</param>
 * <param name="z">Z spawn location.</param>
 * <param name="a">A spawn location.</param>
 * <param name="">Spawn weapons.</param>
 * <remarks>
 *   Adds a class which puts you in the specified group when selected.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Class_AddWithGroupSet(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	Debug_Print3("Class_AddWithGroupSet called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
	new
		n = numargs(),
		w = 6,
		s = 0,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw = 0;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, group);
}

/*-------------------------------------------------------------------------*//**
 * <param name="skin">Skin of the class.</param>
 * <param name="x">X spawn location.</param>
 * <param name="y">Y spawn location.</param>
 * <param name="z">Z spawn location.</param>
 * <param name="a">A spawn location.</param>
 * <param name="weapons">Array of spawn weapon data.</param>
 * <param name="count">Number of weapons added.</param>
 * <param name="forgroup">Group that can use the class.</param>
 * <param name="asgroup">Group to assign people to with this class.</param>
 * <remarks>
 *   Does the hard work.  This took a long time to get working correctly with the
 *   new master system, infact getting just this one function to compile took a
 *   major re-working of the macros to reduce the length of intermediate stages.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,const w[],c,Group:f,Group:g);

GLOBAL__ Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,const w[],c,Group:f,Group:g)
{
	#pragma unused c
	Debug_Print2("Class_AddClass called: %i, %f, %f, %f, %f, %s, %i, %i, %i", s, x, y, z, a, Debug_PrintArray(w, c), c, _:f, _:g);
	new
		i = 0;
	while (i != MAX_CLASSES && _Class_IsActive(i)) ++i;
	if (i == MAX_CLASSES) return -1;
	YSI_g_sClasses[i][E_CLASS_FLAGS] = e_CLASS_FLAGS_ACTIVE | e_CLASS_FLAGS_ENABLED | e_CLASS_FLAGS:s,
	YSI_g_sClasses[i][E_CLASS_X] = x,
	YSI_g_sClasses[i][E_CLASS_Y] = y,
	YSI_g_sClasses[i][E_CLASS_Z] = z,
	YSI_g_sClasses[i][E_CLASS_A] = a,
	memcpy(YSI_g_sClasses[i][E_CLASS_WEAPONS], w, 0, (MAX_CLASS_SPAWN_WEAPONS + 1) * 4, MAX_CLASS_SPAWN_WEAPONS + 1);
	// Debug_Print7("Class_AddClass: weapon %d %d %d", j, c, i);
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	// Debug_Print7("Class_AddClass: weapon %d %d %d", j, c, f);
	Class_ResolveGroups(i, f, false);
	// Debug_Print7("Class_AddClass: weapon %d %d %d", j, c, g);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	YSI_g_sClassCount++;
	// Debug_Print7("Class_AddClass: weapon %d %d %d", j, c, YSI_g_sClassCount);
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="classid">The class to test.</param>
 * <param name="group">The group to test setting of.</param>
 * <returns>
 *   Does this class add players to the given group on spawn?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Class_HasGroup(classid, Group:group);

GLOBAL__ Class_HasGroup(classid, Group:group)
{
	return YSI_g_sClasses[classid][E_CLASS_GROUP] == group;
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

FOREIGN__ Class_Enable(classid, bool:toggle);

GLOBAL__ Class_Enable(classid, bool:toggle)
{
	if (_Class_IsValid(classid))
	{
		if (toggle)
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] |= e_CLASS_FLAGS_ENABLED;
		}
		else
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] &= ~e_CLASS_FLAGS_ENABLED;
			// Hide the class for anyone currently viewing it.
			FOREACH__ (new playerid : Player)
			{
				Debug_Print5("Class_Enable: %d %d %d", playerid, _:YSI_g_sPlayerClass[playerid], _:e_PLAYER_CLASS_IN_SELECTION);
				if (Player_InSelection(playerid))
				{
					_Class_OnPlayerRequestClass(playerid, YSI_g_sInternalClass[playerid]);
				}
			}
		}
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to delete.</param>
 * <remarks>
 *   Completely removes a class from the system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Class_Delete(classid);

GLOBAL__ void:Class_Delete(classid)
{
	Debug_Print2("Class_Delete called: %i", classid);
	if (Class_Enable(classid, false))
	{
		YSI_g_sClasses[classid][E_CLASS_FLAGS] = e_CLASS_FLAGS:0;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to set permissions for.</param>
 * <param name="playerid">Player to set for.</param>
 * <param name="set">Whether or not they can use this class.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Class_SetPlayer(cl, pid, bool:s);

GLOBAL__ void:Class_SetPlayer(cl, pid, bool:s)
{
	PA_Set(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid, s);
}

/*-------------------------------------------------------------------------*//**
 * <param name="classid">Class to set permissions for.</param>
 * <param name="playerid">Player to set for.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Class_GetPlayer(cl,pid);

GLOBAL__ bool:Class_GetPlayer(cl,pid)
{
	return PA_Get(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get the current class of.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Class_Get(playerid);

GLOBAL__ Class_Get(playerid)
{
	if (VALID_PLAYERID(playerid))
	{
		return YSI_g_sPlayerClass[playerid];
	}
	return -1;
}

#if defined _ALS_AddPlayerClass
	#undef AddPlayerClass
#else
	#define _ALS_AddPlayerClass
#endif
#define AddPlayerClass Class_Add

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player whose current class view may need to change.</param>
 * <remarks>
 *   If you change a player's groups while they are in class selection, call this
 *   function to potentially update the currently displayed class.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Class_Reprocess(playerid)
{
	if (!Player_InSelection(playerid))
		return 0;
	new
		classid = -1;
	if (YSI_g_sClassCount)
	{
		// Find the next available skin for this player.  I'm still not
		// sure how this handles the case where you can't use any skin.
		// I'll have to look in to that - don't want to get stuck
		// constantly adding "0".
		classid = Class_FindNew(playerid, YSI_g_sPlayerClass[playerid], 0),
		Class_Goto(playerid, classid);
		Debug_Print5("Class_Reprocess() selected: %d", classid);
	}
	else
	{
		Debug_Error("No YSI classes found");
		SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0),
		SetPlayerSkin(playerid, 0);
	}
	return CallRemoteFunction("Class_OnPlayerRequestClass", "ii", playerid, classid);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who requested a class.</param>
 * <param name="class">Class they requested.</param>
 * <remarks>
 *   The input is one of the three real classes used to detect selected
 *   direction of alteration.  Scans for a class the player is allowed to use
 *   and hot swaps it out.  Uses SetPlayerSkin AND SetSpawnInfo to combat bugs
 *   with calling this from OnPlayerRequestSpawn (e.g. the example team script).
 *   Calls OnPlayerRequestClassEx with the current internal class not the real
 *   one.
 *
 *   Last thing in the file to be simpler to call directly.  If we ever have a
 *   more complex ALS hook on this callback the main body of this code will have
 *   to be moved in to its own function.  As indeed it now does!
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnPlayerRequestClass(playerid, classid)
{
	return _Class_OnPlayerRequestClass(playerid, classid);
}

// Pre-empt y_hooks.
#if !defined YSI_NO_MASTER && _YSIM_IS_CLIENT
		static stock _Class_OnPlayerRequestClass(playerid, classid)
		{
			#pragma unused playerid, classid
			return 1;
		}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		static stock _Class_OnPlayerRequestClass(playerid, classid) <>
		{
			#pragma unused playerid, classid
			return 1;
		}
		
		static stock _Class_OnPlayerRequestClass(playerid, classid) <_YCM:y>
	#else
		static stock _Class_OnPlayerRequestClass(playerid, classid)
	#endif
		{
			Debug_Print1("Class_OnPlayerRequestClass called: %d %d", playerid, classid);
			// Find which direction they pressed.
			if (YSI_g_sClassCount)
			{
				// Find the next available skin for this player.  I'm still not
				// sure how this handles the case where you can't use any skin.
				// I'll have to look in to that - don't want to get stuck
				// constantly adding "0".
				new
					cid = classid;
				classid = Class_FindNew(playerid, YSI_g_sPlayerClass[playerid], ((classid - YSI_g_sInternalClass[playerid]) + 1) % 3 - 1),
				YSI_g_sInternalClass[playerid] = cid,
				Class_Goto(playerid, classid);
				Debug_Print5("Class_OnPlayerRequestClass() selected: %d", classid);
			}
			else
			{
				Debug_Error("No YSI classes found");
				SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0),
				SetPlayerSkin(playerid, 0),
				classid = -1;
			}
			return CallRemoteFunction("Class_OnPlayerRequestClass", "ii", playerid, classid);
		}
#endif

// Use the special pre-y_hooks hook method.
CHAIN_FORWARD:Class_OnPlayerRequestClass(playerid, classid) = 1;
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass(%0) CHAIN_PUBLIC:Class_OnPlayerRequestClass(%0)

