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

#if 0

// This:
inline func(a, &b, c[100])
{
	// Inline function code.
}

// Becomes:
static const func[]="func:.....";if(I@E(func))for(new a, b, c[100];I@F();)while(I@L(0,-1,100))
{
	// Inline function code.
}

// Which is:
static const
	func[] = "func:.....";

if (I@E(func))
{
	for (new a, b, c[100]; I@F(); )
	{
		while (I@L(0, -1, 100))
		{
			// Inline function code.
		}
	}
}

// Translated:
static const
	func[] = "func\02;" #FUNC_ADDRESS #PARAMETERS #INTERNAL_RETURN #PREVIOUS_FUNC_NAME #PARENT_SCOPE_START;

if (Inline_Entry(func))
{
	for (new a, b, c[100]; Inline_Allocator(); )
	{
		while (Inline_Main(INLINE_TYPE_VAR, INLINE_TYPE_REF, INLINE_TYPE_ARR(100)))
		{
			// Inline function code.
		}
	}
}

// Run-time modified to something like:
goto somewhere_after_this_func;
func(parent, parameteters, a, b, c[100])
{
	new parent, local, variables;
	// Inline function code.
}
// Multiple inlines in a row are combined in to one big jump.
somewhere_after_this_func:

#endif

#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0|||,0|||<%9>{%0}(%1)%8;
#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1|||,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2|||,0,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3|||,0,0,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3,_4|||,0,0,0,0,0|||<%9>{%0}(%1)%8;

#define _DO_LAMBDA|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{LAM@1();static const YSII[]="@:....";if(I@E(YSII))for(%6;I@F();)while(I@L(I@K()%5))YSI_gInlineRet+=(%0);LAM@2(%9(callback_tag:YSII%1));}

// Make sure there's a space after the "return".
#define return%0({%1}%2)%3; I@=%0({%1}%2)%3;return I@;

// The "INLINE" in the types here will override "PARSER@" to "PARSE@INLINE",
// because there is no colon (well not "because", but it helps).
#define inline%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()1()

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define PARSER@INLINE:%0(%5)%6(%7)$ static %6[_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(%3,cellmax)
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[%9])%1(%3,%9)
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(%3,0)
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(%3,-1)

#define INLINE_END(%9)%8$(,%0)%1(%3) %8$#%9":....";if (I@E(%9))for(new %0;I@F();)while(I@L(I@K(%1)%3))

#define INLINE_NUL(%9)%8$()%1() %8$#%9":....";if (I@E(%9))for(;I@F();)while(I@L(I@K(%1)))

#define I@O$ 32]=

#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)(%2)

// Parameter type for passing callbacks about.
#define callback:%0) const callback_tag:callback_check:%0$$$
#define callback_tag:callback_check:%0,%1$$$ callback_tag:%0[],%1)
#define callback_check:%0$$$ %0[])

#define using%0\10;%1 callback_tag:@Ik:@Il:%0

// Get ONLY this ONE parameter (this is a VERY important stage)!
#define @Ik:@Il:%0, @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||,
#define @Il:%0) @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||)

#define @Ip:%9|||%0callback%1||| @Ir:@Is:"\03;"#%1||||
#define @Iq:%9|||%0public%1||| @Ir:@Is:"\03;"#%1||||
#define @Io:%9|||%0inline%1||| @In:@It:%0%1||||
#define @Iu:%9|||%0resolved%1||| @In:@It:%1[E_CALLBACK_DATA:0]||||
#define @Iw:|||%1||| @In:@It:#%1||||

// Callbacks with "On" in the name (often overidden by y_hooks and ALS).
#define @Ir:@Is:%0On%1|||| @In:@It:%0"On"#%1||||
#define @Is:%0|||| @In:@It:#%0|||| //Using_unknown_callback

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:@It:%0(%1)%3||||%2) %0%3%2,.bExtra=true,.extra=%1)
#define @It:%0|||| %0

