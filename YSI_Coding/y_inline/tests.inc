/**--------------------------------------------------------------------------**\
					===================================
					 y_inline - PAWN inline functions.
					===================================
Description:
	This library allows a user to write inline functions in their script.  It
	first detects all inline functions and generates data on them, such as
	parameter counts and addresses.  When an inline function is passed in code
	its current context data is stored.  Finally, when an inline function is
	found to be called at some point its current local stack is stored in global
	memory.  When the function actually is called, the stack is restored, and
	additional parameters which are the inline function parameters, are passed.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI Inline Function include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	1.0
Changelog:
	22/06/13:
		Rewrote the library from scratch for better performance all round.
	20/10/12:
		Fixed a bug with "Callback_Release" with public functions.
	15/11/11:
		Changed the precedence of "using" types.
	19/09/11:
		First version
\**--------------------------------------------------------------------------**/

static stock bool:y_inline_Get(callback:c, ret[E_CALLBACK_DATA], f[] = "")
{
	return Callback_Get(c, ret, f);
}

static stock bool:y_inline_Restore(ret[E_CALLBACK_DATA])
{
	Callback_Restore(ret);
}

Test:y_inline1()
{
	new
		cc[E_CALLBACK_DATA];
	inline func()
	{
		@return 42;
	}
	//printf("%d %d %d %d %d", func[0], func[1], func[2], func[3], func[4]);
	y_inline_Get(using inline func, cc);
	ASSERT(Callback_Call(cc) == 42);
	Callback_Release(cc);
}

Test:y_inline2()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(a)
	{
		@return a;
	}
	y_inline_Get(using inline func, cc);
	ASSERT(Callback_Call(cc, 50) == 50);
	Callback_Release(cc);
}

Test:y_inline3()
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
	ASSERT(r == 99);
	Callback_Release(cc);
}

Test:y_inline4()
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
	ASSERT(r == 100);
	Callback_Release(cc);
}

Test:y_inline5()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(a, b, c, d)
	{
		ASSERT(a == 1);
		ASSERT(b == 11);
		ASSERT(c == 111);
		ASSERT(d == 1111);
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc, 1, 11, 111, 1111);
	Callback_Release(cc);
}

Test:y_inline6()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(string:g[])
	{
		#if !(sizeof (g) == YSI_MAX_STRING))
			#error sizeof (g) != YSI_MAX_STRING
		#endif
		ASSERT(!strcmp(g, "hello"));
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
}

Test:y_inline7b()
{
	new
		cc[E_CALLBACK_DATA];
	inline func7b()
	{
	}
	ASSERT(y_inline_Get(using func7a, cc) == false);
	ASSERT(y_inline_Get(using func7b, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(using public y_inline7a, cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"func7b", cc));
	Callback_Release(cc);
	ASSERT(y_inline_Get(callback_tag:"y_inline7a", cc));
	Callback_Release(cc);
}

Test:y_inline8()
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
			ASSERT(y_inline_Get(using func8a, cc) == false);
			ASSERT(y_inline_Get(using func8b, cc));
			Callback_Release(cc);
			ASSERT(y_inline_Get(using public y_inline8, cc) == false);
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

Test:y_inline9()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(using public y_inline9, cc, _F<i>));
	ASSERT(Callback_Call(cc, 67) == 12345 + 67);
	Callback_Release(cc);
}

forward y_inline10(a, b[]);

public y_inline10(a, b[])
{
	return 12345 + a + b[0];
}

Test:y_inline10()
{
	new
		cc[E_CALLBACK_DATA];
	ASSERT(y_inline_Get(using callback y_inline10, cc, _F<is>));
	ASSERT(Callback_Call(cc, 67, "50") == 12345 + 67 + '5');
	Callback_Release(cc);
}

Test:y_inline11()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline func()
	{
		g = 11;
	}
	y_inline_Get(using inline func, cc);
	ASSERT(g == 5);
	Callback_Call(cc);
	ASSERT(g == 5);
	y_inline_Restore(cc);
	ASSERT(g == 11);
	Callback_Release(cc);
}

Test:y_inline12()
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
	ASSERT(g == 9);
	Callback_Release(cc);
}

Test:y_inline13()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline const func()
	{
		ASSERT(g == 5);
		++g;
	}
	y_inline_Get(using inline func, cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	Callback_Call(cc);
	y_inline_Restore(cc);
	ASSERT(g == 5);
	Callback_Release(cc);
}

