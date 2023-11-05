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
	/**
	 * <library>y_rconfix</library>
	 */
	YSI_gscOnClientCheckResponse[] = "FIXES_OnClientCheckResponse",
	/**
	 * <library>y_rconfix</library>
	 */
	YSI_gscRconFixFS[] = "callbackfix.amx";

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   This code is always needed, even if fixes.inc exists, because y_master can
 *   repeatedly load and unload it to use as a buffer filterscript.  Basically,
 *   because this FS is always loaded it ensures that 16 other filterscripts
 *   can't all be loaded at once.  So if 15 are loaded and we need an extra
 *   space to reload one while preserving data we can unload this one, use the
 *   spare space, then load this one back up again.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define __asm(%0,%1,%2,%3) (((0x%3) << 24) | ((0x%2) << 16) | (0x%1 << 8) | (0x%0))

// We are just re-using a random state here.  This automata is always set to
// `_ALS_go` basically instantly, in many different includes, so we can just
// abuse that fact to avoid creating another one.
Server_LoadRconFix() <_ALS : _ALS_no>
{
}

// Set this to the fallback state, in case no other include is used.
Server_LoadRconFix() <>
{
	if (Server_IsSAMP())
	{
		// Test if the fix has already been loaded.
		setproperty(27, YSI_gscOnClientCheckResponse, 0);
		SendRconCommand(__const(YSI_gscOnClientCheckResponse));
		if (getproperty(27, YSI_gscOnClientCheckResponse) != 0)
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
					__asm(20,01,00,00), __asm(E0,F1,08,08), __asm(14,00,08,00), __asm(AC,00,00,00),
					__asm(90,01,00,00), __asm(C0,01,00,00), __asm(C0,41,00,00), __asm(FF,FF,FF,FF),
					__asm(38,00,00,00), __asm(48,00,00,00), __asm(60,00,00,00), __asm(60,00,00,00),
					__asm(60,00,00,00), __asm(60,00,00,00), __asm(94,00,00,00), __asm(62,00,00,00),
					__asm(08,00,00,00), __asm(78,00,00,00), __asm(00,00,00,00), __asm(86,00,00,00),
					__asm(00,00,00,00), __asm(8D,00,00,00), __asm(00,00,00,00), __asm(99,00,00,00),
					__asm(1F,00,4F,6E), __asm(43,6C,69,65), __asm(6E,74,43,68), __asm(65,63,6B,52),
					__asm(65,73,70,6F), __asm(6E,73,65,00), __asm(4F,6E,52,63), __asm(6F,6E,43,6F),
					__asm(6D,6D,61,6E), __asm(64,00,73,74), __asm(72,63,6D,70), __asm(00,73,65,74),
					__asm(70,72,6F,70), __asm(65,72,74,79), __asm(00,43,61,6C), __asm(6C,52,65,6D),
					__asm(6F,74,65,46), __asm(75,6E,63,74), __asm(69,6F,6E,00), __asm(80,78,00,2E),
					__asm(27,87,FF,FF), __asm(FF,7F,27,01), __asm(27,00,29,0C), __asm(27,10,80,7B),
					__asm(00,2C,14,36), __asm(81,0C,27,1C), __asm(27,1B,27,00), __asm(27,1B,27,10),
					__asm(80,7B,01,2C), __asm(14,80,54,30), __asm(80,59,30,2E), __asm(81,05,18,81),
					__asm(05,14,81,05), __asm(10,81,05,0C), __asm(27,28,27,00), __asm(27,18,80,7B),
					__asm(02,2C,1C,30), __asm(84,B2,A5,B0), __asm(45,85,9A,FD), __asm(9E,6E,84,9B),
					__asm(B1,D2,65,86), __asm(F3,D1,86,68), __asm(86,AB,8D,D6), __asm(52,86,AB,CD),
					__asm(E0,6F,86,F3), __asm(CD,CA,00,00), __asm(00,00,86,CB), __asm(A5,D2,69,00)
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
			SendRconCommand(__const("loadfs ../scriptfiles/callbackfix"));
			#if defined YSI_FIX_CALLBACKS
				state OnClientCheckResponse : OnClientCheckResponse_GM;
			#endif
		}
		else
		{
			Debug_Warning("Could not load RconCommand/ClientCheckResponse fix FS.");
			Debug_Info("Ignore this error if the FS already loaded.");
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   Unload the callback fix filterscript.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// We are just re-using a random state here.  This automata is always set to
// `_ALS_go` basically instantly, in many different includes, so we can just
// abuse that fact to avoid creating another one.
stock Server_UnloadRconFix() <_ALS : _ALS_no>
{
}

stock Server_UnloadRconFix() <>
{
	if (Server_IsSAMP())
	{
		SendRconCommand(__const("unloadfs ../scriptfiles/callbackfix"));
	}
}

#if !defined YSI_FIX_CALLBACKS
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   Call the hooked version of <c>OnClientCheckResponse</c>, regardless of how
 *   this version is called.  So either natively or using the fix here.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   Call the hooked version of <c>OnClientCheckResponse</c>, regardless of how
 *   this version is called.  So either natively or using the fix here.  But
 *   use states to only call the fix version in the gamemode, not in
 *   filterscripts, since it works there already.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata);

public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata) <OnClientCheckResponse : OnClientCheckResponse_FS>
{
	return 0;
}

public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata) <>
{
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   Define the states for calling the fix callbacks, or not.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock _FIXES_OnClientCheckResponse() <OnClientCheckResponse : OnClientCheckResponse_GM, OnClientCheckResponse : OnClientCheckResponse_FS>
{
	// Define states only.
}

#if defined _ALS_OnClientCheckResponse
	#error _ALS_OnClientCheckResponse defined
#endif
#define _ALS_OnClientCheckResponse
#define OnClientCheckResponse(%0) FIXES_OnClientCheckResponse(%0) <OnClientCheckResponse : OnClientCheckResponse_GM>

