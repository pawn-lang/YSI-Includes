/**--------------------------------------------------------------------------**\
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
</remarks>
\**--------------------------------------------------------------------------**/

#undef _inc__impl2

// Clear up some artifacts
#if defined YSIM_DEFINED
	#undef YSIM_DEFINED
#endif

#if defined _YCM
	#undef _YCM
	#undef _YCM@
#endif

// Now set the current script data.
// IDIOT!  These are mostly mutually exclusive!  You don't need a horrible huge
// bit array to store the fact that this is both a client AND a server!
#if MASTER == 0
	#if defined _YCM_a@
		#define YSIM_DEFINED
	#else
		#define _YCM_a@
		// Save the settings.
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
	#define _YCM a@
	#define _YCM@ _YCM_ga@
#elseif MASTER == 1
	#if defined _YCM_b@
		#define YSIM_DEFINED
	#else
		#define _YCM_b@
		// Save the settings.
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
	#define _YCM b@
	#define _YCM@ _YCM_gb@
#elseif MASTER == 2
	#if defined _YCM_c@
		#define YSIM_DEFINED
	#else
		#define _YCM_c@
		// Save the settings.
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
	#define _YCM c@
	#define _YCM@ _YCM_gc@
#elseif MASTER == 3
	#if defined _YCM_d@
		#define YSIM_DEFINED
	#else
		#define _YCM_d@
		// Save the settings.
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
	#define _YCM d@
	#define _YCM@ _YCM_gd@
#elseif MASTER == 4
	#if defined _YCM_e@
		#define YSIM_DEFINED
	#else
		#define _YCM_e@
		// Save the settings.
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
	#define _YCM e@
	#define _YCM@ _YCM_ge@
#elseif MASTER == 5
	#if defined _YCM_f@
		#define YSIM_DEFINED
	#else
		#define _YCM_f@
		// Save the settings.
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
	#define _YCM f@
	#define _YCM@ _YCM_gf@
#elseif MASTER == 6
	#if defined _YCM_g@
		#define YSIM_DEFINED
	#else
		#define _YCM_g@
		// Save the settings.
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
	#define _YCM g@
	#define _YCM@ _YCM_gg@
#elseif MASTER == 7
	#if defined _YCM_h@
		#define YSIM_DEFINED
	#else
		#define _YCM_h@
		// Save the settings.
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
	#define _YCM h@
	#define _YCM@ _YCM_gh@
#elseif MASTER == 8
	#if defined _YCM_i@
		#define YSIM_DEFINED
	#else
		#define _YCM_i@
		// Save the settings.
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
	#define _YCM i@
	#define _YCM@ _YCM_gi@
#elseif MASTER == 9
	#if defined _YCM_j@
		#define YSIM_DEFINED
	#else
		#define _YCM_j@
		// Save the settings.
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
	#define _YCM j@
	#define _YCM@ _YCM_gj@
#elseif MASTER == 10
	#if defined _YCM_k@
		#define YSIM_DEFINED
	#else
		#define _YCM_k@
		// Save the settings.
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
	#define _YCM k@
	#define _YCM@ _YCM_gk@
#elseif MASTER == 11
	#if defined _YCM_l@
		#define YSIM_DEFINED
	#else
		#define _YCM_l@
		// Save the settings.
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
	#define _YCM l@
	#define _YCM@ _YCM_gl@
#elseif MASTER == 12
	#if defined _YCM_m@
		#define YSIM_DEFINED
	#else
		#define _YCM_m@
		// Save the settings.
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
	#define _YCM m@
	#define _YCM@ _YCM_gm@
#elseif MASTER == 13
	#if defined _YCM_n@
		#define YSIM_DEFINED
	#else
		#define _YCM_n@
		// Save the settings.
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
	#define _YCM n@
	#define _YCM@ _YCM_gn@
#elseif MASTER == 14
	#if defined _YCM_o@
		#define YSIM_DEFINED
	#else
		#define _YCM_o@
		// Save the settings.
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
	#define _YCM o@
	#define _YCM@ _YCM_go@
#elseif MASTER == 15
	#if defined _YCM_p@
		#define YSIM_DEFINED
	#else
		#define _YCM_p@
		// Save the settings.
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
	#define _YCM p@
	#define _YCM@ _YCM_gp@
#elseif MASTER == 16
	#if defined _YCM_q@
		#define YSIM_DEFINED
	#else
		#define _YCM_q@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_16 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_16 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_16 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_16 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_16 4
		#else
			#error Undefined master type on 16
		#endif
	#endif
	#define _YCM q@
	#define _YCM@ _YCM_gq@
#elseif MASTER == 17
	#if defined _YCM_r@
		#define YSIM_DEFINED
	#else
		#define _YCM_r@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_17 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_17 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_17 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_17 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_17 4
		#else
			#error Undefined master type on 17
		#endif
	#endif
	#define _YCM r@
	#define _YCM@ _YCM_gr@
#elseif MASTER == 18
	#if defined _YCM_s@
		#define YSIM_DEFINED
	#else
		#define _YCM_s@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_18 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_18 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_18 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_18 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_18 4
		#else
			#error Undefined master type on 18
		#endif
	#endif
	#define _YCM s@
	#define _YCM@ _YCM_gs@
#elseif MASTER == 19
	#if defined _YCM_t@
		#define YSIM_DEFINED
	#else
		#define _YCM_t@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_19 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_19 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_19 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_19 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_19 4
		#else
			#error Undefined master type on 19
		#endif
	#endif
	#define _YCM t@
	#define _YCM@ _YCM_gt@
#elseif MASTER == 20
	#if defined _YCM_u@
		#define YSIM_DEFINED
	#else
		#define _YCM_u@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_20 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_20 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_20 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_20 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_20 4
		#else
			#error Undefined master type on 20
		#endif
	#endif
	#define _YCM u@
	#define _YCM@ _YCM_gu@
#elseif MASTER == 21
	#if defined _YCM_v@
		#define YSIM_DEFINED
	#else
		#define _YCM_v@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_21 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_21 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_21 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_21 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_21 4
		#else
			#error Undefined master type on 21
		#endif
	#endif
	#define _YCM v@
	#define _YCM@ _YCM_gv@
