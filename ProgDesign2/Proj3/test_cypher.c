#include<stdio.h>
#include"simpleio.h"
#include <ctype.h>


//int main(int argc, char *argv[])
int main(int argc, char *argv[])
{
    srand(2345);//This is where the encode/decode number goes
    //int x=atoi(argv[1]);
    int g=0;
    
    while (1)
    {
        int x=rand()%27;
        if (x==26||x==0)
        {
            
        
        printf("x:==%d",x);
        }
        g++;
    }
    
    //printf("srand test::%d",x);
    int a[]={'a'};
    //printf("a=:%c",a[0]);
    int f[]={'f'};
    int c;
    /*if ((c=getchar())=='a') {
        putchar(f[0]);
    }*/
    
    //int d= 'b';
    //char a = d + rand()%26;
    //printf("a=%c \n",a);
    
    int i,b;
    
    /*(for(i=0; i<argc; i++)
    {
        printf(" argv[%i]:%s\n",i,argv[i]);
    }*/
    
    //i= tolower('k');
    
    //printf("i==%c",i);
    //getchar("hello");
    //int c;
    /*while (<#condition#>) {
        <#statements#>
    }*/
    
    i=atoi("n");
    //printf("i=%d",i);
    
    //c=getchar();//this like a scanf for input
    //putchar(c);//like a printf but our c is
    //printf("c==%c",c);
   /* while( (c=getchar()) != EOF)
    {
     //printf("am in in here/n");
        i=tolower(c);
        //b=isalpha(i);
        //putchar(c+rand()%26);
        if (isalpha(i))
        {
            putchar(i+rand()%26);
            //printf("in space");
        }
        else
        {
        putchar(i);
        }
    }*/
    
    
}