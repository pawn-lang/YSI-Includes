y_ctrl - v1.0
==========================================
Create new VM registers and use them via `LCTRL` and `SCTRL`.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `CTRL_FoundLCTRL`:


#### Syntax


```pawn
CTRL_FoundLCTRL(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The codescan scanner that found a matching pattern.	 |

#### Remarks
This function is called for every single `LCTRL` in the compiled AMX, after they are found by the code scanner. It checks if the found register load is for one of the new registers and replaces `LCTRL` with a special `CALL`.


#### Depends on
* [`AMX_GetPointerBinary`](#AMX_GetPointerBinary)
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`AsmContext`](#AsmContext)
* [`AsmEmitCallAbs`](#AsmEmitCallAbs)
* [`AsmEmitNop`](#AsmEmitNop)
* [`AsmInitPtr`](#AsmInitPtr)
* [`CodeScanGetMatchAddress`](#CodeScanGetMatchAddress)
* [`CodeScanGetMatchHole`](#CodeScanGetMatchHole)
* [`FIXES_format`](#FIXES_format)
* [`FUNCTION_LENGTH`](#FUNCTION_LENGTH)
* [`__2_cells`](#__2_cells)
* [`__4_cells`](#__4_cells)
* [`true`](#true)
#### Estimated stack usage
63 cells



### `CTRL_FoundSCTRL`:


#### Syntax


```pawn
CTRL_FoundSCTRL(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] ` The codescan scanner that found a matching pattern.	 |

#### Remarks
This function is called for every single `SCTRL` in the compiled AMX, after they are found by the code scanner. It checks if the found register store is for one of the new registers and replaces `SCTRL` with a special `CALL`.


#### Depends on
* [`AMX_GetPointerBinary`](#AMX_GetPointerBinary)
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`AsmContext`](#AsmContext)
* [`AsmEmitCallAbs`](#AsmEmitCallAbs)
* [`AsmEmitNop`](#AsmEmitNop)
* [`AsmInitPtr`](#AsmInitPtr)
* [`CodeScanGetMatchAddress`](#CodeScanGetMatchAddress)
* [`CodeScanGetMatchHole`](#CodeScanGetMatchHole)
* [`FIXES_format`](#FIXES_format)
* [`FUNCTION_LENGTH`](#FUNCTION_LENGTH)
* [`__2_cells`](#__2_cells)
* [`__4_cells`](#__4_cells)
* [`true`](#true)
#### Estimated stack usage
63 cells



### `CTRL_LCTRLStub`:


#### Syntax


```pawn
CTRL_LCTRLStub()
```

#### Remarks
For every custom readable control register we define we need a special call stub that can convert from passing the parameters in registers to passing the parameters on the stack, without clobbering `alt`. A lot of the code is common to all of these stubs, and this function implements that common code. The final handler and return addresses are passed to this, and the parameters are extracted from `pri` and `alt`.


#### Depends on
* [`__2_cells`](#__2_cells)
* [`__4_cells`](#__4_cells)
* [`__9_cells`](#__9_cells)
* [`__cip`](#__cip)
* [`__jmp`](#__jmp)
* [`__param0_offset`](#__param0_offset)
* [`__param1_offset`](#__param1_offset)
* [`__param2_offset`](#__param2_offset)
* [`__param3_offset`](#__param3_offset)
* [`__return_offset`](#__return_offset)
#### Estimated stack usage
1 cells



### `CTRL_SCTRLStub`:


#### Syntax


```pawn
CTRL_SCTRLStub()
```

#### Remarks
For every custom writable control register we define we need a special call stub that can convert from passing the parameters in registers to passing the parameters on the stack, without clobbering the registers. A lot of the code is common to all of these stubs, and this function implements that common code. The final handler and return addresses are passed to this, and the parameters are extracted from `pri` and `alt`.


#### Depends on
* [`__2_cells`](#__2_cells)
* [`__4_cells`](#__4_cells)
* [`__9_cells`](#__9_cells)
* [`__cip`](#__cip)
* [`__jmp`](#__jmp)
* [`__param0_offset`](#__param0_offset)
* [`__param1_offset`](#__param1_offset)
* [`__param2_offset`](#__param2_offset)
* [`__param3_offset`](#__param3_offset)
* [`__return_offset`](#__return_offset)
#### Estimated stack usage
1 cells



### `CTRL_WriteLCTRLStub`:


#### Syntax


```pawn
CTRL_WriteLCTRLStub(addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 	The address to write to.	 |

#### Remarks
For every custom readable control register we define we need a special call stub that can convert from passing the parameters in registers to passing the parameters on the stack, without clobbering `alt`. This generates those stubs.


#### Depends on
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AsmContext`](#AsmContext)
* [`AsmEmitCallAbs`](#AsmEmitCallAbs)
* [`AsmEmitJump`](#AsmEmitJump)
* [`AsmEmitProc`](#AsmEmitProc)
* [`AsmEmitPushC`](#AsmEmitPushC)
* [`AsmEmitRetn`](#AsmEmitRetn)
* [`AsmInitPtr`](#AsmInitPtr)
* [`DisasmContext`](#DisasmContext)
* [`DisasmGetOpcode`](#DisasmGetOpcode)
* [`DisasmGetOperandReloc`](#DisasmGetOperandReloc)
* [`DisasmInit`](#DisasmInit)
* [`DisasmNext`](#DisasmNext)
* [`OP_CALL`](#OP_CALL)
* [`YSI_g_sLCTRLStubAddress`](#YSI_g_sLCTRLStubAddress)
* [`__4_cells`](#__4_cells)
* [`__8_cells`](#__8_cells)
#### Estimated stack usage
33 cells



### `CTRL_WriteSCTRLStub`:


#### Syntax


```pawn
CTRL_WriteSCTRLStub(addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 	The address to write to.	 |

#### Remarks
For every custom writable control register we define we need a special call stub that can convert from passing the parameters in registers to passing the parameters on the stack, without clobbering the registers. This generates those stubs.


#### Depends on
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AsmContext`](#AsmContext)
* [`AsmEmitCallAbs`](#AsmEmitCallAbs)
* [`AsmEmitJump`](#AsmEmitJump)
* [`AsmEmitProc`](#AsmEmitProc)
* [`AsmEmitPushC`](#AsmEmitPushC)
* [`AsmEmitRetn`](#AsmEmitRetn)
* [`AsmInitPtr`](#AsmInitPtr)
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`DisasmGetOperandReloc`](#DisasmGetOperandReloc)
* [`DisasmInit`](#DisasmInit)
* [`DisasmNext`](#DisasmNext)
* [`OP_CALL`](#OP_CALL)
* [`YSI_g_sSCTRLStubAddress`](#YSI_g_sSCTRLStubAddress)
* [`__4_cells`](#__4_cells)
* [`__8_cells`](#__8_cells)
#### Estimated stack usage
33 cells



### `Timers_OnCodeInit`:


#### Syntax


```pawn
Timers_OnCodeInit()
```

#### Remarks
Initialise the library.


#### Depends on
* [`AMX_GetPointerPrefixBinary`](#AMX_GetPointerPrefixBinary)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`CTRL_FoundLCTRL`](#CTRL_FoundLCTRL)
* [`CTRL_FoundSCTRL`](#CTRL_FoundSCTRL)
* [`CTRL_LCTRLStub`](#CTRL_LCTRLStub)
* [`CTRL_SCTRLStub`](#CTRL_SCTRLStub)
* [`CTRL_WriteLCTRLStub`](#CTRL_WriteLCTRLStub)
* [`CTRL_WriteSCTRLStub`](#CTRL_WriteSCTRLStub)
* [`CodeScanAddMatcher`](#CodeScanAddMatcher)
* [`CodeScanInit`](#CodeScanInit)
* [`CodeScanMatcher`](#CodeScanMatcher)
* [`CodeScanMatcherInit_`](#CodeScanMatcherInit_)
* [`CodeScanMatcherPattern_`](#CodeScanMatcherPattern_)
* [`CodeScanRun`](#CodeScanRun)
* [`CodeScanner`](#CodeScanner)
* [`DisasmReloc`](#DisasmReloc)
* [`O@A_`](#O@A_)
* [`O@V_`](#O@V_)
* [`OP_LCTRL`](#OP_LCTRL)
* [`OP_SCTRL`](#OP_SCTRL)
* [`YSI_g_sBaseRelocation`](#YSI_g_sBaseRelocation)
* [`YSI_g_sLCTRLStubAddress`](#YSI_g_sLCTRLStubAddress)
* [`YSI_g_sSCTRLStubAddress`](#YSI_g_sSCTRLStubAddress)
* [`__1_cell`](#__1_cell)
* [`gCodeScanCallback_match`](#gCodeScanCallback_match)
#### Attributes
* `public`
#### Estimated stack usage
526 cells


