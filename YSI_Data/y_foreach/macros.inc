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

/*

    88      a8P                                                                           88            
    88    ,88'                                                                            88            
    88  ,88"                                                                              88            
    88,d88'      ,adPPYba, 8b       d8 8b      db      d8  ,adPPYba,  8b,dPPYba,  ,adPPYb,88 ,adPPYba,  
    8888"88,    a8P_____88 `8b     d8' `8b    d88b    d8' a8"     "8a 88P'   "Y8 a8"    `Y88 I8[    ""  
    88P   Y8b   8PP"""""""  `8b   d8'   `8b  d8'`8b  d8'  8b       d8 88         8b       88  `"Y8ba,   
    88     "88, "8b,   ,aa   `8b,d8'     `8bd8'  `8bd8'   "8a,   ,a8" 88         "8a,   ,d88 aa    ]8I  
    88       Y8b `"Ybbd8"'     Y88'        YP      YP      `"YbbdP"'  88          `"8bbdP"Y8 `"YbbdP"'  
                               d8'                                                                      
                              d8'                                                                       

*/

// Temp definition for documentation.  Will be corrected at the end of the file.
#define Iterator:%1<%2> Iterator:%1[]

/*-------------------------------------------------------------------------*//**
 * <param name="expr"><code>var : Iterator</code></param>
 * <remarks>
 * </remarks>
 *//*------------------------------------------------------------------------**/

//P:D(foreach(expr));
#define foreach(%0) for(new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0|||)

