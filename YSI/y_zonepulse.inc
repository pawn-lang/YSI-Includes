#undef _inc_y_zonepulse

#include "..\YSI_Visual\y_zonepulse"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_zonepulse
	#endinput
#endif
#define _YSI_3_1_INC_y_zonepulse

static stock Use@@YSI_Visual@y_zonepulse()
{
}

#pragma deprecated Use@@YSI_Visual@y_zonepulse

forward YSI@y_zonepulse();

public YSI@y_zonepulse()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Visual\y_zonepulse>
	
	Instead of:
	
		#include <YSI\y_zonepulse>
	*/
	Use@@YSI_Visual@y_zonepulse();
}

