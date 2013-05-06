/**--------------------------------------------------------------------------**\
					===================================
					 y_punycode - Character encodings.
					===================================
Description:
	Functions for converting unicode strings to and from punycode, to be
	represented in just ASCII characters.  Based on several public
	implementations and the RFC, adapted for PAWN.
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
	
	The Original Code is the YSI malloc include.
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.1
Changelog:
	26/04/13:
		First version.
Functions:
	Public
		-
	Core:
		-
	Stock:
		Puny_Encode - Convert a Unicode string to Punycode.
		Puny_Decode - Convert a Punycode string to Unicode.
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

#include "y_version"
#include "y_shortfunc"
#include "y_pp"

#define PUNY_BASE (36)
#define PUNY_CHAR ('-')

static stock const
	PUNY_TMIN = 1,
	PUNY_TMAX = 26,
	PUNY_SKEW = 38,
	PUNY_BIAS = 72,
	PUNY_INIT = 128,
	PUNY_DAMP = 700,
	// Some versions use "-1" or "cellmax", the RFC uses "PUNY_BASE".
	YSI_gscDecoder[128] =
		{
			PP_LOOP<48>(PUNY_BASE)(,),
			// '0' - '9'.
			26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			PP_LOOP<7>(PUNY_BASE)(,),
			// 'A' - 'Z'.
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
			PP_LOOP<6>(PUNY_BASE)(,),
			// 'a' - 'z'.
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
			PP_LOOP<5>(PUNY_BASE)(,)
		};

/**--------------------------------------------------------------------------**\
<summary>Puny_Decode</summary>
<param name="dst">Where to store the converted string.</param>
<param name="src">The string to convert.</param>
<param name="wlen">The length of the destination.</param>
<param name="delimiter">What character to place between the parts.</param>
<returns>
	-
</returns>
<remarks>
	Takes a unicode string and converts it to punycode.
</remarks>
\**--------------------------------------------------------------------------**/

