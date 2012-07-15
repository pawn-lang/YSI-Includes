/*----------------------------------------------------------------------------*\
					=======================================
					 y_groups - Player group abstractions! 
					=======================================
Description:
	Admin levels, gangs, teams etc - they're all "groups" of people, this
	provides an abstraction for all of these collections.
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
	
	The Original Code is the YSI group include.
	
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
	29/11/10:
		First version
\*----------------------------------------------------------------------------*/

#include <a_samp>
//#include "..\y_scriptinit"

#define YSIM_U_DISABLE
#include "..\y_master"
#include "..\y_playerarray"

#include "..\y_stringhash"
#include "..\y_debug"

//#include "..\y_hooks"
#include "..\y_amx"

#include "..\y_iterate"

#include "..\y_hooks"

//#define _YSI_HAS_GROUP_SYSTEM

//#define _GROUP_MAKE_NAME<%0...%1> %0_%1
// Dummy value
//#define _GROUP_MAKE_LIMIT               0

// Dummy values.
#undef _GROUP_MAKE_NAME
#undef _GROUP_MAKE_LIMIT
#define _GROUP_MAKE_NAME<%0...%1>       %0_%1
#define _GROUP_MAKE_LIMIT               0

// Example:
//  #define _GROUP_MAKE_NAME<%0...%1> %0Checkpoint%1
/*#if !defined _GROUP_MAKE_NAME
	#error Please define _GROUP_MAKE_NAME before including y_groupsone.
#endif
#if !defined _GROUP_MAKE_LIMIT
	#error Please define _GROUP_MAKE_LIMIT before including y_groupsone.
#endif*/

// Define local variable names.  This will go in the single call file.
//#define _GROUP_LOCAL_NAME               _GROUP_MAKE_NAME<i...>
#define _GROUP_GROUP_NAME               _GROUP_MAKE_NAME<YSI_gs_Group...Data>
#define _GROUP_GLOBAL_NAME              _GROUP_MAKE_NAME<YSI_gs_GroupGlobal...>

#define _GROUP_SET_PLAYER               _GROUP_MAKE_NAME<..._SetPlayer>

/*#define _GROUP_UPDATE                   _GROUP_MAKE_NAME<Group_UpdatePlayer...>
#define _GROUP_UPDATE_ALL               _GROUP_MAKE_NAME<Group_UpdateAll...>

#define _GROUP_GROUP_FUNC               _GROUP_MAKE_NAME<Group_Set...>
#define _GROUP_GLOBAL_FUNC              _GROUP_MAKE_NAME<Group_SetGlobal...>

#define _GROUP_GLOBAL_DEF               _GROUP_MAKE_NAME<Group_SetGlobal...Default>
#define _GROUP_GROUP_DEF                _GROUP_MAKE_NAME<Group_Set...Default>

//#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yH_PlayerConnect_...@yG>
#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yH_PlayerConnect...@yG>

#define _GROUP_DEFAULTS                 _GROUP_MAKE_NAME<Group_...Defaults>

#define _GROUP_INIT                     _GROUP_MAKE_NAME<Group_...Init>*/

#define _GROUP_CREATE                   _GROUP_MAKE_NAME<@yG_Init...>
#define _GROUP_UPDATE_PLAYER            _GROUP_MAKE_NAME<@yG_Upd...>
//#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yG_..._PlayerConnect>
//#define _GROUP_ON_PLAYER_CONNECT        RH:_GROUP_MAKE_NAME<...@yG_OnPlayerConnect>

/*#define _GROUP_OPC_OTHER_CALLED   _GROUP_MAKE_NAME<_@yGPlayerConnect_...>
#define _GROUP_OPC_IS_CALLED   _GROUP_MAKE_NAME<_yG@PlayerConnect_...>
#define _GROUP_OPC_PUBLIC      _GROUP_MAKE_NAME<@yG_PlayerConnect_...>*/

//#define group_hook%0On%1(%2) _GROUP_MAKE_NAME<master_hook On%1...>(%2)
#define ghook group_hook

