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

public
	YSI_gpThirdpartyTestValud = 41,
	YSI_gpThirdpartyTestValue = 42,
	YSI_gpThirdpartyTestValuf = 43,
	YSI_gpThirdpartyTest = 44;

#pragma unused YSI_gpThirdpartyTestValud, YSI_gpThirdpartyTestValue, YSI_gpThirdpartyTestValuf, YSI_gpThirdpartyTest

@test(.group = "y_thirdpartyinclude") GetSetPubVar()
{
	//ASSERT(GetNumPubVars() > 0);
	new value;
	YSI_gpThirdpartyTestValue = 42;
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValue", value));
	ASSERT_EQ(value, 42);
	ASSERT(SetPubVar("YSI_gpThirdpartyTestValue", 101));
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValud", value));
	ASSERT_EQ(value, 41);
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValuf", value));
	ASSERT_EQ(value, 43);
	ASSERT(GetPubVar("YSI_gpThirdpartyTestValue", value));
	ASSERT_EQ(value, 101);
}

#if defined getpubvar

@test(.group = "y_thirdpartyinclude") GetSetPubVar2()
{
	ASSERT(numpubvars() >= 3);
	YSI_gpThirdpartyTestValue = 7;
	ASSERT_EQ(setpubvar("YSI_gpThirdpartyTestValue", 42), 7);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 42);
	ASSERT_EQ(setpubvar("YSI_gpThirdpartyTestValue", 101), 42);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValud"), 41);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValuf"), 43);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 101);
	ASSERT(existpubvar("YSI_gpThirdpartyTestValue"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestValug"));
}

@test(.group = "y_thirdpartyinclude") GetSetPubVar3()
{
	YSI_gpThirdpartyTestValue = 789;
	YSI_gpThirdpartyTest = 123;
	ASSERT(existpubvar("YSI_gpThirdpartyTestValue"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestValu"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestVal"));
	ASSERT(existpubvar("YSI_gpThirdpartyTest"));
	ASSERT(!existpubvar("YSI_gpThirdpartyTestV"));
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTestValue"), 789);
	ASSERT_EQ(getpubvar("YSI_gpThirdpartyTest"), 123);
}

#endif

@test(.group = "y_thirdpartyinclude") CallNativeByAddress()
{
	//PrintAmxHeader();
	clamp(0, 5, 6);
	new res, addr = GetNativeAddressFromName("clamp");
	//printf("Address = %08x", addr);
	res = CallNativeByAddress(addr, 10, 11, 12);
	ASSERT_EQ(res, 11);
	res = CallNativeByAddress(addr, 10, 5, 15);
	ASSERT_EQ(res, 10);
	res = CallNativeByAddress(addr, 100, 7, 9);
	ASSERT_EQ(res, 9);
	res = CallNativeByAddress(addr, 6, 6, 6);
	ASSERT_EQ(res, 6);
}

