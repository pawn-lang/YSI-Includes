
#define Y_REMOTE_FUNC%0(%1) FUNC_PARSER(Y_REMOTE,NUM_CST_DEF:STR_CST_DEF:REF_DEF:ARR_CST:QAL:RET_VOD_STR_TAG:LEN:)(%0(%1))(%1)#()()()(%1)

// This code uses "i" for normal variables and "d" for references.  These are
// both seen by "CallRemoteFunction" as the same thing, but we can
// differentiate them.
#define Y_REMOTE_NUM(%0,%1,%2)%8$%4#%5(%7)(%9) %8$%4#%5i(%7,%2)(%9,%1%2)
#define Y_REMOTE_STR(%0,%1,%2,%3)%8$%4#%5(%7)(%9) %8$%4#%5s(%7,%2)(%9,%1%2[%3])
#define Y_REMOTE_ARR(%0,%1,%2,%3)%8$%4#%5(%7)(%9) %8$%4#%5a(%7,%2)(%9,%1%2[%3])
#define Y_REMOTE_REF(%0,%1,%2)%8$%4#%5(%7)(%9)(%3) %8$%4#%5d(%7,%2)(%9,%1%2)(%3,%2)
#define Y_REMOTE_NUM_DEF(%0,%1,%2,%9)%8$%4#%5(%7)(%9) %8$%4#%5i(%7,%2)(%9,%1%2)
#define Y_REMOTE_STR_DEF(%0,%1,%2,%3,%9)%8$%4#%5(%7)(%9) %8$%4#%5s(%7,%2)(%9,%1%2[%3])
#define Y_REMOTE_REF_DEF(%0,%1,%2,%9)%8$%4#%5(%7)(%9)(%3) %8$%4#%5d(%7,%2)(%9,%1%2)(%3,%2)

// Use this to force insert a space.  Just "stock " doesn't work.
#define Y_REMOTE_stock()%8$ %8$stock PP_NULL<>
#define Y_REMOTE_static()%8$ %8$static PP_NULL<>

#define Y_REMOTE_END(%9)%8$%4(%1)%3(,%7)(,%2)(%0)(%6) %8$%4 _@%9(%1)return F@(J@,I@),D@(YREMOTE_END:#@@%9,%3i,%7);@@%9(%2,__m)(%7)(%0)(%6)
#define Y_REMOTE_END_STR(%9)%8$%4(%1)%3(,%7)(,%2)(%0)(%6) %8$%4 _@%9(%1)return F@(J@,I@),C@(YREMOTE_STR:#@@%9,%3i,%7);@@%9(%2,__m)(%7)(%0)(%6)
#define Y_REMOTE_END_VOD(%9)%8$%4(%1)%3(,%7)(,%2)(%0)(%6) %8$%4 _@%9(%1)F@(J@,I@),D@(YREMOTE_VOD:#@@%9,%3i,%7);@@%9(%2,__m)(%7)(%0)(%6)
#define Y_REMOTE_END_TAG(%5,%9)%8$%4(%1)%3(,%7)(,%2)(%0)(%6) %8$%4%5 _@%9(%1)return F@(J@,I@),%5D@(YREMOTE_TAG:#@@%9,%3i,%7);@@%9(%2,__m)(%7)(%0)(%6)%5
#define Y_REMOTE_NUL(%9)%8$%4(%1)%3(%7)(%2)(%0)(%6) %8$%4 _@%9()return F@(J@,I@),D@(YREMOTE_END:#@@%9,#i);@@%9(__m)()()()
#define Y_REMOTE_NUL_STR(%9)%8$%4(%1)%3(%7)(%2)(%0)(%6) %8$%4 _@%9()return F@(J@,I@),C@(YREMOTE_STR:#@@%9,#i);@@%9(__m)()()()
#define Y_REMOTE_NUL_VOD(%9)%8$%4(%1)%3(%7)(%2)(%0)(%6) %8$%4 _@%9()F@(J@,I@),D@(YREMOTE_VOD:#@@%9,#i);@@%9(__m)()()()
#define Y_REMOTE_NUL_TAG(%5,%9)%8$%4(%1)%3(%7)(%2)(%0)(%6) %8$%4%5 _@%9()return F@(J@,I@),%5D@(YREMOTE_TAG:#@@%9,#i);@@%9(__m)()()()%5

#define YREMOTE_END:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2)if(__m&@_)L@(%1(%3)%4);%1(%6)
#define YREMOTE_STR:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2)if(__m&@_)T@(%1(%3)%4);%1(%6)
#define YREMOTE_VOD:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2){%1(%3);if(__m&@_)L@(0%4);}%1(%6)
#define YREMOTE_TAG:%0);@@%1(%2)(%3)(%4)(%6)%5: %0);%5:%1(%6);I@R:@@%1(%2);I@R:@@%1(%2)if(__m&@_)L@(%1(%3)%4);%5:%1(%6)

// If someone does:
//   
//   remotefunc X();
//   
// Assume that this is purely a forwarding declaration.  Make the function
// uncallable.
#define I@R:%9;%9;%9; static stock %9{}

