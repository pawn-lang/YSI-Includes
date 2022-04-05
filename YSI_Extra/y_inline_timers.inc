#if defined _INC_y_inline_timers
	#endinput
#endif
#define _INC_y_inline_timers

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

#if !defined _INC_y_inline
	#tryinclude "..\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI\YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#error Could not find y_inline
#endif

static stock
	YSI_gsCalls = 0;

forward @y_inlineTimerCount(Func:func<>, time, count, due);

public @y_inlineTimerCount(Func:func<>, time, count, due)
{
	--count;
	@.func();
	if (count == 0)
	{
		Indirect_Release(func);
		P:7("y_inlineTimerCount ending: %d (%d)", _:func, ++YSI_gsCalls);
	}
	else
	{
		// Run again, to track the count.  Reduce jitter by tracking due times.
		//printf("%d %d %d", time, due, GetTickCount());
		new timer = time + (due - GetTickCount());
		//printf("delay = %d", timer);
		timer = YSI_SetTimerEx("@y_inlineTimerCount", timer < 0 ? 0 : timer, false, "iiii", _:func, time, count, due + time);
		Indirect_SetMeta(func, timer);
		P:7("y_inlineTimerCount calls: %d (%d), %d", _:func, ++YSI_gsCalls, timer);
	}
}

forward @y_inlineTimerRepeat(Func:func<>);

public @y_inlineTimerRepeat(Func:func<>)
{
	// Normal repeating timer.
	@.func();
}

forward @y_inlineTimerStart(Func:func<>, time, due);

public @y_inlineTimerStart(Func:func<>, time, due)
{
	// Initial repeating timer, to set the time offset.
	//printf("%d %d %d", time, due, GetTickCount());
	new timer = time + (due - GetTickCount());
	//printf("delay = %d", timer);
	timer = YSI_SetTimerEx("@y_inlineTimerRepeat", timer < 0 ? 0 : timer, true, "i", _:func);
	Indirect_SetMeta(func, timer);
	// Call the function after setting the meta, incase it kills the timer.
	@.func();
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Function to call on a timer.</param>
 * <param name="initial">Delay before first call.</param>
 * <param name="time">Delay between subsequent calls.</param>
 * <param name="count">How many times to call it.</param>
 * <remarks>
 *  There are several ways to use this function:
 *  
 *  <c>SetCallbackTimer(func, 100);</c>
 *  Calls the function once every 100ms.
 *  
 *  <c>SetCallbackTimer(func, 100, 0);</c>
 *  Same as above (count is <c>0</c>, which means repeat forever).
 *  
 *  <c>SetCallbackTimer(func, 100, 5);</c>
 *  Calls the function once every 100ms, but only 5 times.
 *  
 *  <c>SetCallbackTimer(func, 100, 200, 0);</c>
 *  Calls the function once every 200ms, but the first call is after just 100ms.
 *  
 *  <c>SetCallbackTimer(func, 100, 200, 42);</c>
 *  Calls the function 42 times, first after 100ms, then every 200ms.
 *  
 *  When only one parameter is given its <c>time</c>.
 *  
 *  When two parameters are given they're <c>time</c> and <c>count</c>.
 *  
 *  When all three parameters are given they're <c>initial</c>, <c>time</c>,
 *  and <c>count</c>.
 *  
 *  Count is NOT like <c>repeat</c> in <c>SetTimer</c>.  <c>0</c> means repeat
 *  forever, anything not <c>0</c> means call it exactly that many times.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Timer_CreateCallback(Func:func<>, initialOrTime, timeOrCount = 0, count = -1)
{
	if (count == -1)
	{
		// No `initial` time.
		count = timeOrCount;
		timeOrCount = initialOrTime;
	}
	if (count < 0)
	{
		return 0;
	}
	if (count == 0)
	{
		// Repeat forever, but DON'T repeat here, this is just the initial offset time.
		Indirect_Claim(func);
		new timer = YSI_SetTimerEx("@y_inlineTimerStart", initialOrTime, false, "iii", _:func, timeOrCount, GetTickCount() + initialOrTime);
		Indirect_SetMeta(func, timer);
	}
	else
	{
		// Repeat N times.
		Indirect_Claim(func);
		new timer = YSI_SetTimerEx("@y_inlineTimerCount", initialOrTime, false, "iiii", _:func, timeOrCount, count, GetTickCount() + initialOrTime);
		Indirect_SetMeta(func, timer);
	}
	return _:func;
}

#pragma deprecated Use `Timer_CreateCallback`.
stock SetCallbackTimer(Func:func<>, initialOrTime, timeOrCount = 0, count = -1)
{
	return Timer_CreateCallback(func, initialOrTime, timeOrCount, count);
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Timer to kill.</param>
 * <remarks>
 *  Kill a timer created by <c>SetCallbackTimer</c>.  Normal <c>KillTimer</c>
 *  won't work for them.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Timer_KillCallback(func)
{
	new timer = Indirect_GetMeta(func);
	Indirect_Release(func);
	return KillTimer(timer);
}

#pragma deprecated Use `Timer_KillCallback`.
stock KillCallbackTimer(func)
{
	return Timer_KillCallback(func);
}