/*-------------------------------------------------------------------------*//**
 * <param name="params">The iterator function's parameters.</param>
 * <remarks>
 *  Used to declare a special iterator function.  Examples:
 *
 *  <code>
 * iterfunc stock OnlyZero(cur)                                                    <br />
 * {                                                                               <br /><indent />
 *  if (cur == -1)                                                              <br /><indent /><indent />
 *      return 0;                                                               <br /><indent />
 *  return -1;                                                                  <br />
 * }                                                                               <br />
 *  </code>
 *
 *  <code>
 * iterfunc stock AlsoOnlyZero[cellmin](cur)                                       <br />
 * {                                                                               <br /><indent />
 *  if (cur == cellmin)                                                         <br /><indent /><indent />
 *      return 0;                                                               <br /><indent />
 *  return cellmin;                                                             <br />
 * }                                                                               <br />
 *  </code>
 *
 *  <code>
 * iterfunc stock OneToTen[cellmin](cur)                                           <br />
 * {                                                                               <br /><indent />
 *  if (cur == cellmin)                                                         <br /><indent /><indent />
 *      return 1;                                                               <br /><indent />
 *  if (cur == 10)                                                              <br /><indent /><indent />
 *      return cellmin;                                                         <br /><indent />
 *  return cur + 1;                                                             <br />
 * }                                                                               <br />
 *  </code>
 *
 *  <code>
 * iterfunc stock OneToN(cur, n)                                                   <br />
 * {                                                                               <br /><indent />
 *  if (n &lt; 1)                                                               <br /><indent /><indent />
 *      return -1;                                                              <br /><indent />
 *  if (cur == -1)                                                              <br /><indent /><indent />
 *      return 1;                                                               <br /><indent />
 *  if (cur == n)                                                               <br /><indent /><indent />
 *      return -1;                                                              <br /><indent />
 *  return cur + 1;                                                             <br />
 * }                                                                               <br />
 *  </code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(iterfunc(params));
#define iterfunc%0(%1) F@y:%0(%1)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Iterator to run backwards.</param>
 * <remarks>
 *  Run an iterator backwards.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iterator@Reverse(Iterator:iter<>));
#define Iterator@Reverse%9;_:(%1=%9(%0)%9)%9; F@o)+_:F@p:F@q:$%1,%0$

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator array to initialise.</param>
 * <remarks>
 *  Wrapper for Iter_Init_Internal.  When <c>__COMPILER_NESTED_ELLIPSIS</c> is
 *  set, this isn't needed because multi-dimensional iterators can be
 *  initialised with the new <c>{{0, 1, ...), ...}</c> feature.  In that case
 *  <c>I@ = 0</c> is called as a <c>void</c> function that does nothing but ends
 *  in a semi-colon (<c>I@</c> is used a lot in YSI as a <c>do nothing</c>
 *  enabler).
 *
 * <code>native Iter_Init(IteratorArray:Name[]&lt;&gt;);</code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Init(Iterator:iter[]<>));
#if __COMPILER_NESTED_ELLIPSIS
	#define Iter_Init(%0) (I@=0)
#else
	#define Iter_Init(%0) Iter_Init_Internal(F@r(Iterator@%0),F@r(Iterator@%0)[0],F@s(Iterator@%0),F@s(Iterator@%0[]),F@r(Iter_Init@%0))
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to add the data to.</param>
 * <param name="value">Value to add to the iterator.</param>
 * <remarks>
 *  Wrapper for Iter_AddInternal.
 *
 * native Iter_Add(Iterator:Name&lt;&gt;, value);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Add(Iterator:iter<>, value));
#define Iter_Add _ITER<Add>
#define Iter_Add_InternalA(%0,%1,%9)    Iter_Add_InternalC(%0,_:%1,F@s(%1)-1,_:F@t:((%1[0]-%1[0])+%9))
#define Iter_Add_InternalB(%0,%2,%1,%9) Iter_Add_InternalD(%0[%2],_:%1,F@s(%1)-1-(%2),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to remove data from.</param>
 * <param name="value">Data to remove.</param>
 * <remarks>
 *  Wrapper for Iter_RemoveInternal.
 *
 * native Iter_Remove(Iterator:Name&lt;&gt;, value);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Remove(Iterator:iter<>, value));
#define Iter_Remove _ITER<Remove>
#define Iter_Remove_InternalA(%0,%1,%9)    Iter_Remove_InternalC(%0,_:%1,F@s(%1)-1,_:F@t:((%1[0]-%1[0])+%9))
#define Iter_Remove_InternalB(%0,%2,%1,%9) Iter_Remove_InternalD(%0[%2],_:%1,F@s(%1)-1-(%2),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the first free slot in.</param>
 * <remarks>
 *  Wrapper for Iter_Free_Internal.  Returns a slot NOT in the current
 *  iterator.
 *
 * native Iter_Free(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Free(Iterator:iter<>));
#define Iter_Free _ITER<Free>
#define Iter_Free_InternalA(%0,%1)    Iter_Free_Internal(_:%1,F@s(%1)-F@s(%0))
#define Iter_Free_InternalB(%0,%2,%1) Iter_Free_Internal(_:%1,F@s(%1)-F@s(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the multi-iterator to get the first free slot in.</param>
 * <remarks>
 *  Wrapper for Iter_FreeMulti_Internal.  Returns a slot NOT in the current
 *  multi-iterator.
 *
 * native Iter_FreeMulti(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_FreeMulti(Iterator:iter<,>, ));
#define Iter_FreeMulti _ITER<FreeMulti>
#define Iter_FreeMulti_InternalA(%0,%1)    Iter_FreeMulti_Internal(_:%1,F@s(%1),F@s(%1)-F@s(%0))
#define Iter_FreeMulti_InternalB(%0,%2,%1) Iter_FreeMulti_Internal(_:%1,F@s(%1),F@s(%1)-F@s(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to check membership of.</param>
 * <param name="value">Value to check.</param>
 * <remarks>
 *  Checks if the given value is in the given iterator.
 *
 * native Iter_Contains(Iterator:Name&lt;&gt;, value);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:Iter_Contains(Iterator:iter<>, value));
#define Iter_Contains(%0) (bool:_ITER<Contains>(%0))
#define Iter_Contains_InternalA(%0,%1,%9)     Iter_Contains_InternalC(_:%1,F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))
#define Iter_Contains_InternalB(%0,%2,%1,%9)  Iter_Contains_InternalD(%0[%2],_:%1,F@s(%1)-F@s(%0),-%2+F@s(%1)-1,_:F@t:((%1[0]-%1[0])+%9))
#define Iter_Contains_InternalD(%0,%1,%2,-+%8,%3) Iter_Contains_InternalC(%1,%2,%3)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to check membership of.</param>
 * <param name="value">Value to check.</param>
 * <returns>
 *  Index in which the value is contained in the multi-iterator.
 * </returns>
 * <remarks>
 *  Checks if the given value is in the given iterator, and if it is return which index it is contained.
 *
 * native Iter_GetMulti(Iterator:Name&lt;&gt;, value);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_GetMulti(Iterator:iter<,>, value));
#define Iter_GetMulti _ITER<GetMulti>
#define Iter_GetMulti_InternalA(%0,%1,%9)    Iter_GetMulti_Internal(_:%1,F@s(%1),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))
#define Iter_GetMulti_InternalB(%0,%2,%1,%9) Iter_GetMulti_Internal(_:%1,F@s(%1),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to remove data from.</param>
 * <param name="value">Data to remove.</param>
 * <param name="next">Container for the pointer to the next element.</param>
 * <remarks>
 *  Wrapper for Iter_SafeRemoveInternal.  Common use:
 *
 *  Iter_SafeRemove(iter, i, i);
 *
 * native Iter_SafeRemove(Iterator:Name&lt;&gt;, value, &amp;next);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_SafeRemove(Iterator:iter<>, value, &next));
#define Iter_SafeRemove _ITER<SafeRemove>
#define Iter_SafeRemove_InternalA(%0,%1,%9)    Iter_SafeRemove_InternalC(%0,_:%1,F@s(%1)-1,_:F@t:((%1[0]-%1[0])+%9))
#define Iter_SafeRemove_InternalB(%0,%2,%1,%9) Iter_SafeRemove_InternalD(%0[%2],_:%1,F@s(%1)-1-(%2),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to add a random slot to.</param>
 * <remarks>
 *  Wrapper for Iter_RandomAddInternal.
 *
 * native Iter_RandomAdd(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_RandomAdd(Iterator:iter<>));
#define Iter_RandomAdd _ITER<RandomAdd>
#define Iter_RandomAdd_InternalA(%0,%1)    Iter_RandomAdd_InternalC(%0,_:%1,F@s(%1)-1)
#define Iter_RandomAdd_InternalB(%0,%2,%1) Iter_RandomAdd_InternalD(%0,_:%1,F@s(%1)-F@s(%0),F@s(%0),F@s(%1)-1-(%2),%2)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to remove a random slot from.</param>
 * <remarks>
 *  Wrapper for Iter_RandomRemoveInternal.
 *
 * native Iter_RandomRemove(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_RandomRemove(Iterator:iter<>));
#define Iter_RandomRemove _ITER<RandomRemove>
#define Iter_RandomRemove_InternalA(%0,%1)    Iter_RandomRemove_InternalC(%0,_:%1,F@s(%1)-1)
#define Iter_RandomRemove_InternalB(%0,%2,%1) Iter_RandomRemove_InternalD(%0[%2],_:%1,F@s(%1)-F@s(%0),F@s(%1)-1-(%2))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get a random unused slot for.</param>
 * <remarks>
 *  Wrapper for Iter_RandomFree_Internal.
 *
 * native Iter_RandomFree(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_RandomFree(Iterator:iter<>));
#define Iter_RandomFree _ITER<RandomFree>
#define Iter_RandomFree_InternalA(%0,%1)    Iter_RandomFree_InternalC(%0,_:%1,F@s(%1)-1)
#define Iter_RandomFree_InternalB(%0,%2,%1) Iter_RandomFree_InternalD(%0,_:%1,F@s(%1)-F@s(%0),F@s(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get a random slot from.</param>
 * <remarks>
 *  Wrapper for Iter_RandomInternal.
 *
 * native Iter_Random(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Random(Iterator:iter<>));
#define Iter_Random _ITER<Random>
#define Iter_Random_InternalA(%0,%1)    Iter_Random_Internal(%0,(_:%1),F@s(%1)-1)
#define Iter_Random_InternalB(%0,%2,%1) Iter_Random_Internal(%0[%2],(_:%1),F@s(%1)-1-(%2))
#define Iter_Random_Internal(%0,(_:%1,%2),F@s(%9)%3) Iter_Random_Internal(%0,(_:%1),F@s(%1)%3,%2)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get a random slot from.</param>
 * <remarks>
 *  Returns the number of items in this iterator.
 *
 * native Iter_Count(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Count(Iterator:iter<>));
#define Iter_Count _ITER<Count>
#define Iter_Count_InternalA(%0,%1)    (%0)
#define Iter_Count_InternalB(%0,%2,%1) (%0[%2])

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to empty.</param>
 * <remarks>
 *  Wrapper for Iter_Clear_Internal.
 *
 *  Although it doesn't fit my normal strict spacing, the end of "B" is correct,
 *  namely: "_:F@s(%0),%2)".  This uses the "_:%0,)" macro to consume
 *  a trailing comma when nothing is given in "%2", so I can't have a leading
 *  space sadly.
 *
 *  "- 2" in place of the normal "- 1" is CORRECT!
 *
 * native Iter_Clear(IteratorArray:Name[]&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Clear(Iterator:iter<>));
#define Iter_Clear _ITER<Clear>
#define Iter_Clear_InternalA(%0,%1)           Iter_Clear_InternalC(_:%1,F@s(%1),F@s(%0),F@s(%1)-2,%0)
#define Iter_Clear_InternalB(%0,%2,%1)        Iter_Clear_InternalD(_:%1,F@s(%1),F@s(%0),F@s(%1)-F@s(%0),%0,%2)
#define Iter_Clear_InternalD(%0,%1,%2,%3,%4,) Iter_Clear_InternalC(%0,%1,%2,%3-1,%4)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the first free slot in.</param>
 * <remarks>
 *  Finds an empty slot in an iterator, adds that slot to the iterator, and
 *  returns the now added slot.
 *
 * native Iter_Alloc(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Alloc(Iterator:iter<>));
#define Iter_Alloc _ITER<Alloc>
#define Iter_Alloc_InternalA(%0,%1)    Iter_Alloc_InternalC(%0,_:%1,F@s(%1)-1)
#define Iter_Alloc_InternalB(%0,%2,%1) Iter_Alloc_InternalD(%0[%2],_:%1,F@s(%1)-1-(%2),F@s(%1)-F@s(%0))

/*

    88888888888                                                     db        88888888ba  88  
    88                        ,d                                   d88b       88      "8b 88  
    88                        88                                  d8'`8b      88      ,8P 88  
    88aaaaa     8b,     ,d8 MM88MMM 8b,dPPYba, ,adPPYYba,        d8'  `8b     88aaaaaa8P' 88  
    88"""""      `Y8, ,8P'    88    88P'   "Y8 ""     `Y8       d8YaaaaY8b    88""""""'   88  
    88             )888(      88    88         ,adPPPPP88      d8""""""""8b   88          88  
    88           ,d8" "8b,    88,   88         88,    ,88     d8'        `8b  88          88  
    88888888888 8P'     `Y8   "Y888 88         `"8bbdP"Y8    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to empty.</param>
 * <remarks>
 *  Uses a static array copy to blank the iterator instead of a loop.
 *
 *  BROKEN!
 *
 * native Iter_FastClear(IteratorArray:Name[]&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_FastClear(Iterator:iter<>));
#define Iter_FastClear _ITER<FastClear>
#define Iter_FastClear_InternalA(%0,%1);    {static YSII_Xg@Clear[F@s(%1)]={0,1,...};%1=YSII_Xg@Clear;%0=0;}
#define Iter_FastClear_InternalB(%0,%2,%1); {static YSII_Xg@Clear[F@s(%1)]={0,1,...},YSII_Yg@Clear[F@s(%0)]={0,0,...};%1=YSII_Xg@Clear;%0=YSII_Yg@Clear;}

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the start of.</param>
 * <remarks>
 *  Gets a point BEFORE the start of the iterator (the theoretical beginning).
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Begin(Iterator:iter<>));
#define Iter_Begin _ITER<Begin>
#define Iter_Begin_InternalA(%0,%1)    (F@s(%1)-F@s(%0))
#define Iter_Begin_InternalB(%0,%2,%1) (F@s(%1)-1-(%2))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the end of.</param>
 * <remarks>
 *  Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_End(Iterator:iter<>));
#define Iter_End _ITER<End>
#define Iter_End_InternalA(%0,%1)    (F@s(%1)-F@s(%0))
#define Iter_End_InternalB(%0,%2,%1) (F@s(%1)-1-(%2))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the first valid element in.</param>
 * <remarks>
 *  Gets the first element in an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_First(Iterator:iter<>));
#define Iter_First _ITER<First>
#define Iter_First_InternalA(%0,%1)    (%1[(F@s(%1)- F@s(%0))])
#define Iter_First_InternalB(%0,%2,%1) (%1[(F@s(%1)-1-(%2))])

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to</param>
 * <remarks>
 *  Gets the last element in an iterator.  Works by getting the previous item
 *  from the one BEFORE the first element (i.e. the one before the sentinel).
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Last(Iterator:iter<>));
#define Iter_Last _ITER<Last>
#define Iter_Last_InternalA(%0,%1)    ((%1[Iter_End_InternalA(%0,%1)-1])-1)
#define Iter_Last_InternalB(%0,%2,%1) (Iter_Prev_InternalB(%0,%2,%1,Iter_End_InternalB(%0,%2,%1)))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the next element in.</param>
 * <param name="cur">The current element.</param>
 * <remarks>
 *  Gets the element in an iterator after the current one.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Next(Iterator:iter<>, cur));
#define Iter_Next _ITER<Next>
#define Iter_Next_InternalA(%0,%1,%9)    (%1[_:F@t:((%1[0]-%1[0])+%9)])
#define Iter_Next_InternalB(%0,%2,%1,%9) (%1[_:F@t:((%1[0]-%1[0])+%9)])

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the previous element in.</param>
 * <param name="cur">The current element.</param>
 * <remarks>
 *  Gets the element in an iterator before the current one.  Slow.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Prev(Iterator:iter<>, cur));
#define Iter_Prev _ITER<Prev>
#define Iter_Prev_InternalA(%0,%1,%9)    (((%1[(_:((%1[0]-%1[0])+%9)-1)%F@s(%1)])-1)%F@s(%1))
#define Iter_Prev_InternalB(%0,%2,%1,%9) Iter_Prev_Internal(%1,F@s(%1)-F@s(%0),F@s(%1),_:F@t:((%1[0]-%1[0])+%9))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the true array of.</param>
 * <remarks>
 *  Accesses the internal array of an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_TrueArray(Iterator:iter<>));
#define Iter_TrueArray(%1) F@r(Iterator@%1)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the true count of.</param>
 * <remarks>
 *  Accesses the internal count of an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_TrueCount(Iterator:iter<>));
#define Iter_TrueCount(%1) F@r(Iter_Single@%1)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Multi iterator to get the true count of.</param>
 * <remarks>
 *  Accesses the internal count of a multi-iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_TrueMulti(Iterator:iter<,>));
#define Iter_TrueMulti(%1) F@r(Iter_Multi@%1)

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the true size of.</param>
 * <remarks>
 *  Accesses the internal size of an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_TrueSize(Iterator:iter<>));
#define Iter_TrueSize _ITER<TrueSize>
#define Iter_TrueSize_InternalA(%0,%1)    (F@s(%1))
#define Iter_TrueSize_InternalB(%0,%2,%1) (F@s(%1))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the true starts of.</param>
 * <remarks>
 *  Accesses the number of starts in a multi-iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Starts(Iterator:iter<>));
#define Iter_Starts _ITER<Starts>
#define Iter_Starts_InternalA(%0,%1)    (F@s(%0))
#define Iter_Starts_InternalB(%0,%2,%1) (F@s(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get the size of.</param>
 * <remarks>
 *  Accesses the size of an iterator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Size(Iterator:iter<>));
#define Iter_Size _ITER<Size>
#define Iter_Size_InternalA(%0,%1)    (F@s(%1)-F@s(%0))
#define Iter_Size_InternalB(%0,%2,%1) (F@s(%1)-F@s(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="iter">Name of the iterator to get a slot in by index.</param>
 * <param name="index">Index.</param>
 * <param name="wrap">Keep going around until a value is found?</param>
 * <remarks>
 *  Wrapper for Iter_Index_Internal.  Returns the Nth value in the iterator
 *  (requires looping due to the way iterators are stored and optimised for
 *  loops not direct access).
 *
 * native Iter_Index(Iterator:Name&lt;&gt;);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Iter_Index(Iterator:iter<>, index, bool:wrap = false));
#define Iter_Index _ITER<Index>
#define Iter_Index_InternalA(%0,%1,%9)    Iter_Index_Internal(%0,%1,F@s(%1)-1,F@s(%1)-1,_:F@t:((%1[0]-%1[0])+%9))
#define Iter_Index_InternalB(%0,%2,%1,%9) Iter_Index_Internal(%0[%2],%1,F@s(%1)-1-(%2),F@s(%1)-F@s(%0),_:F@t:((%1[0]-%1[0])+%9))

/*

    88b           d88                                                         
    888b         d888                                                         
    88`8b       d8'88                                                         
    88 `8b     d8' 88 ,adPPYYba,  ,adPPYba, 8b,dPPYba,  ,adPPYba,  ,adPPYba,  
    88  `8b   d8'  88 ""     `Y8 a8"     "" 88P'   "Y8 a8"     "8a I8[    ""  
    88   `8b d8'   88 ,adPPPPP88 8b         88         8b       d8  `"Y8ba,   
    88    `888'    88 88,    ,88 "8a,   ,aa 88         "8a,   ,a8" aa    ]8I  
    88     `8'     88 `"8bbdP"Y8  `"Ybbd8"' 88          `"YbbdP"'  `"YbbdP"'  

*/

