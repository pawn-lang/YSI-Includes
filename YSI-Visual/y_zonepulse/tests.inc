static
	gZone;

// Test pulsing 1.
PTestInit:GangZonePulse1(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse1(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000);
	ASK("Is the zone pulsing from Red to Green?");
}

PTestClose:GangZonePulse1(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 2.
PTestInit:GangZonePulse2(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse2(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 333);
	ASK("Is the zone pulsing from Red to Green fast?");
}

PTestClose:GangZonePulse2(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 3.
PTestInit:GangZonePulse3(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse3(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 1000, 0, 0);
	ASK("Is the zone jumping back to Red?");
}

PTestClose:GangZonePulse3(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 4.
PTestInit:GangZonePulse4(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse4(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 3000, 500, 0);
	ASK("Is the zone stopping on Green?");
}

PTestClose:GangZonePulse4(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 7.
PTestInit:GangZonePulse7(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse7(playerid)
{
	// Regression bug, doing this used to cause a pause at the start - first bug
	// found and fixed by these unit tests.
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 3000, 500, 0);
	ASK("Was there no pause at the start?");
}

PTestClose:GangZonePulse7(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 5.
PTestInit:GangZonePulse5(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse5(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 500, 0, 500, 3000);
	ASK("Is the zone stopping on Red?");
}

PTestClose:GangZonePulse5(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test pulsing 6.
PTestInit:GangZonePulse6(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZonePulse6(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000, _, 500, _);
	ASK("Is Green -> Red faster?");
}

PTestClose:GangZonePulse6(playerid)
{
	GangZoneStopPulse(playerid, gZone);
	GangZoneDestroy(gZone);
}

// Test stopping 1.
PTestInit:GangZoneStopPulse1(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZoneStopPulse1(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 2000);
	GangZoneStopPulse(playerid, gZone);
	ASK("Is the zone NOT pulsing?");
}

PTestClose:GangZoneStopPulse1(playerid)
{
	GangZoneDestroy(gZone);
}

// Test stopping 2.
PTestInit:GangZoneStopPulse2(playerid)
{
	// Create the zone.
	gZone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
	GangZoneShowForPlayer(playerid, gZone, 0xFF0000AA);
	SetPlayerPos(playerid, 0.0, 0.0, 5.0);
}

PTest:GangZoneStopPulse2(playerid)
{
	GangZonePulseForPlayer(playerid, gZone, 0xFF0000AA, 0x00FF00AA, 1000);
	SetTimerEx("GangZoneStopPulse2", 4000, 0, "i", playerid);
	ASK("Does the pulsing stop after four seconds?");
}

forward GangZoneStopPulse2(playerid);
public GangZoneStopPulse2(playerid)
{
	GangZoneStopPulse(playerid, gZone);
}

PTestClose:GangZoneStopPulse2(playerid)
{
	GangZoneDestroy(gZone);
}
