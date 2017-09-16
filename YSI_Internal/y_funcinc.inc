#if defined _INC_y_funcinc
	#endinput
#endif
#define _INC_y_funcinc

/*+
 * <library name="y_funcinc">
 * <section>
 *  Description
 * </section>
 *  Calls functions which are used in SYSREQ.C calls before they are used.  The
 *  compiler crashes if the functions are not used in an included function
 *  before being used in a SYSREQ.C call as the function is not in the native
 *  functions table.
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
 *//** *//*
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

forward _@_y_funcinc_@_();

public _@_y_funcinc_@_()
{
	new _funcinc_a[1 char];
	// This function calls any functions used in assembly code in YSI to ensure
	// that they are included in the native function table.
	printf("");
	strunpack(_funcinc_a, "");
	memcpy("", "", 0, 0, 0);
	format("", 0, "");
	strfind("", "", false, 0);
	strcat(_funcinc_a, "", 0);
	strlen("");
	CallRemoteFunction("", "");
	CallLocalFunction("", "");
	SetTimerEx("", 0, 0, "");
	heapspace();
	setproperty(0, "", 0, "");
	getproperty(0, "", 0, _funcinc_a);
	memset("", 0, 0);
	strcmp("", "");
}

