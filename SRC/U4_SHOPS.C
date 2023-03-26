/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>

/*----------------------------------------*/

char *D_3F0C[][8] = {
	{/* < 20*/
		/*D_316E*/U4TEXT_SHOPS_15,
		/*D_31B4*/U4TEXT_SHOPS_16,
		/*D_3201*/U4TEXT_SHOPS_17,
		/*D_323C*/U4TEXT_SHOPS_18,
		/*D_3273*/U4TEXT_SHOPS_19,
		/*D_32C3*/U4TEXT_SHOPS_20,
		/*D_3315*/U4TEXT_SHOPS_21,
		/*D_3359*/U4TEXT_SHOPS_22,
	}, {/* < 40*/
		/*D_3396*/U4TEXT_SHOPS_24,
		/*D_33E6*/U4TEXT_SHOPS_25,
		/*D_342D*/U4TEXT_SHOPS_26,
		/*D_347A*/U4TEXT_SHOPS_27,
		/*D_34BE*/U4TEXT_SHOPS_28,
		/*D_3506*/U4TEXT_SHOPS_29,
		/*D_3541*/U4TEXT_SHOPS_30,
		/*D_3590*/U4TEXT_SHOPS_31,
	}, {/* < 60*/
		/*D_35DC*/U4TEXT_SHOPS_33,
		/*D_362F*/U4TEXT_SHOPS_34,
		/*D_3672*/U4TEXT_SHOPS_35,
		/*D_36BF*/U4TEXT_SHOPS_36,
		/*D_370E*/U4TEXT_SHOPS_37,
		/*D_3758*/U4TEXT_SHOPS_38,
		/*D_37A9*/U4TEXT_SHOPS_39,
		/*D_37FA*/U4TEXT_SHOPS_40,
	}, {/* < 99*/
		/*D_3848*/U4TEXT_SHOPS_42,
		/*D_3892*/U4TEXT_SHOPS_43,
		/*D_38DF*/U4TEXT_SHOPS_44,
		/*D_392B*/U4TEXT_SHOPS_45,
		/*D_3975*/U4TEXT_SHOPS_46,
		/*D_39BC*/U4TEXT_SHOPS_47,
		/*D_3A10*/U4TEXT_SHOPS_48,
		/*D_3A61*/U4TEXT_SHOPS_49,
	}, {/* >= 99*/
		/*D_3AB6*/U4TEXT_SHOPS_51,
		/*D_3AF5*/U4TEXT_SHOPS_52,
		/*D_3B3F*/U4TEXT_SHOPS_53,
		/*D_3B8F*/U4TEXT_SHOPS_54,
		/*D_3BC3*/U4TEXT_SHOPS_55,
		/*D_3C10*/U4TEXT_SHOPS_56,
		/*D_3C59*/U4TEXT_SHOPS_57,
		/*D_3C93*/U4TEXT_SHOPS_58
	}
};

static unsigned char D_913A;
static unsigned char D_913B, D_913C;
static unsigned D_913E;/*# of drinks in pub*/

/*SHOP #10 - The Seer*/
/*C_C922*/SHP_hawkwind()
{
	int bp_02, bp_04;
	char bp_14[16];

	if(!isCharaConscious(0)) {
		u4_puts(/*D_3CD9*/U4TEXT_SHOPS_73);
		u4_puts(Party.chara[0]._name);
		u4_puts(/*D_3D00*/U4TEXT_SHOPS_75);
		u4_puts(Party.chara[0]._name);
		u4_puts(/*D_3D0F*/U4TEXT_SHOPS_77);
		return;
	}
	u4_puts(/*D_3D1D*/U4TEXT_SHOPS_80);
	u4_puts(Party.chara[0]._name);
	u4_puts(/*D_3D29*/U4TEXT_SHOPS_82);
	u_kbflush();
	u_kbread();
	bp_14[0] = 0;
	while(1) {
		u4_puts(bp_14[0] == 0?
			/*D_3D95*/U4TEXT_SHOPS_88:
			/*D_3DC3*/U4TEXT_SHOPS_89
		);
		u4_gets(bp_14, 15);
		if(
			bp_14[0] == 0 ||
			strnicmp(bp_14, /*D_3DF3*/U4TEXT_SHOPS_94, 16) == 0 ||
			strnicmp(bp_14, /*D_3DF8*/U4TEXT_SHOPS_95, 16) == 0
		) break;
		for(bp_04 = 7; bp_04 >= 0; bp_04 --) {
			if(strnicmp(bp_14, D_1E98[151 + bp_04], 4) == 0)
				break;
		}
		if(bp_04 == -1) {
			u4_puts(/*D_3DFC*/U4TEXT_SHOPS_102);
			continue;
		}
		Gra_CR();
		if(*(pKarmas[bp_04]) == 0) {
			u4_puts(/*D_3E30*/U4TEXT_SHOPS_107);
			continue;
		}
		if(*(pKarmas[bp_04]) < 20) {
			bp_02 = 0;
		} else  if(*(pKarmas[bp_04]) < 40) {
			bp_02 = 1;
		} else  if(*(pKarmas[bp_04]) < 60) {
			bp_02 = 2;
		} else  if(*(pKarmas[bp_04]) < 99) {
			bp_02 = 3;
		} else {
			bp_02 = 4;
		}
		Gra_CR();
		u4_puts(D_3F0C[bp_02][bp_04]);
		Gra_CR();
		if(bp_02 == 4) {
			u4_puts(/*D_3E8A*/U4TEXT_SHOPS_125);
			u_kbflush();
			u_kbread();
		}
	}
	u4_puts(/*D_3EBC*/U4TEXT_SHOPS_130);
	if(Party._moves / 100 != Party.f_1ea) {
		karma_inc(&(Party._spiri), 3);
		Party.f_1ea = Party._moves / 100;
	}
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_4170[16] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 3, 4, 0, 0};

char *D_4180[] = {
	/*D_3F5C*/U4TEXT_SHOPS_143,
	/*D_3F6A*/U4TEXT_SHOPS_144,
	/*D_3F7A*/U4TEXT_SHOPS_145,
	/*D_3F85*/U4TEXT_SHOPS_146
};

char *D_4188[] = {
	/*D_3F92*/U4TEXT_SHOPS_150,
	/*D_3F99*/U4TEXT_SHOPS_151,
	/*D_3F9F*/U4TEXT_SHOPS_152,
	/*D_3FA6*/U4TEXT_SHOPS_153
};

unsigned char D_4190[][6] = {
	{2, 5, 6, 3, 6, 9},
	{2, 4, 9, 6, 4, 8},
	{3, 4, 2, 9, 6, 7},
	{6, 7, 9, 9, 9, 1}
};

