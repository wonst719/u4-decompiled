/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

/*----------------------------------------
MODULE SEARCH[dungeon]
----------------------------------------*/

char *D_2E04[] = {/*D_2DF0*/U4TEXT_SRCH2_13};

C_B730(bp06, bp04)
int bp06;
int bp04;
{
	Gra_11(bp06);
	sound(7);
	sound(7);
	sound(7);
	Gra_11(bp06);
	hitChara(bp06, 100 * bp04);
}

/*increment characteristic (max 50)*/
C_B770(bp06, bp04)
int *bp06;
int bp04;
{
	*bp06 += bp04;
	*bp06 = (*bp06 > 50)?50:*bp06;
}

int D_2E6E[] = {2,2,2,4,4,4,6,6};/*magical ball hits points*/
int D_2E7E[][8] = {/*magical ball characteristic*/
	{0,0,5,0,5,5,5,0},
	{0,5,0,5,5,0,5,0},
	{5,0,0,5,0,5,5,0}
};

/*magical ball*/
C_B795()
{
	int bp_02;

	u4_puts(/*D_2E06*/U4TEXT_SRCH2_48);
	if((bp_02 = AskChara(/*D_2E23*/U4TEXT_SRCH2_49)) < 0)
		return;
	if(!isCharaConscious(bp_02)) {
		u4_puts(/*D_2E33*/U4TEXT_SRCH2_52);
		return;
	}
	D_8742._map.x8x8x8[Party._z][Party._y][Party._x] = 0;
	C_B730(bp_02, D_2E6E[Party._loc - 0x11]);
	/*-- which characteristic(s) ? --*/
	if(D_2E7E[0][Party._loc - 0x11]) {
		C_B770(&(Party.chara[bp_02]._str), 5);
		u4_puts(/*D_2E3F*/U4TEXT_SRCH2_60);
	}
	if(D_2E7E[1][Party._loc - 0x11]) {
		C_B770(&(Party.chara[bp_02]._dex), 5);
		u4_puts(/*D_2E4D*/U4TEXT_SRCH2_64);
	}
	if(D_2E7E[2][Party._loc - 0x11]) {
		C_B770(&(Party.chara[bp_02]._int), 5);
		u4_puts(/*D_2E5C*/U4TEXT_SRCH2_68);
	}
}

/*fountain*/
C_B863()
{
	int bp_02;

	u4_puts(/*D_2EAE*/U4TEXT_SRCH2_77);
	if((bp_02 = AskChara(/*D_2EC4*/U4TEXT_SRCH2_78)) < 0)
		return;
	if(!isCharaConscious(bp_02)) {
		u4_puts(/*D_2ED3*/U4TEXT_SRCH2_81);
		return;
	}
	switch(tile_cur & 0xf) {
		case 0:	u4_puts(D_2E04[0]); break;
		case 1:
			if(Party.chara[bp_02]._HP[0] == Party.chara[bp_02]._HP[1]) {
				u4_puts(D_2E04[0]);
			} else {
				u4_puts(/*D_2EDF*/U4TEXT_SRCH2_90);
				Party.chara[bp_02]._HP[0] = Party.chara[bp_02]._HP[1];
			}
		break;
		case 2:
			u4_puts(/*D_2EF1*/U4TEXT_SRCH2_95);
			C_B730(bp_02, 1);
		return;
		case 3:
			if(Party.chara[bp_02]._stat != STATUS_POISON) {
				u4_puts(D_2E04[0]);
			} else {
				Party.chara[bp_02]._stat = STATUS_GOOD;
				u4_puts(/*D_2F01*/U4TEXT_SRCH2_103);
			}
		break;
		case 4:
			if(Party.chara[bp_02]._stat == STATUS_POISON) {
				u4_puts(D_2E04[0]);
			} else {
				Party.chara[bp_02]._stat = STATUS_POISON;
				u4_puts(/*D_2F13*/U4TEXT_SRCH2_111);
				C_B730(bp_02, 1);
			};
		break;
	}
}

/*found stone*/
C_B93F()
{
	if(
		Party._loc == 0x17 || Party._loc == 0x18 ||
		TST_MSK(Party.mStones, Party._loc - 0x11)
	) {
		u4_puts(/*D_2F26*/U4TEXT_SRCH2_125);
		return;
	}
	SET_MSK(Party.mStones, Party._loc - 0x11);
	u4_puts(/*D_2F3A*/U4TEXT_SRCH2_129);
	u4_puts(D_0884[Party._loc - 0x11]);
	u4_puts(/*D_2F49*/U4TEXT_SRCH2_131);
	karma_inc(&(Party._honor), 5);
	XP_inc(0, 200);
}

/*(S)earch [dungeon]*/
DNG_Search()
{
	u4_puts(/*D_2F52*/U4TEXT_SRCH2_139);
	switch(tile_cur & 0xf0) {
		case 0x70: C_B795(); break;
		case 0x90: C_B863(); break;
		case 0xB0: C_B93F(); break;
		default: u4_puts(/*D_2F5D*/U4TEXT_SRCH2_144);
	}
}
