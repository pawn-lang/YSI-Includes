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

TEST__ y_malloc_100()
{
	new
		Alloc:a = malloc(1000);
	ASSERT(bool:a);
	free(a);
}

TEST__ y_malloc_2_100()
{
	new
		Alloc:a = malloc(100);
	ASSERT(bool:a);
	free(a);
	new
		Alloc:b = malloc(100);
	ASSERT(bool:b);
	free(a);
	ASSERT_EQ(a, b);
}

TEST__ y_malloc_2000()
{
	new
		Alloc:a = malloc(2000);
	ASSERT(bool:a);
	free(a);
}

TEST__ y_malloc_clear()
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

TEST__ y_malloc_Loads()
{
	// Allocate slightly more memory than we have room for.
	new
		Alloc:a = malloc(MALLOC_MEMORY + 1);
	ASSERT_EQ(a, NO_ALLOC);
	ASSERT(!free(a));
}

#define MALLOC_TEST(%0) for (new Alloc:a = malloc(%0); __once && a; free(a))

TEST__ y_malloc_mset()
{
	MALLOC_TEST(10)
	{
		//ASSERT_ZE(mget(a, 5));
		mset(a, 5, 42);
		ASSERT_EQ(mget(a, 5), 42);
	}
}

TEST__ y_malloc_mget()
{
	MALLOC_TEST(10)
	{
		mset(a, 5, 11);
		ASSERT_EQ(mget(a, 5), 11);
		mset(a, 5, 42);
		//ASSERT_ZE(mget(a, 4));
		//ASSERT_ZE(mget(a, 6));
	}
}

TEST__ y_malloc_SlotSize()
{
	MALLOC_TEST(10)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 16 - 1);
	}
	MALLOC_TEST(100)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 112 - 1);
	}
	MALLOC_TEST(1000)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 1008 - 1);
	}
	MALLOC_TEST(1)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 16 - 1);
	}
	MALLOC_TEST(15)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 16 - 1);
	}
	MALLOC_TEST(16)
	{
		ASSERT_EQ(Malloc_SlotSize(a), 32 - 1);
	}
	for (new size = 1; size != 16; ++size)
	{
		MALLOC_TEST(size)
		{
			ASSERT_EQ(Malloc_SlotSize(a), 16 - 1);
		}
	}
	for (new size = 16; size != 32; ++size)
	{
		MALLOC_TEST(size)
		{
			ASSERT_EQ(Malloc_SlotSize(a), 32 - 1);
		}
	}
}

TEST__ y_malloc_msets()
{
	static const
		str0[] = "1111   ",
		str1[] = !"2222   ";
	MALLOC_TEST(10)
	{
		ASSERT_EQ(msets(a, 0, str0, false), 8);
		ASSERT_EQ(mget(a, 0), str0[0]);
		ASSERT_EQ(msets(a, 0, str1, false), 8);
		ASSERT_EQ(mget(a, 0), str1{0});
		ASSERT_EQ(msets(a, 0, str0, true), 8 char);
		ASSERT_EQ(mget(a, 0), ('1' << 24) | ('1' << 16) | ('1' << 08) | ('1' << 00));
		ASSERT_EQ(msets(a, 0, str1, true), 8 char);
		ASSERT_EQ(mget(a, 0), str1[0]);
	}
}

TEST__ y_malloc_mgets()
{
	static const
		str0[] = "1111   ";
	new
		str2[20];
	MALLOC_TEST(10)
	{
		msets(a, 0, str0, false);
		mgets(str2, sizeof (str2), a, 0, false);
		ASSERT_EQ(str2[0], '1');
		msets(a, 0, str0, false);
		mgets(str2, sizeof (str2), a, 0, true);
		ASSERT_EQ(str2{0}, '1');
		msets(a, 0, str0, true);
		mgets(str2, sizeof (str2), a, 0, false);
		ASSERT_EQ(str2[0], '1');
		msets(a, 0, str0, true);
		mgets(str2, sizeof (str2), a, 0, true);
		ASSERT_EQ(str2{0}, '1');
	}
}

/*
TEST__ y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

TEST__ y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

TEST__ y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}

TEST__ y_malloc_()
{
	MALLOC_TEST(10)
	{
	}
}
*/

TEST__ y_malloc_NewS_0()
{
	new
		Alloc:a = Malloc_NewS("Hello There", false);
	ASSERT(bool:a);
	if (a)
	{
		ASSERT_EQ(mget(a, 0), 'H');
		ASSERT_EQ(mget(a, 5), ' ');
		ASSERT_EQ(mget(a, 11), '\0');
		free(a);
	}
}

TEST__ y_malloc_NewS_1()
{
	new
		Alloc:a = Malloc_NewS("Hello There", true);
	ASSERT(bool:a);
	if (a)
	{
		static const
			b[12 char] = !"Hello There";
		ASSERT_EQ(mget(a, 0), b[0]);
		ASSERT_EQ(mget(a, 1), b[1]);
		ASSERT_EQ(mget(a, 2), b[2]);
		free(a);
	}
}

forward y_malloc_Deferred(Alloc:alloc);

public y_malloc_Deferred(Alloc:alloc)
{
	new
		Alloc:clobber = malloc(1000);
	for (new i = 0; i != 1000; ++i)
	{
		mset(clobber, i, 0);
	}
	for (new i = 0; i != 1000; ++i)
	{
		if (mget(alloc, i) != i * 2)
		{
			P:E("y_malloc_Deferred test error");
		}
	}
	free(clobber);
	free(alloc);
}

TEST__ y_malloc_Deferred()
{
	new
		Alloc:alloc = malloc(1000);
	for (new i = 0; i != 1000; ++i)
	{
		mset(alloc, i, i * 2);
	}
	YSI_SetTimerEx("y_malloc_Deferred", 10, false, "i", _:alloc);
}

