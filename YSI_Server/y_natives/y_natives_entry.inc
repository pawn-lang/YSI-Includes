#if defined _INC_y_natives
	#endinput
#endif
#define _INC_y_natives

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
#include "..\y_decorator"
#include "..\y_serverdata"
#include "..\y_thirdpartyinclude\y_codeparse"
#include "..\y_thirdpartyinclude\y_amx-assembly"

/*
@native("CreateDynamicCircle") STREAMER_TAG_AREA:MAYBE_CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0);

if (defined("MAYBE_CreateDynamicCircle"))
{
	MAYBE_CreateDynamicCircle(0.0, 0.0, 10.0);
}
*/

#define _yN@%0\32; _yN@

#define @native(%3)%0(%1); @decorator__(NATIVE_DECORATOR)(%3)%0(%1)

// TODO: `void:` and `string:` return support.
#define NATIVE_IDXOF(%0(%1)) (_:((O@B_())?(((%0(%1)),O@V_)?1:2):(O@V_)))

#define NATIVE_DECORATOR:%8$("%0")(%1)(%2)(%3)(%4)(%5) %8$native %1_yN@%2(%3)=heapspace;stock %1%2(%3){static s=1;if(s)s=yN@_(#%0,NATIVE_IDXOF(_yN@%2(%5)));return _yN@%2(%5);}

stock yN@_(const string:name[], idx)
{
	// Request the native address.
	new
		addrLow,
		addrHigh;
	if (Server_GetNative(name, addrLow, addrHigh))
	{
		//printf("Found native %d (%d) with address %d, %d", idx, AMX_GetEntryFromNativeIndex(idx), addrLow, addrHigh);
		// The native exists.  Write both components of the address pointer,
		// despite the fact that we may only need one depending on what server
		// bit-width we're running on (not worth working it out).
		idx = AMX_GetEntryFromNativeIndex(idx),
		AMX_Write(idx, addrLow);
		#if cellbits == 32
			// If we are running on a 32-bit machine this code does nothing.  If
			// we are running on a 64-bit machine this will write the second
			// cell of the stored pointer.  Pointer entires are `cellbits + 32`
			// long, not a constant two cells.  If this were 64-bit we'd need to
			// do awkward masking to write the upper bytes.  However, if this
			// were a 64-bit script we wouldn't need to write the second address
			// at all so there's no danger of clobbering data in either case.
			AMX_Write(idx + 4, addrHigh);
		#else
			#pragma unused addrHigh
		#endif
	}
	else
	{
		// Don't replace anything.  The server will fall back to calling
		// `heapspace`, which is essentially a no-op.
		Debug_PrintF("Attempting to call non-existant native `%s`", name);
	}
	
	// Never repeat this code.
	return 0;
}

#if defined YSI_TESTS
	#include "y_natives_tests"
#endif

