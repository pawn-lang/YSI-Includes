/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

//static stock GTLE32(const src[])
//{
//	return src[0]
//		| (src[1] << 8)
//		| (src[2] << 16)
//		| (src[3] << 24);
//}

static stock GT24(const src[])
{
	return 0xFF
		| (src[0] << 8)
		| (src[1] << 16)
		| (src[2] << 24);
}

static stock
	YSI_g_sBlock[13];

static stock bool:Bitmap_ReadHeader(File:bmp, &x, &y)
{
	if (fgetchar(bmp, 0, false) != 'B' || fgetchar(bmp, 0, false) != 'M')
	{
		return false;
	}

	// Load in the header.
	fblockread(bmp, YSI_g_sBlock);
	//new size = YSI_g_sBlock[0];
	P:5("Bitmap_ReadHeader: %08x %08x %08x", YSI_g_sBlock[0], YSI_g_sBlock[1], YSI_g_sBlock[2]);
	P:5("Bitmap_ReadHeader: %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x", YSI_g_sBlock[3], YSI_g_sBlock[4], YSI_g_sBlock[5], YSI_g_sBlock[6], YSI_g_sBlock[7], YSI_g_sBlock[8], YSI_g_sBlock[9], YSI_g_sBlock[10], YSI_g_sBlock[11], YSI_g_sBlock[12]);

	// 'BM', 40 byte header, 1 plane, 24 bits, no compression.
	if (YSI_g_sBlock[3] != 40 || YSI_g_sBlock[6] != 0x00180001 || YSI_g_sBlock[7] != 0)
	{
		return false;
	}

	x = YSI_g_sBlock[4];
	y = YSI_g_sBlock[5];
	
	new size = YSI_g_sBlock[0] - sizeof (_YSI_g_sFileHeader) - sizeof (_YSI_g_sInfoHeader);

	P:5("Bitmap_ReadHeader: %d, %d, %d, %d", x, y, size, ceildiv(x * 3, 4) * 4 * y);

	if (size != ceildiv(x * 3, 4) * 4 * y)
	{
		// File is the wrong size.
		return false;
	}

	return true;
}

native YSI_FBlockRead(File: handle, &buffer, size) = fblockread;

