%{
#include <stdio.h>
#include "names.h"
#include "instructions.h"
#include <malloc.h>

extern FILE *yyout;
extern int line;
extern int column;

int error_exist = 0;
name_list *current_symbol = NULL, *next_symbol = NULL;
instruction *curr_ins = NULL;
ins_list *boolist = NULL;
char ident_type;
char compare_type;
%}
%error-verbose

%union
{
	struct number{
		char value[MAX_CPL_LENGTH];
		char type;
	} num;

	char id[MAX_CPL_LENGTH];
	
	char type;
	
	struct exp{
		instruction *head;
		char last[MAX_CPL_LENGTH];
		char type;
	} expression;
	
	struct bool{
		ins_list *false;
		instruction *head;
	} boolean;

	char arop; 
	
	instruction *stmt;
	
	int relop; 
}

%type <type> type

%type <expression> expression				
%type <expression> term			
%type <expression> factor

%type <boolean> boolfactor		
%type <boolean> boolexpr
%type <boolean> boolterm

%type <stmt> write_stmt
%type <stmt> assignment_stmt
%type <stmt> read_stmt
%type <stmt> stmt
%type <stmt> control_stmt
%type <stmt> val
%type <stmt> step
%type <stmt> stmt_block
%type <stmt> stmtlist

%token PROGRAM
%token <id> ID
%token START
%token END
%token DECLARATIONS
%token <type>INT
%token <type>FLOAT
%token PRINT
%token READ
%token ASSIGNOP
%token IVAL
%token RVAL
%token IF
%token THEN
%token OTHERWISE
%token WHILE
%token DO
%token FOR
%token <arop>ADDOP
%token <num>NUM
%token <arop>MULOP
%token OROP
%token ANDOP
%token <relop>RELOP

%%
program 	:  	PROGRAM ID '{' declarations START stmtlist END '}' 
				{
					$6 = add_ins($6,'H',"ALT","","","");
					print_ins($6);
					free_all_names();
					free_ins_list($6);
				}
			|	error '{' declarations START stmtlist END '}'  {yyerrok; yyclearin;}
			|	PROGRAM ID '{' declarations START stmtlist '}' {yyerrok; yyclearin;}
			|	PROGRAM ID '{' stmtlist '}' {yyerrok; yyclearin;}
				;

declarations 	:  	DECLARATIONS declarlist
				| 	/*eplsilon*/
				;

declarlist 	:  	declarlist type ':' {ident_type = $2;} idents ';' 
			| 	type ':' {ident_type = $1;} idents ';' 
			|	declarlist error ';'
			|	error type ':' idents ';'
				;

idents 		:  	idents ',' ID 
				{
					set_idents(ident_type, $3);
				}
			| 	ID 	
				{	
					set_idents(ident_type, $1);
				}
			| 	idents ',' error ';' {yyerrok; yyclearin;}
			| 	error ','
				;
				
type 		: 	INT {$$ = $1;} 
			| 	FLOAT {$$ = $1;}
			| 	error ';' {yyerrok; $$ = 0; yyclearin;}
				; 

stmtlist  	:   stmtlist stmt {$$ = connect_ins($1, $2);} 
            | 	/* epsilon */ {$$ = NULL;}
				;

stmt	 	:	val ';'{$$ = $1;}
			| 	control_stmt {$$ = $1;}
			| 	read_stmt ';'{$$ = $1;}
			| 	write_stmt ';'{$$ = $1;}
			| 	stmt_block {$$ = $1;}
			| 	assignment_stmt ';'{$$ = $1;}
			| 	error ';' {yyerrok; $$ = NULL; yyclearin;}
			| 	error ')' {yyerrok; $$ = NULL; yyclearin;}
				;
				
write_stmt 	:  	PRINT '(' expression ')'
				{
					$$ = add_ins($3.head,$3.type,"PRT",$3.last,"","");		
					free_name($3.last);
				}
			| 	PRINT '(' error ')' {yyerrok; $$ = NULL; yyclearin;}
				;
				
read_stmt 	: 	READ '(' ID ')'
				{
					$$ = NULL;
					if(!(current_symbol = search($3)))
						yyerror("unknown undentifier, the parameter of read was not defined in the declarations list");
					else
						$$ = add_ins(NULL,current_symbol->type,"INP",current_symbol->name,"","");
				}
			| 	READ '(' error ')' {yyerrok; $$ = NULL; yyclearin;}
				;

assignment_stmt	:	ID ASSIGNOP expression 	{ $$ = add_assignment_ins($1, $3.last, $3.type, $3.head);}
					| error ASSIGNOP expression ';' {yyerrok; $$ = NULL; yyclearin;} 
				;
				
val		: 	ID ASSIGNOP IVAL '(' expression ')' 
			{
				$$ = add_val_ins('R','I', $1, $5.last, $5.head, $5.type);
			} 
			
		| 	ID ASSIGNOP RVAL '(' expression ')' 
			{
				$$ = add_val_ins('I', 'R', $1, $5.last, $5.head, $5.type);
			}
			;
			
