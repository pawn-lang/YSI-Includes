/**--------------------------------------------------------------------------**\
					===================================
					Y Sever Includes - Binary Tree Core
					===================================
Description:
	Provides functions to generate balanced binary search trees for efficient
	searching of large arrays by value.  Left branch is less than, right branch
	is greater than or equal to for multiple matching values.
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
	0.1.3
Changelog:
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
		Bintree_QSort - Custom implementaion of QSort to keep pointers.
		Bintree_SortHalf - Itteratively balances halves of an array.
	Stock:
		Bintree_Generate - Generates a balanced binary tree from given input.
		Bintree_Reset - Resets a position in a tree.
		Bintree_FindValue - Finds the pointer for a value in the tree.
		Bintree_Add - Adds an item to a generated tree.
		Bintree_Delete - Removes an item from a tree.
		Bintree_UpdatePointers - Updates the pointers after a target change.
	Static:
		Bintree_Compress - Removes space from an altered tree.
		Bintree_FindMin - Finds the smallest value on a branch.
		Bintree_FindMax - Finds the largest value on a branch.
	Inline:
		Bintree_Sort - Entry point for Bintree_QSort.
		Bintree_Fill - Entry point for Bintree_SortHalf.
	API:
		-
Callbacks:
	-
Definitions:
	BINTREE_NO_BRANCH - Nowhere to go from the number in required direction.
	BINTREE_NOT_FOUND - Failure return.
Enums:
	E_BINTREE_TREE - Structure of a leaf of a binary tree.
	E_BINTREE_INPUT - Structure of an array of data to be added to a tree.
Macros:
	-
Tags:
	Bintree - Binary tree type.
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
</remarks>
\**--------------------------------------------------------------------------**/

#include "internal\y_version"

#include "y_debug"
#include "y_utils"

#define BINTREE_NO_BRANCH -1
#define BINTREE_NOT_FOUND -1

// If this ever changes, update the size reference in y_users.
enum E_BINTREE_TREE
{
	E_BINTREE_TREE_VALUE,
	E_BINTREE_TREE_LEFT,
	E_BINTREE_TREE_RIGHT,
	E_BINTREE_TREE_PARENT,
	E_BINTREE_TREE_POINTER
}

enum E_BINTREE_INPUT
{
	E_BINTREE_INPUT_VALUE,
	E_BINTREE_INPUT_POINTER
}

//#define leafs<%1> %1][E_BINTREE_TREE
//#define Bintree:%1[%2] Bintree:%1[%2][E_BINTREE_TREE]
#define BinaryTree:%1<%2> Bintree:%1[%2][E_BINTREE_TREE]

// Update at a later date...
#define Bintree_DisplayOutput(%0) "<bintree output>"
#define Bintree_DisplayInput(%0) "<bintree input>"

/**--------------------------------------------------------------------------**\
<summary>Bintree_Sort</summary>
<param name="input[][E_BINTREE_INPUT]">Data to sort.</param>
<param name="size">Size of data to sort.</param>
<returns>
	-
</returns>
<remarks>
	Entry point for Bintree_QSort.
</remarks>
\**--------------------------------------------------------------------------**/

#define Bintree_Sort(%1,%2) \
	Bintree_QSort((%1), 0, (%2) - 1)

/**--------------------------------------------------------------------------**\
<summary>Bintree_Fill</summary>
<param name="BinaryTree:output<>">Destination for balanced tree.</param>
<param name="data[][E_BINTREE_INPUT]">Source data.</param>
<param name="size">Size of data.</param>
<returns>
	Bintree_SortHalf.
</returns>
<remarks>
	Entry point for Bintree_SortHalf.
</remarks>
\**--------------------------------------------------------------------------**/

#define Bintree_Fill(%1,%2,%3) \
	Bintree_SortHalf((%1), (%2), 0, (%3), 0, BINTREE_NO_BRANCH)

