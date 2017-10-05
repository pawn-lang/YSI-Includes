/*+
 * <library name="y_unique">
 * <section>
 *  Description
 * </section>
 *  Defines a symbol differently every time it is included.
 * <section>
 *  Version
 * </section>
 *  1.0
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

#include "y_compilerdata"

#if defined _inc_y_unique
	#undef _inc_y_unique
#endif

#if defined UNIQUE_FUNCTION
	#undef UNIQUE_FUNCTION
#endif

// The "static stock const" values are used for debugging, since they will show
// up in preprocessed dumps ("-l") with the value of "UNIQUE_SYMBOL" at that
// moment, instead of its final value.
#if defined UNIQUE_SYMBOL
	#if UNIQUE_SYMBOL < 0 || UNIQUE_SYMBOL >= 1000
		static stock const UNIQUE_SYMBOL_TOO_LARGE = UNIQUE_SYMBOL;
		#error UNIQUE_SYMBOL out of range.
	#endif
	#if UNIQUE_SYMBOL < 100
		static stock const UNIQUE_SYMBOL_LESS_THAN_100 = UNIQUE_SYMBOL;
		#include "y_unique\_000_to_099"
	#elseif UNIQUE_SYMBOL < 200
		static stock const UNIQUE_SYMBOL_LESS_THAN_200 = UNIQUE_SYMBOL;
		#include "y_unique\_100_to_199"
	#elseif UNIQUE_SYMBOL < 300
		static stock const UNIQUE_SYMBOL_LESS_THAN_300 = UNIQUE_SYMBOL;
		#include "y_unique\_200_to_299"
	#elseif UNIQUE_SYMBOL < 400
		static stock const UNIQUE_SYMBOL_LESS_THAN_400 = UNIQUE_SYMBOL;
		#include "y_unique\_300_to_399"
	#elseif UNIQUE_SYMBOL < 500
		static stock const UNIQUE_SYMBOL_LESS_THAN_500 = UNIQUE_SYMBOL;
		#include "y_unique\_400_to_499"
	#elseif UNIQUE_SYMBOL < 600
		static stock const UNIQUE_SYMBOL_LESS_THAN_600 = UNIQUE_SYMBOL;
		#include "y_unique\_500_to_599"
	#elseif UNIQUE_SYMBOL < 700
		static stock const UNIQUE_SYMBOL_LESS_THAN_700 = UNIQUE_SYMBOL;
		#include "y_unique\_600_to_699"
	#elseif UNIQUE_SYMBOL < 800
		static stock const UNIQUE_SYMBOL_LESS_THAN_800 = UNIQUE_SYMBOL;
		#include "y_unique\_700_to_799"
	#elseif UNIQUE_SYMBOL < 900
		static stock const UNIQUE_SYMBOL_LESS_THAN_900 = UNIQUE_SYMBOL;
		#include "y_unique\_800_to_899"
	#else
		static stock const UNIQUE_SYMBOL_OTHER_VALUE;
		#include "y_unique\_900_to_999"
	#endif
#else
	static stock const UNIQUE_SYMBOL_DOESNT_EXIST;
	#define UNIQUE_SYMBOL (0)
	#define UNIQUE_FUNCTION<%0...%1> %0000%1
#endif

#if !defined Y_UNIQUE_LOCK_CONTRIBUTION
	#define Y_UNIQUE_LOCK_CONTRIBUTION 0
#endif

#if defined YSI_LOCK_MODE
	#if Y_UNIQUE_LOCK_CONTRIBUTION < 2
		forward UNIQUE_FUNCTION<@yH_OnScriptInit@...>();
		
		public UNIQUE_FUNCTION<@yH_OnScriptInit@...>()
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
		
		#include "y_unique"
	#endif
#endif

