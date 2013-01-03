/*----------------------------------------------------------------------------*\
					===================================
					 y_inline - PAWN inline functions.
					===================================
Description:
	This library allows a user to write inline functions in their script.  It
	first detects all inline functions and generates data on them, such as
	parameter counts and addresses.  When an inline function is passed in code
	its current context data is stored.  Finally, when an inline function is
	found to be called at some point its current local stack is stored in global
	memory.  When the function actually is called, the stack is restored, and
	additional parameters which are the inline function parameters, are passed.
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
	
	The Original Code is the YSI AMX include.
	
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
	20/10/12:
		Fixed a bug with "Callback_Release" with public functions.
	15/11/11:
		Changed the precedence of "using" types.
	19/09/11:
		First version
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "internal\y_funcinc"
#include "y_amx"
#include "y_utils"
#include "y_malloc"
#include "y_hooks"

#if defined YSI_MALLOC_SECURE
	#error y_inline does not work with "YSI_MALLOC_SECURE" defined.
#endif

// "with inline X"
// "with public X"
// %0 = " in" or " pub" (ignored).
// "%1 = "ne X" or "c X" (makes a macro).

#define using%0) callback_tag:@Ik:@Il:%0)

// Get ONLY this ONE parameter (this is a VERY important stage)!
#define @Ik:@Il:%0, @Ip:@Iq:@Im:@Io:@Iw:|||%0|||,
#define @Il:%0) @Ip:@Iq:@Im:@Io:@Iw:|||%0|||)

// You can use "using InlineFunc" or the faster "using inline InlineFunc".
/*#define @Ip:@Iq:@Im:@Io:@Iw:|||%0anonymous%1||| @Iu:@Iv:%0NULL%1||||
#define @Iq:@Im:@Io:@Iw:|||%0callback%1||| @Ir:@Is:%1||||
#define @Im:@Io:@Iw:|||%0inline%1||| @Iu:@Iv:%0%1||||
#define @Io:@Iw:|||%0public%1||| @Ir:@Is:%1||||
#define @Iw:|||%1||| @In:@It:%1||||*/

#define @Ip:@Iq:@Im:@Io:@Iw:|||%0inline%1||| @Iu:@Iv:%0%1||||
#define @Iq:@Im:@Io:@Iw:|||%0public%1||| @Ir:@Is:%1||||
#define @Im:@Io:@Iw:|||%0anonymous%1||| @Iu:@Iv:%0NULL%1||||
#define @Io:@Iw:|||%0callback%1||| @Ir:@Is:%1||||
#define @Iw:|||%1||| @In:@It:%1||||

// Callbacks with "On" in the name (often overidden by y_hooks and ALS).
#define @Ir:@Is:%0On%1|||| @In:@It:#%0"On"#%1||||
#define @Is:%0|||| @In:@It:#%0|||| //Using_unknown_callback

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:@It:%0(%1)||||%2) %0%2,.bExtra=true,.extra=%1)
#define @It:%0|||| %0

// Inline function surpressing closures.
#define @Iu:@Iv:%0$%1|||| (J@=0,_:@In:@It:%1|||| _Y_INLINE_END
#define @Iv:%1|||| (J@=1,_:@In:@It:%1|||| _Y_INLINE_END

// Defer adding the close bracket till after other macros have run.
#define _Y_INLINE_END )

#define INLINE_LOOP_PATTERN_0 0xA1E7C013
#define INLINE_LOOP_PATTERN_1 0x42424242
#define INLINE_LOOP_PATTERN_2 0x13C0E7A1
#define INLINE_LOOP_PATTERN_3 0x21495359

//#define INLINE_LOOP_PATTERNS INLINE_LOOP_PATTERN_0,INLINE_LOOP_PATTERN_1,INLINE_LOOP_PATTERN_2,INLINE_LOOP_PATTERN_3

// This code uses a specialisation of my "tag macros" technique, embedding the
// macro names in to a string instead of using them as tags.  This does mean
// that they will likely end up in the final AMX (unlike tag macros) but this
// seems to be the only way to get this to work that I can see as there is no
// variable reading involved.

// The "inline" macro only has ":...", whereas the "anonymous" macro has ":...:"
// because "inline" gets its second colon later on after all the parameter tag-
// style macros.  The structure for these extra cells is:
//  
//  0 - Colon.
//  1 - Pointer to next function name.
//  2 - Pointer the the function.
//  3 - Cells in the enclosing function at this point (passed and declared).
//  4 - Parameters format.
//  
#define inline%0(%1) new %0__;static const%0[]=#%0":..."#_YI@CP;for(new%1,,;Inline_Loop(.y=%0__,.f=%0);)

#define callback:%0) const callback_tag:callback_check:%0£££
#define callback_tag:callback_check:%0,%1£££ callback_tag:%0[],%1)
#define callback_check:%0£££ %0[])

#define anonymous%0(%1) new __anonVar;Q@=#_YI@CA;for(new%1,,;Inline_Loop(.y=__anonVar,.f=":...:"#);)

#define _YI@CP;for(new%0,%1; @Ia#@Ib#@Ic#@Id#:;for(new @Iz|||%0|||%1;

#define _YI@CA;for(new%0,%1; @If#@Ig#@Ih#@Ii#:;for(new @Iz|||%0|||%1;

// Detect 0 parameters.
#define @Ia#@Ib#@Ic#@Id#:;for(new%0||||||,;%1;) :;for(;%1;)

// Detect strings (no array support YET).
#define @Ib#@Ic#@Id#%9;for(new%0|||%1string:%2[%3]|||%4,%5; @Ib#@Ic#@Id#%9s;for(new%0,%2[YSI_MAX_STRING]|||%4|||%5;
// Detect end of line.
#define @Ic#@Id#%9;for(new%0|||%2|||%4,%5; @Ib#@Ic#@Id#%9i;for(new%0,%2|||%4|||%5;
// Detect everything else.
#define @Id#%9;for(new%0||||||; %9;for(new %0;

// Drop the leading comma on the parameter list.
#define @Iz,

// Detect 0 parameters.
#define @If#@Ig#@Ih#@Ii#:;for(new%0||||||,;%1;) :;for(;%1;)

