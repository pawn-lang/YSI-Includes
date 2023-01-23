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

#if defined YSI_TESTS
	#pragma option -E-

	#warning ==========================================
	#warning |                                        |
	#warning | Using `YSI_TESTS` will produce a huge  |
	#warning | number of warnings.  However, they're  |
	#warning |  all in tests and actually test that   |
	#warning |    warnings are correctly produced.    |
	#warning |                                        |
	#warning ==========================================
#endif

#define __COMPILER_NESTED_ELLIPSIS (1)
#define __compiler_one_string_parameter:%8(%0,%1) (%0)
#define __COMPILER_STRING_RETURN(%0) return (__compiler_one_string_parameter:(%0))
#define __COMPILER_BUGGED_STRING_RETURN (0)
#define __COMPILER_BUGGED_SYSREQ (0)
#define __COMPILER_WARNING_SUPPRESSION (1)
#define __COMPILER___EMIT (1)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Global variable used for <c>LREF</c> and <c>SREF</c> in the inline versions
 *   of <c>AMX_Read</c> and <c>AMX_Write</c>.
 * </remarks>
 */
stock YSI_gAMXAddress_;

#if __COMPILER___EMIT_U
	#define AMX_Read(%0) (_:(__emit( LOAD.U.pri %0, STOR.pri YSI_gAMXAddress_, LREF.pri YSI_gAMXAddress_ )))
	#define AMX_Write(%0,%1) __emit( PUSH.U %1, LOAD.U.pri %0, STOR.pri YSI_gAMXAddress_, POP.pri, SREF.pri YSI_gAMXAddress_ )
	#define AMX_Ref(%0) (_:(__emit( ADDR.U.pri %0 )))
#endif

// Error with:
//
//   const Float:X[] = Float:"hello";
//
#define __COMPILER_CONST_TAGGED (0)

// This MAY need to have the same code as the old compiler - generating variables that define
// the tags.  This is because `param = tagof (Float:)` doesn't seem to work.  I.e. you can't
// have a default argument of a tagof of a constant tag.
#define __COMPILER_TAG_DATA(%0,%1) stock %0:operator=(__CompilerDefault:a) return a, %0:(%1)

// Disable the recursion warning in the Russian compiler (and the unknown
// pragma warning in other compilers temporarily).
#pragma warning push
#pragma warning disable 207
#pragma disablerecursion
#pragma warning pop

// Check for accepted symbol names that are too long, since some (forked)
// compiler versions increase the limit but a lot of YSI code is hard-coded
// to 32 (31 + NULL).
#pragma warning push
#pragma warning disable 200

#if !defined __COMPILER_sNAMEMAX
	// Define a symbol of 32 characters.
	#define __COMPILER_SYMBOL_NAME_CHECK_1F
	// Then check if the same symbol extended to 32 characters exists.  If
	// it does, it is because the 32 character version was truncated to 31
	// characters (for which we temporarily disabled the warning), so the
	// 31 character version was found instead.  This means we know that the
	// limit (`sNAMEMAX`) is 31 characters.
	#if defined __COMPILER_SYMBOL_NAME_CHECK_1F@
		#define __COMPILER_sNAMEMAX (31)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_2F_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_2F_________padding@
		#define __COMPILER_sNAMEMAX (47)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_3F_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_3F_________padding_________padding@
		#define __COMPILER_sNAMEMAX (63)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_4F_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_4F_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (79)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_5F_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_5F_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (95)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_6F_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_6F_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (111)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_7F_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_7F_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (127)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_8F_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_8F_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (143)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_9F_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_9F_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (159)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_AF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_AF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (175)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_BF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_BF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (191)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_CF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_CF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (207)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_DF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_DF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (223)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_EF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_EF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (239)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#define __COMPILER_SYMBOL_NAME_CHECK_FF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding
	#if defined __COMPILER_SYMBOL_NAME_CHECK_FF_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding_________padding@
		#define __COMPILER_sNAMEMAX (255)
	#endif
#endif
#if !defined __COMPILER_sNAMEMAX
	#warning Could not determine `sNAMEMAX`, falling back on 31.

	#define __COMPILER_sNAMEMAX (31)
#endif

#pragma warning pop

// Disable the warning for `const &var`.
#define __COMPILER_CONST_REF (1)

#if __PawnBuild < 10 || defined __optimisation
	#endinput
#endif

// Requires __addressof.
forward __CompilerAddress1();
forward __CompilerAddress2(a, b);

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The first function to get the address of, to compare against another one to
 *   determine the optimisation level.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public __CompilerAddress1()
{
	__CompilerAddress2(1, 2);
	// Function size in cells for various (-O, -d) combinations:
	// 0, 0 = 13
	// 0, 1 = 14
	// 0, 2 = 15
	// 1, 0 = 11
	// 1, 1 = 12
	// 1, 2 = 13
	// 2, 0 = 10
	// 2, 1 = 11
	// 2, 2 = 12
}

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The second function to get the address of, to compare against another one
 *   to determine the optimisation level.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public __CompilerAddress2(a, b)
{
}

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   When the compiler has <c>__addressof</c> we can determine the optimisation
 *   level (<c>-o</c>) by comparing the addresses of two functions.  Two
 *   functions that are next to each other in code are placed next to each other
 *   in the AMX as well, so the different in start addresses will tell us
 *   exactly how many cells make up the code in the first one.
 * </remarks>
 */
const __CompilerAddress = __addressof(__CompilerAddress2) - __addressof(__CompilerAddress1);

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The current optimsation level.
 * </remarks>
 */
#if __debug == 0
	#if __CompilerAddress == 13 * cellbytes
		const __optimisation = 0;
	#elseif __CompilerAddress == 11 * cellbytes
		const __optimisation = 1;
	#elseif __CompilerAddress == 10 * cellbytes
		const __optimisation = 2;
	#else
		#error Unknown optimisation level.
	#endif
#elseif __debug == 1
	#if __CompilerAddress == 14 * cellbytes
		const __optimisation = 0;
	#elseif __CompilerAddress == 12 * cellbytes
		const __optimisation = 1;
	#elseif __CompilerAddress == 11 * cellbytes
		const __optimisation = 2;
	#else
		#error Unknown optimisation level.
	#endif
#elseif __debug == 2
	#if __CompilerAddress == 15 * cellbytes
		const __optimisation = 0;
	#elseif __CompilerAddress == 13 * cellbytes
		const __optimisation = 1;
	#elseif __CompilerAddress == 12 * cellbytes
		const __optimisation = 2;
	#else
		#error Unknown optimisation level.
	#endif
#else
	// Optimisations are disabled with `-d3`.
	const __optimisation = 0;
#endif

/*
                                                                                                  
     ad88888ba  888888888888  ,ad8888ba,    88888888ba   88  
    d8"     "8b      88      d8"'    `"8b   88      "8b  88  
    Y8,              88     d8'        `8b  88      ,8P  88  
    `Y8aaaaa,        88     88          88  88aaaaaa8P'  88  
      `"""""8b,      88     88          88  88""""""'    88  
            `8b      88     Y8,        ,8P  88           ""  
    Y8a     a8P      88      Y8a.    .a8P   88           aa  
     "Y88888P"       88       `"Y8888Y"'    88           88  
                                                         
                                                         

*/

// There is a `#endinput` above.  Don't put new code down here!

