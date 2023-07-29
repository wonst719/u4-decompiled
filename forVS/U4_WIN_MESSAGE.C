#include "u4.h"
#include "common.h"

#include <SDL2/SDL.h>

int __cdecl u_kbhit()
{
	CONSOLE("u_kbhit\n");
	CMN_pumpmessages();
	Party.f_000++;

	return CMN_kbhit != 0;
}

int __cdecl u_kbread()
{
	int ret;

	CONSOLE("u_kbread\n");
	//	u_delay(0x8081, 0x8081);
	while (u_kbhit() == 0)
		CMN_pumpmessages();
	ret = CMN_kbhit;
	CMN_kbhit = 0;

	return ret;
}

void __cdecl u_kbflush()
{
	CONSOLE("u_kbflush\n");
	CMN_kbhit = 0;
}

int __cdecl u_kbflag()
{
	return SDL_GetModState();
}

void __cdecl u_kbcheck(int* a)
{
	return 0;
}

void __cdecl u_delay(int a, int b)
{
	CONSOLE("u_delay(%d, %d)\n", a, b);
	if (a == 0)
		a = 1000;
	a *= 50;
	while (a) {
		a--;
		t_callback();
		CMN_pumpmessages();
		SDL_Delay(10);
		if (b && u_kbhit())
			break;
		//cursor
		Gra_putchar(0x1c + (~a & 3));
	}
}
