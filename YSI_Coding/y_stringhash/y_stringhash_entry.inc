#if defined _INC_y_stringhash
	#endinput
#endif
#define _INC_y_stringhash

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

#include "..\..\YSI_Core\y_utils"

// Note: H_a, H_b, H_c, H_d, H_f and H_g are defined here, H_e in y_amx, H_z in
// y_masteronce, H_u in y_users, H_y in y_timers.
// ===================
//  Determine version 
// ===================

// Entry.
#define _H (_:_H_1:_H_0
#define _I (_:_H_3:_H_2
#define _H@b (_:_H_1:_H_0
#define _I@b (_:_H_3:_H_2
// Old.
#define _H_0(%0) HASH@bernstein(%0)5381)
#define _H_2(%0) HASHi@bernstein(%0)5381)
// New.
#define _H_1:_H_0<%0> HASh@bernstein(%0))
#define _H_3:_H_2<%0> HAShi@bernstein(%0))

// Entry.
#define _H@f (_:_H0@f:_H1@f
#define _I@f (_:_H2@f:_H3@f
// Old.
#define _H1@f(%0) HASH@fnv1(%0)2166136261)
#define _H3@f(%0) HASHi@fnv1(%0)2166136261)
// New.
#define _H0@f:_H1@f<%0> HASh@fnv1(%0))
#define _H2@f:_H3@f<%0> HAShi@fnv1(%0))

// Entry.
#define _H@a (_:_H0@a:_H1@a
#define _I@a (_:_H2@a:_H3@a
// Old.
#define _H1@a(%0) HASH@fnv1a(%0)2166136261)
#define _H3@a(%0) HASHi@fnv1a(%0)2166136261)
// New.
#define _H0@a:_H1@a<%0> HASh@fnv1a(%0))
#define _H2@a:_H3@a<%0> HAShi@fnv1a(%0))

// Entry.
#define HASH  (_:_H_4:_H_5
#define HASHi (_:_H_6:_H_7
// Old.
#define _H_5(%0,%1) HASH@%0(%1))
#define _H_7(%0,%1) HASHi@%0(%1))
// New.
#define _H_4:_H_5:%0<%1> HASh@%0(%1))
#define _H_6:_H_7:%0<%1> HAShi@%0(%1))

// Empty strings.
#define HASH_:%0(,@,@)%1) %1)

#define _Y_HASH_H(%0,%1)(%9) @B%0:@A0:@A1:@A2:@A3:@A4:@A5:@A6:@A7:@A8:@A9:@Aa:@Ab:@Ac:@Ad:@Ae:@Af:@Ag:@Ah:@Ai:@Aj:@Ak:@Al:@Am:@An:@Ao:@Ap:@Aq:@Ar:@As:@At:@Au:@Av:@Aw:@Ax:@Ay:@Az:@AA:@AB:@AC:@AD:@AE:@AF:@AG:@AH:@AI:@AJ:@AK:@AL:@AM:@AN:@AO:@AP:@AQ:@AR:@AS:@AT:@AU:@AV:@AW:@AX:@AY:@AZ:@A_:@A@:@B_:@B%1$(%9)$
#define _Y_HASH_I(%0,%1)(%9) @B%0:@A0:@A1:@A2:@A3:@A4:@A5:@A6:@A7:@A8:@A9:@Aa:@Ab:@Ac:@Ad:@Ae:@Af:@Ag:@Ah:@Ai:@Aj:@Ak:@Al:@Am:@An:@Ao:@Ap:@Aq:@Ar:@As:@At:@Au:@Av:@Aw:@Ax:@Ay:@Az:@Ba:@Bb:@Bc:@Bd:@Be:@Bf:@Bg:@Bh:@Bi:@Bj:@Bk:@Bl:@Bm:@Bn:@Bo:@Bp:@Bq:@Br:@Bs:@Bt:@Bu:@Bv:@Bw:@Bx:@By:@Bz:@A_:@A@:@B_:@B%1$(%9)$

// Bernstein
#define @B0:%9$()$ 5381
#define @B1$(<%0>%1) @B2:%0@B3:<>%1
#define @B2:%9<%0>%1) %9(@B2:%0)*33^%1)
#define @B3:(%0)*%1$ 5381*%1

