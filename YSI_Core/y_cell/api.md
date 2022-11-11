y_cell - v0.2
==========================================
Provides a few functions for manipulating the bits in single cells. Note that this is distinct from the y_bit library.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Constants


### `YSI_g_c20s`:


#### Value
`-538976289`



### `YSI_g_c80s`:


#### Value
`-2139062144`



### `YSI_g_cFEs`:


#### Value
`-16843009`



## Functions


### `Cell_Abs`:

Cell_Abs(GLOBAL_TAG_TYPES:x, m)



#### Syntax


```pawn
Cell_Abs(number, tag)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`number`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the absolute value of.	 |
| 	`tag`	 | 	The tag of the number, in case its `Float`.	 |

#### Returns
The absolute value of a number.


#### Remarks
Get the absolute value of a number. Floats just remove MSB. For ints, multiply the whole number by the MSB shifted OR 1 (1 or -1).


#### Depends on
* [`cellmax`](#cellmax)
* [`y_utils_abs_shift`](#y_utils_abs_shift)
#### Estimated stack usage
1 cells



### `Cell_CompressRight`:

Cell_CompressRight(GLOBAL_TAG_TYPES:x, m);



#### Syntax


```pawn
Cell_CompressRight(x, m)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`x`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to compress.	 |
| 	`m`	 | 	The mask for which bits to compress.	 |

#### Returns
Selected bits from "x", shifted to be LSBs.


#### Remarks
Doesn't require precomputation.


