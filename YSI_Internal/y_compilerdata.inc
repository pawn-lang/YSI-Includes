#if defined _INC_y_compilerdata
	#endinput
#endif
#define _INC_y_compilerdata

/**
<!--
<transition target[^/]+/>

:::::::: README ::::::::

To read the generated XML output, copy `pawndoc.xsl` to `pawno/xml/`.

This information goes very close to the top of the generated XML documentation
(because of include dependency orders), but doesn't appear in the visual output.

There is a bug in the compiler related to outputting documentation on state
transitions (<a href="https://github.com/Zeex/pawn/issues/184" />).  So after
generation of the XML file, you should clean it up with the following RegEx
replacement:

Search: <transition target[^/]+/>
Replace: (nothing)

This works 99% of the time, though you may get one where the corrupted target
includes the character `/`, in which case you should manually delete them.  Note
that YSI now includes manual documentation for transitions, but these all
include the parameter `keep="true"`, which exists simply to not match that
RegEx.  I also put the search at the top of this block so it is easier to find
in the output code.
-->
*//*+
 * <library name="y_compilerdata">
 * <section>
 *  Description
 * </section>
 *  Detect various information about the compiler, including which pass it is
 *  currently executing, what flags it was compiled with, and which version it
 *  is.  Provide that information to the rest of the script through a series of
 *  consistent macros.  Used by y_groups to include code that might be needed
 *  before it is known if it is needed (it can be dumped later).
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="__CompilerStringReturn">
 *      Assembly for returning a string to its callers' caller.  Used to
 *      bypass a known bug.</symbol>
 *  <symbol name="__CompilerSecondPass">Tested to determine the current compiler pass.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="__COMPILER_STRING_RETURN">Correctly return a string from a varargs function.</symbol>
 * </ul><section>
 *  Macros
 * </section><ul>
 *  <symbol name="__COMPILER_PASS">Which pass the compiler is currently running.</li><to_ul></symbol>
 *  <symbol name="__COMPILER_DOCUMENTING">Is the compiler collecting documentation
 *      information right now (i.e. is this the first pass)?</symbol>
 *  <symbol name="__COMPILER_1ST_PASS">Is this the first compiler pass?</symbol>
 *  <symbol name="__COMPILER_2ND_PASS">Is this the second compiler pass?</symbol>
 *  <symbol name="__COMPILER_FIRST_PASS">Is this the first compiler pass?</symbol>
 *  <symbol name="__COMPILER_SECOND_PASS">Is this the second compiler pass?</symbol>
 *  <symbol name="__COMPILER_MODIFIED">Is the compiler an updated/unofficial/modified one?</symbol>
 *  <symbol name="__COMPILER_OFFICIAL">Is the compiler an official one?</symbol>
 *  <symbol name="__COMPILER_COMPAT">Was the compiler built with `-Z`?</symbol>
 *  <symbol name="__COMPILER_INCLUDE_GUARDS">Does the compiler generate auto-include guards?</symbol>
 *  <symbol name="__COMPILER_NESTED_ELLIPSIS">Does the compiler support nested ellipses?</symbol>
 *  <symbol name="__COMPILER_BUGGED_STRING_RETURN">
 *      Are vararg function string returns bugged?  Not needed for using
 *      <symbolref name="__COMPILER_STRING_RETURN" />, as that will do the best
 *      thing in both cases already.</symbol>
 *  <symbol name="P:D">Wrap a fake function declaration, so macros can be documented.</symbol>
 * </ul>
 * </library>
 *//** *//*
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

#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
	#define __COMPILER_MODIFIED (1)
	#define __COMPILER_OFFICIAL (0)
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

#if __COMPILER_1ST_PASS && __COMPILER_MODIFIED
	// Disable matching the resulting function against (most) macros that are
	// defined with the same name (since the whole point of this is to provide a
	// concrete implementation for documentation to see).
	#define Debug_PrintD(%1(%2)); %1 Debug_PrintD_OPEN %2 Debug_PrintD_CLOSE { return 0; }
#else
	#define Debug_PrintD(%1);
#endif
#define Debug_PrintD_OPEN (
#define Debug_PrintD_CLOSE )

#if __COMPILER_MODIFIED
	#define __COMPILER_NESTED_ELLIPSIS (1)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) return __compiler_one_string_parameter:(%0)
	#define __COMPILER_BUGGED_STRING_RETURN (0)
	// Disable the recursion warning in the Russian compiler (and the unknown
	// pragma warning in other compilers temporarily).
	#pragma warning push
	#pragma warning disable 207
	#pragma disablerecursion
	#pragma warning pop
#else
	#define __COMPILER_NESTED_ELLIPSIS (0)
	#define __compiler_one_string_parameter:%8(%0,%1) (%0)
	#define __COMPILER_STRING_RETURN(%0) __CompilerStringReturn(%0);return (__compiler_one_string_parameter:(%0))
	#define __CompilerStringReturn("%0"%1);return%8(%8:(%3)) return $
	#define __COMPILER_BUGGED_STRING_RETURN (1)
	
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

