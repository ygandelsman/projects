 file ex1.as – function
; externs:
F:	.extern	1:xPRINTG
 .extern PRTSTR
 .extern VOID
	.extern 	VOID 
	.entry	A
 	.extern COUNT
STRADD: .data 0,0,1, 1%
 STR: .string "abcdef"
 LASTCHAR: .data 0, 1, +3, -2
 LEN: .data 0
 K: .data 0

; count length of string, print the original string, reverse string, print reversed string.
 MAIN:	lea STR[%LEN], STRADD1
 jsr COUNT
 sub PRTSTR
 mov STRADD, [K]LASTCHAR[r3]

mov  	 #-1, #21
DO:	
 add COUNT[%LEN],r3
 
A: dec LASTCHAR[%K]
 inc r3
 mov r3,r6	 
 jsr PRINT
 jsr PRTSTR
stop

PRINT: .data 1,-0,3
