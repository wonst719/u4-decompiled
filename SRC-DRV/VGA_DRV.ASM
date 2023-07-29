_TEXT SEGMENT
	ASSUME CS:_TEXT
	dw OFFSET _TEXT:DrvFunc00	;called through Gra_00 highlight cursor; int charY, int charX
	dw OFFSET _TEXT:DrvFunc01	;called through Gra_01 render sprite(2); int tile, int trow, int srow, int scol, int exp
	dw OFFSET _TEXT:DrvFunc02	;called through Gra_02 render sprite(2); int width, int heiht, int tile, int srow, int scol
	dw OFFSET _TEXT:DrvFunc03	;called through Gra_03 shake related(1);
	dw OFFSET _TEXT:DrvFunc04	;called through Gra_04 shake related(2);
	dw OFFSET _TEXT:DrvFunc05	;called through Gra_05 puttile?; int height, int width, unsigned char* pC, int d
	dw OFFSET _TEXT:DrvFunc06Dot	;called through Gra_dot; int y, int x, int col
	dw OFFSET _TEXT:DrvFunc07PutK	;
	dw OFFSET _TEXT:DrvFunc08CR	;called through Gra_CR
	dw OFFSET _TEXT:DrvFunc09	;called through Gra_09 xor screen;
	dw OFFSET _TEXT:DrvFunc10	;called through Gra_10 clear map zone;
	dw OFFSET _TEXT:DrvFunc11	;called through Gra_11 hight char's status; int a
	dw OFFSET _TEXT:DrvFunc12	;called through Gra_12(uncalled)
	dw OFFSET _TEXT:DrvFunc13	;called through Gra_13 clear status zone
	dw OFFSET _TEXT:DrvFunc14DotOR	;called through Gra_dot_OR
	dw OFFSET _TEXT:DrvFunc15DotXOR	;called through Gra_dot_XOR; int y, int x, int c
	dw OFFSET _TEXT:DrvFunc16	;called through Gra_16; draw image?
	dw OFFSET _TEXT:DrvFunc17	;called through Gra_17
	dw OFFSET _TEXT:DrvFunc18	;called through Gra_18 draw a "3d" wall
	dw OFFSET _TEXT:DrvFunc19	;called throuch Gra_19; draw the ankh
	dw OFFSET _TEXT:DrvFunc20AnimSpit	;called through Gra_animSpit; unsigned tile
	dw OFFSET _TEXT:DrvFunc21Init	;called through Gra_init; void **ppshape, void **ppchar void(*pExit)(int)
	dw OFFSET _TEXT:DrvFunc22ClrScr	;called through Gra_clrscr
	dw OFFSET _TEXT:DrvFunc23AnimFlow	;called through Gra_animFlow
	dw OFFSET _TEXT:DrvFunc24AnimFlag	;called through Gra_animFlag
	dw OFFSET _TEXT:DrvFunc25PutChar	;called through Gra_putchar; int c
	dw OFFSET _TEXT:DrvFunc26PutE	;called through Gra_pute; char c
	dw OFFSET _TEXT:DrvFunc27PutF	;called through Gra_putf; char c

LINE_COUNT EQU 200
HIRES_LINE_COUNT EQU 200
VGA_LINE_STRIDE EQU 80

RLE_RUNSTART EQU 2

W_GR_SEGMENT	dw 0A000h

B_0036	db 12h
B_0037	db 34h
B_0038	db 56h
B_0039	db 78h
_Unused1	db 0D5h,0AAh,0C3h,3Ch
_Unused2	db 1h,2h,4h,8h,10h,20h,40h,80h

W_pShapes_0	dw 0h
W_pShapes_1	dw 0h
W_pCharset_0	dw 0h
W_pCharset_1	dw 0h
W_pExit_0	dw 0h
W_0050	dw 0h

W_LineOffsets	dw HIRES_LINE_COUNT dup(0)	; Address for each screen line

; Color Palette: 16 palette + 1 border
W_PaletteTable	db 00h,01h,02h,03h,04h,05h,14h,07h
				db 38h,39h,3Ah,3Bh,3Ch,3Dh,3Eh,3Fh
				db 00h
	
; Black, Green, Blue, White
B_DotColorTable db 00h,02h,01h,07h

	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h

B_KCHR_COMPOSE	db 32 dup(?)	; 16bit*16

SHLM MACRO r,c
	REPT C
		SHL r,1
	ENDM
ENDM

SHRM MACRO r,c
	REPT C
		SHR r,1
	ENDM
ENDM

VGA_SEQ_ADDR EQU 3c4h
VGA_SEQ_DATA EQU 3c5h

VGA_CRTC_ADDR EQU 3d4h
VGA_CRTC_DATA EQU 3d5h

VGA_GRAP_ADDR EQU 3ceh
VGA_GRAP_DATA EQU 3cfh

OUTPORTB MACRO addr, val
	PUSH       DX
	PUSH       AX
	UOUTPORTB  addr, val
	POP        AX
	POP        DX
ENDM

; Uses DX, AX
UOUTPORTB MACRO addr, val
	MOV        DX, addr
	MOV        AL, val
	OUT        DX, AL
ENDM

VGA_WRITE_SEQ MACRO a, b
	UOUTPORTB VGA_SEQ_ADDR, a
	UOUTPORTB VGA_SEQ_DATA, b
ENDM

VGA_WRITE_CRTC MACRO a, b
	UOUTPORTB VGA_CRTC_ADDR, a
	UOUTPORTB VGA_CRTC_DATA, b
ENDM

VGA_WRITE_GRAP MACRO a, b
	UOUTPORTB VGA_GRAP_ADDR, a
	UOUTPORTB VGA_GRAP_DATA, b
ENDM

IODELAY MACRO
	REPT 8
		JMP $+2
	ENDM
ENDM

; AX, CX
MAGNIFY MACRO
	XOR AH, AH
	; x = (x | (x << 4)) & 0x0F0F;
	MOV CX, AX
	SHLM CX, 4
	OR CX, AX
	AND CX, 0f0fh
	MOV AX, CX

	; x = (x | (x << 2)) & 0x3333;
	SHLM CX, 2
	OR CX, AX
	AND CX, 3333h
	MOV AX, CX

	; x = (x | (x << 1)) & 0x5555;
	SHL CX, 1
	OR CX, AX
	AND CX, 5555h
	MOV AX, CX

	; z = (x << 1) | x;
	SHL CX, 1
	OR AX, CX

	XCHG AL, AH

	; ret: AX
ENDM

MAGNIFY_BX MACRO
	XOR AH, AH
	; x = (x | (x << 4)) & 0x0F0F;
	MOV BX, AX
	SHLM BX, 4
	OR BX, AX
	AND BX, 0f0fh
	MOV AX, BX

	; x = (x | (x << 2)) & 0x3333;
	SHLM BX, 2
	OR BX, AX
	AND BX, 3333h
	MOV AX, BX

	; x = (x | (x << 1)) & 0x5555;
	SHL BX, 1
	OR BX, AX
	AND BX, 5555h
	MOV AX, BX

	; z = (x << 1) | x;
	SHL BX, 1
	OR AX, BX

	XCHG AL, AH
ENDM

;----------------------------------------
;Gra_01(cdecl)
;----------------------------------------
; int tile, int trow, int srow, int scol, int exp
DrvFunc01 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,7h
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	UOUTPORTB VGA_SEQ_ADDR, 2h

	MOV        ES,word ptr CS:W_GR_SEGMENT
	LDS        SI,dword ptr CS:W_pShapes_0
	MOV        AX,word ptr [BP + 6h] ; param_1
	SHLM       AX,7		; *128
	ADD        SI,AX
	MOV        BX,word ptr [BP + 8h] ; param_2
	SHL        BX,1h
	ADD        SI,BX
	MOV        word ptr [BP + -6h],SI ; local_8
	MOV        word ptr [BP + -2h],8h ; local_4

L_02b3:
	MOV        DI,word ptr [BP + 0ch] ; param_4
	MOV        BX,word ptr [BP + 0ah] ; param_3
	SHL        BX,1h
	ADD        DI,word ptr CS:W_LineOffsets[BX]
	MOV        AX,word ptr [BP + -2h] ; local_4
	MOV        DX,VGA_SEQ_DATA
	OUT        DX,AL
	MOV        CX,2h

L_02cc:
	LODSB
	MOV        byte ptr [BP + -4h],8h ; local_6
	CMP        word ptr [BP + 0eh],1h ; param_5
	JZ         L_0334

	MAGNIFY_BX
	MOV        byte ptr [BP + -7h], AH ; local_a
	MAGNIFY_BX
	STOSW
	ADD DI, VGA_LINE_STRIDE-2
	STOSW
	SUB DI, VGA_LINE_STRIDE
	MOV        AL, byte ptr [BP + -7h] ; local_a
	MAGNIFY_BX
	STOSW
	ADD DI, VGA_LINE_STRIDE-2
	STOSW
	SUB DI, VGA_LINE_STRIDE

	JMP L_01_LOOP