// Detect strings (no array support YET).
#define @Ig#@Ih#@Ii#%9;for(new%0|||%1string:%2[%3]|||%4,%5;Inline_Loop(%6#%7) @Ig#@Ih#@Ii#%9;for(new%0,%2[YSI_MAX_STRING]|||%4|||%5;Inline_Loop(%6#%7s)
// Detect end of line.
#define @Ih#@Ii#%9;for(new%0|||%2|||%4,%5;Inline_Loop(%6#%7) @Ig#@Ih#@Ii#%9;for(new%0,%2|||%4|||%5;Inline_Loop(%6#%7i)
// Detect everything else.
#define @Ii#%9;for(new%0||||||; ;for(new%0;

// Drop the leading comma on the parameter list.
#define @Iz,

static stock
	YSI_g_sFirstFunc = -1,
	YSI_g_sInInline = 0,
	//YSI_g_sLastFunc = -1,
	YSI_g_sReturn;

enum e_CALLBACK_FLAGS (<<= 1)
{
	// All this is required to correctly design the call stack.
	e_CALLBACK_FLAGS_PUSHED  = 0x000000FF, // Parameters pushed to caller.
	e_CALLBACK_FLAGS_CREATED = 0x0FFFFF00, // Data size declared in caller.
	e_CALLBACK_FLAGS_PUBLIC  = 0x10000000  // Is a public function.
	//e_CALLBACK_FLAGS_INLINE                // Is an inline function.
}

enum E_CALLBACK_DATA
{
	e_CALLBACK_FLAGS:E_CALLBACK_DATA_FLAGS,
	E_CALLBACK_DATA_POINTER, // Pointer to the function.
	E_CALLBACK_DATA_FORMAT,  // Compressed destination format.
	Alloc:E_CALLBACK_DATA_ALLOC // Where our closure is stored.
}

static stock Inline_DoFormat(data[])
{
	// This function encodes the data format in to a single cell.  The format is:
	//  
	//  1111111001
	//  
	// Leading 1s indicate no data.  The 0 immediately following the leading 1s
	// indicates the start of the format section (but is not PART of the format
	// section).  The remaining bits represent either strings (1) or non-strings
	// (0).  For example "(a, string:b, c)" would be:
	//  
	//  1..10010
	//  
	// Where "1..1" indicates full-cell padding of 1s.  From this it is known that
	// the function takes three parameters: non-string, string, non-string.  In
	// addition, as strings in inline functions MUST use the "string:" tag, it is
	// known that ALL strings will ALWAYS be 128 (or "YSI_MAX_STRING") cells big.
	new
		pos = strfind(data, ":"),
		//len = 0, //strlen(data),
		//bit = 1,
		total = 1;
	//printf("%s", data);
	//P:C(if (len - pos - 1 > 30) P:E("Inline functions only support up to 30 parameters"););
	if (pos != -1)
	{
		for ( ; ; )
		{
			// Now matchs the compile-time code much closer.
			switch (data[++pos])
			{
				case '\0':
				{
					break;
				}
				case 's':
				{
					total <<= 1;
				}
				default:
				{
					total = (total << 1) | 1;
				}
			}
		}
	}
	// Store the compressed format, also instantly end the string.
	data[0] = ~total;
	data[1] = '\0';
	//printf("%x", data[0]);
	return 1;
}

static stock Inline_FindFunction(const data[], const name[], address)
{
	new
		value,
		len = strlen(name),
		tmp,
		candidate = cellmax,
		ret = -1;
	#emit LOAD.S.pri data
	#emit STOR.S.pri value
	// Check the "pointer" is valid.
	P:3("Inline_FindFunction called: %08x, %s, %s", value, data, name);
	while (value != -1)
	{
		if (strcmp(name, data, false, len) || data[len] != ':')
		{
			value = data[strlen(data) - 4];
		}
		else
		{
			/*printf("format = %04x%04x", data[len + 4] >>> 16, data[len + 4] & 0xFFFF);
			printf("%d", data[len + 1]);
			printf("%d", data[len + 2]);
			printf("%d", data[len + 3]);
			printf("%d", data[len + 4]);*/
			// Found a candidate.  Now only finds the closest match BEFORE the call.
			tmp = address - data[len + 2];
			//if (0 < tmp < candidate)
			if (-5000 < tmp < 5000)
			{
				// Constrain the checks to +-5000 because of square integer limits and
				// to help reduce clashes.
				if ((tmp *= tmp) < candidate)
				{
					ret = value;
					candidate = tmp;
					//printf("candidate: %x", ret);
				}
			}
			value = data[len + 1];
		}
		// Move on to the next "pointer".
		#emit LOAD.S.pri value
		#emit STOR.S.pri data
	}
	return ret;
}

static stock Inline_FindAnonymous(const data[], address)
{
	new
		value,
		tmp,
		candidate = cellmax,
		ret = -1;
	#emit LOAD.S.pri data
	#emit STOR.S.pri value
	// Check the "pointer" is valid.
	//printf("Inline_FindAnonymous %s %d %d", data, address, value);
	while (value != -1)
	{
		// Check if this is anonymous.
		//printf("%d %s %d %d %d", value, data, address, ret, candidate);
		if (data[0] == ':')
		{
			// Found a candidate.
			tmp = data[2] - address;
			// Make sure this is the closest anonymous function AFTER the return.  We
			// don't need "0 <=" as it will never be INSTANTLY after the return
			// address due to the required "Inline_Loop" call.
			if (0 < tmp < candidate)
			{
				ret = value;
				candidate = tmp;
			}
		}
		//printf("%d %d %d,%d,%d,%d,%d", strlen(data), strlen(data) - 4, data[0], data[1], data[2], data[3], data[4]);
		value = data[strlen(data) - 4];
		// Move on to the next "pointer".
		#emit LOAD.S.pri value
		#emit STOR.S.pri data
	}
	//printf("Found anon: %d", ret);
	return ret;
}

forward _Inline_FixCompiler@@();

