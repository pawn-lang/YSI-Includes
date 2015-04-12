/**--------------------------------------------------------------------------**\
					=================================
					Y Sever Includes - Misc Functions
					=================================
Description:
	Misc functions used throughout.
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
	
	The Original Code is the YSI utils include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
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
	
Version:
	0.1.3
Changelog:
	06/10/12:
		Upgraded "memset" to use "FILL".
	22/12/11:
		Changed "ceildiv" to only evaluate arguments once.
	05/12/11:
		Added NO_VALUE to test if macros have no value.
	08/09/10:
		Added strcpy and StripNL.
	08/08/10:
		Scrapped almost everything.  Only VERY usefult things go in now.
Functions:
	Stock:
		StripNL - Strips the newline characters from the end of a string.
	Inline:
		iseven - Checks if a number is even.
		isodd - Checks if a number is odd.
		isnull - Checks if a string is NULL ("\1\0").
		strcpy - Copy one string to another.
Variables:
	Global:
		TRUE - True hack for infinate loops.
		FALSE - False hack for one-time loops.
		NULL - 1 long string for passing via Call(Remote|Local)Function.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_utils
	#endinput
#endif
#define _INC_y_utils

#include "..\YSI_Internal\y_version"

#include "..\YSI_Core\y_debug"
#include "..\YSI_Storage\y_amx"
//#tryinclude <sscanf>

#include "..\amx\asm"
//asm"

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

#define UNSIGNED(%0) ((%0) - cellmin)

// Define "volatile" as nothing.
#if !defined volatile
	#define volatile
#endif

#define YSIM_MASTER #M

#define YSIM_RETURN #R

#define YSIM_CALLER #C

#define YSIM_TEXT_D #T
#define YSIM_TEXT_L #L
#define YSIM_TEXT_S #Y
#define YSIM_TEXT_P #Z

#define YSIM_ORDERS #O

#define YSIM_HFIRST #H

#define YSIM_OPDRET #D

#define YSIM_TXTFND #X

#define YSIM_TXTIND #I

#define YSIM_TXTLEN #E

#define YSIM_LOG_IN #U

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

/**--------------------------------------------------------------------------**\
<summary>
	UCMP(value, upper);
</summary>
<param name="value">The unsigned number to compare.</param>
<param name="upper">The upper limit.</param>
<returns>
	An unsigned comparison between the two values.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define UCMP(%0,%1) IS_IN_RANGE(%0,0,(%1)) //(((%0) - cellmin) < ((%1) - cellmin))
#define VALID_PLAYERID(%0) UCMP((%0), MAX_PLAYERS)

/**--------------------------------------------------------------------------**\
<summary>
	IS_IN_RANGE(value, lower, upper);
</summary>
<param name="value">The number to compare.</param>
<param name="lower">The lower limit.</param>
<param name="upper">The upper limit.</param>
<returns>
	Is the value in the given range.
</returns>
<remarks>
	Equivalent to:
	
		(%1) <= (%0) < (%2)
	
</remarks>
\**--------------------------------------------------------------------------**/

#define IS_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin)))
#define NOT_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))>=((%2)-((%1)+cellmin)))

/**--------------------------------------------------------------------------**\
<summary>
	ceildiv(numerator, denominator);
</summary>
<param name="numerator">The top of the division.</param>
<param name="denominator">The bottom of the division.</param>
<returns>
	(numerator / denominator) rounded up.
</returns>
<remarks>
	Normal integer division ALWAYS rounds down - this always rounds up.
</remarks>
\**--------------------------------------------------------------------------**/

#define ceildiv(%0,%1) (((%0)-1)/(%1)+1)

/**--------------------------------------------------------------------------**\
<summary>
	floordiv(numerator, denominator);
</summary>
<param name="numerator">The top of the division.</param>
<param name="denominator">The bottom of the division.</param>
<returns>
	(numerator / denominator) rounded down.
</returns>
<remarks>
	Normal integer division ALWAYS rounds down - this also always rounds down,
	making it a little pointless, but also more explicit in function.
</remarks>
\**--------------------------------------------------------------------------**/

