/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>
#include "u4_i18n.h"

typedef tHandler_tlk();
typedef tHandler_tlk *pHandler_tlk;

TLK_name();
TLK_look();
TLK_job();
TLK_health();
TLK_special1();
TLK_special2();
TLK_join();
TLK_give();

char D_2A7A[] = U4TEXT_TALK_24;

#define TLK_HANDLER_COUNT 9

#define TLK_HANDLER_SPECIAL1 5
#define TLK_HANDLER_SPECIAL2 6

struct {
	char* _text[4];
	pHandler_tlk _handler;
} D_2A90_tlkHandler[TLK_HANDLER_COUNT] = {
	{{/*D_2A3E*/U4TEXT_TALK_30, U4TEXT_K_TALK_BYE, 0, 0}, 0},
	{{/*D_2A42*/U4TEXT_TALK_31, U4TEXT_K_TALK_NAME, 0, 0},     TLK_name},
	{{/*D_2A47*/U4TEXT_TALK_32, U4TEXT_K_TALK_LOOK, 0, 0},     TLK_look},
	{{/*D_2A4C*/U4TEXT_TALK_33, U4TEXT_K_TALK_JOB, 0, 0},       TLK_job},
	{{/*D_2A50*/U4TEXT_TALK_34, U4TEXT_K_TALK_HEALTH, 0, 0}, TLK_health},
	{{0, 0, 0, 0}, TLK_special1},
	{{0, 0, 0, 0}, TLK_special2},
	{{/*D_2A57*/U4TEXT_TALK_37, U4TEXT_K_TALK_JOIN, 0, 0},     TLK_join},
	{{/*D_2A5C*/U4TEXT_TALK_38, U4TEXT_K_TALK_GIVE, 0, 0},     TLK_give},
};

#define TLK_DATA_QUESTIONFLAG 0
#define TLK_DATA_QUESTIONTYPE 1
#define TLK_DATA_TURNAWAYPROB 2
#define TLK_DATA_TALK 3

/*D_8CCE:
	0.name
	1.pronoun
	2.look
	3.job
	4.health
	5.personnal answer1
	6.personnal answer2
	7.special question
	8.special answer Y
	9.special answer N
	10.personnal question1
	11.personnal question2*/
#define TLK_LEN 21
static char *D_8CCE[TLK_LEN];

#define TLK_NAME 0
#define TLK_PRONOUN 1
#define TLK_LOOK 2
#define TLK_JOB 3
#define TLK_HEALTH 4
#define TLK_ANSWER1 5
#define TLK_ANSWER2 6
#define TLK_SPECIAL 7
#define TLK_SPECIALANS1 8
#define TLK_SPECIALANS2 9

#define TLK_QUESTION1 10
#define TLK_QUESTION1EX1 11
#define TLK_QUESTION1EX2 12
#define TLK_QUESTION1EX3 13

#define TLK_QUESTION2 14
#define TLK_QUESTION2EX1 15
#define TLK_QUESTION2EX2 16
#define TLK_QUESTION2EX3 17

#define TLK_BYE 18
#define TLK_UNKNOWN 19
#define TLK_GIVE 20

extern int enableInputMethod;

/*special question*/
C_A163()
{
	int ch;

	Gra_CR();
	u_kbread();
	u4_puts(D_8CCE[TLK_SPECIAL]);
	u4_puts(/*D_2A62*/U4TEXT_TALK_65);
	do {
		ch = AskY_N();

		if (ch == ' ' || ch == '\r')
			return;

		if(ch != 'N' && ch != 'Y')
			u4_puts(/*D_2A6E*/U4TEXT_TALK_73);

	} while(ch != 'N' && ch != 'Y');

	if(ch == 'Y') {
		if(D_95CE[TLK_DATA_QUESTIONTYPE])
			karma_dec(&(Party._humil), 5);
		u4_puts(D_8CCE[TLK_SPECIALANS1]);
	} else {
		if(D_95CE[TLK_DATA_QUESTIONTYPE] && (Party._moves >> 4) != Party.f_1ec)
			karma_inc(&(Party._humil), 10);
		u4_puts(D_8CCE[TLK_SPECIALANS2]);
	}
	Party.f_1ec = (Party._moves >> 4);
	Gra_CR();
}

