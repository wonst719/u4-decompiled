/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"
#include "u4_cdda.h"

#include <string.h>
#include <stdlib.h>

C_C445() {}
C_C44A() {}
C_C44F() {}

static int D_9138;

void PutTextCenter(int y, char* text)
{
	unsigned int code;

	int len = strlen(text);
	txt_X = (u4_TextColumn - len) / 2;

	u4_SetTextY(y);
	while (*text) {
		code = (unsigned char)*text++;
		if (code & 0x80) {
			code = (code << 8) | (unsigned char)*text++;
		}
		u4_putc(code);
	}
}

// A = 1, B = 2, ...
#define GetCurrentDrive C_1814
#define SelectDrive C_181D
#define TestFile C_182F

ConfirmFileInDrive(bp06, bp04)
char *bp06;
char *bp04;
{
	int bp_02;

	if(!TestFile(bp04)) {
		CurMode = MOD_VISION;

		PutTextCenter(10, bp06);
		PutTextCenter(11, U4TEXT_INIT_32);
		PutTextCenter(12, U4TEXT_INIT_35);

		while(!u_kbhit());
		do {
			bp_02 = (unsigned char)u_kbread();
			u4_toupper(bp_02);
			if(bp_02 != 'B' || D_9138 != 0) {
				if(bp_02 >= 'A' && bp_02 <= 'P') {
					bp_02 &= 0xf;
					SelectDrive(bp_02);
				}
			}
			if(GetCurrentDrive() == bp_02 && TestFile(bp04))
				return;
			sound(1);
			while(!u_kbhit());
		} while(1);
	}
}

#define NPARAM (far_psp->_80[0])
#define PARAM0 (far_psp->_80[2])
#define PARAM1 (far_psp->_80[4])

extern void CleanupTimer();

C_C51C()
{
	int bp_02, bp_04;
#if 0
	/* CHEAT */
	int i;
#endif

	u4_toupper(PARAM1);
	u4_toupper(PARAM0);

	/*set drive number*/
	D_9138 = ((equip_flags & 0xc0) >> 6) ? 1 : 0;

	/*set graphic type*/
	D_943A = low_gra();

	/* Force EGA graphics mode */
	if (D_943A != 2) {
		Console(/*D_3078*/"I can't find a compatible graphics card.\r\n");
		exit(2);
	}

	/* CDDA */
	CdCheckMscdex();
	CdRequestAudioDiskInfo();

	/* */
	pShapes = dalloc((D_943A == 1)?0x4000:0x8000);
	pCharset = dalloc((D_943A == 1)?0x1400:0x5900);
	if(pShapes == 0 || pCharset == 0)
		exit(3);
	if(Load((D_943A == 1)?/*D_303B*/"CHARSET.CGA":/*D_3047*/"CHARSET.EGA", (D_943A == 1)?0x1400:0x5900, pCharset) == -1)
		exit(3);
	if(D_943A == 1) {
		if(Load(/*D_3053*/"SHAPES.CGA", 0x4000, pShapes) == -1)
			exit(3);
	}
	bp_02 = GetCurrentDrive();
	switch(D_943A) {
		case 1:
			dfree(patch_tandy);
			patch_tandy = 0;
			C_20C1(/*D_305E*/"CGA.DRV");
		break;
		case 2:
			dfree(patch_tandy);
			patch_tandy = 0;
			C_20C1(/*D_3066*/"EGA.DRV");
		break;
		case 3:
			C_20C1(/*D_306E*/"TANDY.DRV");
		break;
		case -1:
			Console(/*D_3078*/"I can't find a color graphics card.\r\n");
			exit(2);
		break;
	}
	bp_04 = C_184F();/*piracy check function ?*/
	Gra_init(&pShapes, &pCharset, exit);
	if(D_943A == 2)
		sizzleCharset();
	C_18A2();

	Gra_clrscr();

	if(PARAM1 >= (char)'A' && PARAM1 <= (char)'Z') {
		if(GetCurrentDrive() == (PARAM1 - 'A' + 1)) {
			ConfirmFileInDrive(/*D_30A8*/U4TEXT_INIT_128, /*D_309E*/"WORLD.MAP");
		} else {
			SelectDrive((PARAM1 - 'A' + 1));
		}
	}
	ConfirmFileInDrive(/*D_30C8*/U4TEXT_INIT_133, /*D_30BE*/"WORLD.MAP");
	if(D_943A != 1) {
		if(Load(/*D_30DB*/"SHAPES.EGA", 0x8000, pShapes) == -1)
			exit(3);
	}
	if(D_943A == 2)
		sizzleShapes();
	if(Load(/*D_30E6*/"PARTY.SAV", sizeof(struct tParty), &Party) == -1)
		exit(3);
#if 0/*def WIN32*/
	/*for debug*/
	Party._x = 0x5b; Party._y = 0x44;
#endif
#if 0
	/* CHEAT */
	Party._gold = 65000;
	Party._torches = 99;
	Party._gems = 99;
	Party._keys = 99;
	Party._sextants = 99;
	for (i = 0; i < 8; i++)
		Party._armors[i] = 99;
	for (i = 0; i < 16; i++)
		Party._weapons[i] = 99;
	for (i = 0; i < 8; i++)
		Party._reagents[i] = 99;
	for (i = 0; i < 26; i++)
		Party._mixtures[i] = 99;
	for (i = 0; i < 8; i++)
		*(pKarmas[i]) = 0;

	SET_MSK(Party.mItems, 5);
	SET_MSK(Party.mItems, 7);
	SET_MSK(Party.mItems, 6);
	Party.f_1d8 = 8;
#endif
	if(Party.party_size == 0) {
		Gra_clrscr();
		u4_SetTextCoordYX(8, 12);
		u4_puts(/*D_30F0*/U4TEXT_INIT_149);
		sound(8);
		u_delay(3, 0);
		u_kbflush();
		if(bp_02 == GetCurrentDrive()) {
			ConfirmFileInDrive(/*D_310B*/U4TEXT_INIT_154, /*D_3010*/"TITLE.EXE");
		} else {
			SelectDrive(bp_02);
			ConfirmFileInDrive(/*D_312C*/U4TEXT_INIT_157, /*D_3122*/"TITLE.EXE");
		}
		CleanupTimer();
		low_clean();
		exit(4);
	}
	if(Load(/*D_3140*/"MONSTERS.SAV", sizeof(struct tNPC), &(D_8742._npc)) == -1)
		exit(3);
	if((File_MAP = dopen(/*D_314D*/"WORLD.MAP", 0)) == -1) {
		Console(/*D_3157*/"Can't open map file\r\n");
		exit(3);
	}
	File_TLK = 0;
	D_9445 = D_0814[Party._trammel];
	D_9448 = D_081C[Party._felucca];
	C_213B();/*draw game screen frame*/
	Gra_CR();
	spell_sta = 7;
	spell_cnt = 0;
	D_9440 = (Party.f_1dc == 0);/*flying status*/
	D_95C6 = 0;
	CurMode = MOD_OUTDOORS;
	WindDir = DIR_N;
	SoundFlag = 1;
	music();
	dspl_Stats();
	C_26B6();
}
