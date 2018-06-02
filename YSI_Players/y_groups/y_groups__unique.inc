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

#if defined _inc__unique
	#undef _inc__unique
#endif

#if _GROUP_UNIQUE_SYMBOL == 0
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 1
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_1
#elseif _GROUP_UNIQUE_SYMBOL == 1
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 2
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_2
#elseif _GROUP_UNIQUE_SYMBOL == 2
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 3
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_3
#elseif _GROUP_UNIQUE_SYMBOL == 3
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 4
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_4
#elseif _GROUP_UNIQUE_SYMBOL == 4
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 5
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_5
#elseif _GROUP_UNIQUE_SYMBOL == 5
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 6
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_6
#elseif _GROUP_UNIQUE_SYMBOL == 6
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 7
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_7
#elseif _GROUP_UNIQUE_SYMBOL == 7
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 8
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_8
#elseif _GROUP_UNIQUE_SYMBOL == 8
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 9
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_9
#elseif _GROUP_UNIQUE_SYMBOL == 9
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 10
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_10
#elseif _GROUP_UNIQUE_SYMBOL == 10
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 11
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_11
#elseif _GROUP_UNIQUE_SYMBOL == 11
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 12
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_12
#elseif _GROUP_UNIQUE_SYMBOL == 12
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 13
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_13
#elseif _GROUP_UNIQUE_SYMBOL == 13
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 14
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_14
#elseif _GROUP_UNIQUE_SYMBOL == 14
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 15
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_15
#elseif _GROUP_UNIQUE_SYMBOL == 15
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 16
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_16
#elseif _GROUP_UNIQUE_SYMBOL == 16
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 17
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_17
#elseif _GROUP_UNIQUE_SYMBOL == 17
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 18
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_18
#elseif _GROUP_UNIQUE_SYMBOL == 18
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 19
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_19
#elseif _GROUP_UNIQUE_SYMBOL == 19
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 20
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_20
#elseif _GROUP_UNIQUE_SYMBOL == 20
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 21
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_21
#elseif _GROUP_UNIQUE_SYMBOL == 21
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 22
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_22
#elseif _GROUP_UNIQUE_SYMBOL == 22
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 23
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_23
#elseif _GROUP_UNIQUE_SYMBOL == 23
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 24
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_24
#elseif _GROUP_UNIQUE_SYMBOL == 24
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 25
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_25
#elseif _GROUP_UNIQUE_SYMBOL == 25
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 26
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_26
#elseif _GROUP_UNIQUE_SYMBOL == 26
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 27
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_27
#elseif _GROUP_UNIQUE_SYMBOL == 27
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 28
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_28
#elseif _GROUP_UNIQUE_SYMBOL == 28
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 29
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_29
#elseif _GROUP_UNIQUE_SYMBOL == 29
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 30
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_30
#elseif _GROUP_UNIQUE_SYMBOL == 30
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 31
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_31
#elseif _GROUP_UNIQUE_SYMBOL == 31
	#undef _GROUP_UNIQUE_SYMBOL
	#undef _GROUP_UNIQUE_FUNCTION
	#define _GROUP_UNIQUE_SYMBOL 32
	#define _GROUP_UNIQUE_FUNCTION _Group_IncludeAll_32
#else
	#error y_groups\_unique.inc range expired!
#endif

