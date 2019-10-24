ALGORITHM:

Step1:  Start the program.

Step2:  Reading an expression .

Step3:  Checking the validating of the given expression according to the rule using yacc.

Step4:  Using expression rule print the result of the given values
Step5:  Stop the program.

PROGRAM:


//Program to recognize a valid arithmetic expression that uses operator +, -, * and /

LEX PART:

%{

    #include "y.tab.h"

%}

%%

[a-zA-Z_][a-zA-Z_0-9]* return id;

[0-9]+(\.[0-9]*)?      return num;

[+/*]                  return op;

.                      return yytext[0];

\n                     return 0;

%%

int yywrap()

{

return 1;

}

YACC PART:

%{

    #include<stdio.h>

    int valid=1;

%}

%token num id op

%%

start : id '=' s ';'

s :     id x

      | num x

      | '-' num x

      | '(' s ')' x

      ;

x :     op s

      | '-' s

      |

      ;

%%

int yyerror()

{

    valid=0;

    printf("\nInvalid expression!\n");

    return 0;

}

int main()

{

    printf("\nEnter the expression:\n");

    yyparse();

    if(valid)

    {

        printf("\nValid expression!\n");

    }

}


1,2 1
-1 2
-1 -1#
0
2
