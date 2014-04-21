// We have reduced the renderer to just 2 phases: specifiers and visuals, where
// the second phase does both colours and new lines in parallel.  As a result,
// the positions update code is vastly simplified because we only need to track
// one phase not more - there is no need to update the first phase while it is
// running.

#if !defined Y_TEXT_MAX_COLOUR_EMBEDS
	#if defined Y_TEXT_MAX_COLOR_EMBEDS
		#define Y_TEXT_MAX_COLOUR_EMBEDS (Y_TEXT_MAX_COLOR_EMBEDS)
	#else
		#define Y_TEXT_MAX_COLOUR_EMBEDS (128)
	#endif
#endif

enum e_TEXT_RENDER_COLOUR
{
	e_TEXT_RENDER_COLOUR_END  = 0x01000000, // {/}
	e_TEXT_RENDER_COLOUR_FADE = 0x00010000, // {>XXXXXX}
	e_TEXT_RENDER_COLOUR_STAR = 0x00000100, // {*}
	e_TEXT_RENDER_COLOUR_LINE = 0x00000001, // \n, \r, \r\n
	e_TEXT_RENDER_COLOUR_MASK = 0xFEFEFEFE,
	e_TEXT_RENDER_COLOUR_FLAG = 0x01010101
}

// This function takes a list of positions in a string, and the length and
// position of a new string inserted in to the original string, and returns a
// list of positions adjusted for after that insertion.  The input is actually a
// list of relative jumps, and the output is a progressively updated list of
// absolute locations.  The input and output also includes additional data, but
// this data is not in a 2D array but all concatenated.
Y_TEXT_STATIC stock TextR_UpdateRelToAbs(rel[], abs[], &idx, addition, insertPos)
{
	// rel = 5  5  7  8  0
	// old = 0  5 10 17 25
	
	// idx = 0
	// add = 11
	// isp = 7
	
	// idx = 2
	// add = 3
	// isp = 30
	
	// idx = 4
	// add = 3
	// isp = 32
	
	// abs = 0  5 21 28 42
	new
		pos = abs[idx];
	while (pos <= insertPos)
	{
		if (!rel[idx]) return;
		pos += rel[idx++],
		abs[idx] = rel[idx], // First slot is data.
		abs[++idx] = pos;    // Second slot is insertion point.
	}
	abs[idx] += addition;
}

Y_TEXT_STATIC stock TextR_CompleteRelToAbs(rel[], abs[], &idx)
{
	// Afterwards (to complete any stragglers).  The function above only updates
	// the list and converts relative jumps to absolute ones as long as there is
	// processing left to do on specifiers.  If we run out of specifiers before
	// the relative jumps have been converted, then we need to finish them off
	// explicitly.
	new
		pos = abs[idx];
	while (rel[idx])
	{
		pos += rel[idx++],
		abs[idx] = rel[idx],
		abs[++idx] = pos;
	}
	abs[0] = idx; // Save the length just in case.
}


Y_TEXT_STATIC stock TextR_Render(string:str[], colourList[])
{
	static
		colourLocations[Y_TEXT_MAX_COLOUR_EMBEDS];
	new
		colourIdx;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	////                                                                    ////
	////                        PHASE 1 - SPECIFIERS                        ////
	////                                                                    ////
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	// There is an embedded linked list of locations of specifiers.
	for (new off = str[0], pos, ins; off; )
	{
		// Jump to the next location.
		pos = pos + off + ins;
		
		// Get the next specifier relative offset.
		off = str[pos];
		
		// Do this specifier.  Returns number of bytes the string GREW by, that
		// may not be the number of characters written, nor may it be positive.
		ins = TextR_DoSpecifier(str[pos]);
		
		// Update the other linked lists to account for this new data.
		TextR_UpdateRelToAbs(colourList, colourLocations, colourIdx, ins, pos);
	}
	
	// Copy the remaining relative locations over.
	TextR_CompleteRelToAbs(colourList, colourLocations, colourIdx);
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	////                                                                    ////
	////                          PHASE 2 - COLORS                          ////
	////                                                                    ////
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	// Note that "colours" is spelt "colors" above PURELY for symmetry.
	
	new
		offset = 0;
	// Loop over the linked list of absolute colour locations.
	for (new i = 1; i < colourIdx; i += 2)
	{
		// Get the colour to be displayed, and where it is to be displayed.
		// new
			// col = colourLocations[i++],
			// pos = colourLocations[i++] + offset;
		
		// As we loop through the string, our offsets get bigger and bigger
		offset += TextR_DoColour(str, offset, colourLocations, i, colourIdx);
	}
}

