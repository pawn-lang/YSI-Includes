#undef _inc_y_malloc

#include "..\YSI_Coding\y_malloc"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_malloc
	#endinput
#endif
#define _YSI_3_1_INC_y_malloc

static stock Use@@YSI_Coding@y_malloc()
{
}

#pragma deprecated Use@@YSI_Coding@y_malloc

forward YSI@y_malloc();

public YSI@y_malloc()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_malloc>
	
	Instead of:
	
		#include <YSI\y_malloc>
	*/
	Use@@YSI_Coding@y_malloc();
}