// Remove trailing spaces.  This looks really unsafe because of the "%0\32;"
// allowing anything to come before the space, but it would have to be
// "anything" not text immediately following a "YSII_X@" prefix.
#define iterstart@%0\32;%1$ iterstart@%0%1$
#define Iterator@%0\32;%1$ Iterator@%0%1$
#define Iter_Func@%0\32;%1$ Iter_Func@%0%1$
#define Iter_Single@%0\32;%1$ Iter_Single@%0%1$
#define Iter_Multi@%0\32;%1$ Iter_Multi@%0%1$
#define Iter_Init@%0\32;%1$ Iter_Init@%0%1$

// Allow "iterfunc stock", "iterfunc stock", and other varieties.
// "iterfunc stock" is the hardest, because we have to detect it BEFORE our own
// macro, but still use it on the function itself.  It does nothing on the
// forward.
#define Iter_Func@stock stock Iter_Func@
#define Iter_Func@static static Iter_Func@
// Must do this manually I think.
//#define Iter_Func@foreign%0(%2) foreign Iter_Func@%0(%2)
//#define Iter_Func@global%0(%2) global Iter_Func@%0(%2)
#define Iter_Func@public public Iter_Func@
#define Iter_Func@forward forward Iter_Func@

// Drop modifiers - the only place these can appear is under `iterfunc` with the
// dummy variable, which we don't want to modify more than we already have.
#define Iterator@stock Iterator@
#define Iterator@static Iterator@
#define Iterator@public Iterator@
#define Iterator@forward Iterator@

