y_functional - v1.0
==========================================
Lambda functions and functional program functions - `map`, `fold`, etc.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `All`:


#### Syntax


```pawn
All(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@i ` A function that takes one parameter.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements pass the test function (`true` if there are no inputs).


#### Remarks
Calls the given function one at a time for every input element until one is found that fails. The function will short-circuit, so will end as soon as a matching index is found, thus not all elements may be processed and any input functions with side-effects should be aware of this.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
6 cells



### `AllIdx`:


#### Syntax


```pawn
AllIdx(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements pass the test function (`true` if there are no inputs).


#### Remarks
Calls the given function one at a time for every input element until one is found that fails. The function will short-circuit, so will end as soon as a matching index is found, thus not all elements may be processed and any input functions with side-effects should be aware of this. Passes the index as the first parameter, and the value as the second.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `And`:


#### Syntax


```pawn
And(input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`input`	 | 	`bool [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if all the elements are non-zero (`true` if there are no inputs).


#### Remarks
An empty array cannot contain a non-zero elements, so the default return is `true`.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Any`:


#### Syntax


```pawn
Any(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@i ` A function that takes one parameter.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements pass the test function (`false` if there are no inputs).


#### Remarks
Calls the given function one at a time for every input element until one is found that passes. The function will short-circuit, so will end as soon as a matching index is found, thus not all elements may be processed and any input functions with side-effects should be aware of this.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
6 cells



### `AnyIdx`:


#### Syntax


```pawn
AnyIdx(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements pass the test function (`false` if there are no inputs).


#### Remarks
Calls the given function one at a time for every input element until one is found that passes. The function will short-circuit, so will end as soon as a matching index is found, thus not all elements may be processed and any input functions with side-effects should be aware of this. Passes the index as the first parameter, and the value as the second.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `Elem`:


#### Syntax


```pawn
Elem(n, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 	The value to compare elements against.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements equal `n` (`false` if there are no inputs).


#### Remarks
An empty array cannot contain a given element, so the default return is `false`.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `FoldL`:


#### Syntax


```pawn
FoldL(cb, n, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
A *fold* applies a function to the current data and the previous result of calling the function, and repeats this process across the whole array. The parameters to the callback are the previous result (`_0`), and the current data (`_1`). The initial "previous" value is passed in as `n`. To add all the values in an array together use:

```pawn
  new sum = FoldL({ _0 + _1 }, 0, array);  
```

To find the product use:
```pawn
  new product = FoldL({ _0 * _1 }, 1, array);  
```

The `L` refers to the call order, which is from the first element to the last element. This is important for non-commutative operations like division.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
8 cells



### `FoldL1`:


#### Syntax


```pawn
FoldL1(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
A *fold* passes two values to the callback function - the previous result and the current element. For the first call you still need a "previous" value, which in functions like `FoldL` is passed as an extra initial value parameter (`n`). In this version the initial value is instead the first array element, and thus the input must contain at least one value.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
8 cells



### `FoldL1Idx`:


#### Syntax


```pawn
FoldL1Idx(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
Like `FoldL1`, but also passes the current index as the first parameter to the callback function.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
9 cells



### `FoldLIdx`:


#### Syntax


```pawn
FoldLIdx(cb, n, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
Like `FoldL`, but passes the index as the first parameter as well. The `L` refers to the call order, which is from the first element to the last element. This is important for non-commutative operations like division.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
9 cells



### `FoldR`:


#### Syntax


```pawn
FoldR(cb, input[], n, inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
A *fold* applies a function to the current data and the previous result of calling the function, and repeats this process across the whole array. The parameters to the callback are the current data (`_0`) and the previous result (`_1`). The initial "previous" value is passed in as `n`. To add all the values in an array together use:

```pawn
  new sum = FoldR({ _0 + _1 }, 0, array);  
```

To find the product use:
```pawn
  new product = FoldR({ _0 * _1 }, 1, array);  
```

The `R` refers to the call order, which is from the last element to the first element. This is important for non-commutative operations like division.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
7 cells



### `FoldR1`:


#### Syntax


```pawn
FoldR1(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
A *fold* passes two values to the callback function - the previous result and the current element. For the first call you still need a "previous" value, which in functions like `FoldR` is passed as an extra initial value parameter (`n`). In this version the initial value is instead the last array element, and thus the input must contain at least one value.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
7 cells



### `FoldR1Idx`:


#### Syntax


```pawn
FoldR1Idx(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
Like `FoldR1`, but also passes the current index as the first parameter to the callback function.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
8 cells



### `FoldRIdx`:


#### Syntax


```pawn
FoldRIdx(cb, input[], n, inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The result of applying one function to every array element in turn.


#### Remarks
Like `FoldR`, but passes the index as the first parameter as well. The `R` refers to the call order, which is from the last element to the first element. This is important for non-commutative operations like division.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
8 cells





#### Estimated stack usage
1 cells



### `Map`:


#### Syntax


```pawn
Map(cb, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@i ` A function that takes one parameter.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Applies the given function to every element in the input array and saves the individual results in the output array. This:

```pawn
  Map({ _0 + 42 }, input, output);  
```

Is equivalent to:
```pawn
  for (new i = 0; i != len; ++i) 
  {                              
      output[i] = input[i] + 42; 
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
7 cells



### `MapIdx`:


#### Syntax


```pawn
MapIdx(cb, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Applies the given function to every element in the input array and their index, and saves the result. This:

```pawn
  MapIdx({ _0 * _1 }, input, output);  
```

Is equivalent to:
```pawn
  for (new i = 0; i != len; ++i) 
  {                              
      output[i] = i * input[i];  
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
8 cells



### `MapIdx_`:


#### Syntax


```pawn
MapIdx_(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Applies the given function to every element in the input array and their index, but doesn't save the result. The function should thus have a side- effect. This:

```pawn
  MapIdx_({ printf("[%d] = %d", _0, _1) }, input);  
```

Is equivalent to:
```pawn
  for (new i = 0; i != len; ++i)        
  {                                     
      printf("[%d] = %d", i, input[i]); 
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
7 cells



### `Map_`:


#### Syntax


```pawn
Map_(cb, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@i ` A function that takes one parameter.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Applies the given function to every element in the input array, but doesn't save the result. The function should thus have a side-effect. This:

```pawn
  Map_({ printf("%d", _0) }, input);  
```

Is equivalent to:
```pawn
  for (new i = 0; i != len; ++i) 
  {                              
      printf("%d", input[i]);    
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
6 cells



### `NotElem`:


#### Syntax


```pawn
NotElem(n, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 	The value to compare elements against.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if none of the elements equal `n` (`true` if there are no inputs).


#### Remarks
An empty array cannot contain a given element, so the default return is `true`.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Or`:


#### Syntax


```pawn
Or(input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`input`	 | 	`bool [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |

#### Tag
`bool:`


#### Returns
`true` if any the elements are non-zero (`false` if there are no inputs).


#### Remarks
An empty array cannot contain a non-zero element, so the default return is `false`.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Reverse`:


#### Syntax


```pawn
Reverse(data[], dataSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`data`	 | 	` [] ` The input and output data array.	 |
| 	`dataSize`	 | 	The size of the input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Reverses an array, so the last element becomes the first, the first becomes the last, and all the ones in-between swap places as well. Modifies the input array.


#### Estimated stack usage
3 cells



### `ScanL`:


#### Syntax


```pawn
ScanL(cb, n, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
A *fold* applies a function to the current data and the previous result of calling the function, and repeats this process across the whole array. A *scan* extends this process by also saving all of the intermediate results in an output array. For example:

```pawn
  new input[5] = { 1, 2, 3, 4, 5 }                    
  new output[6];                                      
  ScanL({ _0 * _1 }, 1, input, output);  
```

Would return all of the interim steps stored in `output` as `{ 1, 1 * 1, 1 * 1 * 2, 1 * 1 * 2 * 3, 1 * 1 * 2 * 3 * 4, 1 * 1 * 2 * 3 * 4, 1 * 1 * 2 * 3 * 4 * 5 }`. Hence why the output array must be one cell larger than the input array. The `L` refers to the call order, which is from the first element to the last element. This is especially important in scan functions - compare the example output of `ScanR`.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ScanLIdx`:


#### Syntax


```pawn
ScanLIdx(cb, n, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ScanL`, but passes the index as the first parameter as well. The `L` refers to the call order, which is from the first element to the last element. This is important for non-commutative operations like division.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
10 cells



### `ScanR`:


#### Syntax


```pawn
ScanR(cb, input[], n, output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
A *fold* applies a function to the current data and the previous result of calling the function, and repeats this process across the whole array. A *scan* extends this process by also saving all of the intermediate results in an output array. For example:

```pawn
  new input[5] = { 1, 2, 3, 4, 5 }                    
  new output[6];                                      
  ScanL({ _0 * _1 }, 1, input, output);  
```

Would return all of the interim steps stored in `output` as `{ 1 * 1 * 2 * 3 * 4 * 5, 1 * 2 * 3 * 4 * 5, 1 * 3 * 4 * 5, 1 * 4 * 5, 1 * 5 }`. Hence why the output array must be one cell larger than the input array. The `R` refers to the call order, which is from the last element to the first element. This is especially important in scan functions - compare the example output of `ScanL`.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
8 cells



### `ScanRIdx`:


#### Syntax


```pawn
ScanRIdx(cb, input[], n, output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`n`	 | 	The initial value of the accumulation.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements written


#### Remarks
Like `ScanR`, but passes the index as the first parameter as well. The `R` refers to the call order, which is from the last element to the first element. This is important for non-commutative operations like division.


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ZipWith`:


#### Syntax


```pawn
ZipWith(cb, left[], right[], output[], leftSize, rightSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes one parameter.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`right`	 | 	` [] ` The second input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`rightSize`	 | 	The size of the second input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Combines two input arrays using a given function, and saves the result. This:

```pawn
  ZipWith({ _0 + _1 }, left, right, output);  
```

Is equivalent to:
```pawn
  for (new i = 0; i != len; ++i)       
  {                                    
      output[i] = left[i] + right[i]; 
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
8 cells



### `ZipWith3`:


#### Syntax


```pawn
ZipWith3(cb, left[], middle[], right[], output[], leftSize, middleSize, rightSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`middle`	 | 	` [] ` The second input data array.	 |
| 	`right`	 | 	` [] ` The third input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`middleSize`	 | 	The size of the second input array.	 |
| 	`rightSize`	 | 	The size of the third input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith`, but has three inputs, not two. The lambda parameters are thus `_0` for the current `left` value, `_1` for the current `middle` value, and `_2` for the current `right` value:

```pawn
  ZipWith3({ VectorSize(Float:_0, Float:_1, Float:_2) }, gPointXs, gPointYs, gPointZs, gDistances);  
```


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ZipWith3Idx`:


#### Syntax


```pawn
ZipWith3Idx(cb, left[], middle[], right[], output[], leftSize, middleSize, rightSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iiii ` A function that takes four parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`middle`	 | 	` [] ` The second input data array.	 |
| 	`right`	 | 	` [] ` The third input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`middleSize`	 | 	The size of the second input array.	 |
| 	`rightSize`	 | 	The size of the third input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith3`, but passes the current index as well. The lambda parameters are thus `_0` for the current index, `_1` for the current `left` value, `_2` for the current `middle` value, and `_3` for the current `right` value:

```pawn
  ZipWith3Idx({ CreateVehicle(gModels[_0], Float:_1, Float:_2, Float:_3, 0.0, -1, -1, 100000) }, gPosXs,  gPosYs, gPosZs, gVehicles);  
```

This example uses the index to replicate a `ZipWith4`, which isn't implemented in the library natively.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
10 cells



### `ZipWith3Idx_`:


#### Syntax


```pawn
ZipWith3Idx_(cb, left[], middle[], right[], leftSize, middleSize, rightSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iiii ` A function that takes four parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`middle`	 | 	` [] ` The second input data array.	 |
| 	`right`	 | 	` [] ` The third input data array.	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`middleSize`	 | 	The size of the second input array.	 |
| 	`rightSize`	 | 	The size of the third input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith3_`, but passes the current index as well. The lambda parameters are thus `_0` for the current index, `_1` for the current `left` value, `_2` for the current `middle` value, and `_3` for the current `right` value. The expression result is not saved:

```pawn
  ZipWith3Idx_({ SetPlayerPos(_0, Float:_1, Float:_2, Float:_3) }, gPlayerXs, gPlayerYs, gPlayerZs);  
```


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
10 cells



### `ZipWith3_`:


#### Syntax


```pawn
ZipWith3_(cb, left[], middle[], right[], leftSize, middleSize, rightSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`middle`	 | 	` [] ` The second input data array.	 |
| 	`right`	 | 	` [] ` The third input data array.	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`middleSize`	 | 	The size of the second input array.	 |
| 	`rightSize`	 | 	The size of the third input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith_`, but has three inputs, not two. The lambda parameters are thus `_0` for the current `left` value, `_1` for the current `middle` value, and `_2` for the current `right` value. The expression result is not saved.

```pawn
  RemoveBins(playerid)                                                                                                    
  {                                                                                                                       
      ZipWith3_({ RemoveBuildingForPlayer(playerid, 1337, Float:_0, Float:_1, Float:_2, 2.0) }, gBinXs, gBinYs,  gBinZs); 
  }  
```

This example uses `playerid`, which is a variable from the function this code is within. Labmdas can use closures, just like inlines.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ZipWithIdx`:


#### Syntax


```pawn
ZipWithIdx(cb, left[], right[], output[], leftSize, rightSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`right`	 | 	` [] ` The second input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`rightSize`	 | 	The size of the second input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith`, but passes the current index as well. The lambda parameters are thus `_0` for the current index, `_1` for the current `left` value, and `_2` for the current `right` value:

```pawn
  inline AddAndMul(a, b, c)                                      
  {                                                              
      return a + (b * c);                                        
  }                                                              
  
  ZipWithIdx(using inline AddAndMul, gInput1, gInput2, gResult);  
```

These functions can also use normal `using` syntax.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ZipWithIdx_`:


#### Syntax


```pawn
ZipWithIdx_(cb, left[], right[], leftSize, rightSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`right`	 | 	` [] ` The second input data array.	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`rightSize`	 | 	The size of the second input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Like `ZipWith_`, but passes the current index as well. The lambda parameters are thus `_0` for the current index, `_1` for the current `left` value, and `_2` for the current `right` value. The expression result is not saved:

```pawn
  ZipWithIdx_({ SetPlayerVirtualWorld(_0, _1), SetPlayerInterior(_0, _2) }, gPlayerWords, gPlayerInteriors);  
```


#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
9 cells



### `ZipWith_`:


#### Syntax


```pawn
ZipWith_(cb, left[], right[], leftSize, rightSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`left`	 | 	` [] ` The first input data array.	 |
| 	`right`	 | 	` [] ` The second input data array.	 |
| 	`leftSize`	 | 	The size of the first input array.	 |
| 	`rightSize`	 | 	The size of the second input array.	 |

#### Returns
The number of elements processed.


#### Remarks
Combines two input arrays using a given function, but doesn't save the result so the function should have side-effects. This:

```pawn
  new bool:result = false; 
  ZipWith_({ result = result || (_0 > _1) }, left, right);  
```

Is equivalent to:
```pawn
  new bool:result = false;                     
  for (new i = 0; i != len; ++i)               
  {                                            
      result = result || (left[i] > right[i]); 
  }  
```

But obviously much shorter and less error-prone.

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`min`](#min)
#### Estimated stack usage
8 cells



