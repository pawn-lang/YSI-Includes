#### HashMap_Hash
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `&hash`: &hash_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Quickly hashes the string using Bernstein.  Caters for both packed and
>	unpacked strings.
 
***

#### HashMap_Init
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `&target`: &target_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>	* `&t2`: &t2_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the location of the hash map linked list data in the passed array data
>	and uses that to read the data through pointers subsequently.  It doesn't
>	matter WHERE in the enum the hash map data is, and if its not there you'll
>	get an error, or at least a warning.
 
***

#### HashMap_ByteLen
>* **Parameters:**
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* The number of BYTES this string takes up including the NULL.
>* **Remarks:**
>	Caters for both packed and unpacked strings.  The weirdness is basically
>	just: "ispacked(str) ? (* 1) : (* 4)".
 
***

#### HashMap_Add
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `const str[]`: const str[]_INFO
>	* `const value`: const value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a value to the given hash map under the given string key.
>	Actually more like adding an index, not a value...
 
***

#### HashMap_Get
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `const str[]`: const str[]_INFO
>* **Returns:**
>	* The value associated with this key in the given hash map.
>* **Remarks:**
>	-
 
***

#### HashMap_GetWithHash
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `const str[]`: const str[]_INFO
>	* `hash`: hash_INFO
>* **Returns:**
>	* The value associated with this key in the given hash map.
>* **Remarks:**
>	-
 
***

#### HashMap_RemoveKey
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `const str[]`: const str[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a given key and its associated value from the given hash map (if it
>	can be found in the map in the first place).
 
***

#### HashMap_RemoveValue
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes a value from the hash map.  First it gets the string key for the
>	value, then removes that (to update associated linked lists correctly).
 
***

#### HashMap_Set
>* **Parameters:**
>	* `HashMap:m<>`: HashMap:m<>_INFO
>	* `const str[]`: const str[]_INFO
>	* `const value`: const value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If this key is already in the hash map it is removed, and then the new value
>	is added in its place.  If the string already exists, its associated data is
>	removed.  If the value already exists, it is removed as well.
 
***

