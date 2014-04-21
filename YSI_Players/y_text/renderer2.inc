// y_text renderer v2.

// This new version embeds linked lists for each item of interest in the strings
// to iterate over one at a time.  The items of interest are (currently):
//  
//  - SA:MP format specifiers.
//  - Custom (YSI) format specifiers.
//  - Colours.
//  - Line breaks.
//  
// The formats for each are below.



#define Y_TEXT_STATIC

static stock TextR_GetNext(string:str[], pos)
{
	
}

enum E_TEXT_RENDER_PASSES
{
	E_TEXT_RENDER_PASS_ALL = -1,
	E_TEXT_RENDER_PASS_NATIVE,
	E_TEXT_RENDER_PASS_CUSTOM,
	E_TEXT_RENDER_PASS_COLOUR,
	E_TEXT_RENDER_PASS_NEWLINE
}

enum e_TEXT_RENDER
{
	e_TEXT_RENDER_NEXT_MASK  = 0x00FFFFFF,
	e_TEXT_RENDER_NEXT_SHIFT = 0,
	e_TEXT_RENDER_TYPE_MASK  = 0xFF000000,
	e_TEXT_RENDER_TYPE_SHIFT = 24
}

enum e_TEXT_RENDER_SAMP
{
	// The basic types (%x etc).
	e_TEXT_RENDER_SAMP_TYPE_MASK  = 0xE0000000,
	e_TEXT_RENDER_SAMP_TYPE_SHIFT = 29,
	e_TEXT_RENDER_SAMP_TYPE_b     = 0x20000000,
	e_TEXT_RENDER_SAMP_TYPE_c     = 0x40000000,
	e_TEXT_RENDER_SAMP_TYPE_di    = 0x60000000,
	e_TEXT_RENDER_SAMP_TYPE_f     = 0x80000000,
	e_TEXT_RENDER_SAMP_TYPE_hx    = 0xA0000000,
	e_TEXT_RENDER_SAMP_TYPE_s     = 0xC0000000,
	
	// Weight (%5s etc).
	e_TEXT_RENDER_SAMP_WEIGHT_MASK  = 0x00FFF000,
	e_TEXT_RENDER_SAMP_WEIGHT_SHIFT = 12,
	
	// Precision (%.5s etc).
	e_TEXT_RENDER_SAMP_PREC_MASK  = 0x00000FFF,
	e_TEXT_RENDER_SAMP_PREC_SHIFT = 0,
	
	// Additional flags (%0*f etc).
	e_TEXT_RENDER_SAMP_FLAG_MASK   = 0x1F000000,
	e_TEXT_RENDER_SAMP_FLAG_SHIFT  = 24,
	e_TEXT_RENDER_SAMP_FLAG_0PAD   = 0x01000000,
	e_TEXT_RENDER_SAMP_FLAG_WEIGHT = 0x02000000,
	e_TEXT_RENDER_SAMP_FLAG_PREC   = 0x04000000,
	e_TEXT_RENDER_SAMP_FLAG_WSTAR  = 0x08000000,
	e_TEXT_RENDER_SAMP_FLAG_PSTAR  = 0x10000000
}

/**
<remarks>
	While processing a string, we maintain multiple linked lists, each one
	holding the formatting locations for different passes.  There are several
	passes of the data:
	
		1) SA:MP formatting - Does all the standard format specifiers (%d etc).
		2) YSI formatting - Does custom specifiers like "%n".
		4) Colours - Fades require the full text, so come after formatting.
		3) Newlines - Determine how (if) to split the string up.
	
	The colours coming before the newlines is a little awkward, but so is the
	other way around.  I think I might actually need a new way of doing it that
	extracts the newline linked list before doing colours, but then the tested
	TextR_UpdatePass function can't be used...  Were that to be done though, the
	newline linked list would be extracted, colours would be done simply, while
	updating the newline linked list, then renders would be done last.  In fact,
	newlines should probably be part of the "render" pass.
</remarks>
**/

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
				off = (str[cur] += addition) & e_TEXT_RENDER_NEXT_MASK;
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

enum E_TEXT_RENDER_SAMP
{
	E_TEXT_RENDER_SAMP_NEXT,
	e_TEXT_RENDER_SAMP:E_TEXT_RENDER_SAMP_TYPE
}


//  




