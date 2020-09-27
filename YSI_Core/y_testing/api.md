#### Testing_Ask
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `str[]`: str[]_INFO
>	* `va_args<>`: va_args<>_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Calls a dialog to ask the player if the given test actually passed.
 
***

#### Testing_Run
>* **Parameters:**
>	* `&tests`: &tests_INFO
>	* `&fails`: &fails_INFO
>	* `buffer[33]`: buffer[33]_INFO
>* **Returns:**
>	* Wether all tests were sucessful or not.
>* **Remarks:**
>	-
>	native Testing_Run(&tests, &fails, buffer[33] = "");
 
***

#### Testing_Player
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `&idx`: &idx_INFO
>	* `&tests`: &tests_INFO
>	* `&fails`: &fails_INFO
>	* `buffer[33]`: buffer[33]_INFO
>* **Returns:**
>	* Wether all tests were sucessful or not.
>* **Remarks:**
>	-
>	native Testing_Run(&tests, &fails, buffer[33] = "");
 
***

