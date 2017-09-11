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
#define HASH@fnv1a(%0) HASH_:_REHASH@a(%0,@,@)

// Internal call.
#define _REHASH@a(%0,%1) _HASH@a_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@a(%0,%1,%2)(%8) _HASH@a_%1(%2)(((%8^%0)*16777619))

// Space.
#define _HASH@a_(%0)(%8) _DOHASH@a(32,%0)(%8)

// Numbers.
#define _HASH@a_0(%0)(%8) _DOHASH@a(48,%0)(%8)
#define _HASH@a_1(%0)(%8) _DOHASH@a(49,%0)(%8)
#define _HASH@a_2(%0)(%8) _DOHASH@a(50,%0)(%8)
#define _HASH@a_3(%0)(%8) _DOHASH@a(51,%0)(%8)
#define _HASH@a_4(%0)(%8) _DOHASH@a(52,%0)(%8)
#define _HASH@a_5(%0)(%8) _DOHASH@a(53,%0)(%8)
#define _HASH@a_6(%0)(%8) _DOHASH@a(54,%0)(%8)
#define _HASH@a_7(%0)(%8) _DOHASH@a(55,%0)(%8)
#define _HASH@a_8(%0)(%8) _DOHASH@a(56,%0)(%8)
#define _HASH@a_9(%0)(%8) _DOHASH@a(57,%0)(%8)

// Upper case letters.
#define _HASH@a_A(%0)(%8) _DOHASH@a(65,%0)(%8)
#define _HASH@a_B(%0)(%8) _DOHASH@a(66,%0)(%8)
#define _HASH@a_C(%0)(%8) _DOHASH@a(67,%0)(%8)
#define _HASH@a_D(%0)(%8) _DOHASH@a(68,%0)(%8)
#define _HASH@a_E(%0)(%8) _DOHASH@a(69,%0)(%8)
#define _HASH@a_F(%0)(%8) _DOHASH@a(70,%0)(%8)
#define _HASH@a_G(%0)(%8) _DOHASH@a(71,%0)(%8)
#define _HASH@a_H(%0)(%8) _DOHASH@a(72,%0)(%8)
#define _HASH@a_I(%0)(%8) _DOHASH@a(73,%0)(%8)
#define _HASH@a_J(%0)(%8) _DOHASH@a(74,%0)(%8)
#define _HASH@a_K(%0)(%8) _DOHASH@a(75,%0)(%8)
#define _HASH@a_L(%0)(%8) _DOHASH@a(76,%0)(%8)
#define _HASH@a_M(%0)(%8) _DOHASH@a(77,%0)(%8)
#define _HASH@a_N(%0)(%8) _DOHASH@a(78,%0)(%8)
#define _HASH@a_O(%0)(%8) _DOHASH@a(79,%0)(%8)
#define _HASH@a_P(%0)(%8) _DOHASH@a(80,%0)(%8)
#define _HASH@a_Q(%0)(%8) _DOHASH@a(81,%0)(%8)
#define _HASH@a_R(%0)(%8) _DOHASH@a(82,%0)(%8)
#define _HASH@a_S(%0)(%8) _DOHASH@a(83,%0)(%8)
#define _HASH@a_T(%0)(%8) _DOHASH@a(84,%0)(%8)
#define _HASH@a_U(%0)(%8) _DOHASH@a(85,%0)(%8)
#define _HASH@a_V(%0)(%8) _DOHASH@a(86,%0)(%8)
#define _HASH@a_W(%0)(%8) _DOHASH@a(87,%0)(%8)
#define _HASH@a_X(%0)(%8) _DOHASH@a(88,%0)(%8)
#define _HASH@a_Y(%0)(%8) _DOHASH@a(89,%0)(%8)
#define _HASH@a_Z(%0)(%8) _DOHASH@a(90,%0)(%8)

// Underscore.
#define _HASH@a__(%0)(%8) _DOHASH@a(95,%0)(%8)

