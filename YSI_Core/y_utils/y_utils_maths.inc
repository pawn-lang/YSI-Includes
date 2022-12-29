/**
 * <library
 *   name="y_utils - maths"
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

#define UNSIGNED(%0) ((%0) - cellmin)

#define FLOAT_INFINITY                  (Float:0x7F800000)
#define FLOAT_NEG_INFINITY              (Float:0xFF800000)
#define FLOAT_NEGATIVE_INFINITY         (Float:0xFF800000)
#define FLOAT_NAN                       (Float:0x7FFFFFFF)
#define FLOAT_NOT_A_NUMBER              (Float:0x7FFFFFFF)
#define FLOAT_QNAN                      (Float:0x7FFFFFFF)
#define FLOAT_QUIET_NAN                 (Float:0x7FFFFFFF)
#define FLOAT_QUIET_NOT_A_NUMBER        (Float:0x7FFFFFFF)
#define FLOAT_SNAN                      (Float:0x7FBFFFFF)
#define FLOAT_SIGNALING_NAN             (Float:0x7FBFFFFF)
#define FLOAT_SIGNALING_NOT_A_NUMBER    (Float:0x7FBFFFFF)
#define FLOAT_E                         (Float:0x402DF854) // e
#define FLOAT_PI                        (Float:0x40490FDB) // pi
#define FLOAT_ROOT_2                    (Float:0x3FB504F3) // sqrt(2)
#define FLOAT_EPSILON                   (Float:0x00000001) // https://en.wikipedia.org/wiki/Machine_epsilon

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">Value to check if is odd.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:IsOdd(value));
#define IsOdd(%0) ((%0)&1)

#if defined isodd
	#undef isodd
#endif
#define isodd(%0) ((%0)&1)
#define _ALS_isodd

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">Value to check if is even.</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:IsEven(value));
#define IsEven(%0) (~(%0)&1)

#if defined iseven
	#undef iseven
#endif
#define iseven(%0) (~(%0)&1)
#define _ALS_iseven

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">The unsigned number to compare.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *   An unsigned comparison between the two values.
 * </returns>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:UCMP(value, upper));
#define UCMP(%0,%1) IS_IN_RANGE(%0,0,(%1))

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">The IEEE754 floating point number (<c>Float:</c>) to check.</param>
 * <returns>
 *   An IEEE754 floating-point number is defined as Not-A-Number when all the exponent bits are set,
 *   and the mantissa is non-zero.  The sign bit is ignored, so we first remove that and test the
 *   result is <c>&gt; 0x7F800000</c>.  Because any signed number bigger than that must have all the
 *   MSBs set, plus at least one more.
 * </returns>
 *//*------------------------------------------------------------------------**/

#define IS_NAN(%0) (_:((Float:0x7FFFFFFF) & (%0)) > (0x7F800000))

FUNC_PAWNDOC(bool:IsNaN(Float:value));
#define IsNaN(%0) IS_NAN(%0)

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">The number to compare.</param>
 * <param name="lower">The lower limit.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *   Is the value in the given range.
 * </returns>
 * <remarks>
 *   Equivalent to:
 *
 * <code>		(%1) &lt;= (%0) &lt; (%2)</code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:IS_IN_RANGE(value, lower, upper));
#define IS_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin)))

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="value">The number to compare.</param>
 * <param name="lower">The lower limit.</param>
 * <param name="upper">The upper limit.</param>
 * <returns>
 *   Is the value outside the given range.
 * </returns>
 * <remarks>
 *   Equivalent to:
 *
 * <code>		(%1) &lt;= (%0) &lt; (%2)</code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:NOT_IN_RANGE(value, lower, upper));
#define NOT_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))>=((%2)-((%1)+cellmin)))

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="numerator">The top of the division.</param>
 * <param name="denominator">The bottom of the division.</param>
 * <returns>
 *   (numerator / denominator) rounded up.
 * </returns>
 * <remarks>
 *   Normal integer division ALWAYS rounds down - this always rounds up.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(ceildiv(numerator, denominator));
#if defined ceildiv
	#undef ceildiv
