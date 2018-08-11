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

#define MAX_RACE_WINNERS 3

#if !defined MAX_RACE_CHECKPOINTS
	#define MAX_RACE_CHECKPOINTS 1024
#endif

#if !defined MAX_RACE_STARTS
	#define MAX_RACE_STARTS 32
#endif

#define NO_RACE -1
#define RACE_NO_CHECKPOINT -1
#define RACE_LOOP_GRANULARITY 5
#define RACE_PLAYER_OUT 0x80000000

enum e_RACE_FLAGS:(<<= 1)
{
	e_RACE_FLAGS_NONE = 0,
	e_RACE_FLAGS_EXIT_TIME = 0xFFFF,
	e_RACE_FLAGS_ACTIVE = 0x10000,
	e_RACE_FLAGS_ARIAL,
	e_RACE_FLAGS_REL_WIN,
	e_RACE_FLAGS_STARTED,
	e_RACE_FLAGS_RACING,
	e_RACE_FLAGS_CD_JOIN,
	e_RACE_FLAGS_RESTART
}

enum E_RACE
{
	e_RACE_FLAGS:E_RACE_FLAGS,
	E_RACE_LAPS,
	E_RACE_CHECKPOINTS,
	E_RACE_CP_START,
	E_RACE_RACER_COUNT,
	E_RACE_RACER_MAX,
	E_RACE_COUNTDOWN,
	E_RACE_FINISHED,
	E_RACE_ENTRY,
	E_RACE_VW,
	E_RACE_INT,
	E_RACE_PRIZES[MAX_RACE_WINNERS]
}

enum E_RACE_PLAYER
{
	E_RACE_PLAYER_RACE,
	E_RACE_PLAYER_LAP,
	E_RACE_PLAYER_CP,
	E_RACE_PLAYER_TIME,
	#if defined RACE_POSITION
		E_RACE_PLAYER_POSITION,
	#endif
	E_RACE_PLAYER_TOUT,
	Float:E_RACE_PLAYER_X,
	Float:E_RACE_PLAYER_Y,
	Float:E_RACE_PLAYER_Z,
	Float:E_RACE_PLAYER_A,
	E_RACE_PLAYER_INT,
	E_RACE_PLAYER_WORLD
}

#define RACE_POS_DONE 0x80000000

enum E_RACE_POS
{
	E_RACE_POS_CP,
	Float:E_RACE_POS_TOGO
}

_Y_RACES_STATIC stock
	PlayerArray:YSI_g_sRacers[MAX_RACES]<MAX_PLAYERS>,
	YSI_g_sRaceData[MAX_RACES][E_RACE],
	Float:YSI_g_sRaceCheckpoints[MAX_RACE_CHECKPOINTS][3],
	YSI_g_sPlayerRace[MAX_PLAYERS][E_RACE_PLAYER],
	Float:YSI_g_sRaceStarts[MAX_RACES][MAX_RACE_STARTS][4],
	YSI_g_sCPIndex,
	Iterator:YSI_g_sRacePeople[MAX_RACES]<MAX_PLAYERS>;

forward Race_Countdown(race, time);
forward Race_Timeout(playerid);

loadtext core[ysi_race];

/*-------------------------------------------------------------------------*//**
 * <param name="from">Which slot to start shifting up.</param>
 * <param name="add">How to adjust the slots.</param>
 * Notes:
 *  Find all races whose checkpoint blocks start above the current index and
 *  increment them.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC stock RaceArray_IndexShift(from, add)
{
	for (new i = 0; i != MAX_RACES; ++i)
	{
		if (YSI_g_sRaceData[i][E_RACE_CP_START] >= from) YSI_g_sRaceData[i][E_RACE_CP_START] += add;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="from">Which slot to start shifting up.</param>
 * <param name="end">Slot to end the shifting on.</param>
 * <param name="to">Slot to shift to.</param>
 * Notes:
 *  Shifts checkpoints up in the main array to make room for new ones.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC stock RaceArray_Shift(from, &end, to)
{
	// Fast version.
	end -= from;
	if (end + to >= MAX_RACE_CHECKPOINTS)
	{
		return false;
	}
	memcpy(_:YSI_g_sRaceCheckpoints[to], _:YSI_g_sRaceCheckpoints[from], 0, end * 4 * 3, end * 3);
	//++to;
	end += to;
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Slot to add to.</param>
 * <param name="x">Position data.</param>
 * <param name="y">Position data.</param>
 * <param name="z">Position data.</param>
 * Notes:
 *  Adds a new checkpoint to the checkpoints array.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC stock RaceArray_Add(slot, Float:x, Float:y, Float:z)
{
	if (slot < YSI_g_sCPIndex)
	{
		if (!RaceArray_Shift(slot, YSI_g_sCPIndex, slot + 1)) return false;
		RaceArray_IndexShift(slot, 1);
	}
	YSI_g_sRaceCheckpoints[slot][0] = x;
	YSI_g_sRaceCheckpoints[slot][1] = y;
	YSI_g_sRaceCheckpoints[slot][2] = z;
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to check.</param>
 * Notes:
 *  Checks a race is active.
 *//*------------------------------------------------------------------------**/