public _Inline_FixCompiler@@()
{
	// Call the function above at least once so the address exists in tables.  But
	// never ACTUALLY call it at run-time (don't call this public function).
	Inline_DoFormat("");
	Inline_FindFunction("", "", 0);
	Inline_FindAnonymous("", 0);
	//memcpy("", "", 0, 0, 0);
}

hook OnScriptInit()
{
	P:2("Inline_OnScriptInit");
	static
		// Default settings.
		sSearch1[] =
			{
				AMX_PUSH_C, INLINE_LOOP_PATTERN_3,
				AMX_PUSH_C, INLINE_LOOP_PATTERN_2,
				AMX_PUSH_C, INLINE_LOOP_PATTERN_1,
				AMX_PUSH_C, INLINE_LOOP_PATTERN_0,
				AMX_PUSH_C, 0x18,
				AMX_CALL
			},
		// Debug settings.
		sSearch2[] =
			{
				AMX_CONST_PRI, INLINE_LOOP_PATTERN_3,
				AMX_PUSH_PRI,
				AMX_CONST_PRI, INLINE_LOOP_PATTERN_2,
				AMX_PUSH_PRI,
				AMX_CONST_PRI, INLINE_LOOP_PATTERN_1,
				AMX_PUSH_PRI,
				AMX_CONST_PRI, INLINE_LOOP_PATTERN_0,
				AMX_PUSH_PRI,
				AMX_PUSH_C, 0x18,
				AMX_CALL
			};
	// Different optimisation levels produce different sensibilities of code.
	if (Inline_DoSearch(sSearch1, 3) == -1)
	{
		// Pass the number of extra instructions before this code block.
		Inline_DoSearch(sSearch2, 5);
	}
	/*new
		p0 = Inline_DoSearch(sSearch1),
		// I could actually detect compilation flags in this way!
		p1 = Inline_DoSearch(sSearch2);
	if (p0 == -1 && p1 != -1)
	{
		// Compiled with "-d3".  That's interesting but ultimately pointless.
		// And I can't detect this if they have no inline functions.
	}*/
}

//pp(d, str[])
//{
//	#emit LOAD.S.pri        d
//	#emit STOR.S.pri        str
//	printf("data = %08x, %x,%x,%x,%x,%x,%x", d, str[0], str[1], str[2], str[3], str[4], str[5]);
//}

static stock Inline_DoSearch(sSearch[], neg, size = sizeof (sSearch))
{
	P:4("Inline_DoSearch called");
	new
		//str[32],
		addr,
		data,
		func;
	static
		last = -1;
	//printf("FIND FUNC: %s", sSearch);
	while (AMX_TraceCode(sSearch, addr, func, size))
	{
		P:4("Inline_DoSearch: %d %d %d", addr, func, size);
		// Get the function return address (make sure "pri" is always non-zero).
		func = addr + ((size + 1) * 4);
		//printf("stored function at %x", func);
		// Get the address of the last parameter.
		addr += (AMX_HEADER_COD - (neg * 4));
		//printf("FOUND FUNC: %d", addr);
		// Get the value of the last parameter.
		#emit LREF.S.pri        addr
		#emit STOR.S.pri        data
		// PERFECT!  This assembly code worked FIRST TIME to correctly display
		// both the address and contents of the loaded string!  Amazingly it
		// worked for anonymous functions too...
		//#emit PUSH.S            data
		//#emit POP.pri
		// Anyway, now we need to see if this is a named or anonymous function
		// and plan accordingly.  We don't need all the complex code of the
		// previous inline version.  If we get a function call which takes an
		// anonymous function, just assume it is the next one found in the list
		// of stored inline function addresses.  This has the HUGE added
		// advantage of allowing small bits of extra code to appear between the
		// function call and the inline function - i.e. we can allow return
		// values and allsorts now (including having functions taking anonymous
		// functions themselves being used as parameters).
		//new
		//	pos = strfind(
		static const
			scSearch[] = ":";
		new
			pos = 0;
		#emit PUSH.C         0
		#emit PUSH.C         0
		#emit PUSH.C         scSearch
		#emit PUSH.S         data
		#emit PUSH.C         16
		#emit SYSREQ.C       strfind
		#emit STOR.S.pri     pos
		#emit STACK          20
		//printf("pos = %d, %d", pos, last);
		if (pos != -1)
		{
			if (last == -1)
			{
				YSI_g_sFirstFunc = data;
			}
			else
			{
				#emit LOAD.S.pri data
				#emit SREF.pri   last
			}
			// Equivalent to: "data[pos + 1] = -1;" (1 cell = 4 bytes).
			data += pos * 4 + 4;
			#emit CONST.pri    0xFFFFFFFF
			#emit SREF.S.pri   data
			// Equivalent to: "data[pos + 2] = func;"
			last = data;
			data += 4;
			//printf("pos = %d, %d", data, func);
			#emit LOAD.S.pri   func
			#emit SREF.S.pri   data
			// Now find and compress the format specifier (backwards).
			// Now compress the format in to a single cell (up to 32 parameters).
			#emit LOAD.S.pri     data
			#emit ADD.C          8//4
			#emit PUSH.pri
			#emit PUSH.C         4
			// Using "CALL Inline_DoFormat" doesn't work, so do the next best thing.
			#emit LCTRL          6
			#emit ADD.C          28
			#emit PUSH.pri
			#emit CONST.pri      Inline_DoFormat
			#emit SCTRL          6
			//pp(data - 8, str);
		}
		// Move on to find the next value.  24 is larger than both 12 and 20,
		// but is still a little hard-coded to the known code types.
		addr -= (AMX_HEADER_COD - 24);
	}
	return last;
}

