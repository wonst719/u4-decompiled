EXTRN u4_puts:NEAR
EXTRN u4_putc:NEAR
EXTRN Gra_putchar:NEAR
EXTRN t_callback:NEAR

EXTRN u_delay_c:NEAR
EXTRN u_kbhit_c:NEAR
EXTRN u_kbread_c:NEAR
;EXTRN u_kbflush_c:NEAR

EXTRN MSG_DSKERR:BYTE
EXTRN MSG_SYSERR:BYTE

EXTRN speed_info:WORD

EXTRN Party:BYTE

EXTRN txt_X:WORD
EXTRN txt_Y:WORD

PUBLIC cursor_rate


DGROUP	GROUP _DATA,_BSS
;########################################
_DATA	SEGMENT PUBLIC WORD 'DATA'
	ASSUME DS:DGROUP
;----------------------------------------
cursor_rate	dw 0	;D_0672
D_0674	dw 0
D_0676	dw 0FFFFh	;display cursor flag
;----------------------------------------
_DATA	ENDS
;########################################
_BSS	SEGMENT PUBLIC WORD 'BSS'
;----------------------------------------
;random seeds
PUBLIC seed_128
seed_128	db 10h dup(?)	;D_8732
;-- struct t_500 --
PUBLIC D_8742
D_8742	db 500h dup(?)
;--
D_8C42	db ?	;cursor state {0, 1, 2, 3}
D_8C43	dw ?	;cursor update counter
	db ?	;padding?
;----------------------------------------
_BSS	ENDS
;########################################
_TEXT	SEGMENT PUBLIC BYTE 'CODE'
	ASSUME CS:_TEXT

;----------------------------------------C_1771
PUBLIC u_rand_a
u_rand_a	PROC NEAR
	PUSHF
	PUSH	CX
	PUSH	DI
	PUSH	ES
	;--
	MOV	AX,DS
	MOV	ES,AX
	STD
	;--
	MOV	CX,0Eh
	MOV	DI,OFFSET DGROUP:seed_128 + 0Eh
	CLC
	MOV	AL,[DI+01]
C_1784:	ADC	AL,[DI]
	STOSB
	LOOP	C_1784
	ADC	[DI],AL
	;--
	MOV	CX,10h
	MOV	DI,OFFSET DGROUP:seed_128 + 10h
C_1791:	DEC	DI
	INC	BYTE PTR [DI]
	LOOPZ	C_1791
	;--
	POP	ES
	POP	DI
	POP	CX
	POPF
	;--
	MOV	AL,seed_128[0]
	MOV	AH,0
	TEST	AL,0FFh
	;--
	RET
u_rand_a	ENDP
;----------------------------------------C_17A2
PUBLIC u_rand_b
u_rand_b	PROC NEAR
	MOV	AL,seed_128[3]
	ADC	AL,seed_128[2]
	MOV	seed_128[2],AL
	XOR	seed_128[1],AL
	MOV	AL,seed_128[1]
	ADC	AL,seed_128[0]
	ROR	AL,1
	MOV	seed_128[0],AL
	MOV	seed_128[3],AL
	MOV	AH,0
	TEST	AX,0FFFFh
	RET
u_rand_b	ENDP

;[bp+04] wait delay in seconds
;[bp+06] allow interruption/prompt
PUBLIC _u_delay
_u_delay PROC NEAR
	PUSH	BP
	MOV	BP,SP
	PUSH	[BP+04] ; delay_sec
	PUSH	[BP+06] ; use_prompt
	CALL	u_delay_c
	POP	BP
	RET
_u_delay ENDP

;increments Party.f_000
;returns:
; 1 if key is pressed
; 0 if not
PUBLIC _u_kbhit
_u_kbhit PROC NEAR
	PUSH	BP
	MOV	BP,SP
	CALL	u_kbhit_c
	POP	BP
	RET
_u_kbhit ENDP

;get keyboard scancode
;wait if necessary
PUBLIC _u_kbread
_u_kbread PROC NEAR
	PUSH	BP
	MOV	BP,SP
	CALL	u_kbread_c
	POP	BP
	RET
_u_kbread ENDP

; NOTE: MSC4 int86() doesn't return ZF
; bp+04: key code
PUBLIC _u_kbcheck
_u_kbcheck PROC NEAR
	PUSH BP
	MOV BP,SP

	MOV	AH,1	; get keyboard status
	INT	16h
	JZ C_KBHIT_Z

	; keypress available
	MOV [BP+04],AX
	MOV AX,1
	JMP C_KBHIT_RET
 
C_KBHIT_Z:
 	; no keypress available
	MOV AX,0

C_KBHIT_RET:
	POP BP
	RET
_u_kbcheck ENDP

;----------------------------------------C_1804
;wait while key pressed
PUBLIC _u_kbflush
_u_kbflush	PROC NEAR
	;-- allow interrupts
	STI
	NOP
	NOP
	NOP
	CLI
	;--
	CALL	_u_kbhit
	JZ	C_1813
	CALL	_u_kbread
	JMP	_u_kbflush
