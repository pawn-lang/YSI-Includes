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

// Disable this version!

static stock
	Alloc:YSI_g_sLastSlot = NO_ALLOC,
	Alloc:YSI_g_sFirstSlot = NO_ALLOC,
	YSI_g_sPlayerTimers = -1;

hook OnScriptInit()
{
	P:1("hook Timers_OnScriptInit called");
	new
		pointer,
		time,
		idx,
		entry;
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yT_>)))
	//while ((idx = AMX_GetPublicPointerSuffix(idx, pointer, _A<@yT_>)))
	{
		P:6("Timer_OnScriptInit: entry: %d", entry);
		#emit LREF.S.pri entry
		#emit STOR.S.pri pointer
		//YSI_g_sCurFunc = pointer;
		// Don't bother with the real name, call the function by address to get
		// the time the function runs for.
		P:7("Timer_OnScriptInit: pointer: %d", pointer);
		// Push the address of the current function.
		#emit PUSH.S     pointer
		#emit PUSH.C     0xFFFFFFFF
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit STOR.S.pri time
		//YSI_g_sCurFunc = 0;
		P:7("Timer_OnScriptInit: time: %d", time);
		if (time != -1)
		{
			// Find all the functions with the same time.  This is less
			// efficient than previous implementations (it is O(N^2)), but also
			// more robust as it won't fail no matter how many different times
			// there are - old ones relied on an array with a finite size.
			new
				pointer2,
				time2,
				idx2,
				total,
				pre;
			while ((idx2 = AMX_GetPublicPointerPrefix(idx2, pointer2, _A<@yT_>)))
			{
				// Call the functions a second time to guarantee getting
				#emit PUSH.C     0
				#emit PUSH.C     0xFFFFFFFF
				#emit PUSH.C     8
				#emit LCTRL      6
				#emit ADD.C      28
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
			P:7("Timer_OnScriptInit: total: %d, time: %d, pre: %d", total, time, pre);
			// Now we know what time this function has, how many others have
			// that time and how many have already been started.
			new
				buffer[32];
			entry += 4;
			#emit LREF.S.pri entry
			#emit STOR.S.pri pointer
			AMX_ReadString(AMX_BASE_ADDRESS + pointer, buffer);
			P:7("Timer_OnScriptInit: %s", unpack(buffer));
			// Get the time offset for the current call.  This should mean that
			// all the functions are nicely spread out.
			SetTimerEx(buffer, time * pre / total, 0, "ii", 1, -1);
		}
	}
	P:1("hook Timers_OnScriptInit ended");
	return 1;
}

hook OnPlayerConnect(playerid)
{
	P:1("hook Timers_OnPlayerConnect called: %d", playerid);
	// Loop through all the per-player timers.  Correctly finds them all from a
	// linked list hidden in static variables (which are really global).
	new
		cur = YSI_g_sPlayerTimers,
		data;
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
		#emit ADD.C      28
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

hook OnPlayerDisconnect(playerid, reason)
{
	P:1("hook Timers_OnPlayerDisconnect called: %d, %d, playerid, reason");
	// Loop through all the per-player timers.  Correctly finds them all from a
	// linked list hidden in static variables (which are really global).
	new
		cur = YSI_g_sPlayerTimers,
		data;
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
		#emit ADD.C      28
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

stock _Timer_I(func[], interval, action, &result)
{
	P:3("_Timer_I called");
	switch (action)
	{
		case 0:
		{
			if (result != -1)
			{
				KillTimer(result),
				result =- 1;
			}
		}
		case 1:
		{
			if (result == -1)
			{
				result = SetTimer(func, interval, 1);
			}
		}
	}
	return interval;
}

// Attempt to stop or start a task, possibly for a single player.
stock _Timer_D(func[], interval, const action, who, results[MAX_PLAYERS], a[2])
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
				foreach (who : Player)
				{
					if (results[who] != -1)
					{
						KillTimer(results[who]);
						results[who] = -1;
					}
				}
			}
			else if (results[who] != -1)
			{
				KillTimer(results[who]);
				results[who] = -1;
			}
		}
		case 1:
		{
			// Start the timer.
			if (who == -1)
			{
				foreach (who : Player)
				{
					if (results[who] == -1)
					{
						results[who] = SetTimerEx(func, interval, true, "i", who);
					}
				}
			}
			else if (results[who] == -1)
			{
				results[who] = SetTimerEx(func, interval, true, "i", who);
			}
		}
	}
	// No global interval for per-player timers.
	return -1;
}

