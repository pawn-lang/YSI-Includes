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

#if !defined _INC_y_compilerdata
	#tryinclude "y_compilerdata\y_compilerdata_entry"
#endif
#if !defined _INC_y_compilerdata
	#tryinclude "YSI_Core\y_compilerdata\y_compilerdata_entry"
#endif
#if !defined _INC_y_compilerdata
	#tryinclude "YSI\YSI_Core\y_compilerdata\y_compilerdata_entry"
#endif
#if !defined _INC_y_compilerdata
	#tryinclude <YSI_Core\y_compilerdata\y_compilerdata_entry>
#endif
#if !defined _INC_y_compilerdata
	#tryinclude <YSI\YSI_Core\y_compilerdata\y_compilerdata_entry>
#endif
#if !defined _INC_y_compilerdata
	#error Could not find y_compilerdata
#endif

