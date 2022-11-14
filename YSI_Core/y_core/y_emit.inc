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

const __cell_bytes = cellbits / charbits;

// Like `4 char`, but `4 __cell`.
#define __cell *__cell_bytes

const __frame_offset    =   0 * __cell_bytes;
const __return_offset   =   1 * __cell_bytes;
const __args_offset     =   2 * __cell_bytes;
const __param0_offset   =   3 * __cell_bytes;
const __param1_offset   =   4 * __cell_bytes;
const __param2_offset   =   5 * __cell_bytes;
const __param3_offset   =   6 * __cell_bytes;
const __param4_offset   =   7 * __cell_bytes;
const __param5_offset   =   8 * __cell_bytes;
const __param6_offset   =   9 * __cell_bytes;
const __param7_offset   =  10 * __cell_bytes;
const __param8_offset   =  11 * __cell_bytes;
const __param9_offset   =  12 * __cell_bytes;
const __local0_offset   =  -1 * __cell_bytes;
const __local1_offset   =  -2 * __cell_bytes;
const __local2_offset   =  -3 * __cell_bytes;
const __local3_offset   =  -4 * __cell_bytes;
const __local4_offset   =  -5 * __cell_bytes;
const __local5_offset   =  -6 * __cell_bytes;
const __local6_offset   =  -7 * __cell_bytes;
const __local7_offset   =  -8 * __cell_bytes;
const __local8_offset   =  -9 * __cell_bytes;
const __local9_offset   = -10 * __cell_bytes;

// General values.
// This is NOT `2 * __cell_bytes`, the internal pointer is always 32 bits, while
// the external pointer is whatever native size is needed.
const __defsize_cells = 4 + __cell_bytes;
const __minus1 = -1;

#if cellbits == 64
	const __cell_shift = 3;
#elseif cellbits == 32
	const __cell_shift = 2;
#elseif cellbits == 16
	const __cell_shift = 1;
#else
	#error Invalid cellbits
#endif

// Control registers.
#if !defined __register_names
	const __cod = 0;
	const __dat = 1;
	const __hea = 2;
	const __stp = 3;
	const __stk = 4;
	const __frm = 5;
	const __cip = 6;
	const __jit = 7;
	const __jmp = 8;
	const __flg = 9;
	#define __register_names
#endif

const __m20_cells = -20 * __cell_bytes;
const __m19_cells = -19 * __cell_bytes;
const __m18_cells = -18 * __cell_bytes;
const __m17_cells = -17 * __cell_bytes;
const __m16_cells = -16 * __cell_bytes;
const __m15_cells = -15 * __cell_bytes;
const __m14_cells = -14 * __cell_bytes;
const __m13_cells = -13 * __cell_bytes;
const __m12_cells = -12 * __cell_bytes;
const __m11_cells = -11 * __cell_bytes;
const __m10_cells = -10 * __cell_bytes;
const  __m9_cells =  -9 * __cell_bytes;
const  __m8_cells =  -8 * __cell_bytes;
const  __m7_cells =  -7 * __cell_bytes;
const  __m6_cells =  -6 * __cell_bytes;
const  __m5_cells =  -5 * __cell_bytes;
const  __m4_cells =  -4 * __cell_bytes;
const  __m3_cells =  -3 * __cell_bytes;
const  __m2_cells =  -2 * __cell_bytes;
const  __m1_cells =  -1 * __cell_bytes;
const  __m1_cell  =  -1 * __cell_bytes;
const   __0_cells =   0 * __cell_bytes;
const   __1_cell  =   1 * __cell_bytes;
const   __1_cells =   1 * __cell_bytes;
const   __2_cells =   2 * __cell_bytes;
const   __3_cells =   3 * __cell_bytes;
const   __4_cells =   4 * __cell_bytes;
const   __5_cells =   5 * __cell_bytes;
const   __6_cells =   6 * __cell_bytes;
const   __7_cells =   7 * __cell_bytes;
const   __8_cells =   8 * __cell_bytes;
const   __9_cells =   9 * __cell_bytes;
const  __10_cells =  10 * __cell_bytes;
const  __11_cells =  11 * __cell_bytes;
const  __12_cells =  12 * __cell_bytes;
const  __13_cells =  13 * __cell_bytes;
const  __14_cells =  14 * __cell_bytes;
const  __15_cells =  15 * __cell_bytes;
const  __16_cells =  16 * __cell_bytes;
const  __17_cells =  17 * __cell_bytes;
const  __18_cells =  18 * __cell_bytes;
const  __19_cells =  19 * __cell_bytes;
const  __20_cells =  20 * __cell_bytes;

