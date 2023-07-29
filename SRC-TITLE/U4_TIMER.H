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

void InitializeTimer();
void CleanupTimer();
unsigned long GetTickCounter();

void u4_sleep(unsigned int ms);
void u4_sleep_tick(unsigned int waitTick);