/**
	Get all information about the extent of this fade.
**/
Y_TEXT_STATIC stock TextR_GetFadeData(colourLocations[], start, &endColour, &endPos, &newLines)
{
	newLines = 0;
	for ( ; ; )
	{
		// These lines are not mutually exclusive.
		if (colourLocations[start - 1] &  _:e_TEXT_RENDER_COLOUR_LINE) ++newLines;
		// Don't check for an end condition, just don't fail!
		start += 2;
		// New lines at the END of a fade don't count as being IN the fade, so
		// we can do the increment in the middle of the loop.  
		if (colourLocations[start - 1] & ~_:e_TEXT_RENDER_COLOUR_LINE)
		{
			endColour = colourLocations[start - 1],
			endPos = colourLocations[start];
			return;
		}
	}
}

Y_TEXT_STATIC stock TextR_DoSpecifier(string:str[])
{
	// Resolve what the specifier is, including all its parameters (which may be
	// very complex, indeed, variable length).
	new
		len = 0,
		headerLen = 2,
		header = str[1];
	// Look at the header and get more information...
	
	// Return the number of characters inserted, minus the length of the header.
	return len - headerLen;
}

// Relatives.

// Colours are stored in a very unique manner (at least I've never seen it
// before).  Most people can't tell the difference visually between, say,
// 0x286A44FF and 0x286A45FF (it's hard enough to read the difference).  There
// is just one bit different, and that is the LSB of the Blue component, meaning
// that it makes a trivial contribution to the colour displayed.  If we use
// these LSBs for something else, then it doesn't matter if they are set or not
// for the display of the colour, and we can instead get 4 bit flags embedded
// within the colour.

Y_TEXT_STATIC stock TextR_InsertColour(str[], len, pos, &oldColour, newColour, &bool:pending) <y_text_colour : y_text_colour_gt>
{
	new
		oldType = oldColour & 0xFF,
		oldLite = oldColour >>> 8,
		nc = Colours_SAMPToGT(newColour >>> 8, (oldType == 0 || oldType == 'x') ? (oldLite) : (3)),
		newType = nc & 0xFF,
		newLite = nc >>> 8;
	static const
		cs_hTags[] = "~x~~h~~h~~h~~h~~h~%s";
	if (newType == oldType || newType == 'x')
	{
		// We don't need to output the type when the colour is 'x'.
		oldLite = (newLite - oldLite) * 3;
		if (oldLite == 0) return 0; // The two are identical.
		else if (oldLite > 0)
		{
			// Only need add some more "~h~"s.
			return
				format(str[pos], len - pos, cs_hTags[sizeof (cs_hTags) - 3 - oldLite], str[pos]),
				oldColour = nc,
				oldLite;
		}
	}
	// Need a whole new colour outputting.
	return
		newLite *= 3,
		format(str[pos], len - pos, cs_hTags[sizeof (cs_hTags) - 6 - newLite], str[pos]),
		str[pos + 1] = newType,
		oldColour = nc,
		3 + newLite;
}

/**
<summary>TextR_InsertColour</summary>
<param name="str">The string we are inserting a colour in to.</param>
<param name="len">The total length of this string.</param>
<param name="pos">The position in the string we want to insert at.</param>
<param name="oldColour">The previous colour for comparison.</param>
<param name="newColour">The new colour to insert.</param>
<param name="pending">Don't write if this colour is followed by a space.</param>
<remarks>
	The format "oldColour" is not constant between different state versions
	of this function, it is determined purely by what display mode is in use.
	On the other hand, "newColour" is always "RRGGBBAA" with component LSBs used
	for formatting flags.
</remarks>
**/

