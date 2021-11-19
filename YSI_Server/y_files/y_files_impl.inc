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

static stock bool:Files_WriteMKDirBat()
{
	new File:f = fopen("YSI\\scripts\\mkdir.bat", io_write);
	if (f)
	{
		fwrite(f, "set dir=scriptfiles\\%~1\r\nset dir=%dir:..=%\r\nset dir=%dir:\\\\=\\%\r\nmkdir \"%dir%\"\r\n");
		fclose(f);
		return true;
	}
	return false;
}

bool:CallMKDirBat(const string:folder[])
{
	new
		cmd[] = !".dmc\0exe", // "cmd.exe" byteswapped.
		operation[] = !"nepo", // "open" byteswapped.
		//cmd[] = !"cmd.exe",
		//operation[] = !"open",
		parameters[128];
	format(parameters, sizeof (parameters), "/C scriptfiles\\mkdir.bat \"%s\"", folder);
	//strpack(parameters, parameters);

	//ToCharString(cmd);
	//ToCharString(operation);
	ToCharString(parameters);

	return ShellExecute(YSI_gscBatOperation, YSI_gscBatCmd, parameters, SW_HIDE) > 32;
}

static stock bool:Files_WriteMKDirBat()
{
	new File:f = fopen("YSI\\scripts\\mkdir.bat", io_write);
	if (f)
	{
		fwrite(f, "set dir=scriptfiles\\%~1\r\nset dir=%dir:..=%\r\nset dir=%dir:\\\\=\\%\r\nmkdir \"%dir%\"\r\n");
		fclose(f);
		return true;
	}
	return false;
}
