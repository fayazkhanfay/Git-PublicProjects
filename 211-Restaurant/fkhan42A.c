#include "fkhan42H.h"

void doAdd (wL* waitL)//COMPLETE
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    //printf("before does name exist\n");
    if(!doesNameExist(waitL,name))
    {
        //printf("IN does name exist\n");
        printf ("Adding group \"%s\" of size %d\n", name, size);
        addToList(waitL,size,name,YES);//The differnce between this is 4th condition because not present in Rest
    }
    else
         printf ("Not Adding group because Name exist \"%s\" of size %d\n", name, size);
        
}

void doCallAhead (wL* waitL)//COMPLETE
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    printf ("Call-ahead group \"%s\" of size %d\n", name, size);
    
    if(!doesNameExist(waitL,name))
    {
        printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
        addToList(waitL,size,name,NO);//The differnce between this is 4th condition because not present in Rest
    }
    else
        printf ("Not Adding Call-ahead group because Name exist \"%s\" of size %d\n", name, size);

    
}

void doWaiting (wL* waitL)//COMPLETE
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }
    
    
    if(doesNameExist(waitL,name))
    {
        //printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
        //addToList(waitL,size,name,NO);//The differnce between this is 4th condition because not present in Rest
        if(updateStatus(waitL,name))
            printf ("Waiting group \"%s\" is now in the restaurant\n", name);
        else
            printf ("Waiting group \"%s\" is already present in restaurant\n", name);
        
    }
    else
         printf ("Waiting group \"%s\" not on the Waiting list\n", name);
}

void doRetrieve (wL* waitL)//NOT DONE!!!!!!!!!
{
    /* get table size from input */

    char* nameRem;
    
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    
    printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n\n", size);
    
    if (waitL->head->next!=NULL)
    {
        if((nameRem =retrieveAndRemove(waitL,size))!=NULL)
            printf("first group that can fit at a table of size %d is group %s \n", size,nameRem);
        else
            printf("Currently cannot accomadate for size %d\n",size);
    }
    else
        printf("Waiting list is empty\n");
    
    free(nameRem);

}

void doList (wL* waitL)//COMPLETE
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }

    
    if(doesNameExist(waitL,name))
    {
        printf("Number of Group waiting ahead of Group \"%s\" is %d \n\n",name,countGroupsAhead(waitL,name));
        printf ("Group \"%s\" is behind the following groups\n", name);
        displayGroupSizeAhead (waitL,name);
    }
    else
    {
        printf ("Group \"%s\" is not in wait list\n", name);
    }
}


void doDisplay (wL* waitL)//COMPLETE
{
    clearToEoln();
    
    if(waitL->head->next!=NULL)
    {
        printf ("Display information about all groups\n");
        displayListInformation(waitL);
    }
    else
        printf("List is empty for Display information\n");

}









