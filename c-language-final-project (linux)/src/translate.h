#ifndef TRANSLATE
#define TRANSLATE

#include "read.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WRONG -1
#define RIGHT 1 
#define UNKNOWN 0 
#define NUM_OF_COMMANDS 16
#define NUM_OF_REGISTERS 8
#define NUM_OF_INSTRUCTIONS 4
#define LABEL 30
#define REG_LENGTH 3

/* commands */
enum {mov, cmp, add, sub, no, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop};

/* registers */
enum {r0,r1,r2,r3,r4,r5,r6,r7};

/* addrssing types */
enum {imm, dir, rel, two, reg};

/* instructions */
enum {dat,str,ent,ext};

void redef_error(int lineNum);
int error_parameter(char *num ,int lineNum);
int ins_error(char* to ,int lineNum);
void copy(char* from, char* to, char end);
void label_error(int lineNum);
int command_check(char* comm);
int ins_check(char* ins);
int number_check(char* operand);
int data_check(char* s);
int number_of_lines(char* line,int lineNum);
int number_of_lines_ins(char* line,int lineNum);
int number_of_lines_comm(char* line,int lineNum);
int check_right_addressing(char* line,int lineNum);
int two_params( int command, int first, int second, int lineNum);
int one_param( int command, int param,int lineNum );
int zero_params( int command,int lineNum );
int error_number_of_params(int lineNum);
int error_addressing_of_params(int lineNum);
int error_def_labels(int lineNum);
int number_of_parameters(char* line,int lineNum);
int addressing_type(char* operand,int lineNum);
int two_dimension_check(char* operand,int lineNum);
int relative_check(char* operand, int lineNum);
int label_check(char* label, char end,int lineNum);
int register_check(char* operand);
int *get_numbers(char* s);
char *get_string(char* s);
int string_check(char* s);


#endif
