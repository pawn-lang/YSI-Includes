/*+
 * <library name="y_shortvar">
 * <section>
 *  Description
 * </section>
 *  Declares a few variables with very short names, used all over YSI.
 * <section>
 *  Version
 * </section>
 *  0.2
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

// VERY VERY VERY IMPORTANT!!! y_text uses "144" explicitly.  Change it too.
#define YSI_MAX_STRING (144)
#if YSI_MAX_STRING != 144
	#error Please update all explicit YSI_MAX_STRING uses.
#endif

#if !defined YSIM_STRING
	#define YSIM_STRING (1000)
#endif

// Public variable.  `-1` initially in case there is no master system.  So we respond to everything.
#define Master_ID() (@_)
public
	@_ = -1;

new
	Q@[YSI_MAX_STRING];

// J@ is a "nul" target - send things there if they need ignoring or if a
// parameter needs using.  I@ is too now.
stock
	I@ = 0,
	J@ = 0;

#if !defined MAX_LANGUAGES
	#define MAX_LANGUAGES (4)
#endif

stock
	YSI_gUnsafeHugeString[MAX_LANGUAGES][2048];

#define YSI_UNSAFE_HUGE_STRING (YSI_gUnsafeHugeString[0])
#define YSI_UNSAFE_HUGE_LENGTH (MAX_LANGUAGES * sizeof (YSI_gUnsafeHugeString[]))

// Used by y_master and y_remote.  Re-evaluate after rewrites.
native U@(id = 0, const name[] = "", value = cellmin, const string[] = "") = setproperty;
native V@(GLOBAL_TAG_TYPES:id = 0, const name[] = "", value = cellmin, string[] = "") = getproperty;

#if defined OPENMP
	native R@(const function[], const format[], GLOBAL_TAG_TYPES:...) = Script_Call;
	native W@(const function[], const format[], GLOBAL_TAG_TYPES:...) = Script_CallAll;
	native O@(const function[], time, repeat, const format[] = "", GLOBAL_TAG_TYPES:...) = SetTimerEx;
#else
	// Define this command with basically every strong tag in existence to avoid
	// tag mismatch warnings with remote functions with strong tag parameters.
	native R@(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallLocalFunction;
	native W@(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallRemoteFunction;
	native O@(const function[], time, repeat, const format[] = "", GLOBAL_TAG_TYPES:...) = SetTimerEx;
#endif

#if !__COMPILER_MODIFIED
	forward _@_y_shortvar_@_();

	public _@_y_shortvar_@_()
	{
		new tmp[2];
		// This function calls any functions used in assembly code in YSI to ensure
		// that they are included in the native function table.
		R@(tmp, tmp);
		W@(tmp, tmp);
		O@(tmp, 0, false);
	}
#endif

#define __ARGS__SCM 0,0,""

#if !defined TRUE
stock const
	bool:TRUE = true;
#endif

#if !defined FALSE
stock const
	bool:FALSE = false;
#endif

#if !defined NULL
stock const
	NULL[2] = "\1";
#endif

/**
	This variable only exists to hide other variables.  It starts a massive
	comment block in the pawndoc XML output that hides all YSI internal
	variables - that is, those that start with <c>YSI_g<c>.

	<!--
*/

static stock YSI_g;

/**
	This variable only exists to hide other variables.  It ends a massive
	comment block in the pawndoc XML output that hides all YSI internal
	variables - that is, those that start with <c>YSI_g<c>.

	-->
*/

static stock YSI_gzzzzzzzzzzzzzzzzzzzzzzzzzz;

#if defined FIXES_PAWNDOC
	// The fixes.inc pawndoc cleverness is already defined, we don't need to
	// duplicate it here.  We have to use `#endinput` to avoid the comments
	// appearing in the output anyway.
	#endinput
#endif

/**
	This function only exists to hide other functions.  It starts a massive
	comment block in the pawndoc XML output that hides all internal functions -
	that is, those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal functions appear in the generated documentation always.  This is
	the best way to hide them.  You still see one function (this one), but at
	least the documentation for this one function can explain why it exists.

	This is <c>ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ</c> and starts the internal
	functions block.  This is the first possible name alphabetically before the
	first character is <c>_</c>.

	<!--
*/

static stock ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ() {}

/**
	This function only exists to hide other functions.  It end a massive comment
	block in the pawndoc XML output that hides all internal functions - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal functions appear in the generated documentation always.  This is
	the best way to hide them.  You still see one function
	(<c>ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ</c>), but at least the documentation for
	that can explain why it exists.

	This is <c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c> and ends the internal
	functions block.  This is the last possible name alphabetically before the
	first character is no longer <c>_</c>.  There's also a
	<c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c> that ends the variables block.  They
	could have the same name if they were not declared in the same scope, but
	they might not always be separately defined.

	-->
*/

static stock _zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz() {}

/**
	The first parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_0</c> prefix.
*/

static stock _0;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_0</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _0zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The second parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_1</c> prefix.
*/

static stock _1;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_1</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _1zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The third parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_2</c> prefix.
*/

static stock _2;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_2</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _2zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The fourth parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_3</c> prefix.
*/

static stock _3;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_3</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _3zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The fifth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_4</c> prefix.
*/

static stock _4;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_4</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _4zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The sixth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_5</c> prefix.
*/

static stock _5;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_5</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _5zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The seventh parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_6</c> prefix.
*/

static stock _6;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_6</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _6zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The eighth parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_7</c> prefix.
*/

static stock _7;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_7</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _7zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The ninth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_8</c> prefix.
*/

static stock _8;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_8</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _8zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The tenth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_9</c> prefix.
*/

static stock _9;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see some internal variables (<c>_0</c>
	- <c>_9</c>), but those have a legitimate reason to be documented
	externally.

	This is <c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c> and ends the internal
	variables block.  This is the last possible name alphabetically before the
	first character is no longer <c>_</c>, except for one.  There's also a
	<c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</c> that ends the functions block.  They
	could have the same name if they were not declared in the same scope, but
	they might not always be separately defined.

	-->
*/

static stock _zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy;

