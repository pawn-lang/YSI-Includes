y_iterate - v0.4
==========================================
(c) 2022 YSI contibutors, licensed under MPL 1.1


Provides efficient looping through sparse data sets, such as connected players. Significantly improved from the original version to be a generic loop system, rather then purely a player loop system. When used for players this has constant time O(n) for number of connected players (n), unlike standard player loops which are O(MAX_PLAYERS), regardless of the actual number of connected players. Even when n is MAX_PLAYERS this is still faster.

For extensive documentation on writing and using iterators, see [this topic](http://forum.sa-mp.com/showthread.php?t=481877)

##  Examples
### Basic Iterators

Basic iterators are simply collections of numbers - little more than an array. A number is either in the array, or not in the array, *y_iterate* loops through only the *in* numbers.

*Players*

This code will loop through every player connected to the server.
```pawn
  foreach (new i : Player)																				
  {																				
      printf("player %d is connected", i);																				
  }  
```



*Vehicles*

This code will loop through all the created vehicles on the server (including those made in other running scripts).
```pawn
  foreach (new vid : Vehicle)																				
  {																				
      printf("vehicleid %d has been created", vid);																				
  }  
```



*Create An Iterator*

To create your own iterator, first declare it, then add things to it, then loop over it:
```pawn
  new																				
      Iterator:MyIter<100>; // First declare it (this has room for 100 items numbered 0-99).									 											
  // Then add things to it.																				
  Iter_Add(MyIter, 0);  // Fine.																				
  Iter_Add(MyIter, 55); // Fine.																				
  Iter_Add(MyIter, 100); // Will fail.																				
  // Then loop over it.																				
  foreach (new i : MyIter)																				
  {																				
      printf("%d", i); // Will print "0" then "55".																				
  }  
```




## Variables


### `F@o`:


### `Iterator@Fib`:

#### Tag
`F@z:`


#### Remarks

Returns every number in the Fibonacci sequence that can be stored in a PAWN cell.

```pawn
    foreach (new i : Fib())         
  {                               
      // 0, 1, 1, 2, 3, 5, etc... 
  }  
```



### `Iterator@Filter`:

#### Tag
`F@z:`


#### Remarks

Loop over all the indexes of this array which contain the given value.

```pawn
  new array[] = { ... };             
  foreach (new i : Filter(5, array)) 
  {                                  
  }  
```



### `Iterator@N`:

#### Tag
`F@z:`


#### Remarks

Loop until the given target is reached.

```pawn
    foreach (new i : N(6))  
  {                       
      // 0, 1, 2, 3, 4, 5 
  }  
```

This is equivalent to:
```pawn
  for (new i = 0; i != 6; ++i) 
  {                            
  }  
```



### `Iterator@NonNull`:

#### Tag
`F@z:`


#### Remarks

Loop over all the indexes of this array that are not zero.

```pawn
  new array[] = { ... };           
  foreach (new i : NonNull(array)) 
  {                                
  }  
```



### `Iterator@Null`:

#### Tag
`F@z:`


#### Remarks

Loop over all the indexes of this array that are zero.

```pawn
  new array[] = { ... };        
  foreach (new i : Null(array)) 
  {                             
  }  
```



### `Iterator@Powers`:

#### Tag
`F@z:`


#### Remarks

Returns all the powers of the given number that can be stored in a PAWN cell.

```pawn
    foreach (new i : Powers(3))       
  {                                 
      // 3^0, 3^1, 3^2, 3^3, etc... 
  }  
```



### `Iterator@Random`:

#### Tag
`F@z:`


#### Remarks

Return a given count of random numbers:

```pawn
  foreach (new i : Random(5)) 
  {                           
      // 5 random numbers.    
  }  
```


```pawn
  foreach (new i : Random(12, 10))                              
  {                                                             
      // 12 random numbers between 0 and 10 (0 to 9 inclusive). 
  }  
```


```pawn
  foreach (new i : Random(100, -10, 10))                             
  {                                                                  
      // 100 random numbers between -10 and 10 (-10 to 9 inclusive). 
  }  
```

If only `min` is given, not `max`, it is used as the max instead and the minimum is `0`.


### `Iterator@Range`:

#### Tag
`F@z:`


#### Remarks

Pretty much used to replicate a normal loop with `foreach`. This:

```pawn
  for (new i = 10; i != 100; i += 2) 
  {                                  
  }  
```

Becomes:
```pawn
  foreach (new i : Range(10, 100, 2)) 
  {                                   
  }  
```

The increment value is optional, and defaults to `1`. If you want a `step` of `1` and a `min` of `0`, consider using `N(max)` instead, which is specifically optimised for that scenario.


### `Iterator@Until`:

#### Tag
`F@z:`


#### Remarks

Loop over all the indexes of this array until one equals the given value.

```pawn
  new array[] = { ... };            
  foreach (new i : Until(5, array)) 
  {                                 
  }  
```



### `using_deprecated_foreach_syntax`:

#### Tag
`bool:`


#### Remarks

This variable is re-declared when you do `foreach (Player, i)` or similar so that a warning is generated. The warning will read:

```pawn
  local variable "using_deprecated_foreach_syntax" shadows a variable at a preceding level  
```

This is the best I could do to warn about the old syntax. That code should now be `foreach (new i : Player)`. It may become an error later.


### `using_deprecated_itertag_syntax`:

#### Tag
`bool:`



## Functions


### `operator*(_no_itertag:,_:)`:


#### Syntax


```pawn
operator*(_no_itertag:,_:)(a, b)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	`_no_itertag `	 |
| 	`b`	 | 		 |

#### Remarks
Suppress warnings when `_:` is used (correctly) instead of `_no_itertag:`. This function is never called, it only exists to check tags in `Iter_Add` et. al, while guarded by `FALSE ?`.


#### Estimated stack usage
1 cells



### `ITER_SAFE_REMOVE`:


#### Syntax


```pawn
ITER_SAFE_REMOVE(iter[], &index)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to deal with safely.	 |
| 	`index`	 | 	` & ` Index.	 |

#### Remarks
Call functions that modify an iterator safely from inside a loop:

```pawn
  DestroyVehicle(vehicleid)  {  Iter_Remove(Vehicle, vehicleid);  }  foreach (new vehicleid : Vehicle)  {  ITER_SAFE_REMOVE(Vehicle, vehicleid)  {  DestroyVehicle(vehicleid);  }  }  
```


#### Attributes
* `native`

### `Iter_Add`:


#### Syntax


```pawn
Iter_Add(iter[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to add the data to.	 |
| 	`value`	 | 	Value to add to the iterator.	 |

#### Remarks
Wrapper for Iter_AddInternal. native Iter_Add(Iterator:Name<>, value);


#### Attributes
* `native`

### `Iter_Add_InternalC`:


#### Syntax


```pawn
Iter_Add_InternalC(&count, array[], size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Array start index.	 |
| 	`value`	 | 	Item to add.	 |

#### Remarks
Adds a value to a given iterator set. Now detects when you try and add the last item multiple times, as well as all the other items. Now simplified even further with the new internal representation. The modulo code is for iterator reversal.


#### Depends on
* [`Iter_Prev_InternalD`](#Iter_Prev_InternalD)
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
* [`cellmin`](#cellmin)
#### Estimated stack usage
13 cells



### `Iter_All_Internal`:


#### Syntax


```pawn
Iter_All_Internal(array[], size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` The internal iterator data.	 |
| 	`size`	 | 	The internal iterator size.	 |
| 	`value`	 | 	The current iterator step.	 |

#### Remarks
Loop over all values in any iterator. This is different to looping over the iterator normally for multi-dimensional iterators, since it will return all values in ANY iterator in their numerical order. For single dimensional iterators it is exactly the same, just a little slower.


#### Estimated stack usage
1 cells



### `Iter_Alloc`:


#### Syntax


```pawn
Iter_Alloc(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the first free slot in.	 |

#### Remarks
Finds an empty slot in an iterator, adds that slot to the iterator, and returns the now added slot. native Iter_Alloc(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_Alloc_InternalC`:


#### Syntax


```pawn
Iter_Alloc_InternalC(&count, array[], size, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Array start index.	 |
| 	`...`	 | 		 |

#### Remarks
Finds the first free slot in the iterator and add it. Excepting requested values.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `Iter_Available`:


#### Syntax


```pawn
Iter_Available(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the number of unused elements in.	 |

#### Remarks
Returns the number of unused items in this iterator. native Iter_Available(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_Begin`:


#### Syntax


```pawn
Iter_Begin(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the start of.	 |

#### Remarks
Gets a point BEFORE the start of the iterator (the theoretical beginning).


#### Attributes
* `native`

### `Iter_Clear`:


#### Syntax


```pawn
Iter_Clear(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to empty.	 |

#### Remarks
Wrapper for Iter_Clear_Internal. Although it doesn't fit my normal strict spacing, the end of "B" is correct, namely: "_:F@s(%0),%2)". This uses the "_:%0,)" macro to consume a trailing comma when nothing is given in "%2", so I can't have a leading space sadly. "- 2" in place of the normal "- 1" is CORRECT! native Iter_Clear(IteratorArray:Name[]<>);


#### Attributes
* `native`

### `Iter_Clear_InternalC`:


#### Syntax


```pawn
Iter_Clear_InternalC(array[], size, entries, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of information.	 |
| 	`entries`	 | 	Size of the count data.	 |
| 	`...`	 | 	Optional single multi-iterator to clear.	 |

#### Remarks
Resets an iterator.


#### Depends on
* [`setarg`](#setarg)
#### Estimated stack usage
5 cells



### `Iter_Clear_InternalD`:


#### Syntax


```pawn
Iter_Clear_InternalD(array[], size, entries, elems, counts[], start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of base array.	 |
| 	`entries`	 | 	Size of the count data.	 |
| 	`elems`	 | 	Number of iterator elements.	 |
| 	`counts`	 | 	` [] ` Number of items in the iterator.	 |
| 	`start`	 | 	Optional single multi-iterator to clear.	 |

#### Remarks
Resets an iterator.


#### Estimated stack usage
1 cells



### `Iter_Contains`:


#### Syntax


```pawn
Iter_Contains(iter[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to check membership of.	 |
| 	`value`	 | 	Value to check.	 |

#### Tag
`bool:`


#### Remarks
Checks if the given value is in the given iterator. native Iter_Contains(Iterator:Name<>, value);


#### Attributes
* `native`

### `Iter_Contains_InternalC`:


#### Syntax


```pawn
Iter_Contains_InternalC(array[], size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`value`	 | 	Item to check.	 |

#### Remarks
Checks if this item is in the iterator.


#### Estimated stack usage
1 cells



### `Iter_Contains_InternalD`:


#### Syntax


```pawn
Iter_Contains_InternalD(count, array[], size, start, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 		 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`start`	 | 		 |
| 	`value`	 | 	Item to check.	 |

#### Remarks
Checks if this item is in the iterator.


#### Estimated stack usage
1 cells



### `Iter_Count`:


#### Syntax


```pawn
Iter_Count(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the number of elements in.	 |

#### Remarks
Returns the number of items in this iterator. native Iter_Count(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_Count_InternalC`:


#### Syntax


```pawn
Iter_Count_InternalC(counts[], slots)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`counts`	 | 	` [] ` Number of items in each iterator part.	 |
| 	`slots`	 | 	Number of multi-iterator values.	 |

#### Remarks
Return the total number of elements in all slots together.


#### Estimated stack usage
2 cells



### `Iter_Debug`:


#### Syntax


```pawn
Iter_Debug(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to	 |

#### Remarks
Print information about an iterator.


#### Attributes
* `native`

### `Iter_Debug_InternalC`:


#### Syntax


```pawn
Iter_Debug_InternalC(name[], array[], size, count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 	` [] ` iterator name.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`count`	 | 	The number of elements added.	 |

#### Remarks
Print the contents of an iterator for debugging.


#### Depends on
* [`cellmax`](#cellmax)
* [`printf`](#printf)
#### Estimated stack usage
19 cells



### `Iter_Debug_InternalD`:


#### Syntax


```pawn
Iter_Debug_InternalD(name[], array[], size, counts[], slots)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 	` [] ` iterator name.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`counts`	 | 	` [] ` The number of elements added.	 |
| 	`slots`	 | 	The number of start points.	 |

#### Remarks
Print the contents of an iterator for debugging.


#### Depends on
* [`cellmax`](#cellmax)
* [`printf`](#printf)
#### Estimated stack usage
21 cells



### `Iter_End`:


#### Syntax


```pawn
Iter_End(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the end of.	 |

#### Remarks
Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").


#### Attributes
* `native`

### `Iter_Excludes`:


#### Syntax


```pawn
Iter_Excludes(iter[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to check membership of.	 |
| 	`value`	 | 	Value to check.	 |

#### Tag
`bool:`


#### Remarks
Checks if the given value is NOT in the given iterator. native Iter_Excludes(Iterator:Name<>, value);


#### Attributes
* `native`

### `Iter_FastClear`:


#### Syntax


```pawn
Iter_FastClear(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to empty.	 |

#### Remarks
Uses a static array copy to blank the iterator instead of a loop. BROKEN! native Iter_FastClear(IteratorArray:Name[]<>);


#### Attributes
* `native`

### `Iter_First`:


#### Syntax


```pawn
Iter_First(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the first valid element in.	 |

#### Remarks
Gets the first element in an iterator.


#### Attributes
* `native`

### `Iter_Free`:


#### Syntax


```pawn
Iter_Free(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the first free slot in.	 |

#### Remarks
Wrapper for Iter_Free_Internal. Returns a slot NOT in the current iterator. native Iter_Free(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_FreeMulti`:


#### Syntax


```pawn
Iter_FreeMulti(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the multi-iterator to get the first free slot in.	 |

#### Remarks
Wrapper for Iter_FreeMulti_Internal. Returns a slot NOT in the current multi-iterator. native Iter_FreeMulti(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_FreeMulti_Internal`:


#### Syntax


```pawn
Iter_FreeMulti_Internal(array[], trueSize, start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` multi-iterator data.	 |
| 	`trueSize`	 | 	Size of the multi-iterator.	 |
| 	`start`	 | 	End [?, since start points are backwards] of the multi-iterator.	 |

#### Remarks
Finds the first free multi index in the multi-iterator.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
2 cells



### `Iter_Free_Internal`:


#### Syntax


```pawn
Iter_Free_Internal(array[], size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |

#### Remarks
Finds the first free slot in the iterator.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
2 cells



### `Iter_GetMulti`:


#### Syntax


```pawn
Iter_GetMulti(iter[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to check membership of.	 |
| 	`value`	 | 	Value to check.	 |

#### Returns
Index in which the value is contained in the multi-iterator.


#### Remarks
Checks if the given value is in the given iterator, and if it is return which index it is contained. native Iter_GetMulti(Iterator:Name<>, value);


#### Attributes
* `native`

### `Iter_GetMulti_Internal`:


#### Syntax


```pawn
Iter_GetMulti_Internal(array[], trueSize, size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` multi-iterator data.	 |
| 	`trueSize`	 | 	Size of the multi-iterator per index.	 |
| 	`size`	 | 	Size of the multi-iterator.	 |
| 	`value`	 | 	Item to check.	 |

#### Returns
INVALID_ITERATOR_SLOT on failure. Index of the multi-iterator the value is contained.


#### Remarks
Checks if this item is in the multi-iterator at all, and if it is returns which index it is in.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
1 cells



### `Iter_Index`:


#### Syntax


```pawn
Iter_Index(iter[], index, wrap)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get a slot in by index.	 |
| 	`index`	 | 	Index.	 |
| 	`wrap`	 | 	`bool ` Keep going around until a value is found?	 |

#### Remarks
Wrapper for Iter_Index_Internal. Returns the Nth value in the iterator (requires looping due to the way iterators are stored and optimised for loops not direct access). native Iter_Index(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_Index_Internal`:


#### Syntax


```pawn
Iter_Index_Internal(count, array[], start, size, index, wrap)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Array start index.	 |
| 	`size`	 | 	Array size.	 |
| 	`index`	 | 	Index to find Nth value.	 |
| 	`wrap`	 | 	`bool ` Keep going around until a value is found?	 |

#### Remarks
Allows you to find the Nth value in the iterator. DO NOT call this in a loop to get all values - that totally defeats the purpose of "foreach", just use a normal "foreach" loop with an index counter for that case.


#### Depends on
* [`cellmin`](#cellmin)
#### Estimated stack usage
1 cells



### `Iter_Init`:


#### Syntax


```pawn
Iter_Init(iter[][])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [][] ` Name of the iterator array to initialise.	 |

#### Remarks
Wrapper for Iter_Init_Internal. When `__COMPILER_NESTED_ELLIPSIS` is set, this isn't needed because multi-dimensional iterators can be initialised with the new `{{0, 1, ...), ...}` feature. In that case `I@ = 0` is called as a `void` function that does nothing but ends in a semi-colon (`I@` is used a lot in YSI as a `do nothing` enabler).

```pawn
native Iter_Init(IteratorArray:Name[]<>);
```


#### Attributes
* `native`

### `Iter_InitAndClear`:


#### Syntax


```pawn
Iter_InitAndClear(iter[][])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [][] ` Name of the iterator array to initialise.	 |

#### Remarks
Wrapper for Iter_Init_Internal. ALWAYS resets the array.

```pawn
native Iter_InitAndClear(IteratorArray:Name[]<>);
```


#### Attributes
* `native`

### `Iter_Init_Internal`:


#### Syntax


```pawn
Iter_Init_Internal(array[][], first[], s0, s1, entries)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [][] ` Iterator array to initialise.	 |
| 	`first`	 | 	` [] ` First iterator slot.	 |
| 	`s0`	 | 	Size of first dimension.	 |
| 	`s1`	 | 	Size of second dimension.	 |
| 	`entries`	 | 	Number of start points.	 |

#### Remarks
Multi-dimensional arrays can't be initialised at compile time, so need to be done at run time, which is slightly annoying.


#### Depends on
* [`FIXES_memcpy`](#FIXES_memcpy)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `Iter_IsEmpty`:


#### Syntax


```pawn
Iter_IsEmpty(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to test the emptiness of.	 |

#### Remarks
For multi-iterators `Iter_IsEmpty(a<>)` and `Iter_IsEmpty(a<5>)` are different. The first returns `true` when all values are unused by any slot. The second returns `true` when that slot alone has no values, even if every single value is used by other slots. native Iter_IsEmpty(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_IsFull`:


#### Syntax


```pawn
Iter_IsFull(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to test the fullness of.	 |

#### Remarks
For multi-iterators `Iter_IsFull(a<>)` and `Iter_IsFull(a<5>)` are different. The first returns `true` when all values are used, in any slot. The second returns `true` when that slot alone has all values. native Iter_IsFull(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_Last`:


#### Syntax


```pawn
Iter_Last(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to	 |

#### Remarks
Gets the last element in an iterator. Works by getting the previous item from the one BEFORE the first element (i.e. the one before the sentinel).


#### Attributes
* `native`

### `Iter_Next`:


#### Syntax


```pawn
Iter_Next(iter[], cur)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the next element in.	 |
| 	`cur`	 | 	The current element.	 |

#### Remarks
Gets the element in an iterator after the current one.


#### Attributes
* `native`

### `Iter_NonEmpty`:


#### Syntax


```pawn
Iter_NonEmpty(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to test the non-emptiness of.	 |

#### Remarks
For multi-iterators `Iter_NonEmpty(a<>)` and `Iter_NonEmpty(a<5>)` are different. The first returns `true` when any value is used, in any slot. The second returns `true` when that slot alone has any values. native Iter_NonEmpty(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_NonFull`:


#### Syntax


```pawn
Iter_NonFull(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to test the non-fullness of.	 |

#### Remarks
For multi-iterators `Iter_NonFull(a<>)` and `Iter_NonFull(a<5>)` are different. The first returns `true` when not all values are used anywhere. The second returns `true` when that slot alone is missing some values, even if those values are in other slots. native Iter_NonFull(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_None_Internal`:


#### Syntax


```pawn
Iter_None_Internal(array[], size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` The internal iterator data.	 |
| 	`size`	 | 	The internal iterator size.	 |
| 	`value`	 | 	The current iterator step.	 |

#### Remarks
Loop over all values NOT in any iterator. Similar to repeatedly calling `Iter_Free`, though that will return the same value twice if called twice in a row. Instead, this function will loop through the missing ones.


#### Estimated stack usage
1 cells



### `Iter_Prev`:


#### Syntax


```pawn
Iter_Prev(iter[], cur)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the previous element in.	 |
| 	`cur`	 | 	The current element.	 |

#### Remarks
Gets the element in an iterator before the current one. Slow.


#### Attributes
* `native`

### `Iter_Prev_InternalC`:


#### Syntax


```pawn
Iter_Prev_InternalC(array[], elems, size, slot)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`elems`	 | 	Number of elements in the iterator.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`slot`	 | 	The current slot.	 |

#### Remarks
Gets the element in an iterator that points to the current element.


#### Estimated stack usage
2 cells



### `Iter_Prev_InternalD`:


#### Syntax


```pawn
Iter_Prev_InternalD(array[], size, slot)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`slot`	 | 	The current slot.	 |

#### Remarks
Gets the element in an iterator that points to the current element.


#### Depends on
* [`min`](#min)
#### Estimated stack usage
5 cells



### `Iter_Random`:


#### Syntax


```pawn
Iter_Random(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get a random slot from.	 |

#### Remarks
Wrapper for Iter_RandomInternal. native Iter_Random(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_RandomAdd`:


#### Syntax


```pawn
Iter_RandomAdd(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to add a random slot to.	 |

#### Remarks
Wrapper for Iter_RandomAddInternal. native Iter_RandomAdd(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_RandomAdd_InternalC`:


#### Syntax


```pawn
Iter_RandomAdd_InternalC(&count, array[], start, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`...`	 | 		 |

#### Remarks
Adds a random value to an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_Add_InternalC`](#Iter_Add_InternalC)
* [`Iter_RandomFree_Multi`](#Iter_RandomFree_Multi)
* [`Iter_RandomFree_Single`](#Iter_RandomFree_Single)
* [`__cell_shift`](#__cell_shift)
* [`__param3_offset`](#__param3_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `Iter_RandomAdd_InternalD`:


#### Syntax


```pawn
Iter_RandomAdd_InternalD(counts[], array[], size, slots, start, slot, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`counts`	 | 	` [] ` Number of items in each iterator part.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Size of the iterator.	 |
| 	`slots`	 | 	Number of multi-iterator values.	 |
| 	`start`	 | 		 |
| 	`slot`	 | 	Multi-iterator slot to add to.	 |
| 	`...`	 | 		 |

#### Remarks
Adds a random value to an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_Add_InternalD`](#Iter_Add_InternalD)
* [`Iter_RandomFree_Multi`](#Iter_RandomFree_Multi)
* [`Iter_RandomFree_Single`](#Iter_RandomFree_Single)
* [`__cell_shift`](#__cell_shift)
* [`__param6_offset`](#__param6_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
12 cells



### `Iter_RandomFree`:


#### Syntax


```pawn
Iter_RandomFree(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get a random unused slot for.	 |

#### Remarks
Wrapper for Iter_RandomFree_Internal. native Iter_RandomFree(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_RandomFree_InternalC`:


#### Syntax


```pawn
Iter_RandomFree_InternalC(count, array[], start, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`...`	 | 		 |

#### Remarks
Returns a random unused value from an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_RandomFree_Multi`](#Iter_RandomFree_Multi)
* [`Iter_RandomFree_Single`](#Iter_RandomFree_Single)
* [`__cell_shift`](#__cell_shift)
* [`__param3_offset`](#__param3_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `Iter_RandomFree_InternalD`:


#### Syntax


```pawn
Iter_RandomFree_InternalD(counts[], array[], start, slots, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`counts`	 | 	` [] ` Number of items in each iterator part.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`slots`	 | 	Number of multi-iterator values.	 |
| 	`...`	 | 		 |

#### Remarks
Returns a random unused value from an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_RandomFree_Multi`](#Iter_RandomFree_Multi)
* [`Iter_RandomFree_Single`](#Iter_RandomFree_Single)
* [`__cell_shift`](#__cell_shift)
* [`__param4_offset`](#__param4_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
11 cells



### `Iter_RandomFree_Multi`:


#### Syntax


```pawn
Iter_RandomFree_Multi(count, array[], start, num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`num`	 | 		 |

#### Remarks
Returns a random unused value from an iterator. Takes a load of hidden extra parameters on the stack, which are values to not return.


#### Depends on
* [`FIXES_random`](#FIXES_random)
* [`__cell_shift`](#__cell_shift)
* [`__param4_offset`](#__param4_offset)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
#### Estimated stack usage
7 cells



### `Iter_RandomFree_Single`:


#### Syntax


```pawn
Iter_RandomFree_Single(count, array[], start)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |

#### Remarks
Returns a random unused value from an iterator. No exclusions.


#### Depends on
* [`FIXES_random`](#FIXES_random)
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `Iter_RandomRemove`:


#### Syntax


```pawn
Iter_RandomRemove(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to remove a random slot from.	 |

#### Remarks
Wrapper for Iter_RandomRemoveInternal. native Iter_RandomRemove(Iterator:Name<>);


#### Attributes
* `native`

### `Iter_RandomRemove_InternalC`:


#### Syntax


```pawn
Iter_RandomRemove_InternalC(&count, array[], start, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`...`	 | 		 |

#### Remarks
Removes a random value from an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_Random_Impl`](#Iter_Random_Impl)
* [`Iter_Remove_InternalC`](#Iter_Remove_InternalC)
* [`__cell_shift`](#__cell_shift)
* [`__param3_offset`](#__param3_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `Iter_RandomRemove_InternalD`:


#### Syntax


```pawn
Iter_RandomRemove_InternalD(&count, array[], size, start, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 		 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`...`	 | 		 |
| 	`slots`	 | 	Number of multi-iterator values.	 |

#### Remarks
Removes a random value from an iterator.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_Random_Impl`](#Iter_Random_Impl)
* [`Iter_Remove_InternalD`](#Iter_Remove_InternalD)
* [`__cell_shift`](#__cell_shift)
* [`__param4_offset`](#__param4_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
11 cells



### `Iter_Random_Impl`:


#### Syntax


```pawn
Iter_Random_Impl(count, array[], start, num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`num`	 | 	Number of extra parameters hidden on the stack.	 |

#### Remarks
Returns a random value from an iterator. If additional parameters are given they are excluded from consideration. This allows you to chain calls to get multiple random values so follows: new president = Iter_Random(Player); new vicePresident = Iter_Random(Player, president); new primeMinister = Iter_Random(Player, president, vicePresident); new minister = Iter_Random(Player, president, vicePresident, primeMinister); None of those values can be the same, and this saves horrible random- dependent loops.


#### Depends on
* [`FIXES_random`](#FIXES_random)
* [`__cell_shift`](#__cell_shift)
* [`__param4_offset`](#__param4_offset)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
#### Estimated stack usage
7 cells



### `Iter_Random_Internal`:


#### Syntax


```pawn
Iter_Random_Internal(count, array[], start, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`start`	 | 	Size of the iterator.	 |
| 	`...`	 | 	Excluded elements.	 |

#### Remarks
Returns a random value from an iterator. If additional parameters are given they are excluded from consideration. This allows you to chain calls to get multiple random values so follows: new president = Iter_Random(Player); new vicePresident = Iter_Random(Player, president); new primeMinister = Iter_Random(Player, president, vicePresident); new minister = Iter_Random(Player, president, vicePresident, primeMinister); None of those values can be the same, and this saves horrible random- dependent loops.


#### Depends on
* [`Hooks_NumArgs`](#Hooks_NumArgs)
* [`Iter_Random_Impl`](#Iter_Random_Impl)
* [`__cell_shift`](#__cell_shift)
* [`__param3_offset`](#__param3_offset)
* [`__stk`](#__stk)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `Iter_Remove`:


#### Syntax


```pawn
Iter_Remove(iter[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to remove data from.	 |
| 	`value`	 | 	Data to remove.	 |

#### Remarks
Wrapper for Iter_RemoveInternal. native Iter_Remove(Iterator:Name<>, value);


#### Attributes
* `native`

### `Iter_Remove_InternalC`:


#### Syntax


```pawn
Iter_Remove_InternalC(&count, array[], size, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` iterator data.	 |
| 	`size`	 | 	Number of iterator elements.	 |
| 	`value`	 | 	Item to remove.	 |

#### Remarks
Removes a value from an iterator.


#### Depends on
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
* [`cellmin`](#cellmin)
* [`min`](#min)
#### Estimated stack usage
12 cells



### `Iter_SafeRemove`:


#### Syntax


```pawn
Iter_SafeRemove(iter[], value, &next)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to remove data from.	 |
| 	`value`	 | 	Data to remove.	 |
| 	`next`	 | 	` & ` Container for the pointer to the next element.	 |

#### Remarks
Wrapper for Iter_SafeRemoveInternal. Common use: Iter_SafeRemove(iter, i, i); native Iter_SafeRemove(Iterator:Name<>, value, &next);


#### Attributes
* `native`

### `Iter_SafeRemove_1`:


#### Syntax


```pawn
Iter_SafeRemove_1(&count, array[], size, value, &last)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 	` & ` Number of items in the iterator.	 |
| 	`array`	 | 	` [] ` Iterator data.	 |
| 	`size`	 | 	Number of iterator elements.	 |
| 	`value`	 | 	Item to remove.	 |
| 	`last`	 | 	` & ` Pointer in which to store the last pointer.	 |

#### Remarks
Removes a value from an iterator safely.


#### Depends on
* [`Iter_Prev_InternalD`](#Iter_Prev_InternalD)
* [`cellmin`](#cellmin)
#### Estimated stack usage
6 cells



### `Iter_Size`:


#### Syntax


```pawn
Iter_Size(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the size of.	 |

#### Remarks
Accesses the size of an iterator.


#### Attributes
* `native`

### `Iter_Starts`:


#### Syntax


```pawn
Iter_Starts(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the true starts of.	 |

#### Remarks
Accesses the number of starts in a multi-iterator.


#### Attributes
* `native`

### `Iter_TrueArray`:


#### Syntax


```pawn
Iter_TrueArray(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the true array of.	 |

#### Remarks
Accesses the internal array of an iterator.


#### Attributes
* `native`

### `Iter_TrueCount`:


#### Syntax


```pawn
Iter_TrueCount(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the true count of.	 |

#### Remarks
Accesses the internal count of an iterator.


#### Attributes
* `native`

### `Iter_TrueMulti`:


#### Syntax


```pawn
Iter_TrueMulti(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Multi iterator to get the true count of.	 |

#### Remarks
Accesses the internal count of a multi-iterator.


#### Attributes
* `native`

### `Iter_TrueSize`:


#### Syntax


```pawn
Iter_TrueSize(iter[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`iter`	 | 	`Iterator [] ` Name of the iterator to get the true size of.	 |

#### Remarks
Accesses the internal size of an iterator.


#### Attributes
* `native`

### `Iterator`:


#### Syntax


```pawn
Iterator(name)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`name`	 | 		 |

#### Tag
`Iterator:`


#### Remarks
Creates a new iterator start/array pair.


#### Attributes
* `native`

### `Master_OnYSIInit`:


#### Syntax


```pawn
Master_OnYSIInit()
```

#### Remarks
Sets up all existing iterators. Does nothing for "XXLocal" ones, since they are by definition empty when a script starts.


#### Depends on
* [`operator*(_no_itertag:,_:)`](#operator*(_no_itertag:,_:))
* [`FALSE`](#FALSE)
* [`FIXES_IsActorStreamedIn`](#FIXES_IsActorStreamedIn)
* [`FIXES_IsPlayerConnected`](#FIXES_IsPlayerConnected)
* [`FIXES_IsPlayerNPC`](#FIXES_IsPlayerNPC)
* [`FIXES_IsPlayerStreamedIn`](#FIXES_IsPlayerStreamedIn)
* [`FIXES_IsValidActor`](#FIXES_IsValidActor)
* [`FIXES_IsVehicleStreamedIn`](#FIXES_IsVehicleStreamedIn)
* [`GetVehicleModel`](#GetVehicleModel)
* [`Iter_Add_InternalC`](#Iter_Add_InternalC)
* [`Iter_Clear_InternalC`](#Iter_Clear_InternalC)
* [`Iter_Init_Internal`](#Iter_Init_Internal)
* [`Iter_OnYSIInit`](#Iter_OnYSIInit)
* [`Iter_Single@Actor`](#Iter_Single@Actor)
* [`Iter_Single@Bot`](#Iter_Single@Bot)
* [`Iter_Single@Character`](#Iter_Single@Character)
* [`Iter_Single@Player`](#Iter_Single@Player)
* [`Iter_Single@StreamedActor`](#Iter_Single@StreamedActor)
* [`Iter_Single@StreamedBot`](#Iter_Single@StreamedBot)
* [`Iter_Single@StreamedCharacter`](#Iter_Single@StreamedCharacter)
* [`Iter_Single@StreamedPlayer`](#Iter_Single@StreamedPlayer)
* [`Iter_Single@StreamedVehicle`](#Iter_Single@StreamedVehicle)
* [`Iter_Single@Vehicle`](#Iter_Single@Vehicle)
* [`Iterator@Actor`](#Iterator@Actor)
* [`Iterator@Bot`](#Iterator@Bot)
* [`Iterator@Character`](#Iterator@Character)
* [`Iterator@Player`](#Iterator@Player)
* [`Iterator@StreamedActor`](#Iterator@StreamedActor)
* [`Iterator@StreamedActor`](#Iterator@StreamedActor)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`Iterator@StreamedVehicle`](#Iterator@StreamedVehicle)
* [`Iterator@StreamedVehicle`](#Iterator@StreamedVehicle)
* [`Iterator@Vehicle`](#Iterator@Vehicle)
#### Attributes
* `public`
#### Automaton
_ALS


#### Estimated stack usage
9 cells



### `OnPlayerStreamIn`:

This callback is called when a player is streamed by some other player's client.



#### Syntax


```pawn
OnPlayerStreamIn(playerid, forplayerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	The ID of the player who has been streamed	 |
| 	`forplayerid`	 | 	The ID of the player that streamed the other player in	 |
| 	`playerid`	 | 	Player who entered streaming range.	 |
| 	`forplayerid`	 | 	The viewing player.	 |

#### Returns
This callback does not handle returns.
It is always called first in filterscripts.


#### Remarks
This callback was added in SA-MP 0.3a and will not work in earlier versions!


This callback can also be called by NPC.


Update the internal list of which players `forplayerid` can see.


#### Depends on
* [`operator*(_no_itertag:,_:)`](#operator*(_no_itertag:,_:))
* [`FALSE`](#FALSE)
* [`FIXES_IsPlayerNPC`](#FIXES_IsPlayerNPC)
* [`Iter_Add_InternalC`](#Iter_Add_InternalC)
* [`Iter_OnPlayerStreamIn`](#Iter_OnPlayerStreamIn)
* [`Iter_Single@StreamedBot`](#Iter_Single@StreamedBot)
* [`Iter_Single@StreamedCharacter`](#Iter_Single@StreamedCharacter)
* [`Iter_Single@StreamedPlayer`](#Iter_Single@StreamedPlayer)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
#### Attributes
* `public`
#### Estimated stack usage
7 cells


#### See Also

* [`OnPlayerStreamOut`](#OnPlayerStreamOut)
* [`OnActorStreamIn`](#OnActorStreamIn)
* [`OnVehicleStreamIn`](#OnVehicleStreamIn)

### `OnPlayerStreamOut`:

This callback is called when a player is streamed out from some other player's client.



#### Syntax


```pawn
OnPlayerStreamOut(playerid, forplayerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	The player who has been destreamed	 |
| 	`forplayerid`	 | 	The player who has destreamed the other player	 |
| 	`playerid`	 | 	Player who left streaming range.	 |
| 	`forplayerid`	 | 	The viewing player.	 |

#### Returns
This callback does not handle returns.
It is always called first in filterscripts.


#### Remarks
This callback was added in SA-MP 0.3a and will not work in earlier versions!


This callback can also be called by NPC.


Update the internal list of which players `forplayerid` can see.


#### Depends on
* [`operator*(_no_itertag:,_:)`](#operator*(_no_itertag:,_:))
* [`FALSE`](#FALSE)
* [`FIXES_IsPlayerNPC`](#FIXES_IsPlayerNPC)
* [`Iter_OnPlayerStreamOut`](#Iter_OnPlayerStreamOut)
* [`Iter_Remove_InternalC`](#Iter_Remove_InternalC)
* [`Iter_Single@StreamedBot`](#Iter_Single@StreamedBot)
* [`Iter_Single@StreamedCharacter`](#Iter_Single@StreamedCharacter)
* [`Iter_Single@StreamedPlayer`](#Iter_Single@StreamedPlayer)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedBot`](#Iterator@StreamedBot)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedCharacter`](#Iterator@StreamedCharacter)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`Iterator@StreamedPlayer`](#Iterator@StreamedPlayer)
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
#### Attributes
* `public`
#### Estimated stack usage
8 cells


#### See Also

* [`OnPlayerStreamIn`](#OnPlayerStreamIn)
* [`OnActorStreamOut`](#OnActorStreamOut)
* [`OnVehicleStreamOut`](#OnVehicleStreamOut)

### `ScriptInit_OnPlayerConnect`:


#### Syntax


```pawn
ScriptInit_OnPlayerConnect(playerid)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player who joined.	 |

#### Remarks
Adds a player to the loop data. Now sorts the list too. Note that I found the most bizzare bug ever (I *think* it may be a compiler but, but it requires further investigation), basically it seems that multiple variables were being treated as the same variable (namely @YSII_EgotS and @YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the same). Adding print statements which reference these variables seem to fix the problem, and I've tried to make sure that the values will never actually get printed.


#### Depends on
* [`operator*(_no_itertag:,_:)`](#operator*(_no_itertag:,_:))
* [`FALSE`](#FALSE)
* [`FIXES_IsPlayerNPC`](#FIXES_IsPlayerNPC)
* [`Iter_Add_InternalC`](#Iter_Add_InternalC)
* [`Iter_OnPlayerConnect`](#Iter_OnPlayerConnect)
* [`Iter_Single@Bot`](#Iter_Single@Bot)
* [`Iter_Single@Character`](#Iter_Single@Character)
* [`Iter_Single@Player`](#Iter_Single@Player)
* [`Iterator@Bot`](#Iterator@Bot)
* [`Iterator@Character`](#Iterator@Character)
* [`Iterator@Player`](#Iterator@Player)
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
#### Attributes
* `public`
#### Automaton
_ALS


#### Estimated stack usage
7 cells



### `ScriptInit_OnPlayerDisconnect`:


#### Syntax


```pawn
ScriptInit_OnPlayerDisconnect(playerid, reason)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`playerid`	 | 	Player who left.	 |
| 	`reason`	 | 		 |

#### Remarks
Removes a player from the loop data. No longer uses "hook" to ENSURE that this is always last. Previously I think that the order of evaluation in y_hooks meant that this got called before the user "OnPlayerDisconnect".


#### Depends on
* [`operator*(_no_itertag:,_:)`](#operator*(_no_itertag:,_:))
* [`FALSE`](#FALSE)
* [`FIXES_IsPlayerNPC`](#FIXES_IsPlayerNPC)
* [`Iter_OnPlayerDisconnect`](#Iter_OnPlayerDisconnect)
* [`Iter_Remove_InternalC`](#Iter_Remove_InternalC)
* [`Iter_Single@Bot`](#Iter_Single@Bot)
* [`Iter_Single@Character`](#Iter_Single@Character)
* [`Iter_Single@Player`](#Iter_Single@Player)
* [`Iterator@Bot`](#Iterator@Bot)
* [`Iterator@Character`](#Iterator@Character)
* [`Iterator@Player`](#Iterator@Player)
#### Attributes
* `public`
#### Automaton
_ALS


#### Estimated stack usage
8 cells



### `iterfunc`:


#### Syntax


```pawn
iterfunc(params)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`params`	 | 	The iterator function's parameters.	 |

#### Remarks
Used to declare a special iterator function. Examples:

```pawn
  iterfunc stock OnlyZero(cur)                                                    
  {                                                                               
      if (cur == -1)                                                              
          return 0;                                                               
      return -1;                                                                  
  }                                                                               
  
```


```pawn
  iterfunc stock AlsoOnlyZero[cellmin](cur)                                       
  {                                                                               
      if (cur == cellmin)                                                         
          return 0;                                                               
      return cellmin;                                                             
  }                                                                               
  
```


```pawn
  iterfunc stock OneToTen[cellmin](cur)                                           
  {                                                                               
      if (cur == cellmin)                                                         
          return 1;                                                               
      if (cur == 10)                                                              
          return cellmin;                                                         
      return cur + 1;                                                             
  }                                                                               
  
```


```pawn
  iterfunc stock OneToN(cur, n)                                                   
  {                                                                               
      if (n < 1)                                                               
          return -1;                                                              
      if (cur == -1)                                                              
          return 1;                                                               
      if (cur == n)                                                               
          return -1;                                                              
      return cur + 1;                                                             
  }                                                                               
  
```


#### Attributes
* `native`


