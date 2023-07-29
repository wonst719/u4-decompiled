#include "u4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#include <windows.h>

#include <SDL2/SDL.h>

#include "common.h"

extern COLORREF U4_PALETTE[];
extern HBRUSH U4_BRUSH[];
extern HPEN U4_PEN[];

SDL_Window* pSdlWindow;
SDL_Renderer* pSdlRenderer;
SDL_Surface* pSdlSurface;
SDL_Texture* pSdlTexture;

const int windowWidth = 1280;
const int windowHeight = 960;

const int hiresWidth = 640;
const int hiresHeight = 400;

const int loresWidth = 320;
const int loresHeight = 200;

const int hiresPackedStride = 80;

const int loresToHiresRatio = 2;

Uint8* pLinearEgaBuffer;

Uint8* pLinearOverlayBuffer;

__cdecl Gra_init(void** ppShp, void** ppChar, void (*pExit)(int))
{
	CONSOLE("Gra_init(%08x,%08x,%08x)//TODO\n", ppShp, ppChar, pExit);

	//CMN_createWindow(320 * RATIO, 200 * RATIO, *ppShp, *ppChar);
	SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &pSdlWindow, &pSdlRenderer);

	pSdlSurface = SDL_CreateRGBSurface(0, hiresWidth, hiresHeight, 32, 0xff0000, 0xff00, 0xff, 0xff000000);

	pSdlTexture = SDL_CreateTextureFromSurface(pSdlRenderer, pSdlSurface);
	SDL_SetTextureScaleMode(pSdlTexture, SDL_ScaleModeLinear);

	if (SDL_MUSTLOCK(pSdlSurface))
	{
		exit(0);
	}

	if (pSdlSurface->pitch != hiresWidth * 4)
	{
		exit(0);
	}

	pLinearEgaBuffer = malloc(loresWidth * loresHeight);
	memset(pLinearEgaBuffer, 0, loresWidth * loresHeight);

	pLinearOverlayBuffer = malloc(hiresWidth * hiresHeight);
	memset(pLinearOverlayBuffer, 0, hiresWidth * hiresHeight);

	FAKE_RET;
}

inline void GrPutOverlayPixel(int y, int x, int egaColor)
{
	pLinearOverlayBuffer[y * hiresWidth + x] = egaColor;
}

inline void GrPutPixel(int y, int x, int egaColor)
{
	pLinearEgaBuffer[y * loresWidth + x] = egaColor;
}

inline void GrPutByte(int y, int x, byte egaByte)
{
	pLinearEgaBuffer[y * loresWidth + x] = egaByte >> 4;
	pLinearEgaBuffer[y * loresWidth + x + 1] = egaByte & 0xf;
}

inline void GrPutOverlayMonoByte(int y, int x, byte b, int egaColor)
{
	pLinearOverlayBuffer[y * hiresWidth + x + 0] = ((b >> 7) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 1] = ((b >> 6) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 2] = ((b >> 5) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 3] = ((b >> 4) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 4] = ((b >> 3) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 5] = ((b >> 2) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 6] = ((b >> 1) & 1) ? egaColor : 0;
	pLinearOverlayBuffer[y * hiresWidth + x + 7] = ((b >> 0) & 1) ? egaColor : 0;
}

#if 0
void PackedToLinear()
{
	memset(pLinearEgaBuffer, 0, hiresWidth * hiresHeight);

	for (int y = 0; y < hiresHeight; y++)
	{
		for (int x = 0; x < hiresPackedStride; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				Uint8* pPlane = SelectPlane(i);
				Uint8 z = pPlane[y * hiresPackedStride + x];

				pLinearEgaBuffer[y * hiresWidth + x * 8 + 0] |= ((z >> 7) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 1] |= ((z >> 6) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 2] |= ((z >> 5) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 3] |= ((z >> 4) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 4] |= ((z >> 3) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 5] |= ((z >> 2) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 6] |= ((z >> 1) & 1) << (4 >> i);
				pLinearEgaBuffer[y * hiresWidth + x * 8 + 7] |= ((z >> 0) & 1) << (4 >> i);
			}
		}
	}
}
#endif

Uint32 egaPalette[16] =
{
	0xff000000,
	0xff0000aa,
	0xff00aa00,
	0xff00aaaa,
	0xffaa0000,
	0xffaa00aa,
	0xffaa5500,
	0xffaaaaaa,

	0xff555555,
	0xff5555ff,
	0xff55ff55,
	0xff55ffff,
	0xffff5555,
	0xffff55ff,
	0xffffff55,
	0xffffffff,
};

