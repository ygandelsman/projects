/* print.c: contains functions of printing information to the file */
#include "print.h"

/* open_file: opens and returns file with the name 'name' and ending 'end', if can't open returns NULL */
FILE *open_file(char* name,char* end, char* type)
{
	FILE *f = NULL;
	char* fileName = create_char_name(name, end);	
	if(fileName)
	{	
		f = fopen(fileName, type);
	}	
	if( !f )
	{
		fprintf(stdout,"Error: during openning file %s\n", fileName);
	}
	free(fileName);	
	return f;	
}

/* get_string_instruction: gets the information of instruction and returs a binary string of it */
char* get_string_instruction(int command, int first_address, int second_address, int first, int second)
{
	char *ins;
	int i, mask = 1; 
	ins = (char *)malloc(INSTRUCTION_LENGTH);		
	for(i = 0; i < REG_LENGTH; ++i)
	{
		ins[INSTRUCTION_LENGTH-i-BACK_RETURN] = PUT_BIT(second);
		mask <<= 1;	
	}
	mask = 1;
	for(i = 0; i < ADD_LENGTH; ++i)
	{
		ins[INSTRUCTION_LENGTH-REG_LENGTH-i-BACK_RETURN] = PUT_BIT(second_address);
		mask <<= 1;	
	} 
	mask = 1;
	for(i = 0; i < REG_LENGTH; ++i)
	{
		ins[INSTRUCTION_LENGTH-REG_LENGTH-ADD_LENGTH-i-BACK_RETURN] = PUT_BIT(first);
		mask <<= 1;	
	}
	mask = 1;
	for(i = 0; i < ADD_LENGTH; ++i)
	{
		ins[INSTRUCTION_LENGTH-2*REG_LENGTH-ADD_LENGTH-i-BACK_RETURN] = PUT_BIT(first_address);
		mask <<= 1;	
	}
	mask = 1;
	for(i = 0; i < COMM_LENGTH; ++i)
	{
		ins[INSTRUCTION_LENGTH-2*(REG_LENGTH+ADD_LENGTH)-i-BACK_RETURN] = PUT_BIT(command);
		mask <<= 1;	
	}
	ins[INSTRUCTION_LENGTH-1] = '\0';
	return ins;
}

/* get_string_number: gets a number and a length and returns the binary number converted to sring with this length */
char* get_string_number(int num, int str_leng)
{
	char *number;
	int i, mask = 1; 
	number = (char *)malloc(str_leng);
	for(i = 0; i < str_leng-1; ++i)
	{
		number[str_leng-i-BACK_RETURN] = PUT_BIT(num);
		mask <<= 1;	
	}
	number[str_leng-1] = '\0';
	return number;
	 
}

/* print_lines: prints to file the next leng lines from the arrays, that starts from the base address */
void print_lines(int leng, int baseAddress, char **commandsArr, char *charArr, FILE *to)
{	
	int i;
	char *counter;
	for(i = 0; i< leng; ++i)
	{
		counter = get_string_number(i+baseAddress,I_COUNTER_LENGTH);
		fprintf(to,"%s\t%s\t%c\n", counter, commandsArr[i], charArr[i]);
	}
}

/* close_file: closes the file and deletes it if the file is empty or there is a WRONG status */
void close_file(int status, FILE *f, char *name)
{	
	int first;
	FILE *readF = NULL;
	fclose(f);
	readF = fopen(name,"r");
	first = fgetc(readF);
	fclose(readF);	
	if(first == EOF || status == WRONG)
	{
		remove(name);	
	}
	free(name);
}

/* print_data: prints the data from the data list to the file */
void print_data(FILE *f,int baseAddress,data_list *d)
{
	data_list *temp = d;	
	while(d)
	{
		fprintf(f,"%s\t%s\n",get_string_number(baseAddress, I_COUNTER_LENGTH),get_string_number(d->data,INSTRUCTION_LENGTH));
		d = d->next;		
		++baseAddress;
	}
	close_data_list(temp);
}

/* print_entries: prints the entries data  from the list to the .ent file */
int print_entries(FILE *f, label_list *labels, name_list *entr, int lastIc)
{
	label_list *entrNode = NULL;
	name_list *tmp;	
	int offset, status = RIGHT;
	while(entr)
	{
		entrNode = get_label_node(labels, entr->name, '\0');
		if(!entrNode)
		{
			fprintf(stdout,"Error: Undefined entry label '%s'.\n", entr->name);
			status = WRONG;
		}
		else
		{	
			offset = (entrNode->type == codeT)?0:lastIc;
			fprintf(f,"%s\t%s\n",entrNode->label, get_string_number(entrNode->address+offset+BASE,I_COUNTER_LENGTH));
		}
		entr = entr->next;
	}
	return status;
	close_name_list(tmp);
}

