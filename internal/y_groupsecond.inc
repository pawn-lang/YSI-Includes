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
	2.0
Changelog:
	21/10/12:
		Added Group_Get... functions.
	20/10/12:
		Pretty much a ground-up API-compatible rewrite.  Shorter and reliabler.
	29/11/10:
		First version
\*----------------------------------------------------------------------------*/

#undef _inc_y_groupsecond

// This code, having been updated to use the later version of y_hooks,
// unfortunately no longer has one function spread between two files, which was
// a very unique (required) code feature.  However this version should be better
// overall (at least slightly).
//#include "..\y_hooks"

// This file contains generic code for setting all the stats to do with a single
// element type.  Groups can be defined for any element (classes, objects etc)
// and each one will specialise this file to give different functions.

#if !defined _GROUP_MAKE_NAME
	#error Please define _GROUP_MAKE_NAME before including y_groups.
#endif

#if !defined _GROUP_MAKE_LIMIT
	#error Please define _GROUP_MAKE_LIMIT before including y_groups.
#endif

#if !defined _GROUP_MAKE_TAG
	#define _GROUP_MAKE_TAG _
#endif

// Start of the multi-use file.
static stock
	BitArray:_GROUP_GROUP_NAME[_GROUP_MAKE_LIMIT]<_:_MAX_GROUPS_G>,
	BitArray:_GROUP_DEFAULTS<_:_MAX_GROUPS_G>,
	BitArray:YSI_g_sEmpty<_:_MAX_GROUPS_G>,
	_yGI,
	_yGU,
	_yGA;

// Define the callback chaining for the current 
#if YSIM_HAS_MASTER
	#if _YSIM_IS_CLIENT
		#define _gchain%0(%2) stock _GROUP_MAKE_NAME<%0...>(%2)
		
		// Should never be needed.
		#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<_Error_..._Client_Set>
	#else
		#if _YSIM_IS_SERVER
			#define _gchain%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2);for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
			#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<..._SetPlayer>
		#else
			#if _YSIM_IS_STUB
				#define _gchain%0(%2) stock _GROUP_MAKE_NAME<%0...>(%2)
				
				// Because of the interaction between the various things that
				// the groups and master systems this will NEVER be called in a
				// stub script - and if it is we now get a nice compile-time
				// error telling us so!  It may, however, prove difficult to
				// trace!
				#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<_Error_..._Stub_Set>
			#else
				#define _gchain%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2)<>GROUP_CHAIN?<%0>(%2);public _GROUP_MAKE_NAME<%0...>(%2)<_YCM:y>for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
				
				#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<..._SetPlayer>
			#endif
		#endif
	#endif
#else
	#define _gchain%0(%2) _GROUP_MAKE_NAME<%0...>(%2);public _GROUP_MAKE_NAME<%0...>(%2);for(J@=1;J@;GROUP_CHAIN?<%0>(%2))
	
	#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<..._SetPlayer>
#endif

/*----------------------------------------------------------------------------*\
Function:
	Group_FU
Params:
	playerid - Player to check.
	el - Element to show or hide.
	previous - The old state of affairs.
	current - The new state of affairs.
	reference - What to compare changes to.
Return:
	-
Notes:
	I did have a good reason for calling this "FU", but I forgot it!  Anyway,
	the state of some groups has changed - either a player's groups or an
	elements groups have changed.  If the player could previously see the
	element but now can't, hide it.  If the player previously couldn't see it
	but now can, show it.  If there is no change do nothing.  The old version of
	this library would just re-show the element even if they could already see
	it, but this was a bad design as it could incur large overheads in other
	libraries when they had to do IO to enable or disable something for a
	player.
	
	The change can be in either the player's groups or the element's groups,
	either way this code will work regardless.
	
	Oh yeah, "FU" means "Full Update".
\*----------------------------------------------------------------------------*/

