
#tryinclude "..\amx\addressof"
#tryinclude <amx_assembly\addressof>
#tryinclude "..\amx_assembly\addressof"
#tryinclude "..\..\amx_assembly\addressof"
#tryinclude "addressof"
#tryinclude <addressof>
#if !defined ADDRESSOF_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\amx_header"
#tryinclude <amx_assembly\amx_header>
#tryinclude "..\amx_assembly\amx_header"
#tryinclude "..\..\amx_assembly\amx_header"
#tryinclude "amx_header"
#tryinclude <amx_header>
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#if defined AMX_INCLUDING_FAILED
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
#elseif !defined GetOpcodeInstructionInformation
	#error Please update "https://github.com/Zeex/amx_assembly" to the latest version.
#endif

//enum E_INDIRECTION
//{
//	// This is a pointer to a function that actually determines HOW to call this
//	// data.  `@` is pretty much just a wrapper that jumps in to this function
//	// instead.
//	E_INDIRECTION_HANDLER,
//	// Custom data for this indirect call.
//	E_INDIRECTION_DATA_1,
//	// This is the amount of data (it could well be 0).
//	E_INDIRECTION_DATA_2
//}

stock
	INDIRECTION_DATA,
	INDIRECTION_TAG;

static stock
	gsCodSize; // The size of `COD`.

#if !defined YSI_MAX_STRING
	#define YSI_MAX_STRING 144
#endif

#define string:
#define void:

stock Indirect_Call(func, tag, GLOBAL_TAG_TYPES:...)
{
	// Read the memory at `handler`.  If it is `OP_PROC`, this is just a normal
	// function not a special handler function.  If so, translate the parameters
	// in to the correct forms from the tag and jump to `handler + cellbytes`.
	// If it isn't `OP_PROC` (don't ask me what happens with state functions),
	// Copy the data and then jump straight to it.
	// 
	// If I make `func` a reference, I think I can trick vars and arrays in to
	// behaving similarly.  No, that will easilly loose its referenceness if
	// people pass it as a regular parameter.  BUT - the COD and DAT segments
	// are different.  So something pointing in to DAT relative to COD will not
	// be a valid pointer, and THAT you can detect!
	#emit LOAD.S.pri   tag
	#emit STOR.pri     INDIRECTION_TAG
	// Get the previous frame.
	#emit POP.pri
	// Get the return address.
	#emit POP.alt
	// Get the parameter count and put the frame back on.
	#emit SWAP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the new parameter count.
	#emit STOR.S.pri   tag
	// Get the indirection data.
	#emit LOAD.S.pri   func
	#emit STOR.pri     INDIRECTION_DATA
	// Store the return address.
	#emit STOR.S.alt   func
	// Move the frame up slightly.
	#emit LCTRL        4
	#emit SCTRL        5
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA > gsCodSize)
	{
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit STOR.pri     INDIRECTION_DATA
		#emit LOAD.I
		#emit SCTRL        6
	}
	else if (INDIRECTION_TAG)
	{
		static
			i,
			addr,
			lTag[32];
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		i = 0;
		#emit ADDR.pri     12
		#emit STOR.pri     addr
		for ( ; ; )
		{
			switch (lTag[i++])
			{
			case 'i', 'd', 'x', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   addr
				#emit LOAD.I
				#emit SREF.pri   addr
			}
			case '\0':
				break;
			}
			addr += 4;
		}
		{}
		// No handler, and no tag data.  Just jump to it and hope.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit SCTRL        6
	}
	else
	{
		// No handler, and no tag data.  Just jump to it and hope.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit SCTRL        6
	}
	return 0;
}

// Not `Indirect_CallString` to make use of the `string:` macro.
stock string:Indirect_Callstring(const func[E_INDIRECTION], tag, GLOBAL_TAG_TYPES:...)
{
	// Get the previous frame.
	#emit POP.alt
	// Get the return address.
	#emit POP.pri
	// Get the parameter count.
	#emit SWAP.pri
	// Put the old frame back on.
	#emit PUSH.alt
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFFC
	// Get the indirection data.
	#emit LOAD.S.alt   func
	// Store the new parameter count.
	#emit STOR.S.pri   func
	// Move the frame up slightly.
	#emit LCTRL        4
	#emit SCTRL        5
	// Get the indirection data.
	#emit CONST.pri    1
	#emit LIDX
	#emit STOR.pri     INDIRECTION_DATA_1
	// Get the indirection size.
	#emit CONST.pri    2
	#emit LIDX
	#emit STOR.pri     INDIRECTION_DATA_2
	// Jump to the handler.
	#emit ZERO.pri
	#emit LIDX
	#emit SCTRL        8
	#emit SCTRL        6
	// Never called.  Don't use "static" because it would allocate real memory
	// in advance.  Instead, this will want to allocate on the stack but never
	// get hit to do so.
	new ret[YSI_MAX_STRING];
	return ret;
}

