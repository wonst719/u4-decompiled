/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"
#include "u4_i18n.h"

#include <string.h>

C_45B5()
{
	for( ;txt_Y <= 8; txt_Y ++) {
		u4_SetTextX(24);
		u4_puts(/*D_18C6*/"               ");
	}
}

/*display centered string*/
Z_PutCenteredString(si/*bp06*/)
register char *si;
{
	register int di;

	di = strlen(si);
	if(di > 24)
		di = 24;
	di -= (di & 1);

	txt_X = (24 - di) / 2 + 50;
	if(txt_Y == 0) {
		u4_DecrementTextX();
		u4_putc(0x10);
	}
	u4_puts(si);
	if(txt_Y == 0)
		u4_putc(0x11);
}

C_4649()
{
	unsigned bp_02, bp_04;

	bp_02 = txt_Y;
	bp_04 = txt_X;
	u4_SetTextCoordYX(0, 24);
	do {
		Gra_putchar('\r');
		u4_IncrementTextX();
	} while (txt_X < 39 * 2);
	txt_Y = bp_02;
	txt_X = bp_04;
}

C_4689(bp04)
int bp04;
{
	register struct tChara *si;

	si = &(Party.chara[bp04]);
	u4_SetTextY(0); Z_PutCenteredString(si->_name);
	u4_SetTextX(24);
	u4_SetTextY(1); u4_putc(si->p_24);
	u4_SetTextY(1); Z_PutCenteredString(Strings[77 + si->_class]);
	u4_SetTextX(38); u4_putc(si->_stat);
	u4_SetTextX(25);
	u4_SetTextY(3); u4_puts(/*D_18D6*/U4TEXT_Z_68); u4_putl(si->_MP, 2, '0');
	u4_SetTextX(32); u4_puts(/*D_18DA*/U4TEXT_Z_69); u4_putc((si->_HP[1]/100)+'0');
	u4_SetTextX(24);
	u4_SetTextY(4); u4_puts(/*D_18DE*/U4TEXT_Z_71); u4_putl(si->_str, 2, '0');
	u4_SetTextX(32); u4_puts(/*D_18E3*/U4TEXT_Z_72); u4_putl(si->_HP[0], 4, '0');
	u4_SetTextX(24);
	u4_SetTextY(5); u4_puts(/*D_18E7*/U4TEXT_Z_74); u4_putl(si->_dex, 2, '0');
	u4_SetTextX(32); u4_puts(/*D_18EC*/U4TEXT_Z_75); u4_putl(si->_HP[1], 4, '0');
	u4_SetTextX(24);
	u4_SetTextY(6); u4_puts(/*D_18F0*/U4TEXT_Z_77); u4_putl(si->_int, 2, '0');
	u4_SetTextX(32); u4_puts(/*D_18F5*/U4TEXT_Z_78); u4_putl(si->_XP, 4, '0');
	u4_SetTextY(7);
	u4_SetTextX(24); u4_puts(/*D_18F9*/U4TEXT_Z_80); u4_puts(Strings[37 + si->_weapon]);
	u4_SetTextY(8);
	u4_SetTextX(24); u4_puts(/*D_18FC*/U4TEXT_Z_82); u4_puts(Strings[53 + si->_armor]);
}

Z_Weapons()
{
	register int si;

	u4_SetTextY(0);
	Z_PutCenteredString(/*D_18FF*/U4TEXT_Z_91);
	u4_SetTextCoordYX(1, 24);
	u4_puts(/*D_1907*/U4TEXT_Z_93);
	u4_SetTextCoordYX(2, 24);
	si = 1;
	do {
		if(Party._weapons[si]) {
			u4_putc(si+'A');
			u4_putl(Party._weapons[si], 2, '-');
			u4_putc('-');
			u4_puts(Strings[61 + si]);
			txt_X = (txt_X - 1) & ~7;
			if(++txt_Y == 9) {
				u4_SetTextY(1);
				txt_X += 8;
			}
		}
	} while(++si < 0x10);
	while(txt_X < 40) {
		u4_puts(/*D_190F*/"       ");
		txt_X = (txt_X - 1) & ~7;
		if(++txt_Y == 9) {
			u4_SetTextY(1);
			txt_X += 8;
		}
	}
}

