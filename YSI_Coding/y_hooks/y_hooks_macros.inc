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

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           

*/

//#define Y_HOOKS_ADDRESSOF(%0(%1)) (I@=((O@D_:O@A_())?(((_:%0(%1)),O@V_)?1:2):(O@V_)),printf("Y_HOOKS_ADDRESSOF = %08x", I@),I@)
#define Y_HOOKS_ADDRESSOF(%0(%1)) (O@D_:O@A_())?(((_:%0(%1)),O@V_)?1:2):(O@V_)

//#define @yH_public%0\32;%1(%2);%3(%4) HOOK_REDO__ %0%1(%2)
#define _@yHnative%9(%9);ADDRESSOF_MAKE_CALL__%9native%1(%2)%9;%9(%9) HOOK_NATIVE__%1(%2)
#define _@yHstock%9(%9);ADDRESSOF_MAKE_CALL__%9stock%1(%2)%9;%9(%9) HOOK_NATIVE__%1(%2)
#define _@yHfunction%9(%9);ADDRESSOF_MAKE_CALL__%9function%1(%2)%9;%9(%9) HOOK_NATIVE__%1(%2)

//#define HOOK_PUBLIC__%1(%2) forward UNIQUE_FUNCTION<@H_y%1@...>(%2);UNIQUE_FUNCTION<@H_y%1@...>(%2)
//#define HOOK_public__%1(%2) forward UNIQUE_FUNCTION<@H_y%1@...>(%2);UNIQUE_FUNCTION<@H_y%1@...>(%2)

/*
// We can't deprecate defines or constants, only functions.
#pragma deprecated Use `return 0;`.
stock Y_HOOKS_CONTINUE_RETURN_0()
{
	return 0;
}

// Matches `\10;` to avoid a double replacement, so we can use the same name for
// both the macro and the function, to give a nicer warning message.
#define Y_HOOKS_CONTINUE_RETURN_0%0\10; Y_HOOKS_CONTINUE_RETURN_0()%0

// We can't deprecate defines or constants, only functions.
#pragma deprecated Use `return 1;`.
stock Y_HOOKS_CONTINUE_RETURN_1()
{
	return 1;
}

// Matches `\10;` to avoid a double replacement, so we can use the same name for
// both the macro and the function, to give a nicer warning message.
#define Y_HOOKS_CONTINUE_RETURN_1%0\10; Y_HOOKS_CONTINUE_RETURN_1()%0

// We can't deprecate defines or constants, only functions.
#pragma deprecated Use `return ~0;`.
stock Y_HOOKS_BREAK_RETURN_0()
{
	return ~0;
}

// Matches `\10;` to avoid a double replacement, so we can use the same name for
// both the macro and the function, to give a nicer warning message.
#define Y_HOOKS_BREAK_RETURN_0%0\10; Y_HOOKS_BREAK_RETURN_0()%0

// We can't deprecate defines or constants, only functions.
#pragma deprecated Use `return ~1;`.
stock Y_HOOKS_BREAK_RETURN_1()
{
	return ~1;
}

// Matches `\10;` to avoid a double replacement, so we can use the same name for
// both the macro and the function, to give a nicer warning message.
#define Y_HOOKS_BREAK_RETURN_1%0\10; Y_HOOKS_BREAK_RETURN_1()%0
*/

// Apparently people like these.
#define Y_HOOKS_CONTINUE_RETURN_0 (0)
#define Y_HOOKS_CONTINUE_RETURN_1 (1)
#define Y_HOOKS_BREAK_RETURN_0 (~0)
#define Y_HOOKS_BREAK_RETURN_1 (~1)

#if !defined MAX_HOOK_REPLACEMENTS
	#define MAX_HOOK_REPLACEMENTS (16)
#endif

// Generate a function name using only ONE of the parts, so two replacements for
// the same long name will collide at compile-time.  Always packed.
#define DEFINE_HOOK_REPLACEMENT__(%0,%1); forward _F<@_yH>%0(); public _F<@_yH>%0() { _Hooks_AddReplacement(__COMPILER_PACK#%0, __COMPILER_PACK#%1); }

// Strip spaces from the generated function names.
#define @yH_%0\32; @yH_ // @hook entry point
#define @_Hy%0\32; @_Hy // unused
#define @Hy_%0\32; @Hy_ // hook stock/native
#define _@yH%0\32; _@yH // hook stock/native
#define @H_y%0\32; @H_y // hook public
#define @y_H%0\32; @y_H // DEFINE_HOOK_RETURN
#define @_yH%0\32; @_yH // DEFINE_HOOK_REPLACEMENT

