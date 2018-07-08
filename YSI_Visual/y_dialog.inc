#if defined _INC_y_dialog
	#endinput
#endif
#define _INC_y_dialog

/**
 * <library name="y_dialog">
 * <section>
 *  Description
 * </section>
 *  Provides functions for dealing with dialogs, without needing to worry about
 *  IDs or huge "OnDialogResponse" callbacks.
 * <section>
 *  Version
 * </section>
 *  0.1
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

// y_dialog - does stuff with dialogs.

#include "..\YSI_Internal\y_version"
#include "..\YSI_Data\y_bit"

#include "..\YSI_Coding\y_remote"

#include "..\YSI_Coding\y_inline"
#include "..\YSI_Data\y_iterate"

#include "..\YSI_Coding\y_hooks"

#include "..\YSI_Storage\y_amx"

#define YSIM_U_DISABLE
#define MASTER 54
#include "..\YSI_Core\y_master"

#define YSI_DIALOG_ID _A<_yD@>

static stock
	YSI_g_sPlayerDialog[MAX_PLAYERS] = {-1, ...},
	bool:YSI_g_sPlayerMaster[MAX_PLAYERS] = {false, ...},
	YSI_g_sPlayerCallback[MAX_PLAYERS][E_CALLBACK_DATA];

stock Dialog_Get(playerid)
{
	return YSI_g_sPlayerDialog[playerid];
}

remotefunc void:Dialog_Set(playerid, dialogid)
{
	// If they could already see a dialog shown by this script, get rid of the
	// data from that one.
	YSI_g_sPlayerDialog[playerid] = dialogid;
	if (YSI_g_sPlayerMaster[playerid])
	{
		Callback_Release(YSI_g_sPlayerCallback[playerid]),
		YSI_g_sPlayerMaster[playerid] = false;
	}
}

stock Dialog_ShowCallback(playerid, callback:callback, style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	#pragma unused dialog
	new
		ret = Dialog_Show(playerid, style, title, caption, button1, button2),
		data[E_CALLBACK_DATA];
	if (Callback_Get(callback, data, _F<iiiis>))
		YSI_g_sPlayerCallback[playerid] = data;
	return ret;
}

stock Dialog_ShowCallbackData(playerid, callback[E_CALLBACK_DATA], style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	#pragma unused dialog
	new
		ret = Dialog_Show(playerid, style, title, caption, button1, button2);
	YSI_g_sPlayerCallback[playerid] = callback;
	return ret;
}

stock Dialog_Show(playerid, style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	#pragma unused dialog
	broadcastfunc Dialog_Set(playerid, YSI_DIALOG_ID);
	YSI_g_sPlayerMaster[playerid] = true;
	return ShowPlayerDialog(playerid, YSI_DIALOG_ID, style, title, caption, button1, button2);
}

stock Dialog_Hide(playerid)
{
	// This almost looks like a Windows API function call!
	broadcastfunc Dialog_Set(playerid, -1);
	return ShowPlayerDialog(playerid, -1, 0, NULL, NULL, NULL, NULL);
}

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	// If this is a filterscript that has the currently displayed dialog in it,
	// then we need all scripts to know that this is no longer the case.  If
	// this script is not in charge of the current dialog then do not broadcast
	// the reset, just do it locally.
	if (YSI_g_sPlayerMaster[playerid])
		Dialog_Hide(playerid);
	else
		YSI_g_sPlayerDialog[playerid] = -1;
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	// Apparently there's a hack to alter this.
	dialogid = YSI_g_sPlayerDialog[playerid];
	P:1("Dialog_OnDialogResponse called: %d %d %d %d %s", playerid, dialogid, response, listitem, inputtext);
	if (dialogid == YSI_DIALOG_ID)
	{
		if (YSI_g_sPlayerMaster[playerid])
		{
			static
				reset[E_CALLBACK_DATA];
			new
				callback[E_CALLBACK_DATA];
			callback = YSI_g_sPlayerCallback[playerid];
			// Totally blank the stored dialog information, after making a local
			// copy of it for the sake of calling the callback.  This is so that
			// we don't free the memory for the callback prematurely.
			YSI_g_sPlayerCallback[playerid] = reset;
			broadcastfunc Dialog_Set(playerid, -1);
			// Call the callback.
			Callback_Call(callback, playerid, YSI_DIALOG_ID, response, listitem, inputtext);
			// Free the data.
			Callback_Release(callback);
			return Y_HOOKS_BREAK_RETURN_1;
		}
		return Y_HOOKS_BREAK_RETURN_0;
	}
	else
		return Y_HOOKS_CONTINUE_RETURN_0;
}

stock _ShowPlayerDialog(playerid, dialog, style, string:title[], string:caption[], string:button1[], string:button2[])
{
	// Fail.
	if (dialog == YSI_DIALOG_ID)
		return 0;
	broadcastfunc Dialog_Set(playerid, dialog);
	YSI_g_sPlayerMaster[playerid] = true;
	return ShowPlayerDialog(playerid, dialog, style, title, caption, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog _ShowPlayerDialog

#define _ALS_HidePlayerDialog
#define HidePlayerDialog Dialog_Hide

#include "..\YSI_Core\y_master"