Y_TEXT_STATIC stock TextR_InsertColour(str[], len, pos, &oldColour, newColour, &bool:pending) <y_text_colour : y_text_colour_scm>
{
	// Insert a colour of the form "{RRGGBB}".
	newColour &= (_:e_TEXT_RENDER_COLOUR_MASK & 0xFFFFFF00); // SCM ignores alpha.
	P:4("TextR_InsertColour: \"%s\", %i, %i, %04x%04x, %04x%04x, %d", str, len, pos, oldColour >>> 16, oldColour & 0xFFFF, newColour >> 16, newColour & 0xFFFF, pending);
	if (oldColour != newColour) // Don't insert at the end.
	{
		P:7("TextR_InsertColour: STATE 1");
		// Don't write any colour out if this colour is followed by a space,
		// instead just mark it as pending.
		if (str[pos] <= ' ')
		{
			P:7("TextR_InsertColour: STATE 2");
			return
				pending = true,
				0;
			// Don't set the new colour as the old colour here, to handle this:
			//  
			//  {FFAA00}Hi{556677} {FFAA00}There
			//  
			// Without saving the pending old colour, we will just output:
			//  
			//  {FFAA00}Hi There
			//  
			// Even less if this is the start of the output; instead we will
			// just use the colour in SendClientMessage:
			//  
			//  Hi There
			//  
		}
		P:7("TextR_InsertColour: STATE 3");
		// The colour has changed, we may be able to do this to a greater degree
		// by relaxing the conditions on when the two colours are considered the
		// same, i.e. when they are within a certain range of each other.  I
		// might make that determined by the 2 LSBs.
		return
			pending = false,
			format(str[pos], len - pos, "{%06x}%s", newColour >>> 8, str[pos]),
			oldColour = newColour,
			// Return the inserted length.
			8;
	}
	P:7("TextR_InsertColour: STATE 4");
	return
		pending = false,
		0;
}

Y_TEXT_STATIC stock TextR_DoStraightFade(str[], len, &oldColour, startPos, startColour, fadeLen, endColour, &bool:pending)
{
	// This function does fades between two points when there are no newlines
	// between the fade points.
	new
		// The individual components of the start colour.
		sr =  startColour >>> 24,
		sg = (startColour >>> 16) & 0xFF,
		sb = (startColour >>>  8) & 0xFF,
		// The differences between the individual components.
		dr = ( endColour >>> 24)         - sr,
		dg = ((endColour >>> 16) & 0xFF) - sg,
		db = ((endColour >>>  8) & 0xFF) - sb;
	// Fake variables to save memory, while keeping names.
	#define inserted endColour
	#define taglen startColour
	inserted = 0; // Now amount of data inserted.
	// Loop over all the points between the ends.
	for (new step = 0; step != fadeLen; ++step)
	{
		// Don't colour spaces, there is exactly zero point!  In this case we
		// DON'T copy over the new colour as the existing colour.  We also know
		// that the very next character will also be coloured, so we don't need
		// to worry about the wrong colour being used in the future.
		// Use the existing insertion function to do the hard work.
		taglen = TextR_InsertColour(str, len, startPos, oldColour,
			// These components look like they should be optimisable, but they
			// aren't, because we are doing integer divisions so "a * b / c" is
			// slightly different to "a * (b / c)", ergo we can't precompute
			// parts like "dr / fadeLen".
			(((dr * step / fadeLen + sr) & 0xFF) << 24) |
			(((dg * step / fadeLen + sg) & 0xFF) << 16) |
			(((db * step / fadeLen + sb) & 0xFF) << 8 ), pending),
		inserted += taglen,
		// Increment to the next insertion point.
		startPos += taglen + 1;
	}
	return inserted;
	#undef inserted
	#undef taglen
}

