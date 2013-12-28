stock const
	INI:INI_NO_FILE = INI:-1;

static stock const
	INI_HEADER_SIZE = 0;

#define INI_FILE_NAME_LENGTH (64)
// Load the file for reading and writing.  Should now support variable access.

enum E_INI_FILE
{
	E_INI_FILE_NAME[INI_FILE_NAME_LENGTH char],
	//E_INI_FILE_HANDLE,
	E_INI_FILE_LENGTH,
	E_INI_FILE_ALLOCATED,
	Alloc:E_INI_FILE_DATA
}

enum e_INI_LINE_TYPE
{
	e_INI_LINE_TYPE_INVALID,
	e_INI_LINE_TYPE_BLANK,
	e_INI_LINE_TYPE_ENTRY,
	e_INI_LINE_TYPE_TAG
}

_Y_INI_STATIC stock
	YSI_g_sINIFiles[INI:2][E_INI_FILE],
	YSI_g_sOneLine[YSI_MAX_STRING];

// Is the current index the start of a line?

_Y_INI_STATIC stock bool:INI_AtStartOfLine(const str[], index)
{
	for (new ch; index--; )
	{
		if ((ch = str[index]) > ' ') return false;
		if (ch == '\r' || ch == '\n') return true;
	}
	return true;
}

//INI_FindEntry(const data[], const tag[]

// stock bool:INI_ParseFile(fname[], remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bFilter = true, filter[] = "")
// {
	// new
		// INI:ini = INI:0;
	// if (ini == INI_NO_FILE) return false;
	// INI_SetupParse(fname, YSI_g_sINIFiles[ini], false);
// }

// _Y_INI_STATIC stock bool:INI_SetupParse(fname[], ini, bool:allocate)
// {
	// // Get an empty info slot.
	// // Open the file.
	// new
		// File:f = fopen(fname);
	// if (!f) return false;
	// // Save the filename.
	// strpack(ini[E_INI_FILE_NAME], fname, INI_FILE_NAME_LENGTH);
	// new
		// // Get the filesize.
		// len = flength(f),
	// ini[E_INI_FILE_LENGTH] = len;
	// ini[E_INI_FILE_ALLOCATED] = len * 2 + INI_HEADER_SIZE;
	// if (allocate)
	// {
		// new
			// // Allocate the memory.
			// Alloc:a = malloc(len * 2 + INI_HEADER_SIZE);
		// ini[E_INI_FILE_DATA] = a;
		// if (a == NO_ALLOC)
		// {
			// Alloc:a = malloc(len + INI_HEADER_SIZE);
			// ini[E_INI_FILE_ALLOCATED] = len + INI_HEADER_SIZE;
			// ini[E_INI_FILE_DATA] = a;
			// if (a == NO_ALLOC)
			// {
				// P:W("Could not allocate memory for INI file - using (slow) fallback.");
				// INI_OldLoad(f);
				// fclose(file);
				// return true;
			// }
			// P:W("Could not allocate extra memory for INI file - writes may be slow.");
		// }
	// }
	// else
	// {
		// ini[E_INI_FILE_ALLOCATED] = 0;
		// ini[E_INI_FILE_DATA] = NO_ALLOC;
	// }
	// INI_NewLoad(f, ini);
	// fclose(file);
	// return true;
// }

/*

    88888888888                           
    88                             ,d     
    88                             88     
    88aaaaa ,adPPYYba, ,adPPYba, MM88MMM  
    88""""" ""     `Y8 I8[    ""   88     
    88      ,adPPPPP88  `"Y8ba,    88     
    88      88,    ,88 aa    ]8I   88,    
    88      `"8bbdP"Y8 `"YbbdP"'   "Y888  

*/

// _Y_INI_STATIC stock INI_NewLoad(File:file, INI:ini) // Alloc:data)
// {
	// new
		// Alloc:data = ini[E_INI_FILE_DATA];
	// // Don't make assumptions here.  It may be that it doesn't WANT saving.
	// if (data == NO_ALLOC) INI_ParseFileCalled(file);
	// // We have now loaded the file in to memory.
	// else INI_ParseFileSaved(file, data);
// }

// _Y_INI_STATIC stock INI_ParseFileCalled(File:file, INI:ini)
// {
	// // Load the data into a line buffer.
	// while (fread(file, YSI_g_sOneLine))
	// {
		// // Parse the line for callbacks.
		// //INI_ParseLine(YSI_g_sOneLine, some, callback, data);
	// }
// }

// _Y_INI_STATIC stock INI_ParseFileSaved(File:file, INI:ini) //, Alloc:data)
// {
	// // Load the data into the allocated slot.
	// // Read the whole file, accounting for unicode characters.
	// new
		// pos = INI_HEADER_SIZE,
		// read;
	// // We don't check the length because it must be enough.
	// while ((read = fread(file, mget(data, pos), cellmax)))
	// {
		// // Parse the line for callbacks.
		// //INI_ParseLine(mget(data, pos), some, callback, data);
		// pos += read;
	// }
// }