// FNV1
#define @B4:%9$()$ 2166136261
#define @B5$(<%0>%1) @B6:%0@B7:<>%1
#define @B6:%9<%0>%1) %9(@B6:%0)*16777619^%1)
#define @B7:(%0)*%9^%1$ 84696351^%1

// FNV1a
#define @B8:%9$()$ 2166136261
#define @B9$(<%0>%1) (@BA:%0@BB:<>%1>
#define @BA:%9<%0>%1>%2) %9(@BA:%0^%1)*16777619>%2)
#define @BB:(%0^%1)%2>$ 2166136261^%1)%2

// Entries
#define HASh@bernstein(%9) _Y_HASH_H(0,1)(%9)
#define HAShi@bernstein(%9) _Y_HASH_I(0,1)(%9)
#define HASh@fnv1(%9) _Y_HASH_H(4,5)(%9)
#define HAShi@fnv1(%9) _Y_HASH_I(4,5)(%9)
#define HASh@fnv1a(%9) _Y_HASH_H(8,9)(%9)
#define HAShi@fnv1a(%9) _Y_HASH_I(8,9)(%9)

/*

    888b      88                                    ,ad8888ba,                                            88 
    8888b     88                                   d8"'    `"8b                                           88 
    88 `8b    88                                  d8'                                                     88 
    88  `8b   88  ,adPPYba, 8b      db      d8    88            ,adPPYYba, ,adPPYba,  ,adPPYba,   ,adPPYb,88 
    88   `8b  88 a8P_____88 `8b    d88b    d8'    88            ""     `Y8 I8[    "" a8P_____88  a8"    `Y88 
    88    `8b 88 8PP"""""""  `8b  d8'`8b  d8'     Y8,           ,adPPPPP88  `"Y8ba,  8PP"""""""  8b       88 
    88     `8888 "8b,   ,aa   `8bd8'  `8bd8'       Y8a.    .a8P 88,    ,88 aa    ]8I "8b,   ,aa  "8a,   ,d88 
    88      `888  `"Ybbd8"'     YP      YP          `"Y8888Y"'  `"8bbdP"Y8 `"YbbdP"'  `"Ybbd8"'   `"8bbdP"Y8 

*/

// ================
//  Case sensitive 
// ================

// Test for the current character.  Numbers MUST be first!
#define @A0:%9$(%10%0)$ @A0:%9$(<%1>'0'%0)$
#define @A1:%9$(%11%0)$ @A1:%9$(<%1>'1'%0)$
#define @A2:%9$(%12%0)$ @A2:%9$(<%1>'2'%0)$
#define @A3:%9$(%13%0)$ @A3:%9$(<%1>'3'%0)$
#define @A4:%9$(%14%0)$ @A4:%9$(<%1>'4'%0)$
#define @A5:%9$(%15%0)$ @A5:%9$(<%1>'5'%0)$
#define @A6:%9$(%16%0)$ @A6:%9$(<%1>'6'%0)$
#define @A7:%9$(%17%0)$ @A7:%9$(<%1>'7'%0)$
#define @A8:%9$(%18%0)$ @A8:%9$(<%1>'8'%0)$
#define @A9:%9$(%19%0)$ @A9:%9$(<%1>'9'%0)$

#define @Aa:%9$(%1a%0)$ @Aa:%9$(<%1>97%0)$
#define @Ab:%9$(%1b%0)$ @Ab:%9$(<%1>98%0)$
#define @Ac:%9$(%1c%0)$ @Ac:%9$(<%1>99%0)$
#define @Ad:%9$(%1d%0)$ @Ad:%9$(<%1>100%0)$
#define @Ae:%9$(%1e%0)$ @Ae:%9$(<%1>101%0)$
#define @Af:%9$(%1f%0)$ @Af:%9$(<%1>102%0)$
#define @Ag:%9$(%1g%0)$ @Ag:%9$(<%1>103%0)$
#define @Ah:%9$(%1h%0)$ @Ah:%9$(<%1>104%0)$
#define @Ai:%9$(%1i%0)$ @Ai:%9$(<%1>105%0)$
#define @Aj:%9$(%1j%0)$ @Aj:%9$(<%1>106%0)$
#define @Ak:%9$(%1k%0)$ @Ak:%9$(<%1>107%0)$
#define @Al:%9$(%1l%0)$ @Al:%9$(<%1>108%0)$
#define @Am:%9$(%1m%0)$ @Am:%9$(<%1>109%0)$
#define @An:%9$(%1n%0)$ @An:%9$(<%1>110%0)$
#define @Ao:%9$(%1o%0)$ @Ao:%9$(<%1>111%0)$
#define @Ap:%9$(%1p%0)$ @Ap:%9$(<%1>112%0)$
#define @Aq:%9$(%1q%0)$ @Aq:%9$(<%1>113%0)$
#define @Ar:%9$(%1r%0)$ @Ar:%9$(<%1>114%0)$
#define @As:%9$(%1s%0)$ @As:%9$(<%1>115%0)$
#define @At:%9$(%1t%0)$ @At:%9$(<%1>116%0)$
#define @Au:%9$(%1u%0)$ @Au:%9$(<%1>117%0)$
#define @Av:%9$(%1v%0)$ @Av:%9$(<%1>118%0)$
#define @Aw:%9$(%1w%0)$ @Aw:%9$(<%1>119%0)$
#define @Ax:%9$(%1x%0)$ @Ax:%9$(<%1>120%0)$
#define @Ay:%9$(%1y%0)$ @Ay:%9$(<%1>121%0)$
#define @Az:%9$(%1z%0)$ @Az:%9$(<%1>122%0)$

