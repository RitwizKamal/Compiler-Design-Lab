#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_TOK 3

void yylex(char *contents);
int i=0;

int main()
{
	char file_name[25],contents[256];
	FILE *fp;
	printf("Welcome to Lexical Analyzer !!!\n");
	printf("Enter file name:");
	gets(file_name);
	char ch;
	fp=fopen(file_name,"r");
	if(fp == NULL)
	{
		printf("Oops :(\nFile not available\n");
		exit(0);
	}
	else
	{
		while((ch=fgetc(fp)) != EOF)
		{
			if(ch=='\n'||ch=='\t')
				contents[i]=' ';
			else
				contents[i]=ch;
			i++;
		}
	}
	contents[i]='\0';

	

	int tokenstart=0,tokenend=0;
	char tok[10];
	while(tokenend < strlen(contents))
	{
		tokenend++;
		if(contents[tokenend]==' ')
		{
			int g,gg=0;
			for(g=tokenstart;g<=tokenend;g++)
			{
				tok[gg]=contents[g];
				gg++;
			}
			tok[gg]='\0';
			yylex(tok);
			tokenstart=tokenend+1;
			tokenend=tokenend+1;
		}
	}
	
	
	/*int j;
	for(j=0;j<strlen(contents);j++)
	{
		printf("_%c",contents[j]);
	}
	printf("\n%d\n\n",strlen(contents));
	printf("\n%c\n",contents[62]);*/


	//char contents[]="#include<stdio.h> ";
	//yylex(contents);
	
	printf("\n~Done~\n");
	return 0;
}

int isletter(char c)
{
	//int value=(int)c;
	//if((65<= value <=90) || (97<= value <=122))
	if(c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f'||c=='g'||c=='h'||c=='i'||c=='j'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='q'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'||c=='x'||c=='y'||c=='z'||c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'||c=='G'||c=='H'||c=='I'||c=='J'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='Q'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'||c=='X'||c=='Y'||c=='Z')
		return 1;
	else
		return 0;
}

int is_digit(char c)
{
	if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||c=='0')
		return 1;
	else 
		return 0;
}

int fail(int s)
{
	int news;
	switch(s)
	{
		case 0:
			news=9;
			break;
		case 9:
			news=12;
			break;
		case 12:
			news=17;
			break;
		case 14:
			news=19;
			break;
		case 17:
			news=19;
			break;
		case 19:
			news=22;
			break;
		case 22:
			news=37;
			break;
	}
	return news;
}