// Lower case letters.
#define _HASH@a_a(%0)(%8) _DOHASH@a(97,%0)(%8)
#define _HASH@a_b(%0)(%8) _DOHASH@a(98,%0)(%8)
#define _HASH@a_c(%0)(%8) _DOHASH@a(99,%0)(%8)
#define _HASH@a_d(%0)(%8) _DOHASH@a(100,%0)(%8)
#define _HASH@a_e(%0)(%8) _DOHASH@a(101,%0)(%8)
#define _HASH@a_f(%0)(%8) _DOHASH@a(102,%0)(%8)
#define _HASH@a_g(%0)(%8) _DOHASH@a(103,%0)(%8)
#define _HASH@a_h(%0)(%8) _DOHASH@a(104,%0)(%8)
#define _HASH@a_i(%0)(%8) _DOHASH@a(105,%0)(%8)
#define _HASH@a_j(%0)(%8) _DOHASH@a(106,%0)(%8)
#define _HASH@a_k(%0)(%8) _DOHASH@a(107,%0)(%8)
#define _HASH@a_l(%0)(%8) _DOHASH@a(108,%0)(%8)
#define _HASH@a_m(%0)(%8) _DOHASH@a(109,%0)(%8)
#define _HASH@a_n(%0)(%8) _DOHASH@a(110,%0)(%8)
#define _HASH@a_o(%0)(%8) _DOHASH@a(111,%0)(%8)
#define _HASH@a_p(%0)(%8) _DOHASH@a(112,%0)(%8)
#define _HASH@a_q(%0)(%8) _DOHASH@a(113,%0)(%8)
#define _HASH@a_r(%0)(%8) _DOHASH@a(114,%0)(%8)
#define _HASH@a_s(%0)(%8) _DOHASH@a(115,%0)(%8)
#define _HASH@a_t(%0)(%8) _DOHASH@a(116,%0)(%8)
#define _HASH@a_u(%0)(%8) _DOHASH@a(117,%0)(%8)
#define _HASH@a_v(%0)(%8) _DOHASH@a(118,%0)(%8)
#define _HASH@a_w(%0)(%8) _DOHASH@a(119,%0)(%8)
#define _HASH@a_x(%0)(%8) _DOHASH@a(120,%0)(%8)
#define _HASH@a_y(%0)(%8) _DOHASH@a(121,%0)(%8)
#define _HASH@a_z(%0)(%8) _DOHASH@a(122,%0)(%8)

// String end.
#define _HASH@a_@(%0)(%8) %8

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
#define HASHi@fnv1a(%0) _REHASH@ia(%0,@,@)

// Internal call.
#define _REHASH@ia(%0,%1) _HASH@ia_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@ia(%0,%1,%2)(%8) _HASH@ia_%1(%2)(((%8^%0)*16777619))

// Space.
#define _HASH@ia_(%0)(%8) _DOHASH@ia(32,%0)(%8)

// Numbers.
#define _HASH@ia_0(%0)(%8) _DOHASH@ia(48,%0)(%8)
#define _HASH@ia_1(%0)(%8) _DOHASH@ia(49,%0)(%8)
#define _HASH@ia_2(%0)(%8) _DOHASH@ia(50,%0)(%8)
#define _HASH@ia_3(%0)(%8) _DOHASH@ia(51,%0)(%8)
#define _HASH@ia_4(%0)(%8) _DOHASH@ia(52,%0)(%8)
#define _HASH@ia_5(%0)(%8) _DOHASH@ia(53,%0)(%8)
#define _HASH@ia_6(%0)(%8) _DOHASH@ia(54,%0)(%8)
#define _HASH@ia_7(%0)(%8) _DOHASH@ia(55,%0)(%8)
#define _HASH@ia_8(%0)(%8) _DOHASH@ia(56,%0)(%8)
#define _HASH@ia_9(%0)(%8) _DOHASH@ia(57,%0)(%8)

