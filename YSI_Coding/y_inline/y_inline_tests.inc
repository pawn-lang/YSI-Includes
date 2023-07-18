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

#define EBC__(%0,%1) (%1)$(Inline_EBC__(_:(%0),_:tagof(%0)))

static stock bool:y_inline_Get(callback:c, ret[E_CALLBACK_DATA], const f[] = "")
{
	return Callback_Get(c, ret, f);
}

static stock y_inline_GetX(Func:c<>, &Func:d<>)
{
	d = c;
	Indirect_Claim(c);
}

static stock y_inline_GetS(Func:c<s>, &Func:d<s>)
{
	d = c;
	Indirect_Claim(c);
}

static stock bool:y_inline_Restore(ret[E_CALLBACK_DATA])
{
	Callback_Restore(ret);
}

@test(.group = "y_inline") y_inline0a()
{
	new Func:cc<>;
	inline const func()
	{
	}
	y_inline_GetX(using inline func, cc);
	@.cc();
}

static g_y_inlineLoadsCalls = 0;

@test(.group = "y_inline") y_inlineLoads()
{
	new Func:a<>;
	new Func:c<>;
	new Func:d<>;
	new Func:e<>;
	g_y_inlineLoadsCalls = 0;
	inline A()
	{
		g_y_inlineLoadsCalls |= 1;
		new Func:b<>;
		inline B()
		{
			g_y_inlineLoadsCalls |= 2;
		}
		y_inline_GetX(using inline B, b);
		@.b();
	}
	y_inline_GetX(using inline A, a);
	inline C()
	{
		g_y_inlineLoadsCalls |= 4;
	}
	inline D()
	{
		g_y_inlineLoadsCalls |= 8;
	}
	inline E()
	{
		@.a();
		g_y_inlineLoadsCalls |= 16;
		new Func:f<>;
		inline F()
		{
			g_y_inlineLoadsCalls |= 32;
			new Func:g<>;
			inline G()
			{
				g_y_inlineLoadsCalls |= 64;
				new Func:h<>;
				inline H()
				{
					g_y_inlineLoadsCalls |= 128;
				}
				#pragma unused H
				y_inline_GetX(using inline H, h);
				@.h();
			}
			#pragma unused G
			y_inline_GetX(using inline G, g);
			@.g();
		}
		#pragma unused F
		y_inline_GetX(using inline F, f);
		@.f();
	}
	#pragma unused E
	y_inline_GetX(using inline C, c);
	@.c();
	y_inline_GetX(using inline D, d);
	@.d();
	y_inline_GetX(using inline E, e);
	@.e();
	ASSERT_EQ(g_y_inlineLoadsCalls, 255);
}

@test(.group = "y_inline") y_inline0b()
{
	new Func:cc<>;
	inline const func()
	{
		//print("1");
		@return 42;
	}
	y_inline_GetX(using inline func, cc);
	@.cc();
}

@test(.group = "y_inline") y_inline0c()
{
	new Func:cc<>;
	inline const func()
	{
		//print("1");
		@return 42;
	}
	y_inline_GetX(using inline func, cc);
	ASSERT_EQ(@.cc(), 42);
}

@test(.group = "y_inline") y_inline0d()
{
	new Func:cc<>;
	inline const func()
	{
		//print("1");
		@return 42;
	}
	y_inline_GetX(using inline func, cc);
	new
		dd[E_CALLBACK_DATA];
	dd[0] = _:cc;
	ASSERT_EQ(Callback_Call(dd, 42), 42);
}

@test(.group = "y_inline") y_inline0e()
{
	new Func:cc<>;
	inline func()
	{
		//print("1");
		@return 42;
	}
	y_inline_GetX(using inline func, cc);
	new
		dd[E_CALLBACK_DATA];
	dd[0] = _:cc;
	ASSERT_EQ(Callback_Call(dd, 42), 42);
}

@test(.group = "y_inline") y_inline0f()
{
	new Func:cc<>;
	inline func()
	{
		//print("1");
		@return 42;
	}
	y_inline_GetX(using inline func, cc);
	new
		dd[E_CALLBACK_DATA];
	dd[0] = _:cc;
	ASSERT_EQ(Callback_Call(dd, 42), 42);
	Callback_Restore(cc);
}

@test(.group = "y_inline") y_inline1()
{
	new
		cc[E_CALLBACK_DATA];
	inline func()
	{
		@return 42;
	}
	y_inline_Get(using inline func, cc);
	ASSERT_EQ(Callback_Call(cc), 42);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline2()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(a)
	{
		@return a;
	}
	y_inline_Get(using inline func, cc);
	ASSERT_EQ(Callback_Call(cc, 50), 50);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline3()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		r2 = 99;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 99);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline4()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		r = 99;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 100);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline5()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(a, b, c, d)
	{
		ASSERT_EQ(a, 1);
		ASSERT_EQ(b, 11);
		ASSERT_EQ(c, 111);
		ASSERT_EQ(d, 1111);
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, 1, 11, 111, 1111);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline6()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(string:g[])
	{
		#if !(sizeof (g) == YSI_MAX_STRING))
			#error sizeof (g) != YSI_MAX_STRING
		#endif
		ASSERT_SAME(g, "hello");
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, "hello");
	Callback_Release(cc);
}

forward y_inline7a();

public y_inline7a()
{
	inline func7a()
	{
	}
	#pragma unused func7a
}

