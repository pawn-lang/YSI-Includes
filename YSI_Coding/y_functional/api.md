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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `CTRL_OnCodeInit`:


#### Syntax


```pawn
CTRL_OnCodeInit()
```

#### Remarks
Initialise the system


#### Depends on
* [`CodeScanAddMatcher`](#CodeScanAddMatcher)
* [`CodeScanInit`](#CodeScanInit)
* [`CodeScanMatcher`](#CodeScanMatcher)
* [`CodeScanMatcherInit_`](#CodeScanMatcherInit_)
* [`CodeScanMatcherPattern_`](#CodeScanMatcherPattern_)
* [`CodeScanRunFast`](#CodeScanRunFast)
* [`CodeScanner`](#CodeScanner)
* [`Functional_FoundCall1`](#Functional_FoundCall1)
* [`Functional_FoundCall2`](#Functional_FoundCall2)
* [`LAM@0`](#LAM@0)
* [`O@A_`](#O@A_)
* [`O@V_`](#O@V_)
* [`OP_CALL`](#OP_CALL)
* [`OP_CONST_PRI`](#OP_CONST_PRI)
* [`OP_PUSH_C`](#OP_PUSH_C)
* [`OP_PUSH_PRI`](#OP_PUSH_PRI)
* [`OP_ZERO_PRI`](#OP_ZERO_PRI)
* [`__1_cell`](#__1_cell)
* [`gCodeScanCallback_match`](#gCodeScanCallback_match)
#### Attributes
* `public`
#### Estimated stack usage
713 cells



### `Elem`:


#### Syntax


```pawn
Elem(n, input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 		 |
| 	`input`	 | 	` [] `	 |
| 	`inputSize`	 | 		 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

#### Depends on
* [`INDIRECTION_DATA`](#INDIRECTION_DATA)
* [`INDIRECTION_NAUGHT`](#INDIRECTION_NAUGHT)
* [`INDIRECTION_TAG`](#INDIRECTION_TAG)
* [`Indirect_Call__`](#Indirect_Call__)
#### Estimated stack usage
8 cells



### `Functional_FoundAfter`:


#### Syntax


```pawn
Functional_FoundAfter(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |

#### Remarks
Called when a scanner matches a `LAM@5()` call, denoting the end of the lambda call. Just removes the call and stores the location.


#### Depends on
* [`CodeScanGetMatchAddressData`](#CodeScanGetMatchAddressData)
* [`CodeScanNOPMatch`](#CodeScanNOPMatch)
* [`YSI_g_sFunctionalAfterPos`](#YSI_g_sFunctionalAfterPos)
* [`YSI_g_sFunctionalLastEnd`](#YSI_g_sFunctionalLastEnd)
* [`cellmin`](#cellmin)
#### Estimated stack usage
4 cells



### `Functional_FoundCall`:


#### Syntax


```pawn
Functional_FoundCall(scanner[], nestingLevel)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |
| 	`nestingLevel`	 | 	How many lambdas deep this call is.	 |

#### Remarks
Once a lambda call is found this code is called to trigger a new set of scans to analyse the lambda function itself. It then does the code generation based on the results. This is to allow nested lambdas as the calls are found first, then the second set of scans run without preventing the call scanner from finding more results later.


#### Depends on
* [`AsmContext`](#AsmContext)
* [`AsmEmitAddC`](#AsmEmitAddC)
* [`AsmEmitHeap`](#AsmEmitHeap)
* [`AsmEmitJumpRel`](#AsmEmitJumpRel)
* [`AsmEmitLctrl`](#AsmEmitLctrl)
* [`AsmEmitLoadPri`](#AsmEmitLoadPri)
* [`AsmEmitMovs`](#AsmEmitMovs)
* [`AsmEmitSctrl`](#AsmEmitSctrl)
* [`AsmEmitStack`](#AsmEmitStack)
* [`AsmEmitStorPri`](#AsmEmitStorPri)
* [`AsmInitPtr`](#AsmInitPtr)
* [`CodeScanAddMatcher`](#CodeScanAddMatcher)
* [`CodeScanClone`](#CodeScanClone)
* [`CodeScanGetMatchAddressData`](#CodeScanGetMatchAddressData)
* [`CodeScanGetMatchStack`](#CodeScanGetMatchStack)
* [`CodeScanMatcher`](#CodeScanMatcher)
* [`CodeScanMatcherInit_`](#CodeScanMatcherInit_)
* [`CodeScanMatcherPattern_`](#CodeScanMatcherPattern_)
* [`CodeScanNOPMatch`](#CodeScanNOPMatch)
* [`CodeScanRun`](#CodeScanRun)
* [`CodeScanner`](#CodeScanner)
* [`Functional_FoundAfter`](#Functional_FoundAfter)
* [`Functional_FoundEnd`](#Functional_FoundEnd)
* [`Functional_FoundStart`](#Functional_FoundStart)
* [`I@`](#I@)
* [`LAM@1`](#LAM@1)
* [`LAM@2`](#LAM@2)
* [`LAM@5`](#LAM@5)
* [`O@A_`](#O@A_)
* [`O@V_`](#O@V_)
* [`OP_CALL`](#OP_CALL)
* [`OP_CONST_PRI`](#OP_CONST_PRI)
* [`OP_PUSH_C`](#OP_PUSH_C)
* [`OP_PUSH_PRI`](#OP_PUSH_PRI)
* [`OP_ZERO_PRI`](#OP_ZERO_PRI)
* [`YSI_g_sFunctionalAfterPos`](#YSI_g_sFunctionalAfterPos)
* [`YSI_g_sFunctionalEndPos`](#YSI_g_sFunctionalEndPos)
* [`YSI_g_sFunctionalExpectedDepth`](#YSI_g_sFunctionalExpectedDepth)
* [`YSI_g_sFunctionalLastEnd`](#YSI_g_sFunctionalLastEnd)
* [`YSI_g_sFunctionalStartPos`](#YSI_g_sFunctionalStartPos)
* [`__10_cells`](#__10_cells)
* [`__12_cells`](#__12_cells)
* [`__14_cells`](#__14_cells)
* [`__1_cell`](#__1_cell)
* [`__2_cells`](#__2_cells)
* [`__4_cells`](#__4_cells)
* [`__5_cells`](#__5_cells)
* [`__8_cells`](#__8_cells)
* [`__hea`](#__hea)
* [`__stk`](#__stk)
* [`gCodeScanCallback_match`](#gCodeScanCallback_match)
#### Estimated stack usage
1488 cells



### `Functional_FoundCall1`:


#### Syntax


```pawn
Functional_FoundCall1(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |

#### Remarks
Used when a matcher finds a lambda call with an explicit nesting level.


#### Depends on
* [`CodeScanGetMatchHole`](#CodeScanGetMatchHole)
* [`Functional_FoundCall`](#Functional_FoundCall)
#### Estimated stack usage
6 cells



### `Functional_FoundCall2`:


#### Syntax


```pawn
Functional_FoundCall2(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |

#### Remarks
Used when a matcher finds a lambda call with a ZERO op for the nesting level.


#### Depends on
* [`Functional_FoundCall`](#Functional_FoundCall)
#### Estimated stack usage
5 cells



### `Functional_FoundEnd`:


#### Syntax


```pawn
Functional_FoundEnd(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |

#### Remarks
Called when a scanner matches a `LAM@2()` call, denoting the end of a lambda function. Just removes the call and stores the location.


#### Depends on
* [`CodeScanGetMatchAddressData`](#CodeScanGetMatchAddressData)
* [`CodeScanNOPMatch`](#CodeScanNOPMatch)
* [`YSI_g_sFunctionalEndPos`](#YSI_g_sFunctionalEndPos)
* [`YSI_g_sFunctionalStartPos`](#YSI_g_sFunctionalStartPos)
#### Estimated stack usage
4 cells



### `Functional_FoundStart`:


#### Syntax


```pawn
Functional_FoundStart(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The code scanner that found a match.	 |

#### Remarks
Called when a scanner matches a `LAM@1()` call, denoting the start of a lambda function. Just removes the call and stores the location.


#### Depends on
* [`CodeScanGetMatchAddressData`](#CodeScanGetMatchAddressData)
* [`CodeScanGetMatchStack`](#CodeScanGetMatchStack)
* [`CodeScanNOPMatch`](#CodeScanNOPMatch)
* [`YSI_g_sFunctionalExpectedDepth`](#YSI_g_sFunctionalExpectedDepth)
* [`YSI_g_sFunctionalStartPos`](#YSI_g_sFunctionalStartPos)
#### Estimated stack usage
4 cells



### `LAM@0`:


#### Syntax


```pawn
LAM@0(idx)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`idx`	 | 	Used by nested lambda calls.	 |

#### Remarks
Marks the point in code where the lambda function gets called.


#### Estimated stack usage
1 cells



### `LAM@1`:


#### Syntax


```pawn
LAM@1(idx, pattern0, pattern1, pattern2, pattern3)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`idx`	 | 		 |
| 	`pattern0`	 | 		 |
| 	`pattern1`	 | 		 |
| 	`pattern2`	 | 		 |
| 	`pattern3`	 | 		 |

#### Remarks
Placeholder function used to deonte the start of lambda code. All parameters are dummies, used for code scanning and generation space padding.


#### Estimated stack usage
1 cells



### `LAM@2`:


#### Syntax


```pawn
LAM@2(par)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`par`	 | 		 |

#### Remarks
Placeholder function used to deonte the end of lambda code. The parameter is eventually used in the rewitten code to return the result.


#### Estimated stack usage
1 cells



### `LAM@5`:


#### Syntax


```pawn
LAM@5(idx, pattern0, pattern1, pattern2, pattern3, pattern4, pattern5, pattern6)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`idx`	 | 		 |
| 	`pattern0`	 | 		 |
| 	`pattern1`	 | 		 |
| 	`pattern2`	 | 		 |
| 	`pattern3`	 | 		 |
| 	`pattern4`	 | 		 |
| 	`pattern5`	 | 		 |
| 	`pattern6`	 | 		 |

#### Remarks
The end of all the generated code; functions and calls.


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
| 	`n`	 | 		 |
| 	`input`	 | 	` [] `	 |
| 	`inputSize`	 | 		 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

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
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Tag
`bool:`


#### Returns

#### Remarks

#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Reverse`:


#### Syntax


```pawn
Reverse(input[], inputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`output`	 | 	The output data array (may be the same array as an input).	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
ScanR(cb, n, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@ii ` A function that takes two parameters.	 |
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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
ScanRIdx(cb, n, input[], output[], inputSize, outputSize)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cb`	 | 	`F@_@iii ` A function that takes three parameters.	 |
| 	`n`	 | 		 |
| 	`input`	 | 	` [] ` The input data array.	 |
| 	`output`	 | 	` [] ` The output data array (may be the same array as an input).	 |
| 	`inputSize`	 | 	The size of the input array.	 |
| 	`outputSize`	 | 	The size of the output array.	 |
| 	``	 | 		 |

#### Returns

#### Remarks

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

