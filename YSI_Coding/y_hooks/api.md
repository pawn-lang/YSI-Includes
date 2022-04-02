#### Hooks_MakeLongName
>* **Parameters:**
>	* `name`: name_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Expands all name parts like "CP" and "Obj" to their full versions (in this
>	example "Checkpoint" and "Object").
 
***

#### Hooks_MakeShortName
>* **Parameters:**
>	* `name`: name_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Compresses function names when required to fit within 32 or 64 characters
>	according to well defined rules (see "YSI_g_sReplacements").
 
***

#### Hooks_IsolateName
>* **Parameters:**
>	* `name`: name_INFO
>* **Returns:**
>	* The input string without y_hooks name decorations.
>* **Remarks:**
>	-
 
***

#### Hooks_GetPreloadLibraries
>* **Parameters:**
>	* `preloads`: preloads_INFO
>	* `precount`: precount_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Some includes, like "fixes.inc" and anti-cheats MUST come before all other
>	includes in order for everything to function correctly (at least fixes.inc
>	must).  This function looks for these definitions:
>	PRE_HOOK(FIXES)
>	Which tell y_hooks that any "FIXES_" prefixed callbacks are part of one of
>	these chains.
 
***

#### Hooks_GetPreHooks
>* **Parameters:**
>	* `preloads`: preloads_INFO
>	* `precount`: precount_INFO
>	* `name`: name_INFO
>	* `hooks`: hooks_INFO
>	* `count`: count_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds all the AMX file headers for functions with a similar name to the
>	given callback that should be called before (or near) the given callback.
 
***

#### Hooks_GetPointerRewrite
>* **Parameters:**
>	* `hooks`: hooks_INFO
>	* `num`: num_INFO
>	* `ptr`: ptr_INFO
>	* `next`: next_INFO
>	* `name`: name_INFO
>	* `nlen`: nlen_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Hooks_GetStubEntry
>* **Parameters:**
>	* `stub`: stub_INFO
>* **Returns:**
>	* The address at which the actual code in this function starts.
>* **Remarks:**
>	This handles three cases.  Regular functions end instantly as found.
>	Functions that start with a switch (even before "PROC") are assumed to be
>	state-based functions, and we find the most likely state to be used (i.e. we
>	remove all future state changes).
 
***

#### Hooks_GetAllHooks
>* **Parameters:**
>	* `name`: name_INFO
>	* `hooks`: hooks_INFO
>	* `idx`: idx_INFO
>	* `namelen`: namelen_INFO
>* **Returns:**
>	* The number of hooks found.
>* **Remarks:**
>	The name of the function currently being processed is derived from the first
>	found hook.  This means we already know of one hook, but to simplify the
>	code we get that one again here.  Above we only know the name not the
>	address.  Hence the "- 1" in "i = idx - 1" (to go back one function name).
>	Our "namelen" variable already contains the full length of the first found
>	hook - this is the length of "name", plus N extra characters.  The following
>	are all valid, and may occur when orders are played with:
>	@yH_OnX@
>	@yH_OnX@1
>	@yH_OnX@01
>	@yH_OnX@024
>	@yH_OnX@ZZZ
>	@yH_OnX@999@024
>	If we want to get the EXACT space taken up by all these hook names we would
>	need to get the string of the name in this function then measure it.  There
>	is really no point in doing this - if we have a second we will always have
>	enough space for our new names.  Instead, we assume that they are all just
>	@yH_OnX@
>	And add on that minimum length accordingly (plus 1 for the NULL character).
>	This length is used if the original callback doesn't exist but hooks do.  In
>	that case we need to add the callback to the AMX header, and there is a tiny
>	chance that the original name will be longer than one hook's name.  In that
>	case, having two or more hooks will (AFAIK) always ensure that we have
>	enough space to write the longer name.
>	If there is only one hook, no original function, and the name of the hook is
>	shorter than the name of the original function then we have an issue and
>	will have to do something else instead.
 
***

#### Hooks_GenerateCode
>* **Parameters:**
>	* `name`: name_INFO
>	* `hooks`: hooks_INFO
>	* `count`: count_INFO
>	* `write`: write_INFO
>	* `hasprehooks`: hasprehooks_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Hooks_InvalidateName
>* **Parameters:**
>	* `entry`: entry_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Basically, once we know a function has been included, wipe it from the AMX
>	header.
 
***

#### Hooks_GetFunctionWritePoint
>* **Parameters:**
>	* `name`: name_INFO
>	* `write`: write_INFO
>* **Returns:**
>	* The address at which this function's pointer is stored in the AMX header, if
>	* the function exists of course.
>* **Remarks:**
>	-
 
***

#### Hooks_GetDefaultReturn
>* **Parameters:**
>	* `name`: name_INFO
>* **Returns:**
>	* The default return for a callback, normally 1.
>* **Remarks:**
>	-
 
***

#### Hooks_WriteFunction
>* **Parameters:**
>	* `pointers`: pointers_INFO
>	* `size`: size_INFO
>	* `ret`: ret_INFO
>	* `skipable`: skipable_INFO
>* **Returns:**
>	* The number of bytes written to memory.
>* **Remarks:**
>	Generate some new code, very nicely :D.
 
***

#### Hooks_CompareNextCell
>* **Parameters:**
>	* `addr0`: addr0_INFO
>	* `addr1`: addr1_INFO
>* **Returns:**
>	* -1 - The first address is bigger.
>	* 0  - The addresses are the same
>	* 1  - The second address is bigger.
>* **Remarks:**
>	Reads two addresses, converts them to big endian, and compares them as four
>	characters of a string at once.
 
***

#### Hooks_ComparePublics
>* **Parameters:**
>	* `idx0`: idx0_INFO
>	* `idx1`: idx1_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Compares two public function entries, and if need-be, swaps them over.
 
***

#### Hooks_SortPublics
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Goes through the whole of the public functions table and sorts them all in
>	to alphabetical order.  This is done as we move and rename some so we need
>	to fix the virtual machine's binary search.
 
***

#### Hooks_CountInvalidPublics
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Counts the number of public functions that have had their names erased.