void LinearToRGB()
{
	Uint32* pixels = pSdlSurface->pixels;
	int pitch = pSdlSurface->pitch / 4;

	for (int y = 0; y < loresHeight; y++)
	{
		for (int x = 0; x < loresWidth; x++)
		{
			Uint32 color = egaPalette[pLinearEgaBuffer[y * loresWidth + x] & 0xf];
			pixels[(y * 2) * pitch + (x * 2)] = color;
			pixels[(y * 2) * pitch + (x * 2 + 1)] = color;
			pixels[(y * 2 + 1) * pitch + (x * 2)] = color;
			pixels[(y * 2 + 1) * pitch + (x * 2 + 1)] = color;
		}
	}

	for (int y = 0; y < hiresHeight; y++)
	{
		for (int x = 0; x < hiresWidth; x++)
		{
			pixels[y * pitch + x] |= egaPalette[pLinearOverlayBuffer[y * hiresWidth + x] & 0xf];
		}
	}
}

void Present()
{
	LinearToRGB();

	SDL_UpdateTexture(pSdlTexture, &pSdlSurface->clip_rect, pSdlSurface->pixels, pSdlSurface->pitch);

	SDL_Rect srcRect = { 0, 0, hiresWidth, hiresHeight };
	SDL_Rect dstRect = { 0, 0, windowWidth, windowHeight };
	SDL_RenderCopy(pSdlRenderer, pSdlTexture, &srcRect, &dstRect);
	SDL_RenderPresent(pSdlRenderer);
}

void UpdateFrame()
{
	Present();
}

void PutTile(int packedY, int packedX, int tile)
{
	Uint8* pByteShapes = (Uint8*)pShapes;

	Uint8* p = &pByteShapes[tile * 32 * 4];

	for (int y = 0; y < 16; y++)
	{
		GrPutByte(packedY + y, packedX + 0, *p++);
		GrPutByte(packedY + y, packedX + 2, *p++);
		GrPutByte(packedY + y, packedX + 4, *p++);
		GrPutByte(packedY + y, packedX + 6, *p++);
		GrPutByte(packedY + y, packedX + 8, *p++);
		GrPutByte(packedY + y, packedX + 10, *p++);
		GrPutByte(packedY + y, packedX + 12, *p++);
		GrPutByte(packedY + y, packedX + 14, *p++);
	}
}

void ClearZone(int x, int y, int w, int h)
{
	int loresX = x * 8;
	int loresY = y * 8;
	int loresW = w * 8;
	int loresH = h * 8;
	int hiresX = x * 16;
	int hiresY = y * 16;
	int hiresW = w * 16;
	int hiresH = h * 16;

	for (int y = loresY; y < loresY + loresH; y++)
	{
		memset(pLinearEgaBuffer + y * loresWidth + loresX, 0, loresW);
	}
	for (int y = hiresY; y < hiresY + hiresH; y++)
	{
		memset(pLinearOverlayBuffer + y * hiresWidth + hiresX, 0, hiresW);
	}
}

//; Black, Green, Blue, White
//B_DotColorTable db 00h, 02h, 01h, 07h

/*highlight cursor*/
__cdecl Gra_00(int char_Y, int char_X) {
	int i, j;
	int top, left;

	CONSOLE("Gra_00 \"highlight cursor\"(%d,%d)\n", char_Y, char_X);
	//top = 8 + char_Y * 16;
	//left = 8 + char_X * 16;
	//CMN_beginScene();
	//for (j = 0; j < 2; j++) {
	//	for (i = 0; i < 16; i++) {
	//		CMN_xorpixel(left + i, top + j, 3);
	//		CMN_xorpixel(left + i, top + (16 - 2) + j, 3);
	//	}
	//}
	//for (j = 2; j < (16 - 2); j++) {
	//	for (i = 0; i < 2; i++) {
	//		CMN_xorpixel(left + i, top + j, 3);
	//		CMN_xorpixel(left + (16 - 2) + i, top + j, 3);
	//	}
	//}
	//CMN_endScene();

	FAKE_RET;
}
/*render sprite(2)*/
__cdecl Gra_01(int tile, int trow, int srow, int scol, int exp) {
	unsigned char* p;
	int i;
	int y;

	//p = CMN_getShapeData(tile) + (trow & 1) * 4 * 8 + (trow >> 1) * 4;

	FAKE_RET;
}
/*render sprite(2)*/
__cdecl Gra_02(int height, int width, int tile, int srow, int scol) {
	int y, x;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			PutTile(srow + y * 16, scol * 4 + x * 16, tile);
		}
	}

	FAKE_RET;
}
/*shake related(1)*/
__cdecl Gra_03() {
	//TODO
	FAKE_RET;
}
/*shake related(2)*/
__cdecl Gra_04() {
	//TODO
	FAKE_RET;
}

