#if defined _INC_y_classes
	#endinput
#endif
#define _INC_y_classes

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

#include "..\..\YSI_Core\y_utils"

stock _YSI_HAS_y_classes(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_classes!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#if !defined MAX_CLASSES
	#define MAX_CLASSES                 (512)
#endif

#if !defined MAX_CLASS_SPAWN_WEAPONS
	#define MAX_CLASS_SPAWN_WEAPONS     (13)
#endif

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR               (100)
#endif

#define INFINATE_ARMOUR                 (0x00800000)

#include "..\..\YSI_Data\y_bit"
#include "..\..\YSI_Data\y_iterate"
#include "..\..\YSI_Data\y_playerarray"
#include "..\..\YSI_Data\y_iterate"

#define Y_CLASSES_GROUP_NAME<%0...%1> %0Class%1
#define Y_CLASSES_GROUP_LIMIT         MAX_CLASSES
#define Y_CLASSES_GROUP_TAG           _
#include "..\..\YSI_Players\y_groups\y_groups__include"

CHAIN_HOOK(Class)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Class)

#define MASTER 61
#define YSIM_U_DISABLE
#include "..\..\YSI_Core\y_master"

#include "..\..\YSI_Coding\y_hooks"
#include "y_classes_classcontrol"
#include "..\..\YSI_Coding\y_hooks"
#include "y_classes_multiclass"

#if defined YSI_TESTS
	#include "y_classes_tests"
#endif

#if defined _INC_y_groups
	#include "y_classes_classgroups"
#endif

// Reset.
//#undef _GROUP_MAKE_LIMIT
//#undef _GROUP_MAKE_NAME

#include "..\..\YSI_Core\y_master"

