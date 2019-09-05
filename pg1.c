#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fp, *fp2;
void block_comment()
{
	char d, e;

	while ((d = fgetc(fp)) != EOF)
	{
		if (d == '*')
		{
			e = fgetc(fp);
			if (e == '/')
				return;
		}
	}
}
void single_comment()
{
	char d, e;

	while ((d = fgetc(fp)) != EOF) {
		if (d == '\n')
			return;
	}
}
void check_comment(char c)
{
	char d;
	if (c == '#') // remove headerfiles also
		single_comment();
	else if (c == '/')
	{
		if ((d = fgetc(fp)) == '*')
			block_comment();
		else if (d == '/')
		{
			single_comment();
		}
		else
		{
			fputc(c, fp2);
			fputc(d, fp2);
		}
	}
	else
		fputc(c, fp2);
}
char *removeCom(char *name)
{
	char c;
	fp = fopen(name, "r");
	fp2 = fopen("rowc", "w");
	while ((c = fgetc(fp)) != EOF)
		check_comment(c);
	fclose(fp);
	fclose(fp2);
	return "rowc";
}

char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
						 "do", "double", "else", "enum", "extern", "float", "for", "goto",
						 "if", "int", "long", "register", "return", "short", "signed",
						 "sizeof", "static", "struct", "switch", "typedef", "union",
						 "unsigned", "void", "volatile", "while"};
int validIdentifier(char *str)
{
	if (isalpha(str[0]) || str[0] == '_')
		return 1;
	return 0;
}
int isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=' || ch == '%')
		return 1;
	return 0;
}
int isDelimiter(char ch)
{
	if (ch == ' ' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '"')
		return 1;
	return 0;
}
int isInteger(char* str) 
{ 
	int i, len = strlen(str); 
	if (len == 0) 
		return 0; 
	for (i = 0; i < len; i++) { 
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)) 
			return 0; 
	} 
	return 1; 
} 
void main(int argv, char *argc[])
{
	FILE *f1, *f2;
	char c, str[10];
	int lineno = 1, num = 0, i = 0,f=0;
	f1 = fopen(removeCom(argc[1]), "r");
	while ((c = getc(f1)) != EOF) // TO READ THE GIVEN FILE
	{	
		if(c== '"'){
		while ((c = getc(f1))!='"')
		{
			printf("%c",c);
		}
		printf(" is a string\n");
		}
		if (isalnum(c)) // TO RECOGNIZE KEYWORDS AND IDENTIFIERS
		{
			checkid:
			str[i++] = c;
			c = getc(f1);
			while (isdigit(c) || isalpha(c) || c == '_' || c == '$' || c == '.')
			{
				str[i++] = c;
				c = getc(f1);
			}
			str[i++] = '\0';
			if(isInteger(str)==1){
					printf("%s is a number\n",str);
					ungetc(c, f1);
					i = 0;
					continue;
					}
			for (int i = 0; i < 32; i++)
			{
			 	if (strcmp(str, keywords[i]) == 0)
				{
					printf("%s is a Keyword\n", str);
					break;
				}
				else if (i == 31)
					if (validIdentifier(str) == 1)
						printf("%s is a identifier\n", str);
					else
						printf("%s is not a valid identifier\n", str);
			}
			ungetc(c, f1);
			i = 0;
		}
		else if (c == ' ' || c == '\t') // TO IGNORE THE SPACE
			;
		else if (c == '\n') // TO COUNT LINE NUMBER
			lineno++;
		else if (isOperator(c) == 1)
			printf("%c is an operator\n", c);
		else if (isDelimiter(c) == 0 && !isspace(c)) // TO FIND SPECIAL SYMBOL
			printf("%c is a special symbol\n", c);
	}
	printf("Total no. of lines are: %d\n", lineno);
	fclose(f1);
}
