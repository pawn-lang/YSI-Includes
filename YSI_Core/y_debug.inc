#if defined _INC_y_debug
	#endinput
#endif
#define _INC_y_debug

/**
 * <library name="y_debug">
 * <section>
 *  Description
 * </section>
 *  <p>Ensures debug levels are set and defines debug functions.</p>
 *
 *  <p>General debug levels:</p>
 *
 *  <ul>
 *  <li>-1 - Run-time selected debug level.</li>
 *  <li>0 - No debug information.</li>
 *  <li>1 - Callbacks and timers.</li>
 *  <li>2 - Remote functions.</li>
 *  <li>3 - Stock functions.</li>
 *  <li>4 - Static functions.</li>
 *  <li>5 - Code.</li>
 *  <li>6 - Loops.</li>
 *  <li>7 - Extra loop code.</li>
 *  </ul>
 *
 *  <p>If you use <c>P:0</c> you get an optional debug print controlled by the
 *  global state <c>ysi_debug</c> - which is either on or off.</p>
 * <section>
 *  Version
 * </section>
 *  1.0
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Debug_Code">Runs defined code if a certain level is active.</symbol>
 *  <symbol name="Debug_Print">Prints the formatted string provided at the given level.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Debug_PrintArray">Print several items from an array for debugging purposes.</symbol>
 *  <symbol name="Debug_Enable">Turn on level 0 prints.</symbol>
 *  <symbol name="Debug_Disable">Turn off level 0 prints.</symbol>
 *  <symbol name="Debug_Level">Set the debug level when the code is compiled with
 *  <c>_DEBUG=-1</c>, which means full run-time selection.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="P:&lt;0-6&gt;">Print a message.</symbol>
 *  <symbol name="P:C">Run debug code.</symbol>
 *  <symbol name="P:E">Print an error message.</symbol>
 *  <symbol name="P:W">Print a warning message.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="_DEBUG">Debugging level to use.</symbol>
 * </ul>
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
*//*-------------------------------------------------------------------------**/

#include "..\YSI_Internal\y_compilerdata"
#include "..\YSI_Internal\y_globaltags"
#include "..\YSI_Internal\y_version"

#include "..\YSI_Internal\y_funcinc"

#include "..\YSI_Server\y_scriptinit"

#if !defined _DEBUG
	#define _DEBUG 0
#endif

stock YSI_gDebugLevel = 0;

