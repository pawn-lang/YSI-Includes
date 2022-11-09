y_dumpamx - v1.0
==========================================
Generate a new AMX from the current state of code.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1


This library allows you to dump the current state of the AMX to a file. If this dumping is done by defining `YSI_YES_MODE_CACHE`, then the file will be generated after `OnCodeInit` is complete, with all YSI constructs pre-compiled and included in the resulting file. The new code will also start up and resume from the point after the dump was completed.



## Functions


### `DumpAMX_EncodeBytes`:


#### Syntax


```pawn
DumpAMX_EncodeBytes(c, buffer[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`c`	 | 	The cell to encode.	 |
| 	`buffer`	 | 	` [5] ` The array in which to write the encoding.	 |

#### Remarks
Ported directly from the compiler, this encodes cells by first converting them to five bytes, then ignoring any leading zeros. This results is a slightly smaller storage size for the vast majority of data.


#### Estimated stack usage
2 cells



### `DumpAMX_Included_`:


#### Syntax


```pawn
DumpAMX_Included_()
```

#### Remarks
Just a symbol that can be detected to prove that this library was included.


#### Estimated stack usage
1 cells



### `DumpAMX_WriteAMXCode`:


#### Syntax


```pawn
DumpAMX_WriteAMXCode(file, data[], &offset, compact)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`file`	 | 	`File ` A handle to the file to write to.	 |
| 	`data`	 | 	` [] ` A buffer for encoding data in to.	 |
| 	`offset`	 | 	` & ` The current position in the file.	 |
| 	`compact`	 | 	Should compact encoding be used.	 |

#### Tag
`bool:`


#### Remarks
Dump the code segment (`COD`) to the file. Does basic code decompilation to extract parameters and convert absolute addresses (resolved when the AMX is loaded) back to the relative addresses stored in the AMX. Also converts any `SYSREQ.D` opcodes back to `SYSREQ.C`.


#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmDecodeInsn`](#DisasmDecodeInsn)
* [`DisasmGetNextIp`](#DisasmGetNextIp)
* [`DisasmGetNumOperands`](#DisasmGetNumOperands)
* [`DisasmGetOpcode`](#DisasmGetOpcode)
* [`DisasmGetOperand`](#DisasmGetOperand)
* [`DisasmGetOperandReloc`](#DisasmGetOperandReloc)
* [`DisasmInit`](#DisasmInit)
* [`DumpAMX_WriteEncoded`](#DumpAMX_WriteEncoded)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
* [`GetNativeIndexFromAddress`](#GetNativeIndexFromAddress)
* [`OP_CASETBL`](#OP_CASETBL)
* [`OP_SYSREQ_C`](#OP_SYSREQ_C)
* [`OP_SYSREQ_D`](#OP_SYSREQ_D)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`true`](#true)
#### Estimated stack usage
27 cells



### `DumpAMX_WriteAMXData`:


#### Syntax


```pawn
DumpAMX_WriteAMXData(file, data[], &offset, compact)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`file`	 | 	`File ` A handle to the file to write to.	 |
| 	`data`	 | 	` [] ` A buffer for encoding data in to.	 |
| 	`offset`	 | 	` & ` The current position in the file.	 |
| 	`compact`	 | 	Should compact encoding be used.	 |

#### Tag
`bool:`


#### Remarks
Dump the data segment (`DAT`) to the file. The `data` buffer is used for temporary encoding in case the segments being written do not align exactly to cell boundaries once compacted.


#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`AMX_HDR_HEA`](#AMX_HDR_HEA)
* [`DumpAMX_WriteEncoded`](#DumpAMX_WriteEncoded)
* [`GetAmxHeader`](#GetAmxHeader)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`true`](#true)
#### Estimated stack usage
27 cells



### `DumpAMX_WriteAMXHeader`:


#### Syntax


```pawn
DumpAMX_WriteAMXHeader(file, data[], &offset, compact)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`file`	 | 	`File ` A handle to the file to write to.	 |
| 	`data`	 | 	` [] ` A buffer for encoding data in to.	 |
| 	`offset`	 | 	` & ` The current position in the file.	 |
| 	`compact`	 | 	Should compact encoding be used.	 |

#### Tag
`bool:`


#### Remarks
Write the AMX header to the file. This basically just copies the header in its entirety, with only a small bit of customisation for natives to not also store their pointers.


#### Depends on
* [`AMX_HDR_OFFSET_COD`](#AMX_HDR_OFFSET_COD)
* [`AMX_HDR_OFFSET_DAT`](#AMX_HDR_OFFSET_DAT)
* [`AMX_HDR_OFFSET_LIBRARIES`](#AMX_HDR_OFFSET_LIBRARIES)
* [`AMX_HDR_OFFSET_NATIVES`](#AMX_HDR_OFFSET_NATIVES)
* [`FIXES_fblockwrite`](#FIXES_fblockwrite)
* [`GetRawAmxHeader`](#GetRawAmxHeader)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`true`](#true)
#### Estimated stack usage
23 cells



### `DumpAMX_WriteEncoded`:


#### Syntax


```pawn
DumpAMX_WriteEncoded(file, data[], &offset, compact, c)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`file`	 | 	`File ` A handle to the file to write to.	 |
| 	`data`	 | 	` [] ` A buffer for encoding data in to.	 |
| 	`offset`	 | 	` & ` The current position in the file.	 |
| 	`compact`	 | 	Should compact encoding be used.	 |
| 	`c`	 | 	The cell to write.	 |

#### Remarks
Take a single cell, encode it, store the encoding in the buffer, then write the buffer to the file if it is full.


#### Depends on
* [`DumpAMX_EncodeBytes`](#DumpAMX_EncodeBytes)
* [`FIXES_fblockwrite`](#FIXES_fblockwrite)
#### Estimated stack usage
12 cells




