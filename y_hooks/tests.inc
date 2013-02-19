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
