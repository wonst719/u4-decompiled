/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

/*thanks to Fenyx4 for the variable
 name issue fix*/

#include "i18n.h"
#include "title.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*====---- _BSS ----====*/
/*D_6938*/static unsigned static_A;
/*D_693A*/static int static_B;
/*D_693C*/static int static_C;
/*D_693E*/static unsigned char static_D;
/*D_6940*/static void far *static_E;
/*D_6944*/static unsigned char static_F;
/*D_6946*/static unsigned static_G;
/*D_6948*/static char static_H[20];
/*D_695C*/static unsigned char static_I;
/*D_695E*/static unsigned char static_J[8];

#define D_6938 static_A
#define lastVirtue static_B
#define M_or_F static_C
#define tmp_str static_D
#define D_6940 static_E
#define tmp_dex static_F
#define curQuestionIndex static_G
#define player_name static_H
#define tmp_int static_I
#define tmp_karma static_J
/*====---- ----====*/


#if 0
#include "joe.h"
#endif

#define STR(i) (D_2EE6[(i) - 1])

char *D_2EE6[0x43] = {
	U4TEXT_TITLE_1_TEXT_1,
	U4TEXT_TITLE_1_TEXT_2,
	U4TEXT_TITLE_1_TEXT_3,
	U4TEXT_TITLE_1_TEXT_4,
	U4TEXT_TITLE_1_TEXT_5,
	U4TEXT_TITLE_1_TEXT_6,
	U4TEXT_TITLE_1_TEXT_7,
	U4TEXT_TITLE_1_TEXT_8,
	U4TEXT_TITLE_1_TEXT_9,
	U4TEXT_TITLE_1_TEXT_10,
	U4TEXT_TITLE_1_TEXT_11,
	U4TEXT_TITLE_1_TEXT_12,
	U4TEXT_TITLE_1_TEXT_13,
	U4TEXT_TITLE_1_TEXT_14,
	U4TEXT_TITLE_1_TEXT_15,
	U4TEXT_TITLE_1_TEXT_16,
	U4TEXT_TITLE_1_TEXT_17,
	U4TEXT_TITLE_1_TEXT_18,
	U4TEXT_TITLE_1_TEXT_19,
	U4TEXT_TITLE_1_TEXT_20,
	U4TEXT_TITLE_1_TEXT_21,
	U4TEXT_TITLE_1_TEXT_22,
	U4TEXT_TITLE_1_TEXT_23,
	U4TEXT_TITLE_1_TEXT_24,
	U4TEXT_TITLE_1_TEXT_25,
	U4TEXT_TITLE_1_TEXT_26,
	U4TEXT_TITLE_1_TEXT_27,
	U4TEXT_TITLE_1_TEXT_28,
	U4TEXT_TITLE_1_TEXT_29,
	U4TEXT_TITLE_1_TEXT_30,
	U4TEXT_TITLE_1_TEXT_31,
	U4TEXT_TITLE_1_TEXT_32,
	U4TEXT_TITLE_1_TEXT_33,
	U4TEXT_TITLE_1_TEXT_34,
	U4TEXT_TITLE_1_TEXT_35,
	U4TEXT_TITLE_1_TEXT_36,
	U4TEXT_TITLE_1_TEXT_37,
	U4TEXT_TITLE_1_TEXT_38,
	U4TEXT_TITLE_1_TEXT_39,
	U4TEXT_TITLE_1_TEXT_40,
	U4TEXT_TITLE_1_TEXT_41,
	U4TEXT_TITLE_1_TEXT_42,
	U4TEXT_TITLE_1_TEXT_43,
	U4TEXT_TITLE_1_TEXT_44,
	U4TEXT_TITLE_1_TEXT_45,
	U4TEXT_TITLE_1_TEXT_46,
	U4TEXT_TITLE_1_TEXT_47,
	U4TEXT_TITLE_1_TEXT_48,
	U4TEXT_TITLE_1_TEXT_49,
	U4TEXT_TITLE_1_TEXT_50,
	U4TEXT_TITLE_1_TEXT_51,
	U4TEXT_TITLE_1_TEXT_52,
	U4TEXT_TITLE_1_TEXT_53,
	U4TEXT_TITLE_1_TEXT_54,
	U4TEXT_TITLE_1_TEXT_55,
	U4TEXT_TITLE_1_TEXT_56,
	U4TEXT_TITLE_1_TEXT_57,
	U4TEXT_TITLE_1_TEXT_58,
	U4TEXT_TITLE_1_TEXT_59,
	U4TEXT_TITLE_1_TEXT_60,
	U4TEXT_TITLE_1_TEXT_61,
	U4TEXT_TITLE_1_TEXT_62,
	U4TEXT_TITLE_1_TEXT_63,
	U4TEXT_TITLE_1_TEXT_64,
	U4TEXT_TITLE_1_TEXT_65,
	U4TEXT_TITLE_1_TEXT_66,
	U4TEXT_TITLE_1_TEXT_67
};

