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

Test:y_malloc_100()
{
	new
		Alloc:a = malloc(1000);
	ASSERT(bool:a);
	free(a);
}

Test:y_malloc_2_100()
{
	new
		Alloc:a = malloc(100);
	ASSERT(bool:a);
	free(a);
	new
		Alloc:b = malloc(100);
	ASSERT(bool:b);
	free(a);
	ASSERT(a == b);
}

Test:y_malloc_2000()
{
	new
		Alloc:a = malloc(2000);
	ASSERT(bool:a);
	free(a);
}

Test:y_malloc_clear()
{
	new Alloc:mem[3];
	mem[0] = malloc(2);
	mem[1] = malloc(1);
	free(mem[0]);
	mem[2] = malloc(1);
	free(mem[1]);
	free(mem[2]);
	mem[0] = malloc(30);
	ASSERT(bool:mem[0]);
	free(mem[0]);
}

Test:y_malloc_Loads()
{
	// Allocate slightly more memory than we have room for.
	new
		Alloc:a = malloc(MALLOC_MEMORY + 1);
	ASSERT(a == NO_ALLOC);
	ASSERT(!free(a));
}

#define MALLOC_TEST(%0) for (new Alloc:a = malloc(%0), __loop = 1; a && (__loop || !free(a)); --__loop)

Test:y_malloc_mset()
{
	MALLOC_TEST(10)
	{
		ASSERT(mget(a, 5) == 0);
		mset(a, 5, 42);
		ASSERT(mget(a, 5) == 42);
	}
}

Test:y_malloc_mget()
{
	MALLOC_TEST(10)
	{
		mset(a, 5, 11);
		ASSERT(mget(a, 5) == 11);
		mset(a, 5, 42);
		ASSERT(mget(a, 4) == 0);
		ASSERT(mget(a, 6) == 0);
	}
}

Test:y_malloc_SlotSize()
{
	MALLOC_TEST(10)
	{
		ASSERT(Malloc_SlotSize(a) == 10);
	}
	MALLOC_TEST(100)
	{
		ASSERT(Malloc_SlotSize(a) == 100);
	}
	MALLOC_TEST(1000)
	{
		ASSERT(Malloc_SlotSize(a) == 1000);
	}
	MALLOC_TEST(1)
	{
		ASSERT(Malloc_SlotSize(a) == 1);
	}
}

Test:y_malloc_msets()
{
	static const
		str0[] = "1111   ",
		str1[] = !"2222   ";
	MALLOC_TEST(10)
	{
		ASSERT(msets(a, 0, str0, false) == 8);
		ASSERT(mget(a, 0) == str0[0]);
		ASSERT(msets(a, 0, str1, false) == 8);
		ASSERT(mget(a, 0) == str1{0});
		ASSERT(msets(a, 0, str0, true) == 8 char);
		ASSERT(mget(a, 0) == ('1' << 24) | ('1' << 16) | ('1' << 08) | ('1' << 00));
		ASSERT(msets(a, 0, str1, true) == 8 char);
		ASSERT(mget(a, 0) == str1[0]);
	}
}

Test:y_malloc_mgets()
{
	static const
		str0[] = "1111   ";
	new
		str2[20];
	MALLOC_TEST(10)
	{
		msets(a, 0, str0, false);
		mgets(str2, sizeof (str2), a, 0, false);
		ASSERT(str2[0] == '1');
		msets(a, 0, str0, false);
		mgets(str2, sizeof (str2), a, 0, true);
		ASSERT(str2{0} == '1');
		msets(a, 0, str0, true);
		mgets(str2, sizeof (str2), a, 0, false);
		ASSERT(str2[0] == '1');
		msets(a, 0, str0, true);
		mgets(str2, sizeof (str2), a, 0, true);
		ASSERT(str2{0} == '1');
	}
}

/*
Test:y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

Test:y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

Test:y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

Test:y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}
*/

Test:y_malloc_NewS_0()
{
	new
		Alloc:a = Malloc_NewS("Hello There", false);
	ASSERT(bool:a);
	if (a)
	{
		ASSERT(mget(a, 0) == 'H');
		ASSERT(mget(a, 5) == ' ');
		ASSERT(mget(a, 11) == '\0');
		free(a);
	}
}

Test:y_malloc_NewS_1()
{
	new
		Alloc:a = Malloc_NewS("Hello There", true);
	ASSERT(bool:a);
	if (a)
	{
		static const
			b[12 char] = !"Hello There";
		ASSERT(mget(a, 0) == b[0]);
		ASSERT(mget(a, 1) == b[1]);
		ASSERT(mget(a, 2) == b[2]);
		free(a);
	}
}
