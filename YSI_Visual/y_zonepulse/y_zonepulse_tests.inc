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

static
	gZone = 0;

// Test pulsing 1.
PTEST_INIT__ GangZonePulse1(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse1(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000);
	ASK("Is the zone pulsing from Red to Green?");
}

PTEST_CLOSE__ GangZonePulse1(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 2.
PTEST_INIT__ GangZonePulse2(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse2(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 333);
	ASK("Is the zone pulsing from Red to Green fast?");
}

PTEST_CLOSE__ GangZonePulse2(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 3.
PTEST_INIT__ GangZonePulse3(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse3(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 1000, 0, 0);
	ASK("Is the zone jumping back to Red?");
}

PTEST_CLOSE__ GangZonePulse3(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 4.
PTEST_INIT__ GangZonePulse4(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse4(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 3000, 500, 0);
	ASK("Is the zone stopping on Green?");
}

PTEST_CLOSE__ GangZonePulse4(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 7.
PTEST_INIT__ GangZonePulse7(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse7(playerid)
{
	// Regression bug, doing this used to cause a pause at the start - first bug
	// found and fixed by these unit tests.
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 3000, 500, 0);
	ASK("Was there no pause at the start?");
}

PTEST_CLOSE__ GangZonePulse7(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 5.
PTEST_INIT__ GangZonePulse5(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse5(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 0, 500, 3000);
	ASK("Is the zone stopping on Red?");
}

PTEST_CLOSE__ GangZonePulse5(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 6.
PTEST_INIT__ GangZonePulse6(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZonePulse6(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000, _, 500, _);
	ASK("Is Green -> Red faster?");
}

PTEST_CLOSE__ GangZonePulse6(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test stopping 1.
PTEST_INIT__ GangZoneStopPulse1(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZoneStopPulse1(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000);
	GangZoneStopPulse(playerid, gZone);
	ASK("Is the zone NOT pulsing?");
}

PTEST_CLOSE__ GangZoneStopPulse1(playerid)
{
	GangZoneDestroy(gZone);
}

// Test stopping 2.
PTEST_INIT__ GangZoneStopPulse2(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTEST__ GangZoneStopPulse2(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 1000);
	YSI_SetTimerEx("GangZoneStopPulse2", 4000, 0, "i", playerid);
	ASK("Does the pulsing stop after four seconds?");
}

forward GangZoneStopPulse2(playerid);
public GangZoneStopPulse2(playerid)
{
	GangZoneStopPulse(playerid, gZone);
}

PTEST_CLOSE__ GangZoneStopPulse2(playerid)
{
	GangZoneDestroy(gZone);
}
