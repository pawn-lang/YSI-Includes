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

static stock Bitmap_ReadHeader(File:bmp, &x, &y)
{
	if (fgetchar(bmp, 0, false) != 'B' || fgetchar(bmp, 0, false) != 'M')
	{
		return 0;
	}

	// Load in the header.
	fblockread(bmp, YSI_g_sBlock);
	//new size = YSI_g_sBlock[0];
	P:5("Bitmap_ReadHeader: %08x %08x %08x", YSI_g_sBlock[0], YSI_g_sBlock[1], YSI_g_sBlock[2]);
	P:5("Bitmap_ReadHeader: %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x", YSI_g_sBlock[3], YSI_g_sBlock[4], YSI_g_sBlock[5], YSI_g_sBlock[6], YSI_g_sBlock[7], YSI_g_sBlock[8], YSI_g_sBlock[9], YSI_g_sBlock[10], YSI_g_sBlock[11], YSI_g_sBlock[12]);

	// 'BM', 40 byte header, 1 plane, 24 bits, no compression.
	if (YSI_g_sBlock[3] != 40 || YSI_g_sBlock[6] != 0x00180001 || YSI_g_sBlock[7] != 0)
	{
		return 0;
	}

	x = YSI_g_sBlock[4];
	y = YSI_g_sBlock[5];
	
	new size = YSI_g_sBlock[0] - sizeof (_YSI_g_sFileHeader) - sizeof (_YSI_g_sInfoHeader);

	P:5("Bitmap_ReadHeader: %d, %d, %d, %d", x, y, size, ceildiv(x * 3, 4) * 4 * y);

	if (size != ceildiv(x * 3, 4) * 4 * y)
	{
		// File is the wrong size.
		return 0;
	}

	return size;
}

