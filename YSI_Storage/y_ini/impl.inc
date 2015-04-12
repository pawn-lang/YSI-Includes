/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           
    
*/

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
	e_INI_LINE_TYPE_CONT,
	e_INI_LINE_TYPE_TAG
}

_Y_INI_STATIC stock
	YSI_g_sINIFiles[INI:2][E_INI_FILE],
	YSI_g_sOneLine[YSI_MAX_STRING];

/*

    88b           d88                                                         
    888b         d888                                                         
    88`8b       d8'88                                                         
    88 `8b     d8' 88 ,adPPYYba,  ,adPPYba, 8b,dPPYba,  ,adPPYba,  ,adPPYba,  
    88  `8b   d8'  88 ""     `Y8 a8"     "" 88P'   "Y8 a8"     "8a I8[    ""  
    88   `8b d8'   88 ,adPPPPP88 8b         88         8b       d8  `"Y8ba,   
    88    `888'    88 88,    ,88 "8a,   ,aa 88         "8a,   ,a8" aa    ]8I  
    88     `8'     88 `"8bbdP"Y8  `"Ybbd8"' 88          `"YbbdP"'  `"YbbdP"'  

*/

#define INI_Int(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = strval(value)

#define INI_Float(%1,%2) \
	if (!strcmp((%1), name, true)) return _:(%2 = floatstr(value))

#define INI_Hex(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = hexstr(value)

#define INI_Bin(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = binstr(value)

#define INI_Bool(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = boolstr(value)

#define INI_String(%1,%2) \
	if (!strcmp((%1), name, true)) return _:INI_CHECK_LEN:strcpy(%2, value)

// The old version of "INI_String" didn't like not having a length.  Correct
// this.  It gave a very odd error message too.
#define INI_CHECK_LEN:strcpy(%0,%1,%2) strcpy(%0,%2,%1)

// Basic checks to see if extension parts exist for INI tags, and if comments
// exist for any lines.
// #define INI_HAS_INHERITANCE_PART (p1s != p1e)
// #define INI_HAS_COMMENT_PART     (p2s != p2e)

/*

    88        88         88 88            
    88        88   ,d    "" 88            
    88        88   88       88            
    88        88 MM88MMM 88 88 ,adPPYba,  
    88        88   88    88 88 I8[    ""  
    88        88   88    88 88  `"Y8ba,   
    Y8a.    .a8P   88,   88 88 aa    ]8I  
     `"Y8888Y"'    "Y888 88 88 `"YbbdP"'  

*/

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

/*_Y_INI_STATIC*/ stock bool:INI_IsEscapeSequence(const str[], pos)
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

/*_Y_INI_STATIC*/ stock INI_ReverseWhitespace(const str[], pos)
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

/*_Y_INI_STATIC*/ stock INI_FindString(const str[], const sub[], pos = -1)
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

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

/**--------------------------------------------------------------------------**\
<summary>INI_GetEntryText</summary>
<param name="str[]">The string you want to type analyse.</param>
<param name="p0s">Start of part 0.</param>
<param name="p0e">End of part 0.</param>
<param name="p1s">Start of part 1.</param>
<param name="p1e">End of part 1.</param>
<param name="p2s">Start of part 2.</param>
<param name="p2e">End of part 2.</param>
<param name="cont">Is this a line continuation?</param>
<returns>
	e_INI_LINE_TYPE
</returns>
<remarks>
	This function's signature is so long that I put it on a separate line.  This
	takes a line and determines what it is and where the parts are.
</remarks>
\**--------------------------------------------------------------------------**/

#define INI_SkipWhitespace(%0,%1) while ('\0' < %0[%1] <= ' ') ++%1

_Y_INI_STATIC stock e_INI_LINE_TYPE:
	INI_IdentifyLineType(const str[], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e)
{
	// Reset everything.
	p0s = p0e = p1s = p1e = p2s = p2e = 0;
	// Do this purely with a single main loop, and a state machine.
	new
		end,
		e_INI_LINE_TYPE:ret = e_INI_LINE_TYPE_BLANK,
		pos;
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_BLANK;
		case  ';': goto state_in_comment;
		case  '[': goto state_in_tag;
		case '\\':
			if (str[pos])
			{
				p0s = pos - 1,
				end = ++pos;
			}
			else return e_INI_LINE_TYPE_INVALID;
		case '=': return e_INI_LINE_TYPE_INVALID;
		default: p0s = pos - 1;
	}
