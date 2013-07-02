#undef _inc_y_bintree

#include "..\YSI-Data\y_bintree"

#if defined _YSI_3_1_INC_y_bintree
	#endinput
#endif
#define _YSI_3_1_INC_y_bintree

static stock Use@@YSI_Structures@y_bintree()
{
}

#pragma deprecated Use@@YSI_Structures@y_bintree

forward YSI@y_bintree();

public YSI@y_bintree()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Structures\y_bintree>
	
	Instead of:
	
		#include <YSI\y_bintree>
	*/
	Use@@YSI_Structures@y_bintree();
}

