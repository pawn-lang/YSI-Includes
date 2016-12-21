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

hook OnTestPrehook()
{
	++YSI_g_sValue;
}

Test:y_hooksPrehook()
{
	YSI_g_sValue = 91;
	CallLocalFunction("OnTestPrehook", "");
	ASSERT(YSI_g_sValue == 90);
}

forward OnTestCallback();

public OnTestCallback()
{
	YSI_g_sValue = 89;
	// TestPrehook_OnTestCallback();
}

CHAIN_FORWARD:TestPrehook_OnTestCallback() = 1;

#define OnTestCallback(%0) CHAIN_PUBLIC:TestPrehook_OnTestCallback(%0)

hook OnTestCallback()
{
	++YSI_g_sValue;
}

Test:y_hooksOrdering()
{
	YSI_g_sValue = 91;
	CallLocalFunction("OnTestCallback", "");
	ASSERT(YSI_g_sValue == 89);
}

static
	bool:y_hooks_OnScriptInit_called = false;

hook OnScriptInit()
{
	y_hooks_OnScriptInit_called = true;
}

Test:OnScriptInit()
{
	ASSERT(y_hooks_OnScriptInit_called);
}

static
	bool:y_hooks_OnCodeInit_called = false;

hook OnCodeInit()
{
	y_hooks_OnCodeInit_called = true;
}

Test:OnCodeInit()
{
	ASSERT(y_hooks_OnCodeInit_called);
}

forward Ony_hooksTest2(cmd[]);

hook Ony_hooksTest2@000(cmd[])
{
	++YSI_g_sValue;
	return 1;
}

hook Ony_hooksTest2@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 1;
}

public Ony_hooksTest2(cmd[])
{
	// Called second due to forced orderings.
	//if (YSI_g_sValue) return YSI_g_sValue - 7;
	ASSERT(!strcmp(cmd, "IGNORE_ME"));
	return 1;
}

Test:y_hooks_Ony_hooksTest2()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("Ony_hooksTest2", "s", "IGNORE_ME") != 0);
	ASSERT(YSI_g_sValue == 2);
	YSI_g_sValue = 0;
}

forward y_hooks_PassParams(i1, a0[], i2);

public y_hooks_PassParams(i1, a0[], i2)
{
	ASSERT(i1 == 42);
	ASSERT(!strcmp(a0, "Hello world"));
	ASSERT(i2 == 101);
}

hook y_hooks_PassParams@3(i1, a0[], i2)
{
	ASSERT(i1 == 42);
	ASSERT(!strcmp(a0, "Hello world"));
	ASSERT(i2 == 101);
}

hook y_hooks_PassParams@2(i1, a0[], i2)
{
	ASSERT(i1 == 42);
	ASSERT(!strcmp(a0, "Hello world"));
	ASSERT(i2 == 101);
}

hook y_hooks_PassParams@1(i1, a0[], i2)
{
	ASSERT(i1 == 42);
	ASSERT(!strcmp(a0, "Hello world"));
	ASSERT(i2 == 101);
}

hook y_hooks_PassParams(i1, a0[], i2)
{
	ASSERT(i1 == 42);
	ASSERT(!strcmp(a0, "Hello world"));
	ASSERT(i2 == 101);
}

Test:y_hooks_PassParams()
{
	CallLocalFunction("y_hooks_PassParams", "isi", 42, "Hello world", 101);
}

forward y_hooks_ReturnM2();

public y_hooks_ReturnM2()
{
	YSI_g_sValue = 8;
	return -2;
}

hook y_hooks_ReturnM2()
{
	YSI_g_sValue = 4;
	return -2;
}

Test:y_hooks_ReturnM2()
{
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("y_hooks_ReturnM2", "") == 1);
	ASSERT(YSI_g_sValue == 4);
}

forward y_hooks_ReturnM1();

public y_hooks_ReturnM1()
{
	YSI_g_sValue = 8;
	return -1;
}

hook y_hooks_ReturnM1()
{
	YSI_g_sValue = 4;
	return -1;
}

Test:y_hooks_ReturnM1()
{
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("y_hooks_ReturnM1", "") == 0);
	ASSERT(YSI_g_sValue == 4);
}

forward y_hooks_Return0();

public y_hooks_Return0()
{
	YSI_g_sValue = 8;
	return 0;
}

hook y_hooks_Return0()
{
	YSI_g_sValue = 4;
	return 0;
}

Test:y_hooks_Return0()
{
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("y_hooks_Return0", "") == 0);
	ASSERT(YSI_g_sValue == 8);
}

forward y_hooks_Return1();

