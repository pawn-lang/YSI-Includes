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

// There are no modules without master.
#if defined YSI_NO_MASTER
	#endinput
#endif

// The prototypes to call.
FOREIGN__ M_FuncP();
FOREIGN__ M_FuncR(in);
FOREIGN__ void:M_FuncT(&ret, in);
FOREIGN__ string:M_FuncV();
FOREIGN__ string:M_FuncX(const string:in[]);
FOREIGN__ M_FuncZ();

static stock Master_TestAll(base)
{
	new
		ret = 0;
	ASSERT_EQ(M_FuncP(), base);
	ASSERT_EQ(M_FuncR(42), 42 * base);
	ret = 0;
	M_FuncT(ret, 11);
	if (base)
	{
		new
			str[32];
		ASSERT_EQ(ret, 11 + base);
		format(str, sizeof (str), "MODULE %d", base);
		ASSERT_SAME(M_FuncV(), str);
		format(str, sizeof (str), "AA %d AA", base);
		ASSERT_SAME(M_FuncX("AA %d AA"), str);
		ASSERT_EQ(M_FuncZ(), Master_ID() << 16 | base);
	}
	else
	{
		ASSERT_EQ(ret, 0);
		ASSERT_SAME(M_FuncV(), YSI_EMPTY);
		ASSERT_SAME(M_FuncX("AA %d AA"), YSI_EMPTY);
		ASSERT_EQ(M_FuncZ(), 0);
	}
}

@test(.group = "y_master") Master_ModulesPhase0a()
{
	// Run the tests, without any server module loaded.
	new
		ret = 0;
	ASSERT_EQ(M_FuncP(), 0);
	ASSERT_EQ(M_FuncR(42), 0);
	ret = 0;
	M_FuncT(ret, 11);
	ASSERT_EQ(ret, 0);
	ASSERT_SAME(M_FuncV(), YSI_EMPTY);
	ASSERT_SAME(M_FuncX("AA %d AA"), YSI_EMPTY);
	ASSERT_EQ(M_FuncZ(), 0);
}

@test(.group = "y_master") Master_ModulesPhase0b()
{
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	// Check the string returns are cleared.
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase1a()
{
	// Loading a server after a cloud will steal it.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase1b()
{
	// Loading a server after a cloud will steal it.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase2a()
{
	// Loading a cloud after a server won't.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase2b()
{
	// Loading a cloud after a server won't.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase3a()
{
	// Even if the version is higher.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase3b()
{
	// Even if the version is higher.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase4a()
{
	// Higher cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase4b()
{
	// Higher cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase5a()
{
	// Lower cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase5b()
{
	// Lower cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

@test(.group = "y_master") Master_ModulesPhase6()
{
	// Loading a client won't make any difference.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_3");
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
	Master_UnloadModule("y_master_test_3");
	Master_TestAll(0);
}