Test:Callback_AA()
{
	new
		cc[E_CALLBACK_DATA];
	inline func(&a)
	{
		// printf("a2 = %d", a);
		a = 7;
		// printf("a3 = %d", a);
		#pragma unused a
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	// printf("%x", cc[E_CALLBACK_DATA_POINTER]);
	// printf("a1 = %d", a);
	Callback_Call(cc, a);
	// printf("a4 = %d", a);
	ASSERT(a == 7);
}

Test:Callback_Arr1()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(&a)
	{
		// printf("a2 = %d", a);
		ASSERT(a == 0);
		a = 7;
		ASSERT(a == 7);
		// printf("a3 = %d", a);
		//#pragma unused a
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	// printf("%x", cc[E_CALLBACK_DATA_POINTER]);
	// printf("a1 = %d", a);
	ASSERT(a == 0);
	Callback_Call(cc, a);
	// printf("a4 = %d", a);
	ASSERT(a == 7);
}

Test:Callback_Arr2()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(string:str[])
	{
		ASSERT(!strcmp(str, "hello"));
	}
	y_inline_Get(using inline func, cc);
	new
		str[YSI_MAX_STRING] = "hello";
	Callback_Call(cc, str);
	ASSERT(!strcmp(str, "hello"));
	Callback_Call(cc, "hello");
}

Test:Callback_Arr3()
{
	new
		cc[E_CALLBACK_DATA];
	inline const func(a)
	{
		ASSERT(a == 0);
		a = 7;
		ASSERT(a == 7);
	}
	y_inline_Get(using inline func, cc);
	new
		a = 0;
	ASSERT(a == 0);
	Callback_Call(cc, a);
	ASSERT(a == 0);
}

Test:Callback_Array0()
{
	new
		g = 5,
		cc[E_CALLBACK_DATA];
	inline const func()
	{
		ASSERT(g == 5);
		++g;
	}
	y_inline_Get(using inline func, cc);
	// Test zero parameter calls.
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
	Callback_Array(cc, "", 0);
}

Test:Callback_Array1()
{
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	#emit LCTRL 6
	new
		cc[E_CALLBACK_DATA];
	inline const func(&a, string:b[], c)
	{
		//printf("%d %s", c, b);
		ASSERT(c == 6);
		ASSERT(!strcmp(b, "hey"));
		a = 7;
		#pragma unused a
	}
	//DisasmDump("inline6.asm");
	y_inline_Get(using inline func, cc);
	new
		a = 0,
		str[4] = "hey",
		c = 6,
		pars[3];
	Callback_Call(cc, a, str, c);
	ASSERT(a == 7);
	pars[0] = ref(a);
	pars[1] = ref(str);
	pars[2] = ref(c);
	// Test more parameters.
	a = 2;
	Callback_Array(cc, pars, 3);
	ASSERT(a == 7);
	a = 11;
	Callback_Array(cc, pars, 3);
	ASSERT(a == 7);
	a = 32;
	Callback_Array(cc, pars, 3);
	ASSERT(a == 7);
}

Test:y_inline_Remote0()
{
	//printf("%08x %08x", 42, 43);
	new
		Function:f0 = GetRemoteFunction("MyTesterFunc", "m"),
		Function:f1 = GetRemoteFunction("MyTesterFunc", "m");
	ASSERT(f0 == f1);
	//printf("%08x %08x", f0, f1);
	ASSERT(GetRemoteFunction("MyTesterFunc", "m") != GetRemoteFunction("MyTesterFunc", "n"));
}

static stock
	YSI_g_sRemoteTestVar;

forward y_inline_Remote1(v);

public y_inline_Remote1(v)
{
	YSI_g_sRemoteTestVar = v;
	return v - 10;
}

Test:y_inline_Remote1()
{
	new
		ret;
	
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
	ASSERT(ret == 64);
	ASSERT(YSI_g_sRemoteTestVar == 74);
	
	ret = CallRemoteFunction(!"y_inline_Remote1", "i", 75);
	ASSERT(ret == 65);
	ASSERT(YSI_g_sRemoteTestVar == 75);
	
	ret = CallRemoteFunction("y_inline_Remote1", !"i", 76);
	ASSERT(ret == 66);
	ASSERT(YSI_g_sRemoteTestVar == 76);
	
	ret = CallRemoteFunction("y_inline_Remote1", "i", 77);
	ASSERT(ret == 67);
	ASSERT(YSI_g_sRemoteTestVar == 77);
}

Test:y_inline_Remote2()
{
	YSI_g_sRemoteTestVar = 5;
	new
		Function:f = GetRemoteFunction("y_inline_Remote1", "i");
	
	YSI_g_sRemoteTestVar = 5;
	ASSERT(CallStoredFunction(f, 99) == 89);
	ASSERT(YSI_g_sRemoteTestVar == 99);
	ASSERT(CallStoredFunction(f, 111) == 101);
	ASSERT(YSI_g_sRemoteTestVar == 111);
	ASSERT(CallStoredFunction(f, 9739) == 9729);
	ASSERT(YSI_g_sRemoteTestVar == 9739);
	ASSERT(CallStoredFunction(f, 11) == 1);
	ASSERT(YSI_g_sRemoteTestVar == 11);
	ASSERT(CallStoredFunction(f, 9) == -1);
	ASSERT(YSI_g_sRemoteTestVar == 9);
}

Test:CallStoredFunction0()
{
	ASSERT(CallStoredFunction(Function:0) == 0);
}

