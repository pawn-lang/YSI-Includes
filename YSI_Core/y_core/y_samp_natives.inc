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
native YSI_Print(const string[]) = print;
native YSI_PrintF(const format[], GLOBAL_TAG_TYPES:...) = printf;

native YSI_SetTimer(const funcname[], interval, bool:repeating) = SetTimer;
native YSI_SetTimerEx(const funcname[], interval, bool:repeating, const format[], GLOBAL_TAG_TYPES:...) = SetTimerEx;

native YSI_HTTP(index, type, const url[], const data[], const callback[]) = HTTP;
native YSI_Format(dest[], size = sizeof (dest), const format[], GLOBAL_TAG_TYPES:...) = format;

native YSI_SendRconCommand(const str[]) = SendRconCommand;
native YSI_SendClientCheck(playerid, type, memoryAddress, memoryOffset, byteCount) = SendClientCheck;
native YSI_SHA256Hash_BAD_DONT_USE(const password[], const salt[], output[], size = sizeof (output)) = SHA256_PassHash;

// Proper casing.
native YSI_Random(max) = random;
native _YSI_ConstCpy(const dst[], const src[], index, numbytes, maxlength) = memcpy;

#define YSI_JOIN(%0,%1,%2) %0And%1And%2

native _YSI_FGetChar(File:handle, value, bool:utf8 = true) = fgetchar;
#define YSI_FGetChar(%0,%1) _YSI_FGetChar((%0),_:(%1),(%1))