Y_TEXT_STATIC stock TextR_DoNLFade(str[], len, &oldColour, startPos, startColour, fadeLen, endColour, colourLocations[], &idx, &bool:pending, offset)
{
	// This function does fades between two points when there may be newlines
	// between the fade points.  First, see if the first item is ALSO a new
	// line.
	if (!(colourLocations[idx - 1] & _:e_TEXT_RENDER_COLOUR_LINE)) idx += 2;
	// Now do all the normal code.
	new
		// The individual components of the start colour.
		sr =  startColour >>> 24,
		sg = (startColour >>> 16) & 0xFF,
		sb = (startColour >>>  8) & 0xFF,
		// The differences between the start and end colour components.
		dr = ( endColour >>> 24)         - sr,
		dg = ((endColour >>> 16) & 0xFF) - sg,
		db = ((endColour >>>  8) & 0xFF) - sb;
	// Fake variables to save memory, while keeping names.
	#define inserted endColour
	#define taglen startColour
	inserted = offset;
	// Loop over all the points between the ends.
	for (new step = 0, colour; step != fadeLen; ++step)
	{
		// These components look like they should be optimisable, but they
		// aren't, because we are doing integer divisions so "a * b / c" is
		// slightly different to "a * (b / c)", ergo we can't pre-compute parts
		// like "dr / fadeLen".
		colour =
			(((dr * step / fadeLen + sr) & 0xFF) << 24) |
			(((dg * step / fadeLen + sg) & 0xFF) << 16) |
			(((db * step / fadeLen + sb) & 0xFF) << 8 ) ;
		P:7("TextR_DoNLFade: step %d = %06x", step, colour >>> 8);
		P:7("TextR_DoNLFade: insert %d, %d, %d", startPos, colourLocations[idx], inserted);
		// Check for new lines, and update their locations accordingly.
		if (startPos == colourLocations[idx] + inserted)
		{
			// We don't need to check for the end colour because we don't loop
			// that far.  This is only triggered by new lines.  Note that it
			// would be triggered by the start point as well, but we make
			// explicit checks for that before the loop because that is the only
			// one that needs the checks so we can save time there.
			colourLocations[idx] += inserted,
			oldColour = colour & (_:e_TEXT_RENDER_COLOUR_MASK & 0xFFFFFF00),
			// We have found a new line - save what colour should appear at this
			// point, but don't write it out to the string.
			colourLocations[idx - 1] = (colour & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_LINE,
			idx += 2,
			pending = false,
			++startPos;
		}
		else
		{
			// Use the existing insertion function to do the hard work.
			P:7("TextR_DoNLFade: %s %d %d %d %d %d", str, len, startPos, oldColour, colour, pending);
			taglen = TextR_InsertColour(str, len, startPos, oldColour, colour, pending);
			P:7("TextR_DoNLFade: done");
			inserted += taglen,
			// Increment to the next insertion point.
			startPos += taglen + 1;
		}
	}
	return
		idx -= 2,
		inserted - offset;
	#undef inserted
	#undef taglen
}

Y_TEXT_STATIC stock TextR_ResolvePending(str[], len, pos, colourLocations[], idx, colour, endPos, &curColour)
{
	endPos += colourLocations[idx];
	//printf("%d %d %c", pos, endPos, str[pos]);
	while (pos < endPos && str[pos])
	{
		//printf("%d %d %c", pos, endPos, str[pos]);
		if (str[pos] <= ' ') ++pos;
		else
		{
			return
				// If we have a "pending" colour, then we know that it is
				// different to the last colour, because that is how pendings
				// are triggered.
				TextR_InsertColour(str, len, pos, curColour, colour, bool:idx);
				// We know the colour is different, and we know we aren't
				// somewhere that will trigger a pending hit, so there's no
				// point saving all that data anywhere but here.  As a result,
				// we re-use "idx" and "endPos" because they aren't needed any
				// more.
		}
	}
	// Reached the next colour item - discard this current one.  We aren't in a
	// fade so any new lines already have a colour assigned.
	return 0;
}

Y_TEXT_STATIC stock TextR_GetSlotColour(slot, originalColour, currentColour)
{
	if (slot & _:e_TEXT_RENDER_COLOUR_END) return originalColour;
	else if (slot & _:e_TEXT_RENDER_COLOUR_STAR) return 0xFEFEFE00; // TODO:.
	// "&=", not "&" - not a typo!
	else if ((slot &= _:e_TEXT_RENDER_COLOUR_MASK)) return slot;
	return currentColour;
}

Y_TEXT_STATIC stock TextR_DoOneColour(str[], len, offset, colourLocations[], &idx, &curColour, initialColour)
{
	new
		pos = offset + colourLocations[idx],
		flags = colourLocations[idx - 1],
		colour = TextR_GetSlotColour(flags, initialColour, curColour);
	//printf("pos: %d = %d", colourLocations[idx], pos);
	//printf("colour: %04x%04x", colour >>> 16, colour & 0xFFFF);
	if (flags & _:e_TEXT_RENDER_COLOUR_FADE)
	{
		new
			endColour,
			fadeLen,
			newLines;
		TextR_GetFadeData(colourLocations, idx, endColour, fadeLen, newLines),
		fadeLen -= pos;
		// Don't need to check and return "pending" statuses here.  The next
		// character will be another colour always (the fade end).
		if (newLines)
		{
			return TextR_DoNLFade(str, len, curColour, pos, colour, fadeLen,
				TextR_GetSlotColour(endColour, initialColour, curColour),
				colourLocations, idx, bool:newLines /* discardedPending */, offset);
		}
		else
			return TextR_DoStraightFade(str, len, curColour, pos, colour, fadeLen,
				TextR_GetSlotColour(endColour, initialColour, curColour),
				bool:newLines /* discardedPending */);
	}
	else if (flags & _:e_TEXT_RENDER_COLOUR_LINE)
	{
		// Don't do any output here.
		return
			curColour = colour, // TODO: Better Game Text aware copying.
			colourLocations[idx] = pos, // Save the final location.
			colourLocations[idx - 1] = colour | _:e_TEXT_RENDER_COLOUR_LINE,
			0;
	}
	else
	{
		return
			initialColour = TextR_InsertColour(str, len, pos, curColour, colour, bool:flags /* pending */),
			flags ?
				TextR_ResolvePending(str, len, pos + 1, colourLocations, idx + 2, colour, offset, curColour) :
				initialColour;
	}
}

TextR_NLBacktrack(&lineEnd, &lineStart, lineColour&)
{
	// There are 2 stages to this:  1) If we are in a colour, extract it and
	// keep going backwards.  2) Skip whitespaces.
	new
		colourPos,
		colourValue;
	for (new i = 0; i != 9; ++i)
	{
		if (TextR_IsColour(str[pos - i]))
		{
			// This records no alpha, which is determined by the "Text_Send"
			// line or somewhere else similar.
			colourPos = pos - i,
			colourValue = hexstr(str[pos - i + 1]) << 8,
			memset(str[pos
			break;
		}
	}
}

Y_TEXT_STATIC stock TextR_FindEnd(str[], lastNL, nextNL, nlColour, &nextColour)
{
	// All fits in fine, not a problem!
	if (nextNL - lastNL <= 144) return nextColour = nlColour, nextNL;
	// Too much between the "\n" characters.
	new
		maybe = TextR_NLBacktrack(str, nextNL, nextColour);
}




Y_TEXT_STATIC stock TextR_RunPhase2(str[], len, colourLocations[], intialColour)
{
	// Loop over all the stored colours and add them in to the string.
	new
		offset = 0,
		idx = 2,
		curColour = initialColour;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour),
		idx += 2;
	}
}

Y_TEXT_STATIC stock TextR_RunPhase3(str[], len, colourLocations[], initialColour)
{
	new
		offset = 0,
		lastNL = 0,
		idx = 2,
		curColour = initialColour;
	while (colourLocations[idx] != 65536)
	{
		if (colourLocations[idx - 1] & _:e_TEXT_RENDER_COLOUR_LINE)
		{
			offset += TextR_DoOneNL(str, len, lastNL, colourLocations, idx, curColour, offset);
		}
		idx += 2;
	}
	//TextR_DoLastNL(str, len, lastNL, curColour, initialColour);
}

Y_TEXT_STATIC stock TextR_DoOneNL(str, len, &lastNL, colourLocations, idx, &curColour, offset) <y_text_display : y_text_display_print>
{
	new
		pos = colourLocations[idx] + offset,
		ch = str[pos];
	return
		str[pos] = '\0',
		printf("TEXT:\n\tpos = %d\n\tcol = 0x%04x%04x\n\tstr = \"%s\"", lastNL, curColour >>> 16, curColour & 0xFFFF, str[lastNL]),
		str[pos] = ch,
		curColour = colourLocations[idx - 1],
		lastNL = pos,
		0;
}

Y_TEXT_STATIC stock TextR_RTrim(str[], start, end)
{
	while (--end >= start && str[end] <= ' ') {}
	return end + 1;
}

Y_TEXT_STATIC stock TextR_FindLast(str[], end, ch[])
{
	new
		last = -1,
		pos = -1;
	while (-1 < (pos = strfind(str, ch, false, pos + 1)) < end)
	{
		last = pos;
	}
	return last;
}

Y_TEXT_STATIC stock TextR_GetSplitPoint(str[], start, end, &colour)
{
	// Find a good place to split the string at between "start" and "end", then
	// figure out what colour the string is at that point.
}



Y_TEXT_STATIC stock TextR_DoOneNL(str, len, &lastNL, colourLocations, idx, &curColour, offset) <y_text_display : y_text_display_scm>
{
	new
		pos = colourLocations[idx] + offset;
	for ( ; ; )
	{
		//TextR_RTrim(str, lastNL, pos);
		if (pos - lastNL > 144) // Can only show 144 characters in one SCM line.
		{
			// TODO: More complex state!  Need to add in new lines at other
			// points.  This might not be easy to do, especially if we are in a
			// fade.
		}
		else
		{
			new
				ch = str[pos];
			str[pos] = '\0',
			SendClientMessageToAll(curColour, str[lastNL]),
			str[pos] = ch,
			curColour = colourLocations[idx - 1],
			lastNL = pos;
			break;
		}
	}
	return 0;
}

#endinput

// Basic printing, less than "n" characters between two new lines, meaning no
// complex location searching.

Y_TEXT_STATIC stock TextR_AddNewLines()
{
	
}









#endinput

Y_TEXT_STATIC stock TextR_WillOverflow(str[], pos, colourLocations[], idx) <y_text_display : y_text_display_print>
{
	return cellmin;
}

/**

<returns>
	The position at which to insert an additional new line.  
</returns>
<remarks>
	This function determines if there will be a line overflow within the next
	few colours.
	
	May not be 100% accurate in some cases, it over-estimates slightly when it
	thinks there should be colours inserted at a point, but those colours are
	elided by the fact that they are too similar to the previous colour.  This
	function will operate assuming that they exist, and so add new lines earlier
	than they need to be.
	
	This function also aims for line lengths of 128 visible characters, with the
	additional 16 characters used purely for colours.
</remarks>
**/

// // Find the next new line.
// #define TextR_GetNextNL(%0,%1,%3%2)                              \
	// while (((%2) = (%0)[(%1)]) != 65536)                         \
	// {                                                            \
		// if ((%0)[(%1) - 1] & _:e_TEXT_RENDER_COLOUR_LINE) break; \
		// (%1) += 2;                                               \
	// }                                                            \
	// if ((%2) == 65536) (%2) = (%3)

Y_TEXT_STATIC stock TextR_AdditionalNewLines(str[], colourLocations[]) <y_text_display : y_text_display_scm>
{
	new
		prevNL = 0,
		nextNL = -1,
		idx = 2,
		bool:fade, // Tracks colour fades over new lines.
		len = TextR_RTrim(str, 0, strlen(str));
	do
	{
		new
			inserts;
		TextR_GetSCMLineData(str, prevNL, len, colourLocations, idx, inserts, nextNL, fade);
		new
			diff = nextNL - prevNL;
		while (diff > 128 || diff + inserts > 144)
		{
			// We need to insert an extra new line somewhere.
		}
	}
	while ((prevNL = nextNL) != len);
}

// TODO: Make this smarter - account for spaces and equal colours.
#define TextR_GetSCMFadeInserts(%0,%1,%2) (((%2) - (%1)) * 8)

TextR_SkipMultiLine(nextNL, colourLocations, &idx, &fade)
{
	// Multiple colour entries may be at the same location, just skip them all
	// as quite pointless for these purposes.
	new
		e_TEXT_RENDER_COLOUR:col;
	// Always run at least once on the found new line.
	while (colourLocations[idx] == nextNL)
	{
		col = e_TEXT_RENDER_COLOUR:colorLocations[idx - 1];
		if (col & e_TEXT_RENDER_COLOUR_FADE) fade = true;
		else if (col & ~e_TEXT_RENDER_COLOUR_LINE) fade = false;
		idx += 2;
	}
}

Y_TEXT_STATIC stock TextR_GetSCMLineData(str[], pos, len, colourLocations[], &idx, &inserts, &nextNL, &bool:fade)
{
	new
		cp,
		e_TEXT_RENDER_COLOUR:col;
	while ((cp = colorLocations[idx]) != 65536)
	{
		col = e_TEXT_RENDER_COLOUR:colorLocations[idx - 1];
		if (col & e_TEXT_RENDER_COLOUR_LINE)
		{
			if (fade) inserts += TextR_GetSCMFadeInserts(str, pos, cp);
			// Another new line may start a fade.
			TextR_SkipMultiLine(cp, colourLocations, idx, fade),
			nextNL = cp;
			return;
		}
		else
		{
			// This is not a new line so it MUST be a colour.
			if (fade) inserts += TextR_GetSCMFadeInserts(str, pos, cp);
			if (col & e_TEXT_RENDER_COLOUR_FADE) fade = true;
			else
			{
				inserts += 8, // Add the characters to show this colour.
				fade = false;
				// TODO: Using this code, we must ensure that "pending" colours,
				// if required, are put where they were first specified, and NOT
				// where they are first used.
				// EDIT: Actually, that is NOT the case!  The colours can move
				// about no problem while they are on the same line, and if they
				// drop to the next line then the SCM call will deal with the
				// excess characters anyway.  Thus, the "inserts" value is an
				// UPPER bound on the number of characters on a line.
			}
		}
		idx += 2;
	}
	nextNL = len;
}

Y_TEXT_STATIC stock bool:TextR_IsColour(const str[])
{
	static const
		scIsHex['F' + 1] = 
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 1, 1, 1
		};
	new
		ch;
	return
		(str[0] == '{') &&
		IS_IN_RANGE((ch = str[1]), '0', 'F' + 1) && (scIsHex[ch]) &&
		IS_IN_RANGE((ch = str[2]), '0', 'F' + 1) && (scIsHex[ch]) &&
		IS_IN_RANGE((ch = str[3]), '0', 'F' + 1) && (scIsHex[ch]) &&
		IS_IN_RANGE((ch = str[4]), '0', 'F' + 1) && (scIsHex[ch]) &&
		IS_IN_RANGE((ch = str[5]), '0', 'F' + 1) && (scIsHex[ch]) &&
		IS_IN_RANGE((ch = str[6]), '0', 'F' + 1) && (scIsHex[ch]) &&
		(str[7] == '}');
}

