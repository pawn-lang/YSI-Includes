#if defined _INC_y_va
	#endinput
#endif
#define _INC_y_va

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

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Core\y_core\y_thirdpartyinclude"

#if !defined YSI_MAX_INLINE_STRING
	#define YSI_MAX_INLINE_STRING YSI_MAX_STRING
#endif

#include "y_va_header"
#include "y_va_impl"

stock PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return CreatePlayerTextDraw(playerid, x, y, va_return(fmat, ___(4)));
}

stock Text:va_TextDrawCreate(Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return TextDrawCreate(x, y, va_return(fmat, ___(3)));
}

stock va_TextDrawSetString(Text:text, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return TextDrawSetString(text, va_return(fmat, ___(2)));
}

stock va_PlayerTextDrawSetString(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return PlayerTextDrawSetString(playerid, text, va_return(fmat, ___(3)));
}

stock va_SendClientMessage(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return SendClientMessage(playerid, colour, va_return(fmat, ___(3)));
}

stock va_SendClientMessageToAll(colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return SendClientMessageToAll(colour, va_return(fmat, ___(2)));
}

stock va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return SendPlayerMessageToPlayer(playerid, senderid, va_return(fmat, ___(3)));
}

stock va_SendPlayerMessageToAll(senderid, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return SendPlayerMessageToAll(senderid, va_return(fmat, ___(2)));
}

stock va_GameTextForPlayer(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...)
{
	return GameTextForPlayer(playerid, va_return(fmat, ___(4)), time, style);
}

stock va_GameTextForAll(const fmat[], time, style, GLOBAL_TAG_TYPES:...)
{
	return GameTextForAll(va_return(fmat, ___(3)), time, style);
}

stock va_print(const fmat[], GLOBAL_TAG_TYPES:...)
{
	return print(va_return(fmat, ___(1)));
}

stock va_fprintf(File:fhnd, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return fwrite(fhnd, va_return(fmat, ___(2)));
}

stock va_SendRconCommand(const command[], GLOBAL_TAG_TYPES:...)
{
	return SendRconCommand(va_return(command, ___(1)));
}

#if defined YSI_TESTS
	#include "y_va_tests"
#endif

