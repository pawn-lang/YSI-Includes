/**--------------------------------------------------------------------------**\
					===========================
					 Gang Zone colour pulsing.
					===========================
Description:
	Gradually fades a zone's colour between one colour and another, then back.
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
	
	The Original Code is the YSI foreach include.
	
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
	19/02/12:
		First version.
Functions:
	Public:
		__GangZonePulse - The timer that does the hard work.
	Core:
		-
	Stock:
		GangZonePulse - Pulse a zone for player or collection of players.
		GangZonePulseForPlayer - Pulse a zone for a player.
		GangZonePulseForAll - Pulse a zone for everyone.
		GangZoneStopPulse - Stop a zone pulsing for a set of players.
		GangZoneStopPulseForPlayer - Stop a zone pulsing for a single player.
		GangZoneStopPulseForAll - Stop a zone pulsing for everyone.
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Hooks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Keywords:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	ZONE_PULSE_STAGE_TIME - ms between each pulse frame.
Operators:
	-
Iterators:
	-
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_zonepulse
	#endinput
#endif
#define _INC_y_zonepulse

/*
native GangZonePulse(@PlayerSet:ps, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZonePulseForPlayer(playerid, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZonePulseForAll(zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZoneStopPulse(@PlayerSet:ps, zone);
native GangZoneStopPulseForPlayer(playerid, zone);
native GangZoneStopPulseForAll(zone);
*/

#include <a_samp>
#include "..\YSI_Internal\y_version"
#include "..\YSI_Data\y_playerset"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Core\y_debug"

#if !defined ZONE_PULSE_STAGE_TIME
	#define ZONE_PULSE_STAGE_TIME (50)
#endif

#include "y_zonepulse/impl"
#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_zonepulse/tests"
#endif
