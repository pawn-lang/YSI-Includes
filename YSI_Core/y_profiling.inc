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
	#define PROFILE__ u@(u[_:__TZ:__TB:__TC:u@$
	#define PROFILE_CLOSE__%0(%1) @P_y%0();@P_y%0()

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
	#define PROFILE__ u@(u[_:__TZ:u@$
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

static stock
	bool:YSI_g_sInProfile = false;

/*-------------------------------------------------------------------------*//**
 * <param name="profilings">Number of profilings run.</param>
 * <returns>
 *  Wether all profilings were sucessful or not.
 * </returns>
 * <remarks>
 *  -
 *
 * native Profiling_Run(&profilings, &fails, buffer[33] = "");
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Profiling_Run(&profilings)
{
	P:3("bool:Profiling_Run called: %i", profilings);
#if defined RUN_PROFILINGS
	P:2("Profiling_Run() called");
	new
		idx = 0,
		buffer[FUNCTION_LENGTH];
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, Y_PROFILING_PROFILE_SEARCH)))
	{
		buffer[0] = Y_PROFILING_INIT,
		CallLocalFunction(buffer, YSI_EMPTY),
		// Call the test.
		buffer[0] = Y_PROFILING_PROFILE;
		P:5("Profiling_Run(): Calling %s", Unpack(buffer[1]));
		YSI_g_sInProfile = true,
		CallLocalFunction(buffer, YSI_EMPTY),
		YSI_g_sInProfile = false,
		buffer[0] = Y_PROFILING_CLOSE,
		CallLocalFunction(buffer, YSI_EMPTY),
		++profilings;
		PROFILE_REPORT(YSI_SPACE);
	}
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
		#undef OnScriptInit
		#define OnScriptInit(%0) CHAIN_PUBLIC:Profiling_OnScriptInit(%0)
	#endif
	
	public OnRuntimeError(code, &bool:suppress)
	{
		if (YSI_g_sInProfile)
		{
			// Fail the current profile if we see any runtime errors.  Requires the
			// crashdetect plugin to function, but not to compile and run.
			P:P("Error: Runtime error detected");
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
	CallLocalFunction("OnProfilingsComplete", "i", profilings);
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
		DumpProfilingTime(PROFILINGS_FILE(name), results, iters);
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

