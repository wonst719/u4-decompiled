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

// ZX0 Decompression
// TODO: Cleanup
#define BUFFER_SIZE 32768  /* must be > MAX_OFFSET */
#define INITIAL_OFFSET 1

unsigned char* input_data;
unsigned char* output_data;
size_t input_index;
size_t output_index;
size_t input_size;
size_t output_size;
int bit_mask;
int bit_value;
int backtrack;
int last_byte;

int read_byte() {
	if (input_index == input_size) {
		exit(1);
	}
	last_byte = input_data[input_index++];
	return last_byte;
}

int read_bit() {
	if (backtrack) {
		backtrack = 0;
		return last_byte & 1;
	}
	bit_mask >>= 1;
	if (bit_mask == 0) {
		bit_mask = 128;
		bit_value = read_byte();
	}
	return bit_value & bit_mask ? 1 : 0;
}

int read_interlaced_elias_gamma(int inverted) {
	int value = 1;
	while (!read_bit()) {
		value = value << 1 | read_bit() ^ inverted;
	}
	return value;
}

void write_byte(int value) {
	if (output_index == BUFFER_SIZE) {
		exit(1);
	}
	output_data[output_index++] = value;
}

void write_bytes(int offset, int length) {
	int i;

	if (offset > output_size + output_index) {
		exit(1);
	}
	while (length-- > 0) {
		i = output_index - offset;
		write_byte(output_data[i >= 0 ? i : BUFFER_SIZE + i]);
	}
}

void zx0decompress(void* inputBuffer, int inputSize, void* outputBuffer, int outputSize, int classic_mode) {
	int last_offset = INITIAL_OFFSET;
	int length;
	int i;

	input_data = (unsigned char*)inputBuffer;
	output_data = (unsigned char*)outputBuffer;

	if (!input_data || !output_data) {
		exit(1);
	}

	input_size = inputSize;
	input_index = 0;
	output_index = 0;
	output_size = 0;
	bit_mask = 0;
	backtrack = 0;

COPY_LITERALS:
	length = read_interlaced_elias_gamma(0);
	for (i = 0; i < length; i++)
		write_byte(read_byte());
	if (read_bit())
		goto COPY_FROM_NEW_OFFSET;

	/*COPY_FROM_LAST_OFFSET:*/
	length = read_interlaced_elias_gamma(0);
	write_bytes(last_offset, length);
	if (!read_bit())
		goto COPY_LITERALS;

COPY_FROM_NEW_OFFSET:
	last_offset = read_interlaced_elias_gamma(!classic_mode);
	if (last_offset == 256) {
		if (input_index != input_size) {
			exit(1);
		}
		return;
	}
	last_offset = last_offset * 128 - (read_byte() >> 1);
	backtrack = 1;
	length = read_interlaced_elias_gamma(0) + 1;
	write_bytes(last_offset, length);
	if (read_bit())
		goto COPY_FROM_NEW_OFFSET;
	else
		goto COPY_LITERALS;
}
