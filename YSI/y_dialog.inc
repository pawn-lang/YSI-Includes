#undef _inc_y_dialog

#include "..\YSI_Visual\y_dialog"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_dialog
	#endinput
#endif
#define _YSI_3_1_INC_y_dialog

static stock Use@@YSI_Visual@y_dialog()
{
}

#pragma deprecated Use@@YSI_Visual@y_dialog

forward YSI@y_dialog();

public YSI@y_dialog()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Visual\y_dialog>
	
	Instead of:
	
		#include <YSI\y_dialog>
	*/
	Use@@YSI_Visual@y_dialog();
}

