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
#define HASH@fnv1(%0) HASH_:_REHASH@f(%0,@,@)

// Internal call.
#define _REHASH@f(%0,%1) _HASH@f_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@f(%0,%1,%2)(%8) _HASH@f_%1(%2)((%8*16777619^%0))

// Space.
#define _HASH@f_(%0)(%8) _DOHASH@f(32,%0)(%8)

// Numbers.
#define _HASH@f_0(%0)(%8) _DOHASH@f(48,%0)(%8)
#define _HASH@f_1(%0)(%8) _DOHASH@f(49,%0)(%8)
#define _HASH@f_2(%0)(%8) _DOHASH@f(50,%0)(%8)
#define _HASH@f_3(%0)(%8) _DOHASH@f(51,%0)(%8)
#define _HASH@f_4(%0)(%8) _DOHASH@f(52,%0)(%8)
#define _HASH@f_5(%0)(%8) _DOHASH@f(53,%0)(%8)
#define _HASH@f_6(%0)(%8) _DOHASH@f(54,%0)(%8)
#define _HASH@f_7(%0)(%8) _DOHASH@f(55,%0)(%8)
#define _HASH@f_8(%0)(%8) _DOHASH@f(56,%0)(%8)
#define _HASH@f_9(%0)(%8) _DOHASH@f(57,%0)(%8)

// Upper case letters.
#define _HASH@f_A(%0)(%8) _DOHASH@f(65,%0)(%8)
#define _HASH@f_B(%0)(%8) _DOHASH@f(66,%0)(%8)
#define _HASH@f_C(%0)(%8) _DOHASH@f(67,%0)(%8)
#define _HASH@f_D(%0)(%8) _DOHASH@f(68,%0)(%8)
#define _HASH@f_E(%0)(%8) _DOHASH@f(69,%0)(%8)
#define _HASH@f_F(%0)(%8) _DOHASH@f(70,%0)(%8)
#define _HASH@f_G(%0)(%8) _DOHASH@f(71,%0)(%8)
#define _HASH@f_H(%0)(%8) _DOHASH@f(72,%0)(%8)
#define _HASH@f_I(%0)(%8) _DOHASH@f(73,%0)(%8)
#define _HASH@f_J(%0)(%8) _DOHASH@f(74,%0)(%8)
#define _HASH@f_K(%0)(%8) _DOHASH@f(75,%0)(%8)
#define _HASH@f_L(%0)(%8) _DOHASH@f(76,%0)(%8)
#define _HASH@f_M(%0)(%8) _DOHASH@f(77,%0)(%8)
#define _HASH@f_N(%0)(%8) _DOHASH@f(78,%0)(%8)
#define _HASH@f_O(%0)(%8) _DOHASH@f(79,%0)(%8)
#define _HASH@f_P(%0)(%8) _DOHASH@f(80,%0)(%8)
#define _HASH@f_Q(%0)(%8) _DOHASH@f(81,%0)(%8)
#define _HASH@f_R(%0)(%8) _DOHASH@f(82,%0)(%8)
#define _HASH@f_S(%0)(%8) _DOHASH@f(83,%0)(%8)
#define _HASH@f_T(%0)(%8) _DOHASH@f(84,%0)(%8)
#define _HASH@f_U(%0)(%8) _DOHASH@f(85,%0)(%8)
#define _HASH@f_V(%0)(%8) _DOHASH@f(86,%0)(%8)
#define _HASH@f_W(%0)(%8) _DOHASH@f(87,%0)(%8)
#define _HASH@f_X(%0)(%8) _DOHASH@f(88,%0)(%8)
#define _HASH@f_Y(%0)(%8) _DOHASH@f(89,%0)(%8)
#define _HASH@f_Z(%0)(%8) _DOHASH@f(90,%0)(%8)

// Underscore.
#define _HASH@f__(%0)(%8) _DOHASH@f(95,%0)(%8)

