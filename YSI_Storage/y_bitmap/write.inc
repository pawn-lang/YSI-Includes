/**--------------------------------------------------------------------------**\
					=================================
					   y_bitmap - Generate bitmaps.
					=================================
Description:
	Code to generate images on the server in the bitmap format.  This is by far
	the simplest format to write to as it is just a huge array of colours (at
	least 24-bit bitmaps are, and we only do them).
	
	This file is responsible for writing the generated data out to a file.
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

static stock
	YSI_g_sFileHeader[] =
	{
		'B', 'M',   // bfType      (Just "BM" for Windows BMP).
		1, 1, 1, 1, // bfSize      (File size in bytes).
		0, 0,       // bfReserved1 (Unused).
		0, 0,       // bfReserved2 (Unused).
		2, 2, 2, 2  // bfOffBits   (Offset to the start of the data).
	},
	YSI_g_sInfoHeader[] =
	{
		40, 0, 0, 0,  // biSize          (This header's size).
		4,  4, 4, 4,  // biWidth         (Image width).
		5,  5, 5, 5,  // biHeight        (Image height).
		1,  0,        // biPlanes        (1 "plane").
		24, 0,        // biBitCount      (24-bit image).
		0,  0, 0, 0,  // biCompression   (Unused).
		0,  0, 0, 0,  // biSizeImage     (Unused).
		0,  0, 0, 0,  // biXPelsPerMeter (Unused).
		0,  0, 0, 0,  // biYPelsPerMeter (Unused).
		0,  0, 0, 0,  // biClrUsed       (Unused).
		0,  0, 0, 0   // biClrImportant  (Unused).
	};

static stock MKLE32(dest[], num, &idx = 0)
{
	dest[idx++] = num & 0xFF;
	dest[idx++] = num >>> 8 & 0xFF;
	dest[idx++] = num >>> 16 & 0xFF;
	dest[idx++] = num >>> 24 & 0xFF;
}

static stock MK24(dest[], num, &idx = 0)
{
	//if (num != -1) printf("colour %d", num);
	dest[idx++] = num >>>  8 & 0xFF;
	dest[idx++] = num >>> 16 & 0xFF;
	dest[idx++] = num >>> 24 & 0xFF;
}

static stock Bitmap_PadRow(dest[], &idx)
{
	while (idx & 0x03)
	{
		dest[idx++] = 0;
	}
}

static stock Bitmap_WriteHeader(Bitmap:ctx, File:bmp)
{
	MKLE32(YSI_g_sInfoHeader[4], Bitmap_Width(ctx));
	MKLE32(YSI_g_sInfoHeader[8], Bitmap_Height(ctx));
	/*new
		x = Bitmap_Width(ctx),
		y = Bitmap_Height(ctx),
		// Pad to a 4 byte boundary with 3 bytes per pixel.
		fsize = ceildiv(x * 3, 4) * 4 * y;
	MKLE32(YSI_g_sFileHeader[2], fsize + sizeof (YSI_g_sFileHeader) + sizeof (YSI_g_sInfoHeader));*/
	// Pad to a 4 byte boundary with 3 bytes per pixel.
	MKLE32(YSI_g_sFileHeader[2], ceildiv(Bitmap_Width(ctx) * 3, 4) * 4 * Bitmap_Height(ctx) + sizeof (YSI_g_sFileHeader) + sizeof (YSI_g_sInfoHeader));
	MKLE32(YSI_g_sFileHeader[10], sizeof (YSI_g_sFileHeader) + sizeof (YSI_g_sInfoHeader));
	for (new j = 0; j != sizeof (YSI_g_sFileHeader); ++j)
	{
		fputchar(bmp, YSI_g_sFileHeader[j], false);
	}
	for (new j = 0; j != sizeof (YSI_g_sInfoHeader); ++j)
	{
		fputchar(bmp, YSI_g_sInfoHeader[j], false);
	}
}

static stock Bitmap_WriteBlock(File:bmp, buf[], len)
{
	for (new i = 0; i != len; ++i)
	{
		fputchar(bmp, buf[i], false);
	}
}

