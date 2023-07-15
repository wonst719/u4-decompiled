#include <SDL2/SDL.h>

#include <windows.h>

#include "common.h"

#include "u4_scan.h"

int CMN_kbhit = 0;

static HWND CMN_hwnd = 0;
/*static */HDC currentHDC = 0;
static unsigned char *pShapesWIN = 0;
static unsigned char *pCharsetWIN = 0;

//----------------------------------------
COLORREF U4_PALETTE[4] = {
	RGB(0x1f,0x1f,0x1f),//black
	RGB(0x1f,0xe0,0xe0),//cyan
	RGB(0xe0,0x1f,0xe0),//magenta
	RGB(0xe0,0xe0,0xe0)//white
};

unsigned int U4_PAL_STRETCH[4];
HBRUSH U4_BRUSH[4];
HPEN U4_PEN[4];

void CMN_putpixel(int x, int y, int col) {
}

void CMN_xorpixel(int x, int y, int col) {
	//COLORREF pix = GetPixel(currentHDC, x * RATIO, y * RATIO) ^ U4_PALETTE[col];
}

unsigned char *CMN_getCharsetData(int c) {
	return pCharsetWIN + c * 2 * 8;
}

unsigned char *CMN_getShapeData(int c) {
	return pShapesWIN + c * 4 * 16;
}

void CMN_pumpmessages()
{
	SDL_Event ev;
	if (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			switch (ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_LEFT: CMN_kbhit = KBD_LEFT; break;
			case SDL_SCANCODE_RIGHT: CMN_kbhit = KBD_RIGHT; break;
			case SDL_SCANCODE_UP: CMN_kbhit = KBD_UP; break;
			case SDL_SCANCODE_DOWN: CMN_kbhit = KBD_DOWN; break;

			case SDL_SCANCODE_RETURN: CMN_kbhit = KBD_ENTER; break;
			case SDL_SCANCODE_ESCAPE: CMN_kbhit = KBD_ESC; break;
			case SDL_SCANCODE_SPACE: CMN_kbhit = KBD_SPACE; break;
			case SDL_SCANCODE_BACKSPACE: CMN_kbhit = KBD_BS; break;

			case SDL_SCANCODE_A: CMN_kbhit = KBD_A; break;
			case SDL_SCANCODE_B: CMN_kbhit = KBD_B; break;
			case SDL_SCANCODE_C: CMN_kbhit = KBD_C; break;
			case SDL_SCANCODE_D: CMN_kbhit = KBD_D; break;
			case SDL_SCANCODE_E: CMN_kbhit = KBD_E; break;
			case SDL_SCANCODE_F: CMN_kbhit = KBD_F; break;
			case SDL_SCANCODE_G: CMN_kbhit = KBD_G; break;
			case SDL_SCANCODE_H: CMN_kbhit = KBD_H; break;
			case SDL_SCANCODE_I: CMN_kbhit = KBD_I; break;
			case SDL_SCANCODE_J: CMN_kbhit = KBD_J; break;
			case SDL_SCANCODE_K: CMN_kbhit = KBD_K; break;
			case SDL_SCANCODE_L: CMN_kbhit = KBD_L; break;
			case SDL_SCANCODE_M: CMN_kbhit = KBD_M; break;
			case SDL_SCANCODE_N: CMN_kbhit = KBD_N; break;
			case SDL_SCANCODE_O: CMN_kbhit = KBD_O; break;
			case SDL_SCANCODE_P: CMN_kbhit = KBD_P; break;
			case SDL_SCANCODE_Q: CMN_kbhit = KBD_Q; break;
			case SDL_SCANCODE_R: CMN_kbhit = KBD_R; break;
			case SDL_SCANCODE_S: CMN_kbhit = KBD_S; break;
			case SDL_SCANCODE_T: CMN_kbhit = KBD_T; break;
			case SDL_SCANCODE_U: CMN_kbhit = KBD_U; break;
			case SDL_SCANCODE_V: CMN_kbhit = KBD_V; break;
			case SDL_SCANCODE_W: CMN_kbhit = KBD_W; break;
			case SDL_SCANCODE_X: CMN_kbhit = KBD_X; break;
			case SDL_SCANCODE_Y: CMN_kbhit = KBD_Y; break;
			case SDL_SCANCODE_Z: CMN_kbhit = KBD_Z; break;

			case SDL_SCANCODE_0: CMN_kbhit = KBD_0; break;
			case SDL_SCANCODE_1: CMN_kbhit = KBD_1; break;
			case SDL_SCANCODE_2: CMN_kbhit = KBD_2; break;
			case SDL_SCANCODE_3: CMN_kbhit = KBD_3; break;
			case SDL_SCANCODE_4: CMN_kbhit = KBD_4; break;
			case SDL_SCANCODE_5: CMN_kbhit = KBD_5; break;
			case SDL_SCANCODE_6: CMN_kbhit = KBD_6; break;
			case SDL_SCANCODE_7: CMN_kbhit = KBD_7; break;
			case SDL_SCANCODE_8: CMN_kbhit = KBD_8; break;
			case SDL_SCANCODE_9: CMN_kbhit = KBD_9; break;
			}
			break;
		}
	}
}

int CMN_beginScene()
{
	return 1;
}

int CMN_endScene()
{
	return 1;
}
