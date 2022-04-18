/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

// Better handling of operator precedences and floating point numbers.  This
// will now work for ALL regular numbers (including -0.5 which broke the old
// version).  I don't know of any complex expressions that break it with
// operator precedences, but I'm not ruling it out.  The brackets do try and
// account for that possibility, but I just don't know.
#define NO_VALUE(%0) ((2*%0-1)==2*(%0-1))

#define UNSIGNED(%0) ((%0) - cellmin)

#define FLOAT_INFINITY                  (Float:0x7F800000)
#define FLOAT_NEG_INFINITY              (Float:0xFF800000)
#define FLOAT_NEGATIVE_INFINITY         (Float:0xFF800000)
#define FLOAT_NAN                       (Float:0x7FFFFFFF)
#define FLOAT_NOT_A_NUMBER              (Float:0x7FFFFFFF)
#define FLOAT_QNAN                      (Float:0x7FFFFFFF)
#define FLOAT_QUIET_NAN                 (Float:0x7FFFFFFF)
#define FLOAT_QUIET_NOT_A_NUMBER        (Float:0x7FFFFFFF)
#define FLOAT_SNAN                      (Float:0x7FBFFFFF)
#define FLOAT_SIGNALING_NAN             (Float:0x7FBFFFFF)
#define FLOAT_SIGNALING_NOT_A_NUMBER    (Float:0x7FBFFFFF)
#define FLOAT_E                         (Float:0x402DF854) // e
#define FLOAT_PI                        (Float:0x40490FDB) // pi
#define FLOAT_ROOT_2                    (Float:0x3FB504F3) // sqrt(2)
#define FLOAT_EPSILON                   (Float:0x00000001) // https://en.wikipedia.org/wiki/Machine_epsilon

#define IS_NAN(%0) (_:((Float:0x7FFFFFFF) & (%0)) > (0x7F800000))

//#pragma unused TRUE, FALSE, NULL

#define __TY|||%0||| (1000000)
#define __TX:__TY|||%0,%1||| (%1)
#define __TF=fopen(%0,%2"%3",%4) __TF=fopen(%0".csv",%4)

#if !defined TIMING_ITERATIONS
	#define TIMING_ITERATIONS (10)
#endif

#define ALS_MRET_(%0) forward PP_MRET();public PP_MRET(%0)(0,0,YSI_EMPTY)(NT_US)

/*-------------------------------------------------------------------------*//**
 * <param name="t">The time in ms.</param>
 * <param name="iters">The number of iterations completed in this time.</param>
 * <remarks>
 *  Formats and returns a string representing the time taken for one iteration,
 *  given the time required for many iterations.  This attempts to format the
 *  number using a reasonable fraction of a second.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock BeautifyProfilingTime(t, iters)
{
	// Number of times run.  Accounts for the string and optional count.
	new
		ret[20];
	if      (iters >  1000000000)
		format(ret, sizeof (ret), "%.2fps", float(t) / (float(iters) / 1000000000.0));
	else if (iters == 1000000000)
		format(ret, sizeof (ret), "%d.00ps", t);
	else if (iters >  1000000)
		format(ret, sizeof (ret), "%.2fns", float(t) / (float(iters) / 1000000.0));
	else if (iters == 1000000)
		format(ret, sizeof (ret), "%d.00ns", t);
	else if (iters >  1000)
		format(ret, sizeof (ret), "%.2fus", float(t) / (float(iters) / 1000.0));
	else if (iters == 1000)
		format(ret, sizeof (ret), "%d.00us", t);
	else if (iters >  1)
		format(ret, sizeof (ret), "%.2fms", float(t) / float(iters));
	else
		format(ret, sizeof (ret), "%d.00ms", t);
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The name of the profile.</param>
 * <param name="timings">The raw profiling results.</param>
 * <param name="iters">The number of iterations per run.</param>
 * <param name="size">The number of repeats.</param>
 * <remarks>
 *  "WTF" here stands for "Write To File".  The output looks like:
 *  
 *  <code>
 *      timestamp,runs,repeats,results (ms)
 *      1546082820,10,1000000,122,121,121,120,121,121,121,119,119,121
 *      1546082822,10,1000000,123,124,123,123,121,121,121,120,122,122
 *  </code>
 *  
 *  The timestamp is the unix timestamp at which the line was WRITTEN, not the
 *      time at which the profilings started or ended.
 *  
 *  "runs" is the number of times the whole profile was repeated.
 *  
 *  "repeats" is the number of times the code was run for each repeat.
 *  
 *  "results" are the total times for each repeat, in milliseconds.  The time
 *      for an individual piece of code is <c>result[n] / repeats</c>.  This is
 *      equivalent to:
 *  
 *  <code>
 *      for (new i = 0; i != runs; ++i)
 *      {
 *          start = GetTickCount();
 *          for (new i = 0; i != repeats; ++i)
 *          {
 *              USER_CODE_HERE();
 *          }
 *          end = GetTickCount();
 *          WriteToFile(end - start);
 *      }
 *  </code>
 *  
 *  The repeats help to time very short pieces of code.  The runs help to
 *  average.  The console reports average results (mean, mode, median, range).
 *  Thus the even more accurate result for a single iteration would be:
 *  <c>sum(results) / (runs * repeats)</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// "Write To File", not another "WTF" meaning...
stock DumpProfilingTime(const name[], const timings[], iters, size = sizeof (timings))
{
	new File:fhnd = File:0;
	if (fexist(name))
	{
		// File already exists.  Append.
		fhnd = fopen(name, io_append);
	}
	else if ((fhnd = fopen(name, io_write)))
	{
		// File doesn't exist.  Create it and write the headers.
		fwrite(fhnd, "timestamp,runs,repeats,results (ms)\n");
	}
	if (!fhnd)
	{
		P:W("Could not write to profiling results file \"%s\".", name);
		return;
	}
	va_fprintf(fhnd, "%d,%d,%d", gettime(), size, iters);
	for (new i = 0; i != size; ++i)
	{
		va_fprintf(fhnd, ",%d", timings[i]);
	}
	fwrite(fhnd, "\n");
	fclose(fhnd);
}

#if !defined PROFILINGS_FILE
	#define DumpProfilingTime(%0),
#endif

#define RUN_TIMING(%0) \
	for(new __TA[TIMING_ITERATIONS],__TC=sizeof __TA,__TE=_:__TX:__TY|||%0|||,__TS=__PA(%0);__TC;__PB(%0,__TA,__TE)) \
	for(;(__TS=GetTickCount(),__TC);__TA[--__TC]=GetTickCount()-__TS) \
	for(new __TI=0;__TI!=__TE;++__TI)

#if defined _samp_included && !defined YSI_NO_GET_IP
	stock
		YSI_gPlayerIP[MAX_PLAYERS + 1] = {-1, ...};

	public OnPlayerConnect(playerid)
	{
		new
			ip[16];
		GetPlayerIp(playerid, ip, sizeof (ip)),
		YSI_gPlayerIP[playerid] = IPToInt(ip);
		#if defined _y_utils_OnPlayerConnect
			_y_utils_OnPlayerConnect(playerid);
		#endif
		return 1;
	}

	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect _y_utils_OnPlayerConnect

	#if defined _y_utils_OnPlayerConnect
		forward _y_utils_OnPlayerConnect(playerid);
	#endif

	public OnPlayerDisconnect(playerid, reason)
	{
		YSI_gPlayerIP[playerid] = -1;
		#if defined _y_utils_OnPlayerDisconnect
			_y_utils_OnPlayerDisconnect(playerid, reason);
		#endif
		return 1;
	}

	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect _y_utils_OnPlayerDisconnect

	#if defined _y_utils_OnPlayerDisconnect
		forward _y_utils_OnPlayerDisconnect(playerid, reason);
	#endif

	/*-------------------------------------------------------------------------*//**
	 * <param name="playerid">Player to get IP of.</param>
	 * <returns>
	 *  IP as a 32bit int.
	 * </returns>
	 *//*------------------------------------------------------------------------**/

	// Cunning macro only uses "%0" once, yet is still safe.
	P:D(GetIP(playerid));
	#define GetIP(%0) (YSI_gPlayerIP[min((%0) + cellmin, MAX_PLAYERS + cellmin) - cellmin])
#endif

#if defined YSI_LOCK_MODE
	public OnYSIInit()
	{
		new
			find = strfind(YSI_gLockData[5], YSI_gLockData[1]) + 6;
		find = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		new
			found = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		if (strval(YSI_gLockData[found]) ^ UNIQUE_SYMBOL != _LOCK_IP_3 ^ UNIQUE_SYMBOL || strval(YSI_gLockData[find]) - _LOCK_IP_3 != _LOCK_IP_2 - _LOCK_IP_3)
		{
			y_lock 1;
		}
		#if defined _y_utils_OnYSIInit
			_y_utils_OnYSIInit();
		#endif
		return 1;
	}

	#if defined _ALS_OnYSIInit
		#undef OnYSIInit
	#else
		#define _ALS_OnYSIInit
	#endif
	#define OnYSIInit _y_utils_OnYSIInit

	#if defined _y_utils_OnYSIInit
		forward _y_utils_OnYSIInit();
	#endif
#endif

#if !defined __once
	#define __once%1;%0) (__gOnce++)%1;(%0),__gOnce=0)
	#define __gOnce++)%1;(), __gOnce++)%1;
	stock __gOnce = 1;
#endif

#define PP_RIGHT_BRACKET<> )

#define IF__(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)if()
#define SWITCH__(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)switch()

#define for(IF_FAIL:new|||%1;%2) for(IF_PASS:new %1=%2;%1;)

#define IF_FAIL:new%0|||%1;%2)%8() ;__once;)%8(new%0 %1=%2 PP_RIGHT_BRACKET<>
#define IF_PASS:%3;%4;%9)%8() %3;__once;)%8(%4 PP_RIGHT_BRACKET<>

#if YSI_KEYWORD(if)
	#define if(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)if()
#endif

#if YSI_KEYWORD(switch)
	#define switch(new%0\32;%1=%2) for(IF_FAIL:new%0|||%1;%2)switch()
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="value">The unsigned number to compare.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *  An unsigned comparison between the two values.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(bool:UCMP(value, upper));
#define UCMP(%0,%1) IS_IN_RANGE(%0,0,(%1))

