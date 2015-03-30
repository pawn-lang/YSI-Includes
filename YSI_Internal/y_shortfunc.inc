/**--------------------------------------------------------------------------**\
                              ====================
                               YSI - Master Funcs
                              ====================
Description:
	Defines new names for native functions.
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
	
	The Original Code is the YSI master include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.2
Changelog:
	21/10/10:
		Split in to y_shortfunc.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
	Hooks:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
Natives:
	W@ - Renaming of __CallRemoteFunction for size reasons.
	V@ - Renaming of getproperty for size reasons.
	S@ - Renaming of setproperty for size reasons.
	P@ - Renaming of __CallLocalFunction for size reasons.
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_shortfunc
	#endinput
#endif
#define _INC_y_shortfunc

// Used to get rid of the "string:" tag once it has been used.
#if !defined string
	#define string:
#endif

#if !defined void
	#define void:
#endif

#include "..\YSI_Core\y_utils"
#include "y_globaltags"
#include "..\YSI_Core\y_debug"

#include "y_renative"

// Public variable.
public stock
	_@ = 0;

// J@ is a "nul" target - send things there if they need ignoring or if a
// parameter needs using.  I@ is too now.
stock
	I@,
	J@;

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
		#define CallRemoteFunction FIXES_CallRemoteFunction
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

native _YSI_RE_NATIVE<O@|||const function[], time, repeat, const format[], GLOBAL_TAG_TYPES:...|||SetTimerEx>

native _YSI_RE_NATIVE<K@|||const function[], time, repeat|||SetTimer>

stock X@(GLOBAL_TAG_TYPES:n)
{
	P:4("X@ called: %i", n);
	setproperty(8, YSIM_RETURN, n);
}

// stock Y@()
// {
	// P:4("Y@ called");
	// static
	    // ret
	// return
		// ret = getproperty(8, YSIM_CALLER),
		// setproperty(8, YSIM_CALLER, _@),
		// ret;
// }

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
	#include "..\YSI_Coding\y_hooks"
	hook OnScriptInit()
	{
		new
			find = strfind(YSI_gLockData[5], YSI_gLockData[1]) + 6;
		find = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		new
			found = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		if (strval(YSI_gLockData[found]) ^ 0x12345678 != _LOCK_IP_3 ^ 0x12345678 || strval(YSI_gLockData[find]) - _LOCK_IP_3 != _LOCK_IP_2 - _LOCK_IP_3)
		{
			y_lock 1;
		}
	}
#endif

