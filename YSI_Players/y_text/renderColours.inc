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

/*Y_TEXT_STATIC stock TextR_DoColour(string:str[], offset, colourLocations[], i, colourIdx)
{
	new
		c = colourLocations[i++],
		pos = colourLocations[i++];
	
}*/

/**
	Get the colour at the end of a fade area, ignoring any spaces.
**/
/*Y_TEXT_STATIC stock TextR_GetFadeEnd(colourLocations[], start)
{
	do
	{
		start += 2;
	}
	while (colourLocations[start] & 1);
	return colourLocations[start];
}

/ **
	Get the length of a fade, before any newlines are applied.
** /
Y_TEXT_STATIC stock TextR_GetFadeLen(colourLocations[], start)
{
	new
		len = colourLocations[start + 1];
	do
	{
		start += 2;
	}
	while (colourLocations[start] & 1);
	return colourLocations[start + 1] - len;
}

/ **
	Get the number of newlines within a fade.
** /
Y_TEXT_STATIC stock TextR_GetFadeNLs(colourLocations[], start)
{
	new
		nls = -1;
	do
	{
		start += 2,
		++nls;
	}
	while (colourLocations[start] & 1);
	return nls;
}*/

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

// Don't call this with an offset.
Y_TEXT_STATIC stock TextR_GetColourAtPoint(pos, colourLocations[])
{
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



/*


new
	nextUpdate = curUpdate + 1,
	nexPos = dst[nextUpdate] = src[curUpdate] + dst[curUpdate] + addition;


*/



// Colours are stored in a very unique manner (at least I've never seen it
// before).  Most people can't tell the difference visually between, say,
// 0x286A44FF and 0x286A45FF (it's hard enough to read the difference).  There
// is just one bit different, and that is the LSB of the Blue component, meaning
// that it makes a trivial contribution to the colour displayed.  If we use
// these LSBs for something else, then it doesn't matter if they are set or not
// for the display of the colour, and we can instead get 4 bit flags embedded
// within the colour.

/*

if (c == e_TEXT_RENDER_COLOUR_LINE)
{
	// New line.
}
else
{
	// Actually a colour.
	switch (c & e_TEXT_RENDER_COLOUR_FLAG)
	{
		case e_TEXT_RENDER_COLOUR_END:
			c = original;
		case e_TEXT_RENDER_COLOUR_FADE:
			fade = true;
		case e_TEXT_RENDER_COLOUR_STAR:
			c = GetNextParam();
		case e_TEXT_RENDER_COLOUR_FADE | e_TEXT_RENDER_COLOUR_END:
			c = original, fade = true;
		case e_TEXT_RENDER_COLOUR_FADE | e_TEXT_RENDER_COLOUR_STAR:
			c = GetNextParam(), fade = true;
		// No other combinations are valid.
	}
}

*/





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
//		if (str[startPos] <= ' ') { ++startPos; continue; }
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

Y_TEXT_STATIC stock TextR_DoNLFade(str[], len, &oldColour, startPos, startColour, fadeLen, endColour, colourLocations[], idx, &bool:pending)
{
	// This function does fades between two points when there ARE newlines
	// between the fade points.  First, see if the first item is ALSO a new
	// line.
	if (!(colourLocations[idx - 1] & _:e_TEXT_RENDER_COLOUR_LINE)) idx += 2;
	// Now do all the normal code.
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
	inserted = 0;
	// Loop over all the points between the ends.
	for (new step = 0, colour; step != fadeLen; ++step)
	{
		// These components look like they should be optimisable, but they
		// aren't, because we are doing integer divisions so "a * b / c" is
		// slightly different to "a * (b / c)", ergo we can't precompute parts
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
	return inserted;
	#undef inserted
	#undef taglen
}

// Originally called "TextR_3f9qzz11", because that was dictated to me by
// someone that can't code, on a plane.
// Y_TEXT_STATIC stock TextR_()
// {
	
// }


Y_TEXT_STATIC stock TextR_ResolvePending(str[], len, pos, colourLocations[], idx, colour)
{
	new
		endPos = colourLocations[idx];
	while (pos < endPos && str[pos])
	{
		if (str[pos] <= ' ') ++pos;
		else
		{
			return
				// Make it as different as possible quickly.
				endPos = ~colour,
				// If we have a "pending" colour, then we know that it is
				// different to the last colour, because that is how pendings
				//are triggered.
				TextR_InsertColour(str, len, pos, endPos, colour, bool:idx);
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


/*
Y_TEXT_STATIC stock TextR_Render(players, str[], start, end, colour) <y_text_display : y_text_display_scm>
{
	#pragma unused players, str, start, end, colour
	return 0;
}

Y_TEXT_STATIC stock TextR_Render(players, str[], start, end, colour) <y_text_display : y_text_display_print>
{
	#pragma unused players
	new
		ch = str[end];
	return
		str[end] = '\0',
		P:0("TextR_Render: 0x%04x%04x \"%s\"", colour >>> 16, colour & 0xFFFF, str[start]),
		str[end] = ch;
}
*/

Y_TEXT_STATIC stock TextR_DoOneColour(str[], len, offset, colourLocations[], &idx, &curColour, initialColour, &pending)
{
	new
		pos = colourLocations[idx],
		flags = colourLocations[idx - 1],
		col = TextR_GetSlotColour(flags, initialColour, curColour);
	idx += 2;
	if (flags & _:e_TEXT_RENDER_COLOUR_FADE)
	{
		new
			endColour,
			endPos,
			newLines,
		TextR_GetFadeData(colourLocations, idx, endColour, endPos, newLines);
		if (newLines)
			return TextR_DoNLFade(str, len, curColour, pos + offset, col, endPos - pos, TextR_GetSlotColour(endColour, initialColour, curColour), colourLocations, idx, pending);
		else
			return TextR_DoStraightFade(str, len, curColour, pos + offset, col, endPos - pos, TextR_GetSlotColour(endColour, initialColour, curColour), pending);
	}
	else if (flags & _:e_TEXT_RENDER_COLOUR_LINE)
	{
		// Don't do any output here.
		return
			colourLocations[idx - 3] = col | _:e_TEXT_RENDER_COLOUR_LINE,
			0;
	}
	return TextR_InsertColour(str, len, pos + offset, curColour, col, pending);
}

#endinput
Y_TEXT_STATIC stock TextR_DoColours(str[], len, colourLocations[], startColour)
{
	
	new
		curColour = startColour,
		idx = 2;
	while (colourLocations[idx])
	{
		new
			bool:pending = false,
			colour = colourLocations[idx - 1];
		// Is a colour.
		if (colour & _:e_TEXT_RENDER_COLOUR_FADE)
		{
			// Do the fading.
			new
				endColour
		}
		
		
		
		
		switch (e_TEXT_RENDER_COLOUR:colour & e_TEXT_RENDER_COLOUR_FLAG)
		{
			//case e_TEXT_RENDER_COLOUR_LINE:
			case e_TEXT_RENDER_COLOUR_END:
				curColour = startColour;
			case e_TEXT_RENDER_COLOUR_FADE:
				fade = true;
			case e_TEXT_RENDER_COLOUR_STAR:
				c = GetNextParam();
			case e_TEXT_RENDER_COLOUR_FADE | e_TEXT_RENDER_COLOUR_END:
				c = original, fade = true;
			case e_TEXT_RENDER_COLOUR_FADE | e_TEXT_RENDER_COLOUR_STAR:
				c = GetNextParam(), fade = true;
			// No other combinations are valid.
		}
		idx += 2;
	}
}












#endinput




	LOOP OVER ALL
		DO NEXT COLOUR
		if (pending) 
		{
			offset += TextR_ResolvePending(str, sizeof (str), pos, colourLocations, colourIdx, newColour);
		}

TextR_DoOneColour(str[], len, &pos, &curColour, colourLocations[], &idx, originalColour)
{
	new
		colour = colourLocations[idx - 1],
		rc; // The colour to output.
	if (colour & _:e_TEXT_RENDER_COLOUR_FADE)
	{
		// Start of a fade.
	}
	switch (e_TEXT_RENDER_COLOUR:colour & ~e_TEXT_RENDER_COLOUR_FADE)
	{
		// Ending a colour, get the original.
		case e_TEXT_RENDER_COLOUR_END: rc = originalColour;
		// Starting a new line with the original colour.  Exit.
		case e_TEXT_RENDER_COLOUR_END  | e_TEXT_RENDER_COLOUR_LINE:
		{
			return
				colourLocations[idx - 1] = originalColour | _:e_TEXT_RENDER_COLOUR_LINE,
				idx += 2,
				0;
		}
		// Getting a colour parameter.
		case e_TEXT_RENDER_COLOUR_STAR: rc = (0xFEFEFE00 & _:e_TEXT_RENDER_COLOUR_MASK); // TODO: Get the relevant parameter.
		// Starting a new line with a colour parameter.  Exit.
		case e_TEXT_RENDER_COLOUR_STAR | e_TEXT_RENDER_COLOUR_LINE:
		{
			return
				// TODO: Get the relevant parameter.
				// HOORAY!  Global state has snuck in!
				colourLocations[idx - 1] = (0xFEFEFE00 & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_LINE,
				idx += 2,
				0;
		}
		// Starting a new line with no other data.  Get current colour.  Exit.
		case e_TEXT_RENDER_COLOUR_LINE:
		{
			return
				colourLocations[idx - 1] = curColour | _:e_TEXT_RENDER_COLOUR_LINE,
				idx += 2,
				0;
		}
		// Specified colour, may end a line.
		default:
		{
			if (colour & _:e_TEXT_RENDER_COLOUR_LINE) return idx += 2, 0;
			else rc = colour;
		}
	}
	// This code does not AT ALL work for fades!
}




// I think we need to do newlines in a separate pass, and worry about getting
// what colour it is at the time - this shouldn't actually be THAT hard!  At
// least vastly simpler than the alternative!  In fact, in many cases it will
// be quite easy and we can just keep a record of the times when we need to do
// the more complex method, otherwise we just stick to the simple one.

enum E_RENDERING_DATA
{
	PlayerArray:E_RENDERING_DATA_PLAYERS<MAX_PLAYERS>, // Language players.
	E_RENDERING_DATA_ORIGINAL_COL, // Colour originally set.
	E_RENDERING_DATA_DISPLAY_COL   // Colour to start the next line with.
}




{
	if (IS_NEW_LINE) // This entry is a new line.
	{
		// Output a new line, and change the initial display colour.
		if (TOO_LONG_SINCE_LAST) // Too long since the last new line.
		{
			// Mark as needing more complex processing.
		}
		else
		{
			// Do simple output.
		}
	}
	if (IS_COLOUR)
	{
		// Stop fading.
	}
}







