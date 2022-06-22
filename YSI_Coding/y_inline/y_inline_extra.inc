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

//
// These forward, but don't declare the "extra" functions.  The reason for this is simple - they
// used to be defined in here, but that's incredibly inefficient if these functions aren't actually
// used.  Not these functions themselves, the compiler is good at getting rid of them, but the
// public functions they called to process the results - the interim implementation details.  The
// reason why is simple - publics are ALWAYS included in the final mode, they can't be ommitted
// based on what other functions you might be calling.
//
// If you get one of the following errors, hopefully this text will direct you here (I doubt it -
// people don't even bother to read the error messages themselves, let alone search further, but
// there we go):
//
//     error 004: function "Timer_CreateCallback" is not implemented
//     error 004: function "SetCallbackTimer" is not implemented
//     error 004: function "Timer_KillCallback" is not implemented
//     error 004: function "KillCallbackTimer" is not implemented
//     error 004: function "RequestCallback" is not implemented
//     error 004: function "RequestJSONCallback" is not implemented
//     error 004: function "MySQL_PQueryInline" is not implemented
//     error 004: function "MySQL_TQueryInline" is not implemented
//     error 004: function "ORM_SelectInline" is not implemented
//     error 004: function "ORM_UpdateInline" is not implemented
//     error 004: function "ORM_InsertInline" is not implemented
//     error 004: function "ORM_DeleteInline" is not implemented
//     error 004: function "ORM_LoadInline" is not implemented
//     error 004: function "ORM_SaveInline" is not implemented
//     error 004: function "BCrypt_CheckInline" is not implemented
//     error 004: function "BCrypt_HashInline" is not implemented
//
// These functions have now moved to `YSI_Extra`.  So to use them, you need to explicitly include
// them:
//
//     #include <YSI_Extra\y_inline_mysql>
//     #include <YSI_Extra\y_inline_bcrypt>
//     #include <YSI_Extra\y_inline_requests>
//     #include <YSI_Extra\y_inline_timers>
//
// Obviously, pick-and-choose which you want.
//
forward Timer_CreateCallback(Func:func<>, initialOrTime, timeOrCount = 0, count = -1);
forward SetCallbackTimer(Func:func<>, initialOrTime, timeOrCount = 0, count = -1);
forward Timer_KillCallback(func);
forward KillCallbackTimer(func);
forward Request:RequestCallback(RequestsClient:id, const path[], E_HTTP_METHOD:method, Func:callback<iisi>, body[] = "", Headers:headers = Headers:-1);
forward Request:RequestJSONCallback(RequestsClient:id, const path[], E_HTTP_METHOD:method, Func:callback<iii>, Node:json = Node:-1, Headers:headers = Headers:-1);
forward MySQL_PQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...);
forward MySQL_TQueryInline(MySQL:handle, Func:cb<>, const query[], GLOBAL_TAG_TYPES:...);
forward ORM_SelectInline(ORM:id, Func:cb<>);
forward ORM_UpdateInline(ORM:id, Func:cb<>);
forward ORM_InsertInline(ORM:id, Func:cb<>);
forward ORM_DeleteInline(ORM:id, Func:cb<>);
forward ORM_LoadInline(ORM:id, Func:cb<>);
forward ORM_SaveInline(ORM:id, Func:cb<>);
forward bool:BCrypt_CheckInline(const password[], const hash[], Func:cb<i>);
forward BCrypt_HashInline(const password[], cost = 12, {F@_@s, F@_@si}:cb); // Func:cb<s> | Func:cb<si>

