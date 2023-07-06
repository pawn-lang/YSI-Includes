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

#if __Pawn >= 0x0400
	#error YSI does not yet support PAWN 4.0
#elseif __Pawn < 0x0300
	#error YSI does not yet support PAWN 2.0/1.0
#endif

// Die tabsize 0!
#pragma tabsize 4
#define tabsize%00%0\10;%0 _DUMMY_do_not_use_tabsize_0

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The debug level, but with a more consistent name for compiler-defined
 *   constants.
 * </remarks>
 */
const __debug = debug;

// Enable `P:D(func())` for forcing function-like macros in to documentation.
// For example:
//   
//  /**  
//   * <param name="playerid">An example named macro parameter (<c>%0</c>).</param>
//   * <remarks>
//   *   This is a function-like macro.  By default, compiling with <c>-r</c> does
//   *   not put macros in the XML, which is a shame if we are using a macro to
//   *   fake a function, because then a function will be apparently missing
//   *   from the documentation.  Instead, we make a function, THEN make the
//   *   macro.  But, importantly, we only make the function on the first pass,
//   *   not the second pass (documentation is apparently generated in the first
//   *   pass).
//   * </remarks>
//   * <example>
//   *
//   *   for (new i = 0; MyFunc(i); ++i)
//   *   {
//   *     printf("%d", i);
//   *   }
//   *
//   * </example>
//   */
//   P:D(bool:MyFunc(playerid));
//   #define MyFunc(%0) ((%0) < MAX_PLAYERS)
//   

#if YSI_OPTIONAL(P)
	#define P:%1(%2); Debug_Print%1(%2);
#endif

#if YSI_OPTIONAL(C)
	#define C:%1{%2} Debug_Code%1{%2}
#endif

#if charbits != 8
	#error YSI assumes `charbits` is 8.
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The number of bytes in a cell.  There is the number of bits as a constant
 *   built-in, but not the number of bytes.
 * </remarks>
 */
#if defined cellbytes
	static stock YSI_cellbytes__ = 0;
#else
	const cellbytes = cellbits / charbits;
#endif

// This will define a symbol - `__COMPILER_OS` equal to either `__COMPILER_UNIX`
// or `__COMPILER_WINDOWS` depending on where the code is being built.  It does
// this in a very simple manner - by trying to include a file by the wrong name,
// by which I mean ignoring case.  The file is saved as `y_determine_os.inc`,
// but is included as `Y_dEtErMiNe_Os`.  On a case-insensitive OS (Windows) this
// still works because the files are considered to be the same, but on Unix it
// fails because they aren't.  Thus it uses `#tryinclude` to not error on Unix,
// sets Unix as the default OS, and changes the OS in the include file if the
// inclusion worked.  Note that only one letter difference was really needed -
// the excessive changes in case weren't required, but were fun.
#define __COMPILER_UNIX (0)
#define __COMPILER_WINDOWS (1)
#define __COMPILER_OS __COMPILER_UNIX
#tryinclude "Y_dEtErMiNe_Os"

#if defined __CompilerThirdPass
	#error Somehow got a fourth compiler pass.  Please tell Y_Less how.
#elseif defined __CompilerSecondPass
	#define __COMPILER_PASS (2)
	#define __COMPILER_GENERATING (1)
	#define __COMPILER_DOCUMENTING (0)
	#define __COMPILER_1ST_PASS (0)
	#define __COMPILER_2ND_PASS (0)
	#define __COMPILER_3RD_PASS (1)
#elseif defined __CompilerFirstPass
	#define __COMPILER_PASS (1)
	#define __COMPILER_GENERATING (1)
	#define __COMPILER_DOCUMENTING (0)
	#define __COMPILER_1ST_PASS (0)
	#define __COMPILER_2ND_PASS (1)
	#define __COMPILER_3RD_PASS (0)
