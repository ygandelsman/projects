; prints the multiplication table 3x3 if read 1 from the keyboard 

.extern Read

.extern Print

.extern Mul

	TABLE: .data -1,-1,-1,-1,-1,-1,-1,-1,-1
	LAST: .data +3
	STR: .string "multiplication table: "
	BASE: .data 0,1
	OFFSET: .data 1

MUL: 	jsr Read
	cmp r0, #1
	bne END
	lea TABLE, r2
	mov BASE[%OFFSET], r4
LOOP1:	mov BASE[%OFFSET], r3
LOOP2:	jmp Mul
	mov LAST,	[BASE]TABLE[r7] 
	inc r2
	cmp r0, TABLE
	bne LOOP2
	dec LAST
	cmp r0, #-3
	bne LOOP1
	mov STR, r1
	red TABLE
	add #1, TABLE	
	jmp Read
	rts
END: 	stop


; note: the code does'nt realy intended to work
