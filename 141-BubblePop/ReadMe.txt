I also included a makefile 

bboard.c has all the functions

bboard.h has all the function declarations

bpop.c I am using Dr.Lillis’s file but i added #include <ctype.h> because it kept on
 	giving me a warning  

bpop.c:43:41: warning: implicit declaration of function 'isspace' is invalid in C99 [-Wimplicit-function-declaration]
while(( (ch = fgetc(fptr)) != EOF) && isspace(ch));