//state_in_entry: // Default (fall-through).
	// Get the key.
	for ( ; ; )
	{
		switch (str[pos++])
		{
			case '\0', ';':
				return e_INI_LINE_TYPE_INVALID;      // No value.
			case '\\':
				if (str[pos]) end = ++pos;           // Skip next character too.
				else return e_INI_LINE_TYPE_INVALID; // Escaping nothing.
			case '=': break;
			case '\1' .. ' ': {} // Whitespace, skip it.
			default: end = pos;  // Characters, save this position.
		}
	}
	p0e = end;
	// See what comes next.
	INI_SkipWhitespace(str, pos);
	switch (str[pos])
	{
		case '\0', ';': return e_INI_LINE_TYPE_INVALID;
		case '\\':
			if (str[pos + 1]) p1s = pos++, end = ++pos;
			else return e_INI_LINE_TYPE_INVALID;
		default: p1s = pos++, end = pos;
	}
	for ( ; ; )
	{
		switch (str[pos++])
		{
			case '\0': return p1e = end, e_INI_LINE_TYPE_ENTRY;
			case  ';':
			{
				p1e = end,
				ret  = e_INI_LINE_TYPE_ENTRY;
				goto state_in_comment;
			}
			case '\\':
				if (str[pos]) end = ++pos;           // Skip next character too.
				else return e_INI_LINE_TYPE_INVALID; // Escaping nothing.
			case '\1' .. ' ': {} // Whitespace, skip it.
			default: end = pos;  // Characters, save this position.
		}
	}
state_in_tag:
	// Get the tag name.
	INI_SkipWhitespace(str, pos);
	p0s = pos;
	for ( ; ; )
	{
		switch (str[pos++])
		{
			case '\0', ';':
				return e_INI_LINE_TYPE_INVALID;      // No tag end.
			case '\\':
				if (str[pos]) end = ++pos;           // Skip next character too.
				else return e_INI_LINE_TYPE_INVALID; // Escaping nothing.
			case ']':
				if (end) break;                      // End of the tag.
				else return e_INI_LINE_TYPE_INVALID; // Tag is empty.
			case '\1' .. ' ': {} // Whitespace, skip it.
			default: end = pos;  // Characters, save this position.
		}
	}
	p0e = end;
	// See what comes next.
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_TAG; // Line over.
		case  ';':
		{
			// Skip over the comments.
			ret = e_INI_LINE_TYPE_TAG;
			goto state_in_comment;
		}
		case  ':': {}
		default  : return e_INI_LINE_TYPE_INVALID; // Unexpected characters.
	}
	// Get the inheritance.
	INI_SkipWhitespace(str, pos);
	if (!str[pos]) return e_INI_LINE_TYPE_INVALID; // No parent tag.
	p1s = pos;
	while (str[pos] > ' ') ++pos;
	p1e = pos;
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_TAG;     // Line over.
		case  ';': ret  = e_INI_LINE_TYPE_TAG;
		default  : return e_INI_LINE_TYPE_INVALID; // Unexpected characters.
	}
state_in_comment:
	INI_SkipWhitespace(str, pos);
	if (str[pos])
	{
		p2s = pos,
		// Non-empty comment.
		pos = strlen(str);
		while (pos-- && str[pos] <= ' ') {}
		p2e = pos + 1;
	}
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>INI_SetupCallbackName</summary>
<param name="fmat[]">The format destination.</param>
<param name="const remoteFormat[]">The source format.</param>
<param name="filename[]">The file we are currently parsing.</param>
<param name="const bool:bFileFirst">The format parameter ordering.</param>
<returns>
	-
