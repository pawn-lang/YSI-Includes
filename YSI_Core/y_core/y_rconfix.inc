static stock const
	YSI_gscOnClientCheckResponse[] = "FIXES_OnClientCheckResponse",
	YSI_gscRconFixFS[] = "callbackfix.amx";

y_rconfix_Load()
{
#if defined YSI_FIX_CALLBACKS
	// Test if the fix has already been loaded.
	setproperty(27, YSI_gscOnClientCheckResponse, 0);
	YSI_SendRconCommand(YSI_gscOnClientCheckResponse);
	if (getproperty(27, YSI_gscOnClientCheckResponse) == 27)
	{
		return;
	}
	// It is.  Create the file.
	if (!fexist(YSI_gscRconFixFS))
	{
		/*
			// Minimise code size.
			#pragma option -d0
			#pragma option -O1

			// Declare some natives for use.
			native CallRemoteFunction(const function[], const format[], ...);
			native setproperty(id = 0, const name[] = "", value = cellmin, const string[] = "");
			native strcmp(const string1[], const string2[], bool:ignorecase = false, length = cellmax);

			// Use the same string for everything, so we only need one.  And pack it.
			new const FIXES_OnClientCheckResponse[] = !"FIXES_OnClientCheckResponse";

			forward OnRconCommand(const cmd[]);

			// This callback just needs to exist in one filterscript.
			public OnRconCommand(const cmd[])
			{
				// The smallest I could make the assembly without `#emit`.
				if (strcmp(cmd, FIXES_OnClientCheckResponse, true) == 0)
				{
					// Add 2 cells of padding here to make the AMX a nice size.
					return !setproperty(27, FIXES_OnClientCheckResponse, 27, "\0\0");
				}
				return 0;
			}

			forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

			// This callback needs to invoke a different callback in GMs.
			public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
			{
				// Invoke the global callback.
				return CallRemoteFunction(FIXES_OnClientCheckResponse, !"iiii", playerid, actionid, memaddr, retndata);
			}
		*/
		static
			lRCFixCode[] = {
				0x00000120, 0x0808F1E0, 0x00080014, 0x000000AC, 0x00000190, 0x000001C0, 0x000041C0, 0xFFFFFFFF,
				0x00000038, 0x00000048, 0x00000060, 0x00000060, 0x00000060, 0x00000060, 0x00000094, 0x00000062,
				0x00000008, 0x00000078, 0x00000000, 0x00000086, 0x00000000, 0x0000008D, 0x00000000, 0x00000099,
				0x6E4F001F, 0x65696C43, 0x6843746E, 0x526B6365, 0x6F707365, 0x0065736E, 0x63526E4F, 0x6F436E6F,
				0x6E616D6D, 0x74730064, 0x706D6372, 0x74657300, 0x706F7270, 0x79747265, 0x6C614300, 0x6D65526C,
				0x4665746F, 0x74636E75, 0x006E6F69, 0x2E007880, 0xFFFF8727, 0x01277FFF, 0x0C290027, 0x7B801027,
				0x36142C00, 0x1C270C81, 0x00271B27, 0x10271B27, 0x2C017B80, 0x30548014, 0x2E305980, 0x81180581,
				0x05811405, 0x0C058110, 0x00272827, 0x7B801827, 0x301C2C02, 0xB0A5B284, 0xFD9A8545, 0x9B846E9E,
				0x8665D2B1, 0x6886D1F3, 0xD68DAB86, 0xCDAB8652, 0xF3866FE0, 0x0000CACD, 0xCB860000, 0x0069D2A5
			};
		new
			File:fs = fopen(YSI_gscRconFixFS, io_write);
		if (fs)
		{
			fblockwrite(fs, lRCFixCode);
			fclose(fs);
		}
	}
	if (fexist(YSI_gscRconFixFS))
	{
		YSI_SendRconCommand("loadfs ../scriptfiles/callbackfix");
	}
	else
	{
		P:W("Could not load RconCommand/ClientCheckResponse fix FS.");
		P:I("Ignore this error if the FS already loaded.");
	}
#endif
}

stock y_rconfix_Unload()
{
	YSI_SendRconCommand("unloadfs ../scriptfiles/callbackfix");
}

