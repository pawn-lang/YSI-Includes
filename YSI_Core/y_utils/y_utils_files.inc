/**
 * <library
 *   name="y_utils - files"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <summary>
 *   ftouch(filename);
 * </summary>
 * <param name="filename">The file to "touch".</param>
 * <returns>
 *   0 - File already exists.
 *   1 - File was created.
 *   -1 - File was not created.
 * </returns>
 * <remarks>
 *   This "touches" a file in the Unix sense of creating it but not opening or
 *   editing it in any way.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock YSI_ftouch__(const string:filename[])
{
	if (fexist(filename))
	{
		return 0;
	}
	else
	{
		new
			File:f = fopen(filename, io_write);
		if (f)
		{
			fclose(f);
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

#if !defined ftouch
	// Turns out there's a bug in open.mp's `ftouch`, for now.
	#define ftouch( YSI_ftouch__(
	#define _ALS_ftouch
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="name">Storage for the return value.</param>
 * <param name="ext">Extension.</param>
 * <param name="path">Directory in which to place temporary files.</param>
 * <param name="len">Maximum string length.</param>
 * <remarks>
 *   Internal detail for <c>ftemporary</c>.  Should not be called directly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock File:ftemporary_(string:name[], const string:ext[] = "tmp", const string:path[] = "", len = sizeof (name))
{
	new
		pathLen = strlen(path);
	// Ensure there's space for the path (`pathLen`); the filename
	// (`YSI_TEMP_FILE_LENGTH`); the extension (`strlen(ext)`); and `'_'`,
	// `'.'`, and `'\0'` (`3`).
	// Ensure there's space for `NULL`, `_`, and at least one character.
	if (len - strlen(ext) - pathLen < YSI_TEMP_FILE_LENGTH + 3)
	{
		return File:0;
	}
	if (YSI_IsLocalVarPackedString__(name))
	{
		// These parts of the filename never change, so only do them once.
		strcat(name, path, len),
		name{pathLen} = '_',
		name{pathLen + YSI_TEMP_FILE_LENGTH + 1} = '.',
		name{pathLen + YSI_TEMP_FILE_LENGTH + 1} = '\0',
		strcat(name, ext, len);
		// Generate a random filename, with an equal distribution of letters and
		// numbers.
		do
		{
			// The post-increment here skips the `_` filename prefix.
			for (new i = pathLen; i++ < YSI_TEMP_FILE_LENGTH + pathLen; )
			{
				new ch = random(62);
				if (ch < 26)
				{
					name{i} = ch + 'a';
				}
				else if (ch < 52)
				{
					name{i} = ch + ('A' - 26);
				}
				else
				{
					name{i} = ch + ('0' - 52);
				}
			}
		}
		while (fexist(name));
	}
	else
	{
		// These parts of the filename never change, so only do them once.
		strcat(name, path, len),
		name[pathLen] = '_',
		name[pathLen + YSI_TEMP_FILE_LENGTH + 1] = '.',
		strcat(name[pathLen + YSI_TEMP_FILE_LENGTH + 2], ext, len);
		// Generate a random filename, with an equal distribution of letters and
		// numbers.
		do
		{
			// The post-increment here skips the `_` filename prefix.
			for (new i = pathLen; i++ < YSI_TEMP_FILE_LENGTH + pathLen; )
			{
				new ch = random(62);
				if (ch < 26)
				{
					name[i] = ch + 'a';
				}
				else if (ch < 52)
				{
					name[i] = ch + ('A' - 26);
				}
				else
				{
					name[i] = ch + ('0' - 52);
				}
			}
		}
		while (fexist(name));
	}
	// Open the file, to ensure it is created.
	return fopen(name, io_readwrite);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="name">File to clean up.</param>
 * <param name="maxAge">Maximum temporary file age.</param>
 * <remarks>
 *   Add a file to the temporary cleanup list.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:fautocleanup(const string:name[], maxAge)
{
	// Add the file to `.tempfiles`.
	new
		bool:initial = !fexist(YSI_TEMP_FILE_NAME),
		File:temps = fopen(YSI_TEMP_FILE_NAME, io_append);
	if (!temps)
	{
		return false;
	}
	new
		line[64];
	// First write to this file.
	if (initial)
	{
		fwrite(temps, "-- DO NOT EDIT THIS FILE, IT RECORDS THE DELETE TIMESTAMPS OF TEMPORARY FILES --\n");
	}
	return
		format(line, sizeof (line), "%d %s", gettime() + maxAge, name),
		fwrite(temps, line),
		fwrite(temps, "\n"),
		fclose(temps),
		true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="ret">Storage for the return value.</param>
 * <param name="ext">Extension.</param>
 * <param name="len">Maximum string length.</param>
 * <param name="maxAge">Maximum temporary file age.</param>
 * <remarks>
 *   Generate a random temporary filename and open it.  Also redefines
 *   <c>ftemp</c> to call this function instead if called with extra parameters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock File:ftemporary(string:ret[] = "", const string:ext[] = "tmp", len = sizeof (ret), maxAge = YSI_TEMP_FILE_AGE)
{
	// Open the file, to ensure it is created.
	if (len < 32)
	{
		// Might not have enough space to store the filename.
		new
			name[32],
			File:file = ftemporary_(name, ext, GetYSIScriptfilesDir(E_YSI_DIR_TEMP));
		if (file)
		{
			return
				ret[0] = '\0',
				strcat(ret, name, len),
				fautocleanup(name, maxAge),
				file;
		}
	}
	else if ((len = _:ftemporary_(ret, ext, GetYSIScriptfilesDir(E_YSI_DIR_TEMP), len)))
	{
		// Shortcut when the destination is big enough.
		return
			fautocleanup(ret, maxAge),
			File:len;
	}
	return File:0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <remarks>
 *   Call the original <c>ftemp</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined _ALS_ftemp
	stock File:ftemp_()
	{
		return ftemp();
	}
	#undef ftemp
#else
	native File:ftemp_() = ftemp;
	#define _ALS_ftemp
#endif

// Redefine this code so we can use `ftemp` with extra parameters, or not.
#define ftemp( ftemporary(
#define ftemporary() ftemp_()
#define _ALS_ftemporary

#if _YSI_SAFE_STARTUP
	#define _YSI_DEFAULT_DIR_PREFIX ""
#else
	#define _YSI_DEFAULT_DIR_PREFIX "YSI"
#endif

static stock
	/**
	 * <library>y_utils - files</library>
	 */
	YSI_gsDefaultDirs[E_YSI_DIR][YSI_DIR_LENGTH] = {
#if _DEBUG || defined DEBUG_DUMP
		__COMPILER_PACK _YSI_DEFAULT_DIR_PREFIX "/debug/",
#endif
#if defined YSI_TESTS
		__COMPILER_PACK _YSI_DEFAULT_DIR_PREFIX "/tests/",
		__COMPILER_PACK _YSI_DEFAULT_DIR_PREFIX "/YDBG/",
#endif
		//"/text/",
		//"/users/",
		__COMPILER_PACK _YSI_DEFAULT_DIR_PREFIX "/fixes/",
		__COMPILER_PACK _YSI_DEFAULT_DIR_PREFIX "/temp/"
	};

