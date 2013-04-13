/**--------------------------------------------------------------------------**\
					=================================
					   y_bitmap - Generate bitmaps.
					=================================
Description:
	Code to generate images on the server in the bitmap format.  This is by far
	the simplest format to write to as it is just a huge array of colours (at
	least 24-bit bitmaps are, and we only do them).
	
	This file handles misc functions.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI utils include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.1
Changelog:
	29/03/13:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
\**--------------------------------------------------------------------------**/

//#define Bitmap:%0<>

/*enum E_BITMAP
{
	Alloc:E_BITMAP_MEMORY,
	E_BITMAP_SIZE,
	E_BITMAP_X,
	E_BITMAP_Y
}*/

#define Bitmap_Size(%0)   (YSI_gMallocMemory[_:(%0) - 3])
#define Bitmap_Width(%0)  (YSI_gMallocMemory[_:(%0) - 2])
#define Bitmap_Height(%0) (YSI_gMallocMemory[_:(%0) - 1])
//#define Bitmap_Height(%0) (YSI_gMallocMemory[_:(%0) - 1])

#define Bitmap_IndexInt(%9,%0,%1,%2) (_:(%9) + (_:(%2) * _:(%1)) + _:(%0))
#define Bitmap_IndexCtx(%9,%0,%2) (_:(%9) + (_:(%2) * _:Bitmap_Width(%9)) + _:(%0))
#define Bitmap_ReadInt(%9,%0,%1,%2) (YSI_gMallocMemory[_:(%9) + (_:(%2) * _:(%1)) + _:(%0)])
#define Bitmap_WriteInt(%9,%0,%1,%2,%3) (YSI_gMallocMemory[_:(%9) + (_:(%2) * _:(%1)) + _:(%0)] = (%3))
#define Bitmap_ReadCtx(%9,%0,%2) (YSI_gMallocMemory[_:(%9) + (_:(%2) * _:Bitmap_Width(%9)) + _:(%0)])
#define Bitmap_WriteCtx(%9,%0,%2,%3) (YSI_gMallocMemory[_:(%9) + (_:(%2) * _:Bitmap_Width(%9)) + _:(%0)] = (%3))

stock Bitmap:Bitmap_Create(xSize, ySize, bgColour = 0xFFFFFFFF)
{
	new
		s = xSize * ySize,
		Alloc:d = malloc(s + 3);
	if (!d) //(ctx[E_BITMAP_MEMORY] = d))
	{
		P:E("Could not allocate bitmap buffer");
		return Bitmap:0;
	}
	//ctx[E_BITMAP_SIZE] = s;
	//ctx[E_BITMAP_X] = x;
	//ctx[E_BITMAP_Y] = y;
	// Raw malloc access.  Set the background colour.
	memset(YSI_gMallocMemory[_:d + 3], s, bgColour | 0xFF);
	/*for (new y = 0; y != ySize; ++y)
	{
		for (new x = 0; x != xSize; ++x)
		{
			printf("(%02d, %02d) = %08x", x, y, YSI_gMallocMemory[
		}
	}*/
	mset(d, 0, s);
	mset(d, 1, xSize);
	mset(d, 2, ySize);
	// Hide the header data.
	return Bitmap:(_:d + 3);
}

stock Bitmap_Destroy(Bitmap:ctx)
{
	if (ctx) free(Alloc:(_:ctx - 3));
}