#else
	#define __COMPILER_PASS (0)
	#define __COMPILER_GENERATING (0)
	#define __COMPILER_DOCUMENTING (1)
	#define __COMPILER_1ST_PASS (1)
	#define __COMPILER_2ND_PASS (0)
	#define __COMPILER_3RD_PASS (0)
#endif

#define __COMPILER_FIRST_PASS  __COMPILER_1ST_PASS
#define __COMPILER_SECOND_PASS __COMPILER_2ND_PASS
#define __COMPILER_THIRD_PASS __COMPILER_3RD_PASS

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Exist purely to be detected before they are used.  If that check succeedes,
 *   the compiler is on its second or third pass and already has a list of all
 *   functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_FIRST_PASS
	static stock __CompilerFirstPass() {}
#else
	static stock __CompilerFirstPass__() {}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Exist purely to be detected before they are used.  If that check succeedes,
 *   the compiler is on its second or third pass and already has a list of all
 *   functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_SECOND_PASS
	static stock __CompilerSecondPass() {}
#else
	static stock __CompilerSecondPass__() {}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Exist purely to be detected before they are used.  If that check succeedes,
 *   the compiler is on its second or third pass and already has a list of all
 *   functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_THIRD_PASS
	static stock __CompilerThirdPass() {}
#else
	static stock __CompilerThirdPass__() {}
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Determines if strings are packed by default or not.  Simply a string with a
 *   single character in, whose size is tested straight after.  If packing is
 *   on, then the string will only be one cell big.  If it isn't, two.
 * </remarks>
 */
static stock const __COMPILER_PACKED_TEST[] = " ";

#if sizeof (__COMPILER_PACKED_TEST) == 1
	#define __COMPILER_STRING_PACKING (1)
	#define __COMPILER_PACK
	#define __COMPILER_UNPACK !""
	#define __COMPILER_PREFIX_CHARSOF(%0) (sizeof (%0))
	#define __COMPILER_BASIC_CHARSOF(%0) ((sizeof (%0)) * cellbytes)
	#define __COMPILER_PREFIX_CHAR
	#define __COMPILER_BASIC_CHAR char
#else
	#define __COMPILER_STRING_PACKING (0)
	#define __COMPILER_PACK !""
	#define __COMPILER_UNPACK
	#define __COMPILER_PREFIX_CHARSOF(%0) ((sizeof (%0) - 1) / cellbytes + 1)
	#define __COMPILER_BASIC_CHARSOF(%0) (sizeof (%0))
	#define __COMPILER_PREFIX_CHAR char
	#define __COMPILER_BASIC_CHAR
#endif

#define __COMPILER_UNPACKEDMAX ((1<<cellbits)-1)

#include "y_compilerdata_codepage"

#define __COMPILER_BUG_317 (1)
#define __COMPILER_NAMEOF (0)
#define __COMPILER_PRAGMA (0)
#define __COMPILER___EMIT_U (0)
#define __COMPILER_FUNC_DECL_BUG (0)
#define __COMPILER_ADDRESSOF (0)

#define __COMPILER_STATIC_ENUM enum
#define __COMPILER_CONST_STATIC const

// Generate macro opcodes?
#define __COMPILER_O2 (0)

// Has `#pragma option`
#define __COMPILER_OPTION (0)

