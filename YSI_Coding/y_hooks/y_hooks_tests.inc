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

static
	YSI_g_sValue = 0;

#if !defined CHAIN_ORDER
	#define CHAIN_ORDER() 0
#endif

CHAIN_HOOK(TestPrehook)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(TestPrehook)

forward OnTestPrehook();

public OnTestPrehook()
{
	YSI_g_sValue = 89;
	TestPrehook_OnTestPrehook();
}

CHAIN_FORWARD:TestPrehook_OnTestPrehook() = 1;

#define OnTestPrehook(%0) CHAIN_PUBLIC:TestPrehook_OnTestPrehook(%0)

HOOK__ OnTestPrehook()
{
	++YSI_g_sValue;
}

@test(.group = "y_hooks") y_hooksPrehook()
{
	YSI_g_sValue = 91;
	CallLocalFunction("OnTestPrehook", "");
	ASSERT_EQ(YSI_g_sValue, 90);
}

forward OnTestCallback();

public OnTestCallback()
{
	YSI_g_sValue = 89;
	// TestPrehook_OnTestCallback();
}

CHAIN_FORWARD:TestPrehook_OnTestCallback() = 1;

#define OnTestCallback(%0) CHAIN_PUBLIC:TestPrehook_OnTestCallback(%0)

HOOK__ OnTestCallback()
{
	++YSI_g_sValue;
}

@test(.group = "y_hooks") y_hooksOrdering()
{
	YSI_g_sValue = 91;
	CallLocalFunction("OnTestCallback", "");
	ASSERT_EQ(YSI_g_sValue, 89);
}

static
	bool:y_hooks_OnScriptInit_called = false;

HOOK__ OnScriptInit()
{
	//print("hi");
	y_hooks_OnScriptInit_called = true;
}

@test(.group = "y_hooks") OnScriptInit()
{
	ASSERT(y_hooks_OnScriptInit_called);
}

static
	bool:y_hooks_OnCodeInit_called = false;

public OnCodeInit()
{
	y_hooks_OnCodeInit_called = true;
	
	#if defined HooksTest_OnCodeInit
		HooksTest_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit HooksTest_OnCodeInit
#if defined HooksTest_OnCodeInit
	forward HooksTest_OnCodeInit();
#endif

@test(.group = "y_hooks") OnCodeInit()
{
	ASSERT(y_hooks_OnCodeInit_called);
}

#if defined YSI_FAILING_TESTS

	DEFINE_HOOK_REPLACEMENT__(VeryLongTarget_, YyYy);

	HOOK__ y_hooks_YyYy0()
	{
		// The length after replacement here will be longer than the hook name,
		// even with prefix/suffixes.  This means you can't generate the
		// original name because there is no original.
		ASSERT(true);
		YSI_g_sValue = 101;
	}

	HOOK__ y_hooks_YyYy1()
	{
		// The length after replacement here will be longer than the hook name,
		// even with prefix/suffixes.  This means you can't generate the
		// original name because there is no original.
		ASSERT(true);
		YSI_g_sValue = 202;
	}

	HOOK__ y_hooks_YyYz1()
	{
		// Will come very next in the header.
		ASSERT(true);
		YSI_g_sValue = 303;
	}

	forward y_hooks_VeryLongTarget_0();

	public y_hooks_VeryLongTarget_0()
	{
		// This one should work, because we have the original function to use
		// for a pointer, not a newly generated version.
		ASSERT_EQ(YSI_g_sValue, 101);
		YSI_g_sValue += 404;
	}

	@test(.group = "y_hooks") y_hooks_TooLongReplacements()
	{
		YSI_g_sValue = 0;
		CallLocalFunction("y_hooks_VeryLongTarget_0", "");
		ASSERT_EQ(YSI_g_sValue, 505);
		YSI_g_sValue = 0;
		CallLocalFunction("y_hooks_YyYz1", "");
		ASSERT_EQ(YSI_g_sValue, 303);
		YSI_g_sValue = 0;
		// Currently fails.
		CallLocalFunction("y_hooks_VeryLongTarget_1", "");
		ASSERT_EQ(YSI_g_sValue, 202);
	}

#endif

HOOK__ Ony_hooksShortUpdate()
{
	++YSI_g_sValue;
}

HOOK__ Ony_hooksShortUpd()
{
	++YSI_g_sValue;
}

@test(.group = "y_hooks") Ony_hooksShortUpdate()
{
	YSI_g_sValue = 0;
	CallLocalFunction("Ony_hooksShortUpdate", "");
	ASSERT_EQ(YSI_g_sValue, 2);
}

#if defined YSI_FAILING_TESTS

	DEFINE_HOOK_REPLACEMENT__(TTTTT_YYYYY, YHook);

	forward Ony_hooksTTTTT_YYYYY_WtExtras();

	HOOK__ Ony_hooksYHook()
	{
		++YSI_g_sValue;
	}

	HOOK__ Ony_hooksTTTTT_YYYYY()
	{
		++YSI_g_sValue;
	}

	@test(.group = "y_hooks") y_hooksReplacement2()
	{
		YSI_g_sValue = 0;
		CallLocalFunction("Ony_hooksTTTTT_YYYYY", "");
		ASSERT_EQ(YSI_g_sValue, 2);
	}

	public Ony_hooksTTTTT_YYYYY_WtExtras()
	{
		++YSI_g_sValue;
	}

	HOOK__ Ony_hooksYHook_WtExtras()
	{
		++YSI_g_sValue;
	}

	@test(.group = "y_hooks") y_hooksReplacement3()
	{
		YSI_g_sValue = 0;
		CallLocalFunction("Ony_hooksTTTTT_YYYYY_WtExtras", "");
		ASSERT_EQ(YSI_g_sValue, 2);
	}

#endif

forward Ony_hooksTest2(cmd[]);

HOOK__ Ony_hooksTest2@000(cmd[])
{
	++YSI_g_sValue;
	return 1;
}

HOOK__ Ony_hooksTest2@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 1;
}

public Ony_hooksTest2(cmd[])
{
	// Called second due to forced orderings.
	//if (YSI_g_sValue) return YSI_g_sValue - 7;
	ASSERT_SAME(cmd, "IGNORE_ME");
	return 1;
}

@test(.group = "y_hooks") y_hooks_Ony_hooksTest2()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT_NZ(CallLocalFunction("Ony_hooksTest2", "s", "IGNORE_ME"));
	ASSERT_EQ(YSI_g_sValue, 2);
	YSI_g_sValue = 0;
}

forward y_hooks_PassParams(i1, a0[], i2);

public y_hooks_PassParams(i1, a0[], i2)
{
	ASSERT_EQ(i1, 42);
	ASSERT_SAME(a0, "Hello world");
	ASSERT_EQ(i2, 101);
}

HOOK__ y_hooks_PassParams@3(i1, a0[], i2)
{
	ASSERT_EQ(i1, 42);
	ASSERT_SAME(a0, "Hello world");
	ASSERT_EQ(i2, 101);
}

HOOK__ y_hooks_PassParams@2(i1, a0[], i2)
{
	ASSERT_EQ(i1, 42);
	ASSERT_SAME(a0, "Hello world");
	ASSERT_EQ(i2, 101);
}

