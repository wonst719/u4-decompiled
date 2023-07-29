/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "i18n.h"
#include "title.h"
#include "U4_CDDA.H"

#include "u4_timer.h"

#include <malloc.h>
#include <stdlib.h>

int D_00C0 = 0;
int D_00C2 = 1;
int D_00C4 = -1;
int D_00C6 = 0;

/*base tiles for view*/
unsigned char D_00C8[] = {0x40,0x80,0x10,0x38,0x38,0xC8,0xC8,0x24,0x20,0x88,0xF0,0xF8,0x4D,0x4F,0x4E};

/*====---- _BSS ----====*/
static unsigned char D_3A24[19 * 5];
static unsigned D_3A84;

void Exit(int code)
{
	CleanupTimer();
	exit(code);
}

/* Frame limiter: limit to about 60 hz (= 30 ticks * 0.549 ms) */
#define TICK_FREQUENCY 1820
#define GAME_FREQUENCY 60

#define GAME_TICK (TICK_FREQUENCY / GAME_FREQUENCY)

/*animate the 2 "monsters"*/
/*callback for u_delay*/
/*C_019A*/t_callback()
{
	unsigned bp_02;
	unsigned long tick = GetTickCounter();

	if(D_3A84)
		D_00C0 = 0;
	if(D_00C0 --)
		return;
	D_00C0 = ((D_7078 == 1)?120:200) * speed_info;
	if(D_6E80) {
		cursor_rate = 200;

		bp_02 = D_3380[D_0036++]; D_0036 &= 0x7f;
		Gra_3(6, 32, D_344A[bp_02], D_3438[bp_02], pAnim, 0, -1, 0);
		bp_02 = D_33F8[D_0038++]; D_0038 &= 0x3f;
		Gra_3(6, 32, D_345C[bp_02], D_3438[bp_02], pAnim, 0, -1, 34);
	} else {
		cursor_rate = 233;
	}

	/* CDDA */
	CdCallback();

	/* elapsed tick */
	tick = GetTickCounter() - tick;
	if (tick < GAME_TICK)
	{
		u4_sleep_tick(GAME_TICK - tick);
	}
}

#include "..\INC\KOREAN.H"

static unsigned int g_lastCode;
static int g_use80ColumnMode = 1;

/*C_0C9F*/u4_putc(bp04)
unsigned int bp04;
{
	g_lastCode = bp04;

	switch (bp04) {
	case '\b':
		if (txt_X > 1) {
			if (g_lastCode >= 256 && g_use80ColumnMode) {
				txt_X -= 2;
				Gra_putchar(' ');
				Gra_putchar(' ');
			}
			else {
				txt_X--;
				Gra_putchar(' ');
			}
		}
		break;
	case ' ':
		if (txt_X <= u4_TextColumn - 1) {
			Gra_pute(bp04);
			txt_X++;
		}
		break;
	default:
		if (bp04 >= 256) {
			u4_putk(bp04);
			txt_X += 2;
		}
		else if (bp04 >= 0x20) {
			Gra_pute(bp04);
			txt_X++;
		}
		else {
			Gra_putchar(bp04);
			txt_X += 2;
		}
	}
}

Anim_Delay(bp04)
long bp04;
{
	if(u_kbhit())
		return;
	u4_sleep_tick(bp04 / 26);
}

/*handwriting?*/
Anim_LordBritish(bp04)
unsigned bp04;
{
	register int si;

	for(si = 0; D_346E[si]; ) {
		Gra_dot(191 - D_346E[si+1], D_346E[si] + 20, 3);
		Gra_dot(191 - D_346E[si+1], D_346E[si] + 21, 3);
		si += 2;
		if(bp04)
			Anim_Delay((long)440);
	}
	if(bp04)
		u_delay(1, 1);
}

/*tiles animation ?*/
C_034D()
{
	register int si;

	for(si = 0; si < 32; si ++) {
		register int di;

		di = D_6976._npc._060[si];
		if(
			(di >= 0x84 && di <= 0x8e) ||
			(di >= 0x20 && di <= 0x2e) ||
			(di >= 0x50 && di <= 0x5e)
		) {
			if(u_rand_b() < 0xc0)
				D_6976._npc._000[si] = ((D_6976._npc._000[si] & 1) | di) ^ 1;
		} else if(di >= 0x90) {
			if(u_rand_b() < 0xc0)
				D_6976._npc._000[si] = ((D_6976._npc._000[si] + 1) & 3) | di;
		} else if(di != 0x80) {
			D_6976._npc._000[si] = di;
		}
	}
	if(--D_00C2)
		return;
	D_00C2 = (speed_info < 16) ? 1 : (speed_info / 16);
	Gra_animFlow(0x00);
	Gra_animFlow(0x01);
	Gra_animFlow(0x02);
	Gra_animFlow(0x4c);
	Gra_animFlow(0x44);
	Gra_animFlow(0x46);
	Gra_animFlow(0x47);
	Gra_animFlow(0x45);
	Gra_animFlag();
}

