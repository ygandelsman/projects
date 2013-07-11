%option noyywrap
%{
#include <stdio.h>
#include "names.h"
#include "instructions.h"
#include "cpq.tab.h" 
int line = 1;
int column = 0;
%}
%x comment
%%

"{"            	{column+=yyleng; fprintf(yyout,"%s",yytext); return '{';}
"}"            	{column+=yyleng; fprintf(yyout,"%s",yytext); return '}';}
"("            	{column+=yyleng; fprintf(yyout,"%s",yytext); return '(';}
")"            	{column+=yyleng; fprintf(yyout,"%s",yytext); return ')';}
","            	{column+=yyleng; fprintf(yyout,"%s",yytext); return ',';}
":"            	{column+=yyleng; fprintf(yyout,"%s",yytext); return ':';}
"!"				{column+=yyleng; fprintf(yyout,"%s",yytext); return '!';}
";"				{column+=yyleng; fprintf(yyout,"%s",yytext); return ';';}

"declarations"  {column+=yyleng; fprintf(yyout,"%s",yytext); return DECLARATIONS;}
"end"			{column+=yyleng; fprintf(yyout,"%s",yytext); return END;}

"float"			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.type = 'R';
					return FLOAT;
				}
"int"			{	
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.type = 'I';
					return INT;
				}
				
"for"			{column+=yyleng; fprintf(yyout,"%s",yytext); return FOR;}
"if"			{column+=yyleng; fprintf(yyout,"%s",yytext); return IF;}
"program"		{column+=yyleng; fprintf(yyout,"%s",yytext); return PROGRAM;}
"then"			{column+=yyleng; fprintf(yyout,"%s",yytext); return THEN;}
"otherwise"		{column+=yyleng; fprintf(yyout,"%s",yytext); return OTHERWISE;}
"print"			{column+=yyleng; fprintf(yyout,"%s",yytext); return PRINT;}
"read"			{column+=yyleng; fprintf(yyout,"%s",yytext); return READ;}
"rval"			{column+=yyleng; fprintf(yyout,"%s",yytext); return RVAL;}
"ival"			{column+=yyleng; fprintf(yyout,"%s",yytext); return IVAL;}
"start"			{column+=yyleng; fprintf(yyout,"%s",yytext); return START;}
"while"			{column+=yyleng; fprintf(yyout,"%s",yytext); return WHILE;}
"do"			{column+=yyleng; fprintf(yyout,"%s",yytext); return DO;}

"=="			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = equal;
					return RELOP;
				}
"<>"			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = not_equal;
					return RELOP;
				}
"<"				{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = smaller;
					return RELOP;
				}
">"				{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = bigger;
					return RELOP;
				}
">="			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = bigger_or_equal;
					return RELOP;
				}
"<="			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.relop = smaller_or_equal;
					return RELOP;
				}		
				
"+"				{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.arop = '+';
				 	return ADDOP;
				}
"-"				{	
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.arop = '-';
				 	return ADDOP;
				}
"*"				{	
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.arop = '*';
					return MULOP;
				}
"/"				{	
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					yylval.arop = '/';
					return MULOP;
				}

":="			{column+=yyleng; fprintf(yyout,"%s",yytext); return ASSIGNOP;}
"or"			{column+=yyleng; fprintf(yyout,"%s",yytext); return OROP;}
"and"			{column+=yyleng; fprintf(yyout,"%s",yytext); return ANDOP;}

[0-9]+"."[0-9]*	{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					strncpy(yylval.num.value, yytext, MAX_CPL_LENGTH);
					yylval.num.type = 'R';
					return NUM;
				}

[0-9]+			{
					column+=yyleng; 
					fprintf(yyout,"%s",yytext); 
					strncpy(yylval.num.value, yytext, MAX_CPL_LENGTH);
					yylval.num.type = 'I';
				 	return NUM;
				}

[a-zA-Z][0-9a-zA-Z]*	{
							column+=yyleng; 
							fprintf(yyout,"%s",yytext); 
							if(strlen(yytext) < MAX_CPL_LENGTH)
								strcpy(yylval.id, yytext);
							else
								yyerror("illegal identifier, the maximum length of the identifier is 9 characters");
							return ID;
						}

"/*"         			{fprintf(yyout,"%s",yytext); column+=yyleng; BEGIN(comment);}
<comment>[^*\n]*        {fprintf(yyout,"%s",yytext); column+=yyleng;} /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   {fprintf(yyout,"%s",yytext); column+=yyleng;} /* eat up '*'s not followed by '/'s */
<comment>\n             {column=0; ++line; fprintf(yyout,"%s%d:\t",yytext,line); }
<comment>"*"+"/"        {fprintf(yyout,"%s",yytext); column+=yyleng; BEGIN(INITIAL);}

[ \t]					{column+=yyleng; fprintf(yyout,"%s",yytext);}
"\n" 					{line++; column=0; fprintf(yyout,"%s%d:\t",yytext,line); }
. 	    	   			{column+=yyleng; fprintf(yyout,"%s",yytext); yyerror("unknown token");}

%%