/*-------------------------------------------------------------------------*//**
 * <param name="value">The IEEE754 floating point number (<c>Float:</c>) to check.</param>
 * <returns>
 *  An IEEE754 floating-point number is defined as Not-A-Number when all the exponent bits are set,
 *  and the mantissa is non-zero.  The sign bit is ignored, so we first remove that and test the
 *  result is <c>&gt; 0x7F800000</c>.  Because any signed number bigger than that must have all the
 *  MSBs set, plus at least one more.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(bool:IsNaN(Float:value));
#define IsNaN(%0) IS_NAN(%0)

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player to check.</param>
 * <returns>
 *  Is this a valid playerid (NOT, is the player connected).
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(bool:VALID_PLAYERID(playerid));
#define VALID_PLAYERID(%0) UCMP((%0), MAX_PLAYERS)

/*-------------------------------------------------------------------------*//**
 * <param name="value">The number to compare.</param>
 * <param name="lower">The lower limit.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *  Is the value in the given range.
 * </returns>
 * <remarks>
 *  Equivalent to:
 *
 * <code>		(%1) &lt;= (%0) &lt; (%2)</code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:IS_IN_RANGE(value, lower, upper));
#define IS_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin)))

/*-------------------------------------------------------------------------*//**
 * <param name="value">The number to compare.</param>
 * <param name="lower">The lower limit.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *  Is the value outside the given range.
 * </returns>
 * <remarks>
 *  Equivalent to:
 *
 * <code>		(%1) &lt;= (%0) &lt; (%2)</code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:NOT_IN_RANGE(value, lower, upper));
#define NOT_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))>=((%2)-((%1)+cellmin)))

/*-------------------------------------------------------------------------*//**
 * <param name="numerator">The top of the division.</param>
 * <param name="denominator">The bottom of the division.</param>
 * <returns>
 *  (numerator / denominator) rounded up.
 * </returns>
 * <remarks>
 *  Normal integer division ALWAYS rounds down - this always rounds up.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(ceildiv(numerator, denominator));
#if defined ceildiv
	#undef ceildiv
#endif
#if __COMPILER_1ST_PASS
	#define ceildiv __MACRO__ceildiv
#else
	#define ceildiv(%0,%1) (((%0)-1)/(%1)+1)
#endif
#define _ALS_ceildiv

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  floordiv(numerator, denominator);
 * </summary>
 * <param name="numerator">The top of the division.</param>
 * <param name="denominator">The bottom of the division.</param>
 * <returns>
 *  (numerator / denominator) rounded down.
 * </returns>
 * <remarks>
 *  Normal integer division ALWAYS rounds down - this also always rounds down,
 *  making it a little pointless, but also more explicit in function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(floordiv(numerator, denominator));
#if defined floordiv
	#undef floordiv
#endif
#if __COMPILER_1ST_PASS
	#define floordiv __MACRO__floordiv
#else
	#define floordiv(%0,%1) ((%0)/(%1))
#endif
#define _ALS_floordiv

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to check if is null.</param>
 * <remarks>
 *  Uses a new shorter and branchless method, which also works with offsets so
 *  this is valid:
 *
 *  <code>
 *    new str[32]; IsNull(str[5]);
 *  </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:IsNull(const str[]));
#define IsNull(%0) ((%0[(%0[0])=='\1'])=='\0')

#if defined isnull
	#undef isnull
#endif
#define isnull(%0) ((%0[(%0[0])=='\1'])=='\0')
#define _ALS_isnull

//#pragma deprecated Use `IsNull` (i.e. use proper capitalisation).
//stock bool:isnull(const str[])
//{
//	return IsNull(str);
//}

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to check if is odd.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:IsOdd(value));
#define IsOdd(%0) ((%0)&1)

#if defined isodd
	#undef isodd
#endif
#define isodd(%0) ((%0)&1)
#define _ALS_isodd

//#pragma deprecated Use `IsOdd` (i.e. use proper capitalisation).
//stock bool:isodd(const str[])
//{
//	return IsOdd(str);
//}

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to check if is even.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:IsEven(value));
#define IsEven(%0) (~(%0)&1)

#if defined iseven
	#undef iseven
#endif
#define iseven(%0) (~(%0)&1)
#define _ALS_iseven

//#pragma deprecated Use `IsEven` (i.e. use proper capitalisation).
//stock bool:iseven(const str[])
//{
//	return IsEven(str);
//}

/*-------------------------------------------------------------------------*//**
 * <param name="dest">Destination string.</param>
 * <param name="src">Source string.</param>
 * <param name="len">(Implicit) maximum length of the destination.</param>
 *//*------------------------------------------------------------------------**/

P:D(StrCpy(dest[], const src[], len = sizeof (dest)));
#define StrCpy(%0,%1) strcat((%0[0] = '\0', %0), %1)

#if defined strcpy
	#undef strcpy
#endif
#define strcpy(%0,%1) strcat((%0[0] = '\0', %0), %1)
#define _ALS_strcpy

//#pragma deprecated Use `StrCpy` (i.e. use proper capitalisation).
//stock strcpy(dest[], const src[], len = sizeof (dest))
//{
//	return StrCpy(dest, src, len);
//}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to convert.</param>
 * <param name="len">How much of the string to convert.</param>
 *//*------------------------------------------------------------------------**/

