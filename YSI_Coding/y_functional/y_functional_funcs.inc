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
	Portions created by the Initial Developer are Copyright (c) 2022
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

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes one parameter.</param>
 * <param name="input">The input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Applies the given function to every element in the input array and saves
 *   the individual results in the output array.  This:
 *
 *   <code>
 *    Map({ _0 + 42 }, input, output);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    for (new i = 0; i != len; ++i) <br />
 *    {                              <br /><indent />
 *        output[i] = input[i] + 42; <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Map(Func:cb<i>, const input[], output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	new len = min(inputSize, outputSize);
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(input[i]);
	}
	return len;
}
#define Map({%0}%1) LAMBDA_i<Map>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes one parameter.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Applies the given function to every element in the input array, but doesn't
 *   save the result.  The function should thus have a side-effect.  This:
 *
 *   <code>
 *    Map_({ printf("%d", _0) }, input);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    for (new i = 0; i != len; ++i) <br />
 *    {                              <br /><indent />
 *        printf("%d", input[i]);    <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Map_(Func:cb<i>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		@.cb(input[i]);
	}
	return inputSize;
}
#define Map_({%0}%1) LAMBDA_i<Map_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Applies the given function to every element in the input array and their
 *   index, and saves the result.  This:
 *
 *   <code>
 *    MapIdx({ _0 * _1 }, input, output);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    for (new i = 0; i != len; ++i) <br />
 *    {                              <br /><indent />
 *        output[i] = i * input[i];  <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock MapIdx(Func:cb<ii>, const input[], output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	new len = min(inputSize, outputSize);
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(i, input[i]);
	}
	return len;
}
#define MapIdx({%0}%1) LAMBDA_ii<MapIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Applies the given function to every element in the input array and their
 *   index, but doesn't save the result.  The function should thus have a side-
 *   effect.  This:
 *
 *   <code>
 *    MapIdx_({ printf("[%d] = %d", _0, _1) }, input);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    for (new i = 0; i != len; ++i)        <br />
 *    {                                     <br /><indent />
 *        printf("[%d] = %d", i, input[i]); <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock MapIdx_(Func:cb<ii>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		@.cb(i, input[i]);
	}
	return inputSize;
}
#define MapIdx_({%0}%1) LAMBDA_ii<MapIdx_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes one parameter.</param>
 * <param name="left">The first input data array.</param>
 * <param name="right">The second input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="rightSize">The size of the second input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Combines two input arrays using a given function, and saves the result.
 *   This:
 *
 *   <code>
 *    ZipWith({ _0 + _1 }, left, right, output);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    for (new i = 0; i != len; ++i)       <br />
 *    {                                    <br /><indent />
 *        output[i] = left[i] + right[i]; <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith(Func:cb<ii>, const left[], const right[], output[], leftSize = sizeof (left), rightSize = sizeof (right), outputSize = sizeof (output))
{
	new len = min(outputSize, min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(left[i], right[i]);
	}
	return len;
}
#define ZipWith({%0}%1) LAMBDA_ii<ZipWith>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="right">The second input data array.</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="rightSize">The size of the second input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Combines two input arrays using a given function, but doesn't save the
 *   result so the function should have side-effects.  This:
 *
 *   <code>
 *    new bool:result = false; <br />
 *    ZipWith_({ result = result || (_0 > _1) }, left, right);
 *   </code>
 *
 *   Is equivalent to:
 *
 *   <code>
 *    new bool:result = false;                     <br />
 *    for (new i = 0; i != len; ++i)               <br />
 *    {                                            <br /><indent />
 *        result = result || (left[i] > right[i]); <br />
 *    }
 *   </code>
 *
 *   But obviously much shorter and less error-prone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith_(Func:cb<ii>, const left[], const right[], leftSize = sizeof (left), rightSize = sizeof (right))
{
	new len = min(leftSize, rightSize);
	for (new i = 0; i != len; ++i)
	{
		@.cb(left[i], right[i]);
	}
	return len;
}
#define ZipWith_({%0}%1) LAMBDA_ii<ZipWith_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="middle">The second input data array.</param>
 * <param name="right">The third input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="middleSize">The size of the second input array.</param>
 * <param name="rightSize">The size of the third input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith</c>, but has three inputs, not two.  The lambda parameters
 *   are thus <c>_0</c> for the current <c>left</c> value, <c>_1</c> for the
 *   current <c>middle</c> value, and <c>_2</c> for the current <c>right</c>
 *   value:
 *
 *   <code>
 *    ZipWith3({ VectorSize(Float:_0, Float:_1, Float:_2) }, gPointXs, gPointYs, gPointZs, gDistances);
 *   </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith3(Func:cb<iii>, const left[], const middle[], const right[], output[], leftSize = sizeof (left), middleSize = sizeof (middle), rightSize = sizeof (right), outputSize = sizeof (output))
{
	new len = min(min(middleSize, outputSize), min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(left[i], middle[i], right[i]);
	}
	return len;
}
#define ZipWith3({%0}%1) LAMBDA_iii<ZipWith3>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="middle">The second input data array.</param>
 * <param name="right">The third input data array.</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="middleSize">The size of the second input array.</param>
 * <param name="rightSize">The size of the third input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith_</c>, but has three inputs, not two.  The lambda parameters
 *   are thus <c>_0</c> for the current <c>left</c> value, <c>_1</c> for the
 *   current <c>middle</c> value, and <c>_2</c> for the current <c>right</c>
 *   value.  The expression result is not saved.
 *
 *   <code>
 *    RemoveBins(playerid)                                                                                                   <br />
 *    {                                                                                                                      <br /><indent />
 *        ZipWith3_({ RemoveBuildingForPlayer(playerid, 1337, Float:_0, Float:_1, Float:_2, 2.0) }, gBinXs, gBinYs, gBinZs); <br />
 *    }
 *   </code>
 *
 *   This example uses <c>playerid</c>, which is a variable from the function
 *   this code is within.  Labmdas can use closures, just like inlines.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith3_(Func:cb<iii>, const left[], const middle[], const right[], leftSize = sizeof (left), middleSize = sizeof (middle), rightSize = sizeof (right))
{
	new len = min(middleSize, min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		@.cb(left[i], middle[i], right[i]);
	}
	return len;
}
#define ZipWith3_({%0}%1) LAMBDA_iii<ZipWith3_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="right">The second input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="rightSize">The size of the second input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith</c>, but passes the current index as well.  The lambda
 *   parameters are thus <c>_0</c> for the current index, <c>_1</c> for the
 *   current <c>left</c> value, and <c>_2</c> for the current <c>right</c>
 *   value:
 *
 *   <code>
 *    inline AddAndMul(a, b, c)                                      <br />
 *    {                                                              <br /><indent />
 *        return a + (b * c);                                        <br />
 *    }                                                              <br />
 *                                                                   <br />
 *    ZipWithIdx(using inline AddAndMul, gInput1, gInput2, gResult);
 *   </code>
 *
 *   These functions can also use normal <c>using</c> syntax.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWithIdx(Func:cb<iii>, const left[], const right[], output[], leftSize = sizeof (left), rightSize = sizeof (right), outputSize = sizeof (output))
{
	new len = min(outputSize, min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(i, left[i], right[i]);
	}
	return len;
}
#define ZipWithIdx({%0}%1) LAMBDA_iii<ZipWithIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="right">The second input data array.</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="rightSize">The size of the second input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith_</c>, but passes the current index as well.  The lambda
 *   parameters are thus <c>_0</c> for the current index, <c>_1</c> for the
 *   current <c>left</c> value, and <c>_2</c> for the current <c>right</c>
 *   value.  The expression result is not saved:
 *
 *   <code>
 *    ZipWithIdx_({ SetPlayerVirtualWorld(_0, _1), SetPlayerInterior(_0, _2) }, gPlayerWords, gPlayerInteriors);
 *   </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWithIdx_(Func:cb<iii>, const left[], const right[], leftSize = sizeof (left), rightSize = sizeof (right))
{
	new len = min(leftSize, rightSize);
	for (new i = 0; i != len; ++i)
	{
		@.cb(i, left[i], right[i]);
	}
	return len;
}
#define ZipWithIdx_({%0}%1) LAMBDA_iii<ZipWithIdx_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes four parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="middle">The second input data array.</param>
 * <param name="right">The third input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="middleSize">The size of the second input array.</param>
 * <param name="rightSize">The size of the third input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith3</c>, but passes the current index as well.  The lambda
 *   parameters are thus <c>_0</c> for the current index, <c>_1</c> for the
 *   current <c>left</c> value, <c>_2</c> for the current <c>middle</c> value,
 *   and <c>_3</c> for the current <c>right</c> value:
 *
 *   <code>
 *    ZipWith3Idx({ CreateVehicle(gModels[_0], Float:_1, Float:_2, Float:_3, 0.0, -1, -1, 100000) }, gPosXs, gPosYs, gPosZs, gVehicles);
 *   </code>
 *
 *   This example uses the index to replicate a <c>ZipWith4</c>, which isn't
 *   implemented in the library natively.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith3Idx(Func:cb<iiii>, const left[], const middle[], const right[], output[], leftSize = sizeof (left), middleSize = sizeof (middle), rightSize = sizeof (right), outputSize = sizeof (output))
{
	new len = min(min(middleSize, outputSize), min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		output[i] = @.cb(i, left[i], middle[i], right[i]);
	}
	return len;
}
#define ZipWith3Idx({%0}%1) LAMBDA_iiii<ZipWith3Idx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes four parameters.</param>
 * <param name="left">The first input data array.</param>
 * <param name="middle">The second input data array.</param>
 * <param name="right">The third input data array.</param>
 * <param name="leftSize">The size of the first input array.</param>
 * <param name="middleSize">The size of the second input array.</param>
 * <param name="rightSize">The size of the third input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ZipWith3_</c>, but passes the current index as well.  The lambda
 *   parameters are thus <c>_0</c> for the current index, <c>_1</c> for the
 *   current <c>left</c> value, <c>_2</c> for the current <c>middle</c> value,
 *   and <c>_3</c> for the current <c>right</c> value.  The expression result is
 *   not saved:
 *
 *   <code>
 *    ZipWith3Idx_({ SetPlayerPos(_0, Float:_1, Float:_2, Float:_3) }, gPlayerXs, gPlayerYs, gPlayerZs);
 *   </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ZipWith3Idx_(Func:cb<iiii>, const left[], const middle[], const right[], leftSize = sizeof (left), middleSize = sizeof (middle), rightSize = sizeof (right))
{
	new len = min(middleSize, min(leftSize, rightSize));
	for (new i = 0; i != len; ++i)
	{
		@.cb(i, left[i], middle[i], right[i]);
	}
	return len;
}
#define ZipWith3Idx_({%0}%1) LAMBDA_iiii<ZipWith3Idx_>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   Like <c>FoldL</c>, but passes the index as the first parameter as well.
 *   The <c>L</c> refers to the call order, which is from the first element to
 *   the last element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldLIdx(Func:cb<iii>, n, const input[], inputSize = sizeof (input))
{
	new
		cur = n;
	for (new i = 0; i != inputSize; ++i)
	{
		cur = @.cb(i, cur, input[i]);
	}
	return cur;
}
#define FoldLIdx({%0}%1) LAMBDA_iii<FoldLIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="input">The input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Like <c>ScanL</c>, but passes the index as the first parameter as well.
 *   The <c>L</c> refers to the call order, which is from the first element to
 *   the last element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ScanLIdx(Func:cb<iii>, n, const input[], output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	if (!outputSize) return 0;
	new
		len = min(inputSize, outputSize - 1),
		i = -1,
		cur;
	while (++i != len)
	{
		cur = @.cb(i, n, input[i]),
		output[i] = n,
		n = cur;
	}
	output[i] = n;
	return len + 1;
}
#define ScanLIdx({%0}%1) LAMBDA_iii<ScanLIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   Like <c>FoldR</c>, but passes the index as the first parameter as well.
 *   The <c>R</c> refers to the call order, which is from the last element to the
 *   first element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldRIdx(Func:cb<iii>, const input[], n, inputSize = sizeof (input))
{
	new
		cur = n;
	while (inputSize--)
	{
		cur = @.cb(i, input[inputSize], cur);
	}
	return cur;
}
#define FoldRIdx({%0}%1) LAMBDA_iii<FoldRIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements written
 * </returns>
 * <remarks>
 *   Like <c>ScanR</c>, but passes the index as the first parameter as well.
 *   The <c>R</c> refers to the call order, which is from the last element to the
 *   first element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ScanRIdx(Func:cb<iii>, const input[], n, output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	if (!outputSize) return 0;
	new
		len = min(inputSize, outputSize - 1),
		cur = n;
	output[(n = len)] = cur;
	while (len--)
	{
		output[len] = cur = @.cb(i, input[len], cur);
	}
	return n + 1;
}
#define ScanRIdx({%0}%1) LAMBDA_iii<ScanRIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   Like <c>FoldL1</c>, but also passes the current index as the first
 *   parameter to the callback function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldL1Idx(Func:cb<iii>, const input[], inputSize = sizeof (input))
{
	assert(inputSize > 0);
	new
		cur = input[0];
	for (new i = 1; i != inputSize; ++i)
	{
		cur = @.cb(i, cur, input[i]);
	}
	return cur;
}
#define FoldL1Idx({%0}%1) LAMBDA_iii<FoldL1Idx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes three parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   Like <c>FoldR1</c>, but also passes the current index as the first
 *   parameter to the callback function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldR1Idx(Func:cb<iii>, const input[], inputSize = sizeof (input))
{
	assert(inputSize > 0);
	new
		cur = input[--inputSize];
	while (inputSize--)
	{
		cur = @.cb(i, input[inputSize], cur);
	}
	return cur;
}
#define FoldR1Idx({%0}%1) LAMBDA_iii<FoldR1Idx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   A <em>fold</em> applies a function to the current data and the previous
 *   result of calling the function, and repeats this process across the whole
 *   array.  The parameters to the callback are the previous result (<c>_0</c>),
 *   and the current data (<c>_1</c>).  The initial "previous" value is passed in
 *   as <c>n</c>.  To add all the values in an array together use:
 *
 *   <code>
 *    new sum = FoldL({ _0 + _1 }, 0, array);
 *   </code>
 *
 *   To find the product use:
 *
 *   <code>
 *    new product = FoldL({ _0 * _1 }, 1, array);
 *   </code>
 *
 *   The <c>L</c> refers to the call order, which is from the first element to
 *   the last element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldL(Func:cb<ii>, n, const input[], inputSize = sizeof (input))
{
	new
		cur = n;
	for (new i = 0; i != inputSize; ++i)
	{
		cur = @.cb(cur, input[i]);
	}
	return cur;
}
#define FoldL({%0}%1) LAMBDA_ii<FoldL>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="input">The input data array.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   A <em>fold</em> applies a function to the current data and the previous
 *   result of calling the function, and repeats this process across the whole
 *   array.  A <em>scan</em> extends this process by also saving all of the
 *   intermediate results in an output array.  For example:
 *
 *   <code>
 *    new input[5] = { 1, 2, 3, 4, 5 }                    <br />
 *    new output[6];                                      <br />
 *    ScanL({ _0 * _1 }, 1, input, output);
 *   </code>
 *
 *   Would return all of the interim steps stored in <c>output</c> as
 *   <c>{ 1, 1 * 1, 1 * 1 * 2, 1 * 1 * 2 * 3, 1 * 1 * 2 * 3 * 4, 1 * 1 * 2 * 3 * 4, 1 * 1 * 2 * 3 * 4 * 5 }</c>.
 *   Hence why the output array must be one cell larger than the input array.
 *
 *   The <c>L</c> refers to the call order, which is from the first element to
 *   the last element.  This is especially important in scan functions -
 *   compare the example output of <c>ScanR</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ScanL(Func:cb<ii>, n, const input[], output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	if (!outputSize) return 0;
	new
		len = min(inputSize, outputSize - 1),
		i = -1,
		cur;
	while (++i != len)
	{
		cur = @.cb(n, input[i]),
		output[i] = n,
		n = cur;
	}
	output[i] = n;
	return len + 1;
}
#define ScanL({%0}%1) LAMBDA_ii<ScanL>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   A <em>fold</em> applies a function to the current data and the previous
 *   result of calling the function, and repeats this process across the whole
 *   array.  The parameters to the callback are the current data (<c>_0</c>) and
 *   the previous result (<c>_1</c>).  The initial "previous" value is passed in
 *   as <c>n</c>.  To add all the values in an array together use:
 *
 *   <code>
 *    new sum = FoldR({ _0 + _1 }, 0, array);
 *   </code>
 *
 *   To find the product use:
 *
 *   <code>
 *    new product = FoldR({ _0 * _1 }, 1, array);
 *   </code>
 *
 *   The <c>R</c> refers to the call order, which is from the last element to the
 *   first element.  This is important for non-commutative operations like
 *   division.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldR(Func:cb<ii>, const input[], n, inputSize = sizeof (input))
{
	new
		cur = n;
	while (inputSize--)
	{
		cur = @.cb(input[inputSize], cur);
	}
	return cur;
}
#define FoldR({%0}%1) LAMBDA_ii<FoldR>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="n">The initial value of the accumulation.</param>
 * <param name="output">The output data array (may be the same array as an input).</param>
 * <param name="inputSize">The size of the input array.</param>
 * <param name="outputSize">The size of the output array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   A <em>fold</em> applies a function to the current data and the previous
 *   result of calling the function, and repeats this process across the whole
 *   array.  A <em>scan</em> extends this process by also saving all of the
 *   intermediate results in an output array.  For example:
 *
 *   <code>
 *    new input[5] = { 1, 2, 3, 4, 5 }                    <br />
 *    new output[6];                                      <br />
 *    ScanL({ _0 * _1 }, 1, input, output);
 *   </code>
 *
 *   Would return all of the interim steps stored in <c>output</c> as
 *   <c>{ 1 * 1 * 2 * 3 * 4 * 5, 1 * 2 * 3 * 4 * 5, 1 * 3 * 4 * 5, 1 * 4 * 5, 1 * 5 }</c>.
 *   Hence why the output array must be one cell larger than the input array.
 *
 *   The <c>R</c> refers to the call order, which is from the last element to the
 *   first element.  This is especially important in scan functions - compare the
 *   example output of <c>ScanL</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ScanR(Func:cb<ii>, const input[], n, output[], inputSize = sizeof (input), outputSize = sizeof (output))
{
	if (!outputSize) return 0;
	new
		len = min(inputSize, outputSize - 1),
		cur = n;
	output[(n = len)] = cur;
	while (len--)
	{
		output[len] = cur = @.cb(input[len], cur);
	}
	return n + 1;
}
#define ScanR({%0}%1) LAMBDA_ii<ScanR>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   A <em>fold</em> passes two values to the callback function - the previous
 *   result and the current element.  For the first call you still need a
 *   "previous" value, which in functions like <c>FoldL</c> is passed as an extra
 *   initial value parameter (<c>n</c>).  In this version the initial value is
 *   instead the first array element, and thus the input must contain at least
 *   one value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldL1(Func:cb<ii>, const input[], inputSize = sizeof (input))
{
	assert(inputSize > 0);
	new
		cur = input[0];
	for (new i = 1; i != inputSize; ++i)
	{
		cur = @.cb(cur, input[i]);
	}
	return cur;
}
#define FoldL1({%0}%1) LAMBDA_ii<FoldL1>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   The result of applying one function to every array element in turn.
 * </returns>
 * <remarks>
 *   A <em>fold</em> passes two values to the callback function - the previous
 *   result and the current element.  For the first call you still need a
 *   "previous" value, which in functions like <c>FoldR</c> is passed as an extra
 *   initial value parameter (<c>n</c>).  In this version the initial value is
 *   instead the last array element, and thus the input must contain at least one
 *   value.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock FoldR1(Func:cb<ii>, const input[], inputSize = sizeof (input))
{
	assert(inputSize > 0);
	new
		cur = input[--inputSize];
	while (inputSize--)
	{
		cur = @.cb(input[inputSize], cur);
	}
	return cur;
}
#define FoldR1({%0}%1) LAMBDA_ii<FoldR1>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if all the elements are non-zero (<c>true</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   An empty array cannot contain a non-zero elements, so the default return is
 *   <c>true</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:And(bool:input[], inputSize = sizeof (input))
{
	while (inputSize--)
	{
		if (!input[inputSize]) return false;
	}
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements are non-zero (<c>false</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   An empty array cannot contain a non-zero element, so the default return is
 *   <c>false</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Or(bool:input[], inputSize = sizeof (input))
{
	while (inputSize--)
	{
		if (input[inputSize]) return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes one parameter.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements pass the test function (<c>true</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   Calls the given function one at a time for every input element until one is
 *   found that fails.  The function will short-circuit, so will end as soon as a
 *   matching index is found, thus not all elements may be processed and any
 *   input functions with side-effects should be aware of this.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:All(Func:cb<i>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		if (!@.cb(input[i])) return false;
	}
	return true;
}
#define All({%0}%1) LAMBDA_i<All>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes one parameter.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements pass the test function (<c>false</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   Calls the given function one at a time for every input element until one is
 *   found that passes.  The function will short-circuit, so will end as soon as
 *   a matching index is found, thus not all elements may be processed and any
 *   input functions with side-effects should be aware of this.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Any(Func:cb<i>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		if (@.cb(input[i])) return true;
	}
	return false;
}
#define Any({%0}%1) LAMBDA_i<Any>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements pass the test function (<c>true</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   Calls the given function one at a time for every input element until one is
 *   found that fails.  The function will short-circuit, so will end as soon as a
 *   matching index is found, thus not all elements may be processed and any
 *   input functions with side-effects should be aware of this.  Passes the index
 *   as the first parameter, and the value as the second.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:AllIdx(Func:cb<ii>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		if (!@.cb(i, input[i])) return false;
	}
	return true;
}
#define AllIdx({%0}%1) LAMBDA_ii<AllIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="cb">A function that takes two parameters.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements pass the test function (<c>false</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   Calls the given function one at a time for every input element until one is
 *   found that passes.  The function will short-circuit, so will end as soon as
 *   a matching index is found, thus not all elements may be processed and any
 *   input functions with side-effects should be aware of this.  Passes the index
 *   as the first parameter, and the value as the second.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:AnyIdx(Func:cb<ii>, const input[], inputSize = sizeof (input))
{
	for (new i = 0; i != inputSize; ++i)
	{
		if (@.cb(i, input[i])) return true;
	}
	return false;
}
#define AnyIdx({%0}%1) LAMBDA_ii<AnyIdx>{%0}(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="data">The input and output data array.</param>
 * <param name="dataSize">The size of the input array.</param>
 * <returns>
 *   The number of elements processed.
 * </returns>
 * <remarks>
 *   Reverses an array, so the last element becomes the first, the first becomes
 *   the last, and all the ones in-between swap places as well.  Modifies the
 *   input array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Reverse(data[], dataSize = sizeof (data))
{
	new
		temp = 0;
	for (new i = 0; j = dataSize - 1; i < j; ++i, --j)
	{
		temp   = data[i],
		data[i] = data[j],
		data[j] = temp;
	}
	return dataSize;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="n">The value to compare elements against.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if any the elements equal <c>n</c> (<c>false</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   An empty array cannot contain a given element, so the default return is
 *   <c>false</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Elem(n, const input[], inputSize = sizeof (input))
{
	while (inputSize--)
	{
		if (input[inputSize] == n) return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="n">The value to compare elements against.</param>
 * <param name="input">The input data array.</param>
 * <param name="inputSize">The size of the input array.</param>
 * <returns>
 *   <c>true</c> if none of the elements equal <c>n</c> (<c>true</c> if there are no inputs).
 * </returns>
 * <remarks>
 *   An empty array cannot contain a given element, so the default return is
 *   <c>true</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:NotElem(n, const input[], inputSize = sizeof (input))
{
	while (inputSize--)
	{
		if (input[inputSize] == n) return false;
	}
	return true;
}

#define Just(%0) (YSI_gJust=_:%0,1)
#define Nothing  (0)

