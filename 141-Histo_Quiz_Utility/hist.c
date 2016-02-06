#include <stdio.h>
//Fayaz Khan
//HW2 Histogram 
//UIN: 655427236

/*Asking user to input 4 values and create a histogram*/

/*
 In our make file:
 Big note hit tab for new line, dont hit space bar
 
 simpleio.o: simpleio.h simpleio.c
	gcc -c simpleio.c
 
 quiz: quiz.c simpleio.o
	gcc -o quiz quiz.c simpleio.o
 
 hist: hist.c
	gcc -o hist hist.c
 
 util.o: util.h util.c
	gcc -c util.c
 
 util_tst: util_tst.c util.o
	make util.o
	gcc -o util_tst util_tst.c util.o

 */
int main() 
{
 int A=-1,B=-1,C=-1,D=-1,Rows,i;
 
//printf("jygyguyEnter values for A,B,C and D\n");
 //scanf("%d,%d,%d,%d",&A,&B,&C,&D);
// printf("A=%d,B=%d,C=%d,D=%d\n",A,B,C,D);
while(A<0)
 {
  printf("Enter A:");
  scanf("%d",&A);
  if(A<0)
   printf("only non-negative number\n");  
 }

while(B<0)
 {
  printf("Enter B:");
  scanf("%d",&B);
  if(B<0)
   printf("only non-negative number\n");
 }

if(A>B)
 Rows=A;
 else
 Rows=B;

//printf("Rows===%d",Rows);

while(C<0)
 {
  printf("Enter C:");
  scanf("%d",&C);
  if(C<0)
   printf("only non-negative number\n");
 }

if(C>Rows)
 Rows=C;

while(D<0)
 {
  printf("Enter D:");
  scanf("%d",&D);
  if(D<0)
   printf("only non-negative number\n");
 }

if(D>Rows)
 Rows=D;

while(Rows>0)
 {
  if(A>=Rows)
   printf("X");
   else
   printf(" ");

   printf(" ");

  if(B>=Rows)
   printf("X");
   else
   printf(" ");

   printf(" ");

  if(C>=Rows)
   printf("X");
   else
   printf(" ");

   printf(" ");

  if(D>=Rows)
   printf("X");
   else
   printf(" ");

   printf("\n");

 // printf("line %d\n",i);
  Rows--;
 }
printf("--------\n");
printf("A B C D \n");
















}
