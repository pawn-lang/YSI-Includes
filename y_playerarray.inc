/**--------------------------------------------------------------------------**\
					========================================
					 y_playerarray - Bit arrays of players! 
					========================================
Description:
	This code provides arrays of players who can do things.  This is for support
	of the text system which can take arrays of player ids, bit arrays or just a
	single ID.
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
	
	The Original Code is the YSI playerarray include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk
	
	Thanks:
		Peter, Cam - Support.
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
		Thiadmer - PAWN.
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
Version:
	1.0
Changelog:
	25/02/11:
		Scrapped pointless "playing" code I was unhappy with.
	29/11/10:
		First version
</remarks>
\**--------------------------------------------------------------------------**/

#include "internal\y_version"

#include <a_samp>
#include "y_debug"
#include "y_bit"

#define PA_TYPE_NONE                    (-1)
#define PA_TYPE_BOOL                    (-2)
#define PA_TYPE_ID                      (-3)
#define PA_TYPE_PA                      (-4)

#if defined _YSI_SPECIAL_DEBUG
	#define PS_IS_PLAYER_CONNECTED(%0) (%0 != INVALID_PLAYER_ID)
#else
	#define PS_IS_PLAYER_CONNECTED IsPlayerConnected
#endif

#define PlayerArray:%0<%1> Bit:%0[%1] //={Bit:PA_TYPE_PA,Bit:0,Bit:0,...}

//#define Bit:%0[%1,%2] Bit:%0[%1]={Bit:PA_TYPE_PA,Bit:(-1*_:%2),Bit:(-1*_:%2),...}

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

/*stock YSI_gSPAFunc(PlayerArray:data<>)
{
	P:3("YSI_gSPA called: %s", Bit_Display(Bit:data[1]));
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
		if ((cur = _:data[i]))
		{
			// http://supertech.csail.mit.edu/papers/debruijn.pdf
			new
				ret = ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
			if (PS_IS_PLAYER_CONNECTED(ret))
			{
				return ret;
			}
			else
			{
				return YSI_gAPAFunc(data, ret);
			}
		}
	}
	return -1;
}*/

stock PA@YSII_Ag(PlayerArray:data<>, start)
{
	P:3("YSI_gAPAFunc called: %s, %i", Bit_Display(Bit:data[1]), start);
	static const
		scDeBruijn[] =
			{
				0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8,
				31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
			};
	++start;
	YSI_gAPAFunc_loop:
	new
		cur,
		i = Bit_Slot(start) + 1;
	if ((cur = (_:data[i] & (~((1 << start) - 1)))))
	{
		new
			ret = ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
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
				ret = ((i - 1) * cellbits) + scDeBruijn[((cur & -cur) * 0x077CB531) >>> 27];
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

//#define YSI_gAPA(%0)[%1] YSI_gAPAFunc(%0,%1)
//#define YSI_gSPS YSI_gSPA
//#define YSI_gAPS YSI_gAPA

//#define PA(%0)_YSII_Sg;_:%1!=-1;%2=_Y_ITER_ARRAY:%8PA(%3)_YSII_Ag[%4] YSI_gSPAFunc(%0);_:%1!=-1;%2=YSI_gAPAFunc(%3,%4)

#undef PlayerArray

#define PlayerArray:%0<%1> Bit:%0[bits<%1>+1]//={Bit:-1}
