#### INI_IsEscapeSequence
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `pos`: pos_INFO
>* **Returns:**
>	* Is the current character escaped?
>* **Remarks:**
>	-
 
***

#### INI_ReverseWhitespace
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `pos`: pos_INFO
>* **Returns:**
>	* Start of the whitespace.
>* **Remarks:**
>	-
 
***

#### INI_FindString
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `sub[]`: sub[]_INFO
>	* `pos`: pos_INFO
>* **Returns:**
>	* Position when found, "cellmax - 1" on fail.
>* **Remarks:**
>	Uses "cellmax" not "-1" as a failure return as it is easier to utilise in
>	later code (it is only used as an upper-bound on line positions).  This is
>	similar to "strfind", but accounts for escape sequences.
 
***

#### INI_GetEntryText
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `p0s`: p0s_INFO
>	* `p0e`: p0e_INFO
>	* `p1s`: p1s_INFO
>	* `p1e`: p1e_INFO
>	* `p2s`: p2s_INFO
>	* `p2e`: p2e_INFO
>	* `cont`: cont_INFO
>* **Returns:**
>	* e_INI_LINE_TYPE
>* **Remarks:**
>	This function's signature is so long that I put it on a separate line.  This
>	takes a line and determines what it is and where the parts are.
 
***

#### INI_SetupCallbackName
>* **Parameters:**
>	* `fmat[]`: fmat[]_INFO
>	* `const remoteFormat[]`: const remoteFormat[]_INFO
>	* `filename[]`: filename[]_INFO
>	* `const bool:bFileFirst`: const bool:bFileFirst_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Generates a partial function name for processing callbacks.  Includes the
>	filename and a placeholder for the tag name.  This now takes extra
>	characters in to account and strips or converts bits:
>	some/dir/file name.ext
>	Becomes:
>	file_name
>	Before being formatted in to the specified remote format.  The filename
>	also takes in to account "/" directory separators and "\\" ones on Windows.
>	Because the	majority of this function is concerned with formatting just part
>	of the function name correctly, it short-circuits if it detects that there
>	is no place for the function name to go.
>	This is quite a complex function, but is only called once per file parse.
 
***

#### INI_GetCallback
>* **Parameters:**
>	* `callback[E_CALLBACK_DATA]`: callback[E_CALLBACK_DATA]_INFO
>	* `const format[]`: const format[]_INFO
>	* `tag[]`: tag[]_INFO
>	* `const input[]`: const input[]_INFO
>	* `const len`: const len_INFO
>	* `tag[]`: tag[]_INFO
>	* `callbackFormat[]`: callbackFormat[]_INFO
>	* `const bool:remote`: const bool:remote_INFO
>* **Returns:**
>	* Was the function found?
>* **Remarks:**
>	Gets a callback given a partial function name and a tag name.  Also saves
>	the tag elsewhere.  This might not work as a separate function - it will
>	need to be in the function called by the function with the inlines in.
 
***

#### INI_ParseFile
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `remoteFormat[]`: remoteFormat[]_INFO
>	* `bool:bFileFirst`: bool:bFileFirst_INFO
>	* `bool:bExtra`: bool:bExtra_INFO
>	* `extra`: extra_INFO
>	* `bLocal`: bLocal_INFO
>	* `bPassTag`: bPassTag_INFO
>	* `bFilter`: bFilter_INFO
>	* `filter`: filter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	bFileFirst sets the order and inclusion of the possible remoteFormat
>	parameters.  If true the format will add the filename first then the
>	current tag, if false the order will be reversed.  This can also be used
>	to exclude one or the other from the function name by setting the required
>	parameter to be entered first and then only having one %s in the format
>	sting.  The default order is tag first for languages compatibility.
 
***

#### INI_DoParentTag
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `remoteFormat[]`: remoteFormat[]_INFO
>	* `bool:bFileFirst`: bool:bFileFirst_INFO
>	* `bool:bExtra`: bool:bExtra_INFO
>	* `extra`: extra_INFO
>	* `bLocal`: bLocal_INFO
>	* `bPassTag`: bPassTag_INFO
>	* `bFilter`: bFilter_INFO
>	* `filter`: filter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	bFileFirst sets the order and inclusion of the possible remoteFormat
>	parameters.  If true the format will add the filename first then the
>	current tag, if false the order will be reversed.  This can also be used
>	to exclude one or the other from the function name by setting the required
>	parameter to be entered first and then only having one %s in the format
>	sting.  The default order is tag first for languages compatibility.
 