C_A22D(bp06, bp04)
int bp06;
char *bp04;
{
	if(!bp04)
		return;
	u4_puts(bp04);
	Gra_CR();
}

/*C_A245*/TLK_special1()
{
	C_A22D(6, D_8CCE[TLK_ANSWER1]);
}

/*C_A253*/TLK_special2()
{
	C_A22D(7, D_8CCE[TLK_ANSWER2]);
}

/*C_A261*/TLK_name()
{
	u4_puts(D_8CCE[TLK_PRONOUN]);
	u4_puts(/*D_2AB8*/U4TEXT_TALK_126);
	u4_puts(D_8CCE[TLK_NAME]);
	Gra_CR();
}

/*C_A280*/TLK_look()
{
	u4_puts(/*D_2AC5*/U4TEXT_TALK_133);
	C_A22D(3, D_8CCE[TLK_LOOK]);
}

/*C_A299*/TLK_job()
{
	C_A22D(4, D_8CCE[TLK_JOB]);
}

/*C_A2AB*/TLK_health()
{
	C_A22D(5, D_8CCE[TLK_HEALTH]);
}

char *D_2BB2[] = {
	/*D_2ACE*/U4TEXT_TALK_148,
	/*D_2AD5*/U4TEXT_TALK_149,
	/*D_2AE3*/U4TEXT_TALK_150,
	/*D_2AEB*/U4TEXT_TALK_151,
	/*D_2AF0*/U4TEXT_TALK_152,
	/*D_2AFC*/U4TEXT_TALK_153,
	/*D_2B06*/U4TEXT_TALK_154,
	/*D_2B10*/U4TEXT_TALK_155
};

char* cantJoin[] = {
	U4TEXT_K_TALK_MARRIAH_CANT_JOIN,
	U4TEXT_K_TALK_IOLO_CANT_JOIN,
	U4TEXT_K_TALK_JEFFERY_CANT_JOIN,
	U4TEXT_K_TALK_JAANA_CANT_JOIN,
	U4TEXT_K_TALK_JULIA_CANT_JOIN,
	U4TEXT_K_TALK_DUPRE_CANT_JOIN,
	U4TEXT_K_TALK_SHAMINO_CANT_JOIN,
	U4TEXT_K_TALK_KATRINA_CANT_JOIN
};

char* willJoin[] = {
	U4TEXT_K_TALK_MARRIAH_WILL_JOIN,
	U4TEXT_K_TALK_IOLO_WILL_JOIN,
	U4TEXT_K_TALK_JEFFERY_WILL_JOIN,
	U4TEXT_K_TALK_JAANA_WILL_JOIN,
	U4TEXT_K_TALK_JULIA_WILL_JOIN,
	U4TEXT_K_TALK_DUPRE_WILL_JOIN,
	U4TEXT_K_TALK_SHAMINO_WILL_JOIN,
	U4TEXT_K_TALK_KATRINA_WILL_JOIN
};

static unsigned D_8CE6;/*type?*/

w_CantJoin(npcId)
unsigned int npcId;
{
	if (npcId >= 0 && npcId <= 7)
		u4_puts(cantJoin[npcId]);
	else
		u4_puts(U4TEXT_TALK_176);
}

