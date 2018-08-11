
#define _SPECIAL_FUNCTION@timer%0[%2](%1) FUNC_PARSER(TIMER,QAL:ARR_CST:REF_DEF:STR_CST_DEF:NUM_CST_DEF:)(%0(%1))(%0(%1))()(%2)()#

// TIMER_STR(const, tag, name, size)rest$(original_call)(time)(pass_parameters)specifier#
#define TIMER_STR(%6,%9,%2,%5,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2[%5])(%1)(%3,%2)%4s#
#define TIMER_ARR(%6,%9,%2,%5,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2[%5])(%1)(%3,%2)%4a#
#define TIMER_NUM(%6,%9,%2,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2)(%1)(%3,%2)%4i#
#define TIMER_REF(%6,%9,%2,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6&%2)(%1)(%3,%2)%4v#

// ".." is used to reserve memory at the start of the string for:
// 
//   +0 - TIMER function start pointer.
//   +1 - Stack size.
#define TIMER_END(%9)%8$(%0(%7))(,%1)(%5)(%3)%4# %8$_yT@%0(%7)return SetTimerEx(#%0,(I@==-1)?(%5):I@,J@,#%4%3)%0(%1);public %0(%1)
#define TIMER_NUL(%9)%8$(%0(%7))(%1)(%5)(%3)%4# %8$_yT@%0()return SetTimer(#%0,(I@==-1)?(%5):I@,J@)%0();public %0()

#define _yT@%0\32; _yT@
#define @_yT%0\32; @_yT
#define @yT_%0\32; @yT_

#define _SPECIAL_FUNCTION@task%0[%1](%2) @yT_%0(g,p);new %0;@yT_%0(g,p){static s=-1;return _Timer_I(#%0,%1,g,s);}@_yT%0();public @_yT%0()

#define _SPECIAL_FUNCTION@ptask%0[%1](%2) @yT_%0(E_TIMER_ACTION:a,p);new %0;@yT_%0(E_TIMER_ACTION:a,p){static s[MAX_PLAYERS]={-1,...},a[2];return Timer_RunPTask_((!"@_yT"#%0),(%0),(%1),a,p,s);}@_yT%0(%2);public @_yT%0(%2)

enum E_TIMER_ACTION
{
	E_TIMER_ACTION_REGISTER,
	E_TIMER_ACTION_GET,
	E_TIMER_ACTION_START,
	E_TIMER_ACTION_START_ALL,
	E_TIMER_ACTION_STOP,
	E_TIMER_ACTION_STOP_ALL,
}

#if !defined MAX_PTASKS
	#define MAX_PTASKS (32)
#endif

static stock
	YSI_g_sPTaskCount,
	YSI_g_sPTasks[MAX_PTASKS];

#if 0

// Options for possible unified function declaration syntax.

//@.task  // Indirection
//@:task  // All tags
@[task] // Maybe (but also clashey)
@<task> // Maybe (but also clashey)
@(task) // Maybe (but also clashey)

__<hook> // Compiler-reserved, but we can have community consensus.
__hook // No, too clashey.
_.hook

@hook

hook@

__declspec(hook)

__func(hook)

__func hook 

@ hook OnPlayerConnect()
{
	
}

HOOK__ OnPlayerConnect()
{
	
}

TASK__
TIMER__
PTASK__
FOREACH__

#if defined KEYWORD_hook
	#define hook HOOK__
#endif

#endif

stock bool:Timer_RunPTask_(const name[], &ptr, const interval, const E_TIMER_ACTION:action, playerid, results[])
{
	switch (action)
	{
		case E_TIMER_ACTION_REGISTER:
		{
			if (YSI_g_sPTaskCount >= MAX_PTASKS)
			{
				P:E("MAX_PTASKS exceeded, please recompile with `#define MAX_PTASKS (more)`");
			}
			else
			{
				// Get the entry point, not the action.
				new entryPoint[32];
				strunpack(entryPoint, name);
				entryPoint[0] = '@';
				entryPoint[0] = 'y';
				entryPoint[0] = 'T';
				entryPoint[0] = '_';
				YSI_g_sPTasks[YSI_g_sPTaskCount] = GetPublicAddressFromName(entryPoint);
				//YSI_g_sPTasks[YSI_g_sPTaskCount] = playerid; // Action param.
				ptr = YSI_g_sPTaskCount++;
			}
		}
		case E_TIMER_ACTION_GET:
		{
			// Check if the timer is running for this player.
			return !!results[playerid];
		}
		case E_TIMER_ACTION_START:
		{
			if (results[playerid])
			{
				KillTimer(results[playerid]);
			}
			results[playerid] = SetTimerEx(name, interval, true, "i", playerid);
		}
		case E_TIMER_ACTION_START_ALL:
		{
			FOREACH__ (playerid : Player)
			{
				if (results[playerid])
				{
					KillTimer(results[playerid]);
				}
				results[playerid] = SetTimerEx(name, interval, true, "i", playerid);
			}
		}
		case E_TIMER_ACTION_STOP:
		{
			if (results[playerid])
			{
				KillTimer(results[playerid]);
				results[playerid] = 0;
			}
		}
		case E_TIMER_ACTION_STOP_ALL:
		{
			FOREACH__ (playerid : Player)
			{
				if (results[playerid])
				{
					KillTimer(results[playerid]);
				}
			}
		}
	}
	return false;
}

