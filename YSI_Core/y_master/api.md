## States

Each MASTER has several states.  I'm listing them here for reference (though they are internal really):

* y - The current script is the master.
* n - The current script is not the master.
* u - The current script will be the master because it has stolen it, but is still in the process of kicking the old master out.
* m - The current script was the master, but is now closing so needs to find a new one.
* p - The current script was the master, and a new one has now been found, so the data needs passing over.

## Functions

#### Master_GetNext
>* **Parameters:**

>* **Returns:**
>	* Next master ID to be assigned.
>* **Remarks:**
>	-
 
***

#### Master_Reassert
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Rebuilds the collection of master data whenever a script is restarted.
 
***

#### _Master_Get
>* **Parameters:**
>	* `library[]`: library[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

