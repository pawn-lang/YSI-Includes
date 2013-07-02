#undef _inc_y_text

#include "..\YSI-Players\y_text"

#if defined _YSI_3_1_INC_y_text
	#endinput
#endif
#define _YSI_3_1_INC_y_text

static stock Use@@YSI_Players@y_text()
{
}

#pragma deprecated Use@@YSI_Players@y_text

forward YSI@y_text();

public YSI@y_text()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Players\y_text>
	
	Instead of:
	
		#include <YSI\y_text>
	*/
	Use@@YSI_Players@y_text();
}

