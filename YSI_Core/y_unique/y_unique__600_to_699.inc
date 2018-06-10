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

static stock const Y_UNIQUE_600_to_699_CALLED;

#if defined _inc_y_unique__600_to_699
	#undef _inc_y_unique__600_to_699
#endif

#if UNIQUE_SYMBOL < 610
	#if UNIQUE_SYMBOL == 600
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (601)
		#define UNIQUE_FUNCTION<%0...%1> %0601%1
		#endinput
	#elseif UNIQUE_SYMBOL == 601
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (602)
		#define UNIQUE_FUNCTION<%0...%1> %0602%1
		#endinput
	#elseif UNIQUE_SYMBOL == 602
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (603)
		#define UNIQUE_FUNCTION<%0...%1> %0603%1
		#endinput
	#elseif UNIQUE_SYMBOL == 603
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (604)
		#define UNIQUE_FUNCTION<%0...%1> %0604%1
		#endinput
	#elseif UNIQUE_SYMBOL == 604
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (605)
		#define UNIQUE_FUNCTION<%0...%1> %0605%1
		#endinput
	#elseif UNIQUE_SYMBOL == 605
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (606)
		#define UNIQUE_FUNCTION<%0...%1> %0606%1
		#endinput
	#elseif UNIQUE_SYMBOL == 606
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (607)
		#define UNIQUE_FUNCTION<%0...%1> %0607%1
		#endinput
	#elseif UNIQUE_SYMBOL == 607
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (608)
		#define UNIQUE_FUNCTION<%0...%1> %0608%1
		#endinput
	#elseif UNIQUE_SYMBOL == 608
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (609)
		#define UNIQUE_FUNCTION<%0...%1> %0609%1
		#endinput
	#elseif UNIQUE_SYMBOL == 609
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (610)
		#define UNIQUE_FUNCTION<%0...%1> %0610%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 620
	#if UNIQUE_SYMBOL == 610
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (611)
		#define UNIQUE_FUNCTION<%0...%1> %0611%1
		#endinput
	#elseif UNIQUE_SYMBOL == 611
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (612)
		#define UNIQUE_FUNCTION<%0...%1> %0612%1
		#endinput
	#elseif UNIQUE_SYMBOL == 612
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (613)
		#define UNIQUE_FUNCTION<%0...%1> %0613%1
		#endinput
	#elseif UNIQUE_SYMBOL == 613
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (614)
		#define UNIQUE_FUNCTION<%0...%1> %0614%1
		#endinput
	#elseif UNIQUE_SYMBOL == 614
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (615)
		#define UNIQUE_FUNCTION<%0...%1> %0615%1
		#endinput
	#elseif UNIQUE_SYMBOL == 615
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (616)
		#define UNIQUE_FUNCTION<%0...%1> %0616%1
		#endinput
	#elseif UNIQUE_SYMBOL == 616
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (617)
		#define UNIQUE_FUNCTION<%0...%1> %0617%1
		#endinput
	#elseif UNIQUE_SYMBOL == 617
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (618)
		#define UNIQUE_FUNCTION<%0...%1> %0618%1
		#endinput
	#elseif UNIQUE_SYMBOL == 618
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (619)
		#define UNIQUE_FUNCTION<%0...%1> %0619%1
		#endinput
	#elseif UNIQUE_SYMBOL == 619
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (620)
		#define UNIQUE_FUNCTION<%0...%1> %0620%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 630
	#if UNIQUE_SYMBOL == 620
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (621)
		#define UNIQUE_FUNCTION<%0...%1> %0621%1
		#endinput
	#elseif UNIQUE_SYMBOL == 621
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (622)
		#define UNIQUE_FUNCTION<%0...%1> %0622%1
		#endinput
	#elseif UNIQUE_SYMBOL == 622
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (623)
		#define UNIQUE_FUNCTION<%0...%1> %0623%1
		#endinput
	#elseif UNIQUE_SYMBOL == 623
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (624)
		#define UNIQUE_FUNCTION<%0...%1> %0624%1
		#endinput
	#elseif UNIQUE_SYMBOL == 624
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (625)
		#define UNIQUE_FUNCTION<%0...%1> %0625%1
		#endinput
	#elseif UNIQUE_SYMBOL == 625
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (626)
		#define UNIQUE_FUNCTION<%0...%1> %0626%1
		#endinput
	#elseif UNIQUE_SYMBOL == 626
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (627)
		#define UNIQUE_FUNCTION<%0...%1> %0627%1
		#endinput
	#elseif UNIQUE_SYMBOL == 627
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (628)
		#define UNIQUE_FUNCTION<%0...%1> %0628%1
		#endinput
	#elseif UNIQUE_SYMBOL == 628
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (629)
		#define UNIQUE_FUNCTION<%0...%1> %0629%1
		#endinput
	#elseif UNIQUE_SYMBOL == 629
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (630)
		#define UNIQUE_FUNCTION<%0...%1> %0630%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 640
	#if UNIQUE_SYMBOL == 630
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (631)
		#define UNIQUE_FUNCTION<%0...%1> %0631%1
		#endinput
	#elseif UNIQUE_SYMBOL == 631
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (632)
		#define UNIQUE_FUNCTION<%0...%1> %0632%1
		#endinput
	#elseif UNIQUE_SYMBOL == 632
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (633)
		#define UNIQUE_FUNCTION<%0...%1> %0633%1
		#endinput
	#elseif UNIQUE_SYMBOL == 633
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (634)
		#define UNIQUE_FUNCTION<%0...%1> %0634%1
		#endinput
	#elseif UNIQUE_SYMBOL == 634
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (635)
		#define UNIQUE_FUNCTION<%0...%1> %0635%1
		#endinput
	#elseif UNIQUE_SYMBOL == 635
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (636)
		#define UNIQUE_FUNCTION<%0...%1> %0636%1
		#endinput
	#elseif UNIQUE_SYMBOL == 636
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (637)
		#define UNIQUE_FUNCTION<%0...%1> %0637%1
		#endinput
	#elseif UNIQUE_SYMBOL == 637
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (638)
		#define UNIQUE_FUNCTION<%0...%1> %0638%1
		#endinput
	#elseif UNIQUE_SYMBOL == 638
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (639)
		#define UNIQUE_FUNCTION<%0...%1> %0639%1
		#endinput
	#elseif UNIQUE_SYMBOL == 639
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (640)
		#define UNIQUE_FUNCTION<%0...%1> %0640%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 650
	#if UNIQUE_SYMBOL == 640
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (641)
		#define UNIQUE_FUNCTION<%0...%1> %0641%1
		#endinput
	#elseif UNIQUE_SYMBOL == 641
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (642)
		#define UNIQUE_FUNCTION<%0...%1> %0642%1
		#endinput
	#elseif UNIQUE_SYMBOL == 642
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (643)
		#define UNIQUE_FUNCTION<%0...%1> %0643%1
		#endinput
	#elseif UNIQUE_SYMBOL == 643
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (644)
		#define UNIQUE_FUNCTION<%0...%1> %0644%1
		#endinput
	#elseif UNIQUE_SYMBOL == 644
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (645)
		#define UNIQUE_FUNCTION<%0...%1> %0645%1
		#endinput
	#elseif UNIQUE_SYMBOL == 645
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (646)
		#define UNIQUE_FUNCTION<%0...%1> %0646%1
		#endinput
	#elseif UNIQUE_SYMBOL == 646
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (647)
		#define UNIQUE_FUNCTION<%0...%1> %0647%1
		#endinput
	#elseif UNIQUE_SYMBOL == 647
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (648)
		#define UNIQUE_FUNCTION<%0...%1> %0648%1
		#endinput
	#elseif UNIQUE_SYMBOL == 648
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (649)
		#define UNIQUE_FUNCTION<%0...%1> %0649%1
		#endinput
	#elseif UNIQUE_SYMBOL == 649
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (650)
		#define UNIQUE_FUNCTION<%0...%1> %0650%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 660
	#if UNIQUE_SYMBOL == 650
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (651)
		#define UNIQUE_FUNCTION<%0...%1> %0651%1
		#endinput
	#elseif UNIQUE_SYMBOL == 651
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (652)
		#define UNIQUE_FUNCTION<%0...%1> %0652%1
		#endinput
	#elseif UNIQUE_SYMBOL == 652
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (653)
		#define UNIQUE_FUNCTION<%0...%1> %0653%1
		#endinput
	#elseif UNIQUE_SYMBOL == 653
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (654)
		#define UNIQUE_FUNCTION<%0...%1> %0654%1
		#endinput
	#elseif UNIQUE_SYMBOL == 654
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (655)
		#define UNIQUE_FUNCTION<%0...%1> %0655%1
		#endinput
	#elseif UNIQUE_SYMBOL == 655
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (656)
		#define UNIQUE_FUNCTION<%0...%1> %0656%1
		#endinput
	#elseif UNIQUE_SYMBOL == 656
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (657)
		#define UNIQUE_FUNCTION<%0...%1> %0657%1
		#endinput
	#elseif UNIQUE_SYMBOL == 657
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (658)
		#define UNIQUE_FUNCTION<%0...%1> %0658%1
		#endinput
	#elseif UNIQUE_SYMBOL == 658
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (659)
		#define UNIQUE_FUNCTION<%0...%1> %0659%1
		#endinput
	#elseif UNIQUE_SYMBOL == 659
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (660)
		#define UNIQUE_FUNCTION<%0...%1> %0660%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 670
	#if UNIQUE_SYMBOL == 660
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (661)
		#define UNIQUE_FUNCTION<%0...%1> %0661%1
		#endinput
	#elseif UNIQUE_SYMBOL == 661
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (662)
		#define UNIQUE_FUNCTION<%0...%1> %0662%1
		#endinput
	#elseif UNIQUE_SYMBOL == 662
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (663)
		#define UNIQUE_FUNCTION<%0...%1> %0663%1
		#endinput
	#elseif UNIQUE_SYMBOL == 663
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (664)
		#define UNIQUE_FUNCTION<%0...%1> %0664%1
		#endinput
	#elseif UNIQUE_SYMBOL == 664
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (665)
		#define UNIQUE_FUNCTION<%0...%1> %0665%1
		#endinput
	#elseif UNIQUE_SYMBOL == 665
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (666)
		#define UNIQUE_FUNCTION<%0...%1> %0666%1
		#endinput
	#elseif UNIQUE_SYMBOL == 666
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (667)
		#define UNIQUE_FUNCTION<%0...%1> %0667%1
		#endinput
	#elseif UNIQUE_SYMBOL == 667
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (668)
		#define UNIQUE_FUNCTION<%0...%1> %0668%1
		#endinput
	#elseif UNIQUE_SYMBOL == 668
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (669)
		#define UNIQUE_FUNCTION<%0...%1> %0669%1
		#endinput
	#elseif UNIQUE_SYMBOL == 669
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (670)
		#define UNIQUE_FUNCTION<%0...%1> %0670%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 680
	#if UNIQUE_SYMBOL == 670
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (671)
		#define UNIQUE_FUNCTION<%0...%1> %0671%1
		#endinput
	#elseif UNIQUE_SYMBOL == 671
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (672)
		#define UNIQUE_FUNCTION<%0...%1> %0672%1
		#endinput
	#elseif UNIQUE_SYMBOL == 672
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (673)
		#define UNIQUE_FUNCTION<%0...%1> %0673%1
		#endinput
	#elseif UNIQUE_SYMBOL == 673
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (674)
		#define UNIQUE_FUNCTION<%0...%1> %0674%1
		#endinput
	#elseif UNIQUE_SYMBOL == 674
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (675)
		#define UNIQUE_FUNCTION<%0...%1> %0675%1
		#endinput
	#elseif UNIQUE_SYMBOL == 675
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (676)
		#define UNIQUE_FUNCTION<%0...%1> %0676%1
		#endinput
	#elseif UNIQUE_SYMBOL == 676
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (677)
		#define UNIQUE_FUNCTION<%0...%1> %0677%1
		#endinput
	#elseif UNIQUE_SYMBOL == 677
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (678)
		#define UNIQUE_FUNCTION<%0...%1> %0678%1
		#endinput
	#elseif UNIQUE_SYMBOL == 678
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (679)
		#define UNIQUE_FUNCTION<%0...%1> %0679%1
		#endinput
	#elseif UNIQUE_SYMBOL == 679
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (680)
		#define UNIQUE_FUNCTION<%0...%1> %0680%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 690
	#if UNIQUE_SYMBOL == 680
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (681)
		#define UNIQUE_FUNCTION<%0...%1> %0681%1
		#endinput
	#elseif UNIQUE_SYMBOL == 681
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (682)
		#define UNIQUE_FUNCTION<%0...%1> %0682%1
		#endinput
	#elseif UNIQUE_SYMBOL == 682
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (683)
		#define UNIQUE_FUNCTION<%0...%1> %0683%1
		#endinput
	#elseif UNIQUE_SYMBOL == 683
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (684)
		#define UNIQUE_FUNCTION<%0...%1> %0684%1
		#endinput
	#elseif UNIQUE_SYMBOL == 684
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (685)
		#define UNIQUE_FUNCTION<%0...%1> %0685%1
		#endinput
	#elseif UNIQUE_SYMBOL == 685
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (686)
		#define UNIQUE_FUNCTION<%0...%1> %0686%1
		#endinput
	#elseif UNIQUE_SYMBOL == 686
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (687)
		#define UNIQUE_FUNCTION<%0...%1> %0687%1
		#endinput
	#elseif UNIQUE_SYMBOL == 687
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (688)
		#define UNIQUE_FUNCTION<%0...%1> %0688%1
		#endinput
	#elseif UNIQUE_SYMBOL == 688
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (689)
		#define UNIQUE_FUNCTION<%0...%1> %0689%1
		#endinput
	#elseif UNIQUE_SYMBOL == 689
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (690)
		#define UNIQUE_FUNCTION<%0...%1> %0690%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 700
	#if UNIQUE_SYMBOL == 690
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (691)
		#define UNIQUE_FUNCTION<%0...%1> %0691%1
		#endinput
	#elseif UNIQUE_SYMBOL == 691
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (692)
		#define UNIQUE_FUNCTION<%0...%1> %0692%1
		#endinput
	#elseif UNIQUE_SYMBOL == 692
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (693)
		#define UNIQUE_FUNCTION<%0...%1> %0693%1
		#endinput
	#elseif UNIQUE_SYMBOL == 693
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (694)
		#define UNIQUE_FUNCTION<%0...%1> %0694%1
		#endinput
	#elseif UNIQUE_SYMBOL == 694
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (695)
		#define UNIQUE_FUNCTION<%0...%1> %0695%1
		#endinput
	#elseif UNIQUE_SYMBOL == 695
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (696)
		#define UNIQUE_FUNCTION<%0...%1> %0696%1
		#endinput
	#elseif UNIQUE_SYMBOL == 696
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (697)
		#define UNIQUE_FUNCTION<%0...%1> %0697%1
		#endinput
	#elseif UNIQUE_SYMBOL == 697
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (698)
		#define UNIQUE_FUNCTION<%0...%1> %0698%1
		#endinput
	#elseif UNIQUE_SYMBOL == 698
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (699)
		#define UNIQUE_FUNCTION<%0...%1> %0699%1
		#endinput
	#elseif UNIQUE_SYMBOL == 699
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (700)
		#define UNIQUE_FUNCTION<%0...%1> %0700%1
		#endinput
	#endif
#endif

