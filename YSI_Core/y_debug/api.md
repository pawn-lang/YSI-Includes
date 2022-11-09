y_debug - v1.0
==========================================
Debugging features, optionally compile-time disabled.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1


Ensures debug levels are set and defines debug functions.

General debug levels:

* -1 - Run-time selected debug level.
* 0 - No debug information.
* 1 - Callbacks and timers.
* 2 - Remote functions.
* 3 - Stock functions.
* 4 - Static functions.
* 5 - Utility functions.
* 6 - Code.
* 7 - Loops.


If you use `Debug_Print0` you get an optional debug print controlled by the global state `ysi_debug` - which is either on or off.



## Functions


### `Debug_Code1`:


#### Syntax


```pawn
Debug_Code1(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code1{if (bla == 2) { bla++; YSI_PrintF__("%d", bla); }}  
```

Or:
```pawn
  C:1{if (bla == 2) { bla++; YSI_PrintF__("%d", bla); }}  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 1`.

#### Attributes
* `native`

### `Debug_Code2`:


#### Syntax


```pawn
Debug_Code2(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code2(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:2(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 2`.

#### Attributes
* `native`

### `Debug_Code3`:


#### Syntax


```pawn
Debug_Code3(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code3(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:3(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 3`.

#### Attributes
* `native`

### `Debug_Code4`:


#### Syntax


```pawn
Debug_Code4(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code4(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:4(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 4`.

#### Attributes
* `native`

### `Debug_Code5`:


#### Syntax


```pawn
Debug_Code5(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code5(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:5(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 5`.

#### Attributes
* `native`

### `Debug_Code6`:


#### Syntax


```pawn
Debug_Code6(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code6(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:6(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 6`.

#### Attributes
* `native`

### `Debug_Code7`:


#### Syntax


