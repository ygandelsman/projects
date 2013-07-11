; file ex1.as – function
; externs:
 	.extern	1PRINTG
 .extern PRTSTR
 .extern VOID
 .entry	A
 	.extern COUNT
STRADD: .data 0
 STR: .string "abcdef"
 LASTCHAR: .data 0, 1, +3, -2
 LEN: .data 0
 K: .data 0

; count length of string, print the original string, reverse string, print reversed string.
 MAIN:	lea STR[%LEN], STRADD
 jsr COUNT
DO: jsr PRTSTR
A: mov STRADD, [K]LASTCHAR[r3]
r3: mov STR[%K], r7

DO:	 add COUNT[%LEN],r3
 
A: dec LASTCHAR[%K]
 inc PRINT
PRTSTR: mov r3,r6	 
 jsr PRINT
 jsr PRTSTR
stop

PRINT: .data 1,-0,3