#define iterstart@stock iterstart@
#define iterstart@static iterstart@
#define iterstart@public iterstart@
#define iterstart@forward iterstart@

#define ITER_TAG_FUNC(%0)%1(%2) %0:Iter_Func@%1(%2)

// Many tag types that may come up as iterator function return types.
#define Iter_Func@_:            ITER_TAG_FUNC(_)
#define Iter_Func@bool:         ITER_TAG_FUNC(bool)
#define Iter_Func@PlayerText3D: ITER_TAG_FUNC(PlayerText3D)
#define Iter_Func@Text3D:       ITER_TAG_FUNC(Text3D)
#define Iter_Func@DB:           ITER_TAG_FUNC(DB)
#define Iter_Func@DBResult:     ITER_TAG_FUNC(DBResult)
#define Iter_Func@Language:     ITER_TAG_FUNC(Language)
#define Iter_Func@Bit:          ITER_TAG_FUNC(Bit)
#define Iter_Func@Text:         ITER_TAG_FUNC(Text)
#define Iter_Func@Menu:         ITER_TAG_FUNC(Menu)
#define Iter_Func@Style:        ITER_TAG_FUNC(Style)
#define Iter_Func@XML:          ITER_TAG_FUNC(XML)
#define Iter_Func@Bintree:      ITER_TAG_FUNC(Bintree)
#define Iter_Func@Group:        ITER_TAG_FUNC(Group)
#define Iter_Func@Timer:        ITER_TAG_FUNC(Timer)
#define Iter_Func@File:         ITER_TAG_FUNC(File)
#define Iter_Func@Float:        ITER_TAG_FUNC(Float)

