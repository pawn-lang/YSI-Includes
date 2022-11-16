/**
 * <library
 *   name="y_utils - varargs"
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
 * </library>
 *//** *//*
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
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - varargs</library>
 * <param name="arg">Index of the string in the parameters.</param>
 * <returns>
 *   String length.
 * </returns>
 * <remarks>
 *   Gets the length of a string passed to variable arguments, using the
 *   parameter index as in <c>getarg</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock va_strlen(arg)
{
	// Get the length of the string at the given position on the previous
	// function's stack (convenience function).
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SHL.C.pri  __cell_shift
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      __3_cells
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     __1_cell
	// Call the function.
	#emit SYSREQ.C   strlen
	// Restore the stack to its level before we called this native.
	#emit STACK      __2_cells
	#emit RETN
	// Never called.
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - varargs</library>
 * <param name="dest">Where to write the string to.</param>
 * <param name="arg">Index of the string in the parameters.</param>
 * <param name="len">The length of the destination address.</param>
 * <remarks>
 *   Like <c>getarg</c> but for strings.  Theoretically just a loop over
 *   <c>getarg</c>, but we can do better with <c>strcat</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock va_getstring(dest[], arg, len = sizeof (dest))
{
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SHL.C.pri  __cell_shift
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt __frame_offset
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      __3_cells
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the length for "strcat".
	#emit PUSH.S     len
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Load the address of the destination.
	#emit LOAD.S.alt dest
	// Blank the first cell so "strcat" behaves like "StrCpy".
	#emit ZERO.pri
	// Store the loaded number 0 to the loaded address.
	#emit STOR.I
	// Push the loaded address.
	#emit PUSH.alt
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     __3_cells
	// Call the function.
	#emit SYSREQ.C   strcat
	// Restore the stack to its level before we called this native.
	#emit STACK      __4_cells
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - varargs</library>
 * <param name="idx">Index of the string in the parameters.</param>
 * <returns>
 *   string
 * </returns>
 * <remarks>
 *   Is passed the result of getarg, which will be the address of a string (in
 *   theory) and uses that for DMA to get the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define getstring        ReturnStringArg
#define GetString        getstring
#define getstringarg     va_getstring
#define GetStringArg     va_getstring
#define returnstringarg  ReturnStringArg

stock ReturnStringArg(idx)
{
	static
		scSize = YSI_MAX_STRING;
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri idx
	// Then convert that number to bytes from cells.
	#emit SMUL.C     cellbytes
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "idx * 4 < *(*(FRM + 0) + 8)", for the previous frame
	// parameter count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      __param0_offset
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the length for "strcat".
	#emit PUSH       scSize
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Load the address of the secret destination.
	#emit LOAD.S.alt __param1_offset
	// Blank the first cell so "strcat" behaves like "StrCpy".
	#emit CONST.pri  0
	// Store the loaded number 0 to the loaded address.
	#emit STOR.I
	// Push the loaded address.
	#emit PUSH.alt
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     __3_cells
	// Call the function.
	#emit SYSREQ.C   strcat
	// Restore the stack to its level before we called this native.
	#emit STACK      __4_cells
	// Return without more string copying.
	#emit RETN
	
	// Fake return to define the API.
	new
		ret[YSI_MAX_STRING];
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - varargs</library>
 * <param name="fmat">String format.</param>
 * <param name="">Parameters.</param>
 * <returns>
 *   Formatted string.
 * </returns>
 * <remarks>
 *   Just wraps <c>format</c> and returns a string instead.  Has extra code to
 *   ensure that it works correctly on the old compiler.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock va_return(const string:fmat[], GLOBAL_TAG_TYPES:...)
{
	#pragma unused fmat
	
	static
		sFrm = 0,
		sRet = 0,
		sCnt = 0;
	const size = YSI_MAX_STRING;
	
	// Store the function preamble.
	#emit POP.pri
	#emit STOR.pri     sFrm
	#emit STACK        0 // Load the stack pointer for later.
	#emit POP.pri
	#emit STOR.pri     sRet
	#emit POP.pri
	#emit ADD.C        __2_cells
	#emit STOR.pri     sCnt
	
	// Put the secret return parameter on the stack again to format in to.
	#emit PUSH.C       size
	#emit ADD
	#emit LOAD.I
	#emit PUSH.pri
	
	// Call the native.
	#emit PUSH         sCnt
	#emit SYSREQ.C     format
	
	// Return directly.  This will clean up our entire stack, even the extra
	// parameters we put on it.  The parameter count is already there!
	#emit PUSH         sRet
	#emit PUSH         sFrm
	#emit RETN
	
	// Fake return to define the API.
	new
		ret[YSI_MAX_STRING];
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - varargs</library>
 * <param name="n">The numeric parameter position to print.</param>
 * <returns>
 *   Prints a string passed as a vararg to the calling function.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock PrintArg(n)
{
	#emit LOAD.S.pri   n
	#emit SHL.C.pri    __cell_shift
	#emit ADD.C        __3_cells
	#emit LOAD.S.alt   __frame_offset
	#emit ADD
	#emit LOAD.I
	#emit PUSH.pri
	#emit PUSH.C       __1_cell
	#emit SYSREQ.C     print
	#emit STACK        __2_cells
	#emit RETN
	__pragma("naked");
}

#define printarg PrintArg