@test(.group = "y_inline") y_inline7b()
{
	new
		cc[E_CALLBACK_DATA];
	inline func7b()
	{
	}
	#pragma unused func7b
	ASSERT_EQ(y_inline_Get(using func7a, cc), false);
	ASSERT(y_inline_Get(using func7b, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(using public y_inline7a, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"func7b", cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"y_inline7a", cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(using func7b, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(using y_inline7a, cc));
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline8()
{
	for (new i = 2; i--; )
	{
		new
			cc[E_CALLBACK_DATA];
		if (i)
		{
			inline func8b()
			{
			}
		}
		if (!i)
		{
			ASSERT_EQ(y_inline_Get(using func8a, cc), false);
			ASSERT_EQ(y_inline_Get(using func8b, cc), false);
			Callback_Release(cc);
			ASSERT_EQ(y_inline_Get(using public y_inline8, cc), false);
			Callback_Release(cc);
		}
		if (i)
		{
			inline func8a()
			{
			}
		}
	}
}

forward y_inline9(a);

public y_inline9(a)
{
	return 12345 + a;
}

@test(.group = "y_inline") y_inline9()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(using public y_inline9, cc, "i"));
	ASSERT_EQ(Callback_Call(cc, 67), 12345 + 67);
	Callback_Release(cc);
}

forward y_inline10(a, b[]);

public y_inline10(a, b[])
{
	return 12345 + a + b[0];
}

@test(.group = "y_inline") y_inline10()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(using callback y_inline10, cc, "is"));
	ASSERT_EQ(Callback_Call(cc, 67, "50"), 12345 + 67 + '5');
	ASSERT(y_inline_Get(using callback y_inline10<is>, cc));
	ASSERT_EQ(Callback_Call(cc, 67, "50"), 12345 + 67 + '5');
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline11()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline func()
	{
		g = 11;
	}
	y_inline_Get(using inline func, cc);
	ASSERT_EQ(g, 5);
	Callback_Call(cc);
	ASSERT_EQ(g, 5);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 11);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline12()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline func()
	{
		++g;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 9);
	Callback_Release(cc);
}

static stock
	YSI_g_sRemoteTestVar = 0;

@test(.group = "y_inline") y_inline13()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline const func()
	{
		ASSERT_EQ(g, 5);
		++g;
		YSI_g_sRemoteTestVar = g;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	YSI_g_sRemoteTestVar = 0;
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 5);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 6);
	Callback_Release(cc);
}

@test(.group = "y_inline") Callback_AAA()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline const func()
	{
		ASSERT_EQ(g, 5);
		++g;
		YSI_g_sRemoteTestVar = g;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	YSI_g_sRemoteTestVar = 0;
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 5);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 6);
	Callback_Release(cc);
}

@test(.group = "y_inline") Callback_AA()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(&a)
	{
		a = 7;
		#pragma unused a
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	Callback_Call(cc, a);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") Callback_Arr1()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(&a)
	{
		ASSERT_ZE(a);
		a = 7;
		ASSERT_EQ(a, 7);
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	ASSERT_ZE(a);
	Callback_Call(cc, a);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") Callback_Arr2()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(string:str[])
	{
		ASSERT_SAME(str, "hello");
	}
	y_inline_Get(using inline func, cc);
	new
		str[YSI_MAX_STRING] = "hello";
	Callback_Call(cc, str);
	ASSERT_SAME(str, "hello");
	Callback_Call(cc, "hello");
}

@test(.group = "y_inline") Callback_Arr3()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(a)
	{
		ASSERT_ZE(a);
		a = 7;
		ASSERT_EQ(a, 7);
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	ASSERT_ZE(a);
	Callback_Call(cc, a);
	ASSERT_ZE(a);
}

@test(.group = "y_inline") Callback_Array0()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline const func()
	{
		ASSERT_EQ(g, 5);
		++g;
	}
	y_inline_Get(using inline func, cc);
	// Test zero parameter calls.
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
}

@test(.group = "y_inline") Callback_Array1()
{
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	new
		cc[E_CALLBACK_DATA];
	inline const func(&a, string:b[], c)
	{
		ASSERT_EQ(c, 6);
		ASSERT_SAME(b, "hey");
		a = 7;
		#pragma unused a
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0,
		str[4] = "hey",
		c = 6,
		pars[3];
	Callback_Call(cc, a, str, c);
	ASSERT_EQ(a, 7);
	pars[0] = AMX_Ref(a);
	pars[1] = AMX_Ref(str[0]);
	pars[2] = AMX_Ref(c);
	// Test more parameters.
	a = 2;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
	a = 11;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
	a = 32;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") y_inline_Remote0()
{
	new
		Function:f0 = GetRemoteFunction("MyTesterFunc", "m"),
		Function:f1 = GetRemoteFunction("MyTesterFunc", "m"),
		Function:f2 = GetRemoteFunction("MyTesterFunc", "m"),
		Function:f3 = GetRemoteFunction("MyTesterFunc", "n");
//	ASSERT_EQ(f0, f1);
	ASSERT_NE(_:f2, _:f3);
}

forward y_inline_Remote1(v);

public y_inline_Remote1(v)
{
	YSI_g_sRemoteTestVar = v;
	return v - 10;
}

@test(.group = "y_inline") y_inline_Remote1()
{
	new
		ret = 0;
	
	ret = strcmp("hello", "hello");
	ASSERT(!ret);
	ret = strcmp("hello", !"hello");
	ASSERT(!ret);
	ret = strcmp(!"hello", "hello");
	ASSERT(!ret);
	ret = strcmp(!"hello", !"hello");
	ASSERT(!ret);
	ret = strcmp("m", "n");
	ASSERT(!!ret);
	ret = strcmp("m", !"n");
	ASSERT(!!ret);
	ret = strcmp(!"m", "n");
	ASSERT(!!ret);
	ret = strcmp(!"m", !"n");
	ASSERT(!!ret);
	
	// Clearly "CallRemoteFunction" works with packed strings.  Good.
	YSI_g_sRemoteTestVar = 5;
	
	ret = CallRemoteFunction(!"y_inline_Remote1", !"i", 74);
	ASSERT_EQ(ret, 64);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 74);
	
	ret = CallRemoteFunction(!"y_inline_Remote1", "i", 75);
	ASSERT_EQ(ret, 65);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 75);
	
	ret = CallRemoteFunction("y_inline_Remote1", !"i", 76);
	ASSERT_EQ(ret, 66);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 76);
	
	ret = CallRemoteFunction("y_inline_Remote1", "i", 77);
	ASSERT_EQ(ret, 67);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 77);
}

