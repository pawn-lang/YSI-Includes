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

#if defined _inc__setup_master_C
	#undef _inc__setup_master_C
#endif

#if MASTER == 32
	#define _MASTER 32
	#define YSIM_STORED_SETTINGS YSIM_RECALL_32
	#if defined _YCM_@G
		#define YSIM_DEFINED
	#else
		#define _YCM_@G
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_32 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_32 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_32 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_32 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_32 4
		#else
			#error Undefined master type on 32
		#endif
	#endif
	#define _YCM @G
	#define MAKE_YCM<%0...%1> %0@G%1
	#define _YCM@ _YCM_g@G
	#endinput
#elseif MASTER == 33
	#define _MASTER 33
	#define YSIM_STORED_SETTINGS YSIM_RECALL_33
	#if defined _YCM_@H
		#define YSIM_DEFINED
	#else
		#define _YCM_@H
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_33 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_33 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_33 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_33 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_33 4
		#else
			#error Undefined master type on 33
		#endif
	#endif
	#define _YCM @H
	#define MAKE_YCM<%0...%1> %0@H%1
	#define _YCM@ _YCM_g@H
	#endinput
#elseif MASTER == 34
	#define _MASTER 34
	#define YSIM_STORED_SETTINGS YSIM_RECALL_34
	#if defined _YCM_@I
		#define YSIM_DEFINED
	#else
		#define _YCM_@I
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_34 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_34 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_34 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_34 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_34 4
		#else
			#error Undefined master type on 34
		#endif
	#endif
	#define _YCM @I
	#define MAKE_YCM<%0...%1> %0@I%1
	#define _YCM@ _YCM_g@I
	#endinput
#elseif MASTER == 35
	#define _MASTER 35
	#define YSIM_STORED_SETTINGS YSIM_RECALL_35
	#if defined _YCM_@J
		#define YSIM_DEFINED
	#else
		#define _YCM_@J
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_35 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_35 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_35 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_35 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_35 4
		#else
			#error Undefined master type on 35
		#endif
	#endif
	#define _YCM @J
	#define MAKE_YCM<%0...%1> %0@J%1
	#define _YCM@ _YCM_g@J
	#endinput
#elseif MASTER == 36
	#define _MASTER 36
	#define YSIM_STORED_SETTINGS YSIM_RECALL_36
	#if defined _YCM_@K
		#define YSIM_DEFINED
	#else
		#define _YCM_@K
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_36 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_36 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_36 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_36 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_36 4
		#else
			#error Undefined master type on 36
		#endif
	#endif
	#define _YCM @K
	#define MAKE_YCM<%0...%1> %0@K%1
	#define _YCM@ _YCM_g@K
	#endinput
#elseif MASTER == 37
	#define _MASTER 37
	#define YSIM_STORED_SETTINGS YSIM_RECALL_37
	#if defined _YCM_@L
		#define YSIM_DEFINED
	#else
		#define _YCM_@L
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_37 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_37 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_37 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_37 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_37 4
		#else
			#error Undefined master type on 37
		#endif
	#endif
	#define _YCM @L
	#define MAKE_YCM<%0...%1> %0@L%1
	#define _YCM@ _YCM_g@L
	#endinput
#elseif MASTER == 38
	#define _MASTER 38
	#define YSIM_STORED_SETTINGS YSIM_RECALL_38
	#if defined _YCM_@M
		#define YSIM_DEFINED
	#else
		#define _YCM_@M
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_38 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_38 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_38 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_38 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_38 4
		#else
			#error Undefined master type on 38
		#endif
	#endif
	#define _YCM @M
	#define MAKE_YCM<%0...%1> %0@M%1
	#define _YCM@ _YCM_g@M
	#endinput
#elseif MASTER == 39
	#define _MASTER 39
	#define YSIM_STORED_SETTINGS YSIM_RECALL_39
	#if defined _YCM_@N
		#define YSIM_DEFINED
	#else
		#define _YCM_@N
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_39 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_39 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_39 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_39 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_39 4
		#else
			#error Undefined master type on 39
		#endif
	#endif
	#define _YCM @N
	#define MAKE_YCM<%0...%1> %0@N%1
	#define _YCM@ _YCM_g@N
	#endinput