/*C_A2BD*/TLK_join()
{
	int bp_02;

	unsigned int npcClass = Party._loc - 5;

	if (D_8742._npc._tlkidx[D_8CE6] != 1 || npcClass >= 8) {
		u4_puts(D_8CCE[TLK_PRONOUN]);
		u4_puts(U4TEXT_TALK_170);
		return;
	}
	if (npcClass == Party.chara[0]._class) {
		u4_puts(D_8CCE[TLK_PRONOUN]);
		u4_puts(U4TEXT_K_TALK_SAME_CLASS);
		w_CantJoin(npcClass);
		return;
	}
	if(*pKarmas[npcClass] < 40 && *pKarmas[npcClass] != 0) {
		u4_puts(U4TEXT_TALK_174);
		u4_puts(D_2BB2[npcClass]);
		w_CantJoin(npcClass);
		return;
	}
	if(100 * Party.party_size + 100 > Party.chara[0]._HP[1]) {
		u4_puts(U4TEXT_TALK_180);
		w_CantJoin(npcClass);
		return;
	}

	u4_puts(willJoin[npcClass]);

	D_8742._npc._tile[31] =
	D_8742._npc._gtile[31] =
	D_8742._npc._var[31] =
	D_8742._npc._tlkidx[31] = 0;
	t_callback();
	for(bp_02 = 7; bp_02 >= 0; bp_02 --) {
		if(Party.chara[bp_02]._class == npcClass)
			break;
	}
	if(bp_02 != -1)
		C_6FF9(&(Party.chara[Party.party_size]), &(Party.chara[bp_02]));
	Party.party_size ++;
	Gra_13();
	dspl_Stats();
}

/*C_A3A2*/TLK_give()
{
	int bp_02;

	if(D_8742._npc._tile[D_8CE6] != TIL_58) {
		if (D_8CCE[TLK_GIVE][0])
			u4_puts(D_8CCE[TLK_GIVE]);
		else {
			u4_puts(D_8CCE[TLK_PRONOUN]);
			u4_puts(/*D_2BC2*/U4TEXT_TALK_206);
		}
		return;
	}
	u4_puts(/*D_2BEC*/U4TEXT_TALK_209);
	if((bp_02 = AskInt(2)) > 0) {
		if(Party._gold < bp_02) {
			u4_puts(/*D_2BFB*/U4TEXT_TALK_212);
		} else {
			Party._gold -= bp_02;
			dspl_Stats();
			u4_puts(D_8CCE[TLK_PRONOUN]);
			u4_puts(/*D_2C1A*/U4TEXT_TALK_217);
			if((Party._moves >> 4) != Party.f_1ec)
				karma_inc(&(Party._compa), 2);
			Party.f_1ec = Party._moves >> 4;
		}
	}
	C_A22D(6, 0);
}

/*parse talk info*/
C_A443(si/*bp04*/)
register char *si;
{
	register char **di;

	for(di = &(D_8CCE[0]); di != &(D_8CCE[TLK_LEN]); ) {
		*(di++) = si;
		while(*(si++));
	}
#if 0
	u4_tolower(D_8CCE[NPC_LOOK][0]);
#endif
}

C_A47F(bp04)
char *bp04;
{
	char *bp_02;

	for(bp_02 = strchr(bp04, 0) - 1; bp_02 + 1 != bp04 && *bp_02 == ' '; )
		*(bp_02--) = 0;
}

