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

//@test(.group = "y_cell", .run = false) y_cell()
@test(.group = "y_cell", .run = false) y_cell()
{
	#if cellbits == 32
		new masks[5];
	#endif
	#if cellbits == 64
		new masks[6];
	#endif
	Cell_ReverseBits(0);
	Cell_ReverseNibbles(0);
	Cell_ReverseBytes(0);
	Cell_CountBits(0);
	Cell_GetLowestBit(0);
	Cell_GetLowestBitEx(0);
	Cell_CountBlanks(0);
	Cell_GetLowestBlank(0);
	Cell_GetLowestBlankEx(0);
	Cell_GetLowestComponent(0);
	Cell_GetLowestEmpty(0);
	Cell_CompressRightPrecomputed(0, 0, masks);
	Cell_ExpandLeftPrecomputed(0, 0, masks);
	Cell_PrecomputeMaskPermutation(0);
	Cell_CompressRight(0, 0);
	Cell_ExpandLeft(0, 0);
}

@test(.group = "y_cell") y_cell_ReverseBits0()
{
	#if cellbits == 32
		ASSERT_EQ(Cell_ReverseBits(0), 0x00000000);
		ASSERT_EQ(Cell_ReverseBits(1), 0x80000000);
		ASSERT_EQ(Cell_ReverseBits(2), 0x40000000);
		ASSERT_EQ(Cell_ReverseBits(3), 0xC0000000);
		ASSERT_EQ(Cell_ReverseBits(4), 0x20000000);
		ASSERT_EQ(Cell_ReverseBits(0b01010101010), 0b01010101010000000000000000000000);
		ASSERT_EQ(Cell_ReverseBits(0b1111000001111000011), 0b11000011110000011110000000000000);
	#else
		ASSERT_EQ(Cell_ReverseBits(0), 0x0000000000000000);
		ASSERT_EQ(Cell_ReverseBits(1), 0x8000000000000000);
		ASSERT_EQ(Cell_ReverseBits(2), 0x4000000000000000);
		ASSERT_EQ(Cell_ReverseBits(3), 0xC000000000000000);
		ASSERT_EQ(Cell_ReverseBits(4), 0x2000000000000000);
		ASSERT_EQ(Cell_ReverseBits(0b01010101010), 0b0101010101000000000000000000000000000000000000000000000000000000);
		ASSERT_EQ(Cell_ReverseBits(0b1111000001111000011), 0b1100001111000001111000000000000000000000000000000000000000000000);
	#endif
}

