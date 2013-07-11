#ifndef LIST
#define LIST

#define LABEL_LENGTH 31

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "translate.h"

/* types of labels */
enum {codeT, dataT};

/* label_list: struct of labels for the .ob file */
typedef struct label_l
{
	char label[LABEL_LENGTH];
	int address;
	int type;
	struct label_l* next; 	
} label_list; 

/* data_list: struct of data from the insructions to the .ob file */
typedef struct data_l
{
	int data;	
	struct data_l* next; 	
} data_list;

/* name_list: struct of labels for the .ext and .ent files */
typedef struct name_l
{
	char name[MAX_LINE_LENGTH];	
	struct name_l* next; 	
} name_list;

void close_lists( label_list* label, name_list* name, data_list* data );
void close_label_list(label_list* list);
void close_name_list(name_list* list);
void close_data_list(data_list* list);
label_list* get_label_node(label_list* list, char* label, char last);
name_list* delete_name(name_list* head);
name_list* get_name_node(name_list* list, char* name, char last);
data_list* get_last(data_list* head);
label_list* insert_label(label_list* head, char* label, int address, int type);
name_list* insert_name(name_list* head, char* label);
data_list *insert_data(data_list *head, int data);
data_list *delete_data(data_list *head);
data_list *string_insert(data_list *head, char* s);
data_list *numbers_insert(data_list *head, int* arr, int leng);
label_list *delete_label(label_list* head);

#endif
