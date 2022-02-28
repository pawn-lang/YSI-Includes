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
*//*-------------------------------------------------------------------------**/

#if _DEBUG
	#define TODO_MESSAGE:%0,%1; %0[]=#%1;
	#define TODO(%0); new TODO_MESSAGE:TODO@%0;
#else
	#define TODO(%0);
#endif

CHAIN_HOOK(Debug)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Debug)

stock YSI_gDebugLevel = 0;

/*-------------------------------------------------------------------------*//**
 * <param name="code">Code to run.</param>
 * <remarks>
 *  Code is not a variable, it's a code chunk and may be written as so:
 *
 *  <code>
 * Debug_Code1(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:1(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code2(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:2(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code3(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:3(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code4(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:4(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code5(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:5(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code6(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:6(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
 * Debug_Code7(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
 *  </code>
 *
 *  Or:
 *
 *  <code>
 * C:7(if (bla == 2) { bla++; YSI_PrintF("%d", bla); });
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
	#define Debug_Print1(%1); { if (YSI_gDebugLevel >= 1) YSI_PrintF(%1); }
	#define Debug_Print2(%1); { if (YSI_gDebugLevel >= 2) YSI_PrintF(%1); }
	#define Debug_Print3(%1); { if (YSI_gDebugLevel >= 3) YSI_PrintF(%1); }
	#define Debug_Print4(%1); { if (YSI_gDebugLevel >= 4) YSI_PrintF(%1); }
	#define Debug_Print5(%1); { if (YSI_gDebugLevel >= 5) YSI_PrintF(%1); }
	#define Debug_Print6(%1); { if (YSI_gDebugLevel >= 6) YSI_PrintF(%1); }
	#define Debug_Print7(%1); { if (YSI_gDebugLevel >= 7) YSI_PrintF(%1); }
#else
	#if _DEBUG >= 1
		#define Debug_Print1(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print1(%1);
	#endif
	
	#if _DEBUG >= 2
		#define Debug_Print2(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print2(%1);
	#endif
	
	#if _DEBUG >= 3
		#define Debug_Print3(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print3(%1);
	#endif
	
	#if _DEBUG >= 4
		#define Debug_Print4(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print4(%1);
	#endif
	
	#if _DEBUG >= 5
		#define Debug_Print5(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print5(%1);
	#endif
	
	#if _DEBUG >= 6
		#define Debug_Print6(%1); YSI_PrintF(%1);
	#else
		#define Debug_Print6(%1);
	#endif
	
	#if _DEBUG >= 7
		#define Debug_Print7(%1); YSI_PrintF(%1);
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
	Debug_Print0("\7\7\7\7\7*** YSI Fatal Error: " #%1),Debug_Kill_();

#define Debug_PrintC(%1); \
	Debug_CodeX(%1);

stock Debug_Kill_()
{
	#emit HALT 42
}

/*-------------------------------------------------------------------------*//**
 * <param name="YSI_Format">str.</param>
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
	static tmp1 = 0, tmp2 = 0;
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
			YSI_Format(str, sizeof (str), "<%d>", arr[0]);
		case 2:
			YSI_Format(str, sizeof (str), "<%d, %d>", arr[0], arr[1]);
		case 3:
			YSI_Format(str, sizeof (str), "<%d, %d, %d>", arr[0], arr[1], arr[2]);
		case 4:
			YSI_Format(str, sizeof (str), "<%d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3]);
		case 5:
			YSI_Format(str, sizeof (str), "<%d, %d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3], arr[4]);
		default:
			YSI_Format(str, sizeof (str), "<%d, %d, %d, %d, %d, ... (+ %d)>", arr[0], arr[1], arr[2], arr[3], arr[4], size - 5);
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

public OnCodeInit()
{
	Debug_SetState();
	new
		s = 0;
	// Test the ADDRESS of the variable, not the value.
	#emit CONST.pri @_
	#emit STOR.S.pri s
	if (s)
	{
		//goto Debug_OnCodeInit_no_fault();
		#if defined Debug_OnCodeInit
			return Debug_OnCodeInit();
		#else
			return 1;
		#endif
	}
	P:F("@_ == 0");
	while (s != 10000000) ++s;
	#emit CONST.pri 0
	#emit SCTRL     6
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Debug_OnCodeInit
#if defined Debug_OnCodeInit
	forward Debug_OnCodeInit();
#endif

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

native Debug_PrintQ_PRINT(const str[], const expr[], &Debug_PrintQ_SIZEOF:size, addr) = printf;

/*-------------------------------------------------------------------------*//**
 * <param name="addr">A pointer to a thing that might be a string.</param>
 * <returns>
 *  Prints a string passed as a vararg to the calling function.
 * </returns>
 *//*------------------------------------------------------------------------**/

