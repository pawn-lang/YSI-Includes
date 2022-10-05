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

@test(.group = "y_dialog", .run = false) y_dialog_Compile()
{
	if (FALSE)
	{
		Dialog_Get(0);
		inline const A(arg0, arg1, string:arg2[])
		{
			#pragma unused arg0, arg1, arg2
		}
		inline const B(arg0, arg1, arg2, arg3, string:arg4[])
		{
			#pragma unused arg0, arg1, arg2, arg3, arg4
		}
		Dialog_ShowCallback(0, using inline A, DIALOG_STYLE_MSGBOX, "", "", "");
		Dialog_ShowCallback(0, using inline B, DIALOG_STYLE_MSGBOX, "", "", "");
		Dialog_Show(0, DIALOG_STYLE_MSGBOX, "", "", "");
		Dialog_Hide(0);
		Dialog_ShowPlayerDialog(0, 0, DIALOG_STYLE_MSGBOX, "", "", "", "");
	}
}

#if defined YSI_DIALOG_ASK
	// Using "y_testing" in here isn't actually possible, because it needs dialogs
	// to ask players for feedback...
	#endinput
#endif

@test(.group = "y_dialog") Dialog_ShowCallback(playerid)
{
	inline const Response(arg0, arg1, string:arg2[])
	{
		#pragma unused arg0, arg1, arg2
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_MSGBOX, "Dialog", "Text", "OK");
	ASK("Did the dialog show up (you may need to close it before answering)?");
}

@test(.group = "y_dialog") Dialog_CallbackOK(playerid)
{
	inline const Response(response, arg1, string:arg2[])
	{
		if (response)
		{
			SendClientMessage(playerid, 0xFF0000AA, "HI!");
		}
		#pragma unused arg1, arg2
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_MSGBOX, "Dialog", "Text", "OK", "CANCEL");
	ASK("Does clicking OK send `HI!`?");
}

@test(.group = "y_dialog") Dialog_CallbackCancel(playerid)
{
	inline const Response(response, arg1, string:arg2[])
	{
		if (!response)
		{
			SendClientMessage(playerid, 0xFF0000AA, "BYE!");
		}
		#pragma unused arg1, arg2
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_MSGBOX, "Dialog", "Text", "OK", "CANCEL");
	ASK("Does clicking CANCEL send `BYE!`?");
}

@test(.group = "y_dialog") Dialog_CallbackInput(playerid)
{
	inline const Response(response, arg1, string:input[])
	{
		SendClientMessage(playerid, 0xFF0000AA, "Your input:");
		if (response)
		{
			SendClientMessage(playerid, 0xFF0000AA, input);
		}
		#pragma unused arg1
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "Dialog", "Input:", "OK", "CANCEL");
	ASK("Does clicking OK send your input?");
}

@test(.group = "y_dialog") Dialog_CallbackIgnore(playerid)
{
	inline const Response(response, arg1, string:input[])
	{
		SendClientMessage(playerid, 0xFF0000AA, "Your input:");
		if (response)
		{
			SendClientMessage(playerid, 0xFF0000AA, input);
		}
		#pragma unused arg1
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "Dialog", "Input:", "OK", "CANCEL");
	ASK("Does clicking CANCEL NOT send your input?");
}

forward Dialog_TestHide(playerid);

public Dialog_TestHide(playerid)
{
	Dialog_Hide(playerid);
}

@test(.group = "y_dialog") Dialog_Hide(playerid)
{
	inline const Response(arg0, arg1, string:arg2[])
	{
		#pragma unused arg0, arg1, arg2
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "Dialog", "Input:", "OK", "CANCEL");
	SetTimerEx("Dialog_TestHide", 5000, false, "i", playerid);
	ASK("Does the dialog disappear after 5 seconds?");
}

