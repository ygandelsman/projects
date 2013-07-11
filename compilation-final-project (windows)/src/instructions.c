#include "instructions.h"

int label_count = 0;

/*
	last_ins: returns the last instruction in the list
*/
instruction *last_ins(instruction *head)
{
	instruction *l = head;
	while(l->next)
		l = l->next;
	return l;
}

/*
	connect_jump_to: connects two list of pointers to instruction
*/
ins_list *connect_jump_to(ins_list *head1, ins_list *head2)
{
	ins_list *last = head1;
	
	if( !head1 )
		return head2;
	while(last->next)
		last = last->next;
	last->next = head2;
	return head1;
}

/*
	add_jump_to: adds a pointer to an instruction to the list
*/
ins_list *add_jump_to(ins_list *list, instruction *ins)
{
	ins_list *pre;
	
	if( !list )
	{
		list = (ins_list *)malloc(sizeof(ins_list));
		list->next = NULL;
		list->inst = ins;
		return list;
	}
	pre = (ins_list *)malloc(sizeof(ins_list));
	pre->next = list;
	pre->inst = ins;
	return pre; 
}

/*
	add_ins: adds quad instruction with the current paramters to the list
*/
instruction *add_ins(instruction *head, char type, char *inst, char *arg1, char* arg2, char *arg3)
{
	instruction *added, *pre;
	
	if( !head )
	{
		head = (instruction *)malloc(sizeof(instruction));
		added = head;
	}
	else
	{
		pre = last_ins( head );
		added = (instruction *)malloc(sizeof(instruction));
		pre->next = added;
	}
	sprintf(added->inst, "%c%s", type, inst);
	sprintf(added->arg1, "%s", arg1);
	sprintf(added->arg2, "%s", arg2);
	sprintf(added->arg3, "%s", arg3);
	added->next = NULL;
	return head;
}

/*
	connect_ins: connects two lists of instructions
*/
instruction *connect_ins(instruction *head1, instruction *head2)
{
	instruction *last;
	
	if( !head1 )
		return head2;
	last = last_ins(head1);
	last->next = head2;
	return head1;
}

/*
	add_label: adds a label to the end of the list
*/
instruction *add_label(instruction *head)
{
	char buf[MAX_QUAD_LENGTH];
	
	label_count++;
	itoa(label_count,buf,MAX_QUAD_LENGTH);
	return add_ins(head,'*', buf, "", "", "");
}

/*
	update_label: updates the first arguments for all instructions in the ins_list to label 
*/
void update_label(ins_list *head, instruction *label)
{
	ins_list *next;
	
	while(head)
	{
		next = head->next;
		rename_arg(head->inst, label->inst);
		free(head);
		head = next;
	}
}

/*
	rename_arg: renames the first argument in the current instruction
*/
void rename_arg(instruction *added, char *newArg1)
{
	free_name(added->arg1);
	sprintf(added->arg1, "%s", newArg1);
}

/*
	print_ins: prints to the .qud file the instructions
*/
void print_ins(instruction *head)
{
	int inst_count = 1, place;
	int lables[MAX_LABELS_NUMBER];
	instruction *start = head;
	
	while(start)
	{	
		if(*(start->inst) == '*')
		{
			lables[atoi(1+start->inst)] = inst_count; 
		}
		else
			++inst_count;
		start = start->next;
	}
	while(head)
	{
		if(*(head->inst) != '*')
		{
			if(*(head->arg1) == '*')
				sprintf(head->arg1, "%d", lables[atoi(1+head->arg1)]);
			fprintf(qud_file,"%s\t%s\t%s\t%s\n", head->inst, head->arg1, head->arg2, head->arg3);
		}
		head = head->next;
	}
}

/*
	add_relop_ins: adds a relop instruction according to the relop type
*/
instruction *add_relop_ins(int relop_type, char *from1, char *from2,instruction *head1, instruction *head2, char compare_type)
{
	instruction *head;
	name_list *to;
	head = connect_ins(head1,head2);
	free_name(from1);
	free_name(from2);
	to = add_without_name('I');
	switch(relop_type)
	{
		case equal:
			head = add_ins(head,compare_type,"EQL",to->name,from1,from2);
			break;
		case not_equal:
			head = add_ins(head,compare_type,"NQL",to->name,from1,from2);
			break;
		case bigger:
			head = add_ins(head,compare_type,"GRT",to->name,from1,from2);
			break;
		case smaller:
			head = add_ins(head,compare_type,"LSS",to->name,from1,from2);
			break;
		case bigger_or_equal:
			head = add_ins(head,compare_type,"LSS",to->name,from1,from2);
			head = reverse_relop_ins(head, to->name);
			break;
		case smaller_or_equal:
			head = add_ins(head,compare_type,"GRT",to->name,from1,from2);
			head = reverse_relop_ins(head, to->name);
			break;
	}
	head = add_ins(head,'J',"MPZ","",to->name,"");
	free_name(to->name);
	return head;
}