L_01_TRAMPOLINE:
	JMP L_02cc

L_0334:
	MAGNIFY_BX
	STOSW
	ADD DI, VGA_LINE_STRIDE-2
	STOSW
	SUB DI, VGA_LINE_STRIDE

L_01_LOOP:
	LOOP       L_01_TRAMPOLINE

	ADD        word ptr [BP + -6h],20h ; local_8
	MOV        SI,word ptr [BP + -6h] ; local_8
	SHR        word ptr [BP + -2h],1h ; local_4
	JZ         L_0348
	JMP        L_02b3

L_0348:
	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF
DrvFunc01 ENDP
;----------------------------------------
;Gra_02(cdecl)
;----------------------------------------
DrvFunc02 PROC FAR C h: WORD, w: WORD, tile: WORD, sy: WORD, sx: WORD
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	MOV        DX, VGA_SEQ_ADDR
	MOV        AL, 2h
	OUT        DX, AL
	MOV        AH, byte ptr h
	MOV        AL, byte ptr w
	MOV        ES, word ptr CS:W_GR_SEGMENT
	MOV        DS, word ptr CS:W_pShapes_1
	MOV        SI, tile		; tile
	SHLM       SI, 7
	ADD        SI, word ptr CS:W_pShapes_0
	MOV        BX, word ptr [BP + 0ch]
	SHL        BX, 1
L_0388:
	MOV        DL, byte ptr w
	SHL        DL, 1
	MOV        DI, sx
	ADD        DI, word ptr CS:W_LineOffsets[BX]
L_0395:
	MOV        CX, 10h
	MOV        DH, 8h

L_039a:
	MOV        AL, DH
	PUSH       DX
	MOV        DX, VGA_SEQ_DATA
	OUT        DX, AL
	POP        DX

	PUSH       CX
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		LODSB
		MAGNIFY
		MOV        word ptr ES:[DI + VGA_LINE_STRIDE * (line * 2 + 0)],AX
		MOV        word ptr ES:[DI + VGA_LINE_STRIDE * (line * 2 + 1)],AX
		LODSB
		MAGNIFY
		MOV        word ptr ES:[DI + VGA_LINE_STRIDE * (line * 2 + 0) + 2],AX
		MOV        word ptr ES:[DI + VGA_LINE_STRIDE * (line * 2 + 1) + 2],AX
	ENDM
	POP        CX

	SHR        DH, 1
	JNZ        L_039a

	SUB        SI, 80h
	ADD        DI, 2h
	DEC        DL
	JNZ        L_0395
	ADD        BX, 20h
	DEC        h
	JZ         L_0417
	JMP        L_0388

L_0417:
	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF
DrvFunc02 ENDP
;----------------------------------------
;Gra_03(pascal)
;----------------------------------------
DrvFunc03 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	VGA_WRITE_GRAP 5h, 1h
	MOV        BX,346
	VGA_WRITE_SEQ 2h, 0fh

	MOV        AX,CS:W_GR_SEGMENT
	MOV        ES,AX
	MOV        DS,AX
L_044f:
	MOV        DI,word ptr CS:W_LineOffsets[BX + 10*2]
	MOV        SI,word ptr CS:W_LineOffsets[BX + 8*2]	; 8 -> 10
	ADD        SI, 2
	ADD        DI, 2
	MOV        CX,22*2
	REP MOVSB

	MOV        DI,word ptr CS:W_LineOffsets[BX + 10*2]
	MOV        SI,word ptr CS:W_LineOffsets[BX + 8*2]
	ADD        SI, VGA_LINE_STRIDE + 2
	ADD        DI, VGA_LINE_STRIDE + 2
	MOV        CX,22*2
	REP MOVSB

	DEC        BX
	DEC        BX
	JNZ        L_044f

	VGA_WRITE_GRAP 5h, 0h

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       2h
DrvFunc03 ENDP
;----------------------------------------
;Gra_04(pascal)
;----------------------------------------
DrvFunc04 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	VGA_WRITE_GRAP 5h, 1h
	MOV        BX,0h
	VGA_WRITE_SEQ 2h, 0fh

	MOV        AX,CS:W_GR_SEGMENT
	MOV        ES,AX
	MOV        DS,AX
L_04c1:
	MOV        DI,word ptr CS:W_LineOffsets[BX + 8*2]
	MOV        SI,word ptr CS:W_LineOffsets[BX + 10*2]
	ADD        SI, 2
	ADD        DI, 2
	MOV        CX,22*2
	REP MOVSB

	MOV        DI,word ptr CS:W_LineOffsets[BX + 8*2]
	MOV        SI,word ptr CS:W_LineOffsets[BX + 10*2]
	ADD        SI, VGA_LINE_STRIDE + 2
	ADD        DI, VGA_LINE_STRIDE + 2
	MOV        CX,22*2
	REP MOVSB

	INC        BX
	INC        BX
	CMP        BX,15ah
	JNZ        L_04c1

	VGA_WRITE_GRAP 5h, 0h

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       2h
DrvFunc04 ENDP

;----------------------------------------
;Gra_05(cdecl)
;----------------------------------------
	;height
	;width
	;src offset
	;dest offset
DrvFunc05 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,2h
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	MOV        DX,3c4h
	MOV        AL,2h
	OUT        DX,AL
	MOV        DX,3c5h
	MOV        DS,word ptr CS:[W_pShapes_1]
	MOV        ES,word ptr CS:[W_GR_SEGMENT]
	MOV        BX,10h
L_0525:
	MOV        byte ptr [BP + -2h],0bh
	MOV        DI,word ptr CS:[BX + W_LineOffsets]
	ADD        DI,1*2	; move 1 tile
L_0531:
	MOV        SI,word ptr [BP + 0Ah]
	INC        word ptr [BP + 0Ah]
	MOV        SI,word ptr SS:[SI]
	AND        SI,0ffh
	SHLM       SI,7
	ADD        SI,word ptr CS:[W_pShapes_0]

	MOV        CH,8h
L_0553:
	MOV        AL,CH
	OUT        DX,AL		; Set color plane mask

	PUSH       CX

	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		LODSB
		MAGNIFY
		MOV        word ptr ES:[DI + line*VGA_LINE_STRIDE*2],AX
		MOV        word ptr ES:[DI + line*VGA_LINE_STRIDE*2 + VGA_LINE_STRIDE],AX
		LODSB
		MAGNIFY
		MOV        word ptr ES:[DI + line*VGA_LINE_STRIDE*2 + 2],AX
		MOV        word ptr ES:[DI + line*VGA_LINE_STRIDE*2 + VGA_LINE_STRIDE + 2],AX
	ENDM

	POP        CX

	SHR        CH,1h
	JNZ        L_0553

	ADD        DI,4h
	DEC        byte ptr [BP + -2h]
	JZ         L_05c0
	JMP        L_0531
L_05c0:
	ADD        BX,20h
	DEC        word ptr [BP + 6h]
	JZ         L_05cb
	JMP        L_0525
L_05cb:

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF
	; Func
	; Func
DrvFunc05 ENDP
;----------------------------------------
;Gra_CR
;----------------------------------------
DrvFunc08CR PROC FAR
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	; Graphics Write Mode 1
	VGA_WRITE_GRAP 5h, 1h

	MOV        DS,word ptr CS:[W_GR_SEGMENT]
	PUSH       DS
	POP        ES

	; Map Mask: 1111
	VGA_WRITE_SEQ 2h, 0fh

	; move up
	MOV        AX,88					; 8*11
	MOV        BX,offset W_LineOffsets+96*2	; LineOffsets[96]
	MOV        DX,192/8*2				; == 24
L_05fe:
	MOV        DI,word ptr CS:[BX]		; LineOffsets[96]
	ADD        DI,DX					; DI=word[x:192, y:96]
	MOV        SI,word ptr CS:[BX + 16]	; LineOffsets[96+8]
	ADD        SI,DX					; SI=word[x:192, y:96+8]

	MOV        CX,16*2					; 16 characters width
	REP MOVSB							; DI <- SI [CX bytes]

	MOV        DI,word ptr CS:[BX]		; LineOffsets[96]
	ADD        DI,80
	ADD        DI,DX					; DI=word[x:192, y:96]
	MOV        SI,word ptr CS:[BX+16]	; LineOffsets[96+8]
	ADD        SI,80
	ADD        SI,DX					; SI=word[x:192, y:96+8]
	ADD        BX,2						; next line
	MOV        CX,16*2					; 16 characters width
	REP MOVSB							; DI <- SI [CX bytes]

	DEC        AX

	JNZ        L_05fe

	; Graphics Write Mode 0
	VGA_WRITE_GRAP 5h, 0h

	; Map Mask: 1111
	VGA_WRITE_SEQ 2h, 0fh

	; Clear last line
	MOV        AX,0
	MOV        BX,offset W_LineOffsets+184*2	; y=184
	MOV        DX,8								; rep 8