// Example:
//
//   #define this. THIS__(Entity)
//   this.GetAngle();
//
// Becomes:
//
//   Entity_GetAngle(this);
//
// And if #234 (or even just a `__tagof` precursor) is made it just becomes:
//
//   #define THIS__(%0)%1(%2) __tagof(this).%1(__tagof(this):_:this,%2)
//
// Unfortunately making it this:
//
//   #define THIS__(%0) this.
//
// Is a recursive definition and will hang the compiler in an infinite loop.
// Trying to defer the replacements with something like:
//
//   #define THIS__(%0) this PP_DEFER.
//
// Would prevent the infinite loop, but then may not be valid syntax - it
// depends if we want `this .Func` to work as opposed to just `this.Func`.  I
// personally think no, because then that doesn't look like normal symbols and
// behaves differently in terms of macro replacements.  This also falls foul of
// another warning I noted in the discussion of #234, that of `this` now
// appearing in the output twice and this being subject to macro replacements
// twice.  However, since doing it for `this` only is a small subset of the
// functionality suggested by #234 this is less of an issue than would happen in
// the generic case - we know exactly what `#define this` is, and thus don't
// need to worry about the effect of multiple replacements.  Actually, even if
// `__tagof` is added, there's no real need to change this definition - it
// already works in the special cases for which it is defined.
//
// I've not yet worked out a way to support both of these at once:
//
//   this.Data[ANGLE] = this.GetAngle();
//
// Becoming:
//
//   Entity_Data[this][ANGLE] = Entity_GetAngle(this);
//
// While I can detect `)` or `]`, I can't until after the opening brackets.
#define THIS__(%0)%1(%2) %0_%1(%0:this__,%2)
#define this__,) this__)
#define __COMPILER_THIS (0)

// Don't define `__PawnBuild` if it doesn't exist, but do create an alternate
// symbol (with a consistent naming scheme) that always exists.
#if defined __pawn_build
	#undef __pawn_build
#endif
#if defined __PawnBuild
	#if __PawnBuild == 0
		#undef __PawnBuild
		#define __pawn_build 0
	#else
		#define __pawn_build __PawnBuild
	#endif
#else
	#define __pawn_build 0
#endif

#if (__Pawn & 0x0F) >= 0x0A
	#define __COMPILER_MODIFIED (1)
	#define __COMPILER_OFFICIAL (0)

	#define __COMPILER_USER_WARNING (1)

	#if __pawn_build >= 2
		#undef __COMPILER_STATIC_ENUM
		#define __COMPILER_STATIC_ENUM static enum
	#endif
	#if __pawn_build >= 4
		#undef __COMPILER_OPTION
		#define __COMPILER_OPTION (1)
		#pragma option -(+
	#endif
	#if __pawn_build >= 8
		#undef __COMPILER_BUG_317
		#define __COMPILER_BUG_317 (0)
	#endif
	// I don't actually know when this was introduced.
	#if __pawn_build == 10
		#undef __COMPILER_FUNC_DECL_BUG
		#define __COMPILER_FUNC_DECL_BUG (1)
	#endif
	#if __pawn_build >= 10
		#if !__COMPILER_DOCUMENTING
			#undef __COMPILER___EMIT_U
			#define __COMPILER___EMIT_U (1)
		#endif

		#undef __COMPILER_ADDRESSOF
		#define __COMPILER_ADDRESSOF (1)
	#endif
	// Disable `__COMPILER_PRAGMA` for now, while there's no `PROC` generated.
	#if __pawn_build >= 11
		#undef __COMPILER_NAMEOF
		//#undef __COMPILER_PRAGMA
		
		#define __COMPILER_NAMEOF (1)
		//#define __COMPILER_PRAGMA (1)
		#undef __COMPILER_CONST_STATIC
		#define __COMPILER_CONST_STATIC const static
	#endif

	#if defined __optimisation
		#if __optimisation == 2
			#undef __COMPILER_O2
			#define __COMPILER_O2 (1)
		#endif
	#endif
#else
	#define __COMPILER_USER_WARNING (0)

	#define __COMPILER_MODIFIED (0)
	#define __COMPILER_OFFICIAL (1)
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This is a variable with the value <c>1</c>, and there is a macro of the
 *   same name with the value <c>0</c>.  The macro also looks for a semi-colon
 *   to match; however, if semi-colons are optional an end of line will also
 *   match a semi-colon in a macro.  We then use this name in a test that does
 *   NOT end with a semi-colon.  If <c>-;-</c> is active the macro will take
 *   precedence and produce <c>0</c>.  If <c>-;+</c> is active the macro will
 *   not match, and so the variable will be used instead.  Thus in this way we
 *   can detect the flag.
 * </remarks>
 *//*------------------------------------------------------------------------**/