public y_hooks_Return1()
{
	YSI_g_sValue = 8;
	return 1;
}

hook y_hooks_Return1()
{
	YSI_g_sValue = 4;
	return 1;
}

Test:y_hooks_Return1()
{
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("y_hooks_Return1", "") == 1);
	ASSERT(YSI_g_sValue == 8);
}

forward Ony_hooksTest3(cmd[]);

hook Ony_hooksTest3@000(cmd[])
{
	++YSI_g_sValue;
	//printf("a");
	return 1;
}

hook Ony_hooksTest3@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	//printf("b");
	return 1;
}

Test:y_hooks_Ony_hooksTest3()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("Ony_hooksTest3", "s", "IGNORE_ME") != 0);
	ASSERT(YSI_g_sValue == 2);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest1(cmd[]);

hook Ony_hooksTest1@000(cmd[])
{
	++YSI_g_sValue;
	return 1;
}

hook Ony_hooksTest1@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

Test:y_hooks_Ony_hooksTest1()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("Ony_hooksTest1", "s", "IGNORE_ME") == 0);
	ASSERT(YSI_g_sValue == 2);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest4(cmd[]);

hook Ony_hooksTest4@000(cmd[])
{
	++YSI_g_sValue;
	return -1;
}

hook Ony_hooksTest4@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

Test:y_hooks_Ony_hooksTest4()
{
	// Check only one hook is called.
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("Ony_hooksTest4", "s", "IGNORE_ME") == 0);
	ASSERT(YSI_g_sValue == 1);
	YSI_g_sValue = 0;
}

forward Ony_hooksTest5(cmd[]);

hook Ony_hooksTest5@000(cmd[])
{
	++YSI_g_sValue;
	return -2;
}

hook Ony_hooksTest5@001(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 0;
}

Test:y_hooks_Ony_hooksTest5()
{
	// Check only one hook is called.
	YSI_g_sValue = 0;
	ASSERT(CallLocalFunction("Ony_hooksTest5", "s", "IGNORE_ME") == 1);
	ASSERT(YSI_g_sValue == 1);
	YSI_g_sValue = 0;
}

static stock y_hooks_funcidx2(str[])
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

Test:y_hooks_Invalidate1()
{
	ASSERT(funcidx("y_hooks_Invalidate1") != -1);
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate1"));
	Hooks_SortPublics();
	ASSERT(funcidx("y_hooks_Invalidate1") == -1);
}

forward y_hooks_Invalidate2();
public y_hooks_Invalidate2() {}

forward y_hooks_Invalidate3();
public y_hooks_Invalidate3() {}

Test:y_hooks_Invalidate23()
{
	new
		base0,
		count0;
	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base0, count0);
	ASSERT(funcidx("y_hooks_Invalidate2") != -1);
	ASSERT(funcidx("y_hooks_Invalidate3") != -1);
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate2"));
	Hooks_InvalidateName(y_hooks_funcidx2("y_hooks_Invalidate3"));
	Hooks_SortPublics();
	ASSERT(funcidx("y_hooks_Invalidate2") == -1);
	ASSERT(funcidx("y_hooks_Invalidate3") == -1);
	new
		base1,
		count1;
	AMX_GetBaseCount(AMX_TABLE_PUBLICS, base1, count1);
	ASSERT(base1 > base0);
	ASSERT(count1 < count0);
}

Test:y_hooks_IsolateName1()
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

Test:y_hooks_IsolateName2()
{
	new
		func[32];
	#define FUNC:%0; func = "_yH@"#%0"@";Hooks_IsolateName(func);ASSERT(!strcmp(#%0, func));
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

Test:y_hooks_Customs()
{
	g_y_hooksVar = 0;
	CallLocalFunction("MyFunc1", "ii", 4, 5);
	ASSERT(g_y_hooksVar == (4 + 5) * 6);
}

forward MyFunc1(a, b);

public MyFunc1(a, b)
{
	// printf("Part 1 %d %d", a, b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	// printf("Part 2 %d", a);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	// printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

forward OnPlayerEnterDynamicArea(p, a);

public OnPlayerEnterDynamicArea(p, a) { g_y_hooksVar += 100; }

hook OnPlayerEnterDynArea(p, a) { g_y_hooksVar += 10; }

Test:y_hooks_SpecialCases()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerEnterDynamicArea", "ii", 0, 0);
	ASSERT(g_y_hooksVar == 110);
}

Test:Hooks_MakeLongName0()
{
	new
		name[64];
	name = "OnUpd";
	ASSERT(Hooks_MakeLongName(name) == 8);
	ASSERT(!strcmp(name, "OnUpdate"));
	name = "OnUpdD";
	ASSERT(Hooks_MakeLongName(name) == 9);
	ASSERT(!strcmp(name, "OnUpdateD"));
	name = "OnUpda";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "OnUpda"));
}

