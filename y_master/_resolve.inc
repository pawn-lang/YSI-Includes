/**--------------------------------------------------------------------------**\
					=================================
					 y_masterresolve - Settings.
					=================================
Description:
	Determine how the master system has been included; client, server, etc.
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
	
	The Original Code is the YSI utils include.
	
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
	0.1
Changelog:
	25/02/12:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
</remarks>
\**--------------------------------------------------------------------------**/

#undef _inc__resolve

#if (!defined YSI_NO_MASTER || defined YSIM_T_ENABLE) && !defined YSIM_T_DISABLE
	#define YSIM_HAS_MASTER 1
#else
	#define YSIM_HAS_MASTER 0
#endif

#if (defined YSI_IS_CLIENT || defined YSIM_C_ENABLE) && !defined YSIM_C_DISABLE
	#define _YSIM_IS_CLIENT 1
#else
	#define _YSIM_IS_CLIENT 0
#endif

#if (defined YSI_IS_SERVER || defined YSIM_S_ENABLE) && !defined YSIM_S_DISABLE
	#define _YSIM_IS_SERVER 1
#else
	#define _YSIM_IS_SERVER 0
#endif

#if (defined YSI_IS_STUB || defined YSIM_U_ENABLE) && !defined YSIM_U_DISABLE
	#define _YSIM_IS_STUB 1
#else
	#define _YSIM_IS_STUB 0
#endif

// Can't be "stub", "client", or "server" if there's no master.
#if !YSIM_HAS_MASTER && _YSIM_IS_CLIENT
	#undef _YSIM_IS_CLIENT
	#define _YSIM_IS_CLIENT 0
#endif

#if !YSIM_HAS_MASTER && _YSIM_IS_SERVER
	#undef _YSIM_IS_SERVER
	#define _YSIM_IS_SERVER 0
#endif

#if !YSIM_HAS_MASTER && _YSIM_IS_STUB
	#undef _YSIM_IS_STUB
	#define _YSIM_IS_STUB 0
#endif

// Are there any conflicts, determine which is better.
#if _YSIM_IS_CLIENT && _YSIM_IS_SERVER
	#if defined YSIM_C_ENABLE
		#if defined YSIM_S_ENABLE
			// Both on temporary enable.
			#error YSIM_C_ENABLE and YSIM_S_ENABLE both defined.
		#else
			// Client override.
			#undef _YSIM_IS_SERVER
			#define _YSIM_IS_SERVER 0
		#endif
	#else
		#if defined YSIM_S_ENABLE
			// Server override.
			#undef _YSIM_IS_CLIENT
			#define _YSIM_IS_CLIENT 0
		#else
			// Neither defined locally.
			#if YSI_IS_SERVER > YSI_IS_CLIENT
				// Client override.
				#undef _YSIM_IS_SERVER
				#define _YSIM_IS_SERVER 0
			#else
				// Server override.
				#undef _YSIM_IS_CLIENT
				#define _YSIM_IS_CLIENT 0
			#endif
		#endif
	#endif
#endif

// Are there any conflicts, determine which is better.
#if _YSIM_IS_STUB && _YSIM_IS_SERVER
	#if defined YSIM_U_ENABLE
		#if defined YSIM_S_ENABLE
			// Both on temporary enable.
			#error YSIM_U_ENABLE and YSIM_S_ENABLE both defined.
		#else
			// Stub override.
			#undef _YSIM_IS_SERVER
			#define _YSIM_IS_SERVER 0
		#endif
	#else
		#if defined YSIM_S_ENABLE
			// Server override.
			#undef _YSIM_IS_STUB
			#define _YSIM_IS_STUB 0
		#else
			// Neither defined locally.
			#if YSI_IS_SERVER > YSI_IS_STUB
				// Stub override.
				#undef _YSIM_IS_SERVER
				#define _YSIM_IS_SERVER 0
			#else
				// Server override.
				#undef _YSIM_IS_STUB
				#define _YSIM_IS_STUB 0
			#endif
		#endif
	#endif
#endif

// Are there any conflicts, determine which is better.
#if _YSIM_IS_STUB && _YSIM_IS_CLIENT
	#if defined YSIM_U_ENABLE
		#if defined YSIM_C_ENABLE
			// Both on temporary enable.
			#error YSIM_U_ENABLE and YSIM_C_ENABLE both defined.
		#else
			// Stub override.
			#undef _YSIM_IS_CLIENT
			#define _YSIM_IS_CLIENT 0
		#endif
	#else
		#if defined YSIM_C_ENABLE
			// Client override.
			#undef _YSIM_IS_STUB
			#define _YSIM_IS_STUB 0
		#else
			// Neither defined locally.
			#if YSI_IS_CLIENT > YSI_IS_STUB
				// Stub override.
				#undef _YSIM_IS_CLIENT
				#define _YSIM_IS_CLIENT 0
			#else
				// Client override.
				#undef _YSIM_IS_STUB
				#define _YSIM_IS_STUB 0
			#endif
		#endif
	#endif
#endif

// Default to cloud.
#if YSIM_HAS_MASTER && !_YSIM_IS_CLIENT && !_YSIM_IS_SERVER && !_YSIM_IS_STUB
	#define _YSIM_IS_CLOUD 1
#else
	#define _YSIM_IS_CLOUD 0
#endif

