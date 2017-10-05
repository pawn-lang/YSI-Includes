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

#define inline%0(%1) static %0[_:I@E:32]=#%0":....";if(I@E(_:_YI@CP:%0))for(new%1,,;I@F();)while(I@L(I@K(1)))

#define I@E:32]=#%9const%7\32;%8":....";if(I@E(_:_YI@CP:%9const%7\32;%8))for(%1)while(I@L(I@K(1))) 32]=#%8":....";if(I@E(_:_YI@CP:%8))for(%1)while(I@L(I@K()))

#define _YI@CP:%8))for(new%0,%1; @Ia:@Ib:@Ic:@Id:@Iz:%8))for(new|||%0|||%1;

// Detect 0 parameters.
#define @Ia:@Ib:@Ic:@Id:@Iz:%8))for(new||||||,; %8))for(;

// Detect arrays.  Get the size, defaulting to YSI_MAX_STRING (passing cellmax).
#define @Ib:@Ic:@Id:@Iz:%8))for(new%0|||%2[%3]|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2[_:@Iy:%3]|||%4|||%5;I@F();)while(I@L(%7,@Ix&&&sizeof %2&&&))
#define @Iy:]%0)while(I@L(%1&&&%2&&&%3)) YSI_MAX_INLINE_STRING]%0)while(I@L(%1%3))
#define @Ix&&&%0&&& %0 // Remove this variable when the size is used correctly.

// Default for passing strings, not arrays.
stock const
	@Ix = cellmax;

// Detect references.
#define @Ic:@Id:@Iz:%8))for(new%0|||%1&%2|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2|||%4|||%5;I@F();)while(I@L(%7,-1))

// Detect normal variables.
#define @Id:@Iz:%8))for(new%0|||%2|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2|||%4|||%5;I@F();)while(I@L(%7,0))

// Detect end of line.
#define @Iz:%8))for(new%1,%0||||||; %8))for(new %0;

// Drop support for anonymous functions.
#define anonymous%0(%1) anonymous_no_longer_supported;for(new %1;FALSE;)

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

// Defer adding the close bracket till after other macros have run.
#define _Y_INLINE_END )