// And in 64-bit
#define @yH_0000%0\32; @yH_0000 // @hook entry point
#define @_Hy0000%0\32; @_Hy0000 // unused
#define @Hy_0000%0\32; @Hy_0000 // hook stock/native
#define _@yH0000%0\32; _@yH0000 // hook stock/native
#define @H_y0000%0\32; @H_y0000 // hook public
#define @y_H0000%0\32; @y_H0000 // DEFINE_HOOK_RETURN
#define @_yH0000%0\32; @_yH0000 // DEFINE_HOOK_REPLACEMENT

// Tags.
#define @yH_Float: Float:@yH_
#define @yH_File: File:@yH_
#define @yH_bool: bool:@yH_
#define @yH_void: void:@yH_
#define @yH_string: string:@yH_

#define DEFINE_HOOK_RETURN__(%0,%1); forward _F<@y_H>%0(); public _F<@y_H>%0() { return (%1); }

#if YSI_KEYWORD(HOOK_REPLACEMENT)
	#define DEFINE_HOOK_REPLACEMENT DEFINE_HOOK_REPLACEMENT__
#endif
#if YSI_KEYWORD(HOOK_RET)
	#define HOOK_RET:%0(%1) forward _F<@y_H>%0(); public _F<@y_H>%0()
#endif
#if YSI_KEYWORD(hook)
	#define hook HOOK__
#endif
#if YSI_KEYWORD(rehook)
	#define rehook REHOOK__
#endif
#if YSI_KEYWORD(Hook)
	#define Hook:%0_%1(%2) forward public _F<@yH_>%1@%0(%2);_F<@yH_>%1@%0(%2)
#endif

// Decorator syntax.
#define YHLEG_%0\32; YHLEG_ // Named parameters.

#define ADDRESSOF_MAKE_CALL__%0(%1) FUNC_PARSER(YHLEG,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:RET_TAG:)(%0(%1))()()()(1,0)

//#define YHLEG_ARR(%0,%1,%2,%9)%8$(%6)(%9,%4) %8$(%6,__ARR)(%9+1,%4)
//#define YHLEG_NUM(%0,%1,%2)%8$(%6)(%9,%4) %8$(%6,%10)(%9+1,1<<%9|%4)
//#define YHLEG_REF(%0,%1,%2)%8$(%6)(%9,%4) %8$(%6,%1__REF)(%9+1,%4)
//#define YHLEG_EXT(%0,%1,%2)%8$(%6)(%9,%4) %8$(%6)(%7)

//#define YHLEG_NUL(%0)%8$()(1,0) YHLEG_END(%0)%8$(,)(1,0)
//#define YHLEG_NUL(%0)%8$()(1,0) YHLEG_END(%0)%8$(,)(1,0)
// I don't actually need the tag, this is purely internal.
//#define YHLEG_END(%0)%8$(,%6)(%9,%4)return%9(, YHLEG:%8$YHNPS_U1<%0>()return _@Hy(Y_HOOKS_ADDRESSOF(%0(%6)),

#define @hook(%0)%1(%2) YHNPS_U0<%1>(%2);ADDRESSOF_MAKE_CALL__ %1(%2)return _@Hy(,_:__COMPILER_PACK"\"%1\"",%0);public YHNPS_U0<%1>(%2)

#define YHLEG:%8$%0(%1);%0(%1)%2(%3,%4,.%5=%6) YHLEG_%5:%8$%0(%1);%0(%1)%2(%3,%4,%6)
#define YHLEG_callback:%8$%0(%1);%0(%1)%2(%3,%4,%6) %8$%0(%1);%0(%1)%2(%3,%4,__COMPILER_PACK%6)
#define YHLEG_public:%8$%0(%1);%0(%1)%2(%3,%4,%6) %8$%0(%1);%0(%1)%2(%3,%4,__COMPILER_PACK%6)
#define YHLEG_order:%8$%0(%1);%0(%1)%2(%3,%4,%6) %8$%0(%1);%0(%1)%2(%3,%4,.order=%6)
#define YHLEG_fallback:%8$%0(%1);%0(%1)%2(%3,%4,%6) %8$%0(%1);%0(%1)%2(%3,%4,.fallback=%6)
//#define YHLEG_fallback1__:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,.fallback=%6)
//#define YHLEG_fallback:%8$%6(%7)%9(%9$Y_HOOKS_ADDRESSOF(%1(%2)),%9,%9);public%9YHNPS_U0<%6>(%7) %8$YHNPS_U1<%6>(%7)return _@Hy(Y_HOOKS_ADDRESSOF(YHNPS_U0<%6>(%2)),__COMPILER_PACK"\"%6\"",.fallback=true);public YHNPS_U0<%6>(%7)