Z_Armour()
{
	register int si;

	u4_SetTextY(0);
	Z_PutCenteredString(/*D_1917*/U4TEXT_Z_124);
	u4_SetTextCoordYX(1, 24);
	u4_puts(/*D_191E*/U4TEXT_Z_126);
	txt_Y = 2;
	for(si = 1; si < 8; si ++) {
		if(Party._armors[si]) {
			u4_SetTextX(24);
			u4_putc(si + 'A');
			u4_putl(Party._armors[si], 2, '-');
			u4_putc('-');
			u4_puts(Strings[53 + si]);
			while(txt_X <= 39 * 2)
				u4_putc(' ');
			u4_IncrementTextY();
		}
	}
	C_45B5();
}

Z_Equipment()
{
	u4_SetTextY(0);
	Z_PutCenteredString(/*D_192C*/U4TEXT_Z_146);

	u4_SetTextCoord(24, 1);
	u4_putl(Party._torches, 2, ' '); u4_puts(/*D_1936*/U4TEXT_Z_149);

	u4_SetTextX(24);
	u4_IncrementTextY();
	u4_putl(Party._gems, 2, ' '); u4_puts(/*D_193F*/U4TEXT_Z_153);

	u4_SetTextX(24);
	u4_IncrementTextY();
	u4_putl(Party._keys, 2, ' '); u4_puts(/*D_1945*/U4TEXT_Z_157);

	if(Party._sextants) {
		u4_SetTextCoord(24, 4);
		u4_putl(Party._sextants, 2, ' '); u4_puts(/*D_194B*/U4TEXT_Z_161);
	}
	u4_IncrementTextY();
	C_45B5();
}

char D_199A[] = "BYRGOPWB";
char D_19A4[] = "HCVJSHSH";

Z_Items()
{
	register int si;

	u4_SetTextY(0);
	Z_PutCenteredString(/*D_1955*/U4TEXT_Z_175);
	u4_SetTextY(1);
	if(Party.mStones) {
		u4_SetTextX(24);
		u4_puts(/*D_195B*/U4TEXT_Z_179);
		si = 0;
		do {
			if(TST_MSK(Party.mStones, si))
				u4_putc(D_199A[si]);
		} while(++si < 8);
		u4_IncrementTextY();
	}
	if(Party.mRunes) {
		u4_SetTextX(24);
		u4_puts(/*D_1963*/U4TEXT_Z_189);
		si = 0;
		do {
			if(TST_MSK(Party.mRunes, si))
				u4_putc(D_19A4[si]);
		} while(++si < 8);
		u4_IncrementTextY();
	}
	if(TST_MSK(Party.mItems, 4) || TST_MSK(Party.mItems, 3) || TST_MSK(Party.mItems, 2)) {
		u4_SetTextX(24);
		if(TST_MSK(Party.mItems, 4))
			u4_puts(/*D_196A*/U4TEXT_Z_200);
		if(TST_MSK(Party.mItems, 3))
			u4_puts(/*D_1970*/U4TEXT_Z_202);
		if(TST_MSK(Party.mItems, 2)) {
			u4_puts(/*D_1976*/U4TEXT_Z_204);
			if(!TST_MSK(Party.mItems, 3) || !TST_MSK(Party.mItems, 4))
				u4_putc('e');
		}
		u4_IncrementTextY();
	}
	if(TST_MSK(Party.mItems, 5) || TST_MSK(Party.mItems, 6) || TST_MSK(Party.mItems, 7)) {
		u4_SetTextX(24);
		u4_puts(/*D_197C*/U4TEXT_Z_212);
		if(TST_MSK(Party.mItems, 7))
			u4_putc('T');
		if(TST_MSK(Party.mItems, 6))
			u4_putc('L');
		if(TST_MSK(Party.mItems, 5))
			u4_putc('C');
		u4_IncrementTextY();
	}
	if(TST_MSK(Party.mItems, 8)) {
		u4_SetTextX(24);
		u4_puts(/*D_1988*/U4TEXT_Z_223);
		u4_IncrementTextY();
	}
	if(TST_MSK(Party.mItems, 9)) {
		u4_SetTextX(24);
		u4_puts(/*D_198D*/U4TEXT_Z_228);
		u4_IncrementTextY();
	}
	if(TST_MSK(Party.mItems, 0)) {
		u4_SetTextX(24);
		u4_puts(/*D_1993*/U4TEXT_Z_233);
	}
}

