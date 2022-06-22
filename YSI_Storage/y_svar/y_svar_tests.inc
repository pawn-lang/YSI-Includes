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

enum y_svar_E_TEST
{
	y_svar_E_TEST_A,
	Float:y_svar_E_TEST_B,
	y_svar_E_TEST_C[24]
}

svar y_svar_TestEnum[y_svar_E_TEST];
svar y_svar_Test1D[200];
svar y_svar_Test2D[200][200];
svar y_svar_Test2DEnum[200][y_svar_E_TEST];
svar y_svar_TestEnum2D[y_svar_E_TEST][200];

TEST__ y_svar_Enum()
{
	// Should fail first time ever, but then not again.
	ASSERT_EQ(y_svar_TestEnum[y_svar_E_TEST_A], 42);
	y_svar_TestEnum[y_svar_E_TEST_A] = 42;
	ASSERT_EQ(y_svar_TestEnum[y_svar_E_TEST_B], 55.44);
	y_svar_TestEnum[y_svar_E_TEST_B] = 55.44;
	ASSERT(!strcmp(y_svar_TestEnum[y_svar_E_TEST_C], "SOME STORED DATA") && y_svar_TestEnum[y_svar_E_TEST_C][0]);
	StrCpy(y_svar_TestEnum[y_svar_E_TEST_C], "SOME STORED DATA", 24);
}

TEST__ y_svar_1D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test1D); ++i)
	{
		if (y_svar_Test1D[i] != i) ++fails;
		y_svar_Test1D[i] = i;
	}
	ASSERT_ZE(fails);
}

TEST__ y_svar_2D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test2D); ++i)
	{
		for (new j = 0; j != sizeof (y_svar_Test2D[]); ++j)
		{
			if (y_svar_Test2D[i][j] != i * j) ++fails;
			y_svar_Test2D[i][j] = i * j;
		}
	}
	ASSERT_ZE(fails);
}

TEST__ y_svar_2DEnum()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test2DEnum); ++i)
	{
		if (!(y_svar_Test2DEnum[i][y_svar_E_TEST_A] == 42 * i)) ++fails;
		y_svar_Test2DEnum[i][y_svar_E_TEST_A] = 42 * i;
		if (!(y_svar_Test2DEnum[i][y_svar_E_TEST_B] == 55.44 + i)) ++fails;
		y_svar_Test2DEnum[i][y_svar_E_TEST_B] = 55.44 + i;
		if (strcmp(y_svar_Test2DEnum[i][y_svar_E_TEST_C], "SOME STORED DATA") || !y_svar_Test2DEnum[i][y_svar_E_TEST_C][0]) ++fails;
		StrCpy(y_svar_Test2DEnum[i][y_svar_E_TEST_C], "SOME STORED DATA", 24);
	}
	ASSERT_ZE(fails);
}

TEST__ y_svar_Enum2D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_TestEnum2D[]); ++i)
	{
		if (y_svar_TestEnum2D[y_svar_E_TEST_A][i] != i + 101) ++fails;
		y_svar_TestEnum2D[y_svar_E_TEST_A][i] = i + 101;
	}
	ASSERT_ZE(fails);
}
