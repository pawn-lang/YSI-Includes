
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

#define Y_REMOTE_stock()%8$ %8$stock
#define Y_REMOTE_static()%8$ %8$static

#define S@(%9:%0);%1; S@(%0); // Get word.
#define W@(%9:%0);%1; W@(%0); // Get string.
#define YREMOTE_END:%0);@RG%1(%2)(%3)(%6)(%4) %0);@RG%1(%2);@RG%1(%2)return X@(RG@%1(%3)%4);RG@%1(%6)
#define YREMOTE_STR:%0);@RG%1(%2)(%3)(%6)(%4) %0);@RG%1(%2);@RG%1(%2)return Z@(RG@%1(%3)%4);RG@%1(%6)
#define YREMOTE_VOD:%0);@RG%1(%2)(%3)(%6)(%4) %0);@RG%1(%2);@RG%1(%2){RG@%1(%3);return X@(0%4);}RG@%1(%6)
#define YREMOTE_TAG:%0);@RG%1(%2)(%3)(%6)(%4)%5: %0);@RG%1(%2);%5:RG@%1(%6);@RG%1(%2)return X@(_:RG@%1(%3)%4);%5:RG@%1(%6)

#define Y_REMOTE_END(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4 %9(%1)return W@(YREMOTE_END:#@RG%9,#%3,%7);@RG%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_STR(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4 %9(%1)return S@(YREMOTE_STR:#@RG%9,#%3,%7);@RG%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_VOD(%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4 %9(%1)W@(YREMOTE_VOD:#@RG%9,#%3,%7);@RG%9(%2)(%7)(%6)(%0)
#define Y_REMOTE_END_TAG(%5,%9)%8$%4(%1)%3(,%7)(,%2)(,%6)(%0) %8$%4 %5%9(%1)return %5W@(YREMOTE_TAG:#@RG%9,#%3,%7);@RG%9(%2)(%7)(%6)(%0)%5
#define Y_REMOTE_NUL(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4 %9(%1)return W@(YREMOTE_END:#@RG%9,"");@RG%9()()()()
#define Y_REMOTE_NUL_STR(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4 %9()return S@(YREMOTE_STR:#@RG%9,"");@RG%9()()()()
#define Y_REMOTE_NUL_VOD(%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4 %9()W@(YREMOTE_VOD:#@RG%9,"");@RG%9()()()()
#define Y_REMOTE_NUL_TAG(%5,%9)%8$%4(%1)%3(%7)(%2)(%6)(%0) %8$%4 %5%9()return %5W@(YREMOTE_TAG:#@RG%9,"");@RG%9()()()()%5

#define @RG%0\32; @RG
#define RG@%0\32; RG@

