// Rendered v3.  In this version, strings are pre-processed to remove ALL of the
// special characters, and linked lists of them are appended to the end of the
// string instead.

// We can probably merge the two formatting phases, there is really no reason
// for them to be separate (assuming I can compact enough data in).

// Colours are stored in a very unique manner (at least I've never seen it
// before).  Most people can't tell the difference visually between, say,
// 0x286A44FF and 0x286A45FF (it's hard enough to read the difference).  There
// is just one bit different, and that is the LSB of the Blue component, meaning
// that it makes a trivial contribution to the colour displayed.  If we use
// these LSBs for something else, then it doesn't matter if they are set or not
// for the display of the colour, and we can instead get 4 bit flags embedded
// within the colour.

enum e_TEXT_RENDER_COLOUR
{
	e_TEXT_RENDER_COLOUR_END  = 0x01000000, // {/}
	e_TEXT_RENDER_COLOUR_FADE = 0x00010000, // {>XXXXXX}
	e_TEXT_RENDER_COLOUR_STAR = 0x00000100, // {*}
	e_TEXT_RENDER_COLOUR_____ = 0x00000001, // <unused>
	e_TEXT_RENDER_COLOUR_MASK = 0xFEFEFEFE
}

// We have 



#if 0

// Current specifier position: 10
// Inserted data: 12 characters.

	// For each pass after the current one...
	{
		// Get the current pointer in the linked list.
		new
			cur = indexes[pass];
		// Add the shift on.
		str[cur] += addition;
		do
		{
			cur += 2;
		}
		while
	}


Y_TEXT_STATIC stock TextR_UpdatePass(string:str[], indexes[E_TEXT_RENDER_PASSES], addition, nextPos, E_TEXT_RENDER_PASSES:pass)
{
	// "pass" is not defined here in "for" so we can skip early passes in the
	// update code after they have already been run.  The calling code passes
	// the CURRENT pass, which is instantly incremented.
	while (++pass != E_TEXT_RENDER_PASSES)
	{
		new
			cur = indexes[pass];
		if (cur > nextPos)
		{
			// Also covers cases where there are none left.
			indexes[pass] += addition;
		}
		else
		{
			// Add the length of the string just formatted (-2) to the offset to
			// the next action of the current pass in this string.  Get the new
			// relative offset to the next item.
			new
				off = (str[cur] += addition);
			// Find the absolute position of the next item, then test if it is
			// before "nextPos" (not <=).
			while ((cur += off) < nextPos)
			{
				if ((off = str[cur] & e_TEXT_RENDER_NEXT_MASK))
				{
					indexes[pass] = cur;
				}
				else
				{
					// There are no actions of this rendering pass after
					// "nextPos" in the string.
					indexes[pass] = 65536;
					break;
				}
			}
		}
	}
}

#endif

