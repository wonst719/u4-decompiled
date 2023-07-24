#include <dos.h>
#include <stdlib.h>

#include "u4_timer.h"

typedef unsigned char byte;
typedef unsigned int word;

extern int speed_info;

char cdecl SoundFlag = 0;

static void SpeakerOn(word pitFreqDivider)
{
	_asm {
		mov ax, pitFreqDivider
		and ax, 0xfffe

		push ax

		cli

		/* Set PIT mode to square wave generator */
		mov al, PIT_SC_2 | PIT_RL_3 | PIT_MODE_3 | PIT_BINARY
		out 0x43, al

		/* Set frequency divider lo */
		pop ax
		out 0x42, al

		/* Set frequency divider hi */
		mov al, ah
		out 0x42, al

		/* get PPI state */
		in  al, 0x61

		/* start generating sound */
		mov al, ah
		or al, 3
		out 0x61, al

		sti
	}
}

static void SpeakerOff()
{
	_asm {
		/* stop generating sound */
		in al, 0x61
		and al, 0xfc
		out 0x61, al
	}
}

static void SpeakerSetFreq(word pitFreqDivider)
{
	_asm {
		mov ax, pitFreqDivider
		and ax, 0xfffe

		cli

		/* Set frequency divider lo */
		out 0x42, al

		/* Set frequency divider hi */
		mov al, ah
		out 0x42, al

		/* get PPI state */
		in  al, 0x61

		sti
	}
}

static void SpeakerBeep(word freq, word duration)
{
	SpeakerOn(PIT_FREQUENCY / freq);
	u4_sleep(duration);
	SpeakerOff();
}

/* footstep */
void sound_0_new()
{
	SpeakerOn(PIT_FREQUENCY / (950 + (rand() & 0x7f)));
	u4_sleep_tick(4);
	SpeakerOff();

	u4_sleep_tick(70);
}

/* beep */
void sound_1_new()
{
	SpeakerBeep(92, 100);
}

/* beep boop */
void sound_2_new()
{
	SpeakerBeep(251, 100);
	SpeakerBeep(92, 100);
}

/* pitch down */
void sound_3_new()
{
	int freqDiv = 20;
	int freqAdd = 60;
	int freqAdd2 = 30;
	SpeakerOn(freqDiv);

	while (freqDiv < 5500)
	{
		freqDiv += (12 + freqAdd + freqAdd2) << 1;
		if (freqAdd > 0)
			freqAdd -= 6;
		if (freqAdd2 > 0)
			freqAdd2 -= 1;

		u4_sleep(2);
		SpeakerSetFreq(freqDiv);
	}

	SpeakerOff();
}

/* pitch up */
void sound_4_new()
{
	int freqDiv = 5810;
	SpeakerOn(freqDiv);

	while (freqDiv > 2780)
	{
		freqDiv -= 50;

		u4_sleep(4);
		SpeakerSetFreq(freqDiv);
	}

	SpeakerOff();
}

/* pitch down slow */
void sound_5_new()
{
	int freqDiv = 4000;
	SpeakerOn(freqDiv);

	while (freqDiv < 8400)
	{
		freqDiv += 53;

		u4_sleep(4);
		SpeakerSetFreq(freqDiv);
	}

	SpeakerOff();
}

/* noise high */
void sound_6_new()
{
	int freq = 440;
	int i;

	SpeakerOn(PIT_FREQUENCY / freq);

	for (i = 0; i < 400; i++)
	{
		freq = rand() % 600 + 575;
		SpeakerSetFreq(PIT_FREQUENCY / freq);
		u4_sleep_tick(1);
	}

	SpeakerOff();
}

/* noise low */
void sound_7_new()
{
	int freq = 440;
	int i;

	SpeakerOn(PIT_FREQUENCY / freq);

	for (i = 0; i < 700; i++)
	{
		freq = rand() % 200 + 335;
		SpeakerSetFreq(PIT_FREQUENCY / freq);
		u4_sleep_tick(1);
	}

	SpeakerOff();
}

/* high pitch up */
void sound_8_new()
{
	int freqDiv = 2700;
	int freqSub = 0;
	SpeakerOn(freqDiv);

	while (freqDiv > 450)
	{
		freqDiv -= 120 + (freqSub >> 4);
		freqSub += 36;

		u4_sleep(2);
		SpeakerSetFreq(freqDiv);
	}

	SpeakerOff();
}

/* moongate */
void sound_9_new(byte param)
{
	/* TODO */
	u4_sleep(1000);
}

/* random pitch */
void sound_10_new(byte duration)
{
	int freq = 440;
	int i;

	SpeakerOn(PIT_FREQUENCY / freq);

	for (i = 0; i < (int)duration * 2; i++)
	{
		freq = rand() % 1200 + 200;
		SpeakerSetFreq(PIT_FREQUENCY / freq);
		u4_sleep_tick(35);
	}

	SpeakerOff();
}

void cdecl sound(int id, byte param)
{
	switch (id)
	{
	case 0: sound_0_new(); break;
	case 1: sound_1_new(); break;
	case 2: sound_2_new(); break;
	case 3: sound_3_new(); break;
	case 4: sound_4_new(); break;
	case 5: sound_5_new(); break;
	case 6: sound_6_new(); break;
	case 7: sound_7_new(); break;
	case 8: sound_8_new(); break;
	case 9: sound_9_new(param); break;
	case 10: sound_10_new(param); break;
	//case 11: sound_11_new(); break;
	//case 12: sound_12_new(); break;
	}
}
