#if defined _INC_y_simpletree
	#endinput
#endif
#define _INC_y_simpletree

/**
 * <library name="y_simpletree">
 * <section>
 *  Description
 * </section>
 *  Provides functions to generate balanced binary search trees for efficient
 *  searching of large arrays by value.  Left branch is less than, right branch
 *  is greater than or equal to for multiple matching values.
 * <section>
 *  Version
 * </section>
 *  0.2
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Core
 * </subsection><ul>
 *  <symbol name="Bintree_QSort">Custom implementaion of QSort to keep pointers.</symbol>
 *  <symbol name="Bintree_SortHalf">Itteratively balances halves of an array.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Bintree_Generate">Generates a balanced binary tree from given input.</symbol>
 *  <symbol name="Bintree_Reset">Resets a position in a tree.</symbol>
 *  <symbol name="Bintree_FindValue">Finds the pointer for a value in the tree.</symbol>
 *  <symbol name="Bintree_Add">Adds an item to a generated tree.</symbol>
 *  <symbol name="Bintree_Delete">Removes an item from a tree.</symbol>
 *  <symbol name="Bintree_UpdatePointers">Updates the pointers after a target change.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Bintree_Compress">Removes space from an altered tree.</symbol>
 *  <symbol name="Bintree_FindMin">Finds the smallest value on a branch.</symbol>
 *  <symbol name="Bintree_FindMax">Finds the largest value on a branch.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Bintree_Sort">Entry point for Bintree_QSort.</symbol>
 *  <symbol name="Bintree_Fill">Entry point for Bintree_SortHalf.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="BINTREE_NO_BRANCH">Nowhere to go from the number in required direction.</symbol>
 *  <symbol name="BINTREE_NOT_FOUND">Failure return.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  <symbol name="E_BINTREE_TREE">Structure of a leaf of a binary tree.</symbol>
 *  <symbol name="E_BINTREE_INPUT">Structure of an array of data to be added to a tree.</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="Bintree">Binary tree type.</symbol>
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

#include "..\YSI_Internal\y_version"

#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"

#include "y_binarytree"
#include "y_simpletree/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_simpletree/tests"
#endif