control_stmt 	:	IF '(' boolexpr ')' THEN stmt OTHERWISE stmt
					{	
						$$ = connect_ins($3.head, $6);
						$$ = add_ins($$,'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins($$)); /*makes list of pointers the the last instruction*/
						$$ = add_label($$);
						update_label($3.false, last_ins($$));
						$$ = connect_ins($$, $8);
						$$ = add_label($$);
						update_label(boolist, last_ins($$));
					}
				|	IF error THEN stmt OTHERWISE stmt {yyerrok; $$ = NULL; yyclearin;}
				|	IF '(' boolexpr ')' THEN stmt error ';' {yyerrok; $$ = NULL; yyclearin;}
				|	IF '(' boolexpr ')' error ';' {yyerrok; $$ = NULL; yyclearin;}
				
     			|	WHILE '(' boolexpr ')' DO stmt 
					{
						$$ = add_label(NULL);
						$$ = connect_ins($$, $3.head);
						$$ = connect_ins($$, $6);
						$$ = add_ins($$,'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins($$));
						update_label(boolist, $$);
						$$ = add_label($$);
						update_label($3.false, last_ins($$));
					}
					
				|	WHILE error DO stmt ';' {$$ = NULL; yyerrok; yyclearin;}
				|	WHILE '(' error ')' {$$ = NULL; yyerrok; yyclearin;}
					
				| 	FOR '(' assignment_stmt ';' boolexpr ';' step ')' stmt
					{
						$$ = add_label($3);
						curr_ins = last_ins($$);
						$$ = connect_ins($$, $5.head); 
						$$ = connect_ins($$, $9);
						$$ = connect_ins($$, $7);
						$$ = add_ins($$,'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins($$));
						update_label(boolist, curr_ins);
						$$ = add_label($$);
						update_label($5.false, last_ins($$));
					}
						
				|	FOR '(' assignment_stmt ';' error ';' step ')'{$$ = NULL; yyerrok; yyclearin;}
				|	FOR '(' assignment_stmt ';' boolexpr ';' error ')'{$$ = NULL; yyerrok; yyclearin;}
				|	FOR '(' error ';' boolexpr ';' step ')'{$$ = NULL; yyerrok; yyclearin;}
				|	FOR error ';' {$$ = NULL; yyerrok; yyclearin;}
				;

stmt_block 	:	'{' stmtlist '}' {$$ = $2;}
				;

step 		: 	ID ASSIGNOP ID ADDOP NUM { $$ = add_step_ins($4, $1, $3, $5.value,$5.type); }	
    		| 	ID ASSIGNOP ID MULOP NUM { $$ = add_step_ins($4, $1, $3, $5.value,$5.type); }
				;
				
boolexpr	: 	boolexpr OROP boolterm 
				{
					$$.head = add_ins($1.head,'J',"UMP","","","");
					boolist = add_jump_to(NULL, last_ins($$.head));
					$$.head = add_label($$.head);
					update_label($1.false, last_ins($$.head));
					$$.head = connect_ins($$.head, $3.head);
					add_label($$.head);
					update_label(boolist, last_ins($$.head));
					$$.false = $3.false;
				}
			| 	boolterm  
				{
					$$.head = $1.head;
					$$.false = $1.false;
				}
				;
				
boolterm   	:	boolterm ANDOP boolfactor
				{
					$$.head = connect_ins($1.head,$3.head);
					$$.false = connect_jump_to($1.false, $3.false);
				}
         	| 	boolfactor    
				{
					$$.false = $1.false;
					$$.head = $1.head;
				}
				;
				
boolfactor 	: 	'!' '(' boolexpr ')'
				{
					$$.head = add_ins($3.head,'J',"UMP","","","");
					$$.false = add_jump_to(NULL, last_ins($$.head));
					add_label($$.head);
					update_label($3.false, last_ins($$.head));
				}
			| 	expression RELOP expression  
				{
					if($1.type == 'I' && $3.type == 'R') /* comparison between different types - makes cast */
						$1.head = convert_to_r($1.head, $1.last);
					else if($3.type == 'I' && $1.type == 'R')
						$3.head = convert_to_r($3.head, $3.last);
					$$.head = add_relop_ins($2, $1.last, $3.last, $1.head, $3.head, expr_type($1.type, $3.type));
					$$.false = add_jump_to(NULL, last_ins($$.head));
				}
				;
				
expression 	:	expression ADDOP term
				{				
					$$.type = expr_type($1.type, $3.type);
					$$.head = add_arop_ins($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
				}
 			| 	term
				{
					$$.type = $1.type;
					$$.head = $1.head;
					strcpy($$.last, $1.last);
				}
				;
				
term 		: 	term MULOP factor
				{
					$$.type = expr_type($1.type, $3.type);
					$$.head = add_arop_ins($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
				}
			| 	factor 
				{
					$$.type = $1.type;
					$$.head = $1.head;
					strcpy($$.last, $1.last);
				}
				;
				
factor		:  	'(' expression ')'	
				{
					$$.type = $2.type;
					$$.head = $2.head;
					strcpy($$.last,$2.last);
				}
          	|	ID		
				{
					$$.head = NULL;
					if(!(current_symbol = search($1))) 
					{
						yyerror("unknown undentifier, the identifier was not defined in the declarations list");
						$$.type = 0;
					}
					else
					{
						strcpy($$.last, $1);
						$$.type = current_symbol->type;
					}
				}
          	|	 NUM	
				{
					strcpy($$.last, $1.value);
					$$.type = $1.type;
					$$.head = NULL;
				}
				;		
%%

int yyerror(char *err)
{
	fprintf(err_file, "ERROR - line %d, column %d: %s\n", line, column, err);
	error_exist = 1;
	return 1;
}