#define gforeign%1(%2); _GROUP_MAKE_NAME<foreign%1>(%2);
#define gglobal%1(%2) _GROUP_MAKE_NAME<global%1>(%2)

//#define master_hook%0On%2(%3) hook On%2(%3)<>return 1;rehook On%2(%3)<_YCM:y>

#if !defined MAX_GROUP_NAME
	#define MAX_GROUP_NAME              (24)
#endif

#if !defined MAX_GROUPS
	// 1 less than a nice number (with good reason).
	#define MAX_GROUPS                  (Group:127)
#endif

enum e_GROUP_FLAGS (<<= 1)
{
	e_GROUP_FLAGS_GANG = 1,
	// I can't remember why I had this!
	//e_GROUP_FLAGS_CHAT,
	e_GROUP_FLAGS_ACTIVE,
	e_GROUP_FLAGS_COLOR = 0xFFFFFF00
}

enum E_GROUP_DATA
{
	E_GROUP_DATA_NAME[MAX_GROUP_NAME char],
	//E_GROUP_DATA_COUNT,
	E_GROUP_DATA_HASH,
	e_GROUP_FLAGS:E_GROUP_DATA_FLAGS,
}

stock
	PlayerArray:YSI_gGroupPlayers[MAX_GROUPS]<MAX_PLAYERS>,
	YSI_gGroupData[MAX_GROUPS][E_GROUP_DATA];

#define GROUPS_MAX_LIBRARIES            4

static stock
	YSI_g_sNextUpdateFunc,//[32],
	YSI_g_sNextInitFunc,//[32],
	YSI_g_sGroupCount/*,
	bool:YSI_g_sHasOPC = false*/;

#define _Group_HasPlayer(%0,%1) \
	PA_Get(YSI_gGroupPlayers[(%0)],(%1))
	//Bit_Get(YSI_gGroupPlayers[(%0)], (%1), MAX_PLAYERS)

#define _Group_GetColor(%0) \
	(_:(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_COLOR | e_GROUP_FLAGS:0xAA))

#define _Group_SetColor(%0,%1) \
	(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] |= e_GROUP_FLAGS:(%1) & e_GROUP_FLAGS_COLOR)

#define _Group_GetGang(%0) \
	(bool:(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_GANG))

#define _Group_LetGang(%0) \
	(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] |= e_GROUP_FLAGS_GANG)

#define _Group_VetGang(%0) \
	(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] &= ~e_GROUP_FLAGS_GANG)

