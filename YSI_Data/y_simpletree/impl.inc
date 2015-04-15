/**--------------------------------------------------------------------------**\
					===================================
					Y Sever Includes - Binary Tree Core
					===================================
Description:
	A reduced binary tree implementation relative to y_bintree.  Doesn't have
	left and right pointers, and doesn't like live modification, but is smaller.
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
	
	The Original Code is the YSI binary tree include.
	
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
	0.2
Changelog:
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
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

#define E_INT_TREE E_BINTREE_INPUT
#define E_INT_TREE_VALUE E_BINTREE_INPUT_VALUE,
#define E_INT_TREE_POINTER E_BINTREE_INPUT_POINTER

#define IntTree BinaryInput

stock IntTree_Generate(IntTree:tree<>, size = sizeof (tree))
{
	P:3("IntTree_Generate called: %s, %i", Bintree_DisplayInput(tree), size);
	// That's more or less all there is to it!
	Bintree_Sort(tree, size);
	return 1;
}

stock IntTree_FindValue(IntTree:tree<>, value, upper = sizeof (tree))
{
	P:3("IntTree_FindValue called: %s, %i, %i", Bintree_DisplayInput(tree), value, size);
	new
		idx,
		cur,
		lower = 0;
	while (upper != lower)
	{
		idx = (upper - lower) / 2 + lower,
		cur = tree[idx][E_INT_TREE_VALUE];
		if (cur < value)
		{
			lower = idx + 1;
		}
		else if (cur > value)
		{
			upper = idx;
		}
		else
		{
				return ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
		}
	}
	return BINTREE_NOT_FOUND;
}



	new
		upper = FIXES_gscAnimIndexes[idx - ('A' - 1)],
		lower = FIXES_gscAnimIndexes[idx - 'A'];
	while (upper != lower)
	{
		idx = (upper - lower) / 2 + lower;
		if ((diff = strcmp(FIXES_gscAnimLib[idx], animlib, true)))
		{
			if (diff > 0) upper = idx;
			else lower = idx + 1;
		}
		else
		{
			// If we hit the "else" branch, we have found the correct
			// animation library from the n-ary search.
			#if FIX_ApplyAnimation_2
				if (FIXES_gsAnimTimer[playerid])
				{
					KillTimer(FIXES_gsAnimTimer[playerid]),
					FIXES_gsAnimTimer[playerid] = 0;
				}
				if (FIXES_gsPlayerAnimLibs[playerid][idx >>> 5] & (1 << (idx & 0x1F)))
				{
					FIXES_gsPlayerAnimLibs[playerid][idx >>> 5] &= ~(1 << (idx & 0x1F)),
					FIXES_gsClassAnimName[playerid][0] = '\0',
					strcat(FIXES_gsClassAnimName[playerid], animname),
					FIXES_gsAnimTimer[playerid] = SetTimerEx("_FIXES_ApplyAnimation", 350, false, "ddfdddddd", playerid, idx, fDelta, loop, lockx, locky, freeze, time, forcesync);
				}
			#endif
				return ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
		}
	}












