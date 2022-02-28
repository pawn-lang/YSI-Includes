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

static stock const Y_UNIQUE_200_to_299_CALLED = cellmin;

#if defined _inc_y_unique__200_to_299
	#undef _inc_y_unique__200_to_299
#endif

#if UNIQUE_SYMBOL < 210
	#if UNIQUE_SYMBOL == 200
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (201)
		#define UNIQUE_FUNCTION<%0...%1> %0201%1
		#endinput
	#elseif UNIQUE_SYMBOL == 201
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (202)
		#define UNIQUE_FUNCTION<%0...%1> %0202%1
		#endinput
	#elseif UNIQUE_SYMBOL == 202
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (203)
		#define UNIQUE_FUNCTION<%0...%1> %0203%1
		#endinput
	#elseif UNIQUE_SYMBOL == 203
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (204)
		#define UNIQUE_FUNCTION<%0...%1> %0204%1
		#endinput
	#elseif UNIQUE_SYMBOL == 204
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (205)
		#define UNIQUE_FUNCTION<%0...%1> %0205%1
		#endinput
	#elseif UNIQUE_SYMBOL == 205
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (206)
		#define UNIQUE_FUNCTION<%0...%1> %0206%1
		#endinput
	#elseif UNIQUE_SYMBOL == 206
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (207)
		#define UNIQUE_FUNCTION<%0...%1> %0207%1
		#endinput
	#elseif UNIQUE_SYMBOL == 207
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (208)
		#define UNIQUE_FUNCTION<%0...%1> %0208%1
		#endinput
	#elseif UNIQUE_SYMBOL == 208
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (209)
		#define UNIQUE_FUNCTION<%0...%1> %0209%1
		#endinput
	#elseif UNIQUE_SYMBOL == 209
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (210)
		#define UNIQUE_FUNCTION<%0...%1> %0210%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 220
	#if UNIQUE_SYMBOL == 210
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (211)
		#define UNIQUE_FUNCTION<%0...%1> %0211%1
		#endinput
	#elseif UNIQUE_SYMBOL == 211
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (212)
		#define UNIQUE_FUNCTION<%0...%1> %0212%1
		#endinput
	#elseif UNIQUE_SYMBOL == 212
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (213)
		#define UNIQUE_FUNCTION<%0...%1> %0213%1
		#endinput
	#elseif UNIQUE_SYMBOL == 213
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (214)
		#define UNIQUE_FUNCTION<%0...%1> %0214%1
		#endinput
	#elseif UNIQUE_SYMBOL == 214
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (215)
		#define UNIQUE_FUNCTION<%0...%1> %0215%1
		#endinput
	#elseif UNIQUE_SYMBOL == 215
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (216)
		#define UNIQUE_FUNCTION<%0...%1> %0216%1
		#endinput
	#elseif UNIQUE_SYMBOL == 216
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (217)
		#define UNIQUE_FUNCTION<%0...%1> %0217%1
		#endinput
	#elseif UNIQUE_SYMBOL == 217
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (218)
		#define UNIQUE_FUNCTION<%0...%1> %0218%1
		#endinput
	#elseif UNIQUE_SYMBOL == 218
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (219)
		#define UNIQUE_FUNCTION<%0...%1> %0219%1
		#endinput
	#elseif UNIQUE_SYMBOL == 219
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (220)
		#define UNIQUE_FUNCTION<%0...%1> %0220%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 230
	#if UNIQUE_SYMBOL == 220
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (221)
		#define UNIQUE_FUNCTION<%0...%1> %0221%1
		#endinput
	#elseif UNIQUE_SYMBOL == 221
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (222)
		#define UNIQUE_FUNCTION<%0...%1> %0222%1
		#endinput
	#elseif UNIQUE_SYMBOL == 222
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (223)
		#define UNIQUE_FUNCTION<%0...%1> %0223%1
		#endinput
	#elseif UNIQUE_SYMBOL == 223
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (224)
		#define UNIQUE_FUNCTION<%0...%1> %0224%1
		#endinput
	#elseif UNIQUE_SYMBOL == 224
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (225)
		#define UNIQUE_FUNCTION<%0...%1> %0225%1
		#endinput
	#elseif UNIQUE_SYMBOL == 225
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (226)
		#define UNIQUE_FUNCTION<%0...%1> %0226%1
		#endinput
	#elseif UNIQUE_SYMBOL == 226
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (227)
		#define UNIQUE_FUNCTION<%0...%1> %0227%1
		#endinput
	#elseif UNIQUE_SYMBOL == 227
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (228)
		#define UNIQUE_FUNCTION<%0...%1> %0228%1
		#endinput
	#elseif UNIQUE_SYMBOL == 228
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (229)
		#define UNIQUE_FUNCTION<%0...%1> %0229%1
		#endinput
	#elseif UNIQUE_SYMBOL == 229
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (230)
		#define UNIQUE_FUNCTION<%0...%1> %0230%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 240
	#if UNIQUE_SYMBOL == 230
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (231)
		#define UNIQUE_FUNCTION<%0...%1> %0231%1
		#endinput
	#elseif UNIQUE_SYMBOL == 231
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (232)
		#define UNIQUE_FUNCTION<%0...%1> %0232%1
		#endinput
	#elseif UNIQUE_SYMBOL == 232
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (233)
		#define UNIQUE_FUNCTION<%0...%1> %0233%1
		#endinput
	#elseif UNIQUE_SYMBOL == 233
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (234)
		#define UNIQUE_FUNCTION<%0...%1> %0234%1
		#endinput
	#elseif UNIQUE_SYMBOL == 234
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (235)
		#define UNIQUE_FUNCTION<%0...%1> %0235%1
		#endinput
	#elseif UNIQUE_SYMBOL == 235
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (236)
		#define UNIQUE_FUNCTION<%0...%1> %0236%1
		#endinput
	#elseif UNIQUE_SYMBOL == 236
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (237)
		#define UNIQUE_FUNCTION<%0...%1> %0237%1
		#endinput
	#elseif UNIQUE_SYMBOL == 237
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (238)
		#define UNIQUE_FUNCTION<%0...%1> %0238%1
		#endinput
	#elseif UNIQUE_SYMBOL == 238
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (239)
		#define UNIQUE_FUNCTION<%0...%1> %0239%1
		#endinput
	#elseif UNIQUE_SYMBOL == 239
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (240)
		#define UNIQUE_FUNCTION<%0...%1> %0240%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 250
	#if UNIQUE_SYMBOL == 240
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (241)
		#define UNIQUE_FUNCTION<%0...%1> %0241%1
		#endinput
	#elseif UNIQUE_SYMBOL == 241
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (242)
		#define UNIQUE_FUNCTION<%0...%1> %0242%1
		#endinput
	#elseif UNIQUE_SYMBOL == 242
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (243)
		#define UNIQUE_FUNCTION<%0...%1> %0243%1
		#endinput
	#elseif UNIQUE_SYMBOL == 243
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (244)
		#define UNIQUE_FUNCTION<%0...%1> %0244%1
		#endinput
	#elseif UNIQUE_SYMBOL == 244
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (245)
		#define UNIQUE_FUNCTION<%0...%1> %0245%1
		#endinput
	#elseif UNIQUE_SYMBOL == 245
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (246)
		#define UNIQUE_FUNCTION<%0...%1> %0246%1
		#endinput
	#elseif UNIQUE_SYMBOL == 246
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (247)
		#define UNIQUE_FUNCTION<%0...%1> %0247%1
		#endinput
	#elseif UNIQUE_SYMBOL == 247
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (248)
		#define UNIQUE_FUNCTION<%0...%1> %0248%1
		#endinput
	#elseif UNIQUE_SYMBOL == 248
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (249)
		#define UNIQUE_FUNCTION<%0...%1> %0249%1
		#endinput
	#elseif UNIQUE_SYMBOL == 249
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (250)
		#define UNIQUE_FUNCTION<%0...%1> %0250%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 260
	#if UNIQUE_SYMBOL == 250
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (251)
		#define UNIQUE_FUNCTION<%0...%1> %0251%1
		#endinput
	#elseif UNIQUE_SYMBOL == 251
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (252)
		#define UNIQUE_FUNCTION<%0...%1> %0252%1
		#endinput
	#elseif UNIQUE_SYMBOL == 252
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (253)
		#define UNIQUE_FUNCTION<%0...%1> %0253%1
		#endinput
	#elseif UNIQUE_SYMBOL == 253
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (254)
		#define UNIQUE_FUNCTION<%0...%1> %0254%1
		#endinput
	#elseif UNIQUE_SYMBOL == 254
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (255)
		#define UNIQUE_FUNCTION<%0...%1> %0255%1
		#endinput
	#elseif UNIQUE_SYMBOL == 255
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (256)
		#define UNIQUE_FUNCTION<%0...%1> %0256%1
		#endinput
	#elseif UNIQUE_SYMBOL == 256
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (257)
		#define UNIQUE_FUNCTION<%0...%1> %0257%1
		#endinput
	#elseif UNIQUE_SYMBOL == 257
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (258)
		#define UNIQUE_FUNCTION<%0...%1> %0258%1
		#endinput
	#elseif UNIQUE_SYMBOL == 258
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (259)
		#define UNIQUE_FUNCTION<%0...%1> %0259%1
		#endinput
	#elseif UNIQUE_SYMBOL == 259
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (260)
		#define UNIQUE_FUNCTION<%0...%1> %0260%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 270
	#if UNIQUE_SYMBOL == 260
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (261)
		#define UNIQUE_FUNCTION<%0...%1> %0261%1
		#endinput
	#elseif UNIQUE_SYMBOL == 261
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (262)
		#define UNIQUE_FUNCTION<%0...%1> %0262%1
		#endinput
	#elseif UNIQUE_SYMBOL == 262
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (263)
		#define UNIQUE_FUNCTION<%0...%1> %0263%1
		#endinput
	#elseif UNIQUE_SYMBOL == 263
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (264)
		#define UNIQUE_FUNCTION<%0...%1> %0264%1
		#endinput
	#elseif UNIQUE_SYMBOL == 264
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (265)
		#define UNIQUE_FUNCTION<%0...%1> %0265%1
		#endinput
	#elseif UNIQUE_SYMBOL == 265
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (266)
		#define UNIQUE_FUNCTION<%0...%1> %0266%1
		#endinput
	#elseif UNIQUE_SYMBOL == 266
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (267)
		#define UNIQUE_FUNCTION<%0...%1> %0267%1
		#endinput
	#elseif UNIQUE_SYMBOL == 267
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (268)
		#define UNIQUE_FUNCTION<%0...%1> %0268%1
		#endinput
	#elseif UNIQUE_SYMBOL == 268
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (269)
		#define UNIQUE_FUNCTION<%0...%1> %0269%1
		#endinput
	#elseif UNIQUE_SYMBOL == 269
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (270)
		#define UNIQUE_FUNCTION<%0...%1> %0270%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 280
	#if UNIQUE_SYMBOL == 270
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (271)
		#define UNIQUE_FUNCTION<%0...%1> %0271%1
		#endinput
	#elseif UNIQUE_SYMBOL == 271
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (272)
		#define UNIQUE_FUNCTION<%0...%1> %0272%1
		#endinput
	#elseif UNIQUE_SYMBOL == 272
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (273)
		#define UNIQUE_FUNCTION<%0...%1> %0273%1
		#endinput
	#elseif UNIQUE_SYMBOL == 273
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (274)
		#define UNIQUE_FUNCTION<%0...%1> %0274%1
		#endinput
	#elseif UNIQUE_SYMBOL == 274
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (275)
		#define UNIQUE_FUNCTION<%0...%1> %0275%1
		#endinput
	#elseif UNIQUE_SYMBOL == 275
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (276)
		#define UNIQUE_FUNCTION<%0...%1> %0276%1
		#endinput
	#elseif UNIQUE_SYMBOL == 276
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (277)
		#define UNIQUE_FUNCTION<%0...%1> %0277%1
		#endinput
	#elseif UNIQUE_SYMBOL == 277
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (278)
		#define UNIQUE_FUNCTION<%0...%1> %0278%1
		#endinput
	#elseif UNIQUE_SYMBOL == 278
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (279)
		#define UNIQUE_FUNCTION<%0...%1> %0279%1
		#endinput
	#elseif UNIQUE_SYMBOL == 279
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (280)
		#define UNIQUE_FUNCTION<%0...%1> %0280%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 290
	#if UNIQUE_SYMBOL == 280
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (281)
		#define UNIQUE_FUNCTION<%0...%1> %0281%1
		#endinput
	#elseif UNIQUE_SYMBOL == 281
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (282)
		#define UNIQUE_FUNCTION<%0...%1> %0282%1
		#endinput
	#elseif UNIQUE_SYMBOL == 282
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (283)
		#define UNIQUE_FUNCTION<%0...%1> %0283%1
		#endinput
	#elseif UNIQUE_SYMBOL == 283
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (284)
		#define UNIQUE_FUNCTION<%0...%1> %0284%1
		#endinput
	#elseif UNIQUE_SYMBOL == 284
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (285)
		#define UNIQUE_FUNCTION<%0...%1> %0285%1
		#endinput
	#elseif UNIQUE_SYMBOL == 285
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (286)
		#define UNIQUE_FUNCTION<%0...%1> %0286%1
		#endinput
	#elseif UNIQUE_SYMBOL == 286
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (287)
		#define UNIQUE_FUNCTION<%0...%1> %0287%1
		#endinput
	#elseif UNIQUE_SYMBOL == 287
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (288)
		#define UNIQUE_FUNCTION<%0...%1> %0288%1
		#endinput
	#elseif UNIQUE_SYMBOL == 288
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (289)
		#define UNIQUE_FUNCTION<%0...%1> %0289%1
		#endinput
	#elseif UNIQUE_SYMBOL == 289
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (290)
		#define UNIQUE_FUNCTION<%0...%1> %0290%1
		#endinput
	#endif