C_041A()
{
	int bp_02;

	if(D_00C6) {
		D_00C6 --;
		return;
	}
	while(1) {
		switch(D_36E2[++D_00C4] & 0xf0) {
			case 0x00: case 0x10: case 0x20: case 0x30: case 0x40: case 0x50: case 0x60:
				D_6976._npc._040[D_36E2[D_00C4] & 0xf] = D_36E2[D_00C4] >> 4;
				D_6976._npc._020[D_36E2[D_00C4] & 0xf] = D_36E2[D_00C4 + 1] & 0x1f;
				D_6976._npc._000[D_36E2[D_00C4] & 0xf] = D_00C8[D_36E2[D_00C4] & 0xf] + (D_36E2[D_00C4 + 1] >> 5);
				D_6976._npc._060[D_36E2[D_00C4] & 0xf] = ((D_36E2[D_00C4] & 0xf) == 1)?
					D_00C8[D_36E2[D_00C4] & 0xf]:
					D_6976._npc._000[D_36E2[D_00C4] & 0xf]
				;
				D_00C4++;
			break;
			case 0x70:/**/
				D_6976._npc._000[D_36E2[D_00C4] & 0xf] =
				D_6976._npc._060[D_36E2[D_00C4] & 0xf] = 0;
			break;
			case 0x80:/*end frame*/
				for(bp_02 = 0; bp_02 < 19 * 5; bp_02 ++)
					D_3A24[bp_02] = D_3683[bp_02];
				for(bp_02 = 0; bp_02 < 32; bp_02 ++) {
					if(D_6976._npc._000[bp_02])
						D_3A24[19 * D_6976._npc._040[bp_02] + D_6976._npc._020[bp_02]] = D_6976._npc._000[bp_02];
				}
				D_00C6 = D_36E2[D_00C4] & 0xf;
			return;
			case 0x90: case 0xa0: case 0xb0: case 0xc0: case 0xd0: case 0xe0: case 0xf0:
				D_00C4 = -1;
			break;
		}
	}
}

/*the "view"*/
C_05A4()
{
	register int si;

	D_3A84 = 1;
	D_31C0 = 0;
	while(!u_kbhit()) {
		C_034D();
		C_041A();
		D_6E80 = 0;
		Gra_0(5, 19, D_3A24, 104, 0, 0, 2);
		for(si = speed_info / 16; si && !u_kbhit(); si --)
			Gra_0(5, 19, D_3A24, 104, 0, 0, 2);
		C_034D();
		C_041A();
		Gra_0(5, 19, D_3A24, 104, 0, 0, 2);
		for(si = speed_info / 16; si && !u_kbhit(); si --)
			Gra_0(5, 19, D_3A24, 104, 0, 0, 2);
		D_6E80 = 1;
	}
	D_3A84 = 0;
	u_kbread();
}