#define _Group_IsActive(%0) \
	(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

//#define _Group_IsValid(%0) 
//	(0 <= (%0) < MAX_GROUPS && Group_IsActive(%0))

#define _Group_IsValid(%0) \
	(Group:0 <= (%0) < MAX_GROUPS && _Group_IsActive(%0))

#define Group_IsActive(%0) \
	(YSI_gGroupData[GROUP_FIX(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

/*#define Group_IsValid(%0) \
	(GROUP_MASK <= (%0) < (GROUP_MASK + MAX_GROUPS) <=  && Group_IsActive(%0))*/

//#define Group_GetColor(%0) 
//	(YSI_gGroupData[(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_COLOR | 0xAA);
//	(0 <= GROUP_FIX(%0) < MAX_GROUPS && Group_IsActive(%0))

hook OnScriptInit()
{
	state YSI_has_groups:y;
	//YSI_g_sHasOPC = funcidx(#_GROUP_OPC_PUBLIC) != -1;
	//P:2(#_GROUP_OPC_PUBLIC " does%s exist", YSI_g_sHasOPC ? ("") : (" not"));
	//P:5("Group_OnScriptInit: OPC = %d", YSI_g_sHasOPC);
	new
		a = AMX_GetPublicPointer(0, YSI_g_sNextUpdateFunc, "@yG_Upd"),
		idx = AMX_GetPublicPointer(0, YSI_g_sNextInitFunc, "@yG_Init");
	P:5("Group_OnScriptInit: %d, %d", a, idx);
	if (idx)
	{
		//CallLocalFunction(YSI_g_sNextInitFunc, "ii", -1, (a << 16) | idx);
		a = (a << 16) | idx;
		#emit PUSH.S     a
		#emit PUSH.C     0xFFFFFFFF
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sNextInitFunc
		#emit SCTRL      6
	}
}

hook OnPlayerDisconnect(playerid, reason)
{
	P:2("hook OnPlayerDisconnect called: %d, %d", playerid, reason);
	new
		s = Bit_Slot(playerid) + 1,
		Bit:m = ~Bit_Mask(playerid);
	for (new Group:i; i != MAX_GROUPS; ++i)
	{
		// Pre-calculate the slot and mask.  Remove the player from every group
		// they were in.
		YSI_gGroupPlayers[i][s] &= m;
	}
}

/*hook OnPlayerConnect(playerid)
{
	P:2("Group_OnPlayerConnect called");
	if (YSI_g_sHasOPC) CallLocalFunction(#_GROUP_OPC_PUBLIC, "i", playerid);
}

forward _GROUP_OPC_PUBLIC(playerid);*/

foreign Group_SetPlayer(Group:g,p,bool:s);

global Group_SetPlayer(Group:g,p,bool:s)
{
	P:2("Group_SetPlayer called: %i, %i, %i", _:g, p, s);
	//g &= ~GROUP_MASK;
	GROUP_FIX(g);
	if (_Group_IsValid(g) && 0 <= p < MAX_PLAYERS)
	{
		PA_Set(YSI_gGroupPlayers[g], p, s);//, bits<MAX_PLAYERS>);
		P:4("Group_SetPlayer: %d %d", _:g, _:YSI_gGroupPlayers[g][1]);
		/*if (YSI_g_sNextUpdateFunc[0])
		{
			CallLocalFunction(YSI_g_sNextUpdateFunc, "iii", p, _:g, s);
		}*/
		if (YSI_g_sNextUpdateFunc)
		{
			#emit PUSH.S     s
			#emit PUSH.S     g
			#emit PUSH.S     p
			#emit PUSH.C     12
			#emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri
			#emit LOAD.pri   YSI_g_sNextUpdateFunc
			#emit SCTRL      6
		}
	}
	return 1;
}

foreign Group:Group_SetBalancedInternal(p,Group:gs[],s,c);

global Group:Group_SetBalancedInternal(p,Group:gs[],s,c)
{
	// Find which of the listed groups has the least players in.
	#pragma unused s
	new
		count = cellmax,
		Group:id = Group:-1,
		slot = Bit_Slot(p) + 1,
		Bit:mask = Bit_Mask(p),
		Bit:inv = ~mask;
	for (new i = 0; i != c; ++i)
	{
		// Find the group with the least players.
		new
			Group:gi = GROUP_TEMP_FIX(gs[i]);
		if (_Group_IsValid(gi))
		{
			new
				cc = PA_GetCount(YSI_gGroupPlayers[gi]);
			if (YSI_gGroupPlayers[gi][slot] & mask)
			{
				// The player is already in this group - prefer it to others.
				--cc;
				if (cc <= count)
				{
					count = cc;
					id = gi;
				}
				// Remove the player from this group.  Doing this here avoids a
				// double loop.
				YSI_gGroupPlayers[gi][slot] &= inv;
			}
			else
			{
				// Needs to be better than their current group to move.
				if (cc < count)
				{
					count = cc;
					id = gi;
				}
			}
		}
	}
	if (id != Group:-1)
	{
		// Quickly update all the player location stats.
		YSI_gGroupPlayers[id][slot] |= mask;
		// Do all the updates at once insted of using Group_SetPlayer which can
		// be quite slow for large numbers of updates.  I should really encode
		// this in a more generic way so that other people can use this deferal.
		if (YSI_g_sNextUpdateFunc)
		{
			// Using "PUSH.C 0" forces a full update.
			#emit PUSH.C     0
			#emit PUSH.C     0
			#emit PUSH.S     p
			#emit PUSH.C     12
			#emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri
			#emit LOAD.pri   YSI_g_sNextUpdateFunc
			#emit SCTRL      6
		}
		return Group:id;
		//Group_SetPlayer(
	}
	return GROUP_GLOBAL;
}

stock Group:Group_SetBalanced(playerid, {Group, _}:...)
{
	new
		Group:possible[MAX_GROUPS],
		count = numargs();
	switch (count)
	{
		case 1, 2:
		{
			P:W("Group_AddBalanced requires at least 2 groups or an array.");
		}
		case 3:
		{
			new
				third = getarg(2);
			if (third & _:GROUP_MASK)
			{
				// Two groups.
				possible[0] = Group:getarg(1);
				possible[1] = Group:third;
				return Group_SetBalancedInternal(playerid, possible, MAX_GROUPS, 2);
			}
			else
			{
				// Array of groups.
				for (new i = 0; i != third; ++i)
				{
					possible[i] = getarg(1, i);
				}
				return Group_SetBalancedInternal(playerid, possible, MAX_GROUPS, third);
			}
		}
		default:
		{
			for (new i = 1; i != count; ++i)
			{
				possible[i - 1] = getarg(i);
			}
			return Group_SetBalancedInternal(playerid, possible, MAX_GROUPS, count - 1);
		}
	}
}

foreign bool:Group_GetPlayer(Group:g,p);

global bool:Group_GetPlayer(Group:g,p)
{
	P:2("bool:Group_GetPlayer called: %i, %i", _:g, p);
	GROUP_FIX(g);
	if (_Group_IsValid(g) && 0 <= p < MAX_PLAYERS)
	{
		return PA_Get(YSI_gGroupPlayers[g], p);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
	}
	return false;
}

foreign Group_SetName(Group:g,string:n[]);

global Group_SetName(Group:g,string:n[])
{
	P:2("Group_SetName called: %i, \"%s\"", _:g, n);
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		strpack(YSI_gGroupData[g][E_GROUP_DATA_NAME], n, MAX_GROUP_NAME char);
		YSI_gGroupData[g][E_GROUP_DATA_HASH] = YHash(n);
	}
	return 1;
}

foreign string:Group_GetName(Group:g);

global string:Group_GetName(Group:g)
{
	P:2("Group_GetName called: %i", _:g);
	new
		ret[YSI_MAX_STRING];
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		//return Bit_Get(YSI_gGroupPlayers[g], p);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
		strunpack(ret, YSI_gGroupData[g][E_GROUP_DATA_NAME], YSI_MAX_STRING);
	}
	return ret;
}

foreign Group:Group_GetID(string:name[]);

global Group:Group_GetID(string:name[])
{
	P:2("Group_GetID called: %s", name);
	new
		Group:i,
		hash = YHash(name);
	while (i != MAX_GROUPS)
	{
		if (_Group_IsActive(i) && YSI_gGroupData[i][E_GROUP_DATA_HASH] == hash)
		{
			break;
		}
		++i;
	}
	if (i == MAX_GROUPS) return GROUP_GLOBAL;
	return i | GROUP_MASK;
}

foreign Group_SetGang(Group:g,bool:n);

global Group_SetGang(Group:g,bool:n)
{
	P:2("Group_SetGang called: %i, %i", _:g, n);
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		if (n)
		{
			_Group_LetGang(g);
		}
		else
		{
			_Group_VetGang(g);
		}
	}
	return 1;
}

foreign bool:Group_GetGang(Group:g);

global bool:Group_GetGang(Group:g)
{
	P:2("bool:Group_GetGang called: %i", _:g);
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		return _Group_GetGang(g);
	}
	return false;
}

