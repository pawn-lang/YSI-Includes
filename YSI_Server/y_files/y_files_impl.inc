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
	Portions created by the Initial Developer are Copyright C 2011
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

static stock const
	YSI_gscBatCmd[] = !".dmc\0exe",  // "cmd.exe" byteswapped.
	YSI_gscBatOperation[] = !"nepo", // "open" byteswapped.
	YSI_gscBasePath[] = "/C scriptfiles\\YSI\\scripts\\",
	YSI_gscArg1[] = "set arg1=scriptfiles\\%~1\r\nset arg1=%arg1:..=%\r\nset arg1=%arg1:\\\\=\\%\r\n",
	YSI_gscArg2[] = "set arg2=scriptfiles\\%~2\r\nset arg2=%arg2:..=%\r\nset arg2=%arg2:\\\\=\\%\r\n",
	YSI_gscMKDir[] = "YSI\\scripts\\mkdir.bat",
	YSI_gscCopy[] = "YSI\\scripts\\copy.bat",
	YSI_gscMove[] = "YSI\\scripts\\move.bat",
	YSI_gscDone[] = "type nul > scriptfiles\\YSI\\.donescript\r\n";

static stock
	YSI_gsAddress,
	YSI_gsBatParameters[128];

// We basically just copy `ShellExecute.inc` here for several reasons:
//
//   1) The default include paths mess up slightly (thanks compiler).
//   2) It's a good PoC, but runs all lookups/generations every call.
//   3) `dynamic_call.inc` uses runtime rewrites, which don't work with JIT.
//   4) We can generate way more specialised code with `@emit`.
//

#define CALL@Files_ShellExecute Files_ShellExecute(YSI_EMPTY, YSI_EMPTY, YSI_EMPTY, 0)
#define CALL@Files_CallBat Files_CallBat()

static stock Files_ShellExecute(const Operation[], const File[], const Parameters[], ShowCmd)
{
	#pragma unused Operation, File, Parameters, ShowCmd
	// This function is entirely replaced, by itself...

	#define __asm(%0,%1,%2,%3) (((0x%3) << 24) | ((0x%2) << 16) | (0x%1 << 8) | (0x%0))
	
	static const asm[] = {
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(55,8B,EC,8B),
		__asm(45,0C,8B,48),
		__asm(18,51,8B,55),
		__asm(0C,8B,42,14),
		__asm(50,8B,4D,0C),
		__asm(8B,51,10,52),
		__asm(8B,45,0C,8B),
		__asm(48,0C,51,8B),
		__asm(55,0C,8B,42),
		__asm(08,50,8B,4D),
		__asm(0C,8B,51,04),
		__asm(52,FF,15,00),
		__asm(00,00,00,5D),
		__asm(C3,CC,CC,CC)
	};

	new
		ctx[AsmContext];
	WriteAmxMemory(ref(asm) + 63, refabs(YSI_gsAddress));
	AsmInitPtr(ctx, YSI_gsBatParameters[0] + AMX_HEADER_COD, YSI_gsBatParameters[1] - YSI_gsBatParameters[0]);
	// Get the offset for absolute DAT addresses.
	#emit LCTRL        1
	#emit LOAD.S.alt   ShowCmd
	#emit ADD
	#emit STOR.S.pri   ShowCmd
	// Push the parameters.
	@emit PROC
	@emit PUSH.S       24
	@emit PUSH.C       0
	@emit LOAD.S.pri   20
	@emit ADD.C        ShowCmd
	@emit PUSH.pri
	@emit LOAD.S.pri   16
	@emit ADD.C        ShowCmd
	@emit PUSH.pri
	@emit LOAD.S.pri   12
	@emit ADD.C        ShowCmd
	@emit PUSH.pri
	@emit PUSH.C       0
	@emit PUSH.C       24
	// Call the 16-byte-aligned code.
	@emit SYSREQ.D     (((refabs(asm) + 15) >>> 4) << 4)
	@emit STACK        28
	@emit RETN

	// TODO: Pad with `NOP` without clobbering our own code.
	return AsmGetCodeSize(ctx);
}

static stock bool:Files_CallBat()
{
	// Convert the normal string to a C string.
	for (new i = 0, j = 0, ch; i != sizeof (YSI_gsBatParameters) / 4; ++i, j += 4)
	{
		YSI_gsBatParameters[i] = ch = YSI_gsBatParameters[j] | (YSI_gsBatParameters[j + 1] << 8) | (YSI_gsBatParameters[j + 2] << 16) | (YSI_gsBatParameters[j + 3] << 24);
		if (Cell_HasZeroByte(ch))
		{
			// Found the NULL end;
			break;
		}
	}
	return Files_ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, YSI_gsBatParameters, SW_HIDE) > 32;
}

