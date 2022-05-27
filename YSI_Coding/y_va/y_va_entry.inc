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
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
		CreatePlayerTextDraw(playerid, x, y, YSI_UNSAFE_HUGE_STRING);
}

stock Text:va_TextDrawCreate(Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		TextDrawCreate(x, y, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_TextDrawSetString(Text:text, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:TextDrawSetString(text, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_PlayerTextDrawSetString(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:PlayerTextDrawSetString(playerid, text, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SendClientMessage(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:SendClientMessage(playerid, colour, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SendClientMessageToAll(colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:SendClientMessageToAll(colour, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:SendPlayerMessageToPlayer(playerid, senderid, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SendPlayerMessageToAll(senderid, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:SendPlayerMessageToAll(senderid, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_GameTextForPlayer(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
		bool:GameTextForPlayer(playerid, YSI_UNSAFE_HUGE_STRING, time, style);
}

stock bool:va_GameTextForAll(const fmat[], time, style, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:GameTextForAll(YSI_UNSAFE_HUGE_STRING, time, style);
}

native va_print(const fmat[], GLOBAL_TAG_TYPES:...) = printf;

stock va_fprintf(File:fhnd, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		fwrite(fhnd, YSI_UNSAFE_HUGE_STRING);
}

#define va_fwrite va_fprintf

stock bool:va_SendRconCommand(const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(1)),
		bool:SendRconCommand(YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SetGameModeText(const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(1)),
		bool:SetGameModeText(YSI_UNSAFE_HUGE_STRING);
}

// In case the lower-case version is rightfully deprecated.
native DBResult:YSI_DB_Query__(DB:db, const query[]) = db_query;

stock DBResult:va_DBQuery(DB:db, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		YSI_DB_Query__(db, YSI_UNSAFE_HUGE_STRING);
}

#define YSI_DB_Query__

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif
stock bool:va_ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE:style, const title[], const fmat[], const button1[], const button2[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(7)),
		Dialog_ShowPlayerNative(playerid, dialogid, style, title, YSI_UNSAFE_HUGE_STRING, button1, button2);
}

stock Menu:va_CreateMenu(const fmat[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(6)),
		CreateMenu(YSI_UNSAFE_HUGE_STRING, columns, x, y, col1width, col2width);
}

stock va_AddMenuItem(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		AddMenuItem(menuid, column, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SetMenuColumnHeader(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:SetMenuColumnHeader(menuid, column, YSI_UNSAFE_HUGE_STRING);
}

#if !defined OBJECT_MATERIAL_SIZE
	#define OBJECT_MATERIAL_SIZE: _:
#endif
#if !defined OBJECT_MATERIAL_TEXT_ALIGN
	#define OBJECT_MATERIAL_TEXT_ALIGN: _:
#endif
stock bool:va_SetObjectMaterialText(objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0)
{
	// If you get an error here, update your includes!
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(10)),
		bool:SetObjectMaterialText(objectid, YSI_UNSAFE_HUGE_STRING, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
}

stock bool:va_SetPlayerObjectMaterialText(playerid, objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0)
{
	// If you get an error here, update your includes!
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(11)),
		bool:SetPlayerObjectMaterialText(playerid, objectid, YSI_UNSAFE_HUGE_STRING, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
}

stock Text3D:va_Create3DTextLabel(const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, virtualWorld, bool:testLOS = false, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(8)),
		Create3DTextLabel(YSI_UNSAFE_HUGE_STRING, colour, x, y, z, drawDistance, virtualWorld, testLOS);
}

stock bool:va_Update3DTextLabelText(Text3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		Update3DTextLabelText(textid, colour, YSI_UNSAFE_HUGE_STRING);
}

stock PlayerText3D:va_CreatePlayer3DTextLabel(playerid, const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, parentPlayerid = INVALID_PLAYER_ID, parentVehicleid = INVALID_VEHICLE_ID, bool:testLOS = false, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(10)),
		CreatePlayer3DTextLabel(playerid, YSI_UNSAFE_HUGE_STRING, colour, x, y, z, drawDistance, parentPlayerid, parentVehicleid, testLOS);
}

stock bool:va_UpdatePlayer3DTextLabelText(playerid, PlayerText3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
		UpdatePlayer3DTextLabelText(playerid, textid, colour, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SetSVarString(const svar[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	// If you get an error here, update your includes!
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:SetSVarString(svar, YSI_UNSAFE_HUGE_STRING);
}

stock bool:va_SetPVarString(playerid, const svar[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	// If you get an error here, update your includes!
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:SetPVarString(playerid, svar, YSI_UNSAFE_HUGE_STRING);
}

// YSF

stock bool:va_AddServerRule(const name[], const fmat[], E_SERVER_RULE_FLAGS:flags = E_SERVER_RULE_FLAGS:4, GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
		bool:AddServerRule(name, YSI_UNSAFE_HUGE_STRING, flags);
}

stock bool:va_SetServerRule(const name[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:SetServerRule(name, YSI_UNSAFE_HUGE_STRING);
}

native bool:va_TextDrawSetStringForPlayer(Text:text, playerid, const fmat[], GLOBAL_TAG_TYPES:...) = TextDrawSetStringForPlayer;

#if defined YSI_TESTS
	#include "y_va_tests"
#endif

