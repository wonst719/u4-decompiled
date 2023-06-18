/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>
#include <stdlib.h>

/*---- mantras*/
char *D_8322[] = {
	/*D_7B62*/U4TEXT_SHRIN_14,
	/*D_7B66*/U4TEXT_SHRIN_15,
	/*D_7B69*/U4TEXT_SHRIN_16,
	/*D_7B6C*/U4TEXT_SHRIN_17,
	/*D_7B70*/U4TEXT_SHRIN_18,
	/*D_7B74*/U4TEXT_SHRIN_19,
	/*D_7B79*/U4TEXT_SHRIN_20,
	/*D_7B7C*/U4TEXT_SHRIN_21
};
/*---- visions*/
char *D_8332[][3] = {
	{
		/*D_7B80*/U4TEXT_SHRIN_26,
		/*D_7BCD*/U4TEXT_SHRIN_27,
		/*D_7C10*/U4TEXT_SHRIN_28,
	}, {
		/*D_7C5C*/U4TEXT_SHRIN_30,
		/*D_7CAA*/U4TEXT_SHRIN_31,
		/*D_7CF3*/U4TEXT_SHRIN_32,
	}, {
		/*D_7D40*/U4TEXT_SHRIN_34,
		/*D_7D85*/U4TEXT_SHRIN_35,
		/*D_7DCF*/U4TEXT_SHRIN_36,
	}, {
		/*D_7E1C*/U4TEXT_SHRIN_38,
		/*D_7E6C*/U4TEXT_SHRIN_39,
		/*D_7EB7*/U4TEXT_SHRIN_40,
	}, {
		/*D_7F11*/U4TEXT_SHRIN_42,
		/*D_7F63*/U4TEXT_SHRIN_43,
		/*D_7FB6*/U4TEXT_SHRIN_44,
	}, {
		/*D_8008*/U4TEXT_SHRIN_46,
		/*D_804E*/U4TEXT_SHRIN_47,
		/*D_8092*/U4TEXT_SHRIN_48,
	}, {
		/*D_80DE*/U4TEXT_SHRIN_50,
		/*D_8133*/U4TEXT_SHRIN_51,
		/*D_8178*/U4TEXT_SHRIN_52,
	}, {
		/*D_81D4*/U4TEXT_SHRIN_54,
		/*D_8222*/U4TEXT_SHRIN_55,
		/*D_8271*/U4TEXT_SHRIN_56
	}
};
/*---- visions 2*/
char *D_8362[] = {
	/*D_82DF*/"rune_1",/*I*/
	/*D_82E6*/"rune_2",/*N*/
	/*D_82ED*/"rune_0",/*F*/
	/*D_82F4*/"rune_1",/*I*/
	/*D_82FB*/"rune_2",/*N*/
	/*D_8302*/"rune_1",/*I*/
	/*D_8309*/"rune_3",/*T*/
	/*D_8310*/"rune_4" /*Y*/
};

/*display avatarhood vision I.N.F.I.N.I.T.Y*/
C_E6DF(bp04)
int bp04;
{
	char bp_14[20];

	CurMode = MOD_VISION;
	music();
	strcpy(bp_14, D_8362[bp04]);
	strcat(bp_14, (D_943A == 1)?/*D_8317*/".pic":/*D_831C*/".ega");
	Gra_10();
	Gra_16(bp_14, 0, 0);
}

/*enter a shrine*/
C_E72C()
{
	int loc_A, loc_B, loc_C;
	char loc_D[16];
	int loc_E;

	loc_A = Party._loc - 0x19;/*shrine "number"*/
	if(!TST_MSK(Party.mRunes, loc_A)) {
		u4_puts(/*D_8372*/U4TEXT_SHRIN_93);
C_E755:
		CurMode = MOD_OUTDOORS;
		music();

		Party._loc = 0;
		return;
	}
	if(Load(/*D_83BA*/"SHRINE.CON", 11 * 11, Combat._map) == -1)
		exit(3);
	CurMode = MOD_SHRINE;
	music();

	u4_puts(/*D_83C5*/U4TEXT_SHRIN_102);
	u4_gets(loc_D, 15);
	Gra_CR();
	u4_puts(/*D_8425*/U4TEXT_SHRIN_105);
	loc_E = AskLetter(/*D_8434*/U4TEXT_SHRIN_106, '0', '3');
	if(loc_E < 0) {
		goto C_E755;
	}
	loc_E -= '0';
	if(loc_E == 0 || strnicmp(loc_D, D_1E98[151 + loc_A], 16)) {
		u4_puts(/*D_8445*/U4TEXT_SHRIN_112);
		goto C_E755;
	}
	if(Party._moves / 100 == Party.f_1ea) {
		u4_puts(/*D_847E*/U4TEXT_SHRIN_116);
		goto C_E755;
	}
	Party.f_1ea = Party._moves / 100;
	u4_puts(/*D_84B2*/U4TEXT_SHRIN_120);
	for(loc_B = 0; loc_B < loc_E; loc_B ++) {
		for(loc_C = 0; loc_C < 0x10; loc_C ++) {
			u_delay(1, 0);
			u4_putc('.');
		}
		u_kbflush();
		u4_puts(/*D_84C4*/U4TEXT_SHRIN_127);
		u4_gets(loc_D, 15);
		Gra_CR();
		if(strnicmp(loc_D, D_8322[loc_A], 0x10)) {
			u4_puts(/*D_84CE*/U4TEXT_SHRIN_131);
			karma_dec(&(Party._spiri), 3);
			goto C_E755;
		}
	}
	if(loc_E != 3 || *(pKarmas[loc_A]) != 99) {
		u4_puts(/*D_850A*/U4TEXT_SHRIN_137);
		karma_inc(&(Party._spiri), loc_E * 3);
		u_kbflush();
		u_kbread();
		Gra_CR();
		u4_puts(D_8332[loc_A][loc_E - 1]);
	} else {
		u4_puts(/*D_853E*/U4TEXT_SHRIN_144);
		u4_puts(D_1E98[151 + loc_A]);
		Gra_09(); sound(9, 0xff); Gra_09();
		Gra_CR();
		*(pKarmas[loc_A]) = 0;
		dspl_Stats();
		u_kbflush();
		u_kbread();
		u4_puts(/*D_8577*/U4TEXT_SHRIN_152);
		C_E6DF(loc_A);
		u_kbflush();
	}
	u_kbread();
	Gra_CR();
	goto C_E755;
}