@test(.group = "y_inline") y_inline_Remote2()
{
	YSI_g_sRemoteTestVar = 5;
	new
		Function:f = GetRemoteFunction("y_inline_Remote1", "i");
	
	YSI_g_sRemoteTestVar = 5;
	ASSERT_EQ(CallStoredFunction(f, 99), 89);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 99);
	ASSERT_EQ(CallStoredFunction(f, 111), 101);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 111);
	ASSERT_EQ(CallStoredFunction(f, 9739), 9729);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 9739);
	ASSERT_EQ(CallStoredFunction(f, 11), 1);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 11);
	ASSERT_EQ(CallStoredFunction(f, 9), -1);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 9);
}

@test(.group = "y_inline") y_inline_Remote3()
{
	new
		Function:a = GetRemoteFunction("MyTesterFunc", "a"),
		Function:b = GetRemoteFunction("MyTesterFunc", "b"),
		Function:c = GetRemoteFunction("MyTesterFunc", "c"),
		Function:d = GetRemoteFunction("MyTesterFunc", "d"),
		Function:e = GetRemoteFunction("MyTesterFunc", "e"),
		Function:f = GetRemoteFunction("MyTesterFunc", "f"),
		Function:g = GetRemoteFunction("MyTesterFunc", "g"),
		Function:h = GetRemoteFunction("MyTesterFunc", "h"),
		Function:i = GetRemoteFunction("MyTesterFunc", "i"),
		Function:j = GetRemoteFunction("MyTesterFunc", "j"),
		Function:k = GetRemoteFunction("MyTesterFunc", "k"),
		Function:l = GetRemoteFunction("MyTesterFunc", "l");
	ASSERT_NZ(_:a);
	ASSERT_NZ(_:b);
	ASSERT_NZ(_:c);
	ASSERT_NZ(_:d);
	ASSERT_NZ(_:e);
	ASSERT_NZ(_:f);
	ASSERT_NZ(_:g);
	ASSERT_NZ(_:h);
	ASSERT_NZ(_:i);
	ASSERT_NZ(_:j);
	ASSERT_NZ(_:k);
	ASSERT_NZ(_:l);
	ASSERT_NE(_:a, _:b);
	ASSERT_NE(_:a, _:c);
	ASSERT_NE(_:a, _:d);
	ASSERT_NE(_:a, _:e);
	ASSERT_NE(_:a, _:f);
	ASSERT_NE(_:a, _:g);
	ASSERT_NE(_:a, _:h);
	ASSERT_NE(_:a, _:i);
	ASSERT_NE(_:a, _:j);
	ASSERT_NE(_:a, _:k);
	ASSERT_NE(_:a, _:l);
	ASSERT_NE(_:b, _:c);
	ASSERT_NE(_:b, _:d);
	ASSERT_NE(_:b, _:e);
	ASSERT_NE(_:b, _:f);
	ASSERT_NE(_:b, _:g);
	ASSERT_NE(_:b, _:h);
	ASSERT_NE(_:b, _:i);
	ASSERT_NE(_:b, _:j);
	ASSERT_NE(_:b, _:k);
	ASSERT_NE(_:b, _:l);
	ASSERT_NE(_:c, _:d);
	ASSERT_NE(_:c, _:e);
	ASSERT_NE(_:c, _:f);
	ASSERT_NE(_:c, _:g);
	ASSERT_NE(_:c, _:h);
	ASSERT_NE(_:c, _:i);
	ASSERT_NE(_:c, _:j);
	ASSERT_NE(_:c, _:k);
	ASSERT_NE(_:c, _:l);
	ASSERT_NE(_:d, _:e);
	ASSERT_NE(_:d, _:f);
	ASSERT_NE(_:d, _:g);
	ASSERT_NE(_:d, _:h);
	ASSERT_NE(_:d, _:i);
	ASSERT_NE(_:d, _:j);
	ASSERT_NE(_:d, _:k);
	ASSERT_NE(_:d, _:l);
	ASSERT_NE(_:e, _:f);
	ASSERT_NE(_:e, _:g);
	ASSERT_NE(_:e, _:h);
	ASSERT_NE(_:e, _:i);
	ASSERT_NE(_:e, _:j);
	ASSERT_NE(_:e, _:k);
	ASSERT_NE(_:e, _:l);
	ASSERT_NE(_:f, _:g);
	ASSERT_NE(_:f, _:h);
	ASSERT_NE(_:f, _:i);
	ASSERT_NE(_:f, _:j);
	ASSERT_NE(_:f, _:k);
	ASSERT_NE(_:f, _:l);
	ASSERT_NE(_:g, _:h);
	ASSERT_NE(_:g, _:i);
	ASSERT_NE(_:g, _:j);
	ASSERT_NE(_:g, _:k);
	ASSERT_NE(_:g, _:l);
	ASSERT_NE(_:h, _:i);
	ASSERT_NE(_:h, _:j);
	ASSERT_NE(_:h, _:k);
	ASSERT_NE(_:h, _:l);
	ASSERT_NE(_:i, _:j);
	ASSERT_NE(_:i, _:k);
	ASSERT_NE(_:i, _:l);
	ASSERT_NE(_:j, _:k);
	ASSERT_NE(_:j, _:l);
	ASSERT_NE(_:k, _:l);
}

