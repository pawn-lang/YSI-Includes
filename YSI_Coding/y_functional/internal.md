y_functional - v1.0
==========================================
Lambda functions and functional program functions - `map`, `fold`, etc.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions

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