void yylex(char *contents)
{
	int id=0;
	char ch;
	int state=0;
	while(state >= 0){   //remember to break the while loop if any of the final states is reached!
	
	switch(state)
	{
		case 0:
			ch=contents[id];
			if(ch=='<')
				state=1;
			else if(ch=='=')
				state=5;
			else if(ch=='>')
				state=6;
			else
				state=fail(0);
			break;
		case 1:
			id=id+1;
			ch=contents[id];
			if(ch=='=')
				state=2;
			else if(ch=='>')
				state=3;
			else if(ch==' ')
				state=4;  //remember to retract in state 4
			break;
		case 2:
			printf("\n%s Relational Operator\n",contents);
			state=-1; //set an invalid state to break while loop
			break;
		case 3:
			printf("\n%s Relational Operator\n",contents);
			state=-1;
			break;
		case 4:
			id=id-1; //retracting by 1
			printf("\n%s Relational Operator\n",contents);
			state=-1;
			break;
		case 5:
			printf("\n%s Relational Operator\n",contents);
			state=-1;
			break;
		case 6:
			id=id+1;
			ch=contents[id];
			if(ch=='=')
				state=7;
			else if(ch==' ')
				state=8; //remember to retract in state 8
			break;
		case 7:
			printf("\n%s Relational Operator\n",contents);
			state=-1;
			break;
		case 8:
			id=id-1; //retracting by 1
			printf("\n%s Relational Operator\n",contents);
			state=-1;
			break;
		case 9:
			ch=contents[id];
			if(isletter(ch))
				state=10;
			else
				state=fail(9);
			break;
		case 10:
			id=id+1;
			ch=contents[id];
			if(isletter(ch) || is_digit(ch))
				state=10;
			else if(ch==' ')
				state=11; //remember to retract in state 11
			break;
		case 11:
			id=id-1;
			if(strcmp(contents,"int ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"float ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"char ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"for ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"while ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"if ")==0)
				printf("\n%s Reserved Word\n",contents);
			else if(strcmp(contents,"else ")==0)
				printf("\n%s Reserved Word\n",contents);
			else
				printf("\n%s Identifier\n",contents);
			state=-1;
			break;
		case 12:
			ch=contents[id];
			if(is_digit(ch))
				state=13;
			else
				state=fail(12);
			break;
		case 13:
			id=id+1;
			ch=contents[id];
			if(is_digit(ch))
				state=13;
			else if(ch=='.')
				state=14;
			else if(ch==' ')
				state=16; //remember to retract in state 16
			break;
		case 14:
			id=id+1;
			ch=contents[id];
			if(is_digit(ch))
				state=15;
			else
				state=fail(14); //means error in token
			break;
		case 15:
			id=id+1;
			ch=contents[id];
			if(is_digit(ch))
				state=15;
			else if(ch==' ')
				state=16; //remember to retract in state 16
			break;
		case 16:
			id=id-1;
			printf("\n%s Number(real/integer)\n",contents);
			state=-1;
			break;
		case 17:
			ch=contents[id];
			if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch==';')
				state=18;
			else
				state=fail(17);
			break;
		case 18:
			ch=contents[id];
			if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
				printf("\n%s Arithmetic Operator\n",contents);
			if(ch=='(')
				printf("\n%s Opening Parentheses\n",contents);
			if(ch==')')
				printf("\n%s Closing Parentheses\n",contents);
			if(ch=='{')
				printf("\n%s Opening Curly Braces\n",contents);
			if(ch=='}')
				printf("\n%s Closing Curly Braces\n",contents);
			if(ch==';')
				printf("\n%s Semi-colon\n",contents);
			state=-1;
			break;
		case 19:
			ch=contents[id];
			if(ch=='#')
				state=20;
			else
				state=fail(19);
			break;
		case 20:
			id=id+1;
			ch=contents[id];
			if(isletter(ch) || ch=='.'||ch=='<'||ch=='>')
				state=20;
			else if(ch==' ')
				state=21;
			break;
		case 21:
			id=id-1;
			printf("\n%s Header file\n",contents);
			state=-1;
			break;
		case 22:
			ch=contents[id];
			if(ch=='^')
				state=23;
			else if(ch=='~')
				state=27;
			else if(ch=='!')
				state=24;
			else if(ch=='&')
				state=25;
			else if(ch=='|')
				state=26;
			else
				state=fail(22);
			break;
		case 23:
			id=id+1;
			ch=contents[id];
			if(ch==' ')
				state=28;
			else 
				state=fail(22);
			break;
		case 24:
			id=id+1;
			ch=contents[id];
			if(ch==' ')
				state=29;
			else 
				state=fail(22);
			break;
		case 25:
			id=id+1;
			ch=contents[id];
			if(ch=='&')
				state=30;
			else if(ch==' ')
				state=31;
			else
				state=fail(22);
			break;
		case 26:
			id=id+1;
			ch=contents[id];
			if(ch=='|')
				state=32;
			else if(ch==' ')
				state=33;
			else
				state=fail(22);
			break;
		case 27:
			id=id+1;
			ch=contents[id];
			if(ch==' ')
				state=34;
			else
				state=fail(22);
			break;
		case 28:
			id=id-1;
			printf("\n%s Bitwise XOR\n",contents);
			state=-1;
			break;
		case 29:
			id=id-1;
			printf("\n%s Logical NOT\n",contents);
			state=-1;
			break;
		case 30:
			id=id+1;
			ch=contents[id];
			if(ch==' ')
				state=35;
			else
				state=fail(22);
			break;
		case 31:
			id=id-1;
			printf("\n%s Bitwise AND\n",contents);
			state=-1;
			break;
		case 32:
			id=id+1;
			ch=contents[id];
			if(ch==' ')
				state=36;
			else
				state=fail(22);
			break;
		case 33:
			id=id-1;
			printf("\n%s Bitwise OR\n",contents);
			state=-1;
			break;
		case 34:
			id=id-1;
			printf("\n%s Bitwise NOT\n",contents);
			state=-1;
			break;
		case 35:
			id=id-1;
			printf("\n%s Logical AND\n",contents);
			state=-1;
			break;
		case 36:
			id=id-1;
			printf("\n%s Logical OR\n",contents);
			state=-1;
			break;
		case 37:
			printf("\n%s Unidentified Token!\n",contents);
			state=-1;
			break;
		default:
			break;
	}
	
   }
	
}















