#if defined _INC_y_text
	#endinput
#endif
#define _INC_y_text
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

#if defined YSI_TESTS
	// Fake `IsPlayerConnected`.
	#define _YSI_SPECIAL_DEBUG
#endif

#include "..\..\YSI_Core\y_utils"

// Make sure this is included early.
#include "..\..\YSI_Data\y_playerset"

// Apparently I'd already written the internal code to support this and forgot!
#define Y_TEXT_UNIQUE

#if !defined Y_TEXT_MAX_SETS
	#define Y_TEXT_MAX_SETS             (16)
#endif

#if !defined Y_TEXT_PER_SET
	#define Y_TEXT_PER_SET              (64)
#endif

#if !defined MAX_TEXT_ENTRIES
	#define MAX_TEXT_ENTRIES (Y_TEXT_PER_SET * Y_TEXT_MAX_SETS)
#endif

#if defined YSI_TESTS
	#define MAX_Y_TEXT_TEST_LINES (10)
	#define MAX_Y_TEXT_TEST_LENGTH (1024)

	// These mocks DO NOT use ALS or stock, so that we get compile-time warnings
	// about anything that may interfere.  Tests shouldn't really be run on a
	// full mode with all other things (unless you are doing integration tests),
	// so the warnings are appropriate.
	new
		YSI_gTextTestPlayer[MAX_Y_TEXT_TEST_LINES],
		YSI_gTextTestStyle[MAX_Y_TEXT_TEST_LINES],
		YSI_gTextTestTime[MAX_Y_TEXT_TEST_LINES],
		YSI_gTextTestOutput[MAX_Y_TEXT_TEST_LINES][MAX_Y_TEXT_TEST_LENGTH],
		YSI_gTextTest;

	// Hook SA:MP natives, so that calls to print functions are routed to us
	// instead.  "TxT" = "TextTest".
	TxT_SendClientMessage(playerid, color, const message[])
	{
		YSI_gTextTestPlayer[YSI_gTextTest] = playerid,
		YSI_gTextTestStyle[YSI_gTextTest] = color,
		StrCpy(YSI_gTextTestOutput[YSI_gTextTest], message),
		++YSI_gTextTest;
	}
	#define SendClientMessage TxT_SendClientMessage

	TxT_SendPlayerMessageToPlayer(playerid, senderid, const message[])
	{
		YSI_gTextTestPlayer[YSI_gTextTest] = playerid,
		YSI_gTextTestStyle[YSI_gTextTest] = senderid,
		StrCpy(YSI_gTextTestOutput[YSI_gTextTest], message),
		++YSI_gTextTest;
	}
	#define SendPlayerMessageToPlayer TxT_SendPlayerMessageToPlayer

	TxT_GameTextForPlayer(playerid, const string[], time, style)
	{
		YSI_gTextTestPlayer[YSI_gTextTest] = playerid,
		YSI_gTextTestStyle[YSI_gTextTest] = style,
		YSI_gTextTestTime[YSI_gTextTest] = time,
		StrCpy(YSI_gTextTestOutput[YSI_gTextTest], string),
		++YSI_gTextTest;
	}
	#define GameTextForPlayer TxT_GameTextForPlayer

	TextTest_Reset()
	{
		for (new i = 0; i != MAX_Y_TEXT_TEST_LINES; ++i)
		{
			YSI_gTextTestPlayer[i] = cellmin,
			YSI_gTextTestStyle[i] = cellmin,
			YSI_gTextTestTime[i] = cellmin,
			YSI_gTextTestOutput[i][0] = '\0';
		}
		YSI_gTextTest = 0;
	}

	// TODO: TextDraw hooks.
#endif

#include "..\..\YSI_Storage\y_xml"
#include "..\..\YSI_Server\y_td"
#include "..\..\YSI_Server\y_colours"

#include "y_text_styles"

// This is a horribly eclectic collection of libraries from all over the place
// and written at different times with different aims - frankly I'll be AMAZED
// if it all comes together and works.
// 
// 2017: I'm still amazed it works!
// 
// 2018: Collating core includes, hopefully will still work.

#if !defined MAX_PLAYER_NAME
	#define MAX_PLAYER_NAME 24
#elseif MAX_PLAYER_NAME != (24)
	#error Unknown MAX_PLAYER_NAME size.
