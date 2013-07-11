/* translate.c: checks and translates words from commands and instruction in the text to their target */
#include "translate.h"

/* command_check: checks if the command that begins from 'comm' is legal, return its number or WRONG otherwise */
int command_check(char* comm)
{
	char* next;
	char* commands[NUM_OF_COMMANDS] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};	
	int i;
	for(i = 0; i<NUM_OF_COMMANDS; ++i)
	{
		if( !strncmp( comm, commands[i], strlen( commands[i] ) ) )
		{
			next = comm + strlen(commands[i]);
			if( *next == ' ' || *next == '\t' || ( (i == stop || i == rts) && end_of_line(next) ) )
			{
				return i;
			}
		}
	}
	return WRONG;
}

/* ins_check: checks if the instruction that begins from 'ins' is legal, return its number or WRONG otherwise */
int ins_check(char* ins)
{
	char next;	
	char* instructions[NUM_OF_INSTRUCTIONS] = {".data",".string",".entry",".extern"};	
	int i;
	for(i = 0; i< NUM_OF_INSTRUCTIONS; ++i)
	{
		next = *(ins + strlen(instructions[i]));
		if( !strncmp(ins, instructions[i], strlen(instructions[i])) && (next == ' ' || next == '\t'))
		{
			return i;
		}
	}
	return WRONG;
}

/* number_check: returns RIGHT if the number that begins from 'operand' is legal, returns WRONG otherwise */
int number_check(char* operand)
{
	int i;	
	if(*operand == '+' || *operand == '-')
	{
		++operand;
	}
	for(i = 0; (!end_of_line(get_next_char(operand+i)) && *get_next_char(operand+i) !=',') ; ++i)
	{
		if(operand[i] < '0' || operand[i] > '9')
		{
			return WRONG;
		}
	}
	if(!i)
	{
		return WRONG;
	}
	return RIGHT;
}

/* data_check: returns the count of numbers if the numbers that begins from 's' are legal, returns WRONG otherwise */
int data_check(char* s)
{
	int leng = 0;	
	--s;	
	while(s)
	{
		s = get_next_char( s+INTERVAL );		
		++leng;			
		if(number_check(s) == WRONG)
		{
			return WRONG;		
		}
		s = strpbrk(s,",");
	}
	return leng;
}

/* string_check: returns the length of string that begins from 's', if it legal, returns WRONG otherwise */
int string_check(char* s)
{
	int leng = WRONG;				
	if(*s != '"')
	{
		return WRONG;
	}
	while(!end_of_line( s+INTERVAL ))
	{
		++leng;
		++s;
	}
	if(*s != '"')
	{
		return WRONG;
	}
	return leng;
}

/* get_string: returns copy of the string that starts from 's' */
char *get_string(char* s)
{
	char *str;
	str = (char *)malloc(sizeof(char)*string_check(s));
	++s;	
	copy(s,str,'"');
	return str;
}

/* get_numbers: returns array of the numbers that starts from 's' */
int *get_numbers(char* s)
{
	int *arr, j = 0;
	char *i = s;
	arr = (int *)malloc(sizeof(int)*data_check(s));
	arr[j] = atoi(i);
	i = strpbrk(i+INTERVAL,",");
	while(i != NULL && !end_of_line(get_next_char(i)))
	{
		j++;
		arr[j] = atoi(get_next_char(i+INTERVAL));	
		i = strpbrk(i+INTERVAL,",");				
	}
	return arr;	
}

/* register_check: checks if the register that begins from 'operand' is legal, return its number or WRONG otherwise */
int register_check(char* operand)
{
	int i;
	char* registers[NUM_OF_REGISTERS] = {"r0", "r1", "r2", "r3", "r4","r5" ,"r6" ,"r7"};	
	for(i = 0; i<NUM_OF_REGISTERS; ++i)
	{
		if( !strncmp(operand, registers[i], REG_LENGTH-INTERVAL) )
		{
			return i;
		}
	}
	return WRONG;
}

/* label_error: prints an error message - the label name is wrong */
void label_error(int lineNum)
{
	fprintf(stderr,"Error: Wrong label name in line %d.\n",lineNum);
}

/* redef_error: prints an error message - the label was already defined */
void redef_error(int lineNum)
{
	fprintf(stderr,"Error: Redefinition of the label in line %d.\n",lineNum);
}

