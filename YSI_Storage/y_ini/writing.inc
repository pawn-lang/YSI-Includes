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

enum E_INI_KV_ENTRY
{
	E_INI_KV_ENTRY_NAME[MAX_INI_ENTRY_NAME],
	E_INI_KV_ENTRY_TEXT[MAX_INI_ENTRY_TEXT],
	E_INI_KV_ENTRY_NEXT
}

enum E_INI_TAGS
{
	E_INI_TAGS_NAME[MAX_INI_TAG char],
	E_INI_TAGS_START,
	E_INI_TAGS_NEXT
}

_Y_INI_STATIC stock
	YSI_g_sINITmpBuffer[36],
	YSI_g_sINIWriteBuffer[INI_MAX_WRITES * INI_BUFFER_SIZE][E_INI_KV_ENTRY],
	YSI_g_sINIWritePos, // Pointer to the first free K/V slot.
	YSI_g_sINITagPos,   // Pointer to the first free tag slot.
	YSI_g_sINITagBuffer[INI_MAX_WRITES * MAX_INI_TAGS][E_INI_TAGS],
	YSI_g_sINICurrentTag[INI:INI_MAX_WRITES],
	YSI_g_sINIStartTag[INI:INI_MAX_WRITES],
	YSI_g_sINIWriteFile[INI:INI_MAX_WRITES][YSI_MAX_STRING];

forward bool:INI_WriteBuffer(INI:file);
forward bool:INI_Flush();

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

#define INI_IsValid(%0) (0 <= _:(%0) < INI_MAX_WRITES && YSI_g_sINIWriteFile[(%0)][0])

#define INI_WriteComments()        \
		fwrite(buffer, ";"),     \
		fwrite(buffer, sLine[p2s])