#define ITER_TAG(%0)%1={%2,%3,...}%4: %0:Iterator@%1={%0:%2,%0:%3,...}F@a$,Iter_Single@

// Many tag types for declared iterators.
#define Iterator@_:            ITER_TAG(_)
#define Iterator@bool:         ITER_TAG(bool)
#define Iterator@PlayerText3D: ITER_TAG(PlayerText3D)
#define Iterator@Text3D:       ITER_TAG(Text3D)
#define Iterator@DB:           ITER_TAG(DB)
#define Iterator@DBResult:     ITER_TAG(DBResult)
#define Iterator@Language:     ITER_TAG(Language)
#define Iterator@Bit:          ITER_TAG(Bit)
#define Iterator@Text:         ITER_TAG(Text)
#define Iterator@Menu:         ITER_TAG(Menu)
#define Iterator@Style:        ITER_TAG(Style)
#define Iterator@XML:          ITER_TAG(XML)
#define Iterator@Bintree:      ITER_TAG(Bintree)
#define Iterator@Timer:        ITER_TAG(Timer)
#define Iterator@File:         ITER_TAG(File)
#define Iterator@Float:        ITER_TAG(Float)

// This iterator is both a special function AND a tag.  This is not natively
// supported, so we need to invent some special macros to do so.  Fortunately,
// it is not a state function, so some of the existing macros are not needed.
#define Iterator@Group I@ Iterator@GroupElse_(-1)

