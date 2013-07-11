/*
	MM"N 14
     	-------------
     	Y. Gandelsman
     	-------------
*/
#include "transition.h"

/* assembler: assemble the arguments file names to .ob files, .ext files, and .ent files */
int main(int argc, char *argv[])
{	
	int i;				
	if(argc < 2)
	{
		fprintf(stderr,"Error: Wrong number of arguments for the assembler.\n");
	}
	else
	{
		for(i = 1; i < argc; ++i)
		{
			first_transition(argv[i]);		
		}
	}	
	return 0;
}