#define INI_IsDeleted(%0) ((%0) != -1 && YSI_g_sINITagBuffer[(%0)][E_INI_TAGS_START] == cellmax)

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="filename">INI file to open.</param>
 * <returns>
 *  INI - handle to the file or INI_NO_FILE.
 * </returns>
 * <remarks>
 *  Doesn't actually open the file, just starts a new buffer if possible.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI:INI_Open(const filename[])
{
	if (ftouch(filename) == -1)
	{
		P:W("INI_Open could not find or create file %s", filename);
	}
	P:3("INI:INI_Open called: \"%s\"", filename);
	new
		i;
	while (i != INI_MAX_WRITES && YSI_g_sINIWriteFile[INI:i][0]) ++i;
	if (i == INI_MAX_WRITES) return INI_NO_FILE;
	return
		strcpy(YSI_g_sINIWriteFile[INI:i], filename, YSI_MAX_STRING),
		// Reset tags.
		YSI_g_sINIStartTag[INI:i] = -1,
		YSI_g_sINICurrentTag[INI:i] = -1,
		INI:i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">Handle to the ini to close.</param>
 * <remarks>
 *  Writes any outstanding buffer data to the file and ends the stream.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_Close(INI:file)
{
	P:3("INI_Close called: %i", _:file);
	if (INI_IsValid(file))
	{
		INI_WriteBuffer(file), // Used to check, now just flush by default.
		YSI_g_sINIWriteFile[file][0] = '\0';
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file handle to write to.</param>
 * <param name="tag">Name of the new file subsection for subsequent data to write to.</param>
 * <remarks>
 *  Sets a new [tag] section header.  Subsequent data is written under this
 *  header.  Uses lists for constant tag switching and checks the tag doesn't
 *  already exist.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_SetTag(INI:file, const tag[])
{
	P:3("INI_SetTag called: %i, \"%s\"", _:file, tag);
	if (INI_IsValid(file))
	{
		// Loop through the tags for this file.
		new
			cur = INI_GetTag(file, tag);
		if (cur != -1) return (YSI_g_sINICurrentTag[file] = cur);
		// May need some extra space.
		if (YSI_g_sINITagPos == -1 && !INI_Flush()) return -1;
		// Tag hasn't been written to yet this flush.
		return
			// Get a new tag.
			cur = YSI_g_sINITagPos,
			// Update the "free" list.
			YSI_g_sINITagPos = YSI_g_sINITagBuffer[cur][E_INI_TAGS_NEXT],
			// Add this tag to the current file's list.
			YSI_g_sINITagBuffer[cur][E_INI_TAGS_NEXT] = YSI_g_sINIStartTag[file],
			YSI_g_sINIStartTag[file] = cur,
			// Copy the name over.
			strpack(YSI_g_sINITagBuffer[cur][E_INI_TAGS_NAME], tag, MAX_INI_TAG char),
			// Set start points.
			YSI_g_sINITagBuffer[cur][E_INI_TAGS_START] = -1,
			YSI_g_sINICurrentTag[file] = cur;
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file handle to write to.</param>
 * <param name="tag">Name of the whole section to delete.</param>
 * <remarks>
 *  Removes a [tag] section from a file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_DeleteTag(INI:file, const tag[])
{
	P:3("INI_DeleteTag called: %i, \"%s\"", _:file, tag);
	if (INI_IsValid(file))
	{
		// Save the tag currently being written to.
		new
			curTag = YSI_g_sINICurrentTag[file],
			tag2[MAX_INI_TAG];
		if (curTag != -1) strunpack(tag2, YSI_g_sINITagBuffer[curTag][E_INI_TAGS_NAME]);
		new
			// Get a pointer to the new tag.
			tp = INI_SetTag(file, tag),
			cur = YSI_g_sINITagBuffer[tp][E_INI_TAGS_START];
		// If there is anything in the tag, discard it.  Accounts for "cellmax"
		// specials.
		while (0 <= cur < sizeof (YSI_g_sINIWriteBuffer)) cur = INI_FreeEntry(cur);
		// Now set it to the special "deleted" mark.
		YSI_g_sINITagBuffer[tp][E_INI_TAGS_START] = cellmax;
		// Reset the current tag, using a name not a pointer - we may have
		// flushed the buffer in the meantime and thus invalidated "curTag".
		YSI_g_sINICurrentTag[file] = (curTag == -1) ? -1 : INI_GetTag(file, tag2);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Item to remove.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for removing data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_RemoveEntry(INI:file, name[])
{
	P:3("INI_RemoveEntry called: %i, \"%s\"", _:file, name);
	return INI_AddToBuffer(file, name, NULL);
}

/*

    I8,        8        ,8I          88         88                          
    `8b       d8b       d8'          ""   ,d    ""                          
     "8,     ,8"8,     ,8"                88                                
      Y8     8P Y8     8P 8b,dPPYba, 88 MM88MMM 88 8b,dPPYba,   ,adPPYb,d8  
      `8b   d8' `8b   d8' 88P'   "Y8 88   88    88 88P'   `"8a a8"    `Y88  
       `8a a8'   `8a a8'  88         88   88    88 88       88 8b       88  
        `8a8'     `8a8'   88         88   88,   88 88       88 "8a,   ,d88  
         `8'       `8'    88         88   "Y888 88 88       88  `"YbbdP"Y8  
                                                                aa,    ,88  
                                                                 "Y8bbdP"   

*/

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteString(INI:file, name[], data[])
{
	P:3("INI_WriteString called: %i, \"%s\", \"%s\"", _:file, name, data);
	return INI_AddToBuffer(file, name, data);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Integer data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers.  Fixed for very large numbers
 *  based on code by Slice from "fixes.inc" for "valstr".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteInt(INI:file, name[], data)
{
	P:3("INI_WriteInt called: %i, \"%s\", %i", _:file, name, data);
	static const
		sc_szCellmin[] = !"-2147483648";
	if (data == cellmin)
	{
		return INI_AddToBuffer(file, name, sc_szCellmin);
	}
	else
	{
		return
			format(YSI_g_sINITmpBuffer, sizeof (YSI_g_sINITmpBuffer), "%d", data),
			INI_AddToBuffer(file, name, YSI_g_sINITmpBuffer);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Hex data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers to be written as hex values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteHex(INI:file, name[], data)
{
	P:3("INI_WriteHex called: %i, \"%s\", %i", _:file, name, data);
	return
		format(YSI_g_sINITmpBuffer, sizeof (YSI_g_sINITmpBuffer), "0x%04x%04x", data >>> 16, data & 0xFFFF),
		INI_AddToBuffer(file, name, YSI_g_sINITmpBuffer);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Binary data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers to be written as binary values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteBin(INI:file, name[], data)
{
	P:3("INI_WriteBin called: %i, \"%s\", %i", _:file, name, data);
	if (data < 0) format(YSI_g_sINITmpBuffer, sizeof (YSI_g_sINITmpBuffer), "0b1%031b", data & 0x7FFFFFFF);
	else format(YSI_g_sINITmpBuffer, sizeof (YSI_g_sINITmpBuffer), "0b%b", data);
	return INI_AddToBuffer(file, name, YSI_g_sINITmpBuffer);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Boolean data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for booleans.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteBool(INI:file, name[], bool:data)
{
	P:3("INI_WriteBool called: %i, \"%s\", %i", _:file, name, _:data);
	return INI_AddToBuffer(file, name, data ? ("true") : ("false"));
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Float data.</param>
 * <param name="accuracy">number of decimal places to write.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for floats.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_WriteFloat(INI:file, name[], Float:data, accuracy = 6)
{
	P:3("INI_WriteFloat called: %i, \"%s\", %f, %i", _:file, name, data, accuracy);
	return
		format(YSI_g_sINITmpBuffer, sizeof (YSI_g_sINITmpBuffer), "%.*f", accuracy, data),
		INI_AddToBuffer(file, name, YSI_g_sINITmpBuffer);
}

/*

    88        88                         88                   
    88        88                         88                   
    88        88                         88                   
    88aaaaaaaa88  ,adPPYba,   ,adPPYba,  88   ,d8  ,adPPYba,  
    88""""""""88 a8"     "8a a8"     "8a 88 ,a8"   I8[    ""  
    88        88 8b       d8 8b       d8 8888[      `"Y8ba,   
    88        88 "8a,   ,a8" "8a,   ,a8" 88`"Yba,  aa    ]8I  
    88        88  `"YbbdP"'   `"YbbdP"'  88   `Y8a `"YbbdP"'  

*/

hook OnScriptInit()
{
	// Set up the linked list of free tag and K/V slots.
	for (new i = 0; i != sizeof (YSI_g_sINITagBuffer) - 1; ++i)
	{
		YSI_g_sINITagBuffer[i][E_INI_TAGS_NEXT] = i + 1;
	}
	for (new i = 0; i != sizeof (YSI_g_sINIWriteBuffer) - 1; ++i)
	{
		YSI_g_sINIWriteBuffer[i][E_INI_KV_ENTRY_NEXT] = i + 1;
	}
	// Start and end value.
	YSI_g_sINITagBuffer[sizeof (YSI_g_sINITagBuffer) - 1][E_INI_TAGS_NEXT] = YSI_g_sINIWriteBuffer[sizeof (YSI_g_sINIWriteBuffer) - 1][E_INI_KV_ENTRY_NEXT] = -1,
	YSI_g_sINITagPos = YSI_g_sINIWritePos = 0;
}

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

static stock INI_GetTag(INI:file, const tag[])
{
	new
		cur = YSI_g_sINIStartTag[file];
	while (cur != -1)
	{
		if (!strcmp(tag, YSI_g_sINITagBuffer[cur][E_INI_TAGS_NAME], true))
		{
			return cur;
		}
		cur = YSI_g_sINITagBuffer[cur][E_INI_TAGS_NEXT];
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Slot to remove.</param>
 * <remarks>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_FreeEntry(slot)
{
	new
		ret = YSI_g_sINIWriteBuffer[slot][E_INI_KV_ENTRY_NEXT];
	// Add this entry to the "free" list.
	return
		YSI_g_sINIWriteBuffer[slot][E_INI_KV_ENTRY_NEXT] = YSI_g_sINIWritePos,
		YSI_g_sINIWritePos = slot,
		ret;
}

static stock INI_DumpTag(File:buffer, curTag)
{
	new
		curSlot = YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START];
	while (0 <= curSlot < sizeof (YSI_g_sINIWriteBuffer))
	{
		fwrite(buffer, YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NAME]),
		fwrite(buffer, " = "),
		fwrite(buffer, YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_TEXT]),
		fwrite(buffer, INI_NEW_LINE),
		curSlot = INI_FreeEntry(curSlot);
	}
}

/*stock INI_WriteArray(INI:file, const name[], data[], len)
{
	// Write 6 bits at a time, in 3 cell chunks.  It takes 16 bytes to record
	// three cells with 6 bits per byte.
	P:4("INI_WriteArray called");
	new
		dname[MAX_INI_ENTRY_NAME],
		write[Y_INI_WRITE_ARRAY_SIZE + 1],
		idx,
		wi,
		iter;
	// Write the length first just so the data exists.
	//INI_WriteInt(file, name, len);
	valstr(write, len),
	INI_AddToBuffer(file, name, write),
	write[0] = '\0';
	while (idx + 3 < len)
	{
		// Store all the data fast.
		write[wi++] = ((data[idx] & 0xFC000000) >>> 26) + '>',
		write[wi++] = ((data[idx] & 0x03F00000) >>> 20) + '>',
		write[wi++] = ((data[idx] & 0x000FC000) >>> 14) + '>',
		write[wi++] = ((data[idx] & 0x00003F00) >>> 8) + '>',
		write[wi++] = ((data[idx] & 0x000000FC) >>> 2) + '>',
		write[wi++] = (((data[idx] & 0x00000003) << 4) | ((data[idx + 1] & 0xF0000000) >>> 28)) + '>',
		++idx,
		write[wi++] = ((data[idx] & 0x0FC00000) >>> 22) + '>',
		write[wi++] = ((data[idx] & 0x003F0000) >>> 16) + '>',
		write[wi++] = ((data[idx] & 0x0000FC00) >>> 10) + '>',
		write[wi++] = ((data[idx] & 0x000003F0) >>> 4) + '>',
		write[wi++] = (((data[idx] & 0x0000000F) << 2) | ((data[idx + 1] & 0xC0000000) >>> 30)) + '>',
		++idx,
		write[wi++] = ((data[idx] & 0x3F000000) >>> 24) + '>',
		write[wi++] = ((data[idx] & 0x00FC0000) >>> 18) + '>',
		write[wi++] = ((data[idx] & 0x0003F000) >>> 12) + '>',
		write[wi++] = ((data[idx] & 0x00000FC0) >>> 6) + '>',
		write[wi++] = ((data[idx] & 0x0000003F) >>> 0) + '>',
		++idx;
		if (wi == Y_INI_WRITE_ARRAY_SIZE)
		{
			format(dname, sizeof (dname), "@@%s-%d", name, iter++);
			P:5("Uvar_WriteArray: write %s = %s", dname, write);
			write[wi] = '\0',
			INI_AddToBuffer(file, dname, write),
			write[0] = '\0',
			wi = 0;
		}
	}
	// Do the straggling bytes.
	if (idx != len)
	{
		write[wi++] = ((data[idx] & 0xFC000000) >>> 26) + '>',
		write[wi++] = ((data[idx] & 0x03F00000) >>> 20) + '>',
		write[wi++] = ((data[idx] & 0x000FC000) >>> 14) + '>',
		write[wi++] = ((data[idx] & 0x00003F00) >>> 8) + '>',
		write[wi++] = ((data[idx] & 0x000000FC) >>> 2) + '>';
		if (++idx == len)
		{
			write[wi++] = ((data[idx - 1] & 0x00000003) << 4) + '>';
		}
		else
		{
			write[wi++] = (((data[idx - 1] & 0x00000003) << 4) | ((data[idx] & 0xF0000000) >>> 28)) + '>',
			write[wi++] = ((data[idx] & 0x0FC00000) >>> 22) + '>',
			write[wi++] = ((data[idx] & 0x003F0000) >>> 16) + '>',
			write[wi++] = ((data[idx] & 0x0000FC00) >>> 10) + '>',
			write[wi++] = ((data[idx] & 0x000003F0) >>> 4) + '>';
			if (++idx == len)
			{
				write[wi++] = ((data[idx - 1] & 0x0000000F) << 2) + '>';
			}
			else
			{
				write[wi++] = (((data[idx - 1] & 0x0000000F) << 2) | ((data[idx] & 0xC0000000) >>> 30)) + '>',
				write[wi++] = ((data[idx] & 0x3F000000) >>> 24) + '>',
				write[wi++] = ((data[idx] & 0x00FC0000) >>> 18) + '>',
				write[wi++] = ((data[idx] & 0x0003F000) >>> 12) + '>',
				write[wi++] = ((data[idx] & 0x00000FC0) >>> 6) + '>',
				write[wi++] = ((data[idx] & 0x0000003F) >>> 0) + '>';
			}
		}
		format(dname, sizeof (dname), "@@%s-%d", name, iter++);
		P:5("Uvar_WriteArray: write %s = %s", dname, write);
		write[wi] = '\0',
		INI_AddToBuffer(file, dname, write),
		write[0] = '\0',
		wi = 0;
	}
	return 1;
}*/

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file to write to.</param>
 * <param name="name">Data name to write.</param>
 * <param name="data">Data to write.</param>
 * <returns>
 *  The slot written to, or -1 on failure.
 * </returns>
 * <remarks>
 *  First checks the name doesn't already exist under the current tag header
 *  and if it does overwrites the current value.  If not checks there's room
 *  in the buffer to write to and purges the buffer if not.  Finally saves the
 *  data in the buffer for writing when required and adds the data to the
 *  relevant list for tag inclusion.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_AddToBuffer(INI:file, const key[], const value[])
{
	P:4("INI_AddToBuffer called: %i, \"%s\", \"%s\"", _:file, key, value);
	if (INI_IsValid(file) && key[0])
	{
		// Get the current tag.
		new
			curTag = YSI_g_sINICurrentTag[file];
		if (curTag == -1) curTag = INI_SetTag(file, INI_NO_TAG);
		else
		{
			// Find if this entry already exists.
			new
				curSlot = YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START];
			if (curSlot == cellmax) return -1; // Deleted tag, don't save.
			else while (curSlot != -1)
			{
				if (!strcmp(key, YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NAME], true))
				{
					return
						strcpy(YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_TEXT], value, MAX_INI_ENTRY_TEXT),
						curSlot;
				}
				curSlot = YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NEXT];
			}
		}
		// Get a new slot.
		if (YSI_g_sINIWritePos == -1)
		{
			// Free up some space.
			if (!INI_Flush()) return -1;
			curTag = YSI_g_sINICurrentTag[file];
		}
		// Get a free slot in the system.
		new
			newSlot = YSI_g_sINIWritePos;
		YSI_g_sINIWritePos = YSI_g_sINIWriteBuffer[YSI_g_sINIWritePos][E_INI_KV_ENTRY_NEXT],
		YSI_g_sINIWriteBuffer[newSlot][E_INI_KV_ENTRY_NEXT] = YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START],
		YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START] = newSlot;
		// Now write to it.
		return
			strcpy(YSI_g_sINIWriteBuffer[newSlot][E_INI_KV_ENTRY_NAME], key,   MAX_INI_ENTRY_NAME),
			strcpy(YSI_g_sINIWriteBuffer[newSlot][E_INI_KV_ENTRY_TEXT], value, MAX_INI_ENTRY_TEXT),
			newSlot;
	}
	return -1;
}

static stock INI_FreeTag(INI:file, tag)
{
	new
		prev = -1,
		curSlot = YSI_g_sINIStartTag[file];
	while (curSlot != tag)
	{
		curSlot = YSI_g_sINITagBuffer[(prev = curSlot)][E_INI_TAGS_NEXT];
	}
	if (prev == -1) YSI_g_sINIStartTag[file] = YSI_g_sINITagBuffer[curSlot][E_INI_TAGS_NEXT];
	else YSI_g_sINITagBuffer[prev][E_INI_TAGS_NEXT] = YSI_g_sINITagBuffer[curSlot][E_INI_TAGS_NEXT];
	// Release this tag slot.
	return
		prev = YSI_g_sINITagBuffer[curSlot][E_INI_TAGS_NEXT],
		YSI_g_sINITagBuffer[curSlot][E_INI_TAGS_NEXT] = YSI_g_sINITagPos,
		YSI_g_sINITagPos = curSlot,
		prev;
}

/*

    I8,        8        ,8I          88         88                          
    `8b       d8b       d8'          ""   ,d    ""                          
     "8,     ,8"8,     ,8"                88                                
      Y8     8P Y8     8P 8b,dPPYba, 88 MM88MMM 88 8b,dPPYba,   ,adPPYb,d8  
      `8b   d8' `8b   d8' 88P'   "Y8 88   88    88 88P'   `"8a a8"    `Y88  
       `8a a8'   `8a a8'  88         88   88    88 88       88 8b       88  
        `8a8'     `8a8'   88         88   88,   88 88       88 "8a,   ,d88  
         `8'       `8'    88         88   "Y888 88 88       88  `"YbbdP"Y8  
                                                                aa,    ,88  
                                                                 "Y8bbdP"   

*/

static stock bool:INI_Flush()
{
	for (new INI:i = INI:0; i != INI:INI_MAX_WRITES; ++i)
	{
		if (YSI_g_sINIWriteFile[i][0])
		{
			new
				curTag = YSI_g_sINICurrentTag[i],
				tag2[MAX_INI_TAG] = "\1\0";
			if (curTag != -1) strunpack(tag2, YSI_g_sINITagBuffer[curTag][E_INI_TAGS_NAME]);
			if (!INI_WriteBuffer(i)) return false;
			if (curTag != -1) INI_SetTag(i, tag2);
		}
	}
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI stream to write to file.</param>
 * <returns>
 *  Success/fail.
 * </returns>
 * <remarks>
 *  Opens the required file for reading and a temp file for read/writing.  Goes
 *  through the entire file reading all contained data.  If it reaches a tag
 *  line ([tag_name]) it dumps any unwritten data from the last tag (if there
 *  was one) and starts processing the new tag.  While a tag is being processed
 *  every line is compared against the UNWRITTEN new data for that tag in the
 *  buffer, if they're the same it writes the new data instead (it also writes
 *  any comments which were after the data in the original line back), else it
 *  writes the original line back.
 *
 *  Once all the new data is written to the temp file any tags which haven't
 *  been processed at all (i.e. were not found in the original file) are
 *  written to the temp file along with all their data.  The original file is
 *  then destroyed and reopend and all the data copied out from the temp file
 *  to the newly opened original file, closed and saved.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:INI_WriteBuffer(INI:file)
{
	if (!INI_IsValid(file)) return false;
	static
		sLine[MAX_INI_LINE];
	new
		File:buffer = ftemp();
	if (!buffer) return false;
	new
		File:source = fopen(YSI_g_sINIWriteFile[file], io_read);
	if (!source) return fclose(buffer), false;
	// Start the processing.  Code again copied from "INI_ParseFile".
	new
		p0s, p0e, p1s, p1e, p2s, p2e,
		curTag = INI_GetTag(file, NULL), // Get the empty tag.
		// See if this tag should be saved or not.
		bool:deleted = INI_IsDeleted(curTag);
	while (fread(source, sLine))
	{
		switch (INI_IdentifyLineType(sLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID:
				P:I("Invalid line in INI file \"%s\": %s", YSI_g_sINIWriteFile[file], sLine);
			case e_INI_LINE_TYPE_DATALESS:
				if (!deleted) fwrite(buffer, sLine);
			case e_INI_LINE_TYPE_TAG:
			{
				// Clean up the previous tag.
				if (curTag != -1)
				{
					if (!deleted) INI_DumpTag(buffer, curTag);
					// Get rid of this tag (now empty).
					INI_FreeTag(file, curTag);
				}
				// Then get the new tag to write from.
				new
					ch = sLine[p0e];
				sLine[p0e] = '\0',
				curTag = INI_GetTag(file, sLine[p0s]);
				if (!(deleted = INI_IsDeleted(curTag)))
				{
					sLine[p0e] = ch,
					fwrite(buffer, sLine);
				}
			}
			default: // e_INI_LINE_TYPE_ENTRY and e_INI_LINE_TYPE_CONT.
			{
				if (deleted) continue; // Delete the entry.
				if (curTag == -1) fwrite(buffer, sLine); // No replacement data.
				else
				{
					new
						prev = -1,
						curSlot = YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START];
					p0e -= p0s;
					while (curSlot != -1)
					{
						if (!strcmp(sLine[p0s], YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NAME], true, p0e))
						{
							fwrite(buffer, YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NAME]),
							fwrite(buffer, " = "),
							fwrite(buffer, YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_TEXT]);
							// Write the end bits.

							if (p2s != p2e) INI_WriteComments();
							else fwrite(buffer, INI_NEW_LINE);
							break;
						}
						curSlot = YSI_g_sINIWriteBuffer[(prev = curSlot)][E_INI_KV_ENTRY_NEXT];
					}
					if (curSlot == -1) fwrite(buffer, sLine); // Not replaced.
					else
					{
						// Free this now written slot.
						if (prev == -1)
						{
							if ((YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START] = YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NEXT]) == -1)
							{
								// No items left in the tag.
								INI_FreeTag(file, curTag),
								curTag = -1;
								// Don't reset "deleted" though.
							}
						}
						else YSI_g_sINIWriteBuffer[prev][E_INI_KV_ENTRY_NEXT] = YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NEXT];
						YSI_g_sINIWriteBuffer[curSlot][E_INI_KV_ENTRY_NEXT] = YSI_g_sINIWritePos,
						YSI_g_sINIWritePos = curSlot;
					}
				}
			}
		}
		// Don't put any code down here (at the end of the loop).
	}
	// FIRST write out the rest of the current tag.
	if (curTag != -1)
	{
		if (!deleted) INI_DumpTag(buffer, curTag);
		INI_FreeTag(file, curTag);
	}
	// THEN do the remaining new tags.
	curTag = YSI_g_sINIStartTag[file];
	while (curTag != -1)
	{
		if (YSI_g_sINITagBuffer[curTag][E_INI_TAGS_START] != cellmax)
		{
			new
				tag[32];
			// Write the tag's name.
			strunpack(tag, YSI_g_sINITagBuffer[curTag][E_INI_TAGS_NAME]);
			fwrite(buffer, "["),
			fwrite(buffer, tag),
			fwrite(buffer, "]"  INI_NEW_LINE),
			INI_DumpTag(buffer, curTag);
		}
		curTag = INI_FreeTag(file, curTag);
	}
	// Done writing, copy the results over.
	fclose(source),
	fremove(YSI_g_sINIWriteFile[file]),
	fseek(buffer);
	if (!(source = fopen(YSI_g_sINIWriteFile[file], io_write))) return fclose(buffer), false;
	// Copy the buffer over.
	while (fread(buffer, sLine)) fwrite(source, sLine);
	return
		fclose(buffer),
		fclose(source),
		true;
}