/*C_261D*/u4_puts(bp04)
char *bp04;
{
	char bp_02;

	while(bp_02 = *bp04) {
		if(bp_02 == '\n') {
			u4_IncrementTextY();
			u4_SetTextX(0);
		} else {
			u4_putc(*bp04);
		}
		bp04 ++;
	}
}

/*text input?*/
C_2656(si/*bp06*/, bp04)
register char *si;
unsigned bp04;
{
	register unsigned di;
	unsigned bp_04;

	di = 0;
	do {
		bp_04 = u_kbread();
		switch(bp_04) {
			case KBD_BS: case KBD_0e7f: case KBD_LEFT:
				if(di == 0) {
					sound_1();
				} else {
					u4_putc(8);
					di--;
					si[di] = ' ';
				}
			break;
			default:
				bp_04 &= 0x00ff;
				if(bp04 - 1 == di || bp_04 < 0x20 || bp_04 >= 0x80) {
					sound_1();
				} else {
					si[di] = bp_04;
					u4_putc(bp_04);
					di ++;
				}
			break;
			case KBD_ENTER:
				si[di] = 0;
			break;
		}
	} while(bp_04 != KBD_ENTER);
	bp_04 = 0;
	while(si[bp_04++] == ' ');
	if(si[--bp_04]) {
		di = 0;
		while(si[bp_04])
			si[di++] = si[bp_04++];
	} else {
		di = bp_04;
	}
	do
		si[di] = 0;
	while(si[--di] == ' ');
}

C_271D(bp04)
char *bp04;
{
	Gra_5();
	u4_SetTextCoord(0, 19);
	u4_puts(bp04);
	u_kbread();
}

/*moongate animation #1*/
C_273E()
{
	int bp_02, bp_04;

	for(bp_02 = 1; bp_02 <= 23; bp_02++) {
		Gra_3(3,      bp_02, 0, 152, D_6940, 92 - bp_02, -1, 9);
		Gra_3(3, 24 - bp_02, 9,  68, D_6940, 68,         -1, 9);
		for(bp_04 = 1; bp_04 <= 10000; bp_04 ++);
	}
	Gra_3(3, 24, 0, 152, D_6940, 68, -1, 9);
}

/*moongate animation #2*/
C_27E0()
{
	int bp_02, bp_04;

	for(bp_02 = 1; bp_02 <= 23; bp_02 ++) {
		Gra_3(3,      bp_02, 3, 152, D_6940,         68, -1, 9);
		Gra_3(3, 24 - bp_02, 0, 152, D_6940, bp_02 + 68, -1, 9);
		for(bp_04 = 1; bp_04 <= 10000; bp_04 ++);
	}
	Gra_3(3, 24, 3, 152, D_6940, 68, -1, 9);
}

