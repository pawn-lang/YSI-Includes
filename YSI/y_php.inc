#undef _inc_y_php

#include "..\YSI_Storage\y_php"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_php
	#endinput
#endif
#define _YSI_3_1_INC_y_php

static stock Use@@YSI_Storage@y_php()
{
}

#pragma deprecated Use@@YSI_Storage@y_php

forward YSI@y_php();

public YSI@y_php()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Storage\y_php>
	
	Instead of:
	
		#include <YSI\y_php>
	*/
	Use@@YSI_Storage@y_php();
}

