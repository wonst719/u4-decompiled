PUBLIC cdromAvailable
PUBLIC numberOfDriveLetters
PUBLIC startingDriveLetter

; small
DGROUP GROUP _DATA, _BSS

_DATA SEGMENT PUBLIC WORD 'DATA'
	ASSUME DS:DGROUP

_DATA ENDS

_BSS SEGMENT PUBLIC WORD 'BSS'

cdromAvailable db ?

numberOfDriveLetters dw ?
startingDriveLetter dw ?

_BSS ENDS

_TEXT SEGMENT PUBLIC BYTE 'CODE'
	ASSUME CS:_TEXT

PUBLIC _CdCheckMscdex
_CdCheckMscdex PROC NEAR
	PUSH BP
	MOV BP,SP

	; INT 2Fh, AX=1500h, BX=0000h
	; CD-ROM - INSTALLATION CHECK
	MOV AX, 1500h
	MOV BX, 0h

	INT 2Fh

	; BX = number of CD-ROM drive letters used
	; CX = starting drive letter (0=A:)
	MOV numberOfDriveLetters, BX
	MOV startingDriveLetter, CX

	; SETE requires 386
	CMP BX,0
	JNE CD_MSCDEX_OK

	MOV cdromAvailable, 0
	MOV AX, 0
	JMP CD_MSCDEX_EXIT

CD_MSCDEX_OK:
	MOV cdromAvailable, 1
	MOV AX, 1

CD_MSCDEX_EXIT:
	POP BP
	RET
_CdCheckMscdex ENDP

PUBLIC _CdSendDriverRequest
_CdSendDriverRequest PROC NEAR
	PUSH BP
	MOV BP,SP

	; INT 2Fh, AX=1510h - send device driver request
	MOV AX, 1510h

	; CX = CD-ROM drive letter
	MOV CX, startingDriveLetter

	; ES:BX: CD-ROM device driver request header
	MOV BX, word ptr [BP + 6] ; param_1_seg
	MOV ES, BX
	MOV BX, word ptr [BP + 4] ; param_1_off

	INT 2Fh

	;JC REQ_FAIL ; JUMP IF CARRY IS SET

;REQ_SUCCESS:

;REQ_FAIL:
	; AX: Error code

	POP BP
	RET
_CdSendDriverRequest ENDP

PUBLIC _CdGetTimeMinuteSecond
_CdGetTimeMinuteSecond PROC NEAR
	PUSH BP
	MOV BP, SP

	; INT 21,2C - get time
	; on return: DH = seconds (0-59)
	; CL = minutes (0-59)
	MOV AH, 2Ch
	INT 21h

	MOV BL, DH
	SUB BH, BH	; BX = DH

	MOV AL, CL
	SUB AH, AH	; AX = CL

	MOV CX, 60
	MUL CX		; AX *= 60

	ADD AX, BX	; AX += BX

	POP BP
	RET
_CdGetTimeMinuteSecond ENDP

_TEXT ENDS

END