__cdecl Gra_05(int height, int width, unsigned char* pC, int d) {
	int y, x;

	//	CONSOLE("Gra_05(%d, %d, %08x, %d)//TODO\n", height, width, pC, d);
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			PutTile(8 + y * 16, 8 + x * 16, pC[y * width + x]);
		}
	}

	FAKE_RET;
}
//XOR SCREEN
Gra_09() {
	int i, j;

	CONSOLE("Gra_09\"XOR SCREEN\"\n");

	FAKE_RET;
}
/*clear map zone*/
Gra_10() {
	CONSOLE("Gra_10\"clear map zone\"\n");

	ClearZone(1, 1, 11 * 2, 11 * 2);

	FAKE_RET;
}
/*highlight char's status*/
Gra_11(int a) {
	int i, j, k;

	CONSOLE("Gra_11\"highlight char's status\"(%d)\n", a);
	CMN_beginScene();
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 8; j++) {
			for (k = 0; k < 8; k++) {
				CMN_xorpixel((24 + i) * 8 + k, (1 + a) * 8 + j, 3);
			}
		}
	}
	CMN_endScene();

	FAKE_RET;
}
/*clear status zone*/
Gra_13() {
	CONSOLE("Gra_13\"clear status zone\"\n");
	ClearZone(24, 1, 15, 8);

	FAKE_RET;
}
__cdecl Gra_16() {
	//TODO
	FAKE_RET;
}
__cdecl Gra_17() {
	//TODO
	FAKE_RET;
}
/*draw a "3D" wall*/
__cdecl Gra_18(int x0, int x1, int y0, int y1, int y0p, int y1p, int col0, int col1) {
	FAKE_RET;
}
/*clear food/gold zone*/
__cdecl Gra_19() {
	CONSOLE("Gra_19\"clear food/gold zone\"\n");
	//CMN_clear(24, 10, 15, 1, 0);

	FAKE_RET;
}

__cdecl Gra_clrscr() {
	CONSOLE("Gra_clrscr\n");

	memset(pLinearEgaBuffer, 0, loresWidth * loresHeight);
	memset(pLinearOverlayBuffer, 0, hiresWidth * hiresHeight);

	FAKE_RET;
}

__cdecl Gra_dot(int y, int x, int c) {
	// TODO
	GrPutPixel(y, x, 1);

	FAKE_RET;
}

__cdecl Gra_dot_OR(int y, int x, int c) {
	// TODO
	GrPutPixel(y, x, 1);

	FAKE_RET;
}

__cdecl Gra_dot_XOR(int y, int x, int c) {
	// TODO
	GrPutPixel(y, x, 1);

	FAKE_RET;
}

__cdecl Gra_line(int x0, int y0, int x1, int y1, int color) {
	if (CMN_beginScene()) {
		CMN_endScene();
	}

	FAKE_RET;
}

Gra_CR() {
	RECT rect;

	//CONSOLE("Gra_CR\n");
	u4_SetTextCoordYX(23, 24);

	for (int y = 88 * 2; y < 192 * 2; y++)
	{
		int x = 24 * 8 * 2;
		int width = 16 * 8 * 2;
		memmove(&pLinearOverlayBuffer[y * hiresWidth + x], &pLinearOverlayBuffer[(y + 16) * hiresWidth + x], width);
	}

	FAKE_RET;
}
__cdecl Gra_animSpit() {
	//TODO
	CONSOLE("Gra_animSpit\n");

	FAKE_RET;
}

