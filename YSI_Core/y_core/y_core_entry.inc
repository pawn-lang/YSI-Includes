/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

// These includes are in quite a strict order, since there's a lot of inter-
// dependencies.  That's why they're all together in here.
#define _INC_y_core

// Define `cellbytes` as a symbol that really should exist already!
#if !defined cellbytes
	#define cellbytes (cellbits / 8)
#endif

// Define "volatile" as nothing.
#if !defined volatile
	#define volatile
#endif

// The most first include, since it determines compiler settings that might be
// used by literally any other include.
#include "y_compilerdata"

#if !defined HTTP
	#tryinclude <a_http>
#endif

// These three includes are just defines.  They declare no code at all, only
// variables.
#include "y_globaltags"
#include "y_pp"
#include "y_prehook"
#include "y_stripnumbers"
#include "y_shortvar"
#include "y_als_impl"

// A few nicely named short strings used for properties.
#define YSIM_MASTER #M
#define YSIM_RETURN #R
#define YSIM_CALLER #C
#define YSIM_TEXT_D #T
#define YSIM_TXTFND #X
#define YSIM_TXTIND #I
#define YSIM_LOG_IN #U
#define YSIM_VARARG #V

// Now all third-party includes, that shouldn't depend on YSI (if they do,
// that's an interesting issue I'll solve if/when it happens).
#include "y_thirdpartyinclude"

// New create the `OnScriptInit` and `OnCodeInit` callbacks, which many YSI
// includes use to start themselves.
#include "y_scriptinit_impl"
#include "y_va_header"

// The ever loved `y_version`.
#include "y_version"

// More common utilities and user-facing functions.
#include "y_debug_impl"
#include "y_amx_impl"
#include "y_shortfunc"
#include "y_utils_impl"
#include "y_va_impl"

// These are conditional, and use most of the preceeding code.
#if defined YSI_TESTS
	#include "..\y_testing"
#endif

#if defined YSI_TESTS
	#include "y_utils_tests"
	#include "y_va_tests"
	#include "y_als_tests"
#endif

