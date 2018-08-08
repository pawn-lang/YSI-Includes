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

#define @yH_public%0\32;%1(%2);%3(%4) @yH_%0%1(%2);@yH_%0%1(%2)
#define @yH_native%0\32;%1(%2);%3(%4) @Hy_%0%1(%2);@Hy_%0%1(%2)

#define HOOK__%1(%2) forward UNIQUE_FUNCTION<@yH_%1@...>(%2);UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define REHOOK__ HOOK__

// Strip out extra spaces (nicely recursive)
#define @yH_%0\32; @yH_

#define Y_HOOKS_CONTINUE_RETURN_1	(1)		// Continue the hook chain, return 1
#define Y_HOOKS_CONTINUE_RETURN_0	(0)		// Continue the hook chain, return 0
#define Y_HOOKS_BREAK_RETURN_0		(-1)	// Break the hook chain, return 0
#define Y_HOOKS_BREAK_RETURN_1		(-2)	// Break the hook chain, return 1

#if !defined MAX_HOOK_REPLACEMENTS
	#define MAX_HOOK_REPLACEMENTS (16)
#endif

// Generate a function name using only ONE of the parts, so two replacements for
// the same long name will collide at compile-time
#define DEFINE_HOOK_REPLACEMENT__(%0,%1); forward @_yH%0(); public @_yH%0() { _Hooks_AddReplacement(#%0, #%1); }

// Strip spaces from the generated function name.
#define @_yH%0\32; @_yH
#define @y_H%0\32; @y_H

#define DEFINE_HOOK_RETURN__(%0,%1); forward @y_H%0(); public @y_H%0() { return (%1); }

#if defined YSI_COMPAT || defined KEYWORD_DEFINE_HOOK_REPLACEMENT
	#define DEFINE_HOOK_REPLACEMENT DEFINE_HOOK_REPLACEMENT__
#endif

#if defined YSI_COMPAT || defined KEYWORD_HOOK_RET
	#define HOOK_RET:%0(%1) forward @y_H%0(); public @y_H%0()
#endif
#if defined YSI_COMPAT || defined KEYWORD_hook
	#define hook HOOK__
#endif
#if defined YSI_COMPAT || defined KEYWORD_rehook
	#define rehook HOOK__
#endif
#if defined YSI_COMPAT || defined KEYWORD_Hook
	#define Hook:%0_%1(%2) forward public @yH_%1@%0(%2);@yH_%1@%0(%2)
#endif