//return _yH@(%4,Y_HOOKS_ADDRESSOF(YHNPS_U0<%0>(%6))),%0(%6);%7YHNPS_U0<%0>(%5)
#define YHLEG_stock:%8$%6(%7);%6(%7)%9(PP_DISCARD%4(%3)$Y_HOOKS_ADDRESSOF(%1(%2)),%9,"%9"%5);public %8$%6(%7);%6(%7)return _yH@(%4,Y_HOOKS_ADDRESSOF(%1(%2))%5),%9(%3);static
#define YHLEG_native:%8$%6(%7);%6(%7)%9(PP_DISCARD%4(%3)$Y_HOOKS_ADDRESSOF(%1(%2)),%9,"%9"%5);public %8$%6(%7);%6(%7)return _yH@(%4,Y_HOOKS_ADDRESSOF(%1(%2))%5),%9(%3);static
#define YHLEG_function:%8$%6(%7);%6(%7)%9(PP_DISCARD%4(%3)$Y_HOOKS_ADDRESSOF(%1(%2)),%9,"%9"%5);public %8$%6(%7);%6(%7)return _yH@(%4,Y_HOOKS_ADDRESSOF(%1(%2))%5),%9(%3);static

// Upgrade the old version to the new version, with only defaults.
#define HOOK__%0(%1) @hook(.fallback=true)%0(%1)
//#define HOOK_PUBLIC__%0(%1) @hook()%0(%1)
//#define HOOK_CALLBACK__%0(%1) @hook()%0(%1)
//
//#define HOOK_STOCK__%0(%1) @hook(.fallback2__=%0)%0(%1)
//#define HOOK_NATIVE__%0(%1) @hook(.fallback2__=%0)%0(%1)
//#define HOOK_FUNCTION__%0(%1) @hook(.fallback2__=%0)%0(%1)

#define REHOOK__%0(%1) public YHNPS_U0<%0>(%1)

#define HOOK_NATIVE__%0(%1) YHNPS_U0<%0>(%1);FUNC_PARSER(YHNPS,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:RET_TAG:)(%0(%1))()()()(1,0)static YHNPS_U0<%0>(%1)
#define HOOK_STOCK__ HOOK_NATIVE__
#define HOOK_native__ HOOK_NATIVE__
#define HOOK_stock__ HOOK_NATIVE__
#define HOOK_FUNCTION__ HOOK_NATIVE__
#define HOOK_function__ HOOK_NATIVE__

// Arrays.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4+ = Dims
#define YHLEG_ARR(%0,%1,%2,%4)%8$ YHLEG_BYREF(%0%2[%4],%2)%8$
#define YHLEG_ARR_ARR(%0,%1,%2,%4,%5)%8$ YHLEG_BYREF(%0%2[%4][%5],%2)%8$
#define YHLEG_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$ YHLEG_BYREF(%0%2[%4][%5][%6],%2)%8$

// Strings.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4  = Size
// %3  = Default (unused)
#define YHLEG_STR(%0,%1,%2,%4)%8$ YHLEG_BYREF(%0%2[%4],%2)%8$
#define YHLEG_STR_DEF(%0,%1,%2,%4,%3)%8$ YHLEG_BYREF(%0%2[%4],%2)%8$

// Varargs.
//
// %0  = `const` (unused)
// %1  = Tag
// %2  = Name (unused)
// %5  = Prototype parameters
// %6  = Call parameters
//
// This does NOT put `...` in to the function parameters with `%1...` because
// publics can't have variable arguments.  But we can still secretly pass them.
// TODO: When you put `___` back, ensure y_hooks still works when y_va is
// initialised afterwards (since `YSI_gYVA2_DoPush__` will be `0`).
#define YHLEG_EXT(%0,%1,%2)%8$(%5)(%6)(%7)(%9,%4) %8$(%5)(%6,YVA2_DummyPush((%9-1)*cellbytes))(%7)(%9,%4)

// References.
//
// %0  = `const` (unused)
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHLEG_REF(%0,%1,%2)%8$ YHLEG_BYREF(&%2,%2)%8$
#define YHLEG_REF_DEF(%0,%1,%2,%3)%8$ YHLEG_BYREF(&%2,%2)%8$

// Variables.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHLEG_NUM(%0,%1,%2)%8$ YHLEG_BYVAL(&%0%2,%2)%8$
#define YHLEG_NUM_DEF(%0,%1,%2,%3)%8$ YHLEG_BYVAL(&%0%2,%2)%8$

// Generate the parameter descriptions.
//
// %0  = Name in prototype
// %1  = Name in call
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Prefix
#define YHLEG_BYREF(%0,%1)%8$(%5)(%6)(%7)(%9,%4) %8$(%5,%0)(%6,%1)(%7,%1)(%9+1,%4)
#define YHLEG_BYVAL(%0,%1)%8$(%5)(%6)(%7)(%9,%4) %8$(%5,%0)(%6,%1)(%7,%1)(%9+1,1<<%9|%4)

