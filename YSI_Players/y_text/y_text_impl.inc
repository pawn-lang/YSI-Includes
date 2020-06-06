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

enum e_TEXT_DISPLAY_TYPE:
{
	text_type_print    = cellmin,
	text_type_3d       = -4,
	text_type_player   = -3,
	text_type_alert    = -2,
	text_type_td       = -1,
	text_type_client   = 0,
	text_type_game1,
	text_type_game2,
	text_type_game3,
	text_type_game4,
	text_type_game5,
	text_type_game6
}

//#include "..\y_master"

// End conditions for the recursive calls (strings and publics).
#define _YT@LE@E%0>
#define _YT@LT@E%0> ;

// Recursive wanted text definition.  Needs two levels of indirection to strip
// the excess commas (,%0,%1).
#define _YT@LO(,%0,%1) UNIQUE_FUNCTION<@yX_%0@%1@...>();public UNIQUE_FUNCTION<@yX_%0@%1@...>(){}
#define _YT@LE%0[%1]%2> _YT@LO(%0,%1) _YT@LE%2>
#define @yX_%0\32;%1() @yX_%0%1()

// Recursive local default string definition.
#define _YT@LJ(,%0,%1) #%0":"#%1"|"
#define _YT@LT%0[%1]%2> _YT@LJ(%0,%1)_YT@LT%2>

// Recursive macro with clever ending to load many items from 1 "loadtext" 
// keyword.  NOW RENAMED FROM JUST "text" - WORST NAMING EVER!
#define loadtext%0[%1]%2; _YT@LE,%0[%1]%2@E>static stock DEFAULT_TEXT_SET[]=_YT@LT,%0[%1]%2@E>

#define Text_RegisterTag(%1) \
	loadtext core[%1]

// Clever macros to load default values when not specified.
//#define Text_Send(%0,%1) _Text_Send(%0,DEFAULT_TEXT_SET,#%1)

#define DO_TEXT_SET: _:HAS_TEXT_SET:NO_TEXT_SET:

#define HAS_TEXT_SET:NO_TEXT_SET:%0$%1||| DEFAULT_TEXT_SET,#%1|||

#define NO_TEXT_SET: "\3",

#define DEFAULT_TEXT_SET,#%1->%2||| #core#:#%1#|,#%2|||

// WTF does this do?  I can't even remember what slots are!
//#define core":"#%1:%2"|",%3) %1":"#%2"|",%3)
#define core#:#%1[%2]%9#|,%3) %1#:#%2#|,%3)

// This holds the data for all entry points.
enum E_TEXT_SETS
{
	E_TEXT_SETS_NAME[28],
	E_TEXT_SETS_HASH,
	bool:E_TEXT_SETS_LOAD
}

enum E_TEXT_ENTRY
{
	E_TEXT_ENTRY_NAME[MAX_INI_ENTRY_NAME],
	E_TEXT_ENTRY_HASHMAP[HASH_MAP_DATA],
	E_TEXT_ENTRY_POINTERS[YSI_MAX_LANGUAGES]
}

#define TEXT_MASTER YSI_g_sDistributionID

#if !defined MAX_SINGLE_TEXT_ITEM
	#define MAX_SINGLE_TEXT_ITEM (1024)
#endif

static stock
	HashMap:YSI_g_sTextMap<>,
	YSI_g_sTextLength = 0,
	YSI_g_sTextSets[Y_TEXT_MAX_SETS][E_TEXT_SETS],
	YSI_g_sTextEntries[MAX_TEXT_ENTRIES][E_TEXT_ENTRY],
	YSI_g_sTextStrings[MAX_TEXT_ENTRIES * _:YSI_MAX_LANGUAGES][MAX_INI_ENTRY_TEXT / 2],
	YSI_g_sDistributionID = -1,
	YSI_g_sUnusedSlot = 0,
	YSI_g_sRemaining = sizeof (YSI_g_sTextStrings) * sizeof (YSI_g_sTextStrings[]);

P:D(Text_FindEntry(set, name, hash));
#define Text_FindEntry(%0,%1,%2) HashMap_GetWithHash(YSI_g_sTextMap, (%1), (%0) + (%2))

/*-------------------------------------------------------------------------*//**
 * <param name="len">Length to make the array slot.</param>
 * <remarks>
 *   Adjusts the first index table in "YSI_g_sTextStrings" such that the next
 *   call to "Text_GetFreeSlot" will point to a non-zero length target string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:Text_UpdateSlotSize(slot, len)
{
	return Jagged_Resize(YSI_g_sTextStrings, { slot, len });
}

//                                                                                               
//    88           ,ad8888ba,         db         88888888ba,    88  888b      88    ,ad8888ba,   
//    88          d8"'    `"8b       d88b        88      `"8b   88  8888b     88   d8"'    `"8b  
//    88         d8'        `8b     d8'`8b       88        `8b  88  88 `8b    88  d8'            
//    88         88          88    d8'  `8b      88         88  88  88  `8b   88  88             
//    88         88          88   d8YaaaaY8b     88         88  88  88   `8b  88  88      88888  
//    88         Y8,        ,8P  d8""""""""8b    88         8P  88  88    `8b 88  Y8,        88  
//    88          Y8a.    .a8P  d8'        `8b   88      .a8P   88  88     `8888   Y8a.    .a88  
//    88888888888  `"Y8888Y"'  d8'          `8b  88888888Y"'    88  88      `888    `"Y88888P"   
//                                                                                               

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Called after most other initialisations, so that languages can be selected.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnGameModeInit()
{
	P:1("TextInt_OnGameModeInit called");
	#if defined TextInt_OnGameModeInit
		TextInt_OnGameModeInit();
	#endif
	if (!YSI_FILTERSCRIPT)
	{
		//Text_SpecialInit();
		Text_LoadAll();
		_Styles_SpecialInit();
	}
	P:1("TextInt_OnGameModeInit ended");
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit TextInt_OnGameModeInit
#if defined TextInt_OnGameModeInit
	forward TextInt_OnGameModeInit();
#endif

public OnFilterScriptInit()
{
	P:1("TextInt_OnFilterScriptInit called");
	// DO ALL (MOST) OTHER INITS FIRST.  ENSURE WE COME LATER.
	#if defined TextInt_OnFilterScriptInit
		TextInt_OnFilterScriptInit();
	#endif
	//Text_SpecialInit();
	Text_LoadAll();
	_Styles_SpecialInit();
	P:1("TextInt_OnFilterScriptInit ended");
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit TextInt_OnFilterScriptInit
#if defined TextInt_OnFilterScriptInit
	forward TextInt_OnFilterScriptInit();
#endif

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_text_get_text : n" />
 * <transition keep="true" target="y_render_show : y_render_show_print" />
 *//*------------------------------------------------------------------------**/

