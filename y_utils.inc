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

#include "internal\y_version"

#include "y_debug"
#include "y_amx"
//#tryinclude <sscanf>

/*// "File,Float," must remain last always.
#if defined CUSTOM_TAG_TYPES
	#define File,Float, Float,File,CUSTOM_TAG_TYPES
#else
	#define File,Float, Float,File
#endif*/
// Add new tags to the START of this list.
#include "internal\y_globaltags"

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

#define ceildiv(%0,%1) \
	(((%0)-1)/(%1)+1)

#define floordiv(%0,%1) \
	((%0)/(%1))

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
	P:3("StripNL called: \"%s\"", str);
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
	P:3("endofline called: \"%s\", %i", line, pos);
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
	P:3("chrfind called: %c, \"%s\", %i", needle, haystack, start);
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
	P:3("chrfind called: %c, \"%s\", %i", needle, haystack, start);
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
	P:3("bernstein called: \"%s\"", string);
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
	P:3("ishex called: \"%s\"", str);
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
	P:3("unpack called: \"%s\"", str);
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
	P:3("isnumeric called: \"%s\"", str);
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
	memset
	rawMemset
</summary>
<param name="arr[], iAddress">Array or address to set to a value.</param>
<param name="iSize">Number of cells to fill.</param>
<param name="iValue">What to set the cells to.</param>
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
	the size is in bytes, not cells.
</remarks>
\**--------------------------------------------------------------------------**/

stock memset(arr[], size = sizeof (arr), val = 0)
{
	new
		addr;
	#emit LOAD.S.pri arr
	#emit STOR.S.pri addr
	// Convert the size from cells to bytes.
	rawMemset(addr, size * 4, val);
	return 0;
}

stock rawMemset(iAddress, iSize, iValue)
{
	// Loop until there are only little bits left to fill.
	while (iSize >= 4096)
	{
		// I have to do this because the FILL instruction doesn't accept a
		// dynamic number.
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 4096
		iSize    -= 4096;
		iAddress += 4096;
	}
	if (iSize & 2048)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 2048
		iAddress += 2048;
	}
	if (iSize & 1024)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 1024
		iAddress += 1024;
	}
	if (iSize & 512)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 512
		iAddress += 512;
	}
	if (iSize & 256)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 256
		iAddress += 256;
	}
	if (iSize & 128)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 128
		iAddress += 128;
	}
	if (iSize & 64)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 64
		iAddress += 64;
	}
	if (iSize & 32)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 32
		iAddress += 32;
	}
	if (iSize & 16)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 16
		iAddress += 16;
	}
	if (iSize & 8)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 8
		iAddress += 8;
	}
	if (iSize & 4)
	{
		#emit LOAD.S.alt iAddress
		#emit LOAD.S.pri iValue
		#emit FILL 4
		iAddress += 4;
	}
}

//#if !defined ReturnPlayerName
stock ReturnPlayerName(playerid)
{
	new
		str[MAX_PLAYER_NAME];
	GetPlayerName(playerid, str, sizeof (str));
	return str;
}
//#endif

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

#include "y_va"
