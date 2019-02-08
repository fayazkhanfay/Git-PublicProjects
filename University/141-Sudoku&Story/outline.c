#include <stdio.h>
#include<stdlib.h>

/*
 Fayaz Khan
 655427236
 */

void outline(int Dep, int Wid, int Cur_D, char buf [100])
{
    char buffer[100];
    int i;
    int Cur_W=0;
    if (Cur_D==1)
    {
        while(Cur_W<Wid)
        {
            sprintf(buffer,"Section %d",Cur_W+1);
            printf("%s\n",buffer);
            if(Cur_D != Dep)
            {
                outline(Dep,Wid,Cur_D+1,buffer);
            }
            Cur_W++;
        }
    }
    else
    {
        while(Cur_W < Wid)
        {
            if(Cur_D % 2 != 0)
            {
                sprintf(buffer,"%s.%d",buf ,Cur_W+1);
            }
            else
            {
                sprintf(buffer,"%s.%c",buf ,65 + Cur_W);
            }
            for(i =0; i<Cur_D; i++)
            {
                printf("   ");
            }
            printf("%s\n",buffer);
            if(Cur_D != Dep)
            {
                outline(Dep,Wid,Cur_D+1,buffer);
            }
            Cur_W++;
        }
    }
}

int main(int argc, char *argv[])
{
    int Dep, Wid;
    Dep=atoi(argv[1]);
    Wid=atoi(argv[2]);
    outline(Dep, Wid, 1, " ");
}



