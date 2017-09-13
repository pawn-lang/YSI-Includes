#if defined _INC_y_bit
	#endinput
#endif
#define _INC_y_bit

/**
<section>
					y_bit
</section>
</ul></li></ul><subsection>Description</subsection><ul>
	Provides functions for bit manipulation and bit arrays greater than 32bits.
	The arrays are usually bigger than required due to cell boundaries but this
	shouldn't cause a major problem (bit tests on the 101st bit of a 100 bit
	array won't return 0 for out of bounds, but the 129th will).
	
	Note that y_commands has a few optimisations which bypass the code in here
	so any modifications to bit array layouts will need to be reflected there.
</ul></li></ul><subsection>Version</subsection><ul>
	0.2
</ul></li></ul><subsection>Changelog</subsection><ul>
	21/10/12:
		Changed "Bit_Display" to print in the correct order.
	22/02/12:
		Added the "BITS" iterator.
	01/12/08:
		Rewrote most of the code to use shifts and ands not divs and mods.
	24/06/07:
		Added Bit_GetBit
	18/06/07:
		Added Bit_GetCount
	30/04/07:
		Added Bit_SetAll
	15/04/07:
		First version.
</ul></li></ul><subsection>Functions</subsection><ul>
<li><em>Stock</em><ul>
		Bit_Set - Sets a slot to the given value.
		Bit_Get - Gets a slot state.
		Bit_SetAll - Sets all the slots in an array to the same thing.
		Bit_GetCount - Gets the number of 1s in a bit array.
</ul></li><li><em>Inline</em><ul>
		Bit_Bits - Gets the number of cells required for a bit array.
		Bit_Let - Sets a slot to 1.
		Bit_Vet - Sets a slot to 0.
		Bit_GetBits - Gets the bit at a slot unsafely.
</ul></li></ul><subsection>Definitions</subsection><ul>
	CELLSHIFT - Number of bits that can hold "cellbits"
</ul></li></ul><subsection>Tags</subsection><ul>
	Bit - Bit array type.
</ul></li></ul><subsection>Compile options</subsection><ul>
	-
</ul>
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

#include "..\YSI_Internal\y_version"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Core\y_cell"
#include "y_bit/impl"

#if defined YSI_TESTS
	#include "..\YSI_Data\y_iterate"
	#include "..\YSI_Core\y_testing"
	#include "y_bit/tests"
#endif

