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
#include "..\y_thirdpartyinclude\y3_codeparse"
#include "..\y_thirdpartyinclude\y3_amx_assembly"

/*
@native("CreateDynamicCircle") STREAMER_TAG_AREA:MAYBE_CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0);

if (defined("MAYBE_CreateDynamicCircle"))
{
	MAYBE_CreateDynamicCircle(0.0, 0.0, 10.0);
}
*/

#define _@yN%0\32; _@yN

#define @native(%3)%0(%1) @decorator__(yN@_:yN_@)(%3)%0(%1)

// TODO: `void:` and `string:` return support.

#define yN@_:yN_@:%8$(%0)(%1)(%2)(%3)(%4)(%5); %8$native _@yN%2()=heapspace;stock %1%2(%3){static s=-1;return _yN@(%0,.s=s),H@(%5),%1_@yN%2();}
#define yN_@:%8$(%0)(%1)(%2)(%3)(%4)(%5) %8$native _@yN%2()=heapspace;stock %1%2(%3){static s=-3;return _yN@(%0,.s=s,.f=_:addressof(_@%2<%4>)),H@(%5),%1_@yN%2();}%1_@%2(%3)

stock _yN@(const string:name[], &s, const string:requires[] = "", f = 0, print = -1)
{
	Debug_Print4("_yN@ called: %s, %d, %s, %d", name, s, requires, f);
	// This code doesn't use 
	switch (s)
	{
	// These values are all odd because they can't be addresses.
	case -1, -3, -5:
	{
		Debug_Print5("_yN@: Looking up the native");
		// Request the native address.
		new
			addrLow,
			addrHigh;
		// `-1` - No fallback.
		// `-3` - No warnings.
		// `-5` - Warnings and fallback.
		if (Server_GetNative(name, addrLow, addrHigh))
		{
			Debug_Print5("_yN@: Found native at %08x, %08x", addrLow, addrHigh);
			// Get the next `SYSREQ.C` opcode to read the index from.
			// Shamelessly ripped from amx-assembly (but I wrote it in the first
			// place, so I said it was OK).
			new
				ctx[DisasmContext];
			DisasmInit(ctx, GetCurrentFrameReturn());
			while (DisasmNext(ctx))
			{
#if OPCODE_HAS_O2
				if (ctx[DisasmContext_opcode] == OP_SYSREQ_C || ctx[DisasmContext_opcode] == OP_SYSREQ_N)
#else
				if (ctx[DisasmContext_opcode] == OP_SYSREQ_C)
#endif
				{
					s = DisasmGetOperand(ctx);
					// The native exists.  Write both components of the address
					// pointer, despite the fact that we may only need one
					// depending on what server bit-width we're running on (not
					// worth working it out).
					f = AMX_GetEntryFromNativeIndex(s),
					AMX_Write(f, addrLow);
					Debug_Print5("_yN@: Found SYSREQ at %d, %08x", s, f);
					//printf("Found native %d (%d) with address %d, %d", s, f, addrLow, addrHigh);
					#if cellbits == 32
						// If we are running on a 32-bit machine this code does
						// nothing.  If we are running on a 64-bit machine this
						// will write the second cell of the stored pointer.
						// Pointer entires are `cellbits + 32` long, not a
						// constant two cells.  If this were 64-bit we'd need to
						// do awkward masking to write the upper bytes.
						// However, if this were a 64-bit script we wouldn't
						// need to write the second address at all so there's no
						// danger of clobbering data in either case.
						AMX_Write(f + 4, addrHigh);
					#else
						#pragma unused addrHigh
					#endif
					// Now store the address of the `SYSREQ` in `s` so that we
					// can jump to it later (this is to maintain JIT
					// compatibility since we can't write `SYSREQ.C` any more).
					break;
				}
			}
		}
		else
		{
			if (s == -3 ? print != 1 : print == 0)
			{
				// Fallback mode.  Don't print the errors here unless we
				// explicitly said to.
			}
			else if (IsNull(requires))
			{
				// Don't replace anything.  The server will fall back to calling
				// `heapspace`, which is essentially a no-op.
				Debug_PrintF("Attempting to call non-existant native `%s`.", name);
			}
			else
			{
				// Don't replace anything.  The server will fall back to calling
				// `heapspace`, which is essentially a no-op.
				Debug_PrintF("Attempting to call non-existant native `%s`; %s required.", name, requires);
			}
			if (s == -1)
			{
				s = -7;
				// Jump straight back to the calling function.
				#emit STACK        __10_cells
				#emit CONST.pri    0
				#emit RETN
				return 0;
			}
			// Call the fallback
			s = -9;
			// Use the fallback function.
			#emit STACK        __8_cells // Dump the function header.
			#emit POP.alt                // Get `f`.
			#emit POP.pri                // Dump data.
			#emit POP.pri
			#emit POP.pri
			#emit SCTRL        __frm     // Reset the frame pointer.
			#emit MOVE.pri
			#emit SCTRL        __cip     // Jump to the fallback code.
		}
	}
	case -7:
	{
		// Previously failed, no fallback.
		#emit STACK        __8_cells
		#emit CONST.pri    0
		#emit RETN
		return 0;
	}
	case -9:
	{
		// Use the fallback function.
		#emit STACK        __6_cells // Dump the function header.
		#emit POP.alt                // Get `f`.
		#emit POP.pri                // Dump data.
		#emit POP.pri
		#emit POP.pri
		#emit SCTRL        __frm     // Reset the frame pointer.
		#emit MOVE.pri
		#emit SCTRL        __cip     // Jump to the fallback code.
	}
	}
	{}
	Debug_Print5("_yN@: Calling native %d", s);
	// Call the native.
	#emit LREF.S.pri   s
	#emit STACK        __8_cells
	#emit MOVE.alt
	#emit POP.pri
	#emit SCTRL        __frm     // Reset the frame pointer.
	#emit MOVE.pri
	#emit POP.alt
	#emit SYSREQ.pri
	#emit PUSH.alt
	#emit PROC
	#emit RETN
	
	return 1;
}

#if defined YSI_TESTS
	#include "y_natives_tests"
#endif