static stock Bitmap_ReadBody(Bitmap:ctx, File:bmp)
{
	// Allocate the memory for the main input.  We don't need to use `CEILDIV`
	// here because the BMP file format body is always an exact multiple of 4.
	new
		y = Bitmap_Height(ctx),
		width = Bitmap_Width(ctx) * cellbytes,
		dest = _:ctx * cellbytes + y * width;
	#emit CONST.pri            YSI_gMallocMemory
	#emit LOAD.S.alt           dest
	#emit ADD
	#emit LOAD.S.alt           width
	#emit SUB
	#emit STOR.S.pri           dest
	
	// Write 4 pixels in to 3 blocks.
	
	// These ARE used, but only by virtue of being contiguous in memory.  They
	// are like an array, but with each index declared separately.  "p" for
	// "pixel".
	static p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, pA, pB;
	#pragma unused p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, pA, pB

	for (new w2 = dest + (width & ~(16 * cellbytes - 1)), w3 = dest + (width & ~(4 * cellbytes - 1)); y--; dest -= width * 2, w2 -= width, w3 -= width)
	{
		// Go through the array backwards (bottom to top).
		for ( ; dest != w2; dest += 16 * cellbytes)
		{
			YSI_FBlockRead(bmp, p0, 16 * 3 / cellbytes);
			{
				// dest[0] = (cur = src[2]) | 0xFF;
				// Make colour 1.
				#emit LOAD.alt             pB
				#emit CONST.pri            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
				// Make colour 2.
				#emit SHL.C.alt            24
				#emit LOAD.pri             pA
				#emit SHR.C.pri            8
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
				// Make colour 3.
				#emit LOAD.alt             pA
				#emit SHL.C.alt            16
				#emit LOAD.pri             p9
				#emit SHR.C.pri            16
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[3] = (cur <<  8) | 0xFF;
				// Make colour 4.
				#emit LOAD.pri             p9
				#emit SHL.C.pri            8
				#emit OR
				#emit PUSH.pri

				// dest[0] = (cur = src[2]) | 0xFF;
				// Make colour 1.
				#emit LOAD.alt             p8
				#emit CONST.pri            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
				// Make colour 2.
				#emit SHL.C.alt            24
				#emit LOAD.pri             p7
				#emit SHR.C.pri            8
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
				// Make colour 3.
				#emit LOAD.alt             p7
				#emit SHL.C.alt            16
				#emit LOAD.pri             p6
				#emit SHR.C.pri            16
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[3] = (cur <<  8) | 0xFF;
				// Make colour 4.
				#emit LOAD.pri             p6
				#emit SHL.C.pri            8
				#emit OR
				#emit PUSH.pri

				// dest[0] = (cur = src[2]) | 0xFF;
				// Make colour 1.
				#emit LOAD.alt             p5
				#emit CONST.pri            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
				// Make colour 2.
				#emit SHL.C.alt            24
				#emit LOAD.pri             p4
				#emit SHR.C.pri            8
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
				// Make colour 3.
				#emit LOAD.alt             p4
				#emit SHL.C.alt            16
				#emit LOAD.pri             p3
				#emit SHR.C.pri            16
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[3] = (cur <<  8) | 0xFF;
				// Make colour 4.
				#emit LOAD.pri             p3
				#emit SHL.C.pri            8
				#emit OR
				#emit PUSH.pri

				// dest[0] = (cur = src[2]) | 0xFF;
				// Make colour 1.
				#emit LOAD.alt             p2
				#emit CONST.pri            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
				// Make colour 2.
				#emit SHL.C.alt            24
				#emit LOAD.pri             p1
				#emit SHR.C.pri            8
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
				// Make colour 3.
				#emit LOAD.alt             p1
				#emit SHL.C.alt            16
				#emit LOAD.pri             p0
				#emit SHR.C.pri            16
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[3] = (cur <<  8) | 0xFF;
				// Make colour 4.
				#emit LOAD.pri             p0
				#emit SHL.C.pri            8
				#emit OR
				#emit PUSH.pri

				// We now have all the colours pushed on to the stack.

				// Copy them to `dest` in one go.
				#emit LCTRL                4
				#emit LOAD.S.alt           dest
				#emit MOVS                 64

				// Remove them.
				#emit STACK                64
			}
		}
		for ( ; dest != w3; dest += 4 * cellbytes)
		{
			YSI_FBlockRead(bmp, p0, 4 * 3 / cellbytes);
			{
				// dest[0] = (cur = src[2]) | 0xFF;
				// Make colour 1.
				#emit LOAD.alt             p2
				#emit CONST.pri            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
				// Make colour 2.
				#emit SHL.C.alt            24
				#emit LOAD.pri             p1
				#emit SHR.C.pri            8
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
				// Make colour 3.
				#emit LOAD.alt             p1
				#emit SHL.C.alt            16
				#emit LOAD.pri             p0
				#emit SHR.C.pri            16
				#emit OR
				#emit CONST.alt            0xFF
				#emit OR
				#emit PUSH.pri

				// dest[3] = (cur <<  8) | 0xFF;
				// Make colour 4.
				#emit LOAD.pri             p0
				#emit SHL.C.pri            8
				#emit OR
				#emit PUSH.pri

				// We now have all the colours pushed on to the stack.

				// Copy them to `dest` in one go.
				#emit LCTRL                4
				#emit LOAD.S.alt           dest
				#emit MOVS                 16

				// Remove them.
				#emit STACK                16	
			}
		}
		switch (width & (4 * cellbytes - 1))
		{
			case 1 * cellbytes:
			{
				// Read 1.
				YSI_FBlockRead(bmp, p0, 1),
				AMX_Write(dest, (p0 << 8) | 0xFF),
				dest += 1 * cellbytes;
			}
			case 2 * cellbytes:
			{
				// Read 2.
				YSI_FBlockRead(bmp, p0, 2),
				AMX_Write(dest                , (p0  <<  8) | 0xFF),
				AMX_Write(dest + 1 * cellbytes, (p0 >>> 16) | (p1 << 16) | 0xFF),
				dest += 2 * cellbytes;
			}
			case 3 * cellbytes:
			{
				// Write 3, pad 3.
				YSI_FBlockRead(bmp, p0, 3),
				AMX_Write(dest                , (p0  <<  8) | 0xFF),
				AMX_Write(dest + 1 * cellbytes, (p0 >>> 16) | (p1 << 16) | 0xFF),
				AMX_Write(dest + 2 * cellbytes, (p1 >>>  8) | (p2 << 24) | 0xFF),
				dest += 3 * cellbytes;
			}
		}
	}
}

stock bool:Bitmap_Read(&Bitmap:ctx, const file[])
{
	if (!fexist(file))
	{
		return false;
	}
	new
		File:bmp = fopen(file, io_read);
	if (!bmp)
	{
		return false;
	}
	new x, y;
	if (!Bitmap_ReadHeader(bmp, x, y))
	{
		return false;
	}
	ctx = Bitmap_Create(x, y);
	Bitmap_ReadBody(ctx, bmp);
	fclose(bmp);
	return true;
}

