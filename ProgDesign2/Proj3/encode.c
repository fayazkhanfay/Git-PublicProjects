#include<stdio.h>
#include"simpleio.h"
#include <ctype.h>

//Be sure to have simpleio.h in the same directory just copy and paste the
//entire file

/*
 FAYAZ KHAN
 655427236
 */

/****NOTES ARE IN decode.c *****/

/*
 In this assigments we have to take a message(msg.txt) and encode it(cipher.txt) and
 then decode it(decode.c) the message will be reveiled in decode.txt
 
 The user enter sort of password after ./a.out that is the seed for the
 srand
 
 */



//./a.out 1234 <msg.txt //if no space between # and < will give error bad file decryptor

//./a.out 1234 <msg.txt>cipher.txt

//We dont have to press control+d to end when coming from a text file
void shuffle(int plainText[],int cipherText[],int n, int seed);


int main(int argc, char *argv[])
{
    int seed=atoi(argv[1]);
    //srand(seed);
    
    int plainText[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    int plainText2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    int cipherText[25];
    
    shuffle(plainText,cipherText,25,seed);
    
    int f=0;
    /*while(f<26)
     {
     //putchar(cipherText[f]);
     printf("cipher_text:=%c\n",cipherText[f]);
     f++;
     }*/
    
    
    // int cipherText[] = {'x', 'p', 'y', 'r', 'b', 'c', 'a', 'z', 'm', 'q', 'k', 'i', 'n', 's', 'o', 'w', 'e', 'l', 'f', 'u', 't', 'd', 'h', 'j', 'v', 'g'};
    
    //printf("seed:%d",seed);
    int i,c,counter=0;
    //printf("plainText:%d\n",plainText[0]);
    
    while( (c=getchar()) != EOF)
    {
        //printf("am in in here/n");
        i=tolower(c);
        //printf("cypherText:%d\n",c);
        //b=isalpha(i);
        //putchar(c+rand()%26);
        if (isalpha(i))
        {
            //putchar(i+rand()%26);//Still have to test
            
            while (i!=plainText2[counter])
            {
                counter++;
            }
            //printf("in space");
            putchar(cipherText[counter]);
        }
        else
        {
            putchar(i);
        }
        counter=0;
    }
    printf("\n");
}

void shuffle(int plainText[],int cipherText[] ,int n,int seed)
{
    srand(seed);
    int i=0,g=0;
    
    while (1)
    {
        
        i=rand()%26;
        if (plainText[i]!=0)
        {
            cipherText[g]=plainText[i];
            plainText[i]=0;
            g++;
        }
        
        i=0;
        int total=0;
        while(i<n&&total==0)
        {
            total=total+plainText[i];
            //printf("plainText_value:%d==spot=%d\n",plainText[i],i);
            i++;
        }
        i=0;
        
        if(total==0)
            return;
        total=0;
    }
}





