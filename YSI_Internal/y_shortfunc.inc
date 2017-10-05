#if defined _INC_y_shortfunc
	#endinput
#endif
#define _INC_y_shortfunc

/*+
 * <library name="y_shortfunc">
 * <section>
 *  Description
 * </section>
 *  Defines new names for native functions.
 * <section>
 *  Version
 * </section>
 *  0.2
 * <section>
 *  Natives
 * </section><ul>
 *  <symbol name="W@">Renaming of <symbolref name="__CallRemoteFunction" /> for size reasons.</symbol>
 *  <symbol name="V@">Renaming of <symbolref name="getproperty" /> for size reasons.</symbol>
 *  <symbol name="S@">Renaming of <symbolref name="setproperty" /> for size reasons.</symbol>
 *  <symbol name="P@">Renaming of <symbolref name="__CallLocalFunction" /> for size reasons.</symbol>
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

// Used to get rid of the "string:" tag once it has been used.
#if !defined string
	#define string:
#endif

#if !defined void
	#define void:
#endif

#include "..\YSI_Core\y_utils"
#include "y_globaltags"
#include "y_shortvar"
#include "..\YSI_Core\y_debug"

#include "y_renative"

// N@ taken by y_uvar.
// M@ taken by y_svar.
// L@ taken by y_testing.

native _YSI_RE_NATIVE<U@|||id=0, const name[]="", value=cellmin, const string[]=""|||setproperty>

native _YSI_RE_NATIVE<V@|||GLOBAL_TAG_TYPES:id=0, const name[]="", value=cellmin, string[]=""|||getproperty>

#if defined _YSI_MINI_MODE
	#undef CallRemoteFunction
	#undef CallLocalFunction
#endif

#if defined _ALS_CallRemoteFunction
	#if defined BAD_CallRemoteFunction
		#undef CallRemoteFunction
	#else
		#error Unknown redefinition of CallRemoteFunction.
	#endif
#endif

// Define this command with basically every strong tag in existence to avoid
// tag mismatch warnings with remote functions with strong tag parameters.
native _YSI_RE_NATIVE<W@|||const function[], const format[], GLOBAL_TAG_TYPES:...|||CallRemoteFunction>

native _YSI_RE_NATIVE<P@|||const function[], const format[], GLOBAL_TAG_TYPES:...|||CallLocalFunction>

#if defined _ALS_CallRemoteFunction
	#if defined BAD_CallRemoteFunction
		#define CallRemoteFunction( FIXES_CallRemoteFunction(
	#endif
#endif

#if defined _YSI_MINI_MODE
	#if defined _ALS_CallRemoteFunction
		#undef CallRemoteFunction
	#else
		#define _ALS_CallRemoteFunction
	#endif
	
	#define CallRemoteFunction _MMD(CallRemoteFunction)
	
	#if defined _ALS_CallLocalFunction
		#undef CallLocalFunction
	#else
		#define _ALS_CallLocalFunction
	#endif
	
	#define CallLocalFunction  _MMD(CallLocalFunction)
#endif

#if defined _ALS_SetTimerEx
	#if defined CST_SetTimerEx
		#undef SetTimerEx
	#else
		#error Unknown redefinition of SetTimerEx.
	#endif
#endif

native _YSI_RE_NATIVE<O@|||const function[], time, repeat, const format[], GLOBAL_TAG_TYPES:...|||SetTimerEx>

#if defined _ALS_SetTimerEx
	#if defined BAD_SetTimerEx
		#define SetTimerEx( CST_SetTimerEx(
	#endif
#endif

native _YSI_RE_NATIVE<K@|||const function[], time, repeat|||SetTimer>

stock X@(GLOBAL_TAG_TYPES:n)
{
	P:4("X@ called: %i", n);
	setproperty(8, YSIM_RETURN, n);
}

stock Y@()
{
	P:4("Y@ called");
	// Already returns the previous value.
	return setproperty(8, YSIM_CALLER, _@);
}

stock Z@(GLOBAL_TAG_TYPES:v = -1)
{
	P:4("Z@ called");
	return
		setproperty(8, YSIM_CALLER, v),
		getproperty(8, YSIM_RETURN);
}

new Q@[YSI_MAX_STRING];

stock S@(GLOBAL_TAG_TYPES:v = -1)
{
	P:4("S@ called");
	return
		getproperty(8, "", YSIM_STRING, Q@),
		strunpack(Q@, Q@),
		setproperty(8, YSIM_CALLER, v);
	//return Q@;
}

stock R@(buffer[])
{
	P:4("R@ called: \"%s\"", buffer);
	return setproperty(8, "", YSIM_STRING, buffer);
}

stock H@(GLOBAL_TAG_TYPES:...)
{
	// Just a dead-end for spare parameters.
	return 0;
}

#define _UNUSED(%0) H@(_:_H@0:_H@1:%0)
#define _H@0:_H@1:%0&%1) _H@0:_H@1:%0%1)
#define _H@1:%0[%9]%1) _H@1:%0%1)

stock G@(GLOBAL_TAG_TYPES:...)
{
	// Just a dead-end for spare parameters which returns a string.
	return Q@;
}

stock F@()
{
	P:4("F@ called");
	return
		getproperty(8, "", YSIM_STRING, Q@),
		//P:4("2"),
		//P:4("3"),
		strunpack(Q@, Q@);
	
	//return Q@;
}

// Consume trailing spaces.  Despite being a common letter, this is unlkely to
// ever be matched due to the unusual series of operators after it.  If anyone
// else tries to define "x" however they may have a slight problem (they can't).
//#define x,), x),
// Changed as x,): was also needed (for ?:).
#define x:##),) #))
//#define x,) )
#define q:##),ALS_RS_none:) #))

// This is for getting excess parameters on non-strings.  Now safely recursive.
#define _:%0,) _:%0)

#if defined YSI_LOCK_MODE
	#include "..\YSI_Internal\y_unique"
	
	forward UNIQUE_FUNCTION<@yH_OnScriptInit@...>();
	
	public UNIQUE_FUNCTION<@yH_OnScriptInit@...>()
	{
		new
			find = strfind(YSI_gLockData[5], YSI_gLockData[1]) + 6;
		find = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		new
			found = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		if (strval(YSI_gLockData[found]) ^ UNIQUE_SYMBOL != _LOCK_IP_3 ^ UNIQUE_SYMBOL || strval(YSI_gLockData[find]) - _LOCK_IP_3 != _LOCK_IP_2 - _LOCK_IP_3)
		{
			y_lock 1;
		}
	}
#endif

