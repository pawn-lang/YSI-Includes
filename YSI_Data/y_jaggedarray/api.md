#### Jagged_ResizeOne
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>	* `slot`: slot_INFO
>	* `newSize`: newSize_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The "slot" variable is usually used to hold the NEXT slot - we barely need
>	the number of the current slot once we have its address.
 
***

#### _Jagged_Resize
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### _Jagged_SizeOf
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* The current size of this slot.  This is NOT a compile-time operation.
>* **Remarks:**
>	Returns the data in BYTES NOT CELLS.
 
***

#### _Jagged_Address
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* The absolute address of this slot.
>* **Remarks:**
>	-
 
***

#### _Jagged_End
>* **Parameters:**
>	* `array[][]`: array[][]_INFO
>	* `size1`: size1_INFO
>	* `size2`: size2_INFO
>* **Returns:**
>	* The absolute address of the end of this array.
>* **Remarks:**
>	-
 
***

