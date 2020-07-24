#define Task<%0> __TASK_%0
#define __TASK_%0\32; __TASK_

// `_yA@%0()` is used to check the function types for returned data.  It's most important operation
// is during compilation, but because it is after `,` it must propagate the value from `*`:
//
//     operator*(a,return_tag:b) YSI_gLastRet = _:b;
//     _yA@%0(Func:unused<>) return unused,return_tag:YSI_gLastRet;
//
#define await%0(%1) (__AWAIT(__async_context)*(%0(%1),$5),_yA@%0())

// Detect `->`.
#define __AWAIT(%0)*(%1),$5)->(%2)%3\10; __AWAIT(__ASYNC_CTX:ACEA__:ACEB__:ACEC__:ACED__:$%0)*(%1),$5)%3$(%2)

// Detect `->` with K&R.
#define __async_context)*(%1),$5)->(%2)%3{ __ASYNC_CTX:ACEA__:ACEC__:ACED__:$__async_context)*(%1),$5)%3$(%2){

// Detect `-> vars;)` (for).
#define ACEA__:%9$%0)*(%1),$5)%3;%4)$(%2) __AWAIT_FOR:%0)*(%1),$5)%3;%4)$(%2)
// Detect `-> vars;` (statement).
#define ACEB__:%9$%0)*(%1),$5)%3;$(%2) __AWAIT_VAR:%0)*(%1),$5)%3;$(%2)
// Detect `-> vars {}` (expression).
#define ACEC__:%9$%0)*(%1),$5)%3$(%2) __AWAIT_FOR:%0)*(%1),$5)%3$(%2)
// Finish (nothing).
#define ACED__:%9$%0$ %0

//#define __AWAIT_VAR(%2) new %2;???%2

await SomeFunction();

if (await SomeFunction()->(a, b, string:c[]))
{

}

await SomeFunction()->(d, e, f);

await SomeFunction() -> (g, h, i[32]);

if (await SomeFunction() -> (a, b, string:c[])) {

}

for (new a, b, c; await SomeFunction() -> (d, e, string:f[]) && c; ++a) {

}

if (await SomeFunction() -> (a, b, string:c[]))
{

}

for (new a, b, c; await SomeFunction() -> (d, e, string:f[]) && c; ++a)
{

}

