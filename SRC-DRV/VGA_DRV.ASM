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
	dw OFFSET _TEXT:DrvFunc19	;called throuch Gra_19 clear food/gold zone
	dw OFFSET _TEXT:DrvFunc20AnimSpit	;called through Gra_animSpit; unsigned tile
	dw OFFSET _TEXT:DrvFunc21Init	;called through Gra_init; void **ppshape, void **ppchar void(*pExit)(int)
	dw OFFSET _TEXT:DrvFunc22ClrScr	;called through Gra_clrscr
	dw OFFSET _TEXT:DrvFunc23AnimFlow	;called through Gra_animFlow
	dw OFFSET _TEXT:DrvFunc24AnimFlag	;called through Gra_animFlag
	dw OFFSET _TEXT:DrvFunc25PutChar	;called through Gra_putchar; char c
W_GR_SEGMENT	dw 0A000h
B_0036	db 12h
B_0037	db 34h
B_0038	db 56h
B_0039	db 78h
	db 0D5h
	db 0AAh
	db 0C3h
	db 3Ch
	db 1h,2h,4h,8h,10h,20h,40h,80h
W_pShapes_0	dw 0h
W_pShapes_1	dw 0h
W_pCharset_0	dw 0h
W_pCharset_1	dw 0h
W_pExit_0	dw 0h
W_0050	dw 0h
U_0052	dw 0000h	; Address for each screen line
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h
U_0062	dw 0000h
U_0064	dw 0000h
U_0066	dw 0000h
U_0068	dw 0000h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
U_0082	dw 0000h
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
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h
U_0112	dw 0000h
U_0114	dw 0000h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h
U_0122	dw 0000h
U_0124	dw 0000h
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
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h
U_01ba	dw 0000h
U_01bc	dw 0000h
U_01be	dw 0000h
U_01c0	dw 0000h
U_01c2	dw 0000h
U_01c4	dw 0000h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h,00h,00h,00h,00h
	db 00h,00h,00h,00h
	db 00h,01h,02h,03h,04h,05h,06h,07h
	db 38h,39h,3Ah,3Bh,3Ch,3Dh,3Eh,3Fh
	db 00h,00h,02h,01h,07h
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

B_KCHR_COMPOSE	db 0aah,55h,0aah,55h,0aah,55h,0aah,55h

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

;----------------------------------------
;Gra_01(cdecl)
;----------------------------------------
DrvFunc01 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,6h
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF
	; Func
	; Func
DrvFunc01 ENDP
;----------------------------------------
;Gra_02(cdecl)
;----------------------------------------
DrvFunc02 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF
	; Func
	; Func
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

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       2h
	; Func
	; Func
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

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       2h
	; Func
	; Func
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

	UOUTPORTB  3ceh, 5h
	UOUTPORTB  3cfh, 1h

	MOV        DS,word ptr CS:[W_GR_SEGMENT]
	PUSH       DS
	POP        ES

	UOUTPORTB  3c4h, 2h
	UOUTPORTB  3c5h, 0fh

	MOV        AH,58h
	MOV        BX,112h
	MOV        DX,18h
L_05fe:
	MOV        DI,word ptr CS:[BX]
	ADD        DI,DX
	MOV        SI,word ptr CS:[BX + 10h]
	ADD        SI,DX
	ADD        BX,2h
	MOV        CX,10h
	REP MOVSB
	DEC        AH
	JNZ        L_05fe

	UOUTPORTB  3ceh, 5h
	UOUTPORTB  3cfh, 0h

	UOUTPORTB  3c5h, 0fh

	MOV        AX,0h
	MOV        BX,1c2h
	MOV        DX,8h

L_0630:
	MOV        DI,word ptr CS:[BX]
	ADD        DI,18h
	ADD        BX,2h
	MOV        CX,8h
	REP STOSW
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

	POP        ES
	POP        DI
	RETF
	; Func
	; Func
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

	POP        ES
	POP        DI
	POP        BP
	RETF       2h
	; Func
	; Func
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

	POP        ES
	POP        BP
	RETF
	; Func
	; Func
DrvFunc14DotOR ENDP
;----------------------------------------
;Gra_dot_XOR(cdecl)
;----------------------------------------
DrvFunc15DotXOR PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	POP        ES
	POP        BP
	RETF
	; Func
	; Func