foreign Group_SetColour(Group:g,c);

global Group_SetColour(Group:g,c)
{
	P:2("Group_SetColour called: %i, %i", _:g, c);
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		_Group_SetColor(g, c);
	}
	return 1;
}

foreign Group_GetColour(Group:g);

global Group_GetColour(Group:g)
{
	P:2("Group_GetColour called: %i", _:g);
	GROUP_FIX(g);
	if (_Group_IsValid(g))
	{
		return _Group_GetColor(g);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
	}
	return 0;
}

#define Group_SetColor Group_SetColour
#define Group_GetColor Group_GetColour

foreign Group:Group_Create(string:name[]);

global Group:Group_Create(string:name[])
{
	P:2("Group:Group_Create called: \"%s\"", name);
	P:2("Group_Create called in %d", _@);
	new
		Group:i;
	while (i != MAX_GROUPS && _Group_IsActive(i))
	{
		++i;
	}
	if (i == MAX_GROUPS) return GROUP_GLOBAL;
	strpack(YSI_gGroupData[i][E_GROUP_DATA_NAME], name, MAX_GROUP_NAME char);
	++YSI_g_sGroupCount;
	PA_Init(YSI_gGroupPlayers[i]);
	YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_ACTIVE;
	YSI_gGroupData[i][E_GROUP_DATA_HASH] = YHash(name);
	// Now initialise all the little bits.  __CallRemoteFunction to get ALL
	// scripts which may control part of the group system.
	//CallRemoteFunction(#_GROUP_CREATE, "ii", _:i, -1);
	/*if (YSI_g_sNextInitFunc[0])
	{
		CallLocalFunction(YSI_g_sNextInitFunc, "ii", _:i, -1);
	}*/
	if (YSI_g_sNextInitFunc)
	{
		#emit PUSH.C     0xFFFFFFFF
		#emit PUSH.S     i
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.pri   YSI_g_sNextInitFunc
		#emit SCTRL      6
	}
	return i | GROUP_MASK;
}