***

#### INI_Int
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### INI_Float
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### INI_Hex
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>* **Returns:**
>	* -
>* **Remarks:**

 
***

#### INI_Bin
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### INI_String
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>	* `len`: len_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The old version of "INI_String" didn't like not having a length.  It gave a
>	very odd error message too.  This has now been corrected by making the
>	length parameter optional.
 
***

#### INI_Bool
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `variable`: variable_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### INI_GetCallback
>* **Parameters:**
>	* `callback[E_CALLBACK_DATA]`: callback[E_CALLBACK_DATA]_INFO
>	* `const format[]`: const format[]_INFO
>	* `tag[]`: tag[]_INFO
>	* `const input[]`: const input[]_INFO
>	* `const len`: const len_INFO
>	* `tag[]`: tag[]_INFO
>	* `callbackFormat[]`: callbackFormat[]_INFO
>	* `const bool:remote`: const bool:remote_INFO
>* **Returns:**
>	* Was the function found?
>* **Remarks:**
>	Gets a callback given a partial function name and a tag name.  Also saves
>	the tag elsewhere.  This might not work as a separate function - it will
>	need to be in the function called by the function with the inlines in.
 
***

#### INI_ParseFile
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `remoteFormat[]`: remoteFormat[]_INFO
>	* `bool:bFileFirst`: bool:bFileFirst_INFO
>	* `bool:bExtra`: bool:bExtra_INFO
>	* `extra`: extra_INFO
>	* `bLocal`: bLocal_INFO
>	* `bPassTag`: bPassTag_INFO
>	* `bFilter`: bFilter_INFO
>	* `filter`: filter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	bFileFirst sets the order and inclusion of the possible remoteFormat
>	parameters.  If true the format will add the filename first then the
>	current tag, if false the order will be reversed.  This can also be used
>	to exclude one or the other from the function name by setting the required
>	parameter to be entered first and then only having one %s in the format
>	sting.  The default order is tag first for languages compatibility.
>	This function is now EXTENSIVELY documented here:
>	http://forum.sa-mp.com/showthread.php?t=485611
 
***

#### INI_Load
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `bool:bExtra`: bool:bExtra_INFO
>	* `extra`: extra_INFO
>	* `bLocal`: bLocal_INFO
>* **Returns:**
>	* INI_ParseFile
>* **Remarks:**
>	Wrapper for INI_ParseFile to use standard API features so people can
>	worry even less.  Designed for use with INI_Parse.
 
***

#### INI_IdentifyLineType
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `p0s`: p0s_INFO
>	* `p0e`: p0e_INFO
>	* `p1s`: p1s_INFO
>	* `p1e`: p1e_INFO
>	* `p2s`: p2s_INFO
>	* `p2e`: p2e_INFO
>	* `cont`: cont_INFO
>* **Returns:**
>	* e_INI_LINE_TYPE
>* **Remarks:**
>	This function's signature is so long that I put it on a separate line.  This
>	takes a line and determines what it is and where the parts are.
 
***

#### INI_SetupCallbackName
>* **Parameters:**
>	* `fmat[]`: fmat[]_INFO
>	* `const remoteFormat[]`: const remoteFormat[]_INFO
>	* `filename[]`: filename[]_INFO
>	* `const bool:bFileFirst`: const bool:bFileFirst_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Generates a partial function name for processing callbacks.  Includes the
>	filename and a placeholder for the tag name.  This now takes extra
>	characters in to account and strips or converts bits:
>	some/dir/file name.ext
>	Becomes:
>	file_name
>	Before being formatted in to the specified remote format.  The filename
>	also takes in to account "/" directory separators and "\\" ones on Windows.
>	Because the	majority of this function is concerned with formatting just part
>	of the function name correctly, it short-circuits if it detects that there
>	is no place for the function name to go.
>	This is quite a complex function, but is only called once per file parse.
 
***