/*SHOP #5 - reagents*/
/*C_CAF6*/SHP_reagent()
{
	char loc_C;
	int loc_A, loc_B, loc_D, loc_E;

	D_9142 = D_4170[Party._loc - 1] - 1;
	u4_puts(/*D_3FAE*/U4TEXT_SHOPS_170);
	u4_puts(D_4180[D_9142]);
	Gra_13();
	C_4BC7();
	u4_puts(/*D_3FDF*/U4TEXT_SHOPS_174);
	u4_puts(D_4188[D_9142]);
	u4_puts(/*D_3FE7*/U4TEXT_SHOPS_176);
	loc_C = AskY_N();
	if(loc_C == 'Y') {
		u4_puts(/*D_4008*/U4TEXT_SHOPS_179);
		do {
			u4_puts(/*D_4014*/U4TEXT_SHOPS_181
			);
			loc_B = AskLetter(/*D_4068*/U4TEXT_SHOPS_189, 'A', 'F');
			loc_B -= 'A';
			if(loc_B < 0)
				break;
			u4_puts(/*D_407A*/U4TEXT_SHOPS_193);
			u4_puts(D_1E98[93 + loc_B]);
			u4_puts(/*D_408F*/U4TEXT_SHOPS_195);
			u4_putl(D_4190[D_9142][loc_B], 1, '0');
			u4_puts(/*D_4095*/U4TEXT_SHOPS_197);
			loc_A = AskInt(2);
			if(loc_A > 0) {
				u4_puts(/*D_40B7*/U4TEXT_SHOPS_200);
				u4_putl((long)loc_A * D_4190[D_9142][loc_B], 1, '0');
				u4_puts(/*D_40D1*/U4TEXT_SHOPS_202);
				loc_D = AskInt(3);
				if(loc_D <= 0) {
					if(loc_D < 0)
						sound(1);
				} else {
					if(loc_D < loc_A * D_4190[D_9142][loc_B]) {
						loc_E = loc_A * D_4190[D_9142][loc_B] - loc_D;
						loc_E = (loc_E < 12)?4:(loc_E / 3);
						karma_dec(&(Party._hones), loc_E);
						karma_dec(&(Party._justi), loc_E);
						karma_dec(&(Party._honor), loc_E);
					}
					if(loc_D > Party._gold) {
						u4_puts(/*D_40E5*/U4TEXT_SHOPS_216);
					} else {
						karma_inc(&(Party._hones), 2);
						karma_inc(&(Party._justi), 2);
						karma_inc(&(Party._honor), 2);
						Party._gold -= loc_D; dspl_Gold();
						Party._reagents[loc_B] += loc_A;
						if(Party._reagents[loc_B] > 99)
							Party._reagents[loc_B] = 99;
						C_4BC7();
						u4_puts(/*D_4106*/U4TEXT_SHOPS_226);
					}
				}
			} else {
				u4_puts(/*D_4113*/U4TEXT_SHOPS_230);
			}
			u4_puts(/*D_4121*/U4TEXT_SHOPS_232);
			loc_C = AskY_N();
		} while(loc_C == 'Y');
	}
	Gra_13();
	C_4649();
	dspl_Stats();
	Gra_CR();
	u4_puts(D_4188[D_9142]);
	u4_puts(/*D_4133*/U4TEXT_SHOPS_241);
}

/*----------------------------------------*/

char *D_46A2[] = {
	/*D_41A8*/U4TEXT_SHOPS_247,
	/*D_41B9*/U4TEXT_SHOPS_248,
	/*D_41CC*/U4TEXT_SHOPS_249,
	/*D_41DB*/U4TEXT_SHOPS_250,
	/*D_41EC*/U4TEXT_SHOPS_251,
	/*D_41F8*/U4TEXT_SHOPS_252
};

char *D_46AE[] = {
	/*D_4205*/U4TEXT_SHOPS_256,
	/*D_420D*/U4TEXT_SHOPS_257,
	/*D_4215*/U4TEXT_SHOPS_258,
	/*D_421B*/U4TEXT_SHOPS_259,
	/*D_4221*/U4TEXT_SHOPS_260,
	/*D_4226*/U4TEXT_SHOPS_261
};

unsigned char D_46BA[][4] = {
	{1,  2,  3,  6},
	{5,  6,  8, 10},
	{4, 10, 11, 12},
	{4,  5,  6,  7},
	{8,  9, 13, 14},
	{2,  3,  7,  9}
};

/*prices[weapons]*/
int D_46D2[] = {
	   0,
	  20,
	   2,
	  25,
	 100,
	 225,
	 300,
	 250,
	 600,
	   5,
	 350,
	1500,
	2500,
	2000,
	5000,

	7000/*what is this price for?*/
};

/*shops indexes*/
unsigned char D_46F2[16] = {0, 0, 0, 0, 0, 1, 2, 0, 3, 4, 0, 0, 0, 5, 6, 0};

char *D_4702[] = {
	/*D_422C*/U4TEXT_SHOPS_298,
	/*D_4275*/U4TEXT_SHOPS_299,
	/*D_42B6*/U4TEXT_SHOPS_300,
	/*D_4306*/U4TEXT_SHOPS_301,
	/*D_4350*/U4TEXT_SHOPS_302,
	/*D_439E*/U4TEXT_SHOPS_303,
	/*D_43E7*/U4TEXT_SHOPS_304,
	/*D_4432*/U4TEXT_SHOPS_305,
	/*D_4481*/U4TEXT_SHOPS_306,
	/*D_44CE*/U4TEXT_SHOPS_307,
	/*D_451D*/U4TEXT_SHOPS_308,
	/*D_456F*/U4TEXT_SHOPS_309,
	/*D_45BE*/U4TEXT_SHOPS_310,
	/*D_4608*/U4TEXT_SHOPS_311
};

/*finalize deal[weapon]*/
C_CD1D(bp06, bp04)
int bp06;
int bp04;
{
	if(D_46D2[bp06] * bp04 > Party._gold) {
		u4_puts(/*D_4652*/U4TEXT_SHOPS_320);
		return;
	}
	Party._gold -= D_46D2[bp06] * bp04; dspl_Gold();
	Party._weapons[bp06] += bp04;
	if(Party._weapons[bp06] > 99)
		Party._weapons[bp06] = 99;
	C_4832();
	Gra_CR();
	u4_puts(D_46AE[D_9142]);
	u4_puts(/*D_468A*/U4TEXT_SHOPS_330);
}

