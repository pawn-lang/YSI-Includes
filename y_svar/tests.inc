enum y_svar_E_TEST
{
	y_svar_E_TEST_A,
	Float:y_svar_E_TEST_B,
	y_svar_E_TEST_C[24]
}

svar y_svar_TestEnum[y_svar_E_TEST];
svar y_svar_Test1D[200];
svar y_svar_Test2D[200][200];
svar y_svar_Test2DEnum[200][y_svar_E_TEST];
svar y_svar_TestEnum2D[y_svar_E_TEST][200];

Test:y_svar_Enum()
{
	// Should fail first time ever, but then not again.
	ASSERT(y_svar_TestEnum[y_svar_E_TEST_A] == 42);
	y_svar_TestEnum[y_svar_E_TEST_A] = 42;
	ASSERT(y_svar_TestEnum[y_svar_E_TEST_B] == 55.44);
	y_svar_TestEnum[y_svar_E_TEST_B] = 55.44;
	ASSERT(!strcmp(y_svar_TestEnum[y_svar_E_TEST_C], "SOME STORED DATA") && y_svar_TestEnum[y_svar_E_TEST_C][0]);
	strcpy(y_svar_TestEnum[y_svar_E_TEST_C], "SOME STORED DATA", 24);
}

Test:y_svar_1D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test1D); ++i)
	{
		if (y_svar_Test1D[i] != i) ++fails;
		y_svar_Test1D[i] = i;
	}
	ASSERT(fails == 0);
}

Test:y_svar_2D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test2D); ++i)
	{
		for (new j = 0; j != sizeof (y_svar_Test2D[]); ++j)
		{
			if (y_svar_Test2D[i][j] != i * j) ++fails;
			y_svar_Test2D[i][j] = i * j;
		}
	}
	ASSERT(fails == 0);
}

Test:y_svar_2DEnum()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_Test2DEnum); ++i)
	{
		if (!(y_svar_Test2DEnum[i][y_svar_E_TEST_A] == 42 * i)) ++fails;
		y_svar_Test2DEnum[i][y_svar_E_TEST_A] = 42 * i;
		if (!(y_svar_Test2DEnum[i][y_svar_E_TEST_B] == 55.44 + i)) ++fails;
		y_svar_Test2DEnum[i][y_svar_E_TEST_B] = 55.44 + i;
		if (strcmp(y_svar_Test2DEnum[i][y_svar_E_TEST_C], "SOME STORED DATA") || !y_svar_Test2DEnum[i][y_svar_E_TEST_C][0]) ++fails;
		strcpy(y_svar_Test2DEnum[i][y_svar_E_TEST_C], "SOME STORED DATA", 24);
	}
	ASSERT(fails == 0);
}

Test:y_svar_Enum2D()
{
	// Should fail first time ever, but then not again.
	new
		fails = 0;
	for (new i = 0; i != sizeof (y_svar_TestEnum2D[]); ++i)
	{
		if (y_svar_TestEnum2D[y_svar_E_TEST_A][i] != i + 101) ++fails;
		y_svar_TestEnum2D[y_svar_E_TEST_A][i] = i + 101;
	}
	ASSERT(fails == 0);
}