HOOK__ y_hooks_PassParams@1(i1, a0[], i2)
{
	ASSERT_EQ(i1, 42);
	ASSERT_SAME(a0, "Hello world");
	ASSERT_EQ(i2, 101);
}

HOOK__ y_hooks_PassParams(i1, a0[], i2)
{
	ASSERT_EQ(i1, 42);
	ASSERT_SAME(a0, "Hello world");
	ASSERT_EQ(i2, 101);
}

@test(.group = "y_hooks") y_hooks_PassParams()
{
	CallLocalFunction("y_hooks_PassParams", "isi", 42, "Hello world", 101);
}

forward y_hooks_ReturnM2();

public y_hooks_ReturnM2()
{
	YSI_g_sValue = 8;
	return -2;
}

HOOK__ y_hooks_ReturnM2()
{
	YSI_g_sValue = 4;
	return -2;
}

@test(.group = "y_hooks") y_hooks_ReturnM2()
{
	YSI_g_sValue = 0;
	ASSERT_EQ(CallLocalFunction("y_hooks_ReturnM2", ""), 1);
	ASSERT_EQ(YSI_g_sValue, 4);
}

forward y_hooks_ReturnM1();

public y_hooks_ReturnM1()
{
	YSI_g_sValue = 8;
	return -1;
}

HOOK__ y_hooks_ReturnM1()
{
	YSI_g_sValue = 4;
	return -1;
}

@test(.group = "y_hooks") y_hooks_ReturnM1()
{
	YSI_g_sValue = 0;
	ASSERT_ZE(CallLocalFunction("y_hooks_ReturnM1", ""));
	ASSERT_EQ(YSI_g_sValue, 4);
}

forward y_hooks_Return0();

public y_hooks_Return0()
{
	YSI_g_sValue = 8;
	return 0;
}

HOOK__ y_hooks_Return0()
{
	YSI_g_sValue = 4;
	return 0;
}

@test(.group = "y_hooks") y_hooks_Return0()
{
	YSI_g_sValue = 0;
	ASSERT_ZE(CallLocalFunction("y_hooks_Return0", ""));
	ASSERT_EQ(YSI_g_sValue, 8);
}

forward y_hooks_Return1();

public y_hooks_Return1()
{
	YSI_g_sValue = 8;
	return 1;
}

HOOK__ y_hooks_Return1()
{
	YSI_g_sValue = 4;
	return 1;
}

@test(.group = "y_hooks") y_hooks_Return1()
{
	YSI_g_sValue = 0;
	ASSERT_EQ(CallLocalFunction("y_hooks_Return1", ""), 1);
	ASSERT_EQ(YSI_g_sValue, 8);
}

forward Ony_hooksTest3(cmd[]);

HOOK__ Ony_hooksTest3@000(cmd[])
{
	++YSI_g_sValue;
	//print("a");
	return 1;
}

HOOK__ Ony_hooksTest3@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	//print("b");
	return 1;
}

@test(.group = "y_hooks") y_hooks_Ony_hooksTest3()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT_NZ(CallLocalFunction("Ony_hooksTest3", "s", "IGNORE_ME"));
	ASSERT_EQ(YSI_g_sValue, 2);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest1(cmd[]);

HOOK__ Ony_hooksTest1@000(cmd[])
{
	++YSI_g_sValue;
	return 1;
}

HOOK__ Ony_hooksTest1@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

@test(.group = "y_hooks") y_hooks_Ony_hooksTest1()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT_ZE(CallLocalFunction("Ony_hooksTest1", "s", "IGNORE_ME"));
	ASSERT_EQ(YSI_g_sValue, 2);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest4(cmd[]);

HOOK__ Ony_hooksTest4@000(cmd[])
{
	++YSI_g_sValue;
	return -1;
}

HOOK__ Ony_hooksTest4@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

