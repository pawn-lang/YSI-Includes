#if defined _INC_y_punycode
	#endinput
#endif
#define _INC_y_punycode

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
*/

#include "..\..\YSI_Core\y_utils"

#define PUNY_BASE (36)
#define PUNY_CHAR ('-')
// Some versions use "-1" or "cellmax", the RFC uses "PUNY_BASE".
#define PUNY_INVL PUNY_BASE

static stock const
	PUNY_TMIN = 1,
	PUNY_TMAX = 26,
	PUNY_SKEW = 38,
	PUNY_BIAS = 72,
	PUNY_INIT = 128,
	PUNY_DAMP = 700,
	YSI_gscDecoder[128] =
		{
			PP_LOOP<48>(PUNY_INVL)(,),
			// '0' - '9'.
			26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			PP_LOOP<7>(PUNY_INVL)(,),
			// 'A' - 'Z'.
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
			PP_LOOP<6>(PUNY_INVL)(,),
			// 'a' - 'z'.
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
			PP_LOOP<5>(PUNY_INVL)(,)
		};

/*-------------------------------------------------------------------------*//**
 * <param name="dst">Where to store the converted string.</param>
 * <param name="src">The string to convert.</param>
 * <param name="wlen">The length of the destination.</param>
 * <param name="delimiter">What character is between the parts.</param>
 * <remarks>
 *  Takes a punycode string and converts it to unicode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Puny_Decode(string:dst[], const string:src[], wlen = sizeof (dst), const delimiter = PUNY_CHAR)
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
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="dst">Where to store the converted string.</param>
 * <param name="src">The string to convert.</param>
 * <param name="wlen">The length of the destination.</param>
 * <param name="delimiter">What character to place between the parts.</param>
 * <remarks>
 *  Takes a unicode string and converts it to punycode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Puny_Encode(string:dst[], const string:src[], wlen = sizeof (dst), const delimiter = PUNY_CHAR)
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
	if (widx == rlen) return (dst[widx] = '\0'), -1;
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

/*-------------------------------------------------------------------------*//**
 * <param name="dst">Where to store the converted string.</param>
 * <param name="src">The string to convert.</param>
 * <param name="hash">Store the hash value.</param>
 * <param name="wlen">The length of the destination.</param>
 * <param name="delimiter">What character to place between the parts.</param>
 * <returns>
 *  The length of string read.
 * </returns>
 * <remarks>
 *  Takes a unicode string and converts it to punycode, while at the same time
 *  generating a Bernstein hash of the string.  CASE INSENSITIVE.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Puny_EncodeHash(string:dst[], const string:src[], &hash, wlen = sizeof (dst), const delimiter = PUNY_CHAR)
{
	new
		ch,
		widx,
		rlen,
		sSrc[YSI_MAX_STRING],
		bPacked = ispacked(src);
	--wlen,
	hash = -1;

	if (bPacked) {
		strunpack(sSrc, src);
	} else {
		strcpy(sSrc, src);
	}

	for (new bool:bb = true; ; ++rlen)
	{
		if ((ch = sSrc[rlen]) <= '~')
		{
			if (ch <= ' ')
			{
				if (bb)
				{
					return
						dst[widx] = '\0',
						rlen;
				}
				break;
			}
			ch = tolower(ch),
			dst[widx++] = ch,
			hash = hash * 33 + ch;
		}
		else bb = false;
	}
	// Wrote out all the characters.
	if (widx >= wlen) return (bPacked ? strpack(dst, dst, wlen) : 0), (dst[widx] = '\0'), rlen;
	dst[widx++] = delimiter,
	hash = hash * 33 + delimiter;
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
			ch = tolower(sSrc[ridx]);
			if (n <= ch < m)
			{
				// Find the lowest Unicode character.
				m = ch;
			}
		}
		// Make sure the number isn't too big to encode.
		if ((m - n) > (cellmax - delta) / (codePointsWritten + 1)) return (bPacked ? strpack(dst, dst, wlen) : 0), (dst[widx] = '\0'), rlen;
		// More punycode state machine.
		delta += (m - n) * (codePointsWritten + 1),
		n = m;
		for (new ridx = 0; ridx != rlen; ++ridx)
		{
			ch = tolower(sSrc[ridx]);
			if (ch < n)
			{
				if (++delta == 0) return (bPacked ? strpack(dst, dst, wlen) : 0), (dst[widx] = '\0'), rlen;
			}
			else if (ch == n)
			{
				widx += Puny_EncodeVarHash(bias, delta, dst[widx], wlen - widx, hash),
				++codePointsWritten,
				bias = Puny_Adapt(delta, codePointsWritten, (codePointsWritten == basicPointsWritten)),
				delta = 0;
			}
		}
		++n,
		++delta;
	}
	return (bPacked ? strpack(dst, dst, wlen) : 0), (dst[widx] = '\0'), rlen;
}

/*-------------------------------------------------------------------------*//**
 * <param name="num">The single number to encode.</param>
 * <remarks>
 *  Convert a single digit to base 36.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(_Puny_Basic(num));
#define _Puny_Basic(%0) (((%0) > 25) ? ((%0) + ('0' - 25)) : ((%0) + 'a'))

/*-------------------------------------------------------------------------*//**
 * <param name="bias">Part of the state machine.</param>
 * <param name="delta">Part of the state machine.</param>
 * <param name="dst">Array to write to.</param>
 * <param name="wlen">Size of the array.</param>
 * <param name="hash">Hashed string.</param>
 * <remarks>
 *  This is part of how the punycode algorithm encodes numbers as very clever
 *  strings, but honestly I don't fully understand it!
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Puny_EncodeVarHash(bias, delta, dst[], wlen, &hash)
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
		dst[i] = _Puny_Basic(c),
		hash = hash * 33 + dst[i++],
		delta = (delta - t) / (PUNY_BASE - t),
		k += PUNY_BASE;
	}
	if (i < wlen)
	{
		dst[i] = _Puny_Basic(delta),
		hash = hash * 33 + dst[i++];
	}
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="bias">Part of the state machine.</param>
 * <param name="delta">Part of the state machine.</param>
 * <param name="dst">Array to write to.</param>
 * <param name="wlen">Size of the array.</param>
 * <remarks>
 *  This is part of how the punycode algorithm encodes numbers as very clever
 *  strings, but honestly I don't fully understand it!
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
		dst[i++] = _Puny_Basic(c),
		delta = (delta - t) / (PUNY_BASE - t),
		k += PUNY_BASE;
	}
	if (i < wlen) dst[i++] = _Puny_Basic(delta);
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="delta">Part of the state machine.</param>
 * <param name="length">Written string size.</param>
 * <param name="firstTime">Have special characters already been written?</param>
 * <remarks>
 *  This is part of how the punycode algorithm encodes numbers as very clever
 *  strings, but honestly I don't fully understand it!
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Puny_Adapt(delta, length, bool:firstTime)
{
	if (firstTime) delta /= PUNY_DAMP;
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


/*-------------------------------------------------------------------------*//**
 * <param name="index">The HTTP reference index.</param>
 * <param name="type">How the request should be sent.</param>
 * <param name="url">The (internationalised) URL address.</param>
 * <param name="data">The GET/POST data.</param>
 * <param name="callback">Which function to return the data to.</param>
 * <remarks>
 *  Hooks the "HTTP" function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined PUNY_HTTP_HOOK
	stock Puny_HTTP(index, type, const url[], const data[], const callback[])
	{
		static
			sPart[64], // Maximum legal domain part length.
			sEncoded[256]; // Maximum legal hostname length.
		new
			idx = strfind(url, !"://");
		// Skip any prefix.
		if (idx != -1) idx += 2;
		// Add the protocol.
		sEncoded[0] = '\0',
		strcat(sEncoded, url, idx + 2);
		// Encode all parts.
		new
			prev = idx + 1,
			end = strfind(url, !"/", false, prev);
		if (end == -1) end = strlen(url); // Nothing after the main domain.
		do
		{
			// Find the size of one part.
			idx = strfind(url, !".", false, prev);
			// Only encode the domain part.
			if (!(-1 < idx < end)) idx = end;
			static
				ch;
			// There's no length parameter for "Puny_Encode", so we need a limit.
			ch = url[idx],
			_YSI_ConstMod(url[idx], '\0'),
			sPart[0] = '\0';
			switch (Puny_Encode(sPart, url[prev]))
			{
				// Encoding error.
				case 0: return 0;
				// Encoded something, add the prefix.
				case 1:
				{
					// The hyphen at the start is the only one - no latin chars.
					if (sPart[0] == '-' && strfind(sPart, !"-", false, 1) == -1) format(sEncoded, sizeof (sEncoded), "%sxn-%s%c", sEncoded, sPart, ch);
					else format(sEncoded, sizeof (sEncoded), "%sxn--%s%c", sEncoded, sPart, ch);
					#if defined _DEBUG
						#if _DEBUG >= 1
							static
								sDecoded[64];
							Puny_Decode(sDecoded, sPart);
							P:5("Puny_HTTP Original: \"%s\", Encoded: \"%s\", Decoded: \"%s\"", url[prev], sPart, sDecoded);
							if (strcmp(url[prev], sDecoded)) P:E("Puny_Decode did not match Puny_Encode");
						#endif
					#endif
				}
				// No special characters.
				case -1: format(sEncoded, sizeof (sEncoded), "%s%s%c", sEncoded, sPart, ch);
			}
			// Restore the data.
			_YSI_ConstMod(url[idx], ch),
			prev = idx + 1;
		}
		while (idx < end);
		// Add the remainder of the domain.
		if (url[end]) strcat(sEncoded, url[end + 1]);
		#if defined _DEBUG
			P:2("Puny_HTTP Domain: \"%s\" -> \"%s\"", url, sEncoded);
		#endif
		// Call the original "HTTP".
		return HTTP(index, type, sEncoded, data, callback);
	}
	
	#if defined _ALS_HTTP
		#undef HTTP
	#else
		
		native BAD_HTTP(index, type, url[], data[], callback[]) = HTTP;
		
		#define _ALS_HTTP
	#endif
	#define HTTP Puny_HTTP
#endif

#undef _Puny_Basic
#undef PUNY_BASE
#undef PUNY_CHAR

#if defined YSI_TESTS
	#include "y_punycode_tests"
#endif

