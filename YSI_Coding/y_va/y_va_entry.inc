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
#include "..\..\YSI_Server\y_thirdpartyinclude"

#if !defined YSI_MAX_INLINE_STRING
	#define YSI_MAX_INLINE_STRING YSI_MAX_STRING
#endif

#include "y_va_header"
#include "y_va_impl"

#if __COMPILER___EMIT_U
	#define YSI_CheckNumargs__(%0) (__emit(LOAD.S.pri __args_offset) == ((%0) * cellbytes))
#else
	#define YSI_CheckNumargs__(%0) (numargs() == (%0))
#endif

native va_print(const fmat[], GLOBAL_TAG_TYPES:...) = printf;

stock va_fprintf(File:fhnd, const fmat[], GLOBAL_TAG_TYPES:...)
{
	if (YSI_CheckNumargs__(2))
		return fwrite(fhnd, fmat);
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		fwrite(fhnd, YSI_UNSAFE_HUGE_STRING);
}
#define va_fwrite va_fprintf

stock bool:va_SetVehicleNumberPlate(vehicleid, const fmat[], GLOBAL_TAG_TYPES:...)
{
	// No open.mp version yet (probably because I forgot it in y_va, so
	// subsequently didn't see it when doing the open.mp natives).
	if (YSI_CheckNumargs__(2))
		return bool:SetVehicleNumberPlate(vehicleid, fmat);
	return
		format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
		bool:SetVehicleNumberPlate(vehicleid, YSI_UNSAFE_HUGE_STRING);
}

