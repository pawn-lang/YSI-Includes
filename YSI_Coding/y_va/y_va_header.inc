#if defined _INC_y_va_header
	#endinput
#endif
#define _INC_y_va_header

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

#if 0

	// Example:
	stock MyPrintf(const format[], {Float, File, _}:...)
	{
		// The triple underscore is used to mirror the triple dots in the
		// function definition.  You can't easily tell it is three from a
		// glance, but it is.
		printf(format, ___1); // Or `___(1)`.
		print("Printed many things");
		return 42;
	}

#endif

#define ___ YVA2_DummyPush()
// For optional parameter skips.
#define YVA2_DummyPush()(%1) YVA2_DummyPush((%1)*cellbytes)

// Shortcuts.
#define ___0 ___(0)
#define ___1 ___(1)
#define ___2 ___(2)
#define ___3 ___(3)
#define ___4 ___(4)
#define ___5 ___(5)
#define ___6 ___(6)
#define ___7 ___(7)
#define ___8 ___(8)
#define ___9 ___(9)

#define va_args<%0> GLOBAL_TAG_TYPES:...
#define va_start<%0> ___(%0)

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

// Detect Slice's va_formatex function, which now doesn't need to exist.  This
// is my first ever use of `#pragma deprecated`!  Actually quite happy about
// that - it's one of the few language features I've never used in earnest, so
// its almost an occassion when that happens.
#pragma deprecated Use formatex instead
forward va_formatex(output[], size = sizeof(output), const fmat[], va_:STATIC_ARGS);

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

// Backwards compatability.
native va_printf            (const format[], GLOBAL_TAG_TYPES:...)                                             = printf;
native va_CallRemoteFunction(const function[], const format[], GLOBAL_TAG_TYPES:...)                           = CallRemoteFunction;
native va_CallLocalFunction (const function[], const format[], GLOBAL_TAG_TYPES:...)                           = CallLocalFunction;
native va_SetTimerEx        (const function[], interval, bool:repeating, const format[], GLOBAL_TAG_TYPES:...) = SetTimerEx;
native va_format            (output[], len, const format[], GLOBAL_TAG_TYPES:...)                              = format;

