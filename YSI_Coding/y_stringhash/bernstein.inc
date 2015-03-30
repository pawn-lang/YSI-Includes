/**--------------------------------------------------------------------------**\
					========================================
					 y_stringhash - Fast string comparisons 
					========================================
Description:
	Allows you to hash strings at compile time to use them in a switch.
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
	
	The Original Code is the YSI stringhash include.
	
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
	2.0
Changelog:
	06/03/11:
		Changed the order of some letters to better support numbers in _I.
	01/03/11:
		Rewrote compile-time hashes to not require commas.
	25/10/10:
		Updated comments.
		Added to YSI 1.0.
		Added FNV1 and FNV1a hashes to avoid collisions.
	19/08/10:
		First version.
Functions:
	stock:
		YHash - Generate a string hash at run time.
Definitions:
	_H - Generate a string hash at compile time.
	_I - Generate a case insensitive string hash at compile time.
\**--------------------------------------------------------------------------**/

/*

      ,ad8888ba,   88          88      ,ad8888ba,                                            88 
     d8"'    `"8b  88          88     d8"'    `"8b                                           88 
    d8'        `8b 88          88    d8'                                                     88 
    88          88 88  ,adPPYb,88    88            ,adPPYYba, ,adPPYba,  ,adPPYba,   ,adPPYb,88 
    88          88 88 a8"    `Y88    88            ""     `Y8 I8[    "" a8P_____88  a8"    `Y88 
    Y8,        ,8P 88 8b       88    Y8,           ,adPPPPP88  `"Y8ba,  8PP"""""""  8b       88 
     Y8a.    .a8P  88 "8a,   ,d88     Y8a.    .a8P 88,    ,88 aa    ]8I "8b,   ,aa  "8a,   ,d88 
      `"Y8888Y"'   88  `"8bbdP"Y8      `"Y8888Y"'  `"8bbdP"Y8 `"YbbdP"'  `"Ybbd8"'   `"8bbdP"Y8 

*/

// =============================
//  Old syntax (case sensitive) 
// =============================

// Signify the end with two "@" symbols.
#define HASH@bernstein(%0) _REHASH@b(%0,@,@)

// Internal call.
#define _REHASH@b(%0,%1) _HASH@b_%0(%1,)(-1)

// The bit that actually does the work.
#define _DOHASH@b(%0,%1,%2)(%8) _HASH@b_%1(%2)((%8*33+%0))

// Space.
#define _HASH@b_(%0)(%8) _DOHASH@b(32,%0)(%8)

// Numbers.
#define _HASH@b_0(%0)(%8) _DOHASH@b(48,%0)(%8)
#define _HASH@b_1(%0)(%8) _DOHASH@b(49,%0)(%8)
#define _HASH@b_2(%0)(%8) _DOHASH@b(50,%0)(%8)
#define _HASH@b_3(%0)(%8) _DOHASH@b(51,%0)(%8)
#define _HASH@b_4(%0)(%8) _DOHASH@b(52,%0)(%8)
#define _HASH@b_5(%0)(%8) _DOHASH@b(53,%0)(%8)
#define _HASH@b_6(%0)(%8) _DOHASH@b(54,%0)(%8)
#define _HASH@b_7(%0)(%8) _DOHASH@b(55,%0)(%8)
#define _HASH@b_8(%0)(%8) _DOHASH@b(56,%0)(%8)
#define _HASH@b_9(%0)(%8) _DOHASH@b(57,%0)(%8)

