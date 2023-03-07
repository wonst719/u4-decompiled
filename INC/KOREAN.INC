/* [0]: when last == FILL */
/* [1]: when last != FILL */
static char initialSetChooseTable[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0,
	1, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5
};

static char vowelSetChooseTable[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
	2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3
};

static char finalSetChooseTable[] = {
	0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0, 2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1
};

void u4_pute(code)
unsigned int code;
{
	/* TODO: add half-width and full-width character support */

#ifdef WIN32
#else
	Gra_pute(code);
#endif
}

void u4_putk(code)
unsigned int code;
{
	/* cp1361 johab -> glyph idx */
	int initial, vowel, last, initialSetIdx, vowelSetIdx, finalSetIdx;

	if (!(code & 0x8000)) {
		initial = 0;
		vowel = 0;
		last = 0;
		initialSetIdx = 0;
		vowelSetIdx = 0;
		finalSetIdx = 0;
		return;
	}

	/* BE */
	initial = (code >> 10) & 0x1f;
	vowel = (code >> 5) & 0x1f;
	last = code & 0x1f;

	/* Convert johab consonant to dkb font idx */
	initial--;
	if (vowel >= 26) {
		vowel -= 8;
	} else if (vowel >= 18) {
		vowel -= 6;
	} else if (vowel >= 10) {
		vowel -= 4;
	} else if (vowel >= 2) {
		vowel -= 2;
	}
	if (last >= 19) {
		last -= 2;
	} else if (last >= 1) {
		last--;
	}

	if (last == 0) {
		initialSetIdx = initialSetChooseTable[0 * 22 + vowel];
		vowelSetIdx = vowelSetChooseTable[0 * 20 + initial];
		finalSetIdx = 0;
	} else {
		initialSetIdx = initialSetChooseTable[1 * 22 + vowel];
		vowelSetIdx = vowelSetChooseTable[1 * 20 + initial];
		finalSetIdx = finalSetChooseTable[vowel];
	}

	if (vowel > 0) {
		vowel = 160 + vowel + 22 * vowelSetIdx;
	}

	if (initial > 0) {
		initial = initial + 20 * initialSetIdx;
	}

	if (last > 0) {
		last = 248 + last + 28 * finalSetIdx;
	}

#ifdef WIN32
#else
	Gra_putk(initial, vowel, last);
#endif
}
