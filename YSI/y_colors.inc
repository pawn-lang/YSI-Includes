#undef _inc_y_colors
#include "..\YSI-Server\y_colors"

static stock Use@@YSI_Server@y_colours()
{
}

#pragma deprecated Use@@YSI_Server@y_colours

forward YSI@y_colors();

public YSI@y_colors()
{
	Use@@YSI_Server@y_colours();
}