HOOK__ OnScriptInit()
{
	new
		fakePtrs[YSI_MAX_LANGUAGES] = { -1, ... };
	P:1("Text_OnScriptInit called");
	HashMap_Init(YSI_g_sTextMap, YSI_g_sTextEntries, E_TEXT_ENTRY_HASHMAP);
	for (new i = 0; i != sizeof (YSI_g_sTextEntries); ++i)
		YSI_g_sTextEntries[i][E_TEXT_ENTRY_POINTERS] = fakePtrs;
	state y_render_show : y_render_show_print;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Loops through all text definition functions in the mode (defined as:
 *  "file@section@unique@yX_" (note that "@unique" is optional but irrelevant).
 *  If any are found and the property "file:section" isn't defined claims
 *  ownership of that section so that the text can be loaded in to this mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_LoadAll()
{
	P:4("Text_LoadAll called");
	//printf("Text_LoadAll: n");
	if (Langs_GetLanguageCount() == Language:0)
	{
		P:E("No languages found - Did you add \"Langs_AddLanguage\" to the script init (NOT \"main\")?");
	}
	new
		idx = 0,
		buffer[32],
		pos = 0;
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, _A<@yX_>)))
	{
		strunpack(buffer, buffer);
		P:6("Text_LoadAll: Adding %s to list", buffer);
		// Get rid of the end parts, doesn't matter if "Y_TEXT_UNIQUE" is
		// defined or not as EVERYTHING later is dropped.  Find the SECOND "@" -
		// there will always be at least one.
		if ((pos = strfind(buffer, "@", false, strfind(buffer, "@", false, 4) + 1)) != -1)
			buffer[pos] = '\0';
		Text_AddLocal(buffer[4]);
	}
	// I am trying very hard NOT to rewrite this code right now.  It might not
	// be as "nice" as I'd like, but it is well tested and works.  Rewriting it
	// would only introduce new bugs.  I do have to update it slightly to use
	// y_hashmap, but that should be a small edit, not a ground-up rewrite.
	Text_LoadLocals();
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_AddLocal(const buffer[])
{
	P:4("Text_AddLocal called: \"%s\", %i", buffer);
	// Check if this already exists.  If not, add it to a found free slot.
	new
		slot = -1;
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (YSI_g_sTextSets[i][E_TEXT_SETS_NAME][0] == '\0')
			slot = i;
		else if (!strcmp(buffer, YSI_g_sTextSets[i][E_TEXT_SETS_NAME]))
			return;
	}
	if (slot != -1)
	{
		YSI_g_sTextSets[slot][E_TEXT_SETS_HASH] = bernstein(buffer);
		YSI_g_sTextSets[slot][E_TEXT_SETS_LOAD] = true;
		strcpy(YSI_g_sTextSets[slot][E_TEXT_SETS_NAME], buffer, 28);
	}
}