Z_Reagents()
{
	register int si;

	u4_SetTextY(0);
	Z_PutCenteredString(/*D_19AD*/U4TEXT_Z_242);
	u4_SetTextY(1);
	si = 0;
	do {
		if(Party._reagents[si]) {
			u4_SetTextX(24);
			u4_putc(si+'A');
			u4_putl(Party._reagents[si], 2, '-');
			u4_putc('-');
			u4_puts(Strings[93 + si]);
			while(txt_X < 39 * 2)
				u4_putc(' ');
			u4_IncrementTextY();
		}
	} while(++si < 8);
	C_45B5();
}

Z_Mixtures()
{
	register int si;

	u4_SetTextY(0);
	Z_PutCenteredString(/*D_19B6*/U4TEXT_Z_265);
	u4_SetTextCoordYX(1, 24);
	si = 0;
	do {
		if(Party._mixtures[si]) {
			u4_putc(si+'A');
			u4_putc('-');
			u4_putl(Party._mixtures[si], 2, '0');
			txt_X -= 4;
			u4_IncrementTextY();
			if(txt_Y == 9) {
				u4_SetTextY(1);
				txt_X += 5;
				if(txt_X >= 39 * 2)
					return;
			}
		}
	} while(++si < 26);
}

typedef z_handler(int);
typedef z_handler *pZ_handler;

pZ_handler D_19C0[] = {
	C_4689,C_4689,C_4689,C_4689,
	C_4689,C_4689,C_4689,C_4689,
	Z_Weapons,
	Z_Armour,
	Z_Equipment,
	Z_Items,
	Z_Reagents,
	Z_Mixtures
};

C_4CC1(bp04)
int bp04;
{
	unsigned bp_02, bp_04;

	bp_02 = txt_Y;
	bp_04 = txt_X;
	do {
		register int si;

		Gra_13();
		C_4649();
		(*D_19C0[bp04])(bp04);
		while(!u_kbhit());
		switch(si = u_kbread()) {
			case KBD_1:
			case KBD_2:
			case KBD_3:
			case KBD_4:
			case KBD_5:
			case KBD_6:
			case KBD_7:
			case KBD_8:
				if((si&0xf) <= Party.party_size)
					bp04 = (si&0xf) - 1;
				else
					sound(1);
			break;
			case KBD_RIGHT: case KBD_DOWN:
				bp04 = (bp04 + 1) % 14;
				if(bp04 == Party.party_size)
					bp04 = 8;
			break;
			case KBD_UP: case KBD_LEFT:
				if(bp04 == 8)
					bp04 = Party.party_size - 1;
				else
					bp04 = (bp04 + 13) % 14;
			break;
			case KBD_PGUP:
				if(bp04 >= 1 && bp04 <= 8)
					bp04 = 0;
				else if(bp04 > 8 && bp04 <= 13)
					bp04 = 8;
				else bp04 = 13;
			break;
			case KBD_HOME:
				bp04 = 0;
			break;
			case KBD_0:
				bp04 = 8;
			break;
			case KBD_PGDN:
				if(bp04 >= 0 && bp04 <= 7)
					bp04 = 8;
				else if(bp04 >= 8 && bp04 <= 12)
					bp04 = 13;
				else
					bp04 = 0;
			break;
			case KBD_END:
				bp04 = 13;
			break;
			default:
				bp04 = -1;
		}
	} while(bp04 != -1);
	C_4649();
	Gra_13();
	dspl_Stats();
	txt_Y = bp_02;
	txt_X = bp_04;
}

/*C_4E45*/CMD_Ztats()
{
	if(CurMode >= MOD_COMBAT) {
		u4_puts(/*D_19DC*/U4TEXT_Z_376);
		Gra_11(activeChara);
		C_4CC1(activeChara);
		Gra_11(activeChara);
	} else {
		int bp_02;

		bp_02 = AskChara(/*D_19E3*/U4TEXT_Z_383);
		if(bp_02 != -1)
			C_4CC1((bp_02 == -2)?8:bp_02);
	}
}
