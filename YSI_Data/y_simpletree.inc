#if defined _INC_y_simpletree
	#endinput
#endif
#define _INC_y_simpletree

/**
<section>
					y_simpletree
</section>
<subsection>Description</subsection>
	Provides functions to generate balanced binary search trees for efficient
	searching of large arrays by value.  Left branch is less than, right branch
	is greater than or equal to for multiple matching values.
<subsection>Version</subsection>
	0.2
<subsection>Changelog</subsection><ul>
	12/04/15:
		Ported to y_simpletree for unique integer searching.
	12/08/07:
		Fixed a bug with empty trees.
	14/04/07:
		Updated header documentation with more than changelog.
	10/04/07:
		Added parents for easy deletion.
		Added node deletion code.
	08/04/07:
		Added Bintree_Add()
	24/03/07:
		First version.
</ul><subsection>Functions</subsection><ul>
<li><em>Core</em><ul>
		Bintree_QSort - Custom implementaion of QSort to keep pointers.
		Bintree_SortHalf - Itteratively balances halves of an array.
</ul></li><li><em>Stock</em><ul>
		Bintree_Generate - Generates a balanced binary tree from given input.
		Bintree_Reset - Resets a position in a tree.
		Bintree_FindValue - Finds the pointer for a value in the tree.
		Bintree_Add - Adds an item to a generated tree.
		Bintree_Delete - Removes an item from a tree.
		Bintree_UpdatePointers - Updates the pointers after a target change.
</ul></li><li><em>Static</em><ul>
		Bintree_Compress - Removes space from an altered tree.
		Bintree_FindMin - Finds the smallest value on a branch.
		Bintree_FindMax - Finds the largest value on a branch.
</ul></li><li><em>Inline</em><ul>
		Bintree_Sort - Entry point for Bintree_QSort.
		Bintree_Fill - Entry point for Bintree_SortHalf.
</ul></li></ul><subsection>Definitions</subsection><ul>
	BINTREE_NO_BRANCH - Nowhere to go from the number in required direction.
	BINTREE_NOT_FOUND - Failure return.
</ul><subsection>Enums</subsection><ul>
	E_BINTREE_TREE - Structure of a leaf of a binary tree.
	E_BINTREE_INPUT - Structure of an array of data to be added to a tree.
</ul><subsection>Tags</subsection><ul>
	Bintree - Binary tree type.
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

#include "y_binarytree"
#include "y_simpletree/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_simpletree/tests"
#endif

