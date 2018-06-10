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

static stock const Y_UNIQUE_900_to_999_CALLED;

#if defined _inc_y_unique__900_to_999
	#undef _inc_y_unique__900_to_999
#endif

#if UNIQUE_SYMBOL < 910
	#if UNIQUE_SYMBOL == 900
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (901)
		#define UNIQUE_FUNCTION<%0...%1> %0901%1
		#endinput
	#elseif UNIQUE_SYMBOL == 901
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (902)
		#define UNIQUE_FUNCTION<%0...%1> %0902%1
		#endinput
	#elseif UNIQUE_SYMBOL == 902
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (903)
		#define UNIQUE_FUNCTION<%0...%1> %0903%1
		#endinput
	#elseif UNIQUE_SYMBOL == 903
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (904)
		#define UNIQUE_FUNCTION<%0...%1> %0904%1
		#endinput
	#elseif UNIQUE_SYMBOL == 904
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (905)
		#define UNIQUE_FUNCTION<%0...%1> %0905%1
		#endinput
	#elseif UNIQUE_SYMBOL == 905
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (906)
		#define UNIQUE_FUNCTION<%0...%1> %0906%1
		#endinput
	#elseif UNIQUE_SYMBOL == 906
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (907)
		#define UNIQUE_FUNCTION<%0...%1> %0907%1
		#endinput
	#elseif UNIQUE_SYMBOL == 907
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (908)
		#define UNIQUE_FUNCTION<%0...%1> %0908%1
		#endinput
	#elseif UNIQUE_SYMBOL == 908
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (909)
		#define UNIQUE_FUNCTION<%0...%1> %0909%1
		#endinput
	#elseif UNIQUE_SYMBOL == 909
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (910)
		#define UNIQUE_FUNCTION<%0...%1> %0910%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 920
	#if UNIQUE_SYMBOL == 910
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (911)
		#define UNIQUE_FUNCTION<%0...%1> %0911%1
		#endinput
	#elseif UNIQUE_SYMBOL == 911
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (912)
		#define UNIQUE_FUNCTION<%0...%1> %0912%1
		#endinput
	#elseif UNIQUE_SYMBOL == 912
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (913)
		#define UNIQUE_FUNCTION<%0...%1> %0913%1
		#endinput
	#elseif UNIQUE_SYMBOL == 913
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (914)
		#define UNIQUE_FUNCTION<%0...%1> %0914%1
		#endinput
	#elseif UNIQUE_SYMBOL == 914
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (915)
		#define UNIQUE_FUNCTION<%0...%1> %0915%1
		#endinput
	#elseif UNIQUE_SYMBOL == 915
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (916)
		#define UNIQUE_FUNCTION<%0...%1> %0916%1
		#endinput
	#elseif UNIQUE_SYMBOL == 916
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (917)
		#define UNIQUE_FUNCTION<%0...%1> %0917%1
		#endinput
	#elseif UNIQUE_SYMBOL == 917
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (918)
		#define UNIQUE_FUNCTION<%0...%1> %0918%1
		#endinput
	#elseif UNIQUE_SYMBOL == 918
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (919)
		#define UNIQUE_FUNCTION<%0...%1> %0919%1
		#endinput
	#elseif UNIQUE_SYMBOL == 919
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (920)
		#define UNIQUE_FUNCTION<%0...%1> %0920%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 930
	#if UNIQUE_SYMBOL == 920
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (921)
		#define UNIQUE_FUNCTION<%0...%1> %0921%1
		#endinput
	#elseif UNIQUE_SYMBOL == 921
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (922)
		#define UNIQUE_FUNCTION<%0...%1> %0922%1
		#endinput
	#elseif UNIQUE_SYMBOL == 922
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (923)
		#define UNIQUE_FUNCTION<%0...%1> %0923%1
		#endinput
	#elseif UNIQUE_SYMBOL == 923
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (924)
		#define UNIQUE_FUNCTION<%0...%1> %0924%1
		#endinput
	#elseif UNIQUE_SYMBOL == 924
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (925)
		#define UNIQUE_FUNCTION<%0...%1> %0925%1
		#endinput
	#elseif UNIQUE_SYMBOL == 925
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (926)
		#define UNIQUE_FUNCTION<%0...%1> %0926%1
		#endinput
	#elseif UNIQUE_SYMBOL == 926
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (927)
		#define UNIQUE_FUNCTION<%0...%1> %0927%1
		#endinput
	#elseif UNIQUE_SYMBOL == 927
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (928)
		#define UNIQUE_FUNCTION<%0...%1> %0928%1
		#endinput
	#elseif UNIQUE_SYMBOL == 928
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (929)
		#define UNIQUE_FUNCTION<%0...%1> %0929%1
		#endinput
	#elseif UNIQUE_SYMBOL == 929
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (930)
		#define UNIQUE_FUNCTION<%0...%1> %0930%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 940
	#if UNIQUE_SYMBOL == 930
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (931)
		#define UNIQUE_FUNCTION<%0...%1> %0931%1
		#endinput
	#elseif UNIQUE_SYMBOL == 931
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (932)
		#define UNIQUE_FUNCTION<%0...%1> %0932%1
		#endinput
	#elseif UNIQUE_SYMBOL == 932
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (933)
		#define UNIQUE_FUNCTION<%0...%1> %0933%1
		#endinput
	#elseif UNIQUE_SYMBOL == 933
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (934)
		#define UNIQUE_FUNCTION<%0...%1> %0934%1
		#endinput
	#elseif UNIQUE_SYMBOL == 934
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (935)
		#define UNIQUE_FUNCTION<%0...%1> %0935%1
		#endinput
	#elseif UNIQUE_SYMBOL == 935
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (936)
		#define UNIQUE_FUNCTION<%0...%1> %0936%1
		#endinput
	#elseif UNIQUE_SYMBOL == 936
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (937)
		#define UNIQUE_FUNCTION<%0...%1> %0937%1
		#endinput
	#elseif UNIQUE_SYMBOL == 937
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (938)
		#define UNIQUE_FUNCTION<%0...%1> %0938%1
		#endinput
	#elseif UNIQUE_SYMBOL == 938
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (939)
		#define UNIQUE_FUNCTION<%0...%1> %0939%1
		#endinput
	#elseif UNIQUE_SYMBOL == 939
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (940)
		#define UNIQUE_FUNCTION<%0...%1> %0940%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 950
	#if UNIQUE_SYMBOL == 940
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (941)
		#define UNIQUE_FUNCTION<%0...%1> %0941%1
		#endinput
	#elseif UNIQUE_SYMBOL == 941
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (942)
		#define UNIQUE_FUNCTION<%0...%1> %0942%1
		#endinput
	#elseif UNIQUE_SYMBOL == 942
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (943)
		#define UNIQUE_FUNCTION<%0...%1> %0943%1
		#endinput
	#elseif UNIQUE_SYMBOL == 943
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (944)
		#define UNIQUE_FUNCTION<%0...%1> %0944%1
		#endinput
	#elseif UNIQUE_SYMBOL == 944
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (945)
		#define UNIQUE_FUNCTION<%0...%1> %0945%1
		#endinput
	#elseif UNIQUE_SYMBOL == 945
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (946)
		#define UNIQUE_FUNCTION<%0...%1> %0946%1
		#endinput
	#elseif UNIQUE_SYMBOL == 946
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (947)
		#define UNIQUE_FUNCTION<%0...%1> %0947%1
		#endinput
	#elseif UNIQUE_SYMBOL == 947
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (948)
		#define UNIQUE_FUNCTION<%0...%1> %0948%1
		#endinput
	#elseif UNIQUE_SYMBOL == 948
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (949)
		#define UNIQUE_FUNCTION<%0...%1> %0949%1
		#endinput
	#elseif UNIQUE_SYMBOL == 949
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (950)
		#define UNIQUE_FUNCTION<%0...%1> %0950%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 960
	#if UNIQUE_SYMBOL == 950
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (951)
		#define UNIQUE_FUNCTION<%0...%1> %0951%1
		#endinput
	#elseif UNIQUE_SYMBOL == 951
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (952)
		#define UNIQUE_FUNCTION<%0...%1> %0952%1
		#endinput
	#elseif UNIQUE_SYMBOL == 952
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (953)
		#define UNIQUE_FUNCTION<%0...%1> %0953%1
		#endinput
	#elseif UNIQUE_SYMBOL == 953
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (954)
		#define UNIQUE_FUNCTION<%0...%1> %0954%1
		#endinput
	#elseif UNIQUE_SYMBOL == 954
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (955)
		#define UNIQUE_FUNCTION<%0...%1> %0955%1
		#endinput
	#elseif UNIQUE_SYMBOL == 955
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (956)
		#define UNIQUE_FUNCTION<%0...%1> %0956%1
		#endinput
	#elseif UNIQUE_SYMBOL == 956
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (957)
		#define UNIQUE_FUNCTION<%0...%1> %0957%1
		#endinput
	#elseif UNIQUE_SYMBOL == 957
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (958)
		#define UNIQUE_FUNCTION<%0...%1> %0958%1
		#endinput
	#elseif UNIQUE_SYMBOL == 958
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (959)
		#define UNIQUE_FUNCTION<%0...%1> %0959%1
		#endinput
	#elseif UNIQUE_SYMBOL == 959
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (960)
		#define UNIQUE_FUNCTION<%0...%1> %0960%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 970
	#if UNIQUE_SYMBOL == 960
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (961)
		#define UNIQUE_FUNCTION<%0...%1> %0961%1
		#endinput
	#elseif UNIQUE_SYMBOL == 961
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (962)
		#define UNIQUE_FUNCTION<%0...%1> %0962%1
		#endinput
	#elseif UNIQUE_SYMBOL == 962
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (963)
		#define UNIQUE_FUNCTION<%0...%1> %0963%1
		#endinput
	#elseif UNIQUE_SYMBOL == 963
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (964)
		#define UNIQUE_FUNCTION<%0...%1> %0964%1
		#endinput
	#elseif UNIQUE_SYMBOL == 964
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (965)
		#define UNIQUE_FUNCTION<%0...%1> %0965%1
		#endinput
	#elseif UNIQUE_SYMBOL == 965
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (966)
		#define UNIQUE_FUNCTION<%0...%1> %0966%1
		#endinput
	#elseif UNIQUE_SYMBOL == 966
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (967)
		#define UNIQUE_FUNCTION<%0...%1> %0967%1
		#endinput
	#elseif UNIQUE_SYMBOL == 967
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (968)
		#define UNIQUE_FUNCTION<%0...%1> %0968%1
		#endinput
	#elseif UNIQUE_SYMBOL == 968
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (969)
		#define UNIQUE_FUNCTION<%0...%1> %0969%1
		#endinput
	#elseif UNIQUE_SYMBOL == 969
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (970)
		#define UNIQUE_FUNCTION<%0...%1> %0970%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 980
	#if UNIQUE_SYMBOL == 970
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (971)
		#define UNIQUE_FUNCTION<%0...%1> %0971%1
		#endinput
	#elseif UNIQUE_SYMBOL == 971
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (972)
		#define UNIQUE_FUNCTION<%0...%1> %0972%1
		#endinput
	#elseif UNIQUE_SYMBOL == 972
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (973)
		#define UNIQUE_FUNCTION<%0...%1> %0973%1
		#endinput
	#elseif UNIQUE_SYMBOL == 973
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (974)
		#define UNIQUE_FUNCTION<%0...%1> %0974%1
		#endinput
	#elseif UNIQUE_SYMBOL == 974
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (975)
		#define UNIQUE_FUNCTION<%0...%1> %0975%1
		#endinput
	#elseif UNIQUE_SYMBOL == 975
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (976)
		#define UNIQUE_FUNCTION<%0...%1> %0976%1
		#endinput
	#elseif UNIQUE_SYMBOL == 976
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (977)
		#define UNIQUE_FUNCTION<%0...%1> %0977%1
		#endinput
	#elseif UNIQUE_SYMBOL == 977
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (978)
		#define UNIQUE_FUNCTION<%0...%1> %0978%1
		#endinput
	#elseif UNIQUE_SYMBOL == 978
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (979)
		#define UNIQUE_FUNCTION<%0...%1> %0979%1
		#endinput
	#elseif UNIQUE_SYMBOL == 979
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (980)
		#define UNIQUE_FUNCTION<%0...%1> %0980%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 990
	#if UNIQUE_SYMBOL == 980
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (981)
		#define UNIQUE_FUNCTION<%0...%1> %0981%1
		#endinput
	#elseif UNIQUE_SYMBOL == 981
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (982)
		#define UNIQUE_FUNCTION<%0...%1> %0982%1
		#endinput
	#elseif UNIQUE_SYMBOL == 982
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (983)
		#define UNIQUE_FUNCTION<%0...%1> %0983%1
		#endinput
	#elseif UNIQUE_SYMBOL == 983
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (984)
		#define UNIQUE_FUNCTION<%0...%1> %0984%1
		#endinput
	#elseif UNIQUE_SYMBOL == 984
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (985)
		#define UNIQUE_FUNCTION<%0...%1> %0985%1
		#endinput
	#elseif UNIQUE_SYMBOL == 985
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (986)
		#define UNIQUE_FUNCTION<%0...%1> %0986%1
		#endinput
	#elseif UNIQUE_SYMBOL == 986
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (987)
		#define UNIQUE_FUNCTION<%0...%1> %0987%1
		#endinput
	#elseif UNIQUE_SYMBOL == 987
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (988)
		#define UNIQUE_FUNCTION<%0...%1> %0988%1
		#endinput
	#elseif UNIQUE_SYMBOL == 988
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (989)
		#define UNIQUE_FUNCTION<%0...%1> %0989%1
		#endinput
	#elseif UNIQUE_SYMBOL == 989
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (990)
		#define UNIQUE_FUNCTION<%0...%1> %0990%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 1000
	#if UNIQUE_SYMBOL == 990
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (991)
		#define UNIQUE_FUNCTION<%0...%1> %0991%1
		#endinput
	#elseif UNIQUE_SYMBOL == 991
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (992)
		#define UNIQUE_FUNCTION<%0...%1> %0992%1
		#endinput
	#elseif UNIQUE_SYMBOL == 992
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (993)
		#define UNIQUE_FUNCTION<%0...%1> %0993%1
		#endinput
	#elseif UNIQUE_SYMBOL == 993
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (994)
		#define UNIQUE_FUNCTION<%0...%1> %0994%1
		#endinput
	#elseif UNIQUE_SYMBOL == 994
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (995)
		#define UNIQUE_FUNCTION<%0...%1> %0995%1
		#endinput
	#elseif UNIQUE_SYMBOL == 995
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (996)
		#define UNIQUE_FUNCTION<%0...%1> %0996%1
		#endinput
	#elseif UNIQUE_SYMBOL == 996
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (997)
		#define UNIQUE_FUNCTION<%0...%1> %0997%1
		#endinput
	#elseif UNIQUE_SYMBOL == 997
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (998)
		#define UNIQUE_FUNCTION<%0...%1> %0998%1
		#endinput
	#elseif UNIQUE_SYMBOL == 998
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (999)
		#define UNIQUE_FUNCTION<%0...%1> %0999%1
		#endinput
	#elseif UNIQUE_SYMBOL == 999
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (1000)
		#define UNIQUE_FUNCTION<%0...%1> %01000%1
		#endinput
	#endif
#endif