static stock Bitmap_WriteBody(Bitmap:ctx, File:bmp)
{
	// Write 4 pixels in to 3 blocks.
	static
		sWriteBlock[12];
	new
		width = Bitmap_Width(ctx),
		w2 = width & ~0x3,
		height = Bitmap_Height(ctx);
	//width &= 0x3;
	//for (new y = height; y-- > 0; )
	for (new y = height; y-- != 0; )
	{
		// Go through the array backwards (bottom to top).
		new
			x = 0;
		//printf(": %d = %d", Bitmap_IndexCtx(ctx, 10, y), Bitmap_ReadCtx(ctx, 10, y));
		//printf(": %d = %d", Bitmap_IndexInt(ctx, 10, y), Bitmap_ReadInt(ctx, 10, y));
		for ( ; x != w2; x += 4)
		{
			new
				i = 0;
			MK24(sWriteBlock, Bitmap_ReadInt(ctx, x, width, y), i);
			MK24(sWriteBlock, Bitmap_ReadInt(ctx, x + 1, width, y), i);
			MK24(sWriteBlock, Bitmap_ReadInt(ctx, x + 2, width, y), i);
			MK24(sWriteBlock, Bitmap_ReadInt(ctx, x + 3, width, y), i);
			Bitmap_WriteBlock(bmp, sWriteBlock, 12);
		}
		switch (width & 0x03)
		{
			case 1:
			{
				// Write 1, pad 1.
				MK24(sWriteBlock[0], Bitmap_ReadInt(ctx, x, width, y));
				sWriteBlock[3] = 0;
				Bitmap_WriteBlock(bmp, sWriteBlock, 4);
			}
			case 2:
			{
				// Write 2, pad 2.
				MK24(sWriteBlock[0], Bitmap_ReadInt(ctx, x, width, y));
				MK24(sWriteBlock[3], Bitmap_ReadInt(ctx, x + 1, width, y));
				sWriteBlock[6] = 0;
				sWriteBlock[7] = 0;
				Bitmap_WriteBlock(bmp, sWriteBlock, 8);
			}
			case 3:
			{
				// Write 3, pad 3.
				MK24(sWriteBlock[0], Bitmap_ReadInt(ctx, x, width, y));
				MK24(sWriteBlock[3], Bitmap_ReadInt(ctx, x + 1, width, y));
				MK24(sWriteBlock[6], Bitmap_ReadInt(ctx, x + 2, width, y));
				sWriteBlock[9] = 0;
				sWriteBlock[10] = 0;
				sWriteBlock[11] = 0;
				Bitmap_WriteBlock(bmp, sWriteBlock, 12);
			}
		}
	}
}

stock bool:Bitmap_Write(Bitmap:ctx, const file[])
{
	if (fexist(file)) fremove(file);
	new
		File:bmp = fopen(file, io_write);
	if (!bmp) return false;
	Bitmap_WriteHeader(ctx, bmp);
	Bitmap_WriteBody(ctx, bmp);
	fclose(bmp);
	return true;
}

#endinput
// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

#pragma dynamic 16680064

#include <a_samp>
#include <YSI\y_colours>

