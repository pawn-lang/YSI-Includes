#if defined _INC_y_serverdata
	#endinput
#endif
#define _INC_y_serverdata

/**
 * <library
 *   name="y_scriptinit"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="OnScriptInit, OnCodeInit, and equivalent exit functions."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//**
 * <library
 *   name="y_scriptdata"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Utility functions for information about how and when the script was built."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//**
 * <library
 *   name="y_serverdata"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Utility functions for information about plugin and server options."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This file provides <c>OnScriptInit</c> and <c>OnScriptExit</c> which are
 *     called at the start and end of the current script, regardless of what the
 *     type of the script is.  It also provides <c>IS_FILTERSCRIPT</c> as a
 *     (partial) replacement for <c>FILTERSCRIPT</c> which detects what the mode is
 *     at runtime for a more reliable system (but it is a run-time variable, not a
 *     compile-time constant).
 *   </remarks>
 * </library>
 *//** *//*
	
	Now also provides OnCodeInit, which comes before OnScriptInit and should
	mostly be used for @emit code generation and other assembly related stuff
	(since it is called by the JIT if that exists).
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

#include "..\..\YSI_Core\y_core\y_core_entry"
#include "..\..\YSI_Coding\y_va"

#define MASTER 54
#define YSIM_U_DISABLE
#include "..\..\YSI_Core\y_master"

forward R__(const data[], length);

#if !_YSI_SAFE_STARTUP
	#if defined YSI_FIX_CALLBACKS
		forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);
	#endif

	#endinput
#endif

// Duplicated from amx_assembly.
#define __asm(%0,%1,%2,%3) (((0x%3) << 24) | ((0x%2) << 16) | (0x%1 << 8) | (0x%0))

static
	/**
	 * <library>y_serverdata</library>
	 */
	// This is an AMX encoded in to an array.  See the adjacent `.pwn` file for
	// the source (and feel free to recompile the source to verify that it is in
	// fact the same thing).
	YSI_g_sByteCode[] = {
		__asm(0C,06,00,00), __asm(E0,F1,08,08), __asm(10,00,08,00), __asm(14,01,00,00),
		__asm(8C,05,00,00), __asm(0C,06,00,00), __asm(0C,06,00,08), __asm(FF,FF,FF,FF),
		__asm(38,00,00,00), __asm(70,00,00,00), __asm(98,00,00,00), __asm(98,00,00,00),
		__asm(98,00,00,00), __asm(98,00,00,00), __asm(08,00,00,00), __asm(9A,00,00,00),
		__asm(F4,01,00,00), __asm(9E,00,00,00), __asm(34,00,00,00), __asm(A2,00,00,00),
		__asm(10,04,00,00), __asm(A6,00,00,00), __asm(50,02,00,00), __asm(BC,00,00,00),
		__asm(84,03,00,00), __asm(CF,00,00,00), __asm(94,00,00,00), __asm(DD,00,00,00),
		__asm(00,00,00,00), __asm(E1,00,00,00), __asm(00,00,00,00), __asm(E5,00,00,00),
		__asm(00,00,00,00), __asm(F1,00,00,00), __asm(00,00,00,00), __asm(F8,00,00,00),
		__asm(00,00,00,00), __asm(0B,01,00,00), __asm(15,00,43,5F), __asm(5F,00,47,5F),
		__asm(5F,00,4E,5F), __asm(5F,00,4F,6E), __asm(43,6C,69,65), __asm(6E,74,43,68),
		__asm(65,63,6B,52), __asm(65,73,70,6F), __asm(6E,73,65,00), __asm(4F,6E,46,69),
		__asm(6C,74,65,72), __asm(53,63,72,69), __asm(70,74,49,6E), __asm(69,74,00,4F),
		__asm(6E,52,63,6F), __asm(6E,43,6F,6D), __asm(6D,61,6E,64), __asm(00,53,5F,5F),
		__asm(00,59,53,49), __asm(00,73,65,74), __asm(70,72,6F,70), __asm(65,72,74,79),
		__asm(00,6D,65,6D), __asm(63,70,79,00), __asm(43,61,6C,6C), __asm(52,65,6D,6F),
		__asm(74,65,46,75), __asm(6E,63,74,69), __asm(6F,6E,00,73), __asm(74,72,63,6D),
		__asm(70,00,00,00), __asm(78,00,00,00), __asm(00,00,00,00), __asm(2E,00,00,00),
		__asm(1F,00,00,00), __asm(02,00,00,00), __asm(0F,00,00,00), __asm(74,00,00,00),
		__asm(0B,00,00,00), __asm(00,00,00,02), __asm(0F,00,00,00), __asm(70,00,00,00),
		__asm(59,00,00,00), __asm(30,00,00,00), __asm(2A,00,00,00), __asm(7B,00,00,00),
		__asm(00,00,00,00), __asm(27,00,00,00), __asm(00,00,00,00), __asm(24,00,00,00),
		__asm(27,00,00,00), __asm(40,00,00,00), __asm(27,00,00,00), __asm(1B,00,00,00),
		__asm(27,00,00,00), __asm(10,00,00,00), __asm(7B,00,00,00), __asm(01,00,00,00),
		__asm(2C,00,00,00), __asm(14,00,00,00), __asm(2B,00,00,00), __asm(1F,00,00,00),
		__asm(04,00,00,00), __asm(4E,00,00,00), __asm(20,00,00,00), __asm(04,00,00,00),
		__asm(78,00,00,00), __asm(00,00,00,00), __asm(2E,00,00,00), __asm(01,00,00,00),
		__asm(70,00,00,00), __asm(04,00,00,00), __asm(10,00,00,00), __asm(3E,00,00,00),
		__asm(B4,01,00,00), __asm(03,00,00,00), __asm(10,00,00,00), __asm(02,00,00,00),
		__asm(70,00,00,00), __asm(50,00,00,00), __asm(0C,00,00,00), __asm(01,00,00,00),
		__asm(4F,00,00,00), __asm(0F,00,00,00), __asm(70,00,00,00), __asm(27,00,00,00),
		__asm(00,00,00,00), __asm(28,00,00,00), __asm(74,00,00,00), __asm(27,00,00,00),
		__asm(40,00,00,00), __asm(27,00,00,00), __asm(1B,00,00,00), __asm(27,00,00,00),
		__asm(10,00,00,00), __asm(7B,00,00,00), __asm(01,00,00,00), __asm(2C,00,00,00),
		__asm(14,00,00,00), __asm(27,00,00,00), __asm(00,00,00,00), __asm(01,00,00,00),
		__asm(74,00,00,00), __asm(57,00,00,00), __asm(04,00,00,00), __asm(11,00,00,00),
		__asm(FC,FF,FF,FF), __asm(04,00,00,00), __asm(10,00,00,00), __asm(45,00,00,00),
		__asm(02,00,00,00), __asm(4E,00,00,00), __asm(20,00,00,00), __asm(02,00,00,00),
		__asm(04,00,00,00), __asm(10,00,00,00), __asm(14,00,00,00), __asm(74,00,00,00),
		__asm(0F,00,00,00), __asm(74,00,00,00), __asm(27,00,00,00), __asm(00,00,00,02),
		__asm(29,00,00,00), __asm(10,00,00,00), __asm(27,00,00,00), __asm(00,00,00,00),
		__asm(29,00,00,00), __asm(0C,00,00,00), __asm(29,00,00,00), __asm(FC,FF,FF,FF),
		__asm(27,00,00,00), __asm(14,00,00,00), __asm(7B,00,00,00), __asm(02,00,00,00),
		__asm(2C,00,00,00), __asm(18,00,00,00), __asm(2C,00,00,00), __asm(04,00,00,00),
		__asm(33,00,00,00), __asm(EC,01,00,00), __asm(27,00,00,00), __asm(00,00,00,00),
		__asm(27,00,00,00), __asm(00,00,00,00), __asm(27,00,00,00), __asm(40,00,00,00),
		__asm(27,00,00,00), __asm(1B,00,00,00), __asm(27,00,00,00), __asm(10,00,00,00),
		__asm(7B,00,00,00), __asm(01,00,00,00), __asm(2C,00,00,00), __asm(14,00,00,00),
		__asm(59,00,00,00), __asm(30,00,00,00), __asm(2E,00,00,00), __asm(01,00,00,00),
		__asm(74,00,00,00), __asm(20,00,00,00), __asm(02,00,00,00), __asm(03,00,00,00),
		__asm(0C,00,00,00), __asm(24,00,00,00), __asm(57,00,00,00), __asm(04,00,00,00),
		__asm(24,00,00,00), __asm(27,00,00,00), __asm(48,00,00,00), __asm(27,00,00,00),
		__asm(40,00,00,00), __asm(27,00,00,00), __asm(10,00,00,00), __asm(7B,00,00,00),
		__asm(03,00,00,00), __asm(2C,00,00,00), __asm(14,00,00,00), __asm(59,00,00,00),
		__asm(30,00,00,00), __asm(2E,00,00,00), __asm(27,00,00,00), __asm(00,00,00,00),
		__asm(1F,00,00,00), __asm(01,00,00,00), __asm(55,00,00,00), __asm(57,00,00,00),
		__asm(24,00,00,00), __asm(11,00,00,00), __asm(FC,FF,FF,FF), __asm(08,00,00,00),
		__asm(FC,FF,FF,FF), __asm(1F,00,00,00), __asm(01,00,00,00), __asm(50,00,00,00),
		__asm(11,00,00,00), __asm(FC,FF,FF,FF), __asm(07,00,00,00), __asm(FC,FF,FF,FF),
		__asm(11,00,00,00), __asm(FC,FF,FF,FF), __asm(27,00,00,00), __asm(40,00,00,00),
		__asm(29,00,00,00), __asm(FC,FF,FF,FF), __asm(27,00,00,00), __asm(40,00,00,00),
		__asm(27,00,00,00), __asm(1B,00,00,00), __asm(27,00,00,00), __asm(10,00,00,00),
		__asm(7B,00,00,00), __asm(01,00,00,00), __asm(2C,00,00,00), __asm(14,00,00,00),
		__asm(1F,00,00,00), __asm(01,00,00,00), __asm(55,00,00,00), __asm(57,00,00,00),
		__asm(24,00,00,00), __asm(11,00,00,00), __asm(FC,FF,FF,FF), __asm(08,00,00,00),
		__asm(FC,FF,FF,FF), __asm(1F,00,00,00), __asm(01,00,00,00), __asm(50,00,00,00),
		__asm(57,00,00,00), __asm(04,00,00,00), __asm(11,00,00,00), __asm(FC,FF,FF,FF),
		__asm(07,00,00,00), __asm(FC,FF,FF,FF), __asm(11,00,00,00), __asm(FC,FF,FF,FF),
		__asm(27,00,00,00), __asm(44,00,00,00), __asm(29,00,00,00), __asm(FC,FF,FF,FF),
		__asm(27,00,00,00), __asm(44,00,00,00), __asm(27,00,00,00), __asm(1B,00,00,00),
		__asm(27,00,00,00), __asm(10,00,00,00), __asm(7B,00,00,00), __asm(01,00,00,00),
		__asm(2C,00,00,00), __asm(14,00,00,00), __asm(2C,00,00,00), __asm(04,00,00,00),
		__asm(1F,00,00,00), __asm(02,00,00,00), __asm(0F,00,00,00), __asm(74,00,00,00),
		__asm(59,00,00,00), __asm(30,00,00,00), __asm(2E,00,00,00), __asm(27,00,00,00),
		__asm(FF,FF,FF,7F), __asm(27,00,00,00), __asm(01,00,00,00), __asm(27,00,00,00),
		__asm(54,00,00,00), __asm(29,00,00,00), __asm(0C,00,00,00), __asm(27,00,00,00),
		__asm(10,00,00,00), __asm(7B,00,00,00), __asm(04,00,00,00), __asm(2C,00,00,00),
		__asm(14,00,00,00), __asm(36,00,00,00), __asm(08,04,00,00), __asm(27,00,00,00),
		__asm(00,00,00,00), __asm(28,00,00,00), __asm(78,00,00,00), __asm(27,00,00,00),
		__asm(54,00,00,00), __asm(27,00,00,00), __asm(1B,00,00,00), __asm(27,00,00,00),
		__asm(10,00,00,00), __asm(7B,00,00,00), __asm(01,00,00,00), __asm(2C,00,00,00),
		__asm(14,00,00,00), __asm(54,00,00,00), __asm(30,00,00,00), __asm(59,00,00,00),
		__asm(30,00,00,00), __asm(2E,00,00,00), __asm(01,00,00,00), __asm(7C,00,00,00),
		__asm(35,00,00,00), __asm(2C,04,00,00), __asm(59,00,00,00), __asm(30,00,00,00),
		__asm(85,00,00,00), __asm(18,00,00,00), __asm(85,00,00,00), __asm(14,00,00,00),
		__asm(85,00,00,00), __asm(10,00,00,00), __asm(85,00,00,00), __asm(0C,00,00,00),
		__asm(27,00,00,00), __asm(4C,00,00,00), __asm(27,00,00,00), __asm(54,00,00,00),
		__asm(27,00,00,00), __asm(18,00,00,00), __asm(7B,00,00,00), __asm(03,00,00,00),
		__asm(2C,00,00,00), __asm(1C,00,00,00), __asm(30,00,00,00), __asm(59,53,49,20),
		__asm(41,75,78,69), __asm(6C,69,61,72), __asm(79,20,52,75), __asm(6E,74,69,6D),
		__asm(65,2C,20,28), __asm(63,29,20,32), __asm(30,32,33,20), __asm(41,6C,65,78),
		__asm(20,22,59,5F), __asm(4C,65,73,73), __asm(22,20,43,6F), __asm(6C,65,2E,00),
		__asm(00,00,00,00), __asm(00,00,00,00), __asm(00,00,00,00), __asm(00,5F,5F,52),
		__asm(00,5F,5F,51), __asm(00,00,69,61), __asm(69,69,69,69), __asm(00,00,00,00),
		__asm(45,58,49,46), __asm(6E,4F,5F,53), __asm(65,69,6C,43), __asm(68,43,74,6E),
		__asm(52,6B,63,65), __asm(6F,70,73,65), __asm(00,65,73,6E), __asm(00,00,00,02),
		__asm(00,00,00,00), __asm(2A,00,00,00), __asm(00,00,00,00)
	},
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_g_sLastNative[64] = "-", // Invalid.
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_g_sLastAddressA = 0,
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_g_sLastAddressB = 0,
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_g_sRequestedData = 0;

