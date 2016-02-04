#include<stdio.h>
#include"arr_util.h"
#include <stdlib.h>

/*
FAYAZ KHAN
 UIN: 655427236
 
 
 COMPLETE!!
 
 
The funtion prototypes are commented here but they 
 are in arr_util.h ****for the arr_util.h i just typed as is on this
 page and i didn't type anything in the terminal and errors in the
 past was because of the funtions

 
*/
//int is_sorted(int a[], int n);//COMPLETE
/**
 * returns 1 if array a[0..n-1] is sorted in ascending order (technically,
 *   non-descending order).
 * Returns 0 otherwise
 */

//void histogram(unsigned int data[], int n);//COMPLETE
/**
 * displays an ASCII histogram as in HW2, but the number of data points
 *   is n rather than 4.
 *
 * Assumptions/Details:
 *
 *     Each column/bar is labeled with an appropriate capital letter
 *        starting from 'A' and continuing left-to-right.
 *
 *
 *     A histogram is drawn only if n <= 26 -- i.e., only labels
 *	'A'...'Z' are possible.
 *     If n is greater than 26, the function should print an error
 *       message and return.
 *
 *     REMEMBER:  characters also have integer interpretations and
 *         in ASCII, the integer values for 'A'...'Z' are contiguous
 *	  and in increasing order.
 */


//int num_distinct(int a[], int n);//COMPLETE
/**
 * returns the number of distinct values stored in array a.
 *
 * parameters:
 *
 *     a:  array of data
 *     n:  length of array a
 *
 * Examples:
 *
 *    if a = {1, 2, 3}, all three entries are distinct so 3 is returned.
 *
 *    if a = {1, 1, 1, 1, 1}, then only one distinct value (1) so 1 is
 *          returned.
 *
 * Rules:  you may NOT rearrange the array in any way; you may not invoke
 *   any external functions; you may not use any additional arrays.
 *
 */

//void max(unsigned int a[],int n);//This is my own function for the histogram to find the
                       //Number of rows we need



//int same_contents(int a[], int b[], int n);//COMPLETE
/**
 * returns 1 if a[0..n-1] and b[0..n-1] have the same contents;
 *    returns 0 otherwiwse.
 *
 * a[] and b[] "have the same contents" when:
 *
 *      - every integer in a[] is also in b[]
 *      - every integer in b[] is also in a[]
 *      - all such common values appear exactly the same
 *           number of times in both a[] and b[]
 *
 * examples:
 *
 *    a = {1, 2, 3}, b = {2, 3, 4}    NO
 *    a = {1, 2, 3}; b = {2, 3, 1}    YES
 *    a = {1, 2, 2}; b = {2, 2, 1}    YES
 *    a = {1, 2, 2}; b = {2, 1, 1}    NO
 *    a = {1, 1, 2, 2, 2}; b = {2, 1, 2, 1, 2}    YES
 *
 * RULES:  You may NOT re-order the elements of the arrays.
 */


/*SELF NOTE:
  Create a third array of 1 and 0 if already read you can refer to third array and see if 
 there is 1(meaning already used) and 0(means not used)
 */



//void rotate_right(int a[], int n);//COMPLETE

/**
 * rotates contents of array one position to the right.
 *
 * element in last position (index n-1) moves to first position (idx 0).
 *
 * Examples:
 *
 *    {1, 2, 3, 4} rearranged to become {4, 1, 2, 3}
 *
 *    {1, 2, 1, 2} rearranged to become {2, 1, 2, 1}
 *
 * NOTES:
 *
 *    Modifies given array; does not create a second array
 */





int main()
{
    int a[]={1, 2, 3, 4,5,6,7,8,9 };
    int b[]={1, 4, 2, 3,5,6,7,9,8 };
    
    int n=8;
    
 
    printf("\nis_sorted returned:%d\n\n",is_sorted(a,n));
    
    unsigned int data[]={1, 5, 2, 13,1,7,5,2,9 };//unsigned is used for ASCII
    histogram(data, n);
    
    printf("\nnum_distinct returned:%d\n\n",num_distinct(a, n));
    
    printf("same_contents returned:%d\n\n",same_contents(a,b,n));
    
    rotate_right(a, n);
    
}

