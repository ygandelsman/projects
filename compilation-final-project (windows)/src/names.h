#ifndef NAME
#define NAME

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPL_LENGTH 10
#define FREE 0
#define OCCUPIED 1
#define LOCKED 2

typedef struct na{
	char name[MAX_CPL_LENGTH];
	char type;
	int state;
	struct na *left;
	struct na *right;
} name_list;

void set_idents(char type, char *name);
name_list *free_search(char type, name_list *curr);
name_list *search( char* name );
name_list *place_to_add(char* name, name_list *curr);
name_list *add_name( char *name, char type );
name_list *add_without_name( char type );
void free_name( char *name );
void free_all_names();
void free_names(name_list *curr);


#endif