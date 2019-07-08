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
	YSI_g_sValue;

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

TEST__ y_hooksPrehook()
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

TEST__ y_hooksOrdering()
{
	YSI_g_sValue = 91;
	CallLocalFunction("OnTestCallback", "");
	ASSERT_EQ(YSI_g_sValue, 89);
}

static
	bool:y_hooks_OnScriptInit_called = false;

HOOK__ OnScriptInit()
{
	y_hooks_OnScriptInit_called = true;
}

TEST__ OnScriptInit()
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

TEST__ OnCodeInit()
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

	TEST__ y_hooks_TooLongReplacements()
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

TEST__ Ony_hooksShortUpdate()
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

	TEST__ y_hooksReplacement2()
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

	TEST__ y_hooksReplacement3()
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

TEST__ y_hooks_Ony_hooksTest2()
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

TEST__ y_hooks_PassParams()
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

TEST__ y_hooks_ReturnM2()
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

TEST__ y_hooks_ReturnM1()
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

TEST__ y_hooks_Return0()
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

TEST__ y_hooks_Return1()
{
	YSI_g_sValue = 0;
	ASSERT_EQ(CallLocalFunction("y_hooks_Return1", ""), 1);
	ASSERT_EQ(YSI_g_sValue, 8);
}

forward Ony_hooksTest3(cmd[]);

HOOK__ Ony_hooksTest3@000(cmd[])
{
	++YSI_g_sValue;
	//printf("a");
	return 1;
}

HOOK__ Ony_hooksTest3@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	//printf("b");
	return 1;
}

TEST__ y_hooks_Ony_hooksTest3()
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

TEST__ y_hooks_Ony_hooksTest1()
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

TEST__ y_hooks_Ony_hooksTest4()
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

TEST__ y_hooks_Ony_hooksTest5()
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
		func[32],
		buf,
		idx;
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

forward y_hooks_Invalidate1();
public y_hooks_Invalidate1() {}

TEST__ y_hooks_Invalidate1()
{
	ASSERT_NE(funcidx("y_hooks_Invalidate1"), -1);
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate1"));
	Hooks_SortPublics();
	ASSERT_EQ(funcidx("y_hooks_Invalidate1"), -1);
}

forward y_hooks_Invalidate2();
public y_hooks_Invalidate2() {}

forward y_hooks_Invalidate3();
public y_hooks_Invalidate3() {}

TEST__ y_hooks_Invalidate23()
{
	new
		base0,
		count0;
	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base0, count0);
	ASSERT_NE(funcidx("y_hooks_Invalidate2"), -1);
	ASSERT_NE(funcidx("y_hooks_Invalidate3"), -1);
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate2"));
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate3"));
	Hooks_SortPublics();
	ASSERT_EQ(funcidx("y_hooks_Invalidate2"), -1);
	ASSERT_EQ(funcidx("y_hooks_Invalidate3"), -1);
	new
		base1,
		count1;
	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base1, count1);
	ASSERT(base1 > base0);
	ASSERT(count1 < count0);
}

TEST__ y_hooks_IsolateName1()
{
	new
		name[32];
	name = "@yH_Hello@Other";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Hello"));
	name = "@yH_Hi@@Other";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Hi"));
	name = "@yH_No@Other@More";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "No"));
	name = "@yH_Yes_Other@N";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Yes_Other"));
}

TEST__ y_hooks_IsolateName2()
{
	new
		func[32];
	#define FUNC:%0; func = "_yH@"#%0"@";Hooks_IsolateName(func);ASSERT(!strcmp(func, #%0));
	FUNC:A;
	FUNC:AAA;
	FUNC:AAB;
	FUNC:ABA;
	FUNC:ABB;
	FUNC:aB;
	FUNC:ab;
	FUNC:Ab;
	#undef FUNC
}

static g_y_hooksVar;

TEST__ y_hooks_Customs()
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

forward OnPlayerEnterDynamicArea(p, a);

public OnPlayerEnterDynamicArea(p, a) { g_y_hooksVar += 100; }

HOOK__ OnPlayerEnterDynArea(p, a) { g_y_hooksVar += 10; }

TEST__ y_hooks_SpecialCases()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerEnterDynamicArea", "ii", 0, 0);
	ASSERT_EQ(g_y_hooksVar, 110);
}

TEST__ Hooks_MakeLongName0()
{
	new
		name[64];
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

TEST__ Hooks_MakeLongName1()
{
	new
		name[64];
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

TEST__ Hooks_MakeLongName2()
{
	new
		name[64];
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

TEST__ Hooks_MakeShortName1()
{
	new
		name[64];
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

TEST__ Hooks_MakeShortName2()
{
	new
		name[64];
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC";
	ASSERT_EQ(Hooks_MakeShortName(name), 43);
	ASSERT_SAME(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC");
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCommandCCCC";
	ASSERT_EQ(Hooks_MakeShortName(name), 45);
	ASSERT_SAME(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCmdCCCC");
}

TEST__ Hooks_GetDefaultReturn()
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

TEST__ y_hooks_CustomReplacement()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerCustomReplacement", "");
	ASSERT_EQ(g_y_hooksVar, 555);
}

#if !defined BAD_numargs
	#error y_hooks tests require BAD_numargs
#endif

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

TEST__ y_hooks_numargs()
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

HOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_1>
{
	g_y_hooksVar = strval(c[0]);
}

HOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_2>
{
	g_y_hooksVar = strval(c[5]);
}

REHOOK__ y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_3>
{
	g_y_hooksVar += strval(c[5]);
}

//HOOK__ public y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_4>
hook y_hooks_State1(string:c[]) <y_hooks_state : y_hooks_state_4>
{
	g_y_hooksVar = strval(c[5]);
}

TEST__ y_hooks_State1()
{
	state y_hooks_state : y_hooks_state_1;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 1000);
	state y_hooks_state : y_hooks_state_2;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 2000);
	state y_hooks_state : y_hooks_state_1;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	state y_hooks_state : y_hooks_state_3;
	CallLocalFunction("y_hooks_State1", "s", "1000 2000");
	ASSERT_EQ(g_y_hooksVar, 3000);
}

static stock y_hooks_CrashTrigger()
{
	#emit HALT 1
}

HOOK__ y_hooks_Crash@1()
{
}

HOOK__ y_hooks_Crash@2()
{
}

HOOK__ y_hooks_Crash@3()
{
	y_hooks_CrashTrigger();
}

HOOK__ y_hooks_Crash@4()
{
}

TEST__ y_hooks_Crash()
{
	CallLocalFunction("y_hooks_Crash", "");
	Testing_SurpressOneFail();
}