L_0630:
	MOV        DI,word ptr CS:[BX]
	ADD        DI,24*2					; x=192(*2)
	MOV        CX,8*2
	REP STOSW							; DI <- SI [CX words]

	MOV        DI,word ptr CS:[BX]
	ADD        DI,80					; next line
	ADD        DI,24*2					; x=192(*2)
	ADD        BX,2
	MOV        CX,8*2
	REP STOSW							; DI <- SI [CX words]

	DEC        DX
	JNZ        L_0630

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	RETF
	; Func
	; Func
DrvFunc08CR ENDP
;----------------------------------------
;Gra_09
;----------------------------------------
;invert main window
DrvFunc09 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES
	PUSH       DX

	VGA_WRITE_SEQ 2h, 7h
	VGA_WRITE_GRAP 3h, 18h

	MOV        ES,word ptr CS:W_GR_SEGMENT

	MOV        AH,176
	MOV        BX,16

L_066d:
	; even
	MOV        CX,22*2
	MOV        DI,word ptr CS:W_LineOffsets[BX]
	MOV        DX,DI
	ADD        BX,2
	ADD        DI,2

L_0679:
	OR         byte ptr ES:[DI],0ffh
	INC        DI
	LOOP       L_0679

	; odd
	MOV        CX,22*2
	MOV        DI,DX
	ADD        DI,VGA_LINE_STRIDE+2

L_0679_Odd:
	OR         byte ptr ES:[DI],0ffh
	INC        DI
	LOOP       L_0679_Odd

	; next line
	DEC        AH
	JNZ        L_066d

	VGA_WRITE_GRAP 3h, 0h

	POP        DX
	POP        ES
	POP        DI
	POP        BP
	RETF
	; Func
	; Func
DrvFunc09 ENDP
;----------------------------------------
;Gra_10
;----------------------------------------
;clear main window
DrvFunc10 PROC FAR
	PUSH       DI
	PUSH       ES
	PUSH       DX

	MOV        ES,word ptr CS:W_GR_SEGMENT

	VGA_WRITE_SEQ 2h, 0fh

	MOV        AX,0h
	MOV        ES,word ptr CS:W_GR_SEGMENT

	MOV        BX,16

L_06b2:
	MOV        DI,word ptr CS:W_LineOffsets[BX]
	MOV        DX,DI
	ADD        BX, 2
	ADD        DI, 2

	MOV        CX,22
	REP STOSW

	MOV        DI,DX
	ADD        DI, VGA_LINE_STRIDE+2

	MOV        CX,22
	REP STOSW

	CMP        BX,368
	JNZ        L_06b2

	POP        DX
	POP        ES
	POP        DI
	RETF
DrvFunc10 ENDP
;----------------------------------------
;Gra_11(pascal)
;----------------------------------------
;invert one text line(status box)
DrvFunc11 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES

	VGA_WRITE_SEQ 2h, 7h

	; XOR mode
	VGA_WRITE_GRAP 3h, 18h

	MOV        ES,word ptr CS:W_GR_SEGMENT
	MOV        BX,word ptr [BP + 6h]
	INC        BX
	SHLM       BX,4
	MOV        AH,8h
L_06f9:
	MOV        CX,15*2
	MOV        DI,word ptr CS:W_LineOffsets[BX]
	ADD        BX,2h
	ADD        DI,24*2
L_0707:
	OR         byte ptr ES:[DI],0ffh
	OR         byte ptr ES:[DI+VGA_LINE_STRIDE],0ffh
	INC        DI
	LOOP       L_0707
	DEC        AH
	JNZ        L_06f9

	VGA_WRITE_GRAP 3h, 0h

	POP        ES
	POP        DI
	POP        BP
	RETF       2h
DrvFunc11 ENDP
;----------------------------------------
;Gra_12(cdecl)(uncalled)
;----------------------------------------
;invert one char(status box)
DrvFunc12 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	POP        ES
	POP        BP
	RETF
	; Func
	; Func
DrvFunc12 ENDP
;----------------------------------------
;Gra_13
;----------------------------------------
;clear status box
DrvFunc13 PROC FAR
	PUSH       DI
	PUSH       ES

	VGA_WRITE_SEQ 2h, 0fh

	MOV        AX,0h
	MOV        ES,word ptr CS:W_GR_SEGMENT
	MOV        BX,10h
L_07ab:
	MOV        DI,word ptr CS:W_LineOffsets[BX]
	ADD        DI,18h*2
	MOV        CX,0fh*2
	REP STOSB

	MOV        DI,word ptr CS:W_LineOffsets[BX]
	ADD        DI,VGA_LINE_STRIDE
	ADD        DI,18h*2
	ADD        BX,2h
	MOV        CX,0fh*2
	REP STOSB

	CMP        BX,90h
	JNZ        L_07ab

	POP        ES
	POP        DI
	RETF
	; Func
	; Func
DrvFunc13 ENDP
;----------------------------------------
;Gra_dot_OR(cdecl)
;----------------------------------------
DrvFunc14DotOR PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	MOV        ES,word ptr CS:[W_GR_SEGMENT]
	; X *= 2
	MOV        CX,word ptr [BP + 8h]
	SHL        CX,1
	MOV        word ptr [BP + 8h],CX
	AND        CX,7h

	UOUTPORTB VGA_GRAP_ADDR, 8h
	MOV        DX,VGA_GRAP_DATA
	MOV        AL,0C0h
	SHR        AL,CL
	OUT        DX,AL

	UOUTPORTB VGA_SEQ_ADDR, 2h

	MOV        DX,VGA_SEQ_DATA
	MOV        BL,byte ptr [BP + 0ah] ; param_3_col
	MOV        BH,0h
	MOV        AL,byte ptr CS:B_DotColorTable[BX]
	OUT        DX,AL

	MOV        BX,word ptr [BP + 6h] ; param_1_y
	SHL        BX,1h
	MOV        BX,word ptr CS:W_LineOffsets[BX]
	MOV        AX,word ptr [BP + 8h] ; param_2_x
	SHRM       AX,3
	ADD        BX,AX

	OR         byte ptr ES:[BX],0ffh
	OR         byte ptr ES:[BX+VGA_LINE_STRIDE],0ffh

	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        BP
	RETF
DrvFunc14DotOR ENDP
;----------------------------------------
;Gra_dot_XOR(cdecl)
;----------------------------------------
DrvFunc15DotXOR PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	MOV        ES,word ptr CS:[W_GR_SEGMENT]
	; X *= 2
	MOV        CX,word ptr [BP + 8h]
	SHL        CX,1
	MOV        word ptr [BP + 8h],CX
	AND        CX,7h

	; XOR mode
	VGA_WRITE_GRAP 3h, 18h

	UOUTPORTB VGA_GRAP_ADDR, 8h
	MOV        DX,VGA_GRAP_DATA
	MOV        AL,0C0h
	SHR        AL,CL
	OUT        DX,AL

	UOUTPORTB VGA_SEQ_ADDR, 2h

	MOV        DX,VGA_SEQ_DATA
	MOV        BL,byte ptr [BP + 0ah]
	MOV        BH,0h
	MOV        AL,byte ptr CS:B_DotColorTable[BX]
	OUT        DX,AL

	MOV        BX,word ptr [BP + 6h]
	SHL        BX,1h
	MOV        BX,word ptr CS:W_LineOffsets[BX]
	MOV        AX,word ptr [BP + 8h]
	SHRM       AX,3
	ADD        BX,AX

	OR         byte ptr ES:[BX],0ffh
	OR         byte ptr ES:[BX+VGA_LINE_STRIDE],0ffh

	VGA_WRITE_GRAP 3h, 0h
	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        BP
	RETF
DrvFunc15DotXOR ENDP
;----------------------------------------
;Gra_dot(cdecl)
;----------------------------------------
DrvFunc06Dot PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES

	MOV        ES,word ptr CS:W_GR_SEGMENT
	; X *= 2
	MOV        CX,word ptr [BP + 8h]
	SHL        CX,1
	MOV        word ptr [BP + 8h],CX

	AND        CX,7h

	VGA_WRITE_GRAP 3h, 18h

	UOUTPORTB VGA_GRAP_ADDR, 8h ; Set Bitmask
	MOV        DX,VGA_GRAP_DATA
	MOV        AL,0C0h
	SHR        AL,CL
	OUT        DX,AL

	VGA_WRITE_SEQ 2h, 0fh

	MOV        BX,word ptr [BP + 6h]
	SHL        BX,1h
	MOV        BX,word ptr CS:W_LineOffsets[BX]
	MOV        DI,word ptr [BP + 8h]
	SHRM       DI,3 ; DI /= 8
	ADD        DI,BX

	VGA_WRITE_GRAP 3h, 8h

	AND        byte ptr ES:[DI],0h

	MOV        DX,VGA_SEQ_DATA
	MOV        BL,byte ptr [BP + 0ah]
	MOV        BH,0h
	MOV        AL,byte ptr CS:B_DotColorTable[BX]
	OUT        DX,AL

	UOUTPORTB VGA_GRAP_DATA, 10h

	OR         byte ptr ES:[DI],0ffh
	OR         byte ptr ES:[DI+VGA_LINE_STRIDE],0ffh

	VGA_WRITE_GRAP 3h, 0h
	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        DI
	POP        BP
	RETF
