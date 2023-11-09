#if defined _INC_y_bcrypt
	#endinput
#endif
#define _INC_y_bcrypt

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

#include "..\..\YSI_Core\y_utils"
#include "..\y_bcrypt\y_bcrypt_natives"

forward _YSI_BCryptCheckDone(extra, ptr);
forward _YSI_BCryptHashDone(extra, ptr, hashid);

public _YSI_BCryptCheckDone(extra, ptr)
{
	// Call the original function.
	new success = _YSI_BCryptIsEqualA();
	// See below for why this line is commented.  It IS passed, secretly.
	//#emit PUSH.S       success
	#pragma unused success
	#emit PUSH.S       extra
	#emit PUSH.C       __2_cells
	#emit LCTRL        __cip
	#emit ADD.C        __9_cells
	#emit LCTRL        __jit_jump
	#emit PUSH.pri
	#emit LOAD.S.pri   ptr
	#emit SCTRL        __cip
	// Fun fact.  If we just got rid of `PUSH.S success` and added `RETN` right here, the code
	// would still work because the `new` pushes the result on to the stack, then we push it a
	// second time.
	//
	// ...So do it, and let the callee clean up for us.
	#emit RETN
}

public _YSI_BCryptHashDone(extra, ptr, hashid)
{
	// Call the original function.
	#emit PUSH.S       hashid
	#emit PUSH.S       extra
	#emit PUSH.C       __2_cells
	#emit LCTRL        __cip
	#emit ADD.C        __9_cells
	#emit LCTRL        __jit_jump
	#emit PUSH.pri
	#emit LOAD.S.pri   ptr
	#emit SCTRL        __cip
}

stock bool:BCrypt_GetHash(hash[], size = sizeof (hash))
{
	// One plugin doesn't take a size parameter, so check it here.
	assert(size >= 61);
	switch (BCrypt_GetPlugin())
	{
	case 1:
		return _YSI_BCryptGetHashA(hash);
	case 2:
		return _YSI_BCryptGetHashB(hash, size);
	default:
		// None found.
		return false;
	}
}

stock bool:BCrypt_Check(extra, const callback[], const password[], const hash[])
{
	switch (BCrypt_GetPlugin())
	{
	case 1:
	{
		new ptr;
		return AMX_GetPublicPointer(0, ptr, callback, true) && _YSI_BCryptCheckA(password, hash, "_YSI_BCryptCheckDone", "ii", extra, ptr);
	}
	case 2:
		return _YSI_BCryptCheckB(extra, callback, password, hash);
	default:
		// None found.
		return 0;
	}
}

stock BCrypt_Hash(extra, const callback[], const password[], cost)
{
	switch (BCrypt_GetPlugin())
	{
	case 1:
	{
		new ptr;
		return
			++_YSI_gHashID,
			AMX_GetPublicPointer(0, ptr, callback, true) && _YSI_BCryptHashA(password, cost, "_YSI_BCryptHashDone", "iii", extra, ptr, _YSI_gHashID) ? _YSI_gHashID : 0;
	}
	case 2:
		return _YSI_BCryptHashB(extra, callback, password, cost);
	default:
		// None found.
		return false;
	}
}

