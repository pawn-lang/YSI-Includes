// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

// #include <a_samp>

// #include <YSI_Coding\y_malloc>

#define _Y_INI_STATIC

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
	e_INI_LINE_TYPE_COMMENT,
	e_INI_LINE_TYPE_BLANK,
	e_INI_LINE_TYPE_ENTRY,
	e_INI_LINE_TYPE_TAG
}

_Y_INI_STATIC stock
	YSI_g_sINIFiles[INI:2][E_INI_FILE],
	YSI_g_sOneLine[YSI_MAX_STRING];

// Is the current index the start of a line?

_Y_INI_STATIC stock INI_AtStartOfLine(const string:str[], index)
{
	for (new ch; index--; )
	{
		if ((ch = str[index]) > ' ') return false;
		if (ch == '\r' || ch == '\n') return true;
	}
	return true;
}

//INI_FindEntry(const string:data[], const string:tag[]

stock bool:INI_ParseFile(fname[], remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bFilter = true, filter[] = "")
{
	new
		INI:ini = INI:0;
	if (ini == INI_NO_FILE) return false;
	INI_SetupParse(fname, YSI_g_sINIFiles[ini], false);
}

_Y_INI_STATIC stock bool:INI_SetupParse(fname[], ini, bool:allocate)
{
	// Get an empty info slot.
	// Open the file.
	new
		File:f = fopen(fname);
	if (!f) return false;
	// Save the filename.
	strpack(ini[E_INI_FILE_NAME], fname, INI_FILE_NAME_LENGTH);
	new
		// Get the filesize.
		len = flength(f),
	ini[E_INI_FILE_LENGTH] = len;
	ini[E_INI_FILE_ALLOCATED] = len * 2 + INI_HEADER_SIZE;
	if (allocate)
	{
		new
			// Allocate the memory.
			Alloc:a = malloc(len * 2 + INI_HEADER_SIZE);
		ini[E_INI_FILE_DATA] = a;
		if (a == NO_ALLOC)
		{
			Alloc:a = malloc(len + INI_HEADER_SIZE);
			ini[E_INI_FILE_ALLOCATED] = len + INI_HEADER_SIZE;
			ini[E_INI_FILE_DATA] = a;
			if (a == NO_ALLOC)
			{
				P:W("Could not allocate memory for INI file - using (slow) fallback.");
				INI_OldLoad(f);
				fclose(file);
				return true;
			}
			P:W("Could not allocate extra memory for INI file - writes may be slow.");
		}
	}
	else
	{
		ini[E_INI_FILE_ALLOCATED] = 0;
		ini[E_INI_FILE_DATA] = NO_ALLOC;
	}
	INI_NewLoad(f, ini);
	fclose(file);
	return true;
}

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

_Y_INI_STATIC stock INI_NewLoad(File:file, INI:ini) // Alloc:data)
{
	new
		Alloc:data = ini[E_INI_FILE_DATA];
	// Don't make assumptions here.  It may be that it doesn't WANT saving.
	if (data == NO_ALLOC) INI_ParseFileCalled(file);
	// We have now loaded the file in to memory.
	else INI_ParseFileSaved(file, data);
}

_Y_INI_STATIC stock INI_ParseFileCalled(File:file, INI:ini)
{
	// Load the data into a line buffer.
	while (fread(file, YSI_g_sOneLine))
	{
		// Parse the line for callbacks.
		//INI_ParseLine(YSI_g_sOneLine, some, callback, data);
	}
}

_Y_INI_STATIC stock INI_ParseFileSaved(File:file, INI:ini) //, Alloc:data)
{
	// Load the data into the allocated slot.
	// Read the whole file, accounting for unicode characters.
	new
		pos = INI_HEADER_SIZE,
		read;
	// We don't check the length because it must be enough.
	while ((read = fread(file, mget(data, pos), cellmax)))
	{
		// Parse the line for callbacks.
		//INI_ParseLine(mget(data, pos), some, callback, data);
		pos += read;
	}
}



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
<param name="string:str[]">String with the character in.</param>
<param name="pos">Location of the character.</param>
<returns>
	Is the current character escaped?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock bool:INI_IsEscapeSequence(const string:str[], pos)
{
	new
		bool:escape = false;
	// Invert for every sequential escape character.
	while (pos && str[--pos] == '\\') escape ^= true;
	return escape;
}

/**--------------------------------------------------------------------------**\
<summary>INI_GetCommentPos</summary>
<param name="string:str[]">The string you want to de-comment.</param>
<returns>
	-
</returns>
<remarks>
	Find where a comment starts on this line, if anywhere.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_GetCommentPos(const string:str[])
{
	// Determine if there is a comment in this string (can be escaped).
	new
		comment = -1;
	do
	{
		comment = strfind(str, ";", false, comment + 1);
		if (comment == -1) return -1;
	}
	while (INI_IsEscapeSequence(str, comment));
	return comment;
}

/**--------------------------------------------------------------------------**\
<summary>INI_GetEntryText</summary>
<param name="string:str[]">The string you want to type analyse.</param>
<param name="p0s">Start of part 0.</param>
<param name="p0e">End of part 0.</param>
<param name="p1s">Start of part 1.</param>
<param name="p1e">End of part 1.</param>
<returns>
	e_INI_LINE_TYPE
</returns>
<remarks>
	This function's signature is so long that I put it on a separate line.  This
	takes a line and determines what it is and where the parts are.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock e_INI_LINE_TYPE:
	INI_IdentifyLineType(const string:str[], &p0s, &p0e, &p1s, &p1e)
{
	// Determine if there is a comment in this string (can be escaped).
	new
		comment = INI_GetCommentPos(str);
	new
		pos = 0;
	// Loop over any whitespace.
	while ('\0' < str[pos] <= ' ') ++pos;
	// Determine what the first character is.
	switch (str[pos])
	{
		case '\0': return e_INI_LINE_TYPE_BLANK;
		case ';': return e_INI_LINE_TYPE_COMMENT;
		case '[':
		{
			// Found a tag.
			p1s = strfind(str, "]", false, (p0s = pos + 1));
			// Not completed correctly.
			if (p1s == -1) return e_INI_LINE_TYPE_INVALID;
			// Are there any extensions?
		}
		default:
	}
}






INI_LoopThroughFile(File:f, INI:ini, end)
{
	// Go to the start of the file.
	fseek(f, 0);
	
	
	
}












