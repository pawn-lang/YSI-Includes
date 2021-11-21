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
	YSI_gscBatOperation[] = !"nepo"; // "open" byteswapped.

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

/*-------------------------------------------------------------------------*//**
 * <param name="Operation"><c>lpOperation<c> string.</param>
 * <param name="File"><c>lpFile<c> string.</param>
 * <param name="Parameters"><c>lpParameters<c> string.</param>
 * <param name="ShowCmd"><c>nShowCmd<c> int.</param>
 * <remarks>
 *  See: http://msdn.microsoft.com/en-us/library/windows/desktop/bb762153%28v=vs.85%29.aspx
 *  <br />
 *  We basically just copy Zeex's `ShellExecute.inc` implementation here for
 *  several reasons:
 *  <ol>
 *    <li>The default include paths mess up slightly (thanks compiler).</li>
 *    <li>It's a good PoC, but runs all lookups/generations every call.</li>
 *    <li><c>dynamic_call.inc</c> uses runtime rewrites, which don't work with JIT.</li>
 *    <li>We can generate way more specialised code with <c>@emit<c>.</li>
 *  </ol>
 *  In short, this is inlined and way faster and more robust.  The first time
 *  this function is called (from <c>OnCodeInit</c>) it doesn't actually invoke
 *  the syscall.  Instead, the function rewrites itself to insert
 *  <c>SYSREQ.D</c> and resolve all addresses once ahead of time.  This makes
 *  subsequent calls faster, and (more importantly) makes the code JITable.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Encode a parameters string as a C string (packed and cell reversed), then
 *  call <c>ShellExecute("open", "cmd.exe", params, SW_HIDE)</c> to run batch
 *  script code in the background.  This call is async, so the sync methods all
 *  have some sort of polling for completion.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
	return Files_ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, YSI_gsBatParameters, 0) > 32;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Initialise the <c>scriptfiles\YSI</c> directory if it doesn't exist, and set
 *  up the standard <c>DANGEROUS_SERVER_ROOT</c> link to allow access to server
 *  root files from scripts.  Only works on Windows.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
		fwrite(f, "cd scriptfiles\r\nmklink /J DANGEROUS_SERVER_ROOT ..\r\nmkdir YSI\r\ncd YSI\r\nmkdir debug\r\nmkdir fixes\r\nmkdir temp\r\nmkdir tests\r\nmkdir text\r\nmkdir users\r\nmkdir YDBG\r\ntype nul > .initscript\r\n"),
		fclose(f);
	}
	// "/C scriptfiles\\_initysi.bat" byteswapped.
	new bool:ret = Files_ShellExecute(/*!"anur\0\0\0s"*/YSI_gscBatOperation, YSI_gscBatCmd, !"s C/pirclift_\\setini.isy\0tab", 0) > 32;
	while (!fexist(iname))
	{
		// Poll for the script to finish.
	}
	fremove(fname);
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to create.</param>
 * <remarks>
 *  Invoke the native mkdir routines on Windows.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:Files_CallMKDirBat(const string:folder[])
{
	return
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "/C \"mkdir scriptfiles\\%s\"", folder),
		Files_CallBat();
}

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to delete.</param>
 * <remarks>
 *  Invoke the native rmdir routines on Windows.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:Files_CallRMDirBat(const string:folder[])
{
	return
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "/C \"rmdir /S /Q scriptfiles\\%s\"", folder),
		Files_CallBat();
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Invoke the native copy routines on Windows.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:Files_CallCopyBat(const string:src[], const string:dst[])
{
	return
		fremove(dst),
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "/C \"copy scriptfiles\\%s scriptfiles\\%s\"", src, dst),
		Files_CallBat();
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Invoke the native move routines on Windows.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:Files_CallMoveBat(const string:src[], const string:dst[])
{
	return
		fremove(dst),
		format(YSI_gsBatParameters, sizeof (YSI_gsBatParameters), "/C \"move scriptfiles\\%s scriptfiles\\%s\"", src, dst),
		Files_CallBat();
}

