#### M@
>* **Parameters:**
>	* `volatile vardata[]`: volatile vardata[]_INFO
>	* `dataSize`: dataSize_INFO
>	* `&pointer`: &pointer_INFO
>	* `ds2 = 1`: ds2 = 1_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function modifies "vardata" well beyond its original limits to contain
>	information on the structure of the enum used to define "val".  This code
>	uses the name and size information passed in the additional parameters as
>	strings, and makes assumptions about how the compiler lays out memory to
>	combine all the passed strings in to one big string in what could be ROM,
>	but in SA:MP isn't.  This takes a human readable(ish) description of the
>	array elements and converts it in to a much simpler to read format for the
>	computer to use later when loading and storing data.
 
***

#### N@
>* **Parameters:**
>	* `val[][]`: val[][]_INFO
>	* `volatile vardata[]`: volatile vardata[]_INFO
>	* `{K@, L@, M@, N@, _}:...`: {K@, L@, M@, N@, _}:..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function modifies "vardata" well beyond its original limits to contain
>	information on the structure of the enum used to define "val".  This code
>	uses the name and size information passed in the additional parameters as
>	strings, and makes assumptions about how the compiler lays out memory to
>	combine all the passed strings in to one big string in what could be ROM,
>	but in SA:MP isn't.  This takes a human readable(ish) description of the
>	array elements and converts it in to a much simpler to read format for the
>	computer to use later when loading and storing data.
>	The description above is no longer the case.  This code now just saves the
>	size of the data, the number of players in the array, the address of the
>	data, a pointer to another data set and the name of this data.  This is by
>	far much simpler than the old version.
 
***

