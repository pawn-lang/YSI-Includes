#undef _inc_y_playerarray

#include "..\YSI_Data\y_playerarray"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_playerarray
	#endinput
#endif
#define _YSI_3_1_INC_y_playerarray

static stock Use@@YSI_Structures@y_playerarray()
{
}

#pragma deprecated Use@@YSI_Structures@y_playerarray

forward YSI@y_playerarray();

public YSI@y_playerarray()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Structures\y_playerarray>
	
	Instead of:
	
		#include <YSI\y_playerarray>
	*/
	Use@@YSI_Structures@y_playerarray();
}

