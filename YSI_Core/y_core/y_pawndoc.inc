#if defined _INC_y_pawndoc
	#endinput
#endif
#define _INC_y_pawndoc

/**
 * <library
 *   name="y_pawndoc"
 *   version="0.2"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Fix pawndoc comments."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   </library>
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

#define Debug_PrintD _FIXES_FUNC_PAWNDOC

#if defined FIXES_PAWNDOC
	// The fixes.inc pawndoc cleverness is already defined, we don't need to
	// duplicate it here, just clear some spaces in the XML hidden output to
	// show some YSI functions.
	#include "y_pawndoc_with_fixes"
#else
	// The fixes.inc pawndoc cleverness is not already defined, we don't need to
	// modify it here.  Instead, this file just copies the whole thing
	// wholesale (I wrote it, I give myself permission to copy it).
	#include "y_pawndoc_without_fixes"
#endif

// YSI internal versions of the pawndoc macros.
#define YSI_FUNC_PAWNDOC _FIXES_FUNC_PAWNDOC
#define YSI_FUNCTION_PAWNDOC _FIXES_FUNC_PAWNDOC
#define YSI_CONST_PAWNDOC _FIXES_CONST_PAWNDOC
#define YSI_ENUM_PAWNDOC _FIXES_ENUM_PAWNDOC
#define YSI_CLOSE_PAWNDOC _FIXES_CLOSE_PAWNDOC
#define YSI_HIDE_PAWNDOC _FIXES_HIDE_PAWNDOC

#define FUNC_PAWNDOC _FIXES_FUNC_PAWNDOC
#define FUNCTION_PAWNDOC _FIXES_FUNC_PAWNDOC
#define CONST_PAWNDOC _FIXES_CONST_PAWNDOC
#define ENUM_PAWNDOC _FIXES_ENUM_PAWNDOC
#define CLOSE_PAWNDOC _FIXES_CLOSE_PAWNDOC
#define HIDE_PAWNDOC _FIXES_HIDE_PAWNDOC

/**
	<summary>
		The first parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_0</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _0;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.  You
		still see one variable (<c>_0</c>), but that one has a legitimate use
		that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _0zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The second parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_1</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _1;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_1</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _1zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The third parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_2</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _2;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_2</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _2zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The fourth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_3</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _3;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_3</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _3zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The fifth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_4</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _4;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_4</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _4zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The sixth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_5</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _5;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_5</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _5zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The seventh parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_6</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _6;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_6</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _6zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The eighth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_7</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _7;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_7</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _7zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The ninth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_8</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _8;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It end a massive
		comment block in the pawndoc XML output that hides all internal
		variables - that is, those that start with <c>_</c>.  This is a very
		common pattern used throughout YSI (and most of programming).
		Unfortunately these weirdly named internal variables appear in the
		generated documentation always.  This is the best way to hide them.
		You still see one variable (<c>_8</c>), but that one has a legitimate
		use that can be documented and is fine to be seen.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	-->
*/

static stock _8zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	<summary>
		The tenth parameter in a <emph>y_functional</emph> lambda function.
		This is implicitly declared.
	</summary>

	<!--

	<remarks>
		Hide future declarations with <c>_9</c> prefix.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>
*/

static stock _9;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It starts a massive
		comment block in the pawndoc XML output that hides all YSI internal
		variables - that is, those that start with <c>YSI_g</c>.
		<p/>
		Note that the actual hiding itself is done by an XML comment started
		earlier and ended here.
	</remarks>

	<!--
*/

static stock YSI_g;

/**
	<hidden />
	<remarks>
		This variable only exists to hide other variables.  It ends a massive
		comment block in the pawndoc XML output that hides all YSI internal
		variables - that is, those that start with <c>YSI_g</c>.
	</remarks>

	-->
*/

static stock YSI_gzzzzzzzzzzzzzzzzzzzzzzzzzz;

