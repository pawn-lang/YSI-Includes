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

#define _Y_GROUPS_INCLUDED
#define _Y_GROUPS_USER_REQUESTED

#if defined _inc_y_groups_entry
	#undef _inc_y_groups_entry
#endif

#if !defined _INC_y_groups
	/**
	 * <library
	 *   name="y_groups"
	 *   version="1.0"
	 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
	 *   summary="Admin levels, gangs, teams etc - they're all *groups* of people, this provides an abstraction for all of these collections."
	 * >
	 *   <summary pawndoc="true">
	 *     This library uses the enhanced <em>pawndoc.xsl</em> from
	 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
	 *     This XSL has features such as library and markdown support, and will not
	 *     render this message when used.
	 *   </summary>
	 * </library>
	 *//** */

	#include "..\..\YSI_Core\y_utils"
	#include "..\..\YSI_Data\y_bit"
	
	//#if !defined _INC_y_groups__funcs
	//	#define _INC_y_groups__funcs
	#include "y_groups_setup"
	#include "..\..\YSI_Data\y_iterate"
	//#endif
	
	#include "..\..\YSI_Data\y_playerarray"
	
	#include "..\..\YSI_Coding\y_stringhash"
	#include "..\..\YSI_Coding\y_remote"
	
	#include "..\..\YSI_Storage\y_amx"
	
	
	#define YSIM_U_DISABLE
	#define MASTER 59
	#include "..\..\YSI_Core\y_master"
	
	#include "..\..\YSI_Coding\y_hooks"
	
	#include "y_groups_impl"
	
	#include "..\..\YSI_Core\y_master"
#endif

#include "y_groups__include"

// Only include the remainder just once.
#if defined _INC_y_groups
	#endinput
#endif
#define _INC_y_groups

#if defined _INC_y_classes
	#include "..\..\YSI_Visual\y_classes\y_classes_classgroups"
#endif

stock _YSI_HAS_y_groups(_do_not_call_me_ever_, _like_never_)
{
	Debug_Fatal("You called _YSI_HAS_y_groups!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#if defined YSI_TESTS
	#include "y_groups_tests"

	#include "..\..\YSI_Core\y_master"
#endif

