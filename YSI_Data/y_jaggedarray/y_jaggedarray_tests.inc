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

Test:Jagged_Declaration_1()
{
	new Jagged:array[5]<1, 2, 3, 4, 5>;
	ASSERT(jaggedsizeof(array[0]) == 1);
	ASSERT(jaggedsizeof(array[1]) == 2);
	ASSERT(jaggedsizeof(array[2]) == 3);
	ASSERT(jaggedsizeof(array[3]) == 4);
	ASSERT(jaggedsizeof(array[4]) >= 5);
}

Test:Jagged_Declaration_2()
{
	new Jagged:array[10]<1, 2, 3, 4, 5>;
	ASSERT(jaggedsizeof(array[0]) == 1);
	ASSERT(jaggedsizeof(array[1]) == 2);
	ASSERT(jaggedsizeof(array[2]) == 3);
	ASSERT(jaggedsizeof(array[3]) == 4);
	ASSERT(jaggedsizeof(array[4]) == 5);
}

Test:Jagged_Declaration_3()
{
	new Jagged:array[3]<12, 1, 1>;
	ASSERT(jaggedsizeof(array[0]) == 12);
	ASSERT(jaggedsizeof(array[1]) == 1);
	ASSERT(jaggedsizeof(array[2]) >= 1);
}

Test:Jagged_Resize()
{
	new array[3][6];
	Jagged_Resize(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(jaggedsizeof(array[0]) == 3);
	ASSERT(jaggedsizeof(array[1]) == 12);
	ASSERT(jaggedsizeof(array[2]) >= 3);
}

Test:Jagged_Rearrange_0()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are yo"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_1()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 3}, {1, 5}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are yu?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_2()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 9}, {1, 6}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_3()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 9}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_4()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Move(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "howare you?"));
	ASSERT(!strcmp(array[2], "OK"));
}