static stock const
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_gscResultA[] = "R__",
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_gscResultB[] = "Q__",
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_gscOnClientCheckResponse[] = "FIXES_OnClientCheckResponse",
	/**
	 * <library>y_serverdata</library>
	 */
	YSI_gscRconFixFS[] = "callbackfix.amx";

/**
 * <library>y_serverdata</library>
 */
static stock bool:Server_DumpFile()
{
	new
		File:f = fopen("ysi_aux_runtime.amx", io_write);
	if (f)
	{
		fblockwrite(f, YSI_g_sByteCode);
		fclose(f);
		return true;
	}
	return false;
}

/**
 * <library>y_serverdata</library>
 */
static stock Server_WriteNative(const name[])
{
	// Data should always be aligned, I think.
	new
		pack[64 char],
		i = -1,
		// The data array we write the new name in to.  This is found strictly
		// at the start of DAT, so is at `*0x10` (always, 32- and 64-bit).
		o = __32(YSI_g_sByteCode[16 / cellbytes]);
	o = o / cellbytes - 1;
	strpack(pack, name);
	do
	{
		++i;
		++o;
		YSI_g_sByteCode[o] = swapchars(pack[i]);
	}
	while (YSI_g_sByteCode[o] > (cellmax >>> (charbits - 1)));
}

