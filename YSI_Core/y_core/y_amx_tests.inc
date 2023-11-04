static stock
	YSI_gsAddr,
	YSI_gsInput[128],
	YSI_gsOutput[128];

@test(.group = "y_amx") y_amx_StringRead1B()
{
	YSI_gsAddr = AMX_Ref(YSI_gsInput[0]);
	AMX_WriteUnpackedString(YSI_gsAddr, __COMPILER_UNPACK"Shorter string.");
	AMX_ReadString(YSI_gsAddr, YSI_gsOutput);
	ASSERT_SAME(YSI_gsOutput, "Shorter string.");
}

@test(.group = "y_amx") y_amx_StringRead2B()
{
	YSI_gsAddr = AMX_Ref(YSI_gsInput[0]);
	AMX_WriteUnpackedString(YSI_gsAddr, __COMPILER_UNPACK"Shorter string.");
	AMX_ReadPackedString(YSI_gsAddr, YSI_gsOutput);
	ASSERT_SAME(YSI_gsOutput, "Shorter string.");
}

@test(.group = "y_amx") y_amx_StringRead3B()
{
	YSI_gsAddr = AMX_Ref(YSI_gsInput[0]);
	AMX_WriteUnpackedString(YSI_gsAddr, __COMPILER_UNPACK"Shorter string.");
	AMX_ReadUnpackedString(YSI_gsAddr, YSI_gsOutput);
	ASSERT_SAME(YSI_gsOutput, "Shorter string.");
}

@test(.group = "y_amx") y_amx_Libraries()
{
	new a, b, c, d, e, f, g, h, i, j, x;
	x = heapspace();
	a = y_testing_a_native();
	b = y_testing_b_native();
	c = y_testing_c_native();
	d = y_testing_d_native();
	e = y_testing_e_native();
	f = y_testing_f_native();
	g = y_testing_g_native();
	h = y_testing_h_native();
	i = y_testing_i_native();
	j = y_testing_j_native();
	ASSERT_EQ(a, x);
	ASSERT_EQ(b, x);
	ASSERT_EQ(c, x);
	ASSERT_EQ(d, x);
	ASSERT_EQ(e, x);
	ASSERT_EQ(f, x);
	ASSERT_EQ(g, x);
	ASSERT_EQ(h, x);
	ASSERT_EQ(i, x);
	ASSERT_EQ(j, x);

	a = AMX_GetLibraryEntry(0, x, "y_testing_a_library");
	b = AMX_GetLibraryEntry(0, x, "y_testing_b_library");
	c = AMX_GetLibraryEntry(0, x, "y_testing_c_library");
	d = AMX_GetLibraryEntry(0, x, "y_testing_d_library");
	e = AMX_GetLibraryEntry(0, x, "y_testing_e_library");
	f = AMX_GetLibraryEntry(0, x, "y_testing_f_library");
	g = AMX_GetLibraryEntry(0, x, "y_testing_g_library");
	h = AMX_GetLibraryEntry(0, x, "y_testing_h_library");
	i = AMX_GetLibraryEntry(0, x, "y_testing_i_library");
	j = AMX_GetLibraryEntry(0, x, "y_testing_j_library");
	ASSERT_NZ(a);
	ASSERT_NZ(b);
	ASSERT_NZ(c);
	ASSERT_NZ(d);
	ASSERT_NZ(e);
	ASSERT_NZ(f);
	ASSERT_NZ(g);
	ASSERT_NZ(h);
	ASSERT_NZ(i);
	ASSERT_NZ(j);
	
	x = AMX_GetLibraryCount();
	ASSERT(x >= 10);
}

@test(.group = "y_amx") y_amx_Natives()
{
	new idx, ptr, buf[FUNCTION_LENGTH];
	idx = AMX_GetNativeEntry(0, ptr, "printf", true);
	ASSERT_NZ(idx);
	ASSERT_NZ(ptr);
	idx = AMX_GetNativePointer(0, ptr, "printf", true);
	ASSERT_NZ(idx);
	ASSERT_NZ(ptr);
	idx = AMX_GetNativePointer(idx, ptr, "printf", true);
	ASSERT_NZ(idx);
	ASSERT_NZ(ptr);
	idx = 0;
	// Shortened for the old compiler.
	ptr = ('p' << 0) | ('r' << 8) | ('i' << 16) | ('n' << 24); // _A<prin>;
	while ((idx = AMX_GetNativeNamePrefix(idx, buf, ptr)))
	{
		strunpack(buf, buf);
		printf("Found %d = `%s`", idx, buf);
	}
}