/*

     ad88888ba  88                                 
    d8"     "8b 88                                 
    Y8,         88                                 
    `Y8aaaaa,   88  ,adPPYba,  8b      db      d8  
      `"""""8b, 88 a8"     "8a `8b    d88b    d8'  
            `8b 88 8b       d8  `8b  d8'`8b  d8'   
    Y8a     a8P 88 "8a,   ,a8"   `8bd8'  `8bd8'    
     "Y88888P"  88  `"YbbdP"'      YP      YP      

*/

/**--------------------------------------------------------------------------**\
<summary>INI_IsEscapeSequence</summary>
<param name="str[]">String with the character in.</param>
<param name="pos">Location of the character.</param>
<returns>
	Is the current character escaped?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock bool:INI_IsEscapeSequence(const str[], pos)
{
	new
		bool:escape = false;
	// Invert for every sequential escape character.
	while (pos && str[--pos] == '\\') escape ^= true;
	return escape;
}

/**--------------------------------------------------------------------------**\
<summary>INI_ReverseWhitespace</summary>
<param name="str[]">String with the whitespace in.</param>
<param name="pos">End of the whitespace.</param>
<returns>
	Start of the whitespace.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_ReverseWhitespace(const str[], pos)
{
	while (pos-- && '\0' < str[pos] <= ' ') {}
	return pos + 1;
}

/**--------------------------------------------------------------------------**\
<summary>INI_FindString</summary>
<param name="str[]">The string you want to search in.</param>
<param name="sub[]">The string you want to search for.</param>
<param name="pos">The start offset.</param>
<returns>
	Position when found, "cellmax - 1" on fail.
</returns>
<remarks>
	Uses "cellmax" not "-1" as a failure return as it is easier to utilise in
	later code (it is only used as an upper-bound on line positions).  This is
	similar to "strfind", but accounts for escape sequences.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_FindString(const str[], const sub[], pos = -1)
{
	// Determine if there is a substring in this string (can be escaped).
	do
	{
		// Find the next possible candidate for starting a comment.
		pos = strfind(str, sub, false, pos + 1);
		if (pos == -1) return cellmax;
	}
	while (INI_IsEscapeSequence(str, pos));
	return pos;
}

/**--------------------------------------------------------------------------**\
<summary>INI_GetEntryText</summary>
<param name="str[]">The string you want to type analyse.</param>
<param name="p0s">Start of part 0.</param>
<param name="p0e">End of part 0.</param>
<param name="p1s">Start of part 1.</param>
<param name="p1e">End of part 1.</param>
<param name="p2s">Start of part 2.</param>
<param name="p2e">End of part 2.</param>
<returns>
	e_INI_LINE_TYPE
</returns>
<remarks>
	This function's signature is so long that I put it on a separate line.  This
	takes a line and determines what it is and where the parts are.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock e_INI_LINE_TYPE:
	INI_IdentifyLineType(const str[], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e)
{
	// Determine if there is a comment in this string (can be escaped).
	if (!(p2s = min(INI_FindString(str, ";"), (p2e = INI_ReverseWhitespace(str, strlen(str)))))) return e_INI_LINE_TYPE_BLANK;
	// Here "p2s" is the end of any valid string contents.  "INI_FindString"
	// will return "cellmax" on failure for a direct comparison.
	if ((p0e = INI_FindString(str, "=")) > p2s)
	{
		// Equals sign is commented out or not present (cellmax return).  If we
		// are in here, it can't be a "key = value" entry.
		if ((p0s = INI_FindString(str, "[")) > p2s)
		{
			// Not a tag.
			if (SkipWhitespace(str, 0) == p2s) return e_INI_LINE_TYPE_BLANK;
		}
		else
		{
			// Found "[", look for "]".
			if ((p0e = INI_FindString(str, "]", p0s++)) < p2s)
			{
				// Skip excess whitespace off the tag name.
				Trim(str, p0s, p0e);
				// Empty tag name.
				if (p0s == p0e) return e_INI_LINE_TYPE_INVALID;
				p1s = INI_FindString(str, ":");
				if (p1s == cellmax)
				{
					// No extension.
					p1e = cellmax;
				}
				else
				{
					// Extension.
					++p1s,
					p1e = p2s,
					Trim(str, p1s, p1e);
				}
				return e_INI_LINE_TYPE_TAG;
			}
			// No "]" found.
		}
	}
	else
	{
		// Set key and value limits.
		p0s = 0, p1s = p0e + 1, p1e = p2s;
		// Remove excess whitespace from the key and the value.
		Trim(str, p0s, p0e),
		// Skip the "=" sign, then trim.
		Trim(str, p1s, p1e);
		// Check for escaped trailing spaces.
		if (INI_IsEscapeSequence(str, p1e)) ++p1e;
		// On lines like:
		//  
		//  [tag-like] = value-like
		//  
		// What should that be?  Probably invalid, but I'll allow it!
		if (p0s != p0e && p1s != p1e) return e_INI_LINE_TYPE_ENTRY;
	}
	// There are several ways to get here.
	return e_INI_LINE_TYPE_INVALID;
}

// INI_LoopThroughFile(File:f, INI:ini, end)
// {
	// // Go to the start of the file.
	// fseek(f, 0);
// }












