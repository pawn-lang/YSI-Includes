#if defined _INC_y_utils
	#endinput
#endif
#define _INC_y_utils

/**
 * <library name="y_utils">
 * <section>
 *  Description
 * </section>
 * Misc functions used throughout.
 * <section>
 *  Version
 * </section>
 *  0.1.3
 * <section>
 *  Functions
 * </section>
 *  <subsection>Stock</subsection>
 * <ul>
 *  <symbol name="StrToLower">Convert a whole string to lower-case.</symbol>
 *  <symbol name="StrToUpper">Convert a whole string to upper-case.</symbol>
 *  <symbol name="Random">Generate a random number, optionally takes lower and upper bounds.</symbol>
 *  <symbol name="RandomFloat">Same as <symbolref name="Random" />, but for floats.</symbol>
 *  <symbol name="StripNL">Strips the newline characters from the end of a string.</symbol>
 *  <symbol name="StripL">Remove whitespace from the start of a string.</symbol>
 *  <symbol name="Strip">Remove whitespace from both ends of a string.</symbol>
 *  <symbol name="endofline">Check if the given position is the end of a string (ignoring whitespace).</symbol>
 *  <symbol name="chrfind">Return the first position (after <symbolref name="start" />) of the given character.</symbol>
 *  <symbol name="chrfindp">Like <symbolref name="chrfind" />, but without the upper-bounds check.</symbol>
 *  <symbol name="bernstein">Generate the Bernstein hash of the given string.</symbol>
 *  <symbol name="ishex">Is the given string hexadecimal?</symbol>
 *  <symbol name="unpack">Version of <symbolref name="strunpack" /> that returns the result.</symbol>
 *  <symbol name="returnstringarg">Get the string passed as a variable argument from the given index.</symbol>
 *  <symbol name="va_return">Like <symbolref name="sprintf" />, formats a string and returns the result.</symbol>
 *  <symbol name="isnumeric">Is the given string a number?</symbol>
 *  <symbol name="hexstr">Return the value of the given hexadecimal string.</symbol>
 *  <symbol name="boolstr">Return the value of the given boolean string.</symbol>
 *  <symbol name="binstr">Return the value of the given binary string.</symbol>
 *  <symbol name="rawMemcpy">Copy memory between two address, instead of two arrays.</symbol>
 *  <symbol name="memset">Set all of an array to a value.</symbol>
 *  <symbol name="rawMemset">Set all of a given memory region to a value.</symbol>
 *  <symbol name="ReturnPlayerName">Return a player's name.</symbol>
 *  <symbol name="ftouch">Ensures that a file exists, but nothing more.</symbol>
 *  <symbol name="InterpolateColour">Get the colour (in 3D RGB space) between two other colours.</symbol>
 *  <symbol name="SkipWhitespace">Return the first position in a string of a non-whitespace character.</symbol>
 *  <symbol name="Trim">Get the first and last positions of non-whitespace characters in the string.  Like <symbolref name="Strip" />, but doesn't modify the string.</symbol>
 *  <symbol name="Sum">Get the total (sum) of an array.</symbol>
 *  <symbol name="Mean">Get the mathematical mean of an array.</symbol>
 *  <symbol name="Mode">Get the mathematical mode of an array.</symbol>
 *  <symbol name="Median">Get the mathematical median of an array.</symbol>
 *  <symbol name="Range">Get the mathematical range of an array.</symbol>
 * </ul>
 *  <subsection>Inline</subsection>
 * <ul>
 *  <symbol name="UCMP">Unsigned compare.</symbol>
 *  <symbol name="VALID_PLAYERID">Check if a player ID is valid (in range).</symbol>
 *  <symbol name="IS_IN_RANGE">Check if a number is in range.</symbol>
 *  <symbol name="NOT_IN_RANGE">Check if a number is outside a range.</symbol>
 *  <symbol name="ceildiv">Divide two numbers and round up.</symbol>
 *  <symbol name="floordiv">Divide two numbers and round down.</symbol>
 *  <symbol name="isnull">Checks if a string is NULL (<c>\1\0</c> or <c>\0</c>).</symbol>
 *  <symbol name="isodd">Checks if a number is odd.</symbol>
 *  <symbol name="iseven">Checks if a number is even.</symbol>
 *  <symbol name="strcpy">Copy one string to another.</symbol>
 *  <symbol name="GetIP">Return the encoded (32-bit) version of a player's IP.</symbol>
 *  <synonym name="getstring" for="returnstringarg"> (there are a lot)</synonym>
 *  <synonym name="GetString" for="returnstringarg"> (there are a lot)</synonym>
 *  <synonym name="getstringarg" for="returnstringarg"> (there are a lot)</synonym>
 *  <synonym name="GetStringArg" for="returnstringarg"> (there are a lot)</synonym>
 *  <synonym name="ReturnStringArg" for="returnstringarg"> (there are a lot)</synonym>
 *  <synonym name="InterpolateColor" for="InterpolateColour" />
 *  <synonym name="StripR" for="StripNL" />
 * </ul>
 * <section>
 *  Variables
 * </section>
 *  <subsection>Global</subsection>
 * <ul>
 *  <symbol name="TRUE">True hack for infinate loops.</symbol>
 *  <symbol name="FALSE">False hack for one-time loops.</symbol>
 *  <symbol name="NULL">1 long string for passing via Call(Remote|Local)Function.</symbol>
 * </ul>
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

#include "..\YSI_Internal\y_compilerdata"
#include "..\YSI_Internal\y_version"

#include "..\YSI_Core\y_debug"
#include "..\YSI_Storage\y_amx"
//#tryinclude <sscanf>

#include "..\YSI_Internal\y_thirdpartyinclude"
#include "..\YSI_Internal\y_funcinc"
// Add new tags to the START of this list.
#include "..\YSI_Internal\y_globaltags"

// VERY VERY VERY IMPORTANT!!! y_inline uses "130" instead of "YSI_MAX_STRING"
// for two lines (one is "520" for "130 * 4").
#define YSI_MAX_STRING                  (130)

#define FUNCTION_LENGTH                 (32)

// Better handling of operator precedences and floating point numbers.  This
// will now work for ALL regular numbers (including -0.5 which broke the old
// version).  I don't know of any complex expressions that break it with
// operator precedences, but I'm not ruling it out.  The brackets do try and
// account for that possibility, but I just don't know.
#define NO_VALUE(%0) ((2*%0-1)==2*(%0-1))

#if !defined TRUE
new stock
	bool:TRUE = true;
#endif
#if !defined FALSE
new stock
	bool:FALSE = false;
#endif
#if !defined NULL
new stock
	NULL[2] = "\1";
#endif

#if !defined cellbytes
	#define cellbytes (cellbits / 8)
#endif

#define UNSIGNED(%0) ((%0) - cellmin)

// Define "volatile" as nothing.
#if !defined volatile
	#define volatile
#endif

#define YSIM_MASTER #M
#define YSIM_RETURN #R
#define YSIM_CALLER #C
#define YSIM_TEXT_D #T
#define YSIM_TXTFND #X
#define YSIM_TXTIND #I
#define YSIM_LOG_IN #U
#define YSIM_VARARG #V

#if !defined YSIM_STRING
	#define YSIM_STRING (42)
#endif

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

//#pragma unused TRUE, FALSE, NULL

#define __TY|||%0||| (1000000)
#define __TX:__TY|||%0,%1||| (%1)
#define __TF=fopen(%0,%2"%3",%4) __TF=fopen(%0".csv",%4)

#if !defined TIMING_ITERATIONS
	#define TIMING_ITERATIONS (10)
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="t">The time in ms.</param>
 * <param name="iters">The number of iterations completed in this time.</param>
 * <remarks>
 *  Formats and returns a string representing the time taken for one iteration,
 *  given the time required for many iterations.  This attempts to format the
 *  number using a reasonable fraction of a second.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock __TU(t, iters)
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

#define RUN_TIMING(%0) \
	for(new __TA[TIMING_ITERATIONS],__TC=sizeof __TA,__TE=_:__TX:__TY|||%0|||,__TS=printf("Timing \"%s\"...",%0);__TC; \
		printf("\t  Mean = %s\n\t  Mode = %s\n\tMedian = %s\n\t Range = %s", \
			__TU(Mean(__TA),__TE),__TU(Mode(__TA),__TE),__TU(Median(__TA),__TE),__TU(Range(__TA),__TE))) \
	for(;(__TS=GetTickCount(),__TC);__TA[--__TC]=GetTickCount()-__TS) \
	for(new __TI;__TI!=__TE;++__TI)

#define CSV_TIMING(%0) \
	for(new __TA[TIMING_ITERATIONS],__TC=sizeof __TA,__TE=_:__TX:__TY|||%0|||,__TS=printf("Timing \"%s\"...",%0),File:__TF=fopen(%0".csv",io_append);__TF&&__TC;\
		va_fprintf(__TF,"%d,%d,%s,%s,%s,%s\n",gettime(),__TE,__TU(Mean(__TA),__TE),__TU(Mode(__TA),__TE),__TU(Median(__TA),__TE),__TU(Range(__TA),__TE)),fclose(__TF))\
	for(;(__TS=GetTickCount(),__TC);__TA[--__TC]=GetTickCount()-__TS)\
	for(new __TI;__TI!=__TE;++__TI)

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
 * <param name="value">The unsigned number to compare.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *  An unsigned comparison between the two values.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(bool:UCMP(value, upper));
#define UCMP(%0,%1) IS_IN_RANGE(%0,0,(%1))

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
#define ceildiv(%0,%1) (((%0)-1)/(%1)+1)

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
#define floordiv(%0,%1) ((%0)/(%1))

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to check if is null.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:isnull(str[]));
#define isnull(%1) \
	((%1[0] == 0) || (%1[0] == 1 && %1[1] == 0))

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to check if is odd.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:isodd(value));
#define isodd(%1) \
	((%1) & 1)

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to check if is even.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:iseven(value));
#define iseven(%1) \
	(!isodd(%1))

/*-------------------------------------------------------------------------*//**
 * <param name="dest">Destination string.</param>
 * <param name="src">Source string.</param>
 * <param name="len">(Implicit) maximum length of the destination.</param>
 *//*------------------------------------------------------------------------**/

