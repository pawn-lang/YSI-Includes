#undef _inc_y_areas

#include "..\YSI_Visual\y_areas"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_areas
	#endinput
#endif
#define _YSI_3_1_INC_y_areas

static stock Use@@YSI_Visual@y_areas()
{
}

#pragma deprecated Use@@YSI_Visual@y_areas

forward YSI@y_areas();

public YSI@y_areas()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Visual\y_areas>
	
	Instead of:
	
		#include <YSI\y_areas>
	*/
	Use@@YSI_Visual@y_areas();
}

