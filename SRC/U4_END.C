/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>

char *endQuestions[] = {
	/*D_09BE*/U4TEXT_END_12,
	/*D_09FB*/U4TEXT_END_13,
	/*D_0A38*/U4TEXT_END_14,
	/*D_0A66*/U4TEXT_END_15,
	/*D_0A97*/U4TEXT_END_16,
	/*D_0AC9*/U4TEXT_END_17,
	/*D_0ADE*/U4TEXT_END_18,
	/*D_0B09*/U4TEXT_END_19,
	/*D_0B52*/U4TEXT_END_20,
	/*D_0B7C*/U4TEXT_END_21,
	/*D_0BB6*/U4TEXT_END_22
};

C_2F7E()
{
	u_delay(15, 1);
	if(u_kbhit())
		u_kbread();
}

unsigned char D_0BF0[] = {0xE7,0x53,0x23,0x3B,0x9E,0x69,0x17,0xBA,0xD8,0x1D,0x91,0x59,0xE9};
unsigned char D_0BFE[] = {0x88,0x69,0xDD,0x2C,0x15,0xB7,0x81,0xAC,0x6A,0x30,0xF3,0x6A,0xE9};

static unsigned D_8CCA;

/*return to surface*/
ReturnToSurface(bp04)
unsigned bp04;
{
	u_delay(5, 0);
	Gra_CR();
	Party._x = D_0BF0[bp04];
	Party._y = D_0BFE[bp04];
	Party.party_size = D_8CCA;
	Party._loc = 0;
	CurMode = MOD_OUTDOORS;
	spell_cnt = 0;
	hit_tile = 0;
	spell_sta = 7;
	D_9440 = 1;
	D_95C6 = 0;
	Party.f_1dc = 0;
	music();
	C_26B6();
	dspl_Stats();
	u_kbflush();
	longjmp(D_9458, -1);
}

/*passage is not granted*/
NotGranted()
{
	u4_puts(/*D_0C0B*/U4TEXT_END_63);
	ReturnToSurface(12);
}

/*Victory !*/
EndVictory()
{
	u_delay(2, 0);
	shakefx();
	shakefx();
	shakefx();
	shakefx();
	u_delay(3, 0);
	dfree(pShapes);
	Gra_17();/*infinity symbol*/
	u_delay(3, 0);
	musici(U4_MUS_LB);
	u4_puts(/*D_0C25*/U4TEXT_END_79);
	C_2F7E();
	u4_puts(/*D_0C76*/U4TEXT_END_81);
	C_2F7E();
	u4_puts(/*D_0CBD*/U4TEXT_END_83);
	C_2F7E();
	u4_puts(/*D_0D15*/U4TEXT_END_85);
	C_2F7E();
	u4_puts(/*D_0D69*/U4TEXT_END_87);
	C_2F7E();
	u4_puts(/*D_0DB9*/U4TEXT_END_89);
	C_2F7E();
	Gra_10();
	u4_puts(/*D_0E32*/U4TEXT_END_92);
	C_2F7E();
	Gra_16((D_943A == 1)?/*D_0EAE*/"stoncrcl.pic":/*D_0EBB*/"stoncrcl.ega", 0, 0);
	u4_puts(/*D_0EC8*/U4TEXT_END_95);
	C_2F7E();
	u4_puts(/*D_0F24*/U4TEXT_END_97);
	C_2F7E();
	u4_puts(/*D_0FA7*/U4TEXT_END_99);
	C_2F7E();
	u4_puts(/*D_102D*/U4TEXT_END_101);
	u4_putl(Party._moves, 0, '0');
	u4_puts(/*D_1087*/U4TEXT_END_103);
	while(1);
}

AskQuestion(question, answer)
char *question;
char *answer;
{
	char buffer[16];
	register int i;

	for (i = 0; i < 3; i++)
	{
		u4_puts(question);
		Gra_CR();
		Gra_CR();
		u4_gets(buffer, 15);
		Gra_CR();

		if (!strnicmp(buffer, answer, 15))
		{
			return 1;
		}
		else if (i < 2)
		{
			u_delay(1, 0);
			u4_puts(/*D_10C6*/U4TEXT_END_120);
			u_delay(2, 0);
		}
	}

	return 0;
}

char *endStrings[] = {
	/*D_111A*/U4TEXT_END_146,
	/*D_1120*/U4TEXT_END_147,
	/*D_1125*/U4TEXT_END_148
};

