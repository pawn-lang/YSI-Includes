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

@test(.group = "y_bit") Bit_Bits()
{
	#if cellbits == 32
		ASSERT_EQ(Bit_Bits(5), 1);
		ASSERT_EQ(Bit_Bits(32), 1);
		ASSERT_EQ(Bit_Bits(33), 2);
		ASSERT_EQ(Bit_Bits(63), 2);
		ASSERT_EQ(Bit_Bits(64), 2);
		ASSERT_EQ(Bit_Bits(65), 3);
		ASSERT_EQ(Bit_Bits(1024), 32);
		ASSERT_EQ(Bit_Bits(1025), 33);
	#elseif cellbits == 64
		ASSERT_EQ(Bit_Bits(5), 1);
		ASSERT_EQ(Bit_Bits(32), 1);
		ASSERT_EQ(Bit_Bits(33), 1);
		ASSERT_EQ(Bit_Bits(63), 1);
		ASSERT_EQ(Bit_Bits(64), 1);
		ASSERT_EQ(Bit_Bits(65), 2);
		ASSERT_EQ(Bit_Bits(1024), 16);
		ASSERT_EQ(Bit_Bits(1025), 17);
	#else
		#error Unsupported `cellbits`.
	#endif
}

@test(.group = "y_bit") Bit_Set()
{
	new
		BitArray:bb<100>;
	#if cellbits == 32
		Bit_Set(bb, 10, true);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_ZE(_:bb[1]);
		Bit_Set(bb, 32, true);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 1);
		Bit_Let(bb, 99);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 1);
		ASSERT_EQ(_:bb[3], 8);
		Bit_Vet(bb, 99);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 1);
		ASSERT_ZE(_:bb[3]);
		Bit_Let(bb, 11);
		ASSERT_EQ(_:bb[0], 3 << 10);
		ASSERT_EQ(_:bb[1], 1);
		ASSERT_ZE(_:bb[3]);
		Bit_Vet(bb, 10);
		ASSERT_EQ(_:bb[0], 2 << 10);
		ASSERT_EQ(_:bb[1], 1);
		ASSERT_ZE(_:bb[3]);
		Bit_Vet(bb, 11);
		ASSERT_ZE(_:bb[0]);
	#elseif cellbits == 64
		Bit_Set(bb, 10, true);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_ZE(_:bb[1]);
		Bit_Set(bb, 64, true);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 1);
		Bit_Let(bb, 99);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 0x800000001);
		Bit_Vet(bb, 99);
		ASSERT_EQ(_:bb[0], 1 << 10);
		ASSERT_EQ(_:bb[1], 1);
		Bit_Let(bb, 11);
		ASSERT_EQ(_:bb[0], 3 << 10);
		ASSERT_EQ(_:bb[1], 1);
		Bit_Vet(bb, 10);
		ASSERT_EQ(_:bb[0], 2 << 10);
		ASSERT_EQ(_:bb[1], 1);
		Bit_Vet(bb, 11);
		ASSERT_ZE(_:bb[0]);
	#else
		#error Unsupported `cellbits`.
	#endif
}

@test(.group = "y_bit") Bit_Get()
{
	new
		BitArray:bb<32>;
	Bit_Set(bb, 10, true);
	Bit_Set(bb, 12, true);
	Bit_Set(bb, 18, true);
	Bit_Set(bb, 20, true);
	Bit_Set(bb, 30, true);
	Bit_Set(bb, 18, false);
	ASSERT(Bit_Get(bb, 10));
	ASSERT(Bit_Get(bb, 12));
	ASSERT(Bit_Get(bb, 20));
	ASSERT(!Bit_Get(bb, 0));
	ASSERT(!Bit_Get(bb, 18));
	ASSERT(!Bit_Get(bb, 17));
	ASSERT(!Bit_Get(bb, 31));
}

@test(.group = "y_bit") Bit_SetAll()
{
	new
		BitArray:bb<50>;
	Bit_SetAll(bb, true);
	ASSERT(Bit_Get(bb, 0));
	ASSERT(Bit_Get(bb, 10));
	ASSERT(Bit_Get(bb, 20));
	ASSERT(Bit_Get(bb, 30));
	ASSERT(Bit_Get(bb, 40));
	ASSERT(Bit_Get(bb, 50));
	ASSERT(Bit_Get(bb, 60));
	Bit_SetAll(bb, false);
	ASSERT(!Bit_Get(bb, 0));
	ASSERT(!Bit_Get(bb, 10));
	ASSERT(!Bit_Get(bb, 20));
	ASSERT(!Bit_Get(bb, 30));
	ASSERT(!Bit_Get(bb, 40));
	ASSERT(!Bit_Get(bb, 50));
	ASSERT(!Bit_Get(bb, 60));
}

@test(.group = "y_bit") Bit_Count()
{
	new
		BitArray:cc<70>;
	Bit_Set(cc, 0, true);
	Bit_Set(cc, 1, true);
	Bit_Set(cc, 2, true);
	Bit_Set(cc, 3, true);
	Bit_Set(cc, 4, true);
	Bit_Set(cc, 5, true);
	Bit_Set(cc, 6, true);
	Bit_Set(cc, 7, true);
	Bit_Set(cc, 8, true);
	Bit_Set(cc, 9, true);
	Bit_Set(cc, 50, true);
	ASSERT_EQ(Bit_Count(cc), 11);
	Bit_Set(cc, 51, true);
	Bit_Set(cc, 52, true);
	ASSERT_EQ(Bit_GetCount(cc), 13);
}

@test(.group = "y_bit") Bit_Iterators()
{
	new
		BitArray:bitArray<32>;
	FOREACH__ (new b : Bits(bitArray))
	{
		ASSERT(false);
	}
	new
		called = 0;
	FOREACH__ (new b : Blanks(bitArray))
	{
		++called;
	}
	ASSERT_EQ(called, cellbits);
	Bit_Set(bitArray, 5, true);
	Bit_Set(bitArray, 7, true);
	Bit_Set(bitArray, 9, true);
	Bit_Set(bitArray, 11, true);
	Bit_Set(bitArray, 13, true);
	FOREACH__ (new b : Bits(bitArray))
	{
		new
			bool:pass = b == 5 || b == 7 || b == 9 || b == 11 || b == 13;
		ASSERT(pass);
	}
	FOREACH__ (new b : Blanks(bitArray))
	{
		new
			bool:pass = b == 5 || b == 7 || b == 9 || b == 11 || b == 13;
		ASSERT(!pass);
	}
}

