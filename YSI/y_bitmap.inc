#undef _inc_y_bitmap

#include "..\YSI-Storage\y_bitmap"

#if defined _YSI_3_1_INC_y_bitmap
	#endinput
#endif
#define _YSI_3_1_INC_y_bitmap

static stock Use@@YSI_Storage@y_bitmap()
{
}

#pragma deprecated Use@@YSI_Storage@y_bitmap

forward YSI@y_bitmap();

public YSI@y_bitmap()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Storage\y_bitmap>
	
	Instead of:
	
		#include <YSI\y_bitmap>
	*/
	Use@@YSI_Storage@y_bitmap();
}