@test(.group = "y_inline") CallStoredFunction0()
{
	ASSERT_ZE(CallStoredFunction(Function:0));
}

// Test inline functions inside hooks, in which the parameter counts are mangled
// so can't be used to allocate memory.
static
	YSI_g_sInlineTestVar0 = 0;

HOOK__ y_inline_InHook0@0()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		YSI_g_sInlineTestVar0 += 1;
		r2 = 94;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 94);
	Callback_Release(cc);
}

HOOK__ y_inline_InHook1@0(a)
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		YSI_g_sInlineTestVar0 += a;
		r2 = 95;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 95);
	Callback_Release(cc);
}

HOOK__ y_inline_InHook2@0(a, b)
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		ASSERT_EQ(numargs(), 2);
		#pragma unused r2
		YSI_g_sInlineTestVar0 += a * b;
		r2 = 96;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 96);
	Callback_Release(cc);
}

HOOK__ y_inline_InHook0@1()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		ASSERT_ZE(numargs());
		#pragma unused r2
		YSI_g_sInlineTestVar0 += 1 * 2;
		r2 = 98;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 98);
	Callback_Release(cc);
}

HOOK__ y_inline_InHook1@1(a)
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		YSI_g_sInlineTestVar0 += a * 2;
		r2 = 97;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 97);
	Callback_Release(cc);
}

HOOK__ y_inline_InHook2@1(a, b)
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	inline func(&r2)
	{
		#pragma unused r2
		YSI_g_sInlineTestVar0 += a * b * 2;
		r2 = 90;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 90);
	Callback_Release(cc);
}

@test(.group = "y_inline") y_inline_InHook0()
{
	// DebugLevel(7);
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook0", "");
	ASSERT_EQ(YSI_g_sInlineTestVar0, 3);
	// DebugLevel(0);
}

@test(.group = "y_inline") y_inline_InHook1()
{
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook1", "i", 4);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 12);
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook1", "i", 5);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 15);
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook1", "i", 100);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 300);
}

@test(.group = "y_inline") y_inline_InHook2()
{
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook2", "ii", 4, 5);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 12 * 5);
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook2", "ii", 5, 6);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 15 * 6);
	YSI_g_sInlineTestVar0 = 0;
	CallLocalFunction("y_inline_InHook2", "ii", 100, 100);
	ASSERT_EQ(YSI_g_sInlineTestVar0, 300 * 100);
}

static stock
	YSI_g_sInlineTestVar2 = 0,
	YSI_g_sInlineTestVar3 = 0,
	YSI_g_sInlineTestCB[E_CALLBACK_DATA];

static stock y_inline_Getter(callback:cb)
{
	Callback_Get(cb, YSI_g_sInlineTestCB);
}

static stock y_inline_TestFunc_0()
{
	inline TestCallback1()
	{
		++YSI_g_sInlineTestVar3;
	}
	y_inline_Getter(using inline TestCallback1);
}

static stock y_inline_TestFunc_1()
{
	inline TestCallback1()
	{
		++YSI_g_sInlineTestVar3;
		return;
	}
	y_inline_Getter(using inline TestCallback1);
}

static stock y_inline_TestFunc_2()
{
	inline TestCallback1()
	{
		++YSI_g_sInlineTestVar3;
		return 1;
	}
	y_inline_Getter(using inline TestCallback1);
	return 0;
}

static stock y_inline_TestFunc_3()
{
	inline TestCallback1()
	{
		++YSI_g_sInlineTestVar3;
		return 3;
	}
	y_inline_Getter(using inline TestCallback1);
	return 2;
}

static stock y_inline_TestFunc_4(lvar)
{
	inline TestCallback1()
	{
		YSI_g_sInlineTestVar2 = lvar;
		++YSI_g_sInlineTestVar3;
		return 4;
	}
	y_inline_Getter(using inline TestCallback1);
	return 9;
}

static stock y_inline_TestFunc_5()
{
	inline TestCallback1(ivar)
	{
		YSI_g_sInlineTestVar2 = ivar;
		++YSI_g_sInlineTestVar3;
		return 5;
	}
	y_inline_Getter(using inline TestCallback1);
	return 8;
}

static stock y_inline_TestFunc_6(lvar)
{
	inline TestCallback1(ivar)
	{
		YSI_g_sInlineTestVar2 = ivar + lvar;
		++YSI_g_sInlineTestVar3;
		return 6;
	}
	y_inline_Getter(using inline TestCallback1);
	return 7;
}

@test(.group = "y_inline") y_inline_ParameterTypes_0()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	y_inline_TestFunc_0();
	ASSERT_ZE(Callback_Call(YSI_g_sInlineTestCB));
	ASSERT_ZE(YSI_g_sInlineTestVar2);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_1()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	y_inline_TestFunc_1();
	ASSERT_ZE(Callback_Call(YSI_g_sInlineTestCB));
	ASSERT_ZE(YSI_g_sInlineTestVar2);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_2()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_ZE(y_inline_TestFunc_2());
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB), 1);
	ASSERT_ZE(YSI_g_sInlineTestVar2);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_3()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_3(), 2);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB), 3);
	ASSERT_ZE(YSI_g_sInlineTestVar2);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_4()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_4(11), 9);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB), 4);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 11);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_5()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_5(), 8);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB, 22), 5);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 22);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_6()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_6(33), 7);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB, 44), 6);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 33 + 44);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