DrvFunc15DotXOR ENDP
;----------------------------------------
;Gra_dot(cdecl)
;----------------------------------------
DrvFunc06Dot PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES

	POP        ES
	POP        DI
	POP        BP
	RETF
DrvFunc06Dot ENDP
;----------------------------------------
;Gra_16(cdecl)
;----------------------------------------
;(PCPaint format)
DrvFunc16 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,0eh
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

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
DrvFunc18 PROC FAR
	PUSH       BP
	MOV        BP,SP
	SUB        SP,10h
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	MOV        SP,BP
	POP        BP
	RETF
DrvFunc18 ENDP

;----------------------------------------
;Gra_19(pascal)
;----------------------------------------
DrvFunc19 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       ES

	POP        ES
	POP        SI
	POP        BP
	RETF       2h
DrvFunc19 ENDP

;----------------------------------------
;Gra_animSpit
;----------------------------------------
DrvFunc20AnimSpit PROC FAR
	PUSH       DS

	POP        DS
	RETF
DrvFunc20AnimSpit ENDP

VGA_SEQ_ADDR EQU 3c4h
VGA_SEQ_DATA EQU 3c5h

VGA_CRTC_ADDR EQU 3d4h
VGA_CRTC_DATA EQU 3d5h

VGA_GRAP_ADDR EQU 3ceh
VGA_GRAP_DATA EQU 3cfh

; Uses DX, AX
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

;----------------------------------------
;Gra_init(cdecl)
;----------------------------------------
DrvFunc21Init PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       ES

	MOV        AH,0h	; Set video mode
	MOV        AL,13h	; mode 13h
	INT        10h

	; Set 320x200 Planar Mode
	VGA_WRITE_SEQ 4h, 6h		; disable chain-4
	VGA_WRITE_CRTC 14h, 0h		; disable double word mode
	VGA_WRITE_CRTC 17h, 0e3h	; enable byte mode

	; Set 320x400 Planar Mode
	;VGA_WRITE_CRTC 9h, 40h		; 400 lines

	PUSH       CS
	POP        ES

	;MOV        DX,1e2h
	;MOV        AH,10h	; Set EGA palette registers
	;MOV        AL,2h
	;INT        10h

	; Seq Addr: Select Color Plane
	; Seq Data: RGBI
	;VGA_WRITE_SEQ, 2h, 0fh

	; Grap Addr: Plane Mask
	; Grap Data: FFh
	;VGA_WRITE_GRAP 8h, 0ffh

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
	MOV        CX,200
	LEA        BX,CS:[U_0052]
L_0e97:
	MOV        word ptr CS:[BX],AX
	ADD        BX,2
	ADD        AX,40
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

	POP        ES
	POP        DI
	RETF
DrvFunc22ClrScr ENDP

;----------------------------------------
;random
;----------------------------------------
random PROC NEAR
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
random ENDP

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

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POPF
	POP        BP
	RETF       2h
	; Func
	; Func
DrvFunc23AnimFlow ENDP

;----------------------------------------
;Gra_animFlag
;----------------------------------------
DrvFunc24AnimFlag PROC FAR
	PUSH       ES

	POP        ES
	RETF
	; Func
	; Func
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
	SHL        AX,1h
	SHL        AX,1h
	SHL        AX,1h
	SHL        AX,1h
	SHL        AX,1h
	LDS        SI,dword ptr CS:[W_pCharset_0]
	ADD        SI,AX
	MOV        BX,word ptr [BP + 6h]
	SHL        BX,1h
	SHL        BX,1h
	SHL        BX,1h
	SHL        BX,1h
	MOV        BX,word ptr CS:[BX + U_0052]
	ADD        BX,word ptr [BP + 8h]
	MOV        DX,3c4h
	MOV        AL,2h
	OUT        DX,AL
	MOV        DX,3c5h
	MOV        CL,8h	; IO VALUE = 8
