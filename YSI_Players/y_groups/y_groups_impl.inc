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

/*-------------------------------------------------------------------------*//**
 * <param name="%9">Check if the function exists?</param>
 * <param name="%0">Variable holding the function.</param>
 * <param name="%1">Parameters.</param>
 * <remarks>
 *  Calls the correct function to chain a function with the given number of
 *  parameters, calls the function stored in a variable and passes parameters
 *  BY REFERENCE - ALL of them!
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*
New groups check:

if (ALL A == ALL B)
{
	if (ALL A == P)
	{
		// Add.
	}
	else
	{
		// Remove.
	}
}
else
{
	if (ANY A == P && NO B == P)
	{
		// Add.
	}
	else
	{
		// Remove.
	}
}
*/

enum e_GROUP_FLAGS:(<<= 1)
{
	e_GROUP_FLAGS_NONE = 0,
	e_GROUP_FLAGS_GANG = 1,
	// I can't remember why I had this!
	//e_GROUP_FLAGS_CHAT,
	e_GROUP_FLAGS_ACTIVE,
	// Only ever set for one group.
	e_GROUP_FLAGS_GLOBAL,
	// Has no name.
	e_GROUP_FLAGS_TEMP,
	e_GROUP_FLAGS_COLOR = 0xFFFFFF00
}

enum E_GROUP_DATA
{
	E_GROUP_DATA_NAME[MAX_GROUP_NAME char],
	//E_GROUP_DATA_COUNT,
	E_GROUP_DATA_HASH,
	e_GROUP_FLAGS:E_GROUP_DATA_FLAGS,
}

stock PlayerGroups(a, b)
{
	return 0;
}

// Define the groups iterator in terms of the underlying bits, but without the
// need for users to know about the "YSI_gGroupPlayers" array, just the player.
#define Iter_Func@PlayerGroups(%1,%0) GROUP_MANGLE(Iter_Func@Bits(_:%1,YSI_gGroupPlayers[%0]))
#define Iterator@PlayerGroups Iterator@Bits

static
	// Function pointers for chaining.
	YSI_g_sNextInitFunc = 0,
	YSI_g_sNextUpdFunc = 0,
	YSI_g_sNextAddFunc = 0,
	YSI_g_sGroupCount = 0;

static stock const
	YSI_g_scGlobalName[] = "__GLOBAL",
	BitArray:RG@<_MAX_GROUPS_G>;

MASTER_DATA<_MAX_GROUPS_G>

static stock __declspec(dist_master) YSI_gGroupData[_MAX_GROUPS_G][E_GROUP_DATA];
static stock __declspec(dist_tagged) Bit:YSI_g_sChildGroups[_MAX_GROUPS_G][bits<_MAX_GROUPS_G>];

static stock
	BitArray:YSI_g_sDefaultGroups<_MAX_GROUPS_G>,
	// Create group hierarchys.
	Iterator:GroupPlayers[_MAX_GROUPS_G]<MAX_PLAYERS>;

//#define GROUP_BITS<%0> BitArray:%0<_MAX_GROUPS_G>,

#define _Group_HasPlayer(%0,%1) \
	Bit_Get(YSI_gGroupPlayers[(%1)],(%0)) //, _MAX_GROUPS_G)
	//PA_Get(YSI_gGroupPlayers[(%0)],(%1))
	//Bit_Get(YSI_gGroupPlayers[(%0)], (%1), MAX_PLAYERS)

#define _Group_GetColor(%0) \
	(_:(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_COLOR) | 0xAA)

#define _Group_SetColor(%0,%1) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] = (YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & ~e_GROUP_FLAGS_COLOR) | (e_GROUP_FLAGS:(%1) & e_GROUP_FLAGS_COLOR))

#define _Group_GetGang(%0) \
	(bool:(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_GANG))

#define _Group_LetGang(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] |= e_GROUP_FLAGS_GANG)

#define _Group_VetGang(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] &= ~e_GROUP_FLAGS_GANG)

#define _Group_IsActive(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

//#define _Group_IsValid(%0) 
//	(0 <= (%0) < _MAX_GROUPS && Group_IsActive(%0))

#define _Group_IsValid(%0) \
	((_:(%0)<=_:GROUP_GLOBAL)&&(_Group_IsActive(GROUP_TEMP_FIX(%0))))

//#define Group_IsActive(%0) 
//	(YSI_gGroupData[_:GROUP_FIX(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

FOREIGN__ void:_Group_ReInitPlayers();

GLOBAL__ void:_Group_ReInitPlayers()
{
	Iter_Init(GroupPlayers);
	for (new i = 0; i != _MAX_GROUPS_G; ++i) if (_Group_IsActive(i))
	{
		FOREACH__ (new playerid : Player)
		{
			if (_Group_HasPlayer(i, playerid)) Iter_Add(GroupPlayers[i], playerid);
		}
	}
}

