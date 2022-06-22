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

#if defined _inc_y_master__push_master
	#undef _inc_y_master__push_master
#endif

#if _YSIM_PUSH_INDEX < 1
	#include "stack\_stack_push_000"
	#endinput
#elseif _YSIM_PUSH_INDEX == 1
	#include "stack\_stack_push_001"
	#endinput
#elseif _YSIM_PUSH_INDEX == 2
	#include "stack\_stack_push_002"
	#endinput
#elseif _YSIM_PUSH_INDEX == 3
	#include "stack\_stack_push_003"
	#endinput
#elseif _YSIM_PUSH_INDEX == 4
	#include "stack\_stack_push_004"
	#endinput
#elseif _YSIM_PUSH_INDEX == 5
	#include "stack\_stack_push_005"
	#endinput
#elseif _YSIM_PUSH_INDEX == 6
	#include "stack\_stack_push_006"
	#endinput
#elseif _YSIM_PUSH_INDEX == 7
	#include "stack\_stack_push_007"
	#endinput
#elseif _YSIM_PUSH_INDEX == 8
	#include "stack\_stack_push_008"
	#endinput
#elseif _YSIM_PUSH_INDEX == 9
	#include "stack\_stack_push_009"
	#endinput
#elseif _YSIM_PUSH_INDEX == 10
	#include "stack\_stack_push_010"
	#endinput
#elseif _YSIM_PUSH_INDEX == 11
	#include "stack\_stack_push_011"
	#endinput
#elseif _YSIM_PUSH_INDEX == 12
	#include "stack\_stack_push_012"
	#endinput
#elseif _YSIM_PUSH_INDEX == 13
	#include "stack\_stack_push_013"
	#endinput
#elseif _YSIM_PUSH_INDEX == 14
	#include "stack\_stack_push_014"
	#endinput
#elseif _YSIM_PUSH_INDEX == 15
	#include "stack\_stack_push_015"
	#endinput
#endif
#error y_master MASTER stack overflow.