stock Inline_Loop(p0 = INLINE_LOOP_PATTERN_0, p1 = INLINE_LOOP_PATTERN_1, p2 = INLINE_LOOP_PATTERN_2, p3 = INLINE_LOOP_PATTERN_3, &y = 0, volatile const f[] = "")
//stock Inline_Loop(p0, p1, p2, p3, &__yil, volatile const format[])
{
	#pragma unused p0, p1, p2, p3
	//#emit LOAD.S.pri    4
	//#emit STOR.S.pri    p0
	//printf("ret: %d %d", p0, YSI_g_sInInline);
	if (y)
	{
		/*#emit LOAD.S.alt 0
		#emit MOVE.pri
		#emit ADD.C      4
		#emit LOAD.I
		#emit XCHG
		#emit LOAD.I
		#emit STOR.S.pri p0
		#emit MOVE.pri
		#emit STOR.S.pri p1
		printf("%d %d", p0, p1);*/
		// Somehow I need to check 
		#emit LOAD.S.alt 0
		#emit MOVE.pri
		#emit ADD.C      4
		#emit LOAD.I
		#emit XCHG
		#emit LOAD.I
		#emit SCTRL      5
		#emit MOVE.pri
		#emit SCTRL      6
	}
	y = 1;
	static const
		scSearch[] = ":";
	// This function needs to be modified to store the stack size at this point
	// and write it to the relevant slot (easy since the relevant slot is
	// passed).  I know "volatile const" makes no sense, but "const" is for the
	// compiler, "volatile" is to show that really it does change.
	#emit LOAD.S.pri    0
	#emit ADD.C         8
	#emit LOAD.I
	#emit PUSH.pri
	// Get the local variable sizes.  Need to allocate the data somewhere.
	#emit LCTRL         5
	#emit LOAD.S.alt    0
	// Subtract the parameters passed to this function.
	#emit ADD.C         36 // 6 * 4 + 12
	#emit SUB.alt
	#emit PUSH.pri
	// Do strfind.
	#emit PUSH.C        0
	#emit PUSH.C        0
	#emit PUSH.C        scSearch
	#emit PUSH.S        f
	#emit PUSH.C        16
	#emit SYSREQ.C      strfind
	#emit STACK         20
	// Save the data.
	#emit CONST.alt     4
	#emit SMUL
	#emit ADD.C         12
	#emit LOAD.S.alt    f
	#emit ADD
	#emit STOR.S.pri    f
	#emit POP.alt
	#emit SHL.C.alt     6
	#emit POP.pri
	#emit SHR.C.pri     2
	#emit ADD
	#emit SREF.S.pri    f
	return 0;
}

stock Callback_Get(callback:name, result[E_CALLBACK_DATA], expect = -1)
{
	new
		func,
		num,
		pos;
	P:2("Callback_Get called: %s %04x%04x", _:name, expect >>> 16, expect & 0xFFFF);
	if (isnull(_:name))
	{
		// Anonymous inline.  Need to find the next available inline function based
		// on the return address of the calling function.
		// Get the return address.
		#emit LOAD.S.pri 0
		#emit ADD.C      4
		#emit LOAD.I
		// Call the function.
		#emit PUSH.pri
		//#emit PUSH.S     name
		#emit PUSH       YSI_g_sFirstFunc
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit CONST.pri  Inline_FindAnonymous
		#emit SCTRL      6
		#emit STOR.S.pri func
		if (func == -1)
		{
			return 0;
		}
		// Save the data.
		func += 2 * 4;
		#emit LREF.S.pri func
		#emit STOR.S.pri pos
		result[E_CALLBACK_DATA_POINTER] = pos;
		// Save the function parameters.
		func += 4;
		#emit LREF.S.pri func
		#emit STOR.S.pri pos
		result[E_CALLBACK_DATA_FLAGS] = e_CALLBACK_FLAGS:pos;
		func += 4;
		#emit LREF.S.pri func
		#emit STOR.S.pri pos
		result[E_CALLBACK_DATA_FORMAT] = pos;
		//printf("%x %x", expect, pos);
		if (expect != -1 && pos != expect)
		{
			P:E("Format specifier didn't match on anonymous function");
		}
		new
			mask = 0x80000000;
		// Skip leading 1s.
		while (pos & mask)
		{
			mask >>>= 1;
		}
		// Skip delimiting 0.
		mask >>>= 1;
		while (mask)
		{
			if (pos & mask)
			{
				num += YSI_MAX_STRING;
			}
			else
			{
				++num;
			}
			mask >>>= 1;
		}
	}
	else
	{
		pos = strfind(name, ":");
		P:5("Callback_Get: %d, %d, %d, %d, %04x%04x", _:name[pos + 1], _:name[pos + 2], _:name[pos + 3] >>> 8, _:name[pos + 3] & 0xFF, _:name[pos + 4] >>> 16, _:name[pos + 4] & 0xFFFF);
		if (pos == -1)
		{
			if (AMX_GetPublicPointer(0, pos, name))
			{
				// Public function, use standard callback techniques (well, psudo-
				// standard, just store the address and use SCTRL manipulation).
				result[E_CALLBACK_DATA_POINTER] = pos;
				result[E_CALLBACK_DATA_FLAGS]   = e_CALLBACK_FLAGS_PUBLIC;
				result[E_CALLBACK_DATA_FORMAT]  = expect;
				return 1;
			}
			else
			{
				P:5("Callback_Get: Not got");
				// Get the caller frame.
				#emit LOAD.S.pri 0
				// Get the caller return.
				#emit ADD.C      4
				#emit LOAD.I
				// Now find the closest item with the correct name.  Hopefully 99% of
				// the time there will only be one function with this name anywhere
				// NEAR the return address, so we can use that one.  Otherwise we will
				// just have to hope that the closest is correct (maybe add a check to
				// see if it's too close, and if so alert the user).
				#emit PUSH.pri
				#emit PUSH.S     name
				#emit PUSH       YSI_g_sFirstFunc
				#emit PUSH.C     12
				#emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri
				#emit CONST.pri  Inline_FindFunction
				#emit SCTRL      6
				#emit STOR.S.pri func
				// So now "func" is the address of the handle to the nearest data we can
				// extract all the relevant data.
				if (func == -1)
				{
					P:5("Callback_Get: inline/public not found");
					return 0;
				}
				P:5("Callback_Get: inline/public found: %08x", func);
				// Save the function pointer.
				func += strlen(name) * 4 + 2 * 4;
				P:5("Callback_Get: inline/public found: %08x", func);
				//#emit LREF.S.pri func
				//pos = 444;
				#emit LOAD.S.pri func
				#emit LOAD.I
				#emit STOR.S.pri pos
				//printf("%d", pos);
				result[E_CALLBACK_DATA_POINTER] = pos;
				// Save the function parameters.
				func += 4;
				#emit LREF.S.pri func
				#emit STOR.S.pri pos
				//printf("%d", pos);
				result[E_CALLBACK_DATA_FLAGS]  = e_CALLBACK_FLAGS:pos;
				// Save the function format.
				func += 4;
				//--pos;
				#emit LREF.S.pri func
				#emit STOR.S.pri pos
				//printf("%d", pos);
				result[E_CALLBACK_DATA_FORMAT]  = pos;
				if (expect != -1 && pos != expect)
				{
					P:E("Format specifier didn't match on inline function %s: %04x%04x != %04x%04x", name, pos >>> 16, pos & 0xFFFF, expect >>> 16, expect & 0xFFFF);
				}
				new
					mask = 0x80000000;
				// Skip leading 1s.
				while (pos & mask)
				{
					mask >>>= 1;
				}
				// Skip delimiting 0.
				mask >>>= 1;
				while (mask)
				{
					if (pos & mask)
					{
						num += YSI_MAX_STRING;
					}
					else
					{
						++num;
					}
					mask >>>= 1;
				}
			}
		}
		else
		{
			// Named and qualified inline function.  Should also include the correct
			// addresses.  By FAR the fastest method as we already have all the data.
			result[E_CALLBACK_DATA_POINTER] = name[pos + 2];
			result[E_CALLBACK_DATA_FLAGS]   = e_CALLBACK_FLAGS:name[pos + 3];
			new
				form = name[pos + 4];
			result[E_CALLBACK_DATA_FORMAT]  = form;
			if (expect != -1 && form != expect)
			{
				P:E("Format specifier didn't match on inline function %s", name);
			}
			// Get the size of inline function parameters:
			new
				mask = 0x80000000;
			// Skip leading 1s.
			while (form & mask)
			{
				mask >>>= 1;
			}
			// Skip delimiting 0.
			mask >>>= 1;
			while (mask)
			{
				if (form & mask)
				{
					num += YSI_MAX_STRING;
				}
				else
				{
					++num;
				}
				mask >>>= 1;
			}
		}
	}
	// Now we need to somehow store all this data somewhere (including, for
	// speed, the extra data involved in calling a function).  Here "pos" is the
	// number of bytes pushed to the owning function.
	P:6("%04x%04x %04x%04x", _:result[E_CALLBACK_DATA_FLAGS] >>> 16, _:result[E_CALLBACK_DATA_FLAGS] & 0xFFFF, (num >>> 8), (num << 8) & 0xFFFF);
	result[E_CALLBACK_DATA_FLAGS] -= e_CALLBACK_FLAGS:(num << 8);
	pos = _:result[E_CALLBACK_DATA_FLAGS];
	// Get the size of the closure.
	func = (pos & 0xFF);
	pos = (pos >>> 8); // - num;
	func = func + pos + 3;
	new
		Alloc:alloc = malloc(func);
	if (alloc == NO_ALLOC)
	{
		return 0;
	}
	result[E_CALLBACK_DATA_ALLOC] = alloc;
	// Now we need to copy the data from the previous-but-one frame to this
	// allocated location.  Copy the whole lot, including passed parameters.
	#emit LOAD.S.pri          pos
	#emit SMUL.C              4
	#emit MOVE.alt
	#emit LOAD.S.pri          0
	#emit LOAD.I
	#emit SUB
	#emit STOR.S.pri          name
	memcpy(YSI_gMallocMemory[_:alloc], name, 0, func * 4, func);
	return 1;
}

