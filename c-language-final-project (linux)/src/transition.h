#ifndef TRANSITION
#define TRANSITION 

#include "translate.h"
#include "list.h"
#include "print.h"
#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* numbers of operators */
enum{firstO,secondO};

name_list* insert_name_to_list(name_list* list, char* line,int lineNum, label_list* labels, int type);
data_list* insert_data_to_list(data_list* data, char* line, int ins);
void first_transition(char *name);
void second_transition(char* name, int lastIc, int dc, FILE *f, int status, name_list *externs, name_list *entries, data_list *commandsL, data_list *data, label_list* labels);
int get_label_address(int lastIc,char *label, char last, name_list *externs, label_list *labels, int place, FILE *extFile,int lineNum);
int insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr,int addressingType, int baseAddress, FILE *extFile, int lineNum,int status);
int print_command(FILE* to, int lastIc, char* line, data_list *commandsL, int baseAddress, int status, name_list *externs, label_list *labels, FILE *extFile,int lineNum);
int two_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum);
int rel_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char *charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum);
int imm_insert_string_arrays( char* current, int offset, char * charArr, char **commandsArr, FILE *extFile);
int dir_insert_string_arrays(int lastIc, name_list *externs, label_list *labels, char* current, int offset, char * charArr, char **commandsArr, int baseAddress, FILE *extFile, int lineNum);
int reg_insert_string_arrays(char* current, int lineNum);
label_list* insert_label_not_extern(label_list* labels, char* label, int address, int type, name_list* externs, int lineNum);

#endif