#define @AA:%9$(%1A%0)$ @AA:%9$(<%1>65%0)$
#define @AB:%9$(%1B%0)$ @AB:%9$(<%1>66%0)$
#define @AC:%9$(%1C%0)$ @AC:%9$(<%1>67%0)$
#define @AD:%9$(%1D%0)$ @AD:%9$(<%1>68%0)$
#define @AE:%9$(%1E%0)$ @AE:%9$(<%1>69%0)$
#define @AF:%9$(%1F%0)$ @AF:%9$(<%1>70%0)$
#define @AG:%9$(%1G%0)$ @AG:%9$(<%1>71%0)$
#define @AH:%9$(%1H%0)$ @AH:%9$(<%1>72%0)$
#define @AI:%9$(%1I%0)$ @AI:%9$(<%1>73%0)$
#define @AJ:%9$(%1J%0)$ @AJ:%9$(<%1>74%0)$
#define @AK:%9$(%1K%0)$ @AK:%9$(<%1>75%0)$
#define @AL:%9$(%1L%0)$ @AL:%9$(<%1>76%0)$
#define @AM:%9$(%1M%0)$ @AM:%9$(<%1>77%0)$
#define @AN:%9$(%1N%0)$ @AN:%9$(<%1>78%0)$
#define @AO:%9$(%1O%0)$ @AO:%9$(<%1>79%0)$
#define @AP:%9$(%1P%0)$ @AP:%9$(<%1>80%0)$
#define @AQ:%9$(%1Q%0)$ @AQ:%9$(<%1>81%0)$
#define @AR:%9$(%1R%0)$ @AR:%9$(<%1>82%0)$
#define @AS:%9$(%1S%0)$ @AS:%9$(<%1>83%0)$
#define @AT:%9$(%1T%0)$ @AT:%9$(<%1>84%0)$
#define @AU:%9$(%1U%0)$ @AU:%9$(<%1>85%0)$
#define @AV:%9$(%1V%0)$ @AV:%9$(<%1>86%0)$
#define @AW:%9$(%1W%0)$ @AW:%9$(<%1>87%0)$
#define @AX:%9$(%1X%0)$ @AX:%9$(<%1>88%0)$
#define @AY:%9$(%1Y%0)$ @AY:%9$(<%1>89%0)$
#define @AZ:%9$(%1Z%0)$ @AZ:%9$(<%1>90%0)$

#define @A_:%9$(%1_%0)$ @A_:%9$(<%1>95%0)$
#define @A@:%9$(%1@%0)$ @A@:%9$(<%1>64%0)$

#define @B_:%9$(%1\32;%0)$ @B_:%9$(<%1>32%0)$

// ==================
//  Case insensitive 
// ==================

