/* list.c: contains functions for three kinds of lists */
#include "list.h"

/* close_lists: closes the 3 kinds of lists */
void close_lists( label_list* label, name_list* name, data_list* data )
{
	close_label_list(label);
	close_name_list(name);
	close_data_list(data);
}

/* close_label_list: frees all nodes in the label list */
void close_label_list(label_list* list)
{
	while(list)
	{
		list = delete_label(list); 
	}
}

/* close_data_list: frees all nodes in the data list */
void close_data_list(data_list* list)
{
	while(list)
	{
		list = delete_data(list); 
	}
}

/* close_name_list: frees all nodes in the name list */
void close_name_list(name_list* list)
{
	while(list)
	{
		list = delete_name(list); 
	}
}

/* get_label_node: returns a label node with the same label name */
label_list* get_label_node(label_list* list, char* label, char last)
{
	int leng;	
	while(list)
	{
		if( !strncmp(list->label, label, leng = strlen(list->label)) && *(get_next_char(label+leng)) == last)
		{
			return list; 
		}
		list = list->next;
	} 
	return NULL;
}

/* delete_name: deletes a name from the list and returns the new list*/
name_list* delete_name(name_list* head)
{
	name_list* node;		
	if(head)
	{
		node = head->next;
		free(head);
	}
	return node;
}

/* get_name_node: returns a name node with the same label name */
name_list* get_name_node(name_list* list, char* name, char last)
{
	int leng;	
	while(list)
	{
		if( !strncmp(list->name, name, leng = strlen(list->name)) && *(get_next_char(name+leng)) == last)
		{
			return list; 
		}
		list = list->next;
	} 
	return NULL;
}

/* get_last: returns the last node in the list */
data_list* get_last(data_list* head)
{
	data_list* node = head;
	while(node->next)
	{
		node = node->next;
	}	
	return node;
}

/* insert_label: inserts the a new label to the list and returns the new list */
label_list* insert_label(label_list* head, char* label, int address,int type)
{
	label_list* node; 	
	if(!head)
	{
		head = (label_list *)malloc(sizeof(label_list));
		head->next = NULL;
	}
	else
	{
		node = (label_list *)malloc(sizeof(label_list));
		node->next = head;
		head = node;	
	}	
	copy(label, head->label, ':');
	head->address = address;
	head->type = type;
	return head;		
}

/* insert_name: inserts the a new name to the list and returns the new list */
name_list* insert_name(name_list* head, char* label)
{
	name_list* node; 	
	if(!head)
	{
		head = (name_list *)malloc(sizeof(name_list));
		head->next = NULL;
	}
	else
	{
		node = (name_list *)malloc(sizeof(name_list));
		node->next = head;
		head = node;	
	}	
	copy(label, head->name, '\n');
	return head;		
}

/* insert_data: inserts the a new data to the list from the end and returns the new list */
data_list *insert_data(data_list *head, int data)
{
	data_list *node = NULL, *last = NULL; 
	if(!head)
	{
		head = (data_list *)malloc(sizeof(data_list));
		head->next = NULL;
		head->data = data;
	}
	else
	{
		last = get_last(head);
		node = (data_list *)malloc(sizeof(data_list));
		last->next = node;		
		node->next = NULL;	
		node->data = data;
	}	
	return head;		
}
/* delete_data: deletes a data node from list and returns the new list */
data_list *delete_data(data_list *head)
{
	data_list* node;	
	if(head)
	{
		node = head;
		head = head->next;
		free(node);	
	}
	return head;
}

/* string_insert: inserts string to data list and returns the new list */
data_list *string_insert(data_list *head, char* s)
{				
	char *begin = s;
	while(*s != '\0')
	{
		head = insert_data(head, (int)(*s));
		++s;
	}
	head = insert_data(head, (int)(*s));
	free(begin);
	return head;
}

/* numbers_insert: inserts numbers to data list and returns the new list */
data_list *numbers_insert(data_list *head, int* arr, int leng)
{
	int i;
	for(i = 0; i < leng; ++i)
	{
		head = insert_data(head, arr[i]);
	}
	free(arr);
	return head;
}

/* delete_label: deletes a label from list and returns the new list */
label_list *delete_label(label_list* head)
{
	label_list *node;	
	if(head)
	{
		node = head;
		head = head->next;		
		free(node);	
	}
	return head;
}