/*choose item[weapon]*/
C_CD80()
{
	int loc_A, loc_B, loc_C;

	Gra_CR();
	u4_puts(/*D_471E*/U4TEXT_SHOPS_339);
	do {
		u4_puts(/*D_472D*/U4TEXT_SHOPS_340);
		for(loc_B = 0; loc_B < 4; loc_B ++) {
			u4_putc(D_46BA[D_9142][loc_B] + 'A');
			u4_putc('-');
			u4_puts(D_1E98[37 + D_46BA[D_9142][loc_B]]);
			u4_putc('s');
			Gra_CR();
		}


		do {
			loc_C = AskLetter(/*D_4737*/U4TEXT_SHOPS_352, 'B', 'O');
			loc_C -= 'A';
			if(loc_C <= 0)
				break;
			for(loc_B = 0; loc_B < 4; loc_B ++) {
				if(D_46BA[D_9142][loc_B] == loc_C)
					break;
			}
			if(loc_B == 4)
				sound(1);
		} while(loc_B == 4);
		if(loc_C < 0)
			break;
		if(D_46D2[loc_C] > Party._gold) {
			u4_puts(/*D_4749*/U4TEXT_SHOPS_366);
		} else {
			Gra_CR();
			u4_puts(D_4702[loc_C-1]);
			Gra_CR();
			u4_puts(/*D_476F*/U4TEXT_SHOPS_371);
			loc_A = AskInt(2);
			if(loc_A <= 0) {
				if(loc_A == 0)
					u4_puts(/*D_478D*/U4TEXT_SHOPS_375);
				else
					sound(1);
			} else {
				C_CD1D(loc_C, loc_A);
			}
		}
		u4_puts(/*D_4798*/U4TEXT_SHOPS_382);
		loc_C = (char)AskY_N();
	} while(loc_C == 'Y');
	Gra_CR();
}

#define clamp(a, b, c) if((a)+(b) > (c)) (a) = (c); else (a) += (b)

/*sell item[weapon]*/
C_CEBE()
{
	int loc_A, loc_B;
	char loc_C;

	u4_puts(/*D_47AB*/U4TEXT_SHOPS_396);
	loc_B = -1;
	do {
		u4_SetTextCoordYX(23, 24);
		loc_B = AskLetter(/*D_47C6*/U4TEXT_SHOPS_400, 'B', 'P');
		loc_B -= 'A';
		Gra_CR();
		if(loc_B <= 0)
			break;
		if(Party._weapons[loc_B] == 0) {
			u4_puts(/*D_47D3*/U4TEXT_SHOPS_406);
		} else {
			if(Party._weapons[loc_B] > 1) {
				u4_puts(/*D_47FC*/U4TEXT_SHOPS_409);
				u4_puts(D_1E98[37 + loc_B]);
				u4_puts(/*D_4806*/U4TEXT_SHOPS_411);
				loc_A = AskInt(2);
				if(loc_A <= 0) {
					if(loc_A == 0)
						u4_puts(/*D_4825*/U4TEXT_SHOPS_415);
					else
						sound(1);
					break;
				}
				if(Party._weapons[loc_B] < loc_A) {
					u4_puts(/*D_4830*/U4TEXT_SHOPS_421);
					break;
				}
				u4_puts(/*D_4851*/U4TEXT_SHOPS_424);
				u4_putl(((long)loc_A * D_46D2[loc_B]) >> 1, 1, '0');
				u4_puts(/*D_4862*/U4TEXT_SHOPS_426);
				if(loc_A > 1)
					u4_puts(/*D_486A*/U4TEXT_SHOPS_428);
				else
					u4_puts(/*D_4870*/U4TEXT_SHOPS_430);
			} else {
				loc_A = 1;
				u4_puts(/*D_4874*/U4TEXT_SHOPS_433);
				u4_putl((long)D_46D2[loc_B] >> 1, 1, '0');
				u4_puts(/*D_4885*/U4TEXT_SHOPS_435);
				u4_puts(D_1E98[37 + loc_B]);
			}
			u4_puts(/*D_4892*/U4TEXT_SHOPS_438);
			loc_C = AskY_N();
			if(loc_C < 'N')
				break;
			if(loc_C == 'N') {
				u4_puts(/*D_489C*/U4TEXT_SHOPS_443);
			} else {
				Party._weapons[loc_B] -= loc_A;
				clamp(Party._gold, (((long)loc_A * D_46D2[loc_B]) >> 1), 9999); dspl_Gold();
				C_4832();
				u4_puts(/*D_48B4*/U4TEXT_SHOPS_448);
			}
		}
	} while(loc_C == 'Y' || loc_C == 'N');
}

/*SHOP #1 - weapons*/
/*C_D085*/SHP_weapon()
{
	char bp_02;

	Gra_13();
	C_4832();
	D_9142 = D_46F2[Party._loc - 1] - 1;
	u4_puts(/*D_48C7*/U4TEXT_SHOPS_462);
	u4_puts(D_46A2[D_9142]);
	u4_puts(/*D_48D7*/"\n\n");
	u4_puts(D_46AE[D_9142]);
	u4_puts(/*D_48DA*/U4TEXT_SHOPS_466);
	do {
		switch(bp_02 = u_kbread()) {
			case 'B': case 'b': bp_02 = 'b'; break;
			case 'S': case 's': bp_02 = 's'; break;
			case ' ': case '\n': case '\r': case 0x1b:
				bp_02 = 0;
				Gra_CR();
			break;
			default:
				bp_02 = -1;
				sound(1);
		}
	} while(bp_02 == -1);
	if(bp_02) {
		u4_putc(bp_02);
		Gra_CR();
		if(bp_02 == 'b')
			C_CD80();
		else
			C_CEBE();
	}
	C_4649();
	Gra_13();
	dspl_Stats();
	Gra_CR();
	u4_puts(D_46AE[D_9142]);
	u4_puts(/*D_4910*/U4TEXT_SHOPS_493);
}

/*----------------------------------------*/

char *D_4BAE[] = {
	/*D_4928*/U4TEXT_SHOPS_499,
	/*D_4937*/U4TEXT_SHOPS_501,
	/*D_4948*/U4TEXT_SHOPS_502,
	/*D_4958*/U4TEXT_SHOPS_503,
	/*D_4965*/U4TEXT_SHOPS_504
};

char *D_4BB8[] = {
	/*D_4972*/U4TEXT_SHOPS_507,
	/*D_497A*/U4TEXT_SHOPS_508,
	/*D_4982*/U4TEXT_SHOPS_509,
	/*D_4987*/U4TEXT_SHOPS_510,
	/*D_498E*/U4TEXT_SHOPS_511,

	/*D_4994*/U4TEXT_SHOPS_513/*?!?who is that?!?*/
};

unsigned char D_4BC4[][4] = {
	{1, 2, 3, 0},
	{3, 4, 5, 6},
	{1, 3, 5, 0},
	{1, 2, 0, 0},
	{1, 2, 3, 0},

	{0, 0, 0, 0}
};

/*prices[armour]*/
int D_4BDC[] = {
	   0,
	  50,
	 200,
	 600,
	2000,
	4000,
	7000,

	9000/*what is this price for?*/
};

/*shops indexes*/
unsigned char D_4BEC[16] = {0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 4, 5, 0, 0};

char *D_4BFC[] = {
	/*D_499D*/U4TEXT_SHOPS_543,
	/*D_49DE*/U4TEXT_SHOPS_544,
	/*D_4A2C*/U4TEXT_SHOPS_545,
	/*D_4A7F*/U4TEXT_SHOPS_546,
	/*D_4ACF*/U4TEXT_SHOPS_547,
	/*D_4B12*/U4TEXT_SHOPS_548
};