DrvFunc06Dot ENDP

;----------------------------------------
;Gra_16(cdecl)
;----------------------------------------
; load and draw image (rle)
; char* fileName, void* dst (null = screen)
DrvFunc16 PROC FAR
	UOUTPORTB VGA_SEQ_ADDR, 2h ; Color plane mask
	UOUTPORTB VGA_GRAP_ADDR, 8h ; Bitmask

	PUSH       BP
	MOV        BP,SP
	SUB        SP,0eh
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	MOV        AX,SS
	MOV        DS,AX

	; local_8 = _dopen(fileName, 0)
	MOV        AX,0h
	PUSH       AX
	PUSH       word ptr [BP + 6h] ; param_1: fileName
	CALL       _dopen
	ADD        SP,4h
	MOV        word ptr [BP + -6h],AX ; local_8: fp

	; if AX == -1: fail
	INC        AX
	JNZ        L_0954

L_094a:
	; Fail if _dopen is failed
	MOV        AX,3h
	PUSH       AX
	PUSH       AX
	JMP DWORD PTR CS:W_pExit_0

L_0954:
	; local_10 = fseek(fp, 0, SEEK_END)
	MOV        BX,word ptr [BP + -6h] ; local_8: fp
	MOV        AL,2h ; SEEK_END
	MOV        CX,0h
	MOV        DX,0h
	MOV        AH,42h
	INT        21h
	MOV        word ptr [BP + -0eh],AX ; local_10

	; fseek(fp, 0, SEEK_SET)
	MOV        BX,word ptr [BP + -6h] ; local_8: fp
	MOV        AL,0h
	MOV        CX,0h
	MOV        DX,0h
	MOV        AH,42h
	INT        21h

	; malloc(local_10)
	PUSH       word ptr [BP + -0eh] ; local_10
	CALL       _dalloc
	ADD        SP,2h
	MOV        word ptr [BP + -2h],DX ; local_4=buf segment
	MOV        word ptr [BP + -4h],AX ; local_6=buf offs(0)
	TEST       DX,0ffffh
	JZ         L_094a		; if failed: goto error

	MOV        DX,0h
	MOV        DI,word ptr [BP + 8h] ; param_2 buf.offs
	MOV        BX,0h

	MOV        ES,word ptr [BP + 0ah] ; param_3 buf.seg
	TEST       word ptr [BP + 0ah],0ffffh ; param_3 buf.seg
	JNZ        L_09ab ; if (buf != 0) goto 09ab
	MOV        ES,word ptr CS:W_GR_SEGMENT

L_09ab:
	PUSH       BX
	PUSH       DX
	PUSH       DI
	; local_4 = dread(..., local_10)
	PUSH       word ptr [BP + -0eh] ; local_10=buf size
	PUSH       word ptr [BP + -2h] ; local_4=buf seg
	PUSH       word ptr [BP + -4h] ; local_6=buf offs
	PUSH       word ptr [BP + -6h] ; local_8: fp
	CALL       _dread
	ADD        SP,8h
	MOV        DS,word ptr [BP + -2h] ; local_4; DS = image buffer seg
	POP        DI
	POP        DX
	POP        BX

	MOV        SI,word ptr [BP + -4h] ; local_6=buf offs
	MOV        byte ptr [BP + -0ch],80h ; local_e
	TEST       word ptr [BP + 0ah],0ffffh ; param_3 buf.seg
	JNZ        L_09d7 ; if (buf != 0) goto 09d7
	JMP        L_0a50

	; Decode to memory
L_09d7:
	MOV        AH,80h
	MOV        BX,8000
	PUSH       AX
	PUSH       CX
	PUSH       DI
	MOV        AX,0h
	MOV        CX,16000
	REP STOSW				; Clear target memory
	POP        DI
	POP        CX
	POP        AX

L_09ea:
	MOV        CX,1h
	LODSB
	CMP        AL,RLE_RUNSTART
	JNZ        L_09f8
	LODSB
	MOV        CL,AL
	LODSB
	MOV        CH,AL
L_09f8:
	SHL        AL,1h
	JNC        L_09ff
	OR         byte ptr ES:[DI],AH
L_09ff:
	SHL        AL,1h
	JNC        L_0a08
	OR         byte ptr ES:[DI + 8000],AH
L_0a08:
	SHL        AL,1h
	JNC        L_0a11
	OR         byte ptr ES:[DI + 16000],AH
L_0a11:
	SHL        AL,1h
	JNC        L_0a1a
	OR         byte ptr ES:[DI + 24000],AH
L_0a1a:
	SHR        AH,1h

	SHL        AL,1h
	JNC        L_0a23
	OR         byte ptr ES:[DI],AH
L_0a23:
	SHL        AL,1h
	JNC        L_0a2c
	OR         byte ptr ES:[DI + 8000],AH
L_0a2c:
	SHL        AL,1h
	JNC        L_0a35
	OR         byte ptr ES:[DI + 16000],AH
L_0a35:
	SHL        AL,1h
	JNC        L_0a3e
	OR         byte ptr ES:[DI + 24000],AH
L_0a3e:
	SHR        AH,1h
	MOV        AL,CH
	JNC        L_0a4a
	MOV        AH,80h
	INC        DI
	DEC        BX
	JZ         L_0aba ; Exit
L_0a4a:
	DEC        CL
	JNZ        L_09f8
	JMP        L_09ea

	; Decode RLE to vram
L_0a50:
	MOV        CX,1h
	LODSB ; DS:SI <- AL
	CMP        AL,RLE_RUNSTART ; AL == RLE_RUNSTART
	JNZ        L_0a5c ; CL = 1, AL = value

	LODSB ; DS:SI <- AL
	MOV        CL,AL
	LODSB ; DS:SI <- AL
	; CL = count, AL = value

	; Run!
L_0a5c:
	PUSH       DX
	PUSH       AX

	; put first pixel
	MOV        DX,VGA_SEQ_DATA ; Color plane mask
	SHRM       AL,4 ; al /= 16
	OUT        DX,AL

	MOV        DX,VGA_GRAP_DATA ; Set bitmask
	MOV        AL,byte ptr [BP + -0ch] ; local_e
	OUT        DX,AL

	OR         byte ptr ES:[BX + DI],0ffh ; Put pixel
	OR         byte ptr ES:[BX + DI + VGA_LINE_STRIDE],0ffh ; Put pixel

	ROR        byte ptr [BP + -0ch],1h ; local_e; Rotate
	CMP        byte ptr [BP + -0ch],80h ; local_e

	; put mag
	MOV        DX,VGA_GRAP_DATA ; Set bitmask
	MOV        AL,byte ptr [BP + -0ch] ; local_e
	OUT        DX,AL

	OR         byte ptr ES:[BX + DI],0ffh ; Put pixel
	OR         byte ptr ES:[BX + DI + VGA_LINE_STRIDE],0ffh ; Put pixel

	ROR        byte ptr [BP + -0ch],1h ; local_e; Rotate
	CMP        byte ptr [BP + -0ch],80h ; local_e
	JNZ        L_0a7f ; if (local_e != 80h) goto 0a7f
	INC        BX ; increment x

	; Skip trampoline
	JMP L_0a7f
L_F16_0a5c_TRAMPOLINE:
	JMP L_0a5c

L_0a7f:
	POP        AX
	PUSH       AX

	; put second pixel
	MOV        DX,VGA_SEQ_DATA ; Color plane mask
	AND        AL,0fh ;al &= 0fh
	OUT        DX,AL

	MOV        DX,VGA_GRAP_DATA ; Set bitmask
	MOV        AL,byte ptr [BP + -0ch] ; local_e
	OUT        DX,AL

	OR         byte ptr ES:[BX + DI],0ffh ; Put pixel
	OR         byte ptr ES:[BX + DI + VGA_LINE_STRIDE],0ffh ; Put pixel

	ROR        byte ptr [BP + -0ch],1h ; local_e
	CMP        byte ptr [BP + -0ch],80h ; local_e

	; put mag
	MOV        DX,VGA_GRAP_DATA ; Set bitmask
	MOV        AL,byte ptr [BP + -0ch] ; local_e
	OUT        DX,AL

	OR         byte ptr ES:[BX + DI],0ffh ; Put pixel
	OR         byte ptr ES:[BX + DI + VGA_LINE_STRIDE],0ffh ; Put pixel

	ROR        byte ptr [BP + -0ch],1h ; local_e
	CMP        byte ptr [BP + -0ch],80h ; local_e

	JNZ        L_0a9c ; if (local_e != 80h) goto 0a9c
	INC        BX ; increment x