static stock bool:Text_InsertString(target[][], const str[], slot, number)
{
	// "target" is passed as a separate string, rather than just used as
	// "YSI_g_sTextStrings[slot]" because that way we do not generate the
	// "BOUNDS" OpCode for the code here, because the compiler can't know the
	// size of any arbitrary passed string.  Plus, it is slightly faster.  We
	// could not do any other slot in this manner because we resize the slot,
	// which moves other slots, but crucially not this one.
	P:4("Text_InsertString called (%s, %d, %d) (%d)", str, slot, number, YSI_g_sUnusedSlot);
	new
		newlen = strlen(str);
	if (number == 0)
	{
		P:5("Text_InsertString: A %d (%d)", newlen, YSI_g_sUnusedSlot);
		// If there is no number, there can be no multiple strings.
		if (!Jagged_UnsafeResizeOne(target, slot, newlen + 1))
			return false;
		P:5("Text_InsertString: A %d (%d)", newlen, YSI_g_sUnusedSlot);
		strcpy(target[slot], str, newlen + 1);
		return true;
	}
	// Prepend "\05;\number;" to the string, for later compression.
	new
		insert[3] = { '\05', 0, 0 },
		oldlen = strlen(target[slot]) + 1,
		largest = 0;
	printf("%d %d %d %d %d", target[slot][0], target[slot][1], target[slot][2], target[slot][3], target[slot][4]);
	// "oldlen" is +1 to cater for "NULL".  If the existing string doesn't
	// begin with `\05`, it was not an extendable string.
	if (oldlen == 1)
		largest = 0;
	else if (target[slot][0] == '\05')
		largest = target[slot][oldlen - 2];
	else
		return false;
	if (largest == number)
	{
		P:5("Text_InsertString: B %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		if (!Jagged_UnsafeResizeOne(target, slot, oldlen + newlen + 2))
			return false;
		P:5("Text_InsertString: B %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		--oldlen,
		insert[1] = number + 1,
		strcat(target[slot][oldlen], str, cellmax),
		strcat(target[slot][oldlen + newlen], insert, cellmax);
	}
	else if (largest < number)
	{
		P:5("Text_InsertString: C %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		if (!Jagged_UnsafeResizeOne(target, slot, oldlen + newlen + 2 + 2 * (number - largest)))
			return false;
		P:5("Text_InsertString: C %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		--oldlen;
		do
		{
			insert[1] = ++largest,
			strcat(target[slot][oldlen], insert, cellmax);
		}
		while (largest < number);
		insert[1] = number + 1,
		strcat(target[slot][oldlen], str, cellmax),
		strcat(target[slot][oldlen + newlen], insert, cellmax);
	}
	else
	{
		P:5("Text_InsertString: D %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		new
			p0 = strfind(target[slot], (insert[1] = number, insert), false, 0),
			p1 = strfind(target[slot], (insert[1] = number + 1, insert), false, p0 + 1);
		// Don't know what to do in this case!
		if (p0 == -1 || p1 == -1)
			return false;
		P:5("Text_InsertString: D %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
		newlen += oldlen;
		oldlen = p1 - p0 - 2;
		if (oldlen)
		{
			P:5("Text_InsertString: E %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
			if (!Jagged_UnsafeResizeOne(target, slot, newlen - oldlen))
				return false;
			P:5("Text_InsertString: E %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
			strdel(target[slot][p0 + 2], 0, oldlen);
			// Delete any existing text in this position.
			strins(target[slot][p0], str, 2, cellmax);
		}
		else
		{
			P:5("Text_InsertString: F %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
			// Nothing to delete, just insert.
			if (!Jagged_UnsafeResizeOne(target, slot, newlen))
				return false;
			P:5("Text_InsertString: F %d %d %d (%d)", newlen, oldlen, largest, YSI_g_sUnusedSlot);
			strins(target[slot][p0], str, 2, cellmax);
		}
	}
	printf("%d %d %d %d %d", target[slot][0], target[slot][1], target[slot][2], target[slot][3], target[slot][4]);
	return true;
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

forward Text_INILoad(Language:langIndex, file[], tag[], name[], value[]);

public Text_INILoad(Language:langIndex, file[], tag[], name[], value[])
{
	// Get the path.
	// Get the file.
	// Get the extension.
	P:5("Text_INILoad called: %s, %s, %s, %s", file, tag, name, value);
	P:5("Text_INILoad: IsPacked? %08x%08x", value[0], value[1]);
	new
		fname[32];
	format(fname, sizeof (fname), "%s:%s", file, tag);
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (!strcmp(YSI_g_sTextSets[i][E_TEXT_SETS_NAME], fname, true))
		{
			YSI_g_sTextSets[i][E_TEXT_SETS_LOAD] = false;
			new
				fhash = YSI_g_sTextSets[i][E_TEXT_SETS_HASH],
				len = strlen(name),
				slot = name[--len],
				number = 0,
				hash = 1;
			P:6("Text_INILoad: Get Number");
			// Find trailing numbers - they are used to concatenate strings, not
			// differentiate.  This should really be a y_ini feature (and then I
			// can add ordering guarantees to simplify the code (unless people
			// manually edit the files)).
			while ('0' <= slot <= '9')
			{
//				name[--len] = '\0';
				number += (slot - '0') * hash;
				hash *= 10;
				slot = name[--len];
			}
			#if !defined Y_TEXT_ACCEPT_BREAKING_CHANGE_1
				if (number)
					P:W("y_text line extensions must now use \"NAME-part\" not \"NAME_part\".\n\tTo acknowledge this change and disable this warning, recompile with:\n\n\t\t#define Y_TEXT_ACCEPT_BREAKING_CHANGE_1\n.");
			#endif
			// So "MY_TEXT-1" becomes "MY_TEXT", not "MY_TEXT-".
			if (slot == '-')
				name[len] = '\0';
			else
				number = 0;
			// `len` is now useless.
			hash = bernstein(name);
			slot = Text_FindEntry(fhash, name, hash);
			P:6("Text_INILoad: Check slot %d", slot);
			if (slot == -1)
			{
				slot = Text_GetFreeEntry();
				if (slot == -1 || !HashMap_AddWithHash(YSI_g_sTextMap, name, fhash + hash, slot))
				{
					P:E("Text buffer full!");
					return;
				}
				// Add this string to the hashmap.  We identify it by name, but
				// the hash is a combination of the string's hash and the search
				// space's hash (through addition).
			}
			P:6("Text_INILoad: Check Collision");
			new
				ss = YSI_g_sTextEntries[slot][E_TEXT_ENTRY_POINTERS][langIndex];
			if (ss == -1)
			{
				ss = Text_GetFreeSlot();
				if (ss == -1)
				{
					P:E("Text buffer full!");
					return;
				}
				YSI_g_sTextEntries[slot][E_TEXT_ENTRY_POINTERS][langIndex] = ss;
			}
			Text_InsertString(YSI_g_sTextStrings, value, ss, number);
			break;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_CompressLoaded(strings[][])
{
	Jagged_PrintHeader(YSI_g_sTextStrings);
	P:4("Text_CompressLoaded called");
	// Remove all the "\05;\number;"s from the strings, now they are all loaded.
	for (new i = 0, pos = 0; i != YSI_g_sUnusedSlot; ++i)
	{
		while ((pos = strfind(strings[i], "\05;")) != -1)
			strdel(strings[i], pos, pos + 2);
		printf("    \"%s\"", strings[i]);
	}
	P:4("Text_CompressLoaded ended");
}

static stock Text_LoadLocals()
{
	P:4("Text_LoadLocals called");
	// This is the interesting part.  Load all the sets which have a name not
	// '\1' and an index of -1.
	new
		loadTextFile[64],
		langs[YSI_MAX_STRING];
	langs = Langs_GetLanguageCodes();
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		P:6("Text_LoadLocals: i = %d, text = %s, %d, %d", i, YSI_g_sTextSets[i][E_TEXT_SETS_NAME], YSI_g_sTextSets[i][E_TEXT_SETS_LOAD], YSI_g_sTextSets[i][E_TEXT_SETS_HASH]);
		if (YSI_g_sTextSets[i][E_TEXT_SETS_LOAD])
		{
			// This is in a file that has apparently not been loaded yet.
			new
				Language:langIndex = Language:0,
				pos = -1,
				offset = strfind(YSI_g_sTextSets[i][E_TEXT_SETS_NAME], "@");
			// Loop through all the language extensions.
			while ((pos = strfind(langs, "|", false, pos + 1)) != -1)
			{
				format(loadTextFile, sizeof (loadTextFile), "YSI/text/%.*s.%.2s", offset, YSI_g_sTextSets[i][E_TEXT_SETS_NAME], langs[pos - 2]);
				P:4("Text_LoadLocals: %s", loadTextFile);
				INI_ParseFile(loadTextFile, "Text_INILoad",
					.bExtra = true,
					.extra = _:langIndex,
					.bPassTag = true,
					.bPassFile = true);
				++langIndex;
				// We can add code here to load the data from y_styles.
			}
			//format(YSI_g_sCurLoadTextFile, sizeof (YSI_g_sCurLoadTextFile), "%.*s", offset, YSI_g_sTextSets[i][E_TEXT_SETS_NAME]);
			P:6("Text_LoadLocals: Loading style %s (%d)", loadTextFile, offset);
			//_Styles_ParseOne(YSI_g_sCurLoadTextFile);
			//YSI_g_sTextSets[i][E_TEXT_SETS_NAME][offset] = ':';
		}
	}
	Text_CompressLoaded(YSI_g_sTextStrings);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to check.</param>
 * <param name="str">Section name to check.</param>
 * <returns>
 *  Does this script own the named section in the current file?
 * </returns>
 * <remarks>
 *  Sets "YSI_g_sReturnText" for use in "_Text_LookupName" too.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Text_CheckOwnership(file[], str[])
{
	// TODO...
//	P:4("_Text_CheckOwnership called: %s, %s", file, str);
//	format(YSI_g_sReturnText, sizeof (YSI_g_sReturnText), "%s:%s", file, str);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the string to look up.</param>
 * <returns>
 *  Slot storing the pointers for the named section.
 * </returns>
 * <remarks>
 *  Assumes this script owns the section based on previously having called
 *  "_Text_CheckOwnership".  This is assumed as both functions are called from
 *  only y_styles (hence the private naming convention).  Note that the string
 *  "YSI_g_sReturnText" is set in "_Text_CheckOwnership" because we make
 *  guarantees about the order in which these functions are called.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Text_LookupName(name[])
{
	// TODO...
//	P:4("_Text_LookupName called: %s, %s", name, YSI_g_sReturnText);
//	new
//		sh = bernstein(YSI_g_sReturnText);
//	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
//	{
//		if (sh == YSI_g_sTextSets[i][E_TEXT_SETS_HASH] && !strcmp(YSI_g_sReturnText, YSI_g_sTextSets[i][E_TEXT_SETS_NAME]))
//		{
//			// Got the start slot.
//			return Text_FindEntry(YSI_g_sTextSets[i][E_TEXT_SETS_HASH], name, bernstein(name));
//		}
//	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_text_get_text : y" />
 * <transition keep="true" target="y_text_get_text : n" />
 *//*------------------------------------------------------------------------**/

stock _Text_GetPointer(master, id)
{
	#pragma unused master
	#emit CONST.alt   YSI_g_sTextStrings
	#emit LOAD.S.pri  id
	#emit IDXADDR
	#emit MOVE.alt
	#emit LOAD.i
	#emit ADD
	#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="search">Search blocks to look in.</param>
 * <param name="nh">Hash of the string name to find.</param>
 * <param name="l">Language in which to get the text.</param>
 * <remarks>
 *  Gets a string in a language from a hash and a text set.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_GetStandard(search[], nh, Language:l)
{
	if (getproperty(8, YSIM_TXTFND) != -1)
	{
		return;
	}
	if (getproperty(7, search) != TEXT_MASTER)
	{
		return;
	}
	P:4("Text_GetStandard called");
	new
		sh = bernstein(search);//,
		//fail[MAX_INI_ENTRY_TEXT] = "String not found";
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		P:7("Text_GetStandard: %d, %d, %d", i, sh, YSI_g_sTextSets[i][E_TEXT_SETS_HASH]);
		if (sh == YSI_g_sTextSets[i][E_TEXT_SETS_HASH] && !strcmp(search, YSI_g_sTextSets[i][E_TEXT_SETS_NAME]))
		{
			// Got the start slot.
			new
				slot = |(YSI_g_sTextSets[i][E_TEXT_SETS_INDEX], nh);
			P:7("Text_GetStandard: found %d, %d, %d", YSI_g_sTextSets[i][E_TEXT_SETS_INDEX], nh, slot);
			if (slot != -1)
			{
				new
					pointer = YSI_g_sTextEntries[slot][E_TEXT_ENTRY_POINTERS][l];
				P:5("Text_GetStandard: %d, %d, %d, %d", slot, pointer, getproperty(8, YSIM_TXTIND), Master_ID());
				if (pointer != -1)
				{
					//P:5("Text_GetStandard: %08x%08x%08x%08x%08x", YSI_g_sTextStrings[pointer][0], YSI_g_sTextStrings[pointer][1], YSI_g_sTextStrings[pointer][2], YSI_g_sTextStrings[pointer][3], YSI_g_sTextStrings[pointer][4]);
					//setproperty(9, "", YSIM_STRING, YSI_g_sTextStrings[pointer]);
					setproperty(8, YSIM_TXTFND, Master_ID());
					// I reckon this is the only time these functions have ever
					// been used together directly...
					P:5("Text_GetStandard: %s", YSI_g_sTextStrings[pointer]);
					//SetPVarString(getproperty(8, YSIM_TXTIND), "YSI_g_sString", YSI_g_sTextStrings[pointer]);
					//printf("%d %d %d %d %d = %d", YSI_g_sTextStrings[pointer][0], YSI_g_sTextStrings[pointer][1], YSI_g_sTextStrings[pointer][2], YSI_g_sTextStrings[pointer][3], YSI_g_sTextStrings[pointer][4], strlen(YSI_g_sTextStrings[pointer]));
					// TODO: Fix this for the new parameter list.
					new
						style[E_STYLE_DATA],
						label[E_3D_DATA];
					Styles_GetData(slot, style, label);
//					CallRemoteFunction("Text_ReturnTheText", "iiaiaiai", TEXT_MASTER, pointer, YSI_g_sTextStrings[pointer], MAX_SINGLE_TEXT_ITEM /*sizeof (YSI_g_sTextStrings[])*/, style, _:E_STYLE_DATA, label, _:E_3D_DATA);
					//format(fail, sizeof (fail), "%s", YSI_g_sTextStrings[pointer]);
					//printf("fail: %s", fail);
					//break;
					return;
				}
			}
			break;
		}
	}
	//static const
	//	fail[MAX_INI_ENTRY_TEXT] = "\1";
	//setproperty(9, "", YSIM_STRING, "\1");
	//return fail;
}

/*-------------------------------------------------------------------------*//**
 * <param name="search">A "|" separated list of files and sections to search in.</param>
 * <param name="name">The text entry to look for.</param>
 * <param name="l">The language to get.</param>
 * <returns>
 *  The specified string in the specified language.
 * </returns>
 * <remarks>
 *  Uses "YSI_g_sReturnText" instead of a normal return because this may call
 *  remote scripts which will need to return a standardised string as an array
 *  to preserve all the non-standard characters (passing data as a string using
 *  __CallRemoteFunction packs the string, which we don't want).
 * </remarks>
 * <transition keep="true" target="y_text_get_text : y" />
 * <transition keep="true" target="y_text_get_text : n" />
 * <transition keep="true" target="y_text_get_text : n" />
 *//*------------------------------------------------------------------------**/

// Get the loaded standardised version of this string.
//forward Text_GetStandard(start[] name[], Language:l);

static stock Text_GetText(search[], name[], Language:l)
{
	/*new
		start = Text_GetProvider(search),
		slot = Text_FindEntry(*/
	// TODO: Parse multiple search strings.
	//search[strlen(search) - 1] = '\0';
	//new loops = 0;
	//static
	//	ret[MAX_INI_ENTRY_TEXT];
	new
		pos = 0,
		lst = 0;
	state y_text_get_text:y;
	while (search[lst])
	{
		pos = strfind(search[lst], "|");
		P:7("Text_GetText: loop1 %s %d %d %s %d", search, lst, pos, search[lst], search[lst + pos + 1]);
		search[lst + pos] = '\0';
		if (existproperty(7, search[lst]))
		{
			// Only call other scripts if ANYONE owns this search.
			CallRemoteFunction("Text_GetStandard", "sii", search[lst], bernstein(name), _:l);
			//P:7("Text_GetText: loop2 %s %d %d %s %d %d", search, lst, pos, search[lst], search[pos + 1], ret[0]);
			search[lst + pos] = '|';
			//if (ret[0] != '\1')
			if (getproperty(8, YSIM_TXTFND) != -1)
			{
				//getproperty(9, "", YSIM_STRING, ret);
				//strunpack(ret, ret)
				//GetPVarString(index, "YSI_g_sString", ret, MAX_INI_ENTRY_TEXT);
				state y_text_get_text:n;
				return;// ret;
			}
		}
		lst += pos + 1;
		//if (++loops == 10) break;
		//break;
	}
	//if (ret[0] == '\1')
	{
		// Need better error reporting here.
		YSI_g_sReturnText = "Text Not Found";
	}
	state y_text_get_text:n;
	return; // ret;
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

// To be public.
//stock Text_GetProvider(search[])
//{
//}

//static stock Text_FindEntry(start, hash)
//{
//	P:4("Text_FindEntry called: %i, %i", start, hash);
//	while (start != -1)
//	{
//		new
//			cmp = YSI_g_sTextEntries[start][E_TEXT_ENTRY_HASH] - hash;
//		if (cmp < 0)
//		{
//			start = YSI_g_sTextEntries[start][E_TEXT_ENTRY_RIGHT];
//		}
//		else if (cmp > 0)
//		{
//			start = YSI_g_sTextEntries[start][E_TEXT_ENTRY_LEFT];
//		}
//		else
//		{
//			return start;
//		}
//	}
//	return -1;
//}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_AddEntry(set, name[], value[], hash)
{
	P:4("Text_AddEntry called: %i, \"%s\", \"%s\", %i", set, name, value, hash);
	new
		entry = Text_GetFreeEntry(),
		slot = Text_GetFreeSlot();
	if (entry == -1 || slot == -1)
	{
		P:E("Text buffer full!");
		return;
	}
	// Save the string.
	//strpack(YSI_g_sTextStrings[slot], value, MAX_INI_ENTRY_TEXT * 4);
	Text_UpdateSlotSize(Format_Standardise(value, YSI_g_sTextStrings[slot], YSI_g_sRemaining));
	//strpack(YSI_g_sTextStrings[slot], value, MAX_INI_ENTRY_TEXT * 4);
	//strcpy(YSI_g_sTextStrings[slot], value, MAX_INI_ENTRY_TEXT * 4);
	// Save the identifier.
	P:5("Text_AddEntry: slot = %d %d,%d,%d,%d,%d", slot, YSI_g_sTextStrings[slot][0], YSI_g_sTextStrings[slot][1], YSI_g_sTextStrings[slot][2], YSI_g_sTextStrings[slot][3], YSI_g_sTextStrings[slot][4]);
	strpack(YSI_g_sTextEntries[entry][E_TEXT_ENTRY_NAME], name, MAX_INI_ENTRY_NAME * 4);
	//strcpy(YSI_g_sTextEntries[entry][E_TEXT_ENTRY_NAME], name, MAX_INI_ENTRY_NAME * 4);
	YSI_g_sTextEntries[entry][E_TEXT_ENTRY_HASH] = hash;
	YSI_g_sTextEntries[entry][E_TEXT_ENTRY_POINTERS][langIndex] = slot;
	// Set the default style.
	_Style_Init(entry);
	// Insert the identifier.
	new
		idx = YSI_g_sTextSets[set][E_TEXT_SETS_INDEX],
		next = 0;
	if (idx == -1)
	{
		YSI_g_sTextSets[set][E_TEXT_SETS_INDEX] = entry;
	}
	else
	{
		for ( ; ; )
		{
			new
				cmp = YSI_g_sTextEntries[idx][E_TEXT_ENTRY_HASH] - hash;
			if (cmp < 0)
			{
				next = YSI_g_sTextEntries[idx][E_TEXT_ENTRY_RIGHT];
				if (next == -1)
				{
					YSI_g_sTextEntries[idx][E_TEXT_ENTRY_RIGHT] = entry;
					return;
				}
			}
			else if (cmp > 0)
			{
				next = YSI_g_sTextEntries[idx][E_TEXT_ENTRY_LEFT];
				if (next == -1)
				{
					YSI_g_sTextEntries[idx][E_TEXT_ENTRY_LEFT] = entry;
					return;
				}
			}
			idx = next;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_GetFreeSlot()
{
	if (YSI_g_sUnusedSlot == sizeof (YSI_g_sTextStrings))
		return -1;
	return YSI_g_sUnusedSlot++;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Prints all the strings loaded by the system, including their data offsets
 *  and storage array lengths (cunning tightly packed array).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Text_DebugAllText()
{
	for (new i = 0; i != YSI_g_sUnusedSlot; ++i)
	{
		new
			next = 0,
			cur = 0;
		printf("%d %d %d %d", i, cur, next, YSI_g_sUnusedSlot);
		Text_GetCurNextOffset(i, cur, next);
		printf("Offset: %d, Length: %d", cur, (next - cur) / 4);
		printf("Text: %s", YSI_g_sTextStrings[i]);
	}
}

static stock Text_GetCurNextOffset(i, &cur, &next)
{
	// Get the address of the previous slot's pointer.
	#emit LOAD.S.pri    i
	#emit SHL.C.pri     2
	#emit CONST.alt     YSI_g_sTextStrings
	#emit ADD
	// Get the pointer to the start of the data.
	#emit LOAD.I
	#emit SREF.S.pri    cur
	// Get the address of the previous slot's pointer.
	#emit LOAD.S.pri    i
	#emit ADD.C         0x1
	#emit SHL.C.pri     2
	#emit CONST.alt     YSI_g_sTextStrings
	#emit ADD
	// Get the pointer to the start of the data.
	#emit LOAD.I
	#emit SREF.S.pri    next
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_GetFreeEntry()
{
	P:4("Text_GetFreeEntry called");
	new
		ret = HashMap_GetUnused(YSI_g_sTextMap);
	if (ret == -1)
		return -1;
	// Reset text storage pointers.
	for (new Language:i = Language:0; i != YSI_MAX_LANGUAGES; ++i)
	{
		YSI_g_sTextEntries[ret][E_TEXT_ENTRY_POINTERS][i] = -1;
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Checks if the string we are trying to display is owned by the local script,
 *  and if so just use that pointer and text directly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_IsLocalOwner(search[], const ident[], &len)
{
	// First, find out if this script owns it's own text for speed reasons, and
	// if it does, save the handle to the text set.
	new
		pos = 0,
		lst = 0,
		hash = 0;
	while (search[lst])
	{
		pos = strfind(search[lst], "|");
		search[lst + pos] = '\0';
		hash = bernstein(search[lst]);
		for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
		{
			if (hash == YSI_g_sTextSets[i][E_TEXT_SETS_HASH] && !strcmp(search[lst], YSI_g_sTextSets[i][E_TEXT_SETS_NAME]))
			{
				new
					ret = Text_FindEntry(YSI_g_sTextSets[i][E_TEXT_SETS_HASH], ident, bernstein(ident));
				if (ret != -1)
				{
					search[lst + pos] = '|';
					new
						style[E_STYLE_DATA],
						label[E_3D_DATA];
					Styles_GetData(ret, style, label);
					len = _Format_SetStyleData(TEXT_MASTER, -1, style, label) - 1;
					return ret;
				}
			}
		}
		search[lst + pos] = '|';
		lst += pos + 1;
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="players">A representation of players to show to.</param>
 * <param name="search">Text sets to look in for this string.</param>
 * <param name="ident">The name of the string to look for (or the string itself).</param>
 * <param name="">All the parameters to pass to the string.</param>
 * <remarks>
 *  Main entry point for showing any sort of code to anyone.
 *
 *  TODO: Change the code to push the parameters to Format_Render only once and
 *  reuse the resulting stack.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock
	YSI_g_sLangBuffer[YSI_MAX_LANGUAGES][MAX_SINGLE_TEXT_ITEM];

stock _Text_Send(@PlayerSet:players, search[], ident[], GLOBAL_TAG_TYPES:...)
{
	YSI_g_sTextLength = MAX_SINGLE_TEXT_ITEM - 1;
	new
		bool:wasOnce[YSI_MAX_LANGUAGES] = {false, ...},
		maxlen = 0,
		source = 0,
		ret = 0;
	switch (search[0])
	{
		case '\1':
		{
			// Null - error.
			P:E("Text_Send called with NULL");
			return -1;
		}
		case '\2':
			source = cellmin;
		default:
			source = Text_IsLocalOwner(search, ident, maxlen);
	}
	// Loop through all the players passed to the function (however they were
	// passed to the function).  This uses "@PlayerArray" instead of
	// "@PlayerVar" so that we can optimised for multiple languages.  Now it
	// uses "@PlayerSet" instead because that's the new one designed for
	// situations like this in which we want direct access to the variable.
	FOREACH__ (new playerid : PS(players))
	//new playerid = 0;
	{
		new
			Language:lang = Langs_GetPlayerLanguage(playerid);
		if (lang == NO_LANGUAGE)
		{
			lang = Language:0;
		}
		if (wasOnce[lang])
		{
			// Optimisation for sending messages to multiple players.
			Format_JustShow(playerid, YSI_g_sLangBuffer[lang]);
			continue;
		}
		switch (source)
		{
			case cellmin:
			{
				ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], YSI_g_sTextLength, 0, 0, ident, ___(3));
			}
			default:
			{
				ret = YSI_g_sTextEntries[source][E_TEXT_ENTRY_POINTERS][lang];
				if (ret == -1)
				{
					ret = 0;
					YSI_g_sLangBuffer[lang] = "Language text not found";
				}
				else
				{
					ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, YSI_g_sTextStrings[ret], ___(3));
				}
			}
		}
		wasOnce[lang] = !ret;
	}
	Format_SetListSeparator(", ");
	return Text_GetLastID();
}

/*-------------------------------------------------------------------------*//**
 * <param name="search">Text sets to look in for this string.</param>
 * <param name="ident">The name of the string to look for (or the string itself).</param>
 * <param name="">All the parameters to pass to the string.</param>
 * <remarks>
 *  This function renders some text to an array, but doesn't display it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Text_GetPreRender(Language:lang)
{
	return YSI_g_sLangBuffer[lang];
}

stock _Text_Render(playerid, search[], ident[], GLOBAL_TAG_TYPES:...)
{
	YSI_g_sTextLength = MAX_SINGLE_TEXT_ITEM - 1;
	new
		maxlen = 0,
		source = 0,
		ret = 0;
	switch (search[0])
	{
		case '\1':
		{
			// Null - error.
			P:E("Text_Send called with NULL");
			return;
		}
		case '\2':
			source = cellmin;
		default:
			source = Text_IsLocalOwner(search, ident, maxlen);
	}
	for (new Language:lang; lang != YSI_MAX_LANGUAGES; ++lang) if (Langs_IsValid(lang))
	{
		switch (source)
		{
			case cellmin:
			{
				ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], YSI_g_sTextLength, 0, e_FORMAT_FLAGS_NONE, ident, ___(3));
			}
			default:
			{
				ret = YSI_g_sTextEntries[source][E_TEXT_ENTRY_POINTERS][lang];
				if (ret == -1)
				{
					ret = 0;
					YSI_g_sLangBuffer[lang] = "Language text not found";
				}
				else
				{
					ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTextStrings[ret], ___(3));
				}
			}
		}
	}
	Format_SetListSeparator(", ");
}

static stock
	YSI_g_sCaptionText[YSI_MAX_LANGUAGES][64],
	YSI_g_sButton1Text[YSI_MAX_LANGUAGES][32],
	YSI_g_sButton2Text[YSI_MAX_LANGUAGES][32];

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

stock _Text_DialogBox(@PlayerSet:players, style, Func:callback<iiiis>, csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)
{
	// This is what the "@PlayerArray" macro expands to, but I needed more
	// control to allow me to return a value.  The fact that I can't ATM is a
	// serious problem, but not serious enough to warrant fixing.
	new
		bool:wasOnce[YSI_MAX_LANGUAGES] = {false, ...},
		bool:gotExtras[YSI_MAX_LANGUAGES] = {false, ...},
		maxlen = 0,
		source = 0,
		ret = 0;
	if (isearch[0] == '\1' || csearch[0] == '\1' || b1search[0] == '\1' || (b2ident[0] && b2search[0] == '\1')
	{
		// Null - error.
		P:E("Text_Send called with NULL");
		return;
	}
	if (isearch[0] == '\2')
		source = cellmin;
	else
		source = Text_IsLocalOwner(isearch, iident, maxlen);
	YSI_g_sTextLength = MAX_SINGLE_TEXT_ITEM - 1;
	// Loop through all the players passed to the function (however they were
	// passed to the function).  This uses "@PlayerArray" instead of
	// "@PlayerVar" so that we can optimised for multiple languages.
	FOREACH__ (new playerid : PS(players))
	{
		new
			Language:lang = Langs_GetPlayerLanguage(playerid);
		if (lang == NO_LANGUAGE)
		{
			lang = Language:0;
		}
		// Only ever do this part once per language.
		if (!gotExtras[lang])
		{
			// Get the text for the caption in this language.
			switch (csearch[0])
			{
				case '\1': P:E("Text_Send called with NULL");
				case '\2': strcpy(YSI_g_sCaptionText[lang], cident, sizeof (YSI_g_sCaptionText[]));
				default:
				{
					Text_GetText(csearch, cident, lang);
					strcpy(YSI_g_sCaptionText[lang], YSI_g_sReturnText, sizeof (YSI_g_sCaptionText[]));
				}
			}
			// Get the text for button 1 in this language.
			switch (b1search[0])
			{
				case '\1': P:E("Text_Send called with NULL");
				case '\2': strcpy(YSI_g_sButton1Text[lang], b1ident, sizeof (YSI_g_sButton1Text[]));
				default:
				{
					Text_GetText(b1search, b1ident, lang);
					strcpy(YSI_g_sButton1Text[lang], YSI_g_sReturnText, sizeof (YSI_g_sButton1Text[]));
				}
			}
			// Get the text for button 1 in this language.
			if (b2ident[0])
			{
				switch (b2search[0])
				{
					case '\1': P:E("Text_Send called with NULL");
					case '\2': strcpy(YSI_g_sButton2Text[lang], b2ident, sizeof (YSI_g_sButton2Text[]));
					default:
					{
						Text_GetText(b2search, b2ident, lang);
						strcpy(YSI_g_sButton2Text[lang], YSI_g_sReturnText, sizeof (YSI_g_sButton2Text[]));
					}
				}
			}
			else
				YSI_g_sButton2Text[lang][0] = '\0';
			gotExtras[lang] = true;
		}
		if (!wasOnce[lang])
		{
			switch (source)
			{
				case cellmin:
				{
					_Text_SetDialogMode();
					ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], YSI_g_sTextLength, 0, e_FORMAT_FLAGS_NONE, iident, ___(11));
				}
				default:
				{
					ret = YSI_g_sTextEntries[source][E_TEXT_ENTRY_POINTERS][lang];
					if (ret == -1)
					{
						ret = 0;
						YSI_g_sLangBuffer[lang] = "Language text not found";
					}
					else
					{
						_Text_SetDialogMode();
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTextStrings[ret], ___(11));
					}
				}
			}
			wasOnce[lang] = !ret;
		}
		// Display the message.
		Dialog_ShowCallback(playerid, callback, style, YSI_g_sCaptionText[lang], YSI_g_sLangBuffer[lang], YSI_g_sButton1Text[lang], YSI_g_sButton2Text[lang]);
	}
	Format_SetListSeparator(", ");
}

stock _Text_Format(dest[], size, Language:lang, e_STYLE_TYPE:style, search[], ident[], ...)
{
	P:4("Text_Format: %s %d %d %d %s %s", dest, size, _:lang, style, search, ident);

	Text_GetText(search, ident, lang);
	
	new
		styleData[E_STYLE_DATA],
		label[E_3D_DATA],
		bool:foundStyle = false
	;

	if (style != e_STYLE_TYPE_DIALOG)
	{
		new hash = bernstein(ident);
		for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
		{
			new
				ret = Text_FindEntry(YSI_g_sTextSets[i][E_TEXT_SETS_HASH], ident, hash)
			;
			P:7("Text_Format: Textset %d entry %d", i, ret);
			if (ret != -1)
			{
				Styles_GetData(ret, styleData, label);
				if ((styleData[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK) != style)
				{
					P:7("Text_Format: No matching style data. Types differ 0x%08x == 0x%08x", (styleData[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK), style);
					break;
				}

				foundStyle = true;
				break;
			}
		}

		if (!foundStyle)
		{
			P:7("Text_Format: Style not found, using default");
		}

		_Format_SetStyleData(TEXT_MASTER, 0, styleData, label);
	}
	else
	{
		P:7("Text_Format: Toggling dialog mode");
		_Text_SetDialogMode();
	}

	Format_Render(INVALID_PLAYER_ID, lang, dest, size, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, ___(6));

	return 1;
}

