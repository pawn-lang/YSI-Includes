/*+
 * <library
 *   name="y_unique"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Defines a symbol differently every time it is included."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

#define _Y_UNIQUE_INCLUDED

#if defined _inc_y_unique_entry
	#undef _inc_y_unique_entry
#endif

#if defined UNIQUE_FUNCTION
	#undef UNIQUE_FUNCTION
#endif

// The "static stock const" values are used for debugging, since they will show
// up in preprocessed dumps ("-l") with the value of "UNIQUE_SYMBOL" at that
// moment, instead of its final value.
#if defined UNIQUE_SYMBOL
	#if UNIQUE_SYMBOL < 0 || UNIQUE_SYMBOL >= 64 * 64 * 64 - 1
		static stock const UNIQUE_SYMBOL_TOO_LARGE = UNIQUE_SYMBOL;
		#error UNIQUE_SYMBOL out of range.
	#endif

	#if UNIQUE_SYMBOL < (32767)
		#if UNIQUE_SYMBOL < (4095)
			static stock const UNIQUE_SYMBOL_LESS_THAN_004095 = UNIQUE_SYMBOL;
			#include "y_unique_000000_004095"
			#endinput
		#if UNIQUE_SYMBOL < (8191)
			static stock const UNIQUE_SYMBOL_LESS_THAN_008191 = UNIQUE_SYMBOL;
			#include "y_unique_004096_008191"
			#endinput
		#if UNIQUE_SYMBOL < (12287)
			static stock const UNIQUE_SYMBOL_LESS_THAN_012287 = UNIQUE_SYMBOL;
			#include "y_unique_008192_012287"
			#endinput
		#if UNIQUE_SYMBOL < (16383)
			static stock const UNIQUE_SYMBOL_LESS_THAN_016383 = UNIQUE_SYMBOL;
			#include "y_unique_012288_016383"
			#endinput
		#if UNIQUE_SYMBOL < (20479)
			static stock const UNIQUE_SYMBOL_LESS_THAN_020479 = UNIQUE_SYMBOL;
			#include "y_unique_016384_020479"
			#endinput
		#if UNIQUE_SYMBOL < (24575)
			static stock const UNIQUE_SYMBOL_LESS_THAN_024575 = UNIQUE_SYMBOL;
			#include "y_unique_020480_024575"
			#endinput
		#if UNIQUE_SYMBOL < (28671)
			static stock const UNIQUE_SYMBOL_LESS_THAN_028671 = UNIQUE_SYMBOL;
			#include "y_unique_024576_028671"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_032767 = UNIQUE_SYMBOL;
			#include "y_unique_028672_032767"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (65535)
		#elseif UNIQUE_SYMBOL < (36863)
			static stock const UNIQUE_SYMBOL_LESS_THAN_036863 = UNIQUE_SYMBOL;
			#include "y_unique_032768_036863"
			#endinput
		#elseif UNIQUE_SYMBOL < (40959)
			static stock const UNIQUE_SYMBOL_LESS_THAN_040959 = UNIQUE_SYMBOL;
			#include "y_unique_036864_040959"
			#endinput
		#elseif UNIQUE_SYMBOL < (45055)
			static stock const UNIQUE_SYMBOL_LESS_THAN_045055 = UNIQUE_SYMBOL;
			#include "y_unique_040960_045055"
			#endinput
		#elseif UNIQUE_SYMBOL < (49151)
			static stock const UNIQUE_SYMBOL_LESS_THAN_049151 = UNIQUE_SYMBOL;
			#include "y_unique_045056_049151"
			#endinput
		#elseif UNIQUE_SYMBOL < (53247)
			static stock const UNIQUE_SYMBOL_LESS_THAN_053247 = UNIQUE_SYMBOL;
			#include "y_unique_049152_053247"
			#endinput
		#elseif UNIQUE_SYMBOL < (57343)
			static stock const UNIQUE_SYMBOL_LESS_THAN_057343 = UNIQUE_SYMBOL;
			#include "y_unique_053248_057343"
			#endinput
		#elseif UNIQUE_SYMBOL < (61439)
			static stock const UNIQUE_SYMBOL_LESS_THAN_061439 = UNIQUE_SYMBOL;
			#include "y_unique_057344_061439"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_065535 = UNIQUE_SYMBOL;
			#include "y_unique_061440_065535"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (98303)
		#elseif UNIQUE_SYMBOL < (69631)
			static stock const UNIQUE_SYMBOL_LESS_THAN_069631 = UNIQUE_SYMBOL;
			#include "y_unique_065536_069631"
			#endinput
		#elseif UNIQUE_SYMBOL < (73727)
			static stock const UNIQUE_SYMBOL_LESS_THAN_073727 = UNIQUE_SYMBOL;
			#include "y_unique_069632_073727"
			#endinput
		#elseif UNIQUE_SYMBOL < (77823)
			static stock const UNIQUE_SYMBOL_LESS_THAN_077823 = UNIQUE_SYMBOL;
			#include "y_unique_073728_077823"
			#endinput
		#elseif UNIQUE_SYMBOL < (81919)
			static stock const UNIQUE_SYMBOL_LESS_THAN_081919 = UNIQUE_SYMBOL;
			#include "y_unique_077824_081919"
			#endinput
		#elseif UNIQUE_SYMBOL < (86015)
			static stock const UNIQUE_SYMBOL_LESS_THAN_086015 = UNIQUE_SYMBOL;
			#include "y_unique_081920_086015"
			#endinput
		#elseif UNIQUE_SYMBOL < (90111)
			static stock const UNIQUE_SYMBOL_LESS_THAN_090111 = UNIQUE_SYMBOL;
			#include "y_unique_086016_090111"
			#endinput
		#elseif UNIQUE_SYMBOL < (94207)
			static stock const UNIQUE_SYMBOL_LESS_THAN_094207 = UNIQUE_SYMBOL;
			#include "y_unique_090112_094207"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_098303 = UNIQUE_SYMBOL;
			#include "y_unique_094208_098303"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (131071)
		#elseif UNIQUE_SYMBOL < (102399)
			static stock const UNIQUE_SYMBOL_LESS_THAN_102399 = UNIQUE_SYMBOL;
			#include "y_unique_098304_102399"
			#endinput
		#elseif UNIQUE_SYMBOL < (106495)
			static stock const UNIQUE_SYMBOL_LESS_THAN_106495 = UNIQUE_SYMBOL;
			#include "y_unique_102400_106495"
			#endinput
		#elseif UNIQUE_SYMBOL < (110591)
			static stock const UNIQUE_SYMBOL_LESS_THAN_110591 = UNIQUE_SYMBOL;
			#include "y_unique_106496_110591"
			#endinput
		#elseif UNIQUE_SYMBOL < (114687)
			static stock const UNIQUE_SYMBOL_LESS_THAN_114687 = UNIQUE_SYMBOL;
			#include "y_unique_110592_114687"
			#endinput
		#elseif UNIQUE_SYMBOL < (118783)
			static stock const UNIQUE_SYMBOL_LESS_THAN_118783 = UNIQUE_SYMBOL;
			#include "y_unique_114688_118783"
			#endinput
		#elseif UNIQUE_SYMBOL < (122879)
			static stock const UNIQUE_SYMBOL_LESS_THAN_122879 = UNIQUE_SYMBOL;
			#include "y_unique_118784_122879"
			#endinput
		#elseif UNIQUE_SYMBOL < (126975)
			static stock const UNIQUE_SYMBOL_LESS_THAN_126975 = UNIQUE_SYMBOL;
			#include "y_unique_122880_126975"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_131071 = UNIQUE_SYMBOL;
			#include "y_unique_126976_131071"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (163839)
		#elseif UNIQUE_SYMBOL < (135167)
			static stock const UNIQUE_SYMBOL_LESS_THAN_135167 = UNIQUE_SYMBOL;
			#include "y_unique_131072_135167"
			#endinput
		#elseif UNIQUE_SYMBOL < (139263)
			static stock const UNIQUE_SYMBOL_LESS_THAN_139263 = UNIQUE_SYMBOL;
			#include "y_unique_135168_139263"
			#endinput
		#elseif UNIQUE_SYMBOL < (143359)
			static stock const UNIQUE_SYMBOL_LESS_THAN_143359 = UNIQUE_SYMBOL;
			#include "y_unique_139264_143359"
			#endinput
		#elseif UNIQUE_SYMBOL < (147455)
			static stock const UNIQUE_SYMBOL_LESS_THAN_147455 = UNIQUE_SYMBOL;
			#include "y_unique_143360_147455"
			#endinput
		#elseif UNIQUE_SYMBOL < (151551)
			static stock const UNIQUE_SYMBOL_LESS_THAN_151551 = UNIQUE_SYMBOL;
			#include "y_unique_147456_151551"
			#endinput
		#elseif UNIQUE_SYMBOL < (155647)
			static stock const UNIQUE_SYMBOL_LESS_THAN_155647 = UNIQUE_SYMBOL;
			#include "y_unique_151552_155647"
			#endinput
		#elseif UNIQUE_SYMBOL < (159743)
			static stock const UNIQUE_SYMBOL_LESS_THAN_159743 = UNIQUE_SYMBOL;
			#include "y_unique_155648_159743"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_163839 = UNIQUE_SYMBOL;
			#include "y_unique_159744_163839"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (196607)
		#elseif UNIQUE_SYMBOL < (167935)
			static stock const UNIQUE_SYMBOL_LESS_THAN_167935 = UNIQUE_SYMBOL;
			#include "y_unique_163840_167935"
			#endinput
		#elseif UNIQUE_SYMBOL < (172031)
			static stock const UNIQUE_SYMBOL_LESS_THAN_172031 = UNIQUE_SYMBOL;
			#include "y_unique_167936_172031"
			#endinput
		#elseif UNIQUE_SYMBOL < (176127)
			static stock const UNIQUE_SYMBOL_LESS_THAN_176127 = UNIQUE_SYMBOL;
			#include "y_unique_172032_176127"
			#endinput
		#elseif UNIQUE_SYMBOL < (180223)
			static stock const UNIQUE_SYMBOL_LESS_THAN_180223 = UNIQUE_SYMBOL;
			#include "y_unique_176128_180223"
			#endinput
		#elseif UNIQUE_SYMBOL < (184319)
			static stock const UNIQUE_SYMBOL_LESS_THAN_184319 = UNIQUE_SYMBOL;
			#include "y_unique_180224_184319"
			#endinput
		#elseif UNIQUE_SYMBOL < (188415)
			static stock const UNIQUE_SYMBOL_LESS_THAN_188415 = UNIQUE_SYMBOL;
			#include "y_unique_184320_188415"
			#endinput
		#elseif UNIQUE_SYMBOL < (192511)
			static stock const UNIQUE_SYMBOL_LESS_THAN_192511 = UNIQUE_SYMBOL;
			#include "y_unique_188416_192511"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_196607 = UNIQUE_SYMBOL;
			#include "y_unique_192512_196607"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (229375)
		#elseif UNIQUE_SYMBOL < (200703)
			static stock const UNIQUE_SYMBOL_LESS_THAN_200703 = UNIQUE_SYMBOL;
			#include "y_unique_196608_200703"
			#endinput
		#elseif UNIQUE_SYMBOL < (204799)
			static stock const UNIQUE_SYMBOL_LESS_THAN_204799 = UNIQUE_SYMBOL;
			#include "y_unique_200704_204799"
			#endinput
		#elseif UNIQUE_SYMBOL < (208895)
			static stock const UNIQUE_SYMBOL_LESS_THAN_208895 = UNIQUE_SYMBOL;
			#include "y_unique_204800_208895"
			#endinput
		#elseif UNIQUE_SYMBOL < (212991)
			static stock const UNIQUE_SYMBOL_LESS_THAN_212991 = UNIQUE_SYMBOL;
			#include "y_unique_208896_212991"
			#endinput
		#elseif UNIQUE_SYMBOL < (217087)
			static stock const UNIQUE_SYMBOL_LESS_THAN_217087 = UNIQUE_SYMBOL;
			#include "y_unique_212992_217087"
			#endinput
		#elseif UNIQUE_SYMBOL < (221183)
			static stock const UNIQUE_SYMBOL_LESS_THAN_221183 = UNIQUE_SYMBOL;
			#include "y_unique_217088_221183"
			#endinput
		#elseif UNIQUE_SYMBOL < (225279)
			static stock const UNIQUE_SYMBOL_LESS_THAN_225279 = UNIQUE_SYMBOL;
			#include "y_unique_221184_225279"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_229375 = UNIQUE_SYMBOL;
			#include "y_unique_225280_229375"
			#endinput
		#endif
	#else
		#elseif UNIQUE_SYMBOL < (233471)
			static stock const UNIQUE_SYMBOL_LESS_THAN_233471 = UNIQUE_SYMBOL;
			#include "y_unique_229376_233471"
			#endinput
		#elseif UNIQUE_SYMBOL < (237567)
			static stock const UNIQUE_SYMBOL_LESS_THAN_237567 = UNIQUE_SYMBOL;
			#include "y_unique_233472_237567"
			#endinput
		#elseif UNIQUE_SYMBOL < (241663)
			static stock const UNIQUE_SYMBOL_LESS_THAN_241663 = UNIQUE_SYMBOL;
			#include "y_unique_237568_241663"
			#endinput
		#elseif UNIQUE_SYMBOL < (245759)
			static stock const UNIQUE_SYMBOL_LESS_THAN_245759 = UNIQUE_SYMBOL;
			#include "y_unique_241664_245759"
			#endinput
		#elseif UNIQUE_SYMBOL < (249855)
			static stock const UNIQUE_SYMBOL_LESS_THAN_249855 = UNIQUE_SYMBOL;
			#include "y_unique_245760_249855"
			#endinput
		#elseif UNIQUE_SYMBOL < (253951)
			static stock const UNIQUE_SYMBOL_LESS_THAN_253951 = UNIQUE_SYMBOL;
			#include "y_unique_249856_253951"
			#endinput
		#elseif UNIQUE_SYMBOL < (258047)
			static stock const UNIQUE_SYMBOL_LESS_THAN_258047 = UNIQUE_SYMBOL;
			#include "y_unique_253952_258047"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_262143 = UNIQUE_SYMBOL;
			#include "y_unique_258048_262143"
			#endinput
		#endif
	#endif
#endif

// The non-repeating header.
/**
 * <library
 *   name="y_unique"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Defines a symbol differently every time it is included."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** */

static stock const UNIQUE_SYMBOL_DOESNT_EXIST = cellmin;
#define UNIQUE_SYMBOL (0)
#define UNIQUE_FUNCTION<%0...%1> %0000%1

#if !defined Y_UNIQUE_LOCK_CONTRIBUTION
	#define Y_UNIQUE_LOCK_CONTRIBUTION 0
#endif

#if defined YSI_LOCK_MODE
	#if Y_UNIQUE_LOCK_CONTRIBUTION < 2
		forward UNIQUE_FUNCTION<@yH_OnYSIInit@...>();

		public UNIQUE_FUNCTION<@yH_OnYSIInit@...>()
		{
			#if Y_UNIQUE_LOCK_CONTRIBUTION == 0
				#undef Y_UNIQUE_LOCK_CONTRIBUTION
				#define Y_UNIQUE_LOCK_CONTRIBUTION 1
				YSI_gLockData[1] -= 'i' - '.';
			#else
				#undef Y_UNIQUE_LOCK_CONTRIBUTION
				#define Y_UNIQUE_LOCK_CONTRIBUTION 2
				YSI_gLockData{11} = 0;
			#endif
		}

		#include "y_unique_entry"
	#endif
#endif

