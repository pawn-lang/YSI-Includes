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

// These are the tag-type definitions for the various possible parameter types.
// Array-like definitions.
#define @Yf:@Yg:@Yh:#%0#%1|||%3[%4]|||%5,%6;%9||| @Yc:@Ye:@Yw:#%0#%1|||%3[%4]|||%5,%6;%9|||

// `const`
#define @Yc:@Ye:@Yw:#%0#%1|||%2const%3|||%5,%6;%9||| @Ye:@Yw:#%0#%1|||%3|||%5,%6;%9|||
#define @Ye:@Yw:#%0#%1|||%2string:%3[%4]|||%5,%6;%9||| @Yf:@Yg:@Yh:#%0d#%1,_Timer_S(%3)|||%5|||%6;%9,@Yv&%3&|||

// This one has an extra parameter because arrays must always be followed by
// their length.
#define @Yw:#%0#%1|||%3[%4]|||%5,%6,%7;%9||| @Yf:@Yg:@Yh:#%0d#%1,_Timer_A(%3,%5)|||%5|||%6,%7;%9,@Yv&%3&|||

// Tag-like definitions.
#define @Yg:@Yh:#%0#%1|||%2:%3|||%5,%6;%9||| @Yf:@Yg:@Yh:#%0d#%1,%2:%3|||%5|||%6;%9,%2:%3|||

// Others.
#define @Yh:#%0#%1|||%3|||%5,%6;%9||| @Yf:@Yg:@Yh:#%0d#%1,%3|||%5|||%6;%9,%3|||

// Main entry point for DEFER__ type determination.
#define _YT@CR:%0,%1)%2||| @Yf:@Yg:@Yh:#i#,@Yx:_Timer_B(J@)|||%0|||%1;%2|||

// Define for "DEFER__" with timer, parameters and main function.
#define TIMER__%0[%1]%3(%2) stock Timer:_yT@%0(%2)return _Timer_C(O@(#@_yT%0,(I@==-1)?(%1):I@,true,_YT@CR:%2,,)%0|||%0|||(%2)

// Expand additional parameters out to three functions after processing.
#define @Yx:%0||||||;%1,%2|||%4||| %0));@Yj:@_yT%1(Timer:__r,%2);@Yj:@_yT%1(Timer:__r,%2){_YSI_g_sCurrentTimer=__r,%4(%2),_Timer_F();}%4

// Can't believe I never thought of this before!  If only there was a way to
// make it less generic than "id".
#define id#,@Yx:_Timer_B(J@),||||||;%1,%2|||%4||| i,_Timer_B(J@)));@Yj:@_yT%1(Timer:__r);@Yj:@_yT%1(Timer:__r){_YSI_g_sCurrentTimer=__r,%4(),_Timer_F();}%4

// Remove excess "_Timer_G" and "_Timer_B".
#define @Yj:%0(%5){%1(%8&%2&%3)%9} @Yj:%0(%5){%1(%8:YSI_gMallocMemory[%2]%3)%9}
#define @Yv&%0& %0

#define DEFER__%0(%1) (J@=1,I@=-1,Timer:_yT@%0(%1))

#define REPEAT__%0(%1) (J@=0,I@=-1,Timer:_yT@%0(%1))

// Detect explicit repeat counts.
#define J@=0,I@=-1,Timer:_yT@[%4] J@=(%4),I@=-1,Timer:_yT@

// Custom time.
#define Timer:%0[%1](%2) I@=%1,Timer:%0(%2)

#define STOP__%0; {_Timer_F((%0),1);}

// `stop` given without a timer ID - kill the current one.
#define _Timer_F((),1) _Timer_F(_,2)

