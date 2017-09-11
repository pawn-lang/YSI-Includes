/** *//**
				             ======================
				              YSI - Master Include
				             ======================
Description:
	Handles distribution of control of code segments across all running scripts
	with YSI to avoid conflicts of checkpoint streamers etc and allow features
	like "/commands" displaying all commands on the server.
	
	Now fully autonomous - to use the master system simply define which one you
	want and include the script:
	
	  #define MASTER 14
	  #include "Master"
	
	That will make the current script attempt to make itself the main master -
	you don't need ANY other code for initialisation anywhere (which took a
	while to figure out)...
	
	This is now over 2000 lines of repetitive and complex macros!
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
	
	The Original Code is the YSI master systems include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.2
Changelog:
	06/08/10:
		Managed the ultimate - got completely transparent inclusion!
	05/08/10:
		Completed new master system, now does all syncing and clients.
	06/10/09:
		Rewrote using states.
		Added remote function macros.
		Reduced the number of masters to a single one.  It must have them all.
		Vastly simplified the master model - ending the master ends everything.
	06/01/08:
		Added code to not pass data if no other script exists.
	17/11/07:
		Added code for a script to remove itself from the global list.
	11/10/07:
		Not first version but added documentation months late.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
	Hooks:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	RF - Declare a function which may be remote.
	RV - Declare a void function which may be remote.
	RS - Declare an optional callback.
	RFN - Declare an optional callback with no parameters.
	RFC - Declare a slower but shorter function.
	RFP - Declare a function with tags and give recall hints.
	RFPC - Combination of P and C.
	RFCP - Combination of P and C.
Tags:
	-
Variables:
	Global:
		_@ - ID of this script.
	Static:
		-
Commands:
	-
Compile options:
	YSI_NO_MASTER - Don't use the master system.
	YSI_IS_CLIENT - Script is a client only script.
	YSI_IS_SERVER - Script is a server only script.
Operators:
	-
Natives:
	-
*/

#if AUTO_INCLUDE_GUARD
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

