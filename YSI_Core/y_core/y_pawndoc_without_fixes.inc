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

// So others know the pawndoc macros exist.
#define FIXES_PAWNDOC

// Strip tags from states.
#define __PAWNDOC:%0:%1> __PAWNDOC:%1>

// Defer macro expansion.
#define PP_BRACKETS<> ()

/**
 * <remarks>
 * Creates fake functions that Pawndoc comments can be attached to in the first
 * compilation phase, before the real macros are created.  Macros can't have
 * documentation comments, but why not?  They need documenting...
 * <p/>
 * Used internally as <c>YSI_FUNC_PAWNDOC</c>.
 * <p/>
 * This creates a native of the same name, then calls it from a special function
 * (called <c>PAWNDOC</c>) with a state set to the name of this function, to
 * avoid declaring multiple functions in the XML while ensuring that this fake
 * function is in the XML.  Natives aren't in the output unless they are called,
 * but we don't have to call them correctly because the container function is
 * never called.  You do need a fallback version of `PAWNDOC` to catch all other
 * state variations declared elsewhere in your script.
 * <p/>
 * <code>
 *     #if defined MACRO_NAME                                                   <br /><indent />
 *         // `#define MACRO_NAME` exists previously, don't document it here.   <br /><indent />
 *         _FIXES_HIDE_PAWNDOC(SIMILAR_NAME);                                   <br />
 *     #else                                                                    <br /><indent />
 *         // Doesn't exist.  Document it and define it.                        <br /><indent />
 *         _FIXES_FUNC_PAWNDOC(MACRO_NAME(parameters));                         <br /><indent />
 *         #define MACRO_NAME(%0) (%0)                                          <br />
 *     #endif
 * </code>
 * <br />
 * </remarks>
 */

#if __COMPILER_1ST_PASS
	// First compiler pass only.
	#define _FIXES_FUNC_PAWNDOC(%0(%1)); native %0(%1) = __PAWNDOC; stock PAWNDOC PP_BRACKETS<> <__PAWNDOC:%0> { (%0()); }
#else
	#define _FIXES_FUNC_PAWNDOC(%0(%1));
#endif

_FIXES_FUNC_PAWNDOC(FUNC_PAWNDOC(const symbol[]));

/**
 * <remarks>
 * Creates fake constants that Pawndoc comments can be attached to in the first
 * compilation phase, before the real macros are created.  Macros can't have
 * documentation comments, but why not?  They need documenting...
 * <p/>
 * Used internally as <c>YSI_CONST_PAWNDOC</c>.
 * <p/>
 * This creates a static stock of the same name to attach the documentation to,
 * before actually defining the macro.
 * <p/>
 * <code>
 *     #if defined MACRO_NAME                                                   <br /><indent />
 *         // `#define MACRO_NAME` exists previously, don't document it here.   <br /><indent />
 *         _FIXES_HIDE_PAWNDOC(SIMILAR_NAME);                                   <br />
 *     #else                                                                    <br /><indent />
 *         // Doesn't exist.  Document it and define it.                        <br /><indent />
 *         _FIXES_CONST_PAWNDOC(MACRO_NAME);                                    <br /><indent />
 *         #define MACRO_NAME(%0) (%0)                                          <br />
 *     #endif
 * </code>
 * <br />
 * </remarks>
 */

#if __COMPILER_1ST_PASS
	// First compiler pass only.
	#define _FIXES_CONST_PAWNDOC(%0=%1); static stock %0 = %1;
#else
	#define _FIXES_CONST_PAWNDOC(%0);
#endif

_FIXES_FUNC_PAWNDOC(CONST_PAWNDOC(const symbol[] = 0));

/**
 * <remarks>
 * Create a <c>const</c> that is never used, which has pawndoc documentation
 * attached to it.  This seems to be the best way to prevent the documentation
 * from appearing in XML (<c>-r</c>) output - even conditional compilation
 * doesn't work on comments.  Used internally as <c>YSI_HIDE_PAWNDOC</c>.
 * <p/>
 * The input should have some unique name, so when using it within an ifdef
 * block, don't use the same name as the tested symbol, because the the
 * replacement in question will be applied to the hidden variable as well.
 * <p/>
 * This should also be a globally unique symbol name, because this only works
 * with `<c>const</c>`, not `<c>static const</c>`.
 * </remarks>
 */

#define _FIXES_HIDE_PAWNDOC(%0); const %0 = 0;

_FIXES_FUNC_PAWNDOC(HIDE_PAWNDOC(const symbol[]));

/**
 * <remarks>
 * There's a bug with the pawndoc for enums.  They loose the documentation, or
 * get some other documentation unless they're immediately followed by another
 * declaration, most notably a function.  This uses the same
 * <c>PAWNDOC&lt;&gt;</c> trick as <c>FUNC_PAWNDOC</c> to use the <c>enum</c>
 * name as a symbol, this time passing it to a function that should always
 * exist.  This ensures the docs are attached to the correct symbol and the
 * additional function is well documented.
 * </remarks>
 */

#define _FIXES_ENUM_PAWNDOC(%0); stock PAWNDOC PP_BRACKETS<> <__PAWNDOC:%0> { random(_:%0); }

_FIXES_FUNC_PAWNDOC(ENUM_PAWNDOC(const symbol[]));

/**
 * <remarks>
 * Use this after all other pawndoc fixes to finish off the <c>PAWNDOC</c>
 * function in the current file.
 * </remarks>
 */

#if __COMPILER_1ST_PASS
	// First compiler pass only.
	stock PAWNDOC() <__PAWNDOC:PAWNDOC>
	{
	}

	stock PAWNDOC() <>
	{
	}
#endif

// Some compile-time safety.
#define PAWNDOC() Dont_Call_PAWNDOC()

/**
	<hidden />
	<remarks>
		This function only exists to hide other functions.  It starts a massive
		comment block in the pawndoc XML output that hides all internal
		functions - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal functions appear in the
		generated documentation always.  This is the best way to hide them.  You
		still see one function (this one), but at least the documentation for
		this one function can explain why it exists.
		<p/>
		This is <c>Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c> and starts the internal
		functions block.  This is the last possible name before the first
		character is <c>_</c> when the functions are sorted lexicographically
		(alphabetically).  There's also <c>Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c>
		that starts the variables block; they could have the same name if they
		were not declared in the same scope, but they might not always be
		separately defined.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		here and ended later.
	</remarks>

	<!--
*/

static stock Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz() {}

/**
	<hidden />
	<remarks>
		This function only exists to hide other functions.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		functions - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal functions appear in the
		generated documentation always.  This is the best way to hide them.  You
		still see one function (<c>Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c>), but at
		least the documentation for that can explain why it exists.
		<p/>
		This is <c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c> and ends the internal
		functions block.  This is the last possible name before the first
		character is no longer <c>_</c> when the functions are sorted
		lexicographically (alphabetically).  There's also
		<c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c> that ends the variables block;
		they could have the same name if they were not declared in the same
		scope, but they might not always be separately defined.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz() {}

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.  You
		still see some internal variables (<c>_0</c> - <c>_9</c>), but those
		have a legitimate reason to be documented externally.
		<p/>
		This is <c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c> and ends the internal
		variables block.  This is the last possible name before the first
		character is no longer <c>_</c>, except for one, when the functions are
		sorted lexicographically (alphabetically).  There's also
		<c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c> that ends the functions block;
		they could have the same name if they were not declared in the same
		scope, but they might not always be separately defined.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy;

