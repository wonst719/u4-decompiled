#include <dos.h>
#include <stdlib.h>

#include "u4_timer.h"

typedef unsigned char byte;
typedef unsigned int word;

extern int speed_info;

void out_61(byte val)
{
	_asm mov al, val
	_asm out 0x61, al
}

byte in_61()
{
	byte val;

	_asm in al, 0x61
	_asm mov val, al

	return val;
}

#define outm_61(x) do { \
	_asm mov ax, x \
	_asm out 0x61, al \
} while (0)

#define r_high(x) do { \
	x &= 0xfc; \
	x ^= 2; \
} while (0)

#define r_low(x) do { \
	x &= 0xfc; \
} while (0)

#define r_flip(x) do { \
	x ^= 2; \
} while (0)

#define speaker_high(x) do { \
	r_high(x); \
	outm_61(x); \
} while(0)

#define speaker_low(x) do { \
	r_low(x); \
	outm_61(x); \
} while(0)

#define speaker_flip(x) do { \
	r_flip(x); \
	outm_61(x); \
} while(0)

// foot
void sound_0()
{
	register int wait;
	register word r;

	byte sav;

	r = sav = in_61();

	speaker_high(r);

	wait = 0x32;
	while (wait != 0)
		wait--;

	speaker_flip(r);

	out_61(sav);
}

/* square wave (mid/low) */
void sound_1()
{
	register word r;
	word wait = speed_info * 202;
	int waita = 16;
	register int waitb;

	byte sav;

	r = sav = in_61();

	r_low(r);

	while (waita != 0)
	{
		outm_61(r);
		r_flip(r);

		waitb = wait;
		while (waitb != 0)
			/* some delay */
			waitb--;

		waita--;
	}

	out_61(sav);
}

/* square wave (high) */
void sound_2()
{
	register word r;
	word wait = speed_info * 224;
	int waita = 48;
	register int waitb;

	byte sav;

	r = sav = in_61();

	while (waita != 0)
	{
		outm_61(r);
		r_flip(r);

		waitb = wait;
		while (waitb != 0)
			waitb--;

		waita--;
	}

	out_61(sav);

	/* chain */
	sound_1();
}