C_1813:	;--
	RET
_u_kbflush	ENDP
;----------------------------------------
;get current default drive
PUBLIC C_1814
C_1814	PROC NEAR
	MOV	AH,19h	;get current default drive
	INT	21h
	INC	AL
	MOV	AH,0
	;--
	RET
C_1814	ENDP
;----------------------------------------
;select disk
PUBLIC C_181D
C_181D	PROC NEAR
	PUSH	BP
	MOV	BP,SP
	;--
	MOV	DL,[BP+04]
	DEC	DL
	MOV	AH,0Eh	;select disk
	INT	21h
	MOV	AH,0
	;--
	POP	BP
	RET	2
C_181D	ENDP
;----------------------------------------
;test file
PUBLIC C_182F
C_182F	PROC NEAR
	PUSH	BP
	MOV	BP,SP
	;--
	MOV	DX,[BP+04]
	MOV	AL,0
	MOV	AH,3Dh	;open file
	INT	21h
	JNB	C_1842
	;--
	MOV	AX,0
	JMP	SHORT C_184B
C_1842:	;--
	MOV	BX,AX
	MOV	AH,3Eh	;close file
	INT	21h
	;--
	MOV	AX,1
C_184B:	;--
	POP	BP
	RET	2
C_182F	ENDP
;----------------------------------------
;piracy check function ?
;succes => 0
;failure => -1
PUBLIC C_184F
C_184F	PROC NEAR
	PUSHF
	PUSH	BX
	PUSH	AX
	PUSH	CX
	PUSH	DX
	PUSH	DS
	PUSH	ES
	;--
	PUSH	BP
	MOV	BP,SP
	PUSH	DI
	PUSH	SI
	;-- set drive
	MOV	AH,19h	;get current default drive
	INT	21h
	CMP	AL,1
	JBE	C_1865
	MOV	AL,0
C_1865:	MOV	DL,AL	;drive
	;--
	MOV	SI,4	;4 tries
	MOV	CL,10h	;from sector 10h
nextSector:	;-- read one sector to c000:0000
	MOV	AX,(2 SHL 8) OR 1	;read 1 sector
	MOV	DH,0	;head 0
	MOV	CH,9	;track 9
	MOV	BX,0C000h
	MOV	ES,BX
	XOR	BX,BX	;to c000:0000
	INT	13h
	JB	C_1887
	;-- one track success
	DEC	CL
	JZ	C_1890	;finished
	MOV	SI,4	;4 tries
	JMP	nextSector
C_1887:	;-- failed this sector
	DEC	SI
	JNZ	nextSector
	;-- failure
	MOV	BX,0FFFFh
	JMP	C_1893	;(+nop)
C_1890:	;-- success
	MOV	BX,0
C_1893:	;--
	POP	SI
	POP	DI
	MOV	SP,BP
	POP	BP
	;--
	POP	ES
	POP	DS
	POP	DX
	POP	CX
	POP	AX
	MOV	AL,BL
	POP	BX
	POPF
	RET
C_184F	ENDP
;----------------------------------------
;set critical error handler
PUBLIC C_18A2
C_18A2	PROC NEAR
	PUSH	DS
	;--
	LEA	DX,INT_18B3
	MOV	AX,CS
	MOV	DS,AX
	MOV	AH,25h	;set new interrupt vector
	MOV	AL,24h	;Critical Error
	INT	21h
	;--
	POP	DS
	RET
C_18A2	ENDP
;----
INT_18B3:
	PUSH	BP
	MOV	BP,SP
	PUSH	BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DS
	PUSH	ES
	;--
	MOV	BX,SS
	MOV	DS,BX
	MOV	ES,BX
	TEST	AH,80h
	JNZ	C_190C
	;-- display disk error --
	PUSH	txt_Y
	PUSH	txt_X
	MOV	txt_Y,24	;18h
	MOV	txt_X,0
	;--
	LEA	AX,MSG_DSKERR
	PUSH	AX
	CALL	u4_puts
	;--
	MOV	AH,0	;wait for keypress and read character
	INT	16h
	;--
	MOV	txt_X,0
	MOV	SI,39	;27h
C_18F0:	;--
	MOV	AX,' '
	PUSH	AX
	CALL	u4_putc
	;--
	DEC	SI
	JNZ	C_18F0
	;--
	POP	txt_X
	POP	txt_Y
	;-- --
	POP	ES
	POP	DS
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	BP
	MOV	AL,1
	IRET
C_190C:	;-- display fatal error
	LEA	AX,MSG_SYSERR
	PUSH	AX
	CALL	u4_puts
	;-- --
	POP	ES
	POP	DS
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	BP
	MOV	AL,2
	IRET
;----------------------------------------
_TEXT	ENDS
;########################################
END
