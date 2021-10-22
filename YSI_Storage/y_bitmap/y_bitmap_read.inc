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

	P:5("Bitmap_ReadHeader: %d, %d, %d, %d", x, y, YSI_g_sBlock[0], ceildiv(x * 3, 4) * 4 * y + sizeof (_YSI_g_sFileHeader) + sizeof (_YSI_g_sInfoHeader));

	if (YSI_g_sBlock[0] != ceildiv(x * 3, 4) * 4 * y + sizeof (_YSI_g_sFileHeader) + sizeof (_YSI_g_sInfoHeader))
	{
		// File is the wrong size.
		return false;
	}

	return true;
}

static stock Bitmap_ReadBody(Bitmap:ctx, File:bmp)
{
	// Write 4 pixels in to 3 blocks.
	static
		sReadBlock[300];
	new
		width = Bitmap_Width(ctx);
	for (new y = Bitmap_Height(ctx); y--; )
	{
		// Go through the array backwards (bottom to top).
		new
			w2 = (width & ~0x3) * 3 / cellbytes,
			x = 0;
		while (w2)
		{
			//printf("i before: %d, %d", i, w2);
			new read = fblockread(bmp, sReadBlock, min(sizeof (sReadBlock), w2));
			w2 -= read;
			//printf("i after: %d, %d", i, w2);
			for (new i = 0; i != read; i += 3, x += 4)
			{
				//printf("i = %d, read = %d", i, read);
				//Bitmap_ReadBlock(bmp, sReadBlock, 12);
				//fblockread(bmp, sReadBlock, 3);
				Bitmap_WriteInt(ctx, x    , width, y, 0xFF | (sReadBlock[i] << 8)),
				Bitmap_WriteInt(ctx, x + 1, width, y, 0xFF | (sReadBlock[i + 1] << 16) | (sReadBlock[i] >>> 16)),
				Bitmap_WriteInt(ctx, x + 2, width, y, 0xFF | (sReadBlock[i + 2] << 24) | (sReadBlock[i + 1] >>> 8)),
				Bitmap_WriteInt(ctx, x + 3, width, y, 0xFF | sReadBlock[i + 2]);
			}
		}
		//return;
		switch (width & 0x03)
		{
			case 1:
			{
				// Read 1.
				fblockread(bmp, sReadBlock, 1);
				Bitmap_WriteInt(ctx, x    , width, y, 0xFF | (sReadBlock[0] << 8));
			}
			case 2:
			{
				// Read 2.
				fblockread(bmp, sReadBlock, 2);
				Bitmap_WriteInt(ctx, x    , width, y, 0xFF | (sReadBlock[0] << 8));
				Bitmap_WriteInt(ctx, x + 1, width, y, 0xFF | (sReadBlock[1] << 16) | (sReadBlock[0] >>> 16));
			}
			case 3:
			{
				// Write 3, pad 3.
				fblockread(bmp, sReadBlock, 3);
				Bitmap_WriteInt(ctx, x    , width, y, 0xFF | (sReadBlock[0] << 8));
				Bitmap_WriteInt(ctx, x + 1, width, y, 0xFF | (sReadBlock[1] << 16) | (sReadBlock[0] >>> 16));
				Bitmap_WriteInt(ctx, x + 2, width, y, 0xFF | (sReadBlock[2] << 24) | (sReadBlock[1] >>> 8));
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

