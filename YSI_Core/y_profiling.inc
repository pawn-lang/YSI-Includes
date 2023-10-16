#if defined _INC_y_profiling
	#endinput
#endif
#define _INC_y_profiling

/**
 * <library
 *   name="y_profiling"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Runs any functions named as profilings when the Profiling_Run function is called."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

#include "y_debug"

CHAIN_HOOK(Profiling)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Profiling)

#if defined YSI_PROFILINGS
	#if defined INCLUDE_PROFILINGS
		#error Incompatible profiling options (YSI_PROFILINGS + INCLUDE_PROFILINGS)
	#endif
	#if !defined RUN_PROFILINGS
		#define RUN_PROFILINGS
	#endif
#endif

#if defined INCLUDE_PROFILINGS
	#define RUN_PROFILINGS
	#define Debug_PrintP printf
#elseif defined RUN_PROFILINGS
	#define _AUTO_RUN_PROFILINGS
	#define Debug_PrintP printf
#else
	#if _DEBUG > 0 || defined _YSI_SPECIAL_DEBUG
		#define RUN_PROFILINGS
		#define _AUTO_RUN_PROFILINGS
		#define Debug_PrintP printf
	#else
		#define Debug_PrintP(%0);
	#endif
#endif

#if defined LIGHT_PROFILE_REPORT
	#define PROFILE_REPORT(%0);
#else
	#define PROFILE_REPORT(%0) printf(%0)
#endif

#if defined RUN_PROFILINGS
	#define PROFILE_INIT__%0(%1) @yP_%0();@yP_%0()
	#define PROFILE__ u@(u[_:__TD:__TZ:__TB:__TC:u@$
	#define PROFILE_CLOSE__%0(%1) @P_y%0();@P_y%0()

	// `@profile` default count.
	#define __TD:__TZ:__TB:%8$%0[](%1) __TB:%8$%0(%1)

	// With explicit count.
	#define __TZ:__TB:%8$%0[%2](%1) %8$%0(%1);@y_P%0();@y_P%0()RUN_TIMING(#%0,%2)%0();%0(%1)

	// Without explicit count.
	#define __TB:%8$%0(%1) %8$%0(%1);@y_P%0();@y_P%0()RUN_TIMING(#%0)%0();%0(%1)

	// Strip tags.
	#define __TC:%8$%1:%3();%9:%0();%9:%0()RUN_TIMING(#%9:%2)%9: %8$%1:%3();@y_P%0();@y_P%0()RUN_TIMING(#%2)

//	// Strip `stock` and `static`.
//	#define @y_Pstock%0()%9()RUN_TIMING(#%9stock%2)%9stock @y_P%0();@y_P%0()RUN_TIMING(#%2)
//	#define @y_Pstatic%0()%9()RUN_TIMING(#%9static%2)%9static @y_P%0();@y_P%0()RUN_TIMING(#%2)
//	#define @y_Pconst%0()%9()RUN_TIMING(#%9const%2)%9const @y_P%0();@y_P%0()RUN_TIMING(#%2)

#else
	#define PROFILE_INIT__%0(%1) static stock yP_@%0()
	#define PROFILE__%0(%1) u@(u[_:__TZ:u@$static stock%0()
	#define PROFILE_CLOSE__%0(%1) static stock P_y@%0()
	#define __TZ:%8$%0[%2](%1) %8$%0(%1)
#endif

#if YSI_KEYWORD(ProfileInit)
	#define ProfileInit:%1() PROFILE_INIT__ %1()
#endif
#if YSI_KEYWORD(Profile)
	#define Profile:%1() PROFILE__ %1()
#endif
#if YSI_KEYWORD(ProfileClose)
	#define ProfileClose:%1() PROFILE_CLOSE__ %1()
#endif

#define @profileinit(%2)%0(%1) PROFILE_INIT__ %0(%1)
#define @profile(%2)%0(%1) PROFILE__ %0[%2](%1)
#define @profileclose(%2)%0(%1) PROFILE_CLOSE__ %0(%1)

#define @y_P%0\32; @y_P
#define @yP_%0\32; @yP_
#define @Py_%0\32; @Py_
#define y_P@%0\32; y_P@
#define yP_@%0\32; yP_@
#define Py_@%0\32; Py_@

#define @P_y%0\32; @P_y
#define @_Py%0\32; @_Py
#define @_yP%0\32; @_yP
#define P_y@%0\32; P_y@
#define _Py@%0\32; _Py@
#define _yP@%0\32; _yP@

#define y@P_%0\32; y@P_
#define y@_P%0\32; y@_P
#define P@_y%0\32; P@_y
#define P@y_%0\32; P@y_

// These all need to come AFTER the types are defined in case the have profilings.
#include "y_utils"

#include "..\YSI_Coding\y_va"

#define Y_PROFILING_PROFILE_SEARCH _A<@y_P>
#define Y_PROFILING_INIT _C<@yP_>
#define Y_PROFILING_PROFILE _C<@y_P>
#define Y_PROFILING_CLOSE _C<@P_y>

#define __TY|||%0||| (1000000)
#define __TX:__TY|||%0,%1||| (%1)
#define __TF=fopen(%0,%2"%3",%4) __TF=fopen(%0".csv",%4)

#if !defined TIMING_ITERATIONS
	#define TIMING_ITERATIONS (10)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_profiling</library>
 * <param name="t">The time in ms.</param>
 * <param name="iters">The number of iterations completed in this time.</param>
 * <remarks>
 *   Formats and returns a string representing the time taken for one iteration,
 *   given the time required for many iterations.  This attempts to format the
 *   number using a reasonable fraction of a second.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock BeautifyProfilingTime(t, iters)
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
 * <library>y_profiling</library>
 * <param name="name">The name of the profile.</param>
 * <param name="timings">The raw profiling results.</param>
 * <param name="iters">The number of iterations per run.</param>
 * <param name="size">The number of repeats.</param>
 * <remarks>
 *   "WTF" here stands for "Write To File".  The output looks like:
 *  
 *   <code>
 *      timestamp,runs,repeats,results (ms)
 *      1546082820,10,1000000,122,121,121,120,121,121,121,119,119,121
 *      1546082822,10,1000000,123,124,123,123,121,121,121,120,122,122
 *   </code>
 *  
 *   The timestamp is the unix timestamp at which the line was WRITTEN, not the
 *      time at which the profilings started or ended.
 *  
 *   "runs" is the number of times the whole profile was repeated.
 *  
 *   "repeats" is the number of times the code was run for each repeat.
 *  
 *   "results" are the total times for each repeat, in milliseconds.  The time
 *      for an individual piece of code is <c>result[n] / repeats</c>.  This is
 *      equivalent to:
 *  
 *   <code>
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
 *   </code>
 *  
 *   The repeats help to time very short pieces of code.  The runs help to
 *   average.  The console reports average results (mean, mode, median, range).
 *   Thus the even more accurate result for a single iteration would be:
 *   <c>sum(results) / (runs * repeats)</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// "Write To File", not another "WTF" meaning...
stock DumpProfilingTime(const string:name[], const timings[], iters, size = sizeof (timings))
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
		Debug_Warning("Could not write to profiling results file \"%s\".", name);
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

static stock
	bool:YSI_g_sInProfile = false;

/*-------------------------------------------------------------------------*//**
 * <param name="profilings">Number of profilings run.</param>
 * <returns>
 *   Wether all profilings were sucessful or not.
 * </returns>
 * <remarks>
 *   -
 *
 * native Profiling_Run(&amp;profilings);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Profiling_Run(&profilings)
{
	Debug_Print3("bool:Profiling_Run called: %i", profilings);
#if defined RUN_PROFILINGS
	Server_DisableLongCall();
	Debug_Print2("Profiling_Run() called");
	new
		idx = 0,
		buffer[FUNCTION_LENGTH];
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, Y_PROFILING_PROFILE_SEARCH)))
	{
		//Server_EnableLongCall();
		//Server_RestartLongCall();
		buffer[0] = Y_PROFILING_INIT,
		CallLocalFunction(buffer, YSI_EMPTY),
		// Call the test.
		buffer[0] = Y_PROFILING_PROFILE;
		Debug_Print5("Profiling_Run(): Calling %s", Unpack(buffer[1]));
		YSI_g_sInProfile = true,
		CallLocalFunction(buffer, YSI_EMPTY),
		YSI_g_sInProfile = false,
		buffer[0] = Y_PROFILING_CLOSE,
		CallLocalFunction(buffer, YSI_EMPTY),
		++profilings;
		PROFILE_REPORT(YSI_SPACE);
		//Server_DisableLongCall();
	}
	Server_EnableLongCall();
	Server_RestartLongCall();
#else
	#pragma unused profilings
#endif
}

forward OnProfilingsComplete(profilings, fails);

#if defined RUN_PROFILINGS
	#if defined _AUTO_RUN_PROFILINGS
		public OnScriptInit()
		{
			Profiling_RunAll();
			return Profiling_OnScriptInit();
		}
		
		CHAIN_FORWARD:Profiling_OnScriptInit() = 1;
		#if defined _ALS_OnScriptInit
			#undef OnScriptInit
		#else
			#define _ALS_OnScriptInit
		#endif
		#define OnScriptInit(%0) CHAIN_PUBLIC:Profiling_OnScriptInit(%0)
	#endif
	
	public OnRuntimeError(code, &bool:suppress)
	{
		if (YSI_g_sInProfile)
		{
			// Fail the current profile if we see any runtime errors.  Requires the
			// crashdetect plugin to function, but not to compile and run.
			Debug_PrintP("Error: Runtime error detected");
		}
		return Profiling_OnRuntimeError(code, suppress);
	}
	
	CHAIN_FORWARD:Profiling_OnRuntimeError(code, &bool:suppress) = 1;
	#if defined _ALS_OnRuntimeError
		#undef OnRuntimeError
	#else
		#define _ALS_OnRuntimeError
	#endif
	#define OnRuntimeError(%0) CHAIN_PUBLIC:Profiling_OnRuntimeError(%0)
#endif

stock Profiling_RunAll()
{
	// Disable error messages (as we're likely to generate them).
	new
		startTime = 0,
		endTime = 0,
		profilings = 0;
	// The timing will be inaccurate since it will include many prints, but it
	// isn't that important to be accurate.
	startTime = GetTickCount();
	#if !defined LIGHT_PROFILE_REPORT
		Server_PrintIntroMessage("        STARTING PROFILINGS..."),
		Server_FinishIntroMessage();
	#endif
	Profiling_Run(profilings);
	printf("*** Profilings: %d", profilings);
	#if !defined LIGHT_PROFILE_REPORT
		Server_PrintIntroMessage("         PROFILINGS COMPLETE!"),
		Server_FinishIntroMessage();
	#endif
	endTime = GetTickCount();
	printf("*** Time: %dms", endTime - startTime);
	PROFILE_REPORT(YSI_SPACE);
	CallLocalFunction("OnProfilingsComplete", YSI_gcI, profilings);
	#if defined PROFILE_AUTO_EXIT
		SendRconCommand("exit");
	#endif
}

stock __PA(const name[])
{
	return printf("Timing \"%s\"...", name);
}

stock __PB(const name[], results[], iters, size = sizeof (results))
{
	#if defined PROFILINGS_FILE
		DumpProfilingTime(PROFILINGS_FILE(name), results, iters, size);
	#else
		#pragma unused name
	#endif
		printf("\t  Mean = %s\n\t  Mode = %s\n\tMedian = %s\n\t Range = %s",
			BeautifyProfilingTime(Mean(results, size), iters),
			BeautifyProfilingTime(Mode(results, size), iters),
			BeautifyProfilingTime(Median(results, size), iters),
			BeautifyProfilingTime(Range(results, size), iters)
		);
}

#define __PA(%0,%9);__TC;__PB(%0,%9,%1,%2) __PA(%0);__TC;__PB(%0,%1,%2)

