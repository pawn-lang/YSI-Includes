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

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 239
#endif

TEST__ INI_IdentifyLineType1()
{
	// Comment lines and blank lines may as well be treated as the same thing,
	// except when rewriting the file.
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Comment lines.
	ASSERT_EQ(INI_IdentifyLineType("; Hello", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType("   ; There", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType("	; Hi", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType(";", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType(";\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_NE(INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_NE(INI_IdentifyLineType("hi ; there", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	// Blank lines.
	ASSERT_EQ(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType("    ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType("	\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
	ASSERT_EQ(INI_IdentifyLineType("\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_DATALESS);
}

TEST__ INI_IdentifyLineType2()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Invalid lines.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("[badtag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [tag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [   ]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag\\;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_NE(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_NE(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\=", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\\\\\=value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key =  ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_ENTRY); // Now allowed again!
	result = INI_IdentifyLineType(" = value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing ; comment", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_EQ(result, e_INI_LINE_TYPE_INVALID);
}

TEST__ INI_IdentifyLineType3()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Entry lines.
	ASSERT_EQ(INI_IdentifyLineType("key = value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("key=value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 4 && p1e == 9 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("key = value ; comment", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 14 && p2e == 21);
	ASSERT_EQ(INI_IdentifyLineType("key = value ;   comment\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 16 && p2e == 23);
	ASSERT_EQ(INI_IdentifyLineType("key =  value   ; com ment  \r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 7 && p1e == 12 && p2s == 17 && p2e == 25);
	ASSERT_EQ(INI_IdentifyLineType("key = value\r\n", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("key	=value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 5 && p1e == 10 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("   key=	value", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("   key=	value    ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("	key   =value  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 1 && p0e == 4 && p1s == 8 && p1e == 13 && p2s == p2e);
}

TEST__ INI_IdentifyLineType4()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Tag lines.
	ASSERT_EQ(INI_IdentifyLineType("[hello]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType(" [hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType(" [ hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType(" [hello ] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[ hello] ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[hello ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[hello   ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[   hello ]", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 4 && p0e == 9 && p1s == p1e && p2s == p2e);
}

TEST__ INI_IdentifyLineType5()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Inheritance.
	ASSERT_EQ(INI_IdentifyLineType("[hello] : ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[hello] : first", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 15 && p2s == p2e);
	// ASSERT_EQ(INI_IdentifyLineType("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	// ASSERT_EQ(INI_IdentifyLineType("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	// ASSERT_EQ(INI_IdentifyLineType("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// These used to work, now they don't.
	ASSERT_EQ(INI_IdentifyLineType("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	ASSERT_EQ(INI_IdentifyLineType("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// Commented out.
	ASSERT_EQ(INI_IdentifyLineType("[hello] ;: ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 9 && p2e == 10);
	ASSERT_EQ(INI_IdentifyLineType("[hello] ; : first, second ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 10 && p2e == 25);
	// Both.
	ASSERT_EQ(INI_IdentifyLineType(" [ hello ]  :  inheritance  ;  : first, second ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == 15 && p1e == 26 && p2s == 31 && p2e == 46);
}

TEST__ INI_IdentifyLineType6a()
{
	state y_ini:y_ini_writing_fast;
	new p0s, p0e, p1s, p1e, p2s, p2e;
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
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\;  Hello  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
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
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 0);
	ASSERT(p1s == 0 && p1e == 10);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
}

TEST__ INI_IdentifyLineType6b()
{
	state y_ini:y_ini_reading_yyyn;
	new p0s, p0e, p1s, p1e, p2s, p2e;
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
	ASSERT_EQ(INI_IdentifyLineType("hi =    \\;  Hello  ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
#if defined Y_INI_NO_ESCAPES
	ASSERT(p1s == 8 && p1e == 17);
#else
	ASSERT(p1s == 8 && p1e == 16);
#endif
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
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 0);
	ASSERT(p1s == 0 && p1e == 10);
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
	ASSERT_EQ(INI_IdentifyLineType("hi = hello     ", p0s, p0e, p1s, p1e, p2s, p2e), e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == 5 && p1e == 10);
}

TEST__ INI_Continuation()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	INI_IdentifyLineType("hi = hello \\\r\n", p0s, p0e, p1s, p1e, p2s, p2e);
	INI_IdentifyLineType("world = the \\ ; Ignore me", p0s, p0e, p1s, p1e, p2s, p2e);
	INI_IdentifyLineType("\\ whole string     ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT_SAME(mget(YSI_g_sExtendedLine, 1), "hello world = the \\ whole string");
	// Cleanup.
	YSI_g_sExtendedName[0] = '\0', free(YSI_g_sExtendedLine), YSI_g_sExtendedLine = NO_ALLOC;
}

#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

TEST__ Trim1()
{
	new start, end;
	start = 0, end = 9;
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
	YSI_g_sINI_Parse0;

forward TestINI_Parse0_test1(key[], value[]);

public TestINI_Parse0_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

TEST__ INI_Parse0()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	if (IsWindows())
	{
		YSI_g_sINI_Parse0 = 0;
		INI_ParseFile("YSI\\test_ini\\test1.ini", "TestINI_Parse0_%s", .bFileFirst = true);
		ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	}
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "unf");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true); //, .bFilter = false, .filter = "unf");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = true); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = false); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

forward TestINI_Parse1_test1_(key[], value[]);

public TestINI_Parse1_test1_(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

TEST__ INI_Parse1()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse1_%s_%s", .bFileFirst = true);
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

TEST__ INI_Parse2()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse2_%s_%s", .bFileFirst = true);
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

TEST__ INI_Parse3()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false); //, .bFilter = false, .filter = "filter");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false); //, .bFilter = false, .filter = "other");
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

TEST__ INI_Parse4()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false/*, .bFilter = false, .filter = "filter"*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false/*, .bFilter = false, .filter = "other"*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

// Test passing the tag.

forward TestINI_Parse5_test1(tag[], key[], value[]);

public TestINI_Parse5_test1(tag[], key[], value[])
{
	printf("%s, %s, %s", tag, key, value);
	if (isnull(tag)) ++YSI_g_sINI_Parse0;
}

TEST__ INI_Parse5()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other");
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s%s", .bFileFirst = true, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_%sParse5_%s", .bFileFirst = false, .bPassTag = true);//, .bFilter = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

TEST__ INI_Parse6()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
//	YSI_g_sINI_Parse0 = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other", .bLocal = false);
//	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true/*, .bFilter = false*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true/*, .bFilter = false*/, .bLocal = false);
	ASSERT_EQ(YSI_g_sINI_Parse0, 5);
}

TEST__ INI_Parse7()
{
	inline const F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 1;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 10);
}

TEST__ INI_Parse8()
{
	inline F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 2;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s", .bFileFirst = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 20);
}

TEST__ INI_Parse9()
{
	inline const F_atag_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 3;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT_EQ(YSI_g_sINI_Parse0, 9);
}

TEST__ INI_Parse10()
{
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 4;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT_EQ(YSI_g_sINI_Parse0, 8);
}

TEST__ INI_Parse11()
{
	new
		a;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT_EQ(a, 0);
}

TEST__ INI_Parse12()
{
	static
		a;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT_EQ(a, 8);
}

TEST__ INI_Parse13()
{
	new
		a;
	inline F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT_EQ(a, 8);
}

TEST__ INI_ParseInline()
{
	new
		num,
		ret;
	inline Inline1(string:key[], string:value[])
	{
		#pragma unused key, value
		++num;
	}
//	num = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "Inline1", .bFilter = true, .filter = "other");
//	ASSERT_EQ(num, 8);
//	// This line also seems to have the -O1 -d0 bug.  It must be caused by the
//	// extra "tag" parameter somehow...
//	inline Inline2(string:tag[], string:key[], string:value[])
//	{
//		#pragma unused key, value
//		if (isnull(tag)) ++num;
//	}
//	num = 0;
//	INI_ParseFile("YSI/test_ini/test1.ini", "Inline2", .bFilter = true, .filter = "other", .bPassTag = true);
//	ASSERT_EQ(num, 5);
	inline Inline3(extra, string:key[], string:value[])
	{
		#pragma unused key, value
		num += extra;
	}
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline3%s", .bExtra = true, .extra = 11);
	ASSERT_EQ(num, 55);
	inline Inline4(extra, string:tag[], string:key[], string:value[])
	{
		#pragma unused key, value
		ret = extra;
		if (!isnull(tag) && !strcmp(tag, "tag2")) ++num;
	}
	ret = 0;
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline4", .bPassTag = true, .bExtra = true, .extra = 42);
	ASSERT_EQ(num, 2);
	ASSERT_EQ(ret, 42);
}

TEST__ INI_Int0()
{
	DoINI_Int0();
}

static stock DoINI_Int0()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	inline Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_%s");
	ASSERT_EQ(k0, 42);
	ASSERT_EQ(k1, 43);
	ASSERT_EQ(k2, 45);
	ASSERT_EQ(k3, 47);
	ASSERT_EQ(k4, 46);
	return 0;
}

TEST__ INI_Int2()
{
	DoINI_Int2();
}

static stock DoINI_Int2()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	inline const Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_%s");
	ASSERT_ZE(k0);
	ASSERT_ZE(k1);
	ASSERT_ZE(k2);
	ASSERT_ZE(k3);
	ASSERT_ZE(k4);
	return 0;
}

TEST__ INI_Int3()
{
	DoINI_Int3();
}

static stock DoINI_Int3()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	new
		sk0[8],
		Float:sk1,
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
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_", .bPassTag = true);
	// First.
	ASSERT_EQ(k0, 42);
	ASSERT_EQ(k1, 43);
	ASSERT_EQ(k2, 45);
	ASSERT_EQ(k3, 47);
	ASSERT_EQ(k4, 46);
	// Second.
	ASSERT(!isnull(sk0) && !strcmp(sk0, "hello"));
	ASSERT_EQ(sk1, 5.5);
	ASSERT(!sk2);
	// Third.
	ASSERT(!isnull(tk0) && !strcmp(tk0, "yes"));
	ASSERT(!isnull(tk1) && !strcmp(tk1, "no"));
	return 0;
}

static stock
	gs_K0,
	gs_K1,
	gs_K2,
	gs_K3,
	gs_K4,
	gs_K5;

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

TEST__ INI_Int1()
{
	INI_ParseFile("YSI/test_ini/test1.ini", "INI_PUB_Inl_%s");
	ASSERT_EQ(gs_K0, 42);
	ASSERT_EQ(gs_K1, 43);
	ASSERT_EQ(gs_K2, 45);
	ASSERT_EQ(gs_K3, 47);
	ASSERT_EQ(gs_K4, 46);
}

TEST__ INI_WriteComments()
{
	new INI:i = INI_Open("YSI/test_ini/test10.ini");
	INI_SetTag(i, "tag_with_parent");
	INI_RemoveEntry(i, "value");
	INI_Close(i);
}

TEST_CLOSE__ INI_WriteComments()
{
	new INI:i = INI_Open("YSI/test_ini/test10.ini");
	INI_SetTag(i, "tag_with_parent");
	INI_WriteInt(i, "value", 5);
	INI_WriteString(i, "value_three", "Some;semi;colons");
	INI_WriteString(i, "value_four", "Some_semi_colons");
	INI_Close(i);
}

forward INI_Inher0_tag0(string:tag[], string:name[], string:value[]);

public INI_Inher0_tag0(string:tag[], string:name[], string:value[])
{
	ASSERT(!isnull(tag) && !strcmp(tag, "tag0"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

TEST__ INI_Inherit0()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher0_%s", .bPassTag = true);
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
	ASSERT(!isnull(tag) && !strcmp(tag, "tag1"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

TEST__ INI_Inherit1()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher1_%s", .bPassTag = true);
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
	ASSERT(!isnull(tag) && !strcmp(tag, "tag2"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

TEST__ INI_Inherit2()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher2_%s", .bPassTag = true);
	ASSERT_EQ(gs_K0, 107);
	ASSERT_EQ(gs_K1, 102);
	ASSERT_EQ(gs_K2, 103);
	ASSERT_EQ(gs_K3, 104);
	ASSERT_EQ(gs_K4, 105);
	ASSERT_EQ(gs_K5, 106);
}

// Writing tests.

TEST__ INI_AddToBuffer0()
{
	new
		INI:i = INI_Open("YSI/test_ini/test3.ini");
	ASSERT_NE(i, INI_NO_FILE);
	ASSERT(!INI_AddToBuffer(i, "", "hi"));
	ASSERT(!INI_AddToBuffer(INI_NO_FILE, "foo", "bar"));
	ASSERT(INI_AddToBuffer(i, "key", "value"));
	ASSERT(INI_AddToBuffer(i, "first", "second"));
	ASSERT(INI_AddToBuffer(i, "first", "third"));
	ASSERT(INI_AddToBuffer(i, "first", "fourth"));
	ASSERT(INI_AddToBuffer(i, "first", "fifth"));
	INI_Close(i);
}

TEST__ INI_AddToBuffer1()
{
	new
		INI:i = INI_Open("YSI/test_ini/test4.ini");
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

TEST__ INI_Write3()
{
	fremove("YSI/test_ini/test9.ini");
	new
		INI:i = INI_Open("YSI/test_ini/test9.ini");
	ASSERT_NE(i, INI_NO_FILE);
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
	INI_ParseFile("YSI/test_ini/test9.ini", "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 42 + 40 + 43 + 44 + 3);
	i = INI_Open("YSI/test_ini/test9.ini");
	INI_SetTag(i, "tag");
	INI_WriteString(i, "another", "200");
	INI_WriteInt(i, "you", 200);
	INI_Close(i);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test9.ini", "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 200 + 200 + 40 + 43 + 44 + 3);
	i = INI_Open("YSI/test_ini/test9.ini");
	INI_SetTag(i, "tag");
	INI_RemoveEntry(i, "another");
	INI_Close(i);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test9.ini", "INI_WriteOne", .bPassTag = true);
	ASSERT_EQ(YSI_g_sINI_Parse0, 100 + 200 + 40 + 43 + 44 + 3);
}

//TEST__ INI_VariousWriting0()
//{
//	new
//		INI:i = INI_Open("YSI/test_ini/test5.ini");
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
//TEST__ INI_VariousWriting1()
//{
//	new
//		INI:f = INI_Open("YSI/test_ini/test5.ini"),
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

TEST__ INI_Write0()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini"),
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

TEST__ INI_Write1()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini"),
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

TEST__ INI_Write2()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini");
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

TEST__ INI_Parents()
{
	INI_ParseFile(
			"YSI/test_ini/test7.ini",
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
//TEST__ INI_BinaryData()
//{
//	INI_ParseFile(
//			"YSI/test_ini/test8.ini",
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

