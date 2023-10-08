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
	Portions created by the Initial Developer are Copyright (c) 2022
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

public
	YSI_gpThirdpartyTestValud = 41,
	YSI_gpThirdpartyTestValue = 42,
	YSI_gpThirdpartyTestValuf = 43,
	YSI_gpThirdpartyTest = 44;

#pragma unused YSI_gpThirdpartyTestValud, YSI_gpThirdpartyTestValue, YSI_gpThirdpartyTestValuf, YSI_gpThirdpartyTest

@test(.group = "y_thirdpartyinclude") GetSetPubVar()
{
	//ASSERT(GetNumPubVars() > 0);
	new value;
	YSI_gpThirdpartyTestValue = 42;
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValue", value));
	ASSERT_EQ(value, 42);
	ASSERT(SetPubVar("YSI_gpThirdpartyTestValue", 101));
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValud", value));
	ASSERT_EQ(value, 41);
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValuf", value));
	ASSERT_EQ(value, 43);
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValue", value));
	ASSERT_EQ(value, 101);
}

#if defined getpubvar

@test(.group = "y_thirdpartyinclude") GetSetPubVar2()
{
	ASSERT(numpubvars() >= 3);
	YSI_gpThirdpartyTestValue = 7;
	ASSERT_EQ(setpubvar("YSI_gpThirdpartyTestValue", 42), 7);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 42);
	ASSERT_EQ(setpubvar("YSI_gpThirdpartyTestValue", 101), 42);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValud"), 41);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValuf"), 43);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 101);
	ASSERT(existpubvar("YSI_gpThirdpartyTestValue"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestValug"));
}

@test(.group = "y_thirdpartyinclude") GetSetPubVar3()
{
	YSI_gpThirdpartyTestValue = 789;
	YSI_gpThirdpartyTest = 123;
	ASSERT(existpubvar("YSI_gpThirdpartyTestValue"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestValu"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestVal"));
	ASSERT(existpubvar("YSI_gpThirdpartyTest"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestV"));
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 789);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTest"), 123);
}

#endif

@test(.group = "y_thirdpartyinclude") CallNativeByAddress()
{
	//PrintAmxHeader();
	clamp(0, 5, 6);
	new res, addr = GetNativeAddressFromName("clamp");
	//printf("Address = %08x", addr);
	res = CallNativeByAddress(addr, 10, 11, 12);
	ASSERT_EQ(res, 11);
	res = CallNativeByAddress(addr, 10, 5, 15);
	ASSERT_EQ(res, 10);
	res = CallNativeByAddress(addr, 100, 7, 9);
	ASSERT_EQ(res, 9);
	res = CallNativeByAddress(addr, 6, 6, 6);
	ASSERT_EQ(res, 6);
}

#tryinclude <md-sort\md-sort>
#tryinclude <md-sort-master\md-sort>
#tryinclude <md-sort-master\md-sort-master\md-sort>
#tryinclude "..\..\md-sort\md-sort"
#tryinclude "..\..\md-sort-master\md-sort"
#tryinclude "..\..\md-sort-master\md-sort-master\md-sort"
#tryinclude "..\..\..\md-sort\md-sort"
#tryinclude "..\..\..\md-sort-master\md-sort"
#tryinclude "..\..\..\md-sort-master\md-sort-master\md-sort"
#tryinclude "md-sort"
#tryinclude <md-sort>
#if !defined _INC_md_sort
	#error Download `github.com/oscar-broman/md-sort/archive/refs/heads/master.zip` and extract it to `include\`.
#elseif !defined SA_4limit
	#error Re-download `github.com/oscar-broman/md-sort/archive/refs/heads/master.zip` and extract it to `include\`.
#endif

@test(.group = "y_thirdpartyinclude") MDSort_1()
{
	new arr[100][2];
	for (new i = 0; i != sizeof (arr); ++i)
	{
		arr[i][0] = random(1000);
		arr[i][1] = i;
	}
	SortDeepArray(arr, 0);
	new prev = cellmin;
	for (new i = 0; i != sizeof (arr); ++i)
	{
		ASSERT_GE(arr[i][0], prev);
		prev = arr[i][0];
		ASSERT_GE(arr[i][1], 0);
		ASSERT_LT(arr[i][1], sizeof (arr));
	}
}

@test(.group = "y_thirdpartyinclude") MDSort_2()
{
	new arr[1000][2];
	for (new i = 0; i != sizeof (arr); ++i)
	{
		arr[i][0] = random(100000);
		arr[i][1] = i;
	}
	SortDeepArray(arr, 0, .order = SORT_DESC);
	new prev = cellmax;
	for (new i = 0; i != sizeof (arr); ++i)
	{
		ASSERT_LE(arr[i][0], prev);
		prev = arr[i][0];
		ASSERT_GE(arr[i][1], 0);
		ASSERT_LT(arr[i][1], sizeof (arr));
	}
}

@test(.group = "y_thirdpartyinclude") MDSort_3()
{
	for (new limit = 1; limit < 20; ++limit)
	{
		new arr[1000][2];
		for (new i = 0; i != sizeof (arr); ++i)
		{
			arr[i][0] = random(100000);
			arr[i][1] = i;
		}
		SortDeepArray(arr, 0, .limit = limit);
		for (new j = 0; j != limit; ++j)
		{
			// The first values should be in order.  Not the rest.
			new prev = arr[j][0];
			for (new i = j; i != sizeof (arr); ++i)
			{
				ASSERT_GE(arr[i][0], prev);
			}
		}
	}
}

@test(.group = "y_thirdpartyinclude") MDSort_4()
{
	for (new limit = 1; limit < 20; ++limit)
	{
		new arr[1000][2];
		for (new i = 0; i != sizeof (arr); ++i)
		{
			arr[i][0] = random(100000);
			arr[i][1] = i;
		}
		SortDeepArray(arr, 0, .limit = limit, .order = SORT_DESC);
		for (new j = 0; j != limit; ++j)
		{
			// The first values should be in order.  Not the rest.
			new prev = arr[j][0];
			for (new i = j; i != sizeof (arr); ++i)
			{
				ASSERT_LE(arr[i][0], prev);
			}
		}
	}
}

@test(.group = "y_thirdpartyinclude", .run = false) MDSort_5()
{
	new arr[100][2];
	for (new i = 0; i != sizeof (arr); ++i)
	{
		arr[i][0] = random(100);
		arr[i][1] = i;
	}
	SortDeepArray(arr, 0, .limit = 10);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[0][0], arr[1][0], arr[2][0], arr[3][0], arr[4][0], arr[5][0], arr[6][0], arr[7][0], arr[8][0], arr[9][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[10][0], arr[11][0], arr[12][0], arr[13][0], arr[14][0], arr[15][0], arr[16][0], arr[17][0], arr[18][0], arr[19][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[20][0], arr[21][0], arr[22][0], arr[23][0], arr[24][0], arr[25][0], arr[26][0], arr[27][0], arr[28][0], arr[29][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[30][0], arr[31][0], arr[32][0], arr[33][0], arr[34][0], arr[35][0], arr[36][0], arr[37][0], arr[38][0], arr[39][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[40][0], arr[41][0], arr[42][0], arr[43][0], arr[44][0], arr[45][0], arr[46][0], arr[47][0], arr[48][0], arr[49][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[50][0], arr[51][0], arr[52][0], arr[53][0], arr[54][0], arr[55][0], arr[56][0], arr[57][0], arr[58][0], arr[59][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[60][0], arr[61][0], arr[62][0], arr[63][0], arr[64][0], arr[65][0], arr[66][0], arr[67][0], arr[68][0], arr[69][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[70][0], arr[71][0], arr[72][0], arr[73][0], arr[74][0], arr[75][0], arr[76][0], arr[77][0], arr[78][0], arr[79][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[80][0], arr[81][0], arr[82][0], arr[83][0], arr[84][0], arr[85][0], arr[86][0], arr[87][0], arr[88][0], arr[89][0]);
	printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d", arr[90][0], arr[91][0], arr[92][0], arr[93][0], arr[94][0], arr[95][0], arr[96][0], arr[97][0], arr[98][0], arr[99][0]);
}

