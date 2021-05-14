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

#if defined bcrypt_included

	static stock const
		YSI_gs_CALLBACK_i[] = "i";

	forward _Inline_BCryptCheckDone(Func:cb<i>);
	forward _Inline_BCryptHashDone(Func:cb<s>);

	public _Inline_BCryptCheckDone(Func:cb<i>)
	{
		new ret = @.cb(bcrypt_is_equal());
		Indirect_Release(cb);
		return ret;
	}

	public _Inline_BCryptHashDone(Func:cb<s>)
	{
		new hash[61];
		bcrypt_get_hash(hash);
		new ret = @.cb(hash);
		Indirect_Release(cb);
		return ret;
	}

	native _YSI_bcrypt_check_const(const password[], const hash[], const callback_name[], const callback_format[], Func:...<i>) = bcrypt_check;
	native _YSI_bcrypt_hash_const(const key[], cost, const callback_name[], const callback_format[], Func:...<s>) = bcrypt_hash;

	stock BCrypt_CheckInline(const text[], const hash[], Func:cb<i>)
	{
		new ret = _YSI_bcrypt_check_const(text, hash, "_Inline_BCryptCheckDone", YSI_gs_CALLBACK_i, cb);
		if (ret)
		{
			Indirect_Claim(cb);
		}
		return ret;
	}

	stock BCrypt_HashInline(const text[], cost = 12, Func:cb<s>)
	{
		new ret = _YSI_bcrypt_hash_const(text, cost, "_Inline_BCryptHashDone", YSI_gs_CALLBACK_i, cb);
		if (ret)
		{
			Indirect_Claim(cb);
		}
		return ret;
	}

#elseif defined _samp_bcrypt_included

	forward _Inline_BCryptCheckDone(Func:cb<i>, bool:success);
	forward _Inline_BCryptHashDone(Func:cb<s>, hashid);

	// I've never had to de-const a native before!
	native _YSI_bcrypt_get_hash_unconst(hash[], size = sizeof(hash)) = bcrypt_get_hash;
	
	public _Inline_BCryptCheckDone(Func:cb<i>, bool:success)
	{
		new ret = @.cb(success);
		Indirect_Release(cb);
		return ret;
	}

	public _Inline_BCryptHashDone(Func:cb<s>, hashid)
	{
		new hash[61];
		_YSI_bcrypt_get_hash_unconst(hash);
		new ret = @.cb(hash);
		Indirect_Release(cb);
		return ret;
	}

	native _YSI_bcrypt_check_const(Func:cb<i>, const callback[], const input[], const hash[]) = bcrypt_verify;
	native _YSI_bcrypt_hash_const(Func:cb<s>, const callback[], const input[], cost) = bcrypt_hash;

	stock BCrypt_CheckInline(const text[], const hash[], Func:cb<i>)
	{
		new ret = _YSI_bcrypt_check_const(cb, "_Inline_BCryptCheckDone", text, hash);
		if (ret)
		{
			Indirect_Claim(cb);
		}
		return ret;
	}

	stock BCrypt_HashInline(const text[], cost = 12, Func:cb<s>)
	{
		new ret = _YSI_bcrypt_hash_const(cb, "_Inline_BCryptHashDone", text, cost);
		if (ret)
		{
			Indirect_Claim(cb);
		}
		return ret;
	}

#else
	// We used to not have an error for this case, just gave undefined errors.  But now they must
	// include it explicitly, so add a real error.
	#error Please include either BCrypt plugin first.

	// This is an alternative, but less clear, method - more unimplmented function errors.
	forward BCrypt_CheckInline(const text[], const hash[], Func:cb<i>);
	forward BCrypt_HashInline(const text[], cost = 12, Func:cb<s>);
#endif