#elseif MASTER == 22
	#if defined _YCM_w@
		#define YSIM_DEFINED
	#else
		#define _YCM_w@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_22 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_22 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_22 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_22 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_22 4
		#else
			#error Undefined master type on 22
		#endif
	#endif
	#define _YCM w@
	#define _YCM@ _YCM_gw@
#elseif MASTER == 23
	#if defined _YCM_x@
		#define YSIM_DEFINED
	#else
		#define _YCM_x@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_23 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_23 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_23 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_23 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_23 4
		#else
			#error Undefined master type on 23
		#endif
	#endif
	#define _YCM x@
	#define _YCM@ _YCM_gx@
#elseif MASTER == 24
	#if defined _YCM_y@
		#define YSIM_DEFINED
	#else
		#define _YCM_y@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_24 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_24 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_24 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_24 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_24 4
		#else
			#error Undefined master type on 24
		#endif
	#endif
	#define _YCM y@
	#define _YCM@ _YCM_gy@
#elseif MASTER == 25
	#if defined _YCM_z@
		#define YSIM_DEFINED
	#else
		#define _YCM_z@
		// Save the settings.
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_25 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_25 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_25 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_25 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_25 4
		#else
			#error Undefined master type on 25
		#endif
	#endif
	#define _YCM z@
	#define _YCM@ _YCM_gz@
#endif

// Check for non-unique masters here.
#if defined YSIM_DEFINED && !defined _YSIM_OVERRIDE && !defined YSIM_LIBRARY_OVERRIDE
	//#error Non-unique master used.
	#if MASTER == 0
		#error Master 0 already defined (Non-unique master used).
	#elseif MASTER == 1
		#error Master 1 already defined (Non-unique master used).
	#elseif MASTER == 2
		#error Master 2 already defined (Non-unique master used).
	#elseif MASTER == 3
		#error Master 3 already defined (Non-unique master used).
	#elseif MASTER == 4
		#error Master 4 already defined (Non-unique master used).
	#elseif MASTER == 5
		#error Master 5 already defined (Non-unique master used).
	#elseif MASTER == 6
		#error Master 6 already defined (Non-unique master used).
	#elseif MASTER == 7
		#error Master 7 already defined (Non-unique master used).
	#elseif MASTER == 8
		#error Master 8 already defined (Non-unique master used).
	#elseif MASTER == 9
		#error Master 9 already defined (Non-unique master used).
	#elseif MASTER == 10
		#error Master 10 already defined (Non-unique master used).
	#elseif MASTER == 11
		#error Master 11 already defined (Non-unique master used).
	#elseif MASTER == 12
		#error Master 12 already defined (Non-unique master used).
	#elseif MASTER == 13
		#error Master 13 already defined (Non-unique master used).
	#elseif MASTER == 14
		#error Master 14 already defined (Non-unique master used).
	#elseif MASTER == 15
		#error Master 15 already defined (Non-unique master used).
	#elseif MASTER == 16
		#error Master 16 already defined (Non-unique master used).
	#elseif MASTER == 17
		#error Master 17 already defined (Non-unique master used).
	#elseif MASTER == 18
		#error Master 18 already defined (Non-unique master used).
	#elseif MASTER == 19
		#error Master 19 already defined (Non-unique master used).
	#elseif MASTER == 20
		#error Master 20 already defined (Non-unique master used).
	#elseif MASTER == 21
		#error Master 21 already defined (Non-unique master used).
	#elseif MASTER == 22
		#error Master 22 already defined (Non-unique master used).
	#elseif MASTER == 23
		#error Master 23 already defined (Non-unique master used).
	#elseif MASTER == 24
		#error Master 24 already defined (Non-unique master used).
	#elseif MASTER == 25
		#error Master 25 already defined (Non-unique master used).
	#else
		#error Non-unique (and invalid) master used.
	#endif
#endif

