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

/**
 * <library>y_emit</library>
 * <remarks>
 *   The number of bytes in one cell.  Usually 4.
 * </remarks>
 */
const __cell_bytes = cellbits / charbits;

// Like `4 char`, but `4 __cell`.
#define __cell *__cell_bytes

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the current frame pointer to the previous
 *   frame pointer.  As it happens, this is directly pointed to.
 * </remarks>
 */
const __frame_offset    =   0 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the return address.
 * </remarks>
 */
const __return_offset   =   1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the parameter count.
 * </remarks>
 */
const __args_offset     =   2 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the start of the memory
 *   block with the passed arguments is.
 * </remarks>
 */
const __params_offset   =   3 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the first parameter.
 *   This is directly after the previous frame pointer, the return address,
 *   and the parameter count.
 * </remarks>
 */
const __param0_offset   =   3 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the second parameter.
 * </remarks>
 */
const __param1_offset   =   4 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the third parameter.
 * </remarks>
 */
const __param2_offset   =   5 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the fourth parameter.
 * </remarks>
 */
const __param3_offset   =   6 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the fifth parameter.
 * </remarks>
 */
const __param4_offset   =   7 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the sixth parameter.
 * </remarks>
 */
const __param5_offset   =   8 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the seventh parameter.
 * </remarks>
 */
const __param6_offset   =   9 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the eighth parameter.
 * </remarks>
 */
const __param7_offset   =  10 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the ninth parameter.
 * </remarks>
 */
const __param8_offset   =  11 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the tenth parameter.
 * </remarks>
 */
const __param9_offset   =  12 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the tenth parameter.
 * </remarks>
 */
const __param10_offset   =  13 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the first local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local0_offset   =  -1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the second local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local1_offset   =  -2 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the third local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local2_offset   =  -3 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the fourth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local3_offset   =  -4 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the fifth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local4_offset   =  -5 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the sixth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local5_offset   =  -6 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the seventh local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local6_offset   =  -7 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the eighth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local7_offset   =  -8 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the ninth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local8_offset   =  -9 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the tenth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local9_offset   = -10 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The offset in the stack from the frame pointer to the tenth local
 *   parameter.  As the stack grows down this is negative.
 * </remarks>
 */
const __local10_offset   = -11 * __cell_bytes;

// General values.

/**
 * <library>y_emit</library>
 * <remarks>
 *   The size of a table entry in the AMX header.  This is not always a exact
 *   multiple of the cell size, i.e. NOT <c>2 * __cell_bytes</c>.  The internal
 *   pointer is always 32 bits, while the external pointer is whatever native
 *   size is needed.
 * </remarks>
 */
