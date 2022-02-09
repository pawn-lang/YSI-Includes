# Quick Start

```pawn
new c = 5 * Percent:20; // 20% of 5 = 1
new a = 5 + Percent:20; // 5 + 20% of 5 = 6
new b = 5 - Percent:20; // 5 - 20% of 5 = 4
```

To add percentages, put them first:

```pawn
new Percent:twenty = Percent:10 + 10; // 20%
new Percent:naught = Percent:10 - 10; //  0%
new Percent:hundred = Percent:10 * 10; // 100%
```

Using both does a mix:

```pawn
new Percent:twenty = Percent:10 + Percent:10; // 10% + 10% = 20%
new Percent:naught = Percent:10 - Percent:10; // 10% - 10% =  0%
new Percent:one = Percent:10 * Percent:10; // 10% * 10% =  1%
```

