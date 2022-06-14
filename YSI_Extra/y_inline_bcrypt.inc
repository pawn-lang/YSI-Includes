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

#if !defined _INC_y_inline
	#tryinclude "..\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI\YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#error Could not find y_inline
#endif

#if !defined _INC_y_bcrypt
	#tryinclude ".\y_bcrypt"
#endif
#if !defined _INC_y_bcrypt
	#tryinclude "YSI_Extra\y_bcrypt"
#endif
#if !defined _INC_y_bcrypt
	#tryinclude "YSI\YSI_Extra\y_bcrypt"
#endif
#if !defined _INC_y_bcrypt
	#tryinclude <YSI_Extra\y_bcrypt>
#endif
#if !defined _INC_y_bcrypt
	#tryinclude <YSI\YSI_Extra\y_bcrypt>
#endif
#if !defined _INC_y_bcrypt
	#error Could not find y_bcrypt
#endif

#if defined bcrypt_included
	forward _Inline_BCryptCheckDone(Func:cb<i>);
	forward _Inline_BCryptHashDone(Func:cb<si>, hashid);
    
	public _Inline_BCryptCheckDone(Func:cb<i>)
	{
		new ret = @.cb(_YSI_BCryptIsEqual());
		Indirect_Release(cb);
		return ret;
	}
    
	public _Inline_BCryptHashDone(Func:cb<si>, hashid)
	{
		new hash[61];
		_YSI_BCryptGetHash(hash),
		hashid = @.cb(hash, hashid),
		Indirect_Release(cb);
		return hashid;
	}
    
	stock bool:BCrypt_CheckInline(const password[], const hash[], Func:cb<i>)
	{
		if (_YSI_BCryptCheck(password, hash, "_Inline_BCryptCheckDone", "i", cb))
		{
			Indirect_Claim(cb);
			return true;
		}
		return false;
	}
    
	stock BCrypt_HashInline(const password[], cost = 12, {F@_@s, F@_@si}:cb) // Func:cb<s> | Func:cb<si>
	{
		if (_YSI_BCryptHash(password, cost, "_Inline_BCryptHashDone", "ii", cb, ++_YSI_gHashID))
		{
			Indirect_Claim(cb);
			return _YSI_gHashID;
		}
		return 0;
	}
#elseif defined _samp_bcrypt_included
	forward _Inline_BCryptCheckDone(Func:cb<i>, bool:success);
	forward _Inline_BCryptHashDone(Func:cb<si>, hashid);

	public _Inline_BCryptCheckDone(Func:cb<i>, bool:success)
	{
		new ret = @.cb(success);
		Indirect_Release(cb);
		return ret;
	}

	public _Inline_BCryptHashDone(Func:cb<si>, hashid)
	{
		new hash[61];
		BCrypt_GetHash(hash),
		hashid = @.cb(hash, hashid),
		Indirect_Release(cb);
		return hashid;
	}

	stock bool:BCrypt_CheckInline(const password[], const hash[], Func:cb<i>)
	{
		if (BCrypt_Check(_:cb, "_Inline_BCryptCheckDone", password, hash))
		{
			Indirect_Claim(cb);
			return true;
		}
		return false;
	}

	stock BCrypt_HashInline(const password[], cost = 12, {F@_@s, F@_@si}:cb) // Func:cb<s> | Func:cb<si>
	{
		if ((cost = BCrypt_Hash(_:cb, "_Inline_BCryptHashDone", password, cost)))
		{
			Indirect_Claim(cb);
			// Return the hashid.
			return cost;
		}
		return 0;
	}

#else
	// We used to not have an error for this case, just gave undefined errors.  But now they must
	// include it explicitly, so add a real error.
	#error Please include either BCrypt plugin first.
#endif