#elseif MASTER == 40
	#define _MASTER 40
	#define YSIM_STORED_SETTINGS YSIM_RECALL_40
	#if defined _YCM_@O
		#define YSIM_DEFINED
	#else
		#define _YCM_@O
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_40 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_40 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_40 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_40 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_40 4
		#else
			#error Undefined master type on 40
		#endif
	#endif
	#define _YCM @O
	#define MAKE_YCM<%0...%1> %0@O%1
	#define _YCM@ _YCM_g@O
	#endinput
#elseif MASTER == 41
	#define _MASTER 41
	#define YSIM_STORED_SETTINGS YSIM_RECALL_41
	#if defined _YCM_@P
		#define YSIM_DEFINED
	#else
		#define _YCM_@P
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_41 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_41 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_41 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_41 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_41 4
		#else
			#error Undefined master type on 41
		#endif
	#endif
	#define _YCM @P
	#define MAKE_YCM<%0...%1> %0@P%1
	#define _YCM@ _YCM_g@P
	#endinput
#elseif MASTER == 42
	#define _MASTER 42
	#define YSIM_STORED_SETTINGS YSIM_RECALL_42
	#if defined _YCM_@Q
		#define YSIM_DEFINED
	#else
		#define _YCM_@Q
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_42 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_42 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_42 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_42 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_42 4
		#else
			#error Undefined master type on 42
		#endif
	#endif
	#define _YCM @Q
	#define MAKE_YCM<%0...%1> %0@Q%1
	#define _YCM@ _YCM_g@Q
	#endinput
#elseif MASTER == 43
	#define _MASTER 43
	#define YSIM_STORED_SETTINGS YSIM_RECALL_43
	#if defined _YCM_@R
		#define YSIM_DEFINED
	#else
		#define _YCM_@R
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_43 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_43 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_43 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_43 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_43 4
		#else
			#error Undefined master type on 43
		#endif
	#endif
	#define _YCM @R
	#define MAKE_YCM<%0...%1> %0@R%1
	#define _YCM@ _YCM_g@R
	#endinput
#elseif MASTER == 44
	#define _MASTER 44
	#define YSIM_STORED_SETTINGS YSIM_RECALL_44
	#if defined _YCM_@S
		#define YSIM_DEFINED
	#else
		#define _YCM_@S
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_44 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_44 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_44 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_44 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_44 4
		#else
			#error Undefined master type on 44
		#endif
	#endif
	#define _YCM @S
	#define MAKE_YCM<%0...%1> %0@S%1
	#define _YCM@ _YCM_g@S
	#endinput
#elseif MASTER == 45
	#define _MASTER 45
	#define YSIM_STORED_SETTINGS YSIM_RECALL_45
	#if defined _YCM_@T
		#define YSIM_DEFINED
	#else
		#define _YCM_@T
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_45 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_45 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_45 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_45 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_45 4
		#else
			#error Undefined master type on 45
		#endif
	#endif
	#define _YCM @T
	#define MAKE_YCM<%0...%1> %0@T%1
	#define _YCM@ _YCM_g@T
	#endinput
#elseif MASTER == 46
	#define _MASTER 46
	#define YSIM_STORED_SETTINGS YSIM_RECALL_46
	#if defined _YCM_@U
		#define YSIM_DEFINED
	#else
		#define _YCM_@U
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_46 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_46 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_46 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_46 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_46 4
		#else
			#error Undefined master type on 46
		#endif
	#endif
	#define _YCM @U
	#define MAKE_YCM<%0...%1> %0@U%1
	#define _YCM@ _YCM_g@U
	#endinput
#elseif MASTER == 47
	#define _MASTER 47
	#define YSIM_STORED_SETTINGS YSIM_RECALL_47
	#if defined _YCM_@V
		#define YSIM_DEFINED
	#else
		#define _YCM_@V
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_47 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_47 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_47 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_47 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_47 4
		#else
			#error Undefined master type on 47
		#endif
	#endif
	#define _YCM @V
	#define MAKE_YCM<%0...%1> %0@V%1
	#define _YCM@ _YCM_g@V
	#endinput
#endif