```pawn
Debug_Code7(code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`code`	 | 	Code to run.	 |

#### Remarks
Code is not a variable, it's a code chunk and may be written as so:

```pawn
  Debug_Code7(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

Or:
```pawn
  C:7(if (bla == 2) { bla++; YSI_PrintF__("%d", bla); });  
```

The code must all be on one line to avoid errors. This isn't really a function as the first parameter is part of the name. Only compiles the code when `_DEBUG %gt;= 7`.

#### Attributes
* `native`

### `Debug_Disable`:


#### Syntax


```pawn
Debug_Disable()
```

#### Tag
`bool:`


#### Remarks
Turn off level 0 prints.


Turn off level 0 prints.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Automaton
ysi_debug


#### Transition table
Source	Target	Condition
off	


#### Estimated stack usage
1 cells



### `Debug_Enable`:


#### Syntax


```pawn
Debug_Enable()
```

#### Tag
`bool:`


#### Remarks
Turn on level 0 prints.


Turn on level 0 prints.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Automaton
ysi_debug


#### Transition table
Source	Target	Condition
CONST_PAWNDOC	on	


#### Estimated stack usage
1 cells



### `Debug_GetState`:


#### Syntax


```pawn
Debug_GetState()
```

#### Tag
`bool:`


#### Remarks
Get the current debug state.


Get the current debug state.


#### Depends on
* [`false`](#false)
* [`true`](#true)
#### Automaton
ysi_debug


#### Transition table
Source	Target	Condition
ysi_debug :	ysi_debug : on	
ysi_debug :	ysi_debug : on	


#### Estimated stack usage
1 cells



### `Debug_IsStringLike`:


#### Syntax


```pawn
Debug_IsStringLike(addr, len)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 	A pointer to a thing that might be a string.	 |
| 	`len`	 | 	The maximum length of the supposed string.	 |

#### Tag
`bool:`


#### Returns
Prints a string passed as a vararg to the calling function.


#### Depends on
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
#### Estimated stack usage
3 cells



### `Debug_Kill_`:


#### Syntax


```pawn
Debug_Kill_()
```

#### Remarks
Stop the server running.


#### Estimated stack usage
1 cells



### `Debug_Level`:


#### Syntax


```pawn
Debug_Level(level)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`level`	 | 	The new debug level to enable prints on.	 |

#### Remarks
Set the debug level when the code is compiled with `_DEBUG=-1`, which means full run-time selection. Returns the level, or sets it when a parameter is given.


#### Depends on
* [`YSI_gDebugLevel`](#YSI_gDebugLevel)
#### Estimated stack usage
1 cells



### `Debug_Print0`:


#### Syntax


```pawn
Debug_Print0(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |
| 	`str`	 | 	The format specifier string.	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print0("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print0("variables: %d, %d", i, j);  
```

`_DEBUG` level 0 prints are ALWAYS compiled, but are runtime switched using the automata `ysi_debug`. When then state is `ysi_debug : on`, the prints are executed. When then state is `ysi_debug : off`, they aren't.

This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print0("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print0("variables: %d, %d", i, j);  
```

`_DEBUG` level 0 prints are ALWAYS compiled, but are runtime switched using the automata `ysi_debug`. When then state is `ysi_debug : on`, the prints are executed. When then state is `ysi_debug : off`, they aren't.

#### Depends on
* [`printf`](#printf)
#### Automaton
ysi_debug


#### Estimated stack usage
1 cells



### `Debug_Print1`:


#### Syntax


```pawn
Debug_Print1(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print1("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print1("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 1`.

#### Attributes
* `native`

### `Debug_Print2`:


#### Syntax


```pawn
Debug_Print2(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print2("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print2("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 2`.

#### Attributes
* `native`

### `Debug_Print3`:


#### Syntax


```pawn
Debug_Print3(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print3("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print3("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 3`.

#### Attributes
* `native`

### `Debug_Print4`:


#### Syntax


```pawn
Debug_Print4(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print4("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print4("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 4`.

#### Attributes
* `native`

### `Debug_Print5`:


#### Syntax


```pawn
Debug_Print5(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print5("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print5("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 5`.

#### Attributes
* `native`

### `Debug_Print6`:


#### Syntax


```pawn
Debug_Print6(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print6("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print6("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 6`.

#### Attributes
* `native`

### `Debug_Print7`:


#### Syntax


```pawn
Debug_Print7(str[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`str`	 | 	` [] ` The format specifier string.	 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
This isn't really a function as the first parameter is part of the name:

```pawn
  Debug_Print7("variables: %d, %d", i, j);  
```

Or:
```pawn
  Debug_Print7("variables: %d, %d", i, j);  
```

Only prints the data when `_DEBUG %gt;= 7`.

#### Attributes
* `native`

### `Debug_PrintArray`:


#### Syntax


```pawn
Debug_PrintArray(arr[], size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arr`	 | 	` [] `	 |
| 	`size`	 | 		 |

#### Remarks
Does some strange mangling of `YSI_FILTERSCRIPT` because at one point I found a compiler bug where the first automata in the script could conflict with the first variable in the script. I don't know what triggered it, and it has never shown up since I messed about with this file to try mangle some things. Never the less, if it ever happens again this code might detect it. Actually, that's less likely now, since that variable is now very unlikely to be the first in the script ever.


#### Depends on
* [`Debug_PrintArray`](#Debug_PrintArray)
* [`YSI_Format__`](#YSI_Format__)
#### Estimated stack usage
108 cells



### `Debug_PrintQ_IMPL`:


#### Syntax


```pawn
Debug_PrintQ_IMPL(tag, size, expr[], file[], line, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`tag`	 | 	`Debug_PrintQ_TAG `	 |
| 	`size`	 | 	`Debug_PrintQ_SIZEOF `	 |
| 	`expr`	 | 	` [] `	 |
| 	`file`	 | 	` [] `	 |
| 	`line`	 | 		 |
| 	`...`	 | 	` {_,Bit,Text,Group,File,Float,Text3D} `	 |

#### Remarks
Try and print a wide range of variables, with their source expression. Examples: new arr[] = {33, 33, 33}; new Float:farr[] = {11.0, 11.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0}; new MyCustomTag:mctarr[] = { MyCustomTag:6, MyCustomTag:7 }; new str[] = "hello"; new var1 = 2; new Float:f = 5.5; Debug_Q(str); Debug_Q(var1); Debug_Q(f); Debug_Q(arr); Debug_Q(farr, 7); Debug_Q(mctarr); If an array length cannot be determined you can pass it as a second arg. All tags are supported, the output from the above is: [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:16 str[6] = "hello" (full data dumped to: _fgdjkeGjAz.tmp) [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:17 var1 = 2 [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:18 Float:f = 5.500 [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:19 arr[3] = { 33, 33, 33 } [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:20 Float:farr[7] = { 11.000, 11.000, 11.000, 12.000, 13.000, ... } (full data dumped to: _HOf6OQgcC8.tmp) [Q] C:\Users\Alex\Documents\SA-MP\gamemodes\IsMaybeAString.pwn:21 MyCustomTag:mctarr[2] = { 6, 7 } Note: Temporary files are automatically deleted after a month.


#### Depends on
* [`AMX_GetTagByValue`](#AMX_GetTagByValue)
* [`Debug_IsStringLike`](#Debug_IsStringLike)
* [`Debug_PrintQ_PRINT`](#Debug_PrintQ_PRINT)
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_format`](#FIXES_format)
* [`FIXES_fwrite`](#FIXES_fwrite)
* [`YSI_PrintF__`](#YSI_PrintF__)
* [`__param5_offset`](#__param5_offset)
* [`ftemporary`](#ftemporary)
* [`getarg`](#getarg)
#### Estimated stack usage
150 cells



### `Debug_SetState`:


#### Syntax


```pawn
Debug_SetState()
```

#### Remarks
Mostly exists to define the full range of `ysi_debug` states.


Mostly exists to define the full range of `ysi_debug` states.


#### Automaton
ysi_debug


#### Transition table
Source	Target	Condition
ysi_debug :	ysi_debug : on	
ysi_debug :	ysi_debug : on	
on	


#### Estimated stack usage
1 cells



### `ScriptInit_OnCodeInit`:


#### Syntax


```pawn
ScriptInit_OnCodeInit()
```

#### Remarks
Does some strange mangling of `YSI_FILTERSCRIPT` because at one point I found a compiler bug where the first automata in the script could conflict with the first variable in the script. I don't know what triggered it, and it has never shown up since I messed about with this file to try mangle some things. Never the less, if it ever happens again this code might detect it. Actually, that's less likely now, since that variable is now very unlikely to be the first in the script ever.


#### Depends on
* [`@_`](#@_)
* [`Debug_Kill_`](#Debug_Kill_)
* [`Debug_Print0`](#Debug_Print0)
* [`Debug_SetState`](#Debug_SetState)
* [`__cip`](#__cip)
#### Attributes
* `public`
#### Estimated stack usage
5 cells


