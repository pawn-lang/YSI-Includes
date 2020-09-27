#### Text_ResetLoaded
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	When a mode ends this is called so that other scripts can know to re-load
>	any text which was previously owned by this script that they still need.
 
***

#### Text_RefreshLoaded
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Loops through all text definition functions in the mode (defined as:
>	"file@section@unique@yX_" (note that "@unique" is optional but irrelevant).
>	If any are found and the property "file:section" isn't defined claims
>	ownership of that section so that the text can be loaded in to this mode.
 
***

#### Text_ReturnTheText
>* **Parameters:**
>	* `master`: master_INFO
>	* `index`: index_INFO
>	* `str[]`: str[]_INFO
>	* `len0`: len0_INFO
>	* `style[E_STYLE_DATA]`: style[E_STYLE_DATA]_INFO
>	* `len1`: len1_INFO
>	* `label[E_3D_DATA]`: label[E_3D_DATA]_INFO
>	* `len2`: len2_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function is used to pass data from the owner script to the script
>	which is doing the display.  It passes the string to format (as an array,
>	not as a string, to keep the non-standard characters).  A copy of the style
>	data, any 3D text label style data, the index and the master ID.  Note that
>	TD data isn't handled here - if there is need to use a text draw the script
>	will have to call to the remote script for display functions.  TD data is
>	loaded in all scripts where it is relevant.  This does mean that if people
>	modify a style we need to modify it in ALL scripts.
>	TODO: Modify the y_text system to store copies of required strings in all
>	modes, just because it's slightly better.
 
***

#### _Text_CheckOwnership
>* **Parameters:**
>	* `file[]`: file[]_INFO
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* Does this script own the named section in the current file?
>* **Remarks:**
>	Sets "YSI_g_sReturnText" for use in "_Text_LookupName" too.
 
***

#### _Text_LookupName
>* **Parameters:**
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* Slot storing the pointers for the named section.
>* **Remarks:**
>	Assumes this script owns the section based on previously having called
>	"_Text_CheckOwnership".  This is assumed as both functions are called from
>	only y_styles (hence the private naming convention).  Note that the string
>	"YSI_g_sReturnText" is set in "_Text_CheckOwnership" because we make
>	guarantees about the order in which these functions are called.
 
***

#### _Text_ReturnSingle
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `len0`: len0_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function, along with _Text_RemoteSingle, is used to get a single string
>	from a remote script when the exact ID is known in advance and no other data
>	like stlyes are required.
 
***

#### Text_GetStandard
>* **Parameters:**
>	* `search[]`: search[]_INFO
>	* `nh`: nh_INFO
>	* `Language:l`: Language:l_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a string in a language from a hash and a text set.
 
***

#### Text_GetText
>* **Parameters:**
>	* `search[]`: search[]_INFO
>	* `name[]`: name[]_INFO
>	* `Language:l`: Language:l_INFO
>* **Returns:**
>	* The specified string in the specified language.
>* **Remarks:**
>	Uses "YSI_g_sReturnText" instead of a normal return because this may call
>	remote scripts which will need to return a standardised string as an array
>	to preserve all the non-standard characters (passing data as a string using
>	__CallRemoteFunction packs the string, which we don't want).
 
***

#### Text_UpdateFreeSlot
>* **Parameters:**

>* **Returns:**

>* **Remarks:**
>	Adjusts the first index table in "YSI_g_sTextStrings" such that the next
>	call to "Text_GetFreeSlot" will point to a non-zero length target string.
 
***

#### Text_DebugAll
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Prints all the strings loaded by the system, including their data offsets
>	and storage array lengths (cunning tightly packed array).
 
***

#### Text_IsLocalOwner
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if the string we are trying to display is owned by the local script,
>	and if so just use that pointer and text directly.
 
***

#### _Text_Send
>* **Parameters:**
>	* `@PlayerSet:players`: @PlayerSet:players_INFO
>	* `search[]`: search[]_INFO
>	* `ident[]`: ident[]_INFO
>	* `GLOBAL_TAG_TYPES:...`: GLOBAL_TAG_TYPES:..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Main entry point for showing any sort of code to anyone.
>	TODO: Change the code to push the parameters to Format_Render only once and
>	reuse the resulting stack.
 
***

#### _Text_Render
>* **Parameters:**
>	* `search[]`: search[]_INFO
>	* `ident[]`: ident[]_INFO
>	* `GLOBAL_TAG_TYPES:...`: GLOBAL_TAG_TYPES:..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function renders some text to an array, but doesn't display it.
 
***

#### Format_GetKeys
>* **Parameters:**
>	* `const input[]`: const input[]_INFO
>	* `&idx`: &idx_INFO
>* **Returns:**
>	* e_GAME_TEXT_KEYS - Enum representation of keys.
>* **Remarks:**
>	Reads a GameText key identifier and compresses it essentially.
 
***

#### Format_Standardise
>* **Parameters:**
>	* `input[]`: input[]_INFO
>	* `output[]`: output[]_INFO
>	* `len`: len_INFO
>	* `pt - Special mode for parsing player text`: pt - Special mode for parsing player text_INFO
>* **Returns:**
>	* The length of the string.
>* **Remarks:**
>	Takes a string input and converts it to a standardised representation, i.e.
>	uses byte-codes instead of human readable codes to represent formats and
>	colours.  This makes it faster to format in to any other representation,
>	instead of having to convert between all possible combinations, we just have
>	this to convert basically all formats at once (it can handle hybrids of all
>	the different representations) to a single fast read format and then have
>	fairly simple to write methods to convert that single format to any other
>	format (see y_formatout.inc).
 
***

#### Format_GetSpecifier
>* **Parameters:**
>	* `input[]`: input[]_INFO
>	* `&iIn`: &iIn_INFO
>* **Returns:**
>	* Single cell representation of the current specifier.
>* **Remarks:**
>	Reads a series of characters from the input string and interprets them as a
>	format specifier (e.g. "%d").  Also returns the new current string index.
 
***

#### Format_GTToSAMP
>* **Parameters:**
>	* `const str[]`: const str[]_INFO
>	* `&idx`: &idx_INFO
>* **Returns:**
>	* Colour.
>* **Remarks:**
>	Reads a GameText colour format and converts it to single-cell RGB.
 
***

#### Format_DoAddString
>* **Parameters:**
>	* `out[]`: out[]_INFO
>	* `in[]`: in[]_INFO
>	* `&oidx`: &oidx_INFO
>	* `len`: len_INFO
>	* `&orem`: &orem_INFO
>	* `&fakePos`: &fakePos_INFO
>* **Returns:**
>	* The amount of data from "in" not added to "out".
>* **Remarks:**
>	Takes an input string and adds it to an output string.  If the input string
>	is too long to fit in the remainder of the output string, what has been
>	added already (including part of the input string) is displayed and a new
>	string is added.  Format_TryShow handles this, including adding formatting
>	of colour fades, which may involve fake rendering of more of the string to
>	determine how much of the remainder of the string needs processing to get
>	the right colour.  This will also require a method of winding back the state
>	to the point just after the initial input string was added to continue on to
>	show the next string including newly determined fade data.
 
***

#### Format_JustShow
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `out[]`: out[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Text_GetLastID
>* **Parameters:**

>* **Returns:**
>	* The basic ID linking all displayed elements together where appropriate (for
>	* example SendClientMessage has no meaningful ID.  3D texts would, but that's
>	* not implemented.  So do game texts, but that's not implemented either, so
>	* really it's just text draws.
>* **Remarks:**
>	-
 
***

#### TextR_InsertColour
>* **Parameters:**
>	* `str`: str_INFO
>	* `len`: len_INFO
>	* `pos`: pos_INFO
>	* `oldColour`: oldColour_INFO
>	* `newColour`: newColour_INFO
>	* `pending`: pending_INFO
>* **Returns:**

>* **Remarks:**
>	The format "oldColour" is not constant between different state versions
>	of this function, it is determined purely by what display mode is in use.
>	On the other hand, "newColour" is always "RRGGBBAA" with component LSBs used
>	for formatting flags.
 
***

#### TextR_InsertColour
>* **Parameters:**
>	* `str`: str_INFO
>	* `len`: len_INFO
>	* `pos`: pos_INFO
>	* `oldColour`: oldColour_INFO
>	* `newColour`: newColour_INFO
>	* `pending`: pending_INFO
>* **Returns:**

>* **Remarks:**
>	The format "oldColour" is not constant between different state versions
>	of this function, it is determined purely by what display mode is in use.
>	On the other hand, "newColour" is always "RRGGBBAA" with component LSBs used
>	for formatting flags.
 
***

#### TextR_SkipChars
>* **Parameters:**
>	* `str`: str_INFO
>	* `pos`: pos_INFO
>	* `num`: num_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Skips over a given number of VISIBLE colours, ignores colours.
 
***

#### Styles_EntryTag
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Called to load "<entry>" tags from XML style files.
 
***

#### Styles_Reload
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Reloads all the string styles in all scripts.  Use sparingly!
 
***

