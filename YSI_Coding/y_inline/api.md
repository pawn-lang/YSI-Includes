#### @_y_inline_y_@
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Calls functions we call via "SYSREQ.C".
 
***

#### Inline_DecodeSimple
>* **Parameters:**
>	* `from[]`: from[]_INFO
>	* `at`: at_INFO
>* **Returns:**
>	* The next variable type stored in the bit array.
>* **Remarks:**
>	Returns data from a bit array when it is known that only basic types are
>	stored (i.e. no arrays with length parameters).
 
***

#### GetRemoteFunction
>* **Parameters:**
>	* `func[]`: func[]_INFO
>	* `spec[]`: spec[]_INFO
>* **Returns:**
>	* A pointer to the function.
>* **Remarks:**
>	Accepts the following parameter specifiers:
>	i - Integer (also x/c/d/h)
>	f - Float (also g)
>	s - String
>	ai - Array (followed by length)
>	v - Reference (&var, any tag)
 
***

#### GetLocalFunction
>* **Parameters:**
>	* `func[]`: func[]_INFO
>	* `spec[]`: spec[]_INFO
>* **Returns:**
>	* A pointer to the function.
>* **Remarks:**
>	Accepts the following parameter specifiers:
>	i - Integer (also x/c/d/h)
>	f - Float (also g)
>	s - String
>	ai - Array (followed by length)
>	v - Reference (&var, any tag)
 
***

#### CallStoredFunction
>* **Parameters:**
>	* `func`: func_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Call the function in the given pointer with the given parameters.
 
***

#### Callback_Get
>* **Parameters:**
>	* `callback:name`: callback:name_INFO
>	* `ret[E_CALLBACK_DATA]`: ret[E_CALLBACK_DATA]_INFO
>	* `expect[]`: expect[]_INFO
>	* `remote`: remote_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Looks up the callback by name.  If the name has the correct data embedded
>	within it that's great and we use that directly.  Otherwise this function
>	loops backwards over the callbacks currently in scope (mostly) to the start
>	of the parent function.  If a match is still not found this looks for a
>	public function of the same name.  If that isn't found either it gives up.
>	The new "remote" parameter returns instantly with a remote public function
>	stub, and no stored data.
 
***

#### Callback_Release
>* **Parameters:**
>	* `input[E_CALLBACK_DATA]`: input[E_CALLBACK_DATA]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Releases all the data associated with a given callback (closure storage).
 
***

#### Callback_Restore
>* **Parameters:**
>	* `func[E_CALLBACK_DATA]`: func[E_CALLBACK_DATA]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Makes variables referenced, instead of valued.  When used after
>	"Callback_Call" the values of any variables in the enclosing function that
>	were modified in the inline function will be propgated so that their new
>	values are seen by the original parent function (rather than that function
>	still seeing the original values prior to the inline function modifying
>	them).  Note that this does no checks at all at the minute - if you call an
>	inline function whose parent is not currently on the stack, this will
>	probably fail catastrophically!
 
***

#### Callback_Call
>* **Parameters:**
>	* `func[E_CALLBACK_DATA]`: func[E_CALLBACK_DATA]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Takes an inline function handler and parameters, and either calls the
>	public function while passing through the parameters, or just jumps to the
>	carefully crafted inline function code.
 
***

#### Callback_Array
>* **Parameters:**
>	* `func[E_CALLBACK_DATA]`: func[E_CALLBACK_DATA]_INFO
>	* `params[]`: params[]_INFO
>	* `num`: num_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is very similar to Callback_Call, but takes an array of ADDRESSES
>	instead of normal parameters.  This is designed to help support some
>	experimental OO code I was working on...
>	If the target is a public function, the parameters are resolved and passed
>	normally.  If the target is an inline function we are optimised for the
>	common case, so move the data on to the stack (currently done value-by-value
>	not all at once) and call "Callback_Call".
>	The new assembly is based on "rawMemset" in "y_utils".
 
***

#### Inline_Timer
>* **Parameters:**
>	* `func[]`: func[]_INFO
>	* `delay`: delay_INFO
>	* `interval`: interval_INFO
>	* `repeat`: repeat_INFO
>	* `format[]`: format[]_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Calls a function, which may be an inline function, after a given delay, and
>	with the given regularity after that.  The parameters are slightly different
>	to those in SetTimer - that takes only an interval and a repeat boolean.
>	This instead takes two times - the first is the delay before the first call,
>	the second is the delay between all subsequent calls (mainly to offset
>	different timers within a given period).  The "repeat" parameter is also
>	different - instead of being a boolean, it is a count.  "0" no longer means
>	"don't repeat", but "repeat forever".  "1" no longer means "repeat forever",
>	but "call once".  All other numbers (beside 0) specify an exact number of
>	times to call the function before calling it no more.  This is in line with
>	the "SetTimer_" and "SetTimerEx_" functions in the fixes2 plugin.
 