// Upper case letters.
#define _HASH@ia_A(%0)(%8) _DOHASH@ia(65,%0)(%8)
#define _HASH@ia_B(%0)(%8) _DOHASH@ia(66,%0)(%8)
#define _HASH@ia_C(%0)(%8) _DOHASH@ia(67,%0)(%8)
#define _HASH@ia_D(%0)(%8) _DOHASH@ia(68,%0)(%8)
#define _HASH@ia_E(%0)(%8) _DOHASH@ia(69,%0)(%8)
#define _HASH@ia_F(%0)(%8) _DOHASH@ia(70,%0)(%8)
#define _HASH@ia_G(%0)(%8) _DOHASH@ia(71,%0)(%8)
#define _HASH@ia_H(%0)(%8) _DOHASH@ia(72,%0)(%8)
#define _HASH@ia_I(%0)(%8) _DOHASH@ia(73,%0)(%8)
#define _HASH@ia_J(%0)(%8) _DOHASH@ia(74,%0)(%8)
#define _HASH@ia_K(%0)(%8) _DOHASH@ia(75,%0)(%8)
#define _HASH@ia_L(%0)(%8) _DOHASH@ia(76,%0)(%8)
#define _HASH@ia_M(%0)(%8) _DOHASH@ia(77,%0)(%8)
#define _HASH@ia_N(%0)(%8) _DOHASH@ia(78,%0)(%8)
#define _HASH@ia_O(%0)(%8) _DOHASH@ia(79,%0)(%8)
#define _HASH@ia_P(%0)(%8) _DOHASH@ia(80,%0)(%8)
#define _HASH@ia_Q(%0)(%8) _DOHASH@ia(81,%0)(%8)
#define _HASH@ia_R(%0)(%8) _DOHASH@ia(82,%0)(%8)
#define _HASH@ia_S(%0)(%8) _DOHASH@ia(83,%0)(%8)
#define _HASH@ia_T(%0)(%8) _DOHASH@ia(84,%0)(%8)
#define _HASH@ia_U(%0)(%8) _DOHASH@ia(85,%0)(%8)
#define _HASH@ia_V(%0)(%8) _DOHASH@ia(86,%0)(%8)
#define _HASH@ia_W(%0)(%8) _DOHASH@ia(87,%0)(%8)
#define _HASH@ia_X(%0)(%8) _DOHASH@ia(88,%0)(%8)
#define _HASH@ia_Y(%0)(%8) _DOHASH@ia(89,%0)(%8)
#define _HASH@ia_Z(%0)(%8) _DOHASH@ia(90,%0)(%8)

// Underscore.
#define _HASH@ia__(%0)(%8) _DOHASH@ia(95,%0)(%8)

// Lower case letters.
#define _HASH@ia_a(%0)(%8) _DOHASH@ia(65,%0)(%8)
#define _HASH@ia_b(%0)(%8) _DOHASH@ia(66,%0)(%8)
#define _HASH@ia_c(%0)(%8) _DOHASH@ia(67,%0)(%8)
#define _HASH@ia_d(%0)(%8) _DOHASH@ia(68,%0)(%8)
#define _HASH@ia_e(%0)(%8) _DOHASH@ia(69,%0)(%8)
#define _HASH@ia_f(%0)(%8) _DOHASH@ia(70,%0)(%8)
#define _HASH@ia_g(%0)(%8) _DOHASH@ia(71,%0)(%8)
#define _HASH@ia_h(%0)(%8) _DOHASH@ia(72,%0)(%8)
#define _HASH@ia_i(%0)(%8) _DOHASH@ia(73,%0)(%8)
#define _HASH@ia_j(%0)(%8) _DOHASH@ia(74,%0)(%8)
#define _HASH@ia_k(%0)(%8) _DOHASH@ia(75,%0)(%8)
#define _HASH@ia_l(%0)(%8) _DOHASH@ia(76,%0)(%8)
#define _HASH@ia_m(%0)(%8) _DOHASH@ia(77,%0)(%8)
#define _HASH@ia_n(%0)(%8) _DOHASH@ia(78,%0)(%8)
#define _HASH@ia_o(%0)(%8) _DOHASH@ia(79,%0)(%8)
#define _HASH@ia_p(%0)(%8) _DOHASH@ia(80,%0)(%8)
#define _HASH@ia_q(%0)(%8) _DOHASH@ia(81,%0)(%8)
#define _HASH@ia_r(%0)(%8) _DOHASH@ia(82,%0)(%8)
#define _HASH@ia_s(%0)(%8) _DOHASH@ia(83,%0)(%8)
#define _HASH@ia_t(%0)(%8) _DOHASH@ia(84,%0)(%8)
#define _HASH@ia_u(%0)(%8) _DOHASH@ia(85,%0)(%8)
#define _HASH@ia_v(%0)(%8) _DOHASH@ia(86,%0)(%8)
#define _HASH@ia_w(%0)(%8) _DOHASH@ia(87,%0)(%8)
#define _HASH@ia_x(%0)(%8) _DOHASH@ia(88,%0)(%8)
#define _HASH@ia_y(%0)(%8) _DOHASH@ia(89,%0)(%8)
#define _HASH@ia_z(%0)(%8) _DOHASH@ia(90,%0)(%8)

// String end.
#define _HASH@ia_@(%0)(%8) %8