@test(.group = "y_cell") y_cell_ExpandCompress()
{
	new o = 0, x = 0, m = 0, n = 0;
	//print("1");
	o = 0b11110000101001011100001100001111;
	m = 0b01010000000000000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000000000000011);
	//PRINT(n);
	//print("2");
	o = 0b11110000101001011100001100001111;
	m = 0b01010101010100000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000000000110000);
	//PRINT(n);
	//print("3");
	o = 0b11110000101001011100001100001111;
	m = 0b00111100000000000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000000000001100);
	//PRINT(n);
	//print("4");
	o = 0b11110000101001011100001100001111;
	m = 0b00000000000000000000111111111111;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000001100001111);
	//PRINT(n);
	//print("5");
	o = 0b11110000101001011100001100001111;
	m = 0b00000000000000000000111111000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000000000001100);
	//PRINT(n);
	//print("6");
	o = 0b11110000101001011100001100001111;
	m = 0b00000110000000100001100001100000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT_EQ(o & m, n);
	ASSERT_EQ(x, 0b00000000000000000000000000000000);
	//PRINT(n);
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBits1()
{
	for (new i = 0; i != 1000000; ++i)
	{
		new
			count = 0;
		for (new j = cellmin, k = 1; j; j >>>= 1, k <<= 1)
		{
			if (i & j) count |= k;
		}
		if (Cell_ReverseBits(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBits2()
{
	for (new i = 1000000000; i != 1000123000; ++i)
	{
		new
			count = 0;
		for (new j = cellmin, k = 1; j; j >>>= 1, k <<= 1)
		{
			if (i & j) count |= k;
		}
		if (Cell_ReverseBits(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBits3()
{
	for (new i = -999888; i != 0; ++i)
	{
		new
			count = 0;
		for (new j = cellmin, k = 1; j; j >>>= 1, k <<= 1)
		{
			if (i & j) count |= k;
		}
		if (Cell_ReverseBits(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell") y_cell_ReverseNibbles0()
{
	#if cellbits == 32
		ASSERT_ZE(Cell_ReverseNibbles(0));
		ASSERT_EQ(Cell_ReverseNibbles(1), 0x10000000);
		ASSERT_EQ(Cell_ReverseNibbles(2), 0x20000000);
		ASSERT_EQ(Cell_ReverseNibbles(3), 0x30000000);
		ASSERT_EQ(Cell_ReverseNibbles(4), 0x40000000);
		ASSERT_EQ(Cell_ReverseNibbles(0b1010101010), 0b10101010001000000000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(0b1111000001111000011), 0b00111100001110000111000000000000);
	#else
		ASSERT_ZE(Cell_ReverseNibbles(0));
		ASSERT_EQ(Cell_ReverseNibbles(1), 0x1000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(2), 0x2000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(3), 0x3000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(4), 0x4000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(0b1010101010), 0b1010101000100000000000000000000000000000000000000000000000000000);
		ASSERT_EQ(Cell_ReverseNibbles(0b1111000001111000011), 0b0011110000111000011100000000000000000000000000000000000000000000);
	#endif
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseNibbles1()
{
	for (new i = 0; i != 1000000; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != cellbytes * 2; ++j)
		{
			count <<= 4;
			count |= k & 0x0F;
			k >>>= 4;
		}
		if (Cell_ReverseNibbles(i) != count)
		{
			ASSERT_EQ(Cell_ReverseNibbles(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseNibbles2()
{
	for (new i = 1000000000; i != 1000123000; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != cellbytes * 2; ++j)
		{
			count <<= 4;
			count |= k & 0x0F;
			k >>>= 4;
		}
		if (Cell_ReverseNibbles(i) != count)
		{
			ASSERT_EQ(Cell_ReverseNibbles(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseNibbles3()
{
	for (new i = -999888; i != 0; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != cellbytes * 2; ++j)
		{
			count <<= 4;
			count |= k & 0x0F;
			k >>>= 4;
		}
		if (Cell_ReverseNibbles(i) != count)
		{
			ASSERT_EQ(Cell_ReverseNibbles(i), count);
			break;
		}
	}
}

@test(.group = "y_cell") y_cell_ReverseBytes0()
{
	#if cellbits == 32
		ASSERT_ZE(Cell_ReverseBytes(0));
		ASSERT_EQ(Cell_ReverseBytes(1), 0x01000000);
		ASSERT_EQ(Cell_ReverseBytes(2), 0x02000000);
		ASSERT_EQ(Cell_ReverseBytes(3), 0x03000000);
		ASSERT_EQ(Cell_ReverseBytes(4), 0x04000000);
		ASSERT_EQ(Cell_ReverseBytes(0b1010101010), 0b10101010000000100000000000000000);
		ASSERT_EQ(Cell_ReverseBytes(0b1111000001111000011), 0b11000011100000110000011100000000);
	#else
		ASSERT_ZE(Cell_ReverseBytes(0));
		ASSERT_EQ(Cell_ReverseBytes(1), 0x0100000000000000);
		ASSERT_EQ(Cell_ReverseBytes(2), 0x0200000000000000);
		ASSERT_EQ(Cell_ReverseBytes(3), 0x0300000000000000);
		ASSERT_EQ(Cell_ReverseBytes(4), 0x0400000000000000);
		ASSERT_EQ(Cell_ReverseBytes(0b1010101010), 0b1010101000000010000000000000000000000000000000000000000000000000);
		ASSERT_EQ(Cell_ReverseBytes(0b1111000001111000011), 0b1100001110000011000001110000000000000000000000000000000000000000);
	#endif
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBytes1()
{
	for (new i = 0; i != 1000000; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != cellbytes; ++j)
		{
			count <<= 8;
			count |= k & 0xFF;
			k >>>= 8;
		}
		if (Cell_ReverseBytes(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBytes(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBytes2()
{
	for (new i = 1000000000; i != 1000123000; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != cellbytes; ++j)
		{
			count <<= 8;
			count |= k & 0xFF;
			k >>>= 8;
		}
		if (Cell_ReverseBytes(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBytes(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_ReverseBytes3()
{
	for (new i = -999888; i != 0; ++i)
	{
		new
			count = 0,
			k = i;
		for (new j = 0; j != 4; ++j)
		{
			count <<= 8;
			count |= k & 0xFF;
			k >>>= 8;
		}
		if (Cell_ReverseBytes(i) != count)
		{
			ASSERT_EQ(Cell_ReverseBytes(i), count);
			break;
		}
	}
}

static stock y_cell_CountBits_v1(GLOBAL_TAG_TYPES:data)
{
	static const
		scCount[256] =
			{
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
			};
	return scCount[data >>> 24] + scCount[(data >>> 16) & 0xFF] + scCount[(data >>> 8) & 0xFF] + scCount[data & 0xFF];
}

static stock y_cell_CountBits_v2(GLOBAL_TAG_TYPES:data)
{
	data = data - ((data >>> 1) & 0x55555555);
	data = (data & 0x33333333) + ((data >>> 2) & 0x33333333);
	return ((data + (data >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
}

static stock y_cell_CountBits_v3(GLOBAL_TAG_TYPES:data)
{
	// This function is a perfect candidate for re-writing in pure assembly.
	// data = data - ((data >>> 1) & 0x55555555);
	#emit LOAD.S.pri           data // From this point on, just use registers!
	#emit PUSH.pri
	#emit SHR.C.pri            1
	#emit CONST.alt            0x55555555
	#emit AND                  // No "AND.C" annoyingly.
	#emit POP.alt
	#emit SUB.alt
	// data = (data & 0x33333333) + ((data >>> 2) & 0x33333333);
	#emit PUSH.pri
	#emit SHR.C.pri            2
	#emit CONST.alt            0x33333333
	#emit AND
	#emit SWAP.pri             // Put the second half of the code on the stack.
	#emit AND                  // "alt" is already the correct value.
	#emit POP.alt
	#emit ADD
	// return ((data + (data >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
	#emit MOVE.alt
	#emit SHR.C.pri            4
	#emit ADD
	#emit CONST.alt            0xF0F0F0F
	#emit AND
	#emit SMUL.C               0x1010101
	#emit SHR.C.pri            24
	#emit RETN
	__pragma("naked");
}

static stock y_cell_CountBits_v4(GLOBAL_TAG_TYPES:data)
{
	static const
		scCount[256] =
			{
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
				4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
			};
	// return scCount[data >>> 24] + scCount[(data >>> 16) & 0xFF] + scCount[(data >>> 8) & 0xFF] + scCount[data & 0xFF];
	#emit CONST.alt            scCount // Get the address of the table.
	#emit ADDR.pri             data    // Get the address of the parameter.
	#emit PUSH.pri
	
	// Load the first value.
	#emit LODB.I               1
	#emit LIDX
	// Store the data.
	#emit SWAP.pri
	#emit PUSH.pri
	
	// Load the second value
	#emit ADD.C                1
	#emit LODB.I               1
	#emit LIDX
	// Store the data.
	#emit SWAP.pri
	#emit PUSH.pri
	
	// Load the third value
	#emit ADD.C                2
	#emit LODB.I               1
	#emit LIDX
	// Store the data.
	#emit SWAP.pri
	
	// Load the fourth value
	#emit ADD.C                3
	#emit LODB.I               1
	#emit LIDX
	
	// We now have a stack with three results, and a fourth in "pri".
	#emit POP.alt
	#emit ADD
	#emit POP.alt
	#emit ADD
	#emit POP.alt
	#emit ADD
	
	// Return.
	#emit RETN
	__pragma("naked");
}

@test(.group = "y_cell", .slow = true) y_cell_CountBits0()
{
	ASSERT_ZE(Cell_CountBits(0));
	ASSERT_EQ(Cell_CountBits(1), 1);
	ASSERT_EQ(Cell_CountBits(2), 1);
	ASSERT_EQ(Cell_CountBits(3), 2);
	ASSERT_EQ(Cell_CountBits(4), 1);
	ASSERT_EQ(Cell_CountBits(0b1010101010), 5);
	ASSERT_EQ(Cell_CountBits(0b1111000001111000011), 10);
#if 0
	new
		t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	t0 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		for (new j = 1; j < 100000000; j *= 3)
		{
			y_cell_CountBits_v1(j);
		}
	}
	t1 = GetTickCount();
	printf("Time 1: %d", t1 - t0);
	t1 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		for (new j = 1; j < 100000000; j *= 3)
		{
			y_cell_CountBits_v2(j);
		}
	}
	t2 = GetTickCount();
	printf("Time 2: %d", t2 - t1);
	t2 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		for (new j = 1; j < 100000000; j *= 3)
		{
			y_cell_CountBits_v3(j);
		}
	}
	t3 = GetTickCount();
	printf("Time 3: %d", t3 - t2);
	t3 = GetTickCount();
	for (new i = 0; i != 10000000; ++i)
	{
		for (new j = 1; j < 100000000; j *= 3)
		{
			y_cell_CountBits_v4(j);
		}
	}
	t4 = GetTickCount();
	printf("Time 4: %d", t4 - t3);
#endif
}

@test(.group = "y_cell", .slow = true) y_cell_CountBits1()
{
	for (new i = 0; i != 1000000; ++i)
	{
		new
			count = 0;
		for (new j = cellmin; j; j >>>= 1)
		{
			if (i & j) ++count;
		}
		if (Cell_CountBits(i) != count)
		{
			ASSERT_EQ(Cell_CountBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_CountBits2()
{
	for (new i = 1000000000; i != 1000123000; ++i)
	{
		new
			count = 0;
		for (new j = cellmin; j; j >>>= 1)
		{
			if (i & j) ++count;
		}
		if (Cell_CountBits(i) != count)
		{
			ASSERT_EQ(Cell_CountBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell", .slow = true) y_cell_CountBits3()
{
	for (new i = -999888; i != 0; ++i)
	{
		new
			count = 0;
		for (new j = cellmin; j; j >>>= 1)
		{
			if (i & j) ++count;
		}
		if (Cell_CountBits(i) != count)
		{
			ASSERT_EQ(Cell_CountBits(i), count);
			break;
		}
	}
}

@test(.group = "y_cell") y_cell_GetLowestComponent()
{
	ASSERT_ZE(Cell_GetLowestComponent(0));
	ASSERT_EQ(Cell_GetLowestComponent(1), 1);
	ASSERT_EQ(Cell_GetLowestComponent(2), 2);
	ASSERT_EQ(Cell_GetLowestComponent(6), 2);
	ASSERT_EQ(Cell_GetLowestComponent(0x110), 0x10);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i,
			l = k;
		ASSERT_EQ(Cell_GetLowestComponent(l), k);
		l |= 2 << i;
		ASSERT_EQ(Cell_GetLowestComponent(l), k);
		l |= 4 << i;
		ASSERT_EQ(Cell_GetLowestComponent(l), k);
		l |= 8 << i;
		ASSERT_EQ(Cell_GetLowestComponent(l), k);
	}
}

@test(.group = "y_cell") y_cell_GetLowestBit()
{
	ASSERT_ZE(Cell_GetLowestBit(0));
	ASSERT_ZE(Cell_GetLowestBit(1));
	ASSERT_EQ(Cell_GetLowestBit(0x800), 11);
	ASSERT_ZE(Cell_GetLowestBit(0x111));
	ASSERT_EQ(Cell_GetLowestBit(6), 1);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i;
		ASSERT_EQ(Cell_GetLowestBit(k), i);
		k |= 2 << i;
		ASSERT_EQ(Cell_GetLowestBit(k), i);
		k |= 4 << i;
		ASSERT_EQ(Cell_GetLowestBit(k), i);
		k |= 8 << i;
		ASSERT_EQ(Cell_GetLowestBit(k), i);
	}
}

@test(.group = "y_cell") y_cell_GetLowestBitEx()
{
	ASSERT_ZE(Cell_GetLowestBitEx(0));
	ASSERT_EQ(Cell_GetLowestBitEx(1), 1);
	ASSERT_EQ(Cell_GetLowestBitEx(0x800), 12);
	ASSERT_EQ(Cell_GetLowestBitEx(0x111), 1);
	ASSERT_EQ(Cell_GetLowestBitEx(6), 2);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i;
		ASSERT_EQ(Cell_GetLowestBitEx(k), i + 1);
		k |= 2 << i;
		ASSERT_EQ(Cell_GetLowestBitEx(k), i + 1);
		k |= 4 << i;
		ASSERT_EQ(Cell_GetLowestBitEx(k), i + 1);
		k |= 8 << i;
		ASSERT_EQ(Cell_GetLowestBitEx(k), i + 1);
	}
}

@test(.group = "y_cell") y_cell_HasZeroByte()
{
	ASSERT(Cell_HasZeroByte(0x00000000));
	ASSERT(Cell_HasZeroByte(0x00800000));
	ASSERT(Cell_HasZeroByte(0xFFFFFF00));
	ASSERT(Cell_HasZeroByte(0xFFFF00FF));
	ASSERT(Cell_HasZeroByte(0xFFFF0000));
	ASSERT(Cell_HasZeroByte(0xFF00FFFF));
	ASSERT(Cell_HasZeroByte(0x0000FFFF));
	ASSERT(Cell_HasZeroByte(0x00FFFFFF));
	ASSERT(!Cell_HasZeroByte(0x20202020));
	ASSERT(!Cell_HasZeroByte(0x55555555));
	ASSERT(!Cell_HasZeroByte(0xFFFFFFFF));
	ASSERT(!Cell_HasZeroByte(0x01010101));
	ASSERT(!Cell_HasZeroByte(0x01FFFFFF));
	ASSERT(!Cell_HasZeroByte(0xF00FFFFF));
}

@test(.group = "y_cell") y_cell_HasSpaceByte()
{
	ASSERT(Cell_HasSpaceByte(0x20202020));
	ASSERT(Cell_HasSpaceByte(0x20802020));
	ASSERT(Cell_HasSpaceByte(0xFFFFFF20));
	ASSERT(Cell_HasSpaceByte(0xFFFF20FF));
	ASSERT(Cell_HasSpaceByte(0xFFFF2020));
	ASSERT(Cell_HasSpaceByte(0xFF20FFFF));
	ASSERT(Cell_HasSpaceByte(0x2020FFFF));
	ASSERT(Cell_HasSpaceByte(0x20FFFFFF));
	ASSERT(!Cell_HasSpaceByte(0x00000000));
	ASSERT(!Cell_HasSpaceByte(0x55555555));
	ASSERT(!Cell_HasSpaceByte(0xFFFFFFFF));
	ASSERT(!Cell_HasSpaceByte(0x01010101));
	ASSERT(!Cell_HasSpaceByte(0x01FFFFFF));
	ASSERT(!Cell_HasSpaceByte(0xF20FFFFF));
}