// Upper case letters.
#define _HASH@b_A(%0)(%8) _DOHASH@b(65,%0)(%8)
#define _HASH@b_B(%0)(%8) _DOHASH@b(66,%0)(%8)
#define _HASH@b_C(%0)(%8) _DOHASH@b(67,%0)(%8)
#define _HASH@b_D(%0)(%8) _DOHASH@b(68,%0)(%8)
#define _HASH@b_E(%0)(%8) _DOHASH@b(69,%0)(%8)
#define _HASH@b_F(%0)(%8) _DOHASH@b(70,%0)(%8)
#define _HASH@b_G(%0)(%8) _DOHASH@b(71,%0)(%8)
#define _HASH@b_H(%0)(%8) _DOHASH@b(72,%0)(%8)
#define _HASH@b_I(%0)(%8) _DOHASH@b(73,%0)(%8)
#define _HASH@b_J(%0)(%8) _DOHASH@b(74,%0)(%8)
#define _HASH@b_K(%0)(%8) _DOHASH@b(75,%0)(%8)
#define _HASH@b_L(%0)(%8) _DOHASH@b(76,%0)(%8)
#define _HASH@b_M(%0)(%8) _DOHASH@b(77,%0)(%8)
#define _HASH@b_N(%0)(%8) _DOHASH@b(78,%0)(%8)
#define _HASH@b_O(%0)(%8) _DOHASH@b(79,%0)(%8)
#define _HASH@b_P(%0)(%8) _DOHASH@b(80,%0)(%8)
#define _HASH@b_Q(%0)(%8) _DOHASH@b(81,%0)(%8)
#define _HASH@b_R(%0)(%8) _DOHASH@b(82,%0)(%8)
#define _HASH@b_S(%0)(%8) _DOHASH@b(83,%0)(%8)
#define _HASH@b_T(%0)(%8) _DOHASH@b(84,%0)(%8)
#define _HASH@b_U(%0)(%8) _DOHASH@b(85,%0)(%8)
#define _HASH@b_V(%0)(%8) _DOHASH@b(86,%0)(%8)
#define _HASH@b_W(%0)(%8) _DOHASH@b(87,%0)(%8)
#define _HASH@b_X(%0)(%8) _DOHASH@b(88,%0)(%8)
#define _HASH@b_Y(%0)(%8) _DOHASH@b(89,%0)(%8)
#define _HASH@b_Z(%0)(%8) _DOHASH@b(90,%0)(%8)

// Underscore.
#define _HASH@b__(%0)(%8) _DOHASH@b(95,%0)(%8)

// Lower case letters.
#define _HASH@b_a(%0)(%8) _DOHASH@b(97,%0)(%8)
#define _HASH@b_b(%0)(%8) _DOHASH@b(98,%0)(%8)
#define _HASH@b_c(%0)(%8) _DOHASH@b(99,%0)(%8)
#define _HASH@b_d(%0)(%8) _DOHASH@b(100,%0)(%8)
#define _HASH@b_e(%0)(%8) _DOHASH@b(101,%0)(%8)
#define _HASH@b_f(%0)(%8) _DOHASH@b(102,%0)(%8)
#define _HASH@b_g(%0)(%8) _DOHASH@b(103,%0)(%8)
#define _HASH@b_h(%0)(%8) _DOHASH@b(104,%0)(%8)
#define _HASH@b_i(%0)(%8) _DOHASH@b(105,%0)(%8)
#define _HASH@b_j(%0)(%8) _DOHASH@b(106,%0)(%8)
#define _HASH@b_k(%0)(%8) _DOHASH@b(107,%0)(%8)
#define _HASH@b_l(%0)(%8) _DOHASH@b(108,%0)(%8)
#define _HASH@b_m(%0)(%8) _DOHASH@b(109,%0)(%8)
#define _HASH@b_n(%0)(%8) _DOHASH@b(110,%0)(%8)
#define _HASH@b_o(%0)(%8) _DOHASH@b(111,%0)(%8)
#define _HASH@b_p(%0)(%8) _DOHASH@b(112,%0)(%8)
#define _HASH@b_q(%0)(%8) _DOHASH@b(113,%0)(%8)
#define _HASH@b_r(%0)(%8) _DOHASH@b(114,%0)(%8)
#define _HASH@b_s(%0)(%8) _DOHASH@b(115,%0)(%8)
#define _HASH@b_t(%0)(%8) _DOHASH@b(116,%0)(%8)
#define _HASH@b_u(%0)(%8) _DOHASH@b(117,%0)(%8)
#define _HASH@b_v(%0)(%8) _DOHASH@b(118,%0)(%8)
#define _HASH@b_w(%0)(%8) _DOHASH@b(119,%0)(%8)
#define _HASH@b_x(%0)(%8) _DOHASH@b(120,%0)(%8)
#define _HASH@b_y(%0)(%8) _DOHASH@b(121,%0)(%8)
#define _HASH@b_z(%0)(%8) _DOHASH@b(122,%0)(%8)

