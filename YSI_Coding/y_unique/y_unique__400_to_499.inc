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

static stock const Y_UNIQUE_400_to_499_CALLED = cellmin;

#if defined _inc_y_unique__400_to_499
	#undef _inc_y_unique__400_to_499
#endif

#if UNIQUE_SYMBOL < 410
	#if UNIQUE_SYMBOL == 400
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (401)
		#define UNIQUE_FUNCTION<%0...%1> %0401%1
		#endinput
	#elseif UNIQUE_SYMBOL == 401
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (402)
		#define UNIQUE_FUNCTION<%0...%1> %0402%1
		#endinput
	#elseif UNIQUE_SYMBOL == 402
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (403)
		#define UNIQUE_FUNCTION<%0...%1> %0403%1
		#endinput
	#elseif UNIQUE_SYMBOL == 403
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (404)
		#define UNIQUE_FUNCTION<%0...%1> %0404%1
		#endinput
	#elseif UNIQUE_SYMBOL == 404
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (405)
		#define UNIQUE_FUNCTION<%0...%1> %0405%1
		#endinput
	#elseif UNIQUE_SYMBOL == 405
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (406)
		#define UNIQUE_FUNCTION<%0...%1> %0406%1
		#endinput
	#elseif UNIQUE_SYMBOL == 406
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (407)
		#define UNIQUE_FUNCTION<%0...%1> %0407%1
		#endinput
	#elseif UNIQUE_SYMBOL == 407
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (408)
		#define UNIQUE_FUNCTION<%0...%1> %0408%1
		#endinput
	#elseif UNIQUE_SYMBOL == 408
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (409)
		#define UNIQUE_FUNCTION<%0...%1> %0409%1
		#endinput
	#elseif UNIQUE_SYMBOL == 409
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (410)
		#define UNIQUE_FUNCTION<%0...%1> %0410%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 420
	#if UNIQUE_SYMBOL == 410
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (411)
		#define UNIQUE_FUNCTION<%0...%1> %0411%1
		#endinput
	#elseif UNIQUE_SYMBOL == 411
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (412)
		#define UNIQUE_FUNCTION<%0...%1> %0412%1
		#endinput
	#elseif UNIQUE_SYMBOL == 412
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (413)
		#define UNIQUE_FUNCTION<%0...%1> %0413%1
		#endinput
	#elseif UNIQUE_SYMBOL == 413
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (414)
		#define UNIQUE_FUNCTION<%0...%1> %0414%1
		#endinput
	#elseif UNIQUE_SYMBOL == 414
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (415)
		#define UNIQUE_FUNCTION<%0...%1> %0415%1
		#endinput
	#elseif UNIQUE_SYMBOL == 415
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (416)
		#define UNIQUE_FUNCTION<%0...%1> %0416%1
		#endinput
	#elseif UNIQUE_SYMBOL == 416
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (417)
		#define UNIQUE_FUNCTION<%0...%1> %0417%1
		#endinput
	#elseif UNIQUE_SYMBOL == 417
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (418)
		#define UNIQUE_FUNCTION<%0...%1> %0418%1
		#endinput
	#elseif UNIQUE_SYMBOL == 418
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (419)
		#define UNIQUE_FUNCTION<%0...%1> %0419%1
		#endinput
	#elseif UNIQUE_SYMBOL == 419
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (420)
		#define UNIQUE_FUNCTION<%0...%1> %0420%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 430
	#if UNIQUE_SYMBOL == 420
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (421)
		#define UNIQUE_FUNCTION<%0...%1> %0421%1
		#endinput
	#elseif UNIQUE_SYMBOL == 421
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (422)
		#define UNIQUE_FUNCTION<%0...%1> %0422%1
		#endinput
	#elseif UNIQUE_SYMBOL == 422
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (423)
		#define UNIQUE_FUNCTION<%0...%1> %0423%1
		#endinput
	#elseif UNIQUE_SYMBOL == 423
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (424)
		#define UNIQUE_FUNCTION<%0...%1> %0424%1
		#endinput
	#elseif UNIQUE_SYMBOL == 424
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (425)
		#define UNIQUE_FUNCTION<%0...%1> %0425%1
		#endinput
	#elseif UNIQUE_SYMBOL == 425
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (426)
		#define UNIQUE_FUNCTION<%0...%1> %0426%1
		#endinput
	#elseif UNIQUE_SYMBOL == 426
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (427)
		#define UNIQUE_FUNCTION<%0...%1> %0427%1
		#endinput
	#elseif UNIQUE_SYMBOL == 427
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (428)
		#define UNIQUE_FUNCTION<%0...%1> %0428%1
		#endinput
	#elseif UNIQUE_SYMBOL == 428
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (429)
		#define UNIQUE_FUNCTION<%0...%1> %0429%1
		#endinput
	#elseif UNIQUE_SYMBOL == 429
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (430)
		#define UNIQUE_FUNCTION<%0...%1> %0430%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 440
	#if UNIQUE_SYMBOL == 430
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (431)
		#define UNIQUE_FUNCTION<%0...%1> %0431%1
		#endinput
	#elseif UNIQUE_SYMBOL == 431
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (432)
		#define UNIQUE_FUNCTION<%0...%1> %0432%1
		#endinput
	#elseif UNIQUE_SYMBOL == 432
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (433)
		#define UNIQUE_FUNCTION<%0...%1> %0433%1
		#endinput
	#elseif UNIQUE_SYMBOL == 433
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (434)
		#define UNIQUE_FUNCTION<%0...%1> %0434%1
		#endinput
	#elseif UNIQUE_SYMBOL == 434
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (435)
		#define UNIQUE_FUNCTION<%0...%1> %0435%1
		#endinput
	#elseif UNIQUE_SYMBOL == 435
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (436)
		#define UNIQUE_FUNCTION<%0...%1> %0436%1
		#endinput
	#elseif UNIQUE_SYMBOL == 436
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (437)
		#define UNIQUE_FUNCTION<%0...%1> %0437%1
		#endinput
	#elseif UNIQUE_SYMBOL == 437
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (438)
		#define UNIQUE_FUNCTION<%0...%1> %0438%1
		#endinput
	#elseif UNIQUE_SYMBOL == 438
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (439)
		#define UNIQUE_FUNCTION<%0...%1> %0439%1
		#endinput
	#elseif UNIQUE_SYMBOL == 439
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (440)
		#define UNIQUE_FUNCTION<%0...%1> %0440%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 450
	#if UNIQUE_SYMBOL == 440
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (441)
		#define UNIQUE_FUNCTION<%0...%1> %0441%1
		#endinput
	#elseif UNIQUE_SYMBOL == 441
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (442)
		#define UNIQUE_FUNCTION<%0...%1> %0442%1
		#endinput
	#elseif UNIQUE_SYMBOL == 442
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (443)
		#define UNIQUE_FUNCTION<%0...%1> %0443%1
		#endinput
	#elseif UNIQUE_SYMBOL == 443
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (444)
		#define UNIQUE_FUNCTION<%0...%1> %0444%1
		#endinput
	#elseif UNIQUE_SYMBOL == 444
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (445)
		#define UNIQUE_FUNCTION<%0...%1> %0445%1
		#endinput
	#elseif UNIQUE_SYMBOL == 445
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (446)
		#define UNIQUE_FUNCTION<%0...%1> %0446%1
		#endinput
	#elseif UNIQUE_SYMBOL == 446
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (447)
		#define UNIQUE_FUNCTION<%0...%1> %0447%1
		#endinput
	#elseif UNIQUE_SYMBOL == 447
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (448)
		#define UNIQUE_FUNCTION<%0...%1> %0448%1
		#endinput
	#elseif UNIQUE_SYMBOL == 448
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (449)
		#define UNIQUE_FUNCTION<%0...%1> %0449%1
		#endinput
	#elseif UNIQUE_SYMBOL == 449
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (450)
		#define UNIQUE_FUNCTION<%0...%1> %0450%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 460
	#if UNIQUE_SYMBOL == 450
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (451)
		#define UNIQUE_FUNCTION<%0...%1> %0451%1
		#endinput
	#elseif UNIQUE_SYMBOL == 451
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (452)
		#define UNIQUE_FUNCTION<%0...%1> %0452%1
		#endinput
	#elseif UNIQUE_SYMBOL == 452
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (453)
		#define UNIQUE_FUNCTION<%0...%1> %0453%1
		#endinput
	#elseif UNIQUE_SYMBOL == 453
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (454)
		#define UNIQUE_FUNCTION<%0...%1> %0454%1
		#endinput
	#elseif UNIQUE_SYMBOL == 454
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (455)
		#define UNIQUE_FUNCTION<%0...%1> %0455%1
		#endinput
	#elseif UNIQUE_SYMBOL == 455
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (456)
		#define UNIQUE_FUNCTION<%0...%1> %0456%1
		#endinput
	#elseif UNIQUE_SYMBOL == 456
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (457)
		#define UNIQUE_FUNCTION<%0...%1> %0457%1
		#endinput
	#elseif UNIQUE_SYMBOL == 457
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (458)
		#define UNIQUE_FUNCTION<%0...%1> %0458%1
		#endinput
	#elseif UNIQUE_SYMBOL == 458
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (459)
		#define UNIQUE_FUNCTION<%0...%1> %0459%1
		#endinput
	#elseif UNIQUE_SYMBOL == 459
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (460)
		#define UNIQUE_FUNCTION<%0...%1> %0460%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 470
	#if UNIQUE_SYMBOL == 460
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (461)
		#define UNIQUE_FUNCTION<%0...%1> %0461%1
		#endinput
	#elseif UNIQUE_SYMBOL == 461
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (462)
		#define UNIQUE_FUNCTION<%0...%1> %0462%1
		#endinput
	#elseif UNIQUE_SYMBOL == 462
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (463)
		#define UNIQUE_FUNCTION<%0...%1> %0463%1
		#endinput
	#elseif UNIQUE_SYMBOL == 463
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (464)
		#define UNIQUE_FUNCTION<%0...%1> %0464%1
		#endinput
	#elseif UNIQUE_SYMBOL == 464
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (465)
		#define UNIQUE_FUNCTION<%0...%1> %0465%1
		#endinput
	#elseif UNIQUE_SYMBOL == 465
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (466)
		#define UNIQUE_FUNCTION<%0...%1> %0466%1
		#endinput
	#elseif UNIQUE_SYMBOL == 466
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (467)
		#define UNIQUE_FUNCTION<%0...%1> %0467%1
		#endinput
	#elseif UNIQUE_SYMBOL == 467
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (468)
		#define UNIQUE_FUNCTION<%0...%1> %0468%1
		#endinput
	#elseif UNIQUE_SYMBOL == 468
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (469)
		#define UNIQUE_FUNCTION<%0...%1> %0469%1
		#endinput
	#elseif UNIQUE_SYMBOL == 469
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (470)
		#define UNIQUE_FUNCTION<%0...%1> %0470%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 480
	#if UNIQUE_SYMBOL == 470
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (471)
		#define UNIQUE_FUNCTION<%0...%1> %0471%1
		#endinput
	#elseif UNIQUE_SYMBOL == 471
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (472)
		#define UNIQUE_FUNCTION<%0...%1> %0472%1
		#endinput
	#elseif UNIQUE_SYMBOL == 472
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (473)
		#define UNIQUE_FUNCTION<%0...%1> %0473%1
		#endinput
	#elseif UNIQUE_SYMBOL == 473
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (474)
		#define UNIQUE_FUNCTION<%0...%1> %0474%1
		#endinput
	#elseif UNIQUE_SYMBOL == 474
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (475)
		#define UNIQUE_FUNCTION<%0...%1> %0475%1
		#endinput
	#elseif UNIQUE_SYMBOL == 475
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (476)
		#define UNIQUE_FUNCTION<%0...%1> %0476%1
		#endinput
	#elseif UNIQUE_SYMBOL == 476
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (477)
		#define UNIQUE_FUNCTION<%0...%1> %0477%1
		#endinput
	#elseif UNIQUE_SYMBOL == 477
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (478)
		#define UNIQUE_FUNCTION<%0...%1> %0478%1
		#endinput
	#elseif UNIQUE_SYMBOL == 478
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (479)
		#define UNIQUE_FUNCTION<%0...%1> %0479%1
		#endinput
	#elseif UNIQUE_SYMBOL == 479
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (480)
		#define UNIQUE_FUNCTION<%0...%1> %0480%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 490
	#if UNIQUE_SYMBOL == 480
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (481)
		#define UNIQUE_FUNCTION<%0...%1> %0481%1
		#endinput
	#elseif UNIQUE_SYMBOL == 481
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (482)
		#define UNIQUE_FUNCTION<%0...%1> %0482%1
		#endinput
	#elseif UNIQUE_SYMBOL == 482
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (483)
		#define UNIQUE_FUNCTION<%0...%1> %0483%1
		#endinput
	#elseif UNIQUE_SYMBOL == 483
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (484)
		#define UNIQUE_FUNCTION<%0...%1> %0484%1
		#endinput
	#elseif UNIQUE_SYMBOL == 484
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (485)
		#define UNIQUE_FUNCTION<%0...%1> %0485%1
		#endinput
	#elseif UNIQUE_SYMBOL == 485
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (486)
		#define UNIQUE_FUNCTION<%0...%1> %0486%1
		#endinput
	#elseif UNIQUE_SYMBOL == 486
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (487)
		#define UNIQUE_FUNCTION<%0...%1> %0487%1
		#endinput
	#elseif UNIQUE_SYMBOL == 487
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (488)
		#define UNIQUE_FUNCTION<%0...%1> %0488%1
		#endinput
	#elseif UNIQUE_SYMBOL == 488
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (489)
		#define UNIQUE_FUNCTION<%0...%1> %0489%1
		#endinput
	#elseif UNIQUE_SYMBOL == 489
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (490)
		#define UNIQUE_FUNCTION<%0...%1> %0490%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 500
	#if UNIQUE_SYMBOL == 490
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (491)
		#define UNIQUE_FUNCTION<%0...%1> %0491%1
		#endinput
	#elseif UNIQUE_SYMBOL == 491
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (492)
		#define UNIQUE_FUNCTION<%0...%1> %0492%1
		#endinput
	#elseif UNIQUE_SYMBOL == 492
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (493)
		#define UNIQUE_FUNCTION<%0...%1> %0493%1
		#endinput
	#elseif UNIQUE_SYMBOL == 493
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (494)
		#define UNIQUE_FUNCTION<%0...%1> %0494%1
		#endinput
	#elseif UNIQUE_SYMBOL == 494
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (495)
		#define UNIQUE_FUNCTION<%0...%1> %0495%1
		#endinput
	#elseif UNIQUE_SYMBOL == 495
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (496)
		#define UNIQUE_FUNCTION<%0...%1> %0496%1
		#endinput
	#elseif UNIQUE_SYMBOL == 496
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (497)
		#define UNIQUE_FUNCTION<%0...%1> %0497%1
		#endinput
	#elseif UNIQUE_SYMBOL == 497
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (498)
		#define UNIQUE_FUNCTION<%0...%1> %0498%1
		#endinput
	#elseif UNIQUE_SYMBOL == 498
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (499)
		#define UNIQUE_FUNCTION<%0...%1> %0499%1
		#endinput
	#elseif UNIQUE_SYMBOL == 499
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (500)
		#define UNIQUE_FUNCTION<%0...%1> %0500%1
		#endinput
	#endif
#endif

