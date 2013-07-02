#undef _inc_y_timers

#include "..\YSI_Coding\y_timers"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_timers
	#endinput
#endif
#define _YSI_3_1_INC_y_timers

static stock Use@@YSI_Coding@y_timers()
{
}

#pragma deprecated Use@@YSI_Coding@y_timers

forward YSI@y_timers();

public YSI@y_timers()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_timers>
	
	Instead of:
	
		#include <YSI\y_timers>
	*/
	Use@@YSI_Coding@y_timers();
}

