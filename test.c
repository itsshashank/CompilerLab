#include <stdio.h>
#include <stdlib.h>

/* Functions */
void check_comment (char) ;  // checks for both types of comments, then passes on control to below comments
void block_comment () ;   //  handles block or multiline comments
void single_comment () ;   // handles single line comments

/* 2 file pointers - 1st is for the file in which we check for comments,
and 2nd is the file in which we copy the code after removing comments  */
FILE *fp , *fp2;

int main(void)
{
    char c;
    fp = fopen ("hello.c","r") ;   // open the first file in read mode
    fp2 = fopen ("mynewfile.txt","w") ;    // open the second file in write mode

    while((c=fgetc(fp))!=EOF)       // read the file character by character
        check_comment(c);   // check for each character if it seems like the beginning of a comment

     //  close both the files at the end of the program
    fclose(fp);
    fclose(fp2);

    return 0;
}


//handles both types of comments
void check_comment(char c)
{
    char d;

    if( c == '/')   // if the character starts with '/', it 'could' be a comment
    {
        if((d=fgetc(fp))=='*')   // if the next character we read is '*', it is the beginning of multiblock comment
         block_comment();  // pass control to function that handles multiblock comments

        else if( d == '/')   // else if the next character we read is '/', it is the beginning of single line comment
        {
          single_comment();// pass control to function that handles single line comment

        }
        else
        {
            // if both the cases fail, it is not a comment, so we add the character as it is in the new file.
            fputc(c,fp2);
            fputc(d,fp2);
        }
    }

    // again, if all above fails, we add the character as it is in the new file.
    else
        fputc(c,fp2);
}


// function that handles block comments
void block_comment()
{

 char d,e;

    while((d=fgetc(fp))!=EOF)   // the block comment has started, read the character by character
    {
    /* keep reading the characters and do nothing,
    as they do not have to be copied into the new file (we are removing the comments)
    */
        if(d=='*')    // if the comment 'seems' like ending
        {
            e=fgetc(fp);  // check if it actually ends (block comments end with '*/')

            if(e=='/')  // if the comment 'has' ended, return from the function
                return;
        }
   }

}


// function that handles single line comments
void single_comment()
{
 char d,e;

    while((d=fgetc(fp))!=EOF)  // the single line comment has started, read the character by character
    {
    /* keep reading the characters and do nothing,
    as they do not have to be copied into the new file (we are removing the comments)
    */
        if(d=='\n')   // check if the comment ends (single comments end with '\n', or newline)
            return;  // if the comment 'has' ended, return from the function

    }

}