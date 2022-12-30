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

#define __pragma("%0"%1) __pragma_%0(%1)

// The only two `__pragma`s we can fake.
#define __pragma_naked(); {return 0;} //__COMPILER_DEFAULT
#define __pragma_unused(,%0) H@(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("option", "-l");</c>
 * </remarks>
 */
forward __pragma_option(const string:option[]);
#define __pragma_option(,%0) __pragma_option(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("align");</c>
 * </remarks>
 */
forward __pragma_align();
#define __pragma_align(,%0) __pragma_align(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("amxlimit", 8192);</c>
 * </remarks>
 */
forward __pragma_amxlimit(limit);
#define __pragma_amxlimit(,%0) __pragma_amxlimit(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("amxram", 4096);</c>
 * </remarks>
 */
forward __pragma_amxram(ram);
#define __pragma_amxram(,%0) __pragma_amxram(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("codepage", 5001);</c>
 * </remarks>
 */
forward __pragma_codepage(const string:codepage[]);
#define __pragma_codepage(,%0) __pragma_codepage(#%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("compress", true);</c>
 * </remarks>
 */
forward __pragma_compress(bool:compress);
#define __pragma_compress(,%0) __pragma_compress(!!%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("ctrlchar", '\\');</c>
 * </remarks>
 */
forward __pragma_ctrlchar(character);
#define __pragma_ctrlchar(,%0) __pragma_ctrlchar(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("deprecated", var);</c>  Gives the best warning I can manage
 *   without compiler support; call a function called <c>__deprecated</c> and
 *   pass in the variable.
 * </remarks>
 */
#define __pragma_deprecated(,%0); {new deprecated_%0=__deprecated(#%0);}

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated The parameter is deprecated.
stock __deprecated(const symbol[])
{
	return 0;
}
#define deprecated_%0\32;%1= deprecated_%1=

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("dynamic", 2048);</c>
 * </remarks>
 */
forward __pragma_dynamic(ram);
#define __pragma_dynamic(,%0) __pragma_dynamic(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("library", "sscanf");</c>
 * </remarks>
 */
forward __pragma_library(const string:library[]);
#define __pragma_library(,%0) __pragma_library(#%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("overlay", 1024);</c>
 * </remarks>
 */
forward __pragma_overlay(size);
#define __pragma_overlay(,%0) __pragma_overlay(%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("pack", true);</c>
 * </remarks>
 */
forward __pragma_pack(bool:pack);
#define __pragma_pack(,%0) __pragma_pack(!!%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("rational", tagof (Float:));</c>
 * </remarks>
 */
forward __pragma_rational(const string:tagname[], bits = -1);
#define __pragma_rational(,%0) __pragma_rational(_:__pragma_rational_:#%0)
#define __pragma_rational_:#%0(%1)) #%0,%1)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("semicolon", true);</c>
 * </remarks>
 */
forward __pragma_semicolon(bool:use);
#define __pragma_semicolon(,%0) __pragma_semicolon(!!%0)

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("tabsize", 4);</c>
 * </remarks>
 */
forward __pragma_tabsize(tabsize);
#define __pragma_tabsize(,%0) __pragma_tabsize(4)

/// <p/>

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The various sub-types of <c>__pragma("warning")</c> - <c>push</c>,
 *   <c>pop</c>, <c>disable</c>, and <c>enable</c>.
 * </remarks>
 */

enum __PRAGMA_WARNING
{
	__PRAGMA_WARNING_enable,
	__PRAGMA_WARNING_disable,
	__PRAGMA_WARNING_push,
	__PRAGMA_WARNING_pop,
}

static stock __PRAGMA_WARNING:_@__PRAGMA_WARNING() { return __PRAGMA_WARNING; }

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("warning", disable, 200);</c>
 * </remarks>
 */
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

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   <c>__pragma("compat", true);</c>
 * </remarks>
 */
forward __pragma_compat(bool:compatibility);
#define __pragma_compat(,%0) __pragma_compat(!!%0)

