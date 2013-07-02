#undef _inc_y_colours

#include "..\YSI_Server\y_colours"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_colours
	#endinput
#endif
#define _YSI_3_1_INC_y_colours

static stock Use@@YSI_Server@y_colours()
{
}

#pragma deprecated Use@@YSI_Server@y_colours

forward YSI@y_colours();

public YSI@y_colours()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_colours>
	
	Instead of:
	
		#include <YSI\y_colours>
	*/
	Use@@YSI_Server@y_colours();
}

