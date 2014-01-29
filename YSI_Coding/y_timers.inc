/**--------------------------------------------------------------------------**\
					  ====================================
					   y_timers - Run timers efficiently. 
					  ====================================
Description:
	Sets up repeating timers without requiring any SetTimers and arranges them
	so that they will be very unlikely to meet (at least for a long time) using
	scheduling algorithms to get timers with the same period to be offset.  Also
	fixes arrays and strings in timers so they can be passed properly.
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
	
	The Original Code is the YSI timers include.
	
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
	2.0
Changelog:
	29/04/11:
		Added version 2 of the code with more advanced options.
	21/03/11:
		Added debug printing to timer functions.  Uses "P:C" in compiling.
	26/10/10:
		Officially added simple calling.
		Added "delay" functions.
	12/10/10:
		Rewrote for YSI 1.0 using y_scripting.
	11/08/07:
		Removed millions of defines to reduce pre-processing.
		Added pickups.
	03/08/07:
		First version.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_timers
	#endinput
#endif
#define _INC_y_timers

// y_uvars

#if defined USE_Y_TIMERS_V1
	#error y_timers version 1 has not worked in years!
	#include "y_timers/v1"
	#endinput
#endif

#include "..\YSI_Internal\y_plugins"

#include "..\YSI_Internal\y_version"

#include "..\YSI_Storage\y_amx"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Coding\y_malloc"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Coding\y_hooks"
#include "..\YSI_Core\y_debug"

#include "y_timers/impl"
#if defined _YSI_PLUGINS_FIXES_2
	//#error V3
	#include "y_timers/v3"
#else
	#include "y_timers/v2"
#endif

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_timers/tests"
#endif
