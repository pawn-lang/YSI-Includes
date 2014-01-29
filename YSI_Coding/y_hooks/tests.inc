static
	YSI_g_sValue;

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
	name = !"@yH_Hello@Other";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Hello"));
	name = !"@yH_Hi@@Other";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Hi"));
	name = !"@yH_No@Other@More";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "No"));
	name = !"@yH_Yes_Other@N";
	Hooks_IsolateName(name);
	ASSERT_FALSE(strcmp(name, "Yes_Other"));
}

Test:y_hooks_IsolateName2()
{
	new
		func[32];
	#define FUNC:%0; func = !"_yH@"#%0"@";Hooks_IsolateName(func);ASSERT(!strcmp(#%0, func));
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
	//printf("Part 1 %d %d", a, b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	//printf("Part 2 %d", a);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#tryinclude "..\YSI_Internal\y_unique"
#tryinclude "..\..\YSI_Internal\y_unique"

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
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