const __COMPILER_DETERMINE_SEMICOLON = 1;
#define __COMPILER_DETERMINE_SEMICOLON%0; 0%0

// The macro looks for `;`, which isn't here.  So if it matches, we must have
// bypassed that requirement.
#if __COMPILER_DETERMINE_SEMICOLON == 0
	// `-;-`
	#define __COMPILER_SEMICOLON (0)

	// The macros `Debug_Code1` and `P:#` don't work without this.
	#pragma semicolon 1

	#if __COMPILER_USER_WARNING
		#define Y_COMPILERDATA_WARNING 2
		#include "y_compilerdata_warning"
	#endif
#else
	#define __COMPILER_SEMICOLON (1)
#endif

#if __COMPILER_MODIFIED
	#if defined __compat
		#define __COMPILER_COMPAT (1)
	#else
		#define __COMPILER_COMPAT (0)
	#endif
#else
	#define __COMPILER_COMPAT (0)
#endif

#if __COMPILER_OFFICIAL || __COMPILER_COMPAT
	#define __COMPILER_INCLUDE_GUARDS (1)
#else
	#define __COMPILER_INCLUDE_GUARDS (0)
#endif

#define __MACRO__bool: bool:__MACRO__
#define __MACRO__Iterator: Iterator:__MACRO__
#define __MACRO__Float: Float:__MACRO__
#define __MACRO__Alloc: Alloc:__MACRO__

#define Debug_PrintD_OPEN (
#define Debug_PrintD_CLOSE )

/// <p/>

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   One version of the compiler changed the definition of <c>sizeof</c> on enum
 *   elements to return their apparent "array" size, not their true size of
 *   <c>1</c>.  The change was to match people's misunderstanding of the syntax,
 *   rather than the correct interpretation of what enums are.  This is an enum
 *   with a multi-cell increment within it used to detect which enum sizeof
 *   method is in use.
 * </remarks>
 */

enum __E_COMPILER_ENUM
{
	__E_COMPILER_ENUM_ENTRY[3],
	__E_COMPILER_ENUM_AFTER
}

static stock __E_COMPILER_ENUM:_@__E_COMPILER_ENUM() { return __E_COMPILER_ENUM; }

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Declares a variable with the enum sizeof determination enum, so that the
 *   size of one of its elements can be taken later.
 * </remarks>
 */
static stock const
	__YSI_gsCompilerEnum[__E_COMPILER_ENUM];

#if sizeof (__YSI_gsCompilerEnum[__E_COMPILER_ENUM_ENTRY]) == 3
	#define __COMPILER_SIZEOF_ENUM (1)
#else
	#define __COMPILER_SIZEOF_ENUM (0)
#endif

#if !__COMPILER_NAMEOF
	// Allow `__nameof(Float:)` as `__nameof(Float)` and
	// `__nameof(Float:Function)` as `__nameof(Function)`.
	#define __CMPRC:tagof(%0:%1),%0:%1) __CMPRA:__CMPRB:tagof(%0:%1:),%0:%1:)
	#define __CMPRA:__CMPRB:tagof(%0::),%0::) %0)
	#define __CMPRB:tagof(%0:%1:),%0:%1:) tagof(%1),#%1)
	
	// Check the symbol exists with `tagof`, then return the name as a string.
	#define __nameof(%0) (__CMPRC:tagof(%0),#%0)
#endif

#define __COMPILER_DECL (0)

#if __COMPILER_DECL
	#define DECL__ decl
#else
	#define DECL__%0; PP_SINGLE_VAR<DO_DECL_SKIP>%0,$new %0;
	#define DO_DECL_SKIP(%0)%1; goto decl_skip_ %0;PP_DISCARD[]$%1;decl_skip_ %0:PP_DISCARD[]$
	#define goto%0:%1;%8$%2;%3:%4:%9$ goto decl_skip_ %1;%8$%2;decl_skip_ %4:%9$
	#define decl_skip_%9\32;%1[%9]%3$%4;decl_skip_%9\32;%5[%9]%6$ decl_skip_%1;PP_DISCARD[]$%4;decl_skip_%5:PP_DISCARD[]$

	#if YSI_KEYWORD(decl)
		#define decl DECL__
	#endif
