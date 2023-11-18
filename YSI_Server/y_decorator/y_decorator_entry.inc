#if defined _INC_y_decorator
	#endinput
#endif
#define _INC_y_decorator

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
#include "..\y_thirdpartyinclude\y3_codeparse"

#define @decorator__(%2)(%3)%0(%1) FUNC_PARSER(DECORATOR__,ARR_CST:STR_CST:NUM_CST:RET_TAG:EXT:)(%0(%1))(%1)()()(%2)(%3)

#define DECORATOR___ARR(%9,%9,%5,%9)%8$(%1)(%6)(%7) %8$(%1)(%6a)(%7,%5)
#define DECORATOR___STR(%9,%9,%5,%9)%8$(%1)(%6)(%7) %8$(%1)(%6s)(%7,%5)
#define DECORATOR___NUM(%9,%9,%5)%8$(%1)(%6)(%7)    %8$(%1)(%6i)(%7,%5)
#define DECORATOR___EXT(%9,%9,%9)%8$(%1)(%6)(%7)    %8$(%1)(%6)(%7)

#define DECORATOR___END(%0)%8$(%1)(%6)(,%7)(%2)(%3) %2:%8$(%3)(_:)(%0)(%1)(%6)(%7)
#define DECORATOR___NUL(%0)%8$()()()(%2)(%3)        %2:%8$(%3)(_:)(%0)()()()

#define DECORATOR___END_TAG(%5,%0)%8$(%1)(%6)(,%7)(%2)(%3) %2:%8$(%3)(%5)(%0)(%1)(%6)(%7)
#define DECORATOR___NUL_TAG(%5,%0)%8$()()()(%2)(%3)        %2:%8$(%3)(%5)(%0)()()()

#define DECORATOR___END_VOD(%0)%8$(%1)(%6)(,%7)(%2)(%3) %2:%8$(%3)(void:)(%0)(%1)(%6)(%7)
#define DECORATOR___NUL_VOD(%0)%8$()()()(%2)(%3)        %2:%8$(%3)(void:)(%0)()()()