// End, generate the code.
//
// %0  = Name
// %3  = Descriptor
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Return tag
// %1  = Call without `___`
#define YHLEG_END_TAG(%7,%0)%8$(,%5)(,%6)(,%1)(%9,%4)return%9(, YHLEG:%8$YHNPS_U1<%0>(%5);YHNPS_U1<%0>(%5)return _@Hy(PP_DISCARD %4(%6)$Y_HOOKS_ADDRESSOF(YHNPS_U0<%0>(%1)),
#define YHLEG_END(%0)%8$(,%5)(,%6)(,%1) YHLEG_END_TAG(,%0)%8$(,%5)(,%6)(,%1)
#define YHLEG_NUL_TAG(%7,%0)%8$()()() YHLEG_END(,%0)%8$(,)(,)(,)
#define YHLEG_NUL(%0)%8$()()() YHLEG_END(%0)%8$(,)(,)(,)

// Arrays.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4+ = Dims
#define YHNPS_ARR(%0,%1,%2,%4)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$
#define YHNPS_ARR_ARR(%0,%1,%2,%4,%5)%8$ YHNPS_BYREF(%0%2[%4][%5],%2)%8$
#define YHNPS_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$ YHNPS_BYREF(%0%2[%4][%5][%6],%2)%8$

// Strings.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4  = Size
// %3  = Default (unused)
#define YHNPS_STR(%0,%1,%2,%4)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$
#define YHNPS_STR_DEF(%0,%1,%2,%4,%3)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$

// Varargs.
//
// %0  = `const` (unused)
// %1  = Tag
// %2  = Name (unused)
// %5  = Prototype parameters
// %6  = Call parameters
//
// TODO: When you put `___` back, ensure y_hooks still works when y_va is
// initialised afterwards (since `YSI_gYVA2_DoPush__` will be `0`).
#define YHNPS_EXT(%0,%1,%2)%8$(%5)(%6)(%7)(%9,%4) %8$(%5)(%6,YVA2_DummyPush((%9-1)*cellbytes))(%7)(%9,%4)

// References.
//
// %0  = `const` (unused)
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHNPS_REF(%0,%1,%2)%8$ YHNPS_BYREF(&%2,%2)%8$
#define YHNPS_REF_DEF(%0,%1,%2,%3)%8$ YHNPS_BYREF(&%2,%2)%8$

// Variables.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHNPS_NUM(%0,%1,%2)%8$ YHNPS_BYVAL(&%0%2,%2)%8$
#define YHNPS_NUM_DEF(%0,%1,%2,%3)%8$ YHNPS_BYVAL(&%0%2,%2)%8$

// Generate the parameter descriptions.
//
// %0  = Name in prototype
// %1  = Name in call
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Prefix
#define YHNPS_BYREF(%0,%1)%8$(%5)(%6)(%7)(%9,%4) %8$(%5,%0)(%6,%1)(%7,%1)(%9+1,%4)
#define YHNPS_BYVAL(%0,%1)%8$(%5)(%6)(%7)(%9,%4) %8$(%5,%0)(%6,%1)(%7,%1)(%9+1,1<<%9|%4)

// End, generate the code.
//
// %0  = Name
// %3  = Descriptor
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Return tag
// %1  = Call without `___`
#define YHNPS_END_TAG(%7,%0)%8$(,%5)(,%6)(,%1)(%9,%4) %8$%7YHNPS_U1<%0>(%5);%7YHNPS_U1<%0>(%5)return _yH@(%4,Y_HOOKS_ADDRESSOF(YHNPS_U0<%0>(%1))),%0(%6);
#define YHNPS_END(%0)%8$(,%5)(,%6)(,%1) YHNPS_END_TAG(,%0)%8$(,%5)(,%6)(,%1)
#define YHNPS_NUL_TAG(%7,%0)%8$()()() YHNPS_END_TAG(%7,%0)%8$(,)(,)(,)
#define YHNPS_NUL(%0)%8$()()() YHNPS_END_TAG(,%0)%8$(,)(,)(,)

// Helper macro to generate the unique function name without bloating the
// generated code multiple times.
#define YHNPS_U0<%1> UNIQUE_FUNCTION<_F<_@yH>%1@...>
#define YHNPS_U1<%1> UNIQUE_FUNCTION<_F<@yH_>%1@...>

// Remove specified priorities from the original call.
#define _yH@(%0),%1@%2(%3); _yH@(%0),%1(%3);