void histogram(unsigned int data[], int n)
{
    // char CAP[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    char c=65;//this for the ASCII we add this with our n below
    //printf("Char=%c,int=%d\n",c,c);//This is for taking numbers and because of ASCII they are letters
    //Their is a list online and they are bunch of characters
    //http://www.ascii-code.com
    if (n>26||n<0)
    {
        return;
    }
    int i=0,rows;
    rows=data[i];
    
    while (i<=n)
    {
        if (rows<data[i])
        {
            rows=data[i];
        }
       
        i++;
        //printf("Rows=%d\n",rows);
    }
    i=0;
    
    while (rows>0)
    {
        while (i<=n)
        {
            if (data[i]>=rows)
                printf("X");
            else
                printf(" ");
            
            printf(" ");
            i++;
        }
        rows--;
        i=0;
        printf("\n");
    }
    
    while (i<=n*2)
    {
        printf("-");
        i++;
    }
    printf("\n");
    i=0;
    while (i<=n)
    {
        printf("%c ",c+i);
        i++;
    }
    printf("\n");
   
    
}



void rotate_right(int a[], int n)
{
    
    int i=0;
    printf("Rotate_right:\n");
    printf("Before:");
    
    while (i<=n)
    {
        printf("%d ",a[i]);
        i++;
    }
    
    
    int temp_array[n+1];
    
    i=0;
  
    while (i<=n)
    {
        temp_array[i+1]=a[i];
        i++;
    }
    
    i=1;
    
    while (i<=n)
    {
        a[i]=temp_array[i];
        i++;
    }
    
    a[0]=temp_array[n+1];
    
    i=0;
    
    printf("\nAfter: ");
    while (i<=n)
    {
        printf("%d ",a[i]);
        i++;
    }
    
    printf("\n\n");
}

int same_contents(int a[], int b[], int n)
{
    //int check[]={0,0,0,0};
    int i=0;
    int check[n];
    while (i<=n)
    {
        check[i]=0;//Purpose of this while loop is to initialize all of the spots
                   //since our n can be changed this way i used the loop
                   //but if the array was fixed size then you dont need loop
                   //u can write check[3]={0}; //for example
        i++;
    }
    i=0;
    //int check[3]={0};
    //printf(" ",check[n]);//only works if print statement is here
                                 //this will complile either way but if not there acts like no variable
    //check[0]=0;s
    int k=0,j=0;
    
    while (j<=n)
    {
        while (k<=n)
        {
            if (a[j]==b[k]&&check[k]==0)
            {
                check[k]=1;
                //k=n;
                //printf("in check_j==%d and check_k==%d \n",j,k);
                k=n;
            }
            k++;
        }
        j++;
        k=0;
    }
    
    while (i<=n)
    {
        if (check[i]==0)
        {
            return 0;//because the contents are not the same;
        }
        i++;
    }
    return 1;//because the contents are the same

}


int is_sorted(int a[], int n)
{
    //printf("fun this a1==%d\n",a[0]);
    //return b;
    int i=0;
    while (i<=n)
    {
        
    
        if (a[i]>a[i+1])
        {
            return 0;
        }
        i++;
    }
    return 1;
}



int num_distinct(int a[], int n)
{
    //printf("I am in num1!");
    int i=0,j=1;
    
    while (i<=n)
    {
        while (j<=n)
        {
            //printf("I am in num2!");
            if (a[i]==a[j])
            {
                return a[j];
                //printf("I am in num3!");
            }
            j++;
        }
        
        i++;
        j=i+1;
     //printf("I am in num4!%d\n",a[i]);
    }
    return a[i-1];
    
    
}