/*finalize deal[armor]*/
C_D16D(bp06, bp04)
int bp06;
int bp04;
{
	if(D_4BDC[bp06] * bp04 > Party._gold) {
		u4_puts(/*D_4B63*/U4TEXT_SHOPS_557);
		return;
	}
	Party._gold -= D_4BDC[bp06] * bp04; dspl_Gold();
	Party._armors[bp06] += bp04;
	if(Party._armors[bp06] > 99)
		Party._armors[bp06] = 99;
	C_48F8();
	Gra_CR();
	u4_puts(D_4BB8[D_9142]);
	u4_puts(/*D_4B99*/U4TEXT_SHOPS_567);
}

/*choose item[armor]*/
C_D1D0()
{
	int loc_A, loc_B, loc_C;


	u4_puts(/*D_4C08*/U4TEXT_SHOPS_576);
	do {
		u4_puts(/*D_4C17*/U4TEXT_SHOPS_578);
		for(loc_B = 0; loc_B < 4; loc_B ++) {
			if(D_4BC4[D_9142][loc_B]) {
				u4_putc(D_4BC4[D_9142][loc_B] + 'A');
				u4_putc(' ');
				u4_puts(D_1E98[53 + D_4BC4[D_9142][loc_B]]);
				Gra_CR();
			}
		}
		Gra_CR();
		do {
			loc_C = AskLetter(/*D_4C23*/U4TEXT_SHOPS_589, 'B', 'G');
			loc_C -= 'A';
			if(loc_C <= 0)
				break;
			for(loc_B = 0; loc_B < 4; loc_B ++) {
				if(D_4BC4[D_9142][loc_B] == loc_C)
					break;
			}
			if(loc_B == 4)
				sound(1);
		} while(loc_B == 4);
		if(loc_C < 0)
			break;
		if(D_4BDC[loc_C] > Party._gold) {
			u4_puts(/*D_4C35*/U4TEXT_SHOPS_603);
		} else {
			Gra_CR();
			u4_puts(D_4BFC[loc_C-1]);
			Gra_CR();
			u4_puts(/*D_4C5D*/U4TEXT_SHOPS_608);
			loc_A = AskInt(2);
			if(loc_A <= 0) {

				u4_puts(/*D_4C7B*/U4TEXT_SHOPS_612);


			} else {
				C_D16D(loc_C, loc_A);
			}
		}
		u4_puts(/*D_4C86*/U4TEXT_SHOPS_619);
		loc_C = (char)AskY_N();
	} while(loc_C == 'Y');

}

/*sell item[armor]*/
C_D2F8()
{
	int loc_A, loc_B;
	char loc_C;

	u4_puts(/*D_4C99*/U4TEXT_SHOPS_631);
	loc_B = -1;
	do {
		u4_SetTextCoordYX(23, 24);
		loc_B = AskLetter(/*D_4CA5*/U4TEXT_SHOPS_635, 'B', 'H');
		loc_B -= 'A';
		Gra_CR();
		if(loc_B <= 0)
			break;
		if(Party._armors[loc_B] == 0) {
			u4_puts(/*D_4CB2*/U4TEXT_SHOPS_641);
		} else {
			if(Party._armors[loc_B] > 1) {
				u4_puts(/*D_4CCF*/U4TEXT_SHOPS_644);
				u4_puts(D_1E98[53 + loc_B]);
				u4_puts(/*D_4CD9*/U4TEXT_SHOPS_646);
				loc_A = AskInt(2);
				if(loc_A <= 0) {

					u4_puts(/*D_4CF8*/U4TEXT_SHOPS_650);


					break;
				}
				if(Party._armors[loc_B] < loc_A) {
					u4_puts(/*D_4D03*/U4TEXT_SHOPS_656);
					break;
				}
				u4_puts(/*D_4D24*/U4TEXT_SHOPS_659);
				u4_putl(((long)loc_A * D_4BDC[loc_B]) >> 1, 1, '0');
				u4_puts(/*D_4D32*/U4TEXT_SHOPS_661);
				if(loc_A > 1)
					u4_puts(/*D_4D3A*/U4TEXT_SHOPS_663);
				else
					u4_puts(/*D_4D40*/U4TEXT_SHOPS_665);
			} else {
				loc_A = 1;
				u4_puts(/*D_4D44*/U4TEXT_SHOPS_668);
				u4_putl((long)D_4BDC[loc_B] >> 1, 1, '0');
				u4_puts(/*D_4D55*/U4TEXT_SHOPS_670);
				u4_puts(D_1E98[53 + loc_B]);
			}
			u4_puts(/*D_4D62*/U4TEXT_SHOPS_673);
			loc_C = AskY_N();
			if(loc_C < 'N')
				break;
			if(loc_C == 'N') {
				u4_puts(/*D_4D6C*/U4TEXT_SHOPS_678);
			} else {
				Party._armors[loc_B] -= loc_A;
				clamp(Party._gold, (((long)loc_A * D_4BDC[loc_B]) >> 1), 9999); dspl_Gold();
				C_48F8();
				u4_puts(/*D_4D86*/U4TEXT_SHOPS_683);
			}
		}
	} while(loc_C == 'Y' || loc_C == 'N');
}

/*SHOP #2 - armor*/
/*C_D4AE*/SHP_armor()
{
	char bp_02;

	Gra_13();
	C_48F8();
	D_9142 = D_4BEC[Party._loc - 1] - 1;
	u4_puts(/*D_4D99*/U4TEXT_SHOPS_697);
	u4_puts(D_4BAE[D_9142]);
	u4_puts(/*D_4DA9*/"\n\n");
	u4_puts(D_4BB8[D_9142]);
	u4_puts(/*D_4DAC*/U4TEXT_SHOPS_701);
	do {
		switch(bp_02 = u_kbread()) {
			case 'B': case 'b': bp_02 = 'b'; break;
			case 'S': case 's': bp_02 = 's'; break;
			case ' ': case '\n': case '\r': case 0x1b:
				bp_02 = 0;
				Gra_CR();
			break;
			default:
				bp_02 = -1;
				sound(1);
		}
	} while(bp_02 == -1);
	if(bp_02) {
		u4_putc(bp_02);
		Gra_CR();
		if(bp_02 == 'b')
			C_D1D0();
		else
			C_D2F8();
	}
	C_4649();
	Gra_13();
	dspl_Stats();
	Gra_CR();
	u4_puts(D_4BB8[D_9142]);
	u4_puts(/*D_4DD9*/U4TEXT_SHOPS_728);/*TODO:0 is for padding*/
}

/*----------------------------------------*/

