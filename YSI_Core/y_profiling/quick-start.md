# Quick Start

```pawn
#define RUN_PROFILINGS

#include <a_samp>
#include <YSI_Core\y_profiling>

PROFILE__ LoopV1()
{
	new i = 0;
	while (i != 10)
	{
		++i;
	}
}

PROFILE__ LoopV2()
{
	for (new i = 0; i != 10; ++i)
	{
	}
}

main() {}
```

Output:

```
  ||========================||
  || STARTING PROFILINGS... ||
  ||========================||

Timing "LoopV1"...
          Mean = 120.00ns
          Mode = 120.00ns
        Median = 120.00ns
         Range = 4.00ns

Timing "LoopV2"...
          Mean = 124.00ns
          Mode = 124.00ns
        Median = 124.00ns
         Range = 9.00ns

*** Profilings: 2

  ||======================||
  || PROFILINGS COMPLETE! ||
  ||======================||

*** Time: 2496ms
```

THIS IS BECAUSE SUCH MICRO-OPTIMISATIONS ARE POINTLESS.  NEVER EVER COMPARE WHICH IS FASTER BETWEEN TWO EQUIVALENT LANGUAGE CONSTRUCTS.  PUT REAL CODE IN THE PROFILING FUNCTIONS!!!