/*talk to citizen*/
C_A4B4(bp04)
int bp04;
{
	int bye, bp_04;
	register int i;

	dlseek(File_TLK, (D_8742._npc._tlkidx[bp04] - 1) * 0x180);
	dread(File_TLK, D_95CE, 0x180);
	bp_04 = Party.party_size;
	D_9452 = D_8742._npc._tile[bp04];
	C_A443(D_95CE + TLK_DATA_TALK);
	/*personnal question 1 & 2*/
#if 0
	for (h = 0; h < 2; h++)
	{
		for (i = 0; i < 4; i++)
		{
			D_2A90[h + TLK_HANDLER_SPECIAL1]._text[i] = D_8CCE[h * 4 + i + TLK_QUESTION1];
			C_A47F(D_2A90[h + TLK_HANDLER_SPECIAL1]._text[i]);
		}
	}
#else
	for (i = 0; i < 8; i++)
	{
		int h = (i >> 2) + TLK_HANDLER_SPECIAL1;
		D_2A90_tlkHandler[h]._text[i & 3] = D_8CCE[i + TLK_QUESTION1];
		C_A47F(D_2A90_tlkHandler[h]._text[i & 3]);
	}
#endif

	C_A22D(3, D_8CCE[TLK_LOOK]);
	/*randomly says his name*/
	if(U4_RND1(1)) {
		Gra_CR();
		u4_puts(D_8CCE[TLK_PRONOUN]);
		u4_puts(/*D_2C60*/U4TEXT_TALK_271);
		u4_puts(D_8CCE[TLK_NAME]);
		Gra_CR();
	}
	bye = 0;
	do {
		register int si;
		char bp_12[12];

		u4_puts(/*D_2C6D*/U4TEXT_TALK_280);
		u4_gets(bp_12, 11);
		Gra_CR();
		Gra_CR();
		if(bp_12[0] == 0)
			break;
		if((si = u_rand_a()) < D_95CE[TLK_DATA_TURNAWAYPROB]) {
			u4_puts(D_8CCE[TLK_PRONOUN]);
			if(D_95CE[TLK_DATA_TURNAWAYPROB] - si >= 0x40) {
				/*he/she gets upset*/
#if 0
				if(strnicmp(D_8CCE[TLK_NAME], /*D_2C7E*/U4TEXT_TALK_288_1, 2) && strnicmp(D_8CCE[TLK_NAME], /*D_2C81*/U4TEXT_TALK_288_2, 4))
					u4_puts(D_8CCE[TLK_NAME]);
				else
					u4_puts(D_8CCE[TLK_PRONOUN]);
#endif
				u4_puts(/*D_2C86*/U4TEXT_TALK_292);
				D_8742._npc._var[bp04] = 0xff;
			} else {
#if 0
				u4_puts(D_8CCE[TLK_PRONOUN]);
#endif
				u4_puts(/*D_2C9E*/U4TEXT_TALK_296);
			}
			return;
		}
		for(si = 0; si < TLK_HANDLER_COUNT; si++) {
			register int tx;
			for (tx = 0; tx < 4; tx++)
			{
				if (!D_2A90_tlkHandler[si]._text[tx])
					continue;

				if (strnicmp(D_2A90_tlkHandler[si]._text[tx], bp_12, 4) == 0) {
					if (D_2A90_tlkHandler[si]._handler) {
						D_8CE6 = bp04;
						(*(D_2A90_tlkHandler[si]._handler))();
						if (Party.party_size != bp_04)
							return;/*looks like he/she has joined*/
					}
					else {
						bye = 1;
					}
					if (!bye) {
						if (D_95CE[TLK_DATA_QUESTIONFLAG] == si)
							C_A163();
					}
					goto EXIT;
				}
			}
		}
EXIT:
		if (si == TLK_HANDLER_COUNT) {
			if (D_8CCE[TLK_UNKNOWN][0])
				u4_puts(D_8CCE[TLK_UNKNOWN]);
			else
				u4_puts(/*D_2CAD*/U4TEXT_TALK_319);
		}
	} while(bye == 0);
	
	if (D_8CCE[TLK_BYE][0])
		u4_puts(D_8CCE[TLK_BYE]);
	else
		u4_puts(/*D_2CCC*/U4TEXT_TALK_321);
}