const __defsize_cells = 4 + __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Literally just <c>-1</c>, but as a constant so that it can be used with
 *   <c>#emit</c>.  Using <c>#emit CONST.pri -1</c> is a syntax error, because
 *   who knows why...  You can use <c>#emit CONST.pri 0xFFFFFFFF</c>, i.e.
 *   encode <c>-1</c> as a twos-complement hex value (why do hex numbers work
 *   when negative numbers don't), but this is not very readable, and can't be
 *   improved with <c>#define</c> as macros don't work with <c>#emit</c> either
 *   (again, why does <c>const</c> work when <c>#define</c>, and even <c>#if</c>
 *   doesn't).  We could do this for all negative numbers, but this is by far
 *   the most useful one that isn't a multiple of the cell size.
 * </remarks>
 */
const __minus1 = -1;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The number of places you must shift a byte count by to get a cell count,
 *   i.e. <c>log2(cellbytes)</c>.  We could use division by <c>cellbytes</c> for
 *   this conversion, but a shift is faster, hence why this value must exist.
 * </remarks>
 */
#if cellbits == 64
	const __cell_shift = 3;
#elseif cellbits == 32
	const __cell_shift = 2;
#elseif cellbits == 16
	const __cell_shift = 1;
#else
	const __cell_shift = -1;
	#error Invalid cellbits
#endif

// Control registers.
/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>COD</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__cod = 0;
#else
	const __cod = 0;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>DAT</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__dat = 1;
#else
	const __dat = 1;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>HEA</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__hea = 2;
#else
	const __hea = 2;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>STP</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__stp = 3;
#else
	const __stp = 3;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>STK</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__stk = 4;
#else
	const __stk = 4;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>FRM</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__frm = 5;
#else
	const __frm = 5;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The <c>CIP</c> register number for use in <c>LCTRL</c> and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__cip = 6;
#else
	const __cip = 6;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The JIT plugin control register value for use in <c>LCTRL</c> and
 *   <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__jit = 7;
#else
	const __jit = 7;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The JIT plugin control register value for use in <c>LCTRL</c> and
 *   <c>SCTRL</c>.
 * </remarks>
 */
const __jit_flag = 7;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The JIT plugin address translation register value for use in <c>LCTRL</c>
 *   and <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__jmp = 8;
#else
	const __jmp = 8;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The JIT plugin address translation register value for use in <c>LCTRL</c>
 *   and <c>SCTRL</c>.
 * </remarks>
 */
const __jit_jump = 8;

/**
 * <library>y_emit</library>
 * <remarks>
 *   The open.mp VM flags register value for use in <c>LCTRL</c> and
 *   <c>SCTRL</c>.
 * </remarks>
 */
#if defined __register_names
	static stock YSI__flg = 9;
#else
	const __flg = 9;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The crashdetect time register value for use in <c>LCTRL</c> and
 *   <c>SCTRL</c>.
 * </remarks>
 */
#if defined __crash_time
	static stock YSI__crash_time = 254;
#else
	const __crash_time = 254;
#endif

/**
 * <library>y_emit</library>
 * <remarks>
 *   The crashdetect flags register value for use in <c>LCTRL</c> and
 *   <c>SCTRL</c>.
 * </remarks>
 */
#if defined __crash_flag
	static stock YSI__crash_flag = 255;
#else
	const __crash_flag = 255;
#endif

#define __register_names

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -32 cells.
 * </remarks>
 */
const __m32_cells = -32 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -32 cells.
 * </remarks>
 */
const __m31_cells = -31 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -30 cells.
 * </remarks>
 */
const __m30_cells = -30 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -29 cells.
 * </remarks>
 */
const __m29_cells = -29 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -28 cells.
 * </remarks>
 */
const __m28_cells = -28 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -27 cells.
 * </remarks>
 */
const __m27_cells = -27 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -26 cells.
 * </remarks>
 */
const __m26_cells = -26 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -25 cells.
 * </remarks>
 */
const __m25_cells = -25 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -24 cells.
 * </remarks>
 */
const __m24_cells = -24 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -23 cells.
 * </remarks>
 */
const __m23_cells = -23 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -22 cells.
 * </remarks>
 */
const __m22_cells = -22 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -21 cells.
 * </remarks>
 */
const __m21_cells = -21 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -20 cells.
 * </remarks>
 */
const __m20_cells = -20 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -19 cells.
 * </remarks>
 */
const __m19_cells = -19 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -18 cells.
 * </remarks>
 */
const __m18_cells = -18 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -17 cells.
 * </remarks>
 */
const __m17_cells = -17 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -16 cells.
 * </remarks>
 */
const __m16_cells = -16 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -15 cells.
 * </remarks>
 */
const __m15_cells = -15 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -14 cells.
 * </remarks>
 */
const __m14_cells = -14 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -13 cells.
 * </remarks>
 */
const __m13_cells = -13 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -12 cells.
 * </remarks>
 */
const __m12_cells = -12 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -11 cells.
 * </remarks>
 */
const __m11_cells = -11 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -10 cells.
 * </remarks>
 */
const __m10_cells = -10 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -9 cells.
 * </remarks>
 */
const __m9_cells =  -9 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -8 cells.
 * </remarks>
 */
const __m8_cells =  -8 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -7 cells.
 * </remarks>
 */
const __m7_cells =  -7 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -6 cells.
 * </remarks>
 */
const __m6_cells =  -6 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -5 cells.
 * </remarks>
 */
const __m5_cells =  -5 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -4 cells.
 * </remarks>
 */
const __m4_cells =  -4 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -3 cells.
 * </remarks>
 */
const __m3_cells =  -3 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -2 cells.
 * </remarks>
 */
const __m2_cells =  -2 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -1 cells.
 * </remarks>
 */
const __m1_cells =  -1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 *   Represents -1 cells.
 * </remarks>
 */
const __m1_cell  =  -1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __0_cells =   0 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __1_cell  =   1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __1_cells =   1 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __2_cells =   2 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __3_cells =   3 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __4_cells =   4 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __5_cells =   5 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __6_cells =   6 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __7_cells =   7 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __8_cells =   8 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const  __9_cells =   9 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __10_cells =  10 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __11_cells =  11 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __12_cells =  12 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __13_cells =  13 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __14_cells =  14 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __15_cells =  15 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __16_cells =  16 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __17_cells =  17 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __18_cells =  18 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __19_cells =  19 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __20_cells =  20 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __21_cells =  21 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __22_cells =  22 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __23_cells =  23 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __24_cells =  24 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __25_cells =  25 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __26_cells =  26 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __27_cells =  27 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __28_cells =  28 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __29_cells =  29 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __30_cells =  30 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __31_cells =  31 * __cell_bytes;

/**
 * <library>y_emit</library>
 * <remarks>
 *   Just a number of cells, converted to bytes, to make various bits of maths
 *   more clear.  Some of these values overlap with parameter offsets and the
 *   like, but these are separate to differentiate the different use-cases.
 * </remarks>
 */
const __32_cells =  32 * __cell_bytes;

