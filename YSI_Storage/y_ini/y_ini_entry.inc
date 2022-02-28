#if defined _INC_y_ini
	#endinput
#endif
#define _INC_y_ini

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

#include "..\..\YSI_Core\y_utils"

#define MAX_INI_LINE                    (MAX_INI_ENTRY_NAME + MAX_INI_ENTRY_TEXT + 32)

#if !defined INI_NEW_LINE
	#define INI_NEW_LINE                "\r\n"
#endif

#if !defined MAX_INI_TAG
	#define MAX_INI_TAG                 (32)
#endif

#if !defined MAX_INI_ENTRY_NAME
	#define MAX_INI_ENTRY_NAME          (32)
#endif

#if !defined MAX_INI_ENTRY_TEXT
	#define MAX_INI_ENTRY_TEXT          YSI_MAX_INLINE_STRING
#endif

#if !defined INI_MAX_WRITES
	#define INI_MAX_WRITES              (4)
#endif

#if !defined INI_BUFFER_SIZE
	#define INI_BUFFER_SIZE             (128)
#endif

#if !defined MAX_INI_TAGS
	#define MAX_INI_TAGS                (8)
#endif

#define MAX_INI_STRING                  FUNCTION_LENGTH

#define Y_INI_WRITE_ARRAY_SIZE ((MAX_INI_ENTRY_TEXT - 1) / 16 * 16)

stock const
	INI_NO_TAG[] = "\1"; // NULL

#define INI_NO_FILE (INI:-1)

#include "..\..\YSI_Coding\y_inline"
#include "..\..\YSI_Coding\y_stringhash"

#if defined YSI_TESTS
	#define _Y_INI_STATIC
#else
	#define _Y_INI_STATIC static
#endif

#include "..\..\YSI_Coding\y_hooks"

#include "y_ini_impl"

#if defined YSI_TESTS
	#tryinclude "..\..\amx\os"
	#tryinclude <amx_assembly\os>
	#tryinclude "..\..\amx_assembly\os"
	#tryinclude "..\..\..\amx_assembly\os"
	#tryinclude "os"
	#tryinclude <os>

	#if !defined OS_INC
		#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
	#endif

	#include "y_ini_tests"
#endif

