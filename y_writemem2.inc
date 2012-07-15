/*----------------------------------------------------------------------------*\
					===========================
					Y Sever Includes - Writemem
					===========================
Description:
	Write to any absolute address in the SA:MP server in pure PAWN with embedded
	assembly (i.e. a new native).  Calls "VirtualProtect" to make writes safe.
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

	The Original Code is the YSI ini include.

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
	1.0
Changelog:
	01/02/12:
		Zeex_: Changed to use SYSREQ.D call not SYSREQ.C.
		Zeex_: Modified "VirtualProtect" pointer to SA:MP server one.
		Added "VirtualProtect" calls to the code.
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		WriteMem - Write data to an address.
Callbacks:
	-
Definitions:
	asm - Convert a stream of assembly to a cell.
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
		YSI_g_sWriteMem - The assembly.
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

#include <a_samp>
#include "y_amx"
#include "y_hooks"
#include "y_utils"

forward WriteMem(addr, value);

#define asm(%0,%1,%2,%3) ((0x%0<<0)|(0x%1<<8)|(0x%2<<16)|(0x%3<<24))

/*
cell AMX_NATIVE_CALL
	n_WriteMem(AMX * amx, cell * params)
{
	if (params[0] == 8)
	{
		DWORD
			oldp;
		VirtualProtect((cell *)params[1], 4, PAGE_EXECUTE_READWRITE, &oldp);
		*((cell *)params[1]) = params[2];
	}
	return 0;
}

BECOMES:

	align   16
	push    ebp
	mov     ebp, esp
	push    esi
	mov     esi, [ebp+12]
	cmp     dword ptr [esi], 8
	jnz     short loc_ret
	mov     ecx, [esi+4]
	lea     eax, [ebp+12]
	push    eax
	push    40h
	push    4
	push    ecx
	call    ds:__imp__VirtualProtect@16
	mov     edx, [esi+4]
	mov     eax, [esi+8]
	mov     [edx], eax
loc_ret:
	xor     eax, eax
	pop     esi
	pop     ebp
	retn
*/

static
	YSI_g_sWriteMem[] =
	{
		asm(CC,CC,CC,CC), asm(CC,CC,CC,CC), asm(CC,CC,CC,CC), asm(CC,CC,CC,CC),
		asm(55,8B,EC,56), asm(8B,75,0C,83), asm(3E,08,75,1A), asm(8B,4E,04,8D),
		asm(45,0C,50,6A), asm(40,6A,04,51), asm(FF,15,8C,11), asm(4A,00,8B,56),
		asm(04,8B,46,08), asm(89,02,33,C0), asm(5E,5D,C3,CC)
	};

static
	YSI_g_iWriteMemAddr = 0;

stock
	WriteMem(addr, value)
{
	static ptr = -1;
	
	// Push addr and value.
	#emit PUSH.S value
	#emit PUSH.S addr
	#emit PUSH.C 8
	
	if (ptr == -1)
	{
		// ptr = COD + CIP - DAT + <distance to nop #1>
		// Modified from code by Zeex_.
		#emit LCTRL      6  // CIP
		#emit LOAD.alt   AMX_HEADER_COD
		#emit ADD
		#emit ADD.C      84
		#emit STOR.S.pri ptr
		
		// NOP #1 = SYSREQ.D
		#emit CONST.pri  135
		#emit SREF.S.pri ptr
		
		// ptr += 4
		#emit LOAD.S.pri ptr
		#emit ADD.C      4
		#emit STOR.S.pri ptr
		
		// NOP #2 = address
		#emit LOAD.pri   YSI_g_iWriteMemAddr
		#emit SREF.S.pri ptr
	}
	// Reserve space for SYSREQ.D WriteMem.
	#emit NOP
	#emit NOP
	
	// Pop native arguments.
	#emit STACK 12
}

static
	WM_Shift(from, to, data[], len = sizeof (data))
{
	if (FALSE)
	{
		WriteMem(0, 0);
	}
	while (from < len)
	{
		data[to++] = data[from++];
	}
}

hook OnScriptInit()
{
	new
		addr = AMX_GetGlobalAddress(YSI_g_sWriteMem);
	// Align the code to a 16-byte boundary.
	switch (addr & 15)
	{
		case 0:
		{
			WM_Shift(4, 0, YSI_g_sWriteMem);
		}
		case 4:
		{
			WM_Shift(4, 3, YSI_g_sWriteMem);
			addr += 12;
		}
		case 8:
		{
			WM_Shift(4, 2, YSI_g_sWriteMem);
			addr += 8;
		}
		case 12:
		{
			WM_Shift(4, 1, YSI_g_sWriteMem);
			addr += 4;
		}
		default:
		{
			P:E("Cannot relocate YSI_g_sWriteMem");
		}
	}
	YSI_g_iWriteMemAddr = addr;
	return 1;
}