#### INI_DoParentTag
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `remoteFormat[]`: remoteFormat[]_INFO
>	* `bool:bFileFirst`: bool:bFileFirst_INFO
>	* `bool:bExtra`: bool:bExtra_INFO
>	* `extra`: extra_INFO
>	* `bLocal`: bLocal_INFO
>	* `bPassTag`: bPassTag_INFO
>	* `bFilter`: bFilter_INFO
>	* `filter`: filter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	bFileFirst sets the order and inclusion of the possible remoteFormat
>	parameters.  If true the format will add the filename first then the
>	current tag, if false the order will be reversed.  This can also be used
>	to exclude one or the other from the function name by setting the required
>	parameter to be entered first and then only having one %s in the format
>	sting.  The default order is tag first for languages compatibility.
 
***

#### INI_Open
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>* **Returns:**
>	* INI - handle to the file or INI_NO_FILE.
>* **Remarks:**
>	Doesn't actually open the file, just starts a new buffer if possible.
 
***

#### INI_Close
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Writes any outstanding buffer data to the file and ends the stream.
 
***

#### INI_SetTag
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `tag[]`: tag[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets a new [tag] section header.  Subsequent data is written under this
>	header.  Uses lists for constant tag switching and checks the tag doesn't
>	already exist.
 
***

#### INI_DeleteTag
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `tag[]`: tag[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a [tag] section from a file.
 
***

#### INI_RemoveEntry
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for removing data.
 
***

#### INI_WriteString
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data[]`: data[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for strings.
 
***

#### INI_WriteInt
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for integers.  Fixed for very large numbers
>	based on code by Slice from "fixes.inc" for "valstr".
 
***

#### INI_WriteHex
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for integers to be written as hex values.
 
***

#### INI_WriteBin
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for integers to be written as binary values.
 
***

#### INI_WriteBool
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for booleans.
 
***

#### INI_WriteFloat
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `Float:data`: Float:data_INFO
>	* `accuracy`: accuracy_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for INI_AddToBuffer for floats.
 
***

#### INI_FreeEntry
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>
 
***

#### INI_AddToBuffer
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>	* `name[]`: name[]_INFO
>	* `data[]`: data[]_INFO
>* **Returns:**
>	* The slot written to, or -1 on failure.
>* **Remarks:**
>	First checks the name doesn't already exist under the current tag header
>	and if it does overwrites the current value.  If not checks there's room
>	in the buffer to write to and purges the buffer if not.  Finally saves the
>	data in the buffer for writing when required and adds the data to the
>	relevant list for tag inclusion.
 
***

#### INI_WriteBuffer
>* **Parameters:**
>	* `INI:file`: INI:file_INFO
>* **Returns:**
>	* Success/fail.
>* **Remarks:**
>	Opens the required file for reading and a temp file for read/writing.  Goes
>	through the entire file reading all contained data.  If it reaches a tag
>	line ([tag_name]) it dumps any unwritten data from the last tag (if there
>	was one) and starts processing the new tag.  While a tag is being processed
>	every line is compared against the UNWRITTEN new data for that tag in the
>	buffer, if they're the same it writes the new data instead (it also writes
>	any comments which were after the data in the original line back), else it
>	writes the original line back.
>	Once all the new data is written to the temp file any tags which haven't
>	been processed at all (i.e. were not found in the original file) are
>	written to the temp file along with all their data.  The original file is
>	then destroyed and reopend and all the data copied out from the temp file
>	to the newly opened original file, closed and saved.
 
***

#### INI_TryGetValue
>* **Parameters:**
>	* `start`: start_INFO
>	* `end`: end_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The INI system uses basic string functions to find candidate keys.  They
>	always start searching from the known start of the current tag, and check
>	that the found key is before the start of the next known tag.  If both those
>	conditions are true, this function is called to further verify the found
>	text - it could be a substring in a larger key, it could be a value, or it
>	could be commented out.  This function therefore checks that the found
>	position in the stored string is the first item on a line, and is followed
>	only by either nothing or an equals sign.
>	If this IS the key we are searching for, then we return a later position
>	corresponding to the start of the value (or cellmax if there is no value).
>	If this isn't a valid key, we return -1.
 
***

