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

// Unify the two BCrypt plugins in to a single API.
#if defined bcrypt_included
	forward YSI_BCryptCheckDone(extra, ptr);
	forward YSI_BCryptHashDone(extra, ptr, hashid);

	// Fix the missing native.
	native BCrypt_GetHash(hash[], size = sizeof(hash)) = bcrypt_get_hash;

	// Plus keep the original version for backwards-compatibility.
	native YSI_BCryptGetHash(hash[], size = sizeof(hash)) = bcrypt_get_hash;
	native _YSI_BCryptCheck(const password[], const hash[], const callback_name[], const callback_format[], ...) = bcrypt_check;
	native _YSI_BCryptHash(const key[], cost, const callback_name[], const callback_format[], ...) = bcrypt_hash;
	native bool:_YSI_BCryptIsEqual(const key[], cost, const callback_name[], const callback_format[], ...) = bcrypt_is_equal;

	public YSI_BCryptCheckDone(extra, ptr)
	{
		// Call the original function.  I think the old compiler messes up if we
		// use the renamed version here.  Maybe.  Not sure why this doesn't use
		// `_YSI_BCryptIsEqual`...
		new success = bcrypt_is_equal();
		#emit PUSH.S       success
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
	}

	public YSI_BCryptHashDone(extra, ptr, hashid)
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

	stock BCrypt_Check(extra, const callback[], const input[], const hash[])
	{
		new ptr;
		if (AMX_GetPublicPointer(0, ptr, callback))
		{
			_YSI_BCryptCheck(input, hash, "YSI_BCryptCheckDone", "ii", extra, ptr);
		}
	}

	stock BCrypt_Hash(extra, const callback[], const input[], cost)
	{
		new ptr;
		static hashid = 0;
		++hashid;
		if (AMX_GetPublicPointer(0, ptr, callback))
		{
			_YSI_BCryptHash(input, cost, "YSI_BCryptHashDone", "iii", extra, ptr, hashid);
			return hashid;
		}
		return 0;
	}

#elseif defined _samp_bcrypt_included
	// I've never had to de-const a native before!
	// Wait, that's not true - `GetPlayerName` is over-const!
	native BCrypt_GetHash(hash[], size = sizeof(hash)) = bcrypt_get_hash;
	native BCrypt_Check(extra, const callback[], const input[], const hash[]) = bcrypt_verify;
	native BCrypt_Hash(extra, const callback[], const input[], cost) = bcrypt_hash;
#else
	// We used to not have an error for this case, just gave undefined errors.  But now they must
	// include it explicitly, so add a real error.
	#error Please include either BCrypt plugin first.
#endif

