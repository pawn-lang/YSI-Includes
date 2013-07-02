#undef _inc_y_races

#include "..\YSI_Visual\y_races"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_races
	#endinput
#endif
#define _YSI_3_1_INC_y_races

static stock Use@@YSI_Visual@y_races()
{
}

#pragma deprecated Use@@YSI_Visual@y_races

forward YSI@y_races();

public YSI@y_races()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Visual\y_races>
	
	Instead of:
	
		#include <YSI\y_races>
	*/
	Use@@YSI_Visual@y_races();
}