#endif

// https://github.com/pawn-lang/compiler/issues/719
#define __COMPILER_NAMED.

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The <c>default()</c> feature allows declaring a variable with the initial
 *   value determined by the tag of the variable.  This is done by assigning to
 *   the variable from another variable (this variable) with a special internal
 *   tag, and using assignment operator overloads to look up the correct
 *   initial value for the target tag.
 * </remarks>
 */
const __CompilerDefault:__COMPILER_DEFAULT = __CompilerDefault:0;

#if YSI_KEYWORD(default)
	// Return a version of `undefined` for any tag.
	// 
	//   new                Float:a = default(); // 0.0
	//   new             Language:b = default(); // -1
	//   new PR_PacketReliability:a = default(); // 6
	#define default() __COMPILER_DEFAULT
#endif
#define DEFAULT__ __COMPILER_DEFAULT

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The current optimisation level, spelt correctly.
 * </remarks>
 */
#if defined __optimization
	const __optimisation = __optimization;
#else
	static stock __optimization__ = 0;
#endif

#if __COMPILER_MODIFIED
	#include "y_compilerdata_new"
#else
	#include "y_compilerdata_old"
#endif

#if !__COMPILER_PRAGMA
	#include "y_compilerdata___pragma"
#endif

// Blank function that does nothing except returns.
#define __COMPILER_UNUSED(%0) __pragma("unused", %0)
#define __COMPILER_NAKED() __pragma("naked")

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The current optimisation level, but we don't know it.
 * </remarks>
 */
#if defined __optimisation
	static stock __optimisation__ = -1;
#else
	// Unknown optimisation level.
	const __optimisation = -1;
#endif

#define __COMPILER_ARRAY_RETURN __COMPILER_STRING_RETURN	

//#if !__COMPILER_CONST_TAGGED
//	// Fix for bugged const assignments.
//	#define _yI@%0\32; _yI@
//	#define const%0:%1[%2]=%3:%4; const _yI@%1[%2]=%4,%0:%1[sizeof(_yI@%1)];PREINIT__ %1()_YSI_ConstCpy__(_:(%1),(_yI@%1),0,sizeof(%1)*4,sizeof(%1));
//#endif

// Consistent naming of compiler defined values. 
#define __Line __line
#define __File __file
#define __Date __date
#define __Time __time
#define __Compat __compat
#define __Emit __emit

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbytes</c>.
 * </remarks>
 */
const __CellBytes = cellbytes;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbits</c>.
 * </remarks>
 */
const __CellBits = cellbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbits</c>.
 * </remarks>
 */
const __CellBits = cellbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>charbits</c>.
 * </remarks>
 */
const __CharBits = charbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>charmax</c>.
 * </remarks>
 */
const __CharMax = charmax;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>ucharmax</c>.
 * </remarks>
 */
const __UCharMax = ucharmax;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbytes</c>.
 * </remarks>
 */
const __cellbytes = cellbytes;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbits</c>.
 * </remarks>
 */
const __cellbits = cellbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>cellbits</c>.
 * </remarks>
 */
const __cell_bits = cellbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>charbits</c>.
 * </remarks>
 */
const __char_bits = charbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>charmax</c>.
 * </remarks>
 */
const __char_max = charmax;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>ucharmax</c>.
 * </remarks>
 */
const __uchar_max = ucharmax;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (compiler internal) spelling of <c>__Pawn</c>.
 * </remarks>
 */
const __pawn = __Pawn;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (YSI internal) spelling of <c>cellbytes</c>.
 * </remarks>
 */
const __COMPILER_CELL_BYTES = cellbytes;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (YSI internal) spelling of <c>cellbits</c>.
 * </remarks>
 */