#define floordiv(%0,%1) ((%0)/(%1))

/**--------------------------------------------------------------------------**\
<summary>isnull</summary>
<param name="str">String to check if is null.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined isnull
	#define isnull(%1) \
		((%1[0] == 0) || (%1[0] == 1 && %1[1] == 0))
#endif

/**--------------------------------------------------------------------------**\
<summary>isodd</summary>
<param name="value">Value to check if is odd.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define isodd(%1) \
	((%1) & 1)

/**--------------------------------------------------------------------------**\
<summary>iseven</summary>
<param name="value">Value to check if is even.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define iseven(%1) \
	(!isodd(%1))

/**--------------------------------------------------------------------------**\
<summary>strcpy</summary>
<param name="dest">Destination string.</param>
<param name="src">Source string.</param>
<param name="len">(Implicit) maximum length of the destination.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define strcpy(%0,%1) \
	strcat((%0[0] = '\0', %0), %1)

/**--------------------------------------------------------------------------**\
<summary>StripNL</summary>
<param name="str[]">The string to remove the newline characters from</param>
<returns>
	-
</returns>
<remarks>
	Updated from old versions, should be more efficient
</remarks>
\**--------------------------------------------------------------------------**/

stock StripNL(str[])
{
	P:7("StripNL called: \"%s\"", str);
	new
		i = strlen(str);
	while (i-- && str[i] <= ' ') str[i] = '\0';
}

/**--------------------------------------------------------------------------**\
<summary>endofline</summary>
<param name="line[]">String to check.</param>
<param name="pos">Postion to start from.</param>
<returns>
	-
</returns>
<remarks>
	Checks if the current point in a line is the end of non-whitespace data.
</remarks>
\**--------------------------------------------------------------------------**/

