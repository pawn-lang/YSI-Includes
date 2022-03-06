/*+
 * <library
 *   name="y_stripnumbers"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     Removes tag overrides which are actually numbers.  This allows for:
 *   
 *     <code>
 *         uvar g_a[MAX_PLAYERS][E_SOME_ENUM]; <br />
 *         uvar g_b[MAX_PLAYERS][42];
 *     </code>
 *   
 *     Without stripping you would end with code doing "42:0" or getting a tag
 *     mismatch on "E_SOME_ENUM", both of which are problems.
 *   </remarks>
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

// This code uses the "@S.:" prefix, where "." is a number or underscore (for
// any other symbol.  y_stringise (aka. y_stringize) uses several letters from
// this same set.
#define STRIP_NUMBERS:%0|||%1:%2||| _:@S0:@S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||%1:%2|||

#define @S0:@S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||0%1:%2||| %0[%2]
#define @S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||1%1:%2||| %0[%2]
#define @S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||2%1:%2||| %0[%2]
#define @S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||3%1:%2||| %0[%2]
#define @S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||4%1:%2||| %0[%2]
#define @S5:@S6:@S7:@S8:@S9:@S_:%0|||5%1:%2||| %0[%2]
#define @S6:@S7:@S8:@S9:@S_:%0|||6%1:%2||| %0[%2]
#define @S7:@S8:@S9:@S_:%0|||7%1:%2||| %0[%2]
#define @S8:@S9:@S_:%0|||8%1:%2||| %0[%2]
#define @S9:@S_:%0|||9%1:%2||| %0[%2]
#define @S_:%0|||%1:%2||| %0[%1:%2]
