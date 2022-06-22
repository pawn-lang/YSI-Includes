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

// Unify the two BCrypt plugins in to a single API.
#if defined bcrypt_included
	stock _YSI_gHashID = 0;

	forward _YSI_BCryptCheckDone(extra, ptr);
	forward _YSI_BCryptHashDone(extra, ptr, hashid);

	native bool:_YSI_BCryptGetHash(hash[]) = bcrypt_get_hash;
	native bool:_YSI_BCryptCheck(const password[], const hash[], const callback[], const format[], ...) = bcrypt_check;
	native bool:_YSI_BCryptHash(const password[], cost, const callback[], const format[], ...) = bcrypt_hash;
	native bool:_YSI_BCryptIsEqual() = bcrypt_is_equal;

	// Fix the missing native.
	stock bool:BCrypt_GetHash(hash[], size = sizeof (hash))
	{
		// The native doesn't take a size parameter, so check it here.
		assert(size >= 61);
		return _YSI_BCryptGetHash(hash);
	}

	// Plus keep the original version for backwards-compatibility.
	#pragma deprecated Use `BCrypt_GetHash`.
	native bool:YSI_BCryptGetHash(hash[]) = bcrypt_get_hash;
	#define YSI_BCryptGetHash(%0,%1) YSI_BCryptGetHash(%0)
	#define _ALS_YSI_BCryptGetHash

	public _YSI_BCryptCheckDone(extra, ptr)
	{
		// Call the original function.
		new success = _YSI_BCryptIsEqual();
		// See below for why this line is commented.  It IS passed, secretly.
		//#emit PUSH.S       success
		#emit PUSH.S       extra
		#emit PUSH.C       8
		#emit LCTRL        6
		#emit ADD.C        36
		#emit LCTRL        8
		#emit PUSH.pri
		#emit LOAD.S.pri   ptr
		#emit SCTRL        6
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
		#emit PUSH.C       8
		#emit LCTRL        6
		#emit ADD.C        36
		#emit LCTRL        8
		#emit PUSH.pri
		#emit LOAD.S.pri   ptr
		#emit SCTRL        6
	}

	stock bool:BCrypt_Check(extra, const callback[], const password[], const hash[])
	{
		new ptr;
		return AMX_GetPublicPointer(0, ptr, callback) && _YSI_BCryptCheck(password, hash, "_YSI_BCryptCheckDone", "ii", extra, ptr);
	}

	stock BCrypt_Hash(extra, const callback[], const password[], cost)
	{
		new ptr;
		return
			++_YSI_gHashID,
			AMX_GetPublicPointer(0, ptr, callback) && _YSI_BCryptHash(password, cost, "_YSI_BCryptHashDone", "iii", extra, ptr, _YSI_gHashID) ? _YSI_gHashID : 0;
	}
#elseif defined _samp_bcrypt_included
	// I've never had to de-const a native before!
	// Wait, that's not true - `GetPlayerName` is over-const!
	native bool:BCrypt_GetHash(hash[], size = sizeof (hash)) = bcrypt_get_hash;
	native bool:BCrypt_Check(extra, const callback[], const password[], const hash[]) = bcrypt_verify;
	native bool:BCrypt_Hash(extra, const callback[], const password[], cost) = bcrypt_hash;
#else
	// We used to not have an error for this case, just gave undefined errors.  But now they must
	// include it explicitly, so add a real error.
	#error Please include either BCrypt plugin first.
#endif

