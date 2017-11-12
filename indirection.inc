
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

#if !defined TAGOF
	#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
		#define TAGOF(%0);
	#else
		#define TAGOF(%0); stock const %0:TAGOF@%0;
		#define TAGOF@%0\32; TAGOF@
		#define tagof(%0:%1) (tagof(TAGOF@%0))
	#endif
	#define TAGOF@TAG@%0\32; TAGOF@TAG@
	#define SPECIFIER(%0) TAGOF(TAG@%0)
	
	TAGOF(Float);
	TAGOF(File);
#endif
#define TAG@%0\32; TAG@

// This is for getting excess parameters on non-strings.
#define _:%0,) _:%0)

SPECIFIER(i);
SPECIFIER(s);

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
#define @%0(%1) (Indirect_Call(_:INDIRECT_DOT:%0,_:(tagof(%0)),%1))
#define Indirect_Call(_:INDIRECT_DOT:%9&%0,_:(tagof(%9)),%2) Indirect_Call(_:TAGOF_ADDRESSOF:addressof(%0),_:0,%2)
#define INDIRECT_DOT:.%0,_:(tagof(.%0)) %0,_:(tagof(%0))
#define TAGOF_ADDRESSOF:addressof(%0<%2>),_:0, addressof(%0),_:tagof(TAG@%2:),
// Can now do:
//   
//   @.var(params)
//   @&func<iis>(params)
//   @.&func(params)
//   

stock Indirect_Call(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr;
	#pragma unused func, tag
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
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function will have a proper `PROC`.
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
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
			lTag[32];
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		i = 4; // Skip the `TAG@` prefix.
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
stock string:Indirect_Callstring(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr;
	#pragma unused func, tag
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
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function will have a proper `PROC`.
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
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
			lTag[32];
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		i = 4; // Skip the `TAG@` prefix.
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
	// Never called.  Don't use "static" because it would allocate real memory
	// in advance.  Instead, this will want to allocate on the stack but never
	// get hit to do so.
	new ret[YSI_MAX_STRING];
	return ret;
}

// Not `Indirect_Callvoid` to make use of the `void:` macro.
stock void:Indirect_Callvoid(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr;
	#pragma unused func, tag
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
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function will have a proper `PROC`.
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
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
			lTag[32];
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		i = 4; // Skip the `TAG@` prefix.
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
	// Don't return anything.
}

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

