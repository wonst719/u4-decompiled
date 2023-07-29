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

static unsigned char johabVowelToDkb[] = {
	0, 0, 0, 1, 2, 3, 4, 5,
	0, 0, 6, 7, 8, 9, 10, 11,
	0, 0, 12, 13, 14, 15, 16, 17,
	0, 0, 18, 19, 20, 21
};

int _useBold = 0;

void u4_putk(code)
unsigned int code;
{
	/* cp1361 johab -> glyph idx */
	int initial, vowel, last, initialSetIdx, vowelSetIdx, finalSetIdx;

	if (!(code & 0x8000)) {
		return;
	}

	/* BE */
	initial = (code >> 10) & 0x1f;
	vowel = (code >> 5) & 0x1f;
	last = code & 0x1f;

	/* Convert johab consonant to dkb font idx */
	initial--;

	vowel = johabVowelToDkb[vowel];

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

	Gra_putk(initial, vowel, last, _useBold);
}