/*logo + splash + animation*/
C_068C()
{
	register unsigned loc_A, loc_B;
	int loc_C;

	u_delay(1, 1);
	/*"lord british"*/
	Anim_LordBritish(1);
	/*"and"*/
	Gra_3(4, 4, 19, 17, pTitle, 17, -1, 19);
	u_delay(1, 1);
	/*draw line*/
	for(loc_A = 86; loc_A < 238; loc_A++) {
		Gra_dot(31, loc_A, 2);
		Anim_Delay((long)320);
	}
	/*"origin systems inc."*/
	for(loc_A = 1; loc_A < 10; loc_A ++) {
		Gra_3(21, loc_A, 9, 21, pTitle, 30 - loc_A, -1, 9);
		Anim_Delay((long)5000);
	}
	u_delay(1, 1);
	/* */
	if(!u_kbhit()) {
		/*"present"*/
		for(loc_A = 1; loc_A <= 5; loc_A++) {
			Gra_3(15, loc_A, 14, 5 - loc_A, pTitle, 33, -1, 14);
			Anim_Delay((long)5000);
		}
		u_delay(1, 1);
		/*"Ultima iv"*/
		for(loc_A = 0; loc_A < 57; loc_A ++) {
			unsigned long tick = GetTickCounter() + 76;

			if (u_kbhit())
				loc_A = 56;

			do {
				Gra_B(30, 45, 5, 34, pTitle, 34, loc_A, 5);
			} while (tick > GetTickCounter());
		}
		u_delay(1, 1);
	} else {
		Gra_3(30, 45,  5, 34, pTitle, 34, -1,  5);
		Gra_3(15,  5, 14,  0, pTitle, 33, -1, 14);
	}
	/*"quest of the avatar"*/
	for(loc_A = 1; loc_A <= 6; loc_A ++) {
		Gra_3(33, loc_A, 3,      81, pTitle, 86 - loc_A, -1, 3);
		Gra_3(33, loc_A, 3, 93 - loc_A, pTitle,      86, -1, 3);
		Anim_Delay((long)4000);
	}
	/*open view like scroll*/
	for(loc_A = 1; loc_A <= 20; loc_A ++) {
		if(u_kbhit())
			loc_A = 20;

		loc_C = 20 - loc_A;
		Gra_3(loc_A * 2, 96, loc_C, 96, pTitle, 96, -1, loc_C);
		C_034D();
		Gra_C(5, 19, D_3683, 104, pTitle, 2);

		Anim_Delay((long)2000);
	}
	_ffree(pTitle);

	/*the 2 "monsters"*/
/*C_0978:*/
	if((pAnim = (void far *)_fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x37);
	Gra_inflate((D_7078 == 1)?/*D_00D7*/"ANIMATE.PIC":/*D_00E3*/"ANIMATE.EGA", pAnim);
	for(loc_A = 1; loc_A <= 32; loc_A++) {
/*C_09C4:*/
		if(u_kbhit())
			loc_A = 32;

		/*the "2 monsters"*/
		loc_C = D_3380[D_0036++]; D_0036 &= 0x7f;
		Gra_3(6, loc_A, D_344A[loc_C], D_3438[loc_C] - loc_A + 32, pAnim, 0, -1, 0);
		loc_C = D_33F8[D_0038++]; D_0038 &= 0x3f;
		Gra_3(6, loc_A, D_345C[loc_C], D_3438[loc_C] - loc_A + 32, pAnim, 0, -1, 34);

		/*the "view"*/
		C_034D();
		C_041A();
		Gra_0(5, 19, D_3A24, 104, 0, 0, 2);
		for(loc_B = speed_info / 16; loc_B && !u_kbhit(); loc_B --)
			Gra_0(5, 19, D_3A24, 104, 0, 0, 2);

		Anim_Delay((long)2000);
	}
}

PutTextAt(int y, int x, char* text)
{
	unsigned int code;

	u4_SetTextCoordYX(y, x);
	while(*text) {
		code = (unsigned char)*text++;
		if (code & 0x80) {
			code = (code << 8) | (unsigned char)*text++;
		}
		u4_putc(code);
	}
}

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

C_0B45()
{
	Gra_2();
	PutTextCenter(14, U4TEXT_TITLE_0_297);

	PutTextAt(16, 17, /*D_0114*/U4TEXT_TITLE_0_298);
	PutTextAt(17, 13, /*D_011D*/U4TEXT_TITLE_0_299);
	PutTextAt(18, 13, /*D_0130*/U4TEXT_TITLE_0_300);
	PutTextAt(19, 13, /*D_013F*/U4TEXT_TITLE_0_301);

	PutTextCenter(21, U4TEXT_TITLE_0_302);
	PutTextCenter(22, U4TEXT_TITLE_0_303);

	u4_SetTextCoord(24, 16);
	D_31C0 = 1;
}

C_0BCA()
{
	int bp_02;

	Gra_clrscr();
	if((pShapes = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x3a);
	if(D_7078 == 1) {
		if(Load(/*D_0191*/"SHAPES.CGA", 0x4000, pShapes) == -1)
			Exit(5);
	} else {
		C_217E(/*D_019C*/"SHAPES.EGZ", pShapes);
		sizzleShapes();
	}

	if((pTitle = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x3b);
	Gra_inflate((D_7078 == 1)?/*D_01A7*/"TITLE.PIC":/*D_01B1*/"TITLE.EGA", pTitle);
	Anim_LordBritish(0);
	Gra_3(4, 4, 19, 17, pTitle, 17, -1, 19);
	for(bp_02 = 86; bp_02 < 238; bp_02 ++)
		Gra_dot(31, bp_02, 2);
	Gra_3(21,  9,  9, 21, pTitle, 21, -1, 9);
	Gra_3(30, 45,  5, 34, pTitle, 34, -1, 5);
	Gra_3(15,  5, 14,  0, pTitle, 33, -1, 14);
	Gra_3(33,  6,  3, 81, pTitle, 80, -1, 3);
	Gra_3(33,  6,  3, 87, pTitle, 86, -1, 3);
	Gra_3(40, 96,  0, 96, pTitle, 96, -1, 0);
	_ffree(pTitle);

	if((pAnim = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x3b);
	Gra_inflate((D_7078 == 1)?/*D_01BB*/"ANIMATE.PIC":/*D_01C7*/"ANIMATE.EGA", pAnim);

	bp_02 = D_3380[D_0036++]; D_0036 &= 0x7f;
	Gra_3(6, 32, D_344A[bp_02], D_3438[bp_02], pAnim, 0, -1, 0);
	bp_02 = D_33F8[D_0038++]; D_0038 &= 0x3f;
	Gra_3(6, 32, D_345C[bp_02], D_3438[bp_02], pAnim, 0, -1, 34);

	D_6E80 = 1;
	C_0B45();
}

cdecl /*C_0EAA*/main()
{
	D_31C0 = 0;
	low_init();

	InitializeTimer();

	u4_toupper(far_psp->_80[4]);
	u4_toupper(far_psp->_80[2]);
	/*set drive number*/
	if(far_psp->_80[0] < 4) {
		D_7082 = ((equip_flags & 0xc0) >> 6) != 0;
	} else if(far_psp->_80[4] == '0') {
		D_7082 = 0;
	} else if(far_psp->_80[4] == '1') {
		D_7082 = 1;
	} else {
		D_7082 = ((equip_flags & 0xc0) >> 6) != 0;
	}
	/*set graphic type*/
	if(far_psp->_80[0] < 2) {
		D_7078 = low_gra();
	} else if(far_psp->_80[2] == 'C') {
		D_7078 = 1;
	} else if(far_psp->_80[2] == 'E') {
		D_7078 = 2;
	} else if(far_psp->_80[2] == 'T') {
		D_7078 = 3;
	} else {
		D_7078 = low_gra();
	}
	if(D_7078 == -1) {
		Console(/*D_01D3*/"I can't find a color graphics card.\r\n");
		Exit(2);
	}

	/* CDDA */
	CdCheckMscdex();
	CdRequestAudioDiskInfo();

	/* */
	D_6E80 = 0;
	if((pCharset = _fmalloc((D_7078 == 1)?0x1400:0x5900)) == 0)
		Exit(0x3c);
	if(Load((D_7078 == 1)?/*D_01F9*/"CHARSET.CGA":/*D_0205*/"CHARSET.EGA", (D_7078 == 1)?0x1400:0x5900, pCharset) == -1)
		Exit(6);
	if((pShapes = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x3d);
	if(D_7078 == 1) {
		if(Load(/*D_0211*/"SHAPES.CGA", 0x4000, pShapes) == -1)
			Exit(5);
	} else {
		C_217E(/*D_021C*/"SHAPES.EGZ", pShapes);
	}
	Gra_init();
	C_331E();/*set int 24h handler*/

	if((pTitle = _fmalloc((D_7078 == 1)?0x4000:0x8000)) == 0)
		Exit(0x3e);
	Gra_inflate((D_7078 == 1)?/*D_0227*/"TITLE.PIC":/**D_0231*/"TITLE.EGA", pTitle);
	if(D_7078 == 1)
		speed_info ++;
	D_3A84 = 0;
	C_068C();/*logo + splash + animation*/

	/* CDDA */
	CdPlayLoopAudio(1);

	D_6E80 = 1;
/*C_10E2:*/
	C_05A4();
	C_0B45();
	do {
		int bp_02;

/*C_10E8:*/
		bp_02 = u_kbread();
		if(u4_isupper((unsigned char)bp_02))
			bp_02 = (bp_02 & 0xff00) | u4_lower((unsigned char)bp_02);
		if((unsigned char)bp_02 > ' ' && ((unsigned char)bp_02 & 0x80) == 0)
			Gra_putchar((unsigned char)bp_02);
		switch(bp_02) {
			case KBD_R:/*(R)eturn*/
				C_05A4();
				C_0B45();
			break;
			case KBD_I:/*(I)nitiate*/
				C_3030();
				C_0BCA();
			break;
			case KBD_J:/*(J)ourney*/
				/* CDDA */
				CdStopAudio();
				_ffree(pAnim);
				_ffree(pShapes);
				_ffree(pCharset);
				low_clean();
				Exit(D_7082?'1':'0');
			break;
			default:
				sound_1();
			break;
		}
	} while(1);
}
