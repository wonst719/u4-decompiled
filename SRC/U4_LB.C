/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>

char *D_6FF0[28] = {
	/*D_639A*/U4TEXT_LB_12,
	/*D_639E*/U4TEXT_LB_13,
	/*D_63A3*/U4TEXT_LB_14,
	/*D_63AA*/U4TEXT_LB_15,
	/*D_63AF*/U4TEXT_LB_16,
	/*D_63B4*/U4TEXT_LB_17,
	/*D_63B8*/U4TEXT_LB_18,
	/*D_63BE*/U4TEXT_LB_19,
	/*D_63C3*/U4TEXT_LB_20,
	/*D_63CB*/U4TEXT_LB_21,
	/*D_63D3*/U4TEXT_LB_22,
	/*D_63DE*/U4TEXT_LB_23,
	/*D_63E4*/U4TEXT_LB_24,
	/*D_63EC*/U4TEXT_LB_25,
	/*D_63F6*/U4TEXT_LB_26,
	/*D_63FC*/U4TEXT_LB_27,
	/*D_6409*/U4TEXT_LB_28,
	/*D_6412*/U4TEXT_LB_29,
	/*D_6418*/U4TEXT_LB_30,
	/*D_641F*/U4TEXT_LB_31,
	/*D_6425*/U4TEXT_LB_32,
	/*D_642F*/U4TEXT_LB_33,
	/*D_6434*/U4TEXT_LB_34,
	/*D_643A*/U4TEXT_LB_35,
	/*D_6442*/U4TEXT_LB_36,
	/*D_6448*/U4TEXT_LB_37,
	/*D_644F*/U4TEXT_LB_38,
	/*D_6456*/""
};

char *D_7028[24] = {
	/*D_6457*/U4TEXT_LB_43,
	/*D_6499*/U4TEXT_LB_44,
	/*D_64C9*/U4TEXT_LB_45,
	/*D_650F*/U4TEXT_LB_46,
	/*D_6577*/U4TEXT_LB_47,
	/*D_65E6*/U4TEXT_LB_48,
	/*D_663B*/U4TEXT_LB_49,
	/*D_6698*/U4TEXT_LB_50,
	/*D_66F3*/U4TEXT_LB_51,
	/*D_673D*/U4TEXT_LB_52,
	/*D_6785*/U4TEXT_LB_53,
	/*D_67DD*/U4TEXT_LB_54,
	/*D_6840*/U4TEXT_LB_55,
	/*D_689B*/U4TEXT_LB_56,
	/*D_6978*/U4TEXT_LB_57,
	/*D_6A66*/U4TEXT_LB_58,
	/*D_6B2B*/U4TEXT_LB_59,
	/*D_6C25*/U4TEXT_LB_60,
	/*D_6D6C*/U4TEXT_LB_61,
	/*D_6DF2*/U4TEXT_LB_62,
	/*D_6F0C*/U4TEXT_LB_63,
	/*D_6F2D*/U4TEXT_LB_64,
	/*D_6F4C*/U4TEXT_LB_65,
	/*D_6F6C*/U4TEXT_LB_66
};

/*10 seconds delay*/
C_E1FC() {
	u_kbflush();
	u_delay(10, 1);
	if(u_kbhit())
		u_kbread();
}

/*when asked 'help'*/
C_E21E() {
	u4_puts(/*D_7058*/U4TEXT_LB_79);
	if(Party._moves < 1000) {
		u4_puts(/*D_7062*/U4TEXT_LB_81); C_E1FC();
		u4_puts(/*D_70D8*/U4TEXT_LB_82); C_E1FC();
		u4_puts(/*D_7113*/U4TEXT_LB_83);
	} else
	if(Party.f_1d8 == 1) {
		u4_puts(/*D_7166*/U4TEXT_LB_86); C_E1FC();
		u4_puts(/*D_71E6*/U4TEXT_LB_87);
	} else
	if(Party.mRunes == 0) {
		u4_puts(/*D_7239*/U4TEXT_LB_90); C_E1FC();
		u4_puts(/*D_7283*/U4TEXT_LB_91); C_E1FC();
		u4_puts(/*D_72FB*/U4TEXT_LB_92); C_E1FC();
		u4_puts(/*D_7353*/U4TEXT_LB_93);
	} else
	if(
		Party._hones & Party._compa &
		Party._valor & Party._justi &
		Party._sacri & Party._honor &
		Party._spiri & Party._humil
	) {
		u4_puts(/*D_73BD*/U4TEXT_LB_101); C_E1FC();
		u4_puts(/*D_740E*/U4TEXT_LB_102); C_E1FC();
		u4_puts(/*D_747A*/U4TEXT_LB_103);
	} else
	if(Party.mStones == 0) {
		u4_puts(/*D_74EA*/U4TEXT_LB_106); C_E1FC();
		u4_puts(/*D_7572*/U4TEXT_LB_107);
	} else
	if(
		Party._hones | Party._compa |
		Party._valor | Party._justi |
		Party._sacri | Party._honor |
		Party._spiri | Party._humil
	) {
		u4_puts(/*D_75B7*/U4TEXT_LB_115);
	} else
	if(!((Party.mItems >> 4) & (Party.mItems >> 3) & (Party.mItems >> 2) & 1)) {
		u4_puts(/*D_762C*/U4TEXT_LB_118);
	} else
	if(!((Party.mItems >> 5) & (Party.mItems >> 6) & (Party.mItems >> 7) & 1)) {
		u4_puts(/*D_7691*/U4TEXT_LB_121); C_E1FC();
		u4_puts(/*D_76F4*/U4TEXT_LB_122);
	} else {
		u4_puts(/*D_7739*/U4TEXT_LB_124); C_E1FC();
		u4_puts(/*D_77A1*/U4TEXT_LB_125); C_E1FC();
		u4_puts(/*D_77FD*/U4TEXT_LB_126);
	}
}

