/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "internal\y_funcinc"
#include "y_utils"

stock va_printf(const fmat[], va_:STATIC_ARGS)
{
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        4
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     printf
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
}

stock va_CallRemoteFunction(const function[], const fmat[], va_:STATIC_ARGS)
{
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	#emit PUSH.S       function
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        8
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     CallRemoteFunction
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
}

stock va_CallLocalFunction(const function[], const fmat[], va_:STATIC_ARGS)
{
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	#emit PUSH.S       function
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        8
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     CallLocalFunction
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
}

stock va_SetTimerEx(const function[], interval, bool:repeating, const fmat[], va_:STATIC_ARGS)
{
	static
		sRet;
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	#emit PUSH.S       repeating
	#emit PUSH.S       interval
	#emit PUSH.S       function
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        16
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     SetTimerEx
	#emit STOR.pri     sRet
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
	return sRet;
}

stock va_format(out[], size, const fmat[], va_:STATIC_ARGS)
{
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	#emit PUSH.S       size
	#emit PUSH.S       out
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        12
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     format
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
}

stock va_return(const fmat[], va_:STATIC_ARGS)
{
	static
		out[YSI_MAX_STRING * 8],
		size = YSI_MAX_STRING;
	new
		num_args,
		arg_start,
		arg_end;
	// Get the pointer to the number of arguments to the last function.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit MOVE.alt
	// Get the number of arguments.
	#emit LOAD.I
	#emit STOR.S.pri   num_args
	// Get the variable arguments (end).
	#emit ADD
	#emit STOR.S.pri   arg_end
	// Get the variable arguments (start).
	#emit LOAD.S.pri   STATIC_ARGS
	#emit SMUL.C       4
	#emit ADD
	#emit STOR.S.pri   arg_start
	// Using an assembly loop here screwed the code up as the labels added some
	// odd stack/frame manipulation code...
	while (arg_end != arg_start)
	{
		#emit MOVE.pri
		#emit LOAD.I
		#emit PUSH.pri
		#emit CONST.pri    4
		#emit SUB.alt
		#emit STOR.S.pri   arg_end
	}
	// Push the additional parameters.
	#emit PUSH.S       fmat
	#emit PUSH         size
	#emit PUSH.C       out
	// Push the argument count.
	#emit LOAD.S.pri   num_args
	#emit ADD.C        12
	#emit LOAD.S.alt   STATIC_ARGS
	#emit XCHG
	#emit SMUL.C       4
	#emit SUB.alt
	#emit PUSH.pri
	#emit MOVE.alt
	// This gets confused if you have a local variable of the same name as it
	// seems to factor in them first, so you get the offset of the local
	// variable instead of the index of the native.
	#emit SYSREQ.C     format
	// Clear the stack.
	#emit CONST.pri    4
	#emit ADD
	#emit MOVE.alt
	// The three lines above get the total stack data size, now remove it.
	#emit LCTRL        4
	#emit ADD
	#emit SCTRL        4
	// Now do the real return.
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
