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

static stock bool:VIM_LocalEmpty(const str[])
{
	return str[0] == '\0';
}

@test(.group = "y_vehicledata") VIM_SomeSettings()
{
	ASSERT(Model_IsCar(401));
	ASSERT(Model_IsCar(457));
	ASSERT(!Model_IsCar(476));
	ASSERT(!Model_IsCar(999));
}

@test(.group = "y_vehicledata") VIM_Clamps()
{
	ASSERT_EQ(_:Model_ToVIM(-3) , (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(0)  , (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(10) , (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(397), (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(398), (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(399), (399 - 399));
	ASSERT_EQ(_:Model_ToVIM(400), (400 - 399));
	ASSERT_EQ(_:Model_ToVIM(401), (401 - 399));
	ASSERT_EQ(_:Model_ToVIM(402), (402 - 399));
	ASSERT_EQ(_:Model_ToVIM(403), (403 - 399));
	ASSERT_EQ(_:Model_ToVIM(404), (404 - 399));
	ASSERT_EQ(_:Model_ToVIM(405), (405 - 399));
	ASSERT_EQ(_:Model_ToVIM(406), (406 - 399));
	ASSERT_EQ(_:Model_ToVIM(407), (407 - 399));
	ASSERT_EQ(_:Model_ToVIM(408), (408 - 399));
	ASSERT_EQ(_:Model_ToVIM(409), (409 - 399));
	ASSERT_EQ(_:Model_ToVIM(410), (410 - 399));
	ASSERT_EQ(_:Model_ToVIM(411), (411 - 399));
	ASSERT_EQ(_:Model_ToVIM(412), (412 - 399));
	ASSERT_EQ(_:Model_ToVIM(413), (413 - 399));
	ASSERT_EQ(_:Model_ToVIM(414), (414 - 399));
	ASSERT_EQ(_:Model_ToVIM(415), (415 - 399));
	ASSERT_EQ(_:Model_ToVIM(416), (416 - 399));
	ASSERT_EQ(_:Model_ToVIM(417), (417 - 399));
	ASSERT_EQ(_:Model_ToVIM(418), (418 - 399));
	ASSERT_EQ(_:Model_ToVIM(419), (419 - 399));
	ASSERT_EQ(_:Model_ToVIM(420), (420 - 399));
	ASSERT_EQ(_:Model_ToVIM(421), (421 - 399));
	ASSERT_EQ(_:Model_ToVIM(422), (422 - 399));
	ASSERT_EQ(_:Model_ToVIM(423), (423 - 399));
	ASSERT_EQ(_:Model_ToVIM(424), (424 - 399));
	ASSERT_EQ(_:Model_ToVIM(425), (425 - 399));
	ASSERT_EQ(_:Model_ToVIM(426), (426 - 399));
	ASSERT_EQ(_:Model_ToVIM(427), (427 - 399));
	ASSERT_EQ(_:Model_ToVIM(428), (428 - 399));
	ASSERT_EQ(_:Model_ToVIM(429), (429 - 399));
	ASSERT_EQ(_:Model_ToVIM(430), (430 - 399));
	ASSERT_EQ(_:Model_ToVIM(431), (431 - 399));
	ASSERT_EQ(_:Model_ToVIM(432), (432 - 399));
	ASSERT_EQ(_:Model_ToVIM(433), (433 - 399));
	ASSERT_EQ(_:Model_ToVIM(434), (434 - 399));
	ASSERT_EQ(_:Model_ToVIM(435), (435 - 399));
	ASSERT_EQ(_:Model_ToVIM(436), (436 - 399));
	ASSERT_EQ(_:Model_ToVIM(437), (437 - 399));
	ASSERT_EQ(_:Model_ToVIM(438), (438 - 399));
	ASSERT_EQ(_:Model_ToVIM(439), (439 - 399));
	ASSERT_EQ(_:Model_ToVIM(440), (440 - 399));
	ASSERT_EQ(_:Model_ToVIM(441), (441 - 399));
	ASSERT_EQ(_:Model_ToVIM(442), (442 - 399));
	ASSERT_EQ(_:Model_ToVIM(443), (443 - 399));
	ASSERT_EQ(_:Model_ToVIM(444), (444 - 399));
	ASSERT_EQ(_:Model_ToVIM(445), (445 - 399));
	ASSERT_EQ(_:Model_ToVIM(446), (446 - 399));
	ASSERT_EQ(_:Model_ToVIM(447), (447 - 399));
	ASSERT_EQ(_:Model_ToVIM(448), (448 - 399));
	ASSERT_EQ(_:Model_ToVIM(449), (449 - 399));
	ASSERT_EQ(_:Model_ToVIM(450), (450 - 399));
	ASSERT_EQ(_:Model_ToVIM(451), (451 - 399));
	ASSERT_EQ(_:Model_ToVIM(452), (452 - 399));
	ASSERT_EQ(_:Model_ToVIM(453), (453 - 399));
	ASSERT_EQ(_:Model_ToVIM(454), (454 - 399));
	ASSERT_EQ(_:Model_ToVIM(455), (455 - 399));
	ASSERT_EQ(_:Model_ToVIM(456), (456 - 399));
	ASSERT_EQ(_:Model_ToVIM(457), (457 - 399));
	ASSERT_EQ(_:Model_ToVIM(458), (458 - 399));
	ASSERT_EQ(_:Model_ToVIM(459), (459 - 399));
	ASSERT_EQ(_:Model_ToVIM(460), (460 - 399));
	ASSERT_EQ(_:Model_ToVIM(461), (461 - 399));
	ASSERT_EQ(_:Model_ToVIM(462), (462 - 399));
	ASSERT_EQ(_:Model_ToVIM(463), (463 - 399));
	ASSERT_EQ(_:Model_ToVIM(464), (464 - 399));
	ASSERT_EQ(_:Model_ToVIM(465), (465 - 399));
	ASSERT_EQ(_:Model_ToVIM(466), (466 - 399));
	ASSERT_EQ(_:Model_ToVIM(467), (467 - 399));
	ASSERT_EQ(_:Model_ToVIM(468), (468 - 399));
	ASSERT_EQ(_:Model_ToVIM(469), (469 - 399));
	ASSERT_EQ(_:Model_ToVIM(470), (470 - 399));
	ASSERT_EQ(_:Model_ToVIM(471), (471 - 399));
	ASSERT_EQ(_:Model_ToVIM(472), (472 - 399));
	ASSERT_EQ(_:Model_ToVIM(473), (473 - 399));
	ASSERT_EQ(_:Model_ToVIM(474), (474 - 399));
	ASSERT_EQ(_:Model_ToVIM(475), (475 - 399));
	ASSERT_EQ(_:Model_ToVIM(476), (476 - 399));
	ASSERT_EQ(_:Model_ToVIM(477), (477 - 399));
	ASSERT_EQ(_:Model_ToVIM(478), (478 - 399));
	ASSERT_EQ(_:Model_ToVIM(479), (479 - 399));
	ASSERT_EQ(_:Model_ToVIM(480), (480 - 399));
	ASSERT_EQ(_:Model_ToVIM(481), (481 - 399));
	ASSERT_EQ(_:Model_ToVIM(482), (482 - 399));
	ASSERT_EQ(_:Model_ToVIM(483), (483 - 399));
	ASSERT_EQ(_:Model_ToVIM(484), (484 - 399));
	ASSERT_EQ(_:Model_ToVIM(485), (485 - 399));
	ASSERT_EQ(_:Model_ToVIM(486), (486 - 399));
	ASSERT_EQ(_:Model_ToVIM(487), (487 - 399));
	ASSERT_EQ(_:Model_ToVIM(488), (488 - 399));
	ASSERT_EQ(_:Model_ToVIM(489), (489 - 399));
	ASSERT_EQ(_:Model_ToVIM(490), (490 - 399));
	ASSERT_EQ(_:Model_ToVIM(491), (491 - 399));
	ASSERT_EQ(_:Model_ToVIM(492), (492 - 399));
	ASSERT_EQ(_:Model_ToVIM(493), (493 - 399));
	ASSERT_EQ(_:Model_ToVIM(494), (494 - 399));
	ASSERT_EQ(_:Model_ToVIM(495), (495 - 399));
	ASSERT_EQ(_:Model_ToVIM(496), (496 - 399));
	ASSERT_EQ(_:Model_ToVIM(497), (497 - 399));
	ASSERT_EQ(_:Model_ToVIM(498), (498 - 399));
	ASSERT_EQ(_:Model_ToVIM(499), (499 - 399));
	ASSERT_EQ(_:Model_ToVIM(500), (500 - 399));
	ASSERT_EQ(_:Model_ToVIM(501), (501 - 399));
	ASSERT_EQ(_:Model_ToVIM(502), (502 - 399));
	ASSERT_EQ(_:Model_ToVIM(503), (503 - 399));
	ASSERT_EQ(_:Model_ToVIM(504), (504 - 399));
	ASSERT_EQ(_:Model_ToVIM(505), (505 - 399));
	ASSERT_EQ(_:Model_ToVIM(506), (506 - 399));
	ASSERT_EQ(_:Model_ToVIM(507), (507 - 399));
	ASSERT_EQ(_:Model_ToVIM(508), (508 - 399));
	ASSERT_EQ(_:Model_ToVIM(509), (509 - 399));
	ASSERT_EQ(_:Model_ToVIM(510), (510 - 399));
	ASSERT_EQ(_:Model_ToVIM(511), (511 - 399));
	ASSERT_EQ(_:Model_ToVIM(512), (512 - 399));
	ASSERT_EQ(_:Model_ToVIM(513), (513 - 399));
	ASSERT_EQ(_:Model_ToVIM(514), (514 - 399));
	ASSERT_EQ(_:Model_ToVIM(515), (515 - 399));
	ASSERT_EQ(_:Model_ToVIM(516), (516 - 399));
	ASSERT_EQ(_:Model_ToVIM(517), (517 - 399));
	ASSERT_EQ(_:Model_ToVIM(518), (518 - 399));
	ASSERT_EQ(_:Model_ToVIM(519), (519 - 399));
	ASSERT_EQ(_:Model_ToVIM(520), (520 - 399));
	ASSERT_EQ(_:Model_ToVIM(521), (521 - 399));
	ASSERT_EQ(_:Model_ToVIM(522), (522 - 399));
	ASSERT_EQ(_:Model_ToVIM(523), (523 - 399));
	ASSERT_EQ(_:Model_ToVIM(524), (524 - 399));
	ASSERT_EQ(_:Model_ToVIM(525), (525 - 399));
	ASSERT_EQ(_:Model_ToVIM(526), (526 - 399));
	ASSERT_EQ(_:Model_ToVIM(527), (527 - 399));
	ASSERT_EQ(_:Model_ToVIM(528), (528 - 399));
	ASSERT_EQ(_:Model_ToVIM(529), (529 - 399));
	ASSERT_EQ(_:Model_ToVIM(530), (530 - 399));
	ASSERT_EQ(_:Model_ToVIM(531), (531 - 399));
	ASSERT_EQ(_:Model_ToVIM(532), (532 - 399));
	ASSERT_EQ(_:Model_ToVIM(533), (533 - 399));
	ASSERT_EQ(_:Model_ToVIM(534), (534 - 399));
	ASSERT_EQ(_:Model_ToVIM(535), (535 - 399));
	ASSERT_EQ(_:Model_ToVIM(536), (536 - 399));
	ASSERT_EQ(_:Model_ToVIM(537), (537 - 399));
	ASSERT_EQ(_:Model_ToVIM(538), (538 - 399));
	ASSERT_EQ(_:Model_ToVIM(539), (539 - 399));
	ASSERT_EQ(_:Model_ToVIM(540), (540 - 399));
	ASSERT_EQ(_:Model_ToVIM(541), (541 - 399));
	ASSERT_EQ(_:Model_ToVIM(542), (542 - 399));
	ASSERT_EQ(_:Model_ToVIM(543), (543 - 399));
	ASSERT_EQ(_:Model_ToVIM(544), (544 - 399));
	ASSERT_EQ(_:Model_ToVIM(545), (545 - 399));
	ASSERT_EQ(_:Model_ToVIM(546), (546 - 399));
	ASSERT_EQ(_:Model_ToVIM(547), (547 - 399));
	ASSERT_EQ(_:Model_ToVIM(548), (548 - 399));
	ASSERT_EQ(_:Model_ToVIM(549), (549 - 399));
	ASSERT_EQ(_:Model_ToVIM(550), (550 - 399));
	ASSERT_EQ(_:Model_ToVIM(551), (551 - 399));
	ASSERT_EQ(_:Model_ToVIM(552), (552 - 399));
	ASSERT_EQ(_:Model_ToVIM(553), (553 - 399));
	ASSERT_EQ(_:Model_ToVIM(554), (554 - 399));
	ASSERT_EQ(_:Model_ToVIM(555), (555 - 399));
	ASSERT_EQ(_:Model_ToVIM(556), (556 - 399));
	ASSERT_EQ(_:Model_ToVIM(557), (557 - 399));
	ASSERT_EQ(_:Model_ToVIM(558), (558 - 399));
	ASSERT_EQ(_:Model_ToVIM(559), (559 - 399));
	ASSERT_EQ(_:Model_ToVIM(560), (560 - 399));
	ASSERT_EQ(_:Model_ToVIM(561), (561 - 399));
	ASSERT_EQ(_:Model_ToVIM(562), (562 - 399));
	ASSERT_EQ(_:Model_ToVIM(563), (563 - 399));
	ASSERT_EQ(_:Model_ToVIM(564), (564 - 399));
	ASSERT_EQ(_:Model_ToVIM(565), (565 - 399));
	ASSERT_EQ(_:Model_ToVIM(566), (566 - 399));
	ASSERT_EQ(_:Model_ToVIM(567), (567 - 399));
	ASSERT_EQ(_:Model_ToVIM(568), (568 - 399));
	ASSERT_EQ(_:Model_ToVIM(569), (569 - 399));
	ASSERT_EQ(_:Model_ToVIM(570), (570 - 399));
	ASSERT_EQ(_:Model_ToVIM(571), (571 - 399));
	ASSERT_EQ(_:Model_ToVIM(572), (572 - 399));
	ASSERT_EQ(_:Model_ToVIM(573), (573 - 399));
	ASSERT_EQ(_:Model_ToVIM(574), (574 - 399));
	ASSERT_EQ(_:Model_ToVIM(575), (575 - 399));
	ASSERT_EQ(_:Model_ToVIM(576), (576 - 399));
	ASSERT_EQ(_:Model_ToVIM(577), (577 - 399));
	ASSERT_EQ(_:Model_ToVIM(578), (578 - 399));
	ASSERT_EQ(_:Model_ToVIM(579), (579 - 399));
	ASSERT_EQ(_:Model_ToVIM(580), (580 - 399));
	ASSERT_EQ(_:Model_ToVIM(581), (581 - 399));
	ASSERT_EQ(_:Model_ToVIM(582), (582 - 399));
	ASSERT_EQ(_:Model_ToVIM(583), (583 - 399));
	ASSERT_EQ(_:Model_ToVIM(584), (584 - 399));
	ASSERT_EQ(_:Model_ToVIM(585), (585 - 399));
	ASSERT_EQ(_:Model_ToVIM(586), (586 - 399));
	ASSERT_EQ(_:Model_ToVIM(587), (587 - 399));
	ASSERT_EQ(_:Model_ToVIM(588), (588 - 399));
	ASSERT_EQ(_:Model_ToVIM(589), (589 - 399));
	ASSERT_EQ(_:Model_ToVIM(590), (590 - 399));
	ASSERT_EQ(_:Model_ToVIM(591), (591 - 399));
	ASSERT_EQ(_:Model_ToVIM(592), (592 - 399));
	ASSERT_EQ(_:Model_ToVIM(593), (593 - 399));
	ASSERT_EQ(_:Model_ToVIM(594), (594 - 399));
	ASSERT_EQ(_:Model_ToVIM(595), (595 - 399));
	ASSERT_EQ(_:Model_ToVIM(596), (596 - 399));
	ASSERT_EQ(_:Model_ToVIM(597), (597 - 399));
	ASSERT_EQ(_:Model_ToVIM(598), (598 - 399));
	ASSERT_EQ(_:Model_ToVIM(599), (599 - 399));
	ASSERT_EQ(_:Model_ToVIM(600), (600 - 399));
	ASSERT_EQ(_:Model_ToVIM(601), (601 - 399));
	ASSERT_EQ(_:Model_ToVIM(602), (602 - 399));
	ASSERT_EQ(_:Model_ToVIM(603), (603 - 399));
	ASSERT_EQ(_:Model_ToVIM(604), (604 - 399));
	ASSERT_EQ(_:Model_ToVIM(605), (605 - 399));
	ASSERT_EQ(_:Model_ToVIM(606), (606 - 399));
	ASSERT_EQ(_:Model_ToVIM(607), (607 - 399));
	ASSERT_EQ(_:Model_ToVIM(608), (608 - 399));
	ASSERT_EQ(_:Model_ToVIM(609), (609 - 399));
	ASSERT_EQ(_:Model_ToVIM(610), (610 - 399));
	ASSERT_EQ(_:Model_ToVIM(611), (611 - 399));
	ASSERT_EQ(_:Model_ToVIM(612), (612 - 399));
	ASSERT_EQ(_:Model_ToVIM(613), (612 - 399));
	ASSERT_EQ(_:Model_ToVIM(614), (612 - 399));
	ASSERT_EQ(_:Model_ToVIM(1000), (612 - 399));
	ASSERT_EQ(_:Model_ToVIM(654684), (612 - 399));
}

@test(.group = "y_vehicledata") VIM_IsValid()
{
	ASSERT(!Model_IsValid(-12));
	ASSERT(!Model_IsValid(0));
	ASSERT(!Model_IsValid(100));
	ASSERT(!Model_IsValid(397));
	ASSERT(!Model_IsValid(398));
	ASSERT(!Model_IsValid(399));
	ASSERT(Model_IsValid(400));
	ASSERT(Model_IsValid(401));
	ASSERT(Model_IsValid(402));
	ASSERT(Model_IsValid(403));
	ASSERT(Model_IsValid(404));
	ASSERT(Model_IsValid(405));
	ASSERT(Model_IsValid(406));
	ASSERT(Model_IsValid(407));
	ASSERT(Model_IsValid(408));
	ASSERT(Model_IsValid(409));
	ASSERT(Model_IsValid(410));
	ASSERT(Model_IsValid(411));
	ASSERT(Model_IsValid(412));
	ASSERT(Model_IsValid(413));
	ASSERT(Model_IsValid(414));
	ASSERT(Model_IsValid(415));
	ASSERT(Model_IsValid(416));
	ASSERT(Model_IsValid(417));
	ASSERT(Model_IsValid(418));
	ASSERT(Model_IsValid(419));
	ASSERT(Model_IsValid(420));
	ASSERT(Model_IsValid(421));
	ASSERT(Model_IsValid(422));
	ASSERT(Model_IsValid(423));
	ASSERT(Model_IsValid(424));
	ASSERT(Model_IsValid(425));
	ASSERT(Model_IsValid(426));
	ASSERT(Model_IsValid(427));
	ASSERT(Model_IsValid(428));
	ASSERT(Model_IsValid(429));
	ASSERT(Model_IsValid(430));
	ASSERT(Model_IsValid(431));
	ASSERT(Model_IsValid(432));
	ASSERT(Model_IsValid(433));
	ASSERT(Model_IsValid(434));
	ASSERT(Model_IsValid(435));
	ASSERT(Model_IsValid(436));
	ASSERT(Model_IsValid(437));
	ASSERT(Model_IsValid(438));
	ASSERT(Model_IsValid(439));
	ASSERT(Model_IsValid(440));
	ASSERT(Model_IsValid(441));
	ASSERT(Model_IsValid(442));
	ASSERT(Model_IsValid(443));
	ASSERT(Model_IsValid(444));
	ASSERT(Model_IsValid(445));
	ASSERT(Model_IsValid(446));
	ASSERT(Model_IsValid(447));
	ASSERT(Model_IsValid(448));
	ASSERT(Model_IsValid(449));
	ASSERT(Model_IsValid(450));
	ASSERT(Model_IsValid(451));
	ASSERT(Model_IsValid(452));
	ASSERT(Model_IsValid(453));
	ASSERT(Model_IsValid(454));
	ASSERT(Model_IsValid(455));
	ASSERT(Model_IsValid(456));
	ASSERT(Model_IsValid(457));
	ASSERT(Model_IsValid(458));
	ASSERT(Model_IsValid(459));
	ASSERT(Model_IsValid(460));
	ASSERT(Model_IsValid(461));
	ASSERT(Model_IsValid(462));
	ASSERT(Model_IsValid(463));
	ASSERT(Model_IsValid(464));
	ASSERT(Model_IsValid(465));
	ASSERT(Model_IsValid(466));
	ASSERT(Model_IsValid(467));
	ASSERT(Model_IsValid(468));
	ASSERT(Model_IsValid(469));
	ASSERT(Model_IsValid(470));
	ASSERT(Model_IsValid(471));
	ASSERT(Model_IsValid(472));
	ASSERT(Model_IsValid(473));
	ASSERT(Model_IsValid(474));
	ASSERT(Model_IsValid(475));
	ASSERT(Model_IsValid(476));
	ASSERT(Model_IsValid(477));
	ASSERT(Model_IsValid(478));
	ASSERT(Model_IsValid(479));
	ASSERT(Model_IsValid(480));
	ASSERT(Model_IsValid(481));
	ASSERT(Model_IsValid(482));
	ASSERT(Model_IsValid(483));
	ASSERT(Model_IsValid(484));
	ASSERT(Model_IsValid(485));
	ASSERT(Model_IsValid(486));
	ASSERT(Model_IsValid(487));
	ASSERT(Model_IsValid(488));
	ASSERT(Model_IsValid(489));
	ASSERT(Model_IsValid(490));
	ASSERT(Model_IsValid(491));
	ASSERT(Model_IsValid(492));
	ASSERT(Model_IsValid(493));
	ASSERT(Model_IsValid(494));
	ASSERT(Model_IsValid(495));
	ASSERT(Model_IsValid(496));
	ASSERT(Model_IsValid(497));
	ASSERT(Model_IsValid(498));
	ASSERT(Model_IsValid(499));
	ASSERT(Model_IsValid(500));
	ASSERT(Model_IsValid(501));
	ASSERT(Model_IsValid(502));
	ASSERT(Model_IsValid(503));
	ASSERT(Model_IsValid(504));
	ASSERT(Model_IsValid(505));
	ASSERT(Model_IsValid(506));
	ASSERT(Model_IsValid(507));
	ASSERT(Model_IsValid(508));
	ASSERT(Model_IsValid(509));
	ASSERT(Model_IsValid(510));
	ASSERT(Model_IsValid(511));
	ASSERT(Model_IsValid(512));
	ASSERT(Model_IsValid(513));
	ASSERT(Model_IsValid(514));
	ASSERT(Model_IsValid(515));
	ASSERT(Model_IsValid(516));
	ASSERT(Model_IsValid(517));
	ASSERT(Model_IsValid(518));
	ASSERT(Model_IsValid(519));
	ASSERT(Model_IsValid(520));
	ASSERT(Model_IsValid(521));
	ASSERT(Model_IsValid(522));
	ASSERT(Model_IsValid(523));
	ASSERT(Model_IsValid(524));
	ASSERT(Model_IsValid(525));
	ASSERT(Model_IsValid(526));
	ASSERT(Model_IsValid(527));
	ASSERT(Model_IsValid(528));
	ASSERT(Model_IsValid(529));
	ASSERT(Model_IsValid(530));
	ASSERT(Model_IsValid(531));
	ASSERT(Model_IsValid(532));
	ASSERT(Model_IsValid(533));
	ASSERT(Model_IsValid(534));
	ASSERT(Model_IsValid(535));
	ASSERT(Model_IsValid(536));
	ASSERT(Model_IsValid(537));
	ASSERT(Model_IsValid(538));
	ASSERT(Model_IsValid(539));
	ASSERT(Model_IsValid(540));
	ASSERT(Model_IsValid(541));
	ASSERT(Model_IsValid(542));
	ASSERT(Model_IsValid(543));
	ASSERT(Model_IsValid(544));
	ASSERT(Model_IsValid(545));
	ASSERT(Model_IsValid(546));
	ASSERT(Model_IsValid(547));
	ASSERT(Model_IsValid(548));
	ASSERT(Model_IsValid(549));
	ASSERT(Model_IsValid(550));
	ASSERT(Model_IsValid(551));
	ASSERT(Model_IsValid(552));
	ASSERT(Model_IsValid(553));
	ASSERT(Model_IsValid(554));
	ASSERT(Model_IsValid(555));
	ASSERT(Model_IsValid(556));
	ASSERT(Model_IsValid(557));
	ASSERT(Model_IsValid(558));
	ASSERT(Model_IsValid(559));
	ASSERT(Model_IsValid(560));
	ASSERT(Model_IsValid(561));
	ASSERT(Model_IsValid(562));
	ASSERT(Model_IsValid(563));
	ASSERT(Model_IsValid(564));
	ASSERT(Model_IsValid(565));
	ASSERT(Model_IsValid(566));
	ASSERT(Model_IsValid(567));
	ASSERT(Model_IsValid(568));
	ASSERT(Model_IsValid(569));
	ASSERT(Model_IsValid(570));
	ASSERT(Model_IsValid(571));
	ASSERT(Model_IsValid(572));
	ASSERT(Model_IsValid(573));
	ASSERT(Model_IsValid(574));
	ASSERT(Model_IsValid(575));
	ASSERT(Model_IsValid(576));
	ASSERT(Model_IsValid(577));
	ASSERT(Model_IsValid(578));
	ASSERT(Model_IsValid(579));
	ASSERT(Model_IsValid(580));
	ASSERT(Model_IsValid(581));
	ASSERT(Model_IsValid(582));
	ASSERT(Model_IsValid(583));
	ASSERT(Model_IsValid(584));
	ASSERT(Model_IsValid(585));
	ASSERT(Model_IsValid(586));
	ASSERT(Model_IsValid(587));
	ASSERT(Model_IsValid(588));
	ASSERT(Model_IsValid(589));
	ASSERT(Model_IsValid(590));
	ASSERT(Model_IsValid(591));
	ASSERT(Model_IsValid(592));
	ASSERT(Model_IsValid(593));
	ASSERT(Model_IsValid(594));
	ASSERT(Model_IsValid(595));
	ASSERT(Model_IsValid(596));
	ASSERT(Model_IsValid(597));
	ASSERT(Model_IsValid(598));
	ASSERT(Model_IsValid(599));
	ASSERT(Model_IsValid(600));
	ASSERT(Model_IsValid(601));
	ASSERT(Model_IsValid(602));
	ASSERT(Model_IsValid(603));
	ASSERT(Model_IsValid(604));
	ASSERT(Model_IsValid(605));
	ASSERT(Model_IsValid(606));
	ASSERT(Model_IsValid(607));
	ASSERT(Model_IsValid(608));
	ASSERT(Model_IsValid(609));
	ASSERT(Model_IsValid(610));
	ASSERT(Model_IsValid(611));
	ASSERT(!Model_IsValid(612));
	ASSERT(!Model_IsValid(613));
	ASSERT(!Model_IsValid(614));
	ASSERT(!Model_IsValid(1000));
	ASSERT(!Model_IsValid(654684));
}

@test(.group = "y_vehicledata") VIM_NamesRange()
{
	ASSERT(VIM_LocalEmpty(Model_Name(-8)));
	ASSERT(VIM_LocalEmpty(Model_Name(10)));
	ASSERT(VIM_LocalEmpty(Model_Name(397)));
	ASSERT(VIM_LocalEmpty(Model_Name(398)));
	ASSERT(VIM_LocalEmpty(Model_Name(399)));
	ASSERT_SAME(Model_Name(400), "Landstalker");
	ASSERT_SAME(Model_Name(401), "Bravura");
	ASSERT_SAME(Model_Name(402), "Buffalo");
	ASSERT_SAME(Model_Name(403), "Linerunner");
	ASSERT_SAME(Model_Name(404), "Perennial");
	ASSERT_SAME(Model_Name(405), "Sentinel");
	ASSERT_SAME(Model_Name(406), "Dumper");
	ASSERT_SAME(Model_Name(407), "Firetruck");
	ASSERT_SAME(Model_Name(408), "Trashmaster");
	ASSERT_SAME(Model_Name(409), "Stretch");
	ASSERT_SAME(Model_Name(410), "Manana");
	ASSERT_SAME(Model_Name(411), "Infernus");
	ASSERT_SAME(Model_Name(412), "Voodoo");
	ASSERT_SAME(Model_Name(413), "Pony");
	ASSERT_SAME(Model_Name(414), "Mule");
	ASSERT_SAME(Model_Name(415), "Cheetah");
	ASSERT_SAME(Model_Name(416), "Ambulance");
	ASSERT_SAME(Model_Name(417), "Leviathan");
	ASSERT_SAME(Model_Name(418), "Moonbeam");
	ASSERT_SAME(Model_Name(419), "Esperanto");
	ASSERT_SAME(Model_Name(420), "Taxi");
	ASSERT_SAME(Model_Name(421), "Washington");
	ASSERT_SAME(Model_Name(422), "Bobcat");
	ASSERT_SAME(Model_Name(423), "Mr Whoopee");
	ASSERT_SAME(Model_Name(424), "BF Injection");
	ASSERT_SAME(Model_Name(425), "Hunter");
	ASSERT_SAME(Model_Name(426), "Premier");
	ASSERT_SAME(Model_Name(427), "Enforcer");
	ASSERT_SAME(Model_Name(428), "Securicar");
	ASSERT_SAME(Model_Name(429), "Banshee");
	ASSERT_SAME(Model_Name(430), "Predator");
	ASSERT_SAME(Model_Name(431), "Bus");
	ASSERT_SAME(Model_Name(432), "Rhino");
	ASSERT_SAME(Model_Name(433), "Barracks");
	ASSERT_SAME(Model_Name(434), "Hotknife");
	ASSERT_SAME(Model_Name(435), "Article Trailer");
	ASSERT_SAME(Model_Name(436), "Previon");
	ASSERT_SAME(Model_Name(437), "Coach");
	ASSERT_SAME(Model_Name(438), "Cabbie");
	ASSERT_SAME(Model_Name(439), "Stallion");
	ASSERT_SAME(Model_Name(440), "Rumpo");
	ASSERT_SAME(Model_Name(441), "RC Bandit");
	ASSERT_SAME(Model_Name(442), "Romero");
	ASSERT_SAME(Model_Name(443), "Packer");
	ASSERT_SAME(Model_Name(444), "Monster");
	ASSERT_SAME(Model_Name(445), "Admiral");
	ASSERT_SAME(Model_Name(446), "Squalo");
	ASSERT_SAME(Model_Name(447), "Seasparrow");
	ASSERT_SAME(Model_Name(448), "Pizzaboy");
	ASSERT_SAME(Model_Name(449), "Tram");
	ASSERT_SAME(Model_Name(450), "Article Trailer 2");
	ASSERT_SAME(Model_Name(451), "Turismo");
	ASSERT_SAME(Model_Name(452), "Speeder");
	ASSERT_SAME(Model_Name(453), "Reefer");
	ASSERT_SAME(Model_Name(454), "Tropic");
	ASSERT_SAME(Model_Name(455), "Flatbed");
	ASSERT_SAME(Model_Name(456), "Yankee");
	ASSERT_SAME(Model_Name(457), "Caddy");
	ASSERT_SAME(Model_Name(458), "Solair");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(459), "Topfun Van", false, 10));
	ASSERT_SAME(Model_Name(460), "Skimmer");
	ASSERT_SAME(Model_Name(461), "PCJ-600");
	ASSERT_SAME(Model_Name(462), "Faggio");
	ASSERT_SAME(Model_Name(463), "Freeway");
	ASSERT_SAME(Model_Name(464), "RC Baron");
	ASSERT_SAME(Model_Name(465), "RC Raider");
	ASSERT_SAME(Model_Name(466), "Glendale");
	ASSERT_SAME(Model_Name(467), "Oceanic");
	ASSERT_SAME(Model_Name(468), "Sanchez");
	ASSERT_SAME(Model_Name(469), "Sparrow");
	ASSERT_SAME(Model_Name(470), "Patriot");
	ASSERT_SAME(Model_Name(471), "Quad");
	ASSERT_SAME(Model_Name(472), "Coastguard");
	ASSERT_SAME(Model_Name(473), "Dinghy");
	ASSERT_SAME(Model_Name(474), "Hermes");
	ASSERT_SAME(Model_Name(475), "Sabre");
	ASSERT_SAME(Model_Name(476), "Rustler");
	ASSERT_SAME(Model_Name(477), "ZR-350");
	ASSERT_SAME(Model_Name(478), "Walton");
	ASSERT_SAME(Model_Name(479), "Regina");
	ASSERT_SAME(Model_Name(480), "Comet");
	ASSERT_SAME(Model_Name(481), "BMX");
	ASSERT_SAME(Model_Name(482), "Burrito");
	ASSERT_SAME(Model_Name(483), "Camper");
	ASSERT_SAME(Model_Name(484), "Marquis");
	ASSERT_SAME(Model_Name(485), "Baggage");
	ASSERT_SAME(Model_Name(486), "Dozer");
	ASSERT_SAME(Model_Name(487), "Maverick");
	ASSERT_SAME(Model_Name(488), "SAN News Maverick");
	ASSERT_SAME(Model_Name(489), "Rancher");
	ASSERT_SAME(Model_Name(490), "FBI Rancher");
	ASSERT_SAME(Model_Name(491), "Virgo");
	ASSERT_SAME(Model_Name(492), "Greenwood");
	ASSERT_SAME(Model_Name(493), "Jetmax");
	ASSERT_SAME(Model_Name(494), "Hotring Racer");
	ASSERT_SAME(Model_Name(495), "Sandking");
	ASSERT_SAME(Model_Name(496), "Blista Compact");
	ASSERT_SAME(Model_Name(497), "Police Maverick");
	ASSERT_SAME(Model_Name(498), "Boxville");
	ASSERT_SAME(Model_Name(499), "Benson");
	ASSERT_SAME(Model_Name(500), "Mesa");
	ASSERT_SAME(Model_Name(501), "RC Goblin");
	ASSERT_SAME(Model_Name(502), "Hotring Racer \"A\"");
	ASSERT_SAME(Model_Name(503), "Hotring Racer \"B\"");
	ASSERT_SAME(Model_Name(504), "Bloodring Banger");
	ASSERT_SAME(Model_Name(505), "Rancher Lure");
	ASSERT_SAME(Model_Name(506), "Super GT");
	ASSERT_SAME(Model_Name(507), "Elegant");
	ASSERT_SAME(Model_Name(508), "Journey");
	ASSERT_SAME(Model_Name(509), "Bike");
	ASSERT_SAME(Model_Name(510), "Mountain Bike");
	ASSERT_SAME(Model_Name(511), "Beagle");
	ASSERT_SAME(Model_Name(512), "Cropduster");
	ASSERT_SAME(Model_Name(513), "Stuntplane");
	ASSERT_SAME(Model_Name(514), "Tanker");
	ASSERT_SAME(Model_Name(515), "Roadtrain");
	ASSERT_SAME(Model_Name(516), "Nebula");
	ASSERT_SAME(Model_Name(517), "Majestic");
	ASSERT_SAME(Model_Name(518), "Buccaneer");
	ASSERT_SAME(Model_Name(519), "Shamal");
	ASSERT_SAME(Model_Name(520), "Hydra");
	ASSERT_SAME(Model_Name(521), "FCR-900");
	ASSERT_SAME(Model_Name(522), "NRG-500");
	ASSERT_SAME(Model_Name(523), "HPV1000");
	ASSERT_SAME(Model_Name(524), "Cement Truck");
	ASSERT_SAME(Model_Name(525), "Towtruck");
	ASSERT_SAME(Model_Name(526), "Fortune");
	ASSERT_SAME(Model_Name(527), "Cadrona");
	ASSERT_SAME(Model_Name(528), "FBI Truck");
	ASSERT_SAME(Model_Name(529), "Willard");
	ASSERT_SAME(Model_Name(530), "Forklift");
	ASSERT_SAME(Model_Name(531), "Tractor");
	ASSERT_SAME(Model_Name(532), "Combine Harvester");
	ASSERT_SAME(Model_Name(533), "Feltzer");
	ASSERT_SAME(Model_Name(534), "Remington");
	ASSERT_SAME(Model_Name(535), "Slamvan");
	ASSERT_SAME(Model_Name(536), "Blade");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(537), "Freight", false, 7));
	ASSERT_ZE(strcmp(Model_Name(538), "Brownstreak", false, 11));
	ASSERT_SAME(Model_Name(539), "Vortex");
	ASSERT_SAME(Model_Name(540), "Vincent");
	ASSERT_SAME(Model_Name(541), "Bullet");
	ASSERT_SAME(Model_Name(542), "Clover");
	ASSERT_SAME(Model_Name(543), "Sadler");
	ASSERT_SAME(Model_Name(544), "Firetruck LA");
	ASSERT_SAME(Model_Name(545), "Hustler");
	ASSERT_SAME(Model_Name(546), "Intruder");
	ASSERT_SAME(Model_Name(547), "Primo");
	ASSERT_SAME(Model_Name(548), "Cargobob");
	ASSERT_SAME(Model_Name(549), "Tampa");
	ASSERT_SAME(Model_Name(550), "Sunrise");
	ASSERT_SAME(Model_Name(551), "Merit");
	ASSERT_SAME(Model_Name(552), "Utility Van");
	ASSERT_SAME(Model_Name(553), "Nevada");
	ASSERT_SAME(Model_Name(554), "Yosemite");
	ASSERT_SAME(Model_Name(555), "Windsor");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(556), "Monster", false, 7));
	ASSERT_ZE(strcmp(Model_Name(557), "Monster", false, 7));
	ASSERT_SAME(Model_Name(558), "Uranus");
	ASSERT_SAME(Model_Name(559), "Jester");
	ASSERT_SAME(Model_Name(560), "Sultan");
	ASSERT_SAME(Model_Name(561), "Stratum");
	ASSERT_SAME(Model_Name(562), "Elegy");
	ASSERT_SAME(Model_Name(563), "Raindance");
	ASSERT_SAME(Model_Name(564), "RC Tiger");
	ASSERT_SAME(Model_Name(565), "Flash");
	ASSERT_SAME(Model_Name(566), "Tahoma");
	ASSERT_SAME(Model_Name(567), "Savanna");
	ASSERT_SAME(Model_Name(568), "Bandito");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(569), "Freight Flat Trailer", false, 20));
	ASSERT_ZE(strcmp(Model_Name(570), "Streak Trailer", false, 14));
	ASSERT_SAME(Model_Name(571), "Kart");
	ASSERT_SAME(Model_Name(572), "Mower");
	ASSERT_SAME(Model_Name(573), "Dune");
	ASSERT_SAME(Model_Name(574), "Sweeper");
	ASSERT_SAME(Model_Name(575), "Broadway");
	ASSERT_SAME(Model_Name(576), "Tornado");
	ASSERT_SAME(Model_Name(577), "AT400");
	ASSERT_SAME(Model_Name(578), "DFT-30");
	ASSERT_SAME(Model_Name(579), "Huntley");
	ASSERT_SAME(Model_Name(580), "Stafford");
	ASSERT_SAME(Model_Name(581), "BF-400");
	ASSERT_SAME(Model_Name(582), "Newsvan");
	ASSERT_SAME(Model_Name(583), "Tug");
	ASSERT_SAME(Model_Name(584), "Petrol Trailer");
	ASSERT_SAME(Model_Name(585), "Emperor");
	ASSERT_SAME(Model_Name(586), "Wayfarer");
	ASSERT_SAME(Model_Name(587), "Euros");
	ASSERT_SAME(Model_Name(588), "Hotdog");
	ASSERT_SAME(Model_Name(589), "Club");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(590), "Freight Box Trailer", false, 19));
	ASSERT_SAME(Model_Name(591), "Article Trailer 3");
	ASSERT_SAME(Model_Name(592), "Andromada");
	ASSERT_SAME(Model_Name(593), "Dodo");
	ASSERT_SAME(Model_Name(594), "RC Cam");
	ASSERT_SAME(Model_Name(595), "Launch");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(596), "Police Car", false, 10));
	ASSERT_ZE(strcmp(Model_Name(597), "Police Car", false, 10));
	ASSERT_ZE(strcmp(Model_Name(598), "Police Car", false, 10));
	ASSERT_SAME(Model_Name(599), "Police Ranger");
	ASSERT_SAME(Model_Name(600), "Picador");
	ASSERT_SAME(Model_Name(601), "S.W.A.T.");
	ASSERT_SAME(Model_Name(602), "Alpha");
	ASSERT_SAME(Model_Name(603), "Phoenix");
	ASSERT_SAME(Model_Name(604), "Glendale Shit");
	ASSERT_SAME(Model_Name(605), "Sadler Shit");
	// The test macro doesn't like `()`s in strings.
	ASSERT_ZE(strcmp(Model_Name(606), "Baggage Trailer", false, 15));
	ASSERT_ZE(strcmp(Model_Name(607), "Baggage Trailer", false, 15));
	ASSERT_SAME(Model_Name(608), "Tug Stairs Trailer");
	ASSERT_SAME(Model_Name(609), "Boxville");
	ASSERT_SAME(Model_Name(610), "Farm Trailer");
	ASSERT_SAME(Model_Name(611), "Utility Trailer");
	ASSERT(VIM_LocalEmpty(Model_Name(612)));
	ASSERT(VIM_LocalEmpty(Model_Name(613)));
	ASSERT(VIM_LocalEmpty(Model_Name(614)));
	ASSERT(VIM_LocalEmpty(Model_Name(1000)));
	ASSERT(VIM_LocalEmpty(Model_Name(987654)));
}