#if defined YSI_NO_WINDOWS_FILES
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Invoke the generation of the <c>ShellExecute</c> code and set up the
 *  <c>YSI</c> folder.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
		Files_InitYSIFolder();
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

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Copies a file from <c>src</c> to <c>dst</c>.  Returns after the copying has
 *  finished.  On Windows this might use <c>ShellExecute</c> to invoke native
 *  file copy operations (depending on file size).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_CopySync(const string:src[], const string:dst[])
{
	// Handy simple check that the source is in `scriptfiles`.
	new File:i = fopen(src, io_read);
	if (!i)
	{
		return false;
	}
	new len = flength(i);
	if (Server_IsWindowsHost() && len > YSI_LARGE_FILE_SIZE && Files_CallCopyBat(src, dst))
	{
		// Use batch file copying.
		fclose(i);
		while (!fexist(dst))
		{
		}
		return true;
	}
	// Use fallback copying.
	return
		len = _:Files_CopyRange(i, len, dst),
		fclose(i) && len;
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Moves (renames) a file from <c>src</c> to <c>dst</c>.  Returns after the
 *  moving has finished.  On Windows this might use <c>ShellExecute</c> to
 *  invoke native file move operations (depending on file size).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_MoveSync(const string:src[], const string:dst[])
{
	// Handy simple check that the source is in `scriptfiles`.
	new File:i = fopen(src, io_read);
	if (!i)
	{
		return false;
	}
	new len = flength(i);
	if (Server_IsWindowsHost() && len > YSI_LARGE_FILE_SIZE && Files_CallMoveBat(src, dst))
	{
		// Use batch file moving.
		fclose(i);
		while (!fexist(dst))
		{
		}
		return true;
	}
	// Use fallback moving.
	return
		len = _:(Files_CopyRange(i, len, dst) && fremove(src)),
		fclose(i) && len;
}

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to create.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory creation
 *  script, without using a plugin.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_CreateDirSync(const string:dir[])
{
	if (fexist(dir))
	{
		return true;
	}
	else if (Server_IsWindowsHost())
	{
		if (Files_CallMKDirBat(dir))
		{
			while (!fexist(dir))
			{
			}
			return true;
		}
	}
	else
	{
		P:E("Files_CreateDirSync unsupported on Linux hosts");
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to delete.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory deletion
 *  script, without using a plugin.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_RemoveDirSync(const string:dir[])
{
	if (!fexist(dir))
	{
		return true;
	}
	else if (Server_IsWindowsHost())
	{
		if (Files_CallRMDirBat(dir))
		{
			while (fexist(dir))
			{
			}
			return true;
		}
	}
	else
	{
		P:E("Files_RemoveDirSync unsupported on Linux hosts");
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Copies a file from <c>src</c> to <c>dst</c>.  May return before the copying
 *  has finished.  Only works on Windows as it uses <c>ShellExecute</c> to
 *  invoke native file copy operations.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_CopySync`, the async code doesn't save time.
stock bool:Files_CopyAsync(const string:src[], const string:dst[])
{
	if (Server_IsWindowsHost())
	{
		return Files_CallCopyBat(src, dst);
	}
	P:E("Files_CopyAsync unsupported on Linux hosts");
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *  Moves (renames) a file from <c>src</c> to <c>dst</c>.  May return before the
 *  moving has finished.  Only works on Windows as it uses <c>ShellExecute</c>
 *  to invoke native file move operations.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_MoveSync`, the async code doesn't save time.
stock bool:Files_MoveAsync(const string:src[], const string:dst[])
{
	if (Server_IsWindowsHost())
	{
		return Files_CallMoveBat(src, dst);
	}
	P:E("Files_MoveAsync unsupported on Linux hosts");
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to create.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory creation
 *  script, without using a plugin.  May return before the creation has
 *  finished.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_CreateDirSync`, the async code doesn't save time.
stock bool:Files_CreateDirAsync(const string:dir[])
{
	if (Server_IsWindowsHost())
	{
		return Files_CallMKDirBat(dir);
	}
	P:E("Files_CreateDirAsync unsupported on Linux hosts");
	return false;
}


/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to delete.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory deletion
 *  script, without using a plugin.  May return before the deletion has
 *  finished.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_RemoveDirSync`, the async code doesn't save time.
stock bool:Files_RemoveDirAsync(const string:dir[])
{
	if (Server_IsWindowsHost())
	{
		return Files_CallRMDirBat(dir);
	}
	P:E("Files_RemoveDirAsync unsupported on Linux hosts");
	return false;
}

