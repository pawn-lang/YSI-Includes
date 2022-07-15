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

//#define @yH_public%0\32;%1(%2);%3(%4) HOOK_REDO__ %0%1(%2)
#define @yH_native%0\32;%1(%2);%3(%4) HOOK_REDO__ %0%1(%2)
#define @yH_stock%0\32;%1(%2);%3(%4) HOOK_REDO__ %0%1(%2)
#define @yH_function%0\32;%1(%2);%3(%4) HOOK_REDO__ %0%1(%2)

//#define HOOK_PUBLIC__%1(%2) forward UNIQUE_FUNCTION<@H_y%1@...>(%2);UNIQUE_FUNCTION<@H_y%1@...>(%2)
//#define HOOK_public__%1(%2) forward UNIQUE_FUNCTION<@H_y%1@...>(%2);UNIQUE_FUNCTION<@H_y%1@...>(%2)

#define Y_HOOKS_CONTINUE_RETURN_1	(1)		// Continue the hook chain, return 1
#define Y_HOOKS_CONTINUE_RETURN_0	(0)		// Continue the hook chain, return 0
#define Y_HOOKS_BREAK_RETURN_0		(~0)	// Break the hook chain, return 0
#define Y_HOOKS_BREAK_RETURN_1		(~1)	// Break the hook chain, return 1

#if !defined MAX_HOOK_REPLACEMENTS
	#define MAX_HOOK_REPLACEMENTS (16)
#endif

// Generate a function name using only ONE of the parts, so two replacements for
// the same long name will collide at compile-time.  Always packed.
#define DEFINE_HOOK_REPLACEMENT__(%0,%1); forward @_yH%0(); public @_yH%0() { _Hooks_AddReplacement(__COMPILER_PACK#%0, __COMPILER_PACK#%1); }

// Strip spaces from the generated function names.
#define @yH_%0\32; @yH_ // hook
#define @_Hy%0\32; @_Hy // extra stock/native info
#define @Hy_%0\32; @Hy_ // hook stock/native
#define @H_y%0\32; @H_y // hook public
#define @y_H%0\32; @y_H // DEFINE_HOOK_RETURN
#define @_yH%0\32; @_yH // DEFINE_HOOK_REPLACEMENT
#define _Hy@%0\32; _Hy@ // Hook implementation

#define DEFINE_HOOK_RETURN__(%0,%1); forward @y_H%0(); public @y_H%0() { return (%1); }

#if YSI_KEYWORD(HOOK_REPLACEMENT)
	#define DEFINE_HOOK_REPLACEMENT DEFINE_HOOK_REPLACEMENT__
#endif
#if YSI_KEYWORD(HOOK_RET)
	#define HOOK_RET:%0(%1) forward @y_H%0(); public @y_H%0()
#endif
#if YSI_KEYWORD(hook)
	#define hook HOOK__
#endif
#if YSI_KEYWORD(rehook)
	#define rehook HOOK__
#endif
#if YSI_KEYWORD(Hook)
	#define Hook:%0_%1(%2) forward public @yH_%1@%0(%2);@yH_%1@%0(%2)
#endif

// Decorator syntax.
#define @yH_%0\32; @yH_ // hook
#define ADDRMKCL_%0\32; ADDRMKCL_ // Named parameters.

// Tags.
#define @yH_Float: Float:@yH_
#define @yH_File: File:@yH_
#define @yH_bool: bool:@yH_
#define @yH_void: void:@yH_
#define @yH_string: string:@yH_

#define ADDRESSOF_MAKE_CALL__%0(%1) FUNC_PARSER(ADDRMKCL,ARR:NUM_TAG:REF_TAG:)(%0(%1))()(#)

#define ADDRMKCL_ARR(%0,%1,%2,%4)%8$(%6)(%7) %8$(%6,__ARR)(%7a)
#define ADDRMKCL_NUM(%0,%1,%2)%8$(%6)(%7) %8$(%6,%10)(%7i)
#define ADDRMKCL_REF(%0,%1,%2)%8$(%6)(%7) %8$(%6,%1__REF)(%7i)

#define ADDRMKCL_NUL(%0)%8$()(#) ADDRMKCL_END(%0)%8$(,)(#)
// I don't actually need the tag, this is purely internal.
#define ADDRMKCL_END(%0)%8$(,%6)(#%7)return%9_Hooks_AddPublicHook(, ADDRMKCL:%8$UNIQUE_FUNCTION<@yH_%0@...>()return _Hooks_AddPublicHook(O@A_()?(((_:%0(%6)),O@V_)?1:2):(O@V_),

#if __COMPILER_STRING_PACKING
	#define @hook(%0)%1(%2) UNIQUE_FUNCTION<@yH_%1@...>();UNIQUE_FUNCTION<%1@...>(%2);ADDRESSOF_MAKE_CALL__ %1(%2)return _Hooks_AddPublicHook(,_:"\"%1\"",%0);static %1(%2)
	#define ADDRMKCL_callback:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,%6)
	#define ADDRMKCL_fallback1__:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,%9);static%6(%7) %8$UNIQUE_FUNCTION<@yH_%6@...>()return _Hooks_AddPublicHook(O@A_()?(((_:UNIQUE_FUNCTION<%6@...>(%2))%3)%4):%5,"\"%6\"",.fallback=true);static UNIQUE_FUNCTION<%6@...>(%7)
#else
	#define @hook(%0)%1(%2) UNIQUE_FUNCTION<@yH_%1@...>();UNIQUE_FUNCTION<%1@...>(%2);ADDRESSOF_MAKE_CALL__ %1(%2)return _Hooks_AddPublicHook(,_:!"\"%1\"",%0);static %1(%2)
	#define ADDRMKCL_callback:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,!%6)
	#define ADDRMKCL_fallback1__:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,%9);static%6(%7) %8$UNIQUE_FUNCTION<@yH_%6@...>()return _Hooks_AddPublicHook(O@A_()?(((_:UNIQUE_FUNCTION<%6@...>(%2))%3)%4):%5,!"\"%6\"",.fallback=true);static UNIQUE_FUNCTION<%6@...>(%7)
#endif

#define ADDRMKCL:%8$%0(%1)%2(%3,%4,.%5=%6) ADDRMKCL_%5:%8$%0(%1)%2(%3,%4,%6)
#define ADDRMKCL_order:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,.order=%6)
#define ADDRMKCL_fallback:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,.fallback=%6)
//#define ADDRMKCL_fallback1__:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,.fallback=%6)

#define ADDRMKCL_stock:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6()return _Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)
#define ADDRMKCL_native:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6()return _Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)
#define ADDRMKCL_function:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6()return _Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)

#define ADDRMKCL_fallback2__:%8$%6()%9(%0?(((%1(%2))%3)%4):%5,%9,%9) %8$%6()return _Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)

// Upgrade the old version to the new version, with only defaults.
#define HOOK__%0(%1) @hook(.fallback1__=true)%0(%1)
//#define HOOK_PUBLIC__%0(%1) @hook()%0(%1)
//#define HOOK_CALLBACK__%0(%1) @hook()%0(%1)
//
//#define HOOK_STOCK__%0(%1) @hook(.fallback2__=%0)%0(%1)
//#define HOOK_NATIVE__%0(%1) @hook(.fallback2__=%0)%0(%1)
//#define HOOK_FUNCTION__%0(%1) @hook(.fallback2__=%0)%0(%1)

#define REHOOK__%0(%1) static UNIQUE_FUNCTION<%0@...>(%1)