/*shops'y positions by town*/
unsigned char D_2CD4[][8] = {
	{0x00,0x00,0x00,0x00,0x00,0x1A,0x00,0x00},/*LB*/

	{0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00},/*lycaeum*/
	{0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00},/*empath*/
	{0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00},/*serpent*/

	{0x00,0x00,0x0E,0x00,0x1A,0x1B,0x02,0x00},/*MOONGLOW*/
	{0x03,0x07,0x06,0x02,0x00,0x1D,0x0C,0x00},/*BRITAIN*/
	{0x09,0x05,0x00,0x13,0x00,0x06,0x1A,0x00},/*JHELOM*/
	{0x00,0x00,0x18,0x00,0x00,0x19,0x00,0x00},/*YEW.ULT*/
	{0x1C,0x00,0x00,0x00,0x00,0x00,0x03,0x00},/*MINOC*/
	{0x14,0x18,0x00,0x02,0x00,0x00,0x03,0x00},/*TRINSIC*/
	{0x00,0x00,0x11,0x00,0x04,0x1B,0x0D,0x00},/*SKARA*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*MAGINCIA*/

	{0x00,0x04,0x1A,0x05,0x07,0x00,0x00,0x00},/*paws*/
	{0x0B,0x11,0x00,0x19,0x08,0x00,0x00,0x07},/*den*/
	{0x14,0x00,0x00,0x16,0x00,0x00,0x15,0x1A},/*vesper*/
	{0x00,0x00,0x00,0x00,0x00,0x1A,0x00,0x00} /*cove*/
};

extern SHP_weapon();
extern SHP_armor();
extern SHP_food();
extern SHP_pub();
extern SHP_reagent();
extern SHP_healer();
extern SHP_inn();
extern SHP_guild();
extern SHP_horse();
extern SHP_hawkwind();

/*shops functions callbacks*/
pHandler_tlk D_2D54[] = {
	SHP_weapon,
	SHP_armor,
	SHP_food,
	SHP_pub,
	SHP_reagent,
	SHP_healer,
	SHP_inn,
	SHP_guild,

	SHP_horse,
	SHP_hawkwind
};

/*shop at Y*/
C_A686(bp04)
unsigned char bp04;
{
	register int si;

	for(si = 7; si >= 0;si--) {
		if(D_2CD4[Party._loc - 1][si] == bp04)
			break;
	}
	if(si == -1 && bp04 == 0x18 && Party._loc == 0x0d)
		si = 8;/*patch! paws' horses*/
	if(si == -1 && bp04 == 0x19 && Party._loc == 0x01)
		si = 9;/*patch! LB's hawkwind*/
	if(si == -1) {
		u4_puts(D_2A7A);
		return;
	}
	musici(U4_MUS_SHOPPING);
	(*(D_2D54[si]))();
	music();
}

/*C_A6F3*/CMD_Talk() {
	unsigned char loc_A, loc_E;
	int loc_B, loc_C, loc_D;

	u4_puts(/*D_2D68*/U4TEXT_TALK_398);
	if(Party.f_1dc != 0) {
		w_DriftOnly();
		return;
	}
	AskDir(/*D_2D6E*/U4TEXT_TALK_403, &loc_B, &loc_D);
	if(!(loc_B | loc_D))
		return;
	loc_E = Party._x + loc_B;
	loc_A = Party._y + loc_D;
	loc_C = C_0A8B(loc_E, loc_A);
	if(loc_E > 31 || loc_A > 31 || Party._loc == 0) {
		u4_puts(D_2A7A);
		return;
	}
	if(
		D_8742._map.x32x32[loc_A][loc_E] >= TIL_60 &&
		D_8742._map.x32x32[loc_A][loc_E] <= TIL_7E
	) {/*alphabet*/
		loc_E += loc_B;
		loc_A += loc_D;
		if(loc_E > 31 || loc_A > 31) {
			u4_puts(D_2A7A);
			return;
		}
		if((loc_C = C_0A8B(loc_E, loc_A)) == -1 || D_8742._npc._tile[loc_C] != TIL_52) {
			u4_puts(D_2A7A);
			return;
		}
		C_A686(loc_A - loc_D);
		return;
	}
	if(loc_C == -1 || D_8742._npc._tlkidx[loc_C] == 0) {
		u4_puts(D_2A7A);
		return;
	}
	if(D_8742._npc._tile[loc_C] == TIL_5E) {
		C_E59B();
		return;
	}
	C_A4B4(loc_C);
}
