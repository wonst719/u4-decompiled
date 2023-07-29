/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#define RG_ash        (0x80>>0)
#define RG_ginseng    (0x80>>1)
#define RG_garlic     (0x80>>2)
#define RG_spiderSilk (0x80>>3)
#define RG_bloodMoss  (0x80>>4)
#define RG_blackPearl (0x80>>5)
#define RG_nightshade (0x80>>6)
#define RG_mandrake   (0x80>>7)

unsigned char D_277E[] = {
	/*A*/RG_ginseng|RG_garlic,
	/*B*/RG_spiderSilk|RG_bloodMoss,
	/*C*/RG_ginseng|RG_garlic,
	/*D*/RG_ash|RG_garlic|RG_blackPearl,
	/*E*/RG_ash|RG_spiderSilk|RG_blackPearl,
	/*F*/RG_ash|RG_blackPearl,
	/*G*/RG_ash|RG_blackPearl|RG_mandrake,
	/*H*/RG_ginseng|RG_spiderSilk,
	/*I*/RG_blackPearl|RG_mandrake,
	/*J*/RG_blackPearl|RG_nightshade|RG_mandrake,
	/*K*/RG_blackPearl|RG_nightshade,
	/*L*/RG_ash,
	/*M*/RG_ash|RG_blackPearl,
	/*N*/RG_ash|RG_garlic|RG_mandrake,
	/*O*/RG_ash|RG_bloodMoss,
	/*P*/RG_ash|RG_ginseng|RG_garlic,
	/*Q*/RG_ash|RG_ginseng|RG_bloodMoss,
	/*R*/RG_ash|RG_ginseng|RG_garlic|RG_spiderSilk|RG_bloodMoss|RG_mandrake,
	/*S*/RG_ginseng|RG_spiderSilk,
	/*T*/RG_ash|RG_bloodMoss|RG_mandrake,
	/*U*/RG_ash|RG_garlic,
	/*V*/RG_nightshade|RG_mandrake,
	/*W*/RG_ash|RG_bloodMoss,
	/*X*/RG_ash|RG_spiderSilk|RG_bloodMoss,
	/*Y*/RG_spiderSilk|RG_bloodMoss,
	/*Z*/RG_spiderSilk|RG_bloodMoss
};

/*C_8C08*/CMD_Mix()
{
	register int si;
	unsigned char loc_A[8];
	int  loc_B, loc_C, loc_D;
	char loc_E;

	loc_D = 0;
	do {
		Gra_13();
		C_4649();
		loc_B = txt_X;
		loc_C = txt_Y;
		Z_Mixtures();
		txt_X = loc_B;
		txt_Y = loc_C;
		u4_puts(/*D_270C*/U4TEXT_MIX_60);
		if((loc_C = AskLetter(/*D_271A*/U4TEXT_MIX_61, 'A', 'Z')) < 0)
			break;
		loc_C -= 'A';
		u4_puts(Strings[101 + loc_C]);
		Gra_CR();
		Gra_13();
		C_4649();
		for(si = 7; si >= 0; si --)
			loc_A[si] = Party._reagents[si];
		loc_E = 0;
		while(1) {
			Z_Reagents();
			u4_SetTextCoordYX(23, 24);
			if((loc_B = AskLetter(/*D_2728*/U4TEXT_MIX_74, 'A', 'H')) == -2) {
				for(si = 7; si >= 0; si --)
					Party._reagents[si] = loc_A[si];
				loc_D = 1;
				break;
			}
			if(loc_B == -1) {
				if(loc_E == 0) {
					u4_puts(/*D_2734*/U4TEXT_MIX_82);
				} else {
					u4_puts(/*D_2745*/U4TEXT_MIX_84);
					loc_B = 0;
					if(D_277E[loc_C] == loc_E) {
						u4_puts(/*D_2764*/U4TEXT_MIX_87);
						Party._mixtures[loc_C] ++;
						if(Party._mixtures[loc_C] > 99)
							Party._mixtures[loc_C] = 99;
					} else {
						u4_puts(/*D_276F*/U4TEXT_MIX_92);
					}
				}
				break;
			}
			loc_B -= 'A';
			if(Party._reagents[loc_B] == 0) {
				w_NoneLeft();
				break;
			}
			loc_E |= 0x80 >> loc_B;
			Party._reagents[loc_B] --;
		}
	} while(loc_D == 0);
	Gra_13();
	C_4649();
	dspl_Stats();
}
