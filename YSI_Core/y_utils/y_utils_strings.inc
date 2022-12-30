/**
 * <library
 *   name="y_utils - strings"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
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

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">String to check if is null.</param>
 * <remarks>
 *   Uses a new shorter and branchless method, which also works with offsets so
 *   this is valid:
 *
 *   <code>
 *    new str[32]; IsNull(str[5]);
 *   </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:IsNull(const string:str[]));
#define IsNull(%0) ((%0[(%0[0])=='\1'])=='\0'||(%0[0])==ucharmax+1)

#if defined isnull
	#undef isnull
#endif
#define isnull(%0) ((%0[(%0[0])=='\1'])=='\0')
#define _ALS_isnull

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="dest">Destination string.</param>
 * <param name="src">Source string.</param>
 * <param name="len">(Implicit) maximum length of the destination.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(StrCpy(string:dest[], const string:src[], len = sizeof (dest)));
#define StrCpy(%0,%1) strcat((%0[0] = '\0', %0), %1)

#if defined strcpy
	#undef strcpy
#endif
#define strcpy(%0,%1) strcat((%0[0] = '\0', %0), %1)
#define _ALS_strcpy

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">String to convert.</param>
 * <param name="len">How much of the string to convert.</param>
 *//*------------------------------------------------------------------------**/