L_0a9c:
	POP        AX
	POP        DX
	CMP        BX,VGA_LINE_STRIDE
	JC         L_0ab6

	; Increment Line
	INC        DX ; increment line index
	CMP        DX,LINE_COUNT
	JZ         L_0aba ; Exit

	; DI <- Next line offset
	MOV        DI,DX
	SHL        DI,1h ; *= 2
	MOV        DI,word ptr CS:W_LineOffsets[DI]
	MOV        BX,0h
 
L_0ab6:
	LOOP       L_F16_0a5c_TRAMPOLINE ; Decrement CX, loop if CX <> 0

	JMP        L_0a50

L_0aba:
	; cleanup
	PUSH       word ptr [BP + -6h] ; local_8
	CALL       _dclose
	ADD        SP,2h

	PUSH       word ptr [BP + -2h] ; local_4
	PUSH       word ptr [BP + -4h] ; local_6
	CALL       _dfree
	ADD        SP,4h

	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF
DrvFunc16 ENDP

;----------------------------------------
;Gra_17(pascal)
;----------------------------------------
DrvFunc17 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,6h
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        AX,SS
	MOV        DS,AX ; DS=SS
	MOV        AX,32000
	PUSH       AX
	CALL       _dalloc
	ADD        SP,2h
	MOV        word ptr [BP + -2h],DX ; local_4=buf segment
	MOV        word ptr [BP + -4h],AX ; local_6=buf offs(0)
	TEST       DX,0ffffh
	JNZ        L_0b1d					; if success: goto 0b1d
	;PUSH       CS
	CALL       DrvFunc10				; _dalloc failed; clear main window
	MOV        AX,0h
	PUSH       AX
	PUSH       AX
	PUSH       word ptr [BP + 6h]
	;PUSH       CS
	CALL       DrvFunc16				; draw directly to screen?
	ADD        SP,6h
	JMP        L_0c0a					; goto end

L_0b1d:
	MOV        ES,DX	; ES = buf.seg
	MOV        DI,AX	; DI = buf.offs
	MOV        CX,16000
	MOV        AX,0h
	REP STOSW			; clear buffer

	PUSH       word ptr [BP + -2h] ; buf.seg
	PUSH       word ptr [BP + -4h] ; buf.offs
	PUSH       word ptr [BP + 6h] ; filename
	;PUSH       CS
	CALL       DrvFunc16	; load image into buffer
	ADD        SP,6h

	; Animation
	LDS        AX,[BP + -4h] ; DS:AX <- [BP-4]
	MOV        ES,word ptr CS:W_GR_SEGMENT
	MOV        CL,1h

L_0b43:
	MOV        DI,8h

L_0b46:
	VGA_WRITE_GRAP 5h, 1h
	VGA_WRITE_SEQ 2h, 0fh

	MOV        SI,DI
	SHL        SI,1h
	MOV        SI,word ptr CS:W_LineOffsets[SI]	; di*2

	MOV        BX,1*2
	MOV        DX,12*2
	SUB        DL,CL
	SUB        DL,CL
L_0b6f:
	MOV        AL,byte ptr ES:[BX + SI + 1]
	MOV        byte ptr ES:[BX + SI],AL

	MOV        AL,byte ptr ES:[BX + SI + 1 + VGA_LINE_STRIDE]
	MOV        byte ptr ES:[BX + SI + VGA_LINE_STRIDE],AL

	INC        BX
	CMP        BX,DX
	JC         L_0b6f

	MOV        BX,22*2+1
	MOV        DX,12*2
	ADD        DL,CL
	ADD        DL,CL
L_0b83:
	MOV        AL,byte ptr ES:[BX + SI + -1h]
	MOV        byte ptr ES:[BX + SI],AL
	MOV        AL,byte ptr ES:[BX + SI + -1h + VGA_LINE_STRIDE]
	MOV        byte ptr ES:[BX + SI + VGA_LINE_STRIDE],AL
	DEC        BX
	CMP        BX,DX
	JNC        L_0b83
	INC        DI
	CMP        DI,184
	JC         L_0b46

	VGA_WRITE_GRAP 5h, 0h

L_0ba2:
	MOV        word ptr [BP + -6h],0h ; local_8 = 0
	MOV        AL,8h
L_0ba9:
	MOV        AH,8h
	MOV        DX,VGA_SEQ_DATA
	OUT        DX,AL
L_0baf:
	MOV        BL,AH
	MOV        BH,0h

	MOV        SI,BX
	SHL        SI,1h
	MOV        SI,word ptr CS:W_LineOffsets[SI]
	MOV        DI,SI ; DI = Line[AH*2]
	SHRM       SI,2 ; HACK

	ADD        SI,word ptr [BP + -6h] ; SI += local_8

	MOV        BX,12
	SUB        BL,CL ; BX = 12-CL
	ADD        SI,BX ; SI += BX

	ADD        DI,BX ; DI += BX
	ADD        DI,BX ; DI += BX

	MOV        DX,11
	ADD        DL,CL
	SUB        DX,BX ; DX = 11+CL-BX = 2*CL-1

	XCHG       CX,DX
	INC        CX

L_17_LOOP:
	PUSH AX
	PUSH CX
	LODSB									; AL <- [DS:SI], SI++
	MAGNIFY
	MOV word ptr ES:[DI],AX
	MOV word ptr ES:[DI + VGA_LINE_STRIDE],AX
	ADD DI,2
	POP CX
	POP AX
	LOOP L_17_LOOP

	XCHG       CX,DX

	INC        AH
	CMP        AH,184
	JC         L_0baf
	ADD        word ptr [BP + -6h],8000 ; local_8 += 8000
	SHR        AL,1h
	JNC        L_0ba9

	MOV AX, 4
L_17_A:
	PUSH AX
	MOV        AX,0h

	; Delay
L_0beb:
	PUSH AX
	POP AX
	DEC        AX
	JNZ        L_0beb

	POP AX
	DEC AX
	JNZ L_17_A

	INC        CL
	CMP        CL,11
	JNC        L_0bf8
	JMP        L_0b43
L_0bf8:
	JZ         L_0ba2

	MOV        AX,SS
	MOV        DS,AX
	PUSH       word ptr [BP + -2h]
	PUSH       word ptr [BP + -4h]
	CALL       _dfree
	ADD        SP,4h
L_0c0a:
	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF       2h
DrvFunc17 ENDP

;----------------------------------------
;Gra_18(cdecl)
;----------------------------------------
DrvFunc18 PROC FAR C x0: WORD, x1: WORD, y0: WORD, y1: WORD, y0p: WORD, y1p: WORD, col0: BYTE, col1: BYTE
	LOCAL local_4: WORD
	LOCAL local_6: WORD
	LOCAL local_8: WORD
	LOCAL local_a: WORD
	LOCAL local_c: WORD
	LOCAL local_e: WORD
	LOCAL local_10: WORD
	LOCAL local_12: WORD

	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	UOUTPORTB VGA_GRAP_ADDR, 8h
	UOUTPORTB VGA_SEQ_ADDR, 2h

	MOV        AX, x1
	SHL        AX, 1
	MOV        x1, AX
	MOV        AX, x0
	SHL        AX, 1
	MOV        x0, AX

	;MOV        AX, x0
	MOV        local_12, AX ; local_12 = x0
	MOV        AX, y0
	MOV        local_8, AX ; local_8 = y0
	MOV        AX, y1
	MOV        local_c, AX ; local_c = y1

	MOV        SI, x1
	SUB        SI, x0
	PUSH       SI
	CALL       _testsign
	ADD        SP, 2h
	MOV        local_4, AX ; local_4 = sign(x1 - x0)

	MOV        AX, y0p
	SUB        AX, y0
	PUSH       AX
	CALL       _testsign
	ADD        SP, 2h
	MOV        local_a, AX ; local_a = sign(y0p - y0)

	MOV        AX, y1p
	SUB        AX, y1
	PUSH       AX
	CALL       _testsign
	ADD        SP,2h
	MOV        local_10, AX ; local_10 = sign(y1p - y1)

	PUSH       SI
	CALL       _abs
	ADD        SP,2h
	SHR        AX,1h ; ax = abs(x1 - x0) / 2
	MOV        local_e, AX ; local_e = ax
	MOV        local_6, AX ; local_6 = ax

	MOV        DS,word ptr CS:W_GR_SEGMENT

