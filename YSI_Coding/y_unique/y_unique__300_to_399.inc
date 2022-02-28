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

static stock const Y_UNIQUE_300_to_399_CALLED = cellmin;

#if defined _inc_y_unique__300_to_399
	#undef _inc_y_unique__300_to_399
#endif

#if UNIQUE_SYMBOL < 310
	#if UNIQUE_SYMBOL == 300
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (301)
		#define UNIQUE_FUNCTION<%0...%1> %0301%1
		#endinput
	#elseif UNIQUE_SYMBOL == 301
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (302)
		#define UNIQUE_FUNCTION<%0...%1> %0302%1
		#endinput
	#elseif UNIQUE_SYMBOL == 302
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (303)
		#define UNIQUE_FUNCTION<%0...%1> %0303%1
		#endinput
	#elseif UNIQUE_SYMBOL == 303
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (304)
		#define UNIQUE_FUNCTION<%0...%1> %0304%1
		#endinput
	#elseif UNIQUE_SYMBOL == 304
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (305)
		#define UNIQUE_FUNCTION<%0...%1> %0305%1
		#endinput
	#elseif UNIQUE_SYMBOL == 305
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (306)
		#define UNIQUE_FUNCTION<%0...%1> %0306%1
		#endinput
	#elseif UNIQUE_SYMBOL == 306
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (307)
		#define UNIQUE_FUNCTION<%0...%1> %0307%1
		#endinput
	#elseif UNIQUE_SYMBOL == 307
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (308)
		#define UNIQUE_FUNCTION<%0...%1> %0308%1
		#endinput
	#elseif UNIQUE_SYMBOL == 308
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (309)
		#define UNIQUE_FUNCTION<%0...%1> %0309%1
		#endinput
	#elseif UNIQUE_SYMBOL == 309
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (310)
		#define UNIQUE_FUNCTION<%0...%1> %0310%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 320
	#if UNIQUE_SYMBOL == 310
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (311)
		#define UNIQUE_FUNCTION<%0...%1> %0311%1
		#endinput
	#elseif UNIQUE_SYMBOL == 311
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (312)
		#define UNIQUE_FUNCTION<%0...%1> %0312%1
		#endinput
	#elseif UNIQUE_SYMBOL == 312
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (313)
		#define UNIQUE_FUNCTION<%0...%1> %0313%1
		#endinput
	#elseif UNIQUE_SYMBOL == 313
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (314)
		#define UNIQUE_FUNCTION<%0...%1> %0314%1
		#endinput
	#elseif UNIQUE_SYMBOL == 314
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (315)
		#define UNIQUE_FUNCTION<%0...%1> %0315%1
		#endinput
	#elseif UNIQUE_SYMBOL == 315
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (316)
		#define UNIQUE_FUNCTION<%0...%1> %0316%1
		#endinput
	#elseif UNIQUE_SYMBOL == 316
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (317)
		#define UNIQUE_FUNCTION<%0...%1> %0317%1
		#endinput
	#elseif UNIQUE_SYMBOL == 317
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (318)
		#define UNIQUE_FUNCTION<%0...%1> %0318%1
		#endinput
	#elseif UNIQUE_SYMBOL == 318
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (319)
		#define UNIQUE_FUNCTION<%0...%1> %0319%1
		#endinput
	#elseif UNIQUE_SYMBOL == 319
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (320)
		#define UNIQUE_FUNCTION<%0...%1> %0320%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 330
	#if UNIQUE_SYMBOL == 320
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (321)
		#define UNIQUE_FUNCTION<%0...%1> %0321%1
		#endinput
	#elseif UNIQUE_SYMBOL == 321
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (322)
		#define UNIQUE_FUNCTION<%0...%1> %0322%1
		#endinput
	#elseif UNIQUE_SYMBOL == 322
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (323)
		#define UNIQUE_FUNCTION<%0...%1> %0323%1
		#endinput
	#elseif UNIQUE_SYMBOL == 323
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (324)
		#define UNIQUE_FUNCTION<%0...%1> %0324%1
		#endinput
	#elseif UNIQUE_SYMBOL == 324
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (325)
		#define UNIQUE_FUNCTION<%0...%1> %0325%1
		#endinput
	#elseif UNIQUE_SYMBOL == 325
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (326)
		#define UNIQUE_FUNCTION<%0...%1> %0326%1
		#endinput
	#elseif UNIQUE_SYMBOL == 326
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (327)
		#define UNIQUE_FUNCTION<%0...%1> %0327%1
		#endinput
	#elseif UNIQUE_SYMBOL == 327
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (328)
		#define UNIQUE_FUNCTION<%0...%1> %0328%1
		#endinput
	#elseif UNIQUE_SYMBOL == 328
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (329)
		#define UNIQUE_FUNCTION<%0...%1> %0329%1
		#endinput
	#elseif UNIQUE_SYMBOL == 329
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (330)
		#define UNIQUE_FUNCTION<%0...%1> %0330%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 340
	#if UNIQUE_SYMBOL == 330
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (331)
		#define UNIQUE_FUNCTION<%0...%1> %0331%1
		#endinput
	#elseif UNIQUE_SYMBOL == 331
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (332)
		#define UNIQUE_FUNCTION<%0...%1> %0332%1
		#endinput
	#elseif UNIQUE_SYMBOL == 332
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (333)
		#define UNIQUE_FUNCTION<%0...%1> %0333%1
		#endinput
	#elseif UNIQUE_SYMBOL == 333
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (334)
		#define UNIQUE_FUNCTION<%0...%1> %0334%1
		#endinput
	#elseif UNIQUE_SYMBOL == 334
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (335)
		#define UNIQUE_FUNCTION<%0...%1> %0335%1
		#endinput
	#elseif UNIQUE_SYMBOL == 335
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (336)
		#define UNIQUE_FUNCTION<%0...%1> %0336%1
		#endinput
	#elseif UNIQUE_SYMBOL == 336
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (337)
		#define UNIQUE_FUNCTION<%0...%1> %0337%1
		#endinput
	#elseif UNIQUE_SYMBOL == 337
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (338)
		#define UNIQUE_FUNCTION<%0...%1> %0338%1
		#endinput
	#elseif UNIQUE_SYMBOL == 338
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (339)
		#define UNIQUE_FUNCTION<%0...%1> %0339%1
		#endinput
	#elseif UNIQUE_SYMBOL == 339
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (340)
		#define UNIQUE_FUNCTION<%0...%1> %0340%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 350
	#if UNIQUE_SYMBOL == 340
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (341)
		#define UNIQUE_FUNCTION<%0...%1> %0341%1
		#endinput
	#elseif UNIQUE_SYMBOL == 341
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (342)
		#define UNIQUE_FUNCTION<%0...%1> %0342%1
		#endinput
	#elseif UNIQUE_SYMBOL == 342
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (343)
		#define UNIQUE_FUNCTION<%0...%1> %0343%1
		#endinput
	#elseif UNIQUE_SYMBOL == 343
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (344)
		#define UNIQUE_FUNCTION<%0...%1> %0344%1
		#endinput
	#elseif UNIQUE_SYMBOL == 344
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (345)
		#define UNIQUE_FUNCTION<%0...%1> %0345%1
		#endinput
	#elseif UNIQUE_SYMBOL == 345
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (346)
		#define UNIQUE_FUNCTION<%0...%1> %0346%1
		#endinput
	#elseif UNIQUE_SYMBOL == 346
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (347)
		#define UNIQUE_FUNCTION<%0...%1> %0347%1
		#endinput
	#elseif UNIQUE_SYMBOL == 347
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (348)
		#define UNIQUE_FUNCTION<%0...%1> %0348%1
		#endinput
	#elseif UNIQUE_SYMBOL == 348
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (349)
		#define UNIQUE_FUNCTION<%0...%1> %0349%1
		#endinput
	#elseif UNIQUE_SYMBOL == 349
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (350)
		#define UNIQUE_FUNCTION<%0...%1> %0350%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 360
	#if UNIQUE_SYMBOL == 350
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (351)
		#define UNIQUE_FUNCTION<%0...%1> %0351%1
		#endinput
	#elseif UNIQUE_SYMBOL == 351
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (352)
		#define UNIQUE_FUNCTION<%0...%1> %0352%1
		#endinput
	#elseif UNIQUE_SYMBOL == 352
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (353)
		#define UNIQUE_FUNCTION<%0...%1> %0353%1
		#endinput
	#elseif UNIQUE_SYMBOL == 353
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (354)
		#define UNIQUE_FUNCTION<%0...%1> %0354%1
		#endinput
	#elseif UNIQUE_SYMBOL == 354
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (355)
		#define UNIQUE_FUNCTION<%0...%1> %0355%1
		#endinput
	#elseif UNIQUE_SYMBOL == 355
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (356)
		#define UNIQUE_FUNCTION<%0...%1> %0356%1
		#endinput
	#elseif UNIQUE_SYMBOL == 356
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (357)
		#define UNIQUE_FUNCTION<%0...%1> %0357%1
		#endinput
	#elseif UNIQUE_SYMBOL == 357
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (358)
		#define UNIQUE_FUNCTION<%0...%1> %0358%1
		#endinput
	#elseif UNIQUE_SYMBOL == 358
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (359)
		#define UNIQUE_FUNCTION<%0...%1> %0359%1
		#endinput
	#elseif UNIQUE_SYMBOL == 359
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (360)
		#define UNIQUE_FUNCTION<%0...%1> %0360%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 370
	#if UNIQUE_SYMBOL == 360
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (361)
		#define UNIQUE_FUNCTION<%0...%1> %0361%1
		#endinput
	#elseif UNIQUE_SYMBOL == 361
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (362)
		#define UNIQUE_FUNCTION<%0...%1> %0362%1
		#endinput
	#elseif UNIQUE_SYMBOL == 362
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (363)
		#define UNIQUE_FUNCTION<%0...%1> %0363%1
		#endinput
	#elseif UNIQUE_SYMBOL == 363
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (364)
		#define UNIQUE_FUNCTION<%0...%1> %0364%1
		#endinput
	#elseif UNIQUE_SYMBOL == 364
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (365)
		#define UNIQUE_FUNCTION<%0...%1> %0365%1
		#endinput
	#elseif UNIQUE_SYMBOL == 365
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (366)
		#define UNIQUE_FUNCTION<%0...%1> %0366%1
		#endinput
	#elseif UNIQUE_SYMBOL == 366
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (367)
		#define UNIQUE_FUNCTION<%0...%1> %0367%1
		#endinput
	#elseif UNIQUE_SYMBOL == 367
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (368)
		#define UNIQUE_FUNCTION<%0...%1> %0368%1
		#endinput
	#elseif UNIQUE_SYMBOL == 368
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (369)
		#define UNIQUE_FUNCTION<%0...%1> %0369%1
		#endinput
	#elseif UNIQUE_SYMBOL == 369
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (370)
		#define UNIQUE_FUNCTION<%0...%1> %0370%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 380
	#if UNIQUE_SYMBOL == 370
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (371)
		#define UNIQUE_FUNCTION<%0...%1> %0371%1
		#endinput
	#elseif UNIQUE_SYMBOL == 371
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (372)
		#define UNIQUE_FUNCTION<%0...%1> %0372%1
		#endinput
	#elseif UNIQUE_SYMBOL == 372
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (373)
		#define UNIQUE_FUNCTION<%0...%1> %0373%1
		#endinput
	#elseif UNIQUE_SYMBOL == 373
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (374)
		#define UNIQUE_FUNCTION<%0...%1> %0374%1
		#endinput
	#elseif UNIQUE_SYMBOL == 374
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (375)
		#define UNIQUE_FUNCTION<%0...%1> %0375%1
		#endinput
	#elseif UNIQUE_SYMBOL == 375
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (376)
		#define UNIQUE_FUNCTION<%0...%1> %0376%1
		#endinput
	#elseif UNIQUE_SYMBOL == 376
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (377)
		#define UNIQUE_FUNCTION<%0...%1> %0377%1
		#endinput
	#elseif UNIQUE_SYMBOL == 377
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (378)
		#define UNIQUE_FUNCTION<%0...%1> %0378%1
		#endinput
	#elseif UNIQUE_SYMBOL == 378
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (379)
		#define UNIQUE_FUNCTION<%0...%1> %0379%1
		#endinput
	#elseif UNIQUE_SYMBOL == 379
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (380)
		#define UNIQUE_FUNCTION<%0...%1> %0380%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 390
	#if UNIQUE_SYMBOL == 380
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (381)
		#define UNIQUE_FUNCTION<%0...%1> %0381%1
		#endinput
	#elseif UNIQUE_SYMBOL == 381
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (382)
		#define UNIQUE_FUNCTION<%0...%1> %0382%1
		#endinput
	#elseif UNIQUE_SYMBOL == 382
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (383)
		#define UNIQUE_FUNCTION<%0...%1> %0383%1
		#endinput
	#elseif UNIQUE_SYMBOL == 383
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (384)
		#define UNIQUE_FUNCTION<%0...%1> %0384%1
		#endinput
	#elseif UNIQUE_SYMBOL == 384
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (385)
		#define UNIQUE_FUNCTION<%0...%1> %0385%1
		#endinput
	#elseif UNIQUE_SYMBOL == 385
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (386)
		#define UNIQUE_FUNCTION<%0...%1> %0386%1
		#endinput
	#elseif UNIQUE_SYMBOL == 386
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (387)
		#define UNIQUE_FUNCTION<%0...%1> %0387%1
		#endinput
	#elseif UNIQUE_SYMBOL == 387
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (388)
		#define UNIQUE_FUNCTION<%0...%1> %0388%1
		#endinput
	#elseif UNIQUE_SYMBOL == 388
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (389)
		#define UNIQUE_FUNCTION<%0...%1> %0389%1
		#endinput
	#elseif UNIQUE_SYMBOL == 389
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (390)
		#define UNIQUE_FUNCTION<%0...%1> %0390%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 400
	#if UNIQUE_SYMBOL == 390
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (391)
		#define UNIQUE_FUNCTION<%0...%1> %0391%1
		#endinput
	#elseif UNIQUE_SYMBOL == 391
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (392)
		#define UNIQUE_FUNCTION<%0...%1> %0392%1
		#endinput
	#elseif UNIQUE_SYMBOL == 392
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (393)
		#define UNIQUE_FUNCTION<%0...%1> %0393%1
		#endinput
	#elseif UNIQUE_SYMBOL == 393
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (394)
		#define UNIQUE_FUNCTION<%0...%1> %0394%1
		#endinput
	#elseif UNIQUE_SYMBOL == 394
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (395)
		#define UNIQUE_FUNCTION<%0...%1> %0395%1
		#endinput
	#elseif UNIQUE_SYMBOL == 395
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (396)
		#define UNIQUE_FUNCTION<%0...%1> %0396%1
		#endinput
	#elseif UNIQUE_SYMBOL == 396
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (397)
		#define UNIQUE_FUNCTION<%0...%1> %0397%1
		#endinput
	#elseif UNIQUE_SYMBOL == 397
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (398)
		#define UNIQUE_FUNCTION<%0...%1> %0398%1
		#endinput
	#elseif UNIQUE_SYMBOL == 398
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (399)
		#define UNIQUE_FUNCTION<%0...%1> %0399%1
		#endinput
	#elseif UNIQUE_SYMBOL == 399
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (400)
		#define UNIQUE_FUNCTION<%0...%1> %0400%1
		#endinput
	#endif
#endif

