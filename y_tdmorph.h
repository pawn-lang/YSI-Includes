// y_tdmorph - morphs a textdraw from one style to another.  You can use this to
// fade them in and out (same location, different colour), move them across the
// screen (same style, different location) or do almost anything else (shrink,
// grow, bounce about etc).

forward MorphTD(Text:td, Style:from, Style:to, speed, pos);

public MorphTD(Text:td, Style:from, Style:to, speed, pos)
{
	// Morph a text draw from one style to another.
	stock
		sFrom[E_TD_DATA],
		sTo[E_TD_DATA],
		sCur[E_TD_DATA];
	// Get the end style.
	TD_GetStyle(to, sTo);
	if (pos == speed)
	{
		// Show the TD using the end point only (no interpolation).
		
		// We could add a callback here to indicate that the morph is done.
	}
	else
	{
		// Get the start style.
		TD_GetStyle(from, sFrom);
		// Interpolate.
		#define MORPH_TD_FROM_TO(%0) sCur[E_TD_DATA_%0] = (sTo[E_TD_DATA_%0] - sFrom[E_TD_DATA_%0]) * pos / speed + sFrom[E_TD_DATA_%0]
		MORPH_TD_FROM_TO(X);
		MORPH_TD_FROM_TO(Y);
		MORPH_TD_FROM_TO(LX);
		MORPH_TD_FROM_TO(LY);
		MORPH_TD_FROM_TO(TX);
		MORPH_TD_FROM_TO(TY);
		MORPH_TD_FROM_TO(COLOUR);
		MORPH_TD_FROM_TO(BITS);
		MORPH_TD_FROM_TO(BOX);
		MORPH_TD_FROM_TO(BG);
		#undef MORPH_TD_FROM_TO
		// Show the interpolated TD data.
	}
}