/*SHOP #9 - horses*/
/*C_D596*/SHP_horse()
{
	char bp_02;

	u4_puts(/*D_4DEC*/U4TEXT_SHOPS_738);
	bp_02 = AskY_N();
	if(bp_02 != 'Y') {
		if(bp_02 == 'N')
			u4_puts(/*D_4E1F*/U4TEXT_SHOPS_742);
		return;
	}
	u4_puts(/*D_4E57*/U4TEXT_SHOPS_745);
	u4_putl(Party.f_1d8, 1, '0');
	u4_puts(/*D_4E62*/U4TEXT_SHOPS_747);
	bp_02 = AskY_N();
	if(bp_02 != 'Y') {
		if(bp_02 == 'N')
			u4_puts(/*D_4E94*/U4TEXT_SHOPS_751);
		return;
	}
	if(100 * Party.f_1d8 > Party._gold) {
		u4_puts(/*D_4ECC*/U4TEXT_SHOPS_755);
		return;
	}
	Party._gold -= 100 * Party.f_1d8; dspl_Gold();
	u4_puts(/*D_4EF9*/U4TEXT_SHOPS_759);
	Party._tile  = TIL_14;
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_5196[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0};

/*items prices*/
int D_51A6[] = {50, 60, 60, 900};
/*items quantities*/
int D_51AE[] = { 5,  5,  6,   1};

char *D_51B6[] = {
	/*D_4F2A*/U4TEXT_SHOPS_774,
	/*D_4F39*/U4TEXT_SHOPS_775
};
char *D_51BA[] = {
	/*D_4F48*/U4TEXT_SHOPS_778,
	/*D_4F58*/U4TEXT_SHOPS_779
};

char *D_51BE[] = {
	/*D_4F68*/U4TEXT_SHOPS_783,
	/*D_4F9F*/U4TEXT_SHOPS_784,
	/*D_4FD0*/U4TEXT_SHOPS_785,
	/*D_5006*/U4TEXT_SHOPS_786
};

/*SHOP #8 - guild*/
/*C_D61E*/SHP_guild()
{
	int loc_A;
	char loc_B;
	U16 *loc_C;

	D_9142 = D_5196[Party._loc - 1] - 1;
	Gra_13();
	C_4987();
	u4_puts(/*D_5056*/U4TEXT_SHOPS_799);
	u4_puts(D_51BA[D_9142]);
	u4_puts(/*D_508A*/U4TEXT_SHOPS_801);
	u4_puts(D_51BA[D_9142]);
	u4_puts(/*D_508F*/U4TEXT_SHOPS_803);
	u4_puts(D_51B6[D_9142]);
	u4_puts(/*D_50A2*/U4TEXT_SHOPS_805);
	while((loc_B = AskY_N()) == 'Y') {
		Gra_CR();
		u4_puts(D_51BA[D_9142]);
		u4_puts(/*D_50BC*/U4TEXT_SHOPS_809);
		loc_A = AskLetter(/*D_5102*/U4TEXT_SHOPS_813, 'A', 'D') - 'A';
		if(loc_A < 0)
			break;
		Gra_CR();
		u4_puts(D_51BE[loc_A]);
		u4_puts(/*D_5112*/U4TEXT_SHOPS_818);
		loc_B = AskY_N();
		if(loc_B != 'Y') {
			if(loc_B == 'N')
				u4_puts(/*D_5123*/U4TEXT_SHOPS_822);
			break;
		}
		if(Party._gold < D_51A6[loc_A]) {
			Gra_13();
			C_4649();
			dspl_Stats();
			u4_puts(/*D_5135*/U4TEXT_SHOPS_829);
			return;
		}
		switch(loc_A) {
			case 0: loc_C = &(Party._torches); break;
			case 1: loc_C = &(Party._gems); break;
			case 2: loc_C = &(Party._keys); break;
			case 3: loc_C = &(Party._sextants); break;
		}
		*loc_C += D_51AE[loc_A];
		if(*loc_C > 99)
			*loc_C = 99;
		Party._gold -= D_51A6[loc_A];
		u4_puts(/*D_5158*/U4TEXT_SHOPS_842);
		dspl_Gold();
		C_4987();
		Gra_CR();
		u4_puts(D_51BA[D_9142]);
		u4_puts(/*D_516A*/U4TEXT_SHOPS_847);
	}
	Gra_13();
	C_4649();
	dspl_Stats();
	Gra_CR();
	u4_puts(D_51BA[D_9142]);
	u4_puts(/*D_517E*/U4TEXT_SHOPS_854);
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_5484[16] = {0, 0, 0, 0, 1, 2, 3, 0, 4, 5, 6, 0, 0, 0, 7, 0};

unsigned char D_5494[] = {0x1C, 0x1D, 0x0A, 0x02, 0x1D, 0x1C, 0x19, 0};
unsigned char D_549C[] = {0x06, 0x06, 0x1A, 0x06, 0x02, 0x0B, 0x17, 0};
unsigned char D_54A4[] = {  20,   15,   10,   30,   15,    5,    1, 0};

char *D_54AC[] = {
	/*D_51C6*/U4TEXT_SHOPS_867,
	/*D_51D5*/U4TEXT_SHOPS_868,
	/*D_51E5*/U4TEXT_SHOPS_869,
	/*D_51F5*/U4TEXT_SHOPS_870,
	/*D_5204*/U4TEXT_SHOPS_871,
	/*D_5212*/U4TEXT_SHOPS_872,
	/*D_5229*/U4TEXT_SHOPS_873
};

char *D_54BA[] = {
	/*D_5238*/U4TEXT_SHOPS_877,
	/*D_523E*/U4TEXT_SHOPS_878,
	/*D_5244*/U4TEXT_SHOPS_879,
	/*D_524A*/U4TEXT_SHOPS_880,
	/*D_5250*/U4TEXT_SHOPS_881,
	/*D_5256*/U4TEXT_SHOPS_882,
	/*D_525D*/U4TEXT_SHOPS_883
};

char *D_54C8[] = {
	/*D_5263*/U4TEXT_SHOPS_887,
	/*D_5293*/U4TEXT_SHOPS_888,
	/*D_52C4*/U4TEXT_SHOPS_889,
	/*D_5302*/U4TEXT_SHOPS_890,
	/*D_5351*/U4TEXT_SHOPS_891,
	/*D_5385*/U4TEXT_SHOPS_892,
	/*D_5402*/U4TEXT_SHOPS_893
};

C_D7A8()
{
	int bp_02;

	u4_puts(/*D_544B*/U4TEXT_SHOPS_900);
	bp_02 = CurMode;
	CurMode = MOD_COM_CAMP;
	D_96F8 = D_9452 = TIL_C8;
	C_7D92();
	CurMode = bp_02;
}

C_D7D6()
{
	int bp_02;

	u_delay(1, 0);
	Party._x = D_913B;
	Party._y = D_913C;
	u_delay(1, 0);
	for(bp_02 = Party.f_1d8 - 1; bp_02 >= 0; bp_02 --) {
		if(isCharaAlive(bp_02))
			Party.chara[bp_02]._stat = 'S';
	}
	dspl_Stats();
	Party._tile = TIL_38;
	u_delay(5, 0);
	Party._tile = TIL_1F;
	for(bp_02 = Party.f_1d8 - 1; bp_02 >= 0; bp_02 --) {
		if(Party.chara[bp_02]._stat == 'S') {
			Party.chara[bp_02]._stat = 'G';
			HP_inc(bp_02, U4_RND3(50) * 2 + 100);
		}
	}
	MP_recover();
	dspl_Stats();
	if(isCharaAlive(0) && U4_RND1(7) == 0) {
		C_D7A8();
	} else if(D_9142 == 5 && U4_RND1(3) == 0) {
		/*Isaac the ghost appears in skara brae*/
		D_8742._npc._tile[0] = D_8742._npc._gtile[0] = TIL_9C;
		D_8742._npc._x[0] = Party._x - 1;
		D_8742._npc._y[0] = Party._y;
		D_8742._npc._var[0] = 1;
		D_8742._npc._tlkidx[0] = 0x10;
	}
	u4_puts(/*D_54D6*/U4TEXT_SHOPS_942);
}

unsigned char D_5672[] = { 2, 2, 8, 0};
unsigned char D_5676[] = { 6, 2, 2, 0};
unsigned char D_567A[] = {30,60,90, 0};

/*SHOP #7 - inn*/
/*C_D8DD*/SHP_inn()
{
	int bp_02;
	char bp_04;

	if(Party._tile != TIL_1F) {
		u4_puts(/*D_54E1*/U4TEXT_SHOPS_956);
		return;
	}
	u4_puts(/*D_5514*/U4TEXT_SHOPS_959);
	D_9142 = D_5484[Party._loc - 1] - 1;
	u4_puts(D_54AC[D_9142]);
	u4_puts(/*D_5534*/U4TEXT_SHOPS_962);
	u4_puts(D_54BA[D_9142]);
	u4_puts(/*D_553C*/U4TEXT_SHOPS_964);
	bp_04 = AskY_N();
	if(bp_04 == 'Y') {
		Gra_CR();
		u4_puts(D_54C8[D_9142]);
		Gra_CR();
		if(D_9142 == 3) {
			bp_02 = AskLetter(/*D_555E*/U4TEXT_SHOPS_971, '1', '3');
			bp_02 -= '1';
			if(bp_02 < 0)
				return;
			D_913B = D_5672[bp_02];
			D_913C = D_5676[bp_02];
			D_913A = D_567A[bp_02];
		} else {
			u4_puts(/*D_5571*/U4TEXT_SHOPS_979);
			bp_04 = AskY_N();
			if(bp_04 != 'Y') {
				if(bp_04 == 'N')
					u4_puts(/*D_557E*/U4TEXT_SHOPS_983);
				return;
			}
			D_913B = D_5494[D_9142];
			D_913C = D_549C[D_9142];
			D_913A = D_54A4[D_9142];
		}
		if(D_913A > Party._gold) {
			u4_puts(/*D_55AC*/U4TEXT_SHOPS_991);
			return;
		}
		Party._gold -= D_913A; dspl_Gold();
		u4_puts(/*D_55DA*/U4TEXT_SHOPS_995);
		if(U4_RND1(3) == 0)
			u4_puts(/*D_5600*/U4TEXT_SHOPS_997);
		C_D7D6();
	} else  {
		Gra_CR();
		u4_puts(D_54BA[D_9142]);
		u4_puts(/*D_5639*/U4TEXT_SHOPS_1002);
	}
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_5788[16] = {1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 9, 0, 0, 0, 0, 10};

char *D_5798[] = {
	/*D_567E*/U4TEXT_SHOPS_1012,
	/*D_568F*/U4TEXT_SHOPS_1013,
	/*D_56A0*/U4TEXT_SHOPS_1014,
	/*D_56B0*/U4TEXT_SHOPS_1015,
	/*D_56BF*/U4TEXT_SHOPS_1016,
	/*D_56CA*/U4TEXT_SHOPS_1017,
	/*D_56D8*/U4TEXT_SHOPS_1018,
	/*D_56E8*/U4TEXT_SHOPS_1019,
	/*D_56F5*/U4TEXT_SHOPS_1020,
	/*D_5705*/U4TEXT_SHOPS_1021
};

char *D_57AC[] = {
	/*D_5715*/U4TEXT_SHOPS_1025,
	/*D_571F*/U4TEXT_SHOPS_1026,
	/*D_5728*/U4TEXT_SHOPS_1027,
	/*D_572F*/U4TEXT_SHOPS_1028,
	/*D_573A*/U4TEXT_SHOPS_1029,
	/*D_5742*/U4TEXT_SHOPS_1030,
	/*D_5749*/U4TEXT_SHOPS_1031,
	/*D_5751*/U4TEXT_SHOPS_1032,
	/*D_5758*/U4TEXT_SHOPS_1033,
	/*D_575F*/U4TEXT_SHOPS_1034
};

C_DA05()
{
	register int si;

	Gra_CR();
	u4_puts(D_57AC[D_9142]);
	u4_puts(/*D_5764*/U4TEXT_SHOPS_1043);
	si = AskChara(/*D_576C*/U4TEXT_SHOPS_1044);
	if(si < 0)
		u4_puts(/*D_577F*/U4TEXT_SHOPS_1046);
	return si;
}

C_DA3E(bp04)
int bp04;
{
	char bp_02;

	u4_puts(/*D_57C0*/U4TEXT_SHOPS_1055);
	bp_02 = AskY_N();
	if(bp_02 == 'Y') {
		Party._gold -= bp04; dspl_Gold();
		return 1;
	}
	if(bp_02 == 'N')
		u4_puts(/*D_57D3*/U4TEXT_SHOPS_1062);

	return 0;
}

C_DA79(bp04)
int bp04;
{
	Gra_09();
	Gra_11(bp04);
	sound(9, 0xc0);
	Gra_11(bp04);
	Gra_09();
}

/*Curing*/
C_DAA2()
{
	int bp_02;

	bp_02 = C_DA05();
	if(bp_02 == -1)
		return;
	if(Party.chara[bp_02]._stat != 'P') {
		u4_puts(/*D_57ED*/U4TEXT_SHOPS_1086);
		return;
	}
	u4_puts(/*D_580C*/U4TEXT_SHOPS_1089);
	if(Party._gold < 100) {
		u4_puts(/*D_582C*/U4TEXT_SHOPS_1091);
		u_kbflush();
		u_delay(5, 1);
		if(u_kbhit())
			u_kbread();
		u4_puts(/*D_5860*/U4TEXT_SHOPS_1096);
	} else {
		if(!C_DA3E(100))
			return;
	}
	Party.chara[bp_02]._stat = 'G';
	C_DA79(bp_02);
	dspl_Stats();
}

/*Healing*/
C_DB29()
{
	int bp_02;

	bp_02 = C_DA05();
	if(bp_02 == -1)
		return;
	if(Party.chara[bp_02]._HP[0] == Party.chara[bp_02]._HP[1]) {
		u4_puts(/*D_58A6*/U4TEXT_SHOPS_1115);
		return;
	}
	u4_puts(/*D_58C7*/U4TEXT_SHOPS_1118);
	if(Party._gold < 200) {
		u4_puts(/*D_58E9*/U4TEXT_SHOPS_1120);
		return;
	}
	if(C_DA3E(200)) {
		Party.chara[bp_02]._HP[0] = Party.chara[bp_02]._HP[1];
		C_DA79(bp_02);
		dspl_Stats();
	}
}

/*Resurrection*/
C_DB93()
{
	int bp_02;

	bp_02 = C_DA05();
	if(bp_02 == -1)
		return;
	if(Party.chara[bp_02]._stat != 'D') {
		u4_puts(/*D_5931*/U4TEXT_SHOPS_1139);
		return;
	}
	u4_puts(/*D_594A*/U4TEXT_SHOPS_1142);
	if(Party._gold < 300) {
		u4_puts(/*D_596E*/U4TEXT_SHOPS_1144);
		return;
	}
	if(C_DA3E(300)) {
		Party.chara[bp_02]._stat = 'G';
		C_DA79(bp_02);
		dspl_Stats();
	}
}

/*blood donation*/
C_DBF5()
{
	char bp_04;
	int dummy;

	u4_puts(/*D_59B6*/U4TEXT_SHOPS_1160);
	bp_04 = AskY_N();
	if(bp_04 == 'Y') {
		karma_inc(&(Party._sacri), 5);
		u4_puts(/*D_59F5*/U4TEXT_SHOPS_1164);
		Party.chara[0]._HP[0] -= 100;
		dspl_Stats();
		u_delay(1, 0);
	} else if(bp_04 == 'N') {
		karma_dec(&(Party._sacri), 5);
		dspl_Stats();
	}
}

/*SHOP #6 - healer*/
/*C_DC4D*/SHP_healer()
{
	int bp_02;
	char bp_04;

	D_9142 = D_5788[Party._loc - 1] - 1;
	u4_puts(/*D_5A23*/U4TEXT_SHOPS_1181);
	u4_puts(D_5798[D_9142]);
	Gra_CR();
	u4_puts(D_57AC[D_9142]);
	u4_puts(/*D_5A31*/U4TEXT_SHOPS_1185);
	while((bp_04 = AskY_N()) == 'Y') {
		Gra_CR();
		u4_puts(D_57AC[D_9142]);
		u4_puts(/*D_5A76*/U4TEXT_SHOPS_1189);
		bp_02 = AskLetter(/*D_5AB0*/U4TEXT_SHOPS_1193, 'A', 'C');
		if(bp_02 < 'A')
			break;
		switch((char)bp_02) {
			case 'A': C_DAA2(); break;
			case 'B': C_DB29(); break;
			case 'C': C_DB93(); break;
		}
		Gra_CR();
		u4_puts(D_57AC[D_9142]);
		u4_puts(/*D_5ABE*/U4TEXT_SHOPS_1203);
	}
	if(Party.chara[0]._HP[0] >= 400)
		C_DBF5();
	dspl_Stats();
	Gra_CR();
	u4_puts(D_57AC[D_9142]);
	u4_puts(/*D_5ADF*/U4TEXT_SHOPS_1210);
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_5EE8[16] = {0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 4, 5, 6, 0};

int D_5EF8[] = {20, 30, 10, 40, 99, 25};

char *D_5F04[] = {
	/*D_5B16*/U4TEXT_SHOPS_1221,
	/*D_5B24*/U4TEXT_SHOPS_1222,
	/*D_5B33*/U4TEXT_SHOPS_1223,
	/*D_5B3F*/U4TEXT_SHOPS_1224,
	/*D_5B4D*/U4TEXT_SHOPS_1225,
	/*D_5B62*/U4TEXT_SHOPS_1226
};

char *D_5F10[] = {
	/*D_5B6D*/U4TEXT_SHOPS_1230,
	/*D_5B71*/U4TEXT_SHOPS_1231,
	/*D_5B7B*/U4TEXT_SHOPS_1232,
	/*D_5B82*/U4TEXT_SHOPS_1233,
	/*D_5B8E*/U4TEXT_SHOPS_1234,
	/*D_5B98*/U4TEXT_SHOPS_1235
};

char *D_5F1C[] = {
	/*D_5B9E*/U4TEXT_SHOPS_1239,
	/*D_5BA9*/U4TEXT_SHOPS_1240,
	/*D_5BB7*/U4TEXT_SHOPS_1241,
	/*D_5BC3*/U4TEXT_SHOPS_1242,
	/*D_5BD0*/U4TEXT_SHOPS_1243,
	/*D_5BDD*/U4TEXT_SHOPS_1244
};

int D_5F28[] = {4,2,3,2,4,2};

char *D_5F34[] = {
	/*D_5BEC*/U4TEXT_SHOPS_1250,
	/*D_5BF8*/U4TEXT_SHOPS_1251,
	/*D_5C00*/U4TEXT_SHOPS_1252,
	/*D_5C0C*/U4TEXT_SHOPS_1253,
	/*D_5C15*/U4TEXT_SHOPS_1254,
	/*D_5C1B*/U4TEXT_SHOPS_1255,
	/*D_5C26*/U4TEXT_SHOPS_1256
};

char *D_5F42[] = {
	/*D_5C34*/U4TEXT_SHOPS_1260,
	/*D_5CA1*/U4TEXT_SHOPS_1261,
	/*D_5CED*/U4TEXT_SHOPS_1262,
	/*D_5D5F*/U4TEXT_SHOPS_1263,
	/*D_5DB1*/U4TEXT_SHOPS_1264,
	/*D_5E12*/U4TEXT_SHOPS_1265
};

/*pub food*/
C_DD24()
{
	int bp_02, bp_04;

	u4_puts(/*D_5E68*/U4TEXT_SHOPS_1273);
	u4_puts(D_5F1C[D_9142]);
	u4_puts(/*D_5E7A*/U4TEXT_SHOPS_1275);
	u4_putl(D_5F28[D_9142], 1, '0');
	u4_puts(/*D_5E89*/U4TEXT_SHOPS_1277);
	bp_02 = AskInt(2);
	if(bp_02 <= 0) {
		if(bp_02 < 0)
			sound(1);
		return 1;
	}
	bp_04 = 0;
	while(bp_02) {
		if(Party._gold >= D_5F28[D_9142]) {
			Party._gold -= D_5F28[D_9142];
			Party._food = (Party._food + 100 > 999900L)?999900L:(Party._food + 100);
			dspl_Stats();
			bp_02 --;
			bp_04 ++;
		} else {
			if(bp_04 == 0) {
				u4_puts(/*D_5EB3*/U4TEXT_SHOPS_1294);
				return 1;
			}
			u4_puts(/*D_5ECB*/U4TEXT_SHOPS_1297);
			u4_putl(bp_04, 1, '0');
			u4_puts(/*D_5EE0*/U4TEXT_SHOPS_1299);
			if(bp_04 != 1)
				u4_putc('s'); 
			u4_putc('.');
			Gra_CR();
			break;
		}
	}

	return 0;
}

/*pub ale*/
C_DE35()
{
	int loc_A;
	char loc_B;
	int loc_C;
	char loc_D[16];
	int loc_E;

	if(D_913E == 3) {
		Gra_CR();
		u4_puts(D_5F10[D_9142]);
		u4_puts(/*D_5F4E*/U4TEXT_SHOPS_1323);
		return 1;
	}
	D_913E ++;
	u4_puts(/*D_5F7E*/U4TEXT_SHOPS_1327);
	loc_A = AskInt(2);
	if(loc_A <= 0) {
		if(loc_A < 0)
			sound(1);
		return 1;
	}
	if(loc_A < 2) {
		u4_puts(/*D_5FB7*/U4TEXT_SHOPS_1335);
		return 1;
	}
	if(Party._gold < loc_A) {
		u4_puts(/*D_5FF2*/U4TEXT_SHOPS_1339);
		return 1;
	}
	Party._gold -= loc_A; dspl_Gold();
	if(loc_A >= 3) {
		u4_puts(/*D_6023*/U4TEXT_SHOPS_1344);
		u4_gets(loc_D, 15);
		for(loc_C = 6; loc_C >= 0; loc_C --) {
			if(strnicmp(loc_D, D_5F34[loc_C], 16) == 0)
			break;
		}
		if(loc_C == 6)
			loc_C = 3;
		if(loc_C < D_9142) {
			u4_puts(/*D_6044*/U4TEXT_SHOPS_1353);
		} else {
			while(D_5EF8[loc_C] > loc_A) {
				u4_puts(/*D_606B*/U4TEXT_SHOPS_1356);
				loc_E = AskInt(2);
				if(loc_E <= 0) {
					if(loc_A < 0)
						sound(1);
					else
						u4_puts(/*D_60C2*/U4TEXT_SHOPS_1362);
					return 1;
				}
				if(Party._gold < loc_E) {
					u4_puts(/*D_60E4*/U4TEXT_SHOPS_1366);
					u4_puts(/*D_6100*/U4TEXT_SHOPS_1367);
					return 1;
				}
				Party._gold -= loc_E; dspl_Gold();
				loc_A += loc_E;
			}
			if(D_5EF8[loc_C] <= loc_A) {
				Gra_CR();
				u4_puts(D_5F10[D_9142]);
				u4_puts(/*D_6122*/U4TEXT_SHOPS_1376);
				u4_puts(D_5F42[loc_C]);
				Gra_CR();
			}
		}
	}
	u4_puts(/*D_612A*/U4TEXT_SHOPS_1382);
	loc_B = AskY_N();
	if(loc_B != 'Y')
		return 1;
	return 0;
}

/*SHOP #4 - pub*/
/*C_DFAF*/SHP_pub()
{
	char bp_02;

	D_913E = 0;
	D_9142 = D_5EE8[Party._loc - 1] - 1;
	Gra_CR();
	u4_puts(D_5F10[D_9142]);
	u4_puts(/*D_613D*/U4TEXT_SHOPS_1398);
	u4_puts(D_5F04[D_9142]);
	Gra_CR();
	do {
		u4_puts(D_5F10[D_9142]);
		u4_puts(/*D_6150*/U4TEXT_SHOPS_1403);
		{
C_E004:
			bp_02 = u_kbread();
			u4_toupper(bp_02);
			if(bp_02 == ' ' || bp_02 == 0x1b || bp_02 == '\r') {
				Gra_CR();
				return;
			}
			if(bp_02 != 'F' && bp_02 != 'A') {
				sound(1);
				goto C_E004;
			}
		}
		u4_putc(bp_02);
		Gra_CR();
		if(bp_02 == 'F') {
			if(C_DD24())
				break;
		} else {
			if(C_DE35())
				break;
		}
		dspl_Stats();
		u4_puts(/*D_6176*/U4TEXT_SHOPS_1427);
		bp_02 = AskY_N();
	} while(bp_02 == 'Y');
	u4_puts(/*D_6196*/U4TEXT_SHOPS_1430);
}

/*----------------------------------------*/

/*shops indexes*/
unsigned char D_636C[16] = {0, 0, 0, 0, 1, 2, 0, 3, 0, 0, 4, 0, 5, 0, 0, 0};

int D_637C[] = {25, 40, 35, 20, 30};

char *D_6386[] = {
	/*D_61A4*/U4TEXT_SHOPS_1441,
	/*D_61B2*/U4TEXT_SHOPS_1442,
	/*D_61C1*/U4TEXT_SHOPS_1443,
	/*D_61CF*/U4TEXT_SHOPS_1444,
	/*D_61E0*/U4TEXT_SHOPS_1445
};

char *D_6390[] = {
	/*D_61EB*/U4TEXT_SHOPS_1449,
	/*D_61F2*/U4TEXT_SHOPS_1450,
	/*D_61FB*/U4TEXT_SHOPS_1451,
	/*D_6102*/U4TEXT_SHOPS_1452,
	/*D_6109*/U4TEXT_SHOPS_1453
};

/*SHOP #3 - food*/
/*C_E088*/SHP_food()
{
	char bp_02;
	char bp_04;

	D_9142 = D_636C[Party._loc - 1] - 1;
	u4_puts(/*D_620D*/U4TEXT_SHOPS_1463);
	u4_puts(D_6386[D_9142]);
	u4_puts(/*D_621D*/"\n\n");
	u4_puts(D_6390[D_9142]);
	u4_puts(/*D_6220*/U4TEXT_SHOPS_1467);
	bp_04 = AskY_N();
	if(bp_04 != 'Y') {
		if(bp_04 == 'N')
			u4_puts(/*D_626D*/U4TEXT_SHOPS_1471);
		return;
	}
	u4_puts(/*D_6283*/U4TEXT_SHOPS_1474);
	u4_putl(D_637C[D_9142], 1, '0');
	u4_puts(/*D_62B4*/U4TEXT_SHOPS_1476);
	do {
		u4_puts(/*D_62B8*/U4TEXT_SHOPS_1478);
		bp_02 = AskInt(3);
		if(bp_02 <= 0) {
			u4_puts(/*D_62E5*/U4TEXT_SHOPS_1481);
			bp_04 = 'N';
			continue;
		}
		if(D_637C[D_9142] * bp_02 > Party._gold) {
			if(D_637C[D_9142] > Party._gold) {
				u4_puts(/*D_6301*/U4TEXT_SHOPS_1487);
				break;
			}
			u4_puts(/*D_6319*/U4TEXT_SHOPS_1490);
			u4_putl((long)Party._gold / (long)D_637C[D_9142], 1, '0');
			u4_puts(/*D_632E*/U4TEXT_SHOPS_1492);
			bp_04 = 'Y';
			continue;
		}
		Party._food += 2500L * bp_02;
		if(Party._food > 999900L)
			Party._food = 999900L;
		Party._gold -= D_637C[D_9142] * bp_02;
		dspl_Stats();
		u4_puts(/*D_6337*/U4TEXT_SHOPS_1501);
		bp_04 = AskY_N();
	} while(bp_04 == 'Y');
	u4_puts(/*D_6355*/U4TEXT_SHOPS_1504);
}
