
// file:  scheck_tst.c
// Description:
//     primitive program exercising/testing the scheck
//     sudoku checker function
//
// Disclaimer:  only for illustration purposes.  Does not do
//     robust testing by any means.
//     Merely offered as a starting point.

#include "scheck.h"//it is linked
#include <stdio.h>

//int scheck(int board[9][9]);//this is from scheck.h//COMMENT THIS LATER

/*You can have multiple same copies of function prototype with erro*/

//scheck it just goes into the function and then goes into all the other functions

/*
 IN scheck.c
 int All_Row_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
 
 */

/*
 All_Row_V this check the row by using Num_distinct from previous HW
 their are 3 arrays one full of zero's second 1-9 and the third is the row.
 everytime their is a match it marks it in the third array as a 1
 the final check to see the array full of zero's is now full of ones
 
 Does not send multiple errors if error found it gets out
 
 */
/*
 IN scheck.c
 
 int All_Column_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
 */
/*
 exact same concept All_Row_V
 */


/*
 IN scheck.c
 void Zero_Reset(int Zero_Check[]);
 */

/*
 Zero_reset all this does it take our array that is now full of ones and
 makes them into 0's but they have to be read in individully thats the reason for the loop
 */

/*
 IN scheck.c
 int All_Box_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
 */

/*
 this uses the num_distinct concept again but we use the switch to specify exactly
 which box to look at because the puzzle is split into 9 boxes
 */


int main() {
    int nviolations;
    //Nothing has been modified in main()
    
    int ok[][9] =  {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {7, 8, 9, 1, 2, 3, 4, 5, 6}, //{7, 8, 9, 1, 2, 3, 4, 5, 6},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        //{1, 2, 3, 4, 5, 6, 7, 8, 9}//get rid of this one
        
    };
    
    int bad[][9] =  {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},//1,2
        {7, 8, 9, 1, 2, 3, 4, 5, 6}, //{7, 8, 9, 1, 2, 3, 4, 5, 6},
        {4, 5, 6, 7, 8, 9, 6, 2, 3},//{4, 5, 6, 7, 8, 9, 6, 2, 3}
        {9, 1, 2, 3, 4, 5, 1, 7, 8},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {2, 3, 4, 5, 6, 7, 8, 9, 1}
    };
    
    int Really_bad[][9] =
    {
        {1, 5, 3, 4, 5, 6, 7, 8, 9},//1,2
        {7, 8, 9, 1, 3, 3, 4, 5, 6}, //{7, 8, 9, 1, 2, 3, 4, 5, 6},
        {4, 5, 6, 7, 8, 9, 6, 2, 3},//{4, 5, 6, 7, 8, 9, 6, 2, 3}
        {9, 1, 2, 3, 4, 5, 1, 7, 8},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {2, 3, 4, 5, 6, 7, 8, 9, 1}
        
        
    };
    // printf("test==%i\n",ok[][]);
    
    
    
    nviolations = scheck(bad);
    
    if(nviolations != 0)
        printf("FAILED:  expected 0 violations; %i reported\n",
               nviolations);
    else
        printf("PASSED: %i violations reported\n", nviolations);
    
}

/*
 BIG NOTE dont send every error
 look at assignment
 ex:Row 3: two 1s, missing a 6
 
 that is 1 violation, so if you get one error for
 that error send it.
 
 CONCLUSION:
 Coloumn_V and All_Coloumn_V if both in violoation
 this is only one error for that coloumn
 *************
 27 units=====27 possible errors
 
 **************
 GRAB same_contents function from previous hw arr_util.c from HW3
 
 */

/*
 IN scheck.c
 void Zero_Reset(int Zero_Check[])
 {
 int i=0;
 while (i<9)
 {
 Zero_Check[i]=0;//This has to be manually done if not
 //kept on giving error of expecrted expression
 i++;
 }
 //return Zero_Check;
 }*/

/*int scheck(int board[9][9])
 {
 //printf("In function==%i\n",board[3][3]);
 //This goes to the individule functions
 int RC =0;
 
 int errors=0;
 int All_Check[]={1,2,3,4,5,6,7,8,9};//This is our Array to check for same content
 int Zero_Check[9];//This is our initial array full of zero's which will be loaded later
 
 int n=8;//this prevents the array going out of bounds
 while(RC<9)//Row and coloum this specify will Row or coloumn
 {
 Zero_Reset(Zero_Check);//This load and resets the array to zero
 errors =errors+ All_Row_V(board,RC,All_Check,Zero_Check,n);//explanation at the top
 
 Zero_Reset(Zero_Check);//This load and resets the array to zero
 
 errors=errors+ All_Column_V(board,RC,All_Check,Zero_Check,n);
 Zero_Reset(Zero_Check);
 
 errors= errors+ All_Box_V(board,RC,All_Check,Zero_Check,n);
 
 RC++;
 
 }
 return errors;
 }*/

