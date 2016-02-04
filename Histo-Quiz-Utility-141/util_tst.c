
#include <stdio.h>
#include "util.h"// Consider this almost like a text file that why for the quotations
//#include "util.c"// NEVER include util.c you will get a duplicate error
                   //
/*
 util.h:
 I just typed it in and it started working. 
 
 util.c:
 We first to make that util.c into util.o and then link them 
 step 1 :
 gcc -c util.c 
 //this will give util.o
 
 step 2:
 //We have to link util.o to this file (util_tst.c)
 gcc util_tst.c util.o
 
 Step 3:
 We have to make a make file 
 
 */



//Ask why <   > vs "   " for the #include !!!!!!


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

/*
 Self note:
 The function proto and functions are commented because they are in
 the include files. I put them here initially to work out problems here on one script
 then seperated them later i copied and pasted the the bottom portion into util.c 
 and I commented everything below ---------
 
 */

//----------------------
/*
int median3(int,int,int);
double abs_diff(double,double);
unsigned  int sqrt_floor(unsigned int ); //This portion is the util.h. Dont modify util.h
int num_ones(unsigned int );//Later on comment this
 */
//------------------
int main()
{
    
int tst_num=1;
int npassed=0;
int nfailed=0;


    //printf("kjdfkshwkj");
    
  if(abs_diff(5.0, 3.0) != 2.0)//COMPLETED
  {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else
  {
	npassed++;
  }
  tst_num++;

   
  if(median3(1, 2, 3) != 2)//COMPLETED
  {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else
  {
	npassed++;
  }
  tst_num++;

  if(sqrt_floor(4) != 2)//COMPLETED
  {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else
  {
	npassed++;
  }
  tst_num++;

  if(num_ones(2) != 1)//COMPLETED
  {
	printf("test %i failed\n", tst_num);
	nfailed++;
  }
  else
  {
   npassed++;
  }

  printf("num_tests:     %i\n", tst_num);
  printf("num_passed:    %i\n", npassed);
  printf("num_failed:    %i\n", nfailed);


}


//-----------------------------------
//below this is util.c


//THE BELOW HAS BEEN COPY AND PASTED IN TO util.c
//Be sure to comment it all bottom

/**
 * function:  abs_diff(x,y)
 *
 * returns |x-y|
 */
/*double abs_diff(double x, double y)
{
    double temp=x-y;
    if (temp<0)
    {
        temp=temp*-1;//the purpose of this if the subtraction gave us a neg it becomes positve
    }
    
    return temp;
    
}
*/

/**
 * function:  median3(a,b,c)
 *
 * returns median ("middle value") among a, b and c.
 */

/*int median3(int a, int b, int c)
{
    int median_M;//this the median
    
    if (a>b)
    {
        median_M=a;
        //median_L=b;
    }
    else
    {
        median_M=b;
        //median_L=a;
    }
    if (median_M<=c)
    {
        //printf("median function==%d",median_M);
      return median_M;
    }
    else
    {
        //printf("median c function==%d",c);
        return c;
    }
    
}
*/

/**
 * function:  sqrt_floor(n)
 *
 * returns the "largest integer less than or equal to sqrt(n)"
 *
 * Examples:
 *
 *       n       value-returned
 *
 *       5            2
 *       4            2
 *       10           3
 *       40           6
 *       44           6
 *
 * Note:  your implementation must be self-contained -- i.e., you can't
 *        call any library functions (like the math library's sqrt function!).
 */
/*unsigned  int sqrt_floor(unsigned int n)
{
    int i=1,temp_sqrt=0;
    
    while (temp_sqrt<=n)
    {
     temp_sqrt=i*i;
      
        if(temp_sqrt>=n)
          return i;
        i++;
    }
    return i;
}
*/
/**
 * function:  num_ones(n)
 *
 * returns the number of 1s in the binary representation of n.
 *
 * Examples:
 *
 *     The binary representation of 5 is 101; so num_ones(5) would report 2
 *
 *     num_ones(32) would report 1
 *
 *     num_ones(15) is 4    (binary representation:  1111)
 *
 *  Notes:  n is unsigned so
 *
 */
/*int num_ones(unsigned int n)
{//even=0, odd=1
    
    int i=0;
   
    while (n>0)
    {
        if (n%2!=0)
        {
            i++;
        }
        n=n/2;
    }
    return i;
    
}*/




