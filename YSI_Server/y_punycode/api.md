#### Puny_Decode
>* **Parameters:**
>	* `dst`: dst_INFO
>	* `src`: src_INFO
>	* `wlen`: wlen_INFO
>	* `delimiter`: delimiter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Takes a punycode string and converts it to unicode.
 
***

#### Puny_Encode
>* **Parameters:**
>	* `dst`: dst_INFO
>	* `src`: src_INFO
>	* `wlen`: wlen_INFO
>	* `delimiter`: delimiter_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Takes a unicode string and converts it to punycode.
 
***

#### Puny_EncodeHash
>* **Parameters:**
>	* `dst`: dst_INFO
>	* `src`: src_INFO
>	* `hash`: hash_INFO
>	* `wlen`: wlen_INFO
>	* `delimiter`: delimiter_INFO
>* **Returns:**
>	* The length of string read.
>* **Remarks:**
>	Takes a unicode string and converts it to punycode, while at the same time
>	generating a Bernstein hash of the string.  CASE INSENSITIVE.
 
***

#### _Puny_Basic
>* **Parameters:**
>	* `num`: num_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Convert a single digit to base 36.
 
***

#### Puny_EncodeVarHash
>* **Parameters:**
>	* `bias`: bias_INFO
>	* `delta`: delta_INFO
>	* `dst`: dst_INFO
>	* `wlen`: wlen_INFO
>	* `hash`: hash_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is part of how the punycode algorithm encodes numbers as very clever
>	strings, but honestly I don't fully understand it!
 
***

#### Puny_EncodeVar
>* **Parameters:**
>	* `bias`: bias_INFO
>	* `delta`: delta_INFO
>	* `dst`: dst_INFO
>	* `wlen`: wlen_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is part of how the punycode algorithm encodes numbers as very clever
>	strings, but honestly I don't fully understand it!
 
***

#### Puny_Adapt
>* **Parameters:**
>	* `delta`: delta_INFO
>	* `length`: length_INFO
>	* `firstTime`: firstTime_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This is part of how the punycode algorithm encodes numbers as very clever
>	strings, but honestly I don't fully understand it!
 
***

#### Puny_HTTP
>* **Parameters:**
>	* `index`: index_INFO
>	* `type`: type_INFO
>	* `url[]`: url[]_INFO
>	* `data[]`: data[]_INFO
>	* `callback[]`: callback[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Hooks the "HTTP" function.
 
***

