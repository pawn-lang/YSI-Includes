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


#if defined _inc_y_groups__funcs
	#undef _inc_y_groups__funcs
#endif

//#if !defined _INC_y_groups__funcs
//	#define _INC_y_groups__funcs
//	#include "..\..\YSI_Core\y_utils"
//	#include "..\..\YSI_Data\y_bit"
//	#include "y_groups_setup"
//	#include "..\..\YSI_Data\y_iterate"
//#endif

//#if !defined _GROUP_MAKE_TAG
//	#define _GROUP_MAKE_TAG _
//#endif

// Start of the multi-use file.
static stock
	YSI_g_sMaxEncountered = -1,
	BitArray:YSI_g_sElementAllowed[_GROUP_MAKE_LIMIT]<_:_MAX_GROUPS_G>,
	BitArray:YSI_g_sElementDenied[_GROUP_MAKE_LIMIT]<_:_MAX_GROUPS_G>,
	BitArray:YSI_g_sDefaultAllowed<_:_MAX_GROUPS_G>,
	BitArray:YSI_g_sDefaultDenied<_:_MAX_GROUPS_G>,
	BitArray:YSI_g_sEmpty<_:_MAX_GROUPS_G>,
	_yGI = 0,
	_yGU = 0,
	_yGA = 0;

//// Define the callback chaining for the current 
//#if defined _YSI_HAS_y_groups
//	#define GFOREIGN__%1(%2); _GROUP_MAKE_NAME<FOREIGN__%1>(%2);
//	#define GGLOBAL__%1(%2) _GROUP_MAKE_NAME<GLOBAL__%1>(%2)
//	#define GPUBLIC__ MASTER_FUNC__
#if YSIM_HAS_MASTER
	#if _YSIM_IS_CLIENT
		#define GCHAIN__%0(%2) static stock _GROUP_MAKE_NAME<%0...>(%2)
	#elseif _YSIM_IS_SERVER
		#define GCHAIN__%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2)for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
	#elseif _YSIM_IS_STUB
		#define GCHAIN__%0(%2) static stock _GROUP_MAKE_NAME<%0...>(%2)
	#else
		#define GCHAIN__%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2)<>GROUP_CHAIN?<%0>(%2);public _GROUP_MAKE_NAME<%0...>(%2)<_YCM:y>for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
	#endif
#else
	#define GCHAIN__%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2)for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
#endif
//#elseif __COMPILER_1ST_PASS
//	#define GFOREIGN__%0...%1(%2) _GROUP_MAKE_FUNC<@@>:_GROUP_MAKE_NAME<%0...>(%2);_GROUP_MAKE_NAME<%0...%1>(%2)
//	#define GGLOBAL__%0...%1(%2) static stock _GROUP_MAKE_NAME<%0...%1>(%2)
//	#define GPUBLIC__%0(%2) _GROUP_MAKE_FUNC<@@>:_GROUP_MAKE_NAME<%0...>(%2);_GROUP_MAKE_NAME<%0...>(%2);static stock _GROUP_MAKE_NAME<%0...>(%2)
//	#define GCHAIN__%0(%2) _GROUP_MAKE_FUNC<@@>:_GROUP_MAKE_NAME<%0...>(%2);_GROUP_MAKE_NAME<%0...>(%2);static stock _GROUP_MAKE_NAME<%0...>(%2)
//	#define _GROUP_SET_PLAYER(%0) P:E(#_GROUP_MAKE_NAME<..._SetPlayer> " called without y_groups")
//#else
//	#define GGLOBAL__%0...%1(%2) static stock _GROUP_MAKE_NAME<%0...%1>(%2)
//	#define GPUBLIC__%0(%2) static stock _GROUP_MAKE_NAME<%0...>(%2)
//	#define GCHAIN__%0(%2) static stock _GROUP_MAKE_NAME<%0...>(%2)
//	#define _GROUP_SET_PLAYER(%0) P:E(#_GROUP_MAKE_NAME<..._SetPlayer> " called without y_groups")
//#endif

//#if YSI_KEYWORD(gforeign)
//	 #define gforeign GFOREIGN__
//#endif
//#if YSI_KEYWORD(gglobal)
//	 #define gglobal GGLOBAL__
//#endif
//#if YSI_KEYWORD(gpublic)
//	 #define gpublic GPUBLIC__
//#endif
//#if YSI_KEYWORD(_gchain)
//	 #define _gchain GCHAIN__
//#endif

