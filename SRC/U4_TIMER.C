#include "u4_timer.h"

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void InitializeTimer()
{
	timeBeginPeriod(1);
}

void CleanupTimer()
{
	timeEndPeriod(1);
}

unsigned long GetTickCounter()
{
	return 1;
}

void u4_sleep(unsigned int ms)
{
	Sleep(1);
}

void u4_sleep_tick(unsigned int waitTick)
{
	Sleep(1);
}

#else

#include <dos.h>
#include <stdlib.h>

typedef void (interrupt far* InterruptHandler)();

static volatile unsigned long far _tickCounter;

static InterruptHandler _oldPitInterruptHandler;

static void interrupt far PitInterruptHandler()
{
	_tickCounter++;

	if (_tickCounter % 100 == 0)
	{
		_oldPitInterruptHandler();
	}
	else
	{
		/* EOI */
		_asm mov al, 0x20
		_asm out 0x20, al
	}
}

static void SetPitFreqDivider(unsigned int pitFreqDivider)
{
	_asm {
		mov ax, pitFreqDivider

		push ax
		cli

		/* Set PIT mode to rate generator */
		mov al, PIT_SC_0 | PIT_RL_3 | PIT_MODE_2 | PIT_BINARY
		out 0x43, al

		/* Set frequency divider lo */
		pop ax
		out 0x40, al

		/* Set frequency divider hi */
		mov al, ah
		out 0x40, al

		sti
	}
}

void InitializeTimer()
{
	_oldPitInterruptHandler = _dos_getvect(8);

	_asm cli
	_dos_setvect(8, PitInterruptHandler);
	_asm sti

	SetPitFreqDivider(PIT_FREQUENCY / TICK_FREQUENCY);
}

void CleanupTimer()
{
	/* Restore PIT */
	_asm {
		cli
		mov al, PIT_SC_0 | PIT_RL_3 | PIT_MODE_3 | PIT_BINARY
		out 0x43, al
		xor al, al
		out 0x40, al
		out 0x40, al
		sti
	}

	_asm cli
	_dos_setvect(8, _oldPitInterruptHandler);
	_asm sti
}

unsigned long GetTickCounter()
{
	return _tickCounter;
}

void Halt()
{
	_asm {
		sti
		hlt
	}
}

void u4_sleep(unsigned int ms)
{
	unsigned long tick = GetTickCounter();
	tick += (unsigned long)ms * TICK_FREQUENCY / 1000;

	while (tick > GetTickCounter())
	{
		Halt();
	}
}

void u4_sleep_tick(unsigned int waitTick)
{
	unsigned long tick = GetTickCounter();
	tick += waitTick;

	while (tick > GetTickCounter())
	{
		Halt();
	}
}
#endif
