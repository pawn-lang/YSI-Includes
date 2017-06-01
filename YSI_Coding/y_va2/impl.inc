/**--------------------------------------------------------------------------**\
					===============================
					 y_va2 - Enhanced vararg code!
					===============================
Description:
	This library provides a new macro - the triple underscore (___) which fully
	passes all of a function's parameters on to another function.
	
	This is a replacement for all other solutions like y_va.
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
	01/06/17:
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
	___ - Passes all variable arguments to another function.
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

#if 0

	// Example:
	stock MyPrintf(const format[], {Float, File, _}:...)
	{
		// The triple underscore is used to mirror the triple dots in the
		// function definition.  You can't easily tell it is three from a
		// glance, but it is.
		printf(format, ___1); // Or `___(1)`.
		print("Printed many things");
		return 42;
	}

#endif

stock __VA__PUSH__(const staticParameters, const skippedParameters = 0)
{
	// Although "staticParameters" is "const", we actually rewrite the value at
	// the call site when the mode starts.  By default it is ALWAYS 0, because
	// we have no way to determine the true value at compile time.  We must
	// read it from the number of parameters given to the target function.
	// 
	// During the execution of this function, we have to actually modify our own
	// stack to make room UNDER it for all the parameters being pushed.  Then
	// when this function is returned from, the bottom of the stack already has
	// all the parameters on it.  Normally, because this function call is a
	// parameter to another function, its return value will also be pushed to
	// the stack, but we NOP that out at initialisation time.
	// 
	// Or entry to this function, the stack looks like:
	// 
	//   16 - skippedParameters.
	//   12 - staticParameters.
	//   08 - Parameter count in bytes (8).
	//   04 - Return address.
	//   00 - Pervious frame.
	//   
	// This means there is 20 bytes of information we need to move to globals,
	// since we are about to totally destroy our own stack.
	#emit POP.pri
	#emit STOR.pri YSI_g_sPreviousFrame
	#emit POP.pri
	#emit STOR.pri YSI_g_sReturnAddress
	#emit POP.pri
	#emit STOR.pri YSI_g_sParameterCount
	#emit POP.pri
	#emit STOR.pri YSI_g_sStaticParameters // (Will have been adjusted).
	#emit POP.pri
	#emit STOR.pri YSI_g_sSkippedParameters
	// The stack is now back to where it was before this function was called.
	// We must copy parameters from the previous stack to the current stack.
	// 
	// There are two methods for this - increase the stack and 'memcpy' in, or
	// loop over all the parameters and re-push them.  I suspect the memcpy
	// version MAY be faster, but there is some trickyness with the stack to
	// call a function while inserting in to the stack.  The best non-JIT method
	// would be `MOVS`, but that requires more run-time code modification, which
	// we can't do (I don't think, never ACTUALLY tried...).
	// 
	// So for now, just loop through them - I can improve the code later.
	static i;
	i = 0;
	#emit 
	#emit LREF.pri i
	#emit LOAD.pri i
	#emit ADD.C    0xFFFFFFFC // -4
	#emit STOR.pri i
	#emit 
	#emit 
	#emit 
	#emit 
	#emit 
	#emit 
	{}
	// We need to tell the real call how many parameters are being pushed, via
	// the hidden 'numargs' parameter.  The first obvious solution would be
	// code rewriting to change the 'PUSH.C', but that doesn't work with JIT or
	// recursion.  The next obvious solution is a global with 'PUSH', but that
	// again doesn't work with recursion and is tricky with nested calls.  The
	// only other solution is to create a local variable and use that.  This
	// means pushing extra data and shifting and modifying code to remove the
	// extra data from the stack after the 'PUSH.S' and 'CALL'.  This is by far
	// the trickiest method, but also the most robust.
	// 
	// Nested calls are still a problem - the outer call must allocate all the
	// stack data for all of the parameter counts at once so that they have a
	// constant offset from the current frame pointer.  This is TODO:  I want it
	// working for just one outer call first before I start complicating it.
	// This also means that the first version will use a global variable and
	// ignore recursion and code shifting.
	// 
	// Return from this function.  Don't bother putting the paramters back on
	// the stack to be removed again.
	#emit PUSH.C 0
	#emit PUSH YSI_g_sReturnAddress
	#emit PUSH YSI_g_sPreviousFrame
	#emit RETN
	return 0;
}

// Add a scanner to find the `___` function call.

// Add a scanner to find the next point at which the stack is smaller than it
// was when `___` was called.  We have to be careful here as there may have been
// another `___` call in the interim, which would have been fully resolved
// first.  As in:
// 
//   Func1(Func2(___), ___);
// 
// `Func1`'s `___` will be first in the code, but before finding the call to
// `Func1` itself, we would see the inner `___` AND the inner function call.

