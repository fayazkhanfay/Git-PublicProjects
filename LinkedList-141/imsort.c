#include<stdio.h>
#include<stdlib.h>
#include "list.h"

void Read_Add(LIST *l, LIST* Add[]);

int main()
{
    int i;
    int count =0;
    LIST *lst1;
    lst1 = lst_create();
    while(scanf("%i",&i)!=EOF)
    {
        //scanf("%i",&i);
        lst_push_back(lst1, i);
        printf("lkvlkj::%i\n",i);
        count++;
    }
    
    lst_sanity1(lst1);
    lst_sanity2(lst1);
    lst_sanity3(lst1);
    
    printf("lst_len(lst1) : %i\n", lst_len(lst1));
    printf("lst1 contents: ");
    lst_print(lst1);
    LIST* Add[count];
    
    printf("\nREAD ADD\n");
    Read_Add(lst1, Add);
    
    //LIST* p= lst1;

    //printf("uhsfh%i",p->val);
    
}


