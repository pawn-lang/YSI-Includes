y_utils - misc - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `Android_OnAndroidTimer`:


#### Syntax


```pawn
Android_OnAndroidTimer(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player to mess up.	 |
| 	`old`	 | 	Unused.	 |

#### Remarks
Timer for applying random effects.


#### Depends on
* [`Utils_ChaosMod`](#Utils_ChaosMod)
#### Attributes
* `public`
#### Estimated stack usage
4 cells



### `Utils_ChaosMod`:


#### Syntax


```pawn
Utils_ChaosMod(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player to mess up.	 |

#### Remarks
Make some random effects on the player. Inspired by the single player chaos mod.


#### Depends on
* [`FIXES_GetPlayerInterior`](#FIXES_GetPlayerInterior)
* [`FIXES_SetPlayerArmedWeapon`](#FIXES_SetPlayerArmedWeapon)
* [`FIXES_SetPlayerInterior`](#FIXES_SetPlayerInterior)
* [`FIXES_SetPlayerWorldBounds`](#FIXES_SetPlayerWorldBounds)
* [`FIXES_random`](#FIXES_random)
* [`GetPlayerVehicleID`](#GetPlayerVehicleID)
* [`LinkVehicleToInterior`](#LinkVehicleToInterior)
* [`SetPlayerHealth`](#SetPlayerHealth)
* [`SetPlayerVelocity`](#SetPlayerVelocity)
* [`SetVehicleHealth`](#SetVehicleHealth)
* [`SetVehicleVelocity`](#SetVehicleVelocity)
#### Estimated stack usage
9 cells



### `VALID_PLAYERID`:


#### Syntax


```pawn
VALID_PLAYERID(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	The player to check.	 |

#### Tag
`bool:`


#### Returns
Is this a valid playerid (NOT, is the player connected).


#### Attributes
* `native`




__________________________________________


y_utils - maths - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `Abs`:

Abs(number);



#### Syntax


```pawn
Abs(number)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`number`	 | 	The number to get the absolute value of.	 |

#### Returns
The absolute value of a number.


#### Remarks
Get the absolute value of a number.


#### Depends on
* [`y_utils_abs_shift`](#y_utils_abs_shift)
#### Estimated stack usage
1 cells



### `FloatAbs`:

Float:FloatAbs(Float:number);



#### Syntax


```pawn
FloatAbs(value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	`Float `	 |
| 	`number`	 | 	The number to get the absolute value of.	 |

#### Tag
`Float:`


#### Returns
The absolute value of a number.


#### Remarks
Get the absolute value of a number. Easy in IEEE754, just remove the MSB.


#### Attributes
* `native`

### `IS_IN_RANGE`:


#### Syntax


```pawn
IS_IN_RANGE(value, lower, upper)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	The number to compare.	 |
| 	`lower`	 | 	The lower limit.	 |
| 	`upper`	 | 	The upper limit.	 |

#### Tag
`bool:`


#### Returns
Is the value in the given range.


#### Remarks
Equivalent to:

```pawn
		(%1) <= (%0) < (%2)
```


#### Attributes
* `native`

### `IsEven`:


#### Syntax


```pawn
IsEven(value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	Value to check if is even.	 |

#### Tag
`bool:`


#### Attributes
* `native`

### `IsNaN`:


#### Syntax


```pawn
IsNaN(value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	`Float ` The IEEE754 floating point number (`Float:`) to check.	 |

#### Tag
`bool:`


#### Returns
An IEEE754 floating-point number is defined as Not-A-Number when all the exponent bits are set, and the mantissa is non-zero. The sign bit is ignored, so we first remove that and test the result is `> 0x7F800000`. Because any signed number bigger than that must have all the MSBs set, plus at least one more.


#### Attributes
* `native`

### `IsOdd`:


#### Syntax


```pawn
IsOdd(value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	Value to check if is odd.	 |

#### Tag
`bool:`


#### Attributes
* `native`

### `Mean`:


#### Syntax


```pawn
Mean(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array whose values need averaging.	 |
| 	`num`	 | 	The size of the array.	 |

#### Returns
The mathematical mean value of the array.


#### Depends on
* [`Sum`](#Sum)
#### Estimated stack usage
5 cells



### `Median`:


#### Syntax


```pawn
Median(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array whose values need averaging.	 |
| 	`num`	 | 	The size of the array.	 |

#### Returns
The mathematical median value of the array.


#### Remarks
Must sort the array first.


#### Depends on
* [`QuickSort`](#QuickSort)
#### Estimated stack usage
5 cells



### `Mode`:


#### Syntax


```pawn
Mode(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array whose values need averaging.	 |
| 	`num`	 | 	The size of the array.	 |

#### Returns
The mathematical modal value of the array.


#### Remarks
Must sort the array first.


#### Depends on
* [`QuickSort`](#QuickSort)
#### Estimated stack usage
6 cells



### `NOT_IN_RANGE`:


#### Syntax


```pawn
NOT_IN_RANGE(value, lower, upper)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	The number to compare.	 |
| 	`lower`	 | 	The lower limit.	 |
| 	`upper`	 | 	The upper limit.	 |

#### Tag
`bool:`


#### Returns
Is the value outside the given range.


#### Remarks
Equivalent to:

```pawn
		(%1) <= (%0) < (%2)
```


#### Attributes
* `native`

### `Range`:


#### Syntax


```pawn
Range(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array whose values need averaging.	 |
| 	`num`	 | 	The size of the array.	 |

#### Returns
The mathematical range of the values of the array.


#### Depends on
* [`cellmax`](#cellmax)
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `Sum`:


#### Syntax


```pawn
Sum(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array whose values need summing.	 |
| 	`num`	 | 	The size of the array.	 |

#### Returns
All the values in the array added together.


#### Estimated stack usage
2 cells



### `TryPPM`:

TryPPM(ppm);



#### Syntax


```pawn
TryPPM(ppm)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ppm`	 | 	The likelihood of returning `true`.	 |

#### Tag
`bool:`


#### Returns
`true`, `ppm%oooo` of the time; or `false`


#### Remarks
Basically a ppm random number generator (that's out of 1000000). Could be used to replicate something with a `1.0001%` chance of happening via:
`TryPPM(10001)`


#### Depends on
* [`FIXES_random`](#FIXES_random)
#### Estimated stack usage
4 cells



### `TryPercentage`:

TryPercentage(percentage);



#### Syntax


```pawn
TryPercentage(percentage)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`percentage`	 | 	The likelihood of returning `true`.	 |

#### Tag
`bool:`


#### Returns
`true`, `percentage%` of the time; or `false`


#### Remarks
Basically a percentage random number generator.


#### Depends on
* [`FIXES_random`](#FIXES_random)
#### Estimated stack usage
4 cells



### `TryPermille`:

TryPermille(permille);



#### Syntax


```pawn
TryPermille(permille)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`permille`	 | 	The likelihood of returning `true`.	 |

#### Tag
`bool:`


#### Returns
`true`, `permille%o` of the time; or `false`


#### Remarks
Basically a permille random number generator (that's out of 1000). Could be used to replicate something with a `42.1%` chance of happening via:
`TryPermille(421)`


#### Depends on
* [`FIXES_random`](#FIXES_random)
#### Estimated stack usage
4 cells



### `UCMP`:


#### Syntax


```pawn
UCMP(value, upper)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`value`	 | 	The unsigned number to compare.	 |
| 	`upper`	 | 	The upper limit.	 |

#### Tag
`bool:`


#### Returns
An unsigned comparison between the two values.


#### Attributes
* `native`

### `ceildiv`:


#### Syntax


```pawn
ceildiv(numerator, denominator)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`numerator`	 | 	The top of the division.	 |
| 	`denominator`	 | 	The bottom of the division.	 |

#### Returns
(numerator / denominator) rounded up.


#### Remarks
Normal integer division ALWAYS rounds down - this always rounds up.


#### Attributes
* `native`

### `floordiv`:

floordiv(numerator, denominator);



#### Syntax


```pawn
floordiv(numerator, denominator)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`numerator`	 | 	The top of the division.	 |
| 	`denominator`	 | 	The bottom of the division.	 |

#### Returns
(numerator / denominator) rounded down.


#### Remarks
Normal integer division ALWAYS rounds down - this also always rounds down, making it a little pointless, but also more explicit in function.


#### Attributes
* `native`








__________________________________________


y_utils - varargs - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `PrintArg`:


#### Syntax


```pawn
PrintArg(n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 	The numeric parameter position to print.	 |

#### Returns
Prints a string passed as a vararg to the calling function.


#### Depends on
* [`__1_cell`](#__1_cell)
* [`__2_cells`](#__2_cells)
* [`__3_cells`](#__3_cells)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__frame_offset`](#__frame_offset)
* [`print`](#print)
#### Estimated stack usage
1 cells



### `ReturnStringArg`:


#### Syntax


```pawn
ReturnStringArg(idx)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`idx`	 | 	Index of the string in the parameters.	 |

#### Returns
string


#### Remarks
Is passed the result of getarg, which will be the address of a string (in theory) and uses that for DMA to get the string.


#### Depends on
* [`ReturnStringArg`](#ReturnStringArg)
* [`__3_cells`](#__3_cells)
* [`__4_cells`](#__4_cells)
* [`__param0_offset`](#__param0_offset)
* [`__param1_offset`](#__param1_offset)
* [`cellbytes`](#cellbytes)
* [`strcat`](#strcat)
#### Estimated stack usage
145 cells



### `va_getstring`:


#### Syntax


```pawn
va_getstring(dest[], arg, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Where to write the string to.	 |
| 	`arg`	 | 	Index of the string in the parameters.	 |
| 	`len`	 | 	The length of the destination address.	 |

#### Remarks
Like `getarg` but for strings. Theoretically just a loop over `getarg`, but we can do better with `strcat`.


#### Depends on
* [`__3_cells`](#__3_cells)
* [`__4_cells`](#__4_cells)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__frame_offset`](#__frame_offset)
* [`strcat`](#strcat)
#### Estimated stack usage
1 cells



### `va_strlen`:


#### Syntax


```pawn
va_strlen(arg)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arg`	 | 	Index of the string in the parameters.	 |

#### Returns
String length.


#### Remarks
Gets the length of a string passed to variable arguments, using the parameter index as in `getarg`.


#### Depends on
* [`__1_cell`](#__1_cell)
* [`__2_cells`](#__2_cells)
* [`__3_cells`](#__3_cells)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`strlen`](#strlen)
#### Estimated stack usage
1 cells










__________________________________________


y_utils - arrays - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `MemCmp`:


#### Syntax


```pawn
MemCmp(arr1[], arr2[], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr1`	 | 	` [] ` First array to compare.	 |
| 	`arr2`	 | 	` [] ` Second array to compare.	 |
| 	`count`	 | 	How many cells to compare.	 |

#### Returns
The difference (0 if the same).


#### Remarks
Returns the first found difference between two arrays. If they are the same the return value is `0`, otherwise it is `arr1[i] - arr2[i]`.


#### Estimated stack usage
3 cells



### `MemSet`:


#### Syntax


```pawn
MemSet(arr[], value, size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` Array or address to set to a value.	 |
| 	`value`	 | 	What to set the cells to.	 |
| 	`size`	 | 	Number of cells to fill.	 |

#### Remarks
Based on [ code by Slice](http://forum.sa-mp.com/showthread.php?p=1606781#post1606781), modified to use binary flags instead of a loop. "MemSet" takes an array, the size of the array, and a value to fill it with and sets the whole array to that value. "rawmemset" is similar, but takes an AMX data segment address instead and the size is in bytes, not cells. However, the size must still be a multiple of 4.


#### Depends on
* [`RawMemSet`](#RawMemSet)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
7 cells



### `QuickSort`:


#### Syntax


```pawn
QuickSort(arr[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array to sort.	 |
| 	`num`	 | 	The size of the array.	 |

#### Remarks
Sorts the array in place. Uses quick sort because it is relatively simple and pretty "quick".


#### Depends on
* [`Utils_QuickSort`](#Utils_QuickSort)
#### Estimated stack usage
6 cells



### `RawMemCpy_`:


#### Syntax


```pawn
RawMemCpy_(dest, src, index, numbytes, maxlength)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	Destination address.	 |
| 	`src`	 | 	Source data.	 |
| 	`index`	 | 		 |
| 	`numbytes`	 | 	Number of bytes to copy.	 |
| 	`maxlength`	 | 		 |

#### Remarks
Like memcpy, but takes addresses instead of arrays. Also far less secure because it doesn't check the destination size - it just assumes it is large enough.


#### Attributes
* `native`

### `RawMemSet`:


#### Syntax


```pawn
RawMemSet(address, value, size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`address`	 | 	Array or address to set to a value.	 |
| 	`value`	 | 	What to set the cells to.	 |
| 	`size`	 | 	Number of bytes to fill.	 |

#### Remarks
Based on code by Slice: [http://forum.sa-mp.com/showthread.php?p=1606781#post1606781](http://forum.sa-mp.com/showthread.php?p=1606781#post1606781) Modified to use binary flags instead of a loop. "MemSet" takes an array, the size of the array, and a value to fill it with and sets the whole array to that value. "RawMemSet" is similar, but takes an AMX data segment address instead and the size is in bytes, not cells. However, the size must still be a multiple of 4.


#### Depends on
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
1 cells



### `Utils_QuickSort`:


#### Syntax


```pawn
Utils_QuickSort(arr[], low, high)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` The array to sort.	 |
| 	`low`	 | 	The lowest index to sort.	 |
| 	`high`	 | 	The highest index (inclusive) to sort.	 |

#### Remarks
Internal recursive call for quicksorting.


#### Estimated stack usage
8 cells



### `memcmp`:


#### Syntax


```pawn
memcmp(arr1[], arr2[], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr1`	 | 	` [] ` First array to compare.	 |
| 	`arr2`	 | 	` [] ` Second array to compare.	 |
| 	`count`	 | 	How many cells to compare.	 |

#### Returns
The difference (0 if the same).


#### Remarks
Returns the first found difference between two arrays. If they are the same the return value is `0`, otherwise it is `arr1[i] - arr2[i]`.


#### Depends on
* [`MemCmp`](#MemCmp)
#### Estimated stack usage
6 cells



### `memset`:


#### Syntax


```pawn
memset(arr[], val, size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] ` Array or address to set to a value.	 |
| 	`val`	 | 		 |
| 	`size`	 | 	Number of cells to fill.	 |
| 	`value`	 | 	What to set the cells to.	 |

#### Remarks
Based on [ code by Slice](http://forum.sa-mp.com/showthread.php?p=1606781#post1606781), modified to use binary flags instead of a loop. "MemSet" takes an array, the size of the array, and a value to fill it with and sets the whole array to that value. "rawmemset" is similar, but takes an AMX data segment address instead and the size is in bytes, not cells. However, the size must still be a multiple of 4.


#### Depends on
* [`RawMemSet`](#RawMemSet)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
7 cells



### `rawMemcpy`:


#### Syntax


```pawn
rawMemcpy(dest, src, numbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	Destination address.	 |
| 	`src`	 | 	Source data.	 |
| 	`numbytes`	 | 	Number of bytes to copy.	 |

#### Remarks
Like memcpy, but takes addresses instead of arrays. Also far less secure because it doesn't check the destination size - it just assumes it is large enough.


#### Depends on
* [`RawMemCpy_`](#RawMemCpy_)
* [`cellmax`](#cellmax)
#### Estimated stack usage
7 cells



### `rawMemset`:


#### Syntax


```pawn
rawMemset(address, value, size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`address`	 | 	Array or address to set to a value.	 |
| 	`value`	 | 	What to set the cells to.	 |
| 	`size`	 | 	Number of bytes to fill.	 |

#### Remarks
Based on code by Slice: [http://forum.sa-mp.com/showthread.php?p=1606781#post1606781](http://forum.sa-mp.com/showthread.php?p=1606781#post1606781) Modified to use binary flags instead of a loop. "MemSet" takes an array, the size of the array, and a value to fill it with and sets the whole array to that value. "RawMemSet" is similar, but takes an AMX data segment address instead and the size is in bytes, not cells. However, the size must still be a multiple of 4.


#### Depends on
* [`RawMemSet`](#RawMemSet)
#### Estimated stack usage
6 cells










__________________________________________


y_utils - colour - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `CIEMultiply`:


#### Syntax


```pawn
CIEMultiply(r, g, b, &x, &y, &z)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`r`	 | 	`Float ` The red colour component.	 |
| 	`g`	 | 	`Float ` The green colour component.	 |
| 	`b`	 | 	`Float ` The blue colour component.	 |
| 	`x`	 | 	`Float & ` The x return value.	 |
| 	`y`	 | 	`Float & ` The y return value.	 |
| 	`z`	 | 	`Float & ` The z return value.	 |

#### Remarks
Performs one step of the sRGB to CIE colour space conversion process. See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)


#### Depends on
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
#### Estimated stack usage
1 cells



### `CIEToSRGB`:

SRGBToCIE(colour, &Float:x, &Float:y, &Float:z);



#### Syntax


```pawn
CIEToSRGB(a, x, y, z)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	The alpha to add on.	 |
| 	`x`	 | 	`Float ` The x return value.	 |
| 	`y`	 | 	`Float ` The y return value.	 |
| 	`z`	 | 	`Float ` The z return value.	 |

#### Remarks
Converts a colour from CIE XYZ colour space to sRGB colour space. See: https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<=(Float:,Float:)`](#operator<=(Float:,Float:))
* [`floatpower`](#floatpower)
* [`floatround`](#floatround)
#### Estimated stack usage
10 cells



### `GetNearestColourGamma`:

GetNearestColourGamma(colour, const options[], count = sizeof (options));



#### Syntax


```pawn
GetNearestColourGamma(colour, options[], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The RGB(A) colour to restrict.	 |
| 	`options`	 | 	` [] ` The list of valid RGB(A) colour options.	 |
| 	`count`	 | 	The size of the options array.	 |

#### Returns
The INDEX of the nearst colour. Or `-1` for errors.


#### Remarks
Find the closest colour to the given colour from the array. Uses gamma colour space for slightly more accuracy.


#### Depends on
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`floatpower`](#floatpower)
#### Estimated stack usage
13 cells



### `GetNearestColourGammaCached`:

GetNearestColourGammaCached(colour, const options[], count = sizeof (options));



#### Syntax


```pawn
GetNearestColourGammaCached(colour, options[][], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The RGB(A) colour to restrict.	 |
| 	`options`	 | 	`Float [][3] ` The list of valid gamma colour options.	 |
| 	`count`	 | 	The size of the options array.	 |

#### Returns
The INDEX of the nearst colour. Or `-1` for errors.


#### Remarks
Find the closest colour to the given colour from the array. Uses gamma colour space for slightly more accuracy. Options are in gamma format.


#### Depends on
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`floatpower`](#floatpower)
#### Estimated stack usage
10 cells



### `GetNearestColourLinear`:

GetNearestColourLinear(colour, const options[], count = sizeof (options));



#### Syntax


```pawn
GetNearestColourLinear(colour, options[], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The RGB(A) colour to restrict.	 |
| 	`options`	 | 	` [] ` The list of valid RGB(A) colour options.	 |
| 	`count`	 | 	The size of the options array.	 |

#### Returns
The INDEX of the nearst colour. Or `-1` for errors.


#### Remarks
Find the closest colour to the given colour from the array. Uses RGB colour space for the distance function, which is not very accurate.


#### Depends on
* [`cellmax`](#cellmax)
#### Estimated stack usage
10 cells



### `GetNearestColourSRGB`:

GetNearestColourGamma(colour, const options[], count = sizeof (options));



#### Syntax


```pawn
GetNearestColourSRGB(colour, options[], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The RGB(A) colour to restrict.	 |
| 	`options`	 | 	` [] ` The list of valid RGB(A) colour options.	 |
| 	`count`	 | 	The size of the options array.	 |

#### Returns
The INDEX of the nearst colour. Or `-1` for errors.


#### Remarks
Find the closest colour to the given colour from the array. Uses SRGB colour space for the most accuracy.


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`SRGBToCIE`](#SRGBToCIE)
#### Estimated stack usage
16 cells



### `GetNearestColourSRGBCached`:

GetNearestColourSRGBCached(colour, const options[], count = sizeof (options));



#### Syntax


```pawn
GetNearestColourSRGBCached(colour, options[][], count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The RGB(A) colour to restrict.	 |
| 	`options`	 | 	`Float [][3] ` The list of valid SRGB colour options.	 |
| 	`count`	 | 	The size of the options array.	 |

#### Returns
The INDEX of the nearst colour. Or `-1` for errors.


#### Remarks
Find the closest colour to the given colour from the array. Uses SRGB colour space for the most accuracy. Options are in SRGB format.


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`SRGBToCIE`](#SRGBToCIE)
#### Estimated stack usage
16 cells



### `InterpolateColor`:


#### Syntax


```pawn
InterpolateColor(startColour, endColour, value, maxvalue, minvalue)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`value`	 | 		 |
| 	`maxvalue`	 | 		 |
| 	`minvalue`	 | 		 |
| 	`fraction`	 | 	How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs linear interpolation between the colours, which isn't usually the best way wrt human vision, but is fast. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`Float:operator=(_:)`](#Float:operator=(_:))
* [`InterpolateColourLinear`](#InterpolateColourLinear)
* [`floatdiv`](#floatdiv)
#### Estimated stack usage
6 cells



### `InterpolateColorGamma`:


#### Syntax


```pawn
InterpolateColorGamma(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs gamma interpolation between the colours, which is a good balance between complexity and perception. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`Debug_Print0`](#Debug_Print0)
* [`InterpolateColourGamma`](#InterpolateColourGamma)
#### Estimated stack usage
6 cells



### `InterpolateColorLinear`:


#### Syntax


```pawn
InterpolateColorLinear(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs linear interpolation between the colours, which isn't usually the best way wrt human vision, but is fast. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`Float:operator=(_:)`](#Float:operator=(_:))
* [`Debug_Print0`](#Debug_Print0)
* [`InterpolateColourLinear`](#InterpolateColourLinear)
#### Estimated stack usage
8 cells



### `InterpolateColorSRGB`:


#### Syntax


```pawn
InterpolateColorSRGB(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs full sRGB colour space interpolation, which is more exact even than gamma interpolation, but also a lot slower. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`Debug_Print0`](#Debug_Print0)
* [`InterpolateColourSRGB`](#InterpolateColourSRGB)
#### Estimated stack usage
6 cells



### `InterpolateColour`:


#### Syntax


```pawn
InterpolateColour(startColour, endColour, value, maxvalue, minvalue)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`value`	 | 		 |
| 	`maxvalue`	 | 		 |
| 	`minvalue`	 | 		 |
| 	`fraction`	 | 	How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs linear interpolation between the colours, which isn't usually the best way wrt human vision, but is fast. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`Float:operator=(_:)`](#Float:operator=(_:))
* [`InterpolateColourLinear`](#InterpolateColourLinear)
* [`floatdiv`](#floatdiv)
#### Estimated stack usage
6 cells



### `InterpolateColourGamma`:

InterpolateColourGamma(startColour, endColour, Float:fraction);



#### Syntax


```pawn
InterpolateColourGamma(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs gamma interpolation between the colours, which is a good balance between complexity and perception. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator>=(Float:,Float:)`](#operator>=(Float:,Float:))
* [`operator<=(Float:,Float:)`](#operator<=(Float:,Float:))
* [`floatpower`](#floatpower)
* [`floatround`](#floatround)
#### Estimated stack usage
14 cells



### `InterpolateColourLinear`:

InterpolateColourLinear(startColour, endColour, Float:fraction);



#### Syntax


```pawn
InterpolateColourLinear(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs linear interpolation between the colours, which isn't usually the best way wrt human vision, but is fast. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator>=(Float:,Float:)`](#operator>=(Float:,Float:))
* [`operator<=(Float:,Float:)`](#operator<=(Float:,Float:))
* [`floatround`](#floatround)
#### Estimated stack usage
9 cells



### `InterpolateColourSRGB`:

InterpolateColourSRGB(startColour, endColour, Float:fraction);



#### Syntax


```pawn
InterpolateColourSRGB(startColour, endColour, fraction)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`startColour`	 | 	One of the two colours.	 |
| 	`endColour`	 | 	The other of the two colours.	 |
| 	`fraction`	 | 	`Float ` How far to interpolate between the colours.	 |

#### Remarks
This function takes a value (fraction) which is a distance between the two endpoints as a fraction. This fraction is applied to the two colours given to find a third colour at some point between those two colours. This function performs full sRGB colour space interpolation, which is more exact even than gamma interpolation, but also a lot slower. The fraction is optional, and uses the second colour's alpha for blending if not given.


#### Depends on
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator>=(Float:,Float:)`](#operator>=(Float:,Float:))
* [`operator<=(Float:,Float:)`](#operator<=(Float:,Float:))
* [`CIEToSRGB`](#CIEToSRGB)
* [`SRGBToCIE`](#SRGBToCIE)
* [`floatround`](#floatround)
#### Estimated stack usage
14 cells



### `SRGBToCIE`:

SRGBToCIE(colour, &Float:x, &Float:y, &Float:z);



#### Syntax


```pawn
SRGBToCIE(colour, &x, &y, &z)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`colour`	 | 	The sRGB colour to convert.	 |
| 	`x`	 | 	`Float & ` The x return value.	 |
| 	`y`	 | 	`Float & ` The y return value.	 |
| 	`z`	 | 	`Float & ` The z return value.	 |

#### Remarks
Converts a colour from sRGB colour space to CIE XYZ colour space. See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)


#### Depends on
* [`operator+(Float:,_:)`](#operator+(Float:,_:))
* [`operator/(_:,Float:)`](#operator/(_:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`floatpower`](#floatpower)
#### Estimated stack usage
10 cells










__________________________________________


y_utils - conversions - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `BinStr`:


#### Syntax


```pawn
BinStr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to try convert to a boolean.	 |

#### Returns
bool: passed boolean.


#### Remarks
This takes a value in 0110101 (boolean) format and returns it as a regular value.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
#### Estimated stack usage
4 cells



### `BoolStr`:


#### Syntax


```pawn
BoolStr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to try convert to a boolean.	 |

#### Tag
`bool:`


#### Returns
bool: passed boolean.


#### Remarks
This can take a number of ways of representing booleans - 0, false and nothing there. Anything not one of those things (false is not case sensitive) is assumed true.


#### Depends on
* [`FIXES_strcmp`](#FIXES_strcmp)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `HexStr`:


#### Syntax


```pawn
HexStr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to convert to a number.	 |

#### Returns
value of the passed hex string.


#### Remarks
Now stops on invalid characters.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
#### Estimated stack usage
7 cells



### `IsHex`:


#### Syntax


```pawn
IsHex(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to check.	 |

#### Tag
`bool:`


#### Returns
true/false.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
#### Estimated stack usage
6 cells



### `binstr`:


#### Syntax


```pawn
binstr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to try convert to a boolean.	 |

#### Returns
bool: passed boolean.


#### Remarks
This takes a value in 0110101 (boolean) format and returns it as a regular value.


#### Depends on
* [`BinStr`](#BinStr)
#### Estimated stack usage
4 cells



### `boolstr`:


#### Syntax


```pawn
boolstr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to try convert to a boolean.	 |

#### Tag
`bool:`


#### Returns
bool: passed boolean.


#### Remarks
This can take a number of ways of representing booleans - 0, false and nothing there. Anything not one of those things (false is not case sensitive) is assumed true.


#### Depends on
* [`BoolStr`](#BoolStr)
#### Estimated stack usage
4 cells



### `hexstr`:


#### Syntax


```pawn
hexstr(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	String to convert to a number.	 |

#### Returns
value of the passed hex string.


#### Remarks
Now stops on invalid characters.


#### Depends on
* [`HexStr`](#HexStr)
#### Estimated stack usage
4 cells



### `ishex`:


#### Syntax


```pawn
ishex(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to check.	 |

#### Tag
`bool:`


#### Returns
true/false.


#### Depends on
* [`IsHex`](#IsHex)
#### Estimated stack usage
4 cells










__________________________________________


y_utils - encodings - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `Base64Decode`:

Base64Decode



#### Syntax


```pawn
Base64Decode(dest[], src[], len, offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] `	 |
| 	`src`	 | 	` [] `	 |
| 	`len`	 | 		 |
| 	`offset`	 | 		 |

#### Remarks
Decodes data using proper base64.


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__m1_cells`](#__m1_cells)
* [`min`](#min)
* [`strlen`](#strlen)
#### Estimated stack usage
4 cells



### `BernsteinHash`:


#### Syntax


```pawn
BernsteinHash(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	the string to hash.	 |

#### Returns
The bernstein hash of the input string


#### Remarks
This is a 32bit hash system so is not very secure, however we're only using this as a string enumerator to uniquely identify strings easilly and allow for a binary search of strings based on the hash of their name. *crc32*, then *jenkins* were originally used however this is far faster, if a little collision prone, but we're checking the strings manually anyway. This doesn't matter as it would be done regardless of hash method, so this doesn't need to be accounted for. Speed is all that matters with at least least a bit of non collision (the number of strings we're dealing with, this should have none-to-few collisions).



I modified it slightly from the original code pasted by aru, to code closer to [the code](http://www.burtleburtle.net/bob/hash/doobs.html) and to work with PAWN (and shaved 0.2us off the time for one call :D).


Uber reduced version (just for fun):
```pawn
  b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}  
```



Update: Contrary to what I said above this is also used to identify colour strings for the updated text system involving file based styling and this is not checked for collisions as it's unimportant. But this doesn't affect the function at all, I just mentioned it here for "interest".

#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellbits`](#cellbits)
#### Estimated stack usage
7 cells



### `JenkinsHash`:


#### Syntax


```pawn
JenkinsHash(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` the string to hash.	 |

#### Returns
the Jenkins hash of the input string


#### Remarks
This is a 32bit hash system so is not very secure, however we're only using this as a string enumerator to uniquely identify strings easilly and allow for a binary search of strings based on the hash of their name.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
#### Estimated stack usage
4 cells



### `bernstein`:


#### Syntax


```pawn
bernstein(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] `	 |
| 	`string`	 | 	the string to hash.	 |

#### Returns
The bernstein hash of the input string


#### Remarks
This is a 32bit hash system so is not very secure, however we're only using this as a string enumerator to uniquely identify strings easilly and allow for a binary search of strings based on the hash of their name. *crc32*, then *jenkins* were originally used however this is far faster, if a little collision prone, but we're checking the strings manually anyway. This doesn't matter as it would be done regardless of hash method, so this doesn't need to be accounted for. Speed is all that matters with at least least a bit of non collision (the number of strings we're dealing with, this should have none-to-few collisions).



I modified it slightly from the original code pasted by aru, to code closer to [the code](http://www.burtleburtle.net/bob/hash/doobs.html) and to work with PAWN (and shaved 0.2us off the time for one call :D).


Uber reduced version (just for fun):
```pawn
  b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}  
```



Update: Contrary to what I said above this is also used to identify colour strings for the updated text system involving file based styling and this is not checked for collisions as it's unimportant. But this doesn't affect the function at all, I just mentioned it here for "interest".

#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellbits`](#cellbits)
#### Estimated stack usage
7 cells










__________________________________________


y_utils - strings - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `ChrFind`:


#### Syntax


```pawn
ChrFind(needle, haystack[], start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`needle`	 | 	The character to find.	 |
| 	`haystack`	 | 	` [] ` The string to find it in.	 |
| 	`start`	 | 	The offset to start from.	 |

#### Returns
Fail - -1, Success - pos


#### Depends on
* [`FIXES_strfind`](#FIXES_strfind)
* [`false`](#false)
#### Estimated stack usage
9 cells



### `EndOfLine`:


#### Syntax


```pawn
EndOfLine(line[], pos)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`line`	 | 	` [] ` String to check.	 |
| 	`pos`	 | 	Postion to start from.	 |

#### Tag
`bool:`


#### Remarks
Checks if the current point in a line is the end of non-whitespace data.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`strlen`](#strlen)
#### Estimated stack usage
4 cells



### `IsNull`:


#### Syntax


```pawn
IsNull(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to check if is null.	 |

#### Tag
`bool:`


#### Remarks
Uses a new shorter and branchless method, which also works with offsets so this is valid:

```pawn
  new str[32]; IsNull(str[5]);  
```


#### Attributes
* `native`

### `SkipWhitespace`:


#### Syntax


```pawn
SkipWhitespace(str[], pos)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to skip over part of.	 |
| 	`pos`	 | 	The start of the whitespace.	 |

#### Returns
The end of the whitespace.


#### Remarks
Doesn't skip over NULL terminators.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `StrCpy`:


#### Syntax


```pawn
StrCpy(dest[], src[], len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Destination string.	 |
| 	`src`	 | 	` [] ` Source string.	 |
| 	`len`	 | 	(Implicit) maximum length of the destination.	 |

#### Attributes
* `native`

### `StrToLower`:


#### Syntax


```pawn
StrToLower(str[], len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to convert.	 |
| 	`len`	 | 	How much of the string to convert.	 |

#### Depends on
* [`FIXES_tolower`](#FIXES_tolower)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
#### Estimated stack usage
6 cells



### `StrToUpper`:


#### Syntax


```pawn
StrToUpper(str[], len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to convert.	 |
| 	`len`	 | 	How much of the string to convert.	 |

#### Depends on
* [`FIXES_toupper`](#FIXES_toupper)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
#### Estimated stack usage
6 cells



### `Strip`:


#### Syntax


```pawn
Strip(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to remove whitespace from the start and end of.	 |

#### Depends on
* [`FIXES_memcpy`](#FIXES_memcpy)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`strlen`](#strlen)
#### Estimated stack usage
10 cells



### `StripL`:


#### Syntax


```pawn
StripL(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to remove whitespace from the start of.	 |

#### Depends on
* [`FIXES_memcpy`](#FIXES_memcpy)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`strlen`](#strlen)
#### Estimated stack usage
10 cells



### `StripNL`:


#### Syntax


```pawn
StripNL(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to remove whitespace from the end of.	 |

#### Remarks
Updated from old versions, should be more efficient


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`strlen`](#strlen)
#### Estimated stack usage
5 cells



### `StripR`:


#### Syntax


```pawn
StripR(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to remove whitespace from the end of.	 |

#### Remarks
Updated from old versions, should be more efficient


#### Attributes
* `native`

### `Trim`:


#### Syntax


```pawn
Trim(str[], &start, &end)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The string to trim.	 |
| 	`start`	 | 	` & ` Start of the substring.	 |
| 	`end`	 | 	` & ` End of the substring.	 |

#### Remarks
Modifies "start" and "end" to be tight on text in "str". `Strip` removes the characters from the end, so needs a modifiable string, this just tells you where the ends are.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `Unpack`:


#### Syntax


```pawn
Unpack(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to unpack	 |

#### Returns
unpacked string


#### Remarks
Mainly used for debugging.


#### Depends on
* [`Unpack`](#Unpack)
* [`strlen`](#strlen)
* [`strunpack`](#strunpack)
#### Estimated stack usage
149 cells



### `ValstrWithOrdinal`:


#### Syntax


```pawn
ValstrWithOrdinal(n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 	The number to convert to a string with ordinal.	 |

#### Returns
Stringises a number, then adds `st/nd/rd/th`.


#### Depends on
* [`FIXES_valstr`](#FIXES_valstr)
* [`ValstrWithOrdinal`](#ValstrWithOrdinal)
* [`strcat`](#strcat)
#### Estimated stack usage
38 cells



### `chrfind`:


#### Syntax


```pawn
chrfind(needle, haystack[], start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`needle`	 | 	The character to find.	 |
| 	`haystack`	 | 	` [] ` The string to find it in.	 |
| 	`start`	 | 	The offset to start from.	 |

#### Returns
Fail - -1, Success - pos


#### Depends on
* [`ChrFind`](#ChrFind)
#### Estimated stack usage
6 cells



### `chrfindp`:


#### Syntax


```pawn
chrfindp(needle, haystack[], start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`needle`	 | 	The character to find.	 |
| 	`haystack`	 | 	` [] ` The string to find it in.	 |
| 	`start`	 | 	The offset to start from.	 |

#### Returns
Fail - -1, Success - pos


#### Remarks
Like [`ChrFind`](#ChrFind), but with no upper-bounds check on start. Now it has them anyway...


#### Depends on
* [`ChrFind`](#ChrFind)
#### Estimated stack usage
6 cells



### `endofline`:


#### Syntax


```pawn
endofline(line[], pos)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`line`	 | 	` [] ` String to check.	 |
| 	`pos`	 | 	Postion to start from.	 |

#### Tag
`bool:`


#### Remarks
Checks if the current point in a line is the end of non-whitespace data.


#### Depends on
* [`EndOfLine`](#EndOfLine)
#### Estimated stack usage
5 cells



### `unpack`:


#### Syntax


```pawn
unpack(str[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` String to unpack	 |

#### Returns
unpacked string


#### Remarks
Mainly used for debugging.


#### Depends on
* [`strlen`](#strlen)
* [`strunpack`](#strunpack)
* [`unpack`](#unpack)
#### Estimated stack usage
149 cells










__________________________________________


y_utils - files - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `Files_Copy`:


#### Syntax


```pawn
Files_Copy(src[], dst[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`src`	 | 	` [] ` The name of the input file.	 |
| 	`dst`	 | 	` [] ` The name of the output file.	 |

#### Tag
`bool:`


#### Remarks
Copies a file from `src` to `dst`.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_flength`](#FIXES_flength)
* [`Files_CopyRange`](#Files_CopyRange)
* [`I@`](#I@)
* [`false`](#false)
* [`fopen`](#fopen)
* [`io_read`](#io_read)
#### Estimated stack usage
7 cells



### `Files_CopyRange`:


#### Syntax


```pawn
Files_CopyRange(i, end, dst[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`i`	 | 	`File ` Handle to the file to copy.	 |
| 	`end`	 | 	How much of the file to copy.	 |
| 	`dst`	 | 	` [] ` The name of the output file.	 |

#### Tag
`bool:`


#### Remarks
Copy part of a file from the current read pointer, for `end` bytes.


#### Depends on
* [`FIXES_fblockread`](#FIXES_fblockread)
* [`FIXES_fblockwrite`](#FIXES_fblockwrite)
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_fputchar`](#FIXES_fputchar)
* [`YSI_gUnsafeHugeString`](#YSI_gUnsafeHugeString)
* [`YSI_gUnsafeHugeString`](#YSI_gUnsafeHugeString)
* [`_YSI_FGetChar__`](#_YSI_FGetChar__)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
* [`fopen`](#fopen)
* [`io_write`](#io_write)
* [`min`](#min)
#### Estimated stack usage
8 cells



### `Files_DoCopy`:


#### Syntax


```pawn
Files_DoCopy(i, dst[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`i`	 | 	`File ` Handle to the file to copy.	 |
| 	`dst`	 | 	` [] ` The name of the output file.	 |

#### Tag
`bool:`


#### Remarks
Fast file copy routine. Surprisingly widely used in YSI, in places where temp files were used and `fseek`ed to the start. Closes the file.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_flength`](#FIXES_flength)
* [`FIXES_fseek`](#FIXES_fseek)
* [`Files_CopyRange`](#Files_CopyRange)
* [`I@`](#I@)
* [`seek_start`](#seek_start)
#### Estimated stack usage
6 cells



### `Files_Move`:


#### Syntax


```pawn
Files_Move(src[], dst[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`src`	 | 	` [] ` The name of the input file.	 |
| 	`dst`	 | 	` [] ` The name of the output file.	 |

#### Tag
`bool:`


#### Remarks
Moves a file from `src` to `dst`.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_flength`](#FIXES_flength)
* [`Files_CopyRange`](#Files_CopyRange)
* [`I@`](#I@)
* [`false`](#false)
* [`fopen`](#fopen)
* [`fremove`](#fremove)
* [`io_read`](#io_read)
#### Estimated stack usage
7 cells



### `GetYSIScriptfilesDir`:


#### Syntax


```pawn
GetYSIScriptfilesDir(dir)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dir`	 | 	`E_YSI_DIR ` The ID of the directory.	 |

#### Returns
A directory.


#### Remarks
Get a YSI scriptfiles directory, or a fallback.


#### Depends on
* [`GetYSIScriptfilesDir`](#GetYSIScriptfilesDir)
* [`YSI_gsDefaultDirs`](#YSI_gsDefaultDirs)
#### Estimated stack usage
1 cells



### `ResolveYSIScriptfileDirs`:


#### Syntax


```pawn
ResolveYSIScriptfileDirs()
```

#### Remarks
Check if all the YSI scriptfiles directories exist. Checks for `.gitkeep` in each folder, then each folder without `YSI/` prefix, then just nothing.


#### Depends on
* [`E_YSI_DIR`](#E_YSI_DIR)
* [`FIXES_fclose`](#FIXES_fclose)
* [`Server_FinishIntroPart`](#Server_FinishIntroPart)
* [`Server_PrintIntroPart`](#Server_PrintIntroPart)
* [`YSI_EMPTY`](#YSI_EMPTY)
* [`YSI_gsDefaultDirs`](#YSI_gsDefaultDirs)
* [`YSI_gsDefaultDirs`](#YSI_gsDefaultDirs)
* [`false`](#false)
* [`fopen`](#fopen)
* [`io_write`](#io_write)
* [`strcat`](#strcat)
* [`true`](#true)
#### Estimated stack usage
66 cells



### `fautocleanup`:


#### Syntax


```pawn
fautocleanup(name[], maxAge)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 	` [] ` File to clean up.	 |
| 	`maxAge`	 | 	Maximum temporary file age.	 |

#### Tag
`bool:`


#### Remarks
Add a file to the temporary cleanup list.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_format`](#FIXES_format)
* [`FIXES_fwrite`](#FIXES_fwrite)
* [`YSI_TEMP_FILE_NAME`](#YSI_TEMP_FILE_NAME)
* [`false`](#false)
* [`fexist`](#fexist)
* [`fopen`](#fopen)
* [`gettime`](#gettime)
* [`io_append`](#io_append)
* [`true`](#true)
#### Estimated stack usage
77 cells



### `ftemp_`:


#### Syntax


```pawn
ftemp_()
```

#### Tag
`File:`


#### Remarks
Call the original `ftemp`.


#### Attributes
* `native`

### `ftemporary`:


#### Syntax


```pawn
ftemporary(ret[], ext[], len, maxAge)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ret`	 | 	` [] ` Storage for the return value.	 |
| 	`ext`	 | 	` [] ` Extension.	 |
| 	`len`	 | 	Maximum string length.	 |
| 	`maxAge`	 | 	Maximum temporary file age.	 |

#### Tag
`File:`


#### Remarks
Generate a random temporary filename and open it. Also redefines `ftemp` to call this function instead if called with extra parameters.


#### Depends on
* [`E_YSI_DIR_TEMP`](#E_YSI_DIR_TEMP)
* [`GetYSIScriptfilesDir`](#GetYSIScriptfilesDir)
* [`fautocleanup`](#fautocleanup)
* [`ftemporary_`](#ftemporary_)
* [`strcat`](#strcat)
#### Estimated stack usage
40 cells



### `ftemporary_`:


#### Syntax


```pawn
ftemporary_(name[], ext[], path[], len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 	` [] ` Storage for the return value.	 |
| 	`ext`	 | 	` [] ` Extension.	 |
| 	`path`	 | 	` [] ` Directory in which to place temporary files.	 |
| 	`len`	 | 	Maximum string length.	 |

#### Tag
`File:`


#### Remarks
Internal detail for `ftemporary`. Should not be called directly.


#### Depends on
* [`FIXES_random`](#FIXES_random)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`fexist`](#fexist)
* [`fopen`](#fopen)
* [`io_readwrite`](#io_readwrite)
* [`strcat`](#strcat)
* [`strlen`](#strlen)
#### Estimated stack usage
7 cells



### `ftouch`:

ftouch(filename);



#### Syntax


```pawn
ftouch(filename[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`filename`	 | 	` [] ` The file to "touch".	 |

#### Returns
0 - File already exists. 1 - File was created. -1 - File was not created.


#### Remarks
This "touches" a file in the Unix sense of creating it but not opening or editing it in any way.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`fexist`](#fexist)
* [`fopen`](#fopen)
* [`io_write`](#io_write)
#### Estimated stack usage
5 cells










__________________________________________


y_utils - ip - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `CensorDottedIP`:


#### Syntax


```pawn
CensorDottedIP(dest[], ip[], parts, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Destination string.	 |
| 	`ip`	 | 	` [] ` Input IP address in dotted notation.	 |
| 	`parts`	 | 	How many parts of the IP to keep.	 |
| 	`len`	 | 	Maximum length of the destination.	 |

#### Tag
`bool:`


#### Returns
`true` if the censoring worked, `false` if the input wasn't a valid IP, or `parts` was invalid.


#### Remarks
Replaces some parts of an IP with stars (`*`) to hide the full thing. There are four components in a dotted IP, so the number of stars returned is `4 - parts`. For example `CensorIP(dest, "192.168.0.1", 3);` will return `"192.168.0.*"`.


#### Depends on
* [`CensorIntIP`](#CensorIntIP)
* [`DottedToIntIP`](#DottedToIntIP)
* [`false`](#false)
#### Estimated stack usage
8 cells



### `CensorIntIP`:


#### Syntax


```pawn
CensorIntIP(dest[], ip, parts, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Destination string.	 |
| 	`ip`	 | 	The IP to censor, as a 32-bit int.	 |
| 	`parts`	 | 	How many parts of the IP to keep.	 |
| 	`len`	 | 	Maximum length of the destination.	 |

#### Tag
`bool:`


#### Returns
`false` if `parts` was invalid, otherwise `true`.


#### Remarks
Replaces some parts of an IP with stars (`*`) to hide the full thing. There are four components in a dotted IP, so the number of stars returned is `4 - parts`. For example `CensorIntIP(dest, 0xC0A80001, 3);` may return `"192.168.0.*"`.


#### Depends on
* [`FIXES_format`](#FIXES_format)
* [`false`](#false)
* [`strcat`](#strcat)
* [`true`](#true)
#### Estimated stack usage
13 cells



### `CensorPlayerIP`:


#### Syntax


```pawn
CensorPlayerIP(dest[], playerid, parts, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Destination string.	 |
| 	`playerid`	 | 	The player whose IP will be used.	 |
| 	`parts`	 | 	How many parts of the IP to keep.	 |
| 	`len`	 | 	Maximum length of the destination.	 |

#### Tag
`bool:`


#### Returns
`true` if the censoring worked, `false` if the input wasn't a valid IP.


#### Remarks
Replaces some parts of an IP with stars (`*`) to hide the full thing. There are four components in a dotted IP, so the number of stars returned is `4 - parts`. For example `CensorPlayerIP(dest, playerid, 3);` may return `"192.168.0.*"`.


#### Depends on
* [`CensorIntIP`](#CensorIntIP)
* [`YSI_gPlayerIP`](#YSI_gPlayerIP)
* [`cellmin`](#cellmin)
* [`false`](#false)
#### Estimated stack usage
6 cells



### `DottedToIntIP`:


#### Syntax


```pawn
DottedToIntIP(ip[], &out)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ip`	 | 	` [] ` Dot notation IP to convert to an integer.	 |
| 	`out`	 | 	` & ` Destination.	 |

#### Tag
`bool:`


#### Returns
`true` if the conversion worked, `false` if the input didn't start with a valid IP.


#### Remarks
Converts an IP from a string, such as `192.168.0.1`, converted to a 32-bit integer, such as `0xC0A80001`. Does far more checks on the input than the older `IPToInt`, but that function isn't deprecated for use in situations where the input format is know, such as directly after a call to `GetPlayerIp`.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
5 cells



### `GetIP`:


#### Syntax


```pawn
GetIP(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player to get IP of.	 |

#### Returns
IP as a 32bit int.


#### Attributes
* `native`

### `IPToInt`:


#### Syntax


```pawn
IPToInt(ip[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ip`	 | 	` [] ` Dot notation IP to convert to an integer.	 |

#### Returns
The IP.


#### Remarks
Converts an IP from a string, such as `192.168.0.1`, converted to a 32-bit integer, such as `0xC0A80001`. Does far fewer checks on the input than the newer `DottedToIntIP`, but this function isn't deprecated for use in situations where the input format is know, such as directly after a call to `GetPlayerIp`.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`strval`](#strval)
#### Estimated stack usage
6 cells



### `IntToIP`:


#### Syntax


```pawn
IntToIP(dest[], ip, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [] ` Where to render the dotted notation IP.	 |
| 	`ip`	 | 	Integer IP version.	 |
| 	`len`	 | 	Size of the destination string.	 |

#### Depends on
* [`FIXES_format`](#FIXES_format)
#### Estimated stack usage
13 cells






__________________________________________


y_utils - names - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `GetPlayerRPComponents`:

GetPlayerRPComponents



#### Syntax


```pawn
GetPlayerRPComponents(playerid, names[][], components, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player whose name you want to get.	 |
| 	`names`	 | 	` [][] `	 |
| 	`components`	 | 		 |
| 	`len`	 | 		 |

#### Returns
The number of parts extracted from the name.


#### Remarks
Get a player's name, split in to parts by `_`.


#### Depends on
* [`FIXES_GetPlayerName`](#FIXES_GetPlayerName)
* [`FIXES_strfind`](#FIXES_strfind)
* [`false`](#false)
* [`strlen`](#strlen)
* [`strmid`](#strmid)
#### Estimated stack usage
35 cells



### `GetPlayerRPName`:

GetPlayerRPName



#### Syntax


```pawn
GetPlayerRPName(playerid, name[], len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player whose name you want to get.	 |
| 	`name`	 | 	` [] `	 |
| 	`len`	 | 		 |

#### Tag
`bool:`


#### Remarks
Get a player's name, with `_` replaced by ` `.


#### Depends on
* [`FIXES_GetPlayerName`](#FIXES_GetPlayerName)
* [`FIXES_strfind`](#FIXES_strfind)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `HasRPName`:

HasRPName



#### Syntax


```pawn
HasRPName(playerid, casing, longNames)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player whose name you want to test.	 |
| 	`casing`	 | 	`bool ` Check for string casing? I.e. allow `James` but not `james`.	 |
| 	`longNames`	 | 	`bool ` Allow more than two name parts?	 |

#### Tag
`bool:`


#### Remarks
Is this player's name in the form `First_Last`?


#### Depends on
* [`FIXES_GetPlayerName`](#FIXES_GetPlayerName)
* [`IsRPName`](#IsRPName)
#### Estimated stack usage
31 cells



### `IsRPName`:

IsRPName



#### Syntax


```pawn
IsRPName(name[], casing, longNames)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 	` [] ` The name to test.	 |
| 	`casing`	 | 	`bool ` Check for string casing? I.e. allow `James` but not `james`.	 |
| 	`longNames`	 | 	`bool ` Allow more than two name parts?	 |

#### Tag
`bool:`


#### Remarks
Is this name in the form `First_Last`?


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
4 cells



### `ReturnPlayerName`:

ReturnPlayerName



#### Syntax


```pawn
ReturnPlayerName(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player whose name you want to get.	 |

#### Remarks
Get a player's name.


#### Depends on
* [`FIXES_GetPlayerName`](#FIXES_GetPlayerName)
* [`ReturnPlayerName`](#ReturnPlayerName)
#### Estimated stack usage
29 cells



### `ReturnPlayerRPName`:

ReturnPlayerRPName



#### Syntax


```pawn
ReturnPlayerRPName(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player whose name you want to get.	 |

#### Remarks
Get a player's name, with `_` replaced by ` `.


#### Depends on
* [`GetPlayerRPName`](#GetPlayerRPName)
* [`ReturnPlayerRPName`](#ReturnPlayerRPName)
#### Estimated stack usage
30 cells










__________________________________________


y_utils - random - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `Random`:


#### Syntax


```pawn
Random(minOrMax, max, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`minOrMax`	 | 	Upper bound, or lower bound with 2+ parameters or when less than naught.	 |
| 	`max`	 | 	Upper bound.	 |
| 	`...`	 | 		 |
| 	``	 | 	Value(s) to not return.	 |

#### Remarks
Generate a random number between the given numbers (min <= n < max). Default minimum is 0 (changes the parameter order). This uses a compile- time macro to detect the number of parameters and adjust the implementation accordingly. Also when there is only one parameter and it is below naught, it uses naught as the max and the parameter as the min instead. Won't return the value `except` if it is between the limits. So can be called with one, two, or three parameters. Don't try `Random(0, _, 2);` for example, it won't work. With more than two parameters all the rest are numbers that should not be returned.


#### Estimated stack usage
1 cells



### `RandomFloatMax`:


#### Syntax


```pawn
RandomFloatMax(max)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`max`	 | 	`Float ` Upper bound.	 |

#### Tag
`Float:`


#### Remarks
Generate a random float between `0 <= n < max`.


#### Depends on
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`FIXES_random`](#FIXES_random)
* [`float`](#float)
* [`floatround`](#floatround)
#### Estimated stack usage
4 cells



### `RandomFloatMinMax`:


#### Syntax


```pawn
RandomFloatMinMax(min, max, dp)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`min`	 | 	`Float ` Lower bound, or upper bound when only parameter.	 |
| 	`max`	 | 	`Float ` Upper bound.	 |
| 	`dp`	 | 	How small to make the differences	 |

#### Tag
`Float:`


#### Remarks
Generate a random float between the given numbers (min <= n < max). Default minimum is 0.0 (changes the parameter order).


#### Depends on
* [`operator-(Float:)`](#operator-(Float:))
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator/(Float:,Float:)`](#operator/(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`Debug_Print0`](#Debug_Print0)
* [`FIXES_random`](#FIXES_random)
* [`float`](#float)
* [`floatpower`](#floatpower)
* [`floatround`](#floatround)
#### Estimated stack usage
4 cells



### `RandomMax`:


#### Syntax


```pawn
RandomMax(max)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`max`	 | 	Upper bound.	 |

#### Remarks
Generate a random number between the given numbers (min <= n < max). Default minimum is 0 (changes the parameter order). This uses a compile- time macro to detect the number of parameters and adjust the implementation accordingly. Also when there is only one parameter and it is below naught, it uses naught as the max and the parameter as the min instead.


#### Depends on
* [`YSI_Random__`](#YSI_Random__)
#### Estimated stack usage
3 cells



### `RandomMinMax`:


#### Syntax


```pawn
RandomMinMax(min, max)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`min`	 | 	Lower bound.	 |
| 	`max`	 | 	Upper bound.	 |

#### Remarks
Generate a random number between the given numbers (min <= n < max).


#### Depends on
* [`YSI_Random__`](#YSI_Random__)
#### Estimated stack usage
3 cells



### `RandomMinMaxExcept`:


#### Syntax


```pawn
RandomMinMaxExcept(min, max, except)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`min`	 | 	Lower bound.	 |
| 	`max`	 | 	Upper bound.	 |
| 	`except`	 | 	Value to not return.	 |

#### Remarks
Generate a random number between the given numbers (min <= n < max). Won't return the value `except` if it is between the limits.


#### Depends on
* [`YSI_Random__`](#YSI_Random__)
#### Estimated stack usage
3 cells



### `RandomMinMaxExceptMany`:


#### Syntax


```pawn
RandomMinMaxExceptMany(min, max, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`min`	 | 	Lower bound.	 |
| 	`max`	 | 	Upper bound.	 |
| 	`...`	 | 	Values to not return.	 |

#### Remarks
Generate a random number between the given numbers (min <= n < max). Default minimum is 0 (changes the parameter order). Won't return any of the extra parameter values, so you can do:

```pawn
  Random(0, 20, 11, 12, 13);  
```

To randomly select `0-10, 14-19` (inclusive).

#### Depends on
* [`YSI_Random__`](#YSI_Random__)
* [`getarg`](#getarg)
* [`numargs`](#numargs)
#### Estimated stack usage
7 cells



### `RandomMulberry32`:


#### Syntax


```pawn
RandomMulberry32()
```

#### Remarks
Relatively high quality 32-bit PRNG.


#### Estimated stack usage
1 cells



### `RandomMulberry32__`:


#### Syntax


```pawn
RandomMulberry32__()
```

#### Remarks
Relatively high quality 32-bit PRNG.


#### Estimated stack usage
1 cells



### `RandomPointInCircleCentred`:

Get a random point in a circle.



#### Syntax


```pawn
RandomPointInCircleCentred(centreX, centreY, radius, outX, outY)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`outX`	 | 	`Float ` The return for the random x co-ordinate.	 |
| 	`outY`	 | 	`Float ` The return for the random y co-ordinate.	 |

#### Remarks
Medium method. Generate an angle and distance. Fixed loop bounds, but worst distribution (although actually the best distribution if you want more near the centre, as in an explosion).


#### Depends on
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`RandomFloatMax`](#RandomFloatMax)
* [`degrees`](#degrees)
* [`floatsin`](#floatsin)
#### Estimated stack usage
6 cells



### `RandomPointInCircleDistributed`:

Get a random point in a circle.



#### Syntax


```pawn
RandomPointInCircleDistributed(centreX, centreY, radius, outX, outY)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`outX`	 | 	`Float ` The return for the random x co-ordinate.	 |
| 	`outY`	 | 	`Float ` The return for the random y co-ordinate.	 |

#### Remarks
Best method. Generate an angle and distance, but adjusted for a perfect distribution of points throughout the circle. Fixed loop bounds.


#### Depends on
* [`operator*(Float:,_:)`](#operator*(Float:,_:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`RandomFloatMax`](#RandomFloatMax)
* [`degrees`](#degrees)
* [`floatsin`](#floatsin)
* [`floatsqrt`](#floatsqrt)
#### Estimated stack usage
6 cells



### `RandomPointInCircleSampled`:

Get a random point in a circle.



#### Syntax


```pawn
RandomPointInCircleSampled(centreX, centreY, radius, outX, outY)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`outX`	 | 	`Float ` The return for the random x co-ordinate.	 |
| 	`outY`	 | 	`Float ` The return for the random y co-ordinate.	 |

#### Remarks
Most basic method. Generate points in a square and test them. Simple but unbounded. Good distribution.


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`RandomFloatMinMax`](#RandomFloatMinMax)
* [`VectorSize`](#VectorSize)
#### Estimated stack usage
10 cells



### `RandomPointsInCircleCentred`:

Get an array of random points in a circle.



#### Syntax


```pawn
RandomPointsInCircleCentred(centreX, centreY, radius, xs[], ys[], sx, sy)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`xs`	 | 	`Float [] ` The return array for the random x co-ordinates.	 |
| 	`ys`	 | 	`Float [] ` The return array for the random y co-ordinates.	 |
| 	`sx`	 | 	The size of the x return array (must match `sy`.	 |
| 	`sy`	 | 	The size of the y return array (must match `sx`.	 |

#### Remarks
Medium method. Generate an angle and distance. Fixed loop bounds, but worst distribution (although actually the best distribution if you want more near the centre, as in an explosion).


#### Depends on
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`RandomFloatMax`](#RandomFloatMax)
* [`degrees`](#degrees)
* [`floatsin`](#floatsin)
#### Estimated stack usage
6 cells



### `RandomPointsInCircleDistributed`:

Get an array of random points in a circle.



#### Syntax


```pawn
RandomPointsInCircleDistributed(centreX, centreY, radius, xs[], ys[], sx, sy)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`xs`	 | 	`Float [] ` The return array for the random x co-ordinates.	 |
| 	`ys`	 | 	`Float [] ` The return array for the random y co-ordinates.	 |
| 	`sx`	 | 	The size of the x return array (must match `sy`.	 |
| 	`sy`	 | 	The size of the y return array (must match `sx`.	 |

#### Remarks
Best method. Generate an angle and distance, but adjusted for a perfect distribution of points throughout the circle. Fixed loop bounds.


#### Depends on
* [`operator*(Float:,_:)`](#operator*(Float:,_:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`RandomFloatMax`](#RandomFloatMax)
* [`degrees`](#degrees)
* [`floatsin`](#floatsin)
* [`floatsqrt`](#floatsqrt)
#### Estimated stack usage
6 cells



### `RandomPointsInCircleSampled`:

Get an array of random points in a circle.



#### Syntax


```pawn
RandomPointsInCircleSampled(centreX, centreY, radius, xs[], ys[], sx, sy)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`centreX`	 | 	`Float ` The x co-ordinate of the centre of the circle.	 |
| 	`centreY`	 | 	`Float ` The y co-ordinate of the centre of the circle.	 |
| 	`radius`	 | 	`Float ` The size (radius) of the circle.	 |
| 	`xs`	 | 	`Float [] ` The return array for the random x co-ordinates.	 |
| 	`ys`	 | 	`Float [] ` The return array for the random y co-ordinates.	 |
| 	`sx`	 | 	The size of the x return array (must match `sy`.	 |
| 	`sy`	 | 	The size of the y return array (must match `sx`.	 |

#### Remarks
Most basic method. Generate points in a square and test them. Simple but unbounded. Good distribution.


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator+(Float:,Float:)`](#operator+(Float:,Float:))
* [`operator<(Float:,Float:)`](#operator<(Float:,Float:))
* [`RandomFloatMinMax`](#RandomFloatMinMax)
* [`VectorSize`](#VectorSize)
#### Estimated stack usage
12 cells



### `RandomSplitMix32`:


#### Syntax


```pawn
RandomSplitMix32()
```

#### Remarks
Slightly lower quality 32-bit PRNG.


#### Estimated stack usage
1 cells



### `RandomSplitMix32__`:


#### Syntax


```pawn
RandomSplitMix32__()
```

#### Remarks
Slightly lower quality 32-bit PRNG.


#### Estimated stack usage
1 cells










__________________________________________


y_utils - similarity - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `BiGramSimilarity`:

BiGramSimilarity(const string1[], const string2[]);



#### Syntax


```pawn
BiGramSimilarity(string1[], string2[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`string1`	 | 	` [] ` The first string to compare.	 |
| 	`string2`	 | 	` [] `	 |
| 	`string1`	 | 	The second string to compare.	 |

#### Tag
`Float:`


#### Returns
The normalised similarity between the strings (`0.0 - 1.0`).


#### Remarks
Compares the pairs of letters and numbers in each string with each other to find a measure of how much of one ordered string is in the other. Useful for seeing if two strings are similar to humans. This is nothing like the more common *Levenshtein Distance*, which pretty much compares strings at an ASCII character level, so two very different strings can be apparently more similar than two others. A good example of this, which was the motivation for writing this function, was in *sscanf*. When checking to see what vehicle a player wrote, the input `NRG` would return `TUG` as the closest match. Why? Because they're both three letters and share the last `G`, so mechanically they are only two transformations apart; whereas `NRG-400` needs four transforms to get to from the input. So this code looks at how much of each string is in the other string. Very little of `TUG` is in `NRG` and vice-versa, while all of `NRG` is in `NRG-400` and a lot of the reverse is true. This entirely ignores case, spaces, and punctuation in the comparisons.


#### Depends on
* [`operator-(Float:,Float:)`](#operator-(Float:,Float:))
* [`operator*(Float:,Float:)`](#operator*(Float:,Float:))
* [`Float:operator=(_:)`](#Float:operator=(_:))
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`floatdiv`](#floatdiv)
#### Estimated stack usage
1306 cells



### `DoLevenshteinDistance`:


#### Syntax


```pawn
DoLevenshteinDistance(a[], lenA, b[], lenB, matrix[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	` [] ` First string to compare.	 |
| 	`lenA`	 | 	Length of the first string.	 |
| 	`b`	 | 	` [] ` Second string to compare.	 |
| 	`lenB`	 | 	Length of the second string.	 |
| 	`matrix`	 | 	` [] ` Storage for the calculations.	 |

#### Returns
The levenshtein difference (0 if the same).


#### Remarks
This function is the internal implementation of a Levenshtein distance when neither string is packed. The `matrix` parameter is rewritten at the start of the function to a larger block of memory, but is still passed in so that the rest of the generated code is correct in terms of lookups.


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__hea`](#__hea)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `DoLevenshteinDistancePackA`:


#### Syntax


```pawn
DoLevenshteinDistancePackA(a[], lenA, b[], lenB, matrix[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	` [] ` First string to compare.	 |
| 	`lenA`	 | 	Length of the first string.	 |
| 	`b`	 | 	` [] ` Second string to compare.	 |
| 	`lenB`	 | 	Length of the second string.	 |
| 	`matrix`	 | 	` [] ` Storage for the calculations.	 |

#### Returns
The levenshtein difference (0 if the same).


#### Remarks
This function is the internal implementation of a Levenshtein distance when the shorter string is packed. The `matrix` parameter is rewritten at the start of the function to a larger block of memory, but is still passed in so that the rest of the generated code is correct in terms of lookups.


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__hea`](#__hea)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `DoLevenshteinDistancePackAB`:


#### Syntax


```pawn
DoLevenshteinDistancePackAB(a[], lenA, b[], lenB, matrix[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	` [] ` First string to compare.	 |
| 	`lenA`	 | 	Length of the first string.	 |
| 	`b`	 | 	` [] ` Second string to compare.	 |
| 	`lenB`	 | 	Length of the second string.	 |
| 	`matrix`	 | 	` [] ` Storage for the calculations.	 |

#### Returns
The levenshtein difference (0 if the same).


#### Remarks
This function is the internal implementation of a Levenshtein distance when both strings are packed. The `matrix` parameter is rewritten at the start of the function to a larger block of memory, but is still passed in so that the rest of the generated code is correct in terms of lookups.


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__hea`](#__hea)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `DoLevenshteinDistancePackB`:


#### Syntax


```pawn
DoLevenshteinDistancePackB(a[], lenA, b[], lenB, matrix[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	` [] ` First string to compare.	 |
| 	`lenA`	 | 	Length of the first string.	 |
| 	`b`	 | 	` [] ` Second string to compare.	 |
| 	`lenB`	 | 	Length of the second string.	 |
| 	`matrix`	 | 	` [] ` Storage for the calculations.	 |

#### Returns
The levenshtein difference (0 if the same).


#### Remarks
This function is the internal implementation of a Levenshtein distance when th elongest stringis packed. The `matrix` parameter is rewritten at the start of the function to a larger block of memory, but is still passed in so that the rest of the generated code is correct in terms of lookups.


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__hea`](#__hea)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `LevenshteinDistance`:


#### Syntax


```pawn
LevenshteinDistance(stringA[], stringB[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`stringA`	 | 	` [] ` First string to compare.	 |
| 	`stringB`	 | 	` [] ` Second string to compare.	 |

#### Returns
The levenshtein difference (0 if the same).


#### Remarks
The levenshtein difference is a measure of the difference between two strings, given as the number of operations required to change one string in to the other one. A lower number means that the strings are more similar, with `0` meaning that they are identical. Either string can be packed, and this function now has no upper limit on the size of strings that can be compared, as long as they can fit in the heap.


#### Depends on
* [`DoLevenshteinDistance`](#DoLevenshteinDistance)
* [`DoLevenshteinDistancePackA`](#DoLevenshteinDistancePackA)
* [`DoLevenshteinDistancePackAB`](#DoLevenshteinDistancePackAB)
* [`DoLevenshteinDistancePackB`](#DoLevenshteinDistancePackB)
* [`FIXES_strcmp`](#FIXES_strcmp)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`strlen`](#strlen)
#### Estimated stack usage
11 cells










__________________________________________


y_utils - textwrap - v0.1.3
==========================================
Misc functions used throughout.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `IterativeColouredSkipSPacked`:


#### Syntax


```pawn
IterativeColouredSkipSPacked(text[], start, &colour)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] `	 |
| 	`start`	 | 		 |
| 	`colour`	 | 	` & `	 |

#### Remarks
Internal implementation.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `IterativeColouredSkipSUnpacked`:


#### Syntax


```pawn
IterativeColouredSkipSUnpacked(text[], start, &colour)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] `	 |
| 	`start`	 | 		 |
| 	`colour`	 | 	` & `	 |

#### Remarks
Internal implementation.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `IterativeColouredSkipWPacked`:


#### Syntax


```pawn
IterativeColouredSkipWPacked(text[], lastIndex, start, &hyphen, &colour, useHyphen)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] `	 |
| 	`lastIndex`	 | 		 |
| 	`start`	 | 		 |
| 	`hyphen`	 | 	`bool & `	 |
| 	`colour`	 | 	` & `	 |
| 	`useHyphen`	 | 	`bool `	 |

#### Remarks
Internal implementation.


#### Depends on
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
9 cells



### `IterativeColouredSkipWUnpacked`:


#### Syntax


```pawn
IterativeColouredSkipWUnpacked(text[], lastIndex, start, &hyphen, &colour, useHyphen)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] `	 |
| 	`lastIndex`	 | 		 |
| 	`start`	 | 		 |
| 	`hyphen`	 | 	`bool & `	 |
| 	`colour`	 | 	` & `	 |
| 	`useHyphen`	 | 	`bool `	 |

#### Remarks
Internal implementation.


#### Depends on
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
9 cells



### `IterativeColouredTextSplitter`:

bool:IterativeColouredTextSplitter(const text[], width, start, &end, &next, &bool:hyphen)



#### Syntax


```pawn
IterativeColouredTextSplitter(text[], width, start, &end, &next, &hyphen, &colour, useHyphen)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] ` The input string to split up.	 |
| 	`width`	 | 	The maximum size of the output (including hyphen).	 |
| 	`start`	 | 	Where in the string to start the next line.	 |
| 	`end`	 | 	` & ` The index to end the current line at (excluding hyphen).	 |
| 	`next`	 | 	` & ` The index to start the next line from (skips trailing spaces).	 |
| 	`hyphen`	 | 	`bool & ` Should a hyphen be inserted in to the output?	 |
| 	`colour`	 | 	` & ` The colour for the start of the next line.	 |
| 	`useHyphen`	 | 	`bool ` May a hyphen be included?	 |

#### Tag
`bool:`


#### Returns
Does the function need to be called again to show another line?


#### Remarks
Split some text in to multiple lines. With sensible breaks at spaces or mid-word if they're long enough. Unlike `IterativeTextSplitter` it will never split in the middle of `{RRGGBB}` colour sequences, and can ignore them for many checks.


#### Depends on
* [`IterativeColouredSkipSPacked`](#IterativeColouredSkipSPacked)
* [`IterativeColouredSkipSUnpacked`](#IterativeColouredSkipSUnpacked)
* [`IterativeColouredSkipWPacked`](#IterativeColouredSkipWPacked)
* [`IterativeColouredSkipWUnpacked`](#IterativeColouredSkipWUnpacked)
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
10 cells



### `IterativeTextSplitter`:

bool:IterativeTextSplitter(const text[], width, start, &end, &next, &bool:hyphen)



#### Syntax


```pawn
IterativeTextSplitter(text[], width, start, &end, &next, &hyphen, useHyphen)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`text`	 | 	` [] ` The input string to split up.	 |
| 	`width`	 | 	The maximum size of the output (including hyphen).	 |
| 	`start`	 | 	Where in the string to start the next line.	 |
| 	`end`	 | 	` & ` The index to end the current line at (excluding hyphen).	 |
| 	`next`	 | 	` & ` The index to start the next line from (skips trailing spaces).	 |
| 	`hyphen`	 | 	`bool & ` Should a hyphen be inserted in to the output?	 |
| 	`useHyphen`	 | 	`bool ` May a hyphen be included?	 |

#### Tag
`bool:`


#### Returns
Does the function need to be called again to show another line?


#### Remarks
Split some text in to multiple lines. With sensible breaks at spaces or mid-word if they're long enough.


#### Depends on
* [`YSI_IsLocalVarPackedString__`](#YSI_IsLocalVarPackedString__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
6 cells


