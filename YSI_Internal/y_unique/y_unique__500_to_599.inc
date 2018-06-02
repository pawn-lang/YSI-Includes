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

static stock const Y_UNIQUE_500_to_599_CALLED;

#if defined _inc__500_to_599
	#undef _inc__500_to_599
#endif

#if UNIQUE_SYMBOL < 510
	#if UNIQUE_SYMBOL == 500
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (501)
		#define UNIQUE_FUNCTION<%0...%1> %0501%1
		#endinput
	#elseif UNIQUE_SYMBOL == 501
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (502)
		#define UNIQUE_FUNCTION<%0...%1> %0502%1
		#endinput
	#elseif UNIQUE_SYMBOL == 502
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (503)
		#define UNIQUE_FUNCTION<%0...%1> %0503%1
		#endinput
	#elseif UNIQUE_SYMBOL == 503
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (504)
		#define UNIQUE_FUNCTION<%0...%1> %0504%1
		#endinput
	#elseif UNIQUE_SYMBOL == 504
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (505)
		#define UNIQUE_FUNCTION<%0...%1> %0505%1
		#endinput
	#elseif UNIQUE_SYMBOL == 505
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (506)
		#define UNIQUE_FUNCTION<%0...%1> %0506%1
		#endinput
	#elseif UNIQUE_SYMBOL == 506
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (507)
		#define UNIQUE_FUNCTION<%0...%1> %0507%1
		#endinput
	#elseif UNIQUE_SYMBOL == 507
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (508)
		#define UNIQUE_FUNCTION<%0...%1> %0508%1
		#endinput
	#elseif UNIQUE_SYMBOL == 508
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (509)
		#define UNIQUE_FUNCTION<%0...%1> %0509%1
		#endinput
	#elseif UNIQUE_SYMBOL == 509
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (510)
		#define UNIQUE_FUNCTION<%0...%1> %0510%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 520
	#if UNIQUE_SYMBOL == 510
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (511)
		#define UNIQUE_FUNCTION<%0...%1> %0511%1
		#endinput
	#elseif UNIQUE_SYMBOL == 511
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (512)
		#define UNIQUE_FUNCTION<%0...%1> %0512%1
		#endinput
	#elseif UNIQUE_SYMBOL == 512
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (513)
		#define UNIQUE_FUNCTION<%0...%1> %0513%1
		#endinput
	#elseif UNIQUE_SYMBOL == 513
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (514)
		#define UNIQUE_FUNCTION<%0...%1> %0514%1
		#endinput
	#elseif UNIQUE_SYMBOL == 514
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (515)
		#define UNIQUE_FUNCTION<%0...%1> %0515%1
		#endinput
	#elseif UNIQUE_SYMBOL == 515
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (516)
		#define UNIQUE_FUNCTION<%0...%1> %0516%1
		#endinput
	#elseif UNIQUE_SYMBOL == 516
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (517)
		#define UNIQUE_FUNCTION<%0...%1> %0517%1
		#endinput
	#elseif UNIQUE_SYMBOL == 517
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (518)
		#define UNIQUE_FUNCTION<%0...%1> %0518%1
		#endinput
	#elseif UNIQUE_SYMBOL == 518
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (519)
		#define UNIQUE_FUNCTION<%0...%1> %0519%1
		#endinput
	#elseif UNIQUE_SYMBOL == 519
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (520)
		#define UNIQUE_FUNCTION<%0...%1> %0520%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 530
	#if UNIQUE_SYMBOL == 520
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (521)
		#define UNIQUE_FUNCTION<%0...%1> %0521%1
		#endinput
	#elseif UNIQUE_SYMBOL == 521
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (522)
		#define UNIQUE_FUNCTION<%0...%1> %0522%1
		#endinput
	#elseif UNIQUE_SYMBOL == 522
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (523)
		#define UNIQUE_FUNCTION<%0...%1> %0523%1
		#endinput
	#elseif UNIQUE_SYMBOL == 523
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (524)
		#define UNIQUE_FUNCTION<%0...%1> %0524%1
		#endinput
	#elseif UNIQUE_SYMBOL == 524
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (525)
		#define UNIQUE_FUNCTION<%0...%1> %0525%1
		#endinput
	#elseif UNIQUE_SYMBOL == 525
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (526)
		#define UNIQUE_FUNCTION<%0...%1> %0526%1
		#endinput
	#elseif UNIQUE_SYMBOL == 526
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (527)
		#define UNIQUE_FUNCTION<%0...%1> %0527%1
		#endinput
	#elseif UNIQUE_SYMBOL == 527
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (528)
		#define UNIQUE_FUNCTION<%0...%1> %0528%1
		#endinput
	#elseif UNIQUE_SYMBOL == 528
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (529)
		#define UNIQUE_FUNCTION<%0...%1> %0529%1
		#endinput
	#elseif UNIQUE_SYMBOL == 529
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (530)
		#define UNIQUE_FUNCTION<%0...%1> %0530%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 540
	#if UNIQUE_SYMBOL == 530
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (531)
		#define UNIQUE_FUNCTION<%0...%1> %0531%1
		#endinput
	#elseif UNIQUE_SYMBOL == 531
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (532)
		#define UNIQUE_FUNCTION<%0...%1> %0532%1
		#endinput
	#elseif UNIQUE_SYMBOL == 532
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (533)
		#define UNIQUE_FUNCTION<%0...%1> %0533%1
		#endinput
	#elseif UNIQUE_SYMBOL == 533
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (534)
		#define UNIQUE_FUNCTION<%0...%1> %0534%1
		#endinput
	#elseif UNIQUE_SYMBOL == 534
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (535)
		#define UNIQUE_FUNCTION<%0...%1> %0535%1
		#endinput
	#elseif UNIQUE_SYMBOL == 535
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (536)
		#define UNIQUE_FUNCTION<%0...%1> %0536%1
		#endinput
	#elseif UNIQUE_SYMBOL == 536
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (537)
		#define UNIQUE_FUNCTION<%0...%1> %0537%1
		#endinput
	#elseif UNIQUE_SYMBOL == 537
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (538)
		#define UNIQUE_FUNCTION<%0...%1> %0538%1
		#endinput
	#elseif UNIQUE_SYMBOL == 538
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (539)
		#define UNIQUE_FUNCTION<%0...%1> %0539%1
		#endinput
	#elseif UNIQUE_SYMBOL == 539
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (540)
		#define UNIQUE_FUNCTION<%0...%1> %0540%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 550
	#if UNIQUE_SYMBOL == 540
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (541)
		#define UNIQUE_FUNCTION<%0...%1> %0541%1
		#endinput
	#elseif UNIQUE_SYMBOL == 541
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (542)
		#define UNIQUE_FUNCTION<%0...%1> %0542%1
		#endinput
	#elseif UNIQUE_SYMBOL == 542
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (543)
		#define UNIQUE_FUNCTION<%0...%1> %0543%1
		#endinput
	#elseif UNIQUE_SYMBOL == 543
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (544)
		#define UNIQUE_FUNCTION<%0...%1> %0544%1
		#endinput
	#elseif UNIQUE_SYMBOL == 544
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (545)
		#define UNIQUE_FUNCTION<%0...%1> %0545%1
		#endinput
	#elseif UNIQUE_SYMBOL == 545
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (546)
		#define UNIQUE_FUNCTION<%0...%1> %0546%1
		#endinput
	#elseif UNIQUE_SYMBOL == 546
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (547)
		#define UNIQUE_FUNCTION<%0...%1> %0547%1
		#endinput
	#elseif UNIQUE_SYMBOL == 547
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (548)
		#define UNIQUE_FUNCTION<%0...%1> %0548%1
		#endinput
	#elseif UNIQUE_SYMBOL == 548
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (549)
		#define UNIQUE_FUNCTION<%0...%1> %0549%1
		#endinput
	#elseif UNIQUE_SYMBOL == 549
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (550)
		#define UNIQUE_FUNCTION<%0...%1> %0550%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 560
	#if UNIQUE_SYMBOL == 550
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (551)
		#define UNIQUE_FUNCTION<%0...%1> %0551%1
		#endinput
	#elseif UNIQUE_SYMBOL == 551
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (552)
		#define UNIQUE_FUNCTION<%0...%1> %0552%1
		#endinput
	#elseif UNIQUE_SYMBOL == 552
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (553)
		#define UNIQUE_FUNCTION<%0...%1> %0553%1
		#endinput
	#elseif UNIQUE_SYMBOL == 553
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (554)
		#define UNIQUE_FUNCTION<%0...%1> %0554%1
		#endinput
	#elseif UNIQUE_SYMBOL == 554
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (555)
		#define UNIQUE_FUNCTION<%0...%1> %0555%1
		#endinput
	#elseif UNIQUE_SYMBOL == 555
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (556)
		#define UNIQUE_FUNCTION<%0...%1> %0556%1
		#endinput
	#elseif UNIQUE_SYMBOL == 556
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (557)
		#define UNIQUE_FUNCTION<%0...%1> %0557%1
		#endinput
	#elseif UNIQUE_SYMBOL == 557
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (558)
		#define UNIQUE_FUNCTION<%0...%1> %0558%1
		#endinput
	#elseif UNIQUE_SYMBOL == 558
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (559)
		#define UNIQUE_FUNCTION<%0...%1> %0559%1
		#endinput
	#elseif UNIQUE_SYMBOL == 559
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (560)
		#define UNIQUE_FUNCTION<%0...%1> %0560%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 570
	#if UNIQUE_SYMBOL == 560
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (561)
		#define UNIQUE_FUNCTION<%0...%1> %0561%1
		#endinput
	#elseif UNIQUE_SYMBOL == 561
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (562)
		#define UNIQUE_FUNCTION<%0...%1> %0562%1
		#endinput
	#elseif UNIQUE_SYMBOL == 562
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (563)
		#define UNIQUE_FUNCTION<%0...%1> %0563%1
		#endinput
	#elseif UNIQUE_SYMBOL == 563
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (564)
		#define UNIQUE_FUNCTION<%0...%1> %0564%1
		#endinput
	#elseif UNIQUE_SYMBOL == 564
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (565)
		#define UNIQUE_FUNCTION<%0...%1> %0565%1
		#endinput
	#elseif UNIQUE_SYMBOL == 565
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (566)
		#define UNIQUE_FUNCTION<%0...%1> %0566%1
		#endinput
	#elseif UNIQUE_SYMBOL == 566
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (567)
		#define UNIQUE_FUNCTION<%0...%1> %0567%1
		#endinput
	#elseif UNIQUE_SYMBOL == 567
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (568)
		#define UNIQUE_FUNCTION<%0...%1> %0568%1
		#endinput
	#elseif UNIQUE_SYMBOL == 568
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (569)
		#define UNIQUE_FUNCTION<%0...%1> %0569%1
		#endinput
	#elseif UNIQUE_SYMBOL == 569
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (570)
		#define UNIQUE_FUNCTION<%0...%1> %0570%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 580
	#if UNIQUE_SYMBOL == 570
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (571)
		#define UNIQUE_FUNCTION<%0...%1> %0571%1
		#endinput
	#elseif UNIQUE_SYMBOL == 571
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (572)
		#define UNIQUE_FUNCTION<%0...%1> %0572%1
		#endinput
	#elseif UNIQUE_SYMBOL == 572
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (573)
		#define UNIQUE_FUNCTION<%0...%1> %0573%1
		#endinput
	#elseif UNIQUE_SYMBOL == 573
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (574)
		#define UNIQUE_FUNCTION<%0...%1> %0574%1
		#endinput
	#elseif UNIQUE_SYMBOL == 574
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (575)
		#define UNIQUE_FUNCTION<%0...%1> %0575%1
		#endinput
	#elseif UNIQUE_SYMBOL == 575
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (576)
		#define UNIQUE_FUNCTION<%0...%1> %0576%1
		#endinput
	#elseif UNIQUE_SYMBOL == 576
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (577)
		#define UNIQUE_FUNCTION<%0...%1> %0577%1
		#endinput
	#elseif UNIQUE_SYMBOL == 577
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (578)
		#define UNIQUE_FUNCTION<%0...%1> %0578%1
		#endinput
	#elseif UNIQUE_SYMBOL == 578
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (579)
		#define UNIQUE_FUNCTION<%0...%1> %0579%1
		#endinput
	#elseif UNIQUE_SYMBOL == 579
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (580)
		#define UNIQUE_FUNCTION<%0...%1> %0580%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 590
	#if UNIQUE_SYMBOL == 580
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (581)
		#define UNIQUE_FUNCTION<%0...%1> %0581%1
		#endinput
	#elseif UNIQUE_SYMBOL == 581
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (582)
		#define UNIQUE_FUNCTION<%0...%1> %0582%1
		#endinput
	#elseif UNIQUE_SYMBOL == 582
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (583)
		#define UNIQUE_FUNCTION<%0...%1> %0583%1
		#endinput
	#elseif UNIQUE_SYMBOL == 583
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (584)
		#define UNIQUE_FUNCTION<%0...%1> %0584%1
		#endinput
	#elseif UNIQUE_SYMBOL == 584
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (585)
		#define UNIQUE_FUNCTION<%0...%1> %0585%1
		#endinput
	#elseif UNIQUE_SYMBOL == 585
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (586)
		#define UNIQUE_FUNCTION<%0...%1> %0586%1
		#endinput
	#elseif UNIQUE_SYMBOL == 586
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (587)
		#define UNIQUE_FUNCTION<%0...%1> %0587%1
		#endinput
	#elseif UNIQUE_SYMBOL == 587
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (588)
		#define UNIQUE_FUNCTION<%0...%1> %0588%1
		#endinput
	#elseif UNIQUE_SYMBOL == 588
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (589)
		#define UNIQUE_FUNCTION<%0...%1> %0589%1
		#endinput
	#elseif UNIQUE_SYMBOL == 589
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (590)
		#define UNIQUE_FUNCTION<%0...%1> %0590%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 600
	#if UNIQUE_SYMBOL == 590
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (591)
		#define UNIQUE_FUNCTION<%0...%1> %0591%1
		#endinput
	#elseif UNIQUE_SYMBOL == 591
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (592)
		#define UNIQUE_FUNCTION<%0...%1> %0592%1
		#endinput
	#elseif UNIQUE_SYMBOL == 592
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (593)
		#define UNIQUE_FUNCTION<%0...%1> %0593%1
		#endinput
	#elseif UNIQUE_SYMBOL == 593
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (594)
		#define UNIQUE_FUNCTION<%0...%1> %0594%1
		#endinput
	#elseif UNIQUE_SYMBOL == 594
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (595)
		#define UNIQUE_FUNCTION<%0...%1> %0595%1
		#endinput
	#elseif UNIQUE_SYMBOL == 595
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (596)
		#define UNIQUE_FUNCTION<%0...%1> %0596%1
		#endinput
	#elseif UNIQUE_SYMBOL == 596
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (597)
		#define UNIQUE_FUNCTION<%0...%1> %0597%1
		#endinput
	#elseif UNIQUE_SYMBOL == 597
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (598)
		#define UNIQUE_FUNCTION<%0...%1> %0598%1
		#endinput
	#elseif UNIQUE_SYMBOL == 598
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (599)
		#define UNIQUE_FUNCTION<%0...%1> %0599%1
		#endinput
	#elseif UNIQUE_SYMBOL == 599
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (600)
		#define UNIQUE_FUNCTION<%0...%1> %0600%1
		#endinput
	#endif
#endif

