#### XML_IsValid
>* **Parameters:**
>	* `XML:file`: XML:file_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_IsChar
>* **Parameters:**
>	* `char`: char_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_New
>* **Parameters:**

>* **Returns:**
>	* XML
>* **Remarks:**
>	Creates a new set of rules for parsing XML files.
 
***

#### XML_Destroy
>* **Parameters:**
>	* `XML:rule`: XML:rule_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_Parse
>* **Parameters:**
>	* `XML:rule`: XML:rule_INFO
>	* `filename[]`: filename[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Now supports self-closing tags and XML comments.
 
***

#### XML_Push
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `text[]`: text[]_INFO
>	* `depth`: depth_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Pushes an identifier and it's value (either explicitaly stated or returned
>	from another function) to the stack with basic parent info.
 
***

#### XML_GetParameter
>* **Parameters:**
>	* `line[]`: line[]_INFO
>	* `&pos`: &pos_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the data from inside ""s in an identifier.  Now supports
>	\ for escape characters.
 
***

#### XML_GetValue
>* **Parameters:**
>	* `line[]`: line[]_INFO
>	* `&pos`: &pos_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the text between tags.
 
***

#### XML_GetName
>* **Parameters:**
>	* `line[]`: line[]_INFO
>	* `&pos`: &pos_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the identifier of a piece of data.
 
***

#### XML_ParseTag
>* **Parameters:**
>	* `XML:rule`: XML:rule_INFO
>	* `name[]`: name[]_INFO
>	* `tagCount`: tagCount_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_GetKeyValue
>* **Parameters:**
>	* `key[]`: key[]_INFO
>	* `value[]`: value[]_INFO
>* **Returns:**
>	* Data found.
>* **Remarks:**
>	Pops items off the stack for use in custom functions.
 
***

#### XML_GetParentValue
>* **Parameters:**
>	* `key[]`: key[]_INFO
>	* `value[]`: value[]_INFO
>* **Returns:**
>	* Data found.
>* **Remarks:**
>	Does no poping, just searches for a value with the right name at the right
>	depth so children can use the data if they HAVE to.
 
***

#### XML_AddHandler
>* **Parameters:**
>	* `XML:ruls`: XML:ruls_INFO
>	* `trigger[]`: trigger[]_INFO
>	* `function[]`: function[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_RemoveHandler
>* **Parameters:**
>	* `XML:rule`: XML:rule_INFO
>	* `trigger[]`: trigger[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_AddParameter
>* **Parameters:**
>	* `parent`: parent_INFO
>	* `tag[]`: tag[]_INFO
>	* `value[]`: value[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### XML_AddItem
>* **Parameters:**
>	* `tag[]`: tag[]_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Starts the creation of a new tag to be written to a file, the structure
>	has to be manually created then written.  There is no buffering of multiple
>	tags before writing as a single tag can have quite a bit of data.
 
***

#### XML_WriteItem
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>	* `item`: item_INFO
>	* `bool:bIncludeXML`: bool:bIncludeXML_INFO
>	* `bool:bFavourShort`: bool:bFavourShort_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Writea the data for a tag to a file.
 
***

#### XML_WriteItemData
>* **Parameters:**
>	* `item`: item_INFO
>	* `File:fHnd`: File:fHnd_INFO
>	* `depth`: depth_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Recursive function to write a tag and it's children to a file.
 
***

#### XML_WriteItemDataShort
>* **Parameters:**
>	* `item`: item_INFO
>	* `File:fHnd`: File:fHnd_INFO
>	* `depth`: depth_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Recursive function to write a tag and it's children to a file.  Writes tags
>	in the shortest manner possible.  This does make it slower however (not much
>	though given the use of linked lists).
 
***

#### XML_RemoveItem
>* **Parameters:**
>	* `file[]`: file[]_INFO
>	* `tag[]`: tag[]_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Does a replace on data in a file with no new data.
 
***

#### XML_ReplaceItem
>* **Parameters:**
>	* `file[]`: file[]_INFO
>	* `tag[]`: tag[]_INFO
>	* `name[]`: name[]_INFO
>	* `replacement`: replacement_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Replaces a tag's data with new data, basically changes a tag's value.
 
***

