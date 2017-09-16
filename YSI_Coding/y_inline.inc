#if defined _INC_y_inline
	#endinput
#endif
#define _INC_y_inline

/**
 * <library name="y_inline">
 * <section>
 *  Description
 * </section>
 *  This library allows a user to write inline functions in their script.  It
 *  first detects all inline functions and generates data on them, such as
 *  parameter counts and addresses.  When an inline function is passed in code
 *  its current context data is stored.  Finally, when an inline function is
 *  found to be called at some point its current local stack is stored in global
 *  memory.  When the function actually is called, the stack is restored, and
 *  additional parameters which are the inline function parameters, are passed.
 * <section>
 *  Version
 * </section>
 *  1.0
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

#include "..\YSI_Internal\y_compilerdata"

#if !defined YSI_MAX_INLINE_STRING
	#define YSI_MAX_INLINE_STRING YSI_MAX_STRING
#endif

#include "..\YSI_Internal\y_thirdpartyinclude"
#include "..\YSI_Internal\y_version"
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Data\y_bit"
#include "y_malloc"


#include "y_inline/macros"
#include "..\YSI_Internal\y_cgen"

#include "y_inline/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_hooks"
	#include "y_inline/tests"
#endif

