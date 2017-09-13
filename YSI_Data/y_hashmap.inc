/**
					  ====================================
					   y_hashmap - Link strings to values
					  ====================================
<subsection>Description</subsection>
	Maps string indexes to integer indexes.  Uses a fast hash to get an array
	slot, then a linked list to resolve collisions.
<subsection>Version</subsection>
	2.0
<subsection>Changelog</subsection>
	23/06/13:
		First version.
<subsection>Functions</subsection>
	stock:
		HashMap_Init - Associate a hash map with an array.
		HashMap_Add - Add a value under a given string.
		HashMap_Get - Get a value from a string.
		HashMap_RemoveKey - Remove a string and its value from a hash map.
		HashMap_Set - Change the value associated with a key.
<subsection>Definitions</subsection>
	HASH_MAP_DATA - What should be added to enums to be hash map referenced.
	HashMap - Declare a new hash map.
*//** *//*
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

#if defined _INC_y_hashmap
	#endinput
#endif
#define _INC_y_hashmap

#include "..\YSI_Internal\y_thirdpartyinclude"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Coding\y_stringhash"
#include "..\YSI_Internal\y_shortfunc"

#include "y_hashmap/impl"

// The hashmap tests are vast.  Only include them when explicitly requested.
#if defined YSI_TESTS && defined YSI_HASHMAP_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_hashmap/tests"
#endif

