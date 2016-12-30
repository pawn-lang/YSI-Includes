
#define remote%0(%1) FUNC_PARSER(Y_REMOTE,NUM_CST_DEF:STR_CST_DEF:REF_DEF:ARR_CST:QAL:RET_VOD_STR_TAG:LEN:)(%0(%1))(%1)#()()()()

// This code uses "i" for normal variables and "d" for references.  These are
// both seen by "CallRemoteFunction" as the same thing, but we can
// differentiate them.
#define Y_REMOTE_NUM(%0,%1,%2)%8$%4#%5(%7)(%9)(%6) %8$%4#%5i(%7,%2)(%9,%1%2)(%6,%0%1%2)
#define Y_REMOTE_STR(%0,%1,%2,%3)%8$%4#%5(%7)(%9)(%6) %8$%4#%5s(%7,%2)(%9,%1%2[%3])(%6,%0%1%2[%3])
#define Y_REMOTE_ARR(%0,%1,%2,%3)%8$%4#%5(%7)(%9)(%6) %8$%4#%5a(%7,%2)(%9,%1%2[%3])(%6,%0%1%2[%3])
#define Y_REMOTE_REF(%0,%1,%2)%8$%4#%5(%7)(%9)(%6)(%3) %8$%4#%5d(%7,%2)(%9,%1%2)(%6,&%1%2)(%3,%2)
#define Y_REMOTE_NUM_DEF(%0,%1,%2,%9)%8$%4#%5(%7)(%9)(%6) %8$%4#%5i(%7,%2)(%9,%1%2)(%6,%0%1%2)
#define Y_REMOTE_STR_DEF(%0,%1,%2,%3,%9)%8$%4#%5(%7)(%9)(%6) %8$%4#%5s(%7,%2)(%9,%1%2[%3])(%6,%0%1%2[%3])
#define Y_REMOTE_REF_DEF(%0,%1,%2,%9)%8$%4#%5(%7)(%9)(%6)(%3) %8$%4#%5d(%7,%2)(%9,%1%2)(%6,&%1%2)(%3,%2)

// Use this to force insert a space.  Just "stock " doesn't work.
#define Y_REMOTE_stock()%8$ %8$stock PP_NULL<>
#define Y_REMOTE_static()%8$ %8$static PP_NULL<>

#define Y_REMOTE_END(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4%9(%1)return D@(YREMOTE_END:#@_%9,%3,%7);@_%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_STR(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4%9(%1)return C@(YREMOTE_STR:#@_%9,%3,%7);@_%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_VOD(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4%9(%1)D@(YREMOTE_VOD:#@_%9,%3,%7);@_%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_TAG(%5,%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4%5%9(%1)return %5D@(YREMOTE_TAG:#@_%9,%3,%7);@_%9(%2)(%7)(%6)(%0)%5
#define Y_REMOTE_NUL(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4%9()return D@(YREMOTE_END:#@_%9,"");@_%9()()()()
#define Y_REMOTE_NUL_STR(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4%9()return C@(YREMOTE_STR:#@_%9,"");@_%9()()()()
#define Y_REMOTE_NUL_VOD(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4%9()D@(YREMOTE_VOD:#@_%9,"");@_%9()()()()
#define Y_REMOTE_NUL_TAG(%5,%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4%5%9()return %5D@(YREMOTE_TAG:#@_%9,"");@_%9()()()()%5

#define YREMOTE_END:%0);@_%1(%2)(%3)(%6)(%4) %0);@_%1(%2);@_%1(%2)return L@(_@%1(%3)%4);_@%1(%6)
#define YREMOTE_STR:%0);@_%1(%2)(%3)(%6)(%4) %0);@_%1(%2);@_%1(%2)return T@(_@%1(%3)%4);_@%1(%6)
#define YREMOTE_VOD:%0);@_%1(%2)(%3)(%6)(%4) %0);@_%1(%2);@_%1(%2){_@%1(%3);return L@(0%4);}_@%1(%6)
#define YREMOTE_TAG:%0);@_%1(%2)(%3)(%6)(%4)%5: %0);@_%1(%2);%5:_@%1(%6);@_%1(%2)return L@(_@%1(%3)%4);%5:_@%1(%6)