L_0c80: ; for each stripe
	MOV        CL, byte ptr local_12
	AND        CL,7h
	MOV        AL,80h
	SHR        AL,CL
	MOV        DX,VGA_GRAP_DATA
	OUT        DX,AL

	MOV        SI, local_12			; si(x) = local_12 / 8
	SHRM       SI,3
	MOV        DI, local_8
	SHL        DI,1h				; line = local_8 / 2
	MOV        CX, local_c
	SUB        CX, local_8
	INC        CX
	MOV        DX,VGA_SEQ_DATA

	TEST       col1, 0ffh
	JZ         L_0cbe

	MOV        AL,0fh ; when col1 != 0ffh
	OUT        DX,AL
L_0caf:
	MOV        BX,word ptr CS:W_LineOffsets[DI]	; bx = [line++]
	ADD        DI,2h
	AND        byte ptr [BX + SI],0h			; CLEAR?
	AND        byte ptr [BX + VGA_LINE_STRIDE + SI],0h
	LOOP       L_0caf
	JMP        L_0cd6

L_0cbe:
	MOV        BL, col0 ; when col1 == 0ffh
	MOV        BH,0h
	MOV        AL,byte ptr CS:B_DotColorTable[BX]
	OUT        DX,AL
L_0cc9:
	MOV        BX,word ptr CS:W_LineOffsets[DI]	; bx = [line++]
	ADD        DI,2h
	OR         byte ptr [BX + SI],0ffh			; PLOT
	OR         byte ptr [BX + VGA_LINE_STRIDE + SI],0ffh
	LOOP       L_0cc9
L_0cd6:
	MOV        AX, local_4
	ADD        local_12, AX

	; abs
	MOV        AX, y0p
	SUB        AX, y0
	JNS        L_0ce6
	NEG        AX
L_0ce6:
	SUB        local_e, AX ; local_e -= abs(y0p - y0)

	; abs
	MOV        AX, y1p
	SUB        AX, y1
	JNS        L_0cf3
	NEG        AX
L_0cf3:
	SUB        local_6, AX ; local_6 -= abs(y1p - y1)

	JNS        L_0d0b ; if (local_6 > 0) goto 0d0b
	MOV        AX, local_a
	ADD        local_8, AX ; local_8 += local_a

	; abs
	MOV        SI, x1
	SUB        SI, x0
	JNS        L_0d08
	NEG        SI
L_0d08:
	ADD        local_e, SI ; local_e += abs(x1 - x0)

L_0d0b:
	CMP        local_6, 0h
	JNS        L_0d1a
	MOV        AX, local_10
	ADD        local_c, AX
	ADD        local_6, SI
L_0d1a:
	MOV        AX, local_12
	CMP        AX, x1
	JZ         L_0d25
	JMP        L_0c80
L_0d25:

	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        DS
	POP        DI
	POP        SI

	MOV SP,BP
	POP BP
	RETF
DrvFunc18 ENDP

;----------------------------------------
;Gra_19(pascal)
;----------------------------------------
DrvFunc19 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       SI
	PUSH       ES

	LES        BX,dword ptr CS:W_pCharset_0

	MOV        SI,7h
L_0d46:
	MOV        AX,SI
	SHL        AX,1h
	MOV        DI,AX ; DI = SI * 2
	ADD        DI,word ptr [BP + 6h]			; param_1; pKarmas
	MOV        DI,word ptr SS:[DI]				; DI = pKarmas[SI*2]
	CMP        word ptr SS:[DI],0h
	JNZ        L_0d7d

	MOV        AL,byte ptr ES:[BX + SI + 0h]
	MOV        byte ptr ES:[BX + SI + 7*32+0h],AL	; pCharset[SI + 7*32+0h] <- pCharset[SI+0h]
	MOV        AL,byte ptr ES:[BX + SI + 8h]
	MOV        byte ptr ES:[BX + SI + 7*32+8h],AL	; pCharset[SI + 7*32+8h] <- pCharset[SI+8h]
	MOV        AL,byte ptr ES:[BX + SI + 10h]
	MOV        byte ptr ES:[BX + SI + 7*32+10h],AL	; ...
	MOV        AL,byte ptr ES:[BX + SI + 18h]
	MOV        byte ptr ES:[BX + SI + 7*32+18h],AL
	JMP        L_0d95

L_0d7d:
	MOV        byte ptr ES:[BX + SI + 7*32+0h],0h	; pCharset[7*32+0h] = 0
	MOV        byte ptr ES:[BX + SI + 7*32+8h],0h	; pCharset[7*32+8h] = 0
	MOV        byte ptr ES:[BX + SI + 7*32+10h],0h	; ...
	MOV        byte ptr ES:[BX + SI + 7*32+18h],0h

L_0d95:
	DEC        SI
	JNS        L_0d46

	POP        ES
	POP        SI
	POP        DI
	POP        BP
	RETF       2h
DrvFunc19 ENDP

;----------------------------------------
;Gra_animSpit
;----------------------------------------
DrvFunc20AnimSpit PROC FAR
	PUSH       DS
	LDS        BX,dword ptr CS:W_pShapes_0
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,0h
	AND        AL,0ch
	XOR        word ptr [BX + 25aeh],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,80h
	AND        AL,0dh
	XOR        word ptr [BX + 25b0h],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,0c0h
	AND        AL,1fh
	XOR        word ptr [BX + 25b2h],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,0c0h
	AND        AL,1fh
	XOR        word ptr [BX + 25b4h],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,80h
	AND        AL,0fh
	XOR        word ptr [BX + 25b6h],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,0c0h
	AND        AL,1fh
	XOR        word ptr [BX + 25b8h],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,40h
	AND        AL,12h
	XOR        word ptr [BX + 25bah],AX
	CALL       _random
	MOV        AH,AL
	CALL       _random
	AND        AH,0c0h
	AND        AL,18h
	XOR        word ptr [BX + 25bch],AX
	POP        DS
	RETF
DrvFunc20AnimSpit ENDP

;----------------------------------------
;Gra_init(cdecl)
;----------------------------------------
DrvFunc21Init PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	MOV        AH,0h	; Set video mode
	MOV        AL,10h	; mode 10h
	INT        10h

	;
	; Setup 640x400x16
	;

	; Misc Read
	MOV        DX,03CCH
	IN         AL,DX
	AND        AL,03FH
	OR         AL,40H

	; Misc Write
	MOV        DX,03C2H
	OUT        DX,AL

	MOV        DX,VGA_CRTC_ADDR

	MOV        AX,9C10H
	OUT        DX,AX
	IODELAY

	MOV        AX,8311H
	OUT        DX,AX
	IODELAY

	MOV        AX,8F12H
	OUT        DX,AX
	IODELAY

	MOV        AX,9615H
	OUT        DX,AX
	IODELAY

	MOV        AX,0B916H
	OUT        DX,AX
	IODELAY

	; End of setting up 400p

	PUSH       CS
	POP        ES

	MOV        DX,offset W_PaletteTable
	MOV        AH,10h	; Set EGA palette registers
	MOV        AL,2h
	INT        10h

	; Seq Addr: Select Color Plane
	; Seq Data: RGBI
	VGA_WRITE_SEQ 2h, 0fh

	; Grap Addr: Plane Mask
	; Grap Data: FFh
	VGA_WRITE_GRAP 8h, 0ffh

	; Load Shape Pointer
	MOV        BX,word ptr [BP + 6h]
	MOV        AX,word ptr SS:[BX]
	MOV        CS:[W_pShapes_0],AX
	MOV        AX,word ptr SS:[BX + 2h]
	MOV        CS:[W_pShapes_1],AX

	; Load Charset Pointer
	MOV        BX,word ptr [BP + 8h]
	MOV        AX,word ptr SS:[BX]
	MOV        CS:[W_pCharset_0],AX
	MOV        AX,word ptr SS:[BX + 2h]
	MOV        CS:[W_pCharset_1],AX

	; Load Exit Callback Pointer
	MOV        AX,word ptr [BP + 0ah]
	MOV        CS:[W_pExit_0],AX
	MOV        AX,word ptr [BP + 4h]
	MOV        CS:[W_0050],AX

	; Calculate Line Offsets
	MOV        AX,0
	MOV        CX,LINE_COUNT
	LEA        BX,CS:[W_LineOffsets]
L_0e97:
	MOV        word ptr CS:[BX],AX
	ADD        BX,2
	ADD        AX,VGA_LINE_STRIDE*2
	LOOP       L_0e97

	POP        ES
	POP        BP
	RETF
DrvFunc21Init ENDP

