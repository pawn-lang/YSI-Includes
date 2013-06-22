#if 0

// This:
inline func(a, &b, c[100])
{
	// Inline function code.
}

// Becomes:
static const func[]="func:....";if(I@E(func2))for(new a, b, c[100];I@F();)while(I@L(0,-1,100))
{
	// Inline function code.
}

// Which is:
static const
	func[] = "func:....";

if (I@E(func2))
{
	for (new a, b, c[100]; I@F(); )
	{
		while (I@L(0, -1, 100))
		{
			// Inline function code.
		}
	}
}

// Translated:
static const
	func[] = "func\02;" #FUNC_ADDRESS #PARAMETERS #INTERNAL_RETURN #PREVIOUS_FUNC_NAME;

if (Inline_Entry(func))
{
	for (new a, b, c[100]; Inline_Allocator(); )
	{
		while (Inline_Main(INLINE_TYPE_VAR, INLINE_TYPE_REF, INLINE_TYPE_ARR(100)))
		{
			// Inline function code.
		}
	}
}

// Run-time modified to something like:
goto somewhere_after_this_func;
func(parent, parameteters, a, b, c[100])
{
	new parent, local, variables;
	// Inline function code.
}
// Multiple inlines in a row are combined in to one big jump.
somewhere_after_this_func:

#endif

#define inline%0(%1) static const %0[]=#%0":....";if(I@E(_:_YI@CP:%0))for(new%1,,;I@F();)while(I@L())


#define _YI@CP:%8))for(new%0,%1; @Ia:@Ib:@Ic:@Id:@Iz:%8))for(new|||%0|||%1;

// Detect 0 parameters.
#define @Ia:@Ib:@Ic:@Id:@Iz:%8))for(new||||||,; %8))for(;

// Detect arrays.  Get the size, defaulting to YSI_MAX_STRING.
#define @Ib:@Ic:@Id:@Iz:%8))for(new%0|||%2[%3]|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2[%3+(_:NO_VALUE(%3)*YSI_MAX_STRING)]|||%4|||%5;I@F();)while(I@L(%7,sizeof %2))

// Detect references.
#define @Ic:@Id:@Iz:%8))for(new%0|||%1&%2|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2|||%4|||%5;I@F();)while(I@L(%7,-1))

// Detect normal variables.
#define @Id:@Iz:%8))for(new%0|||%2|||%4,%5;I@F();)while(I@L(%7)) @Ib:@Ic:@Id:@Iz:%8))for(new%0,%2|||%4|||%5;I@F();)while(I@L(%7,0))

// Detect end of line.
#define @Iz:%8))for(new%1,%0||||||;I@F();)while(I@L(%1,%7)) %8))for(new %0;I@F();)while(I@L(%7))

// Drop support for anonymous functions.
#define anonymous%0(%1) anonymous_no_longer_supported;for(new %1;FALSE;)

// Parameter type for passing callbacks about.
#define callback:%0) const callback_tag:callback_check:%0£££
#define callback_tag:callback_check:%0,%1£££ callback_tag:%0[],%1)
#define callback_check:%0£££ %0[])