P:D(strcpy(dest[], const src[], len = sizeof (dest)));
#define strcpy(%0,%1) \
	strcat((%0[0] = '\0', %0), %1)

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to convert.</param>
 * <param name="len">How much of the string to convert.</param>
 *//*------------------------------------------------------------------------**/

stock StrToLower(str[], len = sizeof (str))
{
	new
		i = -1,
		ch;
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
		ch;
	while ((ch = str[++i]) && len--)
		str[i] = toupper(ch);
}

/*-------------------------------------------------------------------------*//**
 * <param name="minmax">Lower bound, or upper bound when only parameter.</param>
 * <param name="max">Upper bound.</param>
 * <remarks>
 *  Generate a random float between the given numbers (min &lt;= n &lt; max).
 *  Default minimum is 0 (changes the parameter order).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Random(min, max = cellmin)
{
	if (max == cellmin)
	{
		if (min < 0)
			return -random(-min);
		return random(min);
	}
	if (max < min)
		return random(min - max) + max;
	return random(max - min) + min;
}

/*-------------------------------------------------------------------------*//**
 * <param name="minmax">Lower bound, or upper bound when only parameter.</param>
 * <param name="max">Upper bound.</param>
 * <param name="dp">How small to make the differences</param>
 * <remarks>
 *  Generate a random float between the given numbers (min &lt;= n &lt; max).  Default
 *  minimum is 0.0 (changes the parameter order).
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
	if (max != max)
	{
		if (min < 0.0)
			return -(float(random(floatround(-min * mul))) / mul);
		return float(random(floatround(min * mul))) / mul;
	}
	// Parameters are the wrong way around - do it anyway.
	if (max < min)
		return float(random(floatround(min * mul - max * mul))) / mul + max;
	// NOT a silly check - "IsNaN".
	return float(random(floatround(max * mul - min * mul))) / mul + min;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string to remove whitespace from the end of.</param>
 * <remarks>
 *  Updated from old versions, should be more efficient
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock StripNL(str[])
{
	P:7("StripNL called: \"%s\"", str);
	new
		i = strlen(str);
	while (i-- && str[i] <= ' ') str[i] = '\0';
}

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
 *  Checks if the current point in a line is the end of non-whitespace data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock endofline(line[], pos)
{
	P:7("endofline called: \"%s\", %i", line, pos);
	if (NOT_IN_RANGE(pos, 0, strlen(line))) return 0;
	//if (pos < 0 || pos > strlen(line)) return 0;
	while (line[pos]) if (line[pos++] > ' ') return 0;
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *  Fail - -1, Success - pos
 * </returns>
 *//*------------------------------------------------------------------------**/

