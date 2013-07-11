#ifndef READ
#define READ
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024
#define INTERVAL 1

char* read_second_variable(char* line);
char* read_first_variable(char* line);
int end_of_line(char* current);
char* read_command(char* line);
char* read_label(char* line);
int read_next_line(FILE *stream, char* line, int currLine);
char* get_next_char(char* c);
char* create_char_name(char* name, char *end);

#endif
