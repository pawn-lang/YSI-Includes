

//#undef _inc__impl


// The relative order of this data is VERY important.
#define HASH_MAP_DATA<%0> \
	_E_HASH_MAP_NAME[%0], \
	_E_HASH_MAP_NEXT,     \
	_E_HASH_MAP_HASH


#define HASH_MAP_SIZE   (256) // 0x100
#define HASH_MAP_PTR    (HASH_MAP_SIZE)
#define HASH_MAP_SIZE_1 (HASH_MAP_SIZE + 1)
#define HASH_MAP_SIZE_2 (HASH_MAP_SIZE + 2)
#define HASH_MAP_SIZE_3 (HASH_MAP_SIZE + 3)

#define HashMap:%0<%1>                    \
	%0[HASH_MAP_SIZE + 4]
	//
	//forward HASH_%1();
	//public HASH_%1()
	//{printf(#HASH_%1"()");
	//	HashMap_Associate(%0, _:%1);
	//}



// So I can quickly change HashMap hash settings.
#define HashMap_Hash(%0,%1) (%1=YHash(%0))

/*
hook OnScriptInit()
{
	new
		buffer[32],
		idx;
	while ((idx = AMX_GetPublicName(idx, buffer, "HASH_")))
	{
		CallLocalFunction(buffer, "");
	}
}
*/

stock _HashMap_Init(HashMap:m<>, &target, size1, size2, &t2)
{
	static
		HashMap:sInit<> = {-1, ...};
	m = sInit;
	new
		ptr;
	// Save the pointer.
	#emit LOAD.S.pri target
	#emit STOR.S.pri ptr
	m[HASH_MAP_PTR] = ptr,
	// Store the number of elements in the array.
	m[HASH_MAP_SIZE_1] = size1,
	// Store the size of each element.
	m[HASH_MAP_SIZE_2] = size2;
	// Set up the main array.
	while (size1--)
	{
		AMX_Write(ptr, -1),
		ptr += size2;
	}
	#emit LOAD.S.pri target
	#emit LOAD.S.alt t2
	#emit SUB
	//#emit SHR.C.pri  2
	// -4 (for "_E_HASH_MAP_NEXT").
	//#emit ADD.C      0xFFFFFFFC //0xFFFFFFFF
	#emit STOR.S.pri ptr
	// Store the size of "_E_HASH_MAP_NAME" in bytes.
	m[HASH_MAP_SIZE_3] = ptr;
}

#define HashMap_Init(%0,%1) _HashMap_Init(%0,%1[0][_E_HASH_MAP_NEXT],sizeof(%1),sizeof(%1[])*4,%1[0][_E_HASH_MAP_NAME])

#define HashMap_ByteLen(%0) ((strlen((%0)) + 1) << (2 * _:!ispacked((%0))))

stock bool:HashMap_Add(HashMap:m<>, const str[], const value)
{
	P:3("HashMap_Add called: %d <= %d < %d", 0, value, m[HASH_MAP_SIZE_1]);
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		new
			ptr  = m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2];
		if (AMX_Read(ptr) != -1) return false;
		static
			hash,
			mask;
		HashMap_Hash(str, hash);
		mask = hash & 0xFF;
		P:5("HashMap_Add: mask = %d", mask);
		// Add this hash to the hash list.
		AMX_Write(ptr, m[mask]),
		m[mask] = ptr,
		// Get the hashed string destination size.
		mask = m[HASH_MAP_SIZE_3],
		// Copy the string over (limited by both length and space).
		rawMemcpy(ptr - mask, ref(str), min(mask, HashMap_ByteLen(str))),
		// Copy the hashed value.
		AMX_Write(ptr + 4, hash);
		return true;
	}
	return false;
}

/*
stock bool:HashMap_Add(HashMap:m<>, const str[], const value)
{
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		new
			ptr  = m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2];
		if (AMX_Read(ptr) != -1) return false;
		new
			hash = YHash(str),
			mask = hash & 0xFF,
			len2 = strlen(str) + 1;
		if (!ispacked(str)) len2 <<= 2;
		return
			AMX_Write(ptr, m[mask]),
			m[mask] = ptr,
			mask = m[HASH_MAP_SIZE_3],
			rawMemcpy(ptr + 4, ref(str), min(mask, len2)),
			AMX_Write(ptr + 4 + mask, hash),
			true;
	}
	return false;
}
*/

stock HashMap_Get(HashMap:m<>, const str[])
{
	static
		hash,
		res;
	HashMap_Hash(str, hash);
	res = hash & 0xFF;
	P:3("HashMap_Get called: mask = %d", res);
	for (new ptr = m[res]; ptr != -1; ) //ptr = AMX_Read(ptr))
	{
		#emit LOAD.S.pri  ptr
		#emit ADD.C       4
		#emit LOAD.I
		#emit STOR.pri    res
		if (res == hash)
		{
			P:6("HashMap_Get: Candidate %d: %d == %d", (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2], AMX_Read(ptr + 4), hash);
			// Maybe collisions.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.C      0
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			//printf("res = %d", res);
			if (res == 0) return (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2];
		}
		{} // Zero-cost bug fix.
		#emit LREF.S.pri  ptr
		#emit STOR.S.pri  ptr
	}
	return -1;
}
