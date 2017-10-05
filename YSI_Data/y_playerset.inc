#if defined _INC_y_playerset
	#endinput
#endif
#define _INC_y_playerset

/**
 * <library name="y_playerset">
 * <section>
 *  Description
 * </section>
 *  This code is a huge abstraction of collections of players.  It allows you to
 *  define functions which take one or more players, specified in a number of
 *  formats, and perform the code for all those player.  Essentially it is an
 *  abstraction of loops over players.
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
 *//** *//*
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
	Portions created by the Initial Developer are Copyright C 2011
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

#include <a_samp>
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Data\y_playerarray"
#include "..\YSI_Core\y_debug"

#if !defined MAX_PLAYER_SET_STACK
    #define MAX_PLAYER_SET_STACK (3)
#endif

#define ALL_PLAYERS    (0x7FFFFFF1)
#define ALL_HUMANS     (0x7FFFFFF1)
#define ALL_CHARACTERS (0x7FFFFFF2)
#define ALL_BOTS       (0x7FFFFFF3)

enum e_PLAYER_SET_HACK
{
	e_PLAYER_SET_HACK_PA[bits<MAX_PLAYERS> + 1] = 0,
	e_PLAYER_SET_HACK_DATA[MAX_PLAYERS] = 0,
	e_PLAYER_SET_HACK_EXCESS[MAX_PLAYERS - (bits<MAX_PLAYERS> + 1)]
}

enum e_PLAYER_SET_TYPE
{
	e_PLAYER_SET_TYPE_NONE = 0,
	// "GROUP" is a YSI group.
	e_PLAYER_SET_TYPE_GROUP,
	// "ID" is just a single player.
	e_PLAYER_SET_TYPE_ID,
	// "PA" is a YSI player array.
	e_PLAYER_SET_TYPE_PA,
	// "BOOL" is an array of true/false.
	e_PLAYER_SET_TYPE_BOOL,
	// "ARRAY" is just an array of elements.
	e_PLAYER_SET_TYPE_ARRAY,
	// "CUSTOM" is used to identify fields in an enum.
	e_PLAYER_SET_TYPE_CUSTOM,
	e_PLAYER_SET_TYPE_PLAYERS,
	e_PLAYER_SET_TYPE_BOTS,
	e_PLAYER_SET_TYPE_CHARACTERS
}

// ========================================================================== //
// ========================================================================== //
//         WARNING: THE CODE BELOW IS VERY FRAGILE - DO NOT TOUCH IT!         //
// ========================================================================== //
// ========================================================================== //

// DO NOT change the order of these variables!
stock
	e_PLAYER_SET_TYPE:__ps_type[MAX_PLAYER_SET_STACK char],
	__ps_stack[MAX_PLAYER_SET_STACK][MAX_PLAYERS],
	__ps_data[e_PLAYER_SET_HACK],
	__ps_pointer = -1;

#define @PlayerVar:%0) __ps_addr_t:__ps_addr,__ps_drop_t:%0)foreach(new %0:PS(__ps_addr))

// More than one parameter.  This removes the need to redefine "for", which I'm
// very happy about, by doing all detection in one go.
#define __ps_addr_t:__ps_addr,__ps_drop_t:%0,%1)foreach(%2,%3:PS(__ps_addr)) __ps_addr_t:__ps_addr,%1)foreach(%2:PS(__ps_addr))

// Only one parameter (not caught by the above statement).  The one is the
// variable name we steal for the "foreach" loop.
#define __ps_addr,__ps_drop_t:%0) __ps_addr)

// This is not affected by any of the macros above.
#define @PlayerArray:%0<%1>%2) __ps_addr_t:__ps_addr%2)for(new PlayerArray:%0<MAX_PLAYERS>;__PS_A(__ps_addr,%0); )

#define @PlayerSet __ps_addr_t

// This code is now less fragile than before (and I understand it far more
// having done much more work with this style of macro in the interim).

// This is the master function, and a long one at that.  This function looks at
// the parameters passed to it and determines what SORT of parameter has been
// passed from the long list of possibilities.  If "cur" is -1 then this is the
// first call of the function and we need to determine the type.  If "cur" is
// not -1 then we are mid-loop and we can just use the stored determined type
// and use "cur" (as the last player done) to figure out the next player.  This
// code only loops through connected players.
stock Iter_Func@PS(cur, __ps_addr_t:addr)
{
	if (cur == -1)
	{
		P:3("__PS_S called: %i", _:addr);
		// Increment the "stack" pointer.
		if (__ps_pointer == MAX_PLAYER_SET_STACK - 1)
		{
			P:E("y_playerset stack overflow - increase \"MAX_PLAYER_SET_STACK\"");
			return -1;
		}
		++__ps_pointer;
		new
			begin = __ps_data[e_PLAYER_SET_HACK_DATA][0];
		// Is this a single value element (group or ID).
		if (_:addr == begin)
		{
			// Increase the stack pointer for recursive/multi-layered calls.
			// Should really add error-checking code for overflows.
			__ps_stack[__ps_pointer][0] = _:addr;
			// Single value - either a playerid or a groupid.
			#if defined _YSI_HAS_y_groups
				if (Group:addr & (Group:0x80000000))//GROUP_MASK)
				{
					// Use the pre-made iterator functionality.
					__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_GROUP;
					cur = Iter_Func@GroupMember(-1, Group:addr);
					if (cur == -1)
					{
						--__ps_pointer;
					}
					return cur;
				}
			#endif
			// May not always want this check - tough, they can't really have one
			// inside the function because that's just silly.
			switch (_:addr)
			{
				case ALL_PLAYERS:
				{
					// Uses the new "foreach" format of the infinate loop.
					__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_PLAYERS;
					cur = Iter_First(Player);
					if (cur == Iter_End(Player))
					{
						--__ps_pointer;
						cur = -1;
					}
					return cur;
				}
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					case ALL_BOTS:
					{
						__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_BOTS;
						cur = Iter_First(Bot);
						if (cur == Iter_End(Bot))
						{
							--__ps_pointer;
							cur = -1;
						}
						return cur;
					}
					case ALL_CHARACTERS:
					{
						__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_CHARACTERS;
						cur = Iter_First(Character);
						if (cur == Iter_End(Character))
						{
							--__ps_pointer;
							cur = -1;
						}
						return cur;
					}
				#endif
				default:
				{
					__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_ID;
					if (PS_IS_PLAYER_CONNECTED(_:addr))
					{
						return _:addr;
					}
					else
					{
						--__ps_pointer;
						return -1;
					}
				}
			}
		}
		else
		{
			// It's an array - _:addr contains the address of the target.
			memcpy(__ps_stack[__ps_pointer], __ps_data[e_PLAYER_SET_HACK_DATA], 0, MAX_PLAYERS * 4);
			// Try to determine what sort of array it is.  Note that there are three
			// possible types.
			if (begin == PA_TYPE_PA)
			{
				// Easy to handle - the systems were designed for each other.
				// This one needs work...  Err - what work?
				__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_PA;
				cur = Iter_Func@PA(-1, Bit:__ps_stack[__ps_pointer]);
				if (cur == -1)
				{
					--__ps_pointer;
				}
				return cur;
			}
			else if (begin & 0xFF0000FF == 0x0F0000F0)
			{
				__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_CUSTOM;
				cur = begin >>> 8 & 0x0000FFFF;
				if (cur == INVALID_PLAYER_ID & 0x0000FFFF)
				{
					--__ps_pointer;
					return -1;
				}
				if (PS_IS_PLAYER_CONNECTED(cur))
				{
					return cur;
				}
				addr = __ps_addr_t:0;
				while (++_:addr != MAX_PLAYERS)
				{
					cur = __ps_stack[__ps_pointer][_:addr];
					if (cur == INVALID_PLAYER_ID)
					{
						--__ps_pointer;
						return -1;
					}
					if (PS_IS_PLAYER_CONNECTED(cur))
					{
						return cur;
					}
				}
				--__ps_pointer;
				return -1;
			}
			else if (begin > 1 || __ps_data[e_PLAYER_SET_HACK_DATA][1] > 1 || __ps_data[e_PLAYER_SET_HACK_DATA][2] > 1)
			{
				// List of players.  One of the first three will normally be greater
				// than 1 in a list of players.
				__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_ARRAY;
				cur = begin;
				if (cur == INVALID_PLAYER_ID)
				{
					--__ps_pointer;
					return -1;
				}
				if (PS_IS_PLAYER_CONNECTED(cur))
				{
					return cur;
				}
				addr = __ps_addr_t:0;
				while (++_:addr != MAX_PLAYERS)
				{
					cur = __ps_stack[__ps_pointer][_:addr];
					if (cur == INVALID_PLAYER_ID)
					{
						--__ps_pointer;
						return -1;
					}
					if (PS_IS_PLAYER_CONNECTED(cur))
					{
						return cur;
					}
				}
				--__ps_pointer;
				return -1;
			}
			else
			{
				// Boolean array.
				__ps_type{__ps_pointer} = e_PLAYER_SET_TYPE_BOOL;
				// Find the first set player.
				foreach (cur : Player)
				{
					// Now ANY true value is true.
					if (__ps_data[e_PLAYER_SET_HACK_DATA][cur])
					{
						//_:addr = i;
						return cur;
					}
				}
				// No players specified.
				--__ps_pointer;
				return -1;
			}
		}
		// Will have returned by this point.
	}
	P:3("__PS_N called: %i, %i", _:addr, cur);
	// Each mode has a different end condition.
	switch (__ps_type{__ps_pointer})
	{
		#if defined _YSI_HAS_y_groups
			case e_PLAYER_SET_TYPE_GROUP:
			{
				cur = Iter_Func@GroupMember(cur, Group:_:addr);
				if (cur == -1)
				{
					--__ps_pointer;
				}
				return cur;
			}
		#endif
		case e_PLAYER_SET_TYPE_PLAYERS:
		{
			cur = Iter_Next(Player, cur);
			if (cur == Iter_End(Player))
			{
				--__ps_pointer;
				cur = -1;
			}
			return cur;
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			case e_PLAYER_SET_TYPE_BOTS:
			{
				cur = Iter_Next(Bot, cur);
				if (cur == Iter_End(Bot))
				{
					--__ps_pointer;
					cur = -1;
				}
				return cur;
			}
			case e_PLAYER_SET_TYPE_CHARACTERS:
			{
				cur = Iter_Next(Character, cur);
				if (cur == Iter_End(Character))
				{
					--__ps_pointer;
					cur = -1;
				}
				return cur;
			}
		#endif
		case e_PLAYER_SET_TYPE_PA:
		{
			cur = Iter_Func@PA(cur, Bit:__ps_stack[__ps_pointer]);
			if (cur == -1)
			{
				--__ps_pointer;
			}
			return cur;
		}
		case e_PLAYER_SET_TYPE_BOOL:
		{
			for ( ; ; )
			{
				cur = Iter_Next(Player, cur);
				if (cur == Iter_End(Player))
				{
					--__ps_pointer;
					return -1;
				}
				if (__ps_stack[__ps_pointer][cur])
				{
					// Don't need to check if they're connected as the data
					// comes directly from "foreach".
					break;
				}
				// Could add extra late checks here (Error, not Warning, now).
			}
			return cur;
		}
		case e_PLAYER_SET_TYPE_ID:
		{
			--__ps_pointer;
			return -1;
		}
		case e_PLAYER_SET_TYPE_ARRAY:
		{
			addr = __ps_addr_t:-1;
			while (++_:addr != MAX_PLAYERS)
			{
				if (__ps_stack[__ps_pointer][_:addr] == cur)
				{
					break;
				}
			}
			if (_:addr != MAX_PLAYERS)
			{
				while (++_:addr != MAX_PLAYERS)
				{
					cur = __ps_stack[__ps_pointer][_:addr];
					if (cur == INVALID_PLAYER_ID)
					{
						--__ps_pointer;
						return -1;
					}
					if (PS_IS_PLAYER_CONNECTED(cur))
					{
						return cur;
					}
				}
			}
			--__ps_pointer;
			return -1;
		}
		case e_PLAYER_SET_TYPE_CUSTOM:
		{
			if (cur == __ps_stack[__ps_pointer][0] >>> 8 & 0x0000FFFF)
			{
				addr = __ps_addr_t:0;
				while (++_:addr != MAX_PLAYERS)
				{
					cur = __ps_stack[__ps_pointer][_:addr];
					if (cur == INVALID_PLAYER_ID)
					{
						--__ps_pointer;
						return -1;
					}
					if (PS_IS_PLAYER_CONNECTED(cur))
					{
						return cur;
					}
				}
				--__ps_pointer;
				return -1;
			}
			else
			{
				addr = __ps_addr_t:0;
				while (++_:addr != MAX_PLAYERS)
				{
					if (__ps_stack[__ps_pointer][_:addr] == cur)
					{
						break;
					}
				}
				if (_:addr != MAX_PLAYERS)
				{
					while (++_:addr != MAX_PLAYERS)
					{
						cur = __ps_stack[__ps_pointer][_:addr];
						if (cur == INVALID_PLAYER_ID)
						{
							--__ps_pointer;
							return -1;
						}
						if (PS_IS_PLAYER_CONNECTED(cur))
						{
							return cur;
						}
					}
				}
				--__ps_pointer;
				return -1;
			}
		}
	}
	--__ps_pointer;
	return -1;
}

#define Iterator@PS iterstart(-1)

// This function gets the required data from custom format (enum) arrays.
stock __PS_C(source[MAX_PLAYERS][], idx)
{
	static
		sFake[MAX_PLAYERS] = {(INVALID_PLAYER_ID << 8) | 0x0F0000F0};
	new
		ret = (__ps_data[e_PLAYER_SET_HACK_DATA] = sFake),
		e_PLAYER_SET_HACK:i = e_PLAYER_SET_HACK:0;
	foreach (new playerid : Player)
	{
		if (source[playerid][idx])
		{
			if (i)
			{
				__ps_data[i++] = playerid;
			}
			else
			{
				__ps_data[i++] = (playerid << 8) | 0x0F0000F0;
			}
		}
	}
	if (i < e_PLAYER_SET_HACK:MAX_PLAYERS)
	{
		__ps_data[i] = INVALID_PLAYER_ID;
	}
	return ret;
}

stock bool:__PS_A(@PlayerSet:addr, PlayerArray:ret<MAX_PLAYERS>)
{
	if (ret[0])
	{
		return false;
	}
	PA_FastInit(ret);
	foreach (new a : PS(addr))
	{
		PA_Let(ret, a);
	}
	return true;
}

// This SHOULD handle excess parameters correctly, simply because I left out the
// extra brackets.
#define PSF:%0(%1) %0(__ps_addr_t:__ps_data[e_PLAYER_SET_HACK_PA]=__ps_addr_t:%1)

// This redefines e_PLAYER_SET_HACK_DATA in the case of passing player arrays.
#define e_PLAYER_SET_HACK_PA]=__ps_addr_t:@%0) e_PLAYER_SET_HACK_DATA]=__ps_addr_t:%0)

// Don't actually need the "@".
#define __ps_data[e_PLAYER_SET_HACK_DATA]=%0<%1> __ps_addr_t:__PS_C(%0,%1)
#define __PS_C(@%0,%1) __PS_C(%0,%1)

