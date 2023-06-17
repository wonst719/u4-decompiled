#define const

typedef unsigned char Jamo;
typedef unsigned char ScanCode;
typedef unsigned short Codepoint;

typedef int KaBool;

#define KaTrue 1
#define KaFalse 0

/*#define CLEAR_COMPOSITION(x) do { x.initial = x.vowel = x.vowel2 = x.final = x.final2 = 0; } while (0)*/
#define CLEAR_COMPOSITION(x) do { ((union CharUnion*)&x)->p[0] = 0; ((union CharUnion*)&x)->p[1] = 0; ((union CharUnion*)&x)->p[2] = 0; } while (0)

typedef struct _CompositionChar
{
	Jamo initial;
	Jamo vowel;
	Jamo vowel2;
	Jamo final;
	Jamo final2;
	Jamo _dummy;
} CompositionChar;

union CharUnion
{
	CompositionChar c;
	unsigned int* p;
};

static int currentState;

static CompositionChar currentComposition;

static char completedText[256 + 1];

/*
static const Jamo initialTop[] = { 8, 13, 4, 1, 10 };
static const Jamo initialMid[] = { 7, 3, 12, 6, 19 };
static const Jamo initialBot[] = { 16, 17, 15, 18 };
static const Jamo vowelTop[] = { 13, 7, 3, 2, 6 };
static const Jamo vowelMid[] = { 9, 5, 1, 21 };
static const Jamo vowelBot[] = { 18, 14, 19 };
static const Jamo finalTop[] = { 17, 22, 7, 1, 19 };
static const Jamo finalMid[] = { 16, 4, 21, 8, 27 };
static const Jamo finalBot[] = { 24, 25, 23, 26 };
*/

static const Jamo finalTransition[11][3] = {
	{1, 19, 2},
	{4, 22, 1},
	{4, 27, 2},
	{8, 1, 1},
	{8, 16, 2},
	{8, 17, 3},
	{8, 19, 4},
	{8, 25, 5},
	{8, 26, 6},
	{8, 27, 7},
	{17, 19, 1},
};

static const Jamo vowelTransition[7][3] = {
	{9, 1, 1},
	{9, 2, 2},
	{9, 21, 3},
	{14, 5, 1},
	{14, 6, 2},
	{14, 21, 3},
	{19, 21, 1},
};

static const Jamo finalToInitial[] = { 0, 1, 2, 0, 3, 0, 0, 4, 6, 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 10, 0, 12, 13, 15, 16, 17, 18, 19 };

/* Internal */

/* [0x10..0x2F] */
static const Jamo scanToInitial[] = { 8, 13, 4, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 12, 6, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 17, 15, 18 };
static const Jamo scanToInitialShift[] = { 9, 14, 5, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 12, 6, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 17, 15, 18 };

static Jamo ConvertScanCodeToInitial(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
	register unsigned char idx = scanCode - 0x10;
	if (scanCode <= 0x1F)
	{
		if (shift)
			return scanToInitialShift[idx];
		else
			return scanToInitial[idx];
	}

	return 0;

#if 0
	Jamo baseCode = 0;
	if (scanCode >= 0x2C && scanCode <= 0x2F)
		baseCode = initialBot[scanCode - 0x2C];
	else if (scanCode >= 0x1E && scanCode <= 0x22)
		baseCode = initialMid[scanCode - 0x1E];
	else if (scanCode >= 0x10 && scanCode <= 0x14)
		baseCode = initialTop[scanCode - 0x10];
	else
		return 0;

	if (shift && (baseCode == 1 || baseCode == 4 || baseCode == 8 || baseCode == 10 || baseCode == 13))
		baseCode++;

	return baseCode;
#endif
}

/* [0x15..0x32] */
static const Jamo scanToVowel[] = { 13, 7, 3, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 5, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 14, 19 };
static const Jamo scanToVowelShift[] = { 13, 7, 3, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 5, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 14, 19 };

static Jamo ConvertScanCodeToVowel(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
	register unsigned char idx = scanCode - 0x15;
	if (scanCode <= 0x1D)
	{
		if (shift)
			return scanToVowelShift[idx];
		else
			return scanToVowel[idx];
	}

	return 0;

#if 0
	Jamo baseCode = 0;
	if (scanCode >= 0x30 && scanCode <= 0x32)
		baseCode = vowelBot[scanCode - 0x30];
	else if (scanCode >= 0x23 && scanCode <= 0x26)
		baseCode = vowelMid[scanCode - 0x23];
	else if (scanCode >= 0x15 && scanCode <= 0x19)
		baseCode = vowelTop[scanCode - 0x15];
	else
		return 0;

	if (shift && (baseCode == 2 || baseCode == 6))
		baseCode += 2;

	return baseCode;
#endif
}

/* [0x10..0x2F] */
static const Jamo scanToFinal[] = { 17, 22, 7, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 4, 21, 8, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 25, 23, 26 };
static const Jamo scanToFinalShift[] = { 0, 0, 0, 2, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 4, 21, 8, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 25, 23, 26 };

