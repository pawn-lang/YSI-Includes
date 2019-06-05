# Quick Start

Using y_va is very simple.  When you want to pass multiple additional parameters use `___(n)`, where `n` is the number of parameters you DON'T want to pass.  In short, if you have a function that takes variable arguments (`...`), you can pass them all to another varargs function:

```pawn
#include <YSI_Coding\y_va>

VarArgsFunc2(const str[], ...)
{
	printf(str, ___(1));
}

VarArgsFunc1(n, const str1[], const str2[], ...)
{
	if (n)
	{
		VarArgsFunc2(str1, ___(3));
	}
	else
	{
		VarArgsFunc2(str2, ___(3));
	}
}
```

`VarArgsFunc2` has 1 normal parameter, so we call `printf` with `___(1)`.  `VarArgsFunc1` has 3 normal parameters, so calls `VarArgsFunc2` with `___(3)`.

The simple way to remember is - 3 dots to take variable parameters, 3 underscores to pass them.

The following code:

```pawn
PrintStuff(...)
{
	printf("%d %d %d %d %d", ___(0));
}

main()
{
	PrintStuff(0, 1, 2, 3, 4);
}
```

Will print `0 1 2 3 4`.

