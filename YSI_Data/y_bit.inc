/**
 * <library name="y_bit">
 * <section>
 *  Description
 * </section>
 *  Provides functions for bit manipulation and bit arrays greater than 32bits.
 *  The arrays are usually bigger than required due to cell boundaries but this
 *  shouldn't cause a major problem (bit tests on the 101st bit of a 100 bit
 *  array won't return 0 for out of bounds, but the 129th will).
 *
 *  Note that y_commands has a few optimisations which bypass the code in here
 *  so any modifications to bit array layouts will need to be reflected there.
 * <section>
 *  Version
 * </section>
 *  0.2
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Bit_Set">Sets a slot to the given value.</symbol>
 *  <symbol name="Bit_Get">Gets a slot state.</symbol>
 *  <symbol name="Bit_SetAll">Sets all the slots in an array to the same thing.</symbol>
 *  <symbol name="Bit_GetCount">Gets the number of 1s in a bit array.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Bit_Bits">Gets the number of cells required for a bit array.</symbol>
 *  <symbol name="Bit_Let">Sets a slot to 1.</symbol>
 *  <symbol name="Bit_Vet">Sets a slot to 0.</symbol>
 *  <symbol name="Bit_GetBits">Gets the bit at a slot unsafely.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="CELLSHIFT">Number of bits that can hold "cellbits"</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="Bit">Bit array type.</symbol>
 * </ul>
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

#if !defined _INC_y_bit
	#tryinclude "y_bit\y_bit_entry"
#endif
#if !defined _INC_y_bit
	#tryinclude "YSI_Data\y_bit\y_bit_entry"
#endif
#if !defined _INC_y_bit
	#tryinclude "YSI\YSI_Data\y_bit\y_bit_entry"
#endif
#if !defined _INC_y_bit
	#tryinclude <YSI_Data\y_bit\y_bit_entry>
#endif
#if !defined _INC_y_bit
	#tryinclude <YSI\YSI_Data\y_bit\y_bit_entry>
#endif
#if !defined _INC_y_bit
	#error Could not find y_bit
#endif