static stock bool:Files_InitYSIFolder()
{
	static const
		iname[] = "YSI\\.initscript",
		fname[] = "_initysi.bat";
	if (fexist(iname))
	{
		return true;
	}
	if (!fexist(fname))
	{
		new File:f = fopen(fname, io_write);
		if (!f)
		{
			return false;
		}
		fwrite(f, "cd scriptfiles\r\nmkdir YSI\r\ncd YSI\r\nmkdir debug\r\nmkdir fixes\r\nmkdir scripts\r\nmkdir temp\r\nmkdir tests\r\nmkdir text\r\nmkdir users\r\nmkdir YDBG\r\ntype nul > .initscript\r\n"),
		fclose(f);
	}
	// "/C scriptfiles\\_initysi.bat" byteswapped.
	new bool:ret = Files_ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, !"s C/pirclift_\\setini.isy\0tab", SW_HIDE) > 32;
	while (!fexist(iname))
	{
		// Poll for the script to finish.
	}
	//fremove(fname);
	return ret;
}

static stock bool:Files_WriteMKDirBat()
{
	if (fexist(YSI_gscMKDir))
	{
		return true;
	}
	new File:f = fopen(YSI_gscMKDir, io_write);
	if (f)
	{
		return
			fwrite(f, YSI_gscArg1),
			fwrite(f, "mkdir \"%arg1%\"\r\n"),
			fwrite(f, YSI_gscDone),
			fclose(f),
			true;
	}
	return false;
}

static stock bool:Files_CreateDirAsync(const string:folder[])
{
	return
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "%smkdir.bat \"%s\"", YSI_gscBasePath, folder),
		Files_CallBat();
}

static stock bool:Files_WriteCopyBat()
{
	if (fexist(YSI_gscCopy))
	{
		return true;
	}
	new File:f = fopen(YSI_gscCopy, io_write);
	if (f)
	{
		return
			fwrite(f, YSI_gscArg1),
			fwrite(f, YSI_gscArg2),
			fwrite(f, "copy \"%arg1%\" \"%arg2%\"\r\n"),
			fwrite(f, YSI_gscDone),
			fclose(f),
			true;
	}
	return false;
}

stock bool:Files_CopyAsync(const string:src[], const string:dst[])
{
	return
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "%scopy.bat \"%s\" \"%s\"", YSI_gscBasePath, src, dst),
		Files_CallBat();
}

static stock bool:Files_WriteMoveBat()
{
	if (fexist(YSI_gscMove))
	{
		return true;
	}
	new File:f = fopen(YSI_gscMove, io_write);
	if (f)
	{
		return
			fwrite(f, YSI_gscArg1),
			fwrite(f, YSI_gscArg2),
			fwrite(f, "move \"%arg1%\" \"%arg2%\"\r\n"),
			fwrite(f, YSI_gscDone),
			fclose(f),
			true;
	}
	return false;
}

stock bool:Files_MoveAsync(const string:src[], const string:dst[])
{
	return
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "%smove.bat \"%s\" \"%s\"", YSI_gscBasePath, src, dst),
		Files_CallBat();
}

public OnCodeInit()
{
	if (Server_IsWindowsHost())
	{
		// Initialise the assembly.

		// Don't intialise these in `Files_ShellExecute` (they get partially
		// clobbered).
		YSI_gsAddress = GetImportAddress("ShellExecuteA");
		YSI_gsBatParameters[0] = _:addressof (Files_ShellExecute);
		YSI_gsBatParameters[1] = _:addressof (Files_CallBat);
		new
			size = Files_ShellExecute(YSI_EMPTY, YSI_EMPTY, YSI_EMPTY, GetAmxBaseAddress()),
			ctx[AsmContext];
		AsmInitPtr(ctx, YSI_gsBatParameters[0] + size + AMX_HEADER_COD, YSI_gsBatParameters[1] - YSI_gsBatParameters[0] - size);
		AsmEmitPadding(ctx);

		// Create the scripts.
		Files_InitYSIFolder(),
		Files_WriteMKDirBat(),
		Files_WriteCopyBat(),
		Files_WriteMoveBat();
	}
	#if defined Files_OnCodeInit
		return Files_OnCodeInit();
	#endif
}

#undef OnCodeInit
#define OnCodeInit Files_OnCodeInit
#if defined Files_OnCodeInit
	forward Files_OnCodeInit();
#endif

stock bool:Files_CopySync(const string:src[], const string:dst[])
{
	fremove(dst);
	if (Files_CopyAsync(src, dst))
	{
		while (!fexist(dst))
		{
		}
		return true;
	}
	return false;
}

stock bool:Files_MoveSync(const string:src[], const string:dst[])
{
	fremove(dst);
	if (Files_MoveAsync(src, dst))
	{
		while (!fexist(dst))
		{
		}
		return true;
	}
	return false;
}

stock bool:Files_CreateDirSync(const string:dir[])
{
	fremove(".donescript");
	if (Files_CreateDirAsync(dir))
	{
		while (!fexist(".donescript"))
		{
		}
		return true;
	}
	return false;
}

//stock bool:Files_CopyAsync(const string:src[], const string:dst[])
//{
//	return Files_CallCopyBat(src, dst);
//}
//
//stock bool:Files_MoveAsync(const string:src[], const string:dst[])
//{
//	return Files_CallMoveBat(src, dst);
//}
//
//stock bool:Files_CreateDirAsync(const string:dir[])
//{
//	return Files_CallMKDirBat(dir);
//}