@test(.group = "y_hooks") y_hooks_Ony_hooksTest4()
{
	// Check only one hook is called.
	YSI_g_sValue = 0;
	ASSERT_ZE(CallLocalFunction("Ony_hooksTest4", "s", "IGNORE_ME"));
	ASSERT_EQ(YSI_g_sValue, 1);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest5(cmd[]);

HOOK__ Ony_hooksTest5@000(cmd[])
{
	++YSI_g_sValue;
	return -2;
}

HOOK__ Ony_hooksTest5@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

@test(.group = "y_hooks") y_hooks_Ony_hooksTest5()
{
	// Check only one hook is called.
	YSI_g_sValue = 0;
	ASSERT_EQ(CallLocalFunction("Ony_hooksTest5", "s", "IGNORE_ME"), 1);
	ASSERT_EQ(YSI_g_sValue, 1);
	YSI_g_sValue = 0;
}

static stock y_hooks_funcidx2(const str[])
{
	new
		func[FUNCTION_LENGTH],
		buf = 0,
		idx = 0;
	while ((idx = AMX_GetPublicName(idx, func, str)))
	{
		if (!strcmp(func, str))
		{
			AMX_GetPublicEntry(idx - 1, buf);
			return buf;
		}
	}
	return -1;
}

// We shouldn't be testing internal details like these.  Plus doing so REALLY
// messes up y_testing (it does deal with it, but it isn't pretty).
//forward y_hooks_Invalidate1();
//public y_hooks_Invalidate1() {}
//
//@test(.group = "y_hooks") y_hooks_Invalidate1()
//{
//	ASSERT_NE(funcidx("y_hooks_Invalidate1"), -1);
//	Hooks_InvalidatePointer(y_hooks_funcidx2("y_hooks_Invalidate1"));
//	Hooks_CompressPublics();
//	ASSERT_EQ(funcidx("y_hooks_Invalidate1"), -1);
//}
//
//forward y_hooks_Invalidate2();
//public y_hooks_Invalidate2() {}
//
//forward y_hooks_Invalidate3();
//public y_hooks_Invalidate3() {}
//
//@test(.group = "y_hooks") y_hooks_Invalidate23()
//{
//	new
//		base0 = 0,
//		count0 = 0;
//	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base0, count0);
//	ASSERT_NE(funcidx("y_hooks_Invalidate2"), -1);
//	ASSERT_NE(funcidx("y_hooks_Invalidate3"), -1);
//	Hooks_InvalidatePointer(y_hooks_funcidx2("y_hooks_Invalidate2"));
//	Hooks_InvalidatePointer(y_hooks_funcidx2("y_hooks_Invalidate3"));
//	Hooks_CompressPublics();
//	ASSERT_EQ(funcidx("y_hooks_Invalidate2"), -1);
//	ASSERT_EQ(funcidx("y_hooks_Invalidate3"), -1);
//	new
//		base1 = 0,
//		count1 = 0;
//	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base1, count1);
//	ASSERT(base1 > base0);
//	ASSERT(count1 < count0);
//}

static g_y_hooksVar = 0;

@test(.group = "y_hooks") y_hooks_Customs()
{
	g_y_hooksVar = 0;
	CallLocalFunction("y_hooks_MyFunc1", "ii", 4, 5);
	ASSERT_EQ(g_y_hooksVar, (4 + 5) * 6);
}

forward y_hooks_MyFunc1(a, b);

public y_hooks_MyFunc1(a, b)
{
	// printf("Part 1 %d %d", a, b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

HOOK__ y_hooks_MyFunc1(a, b)
{
	// printf("Part 2 %d", a);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

HOOK__ y_hooks_MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

HOOK__ y_hooks_MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

HOOK__ y_hooks_MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

HOOK__ y_hooks_MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#if !defined STREAMER_TAG_AREA
	#define STREAMER_TAG_AREA _
#endif
forward OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) { g_y_hooksVar += 100; }

HOOK__ OnPlayerEnterDynArea(p, a) { g_y_hooksVar += 10; }

@test(.group = "y_hooks") y_hooks_SpecialCases()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerEnterDynamicArea", "ii", 0, 0);
	ASSERT_EQ(g_y_hooksVar, 110);
}

@test(.group = "y_hooks") Hooks_MakeLongName0()
{
	new
		name[Y_HOOKS_MAX_NAME];
	name = "OnUpd";
	ASSERT_EQ(Hooks_MakeLongName(name), 8);
	ASSERT_SAME(name, "OnUpdate");
	name = "OnUpdD";
	ASSERT_EQ(Hooks_MakeLongName(name), 9);
	ASSERT_SAME(name, "OnUpdateD");
	name = "OnUpda";
	ASSERT_EQ(Hooks_MakeLongName(name), 6);
	ASSERT_SAME(name, "OnUpda");
}

@test(.group = "y_hooks") Hooks_MakeLongName1()
{
	new
		name[Y_HOOKS_MAX_NAME];
	name = "CP";
	ASSERT_EQ(Hooks_MakeLongName(name), 10);
	ASSERT_SAME(name, "Checkpoint");
	name = "TD";
	ASSERT_EQ(Hooks_MakeLongName(name), 8);
	ASSERT_SAME(name, "TextDraw");
	name = "Upd";
	ASSERT_EQ(Hooks_MakeLongName(name), 6);
	ASSERT_SAME(name, "Update");
	name = "Dyn";
	ASSERT_EQ(Hooks_MakeLongName(name), 7);
	ASSERT_SAME(name, "Dynamic");
	name = "Obj";
	ASSERT_EQ(Hooks_MakeLongName(name), 6);
	ASSERT_SAME(name, "Object");
	name = "Cmd";
	ASSERT_EQ(Hooks_MakeLongName(name), 7);
	ASSERT_SAME(name, "Command");
	name = "DynamicCP";
	ASSERT_EQ(Hooks_MakeLongName(name), 9);
	ASSERT_SAME(name, "DynamicCP");
}

#if __COMPILER_sNAMEMAX == 31
	@test(.group = "y_hooks") Hooks_MakeLongName2()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "OnUpdTDCP";
		ASSERT_EQ(Hooks_MakeLongName(name), 26);
		ASSERT_SAME(name, "OnUpdateTextDrawCheckpoint");
		name = "OnUpdTDObjCmd";
		ASSERT_EQ(Hooks_MakeLongName(name), 29);
		ASSERT_SAME(name, "OnUpdateTextDrawObjectCommand");
		name = "OnUpdTDCPObjCmd";
		ASSERT_EQ(Hooks_MakeLongName(name), 31);
		ASSERT_SAME(name, "OnUpdateTextDrawCPObjectCommand");
	}

	@test(.group = "y_hooks") Hooks_MakeShortName1()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "OnPlayerEnterRaceCP";
		ASSERT_EQ(Hooks_MakeShortName(name), 19);
		ASSERT_SAME(name, "OnPlayerEnterRaceCP");
		name = "OnPlayerEnterRaceCheckpoint";
		ASSERT_EQ(Hooks_MakeShortName(name), 27);
		ASSERT_SAME(name, "OnPlayerEnterRaceCheckpoint");
		name = "OnPlayerEnterDynamicCP";
		ASSERT_EQ(Hooks_MakeShortName(name), 22);
		ASSERT_SAME(name, "OnPlayerEnterDynamicCP");
		name = "OnPlayerEnterDynamicRaceCheckpoint";
		ASSERT_EQ(Hooks_MakeShortName(name), 26);
		ASSERT_SAME(name, "OnPlayerEnterDynamicRaceCP");
		name = "AAAAAAAAAAAAAAAAAAAUpdateTextDraw";
		Hooks_MakeShortName(name);
		ASSERT_SAME(name, "AAAAAAAAAAAAAAAAAAAUpdateTD");
		name = "BBBBBAAAAAAAAAAAAAAAAAAAUpdateTextDraw";
		Hooks_MakeShortName(name);
		ASSERT_SAME(name, "BBBBBAAAAAAAAAAAAAAAAAAAUpdTD");
	}

	@test(.group = "y_hooks") Hooks_MakeShortName2()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC";
		ASSERT_EQ(Hooks_MakeShortName(name), 43);
		ASSERT_SAME(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC");
		name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCommandCCCC";
		ASSERT_EQ(Hooks_MakeShortName(name), 45);
		ASSERT_SAME(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCmdCCCC");
	}
#elseif __COMPILER_sNAMEMAX == 63
	@test(.group = "y_hooks") Hooks_MakeLongName2()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "OnUpdTDCP";
		ASSERT_EQ(Hooks_MakeLongName(name), 26);
		ASSERT_SAME(name, "OnUpdateTextDrawCheckpoint");
		name = "OnUpdTDObjCmd";
		ASSERT_EQ(Hooks_MakeLongName(name), 29);
		ASSERT_SAME(name, "OnUpdateTextDrawObjectCommand");
		name = "OnUpdTDCPObjCmd";
		ASSERT_EQ(Hooks_MakeLongName(name), 39);
		ASSERT_SAME(name, "OnUpdateTextDrawCheckpointObjectCommand");
		name = "OnUpdTDCPObjCmdBBBBBBBBBAAAAAAAAAAAAAAAAAAA";
		ASSERT_EQ(Hooks_MakeLongName(name), 59);
		ASSERT_SAME(name, "OnUpdateTextDrawCPObjectCommandBBBBBBBBBAAAAAAAAAAAAAAAAAAA");
	}

	@test(.group = "y_hooks") Hooks_MakeShortName1()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "OnPlayerEnterRaceCP";
		ASSERT_EQ(Hooks_MakeShortName(name), 19);
		ASSERT_SAME(name, "OnPlayerEnterRaceCP");
		name = "OnPlayerEnterRaceCheckpoint";
		ASSERT_EQ(Hooks_MakeShortName(name), 27);
		ASSERT_SAME(name, "OnPlayerEnterRaceCheckpoint");
		name = "OnPlayerEnterDynamicCP";
		ASSERT_EQ(Hooks_MakeShortName(name), 22);
		ASSERT_SAME(name, "OnPlayerEnterDynamicCP");
		name = "OnPlayerEnterDynamicRaceCheckpointBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA";
		ASSERT_EQ(Hooks_MakeShortName(name), 60);
		ASSERT_SAME(name, "OnPlayerEnterDynamicRaceCPBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA");
		name = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAUpdateTextDraw";
		Hooks_MakeShortName(name);
		ASSERT_SAME(name, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAUpdateTD");
		name = "BBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAABBBBBAAAAAAAAAAAAAAAAAAAUpdateTextDraw";
		Hooks_MakeShortName(name);
		ASSERT_SAME(name, "BBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAABBBBBAAAAAAAAAAAAAAAAAAAUpdTD");
	}

	@test(.group = "y_hooks") Hooks_MakeShortName2()
	{
		new
			name[Y_HOOKS_MAX_NAME];
		name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC";
		ASSERT_EQ(Hooks_MakeShortName(name), 43);
		ASSERT_SAME(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC");
		name = "BBBBBBBBBBCCCCCCCCBBBBBBBBBBCCCCCCCCAAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCommandCCCC";
		ASSERT_EQ(Hooks_MakeShortName(name), 81);
		ASSERT_SAME(name, "BBBBBBBBBBCCCCCCCCBBBBBBBBBBCCCCCCCCAAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCmdCCCC");
	}
#else
	#error No y_hooks tests for this sNAMEMAX.
#endif

@test(.group = "y_hooks") Hooks_GetDefaultReturn()
{
	ASSERT_EQ(Hooks_GetDefaultReturn("OnHookRet\0\0\0\0\0\0\0\0"), 1);
	ASSERT_ZE(Hooks_GetDefaultReturn("OnPlayerCommandText\0\0\0\0\0\0\0\0"));
	ASSERT_ZE(Hooks_GetDefaultReturn("OnHookRet2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"));
	ASSERT_EQ(Hooks_GetDefaultReturn("OnPlayerConnect\0\0\0\0\0\0\0\0"), 1);
}

DEFINE_HOOK_RETURN__(OnHookRet2, 0);

DEFINE_HOOK_REPLACEMENT__(Replacement, Rpl);

forward OnPlayerCustomReplacement();
public OnPlayerCustomReplacement() { g_y_hooksVar += 500; }

HOOK__ OnPlayerCustomRpl() { g_y_hooksVar += 55; }

@test(.group = "y_hooks") y_hooks_CustomReplacement()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerCustomReplacement", "");
	ASSERT_EQ(g_y_hooksVar, 555);
}

