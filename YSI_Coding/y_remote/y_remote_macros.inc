/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#define REMOTE_FUNC__%0(%1) FUNC_PARSER(Y_REMOTE,NUM_CST_DEF:STR_CST_DEF:REF_DEF:ARR_CST:QAL:RET_VOD_STR_TAG:LEN:)(%0(%1))(%1)#()()()(%1)
#define LOCAL_FUNC__%0(%1) (J@=0,I@=-1,_@%0(%1))
#define BROADCAST_FUNC__%0(%1) (J@=1,I@=-1,_@%0(%1))
#define TARGET_FUNC__%0<%2>%9(%1) (J@=1,I@=(%2),_@%0(%1))

#if YSI_KEYWORD(remotefunc)
	#define remotefunc REMOTE_FUNC__
#endif
#if YSI_KEYWORD(localfunc)
	#define localfunc LOCAL_FUNC__
#endif
#if YSI_KEYWORD(broadcastfunc)
	#define broadcastfunc BROADCAST_FUNC__
#endif
#if YSI_KEYWORD(targetfunc)
	#define targetfunc TARGET_FUNC__
#endif

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

#define YREMOTE_END:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2)return I@R:((__m&@_)&&L@(%1(%3)%4));%1(%6)
#define YREMOTE_STR:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2)return I@R:((__m&@_)&&T@(%1(%3)%4));%1(%6)
#define YREMOTE_VOD:%0);@@%1(%2)(%3)(%4)(%6) %0);I@R:@@%1(%2);I@R:@@%1(%2)return I@R:((__m&@_)&&(%1(%3),L@(0%4)));%1(%6)
#define YREMOTE_TAG:%0);@@%1(%2)(%3)(%4)(%6)%5: %0);I@P:@@%1(%2);%5:%1(%6);I@P:@@%1(%2)return I@P:((__m&@_)&&L@(%1(%3)%4));%5:%1(%6)

// If someone does:
//   
//   remotefunc X();
//   
// Assume that this is purely a forwarding declaration.  Make the function
// uncallable.
#define I@R:%9;%9;%9; static stock %9{}
#define I@P:%9;%9;%9;%9; static stock %9{}

