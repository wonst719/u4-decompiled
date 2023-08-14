.MODEL TINY
.DOSSEG
.DATA
	CODE_MEM_LENGTH EQU 2f0h

.CODE
.STARTUP
	JMP L_START ; 3 bytes

	db 256 dup(?)	; Stack

	TITLE_EXE db "title.exe",0
	AVATAR_EXE db "avatar.exe",0

	PARAM_ENV_SEG dw ?
	PARAM_CMD_TAIL dd ?
	PARAM_FIRST_FCB dd ?
	PARAM_SECOND_FCB dd ?

L_START:
	MOV        SP,offset TITLE_EXE ; Stack pointer

	; Tighten memory
	MOV        AH,4ah
	MOV        BX,CODE_MEM_LENGTH
	SHR        BX,1h
	SHR        BX,1h
	SHR        BX,1h
	SHR        BX,1h
	INC        BX				; BX: MEMORY_LENGTH / 16 + 1 (MCB + 1 PARA)
	INT        21h				; INT 21,4A (SETBLOCK)

	MOV        BX,80h
	MOV        CX,7eh
	SUB        CL,byte ptr [BX]
	ADD        BL,byte ptr [BX]
	LEA        DI,[BX + 2h]
	CLD
	MOV        AL,20h
	REP STOSB

L_LOOP:
	MOV        word ptr DS:[PARAM_ENV_SEG],0h
	MOV        word ptr DS:[PARAM_CMD_TAIL + 0],80h
	MOV        word ptr DS:[PARAM_CMD_TAIL + 2],DS
	MOV        word ptr DS:[PARAM_FIRST_FCB + 0],5ch
	MOV        word ptr DS:[PARAM_FIRST_FCB + 2],DS
	MOV        word ptr DS:[PARAM_SECOND_FCB + 0],6ch
	MOV        word ptr DS:[PARAM_SECOND_FCB + 2],DS

	; Execute TITLE.EXE
	MOV        AH,4bh
	MOV        AL,0h
	MOV        DX,offset TITLE_EXE		; Filename
	MOV        BX,offset PARAM_ENV_SEG	; Parameter block
	PUSH       CS
	POP        ES
	INT        21h						; INT 21,4B EXEC

	; Restore SS, SP (DOS 2.x bug)
	MOV        AX,CS
	MOV        SS,AX
	MOV        SP,offset TITLE_EXE
	MOV        DS,AX
	MOV        ES,AX

	; Get Exit Code
	MOV        AH,4dh
	INT        21h						; INT 21,4D GET EXIT CODE

	CMP AL, 0
	JZ @L1
	JMP L_EXIT

@L1:
	; NPARAM[80] PARAM0[82] PARAM1[84]
	; Set PARAM1
	MOV        DS:[84h],AL

	; PSP+80h: Count of characters in command tail
	MOV        byte ptr DS:[80h],4h

	MOV        word ptr DS:[PARAM_ENV_SEG],0h
	MOV        word ptr DS:[PARAM_CMD_TAIL + 0],80h
	MOV        word ptr DS:[PARAM_CMD_TAIL + 2],DS
	MOV        word ptr DS:[PARAM_FIRST_FCB + 0],5ch
	MOV        word ptr DS:[PARAM_FIRST_FCB + 2],DS
	MOV        word ptr DS:[PARAM_SECOND_FCB + 0],6ch
	MOV        word ptr DS:[PARAM_SECOND_FCB + 2],DS

	; Execute AVATAR.EXE
	MOV        AH,4bh
	MOV        AL,0h
	MOV        DX,offset AVATAR_EXE		; Filename
	MOV        BX,offset PARAM_ENV_SEG	; Parameter block
	PUSH       CS
	POP        ES
	INT        21h					; INT 21,4B EXEC

	JC         L_EXIT				; if (ERROR) goto EXIT

	; Restore SS, SP (DOS 2.x bug)
	MOV        AX,CS
	MOV        SS,AX
	MOV        SP,offset TITLE_EXE
	MOV        DS,AX
	MOV        ES,AX

	; Get Exit Code
	MOV        AH,4dh
	INT        21h					; INT 21,4D GET EXIT CODE

	CMP        AL,4h				; if (RET != 4) goto EXIT
	JNZ        L_EXIT

	JMP        L_LOOP

L_EXIT:
	INT        20h

END
