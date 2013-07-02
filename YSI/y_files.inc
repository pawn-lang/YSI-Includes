#undef _inc_y_files

#include "..\YSI_Extra\y_files"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_files
	#endinput
#endif
#define _YSI_3_1_INC_y_files

static stock Use@@YSI_Extra@y_files()
{
}

#pragma deprecated Use@@YSI_Extra@y_files

forward YSI@y_files();

public YSI@y_files()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Extra\y_files>
	
	Instead of:
	
		#include <YSI\y_files>
	*/
	Use@@YSI_Extra@y_files();
}