// Not `Indirect_Callvoid` to make use of the `void:` macro.
stock void:Indirect_Callvoid(const func[E_INDIRECTION], tag, GLOBAL_TAG_TYPES:...)
{
	// Get the previous frame.
	#emit POP.alt
	// Get the return address.
	#emit POP.pri
	// Get the parameter count.
	#emit SWAP.pri
	// Put the old frame back on.
	#emit PUSH.alt
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFFC
	// Get the indirection data.
	#emit LOAD.S.alt   func
	// Store the new parameter count.
	#emit STOR.S.pri   func
	// Move the frame up slightly.
	#emit LCTRL        4
	#emit SCTRL        5
	// Get the indirection data.
	#emit CONST.pri    1
	#emit LIDX
	#emit STOR.pri     INDIRECTION_DATA_1
	// Get the indirection size.
	#emit CONST.pri    2
	#emit LIDX
	#emit STOR.pri     INDIRECTION_DATA_2
	// Jump to the handler.
	#emit ZERO.pri
	#emit LIDX
	#emit SCTRL        8
	#emit SCTRL        6
	// Don't return anything.
}

// I did consider an alternate method of making `@` do this:
//   
//   #define @.%0(%1) Indirect_Data(%0),Indirect_Call(%1)
//   
// But that would fail when an `@` call contained another `@` call:
//   
//   @.Func1(@.Func2(42, 43));
//   
// It would save the stack manipulation though (not convinced it would be less
// code though with the generation of multiple function calls).
#define @.%0(%1) (Indirect_Call(_:%0,(tagof (%0)),%1))
#define Indirect_Call(%0,%1,) Indirect_Call(%0)

#define Indirect<%2>:%0<%1> @TAG%2:%0[E_INDIRECTION]
static stock
	Indirect<>:gsIndirectData<>;

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Compresses function names when required to fit within 32 characters
 *  according to well defined rules (see "YSI_g_sReplacements").
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Indirect_NullHandler_(GLOBAL_TAG_TYPES:...)
{
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="">Parameters to pass to the function with a .</param>
 * <remarks>
 *  Compresses function names when required to fit within 32 characters
 *  according to well defined rules (see "YSI_g_sReplacements").
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Indirect_FuncHandler_(GLOBAL_TAG_TYPES:...)
{
	// Get the pointer to the first parameter.
	#emit ADDR.alt     12
	#emit PUSH.alt
	while (INDIRECTION_DATA_2)
	{
		if (INDIRECTION_DATA_2 & 1)
		{
			// The parameter is an integer type, not a reference type, resolve
			// the value from how it was passed by reference.
			#emit LREF.S.pri   0xFFFFFFFC
			#emit LOAD.I
			#emit SREF.S.pri   0xFFFFFFFC
			#emit POP.pri
			#emit ADD.C        4
			#emit PUSH.pri
		}
		else
		{
			#emit POP.pri
			#emit ADD.C        4
			#emit PUSH.pri
		}
		INDIRECTION_DATA_2 >>= 1;
	}
	{}
	#emit POP.pri
	#emit LOAD.pri     INDIRECTION_DATA_1
	#emit SCTRL        8
	#emit SCTRL        6
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Compresses function names when required to fit within 32 characters
 *  according to well defined rules (see "YSI_g_sReplacements").
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Func(const fmat[], const name[] = "", ptr = 0)
{
	if (name[0])
		ptr = GetPublicAddressFromName(name);
	if (ptr)
	{
		#emit LOAD.S.pri   ptr
		#emit ADD.C        4
		#emit LCTRL        8
		#emit STOR.S.pri   ptr
		gsIndirectData[E_INDIRECTION_DATA_1] = ptr;
		#emit CONST.pri    Indirect_FuncHandler_
		#emit ADD.C        4
		#emit LCTRL        8
		#emit STOR.S.pri   ptr
		gsIndirectData[E_INDIRECTION_HANDLER] = ptr;
		ptr = 0;
		for (new i; i != 32; ++i)
		{
			switch (fmat[i])
			{
			case '\0':
				break;
			case 'i', 'd', 'x', 'f', 'c':
				ptr |= 1 << i;
			}
		}
		gsIndirectData[E_INDIRECTION_DATA_2] = ptr;
	}
	else
	{
		#emit CONST.pri    Indirect_NullHandler_
		#emit ADD.C        4
		#emit LCTRL        8
		#emit STOR.S.pri   ptr
		gsIndirectData[E_INDIRECTION_HANDLER] = ptr;
	}
	return gsIndirectData;
}

#define Indirect_Func(%1,&%0) Indirect_Func(%1, .ptr = addressof (%0))

#if !defined _ALS_OnJITCompile
	forward OnJITCompile();
#endif

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Get the size of the COD AMX segment.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnJITCompile()
{
	new
		amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	gsCodSize = amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
	#if defined Indirection_OnJITCompile
		return Indirection_OnJITCompile();
	#else
		return 1;
	#endif
}

public OnFilterScriptInit()
{
	new
		amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	gsCodSize = amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
	#if defined Indirection_OnFilterScriptInit
		Indirection_OnFilterScriptInit();
	#endif
	return 1;
}

public OnGameModeInit()
{
	new
		amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	gsCodSize = amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
	#if defined Indirection_OnGameModeInit
		Indirection_OnGameModeInit();
	#endif
	return 1;
}

#if defined Indirection_OnJITCompile
	forward Indirection_OnJITCompile();
#endif
#if defined _ALS_OnJITCompile
	#undef OnJITCompile
#else
	#define _ALS_OnJITCompile
#endif
#define OnJITCompile(%0) Indirection_OnJITCompile(%0)

#if defined Indirection_OnFilterScriptInit
	forward Indirection_OnFilterScriptInit();
#endif
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit(%0) Indirection_OnFilterScriptInit(%0)

#if defined Indirection_OnGameModeInit
	forward Indirection_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit(%0) Indirection_OnGameModeInit(%0)

