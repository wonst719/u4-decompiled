/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>
#include "u4_i18n.h"

char D_00EE[] = U4TEXT_USE_12;
char D_0100[] = U4TEXT_USE_13;
char D_010E[] = {/*colors masks*/
	(1<<6)|(1<<5)|(1<<3)|(1<<0),/*truth*/
	(1<<6)|(1<<4)|(1<<3)|(1<<1),/*love*/
	(1<<6)|(1<<5)|(1<<4)|(1<<2) /*courage*/
};

void C_01E1()
{
	int bp_10, bp_02;
	char bp_12[12];
	char bp_04;

	if(Combat._charaX[activeChara] != 5 || Combat._charaY[activeChara] != 5 || D_943E_AltarRoomPrinciple == -1) {
		u4_puts(D_00EE);
		return;
	}
	u4_puts(/*D_0080*/U4TEXT_USE_30);
	bp_04 = 0;
	for(bp_02 = 1; bp_02 <= 4; bp_02++) {
		u4_putc(bp_02 + 'A' - 1); u4_putc(':');
		u4_gets(bp_12, 11);
		Gra_CR();
		for(bp_10 = 7; bp_10 >= 0; bp_10--) {
			if(strnicmp(D_0884[bp_10], bp_12, 12) == 0)
				break;
		}
		if(bp_10 == -1 || !TST_MSK(Party.mStones, bp_10)) {
			if(*bp_12 != '\0')
				u4_puts(D_0100);
			return;
		}
		if((1 << bp_10) & bp_04) {
			u4_puts(/*D_00AD*/U4TEXT_USE_46);
			return;
		}
		bp_04 |= (1 << bp_10);
	}
	if(D_010E[D_943E_AltarRoomPrinciple] != bp_04) {
		u4_puts(D_00EE);
		return;
	}
	switch(D_943E_AltarRoomPrinciple) {
		case 0:
			if(TST_MSK(Party.mItems, 7)) {
				u4_puts(D_00EE);
				return;
			}
			SET_MSK(Party.mItems, 7);
		break;
		case 1:
			if(TST_MSK(Party.mItems, 6)) {
				u4_puts(D_00EE);
				return;
			}
			SET_MSK(Party.mItems, 6);
		break;
		case 2:
			if(TST_MSK(Party.mItems, 5)) {
				u4_puts(D_00EE);
				return;
			}
			SET_MSK(Party.mItems, 5);
		break;
	}
	u4_puts(/*D_00BC*/U4TEXT_USE_78);
}

char *D_0284[] = {
	/*D_0111*/U4TEXT_USE_82,
	/*D_0117*/U4TEXT_USE_83,
	/*D_011C*/U4TEXT_USE_84,
	/*D_0124*/U4TEXT_USE_85,
	/*D_0133*/U4TEXT_USE_86,
	/*D_0144*/U4TEXT_USE_87,
	/*D_0156*/U4TEXT_USE_88,
	/*D_016E*/U4TEXT_USE_89
};

/*use stone(s)*/
C_0311() {
	int bp_02;

	if(Party.mStones) {
		char bp_10[14];
		if(CurMode != MOD_COM_ROOM && CurMode != MOD_DUNGEON)
			u4_puts(/*D_01BF*/U4TEXT_USE_99);
		if(CurMode == MOD_DUNGEON) {
			if(tile_cur != 0xb0 || Party._loc != 0x18) {
				u4_puts(D_00EE);
				return;
			}
			if(Party._z != 7)
				u4_puts(/*D_01D6*/U4TEXT_USE_106);
			u4_puts(D_0284[Party._z]);
			u4_puts(/*D_021D*/U4TEXT_USE_108);
			u4_gets(bp_10, 13);
			Gra_CR();
			if(strnicmp(bp_10, D_1E98[151 + Party._z], 14)) {
C_03A1:
				if(bp_10[0])
					u4_puts(D_00EE);
				return;
			}
			u4_puts(/*D_0221*/U4TEXT_USE_117);
			u4_gets(bp_10, 11);
			Gra_CR();
			bp_02 = 7;
			while(
				strnicmp(bp_10, D_0884[bp_02], 12) &&
				--bp_02 >= 0
			);
			if(bp_02 == -1)
				goto C_03A1;
			if(!TST_MSK(Party.mStones, bp_02)) {
				u4_puts(/*D_024A*/U4TEXT_USE_128);
				return;
			}
			if(Party._z != bp_02) {
				u4_puts(D_00EE);
				return;
			}
			if(Party._z == 7) {
				C_31F4();/*last phase of game*/
				return;
			}
			D_8742._map.x8x8x8[Party._z][Party._y][Party._x] = 0x20;
			u4_puts(/*D_025C*/U4TEXT_USE_140);
		} else {
			C_01E1();
		}
	} else {
		u4_puts(D_0100);
	}
}

/*use key(s)*/
C_044C() {
	if(
		((Party.mItems >> 7) & 1) |
		((Party.mItems >> 6) & 1) |
		((Party.mItems >> 5) & 1)
	)
		u4_puts(U4TEXT_USE_156);
	else
		u4_puts(D_0100);
}

/*use bell*/
C_0487() {
	if(!TST_MSK(Party.mItems, 4)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0 || Party._x != 0xe9 || Party._y != 0xe9) {
		u4_puts(D_00EE);
		return;
	}
	SET_MSK(Party.mItems, 12);
	u4_puts(U4TEXT_USE_172);
}

