#define const

typedef unsigned char Jamo;
typedef unsigned char ScanCode;
typedef unsigned short Codepoint;

typedef int KaBool;

#define KaTrue 1
#define KaFalse 0

typedef struct _CompositionChar
{
	Jamo initial;
	Jamo vowel;
	Jamo vowel2;
	Jamo final;
	Jamo final2;
} CompositionChar;

static int currentState;

static CompositionChar currentComposition;

static char completedText[256 + 1];

static const Jamo initialTop[] = { 8, 13, 4, 1, 10 };
static const Jamo initialMid[] = { 7, 3, 12, 6, 19 };
static const Jamo initialBot[] = { 16, 17, 15, 18 };
static const Jamo vowelTop[] = { 13, 7, 3, 2, 6 };
static const Jamo vowelMid[] = { 9, 5, 1, 21 };
static const Jamo vowelBot[] = { 18, 14, 19 };
static const Jamo finalTop[] = { 17, 22, 7, 1, 19 };
static const Jamo finalMid[] = { 16, 4, 21, 8, 27 };
static const Jamo finalBot[] = { 24, 25, 23, 26 };

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

static Jamo ConvertScanCodeToInitial(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
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
}

static Jamo ConvertScanCodeToVowel(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
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
}

static Jamo ConvertScanCodeToFinal(scanCode, shift)
ScanCode scanCode;
KaBool shift;
{
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
}

static void ClearCompositionChar(pCompositionChar)
CompositionChar* pCompositionChar;
{
	pCompositionChar->initial = 0;
	pCompositionChar->vowel = 0;
	pCompositionChar->vowel2 = 0;
	pCompositionChar->final = 0;
	pCompositionChar->final2 = 0;
}

static KaBool IsEmptyCompositionChar(pCompositionChar)
CompositionChar* pCompositionChar;
{
	return pCompositionChar->initial == 0 &&
		pCompositionChar->vowel == 0 &&
		pCompositionChar->vowel2 == 0 &&
		pCompositionChar->final == 0 &&
		pCompositionChar->final2 == 0;
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

static Jamo FinalToConsonant(final)
Jamo final;
{
	if (final == 0)
		return 0;

	return finalToInitial[final];
}

static Codepoint ToJohabCodepoint(pCompositionChar)
CompositionChar* pCompositionChar;
{
	int initial = pCompositionChar->initial;
	int vowel = CompositeVowel(pCompositionChar->vowel, pCompositionChar->vowel2);
	int final = CompositeFinal(pCompositionChar->final, pCompositionChar->final2);
	Codepoint ch = 0x8000;

	initial++;

	if (vowel >= 18)
		vowel += 8;
	else if (vowel >= 12)
		vowel += 6;
	else if (vowel >= 6)
		vowel += 4;
	else
		vowel += 2;

	if (final >= 17)
		final += 2;
	else
		final++;

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

	memset(&currentComposition, 0, sizeof(currentComposition));
}

/* Public */

void KaInitialize()
{
	completedText[0] = 0;
	currentState = 0;
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
			currentState = 6;
			KaProcessScan(scanCode, shift);
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
			currentState = 6;
			KaProcessScan(scanCode, shift);
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
			currentState = 6;
			KaProcessScan(scanCode, shift);
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
			currentState = 7;
			KaProcessScan(scanCode, shift);
		}
		else
		{
			currentState = 6;
			KaProcessScan(scanCode, shift);
		}
		break;
	case 5:
		if (jamo = ConvertScanCodeToVowel(scanCode, shift))
		{
			currentState = 7;
			KaProcessScan(scanCode, shift);
		}
		else
		{
			currentState = 6;
			KaProcessScan(scanCode, shift);
		}
		break;
	case 6:
		KaFinalizeComposition();
		currentState = 0;
		KaProcessScan(scanCode, shift);
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

	memset(&currentComposition, 0, sizeof(currentComposition));
	currentState = 0;
}

void KaCancelAllInputs()
{
	memset(&currentComposition, 0, sizeof(currentComposition));
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
