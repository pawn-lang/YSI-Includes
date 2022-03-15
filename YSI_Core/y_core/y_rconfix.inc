/*
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
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

#if defined _INC_y_rconfix
	#endinput
#endif
#define _INC_y_rconfix

#if !_YSI_SAFE_STARTUP
	#if defined YSI_FIX_CALLBACKS
		forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);
	#endif

	#endinput
#endif

static stock const
	YSI_gscOnClientCheckResponse[] = "FIXES_OnClientCheckResponse",
	YSI_gscRconFixFS[] = "callbackfix.amx";

// This code is always needed, even if fixes.inc exists, because y_master can
// repeatedly load and unload it to use as a buffer filterscript.  Basically,
// because this FS is always loaded it ensures that 16 other filterscripts can't
// all be loaded at once.  So if 15 are loaded and we need an extra space to
// reload one while preserving data we can unload this one, use the spare space,
// then load this one back up again.
y_rconfix_Load()
{
	#if !defined YSI_OPENMP__
		// Test if the fix has already been loaded.
		setproperty(27, YSI_gscOnClientCheckResponse, 0);
		YSI_SendRconCommand(YSI_gscOnClientCheckResponse);
		if (getproperty(27, YSI_gscOnClientCheckResponse) == 27)
		{
			return;
		}
		// It is.  Create the file.
		if (!fexist(YSI_gscRconFixFS))
		{
			/*
				// Minimise code size.
				#pragma option -d0
				#pragma option -O1

				// Declare some natives for use.
				native CallRemoteFunction(const function[], const format[], ...);
				native setproperty(id = 0, const name[] = "", value = cellmin, const string[] = "");
				native strcmp(const string1[], const string2[], bool:ignorecase = false, length = cellmax);

				// Use the same string for everything, so we only need one.  And pack it.
				new const FIXES_OnClientCheckResponse[] = !"FIXES_OnClientCheckResponse";

				forward OnRconCommand(const cmd[]);

				// This callback just needs to exist in one filterscript.
				public OnRconCommand(const cmd[])
				{
					// The smallest I could make the assembly without `#emit`.
					if (strcmp(cmd, FIXES_OnClientCheckResponse, true) == 0)
					{
						// Add 2 cells of padding here to make the AMX a nice size.
						return !setproperty(27, FIXES_OnClientCheckResponse, 27, "\0\0");
					}
					return 0;
				}

				forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

				// This callback needs to invoke a different callback in GMs.
				public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
				{
					// Invoke the global callback.
					return CallRemoteFunction(FIXES_OnClientCheckResponse, !"iiii", playerid, actionid, memaddr, retndata);
				}
			*/
			static
				lRCFixCode[] = {
					0x00000120, 0x0808F1E0, 0x00080014, 0x000000AC, 0x00000190, 0x000001C0, 0x000041C0, 0xFFFFFFFF,
					0x00000038, 0x00000048, 0x00000060, 0x00000060, 0x00000060, 0x00000060, 0x00000094, 0x00000062,
					0x00000008, 0x00000078, 0x00000000, 0x00000086, 0x00000000, 0x0000008D, 0x00000000, 0x00000099,
					0x6E4F001F, 0x65696C43, 0x6843746E, 0x526B6365, 0x6F707365, 0x0065736E, 0x63526E4F, 0x6F436E6F,
					0x6E616D6D, 0x74730064, 0x706D6372, 0x74657300, 0x706F7270, 0x79747265, 0x6C614300, 0x6D65526C,
					0x4665746F, 0x74636E75, 0x006E6F69, 0x2E007880, 0xFFFF8727, 0x01277FFF, 0x0C290027, 0x7B801027,
					0x36142C00, 0x1C270C81, 0x00271B27, 0x10271B27, 0x2C017B80, 0x30548014, 0x2E305980, 0x81180581,
					0x05811405, 0x0C058110, 0x00272827, 0x7B801827, 0x301C2C02, 0xB0A5B284, 0xFD9A8545, 0x9B846E9E,
					0x8665D2B1, 0x6886D1F3, 0xD68DAB86, 0xCDAB8652, 0xF3866FE0, 0x0000CACD, 0xCB860000, 0x0069D2A5
				};
			new
				File:fs = fopen(YSI_gscRconFixFS, io_write);
			if (fs)
			{
				fblockwrite(fs, lRCFixCode);
				fclose(fs);
			}
		}
		if (fexist(YSI_gscRconFixFS))
		{
			YSI_SendRconCommand("loadfs ../scriptfiles/callbackfix");
			state OnClientCheckResponse : OnClientCheckResponse_GM;
		}
		else
		{
			P:W("Could not load RconCommand/ClientCheckResponse fix FS.");
			P:I("Ignore this error if the FS already loaded.");
		}
	#endif
}

stock y_rconfix_Unload()
{
	#if !defined YSI_OPENMP__
		YSI_SendRconCommand("unloadfs ../scriptfiles/callbackfix");
	#endif
}

#if defined YSI_FIX_CALLBACKS
	forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

	public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
	{
		// Enable, then disable, the call in to the real version (if it exists).
		state OnClientCheckResponse : OnClientCheckResponse_GM;
		new
			ret = FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
		state OnClientCheckResponse : OnClientCheckResponse_FS;
		return ret;
	}

	forward FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
	public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata) <OnClientCheckResponse : OnClientCheckResponse_FS>
	{
		return 0;
	}

	public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata) <>
	{
		return 0;
	}

	static stock _FIXES_OnClientCheckResponse() <OnClientCheckResponse : OnClientCheckResponse_GM, OnClientCheckResponse : OnClientCheckResponse_FS>
	{
		// Define states only.
	}

	#if defined _ALS_OnClientCheckResponse
		#error _ALS_OnClientCheckResponse defined
	#endif
	#define _ALS_OnClientCheckResponse
	#define OnClientCheckResponse(%0) FIXES_OnClientCheckResponse(%0) <OnClientCheckResponse : OnClientCheckResponse_GM>
#endif

