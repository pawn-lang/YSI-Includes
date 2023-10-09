# Quick Start

## Introduction
The races system in YSI is one of the very first bits of code I wrote for it, back before it was even called YSI. The main "OnPlayerEnterCheckpoint" code remained almost identical to its original version from "San Andreas:Underground" 7 years ago until today when I made some updates (but the main structure is STILL the same).

This library fairly obviously provides functions for defining and running races. You can have (by default) up to 16 races running in parallel, with 1024 checkpoints between them. This system doesn't restrict the number of checkpoints per-race but globally instead, so you can have one with 1 checkpoint (a drag-race perhaps) and another with 1023 (some sort of ridiculous Le-Mans length tour).


## Basic Use
Using the basic system is very simple, but as with all of YSI there are many options that can be changed by advanced users:
```pawn
#include <YSI\y_races>

new
	gRace;

public OnScriptInit()
{
	// Declare a new race.
	gRace = Race_Create();
	// Set it to have 0 laps.
	Race_SetLaps(gRace, 0);
	// Set the price to join the race to $200.
	// Note that if you want, you can set this to
	// 0 and create your own payment system.
	Race_SetEntry(gRace, 200);
}
```
That code creates and initialises a race. The function "Race_Create" also has several optional parameters so you can write the code above as:
```pawn
public OnScriptInit()
{
	gRace = Race_Create(.laps = 0, .entry = 200);
}
```
Now this race is very boring - it doesn't have any starting points or any checkpoints, so let's add some:
```pawn
// Add some points to the starting grid.
// This is a drag race between two cars along the LV airstrip.
// X, Y, Z, Angle.
Race_AddStart(gRace, 425.0, 2488.0, 16.2, 90.0);
Race_AddStart(gRace, 425.0, 2512.0, 16.2, 90.0);
// Add two checkpoints - its a drag race there and back!
// No angle this time.  Arrows and chequred flags are done automatically.
Race_AddCheckpoint(gRace, -78.5, 2500.0, 16.1);
Race_AddCheckpoint(gRace, 434.0, 2500.0, 16.1);
```
Finally, we need some players:
```pawn
YCMD:join(playerid, params[], help)
{
	#pragma unused params
	if (help)
	{
		SendClientMessage(playerid, 0xFF0000AA, "Adds you to the race.");
	}
	else
	{
		Race_PlayerJoin(playerid, gRace);
	}
	return 1;
}
```
And the very last thing, once everyone has been added to the race. Start it:
```pawn
YCMD:start(playerid, params[], help)
{
	#pragma unused params
	if (help)
	{
		SendClientMessage(playerid, 0xFF0000AA, "Begin the race.");
	}
	else
	{
		Race_Start(gRace);
	}
	return 1;
}
```
### Callbacks

This include adds several callbacks that can be used:
```pawn
// Called when a player finishes the race.
forward OnPlayerFinishRace(playerid, race, position, prize, time);

// Called when a player drops out of the race.
forward OnPlayerExitRace(playerid, race);

// Called when the race is over.
forward OnRaceEnd(race);
```
Note that currently none of these are forwarded, nor are they handled by y_hooks.

### Race Position

This include also has experimental code to get a player's position in the race. Simply call:
```pawn
Race_GetPlayerPosition(playerid);
```
As often as you want to update any indication of their position. Note that the information is only updated once every 500 ms (half a second - load balanced).

## Functions

### Race_Create
```pawn
stock Race_Create(laps = 0, entry = 0, countdown = 3, bool:arial = false,
                  bool:fixedPrize = true, exitTime = 0, interior = 0,
                  world = 0, bool:restart = false)
```
Parameters:
- laps = 0
The number of laps to run the race for. If this value is "0" then the race is a straight shot to some point. If the value is anything other than "0" then the start checkpoint is also the end checkpoint.  Default value: 0
- entry = 0
How much a race costs to enter. Set to 0 for a custom entry/prize system. The prize money is relative to the entry cost and the number of people who entered - the first three positions win by default.  Default value: 0
- countdown = 3
When the race starts players are frozen in place and a timer counting down is shown. By default this goes from 3.  Default value: 3
- arial = 0
Is this race for planes (i.e. should it use the donut checkpoints instead of the regular vehicle ones).  Default value: 0
- fixedPrize = false
Use the default inbuilt prize money system.  Default value: false
- exitTime = 0
How many seconds can a player be out of their vehicle during a race before they are disqualified? 0 is infinite.  Default value: 0
- interior = 0
Is the race in an interior? And if so, which one.  Default value: 0
- world = 0
The virtual world to host the race in.  Default value: 0
- restart = false
By default, once a race is completed it will be deleted from the system. Set this parameter to "true" to enable the race to be reused.  Default value: false

Return:
- An identifier for the race

Notes:
As mentioned above, this function has a number of optional parameters, listed here. All of these options also have equivalent "Race_SetXXX" functions that can be called instead.
   
### Race_Destroy

```pawn
stock Race_Destroy(slot, bool:refund = false)
```

Parameters:
- slot
The race to destroy.
- refund = false
Should players be given their money back if the race hasn't started yet.  Default value: false

Notes:
This removes a race from the system - the race can have started or not.
   
### Race_AddCheckpoint

```pawn
foreign Race_AddCheckpoint(raceid, Float:x, Float:y, Float:z)
```
Parameters:
- raceid
The race to add a checkpoint to.
- Float:x
The x location of the checkpoint.
- Float:y
The y location of the checkpoint.
- Float:z
The z location of the checkpoint.

Notes:
A race is made by first setting one up with Race_Create, then adding sequential checkpoints to it. This function adds the checkpoints, assuming that one checkpoint immediately follows the previously added one for the current race.
   
### Race_AddStart

```pawn
foreign Race_AddStart(raceid, Float:x, Float:y, Float:z, Float:a)
```
Parameters:
- raceid
The race to add a start point to.
- Float:x
The x location of the start point.
- Float:y
The y location of the start point.
- Float:z
The z location of the start point.
- Float:a
The facing angle for the start point.

Notes:
As well as points to follow, a race needs a starting grid. This function creates one point on that starting grid.
   
### Race_IsActive

```pawn
foreign Race_IsActive(raceid)
```

Parameters:
- raceid
The race to check.

Notes:
Is there a race already stored in this slot?
   
### Race_PlayerJoin

```pawn
foreign Race_PlayerJoin(playerid, race)
```
Parameters:
- playerid
The player to add to a race.
- race
The race to join.

Notes:
Adds a player to a race that has not yet begun. Note the odd parameter order.
   
### Race_PlayerLeave

```pawn
forward Race_PlayerLeave(playerid, bool:refund = false)
```
Parameters:
- playerid
The player to remove from a race.
- refund = false
Should they get their money back.  Default value: false

Notes:
Remove a player from a race that has not yet begun.
   
### Race_SetPlayer
```pawn
foreign Race_SetPlayer(race, playerid, bool:set)
```

Parameters:
- race
The race to join or leave.
- playerid
The player to remove from, or add to, a race.
- set
Add or remove them.

Notes:
This function is now the preferred method of adding people to, and removing them from, a race. The parameter order is more sensible than the other functions, it can remove people from races that are already running, and it is the correct interface for y_groups.
