y_cgen - v1.0
==========================================
Reserve space in COD for newly generated code.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1



## Functions


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


