/*----------------------------------------------------------------------------*\
					=================================
					 y_dialog - Dialogs wrapper.
					=================================
Description:
	Provides functions for dealing with dialogs, without needing to worry about
	IDs or huge "OnDialogResponse" callbacks.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI utils include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.1
Changelog:
	25/02/12:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
\*----------------------------------------------------------------------------*/

// y_dialog - does stuff with dialogs.

#include "internal\y_version"
#include "y_bit"

#include "y_remote"

#include "y_inline"
#include "y_iterate"

#include "y_hooks"

#include "y_amx"

#define YSIM_U_DISABLE
#include "y_master"

#if !defined MAX_DIALOGS
	#define MAX_DIALOGS (2000)
#endif

// This is actually QUITE A LOT of data, I should maybe sort that out.
static stock
	BitArray:YSI_g_sIDs<MAX_DIALOGS> = {Bit:-1, ...},
	BitArray:YSI_g_sFree<MAX_DIALOGS>,
	YSI_g_sPlayerDialog[MAX_PLAYERS] = {-1, ...},
	YSI_g_sDialogPlayers[MAX_DIALOGS],
	YSI_g_sDialogMasters[MAX_DIALOGS] = {-1, ...},
	YSI_g_sDialogInfo[MAX_DIALOGS][E_CALLBACK_DATA];

/*stock Dialog_ObtainID()
{
	new
		data = Dialog_DoObtainID();
	YSI_g_sDialogInfo[data][E_CALLBACK_DATA_POINTER] = 0;
	return data;
}*/

foreign Dialog_ObtainID();

global Dialog_ObtainID()
{
	static const
		scDeBruijn[] =
			{
				0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8, 
				31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
			};
	for (new i = 0; i != sizeof (YSI_g_sIDs); ++i)
	{
		if (YSI_g_sIDs[i])
		{
			new
				Bit:b = (YSI_g_sIDs[i] & -YSI_g_sIDs[i]),
				data = scDeBruijn[(_:b * 0x077CB531) >>> 27];
			YSI_g_sIDs[i] &= ~b;
			data += (i * 32);
			YSI_g_sDialogPlayers[data] = 0;
			YSI_g_sDialogMasters[data] = -1;
			//YSI_g_sDialogInfo[data][E_CALLBACK_DATA_POINTER] = 0;
			return data;
		}
	}
	return -1;
	// http://supertech.csail.mit.edu/papers/debruijn.pdf
}

foreign Dialog_TryObtainID(id);

global Dialog_TryObtainID(id)
{
	if (Bit_Get(YSI_g_sIDs, id))
	{
		Bit_Vet(YSI_g_sIDs, id);
		YSI_g_sDialogPlayers[id] = 0;
		YSI_g_sDialogMasters[id] = -1;
		//YSI_g_sDialogInfo[data][E_CALLBACK_DATA_POINTER] = 0;
		return id;
	}
	P:C(else P:E("Dialog ID %d already in use", id););
	return -1;
}

foreign Dialog_Get(playerid);

global Dialog_Get(playerid)
{
	return YSI_g_sPlayerDialog[playerid];
}

foreign Dialog_Garbage(dialogid);

global Dialog_Garbage(dialogid)
{
	Bit_Let(YSI_g_sFree, dialogid);
	return 1;
}

foreign Dialog_Free(dialogid);

global Dialog_Free(dialogid)
{
	Bit_Vet(YSI_g_sFree, dialogid);
	Bit_Let(YSI_g_sIDs, dialogid);
	if (YSI_g_sDialogPlayers[dialogid])
	{
		YSI_g_sDialogPlayers[dialogid] = 0;
		foreach (new i : Player)
		{
			if (YSI_g_sPlayerDialog[i] == dialogid)
			{
				ShowPlayerDialog(i, -1, 0, NULL, NULL, NULL, NULL);
				YSI_g_sPlayerDialog[i] = -1;
			}
		}
	}
	return 1;
}

foreign Dialog_Set(playerid, dialogid);

global Dialog_Set(playerid, dialogid)
{
	new
		old = YSI_g_sPlayerDialog[playerid];
	if (dialogid != old)
	{
		if (dialogid != -1)
		{
			++YSI_g_sDialogPlayers[dialogid];
		}
		YSI_g_sPlayerDialog[playerid] = dialogid;
		if (old != -1)
		{
			if (--YSI_g_sDialogPlayers[old] == 0)
			{
				if (Bit_Get(YSI_g_sFree, old))
				{
					YSI_g_sDialogMasters[old] = -1;
					Bit_Vet(YSI_g_sFree, old);
					Bit_Let(YSI_g_sIDs, old);
					// "old" destroyed.
					return 0;
				}
			}
		}
	}
	// "old" still exists.
	return 1;
}

stock Dialog_ShowCallback(playerid, callback:callback, style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	new
		ret = Dialog_Show(playerid, style, title, caption, button1, button2, dialog),
		data[E_CALLBACK_DATA];
	if (Callback_Get(callback, data, _F<iiiis>))
	{
		Dialog_SetCallbackData(ret, data);
	}
	return ret;
}

