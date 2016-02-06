#include <stdio.h>
#include <stdlib.h>
#include "scheck.h"

/*int All_Row_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
int All_Column_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
void Zero_Reset(int Zero_Check[]);
int All_Box_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n);
int scheck(int board[9][9]);
*/
//lknlanf

int All_Row_V(int board[9][9],int RC,int All_Check[],int Zero_Check[],int n)
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
            printf("Error inlknkl Row:%i\n",RC);
            return 1;//Because the content is not the same meaning 1-9 a number is missing
            
        }
        i++;
    }
    return 0; //Numbers 1-9 are present
}

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
}


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

int scheck(int board[9][9])
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
}