;----------------------------------------
;Gra_clrscr
;----------------------------------------
DrvFunc22ClrScr PROC FAR
	PUSH       DI
	PUSH       ES

	VGA_WRITE_SEQ 2h, 0fh

	MOV        AX,0h
	MOV        ES,word ptr CS:W_GR_SEGMENT
	MOV        DI,0h
	MOV        CX,16000
	REP STOSW

	POP        ES
	POP        DI
	RETF
DrvFunc22ClrScr ENDP

;----------------------------------------
;random
;----------------------------------------
_random PROC NEAR
	MOV        AL,CS:[B_0039]
	ADC        AL,byte ptr CS:[B_0038]
	MOV        CS:[B_0038],AL
	XOR        byte ptr CS:[B_0037],AL
	MOV        AL,CS:[B_0037]
	ADC        AL,byte ptr CS:[B_0036]
	ROR        AL,1h
	MOV        CS:[B_0036],AL
	MOV        CS:[B_0039],AL
	TEST       AL,0ffh
	RET
_random ENDP

;----------------------------------------
;test sign
;----------------------------------------
_testsign PROC NEAR
	PUSH       BP
	MOV        BP,SP
	TEST       word ptr [BP + 4h],0ffffh
	JZ         L_0f04
	JNS        L_0eff
	MOV        AX,0ffffh
	JMP        L_0f07
L_0eff:
	MOV        AX,1h
	JMP        L_0f07
L_0f04:
	MOV        AX,0h
L_0f07:
	POP        BP
	RET
_testsign ENDP

;----------------------------------------
;abs
;----------------------------------------
_abs PROC NEAR
	PUSH       BP
	MOV        BP,SP
	MOV        AX,word ptr [BP + 4h]
	TEST       AX,0ffffh
	JNS        L_0f16
	NEG        AX
L_0f16:
	POP        BP
	RET
_abs ENDP

; dos functions
; _dalloc
_dalloc:
	PUSH       BP
	MOV        BP,SP
	MOV        BX,word ptr [BP + 4h]
	SHR        BX,1h
	SHR        BX,1h
	SHR        BX,1h
	SHR        BX,1h
	TEST       word ptr [BP + 4h],0fh
	JZ         L_0f2e
	INC        BX
L_0f2e:
	MOV        AH,48h
	INT        21h
	MOV        DX,AX
	MOV        AX,0h
	JNC        L_0f43
	PUSH       AX
	PUSH       AX
	JMP DWORD PTR CS:[W_pExit_0]
	db 0BAh
	db 00h
	db 00h
L_0f43:
	MOV        SP,BP
	POP        BP
	RET

_dfree:
	PUSH       ES
	PUSH       BP
	MOV        BP,SP
	MOV        ES,word ptr [BP + 8h]
	MOV        AH,49h
	INT        21h
	MOV        AX,0h
	JNC        L_0f5a
	MOV        AX,0ffffh
L_0f5a:
	MOV        SP,BP
	POP        BP
	POP        ES
	RET

_dopen:
	PUSH       BP
	MOV        BP,SP
	MOV        DX,word ptr [BP + 4h]
	MOV        AL,byte ptr [BP + 6h]
	MOV        AH,3dh
	INT        21h
	JNC        L_0f71
	MOV        AX,0ffffh
L_0f71:
	MOV        SP,BP
	POP        BP
	RET

_dread:
	PUSH       BP
	MOV        BP,SP
	PUSH       DS
	PUSH       SI
	PUSH       DI
	MOV        BX,word ptr [BP + 4h]
	MOV        CX,word ptr [BP + 0ah]
	MOV        DX,word ptr [BP + 6h]
	MOV        AX,word ptr [BP + 8h]
	MOV        DS,AX
	MOV        AH,3fh
	INT        21h
	JNC        L_0f92
	MOV        AX,0ffffh
L_0f92:
	POP        DI
	POP        SI
	POP        DS
	MOV        SP,BP
	POP        BP
	RET

_dclose:
	PUSH       BP
	MOV        BP,SP
	MOV        BX,word ptr [BP + 4h]
	MOV        AH,3eh
	INT        21h
	JNC        L_0fa8
	MOV        AX,0ffffh
L_0fa8:
	MOV        SP,BP
	POP        BP
	RET

;----------------------------------------
;Gra_animFlow
;----------------------------------------
DrvFunc23AnimFlow PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSHF
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        DS,word ptr CS:W_pShapes_1
	MOV        AX,DS
	MOV        ES,AX
	MOV        BX,word ptr [BP + 6h]
	SHLM       BX,7
	ADD        BX,word ptr CS:W_pShapes_0
	PUSH       word ptr [BX + 1eh]
	PUSH       word ptr [BX + 3eh]
	PUSH       word ptr [BX + 5eh]
	PUSH       word ptr [BX + 7eh]
	STD
	LEA        SI,[BX + 7ch]
	LEA        DI,[BX + 7eh]
	MOV        CX,3fh
	REP MOVSW
	POP        word ptr [BX + 60h]
	POP        word ptr [BX + 40h]
	POP        word ptr [BX + 20h]
	POP        word ptr [BX]
	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POPF
	POP        BP
	RETF       2h
DrvFunc23AnimFlow ENDP

;----------------------------------------
;Gra_animFlag
;----------------------------------------
DrvFunc24AnimFlag PROC FAR
	PUSH       ES
	LES        BX,dword ptr CS:W_pShapes_0
	CALL       _random
	JS         L_1046
	MOV        AX,word ptr ES:[BX + 506h]
	XCHG       word ptr ES:[BX + 508h],AX
	MOV        word ptr ES:[BX + 506h],AX
	MOV        AX,word ptr ES:[BX + 526h]
	XCHG       word ptr ES:[BX + 528h],AX
	MOV        word ptr ES:[BX + 526h],AX
	MOV        AX,word ptr ES:[BX + 546h]
	XCHG       word ptr ES:[BX + 548h],AX
	MOV        word ptr ES:[BX + 546h],AX
	MOV        AX,word ptr ES:[BX + 566h]
	XCHG       word ptr ES:[BX + 568h],AX
	MOV        word ptr ES:[BX + 566h],AX
L_1046:
	CALL       _random
	JS         L_1087
	MOV        AX,word ptr ES:[BX + 582h]
	XCHG       word ptr ES:[BX + 584h],AX
	MOV        word ptr ES:[BX + 582h],AX
	MOV        AX,word ptr ES:[BX + 5a2h]
	XCHG       word ptr ES:[BX + 5a4h],AX
	MOV        word ptr ES:[BX + 5a2h],AX
	MOV        AX,word ptr ES:[BX + 5c2h]
	XCHG       word ptr ES:[BX + 5c4h],AX
	MOV        word ptr ES:[BX + 5c2h],AX
	MOV        AX,word ptr ES:[BX + 5e2h]
	XCHG       word ptr ES:[BX + 5e4h],AX
	MOV        word ptr ES:[BX + 5e2h],AX
L_1087:
	CALL       _random
	JS         L_10c8
	MOV        AX,word ptr ES:[BX + 804h]
	XCHG       word ptr ES:[BX + 806h],AX
	MOV        word ptr ES:[BX + 804h],AX
	MOV        AX,word ptr ES:[BX + 824h]
	XCHG       word ptr ES:[BX + 826h],AX
	MOV        word ptr ES:[BX + 824h],AX
	MOV        AX,word ptr ES:[BX + 844h]
	XCHG       word ptr ES:[BX + 846h],AX
	MOV        word ptr ES:[BX + 844h],AX
	MOV        AX,word ptr ES:[BX + 864h]
	XCHG       word ptr ES:[BX + 866h],AX
	MOV        word ptr ES:[BX + 864h],AX
L_10c8:
	CALL       _random
	JS         L_1109
	MOV        AX,word ptr ES:[BX + 904h]
	XCHG       word ptr ES:[BX + 906h],AX
	MOV        word ptr ES:[BX + 904h],AX
	MOV        AX,word ptr ES:[BX + 924h]
	XCHG       word ptr ES:[BX + 926h],AX
	MOV        word ptr ES:[BX + 924h],AX
	MOV        AX,word ptr ES:[BX + 944h]
	XCHG       word ptr ES:[BX + 946h],AX
	MOV        word ptr ES:[BX + 944h],AX
	MOV        AX,word ptr ES:[BX + 964h]
	XCHG       word ptr ES:[BX + 966h],AX
	MOV        word ptr ES:[BX + 964h],AX
L_1109:
	CALL       _random
	JS         L_114a
	MOV        AX,word ptr ES:[BX + 702h]
	XCHG       word ptr ES:[BX + 704h],AX
	MOV        word ptr ES:[BX + 702h],AX
	MOV        AX,word ptr ES:[BX + 722h]
	XCHG       word ptr ES:[BX + 724h],AX
	MOV        word ptr ES:[BX + 722h],AX
	MOV        AX,word ptr ES:[BX + 742h]
	XCHG       word ptr ES:[BX + 744h],AX
	MOV        word ptr ES:[BX + 742h],AX
	MOV        AX,word ptr ES:[BX + 762h]
	XCHG       word ptr ES:[BX + 764h],AX
	MOV        word ptr ES:[BX + 762h],AX
