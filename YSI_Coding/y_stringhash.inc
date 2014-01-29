/**--------------------------------------------------------------------------**\
					========================================
					 y_stringhash - Fast string comparisons 
					========================================
Description:
	Allows you to hash strings at compile time to use them in a switch.
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
	
	The Original Code is the YSI stringhash include.
	
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
	06/03/11:
		Changed the order of some letters to better support numbers in _I.
	01/03/11:
		Rewrote compile-time hashes to not require commas.
	25/10/10:
		Updated comments.
		Added to YSI 1.0.
		Added FNV1 and FNV1a hashes to avoid collisions.
	19/08/10:
		First version.
Functions:
	stock:
		YHash - Generate a string hash at run time.
Definitions:
	_H - Generate a string hash at compile time.
	_I - Generate a case insensitive string hash at compile time.
\**--------------------------------------------------------------------------**/

#if defined _INC_y_stringhash
	#endinput
#endif
#define _INC_y_stringhash

#include "..\YSI_Internal\y_version"
#include "..\YSI_Core\y_debug"

// Note: H_a, H_b, H_c, H_d, H_f and H_g are defined here, H_e in y_amx, H_z in
// y_masteronce, H_u in y_users, H_y in y_timers.
// ===================
//  Determine version 
// ===================

// Entry.
#define _H (_:_H_1:_H_0
#define _I (_:_H_3:_H_2
// Old.
#define _H_0(%0) HASH@bernstein(%0))
#define _H_2(%0) HASHi@bernstein(%0))
// New.
#define _H_1:_H_0<%0> hb:@Ba:H_Nba(%0)H_Eb:|||-1|||)
#define _H_3:_H_2<%0> hc:@Ca:H_Nca(%0)H_Ec:|||-1|||)

// Entry.
#define _H@b (_:_H0@b:_H1@b
#define _I@b (_:_H2@b:_H3@b
// Old.
#define _H1@b(%0) HASH@bernstein(%0))
#define _H3@b(%0) HASHi@bernstein(%0))
// New.
#define _H0@b:_H1@b<%0> hb:@Ba:H_Nba(%0)H_Eb:|||-1|||)
#define _H2@b:_H3@b<%0> hc:@Ca:H_Nca(%0)H_Ec:|||-1|||)

// Entry.
#define _H@f (_:_H0@f:_H1@f
#define _I@f (_:_H2@f:_H3@f
// Old.
#define _H1@f(%0) HASH@fnv1(%0))
#define _H3@f(%0) HASHi@fnv1(%0))
// New.
#define _H0@f:_H1@f<%0> hg:@Ga:H_Nga(%0)H_Eg:|||2166136261|||)
#define _H2@f:_H3@f<%0> hf:@Fa:H_Nfa(%0)H_Ef:|||2166136261|||)

// Entry.
#define _H@a (_:_H0@a:_H1@a
#define _I@a (_:_H2@a:_H3@a
// Old.
#define _H1@a(%0) HASH@fnv1a(%0))
#define _H3@a(%0) HASHi@fnv1a(%0))
// New.
#define _H0@a:_H1@a<%0> ha:@Aa:H_Naa(%0)H_Ea:|||2166136261|||)
#define _H2@a:_H3@a<%0> hd:@Da:H_Nda(%0)H_Ed:|||2166136261|||)

// Entry.
#define HASH  (_:_H_4:_H_5
#define HASHi (_:_H_6:_H_7
// Old.
#define _H_5(%0,%1) HASH@%0(%1))
#define _H_7(%0,%1) HASHi@%0(%1))
// New.
#define _H_4:_H_5:%0<%1> HASh@%0(%1)
#define _H_6:_H_7:%0<%1> HAShi@%0(%1)

#define HASh@bernstein(%0)  hb:@Ba:H_Nba(%0)H_Eb:|||-1|||)
#define HAShi@bernstein(%0) hc:@Ca:H_Nca(%0)H_Ec:|||-1|||)
#define HASh@fnv1(%0)  hg:@Ga:H_Nga(%0)H_Eg:|||2166136261|||)
#define HAShi@fnv1(%0) hf:@Fa:H_Nfa(%0)H_Ef:|||2166136261|||)
#define HASh@fnv1a(%0)  ha:@Aa:H_Naa(%0)H_Ea:|||2166136261|||)
#define HAShi@fnv1a(%0) hd:@Da:H_Nda(%0)H_Ed:|||2166136261|||)

// ============
//  Other code 
// ============

enum e_HASH_TYPE
{
	hash_bernstein,
	hash_fnv1,
	hash_fnv1a
}

/**--------------------------------------------------------------------------**\
<summary>Hash</summary>
<param name="str">The string to hash.</param>
<param name="sensitive">Wether the hash is case sensitive or not.</param>
<returns>
	The reverse Bernstein hash of the string.
</returns>
<remarks>
	Based on Bernstein hash, but backwards to match the macros.  The only
	characters which can be used in the compile time version of this code are:
	a-z, A-Z, 0-9, _ and space.

native Hash(str[]);

	NOW FORWARD AGAIN.
</remarks>
\**--------------------------------------------------------------------------**/

stock YHash(const str[], bool:sensitive = true, e_HASH_TYPE:type = hash_bernstein, len = -1, pack = false)
{
	#pragma unused pack
	P:3("YHash called: \"%s\", %i, %i, %i, %i", str, _:sensitive, _:type, len, pack);
	
	//pack = str[0] > 255;
	
	if (len < 0) len = strlen(str);
	else len = min(len, strlen(str));
	new
		i = 0;
	if (str[0] > 255)
	{
		switch (type)
		{
			case hash_bernstein:
			{
				new
					hash = -1;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 33 + str{i++};
					}
				}
				else
				{
					while (i != len)
					{
						hash = hash * 33 + toupper(str{i++});
					}
				}
				return hash;
			}
			case hash_fnv1:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 16777619 ^ str{i++};
					}
				}
				else
				{
					while (i != len)
					{
						hash = hash * 16777619 ^ toupper(str{i++});
					}
				}
				return hash;
			}
			case hash_fnv1a:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (i != len)
					{
						hash = (hash ^ str{i++}) * 16777619;
					}
				}
				else
				{
					while (i != len)
					{
						hash = (hash ^ toupper(str{i++})) * 16777619;
					}
				}
				return hash;
			}
		}
	}
	else
	{
		switch (type)
		{
			case hash_bernstein:
			{
				new
					hash = -1;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 33 + str[i++];
					}
				}
				else
				{
					while (i != len)
					{
						//printf("hash: %d, old: %d, add: %d", hash, str[i], toupper(str[i]));
						hash = hash * 33 + toupper(str[i++]);
					}
				}
				return hash;
			}
			case hash_fnv1:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 16777619 ^ str[i++];
					}
				}
				else
				{
					while (i != len)
					{
						hash = hash * 16777619 ^ toupper(str[i++]);
					}
				}
				return hash;
			}
			case hash_fnv1a:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (i != len)
					{
						hash = (hash ^ str[i++]) * 16777619;
					}
				}
				else
				{
					while (i != len)
					{
						hash = (hash ^ toupper(str[i++])) * 16777619;
					}
				}
				return hash;
			}
		}
	}
	return -1;
}

#include "y_stringhash/bernstein"
#include "y_stringhash/fnv1a"
#include "y_stringhash/fnv1"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_stringhash/tests"
#endif
