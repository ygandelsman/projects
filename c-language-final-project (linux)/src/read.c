/* read.c: contains functions that reads and returns pointers to places in a line */
#include "read.h"

/* get_next_char: returns a pointer to the next char that is not space or tab */
char* get_next_char(char* c)
{
	while(*c == '\t' || *c == ' ')
	{
		++c;
	}
	return c;	
}

/* create_char_name: returns the name of the file by connecting the name with the end */
char* create_char_name(char* name, char *end)
{
	int leng;	
	char* fileName = (char *)malloc(leng = (strlen(name) + strlen(end) + INTERVAL));
	if(fileName)
	{	
		strcpy(fileName, name);
		strcpy(fileName + strlen(name), end);
	}
	return fileName;
}

/* read_next_line: reads the next line of the file to the char array, returns line number, or 0 if coud'nt read */
int read_next_line(FILE *stream, char* line, int currLine)
{	
	char* status;	
	if(!stream)
	{
		return 0;
	}	
	status = fgets(line, MAX_LINE_LENGTH, stream);			
	while(*(line = get_next_char(line)) == '\n' || *line == ';') /* empty statement */
	{			
		if(!status)
		{
			return 0;
		}
		status = fgets(line, MAX_LINE_LENGTH, stream);			
		++currLine;
	}
	if(!status)
	{
		return 0;
	}
	++currLine;	
	return currLine;
	
}

/* read_label: returns the beginning of the label if exists, NULL otherwise */
char* read_label(char* line)
{
	char *s = strpbrk(line,":");
	if(!s)
	{
		return NULL;
	}	
	return get_next_char(line);
}

/* read_command: returns the beginning of the command if exists, NULL otherwise */
char* read_command(char* line)
{	
	if(read_label(line))
	{
		return get_next_char(strpbrk(line,":") + INTERVAL);
	}
	return get_next_char(line);
}

int end_of_line(char* current)
{
	return (*get_next_char(current) == '\n')||(*get_next_char(current) == '\0');
}


/* read_first_variable: returns the first variable in the line if exists, NULL otherwise */
char* read_first_variable(char* line)
{	
	char * c;	
	if(!(c = strpbrk(read_command(line),"\t ")) || end_of_line(c))
	{
		return NULL;	
	}	
	return get_next_char(strpbrk(read_command(line),"\t \n"));
}

/* read_second_variable: returns the second variable in the line if exists, NULL otherwise */
char* read_second_variable(char* line)
{		
	char *c;	
	if(!read_first_variable(line))
	{
		return NULL;
	}
	if(!(c = strpbrk(read_first_variable(line),",")))
	{
		return NULL;	
	}	
	if(!end_of_line(strpbrk(get_next_char(c+1),"\t \n")))
	{
		return NULL;	
	}	
	return get_next_char(c+INTERVAL);
}


