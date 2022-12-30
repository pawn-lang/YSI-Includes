/**
 * <library
 *   name="y_utils - conversions"
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
 * <library>y_utils - conversions</library>
 * <param name="str">String to check</param>
 * <remarks>
 *   Checks if a given string is numeric.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if (__COMPILER_FIRST_PASS && !defined IsNumeric) || defined YSI_IsNumeric__
	stock bool:IsNumeric(const string:str[])
	{
		Debug_Print4("IsNumeric called: \"%s\"", str);
		// This function is copied in `y_core_entry` to test a compiler bug.
		new
			i = -1;
		if (YSI_IsLocalVarPackedString__(str))
		{
			if (str{0} == '-') ++i;
			while (IS_IN_RANGE(str{++i}, '0', '9' + 1)) {}
			return !str{i};
		}
		else
		{
			if (str[0] == '-') ++i;
			while (IS_IN_RANGE(str[++i], '0', '9' + 1)) {}
			return !str[i];
		}
	}

	#if __COMPILER_WARNING_SUPPRESSION
		// On old compilers, only issue the warning at the call site.
		#pragma warning push
		#pragma warning disable 234
	#endif

	#pragma deprecated Use `IsNumeric` (i.e. use proper capitalisation).
	stock bool:isnumeric(const string:str[])
	{
		return IsNumeric(str);
	}

	#if __COMPILER_WARNING_SUPPRESSION
		#pragma warning pop
	#endif

	// Ensure this branch is hit a second time.
	stock YSI_IsNumeric__()
	{
	}
#else
	HIDE_PAWNDOC(YSI_IsNumeric);
#endif

// Detect a compiler issue.
#if __COMPILER_FUNC_DECL_BUG
	// Try disable the next `IsNumeric` declaration.
	#define IsNumeric(%0[]) _@IsNumeric(%0[])
	#define isnumeric(%0[]) _@isnumeric(%0[])
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="str">String to check.</param>
 * <returns>
 *   true/false.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:IsHex(const string:str[])
{
	Debug_Print3("ishex called: \"%s\"", str);
	new
		i = 0,
		cur = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		if (str{0} == '0' && (str{1} | 0x20) == 'x') i = 2;
		do
		{
			cur = str{i++};
		}
		while (IS_IN_RANGE(cur, '0', '9' + 1) || IS_IN_RANGE(cur | 0x20, 'a', 'f' + 1));
	}
	else
	{
		if (str[0] == '0' && (str[1] | 0x20) == 'x') i = 2;
		do
		{
			cur = str[i++];
		}
		while (IS_IN_RANGE(cur, '0', '9' + 1) || IS_IN_RANGE(cur | 0x20, 'a', 'f' + 1));
	}
	//while (('0' <= cur <= '9') || ('a' <= (cur | 0x20) <= 'f'));
	return !cur; // Valid if this is the end of the string.
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="str">String to check.</param>
 * <returns>
 *   true/false.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `IsHex` (i.e. use proper capitalisation).
stock bool:ishex(const string:str[])
{
	return IsHex(str);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="string">String to convert to a number.</param>
 * <returns>
 *   value of the passed hex string.
 * </returns>
 * <remarks>
 *   Now stops on invalid characters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock HexStr(const string:str[])
{
	new
		ret = 0,
		val = 0,
		i = 0;
	if (YSI_IsLocalVarPackedString__(str))
	{
		if (str{0} == '0' && str{1} | 0x20 == 'x') i = 2;
		for ( ; ; )
		{
			switch ((val = str{i++}))
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
	}
	else
	{
		if (str[0] == '0' && str[1] | 0x20 == 'x') i = 2;
		for ( ; ; )
		{
			switch ((val = str[i++]))
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
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="string">String to convert to a number.</param>
 * <returns>
 *   value of the passed hex string.
 * </returns>
 * <remarks>
 *   Now stops on invalid characters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `HexStr` (i.e. use proper capitalisation).
stock hexstr(const string:str[])
{
	return HexStr(str);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
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

stock bool:BoolStr(const string:str[])
{
	// Hooray for De Morgan's rules!
	return str[0] && ((YSI_IsLocalVarPackedString__(str) ? str{0} : str[0]) != '0') && strcmp(str, "false", true);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
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

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `BoolStr` (i.e. use proper capitalisation).
stock bool:boolstr(const string:str[])
{
	return BoolStr(str);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="string">String to try convert to a boolean.</param>
 * <returns>
 *   bool: passed boolean.
 * </returns>
 * <remarks>
 *   This takes a value in 0110101 (boolean) format and returns it as a
 *   regular value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock BinStr(const string:str[])
{
	if (YSI_IsLocalVarPackedString__(str))
	{
		new
			pos = 0;
		switch (str{0})
		{
			case '0':
			{
				if (str{1} | 0x20 == 'b')
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
			switch (str{pos++})
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
	else
	{
		new
			pos = 0;
		switch (str[0])
		{
			case '0':
			{
				if (str[1] | 0x20 == 'b')
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
			switch (str[pos++])
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
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - conversions</library>
 * <param name="string">String to try convert to a boolean.</param>
 * <returns>
 *   bool: passed boolean.
 * </returns>
 * <remarks>
 *   This takes a value in 0110101 (boolean) format and returns it as a
 *   regular value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `BinStr` (i.e. use proper capitalisation).
stock binstr(const string:str[])
{
	return BinStr(str);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

