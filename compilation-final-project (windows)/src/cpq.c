#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUF_LEN 4

extern FILE* yyin;
extern FILE* yyout;
extern int yyparse();
extern int error_exist;

FILE* qud_file;
FILE* err_file;

void copy_errors()
{
	char c;	
	fseek( err_file , 0 , SEEK_SET );
	fputc('\n',yyout);
	while((c = fgetc(err_file)) != EOF)
	{
		fputc(c,yyout);
	}
}

FILE *open_file(char *name, char *type)
{
	FILE* f = NULL;
	f = fopen(name, type);	
	if(f == NULL)
	{
		fprintf(stderr, "error: could'nt open file \"%s\"\n", name);
	}
	return f;
}

int main(int argc, char* argv[])
{
	char* name, *suffix = NULL; 
    if(argc != 2)
    {
        fprintf(stderr, "error: missing arguments \n");	
		return 1;
    }
	name = argv[1];
	suffix = argv[1]+strlen(argv[1])-SUF_LEN;
	if (!strcmp(suffix, ".cpl") || !strcmp(suffix, ".CPL"))
	{
		if(!(yyin = open_file(argv[1], "r")))
			return 1;
		strcpy(suffix,".lst");
		
		if(!(yyout = open_file(name, "w")))
			return 1;
		fprintf(yyout,"1:\t");		
		
		strcpy(suffix,".qud");
		
		if(!(qud_file = open_file(name, "w")))
			return 1;
			
		if(!(err_file = tmpfile()))
		{
			fprintf(stderr, "error: could'nt open temporary file\n");
			return 1;
		}
		if(yyparse() || error_exist)
		{
			copy_errors();
			fclose(qud_file);
			remove(name);
			fprintf(stderr, "error: parsing error, see more information in .lst file\n");
		}
		fclose(qud_file);
		fclose(yyin);
		fclose(yyout);
		
		return 0;
	}
	fprintf(stderr, "error: suffix error, shuld be \".cpl\"\n");
    return 1;
}