// String end.
#define _HASH@b_@(%0)(%8) %8

/*

      ,ad8888ba,   88          88    88                                                            
     d8"'    `"8b  88          88    88                                                            
    d8'        `8b 88          88    88                                                            
    88          88 88  ,adPPYb,88    88  ,adPPYb,d8 8b,dPPYba,   ,adPPYba,  8b,dPPYba,  ,adPPYba,  
    88          88 88 a8"    `Y88    88 a8"    `Y88 88P'   `"8a a8"     "8a 88P'   "Y8 a8P_____88  
    Y8,        ,8P 88 8b       88    88 8b       88 88       88 8b       d8 88         8PP"""""""  
     Y8a.    .a8P  88 "8a,   ,d88    88 "8a,   ,d88 88       88 "8a,   ,a8" 88         "8b,   ,aa  
      `"Y8888Y"'   88  `"8bbdP"Y8    88  `"YbbdP"Y8 88       88  `"YbbdP"'  88          `"Ybbd8"'  
                                         aa,    ,88                                                
                                          "Y8bbdP"                                                 

*/

// ===============================
//  Old syntax (case insensitive) 
// ===============================

// Signify the end with two "@" symbols.
#define HASHi@bernstein(%0) _REHASH@ib(%0,@,@)

// Internal call.
#define _REHASH@ib(%0,%1) _HASH@ib_%0(%1,)(-1)

// The bit that actually does the work.
#define _DOHASH@ib(%0,%1,%2)(%8) _HASH@ib_%1(%2)((%8*33+%0))

// Space.
#define _HASH@ib_(%0)(%8) _DOHASH@ib(32,%0)(%8)

// Numbers.
#define _HASH@ib_0(%0)(%8) _DOHASH@ib(48,%0)(%8)
#define _HASH@ib_1(%0)(%8) _DOHASH@ib(49,%0)(%8)
#define _HASH@ib_2(%0)(%8) _DOHASH@ib(50,%0)(%8)
#define _HASH@ib_3(%0)(%8) _DOHASH@ib(51,%0)(%8)
#define _HASH@ib_4(%0)(%8) _DOHASH@ib(52,%0)(%8)
#define _HASH@ib_5(%0)(%8) _DOHASH@ib(53,%0)(%8)
#define _HASH@ib_6(%0)(%8) _DOHASH@ib(54,%0)(%8)
#define _HASH@ib_7(%0)(%8) _DOHASH@ib(55,%0)(%8)
#define _HASH@ib_8(%0)(%8) _DOHASH@ib(56,%0)(%8)
#define _HASH@ib_9(%0)(%8) _DOHASH@ib(57,%0)(%8)

