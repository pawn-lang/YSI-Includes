#### UCMP
>* **Parameters:**
>	* `value`: value_INFO
>	* `upper`: upper_INFO
>* **Returns:**
>	* An unsigned comparison between the two values.
>* **Remarks:**
>	-
 
***

#### IS_IN_RANGE
>* **Parameters:**
>	* `value`: value_INFO
>	* `lower`: lower_INFO
>	* `upper`: upper_INFO
>* **Returns:**
>	* Is the value in the given range.
>* **Remarks:**
>	Equivalent to:
>	(%1) <= (%0) < (%2)
 
***

#### ceildiv
>* **Parameters:**
>	* `numerator`: numerator_INFO
>	* `denominator`: denominator_INFO
>* **Returns:**
>	* (numerator / denominator) rounded up.
>* **Remarks:**
>	Normal integer division ALWAYS rounds down - this always rounds up.
 
***

#### floordiv
>* **Parameters:**
>	* `numerator`: numerator_INFO
>	* `denominator`: denominator_INFO
>* **Returns:**
>	* (numerator / denominator) rounded down.
>* **Remarks:**
>	Normal integer division ALWAYS rounds down - this also always rounds down,
>	making it a little pointless, but also more explicit in function.
 
***

#### isnull
>* **Parameters:**
>	* `str`: str_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### isodd
>* **Parameters:**
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### iseven
>* **Parameters:**
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### strcpy
>* **Parameters:**
>	* `dest`: dest_INFO
>	* `src`: src_INFO
>	* `len`: len_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### StripNL
>* **Parameters:**
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Updated from old versions, should be more efficient
 
***

#### endofline
>* **Parameters:**
>	* `line[]`: line[]_INFO
>	* `pos`: pos_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if the current point in a line is the end of non-whitespace data.
 
***

#### chrfind
>* **Parameters:**
>	* `needle`: needle_INFO
>	* `haystack[]`: haystack[]_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* Fail - -1, Success - pos
>* **Remarks:**
>	-
 
***

#### IPToInt
>* **Parameters:**
>	* `ip[]`: ip[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### bernstein
>* **Parameters:**
>	* `string[]`: string[]_INFO
>* **Returns:**
>	* the bernstein hash of the input string
>* **Remarks:**
>	This is a 32bit hash system so is not very secure, however we're only
>	using this as a string enumerator to uniquely identify strings easilly
>	and allow for a binary search of strings based on the hash of their name.
>	crc32, then jenkins were originally used however this is far faster, if a
>	little collision prone, but we're checking the strings manually anyway.
>	This doesn't matter as it would be done regardless of hash method, so this
>	doesn't need to be accounted for.  Speed is all that matters with at
>	least a bit of non collision (the number of strings we're dealing with,
>	this should have none-few collisions).
>	I modified it slightly from the original code pasted by aru, to code
>	closer to the code http://www.burtleburtle.net/bob/hash/doobs.html and
>	to work with PAWN (and shaved 0.2?s off the time for one call :D).
>	Uber reduced version (just for fun):
>	b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
>	Update: Contrary to what I said above this is also used to identify colour
>	strings for the updated text system involving file based styling and this
>	is not checked for collisions as it's unimportant.  But this doesn't affect
>	the function at all, I just mentioned it here for "interest".
>	Rewritten in self-generating assembly.
 
***

#### ishex
>* **Parameters:**
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* true/false.
>* **Remarks:**
>	-
 
***

#### unpack
>* **Parameters:**
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* unpacked string
>* **Remarks:**
>	Mainly used for debugging.
 
***

#### GetIP
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* IP as a 32bit int.
>* **Remarks:**
>	-
 
***

#### getstring
>* **Parameters:**
>	* `addr`: addr_INFO
>* **Returns:**
>	* string
>* **Remarks:**
>	Is passed the result of getarg, which will be the address of a string (in
>	theory) and uses that for DMA to get the string.
 
***

#### isnumeric
>* **Parameters:**
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a given string is numeric.
 
***

#### hexstr
>* **Parameters:**
>	* `	string[]`: 	string[]_INFO
>* **Returns:**
>	* value of the passed hex string.
>* **Remarks:**
>	Now stops on invalid characters.
 
***

#### boolstr
>* **Parameters:**
>	* `	string[]`: 	string[]_INFO
>* **Returns:**
>	* bool: passed boolean.
>* **Remarks:**
>	This can take a number of ways of representing booleans - 0, false and
>	nothing there.  Anything not one of those things (false is not case
>	sensitive) is assumed true.
 
***

#### binstr
>* **Parameters:**
>	* `	string[]`: 	string[]_INFO
>* **Returns:**
>	* bool: passed boolean.
>* **Remarks:**
>	This takes a value in 0110101 (boolean) format and returns it as a
>	regular value.
 
***

#### rawMemcpy
>* **Parameters:**
>	* `dest`: dest_INFO
>	* `src`: src_INFO
>	* `bytes`: bytes_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like memcpy, but takes addresses instead of arrays.  Also far less secure.
 
***

#### memset|rawMemset
>* **Parameters:**
>	* `arr[], iAddress`: arr[], iAddress_INFO
>	* `iValue`: iValue_INFO
>	* `iSize`: iSize_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Based on code by Slice:
>	http://forum.sa-mp.com/showthread.php?p=1606781#post1606781
>	Modified to use binary flags instead of a loop.
>	"memset" takes an array, the size of the array, and a value to fill it with
>	and sets the whole array to that value.
>	"rawmemset" is similar, but takes an AMX data segment address instead and
>	the size is in bytes, not cells.  However, the size must still be a multiple
>	of 4.
 
***

#### ReturnPlayerName
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Now uses a global array to avoid repeated function calls.  Actually doesn't
>	because that causes issues with multiple scripts.
 
***

#### ftouch
>* **Parameters:**
>	* `filename`: filename_INFO
>* **Returns:**
>	* 0 - File already exists.
>	* 1 - File was created.
>	* -1 - File was not created.
>* **Remarks:**
>	This "touches" a file in the Unix sense of creating it but not opening or
>	editing it in any way.
 
***

#### InterpolateColour
>* **Parameters:**
>	* `startcolor`: startcolor_INFO
>	* `endcolor`: endcolor_INFO
>	* `value`: value_INFO
>	* `maxvalue`: maxvalue_INFO
>	* `minvalue`: minvalue_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function takes two endpoint values (minvalue and maxvalue, with
>	minvalue defaulting to 0), along with a third value (value) whose distance
>	between the two endpoints is calculated (as a percentage).  This percentage
>	value is then applied to the two colours given to find a third colour at
>	some point between those two colours.
>	For example, if the endpoints given are "0" and "10", and the value given is
>	"3", then that is "30%" of the way between the two endpoints.  We therefore
>	want to find a colour that is 30% of the way between the two given colours.
 
***

#### SkipWhitespace
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `pos`: pos_INFO
>* **Returns:**
>	* The end of the whitespace.
>* **Remarks:**
>	Doesn't skip over NULL terminators.
 
***

#### Trim
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `start`: start_INFO
>	* `end`: end_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Modifies "start" and "end" to be tight on text in "str".
 
***

#### ftell
>* **Parameters:**
>	* `File:f`: File:f_INFO
>* **Returns:**
>	* The current position in the file.
>* **Remarks:**
>	Doesn't seem to work despite documentation claiming it will.
 
***

