#undef _inc_y_properties

#include "..\YSI_Visual\y_properties"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_properties
	#endinput
#endif
#define _YSI_3_1_INC_y_properties

static stock Use@@YSI_Visual@y_properties()
{
}

#pragma deprecated Use@@YSI_Visual@y_properties

forward YSI@y_properties();

public YSI@y_properties()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Visual\y_properties>
	
	Instead of:
	
		#include <YSI\y_properties>
	*/
	Use@@YSI_Visual@y_properties();
}

