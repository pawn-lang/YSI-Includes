#define _Hy@%0\32; _Hy@ // Hook implementation function.
#define @yH_%0\32; @yH_ // hook
#define ADDRMKCL_%0\32; ADDRMKCL_ // Named parameters.

#define ADDRESSOF_MAKE_CALL__%0(%1) FUNC_PARSER(ADDRMKCL,ARR:NUM_TAG:REF_TAG:)(%0(%1))()(#)

#define ADDRMKCL_ARR(%0,%1,%2,%4)%8$(%6)(%7) %8$(%6,__ARR)(%7a)
#define ADDRMKCL_NUM(%0,%1,%2)%8$(%6)(%7) %8$(%6,%10)(%7i)
#define ADDRMKCL_REF(%0,%1,%2)%8$(%6)(%7) %8$(%6,%1__REF)(%7i)

#define ADDRMKCL_NUL(%0)%8$()(#) ADDRMKCL_END(%0)%8$(,)(#)
// I don't actually need the tag, this is purely internal.
//#define ADDRMKCL_END(%0)%8$(,%6)(#%7) %8$(O@A_()?(((_Hy@%0(%6)),O@V_)?(F@_@%7:1):(F@_@%7:2)):(F@_@%7:O@V_))
#define ADDRMKCL_END(%0)%8$(,%6)(#%7)_Hooks_AddPublicHook(, ADDRMKCL:%8$UNIQUE_FUNCTION<@yH_%0@...>()_Hooks_AddPublicHook(O@A_()?(((UNIQUE_FUNCTION<_Hy@%0@...>(%6)),O@V_)?1:2):(O@V_),

#define @hook(%0)%1(%2) forward UNIQUE_FUNCTION<@yH_%1@...>();ADDRESSOF_MAKE_CALL__%1(%2)_Hooks_AddPublicHook(,_:"\"%1\"",%0);static UNIQUE_FUNCTION<_Hy@%1@...>(%2)

#define ADDRMKCL:%8$%0(%1)%2(%3,%4,.%5=%6) ADDRMKCL_%5:%8$%0(%1)%2(%3,%4,%6)
#define ADDRMKCL_callback:%8$%0(%1)%2(%3,%4,%6) %8$%0(%1)%2(%3,%4,%6)
#define ADDRMKCL_stock:%8$%6(%7)%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6(%7)_Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)
#define ADDRMKCL_native:%8$%6(%7)%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6(%7)_Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)
#define ADDRMKCL_function:%8$%6(%7)%9(%0?(((%1(%2))%3)%4):%5,%9,"%9") %8$%6(%7)_Hooks_AddFuncHook(%0?(((%1(%2))%3)%4):%5,%0?(((%9(%2))%3)%4):%5)

stock _Hooks_AddPublicHook(address, const name[], const callback[] = "")
{
}

stock _Hooks_AddFuncHook(address, hooked)
{
}

