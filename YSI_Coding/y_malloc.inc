/**
 * <library name="y_malloc">
 * <section>
 *  Description
 * </section>
 *  Functions for using malloc/calloc/free type functions in PAWN.
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="malloc">Allocate a block of memory (may be inline).</symbol>
 *  <symbol name="calloc">Allocate a block of memory and blank.</symbol>
 *  <symbol name="free">Free an allocated block of memory (may be inline).</symbol>
 *  <symbol name="Malloc_Set">Set a value in an allocated array (may be inline).</symbol>
 *  <symbol name="Malloc_Get">Get a value in an allocated array (may be inline).</symbol>
 *  <symbol name="Malloc_SetS">Set a string in an allocated array.</symbol>
 *  <symbol name="Malloc_GetS">Get a string in an allocated array.</symbol>
 *  <symbol name="Malloc_Allocate">Do the memory allocation (may be static).</symbol>
 *  <symbol name="Malloc_Free">Do the memory freeing (may be static).</symbol>
 *  <symbol name="Malloc_SlotSize">Get the size of an allocated block (may be inline).</symbol>
 *  <symbol name="Malloc_NewS">Allocate for and store a given string.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Malloc_Allocate">Do the memory allocation (may be stock).</symbol>
 *  <symbol name="Malloc_Free">Do the memory freeing (may be stock).</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="mget">Get data from an allocation unit.</symbol>
 *  <symbol name="mset">Set data in an allocation unit.</symbol>
 *  <symbol name="mgets">Get a string from an allocation unit.</symbol>
 *  <symbol name="msets">Set a string in an allocation unit.</symbol>
 *  <symbol name="malloc">Allocate a block of memory (may be stock).</symbol>
 *  <symbol name="free">Free an allocated block of memory (may be stock).</symbol>
 *  <symbol name="Malloc_Set">Set a value in an allocated array (may be stock).</symbol>
 *  <symbol name="Malloc_Get">Get a value in an allocated array (may be stock).</symbol>
 *  <symbol name="Malloc_NextSlot">Get the next free data block.</symbol>
 *  <symbol name="Malloc_GetSlotSize">Get the size of a slot.</symbol>
 *  <symbol name="Malloc_SetSlotSize">Set the size of a block.</symbol>
 *  <symbol name="Malloc_GetData">Direct data access getter.</symbol>
 *  <symbol name="Malloc_SetData">Direct data access setter.</symbol>
 *  <symbol name="Malloc_SlotSize">Get the size of an allocated block (may be stock).</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MALLOC_KB_TO_CELL">Multiplication value to convert kb to cells.</symbol>
 *  <symbol name="NO_ALLOC">A failed allocation (NULL, but YSI already has NULL).</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="Alloc">An allocated block handle variable.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Global
 * </subsection><ul>
 *  <symbol name="YSI_gMallocMemory">Stores the data (may be static).</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_gMallocMemory">Stores the data (may be global).</symbol>
 *  <symbol name="_YSI_g_sUnusedStart">Start of free memory.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="MALLOC_MEMORY">Number of cells to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_KB">Number of killobytes to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_B">Number of bytes to reserve.</symbol>
 *  <symbol name="MALLOC_MEMORY_MB">Number of megabytes to reserve.</symbol>
 *  <symbol name="YSI_MALLOC_SECURE">Use enhanced bounds checking.</symbol>
 *  <symbol name="YSI_MALLOC_NO_SHORT">Avoid conflicts with mget/mset.</symbol>
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

#if !defined _INC_y_malloc
	#tryinclude "y_malloc\y_malloc_entry"
#endif
#if !defined _INC_y_malloc
	#tryinclude "YSI_Coding\y_malloc\y_malloc_entry"
#endif
#if !defined _INC_y_malloc
	#tryinclude "YSI\YSI_Coding\y_malloc\y_malloc_entry"
#endif
#if !defined _INC_y_malloc
	#tryinclude <YSI_Coding\y_malloc\y_malloc_entry>
#endif
#if !defined _INC_y_malloc
	#tryinclude <YSI\YSI_Coding\y_malloc\y_malloc_entry>
#endif
#if !defined _INC_y_malloc
	#error Could not find y_malloc
#endif