static stock Group_FU(playerid, el, Bit:previous[], Bit:current[], Bit:reference[])
{
	// "_GROUPS_CHECK" is a macro that expands to a massive unrolled "if"
	// statement checking up to 512 groups at once.  Any more than that and this
	// code resorts to a loop instead.  I say "at once"; it does 32 AT ONCE
	// (as in truly in parallel), starting with the most likely match (the
	// default group that every player and every element is usually in), and
	// loops over all the groups in 32 group chunks.  When I say "loop", this
	// could be in the form of a huge "if" statement with every iteration put in
	// explicitly.
	// nr = NOT REFERENCE
	// ar = ALOW REFERENCE
	// cur = NEW SETTINGS
	// pre = PREVIOUS SETTINGS
	/*if (Bit_Get(gNotDat, el))
	{
		if (Bit_Get(gAndDat, el))
		{
			_GROUPS_CHECK_IN(ar, cur)
			{
				_GROUPS_CHECK_NONE(nr, cur)
				{
					_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
					return;
				}
			}
			// SHOULD IT BE REMOVED?
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
				return;
			}
		}
		else
		{
			_GROUPS_CHECK_ANY(ar, cur)
			{
				_GROUPS_CHECK_NONE(nr, cur)
				{
					_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
					return;
				}
			}
			// SHOULD IT BE REMOVED?
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
				return;
			}
		}
	}
	else
	{
		if (Bit_Get(gAndDat, el))
		{
			_GROUPS_CHECK_IN(ar, cur)
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
				return;
			}
			// SHOULD IT BE REMOVED?
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
				return;
			}
		}
		else
		{
			_GROUPS_CHECK_ANY(ar, cur)
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
				return;
			}
			// SHOULD IT BE REMOVED?
			{
				_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
				return;
			}
		}
	}*/
	/*_GROUPS_CHECK_ALL(nr, ar)
	{
		_GROUPS_CHECK_IN(ar, cur)
		{
			_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
			return;
		}
		_GROUPS_CHECK_IN(ar, pre)
		{
			_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
			return;
		}
		return;
	}
	_GROUPS_CHECK_ANY(ar, cur)
	{
		_GROUPS_CHECK_NONE(nr, cur)
		{
			_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
			return;
		}
	}
	_GROUPS_CHECK_IN(ar, pre)
	{
		_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
		return;
	}*/
	_GROUPS_CHECK_ANY(previous, reference)
	{
		// Could previously see this thing.  The thing about this design is that
		// it can (best case) take just 2 comparisons to end - and that should
		// be the common case!
		_GROUPS_CHECK_ANY(current, reference)
		{
			// Still can.
			return;
		}
		// Now can't.
		_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, false);
		return;
	}
	// Couldn't see it before.
	_GROUPS_CHECK_ANY(current, reference)
	{
		// They have whatever this thing is.  Note that this may be called
		// MULTIPLE times for an element, without anything actually changing.
		// I.e. this could be set to "true" repeatedly while never being set
		// to "false".
		_GROUP_SET_PLAYER(_GROUP_MAKE_TAG:el, playerid, true);
		// We use "return" here because "_GROUPS_CHECK_ANY" MAY be a loop.
		return;
	}
}

/*----------------------------------------------------------------------------*\
Function:
	_yGI
Params:
	&ni - Next init function variable as returned by y_amx.
	&na - Next add function variable as returned by y_amx.
	&nu - Next update function variable as returned by y_amx.
Return:
	-
Notes:
	This function is called when the group system first starts up to initialise
	the global group and all the various function pointers.  The way the
	"_gchain" macro works means that the fact that "ni" etc are references is
	irrelevant; however, it does make the code LOOK much nicer and like
	assigning to the variables does have some wider meaning.
	
	If this is called with "ni = -1", it is special code to temporarilly set or
	restore the defaults for use with the "GROUP_ADD" macro.
\*----------------------------------------------------------------------------*/

