#undef _inc_y_writemem
#include "..\YSI-Internal\y_writemem"

static stock Use@@YSI_Internal@y_writemem()
{
}

#pragma deprecated Use@@YSI_Internal@y_writemem

forward YSI@y_writemem();

public YSI@y_writemem()
{
	Use@@YSI_Internal@y_writemem();
}