L_118c:
	MOV        AL,CL
	OUT        DX,AL						; IO <- AL: Select Color Plane
	LODSB									; AL <- [DS:SI], SI++
	MOV        byte ptr ES:[BX],AL			; SEG+BX
	LODSB
	MOV        byte ptr ES:[BX + 28h],AL	; SEG+BX+40
	LODSB
	MOV        byte ptr ES:[BX + 50h],AL	; SEG+BX+80
	LODSB
	MOV        byte ptr ES:[BX + 78h],AL	; SEG+BX+120
	LODSB
	MOV        byte ptr ES:[BX + 0a0h],AL	; SEG+BX+160
	LODSB
	MOV        byte ptr ES:[BX + 0c8h],AL	; SEG+BX+200
	LODSB
	MOV        byte ptr ES:[BX + 0f0h],AL	; SEG+BX+240
	LODSB
	MOV        byte ptr ES:[BX + 118h],AL	; SEG+BX+280
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
	; Point Charset
	SHL        AX,1h
	SHL        AX,1h
	SHL        AX,1h
	ADD        AX,1400h

	LDS        SI,dword ptr CS:[W_pCharset_0]
	ADD        SI,AX

	; Load into compose buffer
	LODSB
	OR         CS:B_KCHR_COMPOSE[0],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[1],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[2],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[3],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[4],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[5],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[6],AL
	LODSB
	OR         CS:B_KCHR_COMPOSE[7],AL

	RET

DrvFunc07PutK PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       SI
	PUSH       DI
	PUSH       DS
	PUSH       ES
	MOV        ES,word ptr CS:[W_GR_SEGMENT]

	; Clear compose buffer
	MOV        WORD PTR CS:B_KCHR_COMPOSE[0],0h
	MOV        WORD PTR CS:B_KCHR_COMPOSE[2],0h
	MOV        WORD PTR CS:B_KCHR_COMPOSE[4],0h
	MOV        WORD PTR CS:B_KCHR_COMPOSE[6],0h

	MOV        AX,word ptr [BP + 0eh]	; First
	CALL       L_COMPOSE

	MOV        AX,word ptr [BP + 0ch]	; Mid
	CALL       L_COMPOSE

	MOV        AX,word ptr [BP + 0ah]	; Last
	CALL       L_COMPOSE

	; Calculate target screen position
	MOV        BX,word ptr [BP + 6h]			; Y
	SHL        BX,1h
	SHL        BX,1h
	SHL        BX,1h
	SHL        BX,1h
	MOV        BX,word ptr CS:[BX + U_0052]		; Lines[y*16]
	ADD        BX,word ptr [BP + 8h]			; X

	; Sequence Address Register
	MOV        DX,3c4h
	MOV        AL,2h						; Select Color Plane
	OUT        DX,AL

	; Sequence Data Register
	MOV        DX,3c5h
	MOV        AL,7h						; Color Plane Mask: RGB
	OUT        DX,AL						; IO <- AL: Set Color Plane Mask

	; Transfer Bytes
	MOV        AL,CS:B_KCHR_COMPOSE[0]
	MOV        byte ptr ES:[BX],AL			; SEG+BX
	MOV        AL,CS:B_KCHR_COMPOSE[1]
	MOV        byte ptr ES:[BX + 28h],AL	; SEG+BX+40
	MOV        AL,CS:B_KCHR_COMPOSE[2]
	MOV        byte ptr ES:[BX + 50h],AL	; SEG+BX+80
	MOV        AL,CS:B_KCHR_COMPOSE[3]
	MOV        byte ptr ES:[BX + 78h],AL	; SEG+BX+120
	MOV        AL,CS:B_KCHR_COMPOSE[4]
	MOV        byte ptr ES:[BX + 0a0h],AL	; SEG+BX+160
	MOV        AL,CS:B_KCHR_COMPOSE[5]
	MOV        byte ptr ES:[BX + 0c8h],AL	; SEG+BX+200
	MOV        AL,CS:B_KCHR_COMPOSE[6]
	MOV        byte ptr ES:[BX + 0f0h],AL	; SEG+BX+240
	MOV        AL,CS:B_KCHR_COMPOSE[7]
	MOV        byte ptr ES:[BX + 118h],AL	; SEG+BX+280

	POP        ES
	POP        DS
	POP        DI
	POP        SI
	POP        BP
	RETF       6h
DrvFunc07PutK ENDP

;----------------------------------------
;Gra_00 highlight cursor; int charY, int charX
;----------------------------------------
DrvFunc00 PROC FAR
	PUSH       BP
	MOV        BP,SP
	PUSH       DI
	PUSH       ES

	POP        ES
	POP        DI
	POP        BP
	RETF
	db 0CBh
DrvFunc00 ENDP
_TEXT ENDS
END