/**--------------------------------------------------------------------------**\
<summary>Bintree_Generate</summary>
<param name="BinaryTree:output<>">Binary tree to store the data in.</param>
<param name="input[][E_BINTREE_INPUT]">Input data to get the data from.</param>
<param name="size">Number of items to sort.</param>
<returns>
	-
</returns>
<remarks>
	Just calls the sort and fill routines.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_Generate(BinaryTree:output<>, input[][E_BINTREE_INPUT], size)
{
	P:3("Bintree_Generate called: %s, %s, %i", Bintree_DisplayOutput(output), Bintree_DisplayInput(input), size);
	if (!size)
	{
		output[0][E_BINTREE_TREE_PARENT] = BINTREE_NO_BRANCH;
		output[0][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		output[0][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
		return 0;
	}
	Bintree_Sort(input, size);
	Bintree_Fill(output, input, size);
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_Reset</summary>
<param name="BinaryTree:tree<>">Array to reset.</param>
<param name="pointer">Position to reset.</param>
<returns>
	-
</returns>
<remarks>
	Initialises the array for use.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_Reset(BinaryTree:tree<>, pointer = 0)
{
	P:3("Bintree_Reset called: %s, %i", Bintree_DisplayOutput(tree), pointer);
	tree[pointer][E_BINTREE_TREE_VALUE] = 0;
	tree[pointer][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
	tree[pointer][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
	tree[pointer][E_BINTREE_TREE_PARENT] = BINTREE_NO_BRANCH;
	tree[pointer][E_BINTREE_TREE_POINTER] = BINTREE_NOT_FOUND;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_FindValue</summary>
<param name="BinaryTree:tree<>">Tree to find the data in.</param>
<param name="value">Value to search for.</param>
<param name="&cont">Start point.</param>
<param name="&old">The last real leaf.</param>
<returns>
	-
</returns>
<remarks>
	Itterates through the array following the various paths till it locates
	the value provided or reaches a dead end.  If the current value is greater
	than the search value, the search goes left, otherwise right.
	
	If cont is not -1 the search will start from the data pointed to by the
	data pointed to by conts' right path, this is to allow collisions to be
	passed over if you want a subsequent one.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_FindValue(BinaryTree:tree<>, value, &cont = 0, &old = 0)
{
	P:3("Bintree_FindValue called: %s, %i, %i, %i", Bintree_DisplayOutput(tree), value, cont, old);
	new
		treeValue;
	while (cont != BINTREE_NO_BRANCH)
	{
		P:7("Bintree_FindValue: search %d %d %d %d", cont, old, tree[cont][E_BINTREE_TREE_VALUE], value);
		old = cont;
		treeValue = tree[old][E_BINTREE_TREE_VALUE];
		if (value < treeValue) cont = tree[old][E_BINTREE_TREE_LEFT];
		else
		{
			cont = tree[old][E_BINTREE_TREE_RIGHT];
			if (value == treeValue)
			{
				return tree[old][E_BINTREE_TREE_POINTER];
			}
		}
	}
	return BINTREE_NOT_FOUND;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_QSort</summary>
<param name="numbers[][E_BINTREE_INPUT]">Data to sort.</param>
<param name="left">Start index.</param>
<param name="right">End index.</param>
<returns>
	-
</returns>
<remarks>
	Custom version of QSort (see YSI_misc) allows for E_BINTREE_INPUT data
	types, preserving the relative pointers for the sorted data.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_QSort(numbers[][E_BINTREE_INPUT], left, right)
{
	P:3("Bintree_QSort called: %s, %i, %i", Bintree_DisplayInput(numbers), left, right);
	new
		pivot = numbers[left][E_BINTREE_INPUT_VALUE],
		pointer = numbers[left][E_BINTREE_INPUT_POINTER],
		l_hold = left,
		r_hold = right;
	while (left < right)
	{
		while ((numbers[right][E_BINTREE_INPUT_VALUE] >= pivot) && (left < right)) right--;
		if (left != right)
		{
			numbers[left][E_BINTREE_INPUT_VALUE] = numbers[right][E_BINTREE_INPUT_VALUE];
			numbers[left][E_BINTREE_INPUT_POINTER] = numbers[right][E_BINTREE_INPUT_POINTER];
			left++;
		}
		while ((numbers[left][E_BINTREE_INPUT_VALUE] <= pivot) && (left < right)) left++;
		if (left != right)
		{
			numbers[right][E_BINTREE_INPUT_VALUE] = numbers[left][E_BINTREE_INPUT_VALUE];
			numbers[right][E_BINTREE_INPUT_POINTER] = numbers[left][E_BINTREE_INPUT_POINTER];
			right--;
		}
	}
	numbers[left][E_BINTREE_INPUT_VALUE] = pivot;
	numbers[left][E_BINTREE_INPUT_POINTER] = pointer;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) Bintree_QSort(numbers, left, pivot - 1);
	if (right > pivot) Bintree_QSort(numbers, pivot + 1, right);
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_SortHalf</summary>
<param name="BinaryTree:output<>">Destination array.</param>
<param name="data[][E_BINTREE_INPUT]">Source array.</param>
<param name="index">Start index of the source for processing.</param>
<param name="upper">End index of the source for processing.</param>
<param name="offset">Current offset in the destination array for writing.</param>
<returns>
	Size of balanced tree.
</returns>
<remarks>
	Recursively calls itself.  Bisects the passed array and passed each half
	back to itself, with the middle value of each half being the left and
	right branches of the middle value of the passed array (which isn't
	included in either bisected half).  This is itterative so those are again
	split and again split.  If the passed array is only one or two elements
	big the behaviour is set and hardcoded.
	
	Equal values SHOULD branch right, the code is designed for this however
	the generation is not fully tested (it mostly branches right but adjacent
	after bisecting values haven't been tested).
	
	Based on code written for PHP by me.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_SortHalf(BinaryTree:output<>, data[][E_BINTREE_INPUT], index, upper, offset, parent)
{
	P:3("Bintree_SortHalf called: %s, %s, %i, %i, %i, %i", Bintree_DisplayOutput(output), Bintree_DisplayInput(data), index, upper, offset, parent);
	new
		num = upper - index;
	if (!num) return offset;
	if (num == 1)
	{
		output[offset][E_BINTREE_TREE_VALUE] = data[index][E_BINTREE_INPUT_VALUE];
		output[offset][E_BINTREE_TREE_POINTER] = data[index][E_BINTREE_INPUT_POINTER];
		output[offset][E_BINTREE_TREE_PARENT] = parent;
		output[offset][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		output[offset][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
	}
	else if (num == 2)
	{
		P:3("Bintree_SortHalf: adding %i %i %i", index, data[index][E_BINTREE_INPUT_VALUE], data[index + 1][E_BINTREE_INPUT_VALUE]);
		output[offset][E_BINTREE_TREE_VALUE] = data[index][E_BINTREE_INPUT_VALUE];
		output[offset][E_BINTREE_TREE_POINTER] = data[index][E_BINTREE_INPUT_POINTER];
		output[offset][E_BINTREE_TREE_PARENT] = parent;
		output[offset][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		output[offset][E_BINTREE_TREE_RIGHT] = offset + 1;
		++offset;
		++index;
		output[offset][E_BINTREE_TREE_VALUE] = data[index][E_BINTREE_INPUT_VALUE];
		output[offset][E_BINTREE_TREE_POINTER] = data[index][E_BINTREE_INPUT_POINTER];
		output[offset][E_BINTREE_TREE_PARENT] = offset - 1;
		output[offset][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		output[offset][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
	}
	else
	{
		new
			half = num / 2,
			off = half + index,
			right;
		while (off && data[off][E_BINTREE_INPUT_VALUE] == data[off - 1][E_BINTREE_INPUT_VALUE]) off--;
		right = Bintree_SortHalf(output, data, index, off, offset + 1, offset);
		output[offset][E_BINTREE_TREE_VALUE] = data[off][E_BINTREE_INPUT_VALUE];
		output[offset][E_BINTREE_TREE_POINTER] = data[off][E_BINTREE_INPUT_POINTER];
		output[offset][E_BINTREE_TREE_PARENT] = parent;
		output[offset][E_BINTREE_TREE_LEFT] = offset + 1;
		output[offset][E_BINTREE_TREE_RIGHT] = right;
		return Bintree_SortHalf(output, data, off + 1, upper, right, offset);
	}
	return offset + 1;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_Add</summary>
<param name="BinaryTree:data<>">Array to add to.</param>
<param name="pointer">Pointer to add.</param>
<param name="value">Value to add.</param>
<param name="offset">Location in the array to store the data.</param>
<param name="maxsize">Size of data.</param>
<returns>
	Next free location
</returns>
<remarks>
	-

native Bintree_Add(BinaryTree:tree<>, pointer, value, offset, maxsize = sizeof (data));

</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_Add(BinaryTree:data<>, pointer, value, offset, maxsize = sizeof (data))
{
	P:3("Bintree_Add called: %s, %i, %i, %i, %i", Bintree_DisplayOutput(data), pointer, value, offset, maxsize);
	if (offset >= maxsize) return BINTREE_NOT_FOUND;
	if (offset)
	{
		new
			leaf,
			old;
		while (Bintree_FindValue(data, value, leaf, old) != BINTREE_NOT_FOUND) continue;
		//Bintree_Reset(data, offset);
		if (value < data[old][E_BINTREE_TREE_VALUE]) data[old][E_BINTREE_TREE_LEFT] = offset;
		else data[old][E_BINTREE_TREE_RIGHT] = offset;
		data[offset][E_BINTREE_TREE_PARENT] = old;
		data[offset][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		data[offset][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
		data[offset][E_BINTREE_TREE_VALUE] = value;
		data[offset][E_BINTREE_TREE_POINTER] = pointer;
		return offset + 1;
	}
	else
	{
		data[0][E_BINTREE_TREE_PARENT] = BINTREE_NO_BRANCH;
		data[0][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
		data[0][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
		data[0][E_BINTREE_TREE_VALUE] = value;
		data[0][E_BINTREE_TREE_POINTER] = pointer;
		return 1;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_Delete</summary>
<param name="BinaryTree:tree<>">Data.</param>
<param name="index">Index to remove.</param>
<param name="count">Number of binary tree items.</param>
<returns>
	-
</returns>
<remarks>
	The left branch is usually larger due to the division
	method used so we start there.  Even though right is
	>= and left is only < in even sized arrays the greater
	chunk (unless there's only 2 items) goes left.
	
	Called itteratively to ensure branches are maintained.
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_Delete(BinaryTree:source<>, index, count)
{
	P:3("Bintree_Delete called: %s, %i, %i", Bintree_DisplayOutput(source), index, count);
	new
		branch,
		old = index;
	while (TRUE)
	{
		if ((branch = source[old][E_BINTREE_TREE_LEFT]) != BINTREE_NO_BRANCH) branch = Bintree_FindMax(source, branch);
		else if ((branch = source[old][E_BINTREE_TREE_RIGHT]) != BINTREE_NO_BRANCH) branch = Bintree_FindMin(source, branch);
		else
		{
			if ((branch = source[old][E_BINTREE_TREE_PARENT]) != BINTREE_NO_BRANCH)
			{
				if (source[branch][E_BINTREE_TREE_LEFT] == old) source[branch][E_BINTREE_TREE_LEFT] = BINTREE_NO_BRANCH;
				else source[branch][E_BINTREE_TREE_RIGHT] = BINTREE_NO_BRANCH;
			}
			return Bintree_Compress(source, old, count);
		}
		new
			value = source[old][E_BINTREE_TREE_VALUE],
			pointer = source[old][E_BINTREE_TREE_POINTER];
		source[old][E_BINTREE_TREE_VALUE] = source[branch][E_BINTREE_TREE_VALUE];
		source[old][E_BINTREE_TREE_POINTER] = source[branch][E_BINTREE_TREE_POINTER];
		source[branch][E_BINTREE_TREE_VALUE] = value;
		source[branch][E_BINTREE_TREE_POINTER] = pointer;
		old = branch;
	}
	return BINTREE_NO_BRANCH;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_Compress</summary>
<param name="BinaryTree:tree<>">Array to compress.</param>
<param name="index">Point to start at.</param>
<param name="count">Number of items total.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

static stock Bintree_Compress(BinaryTree:data<>, index, count)
{
	P:4("Bintree_Compress called: %s, %i, %i", Bintree_DisplayOutput(data), index, count);
	new
		index2 = index + 1;
	while (index < count)
	{
		new
			left = (data[index][E_BINTREE_TREE_LEFT] = data[index2][E_BINTREE_TREE_LEFT]),
			right = (data[index][E_BINTREE_TREE_RIGHT] = data[index2][E_BINTREE_TREE_RIGHT]),
			parent = (data[index][E_BINTREE_TREE_PARENT] = data[index2][E_BINTREE_TREE_PARENT]);
		data[index][E_BINTREE_TREE_VALUE] = data[index2][E_BINTREE_TREE_VALUE];
		data[index][E_BINTREE_TREE_POINTER] = data[index2][E_BINTREE_TREE_POINTER];
		if (left != BINTREE_NO_BRANCH) data[left][E_BINTREE_TREE_PARENT] = index;
		if (right != BINTREE_NO_BRANCH) data[right][E_BINTREE_TREE_PARENT] = index;
		if (parent != BINTREE_NO_BRANCH)
		{
			if (data[parent][E_BINTREE_TREE_LEFT] == index2) data[parent][E_BINTREE_TREE_LEFT] = index;
			else if (data[parent][E_BINTREE_TREE_RIGHT] == index2) data[parent][E_BINTREE_TREE_RIGHT] = index;
		}
		index++;
		index2++;
	}
	return count - 1;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_FindMin</summary>
<param name="BinaryTree:data<>">Array to search.</param>
<param name="offset">Start of branch to search.</param>
<returns>
	-
</returns>
<remarks>
	Finds the smallest value on a branch
</remarks>
\**--------------------------------------------------------------------------**/

