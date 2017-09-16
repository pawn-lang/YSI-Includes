#if defined _INC_y_cgen
	#endinput
#endif
#define _INC_y_cgen

/*+
 * <library name="y_cgen">
 * <section>
 *  Description
 * </section>
 *  Large chunks of code that isn't used, so that the space can be reclaimed and
 *  reused by other code generating functions.
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
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

#include "..\YSI_Storage\y_amx"
#include "..\YSI_Internal\y_thirdpartyinclude"

// We use "STE" not a string literal as we are trying to use up code space, not
// data space!
#define _CODE_1 SetTimerEx(s,0,0,s,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _CODE_2 _CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1

static stock
	YSI_g_sCodeSpace = -1,
	YSI_g_sCodeEnd = -1;

forward _@_y_cgen_@_0();

public _@_y_cgen_@_0()
{
	#emit RETN // Invisible return.
	//P:F("Someone called \"_@_y_cgen_@_0\" and somehow it didn't crash yet!");
	//assert(FALSE); // Always fails.
	// Reserve a huge area of "COD" for our own use!
	static
		s[] = "";
	// This reserves about 10kb of space in "COD".  If 10kb isn't enough I don't
	// know WHAT you're doing - that's enough space for about 200 hooks!
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	// These are blocks of 16 lines.  If you ever need to increase this space,
	// just duplicate a block of 16 lines.  Do not put multiple "_CODE_2;"
	// statements on one line - the pre-processor expands this so much that that
	// will probably just crash.
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
}

forward _@_y_cgen_@_1();

public _@_y_cgen_@_1()
{
	// This function SHOULD come straight after "_@_y_hooks_@_0" in both the
	// public functions table and code segment if the compiler is true to form.
}

static stock CGen_GetAddr(const func[])
{
	new
		entry = AMX_HEADER_PUBLICS + funcidx(func) * 8,
		ret = AMX_HEADER_COD + AMX_Read(entry);
	// Reset the pointer to this function, so calling it fails.
	//AMX_Write(entry, 0);
	return ret;
}

static stock CGen_SetupCodeSpace()
{
	if (YSI_g_sCodeSpace != -1) return;
	// Both these functions can now be safely called - but why would you?
	YSI_g_sCodeSpace = CGen_GetAddr("_@_y_cgen_@_0"),
	YSI_g_sCodeEnd   = CGen_GetAddr("_@_y_cgen_@_1"),
	// Rewrite "_@_y_cgen_@_0" to just "return 0;".
	AMX_Write(YSI_g_sCodeSpace, _:RelocateOpcode(OP_PROC)),
	AMX_Write(YSI_g_sCodeSpace + 4, _:RelocateOpcode(OP_ZERO_PRI)),
	AMX_Write(YSI_g_sCodeSpace + 8, _:RelocateOpcode(OP_RETN)),
	YSI_g_sCodeSpace += 12;
}

stock CGen_UseCodeSpace(ctx[AsmContext])
{
	CGen_SetupCodeSpace();
	AsmInitPtr(ctx, YSI_g_sCodeSpace, YSI_g_sCodeEnd - YSI_g_sCodeSpace);
}

stock CGen_GetCodeSpace()
{
	CGen_SetupCodeSpace();
	return YSI_g_sCodeSpace;
}

stock CGen_AddCodeSpace(num)
{
	if (YSI_g_sCodeSpace == -1) P:E("YSI_g_sCodeSpace is -1 in \"CGen_AddCodeSpace\"");
	else YSI_g_sCodeSpace += num;
}

#undef _CODE_2
#undef _CODE_1

