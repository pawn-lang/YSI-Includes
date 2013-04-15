static
	YSI_g_sValue;

hook OnRconCommand00(cmd[])
{
	// We test using OnRconCommand because it is the least likely to cause
	// problems when called unexpectedly at mode start.  Other callbacks use
	// players and probably expect that player to be connected.
	++YSI_g_sValue;
	return YSI_g_sValue;
}

hook OnRconCommand01(cmd[])
{
	// Called second due to forced orderings.
	++YSI_g_sValue;
	return 1;
}

public OnRconCommand(cmd[])
{
	// Called second due to forced orderings.
	if (YSI_g_sValue) return YSI_g_sValue - 7;
	#if defined y_hooks_OnRconCommand
		return y_hooks_OnRconCommand(cmd);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnRconCommand
	#undef OnRconCommand
#else
	#define _ALS_OnRconCommand
#endif
#define OnRconCommand y_hooks_OnRconCommand
#if defined y_hooks_OnRconCommand
	forward OnRconCommand(cmd[]);
#endif

Test:y_hooks_OnRconCommand()
{
	// Check both hooks are called.
	YSI_g_sValue = 0;
	call OnRconCommand("IGNORE_ME");
	ASSERT(YSI_g_sValue == 2);
	YSI_g_sValue = 0;
}

Test:y_hooks_ReturnM1()
{
	// Using -1 as a return should stop all processing.
	YSI_g_sValue = -2;
	new
		ret = call OnRconCommand("IGNORE_ME");
	ASSERT(ret == 0);
	ASSERT(YSI_g_sValue == -1);
	YSI_g_sValue = 0;
}

Test:y_hooks_ReturnM2()
{
	// Using -1 as a return should stop all processing.
	YSI_g_sValue = -3;
	new
		ret = call OnRconCommand("IGNORE_ME");
	ASSERT(ret == -1);
	ASSERT(YSI_g_sValue == -2);
	YSI_g_sValue = 0;
}

Test:y_hooks_Callback()
{
	// Using -1 as a return should stop all processing.
	YSI_g_sValue = 10;
	new
		ret = call OnRconCommand("IGNORE_ME");
	ASSERT(ret == 5);
	ASSERT(YSI_g_sValue == 12);
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

#include <YSI\internal\y_unique>

hook MyFunc1(a, b)
{
	//printf("Part 2 %d", a);
	g_y_hooksVar += a + b;
}

#include <YSI\internal\y_unique>

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#include <YSI\internal\y_unique>

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#include <YSI\internal\y_unique>

hook MyFunc1(a, b)
{
	//printf("Part 3 %d", b);
	g_y_hooksVar += a + b;
}

#include <YSI\internal\y_unique>

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