/* label_check: checks if the label that starts from 'label' and ends by 'end' is correct and returns RIGHT, returns WRONG otherwise */
int label_check(char* label, char end, int lineNum)
{
	int length = 0;
	if(!label)
	{
		return WRONG;
	}
	if(WRONG != command_check(label) || WRONG != register_check(label))
	{		
		return WRONG;
	}
	if((*label > 'Z' || *label < 'A') && (*label > 'z' || *label < 'a'))
	{
		return WRONG;
	} 
	while(*get_next_char(label) != end)
	{
		if((*label > '9' || *label < '0') && (*label > 'Z' || *label < 'A') && (*label > 'z' || *label < 'a'))
		{	
			return WRONG;
		}
		++length; 
		++label;	
	}
	if(length > LABEL_LENGTH)
	{	
		return WRONG;
	}
	return RIGHT;
}

/* relative_check: returns RIGHT if the operand addressed with "last index relative" addressing, returns WRONG otherwise */
int relative_check(char* operand, int lineNum)
{
	if(label_check(operand, '[',lineNum) == WRONG)
	{
		return WRONG;	
	}
	operand = strpbrk(operand,"[");
	if(*(++operand) != '%')
	{
		return WRONG;
	}
	++operand;
	return label_check(operand, ']',lineNum);
}

/* two_dimension_check: returns RIGHT if the operand addressed with "two dimension index" addressing, returns WRONG otherwise */
int two_dimension_check(char* operand,int lineNum)
{
	if( *(operand++) != '[')
	{		
		return WRONG;
	}	
	if(label_check(operand, ']',lineNum) == WRONG)
	{
		return WRONG;	
	}
	operand = strpbrk(operand,"]");
	++operand;
	if(label_check(operand, '[',lineNum) == WRONG)
	{
		return WRONG;
	}
	operand = strpbrk(operand,"[");
	++operand;
	if(register_check(operand) == WRONG)
	{
		return WRONG;
	}
	operand += (REG_LENGTH-INTERVAL);
	if(*operand != ']')
	{
		return WRONG;
	}
	return RIGHT;
}

/* addressing_type: returns the addressing type of the operand, if there is no legal type, returns WRONG */
int addressing_type(char* operand, int lineNum)
{
	if(!operand)
	{
		return WRONG;	
	}	 	
	if(register_check(operand) != WRONG)
	{
		return reg;
	}
	if(*operand == '#' && number_check(operand+INTERVAL) != WRONG)
	{
		return imm;
	}
	if(label_check(operand, ',',lineNum) == RIGHT || label_check(operand, '\n',lineNum) == RIGHT || label_check(operand, '\0',lineNum) == RIGHT)
	{
		return dir;
	}
	if(relative_check(operand, lineNum) == RIGHT )
	{
		return rel;
	}
	if(two_dimension_check(operand,lineNum) == RIGHT )
	{
		return two;
	} 
	return WRONG;
}

/* number_of_parameters: return the number of parameters in this line to the command or to the instruction */
int number_of_parameters(char* line, int lineNum)
{
	int numberOfParams = 0, command; 
	if(read_first_variable(line)) 
	{ 
		++numberOfParams;	
		if(read_second_variable(line))
		{		
			++numberOfParams;	
		}	
	}
	if((command = command_check(read_command(line))) == WRONG)
	{		
		fprintf(stderr,"Error: Wrong command in line %d.\n",lineNum);
		return WRONG;
	} 	
	if(addressing_type(read_first_variable(line),lineNum) == WRONG && numberOfParams)
	{
		return error_parameter("first" ,lineNum);
	}	
	if(addressing_type(read_second_variable(line),lineNum) == WRONG && numberOfParams == 2)
	{
		return error_parameter("second" ,lineNum);
	}
	return numberOfParams;
}

/* error_parameter: prints that the first or second paramter is wrong and returns WRONG */
int error_parameter(char *num ,int lineNum)
{
	fprintf(stderr,"Error: Wrong %s parameter in line %d.\n",num,lineNum);
	return WRONG;
}

/* error_number_of_params: prints that the number of paramters is wrong and returns WRONG */
int error_number_of_params(int lineNum)
{
	fprintf(stderr,"Error: Wrong number of parameters in line %d.\n",lineNum);
	return WRONG;
}

/* error_addressing_of_params: prints that the addressing type of paramters is wrong and returns WRONG */
int error_addressing_of_params(int lineNum)
{
	fprintf(stderr,"Error: Wrong addressing type of parameters in line %d.\n",lineNum);
	return WRONG;
}

/* error_def_labels: prints that the label was already defined and returns WRONG */
int error_def_labels(int lineNum)
{
	fprintf(stderr,"Error: The label in line %d was already defined.\n",lineNum);
	return WRONG;
}

/* zero_params: returns RIGHT if the nubmer of parameters is right in case of zero parmeters, returns WRONG otherwise */
int zero_params( int command, int lineNum )
{
	if(command != stop && command != rts)				
	{
		return error_number_of_params(lineNum);				
	}			
	return RIGHT;
}

