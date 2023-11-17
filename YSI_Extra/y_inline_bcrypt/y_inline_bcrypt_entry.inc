#if defined _INC_y_inline_bcrypt
	#endinput
#endif
#define _INC_y_inline_bcrypt

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
#include "..\..\YSI_Server\y_thirdpartyinclude\y3_indirection"
#include "..\y_bcrypt\y_bcrypt_natives"

forward _Inline_BCryptCheckDone(Func:cb<i>, success);
forward _Inline_BCryptHashDone(Func:cb<si>, hashid);

public _Inline_BCryptCheckDone(Func:cb<i>, success)
{
	// `success` may be uninitialised.
	if (success == -1)
	{
		success = _YSI_BCryptIsEqualA();
	}
	success = @.cb(success);
	Indirect_Release(cb);
	return _:success;
}

public _Inline_BCryptHashDone(Func:cb<si>, hashid)
{
	new hash[61];
	// If the plugin is anything other than `1` or `2` this can't be called
	// so there's no need for extra checks.
	switch (BCrypt_GetPlugin())
	{
	case 1:
		_YSI_BCryptGetHashA(hash);
	case 2:
		_YSI_BCryptGetHashB(hash, sizeof (hash));
	}
	hashid = @.cb(hash, hashid),
	Indirect_Release(cb);
	return hashid;
}

stock bool:BCrypt_CheckInline(const password[], const hash[], Func:cb<i>)
{
	switch (BCrypt_GetPlugin())
	{
	case 1:
		if (_YSI_BCryptCheckA(password, hash, "_Inline_BCryptCheckDone", "ii", _:cb, -1))
		{
			Indirect_Claim(cb);
			return true;
		}
	case 2:
		if (_YSI_BCryptCheckB(_:cb, "_Inline_BCryptCheckDone", password, hash))
		{
			Indirect_Claim(cb);
			return true;
		}
	}
	return false;
}

stock BCrypt_HashInline(const password[], cost = 12, {F@_@s, F@_@si}:cb) // Func:cb<s> | Func:cb<si>
{
	switch (BCrypt_GetPlugin())
	{
	case 1:
		if (_YSI_BCryptHashA(password, cost, "_Inline_BCryptHashDone", "ii", _:cb, ++_YSI_gHashID))
		{
			Indirect_Claim(cb);
			// Return the hashid.
			return _YSI_gHashID;
		}
	case 2:
		if ((cost = _YSI_BCryptHashB(_:cb, "_Inline_BCryptHashDone", password, cost)))
		{
			Indirect_Claim(cb);
			// Return the hashid.
			return cost;
		}
	}
	return 0;
}

