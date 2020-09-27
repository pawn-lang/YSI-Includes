#### Malloc_GetSlotSize
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* The size.
>* **Remarks:**
>	-
 
***

#### Malloc_SlotSize
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* The size.
>* **Remarks:**
>	-
 
***

#### Malloc_NewS
>* **Parameters:**
>	* `string[]`: string[]_INFO
>	* `pack`: pack_INFO
>* **Returns:**
>	* 0 on fail or a data handle on sucess.
>* **Remarks:**
>	Allocates a new piece of memory with enough space to store the given string.
 
***

#### Malloc_SetSlotSize
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Malloc_GetData
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `index`: index_INFO
>* **Returns:**
>	* The data
>* **Remarks:**
>	Basically like Malloc_Get but used internally.
 
***

#### Malloc_SetData
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `index`: index_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### mget
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `index`: index_INFO
>* **Returns:**
>	* The data
>* **Remarks:**
>	Shorthand for Malloc_Get.
 
***

#### mset
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `index`: index_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Shorthand for Malloc_Set.
 
***

#### mgets
>* **Parameters:**
>	* `target[]`: target[]_INFO
>	* `len`: len_INFO
>	* `array`: array_INFO
>	* `index`: index_INFO
>* **Returns:**
>	* The data
>* **Remarks:**
>	Shorthand for Malloc_GetS.
 
***

#### msets
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `str[]`: str[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Shorthand for Malloc_SetS.
 
***

#### Malloc_NextSlot
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the next free block of memory after the current one.
 
***

#### Malloc_Get
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>* **Returns:**
>	* Data.
>* **Remarks:**
>	Displays errors in secure mode.
 
***

#### Malloc_Set
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.
 
***

#### Malloc_GetS
>* **Parameters:**
>	* `target[]`: target[]_INFO
>	* `len`: len_INFO
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `pack`: pack_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.  Gets a string.
 
***

#### Malloc_SetS
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `str[]`: str[]_INFO
>	* `pack`: pack_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.  Inserts a string.
 
***

#### Malloc_SetVAS
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `arg`: arg_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Inserts a string by stack offset for use in vararg functions.
 
***

#### Malloc_GetA
>* **Parameters:**
>	* `target[]`: target[]_INFO
>	* `len`: len_INFO
>	* `array`: array_INFO
>	* `index`: index_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.  Gets an array.
 
***

#### Malloc_SetA
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `str[]`: str[]_INFO
>	* `len`: len_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.  Inserts an array.
 
***

#### Malloc_SetVAA
>* **Parameters:**
>	* `array`: array_INFO
>	* `index`: index_INFO
>	* `arg`: arg_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Inserts an array by stack offset for use in vararg functions.
 
***

#### malloc
>* **Parameters:**
>	* `size`: size_INFO
>* **Returns:**
>	* 0 on fail or a data handle on sucess.
>* **Remarks:**
>	Displays errors in secure mode.
 
***

#### calloc
>* **Parameters:**
>	* `size`: size_INFO
>* **Returns:**
>	* 0 on fail or a data handle on sucess.
>* **Remarks:**
>	Displays errors in secure mode.  Blanks allocated mmeory.
 
***

#### free
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Displays errors in secure mode.
 
***

#### Malloc_Allocate
>* **Parameters:**
>	* `size`: size_INFO
>	* `cleat`: cleat_INFO
>* **Returns:**
>	* Memory identifier.
>* **Remarks:**
>	The size check should never fail, if there's only 1 cell
>	extra somewhere just sneak it onto the end of an array,
>	if the user does proper bounds checking it shouldn't
>	matter.
>	Implementation code for malloc().
>	This code will find an area in memory with sufficient
>	space to store the given data and
 
***

#### Malloc_Free
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Implementation code for free().
 
***

#### Malloc_FindStackTop
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Loop back up through the stack and find the start of the current stack.  If
>	it doesn't equal the top of the true stack then we've been called via
>	"CallLocalFunction" at some point and thus MAY get some memory corruption.
>	Based on ZeeX's GetStackTrace, but gets frames instead of returns.
 
***

#### Malloc_TrySetup
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Move the heap pointer up a load.  This is called multiple times at the start
>	of the mode because we need to beat protections added in by the virtual
>	machine to steal away its heap area.
 
***

#### Malloc_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is the only callback that can be called before our timers when the mode
>	starts.  Make sure the heap is set up correctly.
 
***