// Tag.
#define I@%0Iterator@GroupElse_(%1): ITER_TAG(Group)

// The `Iterator@GroupElse_` macro is in "y_groups", so you only get it if you
// include both libraries.

// A nice "match" symbol that we can scan for, then remove after it is used.
#define F@a$
#define F@b|||

// Detect array declarations: "Iterator:X[20]<4>", "Iterator:X<10, 4>", and the
// frankly silly "Iterator:X[20]<10, 4>".
#define F@c:F@d:((%0,%1)+1)]%2$,Iter_Single@%9$%7$ F@d:((%0)+(%1))]={0,1,...}F@a$,Iter_Multi@%9$[%0]%7$
#if __COMPILER_NESTED_ELLIPSIS
	#define F@d:%0]%2$,Iter_%8@%9[%3$%7$ %0]={{0,1,...},...},Iter_%8@%9[%3$%7$
#else
	#define F@d:%0]%2$,Iter_%8@%9[%3$%7$ %0],Iter_%8@%9[%3$%7$,F@g(Iter_Init@%9,)=F@s(Iter_%8@%9[%3$)
#endif

// Special "sizeof" that strips subscripts.  "|||" prevents "sizeof" recursion.
#define F@e:%0|||(%1[%2]%3|||%4)) F@e:%0|||(%1%3|||%4[]))
#define F@f:%0|||(F@g(%1,%5)%3|||) %0|||(%1 %3|||)
#define F@s(%0) (_:F@f:F@e:sizeof F@b|||(%0 F@a$F@b|||))

