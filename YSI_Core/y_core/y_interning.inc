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

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c></c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_EMPTY[] = "";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c> </c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_SPACE[] = " ";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>i</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcI[] = "i";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>ii</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcII[] = "ii";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>iii</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcIII[] = "iii";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>iiii</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcIIII[] = "iiii";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>f</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcF[] = "f";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>s</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcS[] = "s";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>si</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcSI[] = "si";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>isi</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcISI[] = "isi";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>isii</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcISII[] = "isii";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>isiii</c> defined just once for repeated use.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcISIII[] = "isiii";

/*-------------------------------------------------------------------------*//**
 * <library>y_interning</library>
 * <remarks>
 *   The string <c>iiiiiiiiiiiiiiiii</c> defined just once for repeated use.
 *   Yes, believe it or not this ridiculous string is used in YSI!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock const
	YSI_gcIIIIIIIIIIIIIIIII[] = "iiiiiiiiiiiiiiiii";

