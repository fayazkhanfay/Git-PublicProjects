#include "fkhan42H.h"

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

/* addToList: This operation is to add a new node to the end of the linked list.
 This is to be used when the a and c commands are given as input.*/
void addToList (wL* waitL, int size,char* name, boolean inRest)
{
    NODE* temp=waitL->tail;
    NODE* new=(NODE*)malloc(sizeof(NODE));
    new->next=NULL;
    strcpy(new->nameGroup,name);
    new->numInGroup=size;
    new->resStatusIn=inRest;
    temp->next=new;
    waitL->tail=new;
}

/*
 freeAll: travesses through the list till hits tail free tail, moves tail over
 start from begining ttraverses till next equals tail. till head and tail equal
 each other. Free the dummy and free wL
 */
void freeAll(wL* waitL)
{
    if(debugMode)
        printf("Starting of freeAll\n");
    
    NODE *temp=waitL->head;
    while (waitL->head!=waitL->tail)
    {
        while (temp->next!=waitL->tail)
        {
            if(debugMode)
            {
                char tempBooDisplay[5];
                
                if(temp->resStatusIn)
                    strcpy(tempBooDisplay,"YES");
                else
                    strcpy(tempBooDisplay,"NO");
                
                printf("DebugMode::freeAll::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
            }
            temp=temp->next;
        }
        free(waitL->tail);
        waitL->tail=temp;
        waitL->tail->next=NULL;
        temp=waitL->head;
    }
    
    free(waitL->head);
    free(waitL);
    
    if(debugMode)
        printf("ending of freeAll\n");
}


/* doesNameExist: This operation is to return a Boolean value indicating whether
 a name already exists in the linked list. This is to be used when the a, c, w and l
 commands are given as input.*/
boolean doesNameExist (wL* waitL, char *name)
{
    NODE* temp;
    
    if(waitL->head->next!=NULL)
    {
        temp=waitL->head;
        do
        {
            if(debugMode)
            {
                char tempBooDisplay[5];
                
                if(temp->resStatusIn)
                    strcpy(tempBooDisplay,"YES");
                else
                    strcpy(tempBooDisplay,"NO");
                
                printf("DebugMode::doesNameExist::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
            }
            
            temp=temp->next;
            if (strcmp(temp->nameGroup,name)==0)
            {
                return YES;//name does exist
            }
            
        }while(temp->next!=NULL);
    }
    
    return NO;//name does not exist
}

/*createHeadTail creating a node that will will point head and tail of list*/
wL *createHeadTail()
{
    wL* temp= (wL*)malloc(sizeof(wL));
    temp->head=(NODE*)malloc(sizeof(NODE));
    temp->tail=temp->head;
    temp->head->next=NULL;
    temp->head->numInGroup=DUMMY;
    strcpy(temp->head->nameGroup,"DUMMY");
    //temp->head->nameGroup=
    return temp;
}


boolean lst_sanity1(wL* waitL) {
    if(waitL->head == NULL && waitL->tail != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(waitL->head == NULL && waitL->tail != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

boolean lst_sanity2(wL* waitL) {
    if(waitL->tail != NULL && waitL->tail->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return 1;
}

boolean lst_sanity3(wL* waitL)
{
    NODE *p=waitL->head;
    NODE *q=waitL->tail;
    //NODE *q=l->front;
    int n= lst_len(waitL);
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


int lst_len(wL * waitL)
{
    NODE *p = waitL->head;
    int n=0;
    
    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

/*
 updateStatus: This operation is to change the in-restaurant status when a call-ahead
 group arrives at the restaurant. This operation will return a FALSE value if that group
 is already marked as being in the restaurant. This is to be used when the w command is given as input.
 */
boolean updateStatus (wL* waitL, char* name)
{
    NODE* temp=waitL->head;
    
    while (strcmp(temp->nameGroup,name)!=0)
    {
        
        if(debugMode)
        {
            char tempBooDisplay[5];
            
            if(temp->resStatusIn)
                strcpy(tempBooDisplay,"YES");
            else
                strcpy(tempBooDisplay,"NO");
            
            printf("DebugMode::updateStatus::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
        }

        temp=temp->next;
    }
    if(!temp->resStatusIn)
    {
        return temp->resStatusIn=TRUE;
    }
    else
        return FALSE;//marked as being in the restaurant
}


/*
 displayListInformation:
 This operation to traverse down the entire list from beginning to end.
 As each node is traversed, print out that node’s group name, group size and in-restaurant status.
 This command is to be used when the d command is given as input.
 */
void displayListInformation (wL* waitL)//COMPLETE
{
    NODE* temp=waitL->head->next;
    char tempBooDisplay[5];
    while(temp!=NULL)
    {
        if(temp->resStatusIn)
            strcpy(tempBooDisplay,"YES");
        else
            strcpy(tempBooDisplay,"NO");
        printf("Group name %s, size %d, In Restaurant %s\n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
        temp=temp->next;
    }
    
}

/*
 displayGroupSizeAhead:
 This operation traverses down the list until a specific group name is encountered.
 As each node is traversed, print out that node’s group size.
 This command is to be used when the l command is given.*/
void displayGroupSizeAhead (wL* waitL, char* name)//COMPLETE//l//dolist
{
    NODE* temp=waitL->head->next;
    int i=0;
    while (strcmp(temp->nameGroup,name)!=0)
    {
        printf("Group \"%s\" size of %d\n",temp->nameGroup,temp->numInGroup);
        i++;
        
        if(debugMode)
        {
            char tempBooDisplay[5];
            
            if(temp->resStatusIn)
                strcpy(tempBooDisplay,"YES");
            else
                strcpy(tempBooDisplay,"NO");
            
            printf("DebugMode::displayGroupSizeAhead::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
        }
        
        temp=temp->next;
    }
    if(i==0)
        printf("Group \"%s\" is next in line\n",name);
}


/*
 countGroupsAhead:
 This operation is to return the number of groups waiting ahead of a group with a specific name.
 This is to be used when the l command is given as input.
 */
int countGroupsAhead (wL* waitL, char* name)//COMPLETE
{
    NODE* temp=waitL->head->next;
    int i=0;
    while (strcmp(temp->nameGroup,name)!=0)
    {
        i++;
        
        if(debugMode)
        {
            char tempBooDisplay[5];
            
            if(temp->resStatusIn)
                strcpy(tempBooDisplay,"YES");
            else
                strcpy(tempBooDisplay,"NO");
            
            printf("DebugMode::countGroupsAhead::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
        }
        
        temp=temp->next;
    }
    
    return i;
}


//typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

/*
typedef struct node
{
    char nameGroup[50];
    int numInGroup;
    boolean resStatusIn;//whether the group has called ahead or is waiting in the restaurant
    struct node *next;
}NODE;

struct waitList
{
    NODE *head;
    NODE *tail;
};
*/


/*
 retrieveAndRemove: 
 This operation is to find the first in-restaurant group that can fit at a given table.
 This operation is to return the name of group. This group is to be removed from the linked list.
 This is to be used when the r command is given as input.
 */
char *retrieveAndRemove(wL* waitL, int size)
{
    //char temp[20];
    NODE *temp=waitL->head;
    NODE *removal=NULL;
    while(temp->next!=NULL)
    {
        if(debugMode)
        {
            char tempBooDisplay[5];
            
            if(temp->resStatusIn)
                strcpy(tempBooDisplay,"YES");
            else
                strcpy(tempBooDisplay,"NO");
            
            printf("DebugMode::retrieveAndRemove::Group \"%s\" size %d ,Status in %s \n",temp->nameGroup,temp->numInGroup,tempBooDisplay);
        }
        
        if((temp->next->numInGroup<=size)&&(temp->next->resStatusIn==YES))//sanity 3 not working and seg faults!!
        {
            char *nameRem=(char*)malloc(sizeof(char)*30);
            strcpy(nameRem,temp->next->nameGroup);
            removal=temp->next;
            temp->next=removal->next;
            
            if(waitL->tail==removal)
                waitL->tail=temp;
            
            free(removal);
            
            if(debugMode)
            {
                lst_sanity1(waitL);
                lst_sanity2(waitL);
                lst_sanity3(waitL);
            }
            
            return nameRem;
        }
        temp=temp->next;
    }
    
    return NULL;
}










