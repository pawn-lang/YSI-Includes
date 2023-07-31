# Quick Start
The default gang zone system in SA:MP can display rectangles of colour on the map, and can make those rectangles flash on and off (indicating that a zone is under attack in the original single player game). y_zonepulse extends this flashing to incorporate multiple colours and slower fades between different colours. In the original version a zone was either a colour (say red) or invisible - no other options and no smooth transition between the two states. Now a zone can be one colour and slowly change in to another colour (and back), this other colour can of course be "invisible" but doesn't have to be.

## Examples

### Slowly pulse from Red to Green

Pulse a zone from red to green and back. Changing from red to green takes one second, as does changing back from green to red.
```pawn
#define ZONE_COLOUR_RED   0xFF000033
#define ZONE_COLOUR_GREEN 0x00FF0033
new
	zone = GangZoneCreate(-100.0, -100.0, 100.0, 100.0);
GangZonePulseForPlayer(playerid, zone, ZONE_COLOUR_RED, ZONE_COLOUR_GREEN, 1000);
```
### Jump back from Green to Red

Pulse a zone from red to green, but then jump straight back to red. Changing from red to green takes one second, but going from green to red happens instantly.
```pawn
GangZonePulseForPlayer(playerid, zone, ZONE_COLOUR_RED, ZONE_COLOUR_GREEN, 1000, .time2 = 0);
// Alternate:
GangZonePulseForPlayer(playerid, zone, ZONE_COLOUR_RED, ZONE_COLOUR_GREEN, 1000, _, 0);
```

### Fade to Green and wait
This code will fade a zone from red to green, then stay green for five seconds before fading back to red. Note that the default value for delay2 (i.e. the amount of time to remain red) is the same as delay by default, but since we don't want to wait on red it needs to be explicitly set. Here the value is set to ZONE_PULSE_STAGE_TIME, which is the default time used in y_zonepulse for fades. Fading from red to green takes 1 second, as does fading back again.
```pawn
GangZonePulseForPlayer(playerid, zone, ZONE_COLOUR_RED, ZONE_COLOUR_GREEN, 1000, 5000, 1000, ZONE_PULSE_STAGE_TIME);
```
### Fade to Green and stop
y_zonepulse by default will pulse endlessly, but calling GangZoneStopPulseForX on a delay, after you know the colour has changed, but before it changes back, will appear to make the zone fade and stop. This can be done with a timer and long delay at the second colour:
```pawn
// Fade for 2 seconds, then stop for a long time (20 seconds).  This is to prevent
// the zone from starting to fade back to red too quickly.
GangZonePulseForPlayer(playerid, zone, ZONE_COLOUR_RED, ZONE_COLOUR_GREEN, 2000, 20000);
// Prevent the zone from fading back 22 seconds later, but ensure the initial
// fade is long since completed.
SetTimerEx("DoStop", 5000, 0, "ii", playerid, zone);
public DoStop(playerid, zone)
{
	GangZoneStopPulseForPlayer(playerid, zone);
}
```
You could call GangZoneShowForPlayer in DoStop to ensure the correct colour is seen, but the timer is set to significantly longer than the fade time to ensure the transition is complete.

## Functions

### GangZonePulseForPlayer

```pawn
stock GangZonePulseForPlayer(playerid, zone, from, to, time,
    delay = ZONE_PULSE_STAGE_TIME, time2 = -1, delay2 = -1)
```
Parameters:
- playerid
Which player should see the zone pulsing between two colours.
- zone
Which gang zone should be pulsing.
- from
The colour the zone should start at.
- to
The colour the zone should change to.
- time
How long the change from one colour to another should take (in milliseconds).
- delay = ZONE_PULSE_STAGE_TIME (default 50)
How long the zone should stay as the SECOND colour before returning (in milliseconds).  Default value: ZONE_PULSE_STAGE_TIME (default 50)
- time2 = -1 (means "the same as time")
How long the change back from the second colour to the first should take. By default this is the same as the time taken the other way..  Default value: -1 (means "the same as time")
- delay2 = -1 (means "the same as delay")
How long the zone should stay as the FIRST colour before changing back. By default this is the same as the time spent as the second colour, but does NOT happen when the function is first called (i.e. the fade starts instantly because the zone was already that colour)..  Default value: -1 (means "the same as delay")

Notes:
This function starts a gang zone fading from one colour to another. The first five parameters are required as they control what colours the zone fades between and how long the fading takes. The remaining parameters are optional and can adjust the effects of the zone (flashing, sawtooth, flickering etc).
   
### GangZonePulseForAll
```pawn
stock GangZonePulseForAll(zone, from, to, time,
    delay = ZONE_PULSE_STAGE_TIME, time2 = -1, delay2 = -1)
```
Parameters:
- zone
Which gang zone should be pulsing.
- from
The colour the zone should start at.
- to
The colour the zone should change to.
- time
How long the change from one colour to another should take (in milliseconds).
- delay = ZONE_PULSE_STAGE_TIME (default 50)
How long the zone should stay as the SECOND colour before returning (in milliseconds).  Default value: ZONE_PULSE_STAGE_TIME (default 50)
- time2 = -1 (means "the same as time")
How long the change back from the second colour to the first should take. By default this is the same as the time taken the other way..  Default value: -1 (means "the same as time")
- delay2 = -1 (means "the same as delay")
How long the zone should stay as the FIRST colour before changing back. By default this is the same as the time spent as the second colour, but does NOT happen when the function is first called (i.e. the fade starts instantly because the zone was already that colour)..  Default value: -1 (means "the same as delay")

Notes:
Exactly the same as GangZonePulseForPlayer, but misses off the first parameter and instead pulses the gang zone for all players. Note that if a new player connects after calling this function they will NOT see the zone pulsing.
   
### GangZoneStopPulseForPlayer
```pawn
stock GangZoneStopPulseForPlayer(playerid, zone)
```
Parameters:
- playerid
Which player should stop seeing the zone pulse.
- zone
Which gang zone should stop pulsing.

Notes:
This is the oposite function to GangZonePulseForPlayer, stopping the pulsing for that player instead of starting it. Note that this will leave the zone in whatever colour the pulse was up to, so calling GangZoneShowForPlayer straight afterwards to reset the colour is recommended.
   
### GangZoneStopPulseForAll
```pawn
stock GangZoneStopPulseForAll(zone)
```
Parameters:
- zone
Which gang zone should stop pulsing.

Notes:
Again, very similar to GangZoneStopPulseForPlayer but for all players connected to the server
