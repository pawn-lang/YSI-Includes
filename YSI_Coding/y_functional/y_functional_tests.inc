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

#define FUNC_CHECK_ARR(%0,%1) for (new __i = 0, __j = min(sizeof (%0), sizeof (%1)); __i != __j; ++__i) ASSERT(%0[__i] == %1[__i])

@test(.group = "y_functional") FUNC_Map1()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 2, 4, ...};
	inline const Double(x)
	{
		@return x * 2;
	}
	Map(using inline Double, a0, a0);
	FUNC_CHECK_ARR(a0, a1);
}

@test(.group = "y_functional") FUNC_Map2()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 2, 4, ...},
		a2[10] = {0, 1, 2, ...},
		a3[10];
	inline const Double(x)
	{
		@return x * 2;
	}
	Map(using inline Double, a0, a3);
	FUNC_CHECK_ARR(a0, a2);
	FUNC_CHECK_ARR(a3, a1);
}

@test(.group = "y_functional") FUNC_Map3()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {1, 4, 7, ...},
		a2[10] = {0, 1, 2, ...},
		a3[10];
	Map({_0 * 3 + 1}, a0, a3);
	FUNC_CHECK_ARR(a0, a2);
	FUNC_CHECK_ARR(a3, a1);
}

@test(.group = "y_functional") FUNC_Map_1()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	inline const Triple(x)
	{
		@return x * 3;
	}
	Map_(using inline Triple, a0);
	FUNC_CHECK_ARR(a0, a1);
}

@test(.group = "y_functional") FUNC_Map_2()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	Map_({_0 * 4}, a0);
	FUNC_CHECK_ARR(a0, a1);
}

@test(.group = "y_functional") FUNC_MapIdx()
{
	new
		a0[10] = {1, ...},
		a1[10] = {2, 4, 6, ...};
	inline const AddAndMul(idx, x)
	{
		@return (x + idx) * 2;
	}
	MapIdx(using inline AddAndMul, a0, a0);
	FUNC_CHECK_ARR(a0, a1);
}

@test(.group = "y_functional") FUNC_MapIdx_()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	inline const Thing(idx, x)
	{
		#pragma unused idx, x
		@return 42;
	}
	MapIdx_(using inline Thing, a0);
	FUNC_CHECK_ARR(a0, a1);
}

@test(.group = "y_functional") FUNC_ZipWith()
{
	new
		a0[10] = { 0,  1,  2, ...},
		a1[10] = {10, 20, 30, ...},
		a2[10],
		a3[10] = { 0, 20, 60, 120, 200, 300, 420, 560, 720, 900};
	inline const Mul(a, b) @return a * b;
	ZipWith(using inline Mul, a0, a1, a2);
	FUNC_CHECK_ARR(a2, a3);
}

@test(.group = "y_functional") FUNC_ZipWith3()
{
	new
		a0[10] = { 0,  1,  2, ...},
		a1[10] = {10, 20, 30, ...},
		a9[10] = {22, ...},
		a2[10],
		a3[10] = {22, 42, 82, 142, 222, 322, 442, 582, 742, 922};
	inline const MulAdd(a, b, c) @return a * b + c;
	ZipWith3(using inline MulAdd, a0, a1, a9, a2);
	FUNC_CHECK_ARR(a2, a3);
}

@test(.group = "y_functional") FUNC_FoldR1()
{
	new
		a0[10] = { 0,  1,  2, ...},
		ret = 0;
	ret = FoldR({_0 * _1}, a0, 10);
	ASSERT_ZE(ret);
}

@test(.group = "y_functional") FUNC_FoldR2()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldR({_0 * _1}, a0, 10);
	ASSERT_EQ(ret, 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 10);
}

@test(.group = "y_functional") FUNC_FoldL1()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldL({_0 * _1}, 11, a0);
	ASSERT_EQ(ret, 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11);
}

