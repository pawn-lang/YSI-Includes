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


//task DoPulse1

static stock
	YSI_g_sTimer[32] = "y_zonepulse_";

forward __GangZonePulse(playerid, zone, from, to, time, stage, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1);

public __GangZonePulse(playerid, zone, from, to, time, stage, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1)
{
	if (!IsPlayerConnected(playerid))
	{
		return;
	}
	valstr(YSI_g_sTimer[12], zone);
	//format(YSI_g_sTimer, sizeof (YSI_g_sTimer), "y_zonepulse_%d", zone);
	stage = (stage + 1) % (time + time2);
	if (stage == time)
	{
		GangZoneShowForPlayer(playerid, zone, to);
		SetPVarInt(playerid, YSI_g_sTimer, SetTimerEx("__GangZonePulse", delay, 0, "iiiiiiiiiiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1));
		return;
	}
	else if (stage == 0)
	{
		GangZoneShowForPlayer(playerid, zone, from);
		SetPVarInt(playerid, YSI_g_sTimer, SetTimerEx("__GangZonePulse", delay2, 0, "iiiiiiiiiiiiiiiii", playerid, zone, from, to, time, 0, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1));
		return;
	}
	if (stage > time)
	{
		// Fade back
		new
			multiplier = 2 * time2 - stage;
		//	r = r1 * multiplier / time2 + r0,
		//	g = g1 * multiplier / time2 + g0,
		//	b = b1 * multiplier / time2 + b0,
		//	a = a1 * multiplier / time2 + a0;
		//P:7("__GangZonePulse: %d %d %x %x %x %x", playerid, zone, r & 0xFF, g & 0xFF, b & 0xFF, a & 0xFF);
		GangZoneShowForPlayer(playerid, zone, ((r1 * multiplier / time2 + r0) << 24) | (((g1 * multiplier / time2 + g0) & 0xFF) << 16) | (((b1 * multiplier / time2 + b0) & 0xFF) << 8) | ((a1 * multiplier / time2 + a0) & 0xFF));
		//GangZoneShowForPlayer(playerid, zone, (r << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF));
		SetPVarInt(playerid, YSI_g_sTimer, SetTimerEx("__GangZonePulse", ZONE_PULSE_STAGE_TIME, 0, "iiiiiiiiiiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1));
	}
	else
	{
	    // Fade there.
		//new
		//	r = r1 * stage / time + r0,
		//	g = g1 * stage / time + g0,
		//	b = b1 * stage / time + b0,
		//	a = a1 * stage / time + a0;
		//P:7("__GangZonePulse: %d %d %x %x %x %x", playerid, zone, r & 0xFF, g & 0xFF, b & 0xFF, a & 0xFF);
		GangZoneShowForPlayer(playerid, zone, ((r1 * stage / time + r0) << 24) | (((g1 * stage / time + g0) & 0xFF) << 16) | (((b1 * stage / time + b0) & 0xFF) << 8) | ((a1 * stage / time + a0) & 0xFF));
		SetPVarInt(playerid, YSI_g_sTimer, SetTimerEx("__GangZonePulse", ZONE_PULSE_STAGE_TIME, 0, "iiiiiiiiiiiiiiiii", playerid, zone, from, to, time, stage, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1));
	}
	return;
}

stock _GangZonePulse(@PlayerSet:ps, zone, from, to, time, delay = ZONE_PULSE_STAGE_TIME, time2 = -1, delay2 = -1)
{
	//static
	//	YSI_g_sTimer[32];
	//format(YSI_g_sTimer, sizeof (YSI_g_sTimer), "y_zonepulse_%d", zone);
	valstr(YSI_g_sTimer[12], zone);
	if (time2 == -1)
	{
		time2 = time;
	}
	if (delay2 == -1)
	{
		delay2 = delay;
	}
	time /= ZONE_PULSE_STAGE_TIME;
	time2 /= ZONE_PULSE_STAGE_TIME;
	// Do a load of maths in advance.
	new
		r0 = (from >>> 24),
		g0 = (from >>> 16 & 0xFF),
		b0 = (from >>> 8 & 0xFF),
		a0 = (from  & 0xFF),
		r1 = ((to >>> 24) - r0),
		g1 = ((to >>> 16 & 0xFF) - g0),
		b1 = ((to >>> 8 & 0xFF) - b0),
		a1 = ((to  & 0xFF) - a0);
	// This method would have simpler maths in the main timer, but with less
	// accurate results (possibly MUCH less accurate).  For reference, this way
	// would result in:
	//  
	//  cur = from + fromAdd - fromSub;
	//  
	/*new
		thereAdd,
		thereSub,
		backAdd,
		backSub;
	if (to >>> 24 > from >>> 24) thereAdd |= ((to >>> 24) - (from >>> 24)) / time << 24, backSub |= ((to >>> 24) - (from >>> 24)) / time2 << 24;
	else thereSub |= ((from >>> 24) - (to >>> 24)) / time << 24, backAdd |= ((from >>> 24) - (to >>> 24)) / time2 << 24;
	if (to >>> 16 & 0xFF > from >>> 16 & 0xFF) thereAdd |= ((to >>> 16 & 0xFF) - (from >>> 16 & 0xFF)) / time << 16, backSub |= ((to >>> 16 & 0xFF) - (from >>> 16 & 0xFF)) / time2 << 16;
	else thereSub |= ((from >>> 16 & 0xFF) - (to >>> 16 & 0xFF)) / time << 16, backAdd |= ((from >>> 16 & 0xFF) - (to >>> 16 & 0xFF)) / time2 << 16;
	if (to >>> 8 & 0xFF > from >>> 8 & 0xFF) thereAdd |= ((to >>> 8 & 0xFF) - (from >>> 8 & 0xFF)) / time << 8, backSub |= ((to >>> 8 & 0xFF) - (from >>> 8 & 0xFF)) / time2 << 8;
	else thereSub |= ((from >>> 8 & 0xFF) - (to >>> 8 & 0xFF)) / time << 8, backAdd |= ((from >>> 8 & 0xFF) - (to >>> 8 & 0xFF)) / time2 << 8;
	if (to & 0xFF > from & 0xFF) thereAdd |= ((to & 0xFF) - (from & 0xFF)) / time, backSub |= ((to & 0xFF) - (from & 0xFF)) / time2;
	else thereSub |= ((from & 0xFF) - (to & 0xFF)) / time, backAdd |= ((from & 0xFF) - (to & 0xFF)) / time2;*/
	FOREACH__ (new p : PS(ps))
	{
		KillTimer(GetPVarInt(p, YSI_g_sTimer));
		GangZoneShowForPlayer(p, zone, from);
		// Don't delay at the start (because that's just silly, it already is
		// that colour).
		SetPVarInt(p, YSI_g_sTimer, SetTimerEx("__GangZonePulse", ZONE_PULSE_STAGE_TIME, 0, "iiiiiiiiiiiiiiiii", p, zone, from, to, time, 0, delay, time2, delay2, r0, g0, b0, a0, r1, g1, b1, a1));
	}
}

#define GangZonePulse(%0) PSF:_GangZonePulse(%0)
#define GangZonePulseForPlayer(%0) PSF:_GangZonePulse(%0)
#define GangZonePulseForAll(%0) PSF:_GangZonePulse(ALL_PLAYERS,%0)

stock _GangZoneStopPulse(@PlayerSet:ps, zone)
{
	//static
	//	YSI_g_sTimer[32];
	//format(YSI_g_sTimer, sizeof (YSI_g_sTimer), "y_zonepulse_%d", zone);
	valstr(YSI_g_sTimer[12], zone);
	FOREACH__ (new p : PS(ps))
	{
		KillTimer(GetPVarInt(p, YSI_g_sTimer));
	}
}

#define GangZoneStopPulse(%0) PSF:_GangZoneStopPulse(%0)
#define GangZoneStopPulseForPlayer(%0) PSF:_GangZoneStopPulse(%0)
#define GangZoneStopPulseForAll(%0) PSF:_GangZoneStopPulse(ALL_PLAYERS,%0)