***

#### I@E
>* **Parameters:**
>	* `s`: s_INFO
>	* `constFunc`: constFunc_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	AKA. Inline_Entry
>	This function gets the start of an inline function's code block.  It then
>	removes itself from the compiled code so that it can never be called agian.
>	If "constFunc" is 3, copy the stack back, if it isn't don't.
 
***

#### I@F
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	AKA. Inline_Allocator.
>	This function determines the exact address of the start of the main inline
>	function container loop.  That is, the label that things like "continue"
>	jump to so that we know how much space we have to play with and where it is.
 
***

#### I@L
>* **Parameters:**

>* **Returns:**
>	* 0
>* **Remarks:**
>	AKA. Inline_Main.
>	The code before the start of the function is split in to three parts:
>	The first part comes before the start of the loop condition, and is where
>	all the variables are initialised in the compiled code.  As we don't want to
>	initialise any variables, this can be repurposed for function entry code.
>	The address of this is stored in "entry", and it ends at "loop".
>	The second part is where the function loops back to.  This MUST start with a
>	"RETN" instruction to end the function in all cases, so any startup code in
>	the first segment must jump over that "RETN".  The remainder of this section
>	can be used for any more entry or exit code that is required.  Note that
>	it can also start with a "STACK" opcode when required.  This section starts
>	at "loop" and ends at "code".
>	The final segment is not technically BEFORE the main function code but
>	AFTER.  That's normally where the stack is restored, but we now have full
>	control of that (so don't forget to write it in to the process exit code).
>	"Inline_Allocator" currently marks the end of the first segment, and
>	"Inline_Main" marks the end of the second segment.
 
***

#### StoredF_IsHooked
>* **Parameters:**
>	* `addr`: addr_INFO
>* **Returns:**
>	* Is the function at this address already hooked by us?
>* **Remarks:**
>	-
 
***

#### StoredF_OnPubGenError
>* **Parameters:**
>	* `ctx[AsmContext]`: ctx[AsmContext]_INFO
>	* `AsmError:error`: AsmError:error_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is a fatal error as there isn't really anything we can do about it.
 
***

#### StoredF_WritePublicCode
>* **Parameters:**
>	* `fptr`: fptr_INFO
>	* `spec[]`: spec[]_INFO
>* **Returns:**
>	* the new function pointer.
>* **Remarks:**
>	Writes a stub for calling a public function with an alternate method.
>	Because "CallStoredFunction" (the call entry point) takes all its parameters
>	by reference and some of the actual function's parameters won't be, we have
>	to generate the code to convert those that aren't to values only.  Also,
>	because "CallStoredFunction" takes an extra parameter that's the address of
>	the function to call, we have to wipe that from the stack and update the
>	resulting frame header.
 
***

#### Remote_DoSearch
>* **Parameters:**
>	* `str[]`: str[]_INFO
>	* `ptr`: ptr_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds a given string in a given list.
 
***

#### Remote_WriteStubCode
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	This rewrites itself to be the bulk of the call to "CallRemoteFunction".  It
>	modifies the stack so that the parameters already pushed are the parameters
>	passed to the native function.
 
***

#### Remote_WriteSpecAndFunc
>* **Parameters:**
>	* `&fptr`: &fptr_INFO
>	* `const func[]`: const func[]_INFO
>	* `sptr`: sptr_INFO
>	* `const spec[]`: const spec[]_INFO
>* **Returns:**
>	* A pointer to the start of the newly generated code.
>* **Remarks:**
>	Generates a tiny function-specific stub that sets the values for the
>	function and specifier strings to pass to "CallRemoteFunction", and checks
>	for any empty strings - converting them to "NULL" instead.
 
***

#### Inline_DecodeComplex
>* **Parameters:**
>	* `from[]`: from[]_INFO
>	* `at`: at_INFO
>	* `len`: len_INFO
>* **Returns:**
>	* The next variable type stored in the bit array, and the length of arrays.
>* **Remarks:**
>	Returns data from a bit array when the parameter could be basic (variable or
>	reference), or an array with a length (includes strings).  This requries far
>	more complex code to decode as the lengths may span multiple cells, types
>	can't because they are always 2 bits and always start on an even bit.
 
***

#### operator+
>* **Parameters:**
>	* `InlineRet:a`: InlineRet:a_INFO
>	* `b`: b_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is a prefix function that takes some value and returns it to the
>	caller's caller.  This makes "@return" in inline functions work.
 
***

