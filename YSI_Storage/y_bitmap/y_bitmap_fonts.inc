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

static stock const
	/*YSI_g_scAlphabet[10][26 + 1 + 10 + 1 char] =
	{
		// A     B     C     D     E     F     G     H     I     J     K     L     M     N     O     P     Q     R     S     T     U     V     W     X     Y     Z           0     1     2     3     4     5     6     7     8     9     ~     '     -
		{0x30, 0xFC, 0x3C, 0xF8, 0xFE, 0xFE, 0x3C, 0xCC, 0x78, 0x1E, 0xE6, 0xF0, 0xC6, 0xC6, 0x38, 0xFC, 0x38, 0xFC, 0x78, 0xFC, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0xFE, 0x00, 0x7C, 0x10, 0x78, 0x78, 0x0C, 0xFC, 0x38, 0xFE, 0x78, 0x78, 0x73, 0x30, 0x00},
		{0x78, 0x66, 0x66, 0x6C, 0x62, 0x66, 0x66, 0xCC, 0x30, 0x0C, 0x66, 0x60, 0xEE, 0xC6, 0x6C, 0x66, 0x6C, 0x66, 0xCC, 0xB4, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0xCE, 0x00, 0xC6, 0x30, 0xCC, 0xCC, 0x1C, 0xC0, 0x60, 0xC6, 0xCC, 0xCC, 0xDA, 0x30, 0x00},
		{0xCC, 0x66, 0xC6, 0x66, 0x60, 0x62, 0xC6, 0xCC, 0x30, 0x0C, 0x6C, 0x60, 0xFE, 0xE6, 0xC6, 0x66, 0xC6, 0x66, 0xCC, 0x30, 0xCC, 0xCC, 0xC6, 0xCC, 0xCC, 0x98, 0x00, 0xCE, 0xF0, 0xCC, 0x0C, 0x3C, 0xC0, 0xC0, 0xC6, 0xCC, 0xCC, 0xCE, 0x30, 0x00},
		{0xCC, 0x66, 0xC0, 0x66, 0x64, 0x64, 0xC0, 0xCC, 0x30, 0x0C, 0x6C, 0x60, 0xFE, 0xF6, 0xC6, 0x66, 0xC6, 0x66, 0xC0, 0x30, 0xCC, 0xCC, 0xC6, 0x78, 0xCC, 0x18, 0x00, 0xDE, 0x30, 0x0C, 0x0C, 0x6C, 0xC0, 0xC0, 0x06, 0xCC, 0xCC, 0x00, 0x60, 0x00},
		{0xCC, 0x7C, 0xC0, 0x66, 0x7C, 0x7C, 0xC0, 0xFC, 0x30, 0x0C, 0x78, 0x60, 0xD6, 0xFE, 0xC6, 0x7C, 0xC6, 0x7C, 0x70, 0x30, 0xCC, 0xCC, 0xD6, 0x30, 0x78, 0x30, 0x00, 0xD6, 0x30, 0x18, 0x38, 0xCC, 0xF8, 0xF8, 0x0C, 0x78, 0x7C, 0x00, 0x00, 0xFE},
		{0xFC, 0x66, 0xC0, 0x66, 0x64, 0x64, 0xCE, 0xCC, 0x30, 0xCC, 0x6C, 0x62, 0xC6, 0xDE, 0xC6, 0x60, 0xCE, 0x6C, 0x18, 0x30, 0xCC, 0xCC, 0xD6, 0x78, 0x30, 0x60, 0x00, 0xF6, 0x30, 0x30, 0x0C, 0xFE, 0x0C, 0xCC, 0x18, 0xCC, 0x18, 0x00, 0x00, 0x00},
		{0xCC, 0x66, 0xC6, 0x66, 0x60, 0x60, 0xC6, 0xCC, 0x30, 0xCC, 0x6C, 0x66, 0xC6, 0xCE, 0xC6, 0x60, 0xDE, 0x66, 0xCC, 0x30, 0xCC, 0xCC, 0x6C, 0xCC, 0x30, 0x62, 0x00, 0xE6, 0x30, 0x60, 0x0C, 0x0C, 0x0C, 0xCC, 0x30, 0xCC, 0x18, 0x00, 0x00, 0x00},
		{0xCC, 0x66, 0x66, 0x6C, 0x62, 0x60, 0x66, 0xCC, 0x30, 0xCC, 0x66, 0x66, 0xC6, 0xC6, 0x6C, 0x60, 0x7C, 0x66, 0xCC, 0x30, 0xCC, 0x78, 0x6C, 0xCC, 0x30, 0xC6, 0x00, 0xC6, 0x30, 0xCC, 0xCC, 0x0C, 0xCC, 0xCC, 0x30, 0xCC, 0x30, 0x00, 0x00, 0x00},
		{0xCC, 0xFC, 0x3C, 0xF8, 0xFE, 0xF0, 0x3E, 0xCC, 0x78, 0x78, 0xE6, 0xFE, 0xC6, 0xC6, 0x38, 0xF0, 0x0C, 0xE6, 0x78, 0x78, 0x78, 0x30, 0x6C, 0xCC, 0x78, 0xFE, 0x00, 0x7C, 0xFC, 0xFC, 0x78, 0x1E, 0x78, 0x78, 0x30, 0x78, 0x70, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};*/
	// This data is stored bottom to top, so the last character (the implicit
	// NULL is the top row of the character).  This is as the NULL is required
	// to not be written and the top row is the only one that is always empty.
	YSI_g_scAlphabet[128][12 char] =
	{
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x00
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x01
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x02
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x03
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x04
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x05
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x06
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x07
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x08
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x09
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0A
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0B
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0C
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0D
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0E
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x0F
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x10
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x11
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x12
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x13
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x14
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x15
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x16
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x17
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x18
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x19
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1A
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1B
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1C
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1D
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1E
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // 0x1F
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", //  
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // !
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // "
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // #
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // $
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // %
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // &
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x60;\x30;\x30;\x30;", // '
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // (
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // )
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // *
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // +
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // ,
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\xFE;\x00;\x00;\x00;\x00;", // -
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // .
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // /
		__COMPILER_PACK"\x00;\x00;\x7C;\xC6;\xE6;\xF6;\xD6;\xDE;\xCE;\xC6;\x7C;", // 0
		__COMPILER_PACK"\x00;\x00;\xFC;\x30;\x30;\x30;\x30;\x30;\xF0;\x30;\x10;", // 1
		__COMPILER_PACK"\x00;\x00;\xFC;\xCC;\x60;\x30;\x18;\x0C;\xCC;\xCC;\x78;", // 2
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\x0C;\x0C;\x38;\x0C;\x0C;\xCC;\x78;", // 3
		__COMPILER_PACK"\x00;\x00;\x1E;\x0C;\x0C;\xFE;\xCC;\x6C;\x3C;\x1C;\x0C;", // 4
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\x0C;\x0C;\xF8;\xC0;\xC0;\xC0;\xFC;", // 5
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\xCC;\xF8;\xC0;\xC0;\x60;\x38;", // 6
		__COMPILER_PACK"\x00;\x00;\x30;\x30;\x30;\x18;\x0C;\x06;\xC6;\xC6;\xFE;", // 7
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\xCC;\x78;\xCC;\xCC;\xCC;\x78;", // 8
		__COMPILER_PACK"\x00;\x00;\x70;\x30;\x18;\x18;\x7C;\xCC;\xCC;\xCC;\x78;", // 9
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // :
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // ;
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // <
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // =
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // >
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // ?
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // @
		__COMPILER_PACK"\x00;\x00;\xCC;\xCC;\xCC;\xFC;\xCC;\xCC;\xCC;\x78;\x30;", // A
		__COMPILER_PACK"\x00;\x00;\xFC;\x66;\x66;\x66;\x7C;\x66;\x66;\x66;\xFC;", // B
		__COMPILER_PACK"\x00;\x00;\x3C;\x66;\xC6;\xC0;\xC0;\xC0;\xC6;\x66;\x3C;", // C
		__COMPILER_PACK"\x00;\x00;\xF8;\x6C;\x66;\x66;\x66;\x66;\x66;\x6C;\xF8;", // D
		__COMPILER_PACK"\x00;\x00;\xFE;\x62;\x60;\x64;\x7C;\x64;\x60;\x62;\xFE;", // E
		__COMPILER_PACK"\x00;\x00;\xF0;\x60;\x60;\x64;\x7C;\x64;\x62;\x66;\xFE;", // F
		__COMPILER_PACK"\x00;\x00;\x3E;\x66;\xC6;\xCE;\xC0;\xC0;\xC6;\x66;\x3C;", // G
		__COMPILER_PACK"\x00;\x00;\xCC;\xCC;\xCC;\xCC;\xFC;\xCC;\xCC;\xCC;\xCC;", // H
		__COMPILER_PACK"\x00;\x00;\x78;\x30;\x30;\x30;\x30;\x30;\x30;\x30;\x78;", // I
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\xCC;\x0C;\x0C;\x0C;\x0C;\x1E;", // J
		__COMPILER_PACK"\x00;\x00;\xE6;\x66;\x6C;\x6C;\x78;\x6C;\x6C;\x66;\xE6;", // K
		__COMPILER_PACK"\x00;\x00;\xFE;\x66;\x66;\x62;\x60;\x60;\x60;\x60;\xF0;", // L
		__COMPILER_PACK"\x00;\x00;\xC6;\xC6;\xC6;\xC6;\xD6;\xFE;\xFE;\xEE;\xC6;", // M
		__COMPILER_PACK"\x00;\x00;\xC6;\xC6;\xCE;\xDE;\xFE;\xF6;\xE6;\xC6;\xC6;", // N
		__COMPILER_PACK"\x00;\x00;\x38;\x6C;\xC6;\xC6;\xC6;\xC6;\xC6;\x6C;\x38;", // O
		__COMPILER_PACK"\x00;\x00;\xF0;\x60;\x60;\x60;\x7C;\x66;\x66;\x66;\xFC;", // P
		__COMPILER_PACK"\x00;\x1E;\x0C;\x7C;\xDE;\xCE;\xC6;\xC6;\xC6;\x6C;\x38;", // Q
		__COMPILER_PACK"\x00;\x00;\xE6;\x66;\x66;\x6C;\x7C;\x66;\x66;\x66;\xFC;", // R
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\x18;\x70;\xC0;\xCC;\xCC;\x78;", // S
		__COMPILER_PACK"\x00;\x00;\x78;\x30;\x30;\x30;\x30;\x30;\x30;\xB4;\xFC;", // T
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\xCC;\xCC;\xCC;\xCC;\xCC;\xCC;", // U
		__COMPILER_PACK"\x00;\x00;\x30;\x78;\xCC;\xCC;\xCC;\xCC;\xCC;\xCC;\xCC;", // V
		__COMPILER_PACK"\x00;\x00;\x6C;\x6C;\x6C;\xD6;\xD6;\xC6;\xC6;\xC6;\xC6;", // W
		__COMPILER_PACK"\x00;\x00;\xCC;\xCC;\xCC;\x78;\x30;\x78;\xCC;\xCC;\xCC;", // X
		__COMPILER_PACK"\x00;\x00;\x78;\x30;\x30;\x30;\x78;\xCC;\xCC;\xCC;\xCC;", // Y
		__COMPILER_PACK"\x00;\x00;\xFE;\xC6;\x62;\x60;\x30;\x18;\x98;\xCE;\xFE;", // Z
		__COMPILER_PACK"\x00;\x00;\x3C;\x30;\x30;\x30;\x30;\x30;\x30;\x30;\x3C;", // [
		__COMPILER_PACK"\x00;\x00;\x02;\x06;\x0C;\x18;\x30;\x60;\xC0;\x80;\x00;", // <backslash>
		__COMPILER_PACK"\x00;\x00;\x3C;\x0C;\x0C;\x0C;\x0C;\x0C;\x0C;\x0C;\x3C;", // ]
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\xC6;\x6C;\x38;\x10;", // ^
		__COMPILER_PACK"\x00;\xFF;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;", // _
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x18;\x30;\x30;", // `
		__COMPILER_PACK"\x00;\x00;\x76;\xCC;\xCC;\x7C;\x0C;\x78;\x00;\x00;\x00;", // a
		__COMPILER_PACK"\x00;\x00;\xDC;\x66;\x66;\x66;\x66;\x7C;\x60;\x60;\xE0;", // b
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xC0;\xC0;\xCC;\x78;\x00;\x00;\x00;", // c
		__COMPILER_PACK"\x00;\x00;\x76;\xCC;\xCC;\xCC;\xCC;\x7C;\x0C;\x0C;\x1C;", // d
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xC0;\xFC;\xCC;\x78;\x00;\x00;\x00;", // e
		__COMPILER_PACK"\x00;\x00;\xF0;\x60;\x60;\x60;\xF8;\x60;\x60;\x6C;\x38;", // f
		__COMPILER_PACK"\x78;\xCC;\x0C;\x7C;\xCC;\xCC;\xCC;\x76;\x00;\x00;\x00;", // g
		__COMPILER_PACK"\x00;\x00;\xE6;\x66;\x66;\x66;\x76;\x6C;\x60;\x60;\xE0;", // h
		__COMPILER_PACK"\x00;\x00;\x7E;\x18;\x18;\x18;\x18;\x78;\x00;\x18;\x18;", // i
		__COMPILER_PACK"\x78;\xCC;\xCC;\x0C;\x0C;\x0C;\x0C;\x3C;\x00;\x0C;\x0C;", // j
		__COMPILER_PACK"\x00;\x00;\xE6;\x66;\x6C;\x78;\x6C;\x66;\x60;\x60;\xE0;", // k
		__COMPILER_PACK"\x00;\x00;\x7E;\x18;\x18;\x18;\x18;\x18;\x18;\x18;\x78;", // l
		__COMPILER_PACK"\x00;\x00;\xC6;\xD6;\xD6;\xD6;\xD6;\xFC;\x00;\x00;\x00;", // m
		__COMPILER_PACK"\x00;\x00;\xCC;\xCC;\xCC;\xCC;\xCC;\xF8;\x00;\x00;\x00;", // n
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\xCC;\xCC;\xCC;\x78;\x00;\x00;\x00;", // o
		__COMPILER_PACK"\xF0;\x60;\x7C;\x66;\x66;\x66;\x66;\xDC;\x00;\x00;\x00;", // p
		__COMPILER_PACK"\x1E;\x0C;\x7C;\xCC;\xCC;\xCC;\xCC;\x76;\x00;\x00;\x00;", // q
		__COMPILER_PACK"\x00;\x00;\xF0;\x60;\x60;\x76;\x6E;\xE6;\x00;\x00;\x00;", // r
		__COMPILER_PACK"\x00;\x00;\x78;\xCC;\x18;\x60;\xCC;\x78;\x00;\x00;\x00;", // s
		__COMPILER_PACK"\x00;\x00;\x38;\x6C;\x60;\x60;\x60;\xFC;\x60;\x20;\x00;", // t
		__COMPILER_PACK"\x00;\x00;\x76;\xCC;\xCC;\xCC;\xCC;\xCC;\x00;\x00;\x00;", // u
		__COMPILER_PACK"\x00;\x00;\x30;\x78;\xCC;\xCC;\xCC;\xCC;\x00;\x00;\x00;", // v
		__COMPILER_PACK"\x00;\x00;\x6C;\x6C;\xD6;\xD6;\xC6;\xC6;\x00;\x00;\x00;", // w
		__COMPILER_PACK"\x00;\x00;\xC6;\x6C;\x38;\x38;\x6C;\xC6;\x00;\x00;\x00;", // x
		__COMPILER_PACK"\xF0;\x18;\x0C;\x7C;\x66;\x66;\x66;\x66;\x00;\x00;\x00;", // y
		__COMPILER_PACK"\x00;\x00;\xFC;\xC4;\x60;\x18;\x8C;\xFC;\x00;\x00;\x00;", // z
		__COMPILER_PACK"\x00;\x00;\x1C;\x30;\x30;\x60;\xC0;\x60;\x30;\x30;\x1C;", // {
		__COMPILER_PACK"\x00;\x00;\x18;\x18;\x18;\x18;\x00;\x18;\x18;\x18;\x18;", // |
		__COMPILER_PACK"\x00;\x00;\xE0;\x30;\x30;\x18;\x0C;\x18;\x30;\x30;\xE0;", // }
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\xCE;\xDA;\x73;", // ~
		__COMPILER_PACK"\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;\x00;"  // 0x7F
	};

stock Bitmap_AddSimpleLetter(Bitmap:ctx, colour, letter, &x, &y)
{
	letter &= 0x7F;
	y += 12;
	for (new j = 0; j != 12; ++j)
	{
		--y;
		new
			c = YSI_g_scAlphabet[letter]{j};
		for (new i = 0, k = 0x80; i != 8; ++i, k >>= 1)
		{
			if (c & k) Bitmap_WritePixel(ctx, x, y, colour);
			++x;
		}
		x -= 8;
	}
	x += 8;
}

stock Bitmap_AddSimpleString(Bitmap:ctx, colour, str[], &x, &y)
{
	for (new i = 0, ch = 0; (ch = str[i]); ++i)
	{
		Bitmap_AddSimpleLetter(ctx, colour, ch, x, y);
	}
}

