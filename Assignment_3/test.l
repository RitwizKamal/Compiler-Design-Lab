%{
#include<stdio.h>
#include "tokendef_LEX.h"
%}

%option noyywrap

%%
;                                 {return(SEMICOLON_TOK);}
,                                 {return(COMMA_TOK);}
\{                                {return(LCRLY_TOK);}
\}                                {return(RCRLY_TOK);}
\(				  {return(LPAREN_TOK);}
\)				  {return(RPAREN_TOK);}
int                               {return(INT_TOK);}
main                              {return(MAIN_TOK);}
float				  {return(FLOAT_TOK);}
char				  {return(CHAR_TOK);}
for				  {return(FOR_TOK);}
do				  {return(DO_TOK);}
while				  {return(WHILE_TOK);}
if				  {return(IF_TOK);}
else				  {return(ELSE_TOK);}
([0-9])+			  {return(INTCONST_TOK);}	
([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])* {return(ID_TOK);}
#((<)*([a-z]|[A-Z])*)*(.)*([a-z]|[A-Z]|[0-9])*(>)* {return(HEADER_TOK);}
(>|>=|<|<=)		          {return(REL_OP_TOK);}
\+			  	  {return(ARITH_OP_TOK);}
\-			  	  {return(ARITH_OP_TOK);}
\*			  	  {return(ARITH_OP_TOK);}
\/			  	  {return(ARITH_OP_TOK);}
\&&				  {return(LOGICAL_OP);}
\|				  {return(BITWISE_OP);}
\!				  {return(LOGICAL_OP);}
\&			  	  {return(BITWISE_OP);}
\<<			          {return(BITWISE_OP);}
\>>			          {return(BITWISE_OP);}
\=				  {return(ASSIGN_OP);}
%%


int main()
{
    int val;
    //char file_name[]="testfile.c";
    //FILE *yyin;
    //printf("Welcome to Lexical Analyzer !!!\n");
    //printf("Enter file name:");
    //gets(file_name);
    //char ch;
    yyin=fopen("testfile.c","r");
    while((val = yylex()) > 0)
    {
        printf("Token ===%s; Token ID ====%d\n", yytext, val);    
    }
    
    return 0;
}

