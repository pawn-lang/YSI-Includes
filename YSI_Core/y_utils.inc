/**
 * <library
 *   name="y_utils"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <section>
 *     Functions
 *   </section>
 *     <subsection>Stock</subsection>
 *   <ul>
 *     <symbol name="StrToLower">Convert a whole string to lower-case.</symbol>
 *     <symbol name="StrToUpper">Convert a whole string to upper-case.</symbol>
 *     <symbol name="Random">Generate a random number, optionally takes lower and upper bounds.</symbol>
 *     <symbol name="RandomFloat">Same as <symbolref name="Random" />, but for floats.</symbol>
 *     <symbol name="StripNL">Strips the newline characters from the end of a string.</symbol>
 *     <symbol name="StripL">Remove whitespace from the start of a string.</symbol>
 *     <symbol name="Strip">Remove whitespace from both ends of a string.</symbol>
 *     <symbol name="endofline">Check if the given position is the end of a string (ignoring whitespace).</symbol>
 *     <symbol name="chrfind">Return the first position (after <symbolref name="start" />) of the given character.</symbol>
 *     <symbol name="chrfindp">Like <symbolref name="chrfind" />, but without the upper-bounds check.</symbol>
 *     <symbol name="bernstein">Generate the Bernstein hash of the given string.</symbol>
 *     <symbol name="ishex">Is the given string hexadecimal?</symbol>
 *     <symbol name="Unpack">Version of <symbolref name="strunpack" /> that returns the result.</symbol>
 *     <symbol name="returnstringarg">Get the string passed as a variable argument from the given index.</symbol>
 *     <symbol name="va_return">Like <symbolref name="sprintf" />, formats a string and returns the result.</symbol>
 *     <symbol name="isnumeric">Is the given string a number?</symbol>
 *     <symbol name="hexstr">Return the value of the given hexadecimal string.</symbol>
 *     <symbol name="boolstr">Return the value of the given boolean string.</symbol>
 *     <symbol name="binstr">Return the value of the given binary string.</symbol>
 *     <symbol name="RawMemCpy">Copy memory between two address, instead of two arrays.</symbol>
 *     <symbol name="MemSet">Set all of an array to a value.</symbol>
 *     <symbol name="RawMemSet">Set all of a given memory region to a value.</symbol>
 *     <symbol name="ReturnPlayerName">Return a player's name.</symbol>
 *     <symbol name="ftouch">Ensures that a file exists, but nothing more.</symbol>
 *     <symbol name="InterpolateColour">Get the colour (in 3D RGB space) between two other colours.</symbol>
 *     <symbol name="SkipWhitespace">Return the first position in a string of a non-whitespace character.</symbol>
 *     <symbol name="Trim">Get the first and last positions of non-whitespace characters in the string.  Like <symbolref name="Strip" />, but doesn't modify the string.</symbol>
 *     <symbol name="Sum">Get the total (sum) of an array.</symbol>
 *     <symbol name="Mean">Get the mathematical mean of an array.</symbol>
 *     <symbol name="Mode">Get the mathematical mode of an array.</symbol>
 *     <symbol name="Median">Get the mathematical median of an array.</symbol>
 *     <symbol name="Range">Get the mathematical range of an array.</symbol>
 *   </ul>
 *     <subsection>Inline</subsection>
 *   <ul>
 *     <symbol name="UCMP">Unsigned compare.</symbol>
 *     <symbol name="VALID_PLAYERID">Check if a player ID is valid (in range).</symbol>
 *     <symbol name="IS_IN_RANGE">Check if a number is in range.</symbol>
 *     <symbol name="NOT_IN_RANGE">Check if a number is outside a range.</symbol>
 *     <symbol name="ceildiv">Divide two numbers and round up.</symbol>
 *     <symbol name="floordiv">Divide two numbers and round down.</symbol>
 *     <symbol name="IsNull">Checks if a string is NULL (<c>\1\0</c> or <c>\0</c>).</symbol>
 *     <symbol name="IsOdd">Checks if a number is odd.</symbol>
 *     <symbol name="IsEven">Checks if a number is even.</symbol>
 *     <symbol name="StrCpy">Copy one string to another.</symbol>
 *     <symbol name="GetIP">Return the encoded (32-bit) version of a player's IP.</symbol>
 *     <synonym name="getstring" for="returnstringarg"> (there are a lot)</synonym>
 *     <synonym name="GetString" for="returnstringarg"> (there are a lot)</synonym>
 *     <synonym name="getstringarg" for="returnstringarg"> (there are a lot)</synonym>
 *     <synonym name="GetStringArg" for="returnstringarg"> (there are a lot)</synonym>
 *     <synonym name="ReturnStringArg" for="returnstringarg"> (there are a lot)</synonym>
 *     <synonym name="InterpolateColor" for="InterpolateColour" />
 *     <synonym name="StripR" for="StripNL" />
 *   </ul>
 *   <section>
 *     Variables
 *   </section>
 *     <subsection>Global</subsection>
 *   <ul>
 *     <symbol name="TRUE">True hack for infinate loops.</symbol>
 *     <symbol name="FALSE">False hack for one-time loops.</symbol>
 *     <symbol name="NULL">1 long string for passing via Call(Remote|Local)Function.</symbol>
 *   </ul>
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

#if !defined _INC_y_core
	#tryinclude "y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude "YSI_Core\y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude "YSI\YSI_Core\y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude <YSI_Core\y_core\y_core_entry>
#endif
#if !defined _INC_y_core
	#tryinclude <YSI\YSI_Core\y_core\y_core_entry>
#endif
#if !defined _INC_y_core
	#error Could not find y_utils
#endif