P:D(bool:Race__IsActive(raceid));
#define Race__IsActive(%1) \
	(YSI_g_sRaceData[(%1)][E_RACE_FLAGS] & e_RACE_FLAGS_ACTIVE)

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to check.</param>
 * Notes:
 *  Checks an id is valid and active.
 *//*------------------------------------------------------------------------**/

P:D(bool:Race_IsValid(raceid));
#define Race_IsValid(%1) \
	(0 <= (%1) < MAX_RACES && Race__IsActive((%1)))

/*-------------------------------------------------------------------------*//**
 * <param name="laps">Number of laps to race for.</param>
 * <param name="entry">Cost of entry.</param>
 * <param name="countdown">Time to count down from for start.</param>
 * <param name="arial">Use arial checkpoints instead.</param>
 * <param name="fixedPrize">Set prize amounts manually.</param>
 * <param name="exitTime">Time allowed out a vehicle before fail.</param>
 * <param name="interior">The interior of the race.</param>
 * <param name="world">The world of the race.</param>
 * <param name="restart">Don't destroy the race on completion.</param>
 * Notes:
 *  Disables default group settings when groups are used.
 *//*------------------------------------------------------------------------**/

stock Races_SetupGroups() <YSI_has_groups:n>
{
}

stock Races_SetupGroups() <>
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="laps">Number of laps to race for.</param>
 * <param name="entry">Cost of entry.</param>
 * <param name="countdown">Time to count down from for start.</param>
 * <param name="arial">Use arial checkpoints instead.</param>
 * <param name="fixedPrize">Set prize amounts manually.</param>
 * <param name="exitTime">Time allowed out a vehicle before fail.</param>
 * <param name="interior">The interior of the race.</param>
 * <param name="world">The world of the race.</param>
 * <param name="restart">Don't destroy the race on completion.</param>
 * <returns>raceid - ID of the race for reference or -1.</returns>
 * Notes:
 *  Finds an empty slot and sets the race up for use.  All
 *  parameters are optional and can be set separately aswell.
 *//*------------------------------------------------------------------------**/

FOREIGN__ _Race_Create(l,e,c,a,f,x,i,w,r);

stock Race_Create(laps = 0, entry = 0, countdown = 3, bool:arial = false, bool:fixedPrize = true, exitTime = 0, interior = 0, world = 0, bool:restart = false)
{
	return _Race_Create(laps, entry, countdown, _:arial, _:fixedPrize, exitTime, interior, world, _:restart);
}