stock endofline(line[], pos)
{
	P:7("endofline called: \"%s\", %i", line, pos);
	if (NOT_IN_RANGE(pos, 0, strlen(line))) return 0;
	//if (pos < 0 || pos > strlen(line)) return 0;
	while (line[pos]) if (line[pos++] > ' ') return 0;
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>chrfind</summary>
<param name="needle">The character to find.</param>
<param name="haystack[]">The string to find it in.</param>
<param name="start">The offset to start from.</param>
<returns>
	Fail - -1, Success - pos
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>IPToInt</summary>
<param name="ip[]">Dot notation IP to convert to an integer.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>bernstein</summary>
<param name="string[]">the string to hash.</param>
<returns>
	the bernstein hash of the input string
</returns>
<remarks>
	This is a 32bit hash system so is not very secure, however we're only
	using this as a string enumerator to uniquely identify strings easilly
	and allow for a binary search of strings based on the hash of their name.
	crc32, then jenkins were originally used however this is far faster, if a
	little collision prone, but we're checking the strings manually anyway.
	This doesn't matter as it would be done regardless of hash method, so this
	doesn't need to be accounted for.  Speed is all that matters with at 
	least a bit of non collision (the number of strings we're dealing with,
	this should have none-few collisions).
	
	I modified it slightly from the original code pasted by aru, to code
	closer to the code http://www.burtleburtle.net/bob/hash/doobs.html and
	to work with PAWN (and shaved 0.2�s off the time for one call :D).
	
	Uber reduced version (just for fun):
	b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
	
	Update: Contrary to what I said above this is also used to identify colour
	strings for the updated text system involving file based styling and this
	is not checked for collisions as it's unimportant.  But this doesn't affect
	the function at all, I just mentioned it here for "interest".
	
	Rewritten in self-generating assembly.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>ishex</summary>
<param name="str[]">String to check.</param>
<returns>
	true/false.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>unpack</summary>
<param name="str[]">String to unpack</param>
<returns>
	unpacked string
</returns>
<remarks>
	Mainly used for debugging.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>GetIP</summary>
<param name="playerid">Player to get IP of.</param>
<returns>
	IP as a 32bit int.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

// Cunning macro only uses "%0" once, yet is still safe.
#define GetIP(%0) (YSI_gPlayerIP[min((%0) + cellmin, MAX_PLAYERS + cellmin) - cellmin])

/**--------------------------------------------------------------------------**\
<summary>getstring</summary>
<param name="addr">Address of the string on the heap.</param>
<returns>
	string
</returns>
<remarks>
	Is passed the result of getarg, which will be the address of a string (in
	theory) and uses that for DMA to get the string.
</remarks>
\**--------------------------------------------------------------------------**/

stock getstring(addr)
{
	new
		ret[YSI_MAX_STRING];
	va_getstring(ret, addr);
	return ret;
}

stock getstringarg(addr)
{
	new
		ret[YSI_MAX_STRING];
	va_getstring(ret, addr);
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>isnumeric</summary>
<param name="str[]">String to check</param>
<returns>
	-
</returns>
<remarks>
	Checks if a given string is numeric.
</remarks>
\**--------------------------------------------------------------------------**/

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
	/**----------------------------------------------------------------------**\
	<summary>hexstr</summary>
	<param name="	string[]">String to convert to a number.</param>
	<returns>
		value of the passed hex string.
	</returns>
	<remarks>
		Now stops on invalid characters.
	</remarks>
	\**----------------------------------------------------------------------**/
	
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
	
	/**----------------------------------------------------------------------**\
	<summary>boolstr</summary>
	<param name="	string[]">String to try convert to a boolean.</param>
	<returns>
		bool: passed boolean.
	</returns>
	<remarks>
		This can take a number of ways of representing booleans - 0, false and
		nothing there.  Anything not one of those things (false is not case
		sensitive) is assumed true.
	</remarks>
	\**----------------------------------------------------------------------**/
	
	stock bool:boolstr(string[])
	{
		// Hooray for De Morgan's rules!
		return string[0] && string[0] != '0' && strcmp(string, "false", true);
	}
	
	/**----------------------------------------------------------------------**\
	<summary>binstr</summary>
	<param name="	string[]">String to try convert to a boolean.</param>
	<returns>
		bool: passed boolean.
	</returns>
	<remarks>
		This takes a value in 0110101 (boolean) format and returns it as a
		regular value.
	</remarks>
	\**----------------------------------------------------------------------**/
	
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

/**--------------------------------------------------------------------------**\
<summary>
	rawMemcpy
</summary>
<param name="dest">Destination address.</param>
<param name="src">Source data.</param>
<param name="bytes">Number of bytes to copy.</param>
<returns>
	-
</returns>
<remarks>
	Like memcpy, but takes addresses instead of arrays.  Also far less secure.
</remarks>
\**--------------------------------------------------------------------------**/

forward __rawMemcpy__(dest[], src[], bytes);

public __rawMemcpy__(dest[], src[], bytes)
{
	memcpy(dest, src, 0, bytes, bytes);
	memset("", 0, 0);
	strcmp("", "");
}

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

/**--------------------------------------------------------------------------**\
<summary>
	memset
	rawMemset
</summary>
<param name="arr[], iAddress">Array or address to set to a value.</param>
<param name="iValue">What to set the cells to.</param>
<param name="iSize">Number of cells to fill.</param>
<returns>
	-
</returns>
<remarks>
	Based on code by Slice:
	
	http://forum.sa-mp.com/showthread.php?p=1606781#post1606781
	
	Modified to use binary flags instead of a loop.
	
	"memset" takes an array, the size of the array, and a value to fill it with
	and sets the whole array to that value.
	
	"rawmemset" is similar, but takes an AMX data segment address instead and
	the size is in bytes, not cells.  However, the size must still be a multiple
	of 4.
</remarks>
\**--------------------------------------------------------------------------**/

stock memset(arr[], val = 0, size = sizeof (arr))
{
	new
		addr;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	return rawMemset(addr, val, size * 4);
}

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

/**--------------------------------------------------------------------------**\
<summary>
	ReturnPlayerName
</summary>
<param name="playerid">Player whose name you want to get.</param>
<returns>
	-
</returns>
<remarks>
	Now uses a global array to avoid repeated function calls.  Actually doesn't
	because that causes issues with multiple scripts.
</remarks>
\**--------------------------------------------------------------------------**/

stock ReturnPlayerName(playerid)
{
	new
		str[MAX_PLAYER_NAME];
	GetPlayerName(playerid, str, sizeof (str));
	return str;
}

/**--------------------------------------------------------------------------**\
<summary>
	ftouch(filename);
</summary>
<param name="filename">The file to "touch".</param>
<returns>
	0 - File already exists.
	1 - File was created.
	-1 - File was not created.
</returns>
<remarks>
	This "touches" a file in the Unix sense of creating it but not opening or
	editing it in any way.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>
	InterpolateColour(startcolor, endcolor, value, maxvalue, minvalue = 0);
</summary>
<param name="startcolor">One of the two colours.</param>
<param name="endcolor">The other of the two colours.</param>
<param name="value">The interpolation value between the endpoints.</param>
<param name="maxvalue">One of the two numbers.</param>
<param name="minvalue">The other of the two numbers.</param>
<returns>
	-
</returns>
<remarks>
	This function takes two endpoint values (minvalue and maxvalue, with
	minvalue defaulting to 0), along with a third value (value) whose distance
	between the two endpoints is calculated (as a percentage).  This percentage
	value is then applied to the two colours given to find a third colour at
	some point between those two colours.
	
	For example, if the endpoints given are "0" and "10", and the value given is
	"3", then that is "30%" of the way between the two endpoints.  We therefore
	want to find a colour that is 30% of the way between the two given colours.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>SkipWhitespace</summary>
<param name="str[]">The string to skip over part of.</param>
<param name="pos">The start of the whitespace.</param>
<returns>
	The end of the whitespace.
</returns>
<remarks>
	Doesn't skip over NULL terminators.
</remarks>
\**--------------------------------------------------------------------------**/

stock SkipWhitespace(const str[], pos)
{
	while (IS_IN_RANGE(str[pos], '\0' + 1, ' ' + 1)) ++pos;
	//while ('\0' < str[pos] <= ' ') ++pos;
	return pos;
}

/**--------------------------------------------------------------------------**\
<summary>Trim</summary>
<param name="str[]">The string to trim.</param>
<param name="start">Start of the substring.</param>
<param name="end">End of the substring.</param>
<returns>
	-
</returns>
<remarks>
	Modifies "start" and "end" to be tight on text in "str".
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>ftell</summary>
<param name="File:f">The file to get our position in.</param>
<returns>
	The current position in the file.
</returns>
<remarks>
	Doesn't seem to work despite documentation claiming it will.
</remarks>
\**--------------------------------------------------------------------------**/

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

stock Sum(const arr[], num = sizeof (arr))
{
	new
		tot;
	while (num) tot += arr[--num];
	return tot;
}

stock Mean(const arr[], num = sizeof (arr))
{
	return Sum(arr, num) / num;
}

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

stock Median(arr[], num = sizeof (arr))
{
	Utils_PreSort(arr, num);
	new
		idx = num >>> 1;
	if (num & 1) return arr[idx];
	else return (arr[idx] + arr[idx - 1]) >> 1;
}

stock Range(arr[], num = sizeof (arr))
{
	Utils_PreSort(arr, num);
	return arr[num - 1] - arr[0];
}

#include "..\YSI_Coding\y_va"
#include "..\YSI_Internal\y_shortfunc"