#else
	// Strip the brackets off.
	#undef MAX_PLAYER_NAME
	#define MAX_PLAYER_NAME 24
#endif

//#include <a_samp>
#include "..\..\YSI_Server\y_colours"
#include "..\..\YSI_Data\y_hashmap"
#include "..\..\YSI_Data\y_jaggedarray"

#include "y_text_load"

#include "..\..\YSI_Coding\y_va"

#include "y_text_render"

#include "..\..\YSI_Storage\y_ini"
#include "..\..\YSI_Data\y_iterate"
#include "..\..\YSI_Players\y_languages"
#include "..\..\YSI_Visual\y_dialog"
#include "..\..\YSI_Coding\y_inline"
#include "..\..\YSI_Coding\y_hooks"

#include "y_text_impl"

#define UNDO_MOVE|||
#define DO_MOVE|||%0``` %0DO_MOVE|||

#define Text_Send(%0,%1) PSF:_Text_Send(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)
#define Text_Render(%0,%1) _Text_Render(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)
#define Text_Format(%0,%1,%2,%3,%4) _Text_Format(%0,%1,%2,%3,DO_TEXT_SET:%4 UNDO_MOVE|||)

#define Text_Format_GT_0(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_0,%3)
#define Text_Format_GT_1(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_1,%3)
#define Text_Format_GT_2(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_2,%3)
#define Text_Format_GT_3(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_3,%3)
#define Text_Format_GT_4(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_4,%3)
#define Text_Format_GT_5(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_5,%3)
#define Text_Format_GT_6(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_6,%3)
#define Text_Format_TD(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_TD,%3)
#define Text_Format_3D(%0,%1,%2,%3 Text_Format(%0,%1,%2, e_STYLE_TYPE_3D,%3)
#define Text_Format_Client(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_CLIENT,%3)
#define Text_Format_Player(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_PLAYER,%3)
#define Text_Format_Other(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_OTHER,%3)
#define Text_Format_Dialog(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_DIALOG,%3)

//#define _Text_Send(%0YCMD:%1) _Text_Send(%0_:YCMD_REP_0:YCMD_REP_1:%1)

//#define YCMD_REP_0:YCMD_REP_1:%0, Command_GetID(%0),
//#define YCMD_REP_1:%0) Command_GetID(%0))

// This code allows "DEFAULT_TEXT_SET" to propogate through the text one section
// at a time without detecting later matches too early.  The design of "DO_MOVE"
// and "UNDO_MOVE" means that the compiler will correctly detect the end of the
// code, regardless of the length, and end.
#define Text_MessageBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_MSGBOX,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_InputBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_INPUT,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_ListBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_LIST,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_PasswordBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_PASSWORD,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_DialogBox(%0,%9,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,%9,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
//#define Text_MessageBox(%0,%1,%2,%3) PSF:_Text_MessageBox(%0,%1,DEFAULT_TEXT_SET,#%2 DO_MOVE|||,DEFAULT_TEXT_SET,#%3 $$$,DEFAULT_TEXT_SET,#%4 $$$,DEFAULT_TEXT_SET,#%5 UN$$$)

//#define _Text_MessageBox(%0YCMD:%1) _Text_MessageBox(%0_:YCMD_REP_0:YCMD_REP_1:%1)

//stock Text_GetAllIDs(
static stock
	YSI_g_sFormat[1024],
	YSI_g_sTemp[1024];

stock Text_FormatEx(output[], len, const format[], GLOBAL_TAG_TYPES:...)
{
	// "Format_Standardise" modifies "input" repeatedly.
	StrCpy(YSI_g_sFormat, format);
	Format_Standardise(YSI_g_sFormat, YSI_g_sTemp);
	Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, output, len - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTemp, ___(3));
}

stock Text_PrintFEx(const format[], GLOBAL_TAG_TYPES:...)
{
	// "Format_Standardise" modifies "input" repeatedly.
	StrCpy(YSI_g_sFormat, format);
	Format_Standardise(YSI_g_sFormat, YSI_g_sTemp);
	Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, YSI_g_sFormat, sizeof (YSI_g_sFormat) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTemp, ___(1));
	print(sFormat);
}

#if defined YSI_TESTS
	#include "y_text_tests"
#endif

#if !defined formatex
	#define formatex Text_FormatEx
#endif
#if !defined printfex
	#define printfex Text_PrintFEx
#endif