#if !defined BAD_numargs
	#error y_hooks tests require BAD_numargs
#endif

#if __COMPILER_MODIFIED
	HOOK__ OnTestNumArgs0(a, b, c, d, e, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 6);
		ASSERT_EQ(numargs(), 6);
	}

	HOOK__ OnTestNumArgs1(a, b, c, d, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 5);
		ASSERT_NE(BAD_numargs(), 5);
		ASSERT_EQ(numargs(), 5);
	}

	forward OnTestNumArgs1(a, b, c, d, f);
	public OnTestNumArgs1(a, b, c, d, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 5);
		ASSERT_NE(BAD_numargs(), 5);
		ASSERT_EQ(numargs(), 5);
	}

	HOOK__ OnTestNumArgs2(a, b, c, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 4);
		ASSERT_NE(BAD_numargs(), 4);
		ASSERT_EQ(numargs(), 4);
	}

	#tryinclude "..\YSI_Coding\y_unique"
	#tryinclude "..\..\YSI_Coding\y_unique"

	HOOK__ OnTestNumArgs2(a, b, c, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 4);
		ASSERT_NE(BAD_numargs(), 4);
		ASSERT_EQ(numargs(), 4);
	}

	forward OnTestNumArgs2(a, b, c, f);
	public OnTestNumArgs2(a, b, c, f)
	{
		ASSERT_EQ(Hooks_NumArgs(), 4);
		ASSERT_NE(BAD_numargs(), 4);
		ASSERT_EQ(numargs(), 4);
	}

	static OnTestNumArgs4(total, ...)
	{
		ASSERT_EQ(numargs(), total + 1);
	}

	@test(.group = "y_hooks") y_hooks_numargs()
	{
		CallLocalFunction("OnTestNumArgs0", "iiiiii", 0, 0, 0, 0, 0, 0);
		CallLocalFunction("OnTestNumArgs1", "iiiii", 0, 0, 0, 0, 0);
		CallLocalFunction("OnTestNumArgs2", "iiii", 0, 0, 0, 0);
		OnTestNumArgs4(0);
		OnTestNumArgs4(1, 1);
		OnTestNumArgs4(2, 1, 2);
		OnTestNumArgs4(3, 1, 2, 3);
		OnTestNumArgs4(4, 1, 2, 3, 4);
		OnTestNumArgs4(5, 1, 2, 3, 4, 5);
		OnTestNumArgs4(6, 1, 2, 3, 4, 5, 6);
	}
#endif

HOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_1>
{
	g_y_hooksVar = strval(c[0]);
}

REHOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_2>
{
	g_y_hooksVar = strval(c[5]);
}

REHOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_3>
{
	g_y_hooksVar += strval(c[5]);
}

//HOOK__ public y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_4>
REHOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_4>
{
	g_y_hooksVar = strval(c[5]);
}

@test(.group = "y_hooks") y_hooks_State1()
{
	g_y_hooksVar = 0;
	state y_hooks_state : y_hooks_state_1;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 1000);
	state y_hooks_state : y_hooks_state_2;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 2000);
	state y_hooks_state : y_hooks_state_1;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 1000);
	state y_hooks_state : y_hooks_state_3;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 3000);
}

@test(.group = "y_hooks") y_hooks_DeprecatedReturns()
{
	// Ensure there's a warning on this line.
	return Y_HOOKS_BREAK_RETURN_1;
}

static stock y_hooks_CrashTrigger()
{
	#emit HALT 1
}

HOOK__ y_hooks_Crash@1()
{
}

// Test K&R, because people have no taste.
HOOK__ y_hooks_Crash@2() {
}

HOOK__ y_hooks_Crash@3()
{
	y_hooks_CrashTrigger();
}

HOOK__ y_hooks_Crash@4()
{
}

@test(.group = "y_hooks") y_hooks_Crash()
{
	if (Server_CrashDetectExists())
	{
		CallLocalFunction("y_hooks_Crash", "");
		Testing_SurpressOneFail();
	}
	//else
	//{
	//	ASSERT(Server_CrashDetectExists());
	//}
}

static stock
	YSI_g_sMinA = 0,
	YSI_g_sMinB = 0,
	YSI_g_sMinC = 0;

HOOK_NATIVE__ min(a, b)
{
	// A native function we can easily replicate, in tests only.
	return
		(YSI_g_sMinA = a),
		(YSI_g_sMinB = b),
		(YSI_g_sMinC = (a < b) ? a : b);
}

// Test K&R, because people have no taste.
hook native max(a, b) {
	// A native function we can easily replicate, in tests only.
	return
		(YSI_g_sMinA = a),
		(YSI_g_sMinB = b),
		(YSI_g_sMinC = (a > b) ? a : b);
}

@test(.group = "y_hooks") y_hooks_native()
{
	// Test that we haven't broken `min`.
	ASSERT_EQ(min(5, 6), 5);
	ASSERT_EQ(min(cellmin, cellmax), cellmin);
	ASSERT_EQ(min(cellmin, 0), cellmin);
	ASSERT_EQ(min(0, cellmax), 0);
	ASSERT_EQ(min(0, 1), 0);
	ASSERT_EQ(min(-1, 1), -1);
	ASSERT_EQ(min(-1, 0), -1);

	// Test that the order doesn't matter.
	ASSERT_EQ(min(6, 5), 5);
	ASSERT_EQ(min(cellmax, cellmin), cellmin);
	ASSERT_EQ(min(0, cellmin), cellmin);
	ASSERT_EQ(min(cellmax, 0), 0);
	ASSERT_EQ(min(1, 0), 0);
	ASSERT_EQ(min(1, -1), -1);
	ASSERT_EQ(min(0, -1), -1);

	// Test that our hook was called.
	YSI_g_sMinA = 100,
	YSI_g_sMinB = 100,
	YSI_g_sMinC = 100;
	min(80, 90);
	ASSERT_EQ(YSI_g_sMinA, 80);
	ASSERT_EQ(YSI_g_sMinB, 90);
	ASSERT_EQ(YSI_g_sMinC, 80);
	min(90, 70);
	ASSERT_EQ(YSI_g_sMinA, 90);
	ASSERT_EQ(YSI_g_sMinB, 70);
	ASSERT_EQ(YSI_g_sMinC, 70);
	
	ASSERT_EQ(max(101, 202), 202);
	ASSERT_EQ(YSI_g_sMinA, 101);
	ASSERT_EQ(YSI_g_sMinB, 202);
	ASSERT_EQ(YSI_g_sMinC, 202);
}

