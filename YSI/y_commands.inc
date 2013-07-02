#undef _inc_y_commands

#include "..\YSI-Visual\y_commands"

#if defined _YSI_3_1_INC_y_commands
	#endinput
#endif
#define _YSI_3_1_INC_y_commands

static stock Use@@YSI_Visual@y_commands()
{
}

#pragma deprecated Use@@YSI_Visual@y_commands

forward YSI@y_commands();

public YSI@y_commands()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Visual\y_commands>
	
	Instead of:
	
		#include <YSI\y_commands>
	*/
	Use@@YSI_Visual@y_commands();
}

