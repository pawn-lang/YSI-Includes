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

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 239
#endif

static stock MakeYINITestPath(const file[])
{
	new ret[48];
	return
		strcat(ret, GetYSIScriptfilesDir(E_YSI_DIR_TESTS)),
		strcat(ret, "y_ini/"),
		strcat(ret, file),
		ret;
}

static e_INI_LINE_TYPE:INI_IDENTIFY_LINE_TYPE(str[MAX_INI_LINE], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e)
{
	YSI_g_sExtendedName[0] = '\0';
	if (YSI_g_sExtendedLine)
	{
		free(YSI_g_sExtendedLine);
		YSI_g_sExtendedLine = NO_ALLOC;
	}
	return INI_IdentifyLineType(str, p0s, p0e, p1s, p1e, p2s, p2e);
}

@test(.group = "y_ini") INI_IdentifyLineType1()
{
	// Comment lines and blank lines may as well be treated as the same thing,
	// except when rewriting the file.
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Comment lines.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("; Hello", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("   ; There", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("	; Hi", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(";", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(";\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_NE(INI_IDENTIFY_LINE_TYPE("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_NE(INI_IDENTIFY_LINE_TYPE("hi ; there", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	// Blank lines.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("    ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("	\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
}

@test(.group = "y_ini") INI_IdentifyLineType2()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Invalid lines.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IDENTIFY_LINE_TYPE("[badtag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("   [tag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("   [   ]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("[tag;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("[tag\\;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_NE(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE(" [tag\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE(" [tag\\\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_NE(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("key", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("key\\=", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("key\\\\\\=value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("key =  ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT); // Now allowed again!
	result = INI_IDENTIFY_LINE_TYPE(" = value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("thing", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IDENTIFY_LINE_TYPE("thing ; comment", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
}

@test(.group = "y_ini") INI_IdentifyLineType3()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Entry lines.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key = value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key=value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 4 && p1e == 9 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key = value ; comment", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 14 && p2e == 21);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key = value ;   comment\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 16 && p2e == 23);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key =  value   ; com ment  \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 7 && p1e == 12 && p2s == 17 && p2e == 25);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key = value\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key	=value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 5 && p1e == 10 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("   key=	value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("   key=	value    ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("	key   =value  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 1 && p0e == 4 && p1s == 8 && p1e == 13 && p2s == p2e);
}

@test(.group = "y_ini") INI_IdentifyLineType3b()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Regressions from Discord.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("k=value\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT_EQ(p0s, 0);
	ASSERT_EQ(p0e, 1);
	ASSERT_EQ(p1s, 2);
	ASSERT_EQ(p1e, 7);
	ASSERT_EQ(p2s, p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key=1\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT_EQ(p0s, 0);
	ASSERT_EQ(p0e, 3);
	ASSERT_EQ(p1s, 4);
	ASSERT_EQ(p1e, 5);
	ASSERT_EQ(p2s, p2e);
	// Allow this as an entry of text `=`.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key==\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT_EQ(p0s, 0);
	ASSERT_EQ(p0e, 3);
	ASSERT_EQ(p1s, 4);
	ASSERT_EQ(p1e, 5);
	ASSERT_EQ(p2s, p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("key = 1\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT_EQ(p0s, 0);
	ASSERT_EQ(p0e, 3);
	ASSERT_EQ(p1s, 6);
	ASSERT_EQ(p1e, 7);
	ASSERT_EQ(p2s, p2e);
}

@test(.group = "y_ini") INI_IdentifyLineType4()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Tag lines.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(" [hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(" [ hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(" [hello ] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[ hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello   ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[   hello ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 4 && p0e == 9 && p1s == p1e && p2s == p2e);
}

@test(.group = "y_ini") INI_IdentifyLineType5()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Inheritance.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] : ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] : first", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 15 && p2s == p2e);
	// ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	// ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	// ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// These used to work, now they don't.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// Commented out.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] ;: ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 9 && p2e == 10);
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE("[hello] ; : first, second ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 10 && p2e == 25);
	// Both.
	ASSERT_EQ(INI_IDENTIFY_LINE_TYPE(" [ hello ]  :  inheritance  ;  : first, second ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == 15 && p1e == 26 && p2s == 31 && p2e == 46);
}

@test(.group = "y_ini") INI_IdentifyLineType6a()
{
	state y_ini:y_ini_writing_fast;
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Continuation.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("hi = there\\ ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\\r", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\\n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\ \n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT(p0s == 0 && p1e == 10);
	ASSERT_EQ(INI_IdentifyLineType("hi = there  \\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p1e == 12);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 8 && p1e == 8);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\;  Hello  \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 8 && p1e == 17);
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\ ; Hello  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 8 && p1e == 8);
	ASSERT(p2s == 10 && p2e == 17);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hello there ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT_EQ(INI_IdentifyLineType("hello there \\  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT_EQ(INI_IdentifyLineType("hi = hello\\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 0);
	ASSERT(p1s == 0 && p1e == 10);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
}

@test(.group = "y_ini") INI_IdentifyLineType6b()
{
	state y_ini:y_ini_reading_yyyn;
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Continuation.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("hi = there\\ ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\\r", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\\n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	result = INI_IdentifyLineType("hi = there\\ \n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_CONT);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT(p0s == 0 && p1e == 10);
	ASSERT_EQ(INI_IdentifyLineType("hi = there  \\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p1e == 12);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 8 && p1e == 8);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\;  Hello  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
#if defined Y_INI_NO_ESCAPES
	ASSERT(p1s == 8 && p1e == 17);
#else
	ASSERT(p1s == 8 && p1e == 16);
#endif
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\ ; Hello  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 8 && p1e == 8);
	ASSERT(p2s == 10 && p2e == 17);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hello there ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT_EQ(INI_IdentifyLineType("hello there \\  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT_EQ(INI_IdentifyLineType("hi = hello\\   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 0);
	ASSERT(p1s == 0 && p1e == 10);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
}

@test(.group = "y_ini") INI_Continuation()
{
	new p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	INI_IdentifyLineType("hi = hello \\\r\n", p0s, p0e, p1s, p1e, p2s, p2e);
	INI_IdentifyLineType("world = the \\ ; Ignore me", p0s, p0e, p1s, p1e, p2s, p2e);
	INI_IdentifyLineType("\\ whole string     ", p0s, p0e, p1s, p1e, p2s, p2e);
	//new str[256];
	//mgets(str, _, YSI_g_sExtendedLine, 1);
	//printf(str);
	ASSERT_SAME(mget(YSI_g_sExtendedLine, 1), "hello world = the \\ whole string");
	// Cleanup.
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
}

#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

@test(.group = "y_ini") Trim1()
{
	new start = 0, end = 9;
	Trim("  hello  ", start, end);
	ASSERT_EQ(start, 2);
	ASSERT_EQ(end, 7);
	start = 0, end = 9;
	Trim("         ", start, end);
	ASSERT_EQ(start, 9);
	ASSERT_EQ(end, 9);
	start = 6, end = 13;
	Trim(" hello there ", start, end);
	ASSERT_EQ(start, 7);
	ASSERT_EQ(end, 12);
	start = 0, end = 13;
	Trim("hello there ", start, end);
	ASSERT_ZE(start);
	ASSERT_EQ(end, 11);
}

static stock
	YSI_g_sINI_Parse0 = 0;

forward TestINI_Parse0_test1(key[], value[]);

public TestINI_Parse0_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

@test(.group = "y_ini") INI_Parse0()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	if (IsWindows())
	{
		YSI_g_sINI_Parse0 = 0;
		INI_ParseFile("YSI\\tests\\y_ini\\test1.ini", "TestINI_Parse0_%s", .bFileFirst = true);
		ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	}
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "unf");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s", .bFileFirst = true); //, .bFilter = false, .filter = "unf");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s", .bFileFirst = true); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s%s", .bFileFirst = true); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse0_%s%s", .bFileFirst = false); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

forward TestINI_Parse1_test1_(key[], value[]);

public TestINI_Parse1_test1_(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

@test(.group = "y_ini") INI_Parse1()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse1_%s_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

forward TestINI_Parse2_test1_(key[], value[]);

public TestINI_Parse2_test1_(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse2_test1_tag2(key[], value[]);

public TestINI_Parse2_test1_tag2(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

@test(.group = "y_ini") INI_Parse2()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse2_%s_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 7);
}

forward TestINI_Parse3__test1(key[], value[]);

public TestINI_Parse3__test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse3_atag_test1(key[], value[]);

public TestINI_Parse3_atag_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse3_tag2_test1(key[], value[]);

public TestINI_Parse3_tag2_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

@test(.group = "y_ini") INI_Parse3()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false); //, .bFilter = false, .filter = "other");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

@test(.group = "y_ini") INI_Parse4()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false/*, .bFilter = false, .filter = "filter"*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse3_%s_%s", .bFileFirst = false/*, .bFilter = false, .filter = "other"*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

// Test passing the tag.

forward TestINI_Parse5_test1(tag[], key[], value[]);

public TestINI_Parse5_test1(tag[], key[], value[])
{
	printf("%s, %s, %s", tag, key, value);
	if (IsNull(tag)) ++YSI_g_sINI_Parse0;
}

@test(.group = "y_ini") INI_Parse5()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_%sParse5_%s", .bFileFirst = false, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

@test(.group = "y_ini") INI_Parse6()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true/*, .bFilter = false*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true/*, .bFilter = false*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

@test(.group = "y_ini") INI_Parse7()
{
	inline const F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 1;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

@test(.group = "y_ini") INI_Parse8()
{
	inline F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 2;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 20);
}

@test(.group = "y_ini") INI_Parse9()
{
	inline const F_atag_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 3;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s_%s");
	ASSERT_EQ(YSI_g_sINI_Parse0, 9);
}

@test(.group = "y_ini") INI_Parse10()
{
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 4;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s_%s");
	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
}

@test(.group = "y_ini") INI_Parse11()
{
	new
		a = 0;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s_%s");
	ASSERT_EQ(a, 0);
}

@test(.group = "y_ini") INI_Parse12()
{
	static
		a = 0;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s_%s");
	ASSERT_EQ(a, 8);
}

@test(.group = "y_ini") INI_Parse13()
{
	new
		a = 0;
	inline F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "F_%s_%s");
	ASSERT_EQ(a, 8);
}

@test(.group = "y_ini") INI_ParseInline()
{
	new
		num = 0,
		ret = 0;
	inline Inline1(string:key[], string:value[])
	{
		#pragma unused key, value
		++num;
	}
//	num = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inline1", .bFilter = true, .filter = "other");
//	ASSERT_EQ(num, 8);
//	// This line also seems to have the -O1 -d0 bug.  It must be caused by the
//	// extra "tag" parameter somehow...
//	inline Inline2(string:tag[], string:key[], string:value[])
//	{
//		#pragma unused key, value
//		if (IsNull(tag)) ++num;
//	}
//	num = 0;
//	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inline2", .bFilter = true, .filter = "other", .bPassTag = true);
//	ASSERT_EQ(num, 5);
	inline Inline3(extra, string:key[], string:value[])
	{
		#pragma unused key, value
		num += extra;
	}
	num = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inline3%s", .bExtra = true, .extra = 11);
	ASSERT_EQ(num, 55);
	inline Inline4(extra, string:tag[], string:key[], string:value[])
	{
		#pragma unused key, value
		ret = extra;
		if (!IsNull(tag) && !strcmp(tag, "tag2")) ++num;
	}
	ret = 0;
	num = 0;
	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inline4", .bPassTag = true, .bExtra = true, .extra = 42);
	ASSERT_EQ(num, 2);
	ASSERT_EQ(ret, 42);
}

@test(.group = "y_ini") INI_Int0()
{
	DoINI_Int0();
}

static stock DoINI_Int0()
{
	new
		k0 = 0,
		k1 = 0,
		k2 = 0,
		k3 = 0,
		k4 = 0;
	inline Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inl_%s");
	ASSERT_EQ(k0, 42);
	ASSERT_EQ(k1, 43);
	ASSERT_EQ(k2, 45);
	ASSERT_EQ(k3, 47);
	ASSERT_EQ(k4, 46);
	return 0;
}

@test(.group = "y_ini") INI_Int2()
{
	DoINI_Int2();
}

static stock DoINI_Int2()
{
	new
		k0 = 0,
		k1 = 0,
		k2 = 0,
		k3 = 0,
		k4 = 0;
	inline const Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inl_%s");
	ASSERT_ZE(k0);
	ASSERT_ZE(k1);
	ASSERT_ZE(k2);
	ASSERT_ZE(k3);
	ASSERT_ZE(k4);
	return 0;
}

@test(.group = "y_ini") INI_Int3()
{
	DoINI_Int3();
}

static stock DoINI_Int3()
{
	new
		k0 = 0,
		k1 = 0,
		k2 = 0,
		k3 = 0,
		k4 = 0;
	new
		sk0[8],
		Float:sk1 = 0.0,
		bool:sk2 = true;
	new
		tk0[8],
		tk1[8];
	inline Inl_(string:tag[], string:name[], string:value[])
	{
		// TODO:  I think there's a bug in here somewhere, with "GTYPE=0 MTYPE=1
		// -O1 -d0", which crashes on ENTRY to this inline.  I think that the
		// problem may be too much, or incorrect, code being output.
		switch (YHash(tag, false))
		{
			case _I<>:
			{
				INI_Int("key0", k0);
				INI_Int("key1", k1);
				INI_Int("key2", k2);
				INI_Int("key3", k3);
				INI_Int("key4", k4);
			}
			case _I<atag>:
			{
				INI_String("key0", sk0);
				INI_Float("otherKey", sk1);
				INI_Bool("myKey", sk2);
			}
			case _I<tag2>:
			{
				INI_String("filtered1", tk0);
				INI_String("filtered2", tk1);
			}
		}
	}
	INI_ParseFile(MakeYINITestPath("test1.ini"), "Inl_", .bPassTag = true);
	// First.
	ASSERT_EQ(k0, 42);
	ASSERT_EQ(k1, 43);
	ASSERT_EQ(k2, 45);
	ASSERT_EQ(k3, 47);
	ASSERT_EQ(k4, 46);
	// Second.
	ASSERT(!IsNull(sk0) && !strcmp(sk0, "hello"));
	ASSERT_EQ(sk1, 5.5);
	ASSERT(!sk2);
	// Third.
	ASSERT(!IsNull(tk0) && !strcmp(tk0, "yes"));
	ASSERT(!IsNull(tk1) && !strcmp(tk1, "no"));
	return 0;
}


static stock
	gs_mFS[32],
	gs_mName[32],
	gs_mCreator[32],
	gs_mMode,
	gs_mWeather,
	gs_mInterior;

forward INI_ReadRegression_data(string:name[], string:value[]);

public INI_ReadRegression_data(string:name[], string:value[])
{
	INI_String("mFS", gs_mFS);
	INI_String("mName", gs_mName);
	INI_String("mCreator", gs_mCreator);
	INI_Int("mMode", gs_mMode);
	INI_Int("mWeather", gs_mWeather);
	INI_Int("mInterior", gs_mInterior);

	return 0;
}

@test(.group = "y_ini") INI_ReadRegression()
{
	INI_ParseFile(MakeYINITestPath("test0.ini"), "INI_ReadRegression_%s");
	ASSERT_SAME(gs_mFS, "hayran");
	ASSERT_SAME(gs_mName, "Warehouse");
	ASSERT_SAME(gs_mCreator, "Hayran");
	ASSERT_EQ(gs_mMode, 1);
	ASSERT_EQ(gs_mWeather, 10);
	ASSERT_EQ(gs_mInterior, 0);
}

static stock
	gs_K0 = 0,
	gs_K1 = 0,
	gs_K2 = 0,
	gs_K3 = 0,
	gs_K4 = 0,
	gs_K5 = 0;

forward INI_PUB_Inl_(string:name[], string:value[]);

public INI_PUB_Inl_(string:name[], string:value[])
{
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	return 0;
}

@test(.group = "y_ini") INI_Int1()
{
	INI_ParseFile(MakeYINITestPath("test1.ini"), "INI_PUB_Inl_%s");
	ASSERT_EQ(gs_K0, 42);
	ASSERT_EQ(gs_K1, 43);
	ASSERT_EQ(gs_K2, 45);
	ASSERT_EQ(gs_K3, 47);
	ASSERT_EQ(gs_K4, 46);
}

@test(.group = "y_ini") INI_WriteComments()
{
	new File:f;
	new str[32];

	f = fopen(MakeYINITestPath("test10.ini"), io_read);
	ASSERT(!!f);
	if (f)
	{
		fread(f, str);
		StripNL(str);
		ASSERT_SAME(str, "[tag_with_parent]");
		fread(f, str);
		StripNL(str);
		ASSERT_SAME(str, "value_four=Some_semi_colons");
		fread(f, str);
		StripNL(str);
		ASSERT_SAME(str, "value_three=Some\\;semi\\;colons");
		fread(f, str);
		StripNL(str);
		ASSERT_SAME(str, "value=5");
		ASSERT(!!fread(f, str));
		StripNL(str);
		ASSERT_SAME(str, "");
		fclose(f);
	}

	new INI:i = INI_Open(MakeYINITestPath("test10.ini"));
	INI_SetTag(i, "tag_with_parent");
	INI_RemoveEntry(i, "value");
	INI_Close(i);

	f = fopen(MakeYINITestPath("test10.ini"), io_read);
	ASSERT(!!f);
	if (f)
	{
		fread(f, str);
		printf("Read file: %s", str);
		StripNL(str);
		ASSERT_SAME(str, "[tag_with_parent]");
		fread(f, str);
		printf("Read file: %s", str);
		StripNL(str);
		ASSERT_SAME(str, "value_four=Some_semi_colons");
		fread(f, str);
		printf("Read file: %s", str);
		StripNL(str);
		ASSERT_SAME(str, "value_three=Some\\;semi\\;colons");
		fread(f, str);
		printf("Read file: %s", str);
		StripNL(str);
		ASSERT_SAME(str, "");
		fclose(f);
	}
}

@testinit() INI_WriteComments()
{
	new INI:i = INI_Open(MakeYINITestPath("test10.ini"));
	INI_SetTag(i, "tag_with_parent");
	INI_WriteInt(i, "value", 5);
	INI_WriteString(i, "value_three", "Some;semi;colons");
	INI_WriteString(i, "value_four", "Some_semi_colons");
	INI_Close(i);
}

@testclose() INI_WriteComments()
{
	new INI:i = INI_Open(MakeYINITestPath("test10.ini"));
	INI_SetTag(i, "tag_with_parent");
	INI_WriteInt(i, "value", 5);
	INI_WriteString(i, "value_three", "Some;semi;colons");
	INI_WriteString(i, "value_four", "Some_semi_colons");
	INI_Close(i);
}

forward INI_Inher0_tag0(string:tag[], string:name[], string:value[]);

public INI_Inher0_tag0(string:tag[], string:name[], string:value[])
{
	ASSERT(!IsNull(tag) && !strcmp(tag, "tag0"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

@test(.group = "y_ini") INI_Inherit0()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile(MakeYINITestPath("test2.ini"), "INI_Inher0_%s", .bPassTag = true);
	ASSERT_EQ(gs_K0, 101);
	ASSERT_EQ(gs_K1, 102);
	ASSERT_EQ(gs_K2,   0);
	ASSERT_EQ(gs_K3,   0);
	ASSERT_EQ(gs_K4,   0);
	ASSERT_EQ(gs_K5,   0);
}

forward INI_Inher1_tag1(string:tag[], string:name[], string:value[]);

public INI_Inher1_tag1(string:tag[], string:name[], string:value[])
{
	ASSERT(!IsNull(tag) && !strcmp(tag, "tag1"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

@test(.group = "y_ini") INI_Inherit1()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile(MakeYINITestPath("test2.ini"), "INI_Inher1_%s", .bPassTag = true);
	ASSERT_EQ(gs_K0, 101);
	ASSERT_EQ(gs_K1, 102);
	ASSERT_EQ(gs_K2, 103);
	ASSERT_EQ(gs_K3, 104);
	ASSERT_EQ(gs_K4,   0);
	ASSERT_EQ(gs_K5,   0);
}

forward INI_Inher2_tag2(string:tag[], string:name[], string:value[]);

public INI_Inher2_tag2(string:tag[], string:name[], string:value[])
{
	ASSERT(!IsNull(tag) && !strcmp(tag, "tag2"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

@test(.group = "y_ini") INI_Inherit2()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile(MakeYINITestPath("test2.ini"), "INI_Inher2_%s", .bPassTag = true);
	ASSERT_EQ(gs_K0, 107);
	ASSERT_EQ(gs_K1, 102);
	ASSERT_EQ(gs_K2, 103);
	ASSERT_EQ(gs_K3, 104);
	ASSERT_EQ(gs_K4, 105);
	ASSERT_EQ(gs_K5, 106);
}

// Writing tests.

@test(.group = "y_ini") INI_AddToBuffer0()
{
	new
		INI:i = INI_Open(MakeYINITestPath("test3.ini"));
	ASSERT_NE(File:i, File:INI_NO_FILE);
	ASSERT(!INI_AddToBuffer(i, "", "hi"));
	ASSERT(!INI_AddToBuffer(INI_NO_FILE, "foo", "bar"));
	ASSERT(INI_AddToBuffer(i, "key", "value"));
	ASSERT(INI_AddToBuffer(i, "first", "second"));
	ASSERT(INI_AddToBuffer(i, "first", "third"));
	ASSERT(INI_AddToBuffer(i, "first", "fourth"));
	ASSERT(INI_AddToBuffer(i, "first", "fifth"));
	INI_Close(i);
}

@test(.group = "y_ini") INI_AddToBuffer0a()
{
	new
		INI:i = INI_Open(MakeYINITestPath("test3.ini"));
	ASSERT_NE(File:i, File:INI_NO_FILE);
	ASSERT(!INI_AddToBuffer(i, "", "hi"));
	ASSERT(!INI_AddToBuffer(INI_NO_FILE, "foo", "bar"));
	ASSERT(INI_AddToBuffer(i, "key", "value"));
	ASSERT(INI_AddToBuffer(i, "first", "second"));
	ASSERT(INI_AddToBuffer(i, "first", "third"));
	ASSERT(INI_AddToBuffer(i, "first", "fourth"));
	ASSERT(INI_AddToBuffer(i, "first", "fifth"));
	INI_Close(i);
}

@test(.group = "y_ini") INI_AddToBuffer1()
{
	new
		INI:i = INI_Open(MakeYINITestPath("test4.ini"));
	ASSERT(INI_AddToBuffer(i, "key2", "value2"));
	INI_SetTag(i, "tag0");
	ASSERT(INI_AddToBuffer(i, "key2", "value3"));
	ASSERT(INI_AddToBuffer(i, "key2", "value4"));
	INI_DeleteTag(i, "tag0");
	ASSERT(!INI_AddToBuffer(i, "key2", "value5"));
	INI_Close(i);
}

forward INI_WriteOne(tag[], name[], value[]);

public INI_WriteOne(tag[], name[], value[])
{
	if (!strcmp(tag, "tag"))
	{
		if (!strcmp(name, "thing")) YSI_g_sINI_Parse0 += strval(value);
		if (!strcmp(name, "key")) YSI_g_sINI_Parse0 += strval(value);
		if (!strcmp(name, "name")) ++YSI_g_sINI_Parse0;
		if (!strcmp(name, "alt")) YSI_g_sINI_Parse0 += floatround(floatstr(value));
		if (!strcmp(name, "you")) YSI_g_sINI_Parse0 += strval(value);
		if (!strcmp(name, "hi")) ++YSI_g_sINI_Parse0;
		if (!strcmp(name, "yeah")) ++YSI_g_sINI_Parse0;
		if (!strcmp(name, "another")) YSI_g_sINI_Parse0 += strval(value);
	}
	else
	{
		YSI_g_sINI_Parse0 = 100;
	}
}

@test(.group = "y_ini") fseek()
{
	if (Server_IsSAMP())
	{
		// Always fails on SA:MP, no point even testing it!  The native is
		// broken.
		return;
	}
	fremove(MakeYINITestPath("fseek.ini"));
	new File:f = fopen(MakeYINITestPath("fseek.ini"), io_write);
	ASSERT(!!f);
	if (!f)
	{
		return;
	}
	fwrite(f, "hello world");
	fseek(f, 0, seek_start);
	fwrite(f, "hi");
	ASSERT_EQ(flength(f), 11);
	fwrite(f, "hello world");
	ASSERT_EQ(flength(f), 13);
	fclose(f);
}

@test(.group = "y_ini") INI_Write3()
{
	fremove(MakeYINITestPath("test9.ini"));
	new
		INI:i = INI_Open(MakeYINITestPath("test9.ini"));
	ASSERT_NE(File:i, File:INI_NO_FILE);
	INI_WriteString(i, "hi", "there");
	INI_SetTag(i, "tag");
	INI_WriteString(i, "yeah", "yeah");
	INI_WriteString(i, "hi", "you");
	INI_WriteInt(i, "you", 42);
	INI_WriteFloat(i, "alt", 40.1);
	INI_WriteBool(i, "name", true);
	INI_WriteInt(i, "key", 43);
	INI_WriteInt(i, "thing", 44);
	INI_Close(i);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test9.ini"), "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 42 + 40 + 43 + 44 + 3);
	i = INI_Open(MakeYINITestPath("test9.ini"));
	INI_SetTag(i, "tag");
	INI_WriteString(i, "another", "200");
	INI_WriteInt(i, "you", 200);
	INI_Close(i);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test9.ini"), "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 200 + 200 + 40 + 43 + 44 + 3);
	i = INI_Open(MakeYINITestPath("test9.ini"));
	INI_SetTag(i, "tag");
	INI_RemoveEntry(i, "another");
	INI_Close(i);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile(MakeYINITestPath("test9.ini"), "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 200 + 40 + 43 + 44 + 3);
}

//@test(.group = "y_ini") INI_VariousWriting0()
//{
//	new
//		INI:i = INI_Open(MakeYINITestPath("test5.ini"));
//	new
//		s = INI_AddToBuffer(i, "writing", "written");
//	ASSERT_NE(s, -1);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "writing");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "written");
//	new
//		t = YSI_g_sINICurrentTag[i];
//	ASSERT_NEAR(YSI_g_sINITagBuffer[t][E_INI_TAGS_NAME], "\1\0");
//	ASSERT_EQ(YSI_g_sINITagBuffer[t][E_INI_TAGS_START], s);
//	ASSERT_EQ(YSI_g_sINITagBuffer[t][E_INI_TAGS_NEXT], -1);
//	new
//		x = INI_SetTag(i, "hello");
//	ASSERT_NE(x, -1);
//	ASSERT_EQ(YSI_g_sINITagBuffer[t][E_INI_TAGS_NEXT], -1);
//	ASSERT_EQ(YSI_g_sINITagBuffer[x][E_INI_TAGS_NEXT], t);
//	ASSERT_EQ(YSI_g_sINITagBuffer[x][E_INI_TAGS_START], -1);
//	INI_Close(i);
//}
//
//@test(.group = "y_ini") INI_VariousWriting1()
//{
//	new
//		INI:f = INI_Open(MakeYINITestPath("test5.ini")),
//		s;
//	// String.
//	s = INI_WriteString(f, "vvv", "yyy");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "yyy");
//	// Dec.
//	s = INI_WriteInt(f, "vvv", 57);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "57");
//	s = INI_WriteInt(f, "vvv", cellmin);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "-2147483648");
//	s = INI_WriteInt(f, "vvv", -99);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "-99");
//	// Hex.
//	s = INI_WriteHex(f, "vvv", 0x112233);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0x00112233");
//	s = INI_WriteHex(f, "vvv", cellmin);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0x80000000");
//	s = INI_WriteHex(f, "vvv", cellmax);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0x7FFFFFFF");
//	// Bin.
//	s = INI_WriteBin(f, "vvv", 0);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0b0");
//	s = INI_WriteBin(f, "vvv", 1);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0b1");
//	s = INI_WriteBin(f, "vvv", -1);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0b11111111111111111111111111111111");
//	// Bool.
//	s = INI_WriteBool(f, "vvv", false);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "false");
//	s = INI_WriteBool(f, "vvv", true);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "true");
//	// Float.
//	s = INI_WriteFloat(f, "vvv", 0.0);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0.000000");
//	s = INI_WriteFloat(f, "vvv", 0.2);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0.200000");
//	s = INI_WriteFloat(f, "vvv", 0.2, 2);
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], "vvv");
//	ASSERT_NEAR(YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], "0.20");
//	INI_Close(f);
//}

@test(.group = "y_ini") INI_Write0()
{
	new
		INI:f = INI_Open(MakeYINITestPath("test6.ini")),
		str[32];
	for (new i = 0; i != 12; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_SetTag(f, "hello");
	for (new i = 0; i != 64; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_SetTag(f, "woo");
	for (new i = 0; i != 64; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_Close(f);
}

@test(.group = "y_ini") INI_Write1()
{
	new
		INI:f = INI_Open(MakeYINITestPath("test6.ini")),
		str[32];
	for (new i = 0; i != 16; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_SetTag(f, "hello");
	for (new i = 0; i != 32; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_SetTag(f, "woo");
	for (new i = 0; i != 20; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_Close(f);
}

@test(.group = "y_ini") INI_Write2()
{
	new
		INI:f = INI_Open(MakeYINITestPath("test6.ini"));
	INI_DeleteTag(f, "woo");
	INI_Close(f);
}

enum E_INI14_TEST
{
	E_INI14_TEST_FIRST_KEY[32],
	E_INI14_TEST_SECOND_KEY,
	E_INI14_TEST_C,
	Float:E_INI14_TEST_THIRD_KEY,
	E_INI14_TEST_FOURTH_KEY[32],
	E_INI14_TEST_FIFTH_KEY
}

static stock
	YSI_g_sTestParents[4][E_INI14_TEST];

forward INI_Parents(extra, file[], tag[], name[], value[]);

public INI_Parents(extra, file[], tag[], name[], value[])
{
	ASSERT_SAME(file, "test7");
	if (!strcmp(tag, "parent"))
		extra = extra - 3;
	else if (!strcmp(tag, "child"))
		extra = extra - 2;
	else if (!strcmp(tag, "grandchild"))
		extra = extra - 1;
	else
		ASSERT(false);
	INI_String("first_key", YSI_g_sTestParents[extra][E_INI14_TEST_FIRST_KEY], 32);
	INI_Int("second_key", YSI_g_sTestParents[extra][E_INI14_TEST_SECOND_KEY]);
	INI_Int("c", YSI_g_sTestParents[extra][E_INI14_TEST_C]);
	INI_Float("third_key", YSI_g_sTestParents[extra][E_INI14_TEST_THIRD_KEY]);
	INI_String("fourth_key", YSI_g_sTestParents[extra][E_INI14_TEST_FOURTH_KEY], 32);
	INI_Int("fifth_key", YSI_g_sTestParents[extra][E_INI14_TEST_FIFTH_KEY]);
	return 0;
}

@test(.group = "y_ini") INI_Parents()
{
	INI_ParseFile(
			MakeYINITestPath("test7.ini"),
			"INI_Parents",
			.bExtra    = true,
			.extra     = 3,
			.bPassTag  = true,
			.bPassFile = true);
	// Parent.
	ASSERT_SAME(YSI_g_sTestParents[0][E_INI14_TEST_FIRST_KEY], "how are you?");
	ASSERT_SAME(YSI_g_sTestParents[0][E_INI14_TEST_FOURTH_KEY], "Some string....");
	ASSERT_EQ(YSI_g_sTestParents[0][E_INI14_TEST_SECOND_KEY], 11);
	ASSERT_EQ(YSI_g_sTestParents[0][E_INI14_TEST_C         ], 8);
	ASSERT_EQ(YSI_g_sTestParents[0][E_INI14_TEST_THIRD_KEY ], 0.0);
	ASSERT_EQ(YSI_g_sTestParents[0][E_INI14_TEST_FIFTH_KEY ], 99);
	// Child.
	ASSERT_SAME(YSI_g_sTestParents[1][E_INI14_TEST_FIRST_KEY], "how are you?");
	ASSERT_SAME(YSI_g_sTestParents[1][E_INI14_TEST_FOURTH_KEY], "Some other string....");
	ASSERT_EQ(YSI_g_sTestParents[1][E_INI14_TEST_SECOND_KEY], 11);
	ASSERT_EQ(YSI_g_sTestParents[1][E_INI14_TEST_C         ], 9);
	ASSERT_EQ(YSI_g_sTestParents[1][E_INI14_TEST_THIRD_KEY ], 6.6);
	ASSERT_EQ(YSI_g_sTestParents[1][E_INI14_TEST_FIFTH_KEY ], 99);
	// Grandchild.
	ASSERT_SAME(YSI_g_sTestParents[2][E_INI14_TEST_FIRST_KEY], "how are you?");
	ASSERT_SAME(YSI_g_sTestParents[2][E_INI14_TEST_FOURTH_KEY], "Some other string....");
	ASSERT_EQ(YSI_g_sTestParents[2][E_INI14_TEST_SECOND_KEY], 12);
	ASSERT_EQ(YSI_g_sTestParents[2][E_INI14_TEST_C         ], 10);
	ASSERT_EQ(YSI_g_sTestParents[2][E_INI14_TEST_THIRD_KEY ], 6.6);
	ASSERT_EQ(YSI_g_sTestParents[2][E_INI14_TEST_FIFTH_KEY ], 99);
	// Overflow.
	ASSERT(!YSI_g_sTestParents[3][E_INI14_TEST_FIRST_KEY][0]);
	ASSERT(!YSI_g_sTestParents[3][E_INI14_TEST_FOURTH_KEY][0]);
	ASSERT_ZE(YSI_g_sTestParents[3][E_INI14_TEST_SECOND_KEY]);
	ASSERT_ZE(YSI_g_sTestParents[3][E_INI14_TEST_C         ]);
	ASSERT_EQ(YSI_g_sTestParents[3][E_INI14_TEST_THIRD_KEY ], 0.0);
	ASSERT_ZE(YSI_g_sTestParents[3][E_INI14_TEST_FIFTH_KEY ]);
}

//static
//	YSI_g_sINIBinaryData[3][60 char],
//	YSI_g_sStringData[32];
//
//forward INI_BinaryData(name[], value[]);
//
//public INI_BinaryData(name[], value[])
//{
//	INI_Array("BINARY_DATA_1", YSI_g_sINIBinaryData[0]);
//	INI_Array("BINARY_DATA_2", YSI_g_sINIBinaryData[1]);
//	INI_Array("BINARY_DATA_3", YSI_g_sINIBinaryData[2]);
//	INI_Int("INT_DATA", YSI_g_sINI_Parse0);
//	INI_String("STRING_DATA", YSI_g_sStringData);
//	return 0;
//}
//
//@test(.group = "y_ini") INI_BinaryData()
//{
//	INI_ParseFile(
//			MakeYINITestPath("test8.ini"),
//			"INI_BinaryData",
//			.bExtra    = false,
//			.bPassTag  = false,
//			.bPassFile = false);
//	static
//		l_ResultData[3][60 char] = {
//			{ 0xFF0000AA, 0x67452301, 0x01234567, 0x48000000, 0x9CE0F932, 0xAD8193B8, 0xD7B99AE0, 0x10653129, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x004223BB },
//			{ 0xFF0000AA, 0x67452301, 0x01234567, 0x48000000, 0x9CE0F932, 0xAD8193B8, 0xD7B99AE0, 0x10653129, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0xBB999999, 0x00004223, 0x00000000 },
//			{ 0xFF0000AA, 0x67452301, 0x01234567, 0x48000000, 0x9CE0F932, 0xAD8193B8, 0xD7B99AE0, 0x10653129, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x004223BB, 0x00000000 }
//	};
//	ASSERT_EQ(YSI_g_sINI_Parse0, 888777);
//	ASSERT_SAME(YSI_g_sStringData, "Hello");
//	for (new i = 0; i != sizeof (YSI_g_sINIBinaryData[]); ++i)
//	{
//		ASSERT_EQ(YSI_g_sINIBinaryData[0][i], l_ResultData[0][i]);
//		ASSERT_EQ(YSI_g_sINIBinaryData[1][i], l_ResultData[1][i]);
//		ASSERT_EQ(YSI_g_sINIBinaryData[2][i], l_ResultData[2][i]);
//	}
//}