stock StrToLower(str[], len = sizeof (str))
{
	new
		i = -1,
		ch = 0;
	while ((ch = str[++i]) && len--)
		str[i] = tolower(ch);
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to convert.</param>
 * <param name="len">How much of the string to convert.</param>
 *//*------------------------------------------------------------------------**/

stock StrToUpper(str[], len = sizeof (str))
{
	new
		i = -1,
		ch = 0;
	while ((ch = str[++i]) && len--)
		str[i] = toupper(ch);
}

/*-------------------------------------------------------------------------*//**
 * <param name="minOrMax">Upper bound, or lower bound with 2+ parameters or when less than naught.</param>
 * <param name="max">Upper bound.</param>
 * <param>Value(s) to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  This uses a compile-
 *   time macro to detect the number of parameters and adjust the implementation
 *   accordingly.  Also when there is only one parameter and it is below naught,
 *   it uses naught as the max and the parameter as the min instead.  Won't
 *   return the value <c>except</c> if it is between the limits.  So can be
 *   called with one, two, or three parameters.  Don't try
 *   <c>Random(0, _, 2);</c> for example, it won't work.  With more than two
 *   parameters all the rest are numbers that should not be returned.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Random(minOrMax, max, ...)
{
	// Here for documentation only.
	return 0;
}
 
/*-------------------------------------------------------------------------*//**
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <param name="">Values to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  Won't return any of
 *   the extra parameter values, so you can do:
 *   <code>
 *     Random(0, 20, 11, 12, 13);
 *   </code>
 *   To randomly select <c>0-10, 14-19</c> (inclusive).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMaxExceptMany(min, max, ...)
{
	assert(min < max);
	// This can't use the same technique as `RandomMinMaxExcept`, because the
	// exception values may not be unique.  That method would fail miserably
	// with `RandomMinMaxExceptMany(0, 4, 1, 1, 1, 1);`
	new args = numargs();
	//new valid = 0;
	//// Count how many excluded values are actually within the random selection
	//// range.
	//for (new i = 2; i != args; ++i)
	//{
	//	if (min <= getarg(i) < max)
	//	{
	//		++valid;
	//	}
	//}
	// Instead we will have to first check that there are valid candidates
	// returns.
	for (new i = min, j; i != max; ++i)
	{
		j = 1;
		while (++j != args)
		{
			// Check if any of the exceptions match this input value.
			if (getarg(j) == i)
			{
				break;
			}
		}
		if (j == args)
		{
			// There is at least one number that can be returned.
			for ( ; ; )
			{
				// Get a random number.
				i = YSI_Random(max - min) + min;
				// Check if it is invalid.
				j = 1;
				while (++j != args)
				{
					// Check if any of the exceptions match this input value.
					if (getarg(j) == i)
					{
						break;
					}
				}
				if (j == args)
				{
					// Not found;
					return i;
				}
			}
		}
	}
	// Will probably fail.  If you get an exception here you called the code
	// with an invalid set of values.
	assert(numargs() == 0);
	return max;
}

/*-------------------------------------------------------------------------*//**
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <param name="except">Value to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Won't return the value <c>except</c> if it is between the limits.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMaxExcept(min, max, except)
{
	assert(min < max);
	if (min <= except < max)
	{
		// Select from one fewer random numbers, and shift the results.
		return (max = YSI_Random(max - 1 - min) + min) + _:(max >= except);
	}
	else
	{
		// The ignored value is outside the range we care about.
		return YSI_Random(max - min) + min;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <remarks>
 *   Generate a random number  between the given numbers (min &lt;= n &lt; max).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMax(min, max)
{
	assert(min < max);
	return YSI_Random(max - min) + min;
}

/*-------------------------------------------------------------------------*//**
 * <param name="max">Upper bound.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  This uses a compile-
 *   time macro to detect the number of parameters and adjust the implementation
 *   accordingly.  Also when there is only one parameter and it is below naught,
 *   it uses naught as the max and the parameter as the min instead.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMax(max)
{
	if (max < 0)
	{
		return -YSI_Random(-max);
	}
	return YSI_Random(max);
}

// The macro to detect one parameter.
#define Random(%0) RandomMax(%0)

// The macro to detect two parameters.
#define RandomMax(%0,%1) RandomMinMax(%0,%1)

// The macro to detect three parameters.
#define RandomMinMax(%0,%1,%2) RandomMinMaxExcept(%0,%1,%2)

// The macro to detect many parameters.
#define RandomMinMaxExcept(%0,%1,%2,%3) RandomMinMaxExceptMany(%0,%1,%2,%3)

/*-------------------------------------------------------------------------*//**
 * <param name="minmax">Lower bound, or upper bound when only parameter.</param>
 * <param name="max">Upper bound.</param>
 * <param name="dp">How small to make the differences</param>
 * <remarks>
 *   Generate a random float between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0.0 (changes the parameter order).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Float:RandomFloat(Float:min, Float:max = FLOAT_NAN, dp = 2)
{
	new
		Float:mul = floatpower(10.0, float(dp));
	switch (dp)
	{
	case 0: mul = 1.0;
	case 1: mul = 10.0;
	case 2: mul = 100.0;
	case 3: mul = 1000.0;
	default: mul = floatpower(10.0, float(dp));
	}
	if (IsNaN(max))
	{
		if (min < 0.0)
			return -(float(random(floatround(-min * mul))) / mul);
		return float(random(floatround(min * mul))) / mul;
	}
	// Parameters are the wrong way around - do it anyway.
	if (max < min)
		return float(random(floatround(min * mul - max * mul))) / mul + max;
	return float(random(floatround(max * mul - min * mul))) / mul + min;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to remove whitespace from the end of.</param>
 * <remarks>
 *   Updated from old versions, should be more efficient
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock StripNL(str[])
{
	P:7("StripNL called: \"%s\"", str);
	new
		i = strlen(str);
	while (i-- && str[i] <= ' ') str[i] = '\0';
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to remove whitespace from the end of.</param>
 * <remarks>
 *   Updated from old versions, should be more efficient
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(StripR(str[]));
#define StripR StripNL

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to remove whitespace from the start of.</param>
 *//*------------------------------------------------------------------------**/

stock StripL(str[])
{
	P:7("StripL called: \"%s\"", str);
	new
		len = strlen(str),
		i = 0;
	while ('\0' < str[i] <= ' ') ++i;
	if (i) memcpy(str[0], str[i], 0, (len - i) * 4, len);
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to remove whitespace from the start and end of.</param>
 *//*------------------------------------------------------------------------**/

stock Strip(str[])
{
	P:7("Strip called: \"%s\"", str);
	new
		len = strlen(str),
		i = len;
	while (i-- && str[i] <= ' ') str[i] = '\0';
	i = 0;
	while ('\0' < str[i] <= ' ') ++i;
	if (i) memcpy(str[0], str[i], 0, (len - i) * 4, len);
}

/*-------------------------------------------------------------------------*//**
 * <param name="line">String to check.</param>
 * <param name="pos">Postion to start from.</param>
 * <remarks>
 *   Checks if the current point in a line is the end of non-whitespace data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:EndOfLine(const line[], pos)
{
	P:7("EndOfLine called: \"%s\", %i", line, pos);
	if (NOT_IN_RANGE(pos, 0, strlen(line))) return false;
	while (IS_IN_RANGE(line[pos], '\0' + 1, ' ' + 1)) ++pos;
	return !line[pos];
}

#pragma deprecated Use `EndOfLine` (i.e. use proper capitalisation).
stock bool:endofline(const line[], pos)
{
	return EndOfLine(line, pos);
}

/*-------------------------------------------------------------------------*//**
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *   Fail - -1, Success - pos
 * </returns>
 *//*------------------------------------------------------------------------**/

stock ChrFind(needle, const haystack[], start = 0)
{
	P:3("chrfind called: %c, \"%s\", %i", needle, haystack, start);
	new search[2];
	search[0] = needle;
	return strfind(haystack, search, false, start);
}

#pragma deprecated Use `ChrFind` (i.e. use proper capitalisation).
stock chrfind(needle, const haystack[], start = 0)
{
	return ChrFind(needle, haystack, start);
}

/*-------------------------------------------------------------------------*//**
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *   Fail - -1, Success - pos
 * </returns>
 * <remarks>
 *   Like <symbolref name="ChrFind" />, but with no upper-bounds check on
 *   <paramref name="start" />.  Now it has them anyway...
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `ChrFind` (i.e. use proper capitalisation, and bounds checks).
stock chrfindp(needle, const haystack[], start = 0)
{
	return ChrFind(needle, haystack, start);
}

/*-------------------------------------------------------------------------*//**
 * <param name="ip">Dot notation IP to convert to an integer.</param>
 *//*------------------------------------------------------------------------**/

stock IPToInt(const ip[])
{
	new
		ipv = strval(ip) << 24,
		pos = 0;
	while (pos < 15 && ip[pos++] != '.') {}
	ipv += strval(ip[pos]) << 16;
	while (pos < 15 && ip[pos++] != '.') {}
	ipv += strval(ip[pos]) << 8;
	while (pos < 15 && ip[pos++] != '.') {}
	return ipv + strval(ip[pos]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="string">the string to hash.</param>
 * <returns>
 *   The bernstein hash of the input string
 * </returns>
 * <remarks>
 *   This is a 32bit hash system so is not very secure, however we're only using
 *   this as a string enumerator to uniquely identify strings easilly and allow
 *   for a binary search of strings based on the hash of their name.
 *   <em>crc32</em>, then <em>jenkins</em> were originally used however this is
 *   far faster, if a little collision prone, but we're checking the strings
 *   manually anyway.  This doesn't matter as it would be done regardless of
 *   hash method, so this doesn't need to be accounted for.  Speed is all that
 *   matters with at least least a bit of non collision (the number of strings
 *   we're dealing with, this should have none-to-few collisions).
 *   <p/>
 *   I modified it slightly from the original code pasted by aru, to code closer
 *   to <a href="http://www.burtleburtle.net/bob/hash/doobs.html">the code</a>
 *   and to work with PAWN (and shaved 0.2us off the time for one call :D).
 *   <p/>
 *   Uber reduced version (just for fun):
 *   <code>
 *   b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
 *   </code>
 *   <p/>
 *   Update: Contrary to what I said above this is also used to identify colour
 *   strings for the updated text system involving file based styling and this
 *   is not checked for collisions as it's unimportant.  But this doesn't affect
 *   the function at all, I just mentioned it here for "interest".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock BernsteinHash(const string[] /* 12 */)
{
	new h = 5381, i = 0, j = 0;
	while ((j = string[i++]))
		h = h * 33 ^ j;
	return h;
}

#pragma deprecated Use `BernsteinHash` (i.e. use proper capitalisation).
stock bernstein(const string[] /* 12 */)
{
	new h = 5381, i = 0, j = 0;
	while ((j = string[i++]))
		h = h * 33 ^ j;
	return h;
}

/*-------------------------------------------------------------------------*//**
 * <param name="string">the string to hash.</param>
 * <returns>
 *   the Jenkins hash of the input string
 * </returns>
 * <remarks>
 *   This is a 32bit hash system so is not very secure, however we're only using
 *   this as a string enumerator to uniquely identify strings easilly and allow
 *   for a binary search of strings based on the hash of their name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock JenkinsHash(const string[] /* 12 */)
{
	new h = 0, i = 0, j = 0;
	while ((j = string[i++]))
		h += j, h += h << 10, h ^= h >> 6;
	return
		h += h << 3,
		h ^= h >> 1,
		h + (h << 15);
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to check.</param>
 * <returns>
 *   true/false.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:IsHex(const str[])
{
	P:3("ishex called: \"%s\"", str);
	new
		i = 0,
		cur = 0;
	if (str[0] == '0' && (str[1] | 0x20) == 'x') i = 2;
	do
	{
		cur = str[i++];
	}
	while (IS_IN_RANGE(cur, '0', '9' + 1) || IS_IN_RANGE(cur | 0x20, 'a', 'f' + 1));
	//while (('0' <= cur <= '9') || ('a' <= (cur | 0x20) <= 'f'));
	return !cur; // Valid if this is the end of the string.
}

#pragma deprecated Use `IsHex` (i.e. use proper capitalisation).
stock bool:ishex(const str[])
{
	return IsHex(str);
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to unpack</param>
 * <returns>
 *   unpacked string
 * </returns>
 * <remarks>
 *   Mainly used for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Unpack(const str[])
{
	P:3("Unpack called: \"%s\"", str);
	new
		ret[YSI_MAX_STRING] = {0};
	if (strlen(str) <= YSI_MAX_STRING)
	{
		strunpack(ret, str);
	}
	return ret;
}

#pragma deprecated Use `Unpack` (i.e. use proper capitalisation).
stock unpack(const str[])
{
	// Doesn't call the original, instead inlines the code because it returns a
	// string, and the compiler doesn't like nested string returning functions.
	P:3("unpack called: \"%s\"", str);
	new
		ret[YSI_MAX_STRING] = {0};
	if (strlen(str) <= YSI_MAX_STRING)
	{
		strunpack(ret, str);
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="idx">Index of the string in the parameters.</param>
 * <returns>
 *   string
 * </returns>
 * <remarks>
 *   Is passed the result of getarg, which will be the address of a string (in
 *   theory) and uses that for DMA to get the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define getstring        ReturnStringArg
#define GetString        getstring
#define getstringarg     va_getstring
#define GetStringArg     va_getstring
#define returnstringarg  ReturnStringArg

stock ReturnStringArg(idx)
{
	static
		scSize = YSI_MAX_STRING;
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri idx
	// Then convert that number to bytes from cells.
	#emit SMUL.C     4
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "idx * 4 < *(*(FRM + 0) + 8)", for the previous frame
	// parameter count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      12
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the length for "strcat".
	#emit PUSH       scSize
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Load the address of the secret destination.
	#emit LOAD.S.alt 16
	// Blank the first cell so "strcat" behaves like "StrCpy".
	#emit CONST.pri  0
	// Store the loaded number 0 to the loaded address.
	#emit STOR.I
	// Push the loaded address.
	#emit PUSH.alt
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     12
	// Call the function.
	#emit SYSREQ.C   strcat
	// Restore the stack to its level before we called this native.
	#emit STACK      16
	// Return without more string copying.
	#emit RETN
	
	// Fake return to define the API.
	new
		ret[YSI_MAX_STRING];
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="fmat">String format.</param>
 * <param name="">Parameters.</param>
 * <returns>
 *  Formatted string.
 * </returns>
 * <remarks>
 *   Just wraps <c>format</c> and returns a string instead.  Has extra code to
 *   ensure that it works correctly on the old compiler.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock va_return(const fmat[], GLOBAL_TAG_TYPES:...)
{
	#pragma unused fmat
	
	static
		sFrm = 0,
		sRet = 0,
		sCnt = 0,
		scSize = YSI_MAX_STRING;
	
	// Store the function preamble.
	#emit POP.pri
	#emit STOR.pri     sFrm
	#emit STACK        0 // Load the stack pointer for later.
	#emit POP.pri
	#emit STOR.pri     sRet
	#emit POP.pri
	#emit ADD.C        8
	#emit STOR.pri     sCnt
	
	// Put the secret return parameter on the stack again to format in to.
	#emit PUSH         scSize
	#emit ADD
	#emit LOAD.I
	#emit PUSH.pri
	
	// Call the native.
	#emit PUSH         sCnt
	#emit SYSREQ.C     format
	
	// Return directly.  This will clean up our entire stack, even the extra
	// parameters we put on it.  The parameter count is already there!
	#emit PUSH         sRet
	#emit PUSH         sFrm
	#emit RETN
	
	// Fake return to define the API.
	new
		ret[YSI_MAX_STRING];
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to check</param>
 * <remarks>
 *   Checks if a given string is numeric.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IsNumeric(const str[])
{
	P:4("IsNumeric called: \"%s\"", str);
	new
		i = -1;
	while (IS_IN_RANGE(str[++i], '0', '9' + 1)) {}
	return !str[i];
}

#pragma deprecated Use `IsNumeric` (i.e. use proper capitalisation).
stock bool:isnumeric(const str[])
{
	return IsNumeric(str);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to mess up</param>
 * <remarks>
 *   Make some random effects on the player.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined WEAPON
	#define WEAPON: _:
#endif

stock Utils_ChaosMod(playerid)
{
	new tmp;
	switch (random(720))
	{
		case 0:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleVelocity(tmp, 0.0, 0.0, 0.0);
			else
				SetPlayerVelocity(playerid, 0.0, 0.0, 0.0);
		}
		case 1:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleVelocity(tmp, 0.0, 0.0, 1000.0);
			else
				SetPlayerVelocity(playerid, 0.0, 0.0, 1000.0);
		}
		case 2:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				SetVehicleHealth(tmp, 0.0);
			else
				SetPlayerHealth(playerid, 0.0);
		}
		case 3:
		{
			SetPlayerArmedWeapon(playerid, WEAPON:0);
		}
		case 4:
		{
			SetPlayerWorldBounds(playerid, 0.1, -0.1, 0.1, -0.1);
		}
		case 5:
		{
			if ((tmp = GetPlayerVehicleID(playerid)))
				LinkVehicleToInterior(tmp, GetPlayerInterior(playerid) ^ 1);
			SetPlayerInterior(playerid, GetPlayerInterior(playerid) ^ 1);
		}
	}
}

#if _YSI_SAFE_STARTUP
	public OnChaosTimer(oid, playerid)
	{
		Utils_ChaosMod(playerid);
	}
#endif


/*-------------------------------------------------------------------------*//**
 * <param name="string">String to convert to a number.</param>
 * <returns>
 *   value of the passed hex string.
 * </returns>
 * <remarks>
 *   Now stops on invalid characters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock HexStr(const string[])
{
	new
		ret = 0,
		val = 0,
		i = 0;
	if (string[0] == '0' && string[1] | 0x20 == 'x') i = 2;
	for ( ; ; )
	{
		switch ((val = string[i++]))
		{
			case '0' .. '9':
			{
				val -= '0';
			}
			case 'a' .. 'f':
			{
				val -= 'a' - 10;
			}
			case 'A' .. 'F':
			{
				val -= 'A' - 10;
			}
			default: break;
		}
		ret = ret << 4 | val;
	}
	return ret;
}

#pragma deprecated Use `HexStr` (i.e. use proper capitalisation).
stock hexstr(const string[])
{
	return HexStr(string);
}

/*-------------------------------------------------------------------------*//**
 * <param name="string">String to try convert to a boolean.</param>
 * <returns>
 *   bool: passed boolean.
 * </returns>
 * <remarks>
 *   This can take a number of ways of representing booleans - 0, false and
 *   nothing there.  Anything not one of those things (false is not case
 *   sensitive) is assumed true.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:BoolStr(const string[])
{
	// Hooray for De Morgan's rules!
	return string[0] && string[0] != '0' && strcmp(string, "false", true);
}

#pragma deprecated Use `BoolStr` (i.e. use proper capitalisation).
stock bool:boolstr(const string[])
{
	return BoolStr(string);
}

/*-------------------------------------------------------------------------*//**
 * <param name="string">String to try convert to a boolean.</param>
 * <returns>
 *   bool: passed boolean.
 * </returns>
 * <remarks>
 *   This takes a value in 0110101 (boolean) format and returns it as a
 *   regular value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock BinStr(const string[])
{
	new
		pos = 0;
	switch (string[0])
	{
		case '0':
		{
			if (string[1] | 0x20 == 'b')
			{
				pos = 2;
			}
		}
		case '1':
		{
		}
		default:
		{
			return 0;
		}
	}
	new
		value = 0;
	for ( ; ; )
	{
		switch (string[pos++])
		{
			case '0':
			{
				value <<= 1;
			}
			case '1':
			{
				value = (value << 1) | 1;
			}
			default:
			{
				break;
			}
		}
	}
	return value;
}

#pragma deprecated Use `BinStr` (i.e. use proper capitalisation).
stock binstr(const string[])
{
	return BinStr(string);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *   Base64Encode
 * </summary>
 * <remarks>
 *   Encodes data using proper base64.  This code is complicated by the fact
 *   that PAWN packed strings are backwards by cells in memory, so we need to do
 *   the writes in what seems like a strange order.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Base64Encode(dest[], const src[], num = sizeof (src), len = sizeof (dest), offset = 0)
{
	static
		// This is what the encoding should look like.  We mangle it to make the
		// representation in memory look like a C string, not a PAWN packed
		// string.
		//sEncoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		sEncoding[65 char] = !"DCBAHGFELKJIPONMTSRQXWVUbaZYfedcjihgnmlkrqpovutszyxw32107654/+98",
		//tmp,
		ret = 0;
	num = num << __COMPILER_CELL_SHIFT;
	if (len <= ceildiv(num, 3))
	{
		// How many complete chunks can we fit in?
		num = (len - 1) * 3;
	}
	len = num % 3;
	num /= 3;
	// Set up the array for preincrement.
	#emit LOAD.S.pri   src
	#emit ADD.C        0xFFFFFFFD // -3
	#emit LOAD.S.alt   offset
	#emit ADD
	#emit PUSH.pri
	#emit LOAD.S.pri   dest
	#emit STOR.pri     ret
	// Loop for the whole chunks.
	while (num--)
	{
		// Using a post-increment just refuses to work, and I have no idea why.
		#emit POP.pri
		#emit ADD.C        3
		#emit PUSH.pri
		#emit LOAD.I       // `LODB.I 3` doesn't work.
		#emit PUSH.pri
		
		#emit SHL.C.pri    10 // (pri >> 16) & 0x3F
		#emit SHR.C.pri    26 // 
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit LOAD.S.pri   0xFFFFFFF8
		#emit MOVE.alt
		#emit SHL.C.pri     8 // (pri >> 22) & 0x03
		#emit SHR.C.pri    30 // Would be just `SHR.C.pri` with `LODB.I 3`...
		#emit XCHG
		#emit SHL.C.pri    20 // (alt >> 6) & 0x3C
		#emit SHR.C.pri    28 //
		#emit SHL.C.pri    2  //
		#emit OR
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit LOAD.S.pri   0xFFFFFFF8
		#emit MOVE.alt
		#emit SHL.C.pri    30 // (pri << 4) & 0x30
		#emit SHR.C.pri    26 //
		#emit XCHG
		#emit SHL.C.pri    16 // (alt >> 12) & 0x0F
		#emit SHR.C.pri    28 //
		#emit OR
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
		
		#emit POP.pri
		#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
		#emit SHR.C.pri    26 //
		#emit ADD.C        sEncoding
		#emit LODB.I       1
		#emit SREF.S.pri   dest
		#emit INC.S        dest
	}
	{}
	switch (len)
	{
		case 0:
		{
			#emit POP.pri
			#emit LOAD.S.alt   dest
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
		case 1:
		{
			#emit LOAD.S.alt   dest
			#emit CONST.pri    '='
			#emit STRB.I       1
			#emit INC.alt
			#emit STRB.I       1
			#emit INC.alt
			#emit POP.pri
			#emit ADD.C        3
			#emit LODB.I       1
			#emit PUSH.pri
			
			#emit SHL.C.pri    30 // (pri << 4) & 0x30
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			
			#emit POP.pri
			#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
		case 2:
		{
			// Write out remaining `=` signs.
			#emit LOAD.S.alt   dest
			#emit CONST.pri    '='
			#emit STRB.I       1
			#emit INC.alt
			#emit POP.pri
			#emit ADD.C        3
			#emit LODB.I       2
			#emit PUSH.pri
			
			#emit SHL.C.pri    20 // (alt >> 6) & 0x3C
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			
			#emit LOAD.S.pri   0xFFFFFFFC
			#emit MOVE.alt
			#emit SHL.C.pri    30 // (pri << 4) & 0x30
			#emit SHR.C.pri    26 //
			#emit XCHG
			#emit SHL.C.pri    16 // (alt >> 12) & 0x0F
			#emit SHR.C.pri    28 //
			#emit OR
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit LOAD.S.alt   dest
			#emit INC.alt
			#emit INC.alt
			#emit STRB.I       1
			#emit INC.alt
			
			#emit POP.pri
			#emit SHL.C.pri    24 // (pri >> 2) & 0x3F
			#emit SHR.C.pri    26 //
			#emit ADD.C        sEncoding
			#emit LODB.I       1
			#emit STRB.I       1
			#emit INC.alt
			#emit ZERO.pri
			#emit STRB.I       1
			
			#emit LOAD.pri     ret
			#emit SUB.alt
			#emit RETN
		}
	}
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *   Base64Decode
 * </summary>
 * <remarks>
 *   Decodes data using proper base64.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Base64Decode(dest[], const src[], len = sizeof (dest), offset = 0)
{
	static
		// Again, the encoding looks slightly mangled as we want the bytes in
		// order, while cells are little-endian.
		sDecoding[128 char] = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x00000000, 0x3E000000, 0x3F000000, 0x37363534, 0x3B3A3938, 0x00003D3C, 0x00000000,
			0x02010000, 0x06050403, 0x0A090807, 0x0E0D0C0B, 0x1211100F, 0x16151413, 0x00191817, 0x00000000,
			0x1C1B1A00, 0x201F1E1D, 0x24232221, 0x28272625, 0x2C2B2A29, 0x302F2E2D, 0x00333231, 0x00000000
		},
		blocks = 0,
		num = 0;
	// Work out the final length.  Subtract some for incomplete bytes and
	// insufficient destination data.
	num = strlen(src),
	len = len << __COMPILER_CELL_SHIFT,
	blocks = num >>> __COMPILER_CELL_SHIFT;
	if (src{num - 1}  == '=')
	{
		--blocks;
		if (src{num - 2}  == '=')
			num = 1;
		else
			num = 2;
	}
	else
		num = 0;
	blocks = min(blocks, len / 3);
	num = min(num, len - blocks * 3);
	len = blocks * 3 + num;
	// Do complete blocks of 4 (one cell).
	{}
	// x - 1 - 3
	#emit LOAD.S.pri   dest
	#emit ADD.C        0xFFFFFFFC // -4
	#emit LOAD.S.alt   offset
	#emit ADD
	#emit STOR.S.pri   dest
	#emit LOAD.S.pri   src
	#emit ADD.C        0xFFFFFFFC // -4
	#emit STOR.S.pri   src
	while (blocks--)
	{
		#emit LOAD.S.pri   src
		#emit ADD.C        4
		#emit STOR.S.pri   src
		#emit LOAD.I
		#emit MOVE.alt
		
		// The data has now been loaded.  The data MSB comes from the string's
		// LSB (which for PAWN is the last character).
		#emit SHL.C.pri    24 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit SHL.C.pri    24 // (pri << 24)
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHL.C.pri    16 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit PUSH.pri
		#emit SHL.C.pri    30 // (pri << 30)
		#emit SWAP.pri
		#emit SHR.C.pri     2 // (pri >> 2 << 16)
		#emit SHL.C.pri    16
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHL.C.pri     8 // (pri & 0xFF)
		#emit SHR.C.pri    24
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit PUSH.pri
		#emit SHR.C.pri     4 // (pri >> 4 << 8)
		#emit SHL.C.pri     8
		#emit SWAP.pri
		#emit SHL.C.pri    28 // (pri << 28 >> 8)
		#emit SHR.C.pri     8
		#emit PUSH.pri
		
		#emit MOVE.pri
		#emit SHR.C.pri    24 // (pri & 0xFF)
		#emit ADD.C        sDecoding
		#emit LODB.I        1
		#emit SHL.C.pri    10 // (pri << 10)
		#emit MOVE.alt
		
		// Get the byte before the one we want to write loaded as the LSB then
		// shift the other bytes in to this one.
		#emit LOAD.S.pri   dest
		#emit ADD.C        3
		#emit STOR.S.pri   dest
		#emit LODB.I       1
		
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		#emit POP.alt
		#emit OR
		
		#emit SREF.S.pri   dest
	}
	switch (num)
	{
		case 1:
		{
			// Need to store just one byte (the LSB).
			#emit LOAD.S.pri   src
			#emit ADD.C        4
			#emit LOAD.I
			#emit MOVE.alt
			
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHL.C.pri     2 // (pri << 2)
			#emit XCHG
			#emit SHL.C.pri     8
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHR.C.pri     4 // (pri >> 4)
			#emit OR
			#emit MOVE.alt
			
			#emit LOAD.S.pri   dest
			#emit ADD.C        4
			#emit XCHG
			#emit STRB.I       1
		}
		case 2:
		{
			// Need to store two bytes (the LSBs).
			#emit LOAD.S.pri   src
			#emit ADD.C        4
			#emit LOAD.I
			#emit MOVE.alt
			#emit PUSH.pri
			
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHL.C.pri     2 // (pri << 2)
			#emit XCHG
			#emit SHL.C.pri     8
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit PUSH.pri
			#emit SHR.C.pri     4 // (pri >> 4)
			#emit OR
			#emit MOVE.alt
			
			// This has extra bits left in, but they are cut off by `STRB.I 2`.
			#emit POP.pri
			#emit SHL.C.pri    12 // (pri << 12)
			#emit OR
			#emit POP.alt
			#emit XCHG
			#emit SHL.C.pri    16
			#emit SHR.C.pri    24
			#emit ADD.C        sDecoding
			#emit LODB.I        1
			#emit SHR.C.pri     2 // (pri >> 2 << 8)
			#emit SHL.C.pri     8
			#emit OR
			#emit MOVE.alt
			
			#emit LOAD.S.pri   dest
			#emit ADD.C        4
			#emit XCHG
			#emit STRB.I       2
		}
	}
	return len;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *   RawMemCpy
 * </summary>
 * <param name="dest">Destination address.</param>
 * <param name="src">Source data.</param>
 * <param name="numbytes">Number of bytes to copy.</param>
 * <remarks>
 *   Like memcpy, but takes addresses instead of arrays.  Also far less secure
 *   because it doesn't check the destination size - it just assumes it is large
 *   enough.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native RawMemCpy_(dest, src, index, numbytes, maxlength) = memcpy;
#define RawMemCpy(%0,%1,%2) RawMemCpy_((%0),(%1),0,(%2),(cellmax>>>2))

#pragma deprecated Use `RawMemCpy` (i.e. use proper capitalisation).
stock rawMemcpy(dest, src, numbytes)
{
	return RawMemCpy(dest, src, numbytes);
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of cells to fill.</param>
 * <remarks>
 *   Based on <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781">
 *   code by Slice</a>, modified to use binary flags instead of a loop.
 *
 *   "MemSet" takes an array, the size of the array, and a value to fill it with
 *   and sets the whole array to that value.
 *
 *   "rawmemset" is similar, but takes an AMX data segment address instead and
 *   the size is in bytes, not cells.  However, the size must still be a
 *   multiple of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock MemSet(arr[], value = 0, size = sizeof (arr))
{
	new
		addr = 0;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return RawMemSet(addr, value, size * cellbytes);
}

#pragma deprecated Use `MemSet` (i.e. use proper capitalisation).
stock memset(arr[], val = 0, size = sizeof (arr))
{
	new
		addr = 0;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return RawMemSet(addr, val, size * cellbytes);
}

/*-------------------------------------------------------------------------*//**
 * <param name="address">Array or address to set to a value.</param>
 * <param name="value">What to set the cells to.</param>
 * <param name="size">Number of bytes to fill.</param>
 * <remarks>
 *  Based on code by Slice:
 *
 *  <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781" />
 *
 *  Modified to use binary flags instead of a loop.
 *
 *  "MemSet" takes an array, the size of the array, and a value to fill it with
 *  and sets the whole array to that value.
 *
 *  "RawMemSet" is similar, but takes an AMX data segment address instead and
 *  the size is in bytes, not cells.  However, the size must still be a multiple
 *  of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RawMemSet(address /* 12 */, value /* 16 */, size /* 20 */)
{
	if (size < cellbytes)
		return 0;
	if (address < 0)
	{
		// Somewhere in COD, not DAT.  Can't use FILL because it checks the
		// address.  Unless we are running in the JIT, which doesn't have
		// checks, but we shouldn't be writing to COD after the JIT has started
		// anyway.
		do
		{
			#emit LOAD.S.pri value
			#emit SREF.S.pri address
			address += cellbytes;
		}
		while ((size -= cellbytes) > 0);
		return 1;
	}
	else //if (Server_JITComplete())
	{
		while (size >= 4096)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       4096
			address += 4096;
			size -= 4096;
		}
		if (size & 2048)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       2048
			address += 2048;
		}
		if (size & 1024)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       1024
			address += 1024;
		}
		if (size & 512)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       512
			address += 512;
		}
		if (size & 256)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       256
			address += 256;
		}
		if (size & 128)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       128
			address += 128;
		}
		if (size & 64)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       64
			address += 64;
		}
		if (size & 32)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       32
			address += 32;
		}
		if (size & 16)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       16
			address += 16;
		}
		if (size & 8)
		{
			#emit LOAD.S.pri value
			#emit LOAD.S.alt address
			#emit FILL       8
			address += 8;
		}
		if (size & 4)
		{
			#emit LOAD.S.pri value
			#emit SREF.S.pri address
		}
		return 1;
	}
