main: assembler.c transition.h read.h list.h translate.h print.h transition.c read.c list.c translate.c print.c
	gcc -Wall -g -ansi -pedantic -c read.c 
	gcc -Wall -g -ansi -pedantic -c list.c 
	gcc -Wall -g -ansi -pedantic -c print.c 
	gcc -Wall -g -ansi -pedantic -c translate.c
	gcc -Wall -g -ansi -pedantic -c transition.c
	gcc -Wall -g -ansi -pedantic -c assembler.c
	gcc -Wall -g -ansi -pedantic -o assembler assembler.o transition.o read.o translate.o print.o list.o
	rm transition.o read.o translate.o print.o list.o assembler.o

#cleanup
clean:
	rm *~

