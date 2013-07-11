#ifndef PRINT
#define PRINT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"
#include "translate.h"
#include "list.h"
#define INSTRUCTION_LENGTH 17
#define ADD_LENGTH 3
#define COMM_LENGTH 4
#define D_COUNTER_LENGTH 5
#define BASE 100
#define I_COUNTER_LENGTH 9
#define PUT_BIT(A) (((mask) & (A))?'1':'0') /* returns the bit in some place in A */
#define BACK_RETURN 2

char* get_string_instruction(int command, int first_address, int second_address, int first, int second);
char* get_string_number(int num, int str_leng);
void print_lines(int leng, int baseAddress, char **commandsArr, char *charArr, FILE *to);
FILE* open_file(char* name, char* end,char* type);
void close_file(int status, FILE *f, char *name);
void print_data(FILE *f, int baseAddress, data_list *d);
int print_entries(FILE *f, label_list *labels, name_list *entries, int ic);

#endif