//	else
//	{
//		// JIT not started/non-existant.  We can use code rewriting.
//		return 1;
//	}
}

#pragma deprecated Use `RawMemSet` (i.e. use proper capitalisation).
stock rawMemset(address /* 12 */, value /* 16 */, size /* 20 */)
{
	return RawMemSet(address, value, size);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  ReturnPlayerName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *  Get a player's name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ReturnPlayerName(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME - 1);
	return name;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetPlayerRPName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *  Get a player's name, with <c>_</c> replaced by <c> </c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:GetPlayerRPName(playerid, name[], len = sizeof (name))
{
	if (GetPlayerName(playerid, name, len - 1))
	{
		// Replace `_` with ` `.
		len = -1;
		while ((len = strfind(name, "_", false, len + 1)) != -1)
		{
			name[len] = ' ';
		}
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  IsRPName
 * </summary>
 * <param name="name">The name to test.</param>
 * <param name="casing">Check for string casing?  I.e. allow <c>James</c> but
 *  not <c>james</c>.</param>
 * <param name="longNames">Allow more than two name parts?</param>
 * <remarks>
 *  Is this name in the form <c>First_Last</c>?
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IsRPName(const name[], bool:casing = false, bool:longNames = false)
{
	new
		parts = 0,
		ch = name[0],
		pos = -1;
	if (ch == ' ' || ch == '_' || ch == '\0')
	{
		// Leading bad characters.
		return false;
	}
	if (casing)
	{
		do
		{
			if (NOT_IN_RANGE((ch = name[++pos]), 'A', 'Z' + 1))
			{
				// Not a capital letter.
				return false;
			}
			while ((ch = name[++pos]))
			{
				// Allow real spaces, YSF can enable that.
				if (ch == '_' || ch == ' ')
				{
					if (name[pos + 1] == '\0')
					{
						// Ends with `_`.
						return false;
					}
					break;
				}
				if (NOT_IN_RANGE(ch, 'a', 'z' + 1))
				{
					// Not a lower-case letter.
					return false;
				}
			}
			// Found a name part.
			++parts;
		}
		while (ch);
	}
	else
	{
		do
		{
			while ((ch = name[++pos]))
			{
				// Allow real spaces, YSF can enable that.
				if (ch == '_' || ch == ' ')
				{
					if (name[pos + 1] == '\0')
					{
						// Ends with `_`.
						return false;
					}
					break;
				}
				if (NOT_IN_RANGE(ch, 'a', 'z' + 1) && NOT_IN_RANGE(ch, 'A', 'Z' + 1))
				{
					// Not a valid name letter.
					return false;
				}
			}
			// Found a name part.
			++parts;
		}
		while (ch);
	}
	switch (parts)
	{
	case 1:
		// Not enough parts.
		return false;
	case 2:
		// Exactly two parts.
		return true;
	}
	// More parts.  Is this allowed?
	return longNames;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  HasRPName
 * </summary>
 * <param name="playerid">Player whose name you want to test.</param>
 * <param name="casing">Check for string casing?  I.e. allow <c>James</c> but
 *  not <c>james</c>.</param>
 * <param name="longNames">Allow more than two name parts?</param>
 * <remarks>
 *  Is this player's name in the form <c>First_Last</c>?
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HasRPName(playerid, bool:casing = false, bool:longNames = false)
{
	new
		name[MAX_PLAYER_NAME + 1];
	// Also check they are connected.
	return GetPlayerName(playerid, name, MAX_PLAYER_NAME) && IsRPName(name, casing, longNames);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  ReturnPlayerRPName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *  Get a player's name, with <c>_</c> replaced by <c> </c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ReturnPlayerRPName(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerRPName(playerid, name, MAX_PLAYER_NAME);
	return name;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  ftouch(filename);
 * </summary>
 * <param name="filename">The file to "touch".</param>
 * <returns>
 *  0 - File already exists.
 *  1 - File was created.
 *  -1 - File was not created.
 * </returns>
 * <remarks>
 *  This "touches" a file in the Unix sense of creating it but not opening or
 *  editing it in any way.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ftouch(const filename[])
{
	if (fexist(filename))
	{
		return 0;
	}
	else
	{
		new
			File:f = fopen(filename, io_write);
		if (f)
		{
			fclose(f);
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  InterpolateColourLinear(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *  This function takes a value (fraction) which is a distance between the two
 *  endpoints as a fraction.  This fraction is applied to the two colours given
 *  to find a third colour at some point between those two colours.
 *
 *  This function performs linear interpolation between the colours, which isn't
 *  usually the best way wrt human vision, but is fast.
 *
 *  The fraction is optional, and uses the second colour's alpha for blending
 *  if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// "Interpolation" is the technical name for what you are doing here.
stock InterpolateColourLinear(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Step 1: Get the starting colour components.
		r = startColour & 0xFF000000,
		g = startColour & 0x00FF0000,
		b = startColour & 0x0000FF00,
		// Manipulate the format of floats to multiply by 256 by increasing the exponent by 8.
		stage = floatround(Float:(_:fraction + 0x04000000)); // fraction * 256.0
	return
		// Step 2: Interpolate between the end points, and add to the start.
		// Step 3: Combine the individual components.
		(((r >>> 16) + ((endColour >>> 24       ) - (r >>> 24)) * stage) << 16 & 0xFF000000) |
		(((g >>>  8) + ((endColour >>> 16 & 0xFF) - (g >>> 16)) * stage) <<  8 & 0x00FF0000) |
		(((b       ) + ((endColour >>>  8 & 0xFF) - (b >>>  8)) * stage)       & 0x0000FF00) |
		(a & 0xFF);
	// Because we use a base of 256 instead of 100 to multiply the fractions, we would adjust the
	// numbers down via `>>> 8` instead of `/ 100`, but since we then shift them up again to their
	// final locations in the number we can skip a manipulation stage.
}

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColorLinear(startColour, endColour, Float:fraction)
{
	P:W("`InterpolateColorLinear()` called, please use `InterpolateColourLinear()` isntead,");
	return InterpolateColourLinear(startColour, endColour, value, maxvalue, minvalue);
}

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColor(startColour, endColour, value, maxvalue, minvalue = 0)
{
	return InterpolateColourLinear(startColour, endColour, floatdiv(value - minvalue, maxvalue - minvalue));
}

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColour(startColour, endColour, value, maxvalue, minvalue = 0)
{
	return InterpolateColourLinear(startColour, endColour, floatdiv(value - minvalue, maxvalue - minvalue));
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  InterpolateColourGamma(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *  This function takes a value (fraction) which is a distance between the two
 *  endpoints as a fraction.  This fraction is applied to the two colours given
 *  to find a third colour at some point between those two colours.
 *
 *  This function performs gamma interpolation between the colours, which is a
 *  good balance between complexity and perception.
 *
 *  The fraction is optional, and uses the second colour's alpha for blending
 *  if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define FLOAT_GAMMA (2.2)
#define FLOAT_INVERSE_GAMMA (0.45454545454545454545454545454545) // 1 / 2.2

stock InterpolateColourGamma(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Gamma decode the colour channels.
		Float:r1 = floatpower((startColour >>> 24       ) / 255.0, FLOAT_GAMMA),
		Float:g1 = floatpower((startColour >>> 16 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:b1 = floatpower((startColour >>>  8 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:r2 = floatpower((endColour >>> 24       ) / 255.0, FLOAT_GAMMA),
		Float:g2 = floatpower((endColour >>> 16 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:b2 = floatpower((endColour >>>  8 & 0xFF) / 255.0, FLOAT_GAMMA),
		// Interpolate and encode.
		Float:r3 = floatpower(r1 + (r2 - r1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0,
		Float:g3 = floatpower(g1 + (g2 - g1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0,
		Float:b3 = floatpower(b1 + (b2 - b1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0;
	// Recombine and return.
	return
		(floatround(r3) << 24 & 0xFF000000) |
		(floatround(g3) << 16 & 0x00FF0000) |
		(floatround(b3) <<  8 & 0x0000FF00) |
		(a & 0xFF);
}

#pragma deprecated Use `InterpolateColourGamma` instead.
stock InterpolateColorGamma(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	P:W("`InterpolateColorGamma()` called, please use `InterpolateColourGamma()` isntead,");
	return InterpolateColourGamma(startColour, endColour, fraction);
}

#define FLOAT_SRGB_ADJUST (14.025) // 0.055 * 255.0
#define FLOAT_SRGB_TRANSFORM_LOW  (3294.6) // 12.92 * 255.0
#define FLOAT_SRGB_TRANSFORM_HIGH (269.025) // 1.055 * 255.0
#define FLOAT_SRGB_GAMMA (2.4)
#define FLOAT_SRGB_CUTOFF (11) // 0.04045 * 255

#define FLOAT_CIE_ADJUST (14.025) // 0.055 * 255.0
#define FLOAT_CIE_TRANSFORM_LOW  (3294.6) // 12.92 * 255.0
#define FLOAT_CIE_TRANSFORM_HIGH (269.025) // 1.055 * 255.0
#define FLOAT_CIE_GAMMA     (0.41666666666666666666666666666667) // 1 / 2.4
#define FLOAT_CIE_CUTOFF    (0.0031308)

stock CIEMultiply(Float:r, Float:g, Float:b, &Float:x, &Float:y, &Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
	x = 0.4124 * r + 0.3576 * g + 0.1805 * b;
	y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
	z = 0.0193 * r + 0.1192 * g + 0.9505 * b;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  SRGBToCIE(colour, &amp;Float:x, &amp;Float:y, &amp;Float:z);
 * </summary>
 * <param name="colour">The sRGB colour to convert.</param>
 * <param name="x">The x return value.</param>
 * <param name="y">The y return value.</param>
 * <param name="z">The z return value.</param>
 * <remarks>
 *  Converts a colour from sRGB colour space to CIE XYZ colour space.  See:
 *
 *      https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SRGBToCIE(colour, &Float:x, &Float:y, &Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
	new
		ir = colour >>> 24       ,
		ig = colour >>> 16 & 0xFF,
		ib = colour >>>  8 & 0xFF,
		Float:fr = ir < FLOAT_SRGB_CUTOFF
			? ir / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ir + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA),
		Float:fg = ig < FLOAT_SRGB_CUTOFF
			? ig / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ig + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA),
		Float:fb = ib < FLOAT_SRGB_CUTOFF
			? ib / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ib + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA);
	x = 0.4124 * fr + 0.3576 * fg + 0.1805 * fb,
	y = 0.2126 * fr + 0.7152 * fg + 0.0722 * fb,
	z = 0.0193 * fr + 0.1192 * fg + 0.9505 * fb;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  SRGBToCIE(colour, &amp;Float:x, &amp;Float:y, &amp;Float:z);
 * </summary>
 * <param name="a">The alpha to add on.</param>
 * <param name="x">The x return value.</param>
 * <param name="y">The y return value.</param>
 * <param name="z">The z return value.</param>
 * <remarks>
 *  Converts a colour from CIE XYZ colour space to sRGB colour space.  See:
 *
 *      https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CIEToSRGB(a, Float:x, Float:y, Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)
	new
		// To linear.
		Float:fr = x *  3.2406 + y * -1.5372 + z * -0.4986,
		Float:fg = x * -0.9689 + y *  1.8758 + z *  0.0415,
		Float:fb = x *  0.0557 + y * -0.2040 + z *  1.0570,
		// To RGB.
		ir = fr <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fr)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fr, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST),
		ig = fg <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fg)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fg, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST),
		ib = fb <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fb)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fb, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST);
	return (ir << 24) | (ig << 16 & 0x00FF0000) | (ib << 8 & 0x0000FF00) | (a & 0xFF);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  InterpolateColourSRGB(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *  This function takes a value (fraction) which is a distance between the two
 *  endpoints as a fraction.  This fraction is applied to the two colours given
 *  to find a third colour at some point between those two colours.
 *
 *  This function performs full sRGB colour space interpolation, which is more
 *  exact even than gamma interpolation, but also a lot slower.
 *
 *  The fraction is optional, and uses the second colour's alpha for blending
 *  if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock InterpolateColourSRGB(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Convert colour 1.
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	SRGBToCIE(startColour, x1, y1, z1),
	SRGBToCIE(endColour, x2, y2, z2);
	// Now a simple linear interpolation.
	return CIEToSRGB(a, x1 + (x2 - x1) * fraction, y1 + (y2 - y1) * fraction, z1 + (z2 - z1) * fraction);
}

#pragma deprecated Use `InterpolateColourSRGB` instead.
stock InterpolateColorSRGB(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	P:W("`InterpolateColorSRGB()` called, please use `InterpolateColourSRGB()` isntead,");
	return InterpolateColourSRGB(startColour, endColour, fraction);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetNearestColourLinear(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *  The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *  Find the closest colour to the given colour from the array.  Uses RGB colour
 *  space for the distance function, which is not very accurate.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourLinear(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		// We can use integers because there's no `floatsqrt` used.
		distance = cellmax,
		r1 = colour >>> 24,
		g1 = colour >>> 16 & 0xFF,
		b1 = colour >>>  8 & 0xFF,
		r2,
		g2,
		b2,
		cur;
	while (count--)
	{
		// Get the current colour.
		r2 = (options[count] >>> 24) - r1,
		g2 = (options[count] >>> 16 & 0xFF) - g1,
		b2 = (options[count] >>>  8 & 0xFF) - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetNearestColourGamma(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *  The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *  Find the closest colour to the given colour from the array.  Uses gamma
 *  colour space for slightly more accuracy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourGamma(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		// Gamma decode the colour channels.
		Float:r1 = floatpower((colour >>> 24       ) / 100.0, FLOAT_GAMMA),
		Float:g1 = floatpower((colour >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:b1 = floatpower((colour >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:r2,
		Float:g2,
		Float:b2,
		Float:cur;
	while (count--)
	{
		// Get the current colour.
		r2 = floatpower((options[count] >>> 24       ) / 100.0, FLOAT_GAMMA) - r1,
		g2 = floatpower((options[count] >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA) - g1,
		b2 = floatpower((options[count] >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA) - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetNearestColourGammaCached(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid gamma colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *  The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *  Find the closest colour to the given colour from the array.  Uses gamma
 *  colour space for slightly more accuracy.  Options are in gamma format.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourGammaCached(colour, const Float:options[][3], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		// Gamma decode the colour channels.
		Float:r1 = floatpower((colour >>> 24       ) / 100.0, FLOAT_GAMMA),
		Float:g1 = floatpower((colour >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:b1 = floatpower((colour >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:r2,
		Float:g2,
		Float:b2,
		Float:cur;
	while (count--)
	{
		// Get the current colour.
		r2 = options[count][0] - r1,
		g2 = options[count][1] - g1,
		b2 = options[count][2] - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetNearestColourGamma(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *  The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *  Find the closest colour to the given colour from the array.  Uses SRGB
 *  colour space for the most accuracy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourSRGB(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		Float:cur,
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	// Gamma decode the colour channels.
	SRGBToCIE(colour, x1, y1, z1);
	while (count--)
	{
		// Get the current colour.
		SRGBToCIE(options[count], x2, y2, z2),
		x2 -= x1,
		y2 -= y1,
		z2 -= z1,
		// Find the distance.
		cur = (x2 * x2) + (y2 * y2) + (z2 * z2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  GetNearestColourSRGBCached(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid SRGB colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *  The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *  Find the closest colour to the given colour from the array.  Uses SRGB
 *  colour space for the most accuracy.  Options are in SRGB format.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourSRGBCached(colour, const Float:options[][3], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		Float:cur,
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	// Gamma decode the colour channels.
	SRGBToCIE(colour, x1, y1, z1);
	while (count--)
	{
		// Get the current colour.
		x2 = options[count][0] - x1,
		y2 = options[count][1] - y1,
		z2 = options[count][2] - z1,
		// Find the distance.
		cur = (x2 * x2) + (y2 * y2) + (z2 * z2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

#undef FLOAT_GAMMA
#undef FLOAT_INVERSE_GAMMA

#undef FLOAT_CIE_ADJUST
#undef FLOAT_CIE_TRANSFORM_LOW
#undef FLOAT_CIE_TRANSFORM_HIGH
#undef FLOAT_CIE_GAMMA
#undef FLOAT_CIE_CUTOFF
#undef FLOAT_SRGB_ADJUST
#undef FLOAT_SRGB_TRANSFORM_LOW
#undef FLOAT_SRGB_TRANSFORM_HIGH
#undef FLOAT_SRGB_GAMMA
#undef FLOAT_SRGB_CUTOFF

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to skip over part of.</param>
 * <param name="pos">The start of the whitespace.</param>
 * <returns>
 *  The end of the whitespace.
 * </returns>
 * <remarks>
 *  Doesn't skip over NULL terminators.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SkipWhitespace(const str[], pos)
{
	while (IS_IN_RANGE(str[pos], '\0' + 1, ' ' + 1)) ++pos;
	//while ('\0' < str[pos] <= ' ') ++pos;
	return pos;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to trim.</param>
 * <param name="start">Start of the substring.</param>
 * <param name="end">End of the substring.</param>
 * <remarks>
 *  Modifies "start" and "end" to be tight on text in "str".  <c>Strip</c>
 *  removes the characters from the end, so needs a modifiable string, this just
 *  tells you where the ends are.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Trim(const str[], &start, &end)
{
	while (IS_IN_RANGE(str[start], '\0' + 1, ' ' + 1)) ++start;
	//while ('\0' < str[start] <= ' ') ++start;
	if (str[start])
	{
		while (end-- > start && str[end] <= ' ') {}
		++end;
	}
	else
	{
		end = start;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array to sort.</param>
 * <param name="num">The size of the array.</param>
 * <remarks>
 *  Sorts the array in place.  Uses bubble sort because it is easy and fast for
 *  pre-sorted arrays (which the callers are likely to be).
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Utils_PreSort(arr[], num = sizeof (arr))
{
	// Very simple bubble sort (fast for pre-sorted arrays).
	new
		bool:sort = false;
	do
	{
		sort = false;
		for (new j = 1, temp = 0; j != num; ++j)
		{
			if ((temp = arr[j]) < arr[j - 1])
			{
				arr[j] = arr[j - 1],
				arr[j - 1] = temp,
				sort = true;
			}
		}
	}
	while (sort);
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array whose values need summing.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *  All the values in the array added together.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Sum(const arr[], num = sizeof (arr))
{
	new
		tot = 0;
	while (num) tot += arr[--num];
	return tot;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *  The mathematical mean value of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Mean(const arr[], num = sizeof (arr))
{
	return Sum(arr, num) / num;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *  The mathematical modal value of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Mode(arr[], num = sizeof (arr))
{
	Utils_PreSort(arr, num);
	new
		ret = 0,
		count = 0,
		cn = 0,
		cc = 0;
	for (new i = 0; i != num; ++i)
	{
		if (arr[i] == cn) ++cc;
		else
		{
			if (cc > count) count = cc, ret = cn;
			cc = 1, cn = arr[i];
		}
	}
	if (cc > count) return cn;
	else return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *  The mathematical median value of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Median(arr[], num = sizeof (arr))
{
	Utils_PreSort(arr, num);
	new
		idx = num >>> 1;
	if (num & 1) return arr[idx];
	else return (arr[idx] + arr[idx - 1]) / 2;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *  The mathematical range of the values of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Range(const arr[], num = sizeof (arr))
{
	new
		min2 = cellmax,
		max2 = cellmin,
		cur = 0;
	while (num)
	{
		cur = arr[--num];
		if (cur < min2)
			min2 = cur;
		if (cur > max2)
			max2 = cur;
	}
	return max2 - min2;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr1">First array to compare.</param>
 * <param name="arr2">Second array to compare.</param>
 * <param name="count">How many cells to compare.</param>
 * <returns>
 *  The difference (0 if the same).
 * </returns>
 *//*------------------------------------------------------------------------**/

stock MemCmp(arr1[], arr2[], count)
{
	for (new diff = 0, i = 0; i != count; ++i)
	{
		diff = arr1[i] - arr2[i];
		if (diff)
			return diff;
	}
	return 0;
}

#pragma deprecated Use `MemCmp` (i.e. use proper capitalisation).
stock memcmp(arr1[], arr2[], count)
{
	return MemCmp(arr1, arr2, count);
}

#define MAX_LEVENSHTEIN_STRING (YSI_MAX_STRING)

static stock DoLevenshteinDistance(const a[], lenA, const b[], lenB)
{
	// "a" is the shorter string in this call.
	new
		// Can only compare strings up to this length.
		matrix[MAX_LEVENSHTEIN_STRING + 1] = {0, 1, ...};
	// Initial subsequence equal.
	//if (!strcmp(a, b, false, lenA))
	//	return diff;
	for (new i = 0; i != lenB; ++i)
	{
		// Loop over the characters in the longer string, and use the matrix for the shorter string.
		new
			prev = matrix[0];
		matrix[0] = i + 1;
		for (new j = 0; j != lenA; ++j)
		{
			new
				distance = min(
					matrix[j + 1] + 1     , /* Insertion cost.    */ min(
					matrix[j] + 1         , /* Deletion cost.     */
					prev + _:(b[i] != a[j]) /* Substitution cost. */ )
				);
			prev = matrix[j + 1];
			matrix[j + 1] = distance;
		}
	}
	return matrix[lenA];
}

/*-------------------------------------------------------------------------*//**
 * <param name="a">First string to compare.</param>
 * <param name="b">Second string to compare.</param>
 * <returns>
 *  The levenshtein difference (0 if the same).
 * </returns>
 *//*------------------------------------------------------------------------**/

stock LevenshteinDistance(const a[], const b[])
{
	// If a string is empty, the other length is the distance.
	new
		lenA = strlen(a),
		lenB = strlen(b);
	if (!lenA)
		return lenB;
	if (!lenB)
		return lenA;
	if (lenA > lenB)
	{
		if (lenB > MAX_LEVENSHTEIN_STRING)
		{
			P:E("`LevenshteinDistance` can currenly only handle strings up to `MAX_LEVENSHTEIN_STRING` characters (%d).", MAX_LEVENSHTEIN_STRING);
			return 1;
		}
		return DoLevenshteinDistance(b, lenB, a, lenA);
	}
	else if (lenA == lenB && strcmp(a, b) == 0)
	{
		// Same string.
		return 0;
	}
	if (lenA > MAX_LEVENSHTEIN_STRING)
	{
		P:E("`LevenshteinDistance` can currently only handle strings up to `MAX_LEVENSHTEIN_STRING` characters (%d).", MAX_LEVENSHTEIN_STRING);
		return 1;
	}
	return DoLevenshteinDistance(a, lenA, b, lenB);
}

/*-------------------------------------------------------------------------*//**
 * <param name="n">The number to convert to a string with ordinal.</param>
 * <returns>
 *  Stringises a number, then adds <c>st/nd/rd/th</c>.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock ValstrWithOrdinal(n)
{
	new str[32];
	valstr(str, n);
	if (11 <= (n % 100) <= 13)
	{
		strcat(str, "th");
	}
	else switch (n % 10)
	{
	case 1:
		strcat(str, "st");
	case 2:
		strcat(str, "nd");
	case 3:
		strcat(str, "rd");
	default:
		strcat(str, "th");
	}
	return str;
}

/*-------------------------------------------------------------------------*//**
 * <param name="n">The numeric parameter position to print.</param>
 * <returns>
 *  Prints a string passed as a vararg to the calling function.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock PrintArg(n)
{
	#emit LOAD.S.pri   n
	#emit SHL.C.pri    2
	#emit ADD.C        12
	#emit LOAD.S.alt   0
	#emit ADD
	#emit LOAD.I
	#emit PUSH.pri
	#emit PUSH.C       4
	#emit SYSREQ.C     print
	#emit STACK        8
	#emit RETN
	__pragma("naked");
}

#define printarg PrintArg

stock File:ftemporary_(name[], const ext[] = "tmp", const path[] = "", len = sizeof (name))
{
	new
		pathLen = strlen(path);
	// Ensure there's space for the path (`pathLen`); the filename
	// (`YSI_TEMP_FILE_LENGTH`); the extension (`strlen(ext)`); and `'_'`,
	// `'.'`, and `'\0'` (`3`).
	// Ensure there's space for `NULL`, `_`, and at least one character.
	if (len - strlen(ext) - pathLen < YSI_TEMP_FILE_LENGTH + 3)
	{
		return File:0;
	}
	// These parts of the filename never change, so only do them once.
	strcat(name, path, len),
	name[pathLen] = '_',
	name[pathLen + YSI_TEMP_FILE_LENGTH + 1] = '.',
	strcat(name[pathLen + YSI_TEMP_FILE_LENGTH + 2], ext, len);
	// Generate a random filename, with an equal distribution of letters and
	// numbers.
	do
	{
		// The post-increment here skips the `_` filename prefix.
		for (new i = pathLen; i++ < YSI_TEMP_FILE_LENGTH + pathLen; )
		{
			new ch = random(62);
			if (ch < 26)
			{
				name[i] = ch + 'a';
			}
			else if (ch < 52)
			{
				name[i] = ch + ('A' - 26);
			}
			else
			{
				name[i] = ch + ('0' - 52);
			}
		}
	}
	while (fexist(name));
	// Open the file, to ensure it is created.
	return fopen(name, io_readwrite);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">File to clean up.</param>
 * <param name="maxAge">Maximum temporary file age.</param>
 * <remarks>
 *  Add a file to the temporary cleanup list.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:fautocleanup(const name[], maxAge)
{
	// Add the file to `.tempfiles`.
	new
		bool:initial = !fexist(YSI_TEMP_FILE_NAME),
		File:temps = fopen(YSI_TEMP_FILE_NAME, io_append);
	if (!temps)
	{
		return false;
	}
	new
		line[64];
	// First write to this file.
	if (initial)
	{
		fwrite(temps, "-- DO NOT EDIT THIS FILE, IT RECORDS THE DELETE TIMESTAMPS OF TEMPORARY FILES --\n");
	}
	return
		format(line, sizeof (line), "%d %s", gettime() + maxAge, name),
		fwrite(temps, line),
		fwrite(temps, "\n"),
		fclose(temps),
		true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Storage.</param>
 * <param name="ext">Extension.</param>
 * <param name="len">Maximum string length.</param>
 * <param name="maxAge">Maximum temporary file age.</param>
 * <remarks>
 *  Generate a random temporary filename and open it.  Also redefines
 *  <c>ftemp</c> to call this function instead if called with extra parameters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock File:ftemporary(ret[] = "", const ext[] = "tmp", len = sizeof (ret), maxAge = YSI_TEMP_FILE_AGE)
{
	// Open the file, to ensure it is created.
	if (len < 32)
	{
		// Might not have enough space to store the filename.
		new
			name[32],
			File:file = ftemporary_(name, ext, GetYSIScriptfilesDir(E_YSI_DIR_TEMP));
		if (file)
		{
			return
				ret[0] = '\0',
				strcat(ret, name, len),
				fautocleanup(name, maxAge),
				file;
		}
	}
	else if ((len = _:ftemporary_(ret, ext, GetYSIScriptfilesDir(E_YSI_DIR_TEMP), len)))
	{
		// Shortcut when the destination is big enough.
		return
			fautocleanup(ret, maxAge),
			File:len;
	}
	return File:0;
}

#if defined _ALS_ftemp
	stock File:ftemp_()
	{
		return ftemp();
	}
	#undef ftemp
#else
	native File:ftemp_() = ftemp;
	#define _ALS_ftemp
#endif

// Redefine this code so we can use `ftemp` with extra parameters, or not.
#define ftemp( ftemporary(
#define ftemporary() ftemp_()
#define _ALS_ftemporary

#if _YSI_SAFE_STARTUP
	#define _YSI_DEFAULT_DIR_PREFIX ""
#else
	#define _YSI_DEFAULT_DIR_PREFIX "YSI"
#endif

static stock
	YSI_gsDefaultDirs[E_YSI_DIR][YSI_DIR_LENGTH] = {
#if _DEBUG
		_YSI_DEFAULT_DIR_PREFIX "/debug/",
#endif
#if defined YSI_TESTS
		_YSI_DEFAULT_DIR_PREFIX "/tests/",
		_YSI_DEFAULT_DIR_PREFIX "/YDBG/",
#endif
		//"/text/",
		//"/users/",
		_YSI_DEFAULT_DIR_PREFIX "/fixes/",
		_YSI_DEFAULT_DIR_PREFIX "/temp/"
	};

#undef _YSI_DEFAULT_DIR_PREFIX

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The ID of the directory.</param>
 * <returns>
 *  A directory.
 * </returns>
 * <remarks>
 *  Get a YSI scriptfiles directory, or a fallback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetYSIScriptfilesDir(E_YSI_DIR:dir)
{
	return YSI_gsDefaultDirs[dir];
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Check if all the YSI scriptfiles directories exist.  Checks for `.gitkeep`
 *  in each folder, then each folder without `YSI/` prefix, then just nothing.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP
	stock ResolveYSIScriptfileDirs()
	{
		new
			bool:first = true,
			path[38] = "     /scriptfiles/", // The `18`s below are this length.
			test[YSI_DIR_LENGTH + 8],
			File:file;
		for (new E_YSI_DIR:dir = E_YSI_DIR:0; dir != E_YSI_DIR; ++dir)
		{
			if (YSI_gsDefaultDirs[dir][0] == '/')
			{
				path[18] = '\0',
				strcat(path, "YSI"),
				strcat(path, YSI_gsDefaultDirs[dir]),
				StrCpy(test, path[18]),
				strcat(test, ".gitkeep");
				if ((file = fopen(test, io_write)))
				{
					// Found `YSI/dir/`.
					StrCpy(YSI_gsDefaultDirs[dir], path[18]),
					fclose(file);
				}
				else
				{
					if (first)
					{
						Server_PrintIntroPart(" Missing YSI scriptfiles directories: ", YSI_EMPTY),
						first = false;
					}
					Server_PrintIntroPart(path);
					if ((file = fopen(test[4], io_write)))
					{
						// Found `dir/`.
						StrCpy(YSI_gsDefaultDirs[dir], path[18 + 4]),
						fclose(file);
					}
					else
					{
						// Found nothing.
						YSI_gsDefaultDirs[dir][0] = '\0';
					}
				}
			}
		}
		if (!first)
		{
			Server_FinishIntroPart();
		}
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="i">Handle to the file to copy.</param>
 * <param name="end">How much of the file to copy.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Copy part of a file from the current read pointer, for <c>end</c> bytes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_CopyRange(File:i, end, const string:dst[])
{
	// Must start at the start...
	new
		File:o = fopen(dst, io_write),
		count = min(YSI_UNSAFE_HUGE_LENGTH, end >>> __COMPILER_CELL_SHIFT);
	if (!o)
	{
		return false;
	}
	end &= cellbytes - 1;
	// Only loop as long as we read a full block.  Partials mean the end.  Might
	// do an extra read if `count` starts out as `0`, but that only happens on
	// files less than 4 bytes long and doesn't matter anyway.
	do
	{
		count = fblockread(i, YSI_UNSAFE_HUGE_STRING, count),
		fblockwrite(o, YSI_UNSAFE_HUGE_STRING, count);
	}
	while (count == YSI_UNSAFE_HUGE_LENGTH);
	// Clean up any trailing bytes.
	while (end--)
	{
		//printf("trailing char: %d", end);
		fputchar(o, YSI_FGetChar(i, false), false);
	}
	return bool:fclose(o);
}

/*-------------------------------------------------------------------------*//**
 * <param name="i">Handle to the file to copy.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Fast file copy routine.  Surprisingly widely used in YSI, in places where
 *  temp files were used and <c>fseek</c>ed to the start.  Closes the file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_DoCopy(File:i, const string:dst[])
{
	return
		I@ = _:(fseek(i, 0, seek_start) == 0 && Files_CopyRange(i, flength(i), dst)),
		fclose(i) && I@;
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Copies a file from <c>src</c> to <c>dst</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_Copy(const string:src[], const string:dst[])
{
	new File:i = fopen(src, io_read);
	if (i)
	{
		return
			I@ = _:Files_CopyRange(i, flength(i), dst),
			fclose(i) && I@;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Moves a file from <c>src</c> to <c>dst</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_Move(const string:src[], const string:dst[])
{
	new File:i = fopen(src, io_read);
	if (i)
	{
		return
			I@ = _:(Files_CopyRange(i, flength(i), dst) && fremove(src)),
			fclose(i) && I@;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  TryPercentage(percentage);
 * </summary>
 * <param name="percentage">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *  <c>true</c>, <c>percentage%</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *  Basically a percentage random number generator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPercentage(percentage)
{
	return random(100) < percentage;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  TryPermille(permille);
 * </summary>
 * <param name="permille">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *  <c>true</c>, <c>permille%o</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *  Basically a permille random number generator (that's out of 1000).  Could be
 *  used to replicate something with a <c>42.1%</c> chance of happening via:
 *  <br />
 *  <c>TryPermille(421)</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPermille(permille)
{
	return random(1000) < permille;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  TryPPM(ppm);
 * </summary>
 * <param name="ppm">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *  <c>true</c>, <c>ppm%oooo</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *  Basically a ppm random number generator (that's out of 1000000).  Could be
 *  used to replicate something with a <c>1.0001%</c> chance of happening via:
 *  <br />
 *  <c>TryPPM(10001)</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPPM(ppm)
{
	return random(1000000) < ppm;
}

_Y_CORE_STATIC stock IterativeColouredSkipWhitespace(const text[], start, &colour)
{
	new
		ch = 0,
		i = 0,
		cc = 0;
	while ((ch = text[start]))
	{
		if (ch == '\r' || ch == '\n')
		{
			// Instantly end.  We don't skip this whitespace.
			return start;
		}
		else if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
		{
			// Interesting whitespace.  Will exclude `'\r'` and `'\n'` thanks to
			// the `else`.
			++start;
		}
		else if (ch == '{')
		{
			for (i = 1, cc = 0; i != 7; ++i)
			{
				ch = text[start + i];
				if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					return start;
				}
			}
			if (text[start + 7] == '}')
			{
				colour = cc,
				start += 8;
			}
			else
			{
				// Not valid whitespace.
				return start;
			}
		}
		else
		{
			// Not valid whitespace.
			return start;
		}
	}
	return start;
}

_Y_CORE_STATIC stock IterativeColouredSkipWords(const text[], lastIndex, start, &bool:hyphen, &colour, bool:useHyphen = true)
{
	// Offset.
	new
		// How many real letters appear within the width.
		preLen = 0,
		// How many real letters appear in the whole word?
		truLen = 0,
		g1 = 0,
		g2 = 0,
		ch = 0,
		i = start,
		j = 0,
		cc = 0;
	while ((ch = text[i]) > ' ')
	{
		if (IS_IN_RANGE(ch, 'a', 'z' + 1) || IS_IN_RANGE(ch, 'A', 'Z' + 1))
		{
			// Real letter.
			if (i < lastIndex)
			{
				g1 = g2,
				g2 = i,
				++preLen;
			}
			++truLen;
		}
		else switch (ch)
		{
		case '{':
		{
			for (j = 1, cc = 0; ; ++j)
			{
				ch = text[i + j];
				if (ch <= ' ')
				{
					useHyphen = false,
					i += j;
					break;
				}
				else if (j == 7)
				{
					i += 8;
					if (ch != '}')
					{
						useHyphen = false;
					}
					else if (i <= lastIndex)
					{
						// Only propagate the colour if it is complete in the line.
						colour = cc;
					}
					break;
				}
				else if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					useHyphen = false,
					// NOT an OBOE, rechecks one character.
					i += j;
					break;
				}
			}
			// Don't re-increment.
			continue;
		}
		case '.', ',', '?', '!', '\'':
		{
			// Allow these in normal text.  Thus do nothing.
		}
		default:
		{
			// Not a real word.  Can't be hyphenated.
			useHyphen = false;
		}
		}
		++i;
	}
	// End of the word.
	if (i <= lastIndex)
	{
		// Enough space.
		return
			hyphen = false,
			i;
	}
	else if (useHyphen && truLen > 6 && preLen > 3)
	{
		// Can and should be hyphenated.
		switch (truLen - preLen)
		{
		case 1:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g1;
		}
		case 2:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g2;
		}
		default:
		{
			return
				hyphen = true,
				g2 + 1 == lastIndex ? g2 : g2 + 1;
		}
		}
	}
	// Move the whole thing to the next line.
	return
		hyphen = false,
		start;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  bool:IterativeTextSplitter(const text[], width, start, &amp;end, &amp;next, &amp;bool:hyphen)
 * </summary>
 * <param name="text">The input string to split up.</param>
 * <param name="start">Where in the string to start the next line.</param>
 * <param name="width">The maximum size of the output (including hyphen).</param>
 * <param name="end">The index to end the current line at (excluding hyphen).</param>
 * <param name="next">The index to start the next line from (skips trailing spaces).</param>
 * <param name="hyphen">Should a hyphen be inserted in to the output?</param>
 * <param name="useHyphen">May a hyphen be included?</param>
 * <returns>
 *  Does the function need to be called again to show another line?
 * </returns>
 * <remarks>
 *  Split some text in to multiple lines.  With sensible breaks at spaces or
 *  mid-word if they're long enough.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IterativeTextSplitter(const text[], width, start, &end, &next, &bool:hyphen, bool:useHyphen = true)
{
	// Returns `true` if there is more text to come.
	new
		lastSpace = start,
		wordLen = 0,
		i = start,
		ch;
	for (new j = 0; j != width; ++i, ++j)
	{
		switch ((ch = text[i]))
		{
		case '\0':
		{
			// End of the string.  Quite easy.
			return
				end = wordLen ? i : lastSpace,
				// Just initialise this, the value shouldn't be used.
				next = i,
				// No hyphen, obviously.
				hyphen = false,
				// No more calls after this.
				false;
		}
		case '\r':
		{
			// New line.  Quite easy.
			return
				end = wordLen ? i : lastSpace,
				next = text[i + 1] == '\n' ? i + 2 : i + 1,
				hyphen = false,
				true;
		}
		case '\n':
		{
			// New line.  Very easy.
			return
				end = wordLen ? i : lastSpace,
				next = i + 1,
				hyphen = false,
				true;
		}
		case 1 .. 9, 11 .. 12, 14 .. 32:
		{
			// Spacing.
			if (wordLen)
			{
				// Was in a word, now aren't.
				lastSpace = i,
				wordLen = 0;
			}
			// Else do nothing, we're just skipping an extended space.
		}
		default:
		{
			// Text.
			++wordLen;
		}
		}
	}
	// If we reach the end of the loop we've found the full width of text.
	if (wordLen == 0)
	{
		// In space.  Good.  Skip the rest of the space.
		end = lastSpace,
		hyphen = false;
		while ('\0' < (ch = text[i]) <= ' ')
		{
			if (ch == '\r')
			{
				return
					next = text[i + 1] == '\n' ? i + 2 : i + 1,
					true;
			}
			else if (ch == '\n')
			{
				return
					next = i + 1,
					true;
			}
			++i;
		}
		return
			next = i,
			ch != '\0';
	}
	// In the middle of a string.  Work out if we should split the text with a
	// hyphen or move it down to the next line.
	if (text[i] > ' ')
	{
		if (!useHyphen || wordLen < 4)
		{
			// Not enough space for three characters plus a hyphen on the
			// current line.  Move it down to the next line.
			return
				end = lastSpace,
				next = i - wordLen,
				hyphen = false,
				true;
		}
		if (text[i + 1] > ' ')
		{
			// There will be at least three characters on the next line (the new
			// two plus the one replaced by the hyphen).
			return
				end = i - 1,
				next = i - 1,
				hyphen = true,
				true;
		}
		if (wordLen >= 6)
		{
			// There are at least six characters total.
			return
				end = i - 2,
				next = i - 2,
				hyphen = true,
				true;
		}
		// Five or six characters long.  Move to the next line.
		return
			end = lastSpace,
			next = i - wordLen,
			hyphen = false,
			true;
	}
	// The word fits precisely.
	end = i,
	hyphen = false;
	while ('\0' < (ch = text[i]) <= ' ')
	{
		if (ch == '\r')
		{
			return
				next = text[i + 1] == '\n' ? i + 2 : i + 1,
				true;
		}
		else if (ch == '\n')
		{
			return
				next = i + 1,
				true;
		}
		++i;
	}
	return
		next = i,
		ch != '\0';
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  bool:IterativeColouredTextSplitter(const text[], width, start, &amp;end, &amp;next, &amp;bool:hyphen)
 * </summary>
 * <param name="text">The input string to split up.</param>
 * <param name="start">Where in the string to start the next line.</param>
 * <param name="width">The maximum size of the output (including hyphen).</param>
 * <param name="end">The index to end the current line at (excluding hyphen).</param>
 * <param name="next">The index to start the next line from (skips trailing spaces).</param>
 * <param name="hyphen">Should a hyphen be inserted in to the output?</param>
 * <param name="colour">The colour for the start of the next line.</param>
 * <param name="useHyphen">May a hyphen be included?</param>
 * <returns>
 *  Does the function need to be called again to show another line?
 * </returns>
 * <remarks>
 *  Split some text in to multiple lines.  With sensible breaks at spaces or
 *  mid-word if they're long enough.  Unlike <c>IterativeTextSplitter</c> it
 * will never split in the middle of <c>{RRGGBB}</c> colour sequences, and can
 * ignore them for many checks.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IterativeColouredTextSplitter(const text[], width, start, &end, &next, &bool:hyphen, &colour, bool:useHyphen = true)
{
	new
		ch;
	hyphen = false,
	width += start,
	end = start;
	while ((ch = text[start]))
	{
		if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
		{
			// Skip whitespace.
			start = IterativeColouredSkipWhitespace(text, start, colour);
			switch (text[start])
			{
			case '\r':
			{
				return
					next = text[start + 1] == '\n' ? start + 2 : start + 1,
					true;
			}
			case '\n':
			{
				return
					next = start + 1,
					true;
			}
			case '\0':
			{
				return
					next = start,
					false;
			}
			}
			if (start > width)
			{
				return
					next = start,
					true;
			}
		}
		else
		{
			ch = IterativeColouredSkipWords(text, width, start, hyphen, colour, useHyphen);
			if (ch == start)
			{
				// Either showed nothing of this word, or parts.
				return
					next = ch,
					true;
			}
			else if (hyphen)
			{
				return
					next = end = ch,
					true;
			}
			start = end = ch;
		}
	}
	return
		next = start,
		false;
}

forward y_utils_end();

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Float:FloatAbs(Float:number);
 * </summary>
 * <param name="number">The number to get the absolute value of.</param>
 * <returns>
 *  The absolute value of a number.
 * </returns>
 * <remarks>
 *  Get the absolute value of a number.  Easy in IEEE754, just remove the MSB.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Float:FloatAbs(Float:value));
#define FloatAbs(%0) ((%0) & (Float:0x7FFFFFFF))
#define _ALS_FloatAbs

#if __COMPILER___EMIT_U
	#define Abs(%0) \
		__emit(                         \
			LOAD.U.pri  %0             ,\
			PUSH.pri                   ,\
			CONST.alt   30             ,\
			SSHR                       ,\
			CONST.alt   1              ,\
			OR                         ,\
			POP.alt                    ,\
			SMUL                        \
		)
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Abs(number);
 * </summary>
 * <param name="number">The number to get the absolute value of.</param>
 * <returns>
 *  The absolute value of a number.
 * </returns>
 * <remarks>
 *  Get the absolute value of a number.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Abs(number)
{
	// 31 also works.
	return (number >> 30 | 1) * number;
}

