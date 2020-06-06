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

new
	g_sRaceID = 0;

TEST__ y_races_Create()
{
	g_sRaceID = Race_Create();
	ASSERT_ZE(g_sRaceID);
	Race_Destroy(g_sRaceID);
}

TEST__ y_races_Destroy()
{
	g_sRaceID = Race_Create();
	ASSERT_ZE(g_sRaceID);
	Race_Destroy(g_sRaceID);
	g_sRaceID = Race_Create();
	ASSERT_ZE(g_sRaceID);
	Race_Destroy(g_sRaceID);
}

TEST__ y_races_ArrayAdd0()
{
	for (new i = 0; i != 10; ++i)
	{
		YSI_g_sRaceCheckpoints[i][0] = i + 1;
		YSI_g_sRaceCheckpoints[i][1] = i + 1;
		YSI_g_sRaceCheckpoints[i][2] = i + 1;
	}
	YSI_g_sCPIndex = 10;
	RaceArray_Add(10, 11.0, 11.0, 11.0);
	for (new i = 0; i != 11; ++i)
	{
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][0], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][1], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][2], i + 1);
	}
	YSI_g_sCPIndex = 0;
}

TEST__ y_races_ArrayAdd1()
{
	for (new i = 0; i != 10; ++i)
	{
		YSI_g_sRaceCheckpoints[i][0] = i + 1;
		YSI_g_sRaceCheckpoints[i][1] = i + 1;
		YSI_g_sRaceCheckpoints[i][2] = i + 1;
	}
	YSI_g_sCPIndex = 10;
	RaceArray_Add(6, 22.0, 22.0, 22.0);
	for (new i = 0; i != 6; ++i)
	{
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][0], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][1], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][2], i + 1);
	}
	ASSERT_EQ(YSI_g_sRaceCheckpoints[6][0], 22.0);
	ASSERT_EQ(YSI_g_sRaceCheckpoints[6][1], 22.0);
	ASSERT_EQ(YSI_g_sRaceCheckpoints[6][2], 22.0);
	for (new i = 7; i != 11; ++i)
	{
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][0], i);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][1], i);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][2], i);
	}
	YSI_g_sCPIndex = 0;
}

TEST__ y_races_ArrayShift()
{
	new
		to = 10;
	for (new i = 0; i != 10; ++i)
	{
		YSI_g_sRaceCheckpoints[i][0] = i + 1;
		YSI_g_sRaceCheckpoints[i][1] = i + 1;
		YSI_g_sRaceCheckpoints[i][2] = i + 1;
	}
	RaceArray_Shift(5, to, 6);
	YSI_g_sRaceCheckpoints[5][0] = 66.5;
	YSI_g_sRaceCheckpoints[5][1] = 66.5;
	YSI_g_sRaceCheckpoints[5][2] = 66.5;
	ASSERT_EQ(to, 11);
	for (new i = 0; i != 5; ++i)
	{
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][0], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][1], i + 1);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][2], i + 1);
	}
	ASSERT_EQ(YSI_g_sRaceCheckpoints[5][0], 66.5);
	ASSERT_EQ(YSI_g_sRaceCheckpoints[5][1], 66.5);
	ASSERT_EQ(YSI_g_sRaceCheckpoints[5][2], 66.5);
	for (new i = 6; i != 11; ++i)
	{
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][0], i);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][1], i);
		ASSERT_EQ(YSI_g_sRaceCheckpoints[i][2], i);
		//printf("%.2f %.2f %.2f", YSI_g_sRaceCheckpoints[0][i][0], YSI_g_sRaceCheckpoints[0][i][1], YSI_g_sRaceCheckpoints[0][i][2]);
	}
}

static
	gracePos[MAX_PLAYERS][E_RACE_POS],
	YSI_g_sPlayerRace2[MAX_PLAYERS][E_RACE_PLAYER],
	Iterator:YSI_g_sRacePeople2<MAX_PLAYERS>;

static y_races_Position0(lap, cp, Float:togo, playerid)
{
	new
		pos = 1,
		opl = 0,
		opc = 0;
	for (new i = Iter_Begin(YSI_g_sRacePeople2); (i = Iter_Next(YSI_g_sRacePeople2, i)) != playerid; )
	{
		opl = YSI_g_sPlayerRace2[i][E_RACE_PLAYER_LAP];
		opc = gracePos[i][E_RACE_POS_CP];
		// This checks "checkpoint + start", but both players have that
		// offset so it is fine.
		if (opl > lap ||
		   (opl == lap &&
			   (opc > cp ||
			   (opc == cp && gracePos[i][E_RACE_POS_TOGO] < togo)))) ++pos;
		else ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
	}
	return pos;
}