// Reify macros.
#define F@r(%0) %0 F@a$
#define F@g(%0,%8) %0 F@a$
#define F@h:%0) %0 F@a$)

// Sort out tagged parameters plus extra parameters.  Expanded so it will fail
// to match parameters outside the required area.
//#define F@t:(%0,%1) (%0),%1
#define F@t:(%0) MACRO_PARSE<F@B:>((%0))
#define MACRO_PARSE<%0>(%1) %0_MACRO_PARSE:`%1`
#define _MACRO_PARSE:`%0` %0
#define F@B:%9`(%0,%1)` %9`(%0),%1`

// y_iterate parser.  Takes an array input, and splits up all the components.
#define _ITER<%5>(%1) (_:F@i:F@j:$Iter_%5_Internal(%1))

// Separate "<>"s.  Parameters to the resulting macro/function:
//  
//   %0 - Count.
//   %1 - Multi iterator position.
//   %2 - Array.
//  ... - All other parameters.
//  
#define F@j:%7$%5(%0)       %5A(F@g(Iter_Single@%0,),F@h:Iterator@%0)
#define F@i:%7$%5(%0<%2>%1) %5B(F@h:Iter_Multi@%0,%2,F@h:Iterator@%0%1)

#define _Y_ITER_DO_FOREACH(%1,%0) (_:F@n:F@A:F@m:F@a$%1,%0$

// Multi-iterator.
#define F@n:%9$%1,%0<%2>$ F@s(Iterator@%0)-1-(%2));_:(%1=Iterator@%0 F@a$[_:%1])<(F@s(Iterator@%0)-F@s(Iter_Multi@%0));

// Special iterator.
#define iterstart(%1)%9;_:(%9=Iter%9@%0$[_:%2]%9; F@o))-1+(_:%1));_:(%1)!=_:F@u:F@l:(%2=Iter_Func@%0$(_:%2));
#define iterstate iterstart

// Special iterators without extra defines.  Default to -1 start value.  The
// many extra brackets are needed to ensure that other macros match.
#define F@A:%9$%1,%0(%2)%8$ F@s(Iterator@%0)-1+_:((F@h:iterstart@%0))+_:F@x:F@h:Iterator@%0);_:(%1=Iter_Func@%0(%2)F@a$[_:%1])!=(F@s(Iterator@%0)-1+_:F@h:Iterator@%0+iterstart@%0);
#define F@x:%6);_:(%1=%9@%0(%2)%9[%4])!=%3; %6);_:(%1=Iter_Func@%0(%4,%2)%9)!=%3;

#define F@o))-1+(%5,%6));_:(%9)!=_:%9(%1=%2$(_:%1)); F@o))-1+(%5)),itrst:Iter_State@%1=itrst:(%6);_:(%5)!=_:F@u:F@l:(%1=%2$(_:Iter_State@%1,_:%1));

//#define F@l:%9$%1,%0(%2)%8$ F@r(Iterator@%0));_:(F@r(Iterator@%0))!=_:(%1=F@h:Iter_Func@%0(_:%1,%2));
#define F@u:F@l:(%0(%2)%8$(%1)%9) (%0(%1,%2)%8$%9)
#define F@l:(%0[%2]%8$(%1)%9) (%0(%1,%2)%8$%9)