static stock Bintree_FindMin(BinaryTree:data<>, offset)
{
	P:4("Bintree_FindMin called: %s, %i", Bintree_DisplayOutput(data), offset);
	new
		branch;
	while ((branch = data[offset][E_BINTREE_TREE_LEFT]) != BINTREE_NO_BRANCH) offset = branch;
	return offset;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_FindMax</summary>
<param name="BinaryTree:data<>">Array to search.</param>
<param name="offset">Start of branch to search.</param>
<returns>
	-
</returns>
<remarks>
	Finds the largest value on a branch
</remarks>
\**--------------------------------------------------------------------------**/

static stock Bintree_FindMax(BinaryTree:data<>, offset)
{
	P:4("Bintree_FindMax called: %s, %i", Bintree_DisplayOutput(data), offset);
	new
		branch;
	while ((branch = data[offset][E_BINTREE_TREE_RIGHT]) != BINTREE_NO_BRANCH) offset = branch;
	return offset;
}

/**--------------------------------------------------------------------------**\
<summary>Bintree_UpdatePointers</summary>
<param name="BinaryTree:data<>">Data to modify.</param>
<param name="offset">Pointer to modify values after.</param>
<param name="mod">Value to modify by.</param>
<returns>
	-
</returns>
<remarks>
	Used for updating pointers when the target data has been modifed (i.e. a
	value has been removed from the array and the array shifted).
</remarks>
\**--------------------------------------------------------------------------**/

stock Bintree_UpdatePointers(BinaryTree:data<>, offset, size, mod = -1)
{
	P:3("Bintree_UpdatePointers called: %s, %i, %i, %i", Bintree_DisplayOutput(data), offset, size, mod);
	for (new i = 0; i < size; i++)
	{
		if (data[i][E_BINTREE_TREE_POINTER] > offset) data[i][E_BINTREE_TREE_POINTER] += mod;
	}
}