static y_races_Position1(lap, cp, Float:togo, playerid)
{
	new
		pos = 1;
	for (new i = Iter_Begin(YSI_g_sRacePeople2); (i = Iter_Next(YSI_g_sRacePeople2, i)) != playerid; )
	{
		if (YSI_g_sPlayerRace2[i][E_RACE_PLAYER_LAP] > lap ||
			  (YSI_g_sPlayerRace2[i][E_RACE_PLAYER_LAP] == lap &&
				(gracePos[i][E_RACE_POS_CP] > cp ||
				   (gracePos[i][E_RACE_POS_CP] == cp && gracePos[i][E_RACE_POS_TOGO] < togo)))) ++pos;
		else ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
	}
	return pos;
}

static y_races_Position2(lap, cp, Float:togo, playerid)
{
	new
		pos = 1;
	for (new i = Iter_Begin(YSI_g_sRacePeople2); (i = Iter_Next(YSI_g_sRacePeople2, i)) != playerid; )
	{
		switch (floatcmp(YSI_g_sPlayerRace2[i][E_RACE_PLAYER_LAP], lap))
		{
			case -1: ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
			case  1: ++pos; // This player better.
			default:
			{
				switch (floatcmp(gracePos[i][E_RACE_POS_CP], cp))
				{
					case -1: ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
					case  1: ++pos;
					default:
					{
						// Backwards as bigger is now worse.
						switch (floatcmp(togo, gracePos[i][E_RACE_POS_TOGO]))
						{
							case -1: ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
							case  1: ++pos;
							// Default do nothing (leave them in the same position).
						}
					}
				}
			}
		}
	}
	return pos;
}

static y_races_Position3(lap, cp, Float:togo, playerid)
{
	new
		pos = 1;
	for (new i = Iter_Begin(YSI_g_sRacePeople2); (i = Iter_Next(YSI_g_sRacePeople2, i)) != playerid; )
	{
		switch (floatcmp(YSI_g_sPlayerRace2[i][E_RACE_PLAYER_LAP], lap) * 3 + floatcmp(gracePos[i][E_RACE_POS_CP], cp))
		{
			case 4, 3, 2, 1: ++pos; // This player better.
			case 0: if (gracePos[i][E_RACE_POS_TOGO] < togo) ++pos; else ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION];
			default: ++YSI_g_sPlayerRace2[i][E_RACE_PLAYER_POSITION]; // Other player better.
		}
	}
	return pos;
}

static y_races_SFD0(p, l, c, Float:t, x)
{
	Iter_Add(YSI_g_sRacePeople2, p);
	gracePos[p][E_RACE_POS_CP] = c;
	gracePos[p][E_RACE_POS_TOGO] = t;
	YSI_g_sPlayerRace2[p][E_RACE_PLAYER_LAP] = l;
	YSI_g_sPlayerRace2[p][E_RACE_PLAYER_POSITION] = x;
}

static y_races_SFD()
{
	Iter_Clear(YSI_g_sRacePeople2);
	y_races_SFD0( 0,  3,  6, 10.0, 1);
	y_races_SFD0( 1,  3,  6, 20.0, 2);
	y_races_SFD0( 2,  3,  6, 30.0, 3);
	y_races_SFD0( 3,  3,  5, 10.0, 4);
	y_races_SFD0( 4,  3,  5, 20.0, 5);
	y_races_SFD0( 5,  3,  5, 30.0, 6);
	y_races_SFD0( 6,  3,  4, 10.0, 7);
	y_races_SFD0( 7,  3,  4, 20.0, 8);
	y_races_SFD0( 8,  3,  4, 30.0, 9);
	// Lap 2.
	y_races_SFD0(10,  2,  6, 10.0, 10);
	y_races_SFD0(11,  2,  6, 20.0, 11);
	y_races_SFD0(12,  2,  6, 30.0, 12);
	y_races_SFD0(13,  2,  5, 10.0, 13);
	y_races_SFD0(14,  2,  5, 20.0, 14);
	y_races_SFD0(15,  2,  5, 30.0, 15);
	y_races_SFD0(16,  2,  4, 10.0, 16);
	y_races_SFD0(17,  2,  4, 20.0, 17);
	y_races_SFD0(18,  2,  4, 30.0, 18);
	// Lap 1.
	y_races_SFD0(20,  1,  6, 10.0, 19);
	y_races_SFD0(21,  1,  6, 20.0, 20);
	y_races_SFD0(22,  1,  6, 30.0, 21);
	y_races_SFD0(23,  1,  5, 10.0, 22);
	y_races_SFD0(24,  1,  5, 20.0, 23);
	y_races_SFD0(25,  1,  5, 30.0, 24);
	y_races_SFD0(26,  1,  4, 10.0, 25);
	y_races_SFD0(27,  1,  4, 20.0, 26);
	y_races_SFD0(28,  1,  4, 30.0, 27);
	// Reference.
	y_races_SFD0(30,  2,  5, 20.0, 0);
	// Other.
	y_races_SFD0(31,  3,  6, 20.0, 0);
	y_races_SFD0(32,  3,  4, 10.0, 0);
	y_races_SFD0(33,  2,  6, 10.0, 0);
	y_races_SFD0(34,  3,  5, 30.0, 0);
	y_races_SFD0(35,  2,  4, 30.0, 0);
	y_races_SFD0(36,  1,  6, 30.0, 0);
	y_races_SFD0(37,  1,  5, 10.0, 0);
	y_races_SFD0(38,  1,  4, 20.0, 0);
}

