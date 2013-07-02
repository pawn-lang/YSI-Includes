#undef _inc_y_zonenames

#include "..\YSI_Visual\y_zonenames"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_zonenames
	#endinput
#endif
#define _YSI_3_1_INC_y_zonenames

static stock Use@@YSI_Visual@y_zonenames()
{
}

#pragma deprecated Use@@YSI_Visual@y_zonenames

forward YSI@y_zonenames();

public YSI@y_zonenames()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Visual\y_zonenames>
	
	Instead of:
	
		#include <YSI\y_zonenames>
	*/
	Use@@YSI_Visual@y_zonenames();
}

