#include<stdio.h>
#include<stdlib.h>//Used for malloc and free


void arrayCopy(int fromArray[],int toArray[],int size);//it take a copy of an array
void sort(int arr[],int size);//Takes an array and sorts of programers choice, I used bubble sort
int lsearch(int arr[],int size,int target,int* numComparisons);//This searchs for a value from left to right
// it sends back the index position of where the value is found and it updates a value of number comparison via pointer

int Bsearch(int arr[],int size,int target, int* numComparisons);//Binary works by dividing the array in half but the
//array has to be first sorted either least to greates or vice versa but must be consistant
//After repeates the dividing in half and ignores the part of the section that is either greater than and less than

int test_sort(int arr[],int size);//This is an assist function for for sort becasue in sort function it uses
//bubble sort algorithem, so this function just test from left to right to see if sorted

int *Create(int size);//This function creates the initial space for 100 indexs and sends back a pointer to this allocated space

int *Inc_Cap(int *Data,int size);//This function creates a new allocated space but it is double the size of the
//previous array and then copys the values into new malloced(Double size) array and then frees the previous array

void free_space(int* pointer );//This frees the space that was allocated for the array

int main()
{
    int test;
    
    int terminal=-999;//this is for input text, so the loop knows when to stop

    int size=100;//Initial size
    int i=0;

    int *Data=Create(size);
    
    scanf("%d",&Data[i]);//Read in our initialize variable for our array
    //printf("i:%d and val:%d\n",i,Data[i]);
    i++;
    
    //????Even without increasing the allocated space the array was not Seg faulting
    
    while (Data[i-1]!=terminal)//This looks at the previous posi
    {
        scanf("%d",&Data[i]);
        //printf("i:%d and val:%d\n",i,Data[i]);
        i++;
        if (i==size)//this counter counts up size malloced for array, if true goes into function
        {
            size=size*2;
            Data=Inc_Cap(Data,size);
        }
    }
    printf("\nReading in Data Complete\n");
    size=i-1;//the get rid of the -999 in the array because we dont want that sorted
   
    //printf("Test_shot\n");
    
    int *lsearch_numComp_P;//This is for number of comparisons because we want to return to values from functions
    int *bsearch_numComp_P;
    
    int lsearch_numComp=0;
    int bsearch_numComp=0;
    
    lsearch_numComp_P=&lsearch_numComp;//Take the address of the right because we need to point to that space
    bsearch_numComp_P=&bsearch_numComp;
    
    
    int* toArray=Create(size);//We are mallocing because to we can free it later
    
    arrayCopy(Data,toArray,size);//self- explanatory
    
    sort(Data,size);
    
    i=0;
   
    int target;//This is the value that need to be found for binary and linear search
    scanf("%d",&target);
     //printf("Target Value: %d\n",target);
    while (target!=terminal)
    {
        
        //scanf("%d",&target);
        //printf("Target Value: %d\n",target);
    
        int Print_Lsearch=lsearch(toArray,size,target,lsearch_numComp_P);//reason for this becaue we are sending the index location
    
        if (Print_Lsearch==-1)//because of the above statement is the reason for this "if" statement
        {//we dont want to run the same function twice becasue it would be unneccassay
            printf("Value not found in Linear search\n");
        }
        else
            printf("Target Value:%d found with Linear search in Array position %d with %d comparisons\n",target,Print_Lsearch,*lsearch_numComp_P);
    
    
        int Print_Bsearch=Bsearch(Data,size,target,bsearch_numComp_P);
    
        if (Print_Bsearch==-1)
        {  //Same sort of logic as lsearch explaniation for "if"
            printf("Value not found in Binary search\n");
        }
        else
            printf("Target Value:%d found with Binary search in Array position %d with %d comparisons\n",target,Print_Bsearch,*bsearch_numComp_P);
        
        lsearch_numComp=0;
        bsearch_numComp=0;
        scanf("%d",&target);
    
    }
    
    free_space(Data);
    free_space(toArray);
    
    return 0;
}

void free_space(int* pointer)//Free the memory allocated to whatever the pointer is pointing at
{
    free(pointer);
    printf("\nMemory Freed\n");
}

int *Inc_Cap(int Data[],int size)//COMPLETE
{
    printf("Increasing Capacity\n");
    int *temp;
    temp = (int *) malloc ( size * sizeof(int) );
    int i;
    for ( i = 0 ; i < size ; i++)//takes previous data and reads it into new space(temp)
        temp[i] = Data[i];
    free (Data);//free the previous data
    return temp;//return the new allocated space
}

int *Create(int size)//COMPLETE
{
    int *darr;//first create a pointer but not pointing at anything
    //int size = 100;//this value given to us
    printf("Space allocated\n\n");
    return darr =malloc (size * sizeof(int) );//this creates x size array and return the pointer to our new space allocated
}

void arrayCopy(int fromArray[],int toArray[],int size)//COMPLETE
{
    int i=0;
    printf("\nCopying into new Array\n");
    while (i<size)
    {
        toArray[i]=fromArray[i];//simple read in
        i++;
    }
    

    i=0;//this bottom portion is to see if every value is read in properly
    while (i<size)
    {
       
        if (fromArray[i]!=toArray[i])
        {
            printf(" Error Array Copy Unsuccesful\n");
            return;
        }
        i++;
    }
    printf("Array Copy Successful and Verified\n");
    //printf("\n");
    
}

void sort(int arr[],int size)//BUBBLE SORT//COMPLETE
{
    //int test=1;
    int i=0;
    int temp;
    while (test_sort(arr,size))// the test_sort function sees if the array is order if it is not continues while loop
    {
        i=0;
        while (i<size-1)
        {
            if (arr[i]>arr[i+1])
            {
                temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
            }
            i++;
        }
    }
    i=0;
    while (i<size-1)
    {
        //printf("%d ",arr[i]);
        if (arr[i]>arr[i+1])
        {
            printf("Error Sorting Unsuccessful\n");
            return;
        }
        i++;
    }
    printf("\nSorting Successful and Verified\n");
    
}

int test_sort(int arr[],int size)//PART OF sort functon//COMPLETE
{
    int i=0;
    
    while (i<size-1)
    {
        if (arr[i]>arr[i+1])
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int lsearch(int arr[],int size,int target,int* numComparisons)//COMPLETE
{
    
    int i=0;
    printf("\nSearching Unsorted Array Linearly\n");
    
    while (i<size)
    {
        if (arr[i]==target)
        {
            *numComparisons=i+1;
            
            return i;
            
        }
        i++;
    }
    return -1;//if not found
}

int Bsearch(int arr[],int size,int target, int* numComparisons)//COMPLETE
{
    printf("\nSearching Sorted Array with Binary method\n");
    
    int top=size-1;//we did this because size does not account for index 0 that why we subtract 1
    int bot=0;//starts at index 0
    int test=arr[(((top-bot)/2)+bot)];//reason we add bottom because you need a reference point. Cannot assume bottom
                                    //will be zero everytime
    
    *numComparisons=0;//This is 1 because we initialized variable test that was not yet a comparison but
                    // when entering while loop it will be compared to target and if true it will return
                    //no other place to increment *numcomparisons
    
    while (top>=bot)
    {
        if (target==test)
            return ((top-bot)/2)+bot;
        if (target>test)
        {
            bot=((top-bot)/2)+bot+1;
        }
        else
        {
            top=((top-bot)/2)+bot-1;

        }
        
        test=arr[((top-bot)/2)+bot];//we only look up in array once but the value is stored in test and that is
                                    //being compared
        
        *numComparisons=*numComparisons+1;
    }
    
        return -1;//if not found
}









