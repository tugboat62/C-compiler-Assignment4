.MODEL SMALL
.STACK 100h
.DATA
CR EQU 13
LF EQU 10
t0 DW  ?
t1 DW  ?
t2 DW DUP 3 
.CODE
;start of function main
main PROC
MOV AX, @DATA
MOV DS, AX
XOR BX, BX
XOR CX, CX
;variable t2 declared for local variable c
;assigning 1 * 2 + 3 % 3 to t0
;evaluating term 1 * 2 + 3 % 3
;evaluating term 1 * 2 + 3
MOV AX, 1
PUSH BX
MOV BX, AX
;evaluating simple expression 2 + 3
MOV AX, 2
PUSH BX
MOV BX, AX
MOV AX, 3
ADD AX, BX
POP BX
PUSH CX
MOV CX, AX
MOV AX, BX
MOV BX, CX
POP CX
MUL BX
POP BX
PUSH BX
MOV BX, AX
MOV AX, 3
PUSH CX
MOV CX, AX
MOV AX, BX
MOV BX, CX
POP CX
XOR DX, DX
CWD
IDIV BX
MOV AX, DX
POP BX
MOV t0, AX
;assigning 1 < 5 to t1
;evaluating relational expression
;evaluating relational expression with < operator
MOV AX, 1
PUSH BX
MOV BX, AX
MOV AX, 5
CMP BX, AX
JNL LABEL0
MOV AX, 1
JMP LABEL1
LABEL0:
MOV AX, 0
LABEL1:
POP BX
MOV t1, AX
;assigning 2 to [SI]
MOV AX, 0
MOV SI, offset t2
ADD AX, AX
ADD SI, AX
MOV AX, 2
MOV [SI], AX
;start of if else statement
;evaluating logic expression
;evaluating logic expression with && operator
MOV AX, t0
PUSH BX
MOV BX, AX
MOV AX, t1
CMP BX, 0
JE LABEL2
CMP AX, 0
JE LABEL2
MOV AX, 1
JMP LABEL3
LABEL2:
MOV AX, 0
LABEL3:
POP BX
CMP AX, 0
JE LABEL4
;incrementing the variable [SI]
MOV AX, [SI]
INC AX
MOV [SI], AX
JMP LABEL5
LABEL4:
;assigning [SI] to [SI]
MOV AX, 1
MOV SI, offset t2
ADD AX, AX
ADD SI, AX
MOV AX, 0
MOV SI, offset t2
ADD AX, AX
ADD SI, AX
MOV AX, [SI]
MOV [SI], AX
LABEL5:
;end of if else statement
;calling the function println
MOV AX, t0
PUSH AX
POP AX
CALL println
;calling the function println
MOV AX, t1
PUSH AX
POP AX
CALL println
MOV AH, 4CH
INT 21H
main ENDP
;println procedure implementation
println PROC
PUSH AX
PUSH BX
PUSH CX
PUSH DX
OR AX, AX
JGE @END_IF1
PUSH AX
MOV DL, '-'
MOV AH, 2
INT 21H
POP AX
NEG AX
@END_IF1:
XOR CX, CX
MOV BX, 10D
@REPEAT1:
XOR DX, DX
DIV BX
PUSH DX
INC CX
OR AX, AX
JNE @REPEAT1
MOV AH, 2
@PRINT_LOOP:
POP DX
OR DL, 30H
INT 21H
LOOP @PRINT_LOOP
MOV AH, 2
MOV DL, CR
INT 21H
MOV DL, LF
INT 21H
POP DX
POP CX
POP BX
POP AX
RET
println ENDP
END MAIN
