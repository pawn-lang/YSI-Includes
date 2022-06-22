#if defined _INC_y_inline_mysql
	#endinput
#endif
#define _INC_y_inline_mysql

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

static stock const
	YSI_gs_CALLBACK_ii[] = "ii",
	YSI_gs_INDIRECT_FROM_CALLBACK[] = "Indirect_FromCallback";

stock MySQL_PQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...)
{
	new ret = mysql_format(handle, YSI_UNSAFE_HUGE_STRING, YSI_UNSAFE_HUGE_LENGTH, query, ___(3));
	if (ret)
	{
		ret = mysql_pquery(handle, YSI_UNSAFE_HUGE_STRING, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
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
		ret = mysql_tquery(handle, YSI_UNSAFE_HUGE_STRING, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
		if (ret)
		{
			Indirect_Claim(cb);
		}
	}
	return ret;
}

stock ORM_SelectInline(ORM:id, Func:cb<>)
{
	new ret = orm_select(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_UpdateInline(ORM:id, Func:cb<>)
{
	new ret = orm_update(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_InsertInline(ORM:id, Func:cb<>)
{
	new ret = orm_insert(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_DeleteInline(ORM:id, Func:cb<>)
{
	new ret = orm_delete(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_LoadInline(ORM:id, Func:cb<>)
{
	new ret = orm_load(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

stock ORM_SaveInline(ORM:id, Func:cb<>)
{
	new ret = orm_save(id, YSI_gs_INDIRECT_FROM_CALLBACK, YSI_gs_CALLBACK_ii, _:cb, true);
	if (ret)
	{
		Indirect_Claim(cb);
	}
	return ret;
}

