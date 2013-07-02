#undef _inc_y_inline

#include "..\YSI_Coding\y_inline"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_inline
	#endinput
#endif
#define _YSI_3_1_INC_y_inline

static stock Use@@YSI_Coding@y_inline()
{
}

#pragma deprecated Use@@YSI_Coding@y_inline

forward YSI@y_inline();

public YSI@y_inline()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_inline>
	
	Instead of:
	
		#include <YSI\y_inline>
	*/
	Use@@YSI_Coding@y_inline();
}

