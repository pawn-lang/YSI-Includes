/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

/*
native GangZonePulse(@PlayerSet:ps, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZonePulseForPlayer(playerid, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZonePulseForAll(zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME);
native GangZoneStopPulse(@PlayerSet:ps, zone);
native GangZoneStopPulseForPlayer(playerid, zone);
native GangZoneStopPulseForAll(zone);
*/

#include <a_samp>
#include "internal\y_version"
#include "y_playerset"
#include "y_iterate"
#include "y_debug"

#if !defined ZONE_PULSE_STAGE_TIME
	#define ZONE_PULSE_STAGE_TIME (50)
#endif

//task DoPulse1

forward __GangZonePulse(playerid, zone, from, to, time, stage, delay, time2, delay2);

public __GangZonePulse(playerid, zone, from, to, time, stage, delay, time2, delay2)
{
	if (!IsPlayerConnected(playerid))
	{
		return;
	}
	static
		sTimer[32];
	format(sTimer, sizeof (sTimer), "y_zonepulse_%d", zone);
	stage = (stage + 1) % (time + time2);
	if (stage == time)
	{
		GangZoneShowForPlayer(playerid, zone, to);
		SetPVarInt(playerid, sTimer, SetTimerEx("__GangZonePulse", delay, 0, "iiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2));
		return;
	}
	else if (stage == 0)
	{
		GangZoneShowForPlayer(playerid, zone, from);
		SetPVarInt(playerid, sTimer, SetTimerEx("__GangZonePulse", delay2, 0, "iiiiiiiii", playerid, zone, from, to, time, 0, delay, time2, delay2));
		return;
	}
	if (stage > time)
	{
		// Fade back
		new
			multiplier = (time2 - (stage - time2)),
			r = ((to >>> 24) - (from >>> 24)) * multiplier / time2 + (from >>> 24),
			g = ((to >>> 16 & 0xFF) - (from >>> 16 & 0xFF)) * multiplier / time2 + (from >>> 16 & 0xFF),
			b = ((to >>> 8 & 0xFF) - (from >>> 8 & 0xFF)) * multiplier / time2 + (from >>> 8 & 0xFF),
			a = ((to  & 0xFF) - (from  & 0xFF)) * multiplier / time2 + (from  & 0xFF);
		P:7("__GangZonePulse: %d %d %x %x %x %x", playerid, zone, r & 0xFF, g & 0xFF, b & 0xFF, a & 0xFF);
		GangZoneShowForPlayer(playerid, zone, (r << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF));
		SetPVarInt(playerid, sTimer, SetTimerEx("__GangZonePulse", ZONE_PULSE_STAGE_TIME, 0, "iiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2));
	}
	else
	{
	    // Fade there.
		new
			r = ((to >>> 24) - (from >>> 24)) * stage / time + (from >>> 24),
			g = ((to >>> 16 & 0xFF) - (from >>> 16 & 0xFF)) * stage / time + (from >>> 16 & 0xFF),
			b = ((to >>> 8 & 0xFF) - (from >>> 8 & 0xFF)) * stage / time + (from >>> 8 & 0xFF),
			a = ((to  & 0xFF) - (from  & 0xFF)) * stage / time + (from  & 0xFF);
		P:7("__GangZonePulse: %d %d %x %x %x %x", playerid, zone, r & 0xFF, g & 0xFF, b & 0xFF, a & 0xFF);
		GangZoneShowForPlayer(playerid, zone, (r << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF));
		SetPVarInt(playerid, sTimer, SetTimerEx("__GangZonePulse", ZONE_PULSE_STAGE_TIME, 0, "iiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2));
	}
	return;
}

stock _GangZonePulse(@PlayerSet:ps, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME, time2 = -1, delay2 = -1)
{
	static
		sTimer[32];
	format(sTimer, sizeof (sTimer), "y_zonepulse_%d", zone);
	if (time2 == -1)
	{
		time2 = time;
	}
	if (delay2 == -1)
	{
		delay2 = delay;
	}
	foreach (new p : PS(ps))
	{
		KillTimer(GetPVarInt(p, sTimer));
		GangZoneShowForPlayer(p, zone, from);
		SetPVarInt(p, sTimer, SetTimerEx("__GangZonePulse", delay, 0, "iiiiiiiii", p, zone, from, to, time / ZONE_PULSE_STAGE_TIME, 0, delay, time2 / ZONE_PULSE_STAGE_TIME, delay2));
	}
}

#define GangZonePulse(%0) PSF:_GangZonePulse(%0)
#define GangZonePulseForPlayer(%0) PSF:_GangZonePulse(%0)
#define GangZonePulseForAll(%0) PSF:_GangZonePulse(ALL_PLAYERS,%0)

stock _GangZoneStopPulse(@PlayerSet:ps, zone)
{
	static
		sTimer[32];
	format(sTimer, sizeof (sTimer), "y_zonepulse_%d", zone);
	foreach (new p : PS(ps))
	{
		KillTimer(GetPVarInt(p, sTimer));
	}
}

#define GangZoneStopPulse(%0) PSF:_GangZoneStopPulse(%0)
#define GangZoneStopPulseForPlayer(%0) PSF:_GangZoneStopPulse(%0)
#define GangZoneStopPulseForAll(%0) PSF:_GangZoneStopPulse(ALL_PLAYERS,%0)
