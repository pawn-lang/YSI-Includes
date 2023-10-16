#if defined _INC_y_version
	#endinput
#endif
#define _INC_y_version

/**
 * <library
 *   name="y_version"
 *   version="0.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Checks online to see if there is a newer version of YSI available."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.15
	
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

CHAIN_HOOK(YVers)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(YVers)

// Amazingly, this fixes hooking OnYSIInit...
CHAIN_FORWARD:YVers_OnYSIInit() = 1;

#if defined YSI_NO_VERSION_CHECK && !defined _YSI_NO_VERSION_CHECK
	#define _YSI_NO_VERSION_CHECK
#endif

static stock const
	/**
	 * <library>y_scriptdata</library>
	 */
	YSI_gscWindows[] = "Windows",
	/**
	 * <library>y_scriptdata</library>
	 */
	YSI_gscLinux[] = "Linux";

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The version of the JIT plugin loaded.
 * </returns>
 * <remarks>
 *   There is no native way to determine this, the code just tries to estimate
 *   based on some feature heuristics.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// 0 - No JIT
// 1 - Pre 2.1
// 2 - Post 2.1
// 3 - ???, in `OnJITCompile`
stock Server_GetJITVersion()
{
	if (Script_JITComplete())
	{
		#emit LCTRL     __cip
		#emit MOVE.alt
		#emit LCTRL     __jit_jump
		#emit NEQ
		#emit CONST.alt 1
		#emit XCHG
		#emit SHL
		#emit RETN
	}
	if (Server_JITExists())
	{
		return 3;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The version of the JIT plugin loaded, if any, as a string.
 * </returns>
 * <remarks>
 *   There is no native way to determine this, the code just tries to estimate
 *   based on some feature heuristics.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Server_GetJITString(version[], vlen = sizeof (version))
{
	version[0] = '\0';
	switch (Server_GetJITVersion())
	{
	case 0:
		strcat(version, "<none>", vlen);
	case 1:
		strcat(version, "2.0 or earlier", vlen);
	case 2:
		strcat(version, "2.1 or later", vlen);
	default:
		strcat(version, "<unknown>", vlen);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The version of the compiler used to build this script.  
 * </returns>
 * <remarks>
 *   The compiler version used isn't a feature of the server currently executing
 *   this code, hence this function is deprecated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_GetCompilerVersion`.
stock Server_GetCompilerVersion()
{
	#if ((__Pawn & 0x0F) >= 0x0A)
		// Accurate version.
		return (__Pawn << 16) | __pawn_build;
	#else
		// Estimate version - probably this one.
		return 0x03023664;
	#endif
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The version of the compiler used to build this script.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Script_GetCompilerVersion()
{
	#if ((__Pawn & 0x0F) >= 0x0A)
		// Accurate version.
		return (__Pawn << 16) | __pawn_build;
	#else
		// Estimate version - probably this one.
		return 0x03023664;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The version of the compiler used to build this script, as a string.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Script_GetCompilerString(version[], os[], vlen = sizeof (version), olen = sizeof (os))
{
	#if ((__Pawn & 0x0F) >= 0x0A)
		// Accurate version.
		format(version, vlen, "%d.%02d.%02d", __Pawn >>> 8, __Pawn & 0xFF, __pawn_build);
	#else
		// Estimate version - probably this one.
		version[0] = '\0',
		strcat(version, "3.2.3664", vlen);
	#endif
	#if __COMPILER_OS == __COMPILER_WINDOWS
		os[0] = '\0',
		strcat(os, YSI_gscWindows, olen);
	#else
		os[0] = '\0',
		strcat(os, YSI_gscLinux, olen);
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The version of the compiler used to build this script, as a string.
 * </returns>
 * <remarks>
 *   The compiler version used isn't a feature of the server currently executing
 *   this code, hence this function is deprecated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_GetCompilerString`.
stock Server_GetCompilerString(version[], os[], vlen = sizeof (version), olen = sizeof (os))
{
	Script_GetCompilerString(version, os, vlen, olen);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The codepage used to build this script, as a string.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Script_GetCompilerCodepage(version[], vlen = sizeof (version))
{
	#if __COMPILER_CODEPAGE == 0
		version[0] = '\0',
		strcat(version, "<none>", vlen);
	#elseif __COMPILER_CODEPAGE == -1
		version[0] = '\0',
		strcat(version, "<unknown>", vlen);
	#else
		valstr(version, __COMPILER_CODEPAGE, false);
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The includes used to build this script.
 * </returns>
 * <remarks>
 *   Version examples:
 *   <ul>
 *   <li>0.3.DL R1       - 03D010</li>
 *   <li>0.3.7 R3        - 037030</li>
 *   <li>0.3.7 R2-2      - 037022</li>
 *   <li>0.3.7 R1-2      - 037012</li>
 *   <li>0.3.7           - 037000</li>
 *   <li>0.3z R4         - 030740</li>
 *   <li>0.3z R3         - 030730</li>
 *   <li>0.3z R2-1       - 030721</li>
 *   <li>0.3z R1-2       - 030712</li>
 *   <li>0.3z            - 030700</li>
 *   <li>0.3x R2 patch 1 - 030621</li>
 *   <li>0.3x R2         - 030620</li>
 *   <li>0.3x R1-2       - 030612</li>
 *   <li>0.3x            - 030600</li>
 *   <li>0.3e            - 030500</li>
 *   <li>0.3d            - 030400</li>
 *   <li>0.3c            - 030300</li>
 *   <li>0.3b            - 030200</li>
 *   <li>0.3a            - 030100</li>
 *   <li>0.2X            - 02A000</li>
 *   <li>0.2.2 R3        - 022300</li>
 *   </ul>
 *
 *   Rough rules:
 *   <p />
 *
 *   Uses (roughtly) BCD.  Special versions are denoted outside 0-9.
 *   <p />
 *
 *   <code>
 *   0.1.2c R4-5
 *   | | ||  | |
 *   0 1 23  4 5
 *   =
 *   0x012345
 *   </code>
 *  
 *   (assuming c is the third revision)
 *   <p />
 *  
 *   0.2X becomes 02A000 because it is basically 0.2.3, but not, while higher
 *   than 0.2.2 so can't be 020400 (for example).  Also, its a capital letter,
 *   so doesn't use the revision method.
 *   <p />
 *  
 *   P.S.  Making a consistent scheme for SA:MP versions is REALLY hard.
 *   <p />
 *  
 *   open.mp releases can use `A` as the first digit.
 *  
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Script_GetIncludesVersion()
{
	// SA:MP version determination (from includes only).
	#if !defined _samp_included
		// No SA:MP version.
		return 0;
	#elseif defined StartRecordingPlayback
		// NPC mode.
		return cellmin;
	#else
		// Normal mode.
		#if !defined SendPlayerMessageToPlayer
			// 0.1
			return 0x010000;
		#elseif !defined DisableNameTagLOS
			// 0.2
			return 0x020000;
		#elseif !defined LimitPlayerMarkerRadius
			// 0.3a R4
			return 0x030140;
		#elseif INVALID_OBJECT_ID == 255
			// 0.3a R7
			// 0.3a R8
			return 0x030170;
		#elseif !defined ManualVehicleEngineAndLights
			// 0.3b R2
			return 0x030200;
		#elseif !defined GetPlayerNetworkStats
			// 0.3c
			// 0.3c R2-2
			return 0x030300;
		#elseif !defined DIALOG_STYLE_PASSWORD
			// 0.3c R4-1
			// 0.3c R5
			return 0x030300;
		#elseif !defined GetPlayerVersion
			// 0.3d
			// 0.3d R2
			return 0x030400;
		#elseif !defined EnableVehicleFriendlyFire
			// 0.3e
			// 0.3e R2
			return 0x030500;
		#elseif !defined VectorSize
			// 0.3x
			// 0.3x R1-2
			// 0.3x R2
			// 0.3x R2 patch1
			return 0x030600;
		#elseif !defined BlockIpAddress
			// 0.3z R1
			// 0.3z R1-2
			return 0x030710;
		#elseif !defined GetPlayerPoolSize
			// 0.3z R2-2
			// 0.3z R3
			// 0.3z R4 (added `OnTrailerUpdate`).
			return 0x030720;
		#elseif !defined AddCharModel
			// 0.3.7 R2-1-1
			// 0.3.7 R2-2-1
			// 0.3.7 R3
			// 0.3.8 RC1 (added `OnPlayerFinishedDownloading`).
			return 0x037000;
		#else//if !defined
			// 0.3.8 RC4-1
			// 0.3DL
			return 0x03D000;
		#endif
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The includes used to build this script.
 * </returns>
 * <remarks>
 *   The includes used were taken as a proxy for the server version, but they are
 *   not a good substitute, hence this function is deprecated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_GetIncludesVersion`.
stock Server_GetServerVersion()
{
	return Script_GetIncludesVersion();
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The includes used to build this script, as a string.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Script_GetIncludesString(version[], vlen = sizeof (version))
{
	// Not done yet.
	version[0] = '\0';
	// SA:MP version determination (from includes only).
	#if defined _INC_open_mp
		// open.mp version.
		format(version, vlen, "open.mp v%06x", __SAMP_INCLUDES_VERSION);
	#elseif defined __SAMP_INCLUDES_VERSION
		// SA:MP version.
		format(version, vlen, "samp-stdlib v%06x", __SAMP_INCLUDES_VERSION);
	#elseif !defined _samp_included
		// No SA:MP version.
		strcat(version, "<none>", vlen);
	#elseif defined StartRecordingPlayback
		// NPC mode.
		strcat(version, "<npc>", vlen);
	#else
		// Normal mode.
		#if !defined SendPlayerMessageToPlayer
			// 0.1
			strcat(version, "0.1", vlen);
		#elseif !defined DisableNameTagLOS
			// 0.2
			strcat(version, "0.2", vlen);
		#elseif !defined LimitPlayerMarkerRadius
			// 0.3a R4
			strcat(version, "0.3a R4-", vlen);
		#elseif INVALID_OBJECT_ID == 255
			// 0.3a R7
			// 0.3a R8
			strcat(version, "0.3a R7+", vlen);
		#elseif !defined ManualVehicleEngineAndLights
			// 0.3b R2
			strcat(version, "0.3b", vlen);
		#elseif !defined GetPlayerNetworkStats
			// 0.3c
			// 0.3c R2-2
			strcat(version, "0.3c R2-", vlen);
		#elseif !defined DIALOG_STYLE_PASSWORD
			// 0.3c R4-1
			// 0.3c R5
			strcat(version, "0.3c R4+", vlen);
		#elseif !defined GetPlayerVersion
			// 0.3d
			// 0.3d R2
			strcat(version, "0.3d", vlen);
		#elseif !defined EnableVehicleFriendlyFire
			// 0.3e
			// 0.3e R2
			strcat(version, "0.3e", vlen);
		#elseif !defined VectorSize
			// 0.3x
			// 0.3x R1-2
			// 0.3x R2
			// 0.3x R2 patch1
			strcat(version, "0.3x", vlen);
		#elseif !defined BlockIpAddress
			// 0.3z R1
			// 0.3z R1-2
			strcat(version, "0.3z R1-", vlen);
		#elseif !defined GetPlayerPoolSize
			// 0.3z R2-2
			// 0.3z R3
			// 0.3z R4 (added `OnTrailerUpdate`).
			strcat(version, "0.3z R2+", vlen);
		#elseif !defined AddCharModel
			// 0.3.7 R2-1-1
			// 0.3.7 R2-2-1
			// 0.3.7 R3
			// 0.3.8 RC1 (added `OnPlayerFinishedDownloading`).
			strcat(version, "0.3.7", vlen);
		#else//if !defined
			// 0.3.8 RC4-1
			// 0.3DL
			strcat(version, "0.3DL", vlen);
		#endif
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <library>y_serverdata</library>
 * <returns>
 *   The includes used to build this script, as a string.
 * </returns>
 * <remarks>
 *   The includes used were taken as a proxy for the server version, but they are
 *   not a good substitute, hence this function is deprecated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `Script_GetIncludesString`.
stock Server_GetServerString(version[], os[], vlen = sizeof (version), olen = sizeof (os))
{
	return Script_GetIncludesString(version, os, vlen, olen);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptdata</library>
 * <returns>
 *   The time the script started, as a string.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Script_GetStartString(output[], size = sizeof (output))
{
	static months[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	new year, month, day, hour, minute, second;
	Server_GetStartDateTime(year, month, day, hour, minute, second);
	format(output, size, "%02d %s %04d - %02d:%02d:%02d", day, months[month - 1], year, hour, minute, second);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_version</library>
 * <remarks>
 *   Print information about the script and server to the console.  Plugins,
 *   version, compiler, etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock YVers_PrintHeader()
{
	new
		version[38], os[10];
	GetConsoleVarAsString("version", version, sizeof (version));
	if (version[0])
	{
		format(version, sizeof (version), "Server:      %s (%c)", version, Server_IsWindowsHost() ? 'W' : 'L');
	}
	else
	{
		// TODO: Determine the exact SA:MP server version.
		format(version, sizeof (version), "Server:      SA:MP (%s)", Server_IsWindowsHost() ? YSI_gscWindows : YSI_gscLinux);
	}
	Server_PrintIntroPart(version),
	Script_GetStartString(version),
	format(version, sizeof (version), "Started:     %s", version),
	Server_PrintIntroPart(version),
	Server_PrintIntroPart(YSI_EMPTY),
	Script_GetCompilerString(version, os),
	format(version, sizeof (version), "Compiler:    %s (%s)", version, os),
	Server_PrintIntroPart(version),
	Script_GetIncludesString(version),
	format(version, sizeof (version), "Includes:    %s", version),
	Server_PrintIntroPart(version),
	Script_GetCompilerCodepage(version),
	format(version, sizeof (version), "Codepage:    %s", version),
	Server_PrintIntroPart(version);
	#if ((__Pawn & 0x0F) >= 0x0A)
		format(version, sizeof (version), "Built:       %s - %s", __date, __time),
		Server_PrintIntroPart(version);
	#endif
	Server_PrintIntroPart(YSI_EMPTY),
	format(version, sizeof (version), "YSI:         v%02d.%02d.%04d", YSI_VERSION_MAJOR, YSI_VERSION_MINOR, YSI_VERSION_BUILD),
	Server_PrintIntroPart(version);
	#if defined YSI_NO_MASTER
		Server_PrintIntroPart("Master:      <none>");
	#else
		format(version, sizeof (version), "Master:      %d", @_),
		Server_PrintIntroPart(version);
	#endif
	Server_PrintIntroPart(YSI_EMPTY),
	Server_GetJITString(version),
	format(version, sizeof (version), "JIT:         %s", version),
	Server_PrintIntroPart(version);
	if (!Server_CrashDetectExists())
	{
		Server_PrintIntroPart("Crashdetect: <none>");
	}
	else if (!Server_HasLongCallControl() && Server_IsLinuxHost())
	{
		Server_PrintIntroPart(
			"Crashdetect: <warning>",
			YSI_EMPTY,
			"  Crashdetect has been found, but no",
			"     long-call controls have been",
			"  detected.  Get the unofficial fixed",
			"            release from:",
			YSI_EMPTY,
			"          github.com/Y-Less/          ",
			"       samp-plugin-crashdetect/",
			YSI_EMPTY
		);
	}
	else if (Server_UpgradeCrashDetect())
	{
		Server_PrintIntroPart(
			"Crashdetect: <warning>",
			YSI_EMPTY,
			"  Crashdetect has been found, but may ",
			"  need updating.  Get the unofficial",
			"          fixed release from:",
			YSI_EMPTY,
			"          github.com/Y-Less/          ",
			"       samp-plugin-crashdetect/",
			YSI_EMPTY
		);
	}
	else
	{
		Server_PrintIntroPart("Crashdetect: <found>");
	}
	Server_FinishIntroPart();
}

/*-------------------------------------------------------------------------*//**
 * <library>y_version</library>
 * <remarks>
 *   Constructor.  Checks to see if there is a new version available.  This code
 *   can not use ANY of the rest of YSI as it needs to be included by everything
 *   first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !_YSI_SAFE_STARTUP
	stock YVers_StartCheck()
	{
		#if defined YSI_LOCK_MODE
			new
				x = 10;
			YSI_gLockData[YSI_gLockData[2]++] += (YSI_gLockData[3] = floatround(floatpower(x, 2))) - 2,
			YSI_gLockData[YSI_gLockData[2]++] = (YSI_gLockData[3] | 0x09) & ~0x04,
			YSI_gLockData[2] *= (6 * x) - 5;
		#endif
		return 1;
	}
	#endinput
#endif

#if !defined HTTP
	stock YVers_StartCheck()
	{
		#if defined YSI_LOCK_MODE
			new
				x = 10;
			YSI_gLockData[0] = 'a' + 1,
			YSI_gLockData[YSI_gLockData[0] - 0x60] = x * 11,
			YSI_gLockData[x / 3] = x * 10,
			YSI_gLockData[1] = (YSI_gLockData[2] - YSI_gLockData[3]) / 2 + YSI_gLockData[3];
		#endif
		#if __debug > 0
			YVers_PrintHeader();
			#if _YSI_SAFE_STARTUP
				Server_PrintIntroMessage(
					"Unable to check the latest YSI version",
					"- please watch the forums and github:",
					YSI_EMPTY,
					"         https://git.io/5.x"
				);
			#endif
		#endif
		return 1;
	}
	
	#endinput
#endif

stock YVers_StartCheck()
{
	#if defined YSI_LOCK_MODE
		YSI_gLockData[0] += 1;
		for (new i = 0; i != 2; ++i)
		{
			YSI_gLockData[0] = YSI_gLockData[0] * 9 + 2;
		}
		YSI_gLockData[0] -= 1,
		YSI_gLockData[3] = YSI_gLockData[0],
		YSI_gLockData[0] -= 1,
		YSI_gLockData[2] = YSI_gLockData[0] + 11,
		YSI_gLockData[0] -= 1,
		YSI_gLockData[1] = YSI_gLockData[0] + 7;
	#endif
	#if __debug > 0
		YVers_PrintHeader();
	#endif
	//YSI_Print__(" |                                      | ");
	//YSI_Print__(" |  Checking the latest YSI version..   | ");
	//YSI_Print__(YSI_gscSpacer);
	//YSI_Print__(YSI_gscHeader);
	// Call my server to check the current public YSI version.  v is the
	// current version and c is the version of data response which this code
	// can parse.  Note that the response data SHOULD be backward compatible
	// , but may not always be - hence the accept parameter.  This will
	// never send any data except the current version for targeted replies
	// (e.g. to ignore minor updates which aren't critical).  It MAY in the
	// future send what libraries are in use so that it only tells you to
	// upgrade if the libraries you are using have changed, but that will
	// take more work and I'm not going to do that for now (I'm not entirely
	// sure exactly how to do it (though I have an idea - note to self:
	// chain callbacks from repeated inclusions of this file in the same way
	// as ALS then call them BEFORE sending the HTTP)).  Note that due to
	// the way the internet works the server will know the IP of the server
	// which sent the request, but the ENTIRE current contents of the remote
	// page are (note: I won't update this comment every time the version
	// updates, but that's the gist of it):
	//  
	//  1
	//  1.01.0000
	//  
	// This remote script has now been updated to include changelog
	// information and keeps a record of what IPs are connecting.
	//HTTP(0, HTTP_GET, "version.ysi.tl/index.php?c=" #YSI_VERSION_RESPO "&v=" YSI_VERSION, YSI_EMPTY, &YVers_Callback<>);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_version</library>
 * <param name="	index">Not used.</param>
 * <param name="	code">Response code from the server.</param>
 * <param name="	data[]">HTTP data sent from the server.</param>
 * <remarks>
 *   This is called when my server responds to the HTTP request sent above  (or
 *   when it doesn't).  This prints information on the current and any future
 *   versions of YSI.  Note that it only does a strcmp to determine if the
 *   version is newer - people can't have versions newer than the latest, only
 *   older or equal (unless they play with the version numbers, but then that's
 *   their own fault).
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock YVers_Callback(index, code, data[])
{
	if (code == 200)
	{
		// Got the remote page.
		// The first line is the version data version.  This should be
		// forward compatible, so new data is always added to the end of the
		// file. Skip the first line - contains the response version.
		new
			pos = strfind(data, "\n") + 1;
		if (strcmp(data[pos], YSI_VERSION, false, 9))
		{
			//data[pos + 9] = '\0';
			new msg[40];
			format(msg, sizeof (msg), "A new version (v%s) of YSI is", data[pos]),
			Server_PrintIntroPart(msg, "available from:", YSI_EMPTY, "    www.y-less.com/YSI/YSI_1.0.zip");
			if (data[0] == '2')
			{
				Server_PrintIntroPart(YSI_EMPTY, "Changelog:", YSI_EMPTY);
				// Print the changelog.
				new
					last = pos + 13;
				for ( ; ; )
				{
					pos = strfind(data[last], "\n", false);
					if (pos == -1)
					{
						// To break out in the middle of a loop.
						break;
					}
					pos += last,
					data[pos - 1] = '\0',
					Server_PrintIntroPart(data[last]),
					last = pos + 1;
				}
			}
			//YSI_Print__(YSI_gscSpacer),
			//YSI_Print__(YSI_gscHeader),
			//YSI_Print__(YSI_gscMiniGap);
			Server_FinishIntroPart(),
			Server_FinishIntroMessage();
		}
	}
}

