#undef _inc_y_scriptinit

#include "..\YSI_Server\y_scriptinit"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_scriptinit
	#endinput
#endif
#define _YSI_3_1_INC_y_scriptinit

static stock Use@@YSI_Server@y_scriptinit()
{
}

#pragma deprecated Use@@YSI_Server@y_scriptinit

forward YSI@y_scriptinit();

public YSI@y_scriptinit()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_scriptinit>
	
	Instead of:
	
		#include <YSI\y_scriptinit>
	*/
	Use@@YSI_Server@y_scriptinit();
}

