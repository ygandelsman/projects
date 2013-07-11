CPQ - A cpl to quad compiler
============================


compile cpq:
------------
to compile this project with cl compiler, run the next lines in ./src:

>	cl cpq.c cpq.tab.c lex.yy.c names.c instructions.c
>	del *.obj


files in this directory:
------------------------
cpq.exe:	the compiler
src:		the source files to this compiler
cpq.doc:	an explanation about the compiler
io examples:	input and output examples of the compiler
ex16.pdf:	the description of the project