C_2883()
{
	unsigned bp_02;

	if((D_6940 = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		exit(0x5e);
	bp_02 = 0x1d;
	Gra_inflate((D_7078 == 1)?/*D_2F6C*/"tree.pic":/*D_2F75*/"tree.ega", D_6940);
	Gra_clrscr();
	Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
	while(bp_02 != 0x35) {
		Gra_5();
		u4_SetTextCoord(0, 19);
		u4_puts(STR(bp_02++));
		switch(bp_02 - 1) {
			case 0x20:
				C_273E();/*moongate animation #1*/
			break;
			case 0x22:
				C_27E0();/*moongate animation #2*/
				Gra_inflate((D_7078 == 1)?/*D_2F7E*/"portal.pic":/*D_2F89*/"portal.ega", D_6940);
			break;
			case 0x23:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2F94*/"tree.pic":/*D_2F9D*/"tree.ega", D_6940);
			break;
			case 0x28:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2FA6*/"outside.pic":/*D_2FB2*/"outside.ega", D_6940);
			break;
			case 0x2c:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2FBE*/"inside.pic":/*D_2FC9*/"inside.ega", D_6940);
			break;
			case 0x2e:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2FDE*/"wagon.pic":/*D_2FD4*/"wagon.ega", D_6940);
			break;
			case 0x31:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2FE8*/"gypsy.pic":/*D_2FF2*/"gypsy.ega", D_6940);
			break;
			case 0x32:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
				Gra_inflate((D_7078 == 1)?/*D_2FFC*/"abacus.pic":/*D_3007*/"abacus.ega", D_6940);
			break;
			case 0x34:
				Gra_3(40, 152, 0, 0, D_6940, 0, -1, 0);
			break;
		}
		u_kbflush();
		u_kbread();
	}
}

int D_3012[] = {0x18,0x28,0x36,0x44,0x52,0x62,0x70};

/*draw abacus beas*/
C_2B2A(bp08, bp06, bp04)
unsigned bp08;/*0:chosen, 1:discarded ?*/
unsigned bp06;/*virtue index*/
unsigned bp04;/*line*/
{
	Gra_3(1, 12, (bp08 == 0)?1:3, 187, D_6940, D_3012[bp04], -1, bp06 + 16);
}

char *D_307E[] = {
	/*D_3020*/"HONCOM.EGA",
	/*D_302B*/"VALJUS.EGA",
	/*D_3036*/"SACHONOR.EGA",
	/*D_3043*/"SPIRHUM.EGA",

	/*D_304F*/"HONCOM.PIC",
	/*D_305A*/"VALJUS.PIC",
	/*D_3065*/"SACHONOR.PIC",
	/*D_3072*/"SPIRHUM.PIC"
};