stock Callback_Release(const input[E_CALLBACK_DATA])
{
	if (!(input[E_CALLBACK_DATA_FLAGS] & e_CALLBACK_FLAGS_PUBLIC))
	{
		// Publics don't have any stored data.
		free(input[E_CALLBACK_DATA_ALLOC]);
	}
}

stock Callback_Call(const result[E_CALLBACK_DATA], GLOBAL_TAG_TYPES:...)
{
	// Call the function with the given data.  We need some serious stack
	// manipulation skills in here to make it all work.
	//printf("Calling function at %d", _:result[E_CALLBACK_DATA_FLAGS]);
	if (result[E_CALLBACK_DATA_FLAGS] & e_CALLBACK_FLAGS_PUBLIC)
	{
		// I think I've got an even better way.  NOPE!  None of this code will
		// work because all the parameters are passed by reference, not by
		// value!  This is VERY VERY bad!  D'oh!  Good thing I kept a copy of
		// the old code!  Shame, this would have been very elegant.  Sweet, it
		// seemed to work as well!  Maybe I could just do some similar in-line
		// variable modifications.
		new
			par,
			pointer = result[E_CALLBACK_DATA_POINTER],
			mask = result[E_CALLBACK_DATA_FORMAT];
		// Destroy one parameter.
		//#emit PUSH.S          8
		#emit LOAD.S.alt      8
		#emit PUSH.alt
		//#emit ADD.C      0xFFFFFFFC
		//#emit PUSH.pri
		// Move the return address.
		#emit LOAD.S.pri      4
		#emit STOR.S.pri      8
		// Move the frame.
		#emit LOAD.S.pri      0
		#emit STOR.S.pri      4
		// Fix the parameters.
		#emit LCTRL           5
		#emit ADD
		#emit ADD.C           12
		#emit STOR.S.pri      par
		// Get the jump address.
		//while (mask != ~1)
		// If no format has been provided, just guess and pass every parameter
		// by reference (as they are passed to here).
		while (mask != -1)
		{
			par -= 4;
			if (!(mask & 1))
			{
				#emit LREF.S.pri      par
				#emit LOAD.I
				#emit SREF.S.pri      par
			}
			mask >>= 1;
		}
		//#emit LOAD.S.pri      8
		#emit POP.pri
		#emit ADD.C           0xFFFFFFFC
		#emit STOR.S.pri      12
		//#emit ADD.C      4
		//#emit ADD.C      4
		//#emit MOVE.alt
		#emit LOAD.S.alt      pointer
		// Mangle the stack (no variables from here).
		#emit LCTRL           5
		#emit ADD.C           4
		#emit SCTRL           4
		#emit SCTRL           5
		// Jump to new code (after "PROC").
		#emit MOVE.pri
		#emit ADD.C           4
		#emit SCTRL           6
		// Will never be called.
		//#emit RETN
	}
	else
	{
		new
			size = _:result[E_CALLBACK_DATA_FLAGS],
			num  = 0,
			stack,
			mask = 0x80000000,
			addr,
			tmp;
			//YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		//	ininline = YSI_g_sInInline;
		YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		//printf("Calling function at 0x%08x", YSI_g_sInInline);
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		#emit LCTRL      4
		#emit STOR.S.pri stack
		#emit LOAD.S.alt size
		#emit SUB
		#emit STOR.S.pri addr
		// Add more data for additional parameters.
		#emit SCTRL      4
		//#emit LCTRL      4
		size = result[E_CALLBACK_DATA_FORMAT];
		#emit LCTRL      5
		#emit ADD.C      16
		#emit STOR.S.pri tmp
		// OK, now the fun bit!
		while (size & mask)
		{
			mask >>>= 1;
		}
		mask >>>= 1;
		while (mask)
		{
			if (size & mask)
			{
				num += YSI_MAX_STRING;
				addr -= YSI_MAX_STRING * 4;
				//printf("copying string");
				#emit LOAD.S.pri addr
				#emit SCTRL      4
				// Copy the data.
				#emit PUSH.C     130
				#emit PUSH.C     520
				#emit PUSH.C     0
				#emit LREF.S.pri tmp
				#emit PUSH.pri
				#emit PUSH.S     addr
				#emit PUSH.C     20
				#emit SYSREQ.C   memcpy
				#emit STACK      24
				//printf("finished");
			}
			else
			{
				num += 1;
				addr -= 1 * 4;
				#emit LREF.S.pri tmp
				#emit LOAD.I
				#emit PUSH.pri
			}
			mask >>>= 1;
			tmp += 4;
		}
		#emit LCTRL      5
		#emit STOR.S.pri tmp
		num *= 4;
		addr += num;
		// "addr" now contains the params stack address, "stack" contains the
		// starting stack address.  This code technically pushes an incorrect
		// destination size (it's 4x too big), but as the bytes to copy is
		// smaller this is not important.
		// Set the frame pointer.
		size = _:result[E_CALLBACK_DATA_FLAGS];
		#emit LOAD.S.pri size
		#emit SHR.C.pri  8
		#emit SHL.C.pri  2 // NOT SHR 6
		#emit LOAD.S.alt addr
		#emit ADD
		#emit STOR.S.pri tmp
		// Copy the data.
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		num = _:result[E_CALLBACK_DATA_ALLOC];
		#emit LOAD.S.pri size
		#emit PUSH.pri
		#emit PUSH.pri
		#emit PUSH.C     0
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri num
		#emit IDXADDR
		#emit PUSH.pri
		#emit PUSH.S     addr
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
		// Store the return frame.
		#emit LOAD.S.alt tmp
		#emit LCTRL      5
		#emit STOR.I
		#emit MOVE.pri
		#emit ADD.C      4
		#emit MOVE.alt
		// Get the return address and call the function.
		#emit LCTRL      6
		#emit ADD.C      48              // 8
		#emit STOR.I                     // 12
		#emit LOAD.alt   YSI_g_sInInline // 20
		#emit LOAD.S.pri tmp             // 28
		#emit SCTRL      5               // 36
		#emit MOVE.pri                   // 40
		#emit SCTRL      6               // 48
		// Restore the stack.
		//printf("one");
		#emit LOAD.S.pri stack
		#emit SCTRL      4
		//printf("two");
		//YSI_g_sInInline = ininline;
	}
}

