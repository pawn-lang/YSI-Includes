#define ADDRESSOF_MAKE_CALL__%0(%1) FUNC_PARSER(ADDRMKCL,ARR:NUM_TAG:REF_TAG:)(%0(%1))()(#)

#define ADDRMKCL_ARR(%0,%1,%2,%4)%8$(%6)(%7) %8$(%6,__ARR)(%7a)
#define ADDRMKCL_NUM(%0,%1,%2)%8$(%6)(%7) %8$(%6,%10)(%7i)
#define ADDRMKCL_REF(%0,%1,%2)%8$(%6)(%7) %8$(%6,%1__REF)(%7i)

#define ADDRMKCL_NUL(%0)%8$()(#) ADDRMKCL_END(%0)%8$(,)(#)
// I don't actually need the tag, this is purely internal.
//#define ADDRMKCL_END(%0)%8$(,%6)(#%7) %8$(O@A_()?(((_Hy@%0(%6)),O@V_)?(F@_@%7:1):(F@_@%7:2)):(F@_@%7:O@V_))
#define ADDRMKCL_END(%0)%8$(,%6)(#%7) %8$(O@A_()?(((_Hy@%0(%6)),O@V_)?1:2):(O@V_))