new
	gAlphabet[10][26 + 1 + 10 + 1] =
	{
		// A     B     C     D     E     F     G     H     I     J     K     L     M     N     O     P     Q     R     S     T     U     V     W     X     Y     Z           0     1     2     3     4     5     6     7     8     9     ~
		{0x30, 0xFC, 0x3C, 0xF8, 0xFE, 0xFE, 0x3C, 0xCC, 0x78, 0x1E, 0xE6, 0xF0, 0xC6, 0xC6, 0x38, 0xFC, 0x38, 0xFC, 0x78, 0xFC, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0xFE, 0x00, 0x7C, 0x10, 0x78, 0x78, 0x0C, 0xFC, 0x38, 0xFE, 0x78, 0x78, 0x73},
		{0x78, 0x66, 0x66, 0x6C, 0x62, 0x66, 0x66, 0xCC, 0x30, 0x0C, 0x66, 0x60, 0xEE, 0xC6, 0x6C, 0x66, 0x6C, 0x66, 0xCC, 0xB4, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0xCE, 0x00, 0xC6, 0x30, 0xCC, 0xCC, 0x1C, 0xC0, 0x60, 0xC6, 0xCC, 0xCC, 0xDA},
		{0xCC, 0x66, 0xC6, 0x66, 0x60, 0x62, 0xC6, 0xCC, 0x30, 0x0C, 0x6C, 0x60, 0xFE, 0xE6, 0xC6, 0x66, 0xC6, 0x66, 0xCC, 0x30, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0x98, 0x00, 0xCE, 0xF0, 0xCC, 0x0C, 0x3C, 0xC0, 0xC0, 0xC6, 0xCC, 0xCC, 0xCE},
		{0xCC, 0x66, 0xC0, 0x66, 0x64, 0x64, 0xC0, 0xCC, 0x30, 0x0C, 0x6C, 0x60, 0xFE, 0xF6, 0xC6, 0x66, 0xC6, 0x66, 0xC0, 0x30, 0xCC, 0xCC, 0xC6, 0x78, 0xCC, 0x18, 0x00, 0xDE, 0x30, 0x0C, 0x0C, 0x6C, 0xC0, 0xC0, 0x06, 0xCC, 0xCC, 0x00},
		{0xCC, 0x7C, 0xC0, 0x66, 0x7C, 0x7C, 0xC0, 0xFC, 0x30, 0x0C, 0x78, 0x60, 0xD6, 0xFE, 0xC6, 0x7C, 0xC6, 0x7C, 0x70, 0x30, 0xCC, 0xCC, 0xD6, 0x30, 0x78, 0x30, 0x00, 0xD6, 0x30, 0x18, 0x38, 0xCC, 0xF8, 0xF8, 0x0C, 0x78, 0x7C, 0x00},
		{0xFC, 0x66, 0xC0, 0x66, 0x64, 0x64, 0xCE, 0xCC, 0x30, 0xCC, 0x6C, 0x62, 0xC6, 0xDE, 0xC6, 0x60, 0xCE, 0x6C, 0x18, 0x30, 0xCC, 0xCC, 0xD6, 0x78, 0x30, 0x60, 0x00, 0xF6, 0x30, 0x30, 0x0C, 0xFE, 0x0C, 0xCC, 0x18, 0xCC, 0x18, 0x00},
		{0xCC, 0x66, 0xC6, 0x66, 0x60, 0x60, 0xC6, 0xCC, 0x30, 0xCC, 0x6C, 0x66, 0xC6, 0xCE, 0xC6, 0x60, 0xDE, 0x66, 0xCC, 0x30, 0xCC, 0xCC, 0x6C, 0xCC, 0x30, 0x62, 0x00, 0xE6, 0x30, 0x60, 0x0C, 0x0C, 0x0C, 0xCC, 0x30, 0xCC, 0x18, 0x00},
		{0xCC, 0x66, 0x66, 0x6C, 0x62, 0x60, 0x66, 0xCC, 0x30, 0xCC, 0x66, 0x66, 0xC6, 0xC6, 0x6C, 0x60, 0x7C, 0x66, 0xCC, 0x30, 0xCC, 0x78, 0x6C, 0xCC, 0x30, 0xC6, 0x00, 0xC6, 0x30, 0xCC, 0xCC, 0x0C, 0xCC, 0xCC, 0x30, 0xCC, 0x30, 0x00},
		{0xCC, 0xFC, 0x3C, 0xF8, 0xFE, 0xF0, 0x3E, 0xCC, 0x78, 0x78, 0xE6, 0xFE, 0xC6, 0xC6, 0x38, 0xF0, 0x0C, 0xE6, 0x78, 0x78, 0x78, 0x30, 0x6C, 0xCC, 0x78, 0xFE, 0x00, 0x7C, 0xFC, 0xFC, 0x78, 0x1E, 0x78, 0x78, 0x30, 0x78, 0x70, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};

AddLetter(colour, letter, data[][], &x, &y)
{
	if ('a' <= letter <= 'z') letter -= 'a';
	else if ('A' <= letter <= 'Z') letter -= 'A';
	else if ('0' <= letter <= '9') letter = letter - '0' + 27;
	else if (letter == '~') letter = 26 + 1 + 10;
	else letter = 26;
	for (new j = 0; j != 10; ++j)
	{
		for (new i = 0, k = 0x80; i != 8; ++i, k >>= 1)
		{
			if (gAlphabet[j][letter] & k) data[y + j][x + i] = colour;
		}
	}
	x += 8;
}

AddBlock(colour, data[][], &x, &y, width)
{
	for (new j = 0; j != 50; ++j)
	{
		for (new i = 0; i != 200; ++i)
		{
			data[y + j][x + i] = colour;
		}
	}
	x += 202;
	if (x == width)
	{
		x = 2;
		y += 52;
	}
}

AddString(colour, str[], data[][], &x, &y)
{
	for (new i = 0, ch; (ch = str[i]); ++i)
	{
		AddLetter(colour, ch, data, x, y);
	}
}

AddColour(colour, name[], data[][], &x, &y)
{
	new
		ox = x + 10,
		oy = y + 20;
	colour >>>= 8;
	printf("%08x", colour);
	AddBlock(colour, data, x, y, 202 * 5 + 2);
	if (colour >> 16 & 0xFF < 32 && colour >> 8 & 0xFF < 32 && colour & 0xFF < 32)
	{
		// White (on dark).
		AddString(0xFFFFFF, name, data, ox, oy);
	}
	else
	{
		// Black (on most).
		AddString(0x000000, name, data, ox, oy);
	}
}

#define DO_X11(X11_%0) AddColour(X11_%0, #%0, gGridData, x, y)

#define DO_GT(%0,%1) AddColour(SAMP_GAME_TEXT%0, #%1, gGridData, x, y)

main()
{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
	new
		gGridData[1400 / 5 * 52 + 2][202 * 5 + 2]; // = {0xFF0000, ...};
	new
		x = 2,
		y = 2;
//	AddString(-1, "Hello There", gGridData, x, y);
#include "x11.pwn"
	WriteBMP(gGridData, sizeof (gGridData), sizeof (gGridData[]));
}

MKLE32(dest[], num)
{
	dest[0] = num & 0xFF;
	dest[1] = num >>> 8 & 0xFF;
	dest[2] = num >>> 16 & 0xFF;
	dest[3] = num >>> 24 & 0xFF;
}

/*Inv(dest[], idx)
{
	dest[idx] = (dest[idx] >>> 24) | (dest[idx] & 0xFF0000 >> 8) | (dest[idx] & 0xFF00 << 8) | (dest[idx] & 0xFF << 24);
}

MK24(dest[], num, &idx)
{
	dest{idx++} = num >>> 16 & 0xFF;
	if (idx & 0x07 == 0x04) Inv(dest, idx >> 2);
	dest{idx++} = num >>> 8 & 0xFF;
	if (idx & 0x07 == 0x04) Inv(dest, idx >> 2);
	dest{idx++} = num & 0xFF;
	if (idx & 0x07 == 0x04) Inv(dest, idx >> 2);
}

Pad(dest[], &idx)
{
	while (idx & 0x03)
	{
		dest{idx++} = 0;
	}
	if (idx & 0x07 == 0x04) Inv(dest, idx >> 2);
}*/

MK24(dest[], num, &idx)
{
	dest[idx++] = num & 0xFF;
	dest[idx++] = num >>> 8 & 0xFF;
	dest[idx++] = num >>> 16 & 0xFF;
}

Pad(dest[], &idx)
{
	while (idx & 0x03)
	{
		dest[idx++] = 0;
	}
}

WriteBMP(data[][], y, x)
{
	new
		File:bmp = fopen("x11_colours.bmp", io_write);
	if (!bmp)
	{
		printf("File Error");
		return;
	}
	printf("header");
	// Sizes are little endian.
	static
		sFileHeader[] =
		{
			'B', 'M', // bfType
			1, 1, 1, 1, // bfSize
			0, 0, // bfReserved1
			0, 0, // bfReserved2
			2, 2, 2, 2 // bfOffBits
		},
		sInfoHeader[] =
		{
			40, 0, 0, 0, // biSize
			4, 4, 4, 4, // biWidth
			5, 5, 5, 5, // biHeight
			0, 0, // biPlanes
			24, 0, // biBitCount
			0, 0, 0, 0, // biCompression
			0, 0, 0, 0, // biSizeImage
			0, 0, 0, 0, // biXPelsPerMeter
			0, 0, 0, 0, // biYPelsPerMeter
			0, 0, 0, 0, // biClrUsed
			0, 0, 0, 0 // biClrImportant
		};
	MKLE32(sInfoHeader[4], x);
	MKLE32(sInfoHeader[8], y);
	MKLE32(sFileHeader[2], x * y * 3 + sizeof (sFileHeader) + sizeof (sInfoHeader));
	MKLE32(sFileHeader[10], sizeof (sFileHeader) + sizeof (sInfoHeader));
	printf("write");
	for (new j = 0; j != sizeof (sFileHeader); ++j)
	{
		fputchar(bmp, sFileHeader[j], false);
	}
	for (new j = 0; j != sizeof (sInfoHeader); ++j)
	{
		fputchar(bmp, sInfoHeader[j], false);
	}
	//fblockwrite(bmp, sFileHeader, sizeof (sFileHeader));
	//fblockwrite(bmp, sInfoHeader, sizeof (sInfoHeader));
	printf("body");
	static
		sRow[(202 * 5 + 2) * 3];
	for (new i = y; i-- > 0; )
	{
		//printf("row %d", i);
		// Go through the array backwards (bottom to top).
		new
			idx;
		for (new j = 0; j != x; ++j)
		{
			MK24(sRow, data[i][j], idx);
		}
		Pad(sRow, idx);
		//printf("%04x%04x %04x%04x %04x%04x", sRow[0] >>> 16, sRow[0] & 0xFFFF, sRow[1] >>> 16, sRow[1] & 0xFFFF, sRow[2] >>> 16, sRow[2] & 0xFFFF);
		//strpack(sRow, sRow, idx);
		//fblockwrite(bmp, sRow, idx >> 2);
		for (new j = 0; j != idx; ++j) //j += 4)
		{
			/*sChar{0} = sRow[j + 0];
			sChar{1} = sRow[j + 1];
			sChar{2} = sRow[j + 2];
			sChar{3} = sRow[j + 3];
			fblockwrite(bmp, sChar, 1);*/
			fputchar(bmp, sRow[j], false);
			//fseek(bmp, -3, seek_current);
		}
	}
	printf("done");
	fclose(bmp);
}
