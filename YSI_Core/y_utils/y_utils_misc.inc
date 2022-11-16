/**
 * <library
 *   name="y_utils - misc"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

/// <p/>

// Better handling of operator precedences and floating point numbers.  This
// will now work for ALL regular numbers (including -0.5 which broke the old
// version).  I don't know of any complex expressions that break it with
// operator precedences, but I'm not ruling it out.  The brackets do try and
// account for that possibility, but I just don't know.
#define NO_VALUE(%0) ((2*%0-1)==2*(%0-1))

#define ALS_MRET_(%0) forward PP_MRET();public PP_MRET(%0)(0,0,YSI_EMPTY)(NT_US)

#if defined YSI_LOCK_MODE
	public OnYSIInit()
	{
		new
			find = strfind(YSI_gLockData[5], YSI_gLockData[1]) + 6;
		find = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		new
			found = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		if (strval(YSI_gLockData[found]) ^ UNIQUE_SYMBOL != _LOCK_IP_3 ^ UNIQUE_SYMBOL || strval(YSI_gLockData[find]) - _LOCK_IP_3 != _LOCK_IP_2 - _LOCK_IP_3)
		{
			y_lock 1;
		}
		#if defined _y_utils_OnYSIInit
			_y_utils_OnYSIInit();
		#endif
		return 1;
	}

	#if defined _ALS_OnYSIInit
		#undef OnYSIInit
	#else
		#define _ALS_OnYSIInit
	#endif
	#define OnYSIInit _y_utils_OnYSIInit

	#if defined _y_utils_OnYSIInit
		forward _y_utils_OnYSIInit();
	#endif
#endif

#if !defined __once
	#define __once%1;%0) (__gOnce++)%1;(%0),__gOnce=0)
	#define __gOnce++)%1;(), __gOnce++)%1;
	stock __gOnce = 1;
#endif

#define PP_RIGHT_BRACKET<> )

#define IF__(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)if()
#define SWITCH__(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)switch()

#define for(IF_FAIL:new|||%1;%2) for(IF_PASS:new %1=%2;%1;)

#define IF_FAIL:new%0|||%1;%2)%8() ;__once;)%8(new%0 %1=%2 PP_RIGHT_BRACKET<>
#define IF_PASS:%3;%4;%9)%8() %3;__once;)%8(%4 PP_RIGHT_BRACKET<>

#if YSI_KEYWORD(if)
	#define if(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)if()
#endif

#if YSI_KEYWORD(switch)
	#define switch(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)switch()
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - misc</library>
 * <param name="playerid">The player to check.</param>
 * <returns>
 *   Is this a valid playerid (NOT, is the player connected).
 * </returns>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:VALID_PLAYERID(playerid));
#define VALID_PLAYERID(%0) UCMP((%0), MAX_PLAYERS)

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - misc</library>
 * <param name="playerid">Player to mess up.</param>
 * <remarks>
 *   Make some random effects on the player.  Inspired by the single player chaos
 *   mod.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined WEAPON
	#define WEAPON: _:
#endif

stock Utils_ChaosMod(playerid)
{
	new tmp;
	switch (random(720))
	{
		case 0:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleVelocity(tmp, 0.0, 0.0, 0.0);
			else
				SetPlayerVelocity(playerid, 0.0, 0.0, 0.0);
		}
		case 1:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleVelocity(tmp, 0.0, 0.0, 1000.0);
			else
				SetPlayerVelocity(playerid, 0.0, 0.0, 1000.0);
		}
		case 2:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleHealth(tmp, 0.0);
			else
				SetPlayerHealth(playerid, 0.0);
		}
		case 3:
		{
			SetPlayerArmedWeapon(playerid, WEAPON:0);
		}
		case 4:
		{
			SetPlayerWorldBounds(playerid, 0.1, -0.1, 0.1, -0.1);
		}
		case 5:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				LinkVehicleToInterior(tmp, GetPlayerInterior(playerid) ^ 1);
			SetPlayerInterior(playerid, GetPlayerInterior(playerid) ^ 1);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - misc</library>
 * <param name="old">Unused.</param>
 * <param name="playerid">Player to mess up.</param>
 * <remarks>
 *   Timer for applying random effects.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP
	public OnChaosTimer(oid, playerid)
	{
		Utils_ChaosMod(playerid);
	}
#else
	static stock OnChaosTimer__(oid, playerid)
	{
		#pragma unused old, playerid
	}
#endif

