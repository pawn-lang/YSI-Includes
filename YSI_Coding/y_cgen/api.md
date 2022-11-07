y_cgen - v1.0
==========================================
Reserve space in COD for newly generated code.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


### `@_y_cgen0_y_@`:


#### Syntax


```pawn
@_y_cgen0_y_@()
```

#### Remarks
Calls the `CGEN()` function a massive number of times, to generate a lot of useless assembly whose space we can reuse for useful code (i.e. *y_hooks* stubs).


#### Depends on
* [`CGEN`](#CGEN)
#### Attributes
* `public`
#### Estimated stack usage
55 cells



### `@_y_cgen1_y_@`:


#### Syntax


```pawn
@_y_cgen1_y_@()
```

#### Remarks
Denotes the end of the unused code block, so very much relies on the compiler placing this function directly after `@_y_cgen0_y_@`.


#### Attributes
* `public`
#### Estimated stack usage
1 cells



### `CGEN`:


#### Syntax


```pawn
CGEN(&a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`a`	 | 	` & `	 |
| 	`b`	 | 	` & `	 |
| 	`c`	 | 	` & `	 |
| 	`d`	 | 	` & `	 |
| 	`e`	 | 	` & `	 |
| 	`f`	 | 	` & `	 |
| 	`g`	 | 	` & `	 |
| 	`h`	 | 	` & `	 |
| 	`i`	 | 	` & `	 |
| 	`j`	 | 	` & `	 |
| 	`k`	 | 	` & `	 |
| 	`l`	 | 	` & `	 |
| 	`m`	 | 	` & `	 |
| 	`n`	 | 	` & `	 |
| 	`o`	 | 	` & `	 |
| 	`p`	 | 	` & `	 |
| 	`q`	 | 	` & `	 |
| 	`r`	 | 	` & `	 |
| 	`s`	 | 	` & `	 |
| 	`t`	 | 	` & `	 |
| 	`u`	 | 	` & `	 |
| 	`v`	 | 	` & `	 |
| 	`w`	 | 	` & `	 |
| 	`x`	 | 	` & `	 |
| 	`y`	 | 	` & `	 |
| 	`z`	 | 	` & `	 |

#### Returns

#### Remarks
This is just a function that takes very little pawn code, but an awful lot of p-code, to call. The pawn is just `CGEN()`, but thanks to having a huge number of reference parameters all with default constant values the generated assembly is massive, with twenty-six heap allocations and pushes. It doesn't even do anything, just reserves a huge block of code space in which we can generate new code.


#### Estimated stack usage
1 cells



### `CGen_AddCodeSpace`:


#### Syntax


```pawn
CGen_AddCodeSpace(num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`num`	 | 	How much to reduce the available code space by.	 |

#### Remarks
When a library has finished generating its code this function can be used to tell y_cgen how many cells it wrote, and thus move the space space pointer on by that much.


#### Depends on
* [`Debug_Print0`](#Debug_Print0)
* [`YSI_g_sCodeSpace`](#YSI_g_sCodeSpace)
#### Estimated stack usage
4 cells



### `CGen_GetAddr`:


#### Syntax


```pawn
CGen_GetAddr(func[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`func`	 | 	` [] ` Function name to get the address of.	 |

#### Returns
The address of the function.


#### Remarks
Why this doesn't use functions from in y_amx I don't know.


#### Depends on
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AMX_HEADER_PUBLICS`](#AMX_HEADER_PUBLICS)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`funcidx`](#funcidx)
#### Estimated stack usage
3 cells



### `CGen_GetCodeSpace`:


#### Syntax


```pawn
CGen_GetCodeSpace()
```

#### Returns
The next address with free code space.


#### Depends on
* [`YSI_g_sCodeSpace`](#YSI_g_sCodeSpace)
#### Estimated stack usage
1 cells



### `CGen_OOM`:


#### Syntax


```pawn
CGen_OOM(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] ` The `AsmContext` that ran out of space.	 |

#### Remarks
Called by amx_assembly when more code is written than there is space for, or on some other errors.


#### Depends on
* [`ASM_ERROR_LABEL_DUPLICATE`](#ASM_ERROR_LABEL_DUPLICATE)
* [`ASM_ERROR_LABEL_OVERFLOW`](#ASM_ERROR_LABEL_OVERFLOW)
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`ASM_ERROR_OPCODE`](#ASM_ERROR_OPCODE)
* [`ASM_ERROR_OPERAND`](#ASM_ERROR_OPERAND)
* [`ASM_ERROR_SPACE`](#ASM_ERROR_SPACE)
* [`AsmClearError`](#AsmClearError)
* [`AsmGetError`](#AsmGetError)
* [`Debug_Kill_`](#Debug_Kill_)
* [`Debug_Print0`](#Debug_Print0)
#### Attributes
* `public`
#### Estimated stack usage
8 cells



### `CGen_SetupCodeSpace`:


#### Syntax


```pawn
CGen_SetupCodeSpace()
```

#### Remarks
Initialises the storage for unused code, and ensures that the functions being clobbered by said code are at least left in a semi-valid state.


#### Depends on
* [`CGen_GetAddr`](#CGen_GetAddr)
* [`OP_PROC`](#OP_PROC)
* [`OP_RETN`](#OP_RETN)
* [`OP_ZERO_PRI`](#OP_ZERO_PRI)
* [`RelocateOpcode`](#RelocateOpcode)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`YSI_g_sCodeEnd`](#YSI_g_sCodeEnd)
* [`YSI_g_sCodeSpace`](#YSI_g_sCodeSpace)
* [`__1_cell`](#__1_cell)
* [`__2_cells`](#__2_cells)
* [`__3_cells`](#__3_cells)
#### Estimated stack usage
4 cells



### `CGen_UseCodeSpace`:


#### Syntax


```pawn
CGen_UseCodeSpace(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] ` The assembly generation context.	 |

#### Remarks
Initialises the passed assembly generation context with a pointer in to our space code space region, complete with the remaining size and our error handler.


#### Depends on
* [`AsmInitPtr`](#AsmInitPtr)
* [`AsmSetErrorHandlerName`](#AsmSetErrorHandlerName)
* [`YSI_g_sCodeEnd`](#YSI_g_sCodeEnd)
* [`YSI_g_sCodeSpace`](#YSI_g_sCodeSpace)
#### Estimated stack usage
6 cells



### `VA_OnCodeInit`:


#### Syntax


```pawn
VA_OnCodeInit()
```

#### Remarks
Initialise the library.


#### Depends on
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`CGen_SetupCodeSpace`](#CGen_SetupCodeSpace)
* [`DisasmContext`](#DisasmContext)
* [`DisasmInit`](#DisasmInit)
* [`DisasmNextInsn`](#DisasmNextInsn)
* [`OP_NONE`](#OP_NONE)
* [`OP_NOP`](#OP_NOP)
* [`RelocateOpcode`](#RelocateOpcode)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`YSI_g_sCodeSpace`](#YSI_g_sCodeSpace)
#### Attributes
* `public`
#### Estimated stack usage
11 cells

