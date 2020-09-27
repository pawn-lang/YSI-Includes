#### Cell_ReverseBits
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* All the bits in the input reversed.
>* **Remarks:**
>	1)
>	Example: 0b11110000000000000000000000000000
>	Becomes: 0b00000000000000000000000000001111
>	2)
>	Example: 0b10110011100011110000111110000010
>	Becomes: 0b01000001111100001111000111001101
>	3)
>	Example: 0b01010101010101010101010101010101
>	Becomes: 0b10101010101010101010101010101010
 
***

#### Cell_ReverseNibbles
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* All the nibbles (4-bit chunks) in the input reversed.
>* **Remarks:**
>	1)
>	Example: 0x12345678
>	Becomes: 0x87654321
>	2)
>	Example: 0x010F0703
>	Becomes: 0x3070F010
>	3)
>	Example: 0xF0F0F0F0
>	Becomes: 0x0F0F0F0F
 
***

#### Cell_ReverseBytes
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* All the bytes in the input reversed.
>* **Remarks:**
>	1)
>	Example: 0x12345678
>	Becomes: 0x78563412
>	2)
>	Example: 0x01020304
>	Becomes: 0x04030201
>	3)
>	Example: 0xFF00FF00
>	Becomes: 0x00FF00FF
 
***

#### Cell_CountBits
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* The number of 1s (set bits) in the input.
>* **Remarks:**
>	1)
>	Example: 0
>	Returns: 0
>	2)
>	Example: 1
>	Returns: 1
>	3)
>	Example: 0x01010101
>	Returns: 4
>	I rewrote this in assembly just to see if I could pretty much.  I also
>	rewrote the lookup version in assembly.  In theory it should be faster, but
>	the marshalling of data was a little awkward.
 
***

#### Cell_GetLowestBit
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* The integer position of the lowest set bit.
>* **Remarks:**
>	1)
>	Example: 0b00000000000000000000000000000001
>	Returns: 0
>	2)
>	Example: 0b00000000000000000000000000001000
>	Returns: 3
>	3)
>	Example: 0b00010001100011000011100010001000
>	Returns: 3
>	NOTE: This function returns "0" for both numbers with the "1" bit set AND
>	the number "0", which has NO bits set.  Check that the number is valid
>	before passing it to this function.
>	See: http://supertech.csail.mit.edu/papers/debruijn.pdf
 
***

#### Cell_GetLowestBitEx
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* The integer position of the lowest set bit PLUS ONE.
>* **Remarks:**
>	This function is identical to "Cell_GetLowestBit", but gives different
>	results for 0 and non-zero numbers.  The examples below all have a result
>	one higher than the "Cell_GetLowestBit" function.
>	1)
>	Example: 0b00000000000000000000000000000001
>	Returns: 1
>	2)
>	Example: 0b00000000000000000000000000001000
>	Returns: 4
>	3)
>	Example: 0b00010001100011000011100010001000
>	Returns: 4
>	4)
>	Example: 0
>	Returns: 0
>	See: http://supertech.csail.mit.edu/papers/debruijn.pdf
 
***

#### Cell_GetLowestComponent
>* **Parameters:**
>	* `number`: number_INFO
>* **Returns:**
>	* The lowest set bit.
>* **Remarks:**
>	Similar to Cell_GetLowestBit, but returns the bit, not the position of the
>	bit.
>	1)
>	Example: 0b00000000000000000000000000000001
>	Returns: 0b00000000000000000000000000000001
>	2)
>	Example: 0b00000000000000000000000000001000
>	Returns: 0b00000000000000000000000000001000
>	3)
>	Example: 0b00010001100011000011100010001000
>	Returns: 0b00000000000000000000000000001000
 
***

#### Cell_CompressRightPrecomputed
>* **Parameters:**
>	* `x`: x_INFO
>	* `m`: m_INFO
>	* `masks`: masks_INFO
>* **Returns:**
>	* Selected bits from "x", shifted to be LSBs.
>* **Remarks:**
>	Very briefly, do "x & m", to select certain bits, then shift those bits by
>	various amounts so that they are consecutive:
>	x = 0b110011
>	m = 0b011010
>	x & m = 0b010010
>	From here, because the mask was three bits we know we want just those three
>	bits in the LSBs, so the answer becomes:
>	0b000101
>	Just read this question, it has a diagram:
>	http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb
 
***

#### Cell_ExpandLeftPrecomputed
>* **Parameters:**
>	* `x`: x_INFO
>	* `m`: m_INFO
>	* `masks`: masks_INFO
>* **Returns:**
>	* LSBs from "x", shifted to selected bit positions.
>* **Remarks:**
>	The reverse of "Cell_CompressRightPrecomputed".  Doesn't return exactly the
>	original number before a compression, just the original number ANDed with
>	the mask "m".
 
***

#### Cell_PrecomputeMaskPermutation
>* **Parameters:**
>	* `m`: m_INFO
>* **Returns:**
>	* Five precomputed constants to help expand or contract this mask.
>* **Remarks:**
>	The full maths for generalised expansion and contraction is quite complex;
>	however, much of the inner loop relies only on the mask and not on the value
>	being manipulated.  Given this we can do a lot of work in advance, say
>	outside a loop, to avoid repeated calculations.
 
***

#### Cell_CompressRight
>* **Parameters:**
>	* `x`: x_INFO
>	* `m`: m_INFO
>* **Returns:**
>	* Selected bits from "x", shifted to be LSBs.
>* **Remarks:**
>	Doesn't require precomputation.
 
***

#### Cell_ExpandLeft
>* **Parameters:**
>	* `x`: x_INFO
>	* `m`: m_INFO
>* **Returns:**
>	* LSBs from "x", shifted to selected bit positions.
>* **Remarks:**
>	Doesn't require precomputation.
 
***

