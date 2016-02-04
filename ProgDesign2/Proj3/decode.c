#include<stdio.h>
#include"simpleio.h"
#include <ctype.h>

/*
 FAYAZ KHAN
 655427236
 */


//./a.out 123 <cipher.txt>decode.txt

void shuffle(int plainText[],int cipherText[],int n, int seed);

int main(int argc, char *argv[])
{
    int seed=atoi(argv[1]);//we are the taking the second one in the array because first(0) is
    //occupied by ./a.out
    
    srand(seed);
    
    int plainText[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    int plainText2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    //int cipherText[] = {'x', 'p', 'y', 'r', 'b', 'c', 'a', 'z', 'm', 'q', 'k', 'i', 'n', 's', 'o', 'w', 'e', 'l', 'f', 'u', 't', 'd', 'h', 'j', 'v', 'g'};
    
    int cipherText[25];
    shuffle(plainText,cipherText,25,seed);
    int i,c,counter=0;//notice getchar is an integer
    
    while( (c=getchar()) != EOF)//EOF is -1 but it also end the getchar
    {       //the getchar is like a scanf but it brings it in as an integer
        
        //printf("am in in here/n");
        
        i=tolower(c);//this is taking any letters the CAP and making them lower case
        
        
        //printf("cypherText:%d\n",c);
        //b=isalpha(i);
        //putchar(c+rand()%26);
        if (isalpha(i))//isalpha checks if it is a letter
        {
            //putchar(i+rand()%26);//Still have to test
            
            while (i!=cipherText[counter])//this is taking the value of the letter and matching it
            {                             //and taking the slot # and grabing the letter from the second array
                counter++;
            }
            //printf("in space");
            putchar(plainText2[counter]);
            //printf("%c",plainText2[counter]);
        }
        else
        {
            putchar(i);//this is taking as is for punctuation and spaces
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