#elseif UNIQUE_SYMBOL < 300
	#if UNIQUE_SYMBOL == 290
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (291)
		#define UNIQUE_FUNCTION<%0...%1> %0291%1
		#endinput
	#elseif UNIQUE_SYMBOL == 291
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (292)
		#define UNIQUE_FUNCTION<%0...%1> %0292%1
		#endinput
	#elseif UNIQUE_SYMBOL == 292
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (293)
		#define UNIQUE_FUNCTION<%0...%1> %0293%1
		#endinput
	#elseif UNIQUE_SYMBOL == 293
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (294)
		#define UNIQUE_FUNCTION<%0...%1> %0294%1
		#endinput
	#elseif UNIQUE_SYMBOL == 294
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (295)
		#define UNIQUE_FUNCTION<%0...%1> %0295%1
		#endinput
	#elseif UNIQUE_SYMBOL == 295
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (296)
		#define UNIQUE_FUNCTION<%0...%1> %0296%1
		#endinput
	#elseif UNIQUE_SYMBOL == 296
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (297)
		#define UNIQUE_FUNCTION<%0...%1> %0297%1
		#endinput
	#elseif UNIQUE_SYMBOL == 297
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (298)
		#define UNIQUE_FUNCTION<%0...%1> %0298%1
		#endinput
	#elseif UNIQUE_SYMBOL == 298
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (299)
		#define UNIQUE_FUNCTION<%0...%1> %0299%1
		#endinput
	#elseif UNIQUE_SYMBOL == 299
		#undef UNIQUE_SYMBOL
		#define UNIQUE_SYMBOL (300)
		#define UNIQUE_FUNCTION<%0...%1> %0300%1
		#endinput
	#endif
#endif