Test:Hooks_MakeLongName1()
{
	new
		name[64];
	name = "CP";
	ASSERT(Hooks_MakeLongName(name) == 10);
	ASSERT(!strcmp(name, "Checkpoint"));
	name = "TD";
	ASSERT(Hooks_MakeLongName(name) == 8);
	ASSERT(!strcmp(name, "TextDraw"));
	name = "Upd";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "Update"));
	name = "Dyn";
	ASSERT(Hooks_MakeLongName(name) == 7);
	ASSERT(!strcmp(name, "Dynamic"));
	name = "Obj";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "Object"));
	name = "Cmd";
	ASSERT(Hooks_MakeLongName(name) == 7);
	ASSERT(!strcmp(name, "Command"));
	name = "DynamicCP";
	ASSERT(Hooks_MakeLongName(name) == 9);
	ASSERT(!strcmp(name, "DynamicCP"));
}

Test:Hooks_MakeLongName2()
{
	new
		name[64];
	name = "OnUpdTDCP";
	ASSERT(Hooks_MakeLongName(name) == 26);
	ASSERT(!strcmp(name, "OnUpdateTextDrawCheckpoint"));
	name = "OnUpdTDObjCmd";
	ASSERT(Hooks_MakeLongName(name) == 29);
	ASSERT(!strcmp(name, "OnUpdateTextDrawObjectCommand"));
	name = "OnUpdTDCPObjCmd";
	ASSERT(Hooks_MakeLongName(name) == 31);
	ASSERT(!strcmp(name, "OnUpdateTextDrawCPObjectCommand"));
}

Test:Hooks_MakeShortName1()
{
	new
		name[64];
	name = "OnPlayerEnterRaceCP";
	ASSERT(Hooks_MakeShortName(name) == 19);
	ASSERT(!strcmp(name, "OnPlayerEnterRaceCP"));
	name = "OnPlayerEnterRaceCheckpoint";
	ASSERT(Hooks_MakeShortName(name) == 27);
	ASSERT(!strcmp(name, "OnPlayerEnterRaceCheckpoint"));
	name = "OnPlayerEnterDynamicCP";
	ASSERT(Hooks_MakeShortName(name) == 22);
	ASSERT(!strcmp(name, "OnPlayerEnterDynamicCP"));
	name = "OnPlayerEnterDynamicRaceCheckpoint";
	ASSERT(Hooks_MakeShortName(name) == 26);
	ASSERT(!strcmp(name, "OnPlayerEnterDynamicRaceCP"));
	name = "AAAAAAAAAAAAAAAAAAAUpdateTextDraw";
	Hooks_MakeShortName(name);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAAAAAAAUpdateTD"));
	name = "BBBBBAAAAAAAAAAAAAAAAAAAUpdateTextDraw";
	Hooks_MakeShortName(name);
	ASSERT(!strcmp(name, "BBBBBAAAAAAAAAAAAAAAAAAAUpdTD"));
}

Test:Hooks_MakeShortName2()
{
	new
		name[64];
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC";
	ASSERT(Hooks_MakeShortName(name) == 43);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC"));
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCommandCCCC";
	ASSERT(Hooks_MakeShortName(name) == 45);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCmdCCCC"));
}

Test:Hooks_GetDefaultReturn()
{
	ASSERT(Hooks_GetDefaultReturn("OnHookRet\0\0\0\0\0\0\0\0") == 1);
	ASSERT(Hooks_GetDefaultReturn("OnPlayerCommandText\0\0\0\0\0\0\0\0") == 0);
	ASSERT(Hooks_GetDefaultReturn("OnHookRet2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0") == 0);
	ASSERT(Hooks_GetDefaultReturn("OnPlayerConnect\0\0\0\0\0\0\0\0") == 1);
}

HOOK_RET:OnHookRet2() return 0;

DEFINE_HOOK_REPLACEMENT(Replacement, Rpl);

forward OnPlayerCustomReplacement();
public OnPlayerCustomReplacement() { g_y_hooksVar += 500; }

hook OnPlayerCustomRpl() { g_y_hooksVar += 55; }

Test:y_hooks_CustomReplacement()
{
	g_y_hooksVar = 0;
	CallLocalFunction("OnPlayerCustomReplacement", "");
	ASSERT(g_y_hooksVar == 555);
}

