/* transition.c: makes transitions on the file and prints the results */
#include "transition.h"

/* insert_name_to_list: gets the label from the line and inserts it if undefined in other place */
name_list* insert_name_to_list(name_list* list, char* line, int lineNum, label_list* labels, int ins)
{

	char *label = NULL;
	int labelCheck;
	if((label = read_first_variable(line)) && !get_name_node(list, label, '\n') && (labelCheck = label_check(label,'\n',lineNum)) == RIGHT)
	{	
		if((ins == ext && !get_label_node(labels,label, '\n')) || ins == ent)
		{
			list = insert_name(list,label);		
			return list;		
		}
	}
	if(label)
	{
		redef_error(lineNum);
	}
	return list;				
}

/* insert_data_to_list: gets the data from the line and inserts numbers or string to the data list */
data_list* insert_data_to_list(data_list* data, char* line, int ins)
{	
	if(ins == str)
	{	
		return string_insert(data, get_string(read_first_variable(line)));
	}
	return numbers_insert(data, get_numbers(read_first_variable(line)), data_check(read_first_variable(line)));
}

/* insert_label_not_extern: checks if label undefined in the externs list and insert it to the label list */
label_list* insert_label_not_extern(label_list* labels, char* label, int address, int type, name_list* externs, int lineNum)
{	
	if(!get_name_node(externs,label,':') && !get_label_node(labels,label,':'))
	{
		return insert_label(labels, label, address, type);
	} 
	redef_error(lineNum);
	return labels;
}

/* first_transition: makes the first transition on the file with that name according to the algorithm in page 28 */
void first_transition(char *name)
{	
	int ic = 0, dc = 0, boolLabel = WRONG, leng = 0, status = RIGHT, ins, lineNum = 0;
	char line[MAX_LINE_LENGTH];
	label_list *labels = NULL, *tmpLab = NULL;	
	name_list *externs = NULL, *entries = NULL, *tmp;
	data_list *data = NULL, *commandsL = NULL;
	FILE *current = open_file(name,".as","r");	
	fprintf(stderr,"file %s:\n",name);
	while((lineNum = read_next_line(current,line,lineNum)))/* while there is a new line in the file */
	{					
		ins = ins_check(read_command(line));		
		if((leng = number_of_lines(line,lineNum)) != WRONG)/* the command or instruction is legal */
		{		
			boolLabel = (label_check(read_label(line),':',lineNum) == RIGHT)? RIGHT:WRONG; /* checks if there is a label */
			if(ins == dat || ins == str)
			{
				if(boolLabel == RIGHT)
				{
					if((tmpLab = insert_label_not_extern(labels, read_label(line), dc, dataT,externs, lineNum)) != labels) /* not inserted already */
					{
						labels = tmpLab;
					}
					else
					{
						status = WRONG;
					}
				}					
				data = insert_data_to_list(data, line, ins);
				dc += leng;			
			}
			if(ins == ext)	
			{
				if((tmp = insert_name_to_list(externs, line, lineNum,labels,ins)) != externs) /* not inserted already */
				{					
					externs = tmp;	
				}
				else 
				{
					status = WRONG;		
				}
				boolLabel = WRONG;					
			}
			if(ins == ent)
			{
				if((tmp = insert_name_to_list(entries, line, lineNum, labels ,ins)) != entries) /* not inserted already */					
				{
					entries = tmp;	
				}
				else 
				{
					status = WRONG;			
				}
				boolLabel = WRONG;					
			}
			if(boolLabel == RIGHT && ins != str && ins != dat)
			{
				if((tmpLab = insert_label_not_extern(labels, read_label(line), ic, codeT, externs, lineNum)) != labels) /* not inserted already */
				{				
					labels = tmpLab;	
				}
				else
				{
					status = WRONG;
				}		
			}
			if(ins == WRONG)
			{			
				ic += leng;			
				commandsL = insert_data(commandsL,leng); /* inserts the length to the commands list */			
			}		
		}
		else
		{
			status = WRONG;
			if(ins == WRONG) /* inserts the length of this command to the commands list */
			{
				commandsL = insert_data(commandsL,leng);
			}
			if( label_check(read_first_variable(line),'\n',lineNum) == WRONG && (ins == ext || ins == ent) ) /* wrong label name in extern. or entry. instruction */
			{
				label_error(lineNum);
			}
		}
	}
	if(current) /* file is opened */
	{
		second_transition(name,ic,dc,current,status,externs,entries,commandsL,data,labels);
	}	
	else
	{
		close_lists( labels, entries, data );
		close_lists( NULL, externs, commandsL);
	}	
}

