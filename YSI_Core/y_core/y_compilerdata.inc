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

// Enable `P:D(func())` for forcing function-like macros in to documentation.
// For example:
//   
//  /**  
//   * <param name="playerid">An example named macro parameter (<c>%0</c>).</param>
//   * <remarks>
//   *  This is a function-like macro.  By default, compiling with <c>-r</c> does
//   *  not put macros in the XML, which is a shame if we are using a macro to
//   *  fake a function, because then a function will be apparently missing
//   *  from the documentation.  Instead, we make a function, THEN make the
//   *  macro.  But, importantly, we only make the function on the first pass,
//   *  not the second pass (documentation is apparently generated in the first
//   *  pass).
//   * </remarks>
//   * <example>
//   *
//   *  for (new i = 0; MyFunc(i); ++i)
//   *  {
//   *     printf("%d", i);
//   *  }
//   *
//   * </example>
//   */
//   P:D(bool:MyFunc(playerid));
//   #define MyFunc(%0) ((%0) < MAX_PLAYERS)
//   
#define P:%1(%2); Debug_Print%1(%2);
#define C:%1(%2); Debug_Code%1(%2);

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

/*-------------------------------------------------------------------------*//*+
 * <remarks>
 *  Exist purely to be detected before they are used.  If that check succeedes,
 *  the compiler is on its second or third pass and already has a list of all
 *  functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/
#if __COMPILER_FIRST_PASS
	static stock __CompilerFirstPass() {}
#endif

#if __COMPILER_SECOND_PASS
	static stock __CompilerSecondPass() {}
#endif

#if __COMPILER_THIRD_PASS
	static stock __CompilerThirdPass() {}
#endif

// Determine if strings are packed by default or not.
static stock const __COMPILER_PACKED_TEST[] = " ";

#if sizeof (__COMPILER_PACKED_TEST) == 1
	#define __COMPILER_STRING_PACKING (1)
	#define __COMPILER_PACK
	#define __COMPILER_UKPACK !
#else
	#define __COMPILER_STRING_PACKING (0)
	#define __COMPILER_PACK !
	#define __COMPILER_UKPACK
#endif

#include "y_compilerdata_codepage"

#define __COMPILER_BUG_317 (1)
#define __COMPILER_NAMEOF (0)
#define __COMPILER_PRAGMA (0)
#define __COMPILER___EMIT_U (0)

#define __COMPILER_STATIC_ENUM enum
#define __COMPILER_CONST_STATIC const

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
// `%0:_:` is a trick in since the earlies days of YSI.  There is a macro:
//
//   #define _:%0,) _:%0)
//
// Which will remove trailing commas in function parameter lists, so if `%2` is
// empty this won't cause any problems.
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
#define THIS__(%0)%1(%2) %0_%1(%0:_:(%1),%2)
#define __COMPILER_THIS (0)

#if (__Pawn & 0x0F) >= 0x0A
	#define __COMPILER_MODIFIED (1)
	#define __COMPILER_OFFICIAL (0)

	#define __COMPILER_USER_WARNING (1)

	#if !defined __PawnBuild
		#define __PawnBuild 0
	#endif
	#if __PawnBuild >= 2
		#undef __COMPILER_STATIC_ENUM
		#define __COMPILER_STATIC_ENUM static enum
	#endif
	#if __PawnBuild >= 4
		#undef __COMPILER_OPTION
		#define __COMPILER_OPTION (1)
		#pragma option -(+
	#endif
	#if __PawnBuild >= 8
		#undef __COMPILER_BUG_317
		#define __COMPILER_BUG_317 (0)
	#endif
	#if __PawnBuild >= 10
		#undef __COMPILER___EMIT_U
		#define __COMPILER___EMIT_U (1)
	#endif
	// Disable `__COMPILER_PRAGMA` for now, while there's no `PROC` generated.
	#if __PawnBuild >= 11
		#undef __COMPILER_NAMEOF
		//#undef __COMPILER_PRAGMA
		
		#define __COMPILER_NAMEOF (1)
		//#define __COMPILER_PRAGMA (1)
		#undef __COMPILER_CONST_STATIC
		#define __COMPILER_CONST_STATIC const static
	#endif
#else
	#define __COMPILER_USER_WARNING (0)

	#define __COMPILER_MODIFIED (0)
	#define __COMPILER_OFFICIAL (1)
#endif

const __COMPILER_DETERMINE_SEMICOLON = 1;
#define __COMPILER_DETERMINE_SEMICOLON%0; 0%0

// The macro looks for `;`, which isn't here.  So if it matches, we must have
// bypassed that requirement.
#if __COMPILER_DETERMINE_SEMICOLON == 0
	// `-;-`
	#define __COMPILER_SEMICOLON (0)

	// The macros `P:C` and `P:#` don't work without this.
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

enum __E_COMPILER_ENUM
{
	__E_COMPILER_ENUM_ENTRY[3],
	__E_COMPILER_ENUM_AFTER
}

static stock const
	__YSI_gsCompilerEnum[__E_COMPILER_ENUM];

#if sizeof (__YSI_gsCompilerEnum[__E_COMPILER_ENUM_ENTRY]) == 3
	#define __COMPILER_SIZEOF_ENUM (1)
#else
	#define __COMPILER_SIZEOF_ENUM (0)
#endif

#if !__COMPILER_NAMEOF
	// Allow `__nameof(Float:)` `CoMPiler REMove CoLoN`.
	#define __CMPREMCLN:tagof(%0:),%0:) tagof(%0),%0)
	
	// Check the symbol exists with `tagof`, then return the name as a string.
	#define __nameof(%0) (__CMPREMCLN:tagof(%0),#%0)
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

#if !__COMPILER_PRAGMA
	#define __pragma("%0"%1) __pragma_%0(%1)

	// The only two `__pragma`s we can fake.
	#define __pragma_naked() return 0 //__COMPILER_DEFAULT
	#define __pragma_unused(,%0) H@(%0)

	// Unimplemented errors.
	forward __pragma_option();
	#define __pragma_option(,%0) __pragma_option(%0)

	forward __pragma_align();
	#define __pragma_align(,%0) __pragma_align(%0)

	forward __pragma_amxlimit(limit);
	#define __pragma_amxlimit(,%0) __pragma_amxlimit(%0)

	forward __pragma_amxram(ram);
	#define __pragma_amxram(,%0) __pragma_amxram(%0)

	forward __pragma_codepage(const string:codepage[]);
	#define __pragma_codepage(,%0) __pragma_codepage(#%0)

	forward __pragma_compress(bool:compress);
	#define __pragma_compress(,%0) __pragma_compress(!!%0)

	forward __pragma_ctrlchar(character);
	#define __pragma_ctrlchar(,%0) __pragma_ctrlchar(%0)

	forward __pragma_deprecated(const string:symbol[]);
	#define __pragma_deprecated(,%0) __pragma_deprecated(#%0)

	forward __pragma_dynamic(ram);
	#define __pragma_dynamic(,%0) __pragma_dynamic(%0)

	forward __pragma_library(const string:library[]);
	#define __pragma_library(,%0) __pragma_library(#%0)

	forward __pragma_overlay(size);
	#define __pragma_overlay(,%0) __pragma_overlay(%0)

	forward __pragma_pack(bool:pack);
	#define __pragma_pack(,%0) __pragma_pack(!!%0)

	forward __pragma_rational(const string:tagname[], bits = -1);
	#define __pragma_rational(,%0) __pragma_rational(_:__pragma_rational_:#%0)
	#define __pragma_rational_:#%0(%1)) #%0,%1)

	forward __pragma_semicolon(bool:use);
	#define __pragma_semicolon(,%0) __pragma_semicolon(!!%0)

	forward __pragma_tabsize(tabsize);
	#define __pragma_tabsize(,%0) __pragma_tabsize(4)

	// New compiler pragmas.
	enum __PRAGMA_WARNING
	{
		__PRAGMA_WARNING_enable,
		__PRAGMA_WARNING_disable,
		__PRAGMA_WARNING_push,
		__PRAGMA_WARNING_pop,
	}

	forward __pragma_warning(__PRAGMA_WARNING:type, warning = -1);
	#define __pragma_warning(,%0) __pragma_warning(__PRAGMA_WARNING__%0)
	#define __PRAGMA_WARNING__%0\32; __PRAGMA_WARNING__

	// Ensure that only two of these are followed by arguments.
	#define __PRAGMA_WARNING__disable __PRAGMA_WARNING_disable,
	#define __PRAGMA_WARNING__enable __PRAGMA_WARNING_enable,
	#define __PRAGMA_WARNING__push __PRAGMA_WARNING_push
	#define __PRAGMA_WARNING__pop __PRAGMA_WARNING_pop
	#define __PRAGMA_WARNING_disable,%0, __PRAGMA_WARNING_disable,
	#define __PRAGMA_WARNING_enable,%0, __PRAGMA_WARNING_enable,

	forward __pragma_compat(bool:compatibility);
	#define __pragma_compat(,%0) __pragma_compat(!!%0)
#endif

// Blank function that does nothing except returns.
#define __COMPILER_UNUSED(%0) __pragma("unused", %0)
#define __COMPILER_NAKED() __pragma("naked")

#if __COMPILER_MODIFIED
	#if defined YSI_TESTS
		#pragma option -E-

		#define Y_COMPILERDATA_WARNING 0
		#include "y_compilerdata_warning"
	#endif

	#define __COMPILER_NESTED_ELLIPSIS (1)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) return (__compiler_one_string_parameter:(%0))
	#define __COMPILER_BUGGED_STRING_RETURN (0)
	#define __COMPILER_BUGGED_SYSREQ (0)
	#define __COMPILER_WARNING_SUPPRESSION (1)
	#define __COMPILER___EMIT (1)

	stock YSI_gAMXAddress_;
	
	#if __COMPILER___EMIT_U
		#define AMX_Read(%0) (_:(__emit(load.u.pri %0, stor.pri YSI_gAMXAddress_, lref.pri YSI_gAMXAddress_)))
		#define AMX_Write(%0,%1) __emit(push.u %1, load.u.alt %0, stor.alt YSI_gAMXAddress_, pop.pri, sref.pri YSI_gAMXAddress_)
		#define AMX_Ref(%0) (_:(__emit(addr.u.pri %0)))
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
	#pragma warning disable 238
	
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
		#define Y_COMPILERDATA_WARNING 1
		#include "y_compilerdata_warning"
		#define __COMPILER_sNAMEMAX (31)
	#endif
	
	#pragma warning pop
	
	// Disable the warning for `const &var`.
	#define __COMPILER_CONST_REF (1)
#else
	#define __COMPILER_NESTED_ELLIPSIS (0)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) return (__CompilerStringReturn(%0), __compiler_one_string_parameter:(%0))
	#define __CompilerStringReturn("%0"%1);return%8(%8:(%3)) return $
	#define __COMPILER_BUGGED_STRING_RETURN (1)
	#define __COMPILER_BUGGED_SYSREQ (1)
	#define __COMPILER_WARNING_SUPPRESSION (0)
	#define __COMPILER_CONST_REF (0)
	#define __COMPILER_sNAMEMAX (31)
	#define __COMPILER_CONST_TAGGED (0)
	#define __COMPILER___EMIT (0)

	// It is sufficient simply for a variable to exist anywhere with the tag.
	#define __COMPILER_TAG_DATA(%0,%1) stock const %0:__TAGOF__%0; stock %0:operator=(__CompilerDefault:a) return a, %0:(%1)

	// Fix `tagof (Float:)` and `tagof (Float:x)` on the old compiler, without
	// breaking any default arguments in (I think) any case.  This was very
	// tricky, as adding any tags to `arg = tagof (param)` breaks the compiler's
	// semantics and always returns the same tag.  So we have to detect
	// `tagof (Tag:)` without detecting `tagof (var), Tag:a`, which the old code
	// broke on.  This is normally easy, but we also have to do it without
	// adding any tags before `tagof` in the base case.  So we always match `:`,
	// then revert if there's a bracket between the `tagof` and the `:`.
	#if !defined TAGOF
		#define __TAGOF__%0\32; __TAGOF__
		#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
		#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
		#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__%0)

		stock bool:operator==(_:a, __NO_TAGOF:b)
		{
			return a == _:b;
		}

		stock bool:operator!=(_:a, __NO_TAGOF:b)
		{
			return a != _:b;
		}

		stock _:operator=(__NO_TAGOF:a)
		{
			return _:a;
		}

		stock __NO_TAGOF:operator=(_:a)
		{
			return __NO_TAGOF:a;
		}
	#endif

	#include "y_funcinc"
	
	/*---------------------------------------------------------------------*//*+
	 * <param name="str">String to return.</param>
	 * <param name="size">Size of the string.</param>
	 * <param name="dummy">Ignored parameter for raw string given sizes.</param>
	 * <returns>
	 *  string
	 * </returns>
	 * <remarks>
	 *  The old compiler has a very annoying bug where returning a string from a
	 *  function that takes variable parameters will not work correctly.  This
	 *  is because string returns are done with a secret extra parameter but it
	 *  is not correctly selected when the count is unknown or variable.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	stock __CompilerStringReturn(const str[], size = sizeof (str), dummy = 0)
	{
		#pragma unused dummy
		#emit PUSH.S       size   // Push the first parameter.
		#emit PUSH.S       str    // Push the second parameter.
		#emit LOAD.S.alt   0      // Load the previous frame pointer.
		#emit MOVE.pri            // Copy the pointer.
		#emit ADD.C        8      // Get the pointer to the parameter count.
		#emit LOAD.I              // Load the parameter count.
		#emit ADD.C        12     // Adjust for the function header size.
		#emit ADD                 // Get the pointer to after the parameters.
		#emit LOAD.I              // Load the pointer in the (secret) parameter.
		#emit PUSH.pri            // Push the destination.
		#emit MOVE.alt            // Make a copy of the pointer.
		#emit ZERO.pri            // `pri = 0`.
		#emit STOR.I              // Set the first cell of the target to NULL.
		#emit PUSH.C       12     // Push the parameters for `StrCpy`.
		#emit SYSREQ.C     strcat // Call `strcat`.
		#emit LOAD.S.pri   0      // Reload the previous frame pointer.
		#emit SCTRL        4      // Wipe out the stack.
		#emit SCTRL        5      // Wipe out the frame (go to parent context).
		#emit RETN                // Return (now within the parent context).
		return 0;
	}
#endif

#define __COMPILER_ARRAY_RETURN __COMPILER_STRING_RETURN	

//#if !__COMPILER_CONST_TAGGED
//	// Fix for bugged const assignments.
//	#define _yI@%0\32; _yI@
//	#define const%0:%1[%2]=%3:%4; const _yI@%1[%2]=%4,%0:%1[sizeof(_yI@%1)];PREINIT__ %1()_YSI_ConstCpy(_:(%1),(_yI@%1),0,sizeof(%1)*4,sizeof(%1));
//#endif

// Consistent naming of compiler defined values. 
#define __Line __line
#define __File __file
#define __Date __date
#define __Time __time
#define __Compat __compat
#define __Emit __emit
#define __CellBytes cellbytes
#define __CellBits cellbits
#define __CellBits cellbits
#define __CharBits charbits
#define __CharMax charmax
#define __UCharMax ucharmax

// And the other way
#define __cellbytes cellbytes
#define __cellbits cellbits
#define __cell_bytes cellbytes
#define __cell_bits cellbits
#define __char_bits charbits
#define __char_max charmax
#define __uchar_max ucharmax
#define __pawn __Pawn

// Don't define `__PawnBuild` if it doesn't exist, but do create an alternate
// symbol (with a consistent naming scheme) that always exists.
#if defined __PawnBuild
	#define __pawn_build __PawnBuild
#else
	#define __pawn_build 0
#endif

// Should be an inbuilt constant!
#define cellbytes (cellbits / charbits)

#if cellbits != 32
	#error YSI assumes `cellbits` is 32.
#endif

#if charbits != 8
	#error YSI assumes `charbits` is 8.
#endif

#define __COMPILER_CELL_BYTES cellbytes
#define __COMPILER_CELL_BITS  cellbits
#define __COMPILER_CHAR_BITS  charbits

// How much to adjust a cell count by to get a byte count.
#if cellbits == 8
	#define __COMPILER_CELL_SHIFT (0)
#elseif cellbits == 16
	#define __COMPILER_CELL_SHIFT (1)
#elseif cellbits == 32
	#define __COMPILER_CELL_SHIFT (2)
#elseif cellbits == 64
	#define __COMPILER_CELL_SHIFT (3)
#else
	#error Unknown cellbits size.
#endif

#define FUNCTION_LENGTH (__COMPILER_sNAMEMAX + 1)

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

// SA:MP tags.
__COMPILER_TAG_DATA(DB, 0);
__COMPILER_TAG_DATA(DBResult, 0);
__COMPILER_TAG_DATA(Text, 65535);
__COMPILER_TAG_DATA(PlayerText, 65535);
__COMPILER_TAG_DATA(Menu, 255);
__COMPILER_TAG_DATA(Text3D, 65535);
__COMPILER_TAG_DATA(PlayerText3D, 65535);

// YSI tags.
__COMPILER_TAG_DATA(Language, -1);
__COMPILER_TAG_DATA(Bit, 0);
__COMPILER_TAG_DATA(Style, 0);
__COMPILER_TAG_DATA(XML, -1);
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

