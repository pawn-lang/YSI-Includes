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

#if defined _inc__pop_master
	#undef _inc__pop_master
#endif

#if _YSIM_PUSH_INDEX < 1
	#define MASTER 0
	#endinput
#elseif _YSIM_PUSH_INDEX == 1
	#define MASTER _YSIM_STACK_SLOT_0
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 0
	#endinput
#elseif _YSIM_PUSH_INDEX == 2
	#define MASTER _YSIM_STACK_SLOT_1
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 1
	#endinput
#elseif _YSIM_PUSH_INDEX == 3
	#define MASTER _YSIM_STACK_SLOT_2
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 2
	#endinput
#elseif _YSIM_PUSH_INDEX == 4
	#define MASTER _YSIM_STACK_SLOT_3
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 3
	#endinput
#elseif _YSIM_PUSH_INDEX == 5
	#define MASTER _YSIM_STACK_SLOT_4
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 4
	#endinput
#elseif _YSIM_PUSH_INDEX == 6
	#define MASTER _YSIM_STACK_SLOT_5
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 5
	#endinput
#elseif _YSIM_PUSH_INDEX == 7
	#define MASTER _YSIM_STACK_SLOT_6
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 6
	#endinput
#elseif _YSIM_PUSH_INDEX == 8
	#define MASTER _YSIM_STACK_SLOT_7
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 7
	#endinput
#elseif _YSIM_PUSH_INDEX == 9
	#define MASTER _YSIM_STACK_SLOT_8
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 8
	#endinput
#elseif _YSIM_PUSH_INDEX == 10
	#define MASTER _YSIM_STACK_SLOT_9
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 9
	#endinput
#elseif _YSIM_PUSH_INDEX == 11
	#define MASTER _YSIM_STACK_SLOT_10
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 10
	#endinput
#elseif _YSIM_PUSH_INDEX == 12
	#define MASTER _YSIM_STACK_SLOT_11
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 11
	#endinput
#elseif _YSIM_PUSH_INDEX == 13
	#define MASTER _YSIM_STACK_SLOT_12
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 12
	#endinput
#elseif _YSIM_PUSH_INDEX == 14
	#define MASTER _YSIM_STACK_SLOT_13
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 13
	#endinput
#elseif _YSIM_PUSH_INDEX == 15
	#define MASTER _YSIM_STACK_SLOT_14
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 14
	#endinput
#elseif _YSIM_PUSH_INDEX == 16
	#define MASTER _YSIM_STACK_SLOT_15
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 15
	#endinput
#endif
#error y_master MASTER stack impossibility.