@test(.group = "y_functional") FUNC_FoldL_multiple()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldL({ _0 * _1 }, 11, a0) + FoldL({ _0 + _1 }, 11, a0);
	ASSERT_EQ(ret,1*2*3*4*5*6*7*8*9*10*11+1+2+3+4+5+6+7+8+9+10+11);
}

static FUNC_FoldL_nested_Add(a, b)
{
	return a + b;
}

@test(.group = "y_functional") FUNC_FoldL_params()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FUNC_FoldL_nested_Add(FoldL({ _0 * _1 }, 11, a0), FoldL({ _0 + _1 }, 11, a0));
	ASSERT_EQ(ret,1*2*3*4*5*6*7*8*9*10*11+1+2+3+4+5+6+7+8+9+10+11);
}

@test(.group = "y_functional") FUNC_FoldL_nested()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldL({ _0 * _1 }, FoldL({ _0 + _1 }, 11, a0), a0);
	ASSERT_EQ(ret,1*2*3*4*5*6*7*8*9*10*(1+2+3+4+5+6+7+8+9+10+11));
}

@test(.group = "y_functional") FUNC_FoldR3()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldR({_0 * _1}, a0, 15, 0);
	ASSERT_EQ(ret, 15);
}

@test(.group = "y_functional") FUNC_FoldL2()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret = 0;
	ret = FoldL({_0 * _1}, 99, a0, 0);
	ASSERT_EQ(ret, 99);
}

FUNC_NewLambda1(Func:f<ii>, a, b)
{
	return @.f(a, b);
}

#define FUNC_NewLambda1( @lambda(0, "ii") FUNC_NewLambda1(

FUNC_NewLambda1_(a, b)
{
	return a * 2 + b * 2;
}

@test(.group = "y_functional") FUNC_NewLambda1()
{
	new ret;
	ret = FUNC_NewLambda1({ _0 - _1 }, 100, 80);
	ASSERT_EQ(ret, 20);
	ret = FUNC_NewLambda1(&FUNC_NewLambda1_, 10, 66);
	ASSERT_EQ(ret, 152);
	inline const F(a, b)
	{
		@return b * 7 + a;
	}
	ret = FUNC_NewLambda1(using inline F, 2, 6);
	ASSERT_EQ(ret, 44);
}

FUNC_NewLambda2(const string:s[], Func:f<ii>, d)
{
	return @.f(strval(s), d);
}

#define FUNC_NewLambda2( @lambda(1, "ii") FUNC_NewLambda2(

FUNC_NewLambda2_(s, d)
{
	return s * 2 + d * 2;
}

@test(.group = "y_functional") FUNC_NewLambda2()
{
	new ret;
	ret = FUNC_NewLambda2("100", { _0 - _1 }, 70);
	ASSERT_EQ(ret, 30);
	ret = FUNC_NewLambda2("15", &FUNC_NewLambda2_, 66);
	ASSERT_EQ(ret, 162);
	inline const F(s, d)
	{
		@return d * 7 + s;
	}
	ret = FUNC_NewLambda2("3", using inline F, 6);
	ASSERT_EQ(ret, 45);
}

FUNC_NewLambda3(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, const string:s[], Func:f<ii>, d)
{
	#pragma unused p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19
	return @.f(strval(s), d);
}

#define FUNC_NewLambda3( @lambda(21, "ii") FUNC_NewLambda3(

FUNC_NewLambda3_(s, d)
{
	return s * 2 + d * 2;
}

@test(.group = "y_functional") FUNC_NewLambda3()
{
	new ret;
	ret = FUNC_NewLambda3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "100", { _0 - _1 }, 70);
	ASSERT_EQ(ret, 30);
	ret = FUNC_NewLambda3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "15", &FUNC_NewLambda3_, 66);
	ASSERT_EQ(ret, 162);
	inline const F(s, d)
	{
		@return d * 7 + s;
	}
	ret = FUNC_NewLambda3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "3", using inline F, 6);
	ASSERT_EQ(ret, 45);
}

#undef FUNC_CHECK_ARR

