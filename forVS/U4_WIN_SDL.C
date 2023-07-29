#include "u4.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include <SDL2/SDL.h>

#include "common.h"

unsigned speed_info;
unsigned equip_flags;
void far* patch_tandy;
struct t_500 D_8742;
char cdecl SoundFlag;

struct tPSP far* far_psp;

unsigned cursor_rate;

struct tPSP the_psp;

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "imm32.lib")
#endif

low_init()
{
	CONSOLE("low_init\n");
	//TODO
	far_psp = &the_psp;
	the_psp._80[0] =
		the_psp._80[2] =
		the_psp._80[4] = 0;

	speed_info = 1;

	ImmDisableIME(0);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER);

	FAKE_RET;
}

low_clean()
{
	//TODO

	SDL_Quit();

	FAKE_RET;
}

low_gra()
{
	//TODO
	CONSOLE("low_gra\n");

	return 2;
}

/*load gr driver*/
C_20C1(char* fname)
{
	CONSOLE("C_20C1\"load gr driver\"(\"%s\")\n", fname);

	FAKE_RET;
}

/*draw game screen frame*/
C_213B()
{
	int fd;

	CONSOLE("C_213B \"draw game screen frame\"\n");
	fd = _open(U4_ROOT "START.PIC", _O_RDONLY | _O_BINARY);
	if (fd) {
	}

	FAKE_RET;
}

//----------------------------------------

unsigned char u_rand_a()
{
	CONSOLE("u_rand_a\n");

	return rand();
}
unsigned char u_rand_b()
{
	CONSOLE("u_rand_b\n");

	return rand();
}

//----------------------------------------

//current floppy?
unsigned char C_1814() {
	//TODO
	CONSOLE("C_1814\"current floppy?\"//TODO\n");

	return 0;
}
C_181D(unsigned a) {
	//TODO
	FAKE_RET;
}
/*verify some file?*/
C_182F(char* fname) {
	//TODO
	CONSOLE("C_182F(\"%s\")//TODO\n", fname);

	return 1;
}
/*anti-piracy function*/
C_184F() {
	//TODO
	CONSOLE("C_184F\"anti-piracy function\"//TODO\n");

	return 0;
}
C_18A2() {
	//TODO
	CONSOLE("C_18A2//TODO\n");

	FAKE_RET;
}
