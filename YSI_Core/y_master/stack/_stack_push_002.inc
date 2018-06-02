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

#if defined _inc__stack_push_002
	#undef _inc__stack_push_002
#endif

#undef _YSIM_PUSH_INDEX
#define _YSIM_PUSH_INDEX 3
#if defined _YSIM_STACK_SLOT_2
	#undef _YSIM_STACK_SLOT_2
#endif
#if     _MASTER == 0
	#define _YSIM_STACK_SLOT_2 0
	#endinput
#elseif _MASTER == 1
	#define _YSIM_STACK_SLOT_2 1
	#endinput
#elseif _MASTER == 2
	#define _YSIM_STACK_SLOT_2 2
	#endinput
#elseif _MASTER == 3
	#define _YSIM_STACK_SLOT_2 3
	#endinput
#elseif _MASTER == 4
	#define _YSIM_STACK_SLOT_2 4
	#endinput
#elseif _MASTER == 5
	#define _YSIM_STACK_SLOT_2 5
	#endinput
#elseif _MASTER == 6
	#define _YSIM_STACK_SLOT_2 6
	#endinput
#elseif _MASTER == 7
	#define _YSIM_STACK_SLOT_2 7
	#endinput
#elseif _MASTER == 8
	#define _YSIM_STACK_SLOT_2 8
	#endinput
#elseif _MASTER == 9
	#define _YSIM_STACK_SLOT_2 9
	#endinput
#elseif _MASTER == 10
	#define _YSIM_STACK_SLOT_2 10
	#endinput
#elseif _MASTER == 11
	#define _YSIM_STACK_SLOT_2 11
	#endinput
#elseif _MASTER == 12
	#define _YSIM_STACK_SLOT_2 12
	#endinput
#elseif _MASTER == 13
	#define _YSIM_STACK_SLOT_2 13
	#endinput
#elseif _MASTER == 14
	#define _YSIM_STACK_SLOT_2 14
	#endinput
#elseif _MASTER == 15
	#define _YSIM_STACK_SLOT_2 15
	#endinput
#elseif _MASTER == 16
	#define _YSIM_STACK_SLOT_2 16
	#endinput
#elseif _MASTER == 17
	#define _YSIM_STACK_SLOT_2 17
	#endinput
#elseif _MASTER == 18
	#define _YSIM_STACK_SLOT_2 18
	#endinput
#elseif _MASTER == 19
	#define _YSIM_STACK_SLOT_2 19
	#endinput
#elseif _MASTER == 20
	#define _YSIM_STACK_SLOT_2 20
	#endinput
#elseif _MASTER == 21
	#define _YSIM_STACK_SLOT_2 21
	#endinput
#elseif _MASTER == 22
	#define _YSIM_STACK_SLOT_2 22
	#endinput
#elseif _MASTER == 23
	#define _YSIM_STACK_SLOT_2 23
	#endinput
#elseif _MASTER == 24
	#define _YSIM_STACK_SLOT_2 24
	#endinput
#elseif _MASTER == 25
	#define _YSIM_STACK_SLOT_2 25
	#endinput
#elseif _MASTER == 26
	#define _YSIM_STACK_SLOT_2 26
	#endinput
#elseif _MASTER == 27
	#define _YSIM_STACK_SLOT_2 27
	#endinput
#elseif _MASTER == 28
	#define _YSIM_STACK_SLOT_2 28
	#endinput
#elseif _MASTER == 29
	#define _YSIM_STACK_SLOT_2 29
	#endinput
#elseif _MASTER == 30
	#define _YSIM_STACK_SLOT_2 30
	#endinput
#elseif _MASTER == 31
	#define _YSIM_STACK_SLOT_2 31
	#endinput
#elseif _MASTER == 32
	#define _YSIM_STACK_SLOT_2 32
	#endinput
#elseif _MASTER == 33
	#define _YSIM_STACK_SLOT_2 33
	#endinput
#elseif _MASTER == 34
	#define _YSIM_STACK_SLOT_2 34
	#endinput
#elseif _MASTER == 35
	#define _YSIM_STACK_SLOT_2 35
	#endinput
#elseif _MASTER == 36
	#define _YSIM_STACK_SLOT_2 36
	#endinput
#elseif _MASTER == 37
	#define _YSIM_STACK_SLOT_2 37
	#endinput
#elseif _MASTER == 38
	#define _YSIM_STACK_SLOT_2 38
	#endinput
#elseif _MASTER == 39
	#define _YSIM_STACK_SLOT_2 39
	#endinput
#elseif _MASTER == 40
	#define _YSIM_STACK_SLOT_2 40
	#endinput
#elseif _MASTER == 41
	#define _YSIM_STACK_SLOT_2 41
	#endinput
#elseif _MASTER == 42
	#define _YSIM_STACK_SLOT_2 42
	#endinput
#elseif _MASTER == 43
	#define _YSIM_STACK_SLOT_2 43
	#endinput
#elseif _MASTER == 44
	#define _YSIM_STACK_SLOT_2 44
	#endinput
#elseif _MASTER == 45
	#define _YSIM_STACK_SLOT_2 45
	#endinput
#elseif _MASTER == 46
	#define _YSIM_STACK_SLOT_2 46
	#endinput
#elseif _MASTER == 47
	#define _YSIM_STACK_SLOT_2 47
	#endinput
#elseif _MASTER == 48
	#define _YSIM_STACK_SLOT_2 48
	#endinput
#elseif _MASTER == 49
	#define _YSIM_STACK_SLOT_2 49
	#endinput
#elseif _MASTER == 50
	#define _YSIM_STACK_SLOT_2 50
	#endinput
#elseif _MASTER == 51
	#define _YSIM_STACK_SLOT_2 51
	#endinput
#elseif _MASTER == 52
	#define _YSIM_STACK_SLOT_2 52
	#endinput
#elseif _MASTER == 53
	#define _YSIM_STACK_SLOT_2 53
	#endinput
#elseif _MASTER == 54
	#define _YSIM_STACK_SLOT_2 54
	#endinput
#elseif _MASTER == 55
	#define _YSIM_STACK_SLOT_2 55
	#endinput
#elseif _MASTER == 56
	#define _YSIM_STACK_SLOT_2 56
	#endinput
#elseif _MASTER == 57
	#define _YSIM_STACK_SLOT_2 57
	#endinput
#elseif _MASTER == 58
	#define _YSIM_STACK_SLOT_2 58
	#endinput
#elseif _MASTER == 59
	#define _YSIM_STACK_SLOT_2 59
	#endinput
#elseif _MASTER == 60
	#define _YSIM_STACK_SLOT_2 60
	#endinput
#elseif _MASTER == 61
	#define _YSIM_STACK_SLOT_2 61
	#endinput
#elseif _MASTER == 62
	#define _YSIM_STACK_SLOT_2 62
	#endinput
#elseif _MASTER == 63
	#define _YSIM_STACK_SLOT_2 63
	#endinput
#endif