/*
	add_step_ins: adds a step instruction 
*/
instruction *add_step_ins(char op, char *to, char *from, char *number, char num_type)
{
	instruction *head = NULL;
	name_list *to_symbol, *from_symbol;
	char first_name[MAX_QUAD_LENGTH], second_name[MAX_QUAD_LENGTH];
	if(!(to_symbol = search(to)))
		yyerror("unknown undentifier, the left side of the assignment statement was not defined in the declarations list");
	else if(!(from_symbol = search(from)))
		yyerror("unknown undentifier, the identifier in the right side of the assignment statement was not defined in the declarations list");
	else if(to_symbol->type == 'I' && (num_type == 'R' || from_symbol->type == 'R'))
		yyerror("illegal assignment, from float to integer");
	else
	{
		strcpy(first_name, from_symbol->name);
		strcpy(second_name, number);
		if(from_symbol->type == 'I' && to_symbol->type == 'R') /* cast from int to float */
			head = convert_to_r(head, first_name);
		if(num_type == 'I' && to_symbol->type == 'R') /* cast from int to float */
			head = convert_to_r(head, second_name);
		head = add_operation_insruction(op, head,to_symbol->type,to, first_name,second_name);
	}	
	return head;
}

/*
	add_arop_ins: adds an arithmetic instruction 
*/
instruction *add_arop_ins(char op, char type, char *last, char *arg1_last, char *arg2_last, char arg1_type, char arg2_type, instruction *arg1_head, instruction *arg2_head)
{
	instruction *head = NULL;
	name_list *symbol;
	if(arg1_type == 'I' && arg2_type == 'R') /* cast from int to float */
		arg1_head = convert_to_r(arg1_head, arg1_last);
	else if(arg2_type == 'I' && arg1_type == 'R') /* cast from int to float */
		arg2_head = convert_to_r(arg2_head, arg2_last);
	free_name(arg1_last);
	free_name(arg2_last);
	head = connect_ins(arg1_head,arg2_head);
	symbol = add_without_name(type);
	strcpy(last, symbol->name);
	return add_operation_insruction(op, head, type,symbol->name, arg1_last, arg2_last);
	
}

/*
	add_operation_insruction: adds an arithmetic instruction according to op
*/
instruction *add_operation_insruction(char op, instruction *head, char type, char *arg1, char *arg2, char *arg3)
{
	switch(op)
	{
		case '+':
			return add_ins(head, type, "ADD", arg1, arg2, arg3);
		case '-':
			return add_ins(head, type, "SUB", arg1, arg2, arg3);
		case '/':
			return add_ins(head, type, "DIV", arg1, arg2, arg3);
		default:
			return add_ins(head, type, "MLT", arg1, arg2, arg3);
	}
}

/*
	expr_type: returns the expression type
*/
char expr_type(char type1, char type2)
{
	if(type1 == 'R' || type2 == 'R')
		return 'R';
	return 'I';
}

/*
	reverse_relop_ins: reverses the meaning of the relop instruction
*/
instruction *reverse_relop_ins(instruction *head, char *lastVar)
{
	instruction *last =  NULL, *bef = NULL;
	
	last = last_ins(head);
	if(!strcmp(last->inst+1, "EQL"))
	{
		*((last->inst) + 1) = 'N';
	}
	else if(!strcmp(last->inst+1, "NQL"))
	{
		*((last->inst) + 1) = 'E';
	}
	else
	{
		head = add_ins(head, 'I',"SUB", lastVar, "1", lastVar);
	}
	return head;
}

/*
	convert_to_r: casts from integer to float the last variable
*/
instruction *convert_to_r(instruction *head, char *last)
{
	name_list *c_name;
	
	c_name = add_without_name('R');
	head = add_ins(head,'I',"TOR",c_name->name, last, "");
	free_name(last);
	strcpy(last, c_name->name);
	return head;
}
/*
	add_assignment_ins: adds an assignment instruction
*/
instruction *add_assignment_ins(char *to, char *from, char from_type, instruction *from_head)
{
	name_list* symbol = NULL;
	instruction *head = NULL;
	free_name(from);
	if(!(symbol = search(to)))
		yyerror("unknown undentifier, the left side of the assignment statement was not defined in the declarations list");
	else if(symbol->type == 'I' && from_type == 'R')
		yyerror("illegal assignment, from float to integer");
	else
	{
		if(symbol->type == 'R' && from_type == 'I')
			return add_ins(from_head,'I',"TOR",to,from,"");
		if(!from_head) /* simple assignment - ID := NUMBER or ID := ID */
			return add_ins(NULL,symbol->type,"ASN",to,from,"");
		/* else: complicated assignment - ID := expression */
		rename_arg(last_ins(from_head),to);
		return from_head;
	}
	return NULL;
}

/*
	add_val_ins: adds ival and rval instructions
*/
instruction *add_val_ins(char from_type, char to_type, char *to, char *from, instruction *from_head, char from_real_type)
{
	name_list* symbol = NULL;
	free_name(from);
	if(!(symbol = search(to))) 
		yyerror("unknown undentifier, the left side of the assignment statement was not defined in the declarations list");
	else if(from_real_type == to_type)
		yyerror("illegal assignment, unnecessary cast - already have the same type");
	else if(symbol->type == from_type)
		yyerror("illegal assignment, wrong cast - from ival to float or from rval to int");
	else
	{
		if(from_type == 'R')
			return add_ins(from_head,'R',"TOI",to,from,"");
		return add_ins(from_head,'I',"TOR",to,from,"");
	}
	return NULL;
}

/*
	free_ins_list: frees the instructions list
*/
void free_ins_list(instruction *head)
{
	instruction *current = head;
	
	while(head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}
}