const __COMPILER_CELL_BITS  = cellbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Alternate (YSI internal) spelling of <c>charbits</c>.
 * </remarks>
 */
const __COMPILER_CHAR_BITS  = charbits;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   How much to shift a cell count by to get a byte count.
 * </remarks>
 */
#if cellbits == 8
	const __COMPILER_CELL_SHIFT = 0;
	#error YSI assumes `cellbits` is 32 or 64.
#elseif cellbits == 16
	const __COMPILER_CELL_SHIFT = 1;
	#error YSI assumes `cellbits` is 32 or 64.
#elseif cellbits == 32
	const __COMPILER_CELL_SHIFT = 2;
#elseif cellbits == 64
	const __COMPILER_CELL_SHIFT = 3;
#else
	#error Unknown `cellbits` size.
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   How much to shift a cell count by to get a bit count.
 * </remarks>
 */
#if cellbits == 8
	const __COMPILER_BIT_SHIFT = 3;
	#error YSI assumes `cellbits` is 32 or 64.
#elseif cellbits == 16
	const __COMPILER_BIT_SHIFT = 4;
	#error YSI assumes `cellbits` is 32 or 64.
#elseif cellbits == 32
	const __COMPILER_BIT_SHIFT = 5;
#elseif cellbits == 64
	const __COMPILER_BIT_SHIFT = 6;
#else
	#error Unknown `cellbits` size.
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   A mask to return numbers modulo <c>cellbits</c>.
 * </remarks>
 */
const __COMPILER_BIT_MASK = cellbits - 1;

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The maximum array required to store a symbol name.  i.e.
 *   <c>__snamemax + 1</c>.
 * </remarks>
 */
const FUNCTION_LENGTH = __COMPILER_sNAMEMAX + 1;

// Core tags.
#if defined _INC_indirection
	stock File:operator=(__CompilerDefault:a) return a, File:(0);
	stock Float:operator=(__CompilerDefault:a) return a, Float:(0);
#else
	__COMPILER_TAG_DATA(Float, 0);
	__COMPILER_TAG_DATA(File, 0);
#endif
__COMPILER_TAG_DATA(_, 0);
__COMPILER_TAG_DATA(bool, 0);
__COMPILER_TAG_DATA(filemode, 0);
__COMPILER_TAG_DATA(seek_whence, 0);
__COMPILER_TAG_DATA(floatround_method, 0);
__COMPILER_TAG_DATA(anglemode, 0);

// SA:MP tags.
__COMPILER_TAG_DATA(DB, 0);
__COMPILER_TAG_DATA(DBResult, 0);
__COMPILER_TAG_DATA(Text, 65535);
__COMPILER_TAG_DATA(PlayerText, 65535);
__COMPILER_TAG_DATA(Menu, 255);
__COMPILER_TAG_DATA(Text3D, 65535);
__COMPILER_TAG_DATA(PlayerText3D, 65535);

