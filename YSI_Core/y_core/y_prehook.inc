/*+
 * <library
 *   name="y_prehook"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="State-based ALS hooking with better control of orderings."
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

#if !defined CHAIN_ORDER
	#define CHAIN_ORDER() 0
#endif

#define CHAIN_HOOK(%0) forward @CO_%0();public @CO_%0(){return CHAIN_ORDER()+1;}

#define CHAIN_NEXT(%0) @CO_%0

static stock _PreHook_IncludeStates() <_ALS : _ALS_x0, _ALS : _ALS_x1, _ALS : _ALS_x2, _ALS : _ALS_x3>
{
}

static stock _PreHook_IncludeStates() <_ALS : _ALS_go>
{
}

#define CHAIN_FORWARD:%0_%2(%1)=%3; \
	forward %0_%2(%1); \
	public %0_%2(%1) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return (%3); } \
	public %0_%2(%1) <> { return (%3); }

#define CHAIN_PUBLIC:%0(%1) %0(%1) <_ALS : _ALS_go>

#if defined YSI_LOCK_MODE
	new
		YSI_gLockData[21];
#endif

#endinput

//                                                                                           
//    88888888888                                                            88              
//    88                                                                     88              
//    88                                                                     88              
//    88aaaaa      8b,     ,d8  ,adPPYYba,  88,dPYba,,adPYba,   8b,dPPYba,   88   ,adPPYba,  
//    88"""""       `Y8, ,8P'   ""     `Y8  88P'   "88"    "8a  88P'    "8a  88  a8P_____88  
//    88              )888(     ,adPPPPP88  88      88      88  88       d8  88  8PP"""""""  
//    88            ,d8" "8b,   88,    ,88  88      88      88  88b,   ,a8"  88  "8b,   ,aa  
//    88888888888  8P'     `Y8  `"8bbdP"Y8  88      88      88  88`YbbdP"'   88   `"Ybbd8"'  
//                                                              88                           
//                                                              88                           
//    

// STEP 0

// First, decide on your library prefix.  For this example I will use `<LIB>`,
// you should use an actually valid name.

// STEP 1

// Do this once at the top of the file.  This hard-codes the call order.
forward @CO_<LIB>();public @CO_<LIB>(){return CHAIN_ORDER()+1;}
#undef CHAIN_ORDER
#define CHAIN_ORDER @CO_<LIB>

// If you are using `y_prehook` this simplifies to:
CHAIN_HOOK(<LIB>)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(<LIB>)

// Note that both the order and the `@CO_` are fixed and very important.

// STEP 2

// Insert the callback to hook as normal:

public OnPlayerConnect(playerid)
{
}

// STEP 3:

// Call the next callback in the chain.  Note that this is not conditionally
// compiled in any way:

public OnPlayerConnect(playerid)
{
	return <LIB>_OnPlayerConnect(playerid)
}

// STEP 4:

// ALS

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

// STEP 5:

// Forward the next callback and define it in unused states (with an appropriate
// default return, usually `1`).
forward <LIB>_OnPlayerConnect(playerid);
public <LIB>_OnPlayerConnect(playerid) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return 1; }
public <LIB>_OnPlayerConnect(playerid) <> { return 1; }

// Again, if you are using `y_prehook` this massively simplifies to:
CHAIN_FORWARD:<LIB>_OnPlayerConnect(playerid)=1;

// STEP 6:

// Define the chain:
#define OnPlayerConnect(%0) <LIB>_OnPlayerConnect(%0) <_ALS : _ALS_go>

// Or with `y_prehook`:
#define OnPlayerConnect(%0) CHAIN_PUBLIC:<LIB>_OnPlayerConnect(%0)

// STEP 7:

// Somewhere in one of your init functions (or all of them) add:
public OnScriptInit()
{
	state _ALS : _ALS_go;
}

// STEP 8 (optional):

// If you get warnings about undefined states, put this in your code to define
// all the valid states:
static stock _<LIB>_IncludeStates() <_ALS : _ALS_x0, _ALS : _ALS_x1, _ALS : _ALS_x2, _ALS : _ALS_x3>
{
}

static stock _<LIB>_IncludeStates() <_ALS : _ALS_go>
{
}

