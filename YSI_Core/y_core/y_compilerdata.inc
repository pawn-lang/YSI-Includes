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

// The macros `P:C` and `P:#` don't work without this.
#pragma semicolon 1

// Die tabsize 0!
#pragma tabsize 4
#define tabsize%00%0\10;%0 _DUMMY_do_not_use_tabsize_0

// Enable `P:D(func())` for forcing function-like macros in to documentation.
// For example:
//   
//  /**  
//   * <param name="playerid">An example named macro parameter (`%0`).</param>
//   * <remarks>
//   *  This is a function-like macro.  By default, compiling with `-r` does
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

#if defined __CompilerSecondPass
	#define __COMPILER_PASS (1)
	#define __COMPILER_DOCUMENTING (0)
#else
	#define __COMPILER_PASS (0)
	#define __COMPILER_DOCUMENTING (1)
#endif

#define __COMPILER_1ST_PASS (__COMPILER_PASS == (0))
#define __COMPILER_2ND_PASS (__COMPILER_PASS == (1))
#define __COMPILER_FIRST_PASS  __COMPILER_1ST_PASS
#define __COMPILER_SECOND_PASS __COMPILER_2ND_PASS

// This will define a symbol - `__COMPILER_OS` equal to either `__COMPILER_UNIX`
// or `__COMPILER_WINDOWS` depending on where the code is being built.
#define __COMPILER_UNIX (0)
#define __COMPILER_WINDOWS (1)
#define __COMPILER_OS __COMPILER_UNIX
#tryinclude "Y_dEtErMiNe_Os"

