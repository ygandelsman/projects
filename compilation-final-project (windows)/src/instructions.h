#ifndef INS
#define INS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "names.h"

#define MAX_QUAD_LENGTH 10
#define MAX_LABELS_NUMBER 1000
 
extern FILE *qud_file;
extern FILE *err_file;

typedef struct ins
{
	char inst[MAX_QUAD_LENGTH];
	char arg1[MAX_QUAD_LENGTH];
	char arg2[MAX_QUAD_LENGTH];
	char arg3[MAX_QUAD_LENGTH];
	struct ins *next;
} instruction;

typedef struct ins_p
{
	instruction *inst;
	struct ins_p *next;
} ins_list;

enum {equal,not_equal,bigger,smaller,bigger_or_equal,smaller_or_equal} rel;

char expr_type(char type1, char type2);
instruction *add_val_ins(char from_type, char to_type, char *to, char *from, instruction *from_head, char from_real_type);
instruction *add_assignment_ins(char *to, char *from, char from_type, instruction *from_head);
instruction *add_arop_ins(char op, char type, char *last, char *arg1_last, char *arg2_last, char arg1_type, char arg2_type, instruction *arg1_head, instruction *arg2_head);
instruction *add_step_ins(char op, char *to, char *from, char *number, char num_type);
instruction *add_operation_insruction(char op, instruction *head, char type, char *arg1, char *arg2, char *arg3);
instruction *add_relop_ins(int relop_type, char *from1, char *from2,instruction *head1, instruction *head2, char compare_type);
instruction *add_label(instruction *head);
instruction *convert_to_r(instruction *head, char *last);
ins_list *connect_jump_to(ins_list *head1,ins_list *head2);
void update_label(ins_list *head, instruction *label);
ins_list *add_jump_to(ins_list *list, instruction *ins);
instruction *last_ins(instruction *head);
instruction *add_ins(instruction *head, char type, char *inst, char *arg1, char* arg2, char *arg3);
void free_ins_list(instruction *head);
instruction *connect_ins(instruction *head1, instruction *head2);
instruction *reverse_relop_ins(instruction *head, char *lastVar);
void rename_arg(instruction *head, char *newArg1);

#endif