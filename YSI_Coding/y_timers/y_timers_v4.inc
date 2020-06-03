
#define TIMER__%0[%2](%1) FUNC_PARSER(TIMER,QAL:ARR_CST:REF_DEF:STR_CST_DEF:NUM_CST_DEF:)(%0(%1))(%0(%1))()(%2)()#

// TIMER_STR(const, tag, name, size)rest$(original_call)(time)(pass_parameters)specifier#
#define TIMER_STR(%6,%9,%2,%5,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2[%5])(%1)(%3,%2)%4s#
#define TIMER_ARR(%6,%9,%2,%5,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2[%5])(%1)(%3,%2)%4a#
#define TIMER_NUM(%6,%9,%2,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6%2)(%1)(%3,%2)%4i#
#define TIMER_REF(%6,%9,%2,%9)%8$(%7)(%0)(%1)(%3)%4# %8$(%7)(%0,%6&%2)(%1)(%3,%2)%4v#

// ".." is used to reserve memory at the start of the string for:
// 
//   +0 - TIMER function start pointer.
//   +1 - Stack size.
#define TIMER_END(%9)%8$(%0(%7))(,%1)(%5)(%3)%4# %8$_yT@%0(%7)return O@(#%0,(I@==-1)?(%5):I@,J@,#%4%3)%0(%1);public %0(%1)
#define TIMER_NUL(%9)%8$(%0(%7))(%1)(%5)(%3)%4# %8$_yT@%0()return SetTimer(#%0,(I@==-1)?(%5):I@,J@)%0();public %0()

#define _yT@%0\32; _yT@