static stock Alloc:Timer_GetSingleSlot(len)
{
	// Allocates memory and secretly appends data to the start.
	P:4("Timer_GetSingleSlot called: %d", len);
	new
		Alloc:slot = malloc(len + 1);
	if (slot == NO_ALLOC)
	{
		return NO_ALLOC;
	}
	P:5("Timer_GetSingleSlot: %d, %d, %d", _:YSI_g_sFirstSlot, _:YSI_g_sLastSlot, _:slot);
	// Standard linked list.
	if (YSI_g_sFirstSlot == NO_ALLOC)
	{
		YSI_g_sFirstSlot = slot;
	}
	else
	{
		mset(YSI_g_sLastSlot, 0, _:slot);
	}
	YSI_g_sLastSlot = slot;
	mset(YSI_g_sLastSlot, 0, -1);
	return slot;// + Alloc:1;
}

// Allocate memory to store a string.
stock _Timer_S(string:str[])
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
stock _Timer_A(str[], len)
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

//stock
//	I@ = -1;

// Create the timer setup.
stock _Timer_C(tt, g)
{
	P:3("_Timer_C called: %d, %d", tt, g);
	//P:3("_Timer_C called: %d", tt);
	// This is done here for convenience.
	I@ = -1;
	// Only repeating timers are freed like this.
	// UPDATE: Now all timers with array parameters, regardless of repeat status
	// are freed like this.  Only timers with no malloc aren't.
	if (g)
	{
		new
			Alloc:slot = Timer_GetSingleSlot(1);
		P:5("_Timer_C: slot = %d", _:slot);
		if (slot == NO_ALLOC)
		{
			// Not a graceful fail!
			return 0;
		}
		mset(slot, 1, tt);
		// Just so it isn't a real timer ID (or possibly isn't).
		slot = ~YSI_g_sFirstSlot;// ^ Alloc:-1;
		YSI_g_sFirstSlot = NO_ALLOC;
		YSI_g_sLastSlot = NO_ALLOC;
		return _:slot;
	}
	// Reset these variables on all timers, including self-cleaning ones.
	YSI_g_sFirstSlot = NO_ALLOC;
	YSI_g_sLastSlot = NO_ALLOC;
	return tt;
}

// Free all timer resources.
stock _Timer_F(slot)
{
	P:3("_Timer_F called");
	// This is done here for convenience.
	if (slot & 0x80000000)
	{
		new
			next;
		slot = ~slot; //^= -1;
		for ( ; ; )
		{
			next = mget(Alloc:slot, 0);
			P:6("_Timer_F: slot = %d, next = %d", slot, next);
			// Out of stored strings and arrays.
			if (next == -1)
			{
				KillTimer(mget(Alloc:slot, 1));
				free(Alloc:slot);
				break;
			}
			free(Alloc:slot);
			slot = next;
		}
	}
	else
	{
		KillTimer(slot);
	}
	return 1;
}

stock _Timer_H(slot)
{
	_Timer_F(~(slot - 1));
}

#define task%0[%1](%2) @yT_%0(g,p);@yT_%0(g,p){static s=-1;return _Timer_I(#%0,%1,g,s);}%0();public%0()

// 
#define ptask%0[%1](%2) @yT_%0(g,p);@yT_%0(g,p){static s[MAX_PLAYERS]={-1,...},a[2];return _Timer_D(#%0,%1,g,p,s,a);}%0(%2);public%0(%2)

#define @yT_%0\32;%1(%2) @yT_%0%1(%2)
//#define @_yT%0;\32%1(%2) @_yT%0%1(%2)

#define pause%0; {J@=_:@Ym:@yT_%0(0,-1);}
#define resume%0; {J@=_:@Ym:@yT_%0(1,-1);}
#define @Ym:%0[%1](%2,-1) %0(%2,%1)

#define timerfunc YSI_timer

#if !defined YSI_NO_timer
	#define timer YSI_timer
#endif

