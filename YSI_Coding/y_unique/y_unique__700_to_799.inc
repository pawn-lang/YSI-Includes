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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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

static stock const Y_UNIQUE_700_to_799_CALLED = cellmin;

#if defined _inc_y_unique__700_to_799
	#undef _inc_y_unique__700_to_799
#endif

#if UNIQUE_SYMBOL < 710
	#if UNIQUE_SYMBOL == 700
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (701)
		#define UNIQUE_FUNCTION<%0...%1> %0701%1
		#endinput
	#elseif UNIQUE_SYMBOL == 701
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (702)
		#define UNIQUE_FUNCTION<%0...%1> %0702%1
		#endinput
	#elseif UNIQUE_SYMBOL == 702
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (703)
		#define UNIQUE_FUNCTION<%0...%1> %0703%1
		#endinput
	#elseif UNIQUE_SYMBOL == 703
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (704)
		#define UNIQUE_FUNCTION<%0...%1> %0704%1
		#endinput
	#elseif UNIQUE_SYMBOL == 704
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (705)
		#define UNIQUE_FUNCTION<%0...%1> %0705%1
		#endinput
	#elseif UNIQUE_SYMBOL == 705
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (706)
		#define UNIQUE_FUNCTION<%0...%1> %0706%1
		#endinput
	#elseif UNIQUE_SYMBOL == 706
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (707)
		#define UNIQUE_FUNCTION<%0...%1> %0707%1
		#endinput
	#elseif UNIQUE_SYMBOL == 707
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (708)
		#define UNIQUE_FUNCTION<%0...%1> %0708%1
		#endinput
	#elseif UNIQUE_SYMBOL == 708
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (709)
		#define UNIQUE_FUNCTION<%0...%1> %0709%1
		#endinput
	#elseif UNIQUE_SYMBOL == 709
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (710)
		#define UNIQUE_FUNCTION<%0...%1> %0710%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 720
	#if UNIQUE_SYMBOL == 710
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (711)
		#define UNIQUE_FUNCTION<%0...%1> %0711%1
		#endinput
	#elseif UNIQUE_SYMBOL == 711
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (712)
		#define UNIQUE_FUNCTION<%0...%1> %0712%1
		#endinput
	#elseif UNIQUE_SYMBOL == 712
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (713)
		#define UNIQUE_FUNCTION<%0...%1> %0713%1
		#endinput
	#elseif UNIQUE_SYMBOL == 713
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (714)
		#define UNIQUE_FUNCTION<%0...%1> %0714%1
		#endinput
	#elseif UNIQUE_SYMBOL == 714
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (715)
		#define UNIQUE_FUNCTION<%0...%1> %0715%1
		#endinput
	#elseif UNIQUE_SYMBOL == 715
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (716)
		#define UNIQUE_FUNCTION<%0...%1> %0716%1
		#endinput
	#elseif UNIQUE_SYMBOL == 716
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (717)
		#define UNIQUE_FUNCTION<%0...%1> %0717%1
		#endinput
	#elseif UNIQUE_SYMBOL == 717
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (718)
		#define UNIQUE_FUNCTION<%0...%1> %0718%1
		#endinput
	#elseif UNIQUE_SYMBOL == 718
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (719)
		#define UNIQUE_FUNCTION<%0...%1> %0719%1
		#endinput
	#elseif UNIQUE_SYMBOL == 719
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (720)
		#define UNIQUE_FUNCTION<%0...%1> %0720%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 730
	#if UNIQUE_SYMBOL == 720
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (721)
		#define UNIQUE_FUNCTION<%0...%1> %0721%1
		#endinput
	#elseif UNIQUE_SYMBOL == 721
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (722)
		#define UNIQUE_FUNCTION<%0...%1> %0722%1
		#endinput
	#elseif UNIQUE_SYMBOL == 722
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (723)
		#define UNIQUE_FUNCTION<%0...%1> %0723%1
		#endinput
	#elseif UNIQUE_SYMBOL == 723
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (724)
		#define UNIQUE_FUNCTION<%0...%1> %0724%1
		#endinput
	#elseif UNIQUE_SYMBOL == 724
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (725)
		#define UNIQUE_FUNCTION<%0...%1> %0725%1
		#endinput
	#elseif UNIQUE_SYMBOL == 725
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (726)
		#define UNIQUE_FUNCTION<%0...%1> %0726%1
		#endinput
	#elseif UNIQUE_SYMBOL == 726
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (727)
		#define UNIQUE_FUNCTION<%0...%1> %0727%1
		#endinput
	#elseif UNIQUE_SYMBOL == 727
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (728)
		#define UNIQUE_FUNCTION<%0...%1> %0728%1
		#endinput
	#elseif UNIQUE_SYMBOL == 728
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (729)
		#define UNIQUE_FUNCTION<%0...%1> %0729%1
		#endinput
	#elseif UNIQUE_SYMBOL == 729
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (730)
		#define UNIQUE_FUNCTION<%0...%1> %0730%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 740
	#if UNIQUE_SYMBOL == 730
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (731)
		#define UNIQUE_FUNCTION<%0...%1> %0731%1
		#endinput
	#elseif UNIQUE_SYMBOL == 731
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (732)
		#define UNIQUE_FUNCTION<%0...%1> %0732%1
		#endinput
	#elseif UNIQUE_SYMBOL == 732
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (733)
		#define UNIQUE_FUNCTION<%0...%1> %0733%1
		#endinput
	#elseif UNIQUE_SYMBOL == 733
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (734)
		#define UNIQUE_FUNCTION<%0...%1> %0734%1
		#endinput
	#elseif UNIQUE_SYMBOL == 734
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (735)
		#define UNIQUE_FUNCTION<%0...%1> %0735%1
		#endinput
	#elseif UNIQUE_SYMBOL == 735
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (736)
		#define UNIQUE_FUNCTION<%0...%1> %0736%1
		#endinput
	#elseif UNIQUE_SYMBOL == 736
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (737)
		#define UNIQUE_FUNCTION<%0...%1> %0737%1
		#endinput
	#elseif UNIQUE_SYMBOL == 737
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (738)
		#define UNIQUE_FUNCTION<%0...%1> %0738%1
		#endinput
	#elseif UNIQUE_SYMBOL == 738
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (739)
		#define UNIQUE_FUNCTION<%0...%1> %0739%1
		#endinput
	#elseif UNIQUE_SYMBOL == 739
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (740)
		#define UNIQUE_FUNCTION<%0...%1> %0740%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 750
	#if UNIQUE_SYMBOL == 740
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (741)
		#define UNIQUE_FUNCTION<%0...%1> %0741%1
		#endinput
	#elseif UNIQUE_SYMBOL == 741
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (742)
		#define UNIQUE_FUNCTION<%0...%1> %0742%1
		#endinput
	#elseif UNIQUE_SYMBOL == 742
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (743)
		#define UNIQUE_FUNCTION<%0...%1> %0743%1
		#endinput
	#elseif UNIQUE_SYMBOL == 743
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (744)
		#define UNIQUE_FUNCTION<%0...%1> %0744%1
		#endinput
	#elseif UNIQUE_SYMBOL == 744
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (745)
		#define UNIQUE_FUNCTION<%0...%1> %0745%1
		#endinput
	#elseif UNIQUE_SYMBOL == 745
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (746)
		#define UNIQUE_FUNCTION<%0...%1> %0746%1
		#endinput
	#elseif UNIQUE_SYMBOL == 746
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (747)
		#define UNIQUE_FUNCTION<%0...%1> %0747%1
		#endinput
	#elseif UNIQUE_SYMBOL == 747
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (748)
		#define UNIQUE_FUNCTION<%0...%1> %0748%1
		#endinput
	#elseif UNIQUE_SYMBOL == 748
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (749)
		#define UNIQUE_FUNCTION<%0...%1> %0749%1
		#endinput
	#elseif UNIQUE_SYMBOL == 749
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (750)
		#define UNIQUE_FUNCTION<%0...%1> %0750%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 760
	#if UNIQUE_SYMBOL == 750
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (751)
		#define UNIQUE_FUNCTION<%0...%1> %0751%1
		#endinput
	#elseif UNIQUE_SYMBOL == 751
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (752)
		#define UNIQUE_FUNCTION<%0...%1> %0752%1
		#endinput
	#elseif UNIQUE_SYMBOL == 752
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (753)
		#define UNIQUE_FUNCTION<%0...%1> %0753%1
		#endinput
	#elseif UNIQUE_SYMBOL == 753
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (754)
		#define UNIQUE_FUNCTION<%0...%1> %0754%1
		#endinput
	#elseif UNIQUE_SYMBOL == 754
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (755)
		#define UNIQUE_FUNCTION<%0...%1> %0755%1
		#endinput
	#elseif UNIQUE_SYMBOL == 755
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (756)
		#define UNIQUE_FUNCTION<%0...%1> %0756%1
		#endinput
	#elseif UNIQUE_SYMBOL == 756
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (757)
		#define UNIQUE_FUNCTION<%0...%1> %0757%1
		#endinput
	#elseif UNIQUE_SYMBOL == 757
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (758)
		#define UNIQUE_FUNCTION<%0...%1> %0758%1
		#endinput
	#elseif UNIQUE_SYMBOL == 758
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (759)
		#define UNIQUE_FUNCTION<%0...%1> %0759%1
		#endinput
	#elseif UNIQUE_SYMBOL == 759
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (760)
		#define UNIQUE_FUNCTION<%0...%1> %0760%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 770
	#if UNIQUE_SYMBOL == 760
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (761)
		#define UNIQUE_FUNCTION<%0...%1> %0761%1
		#endinput
	#elseif UNIQUE_SYMBOL == 761
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (762)
		#define UNIQUE_FUNCTION<%0...%1> %0762%1
		#endinput
	#elseif UNIQUE_SYMBOL == 762
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (763)
		#define UNIQUE_FUNCTION<%0...%1> %0763%1
		#endinput
	#elseif UNIQUE_SYMBOL == 763
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (764)
		#define UNIQUE_FUNCTION<%0...%1> %0764%1
		#endinput
	#elseif UNIQUE_SYMBOL == 764
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (765)
		#define UNIQUE_FUNCTION<%0...%1> %0765%1
		#endinput
	#elseif UNIQUE_SYMBOL == 765
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (766)
		#define UNIQUE_FUNCTION<%0...%1> %0766%1
		#endinput
	#elseif UNIQUE_SYMBOL == 766
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (767)
		#define UNIQUE_FUNCTION<%0...%1> %0767%1
		#endinput
	#elseif UNIQUE_SYMBOL == 767
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (768)
		#define UNIQUE_FUNCTION<%0...%1> %0768%1
		#endinput
	#elseif UNIQUE_SYMBOL == 768
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (769)
		#define UNIQUE_FUNCTION<%0...%1> %0769%1
		#endinput
	#elseif UNIQUE_SYMBOL == 769
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (770)
		#define UNIQUE_FUNCTION<%0...%1> %0770%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 780
	#if UNIQUE_SYMBOL == 770
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (771)
		#define UNIQUE_FUNCTION<%0...%1> %0771%1
		#endinput
	#elseif UNIQUE_SYMBOL == 771
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (772)
		#define UNIQUE_FUNCTION<%0...%1> %0772%1
		#endinput
	#elseif UNIQUE_SYMBOL == 772
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (773)
		#define UNIQUE_FUNCTION<%0...%1> %0773%1
		#endinput
	#elseif UNIQUE_SYMBOL == 773
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (774)
		#define UNIQUE_FUNCTION<%0...%1> %0774%1
		#endinput
	#elseif UNIQUE_SYMBOL == 774
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (775)
		#define UNIQUE_FUNCTION<%0...%1> %0775%1
		#endinput
	#elseif UNIQUE_SYMBOL == 775
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (776)
		#define UNIQUE_FUNCTION<%0...%1> %0776%1
		#endinput
	#elseif UNIQUE_SYMBOL == 776
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (777)
		#define UNIQUE_FUNCTION<%0...%1> %0777%1
		#endinput
	#elseif UNIQUE_SYMBOL == 777
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (778)
		#define UNIQUE_FUNCTION<%0...%1> %0778%1
		#endinput
	#elseif UNIQUE_SYMBOL == 778
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (779)
		#define UNIQUE_FUNCTION<%0...%1> %0779%1
		#endinput
	#elseif UNIQUE_SYMBOL == 779
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (780)
		#define UNIQUE_FUNCTION<%0...%1> %0780%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 790
	#if UNIQUE_SYMBOL == 780
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (781)
		#define UNIQUE_FUNCTION<%0...%1> %0781%1
		#endinput
	#elseif UNIQUE_SYMBOL == 781
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (782)
		#define UNIQUE_FUNCTION<%0...%1> %0782%1
		#endinput
	#elseif UNIQUE_SYMBOL == 782
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (783)
		#define UNIQUE_FUNCTION<%0...%1> %0783%1
		#endinput
	#elseif UNIQUE_SYMBOL == 783
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (784)
		#define UNIQUE_FUNCTION<%0...%1> %0784%1
		#endinput
	#elseif UNIQUE_SYMBOL == 784
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (785)
		#define UNIQUE_FUNCTION<%0...%1> %0785%1
		#endinput
	#elseif UNIQUE_SYMBOL == 785
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (786)
		#define UNIQUE_FUNCTION<%0...%1> %0786%1
		#endinput
	#elseif UNIQUE_SYMBOL == 786
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (787)
		#define UNIQUE_FUNCTION<%0...%1> %0787%1
		#endinput
	#elseif UNIQUE_SYMBOL == 787
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (788)
		#define UNIQUE_FUNCTION<%0...%1> %0788%1
		#endinput
	#elseif UNIQUE_SYMBOL == 788
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (789)
		#define UNIQUE_FUNCTION<%0...%1> %0789%1
		#endinput
	#elseif UNIQUE_SYMBOL == 789
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (790)
		#define UNIQUE_FUNCTION<%0...%1> %0790%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 800
	#if UNIQUE_SYMBOL == 790
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (791)
		#define UNIQUE_FUNCTION<%0...%1> %0791%1
		#endinput
	#elseif UNIQUE_SYMBOL == 791
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (792)
		#define UNIQUE_FUNCTION<%0...%1> %0792%1
		#endinput
	#elseif UNIQUE_SYMBOL == 792
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (793)
		#define UNIQUE_FUNCTION<%0...%1> %0793%1
		#endinput
	#elseif UNIQUE_SYMBOL == 793
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (794)
		#define UNIQUE_FUNCTION<%0...%1> %0794%1
		#endinput
	#elseif UNIQUE_SYMBOL == 794
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (795)
		#define UNIQUE_FUNCTION<%0...%1> %0795%1
		#endinput
	#elseif UNIQUE_SYMBOL == 795
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (796)
		#define UNIQUE_FUNCTION<%0...%1> %0796%1
		#endinput
	#elseif UNIQUE_SYMBOL == 796
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (797)
		#define UNIQUE_FUNCTION<%0...%1> %0797%1
		#endinput
	#elseif UNIQUE_SYMBOL == 797
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (798)
		#define UNIQUE_FUNCTION<%0...%1> %0798%1
		#endinput
	#elseif UNIQUE_SYMBOL == 798
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (799)
		#define UNIQUE_FUNCTION<%0...%1> %0799%1
		#endinput
	#elseif UNIQUE_SYMBOL == 799
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (800)
		#define UNIQUE_FUNCTION<%0...%1> %0800%1
		#endinput
	#endif
#endif