static stock y_inline_TestFunc_7(lvar)
{
	new
		cvar = 101;
	inline TestCallback1(ivar)
	{
		YSI_g_sInlineTestVar2 = cvar + ivar + lvar;
		++YSI_g_sInlineTestVar3;
		return ivar;
	}
	y_inline_Getter(using inline TestCallback1);
	return lvar;
}

static stock y_inline_TestFunc_8(const string:svar0[])
{
	new
		svar0b[20];
	StrCpy(svar0b, svar0);
	inline TestCallback1()
	{
		YSI_g_sInlineTestVar2 = strval(svar0b);
		++YSI_g_sInlineTestVar3;
		return strval(svar0b[12]);
	}
	y_inline_Getter(using inline TestCallback1);
	return strval(svar0b[6]);
}

static stock y_inline_TestFunc_9()
{
	inline TestCallback1(string:svar1[])
	{
		YSI_g_sInlineTestVar2 = strval(svar1);
		++YSI_g_sInlineTestVar3;
		return strval(svar1[6]);
	}
	y_inline_Getter(using inline TestCallback1);
	return 99;
}

static stock y_inline_TestFunc_10(const string:svar0[])
{
	new
		svar0b[20];
	StrCpy(svar0b, svar0);
	inline TestCallback1(string:svar1[])
	{
		YSI_g_sInlineTestVar2 = strval(svar0b) * strval(svar1);
		++YSI_g_sInlineTestVar3;
		return strval(svar1[6]);
	}
	y_inline_Getter(using inline TestCallback1);
	return strval(svar0b[6]);
}

@test(.group = "y_inline") y_inline_ParameterTypes_7()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_7(202), 202);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB, 303), 303);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 101 + 202 + 303);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_8()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_8("123   456   999"), 456);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB), 999);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 123);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_9()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_9(), 99);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB, "4242  2424"), 2424);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 4242);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

@test(.group = "y_inline") y_inline_ParameterTypes_10()
{
	YSI_g_sInlineTestVar2 = 0;
	YSI_g_sInlineTestVar3 = 0;
	ASSERT_EQ(y_inline_TestFunc_10("9999  1111"), 1111);
	ASSERT_EQ(Callback_Call(YSI_g_sInlineTestCB, "6543  2109"), 2109);
	ASSERT_EQ(YSI_g_sInlineTestVar2, 9999 * 6543);
	ASSERT_EQ(YSI_g_sInlineTestVar3, 1);
	Callback_Release(YSI_g_sInlineTestCB);
}

y_inline_ForEach(array[], Func:callback<i>, size = sizeof (array))
{
	for (new i = 0; i != size; ++i)
	{
		@.callback(array[i]);
	}
	Callback_Restore(callback);
}

y_inline_Fold(array[], Func:callback<ii>, initial, size = sizeof (array))
{
	for (new i = 0; i != size; ++i)
	{
		initial = @.callback(array[i], initial);
	}
	Callback_Restore(callback);
	return initial;
}

@test(.group = "y_inline") y_inline_NewAPI1()
{
	new array[10] = { 0, 5, 1, 5, 2, 3, 4, 5, 5, 0 };
	new count = 0;
	inline IsFive(value)
	{
		if (value == 5)
			++count;
	}
	y_inline_ForEach(array, using inline IsFive);
	ASSERT_EQ(count, 4);
}

@test(.group = "y_inline") y_inline_NewAPI2()
{
	new array[10] = { 0, 5, 1, 5, 2, 3, 4, 5, 5, 0 };
	new count = 0;
	inline const IsFive(value)
	{
		if (value == 5)
			++count;
	}
	y_inline_ForEach(array, using inline IsFive);
	ASSERT_ZE(count);
}

@test(.group = "y_inline") y_inline_NewAPI3()
{
	new array[10] = { 5, 5, 1, 5, 2, 3, 4, 5, 5, 5 };
	inline const IsFive(value, count)
	{
		if (value == 5)
			inline_return count + 1;
		inline_return count;
	}
	new count = y_inline_Fold(array, using inline IsFive, 0);
	ASSERT_EQ(count, 6);
}

y_inline_MetaData(Func:cb<iis>)
{
	ASSERT_ZE(Indirect_GetMeta(cb));
	Indirect_SetMeta(cb, 42);
	ASSERT_EQ(Indirect_GetMeta(cb), 42);
	new ret = @.cb(4, 5, "The Dummy Call");
	Callback_Restore(cb);
	return ret;
}

@test(.group = "y_inline") y_inline_MetaData()
{
	inline Dummy(a, b, string:c[])
	{
		ASSERT_SAME(c, "The Dummy Call");
		inline_return a + b;
	}
	new ret = y_inline_MetaData(using inline Dummy);
	ASSERT_EQ(ret, 9);
}

// ========================================================================== //
// ========================================================================== //
// ========================================================================== //
// ========================================================================== //