#### Depends on
* [`Cell_CompressRightPrecomputed`](#Cell_CompressRightPrecomputed)
* [`Cell_PrecomputeMaskPermutation`](#Cell_PrecomputeMaskPermutation)
* [`Cell_PrecomputeMaskPermutation`](#Cell_PrecomputeMaskPermutation)
#### Estimated stack usage
12 cells



### `Cell_CompressRightPrecomputed`:

Cell_CompressRightPrecomputed(GLOBAL_TAG_TYPES:x, m, masks[5]);



#### Syntax


```pawn
Cell_CompressRightPrecomputed(x, m, masks[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`x`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to compress.	 |
| 	`m`	 | 	The mask for which bits to compress.	 |
| 	`masks`	 | 	` [5] ` Precomputed constants for the compression.	 |

#### Returns
Selected bits from "x", shifted to be LSBs.


#### Remarks
Very briefly, do "x & m", to select certain bits, then shift those bits by various amounts so that they are consecutive: x = 0b110011 m = 0b011010 x & m = 0b010010 From here, because the mask was three bits we know we want just those three bits in the LSBs, so the answer becomes: 0b000101 Just read this question, it has a diagram: [http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb](http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb)


#### Estimated stack usage
2 cells



### `Cell_CountBits`:

Cell_CountBits(number);



#### Syntax


```pawn
Cell_CountBits(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the number of 1s in.	 |

#### Returns
The number of 1s (set bits) in the input.


#### Remarks
1) Example: 0 Returns: 0 2) Example: 1 Returns: 1 3) Example: 0x01010101 Returns: 4 I rewrote this in assembly just to see if I could pretty much. I also rewrote the lookup version in assembly. In theory it should be faster, but the marshalling of data was a little awkward.


#### Estimated stack usage
1 cells



### `Cell_CountBlanks`:

Cell_CountBlanks(number);



#### Syntax


```pawn
Cell_CountBlanks(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the number of 0s in.	 |

#### Returns
The number of 0s (unset bits) in the input.


#### Remarks
Like Cell_CountBits, but for 0s not 1s.


#### Estimated stack usage
1 cells



### `Cell_ExpandLeft`:

Cell_ExpandLeft(GLOBAL_TAG_TYPES:x, m)



#### Syntax


```pawn
Cell_ExpandLeft(x, m)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`x`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to expand.	 |
| 	`m`	 | 	The mask for which bits to expand to.	 |

#### Returns
LSBs from "x", shifted to selected bit positions.


#### Remarks
Doesn't require precomputation.


#### Depends on
* [`Cell_ExpandLeftPrecomputed`](#Cell_ExpandLeftPrecomputed)
* [`Cell_PrecomputeMaskPermutation`](#Cell_PrecomputeMaskPermutation)
* [`Cell_PrecomputeMaskPermutation`](#Cell_PrecomputeMaskPermutation)
#### Estimated stack usage
12 cells



### `Cell_ExpandLeftPrecomputed`:

Cell_ExpandLeftPrecomputed(GLOBAL_TAG_TYPES:x, m, masks[5])



#### Syntax


```pawn
Cell_ExpandLeftPrecomputed(x, m, masks[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`x`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to expand.	 |
| 	`m`	 | 	The mask for which bits to expand to.	 |
| 	`masks`	 | 	` [5] ` Precomputed constants for the expansion.	 |

#### Returns
LSBs from "x", shifted to selected bit positions.


#### Remarks
The reverse of "Cell_CompressRightPrecomputed". Doesn't return exactly the original number before a compression, just the original number ANDed with the mask "m".


#### Estimated stack usage
2 cells



### `Cell_GetLowestBit`:

Cell_GetLowestBit(number);



#### Syntax


```pawn
Cell_GetLowestBit(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest set bit of.	 |

#### Returns
The integer position of the lowest set bit.


#### Remarks
1) Example: 0b00000000000000000000000000000001 Returns: 0 2) Example: 0b00000000000000000000000000001000 Returns: 3 3) Example: 0b00010001100011000011100010001000 Returns: 3 NOTE: This function returns "0" for both numbers with the "1" bit set AND the number "0", which has NO bits set. Check that the number is valid before passing it to this function. See: [http://supertech.csail.mit.edu/papers/debruijn.pdf](http://supertech.csail.mit.edu/papers/debruijn.pdf)


#### Depends on
* [`YSI_g_scDeBruijn1`](#YSI_g_scDeBruijn1)
#### Estimated stack usage
1 cells



### `Cell_GetLowestBitEx`:

Cell_GetLowestBitEx(number);



#### Syntax


```pawn
Cell_GetLowestBitEx(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest set bit of PLUS ONE.	 |

#### Returns
The integer position of the lowest set bit PLUS ONE.


#### Remarks
This function is identical to "Cell_GetLowestBit", but gives different results for 0 and non-zero numbers. The examples below all have a result one higher than the "Cell_GetLowestBit" function. 1) Example: 0b00000000000000000000000000000001 Returns: 1 2) Example: 0b00000000000000000000000000001000 Returns: 4 3) Example: 0b00010001100011000011100010001000 Returns: 4 4) Example: 0 Returns: 0 See: [http://supertech.csail.mit.edu/papers/debruijn.pdf](http://supertech.csail.mit.edu/papers/debruijn.pdf)


#### Depends on
* [`YSI_g_scDeBruijn2`](#YSI_g_scDeBruijn2)
#### Estimated stack usage
1 cells



### `Cell_GetLowestBlank`:

Cell_GetLowestBlank(number);



#### Syntax


```pawn
Cell_GetLowestBlank(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest unset bit of.	 |

#### Returns
The integer position of the lowest unset bit.


#### Remarks
Like Cell_GetLowestBit, but for 0s not 1s.


#### Depends on
* [`YSI_g_scDeBruijn1`](#YSI_g_scDeBruijn1)
#### Estimated stack usage
1 cells



### `Cell_GetLowestBlankEx`:

Cell_GetLowestBlankEx(number);



#### Syntax


```pawn
Cell_GetLowestBlankEx(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest unset bit of PLUS ONE.	 |

#### Returns
The integer position of the lowest unset bit PLUS ONE.


#### Remarks
Like Cell_GetLowestBitEx, but for 0s not 1s.


#### Depends on
* [`YSI_g_scDeBruijn2`](#YSI_g_scDeBruijn2)
#### Estimated stack usage
1 cells



### `Cell_GetLowestComponent`:

Cell_GetLowestComponent(number);



#### Syntax


```pawn
Cell_GetLowestComponent(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest 1 in.	 |

#### Returns
The lowest set bit.


#### Remarks
Similar to Cell_GetLowestBit, but returns the bit, not the position of the bit. 1) Example: 0b00000000000000000000000000000001 Returns: 0b00000000000000000000000000000001 2) Example: 0b00000000000000000000000000001000 Returns: 0b00000000000000000000000000001000 3) Example: 0b00010001100011000011100010001000 Returns: 0b00000000000000000000000000001000 4) Example: 0b00000000000000000000000000000000 Returns: 0b00000000000000000000000000000000


#### Estimated stack usage
1 cells



### `Cell_GetLowestEmpty`:

Cell_GetLowestEmpty(number);



#### Syntax


```pawn
Cell_GetLowestEmpty(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest 0 in.	 |

#### Returns
The lowest unset bit.


#### Remarks
Like Cell_GetLowestComponent, but for 0s not 1s.


#### Estimated stack usage
1 cells



### `Cell_HasSpaceByte`:

Cell_HasSpaceByte(number);



#### Syntax


```pawn
Cell_HasSpaceByte(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest space in.	 |

#### Returns
The lowest space byte.


#### Remarks
Check if any of the 4 bytes are a space: https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/


#### Depends on
* [`YSI_g_c80s`](#YSI_g_c80s)
* [`YSI_g_cFEs`](#YSI_g_cFEs)
#### Estimated stack usage
1 cells



### `Cell_HasZeroByte`:

Cell_HasZeroByte(number);



#### Syntax


```pawn
Cell_HasZeroByte(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to get the lowest 0 in.	 |

#### Returns
The lowest null byte.


#### Remarks
Check if any of the 4 bytes are zero: https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/


#### Depends on
* [`YSI_g_c20s`](#YSI_g_c20s)
* [`YSI_g_c80s`](#YSI_g_c80s)
* [`YSI_g_cFEs`](#YSI_g_cFEs)
#### Estimated stack usage
1 cells



### `Cell_PrecomputeMaskPermutation`:

Cell_PrecomputeMaskPermutation(m)



#### Syntax


```pawn
Cell_PrecomputeMaskPermutation(m)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`m`	 | 	The mask.	 |

#### Returns
Five precomputed constants to help expand or contract this mask.


#### Remarks
The full maths for generalised expansion and contraction is quite complex; however, much of the inner loop relies only on the mask and not on the value being manipulated. Given this we can do a lot of work in advance, say outside a loop, to avoid repeated calculations.


#### Depends on
* [`Cell_PrecomputeMaskPermutation`](#Cell_PrecomputeMaskPermutation)
#### Estimated stack usage
10 cells



### `Cell_ReverseBits`:

Cell_ReverseBits(number);



#### Syntax


```pawn
Cell_ReverseBits(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to manipulate.	 |

#### Returns
All the bits in the input reversed.


#### Remarks
1) Example: 0b11110000000000000000000000000000 Becomes: 0b00000000000000000000000000001111 2) Example: 0b10110011100011110000111110000010 Becomes: 0b01000001111100001111000111001101 3) Example: 0b01010101010101010101010101010101 Becomes: 0b10101010101010101010101010101010


#### Depends on
* [`swapchars`](#swapchars)
#### Estimated stack usage
1 cells



### `Cell_ReverseBytes`:

Cell_ReverseBytes(number);



#### Syntax


```pawn
Cell_ReverseBytes(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to manipulate.	 |

#### Returns
All the bytes in the input reversed.


#### Remarks
1) Example: 0x12345678 Becomes: 0x78563412 2) Example: 0x01020304 Becomes: 0x04030201 3) Example: 0xFF00FF00 Becomes: 0x00FF00FF


#### Attributes
* `native`

### `Cell_ReverseNibbles`:

Cell_ReverseNibbles(number);



#### Syntax


```pawn
Cell_ReverseNibbles(data)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} ` The number to manipulate.	 |

#### Returns
All the nibbles (4-bit chunks) in the input reversed.


#### Remarks
1) Example: 0x12345678 Becomes: 0x87654321 2) Example: 0x010F0703 Becomes: 0x3070F010 3) Example: 0xF0F0F0F0 Becomes: 0x0F0F0F0F


#### Depends on
* [`swapchars`](#swapchars)
#### Estimated stack usage
1 cells


