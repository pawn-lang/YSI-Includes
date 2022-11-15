/*
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

#define __COMPILER_NESTED_ELLIPSIS (0)
#define __compiler_one_string_parameter:%8(%0,%1) (%0)
#define __COMPILER_STRING_RETURN(%0) return (__CompilerStringReturn(%0), __compiler_one_string_parameter:(%0))
#define __CompilerStringReturn("%0"%1);return%8(%8:(%3)) return $
#define __COMPILER_BUGGED_STRING_RETURN (1)
#define __COMPILER_BUGGED_SYSREQ (1)
#define __COMPILER_WARNING_SUPPRESSION (0)
#define __COMPILER_CONST_REF (0)
#define __COMPILER_sNAMEMAX (31)
#define __COMPILER_CONST_TAGGED (0)
#define __COMPILER___EMIT (0)

// It is sufficient simply for a variable to exist anywhere with the tag.
#define __COMPILER_TAG_DATA(%0,%1) stock const %0:__TAGOF__%0; stock %0:operator=(__CompilerDefault:a) return a, %0:(%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The old compiler has a bug when using <c>SYSREQ.C</c> - the natives aren't
 *   marked as used, so won't be included in the output if they aren't used
 *   normally elsewhere.  This function, on the old compiler, calls the natives
 *   defined in this file to ensure that they go in to the native function
 *   table.  However, they are called with nonsense parameters so this function
 *   must itself never be called.  That would normally mean that this is itself
 *   elided from the AMX, hence it is <c>public</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward @_y_funcinc_y_@();

public @_y_funcinc_y_@()
{
	new tmp[2];
	// This function calls any functions used in assembly code in YSI to ensure
	// that they are included in the native function table.  The newlines are to
	// prevent macro replacements.
	print
		(tmp);
	printf
		(tmp);
	strunpack
		(tmp, tmp);
	memcpy
		(tmp, tmp, 0, 0, 0);
	format
		(tmp, 0, tmp);
	strfind
		(tmp, tmp, false, 0);
	strcat
		(tmp, tmp, 0);
	strlen
		(tmp);
	CallRemoteFunction
		(tmp, tmp);
	CallLocalFunction
		(tmp, tmp);
	SetTimerEx
		(tmp, 0, false, tmp);
	heapspace
		();
	setproperty
		(0, tmp, 0, tmp);
	getproperty
		(0, tmp, 0, tmp);
	swapchars
		(0);
	strcmp
		(tmp, tmp);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <param name="str">String to return.</param>
 * <param name="size">Size of the string.</param>
 * <param name="dummy">Ignored parameter for raw string given sizes.</param>
 * <returns>
 *   string
 * </returns>
 * <remarks>
 *   The old compiler has a very annoying bug where returning a string from a
 *   function that takes variable parameters will not work correctly.  This is
 *   because string returns are done with a secret extra parameter but it is not
 *   correctly selected when the count is unknown or variable.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock __CompilerStringReturn(const str[], size = sizeof (str), dummy = 0)
{
	#pragma unused dummy
	#emit PUSH.S       size           // Push the first parameter.
	#emit PUSH.S       str            // Push the second parameter.
	#emit LOAD.S.alt   __frame_offset // Load the previous frame pointer.
	#emit MOVE.pri                    // Copy the pointer.
	#emit ADD.C        __args_offset  // Get the pointer to the parameter count.
	#emit LOAD.I                      // Load the parameter count.
	#emit ADD.C        __3_cells      // Adjust for the function header size.
	#emit ADD                         // Get the pointer to after the parameters.
	#emit LOAD.I                      // Load the pointer in the (secret) parameter.
	#emit PUSH.pri                    // Push the destination.
	#emit MOVE.alt                    // Make a copy of the pointer.
	#emit ZERO.pri                    // `pri = 0`.
	#emit STOR.I                      // Set the first cell of the target to NULL.
	#emit PUSH.C       __3_cells      // Push the parameters for `StrCpy`.
	#emit SYSREQ.C     strcat         // Call `strcat`.
	#emit LOAD.S.pri   __frame_offset // Reload the previous frame pointer.
	#emit SCTRL        __stk          // Wipe out the stack.
	#emit SCTRL        __frm          // Wipe out the frame (go to parent context).
	#emit RETN                        // Return (now within the parent context).
	return 0;
}

#if defined TAGOF
	#endinput
#endif

// Fix `tagof (Float:)` and `tagof (Float:x)` on the old compiler, without
// breaking any default arguments in (I think) any case.  This was very
// tricky, as adding any tags to `arg = tagof (param)` breaks the compiler's
// semantics and always returns the same tag.  So we have to detect
// `tagof (Tag:)` without detecting `tagof (var), Tag:a`, which the old code
// broke on.  This is normally easy, but we also have to do it without
// adding any tags before `tagof` in the base case.  So we always match `:`,
// then revert if there's a bracket between the `tagof` and the `:`.
#define __TAGOF__%0\32; __TAGOF__
#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__%0)

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <param name="a">Integer parameter.</param>
 * <param name="b">Fake tagged parameter.</param>
 * <returns>
 *   Are the values the same?
 * </returns>
 * <remarks>
 *   The code to fix <c>tagof (Tag:)</c> needed an extra tag for code generation
 *   reasons, but this tag must frequently be used as an integer.  Ensure that
 *   the common places it is used as a normal integer don't give any warnings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:operator==(_:a, __NO_TAGOF:b)
{
	return a == _:b;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <param name="a">Integer parameter.</param>
 * <param name="b">Fake tagged parameter.</param>
 * <returns>
 *   Are the values different?
 * </returns>
 * <remarks>
 *   The code to fix <c>tagof (Tag:)</c> needed an extra tag for code generation
 *   reasons, but this tag must frequently be used as an integer.  Ensure that
 *   the common places it is used as a normal integer don't give any warnings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:operator!=(_:a, __NO_TAGOF:b)
{
	return a != _:b;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <param name="a">Fake tagged parameter.</param>
 * <returns>
 *   The value as an integer.
 * </returns>
 * <remarks>
 *   The code to fix <c>tagof (Tag:)</c> needed an extra tag for code generation
 *   reasons, but this tag must frequently be used as an integer.  Ensure that
 *   the common places it is used as a normal integer don't give any warnings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _:operator=(__NO_TAGOF:a)
{
	return _:a;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_compilerdata</library>
 * <param name="a">Integer parameter.</param>
 * <returns>
 *   The value as a fake tagged value.
 * </returns>
 * <remarks>
 *   The code to fix <c>tagof (Tag:)</c> needed an extra tag for code generation
 *   reasons, but this tag must frequently be used as an integer.  Ensure that
 *   the common places it is used as a normal integer don't give any warnings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock __NO_TAGOF:operator=(_:a)
{
	return __NO_TAGOF:a;
}