/*looks for the parameter in Lord British's keywords
 (4 char is enough)
 not found => -1
 else => index of the keywords*/
C_E37E(bp04)
char *bp04;
{
	int bp_02;

	for(bp_02 = 0; D_6FF0[bp_02][0]; bp_02++) {
		if(strnicmp(bp04, D_6FF0[bp_02], 4) == 0)
			break;
	}
	if(D_6FF0[bp_02][0] == 0)
		return -1;
	return bp_02;
}

C_E3D2(bp04)
register char *bp04;
{
	register int di;
	register unsigned code;

	di = 0;
	while(*bp04) {
		if(*bp04 == '\n') {
			if(di++ == 12) {
				C_E1FC();
				di = 0;
			}
		}
		code = (unsigned char)(*bp04++);
		if (code & 0x80) {
			code = (code << 8) | (unsigned char)(*bp04++);
		}

		u4_putc(code);
	}
}

C_E408() {
	int bp_02;

	for(bp_02 = Party.f_1d8 - 1; bp_02 >= 0; bp_02 --) {
		if(Party.chara[bp_02]._stat != 'D') {
			Party.chara[bp_02]._stat = 'G';
			Party.chara[bp_02]._HP[0] = Party.chara[bp_02]._HP[1];
		}
	}
}

/*when asekd 'health'*/
C_E442() {
	char bp_02;

	u4_puts(/*D_784D*/U4TEXT_LB_181);
	bp_02 = AskY_N();
	if(bp_02 == 'Y') {
		u4_puts(/*D_788D*/U4TEXT_LB_184);
	} else if(bp_02 =='N') {
		u4_puts(/*D_78A6*/U4TEXT_LB_186);
		/*heal party*/
		sound(10, 10);
		Gra_09(); sound(9, 0xc0); Gra_09();
		C_E408();
		dspl_Stats();
	}
}

C_E498(bp04)
int *bp04;
{
	*bp04 += U4_RND1(7)+1;
	*bp04 = u4_min(*bp04, 50);
}

C_E4C3() {
	int loc_A, loc_B, loc_C;

	for(loc_B = 0; loc_B < Party.f_1d8; loc_B++) {
		for(loc_C = loc_A = 100; loc_A <= Party.chara[loc_B]._XP; loc_C += 100, loc_A <<= 1);
		if(Party.chara[loc_B]._HP[1] < loc_C) {
			Party.chara[loc_B]._HP[1] = loc_C;
			Party.chara[loc_B]._HP[0] = loc_C;
			Party.chara[loc_B]._stat = 'G';
			C_E498(&(Party.chara[loc_B]._str));
			C_E498(&(Party.chara[loc_B]._dex));
			C_E498(&(Party.chara[loc_B]._int));
			Gra_CR();
			u4_puts(Party.chara[loc_B]._name);
			u4_puts(/*D_78C9*/U4TEXT_LB_216);
			u4_putl(loc_C / 100, 1, '0');
			Gra_CR();
			Gra_09(); sound(9, 0xc0); Gra_09();
			dspl_Stats();
		}
	}
	u4_puts(/*D_78DE*/U4TEXT_LB_223);
}

/*conversation with Lord british*/
C_E59B()
{
	int bp_02;
	char bp_12[15];

	musici(U4_MUS_LB);

	if(Party.f_1e4 == 0) {
		/*-- first time --*/
		Party.f_1e4 = 1;
		u4_puts(/*D_78FA*/U4TEXT_LB_235);
		u4_puts(Party.chara[0]._name);
		u4_putc(',');
		u4_puts(/*D_7929*/U4TEXT_LB_238);
		C_E1FC();
		u4_puts(/*D_7966*/U4TEXT_LB_240);
		u4_puts(/*D_7A7C*/U4TEXT_LB_242);
	} else {
		/*-- second time and after --*/
		if(Party.chara[0]._stat == 'D') {
			/*resurection*/
			Party.chara[0]._stat = 'G';
			u4_puts(Party.chara[0]._name);
			u4_puts(/*D_7A92*/U4TEXT_LB_249);
			/*heal party*/
			sound(10, 20);
			Gra_09(); sound(9, 0xc0); Gra_09();
			C_E408();
			dspl_Stats();
		}
		u4_puts(/*D_7AAC*/U4TEXT_LB_256);
		u4_puts(Party.chara[0]._name);
		if(Party.f_1d8 >= 3) {
			u4_puts(/*D_7ACC*/U4TEXT_LB_259);
		} else if(Party.f_1d8 == 2) {
			u4_puts(/*D_7AEA*/U4TEXT_LB_261);
			u4_puts(Party.chara[1]._name);
			u4_puts(/*D_7AFA*/U4TEXT_LB_263);
		} else {
			Gra_CR();
		}
		C_E4C3();
	}

	for(;;) {
		u4_gets(bp_12, 15);
		Gra_CR();
		if(bp_12[0] == 0)
			bp_02 = 0;
		else
			bp_02 = C_E37E(bp_12);
		if(bp_02 == 0)/*"bye"*/
			break;
		switch(bp_02) {
			case 2: C_E442(); break;
			case 1: C_E21E(); break;
			case -1: u4_puts(/*D_7AFD*/U4TEXT_LB_282); break;
			default: C_E3D2(D_7028[bp_02-3]);
		}
		u4_puts(/*D_7B26*/U4TEXT_LB_285);
	}

	u4_puts(/*D_7B33*/U4TEXT_LB_288);
	if(Party.f_1d8 > 1)
		u4_puts(U4TEXT_LB_289);
	u4_puts(/*D_7B5F*/U4TEXT_LB_290);

	music();
}
