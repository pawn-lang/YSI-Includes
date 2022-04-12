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
	Portions created by the Initial Developer are Copyright (c) 2022
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

forward bool:Files_CreateDirSync(const string:dir[]);

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to delete.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory deletion
 *  script, without using a plugin.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward bool:Files_RemoveDirSync(const string:dir[]);

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
forward bool:Files_CopyAsync(const string:src[], const string:dst[]);

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
forward bool:Files_MoveAsync(const string:src[], const string:dst[]);

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to create.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory creation
 *  script, without using a plugin.  May return before the creation has
 *  finished.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_CreateDirSync`, the async code doesn't save time.
forward bool:Files_CreateDirAsync(const string:dir[]);

/*-------------------------------------------------------------------------*//**
 * <param name="dir">The name of the directory to delete.</param>
 * <remarks>
 *  Uses <c>ShellExecute</c> on Windows only to invoke a directory deletion
 *  script, without using a plugin.  May return before the deletion has
 *  finished.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Files_RemoveDirSync`, the async code doesn't save time.
forward bool:Files_RemoveDirAsync(const string:dir[]);

