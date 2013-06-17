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

#include "..\YSI-Internal\y_version"

#include "..\YSI-Core\y_debug"
#include "..\YSI-Storage\y_amx"
//#tryinclude <sscanf>

#include "..\amx\asm"
//asm"

/*// "File,Float," must remain last always.
#if defined CUSTOM_TAG_TYPES
	#define File,Float, Float,File,CUSTOM_TAG_TYPES
#else
	#define File,Float, Float,File
#endif*/
// Add new tags to the START of this list.
#include "..\YSI-Internal\y_globaltags"

// VERY VERY VERY IMPORTANT!!! y_inline uses "130" instead of "YSI_MAX_STRING"
// for two lines (one is "520" for "130 * 4").
#define YSI_MAX_STRING                  (130)

#define FUNCTION_LENGTH                 (32)

#define NO_VALUE(%0) ((2*%0-1+1)==-1)

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
	NULL[2] = {1, 0};
#endif

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
//	memcpy(%0,%1,0,strlen(%1)*4+4,%2)

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
	if (pos < 0 || pos > strlen(line)) return 0;
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

//#define chrfind(%0'%1'%2,%3) str

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
</remarks>
\**--------------------------------------------------------------------------**/

stock bernstein(string[])
{
	P:7("bernstein called: \"%s\"", string);
	new
		hash = -1,
		i,
		j;
	while ((j = string[i++]))
	{
		hash = hash * 33 + j;
		//printf("Hash stage %d: %d", i - 1, hash);
	}
	return hash;
}

/**--------------------------------------------------------------------------**\
<summary>ishex</summary>
<param name="str[]">String to check.</param>
<returns>
	-
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
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) i = 2;
	while (str[i])
	{
		cur = str[i++];
		if (!(('0' <= cur <= '9') || ('A' <= cur <= 'F') || ('a' <= cur <= 'f'))) return 0;
		//if ((cur < '0') || ('9' < cur < 'A') || ('F' < cur < 'a') || (cur > 'f')) return 0;
	}
	return 1;
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

stock GetIP(playerid)
{
	new
		ip[16];
	GetPlayerIp(playerid, ip, sizeof (ip));
	new
		ipv = strval(ip) << 24,
		pos = 0;
	while (pos < 15 && ip[pos++] != '.') {}
	ipv += strval(ip[pos]) << 16;
	while (pos < 15 && ip[pos++] != '.') {}
	ipv += strval(ip[pos]) << 8;
	while (pos < 15 && ip[pos++] != '.') {}
	ipv += strval(ip[pos]);
	return ipv;
}

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
		ch,
		i;
	while ((ch = str[i++])) if (!('0' <= ch <= '9')) return 0;
	return 1;
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
		if (!string[0] || string[0] == '0' || !strcmp(string, "false", true)) return false;
		return true;
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
}

stock rawMemcpy(dest, src, bytes)
{
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
	return memset("", 0, 0);
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

/*
#define ReturnPlayerName(%0) (YSI_gPlayerName[(%0)])

stock
	YSI_gPlayerName[MAX_PLAYERS][MAX_PLAYER_NAME];

public OnPlayerConnect(playerid)
{
	GetPlayerName(playerid, YSI_gPlayerName[playerid], sizeof (YSI_gPlayerName[]));
	#if defined y_utils_OnPlayerConnect
		y_utils_OnPlayerConnect(playerid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#if defined y_utils_OnPlayerConnect
	forward y_utils_OnPlayerConnect(playerid);
#endif

stock y_utils_SetPlayerName(playerid, name[])
{
	if (SetPlayerName(playerid, name))
	{
		strcpy(YSI_gPlayerName[playerid], name);
		return 1;
	}
	return 0;
}
#if defined _ALS_SetPlayerName
	#undef SetPlayerName
#else
	#define _ALS_SetPlayerName
#endif
#define SetPlayerName y_utils_SetPlayerName
*/

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

#include "..\YSI-Coding\y_va"
