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
	Portions created by the Initial Developer are Copyright (c) 2022
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

static stock
	YSI_g_sBlock[13];

static stock bool:Bitmap_ReadHeader(File:bmp, &x, &y)
{
	if (YSI_FGetChar__(bmp, false) != 'B' || YSI_FGetChar__(bmp, false) != 'M')
	{
		return false;
	}

	// Load in the header.
	fblockread(bmp, YSI_g_sBlock);
	//new size = YSI_g_sBlock[0];
	Debug_Print5("Bitmap_ReadHeader: %08x %08x %08x", YSI_g_sBlock[0], YSI_g_sBlock[1], YSI_g_sBlock[2]);
	Debug_Print5("Bitmap_ReadHeader: %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x", YSI_g_sBlock[3], YSI_g_sBlock[4], YSI_g_sBlock[5], YSI_g_sBlock[6], YSI_g_sBlock[7], YSI_g_sBlock[8], YSI_g_sBlock[9], YSI_g_sBlock[10], YSI_g_sBlock[11], YSI_g_sBlock[12]);

	// 'BM', 40 byte header, 1 plane, 24 bits, no compression.
	if (YSI_g_sBlock[3] != 40 || YSI_g_sBlock[6] != 0x00180001 || YSI_g_sBlock[7] != 0)
	{
		return false;
	}

	x = YSI_g_sBlock[4],
	y = YSI_g_sBlock[5];

	Debug_Print5("Bitmap_ReadHeader: %d, %d, %d, %d", x, y, YSI_g_sBlock[0] - sizeof (_YSI_g_sFileHeader) - sizeof (_YSI_g_sInfoHeader), ceildiv(x * 3, 4) * 4 * y);

	if (YSI_g_sBlock[0] - sizeof (_YSI_g_sFileHeader) - sizeof (_YSI_g_sInfoHeader) != ceildiv(x * 3, 4) * 4 * y)
	{
		// File is the wrong size.
		return false;
	}

	return true;
}

native Bitmap_FBlockReadAddr(File:file, addr, size) = fblockread;
native Bitmap_FBlockReadRef(File:file, &ref, size) = fblockread;

#define BITMAP_TO_32(%0) ((%0) * 4)
#define BITMAP_TO_24(%0) ((%0) * 3) // * 3 / BITMAP_TO_32(4), cancels.