#define P:%1(%2); Debug_Print%1(%2);
#define C:%1(%2); Debug_Code%1(%2);

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code1(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:1(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 1</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code1(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code2(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:2(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 2</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code2(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code3(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:3(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 3</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code3(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code4(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:4(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 4</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code4(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code5(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:5(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 5</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code5(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code6(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:6(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 6</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code6(code));

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code7(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:7(if (bla == 2) { bla++; printf("%d", bla); });
 *  </code>
 *
 *  The code must all be on one line to avoid errors.
 *  This isn't really a function as the first parameter is part of the name.
 *
 *  Only compiles the code when <c>_DEBUG %gt;= 7</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Code7(code));

#if _DEBUG == -1
	#define Debug_Code1(%1); { if (YSI_gDebugLevel >= 1) { %1 }}
	#define Debug_Code2(%1); { if (YSI_gDebugLevel >= 2) { %1 }}
	#define Debug_Code3(%1); { if (YSI_gDebugLevel >= 3) { %1 }}
	#define Debug_Code4(%1); { if (YSI_gDebugLevel >= 4) { %1 }}
	#define Debug_Code5(%1); { if (YSI_gDebugLevel >= 5) { %1 }}
	#define Debug_Code6(%1); { if (YSI_gDebugLevel >= 6) { %1 }}
	#define Debug_Code7(%1); { if (YSI_gDebugLevel >= 7) { %1 }}
#else
	#if _DEBUG >= 1
		#define Debug_Code1(%1); %1
	#else
		#define Debug_Code1(%1);
	#endif
	
	#if _DEBUG >= 2
		#define Debug_Code2(%1); %1
	#else
		#define Debug_Code2(%1);
	#endif
	
	#if _DEBUG >= 3
		#define Debug_Code3(%1); %1
	#else
		#define Debug_Code3(%1);
	#endif
	
	#if _DEBUG >= 4
		#define Debug_Code4(%1); %1
	#else
		#define Debug_Code4(%1);
	#endif
	
	#if _DEBUG >= 5
		#define Debug_Code5(%1); %1
	#else
		#define Debug_Code5(%1);
	#endif
	
	#if _DEBUG >= 6
		#define Debug_Code6(%1); %1
	#else
		#define Debug_Code6(%1);
	#endif
	
	#if _DEBUG >= 7
		#define Debug_Code7(%1); %1
	#else
		#define Debug_Code7(%1);
	#endif
#endif

#if _DEBUG != 0
	#define Debug_CodeX(%1); %1
#else
	#define Debug_CodeX(%1);
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print1("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:1("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 1</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print1(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print2("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:2("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 2</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print2(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print3("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:3("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 3</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print3(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print4("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:4("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 4</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print4(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print5("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:5("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 5</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print5(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print6("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:6("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 6</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print6(const str[], GLOBAL_TAG_TYPES:...));

/*-------------------------------------------------------------------------*//**
 * <param name="str">Format.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print7("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:7("variables: %d, %d", i, j);
 *  </code>
 *
 *  Only prints the data when <c>_DEBUG %gt;= 7</c>.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Debug_Print7(const str[], GLOBAL_TAG_TYPES:...));

#if _DEBUG == -1
	#define Debug_Print1(%1); { if (YSI_gDebugLevel >= 1) printf(%1); }
	#define Debug_Print2(%1); { if (YSI_gDebugLevel >= 2) printf(%1); }
	#define Debug_Print3(%1); { if (YSI_gDebugLevel >= 3) printf(%1); }
	#define Debug_Print4(%1); { if (YSI_gDebugLevel >= 4) printf(%1); }
	#define Debug_Print5(%1); { if (YSI_gDebugLevel >= 5) printf(%1); }
	#define Debug_Print6(%1); { if (YSI_gDebugLevel >= 6) printf(%1); }
	#define Debug_Print7(%1); { if (YSI_gDebugLevel >= 7) printf(%1); }
#else
	#if _DEBUG >= 1
		#define Debug_Print1(%1); printf(%1);
	#else
		#define Debug_Print1(%1);
	#endif
	
	#if _DEBUG >= 2
		#define Debug_Print2(%1); printf(%1);
	#else
		#define Debug_Print2(%1);
	#endif
	
	#if _DEBUG >= 3
		#define Debug_Print3(%1); printf(%1);
	#else
		#define Debug_Print3(%1);
	#endif
	
	#if _DEBUG >= 4
		#define Debug_Print4(%1); printf(%1);
	#else
		#define Debug_Print4(%1);
	#endif
	
	#if _DEBUG >= 5
		#define Debug_Print5(%1); printf(%1);
	#else
		#define Debug_Print5(%1);
	#endif
	
	#if _DEBUG >= 6
		#define Debug_Print6(%1); printf(%1);
	#else
		#define Debug_Print6(%1);
	#endif
	
	#if _DEBUG >= 7
		#define Debug_Print7(%1); printf(%1);
	#else
		#define Debug_Print7(%1);
	#endif
#endif

#define Debug_PrintE(%1); \
	Debug_Print0("\7\7\7*** YSI Error: " #%1);

#define Debug_PrintW(%1); \
	Debug_Print0("\7*** YSI Warning: " #%1);

#define Debug_PrintI(%1); \
	Debug_Print0("*** YSI Info: " #%1);

#define Debug_PrintF(%1); \
	Debug_Print0("\7\7\7\7\7*** YSI Fatal Error: " #%1);

#define Debug_PrintC(%1); \
	Debug_CodeX(%1);

/*-------------------------------------------------------------------------*//**
 * <param name="format">str.</param>
 * <param name=""></param>
 * <remarks>
 *  This isn't really a function as the first parameter is part of the name:
 *
 *  <code>
 * Debug_Print0("variables: %d, %d", i, j);
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * P:0("variables: %d, %d", i, j);
 *  </code>
 *
 *  <c>_DEBUG</c> level 0 prints are ALWAYS compiled, but are runtime switched
 *  using the automata <c>ysi_debug</c>.  When then state is <c>ysi_debug :
 *  on</c>, the prints are executed.  When then state is <c>ysi_debug : off</c>,
 *  they aren't.
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Debug_Print0(const str[], GLOBAL_TAG_TYPES:...) <ysi_debug : on>
{
	static tmp1, tmp2;
	#emit POP.pri
	#emit STOR.pri     tmp1
	#emit POP.alt
	#emit STOR.alt     tmp2
	#emit SYSREQ.C     printf
	#emit PUSH         tmp2
	#emit PUSH         tmp1
	#pragma unused str
	return 0;
}

stock Debug_Print0(const str[], GLOBAL_TAG_TYPES:...) <>
{
	#pragma unused str
	return 0;
}

stock Debug_PrintArray(arr[], size = sizeof (arr))
{
	new
		str[96];
	switch (size)
	{
		case 0:
			str = "<>";
		case 1:
			format(str, sizeof (str), "<%d>", arr[0]);
		case 2:
			format(str, sizeof (str), "<%d, %d>", arr[0], arr[1]);
		case 3:
			format(str, sizeof (str), "<%d, %d, %d>", arr[0], arr[1], arr[2]);
		case 4:
			format(str, sizeof (str), "<%d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3]);
		case 5:
			format(str, sizeof (str), "<%d, %d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3], arr[4]);
		default:
			format(str, sizeof (str), "<%d, %d, %d, %d, %d, ... (+ %d)>", arr[0], arr[1], arr[2], arr[3], arr[4], size - 5);
	}
	return str;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Does some strange mangling of <c>YSI_FILTERSCRIPT</c> because at one point I
 *  found a compiler bug where the first automata in the script could conflict
 *  with the first variable in the script.  I don't know what triggered it, and
 *  it has never shown up since I messed about with this file to try mangle some
 *  things.  Never the less, if it ever happens again this code might detect it.
 *
 *  Actually, that's less likely now, since that variable is now very unlikely
 *  to be the first in the script ever.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnScriptInit()
{
	Debug_SetState();
	new
		s;
	// Test the ADDRESS of the variable, not the value.
	#emit CONST.pri YSI_FILTERSCRIPT
	#emit STOR.S.pri s
	if (s)
	{
		//goto Debug_OnScriptInit_no_fault();
		#if defined Debug_OnScriptInit
			return Debug_OnScriptInit();
		#else
			return 1;
		#endif
	}
	P:F("YSI_FILTERSCRIPT == 0");
	while (s != 10000000) ++s;
	#emit CONST.pri 0
	#emit SCTRL     6
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="ysi_debug : on" source="ysi_debug : "/>
 * <remarks>
 *  Mostly exists to define the full range of <c>ysi_debug</c> states.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Debug_SetState() <ysi_debug : off>
{
}

static stock Debug_SetState() <>
{
	state ysi_debug : on;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Turn on level 0 prints.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Debug_Enable()
{
	state ysi_debug : on;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Turn off level 0 prints.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Debug_Disable()
{
	state ysi_debug : off;
}

#undef OnScriptInit
#define OnScriptInit Debug_OnScriptInit
#if defined Debug_OnScriptInit
	forward Debug_OnScriptInit();
#endif

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Set the debug level when the code is compiled with <c>_DEBUG=-1</c>, which
 *  means full run-time selection.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Debug_Level(level = -1)
{
	if (0 <= level <= 7)
	{
		YSI_gDebugLevel = level;
	}
	return YSI_gDebugLevel;
}
#define DebugLevel Debug_Level