// Upper case letters.
#define _HASH@ib_A(%0)(%8) _DOHASH@ib(65,%0)(%8)
#define _HASH@ib_B(%0)(%8) _DOHASH@ib(66,%0)(%8)
#define _HASH@ib_C(%0)(%8) _DOHASH@ib(67,%0)(%8)
#define _HASH@ib_D(%0)(%8) _DOHASH@ib(68,%0)(%8)
#define _HASH@ib_E(%0)(%8) _DOHASH@ib(69,%0)(%8)
#define _HASH@ib_F(%0)(%8) _DOHASH@ib(70,%0)(%8)
#define _HASH@ib_G(%0)(%8) _DOHASH@ib(71,%0)(%8)
#define _HASH@ib_H(%0)(%8) _DOHASH@ib(72,%0)(%8)
#define _HASH@ib_I(%0)(%8) _DOHASH@ib(73,%0)(%8)
#define _HASH@ib_J(%0)(%8) _DOHASH@ib(74,%0)(%8)
#define _HASH@ib_K(%0)(%8) _DOHASH@ib(75,%0)(%8)
#define _HASH@ib_L(%0)(%8) _DOHASH@ib(76,%0)(%8)
#define _HASH@ib_M(%0)(%8) _DOHASH@ib(77,%0)(%8)
#define _HASH@ib_N(%0)(%8) _DOHASH@ib(78,%0)(%8)
#define _HASH@ib_O(%0)(%8) _DOHASH@ib(79,%0)(%8)
#define _HASH@ib_P(%0)(%8) _DOHASH@ib(80,%0)(%8)
#define _HASH@ib_Q(%0)(%8) _DOHASH@ib(81,%0)(%8)
#define _HASH@ib_R(%0)(%8) _DOHASH@ib(82,%0)(%8)
#define _HASH@ib_S(%0)(%8) _DOHASH@ib(83,%0)(%8)
#define _HASH@ib_T(%0)(%8) _DOHASH@ib(84,%0)(%8)
#define _HASH@ib_U(%0)(%8) _DOHASH@ib(85,%0)(%8)
#define _HASH@ib_V(%0)(%8) _DOHASH@ib(86,%0)(%8)
#define _HASH@ib_W(%0)(%8) _DOHASH@ib(87,%0)(%8)
#define _HASH@ib_X(%0)(%8) _DOHASH@ib(88,%0)(%8)
#define _HASH@ib_Y(%0)(%8) _DOHASH@ib(89,%0)(%8)
#define _HASH@ib_Z(%0)(%8) _DOHASH@ib(90,%0)(%8)

// Underscore.
#define _HASH@ib__(%0)(%8) _DOHASH@ib(95,%0)(%8)

// Lower case letters.
#define _HASH@ib_a(%0)(%8) _DOHASH@ib(65,%0)(%8)
#define _HASH@ib_b(%0)(%8) _DOHASH@ib(66,%0)(%8)
#define _HASH@ib_c(%0)(%8) _DOHASH@ib(67,%0)(%8)
#define _HASH@ib_d(%0)(%8) _DOHASH@ib(68,%0)(%8)
#define _HASH@ib_e(%0)(%8) _DOHASH@ib(69,%0)(%8)
#define _HASH@ib_f(%0)(%8) _DOHASH@ib(70,%0)(%8)
#define _HASH@ib_g(%0)(%8) _DOHASH@ib(71,%0)(%8)
#define _HASH@ib_h(%0)(%8) _DOHASH@ib(72,%0)(%8)
#define _HASH@ib_i(%0)(%8) _DOHASH@ib(73,%0)(%8)
#define _HASH@ib_j(%0)(%8) _DOHASH@ib(74,%0)(%8)
#define _HASH@ib_k(%0)(%8) _DOHASH@ib(75,%0)(%8)
#define _HASH@ib_l(%0)(%8) _DOHASH@ib(76,%0)(%8)
#define _HASH@ib_m(%0)(%8) _DOHASH@ib(77,%0)(%8)
#define _HASH@ib_n(%0)(%8) _DOHASH@ib(78,%0)(%8)
#define _HASH@ib_o(%0)(%8) _DOHASH@ib(79,%0)(%8)
#define _HASH@ib_p(%0)(%8) _DOHASH@ib(80,%0)(%8)
#define _HASH@ib_q(%0)(%8) _DOHASH@ib(81,%0)(%8)
#define _HASH@ib_r(%0)(%8) _DOHASH@ib(82,%0)(%8)
#define _HASH@ib_s(%0)(%8) _DOHASH@ib(83,%0)(%8)
#define _HASH@ib_t(%0)(%8) _DOHASH@ib(84,%0)(%8)
#define _HASH@ib_u(%0)(%8) _DOHASH@ib(85,%0)(%8)
#define _HASH@ib_v(%0)(%8) _DOHASH@ib(86,%0)(%8)
#define _HASH@ib_w(%0)(%8) _DOHASH@ib(87,%0)(%8)
#define _HASH@ib_x(%0)(%8) _DOHASH@ib(88,%0)(%8)
#define _HASH@ib_y(%0)(%8) _DOHASH@ib(89,%0)(%8)
#define _HASH@ib_z(%0)(%8) _DOHASH@ib(90,%0)(%8)

// String end.
#define _HASH@ib_@(%0)(%8) %8