static Jamo ConvertScanCodeToFinal(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
	register unsigned char idx = scanCode - 0x10;
	if (scanCode <= 0x1F)
	{
		if (shift)
			return scanToFinalShift[idx];
		else
			return scanToFinal[idx];
	}

	return 0;

#if 0
	Jamo baseCode = 0;
	if (scanCode >= 0x2C && scanCode <= 0x2F)
		baseCode = finalBot[scanCode - 0x2C];
	else if (scanCode >= 0x1E && scanCode <= 0x22)
		baseCode = finalMid[scanCode - 0x1E];
	else if (scanCode >= 0x10 && scanCode <= 0x14)
		baseCode = finalTop[scanCode - 0x10];
	else
		return 0;

	if (shift)
	{
		if (baseCode == 1 || baseCode == 19)
			baseCode++;
		else if (baseCode == 7 || baseCode == 17 || baseCode == 22)
			return 0;
	}

	return baseCode;
#endif
}

static void ClearCompositionChar(pCompositionChar)
CompositionChar* pCompositionChar;
{
	register union CharUnion* u = (union CharUnion*)pCompositionChar;

	u->p[0] = 0;
	u->p[1] = 0;
	u->p[2] = 0;
}

static KaBool IsEmptyCompositionChar(pCompositionChar)
CompositionChar* pCompositionChar;
{
	register union CharUnion* u = (union CharUnion*)pCompositionChar;

	return u->p[0] == 0 && u->p[1] == 0 && u->c.final2 == 0;
#if 0
	return pCompositionChar->initial == 0 &&
		pCompositionChar->vowel == 0 &&
		pCompositionChar->vowel2 == 0 &&
		pCompositionChar->final == 0 &&
		pCompositionChar->final2 == 0;
#endif
}

static int CompositeVowel(vowel, vowel2)
Jamo vowel;
Jamo vowel2;
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (vowelTransition[i][0] == vowel && vowelTransition[i][1] == vowel2)
			return vowel + vowelTransition[i][2];
	}

	return vowel;
}

static int CompositeFinal(final, final2)
Jamo final;
Jamo final2;
{
	int i;
	for (i = 0; i < 11; i++)
	{
		if (finalTransition[i][0] == final && finalTransition[i][1] == final2)
			return final + finalTransition[i][2];
	}

	return final;
}

static KaBool IsAcceptableVowel2(vowel, vowel2)
Jamo vowel;
Jamo vowel2;
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (vowelTransition[i][0] == vowel && vowelTransition[i][1] == vowel2)
			return KaTrue;
	}

	return KaFalse;
}

static KaBool IsAcceptableFinal2(final, final2)
Jamo final;
Jamo final2;
{
	int i;
	for (i = 0; i < 11; i++)
	{
		if (finalTransition[i][0] == final && finalTransition[i][1] == final2)
			return KaTrue;
	}

	return KaFalse;
}

#define FinalToConsonant(x) finalToInitial[x]

#if 0
static Jamo FinalToConsonant(final)
Jamo final;
{
	return finalToInitial[final];
}
#endif

static const Jamo johabVowel[] = { 0, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 26, 27, 28, 29 };

static Codepoint ToJohabCodepoint(pCompositionChar)
CompositionChar* pCompositionChar;
{
	int initial = pCompositionChar->initial;
	int vowel = CompositeVowel(pCompositionChar->vowel, pCompositionChar->vowel2);
	int final = CompositeFinal(pCompositionChar->final, pCompositionChar->final2);
	Codepoint ch = 0x8000;

	initial++;

	vowel = johabVowel[vowel];
	/*if (vowel >= 18)
		vowel += 8;
	else if (vowel >= 12)
		vowel += 6;
	else if (vowel >= 6)
		vowel += 4;
	else
		vowel += 2;*/

	final++;
	if (final >= 17)
		final++;
	/*if (final >= 17)
		final += 2;
	else
		final++;*/

	ch |= initial << 10;
	ch |= vowel << 5;
	ch |= final;

	return ch;
}

static void KaFinalizeComposition()
{
	Codepoint codepoint = ToJohabCodepoint(&currentComposition);
	char buffer[3];

	buffer[0] = (codepoint >> 8) & 0xff;
	buffer[1] = codepoint & 0xff;
	buffer[2] = 0;

	strcat(completedText, buffer);

	CLEAR_COMPOSITION(currentComposition);
}

/* Public */

void KaInitialize()
{
	completedText[0] = 0;
	currentState = 0;
}

void KaProcessScan();

void KaProcessNextState(scanCode, shift, nextState)
ScanCode scanCode;
KaBool shift;
int nextState;
{
	currentState = nextState;
	KaProcessScan(scanCode, shift);
}

