static stock y_files_Write100(File:f)
{
	new data[100 char];
	fblockwrite(f, data);
}

static stock y_files_Write1000(File:f)
{
	new data[100 char];
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
	fblockwrite(f, data);
}

static stock y_files_Write1000000(File:f)
{
	for (new i = 0; i != 1000; ++i)
	{
		y_files_Write1000(f);
	}
}

@test(.group = "y_files") y_files_SmallCopy()
{
	// Make sure this triggers the small copy code.
	ASSERT_LT(100, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f = fopen("YSI\\tests\\y_files\\small.in", io_write);
	if (f)
	{
		y_files_Write100(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\small.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\small.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\small.out"));
	ASSERT(Files_CopySync("YSI\\tests\\y_files\\small.in", "YSI\\tests\\y_files\\small.out"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\small.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\small.out"));
	f = fopen("YSI\\tests\\y_files\\small.in", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 100);
		fclose(f);
	}
	else
	{
		ASSERT(false, "in check");
	}
	f = fopen("YSI\\tests\\y_files\\small.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 100);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

@test(.group = "y_files") y_files_MediumCopy()
{
	// Make sure this triggers the small copy code.
	ASSERT_LT(1000, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f = fopen("YSI\\tests\\y_files\\medium.in", io_write);
	if (f)
	{
		y_files_Write1000(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\medium.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\medium.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\medium.out"));
	ASSERT(Files_CopySync("YSI\\tests\\y_files\\medium.in", "YSI\\tests\\y_files\\medium.out"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\medium.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\medium.out"));
	f = fopen("YSI\\tests\\y_files\\medium.in", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 1000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "in check");
	}
	f = fopen("YSI\\tests\\y_files\\medium.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 1000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

@test(.group = "y_files") y_files_LargeCopy()
{
	// Make sure this triggers the large copy code.
	ASSERT_GT(10000000, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f = fopen("YSI\\tests\\y_files\\large.in", io_write);
	if (f)
	{
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\large.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\large.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\large.out"));
	ASSERT(Files_CopySync("YSI\\tests\\y_files\\large.in", "YSI\\tests\\y_files\\large.out"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\large.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\large.out"));
	//while (!(f = fopen("YSI\\tests\\y_files\\large.in", io_read))) {}
	f = fopen("YSI\\tests\\y_files\\large.in", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 10000000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "in check");
	}
	//while (!(f = fopen("YSI\\tests\\y_files\\large.out", io_read))) {}
	f = fopen("YSI\\tests\\y_files\\large.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 10000000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

@test(.group = "y_files") y_files_SmallMove()
{
	// Make sure this triggers the small copy code.
	ASSERT_LT(100, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f = fopen("YSI\\tests\\y_files\\small.in", io_write);
	if (f)
	{
		y_files_Write100(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\small.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\small.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\small.out"));
	ASSERT(Files_MoveSync("YSI\\tests\\y_files\\small.in", "YSI\\tests\\y_files\\small.out"));
	ASSERT(!fexist("YSI\\tests\\y_files\\small.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\small.out"));
	f = fopen("YSI\\tests\\y_files\\small.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 100);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

@test(.group = "y_files") y_files_MediumMove()
{
	// Make sure this triggers the small copy code.
	ASSERT_LT(1000, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f = fopen("YSI\\tests\\y_files\\medium.in", io_write);
	if (f)
	{
		y_files_Write1000(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\medium.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\medium.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\medium.out"));
	ASSERT(Files_MoveSync("YSI\\tests\\y_files\\medium.in", "YSI\\tests\\y_files\\medium.out"));
	ASSERT(!fexist("YSI\\tests\\y_files\\medium.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\medium.out"));
	f = fopen("YSI\\tests\\y_files\\medium.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 1000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

@test(.group = "y_files") y_files_LargeMove()
{
	// Make sure this triggers the large copy code.
	ASSERT_GT(10000000, YSI_LARGE_FILE_SIZE);
	// Create a dummy file.
	new File:f;
	if ((f = fopen("YSI\\tests\\y_files\\large.in", io_write)))
	{
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		y_files_Write1000000(f);
		fclose(f);
	}
	else
	{
		ASSERT(false, "creation");
	}
	fremove("YSI\\tests\\y_files\\large.out");
	ASSERT(!!fexist("YSI\\tests\\y_files\\large.in"));
	ASSERT(!fexist("YSI\\tests\\y_files\\large.out"));
	ASSERT(Files_MoveSync("YSI\\tests\\y_files\\large.in", "YSI\\tests\\y_files\\large.out"));
	ASSERT(!fexist("YSI\\tests\\y_files\\large.in"));
	ASSERT(!!fexist("YSI\\tests\\y_files\\large.out"));
	f = fopen("YSI\\tests\\y_files\\large.out", io_read);
	if (f)
	{
		ASSERT_EQ(flength(f), 10000000);
		fclose(f);
	}
	else
	{
		ASSERT(false, "out check");
	}
}

