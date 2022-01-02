#define Task<%0> __TASK_%0
#define __TASK_%0\32; __TASK_
#define _yA@%0\32; _yA@
#define _Ay@%0\32; _Ay@

#define USING__%0\32; (@Ip:@Iq:@Io:@Iu:@Ia:@Ik:@Il:@Im:Callback_Find_(,I@),F@_@:I@)
#define USING_ASYNC__ (@Ik:@Il:Inline_UA_(),)

// new Async:__async_context;

// Parameter type for passing callbacks about.
#define @Ia:%0)async @Ik:@Il:Inline_UA_(),)

// Detect a `using` parameter that is not the last parameter.  Actually handles
// nested calls quite nicely - `X(Y(using inline Z), 5)` should be detected as a
// final parameter, but this detects it instead and gives
// `X(Y(Inline_UI_(Z)), 5)`, which is still correct.  This only falls down on
// code like `X(Y(using inline Z) - 10, 5)`, which currently becomes
// `X(Y(Inline_UI_(Z - 10)), 5)`
#define @Ik:@Il:%0)%1, %0%1),

// Detect a `using` parameter that is the last parameter.
#define @Il:%0)%1) %0%1))

// `_yA@%0()` is used to check the function types for returned data.  It's most important operation
// is during compilation, but because it is after `,` it must propagate the value from `+`:
//
//     operator+(a,return_tag:b) YSI_gLastRet = _:b;
//     _yA@%0(Func:unused<>) return unused,return_tag:YSI_gLastRet;
//
#define AWAIT__%0(%1) (__AWAIT(__async_context)+(%0(%1)),_yA@%0())

// If we use `using await` for legacy callbacks, replace `,_yA@%0()` with `*@Ic()`, so
// that it is the first thing called when we return from the legacy function and can defer that way
// instead.  Those functions will return, but at the wrong time.  You can even make legacy
// functions, which are easier to write, modern functions, with just a define:
//
//    LegacyFunc(Func:callback<ii>)
//    {
//        @.callback(4, 4);
//    }
//
//    #define ModernFunc() LegacyFunc(using await)
//

// Detect `->`.
#define __AWAIT(%0)+(%1),%5)->(%2)%3\10; __AWAIT(Async:@Ie:@If:@Ig:@Ih:$%0)+(%1),%5)%3$(%2)

// Detect `->` with K&R.
#define __async_context)+(%1),%5)->(%2)%3{ Async:@Ie:@Ig:@Ih:$__async_context)+(%1),%5)%3$(%2){

// Detect `-> vars;)` (for).
#define @Ie:%9$%0)+(%1),%5)%3;%4)$(%2) %0)+(%1),%5)%3;%4)__AWAIT_FOR$(%2)
// Detect `-> vars;` (statement).
#define @If:%9$%0)+(%1),%5)%3;$(%2) %0)+(%1),%5)%3;__AWAIT_VAR$(%2)
// Detect `-> vars {}` (expression).
#define @Ig:%9$%0)+(%1),%5)%3$(%2) %0)+(%1),%5)%3 __AWAIT_FOR$(%2)
// Finish (nothing).
#define @Ih:%9$%0$ %0

// We can use `@Ib` - `@Ij` at least, maybe more.
#define Inline_UA_(),)%0)),_yA@%1()) @Id:ASYNC_PARSER(),F@_@:I@)%0))*@Ic())

#define @Id:ASYNC_PARSER()%0$(%1) ASYNC_PARSER(%1)%0`(%1)
#define ASYNC_PARSER(%1) @Id:MAKE_PARSER(ASYNC,ARR:REF:STR:NUM:QAL::ASYNC)(_(%1))#

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define I@O$
#define PARSER@ASYNC:%0(%5)%6(%7)$ @Ib(_:%0(%5)%6(%7) I@O$

// @Ib - The function called to generate the inline stub.
// @Ic - The function called after the inline using function ends.

#define ASYNC_STR(%9,%9,%2,%9)%8$#%4,F@_@%3:I@) %8$#%4s,F@_@%3s:I@)
#define ASYNC_ARR(%9,%9,%2,%9)%8$#%4,F@_@%3:I@) %8$#%4a,F@_@%3a:I@)
#define ASYNC_NUM(%9,%9,%2)%8$#%4,F@_@%3:I@) %8$#%4i,F@_@%3i:I@)
#define ASYNC_REF(%9,%9,%2)%8$#%4,F@_@%3:I@) %8$#%4v,F@_@%3v:I@)

#define ASYNC_END(%9)%8$#%4, %8$I@,#%4),
#define ASYNC_NUL(%9)%8$#%4, %8$I@,#%4),

#define __AWAIT_VAR%9(%2) new %2;
#define __AWAIT_FOR%9(%2) for (new %2;__once;)

#define ASYNC__%0(%1) %0(%1)Async_B_(_:_Ay@%0(Async_A_()%1));stock _yA@%0()return _:_YSI_g_AsyncReturn;static stock _Ay@%0(__async_context,%1)

#if YSI_KEYWORD(async)
	#define async ASYNC__
#endif

#if YSI_KEYWORD(using)
	#define using USING__
#endif

#if YSI_KEYWORD(await)
	#define using AWAIT__
#endif

stock _Async_A()
{
	// Create a new context, or get the current context.
}

stock _Async_B(returnValue)
{
	_YSI_g_AsyncReturn = returnValue;
}

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

await SomeFunction(using async);

await SomeFunction(first, second, using async, third, fourth) -> (a, b, string:c[], Float:d[50], len);

async MyFunction1()
{
}

async MyFunction2(a, b)
{
}

async MyFunction3(c[], len, string:x[])
{
}

// Create a new context in the current function and specify the top level return value.
new Async:__async_context = Async_Context(0); // With immediate return value.

#define ASYNC_DETACH(%0) new Async:__async_context = Async_Detach(%0)

//ASYNC_CONTEXT__(1);

ASYNC_DETACH(0);

