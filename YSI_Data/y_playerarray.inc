#if defined _INC_y_playerarray
	#endinput
#endif
#define _INC_y_playerarray

/**
 * <library name="y_playerarray">
 * <section>
 *  Description
 * </section>
 *  This code provides arrays of players who can do things.  This is for support
 *  of the text system which can take arrays of player ids, bit arrays or just a
 *  single ID.
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

#include "..\YSI_Internal\y_version"

#include <a_samp>
#include "..\YSI_Core\y_debug"
#include "..\YSI_Data\y_bit"

#define PA_TYPE_NONE                    (-1)
#define PA_TYPE_BOOL                    (-2)
#define PA_TYPE_ID                      (-3)
#define PA_TYPE_PA                      (-4)

#if defined _YSI_SPECIAL_DEBUG
	#define PS_IS_PLAYER_CONNECTED(%0) (%0 != INVALID_PLAYER_ID)
#else
	#define PS_IS_PLAYER_CONNECTED IsPlayerConnected
#endif

// Redefined later on.  This is just for internal use.
#define PlayerArray:%0<%1> Bit:%0[%1]

#define PA_INIT:%1, Bit:PA_TYPE_PA,Bit:(-1*_:%1),Bit:(-1*_:%1),

stock PA_Init(Bit:a[], bool:init = false, s = bits<MAX_PLAYERS>)
{
	P:3("PA_Init called: %i, %i, %i", _:a, _:init, s);
	//--s;
	new
		Bit:m = init ? (Bit:-1) : (Bit:0);
	a[0] = Bit:PA_TYPE_PA;
	while (s)
	{
		a[s--] = m;
	}
}

#define PA_FastInit(%0) %0[0]=Bit:PA_TYPE_PA

#define PA_GetBit(%1,%2) (%1[((%2)>>>CELLSHIFT)+1]&Bit:(1<<((%2)&cellbits-1)))

#define PA_Get(%1,%2) bool:PA_GetBit(Bit:%1,_:%2)

#define PA_Let(%1,%2) %1[((%2)>>>CELLSHIFT)+1]|=Bit:(1<<((%2)&cellbits-1))

#define PA_Vet(%1,%2) %1[((%2)>>>CELLSHIFT)+1]&=Bit:~(1<<((%2)&cellbits-1))

#define PA_GetCount(%1) Bit_GetCount(%1[1],bits<MAX_PLAYERS>)

#define PA_Slot(%0) (Bit_Slot(%0) + 1)
#define PA_Mask(%0) (Bit_Mask(%0))

//#define PA_Set(%0,%1,%2) ((%2)?Bit_Let(%0,(%1)):Bit_Vet(%0,(%1)))
stock PA_Set(PlayerArray:d<>, slot, bool:set)
{
	P:3("PA_Set called: %s, %i, %i", Bit_Display(Bit:d[1]), slot, _:set);
	if (set)
	{
		PA_Let(d, slot);
		return 1;
	}
	else
	{
		PA_Vet(d, slot);
		return 0;
	}
}

stock Iter_Func@PA(start, PlayerArray:data<>)
{
	P:3("YSI_gAPAFunc called: %s, %i", Bit_Display(Bit:data[1]), start);
	++start;
	YSI_gAPAFunc_loop:
	new
		cur,
		i = Bit_Slot(start) + 1;
	if ((cur = (_:data[i] & (~((1 << start) - 1)))))
	{
		new
			ret = ((i - 1) * cellbits) + Cell_GetLowestBit(cur);
		// I'd like to replace this with code which doesn't call
		// IsPlayerConnected and doesn't use "goto", but it avoids massive tail
		// recursion (well, it is tail recursion which I've inlined).
		if (PS_IS_PLAYER_CONNECTED(ret))
		{
			return ret;
		}
		else
		{
			//return YSI_gAPAFunc(data, ret);
			start = ret + 1;
			goto YSI_gAPAFunc_loop;
		}
	}
	++i;
	while (i != bits<MAX_PLAYERS> + 1)
	{
		if ((cur = _:data[i]))
		{
			new
				ret = ((i - 1) * cellbits) + Cell_GetLowestBit(cur);
			if (PS_IS_PLAYER_CONNECTED(ret))
			{
				return ret;
			}
			else
			{
				//return YSI_gAPAFunc(data, ret);
				start = ret + 1;
				goto YSI_gAPAFunc_loop;
			}
		}
		++i;
	}
	return -1;
}

#define Iterator@PA iterstart(-1)

#undef PlayerArray

#define PlayerArray:%0<%1> Bit:%0[bits<%1>+1]//={Bit:-1}

