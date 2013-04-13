/**--------------------------------------------------------------------------**\
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
	
	The Original Code is the YSI groups include.
	
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
	1.0
Changelog:
	29/11/10:
		First version
\**--------------------------------------------------------------------------**/

#undef _inc__init

// Yes, this is odd; yes, it is correct!
#include "..\y_groups/setup"

#if defined _YSI_GROUPS_DO_y_commands
	#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_COMMANDS
	#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_COMMANDS
	#undef _YSI_GROUPS_DO_y_commands
#elseif defined _YSI_GROUPS_DO_y_classes
	#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CLASSES
	#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CLASSES
	#undef _YSI_GROUPS_DO_y_classes
#elseif defined _YSI_GROUPS_DO_y_areas
	#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_AREAS
	#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_AREAS
	#undef _YSI_GROUPS_DO_y_areas
#elseif defined _YSI_GROUPS_DO_y_races
	#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_RACES
	#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_RACES
	#undef _YSI_GROUPS_DO_y_races
#endif

#if !defined _GROUP_MAKE_TAG
	#define _GROUP_MAKE_TAG _
#endif
#if defined _Y_GROUPS_FUNCS
	#include "_funcs"
#else
	#include "_init"
#endif

#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME
#undef _GROUP_MAKE_TAG