/*-------------------------------------------------------------------------*//**
 * <param name="x">The element that was added (maybe).</param>
 * <remarks>
 *  This is called when a new element is created, and as such it is NOT chained
 *  to other parts of the groups system because each part handles one type of
 *  element.  Loop through all players and set up the element for them if they
 *  are in a group that this is also in by default.
 *
 *  If x is "_GROUP_MAKE_LIMIT" then this is the test used in OnPlayerConnect in
 *  various libraries to see if the groups system exists, and if not locally
 *  initialise the player instead of leaving it up to this system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _GROUP_MAKE_NAME<..._InitialiseFromGroups>(_GROUP_MAKE_TAG:x = _GROUP_MAKE_TAG:_GROUP_MAKE_LIMIT)
{
	P:4(#_GROUP_MAKE_NAME<..._InitialiseFromGroups> " called: %i", x);
	// A new item has been added to the system - update all players according to
	// the default settings for a group.
	if (x != _GROUP_MAKE_TAG:_GROUP_MAKE_LIMIT)
	{
		YSI_g_sElementAllowed[_:x] = YSI_g_sDefaultAllowed,
		YSI_g_sElementDenied[_:x] = YSI_g_sDefaultDenied,
		YSI_g_sMaxEncountered = max(YSI_g_sMaxEncountered, _:x);
		FOREACH__ (new playerid : Player)
		{
			Group_FullPlayerUpdate(playerid, _:x, YSI_g_sEmpty, YSI_g_sDefaultAllowed, YSI_g_sEmpty, YSI_g_sDefaultDenied, YSI_gGroupPlayers[playerid]);
		}
	}
	return 0;
}

/*

     ad88888ba  88                         88             
    d8"     "8b ""                         88             
    Y8,                                    88             
    `Y8aaaaa,   88 8b,dPPYba,   ,adPPYb,d8 88  ,adPPYba,  
      `"""""8b, 88 88P'   `"8a a8"    `Y88 88 a8P_____88  
            `8b 88 88       88 8b       88 88 8PP"""""""  
    Y8a     a8P 88 88       88 "8a,   ,d88 88 "8b,   ,aa  
     "Y88888P"  88 88       88  `"YbbdP"Y8 88  `"Ybbd8"'  
                                aa,    ,88                
                                 "Y8bbdP"                 

*/

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Set...</summary>
 * <param name="g">Group to set for.</param>
 * <param name="el">Element to set.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  If "s" is true, then one element is added to the current group.  False it is
 *  removed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_Set...(Group:g,_GROUP_MAKE_TAG:el,E_GROUP_SET:s);

