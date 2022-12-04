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


