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

Test:y_cell_ReverseBits0()
{
	ASSERT(Cell_ReverseBits(0) == 0x00000000);
	ASSERT(Cell_ReverseBits(1) == 0x80000000);
	ASSERT(Cell_ReverseBits(2) == 0x40000000);
	ASSERT(Cell_ReverseBits(3) == 0xC0000000);
	ASSERT(Cell_ReverseBits(4) == 0x20000000);
	ASSERT(Cell_ReverseBits(0b01010101010) == 0b01010101010000000000000000000000);
	ASSERT(Cell_ReverseBits(0b1111000001111000011) == 0b11000011110000011110000000000000);
}

Test:y_cell_ExpandCompress()
{
	new o, x, m, n;
	//printf("1");
	o = 0b11110000101001011100001100001111;
	m = 0b01010000000000000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000000000000011);
	//PRINT(n);
	//printf("2");
	o = 0b11110000101001011100001100001111;
	m = 0b01010101010100000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000000000110000);
	//PRINT(n);
	//printf("3");
	o = 0b11110000101001011100001100001111;
	m = 0b00111100000000000000000000000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000000000001100);
	//PRINT(n);
	//printf("4");
	o = 0b11110000101001011100001100001111;
	m = 0b00000000000000000000111111111111;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000001100001111);
	//PRINT(n);
	//printf("5");
	o = 0b11110000101001011100001100001111;
	m = 0b00000000000000000000111111000000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000000000001100);
	//PRINT(n);
	//printf("6");
	o = 0b11110000101001011100001100001111;
	m = 0b00000110000000100001100001100000;
	//PRINT(x);
	x = Cell_CompressRight(o, m);
	n = Cell_ExpandLeft(x, m);
	ASSERT(o & m == n);
	ASSERT(x == 0b00000000000000000000000000000000);
	//PRINT(n);
}

// Test:y_cell_ReverseBits1()
// {
	// for (new i = 0; i != 1000000; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000, k = 1; j; j >>>= 1, k <<= 1)
		// {
			// if (i & j) count |= k;
		// }
		// if (Cell_ReverseBits(i) != count)
		// {
			// ASSERT(Cell_ReverseBits(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseBits2()
// {
	// for (new i = 1000000000; i != 1000123000; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000, k = 1; j; j >>>= 1, k <<= 1)
		// {
			// if (i & j) count |= k;
		// }
		// if (Cell_ReverseBits(i) != count)
		// {
			// ASSERT(Cell_ReverseBits(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseBits3()
// {
	// for (new i = -999888; i != 0; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000, k = 1; j; j >>>= 1, k <<= 1)
		// {
			// if (i & j) count |= k;
		// }
		// if (Cell_ReverseBits(i) != count)
		// {
			// ASSERT(Cell_ReverseBits(i) == count);
			// break;
		// }
	// }
// }

Test:y_cell_ReverseNibbles0()
{
	ASSERT(Cell_ReverseNibbles(0) == 0);
	ASSERT(Cell_ReverseNibbles(1) == 0x10000000);
	ASSERT(Cell_ReverseNibbles(2) == 0x20000000);
	ASSERT(Cell_ReverseNibbles(3) == 0x30000000);
	ASSERT(Cell_ReverseNibbles(4) == 0x40000000);
	ASSERT(Cell_ReverseNibbles(0b1010101010) == 0b10101010001000000000000000000000);
	ASSERT(Cell_ReverseNibbles(0b1111000001111000011) == 0b00111100001110000111000000000000);
}

// Test:y_cell_ReverseNibbles1()
// {
	// for (new i = 0; i != 1000000; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 8; ++j)
		// {
			// count <<= 4;
			// count |= k & 0x0F;
			// k >>>= 4;
		// }
		// if (Cell_ReverseNibbles(i) != count)
		// {
			// ASSERT(Cell_ReverseNibbles(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseNibbles2()
// {
	// for (new i = 1000000000; i != 1000123000; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 8; ++j)
		// {
			// count <<= 4;
			// count |= k & 0x0F;
			// k >>>= 4;
		// }
		// if (Cell_ReverseNibbles(i) != count)
		// {
			// ASSERT(Cell_ReverseNibbles(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseNibbles3()
// {
	// for (new i = -999888; i != 0; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 8; ++j)
		// {
			// count <<= 4;
			// count |= k & 0x0F;
			// k >>>= 4;
		// }
		// if (Cell_ReverseNibbles(i) != count)
		// {
			// ASSERT(Cell_ReverseNibbles(i) == count);
			// break;
		// }
	// }
// }

Test:y_cell_ReverseBytes0()
{
	ASSERT(Cell_ReverseBytes(0) == 0);
	ASSERT(Cell_ReverseBytes(1) == 0x01000000);
	ASSERT(Cell_ReverseBytes(2) == 0x02000000);
	ASSERT(Cell_ReverseBytes(3) == 0x03000000);
	ASSERT(Cell_ReverseBytes(4) == 0x04000000);
	ASSERT(Cell_ReverseBytes(0b1010101010) == 0b10101010000000100000000000000000);
	ASSERT(Cell_ReverseBytes(0b1111000001111000011) == 0b11000011100000110000011100000000);
}