// open.mp tags.
__COMPILER_TAG_DATA(T_CP_TYPE, 0)
__COMPILER_TAG_DATA(T_WEAPON, -1);
__COMPILER_TAG_DATA(T_WEAPON_SLOT, -1);
__COMPILER_TAG_DATA(T_PLAYER_MARKERS_MODE, -1);
__COMPILER_TAG_DATA(T_DIALOG_STYLE, 0);
__COMPILER_TAG_DATA(T_HTTP_METHOD, 1);
__COMPILER_TAG_DATA(T_HTTP_ERROR, 0);
__COMPILER_TAG_DATA(T_CONNECTION_STATUS, 0);
__COMPILER_TAG_DATA(T_DOWNLOAD_REQUEST, 0);
__COMPILER_TAG_DATA(T_SELECT_OBJECT, 0);
__COMPILER_TAG_DATA(T_OBJECT_MATERIAL_SIZE, 0);
__COMPILER_TAG_DATA(T_EDIT_RESPONSE, 0);
__COMPILER_TAG_DATA(T_PLAYER_STATE, 0);
__COMPILER_TAG_DATA(T_SPECIAL_ACTION, 0);
__COMPILER_TAG_DATA(T_FIGHT_STYLE, 4);
__COMPILER_TAG_DATA(T_WEAPONSKILL, 0);
__COMPILER_TAG_DATA(T_WEAPONSTATE, -1);
__COMPILER_TAG_DATA(T_KEY, 0);
__COMPILER_TAG_DATA(T_CAM_MOVE, 1);
__COMPILER_TAG_DATA(T_CAM_MODE, 0);
__COMPILER_TAG_DATA(T_MAPICON, 0);
__COMPILER_TAG_DATA(T_SPECTATE_MODE, 1);
__COMPILER_TAG_DATA(T_FORCE_SYNC, 0);
__COMPILER_TAG_DATA(T_CLICK_SOURCE, 0);
__COMPILER_TAG_DATA(T_BULLET_HIT_TYPE, 0);
__COMPILER_TAG_DATA(T_TEXT_DRAW_FONT, 0);
__COMPILER_TAG_DATA(T_TEXT_DRAW_ALIGN, 1);
__COMPILER_TAG_DATA(T_VARTYPE, 0);
__COMPILER_TAG_DATA(T_CARMODTYPE, -1);
__COMPILER_TAG_DATA(T_VEHICLE_MODEL_INFO, 0);
__COMPILER_TAG_DATA(T_VEHICLE_PANEL_STATUS, 0);
__COMPILER_TAG_DATA(T_VEHICLE_DOOR_STATUS, 0);
__COMPILER_TAG_DATA(T_VEHICLE_LIGHT_STATUS, 0);
__COMPILER_TAG_DATA(T_VEHICLE_TYRE_STATUS, 0);

#if __COMPILER_MODIFIED
	// Avoid truncation.
	stock const T_OBJECT_MATERIAL_TEXT_ALIGN:__TAGOF__T_OBJECT_MATERIAL_TEXT;
	stock T_OBJECT_MATERIAL_TEXT_ALIGN:operator=(__CompilerDefault:a) return a, T_OBJECT_MATERIAL_TEXT_ALIGN:(0);

	stock const T_PLAYER_RECORDING_TYPE:__TAGOF__T_PLAYER_RECORDING;
	stock T_PLAYER_RECORDING_TYPE:operator=(__CompilerDefault:a) return a, T_PLAYER_RECORDING_TYPE:(0);
#else
	stock T_OBJECT_MATERIAL_TEXT_ALIGN:operator=(__CompilerDefault:a) return a, T_OBJECT_MATERIAL_TEXT_ALIGN:(0);
	stock T_PLAYER_RECORDING_TYPE:operator=(__CompilerDefault:a) return a, T_PLAYER_RECORDING_TYPE:(0);
#endif

// YSI tags.
__COMPILER_TAG_DATA(Language, -1);
__COMPILER_TAG_DATA(Bit, 0);
__COMPILER_TAG_DATA(Bitmap, 0);
__COMPILER_TAG_DATA(Style, 0);
__COMPILER_TAG_DATA(XML, -1);
__COMPILER_TAG_DATA(XMLEntry, -1);
__COMPILER_TAG_DATA(Bintree, 0);
__COMPILER_TAG_DATA(Group, -1);
__COMPILER_TAG_DATA(Timer, 0);
__COMPILER_TAG_DATA(INI, -1);