#define @Ba:%9$(%1A%0)$ @Ba:%9$(<%1>97%0)$
#define @Bb:%9$(%1B%0)$ @Bb:%9$(<%1>98%0)$
#define @Bc:%9$(%1C%0)$ @Bc:%9$(<%1>99%0)$
#define @Bd:%9$(%1D%0)$ @Bd:%9$(<%1>100%0)$
#define @Be:%9$(%1E%0)$ @Be:%9$(<%1>101%0)$
#define @Bf:%9$(%1F%0)$ @Bf:%9$(<%1>102%0)$
#define @Bg:%9$(%1G%0)$ @Bg:%9$(<%1>103%0)$
#define @Bh:%9$(%1H%0)$ @Bh:%9$(<%1>104%0)$
#define @Bi:%9$(%1I%0)$ @Bi:%9$(<%1>105%0)$
#define @Bj:%9$(%1J%0)$ @Bj:%9$(<%1>106%0)$
#define @Bk:%9$(%1K%0)$ @Bk:%9$(<%1>107%0)$
#define @Bl:%9$(%1L%0)$ @Bl:%9$(<%1>108%0)$
#define @Bm:%9$(%1M%0)$ @Bm:%9$(<%1>109%0)$
#define @Bn:%9$(%1N%0)$ @Bn:%9$(<%1>110%0)$
#define @Bo:%9$(%1O%0)$ @Bo:%9$(<%1>111%0)$
#define @Bp:%9$(%1P%0)$ @Bp:%9$(<%1>112%0)$
#define @Bq:%9$(%1Q%0)$ @Bq:%9$(<%1>113%0)$
#define @Br:%9$(%1R%0)$ @Br:%9$(<%1>114%0)$
#define @Bs:%9$(%1S%0)$ @Bs:%9$(<%1>115%0)$
#define @Bt:%9$(%1T%0)$ @Bt:%9$(<%1>116%0)$
#define @Bu:%9$(%1U%0)$ @Bu:%9$(<%1>117%0)$
#define @Bv:%9$(%1V%0)$ @Bv:%9$(<%1>118%0)$
#define @Bw:%9$(%1W%0)$ @Bw:%9$(<%1>119%0)$
#define @Bx:%9$(%1X%0)$ @Bx:%9$(<%1>120%0)$
#define @By:%9$(%1Y%0)$ @By:%9$(<%1>121%0)$
#define @Bz:%9$(%1Z%0)$ @Bz:%9$(<%1>122%0)$

// ============
//  Other code 
// ============

enum e_HASH_TYPE:
{
	hash_bernstein,
	hash_fnv1,
	hash_fnv1a
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to hash.</param>
 * <param name="sensitive">Wether the hash is case sensitive or not.</param>
 * <returns>
 *  The reverse Bernstein hash of the string.
 * </returns>
 * <remarks>
 *  Based on Bernstein hash, but backwards to match the macros.  The only
 *  characters which can be used in the compile time version of this code are:
 *  a-z, A-Z, 0-9, _ and space.
 *
 * native Hash(str[]);
 *
 *  NOW FORWARD AGAIN.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock YHash(const str[], bool:sensitive = true, e_HASH_TYPE:type = hash_bernstein, len = cellmax, pack = false)
{
	if (str[str[0] == '\1'] == '\0')
	{
		// NULL.
		switch (type)
		{
		case hash_fnv1:
			return 2166136261;
		case hash_fnv1a:
			return 2166136261;
		case hash_bernstein:
			return 5381;
		}
	}
	P:3("YHash called: \"%s\", %i, %i, %i, %i", str, _:sensitive, _:type, len, pack);
	len = min(len, strlen(str));
	new
		i = 0;
	if (str[0] > 255)
	{
		switch (type)
		{
			case hash_bernstein:
			{
				new
					hash = 5381;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 33 ^ str{i++};
					}
				}
				else
				{
					while (i != len)
					{
						pack = str{i++},
						hash = hash * 33 ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack);
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
						pack = str{i++},
						hash = hash * 16777619 ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack);
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
						pack = str{i++},
						hash = (hash ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack)) * 16777619;
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
					hash = 5381;
				if (sensitive)
				{
					while (i != len)
					{
						hash = hash * 33 ^ str[i++];
					}
				}
				else
				{
					while (i != len)
					{
						pack = str[i++],
						hash = hash * 33 ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack);
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
						pack = str[i++],
						hash = hash * 16777619 ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack);
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
						pack = str[i++],
						hash = (hash ^ (IS_IN_RANGE(pack, 'A', 'Z' + 1) ? pack | 0x20 : pack)) * 16777619;
					}
				}
				return hash;
			}
		}
	}
	return -1;
}

#include "y_stringhash_bernstein"
#include "y_stringhash_fnv1a"
#include "y_stringhash_fnv1"

#if defined YSI_TESTS
	#include "y_stringhash_tests"
#endif

