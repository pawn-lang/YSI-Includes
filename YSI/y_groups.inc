#undef _inc_y_groups

#include "..\YSI_Players\y_groups"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_groups
	#endinput
#endif
#define _YSI_3_1_INC_y_groups

static stock Use@@YSI_Players@y_groups()
{
}

#pragma deprecated Use@@YSI_Players@y_groups

forward YSI@y_groups();

public YSI@y_groups()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Players\y_groups>
	
	Instead of:
	
		#include <YSI\y_groups>
	*/
	Use@@YSI_Players@y_groups();
}