GLOBAL__ _Race_Create(l,e,c,a,f,x,i,w,r)
{
	new
		raceid;
	for (raceid = 0; raceid < MAX_RACES; raceid++) if (!Race__IsActive(raceid)) break;
	if (raceid == MAX_RACES) return NO_RACE;
	YSI_g_sRaceData[raceid][E_RACE_FLAGS] = e_RACE_FLAGS_ACTIVE |
		(f ? e_RACE_FLAGS_NONE    : e_RACE_FLAGS_REL_WIN) |
		(a ? e_RACE_FLAGS_ARIAL   : e_RACE_FLAGS_NONE   ) |
		(r ? e_RACE_FLAGS_RESTART : e_RACE_FLAGS_NONE   ) |
		(e_RACE_FLAGS:x & e_RACE_FLAGS_EXIT_TIME);
	// 
	// Old functions.
	// 
	//Race_SetLaps(raceid, l);
	YSI_g_sRaceData[raceid][E_RACE_LAPS] = l;
	//Race_SetEntry(raceid, e);
	YSI_g_sRaceData[raceid][E_RACE_ENTRY] = e;
	if (f)
	{
		//for (new p = 1; p <= MAX_RACE_WINNERS; p++) Race_SetPrize(raceid, (MAX_RACE_WINNERS + 1) - p, e * p);
		for (new p = 1; p <= MAX_RACE_WINNERS; p++) YSI_g_sRaceData[raceid][E_RACE_PRIZES][MAX_RACE_WINNERS - p] = e * p;
		//Race_SetFixedWin(raceid, _:f);
	}
	//Race_SetArial(raceid, _:a);
	//Race_SetActive(raceid, 1);
	//Race_SetCountdown(raceid, c);
	YSI_g_sRaceData[raceid][E_RACE_COUNTDOWN] = c;
	//Race_SetExitTime(raceid, x);
	//Race_SetInterior(raceid, i);
	YSI_g_sRaceData[raceid][E_RACE_INT] = i;
	//Race_SetWorld(raceid, w);
	YSI_g_sRaceData[raceid][E_RACE_VW] = w;
	//Race_SetRestart(raceid, _:r);
	// 
	// Remainder.
	// 
	YSI_g_sRaceData[raceid][E_RACE_CHECKPOINTS] = 0;
	YSI_g_sRaceData[raceid][E_RACE_RACER_COUNT] = 0;
	YSI_g_sRaceData[raceid][E_RACE_FINISHED] = 0;
	YSI_g_sRaceData[raceid][E_RACE_RACER_MAX] = 0;
	PA_Init(YSI_g_sRacers[raceid]);
	Iter_Clear(YSI_g_sRacePeople[raceid]);
	YSI_g_sRaceData[raceid][E_RACE_CP_START] = YSI_g_sCPIndex;
	NO_GROUPS<Race>(raceid)
	{
	}
	return raceid;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Race to destroy.</param>
 * <param name="refund">Should entrants get their money back?</param>
 * Notes:
 *  Called whenever a player leaves the race, checks the
 *  number of remaining racers and if none ends the race.
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:_Race_Destroy(slot, refund);

stock Race_Destroy(slot, bool:refund = false)
{
	_Race_Destroy(slot, _:refund);
}

GLOBAL__ void:_Race_Destroy(slot, refund)
{
	if (Race_IsValid(slot))
	{
		if (YSI_g_sRaceData[slot][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED)
		{
			FOREACH__ (new i : Player)
			{
				if (PA_Get(YSI_g_sRacers[slot], i))
				{
					DisablePlayerRaceCheckpoint(i);
					Race_PlayerDone(i);
				}
			}
		}
		else
		{
			FOREACH__ (new i : Player)
			{
				if (PA_Get(YSI_g_sRacers[slot], i))
				{
					_Race_PlayerLeave(i, refund);
				}
			}
		}
		YSI_g_sRaceData[slot][E_RACE_RACER_COUNT] = 0;
		YSI_g_sRaceData[slot][E_RACE_FLAGS] = e_RACE_FLAGS:0;
		new
			count = YSI_g_sRaceData[slot][E_RACE_CHECKPOINTS],
			start = YSI_g_sRaceData[slot][E_RACE_CP_START];
		RaceArray_Shift(start + count, YSI_g_sCPIndex, start);
		RaceArray_IndexShift(start, -count);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to add to.</param>
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <returns>position or -1.</returns>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_AddCheckpoint(raceid, Float:x, Float:y, Float:z)
{
	if (!Race_IsValid(raceid)) return RACE_NO_CHECKPOINT;
	new
		count = YSI_g_sRaceData[raceid][E_RACE_CHECKPOINTS];
	RaceArray_Add(YSI_g_sRaceData[raceid][E_RACE_CP_START] + count, x, y, z);
	YSI_g_sRaceData[raceid][E_RACE_CHECKPOINTS]++;
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to add to.</param>
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <param name="a">Angle.</param>
 * <returns>position or -1.</returns>
 * Notes:
 *  Adds a starting point to a race and increases the max
 *  number of racers for the race.
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_AddStart(raceid, Float:x, Float:y, Float:z, Float:a)
{
	if (!Race_IsValid(raceid)) return RACE_NO_CHECKPOINT;
	new
		count = YSI_g_sRaceData[raceid][E_RACE_RACER_MAX];
	if (count >= MAX_RACE_STARTS) return RACE_NO_CHECKPOINT;
	YSI_g_sRaceStarts[raceid][count][0] = x;
	YSI_g_sRaceStarts[raceid][count][1] = y;
	YSI_g_sRaceStarts[raceid][count][2] = z;
	YSI_g_sRaceStarts[raceid][count][3] = a;
	YSI_g_sRaceData[raceid][E_RACE_RACER_MAX]++;
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="set">1/0.</param>
 * Notes:
 *  Sets wether or not a race has fixed prizes for the
 *  winners.  If not the prizes are calculated at race start
 *  based on the number of entrants and the entry fee.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetFixedWin(raceid, set)
{
	if (!Race_IsValid(raceid)) return;
	if (set) YSI_g_sRaceData[raceid][E_RACE_FLAGS] &= ~e_RACE_FLAGS_REL_WIN;
	else YSI_g_sRaceData[raceid][E_RACE_FLAGS] |= e_RACE_FLAGS_REL_WIN;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="set">1/0.</param>
 * Notes:
 *  Sets wether or not a race is destroyed after completion.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetRestart(raceid, set)
{
	if (!Race_IsValid(raceid)) return;
	if (set) YSI_g_sRaceData[raceid][E_RACE_FLAGS] |= e_RACE_FLAGS_RESTART;
	else YSI_g_sRaceData[raceid][E_RACE_FLAGS] &= ~e_RACE_FLAGS_RESTART;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="set">1/0.</param>
 * Notes:
 *  Toggles the use of arial checkpoints.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetArial(raceid, set)
{
	if (!Race_IsValid(raceid)) return;
	if (set) YSI_g_sRaceData[raceid][E_RACE_FLAGS] |= e_RACE_FLAGS_ARIAL;
	else YSI_g_sRaceData[raceid][E_RACE_FLAGS] &= ~e_RACE_FLAGS_ARIAL;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="set">1/0.</param>
 * Notes:
 *  Activates the race for entry and use.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC stock Race_SetActive(raceid, set)
{
	if (!Race_IsValid(raceid)) return;
	if (set) YSI_g_sRaceData[raceid][E_RACE_FLAGS] |= e_RACE_FLAGS_ACTIVE;
	else YSI_g_sRaceData[raceid][E_RACE_FLAGS] &= ~e_RACE_FLAGS_ACTIVE;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="countdown">Number to count down from.</param>
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetCountdown(raceid, countdown)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_COUNTDOWN] = countdown;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="interior">Interior where race is located.</param>
 * Notes:
 *  AFAIK you can't drive between interiors so all the
 *  checkpoints must be located in the same interior.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetInterior(raceid, interior)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_INT] = interior;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="world">World to run race in.</param>
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetWorld(raceid, world)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_VW] = world;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="position">Winning position to set for/.</param>
 * <param name="amount">Amount for that position to win.</param>
 * Notes:
 *  If this is used after the race has started it will over-
 *  write prizes set by relative winnings.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetPrize(raceid, position, amount)
{
	if (!Race_IsValid(raceid) || position >= MAX_RACE_WINNERS) return;
	YSI_g_sRaceData[raceid][E_RACE_PRIZES][position - 1] = amount;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="time">Time to set.</param>
 * Notes:
 *  Sets the time you are allowed out a vehicle before you
 *  fail the race.  0 means a vehicle exit is an instant fail.
 *
 *  Useful for long races where cars may well be destroyed.
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetExitTime(raceid, time)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_FLAGS] = (YSI_g_sRaceData[raceid][E_RACE_FLAGS] & (~e_RACE_FLAGS_EXIT_TIME)) | (e_RACE_FLAGS:time & e_RACE_FLAGS_EXIT_TIME);
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to check.</param>
 * Notes:
 *  Wrapper for Race_IsValid.
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_IsActive(raceid)
{
	return Race_IsValid(raceid);
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="laps">Number of laps to set.</param>
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetLaps(raceid, laps)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_LAPS] = laps;
}

/*-------------------------------------------------------------------------*//**
 * <param name="raceid">Race to set for.</param>
 * <param name="cost">Cost of entry to the race.</param>
 *//*------------------------------------------------------------------------**/

GLOBAL__ void:Race_SetEntry(raceid, cost)
{
	if (!Race_IsValid(raceid)) return;
	YSI_g_sRaceData[raceid][E_RACE_ENTRY] = cost;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player dropping out.</param>
 * Notes:
 *  Called when a player exits their vehicle.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_Dropout(playerid)
{
	SetTimerEx("Race_Timeout", (YSI_g_sRaceData[(YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE])][E_RACE_FLAGS] & e_RACE_FLAGS_EXIT_TIME), 0, "i", playerid);
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] |= RACE_PLAYER_OUT;
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TOUT] = GetTickCount();
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player rejoining.</param>
 * Notes:
 *  Called when a player gets in a new vehicle if not timmed
 *  out..
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_Rejoin(playerid)
{
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] &= ~RACE_PLAYER_OUT;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * Notes:
 *  Called from Race_Dropout after the race's exit time.  If
 *  the player still isn't in a vehicle (set by Race_Rejoin) the
 *  player fails the race.
 *//*------------------------------------------------------------------------**/

public Race_Timeout(playerid)
{
	if (YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] & RACE_PLAYER_OUT) Race_Exit(playerid);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left.</param>
 * Notes:
 *  Called when a player leaves a race prematurly.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_Exit(playerid)
{
	DisablePlayerRaceCheckpoint(playerid);
	new
		slot = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	Race_PlayerDone(playerid);
	CallRemoteFunction("OnPlayerExitRace", "ii", playerid, slot);
	Race_CheckEnd(slot);
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Race to check.</param>
 * Notes:
 *  Called whenever a player leaves the race, checks the
 *  number of remaining racers and if none ends the race.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_CheckEnd(slot)
{
	// This shouldn't be here...
	//YSI_g_sRaceData[slot][E_RACE_RACER_COUNT]--;
	if (!(--YSI_g_sRaceData[slot][E_RACE_RACER_COUNT]))
	{
		CallRemoteFunction("OnRaceEnd", "i", slot);
		if (YSI_g_sRaceData[slot][E_RACE_FLAGS] & e_RACE_FLAGS_RESTART)
		{
			YSI_g_sRaceData[slot][E_RACE_FLAGS] &= ~e_RACE_FLAGS_STARTED;
			YSI_g_sRaceData[slot][E_RACE_FINISHED] = 0;
			new
				count = YSI_g_sRaceData[slot][E_RACE_CHECKPOINTS],
				start = YSI_g_sRaceData[slot][E_RACE_CP_START];
			RaceArray_Shift(start + count, YSI_g_sCPIndex, start);
			RaceArray_IndexShift(start, -count);
			// Reset groups.
			NO_GROUPS<Race>(slot)
			{
			}
		}
		else
		{
			YSI_g_sRaceData[slot][E_RACE_FLAGS] = e_RACE_FLAGS:0;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player done.</param>
 * Notes:
 *  Generic cleanup for anyone who has left a race.  Sets
 *  the player back to their old position and sets a few other
 *  variables.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_PlayerDone(playerid)
{
	new
		race = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] = NO_RACE;
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TIME] = GetTickCount() - YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TIME];
	#if defined RACE_POSITION
		YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_POSITION] = 0;
	#endif
	if (Race_IsValid(race))
	{
		PA_Set(YSI_g_sRacers[race], playerid, false);
		Iter_Remove(YSI_g_sRacePeople[race], playerid);
		if (IsPlayerConnected(playerid))
		{
			//SetPlayerPos(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_X], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Y], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Z]);
			//SetPlayerFacingAngle(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_A]);
			new
				vehicleid;
			if ((vehicleid = GetPlayerVehicleID(playerid)))
			{
				SetVehiclePos(vehicleid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_X], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Y], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Z]);
				SetVehicleZAngle(vehicleid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_A]);
				LinkVehicleToInterior(vehicleid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_INT]);
				SetVehicleVirtualWorld(vehicleid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_WORLD]);
			}
			else
			{
				SetPlayerPos(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_X], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Y], YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_Z]);
				SetPlayerFacingAngle(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_A]);
			}
			SetPlayerInterior(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_INT]);
			SetPlayerVirtualWorld(playerid, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_WORLD]);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get time of.</param>
 * <returns>The time a player has been out a vehicle.</returns>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_GetPlayerExitedTime(playerid)
{
	return GetTickCount() - YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TOUT];
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to add.</param>
 * <param name="race">Race to add to.</param>
 * Notes:
 *  Checks if a player is valid to join a race and if the race
 *  is valid to be joined to and if so adds them to it.
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_PlayerJoin(playerid, race)
{
	if (YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] != NO_RACE ||
		!Race_IsValid(race)) return 0;
	new
		e_RACE_FLAGS:flags = YSI_g_sRaceData[race][E_RACE_FLAGS];
	if ((flags & e_RACE_FLAGS_STARTED) ||
		YSI_g_sRaceData[race][E_RACE_RACER_COUNT] >= YSI_g_sRaceData[race][E_RACE_RACER_MAX] ||
		GetPlayerMoney(playerid) < YSI_g_sRaceData[race][E_RACE_ENTRY]) return 0;
	GivePlayerMoney(playerid, 0 - YSI_g_sRaceData[race][E_RACE_ENTRY]);
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] = race;
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_LAP] = 0;
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP] = 0;
	PA_Set(YSI_g_sRacers[race], playerid, true);
	++YSI_g_sRaceData[race][E_RACE_RACER_COUNT];
	Iter_Add(YSI_g_sRacePeople[race], playerid);
	#if defined RACE_POSITION
		YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_POSITION] = 0;
	#endif
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to leave the race.</param>
 * <param name="refund">Wether or not to give them their entry fee back.</param>
 * Notes:
 *  Called if a player leaves a race before the race has
 *  started.
 *//*------------------------------------------------------------------------**/

