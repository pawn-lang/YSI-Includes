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

// These are the tag-type definitions for the various possible parameter types.
// Array-like definitions.
#define @Yf:@Yg:@Yh:@Yx:#%0#%1|||%3[%4]|||%5,%6;%9||| @Ye:@Yw:#%0#%1|||%3[%4]|||%5,%6;%9|||

#define @Ye:@Yw:#%0#%1|||%2string:%3[%4]|||%5,%6;%9||| @Yf:@Yg:@Yh:@Yx:#%0s#%1,%3|||%5|||%6;%9,%3|||

// This one has an extra parameter because arrays must always be followed by
// their length.
#define @Yw:#%0#%1|||%3[%4]|||%5,%6,%7;%9||| @Yf:@Yg:@Yh:@Yx:#%0ad#%1,%3,%5|||%6|||%7;%9,%3,%5|||

// Tag-like definitions.
#define @Yg:@Yh:@Yx:#%0#%1|||%2:%3|||%5,%6;%9||| @Yf:@Yg:@Yh:@Yx:#%0d#%1,%2:%3|||%5|||%6;%9,%2:%3|||

// Others.
#define @Yh:@Yx:#%0#%1|||%3|||%5,%6;%9||| @Yf:@Yg:@Yh:@Yx:#%0d#%1,%3|||%5|||%6;%9,%3|||

// Main entry point for defer type determination.
#define _YT@CR:%0,%1)%2||| @Yf:@Yg:@Yh:@Yx:##|||%0|||%1;%2|||

// Define for "defer" with timer, parameters and main function.
#define YSI_timer%0[%1]%3(%2) stock%0_yT@(%2)return SetTimerEx(#%0,(I@==-1)?(%1):I@,@Yj:J@,_YT@CR:%2,,)%0|||%0|||(%2)

// Expand additional parameters out to three functions after processing.
#define @Yx:%0||||||;%1,%2|||%4|||(%5) %0);%1(%5);public%4(%5)

// Can't believe I never thought of this before!  If only there was a way to
// make it less generic than "id".
#define @Yj:J@,_YT@CR:,,)%0|||%1|||(%3) J@,#);%0();public%0()

#define defer%0(%1) (J@=0,I@=-1,Timer:%0_yT@(%1))

#define repeat%0(%1) (J@=1,I@=-1,Timer:%0_yT@(%1))

// Custom time.
#define Timer:%0[%1]_yT@(%2) I@=%1,Timer:%0_yT@(%2)

#define stop%0; {KillTimer(_:%0);}