/*
 int All_Box_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n)
 {//this check if #'s from 0-9 in box
 int i=0,k=0,j=0,Row_E=0,Col_E=0,temp_k;
 // printf("ZeroCheckallbox==%i\n",Zero_Check[k]);
 
 // With the switch I am trying to set row and column pending on the RC
 //if possible to throw into function and get multiple values back but not necessary
 //you can also put each think in an array and bring it back that way
 
 switch (RC)
 {
 case 0:
 j=0;
 k=0;
 temp_k=k;
 //n=3
 Row_E=2;
 Col_E=2;
 break;
 
 case 1:
 j=0;
 k=3;
 temp_k=k;
 //n=3
 Row_E=2;
 Col_E=5;
 break;
 
 case 2:
 j=0;
 k=6;
 temp_k=k;
 //n=3
 Row_E=2;
 Col_E=8;
 break;
 
 case 3:
 j=3;
 k=0;
 temp_k=k;
 //n=3
 Row_E=5;
 Col_E=2;
 break;
 
 case 4:
 j=3;
 k=3;
 temp_k=k;
 //n=3
 Row_E=5;
 Col_E=5;
 break;
 
 case 5:
 j=3;
 k=6;
 temp_k=k;
 //n=3
 Row_E=5;
 Col_E=8;
 break;
 
 case 6:
 j=6;
 k=0;
 temp_k=k;
 //n=3
 Row_E=8;
 Col_E=2;
 break;
 
 case 7:
 j=6;
 k=3;
 temp_k=k;
 //n=3
 Row_E=8;
 Col_E=5;
 break;
 
 case 8:
 j=6;
 k=5;
 temp_k=k;
 //n=3
 Row_E=8;
 Col_E=8;
 break;
 
 default:
 break;
 }
 
 while (j<=Row_E)
 {
 while (k<=Col_E&&i<9)
 {
 if (board[j][k]==All_Check[i]&&Zero_Check[i]==0)//May not be correct
 {
 Zero_Check[i]=1;
 //k=n;
 //printf("board==%i and All_check==%i and Zero_CHeck==%i and k==%i \n",board[j][k],All_Check[i],Zero_Check[i],i);
 
 }
 
 if (i==8)
 {
 i=-1;
 k++;
 }
 i++;
 //k++;
 }
 j++;
 k=temp_k;//Verify this
 i=0;
 }
 
 while (i<=n)
 {
 if (Zero_Check[i]==0)
 {
 printf("Error in Box:%i\n",RC+1);
 
 return 1;//Because the content is not the same meaning 1-9 a number is missing
 
 }
 i++;
 }
 return 0; //Numbers 1-9 are present
 
 }
 */

/*
 int All_Column_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n)
 {//this check if #'s from 0-9 in column
 int i=0,k=0,j=0;
 //printf("ZeroCheck==%i\n",Zero_Check[k]);
 while (j<=n)
 {
 while (k<=n)
 {
 if (board[j][RC]==All_Check[k]&&Zero_Check[k]==0)//May not be correct
 {
 Zero_Check[k]=1;
 //k=n;
 //printf("board==%i and All_check==%i and Zero_CHeck==%i and k==%i \n",board[R][j],All_Check[k],Zero_Check[k],k);
 k=n;
 }
 k++;
 }
 j++;
 k=0;
 }
 
 while (i<=n)
 {
 if (Zero_Check[i]==0)
 {
 printf("Error in Column:%i\n",RC);
 
 return 1;//Because the content is not the same meaning 1-9 a number is missing
 
 }
 i++;
 }
 return 0; //Numbers 1-9 are present
 
 }
 */


/*int All_Row_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n)
 {
 //this check if #'s from 0-9 in row
 //Put in same_contents here from previous hw
 //have a second array checking 1-9 checking if they have the same content
 
 int i=0,k=0,j=0;
 //printf("ZeroCheck==%i\n",Zero_Check[k]);
 while (j<=n)
 {
 while (k<=n)
 {
 if (board[RC][j]==All_Check[k]&&Zero_Check[k]==0)//May not be correct
 {
 Zero_Check[k]=1;
 //k=n;
 //printf("board==%i and All_check==%i and Zero_CHeck==%i and k==%i \n",board[R][j],All_Check[k],Zero_Check[k],k);
 k=n;
 }
 k++;
 }
 j++;
 k=0;
 }
 
 while (i<=n)
 {
 if (Zero_Check[i]==0)
 {
 printf("Error in Row:%i\n",RC);
 return 1;//Because the content is not the same meaning 1-9 a number is missing
 
 }
 i++;
 }
 return 0; //Numbers 1-9 are present
 }
 
 
 */