stock chrfind(needle, haystack[], start = 0)
{
	P:7("chrfind called: %c, \"%s\", %i", needle, haystack, start);
	if (start < 0)
	{
		start = 0;
	}
	else if (start > strlen(haystack)) return -1;
	while (haystack[start]) if (haystack[start++] == needle) return start - 1;
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="needle">The character to find.</param>
 * <param name="haystack">The string to find it in.</param>
 * <param name="start">The offset to start from.</param>
 * <returns>
 *  Fail - -1, Success - pos
 * </returns>
 * <remarks>
 *  Like <symbolref name="chrfind" />, but with no upper-bounds check on
 *  <paramref name="start" />.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock chrfindp(needle, haystack[], start = 0)
{
	P:7("chrfind called: %c, \"%s\", %i", needle, haystack, start);
	if (start < 0)
	{
		start = 0;
	}
	while (haystack{start}) if (haystack{start++} == needle) return start - 1;
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="ip">Dot notation IP to convert to an integer.</param>
 *//*------------------------------------------------------------------------**/

stock IPToInt(ip[])
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
 *  the bernstein hash of the input string
 * </returns>
 * <remarks>
 *  This is a 32bit hash system so is not very secure, however we're only
 *  using this as a string enumerator to uniquely identify strings easilly
 *  and allow for a binary search of strings based on the hash of their name.
 *  crc32, then jenkins were originally used however this is far faster, if a
 *  little collision prone, but we're checking the strings manually anyway.
 *  This doesn't matter as it would be done regardless of hash method, so this
 *  doesn't need to be accounted for.  Speed is all that matters with at 
 *  least a bit of non collision (the number of strings we're dealing with,
 *  this should have none-few collisions).
 *
 *  I modified it slightly from the original code pasted by aru, to code
 *  closer to the code <a href="http://www.burtleburtle.net/bob/hash/doobs.html" />
 *  and to work with PAWN (and shaved 0.2�s off the time for one call :D).
 *
 *  Uber reduced version (just for fun):
 *  b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
 *
 *  Update: Contrary to what I said above this is also used to identify colour
 *  strings for the updated text system involving file based styling and this
 *  is not checked for collisions as it's unimportant.  But this doesn't affect
 *  the function at all, I just mentioned it here for "interest".
 *
 *  Rewritten in self-generating assembly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bernstein(string[] /* 12 */)
{
	// Only shown the very first time this function is run.
	P:7("bernstein called: \"%s\"", string);
	#pragma unused string
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  bernstein
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 128), // Don't need any more than that.
	// Setup.
	@emit PROC
	@emit CONST.alt   -1
	@emit PUSH.S      12 // string
	@emit LREF.S.pri  12 // string
	@emit JZER.rel    12 * 4 // bernstein_end
// bernstein_loop:
	@emit XCHG
	@emit SMUL.C      33
	@emit ADD
	@emit MOVE.alt
	// Update the next pointer.
	@emit POP.pri
	@emit ADD.C       4
	@emit PUSH.pri
	// Load the data for the current pointer.
	@emit LOAD.I
	@emit JNZ.rel     -(12 * 4) // bernstein_loop
// bernstein_end:
	@emit MOVE.pri
	@emit STACK       4
	@emit RETN
	// Now actually CALL the written function.
	#emit LCTRL      5
	#emit SCTRL      4
	#emit CONST.pri  bernstein
	#emit ADD.C      4
	#emit SCTRL      6
	return 0; // Make the compiler happy.
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to check.</param>
 * <returns>
 *  true/false.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock ishex(str[])
{
	P:7("ishex called: \"%s\"", str);
	new
		i,
		cur;
	if (str[0] == '0' && (str[1] | 0x20) == 'x') i = 2;
	do
	{
		cur = str[i++];
	}
	while (IS_IN_RANGE(cur, '0', '9' + 1) || IS_IN_RANGE(cur | 0x20, 'a', 'f' + 1));
	//while (('0' <= cur <= '9') || ('a' <= (cur | 0x20) <= 'f'));
	return !cur; // Valid if this is the end of the string.
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to unpack</param>
 * <returns>
 *  unpacked string
 * </returns>
 * <remarks>
 *  Mainly used for debugging.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock unpack(const str[])
{
	P:7("unpack called: \"%s\"", str);
	new
		ret[YSI_MAX_STRING] = {0};
	if (strlen(str) <= YSI_MAX_STRING)
	{
		strunpack(ret, str);
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get IP of.</param>
 * <returns>
 *  IP as a 32bit int.
 * </returns>
 *//*------------------------------------------------------------------------**/

// Cunning macro only uses "%0" once, yet is still safe.
P:D(GetIP(playerid));
#define GetIP(%0) (YSI_gPlayerIP[min((%0) + cellmin, MAX_PLAYERS + cellmin) - cellmin])

/*-------------------------------------------------------------------------*//**
 * <param name="idx">Index of the string in the parameters.</param>
 * <returns>
 *  string
 * </returns>
 * <remarks>
 *  Is passed the result of getarg, which will be the address of a string (in
 *  theory) and uses that for DMA to get the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define getstring        returnstringarg
#define GetString        getstring
#define getstringarg     va_getstring
#define GetStringArg     va_getstring
#define ReturnStringArg  returnstringarg

stock returnstringarg(idx)
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
	// Blank the first cell so "strcat" behaves like "strcpy".
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
 *  Just wraps `format` and returns a string instead.
 *
 *  Has extra code to ensure that it works correct on the old compiler.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock va_return(const fmat[], GLOBAL_TAG_TYPES:...)
{
	#pragma unused fmat
	
	static
		sFrm,
		sRet,
		sCnt,
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
 *  Checks if a given string is numeric.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock isnumeric(str[])
{
	P:7("isnumeric called: \"%s\"", str);
	new
		i;
	while (IS_IN_RANGE(str[i], '0', '9' + 1)) ++i;
	//while ((ch = str[i++])) if (!('0' <= ch <= '9')) return 0;
	return !str[i];
}

#if !defined _inc_sscanf || 1
	/*---------------------------------------------------------------------*//**
	 *
	 * <param name="string">String to convert to a number.</param>
	 * <returns>
	 *  value of the passed hex string.
	 * </returns>
	 * <remarks>
	 *  Now stops on invalid characters.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	stock hexstr(string[])
	{
		new
			ret,
			val,
			i;
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
	
	/*---------------------------------------------------------------------*//**
	 *
	 * <param name="string">String to try convert to a boolean.</param>
	 * <returns>
	 *  bool: passed boolean.
	 * </returns>
	 * <remarks>
	 *  This can take a number of ways of representing booleans - 0, false and
	 *  nothing there.  Anything not one of those things (false is not case
	 *  sensitive) is assumed true.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	stock bool:boolstr(string[])
	{
		// Hooray for De Morgan's rules!
		return string[0] && string[0] != '0' && strcmp(string, "false", true);
	}
	
	/*---------------------------------------------------------------------*//**
	 *
	 * <param name="string">String to try convert to a boolean.</param>
	 * <returns>
	 *  bool: passed boolean.
	 * </returns>
	 * <remarks>
	 *  This takes a value in 0110101 (boolean) format and returns it as a
	 *  regular value.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	stock binstr(string[])
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
#endif

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Base64Encode
 * </summary>
 * <remarks>
 *  Encodes data using proper base64.  This code is complicated by the fact that
 *  PAWN packed strings are backwards by cells in memory, so we need to do the
 *  writes in what seems like a strange order.
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
		ret;
	num *= cellbytes;
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
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  Base64Decode
 * </summary>
 * <remarks>
 *  Decodes data using proper base64.
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
		blocks,
		num;
	// Work out the final length.  Subtract some for incomplete bytes and
	// insufficient destination data.
	num = strlen(src);
	len *= cellbytes;
	blocks = num / cellbytes;
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
 *  rawMemcpy
 * </summary>
 * <param name="dest">Destination address.</param>
 * <param name="src">Source data.</param>
 * <param name="bytes">Number of bytes to copy.</param>
 * <remarks>
 *  Like memcpy, but takes addresses instead of arrays.  Also far less secure.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock rawMemcpy(dest, src, bytes)
{
	// Don't use "MOVS" as these blocks might overlap.
	#emit PUSH.S     bytes
	#emit PUSH.S     bytes
	#emit PUSH.C     0
	#emit PUSH.S     src
	#emit PUSH.S     dest
	#emit PUSH.C     20
	#emit SYSREQ.C   memcpy
	#emit STACK      24
	#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="arr">Array or address to set to a value.</param>
 * <param name="iValue">What to set the cells to.</param>
 * <param name="iSize">Number of cells to fill.</param>
 * <remarks>
 *  Based on code by Slice:
 *
 *  <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781" />
 *
 *  Modified to use binary flags instead of a loop.
 *
 *  "memset" takes an array, the size of the array, and a value to fill it with
 *  and sets the whole array to that value.
 *
 *  "rawmemset" is similar, but takes an AMX data segment address instead and
 *  the size is in bytes, not cells.  However, the size must still be a multiple
 *  of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock memset(arr[], val = 0, size = sizeof (arr))
{
	new
		addr;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return rawMemset(addr, val, size * 4);
}

/*-------------------------------------------------------------------------*//**
 * <param name="iAddress">Array or address to set to a value.</param>
 * <param name="iValue">What to set the cells to.</param>
 * <param name="iSize">Number of cells to fill.</param>
 * <remarks>
 *  Based on code by Slice:
 *
 *  <a href="http://forum.sa-mp.com/showthread.php?p=1606781#post1606781" />
 *
 *  Modified to use binary flags instead of a loop.
 *
 *  "memset" takes an array, the size of the array, and a value to fill it with
 *  and sets the whole array to that value.
 *
 *  "rawmemset" is similar, but takes an AMX data segment address instead and
 *  the size is in bytes, not cells.  However, the size must still be a multiple
 *  of 4.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock rawMemset(iAddress /* 12 */, iValue /* 16 */, iSize /* 20 */)
{
	// They are really, trust me!
	#pragma unused iAddress, iSize, iValue
	// The first time this is called it rewrites itself.  Any other times it is
	// called it just uses the new code.  This is like doing:
	//  
	//  static
	//      bInitialised = false;
	//  if (!bInitialised)
	//  {
	//      // Do something
	//      bInitialised = true;
	//  }
	//  // Do rest.
	//  
	// But better (though FAR more complex).
	// There is NO checking here that we don't write the function bigger than
	// the space available, or even that we don't overwrite "CIP", which would
	// be bad.  The only way to make sure that doesn't happen is write a little
	// with a lot of code!
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  rawMemset
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 80), // Don't need any more than that.
	// Frankly by this point we have probably already written more code than
	// will be generated!
	@emit PROC
	@emit LOAD.S.pri 20
	@emit CONST.alt  0xFFFFFFC
	@emit AND
	@emit STOR.pri   (ctx[AsmContext_buffer] + 13 * 4)
	// The documentation says "PRI" should be a pointer, but that's not true!
	@emit LOAD.S.alt 12
	@emit LOAD.S.pri 16
	@emit FILL       0
	// Return the bytes filled.
	@emit LOAD.pri   (ctx[AsmContext_buffer] + 13 * 4)
	@emit RETN
	// Do the second version.
	#emit CONST.pri  memset
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 80),
	@emit PROC
	@emit LOAD.S.pri 20
	@emit SHL.C.pri  2
	@emit STOR.pri   (ctx[AsmContext_buffer] + 12 * 4)
	@emit LOAD.S.alt 12
	@emit LOAD.S.pri 16
	@emit FILL       0
	// Return the bytes filled.
	@emit LOAD.pri   (ctx[AsmContext_buffer] + 12 * 4)
	@emit RETN
	// Call this function again (the new version), but don't let the compiler
	// know...  First clear the stack.
	#emit LCTRL      5
	#emit SCTRL      4
	#emit CONST.pri  rawMemset
	#emit ADD.C      4
	#emit SCTRL      6
	// Never hit because of going to an earlier "RETN".
	return 0; //memset("", 0, 0);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  ReturnPlayerName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *  Now uses a global array to avoid repeated function calls.  Actually doesn't
 *  because that causes issues with multiple scripts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ReturnPlayerName(playerid)
{
	new
		str[MAX_PLAYER_NAME];
	GetPlayerName(playerid, str, sizeof (str));
	return str;
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
 *  InterpolateColour(startcolor, endcolor, value, maxvalue, minvalue = 0);
 * </summary>
 * <param name="startcolor">One of the two colours.</param>
 * <param name="endcolor">The other of the two colours.</param>
 * <param name="value">The interpolation value between the endpoints.</param>
 * <param name="maxvalue">One of the two numbers.</param>
 * <param name="minvalue">The other of the two numbers.</param>
 * <remarks>
 *  This function takes two endpoint values (minvalue and maxvalue, with
 *  minvalue defaulting to 0), along with a third value (value) whose distance
 *  between the two endpoints is calculated (as a percentage).  This percentage
 *  value is then applied to the two colours given to find a third colour at
 *  some point between those two colours.
 *
 *  For example, if the endpoints given are "0" and "10", and the value given is
 *  "3", then that is "30%" of the way between the two endpoints.  We therefore
 *  want to find a colour that is 30% of the way between the two given colours.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// "Interpolation" is the technical name for what you are doing here.
#define InterpolateColor InterpolateColour
stock InterpolateColour(startcolor, endcolor, value, maxvalue, minvalue = 0)
{
    if (value >= maxvalue) return endcolor;
    if (value <= minvalue) return startcolor;
	static r, g, b, a;
	new
		time  = maxvalue - minvalue,
		stage = value    - minvalue;
	return
		// Step 1:  Get the starting colour components.
		r = startcolor >>> 24       ,
		g = startcolor >>> 16 & 0xFF,
		b = startcolor >>> 8  & 0xFF,
		a = startcolor        & 0xFF,
		// Step 2:  Interpolate between the end points, and add to the start.
		r += ((endcolor >>> 24       ) - r) * stage / time,
		g += ((endcolor >>> 16 & 0xFF) - g) * stage / time,
		b += ((endcolor >>> 8  & 0xFF) - b) * stage / time,
		a += ((endcolor        & 0xFF) - a) * stage / time,
		// Step 3:  Combine the individual components.
		(r << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

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
 *  Modifies "start" and "end" to be tight on text in "str".
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

//#define ftell(%0) fseek((%0), 0, seek_current)

static stock Utils_PreSort(arr[], num = sizeof (arr))
{
	// Very simple bubble sort (fast for pre-sorted arrays).
	new
		bool:sort;
	do
	{
		sort = false;
		for (new j = 1, temp; j != num; ++j)
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
		tot;
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
		ret,
		count = 0,
		cn,
		cc;
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

stock Range(arr[], num = sizeof (arr))
{
	new
		min = cellmax,
		max = cellmin,
		cur;
	while (num)
	{
		cur = arr[--num];
		if (cur < min)
			min = cur;
		if (cur > max)
			max = cur;
	}
	return max - min;
}

#include "..\YSI_Coding\y_va"
#include "..\YSI_Internal\y_shortfunc"