FOREIGN__ _Race_PlayerLeave(playerid, refund);

stock Race_PlayerLeave(playerid, bool:refund = false)
{
	return _Race_PlayerLeave(playerid, _:refund);
}

GLOBAL__ _Race_PlayerLeave(playerid, refund)
{
	new
		race = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	if (!Race_IsValid(race) || YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED) return 0;
	if (refund) GivePlayerMoney(playerid, YSI_g_sRaceData[race][E_RACE_ENTRY]);
	YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE] = NO_RACE;
	PA_Set(YSI_g_sRacers[race], playerid, false);
	--YSI_g_sRaceData[race][E_RACE_RACER_COUNT];
	Iter_Remove(YSI_g_sRacePeople[race], playerid);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who finished the race.</param>
 * Notes:
 *  Called when a player completes a race.
 *//*------------------------------------------------------------------------**/

_Y_RACES_STATIC Race_Finish(playerid)
{
	new
		slot = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE],
		winners = YSI_g_sRaceData[slot][E_RACE_FINISHED];
	YSI_g_sRaceData[slot][E_RACE_FINISHED]++;
	Race_PlayerDone(playerid);
	new
		prize;
	if (winners < MAX_RACE_WINNERS) prize = YSI_g_sRaceData[slot][E_RACE_PRIZES][winners];
	GivePlayerMoney(playerid, prize);
	CallRemoteFunction("OnPlayerFinishRace", "iiiii", playerid, slot, winners + 1, prize, YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TIME]);
	Race_CheckEnd(slot);
}