// HOPEFULLY will derive the compressed format specifier for a function, with
// anything not "s" zero.
//#define _S<%0> (-1&_:@Rx:@Ry:@Rw:@Rv:@Ru:(0,%0,0))

#define _F<%0> (-1&_:~@Rx:@Ry:@Rv:@Ru:@Rw:(1,%0))

#define @Rx:@Ry:@Rv:@Ru:@Rw:(%9,s%0) @Rx:@Ry:@Rv:@Ru:@Rw:((%9)<<1,%0)
#define @Ry:@Rv:@Ru:@Rw:(%9,i%0) @Rx:@Ry:@Rv:@Ru:@Rw:((%9)<<1|1,%0)
#define @Rv:@Ru:@Rw:(%9,d%0) @Rx:@Ry:@Rv:@Ru:@Rw:((%9)<<1|1,%0)
#define @Ru:@Rw:(%9,f%0) @Rx:@Ry:@Rv:@Ru:@Rw:((%9)<<1|1,%0)
#define @Rw:(%9,) (%9)

/*#define @Ru:(%0i,%1) ~(1<<%1)&@Rx:@Ry:@Rw:@Rv:@Ru:(%0,%1+1)
#define @Rv:@Ru:(%0d,%1) ~(1<<%1)&@Rx:@Ry:@Rw:@Rv:@Ru:(%0,%1+1)
#define @Rw:@Rv:@Ru:(%0f,%1) ~(1<<%1)&@Rx:@Ry:@Rw:@Rv:@Ru:(%0,%1+1)
#define @Rx:@Ry:@Rw:@Rv:@Ru:(%0s,%1) @Rx:@Ry:@Rw:@Rv:@Ru:(%0,%1+1)
#define @Ry:@Rw:@Rv:@Ru:(,%1) ~(1<<%1)*/

