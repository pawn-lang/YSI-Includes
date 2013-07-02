#undef _inc_y_jaggedarray

#include "..\YSI-Data\y_jaggedarray"

#if defined _YSI_3_1_INC_y_jaggedarray
	#endinput
#endif
#define _YSI_3_1_INC_y_jaggedarray

static stock Use@@YSI_Structures@y_jaggedarray()
{
}

#pragma deprecated Use@@YSI_Structures@y_jaggedarray

forward YSI@y_jaggedarray();

public YSI@y_jaggedarray()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Structures\y_jaggedarray>
	
	Instead of:
	
		#include <YSI\y_jaggedarray>
	*/
	Use@@YSI_Structures@y_jaggedarray();
}