/*get_label_address: checks where the label is and returns it if it in just one of the options. if it in externs print it to externs file */
int get_label_address(int lastIc,char *label, char last, name_list *externs, label_list *labels, int place, FILE *extFile, int lineNum)
{	
	name_list* na;
	label_list* la;
	na = get_name_node(externs, label, last);
	la = get_label_node(labels, label, last);	
	if(la && na)
	{
		fprintf(stderr,"Error: Use of extern label '%s' in line %d is forbidden, illegal definition of extern label.\n", la->label,lineNum);		
		return WRONG;
	}
	if(na)
	{		
		fprintf(extFile,"%s\t%s\n",na->name, get_string_number(place,I_COUNTER_LENGTH));
		return UNKNOWN;	
	}
	if(la)
	{
		if(la->type == codeT)
		{
			return BASE + la->address;	
		}
		else
		{
			return BASE + la->address + lastIc;
		}	
	}	
	fprintf(stderr,"Error: Unknown label or known label that was defined wrong, in line %d.\n",lineNum);
	return WRONG;
} 

/* dir_insert_string_arrays: inserts to the arrays the information for one operand if its addressing type is dir and returns the status */
int dir_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char * charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum) 
{
	int add;
	if(strpbrk(current,","))
	{
		add = get_label_address(lastIc,current, ',', externs, labels, baseAddress+offset+1, extFile, lineNum);				
	}
	else
	{
		add = get_label_address(lastIc,current, '\n', externs, labels, baseAddress+offset+1, extFile, lineNum);	
	}			
	if(add == UNKNOWN)
	{				
		commandsArr[1+offset] = get_string_number(UNKNOWN, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'e';			
	}
	else if(add != WRONG)
	{
		commandsArr[1+offset] = get_string_number(add, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'r';			
	}
	else
	{
		return WRONG;				
	}
	return UNKNOWN;
}

/* imm_insert_string_arrays: inserts to the arrays the information for one operand if its addressing type is imm and returns the status */
int imm_insert_string_arrays( char* current, int offset, char * charArr, char **commandsArr, FILE *extFile) 
{
	int num = atoi(current+1);		
	if(num)
	{			
		commandsArr[1+offset] = get_string_number(num, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'a';
		return UNKNOWN;
	}			
	return WRONG;
}

/* rel_insert_string_arrays: inserts to the arrays the information for one operand if its addressing type is rel and returns the status\operand */
int rel_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum)
{
	int operand = UNKNOWN;	
	int add1 = get_label_address(lastIc,current, '[', externs, labels,baseAddress+offset+1, extFile,lineNum);
	int add2 = get_label_address(lastIc,strpbrk(current,"[")+2, ']', externs, labels, baseAddress+offset+2, extFile,lineNum);				
	operand = UNKNOWN;				
	if(add1 == UNKNOWN)
	{				
		commandsArr[1+offset] = get_string_number(UNKNOWN, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'e';			
	}
	else if(add1 != WRONG)
	{
		commandsArr[1+offset] = get_string_number(add1, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'r';			
	}
	else
	{
		operand = WRONG;				
	}
	if(add2 == UNKNOWN)
	{				
		commandsArr[2+offset] = get_string_number(UNKNOWN, INSTRUCTION_LENGTH);
		charArr[2+offset] = 'e';			
	}
	else if(add2 != WRONG)
	{
		commandsArr[2+offset] = get_string_number(1+ add2 - lastIc - BASE, INSTRUCTION_LENGTH);
		charArr[2+offset] = 'a';			
	}
	else
	{
		operand = WRONG;				
	}
	return operand;
}

/* reg_insert_string_arrays: inserts to the arrays the information for one operand if its addressing type is imm and returns the status\operand */
int reg_insert_string_arrays(char* current, int lineNum)
{
	int operand = register_check(current);	
	char *next = current+REG_LENGTH-1;	
	if(!end_of_line(next) && *get_next_char(next) != ',' )
	{
		fprintf(stderr,"Error: Wrong name of register in line %d.\n", lineNum);
		return WRONG;
	}	
	if(operand == WRONG)
	{
		return UNKNOWN;		
	}
	return operand;
}

/* two_insert_string_arrays: inserts to the arrays the information for one operand if its addressing type is two and returns the status\operand */
int two_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum)
{
	int operand = UNKNOWN;
	int add1 = get_label_address(lastIc,strpbrk(current,"]")+1, '[', externs, labels, baseAddress+offset+1, extFile,lineNum);
	int add2 = get_label_address(lastIc,current+1, ']', externs, labels, baseAddress+offset+2, extFile,lineNum);				
	operand = register_check(strpbrk(current+1, "[")+1);				
	if(add1 == UNKNOWN)
	{				
		commandsArr[1+offset] = get_string_number(UNKNOWN, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'e';			
	}
	else if(add1 != WRONG)
	{
		commandsArr[1+offset] = get_string_number(add1, INSTRUCTION_LENGTH);
		charArr[1+offset] = 'r';			
	}
	else
	{
		operand = WRONG;				
	}
	if(add2 == UNKNOWN)
	{				
		commandsArr[2+offset] = get_string_number(UNKNOWN, INSTRUCTION_LENGTH);
		charArr[2+offset] = 'e';			
	}
	else if(add2 != WRONG)
	{
		commandsArr[2+offset] = get_string_number(add2, INSTRUCTION_LENGTH);
		charArr[2+offset] = 'r';			
	}
	else
	{
		operand = WRONG;				
	}
	return operand;		
}

/* insert_string_arrays: inserts to the arrays the information for all operands for one command and returns the status\operand */
int insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr,int addressingType, int baseAddress, 
				FILE *extFile, int lineNum, int status)
{
	int operand = WRONG;
	char *next;	
	switch(addressingType)
	{
		case reg:			
		{
			operand = reg_insert_string_arrays(current,lineNum);
			break;
		}
		case dir:
		{
			operand = dir_insert_string_arrays(lastIc,externs, labels, current, offset, charArr, commandsArr, baseAddress, extFile, lineNum);					
			break;
		}
		case imm:
		{
			operand = imm_insert_string_arrays( current, offset, charArr, commandsArr, extFile);			
			break;
		}
		case rel:
		{
			operand = rel_insert_string_arrays(lastIc,externs, labels, current, offset, charArr, commandsArr, baseAddress, extFile, lineNum);
			break;
		}
		case two:
		{
			operand = two_insert_string_arrays(lastIc,externs, labels, current, offset, charArr, commandsArr, baseAddress, extFile, lineNum);	
			break;
		}
	}
	if(status == firstO && strpbrk(current,",") != NULL)
	{	
		return (operand != WRONG && *get_next_char(strpbrk(current," ,\t\n")) == ',')?operand:WRONG;
	}
	return (operand != WRONG && (!(next = strpbrk(current," \t")) || end_of_line(next)))?operand:WRONG;
	
}

/* print_command: gets and prints a command and all its parts to the .ob file. returns status */
int print_command(FILE* to, int lastIc, char* line, data_list *commandsL, int baseAddress, int status, name_list *externs, label_list *labels, FILE *extFile,  int lineNum)
{		
	int fAdd,sAdd,command,fOperand = UNKNOWN,sOperand = UNKNOWN, offset = 0;
	char *fString, *sString, **commandsArr = NULL, *charArr = NULL;
	int leng = commandsL->data;	
	if(leng != WRONG && ins_check(read_command(line)) == WRONG)/* command */
	{
		commandsArr = (char **)malloc(sizeof(char*)*leng);
		charArr = (char *)malloc(sizeof(char)*leng);		
		command = command_check(read_command(line));		
		fAdd = addressing_type(fString = read_first_variable(line), lineNum);
		sAdd = addressing_type(sString = read_second_variable(line), lineNum);			
		if(fString)
		{	
			fOperand = insert_string_arrays(lastIc, externs, labels, fString, 0, charArr, commandsArr, fAdd, baseAddress, extFile,lineNum,firstO);	
		}		
		if(sString)
		{	
			if(fAdd == two || fAdd == rel)
			{
				offset = 2;		
			}
			if(fAdd == dir || fAdd == imm)
			{
				offset = 1;
			}			
			sOperand = insert_string_arrays(lastIc, externs, labels, sString, offset, charArr, commandsArr, sAdd, baseAddress, extFile,lineNum,secondO);
		}
		if(sOperand == WRONG || fOperand == WRONG)
		{
			status = WRONG;
		}
		if(!sString)
		{
			sOperand = fOperand;
			sAdd = fAdd;
			fOperand = UNKNOWN;
			fAdd = UNKNOWN;
		}
		fAdd = (fAdd == WRONG)?UNKNOWN:fAdd;
		sAdd = (sAdd == WRONG)?UNKNOWN:sAdd;
		commandsArr[0] = get_string_instruction(command, fAdd, sAdd, fOperand, sOperand);
		charArr[0] = 'a';		
		if(status == RIGHT)
		{				
			print_lines(leng, baseAddress,commandsArr,charArr,to);
		}	
		free(charArr);
		free(commandsArr);	
	}
	return status;
}

/* first_transition: makes the second transition on the file with the information from the first transition according to the algorithm in page 28 */
void second_transition(char* name, int lastIc, int dc, FILE *f, int status, name_list *externs, name_list *entries, data_list *commandsL, data_list *data, label_list* labels)
{
	FILE *obFile = NULL, *extFile = NULL, *entFile = NULL;
	data_list* tmpComm = commandsL; 	
	int baseAddress = BASE, tempSt,lineNum = 0, ins;	
	char line[MAX_LINE_LENGTH], *object = ".ob", *external = ".ext", *entry = ".ent", *w = "w";		
	fseek(f, 0, SEEK_SET);
	obFile = open_file(name, object,w);
	extFile = open_file(name,external,w);
	entFile = open_file(name,entry,w);	
	fprintf(obFile,"\t%s\t%s\n",get_string_number(lastIc,I_COUNTER_LENGTH),get_string_number(dc,D_COUNTER_LENGTH));/* prints the first line of the .ob file */				
	while((lineNum = read_next_line(f, line,lineNum)))
	{					
		if((ins = ins_check(read_command(line))) == WRONG)
		{
			tempSt = print_command(obFile, lastIc, line, commandsL, baseAddress, status, externs, labels, extFile, lineNum); 						
			if(tempSt == WRONG)
			{
				status = WRONG;			
			}	
			if(commandsL->data != WRONG)/* right instruction or command */ 
			{
				baseAddress += (commandsL->data);
			}
			commandsL = commandsL->next;
		}	
	}
	print_data(obFile,baseAddress,data);
	if(print_entries(entFile,labels,entries,lastIc) == WRONG)
	{
		status = WRONG;
	}
	/* close files and frees lists */
	close_lists( labels, externs, tmpComm );
	close_file(status, obFile, create_char_name(name, object));
	close_file(status, extFile, create_char_name(name, external));
	close_file(status, entFile, create_char_name(name, entry));
	fclose(f);
	fprintf(stderr,"done!\n");
}



