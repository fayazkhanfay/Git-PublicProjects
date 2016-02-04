#include<stdio.h>
#include <time.h>
#include "simpleio.h"

void story(char *animals[],int printer,int ZtoN[],int alt);
void ZerotoNumb(int ZtoN[],int i);
int Hist_num(int ZtoN[],int j,int Rnum,int i);

/*
 Main lesson of recursion it just does not go back and forward
 
 it goes (back+dowm)+(back+down) etc... when you do the return 
 where ever you entered when you enter return it will go back one and then down
 
 OR
 
 PUT A RETURN BELOW EACH OF THE FUNCTION CALL
 
 LOOK IN Sidra.c for additional comments
 
 
 */


int main()
{
    char *animals[]={"child","Frog", "Cat", "Dog", "Horse", "Snake", "Eagle", "Bear", "Weasel"};
    srand( (unsigned)time(NULL));
   
    int printer=0;
    
    int ZtoN[9]={0};//start off as zero but loaded with numbers in each index
    int i =1;
    ZerotoNumb(ZtoN,i);
    int alt=1;//this to switch the story to start working back words
    story(animals,printer,ZtoN,alt);
}


void ZerotoNumb(int ZtoN[],int i)
{
    
    if(i==9)
    {
        return;
    }
    
    int Rnum=rand()%9;//the max number will be 8
   
    int j=0;
    ;
    if (Hist_num(ZtoN,j,Rnum,i)==1)
    {
        
        ZtoN[i]=Rnum;
        //printf("ZtoN==%i,,i==%i\n",ZtoN[i],i);
        ZerotoNumb(ZtoN,i+1);
    }
    else
    {
        ZerotoNumb(ZtoN,i);
    }
   
}


int Hist_num(int ZtoN[],int j,int Rnum,int i)
{
    //printf("hisT_num_j==%i,i==%i,rnum==%i\n",j,i,Rnum);
    //printf("ZtoN==%i\n",ZtoN[j]);
    //return 1;
    if (j==i)
    {
        //printf("above return_j==%i_i==%i\n",j,i);
        return 1;
    }
    
    if(Rnum==ZtoN[j])
    {
        //printf("IN RNUM");
        return 0;
    }
    else
    {
     return Hist_num(ZtoN,j+1,Rnum,i);//This is the important part
        /* Before I had the return below, understand when it is returned it will 
         print the below statement so that is why i made it return itself*/
    }
    
    //printf("below_Hist_num_j==%i\n",j);

    
}

void story(char *animals[],int printer,int ZtoN[],int alt)
{
    
   
    switch (printer)
    {
        case 0:
            if (alt==-1)
            {
                printf("...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                return;
            }
            else
            {
                printf("\nA %s couldn't sleep, so her mother told a story about a little %s,\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 1:
            if (alt==-1)
            {
                printf("\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\twho couldn't sleep, so the %s%i's mother told a story about a little %s,\n",animals[ZtoN[printer]],alt,animals[ZtoN[printer+1]]);
                break;
            }
        case 2:
            if (alt==-1)
            {
                printf("\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 3:
            if (alt==-1)
            {
                printf("\t\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\t\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 4:
            if (alt==-1)
            {
                printf("\t\t\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\t\t\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 5:
            if (alt==-1)
            {
                printf("\t\t\t\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\t\t\t\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 6:
            if (alt==-1)
            {
                printf("\t\t\t\t\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
            }
            else
            {
                printf("\t\t\t\t\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                break;
            }
        case 7:
            if (alt==-1)
            {
                
                printf("\t\t\t\t\t\t\t...and the little %s fell asleep\n",animals[ZtoN[printer]]);
                break;
                //return;
                
            }
            else
            {
                printf("\t\t\t\t\t\t\twho couldn't sleep, so the %s's mother told a story about a little %s\n",animals[ZtoN[printer]],animals[ZtoN[printer+1]]);
                printf("\t\t\t\t\t\t\t\t...who fell asleep.\n");
                break;
            }
        default:
            printf("ERROR,printer==%i,alt==%i\n",printer,alt);
            break;
    }
    
    
    if (printer==7&&alt==1)
    {
        //printf("\ninside of printer\n");
        alt=-1;
        story(animals,printer,ZtoN,alt);
    }
    else
    {
        story(animals,printer+alt,ZtoN,alt);
        return;
        printf("below_function");
    }
    
    //story(animals,printer+alt,ZtoN,alt);
    
  
}