/* one_params: returns RIGHT if the nubmer of parameters is right in case of one parmeter, returns WRONG otherwise */
int one_param( int command, int param,int lineNum )
{
	switch (command)
	{
		case no: 
		{
			if(param < rel)
			{
				return error_addressing_of_params(lineNum);			
			}
			return RIGHT;		
		}
		case prn:
		{
			return RIGHT;
		}	
		case jsr: 
		{
			if(param != dir)
			{
				return error_addressing_of_params(lineNum);			
			}
			return RIGHT;		
		}		
		case clr: 
		case inc: 
		case dec: 
		case jmp: 
		case bne: 
		case red: 
		{
			if(param == imm)
			{
				return error_addressing_of_params(lineNum);			
			}
			return RIGHT;		
		}
		default: 
		{
			return error_number_of_params(lineNum);
		}		
	}	
}

/* two_params: returns RIGHT if the nubmer of parameters is right in case of two parmeters, returns WRONG otherwise */
int two_params( int command, int first, int second, int lineNum )
{
	switch (command)
	{
		case lea: 
		{
			if(second == imm && (first == imm || first == reg))
			{
				return error_addressing_of_params(lineNum);				
			}
			return RIGHT;		
		}
		case cmp:
		{
			return RIGHT;
		}		
		case mov: 
		case add: 
		case sub: 
		{
			if(second == imm)
			{
				return error_addressing_of_params(lineNum);			
			}
			return RIGHT;		
		}
		default: 
		{
			return error_number_of_params(lineNum);
		}		
	}	
}

/* check_right_addressing: returns RIGHT if there is right number of parameters, returns wrong otherwise */
int check_right_addressing(char* line, int lineNum)
{
	int numberOfParams, command, first, second;	
	if((numberOfParams = number_of_parameters(line,lineNum)) != WRONG)	
	{
		command = command_check(read_command(line)); 	
		first = addressing_type(read_first_variable(line), lineNum);	
		second = addressing_type(read_second_variable(line), lineNum);
		switch (numberOfParams)
		{
			case 0:
			{
				return zero_params(command, lineNum);			
			}
			case 1: 
			{
				return one_param(command,first, lineNum);
			}
			default: 
			{
				return two_params(command, first, second, lineNum); 
			}
		}	
	
	}
	return WRONG;
}

/* number_of_lines_comm: returns the number of lines that will be used in the .ob file for this command */
int number_of_lines_comm(char* line, int lineNum)
{
	int number, numberOfParams, first = WRONG, second = WRONG;	
	if((number = check_right_addressing(line,lineNum)) == RIGHT)
	{
		numberOfParams = number_of_parameters(line,lineNum);
		if(numberOfParams > 0)
		{
			first = addressing_type(read_first_variable(line),lineNum);			
		}
		if(numberOfParams > 1)
		{
			second = addressing_type(read_second_variable(line),lineNum);		
		}		
		if(first == rel || first == two)
		{
			number += 2;		
		}
		if(first == dir || first == imm)
		{
			++number;		
		}
		if(second == rel || second == two)
		{
			number += 2;		
		}
		if(second == dir || second == imm)
		{
			++number;		
		}
	}
	return number;
}

/* number_of_lines_ins: returns the number of lines that will be used in the .ob file for this instruction */
int number_of_lines_ins(char* line, int lineNum)
{
	int number = 0, type;
	char* first;		
	if((type = ins_check(read_command(line))) == ext || type == ent)
	{
		if(label_check(read_first_variable(line), '\n',lineNum) != WRONG)
		{
			return number;
		}
		return WRONG;
	}
	if(type == str)
	{
		if((first = read_first_variable(line)) == NULL || string_check(first) == WRONG)
		{			
			return ins_error(".string",lineNum);	
		}
		number += string_check(first)+1;
	}
	else if(type == dat)
	{
		if((first = read_first_variable(line)) == NULL || data_check(first) == WRONG)
		{
			return ins_error(".data",lineNum);	
		}
		number += data_check(first);	
	}
	return number;
}

/* ins_error: prints that there is wrong parameters for instruction of type 'to' and returns WRONG */
int ins_error(char* to ,int lineNum)
{
	fprintf(stderr, "Error: Wrong parameters to %s in line %d.\n", to, lineNum);
	return WRONG;
}

/* number_of_lines: returns the number of lines that will be used in the .ob file for this line */
int number_of_lines(char* line, int lineNum)
{
	if(ins_check(read_command(line)) == WRONG)
	{
		return number_of_lines_comm(line,lineNum);
	}
	return number_of_lines_ins(line,lineNum);
}

/* copy: copies the string 'from' ended by char end to string 'to' */
void copy(char* from, char* to, char end)
{
	while(*get_next_char(from) != end)
	{
		*to = *from;
		++to;
		++from;
	}
	*to = '\0';	
}

