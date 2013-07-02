/**--------------------------------------------------------------------------**\
  				===================================
					 y_punycode - Character encodings.
					===================================
Description:
	Functions for converting unicode strings to and from punycode, to be
	represented in just ASCII characters.  Based on several public
	implementations and the RFC, adapted for PAWN.  For more information see:
	
	https://en.wikipedia.org/wiki/Punycode
	
	Also includes a function that hooks the "HTTP" function to allow for
	internationalised domain names with that function.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI punycode include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.1
Changelog:
	29/04/13:
		Added Puny_HTTP.
	26/04/13:
		First version.
Functions:
	Public
		-
	Core:
		-
	Stock:
		Puny_Encode - Convert a Unicode string to Punycode.
		Puny_Decode - Convert a Punycode string to Unicode.
		Puny_HTTP - Wrapper for "HTTP" to encode domain names.
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

Test:y_punycode_1()
{
	new
		dst[32];
	Puny_Encode(dst, "b�cher");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
	Puny_Encode(dst, "b��cher");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kvaa"));
	Puny_Encode(dst, "b�c�her");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kvab"));
	Puny_Encode(dst, "b�cher�");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kvae"));
	Puny_Encode(dst, "�b�cher");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kvaf"));
	Puny_Encode(dst, "�b�cher");
	P:1("Test:y_punycode_1: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-jvab"));
}

Test:y_punycode_2()
{
	new
		dst[32],
		hash;
	Puny_EncodeHash(dst, "b�cher", hash);
	P:1("Test:y_punycode_2: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
	Puny_EncodeHash(dst, "b�CHer", hash);
	P:1("Test:y_punycode_2: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
	Puny_EncodeHash(dst, "B�cHeR", hash);
	P:1("Test:y_punycode_2: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
	Puny_EncodeHash(dst, "b�cHER", hash);
	P:1("Test:y_punycode_2: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
	Puny_EncodeHash(dst, "b�cher", hash);
	P:1("Test:y_punycode_2: dst = %s", dst);
	ASSERT(!strcmp(dst, "bcher-kva"));
}

/*
These all work in UTF-8, but can't be compiled in ANSI.

xn--mgbh0fb.xn--kgbechtv 	http://مثال.إختبار 	Arabic 	Arabic
xn--fsqu00a.xn--0zwm56d 	http://例子.测试 	Simplified Chinese 	Chinese
xn--fsqu00a.xn--g6w251d 	http://例子.測試 	Traditional Chinese 	Chinese
xn--hxajbheg2az3al.xn--jxalpdlp 	http://παράδειγμα.δοκιμή 	Greek 	Greek
xn--p1b6ci4b4b3a.xn--11b5bs3a9aj6g 	http://उदाहरण.परीक्षा 	Devanagari 	Hindi
xn--r8jz45g.xn--zckzah 	http://例え.テスト 	Kanji+Kana 	Japanese
xn--9n2bp8q.xn--9t4b11yi5a 	http://실례.테스트 	Hangul 	Korean
xn--mgbh0fb.xn--hgbk6aj7f53bba 	http://مثال.آزمایشی 	Perso-Arabic 	Persian
xn--e1afmkfd.xn--80akhbyknj4f 	http://пример.испытание 	Cyrillic 	Russian
xn--zkc6cc5bi7f6e.xn--hlcj6aya9esc7a 	http://உதாரணம்.பரிட்சை 	Tamil 	Tamil
xn--6dbbec0c.xn--deba0ad 	http://דוגמה.טעסט 	Hebrew 	Hebrew
xn--fdbk5d8ap9b8a8d.xn--deba0ad 	http://בײַשפּיל.טעסט 	Hebrew 	Yiddish
*/
