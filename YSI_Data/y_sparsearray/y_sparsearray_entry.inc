#if defined _INC_y_sparsearray
	#endinput
#endif
#define _INC_y_sparsearray

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

#include "..\..\YSI_Core\y_utils"

#define SparseArray:%0<> %0[]=#%0

#if defined GLOBAL_VARTYPE_INT
	#define SparseArray_MakeName(%0,%1,%2)   format((%0), sizeof (%0), "SparseArray_%d.%s", @_, (%1))
	#define SparseArray_Exists(%0,%1,%2)     (GetGVarType(%0, %2) == GLOBAL_VARTYPE_INT)
	#define SparseArray_DoWrite(%0,%1,%2,%8) (SetGVarInt(%0, %8, %2))
	#define SparseArray_DoRead(%0,%1,%2)     (GetGVarInt(%0, %2))
	#define SparseArray_DoDelete(%0,%1,%2)   (DeleteGVar(%0, %2))
#elseif defined SERVER_VARTYPE_INT
	#define SparseArray_MakeName(%0,%1,%2)   format((%0), sizeof (%0), "SparseArray_%d.%s[%d]", @_, (%1), (%2))
	#define SparseArray_Exists(%0,%1,%2)     (GetSVarType(%0) == SERVER_VARTYPE_INT)
	#define SparseArray_DoWrite(%0,%1,%2,%8) (SetSVarInt(%0, %8))
	#define SparseArray_DoRead(%0,%1,%2)     (GetSVarInt(%0))
	#define SparseArray_DoDelete(%0,%1,%2)   (DeleteSVar(%0))
#else
	#define SPARSE_ARRAY_BASE_ID (0x795F7361)
	
	#define SparseArray_MakeName(%0,%1,%2)   format((%0), sizeof (%0), "%s[%d]", (%1), (%2))
	#define SparseArray_Exists(%0,%1,%2)     (existproperty(SPARSE_ARRAY_BASE_ID + @_, %0))
	#define SparseArray_DoWrite(%0,%1,%2,%8) (setproperty(SPARSE_ARRAY_BASE_ID + @_, %0, %8))
	#define SparseArray_DoRead(%0,%1,%2)     (getproperty(SPARSE_ARRAY_BASE_ID + @_, %0))
	#define SparseArray_DoDelete(%0,%1,%2)   (deleteproperty(SPARSE_ARRAY_BASE_ID + @_, %0))
	
	// TODO:  Restore properties on mode restart.  Really this is something that
	// should be in fixes.inc (but I'm not sure how to do it in a generic way
	// without the ability to a) query properties and b) allocate arbitrary
	// memory, so really I'm not sure how to go about it...)  (a) can actually
	// be solved with more properties - make a property index system, (b) still
	// not...
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <param name="dest">Where to write the value.</param>
 * <returns>
 *  Was the value found?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Sparse_TryGet(const name[], index, &dest)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	if (SparseArray_Exists(id, name, index))
	{
		dest = SparseArray_DoRead(id, name, index);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <returns>
 *  The value at this index (or <c>cellmin</c>).
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Sparse_Get(const name[], index)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	if (SparseArray_Exists(id, name, index))
		return SparseArray_DoRead(id, name, index);
	return cellmin;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <returns>
 *  Does this index exist?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:Sparse_Contains(const name[], index)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	return SparseArray_Exists(id, name, index);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <remarks>
 *  Remove the value from the array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Sparse_UnSet(const name[], index)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	SparseArray_DoDelete(id, name, index);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <param name="value">The data to write.</param>
 * <remarks>
 *  Add the value to the array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Sparse_Set(const name[], index, value)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	SparseArray_DoWrite(id, name, index, value);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The sparse array.</param>
 * <param name="index">The index in the array.</param>
 * <param name="value">The destination variable.</param>
 * <param name="nv">The new value.</param>
 * <returns>
 *  Did the value exist?
 * </returns>
 * <remarks>
 *  Get the value and remove it from the array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Sparse_Exchange(const name[], index, &value, nv = cellmin)
{
	new id[64];
	SparseArray_MakeName(id, name, index);
	if (SparseArray_Exists(id, name, index))
	{
		value = SparseArray_DoRead(id, name, index);
		if (nv == cellmin)
			SparseArray_DoDelete(id, name, index);
		else
			SparseArray_DoWrite(id, name, index, nv);
		return true;
	}
	else if (nv != cellmin)
		SparseArray_DoWrite(id, name, index, nv);
	return false;
}

#if defined YSI_TESTS
	#include "..\y_iterate"
	#include "..\y_bit"
	#include "y_sparsearray_tests"
#endif