void KaProcessScan(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
	Jamo jamo;

	switch (currentState)
	{
	case 0:
	{
		if (jamo = ConvertScanCodeToInitial(scanCode, shift))
		{
			currentComposition.initial = jamo;
			currentState = 1;
		}
		else if (jamo = ConvertScanCodeToVowel(scanCode, shift))
		{
			currentComposition.vowel = jamo;
			currentState = 2;
		}
		else
		{
			if (IsEmptyCompositionChar(&currentComposition))
			{
				/* ? */
			}
			else
			{
				KaFinalizeComposition();
			}
		}
	}
	break;
	case 1:
		if (jamo = ConvertScanCodeToVowel(scanCode, shift))
		{
			currentComposition.vowel = jamo;
			currentState = 2;
		}
		else
		{
			KaProcessNextState(scanCode, shift, 6);
		}
		break;
	case 2:
		jamo = ConvertScanCodeToVowel(scanCode, shift);
		if (IsAcceptableVowel2(currentComposition.vowel, jamo))
		{
			currentComposition.vowel2 = jamo;
			currentState = 3;
		}
		else if (jamo = ConvertScanCodeToFinal(scanCode, shift))
		{
			currentComposition.final = jamo;
			currentState = 4;
		}
		else
		{
			KaProcessNextState(scanCode, shift, 6);
		}
		break;
	case 3:
		if (jamo = ConvertScanCodeToFinal(scanCode, shift))
		{
			currentComposition.final = jamo;
			currentState = 4;
		}
		else
		{
			KaProcessNextState(scanCode, shift, 6);
		}
		break;
	case 4:
		jamo = ConvertScanCodeToFinal(scanCode, shift);
		if (IsAcceptableFinal2(currentComposition.final, jamo))
		{
			currentComposition.final2 = jamo;
			currentState = 5;
		}
		else if (jamo = ConvertScanCodeToVowel(scanCode, shift))
		{
			KaProcessNextState(scanCode, shift, 7);
		}
		else
		{
			KaProcessNextState(scanCode, shift, 6);
		}
		break;
	case 5:
		if (jamo = ConvertScanCodeToVowel(scanCode, shift))
		{
			KaProcessNextState(scanCode, shift, 7);
		}
		else
		{
			KaProcessNextState(scanCode, shift, 6);
		}
		break;
	case 6:
		KaFinalizeComposition();
		KaProcessNextState(scanCode, shift, 0);
		break;
	case 7:
		{
			int nextInitial = 0;
			if (currentComposition.final2)
			{
				nextInitial = FinalToConsonant(currentComposition.final2);
				currentComposition.final2 = 0;
			}
			else if (currentComposition.final)
			{
				nextInitial = FinalToConsonant(currentComposition.final);
				currentComposition.final = 0;
			}

			{
				KaFinalizeComposition();
				if (nextInitial < 0)
				{
					/*printf("err\n");*/
				}

				jamo = ConvertScanCodeToVowel(scanCode, shift);
				currentComposition.initial = nextInitial;
				currentComposition.vowel = jamo;
			}

			currentState = 2;
		}
		break;
	}
}

/*
void KaProcessInput(ch)
char ch;
{
	if (!isalpha(ch))
	{
		KaCompleteChar();
		return;
	}

	KaBool shift = isupper(ch);
	int scanCode = usAsciiToScanCode[tolower(ch) - 0x61];

	KaProcessScan(scanCode, shift);
}
*/

void KaRollbackState()
{
	if (currentComposition.final2)
	{
		currentComposition.final2 = 0;
		currentState = 4;
	}
	else if (currentComposition.final)
	{
		currentComposition.final = 0;
		if (currentComposition.vowel2)
		{
			currentState = 3;
		}
		else
		{
			currentState = 2;
		}
	}
	else if (currentComposition.vowel2)
	{
		currentComposition.vowel2 = 0;
		currentState = 2;
	}
	else if (currentComposition.vowel)
	{
		currentComposition.vowel = 0;
		if (currentComposition.initial)
		{
			currentState = 1;
		}
		else
		{
			currentState = 0;
		}
	}
	else if (currentComposition.initial)
	{
		currentComposition.initial = 0;
		currentState = 0;
	}
	else
	{
		currentState = 0;
	}
}

KaBool KaIsCompositing()
{
	return !IsEmptyCompositionChar(&currentComposition);
}

void KaCompleteChar()
{
	if (!IsEmptyCompositionChar(&currentComposition))
	{
		KaFinalizeComposition();
	}

	CLEAR_COMPOSITION(currentComposition);
	currentState = 0;
}

void KaCancelAllInputs()
{
	CLEAR_COMPOSITION(currentComposition);
	currentState = 0;
	completedText[0] = 0;
}

Codepoint KaGetCompositionChar()
{
	if (IsEmptyCompositionChar(&currentComposition))
		return 0;

	return ToJohabCodepoint(&currentComposition);
}

char* KaGetCompletedText()
{
	return completedText;
}

void KaClearOutText()
{
	completedText[0] = 0;
}