/*draw virtue card*/
C_2B6D(bp06, bp04)
unsigned bp06;/*virtue index*/
unsigned bp04;/*left or right*/
{
	void far *bp_04;

	bp06 += ((D_7078 == 1)?1:0) * 8;
	if((bp_04 = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		exit(0x5d);
	Gra_inflate(D_307E[bp06/2], bp_04);
	Gra_3(12, 124, ((bp06&1) == 0)?1:27, 12, bp_04, 12, -1, (bp04 == 0)?1:27);
	_ffree(bp_04);
}

/*characterisics increments by virtue*/
unsigned char D_30B2[] = {0, 0, 3, 0, 1, 1, 1, 0};/*str*/
unsigned char D_30BA[] = {0, 3, 0, 1, 1, 0, 1, 0};/*dex*/
unsigned char D_30C2[] = {3, 0, 0, 1, 0, 1, 1, 0};/*int*/

/*dilemmas text indexes*/
unsigned char D_30CA[] = {
	/*0x00*/0x01 - 1,/*Honesty vs {Compassion|...|Humility}*/
	/*0x06*/0x08 - 2,/*Compassion vs {Valor|...|Humility}*/
	/*0x0B*/0x0e - 3,/*Valor vs {Justice|...|Humility}*/
	/*0x0F*/0x13 - 4,/*Justice vs {Sacrifice|...|Humility}*/
	/*0x12*/0x17 - 5,/*Sacrifice vs {Honor|...|Humility}*/
	/*0x14*/0x1a - 6,/*Honor vs {Spirituality|Humility}*/
	/*0x15*/0x1c - 7 /*Spirituality vs Humility*/
};

C_2C12()
{
	int loc_A;
	unsigned char loc_B, loc_C;
	unsigned char loc_D[8];

	tmp_str = tmp_int = tmp_dex = 15;
	curQuestionIndex = 0;
	for(loc_A = 7; loc_A >= 0; loc_A--) {
		loc_D[loc_A] = 0;
		tmp_karma[loc_A] = 50;
	}
	do {
		if(curQuestionIndex == 4 || curQuestionIndex == 6) {
			for(loc_A = 7; loc_A >= 0; loc_A --)
				if(loc_D[loc_A] < 0x80)
					loc_D[loc_A] = 0;
		}
		Gra_5();
		u4_SetTextCoord(0, 19);
		do
			loc_B = u_rand_a() & 7;
		while(loc_D[loc_B&0xff]);
		do
			loc_C = u_rand_a() & 7;
		while(loc_D[loc_C&0xff] || loc_C == loc_B);
		if(loc_C < loc_B) {
			/*swap(loc_B,loc_C);*/
			loc_A = loc_B; loc_B = loc_C; loc_C = loc_A;
		}
		if(curQuestionIndex == 0)
			u4_puts(/*D_2F4E*/STR(0x35));
		else if(curQuestionIndex == 6)
			u4_puts(/*D_2F52*/STR(0x37));
		else
			u4_puts(/*D_2F50*/STR(0x36));
		u4_puts(/*D_2F54*/STR(0x38));
		C_2B6D(loc_B, 0);
		u4_puts(STR(0x39 + loc_B));
		u4_puts(/*D_308E*/U4TEXT_TITLE_1_724);
		C_2B6D(loc_C, 1);
		u4_puts(STR(0x39 + loc_C));
		u4_puts(/*D_3094*/U4TEXT_TITLE_1_727);
		u_kbflush();
		u_kbread();
		Gra_5();
		u4_SetTextCoord(0, 19);
		u4_puts(STR(D_30CA[loc_B] + loc_C));
		do {
			loc_A = u_kbread();
			if(u4_isupper((unsigned char)loc_A))
				loc_A += 'a' - 'A';
		} while(loc_A != KBD_A && loc_A != KBD_B);
		if(loc_A == KBD_B) {
			/*swap(loc_B,loc_C);*/
			loc_A = loc_B; loc_B = loc_C; loc_C = loc_A;
		}
		/*chosen virtue*/
		lastVirtue = loc_B;
		loc_D[lastVirtue] = 1;
		tmp_karma[lastVirtue] += 5;
		tmp_str += D_30B2[lastVirtue];
		tmp_dex += D_30BA[lastVirtue];
		tmp_int += D_30C2[lastVirtue];
		C_2B2A(0, lastVirtue, curQuestionIndex);
		/*discarded virtue*/
		loc_D[loc_C] = 0xff;
		C_2B2A(1, loc_C, curQuestionIndex);
	} while(++curQuestionIndex != 7);
	C_271D(/*D_2F68*/STR(0x42));
	C_271D(/*D_2F6A*/STR(0x43));
}

unsigned char D_30DC[] = {0xE7,0x53,0x23,0x3B,0x9E,0x69,0x17,0xBA};
unsigned char D_30E4[] = {0x88,0x69,0xDD,0x2C,0x15,0xB7,0x81,0xAB};

unsigned /*D_30EC*/*pKarmas[] = {
	&(Party._hones),
	&(Party._compa),
	&(Party._valor),
	&(Party._justi),
	&(Party._sacri),
	&(Party._honor),
	&(Party._spiri),
	&(Party._humil)
};

C_2E04()
{
	int loc_A;
	struct tChara loc_B;

	if(Load(/*D_30D1*/"PARTY.NEW", sizeof(struct tParty), &Party) == -1)
		exit(3);
	Party._x = D_30DC[lastVirtue];
	Party._y = D_30E4[lastVirtue];
	Party.f_1d8 = 1;
	for(loc_A = 7; loc_A >= 0; loc_A --)
		*(pKarmas[loc_A]) = tmp_karma[loc_A];
	/*-- swap(&(Party.chara[lastVirtue]), &(Party.chara[0])) --*/
	memcpy(&loc_B, &(Party.chara[lastVirtue]), sizeof(struct tChara));
	memcpy(&(Party.chara[lastVirtue]), &(Party.chara[0]), sizeof(struct tChara));
	memcpy(&(Party.chara[0]), &loc_B, sizeof(struct tChara));
	/*-- --*/
	strcpy(Party.chara[0]._name, player_name);
	Party.chara[0]._str = tmp_str;
	Party.chara[0]._int = tmp_int;
	Party.chara[0]._dex = tmp_dex;
	Party.chara[0].p_24 = (M_or_F == 'M')?0x0b:0x0c;
	for(loc_A = 31; loc_A >= 0; loc_A --) {
		D_6976._npc._000[loc_A] =
		D_6976._npc._020[loc_A] =
		D_6976._npc._040[loc_A] =
		D_6976._npc._060[loc_A] =
		D_6976._npc._080[loc_A] =
		D_6976._npc._0A0[loc_A] =
		D_6976._npc._0C0[loc_A] =
		D_6976._npc._0E0[loc_A] = 0;
	}
}

/*confirmFileInDrive?*/
C_2F07(bp06, bp04)/*%%% hacked %%%*/
char *bp06;
char *bp04;
{
	int bp_02;

	Gra_clrscr();
	u4_SetTextY(10);
	txt_X = (40 - (unsigned)strlen(bp06)) / 2;
	u4_puts(bp06);
	u4_IncrementTextY();
	u4_SetTextX(18);
	u4_puts(/*D_30FC*/U4TEXT_TITLE_1_820);
	u4_IncrementTextY();
	u4_SetTextX(11);
	u4_puts(/*D_3100*/U4TEXT_TITLE_1_823);
	while(!u_kbhit());
	do {
		bp_02 = u_kbread() & 0xff;
		u4_toupper(bp_02);
		if(bp_02 != 'B' || D_7082 != 0) {
			if(bp_02 >= 'A' && bp_02 <= 'P') {
				bp_02 &= 0xf;
				C_3299(bp_02);
			}
		}
		if((C_3290() & 0xff) == bp_02 && C_32AB(bp04))
			return;
		sound_1();
		while(!u_kbhit());
	} while(1);
}

/*prepare player disk?*/
C_2FB8()
{
	unsigned bp_02;

	bp_02 = C_3290() & 0xff;
	C_2F07(/*D_311D*/U4TEXT_TITLE_1_847, /*D_3113*/"WORLD.MAP");
	D_6938 = C_3290() & 0xff;
	if(Save(/*D_3130*/"PARTY.SAV", sizeof(struct tParty), &Party) == -1)
		exit(3);
	if(Save(/*D_313A*/"MONSTERS.SAV", sizeof(struct tNPC), &(D_6976._npc)) == -1)
		exit(3);
	if(D_6938 == bp_02)
		C_2F07(/*D_3152*/U4TEXT_TITLE_1_854, /*D_3147*/"AVATAR.EXE");
	else
		C_3299(bp_02);
}

extern C_0B1E(int, int, char *);

C_3030()
{
	Gra_2();
	C_0B1E(16, 4, /*D_3169*/U4TEXT_TITLE_1_864);
	C_0B1E(17, 4, /*D_318A*/U4TEXT_TITLE_1_865);
	u4_SetTextCoord(12, 19);
	C_2656(player_name, 12);
	if(player_name[0] == 0) {
		_ffree(pAnim);
		_ffree(pShapes);
		return;
	}
	Gra_2();
	C_0B1E(17, 4, /*D_31A2*/U4TEXT_TITLE_1_875);
	M_or_F = u_kbread() & 0xff;
	u4_toupper(M_or_F);
	while(M_or_F != 'M' && M_or_F != 'F') {
		sound_1();
		M_or_F = u_kbread() & 0xff;
		if(M_or_F == 0x1b || M_or_F == KBD_ENTER || M_or_F == KBD_SPACE) {
			_ffree(pAnim);
			_ffree(pShapes);
			return;
		}
		u4_toupper(M_or_F);
	}
	u4_putc(M_or_F);
	_ffree(pAnim);
	_ffree(pShapes);
	D_6E80 = 0;

	C_2883();/*introduction*/
	C_2C12();/*gipsy*/
	C_2E04();/*prepare party structure*/
	C_2FB8();/*prepare player disk?*/
	_ffree(D_6940);
	/*-- clean & return to dos --*/
	_ffree(pCharset);
	low_clean();
	exit('A' + D_6938 - 1);
}