@test(.group = "y_inline") nu_y_inline1()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func()
	{
		@return 42;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	ASSERT_EQ(Callback_Call(cc), 42);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline2()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func(a)
	{
		@return a;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	ASSERT_EQ(Callback_Call(cc, 50), 50);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline3()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	INLINE__ func(&r2)
	{
		#pragma unused r2
		r2 = 99;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 99);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline4()
{
	new
		cc[E_CALLBACK_DATA],
		r = 100;
	INLINE__ func(&r2)
	{
		#pragma unused r2
		r = 99;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc, r);
	ASSERT_EQ(r, 100);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline5()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func(a, b, c, d)
	{
		ASSERT_EQ(a, 1);
		ASSERT_EQ(b, 11);
		ASSERT_EQ(c, 111);
		ASSERT_EQ(d, 1111);
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc, 1, 11, 111, 1111);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline6()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func(string:g[])
	{
		#if !(sizeof (g) == YSI_MAX_STRING))
			#error sizeof (g) != YSI_MAX_STRING
		#endif
		ASSERT_SAME(g, "hello");
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc, "hello");
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline6b()
{
	new Func:cc<s>;
	INLINE_CONST__ func(string:g[])
	{
		#if !(sizeof (g) == YSI_MAX_STRING))
			#error sizeof (g) != YSI_MAX_STRING
		#endif
		ASSERT_SAME(g, "hello");
	}
	y_inline_GetS(USING_INLINE__ func, cc);
	new hash[61] = "hello";
	@.cc(hash);
	Indirect_Release(cc);
}

@test(.group = "y_inline") nu_y_inline7b()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func7b()
	{
	}
	ASSERT_EQ(y_inline_Get(USING__ func7a, cc), false);
	ASSERT(y_inline_Get(USING__ func7b, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(USING_PUBLIC__ y_inline7a, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"func7b", cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"y_inline7a", cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(USING__ func7b, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(USING__ y_inline7a, cc));
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline8()
{
	for (new i = 2; i--; )
	{
		new
			cc[E_CALLBACK_DATA];
		if (i)
		{
			INLINE__ func8b()
			{
			}
		}
		if (!i)
		{
			ASSERT_EQ(y_inline_Get(USING__ func8a, cc), false);
			ASSERT_EQ(y_inline_Get(USING__ func8b, cc), false);
			Callback_Release(cc);
			ASSERT_EQ(y_inline_Get(USING_PUBLIC__ y_inline8, cc), false);
			Callback_Release(cc);
		}
		if (i)
		{
			INLINE__ func8a()
			{
			}
		}
	}
}

@test(.group = "y_inline") nu_y_inline9()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(USING__ public y_inline9, cc, "i"));
	ASSERT_EQ(Callback_Call(cc, 67), 12345 + 67);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline10()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(USING_CALLBACK__ y_inline10, cc, "is"));
	ASSERT_EQ(Callback_Call(cc, 67, "50"), 12345 + 67 + '5');
	ASSERT(y_inline_Get(USING__ callback y_inline10<is>, cc));
	ASSERT_EQ(Callback_Call(cc, 67, "50"), 12345 + 67 + '5');
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline11()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	INLINE__ func()
	{
		g = 11;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	ASSERT_EQ(g, 5);
	Callback_Call(cc);
	ASSERT_EQ(g, 5);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 11);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline12()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	INLINE__ func()
	{
		++g;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 9);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_y_inline13()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	INLINE__ const func()
	{
		ASSERT_EQ(g, 5);
		++g;
		YSI_g_sRemoteTestVar = g;
	}
	y_inline_Get(USING_INLINE__ func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	YSI_g_sRemoteTestVar = 0;
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT_EQ(g, 5);
	ASSERT_EQ(YSI_g_sRemoteTestVar, 6);
	Callback_Release(cc);
}

@test(.group = "y_inline") nu_Callback_AA()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ func(&a)
	{
		a = 7;
		#pragma unused a
	}
	y_inline_Get(USING_INLINE__ func, cc);
	new
		a = 0;
	Callback_Call(cc, a);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") nu_Callback_Arr1()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE_CONST__ func(&a)
	{
		ASSERT_ZE(a);
		a = 7;
		ASSERT_EQ(a, 7);
	}
	y_inline_Get(USING__ inline func, cc);
	new
		a = 0;
	ASSERT_ZE(a);
	Callback_Call(cc, a);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") nu_Callback_Arr2()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ const func(string:str[])
	{
		ASSERT_SAME(str, "hello");
	}
	y_inline_Get(USING_INLINE__ func, cc);
	new
		str[YSI_MAX_STRING] = "hello";
	Callback_Call(cc, str);
	ASSERT_SAME(str, "hello");
	Callback_Call(cc, "hello");
}

@test(.group = "y_inline") nu_Callback_Arr3()
{
	new
		cc[E_CALLBACK_DATA];
	INLINE__ const func(a)
	{
		ASSERT_ZE(a);
		a = 7;
		ASSERT_EQ(a, 7);
	}
	y_inline_Get(USING_INLINE__ func, cc);
	new
		a = 0;
	ASSERT_ZE(a);
	Callback_Call(cc, a);
	ASSERT_ZE(a);
}

@test(.group = "y_inline") nu_Callback_Array0()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	INLINE_CONST__ func()
	{
		ASSERT_EQ(g, 5);
		++g;
	}
	y_inline_Get(USING__ inline func, cc);
	// Test zero parameter calls.
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
}

@test(.group = "y_inline") nu_Callback_Array1()
{
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	new
		cc[E_CALLBACK_DATA];
	INLINE__ const func(&a, string:b[], c)
	{
		ASSERT_EQ(c, 6);
		ASSERT_SAME(b, "hey");
		a = 7;
		#pragma unused a
	}
	//DisasmDump("inline6.asm");
	y_inline_Get(USING_INLINE__ func, cc);
	new
		a = 0,
		str[4] = "hey",
		c = 6,
		pars[3];
	Callback_Call(cc, a, str, c);
	ASSERT_EQ(a, 7);
	pars[0] = AMX_Ref(a);
	pars[1] = AMX_Ref(str[0]);
	pars[2] = AMX_Ref(c);
	// Test more parameters.
	a = 2;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
	a = 11;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
	a = 32;
	Callback_Array(cc, pars, 3);
	ASSERT_EQ(a, 7);
}

@test(.group = "y_inline") nu_y_inline_NewAPI1()
{
	new array[10] = { 0, 5, 1, 5, 2, 3, 4, 5, 5, 0 };
	new count = 0;
	INLINE__ IsFive(value)
	{
		if (value == 5)
			++count;
	}
	y_inline_ForEach(array, USING_INLINE__ IsFive);
	ASSERT_EQ(count, 4);
}

@test(.group = "y_inline") nu_y_inline_NewAPI2()
{
	new array[10] = { 0, 5, 1, 5, 2, 3, 4, 5, 5, 0 };
	new count = 0;
	INLINE__ const IsFive(value)
	{
		if (value == 5)
			++count;
	}
	y_inline_ForEach(array, USING_INLINE__ IsFive);
	ASSERT_ZE(count);
}

@test(.group = "y_inline") nu_y_inline_NewAPI3()
{
	new array[10] = { 5, 5, 1, 5, 2, 3, 4, 5, 5, 5 };
	INLINE__ const IsFive(value, count)
	{
		if (value == 5)
			inline_return count + 1;
		inline_return count;
	}
	new count = y_inline_Fold(array, USING_INLINE__ IsFive, 0);
	ASSERT_EQ(count, 6);
}

@test(.group = "y_inline") nu_y_inline_MetaData()
{
	INLINE__ Dummy(a, b, string:c[])
	{
		ASSERT_SAME(c, "The Dummy Call");
		inline_return a + b;
	}
	new ret = y_inline_MetaData(USING_INLINE__ Dummy);
	ASSERT_EQ(ret, 9);
}

@test(.group = "y_inline") y_inline_DeeplyNested()
{
	new k = 0;
	for (new i = 0; i != 10; ++i)
	{
		switch (i)
		{
		case 0, 2, 4, 6, 8:
		{
		}
		case 1, 3, 5, 7:
		{
			if (i & 1)
			{
				switch (i)
				{
				case 0, 2, 4, 6, 8:
				{
				}
				case 1, 3, 5, 7:
				{
					for (new j = 0; j != 2; ++j)
					{
						INLINE__ Dummy(a, b, string:c[])
						{
							ASSERT_SAME(c, "The Dummy Call");
							++k;
							inline_return a + b;
						}
						new ret = y_inline_MetaData(USING_INLINE__ Dummy);
						ASSERT_EQ(ret, 9);
					}
				}
				case 9:
				{
				}
				default:
				{
					INLINE__ Dummy(a, b, string:c[])
					{
						ASSERT_SAME(c, "The Dummy Call");
						inline_return a + b;
					}
					new ret = y_inline_MetaData(USING_INLINE__ Dummy);
					ASSERT_EQ(ret, 9);
				}
				}
			}
			else
			{
				switch (i)
				{
				case 0, 2, 4, 6, 8:
				{
					INLINE__ Dummy(a, b, string:c[])
					{
						ASSERT_SAME(c, "The Dummy Call");
						inline_return a + b;
					}
					new ret = y_inline_MetaData(USING_INLINE__ Dummy);
					ASSERT_EQ(ret, 9);
				}
				case 1, 3, 5, 7:
				{
					for (new j = 0; j != 1; ++j)
					{
						INLINE__ Dummy(a, b, string:c[])
						{
							ASSERT_SAME(c, "The Dummy Call");
							inline_return a + b;
						}
						new ret = y_inline_MetaData(USING_INLINE__ Dummy);
						ASSERT_EQ(ret, 9);
					}
				}
				case 9:
				{
					INLINE__ Dummy(a, b, string:c[])
					{
						ASSERT_SAME(c, "The Dummy Call");
						inline_return a + b;
					}
					new ret = y_inline_MetaData(USING_INLINE__ Dummy);
					ASSERT_EQ(ret, 9);
				}
				default:
				{
				}
				}
			}
		}
		case 9:
		{
		}
		default:
		{
		}
		}
	}
	ASSERT_EQ(k, 8);
}

@test(.group = "y_inline") y_inline_timer()
{
	// This is tricky to test, because we need to test it instantly, but the timer (by definition)
	// is called in the future.  So we just test that a timer was probably started for now.
	inline const X()
	{
	}
	new timer = Timer_CreateCallback(using inline X, 100);
	ASSERT_NE(timer, 0);
	ASSERT_NE(Indirect_GetMeta(timer), 0);
	Timer_KillCallback(timer);
}

@test(.group = "y_inline") y_inline_repeating()
{
	inline const X()
	{
	}
	new timer = Timer_CreateCallback(using inline X, 10, 1000);
}

static stock
	YSI_gsStarts[1000],
	YSI_gsCounts[sizeof (YSI_gsStarts)],
	YSI_gsCount = 0;

@test(.group = "y_inline") y_inline1000timers()
{
	//print("y_inline1000timers");
	inline const Total()
	{
		//for (new i = 0; i != sizeof (YSI_gsCounts); ++i)
		//{
		//	printf("Count %d = %d", i, YSI_gsCounts[i]);
		//	printf("Time %d = %d", i, YSI_gsStarts[i]);
		//}
		new str[32];
		format(str, sizeof (str), "Count = %d", YSI_gsCount);
		Server_PrintIntroMessage(str);
	}
	for (new i = 0; i != sizeof (YSI_gsStarts); ++i)
	{
		inline X()
		{
			//printf("Call %d = %d", i, callCount);
			if (++YSI_gsCounts[i] == 50)
			{
				//printf("Diff %d = %d", i, GetTickCount() - YSI_gsStarts[i]);
				YSI_gsStarts[i] = GetTickCount() - YSI_gsStarts[i];
			}
			++YSI_gsCount;
		}
		YSI_gsStarts[i] = GetTickCount();
		Timer_CreateCallback(using inline X, 100, 50);
	}
	Timer_CreateCallback(using inline Total, 100 * 51, 1);
}

static stock y_inline_MultiClaimRel(Func:f<>)
{
	Indirect_Claim(f);
	Indirect_Claim(f);
	Indirect_Claim(f);
	Indirect_Claim(f);
	Indirect_Claim(f);
	@.f();
	Callback_Restore(f);
	Indirect_Release(f);
	Indirect_Release(f);
	Indirect_Release(f);
	Indirect_Release(f);
	Indirect_Release(f);
}

@test(.group = "y_inline") y_inline_MultiClaimRel()
{
	new a = 0;
	inline Irrelevant()
	{
		a = 1;
	}
	y_inline_MultiClaimRel(using inline Irrelevant);
	ASSERT_EQ(a, 1);
}

static stock y_inline_EBCClaimRelease(Func:f<i>)
{
	Indirect_Claim(f);
	@.f(Indirect_GetOwner(f));
	Callback_Restore(f);
	Indirect_Release(f);
	return Indirect_GetOwner(f);
}

@test(.group = "y_inline") y_inline_EBCClaimRelease()
{
	new a = 0;
	inline Irrelevant(owner)
	{
		a = owner;
	}
	new ret = 100;
	ret = y_inline_EBCClaimRelease(EBC__(ret, using inline Irrelevant));
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(a, 100);
}

static stock y_inline_EBCDontCall(Func:f<i>)
{
	Indirect_Claim(f);
	@.f(Indirect_GetOwner(f));
	Callback_Restore(f);
	@.f(Indirect_GetOwner(f));
	Callback_Restore(f);
	new id = 100;
	Indirect_Disconnect(id);
	Indirect_Disconnect(Inline_EBC__(id, tagof (id)));
	@.f(Indirect_GetOwner(f));
	Callback_Restore(f);
	Indirect_Release(f);
	return Indirect_GetOwner(f);
}

@test(.group = "y_inline") y_inline_EBCDontCall()
{
	new a = 0;
	inline Irrelevant(owner)
	{
		a = a + owner + 1;
	}
	new id = 100;
	id = y_inline_EBCDontCall(EBC__(id, using inline Irrelevant));
	ASSERT_EQ(id, 0);
	ASSERT_EQ(a, 202);
}

static stock Func:y_inline_ClaimAndReturn<i>(Func:f<i>)
{
	Indirect_Claim(f);
	return f;
}

@test(.group = "y_inline") y_inline_MultipleOwners()
{
	new
		Func:funcs<i>[20],
		owner1 = 40,
		owner2 = 33,
		total,
		Func:f<i>;
	inline const Callback(owner)
	{
		@return owner + 1;
	}

	funcs[0] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[1] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[2] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[3] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[4] = y_inline_ClaimAndReturn(EBC__(owner2, using inline Callback));
	funcs[5] = y_inline_ClaimAndReturn(EBC__(owner2, using inline Callback));
	funcs[6] = y_inline_ClaimAndReturn(EBC__(owner2, using inline Callback));

	total = 0;

	for (new i = 0; i != 7; ++i)
	{
		f = funcs[i];
		total += @.f(Indirect_GetOwner(f));
		//Callback_Restore(f);
	}

	ASSERT_EQ(total, 40 * 4 + 33 * 3 + 7);

	total = 0;

	for (new i = 0; i != 7; ++i)
	{
		if (i == 2)
		{
			Indirect_Disconnect(Inline_EBC__(owner1, tagof (owner1)));
		}
		f = funcs[i];
		total += @.f(Indirect_GetOwner(f));
		//Callback_Restore(f);
	}

	ASSERT_EQ(total, 40 * 2 + 33 * 3 + 5);

	total = 0;
	funcs[7] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[8] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));
	funcs[9] = y_inline_ClaimAndReturn(EBC__(owner1, using inline Callback));

	for (new i = 0; i != 10; ++i)
	{
		f = funcs[i];
		total += @.f(Indirect_GetOwner(f));
		//Callback_Restore(f);
	}

	ASSERT_EQ(total, 40 * 3 + 33 * 3 + 6);
}

forward y_inline_CallLaterPublic();
public y_inline_CallLaterPublic()
{
		printf("Called public later");
	
}

static stock y_inline_CallLater(Func:cb<>)
{
	Indirect_Claim(cb);
	SetTimerEx("Indirect_FromCallback", 100 + random(100), false, "ii", _:cb, true);
}

@test(.group = "y_inline") y_inline_CallLater()
{
	new a = 0;
	inline const Callback()
	{
		printf("Called inline later (%d)", a);
	}

	a = 0;
	y_inline_CallLater(using inline Callback);
	a = 1;
	y_inline_CallLater(using inline Callback);
	a = 2;
	y_inline_CallLater(using inline Callback);
	a = 3;
	y_inline_CallLater(using inline Callback);
	a = 4;
	y_inline_CallLater(using inline Callback);
	a = 5;
	y_inline_CallLater(using inline Callback);
	a = 6;
	y_inline_CallLater(using inline Callback);
	a = 7;
	y_inline_CallLater(using inline Callback);
	a = 8;
	y_inline_CallLater(using inline Callback);
	a = 9;
	y_inline_CallLater(using inline Callback);

	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
	y_inline_CallLater(using public y_inline_CallLaterPublic<>);
}

