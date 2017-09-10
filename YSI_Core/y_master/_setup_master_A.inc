/*
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
	#undef _inc__setup_master_A
#endif

#if MASTER == 0
	#define _MASTER 0
	#define YSIM_STORED_SETTINGS YSIM_RECALL_0
	#if defined _YCM_@a
		#define YSIM_DEFINED
	#else
		#define _YCM_@a
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_0 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_0 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_0 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_0 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_0 4
		#else
			#error Undefined master type on 0
		#endif
	#endif
	#define _YCM @a
	#define MAKE_YCM<%0...%1> %0@a%1
	#define _YCM@ _YCM_g@a
	#endinput
#elseif MASTER == 1
	#define _MASTER 1
	#define YSIM_STORED_SETTINGS YSIM_RECALL_1
	#if defined _YCM_@b
		#define YSIM_DEFINED
	#else
		#define _YCM_@b
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_1 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_1 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_1 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_1 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_1 4
		#else
			#error Undefined master type on 1
		#endif
	#endif
	#define _YCM @b
	#define MAKE_YCM<%0...%1> %0@b%1
	#define _YCM@ _YCM_g@b
	#endinput
#elseif MASTER == 2
	#define _MASTER 2
	#define YSIM_STORED_SETTINGS YSIM_RECALL_2
	#if defined _YCM_@c
		#define YSIM_DEFINED
	#else
		#define _YCM_@c
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_2 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_2 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_2 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_2 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_2 4
		#else
			#error Undefined master type on 2
		#endif
	#endif
	#define _YCM @c
	#define MAKE_YCM<%0...%1> %0@c%1
	#define _YCM@ _YCM_g@c
	#endinput
#elseif MASTER == 3
	#define _MASTER 3
	#define YSIM_STORED_SETTINGS YSIM_RECALL_3
	#if defined _YCM_@d
		#define YSIM_DEFINED
	#else
		#define _YCM_@d
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_3 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_3 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_3 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_3 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_3 4
		#else
			#error Undefined master type on 3
		#endif
	#endif
	#define _YCM @d
	#define MAKE_YCM<%0...%1> %0@d%1
	#define _YCM@ _YCM_g@d
	#endinput
#elseif MASTER == 4
	#define _MASTER 4
	#define YSIM_STORED_SETTINGS YSIM_RECALL_4
	#if defined _YCM_@e
		#define YSIM_DEFINED
	#else
		#define _YCM_@e
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_4 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_4 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_4 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_4 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_4 4
		#else
			#error Undefined master type on 4
		#endif
	#endif
	#define _YCM @e
	#define MAKE_YCM<%0...%1> %0@e%1
	#define _YCM@ _YCM_g@e
	#endinput
#elseif MASTER == 5
	#define _MASTER 5
	#define YSIM_STORED_SETTINGS YSIM_RECALL_5
	#if defined _YCM_@f
		#define YSIM_DEFINED
	#else
		#define _YCM_@f
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_5 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_5 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_5 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_5 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_5 4
		#else
			#error Undefined master type on 5
		#endif
	#endif
	#define _YCM @f
	#define MAKE_YCM<%0...%1> %0@f%1
	#define _YCM@ _YCM_g@f
	#endinput
#elseif MASTER == 6
	#define _MASTER 6
	#define YSIM_STORED_SETTINGS YSIM_RECALL_6
	#if defined _YCM_@g
		#define YSIM_DEFINED
	#else
		#define _YCM_@g
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_6 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_6 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_6 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_6 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_6 4
		#else
			#error Undefined master type on 6
		#endif
	#endif
	#define _YCM @g
	#define MAKE_YCM<%0...%1> %0@g%1
	#define _YCM@ _YCM_g@g
	#endinput
#elseif MASTER == 7
	#define _MASTER 7
	#define YSIM_STORED_SETTINGS YSIM_RECALL_7
	#if defined _YCM_@h
		#define YSIM_DEFINED
	#else
		#define _YCM_@h
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_7 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_7 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_7 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_7 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_7 4
		#else
			#error Undefined master type on 7
		#endif
	#endif
	#define _YCM @h
	#define MAKE_YCM<%0...%1> %0@h%1
	#define _YCM@ _YCM_g@h
	#endinput
#elseif MASTER == 8
	#define _MASTER 8
	#define YSIM_STORED_SETTINGS YSIM_RECALL_8
	#if defined _YCM_@i
		#define YSIM_DEFINED
	#else
		#define _YCM_@i
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_8 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_8 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_8 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_8 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_8 4
		#else
			#error Undefined master type on 8
		#endif
	#endif
	#define _YCM @i
	#define MAKE_YCM<%0...%1> %0@i%1
	#define _YCM@ _YCM_g@i
	#endinput
#elseif MASTER == 9
	#define _MASTER 9
	#define YSIM_STORED_SETTINGS YSIM_RECALL_9
	#if defined _YCM_@j
		#define YSIM_DEFINED
	#else
		#define _YCM_@j
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_9 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_9 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_9 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_9 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_9 4
		#else
			#error Undefined master type on 9
		#endif
	#endif
	#define _YCM @j
	#define MAKE_YCM<%0...%1> %0@j%1
	#define _YCM@ _YCM_g@j
	#endinput
#elseif MASTER == 10
	#define _MASTER 10
	#define YSIM_STORED_SETTINGS YSIM_RECALL_10
	#if defined _YCM_@k
		#define YSIM_DEFINED
	#else
		#define _YCM_@k
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_10 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_10 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_10 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_10 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_10 4
		#else
			#error Undefined master type on 10
		#endif
	#endif
	#define _YCM @k
	#define MAKE_YCM<%0...%1> %0@k%1
	#define _YCM@ _YCM_g@k
	#endinput
#elseif MASTER == 11
	#define _MASTER 11
	#define YSIM_STORED_SETTINGS YSIM_RECALL_11
	#if defined _YCM_@l
		#define YSIM_DEFINED
	#else
		#define _YCM_@l
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_11 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_11 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_11 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_11 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_11 4
		#else
			#error Undefined master type on 11
		#endif
	#endif
	#define _YCM @l
	#define MAKE_YCM<%0...%1> %0@l%1
	#define _YCM@ _YCM_g@l
	#endinput
#elseif MASTER == 12
	#define _MASTER 12
	#define YSIM_STORED_SETTINGS YSIM_RECALL_12
	#if defined _YCM_@m
		#define YSIM_DEFINED
	#else
		#define _YCM_@m
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_12 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_12 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_12 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_12 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_12 4
		#else
			#error Undefined master type on 12
		#endif
	#endif
	#define _YCM @m
	#define MAKE_YCM<%0...%1> %0@m%1
	#define _YCM@ _YCM_g@m
	#endinput
#elseif MASTER == 13
	#define _MASTER 13
	#define YSIM_STORED_SETTINGS YSIM_RECALL_13
	#if defined _YCM_@n
		#define YSIM_DEFINED
	#else
		#define _YCM_@n
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_13 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_13 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_13 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_13 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_13 4
		#else
			#error Undefined master type on 13
		#endif
	#endif
	#define _YCM @n
	#define MAKE_YCM<%0...%1> %0@n%1
	#define _YCM@ _YCM_g@n
	#endinput
#elseif MASTER == 14
	#define _MASTER 14
	#define YSIM_STORED_SETTINGS YSIM_RECALL_14
	#if defined _YCM_@o
		#define YSIM_DEFINED
	#else
		#define _YCM_@o
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_14 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_14 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_14 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_14 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_14 4
		#else
			#error Undefined master type on 14
		#endif
	#endif
	#define _YCM @o
	#define MAKE_YCM<%0...%1> %0@o%1
	#define _YCM@ _YCM_g@o
	#endinput
#elseif MASTER == 15
	#define _MASTER 15
	#define YSIM_STORED_SETTINGS YSIM_RECALL_15
	#if defined _YCM_@p
		#define YSIM_DEFINED
	#else
		#define _YCM_@p
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_15 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_15 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_15 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_15 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_15 4
		#else
			#error Undefined master type on 15
		#endif
	#endif
	#define _YCM @p
	#define MAKE_YCM<%0...%1> %0@p%1
	#define _YCM@ _YCM_g@p
	#endinput
#endif

