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

static stock y_inline_Get(callback:c, ret[E_CALLBACK_DATA])
{
	Callback_Get(c, ret);
}

Test:y_inline1()
{
	new
		cc[E_CALLBACK_DATA];
	inline func()
	{
		@return 42;
	}
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
