#define Task<%0> __TASK_%0
#define __TASK_%0\32; __TASK_

#define await%0(%1) (__AWAIT(__async_context)*(%0(%1)))

// Detect `->`  The line MUST end with a symbol or `%3__AWAIT_FOR$` won't be detected.
#define __AWAIT(%0)*(%1))->(%2)%3\10; __AWAIT(__ASYNC_CTX:ACEA__:ACEB__:ACEC__:ACED__:$%0)*(%1))%3__AWAIT_FOR$(%2)

// Detect `-> vars;)` (for).
#define ACEA__:%9$%0)*(%1))%3;%4)$(%2) __AWAIT_FOR:%0)*(%1))%3;%4)$(%2)
// Detect `-> vars;` (statement).
#define ACEB__:%9$%0)*(%1))%3;$(%2) __AWAIT_VAR:%0)*(%1))%3;$(%2)
// Detect `-> vars {}` (expression).
#define ACEC__:%9$%0)*(%1))%3$(%2) __AWAIT_FOR:%0)*(%1))%3;$(%2)
// Finish (nothing).
#define ACED__:%9$%0$ %0

//// TODO: Detect `-> vars; )` (`for (x; await; y)`).
//#define __async_context)*(%1))%3;__AWAIT_FOR$(%2) __async_context)*(%1))%3;__AWAIT_VAR(%2);
//
//// Detect `-> vars {}` (fallback)
//#define __AWAIT_FOR$(%2) for(__AWAIT_VAR(%2),__once;)

//#define __AWAIT_VAR(%2) new %2;???%2

await SomeFunction();
if (await SomeFunction()->(a, b, string:c[]))
{

}

await SomeFunction()->(d, e, f);
await SomeFunction() -> (g, h, i[32]);
if (await SomeFunction() -> (a, b, string:c[]))
{

}

if (await SomeFunction() -> (a, b, string:c[]))
{

}

