y_amx - v1.0
==========================================

(c) 2022 YSI contibutors, licensed under MPL 1.1
------------------------------------------------

Allows a script access to information about itself, such as function names. This can be used for a range of things, including automatic callback hooking and testing. 







## Constants




### `EMIT_MINUS_16`:



-16, for use in `#emit` which fails with `-`. 



|  **Value**  |  `-16`  | 


#### Used by

* [`Callback_CallHandler_`](#Callback_CallHandler_)








### `EMIT_MINUS_28`:



-28, for use in `#emit` which fails with `-`. 



|  **Value**  |  `-28`  | 


#### Used by

* [`Hooks_RegisterNPSHook`](#Hooks_RegisterNPSHook)
* [`_yH@`](#_yH@)








### `EMIT_MINUS_4`:



-4, for use in `#emit` which fails with `-`. 



|  **Value**  |  `-4`  | 


#### Used by

* [`operator~(I@T:)`](#operator~(I@T:))
* [`Callback_CallHandler_`](#Callback_CallHandler_)








### `EMIT_MINUS_8`:



-8, for use in `#emit` which fails with `-`. 



|  **Value**  |  `-8`  | 


#### Used by

* [`Callback_CallHandler_`](#Callback_CallHandler_)
* [`Inline_GeneratePostamble`](#Inline_GeneratePostamble)





## Functions




### `AMX_Deref`:



#### Syntax


```pawn
AMX_Deref(addr)
```



|  `addr`  |  A DAT pointer.   | 




#### Returns

An array whose data is at `addr`. Converts a pointer to a pawn usable array. 


#### Used by
* [`Testing_Next`](#Testing_Next)
* [`Testing_RunAll`](#Testing_RunAll)

#### Depends on
* [`AMX_Deref`](#AMX_Deref)
* [`__param1_offset`](#__param1_offset)

#### Estimated stack usage

3 cells









### `AMX_DoNothing`:



#### Syntax


```pawn
AMX_DoNothing()
```




#### Remarks

A dummy function used to get the address of. 


#### Used by
* [`AMX_GetGlobal`](#AMX_GetGlobal)

#### Estimated stack usage

1 cells









### `AMX_DumpHeader`:



#### Syntax


```pawn
AMX_DumpHeader()
```




#### Remarks

Print all the names of all the public functions from the AMX header. There is now a more complete version of this function in amx_assembly called `PrintAmxHeader`. 


#### Depends on
* [`AMX_GetNameBinary`](#AMX_GetNameBinary)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`FUNCTION_LENGTH`](#FUNCTION_LENGTH)
* [`print`](#print)
* [`printf`](#printf)
* [`strunpack`](#strunpack)

#### Estimated stack usage

41 cells









### `AMX_GetBaseCount`:



#### Syntax


```pawn
AMX_GetBaseCount(table, &base, &count)
```



|  `table`  |  `E_AMX_TABLE `The table in the header (publics, tags, etc).   | 
|  `base`  |  ` & `Return for the start pointer.   | 
|  `count`  |  ` & `Return for the count.   | 




#### Remarks

Get information about one of the tables in the AMX header. These are lists of address/name pairs. The address is one cell long, and points to where in code/data/vm the corresponding symbol is located. The name is `defsize - cellbytes` long, which may not be exactly one cell (all of y_amx assumes that this value is known at compile-time, but amx_assembly more correctly reads it from the header), and points to the start of the name as a C string in the AMX header's nametable. This function just gets where in memory (relative to DAT) the table starts, and how many items there are in the table. 


#### Used by
* [`AMX_GetEntryBinary`](#AMX_GetEntryBinary)
* [`AMX_GetEntryLinear`](#AMX_GetEntryLinear)
* [`AMX_GetEntryPrefixBinary`](#AMX_GetEntryPrefixBinary)
* [`AMX_GetEntryPrefixLinear`](#AMX_GetEntryPrefixLinear)
* [`AMX_GetEntrySuffix`](#AMX_GetEntrySuffix)
* [`AMX_GetCount`](#AMX_GetCount)
* [`AMX_GetFirstNativeString`](#AMX_GetFirstNativeString)

#### Depends on
* [`AMX_HEADER_LIBRARIES`](#AMX_HEADER_LIBRARIES)
* [`AMX_HEADER_NAMETABLE`](#AMX_HEADER_NAMETABLE)
* [`AMX_HEADER_NATIVES`](#AMX_HEADER_NATIVES)
* [`AMX_HEADER_PUBLICS`](#AMX_HEADER_PUBLICS)
* [`AMX_HEADER_PUBVARS`](#AMX_HEADER_PUBVARS)
* [`AMX_HEADER_TAGS`](#AMX_HEADER_TAGS)
* [`AMX_TABLE_LIBRARIES`](#AMX_TABLE_LIBRARIES)
* [`AMX_TABLE_NATIVES`](#AMX_TABLE_NATIVES)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)
* [`AMX_TABLE_TAGS`](#AMX_TABLE_TAGS)
* [`__defsize_cells`](#__defsize_cells)

#### Estimated stack usage

1 cells









### `AMX_GetCount`:



#### Syntax


```pawn
AMX_GetCount(table)
```



|  `table`  |  `E_AMX_TABLE `Which table to get the size of.   | 




#### Returns

The number of entries in this table. 


#### Used by
* [`AMX_GetPubvarCount`](#AMX_GetPubvarCount)
* [`yQ_@y_amx_Libraries`](#yQ_@y_amx_Libraries)

#### Depends on
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)

#### Estimated stack usage

6 cells









### `AMX_GetEntryBinary`:



#### Syntax


```pawn
AMX_GetEntryBinary(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  ` [] `An optional name to look for.   | 
|  `exact`  |  `bool `When true find the pattern exactly, otherwise just include it.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find one matching the given name pattern, or just the next one when no pattern is given. Loop over all public functions with: 




```pawn
  new idx = 0, buffer;                            
  while ((idx = AMX_GetPublicEntry(idx, buffer))) 
  {                                               
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 


`AMX_GetPublicEntry` `AMX_GetPubVarEntry` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarEntry`](#AMX_GetPubvarEntry)
* [`AMX_GetNameBinary`](#AMX_GetNameBinary)
* [`AMX_GetPointerBinary`](#AMX_GetPointerBinary)
* [`Testing_Run`](#Testing_Run)
* [`Hooks_GetPreHooks`](#Hooks_GetPreHooks)
* [`Hooks_GetDefaultReturn`](#Hooks_GetDefaultReturn)
* [`y_hooks_funcidx2`](#y_hooks_funcidx2)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`Cell_ReverseBytes`](#Cell_ReverseBytes)
* [`FIXES_strcmp`](#FIXES_strcmp)
* [`FIXES_strfind`](#FIXES_strfind)
* [`FUNCTION_LENGTH`](#FUNCTION_LENGTH)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`cellbits`](#cellbits)
* [`cellbytes`](#cellbytes)
* [`cellmax`](#cellmax)

#### Estimated stack usage

45 cells









### `AMX_GetEntryFromNativeIndex`:



#### Syntax


```pawn
AMX_GetEntryFromNativeIndex(index)
```



|  `index`  |  The position in the native functions table.   | 




#### Returns

A pointer to this table entry. 


#### Depends on
* [`AMX_HEADER_NATIVES`](#AMX_HEADER_NATIVES)
* [`__defsize_cells`](#__defsize_cells)

#### Estimated stack usage

1 cells









### `AMX_GetEntryFromPublicIndex`:



#### Syntax


```pawn
AMX_GetEntryFromPublicIndex(index)
```



|  `index`  |  The position in the public functions table.   | 




#### Returns

A pointer to this table entry. 


#### Used by
* [`AMX_GetFirstNativeString`](#AMX_GetFirstNativeString)

#### Depends on
* [`AMX_HEADER_PUBLICS`](#AMX_HEADER_PUBLICS)
* [`__defsize_cells`](#__defsize_cells)

#### Estimated stack usage

1 cells









### `AMX_GetEntryLinear`:



#### Syntax


```pawn
AMX_GetEntryLinear(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  ` [] `An optional name to look for.   | 
|  `exact`  |  `bool `When true find the pattern exactly, otherwise just include it.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find one matching the given name pattern, or just the next one when no pattern is given. Loop over all libraries with: 




```pawn
  new idx = 0, buffer;                             
  while ((idx = AMX_GetLibraryEntry(idx, buffer))) 
  {                                                
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 


`AMX_GetNativeEntry` `AMX_GetLibraryEntry` `AMX_GetTagEntry` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Used by
* [`AMX_GetNameLinear`](#AMX_GetNameLinear)
* [`AMX_GetPointerLinear`](#AMX_GetPointerLinear)
* [`AMX_GetTagByValue`](#AMX_GetTagByValue)
* [`yQ_@y_amx_Libraries`](#yQ_@y_amx_Libraries)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`FIXES_strcmp`](#FIXES_strcmp)
* [`FIXES_strfind`](#FIXES_strfind)
* [`FUNCTION_LENGTH`](#FUNCTION_LENGTH)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

43 cells









### `AMX_GetEntryPointer`:



#### Syntax


```pawn
AMX_GetEntryPointer(tableEntry)
```



|  `tableEntry`  |  The table entry in the AMX header to use.   | 




#### Returns

The data pointer in this table (the first cell in the struct). 


#### Estimated stack usage

1 cells









### `AMX_GetEntryPrefixBinary`:



#### Syntax


```pawn
AMX_GetEntryPrefixBinary(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  A prefix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find one whose name starts with the given prefix. Prefixes are four bytes built from the first four characters in a name. Prefixes are used extensively for looping over special function types as they require no string decoding and so can be compared very quickly. The `_A` macro can be used to convert four characters in to the special format used by `pattern` (which is really just the C string as a 32-bit number). 



*y_hooks* uses this function to find all of its special hook functions, which start with the magic four character sequence `"@yH_"` (both a prefix for this function, and a public function declaration as it starts with `@`), like so: 



```pawn
  new idx = 0, buffer;                                            
  while ((idx = AMX_GetPublicEntryPrefix(idx, buffer, _A<@yH_>))) 
  {                                                               
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 


`AMX_GetPublicEntryPrefix` `AMX_GetPubVarEntryPrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


 Prefixes are widely used in YSI as the names are sorted and so can be binary searched, the entries point to the start of the names, and once a prefix is passed there can be no more later (thanks to sorting). Thus binary prefix searches are extremely efficient. 


#### Used by
* [`AMX_GetPubvarEntryPrefix`](#AMX_GetPubvarEntryPrefix)
* [`AMX_GetNamePrefixBinary`](#AMX_GetNamePrefixBinary)
* [`AMX_GetPointerPrefixBinary`](#AMX_GetPointerPrefixBinary)
* [`Testing_Run`](#Testing_Run)
* [`Testing_Next`](#Testing_Next)
* [`Hooks_GetPreloadLibraries`](#Hooks_GetPreloadLibraries)
* [`CGen_OnCodeInit`](#CGen_OnCodeInit)
* [`yQ_@y_master_Space`](#yQ_@y_master_Space)
* [`Yield_OnCodeInit`](#Yield_OnCodeInit)
* [`_@yHOnYSIInit@FP`](#_@yHOnYSIInit@FP)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`Cell_ReverseBytes`](#Cell_ReverseBytes)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

10 cells









### `AMX_GetEntryPrefixLinear`:



#### Syntax


```pawn
AMX_GetEntryPrefixLinear(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  A prefix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find one whose name starts with the given prefix. Prefixes are four bytes built from the first four characters in a name. Prefixes are used extensively for looping over special function types as they require no string decoding and so can be compared very quickly. The `_A` macro can be used to convert four characters in to the special format used by `pattern` (which is really just the C string as a 32-bit number). 



 All the special `Func:` tags which encode parameter types could be looped over like so: 



```pawn
  new idx = 0, buffer;                                         
  while ((idx = AMX_GetTagEntryPrefix(idx, buffer, _A<F@_@>))) 
  {                                                            
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 


`AMX_GetNativeEntryPrefix` `AMX_GetLibraryEntryPrefix` `AMX_GetTagEntryPrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Used by
* [`AMX_GetNamePrefixLinear`](#AMX_GetNamePrefixLinear)
* [`AMX_GetPointerPrefixLinear`](#AMX_GetPointerPrefixLinear)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

10 cells









### `AMX_GetEntrySuffix`:



#### Syntax


```pawn
AMX_GetEntrySuffix(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through any table to look for names ending with the given four byte suffix. These suffixes are defined in the same way as the prefixes used by `AMX_GetPublicEntryPrefix` et. al, but the scanning is much harder because the full names must all be read. Unlike prefix scanning, suffix scanning is very inefficient. Returns the table entry. 


#### Used by
* [`AMX_GetPubvarEntrySuffix`](#AMX_GetPubvarEntrySuffix)
* [`AMX_GetNameSuffix`](#AMX_GetNameSuffix)
* [`AMX_GetPointerSuffix`](#AMX_GetPointerSuffix)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`__defsize_cells`](#__defsize_cells)
* [`cellbits`](#cellbits)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

10 cells









### `AMX_GetFirstNativeString`:



#### Syntax


```pawn
AMX_GetFirstNativeString()
```




#### Returns

The address in the nametable of the first string name referenced by this table. Same as `AMX_GetFirstString`, but specialised for natives as their pointers may be clobbered in some VM versions. 


#### Used by
* [`AMX_GetPublicStringSpace`](#AMX_GetPublicStringSpace)
* [`AMX_GetNativeStringSpace`](#AMX_GetNativeStringSpace)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetBaseCount`](#AMX_GetBaseCount)
* [`AMX_GetEntryFromPublicIndex`](#AMX_GetEntryFromPublicIndex)
* [`AMX_ReadLength`](#AMX_ReadLength)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

8 cells









### `AMX_GetFirstString`:



#### Syntax


```pawn
AMX_GetFirstString(table)
```



|  `table`  |  `E_AMX_TABLE `Which header table to report on.   | 




#### Returns

The address in the nametable of the first string name referenced by this table. Should be called via the table-specific wrappers: 



`AMX_GetFirstPublicString` `AMX_GetFirstLibraryString` `AMX_GetFirstPubVarString` `AMX_GetFirstTagString` 


#### Used by
* [`AMX_GetPublicStringSpace`](#AMX_GetPublicStringSpace)
* [`AMX_GetNativeStringSpace`](#AMX_GetNativeStringSpace)
* [`AMX_GetLibraryStringSpace`](#AMX_GetLibraryStringSpace)
* [`AMX_GetPubVarStringSpace`](#AMX_GetPubVarStringSpace)
* [`AMX_GetTagStringSpace`](#AMX_GetTagStringSpace)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

1 cells









### `AMX_GetGlobal`:



#### Syntax


```pawn
AMX_GetGlobal()
```




#### Returns

The address of the AMX in the server. 


#### Used by
* [`Debug_OnCodeInit`](#Debug_OnCodeInit)

#### Depends on
* [`AMX_DoNothing`](#AMX_DoNothing)
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`__cip`](#__cip)
* [`__dat`](#__dat)
* [`__m3_cells`](#__m3_cells)

#### Estimated stack usage

4 cells









### `AMX_GetGlobalAddress`:



#### Syntax


```pawn
AMX_GetGlobalAddress(...)
```



|  `...`  |    | 




#### Returns

The passed address, in the server not the AMX. 


#### Depends on
* [`AMX_REAL_DATA`](#AMX_REAL_DATA)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__args_offset`](#__args_offset)
* [`__param0_offset`](#__param0_offset)

#### Estimated stack usage

2 cells









### `AMX_GetLengthFromEntry`:



#### Syntax


```pawn
AMX_GetLengthFromEntry(tableEntry)
```



|  `tableEntry`  |  The AMX header table entry to use.   | 




#### Returns

The length of the name of this entry. 


#### Used by
* [`CGen_OnCodeInit`](#CGen_OnCodeInit)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_ReadLength`](#AMX_ReadLength)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

4 cells









### `AMX_GetLibraryStringSpace`:



#### Syntax


```pawn
AMX_GetLibraryStringSpace()
```




#### Returns

The number of bytes used by all library names in the nametable. 


#### Used by
* [`yQ_@y_master_Space`](#yQ_@y_master_Space)

#### Depends on
* [`AMX_GetFirstString`](#AMX_GetFirstString)
* [`AMX_TABLE_LIBRARIES`](#AMX_TABLE_LIBRARIES)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

4 cells









### `AMX_GetNameBinary`:



#### Syntax


```pawn
AMX_GetNameBinary(table, idx, buffer[], pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed sring.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find one whose name contains the given pattern, or all of them when there is no pattern. Loop over all the defined player callbacks like so: 




```pawn
  new idx = 0, buffer[FUNCTION_LENGTH];                             
  while ((idx = AMX_GetPublicName(idx, buffer, "OnPlayer", false))) 
  {                                                                 
  }  
```




 You should not use this function directly, but one of the macro wrappers defined for sorted tables: 


`AMX_GetPublicNamePrefix` `AMX_GetPubVarNamePrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarName`](#AMX_GetPubvarName)
* [`AMX_DumpHeader`](#AMX_DumpHeader)
* [`y_hooks_funcidx2`](#y_hooks_funcidx2)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntryBinary`](#AMX_GetEntryBinary)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

9 cells









### `AMX_GetNameLinear`:



#### Syntax


```pawn
AMX_GetNameLinear(table, idx, buffer[], pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed sring.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find one whose name contains the given pattern, or all of them when there is no pattern. Loop over all the defined player callbacks like so: 




```pawn
  new idx = 0, buffer[FUNCTION_LENGTH];                             
  while ((idx = AMX_GetPublicName(idx, buffer, "OnPlayer", false))) 
  {                                                                 
  }  
```




 You should not use this function directly, but one of the macro wrappers defined for sorted tables: 


`AMX_GetNativeNameLinear` `AMX_GetLibraryNameLinear` `AMX_GetTagNameLinear` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntryLinear`](#AMX_GetEntryLinear)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

9 cells









### `AMX_GetNamePrefixBinary`:



#### Syntax


```pawn
AMX_GetNamePrefixBinary(table, idx, buffer[], pattern)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed string.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find the next entry matching the given prefix, and returns the full name of the entry. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 



`AMX_GetPublicNamePrefix` `AMX_GetPubVarNamePrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarNamePrefix`](#AMX_GetPubvarNamePrefix)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntryPrefixBinary`](#AMX_GetEntryPrefixBinary)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

8 cells









### `AMX_GetNamePrefixLinear`:



#### Syntax


```pawn
AMX_GetNamePrefixLinear(table, idx, buffer[], pattern)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed string.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find the next entry matching the given prefix, and returns the full name of the entry. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 



`AMX_GetNativeNamePrefix` `AMX_GetLibraryNamePrefix` `AMX_GetTagNamePrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntryPrefixLinear`](#AMX_GetEntryPrefixLinear)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

8 cells









### `AMX_GetNameSuffix`:



#### Syntax


```pawn
AMX_GetNameSuffix(table, idx, buffer[], pattern)
```



|  `table`  |  `E_AMX_TABLE `Which table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed sring.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through any table to look for names ending with the given four byte suffix. These suffixes are defined in the same way as the prefixes used by `AMX_GetPublicEntryPrefix` et. al, but the scanning is much harder because the full names must all be read. Unlike prefix scanning, suffix scanning is very inefficient. Returns the full name. 


#### Used by
* [`AMX_GetPubvarNameSuffix`](#AMX_GetPubvarNameSuffix)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntrySuffix`](#AMX_GetEntrySuffix)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

8 cells









### `AMX_GetNativeIndexFromEntry`:



#### Syntax


```pawn
AMX_GetNativeIndexFromEntry(tableEntry)
```



|  `tableEntry`  |  The AMX header native function entry to use.   | 




#### Returns

The index (i.e the position in the table) of this native function entry. 


#### Depends on
* [`AMX_HEADER_NATIVES`](#AMX_HEADER_NATIVES)
* [`__defsize_cells`](#__defsize_cells)

#### Estimated stack usage

1 cells









### `AMX_GetNativeStringSpace`:



#### Syntax


```pawn
AMX_GetNativeStringSpace()
```




#### Returns

The number of bytes used by all native function names in the nametable. 


#### Used by
* [`yQ_@y_master_Space`](#yQ_@y_master_Space)

#### Depends on
* [`AMX_GetFirstNativeString`](#AMX_GetFirstNativeString)
* [`AMX_GetFirstString`](#AMX_GetFirstString)
* [`AMX_TABLE_LIBRARIES`](#AMX_TABLE_LIBRARIES)

#### Estimated stack usage

4 cells









### `AMX_GetPointerBinary`:



#### Syntax


```pawn
AMX_GetPointerBinary(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find one whose name includes or exactly matches the given pattern. The return value is the pointer from in the entry, not the entry itself, nor the data the pointer references (e.g. a funcion). You should not use this function directly, but one of the macro wrappers defined for sorted tables: 



`AMX_GetPublicPointer` `AMX_GetPubVarPointer` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Used by
* [`AMX_GetPubvarPointer`](#AMX_GetPubvarPointer)
* [`AMX_GetValueBinary`](#AMX_GetValueBinary)
* [`CTRL_FoundLCTRL`](#CTRL_FoundLCTRL)
* [`CTRL_FoundSCTRL`](#CTRL_FoundSCTRL)

#### Depends on
* [`AMX_GetEntryBinary`](#AMX_GetEntryBinary)

#### Estimated stack usage

9 cells









### `AMX_GetPointerLinear`:



#### Syntax


```pawn
AMX_GetPointerLinear(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find one whose name includes or exactly matches the given pattern. The return value is the pointer from in the entry, not the entry itself, nor the data the pointer references (e.g. a funcion). You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 



`AMX_GetNativePointer` `AMX_GetLibraryPointer` `AMX_GetTagPointer` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Used by
* [`AMX_GetValueLinear`](#AMX_GetValueLinear)

#### Depends on
* [`AMX_GetEntryLinear`](#AMX_GetEntryLinear)

#### Estimated stack usage

9 cells









### `AMX_GetPointerPrefixBinary`:



#### Syntax


```pawn
AMX_GetPointerPrefixBinary(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find the next entry matching the given prefix, and returns a pointer to the data. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 



`AMX_GetPublicPointerPrefix` `AMX_GetPubVarPointerPrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarPointerPrefix`](#AMX_GetPubvarPointerPrefix)
* [`AMX_GetValuePrefixBinary`](#AMX_GetValuePrefixBinary)
* [`ScriptInit_CodeInitFuncs_`](#ScriptInit_CodeInitFuncs_)
* [`ScriptInit_MainInitFuncs_`](#ScriptInit_MainInitFuncs_)
* [`ScriptInit_PreInitFuncs_`](#ScriptInit_PreInitFuncs_)
* [`ScriptInit_PostInitFuncs_`](#ScriptInit_PostInitFuncs_)
* [`ScriptInit_PreExitFuncs_`](#ScriptInit_PreExitFuncs_)
* [`ScriptInit_PostExitFuncs_`](#ScriptInit_PostExitFuncs_)
* [`Yield_OnCodeInit`](#Yield_OnCodeInit)
* [`Timers_OnCodeInit`](#Timers_OnCodeInit)
* [`_@yHOnYSIInit@FN`](#_@yHOnYSIInit@FN)
* [`_yGITest`](#_yGITest)
* [`_yGIYCMD`](#_yGIYCMD)

#### Depends on
* [`AMX_GetEntryPrefixBinary`](#AMX_GetEntryPrefixBinary)

#### Estimated stack usage

8 cells









### `AMX_GetPointerPrefixLinear`:



#### Syntax


```pawn
AMX_GetPointerPrefixLinear(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find the next entry matching the given prefix, and returns a pointer to the data. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 



`AMX_GetNativePointerPrefix` `AMX_GetLibraryPointerPrefix` `AMX_GetTagPointerPrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Used by
* [`AMX_GetValuePrefixLinear`](#AMX_GetValuePrefixLinear)

#### Depends on
* [`AMX_GetEntryPrefixLinear`](#AMX_GetEntryPrefixLinear)

#### Estimated stack usage

8 cells









### `AMX_GetPointerSuffix`:



#### Syntax


```pawn
AMX_GetPointerSuffix(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data pointer return value.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through any table to look for names ending with the given four byte suffix. These suffixes are defined in the same way as the prefixes used by `AMX_GetPublicEntryPrefix` et. al, but the scanning is much harder because the full names must all be read. Unlike prefix scanning, suffix scanning is very inefficient. Returns the data pointer. 


#### Used by
* [`AMX_GetPubvarPointerSuffix`](#AMX_GetPubvarPointerSuffix)
* [`AMX_GetValueSuffix`](#AMX_GetValueSuffix)

#### Depends on
* [`AMX_GetEntrySuffix`](#AMX_GetEntrySuffix)

#### Estimated stack usage

8 cells









### `AMX_GetPubVarStringSpace`:



#### Syntax


```pawn
AMX_GetPubVarStringSpace()
```




#### Returns

The number of bytes used by all public variable names in the nametable. 


#### Depends on
* [`AMX_GetFirstString`](#AMX_GetFirstString)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)
* [`AMX_TABLE_TAGS`](#AMX_TABLE_TAGS)

#### Estimated stack usage

4 cells









### `AMX_GetPublicIndexFromEntry`:



#### Syntax


```pawn
AMX_GetPublicIndexFromEntry(tableEntry)
```



|  `tableEntry`  |  The AMX header public function entry to use.   | 




#### Returns

The index (i.e the position in the table) of this public function entry. 


#### Remarks

The value returned corresponds to the return value of `funcidx`. 


#### Depends on
* [`AMX_HEADER_PUBLICS`](#AMX_HEADER_PUBLICS)
* [`__defsize_cells`](#__defsize_cells)

#### Estimated stack usage

1 cells









### `AMX_GetPublicStringSpace`:



#### Syntax


```pawn
AMX_GetPublicStringSpace()
```




#### Returns

The number of bytes used by all public function names in the nametable. 


#### Depends on
* [`AMX_GetFirstNativeString`](#AMX_GetFirstNativeString)
* [`AMX_GetFirstString`](#AMX_GetFirstString)
* [`AMX_TABLE_PUBLICS`](#AMX_TABLE_PUBLICS)

#### Estimated stack usage

4 cells









### `AMX_GetPubvarCount`:



#### Syntax


```pawn
AMX_GetPubvarCount()
```




#### Returns

The number of entries in this table. 


#### Depends on
* [`AMX_GetCount`](#AMX_GetCount)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

4 cells









### `AMX_GetPubvarEntry`:



#### Syntax


```pawn
AMX_GetPubvarEntry(idx, &buffer, pattern[], exact)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  ` [] `An optional name to look for.   | 
|  `exact`  |  `bool `When true find the pattern exactly, otherwise just include it.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the public variables table to find one matching the given name pattern, or just the next one when no pattern is given. Loop over all public variables with: 




```pawn
  new idx = 0, buffer;                            
  while ((idx = AMX_GetPubvarEntry(idx, buffer))) 
  {                                               
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. 


#### Depends on
* [`AMX_GetEntryBinary`](#AMX_GetEntryBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

8 cells









### `AMX_GetPubvarEntryPrefix`:



#### Syntax


```pawn
AMX_GetPubvarEntryPrefix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  A prefix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the public variables table to find one whose name starts with the given prefix. Prefixes are four bytes built from the first four characters in a name. Prefixes are used extensively for looping over special function types as they require no string decoding and so can be compared very quickly. The `_A` macro can be used to convert four characters in to the special format used by `pattern` (which is really just the C string as a 32-bit number). 



 To loop over all public variables that start with `"var_"`: 



```pawn
  new idx = 0, buffer;                                            
  while ((idx = AMX_GetPubvarEntryPrefix(idx, buffer, _A<var_>))) 
  {                                                               
  }  
```




 The *entry* is a pointer in to the table itself, i.e. address/name pair relative to `DAT`. 


#### Depends on
* [`AMX_GetEntryPrefixBinary`](#AMX_GetEntryPrefixBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarEntrySuffix`:



#### Syntax


```pawn
AMX_GetPubvarEntrySuffix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The return value, with a pointer to a table entry.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See *AMX_GetEntrySuffix*. 


#### Depends on
* [`AMX_GetEntrySuffix`](#AMX_GetEntrySuffix)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarName`:



#### Syntax


```pawn
AMX_GetPubvarName(idx, buffer[], pattern[], exact)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed sring.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See *AMX_GetNameBinary*. 


#### Depends on
* [`AMX_GetNameBinary`](#AMX_GetNameBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

8 cells









### `AMX_GetPubvarNamePrefix`:



#### Syntax


```pawn
AMX_GetPubvarNamePrefix(idx, buffer[], pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed string.   | 
|  `pattern`  |  A prefix to scan for.   | 
|  `table`  |  Which sorted table to scan through.  | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See `AMX_GetNamePrefixBinary` 


#### Depends on
* [`AMX_GetNamePrefixBinary`](#AMX_GetNamePrefixBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarNameSuffix`:



#### Syntax


```pawn
AMX_GetPubvarNameSuffix(idx, buffer[], pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` [32] `The name return value, as a packed sring.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See *AMX_GetNameSuffix*. 


#### Depends on
* [`AMX_GetNameSuffix`](#AMX_GetNameSuffix)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarPointer`:



#### Syntax


```pawn
AMX_GetPubvarPointer(idx, &buffer, pattern[], exact)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 
|  `table`  |  Which unsorted table to scan through.  | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See `AMX_GetPointerBinary`. 


#### Depends on
* [`AMX_GetPointerBinary`](#AMX_GetPointerBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

8 cells









### `AMX_GetPubvarPointerPrefix`:



#### Syntax


```pawn
AMX_GetPubvarPointerPrefix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The pointer return value.   | 
|  `pattern`  |  A prefix to scan for.   | 
|  `table`  |  Which unsorted table to scan through.  | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See `AMX_GetPointerPrefixBinary` 


#### Depends on
* [`AMX_GetPointerPrefixBinary`](#AMX_GetPointerPrefixBinary)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarPointerSuffix`:



#### Syntax


```pawn
AMX_GetPubvarPointerSuffix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data pointer return value.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See *AMX_GetPointerSuffix*. 


#### Depends on
* [`AMX_GetPointerSuffix`](#AMX_GetPointerSuffix)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarValue`:



#### Syntax


```pawn
AMX_GetPubvarValue(idx, &buffer, pattern[], exact)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 
|  `table`  |  Which sorted table to scan through.  | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See `AMX_GetValueBinary`. 


#### Depends on
* [`AMX_GetValueBinary`](#AMX_GetValueBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

8 cells









### `AMX_GetPubvarValuePrefix`:



#### Syntax


```pawn
AMX_GetPubvarValuePrefix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See `AMX_GetValuePrefixBinary`. 


#### Depends on
* [`AMX_GetValuePrefixBinary`](#AMX_GetValuePrefixBinary)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetPubvarValueSuffix`:



#### Syntax


```pawn
AMX_GetPubvarValueSuffix(idx, &buffer, pattern)
```



|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

See *AMX_GetNameSuffix*. 


#### Depends on
* [`AMX_GetValueSuffix`](#AMX_GetValueSuffix)
* [`AMX_TABLE_PUBVARS`](#AMX_TABLE_PUBVARS)

#### Estimated stack usage

7 cells









### `AMX_GetRelativeAddress`:



#### Syntax


```pawn
AMX_GetRelativeAddress(...)
```



|  `...`  |    | 




#### Returns

The passed address in the AMX. 


#### Depends on
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__args_offset`](#__args_offset)
* [`__param0_offset`](#__param0_offset)

#### Estimated stack usage

2 cells









### `AMX_GetStringFromEntry`:



#### Syntax


```pawn
AMX_GetStringFromEntry(tableEntry, str[], size)
```



|  `tableEntry`  |  The header entry that has a name pointer.   | 
|  `str`  |  ` [] `The destination array.   | 
|  `size`  |  The size of the destination array.   | 




#### Returns




#### Remarks

Copies a C string in AMX memory out to a packed string. The pointer does not point straight to the string, but instead points to a header *entry*, i.e. part of a table with a data pointer and a name pointer. This thus abstracts the weirdness of the size of the name pointer, which may not be a whole cell. There is no unpacked equivalent. 


#### Used by
* [`Testing_Run`](#Testing_Run)
* [`Testing_Next`](#Testing_Next)
* [`Hooks_GetPreloadLibraries`](#Hooks_GetPreloadLibraries)
* [`Yield_OnCodeInit`](#Yield_OnCodeInit)
* [`_@yHOnYSIInit@FP`](#_@yHOnYSIInit@FP)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

6 cells









### `AMX_GetTagByValue`:



#### Syntax


```pawn
AMX_GetTagByValue(tag, name[], len)
```



|  `tag`  |  The tag value to look up (e.g. from `tagof`).   | 
|  `name`  |  ` [] `The destination for the name.   | 
|  `len`  |  The destination size.   | 




#### Remarks

Get the original string (code) name of a tag from its ID. 


#### Used by
* [`Debug_PrintQ_IMPL`](#Debug_PrintQ_IMPL)

#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetEntryLinear`](#AMX_GetEntryLinear)
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)
* [`AMX_TABLE_TAGS`](#AMX_TABLE_TAGS)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)
* [`strunpack`](#strunpack)

#### Estimated stack usage

11 cells









### `AMX_GetTagStringSpace`:



#### Syntax


```pawn
AMX_GetTagStringSpace()
```




#### Returns

The number of bytes used by all tag names in the nametable. 


#### Depends on
* [`AMX_BASE_ADDRESS`](#AMX_BASE_ADDRESS)
* [`AMX_GetFirstString`](#AMX_GetFirstString)
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AMX_TABLE_TAGS`](#AMX_TABLE_TAGS)

#### Estimated stack usage

4 cells









### `AMX_GetValueBinary`:



#### Syntax


```pawn
AMX_GetValueBinary(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find one whose name includes or exactly matches the given pattern. The return value is the data pointed to by the entry. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 



`AMX_GetPublicValue` `AMX_GetPubVarValue` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarValue`](#AMX_GetPubvarValue)

#### Depends on
* [`AMX_GetPointerBinary`](#AMX_GetPointerBinary)

#### Estimated stack usage

9 cells









### `AMX_GetValueLinear`:



#### Syntax


```pawn
AMX_GetValueLinear(table, idx, &buffer, pattern[], exact)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  ` [] `A prefix to look for.   | 
|  `exact`  |  `bool `True to match the pattern exactly, false for contains.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find one whose name includes or exactly matches the given pattern. The return value is the data pointed to by the entry. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 



`AMX_GetNativeValue` `AMX_GetLibraryValue` `AMX_GetTagValue` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Depends on
* [`AMX_GetPointerLinear`](#AMX_GetPointerLinear)

#### Estimated stack usage

9 cells









### `AMX_GetValuePrefixBinary`:



#### Syntax


```pawn
AMX_GetValuePrefixBinary(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which sorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given sorted table to find the next entry matching the given prefix, and returns the data pointed to by that entry. You should not use this function directly, but one of the macro wrappers defined for sorted tables: 



`AMX_GetPublicValuePrefix` `AMX_GetPubVarValuePrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. 


#### Used by
* [`AMX_GetPubvarValuePrefix`](#AMX_GetPubvarValuePrefix)

#### Depends on
* [`AMX_GetPointerPrefixBinary`](#AMX_GetPointerPrefixBinary)

#### Estimated stack usage

8 cells









### `AMX_GetValuePrefixLinear`:



#### Syntax


```pawn
AMX_GetValuePrefixLinear(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which unsorted table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  A prefix to scan for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through the given unsorted table to find the next entry matching the given prefix, and returns the data pointed to by that entry. You should not use this function directly, but one of the macro wrappers defined for unsorted tables: 



`AMX_GetNativeValuePrefix` `AMX_GetLibraryValuePrefix` `AMX_GetTagValuePrefix` 


 Note that amx_assembly now sorts the library and tag headers, so those could be binary searched, but this library cannot rely on that. Also note that the native name searches may not currently work correctly in all VM versions due to data clobbering. 


#### Depends on
* [`AMX_GetPointerPrefixLinear`](#AMX_GetPointerPrefixLinear)

#### Estimated stack usage

8 cells









### `AMX_GetValueSuffix`:



#### Syntax


```pawn
AMX_GetValueSuffix(table, idx, &buffer, pattern)
```



|  `table`  |  `E_AMX_TABLE `Which table to scan through.   | 
|  `idx`  |  When iterating, the offset to start at.   | 
|  `buffer`  |  ` & `The data return value.   | 
|  `pattern`  |  A suffix to look for.   | 




#### Returns

The next index (`idx`) to continue scanning from, or `0`. 


#### Remarks

This scans through any table to look for names ending with the given four byte suffix. These suffixes are defined in the same way as the prefixes used by `AMX_GetPublicEntryPrefix` et. al, but the scanning is much harder because the full names must all be read. Unlike prefix scanning, suffix scanning is very inefficient. Returns data from the data pointer. 


#### Used by
* [`AMX_GetPubvarValueSuffix`](#AMX_GetPubvarValueSuffix)

#### Depends on
* [`AMX_GetPointerSuffix`](#AMX_GetPointerSuffix)

#### Estimated stack usage

8 cells









### `AMX_ReadArray`:



#### Syntax


```pawn
AMX_ReadArray(addr, dest[], len)
```



|  `addr`  |  Data source address.   | 
|  `dest`  |  ` [] `Where to copy the data to.   | 
|  `len`  |  Amount of data to copy.   | 




#### Remarks

Read data out of a memory location, which may be outside the bounds of DAT. 


#### Depends on
* [`__1_cell`](#__1_cell)

#### Estimated stack usage

1 cells









### `AMX_ReadLength`:



#### Syntax


```pawn
AMX_ReadLength(addr)
```



|  `addr`  |  Pointer to a C string.   | 




#### Returns

The length of the string. 


#### Remarks

Operates on C strings, as found in the header, not pawn packed strings, which have their bytes reversed in a cell. 


#### Used by
* [`AMX_GetLengthFromEntry`](#AMX_GetLengthFromEntry)
* [`AMX_GetFirstNativeString`](#AMX_GetFirstNativeString)

#### Depends on
* [`YSI_g_c80s`](#YSI_g_c80s)
* [`YSI_g_cFEs`](#YSI_g_cFEs)
* [`cellbits`](#cellbits)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

3 cells









### `AMX_ReadPackedString`:



#### Syntax


```pawn
AMX_ReadPackedString(addr, str[], len)
```



|  `addr`  |  Where in DAT to read the string from.   | 
|  `str`  |  ` [] `The destination array.   | 
|  `len`  |  The size of the destination array.   | 




#### Returns




#### Remarks

Copies a C string in AMX memory out to a packed string. Mainly used to read function names from the header, as they are not in pawn order. Uses a clever trick to detect `NULL` in four bytes at once. 


#### Used by
* [`AMX_GetEntryBinary`](#AMX_GetEntryBinary)
* [`AMX_GetEntryLinear`](#AMX_GetEntryLinear)
* [`AMX_GetNameBinary`](#AMX_GetNameBinary)
* [`AMX_GetNameLinear`](#AMX_GetNameLinear)
* [`AMX_GetNamePrefixBinary`](#AMX_GetNamePrefixBinary)
* [`AMX_GetNamePrefixLinear`](#AMX_GetNamePrefixLinear)
* [`AMX_GetNameSuffix`](#AMX_GetNameSuffix)
* [`AMX_GetStringFromEntry`](#AMX_GetStringFromEntry)
* [`AMX_ReadString`](#AMX_ReadString)
* [`AMX_GetTagByValue`](#AMX_GetTagByValue)
* [`yQ_@y_amx_StringRead2B`](#yQ_@y_amx_StringRead2B)
* [`Hooks_Collate`](#Hooks_Collate)

#### Depends on
* [`YSI_g_c80s`](#YSI_g_c80s)
* [`YSI_g_cFEs`](#YSI_g_cFEs)
* [`cellbytes`](#cellbytes)
* [`swapchars`](#swapchars)

#### Estimated stack usage

5 cells









### `AMX_ReadString`:



#### Syntax


```pawn
AMX_ReadString(addr, str[], len)
```



|  `addr`  |  Where in DAT to read the string from.   | 
|  `str`  |  ` [] `The destination array.   | 
|  `len`  |  The size of the destination array.   | 




#### Returns




#### Remarks

Copies a C string in AMX memory out to a packed string. Mainly used to read function names from the header, as they are not in pawn order. Uses a clever trick to detect `NULL` in four bytes at once. Deprecated name. 


#### Used by
* [`yQ_@y_amx_StringRead1B`](#yQ_@y_amx_StringRead1B)

#### Depends on
* [`AMX_ReadPackedString`](#AMX_ReadPackedString)

#### Estimated stack usage

6 cells









### `AMX_ReadUnpackedString`:



#### Syntax


```pawn
AMX_ReadUnpackedString(addr, str[], len)
```



|  `addr`  |  Where in DAT to read the string from.   | 
|  `str`  |  ` [] `The destination array.   | 
|  `len`  |  The size of the destination array.   | 




#### Returns




#### Remarks

Copies a C string in AMX memory out to an unpacked string. Mainly used to read function names from the header, as they are not in pawn order. 


#### Used by
* [`yQ_@y_amx_StringRead3B`](#yQ_@y_amx_StringRead3B)

#### Depends on
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

3 cells









### `AMX_TraceCode`:



#### Syntax


```pawn
AMX_TraceCode(pattern[], &addrRet, &dataRet, size)
```



|  `pattern`  |  ` [] `The pattern to scan for in code.   | 
|  `addrRet`  |  ` & `The return for the address.   | 
|  `dataRet`  |  ` & `The return for the parameter.   | 
|  `size`  |  The size of the pattern.   | 




#### Remarks

An extremely poor-mans version of codescan. Just takes a pure array of opcodes and searches for it in memory. No data wildcards, no stack tracing, no opcode value lookup, etc. Returns the next cell after the end of a found pattern as if it were an opcode parameter. 


#### Depends on
* [`AMX_HEADER_COD`](#AMX_HEADER_COD)
* [`AMX_HEADER_DAT`](#AMX_HEADER_DAT)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

3 cells









### `AMX_TraceMemory`:



#### Syntax


```pawn
AMX_TraceMemory(pattern[], &addrRet, &dataRet, size)
```



|  `pattern`  |  ` [] `The pattern to scan for in data.   | 
|  `addrRet`  |  ` & `The return for the address.   | 
|  `dataRet`  |  ` & `The return for the parameter.   | 
|  `size`  |  The size of the pattern.   | 




#### Remarks

Search for the given pattern in the data segment. Return the address of the match and the data immediately following the match. 


#### Depends on
* [`AMX_HEADER_DAT`](#AMX_HEADER_DAT)
* [`AMX_HEADER_HEA`](#AMX_HEADER_HEA)
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)
* [`cellbytes`](#cellbytes)

#### Estimated stack usage

3 cells









### `AMX_WriteArray`:



#### Syntax


```pawn
AMX_WriteArray(addr, src[], len)
```



|  `addr`  |  Where to copy the data to.   | 
|  `src`  |  ` [] `Data source.   | 
|  `len`  |  Amount of data to copy.   | 




#### Remarks

Write data to a memory location, which may be outside the bounds of DAT. 


#### Depends on
* [`__1_cell`](#__1_cell)

#### Estimated stack usage

1 cells









### `AMX_WritePackedString`:



#### Syntax


```pawn
AMX_WritePackedString(addr, str[])
```



|  `addr`  |  Where in DAT to write the string to.   | 
|  `str`  |  ` [] `The packed string to write.   | 




#### Returns




#### Remarks

Copies a packed string in to AMX memory, as a C string. Mainly used to write function names in to the header, as they are not in pawn order. 


#### Depends on
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)

#### Estimated stack usage

4 cells









### `AMX_WriteUnpackedString`:



#### Syntax


```pawn
AMX_WriteUnpackedString(addr, str[])
```



|  `addr`  |  Where in DAT to write the string to.   | 
|  `str`  |  ` [] `The unpacked string to write.   | 




#### Returns




#### Remarks

Copies an unpacked string in to AMX memory, as a C string. Mainly used to write function names in to the header, as they are not in pawn order. 


#### Used by
* [`yQ_@y_amx_StringRead1B`](#yQ_@y_amx_StringRead1B)
* [`yQ_@y_amx_StringRead2B`](#yQ_@y_amx_StringRead2B)
* [`yQ_@y_amx_StringRead3B`](#yQ_@y_amx_StringRead3B)
* [`Hooks_GetPointerRewrite`](#Hooks_GetPointerRewrite)

#### Depends on
* [`YSI_gAMXAddress_`](#YSI_gAMXAddress_)

#### Estimated stack usage

4 cells



