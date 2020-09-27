#### Bit_Bits
>* **Parameters:**
>	* `size`: size_INFO
>* **Returns:**
>	* Number of cells required for the bit array.
>* **Remarks:**
>	-
 
***

#### Bit_Slot
>* **Parameters:**
>	* `value`: value_INFO
>* **Returns:**
>	* The true array slot for this value.
>* **Remarks:**
>	-
 
***

#### Bit_Mask
>* **Parameters:**
>	* `value`: value_INFO
>* **Returns:**
>	* The bit in the array slot to use.
>* **Remarks:**
>	-
 
***

#### Bit_GetBit
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* State of the provided slot, 0 on fail.
>* **Remarks:**
>	Unsafe but faster for when you're sure you're within range.
 
***

#### Bit_Get
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* State of the provided slot, 0 on fail.
>* **Remarks:**
>	-
>	native Bit_Get(BitArray:array<>, slot);
 
***

#### Bit_Let
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets the slot to 1.
 
***

#### Bit_Vet
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets the slot to 0.
 
***

#### Bit_Set
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>	* `bool:set`: bool:set_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
>	native Bit_Set(BitArray:array<>, slot, bool:set, size = sizeof (array));
 
***

#### Bit_FastSet
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `slot`: slot_INFO
>	* `bool:set`: bool:set_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Exactly the same as "Bit_Set", but as a macro not a function.
>	native Bit_FastSet(BitArray:array<>, slot, bool:set, size = sizeof (array));
 
***

#### Bit_SetAll
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `bool:set`: bool:set_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
>	native Bit_SetAll(BitArray:array<>, bool:set, size = sizeof (array));
 
***

#### Bit_GetCount
>* **Parameters:**
>	* `Bit:array[]`: Bit:array[]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* Number of 1s in the array.
>* **Remarks:**
>	Code from:
>	http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
>	native Bit_Count(BitArray:array<>, size = sizeof (array));
 
***