#define Y_RACES_ASSERT(%0,%1) ASSERT(YSI_g_sPlayerRace2[%0][E_RACE_PLAYER_POSITION] == %1)

static y_races_ASSERT(pos)
{
	Iter_Clear(YSI_g_sRacePeople2);
	Y_RACES_ASSERT( 0, 1);
	Y_RACES_ASSERT( 1, 2);
	Y_RACES_ASSERT( 2, 3);
	Y_RACES_ASSERT( 3, 4);
	Y_RACES_ASSERT( 4, 5);
	Y_RACES_ASSERT( 5, 6);
	Y_RACES_ASSERT( 6, 7);
	Y_RACES_ASSERT( 7, 8);
	Y_RACES_ASSERT( 8, 9);
	//Y_RACES_ASSERT
	Y_RACES_ASSERT(10, 10);
	Y_RACES_ASSERT(11, 11);
	Y_RACES_ASSERT(12, 12);
	Y_RACES_ASSERT(13, 13);
	ASSERT(YSI_g_sPlayerRace2[14][E_RACE_PLAYER_POSITION] == 14 || YSI_g_sPlayerRace2[14][E_RACE_PLAYER_POSITION] == 15);
	Y_RACES_ASSERT(15, 16);
	Y_RACES_ASSERT(16, 17);
	Y_RACES_ASSERT(17, 18);
	Y_RACES_ASSERT(18, 19);
	//Y_RACES_ASSERT
	Y_RACES_ASSERT(20, 20);
	Y_RACES_ASSERT(21, 21);
	Y_RACES_ASSERT(22, 22);
	Y_RACES_ASSERT(23, 23);
	Y_RACES_ASSERT(24, 24);
	Y_RACES_ASSERT(25, 25);
	Y_RACES_ASSERT(26, 26);
	Y_RACES_ASSERT(27, 27);
	Y_RACES_ASSERT(28, 28);
	//Y_RACES_ASSERT
	ASSERT(pos == 14 || pos == 15);
	//Y_RACES_ASSERT(30, 0);
	//Y_RACES_ASSERT
	Y_RACES_ASSERT(31, 0);
	Y_RACES_ASSERT(32, 0);
	Y_RACES_ASSERT(33, 0);
	Y_RACES_ASSERT(34, 0);
	Y_RACES_ASSERT(35, 0);
	Y_RACES_ASSERT(36, 0);
	Y_RACES_ASSERT(37, 0);
	Y_RACES_ASSERT(38, 0);
}

TEST__ y_races_Position0()
{
	y_races_SFD();
	y_races_ASSERT(y_races_Position0(2, 5, 20.0, 30));
}

TEST__ y_races_Position1()
{
	y_races_SFD();
	y_races_ASSERT(y_races_Position1(2, 5, 20.0, 30));
}

TEST__ y_races_Position2()
{
	y_races_SFD();
	y_races_ASSERT(y_races_Position2(2, 5, 20.0, 30));
}

TEST__ y_races_Position3()
{
	y_races_SFD();
	y_races_ASSERT(y_races_Position3(2, 5, 20.0, 30));
}

//#define Profile: TEST__ 
#define Profile: static stock _ // Can't have trailing space.

Profile:y_races_Position()
{
	new
		t0 = 0,
		t1 = 0,
		t2 = 0,
		t3 = 0,
		t4 = 0;
	t0 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		y_races_SFD();
		y_races_Position0(2, 5, 20.0, 30);
	}
	t1 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		y_races_SFD();
		y_races_Position1(2, 5, 20.0, 30);
	}
	t2 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		y_races_SFD();
		y_races_Position2(2, 5, 20.0, 30);
	}
	t3 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		y_races_SFD();
		y_races_Position3(2, 5, 20.0, 30);
	}
	t4 = GetTickCount();
	printf("Times: %d %d %d %d", t1 - t0, t2 - t1, t3 - t2, t4 - t3);
}