foreign bool:Server_GetNative(const string:name[], &addrLow, &addrHigh);

/**
 * <library>y_serverdata</library>
 */
global bool:Server_GetNative(const string:name[], &addrLow, &addrHigh)
{
	if (strcmp(name, YSI_g_sLastNative) == 0)
	{
		// The script is already loaded with this native.  Can just call it.
		return
			addrLow = YSI_g_sLastAddressA,
			addrHigh = YSI_g_sLastAddressB,
			true;
	}
	
	Server_WriteNative(name);
	
	if (!Server_DumpFile())
	{
		return false;
	}
	
	// Reload the FS, and test that it did load.  If it didn't the native we
	// want to use probably doesn't exist.
	deleteproperty(27, YSI_gscResultA);
	if (YSI_g_sLastNative[0] == '-')
	{
		SendRconCommand(__const("loadfs ../scriptfiles/ysi_aux_runtime"));
	}
	else
	{
		SendRconCommand(__const("reloadfs ../scriptfiles/ysi_aux_runtime"));
	}
	if (existproperty(27, YSI_gscResultA))
	{
		// Succeeded, the new native must exist.
		// Cache it.
		return
			YSI_g_sLastNative[0] = '\0',
			strcat(YSI_g_sLastNative, name),
			addrLow = YSI_g_sLastAddressA = getproperty(27, YSI_gscResultA),
			addrHigh = YSI_g_sLastAddressB = getproperty(27, YSI_gscResultB),
			true;
	}
	if (YSI_g_sLastNative[0] != '-')
	{
		// Reset to the previous version (known safe).
		Server_WriteNative(YSI_g_sLastNative);
		if (Server_DumpFile())
		{
			SendRconCommand(__const("loadfs ../scriptfiles/ysi_aux_runtime"));
		}
	}

	return false;
}