// This is very similar to Callback_Call, but takes an array of ADDRESSES
// instead of normal parameters.  This is designed to help support some
// experimental OO code I was working on...
stock Callback_Array(const result[E_CALLBACK_DATA], const params[])
{
	#pragma unused params
	// Call the function with the given data.  We need some serious stack
	// manipulation skills in here to make it all work.
	if (result[E_CALLBACK_DATA_FLAGS] & e_CALLBACK_FLAGS_PUBLIC)
	{
		// I think I've got an even better way.  NOPE!  None of this code will
		// work because all the parameters are passed by reference, not by
		// value!  This is VERY VERY bad!  D'oh!  Good thing I kept a copy of
		// the old code!  Shame, this would have been very elegant.  Sweet, it
		// seemed to work as well!  Maybe I could just do some similar in-line
		// variable modifications.
		new
			par,
			pointer = result[E_CALLBACK_DATA_POINTER],
			mask = result[E_CALLBACK_DATA_FORMAT];
		// Destroy one parameter.
		//#emit PUSH.S          8
		#emit LOAD.S.alt      8
		#emit PUSH.alt
		//#emit ADD.C      0xFFFFFFFC
		//#emit PUSH.pri
		// Move the return address.
		#emit LOAD.S.pri      4
		#emit STOR.S.pri      8
		// Move the frame.
		#emit LOAD.S.pri      0
		#emit STOR.S.pri      4
		// Fix the parameters.
		#emit LCTRL           5
		#emit ADD
		#emit ADD.C           12
		#emit STOR.S.pri      par
		// Get the jump address.
		//while (mask != ~1)
		// If no format has been provided, just guess and pass every parameter
		// by reference (as they are passed to here).
		while (mask != -1)
		{
			par -= 4;
			if (!(mask & 1))
			{
				#emit LREF.S.pri      par
				#emit LOAD.I
				#emit SREF.S.pri      par
			}
			mask >>= 1;
		}
		//#emit LOAD.S.pri      8
		#emit POP.pri
		#emit ADD.C           0xFFFFFFFC
		#emit STOR.S.pri      12
		//#emit ADD.C      4
		//#emit ADD.C      4
		//#emit MOVE.alt
		#emit LOAD.S.alt      pointer
		// Mangle the stack (no variables from here).
		#emit LCTRL           5
		#emit ADD.C           4
		#emit SCTRL           4
		#emit SCTRL           5
		// Jump to new code (after "PROC").
		#emit MOVE.pri
		#emit ADD.C           4
		#emit SCTRL           6
		// Will never be called.
		//#emit RETN
	}
	else
	{
		new
			size = _:result[E_CALLBACK_DATA_FLAGS],
			num  = 0,
			stack,
			mask = 0x80000000,
			addr,
			tmp;
			//YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		//	ininline = YSI_g_sInInline;
		YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		#emit LCTRL      4
		#emit STOR.S.pri stack
		#emit LOAD.S.alt size
		#emit SUB
		#emit STOR.S.pri addr
		// Add more data for additional parameters.
		#emit SCTRL      4
		//#emit LCTRL      4
		size = result[E_CALLBACK_DATA_FORMAT];
		#emit LCTRL      5
		#emit ADD.C      16
		#emit LOAD.I
		#emit STOR.S.pri tmp
		// OK, now the fun bit!
		while (size & mask)
		{
			mask >>>= 1;
		}
		mask >>>= 1;
		while (mask)
		{
			if (size & mask)
			{
				num += YSI_MAX_STRING;
				addr -= YSI_MAX_STRING * 4;
				//printf("copying string");
				#emit LOAD.S.pri addr
				#emit SCTRL      4
				// Copy the data.
				#emit PUSH.C     130
				#emit PUSH.C     520
				#emit PUSH.C     0
				#emit LREF.S.pri tmp
				#emit PUSH.pri
				#emit PUSH.S     addr
				#emit PUSH.C     20
				#emit SYSREQ.C   memcpy
				#emit STACK      24
				//printf("finished");
			}
			else
			{
				num += 1;
				addr -= 1 * 4;
				#emit LREF.S.pri tmp
				#emit LOAD.I
				#emit PUSH.pri
			}
			mask >>>= 1;
			tmp += 4;
		}
		#emit LCTRL      5
		#emit STOR.S.pri tmp
		num *= 4;
		addr += num;
		// "addr" now contains the params stack address, "stack" contains the
		// starting stack address.  This code technically pushes an incorrect
		// destination size (it's 4x too big), but as the bytes to copy is
		// smaller this is not important.
		// Set the frame pointer.
		size = _:result[E_CALLBACK_DATA_FLAGS];
		#emit LOAD.S.pri size
		#emit SHR.C.pri  8
		#emit SHL.C.pri  2 // NOT SHR 6
		#emit LOAD.S.alt addr
		#emit ADD
		#emit STOR.S.pri tmp
		// Copy the data.
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		num = _:result[E_CALLBACK_DATA_ALLOC];
		#emit LOAD.S.pri size
		#emit PUSH.pri
		#emit PUSH.pri
		#emit PUSH.C     0
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri num
		#emit IDXADDR
		#emit PUSH.pri
		#emit PUSH.S     addr
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
		// Store the return frame.
		#emit LOAD.S.alt tmp
		#emit LCTRL      5
		#emit STOR.I
		#emit MOVE.pri
		#emit ADD.C      4
		#emit MOVE.alt
		// Get the return address and call the function.
		#emit LCTRL      6
		#emit ADD.C      48              // 8
		#emit STOR.I                     // 12
		#emit LOAD.alt   YSI_g_sInInline // 20
		#emit LOAD.S.pri tmp             // 28
		#emit SCTRL      5               // 36
		#emit MOVE.pri                   // 40
		#emit SCTRL      6               // 48
		// Restore the stack.
		//printf("one");
		#emit LOAD.S.pri stack
		#emit SCTRL      4
		//printf("two");
		//YSI_g_sInInline = ininline;
	}
}