// Lower case letters.
#define _HASH@f_a(%0)(%8) _DOHASH@f(97,%0)(%8)
#define _HASH@f_b(%0)(%8) _DOHASH@f(98,%0)(%8)
#define _HASH@f_c(%0)(%8) _DOHASH@f(99,%0)(%8)
#define _HASH@f_d(%0)(%8) _DOHASH@f(100,%0)(%8)
#define _HASH@f_e(%0)(%8) _DOHASH@f(101,%0)(%8)
#define _HASH@f_f(%0)(%8) _DOHASH@f(102,%0)(%8)
#define _HASH@f_g(%0)(%8) _DOHASH@f(103,%0)(%8)
#define _HASH@f_h(%0)(%8) _DOHASH@f(104,%0)(%8)
#define _HASH@f_i(%0)(%8) _DOHASH@f(105,%0)(%8)
#define _HASH@f_j(%0)(%8) _DOHASH@f(106,%0)(%8)
#define _HASH@f_k(%0)(%8) _DOHASH@f(107,%0)(%8)
#define _HASH@f_l(%0)(%8) _DOHASH@f(108,%0)(%8)
#define _HASH@f_m(%0)(%8) _DOHASH@f(109,%0)(%8)
#define _HASH@f_n(%0)(%8) _DOHASH@f(110,%0)(%8)
#define _HASH@f_o(%0)(%8) _DOHASH@f(111,%0)(%8)
#define _HASH@f_p(%0)(%8) _DOHASH@f(112,%0)(%8)
#define _HASH@f_q(%0)(%8) _DOHASH@f(113,%0)(%8)
#define _HASH@f_r(%0)(%8) _DOHASH@f(114,%0)(%8)
#define _HASH@f_s(%0)(%8) _DOHASH@f(115,%0)(%8)
#define _HASH@f_t(%0)(%8) _DOHASH@f(116,%0)(%8)
#define _HASH@f_u(%0)(%8) _DOHASH@f(117,%0)(%8)
#define _HASH@f_v(%0)(%8) _DOHASH@f(118,%0)(%8)
#define _HASH@f_w(%0)(%8) _DOHASH@f(119,%0)(%8)
#define _HASH@f_x(%0)(%8) _DOHASH@f(120,%0)(%8)
#define _HASH@f_y(%0)(%8) _DOHASH@f(121,%0)(%8)
#define _HASH@f_z(%0)(%8) _DOHASH@f(122,%0)(%8)

// String end.
#define _HASH@f_@(%0)(%8) %8

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
#define HASHi@fnv1(%0) _REHASH@if(%0,@,@)

// Internal call.
#define _REHASH@if(%0,%1) _HASH@if_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@if(%0,%1,%2)(%8) _HASH@if_%1(%2)((%8*16777619^%0))

// Space.
#define _HASH@if_(%0)(%8) _DOHASH@if(32,%0)(%8)

// Numbers.
#define _HASH@if_0(%0)(%8) _DOHASH@if(48,%0)(%8)
#define _HASH@if_1(%0)(%8) _DOHASH@if(49,%0)(%8)
#define _HASH@if_2(%0)(%8) _DOHASH@if(50,%0)(%8)
#define _HASH@if_3(%0)(%8) _DOHASH@if(51,%0)(%8)
#define _HASH@if_4(%0)(%8) _DOHASH@if(52,%0)(%8)
#define _HASH@if_5(%0)(%8) _DOHASH@if(53,%0)(%8)
#define _HASH@if_6(%0)(%8) _DOHASH@if(54,%0)(%8)
#define _HASH@if_7(%0)(%8) _DOHASH@if(55,%0)(%8)
#define _HASH@if_8(%0)(%8) _DOHASH@if(56,%0)(%8)
#define _HASH@if_9(%0)(%8) _DOHASH@if(57,%0)(%8)

