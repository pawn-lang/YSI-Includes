#### Debug_Code
>* **Parameters:**
>	* `level`: level_INFO
>	* `code`: code_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Code is not a variable, it's a code chunk and may be written as so:
>	Debug_Code1(if (bla == 2) { bla++; printf("%d", bla); });
>	The code must all be on one line to avoid errors.
>	This isn't really a function as the first parameter is part of the name.
 
***

#### Debug_Print
>* **Parameters:**
>	* `level`: level_INFO
>	* `format[]`: format[]_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This isn't really a function as the first parameter is part of the name:
>	Debug_Print4("variables: %d, %d", i, j);
 
***