// Checks if the data pointed to by `addr` might possibly be a string.
static stock bool:Debug_IsStringLike(addr, len = 256)
{
	new i = 0;
	len = len << __COMPILER_CELL_SHIFT;
	for (i = 0; i != len; i += cellbytes)
	{
		new ch = AMX_Read(addr + i);
		if (ch == 0)
		{
			break;
		}
		if (ch < ' ' || ch > '~')
		{
			// Outside regular ASCII.  I know that doesn't mean it isn't a
			// string, but again, I don't care...
			return false;
		}
	}
	// Zero-length strings are possible, but we don't care about those.
	// Must have a `NULL` byte at the end.
	return 0 < i < len;
}

forward File:ftemporary(ret[] = "", const ext[] = "tmp", len = sizeof (ret), maxAge = YSI_TEMP_FILE_AGE);

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Try and print a wide range of variables, with their source expression.
 *
 *  Examples:
 *
 *      new arr[] = {33, 33, 33};
 *      new Float:farr[] = {11.0, 11.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0};
 *      new MyCustomTag:mctarr[] = { MyCustomTag:6, MyCustomTag:7 };
 *      new str[] = "hello";
 *      new var1 = 2;
 *      new Float:f = 5.5;
 *      P:Q(str);
 *      P:Q(var1);
 *      P:Q(f);
 *      P:Q(arr);
 *      P:Q(farr, 7);
 *      P:Q(mctarr);
 *
 *  If an array length cannot be determined you can pass it as a second arg.
 *
 *  All tags are supported, the output from the above is:
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:16
 *      
 *          str[6] = "hello"
 *          (full data dumped to: _fgdjkeGjAz.tmp)
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:17
 *      
 *          var1 = 2
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:18
 *      
 *          Float:f = 5.500
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:19
 *      
 *          arr[3] = { 33, 33, 33 }
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:20
 *      
 *          Float:farr[7] = { 11.000, 11.000, 11.000, 12.000, 13.000, ... }
 *          (full data dumped to: _HOf6OQgcC8.tmp)
 *      
 *      [P:Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:21
 *      
 *          MyCustomTag:mctarr[2] = { 6, 7 }
 *      
 * Note: Temporary files are automatically deleted after a month.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Debug_PrintQ_IMPL(Debug_PrintQ_TAG:tag, Debug_PrintQ_SIZEOF:size, const expr[], const file[], line, GLOBAL_TAG_TYPES:...)
{
	// Get the tag name.
	new name[128];
	AMX_GetTagByValue(_:tag, name);
	YSI_PrintF("[P:Q] %s:%d\n", file, line);
	if (size <= Debug_PrintQ_SIZEOF:1)
	{
		// Normal variable.
		// The switch doesn't work on the old compiler.
		//switch (_:tag)
		//{
		if (_:tag == _:tagof (Float:))
			return YSI_PrintF("    Float:%s = %.3f\n", expr, Float:getarg(5));
		if (_:tag == _:tagof (bool:))
			return YSI_PrintF("    bool:%s = %s\n", expr, getarg(5) ? ("    true") : ("    false"));
		if (_:tag == _:tagof (_:))
			return YSI_PrintF("    %s = %d\n", expr, getarg(5));
		//default:
		return YSI_PrintF("    %s:%s = %d\n", name, expr, _:tag, getarg(5));
		//}
	}
	
	// Array or string.
	if (tag == Debug_PrintQ_TAG:tagof (Float:))
	{
		switch (_:size)
		{
		case 2:
			return YSI_PrintF("    Float:%s[%d] = { %.3f, %.3f }\n", expr, _:size, Float:getarg(5, 0), Float:getarg(5, 1));
		case 3:
			return YSI_PrintF("    Float:%s[%d] = { %.3f, %.3f, %.3f }\n", expr, _:size, Float:getarg(5, 0), Float:getarg(5, 1), Float:getarg(5, 2));
		case 4:
			return YSI_PrintF("    Float:%s[%d] = { %.3f, %.3f, %.3f, %.3f }\n", expr, _:size, Float:getarg(5, 0), Float:getarg(5, 1), Float:getarg(5, 2), Float:getarg(5, 3));
		case 5:
			return YSI_PrintF("    Float:%s[%d] = { %.3f, %.3f, %.3f, %.3f, %.3f }\n", expr, _:size, Float:getarg(5, 0), Float:getarg(5, 1), Float:getarg(5, 2), Float:getarg(5, 3), Float:getarg(5, 4));
		default:
			YSI_PrintF("    Float:%s[%d] = { %.3f, %.3f, %.3f, %.3f, %.3f, ... }", expr, _:size, Float:getarg(5, 0), Float:getarg(5, 1), Float:getarg(5, 2), Float:getarg(5, 3), Float:getarg(5, 4));
		}
	}
	else if (tag == Debug_PrintQ_TAG:tagof (_:))
	{
		// Reuse `line` because we no longer need it.
		#emit LOAD.S.pri 32
		#emit STOR.S.pri line
		if (Debug_IsStringLike(line, _:size))
			Debug_PrintQ_PRINT("    %s[%d] = \"%s\"", expr, size, line);
		else switch (_:size)
		{
		case 2:
			return YSI_PrintF("    %s[%d] = { %d, %d }\n", expr, _:size, getarg(5, 0), getarg(5, 1));
		case 3:
			return YSI_PrintF("    %s[%d] = { %d, %d, %d }\n", expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2));
		case 4:
			return YSI_PrintF("    %s[%d] = { %d, %d, %d, %d }\n", expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3));
		case 5:
			return YSI_PrintF("    %s[%d] = { %d, %d, %d, %d, %d }\n", expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3), getarg(5, 4));
		default:
			YSI_PrintF("    %s[%d] = { %d, %d, %d, %d, %d, ... }", expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3), getarg(5, 4));
		}
	}
	else
	{
		switch (_:size)
		{
		case 2:
			return YSI_PrintF("    %s:%s[%d] = { %d, %d }\n", name, expr, _:size, getarg(5, 0), getarg(5, 1));
		case 3:
			return YSI_PrintF("    %s:%s[%d] = { %d, %d, %d }\n", name, expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2));
		case 4:
			return YSI_PrintF("    %s:%s[%d] = { %d, %d, %d, %d }\n", name, expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3));
		case 5:
			return YSI_PrintF("    %s:%s[%d] = { %d, %d, %d, %d, %d }\n", name, expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3), getarg(5, 4));
		default:
			YSI_PrintF("    %s:%s[%d] = { %d, %d, %d, %d, %d, ... }", name, expr, _:size, getarg(5, 0), getarg(5, 1), getarg(5, 2), getarg(5, 3), getarg(5, 4));
		}
	}
    
	// Dump the rest of the data to a file.
	new File:fhnd;
	if ((fhnd = ftemporary(name, "tmp", 10 + 3 + 3)))
	{
		YSI_PrintF("    (full data dumped to: %s)\n", name);
		// The old compiler didn't like this in a ternary, but honestly moving
		// it out of the loop is better anyway.
		tag = Debug_PrintQ_TAG:(tag == Debug_PrintQ_TAG:tagof (Float:));
		// Dump the file.
		for (line = 8; line <= _:size; line += 8)
		{
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, \n") : ("%d, %d, %d, %d, %d, %d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)), getarg(5, line - (8 - 3)), getarg(5, line - (8 - 4)), getarg(5, line - (8 - 5)), getarg(5, line - (8 - 6)), getarg(5, line - (8 - 7)));
			fwrite(fhnd, name);
		}
		switch (line - _:size)
		{
		case 8:
			return fclose(fhnd);
		case 7:
			format(name, sizeof (name), tag ? ("%.3f, \n") : ("%d, \n"), getarg(5, line - (8 - 0)));
		case 6:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, \n") : ("%d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)));
		case 5:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, \n") : ("%d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)));
		case 4:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, %.3f, \n") : ("%d, %d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)), getarg(5, line - (8 - 3)));
		case 3:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, %.3f, %.3f, \n") : ("%d, %d, %d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)), getarg(5, line - (8 - 3)), getarg(5, line - (8 - 4)));
		case 2:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, \n") : ("%d, %d, %d, %d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)), getarg(5, line - (8 - 3)), getarg(5, line - (8 - 4)), getarg(5, line - (8 - 5)));
		case 1:
			format(name, sizeof (name), tag ? ("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, \n") : ("%d, %d, %d, %d, %d, %d, %d, \n"), getarg(5, line - (8 - 0)), getarg(5, line - (8 - 1)), getarg(5, line - (8 - 2)), getarg(5, line - (8 - 3)), getarg(5, line - (8 - 4)), getarg(5, line - (8 - 5)), getarg(5, line - (8 - 6)));
		}
		fwrite(fhnd, name);
		fclose(fhnd);
	}

	return 0;
}

//#define Debug_PrintQ(%0) Debug_PrintQ_IMPL(Debug_PrintQ_TAG:tagof(%0),Debug_PrintQ_SIZEOF:sizeof(%0),(#%0),__file,__line,_:(%0))
#define Debug_PrintQ_IMPL(%0(%1,%2),%9(%9,%9),(#%7,%9),%4,%5,_:(%8,%9)) Debug_PrintQ_IMPL(%0(%1),Debug_PrintQ_SIZEOF:%2,(#%7),%4,%5,_:(%8))

#define Debug_PrintQ_TAG:tagof("%0") Debug_PrintQ_TAG:-1
#define Debug_PrintQ_SIZEOF:sizeof(%0[%1]) Debug_PrintQ_SIZEOF:sizeof(%0[])

#if _DEBUG >= 1
	#define Debug_PrintQ(%0); Debug_PrintQ_IMPL(Debug_PrintQ_TAG:tagof(%0),Debug_PrintQ_SIZEOF:sizeof(%0),(#%0),__file,__line,_:(%0));
#else
	#define Debug_PrintQ(%0);
#endif

