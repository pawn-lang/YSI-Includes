#if defined _INC_y_thirdparty_codeparse
	#endinput
#endif
#define _INC_y_thirdparty_codeparse

/*+
 * <library
 *   name="y_thirdpartyinclude"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Try and include all YSI dependencies, looking in as many places as needed."
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

// Manually fix earlier versions.
#if !defined _INC_code_parse_inc
	#undef u@
#endif
#tryinclude <code-parse\code-parse>
#tryinclude <code-parse.inc\code-parse>
#tryinclude <code-parse.inc-master\code-parse>
#tryinclude <code-parse.inc-master\code-parse.inc-master\code-parse>
#tryinclude "..\..\code-parse\code-parse"
#tryinclude "..\..\code-parse.inc\code-parse"
#tryinclude "..\..\code-parse.inc-master\code-parse"
#tryinclude "..\..\code-parse.inc-master\code-parse.inc-master\code-parse"
#tryinclude "..\..\..\code-parse\code-parse"
#tryinclude "..\..\..\code-parse.inc\code-parse"
#tryinclude "..\..\..\code-parse.inc-master\code-parse"
#tryinclude "..\..\..\code-parse.inc-master\code-parse.inc-master\code-parse"
#tryinclude "code-parse"
#tryinclude <code-parse>
#if defined _INC_code_parse_inc
	#undef u@
#else
	#error Download `github.com/Y-Less/code-parse.inc/archive/refs/heads/master.zip` and extract it to `include\`.
//#elseif !defined __code_parse_u@_1
//	#error Re-download `github.com/Y-Less/code-parse.inc/archive/refs/heads/master.zip` and extract it to `include\`.
#endif
#define u@$ 1]);