/**
 * <library>y_serverdata</library>
 */
stock bool:Server_HasNative(const string:name[])
{
	new
		a,
		b;
	return Server_GetNative(name, a, b);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Not remote, but does call a remote function.  If that passes, THEN is does
 *   a normal `CallRemoteFunction` to the special native invocation function.
 * </remarks>
 *//*------------------------------------------------------------------------**/
stock bool:Server_CallNative(const name[], &ret, const specifier[], GLOBAL_TAG_TYPES:...)
{
	// This call creates the filterscript.
	if (Server_HasNative(name))
	{
		CallRemoteFunction("N__", specifier, ___(3));
		ret = getproperty(27, YSI_gscResultA);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 *//*------------------------------------------------------------------------**/
public R__(const data[], length)
{
	if (YSI_g_sRequestedData)
	{
		// Save it.
		YSI_g_sRequestedData = 0;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Stores a large amount of data in a random large space of allocated memory.
 *   Note that calling any `Server_XNative` function will invalidate this
 *   temporary storate space.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_WriteData(const data[], length = sizeof (data));

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Retrieves a large amount of data from a random large space of allocated
 *   memory.  Note that calling any `Server_XNative` function will invalidate
 *   this temporary storate space.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Server_ReadData(address, data[], length = sizeof (data));

foreign void:Server_DoAuxRuntimeLoad();

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   This code is always needed, even if fixes.inc exists, because y_master can
 *   repeatedly load and unload it to use as a buffer filterscript.  Basically,
 *   because this FS is always loaded it ensures that 16 other filterscripts
 *   can't all be loaded at once.  So if 15 are loaded and we need an extra
 *   space to reload one while preserving data we can unload this one, use the
 *   spare space, then load this one back up again.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// I can't remember if `static global` is a thing, but it should be.
global void:Server_DoAuxRuntimeLoad()
{
	if (fexist("callbackfix") || fexist("ysi_aux_runtime"))
	{
		// This check doesn't guarantee that it is loaded, but it better.  If
		// neither fix revision is loaded, but one exists, we'll still get an
		// unknown RCON command error.
		// Test if the fix has already been loaded.
		setproperty(27, YSI_gscOnClientCheckResponse, 0);
		SendRconCommand(__const(YSI_gscOnClientCheckResponse));
		// Another script has already loaded one of the two.  Unload them both.
		new res = getproperty(27, YSI_gscOnClientCheckResponse);
		if (res == 27)
		{
			// rconfix.
			SendRconCommand(__const("unloadfs ../scriptfiles/callbackfix"));
		}
		else if (res == Master_ID())
		{
			// We already loaded the script.  Nothing more to do.
			return;
		}
		else if (res)
		{
			// `res` is the master ID of the script that originally loaded the
			// aux FS.  Fortunately master IDs are always powers of two, and
			// despite the fact that I chose a completely random number in `27`
			// when I originally wrote the callbackfix FS, this does mean that
			// we will never have any conflicts.  This could also be `42` from
			// the old version of the AUX runtime.
			SendRconCommand(__const("unloadfs ../scriptfiles/ysi_aux_runtime"));
		}
	}
	// Now clear to load our new version.
	if (YSI_g_sLastNative[0] == '-')
	{
		// Not loaded yet.  We don't care if the file already exists because
		// this is the first time we've got here this server run, thus the
		// available natives may have changed since the last time we wrote it.
		#if cellbits == 64
			new offset = YSI_g_sByteCode[36 / cellbytes] >>> 32;
		#elseif cellbits == 32
			new offset = YSI_g_sByteCode[36 / cellbytes];
		#else
			#error Unsupported `cellbits`.
		#endif
		// This is the location in the file of the pointer to the native we are
		// `*0x24 + 4`, replacing.  It should be the first native, so could be
		// found at i.e. one cell after the start of the native functions block.
		YSI_g_sByteCode[offset / cellbytes + 1] = __32(YSI_g_sByteCode[16 / cellbytes]);
		// Store the current open.mp version (if there is one).
		YSI_g_sByteCode[sizeof (YSI_g_sByteCode) - 1] = __OPEN_MP_VERSION;
		// Store our master ID (so we know who dumped this file).
		YSI_g_sByteCode[sizeof (YSI_g_sByteCode) - 2] = Master_ID();
		// Rewrite the bytecode to include the name of the new native.
		Server_WriteNative("heapspace");
		YSI_g_sLastNative = "native";
	}
	
	// Always re-dump the file if we get to here.
	Server_DumpFile();
	SendRconCommand(__const("loadfs ../scriptfiles/ysi_aux_runtime"));
	if (fexist("ysi_aux_runtime.amx"))
	{
		#if defined YSI_FIX_CALLBACKS
			state OnClientCheckResponse : OnClientCheckResponse_GM;
		#endif
	}
	else
	{
		Debug_Warning("Could not load RconCommand/ClientCheckResponse fix FS.");
		Debug_Info("Ignore this error if the FS already loaded.");
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   This code is always needed, even if fixes.inc exists, because y_master can
 *   repeatedly load and unload it to use as a buffer filterscript.  Basically,
 *   because this FS is always loaded it ensures that 16 other filterscripts
 *   can't all be loaded at once.  So if 15 are loaded and we need an extra
 *   space to reload one while preserving data we can unload this one, use the
 *   spare space, then load this one back up again.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Server_LoadRconFix() <_ALS : _ALS_go>
{
	if (Master_ID())
	{
		// The master system is initialised.
		Server_DoAuxRuntimeLoad();
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <remarks>
 *   Unload the callback fix filterscript.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_UnloadRconFix() <_ALS : _ALS_go>
{
	SendRconCommand(__const("unloadfs ../scriptfiles/ysi_aux_runtime"));
}

#if defined YSI_TESTS
	#include "y_serverdata_tests"
#endif

#include "..\..\YSI_Core\y_master"