static stock y_hooks_HookedStock(str[], v, &c)
{
	str[0] = 'h';
	c = v + 5;
	return 5;
}

HOOK_STOCK__ y_hooks_HookedStock(str[], v, &c)
{
	// A native function we can easily replicate, in tests only.
	new ret = continue(str, v, c);
	c += v;
	str[1] = 'i';
	return 10 + ret;
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

hook stock y_hooks_HookedStock(str[], v, &c)
{
	// A native function we can easily replicate, in tests only.
	new ret = continue(str, v, c);
	c += v;
	str[2] = 't';
	return 20 + ret;
}

@test(.group = "y_hooks") y_hooks_HookedStock()
{
	new c = 10;
	new str[32];
	ASSERT_EQ(y_hooks_HookedStock(str, 2, c), 35);
	ASSERT_EQ(c, 11);
	ASSERT_EQ(str[0], 'h');
	ASSERT_EQ(str[1], 'i');
	ASSERT_EQ(str[2], 't');
}

@hook(.native = "clamp", .order = 5) MyClampHook1(value, min, max)
{
	// A native function we can easily replicate, in tests only.
	//printf("clamp 2: %d, %d, %d, %d", numargs(), value, min, max);
	//DumpFullStack();
	return
		(YSI_g_sMinA = min),
		(YSI_g_sMinB = max),
		(YSI_g_sMinC = continue(value, min, max)),
		min += 5,
		max -= 5,
		continue(value, min, max);
}

@hook(.native = "clamp", .order = 5) MyClampHook2(value, min, max)
{
	//printf("clamp 1: %d, %d, %d, %d", numargs(), value, min, max);
	// A native function we can easily replicate, in tests only.
	return continue(value, min, max + 5);
}

@hook(.native = "clamp", .order = 5) MyClampHook3(value, min, max)
{
	//printf("clamp 0: %d, %d, %d, %d", numargs(), value, min, max);
	// A native function we can easily replicate, in tests only.
	return continue(value, min - 5, max);
}

@test(.group = "y_hooks") HookClamp()
{
	ASSERT_EQ(clamp(100, 70, 90), 90);
	ASSERT_EQ(YSI_g_sMinA, 65);
	ASSERT_EQ(YSI_g_sMinB, 95);
	ASSERT_EQ(YSI_g_sMinC, 95);

	ASSERT_EQ(clamp(168, 170, 190), 170);
	ASSERT_EQ(YSI_g_sMinA, 165);
	ASSERT_EQ(YSI_g_sMinB, 195);
	ASSERT_EQ(YSI_g_sMinC, 168);

	ASSERT_EQ(clamp(-92, -90, -70), -90);
	ASSERT_EQ(YSI_g_sMinA, -95);
	ASSERT_EQ(YSI_g_sMinB, -65);
	ASSERT_EQ(YSI_g_sMinC, -92);

	ASSERT_EQ(clamp(15, 10, 20), 15);
	ASSERT_EQ(YSI_g_sMinA, 5);
	ASSERT_EQ(YSI_g_sMinB, 25);
	ASSERT_EQ(YSI_g_sMinC, 15);
}

@test(.group = "y_hooks") y_va_HookClamp()
{
	// Check a regression.
	ASSERT_EQ(clamp(11, 55, 101), 55);
	ASSERT_EQ(YSI_g_sMinA, 50);
	ASSERT_EQ(YSI_g_sMinB, 106);
	ASSERT_EQ(YSI_g_sMinC, 50);

	ASSERT_EQ(clamp(5, 11, 12), 11);
	ASSERT_EQ(YSI_g_sMinA, 6);
	ASSERT_EQ(YSI_g_sMinB, 17);
	ASSERT_EQ(YSI_g_sMinC, 6);
}

#if defined _ALS_strlen
	#error Found exsting strlen hook in y_hooks tests.
#endif

stock y_hooks_strlen_1(const string[])
{
	YSI_g_sMinA += 10;
	return strlen(string);
}

#define strlen( y_hooks_strlen_1(

hook native strlen(const string[])
{
	YSI_g_sMinA *= 2;
	return continue(string);
}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

hook native strlen(const string[])
{
	YSI_g_sMinA = 50;
	return continue(string);
}

//stock y_hooks_strlen_2(const string[])
//{
//	YSI_g_sMinA = 50;
//	return strlen(string);
//}
//
//#define strlen( y_hooks_strlen_2(

@test(.group = "y_hooks") y_hooks_strlen()
{
	ASSERT_EQ(strlen("Hello world."), 12);
	ASSERT_EQ(YSI_g_sMinA, 50 * 2 + 10);
}

// Don't affect other code.
#undef strlen

//@hook(.callback = "OnNewHooks") OnNewHooks1(playerid)
//{
//	#pragma unused playerid
//	YSI_g_sValue += 4;
//}
//
//@hook("OnNewHooks") OnNewHooks2(playerid)
//{
//	#pragma unused playerid
//	YSI_g_sValue += 8;
//}
//
//@hook() OnNewHooks(playerid)
//{
//	#pragma unused playerid
//	YSI_g_sValue += 2;
//}
//
//@test(.group = "y_hooks") OnNewHooks()
//{
//	YSI_g_sValue = 1;
//	CallLocalFunction("OnNewHooks", "i", 0);
//	ASSERT_EQ(YSI_g_sValue, 15);
//}

//@hook(.fallback = true) OnPlayerConnect(playerid)
//{
//}
//
//@hook(.public = "OnPlayerConnect", .fallback = true) y_hooks_OnPlayerConnect_0(playerid)
//{
//}
//
//#tryinclude "..\YSI_Coding\y_unique"
//#tryinclude "..\..\YSI_Coding\y_unique"
//
//@hook() OnPlayerConnect(playerid)
//{
//}
//
//@hook(.public = "OnPlayerConnect") y_hooks_OnPlayerConnect_1(playerid)
//{
//}
//
//#tryinclude "..\YSI_Coding\y_unique"
//#tryinclude "..\..\YSI_Coding\y_unique"
//
//hook OnPlayerConnect(playerid)
//{
//}

#tryinclude "..\YSI_Coding\y_unique"
#tryinclude "..\..\YSI_Coding\y_unique"

stock TestHookedFunc(a, const string:b[], ...)
{
	#pragma unused a
	return numargs() + strval(b);
}

hook stock TestHookedFunc(a, const string:b[], ...)
//_@yHTestHookedFunc@FI(a, const b[], ...);
//@yH_TestHookedFunc@FI(&a,const b[]);
//@yH_TestHookedFunc@FI(&a,const b[])
//	return _yH@(1<<1|0,(O@D_:O@A_())?(((_:_@yHTestHookedFunc@FI(a,b)),O@V_)?1:2):(O@V_)), TestHookedFunc(a,b);
//static _@yHTestHookedFunc@FI(a, const b[], ...)
{
	//printf("TestHookedFunc");
	return a + continue(a, b, YVA2_DummyPush(2 * cellbytes));
}

@test(.group = "y_hooks") TestHookedFunc()
{
	ASSERT_EQ(TestHookedFunc(5, "100", 9, 8), 109);
}

static HookableFunction1()
{
	return 1;
}

static HookableFunction2()
{
	return 100;
}

@hook(.stock = "HookableFunction1") y_hooks_AAAAA()
{
	return continue() + 2;
}

@hook(.stock = "HookableFunction2") y_hooks_BBBBB()
{
	return continue() + 200;
}

@hook(.stock = "HookableFunction1") y_hooks_CCCCC()
{
	return continue() + 4;
}

@hook(.stock = "HookableFunction2") y_hooks_DDDDD()
{
	return continue() + 400;
}

@test(.group = "y_hooks") y_hooks_DefinitionOrder()
{
	ASSERT_EQ(HookableFunction1(), 7);
	ASSERT_EQ(HookableFunction2(), 700);
}

stock y_hooks_ALSHookedFuncImpl(var)
{
	return var * 2;
}

stock y_hooks_ALSExtraFunc(var)
{
	return var + 7;
}

#define y_hooks_ALSHookedFunc(%0) y_hooks_ALSHookedFuncImpl(y_hooks_ALSExtraFunc(%0))

hook stock y_hooks_ALSHookedFunc(var)
{
	YSI_g_sValue = var;
	return continue(var + 2);
}

@test(.group = "y_hooks") y_hooks_ALSHookedFuncTest()
{
	YSI_g_sValue = 123;
	ASSERT_EQ(y_hooks_ALSHookedFunc(5), 28);
	ASSERT_EQ(YSI_g_sValue, 12);
}

// Dozens of hooks to test the list limits.

static stock y_hooks_Func1(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1") y_hooks_Func1(v)
{
	return continue(v) + 1;
}

static stock y_hooks_Func5(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func5") y_hooks_Func5(v)
{
	return continue(v) + 5;
}

static stock y_hooks_Func4(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func4") y_hooks_Func4(v)
{
	return continue(v) + 4;
}

static stock y_hooks_Func11(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11") y_hooks_Func11(v)
{
	return continue(v) + 11;
}

static stock y_hooks_Func10(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func10") y_hooks_Func10(v)
{
	return continue(v) + 10;
}

static stock y_hooks_Func12(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func12") y_hooks_Func12(v)
{
	return continue(v) + 12;
}

static stock y_hooks_Func18(v)
{
	return v;
}

static stock y_hooks_Func0(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func0") y_hooks_Func0(v)
{
	return continue(v) + 0;
}

static stock y_hooks_Func2(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func2") y_hooks_Func2(v)
{
	return continue(v) + 2;
}

static stock y_hooks_Func8(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func8") y_hooks_Func8(v)
{
	return continue(v) + 8;
}

static stock y_hooks_Func7(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func7") y_hooks_Func7(v)
{
	return continue(v) + 7;
}

static stock y_hooks_Func9(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func9") y_hooks_Func9(v)
{
	return continue(v) + 9;
}

static stock y_hooks_Func6(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func6") y_hooks_Func6(v)
{
	return continue(v) + 6;
}

static stock y_hooks_Func11111(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11111") y_hooks_Func11111(v)
{
	return continue(v) + 11111;
}

static stock y_hooks_Func11110(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11110") y_hooks_Func11110(v)
{
	return continue(v) + 11110;
}

static stock y_hooks_Func11112(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11112") y_hooks_Func11112(v)
{
	return continue(v) + 11112;
}

static stock y_hooks_Func11118(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11118") y_hooks_Func11118(v)
{
	return continue(v) + 11118;
}

static stock y_hooks_Func11117(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11117") y_hooks_Func11117(v)
{
	return continue(v) + 11117;
}

static stock y_hooks_Func11119(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11119") y_hooks_Func11119(v)
{
	return continue(v) + 11119;
}

static stock y_hooks_Func11116(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11116") y_hooks_Func11116(v)
{
	return continue(v) + 11116;
}

static stock y_hooks_Func11113(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11113") y_hooks_Func11113(v)
{
	return continue(v) + 11113;
}

static stock y_hooks_Func11115(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11115") y_hooks_Func11115(v)
{
	return continue(v) + 11115;
}

static stock y_hooks_Func11114(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func11114") y_hooks_Func11114(v)
{
	return continue(v) + 11114;
}

static stock y_hooks_Func1111(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1111") y_hooks_Func1111(v)
{
	return continue(v) + 1111;
}

static stock y_hooks_Func1110(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1110") y_hooks_Func1110(v)
{
	return continue(v) + 1110;
}

static stock y_hooks_Func1112(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1112") y_hooks_Func1112(v)
{
	return continue(v) + 1112;
}

static stock y_hooks_Func1118(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1118") y_hooks_Func1118(v)
{
	return continue(v) + 1118;
}

static stock y_hooks_Func1117(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1117") y_hooks_Func1117(v)
{
	return continue(v) + 1117;
}

static stock y_hooks_Func1119(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1119") y_hooks_Func1119(v)
{
	return continue(v) + 1119;
}

static stock y_hooks_Func1116(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1116") y_hooks_Func1116(v)
{
	return continue(v) + 1116;
}

static stock y_hooks_Func1113(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1113") y_hooks_Func1113(v)
{
	return continue(v) + 1113;
}

static stock y_hooks_Func1115(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1115") y_hooks_Func1115(v)
{
	return continue(v) + 1115;
}

static stock y_hooks_Func1114(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func1114") y_hooks_Func1114(v)
{
	return continue(v) + 1114;
}

static stock y_hooks_Func3(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func3") y_hooks_Func3(v)
{
	return continue(v) + 3;
}

@hook(.stock = "y_hooks_Func18") y_hooks_Func18(v)
{
	return continue(v) + 18;
}

static stock y_hooks_Func17(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func17") y_hooks_Func17(v)
{
	return continue(v) + 17;
}

static stock y_hooks_Func19(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func19") y_hooks_Func19(v)
{
	return continue(v) + 19;
}

static stock y_hooks_Func16(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func16") y_hooks_Func16(v)
{
	return continue(v) + 16;
}

static stock y_hooks_Func13(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func13") y_hooks_Func13(v)
{
	return continue(v) + 13;
}

static stock y_hooks_Func15(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func15") y_hooks_Func15(v)
{
	return continue(v) + 15;
}

static stock y_hooks_Func14(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func14") y_hooks_Func14(v)
{
	return continue(v) + 14;
}

static stock y_hooks_Func111(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func111") y_hooks_Func111(v)
{
	return continue(v) + 111;
}

static stock y_hooks_Func110(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func110") y_hooks_Func110(v)
{
	return continue(v) + 110;
}

static stock y_hooks_Func112(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func112") y_hooks_Func112(v)
{
	return continue(v) + 112;
}

static stock y_hooks_Func118(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func118") y_hooks_Func118(v)
{
	return continue(v) + 118;
}

static stock y_hooks_Func117(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func117") y_hooks_Func117(v)
{
	return continue(v) + 117;
}

static stock y_hooks_Func119(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func119") y_hooks_Func119(v)
{
	return continue(v) + 119;
}

static stock y_hooks_Func116(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func116") y_hooks_Func116(v)
{
	return continue(v) + 116;
}

static stock y_hooks_Func113(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func113") y_hooks_Func113(v)
{
	return continue(v) + 113;
}

static stock y_hooks_Func115(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func115") y_hooks_Func115(v)
{
	return continue(v) + 115;
}

static stock y_hooks_Func114(v)
{
	return v;
}

@hook(.stock = "y_hooks_Func114") y_hooks_Func114(v)
{
	return continue(v) + 114;
}

#define Y_HOOKS_TEST_CONST (1000)

@test(.group = "y_hooks") ManyManyHooks0()
{
	ASSERT_EQ(y_hooks_Func0(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 0);
	ASSERT_EQ(y_hooks_Func1(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1);
	ASSERT_EQ(y_hooks_Func2(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 2);
	ASSERT_EQ(y_hooks_Func3(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 3);
	ASSERT_EQ(y_hooks_Func4(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 4);
	ASSERT_EQ(y_hooks_Func5(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 5);
	ASSERT_EQ(y_hooks_Func6(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 6);
	ASSERT_EQ(y_hooks_Func7(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 7);
	ASSERT_EQ(y_hooks_Func8(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 8);
	ASSERT_EQ(y_hooks_Func9(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 9);
	ASSERT_EQ(y_hooks_Func10(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 10);
	ASSERT_EQ(y_hooks_Func11(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11);
	ASSERT_EQ(y_hooks_Func12(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 12);
	ASSERT_EQ(y_hooks_Func13(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 13);
	ASSERT_EQ(y_hooks_Func14(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 14);
	ASSERT_EQ(y_hooks_Func15(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 15);
	ASSERT_EQ(y_hooks_Func16(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 16);
	ASSERT_EQ(y_hooks_Func17(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 17);
	ASSERT_EQ(y_hooks_Func18(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 18);
	ASSERT_EQ(y_hooks_Func19(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 19);
	ASSERT_EQ(y_hooks_Func110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 110);
	ASSERT_EQ(y_hooks_Func111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 111);
	ASSERT_EQ(y_hooks_Func112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 112);
	ASSERT_EQ(y_hooks_Func113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 113);
	ASSERT_EQ(y_hooks_Func114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 114);
	ASSERT_EQ(y_hooks_Func115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 115);
	ASSERT_EQ(y_hooks_Func116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 116);
	ASSERT_EQ(y_hooks_Func117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 117);
	ASSERT_EQ(y_hooks_Func118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 118);
	ASSERT_EQ(y_hooks_Func119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 119);
	ASSERT_EQ(y_hooks_Func1110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1110);
	ASSERT_EQ(y_hooks_Func1111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1111);
	ASSERT_EQ(y_hooks_Func1112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1112);
	ASSERT_EQ(y_hooks_Func1113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1113);
	ASSERT_EQ(y_hooks_Func1114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1114);
	ASSERT_EQ(y_hooks_Func1115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1115);
	ASSERT_EQ(y_hooks_Func1116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1116);
	ASSERT_EQ(y_hooks_Func1117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1117);
	ASSERT_EQ(y_hooks_Func1118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1118);
	ASSERT_EQ(y_hooks_Func1119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1119);
	ASSERT_EQ(y_hooks_Func11110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11110);
	ASSERT_EQ(y_hooks_Func11111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11111);
	ASSERT_EQ(y_hooks_Func11112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11112);
	ASSERT_EQ(y_hooks_Func11113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11113);
	ASSERT_EQ(y_hooks_Func11114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11114);
	ASSERT_EQ(y_hooks_Func11115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11115);
	ASSERT_EQ(y_hooks_Func11116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11116);
	ASSERT_EQ(y_hooks_Func11117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11117);
	ASSERT_EQ(y_hooks_Func11118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11118);
	ASSERT_EQ(y_hooks_Func11119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11119);
}

#undef Y_HOOKS_TEST_CONST

#define Y_HOOKS_TEST_CONST (cellmax)

@test(.group = "y_hooks") ManyManyHooks1()
{
	ASSERT_EQ(y_hooks_Func0(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 0);
	ASSERT_EQ(y_hooks_Func1(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1);
	ASSERT_EQ(y_hooks_Func2(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 2);
	ASSERT_EQ(y_hooks_Func3(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 3);
	ASSERT_EQ(y_hooks_Func4(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 4);
	ASSERT_EQ(y_hooks_Func5(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 5);
	ASSERT_EQ(y_hooks_Func6(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 6);
	ASSERT_EQ(y_hooks_Func7(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 7);
	ASSERT_EQ(y_hooks_Func8(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 8);
	ASSERT_EQ(y_hooks_Func9(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 9);
	ASSERT_EQ(y_hooks_Func10(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 10);
	ASSERT_EQ(y_hooks_Func11(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11);
	ASSERT_EQ(y_hooks_Func12(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 12);
	ASSERT_EQ(y_hooks_Func13(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 13);
	ASSERT_EQ(y_hooks_Func14(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 14);
	ASSERT_EQ(y_hooks_Func15(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 15);
	ASSERT_EQ(y_hooks_Func16(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 16);
	ASSERT_EQ(y_hooks_Func17(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 17);
	ASSERT_EQ(y_hooks_Func18(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 18);
	ASSERT_EQ(y_hooks_Func19(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 19);
	ASSERT_EQ(y_hooks_Func110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 110);
	ASSERT_EQ(y_hooks_Func111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 111);
	ASSERT_EQ(y_hooks_Func112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 112);
	ASSERT_EQ(y_hooks_Func113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 113);
	ASSERT_EQ(y_hooks_Func114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 114);
	ASSERT_EQ(y_hooks_Func115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 115);
	ASSERT_EQ(y_hooks_Func116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 116);
	ASSERT_EQ(y_hooks_Func117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 117);
	ASSERT_EQ(y_hooks_Func118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 118);
	ASSERT_EQ(y_hooks_Func119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 119);
	ASSERT_EQ(y_hooks_Func1110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1110);
	ASSERT_EQ(y_hooks_Func1111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1111);
	ASSERT_EQ(y_hooks_Func1112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1112);
	ASSERT_EQ(y_hooks_Func1113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1113);
	ASSERT_EQ(y_hooks_Func1114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1114);
	ASSERT_EQ(y_hooks_Func1115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1115);
	ASSERT_EQ(y_hooks_Func1116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1116);
	ASSERT_EQ(y_hooks_Func1117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1117);
	ASSERT_EQ(y_hooks_Func1118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1118);
	ASSERT_EQ(y_hooks_Func1119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1119);
	ASSERT_EQ(y_hooks_Func11110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11110);
	ASSERT_EQ(y_hooks_Func11111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11111);
	ASSERT_EQ(y_hooks_Func11112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11112);
	ASSERT_EQ(y_hooks_Func11113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11113);
	ASSERT_EQ(y_hooks_Func11114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11114);
	ASSERT_EQ(y_hooks_Func11115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11115);
	ASSERT_EQ(y_hooks_Func11116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11116);
	ASSERT_EQ(y_hooks_Func11117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11117);
	ASSERT_EQ(y_hooks_Func11118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11118);
	ASSERT_EQ(y_hooks_Func11119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11119);
}

#undef Y_HOOKS_TEST_CONST

#define Y_HOOKS_TEST_CONST (-5)

@test(.group = "y_hooks") ManyManyHooks2()
{
	ASSERT_EQ(y_hooks_Func0(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 0);
	ASSERT_EQ(y_hooks_Func1(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1);
	ASSERT_EQ(y_hooks_Func2(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 2);
	ASSERT_EQ(y_hooks_Func3(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 3);
	ASSERT_EQ(y_hooks_Func4(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 4);
	ASSERT_EQ(y_hooks_Func5(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 5);
	ASSERT_EQ(y_hooks_Func6(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 6);
	ASSERT_EQ(y_hooks_Func7(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 7);
	ASSERT_EQ(y_hooks_Func8(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 8);
	ASSERT_EQ(y_hooks_Func9(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 9);
	ASSERT_EQ(y_hooks_Func10(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 10);
	ASSERT_EQ(y_hooks_Func11(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11);
	ASSERT_EQ(y_hooks_Func12(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 12);
	ASSERT_EQ(y_hooks_Func13(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 13);
	ASSERT_EQ(y_hooks_Func14(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 14);
	ASSERT_EQ(y_hooks_Func15(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 15);
	ASSERT_EQ(y_hooks_Func16(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 16);
	ASSERT_EQ(y_hooks_Func17(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 17);
	ASSERT_EQ(y_hooks_Func18(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 18);
	ASSERT_EQ(y_hooks_Func19(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 19);
	ASSERT_EQ(y_hooks_Func110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 110);
	ASSERT_EQ(y_hooks_Func111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 111);
	ASSERT_EQ(y_hooks_Func112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 112);
	ASSERT_EQ(y_hooks_Func113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 113);
	ASSERT_EQ(y_hooks_Func114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 114);
	ASSERT_EQ(y_hooks_Func115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 115);
	ASSERT_EQ(y_hooks_Func116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 116);
	ASSERT_EQ(y_hooks_Func117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 117);
	ASSERT_EQ(y_hooks_Func118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 118);
	ASSERT_EQ(y_hooks_Func119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 119);
	ASSERT_EQ(y_hooks_Func1110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1110);
	ASSERT_EQ(y_hooks_Func1111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1111);
	ASSERT_EQ(y_hooks_Func1112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1112);
	ASSERT_EQ(y_hooks_Func1113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1113);
	ASSERT_EQ(y_hooks_Func1114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1114);
	ASSERT_EQ(y_hooks_Func1115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1115);
	ASSERT_EQ(y_hooks_Func1116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1116);
	ASSERT_EQ(y_hooks_Func1117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1117);
	ASSERT_EQ(y_hooks_Func1118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1118);
	ASSERT_EQ(y_hooks_Func1119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1119);
	ASSERT_EQ(y_hooks_Func11110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11110);
	ASSERT_EQ(y_hooks_Func11111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11111);
	ASSERT_EQ(y_hooks_Func11112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11112);
	ASSERT_EQ(y_hooks_Func11113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11113);
	ASSERT_EQ(y_hooks_Func11114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11114);
	ASSERT_EQ(y_hooks_Func11115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11115);
	ASSERT_EQ(y_hooks_Func11116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11116);
	ASSERT_EQ(y_hooks_Func11117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11117);
	ASSERT_EQ(y_hooks_Func11118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11118);
	ASSERT_EQ(y_hooks_Func11119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11119);
}

#undef Y_HOOKS_TEST_CONST

#define Y_HOOKS_TEST_CONST (1003)

@test(.group = "y_hooks") ManyManyHooks3()
{
	ASSERT_EQ(y_hooks_Func0(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 0);
	ASSERT_EQ(y_hooks_Func1(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1);
	ASSERT_EQ(y_hooks_Func2(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 2);
	ASSERT_EQ(y_hooks_Func3(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 3);
	ASSERT_EQ(y_hooks_Func4(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 4);
	ASSERT_EQ(y_hooks_Func5(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 5);
	ASSERT_EQ(y_hooks_Func6(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 6);
	ASSERT_EQ(y_hooks_Func7(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 7);
	ASSERT_EQ(y_hooks_Func8(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 8);
	ASSERT_EQ(y_hooks_Func9(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 9);
	ASSERT_EQ(y_hooks_Func10(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 10);
	ASSERT_EQ(y_hooks_Func11(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11);
	ASSERT_EQ(y_hooks_Func12(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 12);
	ASSERT_EQ(y_hooks_Func13(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 13);
	ASSERT_EQ(y_hooks_Func14(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 14);
	ASSERT_EQ(y_hooks_Func15(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 15);
	ASSERT_EQ(y_hooks_Func16(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 16);
	ASSERT_EQ(y_hooks_Func17(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 17);
	ASSERT_EQ(y_hooks_Func18(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 18);
	ASSERT_EQ(y_hooks_Func19(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 19);
	ASSERT_EQ(y_hooks_Func110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 110);
	ASSERT_EQ(y_hooks_Func111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 111);
	ASSERT_EQ(y_hooks_Func112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 112);
	ASSERT_EQ(y_hooks_Func113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 113);
	ASSERT_EQ(y_hooks_Func114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 114);
	ASSERT_EQ(y_hooks_Func115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 115);
	ASSERT_EQ(y_hooks_Func116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 116);
	ASSERT_EQ(y_hooks_Func117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 117);
	ASSERT_EQ(y_hooks_Func118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 118);
	ASSERT_EQ(y_hooks_Func119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 119);
	ASSERT_EQ(y_hooks_Func1110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1110);
	ASSERT_EQ(y_hooks_Func1111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1111);
	ASSERT_EQ(y_hooks_Func1112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1112);
	ASSERT_EQ(y_hooks_Func1113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1113);
	ASSERT_EQ(y_hooks_Func1114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1114);
	ASSERT_EQ(y_hooks_Func1115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1115);
	ASSERT_EQ(y_hooks_Func1116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1116);
	ASSERT_EQ(y_hooks_Func1117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1117);
	ASSERT_EQ(y_hooks_Func1118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1118);
	ASSERT_EQ(y_hooks_Func1119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 1119);
	ASSERT_EQ(y_hooks_Func11110(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11110);
	ASSERT_EQ(y_hooks_Func11111(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11111);
	ASSERT_EQ(y_hooks_Func11112(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11112);
	ASSERT_EQ(y_hooks_Func11113(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11113);
	ASSERT_EQ(y_hooks_Func11114(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11114);
	ASSERT_EQ(y_hooks_Func11115(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11115);
	ASSERT_EQ(y_hooks_Func11116(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11116);
	ASSERT_EQ(y_hooks_Func11117(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11117);
	ASSERT_EQ(y_hooks_Func11118(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11118);
	ASSERT_EQ(y_hooks_Func11119(Y_HOOKS_TEST_CONST), Y_HOOKS_TEST_CONST + 11119);
}

#undef Y_HOOKS_TEST_CONST