/*-------------------------------------------------------------------------*//**
 * <param name="race">Race to start.</param>
 * Notes:
 *  Loops through all players who have entered the race and
 *  moves them to their respective start points.  If the prize
 *  is set as relative the prizes are calculated here based on
 *  number of entrants, number of possible winners and entry
 *  fee.
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_Start(race)
{
	if (!Race_IsValid(race)) return 0;
	new
		bool:exited = true,
		j;
	for (new i = Iter_First(YSI_g_sRacePeople[race]), k; (k = Iter_Next(YSI_g_sRacePeople[race], i)), i != Iter_End(YSI_g_sRacePeople[race]); i = k)
	//FOREACH__ (new i : YSI_g_sRacePeople[race])
	{
		new
			vehicleid;
		GetPlayerPos(i, YSI_g_sPlayerRace[i][E_RACE_PLAYER_X], YSI_g_sPlayerRace[i][E_RACE_PLAYER_Y], YSI_g_sPlayerRace[i][E_RACE_PLAYER_Z]);
		if ((vehicleid = GetPlayerVehicleID(i)))
		{
			GetPlayerFacingAngle(i, YSI_g_sPlayerRace[i][E_RACE_PLAYER_A]);
			YSI_g_sPlayerRace[i][E_RACE_PLAYER_INT] = GetPlayerInterior(i);
			YSI_g_sPlayerRace[i][E_RACE_PLAYER_WORLD] = GetPlayerVirtualWorld(i);
			LinkVehicleToInterior(vehicleid, YSI_g_sRaceData[race][E_RACE_INT]);
			SetVehicleVirtualWorld(vehicleid, YSI_g_sRaceData[race][E_RACE_VW]);
			SetPlayerInterior(i, YSI_g_sRaceData[race][E_RACE_INT]);
			SetPlayerVirtualWorld(i, YSI_g_sRaceData[race][E_RACE_VW]);
			SetVehiclePos(vehicleid, YSI_g_sRaceStarts[race][j % MAX_RACE_STARTS][0], YSI_g_sRaceStarts[race][j % MAX_RACE_STARTS][1], YSI_g_sRaceStarts[race][j % MAX_RACE_STARTS][2]);
			SetVehicleZAngle(vehicleid, YSI_g_sRaceStarts[race][j % MAX_RACE_STARTS][3]);
			SetCameraBehindPlayer(i);
			TogglePlayerControllable(i, 0);
			++j;
		}
		else
		{
			exited = false;
			Race_Exit(i);
		}
	}
	if (j)
	{
		YSI_g_sRaceData[race][E_RACE_FLAGS] |= e_RACE_FLAGS_STARTED;
		Race_Countdown(race, YSI_g_sRaceData[race][E_RACE_COUNTDOWN]);
		if (YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_REL_WIN)
		{
			new
				prize;
			if (j < MAX_RACE_WINNERS) prize = ((j * j) + j) / 2;
			else prize = (MAX_RACE_WINNERS * (MAX_RACE_WINNERS + 1)) / 2;
			new
				count = (YSI_g_sRaceData[race][E_RACE_ENTRY] * j) / prize;
			for (new i = 0; i < MAX_RACE_WINNERS; i++) YSI_g_sRaceData[race][E_RACE_PRIZES][i] = (MAX_RACE_WINNERS - i) * count;
		}
		return 1;
	}
	else if (exited)
	{
		// No players were in to begin with.
		YSI_g_sRaceData[race][E_RACE_RACER_COUNT] = 1;
		Race_CheckEnd(race);
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="race">Race to do countdown for.</param>
 * <param name="time">Seconds remaining.</param>
 *//*------------------------------------------------------------------------**/