static stock bool:Bitmap_ReadBody(Bitmap:ctx, File:bmp)
{
	// Allocate the memory for the main input.  We don't need to use `CEILDIV`
	// here because the BMP file format body is always an exact multiple of 4.
	new
		width = Bitmap_Width(ctx) << __cell_shift,
		size = ceildiv(width * 3, 4 * cellbytes),
		Alloc:input = malloc(size);
	if (!input)
	{
		Debug_Error("Bitmap_Read: Could not allocate line read buffer");
		return false;
	}

	new
		y = Bitmap_Height(ctx),
		dest = (_:ctx << __cell_shift) + y * width;
	#emit CONST.pri            YSI_gMallocMemory
	#emit LOAD.S.alt           dest
	#emit ADD
	#emit LOAD.S.alt           width
	#emit SUB
	#emit STOR.S.pri           dest

	new
		w2 = dest + (width & ~(BITMAP_TO_32(32) - 1)),
		w3 = dest + (width & ~(BITMAP_TO_32(4) - 1));

	while (y--)
	{
		// After loading the data we offset the `src` by -1 so we can load the
		// first 3 bytes as the MSB (making the one byte before the array the
		// LSB, which we ignore).  This is always safe because `malloc`
		// allocated arrays are preceeded by their size (in hidden data) so
		// there can be no OOB access reading one byte before the start of the
		// data of interest.
		#emit CONST.pri            YSI_gMallocMemory
		#emit LOAD.S.pri           input
		#emit SHL.C.pri            __cell_shift
		#emit ADD
		#emit STOR.S.pri           ctx
		Bitmap_FBlockReadAddr(bmp, _:ctx--, size);

		// Go through the array backwards (bottom to top).
		while (dest != w2)
		{
			const cells0 = 32 * cellbytes;
			const cells1 = 24 * cellbytes;
			#emit CONST.alt            0xFF

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                93
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                90
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                87
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                84
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                81
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                78
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                75
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                72
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                69
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                66
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                63
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                60
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                57
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                54
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                51
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                48
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                45
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                42
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                39
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                36
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                33
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                30
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                27
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                24
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                21
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                18
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                15
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                12
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                9
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                6
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                3
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LREF.S.pri           ctx
			#emit OR
			#emit PUSH.pri

			// We now have all the colours pushed on to the stack.

			// Copy them to `dest` in one go.
			#emit LCTRL                __stk
			#emit LOAD.S.alt           dest
			#emit MOVS                 cells0
			#emit CONST.pri            cells0
			#emit ADD
			#emit STOR.S.pri           dest

			// Remove them.
			#emit STACK                cells0

			#emit LOAD.S.pri           ctx
			#emit ADD.C                cells1
			#emit STOR.S.pri           ctx
		}
		while (dest != w3)
		{
			#emit CONST.alt            0xFF

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                9
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                6
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LOAD.S.pri           ctx
			#emit ADD.C                3
			#emit LOAD.I
			#emit OR
			#emit PUSH.pri

			// Load the next value.
			#emit LREF.S.pri           ctx
			#emit OR
			#emit PUSH.pri

			// We now have all the colours pushed on to the stack.

			// Copy them to `dest` in one go.
			#emit LCTRL                __stk
			#emit LOAD.S.alt           dest
			#emit MOVS                 __4_cells
			#emit CONST.pri            __4_cells
			#emit ADD
			#emit STOR.S.pri           dest

			// Remove them.
			#emit STACK                __4_cells

			#emit LOAD.S.pri           ctx
			#emit ADD.C                __3_cells
			#emit STOR.S.pri           ctx
		}
		switch (width & (BITMAP_TO_32(4) - 1))
		{
			case 1 * cellbytes:
			{
				#emit CONST.alt            0xFF

				// Load the next value.
				#emit LREF.S.pri           ctx
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest
			}
			case 2 * cellbytes:
			{
				#emit CONST.alt            0xFF

				// Load the next value.
				#emit LREF.S.pri           ctx
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest

				// Load the next value.
				#emit LOAD.S.pri           ctx
				#emit ADD.C                3
				#emit LOAD.I
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest
			}
			case 3 * cellbytes:
			{
				#emit CONST.alt            0xFF

				// Load the next value.
				#emit LREF.S.pri           ctx
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest

				// Load the next value.
				#emit LOAD.S.pri           ctx
				#emit ADD.C                3
				#emit LOAD.I
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest

				// Load the next value.
				#emit LOAD.S.pri           ctx
				#emit ADD.C                6
				#emit LOAD.I
				#emit OR
				#emit SREF.S.pri           dest

				#emit LOAD.S.pri           dest
				#emit ADD.C                4
				#emit STOR.S.pri           dest
			}
		}
		{}

		#emit LOAD.S.alt           width

		#emit LOAD.S.pri           w2
		#emit SUB
		#emit STOR.S.pri           w2

		#emit LOAD.S.pri           w3
		#emit SUB
		#emit STOR.S.pri           w3

		#emit LOAD.S.pri           dest
		#emit SUB
		#emit SUB
		#emit STOR.S.pri           dest
	}
	{}

	return bool:free(input);
}

#define Bitmap_FBlockReadAddr
#define Bitmap_FBlockReadRef

#undef BITMAP_TO_32
#undef BITMAP_TO_24

stock bool:Bitmap_Read(&Bitmap:ctx, const file[])
{
	if (!fexist(file))
	{
		return bool:(ctx = Bitmap:0);
	}
	new
		File:bmp = fopen(file, io_read);
	if (!bmp)
	{
		return bool:(ctx = Bitmap:0);
	}
	new x, y;
	if (!Bitmap_ReadHeader(bmp, x, y))
	{
		return bool:(ctx = Bitmap:0);
	}
	ctx = Bitmap_Create(x, y);
	if (!Bitmap_ReadBody(ctx, bmp))
	{
		Bitmap_Destroy(ctx);
		return bool:(ctx = Bitmap:0);
	}
	fclose(bmp);
	return true;
}

