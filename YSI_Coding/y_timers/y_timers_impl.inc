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

// Disable this version!

static stock
	Alloc:YSI_g_sLastSlot = NO_ALLOC,
	Alloc:YSI_g_sFirstSlot = NO_ALLOC,
	YSI_g_sPlayerTimers = -1,
	YSI_g_sUserId = 0,
	Alloc:YSI_g_sTimerList = NO_ALLOC;

stock
	Timer:_YSI_g_sCurrentTimer = Timer:0;

public OnCodeInit()
{
	P:1("hook Timers_OnYSIInit called");
	new
		pointer = 0,
		time = 0,
		idx = 0,
		publicTableEntry = 0;
	while ((idx = AMX_GetPublicEntryPrefix(idx, publicTableEntry, _A<@yT_>)))
	{
		P:6("Timer_OnYSIInit: publicTableEntry: %d", publicTableEntry);
		#emit LREF.S.pri publicTableEntry
		#emit STOR.S.pri pointer
		//YSI_g_sCurFunc = pointer;
		// Don't bother with the real name, call the function by address to get
		// the time the function runs for.
		P:7("Timer_OnYSIInit: pointer: %d", pointer);
		// Push the address of the current function.
		#emit PUSH.S     pointer
		#emit PUSH.C     0xFFFFFFFF // -1: Initial list action for `_Timer_D`.
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit STOR.S.pri time
		//YSI_g_sCurFunc = 0;
		P:7("Timer_OnYSIInit: time: %d", time);
		if (time != -1)
		{
			// Find all the functions with the same time.  This is less
			// efficient than previous implementations (it is O(N^2)), but also
			// more robust as it won't fail no matter how many different times
			// there are - old ones relied on an array with a finite size.
			new
				pointer2 = 0,
				time2 = 0,
				idx2 = 0,
				total = 0,
				pre = 0;
			while ((idx2 = AMX_GetPublicPointerPrefix(idx2, pointer2, _A<@yT_>)))
			{
				// Call the functions a second time to guarantee getting
				#emit PUSH.C     0
				#emit PUSH.C     0xFFFFFFFF
				#emit PUSH.C     8
				#emit LCTRL      6
				#emit ADD.C      36
				#emit LCTRL      8
				#emit PUSH.pri
				#emit LOAD.S.pri pointer2
				#emit SCTRL      6
				#emit STOR.S.pri time2
				// Check if the new time is a FACTOR, SAME, or MULTIPLE of this
				// task, so we don't start different timers together.
				if (time2 == time || time / time2 * time2 == time || time2 / time * time == time2)
				{
					++total;
					if (idx2 < idx)
					{
						++pre;
					}
				}
			}
			P:7("Timer_OnYSIInit: total: %d, time: %d, pre: %d", total, time, pre);
			// Now we know what time this function has, how many others have
			// that time and how many have already been started.
			new
				buffer[FUNCTION_LENGTH];
			publicTableEntry += 4;
			#emit LREF.S.pri publicTableEntry
			#emit STOR.S.pri pointer
			AMX_ReadString(AMX_BASE_ADDRESS + pointer, buffer);
			P:7("Timer_OnYSIInit: %s", Unpack(buffer));
			// Get the time offset for the current call.  This should mean that
			// all the functions are nicely spread out.
			YSI_SetTimerEx(buffer, time * pre / total, false, "ii", 1, -1);
		}
	}
	P:1("hook Timers_OnYSIInit ended");
	
	#if defined Timers_OnCodeInit
		Timers_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Timers_OnCodeInit
#if defined Timers_OnCodeInit
	forward Timers_OnCodeInit();
#endif

HOOK__ OnPlayerConnect(playerid)
{
	P:1("hook Timers_OnPlayerConnect called: %d", playerid);
	// Loop through all the per-player timers.  Correctly finds them all from a
	// linked list hidden in static variables (which are really global).
	new
		cur = YSI_g_sPlayerTimers,
		data = 0;
	while (cur != -1)
	{
		#emit LREF.S.pri  cur
		#emit STOR.S.pri  data
		P:6("Timers_OnPlayerConnect: func: %x", data);
		// Start this timer for this player.
		#emit PUSH.S     playerid
		#emit PUSH.C     1
		// Push the parameter count (in bytes).  This is actually passed to
		// native functions directly.
		#emit PUSH.C     8
		// Call the function currently in the list to trigger the repeating
		// timer.  This involves getting the current "cip" address, modifying it
		// to get the return address then modifying "cip" to call the function.
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri data
		#emit SCTRL      6
		// Returned, get the next list element.
		cur += 4;
		#emit LREF.S.pri  cur
		#emit STOR.S.pri  cur
	}
	P:1("hook Timers_OnPlayerConnect ended");
	return 1;
}

HOOK__ OnPlayerDisconnect(playerid, reason)
{
	P:1("hook Timers_OnPlayerDisconnect called: %d, %d, playerid, reason");
	// Loop through all the per-player timers.  Correctly finds them all from a
	// linked list hidden in static variables (which are really global).
	new
		cur = YSI_g_sPlayerTimers,
		data = 0;
	while (cur != -1)
	{
		#emit LREF.S.pri  cur
		#emit STOR.S.pri  data
		P:6("Timers_OnPlayerDisconnect: func: %x", data);
		// End this timer for this player.
		#emit PUSH.S     playerid
		#emit PUSH.C     0
		// Push the parameter count (in bytes).  This is actually passed to
		// native functions directly.
		#emit PUSH.C     8
		// Call the function currently in the list to trigger the repeating
		// timer.  This involves getting the current "cip" address, modifying it
		// to get the return address then modifying "cip" to call the function.
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri data
		#emit SCTRL      6
		// Returned, get the next list element.
		cur += 4;
		#emit LREF.S.pri  cur
		#emit STOR.S.pri  cur
	}
	P:1("hook Timers_OnPlayerDisconnect ended");
	return 1;
}

stock _Timer_I(const func[], interval, action, &result)
{
	P:3("_Timer_I called");
	switch (action)
	{
		case 0:
		{
			if (result)
			{
				KillTimer(result),
				result = 0;
			}
		}
		case 1:
		{
			if (!result)
			{
				result = YSI_SetTimer(func, interval, true);
			}
		}
	}
	return interval;
}

// Attempt to stop or start a task, possibly for a single player.
stock _Timer_D(const func[], interval, const action, who, results[], a[2])
{
	P:3("_Timer_D called");
	switch (action)
	{
		case -1:
		{
			if (who)
			{
				// Add this timer to the global linked list.
				a[0] = who;
				a[1] = YSI_g_sPlayerTimers;
				// Store the address of the global array.
				#emit LOAD.S.pri  a
				#emit STOR.pri    YSI_g_sPlayerTimers
			}
		}
		case 0:
		{
			// Stop the timer.
			if (who == -1)
			{
				FOREACH__ (who : Player)
				{
					if (results[who])
					{
						KillTimer(results[who]);
						results[who] = 0;
					}
				}
			}
			else if (results[who])
			{
				KillTimer(results[who]);
				results[who] = 0;
			}
		}
		case 1:
		{
			// Start the timer.
			if (who == -1)
			{
				FOREACH__ (who : Player)
				{
					if (!results[who])
					{
						results[who] = YSI_SetTimerEx(func, interval, true, "i", who);
					}
				}
			}
			else if (!results[who])
			{
				results[who] = YSI_SetTimerEx(func, interval, true, "i", who);
			}
		}
	}
	// No global interval for per-player timers.
	return -1;
}

static stock Alloc:Timer_GetSingleSlot(len)
{
	// Allocates memory and secretly appends data to the start.
	++len;
	P:4("Timer_GetSingleSlot called: %d", len);
	// `6` is for the timer header, `- 1` for `++` above.  Slots:
	//
	// 0 - Next.
	// 1 - Native timer ID.
	// 2 - Repeat count remaining.
	// 3 - Repeat count total (or count for `0`).
	// 4 - User timer ID.
	// 5 - Next existing timer.
	//
	new
		Alloc:slot = malloc(len ? len : (6 - 1));
	if (slot == NO_ALLOC)
	{
		return NO_ALLOC;
	}
	P:5("Timer_GetSingleSlot: %d, %d, %d", _:YSI_g_sFirstSlot, _:YSI_g_sLastSlot, _:slot);
	// Standard linked list.
	if (YSI_g_sFirstSlot == NO_ALLOC)
	{
		if (len)
		{
			// Initial value allocation to store the timer ID.
			Timer_GetSingleSlot(-1);
			mset(YSI_g_sLastSlot, 0, _:slot);
		}
		else
		{
			YSI_g_sFirstSlot = slot;
		}
	}
	else
	{
		mset(YSI_g_sLastSlot, 0, _:slot);
	}
	mset(slot, 0, -1);
	YSI_g_sLastSlot = slot;
	return slot;
}

static stock Alloc:_Timer_Get(Timer:slot)
{
	new Alloc:cur = YSI_g_sTimerList;
	while (cur != NO_ALLOC)
	{
		if (Timer:mget(cur, 4) == slot)
		{
			return cur;
		}
		cur = Alloc:mget(cur, 5);
	}
	return NO_ALLOC;
}

stock Timer_GetCallCount(Timer:slot = Timer:0)
{
	if (!slot)
	{
		slot = _YSI_g_sCurrentTimer;
	}
	if ((slot = Timer:_Timer_Get(slot)))
	{
		new count = mget(Alloc:slot, 2);
		// Repeat forever, or repeat N?  If forever, `count` is `0` and slto 3 is
		// the true count.
		return mget(Alloc:slot, 3) - count;
	}
	return -1;
}

stock bool:Timer_IsRunning(Timer:slot = Timer:0)
{
	if (!slot)
	{
		slot = _YSI_g_sCurrentTimer;
	}
	return _Timer_Get(slot) != NO_ALLOC;
}

// Allocate memory to store a string.
stock _Timer_S(const string:str[])
{
	P:3("_Timer_S called");
	new
		len = strlen(str);
	if (len & 0x0F)
	{
		len = (len & ~0x0F) + 32;
	}
	new
		Alloc:slot = Timer_GetSingleSlot(len + 1);
	if (slot != NO_ALLOC)
	{
		msets(slot, 1, str);
	}
	P:5("str: %d", _:slot);
	return _:slot + 1;
}

// Allocate memory to store an array.
stock _Timer_A(const str[], len)
{
	P:3("_Timer_A called");
	new
		Alloc:slot = Timer_GetSingleSlot(len);
	if (slot != NO_ALLOC)
	{
		mseta(slot, 1, str, len);
	}
	P:5("str: %d", _:slot);
	return _:slot + 1;
}

// Create the timer setup.
stock Timer:_Timer_C(timerID)
{
	P:3("_Timer_C called: %d", timerID);
	// This is done here for convenience.
	I@ = -1;
	// Only repeating timers are freed like this.
	// UPDATE: Now all timers with array parameters, regardless of repeat status
	// are freed like this.  Only timers with no malloc aren't.
	// UPDATE 2: Now ALL timers are freed like this, because we need an ID we
	// can know in advance.
	mset(YSI_g_sFirstSlot, 1, timerID);
	// Set the ID we return to the user.
	if (++YSI_g_sUserId == 0)
	{
		++YSI_g_sUserId;
	}
	mset(YSI_g_sFirstSlot, 4, YSI_g_sUserId);
	mset(YSI_g_sFirstSlot, 5, _:YSI_g_sTimerList);
	mset(YSI_g_sFirstSlot, 6, _:NO_ALLOC);
	if (YSI_g_sTimerList != NO_ALLOC)
	{
		mset(YSI_g_sTimerList, 6, _:YSI_g_sFirstSlot);
	}
	YSI_g_sTimerList = YSI_g_sFirstSlot;
	// Just so it isn't a real timer ID (or possibly isn't).
	YSI_g_sFirstSlot = NO_ALLOC;
	YSI_g_sLastSlot = NO_ALLOC;
	return Timer:YSI_g_sUserId;
}

// Allocate the ID.
stock _Timer_B(repeatCount)
{
	P:3("_Timer_B called: %d", repeatCount);
	if (YSI_g_sFirstSlot == NO_ALLOC)
	{
		Timer_GetSingleSlot(-1);
	}
	P:5("_Timer_B: slot = %d", _:YSI_g_sFirstSlot);
	if (YSI_g_sFirstSlot == NO_ALLOC)
	{
		// Not a graceful fail!
		return 0;
	}
	mset(YSI_g_sFirstSlot, 2, repeatCount);
	if (repeatCount)
	{
		mset(YSI_g_sFirstSlot, 3, repeatCount);
	}
	else
	{
		mset(YSI_g_sFirstSlot, 3, 0);
	}
	// Just so it isn't a real timer ID (or possibly isn't).
	return _:YSI_g_sFirstSlot;
}

// Free all timer resources.
stock _Timer_F(Timer:slot = Timer:0, force = 0)
{
	P:3("_Timer_F called");
	// This is done here for convenience.
	// Always called with the first ID.
	switch (force)
	{
	case 0:
	{
		if (!(slot = _YSI_g_sCurrentTimer))
		{
			return 0;
		}
		// "next"
		force = mget(Alloc:slot, 2);
		if (--force == -1)
		{
			// Repeat forever, update the count.
			mset(Alloc:slot, 3, mget(Alloc:slot, 3) + 1);
			return 0;
		}
		else if (force)
		{
			// Decremented the count, still runs left.
			mset(Alloc:slot, 2, force);
			return 0;
		}
	}	
	case 1:
	{
		// Given an ID.
		if (!(slot = Timer:_Timer_Get(slot)))
		{
			return 0;
		}
	}
	case 2:
	{
		// Current timer.
		if (!(slot = _YSI_g_sCurrentTimer))
		{
			return 0;
		}
		// Clear the current timer ID.
		_YSI_g_sCurrentTimer = Timer:0;
	}
	}
	// Remove from the list.
	new
		Alloc:next = Alloc:mget(Alloc:slot, 5),
		Alloc:prev = Alloc:mget(Alloc:slot, 6);
	if (prev == NO_ALLOC)
	{
		// First timer.
		YSI_g_sTimerList = next;
	}
	else
	{
		mset(prev, 5, _:next);
	}
	if (next != NO_ALLOC)
	{
		mset(next, 6, _:prev);
	}
	// Kill time timer.
	KillTimer(mget(Alloc:slot, 1));
	do
	{
		// Free all the slots in the linked list of allocations.
		force = mget(Alloc:slot, 0);
		P:6("_Timer_F: slot = %d, next = %d", _:slot, force);
		free(Alloc:slot);
	}
	while ((_:slot = force) != -1);
	return 1;
}

#define TASK__%0[%1](%2) @yT_%0(g,p);@yT_%0(g,p){static s=0;return _Timer_I(#%0,%1,g,s);}%0();public%0()

// 
#define PTASK__%0[%1](%2) @yT_%0(g,p);@yT_%0(g,p){static s[MAX_PLAYERS]={0,...},a[2];return _Timer_D(#%0,%1,g,p,s,a);}%0(%2);public%0(%2)

#define _yT@%0\32; _yT@
#define @_yT%0\32; @_yT
#define @yT_%0\32; @yT_

#define PAUSE__%0; {J@=_:@Ym:@yT_%0(0,-1);}
#define RESUME__%0; {J@=_:@Ym:@yT_%0(1,-1);}
#define @Ym:%0[%1](%2,-1) %0(%2,%1)

#if YSI_KEYWORD(stop)
	#define stop STOP__
#endif
#if YSI_KEYWORD(defer)
	#define defer DEFER__
#endif
#if YSI_KEYWORD(repeat)
	#define repeat REPEAT__
#endif
#if YSI_KEYWORD(task)
	#define task%0[%1]%3(%2) TASK__%0[%1]%3(%2)
#endif
#if YSI_KEYWORD(ptask)
	#define ptask%0[%1]%3(%2) PTASK__%0[%1]%3(%2)
#endif
#if YSI_KEYWORD(pause)
	#define pause PAUSE__
#endif
#if YSI_KEYWORD(resume)
	#define resume RESUME__
#endif
#if YSI_KEYWORD(timerfunc)
	#define timerfunc%0[%1]%3(%2) TIMER__%0[%1]%3(%2)
#endif
#if YSI_KEYWORD(timer)
	#define timer%0[%1]%3(%2) TIMER__%0[%1]%3(%2)
#endif