Gra_animFlow(unsigned tile) {
	int i;
	unsigned char* p;
	unsigned short AX, DX;
	CONSOLE("Gra_animFlow(%x)\n", tile);

#if 0
	p = CMN_getShapeData(tile);
	AX = *(unsigned short*)(p + 0x3c);
	DX = *(unsigned short*)(p + 0x3e);
	for (i = 0; i < 8; i++) {
		unsigned short temp;
		DO_SWAP(AX, *(unsigned short*)(p + 0x00), temp);
		DO_SWAP(AX, *(unsigned short*)(p + 0x20), temp);
		DO_SWAP(DX, *(unsigned short*)(p + 0x02), temp);
		DO_SWAP(DX, *(unsigned short*)(p + 0x22), temp);
		p += 4;
	}
#endif

	FAKE_RET;
}
static char random() { return (char)(rand() & 0xff); }

Gra_animFlag() {
	unsigned char* p;
	unsigned short temp;
	CONSOLE("Gra_animFlag\n");

#if 0
	p = CMN_getShapeData(0);
	if (random() >= 0) {
		DO_SWAP(*(unsigned short*)(p + 0x2A4), *(unsigned short*)(p + 0x288), temp);
	}
	if (random() >= 0) {
		DO_SWAP(*(unsigned short*)(p + 0x2E2), *(unsigned short*)(p + 0x2c6), temp);
	}
	if (random() >= 0) {
		DO_SWAP(*(unsigned short*)(p + 0x404), *(unsigned short*)(p + 0x424), temp);
		DO_SWAP(*(unsigned short*)(p + 0x406), *(unsigned short*)(p + 0x426), temp);
	}
	if (random() >= 0) {
		DO_SWAP(*(unsigned short*)(p + 0x484), *(unsigned short*)(p + 0x4A4), temp);
		DO_SWAP(*(unsigned short*)(p + 0x486), *(unsigned short*)(p + 0x4A6), temp);
	}
	if (random() >= 0) {
		DO_SWAP(*(unsigned short*)(p + 0x3A0), *(unsigned short*)(p + 0x384), temp);
	}
#endif

	FAKE_RET;
}

Gra_putchar(char c)
{
	Uint8* pByteCharset = (Uint8*)pCharset;

	Uint8* ptr = &pByteCharset[c * 32];

	for (int y = 0; y < 8; y++)
	{
		GrPutByte(txt_Y * 8 + y, txt_X * 4, *ptr++);
		GrPutByte(txt_Y * 8 + y, txt_X * 4 + 2, *ptr++);
		GrPutByte(txt_Y * 8 + y, txt_X * 4 + 4, *ptr++);
		GrPutByte(txt_Y * 8 + y, txt_X * 4 + 6, *ptr++);
	}

	FAKE_RET;
}

Gra_putk(int first, int mid, int last, int bold)
{
	Uint8* pByteCharset = (Uint8*)pCharset;

	Uint8 composeBuffer[32] = { 0, };

	Uint8* ptr;
	ptr = &pByteCharset[0x2C00 + first * 32];
	for (int i = 0; i < 32; i++)
	{
		composeBuffer[i] |= ptr[i];
	}

	ptr = &pByteCharset[0x2C00 + mid * 32];
	for (int i = 0; i < 32; i++)
	{
		composeBuffer[i] |= ptr[i];
	}

	ptr = &pByteCharset[0x2C00 + last * 32];
	for (int i = 0; i < 32; i++)
	{
		composeBuffer[i] |= ptr[i];
	}

	for (int i = 0; i < 16; i++)
	{
		GrPutOverlayMonoByte(txt_Y * 16 + i, txt_X * 8, composeBuffer[i * 2], 0x7);
		GrPutOverlayMonoByte(txt_Y * 16 + i, txt_X * 8 + 8, composeBuffer[i * 2 + 1], 0x7);
	}

	FAKE_RET;
}

Gra_pute(char a)
{
	Uint8* pByteCharset = (Uint8*)pCharset;

	Uint8* ptr = &pByteCharset[0x1000 + a * 16];

	for (int y = 0; y < 16; y++)
	{
		GrPutOverlayMonoByte(txt_Y * 16 + y, txt_X * 8, *ptr++, 7);
	}

	FAKE_RET;
}

Gra_putf(char a)
{
	//PackedPutByte(txt_Y * 16, txt_X, 0xff, 0xf);

	FAKE_RET;
}

sizzleShapes() {
	//TODO
	FAKE_RET;
}
sizzleCharset() {
	//TODO
	FAKE_RET;
}
