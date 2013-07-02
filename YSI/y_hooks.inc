#undef _inc_y_hooks

#include "..\YSI_Coding\y_hooks"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_hooks
	#endinput
#endif
#define _YSI_3_1_INC_y_hooks

static stock Use@@YSI_Coding@y_hooks()
{
}

#pragma deprecated Use@@YSI_Coding@y_hooks

forward YSI@y_hooks();

public YSI@y_hooks()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_hooks>
	
	Instead of:
	
		#include <YSI\y_hooks>
	*/
	Use@@YSI_Coding@y_hooks();
}

