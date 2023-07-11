/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

/*----------------------------------------
LOCATE
----------------------------------------*/

/*C_755E*/CMD_Locate()
{
	if(Party._sextants == 0) {
		u4_puts_with_kbflush(U4TEXT_K_LOCAT_WHAT);
		return;
	}
	u4_puts(U4TEXT_K_LOCAT_WITH_SEXTANT);
	u4_puts(U4TEXT_K_LOCAT_LATITUDE);
	u4_putc((Party._y >> 4) + 'A');
	u4_putc('\'');
	u4_putc((Party._y & 0xf) + 'A');
	u4_puts(/*D_2314*/U4TEXT_LOCAT_24);
	u4_putc((Party._x >> 4) + 'A');
	u4_putc('\'');
	u4_putc((Party._x & 0xf) + 'A');
	u4_putc('"');
	Gra_CR();
}

/*----------------------------------------

----------------------------------------*/

unsigned char D_2334[] = {
	/*weapons class masks*/
	0xFF,0xFF,0xFF,0xFF,0x7F,0x6F,0x6F,0x7E,0x7E,0xFF,0x2C,0x0C,0x2E,0x5E,0xD0,0xFF,
	/*D_2344*//*armor class masks*/
	0xFF,0xFF,0x7F,0x2C,0x2C,0x24,0x04,0xFF
};

/*"may not use"*/
C_75DC(bp08, bp06, bp04)
int bp08;
int bp06;
int bp04;
{
	u4_puts(/*D_2322*/U4TEXT_LOCAT_49);
	u4_puts(Strings[77 + (int)Party.chara[bp08]._class]);
	u4_puts(/*D_2326*/U4TEXT_LOCAT_51);
	if(bp04)
		u4_putc('a');
	Gra_CR();
	u4_puts(Strings[37 + bp06]);
	Gra_CR();
	sound(1);
}

/*C_7631*/CMD_Ready()
{
	register int loc_A, loc_B;
	int loc_C;

	if(CurMode >= MOD_COMBAT) {
		u4_puts(/*D_234C*/U4TEXT_LOCAT_66);
		loc_A = activeChara;
	} else {
		u4_puts(/*D_235B*/U4TEXT_LOCAT_69);
		if((loc_A = AskChara(/*D_236B*/U4TEXT_LOCAT_70)) < 0)
			return;
	}
	Gra_13();
	C_4832();
	u4_SetTextCoordYX(23, 24);
	loc_B = AskLetter(/*D_2373*/U4TEXT_LOCAT_76, 'A', 'P');
	Gra_13();
	C_4649();
	dspl_Stats();
	if(CurMode >= MOD_COMBAT)
		Gra_11(activeChara);
	if(loc_B < 0)
		return;
	loc_B -= 'A';
	if(loc_B != 0 && Party._weapons[loc_B] == 0) {
		w_NoneLeft();
		return;
	}
	if(loc_B != 0) {
		if(((0x80 >> Party.chara[loc_A]._class) & D_2334[loc_B]) == 0) {
			C_75DC(loc_A, loc_B, 1);
			return;
		}
	}
	if((loc_C = Party.chara[loc_A]._weapon) != 0) {
		if(++Party._weapons[loc_C] > 99)
			Party._weapons[loc_C] = 99;
	}
	if(loc_B != 0) 
		Party._weapons[loc_B] --;
	Party.chara[loc_A]._weapon = loc_B;
	u4_puts(Strings[37 + loc_B]);
	Gra_CR();
}

/*C_7732*/CMD_Wear()
{
	register int loc_A, loc_B;
	int loc_C;

	u4_puts(/*D_237E*/U4TEXT_LOCAT_111);
	if((loc_A = AskChara(/*D_238B*/U4TEXT_LOCAT_112)) < 0)
		return;
	Gra_13();
	C_48F8();
	u4_SetTextCoordYX(23, 24);
	loc_B = AskLetter(/*D_2393*/U4TEXT_LOCAT_117, 'A', 'H');
	Gra_13();
	C_4649();
	dspl_Stats();
	if(CurMode >= MOD_COMBAT)
		Gra_11(activeChara);
	if(loc_B < 0)
		return;
	loc_B -= 'A';
	if(loc_B != 0 && Party._armors[loc_B] == 0) {
		w_NoneLeft();
		return;
	}
	if(loc_B != 0) {
		if(((0x80 >> Party.chara[loc_A]._class) & D_2334[loc_B + 0x10]) == 0) {
			C_75DC(loc_A, loc_B + 0x10, 0);
			return;
		}
	}
	if((loc_C = Party.chara[loc_A]._armor) != 0) {
		if(++Party._armors[loc_C] > 99)
			Party._armors[loc_C] = 99;
	}
	if(loc_B != 0)
		Party._armors[loc_B] --;
	Party.chara[loc_A]._armor = loc_B;
	u4_puts(Strings[53 + loc_B]);
	Gra_CR();
}
