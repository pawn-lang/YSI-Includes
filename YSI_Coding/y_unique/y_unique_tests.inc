/*+
 * <library
 *   name="y_unique"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Defines a symbol differently every time it is included."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
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

#if !defined UNIQUE_FUNCTION
	#define UNIQUE_FUNCTION<%0...%1> %0000%1
#endif

#if !defined UNIQUE_SYMBOL
	#define UNIQUE_SYMBOL (0)
#endif

// This slightly hacks the numbers by relying on `else`.
#undef UNIQUE_FUNCTION
#include "y_unique_1024_1087"

static stock y_unique_GetNumber0()
{
	return UNIQUE_SYMBOL;
}

#undef UNIQUE_FUNCTION
#include "y_unique_1024_1087"

static stock y_unique_GetNumber1()
{
	return UNIQUE_SYMBOL;
}

#undef UNIQUE_FUNCTION
#include "y_unique_1024_1087"

static stock y_unique_GetNumber2()
{
	return UNIQUE_SYMBOL;
}

#undef UNIQUE_FUNCTION
#include "y_unique_1024_1087"

@test(.group = "y_unique") y_unique()
{
	new n = UNIQUE_SYMBOL;
	ASSERT_EQ(y_unique_GetNumber0(), 1031);
	ASSERT_EQ(y_unique_GetNumber1(), 1032);
	ASSERT_EQ(y_unique_GetNumber2(), 1033);
	ASSERT_EQ(n, 1034);
}

