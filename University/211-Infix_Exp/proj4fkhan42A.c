#include "proj4fkhan42.h"

int eval(int v1,int OP,int v2)
{
   
    switch (OP)
    {
        case '+':
            return v1+v2;
        case '-':
            return v1-v2;
        case '*':
            return v1*v2;
        case '/':
            return v1/v2;
        default:
            break;
    }
    
    fprintf(stderr,"Error in eval funtion operator is not a +,-,/ or *\n");
    return DUMMY;
}


void popAndEval(stack *stackV, stack* stackOP)//outline provided from Prof.Troy
{
    int OP= top(stackOP);
    pop(stackOP);
    int v2= top(stackV);
    pop(stackV);
    int v1= top(stackV);
    pop(stackV);
    int v3= eval(v1,OP,v2);
    push(stackV,v3);

}


void freeAll(stack* setFreeV,stack* setFreeOP)
{
    while (!isEmpty(setFreeV))
        pop(setFreeV);

    while(!isEmpty(setFreeOP))
        pop(setFreeOP);
    
    free(setFreeV->top);
    free(setFreeOP->top);
    free(setFreeV);
    free(setFreeOP);
}


stack* createStackDummy()
{
    NODE *DummyNode=(NODE*)malloc(sizeof(NODE));
    DummyNode->value=DUMMY;
    DummyNode->next=NULL;
    
    stack *headStack=(stack*)malloc(sizeof(stack));
    headStack->top=DummyNode;
    headStack->bot=DummyNode;
    
    return headStack;
}

int isEmpty(stack *test)
{
    return test->top==test->bot;
}

void push(stack *add, int data)
{
    NODE *temp= (NODE*)malloc(sizeof(NODE));
    temp->value=data;
    temp->next=NULL;
    
    if(!isEmpty(add))
    {
        temp->next=add->top->next;
        add->top->next=temp;
    }
    else
    {
        add->top->next=temp;
        add->bot=temp;
    }
    
}

void pop(stack *remove)
{
    if (!isEmpty(remove))
    {
        NODE *temp= remove->top->next;
        
        if(temp==remove->bot)
            remove->bot=remove->top;
        else
            remove->top->next=temp->next;

        free(temp);
    }
    else
        fprintf(stderr,"The current stack is empty for POP\n");
    
}

int top(stack *display)
{
    if (!isEmpty(display))
    {
        return display->top->next->value;
    }
    else
        fprintf(stderr,"The current stack is empty for top\n");
    
    return DUMMY;
}

boolean debugSwitch(char **argv)
{
    int i=1;//Starting with one because argv[0] will ./a.out no point in checking
    while (argv[i]!=NULL)//looking at the address to see if it is a null because in command line **argv pointer to array
    {
        if (strcmp(argv[i],"-d")==0)
        {
            printf("\nDebugging Information\n\n");
            return TRUE;
        }
        i++;
    }
    
    return FALSE;
}

/**FUNTIONS BELOW ALL FOR TESTING PURPOSES****/


boolean lst_sanity1(stack* test) {
    if(test->top == NULL && test->bot != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(test->top == NULL && test->top != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

boolean lst_sanity2(stack* test) {
    if(test->bot != NULL && test->bot->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return 1;
}

boolean lst_sanity3(stack* test)
{
    NODE *p=test->top;
    NODE *q=test->bot;
    //NODE *q=l->front;
    int n= lst_len(test);
    int i=1;
    while (i<=n)
    {
        if (i==n&&p==q)
        {
            //printf("\nwalked succesfully..i::%i,,,n::%i\n",i,n);
            return 1;//Success
        }
        p=p->next;
        i++;
    }
    //printf("\nwalk UNsuccesfully\n");
    fprintf(stderr,"lst_sanity3 error: back pointer is not the last reachable node\n");
    return 0;//UNsuccess
}


int lst_len(stack* test)
{
    NODE *p = test->top;
    int n=0;
    
    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}


