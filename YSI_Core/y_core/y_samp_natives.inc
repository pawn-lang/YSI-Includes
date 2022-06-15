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

// These should pretty much always exist, but are defined in "a_samp" in SA:MP,
// when they should really be "core" functions.
// 
// TODO: Detect new line requirements.
//
// TODO: Figure out what I meant by that `TODO` above...
//
native YSI_Print__(const string[]) = print;
native YSI_PrintF__(const format[], GLOBAL_TAG_TYPES:...) = printf;

native YSI_SetTimer__(const funcname[], interval, bool:repeating) = SetTimer;
native YSI_SetTimerEx__(const funcname[], interval, bool:repeating, const format[], GLOBAL_TAG_TYPES:...) = SetTimerEx;

native YSI_HTTP__(index, type, const url[], const data[], const callback[]) = HTTP;
native YSI_Format__(dest[], size = sizeof (dest), const format[], GLOBAL_TAG_TYPES:...) = format;

native YSI_SendRconCommand__(const str[]) = SendRconCommand;
native YSI_SendClientCheck__(playerid, type, memoryAddress, memoryOffset, byteCount) = SendClientCheck;
native YSI_SHA256Hash_BAD_DONT_USE__(const password[], const salt[], output[], size = sizeof (output)) = SHA256_PassHash;

// Proper casing.
native YSI_Random__(max) = random;
native _YSI_ConstCpy__(const dst[], const src[], index, numbytes, maxlength) = memcpy;

#define YSI_JOIN(%0,%1,%2) %0And%1And%2

native _YSI_FGetChar__(File:handle, value, bool:utf8 = true) = fgetchar;
#define YSI_FGetChar__(%0,%1) _YSI_FGetChar__((%0),_:(%1),(%1))

// open.mp exclusives.  This file might have to be renamed!
native YSI_ArgCount__() = argcount;
native bool:YSI_ArgIndex__(index, output[], size = sizeof (output), bool:pack = false) = argindex;

//#if defined NopNative
//	native YSI_NOP(GLOBAL_TAG_TYPES:...) = nop;
//#else
//	native YSI_NOP(GLOBAL_TAG_TYPES:...) = sendpacket;
//#endif

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif

#if defined _ALS_ShowPlayerDialog
	#define Dialog_ShowPlayerNative ShowPlayerDialog
#else
	native bool:Dialog_ShowPlayerNative(playerid, dialogid, DIALOG_STYLE:style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;
#endif

#if __COMPILER___EMIT_U
	#if cellbytes == 4
		#define YSI_IsLocalVarPackedString__(%0) \
			__emit(                         \
				LREF.S.pri  %0             ,\
				CONST.alt   0x01000000     ,\
				GEQ                         \
			)
		#endinput
	#elseif cellbytes == 8
		#define YSI_IsLocalVarPackedString__(%0) \
			__emit(                         \
				LREF.S.pri  %0             ,\
				CONST.alt   0x0100000000000000,\
				GEQ                         \
			)
		#endinput
	#else
		#error Unsupported packed string size.
	#endif
#endif

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  IsPacked(str[]);
 * </summary>
 * <param name="str">The string to test the packing of.</param>
 * <remarks>
 *   There is a bug in the SA:MP implementation of <c>ispacked</c>, it doesn't
 *   work with high unicode values.  This is fixed in open.mp, and the same fix
 *   is used here (just change the comparison to unsigned).  The inline assembly
 *   version above is actually faster than the native for locals.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if cellbytes != 4
	#error Unsupported packed string size.
#endif
stock bool:YSI_IsLocalVarPackedString__(const string:str[])
{
	#emit LREF.S.pri           str
	#emit CONST.alt            0x01000000
	#emit GEQ
	#emit RETN

	return false;
}

