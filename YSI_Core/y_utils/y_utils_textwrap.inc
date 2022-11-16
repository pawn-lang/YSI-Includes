/**
 * <library
 *   name="y_utils - textwrap"
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
 * <library>y_utils - textwrap</library>
 * <remarks>
 *   Internal implementation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_CORE_STATIC stock IterativeColouredSkipSUnpacked(const string:text[], start, &colour)
{
	new
		ch = 0,
		i = 0,
		cc = 0;
	while ((ch = text[start]))
	{
		if (ch == '\r' || ch == '\n')
		{
			// Instantly end.  We don't skip this whitespace.
			return start;
		}
		else if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
		{
			// Interesting whitespace.  Will exclude `'\r'` and `'\n'` thanks to
			// the `else`.
			++start;
		}
		else if (ch == '{')
		{
			for (i = 1, cc = 0; i != 7; ++i)
			{
				ch = text[start + i];
				if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					return start;
				}
			}
			if (text[start + 7] == '}')
			{
				colour = cc,
				start += 8;
			}
			else
			{
				// Not valid whitespace.
				return start;
			}
		}
		else
		{
			// Not valid whitespace.
			return start;
		}
	}
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - textwrap</library>
 * <remarks>
 *   Internal implementation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_CORE_STATIC stock IterativeColouredSkipWUnpacked(const string:text[], lastIndex, start, &bool:hyphen, &colour, bool:useHyphen = true)
{
	// Offset.
	new
		// How many real letters appear within the width.
		preLen = 0,
		// How many real letters appear in the whole word?
		truLen = 0,
		g1 = 0,
		g2 = 0,
		ch = 0,
		i = start,
		j = 0,
		cc = 0;
	while ((ch = text[i]) > ' ')
	{
		if (IS_IN_RANGE(ch, 'a', 'z' + 1) || IS_IN_RANGE(ch, 'A', 'Z' + 1))
		{
			// Real letter.
			if (i < lastIndex)
			{
				g1 = g2,
				g2 = i,
				++preLen;
			}
			++truLen;
		}
		else switch (ch)
		{
		case '{':
		{
			for (j = 1, cc = 0; ; ++j)
			{
				ch = text[i + j];
				if (ch <= ' ')
				{
					useHyphen = false,
					i += j;
					break;
				}
				else if (j == 7)
				{
					i += 8;
					if (ch != '}')
					{
						useHyphen = false;
					}
					else if (i <= lastIndex)
					{
						// Only propagate the colour if it is complete in the line.
						colour = cc;
					}
					break;
				}
				else if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					useHyphen = false,
					// NOT an OBOE, rechecks one character.
					i += j;
					break;
				}
			}
			// Don't re-increment.
			continue;
		}
		case '.', ',', '?', '!', '\'':
		{
			// Allow these in normal text.  Thus do nothing.
		}
		default:
		{
			// Not a real word.  Can't be hyphenated.
			useHyphen = false;
		}
		}
		++i;
	}
	// End of the word.
	if (i <= lastIndex)
	{
		// Enough space.
		return
			hyphen = false,
			i;
	}
	else if (useHyphen && truLen > 6 && preLen > 3)
	{
		// Can and should be hyphenated.
		switch (truLen - preLen)
		{
		case 1:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g1;
		}
		case 2:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g2;
		}
		default:
		{
			return
				hyphen = true,
				g2 + 1 == lastIndex ? g2 : g2 + 1;
		}
		}
	}
	// Move the whole thing to the next line.
	return
		hyphen = false,
		start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - textwrap</library>
 * <remarks>
 *   Internal implementation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_CORE_STATIC stock IterativeColouredSkipSPacked(const string:text[], start, &colour)
{
	new
		ch = 0,
		i = 0,
		cc = 0;
	while ((ch = text{start}))
	{
		if (ch == '\r' || ch == '\n')
		{
			// Instantly end.  We don't skip this whitespace.
			return start;
		}
		else if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
		{
			// Interesting whitespace.  Will exclude `'\r'` and `'\n'` thanks to
			// the `else`.
			++start;
		}
		else if (ch == '{')
		{
			for (i = 1, cc = 0; i != 7; ++i)
			{
				ch = text{start + i};
				if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					return start;
				}
			}
			if (text{start + 7} == '}')
			{
				colour = cc,
				start += 8;
			}
			else
			{
				// Not valid whitespace.
				return start;
			}
		}
		else
		{
			// Not valid whitespace.
			return start;
		}
	}
	return start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - textwrap</library>
 * <remarks>
 *   Internal implementation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_CORE_STATIC stock IterativeColouredSkipWPacked(const string:text[], lastIndex, start, &bool:hyphen, &colour, bool:useHyphen = true)
{
	// Offset.
	new
		// How many real letters appear within the width.
		preLen = 0,
		// How many real letters appear in the whole word?
		truLen = 0,
		g1 = 0,
		g2 = 0,
		ch = 0,
		i = start,
		j = 0,
		cc = 0;
	while ((ch = text{i}) > ' ')
	{
		if (IS_IN_RANGE(ch, 'a', 'z' + 1) || IS_IN_RANGE(ch, 'A', 'Z' + 1))
		{
			// Real letter.
			if (i < lastIndex)
			{
				g1 = g2,
				g2 = i,
				++preLen;
			}
			++truLen;
		}
		else switch (ch)
		{
		case '{':
		{
			for (j = 1, cc = 0; ; ++j)
			{
				ch = text{i + j};
				if (ch <= ' ')
				{
					useHyphen = false,
					i += j;
					break;
				}
				else if (j == 7)
				{
					i += 8;
					if (ch != '}')
					{
						useHyphen = false;
					}
					else if (i <= lastIndex)
					{
						// Only propagate the colour if it is complete in the line.
						colour = cc;
					}
					break;
				}
				else if (IS_IN_RANGE(ch, '0', '9' + 1))
				{
					cc = (cc << 4) | (ch - '0');
				}
				else if (IS_IN_RANGE(ch, 'a', 'f' + 1))
				{
					cc = (cc << 4) | (ch - ('a' - 10));
				}
				else if (IS_IN_RANGE(ch, 'A', 'F' + 1))
				{
					cc = (cc << 4) | (ch - ('A' - 10));
				}
				else
				{
					// Bad HEX.
					useHyphen = false,
					// NOT an OBOE, rechecks one character.
					i += j;
					break;
				}
			}
			// Don't re-increment.
			continue;
		}
		case '.', ',', '?', '!', '\'':
		{
			// Allow these in normal text.  Thus do nothing.
		}
		default:
		{
			// Not a real word.  Can't be hyphenated.
			useHyphen = false;
		}
		}
		++i;
	}
	// End of the word.
	if (i <= lastIndex)
	{
		// Enough space.
		return
			hyphen = false,
			i;
	}
	else if (useHyphen && truLen > 6 && preLen > 3)
	{
		// Can and should be hyphenated.
		switch (truLen - preLen)
		{
		case 1:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g1;
		}
		case 2:
		{
			// Only 1 character after the split.
			return
				hyphen = true,
				g2;
		}
		default:
		{
			return
				hyphen = true,
				g2 + 1 == lastIndex ? g2 : g2 + 1;
		}
		}
	}
	// Move the whole thing to the next line.
	return
		hyphen = false,
		start;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - textwrap</library>
 * <summary>
 *   bool:IterativeTextSplitter(const text[], width, start, &amp;end, &amp;next, &amp;bool:hyphen)
 * </summary>
 * <param name="text">The input string to split up.</param>
 * <param name="start">Where in the string to start the next line.</param>
 * <param name="width">The maximum size of the output (including hyphen).</param>
 * <param name="end">The index to end the current line at (excluding hyphen).</param>
 * <param name="next">The index to start the next line from (skips trailing spaces).</param>
 * <param name="hyphen">Should a hyphen be inserted in to the output?</param>
 * <param name="useHyphen">May a hyphen be included?</param>
 * <returns>
 *   Does the function need to be called again to show another line?
 * </returns>
 * <remarks>
 *   Split some text in to multiple lines.  With sensible breaks at spaces or
 *   mid-word if they're long enough.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IterativeTextSplitter(const text[], width, start, &end, &next, &bool:hyphen, bool:useHyphen = true)
{
	if (YSI_IsLocalVarPackedString__(text))
	{
		// Returns `true` if there is more text to come.
		new
			lastSpace = start,
			wordLen = 0,
			i = start,
			ch;
		for (new j = 0; j != width; ++i, ++j)
		{
			switch ((ch = text{i}))
			{
			case '\0':
			{
				// End of the string.  Quite easy.
				return
					end = wordLen ? i : lastSpace,
					// Just initialise this, the value shouldn't be used.
					next = i,
					// No hyphen, obviously.
					hyphen = false,
					// No more calls after this.
					false;
			}
			case '\r':
			{
				// New line.  Quite easy.
				return
					end = wordLen ? i : lastSpace,
					next = text{i + 1} == '\n' ? i + 2 : i + 1,
					hyphen = false,
					true;
			}
			case '\n':
			{
				// New line.  Very easy.
				return
					end = wordLen ? i : lastSpace,
					next = i + 1,
					hyphen = false,
					true;
			}
			case 1 .. 9, 11 .. 12, 14 .. 32:
			{
				// Spacing.
				if (wordLen)
				{
					// Was in a word, now aren't.
					lastSpace = i,
					wordLen = 0;
				}
				// Else do nothing, we're just skipping an extended space.
			}
			default:
			{
				// Text.
				++wordLen;
			}
			}
		}
		// If we reach the end of the loop we've found the full width of text.
		if (wordLen == 0)
		{
			// In space.  Good.  Skip the rest of the space.
			end = lastSpace,
			hyphen = false;
			while ('\0' < (ch = text{i}) <= ' ')
			{
				if (ch == '\r')
				{
					return
						next = text{i + 1} == '\n' ? i + 2 : i + 1,
						true;
				}
				else if (ch == '\n')
				{
					return
						next = i + 1,
						true;
				}
				++i;
			}
			return
				next = i,
				ch != '\0';
		}
		// In the middle of a string.  Work out if we should split the text with a
		// hyphen or move it down to the next line.
		if (text{i} > ' ')
		{
			if (!useHyphen || wordLen < 4)
			{
				// Not enough space for three characters plus a hyphen on the
				// current line.  Move it down to the next line.
				return
					end = lastSpace,
					next = i - wordLen,
					hyphen = false,
					true;
			}
			if (text{i + 1} > ' ')
			{
				// There will be at least three characters on the next line (the new
				// two plus the one replaced by the hyphen).
				return
					end = i - 1,
					next = i - 1,
					hyphen = true,
					true;
			}
			if (wordLen >= 6)
			{
				// There are at least six characters total.
				return
					end = i - 2,
					next = i - 2,
					hyphen = true,
					true;
			}
			// Five or six characters long.  Move to the next line.
			return
				end = lastSpace,
				next = i - wordLen,
				hyphen = false,
				true;
		}
		// The word fits precisely.
		end = i,
		hyphen = false;
		while ('\0' < (ch = text{i}) <= ' ')
		{
			if (ch == '\r')
			{
				return
					next = text{i + 1} == '\n' ? i + 2 : i + 1,
					true;
			}
			else if (ch == '\n')
			{
				return
					next = i + 1,
					true;
			}
			++i;
		}
		return
			next = i,
			ch != '\0';
	}
	else
	{
		// Returns `true` if there is more text to come.
		new
			lastSpace = start,
			wordLen = 0,
			i = start,
			ch;
		for (new j = 0; j != width; ++i, ++j)
		{
			switch ((ch = text[i]))
			{
			case '\0':
			{
				// End of the string.  Quite easy.
				return
					end = wordLen ? i : lastSpace,
					// Just initialise this, the value shouldn't be used.
					next = i,
					// No hyphen, obviously.
					hyphen = false,
					// No more calls after this.
					false;
			}
			case '\r':
			{
				// New line.  Quite easy.
				return
					end = wordLen ? i : lastSpace,
					next = text[i + 1] == '\n' ? i + 2 : i + 1,
					hyphen = false,
					true;
			}
			case '\n':
			{
				// New line.  Very easy.
				return
					end = wordLen ? i : lastSpace,
					next = i + 1,
					hyphen = false,
					true;
			}
			case 1 .. 9, 11 .. 12, 14 .. 32:
			{
				// Spacing.
				if (wordLen)
				{
					// Was in a word, now aren't.
					lastSpace = i,
					wordLen = 0;
				}
				// Else do nothing, we're just skipping an extended space.
			}
			default:
			{
				// Text.
				++wordLen;
			}
			}
		}
		// If we reach the end of the loop we've found the full width of text.
		if (wordLen == 0)
		{
			// In space.  Good.  Skip the rest of the space.
			end = lastSpace,
			hyphen = false;
			while ('\0' < (ch = text[i]) <= ' ')
			{
				if (ch == '\r')
				{
					return
						next = text[i + 1] == '\n' ? i + 2 : i + 1,
						true;
				}
				else if (ch == '\n')
				{
					return
						next = i + 1,
						true;
				}
				++i;
			}
			return
				next = i,
				ch != '\0';
		}
		// In the middle of a string.  Work out if we should split the text with a
		// hyphen or move it down to the next line.
		if (text[i] > ' ')
		{
			if (!useHyphen || wordLen < 4)
			{
				// Not enough space for three characters plus a hyphen on the
				// current line.  Move it down to the next line.
				return
					end = lastSpace,
					next = i - wordLen,
					hyphen = false,
					true;
			}
			if (text[i + 1] > ' ')
			{
				// There will be at least three characters on the next line (the new
				// two plus the one replaced by the hyphen).
				return
					end = i - 1,
					next = i - 1,
					hyphen = true,
					true;
			}
			if (wordLen >= 6)
			{
				// There are at least six characters total.
				return
					end = i - 2,
					next = i - 2,
					hyphen = true,
					true;
			}
			// Five or six characters long.  Move to the next line.
			return
				end = lastSpace,
				next = i - wordLen,
				hyphen = false,
				true;
		}
		// The word fits precisely.
		end = i,
		hyphen = false;
		while ('\0' < (ch = text[i]) <= ' ')
		{
			if (ch == '\r')
			{
				return
					next = text[i + 1] == '\n' ? i + 2 : i + 1,
					true;
			}
			else if (ch == '\n')
			{
				return
					next = i + 1,
					true;
			}
			++i;
		}
		return
			next = i,
			ch != '\0';
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - textwrap</library>
 * <summary>
 *   bool:IterativeColouredTextSplitter(const text[], width, start, &amp;end, &amp;next, &amp;bool:hyphen)
 * </summary>
 * <param name="text">The input string to split up.</param>
 * <param name="start">Where in the string to start the next line.</param>
 * <param name="width">The maximum size of the output (including hyphen).</param>
 * <param name="end">The index to end the current line at (excluding hyphen).</param>
 * <param name="next">The index to start the next line from (skips trailing spaces).</param>
 * <param name="hyphen">Should a hyphen be inserted in to the output?</param>
 * <param name="colour">The colour for the start of the next line.</param>
 * <param name="useHyphen">May a hyphen be included?</param>
 * <returns>
 *   Does the function need to be called again to show another line?
 * </returns>
 * <remarks>
 *   Split some text in to multiple lines.  With sensible breaks at spaces or
 *   mid-word if they're long enough.  Unlike <c>IterativeTextSplitter</c> it
 * will never split in the middle of <c>{RRGGBB}</c> colour sequences, and can
 * ignore them for many checks.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IterativeColouredTextSplitter(const text[], width, start, &end, &next, &bool:hyphen, &colour, bool:useHyphen = true)
{
	if (YSI_IsLocalVarPackedString__(text))
	{
		new
			ch;
		hyphen = false,
		width += start,
		end = start;
		while ((ch = text{start}))
		{
			if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
			{
				// Skip whitespace.
				start = IterativeColouredSkipSPacked(text, start, colour);
				switch (text{start})
				{
				case '\r':
				{
					return
						next = text{start + 1} == '\n' ? start + 2 : start + 1,
						true;
				}
				case '\n':
				{
					return
						next = start + 1,
						true;
				}
				case '\0':
				{
					return
						next = start,
						false;
				}
				}
				if (start > width)
				{
					return
						next = start,
						true;
				}
			}
			else
			{
				ch = IterativeColouredSkipWPacked(text, width, start, hyphen, colour, useHyphen);
				if (ch == start)
				{
					// Either showed nothing of this word, or parts.
					return
						next = ch,
						true;
				}
				else if (hyphen)
				{
					return
						next = end = ch,
						true;
				}
				start = end = ch;
			}
		}
		return
			next = start,
			false;
	}
	else
	{
		new
			ch;
		hyphen = false,
		width += start,
		end = start;
		while ((ch = text[start]))
		{
			if (IS_IN_RANGE(ch, '\0' + 1, ' ' + 1))
			{
				// Skip whitespace.
				start = IterativeColouredSkipSUnpacked(text, start, colour);
				switch (text[start])
				{
				case '\r':
				{
					return
						next = text[start + 1] == '\n' ? start + 2 : start + 1,
						true;
				}
				case '\n':
				{
					return
						next = start + 1,
						true;
				}
				case '\0':
				{
					return
						next = start,
						false;
				}
				}
				if (start > width)
				{
					return
						next = start,
						true;
				}
			}
			else
			{
				ch = IterativeColouredSkipWUnpacked(text, width, start, hyphen, colour, useHyphen);
				if (ch == start)
				{
					// Either showed nothing of this word, or parts.
					return
						next = ch,
						true;
				}
				else if (hyphen)
				{
					return
						next = end = ch,
						true;
				}
				start = end = ch;
			}
		}
		return
			next = start,
			false;
	}
}