// Normal iterator.
#define F@m:%9$%1,%0$ F@s(Iterator@%0)-1);_:(%1=Iterator@%0 F@a$[_:%1])!=(F@s(Iterator@%0)-1);

// Reverse multi-iterator.
#define F@p:%9$%1,%0<%2>$ F@s(Iterator@%0)-2-(%2)));_:(%1=Iter_Prev_InternalB(Iter_Multi@%0,,Iterator@%0,%1))<(F@s(Iterator@%0)-F@s(Iter_Multi@%0));

// Reverse normal iterator.
#define F@q:%9$%1,%0$ F@s(Iterator@%0)-2));_:(%1=Iter_Prev_InternalA(,Iterator@%0,%1))!=(F@s(Iterator@%0)-1);

// Special iterator function declaration.
#define F@y:%0(%1) Y_FOREACH_SQ:Iter_Func@%0[]$(%1);Y_FOREACH_STOCK stock const F@z:Iterator@%0=F@z:0,iterstart@%0=-1;Iter_Func@%0(%1)F@a$

#define Y_FOREACH_STOCK __:F@w:$

// Get rid of ALL square brackets after the first function name.
#define Y_FOREACH_SQ:%0[%1$ %0
#define F@w:%8$%0[%3]=%1,%5[%3]=%6;%2[%3](%4) %8$%0=%1,%5=%3;%2(%4)

// Currently unused:
// Part of y_text for some reason.
//#define F@k

// Make the internal state an array if there is more than one value.
#define itrst:%1=itrst:(%6,%7) %1[]={%6,%7}

// Ultimate macro: <a href="http://forum.sa-mp.com/showpost.php?p=3801730" />
#define u@$ 0]);
#define __:%0$ u@(u[_:%0 u@$

// Consume spaces in the iterator state variables.
#define Iter_State@%0\32;%1) Iter_State@%0%1)

/*-------------------------------------------------------------------------*//**
 *  The workings of these macros are very extensively documented at:
 *
 *      <a href="http://forum.sa-mp.com/showpost.php?p=2823668" />
	
 *//*------------------------------------------------------------------------**/

// This allows us to use "new" multiple times - stripping off ONLY whole words.
#define new%0|||%3|||%1:%2||| %3|||%0|||%1|||%2|||

// This one is called if the new syntax is required, but the state of "new" is
// as-yet unknown.  This attempts to call "%1" as a macro, if it starts with
// "new" as a whole word then it will (and will also helpfully strip off the
// "new" keyword for us).
#define Y_FOREACH_THIRD|||%9|||%1|||%2||| %1=Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2|||

// This is called if the "new" macro is called for a second time.
#define Y_FOREACH_FOURTH|||%1=Y_FOREACH_FIFTH|||%9|||%2||| new Y_FOREACH_SIXTH;%1|||Y_FOREACH_SEVENTH|||%2|||

// This is called when there are tags on the "new" declaration (%9 = "new ").
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1=%0:_Y_ITER_DO_FOREACH(%1,%2)

// This is called when there aren't.
#define Y_FOREACH_SIXTH;%1|||Y_FOREACH_SEVENTH|||%2||| %1=_Y_ITER_DO_FOREACH(%1,%2)

// This is called if "%1" didn't have "new" at the start.
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_DO_FOREACH(%1,%2)

// This is the old version, but DON'T add "new" because that already exists from
// the failed "new" macro call above.
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%2,%1||| using_deprecated_foreach_syntax,%1=_Y_ITER_DO_FOREACH(%1,%2)++using_deprecated_foreach_syntax

stock const
	// This variable is re-declared when you do "foreach (Player, i)" or similar
	// so that a warning is generated.  The warning will read:
	//   
	//   local variable "using_deprecated_foreach_syntax" shadows a variable at a preceding level
	//   
	// This is the best I could do to warn about the old syntax.  That code
	// should now be "foreach (new i : Player)".  It may become an error later.
	bool:using_deprecated_foreach_syntax = false,
	F@o = 1;


/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Creates a new iterator start/array pair.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#undef Iterator
P:D(Iterator:Iterator(name));
#define Iterator:%1<%2> Iterator@%1[_:F@c:F@d:((%2)+1)]={0,1,...}F@a$,Iter_Single@%1 F@a$F@a$
#define IteratorArray Iterator

