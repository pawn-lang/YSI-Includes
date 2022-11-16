/**
 * <library
 *   name="y_utils - similarity"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <param name="a">First string to compare.</param>
 * <param name="lenA">Length of the first string.</param>
 * <param name="b">Second string to compare.</param>
 * <param name="lenB">Length of the second string.</param>
 * <param name="matrix">Storage for the calculations.</param>
 * <returns>
 *   The levenshtein difference (0 if the same).
 * </returns>
 * <remarks>
 *   This function is the internal implementation of a Levenshtein distance when
 *   neither string is packed.  The <c>matrix</c> parameter is rewritten at the
 *   start of the function to a larger block of memory, but is still passed in so
 *   that the rest of the generated code is correct in terms of lookups.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock DoLevenshteinDistance(const string:a[], lenA, const string:b[], lenB, matrix[])
{
	// Allocate heap space for the matrix and point the array at it.  This is
	// why we pass a fake array in as a parameter, so we can mess with the
	// pointer.
	#emit HEAP         0
	#emit STOR.S.alt   matrix
	#emit LOAD.S.pri   lenB
	#emit INC.pri
	#emit SHL.C.pri    __cell_shift
	#emit ADD
	#emit SCTRL        __hea
	// "a" is the shorter string in this call.
	for (new i = 0; i <= lenB; ++i)
	{
		matrix[i] = i;
	}
	for (new i = 0; i != lenB; ++i)
	{
		// Loop over the characters in the longer string, and use the matrix for the shorter string.
		new
			prev = matrix[0];
		matrix[0] = i + 1;
		for (new j = 0; j != lenA; ++j)
		{
			new
				distance = min(
					matrix[j + 1] + 1     , /* Insertion cost.    */ min(
					matrix[j] + 1         , /* Deletion cost.     */
					prev + _:(b[i] != a[j]) /* Substitution cost. */ )
				);
			prev = matrix[j + 1];
			matrix[j + 1] = distance;
		}
	}
	lenA = matrix[lenA];
	#emit LOAD.S.pri   matrix
	#emit SCTRL        __hea
	return lenA;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <param name="a">First string to compare.</param>
 * <param name="lenA">Length of the first string.</param>
 * <param name="b">Second string to compare.</param>
 * <param name="lenB">Length of the second string.</param>
 * <param name="matrix">Storage for the calculations.</param>
 * <returns>
 *   The levenshtein difference (0 if the same).
 * </returns>
 * <remarks>
 *   This function is the internal implementation of a Levenshtein distance when
 *   the shorter string is packed.  The <c>matrix</c> parameter is rewritten at
 *   the start of the function to a larger block of memory, but is still passed
 *   in so that the rest of the generated code is correct in terms of lookups.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock DoLevenshteinDistancePackA(const string:a[], lenA, const string:b[], lenB, matrix[])
{
	// Allocate heap space for the matrix and point the array at it.  This is
	// why we pass a fake array in as a parameter, so we can mess with the
	// pointer.
	#emit HEAP         0
	#emit STOR.S.alt   matrix
	#emit LOAD.S.pri   lenB
	#emit INC.pri
	#emit SHL.C.pri    __cell_shift
	#emit ADD
	#emit SCTRL        __hea
	// "a" is the shorter string in this call.
	for (new i = 0; i <= lenB; ++i)
	{
		matrix[i] = i;
	}
	for (new i = 0; i != lenB; ++i)
	{
		// Loop over the characters in the longer string, and use the matrix for the shorter string.
		new
			prev = matrix[0];
		matrix[0] = i + 1;
		for (new j = 0; j != lenA; ++j)
		{
			new
				distance = min(
					matrix[j + 1] + 1     , /* Insertion cost.    */ min(
					matrix[j] + 1         , /* Deletion cost.     */
					prev + _:(b[i] != a{j}) /* Substitution cost. */ )
				);
			prev = matrix[j + 1];
			matrix[j + 1] = distance;
		}
	}
	lenA = matrix[lenA];
	#emit LOAD.S.pri   matrix
	#emit SCTRL        __hea
	return lenA;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <param name="a">First string to compare.</param>
 * <param name="lenA">Length of the first string.</param>
 * <param name="b">Second string to compare.</param>
 * <param name="lenB">Length of the second string.</param>
 * <param name="matrix">Storage for the calculations.</param>
 * <returns>
 *   The levenshtein difference (0 if the same).
 * </returns>
 * <remarks>
 *   This function is the internal implementation of a Levenshtein distance when
 *   th elongest stringis  packed.  The <c>matrix</c> parameter is rewritten at
 *   the start of the function to a larger block of memory, but is still passed
 *   in so that the rest of the generated code is correct in terms of lookups.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock DoLevenshteinDistancePackB(const string:a[], lenA, const string:b[], lenB, matrix[])
{
	// Allocate heap space for the matrix and point the array at it.  This is
	// why we pass a fake array in as a parameter, so we can mess with the
	// pointer.
	#emit HEAP         0
	#emit STOR.S.alt   matrix
	#emit LOAD.S.pri   lenB
	#emit INC.pri
	#emit SHL.C.pri    __cell_shift
	#emit ADD
	#emit SCTRL        __hea
	// "a" is the shorter string in this call.
	for (new i = 0; i <= lenB; ++i)
	{
		matrix[i] = i;
	}
	for (new i = 0; i != lenB; ++i)
	{
		// Loop over the characters in the longer string, and use the matrix for the shorter string.
		new
			prev = matrix[0];
		matrix[0] = i + 1;
		for (new j = 0; j != lenA; ++j)
		{
			new
				distance = min(
					matrix[j + 1] + 1     , /* Insertion cost.    */ min(
					matrix[j] + 1         , /* Deletion cost.     */
					prev + _:(b{i} != a[j]) /* Substitution cost. */ )
				);
			prev = matrix[j + 1];
			matrix[j + 1] = distance;
		}
	}
	lenA = matrix[lenA];
	#emit LOAD.S.pri   matrix
	#emit SCTRL        __hea
	return lenA;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <param name="a">First string to compare.</param>
 * <param name="lenA">Length of the first string.</param>
 * <param name="b">Second string to compare.</param>
 * <param name="lenB">Length of the second string.</param>
 * <param name="matrix">Storage for the calculations.</param>
 * <returns>
 *   The levenshtein difference (0 if the same).
 * </returns>
 * <remarks>
 *   This function is the internal implementation of a Levenshtein distance when
 *   both strings are packed.  The <c>matrix</c> parameter is rewritten at the
 *   start of the function to a larger block of memory, but is still passed in so
 *   that the rest of the generated code is correct in terms of lookups.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock DoLevenshteinDistancePackAB(const string:a[], lenA, const string:b[], lenB, matrix[])
{
	// Allocate heap space for the matrix and point the array at it.  This is
	// why we pass a fake array in as a parameter, so we can mess with the
	// pointer.
	#emit HEAP         0
	#emit STOR.S.alt   matrix
	#emit LOAD.S.pri   lenB
	#emit INC.pri
	#emit SHL.C.pri    __cell_shift
	#emit ADD
	#emit SCTRL        __hea
	// "a" is the shorter string in this call.
	for (new i = 0; i <= lenB; ++i)
	{
		matrix[i] = i;
	}
	for (new i = 0; i != lenB; ++i)
	{
		// Loop over the characters in the longer string, and use the matrix for the shorter string.
		new
			prev = matrix[0];
		matrix[0] = i + 1;
		for (new j = 0; j != lenA; ++j)
		{
			new
				distance = min(
					matrix[j + 1] + 1     , /* Insertion cost.    */ min(
					matrix[j] + 1         , /* Deletion cost.     */
					prev + _:(b{i} != a{j}) /* Substitution cost. */ )
				);
			prev = matrix[j + 1];
			matrix[j + 1] = distance;
		}
	}
	lenA = matrix[lenA];
	#emit LOAD.S.pri   matrix
	#emit SCTRL        __hea
	return lenA;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <param name="stringA">First string to compare.</param>
 * <param name="stringB">Second string to compare.</param>
 * <returns>
 *   The levenshtein difference (0 if the same).
 * </returns>
 * <remarks>
 *   The levenshtein difference is a measure of the difference between two
 *   strings, given as the number of operations required to change one string in
 *   to the other one.  A lower number means that the strings are more similar,
 *   with <c>0</c> meaning that they are identical.
 *
 *   Either string can be packed, and this function now has no upper limit on the
 *   size of strings that can be compared, as long as they can fit in the heap.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock LevenshteinDistance(const stringA[], const stringB[])
{
	// If a string is empty, the other length is the distance.
	new
		lenA = strlen(stringA),
		lenB = strlen(stringB),
		matrix[1]; // Only exists to trick the compiler.
	if (!lenA)
		return lenB;
	if (!lenB)
		return lenA;
	if (lenA > lenB)
	{
		// The calls below are NOT wrong, the parameters are swapped so the A/B
		// packing calls are also swapped.
		if (YSI_IsLocalVarPackedString__(stringA))
		{
			if (YSI_IsLocalVarPackedString__(stringB))
				return DoLevenshteinDistancePackAB(stringB, lenB, stringA, lenA, matrix);
			else
				return DoLevenshteinDistancePackB(stringB, lenB, stringA, lenA, matrix);
		}
		else
		{
			if (YSI_IsLocalVarPackedString__(stringB))
				return DoLevenshteinDistancePackA(stringB, lenB, stringA, lenA, matrix);
			else
				return DoLevenshteinDistance(stringB, lenB, stringA, lenA, matrix);
		}
	}
	else if (lenA == lenB && strcmp(stringA, stringB) == 0)
	{
		// Same string.
		return 0;
	}
	if (YSI_IsLocalVarPackedString__(stringA))
	{
		if (YSI_IsLocalVarPackedString__(stringB))
			return DoLevenshteinDistancePackAB(stringA, lenA, stringB, lenB, matrix);
		else
			return DoLevenshteinDistancePackA(stringA, lenA, stringB, lenB, matrix);
	}
	else
	{
		if (YSI_IsLocalVarPackedString__(stringB))
			return DoLevenshteinDistancePackB(stringA, lenA, stringB, lenB, matrix);
		else
			return DoLevenshteinDistance(stringA, lenA, stringB, lenB, matrix);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - similarity</library>
 * <summary>
 *   BiGramSimilarity(const string1[], const string2[]);
 * </summary>
 * <param name="string1">The first string to compare.</param>
 * <param name="string1">The second string to compare.</param>
 * <returns>
 *   The normalised similarity between the strings (<c>0.0 - 1.0</c>).
 * </returns>
 * <remarks>
 *   Compares the pairs of letters and numbers in each string with each other to
 *   find a measure of how much of one ordered string is in the other.  Useful
 *   for seeing if two strings are similar to humans.  This is nothing like the
 *   more common <em>Levenshtein Distance</em>, which pretty much compares
 *   strings at an ASCII character level, so two very different strings can be
 *   apparently more similar than two others.
 *
 *   A good example of this, which was the motivation for writing this function,
 *   was in <em>sscanf</em>.  When checking to see what vehicle a player wrote,
 *   the input <c>NRG</c> would return <c>TUG</c> as the closest match.  Why?
 *   Because they're both three letters and share the last <c>G</c>, so
 *   mechanically they are only two transformations apart; whereas <c>NRG-400</c>
 *   needs four transforms to get to from the input.  So this code looks at how
 *   much of each string is in the other string.  Very little of <c>TUG</c> is in
 *   <c>NRG</c> and vice-versa, while all of <c>NRG</c> is in <c>NRG-400</c> and
 *   a lot of the reverse is true.
 *
 *   This entirely ignores case, spaces, and punctuation in the comparisons.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Float:BiGramSimilarity(const string:string1[], const string:string2[])
{
	// 2-dimensional comparison of lower-case letters.
	new
		matrix[36 * 36],
		pair = 0,
		ch,
		unique1 = 0,
		unique2 = 0,
		ngrams1 = -1,
		ngrams2 = -1;
	// We can also "improve" the comparison by making all numbers the same.
	if (YSI_IsLocalVarPackedString__(string1))
	{
		for (new i = 0; (ch = string1{i}); ++i)
		{
			// This code only looks at numbers and letters, and ignores case.
			if ('0' <= ch <= '9')
			{
				pair = (pair / 36) | ((ch - '0') * 36);
			}
			else if ('a' <= ch <= 'z')
			{
				pair = (pair / 36) | ((ch - ('a' - 10)) * 36);
			}
			else if ('A' <= ch <= 'Z')
			{
				pair = (pair / 36) | ((ch - ('A' - 10)) * 36);
			}
			else
			{
				// Not a character we are interested in.
				continue;
			}
			if (++ngrams1)
			{
				// Got at least TWO characters.
				++matrix[pair],
				++unique1;
			}
		}
	}
	else
	{
		for (new i = 0; (ch = string1[i]); ++i)
		{
			// This code only looks at numbers and letters, and ignores case.
			if ('0' <= ch <= '9')
			{
				pair = (pair / 36) | ((ch - '0') * 36);
			}
			else if ('a' <= ch <= 'z')
			{
				pair = (pair / 36) | ((ch - ('a' - 10)) * 36);
			}
			else if ('A' <= ch <= 'Z')
			{
				pair = (pair / 36) | ((ch - ('A' - 10)) * 36);
			}
			else
			{
				// Not a character we are interested in.
				continue;
			}
			if (++ngrams1)
			{
				// Got at least TWO characters.
				++matrix[pair],
				++unique1;
			}
		}
	}
	if (YSI_IsLocalVarPackedString__(string2))
	{
		for (new i = 0; (ch = string2{i}); ++i)
		{
			// This code only looks at numbers and letters, and ignores case.
			if ('0' <= ch <= '9')
			{
				pair = (pair / 36) | ((ch - '0') * 36);
			}
			else if ('a' <= ch <= 'z')
			{
				pair = (pair / 36) | ((ch - ('a' - 10)) * 36);
			}
			else if ('A' <= ch <= 'Z')
			{
				pair = (pair / 36) | ((ch - ('A' - 10)) * 36);
			}
			else
			{
				// Not a character we are interested in.
				continue;
			}
			// The original version had positive numbers as pairs in `string1` but
			// not `string2`, and vice-versa, but I already optimised it.
			if (!++ngrams2)
			{
			}
			else if (matrix[pair])
			{
				--matrix[pair],
				--unique1;
			}
			else
			{
				++unique2;
			}
			/*if (++ngrams2)
			{
				// Got at least TWO characters.
				--matrix[pair];
			}*/
		}
	}
	else
	{
		for (new i = 0; (ch = string2[i]); ++i)
		{
			// This code only looks at numbers and letters, and ignores case.
			if ('0' <= ch <= '9')
			{
				pair = (pair / 36) | ((ch - '0') * 36);
			}
			else if ('a' <= ch <= 'z')
			{
				pair = (pair / 36) | ((ch - ('a' - 10)) * 36);
			}
			else if ('A' <= ch <= 'Z')
			{
				pair = (pair / 36) | ((ch - ('A' - 10)) * 36);
			}
			else
			{
				// Not a character we are interested in.
				continue;
			}
			// The original version had positive numbers as pairs in `string1` but
			// not `string2`, and vice-versa, but I already optimised it.
			if (!++ngrams2)
			{
			}
			else if (matrix[pair])
			{
				--matrix[pair],
				--unique1;
			}
			else
			{
				++unique2;
			}
			/*if (++ngrams2)
			{
				// Got at least TWO characters.
				--matrix[pair];
			}*/
		}
	}
	if (ngrams1 < 1 || ngrams2 < 1)
	{
		// There just aren't enough letters to compare.
		return 0.0;
	}
	// Normalise the number of matching pairs and multiply.
	return (1.0 - floatdiv(unique1, ngrams1)) * (1.0 - floatdiv(unique2, ngrams2));
}

