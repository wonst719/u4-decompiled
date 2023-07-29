#include "u4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#include <windows.h>

#include "common.h"
//----------------------------------------

int __cdecl dopen(char* fname, int mode) {
	int ret;
	static char path[256];

	CONSOLE("dopen(\"%s\", %d)\n", fname, mode);
	strcpy(path, U4_ROOT);
	strcat(path, fname);
	switch (mode) {
	case 0: break;//Read
	case 1: break;//Write
	default:
		CONSOLE("TODO\n");
	}
	ret = _open(path, _O_RDONLY | _O_BINARY);
	if (ret <= 0) {
		CONSOLE("<err>\n");
	}

	return ret;
}

int __cdecl dlseek(int f, unsigned long ofs) {
	int ret;

	CONSOLE("dlseek(%d,0x%08x)\n", f, ofs);
	ret = _lseek(f, ofs, SEEK_SET);

	return ret;
}

int __cdecl dread(int fd, void* buffer, int count) {
	int ret;

	CONSOLE("dread(%d,0x%08x,0x%08x)\n", fd, buffer, count);
	ret = read(fd, buffer, count);
	if (ret != count) {
		CONSOLE("<err>\n");
	}

	return ret;
}
int __cdecl dwrite(int f, void* b, int sz) {
	int ret;

	//	CONSOLE("dwrite(%d,0x%08x,0x%08x)\n", f, b, sz);
		//-- --
	if (f > 2) {
		CONSOLE("dwrite(%d,0x%08x,0x%08x)\n", f, b, sz);
		return sz;
	}
	//-- --
	ret = _write(f, b, sz);

	return ret;
}
int __cdecl dclose(int f) {
	int ret;

	CONSOLE("dclose(%d)\n", f);
	ret = _close(f);

	return ret;
}

void* __cdecl dalloc(int n) {
	void* ret;

	CONSOLE("dalloc(%08x)\n", n);
	ret = malloc(n);

	return ret;
}
__cdecl dfree(void* p) {
	CONSOLE("dfree(%08x)\n", p);
	free(p);

	FAKE_RET;
}
