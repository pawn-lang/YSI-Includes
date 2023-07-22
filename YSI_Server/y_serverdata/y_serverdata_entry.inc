#if defined _INC_y_serverdata
	#endinput
#endif

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

#define MASTER 

#include "..\..\YSI_Core\y_master"

static stock
	YSI_g_sLastNative[64] = "-", // Invalid.
	YSI_g_sRequestedData = 0;

stock bool:Server_HasNative(const name[])
{
	if (strcmp(name, YSI_g_sLastNative) == 0)
	{
		// The script is already loaded with this native.  Can just call it.
		return true;
	}
	
	YAR_WriteNative(name);

	if (!YAR_DumpFile())
	{
		return false;
	}
	
	// Reload the FS, and test that it did load.  If it didn't the native we
	// want to use probably doesn't exist.
	deleteproperty(27, "R__");
	if (YSI_g_sLastNative[0] == '-')
	{
		YSI_SendRconCommand__("loadfs ../scriptfiles/ysi_aux_runtime");
	}
	else
	{
		YSI_SendRconCommand__("reloadfs ../scriptfiles/ysi_aux_runtime");
	}
	if (existproperty(27, "R__"))
	{
		// Succeeded, the new native must exist.
		// Cache it.
		YSI_g_sLastNative[0] = '\0',
		strcat(YSI_g_sLastNative, name);
		return true;
	}
	if (YSI_g_sLastNative[0] != '-')
	{
		// Reset to the previous version (known safe).
		YAR_WriteNative(YSI_g_sLastNative);
		if (YAR_DumpFile())
		{
			YSI_SendRconCommand__("loadfs ../scriptfiles/ysi_aux_runtime");
		}
	}
	
	return false;
}

stock bool:Server_CallNative(const name[], &ret, const specifier[], GLOBAL_TAG_TYPES:...)
{
	// This call creates the filterscript.
	if (Server_HasNative(name))
	{
		CallRemoteFunction("N__", specifier, ___(3));
		ret = getproperty(27, "R__");
		return true;
	}
	return false;
}

public R__(const data[], length)
{
	if (YSI_g_sRequestedData)
	{
		// Save it.
		YSI_g_sRequestedData = 0;
	}
}