</returns>
<remarks>
	Generates a partial function name for processing callbacks.  Includes the
	filename and a placeholder for the tag name.  This now takes extra
	characters in to account and strips or converts bits:
	
		some/dir/file name.ext
	
	Becomes:
	
		file_name
	
	Before being formatted in to the specified remote format.  The filename
	also takes in to account "/" directory separators and "\\" ones on Windows.
	
	Because the	majority of this function is concerned with formatting just part
	of the function name correctly, it short-circuits if it detects that there
	is no place for the function name to go.
	
	This is quite a complex function, but is only called once per file parse.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_SetupCallbackName(fmat[32], const remoteFormat[], filename[], const bool:bFileFirst)
{
	// Copy the basic format over.
	strcpy(fmat, remoteFormat);
	// Before any complex filename parsing, check if we actually need it.
	new
		fpos = strfind(remoteFormat, "%s");
	if (!bFileFirst) fpos = strfind(remoteFormat, "%s", false, fpos + 1);
	// Is there a position in "remoteFormat" for "filename"?
	if (fpos == -1) return 0;
	new
		pos,
		prev = 0;
	// Isolate just the VALID name of the file, not the path or extension.
	while ((pos = strfind(filename, "/" , false, pos) + 1)) prev = pos;
	pos = prev;
	if (IsWindows())
	{
		while ((pos = strfind(filename, "\\", false, pos) + 1)) prev = pos;
		pos = prev;
	}
	// Got the start of the name, now find the end.
	for (new ch; ; )
	{
		// Get the extent of the valid function characters.
		for ( ; ; )
		{
			ch = filename[pos];
			if ('a' <= ch <= 'z' || 'A' <= ch <= 'Z' || '0' <= ch <= '9' || ch == '_' || ch == '@') ++pos;
			else break;
		}
		// Make the secondary format.
		filename[pos] = '\0';
		if (bFileFirst) format(fmat, sizeof (fmat), fmat, filename[prev], "%s");
		else format(fmat, sizeof (fmat), fmat, "%s", filename[prev]);
		filename[pos] = ch;
		// Add spaces as "_".
		P:7("INI_SetupCallbackName: '%02x' \"%s\" -> \"%s\" %d %d %d", ch, filename[prev], fmat, fpos, prev, pos);
		if (ch == ' ')
		{
			fpos += pos - prev,
			strins(fmat, "_%s", fpos++),
			prev = ++pos;
			P:7("INI_SetupCallbackName: \"%s\" -> \"%s\" %d %d %d", filename[prev], fmat, fpos, prev, pos);
		}
		else break;
	}
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>INI_GetCallback</summary>
<param name="callback[E_CALLBACK_DATA]">The callback destination.</param>
<param name="const format[]">The function name format.</param>
<param name="tag[]">The tag destination.</param>
<param name="const input[]">The tag source.</param>
<param name="const len">The tag length.</param>
<param name="tag[]">The tag destination.</param>
<param name="callbackFormat[]">The callback parameter specifiers.</param>
<param name="const bool:remote">Use "CallRemoteFunction".</param>
<returns>
	Was the function found?
</returns>
<remarks>
	Gets a callback given a partial function name and a tag name.  Also saves
	the tag elsewhere.  This might not work as a separate function - it will
	need to be in the function called by the function with the inlines in.
</remarks>
\**--------------------------------------------------------------------------**/

#define INI_GetCallback(%0,%1,%2,%3,%4,%5) \
	( \
		strcpy((%2), (%3)), \
		Inline_Reset((%0)), \
		format(YSI_g_sCurLine, sizeof (YSI_g_sCurLine), (%1), (%2)), \
		Callback_Get(callback_tag:YSI_g_sCurLine, (%0), (%4), (%5)) \
	)

/**--------------------------------------------------------------------------**\
<summary>INI_ParseFile</summary>
<param name="filename[]">The file to load.</param>
<param name="remoteFormat[]">The format string to generate the remote function
t pass the data to once loaded.</param>
<param name="bool:bFileFirst">The order of the remoteFormat parameters.</param>
<param name="bool:bExtra">Send additional data.</param>
<param name="extra">Additional data to send.</param>
<param name="bLocal">Call local functions instead of global ones.</param>
<param name="bPassTag">Pass the tag as an extra parameter not the function
name.</param>
<param name="bFilter">Apply the tag name filter to all tags or just prefixed
ones?</param>
<param name="filter">Text to use to search for which tags to load.</param>
<returns>
	-
</returns>
<remarks>
	bFileFirst sets the order and inclusion of the possible remoteFormat
	parameters.  If true the format will add the filename first then the 
	current tag, if false the order will be reversed.  This can also be used
	to exclude one or the other from the function name by setting the required
	parameter to be entered first and then only having one %s in the format
	sting.  The default order is tag first for languages compatibility.
</remarks>
\**--------------------------------------------------------------------------**/

static stock
	YSI_g_sCurLine[YSI_MAX_INLINE_STRING];

stock bool:INI_ParseFile(fname[], remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bFilter = true, filter[] = "")
{
	P:3("bool:INI_ParseFile called: \"%s\", \"%s\", %i, %i, %i, %i, %i, %i, \"%s\"", fname, remoteFormat, bFileFirst, bExtra, extra, bLocal, bPassTag, bFilter, filter);
	printf("0");
	static
		callback[E_CALLBACK_DATA],
		tag[32],    // The current tag being parsed.
		cbSpec[5],  // The callback specifier.
		cbName[32]; // The callback name format.
	new
		File:f = fopen(fname, io_read);
	if (!f) return false;
	new
		rlen, ppos,
		p0s, p0e, p1s, p1e, p2s, p2e;
	P:5("INI_ParseFile: Opened.");
	bLocal = !bLocal, // Invert for "remote".
	printf("0a");
	INI_MakeCallbackFormat(bExtra, bPassTag, cbSpec),
	printf("0b");
	INI_SetupCallbackName(cbName, remoteFormat, fname, bFileFirst);
	printf("0c");
	new
		bool:handle = INI_GetCallback(callback, cbName, tag, "", cbSpec, bLocal);
	printf("1");
	while ((rlen = fread(f, YSI_g_sCurLine)))
	{
		printf("2a");
		ppos += rlen;
		printf("2b");
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID:
			{
				printf("3a");
				// "P:I" not "P:W" because this is not a script issue.
				P:I("Invalid line in INI file \"%s\": %s", fname, YSI_g_sCurLine);
			}
			case e_INI_LINE_TYPE_BLANK:
			{
				printf("3b");
				// Do nothing.
			}
			case e_INI_LINE_TYPE_TAG:
			{
				printf("3c");
				// A new tag.
				Callback_Restore(callback),
				Callback_Release(callback),
				// First, check if it is a tag we might care about.
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s] == '@' && YSI_g_sCurLine[p0s + 1] == '@' && (p0e = strfind(YSI_g_sCurLine, "-")) != -1)
				{
					// Check if the current tag is one of the ones we want to
					// filer for.  The "@@" prefix is the "filterable" prefix.
					// If there is no filter then everything will be loaded.
					if (p0e == p0s + 2 || !YSI_g_sCurLine[p0e + 1])
					{
						P:I("Invalid line in INI file \"%s\": %s", fname, YSI_g_sCurLine);
						continue;
					}
					YSI_g_sCurLine[p0e] = '\0';
					if (bFilter && strcmp(YSI_g_sCurLine[p0s + 2], filter))
					{
						// Only skip this if filtering is enabled.  We can't put
						// the "bFilter" check higher or the "-" won't be found
						// to resolve the tag name accurately.
						handle = false;
						continue;
					}
					p0s = p0e + 1;
				}
				// This is a tag we can use, is there a handler for it?
				// Is this based on another tag?  If so recurse and do that one
				// first.
				new
					parent[32];
				YSI_g_sCurLine[p1e] = '\0', strcat(parent, YSI_g_sCurLine[p1s]);
				if ((handle = INI_GetCallback(callback, cbName, tag, YSI_g_sCurLine[p0s], cbSpec, bLocal)) && p1s != p1e)
				{
					// No point recursing if there's no handler is there?
					if (!INI_DoParentTag(ppos, parent, f, callback, bExtra, extra, bPassTag, tag, bFilter, filter))
						P:I("Invalid hierarchy in INI file: \"%s\" for tag \"%s\"", fname, tag);
					fseek(f, ppos, seek_start);
				}
			}
			default: // e_INI_LINE_TYPE_ENTRY and e_INI_LINE_TYPE_CONT.
			{
				printf("3d");
				if (!handle) continue;
				// Standard key-value pair.
				YSI_g_sCurLine[p0e] = YSI_g_sCurLine[p1e] = '\0';
				if (bExtra)
				{
					if (bPassTag) Callback_Call(callback, extra, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
					else          Callback_Call(callback, extra,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
				}
				else
				{
					if (bPassTag) Callback_Call(callback,        tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
					else          Callback_Call(callback,             YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
				}
			}
		}
		printf("4");
		// Don't put any code down here (at the end of the loop).
	} // while (fread(f, line))
	printf("5");
	return
		Callback_Restore(callback),
		Callback_Release(callback),
		fclose(f),
		true;
}

_Y_INI_STATIC stock INI_MakeCallbackFormat(const bool:bExtra, const bool:bPassTag, callbackFormat[5])
{
	if (bExtra)
	{
		if (bPassTag) callbackFormat = _F<isss>;
		else          callbackFormat = _F<iss>;
	}
	else
	{
		if (bPassTag) callbackFormat = _F<sss>;
		else          callbackFormat = _F<ss>;
	}
}

/**--------------------------------------------------------------------------**\
<summary>INI_DoParentTag</summary>
<param name="filename[]">The file to load.</param>
<param name="remoteFormat[]">The format string to generate the remote function
t pass the data to once loaded.</param>
<param name="bool:bFileFirst">The order of the remoteFormat parameters.</param>
<param name="bool:bExtra">Send additional data.</param>
<param name="extra">Additional data to send.</param>
<param name="bLocal">Call local functions instead of global ones.</param>
<param name="bPassTag">Pass the tag as an extra parameter not the function
name.</param>
<param name="bFilter">Apply the tag name filter to all tags or just prefixed
ones?</param>
<param name="filter">Text to use to search for which tags to load.</param>
<returns>
	-
</returns>
<remarks>
	bFileFirst sets the order and inclusion of the possible remoteFormat
	parameters.  If true the format will add the filename first then the 
	current tag, if false the order will be reversed.  This can also be used
	to exclude one or the other from the function name by setting the required
	parameter to be entered first and then only having one %s in the format
	sting.  The default order is tag first for languages compatibility.
</remarks>
\**--------------------------------------------------------------------------**/

static stock INI_DoParentTag(const epos, const search[], File:f, callback[E_CALLBACK_DATA], bool:bExtra, extra, bool:bPassTag, tag[], bool:bFilter, filter[])
{
	// The bulk of this function is basically the same as INI_ParseFile (which
	// is a shame as it is a symptom of poor, unmaintainable code).
	fseek(f, 0, seek_start); // Jump back to the start.
	P:4("bool:INI_DoParentTag called: \"%s\", %i, %i, %i, %i, \"%s\"", search, bExtra, extra, bPassTag, bFilter, filter);
	new
		ppos, bool:handle = false,
		p0s, p0e, p1s, p1e, p2s, p2e;
	while ((ppos += fread(f, YSI_g_sCurLine)) < epos)
	{
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID, e_INI_LINE_TYPE_BLANK: {}
			case e_INI_LINE_TYPE_TAG:
			{
				// A new tag.
				// First, check if it is a tag we might care about.
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s] == '@' && YSI_g_sCurLine[p0s + 1] == '@' && (p0e = strfind(YSI_g_sCurLine, "-")) != -1)
				{
					// Check if the current tag is one of the ones we want to
					// filer for.  The "@@" prefix is the "filterable" prefix.
					// If there is no filter then everything will be loaded.
					if (p0e == p0s + 2 || !YSI_g_sCurLine[p0e + 1]) continue;
					YSI_g_sCurLine[p0e] = '\0';
					if (bFilter && strcmp(YSI_g_sCurLine[p0s + 2], filter))
					{
						// Only skip this if filtering is enabled.  We can't put
						// the "bFilter" check higher or the "-" won't be found
						// to resolve the tag name accurately.
						continue;
					}
					p0s = p0e + 1;
				}
				if (!strcmp(YSI_g_sCurLine[p0s], search))
				{
					handle = true;
					if (p1s != p1e)
					{
						new
							parent[32];
						YSI_g_sCurLine[p1e] = '\0',
						strcat(parent, YSI_g_sCurLine[p1s]);
						if (!INI_DoParentTag(ppos, parent, f, callback, bExtra, extra, bPassTag, tag, bFilter, filter)) return false;
						fseek(f, ppos, seek_start);
					}
				}
				else if (handle)
				{
					// Parent tag over.
					return true;
				}
			}
			default: // e_INI_LINE_TYPE_ENTRY and e_INI_LINE_TYPE_CONT.
			{
				if (!handle) continue;
				// Standard key-value pair.
				YSI_g_sCurLine[p0e] = YSI_g_sCurLine[p1e] = '\0';
				if (bExtra)
				{
					if (bPassTag) Callback_Call(callback, extra, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
					else          Callback_Call(callback, extra,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
				}
				else
				{
					if (bPassTag) Callback_Call(callback,        tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
					else          Callback_Call(callback,             YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
				}
			}
		}
	}
	// Return to where we were before.
	return handle;
}

