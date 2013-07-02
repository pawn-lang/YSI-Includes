#undef _inc_y_languages

#include "..\YSI_Players\y_languages"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_languages
	#endinput
#endif
#define _YSI_3_1_INC_y_languages

static stock Use@@YSI_Players@y_languages()
{
}

#pragma deprecated Use@@YSI_Players@y_languages

forward YSI@y_languages();

public YSI@y_languages()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Players\y_languages>
	
	Instead of:
	
		#include <YSI\y_languages>
	*/
	Use@@YSI_Players@y_languages();
}