HANDOFF()
{
	P:1("y_groups HANDOFF called");
	DISTRIBUTE(YSI_gGroupData);
	DISTRIBUTE(YSI_g_sChildGroups);
	_Group_ReInitPlayers();
	P:1("y_groups HANDOFF ended");
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to add the following items to.</param>
 * <remarks>
 *  This sets up a temporary environment, during which all items are ONLY added
 *  to the specified group and no others, with no complex extra code required.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define GROUP_ADD<%0> for(J@=_Group_AddInternal(1,(%0));J@;J@=_Group_AddInternal(0,(%0)))

remotefunc static stock void:Group_AddInternal_(a,g)
{
	GROUP_CHAIN?<YSI_g_sNextInitFunc>(-1, a, g);
}

stock _Group_AddInternal(a, Group:g)
{
	//printf("_Group_AddInternal %d %d", a, _:g);
	if (_Group_IsValid(g))
	{
		broadcastfunc Group_AddInternal_(a, _:GROUP_TEMP_FIX(g));
		return a;
	}
	else
	{
		return 0;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="p">Player who connected.</param>
 * <param name="g">The player's new groups.</param>
 * <param name="s">Size of "g".</param>
 * <remarks>
 *  Pretend the player is in all the groups they won't be in shortly so that
 *  they have a complete blank slate when they connect - the system KNOWS they
 *  are not in some groups and are in others.
 *
 *  Uses an unusual size in "g" to reduce the string length.
 * </remarks>
 *//*------------------------------------------------------------------------**/

remotefunc static void:_Group_FakePlayer(p,Bit:g[sizeof RG@],s)
{
	for (new i = 0; i != sizeof (g); ++i)
	{
		// Set their current groups to the inverse of what they are now in.
		YSI_gGroupPlayers[p][i] = ~g[i];
	}
	_Group_SetPlayer(p, g, s);
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to check.</param>
 * <returns>
 *  bool: - Is the group active and valid?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Group_IsValid(Group:g);

GLOBAL__ bool:Group_IsValid(Group:g)
{
	//GROUP_FIX(g);
	return _Group_IsValid(g);
}

static stock Group_DefineStates_() <YSI_has_groups : y>
{
}

static stock Group_DefineStates_() <YSI_has_groups : n>
{
}

static stock Group_DefineStates_() <YSI_has_groups : other>
{
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Finds three functions by prefix:
 *
 *  _yGI - An init function to set up a script using groups.
 *  _yGA - An add function called when a new group is created.
 *  _yGU - An update function called when a player's groups change.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnYSIInit()
{
	P:1("Group_OnYSIInit called");
	state YSI_has_groups : y;
	// Set up the global groups.
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				P:5("Group_OnYSIInit: Master");
				Iter_Init(GroupPlayers);
				strpack(YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_NAME], YSI_g_scGlobalName, MAX_GROUP_NAME char);
				YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_ACTIVE | e_GROUP_FLAGS_GLOBAL;
				YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_HASH] = YHash(YSI_g_scGlobalName);
				// Store the default groups away from the actual global group.
				// The default groups include the global group, but it itself
				// doesn't.
				Bit_Let(YSI_g_sDefaultGroups, _:_MAX_GROUPS);
			}
	#endif
	// Call the other group init functions.
	new
		ni = AMX_GetPublicPointerPrefix(0, YSI_g_sNextInitFunc, _A<_yGI>),
		na = AMX_GetPublicPointerPrefix(0, YSI_g_sNextAddFunc, _A<_yGA>),
		nu = AMX_GetPublicPointerPrefix(0, YSI_g_sNextUpdFunc, _A<_yGU>);
	//printf("Group_OnYSIInit: %d, %d, %d", ni, na, nu);
	P:4("Group_OnYSIInit: %d, %d, %d", ni, na, nu);
	P:4("Group_OnYSIInit: %d, %d, %d", AMX_HEADER_COD - AMX_BASE_ADDRESS, YSI_g_sNextInitFunc, AMX_HEADER_DAT - AMX_BASE_ADDRESS);
	// So just below the call to `GROUP_CHAIN` is this code:
	//   
	//   heapspace(); // I'm sure there's a reason this is here.  But I forgot it!
	//   
	// I just spent another long debugging session tracking down another bug
	// where the solution, in another totally unrelated file entirely, was
	// adding this line here:
	format(Q@, sizeof (Q@), YSI_EMPTY, AMX_HEADER_COD - AMX_BASE_ADDRESS);
	// WHY!?
	GROUP_CHAIN?<YSI_g_sNextInitFunc>(ni, na, nu);
	//CallLocalFunction("_Group_SpecialInit", YSI_EMPTY);
	heapspace(); // I'm sure there's a reason this is here.  But I forgot it!
	P:1("Group_OnYSIInit end");
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Destroy all this script's groups.  This is an instance of "_YSI_SpecialExit"
 *  which can't be y_hooked and is called after (almost) every other callback,
 *  at least after every one controlled via y_scriptinit.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnYSIExit()
{
	#if defined _Group_SpecialExit
		_Group_SpecialExit();
	#endif
	_Group_TryRemove();
	return 1;
}

#undef OnYSIExit
#define OnYSIExit _Group_SpecialExit
#if defined _Group_SpecialExit
	forward _Group_SpecialExit();
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="group">Group to destroy from the system.</param>
 *//*------------------------------------------------------------------------**/

remotefunc static void:_Group_Destroy(g, const Iterator@gp[MAX_PLAYERS + 1], s)
{
	#pragma unused s
	new
		ps = Bit_Slot(g),
		Bit:pm = ~Bit_Mask(g);
	if (YSI_g_sNextUpdFunc)
	{
		// Update all players who were in this group as they may have lost
		// some permissions.  This is the simplest update because we don't
		// need to worry about the effect of removing this group on the
		// players' memberships in other groups.  Maybe they were added to
		// that other group as a direct result of being added to this group,
		// but maybe they weren't - there's no way to know!
		// Check it!  Local parameter iterator!
		FOREACH__ (new p : gp)
		{
			YSI_gTempAllowed_ = YSI_gGroupPlayers[p];
			// If these parameters were the other way round I could do this:
			//GROUP_CHAIN<YSI_g_sNextUpdFunc>(p, (YSI_gGroupPlayers[p], YSI_gGroupPlayers[p][ps] &= pm), YSI_gGroupPlayers[p]);
			// But they're currently not so I can't.
			GROUP_CHAIN<YSI_g_sNextUpdFunc>(p, YSI_gTempAllowed_, YSI_gGroupPlayers[p]);
			YSI_gGroupPlayers[p][ps] &= pm;
		}
	}
	else
	{
		FOREACH__ (new p : gp)
		{
			// Remove all players from this group.
			YSI_gGroupPlayers[p][ps] &= pm;
		}
	}
}

// Added for the fun of it.
FOREIGN__ void:Group_Destroy(Group:group);

GLOBAL__ void:Group_Destroy(Group:group)
{
	P:2("Group_Destroy called: %i", _:group);
	P:2("Group_Destroy called in %d", Master_ID());
	// You can't destroy the global group.
	if (_Group_IsValid(group) && group != GROUP_GLOBAL)
	{
		GROUP_FIX(group);
		broadcastfunc _Group_Destroy(_:group, Iter_TrueArray(GroupPlayers[_:group]), Iter_TrueSize(GroupPlayers[]));
		YSI_gGroupData[_:group][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS:0;
		YSI_gGroupData[_:group][E_GROUP_DATA_HASH] = 0;
		Iter_Clear(GroupPlayers[_:group]);
		MASTER_RESET<_:group>
		// This group no longer exists, so can't be the child of another group.
		new
			ps = Bit_Slot(_:group),
			Bit:pm = ~Bit_Mask(_:group);
		for (new i = 0; i != _MAX_GROUPS; ++i)
		{
			YSI_g_sChildGroups[i][ps] &= pm;
		}
		// Nor can it have groups (saves some later checks).
		YSI_g_sChildGroups[_: group] = YSI_g_cEmptyGroups;
	}
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Removes all groups purely owned by the calling script.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:_Group_TryRemove();

GLOBAL__ void:_Group_TryRemove()
{
	for (new i = 0; i != _MAX_GROUPS; ++i) if (_Group_IsActive(i))
	{
		MASTER_REMOVE<i>
		MASTER_EMPTY<i>
		{
			//print("removing i");
			broadcastfunc _Group_Destroy(i, Iter_TrueArray(GroupPlayers[i]), Iter_TrueSize(GroupPlayers[]));
			YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS:0;
			YSI_gGroupData[i][E_GROUP_DATA_HASH] = 0;
			Iter_Clear(GroupPlayers[i]);
		}
	}
	//return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player that left.</param>
 * <param name="reason">Why they left (unused).</param>
 * <remarks>
 *  Removes this player from all groups.  Unfortunately there's no way to
 *  combine multiple iterator removals to improve their efficiency - currently
 *  they have to loop through all previous ones to find the one to modify to
 *  skip over that player.  I did debate updating foreach to doubly-linked
 *  lists for this reason - that would make reverse traversal and removal faster
 *  by doubling memory consumption but only very slightly affecting adds.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	P:2("hook OnPlayerDisconnect called: %d, %d", playerid, reason);
	// Can't - can't what?  Don't stop typing mid comment!
	//foreach (new Group:g : PlayerGroups(playerid))
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				FOREACH__ (new g : Bits(YSI_gGroupPlayers[playerid]))
				{
					Iter_Remove(GroupPlayers[g], playerid);
					Bit_Vet(YSI_gGroupPlayers[playerid], g);
				}
			}
	#endif
	// Remove them from everything ever.
	//static const
	//	BitArray:scEmpty<_MAX_GROUPS_G>;
	//GROUP_CHAIN?<YSI_g_sNextUpdFunc>(playerid, YSI_gGroupPlayers[p], scEmpty);
	YSI_gGroupPlayers[playerid] = YSI_g_cEmptyGroups;
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player that joined.</param>
 * <remarks>
 *  The player may not have ACTUALLY joined the server, they may have just been
 *  added to this newly loaded script.  In that case we need to initialise the
 *  locally stored group data to the new data.  Of course, if this script is the
 *  group master, then we need to do significantly more!  This is more complex
 *  than other scripts with master as they don't have some things to do in non-
 *  master scripts as well, whereas this one does.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerConnect@9(playerid)
{
	P:1("Groups_OnPlayerConnect called: %d, %d", playerid, !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT)));
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				//print("0");
				P:6("Group_OnPlayerConnect: Master %d", playerid);
				// Is master.  ALWAYS reset all players - if they start screwing
				// around with loading orders then that's their own fault!
				broadcastfunc _Group_FakePlayer(playerid, YSI_g_sDefaultGroups, bits<_MAX_GROUPS_G>);
				//print("1");
			}
		#if _YSIM_IS_CLOUD
			else
		#endif
	#endif
	#if YSIM_HAS_MASTER
			{
				P:6("Group_OnPlayerConnect: Slave %d", playerid);
				static const
					BitArray:scF<_MAX_GROUPS_G> = {Bit:-1, ...};
				_GROUPS_CHECK_ANY(scF, YSI_gGroupPlayers[playerid])
				{
					// Already been set up - return.
					return 1;
				}
				//_Group_
				_Group_InitPlayer(playerid, Master_ID());
			}
	#endif
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="p">The player that joined.</param>
 * <param name="master">The script that just started.</param>
 * <remarks>
 *  Request all a player's groups from the master system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:_Group_InitPlayer(p, master);

GLOBAL__ void:_Group_InitPlayer(p, master)
{
	targetfunc _Group_FakePlayer<master>(p, YSI_gGroupPlayers[p], bits<_MAX_GROUPS_G>);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to add to multiple groups.</param>
 * <param name="group">Parent group to add to.</param>
 * <returns>
 *  A new array of groups.
 * </returns>
 * <remarks>
 *  Takes a group and adds a player to that group and every child group of
 *  which they are not already a member.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// If you overflow this stack there is something VERY wrong!  The manual stack
// is intended to help us combat very long inheritance chains.  This code also
// neatly ignores recursion by only doing any one group if the player doesn't
// already have it.
static
	YSI_g_sRecursionStack[_MAX_GROUPS_G][2];

static stock Bit:_Group_SetSome(playerid, group)
{
	new
		g = -1,
		s = 0;
	YSI_gTempAllowed_ = YSI_gGroupPlayers[playerid];
	Bit_Let(YSI_gTempAllowed_, group);
	for ( ; ; )
	{
		g = Iter_Func@Bits(g, YSI_g_sChildGroups[group], bits<_MAX_GROUPS_G>);
		if (g == -1)
		{
			// Finished this child group, pop off the stack.
			if (s--)
			{
				g = YSI_g_sRecursionStack[s][0];
				group = YSI_g_sRecursionStack[s][1];
			}
			else break;
		}
		else if (!Bit_Get(YSI_gTempAllowed_, g))
		{
			// This player isn't in this group, add them.
			Bit_Let(YSI_gTempAllowed_, g);
			YSI_g_sRecursionStack[s][0] = g;
			YSI_g_sRecursionStack[s][1] = group;
			++s;
			group = g;
			g = -1;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to modify.</param>
 * <param name="p">Player to modify the group for.</param>
 * <param name="s">Add the player (true) or remove them (false).</param>
 * <remarks>
 *  Will in some cases update all settings, unless they are being added through
 *  a recursive call due to being added to child groups.
 *
 *  There is an internal version that ONLY adds them to the group and DOES NOT
 *  update any of their other settings.  As a result it has less checks in it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetPlayer(Group:g,p,bool:s);

GLOBAL__ void:Group_SetPlayer(Group:g,p,bool:s)
{
	if (_Group_IsValid(g) && VALID_PLAYERID(p))
	{
		GROUP_FIX(g);
		if (s)
		{
			if (!_Group_HasPlayer(g, p))
			{
				// Added to a group they don't already have.  Make a new list of
				// groups they're in, taking in to account the new groups
				// hierarchy and pass that new array about.
				_Group_SetSome(p, _:g);
				broadcastfunc _Group_SetPlayer(p, YSI_gTempAllowed_, sizeof (YSI_gTempAllowed_));
				return; //1;
			}
		}
		else
		{
			if (_Group_HasPlayer(g, p))
			{
				YSI_gTempAllowed_ = YSI_gGroupPlayers[p];
				Bit_Vet(YSI_gTempAllowed_, _:g);
				broadcastfunc _Group_SetPlayer(p, YSI_gTempAllowed_, sizeof (YSI_gTempAllowed_));
				return; //1;
			}
		}
	}
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="p">Player to set.</param>
 * <param name="g">The player's new groups.</param>
 * <param name="s">Size of "g".</param>
 * <remarks>
 *  Pass a list of groups that the player is now in or not in.  This is a
 *  complete replacement for their existing list of groups, and so multiple
 *  updates can be done at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

remotefunc void:_Group_SetPlayer(p, Bit:g[sizeof RG@], s)
{
	#pragma unused s
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				P:2("_Group_SetPlayer called: %i, %s, %s, %i", p, Bit_Display(YSI_gGroupPlayers[p]), Bit_Display(g), s);
				// <a href="http://supertech.csail.mit.edu/papers/debruijn.pdf" />
				new
					Bit:cur = Bit:0,
					Bit:exor = Bit:0,
					Bit:bit = Bit:0,
					group = 0;
				for (new i = 0; i != sizeof (g); ++i)
				{
					// Get the difference between the old and new groups.
					cur = YSI_gGroupPlayers[p][i];
					exor = g[i] ^ cur;
					P:6("_Group_SetPlayer: Loop %d 0x%04x%04x 0x%04x%04x", i, _:cur >>> 16, _:cur & 0xFFFF, _:exor >>> 16, _:exor & 0xFFFF);
					// Low-level bit twiddling.
					while ((bit = Bit:Cell_GetLowestComponent(exor)))
					{
						// group = i * cellbits + (scDeBruijn[(_:bit * 0x077CB531) >>> 27]);
						group = i * cellbits + Cell_GetLowestBit(exor);
						P:7("_Group_SetPlayer: %d %s %d", p, _:(cur & bit) ? ("remove from") : ("add to"), group);
						if (cur & bit)
						{
							// Used to have this group, now don't.
							Iter_Remove(GroupPlayers[group], p);
						}
						else
						{
							// Didn't have this group, now do.
							Iter_Add(GroupPlayers[group], p);
						}
						exor ^= bit;
					}
				}
			}
		#if _YSIM_IS_CLOUD
			else
			{
				P:4("_Group_SetPlayer called - not master");
			}
		#endif
	#else
		P:4("_Group_SetPlayer called - no master");
	#endif
	#pragma tabsize 4
	GROUP_CHAIN?<YSI_g_sNextUpdFunc>(p, YSI_gGroupPlayers[p], g);
	// NOW save the new version, after everything else has had a chance to
	// update according to the changes.
	YSI_gGroupPlayers[p] = g;
}

/*-------------------------------------------------------------------------*//**
 * <param name="p">Player to add to the smallest group.</param>
 * <param name="gs">An array of possible groups.</param>
 * <param name="c">The number of USED items in the array.</param>
 * <returns>
 *  The group they have been added to.
 * </returns>
 * <remarks>
 *  Chains the call with "Group_SetPlayer" to use its hierarchy code.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group:_Group_SetBalancedInternal(p,const Group:gs[],c);

GLOBAL__ Group:_Group_SetBalancedInternal(p,const Group:gs[],c)
{
	// Find which of the listed groups has the fewest players in.
	P:4("_Group_SetBalancedInternal called: %d, %d", p, c);
	new
		count = cellmax,
		Group:id = INVALID_GROUP;
	for (new i = 0; i != c; ++i)
	{
		// Find the group with the fewest players.
		new
			gi = _:gs[i];
		if (_Group_IsValid(Group:gi))
		{
			new
				g2 = _:GROUP_TEMP_FIX(Group:gi),
				cc = Iter_Count(GroupPlayers[g2]);
			P:7("_Group_SetBalancedInternal: Group %d Count = %d", _:g2, cc);
			if (_Group_HasPlayer(g2, p))
			{
				P:7("_Group_SetBalancedInternal: Has player");
				// The player is already in this group - just return.
				return Group:gi;
			}
			else if (cc < count)
			{
				count = cc,
				id = Group:gi;
			}
		}
	}
	if (id == INVALID_GROUP)
	{
		P:W("Group_SetBalanced(Array) requires at least 1 valid group.");
	}
	else
	{
		Group_SetPlayer(id, p, true);
	}
	return id;
}

/*-------------------------------------------------------------------------*//**
 * <param name="p">Player to add to the smallest group.</param>
 * <param name="gs">An array of possible groups.</param>
 * <param name="c">The number of USED items in the array.</param>
 * <returns>
 *  The group they have been added to.
 * </returns>
 * <remarks>
 *  Puts a player in whichever of the given groups currently has the fewest
 *  players.
 *
 *  Now ONLY takes a list - arrays should use "Group_SetBalancedArray".  As a
 *  result, has more error-checking.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Group:Group_SetBalancedArray(p, const Group:gs[], c = sizeof (gs))
{
	if (!(0 <= p < MAX_PLAYERS)) return INVALID_GROUP;
	return _Group_SetBalancedInternal(p, gs, c);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to put in one of a number of groups</param>
 * <param name="">A list of groups.</param>
 * <remarks>
 *  Puts a player in whichever of the given groups currently has the fewest
 *  players.
 *
 *  Now ONLY takes a list - arrays should use "Group_SetBalancedArray".  As a
 *  result, has more error-checking.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Group:Group_SetBalanced(playerid, Group:g0, Group:g1, Group:...)
{
	new
		Group:possible[_MAX_GROUPS_G],
		count = min(_MAX_GROUPS_G + 1, numargs()),
		i = 2,
		j = 3;
	possible[0] = g0,
	possible[1] = g1;
	while (j != count)
	{
		possible[i++] = Group:getarg(j++);
	}
	return Group_SetBalancedArray(playerid, possible, i);
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to check.</param>
 * <param name="p">Player to check.</param>
 * <returns>
 *  Is this player in this group?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Group_GetPlayer(Group:g,p);

GLOBAL__ bool:Group_GetPlayer(Group:g,p)
{
	P:2("bool:Group_GetPlayer called: %i, %i", _:g, p);
	if (_Group_IsValid(g) && VALID_PLAYERID(p))
	{
		return Bit_Get(YSI_gGroupPlayers[p], _:GROUP_TEMP_FIX(g));
	}
	return false;
}

stock Group:operator+(Group:g, o)
{
	Group_SetPlayer(g, o, true);
	return g;
}

stock Group:operator-(Group:g, o)
{
	Group_SetPlayer(g, o, false);
	return g;
}

stock bool:operator==(Group:g, o)
{
	return Group_GetPlayer(g, o);
}

stock bool:operator!=(Group:g, o)
{
	return !Group_GetPlayer(g, o);
}

/*-------------------------------------------------------------------------*//**
 * <summary></summary>
 * <param name="g">Group to set the name of.</param>
 * <param name="n">The new name of the group.</param>
 * <remarks>
 *  Sets the name of a group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetName(Group:g,const string:n[]);

GLOBAL__ void:Group_SetName(Group:g,const string:n[])
{
	P:2("Group_SetName called: %i, \"%s\"", _:g, n);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		if (IsNull(n))
		{
			YSI_gGroupData[_:g][E_GROUP_DATA_NAME][0] = 0;
			YSI_gGroupData[_:g][E_GROUP_DATA_HASH] = 0;
		}
		else
		{
			strpack(YSI_gGroupData[_:g][E_GROUP_DATA_NAME], n, MAX_GROUP_NAME char);
			YSI_gGroupData[_:g][E_GROUP_DATA_HASH] = YHash(n);
		}
	}
	//return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to get the name of.</param>
 * <returns>
 *  string:
 * </returns>
 * <remarks>
 *  Gets the name of a group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ string:Group_GetName(Group:g);

GLOBAL__ string:Group_GetName(Group:g)
{
	//printf("Group_GetName called: %04x%04x", _:g >>> 16, _:g & 0xFFFF);
	P:2("Group_GetName called: %04x%04x", _:g >>> 16, _:g & 0xFFFF);
	static
		ret[YSI_MAX_STRING];
	if (_Group_IsValid(g))
	{
		//print("Is Valid");
		//return Bit_Get(YSI_gGroupPlayers[g], p);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
		strunpack(ret, YSI_gGroupData[_:GROUP_TEMP_FIX(g)][E_GROUP_DATA_NAME], YSI_MAX_STRING);
		//printf("Is Valid: %s", ret);
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of a group to get.</param>
 * <returns>
 *  Group: - The ID of the group with this name.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group:Group_GetID(const string:name[]);

GLOBAL__ Group:Group_GetID(const string:name[])
{
	P:2("Group_GetID called: %s", name);
	new
		i = 0,
		hash = YHash(name);
	while (i != _MAX_GROUPS)
	{
		if (_Group_IsActive(i) && YSI_gGroupData[i][E_GROUP_DATA_HASH] == hash)
		{
			break;
		}
		++i;
	}
	if (i == _MAX_GROUPS) return INVALID_GROUP;
	return GROUP_MANGLE(i);
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to set for.</param>
 * <param name="n">Set or not?</param>
 * <remarks>
 *  I actually can't remember what the "Gang" setting on a group does - I don't
 *  think it actually does anything in the latest code version!
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetGang(Group:g,bool:n);

GLOBAL__ void:Group_SetGang(Group:g,bool:n)
{
	P:2("Group_SetGang called: %i, %i", _:g, n);
	if (_Group_IsValid(g))
	{
		if (n)
		{
			_Group_LetGang(GROUP_TEMP_FIX(g));
		}
		else
		{
			_Group_VetGang(GROUP_TEMP_FIX(g));
		}
	}
	//return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to get the gang status of.</param>
 * <returns>
 *  bool:
 * </returns>
 * <remarks>
 *  I still don't remember what this once did!
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Group_GetGang(Group:g);

GLOBAL__ bool:Group_GetGang(Group:g)
{
	P:2("bool:Group_GetGang called: %i", _:g);
	if (_Group_IsValid(g))
	{
		return _Group_GetGang(GROUP_TEMP_FIX(g));
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Group_SetColor
 *  Group_SetColour
 * </summary>
 * <param name="g">The group to set the colour of.</param>
 * <param name="c">An RGBA colour.</param>
 * <remarks>
 *  This colour is not actually currently used anywhere.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetColour(Group:g,c);

GLOBAL__ void:Group_SetColour(Group:g,c)
{
	P:2("Group_SetColour called: %i, %i", _:g, c);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		_Group_SetColor(g, c);
	}
	//return 1;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Group_GetColor
 *  Group_GetColour
 * </summary>
 * <param name="g">The group to get the colour of.</param>
 * <returns>
 *  An RGBA colour.
 * </returns>
 * <remarks>
 *  This colour is not actually currently used anywhere.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group_GetColour(Group:g);

GLOBAL__ Group_GetColour(Group:g)
{
	P:2("Group_GetColour called: %i", _:g);
	if (_Group_IsValid(g))
	{
		return _Group_GetColor(GROUP_TEMP_FIX(g));
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
	}
	return 0;
}

#define Group_SetColor Group_SetColour
#define Group_GetColor Group_GetColour

/*-------------------------------------------------------------------------*//**
 * <param name="g">The group to get the membership for.</param>
 * <returns>
 *  The number of players in the group.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group_GetCount(Group:g);

GLOBAL__ Group_GetCount(Group:g)
{
	P:2("Group_GetCount called: %i", _:g);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		return Iter_Count(GroupPlayers[_:g]);
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  The number of groups that exist.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group_Count(bool:g = false);

GLOBAL__ Group_Count(bool:g = false)
{
	P:2("Group_Count called: %i", _:g);
	new count = !!g;
	for (new i = 0; i != _MAX_GROUPS; ++i)
	{
		if (_Group_IsActive(i))
		{
			++count;
		}
	}
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The optional name of the new group.</param>
 * <returns>
 *  The group ID with a tag of "Group:", or "INVALID_GROUP".
 * </returns>
 * <remarks>
 *  Group_Create - Local function to detect and "NULL"ify empty strings.
 *  _Group_Create - Global function that does most of the work.
 *  _Group_CreateChain - Remote function that updates all master scripts with
 *      the new group's existence.
 * </remarks>
 *//*------------------------------------------------------------------------**/

remotefunc static void:_Group_CreateChain(Group:g)
{
	GROUP_CHAIN?<YSI_g_sNextAddFunc>(g);
}

FOREIGN__ Group:_Group_Create(const string:name[]);

GLOBAL__ Group:_Group_Create(const string:name[])
{
	P:2("Group:Group_Create called: \"%s\"", name);
	P:2("Group_Create called in %d", Master_ID());
	new
		i = 0;
	if (!IsNull(name))
	{
		// Get a group of the same name if it already exists.
		i = _:Group_GetID(name);
		if (i != _:INVALID_GROUP)
		{
			MASTER_ADD<_:GROUP_TEMP_FIX(Group:i)>
			return Group:i;
		}
	}
	i = 0;
	while (i != _MAX_GROUPS && _Group_IsActive(i))
	{
		++i;
	}
	if (i == _MAX_GROUPS) return INVALID_GROUP;
	if (IsNull(name))
	{
		YSI_gGroupData[i][E_GROUP_DATA_NAME][0] = 0;
		YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_TEMP | e_GROUP_FLAGS_ACTIVE;
		YSI_gGroupData[i][E_GROUP_DATA_HASH] = 0;
	}
	else
	{
		strpack(YSI_gGroupData[i][E_GROUP_DATA_NAME], name, MAX_GROUP_NAME char);
		YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_ACTIVE;
		if (!(YSI_gGroupData[i][E_GROUP_DATA_HASH] = YHash(name)))
		{
			P:E("Group %d has hash 0.", name);
		}
	}
	MASTER_SET<i>
	++YSI_g_sGroupCount;
	// Set the child groups to only this group.
	//Bit_Let(YSI_g_sChildGroups[i], i);
	// Add this group to other groups.
	broadcastfunc _Group_CreateChain(Group:i);
	return GROUP_MANGLE(i);
}

stock Group:Group_Create(const string:name[] = "")
{
	if (name[0])
	{
		return _Group_Create(name);
	}
	else
	{
		return _Group_Create(NULL);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="group">Group to loop over.</param>
 * <param name="start">Last value.</param>
 * <returns>
 *  The next player.
 * </returns>
 * <remarks>
 *  Internal implementation of the "Group()" iterator for "foreach".  Returns
 *  all the players in a group one at a time.  Now just wraps the "GroupPlayers"
 *  iterator that is only stored in the GROUP master script.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated use "GroupMember"
stock Iter_Func@Group(start, Group:group)
{
	static
		sOnce = true;
	if (sOnce)
	{
		P:I("The \"Group\" iterator is deprecated, please use \"GroupMember\" instead.");
		sOnce = false;
	}
	return Iter_Func@GroupMember(start, Group:group);
}

// Else.  VERY similar to the `iterstart` macro, but without the first `J@`,
// which is used both for `sizeof` (we already gave it `I@`) and for detecting
// state functions, which this is not one of (so doesn't need the detection -
// and even if it was a state function, we would know that here and could
// adapt).
#define Iterator@GroupElse_(%1)%9$%9))-1);_:(%9=Iterator@%0$[_:%2]%9; ))-1+(%1));_:(%1)!=_:F@k:F@l:(%2=Iter_Func@%0$(_:%2));

FOREIGN__ Iter_Func@GroupMember(start, Group:group);

GLOBAL__ Iter_Func@GroupMember(start, Group:group)
{
	GROUP_FIX(group);
	if (start == -1)
	{
		//start = Iter_Begin(GroupPlayers[]);
		start = Iter_First(GroupPlayers[_:GROUP_TEMP_FIX(group)]);
	}
	else
	{
		start = Iter_Next(GroupPlayers[_:GROUP_TEMP_FIX(group)], start);
	}
	if (start == Iter_End(GroupPlayers[]))
	{
		return -1;
	}
	return start;
}

#define Iterator@GroupMember iterstart(-1)

/*-------------------------------------------------------------------------*//**
 * <param name="start">Last value.</param>
 * <returns>
 *  The next group.
 * </returns>
 * <remarks>
 *  Internal implementation of the "CreatedGroup()" iterator for "foreach".
 *  Returns all the groups that exist.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// Bypass y_iterate restrictions.
FOREIGN__ Group:Iter_Func@CreatedGroup(group);

GLOBAL__ Group:Iter_Func@CreatedGroup(group)
{
	// In most iterators the inital value is implicitly handled by the first
	// "++", but it isn't here because we need to correct for the "Group" flag.
	if (Group:group != INVALID_GROUP) GROUP_FIX(Group:group);
	while (++group < (_MAX_GROUPS_G - 1))
	{
		// DO NOT include the global group in this loop!
		if (_Group_IsActive(Group:group)) return GROUP_MANGLE(Group:group);
	}
	return INVALID_GROUP;
}

#define Iterator@CreatedGroup iterstart(-1)

/*-------------------------------------------------------------------------*//**
 * <param name="parent">Group to get the children of.</param>
 * <param name="start">Last value.</param>
 * <returns>
 *  The next group.
 * </returns>
 * <remarks>
 *  Internal implementation of the "ChildGroup()" iterator for "foreach".
 *  Returns all the groups that are a child of the provided group.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group:Iter_Func@GroupChild(start, Group:parent);

GLOBAL__ Group:Iter_Func@GroupChild(start, Group:parent)
{
	if (!_Group_IsValid(parent)) return INVALID_GROUP;
	// In most iterators the inital value is implicitly handled by the first
	// "++", but it isn't here because we need to correct for the "Group" flag.
	if (Group:start != INVALID_GROUP) GROUP_FIX(Group:start);
	// Use the existing "Bits" iterator with fixed identifiers.
	return GROUP_MANGLE(Iter_Func@Bits(start, YSI_g_sChildGroups[_:GROUP_TEMP_FIX(parent)], bits<_MAX_GROUPS_G>));
}

#define Iterator@GroupChild Iterator@Bits

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  _Y_G@C_0
 *  _Y_G@C_1
 *  _Y_G@C_2
 *  _Y_G@C_3
 * </summary>
 * <param name="func">Function to call.</param>
 * <param name="">0, 1, 2, or 3 parameters.</param>
 * <returns>
 *  0 - ALWAYS zero to make "GCHAIN__" work properly.
 * </returns>
 * <remarks>
 *  Basically function indirection, call a function through a pointer and use
 *  the compiler to figure out the assembly to generate instead of having a
 *  run-time loop inside a single instance of this function.  Using just one
 *  macro ("GROUP_CHAIN") one of these four functions are selected and called.
 *  Adding more is fairly trivial too, the parameters are just:
 *
 *  <code>
 *      #emit PUSH.S     &lt;16 + n * 4&gt;   <br />
 *      #emit PUSH.S     ...                  <br />
 *      #emit PUSH.S     20                   <br />
 *      #emit PUSH.S     16                   <br />
 *      #emit PUSH.C     &lt;n * 4&gt;
 *  </code>
 *
 * This code is now, of course, SERIOUSLY outdated - function pointers have
 * advanced way beyond this (see indirection.inc), but this code works, and
 * because we have one function for each number of parameters, it is actually
 * very fast because it is so specialised.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Y_G@C_0(func)
{
	#emit PUSH.C     0
	#emit LCTRL      6
	#emit ADD.C      36
	#emit LCTRL      8
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	// ALWAYS return 0;
	return 0;
}

stock _Y_G@C_1(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     16
	#emit PUSH.C     4
	#emit LCTRL      6
	#emit ADD.C      36
	#emit LCTRL      8
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

stock _Y_G@C_2(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     20
	#emit PUSH.S     16
	#emit PUSH.C     8
	#emit LCTRL      6
	#emit ADD.C      36
	#emit LCTRL      8
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

stock _Y_G@C_3(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     24
	#emit PUSH.S     20
	#emit PUSH.S     16
	#emit PUSH.C     12
	#emit LCTRL      6
	#emit ADD.C      36
	#emit LCTRL      8
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="g">Group to set for.</param>
 * <param name="el">Element to set.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  IMPORTANT NOTE: Groups are SLIGHTLY different to other systems - if you
 *  REMOVE a group from another group then players WILL NOT be removed from
 *  that second group, or any child groups.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetGroup(Group:g,Group:el,bool:s);

GLOBAL__ void:Group_SetGroup(Group:g,Group:el,bool:s)
{
	P:2(#Group_SetGroup " called: %i, %i, %i", _:g, _:el, s);
	// Set wether a group can use this item.
	if (g != el && _Group_IsValid(g) && _Group_IsValid(el))
	{
		GROUP_FIX(g);
		GROUP_FIX(el);
		if (s)
		{
			if (Bit_Get(YSI_g_sChildGroups[_:g], _:el))
			{
				// Child is already part of parent.
				return;
			}
			Bit_Let(YSI_g_sChildGroups[_:g], _:el);
			if (g == Group:_MAX_GROUPS) Bit_Let(YSI_g_sDefaultGroups, _:el);
			FOREACH__ (new p : GroupPlayers[_:g])
			{
				if (!_Group_HasPlayer(el, p))
				{
					_Group_SetSome(p, _:el);
					broadcastfunc _Group_SetPlayer(p, YSI_gTempAllowed_, bits<_MAX_GROUPS_G>);
				}
			}
		}
		else
		{
			if (Bit_Get(YSI_g_sChildGroups[_:g], _:el))
			{
				// Child is a part of parent (don't remove players though).
				Bit_Vet(YSI_g_sChildGroups[_:g], _:el);
				if (g == Group:_MAX_GROUPS) Bit_Vet(YSI_g_sDefaultGroups, _:el);
			}
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="el">Element to set.</param>
 * <param name="s">Set or unset?</param>
 * <remarks>
 *  If "s" is true, then one element is added to the global group.  False it is
 *  removed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Group_SetGlobalGroup(Group:el,bool:s);

GLOBAL__ void:Group_SetGlobalGroup(Group:el,bool:s)
{
	P:2(#Group_SetGlobalGroup " called: %i, %i", _:el, s);
	Group_SetGroup(GROUP_GLOBAL, el, s);
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_Get...</summary>
 * <param name="g">Group to get from.</param>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the group have the element?
 * </returns>
 * <remarks>
 *  This has no "active" checks on the groups as if they aren't active but are
 *  in range, then "YSI_g_sChildGroups" will return false anyway.  Extra checks
 *  are therefore just a waste of time.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Group_GetGroup(Group:g,Group:el);

GLOBAL__ bool:Group_GetGroup(Group:g,Group:el)
{
	P:2(#Group_GetGroup " called: %i, %i", _:g, _:el);
	return (el <= GROUP_GLOBAL && g <= GROUP_GLOBAL && Bit_Get(YSI_g_sChildGroups[_:GROUP_TEMP_FIX(g)], _:GROUP_TEMP_FIX(el)));
}

/*-------------------------------------------------------------------------*//**
 * <summary>Group_GetGlobal...</summary>
 * <param name="el">Element to get.</param>
 * <returns>
 *  bool: Does the global group have the element?
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Group_GetGlobalGroup(Group:el);

GLOBAL__ Group_GetGlobalGroup(Group:el)
{
	P:2(#Group_GetGlobalGroup " called: %i", _:el);
	return Group_GetGroup(GROUP_GLOBAL, el);
}

#define Group_AddChild(%0,%1) Group_SetGroup((%0), (%1), true)
#define Group_RemoveChild(%0,%1) Group_SetGroup((%0), (%1), false)
#define Group_IsChild(%0,%1) Group_GetGroup((%0), (%1))

/*-------------------------------------------------------------------------*//**
 * <param name="p">Ancestor group to check.</param>
 * <param name="c">Other group to check.</param>
 * <returns>
 *  bool: Is the second group related to the first?
 * </returns>
 * <remarks>
 *  Now uses implicit, not explicit, recursion.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock
	BitArray:YSI_g_sGroupDone<_MAX_GROUPS_G>;

FOREIGN__ bool:Group_IsDescendant(Group:p, Group:c);

GLOBAL__ bool:Group_IsDescendant(Group:p, Group:c)
{
	// Groups that don't exist CAN'T be related, even if they're the same group.
	if (_Group_IsValid(p) && _Group_IsValid(c))
	{
		if (p == c) return true; // Any group is related to itself.
		GROUP_FIX(p);
		GROUP_FIX(c);
		// "g" = current child.  "s" = current stack position.  "c" = target
		// child group.  "p" = current parent.
		Bit_SetAll(YSI_g_sGroupDone, false);
		Bit_Let(YSI_g_sGroupDone, _:p);
		new
			g = -1,
			s = 0;
		for ( ; ; )
		{
			g = Iter_Func@Bits(g, YSI_g_sChildGroups[_:p], bits<_MAX_GROUPS_G>);
			if (g == -1)
			{
				// Finished this child group, pop off the stack.
				if (s--)
				{
					g = YSI_g_sRecursionStack[s][0];
					p = Group:YSI_g_sRecursionStack[s][1];
				}
				else return false;
			}
			else if (!Bit_Get(YSI_g_sGroupDone, g))
			{
				if (Group:g == c) return true;
				// We haven't tested this group yet.
				Bit_Let(YSI_g_sGroupDone, g);
				YSI_g_sRecursionStack[s][0] = g;
				YSI_g_sRecursionStack[s][1] = _:p;
				++s;
				p = Group:g;
				g = -1;
			}
		}
	}
	return false;
}

//stock Group:operator+(Group:g, Group:o)
//{
//	Group_SetGroup(g, o, true);
//	return g;
//}
//
//stock Group:operator-(Group:g, Group:o)
//{
//	Group_SetGroup(g, o, false);
//	return g;
//}
//
//stock bool:operator>=(Group:g, Group:o)
//{
//	return Group_IsDescendant(g, o);
//}
//
//stock bool:operator>(Group:g, Group:o)
//{
//	return g != o && Group_IsDescendant(g, o);
//}
//
//stock bool:operator<=(Group:g, Group:o)
//{
//	return Group_IsDescendant(o, g);
//}
//
//stock bool:operator<(Group:g, Group:o)
//{
//	return g != o && Group_IsDescendant(o, g);
//}