#endif
#if __COMPILER_1ST_PASS
	#define ceildiv __MACRO__ceildiv
#else
	#define ceildiv(%0,%1) (((%0)-1)/(%1)+1)
#endif
#define _ALS_ceildiv

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <summary>
 *   floordiv(numerator, denominator);
 * </summary>
 * <param name="numerator">The top of the division.</param>
 * <param name="denominator">The bottom of the division.</param>
 * <returns>
 *   (numerator / denominator) rounded down.
 * </returns>
 * <remarks>
 *   Normal integer division ALWAYS rounds down - this also always rounds down,
 *   making it a little pointless, but also more explicit in function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(floordiv(numerator, denominator));
#if defined floordiv
	#undef floordiv
#endif
#if __COMPILER_1ST_PASS
	#define floordiv __MACRO__floordiv
#else
	#define floordiv(%0,%1) ((%0)/(%1))
#endif
#define _ALS_floordiv

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="arr">The array whose values need summing.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *   All the values in the array added together.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Sum(const arr[], num = sizeof (arr))
{
	new
		tot = 0;
	while (num) tot += arr[--num];
	return tot;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *   The mathematical mean value of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Mean(const arr[], num = sizeof (arr))
{
	return Sum(arr, num) / num;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *   The mathematical modal value of the array.
 * </returns>
 * <remarks>
 *   Must sort the array first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Mode(arr[], num = sizeof (arr))
{
	QuickSort(arr, num);
	new
		ret = 0,
		count = 0,
		cn = 0,
		cc = 0;
	for (new i = 0; i != num; ++i)
	{
		if (arr[i] == cn) ++cc;
		else
		{
			if (cc > count) count = cc, ret = cn;
			cc = 1, cn = arr[i];
		}
	}
	if (cc > count) return cn;
	else return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *   The mathematical median value of the array.
 * </returns>
 * <remarks>
 *   Must sort the array first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Median(arr[], num = sizeof (arr))
{
	QuickSort(arr, num);
	new
		idx = num >>> 1;
	if (num & 1) return arr[idx];
	else return (arr[idx] + arr[idx - 1]) / 2;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <param name="arr">The array whose values need averaging.</param>
 * <param name="num">The size of the array.</param>
 * <returns>
 *   The mathematical range of the values of the array.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Range(const arr[], num = sizeof (arr))
{
	new
		min2 = cellmax,
		max2 = cellmin,
		cur = 0;
	while (num)
	{
		cur = arr[--num];
		if (cur < min2)
			min2 = cur;
		if (cur > max2)
			max2 = cur;
	}
	return max2 - min2;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <summary>
 *   Float:FloatAbs(Float:number);
 * </summary>
 * <param name="number">The number to get the absolute value of.</param>
 * <returns>
 *   The absolute value of a number.
 * </returns>
 * <remarks>
 *   Get the absolute value of a number.  Easy in IEEE754, just remove the MSB.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(Float:FloatAbs(Float:value));
#define FloatAbs(%0) ((%0) & (Float:0x7FFFFFFF))
#define _ALS_FloatAbs

#if __COMPILER___EMIT_U
	// Basically `x - (2 * x)`, if x is negative.
	// Technically:
	//
	//    x = x - (x >>> 31 << 1) * X
	//
	// If `x < 0` then `x >>> 31 << 1` gives `2`.  If `x >= 0` then
	// `x >>> 31 << 1` gives `0`.  So we add either `2 * x` or `0` to `x`
	// depending on the original sign of `x`.
	#define Abs(%0) \
		__emit(                            \
			LOAD.U.alt  %0                ,\
			MOVE.pri                      ,\
			SHR.C.pri   y_utils_abs_shift ,\
			SHL.C.pri   1                 ,\
			SMUL                          ,\
			SUB.alt                        \
		)
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - maths</library>
 * <summary>
 *   Abs(number);
 * </summary>
 * <param name="number">The number to get the absolute value of.</param>
 * <returns>
 *   The absolute value of a number.
 * </returns>
 * <remarks>
 *   Get the absolute value of a number.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Abs(number)
{
	return (number >> y_utils_abs_shift | 1) * number;
}