// This is very similar to Callback_Call, but takes an allocated block of stack.
stock Callback_Block(const result[E_CALLBACK_DATA], const params[], num)
{
	#pragma unused params
	// Call the function with the given data.  We need some serious stack
	// manipulation skills in here to make it all work.
	if (result[E_CALLBACK_DATA_FLAGS] & e_CALLBACK_FLAGS_PUBLIC)
	{
		// I think I've got an even better way.  NOPE!  None of this code will
		// work because all the parameters are passed by reference, not by
		// value!  This is VERY VERY bad!  D'oh!  Good thing I kept a copy of
		// the old code!  Shame, this would have been very elegant.  Sweet, it
		// seemed to work as well!  Maybe I could just do some similar in-line
		// variable modifications.
		new
			par,
			pointer = result[E_CALLBACK_DATA_POINTER],
			mask = result[E_CALLBACK_DATA_FORMAT];
		// Destroy one parameter.
		//#emit PUSH.S          8
		#emit LOAD.S.alt      8
		#emit PUSH.alt
		//#emit ADD.C      0xFFFFFFFC
		//#emit PUSH.pri
		// Move the return address.
		#emit LOAD.S.pri      4
		#emit STOR.S.pri      8
		// Move the frame.
		#emit LOAD.S.pri      0
		#emit STOR.S.pri      4
		// Fix the parameters.
		#emit LCTRL           5
		#emit ADD
		#emit ADD.C           12
		#emit STOR.S.pri      par
		// Get the jump address.
		//while (mask != ~1)
		// If no format has been provided, just guess and pass every parameter
		// by reference (as they are passed to here).
		while (mask != -1)
		{
			par -= 4;
			if (!(mask & 1))
			{
				#emit LREF.S.pri      par
				#emit LOAD.I
				#emit SREF.S.pri      par
			}
			mask >>= 1;
		}
		//#emit LOAD.S.pri      8
		#emit POP.pri
		#emit ADD.C           0xFFFFFFFC
		#emit STOR.S.pri      12
		//#emit ADD.C      4
		//#emit ADD.C      4
		//#emit MOVE.alt
		#emit LOAD.S.alt      pointer
		// Mangle the stack (no variables from here).
		#emit LCTRL           5
		#emit ADD.C           4
		#emit SCTRL           4
		#emit SCTRL           5
		// Jump to new code (after "PROC").
		#emit MOVE.pri
		#emit ADD.C           4
		#emit SCTRL           6
		// Will never be called.
		//#emit RETN
	}
	else
	{
		new
			size = _:result[E_CALLBACK_DATA_FLAGS],
			//num  = 0,
			stack,
			//mask = 0x80000000,
			addr,
			tmp;
			//YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		//	ininline = YSI_g_sInInline;
		YSI_g_sInInline = result[E_CALLBACK_DATA_POINTER];
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		#emit LCTRL      4
		#emit STOR.S.pri stack
		#emit LOAD.S.alt size
		#emit SUB
		#emit STOR.S.pri addr
		// Add more data for additional parameters.
		#emit SCTRL      4
		//#emit LCTRL      4
		size = result[E_CALLBACK_DATA_FORMAT];
		//#emit LCTRL      5
		//#emit ADD.C      16
		//#emit LOAD.I
		//#emit STOR.S.pri tmp
		// OK, now the fun bit!
		//num = Malloc_SlotSize(params) - 2;
		addr -= num * 4;
		// Increase the stack size.
		#emit LOAD.S.pri addr
		#emit SCTRL      4
		// Copy the data.
		#emit LOAD.S.pri num
		// Destination size.
		#emit PUSH.pri
		#emit SMUL.C     4
		// Number of bytes.
		#emit PUSH.pri
		// 0.
		#emit PUSH.C     0
		#emit PUSH.S     params
		#emit PUSH.S     addr
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
		//tmp = 
		/*while (size & mask)
		{
			mask >>>= 1;
		}
		mask >>>= 1;
		while (mask)
		{
			if (size & mask)
			{
				num += YSI_MAX_STRING;
				addr -= YSI_MAX_STRING * 4;
				//printf("copying string");
				#emit LOAD.S.pri addr
				#emit SCTRL      4
				// Copy the data.
				#emit PUSH.C     130
				#emit PUSH.C     520
				#emit PUSH.C     0
				#emit LREF.S.pri tmp
				#emit PUSH.pri
				#emit PUSH.S     addr
				#emit PUSH.C     20
				#emit SYSREQ.C   memcpy
				#emit STACK      24
				//printf("finished");
			}
			else
			{
				num += 1;
				addr -= 1 * 4;
				#emit LREF.S.pri tmp
				#emit LOAD.I
				#emit PUSH.pri
			}
			mask >>>= 1;
			tmp += 4;
		}*/
		#emit LCTRL      5
		#emit STOR.S.pri tmp
		//num *= 4;
		addr += num * 4;
		// "addr" now contains the params stack address, "stack" contains the
		// starting stack address.  This code technically pushes an incorrect
		// destination size (it's 4x too big), but as the bytes to copy is
		// smaller this is not important.
		// Set the frame pointer.
		size = _:result[E_CALLBACK_DATA_FLAGS];
		#emit LOAD.S.pri size
		#emit SHR.C.pri  8
		#emit SHL.C.pri  2 // NOT SHR 6
		#emit LOAD.S.alt addr
		#emit ADD
		#emit STOR.S.pri tmp
		// Copy the data.
		size = ((size & 0xFF) + (size >>> 8) + 3) * 4;
		num = _:result[E_CALLBACK_DATA_ALLOC];
		#emit LOAD.S.pri size
		#emit PUSH.pri
		#emit PUSH.pri
		#emit PUSH.C     0
		#emit CONST.alt  YSI_gMallocMemory
		#emit LOAD.S.pri num
		#emit IDXADDR
		#emit PUSH.pri
		#emit PUSH.S     addr
		#emit PUSH.C     20
		#emit SYSREQ.C   memcpy
		#emit STACK      24
		// Store the return frame.
		#emit LOAD.S.alt tmp
		#emit LCTRL      5
		#emit STOR.I
		#emit MOVE.pri
		#emit ADD.C      4
		#emit MOVE.alt
		// Get the return address and call the function.
		#emit LCTRL      6
		#emit ADD.C      48              // 8
		#emit STOR.I                     // 12
		#emit LOAD.alt   YSI_g_sInInline // 20
		#emit LOAD.S.pri tmp             // 28
		#emit SCTRL      5               // 36
		#emit MOVE.pri                   // 40
		#emit SCTRL      6               // 48
		// Restore the stack.
		//printf("one");
		#emit LOAD.S.pri stack
		#emit SCTRL      4
		//printf("two");
		//YSI_g_sInInline = ininline;
	}
}