// Upper case letters.
#define _HASH@if_A(%0)(%8) _DOHASH@if(65,%0)(%8)
#define _HASH@if_B(%0)(%8) _DOHASH@if(66,%0)(%8)
#define _HASH@if_C(%0)(%8) _DOHASH@if(67,%0)(%8)
#define _HASH@if_D(%0)(%8) _DOHASH@if(68,%0)(%8)
#define _HASH@if_E(%0)(%8) _DOHASH@if(69,%0)(%8)
#define _HASH@if_F(%0)(%8) _DOHASH@if(70,%0)(%8)
#define _HASH@if_G(%0)(%8) _DOHASH@if(71,%0)(%8)
#define _HASH@if_H(%0)(%8) _DOHASH@if(72,%0)(%8)
#define _HASH@if_I(%0)(%8) _DOHASH@if(73,%0)(%8)
#define _HASH@if_J(%0)(%8) _DOHASH@if(74,%0)(%8)
#define _HASH@if_K(%0)(%8) _DOHASH@if(75,%0)(%8)
#define _HASH@if_L(%0)(%8) _DOHASH@if(76,%0)(%8)
#define _HASH@if_M(%0)(%8) _DOHASH@if(77,%0)(%8)
#define _HASH@if_N(%0)(%8) _DOHASH@if(78,%0)(%8)
#define _HASH@if_O(%0)(%8) _DOHASH@if(79,%0)(%8)
#define _HASH@if_P(%0)(%8) _DOHASH@if(80,%0)(%8)
#define _HASH@if_Q(%0)(%8) _DOHASH@if(81,%0)(%8)
#define _HASH@if_R(%0)(%8) _DOHASH@if(82,%0)(%8)
#define _HASH@if_S(%0)(%8) _DOHASH@if(83,%0)(%8)
#define _HASH@if_T(%0)(%8) _DOHASH@if(84,%0)(%8)
#define _HASH@if_U(%0)(%8) _DOHASH@if(85,%0)(%8)
#define _HASH@if_V(%0)(%8) _DOHASH@if(86,%0)(%8)
#define _HASH@if_W(%0)(%8) _DOHASH@if(87,%0)(%8)
#define _HASH@if_X(%0)(%8) _DOHASH@if(88,%0)(%8)
#define _HASH@if_Y(%0)(%8) _DOHASH@if(89,%0)(%8)
#define _HASH@if_Z(%0)(%8) _DOHASH@if(90,%0)(%8)

// Underscore.
#define _HASH@if__(%0)(%8) _DOHASH@if(95,%0)(%8)

// Lower case letters.
#define _HASH@if_a(%0)(%8) _DOHASH@if(65,%0)(%8)
#define _HASH@if_b(%0)(%8) _DOHASH@if(66,%0)(%8)
#define _HASH@if_c(%0)(%8) _DOHASH@if(67,%0)(%8)
#define _HASH@if_d(%0)(%8) _DOHASH@if(68,%0)(%8)
#define _HASH@if_e(%0)(%8) _DOHASH@if(69,%0)(%8)
#define _HASH@if_f(%0)(%8) _DOHASH@if(70,%0)(%8)
#define _HASH@if_g(%0)(%8) _DOHASH@if(71,%0)(%8)
#define _HASH@if_h(%0)(%8) _DOHASH@if(72,%0)(%8)
#define _HASH@if_i(%0)(%8) _DOHASH@if(73,%0)(%8)
#define _HASH@if_j(%0)(%8) _DOHASH@if(74,%0)(%8)
#define _HASH@if_k(%0)(%8) _DOHASH@if(75,%0)(%8)
#define _HASH@if_l(%0)(%8) _DOHASH@if(76,%0)(%8)
#define _HASH@if_m(%0)(%8) _DOHASH@if(77,%0)(%8)
#define _HASH@if_n(%0)(%8) _DOHASH@if(78,%0)(%8)
#define _HASH@if_o(%0)(%8) _DOHASH@if(79,%0)(%8)
#define _HASH@if_p(%0)(%8) _DOHASH@if(80,%0)(%8)
#define _HASH@if_q(%0)(%8) _DOHASH@if(81,%0)(%8)
#define _HASH@if_r(%0)(%8) _DOHASH@if(82,%0)(%8)
#define _HASH@if_s(%0)(%8) _DOHASH@if(83,%0)(%8)
#define _HASH@if_t(%0)(%8) _DOHASH@if(84,%0)(%8)
#define _HASH@if_u(%0)(%8) _DOHASH@if(85,%0)(%8)
#define _HASH@if_v(%0)(%8) _DOHASH@if(86,%0)(%8)
#define _HASH@if_w(%0)(%8) _DOHASH@if(87,%0)(%8)
#define _HASH@if_x(%0)(%8) _DOHASH@if(88,%0)(%8)
#define _HASH@if_y(%0)(%8) _DOHASH@if(89,%0)(%8)
#define _HASH@if_z(%0)(%8) _DOHASH@if(90,%0)(%8)

// String end.
#define _HASH@if_@(%0)(%8) %8
