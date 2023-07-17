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

