#### Bintree_Sort
>* **Parameters:**
>	* `input[][E_BINTREE_INPUT]`: input[][E_BINTREE_INPUT]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Entry point for Bintree_QSort.
 
***

#### Bintree_Fill
>* **Parameters:**
>	* `BinaryTree:output<>`: BinaryTree:output<>_INFO
>	* `data[][E_BINTREE_INPUT]`: data[][E_BINTREE_INPUT]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* Bintree_SortHalf.
>* **Remarks:**
>	Entry point for Bintree_SortHalf.
 
***

#### Bintree_Generate
>* **Parameters:**
>	* `BinaryTree:output<>`: BinaryTree:output<>_INFO
>	* `input[][E_BINTREE_INPUT]`: input[][E_BINTREE_INPUT]_INFO
>	* `size`: size_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Just calls the sort and fill routines.
 
***

#### Bintree_Reset
>* **Parameters:**
>	* `BinaryTree:tree<>`: BinaryTree:tree<>_INFO
>	* `pointer`: pointer_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Initialises the array for use.
 
***

#### Bintree_FindValue
>* **Parameters:**
>	* `BinaryTree:tree<>`: BinaryTree:tree<>_INFO
>	* `value`: value_INFO
>	* `&cont`: &cont_INFO
>	* `&old`: &old_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Itterates through the array following the various paths till it locates
>	the value provided or reaches a dead end.  If the current value is greater
>	than the search value, the search goes left, otherwise right.
>	If cont is not -1 the search will start from the data pointed to by the
>	data pointed to by conts' right path, this is to allow collisions to be
>	passed over if you want a subsequent one.
 
***

#### Bintree_QSort
>* **Parameters:**
>	* `numbers[][E_BINTREE_INPUT]`: numbers[][E_BINTREE_INPUT]_INFO
>	* `left`: left_INFO
>	* `right`: right_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Custom version of QSort (see YSI_misc) allows for E_BINTREE_INPUT data
>	types, preserving the relative pointers for the sorted data.
 
***

#### Bintree_SortHalf
>* **Parameters:**
>	* `BinaryTree:output<>`: BinaryTree:output<>_INFO
>	* `data[][E_BINTREE_INPUT]`: data[][E_BINTREE_INPUT]_INFO
>	* `index`: index_INFO
>	* `upper`: upper_INFO
>	* `offset`: offset_INFO
>* **Returns:**
>	* Size of balanced tree.
>* **Remarks:**
>	Recursively calls itself.  Bisects the passed array and passed each half
>	back to itself, with the middle value of each half being the left and
>	right branches of the middle value of the passed array (which isn't
>	included in either bisected half).  This is itterative so those are again
>	split and again split.  If the passed array is only one or two elements
>	big the behaviour is set and hardcoded.
>	Equal values SHOULD branch right, the code is designed for this however
>	the generation is not fully tested (it mostly branches right but adjacent
>	after bisecting values haven't been tested).
>	Based on code written for PHP by me.
 
***

#### Bintree_Add
>* **Parameters:**
>	* `BinaryTree:data<>`: BinaryTree:data<>_INFO
>	* `pointer`: pointer_INFO
>	* `value`: value_INFO
>	* `offset`: offset_INFO
>	* `maxsize`: maxsize_INFO
>* **Returns:**
>	* Next free location
>* **Remarks:**
>	-
>	native Bintree_Add(BinaryTree:tree<>, pointer, value, offset, maxsize = sizeof (data));
 
***

#### Bintree_Delete
>* **Parameters:**
>	* `BinaryTree:tree<>`: BinaryTree:tree<>_INFO
>	* `index`: index_INFO
>	* `count`: count_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The left branch is usually larger due to the division
>	method used so we start there.  Even though right is
>	>= and left is only < in even sized arrays the greater
>	chunk (unless there's only 2 items) goes left.
>	Called itteratively to ensure branches are maintained.
 
***

#### Bintree_Compress
>* **Parameters:**
>	* `BinaryTree:tree<>`: BinaryTree:tree<>_INFO
>	* `index`: index_INFO
>	* `count`: count_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Bintree_FindMin
>* **Parameters:**
>	* `BinaryTree:data<>`: BinaryTree:data<>_INFO
>	* `offset`: offset_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the smallest value on a branch
 
***

#### Bintree_FindMax
>* **Parameters:**
>	* `BinaryTree:data<>`: BinaryTree:data<>_INFO
>	* `offset`: offset_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the largest value on a branch
 
***

#### Bintree_UpdatePointers
>* **Parameters:**
>	* `BinaryTree:data<>`: BinaryTree:data<>_INFO
>	* `offset`: offset_INFO
>	* `mod`: mod_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Used for updating pointers when the target data has been modifed (i.e. a
>	value has been removed from the array and the array shifted).
 
***

