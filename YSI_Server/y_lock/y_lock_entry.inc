#if defined _INC_y_lock
	#endinput
#endif
#define _INC_y_lock

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

#if defined _INC_y_utils
	#error YSI\y_lock must be the first include if you want to use it.
#endif
#if defined _DEBUG
	#if _DEBUG >= 1
		#define y_lock%0; _DoYLock(%0);
	#else
		#define y_lock%0; _DoYLock();
	#endif
#else
	#define y_lock%0; _DoYLock();
#endif

#if !defined BIND_IP
	#if defined Y_LOCK_IP
		#define BIND_IP MAKE_LOCK_IP(Y_LOCK_IP)
	#else
		#define BIND_IP MAKE_LOCK_IP(127.0.0.1)
	#endif
#endif

// MASSIVE reliance on operator precedence here!
#define MAKE_LOCK_IP(%0.%1.%2.%3) ((%0&0xFF)<<24|(%1&0xFF)<<16|(%2&0xFF)<<8|%3&0xFF)

#define _LOCK_IP_0 (BIND_IP>>>24)
#define _LOCK_IP_1 (BIND_IP>>>16&0xFF)
#define _LOCK_IP_2 (BIND_IP>>>8&0xFF)
#define _LOCK_IP_3 (BIND_IP&0xFF)

#define UNHOOK for(from=AMX_HEADER_PUBLICS;from!=AMX_HEADER_NATIVES;from+= 8)AMX_Write(from,-1);

#if _LOCK_IP_0 == 0
	#define _LOCK_LEN_0 1
#else
	#define _LOCK_LEN_0 _LOCK_IP_0
#endif

#if _LOCK_IP_1 == 0
	#define _LOCK_LEN_1 1
#else
	#define _LOCK_LEN_1 _LOCK_IP_1
#endif

#if _LOCK_IP_2 == 0
	#define _LOCK_LEN_2 1
#else
	#define _LOCK_LEN_2 _LOCK_IP_2
#endif

#if _LOCK_IP_3 == 0
	#define _LOCK_LEN_3 1
#else
	#define _LOCK_LEN_3 _LOCK_IP_3
#endif

#define YSI_LOCK_MODE
#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Coding\y_hooks"

_DoYLock(P:C(from);)
{
	new
		arr[][] =
			{
				";23#w",
				"32g2"
			};
	P:1("%d", from);
	#pragma unused arr
	#if !defined _DEBUG || _DEBUG < 1
		new from = 0;
	#endif
	UNHOOK
}