stock StrToLower(string:str[], len = sizeof (str))
{
	new
		i = -1,
		ch = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while ((ch = str{++i}) && len--)
			str{i} = tolower(ch);
	}
	else
	{
		while ((ch = str[++i]) && len--)
			str[i] = tolower(ch);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">String to convert.</param>
 * <param name="len">How much of the string to convert.</param>
 *//*------------------------------------------------------------------------**/

stock StrToUpper(string:str[], len = sizeof (str))
{
	new
		i = -1,
		ch = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while ((ch = str{++i}) && len--)
			str{i} = toupper(ch);
	}
	else
	{
		while ((ch = str[++i]) && len--)
			str[i] = toupper(ch);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to remove whitespace from the end of.</param>
 * <remarks>
 *   Updated from old versions, should be more efficient
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock StripNL(string:str[])
{
	Debug_Print7("StripNL called: \"%s\"", str);
	new
		i = strlen(str);
	if (YSI_IsLocalVarPackedString__(str))
	{
		while (i-- && str{i} <= ' ') str{i} = '\0';
	}
	else
	{
		while (i-- && str[i] <= ' ') str[i] = '\0';
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to remove whitespace from the end of.</param>
 * <remarks>
 *   Updated from old versions, should be more efficient
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(StripR(string:str[]));
#define StripR StripNL

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to remove whitespace from the start of.</param>
 *//*------------------------------------------------------------------------**/

stock StripL(string:str[])
{
	Debug_Print7("StripL called: \"%s\"", str);
	new
		len = strlen(str),
		i = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while (IS_IN_RANGE(str{i}, '\0' + 1, ' ' + 1)) ++i;
		// The byte offsets in `memcpy` are broken, and packed strings aren't
		// even in order.  Thus we do it the slow way.
		//if (i) memcpy(str[0], str[i], 0, (len - i) * cellbytes, len);
		//Debug_Error("Cannot use `StripL` on a packed string");
		if (i)
		{
			for (new j = 0; (str{j} = str{i}); ++i, ++j) {}
		}
	}
	else
	{
		while (IS_IN_RANGE(str[i], '\0' + 1, ' ' + 1)) ++i;
		if (i)
		{
			memcpy(str[0], str[i], 0, (len - i + 1) * cellbytes, len);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to remove whitespace from the start and end of.</param>
 *//*------------------------------------------------------------------------**/

stock Strip(string:str[])
{
	Debug_Print7("Strip called: \"%s\"", str);
	new
		len = strlen(str),
		i = len;
	if (YSI_IsLocalVarPackedString__(str))
	{
		while (i-- && str{i} <= ' ') str{i} = '\0';
		for (i = 0; IS_IN_RANGE(str{i}, '\0' + 1, ' ' + 1); ++i) {}
		if (i)
		{
			for (new j = 0; (str{j} = str{i}); ++i, ++j) {}
		}
	}
	else
	{
		while (i-- && str[i] <= ' ') str[i] = '\0';
		for (i = 0; IS_IN_RANGE(str[i], '\0' + 1, ' ' + 1); ++i) {}
		if (i)
		{
			memcpy(str[0], str[i], 0, (len - i + 1) * cellbytes, len);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="line">String to check.</param>
 * <param name="pos">Postion to start from.</param>
 * <remarks>
 *   Checks if the current point in a line is the end of non-whitespace data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:EndOfLine(const string:line[], pos)
{
	Debug_Print7("EndOfLine called: \"%s\", %i", line, pos);
	if (NOT_IN_RANGE(pos, 0, strlen(line))) return false;
	if (YSI_IsLocalVarPackedString__(line))
	{
		while (IS_IN_RANGE(line{pos}, '\0' + 1, ' ' + 1)) ++pos;
		return !line{pos};
	}
	else
	{
		while (IS_IN_RANGE(line[pos], '\0' + 1, ' ' + 1)) ++pos;
		return !line[pos];
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="line">String to check.</param>
 * <param name="pos">Postion to start from.</param>
 * <remarks>
 *   Checks if the current point in a line is the end of non-whitespace data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `EndOfLine` (i.e. use proper capitalisation).
stock bool:endofline(const string:line[], pos)
{
	return EndOfLine(line, pos);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *   Fail - -1, Success - pos
 * </returns>
 *//*------------------------------------------------------------------------**/

stock ChrFind(needle, const string:haystack[], start = 0)
{
	Debug_Print3("chrfind called: %c, \"%s\", %i", needle, haystack, start);
	new search[2];
	search[0] = needle;
	return strfind(haystack, search, false, start);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *   Fail - -1, Success - pos
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `ChrFind` (i.e. use proper capitalisation).
stock chrfind(needle, const string:haystack[], start = 0)
{
	return ChrFind(needle, haystack, start);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
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

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `ChrFind` (i.e. use proper capitalisation, and bounds checks).
stock chrfindp(needle, const string:haystack[], start = 0)
{
	return ChrFind(needle, haystack, start);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">String to unpack</param>
 * <returns>
 *   unpacked string
 * </returns>
 * <remarks>
 *   Mainly used for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Unpack(const string:str[])
{
	Debug_Print3("Unpack called: \"%s\"", str);
	new
		ret[YSI_MAX_STRING] = {0};
	if (strlen(str) <= YSI_MAX_STRING)
	{
		strunpack(ret, str);
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">String to unpack</param>
 * <returns>
 *   unpacked string
 * </returns>
 * <remarks>
 *   Mainly used for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Unpack` (i.e. use proper capitalisation).
stock unpack(const string:str[])
{
	// Doesn't call the original, instead inlines the code because it returns a
	// string, and the compiler doesn't like nested string returning functions.
	Debug_Print3("unpack called: \"%s\"", str);
	new
		ret[YSI_MAX_STRING] = {0};
	if (strlen(str) <= YSI_MAX_STRING)
	{
		strunpack(ret, str);
	}
	return ret;
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to skip over part of.</param>
 * <param name="pos">The start of the whitespace.</param>
 * <returns>
 *   The end of the whitespace.
 * </returns>
 * <remarks>
 *   Doesn't skip over NULL terminators.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SkipWhitespace(const string:str[], pos)
{
	if (YSI_IsLocalVarPackedString__(str))
	{
		while (IS_IN_RANGE(str{pos}, '\0' + 1, ' ' + 1)) ++pos;
	}
	else
	{
		while (IS_IN_RANGE(str[pos], '\0' + 1, ' ' + 1)) ++pos;
	}
	//while ('\0' < str[pos] <= ' ') ++pos;
	return pos;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="str">The string to trim.</param>
 * <param name="start">Start of the substring.</param>
 * <param name="end">End of the substring.</param>
 * <remarks>
 *   Modifies "start" and "end" to be tight on text in "str".  <c>Strip</c>
 *   removes the characters from the end, so needs a modifiable string, this just
 *   tells you where the ends are.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Trim(const string:str[], &start, &end)
{
	if (YSI_IsLocalVarPackedString__(str))
	{
		while (IS_IN_RANGE(str{start}, '\0' + 1, ' ' + 1)) ++start;
		//while ('\0' < str[start] <= ' ') ++start;
		if (str{start})
		{
			while (end-- > start && str{end} <= ' ') {}
			++end;
		}
		else
		{
			end = start;
		}
	}
	else
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
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - strings</library>
 * <param name="n">The number to convert to a string with ordinal.</param>
 * <returns>
 *   Stringises a number, then adds <c>st/nd/rd/th</c>.
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

