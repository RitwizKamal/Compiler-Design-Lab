%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <ctype.h>
int symbols[128];
extern int yylineno;
extern char *yytext;
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
extern FILE *fp;
%}

%token INT FLOAT CHAR DOUBLE VOID
%token FOR WHILE
%token IF ELSE PRINTF
%token STRUCT
%token NUM ID
%token INCLUDE
%token DOT
%token MAIN_TOK

%right '='
%left AND OR
%left '<' '>' LE GE EQ NE LT GT
%start S



%%
S    :  Type  MAIN_TOK '(' ')'  Block   {printf("Syntax for Main Function is Ok....\n");}
     |  Type Declaration		{printf("Syntax for Declaration is Ok....\n");}
     |  Type ID '(' ArgListOpt ')' ';'	{printf("Syntax for User defined function is Ok....\n");}
     ;
Block : '{' StmtList '}'		{printf("Syntax for a Block of Statements is Ok....\n");}
        ; 

/* Declaration block */
Declaration: Type Assignment ';'	
    | Assignment ';'
    //| FunctionCall ';'
    | StructStmt ';'
    | error				
    ;

/* Assignment block */
Assignment: ID '=' Assignment       {updateSymbolVal($1,$3); }
    | ID '=' FunctionCall
    | ID ',' Assignment
    | NUM ',' Assignment
    | ID '+' Assignment         { $$ = $1 + $3; }
    | ID '-' Assignment            { $$ = $1 - $3; }
    | ID '*' Assignment             { $$ = $1 * $3; }
    | ID '/' Assignment         { $$ = $1 / $3; }
    | NUM '+' Assignment        
    | NUM '-' Assignment
    | NUM '*' Assignment
    | NUM '/' Assignment
    | '\'' Assignment '\''
    | '(' Assignment ')'
    | '-' '(' Assignment ')'
    | '-' NUM
    | '-' ID
    |   NUM                     { $$ = $1;}
    |   ID                     { $$ = symbolVal($1); }
    ;

/* Function Call Block */
FunctionCall : ID'('')'
    | ID'('Assignment')'
    ;

/* Function block */
Function: Type ID '(' ArgListOpt ')' CompoundStmt
    ;
ArgListOpt: ArgList
    |
    ;
ArgList:  ArgList ',' Arg
    | Arg
    ;
Arg:    Type ID
    ;
CompoundStmt:   '{' StmtList '}'
    ;
StmtList:   StmtList Stmt
    |
    ;
Stmt:   WhileStmt
    | Declaration
    | ForStmt
    | IfStmt
    | PrintFunc
    |Function
    | ';'
    ;

/* Type Identifier block */
Type:   INT
    | FLOAT
    | CHAR
    | DOUBLE
    | VOID
    ;

/* Loop Blocks */
WhileStmt: WHILE '(' Expr ')' Stmt
    | WHILE '(' Expr ')' CompoundStmt
    ;

/* For Block */
ForStmt: FOR '(' Expr ';' Expr ';' Expr ')' Stmt
       | FOR '(' Expr ';' Expr ';' Expr ')' CompoundStmt
       | FOR '(' Expr ')' Stmt
       | FOR '(' Expr ')' CompoundStmt
    ;

/* IfStmt Block */
IfStmt : IF '(' Expr ')'
        Block
    ;

/* Struct Statement */
StructStmt : STRUCT ID '{' Type Assignment '}'
    ;

/* Print Function */
PrintFunc : PRINTF  Expr  ';'
    ;

/*Expression Block*/
Expr:
    | Expr LE Expr
    | Expr GE Expr
    | Expr NE Expr
    | Expr EQ Expr
    | Expr GT Expr
    | Expr LT Expr
    | Assignment
    ;
%%
//#include"lex.yy.c"
#include<ctype.h>
//int count=0;

int main(int argc, char *argv[])
{

int i;
    for(i=0; i<128; i++) {
        symbols[i] = 0;
    }

    return yyparse ( );
}

int computeSymbolIndex(char token)
{
    int idx = -1;
    if(islower(token)) {
        idx = token - 'a' + 26;
    } else if(isupper(token)) {
        idx = token - 'A';
    }
    return idx;
} 

/* returns the value of a given symbol */
int symbolVal(char symbol)
{
    int bucket = computeSymbolIndex(symbol);
    return symbols[bucket];
}

/* updates the value of a given symbol */
void updateSymbolVal(char symbol, int val)
{
    int bucket = computeSymbolIndex(symbol);
    symbols[bucket] = val;
}


void yyerror(char *s) {
    printf("%d : %s %s\n", yylineno, s, yytext );
}