public Race_Countdown(race, time)
{
	if (!(YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_ACTIVE)) return;
	if (time)
	{
		Text_Send(YSI_g_sRacers[race], $YSI_RACE_COUNTDOWN, time);
		SetTimerEx("Race_Countdown", 1000, 0, "ii", race, time - 1);
	}
	else
	{
		Text_Send(YSI_g_sRacers[race], $YSI_RACE_GO);
		new
			startTime = GetTickCount(),
			vehicleid,
			pos;
		//for (new i = Iter_First(YSI_g_sRacePeople[race]), j; j = Iter_Next(YSI_g_sRacePeople[race], i), i != Iter_End(YSI_g_sRacePeople[race]); i = j)
		FOREACH__ (new i : YSI_g_sRacePeople[race])
		{
			if ((vehicleid = GetPlayerVehicleID(i)))
			{
				TogglePlayerControllable(i, 1);
				Race_DoEnterRaceCP(i);
				SetVehiclePos(vehicleid, YSI_g_sRaceStarts[race][pos % MAX_RACE_STARTS][0], YSI_g_sRaceStarts[race][pos % MAX_RACE_STARTS][1], YSI_g_sRaceStarts[race][pos % MAX_RACE_STARTS][2] + 0.1);
				SetVehicleZAngle(vehicleid, YSI_g_sRaceStarts[race][pos % MAX_RACE_STARTS][3]);
				YSI_g_sPlayerRace[i][E_RACE_PLAYER_TIME] = startTime;
				pos++;
			}
			else Race_Exit(i);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who entered.</param>
 * Sets up important variables
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnScriptInit()
{
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		YSI_g_sPlayerRace[i][E_RACE_PLAYER_RACE] = NO_RACE;
	}
	Iter_Init(YSI_g_sRacePeople);
	Races_SetupGroups();
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who entered.</param>
 * Checks a players position in the race and displays the corresponding next
 * checkpoint or calls Race_Finish.
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerEnterRaceCP(playerid)
{
	return Race_DoEnterRaceCP(playerid);
}

_Y_RACES_STATIC Race_DoEnterRaceCP(playerid)
{
	new
		race = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	if (race & RACE_PLAYER_OUT) return 1;
	// Race_IsValid check mixed with running check.
	if ((0 <= race < MAX_RACES) && (YSI_g_sRaceData[race][E_RACE_FLAGS] & (e_RACE_FLAGS_ACTIVE | e_RACE_FLAGS_STARTED) == (e_RACE_FLAGS_ACTIVE | e_RACE_FLAGS_STARTED)))
	{
		DisablePlayerRaceCheckpoint(playerid);
		new
			start = YSI_g_sRaceData[race][E_RACE_CP_START],
			check = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP],
			checks = YSI_g_sRaceData[race][E_RACE_CHECKPOINTS],
			laps = YSI_g_sRaceData[race][E_RACE_LAPS],
			type = _:(YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_ARIAL);
		if (laps)
		{
			new
				lap = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_LAP];
			if (lap == laps)
			{
				Race_Finish(playerid);
				return 1;
			}
			else
			{
				if (check + 1 == checks)
				{
					if (lap + 1 == laps)
					{
						SetPlayerRaceCheckpoint(playerid, type ? 4 : 1, YSI_g_sRaceCheckpoints[start][0], YSI_g_sRaceCheckpoints[start][1], YSI_g_sRaceCheckpoints[start][2], 0.0, 0.0, 0.0, 5.0);
					}
					else
					{
						check += start;
						SetPlayerRaceCheckpoint(playerid, type ? 3 : 0, YSI_g_sRaceCheckpoints[check][0], YSI_g_sRaceCheckpoints[check][1], YSI_g_sRaceCheckpoints[check][2], YSI_g_sRaceCheckpoints[start][0], YSI_g_sRaceCheckpoints[start][1], YSI_g_sRaceCheckpoints[start][2], 5.0);
					}
					YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP] = 0;
					++YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_LAP];
					return 1;
				}
				else
				{
					check += start;
					SetPlayerRaceCheckpoint(playerid, type ? 3 : 0, YSI_g_sRaceCheckpoints[check][0], YSI_g_sRaceCheckpoints[check][1], YSI_g_sRaceCheckpoints[check][2], YSI_g_sRaceCheckpoints[check + 1][0], YSI_g_sRaceCheckpoints[check + 1][1], YSI_g_sRaceCheckpoints[check + 1][2], 5.0);
					++YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP];
					return 1;
				}
			}
		}
		else
		{
			switch (checks - check)
			{
				case 0:
				{
					Race_Finish(playerid);
				}
				case 1:
				{
					check += start;
					SetPlayerRaceCheckpoint(playerid, type ? 4 : 1, YSI_g_sRaceCheckpoints[check][0], YSI_g_sRaceCheckpoints[check][1], YSI_g_sRaceCheckpoints[check][2], 0.0, 0.0, 0.0, 5.0);
				}
				default:
				{
					check += start;
					SetPlayerRaceCheckpoint(playerid, type ? 3 : 0, YSI_g_sRaceCheckpoints[check][0], YSI_g_sRaceCheckpoints[check][1], YSI_g_sRaceCheckpoints[check][2], YSI_g_sRaceCheckpoints[check + 1][0], YSI_g_sRaceCheckpoints[check + 1][1], YSI_g_sRaceCheckpoints[check + 1][2], 5.0);
				}
			}
			++YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP];
			return 1;
		}
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who's state changed.</param>
 * <param name="newstate">Their new state.</param>
 * <param name="oldstate">Their last state.</param>
 * Notes:
 *  Processes a players vehicle exit or entry mid race and
 *  calls the relevant functions.
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerStateChange(playerid, newstate, oldstate)
{
	new
		race = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	if (!Race_IsValid(race) || !(YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED)) return 0;
	if (oldstate == PLAYER_STATE_DRIVER)
	{
		if (!(YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_EXIT_TIME) || newstate != PLAYER_STATE_EXIT_VEHICLE) Race_Exit(playerid);
		else Race_Dropout(playerid);
	}
	else if (newstate == PLAYER_STATE_DRIVER) Race_Rejoin(playerid);
	else if (newstate != PLAYER_STATE_ONFOOT && newstate != PLAYER_STATE_ENTER_VEHICLE_DRIVER) Race_Exit(playerid);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left.</param>
 * <param name="reason">Why they left.</param>
 * Notes:
 *  Similar to the Race_OnPlayerStateChange function but
 *  instantly exits them from the race as they're not there
 *  anymore.
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerDisconnect(playerid, reason)
{
	new
		race = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	if (!Race_IsValid(race)) return 0;
	if (YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED)
	{
		Race_Exit(playerid);
	}
	else
	{
		Race_PlayerLeave(playerid);
	}
	return 1;
	#pragma unused reason
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who joined.</param>
 * Just a fix for IsPlayerInRaceCheckpoint.
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerConnect(playerid)
{
	DisablePlayerRaceCheckpoint(playerid);
	return 1;
}

#if defined RACE_POSITION

/*-------------------------------------------------------------------------*//**
 * If compiled with RACE_POSITION this function will keep track of all player's
 * positions in their race.  It uses current lap, checkpoint and distance from next
 * checkpoint to approximate position.
 *
 * Note: If a race doubles back between two checkpoints you may be closer than
 * another player thus show as a higher position when you are infact behind them.
 *//*------------------------------------------------------------------------**/

#if YSIM_HAS_MASTER && (_YSIM_IS_CLIENT || _YSIM_IS_STUB)
	stock Race_Loop()
#else
	task Race_Loop[500 / MAX_RACES]()
#endif
	{
		static
			race = -1;
		// Process a different race every call.
		race = (race + 1) % MAX_RACES;
		static
			racePos[MAX_PLAYERS][E_RACE_POS];
		if (Race__IsActive(race))
		{
			new
				start = YSI_g_sRaceData[race][E_RACE_CP_START],
				lap,
				cp = Iter_Count(YSI_g_sRacePeople[race]),
				Float:togo,
				pos;
			if (!cp)
			{
				return;
			}
			FOREACH__ (new playerid : YSI_g_sRacePeople[race])
			{
				lap = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_LAP],
				cp = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_CP] + start;
				static
					Float:x,
					Float:y,
					Float:z;
				GetPlayerPos(playerid, x, y, z);
				// Get the player's (squared) distance to the next checkpoint.
				x -= YSI_g_sRaceCheckpoints[cp][0];
				y -= YSI_g_sRaceCheckpoints[cp][1];
				z -= YSI_g_sRaceCheckpoints[cp][2];
				togo = ((x * x) + (y * y) + (z * z)),
				pos = 1;
				racePos[playerid][E_RACE_POS_CP] = cp;
				racePos[playerid][E_RACE_POS_TOGO] = togo;
				for (new i = Iter_Begin(YSI_g_sRacePeople[race]); (i = Iter_Next(YSI_g_sRacePeople[race], i)) != playerid; )
				{
					// This checks "checkpoint + start", but both players have
					// that offset so it is fine.
					if (YSI_g_sPlayerRace[i][E_RACE_PLAYER_LAP] > lap ||
					   (YSI_g_sPlayerRace[i][E_RACE_PLAYER_LAP] == lap &&
						   (racePos[i][E_RACE_POS_CP] > cp ||
						   (racePos[i][E_RACE_POS_CP] == cp && racePos[i][E_RACE_POS_TOGO] < togo)))) ++pos;
					// This player is on a higher lap, or on a higher
					// checkpoint, or less distance from their next checkpoint.
					else ++YSI_g_sPlayerRace[i][E_RACE_PLAYER_POSITION];
				}
				YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_POSITION] = pos;
			}
			#if defined RACE_SHOW_POS
				// Race time.
				lap = Race_GetPlayerRaceTime(Iter_First(YSI_g_sRacePeople[race])) / 1000;
				// Racer count.
				cp = Iter_Count(YSI_g_sRacePeople[race]);
				new
					time[8],
					th[3];
				format(time, sizeof (time), "%d:%02d", lap / 60, lap % 60);
				FOREACH__ (new playerid : YSI_g_sRacePeople[race])
				{
					pos = YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_POSITION];
					switch (pos % 20)
					{
						case 1: th = "ST";
						case 2: th = "ND";
						case 3: th = "RD";
						case 11: if (pos % 100 > 20) th = "TH"; else th = "ST";
						case 12: if (pos % 100 > 20) th = "TH"; else th = "ND";
						case 13: if (pos % 100 > 20) th = "TH"; else th = "RD";
						default: th = "TH";
					}
					// Show the background.
					// Show the position.
					// Show the "th".
					// Show the races count.
					// Show the time.
				}
			#endif
		}
	}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get position of.</param>
 * <returns>Dynamic position in race.</returns>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_GetPlayerPosition(playerid)
{
	return YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_POSITION];
}