// Test:y_cell_ReverseBytes1()
// {
	// for (new i = 0; i != 1000000; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 4; ++j)
		// {
			// count <<= 8;
			// count |= k & 0xFF;
			// k >>>= 8;
		// }
		// if (Cell_ReverseBytes(i) != count)
		// {
			// ASSERT(Cell_ReverseBytes(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseBytes2()
// {
	// for (new i = 1000000000; i != 1000123000; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 4; ++j)
		// {
			// count <<= 8;
			// count |= k & 0xFF;
			// k >>>= 8;
		// }
		// if (Cell_ReverseBytes(i) != count)
		// {
			// ASSERT(Cell_ReverseBytes(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_ReverseBytes3()
// {
	// for (new i = -999888; i != 0; ++i)
	// {
		// new
			// count = 0,
			// k = i;
		// for (new j = 0; j != 4; ++j)
		// {
			// count <<= 8;
			// count |= k & 0xFF;
			// k >>>= 8;
		// }
		// if (Cell_ReverseBytes(i) != count)
		// {
			// ASSERT(Cell_ReverseBytes(i) == count);
			// break;
		// }
	// }
// }

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
	return 0;
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
	return 0;
}

Test:y_cell_CountBits0()
{
	ASSERT(y_cell_CountBits_v4(0) == 0);
	ASSERT(y_cell_CountBits_v4(1) == 1);
	ASSERT(y_cell_CountBits_v4(2) == 1);
	ASSERT(y_cell_CountBits_v4(3) == 2);
	ASSERT(y_cell_CountBits_v4(4) == 1);
	ASSERT(y_cell_CountBits_v4(0b1010101010) == 5);
	ASSERT(y_cell_CountBits_v4(0b1111000001111000011) == 10);
#if 0
	new
		t0, t1, t2, t3, t4;
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

// Test:y_cell_CountBits1()
// {
	// for (new i = 0; i != 1000000; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000; j; j >>>= 1)
		// {
			// if (i & j) ++count;
		// }
		// if (y_cell_CountBits_v4(i) != count)
		// {
			// ASSERT(y_cell_CountBits_v4(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_CountBits2()
// {
	// for (new i = 1000000000; i != 1000123000; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000; j; j >>>= 1)
		// {
			// if (i & j) ++count;
		// }
		// if (y_cell_CountBits_v4(i) != count)
		// {
			// ASSERT(y_cell_CountBits_v4(i) == count);
			// break;
		// }
	// }
// }

// Test:y_cell_CountBits3()
// {
	// for (new i = -999888; i != 0; ++i)
	// {
		// new
			// count = 0;
		// for (new j = 0x80000000; j; j >>>= 1)
		// {
			// if (i & j) ++count;
		// }
		// if (y_cell_CountBits_v4(i) != count)
		// {
			// ASSERT(y_cell_CountBits_v4(i) == count);
			// break;
		// }
	// }
// }

Test:y_cell_GetLowestComponent()
{
	ASSERT(Cell_GetLowestComponent(0) == 0);
	ASSERT(Cell_GetLowestComponent(1) == 1);
	ASSERT(Cell_GetLowestComponent(2) == 2);
	ASSERT(Cell_GetLowestComponent(6) == 2);
	ASSERT(Cell_GetLowestComponent(0x110) == 0x10);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i,
			l = k;
		ASSERT(Cell_GetLowestComponent(l) == k);
		l |= 2 << i;
		ASSERT(Cell_GetLowestComponent(l) == k);
		l |= 4 << i;
		ASSERT(Cell_GetLowestComponent(l) == k);
		l |= 8 << i;
		ASSERT(Cell_GetLowestComponent(l) == k);
	}
}

Test:y_cell_GetLowestBit()
{
	ASSERT(Cell_GetLowestBit(0) == 0);
	ASSERT(Cell_GetLowestBit(1) == 0);
	ASSERT(Cell_GetLowestBit(0x800) == 11);
	ASSERT(Cell_GetLowestBit(0x111) == 0);
	ASSERT(Cell_GetLowestBit(6) == 1);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i;
		ASSERT(Cell_GetLowestBit(k) == i);
		k |= 2 << i;
		ASSERT(Cell_GetLowestBit(k) == i);
		k |= 4 << i;
		ASSERT(Cell_GetLowestBit(k) == i);
		k |= 8 << i;
		ASSERT(Cell_GetLowestBit(k) == i);
	}
}

Test:y_cell_GetLowestBitEx()
{
	ASSERT(Cell_GetLowestBitEx(0) == 0);
	ASSERT(Cell_GetLowestBitEx(1) == 1);
	ASSERT(Cell_GetLowestBitEx(0x800) == 12);
	ASSERT(Cell_GetLowestBitEx(0x111) == 1);
	ASSERT(Cell_GetLowestBitEx(6) == 2);
	for (new i = 0; i != 32; ++i)
	{
		new
			k = 1 << i;
		ASSERT(Cell_GetLowestBitEx(k) == i + 1);
		k |= 2 << i;
		ASSERT(Cell_GetLowestBitEx(k) == i + 1);
		k |= 4 << i;
		ASSERT(Cell_GetLowestBitEx(k) == i + 1);
		k |= 8 << i;
		ASSERT(Cell_GetLowestBitEx(k) == i + 1);
	}
}