// PawnPlus tags.
__COMPILER_TAG_DATA(String@Const, -1);
__COMPILER_TAG_DATA(String, -1);
__COMPILER_TAG_DATA(error_level, 0);
__COMPILER_TAG_DATA(locale_category, 0);
__COMPILER_TAG_DATA(filter_type, 0);
__COMPILER_TAG_DATA(handler_flags, 0);
__COMPILER_TAG_DATA(Variant, -1);
__COMPILER_TAG_DATA(Variant@Const, -1);
__COMPILER_TAG_DATA(Iter, -1);
__COMPILER_TAG_DATA(Handle, -1);
__COMPILER_TAG_DATA(tag_uid, 0);
__COMPILER_TAG_DATA(Task, 0);
__COMPILER_TAG_DATA(LinkedList, 0);
__COMPILER_TAG_DATA(List, 0);
__COMPILER_TAG_DATA(Map, 0);
__COMPILER_TAG_DATA(tag_op, 0);
__COMPILER_TAG_DATA(fork_level, 0);
__COMPILER_TAG_DATA(Amx, 0);
__COMPILER_TAG_DATA(Var, 0);
__COMPILER_TAG_DATA(amx_err, 0);
__COMPILER_TAG_DATA(str_create_mode, 0);
__COMPILER_TAG_DATA(AmxString, 0);
__COMPILER_TAG_DATA(ConstAmxString, 0);
__COMPILER_TAG_DATA(AmxStringBuffer, 0);
__COMPILER_TAG_DATA(AmxVariant, 0);
__COMPILER_TAG_DATA(ConstAmxVariant, 0);
__COMPILER_TAG_DATA(AmxVariantBuffer, 0);
__COMPILER_TAG_DATA(Guard, 0);
__COMPILER_TAG_DATA(CallbackHandler, 0);
__COMPILER_TAG_DATA(NativeHook, 0);
__COMPILER_TAG_DATA(Pool, 0);
__COMPILER_TAG_DATA(Expression, 0);
__COMPILER_TAG_DATA(Symbol, 0);
// I'm not doing the generic tags as well...

// Streamer tags.
__COMPILER_TAG_DATA(DynamicObject, 0);
__COMPILER_TAG_DATA(DynamicPickup, 0);
__COMPILER_TAG_DATA(DynamicCP, 0);
__COMPILER_TAG_DATA(DynamicRaceCP, 0);
__COMPILER_TAG_DATA(DynamicMapIcon, 0);
__COMPILER_TAG_DATA(DynamicText3D, 0);
__COMPILER_TAG_DATA(DynamicArea, 0);
__COMPILER_TAG_DATA(DynamicActor, 0);
__COMPILER_TAG_DATA(T_STREAMER_TYPE, -1);

// Pawn.Regex tags.
__COMPILER_TAG_DATA(E_REGEX_GRAMMAR, 0);
__COMPILER_TAG_DATA(E_REGEX_FLAG, 1);
__COMPILER_TAG_DATA(E_MATCH_FLAG, 1);
__COMPILER_TAG_DATA(Regex, 0);
__COMPILER_TAG_DATA(regex, 0);
__COMPILER_TAG_DATA(RegexMatch, 0);
__COMPILER_TAG_DATA(match_results, 0);

// Pawn.Raknet tags.
__COMPILER_TAG_DATA(PR_HandlerType, 0);
__COMPILER_TAG_DATA(PR_ValueType, 0);
__COMPILER_TAG_DATA(PR_PacketPriority, 0);
__COMPILER_TAG_DATA(PR_PacketReliability, 6);
__COMPILER_TAG_DATA(BitStream, 0);

// amx_assembly tags.
__COMPILER_TAG_DATA(Opcode, 0);
__COMPILER_TAG_DATA(AsmError, 0);
__COMPILER_TAG_DATA(DisasmResult, 0);

// md-sort tags.
__COMPILER_TAG_DATA(E_SORT_ORDER, 0);

// Requests tags.
__COMPILER_TAG_DATA(Request, -1);
__COMPILER_TAG_DATA(RequestsClient, -1);
__COMPILER_TAG_DATA(E_HTTP_METHOD, 0);
__COMPILER_TAG_DATA(E_HTTP_STATUS, 0);
__COMPILER_TAG_DATA(JSON_NODE, 0);
__COMPILER_TAG_DATA(Headers, -1);
__COMPILER_TAG_DATA(Node, -1);

