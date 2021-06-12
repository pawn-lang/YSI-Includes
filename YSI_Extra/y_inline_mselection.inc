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

stock const
	Func:YSI_g_sRequestModelSelection[MAX_PLAYERS]<ii>,
	YSI_g_PlayerCurrentListID[MAX_PLAYERS] = {mS_INVALID_LISTID, ...};

stock ShowModelSelectionInline(playerid, listid, const headerText[], Func:cb<ii>, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA) 
{
	new ret = ShowModelSelectionMenu(playerid, listid, headerText, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret) 
	{
		Indirect_Claim(cb);
		YSI_g_PlayerCurrentListID[playerid] = cb;
		YSI_g_sRequestModelSelection[playerid] = listid;
	}
	return ret;
}

stock ShowModelSelectionInlineEx(playerid, const itemsArray[], itemAmount, const headerText[], extraid, Func:cb<ii>, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA) 
{
	new ret = ShowModelSelectionMenuEx(playerid, itemsArray, itemAmount, headerText, extraid, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret) 
	{
		Indirect_Claim(cb);
		YSI_g_PlayerCurrentListID[playerid] = cb;
		YSI_g_sRequestModelSelection[playerid] = extraid;
	}
	return ret;
}

HOOK__ OnPlayerModelSelection(playerid, response, listid, modelid) 
{
	new 
		Func:cb<ii> = YSI_g_sRequestModelSelection[playerid];

	YSI_g_sRequestModelSelection[playerid] = Func:0<ii>;

	if (listid != mS_INVALID_LISTID && listid == YSI_g_PlayerCurrentListID[playerid]) 
	{
		YSI_g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
		@.cb(response, modelid);
	}
	Indirect_Release(cb);
	return 1;
}

HOOK__ OnPlayerModelSelectionEx(playerid, response, extraid, modelid) 
{
	new 
		Func:cb<ii> = YSI_g_sRequestModelSelection[playerid];

	YSI_g_sRequestModelSelection[playerid] = Func:0<ii>;

	if (extraid != mS_INVALID_LISTID && extraid == YSI_g_PlayerCurrentListID[playerid]) 
	{
		YSI_g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
		@.cb(response, modelid);
	}
	Indirect_Release(cb);
	return 1;
}

HOOK__ OnPlayerDisconnect(playerid, reason) 
{
	#pragma unused reason

	// If the current callback not invalid, then we need to clear it
	if (YSI_g_sRequestModelSelection[playerid] != Func:0<ii>) {
		Indirect_Release(YSI_g_sRequestModelSelection[playerid]);
		YSI_g_sRequestModelSelection[playerid] = Func:0<ii>;
	}

	// Setting it to mS_INVALID_LISTID to prevent anything happend.
	YSI_g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
	return 1;
}