stock Dialog_ShowCallbackData(playerid, callback[E_CALLBACK_DATA], style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	new
		ret = Dialog_Show(playerid, style, title, caption, button1, button2, dialog);
	Dialog_SetCallbackData(ret, callback);
	return ret;
}

stock Dialog_Show(playerid, style, string:title[], string:caption[], string:button1[], string:button2[] = "", dialog = -1)
{
	if (dialog == -1)
	{
		dialog = Dialog_ObtainID();
		Dialog_Garbage(dialog);
	}
	ShowPlayerDialog(playerid, dialog, style, title, caption, button1, button2);
	Dialog_Set(playerid, dialog);
	return dialog;
}

stock Dialog_Hide(playerid)
{
	// This almost looks like a Windows API function call!
	ShowPlayerDialog(playerid, -1, 0, NULL, NULL, NULL, NULL);
	return Dialog_Set(playerid, -1);
}

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	Dialog_Hide(playerid);
	return 1;
}

/*#define Dialog_SetCallback(%0) _Dialog_SetCallback(%0,Master_Caller())

foreign @Dialog_SetCallback(dialogid, a, b, c, d);

global @Dialog_SetCallback(dialogid, a, b, c, d)
{
	YSI_g_sDialogInfo[dialogid] = callback;
}

stock _Dialog_SetCallback(dialogid, callback[E_CALLBACK_DATA], master)
{
	@Dialog_SetCallback(dialogid
}*/

remotefunc Dialog_SetMaster(dialogid, master)
{
	//printf("SETTING %d MASTER: %d", dialogid, master);
	YSI_g_sDialogMasters[dialogid] = master;
	//YSI_g_sDialogInfo[dialogid][E_CALLBACK_DATA_POINTER] = 0;
}

stock Dialog_GetMaster(dialogid)
{
	return YSI_g_sDialogMasters[dialogid];
}

stock Dialog_SetCallback(dialogid, callback:callback)
{
	new
		data[E_CALLBACK_DATA];
	if (Callback_Get(callback, data, _F<iiiis>))
	{
		Dialog_SetCallbackData(dialogid, data);
	}
	P:C(else P:E("Could not find dialog callback %s", _:callback););
}

stock Dialog_SetCallbackData(dialogid, callback[E_CALLBACK_DATA])
{
	broadcastfunc Dialog_SetMaster(dialogid, _@);
	YSI_g_sDialogInfo[dialogid] = callback;
}

// Need to somehow integrate this new dialogs library with the text library.

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	P:1("Dialog_OnDialogResponse called: %d %d %d %d %s", playerid, dialogid, response, listitem, inputtext);
	// Apparently there's a hack to alter this.
	dialogid = Dialog_Get(playerid);
	P:5("Dialog_OnDialogResponse: dialog = %d", dialogid);
	if (dialogid == -1)
	{
		return 0;
	}
	P:5("Dialog_OnDialogResponse: master = %d, %d", YSI_g_sDialogMasters[dialogid], _@);
	if (YSI_g_sDialogMasters[dialogid] != _@)
	{
		return 0;
	}
	// Dialogs close automaticaly.
	Dialog_Set(playerid, -1);
	if (Bit_Get(YSI_g_sIDs, dialogid))
	{
		// Or it will screw up when you show a new dialog from a dialog.
		P:5("OnDialogResponse: Already freed");
		new
			dat[E_CALLBACK_DATA];
		dat = YSI_g_sDialogInfo[dialogid];
		// Callback no longer needed.
		if (dat[E_CALLBACK_DATA_POINTER])
		{
			Callback_Call(dat, playerid, dialogid, response, listitem, inputtext);
			Callback_Release(dat);
			return 1;
		}
	}
	else
	{
		P:5("OnDialogResponse: Not free");
		if (YSI_g_sDialogInfo[dialogid][E_CALLBACK_DATA_POINTER])
		{
			Callback_Call(YSI_g_sDialogInfo[dialogid], playerid, dialogid, response, listitem, inputtext);
			return 1;
		}
	}
	//Dialog_Set(playerid, -1);
	return 0;
}

/*stock _ShowPlayerDialog(playerid, dialog, style, string:title[], string:caption[], string:button1[], string:button2[])
{
	Dialog_TryObtainID(dialog);
	YSI_g_sDialogInfo[dialog][E_CALLBACK_DATA_POINTER] = 0;
	ShowPlayerDialog(playerid, dialog, style, title, caption, button1, button2);
	return 0;
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog _ShowPlayerDialog

#define HidePlayerDialog Dialog_Hide*/

/*stock HidePlayerDialog(playerid)
{
	ShowPlayerDialog(playerid, -1, 0, NULL, NULL, NULL, NULL);
}*/

//#define YSI_SET_LAST_GROUP 19
#include "internal\y_grouprevert"