// Y_TEXT_STATIC stock bool:TextR_IsColour(str[])
// {
	// new
		// ch;
	// return
		// (str[0] == '{') && (str[7] == '}') &&
		// (('0' <= (ch = str[1]) <= '9') || ('A' <= ch <= 'F')) &&
		// (('0' <= (ch = str[2]) <= '9') || ('A' <= ch <= 'F')) &&
		// (('0' <= (ch = str[3]) <= '9') || ('A' <= ch <= 'F')) &&
		// (('0' <= (ch = str[4]) <= '9') || ('A' <= ch <= 'F')) &&
		// (('0' <= (ch = str[5]) <= '9') || ('A' <= ch <= 'F')) &&
		// (('0' <= (ch = str[6]) <= '9') || ('A' <= ch <= 'F'));
// }

// Y_TEXT_STATIC stock bool:TextR_IsColour2(str[])
// {
	// static const
		// scIsHex['F' + 1] = 
		// {
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
			// 0, 1, 1, 1, 1, 1, 1
		// };
	// new
		// ch;
	// return
		// (str[0] == '{') && (str[7] == '}') &&
		// ('0' <= (ch = str[1]) <= 'F') && (scIsHex[ch]) &&
		// ('0' <= (ch = str[2]) <= 'F') && (scIsHex[ch]) &&
		// ('0' <= (ch = str[3]) <= 'F') && (scIsHex[ch]) &&
		// ('0' <= (ch = str[4]) <= 'F') && (scIsHex[ch]) &&
		// ('0' <= (ch = str[5]) <= 'F') && (scIsHex[ch]) &&
		// ('0' <= (ch = str[6]) <= 'F') && (scIsHex[ch]);
// }

// Y_TEXT_STATIC stock bool:TextR_IsColour3(str[])
// {
	// static const
		// scIsHex['F' + 1] = 
		// {
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
			// 0, 1, 1, 1, 1, 1, 1
		// };
	// new
		// ch;
	// return
		// (str[0] == '{') &&
		// IS_IN_RANGE((ch = str[1]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// IS_IN_RANGE((ch = str[2]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// IS_IN_RANGE((ch = str[3]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// IS_IN_RANGE((ch = str[4]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// IS_IN_RANGE((ch = str[5]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// IS_IN_RANGE((ch = str[6]), '0', 'F' + 1) && (scIsHex[ch]) &&
		// (str[7] == '}');
// }



