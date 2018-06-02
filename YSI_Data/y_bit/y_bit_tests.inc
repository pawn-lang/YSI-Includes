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

Test:Bit_Bits()
{
	ASSERT(Bit_Bits(5) == 1);
	ASSERT(Bit_Bits(32) == 1);
	ASSERT(Bit_Bits(33) == 2);
	ASSERT(Bit_Bits(63) == 2);
	ASSERT(Bit_Bits(64) == 2);
	ASSERT(Bit_Bits(65) == 3);
	ASSERT(Bit_Bits(1024) == 32);
	ASSERT(Bit_Bits(1025) == 33);
}

Test:Bit_Set()
{
	new
		BitArray:bb<100>;
	Bit_Set(bb, 10, true);
	ASSERT(_:bb[0] == 1 << 10);
	ASSERT(_:bb[1] == 0);
	Bit_Set(bb, 32, true);
	ASSERT(_:bb[0] == 1 << 10);
	ASSERT(_:bb[1] == 1);
	Bit_Let(bb, 99);
	ASSERT(_:bb[0] == 1 << 10);
	ASSERT(_:bb[1] == 1);
	ASSERT(_:bb[3] == 8);
	Bit_Vet(bb, 99);
	ASSERT(_:bb[0] == 1 << 10);
	ASSERT(_:bb[1] == 1);
	ASSERT(_:bb[3] == 0);
	Bit_Let(bb, 11);
	ASSERT(_:bb[0] == 3 << 10);
	ASSERT(_:bb[1] == 1);
	ASSERT(_:bb[3] == 0);
	Bit_Vet(bb, 10);
	ASSERT(_:bb[0] == 2 << 10);
	ASSERT(_:bb[1] == 1);
	ASSERT(_:bb[3] == 0);
	Bit_Vet(bb, 11);
	ASSERT(_:bb[0] == 0);
}

Test:Bit_Get()
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

Test:Bit_SetAll()
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

Test:Bit_Count()
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
	ASSERT(Bit_Count(cc) == 11);
	Bit_Set(cc, 51, true);
	Bit_Set(cc, 52, true);
	ASSERT(Bit_GetCount(cc) == 13);
}

Test:Bit_Iterators()
{
	new
		BitArray:bitArray<32>;
	foreach (new b : Bits(bitArray))
	{
		ASSERT(false);
	}
	new
		called = 0;
	foreach (new b : Blanks(bitArray))
	{
		++called;
	}
	ASSERT(called == 32);
	Bit_Set(bitArray, 5, true);
	Bit_Set(bitArray, 7, true);
	Bit_Set(bitArray, 9, true);
	Bit_Set(bitArray, 11, true);
	Bit_Set(bitArray, 13, true);
	foreach (new b : Bits(bitArray))
	{
		ASSERT(b == 5 || b == 7 || b == 9 || b == 11 || b == 13);
	}
	foreach (new b : Blanks(bitArray))
	{
		ASSERT(!(b == 5 || b == 7 || b == 9 || b == 11 || b == 13));
	}
}

