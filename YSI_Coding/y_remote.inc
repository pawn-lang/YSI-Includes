#if defined _INC_y_remote
	#endinput
#endif
#define _INC_y_remote

/**
 * <library name="y_remote">
 * <section>
 *  Description
 * </section>
 *  Wrapper for "__CallRemoteFunction".  Enforces some features like no returns
 *  and arrays being followed by their length.
 * <section>
 *  Version
 * </section>
 *  1.0
 * <section>
 *  Macros
 * </section><ul>
 *  <symbol name="remotefunc">Define a function to be called remotely (use like "stock").</symbol>
 *  <symbol name="broadcastfunc">Call the function, but in all scripts.</symbol>
 *  <symbol name="localfunc">Call the function by name, not address, in the current script.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="YSI_NO_MASTER">Disable all knowledge of other scripts.</symbol>
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

#include "..\YSI_Internal\y_version"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Internal\y_thirdpartyinclude"

// This supports "targetfunc<master> func()" and "targetfunc func<master>()".
#include "..\YSI_Core\y_utils"
#include "y_remote/macros"

// This VERY LOOSELY uses the master system to figure out if it should even
// bother with complex remote calls.  However, it isn't fully bound by the
// whole system because it's rules are different (and will work regardless).
#if defined YSI_NO_MASTER
	#define remotefunc stock
	#define localfunc%0(%1) (%0(%1))
	#define broadcastfunc%0(%1) (%0(%1))
	#define targetfunc%3<%2>%0(%1) (%3%0(%1))
#else	
	#define remotefunc Y_REMOTE_FUNC
	#define localfunc%0(%1) (J@=0,I@=-1,_@%0(%1))
	#define broadcastfunc%0(%1) (J@=1,I@=-1,_@%0(%1))
	#define targetfunc%0<%2>%9(%1) (J@=1,I@=(%2),_@%0(%1))
#endif

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_remote/tests"
#endif