#if YSIM_HAS_MASTER && !_YSIM_IS_CLIENT && !_YSIM_IS_STUB && (!defined YSIM_DEFINED || defined YSIM_LIBRARY_OVERRIDE)
	// FIRST declare the next callback in the chain.
	//#if defined FILTERSCRIPT
	//	public OnFilterScriptInit()
	//#else
	//	public OnGameModeInit()
	//#endif
	stock
		_E_YCM:_YCM@ = _E_YCM@u;
	
	public OnMasterSystemInit()
	{
		P:1(#_YCM "_OGM");
		// THEN rename the callbacks.
		#if defined _YCM_CALLBACK
			#undef _YCM_CALLBACK
		#endif
		#if MASTER == 0
			#define _YCM_CALLBACK a@OnScriptInit
		#elseif MASTER == 1
			#define _YCM_CALLBACK b@OnScriptInit
		#elseif MASTER == 2
			#define _YCM_CALLBACK c@OnScriptInit
		#elseif MASTER == 3
			#define _YCM_CALLBACK d@OnScriptInit
		#elseif MASTER == 4
			#define _YCM_CALLBACK e@OnScriptInit
		#elseif MASTER == 5
			#define _YCM_CALLBACK f@OnScriptInit
		#elseif MASTER == 6
			#define _YCM_CALLBACK g@OnScriptInit
		#elseif MASTER == 7
			#define _YCM_CALLBACK h@OnScriptInit
		#elseif MASTER == 8
			#define _YCM_CALLBACK i@OnScriptInit
		#elseif MASTER == 9
			#define _YCM_CALLBACK j@OnScriptInit
		#elseif MASTER == 10
			#define _YCM_CALLBACK k@OnScriptInit
		#elseif MASTER == 11
			#define _YCM_CALLBACK l@OnScriptInit
		#elseif MASTER == 12
			#define _YCM_CALLBACK m@OnScriptInit
		#elseif MASTER == 13
			#define _YCM_CALLBACK n@OnScriptInit
		#elseif MASTER == 14
			#define _YCM_CALLBACK o@OnScriptInit
		#elseif MASTER == 15
			#define _YCM_CALLBACK p@OnScriptInit
		#elseif MASTER == 16
			#define _YCM_CALLBACK q@OnScriptInit
		#elseif MASTER == 17
			#define _YCM_CALLBACK r@OnScriptInit
		#elseif MASTER == 18
			#define _YCM_CALLBACK s@OnScriptInit
		#elseif MASTER == 19
			#define _YCM_CALLBACK t@OnScriptInit
		#elseif MASTER == 20
			#define _YCM_CALLBACK u@OnScriptInit
		#elseif MASTER == 21
			#define _YCM_CALLBACK v@OnScriptInit
		#elseif MASTER == 22
			#define _YCM_CALLBACK w@OnScriptInit
		#elseif MASTER == 23
			#define _YCM_CALLBACK x@OnScriptInit
		#elseif MASTER == 24
			#define _YCM_CALLBACK y@OnScriptInit
		#elseif MASTER == 25
			#define _YCM_CALLBACK z@OnScriptInit
		#endif
		#if _YSIM_IS_SERVER
			// Steal the master.
			_Master_Get(#_YCM, true);
			_YCM@ = _E_YCM@y;
			// Determine the next unique name.
			CallRemoteFunction(#_YCM, "");
		#elseif _YSIM_IS_CLOUD
			// See if this script should be master.
			if (_Master_Get(#_YCM))
			{
				P:2("Got master " #_YCM);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
			}
			else
			{
				state _YCM:n;
				_YCM@ = _E_YCM@n;
			}
		#endif
		// FINALLY call the new next one.
		//CallLocalFunction(#_YCM_CALLBACK, "");
		#if MASTER == 0
			#if defined a@OnScriptInit
				return a@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 1
			#if defined b@OnScriptInit
				return b@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 2
			#if defined c@OnScriptInit
				return c@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 3
			#if defined d@OnScriptInit
				return d@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 4
			#if defined e@OnScriptInit
				return e@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 5
			#if defined f@OnScriptInit
				return f@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 6
			#if defined g@OnScriptInit
				return g@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 7
			#if defined h@OnScriptInit
				return h@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 8
			#if defined i@OnScriptInit
				return i@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 9
			#if defined j@OnScriptInit
				return j@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 10
			#if defined k@OnScriptInit
				return k@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 11
			#if defined l@OnScriptInit
				return l@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 12
			#if defined m@OnScriptInit
				return m@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 13
			#if defined n@OnScriptInit
				return n@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 14
			#if defined o@OnScriptInit
				return o@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 15
			#if defined p@OnScriptInit
				return p@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 16
			#if defined q@OnScriptInit
				return q@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 17
			#if defined r@OnScriptInit
				return r@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 18
			#if defined s@OnScriptInit
				return s@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 19
			#if defined t@OnScriptInit
				return t@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 20
			#if defined u@OnScriptInit
				return u@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 21
			#if defined v@OnScriptInit
				return v@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 22
			#if defined w@OnScriptInit
				return w@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 23
			#if defined x@OnScriptInit
				return x@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 24
			#if defined y@OnScriptInit
				return y@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif MASTER == 25
			#if defined z@OnScriptInit
				return z@OnScriptInit();
			#else
				return 1;
			#endif
		#endif
	}
	
	// Don't need extra checks here as we KNOW it is already defined.
	#undef OnMasterSystemInit
	#define OnMasterSystemInit _YCM_CALLBACK
	#if MASTER == 0
		#if defined a@OnScriptInit
			forward a@OnScriptInit();
		#endif
	#elseif MASTER == 1
		#if defined b@OnScriptInit
			forward b@OnScriptInit();
		#endif
	#elseif MASTER == 2
		#if defined c@OnScriptInit
			forward c@OnScriptInit();
		#endif
	#elseif MASTER == 3
		#if defined d@OnScriptInit
			forward d@OnScriptInit();
		#endif
	#elseif MASTER == 4
		#if defined e@OnScriptInit
			forward e@OnScriptInit();
		#endif
	#elseif MASTER == 5
		#if defined f@OnScriptInit
			forward f@OnScriptInit();
		#endif
	#elseif MASTER == 6
		#if defined g@OnScriptInit
			forward g@OnScriptInit();
		#endif
	#elseif MASTER == 7
		#if defined h@OnScriptInit
			forward h@OnScriptInit();
		#endif
	#elseif MASTER == 8
		#if defined i@OnScriptInit
			forward i@OnScriptInit();
		#endif
	#elseif MASTER == 9
		#if defined j@OnScriptInit
			forward j@OnScriptInit();
		#endif
	#elseif MASTER == 10
		#if defined k@OnScriptInit
			forward k@OnScriptInit();
		#endif
	#elseif MASTER == 11
		#if defined l@OnScriptInit
			forward l@OnScriptInit();
		#endif
	#elseif MASTER == 12
		#if defined m@OnScriptInit
			forward m@OnScriptInit();
		#endif
	#elseif MASTER == 13
		#if defined n@OnScriptInit
			forward n@OnScriptInit();
		#endif
	#elseif MASTER == 14
		#if defined o@OnScriptInit
			forward o@OnScriptInit();
		#endif
	#elseif MASTER == 15
		#if defined p@OnScriptInit
			forward p@OnScriptInit();
		#endif
	#elseif MASTER == 16
		#if defined q@OnScriptInit
			forward q@OnScriptInit();
		#endif
	#elseif MASTER == 17
		#if defined r@OnScriptInit
			forward r@OnScriptInit();
		#endif
	#elseif MASTER == 18
		#if defined s@OnScriptInit
			forward s@OnScriptInit();
		#endif
	#elseif MASTER == 19
		#if defined t@OnScriptInit
			forward t@OnScriptInit();
		#endif
	#elseif MASTER == 20
		#if defined u@OnScriptInit
			forward u@OnScriptInit();
		#endif
	#elseif MASTER == 21
		#if defined v@OnScriptInit
			forward v@OnScriptInit();
		#endif
	#elseif MASTER == 22
		#if defined w@OnScriptInit
			forward w@OnScriptInit();
		#endif
	#elseif MASTER == 23
		#if defined x@OnScriptInit
			forward x@OnScriptInit();
		#endif
	#elseif MASTER == 24
		#if defined y@OnScriptInit
			forward y@OnScriptInit();
		#endif
	#elseif MASTER == 25
		#if defined z@OnScriptInit
			forward z@OnScriptInit();
		#endif
	#endif
#endif

// The code below is now deprecated in favour of foreign/global!
// There are the following remote function definitions:
// 
// RF - A basic function.
// RF@p - A function with special parameters which need passing hints.
// RF@c - A function with lots of paramteres that needs special code.
// RF@v - A function with no return value.
// RF@t - A function with a tag result.
// RC - A callback function.
// RH - A y_hooks hook.
// RS - Return a string.
// 
// 
// Supported combinations:
// 
// pc, cp
// pcv, pvc, cpv, cvp, vpc, vcp
// pv, vp
// cv, vc
// cpt ctp pct ptc tcp tpc
// ct tc
// pt tp
// 
// p and c are for special parameter sets, n is for no parameters, so those two
// groups can never be mixed together.  t is for tag result and v is for no
// return, so they can never be used together.
// 
// Note that the callback thing won't work with OnPlayerCommandText as it has a
// different default return to everything else.
// 

// These parts are redefined every time the master system is included.
#if YSIM_HAS_MASTER
	#if _YSIM_IS_SERVER
		
		#define foreign%0(%1) %0(%1);%0@(%1)
		#define @foreign foreign
		//#define global%0(%1) %0@(%1);public%0@(%1)X@(_:@Zk:%0(_YM@CP:%1,,));%0(%1)
		#define global%0(%1) public%0@(%1)(@Zz:X@(@Zk:_YM@CP:%0(%1,,)));%0(%1)
		
		
		
		
		#define RF:%1[%2](%3) @%1(%3);@%1(%3)U@(8,YSIM_RETURN,%1(%3));%1(%3)
		#define RF@p:%1[%2](%3)<%4> @%1(%3);@%1(%3)U@(8,YSIM_RETURN,%1(%4));%1(%3)
		#define RF@c RF
		#define RF@v:%1[%2](%3) @%1(%3);@%1(%3)%1(%3);%1(%3)
		//#define RF@n:%1[]() forward %1R();public %1R()U@(8,YSIM_RETURN,%1());%1()
		#define RF@pc RF@p
		#define RF@pv:%1[%2](%3)<%4> @%1(%3);@%1(%3)%1(%4);%1(%3)
		#define RF@pcv RF@pv
		#define RF@vc RF@v
		//#define RF@vn:%1[]() forward %1R();public %1R()%1();%1()
		
		#define RF@t:%0:%1[%2](%3) %0:%1(%3);@%1(%3);@%1(%3)U@(8,YSIM_RETURN,_:%1(%3));%0:%1(%3)
		#define RF@pt:%0:%1[%2](%3)<%4> %0:%1(%3);@%1(%3);@%1(%3)U@(8,YSIM_RETURN,_:%1(%4));%0:%1(%3)
		#define RF@ct RF@t
		//#define RF@nt:%0:%1[]() forward %0:%1();forward %1R();public %1R()U@(8,YSIM_RETURN,_:%1());%0:%1()
		#define RF@pct RF@pt
		
		#define RS:%1[%2](%3) @%1(%3);@%1(%3)R@(%1(%3));%1(%3)
		#define RS@p:%1[%2](%3)<%4> @%1(%3);@%1(%3)R@(%1(%4));%1(%3)
		
		//#define RC:%1(%3) public %1(%3)
		
		//#define RC@v RC
		#define RH:On%2(%3) hook On%2(%3)
		
		#define master_hook%0On%2(%3) hook On%2(%3)
		#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)
		
		#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()
		
		#if MASTER == 23
			// Less strict (implicit user master).
			#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#else
			#define RC:%0(%1) @yC_%0(a,b[],c);@yC_%0(a,b[],c)U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#endif
		
		// Remote local - only calls the local version if we're master,
		// doesn't call the remote version.
		//#define RL:%1[%2](%3) %1(%3)
		
		//#define RP@v:%1[%2](%3) forward @%1(%3);@%1(%3)%1(%3);static %1(%3)
		
		// Shortcut for y_als hooks.
		#define RA:%0_On%1(%3) public On%1(%3)
		//#define RA@p:%0_%1[%2](%3)<%4> RA:%0_%1[%2](%3)
		
		//#define RX:%0(%1) %0@yX_(%1);public %0@yX_(%1)
		
		#define Master_Caller() \
			(V@(8,YSIM_CALLER))
		
		//#define Master_Get(%1) state (_Master_Get(#%1)) ? (%1:y) : (%1:n)
		//#define Master_Init(%1); _Master_Get(#%1);
	#else
		
		// This definition has "%0(%1)" defined as "public", "stock" AND ""!!!
		//#define foreign%0(%1); %0(%1);public %0(%1)<_YCM:m>return 0;stock %0(%1)<>{new i=Y@();W@(#%0@##,_YM@CM:%1,,);return Z@(i);}
		
		// Define "foreign" more generically.  If you want "server" or "none"
		// you will need to define this specifically, otherwise you just need to
		// include the master system and then you can use "#tryinclude".  This
		// means that if "global" definitions aren't found this system will try
		// default to STUB.  This is NOT a complete definition - the "@Zu:"
		// definition means that more processing is done (mainly for the
		// definition of the "_YCM:m" function to not give warnings.
		//#define foreign%0(%1); stock %0(%1)<>{new i=_:@Zu:Y@();W@(#%0@##,_YM@CX:%1,,);return Z@(i);}%0@(%1);%0(%1)<_YCM:m>
		#define @foreign%0(%1) stock%0(%1)<>{new i=Y@();W@(@Zu:#%0@#,_YM@Cj:%1,,);return Z@(i);}%0(%1)<_YCM:m>
		
		#define foreign%0(%1) stock%0(%1)<>{W@(@Zu:#%0@#,_YM@Cl:%1,,);return V@(8,YSIM_RETURN);}%0(%1)<_YCM:m>
		
		#if _YSIM_IS_CLIENT
			
			#define global%0(%1) stock %0_(%1)
			
			
			
			
			// Defined the functions as remote calling stubs.  Then rename the
			// following code with a name unlikely to ever be used and define the
			// functions as stock so the compiler removes all the code quietly.
			#define RF:%1[%2](%3) stock %1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);stock _@%1(%3)
			#define RF@p:%1[%2](%3)<%4> stock %1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);stock _@%1(%3)
			#define RF@c RF
			#define RF@v:%1[%2](%3) stock %1(%3)U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1);stock _@%1(%3)
			//#define RF@n:%1[]() stock %1()return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);stock _@%1()
			#define RF@pc RF@p
			#define RF@pv:%1[%2](%3)<%4> stock %1(%3)U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1);stock _@%1(%3)
			#define RF@pcv RF@pv
			#define RF@vc RF@v
			//#define RF@vn:%1[]() stock %1()U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1);stock _@%1()
			
			#define RF@t:%0:%1[%2](%3) stock %0:%1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);stock %0:_@%1(%3)
			#define RF@pt:%0:%1[%2](%3)<%4> stock %0:%1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);stock %0:_@%1(%3)
			#define RF@ct RF@t
			//#define RF@nt:%0:%1[]() stock %0:%1()return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);stock %0:_@%1()
			#define RF@pct RF@pt
			
			#define RS:%1[%2](%3) stock %1(%3)return Y@(),W@(#@%1,(x:#%2#),%3),S@(),Q@;stock _@%1(%3)
			#define RS@p:%1[%2](%3)<%4> stock %1(%3)return Y@(),W@(#@%1,#%2,%4),S@(),Q@;stock _@%1(%3)
			
			//#define RC:%1(%3) stock _@%1(%3)
			//#define RC@v RC
			
			#define RH:On%2(%3)
			
			#define master_hook%0On%2(%3) stock UNIQUE_FUNCTION<_yH@%2...>(%3)
			#define group_hook%0On%2(%3) stock _GROUP_MAKE_NAME<On%2...>(%3)
			
			#define RT:%0[%1](%2) stock _yT@%1_%0()
			
			#if MASTER == 23
				// Less strict (implicit user master).
				#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
			#else
				#define RC:%0(%1) static stock _@yC%0()
			#endif
			
			//#define RP@v:%1[%2](%3) static stock %1(%3)U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1);static stock _@%1(%3)
			
			// Remote local - only calls the local version if we're master,
			// doesn't call the remote version.
			//#define RL:%1[%2](%3) stock %1(%3){}static stock _%1(%3)
			
			//#define RX:%0(%1) stock %0_yX@(%1)
			
			// Shortcut for y_als hooks.
			#define RA:%0_On%1(%3) public On%1(%3)ALS_CALL<%1> static stock _%0_%1(%3)
			//#define RA:%0_%1[%2](%3) public %1(%3)<>return Bit_GetBit(Bit:gs_ALS,_:ALS_%0)&&P@(#ALS_PREFIX"_"x:#%2#,%3),1;public %1(%3)<_YCM:y>
			//#define RA@p:%0_%1[%2](%3)<%4> public %1(%3)ALS_CALL<%1,#%2,%4>static stock _%0_%1(%3)
			//#define RA@p:%0_%1[%2](%3)<%4> public %1(%3)<>return Bit_GetBit(Bit:gs_ALS,_:ALS_%0)&&P@(#ALS_PREFIX"_"#%2,%4),1;public %1(%3)<_YCM:y>
			
			#define Master_Caller() (-1)
		#else
			#if _YSIM_IS_STUB
				
				//#define foreign%0(%1); stock %0(%1){new i=Y@();W@(#%0@##,_YM@CM:%1,,);return Z@(i);}
				#define global%0(%1)
				
				
				
				
				// This is used to provide abstractions between different
				// coders on the same team.  Setting a library as a stub means
				// that people without the main implementation can use the code
				// through remote function calls and then the whole code can be
				// integrated in to itself.  Example use:
				//  
				//  #tryinclude "streamer_implementation"
				//  #if defined _inc_streamer_implementation
				//      #endinput
				//  #endif
				//  
				//  #define YSIM_U_ENABLE
				//  #define MASTER 10
				//  #include "y_master"
				//  
				//  RF@p:CreateObject[ifff](modelid,Float:x,Float:y,Float:z)<modelid,x,y,z>;
				//  
				#define RF:%1[%2](%3) stock %1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN)//;stock _@%1()
				#define RF@p:%1[%2](%3)<%4> stock %1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN)//;stock _@%1()
				#define RF@c RF
				#define RF@v:%1[%2](%3) stock %1(%3)U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1)//;stock _@%1()
				//#define RF@n:%1[]() stock %1()return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);stock _@%1()
				#define RF@pc RF@p
				#define RF@pv:%1[%2](%3)<%4> stock %1(%3)U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1)//;stock _@%1()
				#define RF@pcv RF@pv
				#define RF@vc RF@v
				//#define RF@vn:%1[]() stock %1()U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1);stock _@%1()
				
				#define RF@t:%0:%1[%2](%3) stock %0:%1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN)//;stock _@%1()
				#define RF@pt:%0:%1[%2](%3)<%4> stock %0:%1(%3)return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN)//;stock _@%1()
				#define RF@ct RF@t
				//#define RF@nt:%0:%1[]() stock %0:%1()return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);stock %0:_@%1()
				#define RF@pct RF@pt
				
				// Doesn't have the end bit as the function isn't included.
				#define RS:%1[%2](%3) stock %1(%3)return Y@(),W@(#@%1,(x:#%2#),%3),S@(),Q@//;stock _@%1()
				#define RS@p:%1[%2](%3)<%4> stock %1(%3)return Y@(),W@(#@%1,#%2,%4),S@(),Q@//;stock _@%1()
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RC
				
				// NOT DEFINED!  Should not be used if this is a stub.
				//#define RC@v
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RH
				
				#define master_hook
				
				#define group_hook
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RT
				
				// Remote local - only calls the local version if we're master,
				// doesn't call the remote version.
				//#define RL:%1[%2](%3)
				
				//#define RX
				
				//#define RP@v
				
				// Shortcut for y_als hooks.
				#define RA //:%0_%1(%3)
				//#define RA@p:%0_%1[%2](%3)<%4>
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define Master_Caller
			#else
				
				//#define foreign%0(%1); %0(%1)<>{new i=Y@();W@(#%0@##,_YM@CM:%1,,);return Z@(i);}%0@(%1);%0(%1)<_YCM:x>{}
				//#define global%0(%1) %0@(%1);public%0@(%1)<>{}public%0@(%1)<_YCM:y>X@(_:@Zk:%0(_YM@CP:%1,,));%0(%1)<_YCM:y>
				//#define global%0(%1) public%0@(%1)<>{}public%0@(%1)<_YCM:y>X@(_:@Zk:_YM@CP:%0(%1,,));stock %0(%1)<_YCM:y>
				#define global%0(%1) %0@(%1);public%0@(%1)<>{}public%0@(%1)<_YCM:y>(@Zz:X@(@Zk:_YM@CP:%0(%1,,)));stock%0(%1)<_YCM:y>
				
				
				// TODO: I just realised that I have NEVER used the
				// "Master_Caller" feature of the master system EVER, despite
				// all the overhead involved in activating and using it...
				// Maybe I should just remove it!  Update: Or make it optional.
				
				// This is a normal system with the possibility of being the
				// master.  This is the very complicated one to write!
				#define RF:%1[%2](%3) @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>U@(8,YSIM_RETURN,%1(%3));%1(%3)<>return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);%1(%3)<_YCM:y>
				
				#define RF@p:%1[%2](%3)<%4> @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>U@(8,YSIM_RETURN,%1(%4));%1(%3)<>return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);%1(%3)<_YCM:y>
				#define RF@c:%1[%2](%3) @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>X@(%1(%3));%1(%3)<>return Y@(),W@(#@%1,(x:#%2#),%3),Z@();%1(%3)<_YCM:y>
				#define RF@v:%1[%2](%3) @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>%1(%3);%1(%3)<>U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1);%1(%3)<_YCM:y>
				//#define RF@n:%1[]() forward %1R();public %1R()<>{}public %1R()<_YCM:y>U@(8,YSIM_RETURN,%1());%1()<>return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),V@(8,YSIM_RETURN);%1()<_YCM:y>
				#define RF@pc:%1[%2](%3)<%4> @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>X@(%1(%4));%1(%3)<>return Y@(),W@(#@%1,#%2,%4),Z@();%1(%3)<_YCM:y>
				#define RF@pv:%1[%2](%3)<%4> @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>%1(%4);%1(%3)<>U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1);%1(%3)<_YCM:y>
				#define RF@pcv:%1[%2](%3)<%4> @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>%1(%4);%1(%3)<>Y@(),W@(#@%1,#%2,%4),T@();%1(%3)<_YCM:y>
				#define RF@vc:%1[%2](%3) @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>%1(%3);%1(%3)<>Y@(),W@(#@%1,(x:#%2#),%3),T@();%1(%3)<_YCM:y>
				//#define RF@vn:%1[]() forward %1R();public %1R()<>{}public %1R()<_YCM:y>%1();%1()<>U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1);%1()<_YCM:y>
				
				#define RF@t:%0:%1[%2](%3) %0:%1(%3);@%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>U@(8,YSIM_RETURN,_:%1(%3));%0:%1(%3)<>return U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);%0:%1(%3)<_YCM:y>
				#define RF@pt:%0:%1[%2](%3)<%4> %0:%1(%3);@%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>U@(8,YSIM_RETURN,_:%1(%4));%0:%1(%3)<>return U@(8,YSIM_CALLER,_@),W@(#@%1,#%2,%4),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);%0:%1(%3)<_YCM:y>
				#define RF@ct:%0:%1[%2](%3) %0:%1(%3);@%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>X@(_:%1(%3));%0:%1(%3)<>return Y@(),W@(#@%1,(x:#%2#),%3),%0:Z@();%0:%1(%3)<_YCM:y>
				//#define RF@nt:%0:%1[]() forward %0:%1();forward %1R();public %1R()<>{}public %1R()<_YCM:y>U@(8,YSIM_RETURN,_:%1());%0:%1()<>return U@(8,YSIM_CALLER,_@),W@(#@%1,""),U@(8,YSIM_CALLER,-1),%0:V@(8,YSIM_RETURN);%0:%1()<_YCM:y>
				#define RF@pct:%0:%1[%2](%3)<%4> %0:%1(%3);@%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>X@(_:%1(%4));%0:%1(%3)<>return Y@(),W@(#@%1,#%2,%4),%0:Z@();%0:%1(%3)<_YCM:y>
				
				//#define RS:%1[%2](%3) forward %1R(%3);public %1R(%3)<>{}public %1R(%3)<_YCM:y>R@(%1(%3));%1(%3)<>return Y@(),W@(#@%1,(x:#%2#),%3),S@();%1(%3)<_YCM:y>
				// Remote STRING (returns a string).
				#define RS:%1[%2](%3) @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>R@(%1(%3));%1(%3)<>return Y@(),W@(#@%1,(x:#%2#),%3),S@(),Q@;%1(%3)<_YCM:y>
				#define RS@p:%1[%2](%3)<%4> @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>R@(%1(%4));%1(%3)<>return Y@(),W@(#@%1,#%2,%4),S@(),Q@;%1(%3)<_YCM:y>
				
				//#define RC:%1(%3) public %1(%3)<>return 1;public %1(%3)<_YCM:y>
				
				//#define RC@v:%1(%3) public %1(%3)<>{}public %1(%3)<_YCM:y>
				
				// Requires the y_hooks library.
				#define RH:On%2(%3) hook On%2(%3)<>return ALS_R_%2;rehook On%2(%3)<_YCM:y>
				
				#define master_hook%0On%2(%3) hook On%2(%3)<>return ALS_R_%2;rehook On%2(%3)<_YCM:y>
				
				#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)<>return ALS_R_%2;_GROUP_MAKE_NAME<rehook On%2...>(%3)<_YCM:y>
				
				// Requires the y_timers library.
				#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()<>{}@yT_%1_%0()<_YCM:y>
				
				/*#if 
					#define RC:%0(%1) forward @yC_%0(a,b[],c);@yC_%0(a,b[],c)<>{}@yC_%0(a,b[],c)<_YCM:y>U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#else
					// This code defines two publics so that if the master
					// doesn't have a copy of the command it can still be called
					// in another running script.
					#define RC:%0(%1) forward @yC_%0(a,b[],c);forward @_yC%0(i,a,b,c[]);@yC_%0(a,b[],c)<>{}@yC_%0(a,b[],c)<_YCM:y>U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(i,a,b,c[])return i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#endif*/
				//#if defined _YSIM_USED_AUTO
				#if MASTER == 23
					// Less strict (implicit user master).
					#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#else
					// Strict libraries.
					#define RC:%0(%1) @yC_%0(a,b[],c);@yC_%0(a,b[],c)<>{}@yC_%0(a,b[],c)<_YCM:y>U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#endif
				
				//#define RP@v:%1[%2](%3) forward @%1(%3);@%1(%3)<>{}@%1(%3)<_YCM:y>%1(%3);static %1(%3)<>U@(8,YSIM_CALLER,_@),W@(#@%1,(x:#%2#),%3),U@(8,YSIM_CALLER,-1);static %1(%3)<_YCM:y>
				
				#define Master_Caller() \
					(((I@=V@(8,YSIM_CALLER))==-1)?(_@):(I@))
				
				// Remote local - only calls the local version if we're master,
				// doesn't call the remote version.
				//#define RL:%1[%2](%3) %1(%3)<>return 1;%1(%3)<_YCM:y>
				
				//#define RX:%0(%1) %0@yX_(%1);public %0@yX_(%1)<>{}public %0@yX_(%1)<_YCM:y>
				//#define RX:%0(%1) UNIQUE_FUNCTION<@yX_...%0>(%1);UNIQUE_FUNCTION<@yX_...%0>(%1)<>{}UNIQUE_FUNCTION(@yX_...%0>(%1)<_YCM:y>
				
				// Shortcut for y_als hooks.
				//#define RA:%0_%1(%3) public %1(%3)<>ALS_CALL<%1>public %1(%3)<_YCM:y>
				#define RA:%0_On%1(%3) public On%1(%3)<>ALS_CALL<%1> public On%1(%3)<_YCM:y>
				//#define RA:%0_%1[%2](%3) public %1(%3)<>return Bit_GetBit(Bit:gs_ALS,_:ALS_%0)&&P@(#ALS_PREFIX"_"x:#%2#,%3),1;public %1(%3)<_YCM:y>
				//#define RA@p:%0_%1[%2](%3)<%4> public %1(%3)<>ALS_CALL<%1,#%2,%4>public %1(%3)<_YCM:y>
				
				//#define Master_Get(%1) state (_Master_Get(#%1)) ? (%1:y) : (%1:n)
				//#define Master_Init(%1); if (_Master_Get(#%1)) state %1:y; else state %1:n;
			#endif
		#endif
	#endif
#else
	
	#define foreign forward
	#define @foreign forward
	#define global stock
	
	
	
	
	// Master system isn't used.
	#define RF:%1[%2](%3) stock %1(%3)
	#define RF@p:%1[%2](%3)<%4> RF:%1[%2](%3)
	#define RF@c RF
	#define RF@v RF
	//#define RF@n RF
	#define RF@pc RF@p
	#define RF@pv RF@p
	#define RF@pcv RF@p
	#define RF@vc RF
	//#define RF@vn RF
	
	#define RF@t:%0:%1[%2](%3) stock %0:%1(%3)
	#define RF@pt:%0:%1[%2](%3)<%4> RF@t:%0:%1[%2](%3)
	#define RF@ct RF@t
	//#define RF@nt RF@t
	#define RF@pct RF@p
	
	#define RS:%1[%2](%3) stock %1(%3)
	#define RS@p:%1[%2](%3)<%4> stock %1(%3)
	#define RS@c RS
	#define RS@pc RS@p
	
	//#define RC:%1(%3) public %1(%3)
	//#define RC@v: RC
	
	#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()
	
	//#define RP@v:%0[%1](%2) static stock %0(%2)
	
	#define RH:On%2(%3) hook On%2(%3)
	
	#define master_hook%0On%2(%3) hook On%2(%3)
	
	#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)
	
	#define RC:%0(%1) @yC_%0(%1);@yC_%0(%1)
	
	//#define RX:%0(%1) %0@yX_(%1);public %0@yX_(%1)
	
	#define Master_Caller() (_@)
	
	// Remote local - only calls the local version if we're master,
	// doesn't call the remote version.
	//#define RL:%1[%2](%3) stock %1(%3)
	
	// Shortcut for y_als hooks.
	#define RA:%0_On%1(%3) public On%1(%3)
	//#define RA@p:%0_%1[%2](%3)<%4> RA:%0_%1[%2](%3)
	//#define Master_Init(%1);
#endif

#if !YSIM_HAS_MASTER
	static stock const THE_CURRENT_MASTER_IS_UNSET   = MASTER;
#elseif _YSIM_IS_CLIENT
	static stock const THE_CURRENT_MASTER_IS_CLIENT  = MASTER;
#elseif _YSIM_IS_SERVER
	static stock const THE_CURRENT_MASTER_IS_SERVER  = MASTER;
#elseif _YSIM_IS_CLOUD
	static stock const THE_CURRENT_MASTER_IS_CLOUD   = MASTER;
#elseif _YSIM_IS_STUB
	static stock const THE_CURRENT_MASTER_IS_STUB    = MASTER;
#else
	static stock const THE_CURRENT_MASTER_IS_UNKNOWN = MASTER;
#endif
#undef MASTER

#if !defined YSIM_DEFINED || defined YSIM_LIBRARY_OVERRIDE
	#if _YSIM_IS_CLOUD || _YSIM_IS_SERVER
		// Define a load of fake functions to cater for the compiler's need to
		// know all the possible states.  y means master, n means not master, m
		// means master system missing, p means previous (ending master), u
		// means sort of uninitialised (though technically initialised).  This
		// also doubles as a handy call in function for resetting masters when a
		// script ends.  Just to clarify - this function is NOT called _YCM,
		// that is a macro which is expanded every time this file is included.
		// m is also now client/stub.
		forward _YCM();
		public _YCM() <_YCM:y>
		{
			P:1("%d: " #_YCM "<y> called", _@);
			if (getproperty(8, #_YCM) != _@)
			{
				// Master, but not.  A server has claimed this.
				state _YCM:n;
				_YCM@ = _E_YCM@n;
			}
			else
			{
				P:2("%d: " #_YCM ":y called", _@);
				// Disable the current mastership.
				state _YCM:p;
				_YCM@ = _E_YCM@p;
				setproperty(8, #_YCM, -1);
				// Called locally to begin the hand off process.
				CallRemoteFunction(#_YCM, "");
			}
		}
		
		public _YCM() <_YCM:n>
		{
			P:1("%d: " #_YCM "<n> called", _@);
			// This has been called remotely from a script which owns the
			// library masterhood (that's the only way this can ever be called).
			if (_Master_Get(#_YCM))
			{
				P:2("%d: " "Got master " #_YCM, _@);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
			}
		}
		
		public _YCM() <_YCM:m, _YCM:p, _YCM:u>
		{
			P:1("%d: " #_YCM "<m,p,u,x> called", _@);
			// Do nothing at all (just define states).
		}
		
		public _YCM() <>
		{
			P:1("%d: " #_YCM "<> called", _@);
			if (_Master_Get(#_YCM))
			{
				P:2("%d: " "Got master " #_YCM, _@);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
			}
			else
			{
				state _YCM:n;
				_YCM@ = _E_YCM@n;
			}
			// Do nothing at all (just define states).
		}
	/*#elseif _YSIM_IS_SERVER
		forward _YCM();
		public _YCM() <_YCM:y>
		{
			P:1("%d: " #_YCM "<y> called", _@);
			// Disable the current mastership.
			state _YCM:p;
			setproperty(8, #_YCM, -1);
			// Called locally to begin the hand off process.
			CallRemoteFunction(#_YCM, "");
		}
		
		public _YCM() <_YCM:n, _YCM:m, _YCM:p, _YCM:u>
		{
			P:1("%d: " #_YCM "<n,m,p,u,x> called", _@);
			// Do nothing at all (just define states).
		}
		
		public _YCM() <>
		{
			P:1("%d: " #_YCM "<> called", _@);
			//_Master_Get(#_YCM, true);
			P:2("%d: " "Got master " #_YCM, _@);
			state _YCM:y;
			// Do nothing at all (just define states).
		}*/
		
	/*#else
		#if _YSIM_IS_CLIENT || _YSIM_IS_STUB
			static stock _YCM() <_YCM:m>
			{
			}
			
			static stock _YCM() <>
			{
			}
		#endif*/
	#elseif YSIM_HAS_MASTER
		stock
			_E_YCM:_YCM@ = _E_YCM@n;
	#else
		stock
			_E_YCM:_YCM@ = _E_YCM@y;
	#endif
#endif

#if defined YSIM_T_ENABLE
	#undef YSIM_T_ENABLE
#endif

#if defined YSIM_T_DISABLE
	#undef YSIM_T_DISABLE
#endif

#if defined YSIM_C_ENABLE
	#undef YSIM_C_ENABLE
#endif

#if defined YSIM_C_DISABLE
	#undef YSIM_C_DISABLE
#endif

#if defined YSIM_S_ENABLE
	#undef YSIM_S_ENABLE
#endif

#if defined YSIM_S_DISABLE
	#undef YSIM_S_DISABLE
#endif

#if defined YSIM_U_ENABLE
	#undef YSIM_U_ENABLE
#endif

#if defined YSIM_U_DISABLE
	#undef YSIM_U_DISABLE
#endif

// Allow YSI scripts to use the extended master system
/*#if defined _YSIM_USED_AUTO
	#undef _YSIM_USED_AUTO
#endif*/

#if defined _YSIM_OVERRIDE
	#undef _YSIM_OVERRIDE
#endif

#if defined YSIM_STORED_SETTINGS
	#undef YSIM_STORED_SETTINGS
#endif

// Clean up the new library definition code.
#if defined _YSIM_LAST_LIBRARY_MASTER
	#undef _YSIM_LAST_LIBRARY_MASTER
#endif

#if defined LIBRARY_MASTER
	#if LIBRARY_MASTER == 0
		#define _YSIM_LAST_LIBRARY_MASTER 0
	#elseif LIBRARY_MASTER == 1
		#define _YSIM_LAST_LIBRARY_MASTER 1
	#elseif LIBRARY_MASTER == 2
		#define _YSIM_LAST_LIBRARY_MASTER 2
	#elseif LIBRARY_MASTER == 3
		#define _YSIM_LAST_LIBRARY_MASTER 3
	#elseif LIBRARY_MASTER == 4
		#define _YSIM_LAST_LIBRARY_MASTER 4
	#elseif LIBRARY_MASTER == 5
		#define _YSIM_LAST_LIBRARY_MASTER 5
	#elseif LIBRARY_MASTER == 6
		#define _YSIM_LAST_LIBRARY_MASTER 6
	#elseif LIBRARY_MASTER == 7
		#define _YSIM_LAST_LIBRARY_MASTER 7
	#elseif LIBRARY_MASTER == 8
		#define _YSIM_LAST_LIBRARY_MASTER 8
	#elseif LIBRARY_MASTER == 9
		#define _YSIM_LAST_LIBRARY_MASTER 9
	#elseif LIBRARY_MASTER == 10
		#define _YSIM_LAST_LIBRARY_MASTER 10
	#elseif LIBRARY_MASTER == 11
		#define _YSIM_LAST_LIBRARY_MASTER 11
	#elseif LIBRARY_MASTER == 12
		#define _YSIM_LAST_LIBRARY_MASTER 12
	#elseif LIBRARY_MASTER == 13
		#define _YSIM_LAST_LIBRARY_MASTER 13
	#elseif LIBRARY_MASTER == 14
		#define _YSIM_LAST_LIBRARY_MASTER 14
	#elseif LIBRARY_MASTER == 15
		#define _YSIM_LAST_LIBRARY_MASTER 15
	#elseif LIBRARY_MASTER == 16
		#define _YSIM_LAST_LIBRARY_MASTER 16
	#elseif LIBRARY_MASTER == 17
		#define _YSIM_LAST_LIBRARY_MASTER 17
	#elseif LIBRARY_MASTER == 18
		#define _YSIM_LAST_LIBRARY_MASTER 18
	#elseif LIBRARY_MASTER == 19
		#define _YSIM_LAST_LIBRARY_MASTER 19
	#elseif LIBRARY_MASTER == 20
		#define _YSIM_LAST_LIBRARY_MASTER 20
	#elseif LIBRARY_MASTER == 21
		#define _YSIM_LAST_LIBRARY_MASTER 21
	#elseif LIBRARY_MASTER == 22
		#define _YSIM_LAST_LIBRARY_MASTER 22
	#elseif LIBRARY_MASTER == 23
		#define _YSIM_LAST_LIBRARY_MASTER 23
	#elseif LIBRARY_MASTER == 24
		#define _YSIM_LAST_LIBRARY_MASTER 24
	#elseif LIBRARY_MASTER == 25
		#define _YSIM_LAST_LIBRARY_MASTER 25
	#endif
	#undef LIBRARY_MASTER
#endif

#if defined YSIM_LIBRARY_OVERRIDE
	#undef YSIM_LIBRARY_OVERRIDE
#endif
