#include <dos.h>
#include <stdlib.h>

#define PIT_FREQUENCY 1193181

#define PIT_BINARY 0

/* Mode 0: Interrupt on Terminal Count */
#define PIT_MODE_0 (0 << 1)
/* Mode 1: Programmable one-shot */
#define PIT_MODE_1 (1 << 1)
/* Mode 2: Rate Generator */
#define PIT_MODE_2 (2 << 1)
/* Mode 3: Square Wave Generator */
#define PIT_MODE_3 (3 << 1)
/* Mode 4 */
#define PIT_MODE_4 (4 << 1)
/* Mode 5 */
#define PIT_MODE_5 (5 << 1)

/* Access Mode 0: Latch Count Value */
#define PIT_RL_0 (0 << 4)
/* Access Mode 1: Lobyte */
#define PIT_RL_1 (1 << 4)
/* Access Mode 2: Hibyte */
#define PIT_RL_2 (2 << 4)
/* Access Mode 3: Lobyte/Hibyte */
#define PIT_RL_3 (3 << 4)

/* Channel 0 */
#define PIT_SC_0 (0 << 6)
/* Channel 1 */
#define PIT_SC_1 (1 << 6)
/* Channel 2 */
#define PIT_SC_2 (2 << 6)

/* 0.549 ms */
#define TICK_FREQUENCY (182*10)

#ifdef WIN32
#define interrupt
#define far
#endif

typedef void (interrupt far* InterruptHandler)();

#ifdef WIN32
void _dos_setvect(int a, InterruptHandler b)
{
}

InterruptHandler _dos_getvect(int a)
{
	return 0;
}
#endif

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

void u4_sleep(unsigned int ms)
{
	unsigned long tick = GetTickCounter();
	tick += (unsigned long)ms * TICK_FREQUENCY / 1000;

	while (tick > GetTickCounter())
	{
		/* nop */
	}
}

void u4_sleep_tick(unsigned int waitTick)
{
	unsigned long tick = GetTickCounter();
	tick += waitTick;

	while (tick > GetTickCounter())
	{
		/* nop */
	}
}
