#undef _inc_y_colors

#include "..\YSI_Server\y_colors"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_colors
	#endinput
#endif
#define _YSI_3_1_INC_y_colors

static stock Use@@YSI_Server@y_colours()
{
}

#pragma deprecated Use@@YSI_Server@y_colours

forward YSI@y_colors();

public YSI@y_colors()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_colours>
	
	Instead of:
	
		#include <YSI\y_colours>
	*/
	Use@@YSI_Server@y_colours();
}