L_114a:
	POP        ES
	RETF
DrvFunc24AnimFlag ENDP
;----------------------------------------
;Gra_putchar(pascal); int c
;----------------------------------------
DrvFunc25PutChar PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	MOV        ES,word ptr CS:[W_GR_SEGMENT]
	MOV        AL,byte ptr [BP + 0ah]
	MOV        AH,0h
	SHLM       AX,5
	LDS        SI,dword ptr CS:[W_pCharset_0]
	ADD        SI,AX
	MOV        BX,word ptr [BP + 6h]
	SHLM       BX,4
	MOV        BX,word ptr CS:[BX + W_LineOffsets]
	MOV        AX,word ptr [BP + 8h]
	;SHL        AX,1
	ADD        BX,AX			; X

	UOUTPORTB VGA_SEQ_ADDR, 2h

	MOV        DX,3c5h
	MOV        CL,8h	; IO VALUE = 8
L_118c:
	MOV        AL,CL
	OUT        DX,AL						; IO <- AL: Select Color Plane

	PUSH       CX

	IRP line,<0,1,2,3,4,5,6,7>
		LODSB									; AL <- [DS:SI], SI++
		MAGNIFY
		MOV word ptr ES:[BX + VGA_LINE_STRIDE*line*2],AX
		MOV word ptr ES:[BX + VGA_LINE_STRIDE*(line*2+1)],AX
	ENDM

	POP        CX

	SHR        CL,1h	; IO VALUE >>= 1
	JNZ        L_118c

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       6h
DrvFunc25PutChar ENDP

L_COMPOSE:
	LDS        SI,dword ptr CS:[W_pCharset_0]
	ADD        SI,AX

	; Load into compose buffer
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		LODSW
		OR word ptr CS:B_KCHR_COMPOSE[line*2],AX
	ENDM

	RET

L_COMPOSE_E:
	LDS        SI,dword ptr CS:[W_pCharset_0]
	ADD        SI,AX

	; Load into compose buffer
	IRP line,<0,1,2,3,4,5,6,7>
		LODSW
		MOV word ptr CS:B_KCHR_COMPOSE[line*2],AX
	ENDM

	RET

M_COMPOSE_PUTK MACRO
	; Point Charset
	SHLM       AX,5
	ADD        AX,2C00h
	CALL       L_COMPOSE
ENDM

M_COMPOSE_PUTE MACRO
	; Point Charset
	SHLM       AX,4
	ADD        AX,1000h
	CALL       L_COMPOSE_E
ENDM

M_COMPOSE_PUTF MACRO
	; Point Charset
	SUB        AX,20h
	SHLM       AX,5
	ADD        AX,2000h
	CALL       L_COMPOSE
ENDM

PUTKW MACRO idx,off
	MOV        AX, word ptr CS:B_KCHR_COMPOSE[idx]
	MOV        word ptr ES:[BX+off],AX
ENDM

PUTEW MACRO idx,off
	MOV        AL, byte ptr CS:B_KCHR_COMPOSE[idx]
	MOV        byte ptr ES:[BX+off],AL
ENDM

DrvFunc07PutK PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        ES,word ptr CS:W_GR_SEGMENT

	; Clear compose buffer
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		MOV WORD PTR CS:B_KCHR_COMPOSE[line*2],0h
	ENDM

	MOV        AX,word ptr [BP + 0eh]	; First
	M_COMPOSE_PUTK

	MOV        AX,word ptr [BP + 0ch]	; Mid
	M_COMPOSE_PUTK

	MOV        AX,word ptr [BP + 0ah]	; Last
	M_COMPOSE_PUTK

	; Calculate target screen position
	MOV        BX,word ptr [BP + 6h]			; Y
	SHLM       BX,4
	MOV        BX,word ptr CS:W_LineOffsets[BX]	; Lines[y*16]
	MOV        AX,word ptr [BP + 8h]
	;SHL        AX,1
	ADD        BX,AX							; X

	; Set Color Plane Mask
	VGA_WRITE_SEQ 2h, 7h

	; Transfer Bytes
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		PUTKW line*2, VGA_LINE_STRIDE*line
	ENDM

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       0Ah
DrvFunc07PutK ENDP

;----------------------------------------
;Gra_pute(pascal); int c
;----------------------------------------
DrvFunc26PutE PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        ES,word ptr CS:W_GR_SEGMENT

	; Clear compose buffer
	IRP line,<0,1,2,3,4,5,6,7>
		MOV WORD PTR CS:B_KCHR_COMPOSE[line*2],0h
	ENDM

	MOV        AX,word ptr [BP + 0ah]
	M_COMPOSE_PUTE

	; Calculate target screen position
	MOV        BX,word ptr [BP + 6h]			; Y
	SHLM       BX,4
	MOV        BX,word ptr CS:W_LineOffsets[BX]	; Lines[y*16]
	MOV        AX,word ptr [BP + 8h]
	;SHL        AX,1
	ADD        BX,AX							; X

	; Set Color Plane Mask
	VGA_WRITE_SEQ 2h, 7h

	; Transfer Bytes
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		PUTEW line, VGA_LINE_STRIDE*line
	ENDM

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       6h
DrvFunc26PutE ENDP

;----------------------------------------
;Gra_pute(pascal); int c
;----------------------------------------
DrvFunc27PutF PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        ES,word ptr CS:W_GR_SEGMENT

	; Clear compose buffer
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		MOV WORD PTR CS:B_KCHR_COMPOSE[line*2],0h
	ENDM

	MOV        AX,word ptr [BP + 0ah]
	M_COMPOSE_PUTF

	; Calculate target screen position
	MOV        BX,word ptr [BP + 6h]			; Y
	SHLM       BX,4
	MOV        BX,word ptr CS:W_LineOffsets[BX]	; Lines[y*16]
	MOV        AX,word ptr [BP + 8h]
	;SHL        AX,1
	ADD        BX,AX							; X

	; Set Color Plane Mask
	VGA_WRITE_SEQ 2h, 7h

	; Transfer Bytes
	IRP line,<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>
		PUTKW line*2, VGA_LINE_STRIDE*line
	ENDM

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       6h
DrvFunc27PutF ENDP

;----------------------------------------
;Gra_00 highlight cursor; int charY, int charX
;----------------------------------------
DrvFunc00 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES

	MOV        ES,word ptr CS:W_GR_SEGMENT
	
	VGA_WRITE_SEQ 2h, 0fh
	VGA_WRITE_GRAP 3h, 10h

	UOUTPORTB VGA_GRAP_ADDR, 8h
	MOV        DX,VGA_GRAP_DATA

	MOV        BX,word ptr [BP + 6h] ; param_1: Y
	SHLM       BX,4
	ADD        BX,8
	SHL        BX,1
	MOV        BX,word ptr CS:W_LineOffsets[BX]
	MOV        DI,word ptr [BP + 8h] ; param_2: X
	SHLM       DI,2
	ADD        DI,2
	ADD        DI,BX

	MOV        AL,0ffh
	OUT        DX,AL

	MOV        AH,AL ; AH = 0ffh
	REPT 4
		OR     byte ptr ES:[DI],AH
		OR     byte ptr ES:[DI + 1],AH
		OR     byte ptr ES:[DI + 2],AH
		OR     byte ptr ES:[DI + 3],AH
		ADD    DI,VGA_LINE_STRIDE
	ENDM
	MOV        AL,0f0h
	OUT        DX,AL

	PUSH       DI
	MOV        CX,12*2
L_122e:
	OR         byte ptr ES:[DI],0f0h
	ADD        DI,VGA_LINE_STRIDE
	LOOP       L_122e
	POP        DI

	ADD        DI,3

	MOV        AL,0fh
	OUT        DX,AL

	MOV        CX,12*2
L_123f:
	OR         byte ptr ES:[DI],0fh
	ADD        DI,VGA_LINE_STRIDE
	LOOP       L_123f

	SUB        DI,3

	MOV        AL,AH
	OUT        DX,AL
	
	REPT 4
		OR     byte ptr ES:[DI],AH
		OR     byte ptr ES:[DI + 1],AH
		OR     byte ptr ES:[DI + 2],AH
		OR     byte ptr ES:[DI + 3],AH
		ADD    DI,VGA_LINE_STRIDE
	ENDM

	VGA_WRITE_GRAP 3h, 0h
	VGA_WRITE_GRAP 8h, 0ffh

	POP        ES
	POP        DI
	POP        BP
	RETF
	db 0CBh
DrvFunc00 ENDP
_TEXT ENDS
END