// Added for the fun of it.
foreign Group_Destroy(Group:group);

global Group_Destroy(Group:group)
{
	P:2("Group_Destroy called: %i", _:group);
	P:2("Group_Destroy called in %d", _@);
	GROUP_FIX(group);
	if (_Group_IsValid(group))
	{
		YSI_gGroupData[group][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS:0;
		YSI_gGroupData[group][E_GROUP_DATA_HASH] = 0;
		if (YSI_g_sNextUpdateFunc)
		{
			// Update all players who were in this group as they may have lost
			// some permissions.
			foreach (new p : Player)
			{
				if (_Group_HasPlayer(group, p))
				{
					//CallLocalFunction(YSI_g_sNextInitFunc, "iii", p, _:MAX_GROUPS, 0);
					#emit PUSH.C     0
					#emit PUSH.C     0
					#emit PUSH.S     p
					#emit PUSH.C     12
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.pri   YSI_g_sNextUpdateFunc
					#emit SCTRL      6
				}
			}
		}
	}
	return 1;
}

//forward _GROUP_CREATE(group);

/*foreign YSI_gSGroupFunc(Group:group);

global YSI_gSGroupFunc(Group:group)
{
	P:3("YSI_gSGroup called: %i", _:group);
	GROUP_FIX(group);
	if (!_Group_IsValid(group))
	{
		return -1;
	}
	static const
		scDeBruijn[] =
			{
				0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8,
				31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
			};
	new
		cur;
	for (new i = 1; i != bits<MAX_PLAYERS> + 1; ++i)
	{
		if ((cur = _:YSI_gGroupPlayers[group][i]))
		{
			// http://supertech.csail.mit.edu/papers/debruijn.pdf
			return ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
		}
	}
	return -1;
}*/

//foreign YSI_gAGroupFunc(Group:group, start);

//global YSI_gAGroupFunc(Group:group, start)
foreign Group@YSII_Ag(Group:group, start);

global Group@YSII_Ag(Group:group, start)
{
	P:3("YSI_gAGroupFunc called: %i, %i", _:group, start);
	GROUP_FIX(group);
	if (!_Group_IsValid(group))
	{
		return -1;
	}
	static const
		scDeBruijn[] =
			{
				0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8,
				31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
			};
	++start;
	new
		cur,
		i = Bit_Slot(start) + 1;
	if ((cur = (_:YSI_gGroupPlayers[group][i] & (~((1 << start) - 1)))))
	{
		return ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
	}
	++i;
	while (i != bits<MAX_PLAYERS> + 1)
	{
		if ((cur = _:YSI_gGroupPlayers[group][i]))
		{
			return ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
		}
		++i;
	}
	return -1;
}

/*stock Group:operator-(Group:group, Group:playerid)
{
	P:3("Group:operator- called: %i, %i", _:group, _:playerid);
	Group_SetPlayer(group, playerid, false);
	return group;
}

stock Group:operator+(Group:group, playerid)
{
	P:3("Group:operator+ called: %i, %i", _:group, playerid);
	Group_SetPlayer(group, playerid, false);
	return group;
}

stock Group:operator==(Group:group, playerid)
{
	P:3("Group:operator== called: %i, %i", _:group, playerid);
	return Group_GetPlayer(group, playerid);
}*/

//#define YSI_gAGroup(%0)[%1] YSI_gAGroupFunc(%0,%1)

/*foreign Group:YSI_gSPlayerGroupsFunc(playerid);

global Group:YSI_gSPlayerGroupsFunc(playerid)
{
	P:3("Group:YSI_gSPlayerGroups called: %i", playerid);
	new
		s = Bit_Slot(playerid) + 1,
		Bit:m = ~Bit_Mask(playerid);
	for (new Group:i; i != MAX_GROUPS; ++i)
	{
		if (_Group_IsValid(i))
		{
			// Fast membership test.
			if (YSI_gGroupPlayers[i][s] & m)
			{
				return i | GROUP_MASK;
			}
		}
	}
	return Group:-1;
}*/

//foreign Group:YSI_gAPlayerGroupsFunc(playerid, Group:start);

//global Group:YSI_gAPlayerGroupsFunc(playerid, Group:start)
foreign Group:PlayerGroups@YSII_Ag(playerid, Group:start);

global Group:PlayerGroups@YSII_Ag(playerid, Group:start)
{
	P:3("Group:YSI_gAPlayerGroupsFunc called: %i, %i", playerid, _:start);
	// Get the bit for this player in the bit array.
	if (start == Group:-1)
	{
		start = GROUP_MASK;
	}
	new
		s = Bit_Slot(playerid) + 1,
		Bit:m = ~Bit_Mask(playerid);
	// To identify them, groups have special data set, but we need access to
	// the low-level information contained within.
	for (new Group:i = GROUP_TEMP_FIX(start); i != MAX_GROUPS; ++i)
	{
		if (_Group_IsValid(i))
		{
			// Fast membership test.
			if (YSI_gGroupPlayers[i][s] & m)
			{
				return Group:i | GROUP_MASK;
			}
		}
	}
	return Group:-1;
}

stock _Group_ChainCall1(a, h)
{
	// Because "#emit" ignores "#ifdef".
	#emit PUSH.S     a
	#emit PUSH.C     0xFFFFFFFF
	#emit PUSH.C     8
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.S.pri h
	#emit SCTRL      6
}

stock _Group_ChainCall2(s, g, p, n)
{
	// Because "#emit" ignores "#ifdef".
	#emit PUSH.S     s
	#emit PUSH.S     g
	#emit PUSH.S     p
	#emit PUSH.C     12
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.pri   n
	#emit SCTRL      6
}

//#define YSI_gAPlayerGroups(%0)[%1] YSI_gAPlayerGroupsFunc(%0,%1)

// These are hacks to make the old system of functions working.  This is now
// done natively by "y_iterate" - which does free up the "Group" macro for more
// useful things!
//#define Group(%0)_YSII_Sg;_:%1!=-1;%2=_Y_ITER_ARRAY:%8Group(%3)_YSII_Ag[%4] YSI_gSGroupFunc(%0);_:%1!=-1;%2=YSI_gAGroupFunc(%3,%4)

//#define PlayerGroups(%0)_YSII_Sg;_:%1!=-1;%2=_Y_ITER_ARRAY:%8PlayerGroups(%3)_YSII_Ag[%4] YSI_gSPlayerGroupsFunc(%0);_:%1!=-1;%2=YSI_gAPlayerGroupsFunc(%3,%4)

#define _YSIM_RESET_USER
#include "..\y_master"