#undef _YSI_DEFAULT_DIR_PREFIX

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="dir">The ID of the directory.</param>
 * <returns>
 *   A directory.
 * </returns>
 * <remarks>
 *   Get a YSI scriptfiles directory, or a fallback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetYSIScriptfilesDir(E_YSI_DIR:dir)
{
	return YSI_gsDefaultDirs[dir];
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <remarks>
 *   Check if all the YSI scriptfiles directories exist.  Checks for `.gitkeep`
 *   in each folder, then each folder without `YSI/` prefix, then just nothing.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _YSI_SAFE_STARTUP
	stock ResolveYSIScriptfileDirs()
	{
		new
			#if __debug > 0
				bool:first = true,
			#endif
			path[38] = __COMPILER_UNPACK"     /scriptfiles/", // The `18`s below are this length.
			test[YSI_DIR_LENGTH + 8],
			File:file = fopen(".doesntexist/YSI", io_read);
		if (file)
		{
			// Probably bugged fopen.
			YSI_gsBuggedFOpen = true;
		}
		#if defined fcreatedir
			fcreatedir("YSI");
		#endif
		for (new E_YSI_DIR:dir = E_YSI_DIR:0; dir != E_YSI_DIR; ++dir)
		{
			if (YSI_gsDefaultDirs[dir]{0} == '/')
			{
				path[18] = '\0',
				strcat(path, __COMPILER_PACK"YSI"),
				strcat(path, YSI_gsDefaultDirs[dir]),
				StrCpy(test, path[18]),
				strcat(test, __COMPILER_PACK".gitkeep");
				if ((file = fopen(test, io_write)))
				{
					fclose(file);
				}
				if (fexist(test))
				{
					// Found `YSI/dir/`.
					StrCpy(YSI_gsDefaultDirs[dir], path[18]);
				}
				else
				{
					#if defined fcreatedir
						fcreatedir("YSI");
						fcreatedir(path[18]);
						StrCpy(YSI_gsDefaultDirs[dir], path[18]);
					#else
						#if __debug > 0
							if (first)
							{
								Server_PrintIntroPart(" Missing YSI scriptfiles directories: ", YSI_EMPTY),
								first = false;
							}
							Server_PrintIntroPart(path);
						#endif
						if ((file = fopen(test[4], io_write)))
						{
							// Found `dir/`.
							StrCpy(YSI_gsDefaultDirs[dir], path[18 + 4]),
							fclose(file);
						}
						else
						{
							// Found nothing.
							YSI_gsDefaultDirs[dir][0] = '\0';
						}
					#endif
				}
			}
		}
		#if __debug > 0
			if (!first)
			{
				Server_FinishIntroPart();
			}
		#endif
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="i">Handle to the file to copy.</param>
 * <param name="end">How much of the file to copy.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *   Copy part of a file from the current read pointer, for <c>end</c> bytes.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_CopyRange(File:i, end, const string:dst[])
{
	// Must start at the start...
	new
		File:o = fopen(dst, io_write),
		count = min(YSI_UNSAFE_HUGE_LENGTH, end >>> __cell_shift);
	if (!o)
	{
		return false;
	}
	end &= cellbytes - 1;
	// Only loop as long as we read a full block.  Partials mean the end.  Might
	// do an extra read if `count` starts out as `0`, but that only happens on
	// files less than 4 bytes long and doesn't matter anyway.
	do
	{
		count = fblockread(i, YSI_UNSAFE_HUGE_STRING, count),
		fblockwrite(o, YSI_UNSAFE_HUGE_STRING, count);
	}
	while (count == YSI_UNSAFE_HUGE_LENGTH);
	// Clean up any trailing bytes.
	while (end--)
	{
		//printf("trailing char: %d", end);
		fputchar(o, YSI_FGetChar__(i, false), false);
	}
	return bool:fclose(o);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="i">Handle to the file to copy.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *   Fast file copy routine.  Surprisingly widely used in YSI, in places where
 *   temp files were used and <c>fseek</c>ed to the start.  Closes the file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_DoCopy(File:i, const string:dst[])
{
	return
		I@ = _:(fseek(i, 0, seek_start) == 0 && Files_CopyRange(i, flength(i), dst)),
		fclose(i) && I@;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *   Copies a file from <c>src</c> to <c>dst</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_Copy(const string:src[], const string:dst[])
{
	new File:i = fopen(src, io_read);
	if (i)
	{
		return
			I@ = _:Files_CopyRange(i, flength(i), dst),
			fclose(i) && I@;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - files</library>
 * <param name="src">The name of the input file.</param>
 * <param name="dst">The name of the output file.</param>
 * <remarks>
 *   Moves a file from <c>src</c> to <c>dst</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Files_Move(const string:src[], const string:dst[])
{
	new File:i = fopen(src, io_read);
	if (i)
	{
		return
			I@ = _:Files_CopyRange(i, flength(i), dst),
			fclose(i) && I@ && fremove(src);
	}
	return false;
}

