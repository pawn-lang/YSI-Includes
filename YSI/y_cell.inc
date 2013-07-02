#undef _inc_y_cell

#include "..\YSI_Core\y_cell"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_cell
	#endinput
#endif
#define _YSI_3_1_INC_y_cell

static stock Use@@YSI_Code@y_cell()
{
}

#pragma deprecated Use@@YSI_Code@y_cell

forward YSI@y_cell();

public YSI@y_cell()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Code\y_cell>
	
	Instead of:
	
		#include <YSI\y_cell>
	*/
	Use@@YSI_Code@y_cell();
}