#if defined _INC_open_mp
	native PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...) = CreatePlayerTextDraw;
	native va_SetPlayerChatBubble(playerid, const fmat[], colour, Float:drawDistance, expireTime, GLOBAL_TAG_TYPES:...) = SetPlayerChatBubble;
	native Text:va_TextDrawCreate(Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...) = TextDrawCreate;
	native bool:va_TextDrawSetString(Text:text, const fmat[], GLOBAL_TAG_TYPES:...) = TextDrawSetString;
	native bool:va_PlayerTextDrawSetString(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...) = PlayerTextDrawSetString;
	native bool:va_SendClientMessage(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...) = SendClientMessage;
	native bool:va_SendClientMessageToAll(colour, const fmat[], GLOBAL_TAG_TYPES:...) = SendClientMessageToAll;
	native bool:va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], GLOBAL_TAG_TYPES:...) = SendPlayerMessageToPlayer;
	native bool:va_SendPlayerMessageToAll(senderid, const fmat[], GLOBAL_TAG_TYPES:...) = SendPlayerMessageToAll;
	native bool:va_GameTextForPlayer(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...) = GameTextForPlayer;
	native bool:va_GameTextForAll(const fmat[], time, style, GLOBAL_TAG_TYPES:...) = GameTextForAll;
	native bool:va_SendRconCommand(const fmat[], GLOBAL_TAG_TYPES:...) = SendRconCommand;
	native bool:va_SetGameModeText(const fmat[], GLOBAL_TAG_TYPES:...) = SetGameModeText;
	native DBResult:va_DBQuery(DB:db, const fmat[], GLOBAL_TAG_TYPES:...) = DB_ExecuteQuery;
	native bool:va_ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE:style, const title[], const fmat[], const button1[], const button2[], GLOBAL_TAG_TYPES:...) = ShowPlayerDialog;
	native Menu:va_CreateMenu(const fmat[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0, GLOBAL_TAG_TYPES:...) = CreateMenu;
	native va_AddMenuItem(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...) = AddMenuItem;
	native bool:va_SetMenuColumnHeader(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...) = SetMenuColumnHeader;
	native bool:va_SetObjectMaterialText(objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...) = SetObjectMaterialText;
	native bool:va_SetPlayerObjectMaterialText(playerid, objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...) = SetPlayerObjectMaterialText;
	native Text3D:va_Create3DTextLabel(const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, virtualWorld, bool:testLOS = false, GLOBAL_TAG_TYPES:...) = Create3DTextLabel;
	native bool:va_Update3DTextLabelText(Text3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...) = Update3DTextLabelText;
	native PlayerText3D:va_CreatePlayer3DTextLabel(playerid, const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, parentPlayerid = INVALID_PLAYER_ID, parentVehicleid = INVALID_VEHICLE_ID, bool:testLOS = false, GLOBAL_TAG_TYPES:...) = CreatePlayer3DTextLabel;
	native bool:va_UpdatePlayer3DTextLabelText(playerid, PlayerText3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...) = UpdatePlayer3DTextLabelText;
	native bool:va_SetSVarString(const svar[], const fmat[], GLOBAL_TAG_TYPES:...) = SetSVarString;
	native bool:va_SetPVarString(playerid, const svar[], const fmat[], GLOBAL_TAG_TYPES:...) = SetPVarString;
	native bool:va_SetServerRule(const name[], const fmat[], GLOBAL_TAG_TYPES:...) = SetServerRule;
	native bool:va_TextDrawSetStringForPlayer(Text:text, playerid, const fmat[], GLOBAL_TAG_TYPES:...) = TextDrawSetStringForPlayer;

	stock bool:va_AddServerRule(const name[], const fmat[], E_SERVER_RULE_FLAGS:flags = E_SERVER_RULE_FLAGS:4, GLOBAL_TAG_TYPES:...)
	{
		// This gives a warning on purpose - `flags` is not used by open.mp.
		if (YSI_CheckNumargs__(3))
			return bool:AddServerRule(name, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:AddServerRule(name, YSI_UNSAFE_HUGE_STRING);
	}

	#if defined YSI_TESTS
		#include "y_va_tests"
	#endif
#else
	stock PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(4))
			return CreatePlayerTextDraw(playerid, x, y, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
			CreatePlayerTextDraw(playerid, x, y, YSI_UNSAFE_HUGE_STRING);
	}

	stock va_SetPlayerChatBubble(playerid, const fmat[], colour, Float:drawDistance, expireTime, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(5))
			return SetPlayerChatBubble(playerid, fmat, colour, drawDistance, expireTime);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(5)),
			SetPlayerChatBubble(playerid, YSI_UNSAFE_HUGE_STRING, colour, drawDistance, expireTime);
	}

	stock Text:va_TextDrawCreate(Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return TextDrawCreate(x, y, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			TextDrawCreate(x, y, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_TextDrawSetString(Text:text, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(2))
			return bool:TextDrawSetString(text, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
			bool:TextDrawSetString(text, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_PlayerTextDrawSetString(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:PlayerTextDrawSetString(playerid, text, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:PlayerTextDrawSetString(playerid, text, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SendClientMessage(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:SendClientMessage(playerid, colour, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:SendClientMessage(playerid, colour, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SendClientMessageToAll(colour, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(2))
			return bool:SendClientMessageToAll(colour, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
			bool:SendClientMessageToAll(colour, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:SendPlayerMessageToPlayer(playerid, senderid, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:SendPlayerMessageToPlayer(playerid, senderid, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SendPlayerMessageToAll(senderid, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(2))
			return bool:SendPlayerMessageToAll(senderid, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
			bool:SendPlayerMessageToAll(senderid, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_GameTextForPlayer(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(4))
			return bool:GameTextForPlayer(playerid, fmat, time, style);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
			bool:GameTextForPlayer(playerid, YSI_UNSAFE_HUGE_STRING, time, style);
	}

	stock bool:va_GameTextForAll(const fmat[], time, style, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:GameTextForAll(fmat, time, style);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:GameTextForAll(YSI_UNSAFE_HUGE_STRING, time, style);
	}

	stock bool:va_SendRconCommand(const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(1))
			return bool:SendRconCommand(fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(1)),
			bool:SendRconCommand(YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SetGameModeText(const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(1))
			return bool:SetGameModeText(fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(1)),
			bool:SetGameModeText(YSI_UNSAFE_HUGE_STRING);
	}

	// In case the lower-case version is rightfully deprecated.
	native DBResult:YSI_DB_Query__(DB:db, const query[]) = db_query;

	stock DBResult:va_DBQuery(DB:db, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(2))
			return YSI_DB_Query__(db, fmat);
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
		if (YSI_CheckNumargs__(7))
			return bool:Dialog_ShowPlayerNative(playerid, dialogid, style, title, fmat, button1, button2);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(7)),
			bool:Dialog_ShowPlayerNative(playerid, dialogid, style, title, YSI_UNSAFE_HUGE_STRING, button1, button2);
	}

	stock Menu:va_CreateMenu(const fmat[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(6))
			return CreateMenu(fmat, columns, x, y, col1width, col2width);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(6)),
			CreateMenu(YSI_UNSAFE_HUGE_STRING, columns, x, y, col1width, col2width);
	}

	stock va_AddMenuItem(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return AddMenuItem(menuid, column, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			AddMenuItem(menuid, column, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SetMenuColumnHeader(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:SetMenuColumnHeader(menuid, column, fmat);
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
	stock bool:va_SetObjectMaterialText(objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...)
	{
		// If you get an error here, update your includes!
		if (YSI_CheckNumargs__(10))
			return bool:SetObjectMaterialText(objectid, fmat, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(10)),
			bool:SetObjectMaterialText(objectid, YSI_UNSAFE_HUGE_STRING, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
	}

	stock bool:va_SetPlayerObjectMaterialText(playerid, objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...)
	{
		// If you get an error here, update your includes!
		if (YSI_CheckNumargs__(11))
			return bool:SetPlayerObjectMaterialText(playerid, objectid, fmat, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(11)),
			bool:SetPlayerObjectMaterialText(playerid, objectid, YSI_UNSAFE_HUGE_STRING, materialIndex, materialSize, fontFace, fontSize, bold, fontColour, backgroundColour, textalignment);
	}

	stock Text3D:va_Create3DTextLabel(const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, virtualWorld, bool:testLOS = false, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(8))
			return Create3DTextLabel(fmat, colour, x, y, z, drawDistance, virtualWorld, testLOS);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(8)),
			Create3DTextLabel(YSI_UNSAFE_HUGE_STRING, colour, x, y, z, drawDistance, virtualWorld, testLOS);
	}

	stock bool:va_Update3DTextLabelText(Text3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:Update3DTextLabelText(textid, colour, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:Update3DTextLabelText(textid, colour, YSI_UNSAFE_HUGE_STRING);
	}

	stock PlayerText3D:va_CreatePlayer3DTextLabel(playerid, const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, parentPlayerid = INVALID_PLAYER_ID, parentVehicleid = INVALID_VEHICLE_ID, bool:testLOS = false, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(10))
			return CreatePlayer3DTextLabel(playerid, fmat, colour, x, y, z, drawDistance, parentPlayerid, parentVehicleid, testLOS);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(10)),
			CreatePlayer3DTextLabel(playerid, YSI_UNSAFE_HUGE_STRING, colour, x, y, z, drawDistance, parentPlayerid, parentVehicleid, testLOS);
	}

	stock bool:va_UpdatePlayer3DTextLabelText(playerid, PlayerText3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(4))
			return bool:UpdatePlayer3DTextLabelText(playerid, textid, colour, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(4)),
			bool:UpdatePlayer3DTextLabelText(playerid, textid, colour, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SetSVarString(const svar[], const fmat[], GLOBAL_TAG_TYPES:...)
	{
		// If you get an error here, update your includes!
		if (YSI_CheckNumargs__(2))
			return bool:SetSVarString(svar, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
			bool:SetSVarString(svar, YSI_UNSAFE_HUGE_STRING);
	}

	stock bool:va_SetPVarString(playerid, const svar[], const fmat[], GLOBAL_TAG_TYPES:...)
	{
		// If you get an error here, update your includes!
		if (YSI_CheckNumargs__(3))
			return bool:SetPVarString(playerid, svar, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:SetPVarString(playerid, svar, YSI_UNSAFE_HUGE_STRING);
	}

	// YSF

	stock bool:va_AddServerRule(const name[], const fmat[], E_SERVER_RULE_FLAGS:flags = E_SERVER_RULE_FLAGS:4, GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(3))
			return bool:AddServerRule(name, fmat, flags);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(3)),
			bool:AddServerRule(name, YSI_UNSAFE_HUGE_STRING, flags);
	}

	stock bool:va_SetServerRule(const name[], const fmat[], GLOBAL_TAG_TYPES:...)
	{
		if (YSI_CheckNumargs__(2))
			return bool:SetServerRule(name, fmat);
		return
			format(YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, fmat, ___(2)),
			bool:SetServerRule(name, YSI_UNSAFE_HUGE_STRING);
	}

	native bool:va_TextDrawSetStringForPlayer(Text:text, playerid, const fmat[], GLOBAL_TAG_TYPES:...) = TextDrawSetStringForPlayer;

	#if defined YSI_TESTS
		#include "y_va_tests"
	#endif

	#if defined YSI_NO_AUTO_VA
		#endinput
	#endif

	// ALS defines for all the functions above.
	#if defined _ALS_CreatePlayerTextDraw
		#undef CreatePlayerTextDraw
	#endif
	#define _ALS_CreatePlayerTextDraw
	#define CreatePlayerTextDraw( va_CreatePlayerTextDraw(

	#if defined _ALS_SetPlayerChatBubble
		#undef SetPlayerChatBubble
	#endif
	#define _ALS_SetPlayerChatBubble
	#define SetPlayerChatBubble( va_SetPlayerChatBubble(

	#if defined _ALS_TextDrawCreate
		#undef TextDrawCreate
	#endif
	#define _ALS_TextDrawCreate
	#define TextDrawCreate( va_TextDrawCreate(

	#if defined _ALS_TextDrawSetString
		#undef TextDrawSetString
	#endif
	#define _ALS_TextDrawSetString
	#define TextDrawSetString( va_TextDrawSetString(

	#if defined _ALS_PlayerTextDrawSetString
		#undef PlayerTextDrawSetString
	#endif
	#define _ALS_PlayerTextDrawSetString
	#define PlayerTextDrawSetString( va_PlayerTextDrawSetString(

	#if defined _ALS_SendClientMessage
		#undef SendClientMessage
	#endif
	#define _ALS_SendClientMessage
	#define SendClientMessage( va_SendClientMessage(

	#if defined _ALS_SendClientMessageToAll
		#undef SendClientMessageToAll
	#endif
	#define _ALS_SendClientMessageToAll
	#define SendClientMessageToAll( va_SendClientMessageToAll(

	#if defined _ALS_SendPlayerMessageToPlayer
		#undef SendPlayerMessageToPlayer
	#endif
	#define _ALS_SendPlayerMessageToPlayer
	#define SendPlayerMessageToPlayer( va_SendPlayerMessageToPlayer(

	#if defined _ALS_SendPlayerMessageToAll
		#undef SendPlayerMessageToAll
	#endif
	#define _ALS_SendPlayerMessageToAll
	#define SendPlayerMessageToAll( va_SendPlayerMessageToAll(

	#if defined _ALS_GameTextForPlayer
		#undef GameTextForPlayer
	#endif
	#define _ALS_GameTextForPlayer
	#define GameTextForPlayer( va_GameTextForPlayer(

	#if defined _ALS_GameTextForAll
		#undef GameTextForAll
	#endif
	#define _ALS_GameTextForAll
	#define GameTextForAll( va_GameTextForAll(

	#if defined _ALS_fwrite
		#undef fwrite
	#endif
	#define _ALS_fwrite
	#define fwrite( va_fprintf(

	#if defined _ALS_SendRconCommand
		#undef SendRconCommand
	#endif
	#define _ALS_SendRconCommand
	#define SendRconCommand( va_SendRconCommand(

	#if defined _ALS_SetGameModeText
		#undef SetGameModeText
	#endif
	#define _ALS_SetGameModeText
	#define SetGameModeText( va_SetGameModeText(

	#if defined _ALS_DBQuery
		#undef DBQuery
	#endif
	#define _ALS_DBQuery
	#define DBQuery( va_DBQuery(

	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#endif
	#define _ALS_ShowPlayerDialog
	#define ShowPlayerDialog( va_ShowPlayerDialog(

	#if defined _ALS_CreateMenu
		#undef CreateMenu
	#endif
	#define _ALS_CreateMenu
	#define CreateMenu( va_CreateMenu(

	#if defined _ALS_AddMenuItem
		#undef AddMenuItem
	#endif
	#define _ALS_AddMenuItem
	#define AddMenuItem( va_AddMenuItem(

	#if defined _ALS_SetMenuColumnHeader
		#undef SetMenuColumnHeader
	#endif
	#define _ALS_SetMenuColumnHeader
	#define SetMenuColumnHeader( va_SetMenuColumnHeader(

	#if defined _ALS_SetObjectMaterialText
		#undef SetObjectMaterialText
	#endif
	#define _ALS_SetObjectMaterialText
	#define SetObjectMaterialText( va_SetObjectMaterialText(

	#if defined _ALS_SetPlayerObjMaterialText
		#undef SetPlayerObjectMaterialText
	#endif
	#define _ALS_SetPlayerObjMaterialText
	#define SetPlayerObjectMaterialText( va_SetPlayerObjectMaterialText(

	#if defined _ALS_Create3DTextLabel
		#undef Create3DTextLabel
	#endif
	#define _ALS_Create3DTextLabel
	#define Create3DTextLabel( va_Create3DTextLabel(

	#if defined _ALS_Update3DTextLabelText
		#undef Update3DTextLabelText
	#endif
	#define _ALS_Update3DTextLabelText
	#define Update3DTextLabelText( va_Update3DTextLabelText(

	#if defined _ALS_CreatePlayer3DTextLabel
		#undef CreatePlayer3DTextLabel
	#endif
	#define _ALS_CreatePlayer3DTextLabel
	#define CreatePlayer3DTextLabel( va_CreatePlayer3DTextLabel(

	#if defined _ALS_UpdPlayer3DTextLabelText
		#undef UpdatePlayer3DTextLabelText
	#endif
	#define _ALS_UpdPlayer3DTextLabelText
	#define UpdatePlayer3DTextLabelText( va_UpdatePlayer3DTextLabelText(

	#if defined _ALS_SetSVarString
		#undef SetSVarString
	#endif
	#define _ALS_SetSVarString
	#define SetSVarString( va_SetSVarString(

	#if defined _ALS_SetPVarString
		#undef SetPVarString
	#endif
	#define _ALS_SetPVarString
	#define SetPVarString( va_SetPVarString(

	#if defined _ALS_AddServerRule
		#undef AddServerRule
	#endif
	#define _ALS_AddServerRule
	#define AddServerRule( va_AddServerRule(

	#if defined _ALS_SetServerRule
		#undef SetServerRule
	#endif
	#define _ALS_SetServerRule
	#define SetServerRule( va_SetServerRule(

	#if defined _ALS_TextDrawSetStringForPlayer
		#undef TextDrawSetStringForPlayer
	#endif
	#define _ALS_TextDrawSetStringForPlayer
	#define TextDrawSetStringForPlayer( va_TextDrawSetStringForPlayer(
#endif

#if defined _ALS_SetVehicleNumberPlate
	#undef SetVehicleNumberPlate
#endif
#define _ALS_SetVehicleNumberPlate
#define SetVehicleNumberPlate( va_SetVehicleNumberPlate(