_gchain _yGI(&ni, &na, &nu)
{
	if (ni == -1)
	{
		static
			BitArray:sStack<_MAX_GROUPS_G>;
		if (na)
		{
			//printf("PUSH %d", nu);
			// Called to "push" the default settings.
			sStack = _GROUP_DEFAULTS;
			//printf("ONE %d", nu);
			_GROUP_DEFAULTS = YSI_g_cEmptyGroups;
			//printf("TWO %d", nu);
			Bit_Let(_GROUP_DEFAULTS, nu);
			//printf("THREE %d", nu);
			for (new i = 0; i != bits<_MAX_GROUPS_G>; ++i)
			{
				YSI_g_sEmpty[i] = ~_GROUP_DEFAULTS[i];
			}
			//printf("DONE %d", nu);
		}
		else
		{
			//printf("POP");
			// Called to "pop" the default settings.
			_GROUP_DEFAULTS = sStack;
			YSI_g_sEmpty = YSI_g_cEmptyGroups;
		}
	}
	else
	{
		P:4(#_GROUP_MAKE_NAME<_yGI...> " called: %i, %i, %i", ni, na, nu);
		// Enable the default group.  If I'm right, this way is actually better than
		// using variables as in most cases because "_MAX_GROUPS" is a constant so
		// all the other maths will be constant.
		Bit_Let(_GROUP_DEFAULTS, _MAX_GROUPS);
		// Don't need this loop anymore, it is done for every element individually.
		//for (new i = 0; i != _GROUP_MAKE_LIMIT; ++i)
		//{
		//	// Basically, enable everything in the default group.
		//	Bit_Let(_GROUP_GROUP_NAME[i], _MAX_GROUPS);
		//}
		// Set up the function chaining.
		ni = AMX_GetPublicPointerPrefix(ni, _yGI, _A<_yGI>);
		na = AMX_GetPublicPointerPrefix(na, _yGA, _A<_yGA>);
		nu = AMX_GetPublicPointerPrefix(nu, _yGU, _A<_yGU>);
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Exclusive...
Params:
	Group:g - Group to add this to.
	_GROUP_MAKE_TAG:el - Element to add.
Return:
	-
Notes:
	Add this element to ONLY this group and remove it from any others it might
	already be in.  This is basically a simplified version of "GROUP_ADD".
\*----------------------------------------------------------------------------*/

gforeign Group_Exclusive...(Group:g,_GROUP_MAKE_TAG:el);

gglobal Group_Exclusive...(Group:g,_GROUP_MAKE_TAG:el)
{
	if (GROUP_MASK <= g <= GROUP_GLOBAL)
	{
		GROUP_FIX(g);
		YSI_gTempGroups = _GROUP_DEFAULTS;
		_GROUP_DEFAULTS = YSI_g_cEmptyGroups;
		Bit_Let(_GROUP_DEFAULTS, _:g);
		for (new i = 0; i != bits<_MAX_GROUPS_G>; ++i)
		{
			YSI_g_sEmpty[i] = ~_GROUP_DEFAULTS[i];
		}
		_GROUP_INITIALISE(el);
		_GROUP_DEFAULTS = YSI_gTempGroups;
		YSI_g_sEmpty = YSI_g_cEmptyGroups;
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	_yGA
Params:
	&group - The group that was just created.
Return:
	-
Notes:
	The given group was just created, loop over all elements and make sure they
	are NOT in this group - only the global group has a "default default" of
	true.  We don't need to update any players with this as no-one will ever be
	in a brand new group.
\*----------------------------------------------------------------------------*/

_gchain _yGA(&group)
{
	P:4(#_GROUP_MAKE_NAME<_yGA...> " called: %i", _:group);
	// Adding a new group is now a lot harder than it was before, but on the
	// other hand, adding and using elements is vastly simpler so that's OK.
	new
		s = Bit_Slot(group),
		Bit:m = ~Bit_Mask(group);
	// Set the default "contains" for this group to false.
	_GROUP_DEFAULTS[s] &= m;
	// Disable every element in this group.
	for (new i = 0; i != _GROUP_MAKE_LIMIT; ++i)
	{
		_GROUP_GROUP_NAME[i][s] &= m;
	}
}

/*----------------------------------------------------------------------------*\
Function:
	_yGU
Params:
	&pid - The player who joined or left groups.
	Bit:p[] - Their previous groups.
	Bit:c[] - Their new groups.
Return:
	-
Notes:
	The player "pid" just joined or left a group (or groups - can do multiple).
	Update their visibility accordingly.  This function is ONLY called if there
	is a CHANGE - earlier functions confirm that they weren't already in (or
	not) this group(s) before the call.
\*----------------------------------------------------------------------------*/

_gchain _yGU(&pid, Bit:p[], Bit:c[])
{
	P:4(#_GROUP_MAKE_NAME<_yGU...> " called: %i, %s, %s", pid, Bit_Display(p, bits<_MAX_GROUPS_G>), Bit_Display(c, bits<_MAX_GROUPS_G>));
	// This code loops over every "thing" controlled by this script.  For every
	// one it checks to see if the player can or can't see something that they
	// previously could or couldn't see.  If their ability to see it has
	// changed then the "_GROUP_SET_PLAYER" function in the controlling library
	// is called to do the actual internal function of updating their state.
	for (new el = 0; el != _GROUP_MAKE_LIMIT; ++el)
	{
		Group_FU(pid, el, p, c, _GROUP_GROUP_NAME[el]);
	}
}

/*----------------------------------------------------------------------------*\
Function:
	_GROUP_INITIALISE
Params:
	x - The element that was added (maybe).
	s - Was the element added or removed?
Return:
	-
Notes:
	The name is a macro, so this function isn't actually called this.  This is
	called when a new element is created, and as such it is NOT chained to other
	parts of the groups system because each part handles one type of element.
	Loop through all players and set up the element for them if they are in a
	group that this is also in by default.
	
	If x is "_GROUP_MAKE_LIMIT" then this is the test used in OnPlayerConnect in
	various libraries to see if the groups system exists, and if not locally
	initialise the player instead of leaving it up to this system.
\*----------------------------------------------------------------------------*/

#if !defined _YSI_GROUPS_FIRST_HALF
	forward bool:_GROUP_INITIALISE(_GROUP_MAKE_TAG:x = _GROUP_MAKE_TAG:_GROUP_MAKE_LIMIT);
#endif

stock bool:_GROUP_INITIALISE(_GROUP_MAKE_TAG:x = _GROUP_MAKE_TAG:_GROUP_MAKE_LIMIT) <YSI_has_groups:y>
{
	P:4(#_GROUP_INITIALISE " called: %i", x);
	// A new item has been added to the system - update all players according to
	// the default settings for a group.
	if (x != _GROUP_MAKE_TAG:_GROUP_MAKE_LIMIT)
	{
		//static
		//	BitArray:sEmpty<_MAX_GROUPS_G>;
		//printf("%d %s %s", _:x, Bit_Display(_GROUP_DEFAULTS), Bit_Display(YSI_g_sEmpty));
		_GROUP_GROUP_NAME[_:x] = _GROUP_DEFAULTS;
		foreach (new playerid : Player)
		{
			// Uses "YSI_g_sEmpty" instead of a truly blank variable so that we
			// can ensure that NO other groups have this element when we use the
			// "GROUP_ADD" macro.
			Group_FU(playerid, _:x, YSI_g_sEmpty, _GROUP_DEFAULTS, YSI_gGroupPlayers[playerid]);
		}
	}
	return true;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Set...Default
Params:
	Group:g - Group to set for.
	bool:s - Set or unset?
Return:
	-
Notes:
	If "s" is true, then all elements are added to this group (i.e. the default
	is set to true and all previous settings are wiped out).  If it is false
	then all elements are removed and a full update is done.
\*----------------------------------------------------------------------------*/

gforeign Group_Set...Default(Group:g,bool:s);

gglobal Group_Set...Default(Group:g,bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...Default> " called: %i, %i", _:g, s);
	if (GROUP_MASK <= g <= GROUP_GLOBAL)
	{
		// There is now NO validity check for reasons of distruibution.
		GROUP_FIX(g);
		new
			slot = Bit_Slot(g),
			Bit:mask = Bit_Mask(g),
			Iterator:GP<MAX_PLAYERS>;
		foreach (new playerid : Player)
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
		static
			BitArray:sNext<_MAX_GROUPS_G>;
		if (s)
		{
			Bit_Let(_GROUP_DEFAULTS, _:g);
			for (new el = 0; el != _GROUP_MAKE_LIMIT; ++el)
			{
				sNext = _GROUP_GROUP_NAME[el];
				if (sNext[slot] & mask)
				{
					continue;
				}
				// Is this element NOT in the current group?
				Bit_Let(sNext, _:g);
				foreach (new playerid : GP)
				{
					Group_FU(playerid, el, _GROUP_GROUP_NAME[el], sNext, YSI_gGroupPlayers[playerid]);
				}
				_GROUP_GROUP_NAME[el] = sNext;
			}
		}
		else
		{
			Bit_Vet(_GROUP_DEFAULTS, _:g);
			for (new el = 0; el != _GROUP_MAKE_LIMIT; ++el)
			{
				sNext = _GROUP_GROUP_NAME[el];
				if (!(sNext[slot] & mask))
				{
					continue;
				}
				// Is this element in the current group?
				Bit_Vet(sNext, _:g);
				foreach (new playerid : GP)
				{
					Group_FU(playerid, el, _GROUP_GROUP_NAME[el], sNext, YSI_gGroupPlayers[playerid]);
				}
				_GROUP_GROUP_NAME[el] = sNext;
			}
		}
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGlobal...Default
Params:
	bool:s - Set or unset?
Return:
	-
Notes:
	If "s" is true, then all elements are added to the global group (i.e. the
	default is set to true and all previous settings are wiped out).  If it is
	false then all elements are removed and a full update is done.
\*----------------------------------------------------------------------------*/

gforeign Group_SetGlobal...Default(bool:s);

gglobal Group_SetGlobal...Default(bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...Default> " called: %i", s);
	return _GROUP_MAKE_NAME<Group_Set...Default>(GROUP_GLOBAL, s);
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Set...New
Params:
	Group:g - Group to set for.
	bool:s - Set or unset?
Return:
	-
Notes:
	Similar to "Group_Set...Default", but doesn't reset all existing elements,
	just sets the permissions for any future items.
\*----------------------------------------------------------------------------*/

gforeign Group_Set...New(Group:g,bool:s);

gglobal Group_Set...New(Group:g,bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...New> " called: %i, %i", _:g, s);
	if (GROUP_MASK <= g <= GROUP_GLOBAL)
	{
		// There is now NO validity check for reasons of distruibution.
		Bit_Set(_GROUP_DEFAULTS, _:GROUP_TEMP_FIX(g), s);
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGlobal...New
Params:
	bool:s - Set or unset?
Return:
	-
Notes:
	All elements created FROM THIS POINT ON will have this default setting.
\*----------------------------------------------------------------------------*/

gforeign Group_SetGlobal...New(bool:s);

gglobal Group_SetGlobal...New(bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...New> " called: %i", s);
	return _GROUP_MAKE_NAME<Group_Set...New>(GROUP_GLOBAL, s);
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Set...
Params:
	Group:g - Group to set for.
	el - Element to set.
	bool:s - Set or unset?
Return:
	-
Notes:
	If "s" is true, then one element is added to the current group.  False it is
	removed.
\*----------------------------------------------------------------------------*/

gforeign Group_Set...(Group:g,_GROUP_MAKE_TAG:el,bool:s);

gglobal Group_Set...(Group:g,_GROUP_MAKE_TAG:el,bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_Set...> " called: %i, %i, %i", _:g, _:el, s);
	// Set wether a group can use this item.
	if (0 <= _:el < _GROUP_MAKE_LIMIT && GROUP_MASK <= g <= GROUP_GLOBAL)
	{
		// There is now NO validity check for reasons of distruibution.
		GROUP_FIX(g);
		new
			slot = Bit_Slot(g),
			Bit:mask = Bit_Mask(g);
		//static
		//	BitArray:sNext<_MAX_GROUPS_G>;
		if (s)
		{
			YSI_gTempGroups = _GROUP_GROUP_NAME[_:el];
			if (YSI_gTempGroups[slot] & mask)
			{
				// No point adding an element to a group that it is already in.
				return 1;
			}
			// Is this element NOT in the current group?
			Bit_Let(YSI_gTempGroups, _:g);
		}
		else
		{
			YSI_gTempGroups = _GROUP_GROUP_NAME[_:el];
			if (!(YSI_gTempGroups[slot] & mask))
			{
				return 1;
			}
			// Is this element in the current group?
			Bit_Vet(YSI_gTempGroups, _:g);
		}
		foreach (new playerid : Player)
		{
			if (YSI_gGroupPlayers[playerid][slot] & mask)
			{
				// The player is in the group in question, so they need a full
				// update.
				Group_FU(playerid, _:el, _GROUP_GROUP_NAME[_:el], YSI_gTempGroups, YSI_gGroupPlayers[playerid]);
			}
		}
		_GROUP_GROUP_NAME[_:el] = YSI_gTempGroups;
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGlobal...
Params:
	el - Element to set.
	bool:s - Set or unset?
Return:
	-
Notes:
	If "s" is true, then one element is added to the global group.  False it is
	removed.
\*----------------------------------------------------------------------------*/

gforeign Group_SetGlobal...(_GROUP_MAKE_TAG:el,bool:s);

gglobal Group_SetGlobal...(_GROUP_MAKE_TAG:el,bool:s)
{
	P:2(#_GROUP_MAKE_NAME<Group_SetGlobal...> " called: %i, %i", _:el, s);
	return _GROUP_MAKE_NAME<Group_Set...>(GROUP_GLOBAL, el, s);
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Get...
Params:
	Group:g - Group to get from.
	el - Element to get.
Return:
	bool: Does the group have the element?
Notes:
	-
\*----------------------------------------------------------------------------*/

gforeign bool:Group_Get...(Group:g,_GROUP_MAKE_TAG:el);

gglobal bool:Group_Get...(Group:g,_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_Get...> " called: %i, %i", _:g, _:el);
	return (0 <= _:el < _GROUP_MAKE_LIMIT && GROUP_MASK <= g <= GROUP_GLOBAL && Bit_Get(_GROUP_GROUP_NAME[_:el], _:GROUP_TEMP_FIX(g)));
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetGlobal...
Params:
	el - Element to get.
Return:
	bool: Does the global group have the element?
Notes:
	-
\*----------------------------------------------------------------------------*/

gforeign Group_GetGlobal...(_GROUP_MAKE_TAG:el);

gglobal Group_GetGlobal...(_GROUP_MAKE_TAG:el)
{
	P:2(#_GROUP_MAKE_NAME<Group_GetGlobal...> " called: %i", _:el);
	return _GROUP_MAKE_NAME<Group_Get...>(GROUP_GLOBAL, el);
}

#undef _GROUP_MAKE_TAG
#undef _gchain
#undef _GROUP_SET_PLAYER