/*-------------------------------------------------------------------------*//*+
 * <remarks>
 *  Exists purely to be detected before it is used.  If that check succeedes,
 *  the compiler is on its second pass and already has a list of all functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/
static stock __CompilerSecondPass() {}

#if __Pawn >= 0x0400
	#error YSI does not yet support PAWN 4.0
#elseif __Pawn < 0x0300
	#error YSI does not yet support PAWN 2.0/1.0
#endif

#define __COMPILER_BUG_317 (1)
#define __COMPILER_NAMEOF (0)
#define __COMPILER_PRAGMA (0)

#define __COMPILER_STATIC_ENUM enum

#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
	#define __COMPILER_MODIFIED (1)
	#define __COMPILER_OFFICIAL (0)
	#if defined __PawnBuild
		#if __PawnBuild >= 2
			#undef __COMPILER_STATIC_ENUM
			#define __COMPILER_STATIC_ENUM static enum
		#endif
		#if __PawnBuild >= 4
			#pragma option -(+
		#endif
		#if __PawnBuild >= 8
			#undef __COMPILER_BUG_317
			#define __COMPILER_BUG_317 (0)
		#endif
		#if __PawnBuild >= 11
			#undef __COMPILER_NAMEOF
			#define __COMPILER_NAMEOF (1)
		#endif
		#if 0
			#undef __COMPILER_PRAGMA
			#define __COMPILER_PRAGMA (1)
		#endif
	#endif
#else
	#define __COMPILER_MODIFIED (0)
	#define __COMPILER_OFFICIAL (1)
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

#if __COMPILER_1ST_PASS
	// Disable matching the resulting function against (most) macros that are
	// defined with the same name (since the whole point of this is to provide a
	// concrete implementation for documentation to see).
	#define Debug_PrintD(%1(%2)); __MACRO__%1 Debug_PrintD_OPEN %2 Debug_PrintD_CLOSE { return 0; }
#else
	#define Debug_PrintD(%1);
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

const __CompilerDefault:__COMPILER_DEFAULT = __CompilerDefault:0;

#if !__COMPILER_PRAGMA
	// TODO: Check for a minor version that might have this.  Assume this is
	// like the MSVC `__pragma` - i.e. `__pragma(pack(0))` which would give
	// `__pragma_pack(0)`.  Or `__pragma(naked)` -> `__pragma_naked`.
	#define __pragma(%0) __pragma_%0
	
	// Tell the compiler that a function does return a value, even when it
	// appears it doesn't.
	// 
	//   stock Func()
	//   {
	//       #emit RETN
	//       __pragma(naked);
	//   }
	// 
	#define __pragma_naked return __COMPILER_DEFAULT
	
	// Return a version of `undefined` for any tag.
	// 
	//   new                Float:a = __pragma(default); // 0.0
	//   new             Language:b = __pragma(default); // -1
	//   new PR_PacketReliability:a = __pragma(default); // 6
	// 
	#define __pragma_default __COMPILER_DEFAULT
	
	// Don't warn about unused varaibles.
	// 
	//   __pragma(unused(a, b, c));
	// 
	#define __pragma_unused(%0) H@(%0)
	#define __pragma_unread(%0) H@(%0)
	#define __pragma_unwritten(%0) H@(%0)
#endif

#if YSI_KEYWORD(default)
	// Return a version of `undefined` for any tag.
	// 
	//   new                Float:a = default(); // 0.0
	//   new             Language:b = default(); // -1
	//   new PR_PacketReliability:a = default(); // 6
	#define default() __pragma(default)
#endif
#define DEFAULT__ __pragma(default)

#if __COMPILER_MODIFIED
	#define __COMPILER_NAKED __pragma(naked);
	#define __COMPILER_NESTED_ELLIPSIS (1)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) return __compiler_one_string_parameter:(%0)
	#define __COMPILER_BUGGED_STRING_RETURN (0)
	#define __COMPILER_BUGGED_SYSREQ (0)
	#define __COMPILER_WARNING_SUPPRESSION (1)
	#define __COMPILER_USER_WARNING (1)

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
		#include "y_compilerdata_warning"
		#define __COMPILER_sNAMEMAX (31)
	#endif
	
	#pragma warning pop
	
	// Disable the warning for `const &var`.
	#define __COMPILER_CONST_REF (1)
#else
	#define __COMPILER_NAKED __pragma(naked);
	#define __COMPILER_NESTED_ELLIPSIS (0)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) __CompilerStringReturn(%0);return (__compiler_one_string_parameter:(%0))
	#define __CompilerStringReturn("%0"%1);return%8(%8:(%3)) return $
	#define __COMPILER_BUGGED_STRING_RETURN (1)
	#define __COMPILER_BUGGED_SYSREQ (1)
	#define __COMPILER_WARNING_SUPPRESSION (0)
	#define __COMPILER_USER_WARNING (0)
	#define __COMPILER_CONST_REF (0)
	#define __COMPILER_sNAMEMAX (31)
	#define __COMPILER_CONST_TAGGED (0)
	
	// It is sufficient simply for a variable to exist anywhere with the tag.
	#define __COMPILER_TAG_DATA(%0,%1) static stock const %0:__TAGOF__%0; stock %0:operator=(__CompilerDefault:a) return a, %0:(%1)
	#define __TAGOF__%0\32; __TAGOF__
	
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
		#emit PUSH.C       12     // Push the parameters for `strcpy`.
		#emit SYSREQ.C     strcat // Call `strcat`.
		#emit LOAD.S.pri   0      // Reload the previous frame pointer.
		#emit SCTRL        4      // Wipe out the stack.
		#emit SCTRL        5      // Wipe out the frame (go to parent context).
		#emit RETN                // Return (now within the parent context).
		return 0;
	}
	
#endif

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

// And the other way
#define __cellbytes cellbytes
#define __cellbits cellbits
#define __cell_bytes cellbytes
#define __cell_bits cellbits
#define __pawn __Pawn

// Don't define `__PawnBuild` if it doesn't exist, but do create an alternate
// symbol (with a consistent naming scheme) that always exists.
#if defined __PawnBuild
	#define __pawn_build __PawnBuild
#else
	#define __pawn_build 0
#endif

// Should be an inbuilt constant!
#define cellbytes (cellbits / 8)

#if __COMPILER_sNAMEMAX != 31
	#error YSI assumes `sNAMEMAX` is 31.
#endif

__COMPILER_TAG_DATA(_, 0);
__COMPILER_TAG_DATA(bool, 0);
__COMPILER_TAG_DATA(Float, 0);
__COMPILER_TAG_DATA(File, 0);
__COMPILER_TAG_DATA(DB, 0);
__COMPILER_TAG_DATA(DBResult, 0);
__COMPILER_TAG_DATA(Text, 65535);
__COMPILER_TAG_DATA(PlayerText, 65535);
__COMPILER_TAG_DATA(Menu, 255);
__COMPILER_TAG_DATA(Text3D, 65535);
__COMPILER_TAG_DATA(PlayerText3D, 65535);
__COMPILER_TAG_DATA(filemode, 0);
__COMPILER_TAG_DATA(seek_whence, 0);

__COMPILER_TAG_DATA(Language, -1);
__COMPILER_TAG_DATA(Bit, 0);
__COMPILER_TAG_DATA(Style, 0);
__COMPILER_TAG_DATA(XML, -1);
__COMPILER_TAG_DATA(Bintree, 0);
__COMPILER_TAG_DATA(Group, -1);
__COMPILER_TAG_DATA(Timer, 0);
__COMPILER_TAG_DATA(INI, -1);

__COMPILER_TAG_DATA(ConstString, 0);
__COMPILER_TAG_DATA(String, 0);
__COMPILER_TAG_DATA(error_level, 0);
__COMPILER_TAG_DATA(locale_category, 0);
__COMPILER_TAG_DATA(filter_type, 0);
__COMPILER_TAG_DATA(handler_flags, 0);
__COMPILER_TAG_DATA(Variant, 0);
__COMPILER_TAG_DATA(ConstVariant, 0);
__COMPILER_TAG_DATA(Iter, 0);
__COMPILER_TAG_DATA(Handle, 0);
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
// I'm not doing the generic tags as well...

__COMPILER_TAG_DATA(DynamicObject, 0);
__COMPILER_TAG_DATA(DynamicPickup, 0);
__COMPILER_TAG_DATA(DynamicCP, 0);
__COMPILER_TAG_DATA(DynamicRaceCP, 0);
__COMPILER_TAG_DATA(DynamicMapIcon, 0);
__COMPILER_TAG_DATA(DynamicText3D, 0);
__COMPILER_TAG_DATA(DynamicArea, 0);
__COMPILER_TAG_DATA(DynamicActor, 0);

__COMPILER_TAG_DATA(E_REGEX_GRAMMAR, 0);
__COMPILER_TAG_DATA(E_REGEX_FLAG, 1);
__COMPILER_TAG_DATA(E_MATCH_FLAG, 1);
__COMPILER_TAG_DATA(Regex, 0);
__COMPILER_TAG_DATA(regex, 0);
__COMPILER_TAG_DATA(RegexMatch, 0);
__COMPILER_TAG_DATA(match_results, 0);

__COMPILER_TAG_DATA(PR_HandlerType, 0);
__COMPILER_TAG_DATA(PR_ValueType, 0);
__COMPILER_TAG_DATA(PR_PacketPriority, 0);
__COMPILER_TAG_DATA(PR_PacketReliability, 6);
__COMPILER_TAG_DATA(BitStream, 0);

__COMPILER_TAG_DATA(Opcode, 0);
__COMPILER_TAG_DATA(AsmError, 0);
__COMPILER_TAG_DATA(DisasmResult, 0);

__COMPILER_TAG_DATA(E_SORT_ORDER, 0);

