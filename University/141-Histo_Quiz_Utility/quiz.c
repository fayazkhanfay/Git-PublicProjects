#include <stdio.h>
#include <time.h>// no such file or directory !!!!ASK!!!!
#include"simpleio.h"// DONT FORGET THE QUOTATIONS

/*to use simpleio.h
 in the terminal type 
 gcc quiz.c -o quiz simpleio.o
 ./quiz
 
 */
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

//Fayaz Khan
//HW2 Quiz
//UIN: 655427236

int main() 
{

    //get_int();
    
    srand( (unsigned)time(NULL));//This works by taking the time then the rand takes and generates another number
    int a=rand()%101;//if you use this without srand it will generate the same random number
    int b=rand()%101;//this was not working without the simpleio.h and time.h look at the top
    
    //printf("this is a====%d, b==%d",a,b);
    
    //int a=5;// this is suppose to be rand or srand
    //int b=5;//same like above
    
    int result,user_result,wrong=0,first=0;
    

  
while(first==0)
{
//int a=rand() %101;//this is suppose to be srand but we need header file

    while ( first<1||first>4)
    {
     printf("\nQuiz Options:\n");
     printf("1. Addition problem\n");
     printf("2. Subtraction problem\n");
     printf("3. multiplication problem\n");
     printf("4. Quit\n");
        
     printf("\nPlease enter quiz option:");
     scanf("%d",&first);
     
        if (first<1||first>4)
        {
         printf("ERROR\n");
        }
        
    
    }

    
  
    //first=get_int();



    switch (first)
    {
        case 1:
            printf("What is %d+%d=",a,b);
            result=a+b;
            scanf("%d",&user_result);
            while (result!=user_result&&wrong<5)
            {
                printf("I am sorry the Answer is incorrect.Try again\n");
                scanf("%d",&user_result);
                wrong++;
                if (wrong==5)
                {
                    printf("The correct answer is %d\n",result);
                    first=0;
                }
            }
            if (result==user_result)
            {
                printf("\nCongrats! Answer is correct\n");
                first=0;
            }
            
            
            break;
        case 2:
            printf("What is %d-%d=",a,b);
            result=a-b;
            scanf("%d",&user_result);
            while (result!=user_result&&wrong<5)
            {
                printf("I am sorry the Answer is incorrect.Try again\n");
                scanf("%d",&user_result);
                wrong++;
                if (wrong==5)
                {
                    printf("The correct answer is %d\n",result);
                    first=0;
                }
            }
            if (result==user_result)
            {
                printf("\nCongrats! Answer is correct\n");
                first=0;
            }
            break;
        case 3:
            printf("What is %d X %d=",a,b);
            result=a*b;
            scanf("%d",&user_result);
            while (result!=user_result&&wrong<5)
            {
                printf("I am sorry the Answer is incorrect.Try again\n");
                scanf("%d",&user_result);
                wrong++;
                if (wrong==5)
                {
                    printf("The correct answer is %d\n",result);
                    first=0;
                }
            }
            if (result==user_result)
            {
                printf("\nCongrats! Answer is correct\n");
                first=0;
            }
            break;
        case 4:
            printf("Quiting\n");
            break;
        default:
            printf("Error in switch\n");
            break;
    }
   
}

}
