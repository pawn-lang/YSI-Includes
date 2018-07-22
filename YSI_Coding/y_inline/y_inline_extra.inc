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

stock MySQL_PQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...)
{
	Indirect_Claim(cb);
	mysql_format(handle, YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, query, ___(3));
	mysql_pquery(handle, YSI_UNSAFE_HUGE_STRING, "Inline_FromCallback", "ii", _:cb, true);
}

stock MySQL_TQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...)
{
	Indirect_Claim(cb);
	mysql_format(handle, YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, query, ___(3));
	mysql_tquery(handle, YSI_UNSAFE_HUGE_STRING, "Inline_FromCallback", "ii", _:cb, true);
}

stock BCrypt_CheckInline(text[], hash[], Func:cb<>)
{
	Indirect_Claim(cb);
	bcrypt_check(text, hash, "Inline_FromCallback", "ii", _:cb, true);
}

stock BCrypt_HashInline(text[], cost, Func:cb<>)
{
	Indirect_Claim(cb);
	bcrypt_hash(text, cost, "Inline_FromCallback", "ii", _:cb, true);
}

