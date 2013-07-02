#undef _inc_y_bit

#include "..\YSI_Data\y_bit"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_bit
	#endinput
#endif
#define _YSI_3_1_INC_y_bit

static stock Use@@YSI_Structures@y_bit()
{
}

#pragma deprecated Use@@YSI_Structures@y_bit

forward YSI@y_bit();

public YSI@y_bit()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Structures\y_bit>
	
	Instead of:
	
		#include <YSI\y_bit>
	*/
	Use@@YSI_Structures@y_bit();
}

