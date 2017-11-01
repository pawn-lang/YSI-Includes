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

enum e_TEXT_DISPLAY_TYPE
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
#if defined Y_TEXT_UNIQUE
	#define _YT@LO(,%0,%1) UNIQUE_FUNCTION<%0@%1@...@yX_>();public UNIQUE_FUNCTION<%0@%1@...@yX_>(){}
#else
	#define _YT@LO(,%0,%1) %0@%1@yX_();public %0@%1@yX_(){}
#endif
#define _YT@LE%0[%1]%2> _YT@LO(%0,%1) _YT@LE%2>

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

/*#if defined _inc_y_languages
	#define Text_GetLanguageCodes() Langs_GetLanguageCodes()
	
	#define Text_GetPlayerLanguage(%0) Langs_GetPlayerLanguage(%0)
#else
	// y_languages doesn't really do much TBH...  This used to have three
	// langugages, but then I realised that without the "y_languages"
	// library there was no way for a player to select their language.
	// "XX" is used as a dummy to ensure that the array in the enum is always
	// valid and that the compiler doesn't optimise it out.
	#define Text_GetLanguageCodes() "EN|XX|" //|NL|ES|"
	// Number of "|" separated strings above (always 1).
	#define YSI_MAX_LANGUAGES (Language:2)
	
	#define Text_GetPlayerLanguage(%0) (Language:0)
#endif*/

// Return types
enum E_TEXT_FIND
{
	E_TEXT_FIND_NONE,
	E_TEXT_FIND_JUST,
	E_TEXT_FIND_MANY
}

// This holds the data for all entry points.
enum e_TEXT_SETS
{
	e_TEXT_SETS_NAME[28],
	e_TEXT_SETS_HASH,
	e_TEXT_SETS_INDEX,
	e_TEXT_SETS_LOADED
}

enum e_TEXT_ENTRY
{
	e_TEXT_ENTRY_NAME[MAX_INI_ENTRY_NAME],// char],
	e_TEXT_ENTRY_HASH,
	e_TEXT_ENTRY_LEFT,
	e_TEXT_ENTRY_RIGHT,
	e_TEXT_ENTRY_POINTERS[YSI_MAX_LANGUAGES]
}

#define TEXT_MASTER YSI_g_sDistributionID

#if !defined MAX_SINGLE_TEXT_ITEM
	#define MAX_SINGLE_TEXT_ITEM (1024)
#endif

static stock
	YSI_g_sTextSets[Y_TEXT_MAX_SETS][e_TEXT_SETS],
	YSI_g_sTextEntries[MAX_TEXT_ENTRIES][e_TEXT_ENTRY],
	YSI_g_sTextStrings[MAX_TEXT_ENTRIES * _:YSI_MAX_LANGUAGES][MAX_INI_ENTRY_TEXT / 4],// char],
	YSI_g_sReturnText[MAX_SINGLE_TEXT_ITEM],
	YSI_g_sExtraText[MAX_SINGLE_TEXT_ITEM],
	YSI_g_sUnusedEntry = 0,
	YSI_g_sDistributionID = -1,
	YSI_g_sUnusedSlot = 0,
	YSI_g_sCurLoadTextFile[64],
	//YSI_g_sCallbacks,
	YSI_g_sRemaining = sizeof (YSI_g_sTextStrings) * sizeof (YSI_g_sTextStrings[]),
	Language:YSI_g_sLangIndex;

// OnFilterScriptInit

// =============================================================================
// | ========================================================================= |
// | |                                                                       | |
// | |                   HERE STARTS THE LOADING CODE                        | |
// | |                                                                       | |
// | ========================================================================= |
// =============================================================================

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  This callback is hard coded in to YSI to be called absolutely last!  Note
 *  that this WAS hard coded, but now uses a more generic chaining method not
 *  based on y_scriptinit and instead just uses the regular ALS method.
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
		Text_RefreshLoaded();
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
	Text_RefreshLoaded();
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

//forward Text_SpecialInit();
//
//public Text_SpecialInit()
//static stock Text_SpecialInit()
//{
//	P:1("Text_SpecialInit called");
//	// Scan the AMX for all public functions of the type "XX@YY@NN@yX_".  These
//	// are the declarations for included texts.
//	Text_RefreshLoaded();
//	_Styles_SpecialInit();
//	P:2("Text_SpecialInit ended");
//}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_text_ending : n" />
 * <transition keep="true" target="y_text_get_text : n" />
 * <transition keep="true" target="y_render_show : y_render_show_print" />
 *//*------------------------------------------------------------------------**/

