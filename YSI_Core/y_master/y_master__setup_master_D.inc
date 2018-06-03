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

#if defined _inc_y_master__setup_master_D
	#undef _inc_y_master__setup_master_D
#endif

#if MASTER == 48
	#define _MASTER 48
	#define YSIM_STORED_SETTINGS YSIM_RECALL_48
	#if defined _YCM_@W
		#define YSIM_DEFINED
	#else
		#define _YCM_@W
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_48 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_48 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_48 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_48 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_48 4
		#else
			#error Undefined master type on 48
		#endif
	#endif
	#define _YCM @W
	#define MAKE_YCM<%0...%1> %0@W%1
	#define _YCM@ _YCM_g@W
	#endinput
#elseif MASTER == 49
	#define _MASTER 49
	#define YSIM_STORED_SETTINGS YSIM_RECALL_49
	#if defined _YCM_@X
		#define YSIM_DEFINED
	#else
		#define _YCM_@X
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_49 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_49 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_49 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_49 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_49 4
		#else
			#error Undefined master type on 49
		#endif
	#endif
	#define _YCM @X
	#define MAKE_YCM<%0...%1> %0@X%1
	#define _YCM@ _YCM_g@X
	#endinput
#elseif MASTER == 50
	#define _MASTER 50
	#define YSIM_STORED_SETTINGS YSIM_RECALL_50
	#if defined _YCM_@Y
		#define YSIM_DEFINED
	#else
		#define _YCM_@Y
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_50 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_50 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_50 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_50 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_50 4
		#else
			#error Undefined master type on 50
		#endif
	#endif
	#define _YCM @Y
	#define MAKE_YCM<%0...%1> %0@Y%1
	#define _YCM@ _YCM_g@Y
	#endinput
#elseif MASTER == 51
	#define _MASTER 51
	#define YSIM_STORED_SETTINGS YSIM_RECALL_51
	#if defined _YCM_@Z
		#define YSIM_DEFINED
	#else
		#define _YCM_@Z
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_51 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_51 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_51 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_51 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_51 4
		#else
			#error Undefined master type on 51
		#endif
	#endif
	#define _YCM @Z
	#define MAKE_YCM<%0...%1> %0@Z%1
	#define _YCM@ _YCM_g@Z
	#endinput
#elseif MASTER == 52
	#define _MASTER 52
	#define YSIM_STORED_SETTINGS YSIM_RECALL_52
	#if defined _YCM_@0
		#define YSIM_DEFINED
	#else
		#define _YCM_@0
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_52 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_52 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_52 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_52 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_52 4
		#else
			#error Undefined master type on 52
		#endif
	#endif
	#define _YCM @0
	#define MAKE_YCM<%0...%1> %0@0%1
	#define _YCM@ _YCM_g@0
	#endinput
#elseif MASTER == 53
	#define _MASTER 53
	#define YSIM_STORED_SETTINGS YSIM_RECALL_53
	#if defined _YCM_@1
		#define YSIM_DEFINED
	#else
		#define _YCM_@1
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_53 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_53 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_53 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_53 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_53 4
		#else
			#error Undefined master type on 53
		#endif
	#endif
	#define _YCM @1
	#define MAKE_YCM<%0...%1> %0@1%1
	#define _YCM@ _YCM_g@1
	#endinput
#elseif MASTER == 54
	#define _MASTER 54
	#define YSIM_STORED_SETTINGS YSIM_RECALL_54
	#if defined _YCM_@2
		#define YSIM_DEFINED
	#else
		#define _YCM_@2
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_54 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_54 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_54 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_54 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_54 4
		#else
			#error Undefined master type on 54
		#endif
	#endif
	#define _YCM @2
	#define MAKE_YCM<%0...%1> %0@2%1
	#define _YCM@ _YCM_g@2
	#endinput
#elseif MASTER == 55
	#define _MASTER 55
	#define YSIM_STORED_SETTINGS YSIM_RECALL_55
	#if defined _YCM_@3
		#define YSIM_DEFINED
	#else
		#define _YCM_@3
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_55 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_55 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_55 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_55 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_55 4
		#else
			#error Undefined master type on 55
		#endif
	#endif
	#define _YCM @3
	#define MAKE_YCM<%0...%1> %0@3%1
	#define _YCM@ _YCM_g@3
	#endinput
#elseif MASTER == 56
	#define _MASTER 56
	#define YSIM_STORED_SETTINGS YSIM_RECALL_56
	#if defined _YCM_@4
		#define YSIM_DEFINED
	#else
		#define _YCM_@4
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_56 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_56 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_56 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_56 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_56 4
		#else
			#error Undefined master type on 56
		#endif
	#endif
	#define _YCM @4
	#define MAKE_YCM<%0...%1> %0@4%1
	#define _YCM@ _YCM_g@4
	#endinput
#elseif MASTER == 57
	#define _MASTER 57
	#define YSIM_STORED_SETTINGS YSIM_RECALL_57
	#if defined _YCM_@5
		#define YSIM_DEFINED
	#else
		#define _YCM_@5
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_57 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_57 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_57 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_57 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_57 4
		#else
			#error Undefined master type on 57
		#endif
	#endif
	#define _YCM @5
	#define MAKE_YCM<%0...%1> %0@5%1
	#define _YCM@ _YCM_g@5
	#endinput
#elseif MASTER == 58
	#define _MASTER 58
	#define YSIM_STORED_SETTINGS YSIM_RECALL_58
	#if defined _YCM_@6
		#define YSIM_DEFINED
	#else
		#define _YCM_@6
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_58 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_58 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_58 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_58 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_58 4
		#else
			#error Undefined master type on 58
		#endif
	#endif
	#define _YCM @6
	#define MAKE_YCM<%0...%1> %0@6%1
	#define _YCM@ _YCM_g@6
	#endinput
#elseif MASTER == 59
	#define _MASTER 59
	#define YSIM_STORED_SETTINGS YSIM_RECALL_59
	#if defined _YCM_@7
		#define YSIM_DEFINED
	#else
		#define _YCM_@7
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_59 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_59 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_59 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_59 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_59 4
		#else
			#error Undefined master type on 59
		#endif
	#endif
	#define _YCM @7
	#define MAKE_YCM<%0...%1> %0@7%1
	#define _YCM@ _YCM_g@7
	#endinput
#elseif MASTER == 60
	#define _MASTER 60
	#define YSIM_STORED_SETTINGS YSIM_RECALL_60
	#if defined _YCM_@8
		#define YSIM_DEFINED
	#else
		#define _YCM_@8
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_60 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_60 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_60 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_60 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_60 4
		#else
			#error Undefined master type on 60
		#endif
	#endif
	#define _YCM @8
	#define MAKE_YCM<%0...%1> %0@8%1
	#define _YCM@ _YCM_g@8
	#endinput
#elseif MASTER == 61
	#define _MASTER 61
	#define YSIM_STORED_SETTINGS YSIM_RECALL_61
	#if defined _YCM_@9
		#define YSIM_DEFINED
	#else
		#define _YCM_@9
		// Save the settings.
		#include "y_master__resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_61 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_61 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_61 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_61 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_61 4
		#else
			#error Undefined master type on 61
		#endif
	#endif
	#define _YCM @9
	#define MAKE_YCM<%0...%1> %0@9%1
	#define _YCM@ _YCM_g@9
	#endinput
#endif

