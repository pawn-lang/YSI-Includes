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

static stock const Y_UNIQUE_000_to_099_CALLED = cellmin;

#if defined _inc_y_unique__000_to_099
	#undef _inc_y_unique__000_to_099
#endif

#if UNIQUE_SYMBOL < 10
	#if UNIQUE_SYMBOL == 0
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (1)
		#define UNIQUE_FUNCTION<%0...%1> %0001%1
		#endinput
	#elseif UNIQUE_SYMBOL == 1
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (2)
		#define UNIQUE_FUNCTION<%0...%1> %0002%1
		#endinput
	#elseif UNIQUE_SYMBOL == 2
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (3)
		#define UNIQUE_FUNCTION<%0...%1> %0003%1
		#endinput
	#elseif UNIQUE_SYMBOL == 3
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (4)
		#define UNIQUE_FUNCTION<%0...%1> %0004%1
		#endinput
	#elseif UNIQUE_SYMBOL == 4
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (5)
		#define UNIQUE_FUNCTION<%0...%1> %0005%1
		#endinput
	#elseif UNIQUE_SYMBOL == 5
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (6)
		#define UNIQUE_FUNCTION<%0...%1> %0006%1
		#endinput
	#elseif UNIQUE_SYMBOL == 6
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (7)
		#define UNIQUE_FUNCTION<%0...%1> %0007%1
		#endinput
	#elseif UNIQUE_SYMBOL == 7
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (8)
		#define UNIQUE_FUNCTION<%0...%1> %0008%1
		#endinput
	#elseif UNIQUE_SYMBOL == 8
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (9)
		#define UNIQUE_FUNCTION<%0...%1> %0009%1
		#endinput
	#elseif UNIQUE_SYMBOL == 9
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (10)
		#define UNIQUE_FUNCTION<%0...%1> %0010%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 20
	#if UNIQUE_SYMBOL == 10
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (11)
		#define UNIQUE_FUNCTION<%0...%1> %0011%1
		#endinput
	#elseif UNIQUE_SYMBOL == 11
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (12)
		#define UNIQUE_FUNCTION<%0...%1> %0012%1
		#endinput
	#elseif UNIQUE_SYMBOL == 12
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (13)
		#define UNIQUE_FUNCTION<%0...%1> %0013%1
		#endinput
	#elseif UNIQUE_SYMBOL == 13
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (14)
		#define UNIQUE_FUNCTION<%0...%1> %0014%1
		#endinput
	#elseif UNIQUE_SYMBOL == 14
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (15)
		#define UNIQUE_FUNCTION<%0...%1> %0015%1
		#endinput
	#elseif UNIQUE_SYMBOL == 15
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (16)
		#define UNIQUE_FUNCTION<%0...%1> %0016%1
		#endinput
	#elseif UNIQUE_SYMBOL == 16
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (17)
		#define UNIQUE_FUNCTION<%0...%1> %0017%1
		#endinput
	#elseif UNIQUE_SYMBOL == 17
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (18)
		#define UNIQUE_FUNCTION<%0...%1> %0018%1
		#endinput
	#elseif UNIQUE_SYMBOL == 18
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (19)
		#define UNIQUE_FUNCTION<%0...%1> %0019%1
		#endinput
	#elseif UNIQUE_SYMBOL == 19
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (20)
		#define UNIQUE_FUNCTION<%0...%1> %0020%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 30
	#if UNIQUE_SYMBOL == 20
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (21)
		#define UNIQUE_FUNCTION<%0...%1> %0021%1
		#endinput
	#elseif UNIQUE_SYMBOL == 21
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (22)
		#define UNIQUE_FUNCTION<%0...%1> %0022%1
		#endinput
	#elseif UNIQUE_SYMBOL == 22
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (23)
		#define UNIQUE_FUNCTION<%0...%1> %0023%1
		#endinput
	#elseif UNIQUE_SYMBOL == 23
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (24)
		#define UNIQUE_FUNCTION<%0...%1> %0024%1
		#endinput
	#elseif UNIQUE_SYMBOL == 24
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (25)
		#define UNIQUE_FUNCTION<%0...%1> %0025%1
		#endinput
	#elseif UNIQUE_SYMBOL == 25
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (26)
		#define UNIQUE_FUNCTION<%0...%1> %0026%1
		#endinput
	#elseif UNIQUE_SYMBOL == 26
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (27)
		#define UNIQUE_FUNCTION<%0...%1> %0027%1
		#endinput
	#elseif UNIQUE_SYMBOL == 27
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (28)
		#define UNIQUE_FUNCTION<%0...%1> %0028%1
		#endinput
	#elseif UNIQUE_SYMBOL == 28
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (29)
		#define UNIQUE_FUNCTION<%0...%1> %0029%1
		#endinput
	#elseif UNIQUE_SYMBOL == 29
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (30)
		#define UNIQUE_FUNCTION<%0...%1> %0030%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 40
	#if UNIQUE_SYMBOL == 30
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (31)
		#define UNIQUE_FUNCTION<%0...%1> %0031%1
		#endinput
	#elseif UNIQUE_SYMBOL == 31
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (32)
		#define UNIQUE_FUNCTION<%0...%1> %0032%1
		#endinput
	#elseif UNIQUE_SYMBOL == 32
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (33)
		#define UNIQUE_FUNCTION<%0...%1> %0033%1
		#endinput
	#elseif UNIQUE_SYMBOL == 33
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (34)
		#define UNIQUE_FUNCTION<%0...%1> %0034%1
		#endinput
	#elseif UNIQUE_SYMBOL == 34
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (35)
		#define UNIQUE_FUNCTION<%0...%1> %0035%1
		#endinput
	#elseif UNIQUE_SYMBOL == 35
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (36)
		#define UNIQUE_FUNCTION<%0...%1> %0036%1
		#endinput
	#elseif UNIQUE_SYMBOL == 36
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (37)
		#define UNIQUE_FUNCTION<%0...%1> %0037%1
		#endinput
	#elseif UNIQUE_SYMBOL == 37
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (38)
		#define UNIQUE_FUNCTION<%0...%1> %0038%1
		#endinput
	#elseif UNIQUE_SYMBOL == 38
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (39)
		#define UNIQUE_FUNCTION<%0...%1> %0039%1
		#endinput
	#elseif UNIQUE_SYMBOL == 39
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (40)
		#define UNIQUE_FUNCTION<%0...%1> %0040%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 50
	#if UNIQUE_SYMBOL == 40
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (41)
		#define UNIQUE_FUNCTION<%0...%1> %0041%1
		#endinput
	#elseif UNIQUE_SYMBOL == 41
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (42)
		#define UNIQUE_FUNCTION<%0...%1> %0042%1
		#endinput
	#elseif UNIQUE_SYMBOL == 42
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (43)
		#define UNIQUE_FUNCTION<%0...%1> %0043%1
		#endinput
	#elseif UNIQUE_SYMBOL == 43
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (44)
		#define UNIQUE_FUNCTION<%0...%1> %0044%1
		#endinput
	#elseif UNIQUE_SYMBOL == 44
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (45)
		#define UNIQUE_FUNCTION<%0...%1> %0045%1
		#endinput
	#elseif UNIQUE_SYMBOL == 45
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (46)
		#define UNIQUE_FUNCTION<%0...%1> %0046%1
		#endinput
	#elseif UNIQUE_SYMBOL == 46
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (47)
		#define UNIQUE_FUNCTION<%0...%1> %0047%1
		#endinput
	#elseif UNIQUE_SYMBOL == 47
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (48)
		#define UNIQUE_FUNCTION<%0...%1> %0048%1
		#endinput
	#elseif UNIQUE_SYMBOL == 48
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (49)
		#define UNIQUE_FUNCTION<%0...%1> %0049%1
		#endinput
	#elseif UNIQUE_SYMBOL == 49
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (50)
		#define UNIQUE_FUNCTION<%0...%1> %0050%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 60
	#if UNIQUE_SYMBOL == 50
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (51)
		#define UNIQUE_FUNCTION<%0...%1> %0051%1
		#endinput
	#elseif UNIQUE_SYMBOL == 51
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (52)
		#define UNIQUE_FUNCTION<%0...%1> %0052%1
		#endinput
	#elseif UNIQUE_SYMBOL == 52
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (53)
		#define UNIQUE_FUNCTION<%0...%1> %0053%1
		#endinput
	#elseif UNIQUE_SYMBOL == 53
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (54)
		#define UNIQUE_FUNCTION<%0...%1> %0054%1
		#endinput
	#elseif UNIQUE_SYMBOL == 54
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (55)
		#define UNIQUE_FUNCTION<%0...%1> %0055%1
		#endinput
	#elseif UNIQUE_SYMBOL == 55
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (56)
		#define UNIQUE_FUNCTION<%0...%1> %0056%1
		#endinput
	#elseif UNIQUE_SYMBOL == 56
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (57)
		#define UNIQUE_FUNCTION<%0...%1> %0057%1
		#endinput
	#elseif UNIQUE_SYMBOL == 57
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (58)
		#define UNIQUE_FUNCTION<%0...%1> %0058%1
		#endinput
	#elseif UNIQUE_SYMBOL == 58
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (59)
		#define UNIQUE_FUNCTION<%0...%1> %0059%1
		#endinput
	#elseif UNIQUE_SYMBOL == 59
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (60)
		#define UNIQUE_FUNCTION<%0...%1> %0060%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 70
	#if UNIQUE_SYMBOL == 60
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (61)
		#define UNIQUE_FUNCTION<%0...%1> %0061%1
		#endinput
	#elseif UNIQUE_SYMBOL == 61
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (62)
		#define UNIQUE_FUNCTION<%0...%1> %0062%1
		#endinput
	#elseif UNIQUE_SYMBOL == 62
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (63)
		#define UNIQUE_FUNCTION<%0...%1> %0063%1
		#endinput
	#elseif UNIQUE_SYMBOL == 63
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (64)
		#define UNIQUE_FUNCTION<%0...%1> %0064%1
		#endinput
	#elseif UNIQUE_SYMBOL == 64
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (65)
		#define UNIQUE_FUNCTION<%0...%1> %0065%1
		#endinput
	#elseif UNIQUE_SYMBOL == 65
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (66)
		#define UNIQUE_FUNCTION<%0...%1> %0066%1
		#endinput
	#elseif UNIQUE_SYMBOL == 66
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (67)
		#define UNIQUE_FUNCTION<%0...%1> %0067%1
		#endinput
	#elseif UNIQUE_SYMBOL == 67
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (68)
		#define UNIQUE_FUNCTION<%0...%1> %0068%1
		#endinput
	#elseif UNIQUE_SYMBOL == 68
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (69)
		#define UNIQUE_FUNCTION<%0...%1> %0069%1
		#endinput
	#elseif UNIQUE_SYMBOL == 69
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (70)
		#define UNIQUE_FUNCTION<%0...%1> %0070%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 80
	#if UNIQUE_SYMBOL == 70
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (71)
		#define UNIQUE_FUNCTION<%0...%1> %0071%1
		#endinput
	#elseif UNIQUE_SYMBOL == 71
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (72)
		#define UNIQUE_FUNCTION<%0...%1> %0072%1
		#endinput
	#elseif UNIQUE_SYMBOL == 72
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (73)
		#define UNIQUE_FUNCTION<%0...%1> %0073%1
		#endinput
	#elseif UNIQUE_SYMBOL == 73
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (74)
		#define UNIQUE_FUNCTION<%0...%1> %0074%1
		#endinput
	#elseif UNIQUE_SYMBOL == 74
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (75)
		#define UNIQUE_FUNCTION<%0...%1> %0075%1
		#endinput
	#elseif UNIQUE_SYMBOL == 75
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (76)
		#define UNIQUE_FUNCTION<%0...%1> %0076%1
		#endinput
	#elseif UNIQUE_SYMBOL == 76
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (77)
		#define UNIQUE_FUNCTION<%0...%1> %0077%1
		#endinput
	#elseif UNIQUE_SYMBOL == 77
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (78)
		#define UNIQUE_FUNCTION<%0...%1> %0078%1
		#endinput
	#elseif UNIQUE_SYMBOL == 78
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (79)
		#define UNIQUE_FUNCTION<%0...%1> %0079%1
		#endinput
	#elseif UNIQUE_SYMBOL == 79
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (80)
		#define UNIQUE_FUNCTION<%0...%1> %0080%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 90
	#if UNIQUE_SYMBOL == 80
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (81)
		#define UNIQUE_FUNCTION<%0...%1> %0081%1
		#endinput
	#elseif UNIQUE_SYMBOL == 81
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (82)
		#define UNIQUE_FUNCTION<%0...%1> %0082%1
		#endinput
	#elseif UNIQUE_SYMBOL == 82
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (83)
		#define UNIQUE_FUNCTION<%0...%1> %0083%1
		#endinput
	#elseif UNIQUE_SYMBOL == 83
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (84)
		#define UNIQUE_FUNCTION<%0...%1> %0084%1
		#endinput
	#elseif UNIQUE_SYMBOL == 84
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (85)
		#define UNIQUE_FUNCTION<%0...%1> %0085%1
		#endinput
	#elseif UNIQUE_SYMBOL == 85
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (86)
		#define UNIQUE_FUNCTION<%0...%1> %0086%1
		#endinput
	#elseif UNIQUE_SYMBOL == 86
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (87)
		#define UNIQUE_FUNCTION<%0...%1> %0087%1
		#endinput
	#elseif UNIQUE_SYMBOL == 87
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (88)
		#define UNIQUE_FUNCTION<%0...%1> %0088%1
		#endinput
	#elseif UNIQUE_SYMBOL == 88
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (89)
		#define UNIQUE_FUNCTION<%0...%1> %0089%1
		#endinput
	#elseif UNIQUE_SYMBOL == 89
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (90)
		#define UNIQUE_FUNCTION<%0...%1> %0090%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 100
	#if UNIQUE_SYMBOL == 90
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (91)
		#define UNIQUE_FUNCTION<%0...%1> %0091%1
		#endinput
	#elseif UNIQUE_SYMBOL == 91
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (92)
		#define UNIQUE_FUNCTION<%0...%1> %0092%1
		#endinput
	#elseif UNIQUE_SYMBOL == 92
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (93)
		#define UNIQUE_FUNCTION<%0...%1> %0093%1
		#endinput
	#elseif UNIQUE_SYMBOL == 93
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (94)
		#define UNIQUE_FUNCTION<%0...%1> %0094%1
		#endinput
	#elseif UNIQUE_SYMBOL == 94
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (95)
		#define UNIQUE_FUNCTION<%0...%1> %0095%1
		#endinput
	#elseif UNIQUE_SYMBOL == 95
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (96)
		#define UNIQUE_FUNCTION<%0...%1> %0096%1
		#endinput
	#elseif UNIQUE_SYMBOL == 96
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (97)
		#define UNIQUE_FUNCTION<%0...%1> %0097%1
		#endinput
	#elseif UNIQUE_SYMBOL == 97
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (98)
		#define UNIQUE_FUNCTION<%0...%1> %0098%1
		#endinput
	#elseif UNIQUE_SYMBOL == 98
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (99)
		#define UNIQUE_FUNCTION<%0...%1> %0099%1
		#endinput
	#elseif UNIQUE_SYMBOL == 99
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (100)
		#define UNIQUE_FUNCTION<%0...%1> %0100%1
		#endinput
	#endif
#endif

