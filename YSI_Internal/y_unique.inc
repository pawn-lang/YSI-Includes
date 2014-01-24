/**--------------------------------------------------------------------------**\
					============================
					 y_unique - Similar symbols 
					============================
Description:
	Defines a symbol differently every time it is included.
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
	
	The Original Code is the YSI unique symbol include.
	
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
	19/04/13:
		Upped the limit to 343.
		Changed to a 7-ary tree.
		Reversed check order so smallest numbers come first.
	01/05/11:
		First version.
\**--------------------------------------------------------------------------**/

#undef _inc_y_unique

#if !defined UNIQUE_SYMBOL
	#define UNIQUE_SYMBOL (0)
	#define UNIQUE_FUNCTION<%0...%1> %0000%1
#else
	#if UNIQUE_SYMBOL < 100
		#include "y_unique/000_to_099"
	#elseif UNIQUE_SYMBOL < 200
		#include "y_unique/100_to_199"
	#elseif UNIQUE_SYMBOL < 300
		#include "y_unique/200_to_299"
	#elseif UNIQUE_SYMBOL < 400
		#include "y_unique/300_to_399"
	#elseif UNIQUE_SYMBOL < 500
		#include "y_unique/400_to_499"
	#elseif UNIQUE_SYMBOL < 600
		#include "y_unique/500_to_599"
	#elseif UNIQUE_SYMBOL < 700
		#include "y_unique/600_to_699"
	#elseif UNIQUE_SYMBOL < 800
		#include "y_unique/700_to_799"
	#elseif UNIQUE_SYMBOL < 900
		#include "y_unique/800_to_899"
	#else
		#include "y_unique/900_to_999"
	#endif
#endif
#if UNIQUE_SYMBOL < 0 || UNIQUE_SYMBOL >= 1000
	#error UNIQUE_SYMBOL out of range.
#endif