stock Puny_Decode(string:dst[], string:src[], wlen = sizeof (dst), const delimiter = PUNY_CHAR)
{
	new
		rlen = strlen(src),
		basicEnd = rlen;
	while (basicEnd--)
	{
		if (src[basicEnd] == delimiter) break;
	}
	// Enough space for the string, and not empty.
	if (0 < ++basicEnd < wlen)
	{
		// Enough space to store the basic string (and no punycode string).
		dst[0] = '\0',
		strcat(dst, src, basicEnd);
	}
	else
	{
		return dst[0] = '\0', strcat(dst, src, wlen), 1;
	}
	--wlen;
	for (
		new
			n     = PUNY_INIT,
			bias  = PUNY_BIAS,
			delta = 0,
			codePointsWritten = basicEnd - 1,
			pointsRead = basicEnd;
		pointsRead != rlen && codePointsWritten != wlen;
		)
	{
		new
			oldDelta = delta;
		for (new w = 1, k = PUNY_BASE; pointsRead != rlen; k += PUNY_BASE)
		{
			new
				digit = YSI_gscDecoder[src[pointsRead++]];
			if (digit == PUNY_BASE || digit > (cellmax - delta) / w) return 0;
			delta += digit * w;
			new
				t = (k <= bias) ? (PUNY_TMIN) : ((k >= bias + PUNY_TMAX) ? (PUNY_TMAX) : (k - bias));
			// Find the end of the current code.
			if (digit < t) break;
			if (w > cellmax / (PUNY_BASE - t)) return 0;
			w *= PUNY_BASE - t;
		}
		bias = Puny_Adapt(delta - oldDelta, ++codePointsWritten, oldDelta == 0);
		if (delta / codePointsWritten > cellmax - n) return 0;
		static
			sTinyString[2];
		n += delta / codePointsWritten,
		delta %= codePointsWritten,
		sTinyString[0] = n,
		strins(dst, sTinyString, delta++, wlen + 1);
	}
	//dst[codePointsWritten] = '\0';
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Puny_Encode</summary>
<param name="dst">Where to store the converted string.</param>
<param name="src">The string to convert.</param>
<param name="wlen">The length of the destination.</param>
<param name="delimiter">What character is between the parts.</param>
<returns>
	-
</returns>
<remarks>
	Takes a punycode string and converts it to unicode.
</remarks>
\**--------------------------------------------------------------------------**/

stock Puny_Encode(string:dst[], string:src[], wlen = sizeof (dst), const delimiter = PUNY_CHAR)
{
	new
		widx,
		rlen = strlen(src);
	--wlen;
	for (new ridx = 0; ridx != rlen; ++ridx)
	{
		if ('\0' < src[ridx] <= '~')
		{
			if (widx == wlen) return (dst[widx] = '\0');
			dst[widx++] = src[ridx];
		}
	}
	// Wrote out all the characters.
	if (widx == rlen) return (dst[widx] = '\0'), 1;
	if (widx < wlen) dst[widx++] = delimiter;
	else return (dst[widx] = '\0');
	// Set up punycode variables.
	for (
		new
			n     = PUNY_INIT,
			bias  = PUNY_BIAS,
			delta = 0,
			codePointsWritten = widx - 1,
			basicPointsWritten = widx;
		codePointsWritten < rlen;
		)
	{
		new
			m = cellmax;
		for (new ridx = 0; ridx != rlen; ++ridx)
		{
			if (n <= src[ridx] < m)
			{
				// Find the lowest Unicode character.
				m = src[ridx];
			}
		}
		// Make sure the number isn't too big to encode.
		if ((m - n) > (cellmax - delta) / (codePointsWritten + 1)) return (dst[widx] = '\0');
		// More punycode state machine.
		delta += (m - n) * (codePointsWritten + 1),
		n = m;
		for (new ridx = 0; ridx != rlen; ++ridx)
		{
			if (src[ridx] < n)
			{
				if (++delta == 0) return (dst[widx] = '\0');
			}
			else if (src[ridx] == n)
			{
				widx += Puny_EncodeVar(bias, delta, dst[widx], wlen - widx),
				++codePointsWritten,
				bias = Puny_Adapt(delta, codePointsWritten, (codePointsWritten == basicPointsWritten)),
				delta = 0;
			}
		}
		++n,
		++delta;
	}
	return (dst[widx] = '\0'), 1;
}

/**--------------------------------------------------------------------------**\
<summary>Puny_Basic</summary>
<param name="num">The single number to encode.</param>
<returns>
	-
</returns>
<remarks>
	Convert a single digit to base 36.
</remarks>
\**--------------------------------------------------------------------------**/

#define Puny_Basic(%0) (((%0) > 25) ? ((%0) + ('0' - 25)) : ((%0) + 'a'))

/**--------------------------------------------------------------------------**\
<summary>Puny_EncodeVar</summary>
<param name="bias">Part of the state machine.</param>
<param name="delta">Part of the state machine.</param>
<param name="dst">Array to write to.</param>
<param name="wlen">Size of the array.</param>
<returns>
	-
</returns>
<remarks>
	This is part of how the punycode algorithm encodes numbers as very clever
	strings, but honestly I don't fully understand it!
</remarks>
\**--------------------------------------------------------------------------**/

static stock Puny_EncodeVar(bias, delta, dst[], wlen)
{
	new
		i = 0,
		k = PUNY_BASE,
		t;
	while (i < wlen)
	{
		if (k <= bias) t = PUNY_TMIN;
		else if (k >= bias + PUNY_TMAX) t = PUNY_TMAX;
		else t = k - bias;
		// Find the last digit below the threshold.
		if (delta < t) break;
		new
			c = t + (delta - t) % (PUNY_BASE - t);
		dst[i++] = Puny_Basic(c),
		delta = (delta - t) / (PUNY_BASE - t),
		k += PUNY_BASE;
	}
	if (i < wlen) dst[i++] = Puny_Basic(delta);
	return i;
}

/**--------------------------------------------------------------------------**\
<summary>Puny_Adapt</summary>
<param name="delta">Part of the state machine.</param>
<param name="length">Written string size.</param>
<param name="firstTime">Have special characters already been written?</param>
<returns>
	-
</returns>
<remarks>
	This is part of how the punycode algorithm encodes numbers as very clever
	strings, but honestly I don't fully understand it!
</remarks>
\**--------------------------------------------------------------------------**/

static stock Puny_Adapt(delta, length, bool:firstTime)
{
	if(firstTime) delta /= PUNY_DAMP;
	else delta >>>= 1;
	delta += delta / length;
	new
		k = 0;
	while (delta > (PUNY_BASE - PUNY_TMIN) * PUNY_TMAX >> 1)
	{
		delta /= PUNY_BASE - PUNY_TMIN,
		k += PUNY_BASE;
	}
	return k + (PUNY_BASE - PUNY_TMIN + 1) * delta / (delta + PUNY_SKEW);
}

#undef Puny_Basic
#undef PUNY_BASE
#undef PUNY_CHAR
