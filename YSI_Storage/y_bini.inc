/*

y_bin - Binary file storage.

*/

/*

Binary file format:

4 bytes - Number of chunks in the file.

Chunk header:



These are not garbage collected, and memory is allocated for a huge number.
Actually, I'm not sure of the best way to do this well...  The original idea was
to just have fixed blocks, I don't know if that is still the best method.
Actually, maybe the best method is separate files created and destroyed as
required, that would be a LOT less coding!



*/

stock INI_WriteArray(const INI:f, const string:name[], const arr[], const len = sizeof (arr))
{
	// First things first, determine the filename for the data.  This is done as:
	//  
	//  <f path>\<f name>.INI[<tag>]<name>=
	//  
	// Also, unlike all other INI data, this data is not buffered - doing so is
	// not only hard, but pointless because we are writing to a different file.
	new
		fname[64];
	format(fname, sizeof (fname), "%s[%s]%s=.bin", YSI_g_sINIWriteFile[f], YSI_g_sINITagBuffer[YSI_g_sINICurrentTag[f]][E_INI_TAGS_NAME], name);
	new
		File:b = fopen(fname, io_write);
	if (b)
	{
		fblockwrite(b, arr, len);
		INI_WriteString(f, name, fname),
		fclose(b);
	}
}

stock INI_ReadArray(const string:fname[], dest[], len = sizeof (dest))
{
	new
		File:b = fopen(fname, io_read);
	if (b)
	{
		new
			l2 = flength(b);
		if      (l2 > len) P:W("%s buffer has shrunk since writing.", fname);
		else if (l2 < len) P:W("%s buffer has grown since writing.", fname);
		return
			fblockread(b, arr, len);
			fclose(b),
			1;
	}
	else
	{
		// Do something special to detect old style arrays.  Sadly, we can't
		// upgrade them as they may not be writing (actually, why can't we?)
	}
	return 0;
}

#define INI_Array(%1,%2) \
	if (!strcmp((%1), name, true)) return INI_ReadArray(value, %2)

/*

BIN_WriteChunk(const BIN:f, const pos, const arr[], const len = sizeof (arr), buffer = sizeof (arr))
{
	if (buffer < len)
	{
		// Blank the file location, return the new location.  Can NEVER garbage
		// collect the wasted storage.  Actually, why can't we?  Use double
		// indirection!
	}
	else if (buffer > len)
	{
		// Pad the data.
	}
}

*/

/**--------------------------------------------------------------------------**\
<summary>INI_TryGetValue</summary>
<param name="start">Start position of the possibly current key.</param>
<param name="end">End position of the found key.</param>
<returns>
	-
</returns>
<remarks>
	The INI system uses basic string functions to find candidate keys.  They
	always start searching from the known start of the current tag, and check
	that the found key is before the start of the next known tag.  If both those
	conditions are true, this function is called to further verify the found
	text - it could be a substring in a larger key, it could be a value, or it
	could be commented out.  This function therefore checks that the found
	position in the stored string is the first item on a line, and is followed
	only by either nothing or an equals sign.
	
	If this IS the key we are searching for, then we return a later position
	corresponding to the start of the value (or cellmax if there is no value).
	If this isn't a valid key, we return -1.
</remarks>
\**--------------------------------------------------------------------------**/

static stock bool:INI_TryGetValue(start, end)
{
	// Check everything before this position is whitespace only.
	new
		cur = start;
	for ( ; ; )
	{
		switch (YSI_gMallocMemory[--cur])
		{
			case '\0', '\r', '\n': break;
			case ' ', '\t': {}
			default: return -1;
		}
	}
	cur = end;
	for ( ; ; )
	{
		switch (YSI_gMallocMemory[cur++])
		{
			// Has no value, just a key.
			case '\0', '\r', '\n': return cellmax;
			// Has a value, find the start.
			case '=':
			{
				// "cur" has already been incremented by this point.
				for ( ; ; )
				{
					switch (YSI_gMallocMemory[cur])
					{
						case '\0', '\r', '\n': return cellmax;
						case ' ', '\t': ++cur;
						default: return cur;
					}
				}
			}
			case ' ', '\t': {}
			default: break;
		}
	}
	return -1;
}