/*use book*/
C_04C0() {
	if(!TST_MSK(Party.mItems, 3)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0 || Party._x != 0xe9 || Party._y != 0xe9 ||
		!TST_MSK(Party.mItems, 12)
	) {
		u4_puts(D_00EE);
		return;
	}
	SET_MSK(Party.mItems, 11);
	u4_puts(U4TEXT_USE_188);
}

/*use candle*/
C_0501() {
	if(!TST_MSK(Party.mItems, 2)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0 || Party._x != 0xe9 || Party._y != 0xe9 ||
		!TST_MSK(Party.mItems, 11)
	) {
		u4_puts(D_00EE);
		return;
	}
	SET_MSK(Party.mItems, 10);
	u4_puts(U4TEXT_USE_204);
	sound(6);
	shakefx();
}

/*use horn*/
C_0553() {
	if(!TST_MSK(Party.mItems, 8)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0) {
		u4_puts(D_00EE);
		return;
	}
	u4_puts(U4TEXT_USE_219);
	spell_sta = 1;
	spell_cnt = 10;
	dspl_Stats();
}

/*use wheel*/
C_058C() {
	if(!TST_MSK(Party.mItems, 9)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0 || Party._tile > TIL_13 || Party._ship != 50) {
		u4_puts(D_00EE);
		return;
	}
	u4_puts(U4TEXT_USE_235);
	Party._ship = 99;
	dspl_Stats();
}

/*use skull*/
C_05CE() {
	int bp_02;

	if(!TST_MSK(Party.mItems, 0)) {
		u4_puts(D_0100);
		return;
	}
	if(Party._loc != 0 || Party._x != 0xe9 || Party._y != 0xe9) {
		u4_puts(U4TEXT_USE_249);
		sound(6); shakefx();
		Gra_09();
		sound(6); shakefx();
		Gra_09();
		sound(6); shakefx();
		if(CurMode >= MOD_COMBAT) {
			for(bp_02 = 31; bp_02 >= 0; bp_02 --) {
				if(D_8742._npc._tile[bp_02] != TIL_5E)
					D_8742._npc._tile[bp_02] = D_8742._npc._gtile[bp_02] = 0;
			}
			for(bp_02 = 15; bp_02 >= 0; bp_02 --) {
				if(Fighters._tile[bp_02] != TIL_5E)
					Fighters._tile[bp_02] = Fighters._gtile[bp_02] = 0;
			}
		} else {
			for(bp_02 = (Party._loc == 0)?7:31; bp_02 >= 0; bp_02 --) {
				if(D_8742._npc._tile[bp_02] != TIL_5E)
					D_8742._npc._tile[bp_02] = D_8742._npc._gtile[bp_02] = 0;
			}
		}
/*C_06B2:*/
		t_callback();
		karma_dec((char *)&(Party._hones), 5);
		karma_dec((char *)&(Party._compa), 5);
		karma_dec((char *)&(Party._valor), 5);
		karma_dec((char *)&(Party._justi), 5);
		karma_dec((char *)&(Party._sacri), 5);
		karma_dec((char *)&(Party._honor), 5);
		karma_dec((char *)&(Party._spiri), 5);
		karma_dec((char *)&(Party._humil), 5);
		dspl_Stats();
	} else {
		u4_puts(U4TEXT_USE_282);
		SET_MSK(Party.mItems, 1);
		karma_inc((char *)&(Party._hones), 10);
		karma_inc((char *)&(Party._compa), 10);
		karma_inc((char *)&(Party._valor), 10);
		karma_inc((char *)&(Party._justi), 10);
		karma_inc((char *)&(Party._sacri), 10);
		karma_inc((char *)&(Party._honor), 10);
		karma_inc((char *)&(Party._spiri), 10);
		karma_inc((char *)&(Party._humil), 10);
		sound(6); shakefx();
		Gra_09();
		sound(6); shakefx();
		Gra_09();
		sound(6); shakefx();
	}
	RST_MSK(Party.mItems, 0);
}

struct {
	char *_00;
	void (*_02)();
} D_0434[] = {
	{/*D_03D5*/U4TEXT_USE_305,  C_0311},
	{/*D_03DB*/U4TEXT_USE_306, C_0311},
	{/*D_03E2*/U4TEXT_USE_307,   C_0487},
	{/*D_03E7*/U4TEXT_USE_308,   C_04C0},
	{/*D_03EC*/U4TEXT_USE_309, C_0501},
	{/*D_03F3*/U4TEXT_USE_310,    C_044C},
	{/*D_03F7*/U4TEXT_USE_311,   C_044C},
	{/*D_03FC*/U4TEXT_USE_312,   C_0553},
	{/*D_0401*/U4TEXT_USE_313,  C_058C},
	{/*D_0407*/U4TEXT_USE_314,  C_05CE},
	{/*D_040D*/"",       0}
};

/*C_07AE*/CMD_Use() {
	register int si;
	char bp_0e[12];
#if 0
	C_31F4();
	return;
#endif
	u4_puts(U4TEXT_USE_322);
	u4_gets(bp_0e, 11);
	Gra_CR();
	for(si = 0; D_0434[si]._00[0]; si++) {
		if(strnicmp(D_0434[si]._00, bp_0e, 12) == 0) {
			(*(D_0434[si]._02))();
			return;
		}
	}
	u4_puts(U4TEXT_USE_331);
}