char *endFileNames[] = {
	/*D_112D*/"honesty",
	/*D_1135*/"compassn",
	/*D_113E*/"valor",
	/*D_1144*/"justice",
	/*D_114C*/"sacrific",
	/*D_1155*/"honor",
	/*D_115B*/"spirit",
	/*D_1162*/"humility",
	"truth",
	"love",
	"courage"
};

/*last phase of game ?*/
C_31F4()
{
#if 1
	int bp_02;
	char bp_12[16];

	D_8CCA = Party.party_size;
	Party.party_size = 1;
	CurMode = MOD_VISION;
	music();
	Gra_13();
	dspl_Stats();
	Gra_10();
	u4_puts(/*D_116B*/U4TEXT_END_174);
	u_delay(4, 0);
	Gra_16((D_943A == 1)?/*D_11BC*/"key7.pic":/*D_11C5*/"key7.ega", 0, 0);
	if(
		!TST_MSK(Party.mItems, 5) |
		!TST_MSK(Party.mItems, 7) |
		!TST_MSK(Party.mItems, 6)
	) {
		u4_puts(/*D_11CE*/U4TEXT_END_182);
		ReturnToSurface(12);
	}
	u4_puts(/*D_11FB*/U4TEXT_END_185);
	u_delay(3, 0);
	u4_puts(/*D_121E*/U4TEXT_END_187);
	if(!AskQuestion(/*D_123D*/U4TEXT_END_188, /*D_1233*/U4TEXT_END_VERAMOCOR))
		NotGranted();
	if(D_8CCA != 8) {
		u4_puts(/*D_125C*/U4TEXT_END_191);
		u_delay(8, 0);
		NotGranted();
	}
	for(bp_02 = 7; bp_02 >= 0; bp_02 --) {
		if(*(pKarmas[bp_02])) {
			u4_puts(/*D_1298*/U4TEXT_END_197);
			NotGranted();
		}
	}
	u4_puts(/*D_12AE*/U4TEXT_END_201);
	u_delay(5, 0);
	Gra_10();
	for(bp_02 = 0; bp_02 < 11; bp_02 ++) {
		char bp_26[20];

		u_delay(2, 0);
		u4_puts(/*D_12C4*/U4TEXT_END_208);
		u_delay(2, 0);
		if(!AskQuestion(endQuestions[bp_02], (bp_02 <= 7) ? Strings[151 + bp_02] : endStrings[bp_02 - 8])) {
			u_delay(1, 0);
			u4_puts(/*D_12D8*/U4TEXT_END_212);
			ReturnToSurface(bp_02);
		}
		strcpy(bp_26, endFileNames[bp_02]);
		strcat(bp_26, (D_943A == 1)?/*D_12F9*/".pic":/*D_12FE*/".ega");
		Gra_16(bp_26, 0, 0);
		if(bp_02 == 7) {
			u_delay(3, 0);
			u4_puts(/*D_1303*/U4TEXT_END_220);
			u_delay(5, 0);
		}
	}
	u4_puts(/*D_1338*/U4TEXT_END_224);
	shakefx();
	shakefx();
	u_delay(5, 0);
	u4_puts(/*D_1360*/U4TEXT_END_228);
	C_2F7E();
	u4_puts(/*D_13F9*/U4TEXT_END_230);
	u4_gets(bp_12, 15);
	Gra_CR();
	if(strnicmp(bp_12, /*D_147B*/U4TEXT_END_INFINITY, 16) != 0 && strncmp(bp_12, U4TEXT_K_END_INFINITY, 16) != 0) {
		u4_puts(/*D_1484*/U4TEXT_END_234);
		u_delay(3, 0);
		u4_puts(/*D_14AE*/U4TEXT_END_236);
		u4_gets(bp_12, 15);
		Gra_CR();
		if(strnicmp(bp_12, /*D_152B*/U4TEXT_END_INFINITY, 16) != 0 && strncmp(bp_12, U4TEXT_K_END_INFINITY, 16) != 0) {
			u4_puts(/*D_1534*/U4TEXT_END_240);
			u_delay(3, 0);
			u4_puts(/*D_155E*/U4TEXT_END_242);
			u4_gets(bp_12, 15);
			Gra_CR();
			if(strnicmp(bp_12, /*D_15DB*/U4TEXT_END_INFINITY, 16) != 0 && strncmp(bp_12, U4TEXT_K_END_INFINITY, 16) != 0) {
				u_delay(1, 0);
				u4_puts(/*D_15E4*/U4TEXT_END_247);
				ReturnToSurface(11);
			}
		}
	}
#endif
	EndVictory();
}