GGLOBAL__ Group_Set...(Group:g,_GROUP_MAKE_TAG:el,E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...> " called: %i, %i, %i", _:g, _:el, _:s);
	// Set wether a group can use this item.
	if (0 <= _:el < _GROUP_MAKE_LIMIT && g <= GROUP_GLOBAL)
	{
		// There is now NO validity check for reasons of distruibution.
		GROUP_FIX(g);
		new
			slot = Bit_Slot(g),
			Bit:mask = Bit_Mask(g),
			Bit:neg = ~mask;
		P:5(#_GROUP_MAKE_NAME<Group_Set...> ": %i, %i", _:slot, _:mask);
		YSI_gTempAllowed_ = YSI_g_sElementAllowed[_:el];
		YSI_gTempDenied_ = YSI_g_sElementDenied[_:el];
		if (s == E_GROUP_SET:ALLOW)
		{
			// Is this element allowed in the current group?
			if ((YSI_gTempAllowed_[slot] & mask) && !(YSI_gTempDenied_[slot] & mask))
			{
				// No point adding an element to a group that it is already in.
				return 1;
			}
			YSI_gTempAllowed_[slot] |= mask;
			YSI_gTempDenied_[slot] &= neg;
		}
		else if (s == E_GROUP_SET:DENY)
		{
			// Is this element denied in the current group?
			if ((YSI_gTempDenied_[slot] & mask))
			{
				// No point banning an element from a group that it is already in.
				YSI_g_sElementAllowed[_:el][slot] &= neg;
				return 1;
			}
			YSI_gTempAllowed_[slot] &= neg;
			YSI_gTempDenied_[slot] |= mask;
		}
		else
		{
			// Is this element NOT in the current group?
			if (!(YSI_gTempAllowed_[slot] & mask) && !(YSI_gTempDenied_[slot] & mask))
			{
				return 1;
			}
			YSI_gTempAllowed_[slot] &= ~mask;
			YSI_gTempDenied_[slot] &= ~mask;
		}
		FOREACH__ (new playerid : Player)
		{
			if (YSI_gGroupPlayers[playerid][slot] & mask)
			{
				// The player is in the group in question, so they need a full
				// update.
				Group_FullPlayerUpdate(playerid, _:el, YSI_g_sElementAllowed[_:el], YSI_gTempAllowed_, YSI_g_sElementDenied[_:el], YSI_gTempDenied_, YSI_gGroupPlayers[playerid]);
			}
		}
		YSI_g_sElementAllowed[_:el] = YSI_gTempAllowed_;
		YSI_g_sElementDenied[_:el] = YSI_gTempDenied_;
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_...Allowed</summary>
 * <param name="g">Group to get from.</param>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the group have the element explicitly allowed?
 * </returns>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ bool:Group_...Allowed(Group:g,_GROUP_MAKE_TAG:el);

GGLOBAL__ bool:Group_...Allowed(Group:g,_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_Get...> " called: %i, %i", _:g, _:el);
	return (0 <= _:el < _GROUP_MAKE_LIMIT && g <= GROUP_GLOBAL && !Bit_Get(YSI_g_sElementDenied[_:el], _:GROUP_TEMP_FIX(g)) && Bit_Get(YSI_g_sElementAllowed[_:el], _:GROUP_TEMP_FIX(g)));
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_...Denied</summary>
 * <param name="g">Group to get from.</param>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the group have the element explicitly denied?
 * </returns>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ bool:Group_...Denied(Group:g,_GROUP_MAKE_TAG:el);

GGLOBAL__ bool:Group_...Denied(Group:g,_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_Get...> " called: %i, %i", _:g, _:el);
	return (0 <= _:el < _GROUP_MAKE_LIMIT && g <= GROUP_GLOBAL && Bit_Get(YSI_g_sElementDenied[_:el], _:GROUP_TEMP_FIX(g)));
}

#pragma deprecated Use `Group_...Allowed` or `Group_...Denied`.
stock E_GROUP_SET:_GROUP_MAKE_NAME<Group_Get...>(Group:g,_GROUP_MAKE_TAG:el)
{
	// This returns truthy for both allowed and denied.  The function is
	// deprecated, so this is probably OK, because only people with legacy code
	// (thus not using denials) will be calling this function.
	P:2(#_GROUP_MAKE_NAME<Group_Get...> " called: %i, %i", _:g, _:el);
	return
		_GROUP_MAKE_NAME<Group_...Denied>(g, el) ? E_GROUP_SET:DENY :
		_GROUP_MAKE_NAME<Group_...Allowed>(g, el) ? E_GROUP_SET:ALLOW :
		E_GROUP_SET:UNDEF;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Set...Default</summary>
 * <param name="g">Group to set for.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  If "s" is true, then all elements are added to this group (i.e. the default
 *  is set to true and all previous settings are wiped out).  If it is false
 *  then all elements are removed and a full update is done.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_Set...Default(Group:g,E_GROUP_SET:s);

GGLOBAL__ Group_Set...Default(Group:g,E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...Default> " called: %i, %i", _:g, _:s);
	if (g <= GROUP_GLOBAL)
	{
		// There is now NO validity check for reasons of distruibution.
		GROUP_FIX(g);
		new
			slot = Bit_Slot(g),
			Bit:mask = Bit_Mask(g),
			Bit:inv = ~mask,
			Iterator:GP<MAX_PLAYERS>;
		FOREACH__ (new playerid : Player)
		{
			// Do this check here so it is only done once per player.  This is a
			// good argument for moving iterators to be duplicated in every
			// script; however, the default "Group()" iterator implementation is
			// a function, not a standard iterator - actually it now isn't...
			if (YSI_gGroupPlayers[playerid][slot] & mask)
			{
				// Make a fast local iterator of all the players.
				Iter_Add(GP, playerid);
			}
		}
		if (s == E_GROUP_SET:ALLOW)
		{
			P:5(#_GROUP_MAKE_NAME<Group_Set...Default> ": ALLOW");
			YSI_g_sDefaultAllowed[slot] |= mask;
			YSI_g_sDefaultDenied[slot] &= inv;
			for (new el = 0; el <= YSI_g_sMaxEncountered; ++el)
			{
				// Check if this group already has this element.
				YSI_gTempAllowed_ = YSI_g_sElementAllowed[el];
				YSI_gTempDenied_ = YSI_g_sElementDenied[el];
				P:7(#_GROUP_MAKE_NAME<Group_Set...Default> ": element %d %d %d", _:el, YSI_gTempAllowed_[slot] & mask, YSI_gTempDenied_[slot] & mask);
				if ((YSI_gTempAllowed_[slot] & mask) && !(YSI_gTempDenied_[slot] & mask))
				{
					// Could already be seen, thus no change.
					continue;
				}
				YSI_gTempAllowed_[slot] |= mask;
				YSI_gTempDenied_[slot] &= inv;
				// Is this element NOT in the current group?
				FOREACH__ (new playerid : GP)
				{
					Group_FullPlayerUpdate(playerid, el, YSI_g_sElementAllowed[el], YSI_gTempAllowed_, YSI_g_sElementDenied[el], YSI_gTempDenied_, YSI_gGroupPlayers[playerid]);
				}
				YSI_g_sElementAllowed[el][slot] |= mask;
				YSI_g_sElementDenied[el][slot] &= inv;
			}
		}
		else if (s == E_GROUP_SET:DENY)
		{
			P:5(#_GROUP_MAKE_NAME<Group_Set...Default> ": DENY");
			YSI_g_sDefaultAllowed[slot] &= inv;
			YSI_g_sDefaultDenied[slot] |= mask;
			for (new el = 0; el <= YSI_g_sMaxEncountered; ++el)
			{
				YSI_gTempDenied_ = YSI_g_sElementDenied[el];
				P:7(#_GROUP_MAKE_NAME<Group_Set...Default> ": element %d %d %d", _:el, YSI_g_sElementAllowed[el][slot] & mask, YSI_gTempDenied_[slot] & mask);
				if (YSI_gTempDenied_[slot] & mask)
				{
					// Already denied.  Doesn't matter what the old `Allowed`
					// state was because denials override them
					Bit_Vet(YSI_g_sElementAllowed[el], _:g);
					continue;
				}
				// Is this element NOT in the current group?
				YSI_gTempDenied_[slot] |= mask;
				FOREACH__ (new playerid : GP)
				{
					// `YSI_gTempAllowed_` IS NEVER SET.  We don't need it at
					// all in `Group_FullPlayerUpdate` because we know that
					// `YSI_gTempDenied_` has at least one bit set, and will
					// therefore prevent the current state of allows being
					// checked.
					Group_FullPlayerUpdate(playerid, el, YSI_g_sElementAllowed[el], YSI_gTempAllowed_, YSI_g_sElementDenied[el], YSI_gTempDenied_, YSI_gGroupPlayers[playerid]);
				}
				YSI_g_sElementAllowed[el][slot] &= inv;
				YSI_g_sElementDenied[el][slot] |= mask;
			}
		}
		else
		{
			P:5(#_GROUP_MAKE_NAME<Group_Set...Default> ": UNDEF");
			YSI_g_sDefaultAllowed[slot] &= inv;
			YSI_g_sDefaultDenied[slot] &= inv;
			for (new el = 0; el <= YSI_g_sMaxEncountered; ++el)
			{
				YSI_gTempAllowed_ = YSI_g_sElementAllowed[el];
				YSI_gTempDenied_ = YSI_g_sElementDenied[el];
				P:7(#_GROUP_MAKE_NAME<Group_Set...Default> ": element %d %d %d", _:el, YSI_gTempAllowed_[slot] & mask, YSI_gTempDenied_[slot] & mask);
				if (!(YSI_gTempAllowed_[slot] & mask) && !(YSI_gTempDenied_[slot] & mask))
				{
					// Nothing has changed.
					continue;
				}
				// Is this element in the current group?
				YSI_gTempAllowed_[slot] &= inv;
				YSI_gTempDenied_[slot] &= inv;
				FOREACH__ (new playerid : GP)
				{
					Group_FullPlayerUpdate(playerid, el, YSI_g_sElementAllowed[el], YSI_gTempAllowed_, YSI_g_sElementDenied[el], YSI_gTempDenied_, YSI_gGroupPlayers[playerid]);
				}
				YSI_g_sElementAllowed[el][slot] &= inv;
				YSI_g_sElementDenied[el][slot] &= inv;
			}
		}
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Set...New</summary>
 * <param name="g">Group to set for.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  Similar to "Group_Set...Default", but doesn't reset all existing elements,
 *  just sets the permissions for any future items.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_Set...New(Group:g,E_GROUP_SET:s);

GGLOBAL__ Group_Set...New(Group:g,E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...New> " called: %i, %i", _:g, _:s);
	if (g <= GROUP_GLOBAL)
	{
		GROUP_FIX(g);
		// There is now NO validity check for reasons of distruibution.
		if (s == E_GROUP_SET:ALLOW)
		{
			Bit_Let(YSI_g_sDefaultAllowed, _:g);
			Bit_Vet(YSI_g_sDefaultDenied, _:g);
		}
		else if (s == E_GROUP_SET:DENY)
		{
			Bit_Vet(YSI_g_sDefaultAllowed, _:g);
			Bit_Let(YSI_g_sDefaultDenied, _:g);
		}
		else
		{
			Bit_Vet(YSI_g_sDefaultAllowed, _:g);
			Bit_Vet(YSI_g_sDefaultDenied, _:g);
		}
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Exclusive...</summary>
 * <param name="g">Group to add this to.</param>
 * <param name="el">Element to add.</param>
 * <remarks>
 *  Add this element to ONLY this group and remove it from any others it might
 *  already be in.  This is basically a simplified version of "GROUP_ADD".
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_Exclusive...(Group:g, _GROUP_MAKE_TAG:el);

GGLOBAL__ Group_Exclusive...(Group:g, _GROUP_MAKE_TAG:el)
{
	if (g <= GROUP_GLOBAL)
	{
		GROUP_FIX(g);
		YSI_gTempAllowed_ = YSI_g_sDefaultAllowed;
		YSI_g_sDefaultAllowed = YSI_g_cEmptyGroups;
		Bit_Let(YSI_g_sDefaultAllowed, _:g);
		for (new i = 0; i != bits<_MAX_GROUPS_G>; ++i)
		{
			YSI_g_sEmpty[i] = ~YSI_g_sDefaultAllowed[i];
		}
		_GROUP_MAKE_NAME<..._InitialiseFromGroups>(el);
		YSI_g_sDefaultAllowed = YSI_gTempAllowed_;
		YSI_g_sEmpty = YSI_g_cEmptyGroups;
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Iter_Func@Group_...</summary>
 * <param name="g">Group to iterate over.</param>
 * <remarks>
 *  Iterate over all the items in this group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Iter_Func@Group_...(start, Group:g);

GGLOBAL__ Iter_Func@Group_...(start, Group:g)
{
	P:3("Iter_Func@Group_... called: %i, %i", start, _:g);
	if (g <= GROUP_GLOBAL)
	{
		GROUP_FIX(g);
		new
			Bit:mask = Bit_Mask(_:g),
			slot = Bit_Slot(_:g);
		while (++start != _GROUP_MAKE_LIMIT)
		{
			if (YSI_g_sElementAllowed[start][slot] & mask)
			{
				return start;
			}
		}
	}
	return -1;
}

const
	F@z:_GROUP_MAKE_NAME<Iterator@Group_...> = F@z:0,
	_GROUP_MAKE_NAME<iterstart@Group_...> = -1;

/*

      ,ad8888ba,  88             88                     88  
     d8"'    `"8b 88             88                     88  
    d8'           88             88                     88  
    88            88  ,adPPYba,  88,dPPYba,  ,adPPYYba, 88  
    88      88888 88 a8"     "8a 88P'    "8a ""     `Y8 88  
    Y8,        88 88 8b       d8 88       d8 ,adPPPPP88 88  
     Y8a.    .a88 88 "8a,   ,a8" 88b,   ,a8" 88,    ,88 88  
      `"Y88888P"  88  `"YbbdP"'  8Y"Ybbd8"'  `"8bbdP"Y8 88  

*/

/*-------------------------------------------------------------------------*//**
 * <summary>Group_SetGlobal...</summary>
 * <param name="el">Element to set.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  If "s" is true, then one element is added to the global group.  False it is
 *  removed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_SetGlobal...(_GROUP_MAKE_TAG:el,E_GROUP_SET:s);

GGLOBAL__ Group_SetGlobal...(_GROUP_MAKE_TAG:el,E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...> " called: %i, %i", _:el, _:s);
	return _GROUP_MAKE_NAME<Group_Set...>(GROUP_GLOBAL, el, s);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Global...Allowed</summary>
 * <param name="g">Group to get from.</param>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the group have the element explicitly allowed?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:_GROUP_MAKE_NAME<Group_Global...Allowed>(_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_Global...Allowed> " called: %i", _:el);
	return _GROUP_MAKE_NAME<Group_...Allowed>(GROUP_GLOBAL, el);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Global...Denied</summary>
 * <param name="g">Group to get from.</param>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the group have the element explicitly denied?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:_GROUP_MAKE_NAME<Group_Global...Denied>(_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_Global...Denied> " called: %i", _:el);
	return _GROUP_MAKE_NAME<Group_...Denied>(GROUP_GLOBAL, el);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_GetGlobal...</summary>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the global group have the element?
 * </returns>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Group_Global...Allowed` or `Group_Global...Denied`.
stock E_GROUP_SET:_GROUP_MAKE_NAME<Group_GetGlobal...>(_GROUP_MAKE_TAG:el)
{
	// This returns truthy for both allowed and denied.  The function is
	// deprecated, so this is probably OK, because only people with legacy code
	// (thus not using denials) will be calling this function.
	P:2(#_GROUP_MAKE_NAME<Group_GetGlobal...> " called: %i", _:el);
	return
		_GROUP_MAKE_NAME<Group_...Denied>(GROUP_GLOBAL, el) ? E_GROUP_SET:DENY :
		_GROUP_MAKE_NAME<Group_...Allowed>(GROUP_GLOBAL, el) ? E_GROUP_SET:ALLOW :
		E_GROUP_SET:UNDEF;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_SetGlobal...Default</summary>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  If "s" is true, then all elements are added to the global group (i.e. the
 *  default is set to true and all previous settings are wiped out).  If it is
 *  false then all elements are removed and a full update is done.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_SetGlobal...Default(E_GROUP_SET:s);

GGLOBAL__ Group_SetGlobal...Default(E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...Default> " called: %i", _:s);
	return _GROUP_MAKE_NAME<Group_Set...Default>(GROUP_GLOBAL, s);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_SetGlobal...New</summary>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  All elements created FROM THIS POINT ON will have this default setting.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_SetGlobal...New(E_GROUP_SET:s);

GGLOBAL__ Group_SetGlobal...New(E_GROUP_SET:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...New> " called: %i", _:s);
	return _GROUP_MAKE_NAME<Group_Set...New>(GROUP_GLOBAL, s);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_GlobalExclusive...</summary>
 * <param name="el">Element to add.</param>
 * <remarks>
 *  Add this element to ONLY the global group and remove it from any others it
 *  might already be in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Group_GlobalExclusive...(_GROUP_MAKE_TAG:el);

GGLOBAL__ Group_GlobalExclusive...(_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_GlobalExclusive...> " called: %i", el);
	return _GROUP_MAKE_NAME<Group_Exclusive...>(GROUP_GLOBAL, el);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Iter_Func@Group_...</summary>
 * <remarks>
 *  Iterate over all the items in this group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GFOREIGN__ Iter_Func@Group_Global...(start);

GGLOBAL__ Iter_Func@Group_Global...(start)
{
	P:3("Iter_Func@Group_Global... called: %i", start);
	new
		Bit:mask = Bit_Mask(_:_MAX_GROUPS),
		slot = Bit_Slot(_:_MAX_GROUPS);
	while (++start != _GROUP_MAKE_LIMIT)
	{
		if (YSI_g_sElementAllowed[start][slot] & mask)
		{
			return start;
		}
	}
	return -1;
}

const
	F@z:_GROUP_MAKE_NAME<Iterator@Group_Global...> = F@z:0,
	_GROUP_MAKE_NAME<iterstart@Group_Global...> = -1;

#if defined GROUP_LIBRARY_TAGS
	
	stock Group:operator+(Group:g, GROUP_LIBRARY_TAGS:o)
	{
		_GROUP_MAKE_NAME<Group_Set...>(g, o, true);
		return g;
	}
	
	stock Group:operator-(Group:g, GROUP_LIBRARY_TAGS:o)
	{
		_GROUP_MAKE_NAME<Group_Set...>(g, o, false);
		return g;
	}
	
	stock Group:operator%(Group:g, GROUP_LIBRARY_TAGS:o)
	{
		_GROUP_MAKE_NAME<Group_Exclusive...>(g, o);
		return g;
	}
	
	stock bool:operator==(Group:g, GROUP_LIBRARY_TAGS:o)
	{
		return _GROUP_MAKE_NAME<Group_Get...>(g, o);
	}
	
	stock bool:operator!=(Group:g, GROUP_LIBRARY_TAGS:o)
	{
		return !_GROUP_MAKE_NAME<Group_Get...>(g, o);
	}
	
#endif

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

static stock void:Group_Handoff(i, const a[], s)
{
	s = min(s, bits<_:_MAX_GROUPS_G>);
	if (i == cellmin)
	{
		memcpy(_:YSI_g_sDefaultAllowed, a, 0, s * 4);
	}
	else if (i == cellmax)
	{
		memcpy(_:YSI_g_sDefaultDenied, a, 0, s * 4);
	}
	else if (i < 0)
	{
		memcpy(_:YSI_g_sElementDenied[~i], a, 0, s * 4);
	}
	else
	{
		memcpy(_:YSI_g_sElementAllowed[i], a, 0, s * 4);
	}
}

MASTER_FUNC__ MAKE_YCM<HANDOFF_SOURCE...Group>()<_YCM:p>
{
	// Pass data to the new group controller.
	Group_Handoff(cellmin, _:YSI_g_sDefaultAllowed, sizeof (YSI_g_sDefaultAllowed));
	Group_Handoff(cellmax, _:YSI_g_sDefaultDenied, sizeof (YSI_g_sDefaultDenied));
	for (new i = 0; i != sizeof (YSI_g_sElementAllowed); ++i)
	{
		Group_Handoff(i, _:YSI_g_sElementAllowed[i], sizeof (YSI_g_sElementAllowed[]));
		Group_Handoff(~i, _:YSI_g_sElementDenied[i], sizeof (YSI_g_sElementDenied[]));
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * <param name="el">Element to show or hide.</param>
 * <param name="previousAllowed">(p) The old allowed groups.</param>
 * <param name="currentAllowed">(c) The new allowed groups.</param>
 * <param name="previousDenied">(q) The old denied groups.</param>
 * <param name="currentDenied">(d) The new denied groups.</param>
 * <param name="reference">(r) What to compare changes to.</param>
 * <remarks>
 *  I did have a good reason for calling this "FU", but I forgot it!  Anyway,
 *  the state of some groups has changed - either a player's groups or an
 *  elements groups have changed.  If the player could previously see the
 *  element but now can't, hide it.  If the player previously couldn't see it
 *  but now can, show it.  If there is no change do nothing.  The old version of
 *  this library would just re-show the element even if they could already see
 *  it, but this was a bad design as it could incur large overheads in other
 *  libraries when they had to do IO to enable or disable something for a
 *  player.
 *
 *  The change can be in either the player's groups or the element's groups,
 *  either way this code will work regardless.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Group_FullPlayerUpdate(playerid, el, const Bit:p[], const Bit:c[], const Bit:q[], const Bit:d[], const Bit:r[])
{
	// "_GROUPS_CHECK" is a macro that expands to a massive unrolled "if"
	// statement checking up to 512 groups at once.  Any more than that and this
	// code resorts to a loop instead.  I say "at once"; it does 32 AT ONCE
	// (as in truly in parallel), starting with the most likely match (the
	// default group that every player and every element is usually in), and
	// loops over all the groups in 32 group chunks.  When I say "loop", this
	// could be in the form of a huge "if" statement with every iteration put in
	// explicitly.
	// r = Reference (valid groups).
	// c = Current (new groups).
	// p = Previous (old groups).
	#if _DEBUG >= 7
		new debugA[] = "false", debugB[] = "false";
		_GROUPS_CHECK_ANY(p,r)
			debugA = "true";
		_GROUPS_CHECK_ANY(c,r)
			debugB = "true";
		printf("Group_FullPlayerUpdate ("#_GROUP_MAKE_NAME<...>") called:\r\n\t%d, %d,\r\n\t%s,\r\n\t%s,\r\n\t%s,\r\n\t%s, %s",
			playerid, el, Bit_Display(p, bits<_MAX_GROUPS_G>), Bit_Display(c, bits<_MAX_GROUPS_G>), Bit_Display(r, bits<_MAX_GROUPS_G>), debugA, debugB);
	#endif
	_GROUPS_CHECK_ANY(q,r)
	{
		// Were previously denied.
		_GROUPS_CHECK_ANY(d,r)
		{
			// Still denied.
			P:7("Group_FullPlayerUpdate: %d %d denied, still are", playerid, el);
			return;
		}
		// They were previously denied, but now they aren't.  Does that mean
		// then can now see it?
		_GROUPS_CHECK_ANY(c,r)
		{
			P:7("Group_FullPlayerUpdate: %d %d denied, now can", playerid, el);
			_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, true);
			return;
		}
		P:7("Group_FullPlayerUpdate: %d %d denied, now not", playerid, el);
		return;
	}
	// Were not previously denied.  Are they now?
	_GROUPS_CHECK_ANY(d,r)
	{
		_GROUPS_CHECK_ANY(p,r)
		{
			// Now denied.
			P:7("Group_FullPlayerUpdate: %d %d allowed, now cant't", playerid, el);
			_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, false);
			return;
		}
		P:7("Group_FullPlayerUpdate: %d %d allowed, now aren't", playerid, el);
		return;
	}
	// No denies in force.  Check normal allows.
	_GROUPS_CHECK_ANY(p,r)
	{
		// Could previously see this thing.  The thing about this design is that
		// it can (best case) take just 2 comparisons to end - and that should
		// be the common case!
		_GROUPS_CHECK_ANY(c,r)
		{
			// Still can.
			P:7("Group_FullPlayerUpdate: %d %d could, still can", playerid, el);
			return;
		}
		// Now can't.
		P:7("Group_FullPlayerUpdate: %d %d could, now can't", playerid, el);
		_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, false);
		return;
	}
	// Couldn't see it before.
	_GROUPS_CHECK_ANY(c,r)
	{
		P:7("Group_FullPlayerUpdate: %d %d now can", playerid, el);
		// They have whatever this thing is.  Note that this may be called
		// MULTIPLE times for an element, without anything actually changing.
		// I.e. this could be set to "true" repeatedly while never being set
		// to "false".
		_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, true);
		// We use "return" here because "_GROUPS_CHECK_ANY" MAY be a loop.
		return;
	}
	P:7("Group_FullPlayerUpdate: %d %d can't", playerid, el);
}

/*

      ,ad8888ba,  88                     88                        
     d8"'    `"8b 88                     ""                        
    d8'           88                                               
    88            88,dPPYba,  ,adPPYYba, 88 8b,dPPYba,  ,adPPYba,  
    88            88P'    "8a ""     `Y8 88 88P'   `"8a I8[    ""  
    Y8,           88       88 ,adPPPPP88 88 88       88  `"Y8ba,   
     Y8a.    .a8P 88       88 88,    ,88 88 88       88 aa    ]8I  
      `"Y8888Y"'  88       88 `"8bbdP"Y8 88 88       88 `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="ni">Next init function variable as returned by y_amx.</param>
 * <param name="na">Next add function variable as returned by y_amx.</param>
 * <param name="nu">Next update function variable as returned by y_amx.</param>
 * <remarks>
 *  This function is called when the group system first starts up to initialise
 *  the global group and all the various function pointers.  The way the
 *  "GCHAIN__" macro works means that the fact that "ni" etc are references is
 *  irrelevant; however, it does make the code LOOK much nicer and like
 *  assigning to the variables does have some wider meaning.
 *
 *  If this is called with "ni = -1", it is special code to temporarily set or
 *  restore the defaults for use with the "GROUP_ADD" macro.  So basically, it
 *  is poor design giving two distinct uses to a single function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GCHAIN__ _yGI(&ni, &na, &nu)
{
	P:2(#_GROUP_MAKE_NAME<_yGI...> " called: %i, %i, %i", ni, na, nu);
	if (ni == -1)
	{
		P:4(#_GROUP_MAKE_NAME<_yGI...> " INIT");
		static
			BitArray:sAllowed<_MAX_GROUPS_G>,
			BitArray:sDenied<_MAX_GROUPS_G>;
		if (na)
		{
			// Called to "push" the default settings.
			sAllowed = YSI_g_sDefaultAllowed;
			sDenied = YSI_g_sDefaultDenied;
			YSI_g_sDefaultAllowed = YSI_g_cEmptyGroups;
			YSI_g_sDefaultDenied = YSI_g_cEmptyGroups;
			Bit_Let(YSI_g_sDefaultAllowed, nu);
			for (new i = 0; i != bits<_MAX_GROUPS_G>; ++i)
			{
				YSI_g_sEmpty[i] = ~YSI_g_sDefaultAllowed[i];
			}
		}
		else
		{
			// Called to "pop" the default settings.
			YSI_g_sDefaultAllowed = sAllowed;
			YSI_g_sDefaultDenied = sDenied;
			YSI_g_sEmpty = YSI_g_cEmptyGroups;
		}
	}
	else
	{
		P:4(#_GROUP_MAKE_NAME<_yGI...> " SETUP");
		// Enable the default group.  If I'm right, this way is actually better than
		// using variables as in most cases because "_MAX_GROUPS" is a constant so
		// all the other maths will be constant.
		Bit_Let(YSI_g_sDefaultAllowed, _MAX_GROUPS);
		// Set up the function chaining.
		new
			x = 0;
		ni = AMX_GetPublicPointerPrefix(ni, x, _A<_yGI>);
		_yGI = x;
		na = AMX_GetPublicPointerPrefix(na, x, _A<_yGA>);
		_yGA = x;
		nu = AMX_GetPublicPointerPrefix(nu, x, _A<_yGU>);
		_yGU = x;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="group">The group that was just created.</param>
 * <remarks>
 *  The given group was just created, loop over all elements and make sure they
 *  are NOT in this group - only the global group has a "default default" of
 *  true.  We don't need to update any players with this as no-one will ever be
 *  in a brand new group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GCHAIN__ _yGA(&group)
{
	P:4(#_GROUP_MAKE_NAME<_yGA...> " called: %i", _:group);
	// Adding a new group is now a lot harder than it was before, but on the
	// other hand, adding and using elements is vastly simpler so that's OK.
	new
		s = Bit_Slot(group),
		Bit:m = ~Bit_Mask(group);
	// Set the default "contains" for this group to false.
	YSI_g_sDefaultAllowed[s] &= m;
	YSI_g_sDefaultDenied[s] &= m;
	// Disable every element in this group.  DOESN'T use "YSI_g_sMaxEncountered"
	// because we need to set up for the future too.
	for (new i = 0; i != _GROUP_MAKE_LIMIT; ++i)
	{
		YSI_g_sElementAllowed[i][s] &= m;
		YSI_g_sElementDenied[i][s] &= m;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="pid">The player who joined or left groups.</param>
 * <param name="p">Their previous groups.</param>
 * <param name="c">Their new groups.</param>
 * <remarks>
 *  The player "pid" just joined or left a group (or groups - can do multiple).
 *  Update their visibility accordingly.  This function is ONLY called if there
 *  is a CHANGE - earlier functions confirm that they weren't already in (or
 *  not) this group(s) before the call.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GCHAIN__ _yGU(&pid, Bit:p[], Bit:c[])
{
	P:4(#_GROUP_MAKE_NAME<_yGU...> " called: %i, %s, %s", pid, Bit_Display(p, bits<_MAX_GROUPS_G>), Bit_Display(c, bits<_MAX_GROUPS_G>));
	// This code loops over every "thing" controlled by this script.  For every
	// one it checks to see if the player can or can't see something that they
	// previously could or couldn't see.  If their ability to see it has
	// changed then the `..._SetPlayer` function in the controlling library is
	// called to do the actual internal function of updating their state.
	for (new el = 0; el <= YSI_g_sMaxEncountered; ++el)
	{
		Group_PartPlayerUpdate(pid, el, p, c, YSI_g_sElementAllowed[el], YSI_g_sElementDenied[el]);
	}
}

static stock Group_PartPlayerUpdate(playerid, el, const Bit:p[], const Bit:c[], const Bit:a[], const Bit:d[])
{
	// p = Previous
	// c = Current
	// a = Allowed
	// d = Denied
	P:4("Group_PartPlayerUpdate called: %d %d\n    %s\n    %s\n    %s\n    %s", playerid, el, Bit_Display(p, bits<_MAX_GROUPS_G>), Bit_Display(c, bits<_MAX_GROUPS_G>), Bit_Display(a, bits<_MAX_GROUPS_G>), Bit_Display(d, bits<_MAX_GROUPS_G>));
	_GROUPS_CHECK_ANY(p,d)
	{
		P:6("Group_PartPlayerUpdate: Previously Denied.");
		// Any previous denials.
		_GROUPS_CHECK_ANY(c,d)
		{
			P:6("Group_PartPlayerUpdate: Currently Denied.");
			// No change there.
			return;
		}
		_GROUPS_CHECK_ANY(c,a)
		{
			P:6("Group_PartPlayerUpdate: Currently Allowed.");
			// Now allowed.
			_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, true);
			return;
		}
		return;
	}
	_GROUPS_CHECK_ANY(c,d)
	{
		P:6("Group_PartPlayerUpdate: Currently Denied.");
		_GROUPS_CHECK_ANY(p,a)
		{
			P:6("Group_PartPlayerUpdate: Previously Allowed.");
			// Previously allowed, now denied.
			_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, false);
			return;
		}
		P:6("Group_PartPlayerUpdate: Previously Nothing.");
		return;
	}
	_GROUPS_CHECK_ANY(p,a)
	{
		P:6("Group_PartPlayerUpdate: Previously Allowed.");
		_GROUPS_CHECK_ANY(c,a)
		{
			P:6("Group_PartPlayerUpdate: Currently Allowed.");
			return;
		}
		P:6("Group_PartPlayerUpdate: Currently Nothing.");
		// Were allowed, now aren't.
		_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, false);
		return;
	}
	_GROUPS_CHECK_ANY(c,a)
	{
		P:6("Group_PartPlayerUpdate: Currently Allowed.");
		// Currently allowed.
		_GROUP_MAKE_NAME<..._SetPlayer>(_GROUP_MAKE_TAG:el, playerid, true);
		return;
	}
	P:6("Group_PartPlayerUpdate: Currently Nothing.");
}

/*

      ,ad8888ba,  88                                                            
     d8"'    `"8b 88                                                            
    d8'           88                                                            
    88            88  ,adPPYba, ,adPPYYba, 8b,dPPYba,  88       88 8b,dPPYba,   
    88            88 a8P_____88 ""     `Y8 88P'   `"8a 88       88 88P'    "8a  
    Y8,           88 8PP""""""" ,adPPPPP88 88       88 88       88 88       d8  
     Y8a.    .a8P 88 "8b,   ,aa 88,    ,88 88       88 "8a,   ,a88 88b,   ,a8"  
      `"Y8888Y"'  88  `"Ybbd8"' `"8bbdP"Y8 88       88  `"YbbdP'Y8 88`YbbdP"'   
                                                                   88           
                                                                   88           

*/

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Calls all functions to correctly include them in the AMX when required.
 *  Also all variables as it turns out they were a problem too.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#undef GCHAIN__

#undef _GROUP_MAKE_NAME
#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_TAG

