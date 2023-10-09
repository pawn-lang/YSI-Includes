# Quick Start

y_bit allows for simple compressed storage of boolean (true/false) values. A single cell has 32 bits yet is often used to store just one "bool:", wasting 31 bits (around 97% of the memory). Thus, better use can be made by storing 32 bits in one cell, but more than than (for example 500 bits - one per player) becomes more of an issue. Instead a boolean array called "name", and storing 100 true/false values looks like:
```pawn
new BitArray:name<100>;
```
As a normal array this would look like:
```pawn
new bool:name[100];
```
And would take up 400 bytes of memory, compared to only 20 for the "BitArray:" version.

To read bit 47 do:
```pawn
Bit_Get(name, 47);
```
To set bit 47 to true (1) do:
```pawn
Bit_Set(name, 47, true);
Bit_Let(name, 47); // Equivalent.
```
To set it to false (0, the default) do:
```pawn
Bit_Set(name, 47, false);
Bit_Vet(name, 47); // Equivalent.
```
"Bit_Set" is slightly slower than "Bit_Let" and "Bit_Get", but does take a third parameter defining which state to go to so is often useful. There is also a "Bit_SetAll" function:
```pawn
 Bit_SetAll(name, true);
```
That will set all the bits in the array to "true" faster than a loop would (32 times faster to be exact).