//static stock Text_GetDistributionID()
hook OnScriptInit()
{
	P:1("Text_OnScriptInit called");
	// Initialise.
	new
		i;
	for (i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		YSI_g_sTextSets[i][e_TEXT_SETS_NAME][0] = '\1';
		YSI_g_sTextSets[i][e_TEXT_SETS_INDEX] = -1;
	}
	for (i = 0; i != MAX_TEXT_ENTRIES; ++i)
	{
		YSI_g_sTextEntries[i][e_TEXT_ENTRY_HASH] = i + 1;
	}
	// Redirect all the pointers to the last cell.
	new
		offset = (sizeof (YSI_g_sTextStrings) - 1) * 4;
	i = (sizeof (YSI_g_sTextStrings[]) - 1) * 4;
	// Get the absolute address of the pointer to the last array.
	#emit CONST.pri     YSI_g_sTextStrings
	#emit LOAD.S.alt    offset
	#emit ADD
	// Get the data at that address (i.e. the RELATIVE pointer).
	#emit LOAD.I
	// Get the RELATIVE address of the last element.
	#emit LOAD.S.alt    i
	#emit ADD
	#emit STOR.S.pri    offset
	for (i = sizeof (YSI_g_sTextStrings) - 1; i != 0; --i)
	{
		//YSI_g_sTextStrings[i][0] = i + 1;
		#emit CONST.pri     YSI_g_sTextStrings
		#emit LOAD.S.alt    i
		#emit SHL.C.alt     2
		#emit ADD
		#emit MOVE.alt
		#emit LOAD.S.pri    offset
		#emit STOR.I
		#emit ADD.C         4
		#emit STOR.S.pri    offset
	}
	offset = getproperty(8, YSIM_TEXT_D);
	i = 0;
	while (i != 32)
	{
		if (!(offset & (1 << i)))
		{
			YSI_g_sDistributionID = i;
			offset |= 1 << i;
			break;
		}
		++i;
	}
	if (i != 32)
	{
		setproperty(8, YSIM_TEXT_D, offset);
	}
	P:C(else P:E("y_text distribution ID not set"););
	CallRemoteFunction("Text_ResetLoaded", "");
	state y_text_ending : n;
	state y_text_get_text : n;
	state y_render_show : y_render_show_print;
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_text_ending : y" />
 *//*------------------------------------------------------------------------**/

hook OnScriptExit()
{
	P:1("Textint_OnScriptExit called");
	new
		idx = 0,
		buffer[32],
		pos;
	while ((idx = AMX_GetPublicNameSuffix(idx, buffer, _A<@yX_>)))
	{
		pos = chrfind('@', buffer);
		if (pos != -1)
		{
			buffer[pos] = ':';
			pos = chrfind('@', buffer, pos);
			if (pos != -1)
			{
				buffer[pos] = '\0';
				if (existproperty(7, buffer) && getproperty(7, buffer) == TEXT_MASTER)
				{
					deleteproperty(7, buffer);
				}
			}
		}
	}
	state y_text_ending:y;
	CallRemoteFunction("Text_RefreshLoaded", "");
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  When a mode ends this is called so that other scripts can know to re-load
 *  any text which was previously owned by this script that they still need.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Text_ResetLoaded();

public Text_ResetLoaded() <>
{
}

public Text_ResetLoaded() <y_text_ending:n>
{
	// Called to reset the owners of texts after a gamemode restart.
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (YSI_g_sTextSets[i][e_TEXT_SETS_NAME][0] != '\1')
		{
			setproperty(7, YSI_g_sTextSets[i][e_TEXT_SETS_NAME], TEXT_MASTER);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Loops through all text definition functions in the mode (defined as:
 *  "file@section@unique@yX_" (note that "@unique" is optional but irrelevant).
 *  If any are found and the property "file:section" isn't defined claims
 *  ownership of that section so that the text can be loaded in to this mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Text_RefreshLoaded();

public Text_RefreshLoaded() <y_text_ending:y>
{
	//printf("Text_RefreshLoaded: y");
	// Do nothing, only called for other scripts to check that all their text
	// items are still loaded.
}

public Text_RefreshLoaded() <y_text_ending:n>
{
	//printf("Text_RefreshLoaded: n");
	if (Langs_GetLanguageCount() == Language:0)
	{
		P:E("No languages found - Did you add \"Langs_AddLanguage\" to the script init (NOT \"main\")?");
	}
	new
		idx = 0,
		buffer[32],
		pos;
	while ((idx = AMX_GetPublicNameSuffix(idx, buffer, _A<@yX_>)))
	{
		strunpack(buffer, buffer);
		pos = chrfind('@', buffer);
		//printf("%d, %x", pos, buffer[0]);
		if (pos != -1)
		{
			// Get rid of the end parts, doesn't matter if "Y_TEXT_UNIQUE" is
			// defined or not as EVERYTHING later is dropped.
			buffer[pos] = ':';
			pos = chrfind('@', buffer, pos);
			if (pos != -1)
			{
				buffer[pos] = '\0';
				//printf("buffer: %s %d", buffer, existproperty(7, buffer));
				//buffer[pos + 1] = '\0';
				if (!existproperty(7, buffer))
				{
					setproperty(7, buffer, TEXT_MASTER);
					Text_AddLocal(buffer, bernstein(buffer));
				}
			}
		}
	}
	Text_LoadLocals();
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_AddLocal(buffer[], hash)
{
	P:4("Text_AddLocal called: \"%s\", %i", buffer, hash);
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (YSI_g_sTextSets[i][e_TEXT_SETS_NAME][0] == '\1')
		{
			YSI_g_sTextSets[i][e_TEXT_SETS_HASH] = hash;
			strcpy(YSI_g_sTextSets[i][e_TEXT_SETS_NAME], buffer, 28);
			return;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

forward Text_INILoad(offset, tag[], name[], value[]);

public Text_INILoad(offset, tag[], name[], value[])
{
	// Get the path.
	// Get the file.
	// Get the extension.
	P:5("Text_INILoad called: %d, %s, %s, %s", offset, tag, name, value);
	P:5("Text_INILoad: IsPacked? %08x%08x", value[0], value[1]);
	new
		fname[sizeof (YSI_g_sCurLoadTextFile) - (3 + 9)],
		len = strlen(YSI_g_sCurLoadTextFile);
	//format(fname, sizeof (fname
	strcpy(fname, YSI_g_sCurLoadTextFile[9], len - (3 + 9 - 1));
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		//printf("fname: %s, %d, %d, %s", fname, len, offset, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]);
		if (!strcmp(YSI_g_sTextSets[i][e_TEXT_SETS_NAME], fname, true, offset - 1) && !strcmp(YSI_g_sTextSets[i][e_TEXT_SETS_NAME][offset], tag, true))
		{
			//printf("%d \"%s\" \"%s\" \"%s\"", len, fname, YSI_g_sCurLoadTextFile[len - 2], tag);
			len = strlen(name);
			new
				slot = name[--len],
				number,
				hash = 1;
			P:6("Text_INILoad: Get Number");
			while ('0' <= slot <= '9')
			{
				name[len] = '\0';
				number += (slot - '0') * hash;
				hash *= 10;
				slot = name[--len];
			}
			// So "MY_TEXT_1" becomes "MY_TEXT", not "MY_TEXT_".
			if (slot == '_')
			{
				name[len] = '\0';
			}
			hash = bernstein(name);
			slot = Text_FindEntry(YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], hash);
			P:6("Text_INILoad: Check slot %d", slot);
			if (slot == -1)
			{
				Text_AddEntry(i, name, value, hash);
				//P:5("%d,%d,%d,%d,%d", YSI_g_sTextStrings[ss][0], YSI_g_sTextStrings[ss][1], YSI_g_sTextStrings[ss][2], YSI_g_sTextStrings[ss][3], YSI_g_sTextStrings[ss][4]);
			}
			else
			{
				P:6("Text_INILoad: Check Collision");
				if (strcmp(name, YSI_g_sTextEntries[slot][e_TEXT_ENTRY_NAME], true))
				{
					P:E("Text collision on \"%s\" and \"%s\"!", name, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]);
					return;
				}
				else if (YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex] == -1)
				{
					new
						ss = Text_GetFreeSlot();
					if (ss == -1)
					{
						P:E("Text buffer full!");
						return;
					}
					//strpack(YSI_g_sTextStrings[ss], value, MAX_INI_ENTRY_TEXT * 4);
					Text_UpdateFreeSlot(Format_Standardise(value, YSI_g_sTextStrings[ss], MAX_INI_ENTRY_TEXT));
					//P:5("%d,%d,%d,%d,%d", YSI_g_sTextStrings[ss][0], YSI_g_sTextStrings[ss][1], YSI_g_sTextStrings[ss][2], YSI_g_sTextStrings[ss][3], YSI_g_sTextStrings[ss][4]);
					//strcpy(YSI_g_sTextStrings[ss], value, MAX_INI_ENTRY_TEXT * 4);
					YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex] = ss;
				}
				else if (number)
				{
					// Found a string with multiple entries in the INI file to
					// be linked together dynamically.
					new
						ss = Text_GetFreeSlot();
					if (ss == -1)
					{
						P:E("Text buffer full!");
						return;
					}
					Text_UpdateFreeSlot(Format_Standardise(value, YSI_g_sTextStrings[ss], MAX_INI_ENTRY_TEXT));
					hash = YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex];
					if (hash == -1)
					{
						// Will happen when the text entry exists in other
						// languages but not yet in this one.
						YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex] = ss;
					}
					else if (number == 1)
					{
						YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex] = ss;
						len = strlen(YSI_g_sTextStrings[ss]);
						//if (len < sizeof (YSI_g_sTextStrings[]) - 2)
						//{
							// Add the linked list.
						Text_DoLinkedText(YSI_g_sTextStrings[ss], hash, len);
						//}
						//else
						//{
						//	P:W("Text size error on \"%s\"!", name);
						//}
					}
					else
					{
						// Add the string to the chain.
						slot = 2;
						len = strlen(YSI_g_sTextStrings[hash]);
						// Loop through existing strings in this list till we
						// find the right position (either the specified ID or
						// the last item) at which to add the new string.
						while (slot < number)
						{
							if (len < 2)
							{
								break;
							}
							//if (YSI_g_sTextStrings[hash][len - 2] != '\05')
							//{
							//	break;
							//}
							//hash = YSI_g_sTextStrings[hash][len - 1];
							if (!Text_GetLinkedText(YSI_g_sTextStrings[hash], hash, len))
							{
								break;
							}
							len = strlen(YSI_g_sTextStrings[hash]);
							++slot;
						}
						if (len < 2)
						{
							Text_DoLinkedText(YSI_g_sTextStrings[hash], ss, len);
						}
						//else if (YSI_g_sTextStrings[hash][len - 2] == '\05')
						else if (Text_HasLinkedText(YSI_g_sTextStrings[hash], len))
						{
							slot = Text_UpdateLinkedText(YSI_g_sTextStrings[hash], ss, len);
							//slot = YSI_g_sTextStrings[hash][len - 1];
							//YSI_g_sTextStrings[hash][len - 1] = ss;
							len = strlen(YSI_g_sTextStrings[ss]);
							//if (len < sizeof (YSI_g_sTextStrings[]) - 2)
							//{
							//	// Add the linked list.
							//	YSI_g_sTextStrings[ss][len] = '\05';
							//	YSI_g_sTextStrings[ss][len + 1] = slot;
							//	YSI_g_sTextStrings[ss][len + 2] = '\0';
							Text_DoLinkedText(YSI_g_sTextStrings[ss], slot, len);
							//}
							//else
							//{
							//	P:W("Text size error on \"%s\"!", name);
							//}
						}
						else
						{
							//if (len < sizeof (YSI_g_sTextStrings[]) - 2)
							//{
							//	// Add the linked list.
							//	YSI_g_sTextStrings[hash][len] = '\05';
							//	YSI_g_sTextStrings[hash][len + 1] = ss;
							//	YSI_g_sTextStrings[hash][len + 2] = '\0';
							Text_DoLinkedText(YSI_g_sTextStrings[hash], ss, len);
							//}
							//else
							//{
							//	P:W("Text size error on \"%s\"!", name);
							//}
						}
					}
				}
				else
				{
					P:W("Text repeat on \"%s\"!", name);
				}
			}
			// Add the current value to the current tag.
			break;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_LoadLocals()
{
	//printf("Text_LoadLocals called");
	P:4("Text_LoadLocals called");
	// This is the interesting part.  Load all the sets which have a name not
	// '\1' and an index of -1.
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		P:6("Text_LoadLocals: i = %d, text = %s, %d, %d", i, YSI_g_sTextSets[i][e_TEXT_SETS_NAME], YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], YSI_g_sTextSets[i][e_TEXT_SETS_HASH]);
		if (YSI_g_sTextSets[i][e_TEXT_SETS_INDEX] == -1 && YSI_g_sTextSets[i][e_TEXT_SETS_HASH])
		{
			new
				offset = chrfind(':', YSI_g_sTextSets[i][e_TEXT_SETS_NAME]) + 1,
				j = i + 1;
			while (j != Y_TEXT_MAX_SETS)
			{
				if (YSI_g_sTextSets[j][e_TEXT_SETS_INDEX] == -1 && YSI_g_sTextSets[j][e_TEXT_SETS_HASH] && !strcmp(YSI_g_sTextSets[i][e_TEXT_SETS_NAME], YSI_g_sTextSets[j][e_TEXT_SETS_NAME], false, offset))
				{
					break;
				}
				++j;
			}
			// Only load a file one.
			if (j != Y_TEXT_MAX_SETS)
			{
				continue;
			}
			--offset;
			//YSI_g_sTextSets[i][e_TEXT_SETS_NAME][offset] = '\0';
			YSI_g_sLangIndex = Language:0;
			new
				langs[YSI_MAX_STRING],
				pos;
			langs = Langs_GetLanguageCodes();
			while ((pos = chrfind('|', langs, pos)) != -1)
			{
				format(YSI_g_sCurLoadTextFile, sizeof (YSI_g_sCurLoadTextFile), "YSI/text/%.*s.%.2s", offset, YSI_g_sTextSets[i][e_TEXT_SETS_NAME], langs[pos - 2]);
				INI_ParseFile(YSI_g_sCurLoadTextFile, "Text_INILoad", _, true, offset + 1, _, true);
				++YSI_g_sLangIndex;
				++pos;
				// We can add code here to load the data from y_styles.
			}
			//format(YSI_g_sCurLoadTextFile, sizeof (YSI_g_sCurLoadTextFile), "%.*s", offset, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]);
			P:6("Text_LoadLocals: Loading style %s (%d)", YSI_g_sCurLoadTextFile, offset);
			//_Styles_ParseOne(YSI_g_sCurLoadTextFile);
			//YSI_g_sTextSets[i][e_TEXT_SETS_NAME][offset] = ':';
		}
	}
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

forward Text_CheckLoad(buffer[], hash);

public Text_CheckLoad(buffer[], hash) <y_text_ending:y>
{
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		YSI_g_sTextSets[i][e_TEXT_SETS_HASH] = 0;
		YSI_g_sTextSets[i][e_TEXT_SETS_NAME][0] = '\1';
		YSI_g_sTextSets[i][e_TEXT_SETS_NAME][1] = '\0';
	}
}

public Text_CheckLoad(buffer[], hash) <y_text_ending:n>
{
	// Check if another script is already in charge of this set.
	if (getproperty(8, "T_CL"))
	{
		return;
	}
	// Nope, are we?
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (hash == YSI_g_sTextSets[i][e_TEXT_SETS_HASH] && !strcmp(buffer, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]))
		{
			setproperty(8, "T_CL", 1);
			return;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="master">The script which owns this string.</param>
 * <param name="index">The slot in which this string is stored.</param>
 * <param name="str">The string to display.</param>
 * <param name="len0">The length of the string array.</param>
 * <param name="style">The style of the string.</param>
 * <param name="len1">The length of the style array.</param>
 * <param name="label">The 3D label style of the string.</param>
 * <param name="len2">The length of the 3D array.</param>
 * <remarks>
 *  This function is used to pass data from the owner script to the script
 *  which is doing the display.  It passes the string to format (as an array,
 *  not as a string, to keep the non-standard characters).  A copy of the style
 *  data, any 3D text label style data, the index and the master ID.  Note that
 *  TD data isn't handled here - if there is need to use a text draw the script
 *  will have to call to the remote script for display functions.  TD data is
 *  loaded in all scripts where it is relevant.  This does mean that if people
 *  modify a style we need to modify it in ALL scripts.
 *
 *  TODO: Modify the y_text system to store copies of required strings in all
 *  modes, just because it's slightly better.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Text_ReturnTheText(master, index, str[], len0, style[E_STYLE_DATA], len1, label[E_3D_DATA], len2);

public Text_ReturnTheText(master, index, str[], len0, style[E_STYLE_DATA], len1, label[E_3D_DATA], len2) <y_text_get_text:n>
{
}

public Text_ReturnTheText(master, index, str[], len0, style[E_STYLE_DATA], len1, label[E_3D_DATA], len2) <y_text_get_text:y>
{
	P:4("Text_ReturnTheText called: %d,%d,%d,%d,%d len = %d (%s)", str[0], str[1], str[2], str[3], str[4], len0, str);
	strcpy(YSI_g_sReturnText, str, len0);
	setproperty(8, YSIM_TXTLEN, _Format_SetStyleData(master, index, style, label));
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
	P:4("_Text_CheckOwnership called: %s, %s", file, str);
	format(YSI_g_sReturnText, sizeof (YSI_g_sReturnText), "%s:%s", file, str);
	return existproperty(7, YSI_g_sReturnText) && (getproperty(7, YSI_g_sReturnText) == TEXT_MASTER);
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
	P:4("_Text_LookupName called: %s, %s", name, YSI_g_sReturnText);
	//format(YSI_g_sReturnText, sizeof (YSI_g_sReturnText), "%s:%s", YSI_g_sCurLoadTextFile, str);
	new
		sh = bernstein(YSI_g_sReturnText);
	for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
	{
		if (sh == YSI_g_sTextSets[i][e_TEXT_SETS_HASH] && !strcmp(YSI_g_sReturnText, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]))
		{
			// Got the start slot.
			return Text_FindEntry(YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], bernstein(name));
		}
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to be returned.</param>
 * <param name="len0">The length of the string.</param>
 * <remarks>
 *  This function, along with _Text_RemoteSingle, is used to get a single string
 *  from a remote script when the exact ID is known in advance and no other data
 *  like stlyes are required.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward _Text_ReturnSingle(str[], len0);

public _Text_ReturnSingle(str[], len0) <y_text_get_text : n>
{
}

public _Text_ReturnSingle(str[], len0) <y_text_get_text : y>
{
	#pragma unused len0
	strcpy(YSI_g_sExtraText, str);
}

forward _Text_RemoteSingle(master, id);

public _Text_RemoteSingle(master, id)
{
	if (master == TEXT_MASTER)
	{
		CallRemoteFunction("_Text_ReturnSingle", "ai", YSI_g_sTextStrings[id], MAX_SINGLE_TEXT_ITEM); //sizeof (YSI_g_sTextStrings[]));
	}
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_text_get_text : y" />
 * <transition keep="true" target="y_text_get_text : n" />
 *//*------------------------------------------------------------------------**/

stock _Text_GetPointer(master, id)
{
	if (master == TEXT_MASTER)
	{
		//new
		//	ret = id * sizeof (YSI_g_sTextStrings[]);
		//printf("%d", ret);
		#emit CONST.alt   YSI_g_sTextStrings
		#emit LOAD.S.pri  id
		#emit IDXADDR
		#emit MOVE.alt
		#emit LOAD.i
		#emit ADD
		#emit RETN
	}
	state y_text_get_text : y;
	CallRemoteFunction("_Text_RemoteSingle", "ii", master, id);
	state y_text_get_text : n;
	#emit CONST.pri  YSI_g_sExtraText
	#emit RETN
	//#emit STOR.S.pri  ret
	//printf("%d", ret);
	// Never actually called, but shuts up the compiler
	return id;
}

/*-------------------------------------------------------------------------*//**
 * <param name="search">Search blocks to look in.</param>
 * <param name="nh">Hash of the string name to find.</param>
 * <param name="l">Language in which to get the text.</param>
 * <remarks>
 *  Gets a string in a language from a hash and a text set.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Text_GetStandard(search[], nh, Language:l);

public Text_GetStandard(search[], nh, Language:l)
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
		P:7("Text_GetStandard: %d, %d, %d", i, sh, YSI_g_sTextSets[i][e_TEXT_SETS_HASH]);
		if (sh == YSI_g_sTextSets[i][e_TEXT_SETS_HASH] && !strcmp(search, YSI_g_sTextSets[i][e_TEXT_SETS_NAME]))
		{
			// Got the start slot.
			new
				slot = Text_FindEntry(YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], nh);
			P:7("Text_GetStandard: found %d, %d, %d", YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], nh, slot);
			if (slot != -1)
			{
				new
					pointer = YSI_g_sTextEntries[slot][e_TEXT_ENTRY_POINTERS][l];
				P:5("Text_GetStandard: %d, %d, %d, %d", slot, pointer, getproperty(8, YSIM_TXTIND), _@);
				if (pointer != -1)
				{
					//P:5("Text_GetStandard: %08x%08x%08x%08x%08x", YSI_g_sTextStrings[pointer][0], YSI_g_sTextStrings[pointer][1], YSI_g_sTextStrings[pointer][2], YSI_g_sTextStrings[pointer][3], YSI_g_sTextStrings[pointer][4]);
					//setproperty(9, "", YSIM_STRING, YSI_g_sTextStrings[pointer]);
					setproperty(8, YSIM_TXTFND, _@);
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
					CallRemoteFunction("Text_ReturnTheText", "iiaiaiai", TEXT_MASTER, pointer, YSI_g_sTextStrings[pointer], MAX_SINGLE_TEXT_ITEM /*sizeof (YSI_g_sTextStrings[])*/, style, _:E_STYLE_DATA, label, _:E_3D_DATA);
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
		pos,
		lst;
	state y_text_get_text:y;
	setproperty(8, YSIM_TXTFND, -1);
	//setproperty(8, YSIM_TXTIND, index);
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
	return;// ret;
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

// To be public.
//stock Text_GetProvider(search[])
//{
//}

static stock Text_FindEntry(start, hash)
{
	P:4("Text_FindEntry called: %i, %i", start, hash);
	while (start != -1)
	{
		new
			cmp = YSI_g_sTextEntries[start][e_TEXT_ENTRY_HASH] - hash;
		if (cmp < 0)
		{
			start = YSI_g_sTextEntries[start][e_TEXT_ENTRY_RIGHT];
		}
		else if (cmp > 0)
		{
			start = YSI_g_sTextEntries[start][e_TEXT_ENTRY_LEFT];
		}
		else
		{
			return start;
		}
	}
	return -1;
}

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
	Text_UpdateFreeSlot(Format_Standardise(value, YSI_g_sTextStrings[slot], YSI_g_sRemaining));
	//strpack(YSI_g_sTextStrings[slot], value, MAX_INI_ENTRY_TEXT * 4);
	//strcpy(YSI_g_sTextStrings[slot], value, MAX_INI_ENTRY_TEXT * 4);
	// Save the identifier.
	P:5("Text_AddEntry: slot = %d %d,%d,%d,%d,%d", slot, YSI_g_sTextStrings[slot][0], YSI_g_sTextStrings[slot][1], YSI_g_sTextStrings[slot][2], YSI_g_sTextStrings[slot][3], YSI_g_sTextStrings[slot][4]);
	strpack(YSI_g_sTextEntries[entry][e_TEXT_ENTRY_NAME], name, MAX_INI_ENTRY_NAME * 4);
	//strcpy(YSI_g_sTextEntries[entry][e_TEXT_ENTRY_NAME], name, MAX_INI_ENTRY_NAME * 4);
	YSI_g_sTextEntries[entry][e_TEXT_ENTRY_HASH] = hash;
	YSI_g_sTextEntries[entry][e_TEXT_ENTRY_POINTERS][YSI_g_sLangIndex] = slot;
	// Set the default style.
	_Style_Init(entry);
	// Insert the identifier.
	new
		idx = YSI_g_sTextSets[set][e_TEXT_SETS_INDEX],
		next;
	if (idx == -1)
	{
		YSI_g_sTextSets[set][e_TEXT_SETS_INDEX] = entry;
	}
	else
	{
		for ( ; ; )
		{
			new
				cmp = YSI_g_sTextEntries[idx][e_TEXT_ENTRY_HASH] - hash;
			if (cmp < 0)
			{
				next = YSI_g_sTextEntries[idx][e_TEXT_ENTRY_RIGHT];
				if (next == -1)
				{
					YSI_g_sTextEntries[idx][e_TEXT_ENTRY_RIGHT] = entry;
					return;
				}
			}
			else if (cmp > 0)
			{
				next = YSI_g_sTextEntries[idx][e_TEXT_ENTRY_LEFT];
				if (next == -1)
				{
					YSI_g_sTextEntries[idx][e_TEXT_ENTRY_LEFT] = entry;
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
	if (YSI_g_sUnusedSlot == MAX_TEXT_ENTRIES * _:YSI_MAX_LANGUAGES)
	{
		return -1;
	}
	return YSI_g_sUnusedSlot++;
	/*P:4("Text_GetFreeSlot called");
	if (YSI_g_sUnusedSlot == MAX_TEXT_ENTRIES * _:YSI_MAX_LANGUAGES)
	{
		return -1;
	}
	new
		ret = YSI_g_sUnusedSlot;
	YSI_g_sUnusedSlot = YSI_g_sTextStrings[ret][0];
	YSI_g_sTextStrings[ret][0] = '\0';
	return ret;*/
}

/*-------------------------------------------------------------------------*//**
 * <param name="len">Length to make the array slot.</param>
 * <remarks>
 *  Adjusts the first index table in "YSI_g_sTextStrings" such that the next
 *  call to "Text_GetFreeSlot" will point to a non-zero length target string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_UpdateFreeSlot(len)
{
	YSI_g_sRemaining -= len + 3;
	// Get the address of the previous slot's pointer.
	#emit LOAD.pri      YSI_g_sUnusedSlot
	#emit ADD.C         0xFFFFFFFF
	#emit SHL.C.pri     2
	#emit CONST.alt     YSI_g_sTextStrings
	#emit ADD
	// Get the pointer to the start of the data.
	#emit LOAD.I
	// Get the pointer to the end of the data.
	#emit LOAD.S.alt    len
	#emit SHL.C.alt     2
	#emit ADD
	// Add an offset for "\05" (NULL is implicit in the code because we get an
	// extra four bytes of offset from shifting the index up a slot).
	#emit ADD.C         12
	// Temporarily store the data on the stack.
	#emit PUSH.pri
	// Now get the address of the slot of the CURRENT data.
	#emit LOAD.pri      YSI_g_sUnusedSlot
	#emit SHL.C.pri     2
	#emit CONST.alt     YSI_g_sTextStrings
	#emit ADD
	#emit MOVE.alt
	// Retrieve the data and store it in the new index.
	#emit POP.pri
	#emit STOR.I
	#emit RETN
	//printf("%d %d", len, YSI_g_sUnusedSlot - 1);
	// Bypass compiler warnings.
	return len;
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
			next,
			cur;
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
 * <remarks>
 *  Bypass run-time OOB errors when -d0 is disabled.  Set the initial "next"
 *  pointer on the end of the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_DoLinkedText(entry[], add, len)
{
	entry[len] = '\05';
	entry[len + 1] = add;
	entry[len + 2] = '\0';
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Bypass run-time OOB errors when -d0 is disabled.  Get and set the "next"
 *  pointer on the end of the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_UpdateLinkedText(entry[], add, len)
{
	new
		ret = entry[len - 1];
	entry[len - 1] = add;
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Bypass run-time OOB errors when -d0 is disabled.  Get the "next" pointer on
 *  the end of the string.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_GetLinkedText(entry[], &ret, len)
{
	if (entry[len - 2] != '\05')
	{
		return 0;
	}
	ret = entry[len - 1];
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Bypass run-time OOB errors when -d0 is disabled.  Check if there is a "next"
 *  pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_HasLinkedText(entry[], len)
{
	return (entry[len - 2] == '\05');
}

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

static stock Text_GetFreeEntry()
{
	P:4("Text_GetFreeEntry called");
	if (YSI_g_sUnusedEntry == MAX_TEXT_ENTRIES)
	{
		return -1;
	}
	new
		ret = YSI_g_sUnusedEntry;
	YSI_g_sUnusedEntry = YSI_g_sTextEntries[ret][e_TEXT_ENTRY_HASH];
	YSI_g_sTextEntries[ret][e_TEXT_ENTRY_HASH] = 0;
	YSI_g_sTextEntries[ret][e_TEXT_ENTRY_LEFT] = -1;
	YSI_g_sTextEntries[ret][e_TEXT_ENTRY_RIGHT] = -1;
	// Reset text storage pointers.
	for (new Language:i = Language:0; i != YSI_MAX_LANGUAGES; ++i)
	{
		YSI_g_sTextEntries[ret][e_TEXT_ENTRY_POINTERS][i] = -1;
	}
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Checks if the string we are trying to display is owned by the local script,
 *  and if so just use that pointer and text directly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text_IsLocalOwner(search[], ident[], &len)
{
	// First, find out if this script owns it's own text for speed reasons, and
	// if it does, save the handle to the text set.
	switch (search[0])
	{
		case '\1', '\2':
		{
			return -1;
		}
		case '\3':
		{
			// TODO...
		}
		default:
		{
			//Text_GetText(search, ident, lang);
			new
				pos,
				lst,
				hash;
			while (search[lst])
			{
				pos = strfind(search[lst], "|");
				search[lst + pos] = '\0';
				if (existproperty(7, search[lst]) && (getproperty(7, search[lst]) == TEXT_MASTER))
				{
					hash = bernstein(search[lst]);
					for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
					{
						if (hash == YSI_g_sTextSets[i][e_TEXT_SETS_HASH] && !strcmp(search[lst], YSI_g_sTextSets[i][e_TEXT_SETS_NAME]))
						{
							new
								ret = Text_FindEntry(YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], bernstein(ident));
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
				}
				search[lst + pos] = '|';
				lst += pos + 1;
			}
		}
	}
	return -1;
}

static stock
	YSI_g_sLangBuffer[YSI_MAX_LANGUAGES][MAX_SINGLE_TEXT_ITEM];

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

stock _Text_Send(@PlayerSet:players, search[], ident[], GLOBAL_TAG_TYPES:...)
{
	setproperty(8, YSIM_TXTLEN, 1023);
	new
		bool:wasOnce[YSI_MAX_LANGUAGES] = {false, ...},
		n = (numargs() - 3) * 4,
		maxlen,
		owned = Text_IsLocalOwner(search, ident, maxlen);
	// Loop through all the players passed to the function (however they were
	// passed to the function).  This uses "@PlayerArray" instead of
	// "@PlayerVar" so that we can optimised for multiple languages.  Now it
	// uses "@PlayerSet" instead because that's the new one designed for
	// situations like this in which we want direct access to the variable.
	if (n)
	{
		new
			arg_start,
			arg_end;
		// Load the real address of the last static parameter.  Do this by
		// loading the address of the parameter and then adding the value of
		// [FRM] (frame pointer).
		#emit CONST.alt                 ident
		#emit LCTRL                     5
		#emit ADD
		#emit STOR.S.pri                arg_start
		// Load the address of the last variable parameter.  Do this by adding
		// the number of variables on the value just loaded.
		#emit LOAD.S.alt                n
		#emit ADD
		#emit STOR.S.pri                arg_end
		// Push the variable arguments.  This is done by loading the value of
		// each one in reverse order and pushing them.  I'd love to be able to
		// rewrite this to use the values of pri and alt for comparison, instead
		// of having or constantly reload two variables.
		foreach (new playerid : PS(players))
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
			new
				arg_cur = arg_end,
				ret;
			do
			{
				#emit LOAD.S.pri            arg_cur
				#emit LOAD.I
				#emit PUSH.pri
				arg_cur -= 4;
			}
			while (arg_cur > arg_start);
			switch (search[0])
			{
				case '\1':
				{
					// Null - error.
					P:E("Text_Send called with NULL");
				}
				case '\2':
				{
					// None - just print the string directly.
					ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, ident, n / 4);
				}
				case '\3':
				{
					if (owned == -1)
					{
						new
							pos = strfind(ident, ">"),
							br = strfind(ident, "[");
						if (pos > 1 && br != -1)
						{
							ident[pos - 2] = '\0';
							if (br)
							{
								ident[br] = ':';
								Text_GetText(ident, ident[pos + 1], lang);
							}
							else
							{
								Text_GetText(ident[1], ident[pos + 1], lang);
							}
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, YSI_g_sReturnText, n / 4);
						}
						else
						{
							// Var - May contain location search information in
							// "name".  Maybe add an "all" search parameter...
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, "Could not find text source", n / 4);
							// The code generated messes up the pushing.
						}
					}
					else
					{
						ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, "Language text not found", n / 4);
						}
						else
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, YSI_g_sTextStrings[ret], n / 4);
						}
					}
				}
				default:
				{
					if (owned == -1)
					{
						Text_GetText(search, ident, lang);
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, YSI_g_sReturnText, n / 4);
					}
					else
					{
						ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, "Language text not found", n / 4);
						}
						else
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, YSI_g_sTextStrings[ret], n / 4);
						}
					}
				}
			}
			#emit LCTRL                     4
			#emit LOAD.S.alt                n
			#emit ADD
			#emit SCTRL                     4
			wasOnce[lang] = !ret;
		}
	}
	else
	{
		foreach (new playerid : PS(players))
		{
			new
				Language:lang = Langs_GetPlayerLanguage(playerid);
			if (wasOnce[lang])
			{
				// Optimisation for sending messages to multiple players.
				Format_JustShow(playerid, YSI_g_sLangBuffer[lang]);
				continue;
			}
			switch (search[0])
			{
				case '\1':
				{
					// Null - error.
					P:E("Text_Send called with NULL");
				}
				case '\2':
				{
					// None - just print the string directly.
					wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, ident, 0);
				}
				case '\3':
				{
					new
						pos = strfind(ident, ">"),
						br = strfind(ident, "[");
					if (pos > 1 && br != -1)
					{
						ident[pos - 2] = '\0';
						if (br)
						{
							ident[br] = ':';
							Text_GetText(ident, ident[pos + 1], lang);
						}
						else
						{
							Text_GetText(ident[1], ident[pos + 1], lang);
						}
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, YSI_g_sReturnText, 0);
					}
					else
					{
						// Var - May contain location search information in
						// "name".  Maybe add an "all" search parameter...
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, "Could not find text source", 0);
					}
				}
				default:
				{
					if (owned == -1)
					{
						Text_GetText(search, ident, lang);
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, 0, YSI_g_sReturnText, 0);
					}
					else
					{
						new
							ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, "Language text not found", 0);
						}
						else
						{
							wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, 0, YSI_g_sTextStrings[ret], 0);
						}
					}
				}
			}
		}
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
	setproperty(8, YSIM_TXTLEN, 1023);
	new
		bool:wasOnce[YSI_MAX_LANGUAGES] = {false, ...},
		n = (numargs() - 3) * 4,
		maxlen,
		owned = Text_IsLocalOwner(search, ident, maxlen);
	// Loop through all the players passed to the function (however they were
	// passed to the function).  This uses "@PlayerArray" instead of
	// "@PlayerVar" so that we can optimised for multiple languages.  Now it
	// uses "@PlayerSet" instead because that's the new one designed for
	// situations like this in which we want direct access to the variable.
	if (n)
	{
		new
			arg_start,
			arg_end;
		// Load the real address of the last static parameter.  Do this by
		// loading the address of the parameter and then adding the value of
		// [FRM] (frame pointer).
		#emit CONST.alt                 ident
		#emit LCTRL                     5
		#emit ADD
		#emit STOR.S.pri                arg_start
		// Load the address of the last variable parameter.  Do this by adding
		// the number of variables on the value just loaded.
		#emit LOAD.S.alt                n
		#emit ADD
		#emit STOR.S.pri                arg_end
		// Push the variable arguments.  This is done by loading the value of
		// each one in reverse order and pushing them.  I'd love to be able to
		// rewrite this to use the values of pri and alt for comparison, instead
		// of having or constantly reload two variables.
		for (new Language:lang; lang != YSI_MAX_LANGUAGES; ++lang) if (Langs_IsValid(lang))
		{
			new
				arg_cur = arg_end,
				ret;
			do
			{
				#emit LOAD.S.pri            arg_cur
				#emit LOAD.I
				#emit PUSH.pri
				arg_cur -= 4;
			}
			while (arg_cur > arg_start);
			switch (search[0])
			{
				case '\1':
				{
					// Null - error.
					P:E("Text_Send called with NULL");
				}
				case '\2':
				{
					// None - just print the string directly.
					ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, ident, n / 4);
				}
				case '\3':
				{
					if (owned == -1)
					{
						new
							pos = strfind(ident, ">"),
							br = strfind(ident, "[");
						if (pos > 1 && br != -1)
						{
							ident[pos - 2] = '\0';
							if (br)
							{
								ident[br] = ':';
								Text_GetText(ident, ident[pos + 1], lang);
							}
							else
							{
								Text_GetText(ident[1], ident[pos + 1], lang);
							}
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, n / 4);
						}
						else
						{
							// Var - May contain location search information in
							// "name".  Maybe add an "all" search parameter...
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, "Could not find text source", n / 4);
							// The code generated messes up the pushing.
						}
					}
					else
					{
						ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, "Language text not found", n / 4);
						}
						else
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTextStrings[ret], n / 4);
						}
					}
				}
				default:
				{
					if (owned == -1)
					{
						Text_GetText(search, ident, lang);
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, n / 4);
					}
					else
					{
						ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, "Language text not found", n / 4);
						}
						else
						{
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTextStrings[ret], n / 4);
						}
					}
				}
			}
			#emit LCTRL                     4
			#emit LOAD.S.alt                n
			#emit ADD
			#emit SCTRL                     4
			wasOnce[lang] = !ret;
		}
	}
	else
	{
		for (new Language:lang; lang != YSI_MAX_LANGUAGES; ++lang) if (Langs_IsValid(lang))
		{
			switch (search[0])
			{
				case '\1':
				{
					// Null - error.
					P:E("Text_Send called with NULL");
				}
				case '\2':
				{
					// None - just print the string directly.
					wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, ident, 0);
				}
				case '\3':
				{
					new
						pos = strfind(ident, ">"),
						br = strfind(ident, "[");
					if (pos > 1 && br != -1)
					{
						ident[pos - 2] = '\0';
						if (br)
						{
							ident[br] = ':';
							Text_GetText(ident, ident[pos + 1], lang);
						}
						else
						{
							Text_GetText(ident[1], ident[pos + 1], lang);
						}
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
					else
					{
						// Var - May contain location search information in
						// "name".  Maybe add an "all" search parameter...
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, "Could not find text source", 0);
					}
				}
				default:
				{
					if (owned == -1)
					{
						Text_GetText(search, ident, lang);
						wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], getproperty(8, YSIM_TXTLEN) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
					else
					{
						new
							ret = YSI_g_sTextEntries[owned][e_TEXT_ENTRY_POINTERS][lang];
						if (ret == -1)
						{
							wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, "Language text not found", 0);
						}
						else
						{
							wasOnce[lang] = !Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], maxlen, 0, e_FORMAT_FLAGS_NONE, YSI_g_sTextStrings[ret], 0);
						}
					}
				}
			}
		}
	}
	//return Text_GetLastID();
	Format_SetListSeparator(", ");
}

static stock
	YSI_g_sCaptionText[YSI_MAX_LANGUAGES][64],
	YSI_g_sButton1Text[YSI_MAX_LANGUAGES][32],
	YSI_g_sButton2Text[YSI_MAX_LANGUAGES][32];

/*-------------------------------------------------------------------------*//**
 *//*------------------------------------------------------------------------**/

//stock @PlayerArray:players<MAX_PLAYERS>, callback[], csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)
//stock _Text_MessageBox(@PlayerArray:players<MAX_PLAYERS>, callback[], csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)

//stock _Text_MessageBox(@PlayerArray:players<MAX_PLAYERS>, callback[], csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)
stock _Text_DialogBox(@PlayerSet:players, style, callback:callback, csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)
//stock _Text_MessageBox(__ps_addr_t:__ps_addr, callback[], csearch[], cident[], isearch[], iident[], b1search[], b1ident[], b2search[], b2ident[], GLOBAL_TAG_TYPES:...)
{
	// This is what the "@PlayerArray" macro expands to, but I needed more
	// control to allow me to return a value.  The fact that I can't ATM is a
	// serious problem, but not serious enough to warrant fixing.
	new
		bool:wasOnce[YSI_MAX_LANGUAGES] = {false, ...},
		bool:gotExtras[YSI_MAX_LANGUAGES] = {false, ...},
		n = (numargs() - 11) * 4,
		dialog = Dialog_ObtainID();//,
		//maxlen,
		//owned = Text_IsLocalOwner(isearch, iident, maxlen);
	// Loop through all the players passed to the function (however they were
	// passed to the function).  This uses "@PlayerArray" instead of
	// "@PlayerVar" so that we can optimised for multiple languages.
	if (n)
	{
		new
			arg_start,
			arg_end;
		// Load the real address of the last static parameter.  Do this by
		// loading the address of the parameter and then adding the value of
		// [FRM] (frame pointer).
		#emit CONST.alt                 b2ident
		#emit LCTRL                     5
		#emit ADD
		#emit STOR.S.pri                arg_start
		// Load the address of the last variable parameter.  Do this by adding
		// the number of variables on the value just loaded.
		#emit LOAD.S.alt                n
		#emit ADD
		#emit STOR.S.pri                arg_end
		// Push the variable arguments.  This is done by loading the value of
		// each one in reverse order and pushing them.  I'd love to be able to
		// rewrite this to use the values of pri and alt for comparison, instead
		// of having or constantly reload two variables.
		//for (new PlayerArray:players<MAX_PLAYERS>; __PS_A(_:__ps_addr, players); )
		foreach (new playerid : PS(players))
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
					case '\3':
					{
						new pos = strfind(cident, ">"), br = strfind(cident, "[");
						if (pos > 1 && br != -1)
						{
							cident[pos - 2] = '\0';
							if (br) cident[br] = ':', Text_GetText(cident, cident[pos + 1], lang);
							else Text_GetText(cident[1], cident[pos + 1], lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sCaptionText[lang], sizeof (YSI_g_sCaptionText[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
						else YSI_g_sCaptionText[lang] = "Could not find title source";
					}
					default:
					{
						Text_GetText(csearch, cident, lang);
						_Text_SetDialogMode();
						Format_Render(playerid, lang, YSI_g_sCaptionText[lang], sizeof (YSI_g_sCaptionText[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
				}
				// Get the text for button 1 in this language.
				switch (b1search[0])
				{
					case '\1': P:E("Text_Send called with NULL");
					case '\2': strcpy(YSI_g_sButton1Text[lang], b1ident, sizeof (YSI_g_sButton1Text[]));
					case '\3':
					{
						new pos = strfind(b1ident, ">"), br = strfind(b1ident, "[");
						if (pos > 1 && br != -1)
						{
							b1ident[pos - 2] = '\0';
							if (br) b1ident[br] = ':', Text_GetText(b1ident, b1ident[pos + 1], lang);
							else Text_GetText(b1ident[1], b1ident[pos + 1], lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sButton1Text[lang], sizeof (YSI_g_sButton1Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
						else YSI_g_sButton1Text[lang] = "???";
					}
					default:
					{
						Text_GetText(b1search, b1ident, lang);
						_Text_SetDialogMode();
						Format_Render(playerid, lang, YSI_g_sButton1Text[lang], sizeof (YSI_g_sButton1Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
				}
				// Get the text for button 1 in this language.
				if (b2ident[0])
				{
					switch (b2search[0])
					{
						case '\1': P:E("Text_Send called with NULL");
						case '\2': strcpy(YSI_g_sButton2Text[lang], b2ident, sizeof (YSI_g_sButton2Text[]));
						case '\3':
						{
							new pos = strfind(b2ident, ">"), br = strfind(b2ident, "[");
							if (pos > 1 && br != -1)
							{
								b2ident[pos - 2] = '\0';
								if (br) b2ident[br] = ':', Text_GetText(b2ident, b2ident[pos + 1], lang);
								else Text_GetText(b2ident[1], b2ident[pos + 1], lang);
								_Text_SetDialogMode();
								Format_Render(playerid, lang, YSI_g_sButton2Text[lang], sizeof (YSI_g_sButton2Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
							}
							else YSI_g_sButton2Text[lang] = "";
						}
						default:
						{
							Text_GetText(b2search, b2ident, lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sButton2Text[lang], sizeof (YSI_g_sButton2Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
					}
				}
				else YSI_g_sButton2Text[lang] = "";
				gotExtras[lang] = true;
			}
			if (!wasOnce[lang])
			{
				// Optimisation for sending messages to multiple players.
				//Format_DoDisplay(playerid, 0xFF0000AA, YSI_g_sLangBuffer[lang]);
				//continue;
				new
					arg_cur = arg_end,
					ret;
				do
				{
					#emit LOAD.S.pri            arg_cur
					#emit LOAD.I
					#emit PUSH.pri
					arg_cur -= 4;
				}
				while (arg_cur > arg_start);
				switch (isearch[0])
				{
					case '\1':
					{
						// Null - error.
						P:E("Text_Send called with NULL");
					}
					case '\2':
					{
						// None - just print the string directly.
						_Text_SetDialogMode();
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, iident, n / 4);
					}
					case '\3':
					{
						new
							pos = strfind(iident, ">"),
							br = strfind(iident, "[");
						if (pos > 1 && br != -1)
						{
							iident[pos - 2] = '\0';
							if (br)
							{
								iident[br] = ':';
								Text_GetText(iident, iident[pos + 1], lang);
							}
							else
							{
								Text_GetText(iident[1], iident[pos + 1], lang);
							}
							_Text_SetDialogMode();
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, n / 4);
						}
						else
						{
							// Var - May contain location isearch information in
							// "name".  Maybe add an "all" isearch parameter...
							_Text_SetDialogMode();
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, "Could not find text source", n / 4);
							// The code generated messes up the pushing.
						}
					}
					default:
					{
						Text_GetText(isearch, iident, lang);
						_Text_SetDialogMode();
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, n / 4);
					}
				}
				#emit LCTRL                     4
				#emit LOAD.S.alt                n
				#emit ADD
				#emit SCTRL                     4
				wasOnce[lang] = !ret;
			}
			// Display the message.
			Dialog_Show(playerid, style, YSI_g_sCaptionText[lang], YSI_g_sLangBuffer[lang], YSI_g_sButton1Text[lang], YSI_g_sButton2Text[lang], dialog);
		}
	}
	else
	{
		// Push the variable arguments.  This is done by loading the value of
		// each one in reverse order and pushing them.  I'd love to be able to
		// rewrite this to use the values of pri and alt for comparison, instead
		// of having or constantly reload two variables.
		foreach (new playerid : PS(players))
		//for (new PlayerArray:players<MAX_PLAYERS>; __PS_A(_:__ps_addr, players); )
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
					case '\3':
					{
						new pos = strfind(cident, ">"), br = strfind(cident, "[");
						if (pos > 1 && br != -1)
						{
							cident[pos - 2] = '\0';
							if (br) cident[br] = ':', Text_GetText(cident, cident[pos + 1], lang);
							else Text_GetText(cident[1], cident[pos + 1], lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sCaptionText[lang], sizeof (YSI_g_sCaptionText[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
						else YSI_g_sCaptionText[lang] = "Could not find title source";
					}
					default:
					{
						Text_GetText(csearch, cident, lang);
						_Text_SetDialogMode();
						Format_Render(playerid, lang, YSI_g_sCaptionText[lang], sizeof (YSI_g_sCaptionText[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
				}
				// Get the text for button 1 in this language.
				switch (b1search[0])
				{
					case '\1': P:E("Text_Send called with NULL");
					case '\2': strcpy(YSI_g_sButton1Text[lang], b1ident, sizeof (YSI_g_sButton1Text[]));
					case '\3':
					{
						new pos = strfind(b1ident, ">"), br = strfind(b1ident, "[");
						if (pos > 1 && br != -1)
						{
							b1ident[pos - 2] = '\0';
							if (br) b1ident[br] = ':', Text_GetText(b1ident, b1ident[pos + 1], lang);
							else Text_GetText(b1ident[1], b1ident[pos + 1], lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sButton1Text[lang], sizeof (YSI_g_sButton1Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
						else YSI_g_sButton1Text[lang] = "???";
					}
					default:
					{
						Text_GetText(b1search, b1ident, lang);
						_Text_SetDialogMode();
						Format_Render(playerid, lang, YSI_g_sButton1Text[lang], sizeof (YSI_g_sButton1Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
				}
				// Get the text for button 1 in this language.
				if (b2ident[0])
				{
					switch (b2search[0])
					{
						case '\1': P:E("Text_Send called with NULL");
						case '\2': strcpy(YSI_g_sButton2Text[lang], b2ident, sizeof (YSI_g_sButton2Text[]));
						case '\3':
						{
							new pos = strfind(b2ident, ">"), br = strfind(b2ident, "[");
							if (pos > 1 && br != -1)
							{
								b2ident[pos - 2] = '\0';
								if (br) b2ident[br] = ':', Text_GetText(b2ident, b2ident[pos + 1], lang);
								else Text_GetText(b2ident[1], b2ident[pos + 1], lang);
								_Text_SetDialogMode();
								Format_Render(playerid, lang, YSI_g_sButton2Text[lang], sizeof (YSI_g_sButton2Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
							}
							else YSI_g_sButton2Text[lang] = "";
						}
						default:
						{
							Text_GetText(b2search, b2ident, lang);
							_Text_SetDialogMode();
							Format_Render(playerid, lang, YSI_g_sButton2Text[lang], sizeof (YSI_g_sButton2Text[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
					}
				}
				else YSI_g_sButton2Text[lang] = "";
				gotExtras[lang] = true;
			}
			if (!wasOnce[lang])
			{
				new
					ret;
				switch (isearch[0])
				{
					case '\1':
					{
						// Null - error.
						P:E("Text_Send called with NULL");
					}
					case '\2':
					{
						// None - just print the string directly.
						_Text_SetDialogMode();
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, iident, 0);
					}
					case '\3':
					{
						new
							pos = strfind(iident, ">"),
							br = strfind(iident, "[");
						if (pos > 1 && br != -1)
						{
							iident[pos - 2] = '\0';
							if (br)
							{
								iident[br] = ':';
								Text_GetText(iident, iident[pos + 1], lang);
							}
							else
							{
								Text_GetText(iident[1], iident[pos + 1], lang);
							}
							_Text_SetDialogMode();
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
						}
						else
						{
							// Var - May contain location isearch information in
							// "name".  Maybe add an "all" isearch parameter...
							_Text_SetDialogMode();
							ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, "Could not find text source", 0);
							// The code generated messes up the pushing.
						}
					}
					default:
					{
						Text_GetText(isearch, iident, lang);
						_Text_SetDialogMode();
						ret = Format_Render(playerid, lang, YSI_g_sLangBuffer[lang], sizeof (YSI_g_sLangBuffer[]) - 1, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, 0);
					}
				}
				wasOnce[lang] = !ret;
			}
			// Display the message.
			Dialog_Show(playerid, style, YSI_g_sCaptionText[lang], YSI_g_sLangBuffer[lang], YSI_g_sButton1Text[lang], YSI_g_sButton2Text[lang], dialog);
		}
	}
	// Sort out the callbacks etc for the dialog return.
	new
		cd[E_CALLBACK_DATA];
	Callback_Get(callback, cd, _F<iiiis>);
	Dialog_SetCallbackData(dialog, cd); //AMX_GetPublicPointer(callback));
	// Automatically free the dialog when we're done.
	Dialog_Garbage(dialog);
	Format_SetListSeparator(", ");
	return dialog;
}

stock _Text_Format(dest[], size, Language:lang, e_STYLE_TYPE:style, search[], ident[], ...)
{
	P:4("Text_Format: %s %d %d %d %s %s", dest, size, _:lang, style, search, ident);

	Text_GetText(search, ident, lang);
	
	new
		styleData[E_STYLE_DATA],
		label[E_3D_DATA],
		argCount = numargs() - 6,
		bool:foundStyle = false
	;

	if (style != e_STYLE_TYPE_DIALOG)
	{
		new hash = bernstein(ident);
		for (new i = 0; i != Y_TEXT_MAX_SETS; ++i)
		{
			new
				ret = Text_FindEntry(YSI_g_sTextSets[i][e_TEXT_SETS_INDEX], hash)
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

	Format_Render(INVALID_PLAYER_ID, lang, dest, size, 0, e_FORMAT_FLAGS_NONE, YSI_g_sReturnText, argCount, ___(6));

	return 1;
}