static stock Bitmap_StoreBlock64(dest, const src[])
{
	// dest[0] = (cur = src[2]) | 0xFF;
	// Load the next value.
	#emit LOAD.S.alt           src
	#emit CONST.pri            11
	#emit LIDX
	#emit PUSH.pri

	// Make colour 1.
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            10
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 2.
	#emit SHL.C.alt            24
	#emit SHR.C.pri            8
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            9
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 3.
	#emit SHL.C.alt            16
	#emit SHR.C.pri            16
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[3] = (cur <<  8) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit POP.pri

	// Make colour 4.
	#emit SHL.C.pri            8
	//#emit CONST.alt            0xFF
	#emit OR
	#emit PUSH.pri

	// dest[0] = (cur = src[2]) | 0xFF;
	// Load the next value.
	#emit LOAD.S.alt           src
	#emit CONST.pri            8
	#emit LIDX
	#emit PUSH.pri

	// Make colour 1.
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            7
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 2.
	#emit SHL.C.alt            24
	#emit SHR.C.pri            8
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            6
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 3.
	#emit SHL.C.alt            16
	#emit SHR.C.pri            16
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[3] = (cur <<  8) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit POP.pri

	// Make colour 4.
	#emit SHL.C.pri            8
	//#emit CONST.alt            0xFF
	#emit OR
	#emit PUSH.pri

	// dest[0] = (cur = src[2]) | 0xFF;
	// Load the next value.
	#emit LOAD.S.alt           src
	#emit CONST.pri            5
	#emit LIDX
	#emit PUSH.pri

	// Make colour 1.
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            4
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 2.
	#emit SHL.C.alt            24
	#emit SHR.C.pri            8
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            3
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 3.
	#emit SHL.C.alt            16
	#emit SHR.C.pri            16
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[3] = (cur <<  8) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit POP.pri

	// Make colour 4.
	#emit SHL.C.pri            8
	//#emit CONST.alt            0xFF
	#emit OR
	#emit PUSH.pri

	// dest[0] = (cur = src[2]) | 0xFF;
	// Load the next value.
	#emit LOAD.S.alt           src
	#emit CONST.pri            2
	#emit LIDX
	#emit PUSH.pri

	// Make colour 1.
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            1
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 2.
	#emit SHL.C.alt            24
	#emit SHR.C.pri            8
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit LOAD.S.alt           src
	//#emit CONST.pri            3
	//#emit LIDX
	//#emit POP.alt
	//#emit PUSH.pri
	#emit LREF.S.alt           src
	#emit PUSH.alt

	// Make colour 3.
	#emit SHL.C.pri            16
	#emit SHR.C.alt            16
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[3] = (cur <<  8) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit POP.pri

	// Make colour 4.
	#emit SHL.C.pri            8
	//#emit CONST.alt            0xFF
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

static stock Bitmap_StoreBlock16(dest, const src[])
{
	// dest[0] = (cur = src[2]) | 0xFF;
	// Load the next value.
	#emit LOAD.S.alt           src
	#emit CONST.pri            2
	#emit LIDX
	#emit PUSH.pri

	// Make colour 1.
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[1] = (cur << 24) | ((cur = src[1]) >>>  8) | 0xFF;
	// Load the next value.
	#emit PUSH.pri
	#emit LOAD.S.alt           src
	#emit CONST.pri            1
	#emit LIDX
	#emit POP.alt
	#emit PUSH.pri

	// Make colour 2.
	#emit SHL.C.alt            24
	#emit SHR.C.pri            8
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[2] = (cur << 16) | ((cur = src[0]) >>> 16) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit LOAD.S.alt           src
	//#emit CONST.pri            3
	//#emit LIDX
	//#emit POP.alt
	//#emit PUSH.pri
	#emit LREF.S.alt           src
	#emit PUSH.alt

	// Make colour 3.
	#emit SHL.C.pri            16
	#emit SHR.C.alt            16
	#emit OR
	#emit CONST.alt            0xFF
	#emit OR
	#emit SWAP.pri

	// dest[3] = (cur <<  8) | 0xFF;
	// Load the next value.
	//#emit PUSH.pri
	//#emit POP.pri

	// Make colour 4.
	#emit SHL.C.pri            8
	//#emit CONST.alt            0xFF
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

static stock Bitmap_ReadBody(Bitmap:ctx, File:bmp, size)
{
	// Allocate the memory for the main input.  We don't need to use `CEILDIV`
	// here because the BMP file format body is always an exact multiple of 4.
	new
		Alloc:input = malloc(size / 4),
		y = Bitmap_Height(ctx),
		width = Bitmap_Width(ctx) * cellbytes,
		dst = _:ctx * cellbytes + y * width;
	#emit CONST.pri            YSI_gMallocMemory
	#emit LOAD.S.alt           dst
	#emit ADD
	#emit LOAD.S.alt           width
	#emit SUB
	#emit STOR.S.pri           dst
	if (input)
	{
		new
			src = _:input;
		fblockread(bmp, YSI_gMallocMemory[_:input], size);
		for (new w2 = dst + (width & ~(16 * cellbytes - 1)), w3 = dst + (width & ~(4 * cellbytes - 1)); y--; dst -= width * 2, w2 -= width, w3 -= width)
		{
			// Go through the array backwards (bottom to top).
			for ( ; dst != w2; dst += 16 * cellbytes, src += 12)
			{
				Bitmap_StoreBlock64(dst, YSI_gMallocMemory[src]);
			}
			for ( ; dst != w3; dst += 4 * cellbytes, src += 3)
			{
				Bitmap_StoreBlock16(dst, YSI_gMallocMemory[src]);
			}
			switch (width & (4 * cellbytes - 1))
			{
				case 1 * cellbytes:
				{
					// Read 1, skip 1.
					AMX_Write(dst, (YSI_gMallocMemory[src] << 8) | 0xFF),
					dst += 1 * cellbytes,
					src += 1;
				}
				case 2 * cellbytes:
				{
					// Read 2, skip 2.
					AMX_Write(dst    , (YSI_gMallocMemory[src]  <<  8) | 0xFF),
					AMX_Write(dst + 1, (YSI_gMallocMemory[src] >>> 16) | (YSI_gMallocMemory[src + 1] << 16) | 0xFF),
					dst += 2 * cellbytes,
					src += 2;
				}
				case 3 * cellbytes:
				{
					// Read 3, skip 3.
					AMX_Write(dst    , (YSI_gMallocMemory[src]  <<  8) | 0xFF),
					AMX_Write(dst + 1, (YSI_gMallocMemory[src] >>> 16) | (YSI_gMallocMemory[src + 1] << 16) | 0xFF),
					AMX_Write(dst + 2, (YSI_gMallocMemory[src + 1] >>>  8) | (YSI_gMallocMemory[src + 2] << 24) | 0xFF),
					dst += 3 * cellbytes,
					src += 3;
				}
			}
		}
		free(input);
	}
	else
	{
		// Write 4 pixels in to 3 blocks.
		static
			sReadBlock[16 * 3 / cellbytes];
		P:W("Could not allocate space to load bitmap, using fallback code");
		for (new w2 = dst + (width & ~(16 * cellbytes - 1)), w3 = dst + (width & ~(4 * cellbytes - 1)); y--; dst -= width * 2, w2 -= width, w3 -= width)
		{
			// Go through the array backwards (bottom to top).
			for ( ; dst != w2; dst += 16 * cellbytes)
			{
				fblockread(bmp, sReadBlock, 16 * 3 / cellbytes),
				Bitmap_StoreBlock64(dst, sReadBlock);
			}
			for ( ; dst != w3; dst += 4 * cellbytes)
			{
				fblockread(bmp, sReadBlock, 4 * 3 / cellbytes),
				Bitmap_StoreBlock16(dst, sReadBlock);
			}
			switch (width & (4 * cellbytes - 1))
			{
				case 1 * cellbytes:
				{
					// Read 1.
					fblockread(bmp, sReadBlock, 1),
					AMX_Write(dst, (sReadBlock[0] << 8) | 0xFF),
					dst += 1 * cellbytes;
				}
				case 2 * cellbytes:
				{
					// Read 2.
					fblockread(bmp, sReadBlock, 2),
					AMX_Write(dst                , (sReadBlock[0]  <<  8) | 0xFF),
					AMX_Write(dst + 1 * cellbytes, (sReadBlock[0] >>> 16) | (sReadBlock[1] << 16) | 0xFF),
					dst += 2 * cellbytes;
				}
				case 3 * cellbytes:
				{
					// Write 3, pad 3.
					fblockread(bmp, sReadBlock, 3),
					AMX_Write(dst                , (sReadBlock[0]  <<  8) | 0xFF),
					AMX_Write(dst + 1 * cellbytes, (sReadBlock[0] >>> 16) | (sReadBlock[1] << 16) | 0xFF),
					AMX_Write(dst + 2 * cellbytes, (sReadBlock[1] >>>  8) | (sReadBlock[2] << 24) | 0xFF),
					dst += 3 * cellbytes;
				}
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
	new x, y, size = Bitmap_ReadHeader(bmp, x, y);
	if (!size)
	{
		return false;
	}
	ctx = Bitmap_Create(x, y);
	Bitmap_ReadBody(ctx, bmp, size);
	fclose(bmp);
	return true;
}