#endif

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get time for.</param>
 * <returns>Time in race so far.</returns>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_GetPlayerRaceTime(playerid)
{
	return GetTickCount() - YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_TIME];
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get race of.</param>
 * <returns>Player's race.</returns>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_GetPlayerRace(playerid)
{
	if (VALID_PLAYERID(playerid)) return YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE];
	return NO_RACE;
}

/*-------------------------------------------------------------------------*//**
 * <param name="race">Which race to add them to.</param>
 * <param name="playerid">Player to set in the race.</param>
 * <param name="set">Add or remove them.</param>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Race_SetPlayer(race, playerid, bool:set)
{
	if (Race_IsValid(race))
	{
		if (set)
		{
			if (!(YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED))
			{
				Race_PlayerJoin(playerid, race);
				return 1;
			}
		}
		else if (race == YSI_g_sPlayerRace[playerid][E_RACE_PLAYER_RACE])
		{
			if (YSI_g_sRaceData[race][E_RACE_FLAGS] & e_RACE_FLAGS_STARTED)
			{
				Race_Exit(playerid);
			}
			else
			{
				Race_PlayerLeave(playerid);
			}
			return 1;
		}
	}
	return 0;
}

// Called when a player finishes the race.
forward OnPlayerFinishRace(playerid, race, position, prize, time);

// Called when a player drops out of the race.
forward OnPlayerExitRace(playerid, race);

// Called when the race is over.
forward OnRaceEnd(race);