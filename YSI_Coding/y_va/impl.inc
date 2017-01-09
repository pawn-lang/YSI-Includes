/**--------------------------------------------------------------------------**\
					==============================
					 y_va - Enhanced vararg code!
					==============================
Description:
	This library currently provides two functions - va_printf and va_format
	which perform printf and format using variable arguments passed to another
	function.
	
	This is bsed on the variable parameter passing method based on code by Zeex.
	See page 15 of the code optimisations topic.
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
	
	The Original Code is the YSI vararg include.
	
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
	02/05/11:
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
		-
Callbacks:
	-
Definitions:
	-
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
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

static stock
	YSI_g_sHeap,
	YSI_g_sStack,
	YSI_g_sArgCount,
	YSI_g_sArgs[6];

stock va_printf(const fmat[], va_:STATIC_ARGS)
{
	// Get the number of parameters.  Plus an extra one because the JIT pushes
	// its own value on to the stack (won't make any difference when the JIT
	// isn't in use).
	#emit LOAD.S.alt   STATIC_ARGS
	#emit INC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "printf"s parameter count.
	
	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD
	#emit ADD.C        0xFFFFFFFC // -4 adjustment for JIT.
	
	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         12 // (n + 3) * 4
	
	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        12 // (n + 3) * 4
	#emit SCTRL        4
	
	// "frm" is still valid.
	#emit PUSH.S       fmat            // Get the final parameter.
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.
	
	// Call the function.
	#emit SYSREQ.C     printf
	#emit STOR.pri     YSI_g_sArgCount
	
	// Copy the data back.
	#emit STACK        0xFFFFFFFC // -4 adjustment for JIT.
	#emit STACK        0
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         12
	
	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN
	
	// This new version of the code worked first time!  I'm very happy with that
	// result, but I also feel it was justified given how long I spent staring
	// at it!
	return 0;
}

stock va_CallRemoteFunction(const function[], const fmat[], va_:STATIC_ARGS)
{
	// This function can't use the same stack manipulation tricks as most of the
	// other native function calls, since the native calls back in to user code
	// and so will use more of the stack.  The other native calls are fast
	// because they unwind part of the stack, use the parameters from an earlier
	// function call to call the native, then restore the stack to where it was
	// before.  If this does that, local variables and frame headers will be
	// overwritten by the called functions.  This problem also affects
	// "CallLocalFunction", but does NOT affect "SetTimerEx", because that gets
	// a totally fresh stack for the called function when it eventually is
	// called.  Ideally, this would use "MOVS" rewriting to do the data copying,
	// but that method is not JIT compatible, so instead we must use "memcpy".
	
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit SHL.C.alt    2
	#emit STOR.alt     YSI_g_sArgCount
	// "alt" now contains the number of static arguments in bytes.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	// "pri" now contains the number of total arguments in bytes.
	
	// Subtract the number of static bytes, and allocate the memory for the
	// variable arguments.
	#emit SUB
	// "pri" now contains the number of dynamic arguments in bytes.	
	#emit STOR.pri     YSI_g_sStack
	#emit STACK        0
	#emit SUB.alt
	#emit SCTRL        4
	
	// Copy the data.
	#emit LOAD.alt     YSI_g_sArgCount
	#emit LOAD.S.pri   0
	#emit ADD.C        12
	#emit ADD
	// "pri" now contains a pointer to the dynamic arguments.
	
	// Call "memcpy".  The final argument (the first push) is stupid big, way
	// bigger than it needs to be, but we know the destination is large enough
	// so there's no need to check and pass an accurate value, instead we can
	// just pass a "large enough" constant.
	#emit STACK        0
	#emit PUSH.C       1000000
	#emit PUSH         YSI_g_sStack
	#emit PUSH.C       0
	#emit PUSH.pri
	#emit PUSH.alt
	#emit PUSH.C       20
	#emit SYSREQ.C     memcpy
	#emit STACK        24
	
	// Call "CallRemoteFunction"
	#emit PUSH.S       fmat
	#emit PUSH.S       function
	#emit LOAD.pri     YSI_g_sStack
	#emit ADD.C        8
	#emit PUSH.pri
	#emit SYSREQ.C     CallRemoteFunction
	
	// Pop the stack.
	#emit STOR.pri     YSI_g_sArgCount
	#emit POP.pri
	#emit STACK        0
	#emit ADD
	#emit SCTRL        4
	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN
	
	return 0;
}

stock va_CallLocalFunction(const function[], const fmat[], va_:STATIC_ARGS)
{
	// This function can't use the same stack manipulation tricks as most of the
	// other native function calls, since the native calls back in to user code
	// and so will use more of the stack.  The other native calls are fast
	// because they unwind part of the stack, use the parameters from an earlier
	// function call to call the native, then restore the stack to where it was
	// before.  If this does that, local variables and frame headers will be
	// overwritten by the called functions.  This problem also affects
	// "CallRemoteFunction", but does NOT affect "SetTimerEx", because that gets
	// a totally fresh stack for the called function when it eventually is
	// called.  Ideally, this would use "MOVS" rewriting to do the data copying,
	// but that method is not JIT compatible, so instead we must use "memcpy".
	
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit SHL.C.alt    2
	#emit STOR.alt     YSI_g_sArgCount
	// "alt" now contains the number of static arguments in bytes.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	// "pri" now contains the number of total arguments in bytes.
	
	// Subtract the number of static bytes, and allocate the memory for the
	// variable arguments.
	#emit SUB
	// "pri" now contains the number of dynamic arguments in bytes.	
	#emit STOR.pri     YSI_g_sStack
	#emit STACK        0
	#emit SUB.alt
	#emit SCTRL        4
	
	// Copy the data.
	#emit LOAD.alt     YSI_g_sArgCount
	#emit LOAD.S.pri   0
	#emit ADD.C        12
	#emit ADD
	// "pri" now contains a pointer to the dynamic arguments.
	
	// Call "memcpy".  The final argument (the first push) is stupid big, way
	// bigger than it needs to be, but we know the destination is large enough
	// so there's no need to check and pass an accurate value, instead we can
	// just pass a "large enough" constant.
	#emit STACK        0
	#emit PUSH.C       1000000
	#emit PUSH         YSI_g_sStack
	#emit PUSH.C       0
	#emit PUSH.pri
	#emit PUSH.alt
	#emit PUSH.C       20
	#emit SYSREQ.C     memcpy
	#emit STACK        24
	
	// Call "CallLocalFunction"
	#emit PUSH.S       fmat
	#emit PUSH.S       function
	#emit LOAD.pri     YSI_g_sStack
	#emit ADD.C        8
	#emit PUSH.pri
	#emit SYSREQ.C     CallLocalFunction
	
	// Pop the stack.
	#emit MOVE.alt
	#emit LCTRL        5
	#emit SCTRL        4
	#emit MOVE.pri
	#emit RETN
	
	return 0;
}

stock va_SetTimerEx(const function[], interval, bool:repeating, const fmat[], va_:STATIC_ARGS)
{
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit DEC.alt
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 8.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.
	
	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD
	#emit ADD.C        0xFFFFFFFC // -4 adjustment for JIT.
	
	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         24 // (n + 1) * 4
	
	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        24 // (n + 1) * 4
	#emit SCTRL        4
	
	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH.S       repeating
	#emit PUSH.S       interval
	#emit PUSH.S       function
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.
	
	// Call the function.
	#emit SYSREQ.C     SetTimerEx
	#emit STOR.pri     YSI_g_sArgCount
	
	// Copy the data back.
	#emit STACK        0xFFFFFFFC // -4 adjustment for JIT.
	#emit STACK        0
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         24
	
	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN
	
	return 0;
}

stock va_format(out[], size, const fmat[], va_:STATIC_ARGS)
{
	//P:C(if (_:STATIC_ARGS < 1) P:W("No static args found, please add a dummy local"););
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.
	
	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD
	#emit ADD.C        0xFFFFFFFC // -4 adjustment for JIT.
	
	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         20 // (n + 1) * 4
	
	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        20 // (n + 1) * 4
	#emit SCTRL        4
	
	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH.S       size
	#emit PUSH.S       out
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.
	
	// Modify the heap to hold "locals".  This is for when the destination is a
	// local within the function that called us.
	#emit HEAP         0
	#emit STOR.alt     YSI_g_sHeap
	#emit LCTRL        4
	#emit SCTRL        2
	
	// Call the function.
	#emit SYSREQ.C     format
	#emit STOR.pri     YSI_g_sArgCount
	
	// Copy the data back.
	#emit LOAD.pri     YSI_g_sHeap
	#emit SCTRL        2
	#emit STACK        0xFFFFFFFC // -4 adjustment for JIT.
	#emit STACK        0
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         20
	
	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN
	
	return 0;
}

stock va_return(const fmat[], va_:STATIC_ARGS)
{
	static
		out[YSI_MAX_STRING * 8],
		size = sizeof (out);
	
	// Get the number of parameters - don't forget the hidden string return one.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.
	
	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.
	
	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD
	#emit ADD.C        0xFFFFFFFC // -4 adjustment for JIT.
	
	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         20 // (n + 1) * 4
	
	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        20 // (n + 1) * 4
	#emit SCTRL        4
	
	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH         size
	#emit PUSH.S       20 // Secret return parameter.
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.
	
	// Modify the heap to hold "locals".  This is for when the destination is a
	// local within the function that called us.
	#emit HEAP         0
	#emit STOR.alt     YSI_g_sHeap
	#emit LCTRL        4
	#emit SCTRL        2
	
	// Call the function.
	#emit SYSREQ.C     format
	
	// Copy the data back.
	#emit LOAD.pri     YSI_g_sHeap
	#emit SCTRL        2
	#emit STACK        0xFFFFFFFC // -4 adjustment for JIT.
	#emit STACK        0
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         20
	
	// Now do the real return, but without the costly string copying.
	#emit RETN
	return out;
}

stock va_strlen(arg)
{
	// Get the length of the string at the given position on the previous
	// function's stack (convenience function).
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SMUL.C     4
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      12
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     4
	// Call the function.
	#emit SYSREQ.C   strlen
	// Restore the stack to its level before we called this native.
	#emit STACK      8
	#emit RETN
	// Never called.
	return 0;
}

stock va_getstring(dest[], arg, len = sizeof (dest))
{
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SMUL.C     4
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      12
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the length for "strcat".
	#emit PUSH.S     len
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Load the address of the destination.
	#emit LOAD.S.alt dest
	// Blank the first cell so "strcat" behaves like "strcpy".
	#emit CONST.pri  0
	// Store the loaded number 0 to the loaded address.
	#emit STOR.I
	// Push the loaded address.
	#emit PUSH.alt
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     12
	// Call the function.
	#emit SYSREQ.C   strcat
	// Restore the stack to its level before we called this native.
	#emit STACK      16
}

stock PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, fmat[], va_args<>)
{
	return CreatePlayerTextDraw(playerid, x, y, va_return(fmat, va_start<4>));
}

stock Text:va_TextDrawCreate(Float:x, Float:y, fmat[], va_args<>)
{
	return TextDrawCreate(x, y, va_return(fmat, va_start<3>));
}

stock va_SendClientMessage(playerid, colour, const fmat[], va_args<>)
{
	return SendClientMessage(playerid, colour, va_return(fmat, va_start<3>));
}

stock va_SendClientMessageToAll(colour, const fmat[], va_args<>)
{
	return SendClientMessageToAll(colour, va_return(fmat, va_start<2>));
}

stock va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], va_args<>)
{
	return SendPlayerMessageToPlayer(playerid, senderid, va_return(fmat, va_start<3>));
}

stock va_SendPlayerMessageToAll(senderid, const fmat[], va_args<>)
{
	return SendPlayerMessageToAll(senderid, va_return(fmat, va_start<2>));
}

stock va_GameTextForPlayer(playerid, const fmat[], time, style, va_args<>)
{
	return GameTextForPlayer(playerid, va_return(fmat, va_start<4>), time, style);
}

stock va_GameTextForAll(const fmat[], time, style, va_args<>)
{
	return GameTextForAll(va_return(fmat, va_start<3>), time, style);
}

stock va_print(const fmat[], va_args<>)
{
	return print(va_return(fmat, va_start<1>));
}

stock va_fprintf(File:fhnd, const fmat[], va_args<>)
{
	return fwrite(fhnd, va_return(fmat, va_start<2>));
}

