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
	YSI_gscBatParameters[128];

static stock bool:Files_CallBat()
{
	static const
		dname[] = "YSI\\.donescript",
	// Convert the normal string to a C string.
	for (new i = 0; (YSI_gscBatParameters{i ^ 3} = YSI_gscBatParameters[i]); i++)
	{
	}
	fremove(dname);
	if (ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, YSI_gscBatParameters, SW_HIDE) > 32)
	{
		while (!fexist(dname))
		{
			// Poll for the script to finish.
		}
		return true;
	}
	return false;
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
	new bool:ret = ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, !"s C/pirclift_\\setini.isy\0tab", SW_HIDE) > 32;
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

static stock bool:Files_CallMKDirBat(const string:folder[])
{
	return
		format(YSI_gscBatParameters, sizeof (YSI_gscBatParameters), "%smkdir.bat \"%s\"", YSI_gscBasePath, folder),
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

static stock bool:Files_CallCopyBat(const string:src[], const string:dst[])
{
	return
		format(YSI_gscBatParameters, sizeof (YSI_gscBatParameters), "%scopy.bat \"%s\" \"%s\"", YSI_gscBasePath, src, dst),
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

static stock bool:Files_CallMoveBat(const string:src[], const string:dst[])
{
	return
		format(YSI_gscBatParameters, sizeof (YSI_gscBatParameters), "%smove.bat \"%s\" \"%s\"", YSI_gscBasePath, src, dst),
		Files_CallBat();
}

public OnCodeInit()
{
	if (Server_IsWindowsHost())
	{
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

