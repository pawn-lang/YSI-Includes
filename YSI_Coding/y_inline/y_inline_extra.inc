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
	new ret = mysql_format(handle, YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, query, ___(3));
	if (ret)
	{
		ret = mysql_pquery(handle, YSI_UNSAFE_HUGE_STRING, "Indirect_FromCallback", "ii", _:cb, true);
		if (ret)
		{
			Indirect_Claim(cb);
		}
	}
	return ret;
}

stock MySQL_TQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...)
{
	new ret = mysql_format(handle, YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, query, ___(3));
	if (ret)
	{
		ret = mysql_tquery(handle, YSI_UNSAFE_HUGE_STRING, "Indirect_FromCallback", "ii", _:cb, true);
		if (ret)
		{
			Indirect_Claim(cb);
		}
	}
	return ret;
}

stock ORM_SelectInline(ORM:id, Func:cb<>)
{
	new ret = orm_select(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_UpdateInline(ORM:id, Func:cb<>)
{
	new ret = orm_update(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_InsertInline(ORM:id, Func:cb<>)
{
	new ret = orm_insert(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_DeleteInline(ORM:id, Func:cb<>)
{
	new ret = orm_delete(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_LoadInline(ORM:id, Func:cb<>)
{
	new ret = orm_load(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_SaveInline(ORM:id, Func:cb<>)
{
	new ret = orm_save(id, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock BCrypt_CheckInline(text[], hash[], Func:cb<>)
{
	new ret = bcrypt_check(text, hash, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock BCrypt_HashInline(text[], cost, Func:cb<>)
{
	new ret = bcrypt_hash(text, cost, "Indirect_FromCallback", "ii", _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

