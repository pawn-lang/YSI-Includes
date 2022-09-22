	static stock const Y_UNIQUE__CALLED = UNIQUE_SYMBOL;

	#if defined _inc_y_unique_
		#undef _inc_y_unique_
	#endif

	#if UNIQUE_SYMBOL < (511)
		#if UNIQUE_SYMBOL < (63)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0063 = UNIQUE_SYMBOL;
			#include "y_unique_0000_0063"
			#endinput
		#elseif UNIQUE_SYMBOL < (127)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0127 = UNIQUE_SYMBOL;
			#include "y_unique_0064_0127"
			#endinput
		#elseif UNIQUE_SYMBOL < (191)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0191 = UNIQUE_SYMBOL;
			#include "y_unique_0128_0191"
			#endinput
		#elseif UNIQUE_SYMBOL < (255)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0255 = UNIQUE_SYMBOL;
			#include "y_unique_0192_0255"
			#endinput
		#elseif UNIQUE_SYMBOL < (319)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0319 = UNIQUE_SYMBOL;
			#include "y_unique_0256_0319"
			#endinput
		#elseif UNIQUE_SYMBOL < (383)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0383 = UNIQUE_SYMBOL;
			#include "y_unique_0320_0383"
			#endinput
		#elseif UNIQUE_SYMBOL < (447)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0447 = UNIQUE_SYMBOL;
			#include "y_unique_0384_0447"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_0511 = UNIQUE_SYMBOL;
			#include "y_unique_0448_0511"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (1023)
		#if UNIQUE_SYMBOL < (575)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0575 = UNIQUE_SYMBOL;
			#include "y_unique_0512_0575"
			#endinput
		#elseif UNIQUE_SYMBOL < (639)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0639 = UNIQUE_SYMBOL;
			#include "y_unique_0576_0639"
			#endinput
		#elseif UNIQUE_SYMBOL < (703)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0703 = UNIQUE_SYMBOL;
			#include "y_unique_0640_0703"
			#endinput
		#elseif UNIQUE_SYMBOL < (767)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0767 = UNIQUE_SYMBOL;
			#include "y_unique_0704_0767"
			#endinput
		#elseif UNIQUE_SYMBOL < (831)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0831 = UNIQUE_SYMBOL;
			#include "y_unique_0768_0831"
			#endinput
		#elseif UNIQUE_SYMBOL < (895)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0895 = UNIQUE_SYMBOL;
			#include "y_unique_0832_0895"
			#endinput
		#elseif UNIQUE_SYMBOL < (959)
			static stock const UNIQUE_SYMBOL_LESS_THAN_0959 = UNIQUE_SYMBOL;
			#include "y_unique_0896_0959"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_1023 = UNIQUE_SYMBOL;
			#include "y_unique_0960_1023"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (1535)
		#if UNIQUE_SYMBOL < (1087)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1087 = UNIQUE_SYMBOL;
			#include "y_unique_1024_1087"
			#endinput
		#elseif UNIQUE_SYMBOL < (1151)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1151 = UNIQUE_SYMBOL;
			#include "y_unique_1088_1151"
			#endinput
		#elseif UNIQUE_SYMBOL < (1215)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1215 = UNIQUE_SYMBOL;
			#include "y_unique_1152_1215"
			#endinput
		#elseif UNIQUE_SYMBOL < (1279)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1279 = UNIQUE_SYMBOL;
			#include "y_unique_1216_1279"
			#endinput
		#elseif UNIQUE_SYMBOL < (1343)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1343 = UNIQUE_SYMBOL;
			#include "y_unique_1280_1343"
			#endinput
		#elseif UNIQUE_SYMBOL < (1407)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1407 = UNIQUE_SYMBOL;
			#include "y_unique_1344_1407"
			#endinput
		#elseif UNIQUE_SYMBOL < (1471)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1471 = UNIQUE_SYMBOL;
			#include "y_unique_1408_1471"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_1535 = UNIQUE_SYMBOL;
			#include "y_unique_1472_1535"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (2047)
		#if UNIQUE_SYMBOL < (1599)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1599 = UNIQUE_SYMBOL;
			#include "y_unique_1536_1599"
			#endinput
		#elseif UNIQUE_SYMBOL < (1663)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1663 = UNIQUE_SYMBOL;
			#include "y_unique_1600_1663"
			#endinput
		#elseif UNIQUE_SYMBOL < (1727)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1727 = UNIQUE_SYMBOL;
			#include "y_unique_1664_1727"
			#endinput
		#elseif UNIQUE_SYMBOL < (1791)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1791 = UNIQUE_SYMBOL;
			#include "y_unique_1728_1791"
			#endinput
		#elseif UNIQUE_SYMBOL < (1855)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1855 = UNIQUE_SYMBOL;
			#include "y_unique_1792_1855"
			#endinput
		#elseif UNIQUE_SYMBOL < (1919)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1919 = UNIQUE_SYMBOL;
			#include "y_unique_1856_1919"
			#endinput
		#elseif UNIQUE_SYMBOL < (1983)
			static stock const UNIQUE_SYMBOL_LESS_THAN_1983 = UNIQUE_SYMBOL;
			#include "y_unique_1920_1983"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_2047 = UNIQUE_SYMBOL;
			#include "y_unique_1984_2047"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (2559)
		#if UNIQUE_SYMBOL < (2111)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2111 = UNIQUE_SYMBOL;
			#include "y_unique_2048_2111"
			#endinput
		#elseif UNIQUE_SYMBOL < (2175)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2175 = UNIQUE_SYMBOL;
			#include "y_unique_2112_2175"
			#endinput
		#elseif UNIQUE_SYMBOL < (2239)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2239 = UNIQUE_SYMBOL;
			#include "y_unique_2176_2239"
			#endinput
		#elseif UNIQUE_SYMBOL < (2303)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2303 = UNIQUE_SYMBOL;
			#include "y_unique_2240_2303"
			#endinput
		#elseif UNIQUE_SYMBOL < (2367)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2367 = UNIQUE_SYMBOL;
			#include "y_unique_2304_2367"
			#endinput
		#elseif UNIQUE_SYMBOL < (2431)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2431 = UNIQUE_SYMBOL;
			#include "y_unique_2368_2431"
			#endinput
		#elseif UNIQUE_SYMBOL < (2495)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2495 = UNIQUE_SYMBOL;
			#include "y_unique_2432_2495"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_2559 = UNIQUE_SYMBOL;
			#include "y_unique_2496_2559"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (3071)
		#if UNIQUE_SYMBOL < (2623)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2623 = UNIQUE_SYMBOL;
			#include "y_unique_2560_2623"
			#endinput
		#elseif UNIQUE_SYMBOL < (2687)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2687 = UNIQUE_SYMBOL;
			#include "y_unique_2624_2687"
			#endinput
		#elseif UNIQUE_SYMBOL < (2751)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2751 = UNIQUE_SYMBOL;
			#include "y_unique_2688_2751"
			#endinput
		#elseif UNIQUE_SYMBOL < (2815)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2815 = UNIQUE_SYMBOL;
			#include "y_unique_2752_2815"
			#endinput
		#elseif UNIQUE_SYMBOL < (2879)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2879 = UNIQUE_SYMBOL;
			#include "y_unique_2816_2879"
			#endinput
		#elseif UNIQUE_SYMBOL < (2943)
			static stock const UNIQUE_SYMBOL_LESS_THAN_2943 = UNIQUE_SYMBOL;
			#include "y_unique_2880_2943"
			#endinput
		#elseif UNIQUE_SYMBOL < (3007)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3007 = UNIQUE_SYMBOL;
			#include "y_unique_2944_3007"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_3071 = UNIQUE_SYMBOL;
			#include "y_unique_3008_3071"
			#endinput
		#endif
	#elseif UNIQUE_SYMBOL < (3583)
		#if UNIQUE_SYMBOL < (3135)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3135 = UNIQUE_SYMBOL;
			#include "y_unique_3072_3135"
			#endinput
		#elseif UNIQUE_SYMBOL < (3199)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3199 = UNIQUE_SYMBOL;
			#include "y_unique_3136_3199"
			#endinput
		#elseif UNIQUE_SYMBOL < (3263)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3263 = UNIQUE_SYMBOL;
			#include "y_unique_3200_3263"
			#endinput
		#elseif UNIQUE_SYMBOL < (3327)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3327 = UNIQUE_SYMBOL;
			#include "y_unique_3264_3327"
			#endinput
		#elseif UNIQUE_SYMBOL < (3391)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3391 = UNIQUE_SYMBOL;
			#include "y_unique_3328_3391"
			#endinput
		#elseif UNIQUE_SYMBOL < (3455)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3455 = UNIQUE_SYMBOL;
			#include "y_unique_3392_3455"
			#endinput
		#elseif UNIQUE_SYMBOL < (3519)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3519 = UNIQUE_SYMBOL;
			#include "y_unique_3456_3519"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_3583 = UNIQUE_SYMBOL;
			#include "y_unique_3520_3583"
			#endinput
		#endif
	#else
		#if UNIQUE_SYMBOL < (3647)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3647 = UNIQUE_SYMBOL;
			#include "y_unique_3584_3647"
			#endinput
		#elseif UNIQUE_SYMBOL < (3711)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3711 = UNIQUE_SYMBOL;
			#include "y_unique_3648_3711"
			#endinput
		#elseif UNIQUE_SYMBOL < (3775)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3775 = UNIQUE_SYMBOL;
			#include "y_unique_3712_3775"
			#endinput
		#elseif UNIQUE_SYMBOL < (3839)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3839 = UNIQUE_SYMBOL;
			#include "y_unique_3776_3839"
			#endinput
		#elseif UNIQUE_SYMBOL < (3903)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3903 = UNIQUE_SYMBOL;
			#include "y_unique_3840_3903"
			#endinput
		#elseif UNIQUE_SYMBOL < (3967)
			static stock const UNIQUE_SYMBOL_LESS_THAN_3967 = UNIQUE_SYMBOL;
			#include "y_unique_3904_3967"
			#endinput
		#elseif UNIQUE_SYMBOL < (4031)
			static stock const UNIQUE_SYMBOL_LESS_THAN_4031 = UNIQUE_SYMBOL;
			#include "y_unique_3968_4031"
			#endinput
		#else
			static stock const UNIQUE_SYMBOL_LESS_THAN_4095 = UNIQUE_SYMBOL;
			#include "y_unique_4032_4095"
			#endinput
		#endif
	#endif

