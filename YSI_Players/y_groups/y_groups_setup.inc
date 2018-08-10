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

#if defined _INC_y_groups_setup
	#endinput
#endif
#define _INC_y_groups_setup

#define _GROUP_LOCAL_NAME               _GROUP_MAKE_TAG:e

// Dummy values.
#define INVALID_GROUP (Group:-1)

// IF THIS VALUE EVER CHANGES, CHANGE y_playerset AS WELL - IT MAY BE INCLUDED
// BEFORE y_groups BUT NEEDS THE MACRO.
//
// TODO: Fix that fact with better y_groups segmenting.
#define GROUP_MASK                      (Group:0x80000000)

#define GROUP_GLOBAL                    (Group:_MAX_GROUPS | GROUP_MASK) //-1)
#define GROUP_FIX(%0)                   ((%0)&=~GROUP_MASK)
#define GROUP_TEMP_FIX(%0)              ((%0)&~GROUP_MASK)
#define GROUP_MANGLE(%0)                (Group:(%0) | GROUP_MASK)

#define GFOREIGN__%1(%2); _GROUP_MAKE_NAME<FOREIGN__%1>(%2);
#define GGLOBAL__%1(%2) _GROUP_MAKE_NAME<GLOBAL__%1>(%2)
#define GPUBLIC__ MASTER_FUNC__
//#define _GROUP_SET_PLAYER _GROUP_MAKE_NAME<..._SetPlayer>

#define _GROUP_MAKE_FUNC<%4>:%0<%1> u@(u[_:_Y_G@C4:_Y_G@C5:0]);%0<%1><%4>$

#define _Y_G@C4:_Y_G@C5:%0;%1<%2:%3><%4>$ %0;%1<%2:%4%3>
#define _Y_G@C5:%0;%1<%3><%4>$ %0;%1<%4%3>

// This is currently "leaking" code to the final script - code that we don't
// want!  No longer.
#if defined _YSI_HAS_y_groups || __COMPILER_1ST_PASS
	#define NO_GROUPS<%1>(%0) if(%1_InitialiseFromGroups(%0))
#else
	#define NO_GROUPS<%1>(%0)
#endif

// Chain init functions.
#define GROUP_CHAIN%9<%0>(%1) (J@=_:(_Y_G@C_YES:_Y_G@C_NO:%0%9|||(_:_Y_G@C3:_Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1))))

#define _Y_G@C3:_Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1,%2,%3) _Y_G@C_3(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1,_:%2,_:%3|||)
#define _Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1,%2) _Y_G@C_2(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1,_:%2|||)
#define _Y_G@C0:_Y_G@C1:%0() _Y_G@C_0(%0)
#define _Y_G@C1:%0(%1) _Y_G@C_1(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1|||)
#define _Y_G@C_YES:_Y_G@C_NO:%0?||| (!(%0))?(0):
#define _Y_G@C_NO:%0|||
// Can strip out multiple brackets in one go.
#define _Y_G@P:%0[]%1||| _Y_G@P:%0%1|||
#define _Y_G@Q:%0&%1||| _Y_G@Q:%0%1|||
#define _Y_G@R:%0||| %0

#if !defined MAX_GROUP_NAME
	#define MAX_GROUP_NAME              (24)
#endif

#if defined MAX_GROUPS
	// Round up to the next nice number (or not, we could with long macros).
	#define _MAX_GROUPS                  (_:MAX_GROUPS)
#else
	// 1 less than a nice number (with good reason).
	#define _MAX_GROUPS                  (_:127)
#endif

#define _MAX_GROUPS_G (_:_MAX_GROUPS + 1)

// Note that these macros always do the last element before all the others
// (which may or may not be in order).  This is as the last element holds the
// "default" group, which is the most likely to be a good match.
#if _MAX_GROUPS < 32
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[0]&%1[0])
#elseif _MAX_GROUPS < 64
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[1]&%1[1]||%0[0]&%1[0])
#elseif _MAX_GROUPS < 96
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[2]&%1[2]||%0[0]&%1[0]||%0[1]&%1[1])
#elseif _MAX_GROUPS < 128
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[3]&%1[3]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2])
#elseif _MAX_GROUPS < 160
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[4]&%1[4]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3])
#elseif _MAX_GROUPS < 192
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[5]&%1[5]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4])
#elseif _MAX_GROUPS < 224
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[6]&%1[6]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5])
#elseif _MAX_GROUPS < 256
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[7]&%1[7]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6])
#elseif _MAX_GROUPS < 288
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[8]&%1[8]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7])
#elseif _MAX_GROUPS < 320
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[9]&%1[9]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8])
#elseif _MAX_GROUPS < 352
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[10]&%1[10]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9])
#elseif _MAX_GROUPS < 384
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[11]&%1[11]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10])
#elseif _MAX_GROUPS < 416
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[12]&%1[12]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11])
#elseif _MAX_GROUPS < 448
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[13]&%1[13]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12])
#elseif _MAX_GROUPS < 480
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[14]&%1[14]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13])
#elseif _MAX_GROUPS < 512
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[15]&%1[15]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14])
#elseif _MAX_GROUPS < 534
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[16]&%1[16]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14]||%0[15]&%1[15])
#else
	// The variable is now based on both input variables to avoid shadow
	// warnings when used within another check (as in "Group_FullPlayerUpdate").
	#define _GROUPS_CHECK_ANY(%0,%1) \
		for (new %1__g%0 = bits<_MAX_GROUPS_G>; %1__g%0--; ) if ((%0[%1__g%0] & %1[%1__g%0]) && !((%1__g%0 = 0)))
#endif

stock
	BitArray:YSI_gGroupPlayers[MAX_PLAYERS]<_MAX_GROUPS_G>,
	BitArray:YSI_gTempGroups<_MAX_GROUPS_G>;

stock const
	BitArray:YSI_g_cEmptyGroups<_MAX_GROUPS_G>;

