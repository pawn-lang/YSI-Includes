enum E_INDIRECTION
{
	// This is a pointer to a function that actually determines HOW to call this
	// data.  `@` is pretty much just a wrapper that jumps in to this function
	// instead.
	E_INDIRECTION_HANDLER,
	// Custom data for this indirect call.
	E_INDIRECTION_DATA_1,
	// This is the amount of data (it could well be 0).
	E_INDIRECTION_DATA_2
}

stock
	INDIRECTION_DATA_1,
	INDIRECTION_DATA_2;

#define Indirect:%0<%1> %0[E_INDIRECTION]

stock Indirect_Call(const Indirect:func<>, GLOBAL_TAG_TYPES:...)
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
	return 0;
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
#define @.%0(%1) (Indirect_Call(%0,%1))
#define Indirect_Call(%0,) Indirect_Call(%0)

static stock
	Indirect:gsIndirectData<>;

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

stock Indirect_Func(addr, const fmat[])
{
	#emit LOAD.S.pri   addr
	#emit ADD.C        4
	#emit LCTRL        8
	#emit STOR.S.pri   addr
	gsIndirectData[E_INDIRECTION_DATA_1] = addr;
	#emit CONST.pri    Indirect_FuncHandler_
	#emit ADD.C        4
	#emit LCTRL        8
	#emit STOR.S.pri   addr
	gsIndirectData[E_INDIRECTION_HANDLER] = addr;
	addr = 0;
	for (new i; i != 32; ++i)
	{
		switch (fmat[i])
		{
		case '\0':
			break;
		case 'i', 'd', 'x', 'f', 'c':
			addr |= 1 << i;
		}
	}
	gsIndirectData[E_INDIRECTION_DATA_2] = addr;
	return gsIndirectData;
}

#define Indirect_Func(&%0,%1) Indirect_Func(addressof (%0), %1)

