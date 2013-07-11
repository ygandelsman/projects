#include "names.h"

int names_counter = 0;
name_list *head = NULL;

/*
	set_idents: adds new idents to the tree
*/
void set_idents(char type, char *name)
{
	if(!search(name))
		add_name(name,type); 
	else
		yyerror("identifier error, the identifier was already defined before in the declarations list");
}

/*
	search: searchs for the current name in the tree
*/
name_list *search( char* name )
{
	name_list *curr = head;
	
	while(curr)
	{
		if(!strcmp(curr->name, name))
			return curr;
		else if(strcmp(curr->name, name) < 0)
			curr=curr->right;
		else
			curr=curr->left;
	}
	return NULL;
}

/*
	free_search: searchs for a free symbol from the current type in the tree
*/
name_list *free_search(char type, name_list *curr)
{
	name_list *answer;
	
	if(!curr)
		return NULL;
	if(curr->state == FREE && curr->type == type)
		return curr;
	if((answer = free_search(type,curr->left)))
		return answer;
	return free_search(type,curr->right);
}

/*
	place_to_add: returns a place for a new name
*/
name_list *place_to_add(char *name, name_list *curr)
{
	
	if(!curr)
		return NULL;
	if(strcmp(curr->name, name) < 0)
	{
		if(curr->right)
			return place_to_add(name,curr->right);
		return curr;
	}
	if(curr->left)
		return place_to_add(name,curr->left);
	return curr;
}

/*
	add_name: adds a symbol with the current name and type to the tree
*/
name_list *add_name( char *name, char type )
{
	name_list *added, *pre;
		
	if( !head )
	{
		head = (name_list *)malloc(sizeof(name_list));
		added = head;
	}
	else
	{
		added = (name_list *)malloc(sizeof(name_list));
		pre = place_to_add(name,head);
		if(strcmp(pre->name, name) < 0)
			pre->right = added;
		else
			pre->left = added;
	}
	sprintf(added->name, "%s", name);
	added->left = NULL;
	added->right = NULL;
	added->type = type;
	added->state = LOCKED;
	return added;
}

/*
	add_without_name: adds a new symbol to the tree, named _X, when X is number
*/
name_list *add_without_name( char type )
{
	char name[MAX_CPL_LENGTH];
	name_list *added;
		
	added = free_search( type,head );
	if(!added)
	{
		sprintf(name, "_%d", names_counter);
		added = add_name( name, type );
		++names_counter;
	}
	added->state = OCCUPIED;
	return added;
}

/*
	free_name: frees the state of the current name
*/
void free_name( char *name )
{
	name_list *curr = NULL;
		
	if( (curr = search(name)) && curr->state == OCCUPIED )
			curr->state = FREE;
}

/*
	free_all_names: frees the memory for the tree
*/
void free_all_names()
{
	
	free_names(head);
}
/*
	free_all_names: frees the memory for the current place in the tree
*/
void free_names(name_list *curr)
{
	
	if(curr)
	{
		free_names(curr->right);
		free_names(curr->left);
		free(curr);
	}
}
