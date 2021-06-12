#if defined _INC_y_inline_mselection
	#endinput
#endif
#define _INC_y_inline_mselection

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

#if !defined _INC_y_inline
	#tryinclude "..\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI\YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#error Could not find y_inline
#endif

// Using this to prevent any problem due to PAWN Limitations
DEFINE_HOOK_REPLACEMENT__(ModelSelection, ModSel);

static stock
	Func:YSI_g_sRequestModelSelection[MAX_PLAYERS]<iii>,
	YSI_g_PlayerCurrentListID[MAX_PLAYERS] = {mS_INVALID_LISTID, ...};

// Func:callback<iii> | Func:callback<ii>
stock ShowModelSelectionInline({F@_@iii, F@_@ii}:callback, playerid, listid, const string:headerText[], dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback)) 
{
	new ret = ShowModelSelectionMenu(playerid, listid, headerText, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret) 
	{
		Indirect_Claim(callback);
		Indirect_SetMeta(callback, tag);

		YSI_g_PlayerCurrentListID[playerid] = listid;
		YSI_g_sRequestModelSelection[playerid] = callback;
	}
	return ret;
}

// Func:callback<iii> | Func:callback<ii>
stock ShowModelSelectionInlineEx({F@_@iii, F@_@ii}:callback, playerid, const itemsArray[], itemAmount, const string:headerText[], Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback)) 
{
	new ret = ShowModelSelectionMenuEx(playerid, itemsArray, itemAmount, headerText, -1, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret) 
	{
		Indirect_Claim(callback);
		Indirect_SetMeta(callback, tag);

		YSI_g_sRequestModelSelection[playerid] = callback;
	}
	return ret;
}

HOOK__ OnPlayerModSel(playerid, response, listid, modelid) 
{
	new 
		Func:cb<iii> = YSI_g_sRequestModelSelection[playerid];

	YSI_g_sRequestModelSelection[playerid] = Func:0<iii>;
	P:1("OnPlayerModelSelection(%d, %d, %d, %d)", playerid, response, listid, modelid);
	if (listid != mS_INVALID_LISTID && listid == YSI_g_PlayerCurrentListID[playerid]) 
	{
		if (Indirect_GetMeta(cb) == tagof (F@_@iii:))
		{
			Indirect_Call(_:cb, tagof (F@_@iii:), playerid, response, modelid);
		}
		else
		{
			Indirect_Call(_:cb, tagof (F@_@ii:), response, modelid);
		}
		// Free the data after call.
		Indirect_Release(cb);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}

HOOK__ OnPlayerModSelEx(playerid, response, extraid, modelid) 
{
	new 
		Func:cb<iii> = YSI_g_sRequestModelSelection[playerid];

	YSI_g_sRequestModelSelection[playerid] = Func:0<iii>;
	P:1("OnPlayerModelSelectionEx(%d, %d, %d, %d)", playerid, response, extraid, modelid);
	if (cb != Func:0<iii>) 
	{
		if (Indirect_GetMeta(cb) == tagof (F@_@iii:))
		{
			Indirect_Call(_:cb, tagof (F@_@iii:), playerid, response, modelid);
		}
		else 
		{
			Indirect_Call(_:cb, tagof (F@_@ii:), response, modelid);
		}
		// Free the data after call.
		Indirect_Release(cb);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}

HOOK__ OnPlayerDisconnect(playerid, reason) 
{
	#pragma unused reason

	// If the current cb not invalid, then we need to clear it
	if (YSI_g_sRequestModelSelection[playerid] != Func:0<iii>) 
	{
		Indirect_Release(YSI_g_sRequestModelSelection[playerid]);
		YSI_g_sRequestModelSelection[playerid] = Func:0<iii>;
	}

	// Setting it to mS_INVALID_LISTID to prevent anything happend.
	YSI_g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
	return 1;
}
